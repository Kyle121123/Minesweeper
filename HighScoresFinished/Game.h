#pragma once
#include <Windows.h>
#include <FL/Fl.h>
#include <FL/Fl_Window.h>
#include <FL/Fl_Button.H>
#include <iostream>
#include <time.h>
#include <vector>
#include <string>
#include "Tile.h"
#include "Timer.h"
#include "ResetButton.h"

class Game : public Fl_Window {
public:
	Game(int sizeW, int sizeH,int bombCnt,std::string d);
	void setBombs();
	void initBoard();
	//int handle(int event);
	void debugTiles();
	void resetBombs();
	void setNumNear();
	void setStartingTile(int x);
	int boardSizeW;
	int boardSizeH;
	bool hasStarted();
	void setStarted(bool s);
	void cascade(Tile* t);
	void resetTimer();
	int getFlags();
	Fl_Box* bombs;
	bool contains(std::vector<int> v , int n);
	void getWon();
	void getLost(Tile* t);
	void zeroTimer();
	void clearAdjacent(Tile* tile);
	void readTimes();
	void writeTimes();
	void calculateScore();
	int fastestTimes[3][5];
private:
	int startingTile;
	int bombsLeft;
	ResetButton* rb;
	bool started;
	Timer* timer;
	std::string difficulty;
	
	std::vector<std::vector<Tile*> > tiles;
	int bombCnt;
	


};


