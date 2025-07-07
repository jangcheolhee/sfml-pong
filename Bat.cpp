#include "stdafx.h"
#include "Bat.h"

Bat::Bat(const std::string& name)
	: GameObject(name)
{
}

Bat::~Bat()
{
}

void Bat::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	shape.setPosition(pos);
}

void Bat::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	shape.setRotation(rot);
}

void Bat::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	shape.setScale(s);
}

void Bat::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	shape.setOrigin(o);
}

void Bat::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	Utils::SetOrigin(shape, preset);
}


void Bat::Init()
{
	if (solo)
	{
		shape.setSize({100.f, 5.f});

	}
	else 
	{
		shape.setSize({ 5.f, 100.f });
	}
	shape.setFillColor(sf::Color::White);
	SetOrigin(Origins::BC);
}

void Bat::Release()
{
}

void Bat::Reset()
{
	if (solo)
	{
		sf::FloatRect bounds = FRAMEWORK.GetWindowBounds();
		SetPosition({ bounds.width * 0.5f, bounds.height - 20.f });
		sf::Vector2f size = shape.getSize();
		minX = bounds.left + size.x * 0.5f;
		maxX = (bounds.left + bounds.width) - size.x * 0.5f;
	}
	else
	{
		if (name == "Bat")
		{
			sf::FloatRect bounds = FRAMEWORK.GetWindowBounds();
			SetPosition({ bounds.width * 0.1f, bounds.height*.5f });
			sf::Vector2f size = shape.getSize();
			minY = bounds.top + size.y * 0.5f;
			maxY = (bounds.top + bounds.height) - size.y * 0.5f;
		}
		else
		{
			sf::FloatRect bounds = FRAMEWORK.GetWindowBounds();
			SetPosition({ bounds.width * 0.9f, bounds.height * .5f });
			sf::Vector2f size = shape.getSize();
			minY = bounds.top + size.y * 0.5f;
			maxY = (bounds.top + bounds.height) - size.y * 0.5f;
		}
	}
	
}

void Bat::Update(float dt)
{
	if (solo)
	{
		direction.x = InputMgr::GetAxisRaw(Axis::Horizontal);
		sf::Vector2f pos = GetPosition() + direction * speed * dt;
		pos.x = Utils::Clamp(pos.x, minX, maxX);
		SetPosition(pos);
	}
	else 
	{
		if (name == "Bat")
		{
			direction.y = InputMgr::GetAxisRaw(Axis::Vertical);
		}
		else
		{
			direction.y = InputMgr::GetAxisRaw(Axis::Vertical2);
		}
		sf::Vector2f pos = GetPosition() + direction * speed * dt;
		pos.y = Utils::Clamp(pos.y, minY, maxY);
		SetPosition(pos);
	}
}

void Bat::Draw(sf::RenderWindow& window)
{
	window.draw(shape);
}
