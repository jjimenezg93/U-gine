#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#pragma warning(disable: 4100)
#pragma warning(disable: 4710)
#pragma warning(disable: 4820)
#pragma warning(disable: 4996)

#include "../include/u-gine.h"

int main(int argc, char* argv[]) {
	Screen::Instance().Open(800, 600, false);
	
	double angle = 0;

	unsigned int circX = 0;
	unsigned int circY = 0;

	while ( Screen::Instance().IsOpened() && !Screen::Instance().KeyPressed(GLFW_KEY_ESC)) {
		//calc circle coords
		circX = Screen::Instance().GetMouseX() + 32 * DegCos(angle);
		circY = Screen::Instance().GetMouseY() - 32 * DegSin(angle);
		
		String title = String("Mouse dist from center = ");
		title += String(String::FromInt(Distance(Screen::Instance().GetWidth() / 2, Screen::Instance().GetHeight() / 2, Screen::Instance().GetMouseX(), Screen::Instance().GetMouseY())));
		title += String(" Circle angle = ") + String::FromInt(Angle(Screen::Instance().GetMouseX(), Screen::Instance().GetMouseY(), circX, circY));
		Screen::Instance().SetTitle(title);
		
		// TAREA: Pintar primitivas
		Renderer::Instance().Clear();
		Renderer::Instance().SetColor(255, 0, 0, 255);
		Renderer::Instance().DrawRect(Screen::Instance().GetWidth()/2, Screen::Instance().GetHeight()/2, 16, 16);
		
		Renderer::Instance().SetColor(0, 255, 0, 255);
		Renderer::Instance().DrawRect(Screen::Instance().GetMouseX(), Screen::Instance().GetMouseY(), 8, 8);

		Renderer::Instance().SetColor(0, 0, 255, 255);
		Renderer::Instance().DrawEllipse(circX, circY, 8, 8);


		// Refrescamos la pantalla
		Screen::Instance().Refresh();
		angle++;
	}
	
	return 0;
}
