#include "GenreState.h"

void GenreState::initFonts()
{
}

GenreState::GenreState(sf::RenderWindow* window, std::stack<State*>* states) : State (window, states)
{
	this->font.loadFromFile("Fonts/Blomberg.otf");
	
	this->initButtons();
	this->initText();

	//this->background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	//this->background.setFillColor(sf::Color::Magenta);
	if (!GenreTexture.loadFromFile("Resources/Genre.jpg"))
	{
		std::cout << "Unable to load from file.";
		system("pause");
	}
	GenreSprite.setTexture(GenreTexture);
	GenreSprite.setScale(0.8, 0.7);
}

GenreState::~GenreState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}

}

void GenreState::initButtons()
{
	this->buttons["AllGenre"] = new Button(600, 150, 150, 50, &this->font, "All Genre", sf::Color(220, 20, 60, 220),
		sf::Color(125, 237, 23, 155), sf::Color::White,25);
	this->buttons["Technology"] = new Button(600, 250, 150, 50, &this->font, "Technology", sf::Color(220, 20, 60, 220),
		sf::Color(125, 237, 23, 155), sf::Color::White,25);
	this->buttons["History"] = new Button(600, 350, 150, 50, &this->font, "History", sf::Color(220, 20, 60, 220),
		sf::Color(125, 237, 23, 155), sf::Color::White,25);
	this->buttons["Back"] = new Button(1100, 500, 80, 30, &this->font, "Back", sf::Color(10, 52, 99, 220),
		sf::Color(125, 237, 23, 155), sf::Color::White,25);
}

void GenreState::updateButtons()
{
	for (auto& it : buttons)
	{
		it.second->update(this->mousePosView);
	}
	//quit the state

	if (this->buttons["AllGenre"]->isPressed())
	{

		file.open("ProgramFile/files.dat", std::ios::out);
		if (file)
		{
			file << "Qns/allgenre.dat";
			file.close();
		}
		this->text2.setString("All Genre Selected");
		file.open("ProgramFile/highscorefile.dat", std::ios::out);
		if (file)
		{
			file << "Highscore/allgenrehighscore.txt";
			file.close();
		}
	}
	if (this->buttons["Technology"]->isPressed())
	{
		file.open("ProgramFile/files.dat", std::ios::out);
		if (file)
		{
			file << "Qns/tech.dat";
			file.close();
		}
		this->text2.setString("Technology Selected");
		file.open("ProgramFile/highscorefile.dat", std::ios::out);
		if (file)
		{
			file << "Highscore/techhighscore.txt";
			file.close();
		}
	}
	if (this->buttons["History"]->isPressed())
	{

		file.open("ProgramFile/files.dat", std::ios::out);
		if (file)
		{
			file << "Qns/history.dat";
			file.close();
		}
		this->text2.setString("History Selected");
		file.open("ProgramFile/highscorefile.dat", std::ios::out);
		if (file)
		{
			file << "Highscore/historyhighscore.txt";
			file.close();
		}
	}
	if (this->buttons["Back"]->isPressed())
	{
		this->states->pop();
	}
}

void GenreState::renderButtons(sf::RenderTarget* target)
{
	for (auto& it : buttons)
	{
		it.second->render(target);
	}
}

 void GenreState::initText()
{
	//this->text1.setFont(this->font);
	//this->text1.setString("Press esc to exit");
	//this->text1.setCharacterSize(15);
	//this->text1.setPosition(10, 10);
	//this->text1.setFillColor(sf::Color::White);

	this->text2.setFont(this->font);
	this->text2.setString("Select a Genre");
	this->text2.setCharacterSize(35);
	this->text2.setPosition(580, 50);
	this->text2.setFillColor(sf::Color::White);
}

void GenreState::renderText(sf::RenderTarget *target)
{
	//target->draw(this->text1);
	target->draw(this->text2);
}

void GenreState::endState()
{
}

void GenreState::updateInput(const float& dt)
{
	this->checkForQuit();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
	{
		this->states->pop();
	}
}

void GenreState::update(const float& dt)
{
	this->updateInput(dt);
	this->updateMousePosition();

	this->updateButtons();
}

void GenreState::render(sf::RenderTarget* target)
{
	if (!target)
		target = (this->window);

	target->draw(this->GenreSprite);

	this->renderButtons(target);
	this->renderText(target);
}
