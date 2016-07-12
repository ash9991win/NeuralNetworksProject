#pragma once

template<typename T>
class Genome
{
private:
	T Value;
	static vector<T> list;
public:
	static function<void(T)> UpdateFunction;
	static void AddPossibleValue(T value)
	{
		//ListOfValues.ListOfValues.push_back(value);
		list.push_back(value);
	}
	T CurrentValue() const
	{
		return Value;
	}
	void Update()
	{
		if (UpdateFunction)
		{
			UpdateFunction(Value);
		}
	}
	static Genome GetRandomGenome()
	{
		int i = std::rand() % list.size();
		return list[i];
	}
    Genome(T v)
		:Value(v)
	{
	}

	~Genome() = default;
};

