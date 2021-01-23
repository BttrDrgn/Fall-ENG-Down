#include <cmath>
#include <DxLib.h>
#include <animation/animation.h>
#include <mathematics/mathematics.h>

const double PI = 3.1415926535897931;
const double PI2 = 6.2831853071795862;
const double ROOT2 = 1.4142135623730951;

void CAnimation::CalcWater(int cnt){
	for(int i=0;i<CAnimation::WATER_MAX;i++){
		if(CAnimation::Water[i].Flag){
			CAnimation::Water[i].VY+=1.0/30.0;
			CAnimation::Water[i].VX*=0.995;
			CAnimation::Water[i].X+=CAnimation::Water[i].VX;
			CAnimation::Water[i].Y+=CAnimation::Water[i].VY;
			if(CAnimation::Water[i].Y>CAnimation::Water[i].TargetY){
				for(int j=-1;j<2;j+=2){
					for(int k=0;k<CAnimation::WATER_MAX;k++){
						if(!CAnimation::Water[k].Flag){
							memset(&CAnimation::Water[k],0,sizeof(Water_t));
							CAnimation::Water[k].Flag=1;
							CAnimation::Water[k].X=CAnimation::Water[i].X;
							CAnimation::Water[k].Y=CAnimation::Water[i].Y;
							CAnimation::Water[k].R=CAnimation::Water[i].R/ROOT2;
							CAnimation::Water[k].VX=CAnimation::Water[i].VY/5.0*j;
							CAnimation::Water[k].VY=-1.0;
							CAnimation::Water[k].TargetY=CAnimation::Water[k].Y+120+GetRand(240);
							k=CAnimation::WATER_MAX;
						}
					}
				}
				memset(&CAnimation::Water[i],0,sizeof(Water_t));
			}
		}
	}
	for(int i=0;i<CAnimation::WATER_MAX;i++){
		if(CAnimation::Water[i].Flag){
			if(CAnimation::Water[i].Y-70*CAnimation::Water[i].R>480||CAnimation::Water[i].X+70*CAnimation::Water[i].R<0||CAnimation::Water[i].X-70*CAnimation::Water[i].R>640){
				memset(&CAnimation::Water[i],0,sizeof(Water_t));
			}
		}
	}
	if(cnt%30==0){
		for(int i=0;i<CAnimation::WATER_MAX;i++){
			if(!CAnimation::Water[i].Flag){
				memset(&CAnimation::Water[i],0,sizeof(Water_t));
				CAnimation::Water[i].Flag=1;
				CAnimation::Water[i].R=0.5+Rang(ROOT2/8.0);
				CAnimation::Water[i].VY=1.0+Rang(1.0);
				CAnimation::Water[i].VX=0.0;
				CAnimation::Water[i].X=320.0+Rang(320+70*CAnimation::Water[i].R);
				CAnimation::Water[i].Y=GetRand(100)-100-70*CAnimation::Water[i].R;
				CAnimation::Water[i].TargetY=CAnimation::Water[i].Y+120+GetRand(240);
				i=CAnimation::WATER_MAX;
			}
		}
	}
}

void CAnimation::BlossomInitialize(){
	memset(CAnimation::Blossom,0,sizeof(Blossom_t)*CAnimation::BLOSSOM_MAX);
	for(int i=0;i<CAnimation::BLOSSOM_MAX;i++){
		CAnimation::Blossom[i].Sp=(GetRand(8000)+10000)*0.0001;
		CAnimation::Blossom[i].VA=GetRand(500)+500;
		CAnimation::Blossom[i].R=(GetRand(6000)+6000)*0.0001;
		CAnimation::Blossom[i].X=GetRand(720)-40;
		double min=-100-50*CAnimation::Blossom[i].R;
		double max=480+50*CAnimation::Blossom[i].R;
		CAnimation::Blossom[i].Y=GetRand((int)(max-min))+min;
	}
}

void CAnimation::FireflyInitialize(){
	memset(CAnimation::Firefly,0,sizeof(Firefly_t)*CAnimation::FIREFLY_MAX);
	for(int i=0;i<CAnimation::FIREFLY_MAX;i++){
		CAnimation::Firefly[i].Count=GetRand(20);
		CAnimation::Firefly[i].X=320+Rang(360);
		CAnimation::Firefly[i].Y=240+Rang(280);
		CAnimation::Firefly[i].Sp=1.0+Rang(0.25);
		CAnimation::Firefly[i].Ang=Rang(PI);
		CAnimation::Firefly[i].VVA=Rang(PI/3000);
		CAnimation::Firefly[i].VVS=Rang(0.0002);
		CAnimation::Firefly[i].VA=Rang(PI/90);
		CAnimation::Firefly[i].VS=Rang(0.01);
	}
}

void CAnimation::WaterInitialize(){
	memset(CAnimation::Water,0,sizeof(Water_t)*CAnimation::WATER_MAX);
	for(int i=0;i<300;i++)CalcWater(i);
}

