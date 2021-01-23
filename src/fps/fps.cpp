#include <DxLib.h>
#include <fps/fps.h>

CFps::CFps(){
	CFps::Count=0;
	CFps::ZeroFrame=0;
	CFps::Margin=0;
	CFps::Average=0.0;
	memset(CFps::Child,0,sizeof(CFps::Child));
	memset(CFps::Target,0,sizeof(CFps::Target));
}

void CFps::Wait(){
	int Now_ms,Term;
	if(CFps::Count==0){
		if(CFps::Margin==0){
			Term=0;
			for(int i=0;i<CFps::FRAME_RATE;i++)CFps::Target[i]=1000*i/CFps::FRAME_RATE;
		}
		else {
			Term=CFps::ZeroFrame+1000-GetNowCount();
		}
	}
	else {
		Term=CFps::ZeroFrame+CFps::Target[Count]-GetNowCount();
	}
	if(Term>0){
		Sleep(Term);
	}
	Now_ms=GetNowCount();
	if(Count==0){
		CFps::ZeroFrame=Now_ms;
	}
	CFps::Child[Count]=Now_ms-CFps::Margin;
	CFps::Margin=Now_ms;
	if(Count==CFps::FRAME_RATE-1){
		CFps::Average=0;
		for(int i=0;i<CFps::FRAME_RATE;i++){
			CFps::Average+=CFps::Child[i];
		}
		CFps::Average/=CFps::FRAME_RATE;
	}
	Count=(++Count)%CFps::FRAME_RATE;
}

double CFps::Get(){
	return CFps::Average?1000/CFps::Average:0;
}