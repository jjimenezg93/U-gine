#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#pragma warning(disable: 4100)
#pragma warning(disable: 4710)
#pragma warning(disable: 4820)
#pragma warning(disable: 4996)

#include "../include/u-gine.h"
#include <ctime>

int main(int argc, char* argv[]) {
	srand(time(NULL));
	Screen::Instance().Open(800, 600, false);

	String alienFile = String("data/alienanim.png");
	Image * alien = ResourceManager::Instance().LoadImage(alienFile, 8, 1);
	alien->SetMidHandle();

	Sprite * alienSprite = new Sprite(alien);
	alienSprite->SetPosition(Screen::Instance().GetWidth() / 2, Screen::Instance().GetHeight() / 2);
	alienSprite->SetPosition(0, 0);

	Sprite * alienSprite2 = new Sprite(alien);
	alienSprite2->SetPosition(Screen::Instance().GetWidth() / 2, Screen::Instance().GetHeight() / 2);
	alienSprite2->SetPosition(350, 250);

	Sprite * alienSprite3 = new Sprite(alien);
	alienSprite3->SetPosition(Screen::Instance().GetWidth() / 2, Screen::Instance().GetHeight() / 2);
	alienSprite3->SetPosition(600, 50);

	Array<Sprite *> sprites;
	sprites.Add(alienSprite);
	sprites.Add(alienSprite2);
	sprites.Add(alienSprite3);

	for (unsigned short int i = 0; i < sprites.Size(); i++) {
		sprites[i]->SetFPS(16);
		sprites[i]->SetFrameRange(0, 7);
		sprites[i]->SetScaleX(4);
		sprites[i]->SetScaleY(4);
	}

	Array<double> spritesSpeeds;

	spritesSpeeds.Add(128);
	spritesSpeeds.Add(64);
	spritesSpeeds.Add(168);

	while (Screen::Instance().IsOpened() && !Screen::Instance().KeyPressed(GLFW_KEY_ESC)) {
		Renderer::Instance().Clear();

		for (unsigned short int i = 0; i < sprites.Size(); i++) {
			//move
			sprites[i]->MoveTo(Screen::Instance().GetMouseX(), Screen::Instance().GetMouseY(), spritesSpeeds[i]);

			//rotation
			if (sprites[i]->GetX() < Screen::Instance().GetMouseX() && sprites[i]->IsMoving()) {
				sprites[i]->RotateTo(-15, 128);
			} else if (sprites[i]->GetX() > Screen::Instance().GetMouseX() && sprites[i]->IsMoving()) {
				sprites[i]->RotateTo(15, 128);
			}

			if (!sprites[i]->IsMoving()) {
				sprites[i]->RotateTo(0, 128);
			}

			sprites[i]->Update(Screen::Instance().ElapsedTime());
			sprites[i]->Render();
		}

		Screen::Instance().Refresh();
	}

	for (unsigned short int i = 0; i < sprites.Size(); i++) {
		delete sprites[i];
	}
	
	//image
	ResourceManager::Instance().FreeResources();

	return 0;
}
