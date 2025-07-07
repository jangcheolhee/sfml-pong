#pragma once
#include "Scene.h"

class UiHud;
class Bat;
class Ball;

class SceneGame2 : public Scene
{
protected:
	bool turn = true;
	UiHud* uiHud;
	Ball* ball;
	Bat* bat1;
	Bat* bat2;

	int score1 = 0;
	int score2 = 0;

	bool ballActive = true;
public:
	SceneGame2();
	~SceneGame2() override;

	void Init() override;
	void Enter() override;
	void Update(float dt) override;

	void SetGameOver();
};

