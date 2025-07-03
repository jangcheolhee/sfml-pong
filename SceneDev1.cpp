#include "stdafx.h"
#include "SceneDev1.h"
#include "TextGo.h"

SceneDev1::SceneDev1()
	: Scene(SceneIds::Dev1)
{
}

void SceneDev1::Init()
{
	fontIds.push_back("fonts/DS-DIGIT.ttf");

	TextGo* go = new TextGo("fonts/DS-DIGIT.ttf");
	go->SetString("Dev 1");
	go->SetCharacterSize(30);
	go->SetFillColor(sf::Color::White);
	AddGameObject(go);

	textGo = new TextGo("fonts/DS-DIGIT.ttf");
	textGo->SetString("Dev 1");
	textGo->SetCharacterSize(30);
	textGo->SetFillColor(sf::Color::Red);
	AddGameObject(textGo);
	Scene::Init();
}

void SceneDev1::Update(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		SCENE_MGR.ChangeScene(SceneIds::Dev2);
	}
	if (InputMgr::GetMouseButtonDown(sf::Mouse::Button::Left))
	{
		std::cout << InputMgr::GetMousePostion().x << ", " << InputMgr::GetMousePostion().y << std::endl;
		textGo->sortingOrder = -1;
	}
	if (InputMgr::GetMouseButtonDown(sf::Mouse::Button::Right))
	{
		textGo->sortingOrder = 1;
	}
	sf::Vector2f dir;
	dir.x = InputMgr::GetAxisRaw(Axis::Horizontal);
	dir.y = InputMgr::GetAxisRaw(Axis::Vertical);

	sf::Vector2f pos = textGo->GetPosition();
	pos += dir * 100.f * dt;
	textGo->SetPosition(pos);

}
