#include <Windows.h>
#include <FL/Fl.h>
#include <FL/Fl_Window.h>
#include <FL/Fl_Button.H>
#include <FL/Fl_Menu_Bar.H>
#include <iostream>
#include <time.h>
#include <vector>
#include <string>
#include "Game.h"






int main() {

	Game* game = new Game(9,9,10,"easy");


	/*
	
	
	
	
	Fl_Menu_Bar *menu = new Fl_Menu_Bar(0,0,game->boardSizeW*25,25);
	menu->add("File/About", 0, About_CB);
	menu->add("File/Quit",   FL_CTRL+'q',Quit_CB);
	menu->add("Edit/Change", FL_CTRL+'c', Change_CB);
	menu->add("Edit/Submenu/Aaa");
	menu->add("Edit/Submenu/Bbb");

	
	

	
	
	
	*/


	game->show();
	Fl::run();
	

}