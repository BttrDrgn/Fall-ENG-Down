#include <cmath>
#include <DxLib.h>
#include <layer/layer.h>
#include <mathematics/mathematics.h>

const double PI = 3.1415926535897931;
const double PI2 = 6.2831853071795862;

CLayer::CLayer(){
	for(int i=0;i<CLayer::MAX;i++){
		memset(&CLayer::Main[i],0,sizeof(LayerMain_t));
		CLayer::Image[i]=0;
	}
	CLayer::TimeLine=0;
}

CLayer::~CLayer(){
	for(int i=0;i<CLayer::MAX;i++){
		DeleteGraph(CLayer::Image[i]);
	}
}

void CLayer::Initialize(){
	for(int i=0;i<CLayer::MAX;i++){
		DeleteGraph(CLayer::Image[i]);
		memset(&CLayer::Main[i],0,sizeof(LayerMain_t));
		CLayer::Image[i]=0;
	}
	CLayer::TimeLine=0;
}

void CLayer::LoadImage(int Image_Num,char Path[256]){
	DeleteGraph(CLayer::Image[Image_Num]);
	CLayer::Image[Image_Num]=LoadGraph(Path);
}

void CLayer::CopyImage(int Source=-1,int Target=-1){
	if(Source!=Target&&Source>=0&&Source<CLayer::MAX&&Target>=0&&Target<CLayer::MAX){
		CLayer::Image[Target]=CLayer::Image[Source];
	}
}

void CLayer::LoadInfo_Draw(int Image_Num,char Data[256]){
	sscanf_s(Data,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
		&CLayer::Main[Image_Num].Priority,&CLayer::Main[Image_Num].BlendMode,&CLayer::Main[Image_Num].BlendParam,
		&CLayer::Main[Image_Num].DrawX1,&CLayer::Main[Image_Num].DrawY1,&CLayer::Main[Image_Num].DrawX2,&CLayer::Main[Image_Num].DrawY2,
		&CLayer::Main[Image_Num].TransFlag,&CLayer::Main[Image_Num].TurnFlag,&CLayer::Main[Image_Num].QuakeFlag);
}

void CLayer::LoadInfo_XY(int Image_Num,char Data[256]){
	sscanf_s(Data,"%lf,%lf",&CLayer::Main[Image_Num].Motion[3].Value,&CLayer::Main[Image_Num].Motion[4].Value);
}

void CLayer::LoadInfo_Rota(int Image_Num,char Data[256]){
	sscanf_s(Data,"%d,%d,%lf,%lf,%lf,%lf,%lf",
		&CLayer::Main[Image_Num].DrawAngleFlag,&CLayer::Main[Image_Num].CenterFlag,&CLayer::Main[Image_Num].Motion[2].Value,
		&CLayer::Main[Image_Num].DrawAngle,&CLayer::Main[Image_Num].DrawVA,&CLayer::Main[Image_Num].CX,&CLayer::Main[Image_Num].CY);
	CLayer::Main[Image_Num].DrawMethod=1;
	CLayer::Main[Image_Num].DrawAngle=CLayer::Main[Image_Num].DrawAngle*PI/180.0;
	CLayer::Main[Image_Num].DrawVA=CLayer::Main[Image_Num].DrawVA*PI/180.0;
}

void CLayer::LoadInfo_Act(int Image_Num,char Data[256]){
	sscanf_s(Data,"%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf",
		&CLayer::Main[Image_Num].Motion[1].Value,&CLayer::Main[Image_Num].Motion[0].Value,
		&CLayer::Main[Image_Num].Motion[3].Velocity,&CLayer::Main[Image_Num].Motion[4].Velocity,&CLayer::Main[Image_Num].Motion[1].Velocity,&CLayer::Main[Image_Num].Motion[0].Velocity,&CLayer::Main[Image_Num].Motion[2].Velocity,
		&CLayer::Main[Image_Num].Motion[3].Option,&CLayer::Main[Image_Num].Motion[4].Option,&CLayer::Main[Image_Num].Motion[1].Option,&CLayer::Main[Image_Num].Motion[0].Option,&CLayer::Main[Image_Num].Motion[2].Option);
	CLayer::Main[Image_Num].ActFlag=1;
	CLayer::Main[Image_Num].Motion[0].Value=CLayer::Main[Image_Num].Motion[0].Value*PI/180.0;
	CLayer::Main[Image_Num].Motion[0].Velocity=CLayer::Main[Image_Num].Motion[0].Velocity*PI/180.0;
	CLayer::Main[Image_Num].Motion[0].Option=CLayer::Main[Image_Num].Motion[0].Option*PI/180.0;
	for(int i=0;i<5;i++){
		CLayer::Main[Image_Num].Motion[i].DefaultVelocity=CLayer::Main[Image_Num].Motion[i].Velocity;
	}
}

