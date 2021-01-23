#include <DxLib.h>
#include <bgm/bgm.h>

CBgm::CBgm(){
	CBgm::File=0;
	memset(CBgm::PlayingPath,0,sizeof(CBgm::PlayingPath));
}

CBgm::~CBgm(){
	StopSoundMem(CBgm::File);
	DeleteSoundMem(CBgm::File);
}

void CBgm::Stop(){
	StopSoundMem(CBgm::File);
	DeleteSoundMem(CBgm::File);
	memset(CBgm::PlayingPath,0,sizeof(CBgm::PlayingPath));
}

int CBgm::Play(char Path[256],int Volume,int LoopPoint){
	if(strcmp(Path,CBgm::PlayingPath)!=0){
		SetCreateSoundDataType(DX_SOUNDDATATYPE_MEMPRESS);
		CBgm::Stop();
		CBgm::File=LoadSoundMem(Path);
		ChangeVolumeSoundMem(Volume,CBgm::File);
		SetLoopSamplePosSoundMem(LoopPoint,CBgm::File);
		PlaySoundMem(CBgm::File,DX_PLAYTYPE_LOOP);
		strcpy_s(CBgm::PlayingPath,sizeof(CBgm::PlayingPath),Path);
		SetCreateSoundDataType(DX_SOUNDDATATYPE_MEMNOPRESS);
		return 1;
	}
	else return 0;
}