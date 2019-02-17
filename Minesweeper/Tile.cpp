#include <Windows.h>
#include <FL/Fl.h>
#include <FL/Fl_Window.h>
#include <FL/Fl_JPEG_Image.H>
#include <FL/Fl_Box.h>
#include <FL/Fl_Button.H>
#include "Tile.h"
#include <iostream>
using namespace std;


Tile::Tile(int x, int y, int w, int h, int xpos, int ypos, bool hasMine) : Fl_Button(x,y,w,h) , hasMine(hasMine), row(xpos), col(ypos) {
	click = "left";
	flagsNear = 0;
	pics.push_back(new Fl_JPEG_Image("img/tile-basic.jpg"));
	pics.push_back(new Fl_JPEG_Image("img/tile-covered.jpg"));
	pics.push_back(new Fl_JPEG_Image("img/tile-1.jpg"));
	pics.push_back(new Fl_JPEG_Image("img/tile-2.jpg"));
	pics.push_back(new Fl_JPEG_Image("img/tile-3.jpg"));
	pics.push_back(new Fl_JPEG_Image("img/tile-4.jpg"));
	pics.push_back(new Fl_JPEG_Image("img/tile-5.jpg"));
	pics.push_back(new Fl_JPEG_Image("img/tile-6.jpg"));
	pics.push_back(new Fl_JPEG_Image("img/tile-7.jpg"));
	pics.push_back(new Fl_JPEG_Image("img/tile-8.jpg"));
	pics.push_back(new Fl_JPEG_Image("img/tile-question.jpg")); //10
	pics.push_back(new Fl_JPEG_Image("img/tile-flag.jpg")); //11
	pics.push_back(new Fl_JPEG_Image("img/tile-game_over.jpg")); //12
	pics.push_back(new Fl_JPEG_Image("img/tile-reveal.jpg")); //13
	pics.push_back(new Fl_JPEG_Image("img/tile-bad.jpg")); //14


	debug = false;
	covered = true;
	//this->image(pics.at(0));
	
}




void Tile::debugMine() {
	
	if (hasMine) {
		
		if (!debug) {
			debug = true;
			this->image(0);
			this->color(FL_RED);
			this->redraw();
		}
		else {
			if (hasFlag) {
				this->image(pics.at(11));
			}
			else if (hasQuestion) {
				this->image(pics.at(10));
			}
			else {
				this->image(0);
			}
			debug = false;
			
			this->color(FL_GRAY);
			this->redraw();
		}	
	}
}

int Tile::getRow() {
	return row;
}
int Tile::getCol() {
	return col;
}



void Tile::placeBomb(bool has) {

	hasMine = has;
	bombsNear = -1;
	
}

void Tile::reset() {
	debugM = false;
	debug = false;
	hasFlag = false;
	hasQuestion = false;
	hasMine = false;
	covered = true;
	bombsNear = 0;
	totalClicks = 0;
	//this->copy_label("");
	this->align(FL_ALIGN_IMAGE_MASK);
	this->image(0);
	this->color(FL_GRAY);
	this->redraw();
}

Fl_JPEG_Image* Tile::changePic() {
	if (hasFlag == true) {
		hasFlag = false;

		hasQuestion = true;
		return pics.at(10);
	}
	else if (hasQuestion) {
		hasQuestion = false;
		
		
		return 0;
	}
	else if (!hasFlag && !hasQuestion) {
		hasFlag = true;

		return pics.at(11);
	}
}


void Tile::incBombCnt(int bombs) {
	//cout << "inc bombs" << endl;
	bombsNear = bombs;
}

void Tile::incFlags(int flags) {
	flagsNear = flags;
}

bool Tile::haveMine() {
	return hasMine;
}

int Tile::getClicks(){
	return this->totalClicks;
}

bool Tile::getCovered() {
	return covered;
}

bool Tile::getDebugM() {
	return debugM;
}

bool Tile::flagged() {
	return hasFlag;
}

int Tile::totalClicks = 0;
bool Tile::debugM = false;

void Tile::clearTile() {
	//cout << "CLEARED TILE" << endl;
	
	covered = false;
	//this->labelcolor(FL_BLUE);
	//this->labelfont(8);
	if (hasMine) {
		this->image(pics.at(12));
		cout << "LOSTTTTT" << endl;
	}
	else {
		this->image(pics.at(bombsNear + 1));

	}
	//this->color(FL_WHITE);
	
	
	this->redraw();
	
}


void Tile::updateLost() {
	this->color(FL_GRAY);
	if (hasFlag&&!hasMine) {
		//this->color(FL_BLUE);
		this->image(pics.at(14));
	}
	else if (!hasFlag&&hasMine) {
		//this->color(FL_GREEN);
		this->image(pics.at(13));
	}
	else if (hasFlag&&hasMine) {
		this->image(pics.at(11));
	}
	this->redraw();
	
}

int Tile::getBombsNear() {
	return bombsNear;
}
int Tile::getFlagsNear() {
	return flagsNear;
}

void Tile::setFlag() {
	hasFlag = true;
	this->image(pics.at(11));
	this->redraw();
}

bool Tile::questioned() {
	return hasQuestion;
}

string Tile::clickT() {
	return click;
}

bool Tile::playing = true;

void Tile::setPlaying(bool c) {
	playing = c;
}

int Tile::handle(int event) {
	switch (event) {
	case FL_RELEASE:
		if (Fl::event_button() == FL_LEFT_MOUSE) {
			if (playing) {
				click = "left";
				debugM = false;
				if (!hasFlag) {
					cout << "left click" << endl;
					cout << "Bombs Near: " << bombsNear << endl;
					cout << "Flags Near: " << flagsNear << endl;

					this->totalClicks++;




					/*if (hasMine) {
					this->image(pics.at(12));

					}*/
					do_callback();


					this->redraw();
				}

				return 1;
			}
			
			
		}

		else if (Fl::event_button() == FL_RIGHT_MOUSE) {
			if (playing) {
				click = "right";
				if (covered) {

					Fl_JPEG_Image* p = changePic();
					this->image(p);

					this->redraw();

					cout << "right click" << endl;
					cout << "Bombs Near: " << bombsNear << endl;
					cout << "Flags Near: " << flagsNear << endl;
					this->totalClicks++;
					//if (totalClicks == 1) {
					do_callback();
					//}
				}

				return 1;
			}
			
		}
	case FL_KEYBOARD:
		if (Fl::event_shift() && Fl::event_key() == 'd') {
			if (playing) {
				click = "debug";
				cout << "DEBUG Mode" << endl;
				if (totalClicks == 1) {
					//totalClicks++;
				}
				debugM = true;
				this->do_callback();
			}
			

		}
		return 1;
	

	}

}





