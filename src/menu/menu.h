#ifndef MENU_H
#define MENU_H

extern char FLDN_FileName[256];
extern int SelectLevel;
extern int SelectOption;
extern int SelectPage;

extern int GameSelect();
extern int BackViewing();
extern int GameReady();
extern void GameConfiguration();
extern void GameCareer();
extern void GameKeyConfig();
extern int GamePause();

#endif