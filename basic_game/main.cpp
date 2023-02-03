#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>

#include "Physical.h"
#include "Controller.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "cubes", sf::Style::Titlebar | sf::Style::Close); //"Retario"
	window.setFramerateLimit(60);
	sf::Event event;
	sf::Clock clock;

	//Physical::gravityAcc = 0;// 9.81f; Vec2(6.94f, -6.94f);
	//Physical::gravityAcc.y = -9.81f;;
	Physical::setGravity(Vec2(0, -9.81f));
	GObject::pxlByMtr = 20;

	GObject ground(0, 0, 50, 2, true);
	GObject celling(0, 28, 50, 2, true);
	GObject RWall(38, 0, 2, 30, true);
	GObject LWall(0, 0, 1, 30, true);

	//Physical p1(Vec2(15, 7), Vec2(2, 2), true, 10, 0, true); //7->10
	//Physical p2(Vec2(19, 18), Vec2(2, 2), true, 10, 10, true);
	//Physical p3(Vec2(20, 3), Vec2(4, 4), true, 100, 10, true);

	for (int i = 0; i < 8; i++)
	{
		new Physical(Vec2(6 + ( 0.2f * (i%3) ), 2 + i * 2), Vec2(2, 2), true, 4, 0, true);
	}
	
	//Physical p3(Vec2(20, 13), Vec2(4, 4), true, 40, -10, true);
	//Physical p3(Vec2(20, 13), Vec2(2, 2), true, 10, 0, true);

	//Physical test1(Vec2(9, 8), Vec2(5, 5), true, 10, 0, true); test1.boyancy = 1;
	//Physical test2(Vec2(9, 11), Vec2(3, 3), true, 10, 0, false);
	//GObject test2(9, 11, 3, 3, true);

	//Controller player(Vec2(15, 20), Vec2(5, 20));

	//std::cout << p1.colidable.size() << std::endl;
	
	sf::err().rdbuf(NULL);
	clock.restart();

	bool setTrigger = false;
	Vec2 aimBegin;
	Vec2 aimEnd;

	while (window.isOpen())
	{
		window.clear(sf::Color::Cyan);
		constexpr float deltaT = 1 / 60.f;//clock.getElapsedTime().asSeconds(); clock.restart();
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				//aimEnd = Vec2(event.mouseMove.x, event.mouseMove.y);
				//if (event.key.code == sf::Keyboard::Space) p1.addVelocity(Vec2(5, 20));// 20));
				//if (event.key.code == sf::Keyboard::LControl) p2.addVelocity(Vec2(0,35));
				//if (event.key.code == sf::Keyboard::LShift) p3.addVelocity(Vec2(0, 5));
					//if (event.key.code == sf::Keyboard::A) player.move(-5 * deltaT);
				//else if (event.key.code == sf::Keyboard::D) player.move(5 * deltaT);
				
			}
			else if (event.type == sf::Event::MouseMoved)
			{
				aimEnd = Vec2(event.mouseMove.x, event.mouseMove.y);
				//std::cout << test2.pos.x << " --- " << test2.pos.y << " --- ";
				//test2.pos.x = event.mouseMove.x / GObject::pxlByMtr;
				//test2.pos.y = (window.getSize().y - event.mouseMove.y) / GObject::pxlByMtr;
			}
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				setTrigger = true;
				//aimBegin = Vec2{ (float) event.mouseButton.x, window.getSize().y - (float)event.mouseButton.y} / GObject::pxlByMtr;
				aimBegin = Vec2(event.mouseButton.x, event.mouseButton.y);
			}
			else if (event.type == sf::Event::MouseButtonReleased && setTrigger)
			{
				setTrigger = false;
				Vec2 aimEnd = Vec2{ (float) event.mouseButton.x, window.getSize().y - (float) event.mouseButton.y } / GObject::pxlByMtr;
				aimBegin = Vec2{ aimBegin.x, window.getSize().y - aimBegin.y } / GObject::pxlByMtr;
				new Physical(aimBegin, Vec2(2, 2), true, 10, aimEnd - aimBegin, true);
			}
			//else p1.velocity.x = 0;
		}
		if (setTrigger)
		{
			//if (event.type == sf::Event::MouseMoved) aimEnd = Vec2(event.mouseMove.x, event.mouseMove.y);

			sf::Vertex line[] =
			{
				sf::Vertex(aimBegin),
				sf::Vertex(aimEnd)// (event.mouseMove.x, event.mouseMove.y))
			};

			window.draw(line, 2, sf::Lines);
		}
		
		//p1.update(deltaT);
		//p3.updateC(deltaT);
		GObject::update(deltaT);
		GObject::drawAll(window);
		window.display();

		//std::cout << isHorizBound(&test2, &test1) << "\n";
		//otentialEnergy(p1);
		//::cout << " \t|--| " << p1.pos.x << "\n";
		/*std::cout << kineticEnergy(p2) + kineticEnergy(p3) + kineticEnergy(p1)
				  + potentialEnergy(p2) + potentialEnergy(p3) + potentialEnergy(p1) << " ||---|| ";
		
		std::cout << momentum(p2) + momentum(p3) + momentum(p3) << "\n";*/
	}
	return 0;
}


/*
known bugs:
1.speed keeps increasing even if object is standing "still" bug is pressend from oposide sides,
probably couse both object have velocity in one direction and new velocity also is in the same direction.
(tested when cubes were on each other from top to bottom: space, shift, ctrl)
*/

/*
TODO:
npos only to predict 00
pos actual movement  00

if physical touch solid, also get partialy solid
*/