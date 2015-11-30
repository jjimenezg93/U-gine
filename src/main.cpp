#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#pragma warning(disable: 4100)
#pragma warning(disable: 4710)
#pragma warning(disable: 4820)
#pragma warning(disable: 4996)

#include "../include/u-gine.h"
#include <ctime>

struct SpriteSpeed {
	SpriteSpeed(double x, double y) : x(x), y(y) {};
	double x, y;

	void setSSX(double x) { this->x = x; }
	void setSSY(double y) { this->y = y; }
	double getSSX() { return x; }
	double getSSY() { return y; }
};

void checkAndUpdateSpriteDirection(Sprite *sprite) {
	if (sprite->GetX() <= sprite->GetX() / 2) {
		((SpriteSpeed *)(sprite->GetUserData()))->setSSX(((SpriteSpeed *)(sprite->GetUserData()))->getSSX() * (-1));
	} else if (sprite->GetX() >= Screen::Instance().GetWidth() - sprite->GetImage()->GetWidth()) {
		((SpriteSpeed *)(sprite->GetUserData()))->setSSX(((SpriteSpeed *)(sprite->GetUserData()))->getSSX() * (-1));
	}

	if (sprite->GetY() <= sprite->GetY() / 2) {
		((SpriteSpeed *)(sprite->GetUserData()))->setSSY(((SpriteSpeed *)(sprite->GetUserData()))->getSSY() * (-1));
	} else if (sprite->GetY() >= Screen::Instance().GetHeight() - sprite->GetImage()->GetHeight()) {
		((SpriteSpeed *)(sprite->GetUserData()))->setSSY(((SpriteSpeed *)(sprite->GetUserData()))->getSSY() * (-1));
	}
}

float genRandomF() {
	return ((float(rand()) / float(RAND_MAX)) * (15 - 0) + 0);
}

int main(int argc, char* argv[]) {
	srand(time(NULL));
	Screen::Instance().Open(800, 600, false);

	String alienFile = String("data/alien.png");
	Image * alien = ResourceManager::Instance().LoadImage(alienFile, 1, 1);
	alien->SetMidHandle();

	Sprite * alienSprite = new Sprite(alien);
	//alienSprite->SetPosition(Screen::Instance().GetWidth() / 2, Screen::Instance().GetHeight() / 2);
	alienSprite->SetPosition(0, 0);
	alienSprite->SetUserData(new SpriteSpeed(genRandomF(), genRandomF()));

	Sprite * sprites[] = { alienSprite };

	while (Screen::Instance().IsOpened() && !Screen::Instance().KeyPressed(GLFW_KEY_ESC)) {
		Renderer::Instance().Clear();

		for (unsigned short int i = 0; i < sizeof(sprites) / sizeof(sprites[0]); i++) {
			//checkAndUpdateSpriteDirection(sprites[i]);
			//sprites[i]->SetPosition(sprites[i]->GetX() + ((SpriteSpeed *)(sprites[i]->GetUserData()))->getSSX(), sprites[i]->GetY() + ((SpriteSpeed *)(sprites[i]->GetUserData()))->getSSY());
			sprites[i]->Render();

			//move
			if (!sprites[i]->IsMoving()) {
				sprites[i]->MoveTo(Screen::Instance().GetWidth() - alien->GetWidth(), Screen::Instance().GetHeight() - alien->GetHeight(), 0.1);
				//sprites[i]->MoveTo(600, 380, 3);
			}

			//rotation
			if (!sprites[i]->IsRotating() /*&& sprites[i]->IsMoving()*/) {
				sprites[i]->RotateTo(180, 45);
			}

			sprites[i]->Update(Screen::Instance().ElapsedTime());
		}

		Screen::Instance().Refresh();
	}

	delete alien;

	delete alienSprite;
	return 0;
}
