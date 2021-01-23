#ifndef KEY_H
#define KEY_H

typedef struct{
	int Key[15],Pad[15];
}Config_t;

class CKey{
public:
	CKey();
	void GetKey();
	void GetPad();
	int Check(int Handle);
	void LoadKeyConfig();
	void LoadPadConfig();
	void ResetKey();
	void ResetPad();
	int SetAnyKey(int keyNum);
	int GetAnyKey(int keyNum);
	int SetAnyPad(int padNum);
	int GetAnyPad(int padNum);
private:
	int StateKey[256];
	int StatePad[32];
	Config_t Config;
};

extern CKey Key;

#endif