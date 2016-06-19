#pragma once
class Actor;
class Component
{
protected:
	Actor* mOwner;
public:
	virtual void Update(float deltaTime) = 0;
	virtual void BeginPlay() = 0;
	void SetOwner(Actor& owner);
	Component();
	~Component();
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

