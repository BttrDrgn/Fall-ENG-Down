#ifndef DROP_H
#define DROP_H

class CDrop{
public:
	CDrop();
	~CDrop();
	void Initialize();
	void Draw(int pattern, int amount, double size, double speed, double x1, double y1, double x2, double y2);
private:
	int progress;
	int graph[9][3];
	int flag[100];
	int pattern[100];
	int patternChild[100];
	double count[100];
	double x[100];
	double y[100];
	double gAngle[100];
	double vAngle[100];
	double gSpeed[100];
	double vSpeed[100];
	double exRate[100];

};

extern CDrop Drop;

#endif