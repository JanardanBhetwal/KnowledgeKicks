#include "FinishState.h"
#include<cstring>
#include"MainMenuState.h"

FinishState::FinishState(sf::RenderWindow* window, std::stack<State*>* states) : State(window, states)
{
	this->font.loadFromFile("Fonts/PrintBold.otf");
	this->initText();

	if (!FTexture.loadFromFile("Resources/TotalScore.jpg"))
	{
		std::cout << "Unable to load from file.";
		system("pause");
	}
	FSprite.setTexture(FTexture);
	FSprite.setScale(0.8, 0.7);
}

FinishState::~FinishState()
{
	this->deleteButtons();
}

void FinishState::initText()
{
	this->text.setFont(this->font);
	this->text.setString("Quiz completed");
	this->text.setOrigin(this->text.getLocalBounds().width/2, this->text.getLocalBounds().height/2);
	this->text.setCharacterSize(40);
	this->text.setPosition(650, 300);
	this->text.setFillColor(sf::Color::White);

	file.open("ProgramFile/Score.dat", std::ios::in);
	if (file)
	{
		s << file.rdbuf();
		content = s.str();
	}
	std::string texty = "Your Score is ";
	texty = texty + content + " /10";
	
	this->text1.setFont(this->font);
	this->text1.setString(texty);
	this->text1.setOrigin(this->text.getLocalBounds().width/2, this->text.getLocalBounds().height/2);
	this->text1.setCharacterSize(40);
	this->text1.setPosition(650, 400);
	this->text1.setFillColor(sf::Color::White);


	this->buttons["Exit"] = new Button(650, 500, 250, 50, &this->font, "Exit", sf::Color::Red,
		sf::Color::Blue, sf::Color::White,40);
}

void FinishState::renderText(sf::RenderTarget *target)
{
	target->draw(this->text);
	target->draw(this->text1);
	target->draw(this->text2);
	target->draw(this->text3);
	for (auto& it : buttons)
	{
		it.second->render(target);
	}
}

void FinishState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		this->states->pop();
	}
	
}

void FinishState::updateButtons()
{
	for (auto& it : buttons)
	{
		it.second->update(this->mousePosView);
	}
	if (this->buttons["Exit"]->isPressed())
	{
		std::fstream question;
		int num = 1;
		question.open("ProgramFile/questionnumber.txt", std::ios::out);
		question << num;
		question.close();
		this->states->push(new MainMenuState(this->window, this->states));
	}
}

void FinishState::deleteButtons()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

void FinishState::update(const float& dt)
{
	this->updateInput(dt);
	this->updateMousePosition();
	this->updateButtons();	
}

void FinishState::render(sf::RenderTarget* target)
{
	if (!target)
		target = (this->window);
	target->draw(FSprite);
	this->renderText(target);
}
