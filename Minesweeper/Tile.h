#pragma once
#include <Windows.h>
#include <FL/Fl.h>
#include <FL/Fl_Window.h>
#include <FL/Fl_Box.h>
#include <FL/Fl_JPEG_Image.H>
#include <FL/Fl_Button.H>
#include <vector>
#include <string>

class Tile : public Fl_Button {

	

public:
	Tile(int x, int y, int w, int h, int xpos, int ypos, bool hasMine = false);
	int handle(int event);
	void placeBomb(bool has);
	void debugMine();
	Fl_JPEG_Image* changePic();
	void reset();
	bool haveMine();
	void incBombCnt(int bombs);
	int getRow();
	int getCol();
	int getClicks();
	void clearTile();
	bool getCovered();
	bool getDebugM();
	int getBombsNear();
	bool flagged();
	bool questioned();
	std::string clickT();
	void setFlag();
	void updateLost();
	void incFlags(int flags);
	int getFlagsNear();
	void setPlaying(bool c);

private:
	std::string click;
	int flagsNear;
	static bool playing;
	int row;
	int col;
	static int totalClicks;
	static bool debugM;
	int bombsNear;
	bool debug;
	bool covered;
	bool gameLost;
	bool hasFlag = false;
	bool hasQuestion = false;
	bool hasMine;
	std::vector <Fl_JPEG_Image*> pics;




};