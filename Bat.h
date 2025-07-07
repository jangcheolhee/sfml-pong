#pragma once
#include "GameObject.h"
class Bat : public GameObject
{
protected:
    sf::RectangleShape shape;
    float speed = 500.f;
    sf::Vector2f direction;

    float minX;
    float maxX;
    float minY;
    float maxY;
    bool solo = false;
public:
    Bat(const std::string& name);
    ~Bat() override;

    void SetPosition(const sf::Vector2f& pos) override;
    void SetRotation(float rot) override;
    void SetScale(const sf::Vector2f& s) override;
    void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;
    void SetMode(bool mode) { solo = mode; }

    void Init() override;
    void Release() override;
    void Reset() override;
    void Update(float dt) override;
    void Draw(sf::RenderWindow& window) override;

    sf::FloatRect GetGlobalBounds() { return shape.getGlobalBounds(); }
};

