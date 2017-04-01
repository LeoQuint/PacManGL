#include "Game.h"
#include <stdio.h>
#include <iostream>
#include <mmsystem.h>

								//gameboard[y][x]
const char Game::initial_gameboard[31][28] = {//i = empty intersection, f = intersection with d, w = intersection with u
											{'1','2','2','2','2','2','2','2','2','2','2','2','2','3','1','2','2','2','2','2','2','2','2','2','2','2','2','3'},
											{'8','f','d','d','d','d','f','d','d','d','d','d','f','4','8','f','d','d','d','d','d','f','d','d','d','d','f','4'},
											{'8','d','1','2','2','3','d','1','2','2','2','3','d','8','4','d','1','2','2','2','3','d','1','2','2','3','d','4'},
											{'8','u','8','0','0','4','d','8','0','0','0','4','d','8','4','d','8','0','0','0','4','d','8','0','0','4','u','4'},
											{'8','d','7','6','6','5','d','7','6','6','6','5','d','7','5','d','7','6','6','6','5','d','7','6','6','5','d','4'},
											{'8','f','d','d','d','d','f','d','d','f','d','d','f','d','d','f','d','d','f','d','d','f','d','d','d','d','f','4'},
											{'8','d','1','2','2','3','d','1','3','d','1','2','2','2','2','2','2','3','d','3','1','d','1','2','2','3','d','4'},
											{'8','d','7','6','6','5','d','8','4','d','7','6','6','3','1','6','6','5','d','4','8','d','7','6','6','5','d','4'},
											{'8','f','d','d','d','d','f','8','4','f','d','d','f','8','4','f','d','d','f','4','8','f','d','d','d','d','f','4'},
											{'7','2','2','2','2','3','d','8','7','2','2','3','0','8','4','0','1','2','2','5','8','d','7','2','2','2','2','5'},
											{'0','0','0','0','0','4','d','8','1','6','6','5','0','7','5','0','7','6','6','3','8','d','8','0','0','0','0','0'},
											{'0','0','0','0','0','4','d','8','4','i','0','0','i','i','i','i','0','0','i','4','8','d','8','0','0','0','0','0'},
											{'0','0','0','0','0','4','d','8','4','0','1','2','2','-','-','2','2','3','0','4','8','d','8','0','0','0','0','0'},
											{'6','6','6','6','6','5','d','7','5','0','8','0','0','0','0','0','0','4','0','5','7','d','7','6','6','6','6','6'},
											{'9','0','0','0','0','0','f','0','0','i','8','0','0','0','0','0','0','4','i','0','0','f','0','0','0','0','0','9'},
											{'2','2','2','2','2','3','d','1','3','0','8','0','0','0','0','0','0','4','0','1','3','d','1','2','2','2','2','2'},
											{'0','0','0','0','0','4','d','8','4','0','7','6','6','6','6','6','6','5','0','8','4','d','8','0','0','0','0','0'},
											{'0','0','0','0','0','4','d','8','4','i','0','0','0','0','0','0','0','0','i','8','4','d','8','0','0','0','0','0'},
											{'0','0','0','0','0','4','d','8','4','0','1','2','2','2','2','2','2','3','0','8','4','d','8','0','0','0','0','0'},
											{'1','6','6','6','6','5','d','7','5','0','7','6','6','3','1','6','6','5','0','7','5','d','7','6','6','6','6','3'},
											{'8','f','d','d','d','d','f','d','d','f','d','d','f','8','4','f','d','d','f','d','d','f','d','d','d','d','f','4'},
											{'8','d','1','2','2','3','d','1','2','2','2','3','d','8','4','d','1','2','2','2','3','d','1','2','2','3','d','4'},
											{'8','d','7','6','3','4','d','7','6','6','6','5','d','7','5','d','7','6','6','6','5','d','8','1','6','5','d','4'},
											{'8','w','d','f','8','4','f','d','d','f','d','d','f','0','0','f','d','d','f','d','d','f','8','4','f','d','w','4'},
											{'7','2','3','d','8','4','d','1','3','d','1','2','2','2','2','2','2','3','d','1','3','d','8','4','d','1','6','5'},
											{'1','6','5','d','7','5','d','8','4','d','7','6','6','3','1','6','6','5','d','8','4','d','7','5','d','7','2','3'},
											{'8','f','d','f','d','d','f','8','4','f','d','d','f','8','4','f','d','d','f','8','4','f','d','d','f','d','f','4'},
											{'8','d','1','2','2','2','2','5','7','2','2','3','d','8','4','d','1','2','2','2','2','5','7','2','2','3','d','4'},
											{'8','d','7','6','6','6','6','6','6','6','6','5','d','7','5','d','7','6','6','6','6','6','6','6','6','5','d','4'},
											{'8','f','d','d','d','d','d','d','d','d','d','d','f','d','d','f','d','d','d','d','d','d','d','d','d','d','f','4'},
											{'7','6','6','6','6','6','6','6','6','6','6','6','6','6','6','6','6','6','6','6','6','6','6','6','6','6','6','5'} };

Game::Game(void)
{
	wallmanager = new Wallmanager();
	dot = new Dot();
	powerup = new Powerup();
	pacman = new Pacman();
	pinky = new Pinky();
	blinky = new Blinky();
	inky = new Inky();
	clyde = new Clyde();
	
	
	speed = 200;
	level = 1;
	score = 0;
	paused = false;
	initHeaders();
	newLevel();
}
void Game::playSound(void)
{
	PlaySoundA((LPCSTR)"C:/Users/Leonard/Desktop/PacManOpenGL/Debug/pacman_chomp.wav", NULL, SND_FILENAME | SND_ASYNC);
}
void Game::initHeaders(void)
{
	lives_header = new Text("Lives:");
	level_header = new Text("Level:");
	score_header = new Text("Score:");
}

