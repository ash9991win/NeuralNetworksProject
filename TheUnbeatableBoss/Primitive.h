#pragma once
class Primitive
{
	static sf::RenderWindow* window;
	sf::RectangleShape rect;
public:
	static void SetWindow(sf::RenderWindow* w)
	{
		window = w;
	}
	static void DrawCircles(float x, float y, float radius)
	{
		sf::CircleShape circle;

		if (window && window->isOpen())
		{

			circle.setRadius(radius);
			circle.setFillColor(sf::Color::Transparent);
			circle.setOutlineThickness(1);
			circle.setOutlineColor(sf::Color::White);
			circle.setPosition(x, y);
			window->draw(circle);
			if (radius > 8)
			{
				DrawCircles(x + radius / 2, y, radius / 2);
				DrawCircles(x - radius / 2, y, radius / 2);
				DrawCircles(x, y + radius / 2, radius / 2);
				DrawCircles(x, y - radius / 2, radius / 2);
			}
		}
	}
	static 	void Cantor(float x, float y, float length)
	{
		if (length >= 1)
		{
			DrawLine(x, y, x + length, y);
			y += 20;
			Cantor(x, y, length / 3);
			Cantor(x + length * 2 / 3, y, length / 3);
		}
	}
	static void LineFractal(float x, float y, float l)
	{
		if (l >= 1)
		{
			DrawLine(x, y, x, y + l);
			x -= l / 2;
			y -= l / 2;
			LineFractal(x, y, l / 2);
			x += l / 2;
			y += l / 2;
			LineFractal(x, y, l / 2);
		}

	}

	//Draw a line given the starting and ending points
	static  void DrawLine(float x, float y, float x1, float y1, sf::Color color = sf::Color::White, sf::RenderTexture* texture = nullptr)
	{
		sf::VertexArray line(sf::Lines, 2);
		line[0] = sf::Vector2f(x, y);
		line[1] = sf::Vector2f(x1, y1);
		line[0].color = color;
		line[1].color = color;
		if (texture)
			texture->draw(line);
		else
			window->draw(line);

	}
	static void DrawTriangle(sf::Vector2f v1, sf::Vector2f v2, sf::Vector2f v3, sf::Color color = sf::Color::White, sf::RenderTexture* texture = nullptr)
	{
		sf::VertexArray triangle(sf::Triangles, 3);
		triangle[0] = v1;
		triangle[0].color = color;
		triangle[1] = v2;
		triangle[1].color = color;
		triangle[2] = v3;
		triangle[2].color = color;
		if (texture)
			texture->draw(triangle);
		else
			window->draw(triangle);
	}
	static void DrawRectangle(sf::Vector2f position, float width, float height, sf::Color color = sf::Color::White)
	{
		sf::RectangleShape shape;
		shape.setPosition(position);
		shape.setSize(sf::Vector2f(width, height));
		shape.setFillColor(color);
		shape.setOutlineColor(sf::Color::Black);
		shape.setOutlineThickness(2);
		window->draw(shape);
	}

};

