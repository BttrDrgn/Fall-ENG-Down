#include <DxLib.h>
#include <save/save.h>

CSave::CSave(){
	memset(CSave::Key,0,sizeof(CSave::Key));
	CSave::InitSystem();
	SRand(19901228);
	for(int i=0;i<CSave::KEY_LENGTH;i++)CSave::Key[i]=(GetRand(0x7FFFFFFF)*(GetRand(1)*2-1));
	SRand(19690720);
	for(int i=0;i<CSave::KEY_LENGTH;i++)CSave::Key[i]^=((GetRand(0x7FFFFFFF)*(GetRand(1)*2-1)));
	int max[14] = { 100, 100, 100, 3, 1, 1, 100, 1, 1, 2, 3, 3, 3, 1 };
	int def[14] = { 60, 80, 80, 1, 0, 0, 80, 1, 1, 1, 2, 0, 3, 0 };
	for (int i = 0; i < 14; i++){
		CSave::ConfigMax[i] = max[i];
		CSave::ConfigDefault[i] = def[i];
	}
}

int CSave::LoadSystem(char Path[256]){
	FILE *SaveFP;
	strcpy_s(CSave::SystemPath,sizeof(CSave::SystemPath),Path);
	if((fopen_s(&SaveFP,CSave::SystemPath,"rb"))!=0){
		CSave::InitSystem();
		CSave::SaveSystem();
		return 0;
	}
	else {
		int CheckSum=0;
		fread(CSave::System,sizeof(CSave::System),1,SaveFP);
		fclose(SaveFP);
		for(int i=0;i<CSave::SYSTEM_SUM;i++){
			CheckSum^=CSave::System[i];
		}
		CheckSum^=CSave::Key[SYSTEM_SUM];
		if(CheckSum!=CSave::System[CSave::SYSTEM_SUM]){
			MessageBox(NULL,"システムセーブデータに異常があります。","エラー",MB_OK);
			return -1;
		}
		return 1;
	}
}

void CSave::InitSystem(){
	memset(CSave::System,0,sizeof(CSave::System));
	for (int i = 0; i < CSave::CONFIG_NUM; i++){
		CSave::System[i] = CSave::ConfigDefault[i];
	}
	for(int i=0;i<CSave::SYSTEM_SUM;i++){
		CSave::System[i]^=CSave::Key[i];
		CSave::System[SYSTEM_SUM]^=CSave::System[i];
	}
	CSave::System[SYSTEM_SUM]^=CSave::Key[SYSTEM_SUM];
}

void CSave::SaveSystem(){
	FILE *SaveFP;
	CSave::System[SYSTEM_SUM]=0;
	for(int i=0;i<CSave::SYSTEM_SUM;i++){
		CSave::System[SYSTEM_SUM]^=CSave::System[i];
	}
	CSave::System[SYSTEM_SUM]^=CSave::Key[SYSTEM_SUM];
	fopen_s(&SaveFP,CSave::SystemPath,"wb");
	fwrite(CSave::System,sizeof(CSave::System),1,SaveFP);
	fclose(SaveFP);
}

void CSave::WriteSystem(int Target,int Data){
	CSave::System[Target]=Data^CSave::Key[Target];
}

int CSave::ReadSystem(int Target){
	return CSave::System[Target]^CSave::Key[Target];
}

int CSave::LoadCourse(char Path[256]){
	FILE *SaveFP;
	strcpy_s(CSave::CoursePath,sizeof(CSave::CoursePath),Path);
	if((fopen_s(&SaveFP,CSave::CoursePath,"rb"))!=0){
		CSave::InitCourse();
		CSave::SaveCourse();
		return 0;
	}
	else {
		int CheckSum=0;
		fread(CSave::Course,sizeof(CSave::Course),1,SaveFP);
		fclose(SaveFP);
		for(int i=0;i<CSave::COURSE_SUM;i++){
			CheckSum^=CSave::Course[i];
		}
		CheckSum^=CSave::Key[COURSE_SUM];
		if(CheckSum!=CSave::Course[CSave::COURSE_SUM]){
			MessageBox(NULL,"コースセーブデータに異常があります。","エラー",MB_OK);
			return -1;
		}
		return 1;
	}
}

void CSave::InitCourse(){
	memset(CSave::Course,0,sizeof(CSave::Course));
	CSave::Course[CSave::BEST_TIME]=360000;
	for(int i=0;i<CSave::COURSE_SUM;i++){
		CSave::Course[i]^=CSave::Key[i];
		CSave::Course[COURSE_SUM]^=CSave::Course[i];
	}
	CSave::Course[COURSE_SUM]^=CSave::Key[COURSE_SUM];
}

void CSave::SaveCourse(){
	FILE *SaveFP;
	CSave::Course[COURSE_SUM]=0;
	for(int i=0;i<CSave::COURSE_SUM;i++){
		CSave::Course[COURSE_SUM]^=CSave::Course[i];
	}
	CSave::Course[COURSE_SUM]^=CSave::Key[COURSE_SUM];
	fopen_s(&SaveFP,CSave::CoursePath,"wb");
	fwrite(CSave::Course,sizeof(CSave::Course),1,SaveFP);
	fclose(SaveFP);
}

void CSave::WriteCourse(int Target,int Data){
	CSave::Course[Target]=Data^CSave::Key[Target];
}

int CSave::ReadCourse(int Target){
	return CSave::Course[Target]^CSave::Key[Target];
}

int CSave::GetConfigMax(int num){
	return CSave::ConfigMax[num];
}

int CSave::GetConfigDefault(int num){
	return CSave::ConfigDefault[num];
}