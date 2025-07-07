#include "stdafx.h"
#include "InputMgr.h"

std::list<int> InputMgr::downKeys;
std::list<int> InputMgr::heldKeys;
std::list<int> InputMgr::upKeys;
std::unordered_map<Axis, AxisInfo> InputMgr::axisInfoMap;

void InputMgr::Init()
{
	AxisInfo infoH;
	infoH.axis = Axis::Horizontal;
	infoH.positivies.push_back(sf::Keyboard::Right);
	infoH.positivies.push_back(sf::Keyboard::D);
	infoH.negatives.push_back(sf::Keyboard::Left);
	infoH.negatives.push_back(sf::Keyboard::A);
	axisInfoMap.insert({ Axis::Horizontal, infoH });

	AxisInfo infoV;
	infoV.axis = Axis::Vertical;
	infoV.positivies.push_back(sf::Keyboard::S);
	
	infoV.negatives.push_back(sf::Keyboard::W);
	
	axisInfoMap.insert({ Axis::Vertical, infoV });

	AxisInfo infoV2;
	infoV2.axis = Axis::Vertical2;
	
	infoV2.positivies.push_back(sf::Keyboard::Down);
	infoV2.negatives.push_back(sf::Keyboard::Up);
	axisInfoMap.insert({ Axis::Vertical2, infoV2 });
}

void InputMgr::Clear() 
{
	downKeys.clear();
	upKeys.clear();
}

void InputMgr::UpdateEvent(const sf::Event& ev) 
{
	switch (ev.type)
	{
	case sf::Event::KeyPressed:
		if (!Contains(heldKeys, ev.key.code))
		{
			downKeys.push_back(ev.key.code);
			heldKeys.push_back(ev.key.code);
		}
		break;

	case sf::Event::KeyReleased:
		Remove(heldKeys, ev.key.code);
		upKeys.push_back(ev.key.code);
		break;

	case sf::Event::MouseButtonPressed:
		if (!Contains(heldKeys, sf::Keyboard::KeyCount + ev.mouseButton.button))
		{
			int code = sf::Keyboard::KeyCount + ev.mouseButton.button;
			downKeys.push_back(code);
			heldKeys.push_back(code);
		}
		break;

	case sf::Event::MouseButtonReleased:
		int code = sf::Keyboard::KeyCount + ev.mouseButton.button;
		Remove(heldKeys, code);
		upKeys.push_back(code);
		break;
	}
}

void InputMgr::Update(float dt) 
{
	sf::Mouse::getPosition(FRAMEWORK.GetWindow());

	for (auto& pair : axisInfoMap)
	{
		AxisInfo& axisInfo = pair.second;
		float raw = GetAxisRaw(axisInfo.axis); // -1, 0, 1
		float dir = raw;
		if (raw == 0.f && axisInfo.value != 0.f)
		{
			dir = axisInfo.value > 0.f ? -1.f : 1.f;
		}
		axisInfo.value += dir * axisInfo.sensi * dt;
		axisInfo.value = Utils::Clamp(axisInfo.value, -1.f, 1.f);

		//std::abs float형의 절대값을 구해준다.
		float stopThreshold = std::abs(dir * axisInfo.sensi * dt);
		if (raw == 0.f && std::abs(axisInfo.value) < stopThreshold)
		{
			axisInfo.value = 0.f;
		}
	}

}

bool InputMgr::GetKeyDown(sf::Keyboard::Key key)
{
	return Contains(downKeys, key);
}

bool InputMgr::GetKeyUp(sf::Keyboard::Key key)
{
	return Contains(upKeys, key);
}

bool InputMgr::GetKey(sf::Keyboard::Key key)
{
	return Contains(heldKeys, key);
}

bool InputMgr::Contains(const std::list<int>& list, int key)
{
	return std::find(list.begin(), list.end(), key) != list.end();
}

void InputMgr::Remove(std::list<int>& list, int key)
{
	list.remove(key);
}

float InputMgr::GetAxisRaw(Axis axis)
{
	auto findIt = axisInfoMap.find(axis);
	if (findIt == axisInfoMap.end())
	{
		return 0.f;
	}
	const AxisInfo& axisInfo = findIt->second;
	
	auto it = heldKeys.rbegin();
	while (it != heldKeys.rend())
	{
		int code = *it;
		if (Contains(axisInfo.positivies, code))
		{
			return 1.f;
		}
		if (Contains(axisInfo.negatives, code))
		{
			return -1.f;
		}
		++it;
	}
	return 0.0f;
}

float InputMgr::GetAxis(Axis axis)
{
	auto findIt = axisInfoMap.find(axis);
	if (findIt == axisInfoMap.end())
	{
		return 0.f;
	}

	return findIt->second.value;
}

bool InputMgr::GetMouseButtonDown(sf::Mouse::Button button)
{
	int code = sf::Keyboard::KeyCount + button;
	return Contains(downKeys, code);
}

bool InputMgr::GetMouseButtonUp(sf::Mouse::Button button)
{
	int code = sf::Keyboard::KeyCount + button;
	return Contains(upKeys, code);
}

bool InputMgr::GetMouseButton(sf::Mouse::Button button)
{
	int code = sf::Keyboard::KeyCount + button;
	return Contains(heldKeys, code);
}

sf::Vector2i InputMgr::GetMouseButton()
{
	return sf::Mouse::getPosition(FRAMEWORK.GetWindow());
}

