#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#pragma warning(disable: 4100)
#pragma warning(disable: 4710)
#pragma warning(disable: 4820)
#pragma warning(disable: 4996)

#include "../include/u-gine.h"

int main(int argc, char* argv[]) {
	Screen::Instance().Open(800, 600, false);
	
	String filename = String("data/soccer_npot.png");

	Image * ball = ResourceManager::Instance().LoadImage(filename, 1, 1);
	ball->SetMidHandle();		//center

	double rotation = 1;
	double scale = 0;
	short int flagScale = 1;

	while ( Screen::Instance().IsOpened() && !Screen::Instance().KeyPressed(GLFW_KEY_ESC)) {
		scale += (Screen::Instance().ElapsedTime() * (2 * flagScale));
		rotation += (Screen::Instance().ElapsedTime() * 30);

		if (scale >= 5) {
			flagScale = -1;
		} else if (scale <= 0.5) {
			flagScale = 1;
		}

		//clean screen and draw Image
		Renderer::Instance().Clear();

		Renderer::Instance().DrawImage(ball, Screen::Instance().GetMouseX(), Screen::Instance().GetMouseY(), 0U, scale * ball->GetWidth(), scale * ball->GetHeight(), rotation);

		Screen::Instance().Refresh();
	}
	
	return 0;
}
