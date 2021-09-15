#include "graphics.hpp"

int main() {
	
	int scrX = 0.95 * GetSystemMetrics(SM_CXSCREEN); //Разрешение экрана по X
	int scrY = 0.95 * GetSystemMetrics(SM_CYSCREEN); //Разрешение экрана по Y
	sf::RenderWindow window(sf::VideoMode(scrX, scrY), "Brand new Grapher");
	
	int firstPlotColor  = 0xaa55fb;
	int secondPlotColor = 0xff00ff;

	Vector_t firstOrdinate (0.05 * scrX, 0.85 * scrY, 0, -0.8 * scrY);
	Vector_t firstAbscissa (0.05 * scrX, 0.85 * scrY, 0.4 * scrX, 0);
	Plot_t firstPlot(&firstAbscissa, &firstOrdinate,  0, 0, firstPlotColor);

	Vector_t secondOrdinate (0.55 * scrX, 0.85 * scrY, 0, -0.8 * scrY);
	Vector_t secondAbscissa (0.55 * scrX, 0.85 * scrY, 0.4 * scrX, 0);
	Plot_t secondPlot(&secondAbscissa, &secondOrdinate, 0, 0, secondPlotColor);
	
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
			window.display();
			window.clear(sf::Color::White);
			firstPlot.Draw (&window);
			secondPlot.Draw(&window);
			DrawVector(&r, &window, 0xFF0000 , 0.25);
			r.RightRotate(temp_angle);
			angle += temp_angle;
			for (long long int i = 0; i < 1000000000; ++i); //ping
		}

		if (flag) {
			DrawVector(&a, &window, 0x00FF00, 0.25);
			for (long long int i = 0; i < 1000000000; ++i);
			DrawVector(&b, &window, 0x0000FF, 0.25);
			for (long long int i = 0; i < 1000000000; ++i);
			DrawVector(&c, &window, 0xFF00FF, 0.25);
			for (long long int i = 0; i < 1000000000; ++i);
			window.display();
		}
		flag = 0;
    }

    return 0;
}