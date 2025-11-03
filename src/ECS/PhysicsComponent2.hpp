#ifndef PHYSICSCOMPONENT_HPP2
#define PHYSICSCOMPONENT_HPP2

#include "ECS.hpp"
#include "TransformComponent.hpp"


struct PhysicsResolver
{
public:
	virtual ~PhysicsResolver() { };
	virtual void update(float mfT, ECS::Entity* entity, ECS::Manager& manager) = 0;
};

class PhysicsComponent2 : public ECS::Component
{
	ECS::Manager& manager;
	PhysicsResolver* physics;	
	TransformComponent* transform;

public:
	PhysicsComponent2(ECS::Manager& mManager, PhysicsResolver* mPhysics)
	: manager(mManager), physics(mPhysics)
	{ }

	void init() override 
	{
		transform = &entity->getComponent<TransformComponent>();
	}
	void update(float mFT) override
	{
		++cnt;
		std::cout << "Updating physics " << cnt << '\n';
		physics->update(mFT, entity, manager);	
	}

private:
	int cnt {};
};

#endif
