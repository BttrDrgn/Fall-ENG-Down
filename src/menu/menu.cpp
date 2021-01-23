#include <DxLib.h>
#include <bgm/bgm.h>
#include <display/display.h>
#include <file_list/file_list.h>
#include <game_play/game_play.h>
#include <key/key.h>
#include <layer/layer.h>
#include <load/load.h>
#include <macro_function.h>
#include <main.h>
#include <save/save.h>
#include <sound_effect/sound_effect.h>
#include <voice/voice.h>
#include <window_mode/window_mode.h>

char FLDN_FileName[256];
int SelectingTime = 0;
int SelectLevel = 0;
int SelectOption = 0;
int SelectPage = 0;
int SelectingFlag = 0;

void SoundVolumeSet(){
	SoundEffect.SetVolume(Save.ReadSystem(Save.SE_VOLUME));
	Voice.SetVolume(Save.ReadSystem(Save.VOICE_VOLUME));
}

void SetStatus(){
	Save.LoadCourse("dat/save/speed.save");
	Status.RoadMaxLevel[0]=Save.ReadCourse(Save.BEST_LEVEL);
	Status.RoadMaxPoint[0]=Save.ReadCourse(Save.BEST_POINT);
	Save.LoadCourse("dat/save/chaos.save");
	Status.RoadMaxLevel[1]=Save.ReadCourse(Save.BEST_LEVEL);
	Status.RoadMaxPoint[1]=Save.ReadCourse(Save.BEST_POINT);
	Status.GradeHS=0;
	Status.GradeHSSum=0;
	Status.MaxClearGrade=-1;
	for(int i=0;i<=GRADE_MAX;i++){
		char Path[256]={0};
		sprintf_s(Path,sizeof(Path),"dat/save/grade_%02d.save",i);
		Save.LoadCourse(Path);
		Status.GradeHSSum+=Save.ReadCourse(Save.BEST_SCORE);
		if(Save.ReadCourse(Save.CLEAR_TIMES)){
			Status.MaxClearGrade=i;
			Status.GradeHS=Save.ReadCourse(Save.BEST_SCORE);
		}
		else i=GRADE_MAX;
	}
}

void StartingSet(){
	GameStartRemainCount=180;
	SoundEffect.Stop(15);
	SoundEffect.Stop(16);
	GraphicInfo.MaskLevel=Progress.Level;
	LoadBackGraphic(0);
	for(int i=0;i<OBSTACLE_MAX;i++){
		if(Course.NaturalObstacle[i]||Scenario[Progress.Level].FirstObstacle[i])ObstacleFlag[i]=1;
		else ObstacleFlag[i]=0;
	}
	if(Scenario[Progress.Level].ObstacleTime==0){
		for(int i=0;i<OBSTACLE_MAX;i++)if(Scenario[Progress.Level].ObstacleFlag[i])ObstacleFlag[i]=1;
		WarnFlag=3;
	}
	else WarnFlag=0;
	FontSizePosSetting();
	for(int i=0;i<SHAPE_MAX;i++){
		if(Course.ShapePath[i][0]!='\0'){
			LoadShape(Course.ShapePath[i],i);
		}
	}
	for(int i=0;i<ROTATION_MAX;i++){
		if(Course.RotationPath[i][0]!='\0'){
			LoadRotation(Course.RotationPath[i],i);
		}
	}
	for(int i=0;i<Layer.MAX;i++){
		if(Course.LayerPath[0]!=0&&(Course.CopyLayerPath[i]<0||Course.CopyLayerPath[i]>=Layer.MAX)){
			Layer.LoadImage(i,Course.LayerPath[i]);
		}
	}
	for(int i=0;i<Layer.MAX;i++){
		if(Course.CopyLayerPath[i]>=0&&Course.CopyLayerPath[i]<Layer.MAX){
			Layer.CopyImage(Course.CopyLayerPath[i],i);
		}
	}
	SoundVolumeSet();
	if(Course.PlayingRank){
		Progress.Rank=CalcRank(Course.RankBoard,Course.RankSign);
	}
}