void CLayer::LoadInfo_Limit(int Image_Num,char Data[256]){
	sscanf_s(Data,"%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%d,%d,%d,%d,%d",
		&CLayer::Main[Image_Num].Motion[3].Min,
		&CLayer::Main[Image_Num].Motion[3].Max,
		&CLayer::Main[Image_Num].Motion[4].Min,
		&CLayer::Main[Image_Num].Motion[4].Max,
		&CLayer::Main[Image_Num].Motion[1].Min,
		&CLayer::Main[Image_Num].Motion[1].Max,
		&CLayer::Main[Image_Num].Motion[0].Min,
		&CLayer::Main[Image_Num].Motion[0].Max,
		&CLayer::Main[Image_Num].Motion[2].Min,
		&CLayer::Main[Image_Num].Motion[2].Max,
		&CLayer::Main[Image_Num].Motion[3].Type,
		&CLayer::Main[Image_Num].Motion[4].Type,
		&CLayer::Main[Image_Num].Motion[1].Type,
		&CLayer::Main[Image_Num].Motion[0].Type,
		&CLayer::Main[Image_Num].Motion[2].Type);
	CLayer::Main[Image_Num].Motion[0].Min=CLayer::Main[Image_Num].Motion[0].Min*PI/180.0;
	CLayer::Main[Image_Num].Motion[0].Max=CLayer::Main[Image_Num].Motion[0].Max*PI/180.0;
}

void CLayer::CopyInfo(int Source,int Target){
	if(Source!=Target&&Source>=0&&Source<CLayer::MAX&&Target>=0&&Target<CLayer::MAX){
		CLayer::Image[Target]=CLayer::Image[Source];
		memcpy_s(&CLayer::Main[Target],sizeof(CLayer::Main[Target]),&CLayer::Main[Source],sizeof(CLayer::Main[Source]));
	}
}

