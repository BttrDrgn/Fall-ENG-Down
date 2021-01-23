#include <DxLib.h>
#include <animation/animation.h>
#include <display/display.h>
#include <drop/drop.h>
#include <file_list/file_list.h>
#include <fps/fps.h>
#include <game_play/game_play.h>
#include <key/key.h>
#include <layer/layer.h>
#include <load/load.h>
#include <macro_function.h>
#include <main.h>
#include <menu/menu.h>
#include <save/save.h>
#include <sound_effect/sound_effect.h>

const int V_YEAR		= 2015;
const int V_MONTH		= 7;
const int V_DAY			= 15;
const int FRAMEX		= 240;
const int FRAMEY		= 96;
const int FRAMEWIDTH	= 160;
const int FRAMEHEIGHT	= 320;
const double PI = 3.1415926535897931;

Status_t Status;

char BoardDrawName[BOARD_MAX][20];
char SignDrawName[6][5];
char GradeName[GRADE_MAX+1][16];
int HpFlag;
int VpFlag;
int MonoFlag[7];
int RCFlag[7];
int RevFlag[3];
int CloneTimes[4];
int AHPos[2];
int TetriminoSize;
int BlackBackGraphic[2] = {0};
int BlackBackGraphic_Num = -100;
int WhiteBackGraphic[2] = {0};
int WhiteBackGraphic_Num = -100;
int BlockColorTable[2][8] = {{0,1,2,3,4,5,6,7},{4,1,2,5,3,0,6,7}};
int ScreenShotCount = 0;
int ViewMode = 0;
int GameStartRemainCount = 0;
int BlackBackRemainCount = 0,WhiteBackRemainCount = 0,MaskBackRemainCount = 0;
int FrameCount = 0;
int addPointTable[20][4] = { 0 };
int cascadeArrowBase = 0;
char KeyName[256][16] = { 0 };
char PadName[32][16] = { 0 };

typedef struct{
	int White,Black,Red,Yellow,Green,Purple;
}Color_t;

typedef struct{
	int Board,Count,Ren,Ready,Warning,Hold,AddPoint[3],BigBoard,MiddleBoard;
}Font_t;

typedef struct{
	int Curtain[2],Frame,Select[8],Block[16],Explosion[80],Shutter[3],Word[9],Point_Color[3],Point_Mask[22],LDTARE_Color[3],LDTARE_Mask[20],SpeedChange,FlipFlop[4],VPress,HPress,Effect,Lift[2],BlackOut,TextColor,Text[5];
	int cascadeArrow;
	int ruledLine[3];
	int cascadeColor[2];
	int cascadeMask;
	int cascadeBlock;
	int levelupBlock;
	int effectRing[2];
}Graphic_t;

Color_t Color;
Font_t Font;
Graphic_t Graphic;

void SetKeyName(){
	strcpy_s(KeyName[1], _countof(KeyName[1]), "ESCAPE");
	strcpy_s(KeyName[2], _countof(KeyName[2]), "1");
	strcpy_s(KeyName[3], _countof(KeyName[3]), "2");
	strcpy_s(KeyName[4], _countof(KeyName[4]), "3");
	strcpy_s(KeyName[5], _countof(KeyName[5]), "4");
	strcpy_s(KeyName[6], _countof(KeyName[6]), "5");
	strcpy_s(KeyName[7], _countof(KeyName[7]), "6");
	strcpy_s(KeyName[8], _countof(KeyName[8]), "7");
	strcpy_s(KeyName[9], _countof(KeyName[9]), "8");
	strcpy_s(KeyName[10], _countof(KeyName[10]), "9");
	strcpy_s(KeyName[11], _countof(KeyName[11]), "0");
	strcpy_s(KeyName[12], _countof(KeyName[12]), "MINUS");
	strcpy_s(KeyName[13], _countof(KeyName[13]), "EQUALS");
	strcpy_s(KeyName[14], _countof(KeyName[14]), "BACK");
	strcpy_s(KeyName[15], _countof(KeyName[15]), "TAB");
	strcpy_s(KeyName[16], _countof(KeyName[16]), "Q");
	strcpy_s(KeyName[17], _countof(KeyName[17]), "W");
	strcpy_s(KeyName[18], _countof(KeyName[18]), "E");
	strcpy_s(KeyName[19], _countof(KeyName[19]), "R");
	strcpy_s(KeyName[20], _countof(KeyName[20]), "T");
	strcpy_s(KeyName[21], _countof(KeyName[21]), "Y");
	strcpy_s(KeyName[22], _countof(KeyName[22]), "U");
	strcpy_s(KeyName[23], _countof(KeyName[23]), "I");
	strcpy_s(KeyName[24], _countof(KeyName[24]), "O");
	strcpy_s(KeyName[25], _countof(KeyName[25]), "P");
	strcpy_s(KeyName[26], _countof(KeyName[26]), "LBRACKET");
	strcpy_s(KeyName[27], _countof(KeyName[27]), "RBRACKET");
	strcpy_s(KeyName[28], _countof(KeyName[28]), "RETURN");
	strcpy_s(KeyName[29], _countof(KeyName[29]), "LCONTROL");
	strcpy_s(KeyName[30], _countof(KeyName[30]), "A");
	strcpy_s(KeyName[31], _countof(KeyName[31]), "S");
	strcpy_s(KeyName[32], _countof(KeyName[32]), "D");
	strcpy_s(KeyName[33], _countof(KeyName[33]), "F");
	strcpy_s(KeyName[34], _countof(KeyName[34]), "G");
	strcpy_s(KeyName[35], _countof(KeyName[35]), "H");
	strcpy_s(KeyName[36], _countof(KeyName[36]), "J");
	strcpy_s(KeyName[37], _countof(KeyName[37]), "K");
	strcpy_s(KeyName[38], _countof(KeyName[38]), "L");
	strcpy_s(KeyName[39], _countof(KeyName[39]), "SEMICOLON");
	strcpy_s(KeyName[40], _countof(KeyName[40]), "APOSTROPHE");
	strcpy_s(KeyName[41], _countof(KeyName[41]), "GRAVE");
	strcpy_s(KeyName[42], _countof(KeyName[42]), "LSHIFT");
	strcpy_s(KeyName[43], _countof(KeyName[43]), "BACKSLASH");
	strcpy_s(KeyName[44], _countof(KeyName[44]), "Z");
	strcpy_s(KeyName[45], _countof(KeyName[45]), "X");
	strcpy_s(KeyName[46], _countof(KeyName[46]), "C");
	strcpy_s(KeyName[47], _countof(KeyName[47]), "V");
	strcpy_s(KeyName[48], _countof(KeyName[48]), "B");
	strcpy_s(KeyName[49], _countof(KeyName[49]), "N");
	strcpy_s(KeyName[50], _countof(KeyName[50]), "M");
	strcpy_s(KeyName[51], _countof(KeyName[51]), "COMMA");
	strcpy_s(KeyName[52], _countof(KeyName[52]), "PERIOD");
	strcpy_s(KeyName[53], _countof(KeyName[53]), "SLASH");
	strcpy_s(KeyName[54], _countof(KeyName[54]), "RSHIFT");
	strcpy_s(KeyName[55], _countof(KeyName[55]), "MULTIPLY");
	strcpy_s(KeyName[56], _countof(KeyName[56]), "LMENU");
	strcpy_s(KeyName[57], _countof(KeyName[57]), "SPACE");
	strcpy_s(KeyName[58], _countof(KeyName[58]), "CAPITAL");
	strcpy_s(KeyName[59], _countof(KeyName[59]), "F1");
	strcpy_s(KeyName[60], _countof(KeyName[60]), "F2");
	strcpy_s(KeyName[61], _countof(KeyName[61]), "F3");
	strcpy_s(KeyName[62], _countof(KeyName[62]), "F4");
	strcpy_s(KeyName[63], _countof(KeyName[63]), "F5");
	strcpy_s(KeyName[64], _countof(KeyName[64]), "F6");
	strcpy_s(KeyName[65], _countof(KeyName[65]), "F7");
	strcpy_s(KeyName[66], _countof(KeyName[66]), "F8");
	strcpy_s(KeyName[67], _countof(KeyName[67]), "F9");
	strcpy_s(KeyName[68], _countof(KeyName[68]), "F10");
	strcpy_s(KeyName[69], _countof(KeyName[69]), "NUMLOCK");
	strcpy_s(KeyName[70], _countof(KeyName[70]), "SCROLL");
	strcpy_s(KeyName[71], _countof(KeyName[71]), "NUMPAD7");
	strcpy_s(KeyName[72], _countof(KeyName[72]), "NUMPAD8");
	strcpy_s(KeyName[73], _countof(KeyName[73]), "NUMPAD9");
	strcpy_s(KeyName[74], _countof(KeyName[74]), "SUBTRACT");
	strcpy_s(KeyName[75], _countof(KeyName[75]), "NUMPAD4");
	strcpy_s(KeyName[76], _countof(KeyName[76]), "NUMPAD5");
	strcpy_s(KeyName[77], _countof(KeyName[77]), "NUMPAD6");
	strcpy_s(KeyName[78], _countof(KeyName[78]), "ADD");
	strcpy_s(KeyName[79], _countof(KeyName[79]), "NUMPAD1");
	strcpy_s(KeyName[80], _countof(KeyName[80]), "NUMPAD2");
	strcpy_s(KeyName[81], _countof(KeyName[81]), "NUMPAD3");
	strcpy_s(KeyName[82], _countof(KeyName[82]), "NUMPAD0");
	strcpy_s(KeyName[83], _countof(KeyName[83]), "DECIMAL");
	strcpy_s(KeyName[86], _countof(KeyName[86]), "OEM_102");
	strcpy_s(KeyName[87], _countof(KeyName[87]), "F11");
	strcpy_s(KeyName[88], _countof(KeyName[88]), "F12");
	strcpy_s(KeyName[100], _countof(KeyName[100]), "F13");
	strcpy_s(KeyName[101], _countof(KeyName[101]), "F14");
	strcpy_s(KeyName[102], _countof(KeyName[102]), "F15");
	strcpy_s(KeyName[112], _countof(KeyName[112]), "KANA");
	strcpy_s(KeyName[115], _countof(KeyName[115]), "ABNT_C1");
	strcpy_s(KeyName[121], _countof(KeyName[121]), "CONVERT");
	strcpy_s(KeyName[123], _countof(KeyName[123]), "NOCONVERT");
	strcpy_s(KeyName[125], _countof(KeyName[125]), "YEN");
	strcpy_s(KeyName[126], _countof(KeyName[126]), "ABNT_C2");
	strcpy_s(KeyName[141], _countof(KeyName[141]), "NUMPADEQUALS");
	strcpy_s(KeyName[144], _countof(KeyName[144]), "PREVTRACK");
	strcpy_s(KeyName[145], _countof(KeyName[145]), "AT");
	strcpy_s(KeyName[146], _countof(KeyName[146]), "COLON");
	strcpy_s(KeyName[147], _countof(KeyName[147]), "UNDERLINE");
	strcpy_s(KeyName[148], _countof(KeyName[148]), "KANJI");
	strcpy_s(KeyName[149], _countof(KeyName[149]), "STOP");
	strcpy_s(KeyName[150], _countof(KeyName[150]), "AX");
	strcpy_s(KeyName[151], _countof(KeyName[151]), "UNLABELED");
	strcpy_s(KeyName[153], _countof(KeyName[153]), "NEXTTRACK");
	strcpy_s(KeyName[156], _countof(KeyName[156]), "NUMPADENTER");
	strcpy_s(KeyName[157], _countof(KeyName[157]), "RCONTROL");
	strcpy_s(KeyName[160], _countof(KeyName[160]), "MUTE");
	strcpy_s(KeyName[161], _countof(KeyName[161]), "CALCULATOR");
	strcpy_s(KeyName[162], _countof(KeyName[162]), "PLAYPAUSE");
	strcpy_s(KeyName[164], _countof(KeyName[164]), "MEDIASTOP");
	strcpy_s(KeyName[174], _countof(KeyName[174]), "VOLUMEDOWN");
	strcpy_s(KeyName[176], _countof(KeyName[176]), "VOLUMEUP");
	strcpy_s(KeyName[178], _countof(KeyName[178]), "WEBHOME");
	strcpy_s(KeyName[179], _countof(KeyName[179]), "NUMPADCOMMA");
	strcpy_s(KeyName[181], _countof(KeyName[181]), "DIVIDE");
	strcpy_s(KeyName[183], _countof(KeyName[183]), "SYSRQ");
	strcpy_s(KeyName[184], _countof(KeyName[184]), "RMENU");
	strcpy_s(KeyName[197], _countof(KeyName[197]), "PAUSE");
	strcpy_s(KeyName[199], _countof(KeyName[199]), "HOME");
	strcpy_s(KeyName[200], _countof(KeyName[200]), "UP");
	strcpy_s(KeyName[201], _countof(KeyName[201]), "PRIOR");
	strcpy_s(KeyName[203], _countof(KeyName[203]), "LEFT");
	strcpy_s(KeyName[205], _countof(KeyName[205]), "RIGHT");
	strcpy_s(KeyName[207], _countof(KeyName[207]), "END");
	strcpy_s(KeyName[208], _countof(KeyName[208]), "DOWN");
	strcpy_s(KeyName[209], _countof(KeyName[209]), "NEXT");
	strcpy_s(KeyName[210], _countof(KeyName[210]), "INSERT");
	strcpy_s(KeyName[211], _countof(KeyName[211]), "DELETE");
	strcpy_s(KeyName[219], _countof(KeyName[219]), "LWIN");
	strcpy_s(KeyName[220], _countof(KeyName[220]), "RWIN");
	strcpy_s(KeyName[221], _countof(KeyName[221]), "APPS");
	strcpy_s(KeyName[222], _countof(KeyName[222]), "POWER");
	strcpy_s(KeyName[223], _countof(KeyName[223]), "SLEEP");
	strcpy_s(KeyName[227], _countof(KeyName[227]), "WAKE");
	strcpy_s(KeyName[229], _countof(KeyName[229]), "WEBSEARCH");
	strcpy_s(KeyName[230], _countof(KeyName[230]), "WEBFAVORITES");
	strcpy_s(KeyName[231], _countof(KeyName[231]), "WEBREFRESH");
	strcpy_s(KeyName[232], _countof(KeyName[232]), "WEBSTOP");
	strcpy_s(KeyName[233], _countof(KeyName[233]), "WEBFORWARD");
	strcpy_s(KeyName[234], _countof(KeyName[234]), "WEBBACK");
	strcpy_s(KeyName[235], _countof(KeyName[235]), "MYCOMPUTER");
	strcpy_s(KeyName[236], _countof(KeyName[236]), "MAIL");
	strcpy_s(KeyName[237], _countof(KeyName[237]), "MEDIASELECT");

	strcpy_s(PadName[0], _countof(PadName[0]), "DOWN");
	strcpy_s(PadName[1], _countof(PadName[1]), "LEFT");
	strcpy_s(PadName[2], _countof(PadName[2]), "RIGHT");
	strcpy_s(PadName[3], _countof(PadName[3]), "UP");
	strcpy_s(PadName[4], _countof(PadName[4]), "BUTTON 1");
	strcpy_s(PadName[5], _countof(PadName[5]), "BUTTON 2");
	strcpy_s(PadName[6], _countof(PadName[6]), "BUTTON 3");
	strcpy_s(PadName[7], _countof(PadName[7]), "BUTTON 4");
	strcpy_s(PadName[8], _countof(PadName[8]), "BUTTON 5");
	strcpy_s(PadName[9], _countof(PadName[9]), "BUTTON 6");
	strcpy_s(PadName[10], _countof(PadName[10]), "BUTTON 7");
	strcpy_s(PadName[11], _countof(PadName[11]), "BUTTON 8");
	strcpy_s(PadName[12], _countof(PadName[12]), "BUTTON 9");
	strcpy_s(PadName[13], _countof(PadName[13]), "BUTTON 10");
	strcpy_s(PadName[14], _countof(PadName[14]), "BUTTON 11");
	strcpy_s(PadName[15], _countof(PadName[15]), "BUTTON 12");
	strcpy_s(PadName[16], _countof(PadName[16]), "BUTTON 13");
	strcpy_s(PadName[17], _countof(PadName[17]), "BUTTON 14");
	strcpy_s(PadName[18], _countof(PadName[18]), "BUTTON 15");
	strcpy_s(PadName[19], _countof(PadName[19]), "BUTTON 16");
	strcpy_s(PadName[20], _countof(PadName[20]), "BUTTON 17");
	strcpy_s(PadName[21], _countof(PadName[21]), "BUTTON 18");
	strcpy_s(PadName[22], _countof(PadName[22]), "BUTTON 19");
	strcpy_s(PadName[23], _countof(PadName[23]), "BUTTON 20");
	strcpy_s(PadName[24], _countof(PadName[24]), "BUTTON 21");
	strcpy_s(PadName[25], _countof(PadName[25]), "BUTTON 22");
	strcpy_s(PadName[26], _countof(PadName[26]), "BUTTON 23");
	strcpy_s(PadName[27], _countof(PadName[27]), "BUTTON 24");
	strcpy_s(PadName[28], _countof(PadName[28]), "BUTTON 25");
	strcpy_s(PadName[29], _countof(PadName[29]), "BUTTON 26");
	strcpy_s(PadName[30], _countof(PadName[30]), "BUTTON 27");
	strcpy_s(PadName[31], _countof(PadName[31]), "BUTTON 28");
}

int LoadBlackBackGraphic(int Back_Num){
	if (BlackBackGraphic_Num != Back_Num){
		char Path[256] = { 0 };
		BlackBackGraphic_Num = Back_Num;
		DeleteGraph(BlackBackGraphic[1]);
		BlackBackGraphic[1] = BlackBackGraphic[0];
		if (Back_Num < 0)sprintf_s(Path, sizeof(Path), "dat/img/back/black/main.png");
		else sprintf_s(Path, sizeof(Path), "dat/img/back/black/%02d.png", Back_Num);
		BlackBackGraphic[0] = LoadGraph(Path);
		return 1;
	}
	else return 0;
}

int LoadWhiteBackGraphic(int Back_Num){
	if (WhiteBackGraphic_Num != Back_Num){
		char Path[256] = { 0 };
		WhiteBackGraphic_Num = Back_Num;
		DeleteGraph(WhiteBackGraphic[1]);
		WhiteBackGraphic[1] = WhiteBackGraphic[0];
		if (Back_Num < 0)sprintf_s(Path, sizeof(Path), "dat/img/back/white/main.png");
		else sprintf_s(Path, sizeof(Path), "dat/img/back/white/%02d.png", Back_Num);
		WhiteBackGraphic[0] = LoadGraph(Path);
		return 1;
	}
	else return 0;
}

void LoadGraphic(){
	Graphic.Curtain[0] = LoadGraph("dat/img/fieldcurtain.png");
	Graphic.Curtain[1] = LoadGraph("dat/img/nextcurtain.png");
	Graphic.Frame = LoadGraph("dat/img/frame.png");
	LoadDivGraph("dat/img/block.png", 16, 8, 2, 16, 16, Graphic.Block);
	LoadDivGraph("dat/img/select.png", 8, 1, 8, 160, 32, Graphic.Select);
	LoadDivGraph("dat/img/explode.png", 80, 8, 10, 48, 48, Graphic.Explosion);
	LoadDivGraph("dat/img/shutter.png", 3, 3, 1, 96, 64, Graphic.Shutter);
	LoadDivGraph("dat/img/word.png", 9, 1, 9, 135, 18, Graphic.Word);
	LoadDivGraph("dat/img/point_color.png", 3, 3, 1, 6, 320, Graphic.Point_Color);
	LoadDivGraph("dat/img/point_mask.png", 22, 22, 1, 6, 320, Graphic.Point_Mask);
	LoadDivGraph("dat/img/ldtare_color.png", 3, 1, 3, 176, 6, Graphic.LDTARE_Color);
	LoadDivGraph("dat/img/ldtare_mask.png", 20, 1, 20, 176, 6, Graphic.LDTARE_Mask);
	LoadDivGraph("dat/img/flipflop.png", 4, 4, 1, 40, 320, Graphic.FlipFlop);
	LoadDivGraph("dat/img/lift.png", 2, 1, 2, 160, 16, Graphic.Lift);
	Graphic.SpeedChange = LoadGraph("dat/img/spchange.png");
	Graphic.VPress = LoadGraph("dat/img/vpress.png");
	Graphic.HPress = LoadGraph("dat/img/hpress.png");
	Graphic.Effect = LoadGraph("dat/img/effect.png");
	Graphic.BlackOut = LoadGraph("dat/img/blackout.png");
	Graphic.TextColor = LoadGraph("dat/img/textcolor.png");
	Graphic.cascadeArrow = LoadGraph("dat/img/cascade_arrow.png");
	Graphic.ruledLine[0] = LoadGraph("dat/img/ruled_line_00.png");
	Graphic.ruledLine[1] = LoadGraph("dat/img/ruled_line_01.png");
	Graphic.ruledLine[2] = LoadGraph("dat/img/ruled_line_02.png");
	LoadDivGraph("dat/img/cascade_color.png", 2, 1, 2, 176, 38, Graphic.cascadeColor);
	Graphic.cascadeMask = LoadGraph("dat/img/cascade_mask.png");
	Graphic.cascadeBlock = LoadGraph("dat/img/cascade_block.png");
	Graphic.levelupBlock = LoadGraph("dat/img/levelup_block.png");
	Graphic.effectRing[0] = LoadGraph("dat/img/effect_ring_0.png");
	Graphic.effectRing[1] = LoadGraph("dat/img/effect_ring_1.png");
}