void CAnimation::SeaInitialize(){
	memset(CAnimation::Bubble,0,sizeof(Bubble_t)*CAnimation::BUBBLE_MAX);
	for(int i=0;i<CAnimation::BUBBLE_MAX;i++){
		CAnimation::Bubble[i].R=0.75+Rang(0.25);
		CAnimation::Bubble[i].X=GetRand(740)-50;
		double min=0-100*CAnimation::Bubble[i].R;
		double max=480+200+100*CAnimation::Bubble[i].R;
		CAnimation::Bubble[i].Y=GetRand((int)(max-min))+min;
		CAnimation::Bubble[i].Ang=-PI/2+Rang(PI/16);
		CAnimation::Bubble[i].Dir=Rang(PI);
		CAnimation::Bubble[i].Sp=1.1+Rang(0.1);
		CAnimation::Bubble[i].Clock=GetRand(40)+50;
	}
	memset(CAnimation::Fish,0,sizeof(Fish_t)*CAnimation::FISH_MAX);
	for(int i=0;i<CAnimation::FISH_MAX;i++){
		CAnimation::Fish[i].R=0.4+Rang(0.2);
		CAnimation::Fish[i].Type=GetRand(2)+1;
		CAnimation::Fish[i].VXMax=3+Rang(0.5);
		CAnimation::Fish[i].VXMin=1+Rang(0.5);
		CAnimation::Fish[i].Drag=0.99+Rang(0.005);
		double min=CAnimation::Fish[i].VXMin*1000;
		double max=(CAnimation::Fish[i].VXMax+Rang(0.25))*1000;
		CAnimation::Fish[i].VX=GetRand((int)(max-min))+min;
		CAnimation::Fish[i].VX*=0.001;
		min=0-340*CAnimation::Fish[i].R;
		max=640+100+340*CAnimation::Fish[i].R;
		CAnimation::Fish[i].X=GetRand((int)(max-min))+min;
		CAnimation::Fish[i].Y=GetRand(480);
	}
}

void CAnimation::DragonflyInitialize(){
	memset(CAnimation::Dragonfly,0,sizeof(Dragonfly_t)*CAnimation::DRAGONFLY_MAX);
	for(int i=0;i<CAnimation::DRAGONFLY_MAX;i++){
		CAnimation::Dragonfly[i].LapCount=60+GetRand(180);
		CAnimation::Dragonfly[i].Count=GetRand(CAnimation::Dragonfly[i].LapCount);
		CAnimation::Dragonfly[i].R=0.5+Rang(0.15);
		CAnimation::Dragonfly[i].Sp=2.0+Rang(0.5);
		CAnimation::Dragonfly[i].FlapSp=(CAnimation::Dragonfly[i].Sp+2.0)/2.0;
		CAnimation::Dragonfly[i].Ang=PI2+Rang(PI/8);
		CAnimation::Dragonfly[i].VA=Rang(PI/8)/60;
		double min=-200-140*CAnimation::Dragonfly[i].R;
		double max=640+140*CAnimation::Dragonfly[i].R;
		CAnimation::Dragonfly[i].X=GetRand((int)(max-min))+min;
		CAnimation::Dragonfly[i].Y=240+Rang(240+140*CAnimation::Dragonfly[i].R);
	}
}

void CAnimation::LeafInitialize(){
	memset(CAnimation::Leaf,0,sizeof(Leaf_t)*CAnimation::LEAF_MAX);
	for(int i=0;i<CAnimation::LEAF_MAX;i++){
		CAnimation::Leaf[i].R=0.5+Rang(0.1);
		CAnimation::Leaf[i].Dir=Rang(PI);
		CAnimation::Leaf[i].Ang=PI/2+PI/8+Rang(PI/16);
		CAnimation::Leaf[i].Turn=GetRand(1);
		CAnimation::Leaf[i].Type=GetRand(1);
		CAnimation::Leaf[i].Clock=80+GetRand(20);
		CAnimation::Leaf[i].Sp=1.6+Rang(0.2);
		CAnimation::Leaf[i].X=420+Rang(420+100*CAnimation::Leaf[i].R);
		double min=-100-100*CAnimation::Leaf[i].R;
		double max=640+100*CAnimation::Leaf[i].R;
		CAnimation::Leaf[i].Y=GetRand((int)(max-min))+min;
	}
}

void CAnimation::FireInitialize(){
	memset(CAnimation::Fire,0,sizeof(Fire_t)*CAnimation::FIRE_MAX);
}

void CAnimation::IceInitialize(){
	memset(CAnimation::Ice,0,sizeof(Ice_t)*CAnimation::ICE_MAX);
	for(int i=0;i<CAnimation::ICE_MAX;i++){
		double min,max;
		CAnimation::Ice[i].Sp=(GetRand(10000)+12000)*0.0001;
		CAnimation::Ice[i].VA=GetRand(400)+400;
		CAnimation::Ice[i].Dir=GetRand(2)*2-1;
		CAnimation::Ice[i].R=(GetRand(1600)+1600)*0.0001;
		CAnimation::Ice[i].Ang=atan2(480.0,480.0-160.0)+Rang(PI/16.0);
		min=0-200*CAnimation::Ice[i].R;
		max=640+200*CAnimation::Ice[i].R;
		CAnimation::Ice[i].X=GetRand((int)(max-min))+min;
		min=0-200*CAnimation::Ice[i].R;
		max=480+200*CAnimation::Ice[i].R;
		CAnimation::Ice[i].Y=GetRand((int)(max-min))+min;
		CAnimation::Ice[i].Type=GetRand(3);
	}
}

void CAnimation::TreeInitialize(){
	memset(CAnimation::Twig,0,sizeof(Twig_t)*CAnimation::TWIG_MAX);
	memset(CAnimation::Bud,0,sizeof(Bud_t)*CAnimation::BUD_MAX);
}

