#include <DxLib.h>
#include <bgm/bgm.h>
#include <display/display.h>
#include <drop/drop.h>
#include <fps/fps.h>
#include <game_play/game_play.h>
#include <key/key.h>
#include <load/load.h>
#include <macro_function.h>
#include <main.h>
#include <menu/menu.h>
#include <sound_effect/sound_effect.h>
#include <save/save.h>
#include <speed/speed.h>
#include <voice/voice.h>

Explode_t Explode[20][10];
Flash_t Flash[FLASH_MAX];
Progress_t Progress;
RandomNumber_t RandomNumber;
Scores_t Scores;
Tetrimino_t Tetrimino;
NewRecord_t NewRecord;

int ClearLineBase = 0;
int ClearRow[8] = {0};
int LevelStartClock = 0;
int Field[60][30] = {0};
int LoadFieldFlag = 0;
int PastClearLines = 0;
int QuakeX = 0,QuakeY = 0,QuakeTargetX = 0,QuakeTargetY = 0;
int SpentIfFlag[LEVEL_MAX] = {0};
int SoftLand = 0;
int MoveInfinity = 0,TurnInfinity = 0;
int MoveFlag = 0,TurnFlag = 0;
int IrregularRand[7] = {0};
int JustBeforeX=0,JustBeforeY=0,JustBeforeType = 0;
int ClearFieldTime = 0;
int GameClearFlag = 0;
int GameOverWaitTime = 0;
int WarnTime = 0,WarnFlag = 0;
int RemainLDT = 0,RemainLCT = 0,RemainARE = 0;
int LevelUpWaitRemain = 0;
int DropWait = 0,PressTime = 0;
int ExchangeState[10] = {0},ExchangeRand[10] = {0};
int TSpiningFlag = 0,TSpinMiniFlag = 0,BtBingFlag = 0,AfterEmerge = 0,AfterLevelUp = 0;
int NowRen_Keep = 0;
int AfterHold = 0;
int LevelDisplayTimeRemain = 0;
int WordFlag = 0,WordRemainCount = 0,GetLineClearPoint = 0,GetLineClearScore = 0;
int TimeLeftBonusTime = 0,TimeLeftGetScore = 0;
int CopyGarbageTime = 0,RandomGarbageTime = 0;
int BlockOldness[20][10] = {0};
int InvisibleBlock[20][10] = {0};
int NowLiftPressure = 0;
int AlternateHideState = 0;
int ObstacleFlag[30] = {0};
int MoveAtodashiFlag = 0;
int CascadingFlag = 0;
int TempCascade = 0;
int TempLevelup = 0;
double CascadeGage = 0.0;
int CascadeNext = 0;
int PlayStartLevel = 0;
int IRSFlag = 0;

void Swap(int *x, int *y){
	int temp = *x;
	*x = *y;
	*y = temp;
}

void FieldInitialize(){
	memset(Field,0,sizeof(Field));
	for(int i=0;i<60;i++){
		for(int j=0;j<10;j++)Field[i][j]=-1;
		for(int j=20;j<30;j++)Field[i][j]=-1;
	}
	for(int i=51;i<60;i++)for(int j=10;j<20;j++)Field[i][j]=-1;
}

int BoardToValue(int BoardNum){
	switch (BoardNum){
	case 0:return Progress.Level;
	case 1:return Progress.Point;
	case 2:return Scenario[Progress.Level].PointMax;
	case 3:return Scenario[Progress.Level].TargetTime;
	case 4:return Scores.Leftover;
	case 5:return Progress.LTime;
	case 6:return Progress.TTime;
	case 7:return Scenario[Progress.Level].ObstacleTime;
	case 8:return Scores.Score;
	case 9:return Save.ReadCourse(Save.BEST_SCORE);
	case 10:return Scores.LTetriminos;
	case 11:return Scores.TTetriminos;
	case 12:return Scores.LLines;
	case 13:return Scores.TLines;
	case 14:return Scores.Tmin;
	case 15:return Scores.Lmin;
	case 16:return Scores.LTetris;
	case 17:return Scores.TTetris;
	case 18:return Scores.LBacktoBack;
	case 19:return Scores.TBacktoBack;
	case 20:return Scores.LTSpin;
	case 21:return Scores.TTSpin;
	case 22:return Scores.LRens;
	case 23:return Scores.TRens;
	case 24:return Scenario[Progress.Level].Numerator;
	case 25:return Scenario[Progress.Level].Denominator;
	case 26:return Scenario[Progress.Level].LDT;
	case 27:return Scenario[Progress.Level].LCT;
	case 28:return Scenario[Progress.Level].ARE;
	case 29:return Scenario[Progress.Level].DAS;
	case 30:return Progress.Rank;
	case 31:return (int)((double)Scores.Score / (double)Progress.ClearBaseScore * 1000000.0);
	case 32:return (int)((double)Progress.TTime / (double)Progress.ClearBaseTime * 1000000.0);
	case 33:return Scores.LMaxRen;
	case 34:return Scores.TMaxRen;
	case 35:return RandomNumber.Game;
	case 36:return RandomNumber.Level;
	case 37:return RandomNumber.Line;
	case 38:return RandomNumber.Tetrimino;
	case 39:return RandomNumber.Frame;
	default:return -1;
	}
}

int JudgeBySign(int Num1,int Num2,int Sign){
	switch(Sign){
		case 0 :return Num1<Num2;
		case 1 :return Num1<=Num2;
		case 2 :return Num1>Num2;
		case 3 :return Num1>=Num2;
		case 4 :return Num1==Num2;
		case 5 :return Num1!=Num2;
	}
	return 0;
}

int CalcRank(int Board,int Sign){
	int rank=-1;
	if(Board>=0&&Board<BOARD_MAX&&Sign>=0&&Sign<SIGN_MAX){
		rank=0;
		for(int i=Course.RankMax;i>0;i--){
			if(JudgeBySign(Course.RankBase[i],BoardToValue(Board),Sign)){
				rank=i;
				i=0;
			}
		}
	}
	return rank;
}

void NextLevel(int UpLevel){
	int pastlevel = Progress.Level;
	if (Scenario[Progress.Level].TargetTime >= Progress.LTime && Scenario[Progress.Level].TargetTime > 0){
		Scores.Leftover += (Scenario[Progress.Level].TargetTime - Progress.LTime);
		if (Save.ReadSystem(Save.CASCADE)){
			CascadeGage += 24.0 * Scenario[Progress.Level].CascadeRate / 100.0;
		}
		else {
			CascadeGage = 0.0;
		}
	}
	if (Scenario[Progress.Level].PointMax >= 0 && Scenario[Progress.Level].TargetTime > 0 && Progress.LTime > 0){
		int scorebonus;
		double rate = (double)Scenario[Progress.Level].TargetTime / (double)Progress.LTime;
		if (rate > 10.0){
			rate = 10.0;
		}
		scorebonus = (int)(Scenario[Progress.Level].ScoreBase * Scenario[Progress.Level].PointMax * rate);
		if (scorebonus > 0){
			TimeLeftBonusTime = 120;
			TimeLeftGetScore = scorebonus;
			Scores.Score += scorebonus;
		}
	}
	memset(InvisibleBlock, 0, sizeof(InvisibleBlock));
	if (Progress.Level + UpLevel <= Progress.LevelMax){
		LevelUpWaitRemain = Scenario[Progress.Level].LevelUpWaitTime;
		Progress.Point -= Scenario[Progress.Level].PointMax;
		if (Progress.Point<0)Progress.Point = 0;
		Progress.Level += UpLevel;
		LevelStartClock = GetNowCount();
		GraphicInfo.MaskLevel = Progress.Level;
		if (Scenario[Progress.Level - 1].BackBlackNum != Scenario[Progress.Level].BackBlackNum || Scenario[Progress.Level - 1].BackWhiteNum != Scenario[Progress.Level].BackWhiteNum || Scenario[Progress.Level - 1].BackMaskNum != Scenario[Progress.Level].BackMaskNum){
			LoadBackGraphic(0);
		}
		if (Course.PlayingRank){
			Progress.Rank = CalcRank(Course.RankBoard, Course.RankSign);
		}
		if (Progress.Rank>Save.ReadCourse(Save.BEST_RANK) && Course.RecMaxRank){
			Save.WriteCourse(Save.BEST_RANK, Progress.Rank);
			NewRecord.Rank = 1;
		}
		Progress.DisplayPoint = Scenario[Progress.Level].PointMax;
		Bgm.Play(Course.BgmPath[Scenario[Progress.Level].BgmFlag], Course.BgmVolume[Scenario[Progress.Level].BgmFlag] * Save.ReadSystem(Save.BGM_VOLUME) / 100, Course.BgmLoopPoint[Scenario[Progress.Level].BgmFlag]);
		Scores.LTetriminos = 0;
		Scores.LLines = 0;
		Scores.LTetris = 0;
		Scores.LBacktoBack = 0;
		Scores.LTSpin = 0;
		Scores.LMaxRen = 0;
		Scores.LRens = 0;
		Progress.LTime = 0;
		RandomNumber.Level = GetRand(9999);
		AfterLevelUp = 1;
		WarnTime = 0;
		LoadFieldFlag = 0;
		LevelDisplayTimeRemain = 100;
		memset(SpentIfFlag, 0, sizeof(SpentIfFlag));
		for (int i = 0; i < OBSTACLE_MAX; i++){
			if ((Scenario[Progress.Level].ObstacleFlag[i] && Progress.LTime >= Scenario[Progress.Level].ObstacleTime) || Scenario[Progress.Level].FirstObstacle[i] || Course.NaturalObstacle[i]){
				ObstacleFlag[i] = 1;
			}
			else {
				ObstacleFlag[i] = 0;
			}
		}
		if (Scenario[Progress.Level].ObstacleTime == 0){
			WarnFlag = 3;
		}
		else WarnFlag = 0;
		if (!ObstacleFlag[OBS_QUAKE]){
			QuakeX = 0;
			QuakeY = 0;
			QuakeTargetX = 0;
			QuakeTargetY = 0;
		}
		CopyGarbageTime = Scenario[Progress.Level].CopyGarbage[1];
		RandomGarbageTime = Scenario[Progress.Level].RandomGarbage[1];
		if (Progress.Level > Save.ReadCourse(Save.BEST_LEVEL) && Course.RecMaxLevel){
			Save.WriteCourse(Save.BEST_LEVEL, Progress.Level);
			NewRecord.Level = 1;
			if (Course.RecMaxPoint){
				Save.WriteCourse(Save.BEST_POINT, Progress.Point);
				NewRecord.Point = 1;
			}
		}
		SoundEffect.RaiseFlag(17);
	}
	else {
		GameClearFlag = 1;
	}
	if (Course.HighestScore){
		if (Scores.Score > Save.ReadCourse(Save.BEST_SCORE)){
			Save.WriteCourse(Save.BEST_SCORE, Scores.Score);
			NewRecord.Score = 1;
		}
	}
	Save.SaveCourse();
	Save.SaveSystem();
}

