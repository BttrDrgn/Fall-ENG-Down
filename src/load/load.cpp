#include <DxLib.h>
#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")
#include <animation/animation.h>
#include <display/display.h>
#include <game_play/game_play.h>
#include <layer/layer.h>
#include <load/load.h>
#include <macro_function.h>
#include <save/save.h>

char CourseTag[TAG_MAX][20];
char BoardName[BOARD_MAX][16];
char SignName[SIGN_MAX][16];
char CrsSaveFileName[256];
char SubDir[256];

Course_t D_Course;
Scenario_t D_Scenario[LEVEL_MAX];
Course_t Course;
Scenario_t Scenario[LEVEL_MAX];
GraphicInfo_t GraphicInfo;

void CourseTagSetting(){
	memset(CourseTag,0,sizeof(CourseTag));
	strcpy_s(CourseTag[0],20,"#COMENT");
	strcpy_s(CourseTag[1],20,"#MAINDATAFIELD");
	strcpy_s(CourseTag[2],20,"#INDEXTITLE");
	strcpy_s(CourseTag[3],20,"#GENRE");
	strcpy_s(CourseTag[4],20,"#TITLE");
	strcpy_s(CourseTag[5],20,"#SUBTITLE");
	strcpy_s(CourseTag[6],20,"#ARTIST");
	strcpy_s(CourseTag[7],20,"#SUBARTIST");
	strcpy_s(CourseTag[8],20,"#FONT");
	strcpy_s(CourseTag[9],20,"#FONTTHICKNESS");
	strcpy_s(CourseTag[10],20,"#TEXT");
	strcpy_s(CourseTag[11],20,"#SELECTLIMIT");
	strcpy_s(CourseTag[12],20,"#NATURALOBSTACLE");
	strcpy_s(CourseTag[13],20,"#FIRSTTETRIMINO");
	strcpy_s(CourseTag[14],20,"#EXCHANGETETRIMINO");
	strcpy_s(CourseTag[15],20,"#RANKNAME");
	strcpy_s(CourseTag[16],20,"#RANKBASE");
	strcpy_s(CourseTag[17],20,"#RANKFORM");

	strcpy_s(CourseTag[20],20,"#RECHIGHESTSCORE");
	strcpy_s(CourseTag[21],20,"#RECFASTESTTIME");
	strcpy_s(CourseTag[22],20,"#RECMAXLEVEL");
	strcpy_s(CourseTag[23],20,"#RECMAXPOINT");
	strcpy_s(CourseTag[24],20,"#RECMAXRANK");
	strcpy_s(CourseTag[25],20,"#RECCLEARTIMES");
	strcpy_s(CourseTag[26],20,"#SAVEFILEPATH");

	strcpy_s(CourseTag[30],20,"#CLEARFIELD");
	strcpy_s(CourseTag[31],20,"#LEVELUP");
	strcpy_s(CourseTag[32],20,"#EXORCISE");
	strcpy_s(CourseTag[33],20,"#CLEARFORBIG");
	strcpy_s(CourseTag[34],20,"#BIG");
	strcpy_s(CourseTag[35],20,"#NOHOLD");
	strcpy_s(CourseTag[36],20,"#BOOST");
	strcpy_s(CourseTag[37],20,"#COPYGARBAGE");
	strcpy_s(CourseTag[38],20,"#RANDOMGARBAGE");
	strcpy_s(CourseTag[39],20,"#SHUTTER");

	strcpy_s(CourseTag[40],20,"#SHADOW");
	strcpy_s(CourseTag[41],20,"#SUDDENAPPEAR");
	strcpy_s(CourseTag[42],20,"#RANDOMCOLOR");
	strcpy_s(CourseTag[43],20,"#MONOCHROME");
	strcpy_s(CourseTag[44],20,"#REVERSE");
	strcpy_s(CourseTag[45],20,"#DARK");
	strcpy_s(CourseTag[46],20,"#ALTERNATEHIDE");
	strcpy_s(CourseTag[47],20,"#SNOW");
	strcpy_s(CourseTag[48],20,"#LIFT");
	strcpy_s(CourseTag[49],20,"#PRESS");
	strcpy_s(CourseTag[50],20,"#QUAKE");
	strcpy_s(CourseTag[51],20,"#BLACKOUT");
	strcpy_s(CourseTag[52],20,"#ZEROGRAVITY");
	strcpy_s(CourseTag[53],20,"#CLONE");
	strcpy_s(CourseTag[54],20,"#CASCADE");
	strcpy_s(CourseTag[55], 20, "#DROPEFFECT");

	strcpy_s(CourseTag[65],20,"#OBSTACLEFLAG");
	strcpy_s(CourseTag[66],20,"#FIRSTOBSTACLE");

	strcpy_s(CourseTag[70],20,"#NOPAUSE");
	strcpy_s(CourseTag[71],20,"#LINECLEARPOINT");
	strcpy_s(CourseTag[72],20,"#BACKTOBACKPOINT");
	strcpy_s(CourseTag[73],20,"#TSPINPOINT");
	strcpy_s(CourseTag[74],20,"#RENPOINT");
	strcpy_s(CourseTag[75],20,"#PROGRESSCONDITION");
	strcpy_s(CourseTag[76],20,"#PRELIMINARYBELL");
	strcpy_s(CourseTag[77],20,"#LEVELUPWAITTIME");
	strcpy_s(CourseTag[78],20,"#INITIALFIELDPATH");
	strcpy_s(CourseTag[79], 20, "#CASCADERATE");

	strcpy_s(CourseTag[80],20,"#MOVEINFINITYMAX");
	strcpy_s(CourseTag[81],20,"#TURNINFINITYMAX");
	strcpy_s(CourseTag[82],20,"#INFINITYDELAY");
	strcpy_s(CourseTag[83],20,"#EMERGECOLUMN");
	strcpy_s(CourseTag[84],20,"#EMERGEROW");
	strcpy_s(CourseTag[85],20,"#EMERGEBIGCOLUMN");
	strcpy_s(CourseTag[86],20,"#EMERGEBIGROW");
	strcpy_s(CourseTag[87],20,"#SMOOTHDROP");
	strcpy_s(CourseTag[88], 20, "#SOFTDROPINTERVAL");

	strcpy_s(CourseTag[90],20,"#HIDEOBSTACLE");
	strcpy_s(CourseTag[91],20,"#HIDETEXT");
	strcpy_s(CourseTag[92],20,"#HIDETETRIMINO");
	strcpy_s(CourseTag[93],20,"#HIDEFIELD");
	strcpy_s(CourseTag[94],20,"#HIDEGAGE");
	strcpy_s(CourseTag[95],20,"#HIDEGHOST");
	strcpy_s(CourseTag[96],20,"#HIDESURFACE");
	strcpy_s(CourseTag[97],20,"#HIDEHOLD");
	strcpy_s(CourseTag[98],20,"#HIDENEXT");
	strcpy_s(CourseTag[99],20,"#HIDEEXPLOSION");
	strcpy_s(CourseTag[100],20,"#HIDEBACK");
	strcpy_s(CourseTag[101],20,"#HIDECURTAIN");
	strcpy_s(CourseTag[102],20,"#HIDEFRAME");

	strcpy_s(CourseTag[110],20,"#PAUSEBRIGHT");
	strcpy_s(CourseTag[111],20,"#FIELDBRIGHT");
	strcpy_s(CourseTag[112],20,"#TETRIMINOBRIGHT");
	strcpy_s(CourseTag[113],20,"#BLACKBACKBRIGHT");
	strcpy_s(CourseTag[114],20,"#WHITEBACKBRIGHT");
	strcpy_s(CourseTag[115],20,"#MASKBACKBRIGHT");
	strcpy_s(CourseTag[116],20,"#NEXTBRIGHT");
	strcpy_s(CourseTag[117],20,"#HOLDBRIGHT");
	strcpy_s(CourseTag[118],20,"#GHOSTBRIGHT");
	strcpy_s(CourseTag[119],20,"#EXPLOSIONBRIGHT");

	strcpy_s(CourseTag[120],20,"#FLASHCOLOR");
	strcpy_s(CourseTag[121],20,"#SURFACECOLOR");
	strcpy_s(CourseTag[122],20,"#SNOWCOLOR");

	strcpy_s(CourseTag[130],20,"#FLASHINTENSITY");
	strcpy_s(CourseTag[131],20,"#FLASHTIME");
	strcpy_s(CourseTag[132],20,"#FLASHMAX");
	strcpy_s(CourseTag[133],20,"#FLASHFILL");
	strcpy_s(CourseTag[134],20,"#SURFACETHICKNESS");

	strcpy_s(CourseTag[140],20,"#SHAPEPATH");
	strcpy_s(CourseTag[141],20,"#USESHAPE");
	strcpy_s(CourseTag[142],20,"#SHAPEBLACKOUT");
	strcpy_s(CourseTag[143],20,"#SHAPETSPININFO");
	strcpy_s(CourseTag[144],20,"#SHAPETSPINPOINT");
	strcpy_s(CourseTag[145],20,"#SHAPETSPINMINI");

	strcpy_s(CourseTag[150],20,"#ROTATIONPATH");
	strcpy_s(CourseTag[151],20,"#ROTATIONTYPE");
	strcpy_s(CourseTag[152],20,"#USEROTATION");

	strcpy_s(CourseTag[160],20,"#BGMPATH");
	strcpy_s(CourseTag[161],20,"#BGMINFO");
	strcpy_s(CourseTag[162],20,"#PLAYBGM");

	strcpy_s(CourseTag[170],20,"#LAYERPATH");
	strcpy_s(CourseTag[171],20,"#LAYERINFO_DRAW");
	strcpy_s(CourseTag[172],20,"#LAYERINFO_XY");
	strcpy_s(CourseTag[173],20,"#LAYERINFO_ROTA");
	strcpy_s(CourseTag[174],20,"#LAYERINFO_ACT");
	strcpy_s(CourseTag[175],20,"#LAYERINFO_LIMIT");
	strcpy_s(CourseTag[176],20,"#COPYLAYERPATH");
	strcpy_s(CourseTag[177],20,"#COPYLAYERINFO");
	strcpy_s(CourseTag[178],20,"#DRAWLAYER");
	strcpy_s(CourseTag[179],20,"#DRAWLAYER_RANGE");
	
	strcpy_s(CourseTag[180],20,"#SCOREBASE");
	strcpy_s(CourseTag[181],20,"#CALCSCOREBASE_0");
	strcpy_s(CourseTag[182],20,"#CALCSCOREBASE_1"); 
	strcpy_s(CourseTag[183],20,"#BACKNUM");
	strcpy_s(CourseTag[184],20,"#ADDBACKNUM");
	strcpy_s(CourseTag[185],20,"#APPLYIF");

	strcpy_s(CourseTag[190],20,"#SETRETURNSTATE");
	strcpy_s(CourseTag[191],20,"#SETLEVEL");
	strcpy_s(CourseTag[192],20,"#SETRANGE");
	strcpy_s(CourseTag[193],20,"#SETJUMP");
	strcpy_s(CourseTag[194],20,"#SETJUMPSTATE");
	strcpy_s(CourseTag[195],20,"#SHOWERRORROW");
	strcpy_s(CourseTag[196],20,"#IF");
	strcpy_s(CourseTag[197], 20, "#CURRENTDIRFLAG");
	strcpy_s(CourseTag[198],20,"#COPYLEVELDATA");
	strcpy_s(CourseTag[199],20,"#STATE");
}

