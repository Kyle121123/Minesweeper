#pragma once
#include <Windows.h>
#include <FL/Fl.h>
#include <FL/Fl_Window.h>

#include <ctime>

#include <FL/Fl_Box.h>
#include <FL/Fl_Button.H>
#include "Tile.h"
#include <iostream>


class Timer : public Fl_Box {
public:
	Timer(int x, int y, int w, int h);
	bool hasStartedT();
	void setStartedT(bool con);
	void reset();
	bool stopTime();
	void setStopTime(bool t);
	
private:
	bool startedT;
	bool stop;
};