void CAnimation::DrawWheel(){
	for(int i=0;i<5;i++)DrawRotaGraph2(120,400,44,93,1.0,CAnimation::TimeLine%800/800.0*2.0*PI+2.0*PI*i/5.0,CAnimation::Image[0],FALSE);
	for(int i=0;i<9;i++)DrawRotaGraph2(120,400,39,152,1.0,CAnimation::TimeLine%1280/1280.0*(-2.0)*PI+2.0*PI*i/9.0,CAnimation::Image[1],FALSE);
	for(int i=0;i<16;i++)DrawRotaGraph2(120,400,22,432,1.0,CAnimation::TimeLine%1600/1600.0*2.0*PI+2.0*PI*i/16.0,CAnimation::Image[2],FALSE);
}

void CAnimation::DrawBlossom(){
	for(int i=0;i<CAnimation::BLOSSOM_MAX;i++){
		if(CAnimation::Blossom[i].Y-50*CAnimation::Blossom[i].R>480){
			CAnimation::Blossom[i].Sp=(GetRand(8000)+10000)*0.0001;
			CAnimation::Blossom[i].VA=GetRand(500)+500;
			CAnimation::Blossom[i].R=(GetRand(6000)+6000)*0.0001;
			CAnimation::Blossom[i].X=GetRand(720)-40;
			CAnimation::Blossom[i].Y=GetRand(100)-100-50*CAnimation::Blossom[i].R;
		}
		DrawRotaGraphF((float)CAnimation::Blossom[i].X,(float)CAnimation::Blossom[i].Y,CAnimation::Blossom[i].R,0.0,CAnimation::Image[0],FALSE);
		for(int j=0;j<5;j++){
			DrawRotaGraph2F((float)CAnimation::Blossom[i].X,(float)CAnimation::Blossom[i].Y,(float)16.0,(float)48.0,CAnimation::Blossom[i].R,((double)(CAnimation::TimeLine%CAnimation::Blossom[i].VA))/CAnimation::Blossom[i].VA*2.0*PI*(i%2*2-1)+2.0*PI*j/5.0,CAnimation::Image[1],FALSE);
		}
		CAnimation::Blossom[i].Y+=CAnimation::Blossom[i].Sp;
	}
}

void CAnimation::DrawFirefly(){
	for(int i=0;i<CAnimation::FIREFLY_MAX;i++){
		CAnimation::Firefly[i].Count++;
		if(GetRand(100-CAnimation::Firefly[i].Count)<2){
			CAnimation::Firefly[i].VVA=Rang(PI/6000);
			CAnimation::Firefly[i].VVS=Rang(0.0002);
			CAnimation::Firefly[i].Count=0;
		}
		CAnimation::Firefly[i].VA+=CAnimation::Firefly[i].VVA;
		if(CAnimation::Firefly[i].VA>PI/90)CAnimation::Firefly[i].VA=PI/90;
		if(CAnimation::Firefly[i].VA<-PI/90)CAnimation::Firefly[i].VA=-PI/90;
		CAnimation::Firefly[i].VS+=CAnimation::Firefly[i].VVS;
		if(CAnimation::Firefly[i].VS>0.01)CAnimation::Firefly[i].VS=0.01;
		if(CAnimation::Firefly[i].VS<-0.01)CAnimation::Firefly[i].VS=-0.01;
		CAnimation::Firefly[i].Ang+=CAnimation::Firefly[i].VA;
		CAnimation::Firefly[i].Sp+=CAnimation::Firefly[i].VS;
		if(CAnimation::Firefly[i].Sp>1.25)CAnimation::Firefly[i].Sp=1.5;
		if(CAnimation::Firefly[i].Sp<0.75)CAnimation::Firefly[i].Sp=1.0;
		CAnimation::Firefly[i].X+=cos(CAnimation::Firefly[i].Ang)*CAnimation::Firefly[i].Sp;
		CAnimation::Firefly[i].Y+=sin(CAnimation::Firefly[i].Ang)*CAnimation::Firefly[i].Sp;
		if(CAnimation::Firefly[i].X+35*CAnimation::Firefly[i].R<-40||CAnimation::Firefly[i].X-35*CAnimation::Firefly[i].R>680||CAnimation::Firefly[i].Y+35*CAnimation::Firefly[i].R<-40||CAnimation::Firefly[i].Y-35*CAnimation::Firefly[i].R>520){
			CAnimation::Firefly[i].Ang=atan2(240-CAnimation::Firefly[i].Y,320-CAnimation::Firefly[i].X)+Rang(PI/6);
			CAnimation::Firefly[i].VA/=3;
		}
		CAnimation::Firefly[i].R=(sin(PI*(CAnimation::TimeLine+i*(240.0/CAnimation::FIREFLY_MAX))/120.0)*0.5+1.0)*0.5;
		DrawRotaGraphF((float)CAnimation::Firefly[i].X,(float)CAnimation::Firefly[i].Y,CAnimation::Firefly[i].R,CAnimation::Firefly[i].Ang,CAnimation::Image[0],FALSE);
	}
}

void CAnimation::DrawWater(){
	CalcWater(CAnimation::TimeLine);
	for(int i=0;i<CAnimation::WATER_MAX;i++){
		if(CAnimation::Water[i].Flag){
			DrawRotaGraphF((float)CAnimation::Water[i].X,(float)CAnimation::Water[i].Y,CAnimation::Water[i].R,atan2(CAnimation::Water[i].VY,CAnimation::Water[i].VX)-PI/2.0,CAnimation::Image[0],FALSE);
		}
	}
}

