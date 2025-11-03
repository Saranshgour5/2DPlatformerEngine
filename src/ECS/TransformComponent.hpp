#ifndef TRANSFORMCOMPONENT_HPP
#define TRANSFORMCOMPONENT_HPP	

#include "../Vector2D.hpp"
#include "ECS.hpp"

class TransformComponent: public ECS::Component 
{
public:
	Vector2D position {};
	Vector2D velocity {};
	Vector2D accelaration {};
	int height{32};
	int width{32};
	int scale{1};

	int speed{3};
	
	bool blocked{false};

	TransformComponent()
	{
		position.Zero();
	}

	TransformComponent(int sc)
	{
		position.Zero();
		scale = sc;
	}

	TransformComponent(float mX, float mY)
	{
		position.x = mX;
		position.y = mY;
	}

	TransformComponent(float x, float y, int h, int w, int sc)
	{
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = sc;
	}

	void init() override
	{
		velocity.Zero();
		accelaration.Zero();
	}

	void update(float mFT) override
	{
		//position.x += static_cast<int>(velocity.x * speed * mFT);
		//position.y += static_cast<int>((velocity.y * speed + accelaration.y / 2) * mFT);
	}

};
#endif
