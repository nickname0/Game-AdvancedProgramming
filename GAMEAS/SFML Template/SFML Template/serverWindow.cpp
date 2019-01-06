#include <iostream> //cout cin
#include <SFML/Graphics.hpp> //textures etc.
#include <SFML/Window.hpp> //keyboard, window events
#include <SFML/Network.hpp> // network
#include <string> //string
#include <stdlib.h>
#include "GameObject.h"
#include "Loader.h"
#include <fmod_studio.hpp> // audio
#include <fmod.hpp> // audio

void serverApp()
{

	//Getting the ScreenSize
	int screenW = intLoader("ScreenSize.txt", 1); // screenSize Width (x axis)
	int screenH = intLoader("ScreenSize.txt", 2); // screensize height (y axis)

	//Clock that was going to be used for the random Spawn of the boxes if i could make the boxArray working
	sf::Clock clock;
	float freq = 1.5f;

	//Getting the Different textures for the different game objects
	std::string playerTex = stringLoader("resources/Textures.txt", 1); //player Texture
	std::string boxTex = stringLoader("Textures.txt", 4); // 
	std::string platformTex = stringLoader("Textures.txt", 3); // middleLine texture
	std::string backGroundTex = stringLoader("Textures.txt", 5); // background texture

	//Getting the Keys for the movement
	char lKey = charLoader("KeyBinds.txt", 1); // key inputs
	char rKey = charLoader("KeyBinds.txt", 2); // key inputs
	char uKey = charLoader("KeyBinds.txt", 3);
	char dKey = charLoader("KeyBinds.txt", 4);

	// port value
	int port = 2000;

	//checking if button is pressed
	char pressed;

	// setting the speed values for the player and the box
	float playerSpeed = 6.0f;
	float player2Speed = 6.0f;
	float boxSpeed = 3.0f;

	sf::TcpSocket socket;  //Socket is used to recieve and send data
	sf::TcpListener listener;
	sf::Int32 send, receive; //

	int playerSizeX = 80, playerSizeY = 80; //player size restriction

	sf::RenderWindow window(sf::VideoMode(screenW, screenH), "Game"); //screen size and name
	window.setFramerateLimit(60); //setting the FPS


	//Creating the Sound System
	FMOD::Studio::System* system = NULL;
	FMOD::Studio::System::create(&system);

	if (system)
	{
		std::cout << "High-level (fmod studio) audio system created." << "\n";
	}


	FMOD::System* lowLevelSystem = NULL;
	system->getLowLevelSystem(&lowLevelSystem);

	if (lowLevelSystem)
	{
		std::cout << "Low-level (fmod) audio system created." << "\n";
	}

	lowLevelSystem->setSoftwareFormat(0, FMOD_SPEAKERMODE_STEREO, 0);
	system->initialize(1024, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, NULL);

	//Creating the background music that will loop nonstop when the terminal(.exe) is on
	FMOD::Sound* bgMusic = NULL;
	lowLevelSystem->createSound("music.ogg", FMOD_LOOP_NORMAL, NULL, &bgMusic);

	//Creating Collision sound that will play when player is hit by boxes
	FMOD::Sound* collSound = NULL;
	lowLevelSystem->createSound("scream.wav", FMOD_LOOP_OFF, NULL, &collSound);


	//Checking if the sound are loaded
	if (bgMusic)
	{
		std::cout << "Background Music loaded." << "\n";
	}
	if (collSound)
	{
		std::cout << "Collision sound loaded." << std::endl;
	}

	//Setting how fast the sounds would be
	bgMusic->setDefaults(16400, 0);
	collSound->setDefaults(50000, 0);

	//This is the API of the channel used in the playSound function
	FMOD::Channel* bgChannel = NULL;
	FMOD::Channel* collChannel = NULL;

	socket.setBlocking(false); //setting the blocking to false so will not gather data

	if (listener.listen(port) != sf::Socket::Done)
	{
		exit(EXIT_FAILURE);
	}
	if (listener.accept(socket) != sf::Socket::Done)
	{
		exit(EXIT_FAILURE);
	}


	//Creating of the gameObjects ( Textures(we got it from the Textures.txt), x sprite size , y sprite size)
	GameObject background(backGroundTex, 3000, 2000);
	GameObject player1(playerTex, playerSizeX, playerSizeY); //creates players and gets filename of the texture from the string and sets sprite size
	GameObject player2(playerTex, playerSizeX, playerSizeY); //creates players and gets filename of the texture from the string and sets sprite size
	GameObject box(boxTex, 100, 100); //creates the ball object and gives it the texture filename and texture size
	GameObject platform(platformTex, 1000, 24);

	GameObject boxArray[10];
	for (int i = 0; i < 10; i++)
	{
		boxArray[i].setScale(0.5f, 0.5f);
		boxArray[i].setPosition(screenW, screenH / 2);
	}

	GameObject box1(boxTex, 50, 50);
	GameObject box2(boxTex, 50, 50);
	GameObject box3(boxTex, 50, 50);
	GameObject box4(boxTex, 50, 50);
	GameObject box5(boxTex, 50, 50);
	GameObject box6(boxTex, 50, 50);
	GameObject box7(boxTex, 50, 50);
	GameObject box8(boxTex, 50, 50);
	GameObject box9(boxTex, 50, 50);
	GameObject box10(boxTex, 50, 50);

	// Scalling objects that need to be resized with this method the whole textures is working 
	box.setScale(0.5f, 0.5f);
	platform.setScale(2.0f, 1.0f);

	//Setting the postion of the game objects
	// Boxes are hardcoded because I could not make my boxArray working 
	background.setPosition(0, 0);
	player1.setPosition(0, screenH / 3);
	player2.setPosition(0, screenH);
	box.setPosition(screenW, screenH / 4);
	platform.setPosition(0, screenH / 2);
	box1.setPosition(screenW + 50, screenH / 5);
	box2.setPosition(screenW + 200, (screenH / 5) - 50);
	box3.setPosition(screenW + 350, screenH / 8);
	box4.setPosition(screenW + 50, screenH - 50);
	box5.setPosition(screenW + 150, screenH / 2.5f);
	box6.setPosition(screenW + 350, screenH / 1.5f);
	box7.setPosition(screenW + 500, screenH / 3.5f);
	box8.setPosition(screenW + 400, screenH / -150);
	box9.setPosition(screenW + 700, screenH / 3);
	box10.setPosition(screenW + 600, (screenH / 3) + 100);


	lowLevelSystem->playSound(bgMusic, NULL, false, &bgChannel); //Background Music
	 
    while (window.isOpen())
	{
        sf::Event event; //activating event system (used for detecting window close)
        sf::Packet packet; //creating a packet to be used for data transmission
        while (window.pollEvent(event)){ //checking for events
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) // checking event if the windows is closed by the X(top right of the app) or Esc
			{ 
                window.close(); //closing window
            }
        }
        window.clear(); //clear the window
        if (event.type == sf::Event::TextEntered)
		{
            if (event.text.unicode < 128) //checking if the key is in ASCII
			{ 
				pressed = static_cast<char>(event.text.unicode);
            }
            
            if(pressed == rKey)
			{
                player1.move('r', playerSpeed);
                send = 0; //setting the sending data to 0 if moving right
            }
			else if (pressed == lKey) //checking the key from the Keybinds.txt
			{

				player1.move('l', playerSpeed); //moving player with set speed
				send = 1;  // if the value is 1 the player will move left
			}
			else if (pressed == uKey)
			{
				playerSpeed = 6;
				player1.move('u', playerSpeed);
				send = 2; //setting to 2 if moving up
			}
			else if (pressed == dKey)
			{
				player1.move('d', playerSpeed);
				send = 3; //setiing to 3 if movng down
			}

			else
			{
				send = 4; //setting to 4 if nothing is happennings
			}
        }
		else 
		{
			send = 4;
		}

        packet << send; //adding data into packet
        socket.send(packet); //sending packet
		//Creating random int in the loop so the position of the box will be different each time
		int randomY = rand() % (screenH + 1);

		sf::FloatRect boxArrayBounds[10];

		for (int i = 0; i < 10; i++)
		{
			boxArrayBounds[i] = boxArray[i].getGlobalBounds();
		}
        
        
        //FloatRects are created nonstop because the players and the box are nonstop moving objects
       // This Bounds will be used later in the code for comparesing with each other
        sf::FloatRect player1Bounds = player1.getGlobalBounds(); 
        sf::FloatRect player2Bounds = player2.getGlobalBounds(); 
		sf::FloatRect platformBounds = platform.getGlobalBounds();

		sf::FloatRect boxBounds = box.getGlobalBounds(); 
		sf::FloatRect box1Bounds = box1.getGlobalBounds();
		sf::FloatRect box2Bounds = box2.getGlobalBounds();
		sf::FloatRect box3Bounds = box3.getGlobalBounds();
		sf::FloatRect box4Bounds = box4.getGlobalBounds();
		sf::FloatRect box5Bounds = box5.getGlobalBounds();
		sf::FloatRect box6Bounds = box6.getGlobalBounds();
		sf::FloatRect box7Bounds = box7.getGlobalBounds();
		sf::FloatRect box8Bounds = box8.getGlobalBounds();
		sf::FloatRect box9Bounds = box9.getGlobalBounds();
		sf::FloatRect box10Bounds = box10.getGlobalBounds();

		//My Player One Collision Detection
		// If the Box Bounds interfere with the player Bounds The player will move Back and will play a sound
        if(boxBounds.intersects(player1Bounds)||box1Bounds.intersects(player1Bounds)|| box2Bounds.intersects(player1Bounds)|| box3Bounds.intersects(player1Bounds)
			|| box4Bounds.intersects(player1Bounds)|| box5Bounds.intersects(player1Bounds)|| box6Bounds.intersects(player1Bounds)|| box7Bounds.intersects(player1Bounds)
			|| box8Bounds.intersects(player1Bounds)|| box9Bounds.intersects(player1Bounds)|| box10Bounds.intersects(player1Bounds)) //Collision detection
		{ 
			lowLevelSystem->playSound(collSound, NULL, false, &collChannel);
			player1.move('l', +3.0f);
        }

		//My Player Two Collision Detection
		
		if (boxBounds.intersects(player2Bounds) || box1Bounds.intersects(player2Bounds) || box2Bounds.intersects(player2Bounds) || box3Bounds.intersects(player2Bounds)
			|| box4Bounds.intersects(player2Bounds) || box5Bounds.intersects(player2Bounds) || box6Bounds.intersects(player2Bounds) || box7Bounds.intersects(player2Bounds)
			|| box8Bounds.intersects(player2Bounds) || box9Bounds.intersects(player2Bounds) || box10Bounds.intersects(player2Bounds)) //Collision detection
		{
			lowLevelSystem->playSound(collSound, NULL, false, &collChannel);
			player2.move('l', +3.0f);
		}

		//Reseting the box Position when they reach given X Axis Position

        if(box.curLoc('x') <-20) //When the box goes out of the given scope the box will reset with a random Y axis Position
		{ 
            box.setPosition(screenW, screenH/4);
        }
		if (box1.curLoc('x') < -40) 
		{
			box1.setPosition(screenW + 50, randomY);
		}
		if (box2.curLoc('x') < -40)
		{
			box2.setPosition(screenW + 50, randomY);
		}
		if (box3.curLoc('x') < -40)
		{
			box3.setPosition(screenW + 50, randomY);
		}
		if (box5.curLoc('x') < -80)
		{
			box5.setPosition(screenW + 100, randomY);
		}

		if (box8.curLoc('x') < -60)
		{
			box8.setPosition(screenW + 50, randomY);
		}


		//Bottom Side
		if (box4.curLoc('x') < -20)
		{
			box4.setPosition(screenW + 50, randomY);
		}
		if (box6.curLoc('x') < -20)
		{	   
			box6.setPosition(screenW + 50, randomY);
		}
		if (box7.curLoc('x') < -20)
		{	   
			box7.setPosition(screenW + 50, randomY);
		}
		if (box10.curLoc('x') < -20)
		{	   
			box10.setPosition(screenW + 50, randomY);
		}
		if (platformBounds.intersects(player1Bounds))
		{
			playerSpeed = 0;
		}
		if (platformBounds.intersects(player2Bounds))
		{
			player2Speed = 0;
		}
        
        box.move('l', boxSpeed); //moving box in the X axis
		box1.move('l', boxSpeed);
		box2.move('l', boxSpeed);
		box3.move('l', boxSpeed);
		box4.move('l', boxSpeed);
		box5.move('l', boxSpeed);
		box6.move('l', boxSpeed);
		box7.move('l', boxSpeed);
		box8.move('l', boxSpeed);
		box9.move('l', boxSpeed);
		box10.move('l', boxSpeed);

        socket.receive(packet); //pulling data from the client
        packet >> receive; //taking data from the packet recieved
       
		//Depending on the recieved value the player will move 
		if(receive == 1) //left
		{ 
			
            player2.move('l', player2Speed);       
        }
        if(receive == 0) //right
		{ 
			
			player2.move('r', player2Speed);
        }
		if (receive == 2) //up
		{
			player2.move('u', player2Speed);
		}
		if (receive == 3) //down
		{
			player2Speed = 6.0f;
			player2.move('d', player2Speed);
		}

		for (int i =0; i < 10; i++)
		{
			boxArray[i].draw(window);
		}


		//Giving a restrictions to the players
        player1.restrictToWindow(screenW/3, screenH, playerSizeX, playerSizeY); 
        player2.restrictToWindow(screenW/3, screenH+30, playerSizeX, playerSizeY);
		
		
		//Drawing all the objects

		background.draw(window);
		player1.draw(window); //drawing player 1
        player2.draw(window); //drawing player 2
		platform.draw(window); //Drawing platform

		//Drawing the boxes
		box.draw(window); 
		box1.draw(window); 
		box2.draw(window); 
		box3.draw(window); 
		box4.draw(window); 
		box5.draw(window); 
		box6.draw(window); 
		box7.draw(window); 
		box8.draw(window); 
		box9.draw(window); 
		box10.draw(window);

        
        window.display(); //updating screen
        //the drawing is dependant on the order, the earlier things stay behind the later drawing things (tiles are below players)
    }
	lowLevelSystem->playSound(bgMusic, NULL, true, &bgChannel);
}