void FontSetting(){
	Font.Board = CreateFontToHandle("ＭＳ ゴシック", 12, 9, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
	Font.Ren = CreateFontToHandle("ＭＳ ゴシック", 12, 9, DX_FONTTYPE_NORMAL);
	Font.Hold = CreateFontToHandle("ＭＳ ゴシック", 18, 9, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
	Font.AddPoint[0] = Font.Ren;
	Font.AddPoint[1] = CreateFontToHandle("ＭＳ ゴシック", 15, 9, DX_FONTTYPE_NORMAL);
	Font.AddPoint[2] = CreateFontToHandle("ＭＳ ゴシック", 18, 9, DX_FONTTYPE_NORMAL);
	Font.BigBoard = Font.Hold;
	Font.MiddleBoard = CreateFontToHandle("ＭＳ ゴシック", 14, 9, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
}

void ColorSetting(){
	Color.White = GetColor(255, 255, 255);
	Color.Red = GetColor(255, 0, 0);
	Color.Yellow = GetColor(255, 255, 0);
	Color.Purple = GetColor(224, 0, 224);
	Color.Green = GetColor(0, 255, 0);
	Color.Black = GetColor(0, 0, 0);
}

void DrawNameSetting(){
	strcpy_s(BoardDrawName[0], sizeof(BoardDrawName[0]), "LEVEL");
	strcpy_s(BoardDrawName[1], sizeof(BoardDrawName[1]), "POINT");
	strcpy_s(BoardDrawName[2], sizeof(BoardDrawName[2]), "MAX POINTS");
	strcpy_s(BoardDrawName[3], sizeof(BoardDrawName[3]), "目標時点");
	strcpy_s(BoardDrawName[4], sizeof(BoardDrawName[4]), "余剰時間量");
	strcpy_s(BoardDrawName[5], sizeof(BoardDrawName[5]), "今節経過時間");
	strcpy_s(BoardDrawName[6], sizeof(BoardDrawName[6]), "合計経過時間");
	strcpy_s(BoardDrawName[7], sizeof(BoardDrawName[7]), "妨害開始時点");
	strcpy_s(BoardDrawName[8], sizeof(BoardDrawName[8]), "得点");
	strcpy_s(BoardDrawName[9], sizeof(BoardDrawName[9]), "最高得点");
	strcpy_s(BoardDrawName[10], sizeof(BoardDrawName[10]), "テトリミノ");
	strcpy_s(BoardDrawName[11], sizeof(BoardDrawName[11]), "TOTAL TETROMINO");
	strcpy_s(BoardDrawName[12], sizeof(BoardDrawName[12]), "ライン");
	strcpy_s(BoardDrawName[13], sizeof(BoardDrawName[13]), "合計ﾗｲﾝ");
	strcpy_s(BoardDrawName[14], sizeof(BoardDrawName[14]), "ﾃﾄﾘﾐﾉ/分");
	strcpy_s(BoardDrawName[15], sizeof(BoardDrawName[15]), "ﾗｲﾝ/分");
	strcpy_s(BoardDrawName[16], sizeof(BoardDrawName[16]), "テトリス");
	strcpy_s(BoardDrawName[17], sizeof(BoardDrawName[17]), "合計ﾃﾄﾘｽ");
	strcpy_s(BoardDrawName[18], sizeof(BoardDrawName[18]), "Ｂ２Ｂ");
	strcpy_s(BoardDrawName[19], sizeof(BoardDrawName[19]), "合計B2B");
	strcpy_s(BoardDrawName[20], sizeof(BoardDrawName[20]), "Ｔスピン");
	strcpy_s(BoardDrawName[21], sizeof(BoardDrawName[21]), "合計Tｽﾋﾟﾝ");
	strcpy_s(BoardDrawName[22], sizeof(BoardDrawName[22]), "ＲＥＮ");
	strcpy_s(BoardDrawName[23], sizeof(BoardDrawName[23]), "合計REN");
	strcpy_s(BoardDrawName[24], sizeof(BoardDrawName[24]), "Ｇ分子");
	strcpy_s(BoardDrawName[25], sizeof(BoardDrawName[25]), "Ｇ分母");
	strcpy_s(BoardDrawName[26], sizeof(BoardDrawName[26]), "固定時間");
	strcpy_s(BoardDrawName[27], sizeof(BoardDrawName[27]), "LINE TIME");
	strcpy_s(BoardDrawName[28], sizeof(BoardDrawName[28]), "出現猶予");
	strcpy_s(BoardDrawName[29], sizeof(BoardDrawName[29]), "DAS");
	strcpy_s(BoardDrawName[30], sizeof(BoardDrawName[30]), "評価");
	strcpy_s(BoardDrawName[31], sizeof(BoardDrawName[31]), "得点率");
	strcpy_s(BoardDrawName[32], sizeof(BoardDrawName[32]), "最長ＲＥＮ");
	strcpy_s(BoardDrawName[33], sizeof(BoardDrawName[33]), "総合最長REN");
	strcpy_s(BoardDrawName[34], sizeof(BoardDrawName[34]), "乱数/ゲーム");
	strcpy_s(BoardDrawName[35], sizeof(BoardDrawName[35]), "乱数/レベル");
	strcpy_s(BoardDrawName[36], sizeof(BoardDrawName[36]), "乱数/ライン");
	strcpy_s(BoardDrawName[37], sizeof(BoardDrawName[37]), "RNG / TETROMINO");
	strcpy_s(BoardDrawName[38], sizeof(BoardDrawName[38]), "乱数/フレーム");

	strcpy_s(SignDrawName[0], sizeof(SignDrawName[0]), "＜");
	strcpy_s(SignDrawName[1], sizeof(SignDrawName[1]), "≦");
	strcpy_s(SignDrawName[2], sizeof(SignDrawName[2]), "＞");
	strcpy_s(SignDrawName[3], sizeof(SignDrawName[3]), "≧");
	strcpy_s(SignDrawName[4], sizeof(SignDrawName[4]), "＝");
	strcpy_s(SignDrawName[5], sizeof(SignDrawName[5]), "≠");

	strcpy_s(GradeName[0], sizeof(GradeName[0]), "5th Grade");
	strcpy_s(GradeName[1], sizeof(GradeName[1]), "4th Grade");
	strcpy_s(GradeName[2], sizeof(GradeName[2]), "3rd Grade");
	strcpy_s(GradeName[3], sizeof(GradeName[3]), "2nd Grade");
	strcpy_s(GradeName[4], sizeof(GradeName[4]), "1st Grade");
	strcpy_s(GradeName[5], sizeof(GradeName[5]), "1st Stage");
	strcpy_s(GradeName[6], sizeof(GradeName[6]), "2nd Stage");
	strcpy_s(GradeName[7], sizeof(GradeName[7]), "3rd Stage");
	strcpy_s(GradeName[8], sizeof(GradeName[8]), "4th Stage");
	strcpy_s(GradeName[9], sizeof(GradeName[9]), "5th Stage");
	strcpy_s(GradeName[10], sizeof(GradeName[10]), "6th Stage");
	strcpy_s(GradeName[11], sizeof(GradeName[11]), "7th Stage");
	strcpy_s(GradeName[12], sizeof(GradeName[12]), "8th Stage");
	strcpy_s(GradeName[13], sizeof(GradeName[13]), "9th Stage");
	strcpy_s(GradeName[14], sizeof(GradeName[14]), "10th Stage");
	strcpy_s(GradeName[15], sizeof(GradeName[15]), "Master");
	strcpy_s(GradeName[16], sizeof(GradeName[16]), "Grand Master");
}

void MakeTextGraphic(int *TextGraphic, int FontHandle, int TextColor, char Text[], int TextRangeX = 640, int TextRangeY = 480, double ExtRate = 1.0, int TextColorMaskFlag = 0, int MaskGraphic = 0){
	int Length = strlen(Text);
	int Width = GetDrawStringWidthToHandle(Text, Length, FontHandle);
	int Pos = 0;
	int TempScreen;
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DeleteGraph(*TextGraphic);
	if (Width < (int)(TextRangeX*ExtRate)){
		Pos = (int)(TextRangeX*ExtRate / 2 - Width / 2);
		Width = (int)(TextRangeX*ExtRate);
	}
	TempScreen = MakeScreen(Width, TextRangeY, TRUE);
	SetDrawScreen(TempScreen);
	DrawStringToHandle(Pos, 0, Text, TextColor, FontHandle);
	*TextGraphic = MakeScreen(TextRangeX, TextRangeY, TRUE);
	SetDrawScreen(*TextGraphic);
	DrawExtendGraph(0, 0, TextRangeX, TextRangeY, TempScreen, TRUE);
	if (TextColorMaskFlag){
		SetDrawBlendMode(DX_BLENDMODE_MUL, 255);
		DrawGraph(0, 0, MaskGraphic, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	SetDrawScreen(DX_SCREEN_BACK);
	DeleteGraph(TempScreen);
}

void FontSizePosSetting(){
	int TextRangeX, DisposableFont;

	DeleteFontToHandle(Font.Count);
	Font.Count = CreateFontToHandle(Course.Font, 18, Course.FontThickness, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);

	DeleteFontToHandle(Font.Ready);
	Font.Ready = CreateFontToHandle(Course.Font, 18, Course.FontThickness, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
	TextRangeX = GetDrawStringWidthToHandle("READY... GO", 11, Font.Ready);
	Course.ReadyPos = 320 - TextRangeX / 2;

	DeleteFontToHandle(Font.Warning);
	Font.Warning = CreateFontToHandle(Course.Font, 18, Course.FontThickness, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
	TextRangeX = GetDrawStringWidthToHandle("！Warning！", 11, Font.Warning);
	Course.WarningPos = 320 - TextRangeX / 2;
	TextRangeX = GetDrawStringWidthToHandle("LEVEL999", 8, Font.Warning);
	Course.NowLevelPos = 320 - TextRangeX / 2;

	SetDrawMode(DX_DRAWMODE_BILINEAR);

	DisposableFont = CreateFontToHandle(Course.Font, 16, Course.FontThickness, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
	for (int i = 1; i < 5; i++)MakeTextGraphic(&Graphic.Text[i], DisposableFont, GetColor(255, 255, 255), Course.TitleText[i], FRAMEWIDTH, 24, 1.0);
	DeleteFontToHandle(DisposableFont);

	DisposableFont = CreateFontToHandle(Course.Font, 24, Course.FontThickness, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
	MakeTextGraphic(&Graphic.Text[0], DisposableFont, GetColor(255, 255, 255), Course.TitleText[0], FRAMEWIDTH, 32, 0.8, 1, Graphic.TextColor);
	DeleteFontToHandle(DisposableFont);

	SetDrawMode(DX_DRAWMODE_NEAREST);
}

void SelecterEffect(int SelecterPosX, int SelecterPosY, int Density){
	static int SelecterX = 224;
	static int SelecterY = 96;
	SetDrawBlendMode(DX_BLENDMODE_ADD, Density);
	SelecterY += (SelecterPosY - SelecterY) / 3;
	if (SelecterY < SelecterPosY)SelecterY++;
	if (SelecterY > SelecterPosY)SelecterY--;
	SelecterX += (SelecterPosX - SelecterX) / 3;
	if (SelecterX < SelecterPosX)SelecterX++;
	if (SelecterX > SelecterPosX)SelecterX--;
	DrawGraph(SelecterX, SelecterY, Graphic.Effect, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void DrawCommonA(int HideBlack, int HideWhite, int HideMask){
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	if (MainFlag / 100 == 1 || MainFlag / 100 == 2)SetDrawBright(Scenario[Progress.Level].BlackBackBright[0], Scenario[Progress.Level].BlackBackBright[1], Scenario[Progress.Level].BlackBackBright[2]);
	else SetDrawBright(255, 255, 255);
	if (!HideBlack)DrawGraph(0, 0, BlackBackGraphic[0], FALSE);
	if (BlackBackRemainCount == 0){
		if (BlackBackGraphic[0] != BlackBackGraphic[1])DeleteGraph(BlackBackGraphic[1]);
		BlackBackRemainCount = -1;
	}
	else if (BlackBackRemainCount > 0){
		if (BlackBackGraphic[0] != BlackBackGraphic[1]){
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, BlackBackRemainCount * 255 / 80);
			if (!HideBlack)DrawGraph(0, 0, BlackBackGraphic[1], FALSE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
	}
	SetDrawBright(255, 255, 255);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	if (Save.ReadSystem(Save.ANIMATION)){
		int m_src, w_src;
		m_src = MakeScreen(640, 480, FALSE);
		w_src = MakeScreen(640, 480, FALSE);
		SetDrawScreen(m_src);
		SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
		if (!HideMask){
			if (MainFlag / 100 == 1 || MainFlag / 100 == 2){
				SetDrawBright(Scenario[Progress.Level].MaskBackBright[0], Scenario[Progress.Level].MaskBackBright[1], Scenario[Progress.Level].MaskBackBright[2]);
			}
			else {
				SetDrawBright(255, 255, 255);
			}
			if (GraphicInfo.MaskLevel >= 0){
				Animation.Draw(GraphicInfo.MaskNumber);
			}
			else {
				Animation.Draw(-1);
			}
			SetDrawBright(255, 255, 255);
		}
		if (ViewMode < 2 && (!HideBlack || !HideWhite)){
			SetDrawScreen(w_src);
			SetDrawBlendMode(DX_BLENDMODE_INVSRC, 255);
			DrawGraph(0, 0, m_src, FALSE);

			SetDrawScreen(DX_SCREEN_BACK);
			SetDrawBlendMode(DX_BLENDMODE_MUL, 255);
			DrawGraph(0, 0, w_src, FALSE);

			SetDrawScreen(w_src);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			if (MainFlag / 100 == 1 || MainFlag / 100 == 2)SetDrawBright(Scenario[Progress.Level].WhiteBackBright[0], Scenario[Progress.Level].WhiteBackBright[1], Scenario[Progress.Level].WhiteBackBright[2]);
			else SetDrawBright(255, 255, 255);
			if (!HideWhite)DrawGraph(0, 0, WhiteBackGraphic[0], FALSE);
			if (WhiteBackRemainCount == 0){
				if (WhiteBackGraphic[0] != WhiteBackGraphic[1])DeleteGraph(WhiteBackGraphic[1]);
				WhiteBackRemainCount = -1;
			}
			else if (WhiteBackRemainCount > 0){
				if (WhiteBackGraphic[0] != WhiteBackGraphic[1]){
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, WhiteBackRemainCount * 255 / 80);
					if (!HideWhite)DrawGraph(0, 0, WhiteBackGraphic[1], FALSE);
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
				}
			}
			SetDrawBright(255, 255, 255);
			SetDrawBlendMode(DX_BLENDMODE_MUL, 255);
			DrawGraph(0, 0, m_src, FALSE);

			SetDrawScreen(DX_SCREEN_BACK);
			SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
			DrawGraph(0, 0, w_src, FALSE);
		}
		else {
			SetDrawScreen(DX_SCREEN_BACK);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			DrawGraph(0, 0, m_src, FALSE);
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		DeleteGraph(m_src);
		DeleteGraph(w_src);

	}
	if (BlackBackRemainCount > 0){
		BlackBackRemainCount--;
	}
	if (WhiteBackRemainCount > 0){
		WhiteBackRemainCount--;
	}
	if (MaskBackRemainCount > 0){
		MaskBackRemainCount--;
	}
}

void DrawCommonB(){
	SetDrawBlendMode(DX_BLENDMODE_MUL, 0);
	SetDrawBright(255, 255, 255);
	SetDrawBlendMode(DX_BLENDMODE_MULA, 255 * Save.ReadSystem(Save.DARKNESS) / 100);
	if (!Scenario[Progress.Level].HideCurtain[0]){
		DrawGraph(FRAMEX, FRAMEY, Graphic.Curtain[0], FALSE);
	}
	if (!Scenario[Progress.Level].HideCurtain[1]){
		DrawGraph(196, 16, Graphic.Curtain[1], FALSE);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void DrawCommonZ(){
	if (ScreenShotCount > 0){
		DrawStringToHandle(488, 11, "画面を撮影しました", Color.White, Font.Board);
		ScreenShotCount--;
	}
	DrawFormatStringToHandle(10, 11, Color.White, Font.Board, "%d年%d月%d日発兌", V_YEAR, V_MONTH, V_DAY);
	DrawFormatStringToHandle(10, 453, Color.White, Font.Board, "%4.1f FPS", Fps.Get());
}

void DrawDropEffect(){
	if (ObstacleFlag[OBS_DROPEFFECT]){
		int temp;
		SetDrawMode(DX_DRAWMODE_BILINEAR);
		temp = Scenario[Progress.Level].DropEffect[0];
		if (temp < 0){
			temp = GetRand(7) + 1;
		}
		if (temp >= 1 && temp <= 6){
			Drop.Draw(temp, Scenario[Progress.Level].DropEffect[1], Scenario[Progress.Level].DropEffect[2] * 0.01, Scenario[Progress.Level].DropEffect[3] * 0.01, (double)FRAMEX, 0.0, (double)(FRAMEX + FRAMEWIDTH), 480.0);
		}
		else if (temp >= 7 && temp <= 8){
			Drop.Draw(temp, Scenario[Progress.Level].DropEffect[1], Scenario[Progress.Level].DropEffect[2] * 0.01, Scenario[Progress.Level].DropEffect[3] * 0.01, 0.0, (double)FRAMEY, 640.0, (double)(FRAMEY + FRAMEHEIGHT));
		}
		SetDrawMode(DX_DRAWMODE_NEAREST);
	}
}

void DrawWord(){
	if (WordRemainCount > 0){
		int BtB = (WordFlag & 8) && 1, TSpin = (WordFlag & 16) && 1;
		if (BtB)DrawGraph(420, 286, Graphic.Word[5], TRUE);
		if (TSpin)DrawGraph(420 + BtB * 126, 286, Graphic.Word[6], TRUE);
		if (WordFlag & 7){
			if ((WordFlag & 48) == 48)DrawGraph(420 + (BtB + TSpin) % 2 * 126, 286 + (BtB&&TSpin) * 18, Graphic.Word[0], TRUE);
			else DrawGraph(420 + (BtB + TSpin) % 2 * 126, 286 + (BtB&&TSpin) * 18, Graphic.Word[WordFlag & 7], TRUE);
		}
		if (WordFlag & 64){
			DrawGraph(420 + (BtB + TSpin + 1) % 2 * 126, 286 + (BtB || TSpin) * 18, Graphic.Word[7], TRUE);
			DrawFormatStringToHandle(457 + (BtB + TSpin + 1) % 2 * 126, 286 + (BtB || TSpin) * 18, Color.Purple, Font.Ren, "%d", NowRen_Keep - 1);
			DrawFormatStringToHandle(456 + (BtB + TSpin + 1) % 2 * 126, 286 + (BtB || TSpin) * 18, Color.White, Font.Ren, "%d", NowRen_Keep - 1);
		}
		if (GetLineClearPoint > 0)DrawFormatStringToHandle(420, 322, Color.White, Font.Board, "ポイント +%d", GetLineClearPoint);
		if (GetLineClearScore > 0)DrawFormatStringToHandle(420, 340, Color.White, Font.Board, "スコア　 +%d", GetLineClearScore);
		WordRemainCount--;
	}
	else if (TimeLeftBonusTime > 0){
		DrawGraph(420, 286, Graphic.Word[8], TRUE);
		DrawFormatStringToHandle(420, 340, Color.White, Font.Board, "スコア　 +%d", TimeLeftGetScore);
		TimeLeftBonusTime--;
	}
}

void DrawRuledLine(){
	if (Save.ReadSystem(Save.RULED_LINE) > 0){
		SetDrawBlendMode(DX_BLENDMODE_ADD, 128);
		DrawGraph(FRAMEX, FRAMEY, Graphic.ruledLine[Save.ReadSystem(Save.RULED_LINE) - 1], TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

void ResetAddPoint(){
	memset(addPointTable, 0, sizeof(addPointTable));
}

void EnterAddPoint(int x, int y, int num){
	for (int i = 0; i < 20; i++){
		if (addPointTable[i][0] == 0){
			addPointTable[i][0] = 30;
			addPointTable[i][1] = x;
			addPointTable[i][2] = y;
			addPointTable[i][3] = num;
			i = 20;
		}
	}
}

void DrawAddPoint(){
	int addFontNum = Save.ReadSystem(Save.SHOW_ADDPT);
	if (addFontNum > 0){
		for (int i = 0; i < 20; i++){
			if (addPointTable[i][0] > 0){
				if (addPointTable[i][0] < 10){
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * addPointTable[i][0] / 10);
				}
				DrawFormatStringToHandle(FRAMEX + addPointTable[i][1] * 13 + 30, FRAMEY + addPointTable[i][2] * 16 + addPointTable[i][0] - 30, Color.White, Font.AddPoint[addFontNum - 1], "+%d", addPointTable[i][3]);
				addPointTable[i][0]--;
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
		}
	}
}

void DrawShutter(){
	if (ObstacleFlag[OBS_SHUTTER]){
		if (Scenario[Progress.Level].Shutter[0])DrawGraph(186, 32, Graphic.Shutter[1], TRUE);
		if (Scenario[Progress.Level].Shutter[1])DrawGraph(272, 32, Graphic.Shutter[1], TRUE);
		if (Scenario[Progress.Level].Shutter[2])DrawGraph(352, 32, Graphic.Shutter[2], TRUE);
		if (Scenario[Progress.Level].Shutter[3])DrawGraph(410, 32, Graphic.Shutter[2], TRUE);
	}
}

void DrawPress(){
	SetDrawArea(FRAMEX, FRAMEY, FRAMEX + FRAMEWIDTH, FRAMEY + FRAMEHEIGHT);
	if (ObstacleFlag[OBS_PRESS] && Scenario[Progress.Level].Press[0]){
		DrawGraph(FRAMEX, FRAMEY, Graphic.VPress, TRUE);
		DrawGraph(FRAMEX, FRAMEY + FRAMEHEIGHT - 80, Graphic.VPress, TRUE);
	}
	if (ObstacleFlag[OBS_PRESS] && Scenario[Progress.Level].Press[1]){
		DrawGraph(FRAMEX, FRAMEY, Graphic.HPress, TRUE);
		DrawGraph(FRAMEX + FRAMEWIDTH - 40, FRAMEY, Graphic.HPress, TRUE);
	}
	SetDrawArea(0, 0, 640, 480);
}

void DrawNexts(){
	int top, bottom, height, width;
	static int cnt = 0;
	if (CascadeNext == 0){
		cnt = 0;
	}
	else {
		cnt += 1;
	}
	if (MainPauseFlag == FALSE)SetDrawBright(Scenario[Progress.Level].HoldBright[0], Scenario[Progress.Level].HoldBright[1], Scenario[Progress.Level].HoldBright[2]);
	if (Tetrimino.Hold >= 0 && (!ObstacleFlag[OBS_SHUTTER] || !Scenario[Progress.Level].Shutter[0]) && !Scenario[Progress.Level].HideHold){
		top = 3;
		for (int i = 0; i < 3; i++)for (int j = 0; j<4; j++)if (Course.Shape[Scenario[Progress.Level].ShapeFlag][Tetrimino.Hold][0][i][j]){ top = i; i = 3; j = 4; }
		bottom = 0;
		for (int i = 3; i > 0; i--)for (int j = 0; j < 4; j++)if (Course.Shape[Scenario[Progress.Level].ShapeFlag][Tetrimino.Hold][0][i][j]){ bottom = i; i = 0; j = 4; }
		height = bottom - top + 1;
		if (height < 3)width = 16;
		else if (height == 3)width = 12;
		else width = 9;
		if (width == 16)SetDrawMode(DX_DRAWMODE_NEAREST);
		else SetDrawMode(DX_DRAWMODE_BILINEAR);
		for (int i = 0; i < height; i++){
			for (int j = 0; j < 4; j++){
				if (Course.Shape[Scenario[Progress.Level].ShapeFlag][Tetrimino.Hold][0][i + top][j]){
					if (width == 16){
						DrawGraph(202 + j*width, 48 + i*width*(RevFlag[2] * (-2) + 1) + RevFlag[2] * (height - 1)*width, Graphic.Block[BlockColorTable[Save.ReadSystem(Save.BLOCK_FLAG)][MonoFlag[1] ? 7 : RCFlag[1] ? IrregularRand[1] : Tetrimino.Hold]], TRUE);
						if (CascadeNext > 4 && Course.Shape[Scenario[Progress.Level].ShapeFlag][Tetrimino.Hold][0][i + top][j] == 2){
							DrawGraph(202 + j*width, 48 + i*width*(RevFlag[2] * (-2) + 1) + RevFlag[2] * (height - 1)*width, Graphic.cascadeBlock, TRUE);
							SetDrawMode(DX_DRAWMODE_BILINEAR);
							SetDrawBlendMode(DX_BLENDMODE_ADD, 192);
							DrawRotaGraph(202 + j * width + width / 2, 48 + i*width*(RevFlag[2] * (-2) + 1) + RevFlag[2] * (height - 1) * width + width / 2, 0.4, cnt * PI / 40.0, Graphic.effectRing[0], TRUE);
							SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
							if (width == 16)SetDrawMode(DX_DRAWMODE_NEAREST);
						}
					}
					else {
						DrawExtendGraph(202 + j * width, 48 + i*width*(RevFlag[2] * (-2) + 1) + RevFlag[2] * (height - 1)*width, 202 + j*width + width, 48 + i*width*(RevFlag[2] * (-2) + 1) + RevFlag[2] * (height - 1)*width + width, Graphic.Block[BlockColorTable[Save.ReadSystem(Save.BLOCK_FLAG)][MonoFlag[1] ? 7 : RCFlag[1] ? IrregularRand[1] : Tetrimino.Hold]], TRUE);
						if (CascadeNext > 4 && Course.Shape[Scenario[Progress.Level].ShapeFlag][Tetrimino.Hold][0][i + top][j] == 2){
							DrawExtendGraph(202 + j * width, 48 + i*width*(RevFlag[2] * (-2) + 1) + RevFlag[2] * (height - 1)*width, 202 + j*width + width, 48 + i*width*(RevFlag[2] * (-2) + 1) + RevFlag[2] * (height - 1)*width + width, Graphic.cascadeBlock, TRUE);
							SetDrawMode(DX_DRAWMODE_BILINEAR);
							SetDrawBlendMode(DX_BLENDMODE_ADD, 192);
							DrawRotaGraph(202 + j * width + width / 2, 48 + i*width*(RevFlag[2] * (-2) + 1) + RevFlag[2] * (height - 1) * width + width / 2, 0.4, cnt * PI / 40.0, Graphic.effectRing[0], TRUE);
							SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
							if (width == 16)SetDrawMode(DX_DRAWMODE_NEAREST);
						}
					}
				}
			}
		}
	}
	if (MainPauseFlag == FALSE)SetDrawBright(Scenario[Progress.Level].NextBright[0], Scenario[Progress.Level].NextBright[1], Scenario[Progress.Level].NextBright[2]);
	if ((!ObstacleFlag[OBS_SHUTTER] || !Scenario[Progress.Level].Shutter[1]) && !Scenario[Progress.Level].HideNext[0]){
		top = 3;
		for (int i = 0; i < 3; i++)for (int j = 0; j<4; j++)if (Course.Shape[Scenario[Progress.Level].ShapeFlag][Tetrimino.Next[0]][0][i][j]){ top = i; i = 3; j = 4; }
		bottom = 0;
		for (int i = 3; i>0; i--)for (int j = 0; j < 4; j++)if (Course.Shape[Scenario[Progress.Level].ShapeFlag][Tetrimino.Next[0]][0][i][j]){ bottom = i; i = 0; j = 4; }
		height = bottom - top + 1;
		if (height < 3)width = 16;
		else if (height == 3)width = 12;
		else width = 9;
		if (width == 16)SetDrawMode(DX_DRAWMODE_NEAREST);
		else SetDrawMode(DX_DRAWMODE_BILINEAR);
		for (int i = 0; i < height; i++){
			for (int j = 0; j < 4; j++){
				if (Course.Shape[Scenario[Progress.Level].ShapeFlag][Tetrimino.Next[0]][0][i + top][j]){
					if (width == 16){
						DrawGraph(288 + j*width, 48 + i*width*(RevFlag[2] * (-2) + 1) + RevFlag[2] * (height - 1)*width, Graphic.Block[BlockColorTable[Save.ReadSystem(Save.BLOCK_FLAG)][MonoFlag[2] ? 7 : RCFlag[2] ? IrregularRand[2] : Tetrimino.Next[0]]], TRUE);
						if (CascadeNext == 2 && Course.Shape[Scenario[Progress.Level].ShapeFlag][Tetrimino.Next[0]][0][i + top][j] == 2){
							DrawGraph(288 + j*width, 48 + i*width*(RevFlag[2] * (-2) + 1) + RevFlag[2] * (height - 1)*width, Graphic.cascadeBlock, TRUE);
							SetDrawMode(DX_DRAWMODE_BILINEAR);
							SetDrawBlendMode(DX_BLENDMODE_ADD, 192);
							DrawRotaGraph(288 + j * width + width / 2, 48 + i*width*(RevFlag[2] * (-2) + 1) + RevFlag[2] * (height - 1) * width + width / 2, cnt < 40 ? (0.4 * cnt / 40.0) : 0.4, cnt * PI / 40.0, Graphic.effectRing[0], TRUE);
							SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
							if (width == 16)SetDrawMode(DX_DRAWMODE_NEAREST);
						}
					}
					else {
						DrawExtendGraph(288 + j*width, 48 + i*width*(RevFlag[2] * (-2) + 1) + RevFlag[2] * (height - 1)*width, 288 + j*width + width, 48 + i*width*(RevFlag[2] * (-2) + 1) + RevFlag[2] * (height - 1)*width + width, Graphic.Block[BlockColorTable[Save.ReadSystem(Save.BLOCK_FLAG)][MonoFlag[2] ? 7 : RCFlag[2] ? IrregularRand[2] : Tetrimino.Next[0]]], TRUE);
						if (CascadeNext == 2 && Course.Shape[Scenario[Progress.Level].ShapeFlag][Tetrimino.Next[0]][0][i + top][j] == 2){
							DrawExtendGraph(288 + j*width, 48 + i*width*(RevFlag[2] * (-2) + 1) + RevFlag[2] * (height - 1)*width, 288 + j*width + width, 48 + i*width*(RevFlag[2] * (-2) + 1) + RevFlag[2] * (height - 1)*width + width, Graphic.cascadeBlock, TRUE);
							SetDrawMode(DX_DRAWMODE_BILINEAR);
							SetDrawBlendMode(DX_BLENDMODE_ADD, 192);
							DrawRotaGraph(288 + j * width + width / 2, 48 + i*width*(RevFlag[2] * (-2) + 1) + RevFlag[2] * (height - 1) * width + width / 2, cnt < 40 ? (0.4 * cnt / 40.0) : 0.4, cnt * PI / 40.0, Graphic.effectRing[0], TRUE);
							SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
							if (width == 16)SetDrawMode(DX_DRAWMODE_NEAREST);
						}
					}
				}
			}
		}
	}
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	if ((!ObstacleFlag[OBS_SHUTTER] || !Scenario[Progress.Level].Shutter[2]) && !Scenario[Progress.Level].HideNext[1]){
		top = 3;
		for (int i = 0; i < 3; i++)for (int j = 0; j<4; j++)if (Course.Shape[Scenario[Progress.Level].ShapeFlag][Tetrimino.Next[1]][0][i][j]){ top = i; i = 3; j = 4; }
		bottom = 0;
		for (int i = 3; i>0; i--)for (int j = 0; j < 4; j++)if (Course.Shape[Scenario[Progress.Level].ShapeFlag][Tetrimino.Next[1]][0][i][j]){ bottom = i; i = 0; j = 4; }
		height = bottom - top + 1;
		if (height < 4)width = 12;
		else width = 9;
		for (int i = 0; i < height; i++){
			for (int j = 0; j < 4; j++){
				if (Course.Shape[Scenario[Progress.Level].ShapeFlag][Tetrimino.Next[1]][0][i + top][j]){
					DrawExtendGraph(362 + j*width, 48 + i*width*(RevFlag[2] * (-2) + 1) + RevFlag[2] * (height - 1)*width, 362 + j*width + width, 48 + i*width*(RevFlag[2] * (-2) + 1) + RevFlag[2] * (height - 1)*width + width, Graphic.Block[BlockColorTable[Save.ReadSystem(Save.BLOCK_FLAG)][MonoFlag[3] ? 7 : RCFlag[3] ? IrregularRand[3] : Tetrimino.Next[1]]], TRUE);
					if (CascadeNext == 3 && Course.Shape[Scenario[Progress.Level].ShapeFlag][Tetrimino.Next[1]][0][i + top][j] == 2){
						DrawExtendGraph(362 + j*width, 48 + i*width*(RevFlag[2] * (-2) + 1) + RevFlag[2] * (height - 1)*width, 362 + j*width + width, 48 + i*width*(RevFlag[2] * (-2) + 1) + RevFlag[2] * (height - 1)*width + width, Graphic.cascadeBlock, TRUE);
						SetDrawMode(DX_DRAWMODE_BILINEAR);
						SetDrawBlendMode(DX_BLENDMODE_ADD, 192);
						DrawRotaGraph(362 + j * width + width / 2, 48 + i*width*(RevFlag[2] * (-2) + 1) + RevFlag[2] * (height - 1) * width + width / 2, cnt < 40 ? (0.3 * cnt / 40.0) : 0.3, cnt * PI / 40.0, Graphic.effectRing[0], TRUE);
						SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
						if (width == 16)SetDrawMode(DX_DRAWMODE_NEAREST);
					}
				}
			}
		}
	}
	if ((!ObstacleFlag[OBS_SHUTTER] || !Scenario[Progress.Level].Shutter[3]) && !Scenario[Progress.Level].HideNext[2]){
		top = 3;
		for (int i = 0; i < 3; i++)for (int j = 0; j<4; j++)if (Course.Shape[Scenario[Progress.Level].ShapeFlag][Tetrimino.Next[2]][0][i][j]){ top = i; i = 3; j = 4; }
		bottom = 0;
		for (int i = 3; i>0; i--)for (int j = 0; j < 4; j++)if (Course.Shape[Scenario[Progress.Level].ShapeFlag][Tetrimino.Next[2]][0][i][j]){ bottom = i; i = 0; j = 4; }
		height = bottom - top + 1;
		if (height < 4)width = 12;
		else width = 9;
		for (int i = 0; i < height; i++){
			for (int j = 0; j < 4; j++){
				if (Course.Shape[Scenario[Progress.Level].ShapeFlag][Tetrimino.Next[2]][0][i + top][j]){
					DrawExtendGraph(420 + j*width, 48 + i*width*(RevFlag[2] * (-2) + 1) + RevFlag[2] * (height - 1)*width, 420 + j*width + width, 48 + i*width*(RevFlag[2] * (-2) + 1) + RevFlag[2] * (height - 1)*width + width, Graphic.Block[BlockColorTable[Save.ReadSystem(Save.BLOCK_FLAG)][MonoFlag[4] ? 7 : RCFlag[4] ? IrregularRand[4] : Tetrimino.Next[2]]], TRUE);
					if (CascadeNext == 4 && Course.Shape[Scenario[Progress.Level].ShapeFlag][Tetrimino.Next[2]][0][i + top][j] == 2){
						DrawExtendGraph(420 + j*width, 48 + i*width*(RevFlag[2] * (-2) + 1) + RevFlag[2] * (height - 1)*width, 420 + j*width + width, 48 + i*width*(RevFlag[2] * (-2) + 1) + RevFlag[2] * (height - 1)*width + width, Graphic.cascadeBlock, TRUE);
						SetDrawMode(DX_DRAWMODE_BILINEAR);
						SetDrawBlendMode(DX_BLENDMODE_ADD, 192);
						DrawRotaGraph(420 + j * width + width / 2, 48 + i*width*(RevFlag[2] * (-2) + 1) + RevFlag[2] * (height - 1) * width + width / 2, cnt < 40 ? (0.3 * cnt / 40.0) : 0.3, cnt * PI / 40.0, Graphic.effectRing[0], TRUE);
						SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
						if (width == 16)SetDrawMode(DX_DRAWMODE_NEAREST);
					}
				}
			}
		}
	}
	if (MainPauseFlag == FALSE)SetDrawBright(255, 255, 255);
	SetDrawMode(DX_DRAWMODE_NEAREST);
}

void DrawGhost(int Distance){
	int x, y, density1, density2;
	SetDrawArea(FRAMEX, FRAMEY, FRAMEX + FRAMEWIDTH, FRAMEY + FRAMEHEIGHT);
	if (MainPauseFlag == FALSE)SetDrawBright(Scenario[Progress.Level].GhostBright[0], Scenario[Progress.Level].GhostBright[1], Scenario[Progress.Level].GhostBright[2]);
	if (ObstacleFlag[OBS_CLONE]){
		if (Scenario[Progress.Level].Clone[4] >= 0){ density1 = 255; density2 = MIN(Scenario[Progress.Level].Clone[4], 255); }
		else { density1 = 255 - MIN(abs(Scenario[Progress.Level].Clone[4]), 255); density2 = 0; }
	}
	for (x = Tetrimino.X - CloneTimes[0] * TetriminoSize; x <= Tetrimino.X + CloneTimes[1] * TetriminoSize; x += TetriminoSize){
		for (y = Tetrimino.Y - CloneTimes[2] * TetriminoSize; y <= Tetrimino.Y + CloneTimes[3] * TetriminoSize; y += TetriminoSize){
			if (x == Tetrimino.X&&y == Tetrimino.Y)SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			else if (Progress.TTime % 2 == 0)SetDrawBlendMode(DX_BLENDMODE_ALPHA, density1);
			else SetDrawBlendMode(DX_BLENDMODE_ALPHA, density2);
			for (int i = 0; i < 4; i++){
				for (int j = 0; j < 4; j++){
					if (Course.Shape[Scenario[Progress.Level].ShapeFlag][Tetrimino.Type][Tetrimino.Side][i][j] && y + Distance + i*TetriminoSize >= FIELD_Y){
						DrawExtendGraph(QuakeX + FRAMEX + (x + j*TetriminoSize - FIELD_X) * 16 / (HpFlag + 1) + 40 * HpFlag, QuakeY + FRAMEY + (y + i*TetriminoSize + Distance - FIELD_Y - (RevFlag[1] * 19 - RevFlag[1] * (TetriminoSize - 1)))*(RevFlag[1] * (-2) + 1) * 16 / (VpFlag + 1) + 80 * VpFlag, QuakeX + FRAMEX + (x + (j + 1)*TetriminoSize - FIELD_X) * 16 / (HpFlag + 1) + 40 * HpFlag, QuakeY + FRAMEY + (y + (i + (RevFlag[1] * (-2) + 1))*TetriminoSize + Distance - FIELD_Y - (RevFlag[1] * 19 - RevFlag[1] * (TetriminoSize - 1)))*(RevFlag[1] * (-2) + 1) * 16 / (VpFlag + 1) + 80 * VpFlag, Graphic.Block[BlockColorTable[Save.ReadSystem(Save.BLOCK_FLAG)][MonoFlag[5] ? 7 : RCFlag[5] ? IrregularRand[5] : Tetrimino.Type] + 8], TRUE);
					}
				}
			}
		}
	}
	if (MainPauseFlag == FALSE)SetDrawBright(255, 255, 255);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	SetDrawArea(0, 0, 640, 480);
}

void DrawField(){
	static int cnt = 0;
	int check = 0;
	SetDrawArea(FRAMEX, FRAMEY, FRAMEX + FRAMEWIDTH, FRAMEY + FRAMEHEIGHT);
	for (int i = FIELD_Y; i < FIELD_Y + 20; i++){
		for (int j = FIELD_X + AHPos[0]; j < FIELD_X + 10 - AHPos[1]; j++){
			if (Field[i][j] >= 1 && Field[i][j] <= 24){
				if (Scenario[Progress.Level].HideField[(Field[i][j] - 1) % 8] == 0){
					if (InvisibleBlock[i - FIELD_Y][j - FIELD_X] == 0){
						DrawExtendGraph(QuakeX + FRAMEX + (j - FIELD_X) * 16 / (HpFlag + 1) + 40 * HpFlag, QuakeY + FRAMEY + (i - FIELD_Y - RevFlag[1] * 19)*(RevFlag[1] * (-2) + 1) * 16 / (VpFlag + 1) + 80 * VpFlag, QuakeX + FRAMEX + (j - FIELD_X) * 16 / (HpFlag + 1) + 40 * HpFlag + 16 / (HpFlag + 1), QuakeY + FRAMEY + (i - FIELD_Y - RevFlag[1] * 19)*(RevFlag[1] * (-2) + 1) * 16 / (VpFlag + 1) + 80 * VpFlag + 16 / (VpFlag + 1), Graphic.Block[BlockColorTable[Save.ReadSystem(Save.BLOCK_FLAG)][MonoFlag[6] ? 7 : RCFlag[6] ? ((Field[i][j] - 1) % 8 + IrregularRand[6]) % 8 : (Field[i][j] - 1) % 8]], TRUE);
					}
				}
				if (Field[i][j] >= 9 && Field[i][j] <= 16){
					check = 1;
					DrawExtendGraph(QuakeX + FRAMEX + (j - FIELD_X) * 16 / (HpFlag + 1) + 40 * HpFlag, QuakeY + FRAMEY + (i - FIELD_Y - RevFlag[1] * 19)*(RevFlag[1] * (-2) + 1) * 16 / (VpFlag + 1) + 80 * VpFlag, QuakeX + FRAMEX + (j - FIELD_X) * 16 / (HpFlag + 1) + 40 * HpFlag + 16 / (HpFlag + 1), QuakeY + FRAMEY + (i - FIELD_Y - RevFlag[1] * 19)*(RevFlag[1] * (-2) + 1) * 16 / (VpFlag + 1) + 80 * VpFlag + 16 / (VpFlag + 1), Graphic.cascadeBlock, TRUE);
					SetDrawBlendMode(DX_BLENDMODE_ADD, 96);
					SetDrawMode(DX_DRAWMODE_BILINEAR);
					DrawRotaGraph(QuakeX + FRAMEX + (j - FIELD_X) * 16 / (HpFlag + 1) + 40 * HpFlag + 8, QuakeY + FRAMEY + (i - FIELD_Y - RevFlag[1] * 19)*(RevFlag[1] * (-2) + 1) * 16 / (VpFlag + 1) + 80 * VpFlag + 8, 0.4, cnt * PI / 40.0,Graphic.effectRing[0], TRUE);
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
					SetDrawMode(DX_DRAWMODE_NEAREST);
				}
				if (Field[i][j] >= 17 && Field[i][j] <= 24){
					check = 1;
					DrawExtendGraph(QuakeX + FRAMEX + (j - FIELD_X) * 16 / (HpFlag + 1) + 40 * HpFlag, QuakeY + FRAMEY + (i - FIELD_Y - RevFlag[1] * 19)*(RevFlag[1] * (-2) + 1) * 16 / (VpFlag + 1) + 80 * VpFlag, QuakeX + FRAMEX + (j - FIELD_X) * 16 / (HpFlag + 1) + 40 * HpFlag + 16 / (HpFlag + 1), QuakeY + FRAMEY + (i - FIELD_Y - RevFlag[1] * 19)*(RevFlag[1] * (-2) + 1) * 16 / (VpFlag + 1) + 80 * VpFlag + 16 / (VpFlag + 1), Graphic.levelupBlock, TRUE);
					SetDrawBlendMode(DX_BLENDMODE_ADD, 96);
					SetDrawMode(DX_DRAWMODE_BILINEAR);
					DrawRotaGraph(QuakeX + FRAMEX + (j - FIELD_X) * 16 / (HpFlag + 1) + 40 * HpFlag + 8, QuakeY + FRAMEY + (i - FIELD_Y - RevFlag[1] * 19)*(RevFlag[1] * (-2) + 1) * 16 / (VpFlag + 1) + 80 * VpFlag + 8, 0.4, cnt * PI / 40.0, Graphic.effectRing[1], TRUE);
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
					SetDrawMode(DX_DRAWMODE_NEAREST);
				}
			}
		}
	}
	for (int i = FIELD_Y; i < FIELD_Y + 20; i++){
		if (Field[i][FIELD_X] < 0)DrawExtendGraph(QuakeX + FRAMEX + 40 * HpFlag, QuakeY + FRAMEY + (i - FIELD_Y - RevFlag[1] * 19)*(RevFlag[1] * (-2) + 1) * 16 / (VpFlag + 1) + 80 * VpFlag, QuakeX + FRAMEX + 40 * HpFlag + 160 / (HpFlag + 1), QuakeY + FRAMEY + (i - FIELD_Y - RevFlag[1] * 19)*(RevFlag[1] * (-2) + 1) * 16 / (VpFlag + 1) + 80 * VpFlag + 16 / (VpFlag + 1), Graphic.Lift[RevFlag[1]], TRUE);
	}
	if (check == 0){
		cnt = 0;
	}
	else {
		cnt += 1;
	}
	SetDrawArea(0, 0, 640, 480);
}

void DrawTetrimino(){
	int x, y, density1, density2;
	static int cnt;
	if (CascadeNext == 0){
		cnt = 0;
	}
	else {
		cnt += 1;
	}
	SetDrawArea(FRAMEX, FRAMEY, FRAMEX + FRAMEWIDTH, FRAMEY + FRAMEHEIGHT);
	if (ObstacleFlag[OBS_CLONE]){
		if (Scenario[Progress.Level].Clone[4] >= 0){ density1 = 255; density2 = MIN(Scenario[Progress.Level].Clone[4], 255); }
		else { density1 = 255 - MIN(abs(Scenario[Progress.Level].Clone[4]), 255); density2 = 0; }
	}
	if (!Scenario[Progress.Level].HideTetrimino[Tetrimino.Type]){
		for (x = Tetrimino.X - CloneTimes[0] * TetriminoSize; x <= Tetrimino.X + CloneTimes[1] * TetriminoSize; x += TetriminoSize){
			for (y = Tetrimino.Y - CloneTimes[2] * TetriminoSize; y <= Tetrimino.Y + CloneTimes[3] * TetriminoSize; y += TetriminoSize){
				if (x == Tetrimino.X&&y == Tetrimino.Y)SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
				else if (Progress.TTime % 2 == 0)SetDrawBlendMode(DX_BLENDMODE_ALPHA, density1);
				else SetDrawBlendMode(DX_BLENDMODE_ALPHA, density2);
				for (int i = 0; i < 4; i++){
					for (int j = 0; j < 4; j++){
						if (Course.Shape[Scenario[Progress.Level].ShapeFlag][Tetrimino.Type][Tetrimino.Side][i][j] && y + i*TetriminoSize >= FIELD_Y){
							DrawExtendGraph(QuakeX + FRAMEX + (x - FIELD_X + j*TetriminoSize) * 16 / (HpFlag + 1) + 40 * HpFlag, QuakeY + FRAMEY + (y - FIELD_Y + i*TetriminoSize - (RevFlag[1] * 19 - RevFlag[1] * (TetriminoSize - 1)))*(RevFlag[1] * (-2) + 1) * 16 / (VpFlag + 1) + 80 * VpFlag, QuakeX + FRAMEX + (x - FIELD_X + (j + 1)*TetriminoSize) * 16 / (HpFlag + 1) + 40 * HpFlag, QuakeY + FRAMEY + (y - FIELD_Y + (i + (RevFlag[1] * (-2) + 1))*TetriminoSize - (RevFlag[1] * 19 - RevFlag[1] * (TetriminoSize - 1)))*(RevFlag[1] * (-2) + 1) * 16 / (VpFlag + 1) + 80 * VpFlag, Graphic.Block[BlockColorTable[Save.ReadSystem(Save.BLOCK_FLAG)][MonoFlag[0] ? 7 : RCFlag[0] ? IrregularRand[0] : Tetrimino.Type]], TRUE);
							if (CascadeNext == 1 && Course.Shape[Scenario[Progress.Level].ShapeFlag][Tetrimino.Type][Tetrimino.Side][i][j] == 2){
								DrawExtendGraph(QuakeX + FRAMEX + (x - FIELD_X + j*TetriminoSize) * 16 / (HpFlag + 1) + 40 * HpFlag, QuakeY + FRAMEY + (y - FIELD_Y + i*TetriminoSize - (RevFlag[1] * 19 - RevFlag[1] * (TetriminoSize - 1)))*(RevFlag[1] * (-2) + 1) * 16 / (VpFlag + 1) + 80 * VpFlag, QuakeX + FRAMEX + (x - FIELD_X + (j + 1)*TetriminoSize) * 16 / (HpFlag + 1) + 40 * HpFlag, QuakeY + FRAMEY + (y - FIELD_Y + (i + (RevFlag[1] * (-2) + 1))*TetriminoSize - (RevFlag[1] * 19 - RevFlag[1] * (TetriminoSize - 1)))*(RevFlag[1] * (-2) + 1) * 16 / (VpFlag + 1) + 80 * VpFlag, Graphic.cascadeBlock, TRUE);
								SetDrawMode(DX_DRAWMODE_BILINEAR);
								SetDrawBlendMode(DX_BLENDMODE_ADD, 192);
								DrawRotaGraph(QuakeX + FRAMEX + (x - FIELD_X + j*TetriminoSize) * 16 / (HpFlag + 1) + 40 * HpFlag + 8 * TetriminoSize, QuakeY + FRAMEY + (y - FIELD_Y + i*TetriminoSize - (RevFlag[1] * 19 - RevFlag[1] * (TetriminoSize - 1)))*(RevFlag[1] * (-2) + 1) * 16 / (VpFlag + 1) + 80 * VpFlag + 8 * TetriminoSize, 0.4, cnt * PI / 40.0, Graphic.effectRing[0], TRUE);
								SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
								if (TetriminoSize == 1)SetDrawMode(DX_DRAWMODE_NEAREST);
							}
						}
					}
				}
			}
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	SetDrawArea(0, 0, 640, 480);
}

void DrawSurface(){
	int SurfaceColor = GetColor(Scenario[Progress.Level].SurfaceColor[0], Scenario[Progress.Level].SurfaceColor[1], Scenario[Progress.Level].SurfaceColor[2]);
	SetUse3DFlag(FALSE);
	SetDrawArea(FRAMEX, FRAMEY, FRAMEX + FRAMEWIDTH, FRAMEY + FRAMEHEIGHT);
	for (int i = FIELD_Y; i < FIELD_Y + 20; i++){
		for (int j = FIELD_X + AHPos[0]; j<FIELD_X + 10 - AHPos[1]; j++){
			if (Field[i][j] == 0){
				int px[2], py[2];
				px[0] = QuakeX + FRAMEX + (j - FIELD_X) * 16 / (HpFlag + 1) + 40 * HpFlag;
				py[0] = QuakeY + FRAMEY + (i - FIELD_Y - RevFlag[1] * 19)*(RevFlag[1] * (-2) + 1) * 16 / (VpFlag + 1) + 80 * VpFlag;
				px[1] = px[0] + 16 / (HpFlag + 1) - 1;
				py[1] = py[0] + 16 / (VpFlag + 1) - 1;
				if (Field[i - 1][j]>0 && InvisibleBlock[i - 1 - FIELD_Y][j - FIELD_X] == 0){
					DrawLine(px[0], RevFlag[1] ? py[1] : py[0], px[1] + 1, RevFlag[1] ? py[1] : py[0], SurfaceColor, Scenario[Progress.Level].SurfaceThickness[0]);
				}
				if (Field[i + 1][j] > 0 && InvisibleBlock[i + 1 - FIELD_Y][j - FIELD_X] == 0){
					DrawLine(px[0], RevFlag[1] ? py[0] : py[1], px[1] + 1, RevFlag[1] ? py[0] : py[1], SurfaceColor, Scenario[Progress.Level].SurfaceThickness[1]);
				}
				if (Field[i][j - 1] > 0 && InvisibleBlock[i - FIELD_Y][j - 1 - FIELD_X] == 0){
					DrawLine(px[0], py[0], px[0], py[1] + 1, SurfaceColor, Scenario[Progress.Level].SurfaceThickness[2]);
				}
				if (Field[i][j + 1] > 0 && InvisibleBlock[i - FIELD_Y][j + 1 - FIELD_X] == 0){
					DrawLine(px[1], py[0], px[1], py[1] + 1, SurfaceColor, Scenario[Progress.Level].SurfaceThickness[3]);
				}
			}
		}
	}
	SetDrawArea(0, 0, 640, 480);
	SetUse3DFlag(TRUE);
}

void DrawFlash(){
	int FlashColor=GetColor(Scenario[Progress.Level].FlashColor[0],Scenario[Progress.Level].FlashColor[1],Scenario[Progress.Level].FlashColor[2]);
	SetDrawArea(FRAMEX,FRAMEY,FRAMEX+FRAMEWIDTH,FRAMEY+FRAMEHEIGHT);
	for(int i=0;i<FLASH_MAX;i++){
		if(Flash[i].FlashRemain>0){
			if(Flash[i].FlashRemain>Scenario[Progress.Level].FlashTime)Flash[i].FlashRemain=Scenario[Progress.Level].FlashTime;
			if(i<Scenario[Progress.Level].FlashDrawMax){
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,Scenario[Progress.Level].FlashIntensity*Flash[i].FlashRemain/Scenario[Progress.Level].FlashTime);
				DrawBox(QuakeX+FRAMEX+Flash[i].X*16/(HpFlag+1)+40*HpFlag,QuakeY+FRAMEY+(Flash[i].Y-RevFlag[1]*19)*(RevFlag[1]*(-2)+1)*16/(VpFlag+1)+80*VpFlag,QuakeX+FRAMEX+Flash[i].X*16/(HpFlag+1)+40*HpFlag+16/(HpFlag+1),QuakeY+FRAMEY+(Flash[i].Y-RevFlag[1]*19)*(RevFlag[1]*(-2)+1)*16/(VpFlag+1)+80*VpFlag+16/(VpFlag+1),FlashColor,Scenario[Progress.Level].FlashFill);
				Flash[i].FlashRemain--;
			}
			else Flash[i].FlashRemain=0;
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
	SetDrawArea(0,0,640,480);
}

void DrawSnow(){
	int row=0,column=0;
	int SnowColor=GetColor(Scenario[Progress.Level].SnowColor[0],Scenario[Progress.Level].SnowColor[1],Scenario[Progress.Level].SnowColor[2]);
	SetDrawArea(FRAMEX,FRAMEY,FRAMEX+FRAMEWIDTH,FRAMEY+FRAMEHEIGHT);
	if(Scenario[Progress.Level].Snow[4]!=0)row=Progress.TTime/Scenario[Progress.Level].Snow[4];
	row+=(Scenario[Progress.Level].Snow[6]+Scenario[Progress.Level].Snow[8]);
	if(Scenario[Progress.Level].Snow[8]!=0)row%=Scenario[Progress.Level].Snow[8];
	if(Scenario[Progress.Level].Snow[12]!=0&&(row>=Scenario[Progress.Level].Snow[12]||row<0)){
		row=(row+Scenario[Progress.Level].Snow[12])%Scenario[Progress.Level].Snow[12];
		if(row<0)column-=Scenario[Progress.Level].Snow[15];
		else column+=Scenario[Progress.Level].Snow[15];
	}
	if(Scenario[Progress.Level].Snow[5]!=0)column=Progress.TTime/Scenario[Progress.Level].Snow[5];
	column+=(Scenario[Progress.Level].Snow[7]+Scenario[Progress.Level].Snow[9]);
	if(Scenario[Progress.Level].Snow[9]!=0)column%=Scenario[Progress.Level].Snow[9];
	if(Scenario[Progress.Level].Snow[13]!=0&&(column>=Scenario[Progress.Level].Snow[13]||column<0)){
		column=(column+Scenario[Progress.Level].Snow[13])%Scenario[Progress.Level].Snow[13];
		if(column<0)row-=Scenario[Progress.Level].Snow[14];
		else row+=Scenario[Progress.Level].Snow[14];
	}
	for(int i=0;i<Scenario[Progress.Level].Snow[3];i++){
		if(i>=Scenario[Progress.Level].Snow[2]){
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
			DrawBox(QuakeX+FRAMEX+column*Scenario[Progress.Level].Snow[0],QuakeY+FRAMEY+row*Scenario[Progress.Level].Snow[0],QuakeX+FRAMEX+(column+1)*Scenario[Progress.Level].Snow[0],QuakeY+FRAMEY+(row+1)*Scenario[Progress.Level].Snow[0],SnowColor,TRUE);
			for(int j=1;j<=Scenario[Progress.Level].Snow[1];j++){
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,255-(255/(Scenario[Progress.Level].Snow[1]+1))*j);
				DrawBox(QuakeX+FRAMEX+column*Scenario[Progress.Level].Snow[0]-j,QuakeY+FRAMEY+row*Scenario[Progress.Level].Snow[0]-j,QuakeX+FRAMEX+(column+1)*Scenario[Progress.Level].Snow[0]+j,QuakeY+FRAMEY+(row+1)*Scenario[Progress.Level].Snow[0]+j,SnowColor,FALSE);
			}
		}
		row+=Scenario[Progress.Level].Snow[10];
		if(Scenario[Progress.Level].Snow[12]!=0&&(row>=Scenario[Progress.Level].Snow[12]||row<0)){
			row=(row+Scenario[Progress.Level].Snow[12])%Scenario[Progress.Level].Snow[12];
			if(row<0)column-=Scenario[Progress.Level].Snow[15];
			else column+=Scenario[Progress.Level].Snow[15];
		}
		column+=Scenario[Progress.Level].Snow[11];
		if(Scenario[Progress.Level].Snow[13]!=0&&(column>=Scenario[Progress.Level].Snow[13]||column<0)){
			column=(column+Scenario[Progress.Level].Snow[13])%Scenario[Progress.Level].Snow[13];
			if(column<0)row-=Scenario[Progress.Level].Snow[14];
			else row+=Scenario[Progress.Level].Snow[14];
		}

	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
	SetDrawArea(0,0,640,480);
}

void DrawBoost(int Height){
	SetDrawArea(FRAMEX,FRAMEY,FRAMEX+FRAMEWIDTH,FRAMEY+FRAMEHEIGHT);
	SetDrawBlendMode(DX_BLENDMODE_ADD,Progress.TTime%3*80+80);
	DrawGraph(QuakeX+FRAMEX,QuakeY+Height*16+95,Graphic.SpeedChange,TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
	SetDrawArea(0,0,640,480);
}

void DrawFlipFlop(){
	SetDrawArea(FRAMEX,FRAMEY,FRAMEX+FRAMEWIDTH,FRAMEY+FRAMEHEIGHT);
	SetDrawBlendMode(DX_BLENDMODE_ADD,(Progress.TTime%30-16)*(Progress.TTime%30-16)*(-1)+199);
	if(AlternateHideState==0){
		if(Scenario[Progress.Level].AlternateHide[1]>0){
			DrawGraph(QuakeX+FRAMEX,QuakeY+FRAMEY,Graphic.FlipFlop[0],TRUE);
			DrawGraph(QuakeX+FRAMEX+Scenario[Progress.Level].AlternateHide[1]*16-40,QuakeY+FRAMEY,Graphic.FlipFlop[1],TRUE);
		}
	}
	else {
		if(Scenario[Progress.Level].AlternateHide[2]>0){
			DrawGraph(QuakeX+360,QuakeY+FRAMEY,Graphic.FlipFlop[3],TRUE);
			DrawGraph(QuakeX+400-Scenario[Progress.Level].AlternateHide[2]*16,QuakeY+FRAMEY,Graphic.FlipFlop[2],TRUE);
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
	SetDrawArea(0,0,640,480);
}

void DrawBlackOut(){
	int tempScreen;
	int X_Base = QuakeX + 40 * HpFlag + Scenario[Progress.Level].BlackOut[0];
	int Y_Base = QuakeY + 80 * VpFlag + (Scenario[Progress.Level].BlackOut[1] * (RevFlag[1] * (-2) + 1));
	int NowBlack_X = X_Base + (Tetrimino.X - FIELD_X) * 16 / (HpFlag + 1) + (Course.ShapeBlackOut[Scenario[Progress.Level].ShapeFlag][0][Tetrimino.Type] * TetriminoSize / (HpFlag + 1));
	int NowBlack_Y = Y_Base + (Tetrimino.Y - FIELD_Y - (RevFlag[1] * 19 - RevFlag[1] * (TetriminoSize - 1)))*(RevFlag[1] * (-2) + 1) * 16 / (VpFlag + 1) + ((Course.ShapeBlackOut[Scenario[Progress.Level].ShapeFlag][1][Tetrimino.Type] * TetriminoSize / (VpFlag + 1))*(RevFlag[1] * (-2) + 1));
	int PastBlack_X = X_Base + (JustBeforeX - FIELD_X) * 16 / (HpFlag + 1) + (Course.ShapeBlackOut[Scenario[Progress.Level].ShapeFlag][0][JustBeforeType] * TetriminoSize / (HpFlag + 1));
	int PastBlack_Y = Y_Base + (JustBeforeY - FIELD_Y - (RevFlag[1] * 19 - RevFlag[1] * (TetriminoSize - 1)))*(RevFlag[1] * (-2) + 1) * 16 / (VpFlag + 1) + ((Course.ShapeBlackOut[Scenario[Progress.Level].ShapeFlag][1][JustBeforeType] * TetriminoSize / (VpFlag + 1))*(RevFlag[1] * (-2) + 1));
	int bright1 = Scenario[Progress.Level].BlackOut[4], bright2 = Scenario[Progress.Level].BlackOut[5];
	tempScreen = MakeScreen(160, 320, FALSE);
	SetDrawScreen(tempScreen);
	SetDrawArea(0, 0, 160, 320);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	if (MainFlag % 100 == 11){
		DrawOval(NowBlack_X, NowBlack_Y, Scenario[Progress.Level].BlackOut[2], Scenario[Progress.Level].BlackOut[3], GetColor(bright1, bright1, bright1), TRUE);
	}
	else {
		if (bright1 > bright2){
			DrawOval(PastBlack_X, PastBlack_Y, Scenario[Progress.Level].BlackOut[2], Scenario[Progress.Level].BlackOut[3], GetColor(bright2, bright2, bright2), TRUE);
			DrawOval(NowBlack_X, NowBlack_Y, Scenario[Progress.Level].BlackOut[2], Scenario[Progress.Level].BlackOut[3], GetColor(bright1, bright1, bright1), TRUE);
		}
		else {
			DrawOval(NowBlack_X, NowBlack_Y, Scenario[Progress.Level].BlackOut[2], Scenario[Progress.Level].BlackOut[3], GetColor(bright1, bright1, bright1), TRUE);
			DrawOval(PastBlack_X, PastBlack_Y, Scenario[Progress.Level].BlackOut[2], Scenario[Progress.Level].BlackOut[3], GetColor(bright2, bright2, bright2), TRUE);
		}
	}
	SetDrawScreen(DX_SCREEN_BACK);
	SetDrawArea(FRAMEX, FRAMEY, FRAMEX + FRAMEWIDTH, FRAMEY + FRAMEHEIGHT);
	SetDrawBlendMode(DX_BLENDMODE_MUL, 255);
	DrawGraph(FRAMEX, FRAMEY, tempScreen, FALSE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DeleteGraph(tempScreen);
	if (Scenario[Progress.Level].BlackOut[6]){
		DrawOval(FRAMEX + NowBlack_X, FRAMEY + NowBlack_Y, Scenario[Progress.Level].BlackOut[2], Scenario[Progress.Level].BlackOut[3], Color.White, FALSE);
	}
	if (Scenario[Progress.Level].BlackOut[7]){
		if (MainFlag % 100 != 11){
			DrawOval(FRAMEX + PastBlack_X, FRAMEY + PastBlack_Y, Scenario[Progress.Level].BlackOut[2], Scenario[Progress.Level].BlackOut[3], Color.White, FALSE);
		}
	}
	SetDrawArea(0, 0, 640, 480);
}

void DrawWarning(){
	if(WarnTime){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,(WarnTime%150-75)*(WarnTime%150-75)/35*(-1)+160);
		DrawStringToHandle(Course.WarningPos,FRAMEY+24,"！Warning！",Color.Red,Font.Warning);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
	}
}

void DrawNowLevel(){
	if(LevelDisplayTimeRemain>0&&LevelDisplayTimeRemain%10<5){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,160);
		DrawFormatStringToHandle(Course.NowLevelPos,FRAMEY+24,Color.Yellow,Font.Warning,"LEVEL%3d",Progress.Level+1);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
	}
	LevelDisplayTimeRemain--;
}

void DrawExplosion(){
	int basex,basey,width,height;
	if(MainPauseFlag==FALSE)SetDrawBright(Scenario[Progress.Level].ExplosionBright[0],Scenario[Progress.Level].ExplosionBright[1],Scenario[Progress.Level].ExplosionBright[2]);
	for(int i=0;i<20;i++){
		for(int j=0;j<10;j++){
			if(Explode[i][j].ClearRemain>0&&!Scenario[Progress.Level].HideExplosion){
				if(Explode[i][j].ClearRemain<=10){
					basex=QuakeX+FRAMEX+(HpFlag*40)+j*(16/(HpFlag+1))-16/(HpFlag+1);
					basey=QuakeY+FRAMEY+(VpFlag*80)+(i-RevFlag[1]*19)*(RevFlag[1]*(-2)+1)*(16/(VpFlag+1))-16/(VpFlag+1);
					width=48/(HpFlag+1);
					height=48/(VpFlag+1);
					DrawExtendGraph(basex,basey,basex+width,basey+height,Graphic.Explosion[(10-Explode[i][j].ClearRemain)*8+BlockColorTable[Save.ReadSystem(Save.BLOCK_FLAG)][(MonoFlag[6]?7:RCFlag[6]?(Explode[i][j].ClearColor+IrregularRand[6])%8:Explode[i][j].ClearColor)]],TRUE);
				}
				else {
					basex=QuakeX+FRAMEX+(HpFlag*40)+j*(16/(HpFlag+1));
					basey=QuakeY+FRAMEY+(VpFlag*80)+(i-RevFlag[1]*19)*(RevFlag[1]*(-2)+1)*(16/(VpFlag+1));
					width=16/(HpFlag+1);
					height=16/(VpFlag+1);
					DrawExtendGraph(basex,basey,basex+width,basey+height,Graphic.Block[BlockColorTable[Save.ReadSystem(Save.BLOCK_FLAG)][(MonoFlag[6]?7:RCFlag[6]?(Explode[i][j].ClearColor+IrregularRand[6])%8:Explode[i][j].ClearColor)]],TRUE);
				}
			}
			Explode[i][j].ClearRemain--;
		}
	}
	if(MainPauseFlag==FALSE)SetDrawBright(255,255,255);
}

void DrawCascadeArrow(){
	int line = cascadeArrowBase;
	SetDrawMode(DX_DRAWMODE_BILINEAR);

	if (ObstacleFlag[OBS_ZEROG] != 0 && Scenario[Progress.Level].ZeroGravity[1] == 0 && TempCascade == 0){
		if (PastClearLines < Scenario[Progress.Level].ZeroGravity[0]){
			return;
		}
	}
	if (ObstacleFlag[OBS_ZEROG] != 0 && Scenario[Progress.Level].ZeroGravity[1] != 0 && TempCascade == 0){
		if (PastClearLines < Scenario[Progress.Level].ZeroGravity[0] && CascadingFlag == 0){
			return;
		}
	}
	int pcl = PastClearLines;
	if (pcl > 4){
		pcl = 4;
	}
	int base = ClearLineBase + Scenario[Progress.Level].Cascade[pcl - 1] - FIELD_Y;
	if (base >= 0){
		for (int j = 0; j < 10; j += 1){
			int flag = 0;
			int iMem = -1;
			for (int i = 0; i < 21; i += 1){
				if (flag == 0 && Field[FIELD_Y + i][FIELD_X + j] != 0){
					if (iMem >= 0){
						int check = 0;
						for (int k = 0; k < 8 && ClearRow[k] >= 0; k += 1){
							if (i - 1 == ClearRow[k] - FIELD_Y){
								check = 1;
								k = 8;
							}
						}
						if (check == 1){
							for (int k = 0; k < 8 && ClearRow[k] >= 0; k += 1){
								if (iMem == ClearRow[k] - FIELD_Y){
									check = 2;
									k = 8;
								}
							}
						}
						if (check < 2){
							int x1 = QuakeX + FRAMEX + j * 16 / (HpFlag + 1) + 40 * HpFlag;
							int y1 = QuakeY + FRAMEY + (iMem - RevFlag[1] * 20) * (RevFlag[1] * (-2) + 1) * 16 / (VpFlag + 1) + 80 * VpFlag;
							int x2 = QuakeX + FRAMEX + j * 16 / (HpFlag + 1) + 40 * HpFlag + 16 / (HpFlag + 1);
							int y2 = QuakeY + FRAMEY + (i - 1 - RevFlag[1] * 20) * (RevFlag[1] * (-2) + 1) * 16 / (VpFlag + 1) + 80 * VpFlag + 16 / (VpFlag + 1) * (RevFlag[1] * (-2) + 1);
							DrawExtendGraph(x1, y1, x2, y2, Graphic.cascadeArrow, TRUE);
						}
					}
					flag = 1;
					if (i >= base){
						i = 20;
					}
				}
				else if (flag == 1 && Field[FIELD_Y + i][FIELD_X + j] == 0){
					iMem = i;
					flag = 0;
				}
			}
		}
	}
	SetDrawMode(DX_DRAWMODE_BILINEAR);
}

void DrawText(){
	for(int i=0;i<6;i++)DrawStringToHandle(420,157+i*18,Course.Text[i],Color.White,Font.Board);
}

void DrawError(){
	for(int i=0;i<2;i++){
		for(int j=0;j<20;j++){
			if(Course.ErrorRow[i*20+j])DrawFormatStringToHandle(FRAMEX+i*80,FRAMEY+j*16,Color.White,Font.Board,"%d",Course.ErrorRow[i*20+j]);
			else return;
		}
	}
}

void DrawStatus(){
	DrawStringToHandle(10,217,"SPEED ROAD",Color.White,Font.Board);
	DrawFormatStringToHandle(10,235,Color.White,Font.Board,"　最高到達レベル　%3d",Status.RoadMaxLevel[0]+1);
	DrawFormatStringToHandle(10,253,Color.White,Font.Board,"　　　　ポイント　%3d",Status.RoadMaxPoint[0]);
	DrawStringToHandle(10,289,"CHAOS ROAD",Color.White,Font.Board);
	DrawFormatStringToHandle(10,307,Color.White,Font.Board,"　最高到達レベル　%3d",Status.RoadMaxLevel[1]+1);
	DrawFormatStringToHandle(10,325,Color.White,Font.Board,"　　　　ポイント　%3d",Status.RoadMaxPoint[1]);
	DrawStringToHandle(10,361,"GRADE TEST",Color.White,Font.Board);
	if(Status.MaxClearGrade<0)DrawStringToHandle(25,379,"無級",Color.White,Font.Board);
	else DrawStringToHandle(25,379,GradeName[Status.MaxClearGrade],Color.White,Font.Board);
	if(Status.MaxClearGrade>=0)DrawFormatStringToHandle(91,379,Color.White,Font.Board,"%9d 点",Status.GradeHS);
	DrawFormatStringToHandle(10,397,Color.White,Font.Board,"　合計%13d 点",Status.GradeHSSum);
}

void DrawObstacle(){
	int row = 0, num = 0, ObsSum = 0;
	int itv = 18;
	int fontTemp = Font.Board;
	int fontTemp2 = Font.Board;
	int boardType = Save.ReadSystem(Save.BOARD);
	if (boardType == 0){
		return;
	}
	else if (boardType == 1){
		itv = 27;
		fontTemp = Font.BigBoard;
		fontTemp2 = Font.MiddleBoard;
	}
	SetDrawArea(0, 0, 214, 480);
	for (int i = 0; i < OBSTACLE_MAX; i++)if (Scenario[Progress.Level].ObstacleFlag[i] && !Scenario[Progress.Level].HideObstacle[i] && !Course.NaturalObstacle[i])ObsSum++;
	for (int i = 0; i<OBSTACLE_MAX; i++){
		if (Scenario[Progress.Level].ObstacleFlag[i] && !Scenario[Progress.Level].HideObstacle[i] && !Course.NaturalObstacle[i]){
			row++;
			num++;
			if (row >= 11 && ObsSum>11){
				DrawFormatStringToHandle(10, row * itv + 231, Color.White, Font.Board, "その他%d種類の妨害", ObsSum - (num - 1));
				i = OBSTACLE_MAX;
			}
			else {
				int branch;
				switch (i){
				case OBS_CFIELD:
					if (Scenario[Progress.Level].ClearField[0] <= 0 && Scenario[Progress.Level].ClearField[1] >= 19 && Scenario[Progress.Level].ClearField[2] <= 0 && Scenario[Progress.Level].ClearField[3] >= 9)DrawStringToHandle(10, row * itv + 231, "地形消去", Color.White, fontTemp);
					else DrawStringToHandle(10, row * itv + 231, "部分的地形消去", Color.White, fontTemp);
					break;
				case OBS_LEVELUP:
					DrawFormatStringToHandle(10, row * itv + 231, Color.White, fontTemp, "レベル進行 %+d", Scenario[Progress.Level].LevelUp[0]);
					for (int j = 0; j < 5; j++){
						if (Scenario[Progress.Level].LevelUpCondition[j * 3] >= 0 && Scenario[Progress.Level].LevelUpCondition[j * 3 + 1] >= 0){
							row++;
							if (Scenario[Progress.Level].LevelUpCondition[j * 3] >= 3 && Scenario[Progress.Level].LevelUpCondition[j * 3] <= 7){
								int time = Scenario[Progress.Level].LevelUpCondition[j * 3 + 2];
								if (time >= 0 && time < 360000)DrawFormatStringToHandle(10, row * itv + 231, Color.White, fontTemp2, "　%s%s%02d:%02d:%02d", BoardDrawName[Scenario[Progress.Level].LevelUpCondition[j * 3]], SignDrawName[Scenario[Progress.Level].LevelUpCondition[j * 3 + 1]], time / 3600, time % 3600 / 60, time % 60 * 10 / 6);
								else if (time < 0)DrawFormatStringToHandle(10, row * itv + 231, Color.White, fontTemp2, "　%s%s%02d:%02d:%02d", BoardDrawName[Scenario[Progress.Level].LevelUpCondition[j * 3]], SignDrawName[Scenario[Progress.Level].LevelUpCondition[j * 3 + 1]], 0, 0, 0);
								else DrawFormatStringToHandle(10, row * itv + 231, Color.White, fontTemp2, "　%s%s%02d:%02d:%02d", BoardDrawName[Scenario[Progress.Level].LevelUpCondition[j * 3]], SignDrawName[Scenario[Progress.Level].LevelUpCondition[j * 3 + 1]], 99, 59, 99);
							}
							else if (Scenario[Progress.Level].LevelUpCondition[j * 3] == 30){
								DrawFormatStringToHandle(10, row * itv + 231, Color.White, fontTemp2, "　%s%s%s", BoardDrawName[Scenario[Progress.Level].LevelUpCondition[j * 3]], SignDrawName[Scenario[Progress.Level].LevelUpCondition[j * 3 + 1]], Course.RankName[MIN(Scenario[Progress.Level].LevelUpCondition[j * 3 + 2], Course.RankMax)]);
							}
							else if (Scenario[Progress.Level].LevelUpCondition[j * 3] == 31){
								DrawFormatStringToHandle(10, row * itv + 231, Color.White, fontTemp2, "　%s%s%dppm", BoardDrawName[Scenario[Progress.Level].LevelUpCondition[j * 3]], SignDrawName[Scenario[Progress.Level].LevelUpCondition[j * 3 + 1]], Scenario[Progress.Level].LevelUpCondition[j * 3 + 2]);
							}
							else DrawFormatStringToHandle(10, row * itv + 231, Color.White, fontTemp2, "　%s%s%d", BoardDrawName[Scenario[Progress.Level].LevelUpCondition[j * 3]], SignDrawName[Scenario[Progress.Level].LevelUpCondition[j * 3 + 1]], Scenario[Progress.Level].LevelUpCondition[j * 3 + 2]);
						}
					}
					break;
				case OBS_EXORCISE:
					branch = (Scenario[Progress.Level].Exorcise[0] && 1) * 2 + (Scenario[Progress.Level].Exorcise[1] && 1) * 1;
					switch (branch){
					case 0:DrawStringToHandle(10, row * itv + 231, "不除霊", Color.White, fontTemp); break;
					case 1:DrawStringToHandle(10, row * itv + 231, "除霊 着地霊のみ", Color.White, fontTemp); break;
					case 2:DrawStringToHandle(10, row * itv + 231, "除霊 出現霊のみ", Color.White, fontTemp); break;
					case 3:DrawStringToHandle(10, row * itv + 231, "除霊", Color.White, fontTemp); break;
					}
					break;
				case OBS_CFB:
					if (Scenario[Progress.Level].ClearForBig[0] <= 0 && Scenario[Progress.Level].ClearForBig[1] >= 19 && Scenario[Progress.Level].ClearForBig[2] <= 0 && Scenario[Progress.Level].ClearForBig[3] >= 9)DrawStringToHandle(10, row * itv + 231, "地形四倍角化", Color.White, fontTemp);
					else DrawStringToHandle(10, row * itv + 231, "部分的地形四倍角化", Color.White, fontTemp);
					break;
				case OBS_BIG:DrawStringToHandle(10, row * itv + 231, "ビッグ", Color.White, fontTemp); break;
				case OBS_NH:
					if (Scenario[Progress.Level].NoHold[0]<0)DrawStringToHandle(10, row * itv + 231, "ホールド使用不可", Color.White, fontTemp);
					else if (Scenario[Progress.Level].NoHold[0] == 0)DrawStringToHandle(10, row * itv + 231, "ホールド無制限", Color.White, fontTemp);
					else if (Scenario[Progress.Level].NoHold[0] == 1)DrawStringToHandle(10, row * itv + 231, "ホールド通常", Color.White, fontTemp);
					else DrawFormatStringToHandle(10, row * itv + 231, Color.White, fontTemp, "ホールド制限 %dミノ", Scenario[Progress.Level].NoHold[0]);
					break;
				case OBS_BOOST:
					if (Scenario[Progress.Level].Boost[3] >= 0){
						if (Scenario[Progress.Level].Boost[2]>1 || (Scenario[Progress.Level].Boost[2]<0 && Scenario[Progress.Level].Denominator>1))DrawFormatStringToHandle(10, row * itv + 231, Color.White, fontTemp, "第%d段 %d/%dG LDT%dF", 20 - Scenario[Progress.Level].Boost[0], Scenario[Progress.Level].Boost[1], Scenario[Progress.Level].Boost[2], Scenario[Progress.Level].Boost[3]);
						else DrawFormatStringToHandle(10, row * itv + 231, Color.White, fontTemp, "第%d段 %dG LDT%dF", 20 - Scenario[Progress.Level].Boost[0], Scenario[Progress.Level].Boost[1], Scenario[Progress.Level].Boost[3]);
					}
					else {
						if (Scenario[Progress.Level].Boost[2] > 1 || (Scenario[Progress.Level].Boost[2]<0 && Scenario[Progress.Level].Denominator>1))DrawFormatStringToHandle(10, row * itv + 231, Color.White, fontTemp, "第%d段から %d/%dG", 20 - Scenario[Progress.Level].Boost[0], Scenario[Progress.Level].Boost[1], Scenario[Progress.Level].Boost[2]);
						else DrawFormatStringToHandle(10, row * itv + 231, Color.White, fontTemp, "第%d段から %dG", 20 - Scenario[Progress.Level].Boost[0], Scenario[Progress.Level].Boost[1]);
					}
					break;
				case OBS_COPY:
					if (Scenario[Progress.Level].CopyGarbage[0] == 0)DrawFormatStringToHandle(10, row * itv + 231, Color.White, fontTemp, "複写隆起 %d段/%dF", Scenario[Progress.Level].CopyGarbage[2], Scenario[Progress.Level].CopyGarbage[1]);
					else if (Scenario[Progress.Level].CopyGarbage[0] == 1)DrawFormatStringToHandle(10, row * itv + 231, Color.White, fontTemp, "複写隆起 %d段/%dQ", Scenario[Progress.Level].CopyGarbage[2], Scenario[Progress.Level].CopyGarbage[1]);
					break;
				case OBS_RANDOM:
					if (Scenario[Progress.Level].RandomGarbage[0] == 0)DrawFormatStringToHandle(10, row * itv + 231, Color.White, fontTemp, "乱雑隆起 %d段/%dF", Scenario[Progress.Level].RandomGarbage[2], Scenario[Progress.Level].RandomGarbage[1]);
					else if (Scenario[Progress.Level].RandomGarbage[0] == 1)DrawFormatStringToHandle(10, row * itv + 231, Color.White, fontTemp, "乱雑隆起 %d段/%dQ", Scenario[Progress.Level].RandomGarbage[2], Scenario[Progress.Level].RandomGarbage[1]);
					break;
				case OBS_SHUTTER:
					branch = (Scenario[Progress.Level].Shutter[0] && 1) * 8 + (Scenario[Progress.Level].Shutter[1] && 1) * 4 + (Scenario[Progress.Level].Shutter[2] && 1) * 2 + (Scenario[Progress.Level].Shutter[3] && 1) * 1;
					switch (branch){
					case  0:DrawStringToHandle(10, row * itv + 231, "ノンシャッター", Color.White, fontTemp); break;
					case  1:DrawStringToHandle(10, row * itv + 231, "シャッター 3", Color.White, fontTemp); break;
					case  2:DrawStringToHandle(10, row * itv + 231, "シャッター 2", Color.White, fontTemp); break;
					case  3:DrawStringToHandle(10, row * itv + 231, "シャッター 2 3", Color.White, fontTemp); break;
					case  4:DrawStringToHandle(10, row * itv + 231, "シャッター 1", Color.White, fontTemp); break;
					case  5:DrawStringToHandle(10, row * itv + 231, "シャッター 1 3", Color.White, fontTemp); break;
					case  6:DrawStringToHandle(10, row * itv + 231, "シャッター 1 2", Color.White, fontTemp); break;
					case  7:DrawStringToHandle(10, row * itv + 231, "シャッター 1 2 3", Color.White, fontTemp); break;
					case  8:DrawStringToHandle(10, row * itv + 231, "シャッター H", Color.White, fontTemp); break;
					case  9:DrawStringToHandle(10, row * itv + 231, "シャッター H 3", Color.White, fontTemp); break;
					case 10:DrawStringToHandle(10, row * itv + 231, "シャッター H 2", Color.White, fontTemp); break;
					case 11:DrawStringToHandle(10, row * itv + 231, "シャッター H 2 3", Color.White, fontTemp); break;
					case 12:DrawStringToHandle(10, row * itv + 231, "シャッター H 1", Color.White, fontTemp); break;
					case 13:DrawStringToHandle(10, row * itv + 231, "シャッター H 1 3", Color.White, fontTemp); break;
					case 14:DrawStringToHandle(10, row * itv + 231, "シャッター H 1 2", Color.White, fontTemp); break;
					case 15:DrawStringToHandle(10, row * itv + 231, "シャッター H 1 2 3", Color.White, fontTemp); break;
					}
					break;
				case OBS_SHADOW:DrawFormatStringToHandle(10, row * itv + 231, Color.White, fontTemp, "雲隠 固定後%dF", Scenario[Progress.Level].Shadow[0]); break;
				case OBS_SUDDEN:DrawFormatStringToHandle(10, row * itv + 231, Color.White, fontTemp, "露顕 固定後%dF", Scenario[Progress.Level].SuddenAppear[0]); break;
				case OBS_RC:DrawStringToHandle(10, row * itv + 231, "変色ブロック", Color.White, fontTemp); break;
				case OBS_MONO:DrawStringToHandle(10, row * itv + 231, "褪色ブロック", Color.White, fontTemp); break;
				case OBS_REVERSE:DrawStringToHandle(10, row * itv + 231, "天地倒立", Color.White, fontTemp); break;
				case OBS_DARK:DrawStringToHandle(10, row * itv + 231, "暗闇", Color.White, fontTemp); break;
				case OBS_ALTHIDE:DrawStringToHandle(10, row * itv + 231, "交互透明", Color.White, fontTemp); break;
				case OBS_SNOW:DrawStringToHandle(10, row * itv + 231, "紙吹雪", Color.White, fontTemp); break;
				case OBS_LIFT:DrawFormatStringToHandle(10, row * itv + 231, Color.White, fontTemp, "リフト %d秒で%d段", Scenario[Progress.Level].Lift[0] / 60, Scenario[Progress.Level].Lift[1]); break;
				case OBS_PRESS:
					branch = (Scenario[Progress.Level].Press[0] && 1) * 2 + (Scenario[Progress.Level].Press[1] && 1) * 1;
					switch (branch){
					case 0:DrawStringToHandle(10, row * itv + 231, "無圧縮", Color.White, fontTemp); break;
					case 1:DrawStringToHandle(10, row * itv + 231, "左右圧縮", Color.White, fontTemp); break;
					case 2:DrawStringToHandle(10, row * itv + 231, "上下圧縮", Color.White, fontTemp); break;
					case 3:DrawStringToHandle(10, row * itv + 231, "四方圧縮", Color.White, fontTemp); break;
					}
					break;
				case OBS_QUAKE:DrawStringToHandle(10, row * itv + 231, "地震", Color.White, fontTemp); break;
				case OBS_BLACKOUT:DrawStringToHandle(10, row * itv + 231, "停電", Color.White, fontTemp); break;
				case OBS_ZEROG:
					if (Scenario[Progress.Level].ZeroGravity[0]<2)DrawStringToHandle(10, row * itv + 231, "平重力", Color.White, fontTemp);
					else if (Scenario[Progress.Level].ZeroGravity[0] == 2)DrawStringToHandle(10, row * itv + 231, "無重力 要2ライン以上", Color.White, fontTemp);
					else if (Scenario[Progress.Level].ZeroGravity[0] == 3)DrawStringToHandle(10, row * itv + 231, "無重力 要3ライン以上", Color.White, fontTemp);
					else if (Scenario[Progress.Level].ZeroGravity[0] == 4)DrawStringToHandle(10, row * itv + 231, "無重力 要4ライン", Color.White, fontTemp);
					else if (Scenario[Progress.Level].ZeroGravity[0]>4)DrawStringToHandle(10, row * itv + 231, "完全無重力", Color.White, fontTemp);
					break;
				case OBS_CLONE:
					branch = (Scenario[Progress.Level].Clone[0] > 0) * 8 + (Scenario[Progress.Level].Clone[1] > 0) * 4 + (Scenario[Progress.Level].Clone[2] > 0) * 2 + (Scenario[Progress.Level].Clone[3] > 0) * 1;
					switch (branch){
					case  1:DrawFormatStringToHandle(10, row * itv + 231, Color.White, fontTemp, "影身 %d→", Scenario[Progress.Level].Clone[3]); break;
					case  2:DrawFormatStringToHandle(10, row * itv + 231, Color.White, fontTemp, "影身 %d←", Scenario[Progress.Level].Clone[2]); break;
					case  3:DrawFormatStringToHandle(10, row * itv + 231, Color.White, fontTemp, "影身 %d← %d→", Scenario[Progress.Level].Clone[2], Scenario[Progress.Level].Clone[3]); break;
					case  4:DrawFormatStringToHandle(10, row * itv + 231, Color.White, fontTemp, "影身 %d↓", Scenario[Progress.Level].Clone[1]); break;
					case  5:DrawFormatStringToHandle(10, row * itv + 231, Color.White, fontTemp, "影身 %d↓ %d→", Scenario[Progress.Level].Clone[1], Scenario[Progress.Level].Clone[3]); break;
					case  6:DrawFormatStringToHandle(10, row * itv + 231, Color.White, fontTemp, "影身 %d↓ %d←", Scenario[Progress.Level].Clone[1], Scenario[Progress.Level].Clone[2]); break;
					case  7:DrawFormatStringToHandle(10, row * itv + 231, Color.White, fontTemp, "影身 %d↓ %d← %d→", Scenario[Progress.Level].Clone[1], Scenario[Progress.Level].Clone[2], Scenario[Progress.Level].Clone[3]); break;
					case  8:DrawFormatStringToHandle(10, row * itv + 231, Color.White, fontTemp, "影身 %d↑", Scenario[Progress.Level].Clone[0]); break;
					case  9:DrawFormatStringToHandle(10, row * itv + 231, Color.White, fontTemp, "影身 %d↑ %d→", Scenario[Progress.Level].Clone[0], Scenario[Progress.Level].Clone[3]); break;
					case 10:DrawFormatStringToHandle(10, row * itv + 231, Color.White, fontTemp, "影身 %d↑ %d←", Scenario[Progress.Level].Clone[0], Scenario[Progress.Level].Clone[2]); break;
					case 11:DrawFormatStringToHandle(10, row * itv + 231, Color.White, fontTemp, "影身 %d↑ %d← %d→", Scenario[Progress.Level].Clone[0], Scenario[Progress.Level].Clone[2], Scenario[Progress.Level].Clone[3]); break;
					case 12:DrawFormatStringToHandle(10, row * itv + 231, Color.White, fontTemp, "影身 %d↑ %d↓", Scenario[Progress.Level].Clone[0], Scenario[Progress.Level].Clone[1]); break;
					case 13:DrawFormatStringToHandle(10, row * itv + 231, Color.White, fontTemp, "影身 %d↑ %d↓ %d→", Scenario[Progress.Level].Clone[0], Scenario[Progress.Level].Clone[1], Scenario[Progress.Level].Clone[3]); break;
					case 14:DrawFormatStringToHandle(10, row * itv + 231, Color.White, fontTemp, "影身 %d↑ %d↓ %d←", Scenario[Progress.Level].Clone[0], Scenario[Progress.Level].Clone[1], Scenario[Progress.Level].Clone[2]); break;
					case 15:DrawFormatStringToHandle(10, row * itv + 231, Color.White, fontTemp, "影身 %d↑ %d↓ %d← %d→", Scenario[Progress.Level].Clone[0], Scenario[Progress.Level].Clone[1], Scenario[Progress.Level].Clone[2], Scenario[Progress.Level].Clone[3]); break;
					}
					break;
				case OBS_CASCADE:
					DrawStringToHandle(10, row * itv + 231, "フルタイムカスケード", Color.White, fontTemp);
					break;
				case OBS_DROPEFFECT:
					branch = Scenario[Progress.Level].DropEffect[0];
					if (branch < 0){
						branch = -1;
					}
					else if (branch > 8){
						branch = 0;
					}
					switch (branch){
					case  0:DrawStringToHandle(10, row * itv + 231, "視覚効果無し", Color.White, fontTemp); break;
					case  1:DrawStringToHandle(10, row * itv + 231, "視覚効果 水滴", Color.White, fontTemp); break;
					case  2:DrawStringToHandle(10, row * itv + 231, "視覚効果 桜花", Color.White, fontTemp); break;
					case  3:DrawStringToHandle(10, row * itv + 231, "視覚効果 雪結晶", Color.White, fontTemp); break;
					case  4:DrawStringToHandle(10, row * itv + 231, "視覚効果 紅葉", Color.White, fontTemp); break;
					case  5:DrawStringToHandle(10, row * itv + 231, "視覚効果 果実", Color.White, fontTemp); break;
					case  6:DrawStringToHandle(10, row * itv + 231, "視覚効果 胡蝶", Color.White, fontTemp); break;
					case  7:DrawStringToHandle(10, row * itv + 231, "視覚効果 深海魚", Color.White, fontTemp); break;
					case  8:DrawStringToHandle(10, row * itv + 231, "視覚効果 飛鳥", Color.White, fontTemp); break;
					case -1:DrawStringToHandle(10, row * itv + 231, "視覚効果 混沌", Color.White, fontTemp); break;
					}
					break;
				default:
					break;
				}
			}
		}
	}
	SetDrawArea(0, 0, 640, 480);
}

void DrawPause(){
	if(MainPauseFlag>1&&MainPauseFlag<5){
	for(int k=0;k<3;k++)DrawGraph(FRAMEX,144+k*32,Graphic.Select[0],TRUE);
		DrawGraph(FRAMEX,(MainPauseFlag)*32+80,Graphic.Select[1],TRUE);
		DrawStringToHandle(256,153,"ゲーム再開",Color.White,Font.Board);
		DrawStringToHandle(256,185,"最初からやり直し",Color.White,Font.Board);
		DrawStringToHandle(256,217,"メニューに戻る",Color.White,Font.Board);
	}
	if(MainPauseFlag>59&&MainPauseFlag<120)DrawStringToHandle(FRAMEX,100,"3.",Color.White,Font.Count);
	if(MainPauseFlag>119&&MainPauseFlag<180)DrawStringToHandle(FRAMEX,100,"3.2.",Color.White,Font.Count);
	if(MainPauseFlag>179)DrawStringToHandle(FRAMEX,100,"3.2.1.",Color.White,Font.Count);
}

void DrawMenu(){
	for(int i=0;i<7;i++)DrawGraph(FRAMEX,112+i*32,Graphic.Select[0],TRUE);
	if(Progress.Mode==3&&MainFlag>=20){
		DrawGraph(FRAMEX,3*32+112,Graphic.Select[1],TRUE);
		for(int i=0;i<7;i++){
			if(i==3){
				if(MainFlag%100==30)SetDrawArea(0,0,352,480);
				else SetDrawArea(0,0,388,480);
				DrawFormatStringToHandle(256,121+i*32,Color.White,Font.Board,"%s",Course.IndexTitle);
			}
			else {
				SetDrawArea(0,0,388,480);
				char crs_Path[256]={0};
				int target=i+Progress.OtherCourse-3;
				if(target<0){
					target+=FileList.HowManyFiles();
				}
				if(target>=FileList.HowManyFiles()){
					target-=FileList.HowManyFiles();
				}
				FileList.FilePath(target,crs_Path);
				DrawFormatStringToHandle(256,121+i*32,Color.White,Font.Board,"%s",&crs_Path[4]);
				
			}
		}
		SetDrawArea(0,0,640,480);
	}
	else {
		DrawGraph(FRAMEX,Progress.Mode*32+112,Graphic.Select[1],TRUE);
		DrawStringToHandle(256,121,"SPEED ROAD",Color.White,Font.Board);
		DrawStringToHandle(256,153,"CHAOS ROAD",Color.White,Font.Board);
		DrawStringToHandle(256,185,"GRADE TEST",Color.White,Font.Board);		
		DrawStringToHandle(256,217,"OTHER COURSE",Color.White,Font.Board);
		DrawStringToHandle(256,249,"CONFIGURATION",Color.White,Font.Board);
		DrawStringToHandle(256,281,"CAREER",Color.White,Font.Board);
		DrawStringToHandle(256,313,"EXIT",Color.White,Font.Board);
	}
}

void DrawStageBoardSimple(){
	int tt = Scenario[Progress.Level].TargetTime - Progress.LTime;
	int th = Scenario[Progress.Level].ObstacleTime - Progress.LTime;
	int x1 = 10;
	int x2 = 420;
	int x3 = 420;
	int y1 = 49;
	int y2 = 217;
	int y3 = 381;
	int xr2 = 620;
	int itv = 27;
	int ch = 11;
	int xr1 = 202;
	int fontTemp = Font.BigBoard;
	SetDrawArea(0, 0, 186, 480);
	DrawFormatStringToHandle(x1, y1 + itv * 0, Color.White, fontTemp, "%s", Course.TitleText[0]);
	DrawFormatStringToHandle(x1, y1 + itv * 1, Color.White, fontTemp, "%s", Course.TitleText[2]);
	SetDrawArea(0, 0, 640, 480);
	if (Course.HighestScore){
		DrawStringToHandle(x2, y1 + itv * 3, "最高得点", Color.White, fontTemp);
		DrawFormatStringToHandle(xr2 - ch * 9, y1 + itv * 3, Color.White, fontTemp, "%9d", Save.ReadCourse(Save.BEST_SCORE));
	}
	else if (Course.SpeedRun){
		int ft = Save.ReadCourse(Save.BEST_TIME);
		if (ft < 0){
			ft = 0;
		}
		else if (ft > 359999){
			ft = 359999;
		}
		DrawStringToHandle(x2, y1 + itv * 3, "最速時間", Color.White, Font.BigBoard);
		DrawFormatStringToHandle(xr2 - ch * 8, y1 + itv * 3, NewRecord.Time ? Color.Yellow : Color.White, Font.BigBoard, "%02d:%02d:%02d", ft / 3600, ft % 3600 / 60, (ft == 359999) ? 99 : ft % 60 * 10 / 6);
	}
	if (!Scenario[Progress.Level].HideText[0]){
		DrawStringToHandle(x1, y1 + itv * 2, "レベル", Color.White, fontTemp);
		DrawFormatStringToHandle(xr1 - ch * 3, y1 + itv * 2, NewRecord.Level ? Color.Yellow : Color.White, fontTemp, "%3d", Progress.Level + 1);
	}
	if (!Scenario[Progress.Level].HideText[1]){
		DrawStringToHandle(x1, y1 + itv * 3, "ポイント", Color.White, fontTemp);
		if (Scenario[Progress.Level].PointMax >= 0){
			DrawFormatStringToHandle(xr1 - ch * 10, y1 + itv * 3, NewRecord.Point ? Color.Yellow : Color.White, fontTemp, "%4d /%4d", Progress.DisplayPoint, Scenario[Progress.Level].PointMax);
		}
		else {
			DrawFormatStringToHandle(xr1 - ch * 10, y1 + itv * 3, NewRecord.Point ? Color.Yellow : Color.White, fontTemp, "%4d /  ∞", Progress.DisplayPoint);
		}
	}
	if (!Scenario[Progress.Level].HideText[2]){
		DrawStringToHandle(x1, y1 + itv * 4, "目標まで", Color.White, fontTemp);
	}
	if (tt < 0){
		tt = 0;
	}
	else if (tt > 359999){
		tt = 359999;
	}
	DrawFormatStringToHandle(xr1 - ch * 8, y1 + itv * 4, tt >= 600 ? Color.White : tt > 0 ? Color.Yellow : Color.Red, fontTemp, "%02d:%02d:%02d", tt / 3600, tt % 3600 / 60, (tt == 359999) ? 99 : tt % 60 * 10 / 6);
	if (!Scenario[Progress.Level].HideText[4]){
		for (int i = 0; i<OBSTACLE_MAX; i++){
			if (Scenario[Progress.Level].ObstacleFlag[i] && !Scenario[Progress.Level].HideObstacle[i] && !Course.NaturalObstacle[i]){
				DrawStringToHandle(x1, y2, "妨害まで", Color.White, fontTemp);
				if (th < 0){
					th = 0;
				}
				else if (th > 359999){
					th = 359999;
				}
				DrawFormatStringToHandle(xr1 - ch * 8, y2, th >= 600 ? Color.White : th > 0 ? Color.Yellow : Color.Red, fontTemp, "%02d:%02d:%02d", th / 3600, th % 3600 / 60, (th == 359999) ? 99 : th % 60 * 10 / 6);
				i = OBSTACLE_MAX;
			}
		}
	}
	if (!Scenario[Progress.Level].HideText[6]){
		if (Scenario[Progress.Level].Denominator > 1)DrawFormatStringToHandle(x3, y3 + itv * 0, Color.White, fontTemp, "%2d /%3d Ｇ", Scenario[Progress.Level].Numerator, Scenario[Progress.Level].Denominator);
		else DrawFormatStringToHandle(x3, y3 + itv * 0, Color.White, fontTemp, "%2d Ｇ", Scenario[Progress.Level].Numerator);
		DrawStringToHandle(x3, y3 + itv * 1, "固定時間", Color.White, fontTemp);
		DrawStringToHandle(x3, y3 + itv * 2, "出現猶予", Color.White, fontTemp);
		DrawFormatStringToHandle(xr2 - ch * 8, y3 + itv * 1, Color.White, fontTemp, "%5d Ｆ", Scenario[Progress.Level].LDT);
		DrawFormatStringToHandle(xr2 - ch * 8, y3 + itv * 2, Color.White, fontTemp, "%5d Ｆ", Scenario[Progress.Level].ARE);
	}
	if (!Scenario[Progress.Level].HideText[5])DrawObstacle();
}

void DrawStageBoardDetail(){
	int tt = Scenario[Progress.Level].TargetTime;
	int th = Scenario[Progress.Level].ObstacleTime;
	int x1 = 10;
	int x2 = 420;
	int x3 = 420;
	int y1 = 49;
	int y2 = 217;
	int y3 = 381;
	int itv = 18;
	int fontTemp = Font.Board;
	SetDrawArea(0, 0, 186, 480);
	DrawFormatStringToHandle(x1, y1 + itv * 0, Color.White, fontTemp, "%s", Course.TitleText[0]);
	DrawFormatStringToHandle(x1, y1 + itv * 1, Color.White, fontTemp, "%s", Course.TitleText[2]);
	SetDrawArea(0, 0, 640, 480);
	if (Course.HighestScore){
		DrawFormatStringToHandle(x2, y1 + itv * 4, Color.White, fontTemp, "最高得点　　　　%9d", Save.ReadCourse(Save.BEST_SCORE));
	}
	else if(Course.SpeedRun){
		int ft = Save.ReadCourse(Save.BEST_TIME);
		if (ft < 0){
			ft = 0;
		}
		else if (ft > 359999){
			ft = 359999;
		}
		DrawFormatStringToHandle(x2, y1 + itv * 4, Color.White, fontTemp, "最速時間　　　　 %02d:%02d:%02d", ft / 3600, ft % 3600 / 60, (ft == 359999) ? 99 : ft % 60 * 10 / 6);
	}
	if (!Scenario[Progress.Level].HideText[0]){
		DrawStringToHandle(x1, y1 + itv * 2, "レベル", Color.White, fontTemp);
		DrawFormatStringToHandle(x1, y1 + itv * 2, NewRecord.Level ? Color.Yellow : Color.White, fontTemp, "　　　　　 %9d", Progress.Level + 1);
	}
	if (!Scenario[Progress.Level].HideText[1]){
		DrawStringToHandle(x1, y1 + itv * 3, "ポイント", Color.White, fontTemp);
		if (Scenario[Progress.Level].PointMax >= 0){
			DrawFormatStringToHandle(76, y1 + itv * 3, NewRecord.Point ? Color.Yellow : Color.White, fontTemp, "%6d /%6d", Progress.DisplayPoint, Scenario[Progress.Level].PointMax);
		}
		else {
			DrawFormatStringToHandle(76, y1 + itv * 3, NewRecord.Point ? Color.Yellow : Color.White, fontTemp, "%6d / 　　∞", Progress.DisplayPoint);
		}
	}
	if (!Scenario[Progress.Level].HideText[2]){
		DrawStringToHandle(x1, y1 + itv * 4, "目標時点", Color.White, fontTemp);
	}
	if (tt >= 0 && tt<360000)DrawFormatStringToHandle(x1, y1 + itv * 4, Scenario[Progress.Level].TargetTime>Progress.LTime + 600 ? Color.White : Scenario[Progress.Level].TargetTime>Progress.LTime ? Color.Yellow : Color.Red, fontTemp, "　　　　　　　　%02d:%02d:%02d", tt / 3600, tt % 3600 / 60, tt % 60 * 10 / 6);
	else if (tt<0)DrawFormatStringToHandle(x1, y1 + itv * 4, Scenario[Progress.Level].TargetTime>Progress.LTime + 600 ? Color.White : Scenario[Progress.Level].TargetTime>Progress.LTime ? Color.Yellow : Color.Red, fontTemp, "　　　　　　　　%02d:%02d:%02d", 0, 0, 0);
	else DrawFormatStringToHandle(x1, y1 + itv * 4, Scenario[Progress.Level].TargetTime>Progress.LTime + 600 ? Color.White : Scenario[Progress.Level].TargetTime>Progress.LTime ? Color.Yellow : Color.Red, fontTemp, "　　　　　　　　%02d:%02d:%02d", 99, 59, 99);
	if (!Scenario[Progress.Level].HideText[4]){
		for (int i = 0; i<OBSTACLE_MAX; i++){
			if (Scenario[Progress.Level].ObstacleFlag[i] && !Scenario[Progress.Level].HideObstacle[i] && !Course.NaturalObstacle[i]){
				DrawStringToHandle(x1, y2, "妨害開始時点", Color.White, fontTemp);
				if (th >= 0 && th<360000)DrawFormatStringToHandle(x1, y2, Scenario[Progress.Level].ObstacleTime>Progress.LTime + 600 ? Color.White : th>Progress.LTime ? Color.Yellow : Color.Red, fontTemp, "　　　　　　　　%02d:%02d:%02d", th / 3600, th % 3600 / 60, th % 60 * 10 / 6);
				else if (th<0)DrawFormatStringToHandle(x1, y2, Scenario[Progress.Level].ObstacleTime>Progress.LTime + 600 ? Color.White : th>Progress.LTime ? Color.Yellow : Color.Red, fontTemp, "　　　　　　　　%02d:%02d:%02d", 0, 0, 0);
				else DrawFormatStringToHandle(x1, y2, Scenario[Progress.Level].ObstacleTime>Progress.LTime + 600 ? Color.White : th>Progress.LTime ? Color.Yellow : Color.Red, fontTemp, "　　　　　　　　%02d:%02d:%02d", 99, 59, 99);
				i = OBSTACLE_MAX;
			}
		}
	}
	if (!Scenario[Progress.Level].HideText[6]){
		if (Scenario[Progress.Level].Denominator>1)DrawFormatStringToHandle(x3, y3 + itv * 0, Color.White, fontTemp, "%2d /%4d Ｇ", Scenario[Progress.Level].Numerator, Scenario[Progress.Level].Denominator);
		else DrawFormatStringToHandle(x3, y3 + itv * 0, Color.White, fontTemp, "%2d Ｇ", Scenario[Progress.Level].Numerator);
		DrawFormatStringToHandle(x3, y3 + itv * 1, Color.White, fontTemp, "固定時間　　　　%7d Ｆ", Scenario[Progress.Level].LDT);
		DrawFormatStringToHandle(x3, y3 + itv * 2, Color.White, fontTemp, "ライン消去時間　%7d Ｆ", Scenario[Progress.Level].LCT);
		DrawFormatStringToHandle(x3, y3 + itv * 3, Color.White, fontTemp, "出現猶予　　　　%7d Ｆ", Scenario[Progress.Level].ARE);
		DrawFormatStringToHandle(x3, y3 + itv * 4, Color.White, fontTemp, "自動移動開始猶予%7d Ｆ", Scenario[Progress.Level].DAS);
	}
	if (!Scenario[Progress.Level].HideText[5])DrawObstacle();
}

void DrawStageBoard(){
	int boardType = Save.ReadSystem(Save.BOARD);
	if (MainFlag / 10 == 21){
		if (Progress.DisplayPoint < Progress.Point - 10000)Progress.DisplayPoint += 1113;
		else if (Progress.DisplayPoint < Progress.Point - 1000)Progress.DisplayPoint += 113;
		else if (Progress.DisplayPoint < Progress.Point - 100)Progress.DisplayPoint += 13;
		else if (Progress.DisplayPoint < Progress.Point - 10)Progress.DisplayPoint += 3;
		else if (Progress.DisplayPoint < Progress.Point)Progress.DisplayPoint += 1;
		else if (Progress.DisplayPoint >= Progress.Point + MAX(Scenario[Progress.Level].PointMax / 60, 1))Progress.DisplayPoint -= MAX(Scenario[Progress.Level].PointMax / 60, 1);
		else Progress.DisplayPoint = Progress.Point;
	}
	else {
		Progress.DisplayPoint = Progress.Point;
	}
	if (boardType == 1){
		DrawStageBoardSimple();
	}
	else if (boardType == 2){
		DrawStageBoardDetail();
	}
}

void DrawPlayBoardSimple(){
	int x2 = 420;
	int xr2 = 620;
	int y2 = 49;
	int ch = 11;
	int itv = 27;
	int tt = Progress.TTime;
	int fontTemp = Font.BigBoard;
	int keikaPos = 2;
	if (tt < 0){
		tt = 0;
	}
	else if (tt > 359999){
		tt = 359999;
	}
	if (Course.HighestScore){
		DrawStringToHandle(x2, y2 + itv * 2, "得点", Color.White, fontTemp);
		DrawFormatStringToHandle(xr2 - ch * 9, y2 + itv * 2, NewRecord.Score ? Color.Yellow : Color.White, fontTemp, "%9d", Scores.DisplayScore);
		keikaPos = 7;
	}
	
	DrawStringToHandle(x2, y2 + itv * keikaPos, "経過時間", Color.White, fontTemp);
	DrawFormatStringToHandle(xr2 - ch * 8, y2 + itv * keikaPos, Color.White, fontTemp, "%02d:%02d:%02d", tt / 3600, tt % 3600 / 60, tt % 60 * 10 / 6);
	DrawStringToHandle(x2, y2 + itv * 5, "テトリミノ", Color.White, fontTemp);
	DrawStringToHandle(x2, y2 + itv * 6, "ライン", Color.White, fontTemp);
	
	
	DrawFormatStringToHandle(xr2 - ch * 6, y2 + itv * 5, Color.White, fontTemp, "%6d", Scores.TTetriminos);
	DrawFormatStringToHandle(xr2 - ch * 6, y2 + itv * 6, Color.White, fontTemp, "%6d", Scores.TLines);

	

	
}

void DrawPlayBoardDetail(){
	int x1 = 10;
	int x2 = 420;
	int y1 = 49;
	int y2 = 49;
	int itv = 18;
	int fontTemp = Font.Board;
	if (!Scenario[Progress.Level].HideText[3]){
		if (Scores.Leftover >= 0 && Scores.Leftover<360000)DrawFormatStringToHandle(x1, y1 + itv * 5, Color.White, fontTemp, "余剰時間量　　　%02d:%02d:%02d", Scores.Leftover / 3600, Scores.Leftover % 3600 / 60, Scores.Leftover % 60 * 10 / 6);
		else if (Scores.Leftover<0)DrawFormatStringToHandle(x1, y1 + itv * 5, Color.White, fontTemp, "余剰時間量　　　%02d:%02d:%02d", 0, 0, 0);
		else DrawFormatStringToHandle(x1, y1 + itv * 5, Color.White, fontTemp, "余剰時間量　　　%02d:%02d:%02d", 99, 59, 99);
	}
	if (Progress.LTime >= 0 && Progress.LTime<360000)DrawFormatStringToHandle(x1, y1 + itv * 6, Color.White, fontTemp, "今節経過時間　　%02d:%02d:%02d", Progress.LTime / 3600, Progress.LTime % 3600 / 60, Progress.LTime % 60 * 10 / 6);
	else if (Progress.LTime<0)DrawFormatStringToHandle(x1, y1 + itv * 6, Color.White, fontTemp, "今節経過時間　　%02d:%02d:%02d", 0, 0, 0);
	else DrawFormatStringToHandle(x1, y1 + itv * 6, Color.White, fontTemp, "今節経過時間　　%02d:%02d:%02d", 99, 59, 99);
	if (Progress.TTime >= 0 && Progress.TTime<360000)DrawFormatStringToHandle(x1, y1 + itv * 7, Color.White, fontTemp, "合計経過時間　　%02d:%02d:%02d", Progress.TTime / 3600, Progress.TTime % 3600 / 60, Progress.TTime % 60 * 10 / 6);
	else if (Progress.TTime<0)DrawFormatStringToHandle(x1, y1 + itv * 7, Color.White, fontTemp, "合計経過時間　　%02d:%02d:%02d", 0, 0, 0);
	else DrawFormatStringToHandle(x1, y1 + itv * 7, Color.White, fontTemp, "合計経過時間　　%02d:%02d:%02d", 99, 59, 99);
	DrawStringToHandle(x2, y2 + itv * 3, "得点", Color.White, fontTemp);
	DrawFormatStringToHandle(x2, y2 + itv * 3, NewRecord.Score ? Color.Yellow : Color.White, fontTemp, "　　　　　　　　%9d", Scores.DisplayScore);
	DrawFormatStringToHandle(x2, y2 + itv * 5, Color.White, fontTemp, "テトリミノ%6d /%6d", Scores.LTetriminos, Scores.TTetriminos);
	DrawFormatStringToHandle(x2, y2 + itv * 6, Color.White, fontTemp, "ライン　　%6d /%6d", Scores.LLines, Scores.TLines);
	DrawFormatStringToHandle(x2, y2 + itv * 7, Color.White, fontTemp, "ﾃﾄﾘﾐﾉ/分%4d  ﾗｲﾝ/分%3d", Scores.Tmin, Scores.Lmin);
	DrawFormatStringToHandle(x2, y2 + itv * 8, Color.White, fontTemp, "テトリス　%6d /%6d", Scores.LTetris, Scores.TTetris);
	DrawFormatStringToHandle(x2, y2 + itv * 9, Color.White, fontTemp, "Ｂ２Ｂ　　%6d /%6d", Scores.LBacktoBack, Scores.TBacktoBack);
	DrawFormatStringToHandle(x2, y2 + itv * 10, Color.White, fontTemp, "Ｔスピン　%6d /%6d", Scores.LTSpin, Scores.TTSpin);
	DrawFormatStringToHandle(x2, y2 + itv * 11, Color.White, fontTemp, "ＲＥＮ　　%6d /%6d", Scores.LRens, Scores.TRens);
}

void DrawPlayBoard(){
	static int cnt = 0;
	static int dispCasc = 0;
	int colorFlag = 0;
	int boardType = Save.ReadSystem(Save.BOARD);
	int fontTemp = Font.Board;
	int yOffs = 0;
	if (Progress.TTime == 0){
		dispCasc = 0;
	}
	if(MainFlag/10==21){
		if(Scores.DisplayScore<Scores.Score-100000)Scores.DisplayScore+=11137;
		else if(Scores.DisplayScore<Scores.Score-10000)Scores.DisplayScore+=1137;
		else if(Scores.DisplayScore<Scores.Score-1000)Scores.DisplayScore+=137;
		else if(Scores.DisplayScore<Scores.Score-100)Scores.DisplayScore+=37;
		else if(Scores.DisplayScore<Scores.Score-10)Scores.DisplayScore+=7;
		else if(Scores.DisplayScore<Scores.Score)Scores.DisplayScore+=1;
		if(Scores.DisplayScore>Scores.Score)Scores.DisplayScore=Scores.Score;
	}
	else Scores.DisplayScore=Scores.Score;

	if (boardType == 1){
		DrawPlayBoardSimple();
		fontTemp = Font.BigBoard;
		yOffs = -2;
	}
	if (boardType == 2){
		DrawPlayBoardDetail();
	}

	if(RemainLDT>0&&Scenario[Progress.Level].LDT>0&&!Scenario[Progress.Level].HideGage[0]){
		SetDrawArea(317,426,317+RemainLDT*83/Scenario[Progress.Level].LDT,432);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
		DrawGraph(317,426,Graphic.LDTARE_Color[RemainLDT>=Scenario[Progress.Level].LDT?0:RemainLDT>=Scenario[Progress.Level].LDT/2?1:2],TRUE);
		SetDrawBlendMode(DX_BLENDMODE_MUL,128);
		DrawGraph(224,426,Graphic.LDTARE_Mask[FrameCount*2/3%20],TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
		SetDrawArea(0,0,640,480);
	}
	if(RemainARE>0&&Scenario[Progress.Level].ARE>0&&!Scenario[Progress.Level].HideGage[1]){
		SetDrawArea(224,426,224+RemainARE*83/Scenario[Progress.Level].ARE,432);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
		DrawGraph(224,426,Graphic.LDTARE_Color[RemainARE>=Scenario[Progress.Level].ARE?0:RemainARE>=Scenario[Progress.Level].ARE/2?1:2],TRUE);
		SetDrawBlendMode(DX_BLENDMODE_MUL,128);
		DrawGraph(224,426,Graphic.LDTARE_Mask[FrameCount*2/3%20],TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
		SetDrawArea(0,0,640,480);
	}
	if(Progress.DisplayPoint>0&&Scenario[Progress.Level].PointMax>=0&&!Scenario[Progress.Level].HideGage[2]){
		int gagecolor;
		if(Progress.Point>=Scenario[Progress.Level].PointMax-Scenario[Progress.Level].PreliminaryBell[1])gagecolor=2;
		else if(Progress.Point>=Scenario[Progress.Level].PointMax-Scenario[Progress.Level].PreliminaryBell[0])gagecolor=1;
		else gagecolor=0;
		DrawRectGraph(FRAMEX-16,Progress.DisplayPoint>=Scenario[Progress.Level].PointMax?FRAMEY:416-Progress.DisplayPoint*320/Scenario[Progress.Level].PointMax,0,0,6,Progress.DisplayPoint*320/Scenario[Progress.Level].PointMax,Graphic.Point_Color[gagecolor],TRUE,FALSE);
		SetDrawBlendMode(DX_BLENDMODE_MUL,128);
		DrawRectGraph(FRAMEX-16,Progress.DisplayPoint>=Scenario[Progress.Level].PointMax?FRAMEY:416-Progress.DisplayPoint*320/Scenario[Progress.Level].PointMax,0,0,6,Progress.DisplayPoint*320/Scenario[Progress.Level].PointMax,Graphic.Point_Mask[FrameCount%22],TRUE,FALSE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
	}
	if (Save.ReadSystem(Save.CASCADE)){
		int cascTemp = (int)CascadeGage;
		if (cascTemp < 0){
			cascTemp = 0;
		}
		else if (cascTemp >= 100){
			cascTemp = 100;
			colorFlag = 1;
		}
		if (cascTemp * 176 / 100 > dispCasc){
			dispCasc += 1;
		}
		else if (cascTemp * 176 / 100 < dispCasc){
			dispCasc -= 3;
			colorFlag = 1;
		}
		SetDrawArea(224, 442, 224 + dispCasc, 480);
		DrawGraph(224, 442, Graphic.cascadeColor[colorFlag], TRUE);
		SetDrawBlendMode(DX_BLENDMODE_ADD, 128);
		DrawGraph(224, 442 - 40 + cnt * 4, Graphic.cascadeMask, FALSE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		SetDrawArea(0, 0, 640, 480);
		cnt++;
		cnt %= 40;
	}
	
	if (Progress.Rank >= 0 && boardType != 0){
		if (Course.FirstStartRank == 0 || PlayStartLevel == 0){
			SetDrawArea(224, 0, 400, 480);
			DrawStringToHandle(230, 453 + yOffs, "評価", Color.White, fontTemp);
			DrawFormatStringToHandle(230, 453 + yOffs, NewRecord.Rank ? Color.Yellow : Color.White, fontTemp, "　　 %s", Course.RankName[Progress.Rank]);
			SetDrawArea(0, 0, 640, 480);
		}
	}
}

void DrawOtherPoint(){
	if(Course.RecMaxLevel)DrawFormatStringToHandle(420,283,Color.White,Font.Board,"到達レベル　　　%9d",Save.ReadCourse(Save.BEST_LEVEL)+1);
	if(Course.RecMaxPoint)DrawFormatStringToHandle(420,301,Color.White,Font.Board,"到達ポイント　　%9d",Save.ReadCourse(Save.BEST_POINT));
	if(Course.RecMaxRank)DrawFormatStringToHandle(420,319,Color.White,Font.Board,"最高評価　%14s",Course.RankName[Save.ReadCourse(Save.BEST_RANK)]);
	if(Course.RecClearTimes){
		if(Save.ReadCourse(Save.CLEAR_TIMES))DrawFormatStringToHandle(420,337,Color.White,Font.Board,"完走　　　　　%9d回",Save.ReadCourse(Save.CLEAR_TIMES));
		else DrawStringToHandle(420,337,"未完",Color.White,Font.Board);
	}
}

void DrawGameScreen(){
	int gs = GhostBlock();
	int configGhost = Save.ReadSystem(Save.GHOST);
	SetDrawMode(DX_DRAWMODE_NEAREST);
	if (!(ObstacleFlag[OBS_DARK] && Scenario[Progress.Level].Dark[0]))DrawCommonA(Scenario[Progress.Level].HideBack[0], Scenario[Progress.Level].HideBack[1], Scenario[Progress.Level].HideBack[2]);
	for (int i = 0; i < Layer.MAX; i++){
		if (Scenario[Progress.Level].LayerFlag[i])Layer.Draw(1, i, Progress.TTime, QuakeX, QuakeY);
	}
	if (!(ObstacleFlag[OBS_DARK] && Scenario[Progress.Level].Dark[1]))DrawCommonB();
	for (int i = 0; i < Layer.MAX; i++){
		if (Scenario[Progress.Level].LayerFlag[i])Layer.Draw(2, i, Progress.TTime, QuakeX, QuakeY);
	}
	if (!(ObstacleFlag[OBS_DARK] && Scenario[Progress.Level].Dark[2])){
		DrawStageBoard();
		DrawPlayBoard();
		DrawWord();
	}
	for (int i = 0; i<Layer.MAX; i++){
		if (Scenario[Progress.Level].LayerFlag[i])Layer.Draw(3, i, Progress.TTime, QuakeX, QuakeY);
	}
	if (MainPauseFlag == FALSE || MainPauseFlag>59){
		DrawRuledLine();
		if (MainPauseFlag > 59)SetDrawBright(Scenario[Progress.Level].PauseBright[0], Scenario[Progress.Level].PauseBright[1], Scenario[Progress.Level].PauseBright[2]);
		if (TetriminoSize == 2 || HpFlag || VpFlag)SetDrawMode(DX_DRAWMODE_BILINEAR);
		if (MainPauseFlag == FALSE)SetDrawBright(Scenario[Progress.Level].FieldBright[0], Scenario[Progress.Level].FieldBright[1], Scenario[Progress.Level].FieldBright[2]);
		if (!(ObstacleFlag[OBS_DARK] && Scenario[Progress.Level].Dark[3]))DrawField();
		if (MainPauseFlag == FALSE)SetDrawBright(255, 255, 255);
		for (int i = 0; i < Layer.MAX; i++){
			if (Scenario[Progress.Level].LayerFlag[i])Layer.Draw(4, i, Progress.TTime, QuakeX, QuakeY);
		}
		if (!(ObstacleFlag[OBS_DARK] && Scenario[Progress.Level].Dark[4])){
			if (MainFlag % 100 == 11){
				if (MainPauseFlag == FALSE)SetDrawBright(Scenario[Progress.Level].TetriminoBright[0], Scenario[Progress.Level].TetriminoBright[1], Scenario[Progress.Level].TetriminoBright[2]);
				DrawTetrimino();
				if (MainPauseFlag == FALSE)SetDrawBright(255, 255, 255);
			}
		}
		if (!(ObstacleFlag[OBS_DARK] && Scenario[Progress.Level].Dark[5]))if (!Scenario[Progress.Level].HideSurface)DrawSurface();
		if (TetriminoSize == 2 || HpFlag || VpFlag)SetDrawMode(DX_DRAWMODE_NEAREST);
		if (!(ObstacleFlag[OBS_DARK] && Scenario[Progress.Level].Dark[6]))if (MainPauseFlag == FALSE)DrawFlash();
		for (int i = 0; i < Layer.MAX; i++){
			if (Scenario[Progress.Level].LayerFlag[i])Layer.Draw(5, i, Progress.TTime, QuakeX, QuakeY);
		}
		if (ObstacleFlag[OBS_SNOW])DrawSnow();
		if (!(ObstacleFlag[OBS_DARK] && Scenario[Progress.Level].Dark[7])){
			if (ObstacleFlag[OBS_BOOST])DrawBoost(Scenario[Progress.Level].Boost[0]);
			if (ObstacleFlag[OBS_ALTHIDE])DrawFlipFlop();
			DrawPress();
		}
		if (ObstacleFlag[OBS_BLACKOUT])DrawBlackOut();
		for (int i = 0; i<Layer.MAX; i++){
			if (Scenario[Progress.Level].LayerFlag[i])Layer.Draw(6, i, Progress.TTime, QuakeX, QuakeY);
		}
		if (TetriminoSize == 2 || HpFlag || VpFlag)SetDrawMode(DX_DRAWMODE_BILINEAR);
		if (MainFlag % 100 == 11){
			if (gs>0){
				if ((configGhost == 2 || configGhost == 3) && !(ObstacleFlag[OBS_EXORCISE] && Scenario[Progress.Level].Exorcise[1]) && !Scenario[Progress.Level].HideGhost[1])DrawGhost(gs);
			}
			else {
				if ((configGhost == 2 || configGhost == 3) && !(ObstacleFlag[OBS_EXORCISE] && Scenario[Progress.Level].Exorcise[2]) && !Scenario[Progress.Level].HideGhost[2])DrawGhost(0);
			}
		}
		if (MainFlag % 100 == 14 && (configGhost == 1 || configGhost == 3) && !(ObstacleFlag[OBS_EXORCISE] && Scenario[Progress.Level].Exorcise[0]) && !Scenario[Progress.Level].HideGhost[0])DrawGhost(0);
		if (TetriminoSize == 2 || HpFlag || VpFlag)SetDrawMode(DX_DRAWMODE_NEAREST);
		DrawWarning();
		DrawNowLevel();
		DrawNexts();
		if (!(ObstacleFlag[OBS_DARK] && Scenario[Progress.Level].Dark[7]))DrawShutter();
		if (ObstacleFlag[OBS_NH]){
			if (Scenario[Progress.Level].NoHold[0]<0 || AfterHold>0)DrawGraph(186, 32, Graphic.Shutter[0], TRUE);
			if (AfterHold > 0)DrawFormatStringToHandle(198, 66, Color.Red, Font.Hold, "%6d", AfterHold);
		}
		for (int i = 0; i<Layer.MAX; i++){
			if (Scenario[Progress.Level].LayerFlag[i])Layer.Draw(7, i, Progress.TTime, QuakeX, QuakeY);
		}
	}
	if (MainPauseFlag>59)SetDrawBright(255, 255, 255);
	if (!(ObstacleFlag[OBS_DARK] && Scenario[Progress.Level].Dark[8]))if (!Scenario[Progress.Level].HideFrame)DrawGraph(0, 0, Graphic.Frame, TRUE);
	for (int i = 0; i<Layer.MAX; i++){
		if (Scenario[Progress.Level].LayerFlag[i])Layer.Draw(8, i, Progress.TTime, QuakeX, QuakeY);
	}
	if (MainPauseFlag == FALSE || MainPauseFlag>59){
		if (MainPauseFlag > 59)SetDrawBright(Scenario[Progress.Level].PauseBright[0], Scenario[Progress.Level].PauseBright[1], Scenario[Progress.Level].PauseBright[2]);
		if (TetriminoSize == 2 || HpFlag || VpFlag)SetDrawMode(DX_DRAWMODE_BILINEAR);
		if (!(ObstacleFlag[OBS_DARK] && Scenario[Progress.Level].Dark[9]))DrawExplosion();
		if (MainFlag % 100 == 12 && (ObstacleFlag[OBS_CASCADE] || TempCascade)){
			DrawCascadeArrow();
		}
		if (TetriminoSize == 2 || HpFlag || VpFlag)SetDrawMode(DX_DRAWMODE_NEAREST);
		if ((MainFlag / 10) == 22)DrawGraph(FRAMEX, 144, Graphic.Select[6], TRUE);
		else if ((MainFlag / 10) == 23)DrawGraph(FRAMEX, 144, Graphic.Select[7], TRUE);
	}
	if (MainPauseFlag > 59)SetDrawBright(255, 255, 255);
	DrawError();
	for (int i = 0; i < Layer.MAX; i++){
		if (Scenario[Progress.Level].LayerFlag[i])Layer.Draw(9, i, Progress.TTime, QuakeX, QuakeY);
	}
	DrawDropEffect();
	DrawAddPoint();
	if (!(ObstacleFlag[OBS_DARK] && Scenario[Progress.Level].Dark[10]))DrawCommonZ();
	for (int i = 0; i < Layer.MAX; i++){
		if (Scenario[Progress.Level].LayerFlag[i])Layer.Draw(10, i, Progress.TTime, QuakeX, QuakeY);
	}
}

void DrawFirstMenuScreen(){
	DrawCommonA(0, 0, 0);
	DrawCommonB();
	DrawMenu();
	DrawStatus();
	DrawGraph(0, 0, Graphic.Frame, TRUE);
	DrawCommonZ();
	SelecterEffect(224, Progress.Mode * 32 + 96, 64);
}
	
void DrawOtherMenuScreen(){
	DrawCommonA(0, 0, 0);
	DrawCommonB();
	DrawMenu();
	DrawGraph(258, Progress.Mode * 32 + 112, Graphic.Select[5], TRUE);
	DrawOtherPoint();
	DrawStageBoard();
	DrawText();
	DrawGraph(0, 0, Graphic.Frame, TRUE);
	DrawCommonZ();
	SelecterEffect(224, Progress.Mode * 32 + 96, 64);
}

void DrawSecondMenuScreen(){
	DrawCommonA(Scenario[Progress.Level].HideBack[0], Scenario[Progress.Level].HideBack[1], Scenario[Progress.Level].HideBack[2]);
	DrawCommonB();
	DrawMenu();
	if (Progress.Mode == 2)DrawGraph(FRAMEX - 6, Progress.Mode * 32 + 112, Graphic.Select[(Progress.Grade == 0 && 0 == MIN(Status.MaxClearGrade + 1, GRADE_MAX)) ? 2 : Progress.Grade == MIN(Status.MaxClearGrade + 1, GRADE_MAX) ? 3 : Progress.Grade == 0 ? 4 : 5], TRUE);
	else DrawGraph(FRAMEX, Progress.Mode * 32 + 112, Graphic.Select[(Progress.Level == 0 && 0 >= MIN(Save.ReadCourse(Save.BEST_LEVEL) - Course.SelectLimit, Progress.LevelMax)) ? 2 : Progress.Level == MIN(Save.ReadCourse(Save.BEST_LEVEL) - Course.SelectLimit, Progress.LevelMax) ? 3 : Progress.Level == 0 ? 4 : 5], TRUE);

	if (Progress.Mode == 2)DrawFormatStringToHandle(358, Progress.Mode * 32 + 121, Color.White, Font.Board, "%s", GradeName[Progress.Grade]);
	else DrawFormatStringToHandle(356, Progress.Mode * 32 + 121, Color.White, Font.Board, "%3d", Progress.Level + 1);
	if (Progress.Mode == 2 || Progress.Mode == 3)DrawOtherPoint();
	DrawStageBoard();
	DrawText();
	DrawGraph(0, 0, Graphic.Frame, TRUE);
	DrawCommonZ();
	SelecterEffect(224, Progress.Mode * 32 + 96, 64);
}

void DrawViewingScreen(){
	DrawCommonA(0,0,0);
}

void DrawReadyScreen(){
	if(!(ObstacleFlag[OBS_DARK]&&Scenario[Progress.Level].Dark[0]))DrawCommonA(Scenario[Progress.Level].HideBack[0],Scenario[Progress.Level].HideBack[1],Scenario[Progress.Level].HideBack[2]);
	if(!(ObstacleFlag[OBS_DARK]&&Scenario[Progress.Level].Dark[1]))DrawCommonB();
	if(!(ObstacleFlag[OBS_DARK]&&Scenario[Progress.Level].Dark[2])){
		DrawStageBoard();
		DrawPlayBoard();
	}
	if(!(ObstacleFlag[OBS_DARK]&&Scenario[Progress.Level].Dark[7])){
		DrawShutter();
		DrawPress();
	}
	DrawNexts();
	if(GameStartRemainCount>170){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,(181-GameStartRemainCount)*250/10);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
	}
	if(GameStartRemainCount>160)SetDrawBlendMode(DX_BLENDMODE_ALPHA,(181-GameStartRemainCount)*255/20);
	else if(GameStartRemainCount>120)SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
	else if(GameStartRemainCount>60){
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
		DrawStringToHandle(Course.ReadyPos,340,"READY...",Color.White,Font.Ready);
	}
	else if(GameStartRemainCount%3){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,GameStartRemainCount*255/60);
		DrawStringToHandle(Course.ReadyPos,340,"READY... GO",Color.White,Font.Ready);
	}
	else SetDrawBlendMode(DX_BLENDMODE_ALPHA,0);
	DrawGraph(FRAMEX,120,Graphic.Text[1],TRUE);
	DrawGraph(FRAMEX,140,Graphic.Text[0],TRUE);
	DrawGraph(FRAMEX,170,Graphic.Text[2],TRUE);
	DrawGraph(FRAMEX,210,Graphic.Text[3],TRUE);
	DrawGraph(FRAMEX,230,Graphic.Text[4],TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
	if(!(ObstacleFlag[OBS_DARK]&&Scenario[Progress.Level].Dark[8]))DrawGraph(0,0,Graphic.Frame,TRUE);
	DrawError();
	if(!(ObstacleFlag[OBS_DARK]&&Scenario[Progress.Level].Dark[10]))DrawCommonZ();
}

void DrawConfigurationMenuScreen(){
	int selectPos = MainFlag % 10;
	int selectPage = MainFlag % 50 / 10;
	int selectingFlag = MainFlag % 100 / 50;
	const static int itv = 9;
	const static int gap = 125;
	const static int rx = 383;
	int saveList[14] = { 0 };
	saveList[0] = Save.BGM_VOLUME;
	saveList[1] = Save.SE_VOLUME;
	saveList[2] = Save.VOICE_VOLUME;
	saveList[3] = Save.WINDOW_MODE;
	saveList[4] = Save.KEY_CONFIG;
	saveList[5] = Save.ANIMATION;
	saveList[6] = Save.SE_SET;
	saveList[7] = Save.CASCADE;
	saveList[8] = Save.BLOCK_FLAG;
	saveList[9] = Save.GHOST;
	saveList[10] = Save.RULED_LINE;
	saveList[11] = Save.DARKNESS;
	saveList[12] = Save.SHOW_ADDPT;
	saveList[13] = Save.BOARD;
	int saveNum = saveList[selectPage * 7 + selectPos];
	const static int choiceFlag[14] = { 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1 };
	const static int choiceLen[14] = { 3, 3, 3, 5, 3, 3, 1, 3, 7, 4, 1, 3, 1, 6 };
	const static char configName[14][15] = { "BGM VOL", "SE VOL", "VOICE VOL", "WINDOW", "KEY CONFIG", "ANIMATION", "SE SET", "CASCADE", "BLOCK", "GHOST", "RULED LINE", "DARKNESS", "SHOW ADD PT", "BOARD" };
	const static char configChoice[14][4][10] = { {}, {}, {}, { " FULL", "  FIX", "FLEX1", "FLEX2" }, { "KBD", "PAD" }, { "OFF", " ON" }, {}, { "OFF", " ON" }, { "CLASSIC", "  WORLD" }, { "NONE", "  UP", "DOWN", "BOTH" }, { "0", "A", "B", "C" }, {}, { "0", "S", "M", "L" }, { "  NONE", "SIMPLE", "DETAIL" } };
	DrawCommonA(0, 0, 0);
	DrawCommonB();
	for (int k = 0; k < 9; k++){
		DrawGraph(FRAMEX, 112 + k * 32, Graphic.Select[0], TRUE);
	}
	DrawGraph(FRAMEX, selectPos * 32 + 112, Graphic.Select[1], TRUE);
	if (selectingFlag == 1){
		DrawGraph(rx - itv * choiceLen[selectPage * 7 + selectPos] - gap, selectPos * 32 + 112, Graphic.Select[Save.ReadSystem(saveNum) == Save.GetConfigMax(saveNum) ? 3 : Save.ReadSystem(saveNum) == 0 ? 4 : 5], TRUE);
		if (choiceFlag[selectPage * 7 + selectPos]){
			DrawStringToHandle(rx - itv * choiceLen[selectPage * 7 + selectPos], selectPos * 32 + 121, configChoice[selectPage * 7 + selectPos][Save.ReadSystem(saveNum)], Color.White, Font.Board);
		}
		else {
			DrawFormatStringToHandle(rx - itv * 3, selectPos * 32 + 121, Color.White, Font.Board, "%3d", Save.ReadSystem(saveNum));
		}
	}
	for (int i = 0; i < 7; i++){
		DrawStringToHandle(256, 121 + 32 * i, configName[selectPage * 7 + i], Color.White, Font.Board);
	}
	DrawFormatStringToHandle(256, 121 + 32 * 7, Color.White, Font.Board, "PAGE %d", selectPage + 1);
	DrawStringToHandle(256, 121 + 32 * 8, "EXIT", Color.White, Font.Board);
	DrawGraph(0, 0, Graphic.Frame, TRUE);
	DrawCommonZ();
	SelecterEffect(224, selectPos * 32 + 96, 64);
}

void DrawKeyConfigMenuScreen(){
	int fontTemp = Font.Board;
	int selectPos = SelectOption;

	char* controlName[15] = { "　　　　　決定", "　　　　　撤回", "　　　　　　上", "　　　　　　右", "　　　　　　下", "　　　　　　左", "　　　 左回転1", "　　　 左回転2", "　　　 右回転1", "　　　 右回転2", "　　　ホールド", "ミドルドロップ", "ハードドロップ", "　　　一時停止", "　　　画面撮影" };
	DrawCommonA(0, 0, 0);
	for (int k = 0; k < 15; k++){
		DrawGraph(112 + k / 8 * 320, 112 + k % 8 * 32, Graphic.Select[0], TRUE);
		DrawStringToHandle(10 + k / 8 * 320, 121 + k % 8 * 32, controlName[k], Color.White, fontTemp);
		if (MainFlag % 100 < 50){
			DrawStringToHandle(130 + k / 8 * 320, 121 + k % 8 * 32, KeyName[Key.GetAnyKey(k)], Color.White, fontTemp);
		}
		else {
			DrawStringToHandle(130 + k / 8 * 320, 121 + k % 8 * 32, PadName[Key.GetAnyPad(k)], Color.White, fontTemp);
		}
	}
	DrawGraph(112 + 15 / 8 * 320, 112 + 15 % 8 * 32, Graphic.Select[0], TRUE);
	DrawStringToHandle(130 + 15 / 8 * 320, 121 + 15 % 8 * 32, "E X I T", Color.White, fontTemp);
	DrawGraph(240, 112 + 8 * 32, Graphic.Select[0], TRUE);
	DrawStringToHandle(284, 121 + 8 * 32, "R E S E T", Color.White, fontTemp);
	if (selectPos < 16){
		DrawGraph(112 + selectPos / 8 * 320, 112 + selectPos % 8 * 32, Graphic.Select[1], TRUE);
		SelecterEffect(96 + selectPos / 8 * 320, 96 + selectPos % 8 * 32, 64);
	}
	else {
		DrawGraph(240, 112 + 8 * 32, Graphic.Select[1], TRUE);
		SelecterEffect(224, 96 + 8 * 32, 64);
	}
	if (MainFlag % 50 > 0){
		DrawGraph(112 + selectPos / 8 * 320, 112 + selectPos % 8 * 32, Graphic.Select[5], TRUE);
		if (MainFlag % 100 < 50){
			DrawStringToHandle(50, 60, "設定したいキーを長押ししてください", Color.Yellow, Font.BigBoard);
		}
		else {
			DrawStringToHandle(50, 60, "設定したいボタンを長押ししてください", Color.Yellow, Font.BigBoard);
		}
	}
	if (MainFlag % 100 < 50){
		DrawStringToHandle(30, 30, "KEYBOARD CONFIGURATION", Color.White, Font.BigBoard);
	}
	else {
		DrawStringToHandle(30, 30, "JOYPAD CONFIGURATION", Color.White, Font.BigBoard);
		if (GetJoypadNum() == 0){
			DrawStringToHandle(50, 60, "ジョイパッドの接続が確認できません", Color.Yellow, Font.BigBoard);
		}
	}
	DrawCommonZ();
}

void DrawCareerMenuScreen(){
	int selectPos = MainFlag % 10;
	DrawCommonA(0, 0, 0);
	DrawCommonB();
	DrawGraph(FRAMEX, 112, Graphic.Select[0], TRUE);
	DrawGraph(FRAMEX, 112, Graphic.Select[1], TRUE);
	DrawGraph(258, 112, Graphic.Select[5], TRUE);
	if (selectPos == 0)DrawStringToHandle(256, 121, "SPEED ROAD", Color.White, Font.Board);
	if (selectPos == 1)DrawStringToHandle(256, 121, "CHAOS ROAD", Color.White, Font.Board);
	if (selectPos == 2)DrawStringToHandle(256, 121, "GRADE TEST", Color.White, Font.Board);
	if (selectPos == 3)DrawStringToHandle(256, 121, "OTHER COURSE", Color.White, Font.Board);
	DrawStringToHandle(248, 153, "通算出現ミノ数", Color.White, Font.Board);
	DrawStringToHandle(248, 193, "通算消去ライン数", Color.White, Font.Board);
	DrawStringToHandle(248, 233, "通算テトリス回数", Color.White, Font.Board);
	DrawStringToHandle(248, 273, "通算Ｂ２Ｂ回数", Color.White, Font.Board);
	DrawStringToHandle(248, 313, "通算Ｔスピン回数", Color.White, Font.Board);
	DrawStringToHandle(248, 353, "通算ＲＥＮ回数", Color.White, Font.Board);
	for (int i = 0; i < 6; i++){
		DrawFormatStringToHandle(248, 173 + i * 40, Color.White, Font.Board, "%16d", Save.ReadSystem(Save.TOTALS_TM + selectPos * 6 + i));
	}
	DrawGraph(0, 0, Graphic.Frame, TRUE);
	DrawCommonZ();
	SelecterEffect(224, 96, 64);
}

void DrawMain(){
	int first=MainFlag/100,second=MainFlag%100/10;
	if(ObstacleFlag[OBS_PRESS]&&Scenario[Progress.Level].Press[0]){
		VpFlag=1;
	}
	else {
		VpFlag=0;
	}
	if(ObstacleFlag[OBS_PRESS]&&Scenario[Progress.Level].Press[1]){
		HpFlag=1;
	}
	else {
		HpFlag=0;
	}
	for(int i=0;i<3;i++){
		if(ObstacleFlag[OBS_REVERSE]&&Scenario[Progress.Level].Reverse[i])RevFlag[i]=1;
		else RevFlag[i]=0;
	}
	for(int i=0;i<7;i++){
		if(ObstacleFlag[OBS_MONO]&&Scenario[Progress.Level].Monochrome[i])MonoFlag[i]=1;
		else MonoFlag[i]=0;
	}
	for(int i=0;i<7;i++){
		if(ObstacleFlag[OBS_RC]&&Scenario[Progress.Level].RandomColor[i])RCFlag[i]=1;
		else RCFlag[i]=0;
	}
	for(int i=0;i<4;i++){
		if(ObstacleFlag[OBS_CLONE])CloneTimes[i]=Scenario[Progress.Level].Clone[i];
		else CloneTimes[i]=0;
	}
	if(ObstacleFlag[OBS_ALTHIDE]&&Scenario[Progress.Level].AlternateHide[0]){
		if(AlternateHideState==0){
			AHPos[0]=Scenario[Progress.Level].AlternateHide[1];
			AHPos[1]=0;
		}
		else {
			AHPos[0]=0;
			AHPos[1]=Scenario[Progress.Level].AlternateHide[2];
		}
	}
	else {
		AHPos[0]=0;
		AHPos[1]=0;
	}
	if(ObstacleFlag[OBS_BIG]){
		TetriminoSize=2;
	}
	else {
		TetriminoSize=1;
	}
	if(first==0){
		if(ViewMode==0){
			if(second<=1)DrawFirstMenuScreen();
			else if(second==2)DrawOtherMenuScreen();
			else if(second==3)DrawSecondMenuScreen();
		}
		else DrawViewingScreen();
	}
	else if(first==1){
		if(MainPauseFlag){
			DrawGameScreen();
			DrawPause();
		}
		else DrawReadyScreen();
	}
	else if(first==2){
		if(MainPauseFlag){
			DrawGameScreen();
			DrawPause();
		}
		else DrawGameScreen();
	}
	else if(first==3){
		DrawConfigurationMenuScreen();
	}
	else if(first==4){
		DrawCareerMenuScreen();
	}
	else if (first == 5){
		DrawKeyConfigMenuScreen();
	}
	FrameCount++;
}