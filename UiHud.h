#pragma once
#include "GameObject.h"
class UiHud : public GameObject
{
protected:
	sf::Text textScore;
	sf::Text textMessage;
	
	std::string fontId;
	bool isShowMessage;
	// GameObject을(를) 통해 상속됨
public:
	UiHud(const std::string& name = "");
	~UiHud() override = default;
	//
	void SetScore(int score);
	void SetScore(int score1, int score2);
	void SetScorePosition(const sf::Vector2f pos);
	void SetScoreSize(int size);
	void SetMessage(const std::string& msg);
	void SetMessageSize(int size);
	void SetMessagePosition(const sf::Vector2f pos);
	void SetShowMessage(bool show) { isShowMessage = show; }


	//
	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

