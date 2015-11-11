#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#pragma warning(disable: 4100)
#pragma warning(disable: 4710)
#pragma warning(disable: 4820)
#pragma warning(disable: 4996)

#include "../include/u-gine.h"

int main(int argc, char* argv[]) {
	Screen::Instance().Open(800, 600, false);
	
	double angle = 0;

	while ( Screen::Instance().IsOpened() && !Screen::Instance().KeyPressed(GLFW_KEY_ESC)) {
		//calc circle coords
		
		String title = String("Mouse coords = ");
		title += String("X(") + String::FromInt(Screen::Instance().GetMouseX()) + String(")") + String(",");
		title += String(" Y(") + String::FromInt(Screen::Instance().GetMouseY()) + String(")") + String("; ");
		title += String("Circle angle = ") + String::FromInt(angle);
		Screen::Instance().SetTitle(title);
		
		// TAREA: Pintar primitivas
		Renderer::Instance().Clear();
		Renderer::Instance().SetColor(255, 0, 0, 255);
		Renderer::Instance().DrawRect(Screen::Instance().GetWidth()/2, Screen::Instance().GetHeight()/2, 16, 16);
		
		Renderer::Instance().SetColor(0, 255, 0, 255);
		Renderer::Instance().DrawRect(Screen::Instance().GetMouseX(), Screen::Instance().GetMouseY(), 8, 8);

		Renderer::Instance().SetColor(0, 0, 255, 255);
		//Renderer::Instance().DrawEllipse(Screen::Instance().GetMouseX(), Screen::Instance().GetMouseY(), 8, 8);

		// Refrescamos la pantalla
		Screen::Instance().Refresh();
	}
	
	return 0;
}
