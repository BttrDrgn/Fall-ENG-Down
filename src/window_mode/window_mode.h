#ifndef WINDOW_MODE_H
#define WINDOW_MODE_H

class CWindowMode{
public:
	void Initialize(int StartWindowModeFlag);
	int Change(int TargetWindowModeFlag);
private:
	int NowWindowModeFlag;
};

extern CWindowMode WindowMode;

#endif