int GameSelect(){
	switch(MainFlag%100/10){
		case 0:
			Save.SaveSystem();
			SoundVolumeSet();
			Bgm.Stop();
			SoundEffect.Stop(15);
			SoundEffect.Stop(16);
			Layer.Initialize();
			SetStatus();
			memset(&Progress,0,sizeof(Progress_t));
			NewRecord.Level=0;
			NewRecord.Point=0;
			NewRecord.Rank=0;
			NewRecord.Score=0;
			NewRecord.Time=0;
			GraphicInfo.MaskLevel=-1;
			LoadBackGraphic(1);
			MainFlag+=10;
		case 1:
			if((Key.Check(KC_DOWN)==1||(Key.Check(KC_DOWN)>14&&Key.Check(KC_DOWN)%3==0))){
				Progress.Mode=(Progress.Mode+8)%7;
				SoundEffect.RaiseFlag(18);
			}
			else if((Key.Check(KC_UP)==1||(Key.Check(KC_UP)>14&&Key.Check(KC_UP)%3==0))){
				Progress.Mode=(Progress.Mode+6)%7;
				SoundEffect.RaiseFlag(18);
			}
			else if(Key.Check(KC_DECIDE)==1){
				SoundEffect.RaiseFlag(20);
				if(Progress.Mode==6){
					MainFlag=999;
				}
				else if(Progress.Mode==5){
					SelectOption=0;
					SelectPage = 0;
					MainFlag=400;
				}
				else if(Progress.Mode==4){
					SelectOption=0;
					MainFlag=300;
				}
				else {
					Progress.Grade=0;
					Progress.Level=0;
					Progress.OtherCourse=0;
					if(Progress.Mode==0||Progress.Mode==1||Progress.Mode==2){
						MainFlag+=20;
						SelectingTime=0;
					}
					if(Progress.Mode==0){
						strcpy_s(FLDN_FileName,sizeof(FLDN_FileName),"dat/archive/speed.fldn");
					}
					else if(Progress.Mode==1){
						strcpy_s(FLDN_FileName,sizeof(FLDN_FileName),"dat/archive/chaos.fldn");
					}
					else if(Progress.Mode==2){
						strcpy_s(FLDN_FileName,sizeof(FLDN_FileName),"dat/archive/grade_00.fldn");
					}
					else if(Progress.Mode==3){
						if(FileList.HowManyFiles()>0){
							FileList.FilePath(Progress.OtherCourse,FLDN_FileName);
							MainFlag+=10;
						}
					}
					Progress.LevelMax=LoadCourse(FLDN_FileName,-1);
					Save.LoadCourse(CrsSaveFileName);
				}
			}
			else if(Key.Check(KC_HOLD)==1){
				SoundEffect.RaiseFlag(20);
				ViewMode=1;
			}
			break;
		case 2:
			if((Key.Check(KC_DOWN)==1||(Key.Check(KC_DOWN)>14&&Key.Check(KC_DOWN)%3==0))){
				SoundEffect.RaiseFlag(18);
				Progress.OtherCourse=(Progress.OtherCourse+FileList.HowManyFiles()+1)%FileList.HowManyFiles();
				FileList.FilePath(Progress.OtherCourse,FLDN_FileName);
				Progress.LevelMax=LoadCourse(FLDN_FileName,-1);
				Save.LoadCourse(CrsSaveFileName);
			}
			else if((Key.Check(KC_UP)==1||(Key.Check(KC_UP)>14&&Key.Check(KC_UP)%3==0))){
				SoundEffect.RaiseFlag(18);
				Progress.OtherCourse=(Progress.OtherCourse+FileList.HowManyFiles()-1)%FileList.HowManyFiles();
				FileList.FilePath(Progress.OtherCourse,FLDN_FileName);
				Progress.LevelMax=LoadCourse(FLDN_FileName,-1);
				Save.LoadCourse(CrsSaveFileName);
			}
			else if(Key.Check(KC_DECIDE)==1){
				SoundEffect.RaiseFlag(20);
				Progress.Level=0;
				MainFlag+=10;
				SelectingTime=0;
			}
			else if(Key.Check(KC_CANCEL)==1){
				SoundEffect.RaiseFlag(19);
				MainFlag-=10;
			}
			else if(Key.Check(KC_HOLD)==1){
				SoundEffect.RaiseFlag(20);
				ViewMode=1;
			}
			break;
		case 3:
			SelectingTime++;
			if(Progress.Mode==2){
				if((Key.Check(KC_DOWN)==1||(Key.Check(KC_DOWN)>14&&Key.Check(KC_DOWN)%3==0))&&Progress.Grade>0){
					SoundEffect.RaiseFlag(18);
					Progress.Grade--;
					sprintf_s(FLDN_FileName,sizeof(FLDN_FileName),"dat/archive/grade_%02d.fldn",Progress.Grade);
					Progress.LevelMax=LoadCourse(FLDN_FileName,-1);
					Save.LoadCourse(CrsSaveFileName);
					SelectingTime=0;
				}
				else if((Key.Check(KC_UP)==1||(Key.Check(KC_UP)>14&&Key.Check(KC_UP)%3==0))&&Progress.Grade<MIN(Status.MaxClearGrade+1,GRADE_MAX)){
					SoundEffect.RaiseFlag(18);
					Progress.Grade++;
					sprintf_s(FLDN_FileName,sizeof(FLDN_FileName),"dat/archive/grade_%02d.fldn",Progress.Grade);
					Progress.LevelMax=LoadCourse(FLDN_FileName,-1);
					Save.LoadCourse(CrsSaveFileName);
					SelectingTime=0;
				}
				else if(Key.Check(KC_DECIDE)==1){
					GameInitialize();
					SoundEffect.RaiseFlag(20);
					SelectLevel=Progress.Level=0;
					StartingSet();
					StartNext();
					MainFlag=100;
				}
				else if(Key.Check(KC_CANCEL)==1){
					SoundEffect.RaiseFlag(19);
					GraphicInfo.MaskLevel=-1;
					LoadBackGraphic(1);
					MainFlag-=20;
				}
				else if(Key.Check(KC_HOLD)==1){
					SoundEffect.RaiseFlag(20);
					ViewMode=1;
				}
			}
			else {
				if((Key.Check(KC_DOWN)==1||(Key.Check(KC_DOWN)>14&&Key.Check(KC_DOWN)%3==0))&&Progress.Level>0){
					SoundEffect.RaiseFlag(18);;
					Progress.Level--;
					SelectingTime=0;
				}
				else if(Key.Check(KC_UP)==1||(Key.Check(KC_UP)>14&&Key.Check(KC_UP)%3==0)){
					int max=MIN(Save.ReadCourse(Save.BEST_LEVEL)-Course.SelectLimit,Progress.LevelMax);
					if(Progress.Level<max){
						SoundEffect.RaiseFlag(18);
						Progress.Level++;
						SelectingTime=0;
					}
				}
				else if(Key.Check(KC_DECIDE)==1){
					GameInitialize();
					SoundEffect.RaiseFlag(20);
					SelectLevel=Progress.Level;
					GameStartRemainCount=180;
					StartingSet();
					StartNext();
					MainFlag=100;
				}
				else if(Key.Check(KC_CANCEL)==1){
					SoundEffect.RaiseFlag(19);
					GraphicInfo.MaskLevel=-1;
					LoadBackGraphic(1);
					if(Progress.Mode==3){
						MainFlag-=10;
					}
					else {
						MainFlag-=20;
					}
				}
				else if(Key.Check(KC_HOLD)==1){
					SoundEffect.RaiseFlag(20);
					ViewMode=1;
				}
			}
			if(SelectingTime==30&&MainFlag%100/10==3){
				GraphicInfo.MaskLevel=Progress.Level;
				LoadBackGraphic(0);
			}
			break;
	}
	return 1;
}

