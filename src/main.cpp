#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#pragma warning(disable: 4100)
#pragma warning(disable: 4710)
#pragma warning(disable: 4820)
#pragma warning(disable: 4996)

#include "../include/u-gine.h"

float genRandomF(double min, double max) {
	return ((float(rand()) / float(RAND_MAX)) * (max - min) + min);
}

int main(int argc, char* argv[]) {
	Screen::Instance().Open(800, 600, false);

	String alienFile = String("data/alien.png");
	String backgroundFile = String("data/background.png");

	Image *imgSprite = ResourceManager::Instance().LoadImage(alienFile, 1, 1);
	Image *background = ResourceManager::Instance().LoadImage(backgroundFile, 1, 1);

	Scene *mainScene = new Scene(background);
	mainScene->SetBackgroundColor(0, 0, 255);

	Sprite *sprt = mainScene->CreateSprite(imgSprite);

	(mainScene->GetCamera()).FollowSprite(sprt);

	while (Screen::Instance().IsOpened() && !Screen::Instance().KeyPressed(GLFW_KEY_ESC)) {
		Renderer::Instance().Clear();

		mainScene->Update(Screen::Instance().ElapsedTime());
		
		mainScene->Render();
		Screen::Instance().Refresh();
	}
	
	//image
	ResourceManager::Instance().FreeResources();

	delete mainScene;

	return 0;
}
