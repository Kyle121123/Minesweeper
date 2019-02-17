#pragma once
#include <Windows.h>
#include <FL/Fl.h>
#include <FL/Fl_Window.h>
#include <FL/Fl_Button.H>
#include <iostream>
#include <time.h>
#include <vector>
#include <string>
#include <FL/Fl_Input.H>

#include "Game.h"
#include <FL/Fl_Menu_Bar.H>

#include "ResetButton.h"
#include "Tile.h"
class CustomGame : public Fl_Window{
public:
	int getW();
	int getH();
	int getB();
	CustomGame();
	int handle(int event);

private:
	Fl_Input* inputW;
	Fl_Input* inputH;
	Fl_Input* inputB;
	Fl_Button* but;



};