void CLayer::MotionCalc(int Image_Num,int Motion_Num){
	if(CLayer::Main[Image_Num].Motion[Motion_Num].Type==5)CLayer::Main[Image_Num].Motion[Motion_Num].Value=(CLayer::Main[Image_Num].Motion[Motion_Num].Max+CLayer::Main[Image_Num].Motion[Motion_Num].Min)/2.0+sin(PI*(TimeLine+CLayer::Main[Image_Num].Motion[Motion_Num].Option)*CLayer::Main[Image_Num].Motion[Motion_Num].Velocity)*(CLayer::Main[Image_Num].Motion[Motion_Num].Max-CLayer::Main[Image_Num].Motion[Motion_Num].Min)/2.0;
	else {
		CLayer::Main[Image_Num].Motion[Motion_Num].Velocity+=CLayer::Main[Image_Num].Motion[Motion_Num].Option;
		CLayer::Main[Image_Num].Motion[Motion_Num].Value+=CLayer::Main[Image_Num].Motion[Motion_Num].Velocity;
		if(Motion_Num==3)CLayer::Main[Image_Num].Motion[Motion_Num].Value+=cos(CLayer::Main[Image_Num].Motion[0].Value)*CLayer::Main[Image_Num].Motion[1].Value;
		else if(Motion_Num==4)CLayer::Main[Image_Num].Motion[Motion_Num].Value+=sin(CLayer::Main[Image_Num].Motion[0].Value)*CLayer::Main[Image_Num].Motion[1].Value;
		if(CLayer::Main[Image_Num].Motion[Motion_Num].Value>CLayer::Main[Image_Num].Motion[Motion_Num].Max){
			CLayer::Main[Image_Num].Motion[Motion_Num].Velocity=CLayer::Main[Image_Num].Motion[Motion_Num].DefaultVelocity;
			if(CLayer::Main[Image_Num].Motion[Motion_Num].Type==1){CLayer::Main[Image_Num].Motion[Motion_Num].Value=CLayer::Main[Image_Num].Motion[Motion_Num].Max;}
			else if(CLayer::Main[Image_Num].Motion[Motion_Num].Type==2){CLayer::Main[Image_Num].Motion[Motion_Num].Value=CLayer::Main[Image_Num].Motion[Motion_Num].Min;}
			else if(CLayer::Main[Image_Num].Motion[Motion_Num].Type==3){CLayer::Main[Image_Num].Motion[Motion_Num].Value=CLayer::Main[Image_Num].Motion[Motion_Num].Max;CLayer::Main[Image_Num].Motion[Motion_Num].Velocity=fabs(CLayer::Main[Image_Num].Motion[Motion_Num].Velocity)*(-1.0);}
			else if(CLayer::Main[Image_Num].Motion[Motion_Num].Type==4){CLayer::Main[Image_Num].Motion[Motion_Num].Value=CLayer::Main[Image_Num].Motion[Motion_Num].Min+GetRandF(CLayer::Main[Image_Num].Motion[Motion_Num].Max-CLayer::Main[Image_Num].Motion[Motion_Num].Min);}
			else if(CLayer::Main[Image_Num].Motion[Motion_Num].Type==6){CLayer::Main[Image_Num].Motion[Motion_Num].Value=CLayer::Main[Image_Num].Motion[Motion_Num].Max;}
			else if(CLayer::Main[Image_Num].Motion[Motion_Num].Type==7){CLayer::Main[Image_Num].Motion[Motion_Num].Value=CLayer::Main[Image_Num].Motion[Motion_Num].Max;}
			else if(CLayer::Main[Image_Num].Motion[Motion_Num].Type==8){CLayer::Main[Image_Num].Motion[Motion_Num].Value=CLayer::Main[Image_Num].Motion[Motion_Num].Min;}
			if((Motion_Num==3||Motion_Num==4)&&(CLayer::Main[Image_Num].Motion[Motion_Num].Type==7||CLayer::Main[Image_Num].Motion[Motion_Num].Type==8)){
				CLayer::Main[Image_Num].Motion[7-Motion_Num].Value=CLayer::Main[Image_Num].Motion[7-Motion_Num].Min+GetRandF(CLayer::Main[Image_Num].Motion[7-Motion_Num].Max-CLayer::Main[Image_Num].Motion[7-Motion_Num].Min);
			}
			if(CLayer::Main[Image_Num].Motion[Motion_Num].Type==6){
				if(Motion_Num==3){
					CLayer::Main[Image_Num].Motion[0].Value=PI-CLayer::Main[Image_Num].Motion[0].Value;
				}
				else if(Motion_Num==4){
					CLayer::Main[Image_Num].Motion[0].Value=PI2-CLayer::Main[Image_Num].Motion[0].Value;
				}
			}
		}
		else if(CLayer::Main[Image_Num].Motion[Motion_Num].Value<CLayer::Main[Image_Num].Motion[Motion_Num].Min){
			CLayer::Main[Image_Num].Motion[Motion_Num].Velocity=CLayer::Main[Image_Num].Motion[Motion_Num].DefaultVelocity;
			if(CLayer::Main[Image_Num].Motion[Motion_Num].Type==1){CLayer::Main[Image_Num].Motion[Motion_Num].Value=CLayer::Main[Image_Num].Motion[Motion_Num].Min;}
			else if(CLayer::Main[Image_Num].Motion[Motion_Num].Type==2){CLayer::Main[Image_Num].Motion[Motion_Num].Value=CLayer::Main[Image_Num].Motion[Motion_Num].Max;}
			else if(CLayer::Main[Image_Num].Motion[Motion_Num].Type==3){CLayer::Main[Image_Num].Motion[Motion_Num].Value=CLayer::Main[Image_Num].Motion[Motion_Num].Min;CLayer::Main[Image_Num].Motion[Motion_Num].Velocity=fabs(CLayer::Main[Image_Num].Motion[Motion_Num].Velocity);}
			else if(CLayer::Main[Image_Num].Motion[Motion_Num].Type==4){CLayer::Main[Image_Num].Motion[Motion_Num].Value=CLayer::Main[Image_Num].Motion[Motion_Num].Min+GetRandF(CLayer::Main[Image_Num].Motion[Motion_Num].Max-CLayer::Main[Image_Num].Motion[Motion_Num].Min);}
			else if(CLayer::Main[Image_Num].Motion[Motion_Num].Type==6){CLayer::Main[Image_Num].Motion[Motion_Num].Value=CLayer::Main[Image_Num].Motion[Motion_Num].Min;}
			else if(CLayer::Main[Image_Num].Motion[Motion_Num].Type==7){CLayer::Main[Image_Num].Motion[Motion_Num].Value=CLayer::Main[Image_Num].Motion[Motion_Num].Min;}
			else if(CLayer::Main[Image_Num].Motion[Motion_Num].Type==8){CLayer::Main[Image_Num].Motion[Motion_Num].Value=CLayer::Main[Image_Num].Motion[Motion_Num].Max;}
			if((Motion_Num==3||Motion_Num==4)&&(CLayer::Main[Image_Num].Motion[Motion_Num].Type==7||CLayer::Main[Image_Num].Motion[Motion_Num].Type==8)){
				CLayer::Main[Image_Num].Motion[7-Motion_Num].Value=CLayer::Main[Image_Num].Motion[7-Motion_Num].Min+GetRandF(CLayer::Main[Image_Num].Motion[7-Motion_Num].Max-CLayer::Main[Image_Num].Motion[7-Motion_Num].Min);
			}
			if(CLayer::Main[Image_Num].Motion[Motion_Num].Type==6){
				if(Motion_Num==3){
					CLayer::Main[Image_Num].Motion[0].Value=PI-CLayer::Main[Image_Num].Motion[0].Value;
				}
				else if(Motion_Num==4){
					CLayer::Main[Image_Num].Motion[0].Value=PI2-CLayer::Main[Image_Num].Motion[0].Value;
				}
			}
		}
	}
}	

