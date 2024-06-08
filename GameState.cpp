#include "GameState.h"
#include<iomanip>

GameState::GameState(sf::RenderWindow* window, std::stack<State*>* states)
	: State(window, states)
{
	this->background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	this->background.setFillColor(sf::Color(128, 128, 128, 255));

	this->font.loadFromFile("Fonts/Blomberg.otf");
	this->initGui();
	this->initText();

	//buttons
	file.open("ProgramFile/files.dat", std::ios::in);
	if (file)
	{
		std::stringstream buffer;
		buffer << file.rdbuf();
		str = buffer.str();
		file.close();
	}
	this->askQuestion(file, q);	
}

GameState::~GameState()
{
	this->deleteButtons();
}

void GameState::initButtons()
{
	this->buttons["OptionA"] = new Button(300, 300, 350, 70, &this->font, q.getOptionA() , sf::Color(220, 20, 60, 220),
		sf::Color(125, 237, 23, 155), sf::Color::White,30);
	this->buttons["OptionB"] = new Button(700, 300, 350, 70, &this->font, q.getOptionB(), sf::Color(220, 20, 60, 220),
		sf::Color(125, 237, 23, 155), sf::Color::White,30);
	this->buttons["OptionC"] = new Button(300, 400, 350, 70, &this->font, q.getOptionC(), sf::Color(220, 20, 60, 220),
		sf::Color(125, 237, 23, 155), sf::Color::White,30);
	this->buttons["OptionD"] = new Button(700, 400, 350, 70, &this->font, q.getOptionD(), sf::Color(220, 20, 60, 220),
		sf::Color(125, 237, 23, 155), sf::Color::White,30);
	this->buttons["Back"] = new Button(1100, 500, 80, 30, &this->font, "Back", sf::Color(10, 52, 99, 220),
		sf::Color(125, 237, 23, 155), sf::Color::White, 25);
}

void GameState::updateButtons()
{
	for (auto& it : buttons)
	{
		it.second->update(this->mousePosView);
	}
	if (this->buttons["OptionA"]->isPressed())
	{
		opt = 'a';
		this->verifyAnswer(file, q);
	}
	if (this->buttons["OptionB"]->isPressed())
	{
		opt = 'b';
		this->verifyAnswer(file, q);
	}
	if (this->buttons["OptionC"]->isPressed())
	{
		opt = 'c';
		this->verifyAnswer(file, q);
	}
	if (this->buttons["OptionD"]->isPressed())
	{
		opt = 'd';
		this->verifyAnswer(file, q);
	}
	if (this->buttons["Back"]->isPressed())
	{
		this->states->pop();
	}
}

void GameState::renderButtons(sf::RenderTarget* target)
{
	for (auto& it : buttons)
	{
		it.second->render(target);
	}
}

void GameState::deleteButtons()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

void GameState::initText()	
{


	this->text.setFont(this->font);
	/*this->text.setString("Load qn from file");*/
	this->text.setCharacterSize(40);	
	this->text.setPosition(650, 200);
	this->text.setFillColor(sf::Color::White);

	/*this->text1.setFont(this->font);
	this->text1.setString("Press esc to exit");
	this->text1.setCharacterSize(15);
	this->text1.setPosition(10, 10);
	this->text1.setFillColor(sf::Color::White);*/
}

void GameState::renderText(sf::RenderTarget* target)
{
	target->draw(this->text);
	//target->draw(this->text1);
}

void GameState::initGui()
{
	GameTexture.loadFromFile("Resources/QN1.jpg");
	GameSprite.setTexture(GameTexture);
	//GameSprite.setColor( sf::Color(67.8, 84.7, 90.2,250));
	GameSprite.setScale(sf::Vector2f(0.8f, 0.6f));	
}

void GameState::renderGui(sf::RenderTarget* target)
{
	target->draw(GameSprite);
	//target->draw(this->brain);
}

void GameState::askQuestion(std::fstream &file, Question &q)
{
		i = getQnNumber();
		setQnNumber();
		file.open(str, std::ios::in | std::ios::binary);
		file.seekp((i - 1) * sizeof(q));

		file.read(reinterpret_cast<char*>(&q), sizeof(Question));

		this->text.setString(q.getQuestion());

		this->setQuestionPos();

		this->initButtons();
}

void GameState::setQuestionPos()
{
	sf::FloatRect position;
	position = this->text.getLocalBounds();
	std::cout << position.width << " " << position.height;
	this->text.setOrigin(position.width / 2, position.height/2);
}

void GameState::verifyAnswer(std::fstream& file, Question& q)
{
	if (q.getCorrectOption() == opt)
	{
		++j;
	}
	this->setOption();
	//this->deleteButtons();
	this->file.close();
	this->states->push(new FeedbackState(this->window, this->states));
	if (i == 10)
	{
		file.open("ProgramFile/Score.dat", std::ios::out);
		if (file)
		{
			std::cout << j;
			file << j;
			file.close();
		}
		ScoreCompare s;
		s.compareScore(j);
		this->states->push(new FinishState(this->window, this->states));
	}
	else
	this->askQuestion(file, q);
}

int GameState::getQnNumber()
{
	std::fstream question;
	std::stringstream buffer;
	std::string number;
	question.open("ProgramFile/questionnumber.txt", std::ios::in);
	buffer << question.rdbuf();
	number = buffer.str();
	question.close();
	return std::stoi(number);
}

void GameState::setQnNumber()
{
	std::fstream question;
	std::stringstream buffer;
	std::string number;
	question.open("ProgramFile/questionnumber.txt", std::ios::in);
	buffer << question.rdbuf();
	number = buffer.str();
	int num = std::stoi(number);
	question.close();
	
	num++;
	question.open("ProgramFile/questionnumber.txt", std::ios::out);
	question << num;
	question.close();
}

void GameState::setOption()
{
	std::fstream option;
	option.open("ProgramFile/chosenoption.txt", std::ios::out);
	option << opt;
	option.close();
}

void GameState::updateInput(const float& dt)
{
	this->checkForQuit();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
	{
		this->endstate();
	}
	//update inputs of player
}

void GameState::update(const float& dt)
{
	this->updateInput(dt);
	this->updateMousePosition();
	this->updateButtons();
	//if (end == 1)
	//{
	//	this->states->pop();
	//}
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
	target = (this->window);
	
	target->draw(GameSprite);
	this->renderText(target);
	this->renderButtons(target);
	
}

void GameState::endstate()
{
	std::fstream question;
	int num = 1;
	question.open("ProgramFile/questionnumber.txt", std::ios::out);
	question << num;
	question.close();
	this->states->pop();
}

