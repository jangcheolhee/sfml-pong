#pragma once

enum class Axis
{
	Horizontal,
	Vertical,
	Vertical2,
};

struct AxisInfo
{
	Axis axis;
	std::list<int> positivies; // 1.f;
	std::list<int> negatives; // -1.f; 음수 출력 ex)좌

	float sensi = 1.f; // 증가 속도 / 감소 속도
	float value = 0.f; // 최대 증가 속도 / 최대 감소 속도

};

class InputMgr
{
private:
	static std::list<int> downKeys;
	static std::list<int> heldKeys;
	static std::list<int> upKeys;

	static std::unordered_map<Axis, AxisInfo> axisInfoMap;

public:
	static void Init();
	static void Clear();

	static void UpdateEvent(const sf::Event& ev);
	static void Update(float dt);

	static bool GetKeyDown(sf::Keyboard::Key key);
	static bool GetKeyUp(sf::Keyboard::Key key);
	static bool GetKey(sf::Keyboard::Key key);

	static bool Contains(const std::list<int>& list, int key);
	static void Remove(std::list<int>& list, int key);

	static float GetAxisRaw(Axis axis); // sensi
	static float GetAxis(Axis axis); //value
	
	//숙제
	static bool GetMouseButtonDown(sf::Mouse::Button button);
	static bool GetMouseButtonUp(sf::Mouse::Button button);
	static bool GetMouseButton(sf::Mouse::Button button);


	static sf::Vector2i GetMouseButton();

};

