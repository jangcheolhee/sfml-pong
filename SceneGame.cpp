#include "stdafx.h"
#include "SceneGame.h"
#include "Bat.h"
#include "Ball.h"
#include "UiHud.h"

SceneGame::SceneGame()
	:Scene(SceneIds::Game)
{
}

SceneGame::~SceneGame()
{
}

void SceneGame::Init()
{
	fontIds.push_back("fonts/DS-DIGIT.ttf");

	bat = (Bat*)AddGameObject(new Bat("Bat"));
	ball = (Ball*)AddGameObject(new Ball("Ball"));
	ball->SetBat(bat);
	uiHud = (UiHud*)AddGameObject(new UiHud());

	Scene::Init();
}

void SceneGame::Enter()
{
	ballActive = false;



	Scene::Enter();
	score = 0;

	uiHud->SetScore(0);
	uiHud->SetShowMessage(true);
	uiHud->SetMessage("Space to Start!");
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);
	if (!ballActive)
	{
		ball->SetPosition(bat->GetPosition());
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

void SceneGame::SetGameOver()
{
	SCENE_MGR.ChangeScene(SceneIds::Game);
}