int LineScorePoint(int seemingly_lines){
	int lines, word, position, sum, sum_rest = 0, nextflag = 0, beneath = 0, firstpoint = Progress.Point, firstscore = Scores.Score;
	int TetriminoSize = ObstacleFlag[OBS_BIG] + 1;
	lines = seemingly_lines / TetriminoSize;
	if (lines > 4)lines = 4;
	TSpinMiniFlag = (TSpinMiniFlag&&lines == 1);
	if (Scenario[Progress.Level].CopyGarbage[0] == 1)CopyGarbageTime--;
	if (Scenario[Progress.Level].RandomGarbage[0] == 1)RandomGarbageTime--;
	for (int i = 3; i > 0; i--){
		for (int j = 0; j < 4; j++){
			if (Course.Shape[Scenario[Progress.Level].ShapeFlag][Tetrimino.Type][Tetrimino.Side][i][j]){ beneath = i; i = 0; j = 4; }
		}
	}
	if (TSpiningFlag){
		Scores.TTSpin++;
		Scores.LTSpin++;
		if (Save.ReadSystem(Save.CASCADE)){
			CascadeGage += 7.5 * Scenario[Progress.Level].CascadeRate / 100.0;
		}
		else {
			CascadeGage = 0.0;
		}
		Save.WriteSystem(Save.TOTALS_TSPIN + Progress.Mode * 6, Save.ReadSystem(Save.TOTALS_TSPIN + Progress.Mode * 6) + 1);
	}
	PastClearLines = lines;
	if (lines){
		SoundEffect.RaiseFlag(10 + lines);
		if (Scenario[Progress.Level].CopyGarbage[0] == 1){
			CopyGarbageTime += lines;
			if (CopyGarbageTime > Scenario[Progress.Level].CopyGarbage[1]){
				CopyGarbageTime = Scenario[Progress.Level].CopyGarbage[1];
			}
		}
		if (Scenario[Progress.Level].RandomGarbage[0] == 1){
			RandomGarbageTime += lines;
			if (RandomGarbageTime > Scenario[Progress.Level].RandomGarbage[1]){
				RandomGarbageTime = Scenario[Progress.Level].RandomGarbage[1];
			}
		}
		Scores.TLines += lines;
		Scores.LLines += lines;
		RandomNumber.Line = GetRand(9999);
		Save.WriteSystem(Save.TOTALS_LINE + Progress.Mode * 6, Save.ReadSystem(Save.TOTALS_LINE + Progress.Mode * 6) + lines);
		if (lines == 4){
			Scores.TTetris++;
			Scores.LTetris++;
			if (Save.ReadSystem(Save.CASCADE)){
				CascadeGage += 15.0 * Scenario[Progress.Level].CascadeRate / 100.0;
			}
			else {
				CascadeGage = 0.0;
			}
			Save.WriteSystem(Save.TOTALS_TETRIS + Progress.Mode * 6, Save.ReadSystem(Save.TOTALS_TETRIS + Progress.Mode * 6) + 1);
		}
		if (TSpiningFlag || lines == 4)BtBingFlag++;
		else BtBingFlag = 0;
		if (BtBingFlag > 1){
			Scores.TBacktoBack++;
			Scores.LBacktoBack++;
			if (Save.ReadSystem(Save.CASCADE)){
				CascadeGage += 7.5 * Scenario[Progress.Level].CascadeRate / 100.0;
			}
			else {
				CascadeGage = 0.0;
			}
			Save.WriteSystem(Save.TOTALS_BTB + Progress.Mode * 6, Save.ReadSystem(Save.TOTALS_BTB + Progress.Mode * 6) + 1);
		}
		NowRen_Keep++;
		if (NowRen_Keep > 1){
			Scores.TRens++;
			Scores.LRens++;
			if (Save.ReadSystem(Save.CASCADE)){
				CascadeGage += 2.5 * Scenario[Progress.Level].CascadeRate / 100.0;
			}
			else {
				CascadeGage = 0.0;
			}
			Save.WriteSystem(Save.TOTALS_REN + Progress.Mode * 6, Save.ReadSystem(Save.TOTALS_REN + Progress.Mode * 6) + 1);
			if (Scores.TMaxRen < NowRen_Keep - 1)Scores.TMaxRen = NowRen_Keep - 1;
			if (Scores.LMaxRen < NowRen_Keep - 1)Scores.LMaxRen = NowRen_Keep - 1;
			SoundEffect.RaiseFlag(SoundEffect.REN_START + NowRen_Keep - 2);
		}
		for (int i = 0; i<lines; i++){
			Line_Speed.Record(Progress.TTime);
		}
	}
	else {
		NowRen_Keep = 0;
	}
	position = lines;
	if (BtBingFlag>1 && lines > 0)position += 10;
	else if (TSpiningFlag)position += 6;
	if ((TSpinMiniFlag) || (TSpiningFlag&&lines == 0))position -= 1;
	position -= 2;
	if (position >= 0 && position<Voice.MAX)Voice.RaiseFlag(position);

	sum = Scenario[Progress.Level].LineClearPoint[lines];
	if (BtBingFlag>1 && lines > 0)sum += Scenario[Progress.Level].BacktoBackPoint[lines - 1];
	if (TSpiningFlag&&lines == 0)sum += Scenario[Progress.Level].TSpinPoint[0];
	else if (TSpinMiniFlag)sum += Scenario[Progress.Level].TSpinPoint[1];
	else if (TSpiningFlag&&lines > 0 && lines<4)sum += Scenario[Progress.Level].TSpinPoint[1 + lines];
	if (NowRen_Keep>1 && lines > 0)sum += Scenario[Progress.Level].RenPoint[lines - 1];

	if (Progress.Point + sum >= Scenario[Progress.Level].PointMax&&Scenario[Progress.Level].PointMax >= 0){
		if (Scenario[Progress.Level].Condition[lines] == 0)sum = Scenario[Progress.Level].PointMax - Progress.Point - 1;
		else {
			nextflag = 1;
			if (Progress.Level < Progress.LevelMax){
				sum_rest = Progress.Point + sum - Scenario[Progress.Level].PointMax;
				Scores.Score += sum_rest*Scenario[Progress.Level + 1].ScoreBase;
			}
			else sum_rest = 0;
			sum = Scenario[Progress.Level].PointMax - Progress.Point;
			Progress.Point += sum_rest;
		}
	}
	Progress.Point += sum;
	Scores.Score += sum * Scenario[Progress.Level].ScoreBase;
	if (Progress.Point<0){
		Progress.Point = 0;
	}
	if (Course.PlayingRank){
		Progress.Rank = CalcRank(Course.RankBoard, Course.RankSign);
	}
	if (Progress.Rank>Save.ReadCourse(Save.BEST_RANK) && Course.RecMaxRank){
		Save.WriteCourse(Save.BEST_RANK, Progress.Rank);
		NewRecord.Rank = 1;
	}
	if (Progress.Level == Save.ReadCourse(Save.BEST_LEVEL) && Progress.Point > Save.ReadCourse(Save.BEST_POINT) && Course.RecMaxPoint){
		Save.WriteCourse(Save.BEST_POINT, Progress.Point);
		NewRecord.Point = 1;
	}
	if (Scores.Score > Save.ReadCourse(Save.BEST_SCORE)){
		Save.WriteCourse(Save.BEST_SCORE, Scores.Score);
		NewRecord.Score = 1;
	}
	word = lines + (BtBingFlag > 1 && lines) * 8 + TSpiningFlag * 16 + TSpinMiniFlag * 32 + (NowRen_Keep > 1) * 64;
	if (word > 0){
		WordFlag = word;
		WordRemainCount = 120;
		GetLineClearPoint = Progress.Point - firstpoint;
		GetLineClearScore = Scores.Score - firstscore;
		EnterAddPoint(Tetrimino.X - FIELD_X, Tetrimino.Y - FIELD_Y, GetLineClearPoint);
		if (TimeLeftBonusTime < 120)TimeLeftBonusTime = 0;
	}
	if (nextflag)NextLevel(1);
	return seemingly_lines;
}

void QuakeField(){
	if(ObstacleFlag[OBS_QUAKE]&&Scenario[Progress.Level].Quake[0]){
		if(Progress.TTime%Scenario[Progress.Level].Quake[0]==0){
			int cq3=0,cq4=0,cq7=0,cq8=0;
			if(Scenario[Progress.Level].Quake[3]!=0)cq3=Progress.TTime%Scenario[Progress.Level].Quake[3];
			if(Scenario[Progress.Level].Quake[4]!=0)cq4=Progress.TTime%Scenario[Progress.Level].Quake[4];
			if(Scenario[Progress.Level].Quake[7]!=0)cq7=Progress.TTime%Scenario[Progress.Level].Quake[7];
			if(Scenario[Progress.Level].Quake[8]!=0)cq8=Progress.TTime%Scenario[Progress.Level].Quake[8];
			if(Scenario[Progress.Level].Quake[5]!=0)QuakeTargetX=(Scenario[Progress.Level].Quake[2]+cq3+cq4)*Scenario[Progress.Level].Quake[1]/32*(Progress.TTime/(Scenario[Progress.Level].Quake[0]*Scenario[Progress.Level].Quake[5])%2*2-1);
			if(Scenario[Progress.Level].Quake[9]!=0)QuakeTargetY=(Scenario[Progress.Level].Quake[6]+cq7+cq8)*Scenario[Progress.Level].Quake[1]/32*(Progress.TTime/(Scenario[Progress.Level].Quake[0]*Scenario[Progress.Level].Quake[9])%2*2-1);
		}
		QuakeX+=((QuakeTargetX-QuakeX)/(Scenario[Progress.Level].Quake[0]-(Progress.TTime%Scenario[Progress.Level].Quake[0])));
		QuakeY+=((QuakeTargetY-QuakeY)/(Scenario[Progress.Level].Quake[0]-(Progress.TTime%Scenario[Progress.Level].Quake[0])));
	}
	else {
		QuakeX=0;
		QuakeY=0;
	}
}

