#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")
#include <DxLib.h>
#include <screen_shot/screen_shot.h>

void CScreenShot::Shot(char Directory[256]){
	char Path[256];
	DATEDATA Date;
	wsprintf(Path,Directory);
	if(PathIsDirectory(Path)==FALSE){
		CreateDirectory(Path,NULL);
	}
	GetDateTime(&Date);
	for(int i=1;i<100&&PathFileExists(Path)==TRUE;i++){
		wsprintf(Path,"%s/%04dy%02dm%02dd%02dh%02dm%02ds_%d.bmp",Directory,Date.Year,Date.Mon,Date.Day,Date.Hour,Date.Min,Date.Sec,i);
	}
	SaveDrawScreenToBMP(0,0,640,480,Path);
}