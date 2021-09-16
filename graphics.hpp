#include <SFML/Graphics.hpp>
#include <Windows.h>

#include <iostream>
#include <cstdlib>
#include <cmath>

#include "vector.hpp"
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
sf::VertexArray *CreateSegment(Point_t *First, Point_t *Second, int color);
sf::VertexArray *CreateSegment (Vector_t *vector, int color);

void DrawVector(Vector_t *vector, sf::RenderWindow *window, int color, double fracion);

int oneStep(double x);
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------`
class Plot_t {
	public:
		Plot_t(Point_t Centre, Point_t Abs, Point_t Ord, int MaxElemX, int MaxElemY, int color) {
			this->Ordinate = new Vector_t(Centre, Ord);
			this->Abscissa = new Vector_t(Centre, Abs);
			this->MaxElemX = MaxElemX;
			this->MaxElemY = MaxElemY;
			this->Color    = color;
		}
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------`
		Plot_t(Vector_t *Abscissa, Vector_t *Ordinate, int MaxElemX, int MaxElemY, int color) {
			this->Ordinate = Ordinate;
			this->Abscissa = Abscissa;
			this->MaxElemX = MaxElemX;
			this->MaxElemY = MaxElemY;
			this->Color    = color;
		}
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
		~Plot_t() {
			delete this->Ordinate;
			delete this->Abscissa;
		}
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
		void Draw(sf::RenderWindow *window) {
			DrawVector(this->Ordinate, window, this->Color, 0.05);
			DrawVector(this->Abscissa, window, this->Color, 0.05);

			Point_t centreP(this->Abscissa->GetStartingPoint()->x , this->Abscissa->GetStartingPoint()->y);
			Point_t endAbs (this->Abscissa->GetStartingPoint()->x + this->Abscissa->GetX(), 
							this->Abscissa->GetStartingPoint()->y + this->Abscissa->GetY());
			Point_t endOrd (this->Ordinate->GetStartingPoint()->x + this->Ordinate->GetX(), 
							this->Ordinate->GetStartingPoint()->y + this->Ordinate->GetY());
			
			int oneStepAbscissa   = oneStep(MaxElemX);
			int oneStepOrdinate   = oneStep(MaxElemY);
			int countStepAbscissa = (MaxElemX + oneStepAbscissa - 1) / oneStepAbscissa;
			int countStepOrdinate = (MaxElemY + oneStepOrdinate - 1) / oneStepOrdinate;

			double lambda = 1./(countStepAbscissa + 1);
			double xCoord = 0;
			double yCoord = 0;
			Vector_t topStreak;
			Vector_t botStreak;
			Point_t tempFirstP, tempSecondP;

			sf::VertexArray *division;

			for (int i = 0; i < countStepAbscissa; ++i) {
				xCoord = centreP.x + (endAbs.x - centreP.x) * lambda;
				yCoord = centreP.y + (endAbs.y - centreP.y) * lambda;

				topStreak = Vector_t(xCoord, yCoord, 0, 0);
				botStreak = Vector_t(xCoord, yCoord, 0, 0);
				topStreak += 0.01 * (*(this->Ordinate));
				botStreak -= 0.01 * (*(this->Ordinate));

				tempFirstP.x  = xCoord + topStreak.GetX();
				tempFirstP.y  = yCoord + topStreak.GetY();
				tempSecondP.x = xCoord + botStreak.GetX();
				tempSecondP.y = yCoord + botStreak.GetY();

				division = CreateSegment(&tempFirstP, &tempSecondP, this->Color);
				window->draw(*division);
				delete division;
				lambda += 1./(countStepAbscissa + 1);
			}

			lambda = 1./(countStepOrdinate + 1);

			for (int i = 0; i < countStepOrdinate; ++i) {
				xCoord = centreP.x + (endOrd.x - centreP.x) * lambda;
				yCoord = centreP.y + (endOrd.y - centreP.y) * lambda;

				topStreak = Vector_t(xCoord, yCoord, 0, 0);
				botStreak = Vector_t(xCoord, yCoord, 0, 0);
				topStreak += 0.01 * (*(this->Abscissa));
				botStreak -= 0.01 * (*(this->Abscissa));

				tempFirstP.x  = xCoord + topStreak.GetX();
				tempFirstP.y  = yCoord + topStreak.GetY();
				tempSecondP.x = xCoord + botStreak.GetX();
				tempSecondP.y = yCoord + botStreak.GetY();

				division = CreateSegment(&tempFirstP, &tempSecondP, this->Color);
				window->draw(*division);
				delete division;
				lambda += 1./(countStepOrdinate + 1);
			}
		}
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
	private:
		Vector_t *Ordinate;
		Vector_t *Abscissa;
		int MaxElemX;
		int MaxElemY;
		int Color;
};
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
sf::VertexArray *CreateSegment (Point_t *First, Point_t *Second, int color) {
	sf::VertexArray *segment = nullptr;
	try {
		segment = new sf::VertexArray(sf::Lines, 2);
	}
	catch (std::bad_alloc) {
		perror("Bad allocation");
	}
	(*segment)[0].position = sf::Vector2f(First->x,   First->y);
	(*segment)[0].color = sf::Color((color & 0xFF0000) >> 16, (color & 0xFF00) >> 8, color & 0xFF);
	
	(*segment)[1].position = sf::Vector2f(Second->x, Second->y);
	(*segment)[1].color = sf::Color((color & 0xFF0000) >> 16, (color & 0xFF00) >> 8, color & 0xFF);
	return segment;
}