void StartNext(){
	SRand(GetNowCount());
	for(int i=0;i<7;i++)Tetrimino.Next[i]=i;
	for(int i=0;i<10;i++)ExchangeRand[i]=0;
	for(int i=6;i>0;i--)Swap(&Tetrimino.Next[i],&Tetrimino.Next[GetRand(i)]);
	if(!Course.FirstTetrimino[Tetrimino.Next[0]]){
		for(int i=1;i<7;i++){
			if(Course.FirstTetrimino[Tetrimino.Next[i]]){Swap(&Tetrimino.Next[0],&Tetrimino.Next[i]);i=7;}
		}
	}
	for(int i=0;i<10;i++){
		if(Course.ExchangeTetrimino[i][0]){
			ExchangeRand[i]=0;
			ExchangeState[i]=1;
			for(int j=0;j<7;j++){
				if(Tetrimino.Next[j]==Course.ExchangeTetrimino[i][1])j=7;
				else if(Tetrimino.Next[j]==Course.ExchangeTetrimino[i][2]){ExchangeState[i]=2;j=7;}
			}
		}
	}		
}

void PermNext(){
	for(int i=0;i<7;i++)Tetrimino.Next[i+7]=i;
	for(int i=6;i>0;i--)Swap(&Tetrimino.Next[i+7],&Tetrimino.Next[GetRand(i)+7]);
	for(int i=0;i<10;i++){
		if(Course.ExchangeTetrimino[i][0]){
			ExchangeRand[i]+=(Course.ExchangeTetrimino[i][4]+GetRand(Course.ExchangeTetrimino[i][5]));
			if(ExchangeRand[i]>=Course.ExchangeTetrimino[i][3]){
				if(ExchangeState[i]==1)ExchangeState[i]=2;
				else ExchangeState[i]=1;
				ExchangeRand[i]=0;
			}
			for(int j=7;j<14;j++){
				if(Tetrimino.Next[j]==Course.ExchangeTetrimino[i][1]||Tetrimino.Next[j]==Course.ExchangeTetrimino[i][2]){
					if(Tetrimino.Next[j]!=Course.ExchangeTetrimino[i][ExchangeState[i]]){
						for(int k=j+1;k<14;k++){
							if(Tetrimino.Next[k]==Course.ExchangeTetrimino[i][ExchangeState[i]]){Swap(&Tetrimino.Next[j],&Tetrimino.Next[k]);k=14;}
						}
					}
					j=14;
				}
			}
		}
	}
}

int GameOverJudge(int minotype,int minoside,int x,int y,int garbage){
	int GameOver=0,TetriminoSize=ObstacleFlag[OBS_BIG]+1;
	for(int i=0;i<4&&!GameOver;i++){
		for(int j=0;j<4&&!GameOver;j++){
			GameOver=Field[y+(i+garbage)*TetriminoSize][x+j*TetriminoSize]&&Course.Shape[Scenario[Progress.Level].ShapeFlag][minotype][minoside][i][j];
		}
	}
	return GameOver;
}

int EmergeTetrimino(){
	int GameOver;
	Tetrimino.Side = (((Key.Check(KC_LTURN_1) || Key.Check(KC_LTURN_2)) && 1) * 3 + ((Key.Check(KC_RTURN_1) || Key.Check(KC_RTURN_2)) && 1)) % 4;
	if (ObstacleFlag[OBS_REVERSE] && Scenario[Progress.Level].Reverse[0]){
		if (Tetrimino.Side == 3)Tetrimino.Side = 1;
		else if (Tetrimino.Side == 1)Tetrimino.Side = 3;
	}
	if (ObstacleFlag[OBS_BIG]){
		Tetrimino.X = FIELD_X + Scenario[Progress.Level].EmergePos[Tetrimino.Type][2];
		Tetrimino.Y = FIELD_Y + Scenario[Progress.Level].EmergePos[Tetrimino.Type][3];
	}
	else {
		Tetrimino.X = FIELD_X + Scenario[Progress.Level].EmergePos[Tetrimino.Type][0];
		Tetrimino.Y = FIELD_Y + Scenario[Progress.Level].EmergePos[Tetrimino.Type][1];
	}
	DropWait = Scenario[Progress.Level].Denominator;
	RemainLDT = Scenario[Progress.Level].LDT;
	RemainLCT = Scenario[Progress.Level].LCT;
	RemainARE = Scenario[Progress.Level].ARE;
	if (ObstacleFlag[OBS_BOOST] && Tetrimino.Y + Course.ShapeBoostPos[Scenario[Progress.Level].ShapeFlag][Tetrimino.Type][Tetrimino.Side] >= FIELD_Y + Scenario[Progress.Level].Boost[0]){
		if (Scenario[Progress.Level].Boost[2] >= 0)DropWait = Scenario[Progress.Level].Boost[2];
		if (Scenario[Progress.Level].Boost[3] >= 0)RemainLDT = Scenario[Progress.Level].Boost[3];
	}
	TSpiningFlag = 0;
	if (!ObstacleFlag[OBS_NH] && AfterHold > 1)AfterHold = 1;
	if (AfterHold > 0)AfterHold--;
	SoftLand = 0;
	MoveFlag = 0;
	TurnFlag = 0;
	MoveAtodashiFlag = 0;
	MoveInfinity = 0;
	TurnInfinity = 0;
	CascadingFlag = 0;
	TempCascade = 0;
	GameOver = GameOverJudge(Tetrimino.Type, Tetrimino.Side, Tetrimino.X, Tetrimino.Y, 0);
	if (GameOver == 1 && Tetrimino.Side > 0){
		Tetrimino.Side = 0;
		GameOver = GameOverJudge(Tetrimino.Type, 0, Tetrimino.X, Tetrimino.Y, 0);
	}
	if (Tetrimino.Side != 0){
		IRSFlag = 1;
	}
	else {
		IRSFlag = 0;
	}
	return !GameOver;
}

void StuffNext(){
	for(int i=0;i<13;i++){
		Tetrimino.Next[i]=Tetrimino.Next[i+1];
	}
	if (CascadeNext > 0){
		CascadeNext -= 1;
	}
	if (CascadeGage > 200.0){
		CascadeGage = 200.0;
	}
	if (Save.ReadSystem(Save.CASCADE)){
		if (CascadeGage >= 100.0 && CascadeNext <= 0){
			CascadeNext = 4;
			CascadeGage -= 100.0;
			SoundEffect.RaiseFlag(25);
		}
	}
	else {
		CascadeGage = 0.0;
	}
}

int GhostBlock(){
	int Drop,NG=0,TetriminoSize=ObstacleFlag[OBS_BIG]+1;
	for(Drop=0;Drop<20&&!NG;Drop++){
		for(int i=0;i<4&&!NG;i++){
			for(int j=0;j<4&&!NG;j++){
				NG=Field[Tetrimino.Y+i*TetriminoSize+Drop+TetriminoSize][Tetrimino.X+j*TetriminoSize]&&Course.Shape[Scenario[Progress.Level].ShapeFlag][Tetrimino.Type][Tetrimino.Side][i][j];
			}
		}
	}
	return Drop-1;
}

int HoldTetrimino(){
	int GameOver=0,siding,x,y;
	int nh=ObstacleFlag[OBS_NH];
	if(AfterHold>0||(nh&&Scenario[Progress.Level].NoHold[0]<0)){
		SoundEffect.RaiseFlag(9);
	}
	else {
		siding=(((Key.Check(KC_LTURN_1)||Key.Check(KC_LTURN_2))&&1)*3+((Key.Check(KC_RTURN_1)||Key.Check(KC_RTURN_2))&&1))%4;
		if(ObstacleFlag[OBS_REVERSE]&&Scenario[Progress.Level].Reverse[0]){
			if(siding==3)siding=1;
			else if(siding==1)siding=3;
		}
		if(Tetrimino.Hold==-1){
			if(ObstacleFlag[OBS_BIG]){
				x=FIELD_X+Scenario[Progress.Level].EmergePos[Tetrimino.Next[0]][2];
				y=FIELD_Y+Scenario[Progress.Level].EmergePos[Tetrimino.Next[0]][3];
			}
			else {
				x=FIELD_X+Scenario[Progress.Level].EmergePos[Tetrimino.Next[0]][0];
				y=FIELD_Y+Scenario[Progress.Level].EmergePos[Tetrimino.Next[0]][1];
			}
			GameOver=GameOverJudge(Tetrimino.Next[0],siding,x,y,0);
			if(GameOver&&siding)GameOver=GameOverJudge(Tetrimino.Next[0],0,x,y,0);
			if(!GameOver){
				Tetrimino.Hold=Tetrimino.Type;
				if(Scores.TTetriminos%7==0)PermNext();
				Tetrimino.Type=Tetrimino.Next[0];
				Scores.TTetriminos++;
				Scores.LTetriminos++;
				RandomNumber.Tetrimino=GetRand(9999);
				if(ObstacleFlag[OBS_ALTHIDE]&&Scenario[Progress.Level].AlternateHide[0]){
					if(Scores.TTetriminos%Scenario[Progress.Level].AlternateHide[0]==0){
						if(AlternateHideState==0)AlternateHideState=1;
						else AlternateHideState=0;
					}
				}
				if (CascadeNext == 1){
					CascadeNext = 99999999;
				}
				StuffNext();
				SoundEffect.RaiseFlag(8);
				TSpiningFlag=0;
				EmergeTetrimino();
				if(nh){
					AfterHold=Scenario[Progress.Level].NoHold[0];
				}
				else {
					AfterHold=1;
				}
			}
			else {
				SoundEffect.RaiseFlag(9);
			}
		}
		else {
			if(ObstacleFlag[OBS_BIG]){
				x=FIELD_X+Scenario[Progress.Level].EmergePos[Tetrimino.Hold][2];
				y=FIELD_Y+Scenario[Progress.Level].EmergePos[Tetrimino.Hold][3];
			}
			else {
				x=FIELD_X+Scenario[Progress.Level].EmergePos[Tetrimino.Hold][0];
				y=FIELD_Y+Scenario[Progress.Level].EmergePos[Tetrimino.Hold][1];
			}
			GameOver=GameOverJudge(Tetrimino.Hold,siding,x,y,0);
			if(GameOver&&siding)GameOver=GameOverJudge(Tetrimino.Hold,0,x,y,0);
			if(!GameOver){
				Swap(&Tetrimino.Hold,&Tetrimino.Type);
				if (CascadeNext == 1){
					CascadeNext = 99999999;
				}
				else if (CascadeNext > 4){
					CascadeNext = 1;
				}
				SoundEffect.RaiseFlag(8);
				TSpiningFlag=0;
				EmergeTetrimino();
				if(nh){
					AfterHold=Scenario[Progress.Level].NoHold[0];
				}
				else {
					AfterHold=1;
				}
			}
			else {
				SoundEffect.RaiseFlag(9);
			}
		}
	}
	return !GameOver;
}

