#include "stdafx.h"
#include "SceneGame2.h"
#include "UiHud.h"
#include "Bat.h"
#include "Ball.h"
SceneGame2::SceneGame2()
	:Scene(SceneIds::Game)
{
}

SceneGame2::~SceneGame2()
{
}

void SceneGame2::Init()
{

	bat1 = (Bat*)AddGameObject(new Bat("Bat"));
	bat2 = (Bat*)AddGameObject(new Bat("Bat2"));
	ball = (Ball*)AddGameObject(new Ball("Ball"));
	ball->SetBat(bat1, bat2);
	
	fontIds.push_back("fonts/DS-DIGIT.ttf");
	uiHud = (UiHud*)AddGameObject(new UiHud());

	Scene::Init();
}

void SceneGame2::Enter()
{
	ballActive = false;
	
	Scene::Enter();
	score = 0;

	uiHud->SetScore(0);
	uiHud->SetShowMessage(true);
	uiHud->SetMessage("Space to Start!");
}

void SceneGame2::Update(float dt)
{
	Scene::Update(dt);
	if (!ballActive)
	{
		ball->SetPosition(bat1->GetPosition());
		if (InputMgr::GetKeyDown(sf::Keyboard::Space))
		{
			uiHud->SetShowMessage(false);
			ballActive = true;
			sf::Vector2f dir(1.f, -1.f);
			Utils::Normallize(dir);
			ball->Fire(dir, 500.f);
		}
	}
}
