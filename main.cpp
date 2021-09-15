#include "graphics.hpp"
#include <thread>
#include <chrono>

int main() {
	
	int scrX = 0.95 * GetSystemMetrics(SM_CXSCREEN); //Разрешение экрана по X
	int scrY = 0.95 * GetSystemMetrics(SM_CYSCREEN); //Разрешение экрана по Y
	sf::RenderWindow window(sf::VideoMode(scrX, scrY), "Brand new Grapher");
	
	int firstPlotColor = 0x000000;

	Vector_t firstOrdinate (0.05 * scrX, 0.85 * scrY, 0, -0.8 * scrY);
	Vector_t firstAbscissa (0.05 * scrX, 0.85 * scrY, 0.4 * scrX, 0);
	Plot_t firstPlot(&firstAbscissa, &firstOrdinate,  0, 0, firstPlotColor);

	Vector_t secondOrdinate (0.55 * scrX, 0.85 * scrY, 0, -0.8 * scrY);
	Vector_t secondAbscissa (0.55 * scrX, 0.85 * scrY, 0.4 * scrX, 0);
	Plot_t secondPlot(&secondAbscissa, &secondOrdinate, 0, 0, firstPlotColor);
	
	Vector_t a(0.55 * scrX, 0.85 * scrY, 100, -50);
	Vector_t b(0.55 * scrX, 0.85 * scrY, 50, -100);
	Vector_t c = a + b;

	Vector_t r(0.5 * scrX , 0.5 * scrY, 0, 200);
	
	while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);
		DrawVector(&a, &window, 0xFFFFFF, 0.25);
		DrawVector(&b, &window, 0xFFFFFF, 0.25);
		DrawVector(&c, &window, 0xFFFFFF, 0.25);

		double angle = M_PI / 50, temp_angle = M_PI / 50;
		while (angle < 2 * M_PI) {
			DrawVector(&r, &window, 0xFFFFFF, 0.25);
			r.RightRotate(temp_angle);
			angle += temp_angle;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(200));

		void DrawVector(Vector_t *vector, sf::RenderWindow *window,int color, double fraction);
		firstPlot.Draw(&window);
		secondPlot.Draw(&window);
        window.display();
    }

    return 0;
}