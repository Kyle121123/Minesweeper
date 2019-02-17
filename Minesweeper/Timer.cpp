#include <Windows.h>
#include <FL/Fl.h>
#include <FL/Fl_Window.h>
#include <ctime>
#include <FL/Fl_Box.h>
#include <FL/Fl_Button.H>
#include <time.h>
#include "Tile.h"
#include "Timer.h"
#include <iostream>
#include "pch.h"



using namespace std;



static void Timer_CB(void *data) {              // timer callback
	static long start = time(NULL);
	long now = time(NULL);
	static int count = 0;
	//cout << "COUNT: " << count << endl;;
	Timer* t = static_cast<Timer*>(data);
	
	if (!(t->hasStartedT())) {
		
		start = now;
		t->copy_label(to_string(now - start).c_str());

	}
	if (count == 0) {
		start = now;
	}
	
	if (!(t->stopTime())) {
		if (now-start >= 999) {

			count = 0;
			Fl::remove_timeout(Timer_CB, data);
			printf("Timer turned off.\n");
		}
		else {
			Fl::repeat_timeout(.2, Timer_CB, data);
			count++;
			//t->copy_label(to_string(count).c_str());
		}
	}
	
	else {
		count = 0;
		Fl::remove_timeout(Timer_CB, data);
	}
	
	

	

	t->copy_label(to_string(now-start).c_str());
	//
	//printf("Timer! #%d\n", count); 
	
	
	
	/*
	if (count > 1  && (t->hasStartedT())) {
		Fl::repeat_timeout(1, Timer_CB, data);
		count++;
		t->copy_label(to_string(count).c_str());
	}
	else if ((t->hasStartedT())) {
		Fl::repeat_timeout(1, Timer_CB, data);
		count++;
		t->copy_label(to_string(count).c_str());
		

	}
	

	
	else if (count >= 999) {


		Fl::remove_timeout(Timer_CB, data);
		printf("Timer turned off.\n");
	}
	else {
		Fl::repeat_timeout(0, Timer_CB, data);
		count = 0;
		t->copy_label(to_string(count).c_str());
	}
	   */                   
	
}


void Timer::setStopTime(bool t) {
	
	stop = t;
}

bool Timer::stopTime() {
	return stop;
}


Timer::Timer(int x, int y, int w, int h):Fl_Box(x,y,w,h,"0") {
	this->startedT = false;
	this->stop = false;
	//hasStartedT();
	this->labelsize(45);
	//this->copy_label("BOX NEW");
	this->color(FL_BLACK);
	this->show();
	//box->show();
	Fl::add_timeout(1, Timer_CB,(void*)this);
	
	/*
	time_t now;
	struct tm newyear;
	double seconds;

	time(&now);  /* get current time; same as: now = time(NULL)  

	//newyear = *localtime(&now);

	newyear.tm_hour = 0; newyear.tm_min = 0; newyear.tm_sec = 0;
	newyear.tm_mon = 0;  newyear.tm_mday = 0;
	int n = 0;
	while ( n <999) {
		time_t nowN;
		time(&nowN);
		newyear.tm_sec = newyear.tm_sec + 1;
		seconds = difftime(nowN, now);
		printf("%.f seconds since new year in the current timezone.\n", seconds);
		n++;
		
	}
	*/




	

}

void Timer::setStartedT(bool con) {
	startedT = con;
	if (con) {
		this->copy_label("0");
		Fl::add_timeout(1, Timer_CB, (void*)this);
		
		this->redraw();
	}

	
}

bool Timer::hasStartedT() {
	return this->startedT;
}

void Timer::reset() {
	stop = false;
	Fl::remove_timeout(Timer_CB, (void*)this);
	this->copy_label("0");
	
	
	
}
