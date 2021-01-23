#include <DxLib.h>
#include <resource/resource.h>
#include <animation/animation.h>
#include <bgm/bgm.h>
#include <display/display.h>
#include <drop/drop.h>
#include <file_list/file_list.h>
#include <fps/fps.h>
#include <game_play/game_play.h>
#include <key/key.h>
#include <layer/layer.h>
#include <load/load.h>
#include <main.h>
#include <menu/menu.h>
#include <save/save.h>
#include <screen_shot/screen_shot.h>
#include <sound_effect/sound_effect.h>
#include <speed/speed.h>
#include <voice/voice.h>
#include <window_mode/window_mode.h>

#ifdef _WIN32
#  ifdef DXPORTLIB
#    include "SDL_main.h"
#  endif
#endif

CAnimation Animation;
CBgm Bgm;
CDrop Drop;
CFileList FileList;
CFps Fps;
CKey Key;
CLayer Layer;
CSave Save;
CScreenShot ScreenShot;
CSoundEffect SoundEffect;
CSpeed Tetrimino_Speed;
CSpeed Line_Speed;
CVoice Voice;
CWindowMode WindowMode;

int MainFlag = 0;
int MainPauseFlag =0;

int LoadBackInfo(){
	char Data[256]={0};
	int fp=FileRead_open("dat/img/back/info.txt");
	if(!fp)return -1;
	FileRead_gets(Data,sizeof(Data),fp);
	sscanf_s(Data,"%d,%d,%d",&GraphicInfo.BackBlackMax,&GraphicInfo.BackWhiteMax,&GraphicInfo.BackMaskMax);
	FileRead_close(fp);
	if(GraphicInfo.BackBlackMax<=0)GraphicInfo.BackBlackMax=1;
	if(GraphicInfo.BackWhiteMax<=0)GraphicInfo.BackWhiteMax=1;
	if(GraphicInfo.BackMaskMax<=0)GraphicInfo.BackMaskMax=1;
	return 0;
}

void FirstInitialize(){
	GraphicInfo.MaskLevel=-1;
	GraphicInfo.MaskNumber=0;
	FileList.ListUp("crs");
	SoundEffect.LoadSet(Save.ReadSystem(Save.SE_SET));
	Voice.LoadSet();
	LoadBackInfo();
	Animation.Initialize();
	LoadGraphic();
	FontSetting();
	ColorSetting();
	DrawNameSetting();
	CourseTagSetting();
	BoardSignNameSetting();
	SetDefaultCourseData();
	SetKeyName();
}

