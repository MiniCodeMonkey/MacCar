/*
 *  Main.cpp
 *  MacCar2
 *
 *  Created by Mathias Hansen on 11/10/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "Main.h"

void Main::Init()
{
	// Create main window
	App = new sf::RenderWindow(sf::VideoMode(800, 600), "Mac Car");
	
	// Load media manager
	mediaManager = new MediaManager();
	mediaManager->Play();
	
	// Load main scene
	currentScene = new Scene_Main();
	currentScene->Preload(this);
}

Main::Main()
{
	done = false;
	this->Init();
}

void Main::Run()
{
	while (App.IsOpened())
    {
		mediaManager->Tick();
		
		sf::Event Event;
        while (App.GetEvent(Event))
        {
            currentScene->HandleEvents(Event);
			
            if (Event.Type == sf::Event::Closed)
                App.Close();
        }
		
		currentScene->Draw();
		
		App.Display();
	}
}

void Main::SetScene(Scene *scene)
{	
	scene->Preload(this);
	currentScene = scene;
}

Main::~Main()
{
	//Mix_CloseAudio();
	SDL_Quit();
}

int main(int argc, char *argv[])
{
	Main *main = new Main();
	main->Run();
	
	return 0;
}
