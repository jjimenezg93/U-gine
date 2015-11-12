#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#pragma warning(disable: 4100)
#pragma warning(disable: 4710)
#pragma warning(disable: 4820)
#pragma warning(disable: 4996)

#include "../include/u-gine.h"

int main(int argc, char* argv[]) {
	Screen::Instance().Open(800, 600, false);
	
	Image * ball = ResourceManager::Instance().LoadImage(String("../data/ball.png"), 128, 128);
	//ball->SetHandle(ball->GetHFrames() / 2, ball->GetVFrames() / 2);		//center
	uint32 xCoord = Screen::Instance().GetWidth() + (ball->GetHFrames() / 2);
	uint32 yCoord = Screen::Instance().GetHeight() + (ball->GetVFrames() / 2);

	while ( Screen::Instance().IsOpened() && !Screen::Instance().KeyPressed(GLFW_KEY_ESC)) {
		//update image angle and scale

		//clean screen and draw Image
		Renderer::Instance().Clear();

		Renderer::Instance().DrawEllipse(xCoord, yCoord, 128, 128);

		Screen::Instance().Refresh();
	}
	
	return 0;
}
