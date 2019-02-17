#include <Windows.h>
#include <FL/Fl.h>
#include <FL/Fl_Window.h>
#include <FL/Fl_JPEG_Image.h>

#include <FL/Fl_Box.h>
#include <FL/Fl_Button.H>
#include "Tile.h"
#include "ResetButton.h"
#include <iostream>


using namespace std;

ResetButton::ResetButton(int x, int y) : Fl_Button(x,y,30,30) {
	image(new Fl_JPEG_Image("img/smile-idle.jpg"));



}

void ResetButton::updateImg(bool t) {
	if (t) {
		this->image(new Fl_JPEG_Image("img/smile-won.jpg"));
	}
	else {
		this->image(new Fl_JPEG_Image("img/smile-lost.jpg"));
	}
	this->redraw();
}
int  ResetButton::handle(int event) {
	switch (event) {
	case FL_RELEASE:
		if (Fl::event_button() == FL_LEFT_MOUSE) {
			this->image(new Fl_JPEG_Image("img/smile-idle.jpg"));
			this->redraw();


			cout << "RESET" << endl;
			do_callback();
			return 1;
		}
	default:
		return Fl_Widget::handle(event);

	}
}




