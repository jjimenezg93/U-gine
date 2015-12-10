#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#pragma warning(disable: 4100)
#pragma warning(disable: 4710)
#pragma warning(disable: 4820)
#pragma warning(disable: 4996)

#include "../include/u-gine.h"

int main(int argc, char* argv[]) {
	Screen::Instance().Open(800, 600, false);

	SkeletonSprite * sSprite = new SkeletonSprite("data/animation.xml");
	sSprite->SetFPS(32);

	while (Screen::Instance().IsOpened() && !Screen::Instance().KeyPressed(GLFW_KEY_ESC)) {
		Renderer::Instance().Clear();

		sSprite->SetPosition(Screen::Instance().GetMouseX(), Screen::Instance().GetMouseY());

		sSprite->Update(Screen::Instance().ElapsedTime());
		sSprite->Render();

		Screen::Instance().Refresh();
	}
	
	//image
	ResourceManager::Instance().FreeResources();

	delete sSprite;

	return 0;
}
