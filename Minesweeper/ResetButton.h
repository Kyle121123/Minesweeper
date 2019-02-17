#pragma once
#include <Windows.h>
#include <FL/Fl.h>
#include <FL/Fl_Window.h>
#include <FL/Fl_Box.h>
#include <FL/Fl_Button.H>
#include "Tile.h"
#include <iostream>



class ResetButton :public Fl_Button {
public:
	ResetButton(int x, int y);
	int handle(int event);
	void updateImg(bool t);
private:







};