void BoardSignNameSetting(){
	strcpy_s(BoardName[0],sizeof(BoardName[0]),"LEVEL");
	strcpy_s(BoardName[1],sizeof(BoardName[1]),"POINT");
	strcpy_s(BoardName[2],sizeof(BoardName[2]),"POINTMAX");
	strcpy_s(BoardName[3],sizeof(BoardName[3]),"TARGET");
	strcpy_s(BoardName[4],sizeof(BoardName[4]),"LEFTOVER");
	strcpy_s(BoardName[5],sizeof(BoardName[5]),"L-TIME");
	strcpy_s(BoardName[6],sizeof(BoardName[6]),"T-TIME");
	strcpy_s(BoardName[7],sizeof(BoardName[7]),"OBSTACLE");
	strcpy_s(BoardName[8],sizeof(BoardName[8]),"SCORE");
	strcpy_s(BoardName[9],sizeof(BoardName[9]),"HIGHESTSCORE");
	strcpy_s(BoardName[10],sizeof(BoardName[10]),"L-TETRIMINO");
	strcpy_s(BoardName[11],sizeof(BoardName[11]),"T-TETRIMINO");
	strcpy_s(BoardName[12],sizeof(BoardName[12]),"L-LINE");
	strcpy_s(BoardName[13],sizeof(BoardName[13]),"T-LINE");
	strcpy_s(BoardName[14],sizeof(BoardName[14]),"TETRIMINO/M");
	strcpy_s(BoardName[15],sizeof(BoardName[15]),"LINE/M");
	strcpy_s(BoardName[16],sizeof(BoardName[16]),"L-TETRIS");
	strcpy_s(BoardName[17],sizeof(BoardName[17]),"T-TETRIS");
	strcpy_s(BoardName[18],sizeof(BoardName[18]),"L-B2B");
	strcpy_s(BoardName[19],sizeof(BoardName[19]),"T-B2B");
	strcpy_s(BoardName[20],sizeof(BoardName[20]),"L-TSPIN");
	strcpy_s(BoardName[21],sizeof(BoardName[21]),"T-TSPIN");
	strcpy_s(BoardName[22],sizeof(BoardName[22]),"L-REN");
	strcpy_s(BoardName[23],sizeof(BoardName[23]),"T-REN");
	strcpy_s(BoardName[24],sizeof(BoardName[24]),"NUMERATOR");
	strcpy_s(BoardName[25],sizeof(BoardName[25]),"DENOMINATOR");
	strcpy_s(BoardName[26],sizeof(BoardName[26]),"LDT");
	strcpy_s(BoardName[27],sizeof(BoardName[27]),"LCT");
	strcpy_s(BoardName[28],sizeof(BoardName[28]),"ARE");
	strcpy_s(BoardName[29],sizeof(BoardName[29]),"DAS");
	strcpy_s(BoardName[30],sizeof(BoardName[30]),"RANK");
	strcpy_s(BoardName[31],sizeof(BoardName[31]),"SCOREPPM");
	strcpy_s(BoardName[32], sizeof(BoardName[32]), "T-TIMEPPM");
	strcpy_s(BoardName[33],sizeof(BoardName[33]),"L-MAXREN");
	strcpy_s(BoardName[34],sizeof(BoardName[34]),"T-MAXREN");
	strcpy_s(BoardName[35],sizeof(BoardName[35]),"RAND-GAME");
	strcpy_s(BoardName[36],sizeof(BoardName[36]),"RAND-LEVEL");
	strcpy_s(BoardName[37],sizeof(BoardName[37]),"RAND-LINE");
	strcpy_s(BoardName[38],sizeof(BoardName[38]),"RAND-TETRIMINO");
	strcpy_s(BoardName[39],sizeof(BoardName[39]),"RAND-FRAME");

	strcpy_s(SignName[0],sizeof(SignName[0]),"<");
	strcpy_s(SignName[1],sizeof(SignName[1]),"<=");
	strcpy_s(SignName[2],sizeof(SignName[2]),">");
	strcpy_s(SignName[3],sizeof(SignName[3]),">=");
	strcpy_s(SignName[4],sizeof(SignName[4]),"==");
	strcpy_s(SignName[5],sizeof(SignName[5]),"!=");
}

void LoadBackGraphic(int main_or_notmain){
	char Path[256]={0};
	if(GraphicInfo.MaskLevel>=0&&GraphicInfo.MaskLevel<LEVEL_MAX){
		GraphicInfo.MaskNumber=Scenario[GraphicInfo.MaskLevel].BackMaskNum%GraphicInfo.BackMaskMax;
	}
	else {
		GraphicInfo.MaskNumber=-1;
	}
	if(main_or_notmain){
		if(LoadBlackBackGraphic(-1)){
			BlackBackRemainCount=80;
		}
		if(LoadWhiteBackGraphic(-1)){
			WhiteBackRemainCount=80;
		}
		if(Animation.Load(-1)){
			MaskBackRemainCount=80;
		}
	}
	else {
		if(LoadBlackBackGraphic(Scenario[Progress.Level].BackBlackNum%GraphicInfo.BackBlackMax)){
			BlackBackRemainCount=80;
		}
		if(Save.ReadSystem(Save.ANIMATION)){
			if(LoadWhiteBackGraphic(Scenario[Progress.Level].BackWhiteNum%GraphicInfo.BackWhiteMax)){
				WhiteBackRemainCount=80;
			}
			if(Animation.Load(Scenario[Progress.Level].BackMaskNum%GraphicInfo.BackMaskMax)){
				MaskBackRemainCount=80;
			}
		}
	}
}

void SetShapeBoostPos(int num){
	for(int i=0;i<7;i++){
		for(int j=0;j<4;j++){
			for(int k=3;k>=0;k--){
				if(Course.Shape[num][i][j][k][0]||Course.Shape[num][i][j][k][1]||Course.Shape[num][i][j][k][2]||Course.Shape[num][i][j][k][3]){
					Course.ShapeBoostPos[num][i][j]=k;
					k=-1;
				}
			}
		}
	}
}

int LoadShape(char Path[256],int num){
	if(num<0){
		num=0;
	}
	else if(num>SHAPE_MAX-1){
		num=SHAPE_MAX-1;
	}
	memset(Course.Shape[num],0,sizeof(Course.Shape[num]));
	int fp=FileRead_open(Path);
	if(!fp)return -1;
	for(int i=0;i<112&&!FileRead_eof(fp);i++){
		char Data[256]={0};
		FileRead_gets(Data,sizeof(Data),fp);
		sscanf_s(Data,"%d %d %d %d",&Course.Shape[num][i/16][i%16/4][i%4][0],&Course.Shape[num][i/16][i%16/4][i%4][1],&Course.Shape[num][i/16][i%16/4][i%4][2],&Course.Shape[num][i/16][i%16/4][i%4][3]);
	}
	FileRead_close(fp);
	SetShapeBoostPos(num);
	return 0;
}

