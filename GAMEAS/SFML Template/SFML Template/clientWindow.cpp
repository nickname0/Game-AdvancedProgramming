#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "Loader.h"

void clientApp()
{
	int screenW = 200, screenH = 100;

	char lKey = charLoader("KeyBinds.txt", 1);
	char rKey = charLoader("KeyBinds.txt", 2);
	char uKey = charLoader("KeyBinds.txt", 3);
	char dKey = charLoader("KeyBinds.txt", 4);

	int port = 2000;

	char pressed;

	sf::TcpSocket socket;
	sf::Packet packet;
	sf::IpAddress ipAdd = stringLoader("ip.txt", 1);
	sf::Int32 send, receive;

	sf::RenderWindow window(sf::VideoMode(screenW, screenH), "Second Player Controller"); //screen size and name
	window.setFramerateLimit(60);

	//setting up tcp client
	socket.setBlocking(false);
	socket.connect(ipAdd, port);

	while (window.isOpen()) {
		sf::Event event;
		sf::Packet packet;
		while (window.pollEvent(event)) 
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		if (event.type == sf::Event::TextEntered) 
		{
			if (event.text.unicode < 128) 
			{
				pressed = static_cast<char>(event.text.unicode);
			}
			if (pressed == lKey) //left
			{
				send = 1;
			}
			else if (pressed == rKey) //right
			{
				send = 0;
			}
			else if (pressed == uKey) //up
			{
				send = 2;
			}
			else if (pressed == dKey) //down
			{
				send = 3;
			}
			else
			{
				send = 4;
			}
		}
		else {
			send = 4;
		}
		packet << send;
		socket.send(packet);

		receive = 4; 
		socket.receive(packet);//get data from server
		packet >> receive;

		window.clear(); //clear the whole thing, better to have it each frame

		window.display(); //display what is rendered to this moment
	}
	socket.disconnect(); //gracefully disconnecting when closing window
}
