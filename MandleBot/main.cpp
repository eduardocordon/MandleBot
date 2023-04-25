// MandleBot.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "ComplexPlane.h"
#include <iostream>
#include <complex>      // std::complex, std::abs

using namespace std;
using namespace sf;

int main()
{
	float ratio;
	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;															////Get resulution
	ratio = resolution.y / resolution.x;

	RenderWindow window(VideoMode(resolution.x, resolution.y), "Mandelbrot", Style::Default);

	ComplexPlane View(ratio);//rename

	Text text;																									//Text
	Font font;
	font.loadFromFile("fonts/KOMIKAP_.ttf");
	text.setFont(font);
	text.setCharacterSize(25);
	text.setPosition(50, 50);
	text.setFillColor(Color::Red);

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
			if (event.type == sf::Event::MouseButtonPressed) {

				if (event.mouseButton.button == Mouse::Left) {
					View.zoomIn();

					coord = window.mapPixelToCoords(Mouse::getPosition() , View.getView());
					/*mouseP = Mouse::getPosition(window);
					coord = window.mapPixelToCoords(mouseP);
					*/
					View.setCenter(coord);
					now = CALCULATING;
					

				}

				if (event.mouseButton.button == Mouse::Right) {
					View.zoomOut();
					coord = window.mapPixelToCoords(Mouse::getPosition(), View.getView());
					//mouseP = Mouse::getPosition(window);
					//coord = window.mapPixelToCoords(mouseP);
					View.setCenter(coord);
					now = CALCULATING;

				}
			}

			if (event.type == sf::Event::MouseMoved) {
				//vmouseP = Mouse::getPosition(window);
				//vcoord = window.mapPixelToCoords(vmouseP);
				vcoord = window.mapPixelToCoords(Mouse::getPosition(), View.getView());
				View.setMouseLocation(vcoord);
			}

		}

		if (Keyboard::isKeyPressed(Keyboard::Escape))                                               //ESC TO CLOSE
		{
			window.close();
		}

		

																								//Update scene;
		if (now == CALCULATING) {
			for (float j = 0; j < resolution.x; j++) {
				for (float i = 0; i < resolution.y; i++) {
					background[j + i * resolution.x].position = { (float)j,(float)i };						//pixelWidth,am not sure;
					float counter = 0;
					Vector2i coord(j, i);
					Vector2f worldCord;
					worldCord = window.mapPixelToCoords(coord,View.getView());

					counter = View.countIterations(worldCord);//fix
					Uint8 r, g, b;
					View.iterationsToRGB(counter, r, g, b);
					background[j + i * resolution.x].color = { r,g,b };
					
			
				}

			}
			now = DISPLAYING;
		}

		//draw
		//window.setView(View.getView());
		View.loadText(text);
		window.clear();
		window.draw(background);
		window.draw(text);
		window.display();

	}


}

