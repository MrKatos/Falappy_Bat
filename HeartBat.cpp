#include "HeartBat.h"

HeartBat::HeartBat()
{
	this->InitWindow();
	this->InitFloor();
	this->InitPipe();
	this->InitText();
	this->InitHitbox();
	this->InitBestScore();
	this->InitMenu();
	this->InitBools();
}

void HeartBat::Run()
{
	while (window.isOpen()) 
	{

		float time = this->clock.getElapsedTime().asSeconds();
		this->clock.restart();
		time *= 35;
		 
		sf::Clock clock;
		sf::Time elapsedTime;
		elapsedTime = clock.getElapsedTime();

		this->PullEvents();
		if (this->NotPause)
		{
			this->AnimateBat(time);
		}
		this->Fall(time);

		if (this->BatAlive && this->NotPause)
		{
			this->AnimateFloor();
			this->AnimatePipe();
		}

		this->Render();
	}
}
//KEYBOARD
void HeartBat::PullEvents() 
{

	sf::Event event;
	while (this->window.pollEvent(event)) 
	{
		if (event.Event::type == sf::Event::Closed || event.Event::KeyPressed && event.Event::key.code == sf::Keyboard::Escape) 
		{
			this->window.close();
		}

		if (!InMenu)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
			{
				FallSpeed = 0.1;
				Velocity = -2.3f;
				this->NotPause = true;
				this->Start = true;
			}
		}
		if (Start)
		{
			if (this->BatAlive)
			{

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P))
				{
					FallSpeed = 0;
					Velocity = 0;
					this->InMenu = true;
					this->NotPause = false;
				}
			}
		}
		if (this->InMenu)
		{
			if (this->BatAlive)
			{
				if (this->menu->GetPlayBounds().contains(this->window.mapPixelToCoords(sf::Mouse::getPosition(this->window))) && event.type == sf::Event::MouseButtonPressed)
				{
					FallSpeed = 0.1;
					Velocity = -2.3f;
					this->NotPause = true;
					this->Start = true;
					this->InMenu = false;
				}
				if (this->menu->GetReplayBounds().contains(this->window.mapPixelToCoords(sf::Mouse::getPosition(this->window))) && event.type == sf::Event::MouseButtonPressed)
				{
					this->RestartGame();
				}

				if (this->menu->GetPlayBounds().contains(this->window.mapPixelToCoords(sf::Mouse::getPosition(this->window))))
				{
					this->menu->SetPlayColor(sf::Color(255, 255, 255, 255));
				}
				else
				{
					this->menu->SetPlayColor(sf::Color(190, 190, 190, 255));
				}

				if (this->menu->GetReplayBounds().contains(this->window.mapPixelToCoords(sf::Mouse::getPosition(this->window))))
				{
					this->menu->SetReplayColor(sf::Color(255, 255, 255, 255));
				}
				else
				{
					this->menu->SetReplayColor(sf::Color(190, 190, 190, 255));
				}
			}
			else
			{
				if (this->menu->GetReplayBounds().contains(this->window.mapPixelToCoords(sf::Mouse::getPosition(this->window))) && event.type == sf::Event::MouseButtonPressed)
				{
					this->menu->SetTypeMenu(false);
					this->RestartGame();
				}
				if (this->menu->GetReplayBounds().contains(this->window.mapPixelToCoords(sf::Mouse::getPosition(this->window))))
				{
					this->menu->SetReplayColor(sf::Color(255, 255, 255, 255));
				}
				else
				{
					this->menu->SetReplayColor(sf::Color(190, 190, 190, 255));
				}
			}
			
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) 
		{
			this->menu->SetTypeMenu(false);
			this->RestartGame();
		}
	}
}
//INITS
void HeartBat::InitWindow()
{
	this->window.create(sf::VideoMode(600, 600), "FlappyBat");
	this->window.setFramerateLimit(60);
}

void HeartBat::InitMenu()
{
	this->menu = new Menu();
}

void HeartBat::InitBools()
{
	BatAlive = true;
	InMenu = false;
	NotPause = true;
	Start = false;
	PipeCreat = true;
	GetPoint = true;
}

void HeartBat::InitBestScore()
{
	std::ifstream file("save/score.txt");
	if (file.is_open())
	{
		std::getline(file, BestScore);
		file.close();
	}
	else
	{
		std::cout << "Unable to open the file" << std::endl;
	}
	
}

void HeartBat::SetBestScore()
{
	this->ScoreMenu.setString(std::to_string(this->score));
	if (std::stoi(this->BestScore) <= this->score)
	{
		std::ofstream out("save/score.txt", std::ios::trunc);
		out << std::to_string(this->score);
		out.close();
		this->InitBestScore();
	}
	this->BestScoreMenu.setString(this->BestScore);
}