Game::~Game(void)
{
}
void Game::setPoint(int x, int y)
{
	this->x = x;
	this->y = y;
}
void Game::draw(void)
{
	glViewport(x, y, width * 0.7, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.5, 28.5, 31.5, -1.5, -512, 512);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	for (int i = 0; i < 31; i++)
	{
		for (int j = 0; j < 28; j++)
		{

			glPushMatrix();
			glTranslatef(j, i, 0);
			switch (gameboard[i][j])
			{
			case 'd':
			case 'f':
				dot->draw();
				break;
			case 'u':
			case 'w':
				powerup->draw();
				break;
			case '0':
			case '9':
			case 'i':
				break;
			default:
				wallmanager->draw(gameboard[i][j]);
				break;
			}
			glPopMatrix();
		}
	}
	pacman->draw();
	pinky->draw();
	blinky->draw();
	inky->draw();
	clyde->draw();

	glViewport(width * 0.7 + x, 0 + y, width * 0.3, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-150, 150, 500, -500, -512, 512);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();
	glTranslatef(-50, -500, 0);
	drawScore();
	drawLives();
	drawLevel();
	glPopMatrix();
}
void Game::setKeys(int l, int t, int r, int b) {
	pacman->setKeys(l, t, r, b);
}
void Game::drawLevel()
{
	MyDrawable::newMaterial(1, 0, 1, 0);
	glTranslatef(0, 150, 0);
	level_header->draw();
	glPushMatrix();
	glTranslatef(50, 30, 0);
	Text::drawInt(level);
	glPopMatrix();
}
void Game::drawLives()
{
	MyDrawable::newMaterial(1, 1, 1, 0);
	glTranslatef(0, 150, 0);
	lives_header->draw();
	glPushMatrix();
	glTranslatef(50, 30, 0);
	Text::drawInt(pacman->lives);
	glPopMatrix();
}
void Game::drawScore()
{
	MyDrawable::newMaterial(1, 1, 0, 0);
	glTranslatef(0, 150, 0);
	score_header->draw();
	glPushMatrix();
	glTranslatef(50, 30, 0);
	Text::drawInt(score);
	glPopMatrix();
}

void Game::superPacman(void)
{

	pinky->makeMortal();
	blinky->makeMortal();
	inky->makeMortal();
	clyde->makeMortal();

}
void Game::update(void)
{
	if (dots > 0) {
		pacman->update(gameboard);
		int x = pacman->getX();
		int y = pacman->getY();
		switch (gameboard[y][x]) {
		case 'u':
			superPacman();
			score++;
			gameboard[y][x] = '0';
			break;
		case 'w':
			superPacman();
			score++;
			gameboard[y][x] = 'i';
			break;
		case 'd':
			score++;
			dots--;
			gameboard[y][x] = '0';
			break;
		case 'f':
			score++;
			dots--;
			gameboard[y][x] = 'i';
			break;
		}
		boolean hit = false;

		
		hit = pinky->update(x, y, gameboard) || hit;
		
		hit = blinky->update(x, y, gameboard) || hit;

		hit = inky->update(x, y, gameboard) || hit;

		hit = clyde->update(x, y, gameboard) || hit;

		if (hit) 
		{
			score -= 30;
			pacman->die();
		}
	}
	else 
	{
		levelUp();
	}
}
void Game::levelUp(void)
{
	level++;
	if (level % 5 == 0) {
		pacman->lives++;
	}
	if (speed > 100) {
		speed -= 20;
	}
	newLevel();
}
void Game::newLevel(void)
{
	pacman->setPoint(13, 23);
	pinky->die();
	blinky->die();
	inky->die();
	clyde->die();
	pinky->setPoint(12, 14);
	blinky->setPoint(13, 14);
	inky->setPoint(14, 14);
	clyde->setPoint(14, 14);
	dots = 0;
	initGameboard();
	
	
}
void Game::pause(void)
{
	paused = !paused;
}
boolean Game::isPlaying(void) {
	return !paused;
}

boolean Game::hasEnded(void) {
	return pacman->isDead();
}

void Game::initGameboard(void)
{
	for (int i = 0; i < 31; i++)
	{
		std::vector<Node*> row;
		
		for (int j = 0; j < 28; j++)
		{
			if (this->initial_gameboard[i][j] == 'd' || this->initial_gameboard[i][j] == 'u' || this->initial_gameboard[i][j] == 'f'  || this->initial_gameboard[i][j] == 'w') {
				dots++;
			}
			gameboard[i][j] = this->initial_gameboard[i][j];
			Node *n = new Node(
				this->initial_gameboard[i][j] == 'd' || 
				this->initial_gameboard[i][j] == 'u' || 
				this->initial_gameboard[i][j] == 'f' || 
				this->initial_gameboard[i][j] == 'w' || 
				this->initial_gameboard[i][j] == '0' ||
				this->initial_gameboard[i][j] == 'i' ||
				this->initial_gameboard[i][j] == '-',
				i, j, NULL
				);
			row.push_back(n);
		}
		grid.push_back(row);
	}
	//Assign the grid to each ghosts
	pinky->InitGid(grid);
	blinky->InitGid(grid);
	inky->InitGid(grid);
	clyde->InitGid(grid);


}


void Game::keyListener(int key, int x, int y)
{
	if (key == 1112) {
		paused = !paused;
	}
	pacman->keyListener(key, x, y);
}

void Game::setDimensions(int x, int y)
{
	width = x;
	height = y;
}