int BackViewing(){
	if(Key.Check(KC_HOLD)==1){
		SoundEffect.RaiseFlag(20);
		if(ViewMode==1)ViewMode=2;
		else ViewMode=1;
	}
	else if(Key.Check(KC_DECIDE)==1){
		SoundEffect.RaiseFlag(20);
		ViewMode=0;
	}
	else if(Key.Check(KC_CANCEL)==1){
		SoundEffect.RaiseFlag(19);
		ViewMode=0;
	}
	return 1;
}

int GameReady(){
	GameStartRemainCount--;
	if(GameStartRemainCount<1)MainFlag=200;
	return 1;
}

void GameConfiguration(){
	int saveNum = -1;
	int saveList[14] = { 0 };
	saveList[0] = Save.BGM_VOLUME;
	saveList[1] = Save.SE_VOLUME;
	saveList[2] = Save.VOICE_VOLUME;
	saveList[3] = Save.WINDOW_MODE;
	saveList[4] = Save.KEY_CONFIG;
	saveList[5] = Save.ANIMATION;
	saveList[6] = Save.SE_SET;
	saveList[7] = Save.CASCADE;
	saveList[8] = Save.BLOCK_FLAG;
	saveList[9] = Save.GHOST;
	saveList[10] = Save.RULED_LINE;
	saveList[11] = Save.DARKNESS;
	saveList[12] = Save.SHOW_ADDPT;
	saveList[13] = Save.BOARD;

	if (SelectingFlag == 0){
		if (Key.Check(KC_DOWN) == 1 || (Key.Check(KC_DOWN) > 14 && Key.Check(KC_DOWN) % 3 == 0)){
			SelectOption = (SelectOption + 10) % 9;
			MainFlag = MainFlag / 100 * 100 + SelectPage * 10 + SelectOption;
			SoundEffect.RaiseFlag(18);
		}
		else if (Key.Check(KC_UP) == 1 || (Key.Check(KC_UP) > 14 && Key.Check(KC_UP) % 3 == 0)){
			SelectOption = (SelectOption + 8) % 9;
			MainFlag = MainFlag / 100 * 100 + SelectPage * 10 + SelectOption;
			SoundEffect.RaiseFlag(18);
		}
		else if (Key.Check(KC_DECIDE) == 1){
			SoundEffect.RaiseFlag(20);
			if (SelectOption == 7){
				SelectPage = (SelectPage + 1) % 2;
				MainFlag = MainFlag / 100 * 100 + SelectPage * 10 + SelectOption;
			}
			else if (SelectOption == 8){
				Progress.Mode = 0;
				SelectingFlag = 0;
				SelectPage = 0;
				SelectOption = 0;
				MainFlag = 0;
			}
			else {
				SelectingFlag = 1;
				MainFlag = MainFlag / 100 * 100 + 50 + SelectPage * 10 + SelectOption;
			}
		}
		else if (Key.Check(KC_CANCEL) == 1){
			SoundEffect.RaiseFlag(19);
			Progress.Mode = 0;
			SelectPage = 0;
			SelectOption = 0;
			MainFlag = 0;
		}
	}
	else {
		int pos = SelectPage * 7 + SelectOption;
		int soundFlag = 0;
		saveNum = saveList[pos];
		if (Save.ReadSystem(saveNum) < 0 || Save.ReadSystem(saveNum) > Save.GetConfigMax(saveNum)){
			Save.WriteSystem(saveNum, Save.GetConfigDefault(saveNum));
		}
		if ((Key.Check(KC_UP) == 1 || (Key.Check(KC_UP) > 14 && Key.Check(KC_UP) % 3 == 0)) && Save.ReadSystem(saveNum) < Save.GetConfigMax(saveNum)){
			Save.WriteSystem(saveNum, Save.ReadSystem(saveNum) + 1);
			if (saveList[pos] == Save.BGM_VOLUME || saveList[pos] == Save.SE_VOLUME || saveList[pos] == Save.VOICE_VOLUME){
				SoundVolumeSet();
			}
			SoundEffect.RaiseFlag(18);
		}
		else if ((Key.Check(KC_DOWN) == 1 || (Key.Check(KC_DOWN)>14 && Key.Check(KC_DOWN) % 3 == 0)) && Save.ReadSystem(saveNum) > 0){
			Save.WriteSystem(saveNum, Save.ReadSystem(saveNum) - 1);
			if (saveList[pos] == Save.BGM_VOLUME || saveList[pos] == Save.SE_VOLUME || saveList[pos] == Save.VOICE_VOLUME){
				SoundVolumeSet();
			}
			SoundEffect.RaiseFlag(18);
		}
		else if (Key.Check(KC_CANCEL) == 1){
			if (saveNum == Save.SE_SET){
				SoundEffect.LoadSet(Save.ReadSystem(Save.SE_SET));
				SoundVolumeSet();
			}
			if (saveNum == Save.WINDOW_MODE){
				if (WindowMode.Change(Save.ReadSystem(Save.WINDOW_MODE)) == 1){
					ColorSetting();
				}
			}
			SoundEffect.RaiseFlag(19);
			SelectingFlag = 0;
			Save.SaveSystem();
			MainFlag = MainFlag / 100 * 100 + SelectPage * 10 + SelectOption;
		}
		else if (saveNum == Save.KEY_CONFIG && Key.Check(KC_DECIDE) == 1){
			SoundEffect.RaiseFlag(20);
			if (Save.ReadSystem(saveNum) == 0){
				MainFlag = 500;
				SelectPage = 0;
				SelectOption = 0;
			}
			else {
				MainFlag = 550;
				SelectPage = 1;
				SelectOption = 0;
			}
		}
	}
}