void ResetByDrop(){
	if(ObstacleFlag[OBS_BOOST]&&Tetrimino.Y+Course.ShapeBoostPos[Scenario[Progress.Level].ShapeFlag][Tetrimino.Type][Tetrimino.Side]>=FIELD_Y+Scenario[Progress.Level].Boost[0]){
		if(Scenario[Progress.Level].Boost[2]>=0){
			if(Scenario[Progress.Level].SmoothDrop)DropWait+=Scenario[Progress.Level].Boost[2];
			else DropWait=Scenario[Progress.Level].Boost[2];
		}
		else {
			if(Scenario[Progress.Level].SmoothDrop)DropWait+=Scenario[Progress.Level].Denominator;
			else DropWait=Scenario[Progress.Level].Denominator;
		}
		if(Scenario[Progress.Level].Boost[3]>=0)RemainLDT=Scenario[Progress.Level].Boost[3];
		else RemainLDT=Scenario[Progress.Level].LDT;
	}
	else {
		if(Scenario[Progress.Level].SmoothDrop)DropWait+=Scenario[Progress.Level].Denominator;
		else DropWait=Scenario[Progress.Level].Denominator;
		RemainLDT=Scenario[Progress.Level].LDT;
	}
	TSpiningFlag=PressTime=0;
}

int DropTetrimino(){
	int NG=0,TetriminoSize=ObstacleFlag[OBS_BIG]+1,YDistance=(ObstacleFlag[OBS_BIG]&&Scenario[Progress.Level].Big[0])+1;
	for(int i=0;i<4&&!NG;i++){
		for(int j=0;j<4&&!NG;j++){
			NG=Field[Tetrimino.Y+i*TetriminoSize+YDistance][Tetrimino.X+j*TetriminoSize]&&Course.Shape[Scenario[Progress.Level].ShapeFlag][Tetrimino.Type][Tetrimino.Side][i][j];
		}
	}
	if(!NG){
		Tetrimino.Y+=YDistance;
		ResetByDrop();
	}
	return !NG;
}

int MoveTetrimino(int LR){
	int NG=0,TetriminoSize=ObstacleFlag[OBS_BIG]+1;
	if(ObstacleFlag[OBS_BIG]&&Scenario[Progress.Level].Big[1])LR*=2;
	for(int i=0;i<4&&!NG;i++){
		for(int j=0;j<4&&!NG;j++){
			NG=Field[Tetrimino.Y+i*TetriminoSize][Tetrimino.X+j*TetriminoSize+LR]&&Course.Shape[Scenario[Progress.Level].ShapeFlag][Tetrimino.Type][Tetrimino.Side][i][j];
		}
	}
	if(!NG){
		TSpiningFlag=0;
		Tetrimino.X+=LR;
		return 1;
	}
	return 0;
}

int TurnTetrimino(int LR){
	int TurnedSide = 0, NG = 1, TetriminoSize = ObstacleFlag[OBS_BIG] + 1, YDistance = (ObstacleFlag[OBS_BIG] && Scenario[Progress.Level].Big[0]) + 1, XDistance = (ObstacleFlag[OBS_BIG] && Scenario[Progress.Level].Big[1]) + 1;
	if (IRSFlag == 0){
		if (ObstacleFlag[OBS_REVERSE] && Scenario[Progress.Level].Reverse[0])LR *= (-1);
		TurnedSide = (Tetrimino.Side + LR + 4) % 4;
		if (Scenario[Progress.Level].RotationType[Tetrimino.Type] & 1){
			NG = 0;
			for (int i = 0; i < 4 && !NG; i++){
				for (int j = 0; j < 4 && !NG; j++){
					NG = Field[Tetrimino.Y + i*TetriminoSize][Tetrimino.X + j*TetriminoSize] && Course.Shape[Scenario[Progress.Level].ShapeFlag][Tetrimino.Type][TurnedSide][i][j];
				}
			}
			if (!NG)Tetrimino.Side = TurnedSide;
		}
		if (NG&&Scenario[Progress.Level].RotationType[Tetrimino.Type] & 2){
			int OrderNum, Order[4][7] = { { 3, 2, 1, 0, 4, 5, 6 }, { 3, 4, 5, 6, 2, 1, 0 }, { 3, 2, 4, 1, 5, 0, 6 }, { 3, 4, 2, 5, 1, 6, 0 } };
			if ((Key.Check(KC_LEFT) >= Scenario[Progress.Level].DAS || Key.Check(KC_LEFT) == 1) && Key.Check(KC_RIGHT) == 0)OrderNum = 0;
			else if ((Key.Check(KC_RIGHT) >= Scenario[Progress.Level].DAS || Key.Check(KC_RIGHT) == 1) && Key.Check(KC_LEFT) == 0)OrderNum = 1;
			else if (LR <= 0)OrderNum = 2;
			else OrderNum = 3;
			for (int l = 0; l < 4 && NG; l++){
				int Dodge[7] = { 0 };
				for (int k = -3; k <= 3; k++){
					for (int i = 0; i < 4; i++){
						if (i + l <= 3){
							for (int j = 0; j < 4; j++){
								if (j + k >= 0 && j + k <= 3){
									if (Course.Shape[Scenario[Progress.Level].ShapeFlag][Tetrimino.Type][Tetrimino.Side][i + l][j + k] && Course.Shape[Scenario[Progress.Level].ShapeFlag][Tetrimino.Type][TurnedSide][i][j])Dodge[k + 3] = 1;
								}
							}
						}
					}
				}
				for (int k = -3; k <= 3; k++){
					for (int i = 0; i < 4 && Dodge[k + 3]; i++){
						for (int j = 0; j < 4 && Dodge[k + 3]; j++){
							if (Course.Shape[Scenario[Progress.Level].ShapeFlag][Tetrimino.Type][TurnedSide][i][j] && Field[Tetrimino.Y + i*TetriminoSize + l*YDistance][Tetrimino.X + j*TetriminoSize + k*XDistance])Dodge[k + 3] = 0;
						}
					}
				}
				for (int k = 0; k<7 && NG; k++){
					if (Dodge[Order[OrderNum][k]]){
						NG = 0;
						Tetrimino.Side = TurnedSide;
						Tetrimino.X += (Order[OrderNum][k] - 3)*XDistance;
						Tetrimino.Y += l*YDistance;
						if (l>0){
							ResetByDrop();
						}
					}
				}
			}
		}
		if (NG&&Scenario[Progress.Level].RotationType[Tetrimino.Type] & 4){
			int Priority, RotateNum = (LR + 1) * 2 + Tetrimino.Side;
			for (Priority = 0; Priority < 32 && NG; Priority += 2){
				NG = 0;
				for (int i = 0; i < 4 && !NG; i++){
					for (int j = 0; j<4 && !NG; j++){
						NG = Field[Tetrimino.Y + i*TetriminoSize + Course.Rotation[Scenario[Progress.Level].RotationFlag][Tetrimino.Type][RotateNum][Priority + 1] * YDistance][Tetrimino.X + j*TetriminoSize + Course.Rotation[Scenario[Progress.Level].RotationFlag][Tetrimino.Type][RotateNum][Priority] * XDistance] && Course.Shape[Scenario[Progress.Level].ShapeFlag][Tetrimino.Type][TurnedSide][i][j];
					}
				}
			}
			if (!NG){
				Priority -= 2;
				Tetrimino.Side = TurnedSide;
				Tetrimino.X += Course.Rotation[Scenario[Progress.Level].RotationFlag][Tetrimino.Type][RotateNum][Priority] * XDistance;
				Tetrimino.Y += Course.Rotation[Scenario[Progress.Level].RotationFlag][Tetrimino.Type][RotateNum][Priority + 1] * YDistance;
				if (Course.Rotation[Scenario[Progress.Level].RotationFlag][Tetrimino.Type][RotateNum][Priority + 1]>0){
					ResetByDrop();
				}
			}
		}
		if (Tetrimino.Type % 8 == Course.ShapeTSpinInfo[Scenario[Progress.Level].ShapeFlag][0] && Tetrimino.Side == TurnedSide){
			int tspin = 0;
			for (int i = 0; i < 4; i++)if (Field[Tetrimino.Y + Course.ShapeTSpinPoint[Scenario[Progress.Level].ShapeFlag][Tetrimino.Side][i][1] * TetriminoSize][Tetrimino.X + Course.ShapeTSpinPoint[Scenario[Progress.Level].ShapeFlag][Tetrimino.Side][i][0] * TetriminoSize])tspin++;
			if (tspin >= Course.ShapeTSpinInfo[Scenario[Progress.Level].ShapeFlag][1])TSpiningFlag = 1;
			else TSpiningFlag = 0;
			if (TSpiningFlag&&Course.ShapeTSpinInfo[Scenario[Progress.Level].ShapeFlag][2]){
				if (Field[Tetrimino.Y + Course.ShapeTSpinMini[Scenario[Progress.Level].ShapeFlag][Tetrimino.Side][1] * TetriminoSize][Tetrimino.X + Course.ShapeTSpinMini[Scenario[Progress.Level].ShapeFlag][Tetrimino.Side][0] * TetriminoSize])TSpinMiniFlag = 1;
			}
			else TSpinMiniFlag = 0;
		}
		else { TSpiningFlag = 0; TSpinMiniFlag = 0; }
	}
	else {
		IRSFlag = 0;
	}
	return Tetrimino.Side == TurnedSide;
}

