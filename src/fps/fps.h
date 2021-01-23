#ifndef FPS_H
#define FPS_H

class CFps{
public:
	static const int FRAME_RATE=60;
	CFps();
	void Wait();
	double Get();
private:
	int Count;
	int ZeroFrame;
	int Margin;
	double Average;
	int Child[FRAME_RATE];
	int Target[FRAME_RATE];
};

extern CFps Fps;

#endif