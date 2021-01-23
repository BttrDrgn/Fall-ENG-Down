#ifndef GAME_PLAY_H
#define GAME_PLAY_H

static const int FLASH_MAX = 200;

const int FIELD_X = 10;
const int FIELD_Y = 31;

extern int CalcRank(int Board,int Sign);
extern void StartNext();
extern int GhostBlock();
extern void GameInitialize();
extern int GamePlay();

typedef struct{
	int ClearRemain,ClearColor;
}Explode_t;

typedef struct{
	int X,Y,FlashRemain;
}Flash_t;

typedef struct{
	int Mode,Grade,OtherCourse,Level,LevelMax,Point,DisplayPoint;
	int LTime,TTime;
	int LTetrimino;
	int ClearBaseScore;
	int ClearBaseTime;
	int Rank;
}Progress_t;

typedef struct{
	int Game,Level,Line,Tetrimino,Frame;
}RandomNumber_t;

typedef struct{
	int Score;
	int DisplayScore;
	int TTetriminos,LTetriminos;
	int TLines,LLines;
	int Lmin,Tmin;
	int TTetris,LTetris;
	int TBacktoBack,LBacktoBack;
	int TTSpin,LTSpin;
	int TMaxRen,LMaxRen;
	int TRens,LRens;
	int Leftover;
}Scores_t;

typedef struct{
	int Type,Side,Hold,Next[14],Y,X;
}Tetrimino_t;

typedef struct{
	int Score,Time,Level,Point,Rank;
}NewRecord_t;

extern Explode_t Explode[20][10];
extern Flash_t Flash[FLASH_MAX];
extern Progress_t Progress;
extern Scores_t Scores;
extern Tetrimino_t Tetrimino;
extern NewRecord_t NewRecord;

extern int Field[60][30];
extern int QuakeX,QuakeY,QuakeTargetX,QuakeTargetY;
extern int IrregularRand[7];
extern int JustBeforeX,JustBeforeY,JustBeforeType;
extern int WarnTime,WarnFlag;
extern int RemainLDT,RemainLCT,RemainARE;
extern int NowRen_Keep;
extern int AfterHold;
extern int LevelDisplayTimeRemain;
extern int WordFlag,WordRemainCount,GetLineClearPoint,GetLineClearScore;
extern int TimeLeftBonusTime,TimeLeftGetScore;
extern int InvisibleBlock[20][10];
extern int NowLiftPressure;;
extern int AlternateHideState;
extern int PastClearLines;
extern int ClearLineBase;
extern int ClearRow[8];
extern int CascadingFlag;
extern double CascadeGage;
extern int CascadeNext;
extern int TempCascade;
extern int PlayStartLevel;

enum {
	OBS_CFIELD,
	OBS_LEVELUP,
	OBS_EXORCISE,
	OBS_CFB,
	OBS_BIG,
	OBS_NH,
	OBS_BOOST,
	OBS_COPY,
	OBS_RANDOM,
	OBS_SHUTTER,
	OBS_SHADOW,
	OBS_SUDDEN,
	OBS_RC,
	OBS_MONO,
	OBS_REVERSE,
	OBS_DARK,
	OBS_ALTHIDE,
	OBS_SNOW,
	OBS_LIFT,
	OBS_PRESS,
	OBS_QUAKE,
	OBS_BLACKOUT,
	OBS_ZEROG,
	OBS_CLONE,
	OBS_CASCADE,
	OBS_DROPEFFECT
};

#endif