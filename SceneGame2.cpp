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
	

	uiHud->SetScore(bat1->GetScore(), bat2->GetScore());
	uiHud->SetShowMessage(true);
	uiHud->SetMessage("Space to Start!");
}

void SceneGame2::Update(float dt)
{
	Scene::Update(dt);
	if (!ballActive)
	{
		uiHud->SetScore(bat1->GetScore(), bat2->GetScore());
		if (turn)
		{
			sf::Vector2f pos = bat1->GetPosition();
			pos.y -= 50;
			pos.x += 20;
			ball->SetPosition(pos);
		}
		else 
		{
			sf::Vector2f pos = bat2->GetPosition();
			pos.y -= 50;
			pos.x -= 20;
			ball->SetPosition(pos);
		}
		if (InputMgr::GetKeyDown(sf::Keyboard::Space))
		{
			uiHud->SetShowMessage(false);
			ballActive = true;
			sf::Vector2f dir(1.f, Utils::RandomRange(0,2) == 1 ? 1.f : -1.f);
			Utils::Normallize(dir);
			ball->Fire(dir, 500.f);
			turn = !turn;
		}
		if (bat1->GetScore() == 10 || bat2->GetScore() == 10)
		{
			uiHud->SetMessage("Game End");

		}
	}
}
void SceneGame2::SetGameOver()
{
	SCENE_MGR.ChangeScene(SceneIds::Game2);
}
