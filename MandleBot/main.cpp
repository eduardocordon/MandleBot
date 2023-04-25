// MandleBot.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "ComplexPlane.h"
#include <iostream>

using namespace std;
using namespace sf;

int main()
{
	float ratio;
	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;															////Get resulution
	ratio = resolution.x / resolution.y;

	RenderWindow window(VideoMode(resolution.x, resolution.y), "Mandelbrot", Style::Default);

	ComplexPlane View(ratio);

	Text text;																									//Text
	Font font;
	font.loadFromFile("fonts/KOMIKAP_.ttf");
	text.setFont(font);
	text.setCharacterSize(25);
	//text.setPosition(10, 10);
	text.setFillColor(Color::Black);

	VertexArray background;																						//vertex array
	background.setPrimitiveType(Points);
	background.resize(resolution.x * resolution.y);

	enum action{ CALCULATING,DISPLAYING};
	action now= CALCULATING;
	

	// The main game loop
	while (window.isOpen())
	{
		Vector2f coord,vcoord,pixelc;//maybe use?
		Vector2i mouseP,vmouseP;

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)                                                        //Close for red X 
			{
				window.close();
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape))                                               //ESC TO CLOSE
		{
			window.close();
		}

		if (event.type == sf::Event::MouseButtonPressed) {

			if (event.mouseButton.button == Mouse::Left) {
				View.zoomIn();
				mouseP = Mouse::getPosition(window);
				coord = window.mapPixelToCoords(mouseP);
				View.setCenter(coord);
				action now = CALCULATING;

			}

			if (event.mouseButton.button == Mouse::Left) {
				View.zoomOut();
				mouseP = Mouse::getPosition(window);
				coord = window.mapPixelToCoords(mouseP);
				View.setCenter(coord);
				action now = CALCULATING;

			}
		}

		if (event.type == sf::Event::MouseMoved) {
			vmouseP = Mouse::getPosition(window);
			vcoord = window.mapPixelToCoords(vmouseP);
			View.setMouseLocation(vcoord);
		}

																								//Update scene;
		if (now == CALCULATING) {
			for (float j = 0; j < resolution.x; j++) {
				for (float i = 0; i < resolution.y; i++) {
					background[j + i * 1].position = { (float)j,(float)i };						//pixelWidth,am not sure;
					pixelc.x = j;
					pixelc.y = i;
					View.countIterations(pixelc);//fix
					Uint8 r, g, b;
					View.iterationsToRGB(View.countIterations(pixelc), r, g, b);
					background[j + i * 1].color = { r,g,b };
					now = DISPLAYING;
					View.loadText(text);
				}
			}
		}

		//draw
		window.clear();
		window.draw(background);
		window.draw(text);
		window.display();

	}


}

