#include <Windows.h>
#include <FL/Fl.h>
#include <FL/Fl_Window.h>
#include <FL/Fl_Button.H>
#include <iostream>
#include <time.h>
#include <vector>
#include <string>
#include <FL/Fl_Input.H>
#include "Timer.h"
#include "Game.h"
#include <FL/Fl_Menu_Bar.H>
#include "customGame.h"
#include "ResetButton.h"
#include "Tile.h"
#include "Timer.h"
#include <fstream>
#include <FL/Fl_Text_Display.H>
#include <sstream>


using namespace std;

Game::Game(int sizeW, int sizeH, int bombCnt,string d) : Fl_Window(0+sizeW*25+30, 90+sizeH*25,"MineSweeper"), boardSizeW(sizeW), boardSizeH(sizeH) , bombCnt(bombCnt), difficulty(d){
	
	

	initBoard(); //create all the elements of the board
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 5; ++j) {
			fastestTimes[i][j] = -1;
		}
	}
	readTimes();
	started = false; // game hasnt started yet
	bombsLeft = 0; //set the bombs left

	
}

void Game::readTimes() {
	ifstream times_file("HighScores.bin");
	if (!times_file.is_open()){ cerr << "ERROR OPENING HighScores.bin for reading scores\n"; return; }
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 5; ++j) {
			times_file >> fastestTimes[i][j];
		}
	}
}
void Game::writeTimes() {
	ofstream times_file("HighScores.bin");
	if (!times_file.is_open()){ cerr << "WRITE ERROR: Cannot open HighScores.bin\n"; return; }
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 5; ++j) {
			times_file << fastestTimes[i][j]<<' ';
		}
		times_file << endl;
	}
}

void Game::calculateScore() {

	if (difficulty == "easy") {
		for (int i = 0; i < 5; ++i) {
			if (fastestTimes[0][i] == -1) {
				fastestTimes[0][i] = stoi(timer->label());
				break;
			}
			else if (fastestTimes[0][i] > stoi(timer->label())) {
				int score = stoi(timer->label());
				for (i; i < 5; ++i) {
					int temp = fastestTimes[0][i];
					fastestTimes[0][i] = score;
					score = temp;

				}
			}

		}
	}
	else if (difficulty == "medium") {
		for (int i = 0; i < 5; ++i) {
			if (fastestTimes[1][i] == -1) {
				fastestTimes[1][i] = stoi(timer->label());
				break;
			}
			else if (fastestTimes[1][i] > stoi(timer->label())) {
				int score = stoi(timer->label());
				for (i; i < 5; ++i) {
					int temp = fastestTimes[1][i];
					fastestTimes[1][i] = score;
					score = temp;

				}
			}

		}
	}
	else {
		for (int i = 0; i < 5; ++i) {
			if (fastestTimes[2][i] == -1) {
				fastestTimes[2][i] = stoi(timer->label());
				break;
			}
			else if (fastestTimes[2][i] > stoi(timer->label())) {
				int score = stoi(timer->label());
				for (i; i < 5; ++i) {
					int temp = fastestTimes[2][i];
					fastestTimes[2][i] = score;
					score = temp;

				}
			}

		}
	}
	writeTimes();
}

void Quit_CB(Fl_Widget* g, void* t) {	//exit game
	exit(0);
}




void Custom_CB(Fl_Widget* w, void* t) {		//custom game
	Game* c = static_cast<Game*>(t);
	
	c->hide();
	
	Fl_Window* win = new Fl_Window(0, 0, 200, 200, "Input");
	Fl_Input* inputW = new Fl_Input(50, 10, 120, 25, "Width:");
	Fl_Input* inputH = new Fl_Input(50, 60, 120, 25, "Height:");
	Fl_Input* inputB = new Fl_Input(50, 110, 120, 25, "Bombs:");
	Fl_Button* but = new Fl_Button(50, 150, 100, 40, "Enter");

	win->copy_label("cust");
	win->show();	
	
}



void Easy_CB(Fl_Widget* w, void* t) {	//easy game
	Game* c = static_cast<Game*>(t);
	c->resetTimer();
	c->resetBombs();
	c->hide();
	Game* easy = new Game(9, 9, 10,"easy");
	easy->show();
}
void Medium_CB(Fl_Widget* w, void* t) {		//intermediate game
	Game* c = static_cast<Game*>(t);
	c->resetTimer();
	c->resetBombs();
	c->hide();
	Game* med = new Game(16, 16, 40,"medium");
	med->show();
}
void Expert_CB(Fl_Widget* w, void* t) {		//expert game
	Game* c = static_cast<Game*>(t);
	c->resetTimer();
	c->resetBombs();
	c->hide();
	Game* exp = new Game(30, 16, 99,"expert");
	exp->show();
}

