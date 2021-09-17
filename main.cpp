#include "graphics.hpp"
#include <thread>
#include <chrono>

int main() {
	
	int scrX = 0.95 * GetSystemMetrics(SM_CXSCREEN); //Разрешение экрана по X
	int scrY = 0.95 * GetSystemMetrics(SM_CYSCREEN); //Разрешение экрана по Y
	sf::RenderWindow window(sf::VideoMode(scrX, scrY), "Brand new Grapher");	
	int firstPlotColor  = 0x000000;
	int secondPlotColor = 0x000000;

	Vector_t firstOrdinate (0.05 * scrX, 0.85 * scrY, 0, -0.8 * scrY);
	Vector_t firstAbscissa (0.05 * scrX, 0.85 * scrY, 0.4 * scrX, 0);
	Plot_t firstPlot(&firstAbscissa, &firstOrdinate,  100, 250, firstPlotColor);

	Vector_t secondOrdinate (0.55 * scrX, 0.85 * scrY, 0, -0.8 * scrY);
	Vector_t secondAbscissa (0.55 * scrX, 0.85 * scrY, 0.4 * scrX, 0);
	Plot_t secondPlot(&secondAbscissa, &secondOrdinate, 50, 80, secondPlotColor);
	
	Vector_t a(0.55 * scrX, 0.85 * scrY, 100, -50);
	Vector_t b(0.55 * scrX, 0.85 * scrY, 50, -100);
	Vector_t c = a + b;

	Vector_t r(0.25 * scrX , 0.5 * scrY, 0, 200);

	window.clear(sf::Color::White);
	firstPlot.Draw (&window);
	secondPlot.Draw(&window);
	window.display();
	window.clear(sf::Color::White);
	firstPlot.Draw (&window);
	secondPlot.Draw(&window);

	int flag = 1;
	
	while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

		double angle = M_PI / 3, temp_angle = M_PI / 3;
		
		while (angle < 2 * 3.14 + 1 && flag) {
			DrawVector(&r, &window, 0xff0000 , 0.25);
			r.LeftRotate(temp_angle);
			angle += temp_angle;
			std::this_thread::sleep_for(std::chrono::milliseconds(500));

			window.display();
			window.clear(sf::Color::White);
			firstPlot.Draw (&window);
			secondPlot.Draw(&window);
		}

		if (flag) {
			DrawVector(&a, &window, 0x00ff00, 0.25);
			DrawVector(&b, &window, 0x0000ff, 0.25);
			DrawVector(&c, &window, 0x0f0fff, 0.25);
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			window.display();
		}
		flag = 0;
    }

    return 0;
}