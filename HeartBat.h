#pragma once
#include "Bat.h"
#include "Background.h"
#include "Floor.h"
#include "Pipe.h"
#include "Menu.h"

#include <fstream>
#include <string>
#include <vector>
#include <ctime>

class HeartBat
{
public:
	HeartBat();
	void Run();
	void PullEvents();
	void InitWindow();
	void InitMenu();
	void InitBools();
	void InitBestScore();
	void SetBestScore();
	void Render();
	void Fall(float time_arg);
	void AnimateBat(float time_arg);
	void InitFloor();
	void AnimateFloor();
	void DrawFloor();
	void InitPipe();
	void AnimatePipe();
	void DrawPipe();
	void UpdateHitBox();
	void InitHitbox();
	bool CheckHit(int a);
	void InitText();
	void RefreshScore();
	void SetScore(int arg);
	void RestartGame();

private:
	sf::RenderWindow window;
	sf::Clock clock;
	sf::Font font;
	sf::Text scoreText1;
	sf::Text scoreText2;
	sf::Text Paused;
	sf::Text Paused2;
	sf::Text Start1;
	sf::Text Start2;

	sf::Text ScoreMenu;
	sf::Text BestScoreMenu;

	float speed = 1;
	float FallSpeed = 0;
	float Velocity = 0;
	float DeadVelocity = 0;
	float CurrentFrame = 0;

	Menu* menu;

	Bat bat;
	Background background;
	std::vector<Floor*> floor;
	std::vector<Pipe*> pipe;
	sf::CircleShape hitbox;

	bool BatAlive;
	bool InMenu;
	bool NotPause;
	bool Start;
	bool PipeCreat;
	bool GetPoint;
	
	int score = 0;
	std::string BestScore;
};