void About_CB(Fl_Widget* w, void* t) {		//about window
	Fl_Window* about = new Fl_Window(200, 150, "About");
	
	Fl_Box *input = new Fl_Box(0, 30, 100, 25, "\tMineSweeper\n Coded by Swamp Donkeys(group 12)");
	about->inside(input);
	about->show();
}
void HighScore_CB(Fl_Widget* w, void* t) {		//about window
	Fl_Window* highScores = new Fl_Window(200, 150, "High Scores");

	Fl_Box *input = new Fl_Box(0, 0, 100, 25, "\t\t\tHigh Scores");
	for (int i = 0; i < 5; ++i) {
		char* temp = new char[2];
		temp[0] = i + 49;
		temp[1] = 0;
		Fl_Box* score = new Fl_Box(65 + i * 25, 30, 20, 25, (const char*)temp);
		highScores->inside(score);
	}
	Fl_Box *easy = new Fl_Box(0, 60, 100, 25, "Easy");
	for (int i = 0; i < 5; ++i) {
		if (((Game*)t)->fastestTimes[0][i] == -1) break;
		string temp(to_string(((Game*)t)->fastestTimes[0][i]));
		char* temp2 = new char[temp.size()+1];
		for (int j = 0; j < temp.size(); ++j) {
			temp2[j] = temp[j];
		}
		temp2[temp.size()] = 0;
		Fl_Box* score = new Fl_Box(65 + i * 25, 60, 20, 25, (const char*)temp2);
		highScores->inside(score);
	}
	cout << endl;
	Fl_Box *medium = new Fl_Box(-10, 90, 100, 25, "Medium");
	for (int i = 0; i < 5; ++i) {

		if (((Game*)t)->fastestTimes[1][i] == -1) break;
		string temp(to_string(((Game*)t)->fastestTimes[1][i]));
		char* temp2 = new char[temp.size() + 1];
		for (int j = 0; j < temp.size(); ++j) {
			temp2[j] = temp[j];
		}
		temp2[temp.size()] = 0;
		Fl_Box* score = new Fl_Box(65 + i * 25, 90, 20, 25, (const char*)temp2);
		highScores->inside(score);
	}
	cout << endl;
	Fl_Box *expert = new Fl_Box(-8, 120, 100, 25, "Expert");
	for (int i = 0; i < 5; ++i) {
		if (((Game*)t)->fastestTimes[2][i] == -1) break;
		string temp(to_string(((Game*)t)->fastestTimes[2][i]));
		char* temp2 = new char[temp.size() + 1];
		for (int j = 0; j < temp.size(); ++j) {
			temp2[j] = temp[j];
		}
		temp2[temp.size()] = 0;
		Fl_Box* score = new Fl_Box(65 + i * 25, 120, 20, 25, (const char*)temp2);
		highScores->inside(score);
	}
	cout << endl;
	highScores->inside(input);
	highScores->inside(easy);
	highScores->inside(medium);
	highScores->inside(expert);
	highScores->show();
}

void tileCallback(Fl_Widget* cb, void* v) {		//handle all tile callbacks
	Game* game = static_cast<Game*>(v);
	Tile* tile = static_cast<Tile*>(cb);
	
	game->setNumNear();		//update the flags/mines near each tile
	
	if (!(game->hasStarted()) && tile->getClicks() == 1) {		//first removed tile
		cout << "GAME START!" << endl;
		cout << "Starting Tile: " << tile->getRow() * 10 + tile->getCol() + 1 << endl;
		game->setStartingTile(tile->getRow() * game->boardSizeW + tile->getCol());	//set starting tile
		game->setBombs();		//set the bombs after the first click
		game->setStarted(true);		//start the game
		if (!(tile->flagged())) {	//not flagged then clear tiles
			game->cascade(tile);

		}
		else {	//update counter if is flagged
			game->bombs->copy_label(to_string(game->getFlags()).c_str());
			
		}


	}
	
	else if ((tile->clickT()=="debug")) {	//debug tiles
		game->debugTiles();
	}
	else if (tile->clickT() == "left" && !(tile->getCovered())) {	//cleared adjacent tiles
		game->clearAdjacent(tile);
	}
	else if (game->hasStarted()&&tile->clickT() =="left") {		//cascade or clear tile;
		game->cascade(tile);


	}
	game->getWon();		//do something if game won
	cout << "Bombs Left: " << game->getFlags() << endl;
	game->bombs->copy_label(to_string(game->getFlags()).c_str());	//update bomb counter
}

