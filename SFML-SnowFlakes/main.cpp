#include "SnowFlake.h"
#include <list>

#define TEST_MODE	(0)

int main()
{
	srand(time(nullptr));

	sf::VideoMode vm(1280, 720);

	sf::RenderWindow wnd(vm, "Snow Flakes - Merry Xmas 2020!");
	wnd.setFramerateLimit(24);

#if TEST_MODE
	SnowFlake theOneAndOnly(250);
	theOneAndOnly.transform(sf::Vector2f(
		vm.width / 2, vm.height / 2), 15.f);

#else
	std::list<std::pair<SnowFlake, float>> snowFlakes;

	sf::Clock clk;

	decltype(sf::Time().asMilliseconds()) interval = 0;
#endif

	while (wnd.isOpen())
	{
		wnd.clear();

		sf::Event event;
		while (wnd.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				wnd.close();
			}
		}

#if TEST_MODE
		theOneAndOnly.transform(sf::Vector2f(0.f, 0.f), 3.f);
		wnd.draw(theOneAndOnly);
#else
		auto elapsed = clk.getElapsedTime();
		if (elapsed.asMilliseconds() > interval)
		{
			snowFlakes.push_back({
				SnowFlake(static_cast<float>(rand() % 21 + 13)),
				(static_cast<float>(rand() % 10) - 5) });
			
			auto & x = snowFlakes.back();
			
			auto & snowFlake = x.first;
			snowFlake.transform(
				sf::Vector2f(rand() % (vm.width - 20) + 10,
					-snowFlake.getBounds().height), 0.f);

			auto & rotationSpeed = x.second;
			rotationSpeed = ((static_cast<float>(rand() % 2) + 1.f) / 2.f) * ((rand() % 2) * 2.f - 1.f);

			clk.restart();

			interval = (rand() % 4 + 1) * 250;
		}

		for (auto it = snowFlakes.begin(); it != snowFlakes.end(); ++it)
		{
			auto & x = (*it);
			auto & shape = x.first;
			auto & angle = x.second;

			if (shape.getBounds().top > vm.height /*/ 2*/)
			{
				it = snowFlakes.erase(it);
				continue;
			}

			shape.transform(sf::Vector2f(0.f, 1.f), angle);

			wnd.draw(shape);
		}
#endif

		wnd.display();
	}

	return 0;
}
