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

	//IMAGES
	Image * mouseRectImg = ResourceManager::Instance().LoadImage("data/rect.png");
	mouseRectImg->SetMidHandle();

	Image * mouseCircImg = ResourceManager::Instance().LoadImage("data/circle.png");
	mouseCircImg->SetMidHandle();

	Image * boxImg = ResourceManager::Instance().LoadImage("data/box.jpg");
	boxImg->SetMidHandle();

	Image * ballImg = ResourceManager::Instance().LoadImage("data/ball.png");
	ballImg->SetMidHandle();

	Image * alienImg = ResourceManager::Instance().LoadImage("data/alien.png");
	alienImg->SetMidHandle();

	CollisionPixelData * alienPixelData = ResourceManager::Instance().LoadCollisionPixelData("data/aliencol.png");
	CollisionPixelData * alienPixelPlayerData = ResourceManager::Instance().LoadCollisionPixelData("data/alienplayercol.png");

	//SCENE
	Scene * mainScene = new Scene();

	//SPRITES
	Sprite * ballSprt = mainScene->CreateSprite(ballImg);
	ballSprt->SetPosition(Screen::Instance().GetWidth() / 4, Screen::Instance().GetHeight() / 4);
	ballSprt->SetCollision(Sprite::CollisionMode::COLLISION_CIRCLE);
	ballSprt->SetColor(255, 255, 255, 255);
	ballSprt->SetBlendMode(Renderer::BlendMode::ALPHA);

	Sprite * boxSprt = mainScene->CreateSprite(boxImg);
	boxSprt->SetPosition(Screen::Instance().GetWidth() * 3/4, Screen::Instance().GetHeight() *3/4);
	boxSprt->SetCollision(Sprite::CollisionMode::COLLISION_RECT);
	boxSprt->SetColor(255, 255, 255, 255);
	boxSprt->SetBlendMode(Renderer::BlendMode::ALPHA);

	Sprite * alienSprt = mainScene->CreateSprite(alienImg);
	alienSprt->SetPosition(Screen::Instance().GetWidth() / 4, Screen::Instance().GetHeight() * 3 / 4);
	alienSprt->SetCollisionPixelData(alienPixelData);
	alienSprt->SetCollision(Sprite::CollisionMode::COLLISION_PIXEL);
	alienSprt->SetColor(255, 255, 255, 255);
	alienSprt->SetBlendMode(Renderer::BlendMode::ALPHA);

	Sprite * mouseSprt = mainScene->CreateSprite(mouseCircImg);
	mouseSprt->SetBlendMode(Renderer::BlendMode::ALPHA);
	mouseSprt->SetCollision(Sprite::CollisionMode::COLLISION_CIRCLE);
	mouseSprt->SetColor(255, 255, 255, 255);

	double keyDelay = 0;

	while (Screen::Instance().IsOpened() && !Screen::Instance().KeyPressed(GLFW_KEY_ESC)) {
		Renderer::Instance().Clear();

		if (Screen::Instance().MouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT) &&  keyDelay >= 0.5) {
			mouseSprt->SetImage(mouseCircImg);
			mouseSprt->SetCollision(Sprite::CollisionMode::COLLISION_CIRCLE);
			keyDelay = 0;
		} else if (Screen::Instance().MouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT) && keyDelay >= 0.5) {
			mouseSprt->SetCollision(Sprite::CollisionMode::COLLISION_RECT);
			mouseSprt->SetImage(mouseRectImg);
			keyDelay = 0;
		} else if (Screen::Instance().MouseButtonPressed(GLFW_MOUSE_BUTTON_MIDDLE) && keyDelay >= 0.5) {
			//mouseSprt->SetCollisionPixelData(alienPixelData);
			mouseSprt->SetCollisionPixelData(alienPixelPlayerData);
			mouseSprt->SetCollision(Sprite::CollisionMode::COLLISION_PIXEL);
			mouseSprt->SetImage(alienImg);
			keyDelay = 0;
		}

		if (mouseSprt->CheckCollision(ballSprt)) {
			mouseSprt->SetColor(255, 0, 0, 255);
			ballSprt->SetColor(255, 0, 0, 255);
		} else if (mouseSprt->CheckCollision(boxSprt)) {
			mouseSprt->SetColor(255, 0, 0, 255);
			boxSprt->SetColor(255, 0, 0, 255);
		} else if (mouseSprt->CheckCollision(alienSprt)) {
			mouseSprt->SetColor(255, 0, 0, 255);
			alienSprt->SetColor(255, 0, 0, 255);
		} else {
			mouseSprt->SetColor(255, 255, 255, 255);
			ballSprt->SetColor(255, 255, 255, 255);
			boxSprt->SetColor(255, 255, 255, 255);
			alienSprt->SetColor(255, 255, 255, 255);
		}

		mouseSprt->SetPosition(Screen::Instance().GetMouseX(), Screen::Instance().GetMouseY());

		mainScene->Update(Screen::Instance().ElapsedTime());
		mainScene->Render();

		keyDelay += Screen::Instance().ElapsedTime();

		Screen::Instance().Refresh();
	}
	
	delete mainScene;

	ResourceManager::Instance().FreeResources();

	return 0;
}
