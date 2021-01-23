#ifndef SPEED_H
#define SPEED_H

class CSpeed{
public:
	static const int SIZE=3600;
	CSpeed();
	void Initialize();
	void Record(int TimeLine);
	int Calc(int TimeLine);
private:
	int Point[SIZE];
	int Index;
};

extern CSpeed Tetrimino_Speed;
extern CSpeed Line_Speed;

#endif