void CLayer::Draw(int Priority,int LayerNum,int TimeLine,int QuakeX,int QuakeY){
	if(CLayer::Main[LayerNum].Priority==Priority){
		int QX=0,QY=0;
		CLayer::TimeLine=TimeLine;
		SetDrawBlendMode(CLayer::Main[LayerNum].BlendMode,CLayer::Main[LayerNum].BlendParam);
		SetDrawArea(CLayer::Main[LayerNum].DrawX1,CLayer::Main[LayerNum].DrawY1,CLayer::Main[LayerNum].DrawX2,CLayer::Main[LayerNum].DrawY2);
		if(CLayer::Main[LayerNum].DrawMethod==0){
			SetDrawMode(DX_DRAWMODE_NEAREST);
		}
		else {
			SetDrawMode(DX_DRAWMODE_BILINEAR);
		}
		if(CLayer::Main[LayerNum].QuakeFlag){
			QX=QuakeX;
			QY=QuakeY;
		}
		if(CLayer::Main[LayerNum].ActFlag){
			for(int j=0;j<5;j++){
				CLayer::MotionCalc(LayerNum,j);
			}
		}
		if(CLayer::Main[LayerNum].DrawMethod){
			CLayer::Main[LayerNum].DrawAngle+=CLayer::Main[LayerNum].DrawVA;
			if(CLayer::Main[LayerNum].DrawAngle>=PI2){
				CLayer::Main[LayerNum].DrawAngle-=PI2;
			}
			else if(CLayer::Main[LayerNum].DrawAngle<0){
				CLayer::Main[LayerNum].DrawAngle+=PI2;
			}
			if(CLayer::Main[LayerNum].CenterFlag){
				DrawRotaGraph2F((float)(QX+CLayer::Main[LayerNum].Motion[3].Value),(float)(QY+CLayer::Main[LayerNum].Motion[4].Value),(float)CLayer::Main[LayerNum].CX,(float)CLayer::Main[LayerNum].CY,CLayer::Main[LayerNum].Motion[2].Value,CLayer::Main[LayerNum].DrawAngleFlag?CLayer::Main[LayerNum].DrawAngle:CLayer::Main[LayerNum].Motion[0].Value,CLayer::Image[LayerNum],CLayer::Main[LayerNum].TransFlag,CLayer::Main[LayerNum].TurnFlag);
			}
			else {
				DrawRotaGraphF((float)(QX+CLayer::Main[LayerNum].Motion[3].Value),(float)(QY+CLayer::Main[LayerNum].Motion[4].Value),CLayer::Main[LayerNum].Motion[2].Value,CLayer::Main[LayerNum].DrawAngleFlag?CLayer::Main[LayerNum].DrawAngle:CLayer::Main[LayerNum].Motion[0].Value,CLayer::Image[LayerNum],CLayer::Main[LayerNum].TransFlag,CLayer::Main[LayerNum].TurnFlag);
			}
		}
		else {
			if(CLayer::Main[LayerNum].TurnFlag){
				DrawTurnGraphF((float)(QX+CLayer::Main[LayerNum].Motion[3].Value),(float)(QY+CLayer::Main[LayerNum].Motion[4].Value),CLayer::Image[LayerNum],CLayer::Main[LayerNum].TransFlag);
			}
			else {
				DrawGraphF((float)(QX+CLayer::Main[LayerNum].Motion[3].Value),(float)(QY+CLayer::Main[LayerNum].Motion[4].Value),CLayer::Image[LayerNum],CLayer::Main[LayerNum].TransFlag);
			}
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
	SetDrawArea(0,0,640,480);
	SetDrawMode(DX_DRAWMODE_NEAREST);
}