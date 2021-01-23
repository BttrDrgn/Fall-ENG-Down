#include <DxLib.h>
#include <window_mode/window_mode.h>

void CWindowMode::Initialize(int StartWindowModeFlag){
	ChangeWindowMode(StartWindowModeFlag && 1);
	CWindowMode::NowWindowModeFlag = (StartWindowModeFlag && 1);
}

int CWindowMode::Change(int TargetWindowModeFlag){
	int State = 0;
	if (TargetWindowModeFlag){
		if (TargetWindowModeFlag == 1){
			SetWindowStyleMode(2);
			SetWindowSizeChangeEnableFlag(FALSE);
		}
		else if (TargetWindowModeFlag == 2){
			SetWindowStyleMode(2);
			SetWindowSizeChangeEnableFlag(TRUE);
		}
		else if (TargetWindowModeFlag == 3){
			SetWindowStyleMode(0);
			SetWindowSizeChangeEnableFlag(TRUE);
		}
		TargetWindowModeFlag = 1;
	}
	if (CWindowMode::NowWindowModeFlag != (TargetWindowModeFlag && 1)){
		if (ChangeWindowMode(TargetWindowModeFlag) == DX_CHANGESCREEN_OK){
			CWindowMode::NowWindowModeFlag = TargetWindowModeFlag;
			State = 1;
		}
		else {
			ChangeWindowMode(TRUE);
			State = -1;
		}
		SetDrawScreen(DX_SCREEN_BACK);
	}
	return State;
}