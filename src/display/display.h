#ifndef DISPLAY_H
#define DISPLAY_H

static const int GRADE_MAX	= 16;

typedef struct{
	int RoadMaxLevel[2],RoadMaxPoint[2],MaxClearGrade,GradeHS,GradeHSSum;
}Status_t;

extern Status_t Status;

extern int LoadBlackBackGraphic(int Back_Num);
extern int LoadWhiteBackGraphic(int Back_Num);
extern void LoadGraphic();
extern void FontSetting();
extern void ColorSetting();
extern void DrawNameSetting();
extern void FontSizePosSetting();
extern void DrawMain();
extern void ResetAddPoint();
extern void EnterAddPoint(int x, int y, int num);
extern void SetKeyName();

extern int ViewMode;
extern int ScreenShotCount;
extern int GameStartRemainCount;
extern int BlackBackRemainCount,WhiteBackRemainCount,MaskBackRemainCount;

#endif