void resetCallback(Fl_Widget* cb, void* v) {	//reset game
	cout << "GAME RESET..." << endl;
	Game* game = static_cast<Game*>(v);
	game->resetBombs();
	game->zeroTimer();
	game->setStarted(false);
}

void Game::zeroTimer() {	//fix timer to 0
	timer->copy_label("0");
}

void Game::resetTimer() {
	timer->copy_label("0"); //fix label
	timer->reset();	//reset timeout


}

void Game::clearAdjacent(Tile* tile) {		//clear adjacent tiles if flags = bombs near
	int i = tile->getCol();
	int j = tile->getRow();
	
	if (tile->getBombsNear() == tile->getFlagsNear()) {
		if (!(i == 0)) {			//left
			if (!tiles.at(i - 1).at(j)->flagged()) {
				cascade(tiles.at(i - 1).at(j));
			}
		}												

		if (!(i == boardSizeW - 1)) {		//right
			if (!(tiles.at(i + 1).at(j)->flagged())) {
				cascade((tiles.at(i + 1).at(j)));		
			}
		}


		if (!(j == 0)) {				//top
			if (!tiles.at(i).at(j - 1)->flagged()) {
				cascade(tiles.at(i).at(j - 1));						
			}
		}

		if (!(j == boardSizeH - 1)) {			//bottom
			if (!tiles.at(i).at(j + 1)->flagged()) {

				cascade(tiles.at(i).at(j + 1));			 
			}
		}

		if (!((j == 0) || (i == 0))) {			//top left corner
			if (!tiles.at(i - 1).at(j - 1)->flagged()) {
				cascade(tiles.at(i - 1).at(j - 1));		

			}
		}

		if (!((j == boardSizeH - 1) || (i == boardSizeW - 1))) {		//btm right corner
			if (!tiles.at(i + 1).at(j + 1)->flagged()) {
				cascade(tiles.at(i + 1).at(j + 1));	

			}
		}

		if (!((i == 0) || (j == boardSizeH - 1))) {			//btm left corner
			if (!tiles.at(i - 1).at(j + 1)->flagged()) {
				cascade(tiles.at(i - 1).at(j + 1));		

			}
		}

		if (!((i == boardSizeW - 1) || (j == 0))) {			//top right corner
			if (!tiles.at(i + 1).at(j - 1)->flagged()) {
				cascade(tiles.at(i + 1).at(j - 1));		 

			}
		}
	}
	
}

/*

	function SETTERS/GETTERS
*/

bool Game::hasStarted() { //return playing status
	return started;
}

int Game::getFlags() { //updates the bombs left counter based on flagged tiles
	bombsLeft = bombCnt;
	for (int i = 0; i < boardSizeW; i++) {
		for (int j = 0; j < boardSizeH; j++) {
			if (tiles.at(i).at(j)->flagged()) bombsLeft--;
		}
	}
	return bombsLeft;


}

void Game::getLost(Tile* t) {	//set lost status
	bool lost = false;
	for (int i = 0; i < boardSizeW; i++) {
		for (int j = 0; j < boardSizeH; j++) {
			if (!(tiles.at(i).at(j)->getCovered()) && (tiles.at(i).at(j)->haveMine())) lost = true;
			
		}
	}
	if (lost) {
		rb->updateImg(false);
		tiles.at(0).at(0)->setPlaying(false);

		for (int i = 0; i < boardSizeW; i++) {
			for (int j = 0; j < boardSizeH; j++) {
				if (!(t->getCol() == i && t->getRow() == j)) {
					tiles.at(i).at(j)->updateLost();
				}
				
			}
		}
		timer->setStopTime(true);
	}
}


