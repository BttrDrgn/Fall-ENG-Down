#include <DxLib.h>
#include <sound_effect/sound_effect.h>

CSoundEffect::CSoundEffect(){
	memset(CSoundEffect::File,0,sizeof(CSoundEffect::File));
	memset(CSoundEffect::Flag,0,sizeof(CSoundEffect::Flag));
	memset(CSoundEffect::Info,0,sizeof(CSoundEffect::Info));
}

CSoundEffect::~CSoundEffect(){
	for(int i=0;i<CSoundEffect::MAX;i++){
		StopSoundMem(CSoundEffect::File[i]);
		DeleteSoundMem(CSoundEffect::File[i]);
	}
}

void CSoundEffect::SetVolume(int Volume){
	for(int i=0;i<CSoundEffect::MAX;i++){
		ChangeVolumeSoundMem(Volume*255/100,CSoundEffect::File[i]);
	}
}

void CSoundEffect::RaiseFlag(int Num){
	CSoundEffect::Flag[Num]=1;
}

void CSoundEffect::LoadSet(int SoundSet_Num){
	char Path[256] = { 0 }, SoundName[CSoundEffect::REN_START][16] = {
		"t_tetrimino", "j_tetrimino", "l_tetrimino", "z_tetrimino", "s_tetrimino", "i_tetrimino", "o_tetrimino", "lockdown", "hold", "canthold",
		"close", "single", "double", "triple", "tetris", "gameover", "gameclear", "levelup", "select", "cancel",
		"decide", "warning", "obstacle", "notice_0", "notice_1", "cascade_max"
	};
	SetCreateSoundDataType(DX_SOUNDDATATYPE_MEMNOPRESS);
	SoundSet_Num %= 100;
	for (int i = 0; i < CSoundEffect::MAX; i++){
		StopSoundMem(CSoundEffect::File[i]);
		DeleteSoundMem(CSoundEffect::File[i]);
	}
	for (int i = 0; i < CSoundEffect::REN_START; i++){
		sprintf_s(Path, sizeof(Path), "dat/se/set%02d/%s.ogg", SoundSet_Num, SoundName[i]);
		CSoundEffect::File[i] = LoadSoundMem(Path);
	}
	sprintf_s(Path, sizeof(Path), "dat/se/set%02d/info.txt", SoundSet_Num);
	if (int FP = FileRead_open(Path)){
		char Data[256] = { 0 };
		FileRead_gets(Data, sizeof(Data), FP);
		sscanf_s(Data, "%d,%d,%d", &CSoundEffect::Info[0], &CSoundEffect::Info[1], &CSoundEffect::Info[2]);
		FileRead_close(FP);
	}
	if (CSoundEffect::Info[0] >= 0){
		SetLoopSamplePosSoundMem(CSoundEffect::Info[0], CSoundEffect::File[CSoundEffect::GAMEOVER]);
	}
	if (CSoundEffect::Info[1] >= 0){
		SetLoopSamplePosSoundMem(CSoundEffect::Info[1], CSoundEffect::File[CSoundEffect::GAMECLEAR]);
	}
	if (CSoundEffect::Info[2]<0){
		CSoundEffect::Info[2] = 0;
	}
	if (CSoundEffect::Info[2]>20){
		CSoundEffect::Info[2] = 20;
	}
	for (int i = 0; i < CSoundEffect::Info[2]; i++){
		sprintf_s(Path, sizeof(Path), "dat/se/set%02d/ren%02d.ogg", SoundSet_Num, i + 1);
		CSoundEffect::File[CSoundEffect::REN_START + i] = LoadSoundMem(Path);
	}
}

void CSoundEffect::Play(){
	for(int i=0;i<CSoundEffect::MAX;i++){
		if(CSoundEffect::Flag[i]){
			if(i>=CSoundEffect::REN_START&&CSoundEffect::Info[2]<=0){
				continue;
			}
			else if(i>CSoundEffect::REN_START+CSoundEffect::Info[2]-1){
				PlaySoundMem(CSoundEffect::File[CSoundEffect::REN_START+CSoundEffect::Info[2]-1],DX_PLAYTYPE_BACK);
			}
			else if((i==CSoundEffect::GAMEOVER&&CSoundEffect::Info[0]>=0)||(i==CSoundEffect::GAMECLEAR&&CSoundEffect::Info[1]>=0)){
				PlaySoundMem(CSoundEffect::File[i],DX_PLAYTYPE_LOOP);
			}
			else {
				PlaySoundMem(CSoundEffect::File[i],DX_PLAYTYPE_BACK);
			}
			CSoundEffect::Flag[i]=0;
		}
	}
}

void CSoundEffect::Stop(int SoundFile_Num){
	StopSoundMem(CSoundEffect::File[SoundFile_Num]);
}