void HeartBat::InitFloor()
{
	this->floor.push_back(new Floor(sf::Vector2f(0, 450)));
	this->floor.push_back(new Floor(sf::Vector2f(602, 450)));
}

void HeartBat::InitHitbox()
{
	this->hitbox.setRadius(30.f);
	this->hitbox.setOrigin(sf::Vector2f(40.f, 67.f));
	this->hitbox.setPosition(this->bat.GetPosition());
}

void HeartBat::InitText()
{
	if (!font.loadFromFile("font.ttf"))
	{
		std::cout << "Can not download from file" << std::endl;
	}
	else
	{
		this->scoreText1.setFont(font);
		this->scoreText1.setCharacterSize(36);
		this->scoreText1.setFillColor(sf::Color(251, 206, 21));
		this->scoreText1.setPosition(50, 50);
		this->scoreText1.setString("Score: " + std::to_string(this->score));

		this->scoreText2.setFont(font);
		this->scoreText2.setCharacterSize(39);
		this->scoreText2.setFillColor(sf::Color::Black);
		this->scoreText2.setPosition(44, 50);
		this->scoreText2.setString("Score: ");

		this->Paused.setFont(font);
		this->Paused.setCharacterSize(36);
		this->Paused.setFillColor(sf::Color(251, 206, 21));
		this->Paused.setPosition(200,200);
		this->Paused.setString("Game Paused");

		this->Paused2.setFont(font);
		this->Paused2.setCharacterSize(39);
		this->Paused2.setFillColor(sf::Color::Black);
		this->Paused2.setPosition(193, 200);
		this->Paused2.setString("Game Paused");

		this->Start1.setFont(font);
		this->Start1.setCharacterSize(36);
		this->Start1.setFillColor(sf::Color(251, 206, 21));
		this->Start1.setPosition(110, 200);
		this->Start1.setString("Press \"space\" to start");

		this->Start2.setFont(font);
		this->Start2.setCharacterSize(39);
		this->Start2.setFillColor(sf::Color::Black);
		this->Start2.setPosition(95, 200);
		this->Start2.setString("Press \"space\" to start");

		this->ScoreMenu.setFont(font);
		this->ScoreMenu.setCharacterSize(25);
		this->ScoreMenu.setFillColor(sf::Color::Black);
		this->ScoreMenu.setPosition(244, 174);
		this->ScoreMenu.setString(std::to_string(this->score));

		this->BestScoreMenu.setFont(font);
		this->BestScoreMenu.setCharacterSize(25);
		this->BestScoreMenu.setFillColor(sf::Color::Black);
		this->BestScoreMenu.setPosition(297, 145);
		this->BestScoreMenu.setString(this->BestScore);
	}
}

void HeartBat::InitPipe()
{
	
		std::srand(static_cast<unsigned>(std::time(NULL)));
		int a = rand() % 5;
		switch (a)
		{
		case 0:
			this->pipe.push_back(new Pipe(sf::Vector2f(670, 460), 0));
			this->pipe.push_back(new Pipe(sf::Vector2f(670, 0), 180));
			break;
		case 1:
			this->pipe.push_back(new Pipe(sf::Vector2f(670, 360), 0));
			this->pipe.push_back(new Pipe(sf::Vector2f(670, -100), 180));
			break;
		case 2:
			this->pipe.push_back(new Pipe(sf::Vector2f(670, 560), 0));
			this->pipe.push_back(new Pipe(sf::Vector2f(670, 100), 180));
			break;
		case 3:
			this->pipe.push_back(new Pipe(sf::Vector2f(670, 300), 0));
			this->pipe.push_back(new Pipe(sf::Vector2f(670, -160), 180));
			break;
		case 4:
			this->pipe.push_back(new Pipe(sf::Vector2f(670, 400), 0));
			this->pipe.push_back(new Pipe(sf::Vector2f(670, -60), 180));
			break;
		}
	}

//OTHER
void HeartBat::Render()
{
	this->window.clear(sf::Color::White);
	this->background.Render(this->window);
	this->bat.Render(this->window);
	this->DrawPipe();
	this->DrawFloor();
	if (!InMenu)
	{
		this->window.draw(this->scoreText2);
		this->window.draw(this->scoreText1);
	}
	if (!this->NotPause)
	{
		this->window.draw(this->Paused2);
		this->window.draw(this->Paused);
	}
	if (!this->Start)
	{
		this->window.draw(this->Start2);
		this->window.draw(this->Start1);
	}
	if(this->InMenu)
	{
		this->menu->Render(this->window);
		this->window.draw(this->ScoreMenu);
		this->window.draw(this->BestScoreMenu);
	}
	this->window.display();
}

