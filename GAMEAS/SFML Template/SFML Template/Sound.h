#pragma once
#include <iostream>
#include <fmod_studio.hpp>
#include <fmod.hpp>
#include <string>

class Sound
{
	Sound()
	{}
	Sound(std::string filename)
	{

	}


private:
	FMOD::Studio::System* system = NULL;
	FMOD::System* lowLevelSystem = NULL;
	FMOD::Sound* meow = NULL;
	FMOD::Channel* catChannel = NULL;
	
};