int LoadRotation(char Path[256],int num){
	if(num<0){
		num=0;
	}
	else if(num>ROTATION_MAX-1){
		num=ROTATION_MAX-1;
	}
	memset(Course.Rotation[num],0,sizeof(Course.Rotation[num]));
	int fp=FileRead_open(Path);
	if(!fp)return -1;
	for(int i=0;i<56&&!FileRead_eof(fp);i++){
		char Data[256]={0};
		FileRead_gets(Data,sizeof(Data),fp);
		sscanf_s(Data,"%d,%d %d,%d %d,%d %d,%d %d,%d %d,%d %d,%d %d,%d %d,%d %d,%d %d,%d %d,%d %d,%d %d,%d %d,%d %d,%d",
			&Course.Rotation[num][i/8][i%8][0],&Course.Rotation[num][i/8][i%8][1],
			&Course.Rotation[num][i/8][i%8][2],&Course.Rotation[num][i/8][i%8][3],
			&Course.Rotation[num][i/8][i%8][4],&Course.Rotation[num][i/8][i%8][5],
			&Course.Rotation[num][i/8][i%8][6],&Course.Rotation[num][i/8][i%8][7],
			&Course.Rotation[num][i/8][i%8][8],&Course.Rotation[num][i/8][i%8][9],
			&Course.Rotation[num][i/8][i%8][10],&Course.Rotation[num][i/8][i%8][11],
			&Course.Rotation[num][i/8][i%8][12],&Course.Rotation[num][i/8][i%8][13],
			&Course.Rotation[num][i/8][i%8][14],&Course.Rotation[num][i/8][i%8][15],
			&Course.Rotation[num][i/8][i%8][16],&Course.Rotation[num][i/8][i%8][17],
			&Course.Rotation[num][i/8][i%8][18],&Course.Rotation[num][i/8][i%8][19],
			&Course.Rotation[num][i/8][i%8][20],&Course.Rotation[num][i/8][i%8][21],
			&Course.Rotation[num][i/8][i%8][22],&Course.Rotation[num][i/8][i%8][23],
			&Course.Rotation[num][i/8][i%8][24],&Course.Rotation[num][i/8][i%8][25],
			&Course.Rotation[num][i/8][i%8][26],&Course.Rotation[num][i/8][i%8][27],
			&Course.Rotation[num][i/8][i%8][28],&Course.Rotation[num][i/8][i%8][29],
			&Course.Rotation[num][i/8][i%8][30],&Course.Rotation[num][i/8][i%8][31]);
	}
	FileRead_close(fp);
	return 0;
}

int BoardAllotment(char BoardString[16]){
	for(int i=0;i<BOARD_MAX;i++)if(strcmp(BoardString,BoardName[i])==0)return i;
	return -1;
}

int SignAllotment(char Signstring[16]){
	for(int i=0;i<SIGN_MAX;i++)if(strcmp(Signstring,SignName[i])==0)return i;
	return -1;
}

