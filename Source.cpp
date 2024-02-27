#include<iostream>
#include<cmath>
#include<SFML/Graphics.hpp>
#include<Windows.h>
using namespace std;

int main()
{
	//create the window:
	int window_x = 2560;
	int window_y = 1440;
	sf::RenderWindow window(sf::VideoMode(window_x, window_y), "Player movement and floor collision");
	window.setFramerateLimit(60);

	sf::CircleShape player(100.f);
	player.setFillColor(sf::Color::Red);
	player.setRadius(30.f);
	int circle_current_x = 10;
	int circle_current_y = window_y - 100;
	player.setPosition(sf::Vector2f(circle_current_x, circle_current_y));

	int half_of_window_y = window_y / 2;
	int half_of__half_of_window_y = half_of_window_y / 2;
	sf::RectangleShape floor1(sf::Vector2f((half_of__half_of_window_y) , 30));
	floor1.setFillColor(sf::Color::Green);
	floor1.setPosition(sf::Vector2f(0, window_y - 35));

	sf::RectangleShape floor2(sf::Vector2f((half_of__half_of_window_y) , 30));
	floor2.setFillColor(sf::Color::Green);
	floor2.setPosition(sf::Vector2f(half_of__half_of_window_y + 20, window_y - 85));



	float player_movement_speed = 10;
	float normalize_player_movement_speed = sqrt(pow(player_movement_speed, 2)) - 2;//a^2  +  b^2  =  c^2 //incomplete

	while (window.isOpen())
	{
		sf::Event event;  
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed  || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();
		}

		window.clear();
		window.draw(player);
		window.draw(floor1);
		window.draw(floor2);
		window.display();

		
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			circle_current_y -= normalize_player_movement_speed; //W
			circle_current_x += normalize_player_movement_speed; //D
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			circle_current_y -= normalize_player_movement_speed; //W
			circle_current_x -= normalize_player_movement_speed; //A
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			circle_current_y += normalize_player_movement_speed; //S
			circle_current_x += normalize_player_movement_speed; //D
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			circle_current_y += normalize_player_movement_speed; //S
			circle_current_x -= normalize_player_movement_speed; //A
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			circle_current_y -= player_movement_speed;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			circle_current_x -= player_movement_speed;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			circle_current_y += player_movement_speed;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			circle_current_x += player_movement_speed;
		//impliment space/jump
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			//int prev_circle_current_y = circle_current_y;

			circle_current_y -= 100;
			player.setPosition(sf::Vector2f(circle_current_x, circle_current_y));
			Sleep(1000);
			circle_current_y += 50;
		}
			
		
		//make it so player is always being forced down
		if (player.getGlobalBounds().top + 60 > floor1.getGlobalBounds().top)
			circle_current_y = floor1.getGlobalBounds().top - 60;

			
		player.setPosition(sf::Vector2f(circle_current_x, circle_current_y));

		//if (player.getGlobalBounds().intersects(floor1.getGlobalBounds()))
		//	return 0;
	}

	return 0;
}