void CAnimation::DrawSea(){
	for(int i=0;i<CAnimation::BUBBLE_MAX;i++){
		if(CAnimation::Bubble[i].Y+100*CAnimation::Bubble[i].R<0){
			CAnimation::Bubble[i].R=0.75+Rang(0.25);
			CAnimation::Bubble[i].X=GetRand(740)-50;
			CAnimation::Bubble[i].Y=480+GetRand(200)+100*CAnimation::Bubble[i].R;
			CAnimation::Bubble[i].Ang=-PI/2+Rang(PI/16);
			CAnimation::Bubble[i].Dir=Rang(PI);
			CAnimation::Bubble[i].Sp=1.1+Rang(0.1);
			CAnimation::Bubble[i].Clock=GetRand(40)+50;
		}
		DrawRotaGraphF((float)CAnimation::Bubble[i].X,(float)CAnimation::Bubble[i].Y,CAnimation::Bubble[i].R,CAnimation::Bubble[i].Dir+sin(CAnimation::TimeLine%CAnimation::Bubble[i].Clock*PI*2.0/CAnimation::Bubble[i].Clock)*PI/16.0,CAnimation::Image[0],FALSE);
		CAnimation::Bubble[i].Y+=sin(CAnimation::Bubble[i].Ang+sin(CAnimation::TimeLine%CAnimation::Bubble[i].Clock*PI*2.0/CAnimation::Bubble[i].Clock)*PI/16.0)*CAnimation::Bubble[i].Sp;
		CAnimation::Bubble[i].X+=cos(CAnimation::Bubble[i].Ang+sin(CAnimation::TimeLine%CAnimation::Bubble[i].Clock*PI*2.0/CAnimation::Bubble[i].Clock)*PI/16.0)*CAnimation::Bubble[i].Sp;
	}
	for(int i=0;i<CAnimation::FISH_MAX;i++){
		if(CAnimation::Fish[i].X+340*CAnimation::Fish[i].R<0){
			double min,max;
			CAnimation::Fish[i].R=0.4+Rang(0.2);
			CAnimation::Fish[i].Type=GetRand(2)+1;
			CAnimation::Fish[i].VXMax=3+Rang(0.5);
			CAnimation::Fish[i].VXMin=1+Rang(0.5);
			CAnimation::Fish[i].Drag=0.99+Rang(0.005);
			min=CAnimation::Fish[i].VXMin*1000;
			max=(CAnimation::Fish[i].VXMax+Rang(0.25))*1000;
			CAnimation::Fish[i].VX=GetRand((int)(max-min))+min;
			CAnimation::Fish[i].VX*=0.001;
			CAnimation::Fish[i].X=640+GetRand(100)+340*CAnimation::Fish[i].R;
			CAnimation::Fish[i].Y=GetRand(480);
		}
		DrawRotaGraphF((float)CAnimation::Fish[i].X,(float)CAnimation::Fish[i].Y,CAnimation::Fish[i].R,0.0,CAnimation::Image[CAnimation::Fish[i].Type],FALSE);
		CAnimation::Fish[i].X-=CAnimation::Fish[i].VX;
		CAnimation::Fish[i].VX*=CAnimation::Fish[i].Drag;
		if(CAnimation::Fish[i].VX<CAnimation::Fish[i].VXMin)CAnimation::Fish[i].VX=CAnimation::Fish[i].VXMax+Rang(0.25);
	}
}

void CAnimation::DrawDragonfly(){
	for(int i=0;i<CAnimation::DRAGONFLY_MAX;i++){
		if(CAnimation::Dragonfly[i].Y+140*CAnimation::Dragonfly[i].R<0||CAnimation::Dragonfly[i].Y-140*CAnimation::Dragonfly[i].R>480||CAnimation::Dragonfly[i].X-140*CAnimation::Dragonfly[i].R>640){
			CAnimation::Dragonfly[i].LapCount=60+GetRand(180);
			CAnimation::Dragonfly[i].Count=GetRand(CAnimation::Dragonfly[i].LapCount);
			CAnimation::Dragonfly[i].R=0.5+Rang(0.15);
			CAnimation::Dragonfly[i].Sp=2.0+Rang(0.5);
			CAnimation::Dragonfly[i].FlapSp=(CAnimation::Dragonfly[i].Sp+2.0)/2.0;
			CAnimation::Dragonfly[i].Ang=PI2+Rang(PI/8);
			CAnimation::Dragonfly[i].VA=Rang(PI/8)/60;
			CAnimation::Dragonfly[i].X=Rang(100)-100-140*CAnimation::Dragonfly[i].R;
			CAnimation::Dragonfly[i].Y=240+Rang(240+140*CAnimation::Dragonfly[i].R);
		}
		double target_x,target_y,target_ang;
		target_x=CAnimation::Dragonfly[i].X+640;
		target_y=CAnimation::Dragonfly[i].Y+sin(PI2*CAnimation::Dragonfly[i].Count/CAnimation::Dragonfly[i].LapCount)*240;
		target_ang=atan2(target_y-CAnimation::Dragonfly[i].Y,target_x-CAnimation::Dragonfly[i].X);
		CAnimation::Dragonfly[i].Ang+=CAnimation::Dragonfly[i].VA;
		CAnimation::Dragonfly[i].Ang=AppointCross(target_ang,CAnimation::Dragonfly[i].Ang,0.025);
		CAnimation::Dragonfly[i].X+=cos(CAnimation::Dragonfly[i].Ang)*CAnimation::Dragonfly[i].Sp;
		CAnimation::Dragonfly[i].Y+=sin(CAnimation::Dragonfly[i].Ang)*CAnimation::Dragonfly[i].Sp;
		DrawRotaGraph2F((float)CAnimation::Dragonfly[i].X,(float)CAnimation::Dragonfly[i].Y,(float)140,(float)25,CAnimation::Dragonfly[i].R,CAnimation::Dragonfly[i].Ang,CAnimation::Image[0],FALSE);
		DrawRotaGraph2F((float)CAnimation::Dragonfly[i].X,(float)CAnimation::Dragonfly[i].Y,(float)45,(float)85,CAnimation::Dragonfly[i].R,CAnimation::Dragonfly[i].Ang+sin(PI2*CAnimation::Dragonfly[i].FlapSp*CAnimation::Dragonfly[i].Count*0.01-PI/2)*PI/12,CAnimation::Image[1],FALSE);
		DrawRotaGraph2F((float)CAnimation::Dragonfly[i].X,(float)CAnimation::Dragonfly[i].Y,(float)7,(float)7,CAnimation::Dragonfly[i].R,CAnimation::Dragonfly[i].Ang-sin(PI2*CAnimation::Dragonfly[i].FlapSp*CAnimation::Dragonfly[i].Count*0.01-PI/2)*PI/12,CAnimation::Image[2],FALSE);
		DrawRotaGraph2F((float)CAnimation::Dragonfly[i].X,(float)CAnimation::Dragonfly[i].Y,(float)80,(float)73,CAnimation::Dragonfly[i].R,CAnimation::Dragonfly[i].Ang+sin(PI2*CAnimation::Dragonfly[i].FlapSp*CAnimation::Dragonfly[i].Count*0.01)*PI/12,CAnimation::Image[3],FALSE);
		DrawRotaGraph2F((float)CAnimation::Dragonfly[i].X,(float)CAnimation::Dragonfly[i].Y,(float)9,(float)6,CAnimation::Dragonfly[i].R,CAnimation::Dragonfly[i].Ang-sin(PI2*CAnimation::Dragonfly[i].FlapSp*CAnimation::Dragonfly[i].Count*0.01)*PI/12,CAnimation::Image[4],FALSE);
		CAnimation::Dragonfly[i].Count++;
	}
}

