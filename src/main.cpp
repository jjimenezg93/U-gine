#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#pragma warning(disable: 4100)
#pragma warning(disable: 4710)
#pragma warning(disable: 4820)
#pragma warning(disable: 4996)

#include "../include/u-gine.h"

float genRandomF(double min, double max) {
	return ((float(rand()) / float(RAND_MAX)) * (max - min) + min);
}

void checkAndUpdateDirection(Font *font, const String &text) {
	if (font->GetX() + font->GetTextWidth(text) >= Screen::Instance().GetWidth() || font->GetX() <= 0) {
		font->SetSpeedX(font->GetSpeedX() * -1);
		Renderer::Instance().SetColor(genRandomF(20, 255), genRandomF(20, 255), genRandomF(20, 255), 255);
	}

	if (font->GetY() + font->GetTextHeight(text) >= Screen::Instance().GetHeight() || font->GetY() <= 0) {
		font->SetSpeedY(font->GetSpeedY() * -1);
		Renderer::Instance().SetColor(genRandomF(20, 255), genRandomF(20, 255), genRandomF(20, 255), 255);
	}
}

int main(int argc, char* argv[]) {
	Screen::Instance().Open(800, 600, false);

	Renderer::Instance().SetColor(genRandomF(20, 255), genRandomF(20, 255), genRandomF(20, 255), 255);

	Font * monoSpacedFont = ResourceManager::Instance().LoadFont("data/monospaced.png");
	String textToShow = String("Hola, mundo");

	monoSpacedFont->SetX(Screen::Instance().GetWidth() / 2);
	monoSpacedFont->SetY(Screen::Instance().GetHeight() / 2);

	monoSpacedFont->SetSpeedX(genRandomF(128, 255));
	monoSpacedFont->SetSpeedY(genRandomF(128, 255));

	while (Screen::Instance().IsOpened() && !Screen::Instance().KeyPressed(GLFW_KEY_ESC)) {
		Renderer::Instance().Clear();

		checkAndUpdateDirection(monoSpacedFont, textToShow);

		monoSpacedFont->SetX(monoSpacedFont->GetX() + (monoSpacedFont->GetSpeedX() * Screen::Instance().ElapsedTime()));
		monoSpacedFont->SetY(monoSpacedFont->GetY() + (monoSpacedFont->GetSpeedY() * Screen::Instance().ElapsedTime()));

		monoSpacedFont->Render(textToShow, monoSpacedFont->GetX(), monoSpacedFont->GetY());

		Screen::Instance().Refresh();
	}
	
	//image
	ResourceManager::Instance().FreeResources();

	return 0;
}
