#ifndef ANIMATION_H
#define ANIMATION_H

typedef struct{
	double X,Y,Sp,R;
	int VA;
}Blossom_t;

typedef struct{
	double X,Y,Sp,Ang,VA,VVA,VS,VVS,R;
	int Count;
}Firefly_t;

typedef struct{
	double X,Y,VX,VY,R,TargetY;
	int Flag;
}Water_t;

typedef struct{
	double X,Y,Ang,R,Dir,Sp;
	int Clock;
}Bubble_t;

typedef struct{
	double X,Y,VX,VXMax,VXMin,R,Drag;
	int Type;
}Fish_t;

typedef struct{
	double X,Y,Sp,Ang,R,VA,FlapSp;
	int Count,LapCount;
}Dragonfly_t;

typedef struct{
	double X,Y,R,Sp,Ang,Dir,Turn;
	int Type,Clock;
}Leaf_t;

typedef struct{
	double X,Y,Sp,Ang,VA,VVA,R,VR,Target;
	int Flag,Turn;
}Fire_t;

typedef struct{
	double X,Y,Sp,Ang,R;
	int VA,Dir,Type;
}Ice_t;

typedef struct{
	double X,Y,Length,Width,VL,VW,Ang;
	int Flag,Count,Target,State,TargetState;
}Twig_t;

typedef struct{
	double X,Y,R,VR,Ang;
	int Flag,Turn;
}Bud_t;

class CAnimation{
public:
	CAnimation();
	~CAnimation();
	static const int BLOSSOM_MAX	= 10;
	static const int FIREFLY_MAX	= 20;
	static const int WATER_MAX		= 50;
	static const int BUBBLE_MAX		= 12;
	static const int FISH_MAX		= 6;
	static const int DRAGONFLY_MAX	= 8;
	static const int LEAF_MAX		= 12;
	static const int FIRE_MAX		= 40;
	static const int ICE_MAX		= 10;
	static const int TWIG_MAX		= 40;
	static const int BUD_MAX		= 15;
	static const int IMAGE_MAX		= 5;
	void Initialize();
	int Load(int Type);
	void Draw(int Type);
private:
	Blossom_t Blossom[BLOSSOM_MAX];
	Firefly_t Firefly[FIREFLY_MAX];
	Water_t Water[WATER_MAX];
	Bubble_t Bubble[BUBBLE_MAX];
	Fish_t Fish[FISH_MAX];
	Leaf_t Leaf[LEAF_MAX];
	Dragonfly_t Dragonfly[DRAGONFLY_MAX];
	Fire_t Fire[FIRE_MAX];
	Ice_t Ice[ICE_MAX];
	Twig_t Twig[TWIG_MAX];
	Bud_t Bud[BUD_MAX];
	int Image[IMAGE_MAX];
	int PlayingType;
	int TimeLine;
	void CalcWater(int cnt);
	void BlossomInitialize();
	void FireflyInitialize();
	void WaterInitialize();
	void SeaInitialize();
	void DragonflyInitialize();
	void LeafInitialize();
	void FireInitialize();
	void IceInitialize();
	void TreeInitialize();
	void DrawWheel();
	void DrawBlossom();
	void DrawFirefly();
	void DrawWater();
	void DrawSea();
	void DrawDragonfly();
	void DrawLeaf();
	void DrawFire();
	void DrawIce();
	void DrawTree();
};

extern CAnimation Animation;

#endif