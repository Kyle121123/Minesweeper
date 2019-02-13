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
#include"customGame.h"




void cb(Fl_Widget* w, void* v) {
	CustomGame* cg = static_cast<CustomGame*>(v);
	Fl_Button* b = static_cast<Fl_Button*>(w);
	if (w->label() == "Enter") {
		Game* custom = new Game(cg->getH(), cg->getW(), cg->getB(),"custom");
		custom->show();
		//cg->hide();
	}
	
}

CustomGame::CustomGame() : Fl_Window(0, 0, 200, 200, "Input") {
	
	inputW = new Fl_Input(50, 10, 120, 25, "Width:");
	inputH = new Fl_Input(50, 60, 120, 25, "Height:");
	inputB = new Fl_Input(50, 110, 120, 25, "Bombs:");
	but = new Fl_Button(50, 150, 100, 40, "Enter");
	but->callback(cb, static_cast<void*>(this));
	
}


int CustomGame::getW() {
	return atoi(inputW->value());
}

int CustomGame::getH() {
	return atoi(inputH->value());
}
int CustomGame::getB() {
	return atoi(inputB->value());
}



int CustomGame::handle(int event) {
	switch (event) {
	case FL_RELEASE:
		
		but->do_callback();
		return 0;
	}
}