void HeartBat::Fall(float time_arg)
{
	if (BatAlive)
	{
		if (this->bat.GetPosition().y < 450)
		{
			this->bat.Move(0, this->Velocity);
			this->Velocity += this->FallSpeed;
		}
		else
		{
			this->bat.SetDeadReason(DEAD::FLOOR);
			std::cout << this->bat << std::endl;
			this->SetBestScore();
			this->BatAlive = false;
			this->menu->SetTypeMenu(true);
			this->InMenu = true;
		}
		this->UpdateHitBox();
	}
	else
	{
		if (this->bat.GetPosition().y < 600)
		{
			this->bat.Move(0, this->DeadVelocity);
			this->DeadVelocity += this->FallSpeed;
		}
	}

	for (int i = 0; i < this->pipe.size(); i++)
	{
		if (this->CheckHit(i)) 
		{
			if (this->BatAlive)
			{
				this->bat.SetDeadReason(DEAD::PIPE);
				std::cout << this->bat << std::endl;
				this->SetBestScore();
			}
			this->BatAlive = false;
			this->menu->SetTypeMenu(true);
			this->InMenu = true;
		}
	}		
}

void HeartBat::AnimateBat(float time_arg)
{
	this->CurrentFrame += 0.05 * time_arg;
	if (this->CurrentFrame > 4) this->CurrentFrame -= 4;
	this->bat.SetTextureRect(sf::IntRect(int(this->CurrentFrame) * 162.f, 110.f, 162.f, 73.f));
}

void HeartBat::AnimateFloor()
{
	if (static_cast<int>(this->floor[0]->GetPosition().x) <= -602)
	{
		delete this->floor[0];
		this->floor.erase(this->floor.begin());
		this->floor.push_back(new Floor(sf::Vector2f(602 - this->speed, 450)));
	}
	for (size_t i = 0; i < this->floor.size(); ++i)
	{
		this->floor[i]->Move(-this->speed, 0.f);
	}
}

void HeartBat::AnimatePipe()
{
	if (this->Start) 
	{
		if (static_cast<int>(this->pipe[0]->GetPosition().x) >= 248 && static_cast<int>(this->pipe[0]->GetPosition().x) <= 252 && this->PipeCreat)
		{
			this->PipeCreat = false;
			this->InitPipe();
		}
		if (static_cast<int>(this->pipe[0]->GetPosition().x) <= -70)
		{
			this->GetPoint = true;
			this->PipeCreat = true;
			delete this->pipe[0];
			delete this->pipe[1];
			this->pipe.erase(this->pipe.begin());
			this->pipe.erase(this->pipe.begin());
		}
		for (size_t i = 0; i < this->pipe.size(); ++i)
		{
			this->pipe[i]->Move(-this->speed, 0.f);
		}
		for (int i = 0; i < this->pipe.size(); i++)
		{
			this->SetScore(i);
		}
	}
	this->RefreshScore();
	
}

void HeartBat::DrawFloor()
{
	for (size_t i = 0; i < floor.size(); ++i)
	{
		this->floor[i]->Render(this->window);
	}
}

void HeartBat::DrawPipe()
{
	for (size_t i = 0; i < pipe.size(); ++i)
	{
		this->pipe[i]->Render(this->window);
	}
}

void HeartBat::UpdateHitBox()
{
	this->hitbox.setPosition(this->bat.GetPosition());
}

bool HeartBat::CheckHit(int a)
{
	sf::FloatRect CircleBounds = this->hitbox.getGlobalBounds();
	sf::FloatRect RectangleBounds = this->pipe[a]->GetGlobalBounds();
	return CircleBounds.intersects(RectangleBounds);
}

void HeartBat::RefreshScore()
{
	scoreText1.setString("Score: " + std::to_string(this->score));
	scoreText2.setString("Score: " + std::to_string(this->score));
}

void HeartBat::SetScore(int i)
{
	if (this->GetPoint)
	{
		if (static_cast<int>(this->pipe[0]->GetPosition().x) <= this->hitbox.getPosition().x)
		{
			this->GetPoint = false;
			this->score += 1;
			this->speed += static_cast<float>(this->speed) / 10.f;
		}
	}
}

void HeartBat::RestartGame()
{
	for (size_t i = 0; i < pipe.size(); i++)
	{
		delete this->pipe[i];
	}
	this->pipe.clear();

	for (size_t i = 0; i < floor.size(); i++)
	{
		delete this->floor[i];
	}
	this->floor.clear();

	this->FallSpeed = 0;
	this->Velocity = 0;
	this->DeadVelocity = 0;

	this->bat.SetDeadReason(DEAD::UNKNOWN);
	this->bat.SetPosition(300.f, 300.f);

	this->score = 0;
	this->speed = 1;

	this->InitFloor();
	this->InitPipe();
	this->InitBools();
}


