#include "SnowFlake.h"
#include <boost/math/special_functions/cos_pi.hpp>
#include <boost/math/special_functions/sin_pi.hpp>

SnowFlake::SnowFlake(const float r /*= 27.f*/)
	: phantom(sf::Lines)
	, origin(sf::Vector2f(0.f, 0.f))
{
	const auto divisor = rand() % 2;

	const auto r_3 = static_cast<int>(r / 3.f);
	const auto r_5 = static_cast<int>(r / 5.f);
	const int r1[] = { rand() % r_3 + r_5, rand() % r_3 + r_5 };

	const auto tDelta = 1.f / 3.f;
	for (auto theta = 0.f; theta < 2.f; theta += tDelta)
	{
		phantom.append(origin);

		phantom.append(sf::Vertex(sf::Vector2f(
			origin.position.x + r * boost::math::cos_pi(theta),
			origin.position.y + r * boost::math::sin_pi(theta))));

		for (auto i = 0; i <= divisor; i++)
		{
			const auto rr = ((i + 1.f) * r) / (divisor + 2.f);

			sf::Vertex o1;
			o1.position.x = rr * boost::math::cos_pi(theta);
			o1.position.y = rr * boost::math::sin_pi(theta);

			phantom.append(o1);
			phantom.append(sf::Vertex(sf::Vector2f(
				o1.position.x + r1[i] * boost::math::cos_pi(theta + tDelta),
				o1.position.y + r1[i] * boost::math::sin_pi(theta + tDelta))));

			phantom.append(o1);
			phantom.append(sf::Vertex(sf::Vector2f(
				o1.position.x + r1[i] * boost::math::cos_pi(theta - tDelta),
				o1.position.y + r1[i] * boost::math::sin_pi(theta - tDelta))));
		}
	}
}

void SnowFlake::transform(const sf::Vector2f & offset, const float angle)
{
	sf::Transform rotation;
	rotation.rotate(angle);
	transform(rotation, phantom);

	auto & vertices = (VertexArray&)(*this);
	vertices = phantom;

	sf::Transform translation;
	translation.translate(origin.position += offset);
	transform(translation, *this);
}

/*static*/ void SnowFlake::transform(const sf::Transform & tr, sf::VertexArray & vertices)
{
	for (std::size_t i = 0; i < vertices.getVertexCount(); i++)
	{
		auto & v = vertices[i];
		v.position = tr.transformPoint(v.position);
	}
}