void CAnimation::DrawLeaf(){
	for(int i=0;i<CAnimation::LEAF_MAX;i++){
		if(CAnimation::Leaf[i].Y-100*CAnimation::Leaf[i].R>480){
			CAnimation::Leaf[i].R=0.5+Rang(0.1);
			CAnimation::Leaf[i].Dir=Rang(PI);
			CAnimation::Leaf[i].Ang=PI/2+PI/8+Rang(PI/16);
			CAnimation::Leaf[i].Turn=GetRand(1);
			CAnimation::Leaf[i].Type=GetRand(1);
			CAnimation::Leaf[i].Clock=80+GetRand(20);
			CAnimation::Leaf[i].Sp=1.6+Rang(0.2);
			CAnimation::Leaf[i].X=420+Rang(420+100*CAnimation::Leaf[i].R);
			CAnimation::Leaf[i].Y=0-GetRand(100)-100*CAnimation::Leaf[i].R;
		}
		DrawRotaGraphF((float)CAnimation::Leaf[i].X,(float)CAnimation::Leaf[i].Y,CAnimation::Leaf[i].R,CAnimation::Leaf[i].Dir+sin(CAnimation::TimeLine%CAnimation::Leaf[i].Clock*PI*2.0/CAnimation::Leaf[i].Clock)*PI/24.0,CAnimation::Image[CAnimation::Leaf[i].Type],FALSE);
		CAnimation::Leaf[i].Y+=sin(CAnimation::Leaf[i].Ang+sin(CAnimation::TimeLine%CAnimation::Leaf[i].Clock*PI*2.0/CAnimation::Leaf[i].Clock)*PI/24.0)*CAnimation::Leaf[i].Sp;
		CAnimation::Leaf[i].X+=cos(CAnimation::Leaf[i].Ang+sin(CAnimation::TimeLine%CAnimation::Leaf[i].Clock*PI*2.0/CAnimation::Leaf[i].Clock)*PI/24.0)*CAnimation::Leaf[i].Sp;
	}
}