void GameCareer(){
	if((Key.Check(KC_DOWN)==1||(Key.Check(KC_DOWN)>14&&Key.Check(KC_DOWN)%3==0))){
		SelectOption=(SelectOption+5)%4;
		MainFlag = MainFlag / 10 * 10 + SelectOption;
		SoundEffect.RaiseFlag(18);
	}
	else if((Key.Check(KC_UP)==1||(Key.Check(KC_UP)>14&&Key.Check(KC_UP)%3==0))){
		SelectOption=(SelectOption+3)%4;
		MainFlag = MainFlag / 10 * 10 + SelectOption;
		SoundEffect.RaiseFlag(18);
	}
	else if(Key.Check(KC_DECIDE)==1){
		SoundEffect.RaiseFlag(20);
		Progress.Mode=0;
		MainFlag=0;
	}
	else if(Key.Check(KC_CANCEL)==1){
		SoundEffect.RaiseFlag(19);
		Progress.Mode=0;
		MainFlag=0;
	}
}

void GameKeyConfig(){
	if (MainFlag % 50 == 0){
		if ((Key.Check(KC_DOWN) == 1 || (Key.Check(KC_DOWN) > 14 && Key.Check(KC_DOWN) % 3 == 0))){
			SelectOption = (SelectOption + 18) % 17;
			SoundEffect.RaiseFlag(18);
		}
		else if ((Key.Check(KC_UP) == 1 || (Key.Check(KC_UP) > 14 && Key.Check(KC_UP) % 3 == 0))){
			SelectOption = (SelectOption + 16) % 17;
			SoundEffect.RaiseFlag(18);
		}
		else if ((Key.Check(KC_LEFT) == 1 || (Key.Check(KC_LEFT) > 14 && Key.Check(KC_LEFT) % 3 == 0))){
			if (SelectOption == 16){
				SelectOption = 7;
			}
			else {
				SelectOption = (SelectOption + 8) % 16;
			}
			SoundEffect.RaiseFlag(18);
		}
		else if ((Key.Check(KC_RIGHT) == 1 || (Key.Check(KC_RIGHT) > 14 && Key.Check(KC_RIGHT) % 3 == 0))){
			if (SelectOption == 16){
				SelectOption = 15;
			}
			else {
				SelectOption = (SelectOption + 24) % 16;
			}
			SoundEffect.RaiseFlag(18);
		}
		else if (Key.Check(KC_DECIDE) == 1){
			SoundEffect.RaiseFlag(20);
			if (SelectOption <= 14){
				if (SelectPage == 0 || GetJoypadNum() > 0){
					MainFlag = 500 + SelectPage * 50 + SelectOption + 1;
				}
			}
			else if (SelectOption == 15){
				MainFlag = 300;
				SelectPage = 0;
				SelectOption = 4;
				SelectingFlag = 0;
				MainFlag = MainFlag / 100 * 100 + SelectPage * 10 + SelectOption;
			}
			else if (SelectOption == 16){
				if (MainFlag % 100 < 50){
					Key.ResetKey();
				}
				else {
					Key.ResetPad();
				}
			}
		}
		else if (Key.Check(KC_CANCEL) == 1){
			SoundEffect.RaiseFlag(19);
			MainFlag = 300;
			SelectPage = 0;
			SelectOption = 4;
			SelectingFlag = 0;
			MainFlag = MainFlag / 100 * 100 + SelectPage * 10 + SelectOption;
		}
	}
	else {
		if (SelectPage == 0){
			if (Key.SetAnyKey(MainFlag % 50 - 1) >= 0){
				SoundEffect.RaiseFlag(20);
				MainFlag = 500 + SelectPage * 50;
			}
		}
		else {
			if (GetJoypadNum() == 0){
				SoundEffect.RaiseFlag(19);
				MainFlag = 500 + SelectPage * 50;
			}
			if (Key.SetAnyPad(MainFlag % 50 - 1) >= 0){
				SoundEffect.RaiseFlag(20);
				MainFlag = 500 + SelectPage * 50;
			}
		}
	}
}

