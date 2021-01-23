#include <cstring>
#include <DxLib.h>
#include <key/key.h>

CKey::CKey(){
	memset(CKey::StateKey,0,sizeof(CKey::StateKey));
	memset(CKey::StatePad,0,sizeof(CKey::StatePad));
	CKey::LoadKeyConfig();
	CKey::LoadPadConfig();
}

void CKey::GetKey(){
	char KeyInput[256];
	GetHitKeyStateAll(KeyInput);
	for (int i = 0; i < 256; i++){
		if (KeyInput[i])CKey::StateKey[i]++;
		else CKey::StateKey[i] = 0;
	}
}

void CKey::GetPad(){
	int PadInput, mul = 1;
	PadInput = GetJoypadInputState(DX_INPUT_PAD1);
	for (int i = 0; i < 32; i++){
		if (PadInput&mul)CKey::StatePad[i]++;
		else CKey::StatePad[i] = 0;
		mul *= 2;
	}
}

int CKey::Check(int Handle){
	return CKey::StateKey[Config.Key[Handle]]>=CKey::StatePad[Config.Pad[Handle]]?CKey::StateKey[Config.Key[Handle]]:CKey::StatePad[Config.Pad[Handle]];
}

void CKey::LoadKeyConfig(){
	char data[1024]={0};
	int default_num[15]={44,45,200,205,208,203,44,46,45,47,42,200,57,1,25};
	for(int i=0;i<15;i++)CKey::Config.Key[i]=default_num[i];
	int fp=FileRead_open("key.txt");
	if(!fp){
		FILE *SaveFP;
		fopen_s(&SaveFP,"key.txt","w");
		fputs("44,45,200,205,208,203,44,46,45,47,42,200,57,1,25",SaveFP);
		fclose(SaveFP);
		return;
	}
	FileRead_gets(data,sizeof(data),fp);
	sscanf_s(data,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",&CKey::Config.Key[0],&CKey::Config.Key[1],&CKey::Config.Key[2],&CKey::Config.Key[3],&CKey::Config.Key[4],&CKey::Config.Key[5],&CKey::Config.Key[6],&CKey::Config.Key[7],&CKey::Config.Key[8],&CKey::Config.Key[9],&CKey::Config.Key[10],&CKey::Config.Key[11],&CKey::Config.Key[12],&CKey::Config.Key[13],&CKey::Config.Key[14]);
	FileRead_close(fp);
}

void CKey::LoadPadConfig(){
	char data[1024]={0};
	int default_num[15]={7,8,3,2,0,1,7,9,8,6,4,3,5,14,13};
	for(int i=0;i<15;i++)CKey::Config.Pad[i]=default_num[i];
	int fp=FileRead_open("pad.txt");
	if(!fp){
		FILE *SaveFP;
		fopen_s(&SaveFP,"pad.txt","w");
		fputs("7,8,3,2,0,1,7,9,8,6,4,3,5,14,13",SaveFP);
		fclose(SaveFP);
		return;
	}
	FileRead_gets(data,sizeof(data),fp);
	sscanf_s(data,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",&CKey::Config.Pad[0],&CKey::Config.Pad[1],&CKey::Config.Pad[2],&CKey::Config.Pad[3],&CKey::Config.Pad[4],&CKey::Config.Pad[5],&CKey::Config.Pad[6],&CKey::Config.Pad[7],&CKey::Config.Pad[8],&CKey::Config.Pad[9],&CKey::Config.Pad[10],&CKey::Config.Pad[11],&CKey::Config.Pad[12],&CKey::Config.Pad[13],&CKey::Config.Pad[14]);
	FileRead_close(fp);
}

void CKey::ResetKey(){
	int default_num[15] = { 44, 45, 200, 205, 208, 203, 44, 46, 45, 47, 42, 200, 57, 1, 25 };
	for (int i = 0; i < 15; i++){
		CKey::Config.Key[i] = default_num[i];
	}
	FILE *SaveFP;
	fopen_s(&SaveFP, "key.txt", "w");
	fputs("44,45,200,205,208,203,44,46,45,47,42,200,57,1,25", SaveFP);
	fclose(SaveFP);
}

void CKey::ResetPad(){
	int default_num[15] = { 7, 8, 3, 2, 0, 1, 7, 9, 8, 6, 4, 3, 5, 14, 13 };
	for (int i = 0; i < 15; i++){
		CKey::Config.Pad[i] = default_num[i];
	}
	FILE *SaveFP;
	fopen_s(&SaveFP, "pad.txt", "w");
	fputs("7,8,3,2,0,1,7,9,8,6,4,3,5,14,13", SaveFP);
	fclose(SaveFP);
}

int CKey::SetAnyKey(int keyNum){
	int check = -1;
	int keyGroup[15] = { 1, 1, 2, 2, 2, 2, 3, 4, 3, 4, 5, 5, 5, 5, 6 };
	for (int i = 0; i < 256; i++){
		if (CKey::StateKey[i] == 30){
			check = i;
			i = 256;
		}
	}
	if (check >= 0){
		char configStr[256] = { 0 };
		for (int i = 0; i < 15; i++){
			if (CKey::Config.Key[i] == check && keyGroup[i] == keyGroup[keyNum]){
				CKey::Config.Key[i] = CKey::Config.Key[keyNum];
				i = 15;
			}
		}
		CKey::Config.Key[keyNum] = check;
		for (int i = 0; i < 15; i++){
			char itoaTemp[16] = { 0 };
			if (i == 0){
				sprintf_s(itoaTemp, sizeof(itoaTemp)-1, "%d", CKey::Config.Key[i]);
			}
			else {
				sprintf_s(itoaTemp, sizeof(itoaTemp)-1, ",%d", CKey::Config.Key[i]);
			}
			strcat_s(configStr, sizeof(configStr), itoaTemp);
		}
		FILE *SaveFP;
		fopen_s(&SaveFP, "key.txt", "w");
		fputs(configStr, SaveFP);
		fclose(SaveFP);
	}
	return check;
}

int CKey::GetAnyKey(int keyNum){
	if (keyNum < 0 || keyNum > 15){
		keyNum = 0;
	}
	return CKey::Config.Key[keyNum];
}

int CKey::SetAnyPad(int padNum){
	int check = -1;
	int keyGroup[15] = { 1, 1, 2, 2, 2, 2, 3, 4, 3, 4, 5, 5, 5, 5, 6 };
	for (int i = 0; i < 32; i++){
		if (CKey::StatePad[i] == 30){
			check = i;
			i = 32;
		}
	}
	if (check >= 0){
		char configStr[256] = { 0 };
		for (int i = 0; i < 15; i++){
			if (CKey::Config.Pad[i] == check && keyGroup[i] == keyGroup[padNum]){
				CKey::Config.Pad[i] = CKey::Config.Pad[padNum];
				i = 15;
			}
		}
		CKey::Config.Pad[padNum] = check;
		for (int i = 0; i < 15; i++){
			char itoaTemp[16] = { 0 };
			if (i == 0){
				sprintf_s(itoaTemp, sizeof(itoaTemp)-1, "%d", CKey::Config.Pad[i]);
			}
			else {
				sprintf_s(itoaTemp, sizeof(itoaTemp)-1, ",%d", CKey::Config.Pad[i]);
			}
			strcat_s(configStr, sizeof(configStr), itoaTemp);
		}
		FILE *SaveFP;
		fopen_s(&SaveFP, "pad.txt", "w");
		fputs(configStr, SaveFP);
		fclose(SaveFP);
	}
	return check;
}

int CKey::GetAnyPad(int padNum){
	if (padNum < 0 || padNum > 15){
		padNum = 0;
	}
	return CKey::Config.Pad[padNum];
}