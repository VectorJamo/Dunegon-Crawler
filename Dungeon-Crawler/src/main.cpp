#include "Application.h"

#include "application/tilemap/MapConstants.h"

int main()
{
	Application* app = Application::CreateApplication(MapConstants::ScreenWidth, MapConstants::ScreenHeight, "Dungeon Crawler");
	app->Run();

	delete app;

	return 0;
}
