#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <ostream>

class GameObject 
{
public:
	GameObject()
	{}

	GameObject(std::string fileDir, int sizeX, int sizeY)
	{
		if (!objTexture.loadFromFile(fileDir, sf::IntRect(0, 0, sizeX, sizeY))) { //file loader
			std::cerr << "Error\n";
		}
		objSprite.setTexture(objTexture);
	}
	void draw(sf::RenderWindow &window) 
	{
		window.draw(objSprite); // Drawing an object in the window
	}

	void move(char direction, float movement)// Object Movement
	{ 
		if (direction == 'u')//up
		{ 
			objSprite.move(0, -movement);
		}
		if (direction == 'd')//down
		{ 
			objSprite.move(0, movement);
		}
		if (direction == 'l') // left
		{ 
			objSprite.move(-movement, 0);
		}
		if (direction == 'r') // right
		{ 
			objSprite.move(movement, 0);
		}
	}

	sf::FloatRect getGlobalBounds() { //global bounding of the entity
		return objSprite.getGlobalBounds();
	}

	float curLoc(char letter)  //getting location
	{
		if (letter == 'y') 
		{
			return objSprite.getPosition().y;
		}
		if (letter == 'x') 
		{
			return objSprite.getPosition().x;
		}
	}

	void setPosition(float x, float y) // Position of the object
	{ 
		objSprite.setPosition(x, y);
	}

	void setScale(float x, float y) // Scale of the object
	{
		objSprite.setScale(x, y);
	}

	void restrictToWindow(float screenW, float screenH, float sizeX, float sizeY) 
	{
		if (objSprite.getPosition().y >= screenH - sizeY) 
		{
			objSprite.setPosition(objSprite.getPosition().x, screenH - sizeY);
		}
		if (objSprite.getPosition().y <= 0) 
		{
			objSprite.setPosition(objSprite.getPosition().x, 0);
		}

		if (objSprite.getPosition().x >= screenW - sizeX) 
		{
			objSprite.setPosition(screenW - sizeX, objSprite.getPosition().y);

		}
		if (objSprite.getPosition().x <= 0) 
		{
			objSprite.setPosition(0, objSprite.getPosition().y);

		}
	}

private:

	sf::Texture objTexture;
	sf::Sprite objSprite;

};
