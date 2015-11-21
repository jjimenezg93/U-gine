#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#pragma warning(disable: 4100)
#pragma warning(disable: 4710)
#pragma warning(disable: 4820)
#pragma warning(disable: 4996)

#include "../include/u-gine.h"

int main(int argc, char* argv[]) {
	Screen::Instance().Open(800, 600, false);
	
	while ( Screen::Instance().IsOpened() && !Screen::Instance().KeyPressed(GLFW_KEY_ESC)) {
		Renderer::Instance().SetColor(255, 255, 255, 255);
		Renderer::Instance().DrawRect(Screen::Instance().GetWidth() / 3, 0, Screen::Instance().GetWidth() / 3, Screen::Instance().GetHeight());

		//ALPHA
		Renderer::Instance().SetBlendMode(Renderer::BlendMode::ALPHA);

		Renderer::Instance().SetColor(255, 0, 0, 128);
		Renderer::Instance().DrawEllipse(Screen::Instance().GetWidth() / 4, (Screen::Instance().GetHeight() / 2), 24, 24);

		Renderer::Instance().SetColor(0, 255, 0, 128);
		Renderer::Instance().DrawEllipse((Screen::Instance().GetWidth() / 4) - 16, (Screen::Instance().GetHeight() / 2) + 16, 24, 24);

		Renderer::Instance().SetColor(0, 0, 255, 128);
		Renderer::Instance().DrawEllipse((Screen::Instance().GetWidth() / 4) + 16, (Screen::Instance().GetHeight() / 2) + 16, 24, 24);

		//SOLID
		Renderer::Instance().SetBlendMode(Renderer::BlendMode::SOLID);

		Renderer::Instance().SetColor(255, 0, 0, 255);
		Renderer::Instance().DrawEllipse(Screen::Instance().GetWidth() / 2, (Screen::Instance().GetHeight() / 4), 24, 24);

		Renderer::Instance().SetColor(0, 255, 0, 255);
		Renderer::Instance().DrawEllipse((Screen::Instance().GetWidth() / 2) - 16, (Screen::Instance().GetHeight() / 4) + 16, 24, 24);

		Renderer::Instance().SetColor(0, 0, 255, 255);
		Renderer::Instance().DrawEllipse((Screen::Instance().GetWidth() / 2) + 16, (Screen::Instance().GetHeight() / 4) + 16, 24, 24);

		//MULTIPLICATIVE
		Renderer::Instance().SetBlendMode(Renderer::BlendMode::MULTIPLICATIVE);

		Renderer::Instance().SetColor(255, 0, 0, 255);
		Renderer::Instance().DrawEllipse(Screen::Instance().GetWidth() / 2, (Screen::Instance().GetHeight() / 2), 24, 24);

		Renderer::Instance().SetColor(0, 255, 0, 255);
		Renderer::Instance().DrawEllipse((Screen::Instance().GetWidth() / 2) - 16, (Screen::Instance().GetHeight() / 2) + 16, 24, 24);

		Renderer::Instance().SetColor(0, 0, 255, 255);
		Renderer::Instance().DrawEllipse((Screen::Instance().GetWidth() / 2) + 16, (Screen::Instance().GetHeight() / 2) + 16, 24, 24);

		//ADDITIVE
		Renderer::Instance().SetBlendMode(Renderer::BlendMode::ADDITIVE);

		Renderer::Instance().SetColor(255, 0, 0, 255);
		Renderer::Instance().DrawEllipse(Screen::Instance().GetWidth() * 3 / 4, (Screen::Instance().GetHeight() / 2), 24, 24);

		Renderer::Instance().SetColor(0, 255, 0, 255);
		Renderer::Instance().DrawEllipse((Screen::Instance().GetWidth() * 3 / 4) - 16, (Screen::Instance().GetHeight() / 2) + 16, 24, 24);

		Renderer::Instance().SetColor(0, 0, 255, 255);
		Renderer::Instance().DrawEllipse((Screen::Instance().GetWidth() * 3 / 4) + 16, (Screen::Instance().GetHeight() / 2) + 16, 24, 24);

		Screen::Instance().Refresh();
	}
	
	return 0;
}
