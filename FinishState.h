#pragma once
#include "State.h"
#include <sstream>
#include "Button.h"

class FinishState :
    public State
{
private:
    sf::Text text, text1, text2, text3;
    std::stringstream s;
    std::string content;
    std::fstream file;
    sf::Font font;
    std::map<std::string, Button*> buttons;

    sf::Texture FTexture;
    sf::Sprite FSprite;

public:
    FinishState(sf::RenderWindow *window, std::stack<State*> *states);
    ~FinishState();

    void initText();
    void renderText(sf::RenderTarget *target);

    void updateInput(const float& dt);
    void updateButtons();
    void deleteButtons();

    void update(const float& dt);
    void render(sf::RenderTarget* target = NULL);
};

