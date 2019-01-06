#pragma once

#include <fstream>
#include <string>
#include <iostream>
#include <ostream>

char charLoader(std::string filepath, int posN) //used for keybinds
{ 
	char pos1, pos2, pos3,pos4; // position of the values in the filepath
	std::ifstream values(filepath);
	if (values) 
		values >> pos1 >> pos2>>pos3>>pos4;
	if (posN == 1)
		return pos1;
	else if (posN == 2)
		return pos2;
	else if (posN == 3)
		return pos3;
	else if (posN == 4)
		return pos4;
};

std::string stringLoader(std::string filepath, int posN) //used for the textures
{ 
	std::string pos1, pos2, pos3, pos4, pos5;
	std::ifstream values(filepath);
	if (values)
		values >> pos1 >> pos2 >> pos3>>pos4>>pos5;
	if (posN == 1)
		return pos1;
	else if (posN == 2)
		return pos2;
	else if (posN == 3)
		return pos3;
	else if (posN == 4)
		return pos4;
	else if (posN == 5)
		return pos5;
};

int intLoader(std::string filepath, int posN) //used for the screen size
{
	int pos1, pos2;
	std::ifstream values(filepath);
	if (values) 
		values >> pos1 >> pos2;
	if (posN == 1) 
		return pos1;
	else if (posN == 2)
		return pos2;
};
