#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#pragma warning(disable: 4100)
#pragma warning(disable: 4710)
#pragma warning(disable: 4820)
#pragma warning(disable: 4996)

#include "../include/u-gine.h"

#define SPEED 5

float genRandomF(double min, double max) {
	return ((float(rand()) / float(RAND_MAX)) * (max - min) + min);
}

int main(int argc, char* argv[]) {
	Screen::Instance().Open(800, 600, false);

	//IMAGES
	Image * alienImg = ResourceManager::Instance().LoadImage("data/alien.png");
	alienImg->SetMidHandle();

	Map * map = new Map(String("data/map.tmx"));

	MapScene * mainScene = new MapScene(map);

	Sprite * alienSprite = mainScene->CreateSprite(alienImg);
	(mainScene->GetCamera()).FollowSprite(alienSprite);

	while (Screen::Instance().IsOpened() && !Screen::Instance().KeyPressed(GLFW_KEY_ESC)) {
		Renderer::Instance().Clear();

		if (Screen::Instance().KeyPressed(GLFW_KEY_LEFT)) {
			alienSprite->SetPosition(alienSprite->GetX() - SPEED, alienSprite->GetY());
		} else if (Screen::Instance().KeyPressed(GLFW_KEY_RIGHT)) {
			alienSprite->SetPosition(alienSprite->GetX() + SPEED, alienSprite->GetY());
		}
		
		if (Screen::Instance().KeyPressed(GLFW_KEY_UP)) {
			alienSprite->SetPosition(alienSprite->GetX(), alienSprite->GetY() - SPEED);
		} else if (Screen::Instance().KeyPressed(GLFW_KEY_DOWN)) {
			alienSprite->SetPosition(alienSprite->GetX(), alienSprite->GetY() + SPEED);
		}

		mainScene->Update(Screen::Instance().ElapsedTime());
		mainScene->Render();

		Screen::Instance().Refresh();
	}
	
	delete mainScene;
	delete map;
	ResourceManager::Instance().FreeResources();

	return 0;
}
