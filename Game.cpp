#include <string>
#include <iostream>
#include <exception>

#include "GameFramework.h"
#include "World.h"
#include "Scalings.h"


class Game : public GameFramework {

protected:

	bool IsDirectionLeft(InputKey k) {
		if (InputKey::LEFT == k)
			return true;
		else if (InputKey::RIGHT == k)
			return false;
		return false;
	}

public:
	Game(int width, int height, bool fullscreen = false) {
		world = nullptr;
		window_width = width;
		window_height = height;
		window_fullscreen = fullscreen;
		mouseX = mouseY = 0;
	}

	virtual void GamePreparation(int& width, int& height, bool& fullscreen)
	{
		width = window_width;
		height = window_height;
		fullscreen = window_fullscreen;
	}

	virtual bool GameInit() {
		world = new World();
		return true;
	}

	virtual void GameExit() {
		delete world;
	}

	virtual bool GameTick() {
		world->SpawnAll();
		world->MoveAll();
		world->ClearQueues();
		if (world->GetPlayer()->IsShooting() && oldTickShoot < (getTickCount() / 200)) {
			world->SpawnProjectile(mouseX, mouseY, 0);
			oldTickShoot = getTickCount() / 200;
		}
		if (getTickCount() % 5000 == 0) {
			world->SpawnProjectile(0, 0, 1);
		}
		if (startedImmunity != 0) {
			if (getTickCount() / 1000 > 20 + startedImmunity) {
				world->StopPlayerImmunity();
				startedImmunity = 0;
			}
		}
		world->CheckCollisions();
		world->DrawWorld();
		if (world->ToRestart()) {
			World* tmp = world;
			world = new World();
			delete tmp;
		}
		return false;
	}

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative) {
		mouseX = x;
		mouseY = y;
	}

	virtual void onMouseButtonClick(InputMouseButton button, bool isReleased) {
		if (button == InputMouseButton::LEFT) {
			Player* p = world->GetPlayer();
			if ((!p->IsShooting() && !isReleased) || (p->IsShooting() && isReleased)) {
				p->MakeShoot();
			}
		}
		if (button == InputMouseButton::RIGHT) {
			if (world->CanPlayerBeImmune()) {
				world->StartPlayerImmunity();
				startedImmunity = getTickCount() / 1000;
			}
		}
	}

	virtual void onKeyPressed(InputKey k) {
		Player* p = world->GetPlayer();
		if (k == InputKey::LEFT) {
			p->MakeMove(1);
		}
		else if (k == InputKey::RIGHT){
			p->MakeMove(0);
		}
	}

	virtual void onKeyReleased(InputKey k) {
		Player* p = world->GetPlayer();
		p->Stop(IsDirectionLeft(k));
	}

	virtual const char* GetTitle() override
	{
		return "Jump Ninja Jump!";
	}

private:
	int window_width;
	int window_height;
	int mouseX, mouseY;
	bool window_fullscreen;
	unsigned int oldTickShoot = 0;
	unsigned int startedImmunity = 0;
	World* world;
};

int main(int argc, char* argv[])
{
	double x = 350, y = 600;
	bool userInput = false;
	for (int i = 0; i < argc; i++) {
		std::string s = argv[i];
		if (userInput) {
			std::string strX = s.substr(0, s.find('x'));
			std::string strY = s.substr(s.find('x') + 1, s.length());
			try {
				if (strX.length() == strY.length()) {
					throw std::runtime_error("Bad arguments");
				}
				if (stoi(strX) < 175) {
					x = 175;
				}
				else if (stoi(strX) > 1920) {
					x = 1920;
				}
				else {
					x = stoi(strX);
				}

				if (stoi(strY) < 300) {
					y = 300;
				}
				else if (stoi(strY) > 1080) {
					y = 1080;
				}
				else {
					y = stoi(strY);
				}
							
			}
			catch (std::exception err) {
				std::cerr << "Invalid arguments, using default values" << std::endl;
				x = 350;
				y = 600;
			}
			userInput = false;
		}
		if (s == "-screen") {
			userInput = true;
		}
	}
	Scalings::SetVariables(x / 350.0, y / 600.0, std::min(x / 350.0, y / 600.0));
	return run(new Game((int)x, (int)y, false));
}