int LockDown(){
	int lines=0,TetriminoSize=ObstacleFlag[OBS_BIG]+1,leftend=3,rightend=0;
	for(int i=0;i<4*TetriminoSize;i++){
		for(int j=0;j<4*TetriminoSize;j++){
			if(Course.Shape[Scenario[Progress.Level].ShapeFlag][Tetrimino.Type][Tetrimino.Side][i/TetriminoSize][j/TetriminoSize]){
				Field[Tetrimino.Y+i][Tetrimino.X+j]=Tetrimino.Type+1;
				if (CascadeNext == 1 && Course.Shape[Scenario[Progress.Level].ShapeFlag][Tetrimino.Type][Tetrimino.Side][i / TetriminoSize][j / TetriminoSize] == 2){
					Field[Tetrimino.Y + i][Tetrimino.X + j] += 8;
					CascadeNext = 0;
				}
				if(Tetrimino.Y+i-FIELD_Y>=0&&Tetrimino.Y+i-FIELD_Y<20&&Tetrimino.X+j-FIELD_X>=0&&Tetrimino.X+j-FIELD_X<20){
					BlockOldness[Tetrimino.Y+i-FIELD_Y][Tetrimino.X+j-FIELD_X]=0;
					if(ObstacleFlag[OBS_SUDDEN]){
						InvisibleBlock[Tetrimino.Y+i-FIELD_Y][Tetrimino.X+j-FIELD_X]=1;
					}
					else {
						InvisibleBlock[Tetrimino.Y+i-FIELD_Y][Tetrimino.X+j-FIELD_X]=0;
					}
					int RemainMin=0x7FFFFFFF,MinIndex=0;
					for(int FlashIndex=0;FlashIndex<MIN(Scenario[Progress.Level].FlashDrawMax,FLASH_MAX);FlashIndex++){
						if(Flash[FlashIndex].FlashRemain<RemainMin){MinIndex=FlashIndex;RemainMin=Flash[FlashIndex].FlashRemain;}
						if(Flash[FlashIndex].FlashRemain<=0)FlashIndex=FLASH_MAX;
					}
					Flash[MinIndex].X=Tetrimino.X+j-FIELD_X;
					Flash[MinIndex].Y=Tetrimino.Y+i-FIELD_Y;
					Flash[MinIndex].FlashRemain=Scenario[Progress.Level].FlashTime;
				}
			}
		}
	}
	for(int i=3;i>=0;i--){
		for(int j=0;j<3;j++)if(Course.Shape[Scenario[Progress.Level].ShapeFlag][Tetrimino.Type][Tetrimino.Side][i][j]){leftend=j;j=3;}
		for(int j=3;j>0;j--)if(Course.Shape[Scenario[Progress.Level].ShapeFlag][Tetrimino.Type][Tetrimino.Side][i][j]){rightend=j;j=0;}
		if(leftend<3||rightend>0){
			for(int ts=0;ts<TetriminoSize;ts++){
				int check;
				for(check=FIELD_X;check<FIELD_X+10&&Field[Tetrimino.Y+i*TetriminoSize+ts][check];check++);
				if(check==FIELD_X+10){
					for(int k=FIELD_X;k<FIELD_X+10;k++){
						Explode[Tetrimino.Y+i*TetriminoSize+ts-FIELD_Y][k-FIELD_X].ClearColor=(Field[Tetrimino.Y+i*TetriminoSize+ts][k]-1)%8;
						if(k>=Tetrimino.X+leftend&&k<=Tetrimino.X+rightend)Explode[Tetrimino.Y+i*TetriminoSize+ts-FIELD_Y][k-FIELD_X].ClearRemain=10;
						else if(k<Tetrimino.X+leftend)Explode[Tetrimino.Y+i*TetriminoSize+ts-FIELD_Y][k-FIELD_X].ClearRemain=10+((Tetrimino.X+leftend)-k+1)/2;
						else if(k>Tetrimino.X+rightend)Explode[Tetrimino.Y+i*TetriminoSize+ts-FIELD_Y][k-FIELD_X].ClearRemain=10+(k-(Tetrimino.X+rightend)+1)/2;
						else Explode[Tetrimino.Y+i*TetriminoSize+ts-FIELD_Y][k-FIELD_X].ClearRemain=10;
					}
					ClearRow[lines++]=Tetrimino.Y+i*TetriminoSize+ts;
				}
			}
		}
	}
	JustBeforeX=Tetrimino.X;
	JustBeforeY=Tetrimino.Y;
	JustBeforeType=Tetrimino.Type;
	SoundEffect.RaiseFlag(7);
	if (Save.ReadSystem(Save.CASCADE)){
		CascadeGage += 1.0 * Scenario[Progress.Level].CascadeRate / 100.0;
	}
	else {
		CascadeGage = 0.0;
	}
	return lines;
}

int ClearLine(int lines){
	ClearLineBase = 0;
	for (int i = 0; i < lines; i++){
		ClearLineBase = MAX(ClearLineBase, ClearRow[i]);
		for (int j = FIELD_X; j < FIELD_X + 10; j++){
			if (Field[ClearRow[i]][j] >= 9 && Field[ClearRow[i]][j] <= 16){
				TempCascade = 1;
			}
			if (Field[ClearRow[i]][j] >= 17 && Field[ClearRow[i]][j] <= 24){
				TempLevelup = 1;
			}
			Field[ClearRow[i]][j] = 0;
		}
	}
	return lines;
}

void StuffLine(int n){
	int lines = 0;
	int TetriminoSize = (ObstacleFlag[OBS_BIG] && 1) + 1;
	int pcl = PastClearLines;
	if (pcl > 4){
		pcl = 4;
	}
	memset(ClearRow, -1, sizeof(ClearRow));
	if (ObstacleFlag[OBS_ZEROG] && n < Scenario[Progress.Level].ZeroGravity[0] && (Scenario[Progress.Level].ZeroGravity[0] == 0 || CascadingFlag == 0) && TempCascade == 0){

	}
	else if ((ObstacleFlag[OBS_CASCADE] && pcl > 0 && Scenario[Progress.Level].Cascade[pcl - 1] > -100) || TempCascade != 0){
		
		int base = ClearLineBase + Scenario[Progress.Level].Cascade[pcl - 1];
		if (base > FIELD_Y + 19){
			base = FIELD_Y + 19;
		}
		for (int j = FIELD_X; j < FIELD_X + 10; j++){
			int newBase = base;
			if (Field[newBase][j] == 0){
				for (int i = newBase + 1; i < FIELD_Y + 21; i++){
					if (Field[i][j] != 0){
						newBase = i - 1;
						i = FIELD_Y + 21;
					}
				}
			}
			else {
				for (int i = newBase; i > 0; i--){
					if (Field[i][j] == 0){
						newBase = i;
						i = 0;
					}
				}
			}
			for (int i = newBase - 1; i > 0; i--){
				if (Field[i][j] > 0){
					Field[newBase][j] = Field[i][j];
					Field[i][j] = 0;
					newBase -= 1;
				}
			}
		}
		for (int i = FIELD_Y + 19; i >= FIELD_Y && lines < 4 * TetriminoSize; i--){
			int check = 0;
			for (int j = FIELD_X; j < FIELD_X + 10; j++){
				if (Field[i][j] <= 0){
					check = 1;
					j = FIELD_X + 10;
				}
			}
			if (check == 0){
				for (int k = FIELD_X; k < FIELD_X + 10; k++){
					Explode[i - FIELD_Y][k - FIELD_X].ClearColor = (Field[i][k] - 1) % 8;
					Explode[i - FIELD_Y][k - FIELD_X].ClearRemain = 10;
				}
				ClearRow[lines++] = i;
				lines = lines;
			}
		}
		if (lines > 0){
			CascadingFlag = 1;
			ClearLine(LineScorePoint(lines));
			RemainLCT = Scenario[Progress.Level].LCT;
			MainFlag -= 1;
		}
	}
	else {
		for (int i = FIELD_Y + 19; i >= FIELD_Y; i--){
			int check;
			for (check = FIELD_X; Field[i + lines][check] == 0 && check < FIELD_X + 10; check++);
			if (check == FIELD_X + 10){
				for (int k = i; k > 0; k--){
					for (int j = FIELD_X; j < FIELD_X + 10; j++){
						Field[k + lines][j] = Field[k + lines - 1][j];
					}
				}
				lines++;
			}
		}
	}
}

int GarbageCopy(){
	int check = 0, YDistance = (ObstacleFlag[OBS_BIG] && Scenario[Progress.Level].Big[0]) + 1;
	int xOrder[10] = { 9, 0, 8, 1, 7, 2, 6, 3, 5, 4 };
	int spaced = 0;
	for (int j = FIELD_X; check == 0 && j < FIELD_X + 10; j++){
		check += Field[FIELD_Y + 19 - NowLiftPressure][j];
	}
	if (check == 0){
		return 0;
	}
	if (GameOverJudge(Tetrimino.Type, Tetrimino.Side, Tetrimino.X, Tetrimino.Y, 1)){
		return 0;
	}
	for (int k = 0; k < YDistance; k++){
		for (int i = 1; i < FIELD_Y + 20 - NowLiftPressure; i++){
			for (int j = FIELD_X; j < FIELD_X + 10; j++){
				Field[i - 1][j] = Field[i][j];
				if (i - 1 - FIELD_Y >= 0){
					BlockOldness[i - 1 - FIELD_Y][j - FIELD_X] = BlockOldness[i - FIELD_Y][j - FIELD_X];
					InvisibleBlock[i - 1 - FIELD_Y][j - FIELD_X] = InvisibleBlock[i - FIELD_Y][j - FIELD_X];
				}
			}
		}
		for (int j = 0; j < 10; j++){
			if (Scenario[Progress.Level].CopyGarbage[3] != 0){
				if (spaced == 0 && Field[FIELD_Y + 18 - NowLiftPressure][FIELD_X + xOrder[j]] == 0){
					spaced = 1;
					Field[FIELD_Y + 19 - NowLiftPressure][FIELD_X + xOrder[j]] = 0;
				}
				else {
					Field[FIELD_Y + 19 - NowLiftPressure][FIELD_X + xOrder[j]] = 8;
				}
			}
			else {
				if (Field[FIELD_Y + 18 - NowLiftPressure][FIELD_X + xOrder[j]] == 0){
					Field[FIELD_Y + 19 - NowLiftPressure][FIELD_X + xOrder[j]] = 0;
				}
				else {
					Field[FIELD_Y + 19 - NowLiftPressure][FIELD_X + xOrder[j]] = 8;
				}
			}
			BlockOldness[19 - NowLiftPressure][xOrder[j]] = 0;
			InvisibleBlock[19 - NowLiftPressure][xOrder[j]] = 0;
		}
	}
	return 1;
}

