#pragma once
#include"World.h"
class Component;
class World;
/*!
@class Actor
@brief The base class for all the updatable objects in the world
*/
class Actor
{
private:
	//Make the World class a friend, in order to access the World's variables
	friend class World;
	friend class CollisionManager;
	//The name of the actor
	std::string mName;
	//List of components for this actor
	std::vector<Component*> mComponents;
	//A world reference
	World* mWorld;
	//Whether the actor should update every frame or no
protected:
	bool shouldUpdate;
	bool isActorAlive;
	//The window that the actor renders to
	sf::RenderWindow* mWindow;
	class CollisionComponent* mCollider;
	void CreateCollider();
	bool IsShielded;
public:
	void Shield();
	void UnShield();
	inline bool CheckIfShielded() const { return IsShielded; }
	//The position of the actor
	sf::Vector2f mPosition;
	double mHealth;
	virtual void GameOver();
	delegate<void> GameOverEvent();
	virtual void Damage(double value);
	//The dimensions of the sprite that the actor has and the sprite of the actor
	sf::Sprite mSprite;
	float mSpriteWidth;
	float mSpriteHeight;
	sf::RenderWindow* GetWindow() { return mWindow; }
	virtual ~Actor();
	const World* GetWorld() const;
	virtual void Update(float deltaTime) = 0 ;
	virtual void BeginPlay() = 0;
	template<typename ComponentType,typename...arg>
	//Add a component of a given type
	ComponentType* AddComponent(arg...);
	//Get a component of given type
	template<typename ComponentType>
	ComponentType* GetComponent();
	//Remove a given component
	void RemoveComponent(Component& comp);
	//Speed of the actor
	float speed;
	//Change the sprite's dimensions ( it scales the sf::Sprite accordingly)
	void SetSpriteDimensions(float width, float height);
	//Destroy an actor ( unregister it from the world)
	void Destroy();
	//Returns if the actor should or shouldn't be updated
	bool IsActorAlive() const { return isActorAlive; }
	//RTTI functions 
	virtual bool Is(std::uint64_t) const { return false; }
	virtual bool Is(std::string) const { return false; }
	class GlowEffects *GlowComponent;
	template <typename T>
	T* As() const
	{
		if (Is(T::TypeIdClass()))
		{
			return (T*)this;
		}
		return nullptr;
	}
};

template<typename ComponentType, typename ...arg>
 ComponentType * Actor::AddComponent(arg ...a)
{
	ComponentType *component = new ComponentType(a...);
	component->SetOwner(*this);
	mComponents.push_back(component);
	if (World::CURRENT_GAME_STATE == GAME_STATE::GAME_RUNNING)
	{
		component->BeginPlay();
	}
	return component;
}

template<typename ComponentType>
inline ComponentType * Actor::GetComponent()
{
	ComponentType *foundComponent = nullptr;
	for (auto components : mComponents)
	{
		if (components->Is(ComponentType::TypeIdClass()))
		{
			foundComponent = components->As<ComponentType>();
		}
	}
	return foundComponent;
}


