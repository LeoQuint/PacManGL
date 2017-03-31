#pragma once
#include "Pinky.h"
#include "Blinky.h"
#include "Inky.h"
#include "Clyde.h"
#include "Pacman.h"
#include "Powerup.h"
#include "Dot.h"
#include "Wallmanager.h"
#include "Text.h"
#include "Node.h"
#include <vector>


class Game
{
public:
	Game(void);
	~Game(void);
	void draw(void);
	void update(void);
	void keyListener(int key, int x, int y);
	int speed;
	int score;
	int width;
	int level;
	int height;
	boolean isPlaying(void);
	boolean hasEnded(void);
	void pause(void);
	void setDimensions(int x,int y);
	void setPoint(int x, int y);
	void setKeys(int l, int t, int r, int b);
	void playSound(void);
private:
	void drawScore(void);
	void drawLives(void);
	void drawLevel(void);
	void initHeaders(void);
	boolean paused;
	int dots;
	void initGameboard(void);
	void levelUp(void);
	void newLevel(void);
	void superPacman(void);
	Blinky* blinky;
	Pinky* pinky;
	Inky* inky;
	Clyde* clyde;
	Pacman* pacman;
	Powerup* powerup;
	Dot* dot;
	Wallmanager* wallmanager;
	std::vector<std::vector<Node*>> grid;
	int x;
	int y;
	const static char initial_gameboard[31][28];
	char gameboard[31][28];
	Text* score_header;
	Text* lives_header;
	Text* level_header;
};

