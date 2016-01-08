#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#pragma warning(disable: 4100)
#pragma warning(disable: 4710)
#pragma warning(disable: 4820)
#pragma warning(disable: 4996)

#include "../include/u-gine.h"

#define SPEED 10

float genRandomF(double min, double max) {
	return ((float(rand()) / float(RAND_MAX)) * (max - min) + min);
}

int main(int argc, char* argv[]) {
	Screen::Instance().Open(800, 600, false);

	String alienFile = String("data/alien.png");
	String backgroundFile = String("data/background.png");

	Image *imgSprite = ResourceManager::Instance().LoadImage(alienFile, 1, 1);
	imgSprite->SetMidHandle();
	Image *background = ResourceManager::Instance().LoadImage(backgroundFile, 1, 1);

	Scene *mainScene = new Scene(background);
	mainScene->SetBackgroundColor(0, 0, 255);

	Sprite *sprt = mainScene->CreateSprite(imgSprite);
	sprt->SetPosition(Screen::Instance().GetWidth() / 2, Screen::Instance().GetHeight() / 2);

	(mainScene->GetCamera()).SetBounds(0, 0, background->GetWidth(), background->GetHeight());
	(mainScene->GetCamera()).FollowSprite(sprt);

	while (Screen::Instance().IsOpened() && !Screen::Instance().KeyPressed(GLFW_KEY_ESC)) {
		Renderer::Instance().Clear();

		if (Screen::Instance().KeyPressed(GLFW_KEY_LEFT) && sprt->GetX() > sprt->GetImage()->GetWidth() / 2)
			sprt->SetX(sprt->GetX() - SPEED);
		if (Screen::Instance().KeyPressed(GLFW_KEY_RIGHT) && sprt->GetX() <= (mainScene->GetCamera()).GetMaxX() - (sprt->GetImage()->GetWidth() / 2))
			sprt->SetX(sprt->GetX() + SPEED);
		if (Screen::Instance().KeyPressed(GLFW_KEY_UP) && sprt->GetY() > sprt->GetImage()->GetHeight() / 2)
			sprt->SetY(sprt->GetY() - SPEED);
		if (Screen::Instance().KeyPressed(GLFW_KEY_DOWN) && sprt->GetY() <= (mainScene->GetCamera()).GetMaxY() - (sprt->GetImage()->GetHeight() / 2))
			sprt->SetY(sprt->GetY() + SPEED);

		mainScene->Update(Screen::Instance().ElapsedTime());
		
		mainScene->Render();
		Screen::Instance().Refresh();
	}

	ResourceManager::Instance().FreeResources();

	delete mainScene;

	return 0;
}
