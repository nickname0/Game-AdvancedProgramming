#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <TGUI/TGUI.hpp>
#include <fstream>
#include <ostream>
#include <string>
#include <cstring>
#include <sstream>
#include "serverWindow.cpp"
#include "clientWindow.cpp"
#include "fmod_studio.h"


char connection;

void server() {
	connection = 's';
}
void client() {
	connection = 'c';
}
void exitG()
{
	connection = 'e';
}

int main() {
	sf::RenderWindow window{ {400, 200}, "Server/Client" }; //size of the Gui window
	tgui::Gui gui{ window }; // Create the gui and attach it to the window
	window.setPosition(sf::Vector2i(750, 500)); // Position of the Gui window
	window.setFramerateLimit(60);

	tgui::Button::Ptr serverB = tgui::Button::create(); // Creating button
	serverB->setPosition(40, 50); // setting the position
	serverB->setSize(100, 50); // setting the size
	serverB->setText("Server"); // setting the text 
	serverB->connect("pressed", server); //setting what the button will do
	serverB->connect("pressed", [&]() { window.close(); }); 
	gui.add(serverB); // adding the button in the Gui window

	tgui::Button::Ptr clientB = tgui::Button::create();
	clientB->setPosition(260, 50);
	clientB->setSize(100, 50);
	clientB->setText("Client");
	clientB->connect("pressed", client);
	clientB->connect("pressed", [&]() { window.close(); });
	gui.add(clientB);

	tgui::Button::Ptr exitB = tgui::Button::create();
	exitB->setPosition(175, 100);
	exitB->setSize(50, 50);
	exitB->setText("Exit");
	exitB->connect("pressed", exitG);
	exitB->connect("pressed", [&]() { window.close(); });
	gui.add(exitB);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			gui.handleEvent(event); // Pass the event to the widgets
		}
		window.clear();
		gui.draw(); // Draw all widgets
		window.display();
	}
	if (connection == 's') 
	{
		serverApp();
	}
	else if (connection == 'c') 
	{
		clientApp();
	}
	else 
	{
		std::cout << "exit" << std::endl;
		window.close();
	}
	return 0;
}
