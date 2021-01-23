#ifndef SAVE_H
#define SAVE_H

class CSave{
public:
	static const int BGM_VOLUME		= 0;
	static const int SE_VOLUME		= 1;
	static const int VOICE_VOLUME	= 2;
	static const int WINDOW_MODE	= 3;
	static const int BLOCK_FLAG		= 4;
	static const int SE_SET			= 5;
	static const int DARKNESS		= 6;
	static const int ANIMATION		= 7;
	static const int CASCADE = 8;
	static const int BOARD = 9;
	static const int SHOW_ADDPT = 10;
	static const int RULED_LINE = 11;
	static const int GHOST = 12;
	static const int KEY_CONFIG = 13;
	static const int CONFIG_NUM = 14;
	static const int TOTALS_TM		= 30;
	static const int TOTALS_LINE	= 31;
	static const int TOTALS_TETRIS	= 32;
	static const int TOTALS_BTB		= 33;
	static const int TOTALS_TSPIN	= 34;
	static const int TOTALS_REN		= 35;
	static const int SYSTEM_SUM		= 63;
	static const int BEST_SCORE		= 0;
	static const int BEST_TIME		= 1;
	static const int BEST_LEVEL		= 2;
	static const int BEST_POINT		= 3;
	static const int BEST_RANK		= 4;
	static const int CLEAR_TIMES	= 5;
	static const int COURSE_SUM		= 15;
	static const int KEY_LENGTH		= 64;
	CSave();
	int LoadSystem(char Path[256]);
	void InitSystem();
	void SaveSystem();
	void WriteSystem(int Target,int Data);
	int ReadSystem(int Target);
	int LoadCourse(char Path[256]);
	void InitCourse();
	void SaveCourse();
	void WriteCourse(int Target,int Data);
	int ReadCourse(int Target);
	int GetConfigMax(int num);
	int GetConfigDefault(int num);
private:
	int Key[KEY_LENGTH];
	int System[64];
	int Course[16];
	char SystemPath[256];
	char CoursePath[256];
	int ConfigMax[14];
	int ConfigDefault[14];
};

extern CSave Save;

#endif