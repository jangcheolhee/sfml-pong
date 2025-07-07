#pragma once
#include "Scene.h"

class UiHud;
class Bat;
class Ball;

class SceneGame2 : public Scene
{
protected:
	UiHud* uiHud;
	Ball* ball;
	Bat* bat1;
	Bat* bat2;

	int score = 0;

	bool ballActive = true;
public:
	SceneGame2();
	~SceneGame2() override;

	void Init() override;
	void Enter() override;
	void Update(float dt) override;

	void SetGameOver();
};

