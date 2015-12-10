#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#pragma warning(disable: 4100)
#pragma warning(disable: 4710)
#pragma warning(disable: 4820)
#pragma warning(disable: 4996)

#include "../include/u-gine.h"

/*void checkAndUpdateDirection(const Font *font, const String &text) {
	if (font->GetTextWidth(text) <= font->GetX() / 2) {
	} else if (font->GetX() >= Screen::Instance().GetWidth() - font->GetImage()->GetWidth()) {
	}

	if (font->GetY() <= font->GetY() / 2) {
	} else if (font->GetY() >= Screen::Instance().GetHeight() - font->GetImage()->GetHeight()) {
	}
}*/

float genRandomF(double min, double max) {
	return ((float(rand()) / float(RAND_MAX)) * (max - min) + min);
}

int main(int argc, char* argv[]) {
	Screen::Instance().Open(800, 600, false);

	Font * monoSpacedFont = ResourceManager::Instance().LoadFont("data/monospaced.png");
	String textToShow = String("Hola, mundo");

	monoSpacedFont->SetSpeedX(genRandomF(128, 255));
	monoSpacedFont->SetSpeedY(genRandomF(128, 255));

	while (Screen::Instance().IsOpened() && !Screen::Instance().KeyPressed(GLFW_KEY_ESC)) {
		Renderer::Instance().Clear();

		monoSpacedFont->Render(textToShow, monoSpacedFont->GetX() + monoSpacedFont->GetSpeedX(), monoSpacedFont->GetY() + monoSpacedFont->GetSpeedY());

		//checkAndUpdateDirection(monoSpacedFont, textToShow);

		Screen::Instance().Refresh();
	}
	
	//image
	ResourceManager::Instance().FreeResources();

	return 0;
}