int GarbageDirty(){
	static int preTime = 0, renzoku = 0, spacenum = 0, spacepos = 0;
	int YDistance=(ObstacleFlag[OBS_BIG]&&Scenario[Progress.Level].Big[0])+1,spacecell[10]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
	if(GameOverJudge(Tetrimino.Type,Tetrimino.Side,Tetrimino.X,Tetrimino.Y,1))return 0;
	if (preTime != LevelStartClock || Scenario[Progress.Level].RandomGarbage[4] == 0){
		preTime = LevelStartClock;
		renzoku = 0;
	}
	if (renzoku <= 0){
		spacenum = GetRand(Scenario[Progress.Level].RandomGarbage[3] - 1) + 1;
		if (spacenum > 10 / YDistance){
			spacenum = 10 / YDistance;
		}
		spacepos = GetRand(10 / YDistance - spacenum) * YDistance;
		renzoku = GetRand(3) + 1;
	}
	else {
		renzoku -= 1;
	}
	for(int i=0;i<spacenum*YDistance;i++)spacecell[i]=spacepos+i;
	for(int k=0;k<YDistance;k++){
		for(int i=1;i<FIELD_Y+20-NowLiftPressure;i++){
			for(int j=FIELD_X;j<FIELD_X+10;j++){
				Field[i-1][j]=Field[i][j];
				if(i-1-FIELD_Y>=0){
					BlockOldness[i-1-FIELD_Y][j-FIELD_X]=BlockOldness[i-FIELD_Y][j-FIELD_X];
					InvisibleBlock[i-1-FIELD_Y][j-FIELD_X]=InvisibleBlock[i-FIELD_Y][j-FIELD_X];
				}
			}
		}
		for(int j=FIELD_X;j<FIELD_X+10;j++){
			Field[FIELD_Y+19-NowLiftPressure][j]=8;
			BlockOldness[19-NowLiftPressure][j-FIELD_X]=0;
			InvisibleBlock[19-NowLiftPressure][j-FIELD_X]=0;
		}
		for(int j=0;j<10;j++){
			if(spacecell[j]>=0){
				Field[FIELD_Y+19-NowLiftPressure][FIELD_X+spacecell[j]]=0;
			}
		}
	}
	return 1;
}

void PressureUp(){
	int YDistance=(ObstacleFlag[OBS_BIG]&&Scenario[Progress.Level].Big[0])+1;
	if(GameOverJudge(Tetrimino.Type,Tetrimino.Side,Tetrimino.X,Tetrimino.Y,1))return;
	for(int k=0;k<YDistance;k++){
		for(int i=1;i<FIELD_Y+20;i++){
			for(int j=FIELD_X;j<FIELD_X+10;j++){
				Field[i-1][j]=Field[i][j];
				if(i-1-FIELD_Y>=0){
					BlockOldness[i-1-FIELD_Y][j-FIELD_X]=BlockOldness[i-FIELD_Y][j-FIELD_X];
					InvisibleBlock[i-1-FIELD_Y][j-FIELD_X]=InvisibleBlock[i-FIELD_Y][j-FIELD_X];
				}
			}
		}
		for(int j=FIELD_X;j<FIELD_X+10;j++){
			Field[FIELD_Y+19][j]=-1;
			BlockOldness[19][j-FIELD_X]=0;
			InvisibleBlock[19][j-FIELD_X]=0;
		}
		NowLiftPressure++;
	}
}

void PressureDown(){
	for(int i=FIELD_Y+19;i>=NowLiftPressure;i--){
		for(int j=FIELD_X;j<FIELD_X+10;j++){
			Field[i][j]=Field[i-NowLiftPressure][j];
		}
	}
	NowLiftPressure=0;
}

int LoadField(char Path[256]){
	int fp = FileRead_open(Path);
	if (!fp)return -1;
	for (int i = 0; i < 20 && !FileRead_eof(fp); i++){
		char Data[256] = { 0 };
		int block[10] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
		FileRead_gets(Data, sizeof(Data), fp);
		sscanf_s(Data, "%d %d %d %d %d %d %d %d %d %d", &block[0], &block[1], &block[2], &block[3], &block[4], &block[5], &block[6], &block[7], &block[8], &block[9]);
		for (int j = 0; j < 10; j++)if (block[j] >= 0 && block[j] <= 24){
			Field[FIELD_Y + i][FIELD_X + j] = block[j];
		}
	}
	FileRead_close(fp);
	return 0;
}

void GameInitialize(){
	Tetrimino.Hold = -1;
	memset(&Scores, 0, sizeof(Scores_t));
	Progress.Point = 0;
	Progress.DisplayPoint = 0;
	Progress.LTime = 0;
	Progress.TTime = 0;
	Progress.Rank = -1;
	MainFlag = 0;
	Scores.TTetriminos = 0;
	Scores.LTetriminos = 0;
	RemainLDT = 0;
	RemainLCT = 0;
	RemainARE = Scenario[Progress.Level].ARE;
	LevelUpWaitRemain = 0;
	DropWait = 0;
	PressTime = 0;
	AfterHold = 0;
	NowRen_Keep = 0;
	BtBingFlag = 0;
	TSpiningFlag = 0;
	GameClearFlag = 0;
	LevelDisplayTimeRemain = 0;
	ClearFieldTime = 0;
	WordFlag = 0;
	WordRemainCount = 0;
	GetLineClearPoint = 0;
	GetLineClearScore = 0;
	TimeLeftBonusTime = 0;
	TimeLeftGetScore = 0;
	CopyGarbageTime = 0;
	RandomGarbageTime = 0;
	NowLiftPressure = 0;
	AfterLevelUp = 0;
	QuakeX = 0;
	QuakeY = 0;
	QuakeTargetX = 0;
	QuakeTargetY = 0;
	memset(ObstacleFlag, 0, sizeof(ObstacleFlag));
	AfterEmerge = 0;
	MainPauseFlag = 0;
	WarnFlag = 0;
	WarnTime = 0;
	SoftLand = 0;
	MoveInfinity = 0;
	TurnInfinity = 0;
	MoveFlag = 0;
	TurnFlag = 0;
	for (int i = 0; i < 6; i++){
		IrregularRand[i] = GetRand(6);
	}
	IrregularRand[6] = GetRand(7);
	PastClearLines = 0;
	AlternateHideState = 0;
	NewRecord.Score = 0;
	NewRecord.Time = 0;
	NewRecord.Level = 0;
	NewRecord.Point = 0;
	NewRecord.Rank = 0;
	JustBeforeX = 0;
	JustBeforeY = 0;
	JustBeforeType = 0;
	ClearLineBase = 0;
	LoadFieldFlag = 0;
	CascadingFlag = 0;
	TempCascade = 0;
	TempLevelup = 0;
	CascadeGage = 0.0;
	CascadeNext = 0;
	PlayStartLevel = Progress.Level;
	RandomNumber.Game = GetRand(9999);
	RandomNumber.Level = GetRand(9999);
	RandomNumber.Line = GetRand(9999);
	RandomNumber.Tetrimino = GetRand(9999);
	RandomNumber.Frame = GetRand(9999);
	memset(BlockOldness, 0, sizeof(BlockOldness));
	memset(InvisibleBlock, 0, sizeof(InvisibleBlock));
	memset(SpentIfFlag, 0, sizeof(SpentIfFlag));
	memset(Flash, 0, sizeof(Flash_t)*FLASH_MAX);
	memset(Explode, 0, sizeof(Explode_t)* 20 * 10);
	memset(ClearRow, -1, sizeof(ClearRow));
	FieldInitialize();
	Tetrimino_Speed.Initialize();
	Line_Speed.Initialize();
	Drop.Initialize();
	ResetAddPoint();
}

