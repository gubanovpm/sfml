#include <iostream>
#include <cmath>

struct Point_t {
		Point_t(double x_ = 0, double y_ = 0) :
			x(x_),
			y(y_) {
		};
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
		void Print() {
			std::cout << "(" << this->x << ", " << this->y << ")" << std::endl;
		};
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
		double x;
		double y;
};

class Vector_t {
	public:
		Vector_t(double startingPointX = 0, double startingPointY = 0, double x = 0, double y = 0) :
			StartingPoint(startingPointX, startingPointY),
			X(x),
			Y(y) {
		};
		Vector_t(Point_t startingPoint, double x = 0, double y = 0) :
			StartingPoint(startingPoint),
			X(x),
			Y(y) {
		};
		Vector_t(Point_t startPoint, Point_t endPoint) :
			StartingPoint(startPoint),
			X(endPoint.x - startPoint.x),
			Y(endPoint.y - startPoint.y) {
		};
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
		~Vector_t(){
		}
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
		Vector_t &operator = (Vector_t &other) {
			this->StartingPoint = other.StartingPoint;
						this->X = other.X;
						this->Y = other.Y;

			return *this;
		}
		Vector_t &operator = (Vector_t &&other) {
			this->StartingPoint = other.StartingPoint;
						this->X = other.X;
						this->Y = other.Y;

			return *this;
		}
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
		Vector_t(Vector_t &other){
			this->StartingPoint = other.StartingPoint;
						this->X = other.X;
						this->Y = other.Y;
		}
		Vector_t(Vector_t &&other){
			this->StartingPoint = other.StartingPoint;
						this->X = other.X;
						this->Y = other.Y;
		}
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
		Vector_t operator - () const{
		    Vector_t Result(this->StartingPoint, -this->X, -this->Y);
			return Result;
		}
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
		Vector_t &operator += (Vector_t &other) {
			this->X += other.X;
			this->Y += other.Y;

			return *this;
		}

		Vector_t &operator += (Vector_t &&other) {
			this->X += other.X;
			this->Y += other.Y;

			return *this;
		}
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
		Vector_t  &operator *= (double k) {
			this->X *= k;
			this->Y *= k;

			return *this;
		}
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
		double operator  *= (Vector_t &other) const{
			return (this->X * other.X + this->Y * other.Y);
		}

		double operator  *= (Vector_t &&other) const{
			return (this->X * other.X + this->Y * other.Y);
		}
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
		Vector_t &operator -= (Vector_t &other) {
			this->X -= other.X;
			this->Y -= other.Y;

			return *this;
		}

		Vector_t &operator -= (Vector_t &&other) {
			this->X -= other.X;
			this->Y -= other.Y;

			return *this;
		}
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
		Vector_t &operator /= (double k) {
			if (k == 0) {
				std::cout << "Floating point exception" << std::endl;
				return *this;
			}
			this->X /= k;
			this->Y /= k;
			return *this;
		}
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
		void Print() const{
			std::cout << "{" << this->X << ", " << this->Y << "} with starting point "
					  << "(" << this->StartingPoint.x << ", "
							 << this->StartingPoint.y << ")\n";
		};
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
		double Length() const{
			return sqrt(this->X * this->X + this->Y * this->Y);
		}
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
		void RightRotate(double angle) {
			double temp_x = this->X, temp_y = this->Y;
			this->X = round(  temp_x * cos(angle) + temp_y * sin(angle));
			this->Y = round(- temp_x * sin(angle) + temp_y * cos(angle));
		}

		void LeftRotate(double angle) {
			double temp_x = this->X, temp_y = this->Y;
			this->X = temp_x * cos(angle) - temp_y * sin(angle);
			this->Y = temp_x * sin(angle) + temp_y * cos(angle);
		}
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
		Vector_t PerpendicularVector_t() const{
			Vector_t Result(this->StartingPoint, -(this->Y), this->X);
			return Result;
		}
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
		double GetX() const{
			return this->X;
		}

		double GetY() const{
			return this->Y;
		}

		const Point_t *GetStartingPoint() const{
			return &(this->StartingPoint);
		}
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
		void SetX(double x) {
			this->X = x;
		}

		void SetY(double y) {
			this->Y = y;
		}

		void SetStartingPoint(double x, double y) {
			this->StartingPoint = {x, y};
		}
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
	private:
		double X;
		double Y;
		Point_t StartingPoint;
};
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
Vector_t operator + (Vector_t &v1, Vector_t &v2) {
	Vector_t Result = v1;
	Result += v2;
	return Result;
}

Vector_t operator + (Vector_t &v1, Vector_t &&v2) {
	Vector_t Result = v1;
	Result += v2;
	return Result;
}

Vector_t operator + (Vector_t &&v1, Vector_t &v2) {
	Vector_t Result = v1;
	Result += v2;
	return Result;
}

Vector_t operator + (Vector_t &&v1, Vector_t &&v2) {
	Vector_t Result = v1;
	Result += v2;
	return Result;
}
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
Vector_t operator * (double k, Vector_t &v2) {
	Vector_t Result = v2;
	Result *= k;
	return Result;
}

Vector_t operator * (Vector_t &v2, double k) {
	return k * v2;
}

Vector_t operator * (double k, Vector_t &&v2) {
	Vector_t Result = v2;
	Result *= k;
	return Result;
}

Vector_t operator * (Vector_t &&v2, double k) {
	return k * v2;
}
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
double operator * (Vector_t &v1, Vector_t &v2) {
	return (v1 *= v2);
}

double operator * (Vector_t &v1, Vector_t &&v2) {
	return (v1 *= v2);
}

double operator * (Vector_t &&v1, Vector_t &v2) {
	return (v2*=v1);
}

double operator * (Vector_t &&v1, Vector_t &&v2) {
	Vector_t Result = v1;
	return (Result*=v2);
}
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
Vector_t operator - (Vector_t &v1, Vector_t &v2) {
	Vector_t Result = v1;
	Result -= v2;
	return Result;
}

Vector_t operator - (Vector_t &&v1, Vector_t &v2) {
	Vector_t Result = v1;
	Result -= v2;
	return Result;
}

Vector_t operator - (Vector_t &v1, Vector_t &&v2) {
	Vector_t Result = v1;
	Result -= v2;
	return Result;
}

Vector_t operator - (Vector_t &&v1, Vector_t &&v2) {
	Vector_t Result = v1;
	Result -= v2;
	return Result;
}
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
Vector_t operator / (Vector_t &v1, double k) {
	Vector_t Result = v1;
	Result /= k;
	return Result;
}

Vector_t operator / (Vector_t &&v1, double k) {
	Vector_t Result = v1;
	Result /= k;
	return Result;
}
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------`