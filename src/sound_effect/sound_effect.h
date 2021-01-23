#ifndef SOUND_EFFECT_H
#define SOUND_EFFECT_H

class CSoundEffect{
public:
	CSoundEffect();
	~CSoundEffect();
	static const int MAX=50;
	static const int REN_START=26;
	static const int GAMEOVER=15;
	static const int GAMECLEAR=16;
	void SetVolume(int Volume);
	void RaiseFlag(int Num);
	void LoadSet(int SoundSet_Num);
	void Play();
	void Stop(int SoundFile_Num);
private:
	int File[MAX];
	int Flag[MAX];
	int Info[3];
};

extern CSoundEffect SoundEffect;

#endif