void CAnimation::DrawFire(){
	if(CAnimation::TimeLine%12==0){
		for(int i=0;i<CAnimation::FIRE_MAX;i++){
			if(!CAnimation::Fire[i].Flag){
				CAnimation::Fire[i].Flag=1;
				CAnimation::Fire[i].Sp=2.0+Rang(1.0);
				CAnimation::Fire[i].Ang=PI+PI/2+Rang(PI/4);
				CAnimation::Fire[i].VA=Rang(PI/6)/60;
				CAnimation::Fire[i].VVA=Rang(PI/6)/3600;
				CAnimation::Fire[i].R=1.1+Rang(0.25);
				CAnimation::Fire[i].VR=(-1+Rang(0.25))/240;
				CAnimation::Fire[i].X=320+Rang(Rang(Rang(320)));
				CAnimation::Fire[i].Y=480-sin(CAnimation::Fire[i].Ang)*160*CAnimation::Fire[i].R;
				CAnimation::Fire[i].Target=CAnimation::Fire[i].Y-(320+Rang(160));
				CAnimation::Fire[i].Turn=GetRand(1);
				i=CAnimation::FIRE_MAX;
			}
		}
	}
	for(int i=0;i<CAnimation::FIRE_MAX;i++){
		if(CAnimation::Fire[i].Flag){
			CAnimation::Fire[i].VVA*=0.9975;
			CAnimation::Fire[i].VA*=0.9975;
			CAnimation::Fire[i].Ang=AppointCross(PI+PI/2,CAnimation::Fire[i].Ang,0.02);
			if(CAnimation::Fire[i].Y<=CAnimation::Fire[i].Target){
				CAnimation::Fire[i].VR=(-1+Rang(0.25))/180;
				CAnimation::Fire[i].VA=Rang(PI/6)/60;
				CAnimation::Fire[i].VVA=Rang(PI/6)/3600;
				CAnimation::Fire[i].Target=CAnimation::Fire[i].Y-(320+Rang(160));
				for(int j=0;j<CAnimation::FIRE_MAX;j++){
					if(!CAnimation::Fire[j].Flag){
						CAnimation::Fire[j].Flag=1;
						CAnimation::Fire[j].Sp=CAnimation::Fire[i].Sp+Rang(0.5);
						CAnimation::Fire[j].Ang=CAnimation::Fire[i].Ang;
						CAnimation::Fire[j].VA=CAnimation::Fire[i].VA+Rang(PI/6)/60;
						CAnimation::Fire[j].VVA=CAnimation::Fire[i].VVA+Rang(PI/6)/3600;
						CAnimation::Fire[j].R=CAnimation::Fire[i].R;
						CAnimation::Fire[j].VR=CAnimation::Fire[i].VR+Rang(0.125)/240;
						CAnimation::Fire[j].X=CAnimation::Fire[i].X;
						CAnimation::Fire[j].Y=CAnimation::Fire[i].Y;
						CAnimation::Fire[j].Target=CAnimation::Fire[i].Y-(320+Rang(160));
						CAnimation::Fire[j].Turn=CAnimation::Fire[i].Turn;
						j=CAnimation::FIRE_MAX;
					}
				}
			}
			CAnimation::Fire[i].VA+=CAnimation::Fire[i].VVA;
			CAnimation::Fire[i].Ang+=CAnimation::Fire[i].VA;
			if(CAnimation::Fire[i].VR<0)CAnimation::Fire[i].R+=((640.0-CAnimation::Fire[i].Y)/320.0+0.2)*CAnimation::Fire[i].VR;
			else CAnimation::Fire[i].R+=CAnimation::Fire[i].VR;
			CAnimation::Fire[i].X+=cos(CAnimation::Fire[i].Ang)*CAnimation::Fire[i].Sp;
			CAnimation::Fire[i].Y+=sin(CAnimation::Fire[i].Ang)*CAnimation::Fire[i].Sp;
			if(CAnimation::Fire[i].R<=0.0||CAnimation::Fire[i].X+160*CAnimation::Fire[i].R<0||CAnimation::Fire[i].X-160*CAnimation::Fire[i].R>640||CAnimation::Fire[i].Y+160*CAnimation::Fire[i].R<0)CAnimation::Fire[i].Flag=0;
			else DrawRotaGraph2F((float)CAnimation::Fire[i].X,(float)CAnimation::Fire[i].Y,(float)63.0,(float)160.0,CAnimation::Fire[i].R,CAnimation::Fire[i].Ang+PI/2,CAnimation::Image[0],FALSE,CAnimation::Fire[i].Turn);
		}
	}
}

void CAnimation::DrawIce(){
	for(int i=0;i<CAnimation::ICE_MAX;i++){
		if(CAnimation::Ice[i].Y-200*CAnimation::Ice[i].R>480||CAnimation::Ice[i].X-200*CAnimation::Ice[i].R>640){
			double min,max;
			CAnimation::Ice[i].Sp=(GetRand(10000)+12000)*0.0001;
			CAnimation::Ice[i].VA=GetRand(400)+400;
			CAnimation::Ice[i].Dir=GetRand(1)*2-1;
			CAnimation::Ice[i].R=(GetRand(1600)+1600)*0.0001;
			CAnimation::Ice[i].Ang=atan2(480.0,480.0-160.0)+Rang(PI/16.0);
			CAnimation::Ice[i].Type=GetRand(3);
			min=0-200*CAnimation::Ice[i].R;
			max=640+200*CAnimation::Ice[i].R;
			CAnimation::Ice[i].X=GetRand((int)(max-min))+min;
			min=0-200*CAnimation::Ice[i].R;
			max=480+200*CAnimation::Ice[i].R;
			CAnimation::Ice[i].Y=GetRand((int)(max-min))+min;
			for(int j=0;j<100;j++){
				CAnimation::Ice[i].Y+=sin(CAnimation::Ice[i].Ang+PI)*10.0;
				CAnimation::Ice[i].X+=cos(CAnimation::Ice[i].Ang+PI)*10.0;
				if(CAnimation::Ice[i].Y+200*CAnimation::Ice[i].R<0||CAnimation::Ice[i].X+200*CAnimation::Ice[i].R<0)j=100;
			}
		}
		DrawRotaGraphF((float)CAnimation::Ice[i].X,(float)CAnimation::Ice[i].Y,CAnimation::Ice[i].R,((double)(CAnimation::TimeLine%CAnimation::Ice[i].VA))/CAnimation::Ice[i].VA*2.0*PI*CAnimation::Ice[i].Dir,CAnimation::Image[CAnimation::Ice[i].Type],FALSE);
		CAnimation::Ice[i].Y+=sin(CAnimation::Ice[i].Ang)*CAnimation::Ice[i].Sp;
		CAnimation::Ice[i].X+=cos(CAnimation::Ice[i].Ang)*CAnimation::Ice[i].Sp;
	}
}

