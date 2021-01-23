#ifndef LOAD_H
#define LOAD_H

static const int LEVEL_MAX		= 100;
static const int BOARD_MAX		= 40;
static const int SIGN_MAX		= 6;
static const int TAG_MAX		= 200;
static const int SHAPE_MAX		= 10;
static const int ROTATION_MAX	= 10;
static const int BGM_MAX		= 10;
static const int OBSTACLE_MAX	= 30;
static const int IF_MAX			= 100;

typedef struct{
	int LineClearPoint[5],BacktoBackPoint[4],TSpinPoint[5],RenPoint[4],Condition[5],PreliminaryBell[2];
	int SmoothDrop;
	int SoftDropInterval;
	int BackBlackNum,BackWhiteNum,BackMaskNum;
	int ScoreBase;
	int Numerator,Denominator,LDT,LCT,ARE,DAS,PointMax;
	int TargetTime,ObstacleTime;
	int ObstacleFlag[OBSTACLE_MAX];
	int FirstObstacle[OBSTACLE_MAX];
	int ClearField[4];
	int LevelUp[2];
	int LevelUpCondition[15];
	int Exorcise[3];
	int ClearForBig[4];
	int Big[2];
	int NoHold[1];
	int Boost[4];
	int CopyGarbage[4];
	int RandomGarbage[5];
	int Shutter[4];
	int Shadow[1];
	int SuddenAppear[1];
	int RandomColor[7];
	int Monochrome[7];
	int Reverse[3];
	int Dark[11];
	int AlternateHide[3];
	int Snow[16];
	int Lift[2];
	int Press[2];
	int Quake[10];
	int BlackOut[8];
	int ZeroGravity[2];
	int Clone[5];
	int Cascade[4];
	int DropEffect[4];
	int HideObstacle[OBSTACLE_MAX],HideText[7],HideTetrimino[7],HideField[8],HideGage[3],HideGhost[3],HideSurface,HideHold,HideNext[3],HideExplosion,HideBack[3],HideCurtain[2],HideFrame;
	int NoPause;
	int LevelUpWaitTime;
	int FieldBright[3];
	int TetriminoBright[3];
	int BlackBackBright[3];
	int WhiteBackBright[3];
	int MaskBackBright[3];
	int NextBright[3];
	int HoldBright[3];
	int GhostBright[3];
	int SurfaceColor[3];
	int ExplosionBright[3];
	int SnowColor[3];
	int PauseBright[3];
	int FlashIntensity,FlashTime,FlashColor[3],FlashDrawMax,FlashFill;
	int SurfaceThickness[4];
	int MoveInfMax,TurnInfMax,InfDelay;
	int EmergePos[7][4];
	int RotationType[7];
	int LayerFlag[100];
	int ShapeFlag;
	int RotationFlag;
	int BgmFlag;
	int IfFlag[IF_MAX];
	char InitialFieldPath[256];
	int CascadeRate;
}Scenario_t;

typedef struct{
	char TitleText[5][256];
	char IndexTitle[32];
	int SelectLimit;
	int HighestScore,SpeedRun,RecMaxLevel,RecMaxPoint,RecMaxRank,RecClearTimes;
	int NaturalObstacle[OBSTACLE_MAX];
	char RankName[100][32];
	int RankBase[100];
	int RankSign,RankBoard,RankMax,PlayingRank,GameOverRank,FirstStartRank;
	int FirstTetrimino[7];
	int ExchangeTetrimino[10][6];
	char BgmPath[BGM_MAX][256];
	int BgmLoopPoint[BGM_MAX],BgmVolume[BGM_MAX];
	char LayerPath[100][256];
	int CopyLayerPath[100];
	char Text[6][32];
	int ErrorRow[40];
	char Font[256];
	int FontThickness;
	int ReadyPos,WarningPos,NowLevelPos;
	int Shape[SHAPE_MAX][7][4][4][4];
	int Rotation[ROTATION_MAX][7][8][32];
	char ShapePath[SHAPE_MAX][256];
	char RotationPath[ROTATION_MAX][256];
	int ShapeBlackOut[SHAPE_MAX][2][7];
	int ShapeBoostPos[SHAPE_MAX][7][4];
	int ShapeTSpinInfo[SHAPE_MAX][3];
	int ShapeTSpinPoint[SHAPE_MAX][4][4][2];
	int ShapeTSpinMini[SHAPE_MAX][4][2];
	int IfPointer[IF_MAX];
	int IfCondition[IF_MAX][15];
	//int IfTermControl[IF_MAX][4];
}Course_t;

typedef struct{
	int BackBlackMax,BackWhiteMax,BackMaskMax;
	int MaskLevel,MaskNumber;
}GraphicInfo_t;

extern void LoadBackGraphic(int main_or_notmain);
extern void CourseTagSetting();
extern void BoardSignNameSetting();
extern int LoadShape(char Path[256],int num);
extern int LoadRotation(char Path[256],int num);
extern int LoadCourse(char coursefile[256],int IfNum);
extern void SetDefaultCourseData();

extern char SignName[SIGN_MAX][16];
extern char CrsSaveFileName[256];
extern int ObstacleFlag[30];

extern Course_t Course;
extern Scenario_t Scenario[LEVEL_MAX];
extern GraphicInfo_t GraphicInfo;

#endif