int GamePlay(){
	for (int i = 0; i<IF_MAX; i++){
		if (Scenario[Progress.Level].IfFlag[i]){
			int ok = 1;
			for (int j = 0; j<5 && ok; j++){
				if (Course.IfCondition[i][j * 3] >= 0 && Course.IfCondition[i][j * 3 + 1] >= 0){
					if (!JudgeBySign(BoardToValue(Course.IfCondition[i][j * 3]), Course.IfCondition[i][j * 3 + 2], Course.IfCondition[i][j * 3 + 1]))ok = 0;
				}
			}
			if (ok && SpentIfFlag[i] == 0){
				LoadCourse(FLDN_FileName, i);
				SpentIfFlag[i] = 1;
			}
			else if (!ok && SpentIfFlag[i] == 1){
				SpentIfFlag[i] = 0;
			}
		}
	}
	switch(MainFlag%100/10){
		case 0:
			LevelStartClock = GetNowCount();
			CopyGarbageTime=Scenario[Progress.Level].CopyGarbage[1];
			RandomGarbageTime=Scenario[Progress.Level].RandomGarbage[1];
			Bgm.Play(Course.BgmPath[Scenario[Progress.Level].BgmFlag],Course.BgmVolume[Scenario[Progress.Level].BgmFlag]*Save.ReadSystem(Save.BGM_VOLUME)/100,Course.BgmLoopPoint[Scenario[Progress.Level].BgmFlag]);
			MainFlag+=13;
		case 1:
			RandomNumber.Frame=GetRand(9999);
			switch(MainFlag%10){
				case 0:
					SoftLand=0;
					if(GameClearFlag==1){
						MainFlag=230;
						break;
					}
					if(Scores.TTetriminos%7==0)PermNext();
					Tetrimino.Type=Tetrimino.Next[0];
					if(ObstacleFlag[OBS_SHADOW]||ObstacleFlag[OBS_SUDDEN]){
						for(int i=0;i<20;i++){
							for(int j=0;j<10;j++){
								if(Field[FIELD_Y+i][FIELD_X+j]>=1&&Field[FIELD_Y+i][FIELD_X+j]<=8){
									if(Scenario[Progress.Level].Shadow[0]<Scenario[Progress.Level].SuddenAppear[0]){
										if(ObstacleFlag[OBS_SHADOW]&&BlockOldness[i][j]>=Scenario[Progress.Level].Shadow[0])InvisibleBlock[i][j]=1;
										if(ObstacleFlag[OBS_SUDDEN]&&BlockOldness[i][j]>=Scenario[Progress.Level].SuddenAppear[0])InvisibleBlock[i][j]=0;
									}
									else {
										if(ObstacleFlag[OBS_SUDDEN]&&BlockOldness[i][j]>=Scenario[Progress.Level].SuddenAppear[0])InvisibleBlock[i][j]=0;
										if(ObstacleFlag[OBS_SHADOW]&&BlockOldness[i][j]>=Scenario[Progress.Level].Shadow[0])InvisibleBlock[i][j]=1;
									}
								}
							}
						}
					}
					else memset(InvisibleBlock,0,sizeof(InvisibleBlock));
					if(ObstacleFlag[OBS_COPY]&&CopyGarbageTime<1){
						for(int i=0;i<Scenario[Progress.Level].CopyGarbage[2];i++){
							if(GarbageCopy())CopyGarbageTime=Scenario[Progress.Level].CopyGarbage[1];
						}
					}
					if(ObstacleFlag[OBS_RANDOM]&&RandomGarbageTime<1){
						for(int i=0;i<Scenario[Progress.Level].RandomGarbage[2];i++){
							if(GarbageDirty())RandomGarbageTime=Scenario[Progress.Level].RandomGarbage[1];
						}
					}
					if(ObstacleFlag[OBS_RC]){
						for(int i=0;i<6;i++){
							if(Scenario[Progress.Level].RandomColor[i]){
								IrregularRand[i]=GetRand(6);
							}
						}
						IrregularRand[6]=GetRand(7);
					}
					if(NowLiftPressure&&AfterLevelUp)PressureDown();
					if(ObstacleFlag[OBS_LIFT]&&NowLiftPressure<Scenario[Progress.Level].Lift[1]&&Scenario[Progress.Level].Lift[0]/(Scenario[Progress.Level].Lift[1]<=1?1:Scenario[Progress.Level].Lift[1]-1)*NowLiftPressure<=Progress.LTime-Scenario[Progress.Level].ObstacleTime){
						PressureUp();
					}
					if(!EmergeTetrimino()){
						MainFlag=220;
						break;
					}
					else {
						Scores.TTetriminos++;
						Scores.LTetriminos++;
						RandomNumber.Tetrimino=GetRand(9999);
						Save.WriteSystem(Save.TOTALS_TM + Progress.Mode * 6, Save.ReadSystem(Save.TOTALS_TM + Progress.Mode * 6) + 1);
						if(ObstacleFlag[OBS_ALTHIDE]&&Scenario[Progress.Level].AlternateHide[0]){
							if(Scores.TTetriminos%Scenario[Progress.Level].AlternateHide[0]==0){
								if(AlternateHideState==0)AlternateHideState=1;
								else AlternateHideState=0;
							}
						}
						Tetrimino_Speed.Record(Progress.TTime);
						StuffNext();
						if(ObstacleFlag[OBS_RC]&&Scenario[Progress.Level].RandomColor[0])SoundEffect.RaiseFlag(IrregularRand[0]);
						else SoundEffect.RaiseFlag(Tetrimino.Type);
						AfterEmerge=1;
						AfterLevelUp=0;
						MainFlag+=1;
					}
				case 1:
					if(Key.Check(KC_HOLD)==1||(AfterEmerge==1&&Key.Check(KC_HOLD)>0))HoldTetrimino();
					AfterEmerge=0;
					MoveFlag=0;
					TurnFlag=0;
					if(Key.Check(KC_LTURN_1)==1){
						if(TurnTetrimino(-1))TurnFlag=1;
						PressTime=0;
					}
					else if(Key.Check(KC_RTURN_1)==1){
						if(TurnTetrimino(1))TurnFlag=1;
						PressTime=0;
					}
					else if(Key.Check(KC_LTURN_2)==1){
						if(TurnTetrimino(-1))TurnFlag=1;
						PressTime=0;
					}
					else if(Key.Check(KC_RTURN_2)==1){
						if(TurnTetrimino(1))TurnFlag=1;
						PressTime=0;
					}
					if (IRSFlag != 0){
						IRSFlag = 0;
					}
					if(Key.Check(KC_LEFT)==1){
						MoveAtodashiFlag=-1;
					}
					else if(Key.Check(KC_RIGHT)==1){
						MoveAtodashiFlag=1;
					}
					if((Key.Check(KC_LEFT)>=Scenario[Progress.Level].DAS||Key.Check(KC_LEFT)==1)&&MoveAtodashiFlag!=1){
						if(MoveTetrimino(-1))MoveFlag=1;
						PressTime=0;
					}
					else if((Key.Check(KC_RIGHT)>=Scenario[Progress.Level].DAS||Key.Check(KC_RIGHT)==1)&&MoveAtodashiFlag!=-1){
						if(MoveTetrimino(1))MoveFlag=1;
						PressTime=0;
					}
					if(Key.Check(KC_MDROP)){
						int k=GhostBlock();
						if(k>0){
							Tetrimino.Y+=k;
							DropWait=Scenario[Progress.Level].Denominator;
							RemainLDT=Scenario[Progress.Level].LDT;
							if(ObstacleFlag[OBS_BOOST]&&Tetrimino.Y+Course.ShapeBoostPos[Scenario[Progress.Level].ShapeFlag][Tetrimino.Type][Tetrimino.Side]>=FIELD_Y+Scenario[Progress.Level].Boost[0]){
								if(Scenario[Progress.Level].Boost[2]>=0)DropWait=Scenario[Progress.Level].Boost[2];
								if(Scenario[Progress.Level].Boost[3]>=0)RemainLDT=Scenario[Progress.Level].Boost[3];
							}
							TSpiningFlag=PressTime=0;
						}
					}
					if (DropWait > 0 && (Key.Check(KC_DOWN) > 0 && (Key.Check(KC_DOWN) - 1) % ((Scenario[Progress.Level].SoftDropInterval > 0) ? Scenario[Progress.Level].SoftDropInterval : 1) == 0 || Key.Check(KC_HDROP))){
						DropWait = 0;
					}
					else {
						if(Scenario[Progress.Level].SmoothDrop)DropWait-=Scenario[Progress.Level].Numerator;
						else DropWait--;
					}
					if(DropWait<1){
						if(Key.Check(KC_HDROP)){
							for(int i=0;DropTetrimino()&&i<20;i++);
							DropWait=0;
						}
						else {
							int k;
							k = Scenario[Progress.Level].Numerator;
							if(ObstacleFlag[OBS_BOOST]&&Tetrimino.Y+Course.ShapeBoostPos[Scenario[Progress.Level].ShapeFlag][Tetrimino.Type][Tetrimino.Side]>=FIELD_Y+Scenario[Progress.Level].Boost[0]){
								if (Scenario[Progress.Level].Boost[1] >= 0){
									k = Scenario[Progress.Level].Boost[1];
								}
							}
							if (Scenario[Progress.Level].SmoothDrop){
								for (int i = 0; i < 20 && DropWait < 1 && DropTetrimino(); i++);
							}
							else for(int i=0;i<k&&DropTetrimino();i++);
						}
						if(DropWait<1){
							if(Key.Check(KC_DOWN)==1||Key.Check(KC_HDROP)){
								RemainLDT=-1;
								SoftLand=0;
							}
							else if(Key.Check(KC_DOWN)){
								if(RemainLDT>=0)RemainLDT--;
								if(Key.Check(KC_LEFT)==0&&Key.Check(KC_RIGHT)==0)PressTime++;
								if(PressTime>=Scenario[Progress.Level].DAS){
									PressTime=0;
									RemainLDT=-1;
									SoftLand=0;
								}
							}
							else {
								if(RemainLDT>=0)RemainLDT--;
								PressTime=0;
								if(MoveFlag&&RemainLDT<=Scenario[Progress.Level].InfDelay&&MoveInfinity<Scenario[Progress.Level].MoveInfMax&&SoftLand<Scenario[Progress.Level].InfDelay){
									MoveInfinity+=(Scenario[Progress.Level].InfDelay-SoftLand);
									SoftLand=Scenario[Progress.Level].InfDelay;
									if(MoveInfinity>Scenario[Progress.Level].MoveInfMax){
										SoftLand-=(MoveInfinity-Scenario[Progress.Level].MoveInfMax);
										MoveInfinity=Scenario[Progress.Level].MoveInfMax;
									}
								}
								if(TurnFlag&&RemainLDT<=Scenario[Progress.Level].InfDelay&&TurnInfinity<Scenario[Progress.Level].TurnInfMax&&SoftLand<Scenario[Progress.Level].InfDelay){
									TurnInfinity+=(Scenario[Progress.Level].InfDelay-SoftLand);
									SoftLand=Scenario[Progress.Level].InfDelay;
									if(TurnInfinity>Scenario[Progress.Level].TurnInfMax){
										SoftLand-=(TurnInfinity-Scenario[Progress.Level].TurnInfMax);
										TurnInfinity=Scenario[Progress.Level].TurnInfMax;
									}
								}
							}
							if(RemainLDT<0){
								if(SoftLand<=0){
									if(ClearLine(LineScorePoint(LockDown()))){
										MainFlag+=1;
									}
									else {
										MainFlag+=2;
										break;
									}
								}
								else {
									SoftLand--;
								}
							}
						}
					}
					if(MainFlag%100==11)break;
				case 2:
					RemainLCT--;
					if(RemainLCT>=0)
						break;
					else {
						SoundEffect.RaiseFlag(10);
						MainFlag+=1;
						StuffLine(PastClearLines);
					}
					break;
				case 3:
					if(!(WarnFlag&2)&&Progress.LTime>=Scenario[Progress.Level].ObstacleTime){
						int change=0;
						for(int i=0;i<OBSTACLE_MAX;i++){
							if(Scenario[Progress.Level].ObstacleFlag[i]){
								change++;
								i = OBSTACLE_MAX;
							}
						}
						WarnFlag|=2;
						if(change&&Scenario[Progress.Level].ObstacleTime>0){
							SoundEffect.Stop(21);
							SoundEffect.RaiseFlag(22);
						}
					}
					for (int i = 0; i < OBSTACLE_MAX; i++){
						if ((Scenario[Progress.Level].ObstacleFlag[i] && Progress.LTime >= Scenario[Progress.Level].ObstacleTime) || Scenario[Progress.Level].FirstObstacle[i] || Course.NaturalObstacle[i]){
							ObstacleFlag[i] = 1;
						}
						else {
							ObstacleFlag[i] = 0;
						}
					}

					if(!(WarnFlag&8)&&Progress.Point>=Scenario[Progress.Level].PointMax-Scenario[Progress.Level].PreliminaryBell[1]&&Scenario[Progress.Level].PointMax>Scenario[Progress.Level].PreliminaryBell[1]&&Scenario[Progress.Level].PointMax>Progress.Point){
						SoundEffect.RaiseFlag(24);
						WarnFlag|=12;
					}
					if(!(WarnFlag&4)&&Progress.Point>=Scenario[Progress.Level].PointMax-Scenario[Progress.Level].PreliminaryBell[0]&&Scenario[Progress.Level].PointMax>Scenario[Progress.Level].PreliminaryBell[0]&&Scenario[Progress.Level].PointMax>Progress.Point){
						SoundEffect.RaiseFlag(23);
						WarnFlag|=4;
					}
					MainFlag+=1;
				case 4:
					MoveAtodashiFlag=0;
					TSpiningFlag=0;
					Tetrimino.Type=Tetrimino.Next[0];
					Tetrimino.Side=(((Key.Check(KC_LTURN_1)||Key.Check(KC_LTURN_2))&&1)*3+((Key.Check(KC_RTURN_1)||Key.Check(KC_RTURN_2))&&1))%4;
					if(ObstacleFlag[OBS_REVERSE]&&Scenario[Progress.Level].Reverse[0]){
						if(Tetrimino.Side==3)Tetrimino.Side=1;
						else if(Tetrimino.Side==1)Tetrimino.Side=3;
					}
					if(ObstacleFlag[OBS_BIG]){
						Tetrimino.X=FIELD_X+Scenario[Progress.Level].EmergePos[Tetrimino.Type][2];
						Tetrimino.Y=FIELD_Y+Scenario[Progress.Level].EmergePos[Tetrimino.Type][3];
					}
					else {
						Tetrimino.X=FIELD_X+Scenario[Progress.Level].EmergePos[Tetrimino.Type][0];
						Tetrimino.Y=FIELD_Y+Scenario[Progress.Level].EmergePos[Tetrimino.Type][1];
					}
					Tetrimino.Side*=(!GameOverJudge(Tetrimino.Type,Tetrimino.Side,Tetrimino.X,Tetrimino.Y,0));
					if(ClearFieldTime<=0&&ObstacleFlag[OBS_CFB]){
						int exp_remain=0;
						for(int i=MIN(19,Scenario[Progress.Level].ClearForBig[1]);i>=MAX(0,Scenario[Progress.Level].ClearForBig[0]);i--){
							int blocks=0;
							for(int j=MAX(0,Scenario[Progress.Level].ClearForBig[2]);j<=MIN(9,Scenario[Progress.Level].ClearForBig[3]);j++){
								if((Field[FIELD_Y+i/2*2][FIELD_X+j/2*2]>0)+(Field[FIELD_Y+i/2*2][FIELD_X+j/2*2+1]>0)+(Field[FIELD_Y+i/2*2+1][FIELD_X+j/2*2]>0)+(Field[FIELD_Y+i/2*2+1][FIELD_X+j/2*2+1]>0)<4&&Field[FIELD_Y+i][FIELD_X+j]>0){
									Explode[i][j].ClearColor=(Field[FIELD_Y+i][FIELD_X+j]-1)%8;
									Explode[i][j].ClearRemain=exp_remain+10;
									blocks+=Field[FIELD_Y+i][FIELD_X+j];
									Field[FIELD_Y+i][FIELD_X+j]=0;
								}
							}
							if(blocks){
								exp_remain+=10;
							}
						}
						if(exp_remain>ClearFieldTime){
							ClearFieldTime=exp_remain;
						}
						for(int i=0;i<FIELD_Y;i++){
							for(int j=FIELD_X;j<FIELD_X+10;j++){
								if(Field[i][j]>0)Field[i][j]=0;
							}
						}
						ObstacleFlag[OBS_CFB] = 0;
						Scenario[Progress.Level].ObstacleFlag[OBS_CFB] = 0;
					}
					else if(ClearFieldTime<=0&&ObstacleFlag[OBS_CFIELD]){
						int exp_remain=0;
						for(int i=MIN(19,Scenario[Progress.Level].ClearField[1]);i>=MAX(0,Scenario[Progress.Level].ClearField[0]);i--){
							int blocks=0;
							for(int j=MAX(0,Scenario[Progress.Level].ClearField[2]);j<=MIN(9,Scenario[Progress.Level].ClearField[3]);j++){
								if(Field[FIELD_Y+i][FIELD_X+j]>0){
									Explode[i][j].ClearColor=(Field[FIELD_Y+i][FIELD_X+j]-1)%8;
									Explode[i][j].ClearRemain=exp_remain+10;
									blocks+=Field[FIELD_Y+i][FIELD_X+j];
									Field[FIELD_Y+i][FIELD_X+j]=0;
								}
							}
							if(blocks){
								exp_remain+=10;
							}
						}
						if(exp_remain>ClearFieldTime){
							ClearFieldTime=exp_remain;
						}
						for(int i=0;i<FIELD_Y;i++){
							for(int j=FIELD_X;j<FIELD_X+10;j++){
								if(Field[i][j]>0)Field[i][j]=0;
							}
						}
						ObstacleFlag[OBS_CFIELD] = 0;
						Scenario[Progress.Level].ObstacleFlag[OBS_CFIELD] = 0;
					}
					if(ClearFieldTime<=0){
						if(ObstacleFlag[OBS_LEVELUP]){
							int ok=1;
							for(int i=0;i<5&&ok;i++){
								if(Scenario[Progress.Level].LevelUpCondition[i*3]>=0&&Scenario[Progress.Level].LevelUpCondition[i*3+1]>=0){
									if(!JudgeBySign(BoardToValue(Scenario[Progress.Level].LevelUpCondition[i*3]),Scenario[Progress.Level].LevelUpCondition[i*3+2],Scenario[Progress.Level].LevelUpCondition[i*3+1]))ok=0;
								}
							}
							if(ok){
								if(Scenario[Progress.Level].LevelUp[1])Progress.Point=0;
								NextLevel(Scenario[Progress.Level].LevelUp[0]);	
							}
						}
						if (TempLevelup){
							NextLevel(1);
							TempLevelup = 0;
						}
						if(!LoadFieldFlag){
							LoadField(Scenario[Progress.Level].InitialFieldPath);
							LoadFieldFlag=1;
						}
						LevelUpWaitRemain--;
						if(Scenario[Progress.Level].ARE>LevelUpWaitRemain)RemainARE--;
						if(RemainARE<0)MainFlag-=4;
					}
					else {
						if(ClearFieldTime%10==0){
							SoundEffect.RaiseFlag(11);
						}
						ClearFieldTime--;
					}
					break;
			}
			if(Progress.TTime%Fps.FRAME_RATE==Fps.FRAME_RATE-1){
				Scores.Tmin=Tetrimino_Speed.Calc(Progress.TTime);
				Scores.Lmin=Line_Speed.Calc(Progress.TTime);
			}
			if(!(WarnFlag&1)&&Progress.LTime>=Scenario[Progress.Level].ObstacleTime-300&&Progress.LTime<Scenario[Progress.Level].ObstacleTime){
				for(int i=0;i<OBSTACLE_MAX;i++){
					if(Scenario[Progress.Level].ObstacleFlag[i]&&!ObstacleFlag[i]){
						SoundEffect.RaiseFlag(21);
						WarnFlag|=1;
						i=OBSTACLE_MAX;
					}
				}
			}
			QuakeField();
			if(CopyGarbageTime>0&&Scenario[Progress.Level].CopyGarbage[0]==0)CopyGarbageTime--;
			if(RandomGarbageTime>0&&Scenario[Progress.Level].RandomGarbage[0]==0)RandomGarbageTime--;
			for(int i=0;i<20;i++){
				for(int j=0;j<10;j++){
					if(Field[FIELD_Y+i][FIELD_X+j]>=1&&Field[FIELD_Y+i][FIELD_X+j]<=8)BlockOldness[i][j]++;
				}
			}
			WarnTime=(WarnTime+(WarnFlag&1&&1))*!(WarnFlag&2&&1);
			Progress.LTime++;
			Progress.TTime++;
			break;
		case 2:
			switch(MainFlag%10){
				case 0:
					Bgm.Stop();
					SoundEffect.RaiseFlag(15);
					QuakeX=0;
					QuakeY=0;
					for(int i=0;i<OBSTACLE_MAX;i++)if(!Course.NaturalObstacle[i])ObstacleFlag[i]=0;
					if(Course.GameOverRank)Progress.Rank=0;
					else Progress.Rank=CalcRank(Course.RankBoard,Course.RankSign);
					for(int i=0;i<20;i++){
						for(int j=0;j<10;j++){
							InvisibleBlock[i][j]=0;
						}
					}
					Save.SaveCourse();
					GameOverWaitTime=0;
					MainFlag+=1;
				case 1:
					GameOverWaitTime++;
					if(GameOverWaitTime>60)MainFlag+=1;
					break;
				case 2:
					if(Key.Check(KC_DECIDE)==1||Key.Check(KC_CANCEL)==1)MainFlag=0;
					break;
			}
			break;
		case 3:
			switch(MainFlag%10){
				case 0:
					if(Course.SpeedRun){
						if(Progress.TTime<Save.ReadCourse(Save.BEST_TIME)&&SelectLevel==0){
							Save.WriteCourse(Save.BEST_TIME,Progress.TTime);
							NewRecord.Time=1;
						}
					}
					Bgm.Stop();
					SoundEffect.RaiseFlag(16);
					QuakeX=0;
					QuakeY=0;
					for(int i=0;i<OBSTACLE_MAX;i++)if(!Course.NaturalObstacle[i])ObstacleFlag[i]=0;
					Progress.Rank=CalcRank(Course.RankBoard,Course.RankSign);
					if(Progress.Rank>Save.ReadCourse(Save.BEST_RANK)&&Course.RecMaxRank){
						if (Course.FirstStartRank == 0 || PlayStartLevel == 0){
							Save.WriteCourse(Save.BEST_RANK, Progress.Rank);
							NewRecord.Rank = 1;
						}
					}
					if(Course.RecClearTimes){
						Save.WriteCourse(Save.CLEAR_TIMES,Save.ReadCourse(Save.CLEAR_TIMES)+1);
					}
					for(int i=0;i<20;i++){
						for(int j=0;j<10;j++){
							InvisibleBlock[i][j]=0;
						}
					}
					Save.SaveCourse();
					GameOverWaitTime=0;
					MainFlag+=1;
				case 1:
					GameOverWaitTime++;
					if(GameOverWaitTime>60)MainFlag+=1;
					break;
				case 2:
					if(Key.Check(KC_DECIDE)==1||Key.Check(KC_CANCEL)==1)MainFlag=0;
					break;
			}
			break;
	}
	return (MainFlag/10)!=21;
}