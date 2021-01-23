#ifndef LAYER_H
#define LAYER_H

typedef struct{
	double Value;
	double Velocity;
	double DefaultVelocity;
	double Min;
	double Max;
	double Option;
	int Type;
}LayerMotion_t;

typedef struct{
	int Priority;
	int BlendMode,BlendParam;
	double DrawAngle,DrawVA;
	double CX,CY;
	LayerMotion_t Motion[5];
	int DrawX1,DrawY1,DrawX2,DrawY2;
	int DrawMethod;
	int DrawAngleFlag;
	int CenterFlag;
	int ActFlag;
	int TurnFlag;
	int TransFlag;
	int QuakeFlag;
}LayerMain_t;

class CLayer{
public:
	CLayer();
	~CLayer();
	static const int MAX=100;
	void Initialize();
	void LoadImage(int Image_Num,char Path[256]);
	void CopyImage(int Source,int Target);
	void LoadInfo_Draw(int Image_Num,char Data[256]);
	void LoadInfo_XY(int Image_Num,char Data[256]);
	void LoadInfo_Rota(int Image_Num,char Data[256]);
	void LoadInfo_Act(int Image_Num,char Data[256]);
	void LoadInfo_Limit(int Image_Num,char Data[256]);
	void CopyInfo(int Source=-1,int Target=-1);
	void MotionCalc(int Image_Num,int Motion_Num);
	void Draw(int Priority,int LayerNum,int TimeLine,int QuakeX,int QuakeY);
private:
	LayerMain_t Main[MAX];
	int Image[MAX];
	int TimeLine;
};

extern CLayer Layer;

#endif