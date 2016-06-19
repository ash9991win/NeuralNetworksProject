#pragma once
#include"pch.h"
class Component;
class World;
/*!
@class Actor
@brief The base class for all the updatable objects in the world
*/
class Actor
{
private:
	friend class World;
	std::string mName;
	std::vector<Component*> mComponents;
	World* mWorld;
protected:
	sf::RenderWindow* mWindow;
	sf::Sprite mSprite;
	float mSpriteWidth;
	float mSpriteHeight;
public:

	sf::RenderWindow* GetWindow() { return mWindow; }
	sf::Vector2f mPosition;
	virtual ~Actor();
	const World* GetWorld() const;
	virtual void Update(float deltaTime) = 0 ;
	virtual void BeginPlay() = 0;
	template<typename ComponentType,typename...arg>
	ComponentType* AddComponent(arg...);
	template<typename ComponentType>
	ComponentType* GetComponent();
	float speed;
	void SetSpriteDimensions(float width, float height);
	virtual bool Is(std::uint64_t) const { return false; }
	virtual bool Is(std::string) const { return false; }
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
inline ComponentType * Actor::AddComponent(arg ...a)
{
	ComponentType *component = new ComponentType(a...);
	component->SetOwner(*this);
	mComponents.push_back(component);
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