void Game::getWon() {	//set win status
	
	int uncovered = 0;
	//int coveredMines = 0;
	for (int i = 0; i < boardSizeW; i++) {
		for (int j = 0; j < boardSizeH; j++) {
			if (!(tiles.at(i).at(j)->getCovered()) && (!(tiles.at(i).at(j)->haveMine()))) uncovered++;
		}
	}
	if (uncovered == boardSizeW*boardSizeH - bombCnt) {
		cout << "WON" << endl;
		tiles.at(0).at(0)->setPlaying(false);
		rb->updateImg(true);
		timer->setStopTime(true);
		cout << "Finish Timer: " << timer->label() << endl;
		//code for high score
		calculateScore();
		for (int i = 0; i < boardSizeW; i++) {
			for (int j = 0; j < boardSizeH; j++) {
				
				if (tiles.at(i).at(j)->haveMine()) {
					tiles.at(i).at(j)->setFlag();
				}

			}
			
		}
		cout << "UNCOVERED TILES: " << uncovered << endl;
	}

	
	
}

void Game::setStarted(bool s) {	//set game and timer to start
	started = s;
	timer->setStartedT(s);

}

void Game::setStartingTile(int x) {	//assign starting tile
	this->startingTile = x;
}


void Game::setBombs() {	//place bombs 
	srand(time(NULL));

	cout << "Settig bombs..." << endl;
	vector<int> bombs(bombCnt,-1);
	
	for (int i = 0; i < bombCnt; i++) {
		int num = rand() % (boardSizeW*boardSizeH);
		
		while (contains(bombs, num)) {
			num = rand() % (boardSizeW*boardSizeH);
		}
		bombs.at(i) = num;
	
	}
	
	for (int i = 0; i < bombCnt; i++) {
		int row = (bombs.at(i)) / boardSizeW ;
		
		int col = (bombs.at(i)) % boardSizeW;
		cout << "Bomb Location: " << row << ", " << col << endl;
		
		
		tiles.at(col).at(row)->placeBomb(true);
		
		
	}
	
	setNumNear();  // needs to set bombs near and pass to each tile


}

void Game::setNumNear() {	//set mines and flags near
	Tile * current;
	
	for (int i = 0; i < boardSizeW; i++) {
		for (int j = 0; j < boardSizeH; j++) {
			current = tiles.at(i).at(j);
			int bombs = 0;
			int flags = 0;
			if (!current->haveMine()) {
				
				if (!(i == 0)) {		//left
					if (tiles.at(i - 1).at(j)->haveMine()) bombs++; 
					if (tiles.at(i - 1).at(j)->flagged()) flags++; 

				}
				if (!(i == boardSizeW - 1)) {		//right
					if (tiles.at(i + 1).at(j)->haveMine()) bombs++;  
					if (tiles.at(i + 1).at(j)->flagged()) flags++; 

				}
				
				if (!(j == 0)) {	//top
					if (tiles.at(i).at(j - 1)->haveMine()) bombs++;  
					if (tiles.at(i).at(j - 1)->flagged()) flags++; 

				}
				if (!(j == boardSizeH - 1)) {	//bottom
					if (tiles.at(i).at(j + 1)->haveMine()) bombs++;  
					if (tiles.at(i).at(j + 1)->flagged()) flags++; 

				}

					

				if (!((j == 0) || (i == 0))) {	//top left corner
					if (tiles.at(i - 1).at(j - 1)->haveMine()) bombs++;  
					if (tiles.at(i - 1).at(j - 1)->flagged()) flags++; 

				}

				if (!((j == boardSizeH - 1) || (i == boardSizeW - 1))) {	//btm right corner
					if (tiles.at(i + 1).at(j + 1)->haveMine()) bombs++;  
					if (tiles.at(i + 1).at(j + 1)->flagged()) flags++; 

				}
				if (!((i == 0) || (j == boardSizeH - 1))) {		//btm left corner
					if (tiles.at(i - 1).at(j + 1)->haveMine()) bombs++;  
					if (tiles.at(i - 1).at(j + 1)->flagged()) flags++; 

				}
				if (!((i == boardSizeW - 1) || (j == 0))) {		//top right corner
					if (tiles.at(i + 1).at(j - 1)->haveMine()) bombs++;  
					if (tiles.at(i + 1).at(j - 1)->flagged()) flags++; 


				}
				current->incBombCnt(bombs);
				current->incFlags(flags);
			}
			
			
		}
	}


}



bool Game::contains(vector<int> v, int n) {	//cant loose game on first click, added cascade on first click as well
	for (int i = 0; i < v.size(); i++) {
		if (v.at(i) == n) {
			return true;
		}
	}
	if (((n) == startingTile)|| ((n + 1) == startingTile)|| ((n-1) == startingTile)|| ((n+1+boardSizeW) == startingTile)|| ((n + boardSizeW) == startingTile) || ((n - 1 + boardSizeW) == startingTile)|| ((n + 1 - boardSizeW) == startingTile) || ((n - boardSizeW) == startingTile) || ((n - 1 - boardSizeW) == startingTile)) {
		return true;
	}
	
	return false;
}










