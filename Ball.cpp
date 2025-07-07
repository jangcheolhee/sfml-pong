#include "stdafx.h"
#include "Ball.h"
#include "Bat.h"
#include "SceneGame.h"
#include "SceneGame2.h"

Ball::Ball(const std::string& name)
	:GameObject(name)
{
}

Ball::~Ball()
{
}

void Ball::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	cir.setPosition(pos);
}

void Ball::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	cir.setRotation(rot);
}

void Ball::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	cir.setScale(s);
}

void Ball::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	cir.setScale(o);
}

void Ball::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	Utils::SetOrigin(cir, preset);
}

std::string Ball::GetScore()
{
	return std::to_string(bat->GetScore()) + " : " + std::to_string(bat2->GetScore());
}

void Ball::Init()
{
	cir.setRadius(10.f);
	cir.setFillColor(sf::Color::Yellow);
	SetOrigin(Origins::BC);
	
}

void Ball::Release()
{
}

void Ball::Reset()
{
	if (bat2 == nullptr)
	{
		bat->SetMode(true);
		sf::FloatRect bounds = FRAMEWORK.GetWindowBounds();
		SetPosition({ bounds.width * 0.5f, bounds.height - 20.f });

		float radius = cir.getRadius();
		minX = bounds.left + radius;
		maxX = (bounds.left + bounds.width) - radius;

		minY = bounds.top + radius * 2.f;
		maxY = bounds.top + bounds.height + radius;

		direction = { 0.f, 0.f };
		speed = 0.f;
	}
	else 
	{
		sf::FloatRect bounds = FRAMEWORK.GetWindowBounds();
		SetPosition({ bounds.width * 0.5f, bounds.height - 20.f });

		float radius = cir.getRadius();
		minX = bounds.left + radius;
		maxX = (bounds.left + bounds.width) - radius;

		minY = bounds.top + radius * 2.f;
		maxY = bounds.top + bounds.height + radius;

		direction = { 0.f, 0.f };
		speed = 0.f;
	}
	
}

void Ball::Update(float dt)
{
	sf::Vector2f pos = GetPosition() + direction * speed * dt;
	if (bat2 == nullptr)
	{


		if (pos.x < minX)
		{
			pos.x = minX;
			direction.x *= -1.f;
		}
		else if (pos.x > maxX)
		{
			pos.x = maxX;
			direction.x *= -1.f;
		}
		if (pos.y < minY)
		{
			pos.y = minY;
			direction.y *= -1.f;
		}
		else if (pos.y > maxY)
		{
			if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Game)
			{
				(SceneGame*)SCENE_MGR.GetCurrentScene();
				scene->SetGameOver();
			}
		}

		if (bat != nullptr)
		{
			const sf::FloatRect& batBounds = bat->GetGlobalBounds();
			if (cir.getGlobalBounds().intersects(batBounds))
			{
				pos.y = batBounds.top;
				direction.y *= -1.f;
			}
		}
	}
	else
	{
		if (pos.y < minY)
		{
			pos.y = minY;
			direction.y *= -1.f;
		}
		else if (pos.y > maxY)
		{
			pos.y = maxY;
			direction.y *= -1.f;
		}
		if (pos.x < minX)
		{
			bat2->SetScore();
			if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Game2)
			{
				(SceneGame2*)SCENE_MGR.GetCurrentScene();
				scene2->SetGameOver();
			}

			
		}
		if (pos.x > maxX)
		{
			bat->SetScore();
			if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Game2)
			{
				(SceneGame2*)SCENE_MGR.GetCurrentScene();
				scene2->SetGameOver();
			}

		}
		if (bat != nullptr)
		{
			const sf::FloatRect& batBounds = bat->GetGlobalBounds();
			if (cir.getGlobalBounds().intersects(batBounds))
			{
				pos.x = batBounds.left +40;
				direction.x *= -1.f;
			}
		}
		if (bat2 != nullptr)
		{
			const sf::FloatRect& batBounds = bat2->GetGlobalBounds();
			if (cir.getGlobalBounds().intersects(batBounds))
			{
				pos.x = batBounds.left - 40;
				direction.x *= -1.f;
			}
		}
	}

	SetPosition(pos);



}

void Ball::Draw(sf::RenderWindow& window)
{
	window.draw(cir);
}

void Ball::Fire(const sf::Vector2f& d, float s)
{
	direction = d;
	speed = s;
}