int GamePause(){
	if(MainPauseFlag==1){
		SoundEffect.RaiseFlag(20);
		MainPauseFlag=2;
	}
	if(MainPauseFlag<5){
		if(Key.Check(KC_UP)==1){
			MainPauseFlag=MainPauseFlag%3+2;
			SoundEffect.RaiseFlag(18);
		}
		else if(Key.Check(KC_DOWN)==1){
			MainPauseFlag=(MainPauseFlag+2)%3+2;
			SoundEffect.RaiseFlag(18);
		}
		else if(Key.Check(KC_DECIDE)==1){
			SoundEffect.RaiseFlag(20);
			Save.SaveCourse();
			if(MainPauseFlag==2){
				if(MainFlag/10==22||MainFlag/10==23)MainPauseFlag=0;
				else MainPauseFlag=60;
			}
			else if(MainPauseFlag==3){
				Bgm.Stop();
				Progress.LevelMax=LoadCourse(FLDN_FileName,-1);
				Progress.Level=SelectLevel;
				GameInitialize();
				GameStartRemainCount=180;
				StartingSet();
				StartNext();
				MainFlag=100;
			}
			else if(MainPauseFlag==4){
				MainFlag=0;
			}
		}
	}
	if(MainPauseFlag>59){
		MainPauseFlag++;
		if(MainPauseFlag>240){
			MainPauseFlag=0;
		}
	}
	return 1;
}
