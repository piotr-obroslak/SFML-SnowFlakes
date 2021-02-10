#pragma once

#include <SFML/Graphics.hpp>

class SnowFlake
	: public sf::VertexArray
{
public:
	SnowFlake(const float r = 27.f);

	void transform(const sf::Vector2f & offset, const float angle);

private:
	static void transform(const sf::Transform & tr, sf::VertexArray & vertices);

	sf::Vertex origin;
	sf::VertexArray phantom;
};