sf::VertexArray *CreateSegment (const Point_t *First,const Point_t *Second, int color) {
	sf::VertexArray *segment = nullptr;
	try {
		segment = new sf::VertexArray(sf::Lines, 2);
	}
	catch (std::bad_alloc) {
		perror("Bad allocation");
	}
	(*segment)[0].position = sf::Vector2f(First->x,   First->y);
	(*segment)[0].color = sf::Color((color & 0xFF0000) >> 16, (color & 0xFF00) >> 8, color & 0xFF);
	
	(*segment)[1].position = sf::Vector2f(Second->x, Second->y);
	(*segment)[1].color = sf::Color((color & 0xFF0000) >> 16, (color & 0xFF00) >> 8, color & 0xFF);
	return segment;
}
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
void DrawVector(Vector_t *vector, sf::RenderWindow *window,int color, double fraction) {
	double lambda = (1. - fraction) / fraction;

	Point_t endingPoint  (vector->GetX() + vector->GetStartingPoint()->x,
					 	  vector->GetY() + vector->GetStartingPoint()->y);
	Point_t startingPoint(vector->GetStartingPoint()->x, 
						  vector->GetStartingPoint()->y);

	Vector_t firstPart (endingPoint, 
					   (startingPoint.x + lambda * endingPoint.x) / (1. + lambda) - endingPoint.x, 
					   (startingPoint.y + lambda * endingPoint.y) / (1. + lambda) - endingPoint.y);
	Vector_t secondPart(endingPoint, 
					   (startingPoint.x + lambda * endingPoint.x) / (1. + lambda) - endingPoint.x, 
					   (startingPoint.y + lambda * endingPoint.y) / (1. + lambda) - endingPoint.y); 
	
	firstPart.RightRotate(M_PI / 6);
	secondPart.LeftRotate(M_PI / 6);

	Point_t result_1(firstPart.GetX()  + firstPart.GetStartingPoint()->x,
					 firstPart.GetY()  + firstPart.GetStartingPoint()->y);
	Point_t result_2(secondPart.GetX() + secondPart.GetStartingPoint()->x,
					 secondPart.GetY() + secondPart.GetStartingPoint()->y);

	sf::VertexArray *segmentArrow1 = CreateSegment(firstPart.GetStartingPoint() , &result_1   , color);
	sf::VertexArray *segmentArrow2 = CreateSegment(secondPart.GetStartingPoint(), &result_2   , color);
	sf::VertexArray *segmentMain   = CreateSegment(&startingPoint               , &endingPoint, color);

	window->draw(*segmentArrow1);
	window->draw(*segmentArrow2);
	window->draw(*segmentMain);

	delete segmentArrow1;
	delete segmentArrow2;
	delete segmentMain;
}
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
int oneStep (double x) {
	int k = 1, mult = 2;
	for (; k *10 < x; k *= (7 - mult), mult = (7-mult));
	return k;
}