void CAnimation::DrawTree(){
	int twigsum=0,growing=0,budsum=0;
	for(int i=0;i<CAnimation::TWIG_MAX;i++){
		if(CAnimation::Twig[i].Flag){
			twigsum++;
			if(!CAnimation::Twig[i].State&&!CAnimation::Twig[i].TargetState)growing++;
		}
	}
	for(int i=0;i<CAnimation::BUD_MAX;i++)if(CAnimation::Bud[i].Flag)budsum++;
	if(growing==0){
		CAnimation::Twig[0].Flag=1;
		CAnimation::Twig[0].Count=0;
		CAnimation::Twig[0].X=320;
		CAnimation::Twig[0].Y=480;
		CAnimation::Twig[0].Length=1.0;
		CAnimation::Twig[0].Width=1.0;
		CAnimation::Twig[0].VL=0.75+CAnimation::Twig[0].Y*0.006;
		CAnimation::Twig[0].VW=(0.75+CAnimation::Twig[0].Y*0.006)*0.15;
		CAnimation::Twig[0].State=0;
		CAnimation::Twig[0].Target=60;
		CAnimation::Twig[0].TargetState=0;
		CAnimation::Twig[0].Ang=-PI/2;
		growing++;
	}
	for(int i=0;i<CAnimation::TWIG_MAX;i++){
		if(CAnimation::Twig[i].Flag&&!CAnimation::Twig[i].State){
			CAnimation::Twig[i].Count++;
			if(CAnimation::Twig[i].Count>CAnimation::Twig[i].Target){
				double angtarget=atan2(-480,320+Rang(320-CAnimation::Twig[i].Y*2/3)-CAnimation::Twig[i].X)+Rang(PI/4);
				double angwidth=PI/18+PI/10+Rang(PI/10);
				CAnimation::Twig[i].State=1;
				CAnimation::Twig[i].VL=0.0;
				if(CAnimation::Twig[i].TargetState==1){
					int branch;
					if(budsum<=CAnimation::BUD_MAX/4)branch=1;
					else if(GetRand(CAnimation::BUD_MAX)>=budsum)branch=1;
					else branch=0;
					if(branch){
						for(int j=0;j<CAnimation::BUD_MAX;j++){
							if(!CAnimation::Bud[j].Flag){
								CAnimation::Bud[j].Flag=1;
								CAnimation::Bud[j].X=CAnimation::Twig[i].X+cos(CAnimation::Twig[i].Ang)*CAnimation::Twig[i].Length;
								CAnimation::Bud[j].Y=CAnimation::Twig[i].Y+sin(CAnimation::Twig[i].Ang)*CAnimation::Twig[i].Length;
								CAnimation::Bud[j].R=0.0;
								CAnimation::Bud[j].VR=0.01+Rang(0.002);
								CAnimation::Bud[j].Turn=GetRand(1);
								CAnimation::Bud[j].Ang=HalfCross(angtarget,CAnimation::Twig[i].Ang);
								j=CAnimation::BUD_MAX;
							}
						}
					}
				}
				else if(CAnimation::Twig[i].TargetState==0){
					growing--;
					for(int j=0;j<2;j++){
						for(int k=0;k<CAnimation::TWIG_MAX;k++){
							if(!CAnimation::Twig[k].Flag){
								int branch;
								if(growing<=1)branch=0;
								else branch=GetRand(1);
								CAnimation::Twig[k].Flag=1;
								CAnimation::Twig[k].Count=0;
								CAnimation::Twig[k].X=CAnimation::Twig[i].X+cos(CAnimation::Twig[i].Ang)*CAnimation::Twig[i].Length;
								CAnimation::Twig[k].Y=CAnimation::Twig[i].Y+sin(CAnimation::Twig[i].Ang)*CAnimation::Twig[i].Length;
								CAnimation::Twig[k].Length=0.0;
								CAnimation::Twig[k].Width=0.0;
								CAnimation::Twig[k].VL=0.75+CAnimation::Twig[k].Y*(0.003+Rang(0.003));
								CAnimation::Twig[k].VW=(0.75+CAnimation::Twig[k].Y*(0.003+Rang(0.003)))*0.1;
								CAnimation::Twig[k].State=0;
								if(branch==0){
									CAnimation::Twig[k].TargetState=0;
									CAnimation::Twig[k].Target=60+twigsum+GetRand(60-twigsum);
									growing++;
								}
								else {
									CAnimation::Twig[k].TargetState=1;
									CAnimation::Twig[k].Target=30+GetRand(30);
								}
								if(twigsum>=CAnimation::TWIG_MAX-CAnimation::TWIG_MAX/4){
									CAnimation::Twig[k].Ang=HalfCross(angtarget+angwidth*(GetRand(1)*2-1),CAnimation::Twig[i].Ang);
									j=2;
								}
								else {
									CAnimation::Twig[k].Ang=HalfCross(angtarget+angwidth*(j*2-1),CAnimation::Twig[i].Ang);
								}
								k=CAnimation::TWIG_MAX;
							}
						}
					}
				}
			}
		}
	}
	for(int i=0;i<CAnimation::TWIG_MAX;i++){
		if(CAnimation::Twig[i].Flag){
			double x1,x2,x3,x4,y1,y2,y3,y4;
			CAnimation::Twig[i].Y+=1.0;
			CAnimation::Twig[i].Length+=CAnimation::Twig[i].VL;
			CAnimation::Twig[i].Width+=CAnimation::Twig[i].VW;
			CAnimation::Twig[i].VW*=0.995;
			if(CAnimation::Twig[i].Length>200)CAnimation::Twig[i].VL*=0.99;
			x1=CAnimation::Twig[i].X+cos(CAnimation::Twig[i].Ang-PI/2)*CAnimation::Twig[i].Width*0.5;
			x2=CAnimation::Twig[i].X+cos(CAnimation::Twig[i].Ang)*CAnimation::Twig[i].Length*1.1+cos(CAnimation::Twig[i].Ang-PI/2)*CAnimation::Twig[i].Width*0.5;
			x3=CAnimation::Twig[i].X+cos(CAnimation::Twig[i].Ang)*CAnimation::Twig[i].Length*1.1+cos(CAnimation::Twig[i].Ang+PI/2)*CAnimation::Twig[i].Width*0.5;
			x4=CAnimation::Twig[i].X+cos(CAnimation::Twig[i].Ang+PI/2)*CAnimation::Twig[i].Width*0.5;
			y1=CAnimation::Twig[i].Y+sin(CAnimation::Twig[i].Ang-PI/2)*CAnimation::Twig[i].Width*0.5;
			y2=CAnimation::Twig[i].Y+sin(CAnimation::Twig[i].Ang)*CAnimation::Twig[i].Length*1.1+sin(CAnimation::Twig[i].Ang-PI/2)*CAnimation::Twig[i].Width*0.5;
			y3=CAnimation::Twig[i].Y+sin(CAnimation::Twig[i].Ang)*CAnimation::Twig[i].Length*1.1+sin(CAnimation::Twig[i].Ang+PI/2)*CAnimation::Twig[i].Width*0.5;
			y4=CAnimation::Twig[i].Y+sin(CAnimation::Twig[i].Ang+PI/2)*CAnimation::Twig[i].Width*0.5;
			double Lend,Rend,Dend;
			Lend=0-CAnimation::Twig[i].Width;
			Rend=640+CAnimation::Twig[i].Width;
			Dend=480+CAnimation::Twig[i].Width;
			if((y1>Dend&&y2>Dend&&y3>Dend&&y4>Dend)||(x1<Lend&&x2<Lend&&x3<Lend&&x4<Lend)||(x1>Rend&&x2>Rend&&x3>Rend&&x4>Rend))CAnimation::Twig[i].Flag=0;
			else {
				DrawModiGraphF((float)x1,(float)y1,(float)x2,(float)y2,(float)x3,(float)y3,(float)x4,(float)y4,CAnimation::Image[0],FALSE);
				DrawRotaGraphF((float)CAnimation::Twig[i].X,(float)CAnimation::Twig[i].Y,CAnimation::Twig[i].Width/24.0,CAnimation::Twig[i].Ang,CAnimation::Image[1],FALSE);
			}
		}
	}
	for(int i=0;i<CAnimation::BUD_MAX;i++){
		if(CAnimation::Bud[i].Flag){
			CAnimation::Bud[i].Y+=1.0;
			if(CAnimation::Bud[i].Y-150*CAnimation::Bud[i].R>480||CAnimation::Bud[i].X+150*CAnimation::Bud[i].R<0||CAnimation::Bud[i].X-150*CAnimation::Bud[i].R>640)CAnimation::Bud[i].Flag=0;
			else {
				CAnimation::Bud[i].R+=CAnimation::Bud[i].VR;
				CAnimation::Bud[i].VR*=0.982;
				DrawRotaGraph2F((float)CAnimation::Bud[i].X,(float)CAnimation::Bud[i].Y,41.0,150.0,CAnimation::Bud[i].R,CAnimation::Bud[i].Ang+PI/2,CAnimation::Image[2],FALSE,CAnimation::Bud[i].Turn);
			}
		}
	}
}

