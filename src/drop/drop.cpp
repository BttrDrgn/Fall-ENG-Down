#include <cmath>
#include <DxLib.h>
#include <drop/drop.h>

const double PI = 3.1415926535897931;
const double PI2 = 6.2831853071795862;
const double ROOT2 = 1.4142135623730951;

CDrop::CDrop(){

}

CDrop::~CDrop(){
	
}

void CDrop::Initialize(){
	CDrop::graph[1][0] = LoadGraph("dat/img/drop_01_0.png");
	CDrop::graph[2][0] = LoadGraph("dat/img/drop_02_0.png");
	CDrop::graph[3][0] = LoadGraph("dat/img/drop_03_0.png");
	CDrop::graph[3][1] = LoadGraph("dat/img/drop_03_1.png");
	CDrop::graph[4][0] = LoadGraph("dat/img/drop_04_0.png");
	CDrop::graph[4][1] = LoadGraph("dat/img/drop_04_1.png");
	CDrop::graph[5][0] = LoadGraph("dat/img/drop_05_0.png");
	CDrop::graph[5][1] = LoadGraph("dat/img/drop_05_1.png");
	CDrop::graph[5][2] = LoadGraph("dat/img/drop_05_2.png");
	CDrop::graph[6][0] = LoadGraph("dat/img/drop_06_0.png");
	CDrop::graph[6][1] = LoadGraph("dat/img/drop_06_1.png");
	CDrop::graph[6][2] = LoadGraph("dat/img/drop_06_2.png");
	CDrop::graph[7][0] = LoadGraph("dat/img/drop_07_0.png");
	CDrop::graph[7][1] = LoadGraph("dat/img/drop_07_1.png");
	CDrop::graph[7][2] = LoadGraph("dat/img/drop_07_2.png");
	CDrop::graph[8][0] = LoadGraph("dat/img/drop_08_0.png");
	CDrop::graph[8][1] = LoadGraph("dat/img/drop_08_1.png");
	CDrop::graph[8][2] = LoadGraph("dat/img/drop_08_2.png");
	progress = 0;
	for (int i = 0; i < 100; i += 1){
		CDrop::flag[i] = 0;
		CDrop::pattern[i] = 0;
		CDrop::patternChild[i] = 0;
		CDrop::count[i] = 0.0;
		CDrop::x[i] = 0.0;
		CDrop::y[i] = 0.0;
		CDrop::gAngle[i] = 0.0;
		CDrop::vAngle[i] = 0.0;
		CDrop::gSpeed[i] = 0.0;
		CDrop::vSpeed[i] = 0.0;
		CDrop::exRate[i] = 0.0;
	}
}

void CDrop::Draw(int pattern, int amount, double size, double speed, double x1, double y1, double x2, double y2){
	CDrop::progress += amount;
	while (CDrop::progress >= 10000){
		if (pattern < 0 || pattern > 8){
			pattern = 0;
		}
		CDrop::progress -= 10000;
		for (int i = 0; i < 100; i += 1){
			if (CDrop::flag[i] == 0){
				CDrop::flag[i] = 1;
				CDrop::pattern[i] = pattern;
				if (pattern == 3 || pattern == 4){
					CDrop::patternChild[i] = GetRand(1);
				}
				else if (pattern >= 5 && pattern <= 8){
					CDrop::patternChild[i] = GetRand(2);
				}
				else {
					CDrop::patternChild[i] = 0;
				}
				CDrop::exRate[i] = size * (0.85 + 0.3 * GetRand(10000) / 10000.0);
				if (pattern >= 1 && pattern <= 6){
					CDrop::x[i] = x1 + (x2 - x1) * GetRand(10000) / 10000.0;
					if (pattern == 6){
						CDrop::y[i] = y2 + 400.0 * size;
					}
					else {
						CDrop::y[i] = y1 - 400.0 * size;
					}
					if (pattern == 1 || pattern == 6){
						CDrop::gAngle[i] = 0.0;
						CDrop::gSpeed[i] = 0.0;
					}
					else {
						CDrop::gAngle[i] = PI * 2.0 * GetRand(10000) / 10000.0;
						CDrop::gSpeed[i] = PI / 100.0 * speed * (-1.0 + 2.0 * GetRand(10000) / 10000.0);
					}
					if (pattern == 6){
						CDrop::vAngle[i] = PI + PI / 2.0;
					}
					else {
						CDrop::vAngle[i] = PI / 2.0;
					}
				}
				else {
					if (pattern == 7){
						CDrop::x[i] = x2 + 400.0 * size;
						CDrop::vAngle[i] = PI;
					}
					else if (pattern == 8){
						CDrop::x[i] = x1 - 400.0 * size;
						CDrop::vAngle[i] = 0.0;
					}
					CDrop::y[i] = y1 + (y2 - y1) * GetRand(10000) / 10000.0;
					CDrop::gAngle[i] = 0.0;
					CDrop::gSpeed[i] = 0.0;
				}
				CDrop::vSpeed[i] = speed * (0.8 + 0.4 * GetRand(10000) / 10000.0);
				i = 100;
			}
		}
	}
	for (int i = 0; i < 100; i += 1){
		if (CDrop::flag[i] == 1){
			CDrop::count[i] += CDrop::vSpeed[i];
			if (CDrop::pattern[i] == 6){
				double temp = sin(CDrop::count[i] * 0.025) * PI / 5.0;
				CDrop::vAngle[i] = PI + PI / 2.0 + temp;
				CDrop::gAngle[i] = temp;
			}
			else if (CDrop::pattern[i] == 8){
				double temp = sin(CDrop::count[i] * 0.025) * PI / 5.0;
				CDrop::vAngle[i] = temp;
				CDrop::gAngle[i] = temp;
			}
			CDrop::x[i] += cos(CDrop::vAngle[i]) * CDrop::vSpeed[i];
			CDrop::y[i] += sin(CDrop::vAngle[i]) * CDrop::vSpeed[i];
			CDrop::gAngle[i] += CDrop::gSpeed[i];
			if (CDrop::y[i] < 0.0 - 500.0 * size || CDrop::y[i] > 480.0 + 500.0 * size || CDrop::x[i] < 0.0 - 500.0 * size || CDrop::x[i] > 640.0 + 500.0 * size){
				CDrop::flag[i] = 0;
			}
			else {
				DrawRotaGraphF((float)CDrop::x[i], (float)CDrop::y[i], CDrop::exRate[i], CDrop::gAngle[i], CDrop::graph[CDrop::pattern[i]][CDrop::patternChild[i]], TRUE);
			}
		}
	}
}