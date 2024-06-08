#pragma once

#include<iostream>
#include<ctime>
#include<cstdlib>
#include<sstream>


#include<SFML\Graphics.hpp>
#include<SFML\Window.hpp>
#include<SFML\System.hpp>
#include<SFML\Audio.hpp>

enum button_states { BTN_IDLE=0, BTN_HOVER, BTN_PRESSED };

class Button
{
private:

	short unsigned buttonState;
	
	sf::RectangleShape shape;
	sf::Font* font;
	sf::Text text;
	int fontSize;

	sf::Color hoverColor, idleColor, activeColor;

public:
	Button(float x, float y, float width, float height, sf::Font* font,
		std::string text = "", sf::Color idleColor = sf::Color::White,
		sf::Color hoverColor = sf::Color::Black , sf::Color activeColor = sf::Color::Magenta,int fsize=15);
	virtual ~Button();

	//Accessor

	const bool isPressed() const;

	//function

	void update(const sf::Vector2f mousePos);
	void render(sf::RenderTarget* target);
};

