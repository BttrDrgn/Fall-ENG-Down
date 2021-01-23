#include <DxLib.h>

const double PI2 = 6.2831853071795862;

double Rang(double ang){
	return (-ang+ang*2*GetRand(10000)/10000.0);
}

double GetRandF(double RandMax){
	return (RandMax*GetRand(10000)/10000.0);
}

double HalfCross(double ang1,double ang2){
	double gap1,gap2,answer;
	while(ang1<ang2)ang1+=PI2;
	while(ang2<ang1)ang2+=PI2;
	if(ang1<ang2)ang1+=PI2;
	gap1=ang1-ang2;
	if(ang2<ang1)ang2+=PI2;
	gap2=ang2-ang1;
	if(gap1<gap2)answer=ang2+gap1/2.0;
	else answer=ang1+gap2/2.0;
	while(answer>=PI2)answer-=PI2;
	return answer;
}

double AppointCross(double ang1,double ang2,double ang1factor){
	double gap1,gap2,answer;
	while(ang1<ang2)ang1+=PI2;
	while(ang2<ang1)ang2+=PI2;
	if(ang1<ang2)ang1+=PI2;
	gap1=ang1-ang2;
	if(ang2<ang1)ang2+=PI2;
	gap2=ang2-ang1;
	if(gap1<gap2)answer=ang2+gap1*ang1factor;
	else answer=ang1+gap2*(1.0-ang1factor);
	while(answer>=PI2)answer-=PI2;
	return answer;
}