int ProcessLoop(){
	if(ProcessMessage()!=0)return -1;
	if(ClearDrawScreen()!=0)return -1;
	Key.GetKey();
	Key.GetPad();
    return 0;
}

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow){
	MessageBoxA(nullptr, 0,0,0);
	SetWindowStyleMode(2);
	SetAlwaysRunFlag(FALSE);
	SetDoubleStartValidFlag(FALSE);
	SetOutApplicationLogValidFlag(FALSE);
	SetWindowIconID(IDI_ICON2);
	SetMainWindowText("Falling Down");
	if(Save.LoadSystem("dat/save/system.save")==-1)return -1;
	WindowMode.Initialize(Save.ReadSystem(Save.WINDOW_MODE));
    if(DxLib_Init()==-1||SetDrawScreen(DX_SCREEN_BACK)!=0)return -1;
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);
	SetUseGraphBaseDataBackup(TRUE);
	int BootTime=GetNowCount();
	LoadGraphScreen(0,0,"dat/img/loading.png",FALSE);
	ScreenFlip();
	Key.LoadKeyConfig();
	Key.LoadPadConfig();
	FirstInitialize();
	if(GetNowCount()<BootTime+1000){
		Sleep(BootTime+1000-GetNowCount());
	}
	while(ProcessLoop()==0){
		if(Key.Check(KC_SCREENSHOT)==1){
			ScreenShotCount=0;
		}
		if(Key.Check(KC_ESCAPE)==1){
			if(MainFlag==10)MainFlag=999;
			else if(MainFlag/100==0||MainFlag/100==3){
				MainFlag=0;
			}
			else if((MainFlag/100==1||MainFlag/100==2)&&Scenario[Progress.Level].NoPause==0){
				if(MainPauseFlag==0)MainPauseFlag=1;
			}
		}
		switch(MainFlag/100){
			case 0:
				if(ViewMode==0)GameSelect();
				else BackViewing();
				break;
			case 1:
				if(MainPauseFlag==FALSE)GameReady();
				else GamePause();
				break;
			case 2:
				if(MainPauseFlag==FALSE)GamePlay();
				else GamePause();
				break;
			case 3:
				GameConfiguration();
				break;
			case 4:
				GameCareer();
				break;
			case 5:
				GameKeyConfig();
				break;
		}
		if(MainFlag==999)break;
		DrawMain();
		SoundEffect.Play();
		Voice.Play();
        ScreenFlip();
		if(Key.Check(KC_SCREENSHOT)==1){
			ScreenShot.Shot("ss");
			ScreenShotCount=180;
		}
		Fps.Wait();
    }
	Save.SaveSystem();
    DxLib_End();
    return 0;
}
#else
int main(int argc, char **argv) {

	//For DxPortLib
#ifdef DXPORTLIB
	SetUseCharSet(DX_CHARSET_EXT_UTF8);
#endif
	SetWindowSizeChangeEnableFlag(TRUE);
	SetWaitVSyncFlag(TRUE);
	SetGraphMode(640, 480, 32);
	ChangeWindowMode(TRUE);
	DxLib_Init();
	//end

	SetWindowStyleMode(2);
	SetAlwaysRunFlag(FALSE);
	SetDoubleStartValidFlag(FALSE);
	SetOutApplicationLogValidFlag(FALSE);
	SetWindowIconID(IDI_ICON2);

	/* - DxPortLib defines the _T() and _TEXT() macro for all platforms.
	 *   This chooses between Unicode or Multibyte text automatically. */

	SetMainWindowText(_T("Falling Down"));
	if (Save.LoadSystem("dat/save/system.save") == -1)return -1;
	WindowMode.Initialize(Save.ReadSystem(Save.WINDOW_MODE));
	if (DxLib_Init() == -1 || SetDrawScreen(DX_SCREEN_BACK) != 0)return -1;
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);
	SetUseGraphBaseDataBackup(TRUE);
	int BootTime = GetNowCount();
	LoadGraphScreen(0, 0, "dat/img/loading.png", FALSE);
	ScreenFlip();
	Key.LoadKeyConfig();
	Key.LoadPadConfig();
	FirstInitialize();
	if (GetNowCount() < BootTime + 1000) {
		Sleep(BootTime + 1000 - GetNowCount());
	}
	while (ProcessLoop() == 0) {
		if (Key.Check(KC_SCREENSHOT) == 1) {
			ScreenShotCount = 0;
		}
		if (Key.Check(KC_ESCAPE) == 1) {
			if (MainFlag == 10)MainFlag = 999;
			else if (MainFlag / 100 == 0 || MainFlag / 100 == 3) {
				MainFlag = 0;
			}
			else if ((MainFlag / 100 == 1 || MainFlag / 100 == 2) && Scenario[Progress.Level].NoPause == 0) {
				if (MainPauseFlag == 0)MainPauseFlag = 1;
			}
		}
		switch (MainFlag / 100) {
		case 0:
			if (ViewMode == 0)GameSelect();
			else BackViewing();
			break;
		case 1:
			if (MainPauseFlag == FALSE)GameReady();
			else GamePause();
			break;
		case 2:
			if (MainPauseFlag == FALSE)GamePlay();
			else GamePause();
			break;
		case 3:
			GameConfiguration();
			break;
		case 4:
			GameCareer();
			break;
		case 5:
			GameKeyConfig();
			break;
		}
		if (MainFlag == 999)break;
		DrawMain();
		SoundEffect.Play();
		Voice.Play();
		ScreenFlip();
		if (Key.Check(KC_SCREENSHOT) == 1) {
			ScreenShot.Shot("ss");
			ScreenShotCount = 180;
		}
		Fps.Wait();
	}
	Save.SaveSystem();
	DxLib_End();
	return 0;
}
#endif