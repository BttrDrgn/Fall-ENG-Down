#include <DxLib.h>
#include <voice/voice.h>

CVoice::CVoice(){
	memset(CVoice::File,0,sizeof(CVoice::File));
	memset(CVoice::Flag,0,sizeof(CVoice::Flag));
}

CVoice::~CVoice(){
	for(int i=0;i<CVoice::MAX;i++){
		StopSoundMem(CVoice::File[i]);
		DeleteSoundMem(CVoice::File[i]);
	}
}

void CVoice::SetVolume(int Volume){
	for(int i=0;i<CVoice::MAX;i++){
		ChangeVolumeSoundMem(Volume*255/100,CVoice::File[i]);
	}
}

void CVoice::RaiseFlag(int Num){
	CVoice::Flag[Num]=1;
}

void CVoice::LoadSet(){
	char Path[256]={0},VoiceName[CVoice::MAX][6]={
		"v_2","v_3","v_4","v_t","v_tm","v_t1","v_t2","v_t3","v_btm","v_bt1",
		"v_bt2","v_bt3","v_b4"
	};
	SetCreateSoundDataType(DX_SOUNDDATATYPE_MEMNOPRESS);
	for(int i=0;i<CVoice::MAX;i++){
		StopSoundMem(CVoice::File[i]);
		DeleteSoundMem(CVoice::File[i]);
		sprintf_s(Path,sizeof(Path),"dat/voice/%s.ogg",VoiceName[i]);
		CVoice::File[i]=LoadSoundMem(Path);
	}
}

void CVoice::Play(){
	for(int i=0;i<CVoice::MAX;i++){
		if(CVoice::Flag[i]){
			PlaySoundMem(CVoice::File[i],DX_PLAYTYPE_BACK);
		}
		CVoice::Flag[i]=0;
	}
}