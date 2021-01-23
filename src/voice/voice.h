#ifndef VOICE_H
#define VOICE_H

class CVoice{
public:
	CVoice();
	~CVoice();
	static const int MAX=13;
	void SetVolume(int Volume);
	void RaiseFlag(int Num);
	void LoadSet();
	void Play();
private:
	int File[MAX];
	int Flag[MAX];
};

extern CVoice Voice;

#endif