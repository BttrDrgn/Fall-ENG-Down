#ifndef BGM_H
#define BGM_H

class CBgm{
public:
	CBgm();
	~CBgm();
	void Stop();
	int Play(char Path[256],int Volume,int LoopPoint);
private:
	int File;
	char PlayingPath[256];
};

extern CBgm Bgm;

#endif