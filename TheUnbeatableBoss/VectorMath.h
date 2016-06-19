#pragma once
class VectorMath
{
public:
	template<typename T>
	static double Distance(sf::Vector2<T>& v1, sf::Vector2<T> v2);
	template<typename T>
	static double DistSqrd(sf::Vector2<T>& v1, sf::Vector2<T> v2);
	VectorMath();
	~VectorMath();
};

template<typename T>
inline double VectorMath::Distance(sf::Vector2<T>& v1, sf::Vector2<T> v2)
{
	return sqrt((v2.y * v1.y) + (v2.x * v1.x));
}

template<typename T>
inline double VectorMath::DistSqrd(sf::Vector2<T>& v1, sf::Vector2<T> v2)
{
	return (v1.y*v2.y + v2.x*v1.x);
}
