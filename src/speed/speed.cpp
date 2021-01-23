#include <cstring>
#include <speed/speed.h>

CSpeed::CSpeed(){
	CSpeed::Initialize();
}

void CSpeed::Initialize(){
	memset(CSpeed::Point,0,sizeof(CSpeed::Point));
	CSpeed::Index=0;
}

void CSpeed::Record(int TimeLine){
	CSpeed::Index++;
	if(CSpeed::Index>=CSpeed::SIZE){
		CSpeed::Index=0;
	}
	CSpeed::Point[CSpeed::Index]=TimeLine+CSpeed::SIZE;
}

int CSpeed::Calc(int TimeLine){
	int Num=0;
	for(int i=CSpeed::Index;CSpeed::Point[i]>TimeLine;i--){
		Num++;
		if(i<1)i=CSpeed::SIZE;
	}
	return Num;
}