int LoadCourse(char coursefile[256], int IfNum){
	int row = 1, errors = 0, fall = 0, filechars = 0, state = 0, level = 0, showerrorrow = 0, range = LEVEL_MAX, jump = 1, returnstate = -1, jumpstate = 1, readable = 1;
	int subDirFlag = 0;
	int fp = FileRead_open(coursefile);
	if (!fp){
		MessageBox(NULL, "I can't insert the course file", "Error", MB_OK);
		return -1;
	}
	if (IfNum >= 0 && IfNum < IF_MAX){
		//returnstate = Course.IfTermControl[IfNum][0];
		//level = Course.IfTermControl[IfNum][1];
		//range = Course.IfTermControl[IfNum][2];
		//jump = Course.IfTermControl[IfNum][3];
		level = Progress.Level;
		FileRead_seek(fp, Course.IfPointer[IfNum], SEEK_SET);
	}
	else {
		memcpy_s(&Course, sizeof(Course_t), &D_Course, sizeof(Course_t));
		memcpy_s(Scenario, sizeof(Scenario_t)*LEVEL_MAX, D_Scenario, sizeof(Scenario_t)*LEVEL_MAX);
		memset(CrsSaveFileName, 0, sizeof(CrsSaveFileName));
		Layer.Initialize();
		strcpy_s(CrsSaveFileName, sizeof(CrsSaveFileName), coursefile);
		filechars = strlen(CrsSaveFileName);
		memcpy_s(SubDir, sizeof(SubDir), CrsSaveFileName, _countof(SubDir));
		for (int i = filechars - 1; i > 0; i -= 1){
			if (SubDir[i] == '/'){
				i = 0;
			}
			else {
				SubDir[i] = '\0';
			}
		}
		CrsSaveFileName[filechars - 4] = 's';
		CrsSaveFileName[filechars - 3] = 'a';
		CrsSaveFileName[filechars - 2] = 'v';
		CrsSaveFileName[filechars - 1] = 'e';

	}
	while (FileRead_eof(fp) == 0){
		int fall = 0, pos = 0;
		char Data[256] = { 0 }, Path[256] = { 0 }, PathMerge[256] = { 0 };
		FileRead_gets(Data, sizeof(Data), fp);
		if ((Data[0] == '/'&&Data[1] == '/') || Data[0] == 0){
		}
		else if (Data[0] == '*'&&Data[1] == 'E'&&Data[2] == 'N'&&Data[3] == 'D'&&Data[4] == 'I'&&Data[5] == 'F'){
			if (IfNum >= 0 && IfNum < IF_MAX){
				FileRead_close(fp);
				return MIN(LEVEL_MAX - 1, level - 1);
			}
			else readable = 1;
		}
		else if (readable&&Data[0] == '#'){
			int tag;
			for (tag = 0; tag < TAG_MAX; tag++){
				if (strcmp(CourseTag[tag], Data) == 0){
					state = tag;
					if (state == 1){
						level = 0;
						range = 1;
						returnstate = 1;
					}
					if (state >= 30 && state < 30 + OBSTACLE_MAX){
						for (int i = level; i < MIN(level + range, LEVEL_MAX); i++){
							Scenario[i].ObstacleFlag[state - 30] = 1;
						}
					}
					tag = 1000;
				}
			}
			if (tag == TAG_MAX){
				state = 0;
				fall = EOF;
			}
		}
		else if (readable){
			switch (state){
			case 0:break;
			case 1:
				if (level >= 0 && level<LEVEL_MAX){
					fall = sscanf_s(Data, "%d,%d,%d,%d,%d,%d,%d,%d,%d", &Scenario[level].Numerator, &Scenario[level].Denominator, &Scenario[level].LDT, &Scenario[level].LCT, &Scenario[level].ARE, &Scenario[level].DAS, &Scenario[level].PointMax, &Scenario[level].TargetTime, &Scenario[level].ObstacleTime);
					if (Scenario[level].DAS <= 0){
						if (Scenario[level].Denominator / Scenario[level].Numerator>1){
							if (Scenario[level].ARE >= 24)Scenario[level].DAS = 12;
							else if (Scenario[level].ARE >= 16)Scenario[level].DAS = Scenario[level].ARE / 2;
							else Scenario[level].DAS = 8;
							if (Scenario[level].DAS < 1)Scenario[level].DAS = 1;
						}
						else {
							if (Scenario[level].ARE >= 16)Scenario[level].DAS = 8;
							else if (Scenario[level].ARE >= 12)Scenario[level].DAS = Scenario[level].ARE / 2;
							else if (Scenario[level].ARE >= 6)Scenario[level].DAS = 6;
							else Scenario[level].DAS = Scenario[level].ARE;
							if (Scenario[level].DAS < 1)Scenario[level].DAS = 1;
						}
					}
				}
				break;
			case 2:fall = strncpy_s(Course.IndexTitle, _countof(Course.IndexTitle), Data, _countof(Course.IndexTitle) - 1); break;
			case 3:fall = strncpy_s(Course.TitleText[1], _countof(Course.TitleText[1]), Data, _countof(Course.TitleText[1]) - 1); break;
			case 4:fall = strncpy_s(Course.TitleText[0], _countof(Course.TitleText[0]), Data, _countof(Course.TitleText[0]) - 1); break;
			case 5:fall = strncpy_s(Course.TitleText[2], _countof(Course.TitleText[2]), Data, _countof(Course.TitleText[2]) - 1); break;
			case 6:fall = strncpy_s(Course.TitleText[3], _countof(Course.TitleText[3]), Data, _countof(Course.TitleText[3]) - 1); break;
			case 7:fall = strncpy_s(Course.TitleText[4], _countof(Course.TitleText[4]), Data, _countof(Course.TitleText[4]) - 1); break;
			case 8:fall = strncpy_s(Course.Font, _countof(Course.Font), Data, _countof(Course.Font) - 1); break;
			case 9:fall = sscanf_s(Data, "%d", &Course.FontThickness); break;
			case 10:fall = sscanf_s(Data, "%d %[^\n]", &pos, Path, sizeof(Path)); strncpy_s(Course.Text[MAX(0, MIN(pos, 5))], _countof(Course.Text[MAX(0, MIN(pos, 5))]), Path, _countof(Course.Text[MAX(0, MIN(pos, 5))]) - 1); break;
			case 11:fall = sscanf_s(Data, "%d", &Course.SelectLimit); break;
			case 12:fall = sscanf_s(Data, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
				&Course.NaturalObstacle[0], &Course.NaturalObstacle[1], &Course.NaturalObstacle[2], &Course.NaturalObstacle[3], &Course.NaturalObstacle[4],
				&Course.NaturalObstacle[5], &Course.NaturalObstacle[6], &Course.NaturalObstacle[7], &Course.NaturalObstacle[8], &Course.NaturalObstacle[9],
				&Course.NaturalObstacle[10], &Course.NaturalObstacle[11], &Course.NaturalObstacle[12], &Course.NaturalObstacle[13], &Course.NaturalObstacle[14],
				&Course.NaturalObstacle[15], &Course.NaturalObstacle[16], &Course.NaturalObstacle[17], &Course.NaturalObstacle[18], &Course.NaturalObstacle[19],
				&Course.NaturalObstacle[20], &Course.NaturalObstacle[21], &Course.NaturalObstacle[22], &Course.NaturalObstacle[23], &Course.NaturalObstacle[24],
				&Course.NaturalObstacle[25], &Course.NaturalObstacle[26], &Course.NaturalObstacle[27], &Course.NaturalObstacle[28], &Course.NaturalObstacle[29]);
				break;

			case 13:fall = sscanf_s(Data, "%d,%d,%d,%d,%d,%d,%d", &Course.FirstTetrimino[0], &Course.FirstTetrimino[1], &Course.FirstTetrimino[2], &Course.FirstTetrimino[3], &Course.FirstTetrimino[4], &Course.FirstTetrimino[5], &Course.FirstTetrimino[6]); break;
			case 14:fall = sscanf_s(Data, "%d %[^\n]", &pos, Path, sizeof(Path)); sscanf_s(Path, "%d,%d,%d,%d,%d,%d", &Course.ExchangeTetrimino[MAX(0, MIN(pos, 9))][0], &Course.ExchangeTetrimino[MAX(0, MIN(pos, 9))][1], &Course.ExchangeTetrimino[MAX(0, MIN(pos, 9))][2], &Course.ExchangeTetrimino[MAX(0, MIN(pos, 9))][3], &Course.ExchangeTetrimino[MAX(0, MIN(pos, 9))][4], &Course.ExchangeTetrimino[MAX(0, MIN(pos, 9))][5]); break;
			case 15:fall = sscanf_s(Data, "%d %[^\n]", &pos, Path, sizeof(Path)); strncpy_s(Course.RankName[MAX(0, MIN(pos, LEVEL_MAX - 1))], _countof(Course.RankName[MAX(0, MIN(pos, LEVEL_MAX - 1))]), Path, _countof(Course.RankName[MAX(0, MIN(pos, LEVEL_MAX - 1))]) - 1); break;
			case 16:fall = sscanf_s(Data, "%d %[^\n]", &pos, Path, sizeof(Path)); sscanf_s(Path, "%d", &Course.RankBase[MAX(0, MIN(pos, LEVEL_MAX - 1))]); break;
			case 17:do{
						char BoardString[16] = { 0 }, SignString[16] = { 0 };
						fall = sscanf_s(Data, "%s %s %d,%d,%d,%d", SignString, sizeof(SignString), BoardString, sizeof(BoardString), &Course.RankMax, &Course.PlayingRank, &Course.GameOverRank, &Course.FirstStartRank);
						Course.RankSign = SignAllotment(SignString);
						Course.RankBoard = BoardAllotment(BoardString);
			} while (0);
				break;

			case 20:fall = sscanf_s(Data, "%d", &Course.HighestScore); break;
			case 21:fall = sscanf_s(Data, "%d", &Course.SpeedRun); break;
			case 22:fall = sscanf_s(Data, "%d", &Course.RecMaxLevel); break;
			case 23:fall = sscanf_s(Data, "%d", &Course.RecMaxPoint); break;
			case 24:fall = sscanf_s(Data, "%d", &Course.RecMaxRank); break;
			case 25:fall = sscanf_s(Data, "%d", &Course.RecClearTimes); break;
			case 26:
				memset(PathMerge, 0, sizeof(PathMerge));
				if (subDirFlag){
					strcpy_s(PathMerge, _countof(PathMerge), SubDir);
				}
				strcat_s(PathMerge, Data);
				fall = strncpy_s(CrsSaveFileName, _countof(CrsSaveFileName), PathMerge, _countof(CrsSaveFileName) - 1);
				break;

			case 30:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d,%d,%d,%d", &Scenario[i].ClearField[0], &Scenario[i].ClearField[1], &Scenario[i].ClearField[2], &Scenario[i].ClearField[3]); break;
			case 31:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++){
						char BoardString[5][16] = { 0 }, SignString[5][16] = { 0 };
						fall = sscanf_s(Data, "%d,%d %s %s %d && %s %s %d && %s %s %d && %s %s %d && %s %s %d", &Scenario[i].LevelUp[0], &Scenario[i].LevelUp[1],
							BoardString[0], sizeof(BoardString[0]), SignString[0], sizeof(SignString[0]), &Scenario[i].LevelUpCondition[2],
							BoardString[1], sizeof(BoardString[1]), SignString[1], sizeof(SignString[1]), &Scenario[i].LevelUpCondition[5],
							BoardString[2], sizeof(BoardString[2]), SignString[2], sizeof(SignString[2]), &Scenario[i].LevelUpCondition[8],
							BoardString[3], sizeof(BoardString[3]), SignString[3], sizeof(SignString[3]), &Scenario[i].LevelUpCondition[11],
							BoardString[4], sizeof(BoardString[4]), SignString[4], sizeof(SignString[4]), &Scenario[i].LevelUpCondition[14]);
						for (int j = 0; j < 5 && BoardString[j][0] != '\0'; j++)Scenario[i].LevelUpCondition[j * 3] = BoardAllotment(BoardString[j]);
						for (int j = 0; j < 5 && SignString[j][0] != '\0'; j++)Scenario[i].LevelUpCondition[j * 3 + 1] = SignAllotment(SignString[j]);
			}
					break;
			case 32:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d,%d,%d", &Scenario[i].Exorcise[0], &Scenario[i].Exorcise[1], &Scenario[i].Exorcise[2]); break;
			case 33:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d,%d,%d,%d", &Scenario[i].ClearForBig[0], &Scenario[i].ClearForBig[1], &Scenario[i].ClearForBig[2], &Scenario[i].ClearForBig[3]); break;
			case 34:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d,%d", &Scenario[i].Big[0], &Scenario[i].Big[1]); break;
			case 35:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d", &Scenario[i].NoHold[0]); break;
			case 36:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d,%d,%d,%d", &Scenario[i].Boost[0], &Scenario[i].Boost[1], &Scenario[i].Boost[2], &Scenario[i].Boost[3]); break;
			case 37:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d,%d,%d,%d", &Scenario[i].CopyGarbage[0], &Scenario[i].CopyGarbage[1], &Scenario[i].CopyGarbage[2], &Scenario[i].CopyGarbage[3]); break;
			case 38:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d,%d,%d,%d,%d", &Scenario[i].RandomGarbage[0], &Scenario[i].RandomGarbage[1], &Scenario[i].RandomGarbage[2], &Scenario[i].RandomGarbage[3], &Scenario[i].RandomGarbage[4]); break;
			case 39:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d,%d,%d,%d", &Scenario[i].Shutter[0], &Scenario[i].Shutter[1], &Scenario[i].Shutter[2], &Scenario[i].Shutter[3]); break;
			case 40:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d", &Scenario[i].Shadow[0]); break;
			case 41:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d", &Scenario[i].SuddenAppear[0]); break;
			case 42:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d,%d,%d,%d,%d,%d,%d", &Scenario[i].RandomColor[0], &Scenario[i].RandomColor[1], &Scenario[i].RandomColor[2], &Scenario[i].RandomColor[3], &Scenario[i].RandomColor[4], &Scenario[i].RandomColor[5], &Scenario[i].RandomColor[6]); break;
			case 43:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d,%d,%d,%d,%d,%d,%d", &Scenario[i].Monochrome[0], &Scenario[i].Monochrome[1], &Scenario[i].Monochrome[2], &Scenario[i].Monochrome[3], &Scenario[i].Monochrome[4], &Scenario[i].Monochrome[5], &Scenario[i].Monochrome[6]); break;
			case 44:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d,%d,%d", &Scenario[i].Reverse[0], &Scenario[i].Reverse[1], &Scenario[i].Reverse[2]); break;
			case 45:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d", &Scenario[i].Dark[0], &Scenario[i].Dark[1], &Scenario[i].Dark[2], &Scenario[i].Dark[3], &Scenario[i].Dark[4], &Scenario[i].Dark[5], &Scenario[i].Dark[6], &Scenario[i].Dark[7], &Scenario[i].Dark[8], &Scenario[i].Dark[9], &Scenario[i].Dark[10]); break;
			case 46:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d,%d,%d", &Scenario[i].AlternateHide[0], &Scenario[i].AlternateHide[1], &Scenario[i].AlternateHide[2]); break;
			case 47:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d", &Scenario[i].Snow[0], &Scenario[i].Snow[1], &Scenario[i].Snow[2], &Scenario[i].Snow[3], &Scenario[i].Snow[4], &Scenario[i].Snow[5], &Scenario[i].Snow[6], &Scenario[i].Snow[7], &Scenario[i].Snow[8], &Scenario[i].Snow[9], &Scenario[i].Snow[10], &Scenario[i].Snow[11], &Scenario[i].Snow[12], &Scenario[i].Snow[13], &Scenario[i].Snow[14], &Scenario[i].Snow[15]); break;
			case 48:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d,%d", &Scenario[i].Lift[0], &Scenario[i].Lift[1]); break;
			case 49:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d,%d", &Scenario[i].Press[0], &Scenario[i].Press[1]); break;
			case 50:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d", &Scenario[i].Quake[0], &Scenario[i].Quake[1], &Scenario[i].Quake[2], &Scenario[i].Quake[3], &Scenario[i].Quake[4], &Scenario[i].Quake[5], &Scenario[i].Quake[6], &Scenario[i].Quake[7], &Scenario[i].Quake[8], &Scenario[i].Quake[9]); break;
			case 51:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d,%d,%d,%d,%d,%d,%d,%d", &Scenario[i].BlackOut[0], &Scenario[i].BlackOut[1], &Scenario[i].BlackOut[2], &Scenario[i].BlackOut[3], &Scenario[i].BlackOut[4], &Scenario[i].BlackOut[5], &Scenario[i].BlackOut[6], &Scenario[i].BlackOut[7]); break;
			case 52:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d,%d", &Scenario[i].ZeroGravity[0], &Scenario[i].ZeroGravity[1]); break;
			case 53:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d,%d,%d,%d,%d", &Scenario[i].Clone[0], &Scenario[i].Clone[1], &Scenario[i].Clone[2], &Scenario[i].Clone[3], &Scenario[i].Clone[4]); break;
			case 54:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d,%d,%d,%d", &Scenario[i].Cascade[0], &Scenario[i].Cascade[1], &Scenario[i].Cascade[2], &Scenario[i].Cascade[3]); break;
			case 55:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d,%d,%d,%d", &Scenario[i].DropEffect[0], &Scenario[i].DropEffect[1], &Scenario[i].DropEffect[2], &Scenario[i].DropEffect[3]); break;

			case 65:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
				&Scenario[i].ObstacleFlag[0], &Scenario[i].ObstacleFlag[1], &Scenario[i].ObstacleFlag[2], &Scenario[i].ObstacleFlag[3], &Scenario[i].ObstacleFlag[4],
				&Scenario[i].ObstacleFlag[5], &Scenario[i].ObstacleFlag[6], &Scenario[i].ObstacleFlag[7], &Scenario[i].ObstacleFlag[8], &Scenario[i].ObstacleFlag[9],
				&Scenario[i].ObstacleFlag[10], &Scenario[i].ObstacleFlag[11], &Scenario[i].ObstacleFlag[12], &Scenario[i].ObstacleFlag[13], &Scenario[i].ObstacleFlag[14],
				&Scenario[i].ObstacleFlag[15], &Scenario[i].ObstacleFlag[16], &Scenario[i].ObstacleFlag[17], &Scenario[i].ObstacleFlag[18], &Scenario[i].ObstacleFlag[19],
				&Scenario[i].ObstacleFlag[20], &Scenario[i].ObstacleFlag[21], &Scenario[i].ObstacleFlag[22], &Scenario[i].ObstacleFlag[23], &Scenario[i].ObstacleFlag[24],
				&Scenario[i].ObstacleFlag[25], &Scenario[i].ObstacleFlag[26], &Scenario[i].ObstacleFlag[27], &Scenario[i].ObstacleFlag[28], &Scenario[i].ObstacleFlag[29]); break;
			case 66:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
				&Scenario[i].FirstObstacle[0], &Scenario[i].FirstObstacle[1], &Scenario[i].FirstObstacle[2], &Scenario[i].FirstObstacle[3], &Scenario[i].FirstObstacle[4],
				&Scenario[i].FirstObstacle[5], &Scenario[i].FirstObstacle[6], &Scenario[i].FirstObstacle[7], &Scenario[i].FirstObstacle[8], &Scenario[i].FirstObstacle[9],
				&Scenario[i].FirstObstacle[10], &Scenario[i].FirstObstacle[11], &Scenario[i].FirstObstacle[12], &Scenario[i].FirstObstacle[13], &Scenario[i].FirstObstacle[14],
				&Scenario[i].FirstObstacle[15], &Scenario[i].FirstObstacle[16], &Scenario[i].FirstObstacle[17], &Scenario[i].FirstObstacle[18], &Scenario[i].FirstObstacle[19],
				&Scenario[i].FirstObstacle[20], &Scenario[i].FirstObstacle[21], &Scenario[i].FirstObstacle[22], &Scenario[i].FirstObstacle[23], &Scenario[i].FirstObstacle[24],
				&Scenario[i].FirstObstacle[25], &Scenario[i].FirstObstacle[26], &Scenario[i].FirstObstacle[27], &Scenario[i].FirstObstacle[28], &Scenario[i].FirstObstacle[29]); break;

			case 70:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d", &Scenario[i].NoPause); break;
			case 71:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d,%d,%d,%d,%d", &Scenario[i].LineClearPoint[0], &Scenario[i].LineClearPoint[1], &Scenario[i].LineClearPoint[2], &Scenario[i].LineClearPoint[3], &Scenario[i].LineClearPoint[4]); break;
			case 72:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d,%d,%d,%d", &Scenario[i].BacktoBackPoint[0], &Scenario[i].BacktoBackPoint[1], &Scenario[i].BacktoBackPoint[2], &Scenario[i].BacktoBackPoint[3]); break;
			case 73:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d,%d,%d,%d,%d", &Scenario[i].TSpinPoint[0], &Scenario[i].TSpinPoint[1], &Scenario[i].TSpinPoint[2], &Scenario[i].TSpinPoint[3], &Scenario[i].TSpinPoint[4]); break;
			case 74:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d,%d,%d,%d", &Scenario[i].RenPoint[0], &Scenario[i].RenPoint[1], &Scenario[i].RenPoint[2], &Scenario[i].RenPoint[3]); break;
			case 75:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d,%d,%d,%d,%d", &Scenario[i].Condition[0], &Scenario[i].Condition[1], &Scenario[i].Condition[2], &Scenario[i].Condition[3], &Scenario[i].Condition[4]); break;
			case 76:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d,%d", &Scenario[i].PreliminaryBell[0], &Scenario[i].PreliminaryBell[1]); break;
			case 77:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d", &Scenario[i].LevelUpWaitTime); break;
			case 78:
				memset(PathMerge, 0, sizeof(PathMerge));
				if (subDirFlag){
					strcpy_s(PathMerge, _countof(PathMerge), SubDir);
				}
				strcat_s(PathMerge, Data);
				for (int i = level; i < MIN(level + range, LEVEL_MAX); i++){
					fall = strncpy_s(Scenario[i].InitialFieldPath, _countof(Scenario[i].InitialFieldPath), PathMerge, _countof(Scenario[i].InitialFieldPath) - 1);
				}
				break;
			case 79:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d", &Scenario[i].CascadeRate); break;

			case 80:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d", &Scenario[i].MoveInfMax); break;
			case 81:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d", &Scenario[i].TurnInfMax); break;
			case 82:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d", &Scenario[i].InfDelay); break;
			case 83:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d,%d,%d,%d,%d,%d,%d", &Scenario[i].EmergePos[0][0], &Scenario[i].EmergePos[1][0], &Scenario[i].EmergePos[2][0], &Scenario[i].EmergePos[3][0], &Scenario[i].EmergePos[4][0], &Scenario[i].EmergePos[5][0], &Scenario[i].EmergePos[6][0]); break;
			case 84:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d,%d,%d,%d,%d,%d,%d", &Scenario[i].EmergePos[0][1], &Scenario[i].EmergePos[1][1], &Scenario[i].EmergePos[2][1], &Scenario[i].EmergePos[3][1], &Scenario[i].EmergePos[4][1], &Scenario[i].EmergePos[5][1], &Scenario[i].EmergePos[6][1]); break;
			case 85:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d,%d,%d,%d,%d,%d,%d", &Scenario[i].EmergePos[0][2], &Scenario[i].EmergePos[1][2], &Scenario[i].EmergePos[2][2], &Scenario[i].EmergePos[3][2], &Scenario[i].EmergePos[4][2], &Scenario[i].EmergePos[5][2], &Scenario[i].EmergePos[6][2]); break;
			case 86:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d,%d,%d,%d,%d,%d,%d", &Scenario[i].EmergePos[0][3], &Scenario[i].EmergePos[1][3], &Scenario[i].EmergePos[2][3], &Scenario[i].EmergePos[3][3], &Scenario[i].EmergePos[4][3], &Scenario[i].EmergePos[5][3], &Scenario[i].EmergePos[6][3]); break;
			case 87:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d", &Scenario[i].SmoothDrop); break;
			case 88:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d", &Scenario[i].SoftDropInterval); break;

			case 90:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d"
				, &Scenario[i].HideObstacle[0], &Scenario[i].HideObstacle[1], &Scenario[i].HideObstacle[2], &Scenario[i].HideObstacle[3], &Scenario[i].HideObstacle[4]
				, &Scenario[i].HideObstacle[5], &Scenario[i].HideObstacle[6], &Scenario[i].HideObstacle[7], &Scenario[i].HideObstacle[8], &Scenario[i].HideObstacle[9]
				, &Scenario[i].HideObstacle[10], &Scenario[i].HideObstacle[11], &Scenario[i].HideObstacle[12], &Scenario[i].HideObstacle[13], &Scenario[i].HideObstacle[14]
				, &Scenario[i].HideObstacle[15], &Scenario[i].HideObstacle[16], &Scenario[i].HideObstacle[17], &Scenario[i].HideObstacle[18], &Scenario[i].HideObstacle[19]
				, &Scenario[i].HideObstacle[20], &Scenario[i].HideObstacle[21], &Scenario[i].HideObstacle[22], &Scenario[i].HideObstacle[23], &Scenario[i].HideObstacle[24]
				, &Scenario[i].HideObstacle[25], &Scenario[i].HideObstacle[26], &Scenario[i].HideObstacle[27], &Scenario[i].HideObstacle[28], &Scenario[i].HideObstacle[29]); break;
			case 91:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d,%d,%d,%d,%d,%d,%d", &Scenario[i].HideText[0], &Scenario[i].HideText[1], &Scenario[i].HideText[2], &Scenario[i].HideText[3], &Scenario[i].HideText[4], &Scenario[i].HideText[5], &Scenario[i].HideText[6]); break;
			case 92:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d,%d,%d,%d,%d,%d,%d", &Scenario[i].HideTetrimino[0], &Scenario[i].HideTetrimino[1], &Scenario[i].HideTetrimino[2], &Scenario[i].HideTetrimino[3], &Scenario[i].HideTetrimino[4], &Scenario[i].HideTetrimino[5], &Scenario[i].HideTetrimino[6]); break;
			case 93:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d,%d,%d,%d,%d,%d,%d,%d", &Scenario[i].HideField[0], &Scenario[i].HideField[1], &Scenario[i].HideField[2], &Scenario[i].HideField[3], &Scenario[i].HideField[4], &Scenario[i].HideField[5], &Scenario[i].HideField[6], &Scenario[i].HideField[7]); break;
			case 94:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d,%d,%d", &Scenario[i].HideGage[0], &Scenario[i].HideGage[1], &Scenario[i].HideGage[2]); break;
			case 95:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d,%d,%d", &Scenario[i].HideGhost[0], &Scenario[i].HideGhost[1], &Scenario[i].HideGhost[2]); break;
			case 96:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d", &Scenario[i].HideSurface); break;
			case 97:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d", &Scenario[i].HideHold); break;
			case 98:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d,%d,%d", &Scenario[i].HideNext[0], &Scenario[i].HideNext[1], &Scenario[i].HideNext[2]); break;
			case 99:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d", &Scenario[i].HideExplosion); break;
			case 100:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d,%d,%d", &Scenario[i].HideBack[0], &Scenario[i].HideBack[1], &Scenario[i].HideBack[2]); break;
			case 101:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d,%d", &Scenario[i].HideCurtain[0], &Scenario[i].HideCurtain[1]); break;
			case 102:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d", &Scenario[i].HideFrame); break;

			case 110:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d,%d,%d", &Scenario[i].PauseBright[0], &Scenario[i].PauseBright[1], &Scenario[i].PauseBright[2]); break;
			case 111:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d,%d,%d", &Scenario[i].FieldBright[0], &Scenario[i].FieldBright[1], &Scenario[i].FieldBright[2]); break;
			case 112:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d,%d,%d", &Scenario[i].TetriminoBright[0], &Scenario[i].TetriminoBright[1], &Scenario[i].TetriminoBright[2]); break;
			case 113:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d,%d,%d", &Scenario[i].BlackBackBright[0], &Scenario[i].BlackBackBright[1], &Scenario[i].BlackBackBright[2]); break;
			case 114:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d,%d,%d", &Scenario[i].WhiteBackBright[0], &Scenario[i].WhiteBackBright[1], &Scenario[i].WhiteBackBright[2]); break;
			case 115:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d,%d,%d", &Scenario[i].MaskBackBright[0], &Scenario[i].MaskBackBright[1], &Scenario[i].MaskBackBright[2]); break;
			case 116:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d,%d,%d", &Scenario[i].NextBright[0], &Scenario[i].NextBright[1], &Scenario[i].NextBright[2]); break;
			case 117:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d,%d,%d", &Scenario[i].HoldBright[0], &Scenario[i].HoldBright[1], &Scenario[i].HoldBright[2]); break;
			case 118:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d,%d,%d", &Scenario[i].GhostBright[0], &Scenario[i].GhostBright[1], &Scenario[i].GhostBright[2]); break;
			case 119:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d,%d,%d", &Scenario[i].ExplosionBright[0], &Scenario[i].ExplosionBright[1], &Scenario[i].ExplosionBright[2]); break;

			case 120:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d,%d,%d", &Scenario[i].FlashColor[0], &Scenario[i].FlashColor[1], &Scenario[i].FlashColor[2]); break;
			case 121:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d,%d,%d", &Scenario[i].SurfaceColor[0], &Scenario[i].SurfaceColor[1], &Scenario[i].SurfaceColor[2]); break;
			case 122:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d,%d,%d", &Scenario[i].SnowColor[0], &Scenario[i].SnowColor[1], &Scenario[i].SnowColor[2]); break;

			case 130:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d", &Scenario[i].FlashIntensity); break;
			case 131:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d", &Scenario[i].FlashTime); break;
			case 132:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d", &Scenario[i].FlashDrawMax); break;
			case 133:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d", &Scenario[i].FlashFill); break;
			case 134:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d,%d,%d,%d", &Scenario[i].SurfaceThickness[0], &Scenario[i].SurfaceThickness[1], &Scenario[i].SurfaceThickness[2], &Scenario[i].SurfaceThickness[3]); break;

			case 140:
				fall = sscanf_s(Data, "%d %[^\n]", &pos, Path, sizeof(Path));
				memset(PathMerge, 0, sizeof(PathMerge));
				if (subDirFlag){
					strcpy_s(PathMerge, _countof(PathMerge), SubDir);
				}
				strcat_s(PathMerge, Path);
				strncpy_s(Course.ShapePath[MAX(0, MIN(pos, SHAPE_MAX - 1))], _countof(Course.ShapePath[MAX(0, MIN(pos, SHAPE_MAX - 1))]), PathMerge, _countof(Course.ShapePath[MAX(0, MIN(pos, SHAPE_MAX - 1))]) - 1);
				break;
			case 141:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d", &Scenario[i].ShapeFlag); break;
			case 142:fall = sscanf_s(Data, "%d %[^\n]", &pos, Path, sizeof(Path)); sscanf_s(Path, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
				&Course.ShapeBlackOut[MAX(0, MIN(pos, SHAPE_MAX - 1))][0][0], &Course.ShapeBlackOut[MAX(0, MIN(pos, SHAPE_MAX - 1))][1][0],
				&Course.ShapeBlackOut[MAX(0, MIN(pos, SHAPE_MAX - 1))][0][1], &Course.ShapeBlackOut[MAX(0, MIN(pos, SHAPE_MAX - 1))][1][1],
				&Course.ShapeBlackOut[MAX(0, MIN(pos, SHAPE_MAX - 1))][0][2], &Course.ShapeBlackOut[MAX(0, MIN(pos, SHAPE_MAX - 1))][1][2],
				&Course.ShapeBlackOut[MAX(0, MIN(pos, SHAPE_MAX - 1))][0][3], &Course.ShapeBlackOut[MAX(0, MIN(pos, SHAPE_MAX - 1))][1][3],
				&Course.ShapeBlackOut[MAX(0, MIN(pos, SHAPE_MAX - 1))][0][4], &Course.ShapeBlackOut[MAX(0, MIN(pos, SHAPE_MAX - 1))][1][4],
				&Course.ShapeBlackOut[MAX(0, MIN(pos, SHAPE_MAX - 1))][0][5], &Course.ShapeBlackOut[MAX(0, MIN(pos, SHAPE_MAX - 1))][1][5],
				&Course.ShapeBlackOut[MAX(0, MIN(pos, SHAPE_MAX - 1))][0][6], &Course.ShapeBlackOut[MAX(0, MIN(pos, SHAPE_MAX - 1))][1][6]); break;
			case 143:fall = sscanf_s(Data, "%d %[^\n]", &pos, Path, sizeof(Path)); sscanf_s(Path, "%d,%d,%d", &Course.ShapeTSpinInfo[MAX(0, MIN(pos, SHAPE_MAX - 1))][0], &Course.ShapeTSpinInfo[MAX(0, MIN(pos, SHAPE_MAX - 1))][1], &Course.ShapeTSpinInfo[MAX(0, MIN(pos, SHAPE_MAX - 1))][2]); break;
			case 144:fall = sscanf_s(Data, "%d %[^\n]", &pos, Path, sizeof(Path)); sscanf_s(Path, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
				&Course.ShapeTSpinPoint[MAX(0, MIN(pos, SHAPE_MAX - 1))][0][0][0], &Course.ShapeTSpinPoint[MAX(0, MIN(pos, SHAPE_MAX - 1))][0][0][1],
				&Course.ShapeTSpinPoint[MAX(0, MIN(pos, SHAPE_MAX - 1))][0][1][0], &Course.ShapeTSpinPoint[MAX(0, MIN(pos, SHAPE_MAX - 1))][0][1][1],
				&Course.ShapeTSpinPoint[MAX(0, MIN(pos, SHAPE_MAX - 1))][0][2][0], &Course.ShapeTSpinPoint[MAX(0, MIN(pos, SHAPE_MAX - 1))][0][2][1],
				&Course.ShapeTSpinPoint[MAX(0, MIN(pos, SHAPE_MAX - 1))][0][3][0], &Course.ShapeTSpinPoint[MAX(0, MIN(pos, SHAPE_MAX - 1))][0][3][1],
				&Course.ShapeTSpinPoint[MAX(0, MIN(pos, SHAPE_MAX - 1))][1][0][0], &Course.ShapeTSpinPoint[MAX(0, MIN(pos, SHAPE_MAX - 1))][1][0][1],
				&Course.ShapeTSpinPoint[MAX(0, MIN(pos, SHAPE_MAX - 1))][1][1][0], &Course.ShapeTSpinPoint[MAX(0, MIN(pos, SHAPE_MAX - 1))][1][1][1],
				&Course.ShapeTSpinPoint[MAX(0, MIN(pos, SHAPE_MAX - 1))][1][2][0], &Course.ShapeTSpinPoint[MAX(0, MIN(pos, SHAPE_MAX - 1))][1][2][1],
				&Course.ShapeTSpinPoint[MAX(0, MIN(pos, SHAPE_MAX - 1))][1][3][0], &Course.ShapeTSpinPoint[MAX(0, MIN(pos, SHAPE_MAX - 1))][1][3][1],
				&Course.ShapeTSpinPoint[MAX(0, MIN(pos, SHAPE_MAX - 1))][2][0][0], &Course.ShapeTSpinPoint[MAX(0, MIN(pos, SHAPE_MAX - 1))][2][0][1],
				&Course.ShapeTSpinPoint[MAX(0, MIN(pos, SHAPE_MAX - 1))][2][1][0], &Course.ShapeTSpinPoint[MAX(0, MIN(pos, SHAPE_MAX - 1))][2][1][1],
				&Course.ShapeTSpinPoint[MAX(0, MIN(pos, SHAPE_MAX - 1))][2][2][0], &Course.ShapeTSpinPoint[MAX(0, MIN(pos, SHAPE_MAX - 1))][2][2][1],
				&Course.ShapeTSpinPoint[MAX(0, MIN(pos, SHAPE_MAX - 1))][2][3][0], &Course.ShapeTSpinPoint[MAX(0, MIN(pos, SHAPE_MAX - 1))][2][3][1],
				&Course.ShapeTSpinPoint[MAX(0, MIN(pos, SHAPE_MAX - 1))][3][0][0], &Course.ShapeTSpinPoint[MAX(0, MIN(pos, SHAPE_MAX - 1))][3][0][1],
				&Course.ShapeTSpinPoint[MAX(0, MIN(pos, SHAPE_MAX - 1))][3][1][0], &Course.ShapeTSpinPoint[MAX(0, MIN(pos, SHAPE_MAX - 1))][3][1][1],
				&Course.ShapeTSpinPoint[MAX(0, MIN(pos, SHAPE_MAX - 1))][3][2][0], &Course.ShapeTSpinPoint[MAX(0, MIN(pos, SHAPE_MAX - 1))][3][2][1],
				&Course.ShapeTSpinPoint[MAX(0, MIN(pos, SHAPE_MAX - 1))][3][3][0], &Course.ShapeTSpinPoint[MAX(0, MIN(pos, SHAPE_MAX - 1))][3][3][1]); break;
			case 145:fall = sscanf_s(Data, "%d %[^\n]", &pos, Path, sizeof(Path)); sscanf_s(Path, "%d,%d,%d,%d,%d,%d,%d,%d",
				&Course.ShapeTSpinMini[MAX(0, MIN(pos, SHAPE_MAX - 1))][0][0], &Course.ShapeTSpinMini[MAX(0, MIN(pos, SHAPE_MAX - 1))][0][1],
				&Course.ShapeTSpinMini[MAX(0, MIN(pos, SHAPE_MAX - 1))][1][0], &Course.ShapeTSpinMini[MAX(0, MIN(pos, SHAPE_MAX - 1))][1][1],
				&Course.ShapeTSpinMini[MAX(0, MIN(pos, SHAPE_MAX - 1))][2][0], &Course.ShapeTSpinMini[MAX(0, MIN(pos, SHAPE_MAX - 1))][2][1],
				&Course.ShapeTSpinMini[MAX(0, MIN(pos, SHAPE_MAX - 1))][3][0], &Course.ShapeTSpinMini[MAX(0, MIN(pos, SHAPE_MAX - 1))][3][1]); break;

			case 150:
				fall = sscanf_s(Data, "%d %[^\n]", &pos, Path, sizeof(Path));
				memset(PathMerge, 0, sizeof(PathMerge));
				if (subDirFlag){
					strcpy_s(PathMerge, _countof(PathMerge), SubDir);
				}
				strcat_s(PathMerge, Path);
				strncpy_s(Course.RotationPath[MAX(0, MIN(pos, ROTATION_MAX - 1))], _countof(Course.RotationPath[MAX(0, MIN(pos, ROTATION_MAX - 1))]), PathMerge, _countof(Course.RotationPath[MAX(0, MIN(pos, ROTATION_MAX - 1))]) - 1);
				break;
			case 151:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d,%d,%d,%d,%d,%d,%d", &Scenario[i].RotationType[0], &Scenario[i].RotationType[1], &Scenario[i].RotationType[2], &Scenario[i].RotationType[3], &Scenario[i].RotationType[4], &Scenario[i].RotationType[5], &Scenario[i].RotationType[6]); break;
			case 152:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d", &Scenario[i].RotationFlag); break;

			case 160:
				fall = sscanf_s(Data, "%d %[^\n]", &pos, Path, sizeof(Path));
				memset(PathMerge, 0, sizeof(PathMerge));
				if (subDirFlag){
					strcpy_s(PathMerge, _countof(PathMerge), SubDir);
				}
				strcat_s(PathMerge, Path);
				strncpy_s(Course.BgmPath[MAX(0, MIN(pos, BGM_MAX - 1))], _countof(Course.BgmPath[MAX(0, MIN(pos, BGM_MAX - 1))]), PathMerge, _countof(Course.BgmPath[MAX(0, MIN(pos, BGM_MAX - 1))]) - 1);
				break;
			case 161:fall = sscanf_s(Data, "%d %[^\n]", &pos, Path, sizeof(Path)); sscanf_s(Path, "%d,%d", &Course.BgmLoopPoint[MAX(0, MIN(pos, BGM_MAX - 1))], &Course.BgmVolume[MAX(0, MIN(pos, BGM_MAX - 1))]); break;
			case 162:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d", &Scenario[i].BgmFlag); break;

			case 170:
				fall = sscanf_s(Data, "%d %[^\n]", &pos, Path, sizeof(Path));
				memset(PathMerge, 0, sizeof(PathMerge));
				if (subDirFlag){
					strcpy_s(PathMerge, _countof(PathMerge), SubDir);
				}
				strcat_s(PathMerge, Path);
				strncpy_s(Course.LayerPath[MAX(0, MIN(pos, Layer.MAX - 1))], _countof(Course.LayerPath[MAX(0, MIN(pos, Layer.MAX - 1))]), PathMerge, _countof(Course.LayerPath[MAX(0, MIN(pos, Layer.MAX - 1))]) - 1);
				break;
			case 171:fall = sscanf_s(Data, "%d %[^\n]", &pos, Path, sizeof(Path));
				pos = MAX(0, MIN(pos, Layer.MAX - 1));
				Layer.LoadInfo_Draw(pos, Path);
				break;
			case 172:fall = sscanf_s(Data, "%d %[^\n]", &pos, Path, sizeof(Path));
				pos = MAX(0, MIN(pos, Layer.MAX - 1));
				Layer.LoadInfo_XY(pos, Path);
				break;
			case 173:fall = sscanf_s(Data, "%d %[^\n]", &pos, Path, sizeof(Path));
				pos = MAX(0, MIN(pos, Layer.MAX - 1));
				Layer.LoadInfo_Rota(pos, Path);
				break;
			case 174:fall = sscanf_s(Data, "%d %[^\n]", &pos, Path, sizeof(Path));
				pos = MAX(0, MIN(pos, Layer.MAX - 1));
				Layer.LoadInfo_Act(pos, Path);
				break;
			case 175:fall = sscanf_s(Data, "%d %[^\n]", &pos, Path, sizeof(Path));
				pos = MAX(0, MIN(pos, Layer.MAX - 1));
				Layer.LoadInfo_Limit(pos, Path);
				break;
			case 176:do{
						 int source = -1, target[10] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
						 fall = sscanf_s(Data, "%d %d,%d,%d,%d,%d,%d,%d,%d,%d,%d", &source, &target[0], &target[1], &target[2], &target[3], &target[4], &target[5], &target[6], &target[7], &target[8], &target[9]);
						 for (int j = 0; j < 10; j++){
							 if (target[j] >= 0 && target[j] < Layer.MAX){
								 Course.CopyLayerPath[target[j]] = source;
							 }
						 }
			} while (0);
				break;
			case 177:do{
						 int source = -1, target[10] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
						 fall = sscanf_s(Data, "%d %d,%d,%d,%d,%d,%d,%d,%d,%d,%d", &source, &target[0], &target[1], &target[2], &target[3], &target[4], &target[5], &target[6], &target[7], &target[8], &target[9]);
						 if (source >= 0 && source < Layer.MAX){
							 for (int j = 0; j < 10; j++){
								 if (target[j] >= 0 && target[j] < Layer.MAX){
									 Layer.CopyInfo(source, target[j]);
								 }
							 }
						 }
			} while (0);
				break;
			case 178:do{
						 int target[10] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
						 fall = sscanf_s(Data, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d", &target[0], &target[1], &target[2], &target[3], &target[4], &target[5], &target[6], &target[7], &target[8], &target[9]);
						 for (int i = level; i < MIN(level + range, LEVEL_MAX); i++){
							 for (int j = 0; j < 10; j++){
								 if (target[j] >= 0 && target[j] < Layer.MAX)Scenario[i].LayerFlag[target[j]] = 1;
							 }
						 }
			} while (0);
				break;
			case 179:do{
						 int target[10] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
						 fall = sscanf_s(Data, "%d,%d", &target[0], &target[1]);
						 for (int i = level; i < MIN(level + range, LEVEL_MAX); i++){
							 if (target[0] >= 0 && target[0] < Layer.MAX&&target[1] >= 0 && target[1] < Layer.MAX){
								 for (int j = target[0]; j <= target[1]; j++){
									 Scenario[i].LayerFlag[j] = 1;
								 }
							 }
						 }
			} while (0);
				break;

			case 180:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d", &Scenario[i].ScoreBase); break;
			case 181:do{
						 int operand[2] = { 0 };
						 fall = sscanf_s(Data, "%d,%d", &operand[0], &operand[1]);
						 switch (operand[0]){
						 case 0:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)Scenario[i].ScoreBase = operand[1]; break;
						 case 1:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)Scenario[i].ScoreBase += operand[1]; break;
						 case 2:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)Scenario[i].ScoreBase -= operand[1]; break;
						 case 3:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)Scenario[i].ScoreBase *= operand[1]; break;
						 case 4:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)Scenario[i].ScoreBase /= operand[1]; break;
						 case 5:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)Scenario[i].ScoreBase %= operand[1]; break;
						 }
			} while (0);
				break;
			case 182:do{
						 int operand[4] = { 0 };
						 fall = sscanf_s(Data, "%d,%d,%d", &operand[0], &operand[1], &operand[2]);
						 for (int i = level; i < MIN(level + range, LEVEL_MAX); i++){
							 switch (operand[1]){
							 case 1:operand[3] = i + operand[2]; break;
							 case 2:operand[3] = i - operand[2]; break;
							 case 3:operand[3] = i*operand[2]; break;
							 case 4:operand[3] = i / operand[2]; break;
							 case 5:operand[3] = i%operand[2]; break;
							 default:operand[3] = 0;
							 }
							 switch (operand[0]){
							 case 0:Scenario[i].ScoreBase = operand[3]; break;
							 case 1:Scenario[i].ScoreBase += operand[3]; break;
							 case 2:Scenario[i].ScoreBase -= operand[3]; break;
							 case 3:Scenario[i].ScoreBase *= operand[3]; break;
							 case 4:Scenario[i].ScoreBase /= operand[3]; break;
							 case 5:Scenario[i].ScoreBase %= operand[3]; break;
							 }
						 }
			} while (0);
				break;
			case 183:for (int i = level; i < MIN(level + range, LEVEL_MAX); i++)fall = sscanf_s(Data, "%d,%d,%d", &Scenario[i].BackBlackNum, &Scenario[i].BackWhiteNum, &Scenario[i].BackMaskNum); break;
			case 184:do{
						 int operand[3] = { 0 };
						 fall = sscanf_s(Data, "%d,%d,%d", &operand[0], &operand[1], &operand[2]);
						 for (int i = level; i < MIN(level + range, LEVEL_MAX); i++){
							 Scenario[i].BackBlackNum += operand[0];
							 Scenario[i].BackWhiteNum += operand[1];
							 Scenario[i].BackMaskNum += operand[2];
						 }
			} while (0);
				break;
			case 185:do{
						 int target[10] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
						 fall = sscanf_s(Data, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d", &target[0], &target[1], &target[2], &target[3], &target[4], &target[5], &target[6], &target[7], &target[8], &target[9]);
						 for (int i = level; i < MIN(level + range, LEVEL_MAX); i++){
							 for (int j = 0; j < 10; j++){
								 if (target[j] >= 0 && target[j] < IF_MAX)Scenario[i].IfFlag[target[j]] = 1;
							 }
						 }
			} while (0);
				break;

			case 190:fall = sscanf_s(Data, "%d", &returnstate); break;
			case 191:fall = sscanf_s(Data, "%d", &level); break;
			case 192:fall = sscanf_s(Data, "%d", &range); break;
			case 193:fall = sscanf_s(Data, "%d", &jump); break;
			case 194:fall = sscanf_s(Data, "%d", &jumpstate); break;
			case 195:fall = sscanf_s(Data, "%d", &showerrorrow); break;
			case 196:do{
						 char BoardString[5][16] = { 0 }, SignString[5][16] = { 0 };
						 sscanf_s(Data, "%d %[^\n]", &pos, Path, sizeof(Path));
						 pos = MAX(0, MIN(pos, IF_MAX - 1));
						 fall = sscanf_s(Path, "%s %s %d && %s %s %d && %s %s %d && %s %s %d && %s %s %d",
							 BoardString[0], sizeof(BoardString[0]), SignString[0], sizeof(SignString[0]), &Course.IfCondition[pos][2],
							 BoardString[1], sizeof(BoardString[1]), SignString[1], sizeof(SignString[1]), &Course.IfCondition[pos][5],
							 BoardString[2], sizeof(BoardString[2]), SignString[2], sizeof(SignString[2]), &Course.IfCondition[pos][8],
							 BoardString[3], sizeof(BoardString[3]), SignString[3], sizeof(SignString[3]), &Course.IfCondition[pos][11],
							 BoardString[4], sizeof(BoardString[4]), SignString[4], sizeof(SignString[4]), &Course.IfCondition[pos][14]);
						 for (int j = 0; j < 5 && BoardString[j][0] != '\0'; j++)Course.IfCondition[pos][j * 3] = BoardAllotment(BoardString[j]);
						 for (int j = 0; j < 5 && SignString[j][0] != '\0'; j++)Course.IfCondition[pos][j * 3 + 1] = SignAllotment(SignString[j]);
						 Course.IfPointer[pos] = (int)FileRead_tell(fp);
						 //Course.IfTermControl[pos][0] = returnstate;
						 //Course.IfTermControl[pos][1] = level;
						 //Course.IfTermControl[pos][2] = range;
						 //Course.IfTermControl[pos][3] = jump;
						 readable = 0;
			} while (0);
				break;
			case 197:fall = sscanf_s(Data, "%d", &subDirFlag);
				break;
			case 198:do{
						 int source = -1, target[10] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
						 fall = sscanf_s(Data, "%d %d,%d,%d,%d,%d,%d,%d,%d,%d,%d", &source, &target[0], &target[1], &target[2], &target[3], &target[4], &target[5], &target[6], &target[7], &target[8], &target[9]);
						 if (source >= 0 && source < LEVEL_MAX){
							 for (int j = 0; j < 10; j++){
								 if (target[j] >= 0 && target[j] < LEVEL_MAX)memcpy_s(&Scenario[target[j]], sizeof(Scenario_t), &Scenario[source], sizeof(Scenario_t));
							 }
						 }
			} while (0);
				break;
			case 199:fall = sscanf_s(Data, "%d", &state); break;
			}
			if (state == jumpstate)level += jump;
			if (returnstate >= 0)state = returnstate;
		}
		if (showerrorrow&&fall == EOF&&errors < 40){
			Course.ErrorRow[errors] = row;
			errors++;
		}
		row++;
	}
	if (IfNum < 0 || IfNum >= IF_MAX){
		Progress.ClearBaseScore = 0;
		Progress.ClearBaseTime = 0;
		for (int i = 0; i < level; i++){
			Progress.ClearBaseScore += (Scenario[i].ScoreBase*Scenario[i].PointMax);
			Progress.ClearBaseTime += Scenario[i].TargetTime;
		}
	}
	FileRead_close(fp);
	return MIN(LEVEL_MAX - 1, level - 1);
}

void SetDefaultCourseData(){
	memset(&D_Course,0,sizeof(Course_t));
	memset(D_Scenario,0,sizeof(Scenario_t)*LEVEL_MAX);
	memset(D_Course.IfCondition,-1,sizeof(D_Course.IfCondition));
	memset(D_Course.CopyLayerPath,-1,sizeof(D_Course.CopyLayerPath));
	for(int i=0;i<15;i++)D_Scenario[0].LevelUpCondition[i]=-1;
	LoadCourse("dat/archive/default.fldn",-1);
	memcpy_s(&D_Course,sizeof(Course_t),&Course,sizeof(Course_t));
	memcpy_s(D_Scenario,sizeof(Scenario_t)*LEVEL_MAX,Scenario,sizeof(Scenario_t)*LEVEL_MAX);
}