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

	Image * starImage = ResourceManager::Instance().LoadImage("data/star.png");
	starImage->SetMidHandle();

	Scene * mainScene = new Scene();

	Emitter * em = mainScene->CreateEmitter(starImage, true);

	Sprite * sprtStar = mainScene->CreateSprite(starImage, Scene::LAYER_FRONT);
	sprtStar->SetColor(255, 0, 0, 255);
	sprtStar->SetBlendMode(Renderer::BlendMode::ALPHA);
	
	em->SetRate(500, 1000);
	em->SetVelocityX(-128, 128);
	em->SetVelocityY(-128, 128);
	em->SetAngularVelocity(0, 360);
	em->SetLifetime(1, 2);
	em->SetMinColor(0, 0, 0);
	em->SetMaxColor(255, 255, 255);

	double keyDelay = 0;

	while (Screen::Instance().IsOpened() && !Screen::Instance().KeyPressed(GLFW_KEY_ESC)) {
		Renderer::Instance().Clear();

		if (Screen::Instance().MouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT) && !em->IsEmitting() && keyDelay >= 0.5) {
			em->Start();
			keyDelay = 0;
		} else if (Screen::Instance().MouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT) && em->IsEmitting() && keyDelay >= 0.5) {
			em->Stop();
			keyDelay = 0;
		}

		sprtStar->SetPosition(Screen::Instance().GetMouseX(), Screen::Instance().GetMouseY());
		em->SetPosition(Screen::Instance().GetMouseX(), Screen::Instance().GetMouseY());

		mainScene->Update(Screen::Instance().ElapsedTime());
		mainScene->Render();

		keyDelay += Screen::Instance().ElapsedTime();

		Screen::Instance().Refresh();
	}
	
	//image
	ResourceManager::Instance().FreeResources();

	return 0;
}