void Game::cascade(Tile* t) {	//recursively clear tiles;
	
	
	if (!(t->flagged())) {
		if (t->getCovered() && t->getBombsNear() == 0) {
			t->clearTile();
			int i = t->getCol();
			int j = t->getRow();

			if (!(i == 0)) cascade(tiles.at(i - 1).at(j));						//left
			
			if (!(i == boardSizeW - 1)) cascade((tiles.at(i + 1).at(j)));		//right

			if (!(j == 0)) cascade(tiles.at(i).at(j - 1));						//top
			
			if (!(j == boardSizeH - 1)) cascade(tiles.at(i).at(j + 1));			 //bottom

			if (!((j == 0) || (i == 0))) cascade(tiles.at(i - 1).at(j - 1));		//top left corner

			if (!((j == boardSizeH - 1) || (i == boardSizeW - 1))) cascade(tiles.at(i + 1).at(j + 1));	//btm right corner
			
			if (!((i == 0) || (j == boardSizeH - 1))) cascade(tiles.at(i - 1).at(j + 1));		//btm left corner
			
			if (!((i == boardSizeW - 1) || (j == 0))) cascade(tiles.at(i + 1).at(j - 1));		 //top right corner

		}
		else if (t->getBombsNear() == -1) {	//if its a bomb
			
			t->clearTile();
			getLost(t);
		}
		else {
			
			t->clearTile();

			
		}
	}
	
}






void Game::resetBombs() {	//reset bombss
	timer->setStopTime(false);
	tiles.at(0).at(0)->setPlaying(true);
	bombs->copy_label(to_string(bombCnt).c_str());
	cout << "RESETING BOMBS..." << endl;
	for (int i = 0; i < boardSizeW; i++) {
		for (int j = 0; j < boardSizeH; j++) {
			tiles.at(i).at(j)->reset();


		}
	}
	
}




void Game::debugTiles() {		//debug tiles
	for (int i = 0; i < boardSizeW; i++) {
		for (int j = 0; j < boardSizeH; j++) {
			tiles.at(i).at(j)->debugMine(); 
		}
	}
	
}




void Game::initBoard() {
	cout << "CREATING BOARD..." << endl;

	Fl_Box* container = new Fl_Box(FL_ENGRAVED_BOX, 10, 27, boardSizeW * 25+10, 45, NULL);	//contain top elements
	Fl_Box* container2 = new Fl_Box(FL_ENGRAVED_BOX, 10, 75, boardSizeW * 25+10, boardSizeH*25+10, NULL);	//contain tiles


	timer = new Timer(boardSizeW*25-55,20,70,60);	//timer

	bombs = new Fl_Box(25, 20, 60, 60,"Bombs");	//bomb counter
	bombs->labelsize(45);
	bombs->redraw();
	bombs->copy_label(to_string(bombCnt).c_str());

	rb = new ResetButton(boardSizeW * 25 / 2, 35); // reset button
	rb->callback(resetCallback, static_cast<void*>(this));

	Fl_Menu_Bar *menu = new Fl_Menu_Bar(0, 0, boardSizeW * 25+30, 25);	//file menu
	
	menu->add("File/About", 0, About_CB,(void*)this);
	menu->add("File/High Scores", 0, HighScore_CB, (void*)this);
	menu->add("File/Quit", FL_CTRL + 'q', Quit_CB);
	menu->add("Options/Custom", FL_CTRL + 'c', Custom_CB, (void*)this);
	menu->add("Options/Difficulty/Easy", 0, Easy_CB, (void*)this);
	menu->add("Options/Difficulty/Intermediate", 0,Medium_CB, (void*)this);
	menu->add("Options/Difficulty/Expert",0,Expert_CB, (void*)this);

	
	
	
	//add tiles
	for (int i = 0; i < boardSizeW; i++) {

		vector<Tile*> tRow;
		for (int j = 0; j < boardSizeH; j++) {
			
			Tile* t = new Tile(i * 25+15, 80 + j * 25, 25, 25, j,i);
			t->box(FL_PLASTIC_UP_BOX);
			t->callback(tileCallback, static_cast<void*>(this));
			tRow.push_back(t);
		}
		tiles.push_back(tRow);

	}

	


}