CAnimation::CAnimation(){
}

CAnimation::~CAnimation(){
	for(int i=0;i<CAnimation::IMAGE_MAX;i++){
		DeleteGraph(CAnimation::Image[i]);
	}
}

void CAnimation::Initialize(){
	CAnimation::BlossomInitialize();
	CAnimation::FireflyInitialize();
	CAnimation::WaterInitialize();
	CAnimation::SeaInitialize();
	CAnimation::DragonflyInitialize();
	CAnimation::LeafInitialize();
	CAnimation::FireInitialize();
	CAnimation::IceInitialize();
	CAnimation::TreeInitialize();
	memset(CAnimation::Image,0,sizeof(CAnimation::Image));
	CAnimation::PlayingType=-100;
	CAnimation::TimeLine=0;
}

int CAnimation::Load(int Type){
	if(CAnimation::PlayingType!=Type){
		for(int i=0;i<CAnimation::IMAGE_MAX;i++){
			char Path[256];
			DeleteGraph(CAnimation::Image[i]);
			if(Type<0)sprintf_s(Path,sizeof(Path),"dat/img/back/mask/main_%02d.png",i);
			else sprintf_s(Path,sizeof(Path),"dat/img/back/mask/%02d_%02d.png",Type,i);
			CAnimation::Image[i]=LoadGraph(Path);
		}
		CAnimation::PlayingType=Type;
		return 1;
	}
	else return 0;
}

void CAnimation::Draw(int Type){
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	switch(Type){
		case -1:CAnimation::DrawWheel();break;
		case  0:CAnimation::DrawBlossom();break;
		case  1:CAnimation::DrawFirefly();break;
		case  2:CAnimation::DrawWater();break;
		case  3:CAnimation::DrawSea();break;
		case  4:CAnimation::DrawDragonfly();break;
		case  5:CAnimation::DrawLeaf();break;
		case  6:CAnimation::DrawFire();break;
		case  7:CAnimation::DrawIce();break;
		case  8:CAnimation::DrawTree();break;
	}
	SetDrawMode(DX_DRAWMODE_NEAREST);
	CAnimation::TimeLine++;
}