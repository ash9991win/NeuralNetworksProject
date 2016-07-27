#pragma once
class Actor;
//The component of an actor
class Component
{
protected:
	friend class Actor;
	//The owner of this component
	Actor* mOwner;
	Component() = default;
	virtual ~Component();
public:
	bool Enable;
	virtual void Update(float deltaTime) = 0;
	virtual void BeginPlay() = 0;
	void SetOwner(Actor& owner);

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

