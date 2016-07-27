#pragma once
class VectorMath
{
public:
	template<typename T>
	static double Distance(sf::Vector2<T>& v1, sf::Vector2<T> v2);
	template<typename T>
	static double DistSqrd(sf::Vector2<T>& v1, sf::Vector2<T> v2);
	template<typename T>
	static void Normalize(sf::Vector2<T>& v);
	template<typename T>
	static double Magnitude(sf::Vector2<T>& v);
	VectorMath();
	~VectorMath();
};

template<typename T>
inline double VectorMath::Distance(sf::Vector2<T>& v1, sf::Vector2<T> v2)
{
	return sqrt((v2.x - v1.x)*(v2.x - v1.x) + (v2.y - v1.y)*(v2.y - v1.y));
}

template<typename T>
inline double VectorMath::DistSqrd(sf::Vector2<T>& v1, sf::Vector2<T> v2)
{
	return (v1.y*v2.y + v2.x*v1.x);
}

template<typename T>
inline void VectorMath::Normalize(sf::Vector2<T>& v)
{
	double mag = Magnitude(v);
	v.x /= mag;
	v.y /= mag;
}

template<typename T>
inline double VectorMath::Magnitude(sf::Vector2<T> & v)
{
	return sqrt(v.x * v.x + v.y * v.y);
}
