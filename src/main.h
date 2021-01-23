#ifndef MAIN_H
#define MAIN_H

enum {
	KC_DECIDE,
	KC_CANCEL,
	KC_UP,
	KC_RIGHT,
	KC_DOWN,
	KC_LEFT,
	KC_LTURN_1,
	KC_LTURN_2,
	KC_RTURN_1,
	KC_RTURN_2,
	KC_HOLD,
	KC_MDROP,
	KC_HDROP,
	KC_ESCAPE,
	KC_SCREENSHOT
};

extern int MainFlag;
extern int MainPauseFlag;

#endif