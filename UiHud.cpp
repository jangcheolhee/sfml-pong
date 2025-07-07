#include "stdafx.h"
#include "UiHud.h"

UiHud::UiHud(const std::string& name)
	:GameObject(name)
{
}

void UiHud::SetScore(int score)
{
	static std::string formatScore = "SCORE: ";
	textScore.setString(formatScore + std::to_string(score));
	Utils::SetOrigin(textScore, Origins::TL);
}
void UiHud::SetScore(int score1, int score2)
{
	
	textScore.setString(std::to_string(score1) + " : " + std::to_string(score2));
	Utils::SetOrigin(textScore, Origins::MC);
	textScore.setPosition({ 640,100 });
}

void UiHud::SetScorePosition(const sf::Vector2f pos)
{
	textScore.setPosition(pos);
}

void UiHud::SetScoreSize(int size)
{
	textScore.setCharacterSize(size);

}

void UiHud::SetMessage(const std::string& msg)
{
	textMessage.setString(msg);
	Utils::SetOrigin(textMessage, Origins::MC);
}

void UiHud::SetMessageSize(int size)
{
	textMessage.setCharacterSize(size);
	Utils::SetOrigin(textMessage, Origins::MC);

}

void UiHud::SetMessagePosition(const sf::Vector2f pos)
{
	textMessage.setPosition(pos);
}

void UiHud::Init()
{
	fontId = "fonts/DS-DIGIT.ttf";
	sf::FloatRect bounds = FRAMEWORK.GetWindowBounds();

	textScore.setCharacterSize(100);
	textScore.setFillColor(sf::Color::White);
	
	textMessage.setCharacterSize(100);
	textMessage.setFillColor(sf::Color::White);
	textMessage.setPosition(bounds.width * 0.5f, bounds.height * 0.5f);

}

void UiHud::Release()
{
}

void UiHud::Reset()
{
	textScore.setFont(FONT_MGR.Get(fontId));
	textMessage.setFont(FONT_MGR.Get(fontId));
	SetScore(0);
	isShowMessage = true;
}

void UiHud::Update(float dt)
{
}

void UiHud::Draw(sf::RenderWindow& window)
{
	window.draw(textScore);
	if (isShowMessage)
	{
		window.draw(textMessage);
		
	}
	

}
