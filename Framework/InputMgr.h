#pragma once
enum class Axis 
{
	Horizontal,
	Vertical,
};
struct AxisInfo
{
	Axis axis;
	std::list <int> positives;
	std::list <int> negatives;

	float sinsi = 10.f;
	float value = 0.f;


};

class InputMgr
{
private:
	static std::list<int> downKeys;
	static std::list<int> heldKeys;
	static std::list<int> upKeys;

	//static sf::Mouse::Button downBtn;
	//static sf::Mouse::Button upBtn;
	//static sf::Mouse::Button heldBtn;

	static std::unordered_map<Axis, AxisInfo> axisInfoMap;


public:
	static void Init();
	static void Clear();

	static void UpdateEvent(const sf::Event& ev);
	static void Update(float dt);

	static bool GetKeyDown(sf::Keyboard::Key key);
	static bool GetKeyUp(sf::Keyboard::Key key);
	static bool GetKey(sf::Keyboard::Key key);

	static bool Contains(const std::list<int>& list, int code);
	static void Remove(std::list<int>& list, int code);

	static float GetAxisRaw(Axis axis);
	static float GetAxis(Axis axis);

	static bool GetMouseButtonDown(sf::Mouse::Button btn);
	static bool GetMouseButtonUp(sf::Mouse::Button btn);
	static bool GetMouseButton(sf::Mouse::Button btn);
	static int GetMouse(sf::Mouse::Button btn) { return btn + sf::Keyboard::KeyCount; }

	static sf::Vector2i GetMousePostion();
};


