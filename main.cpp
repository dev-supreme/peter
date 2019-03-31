#include<stdio.h>

const float PI = 3.14159;

typedef struct coordinate {
	float x;
	float y;
	coordinate() { x = y = 0; }
	coordinate(int x1, int y1)
	{
		x = x1;
		y = y1;
	}
}coordinate;

class Circle
{
public:
	Circle(int radius, int x, int y) 
	{
		setRadius(radius);
		this->center.x = x;
		this->center.y = y;
	}
	Circle(int radius, coordinate pos)
	{
		setRadius(radius);
		this->center = pos;
	}
	~Circle() {}
private:
	int radius;
	coordinate center;

	void setCenterPos(int x, int y)
	{
		this->center.x = x;
		this->center.y = y;
	}
	void setCenterPos(coordinate pos)
	{
		setCenterPos(pos.x, pos.y);
	}
public:
	int getRadius()
	{
		return radius;
	}
	void setRadius(int radius)
	{
		if (radius <= 0)
			radius = 1;
		if (radius > 100)
			radius = 100;

		this->radius = radius;
	}
	double getArea()
	{
		return PI * radius * radius;
	}
	
	void Move(int x, int y)
	{
		setCenterPos(this->center.x + x, this->center.y + y);
	}

	void Move(coordinate pos)
	{
		setCenterPos(this->center.x + pos.x, this->center.y + pos.y);
	}

	void MoveTo(int x, int y)
	{
		setCenterPos(x, y);
	}

	void MoveTo(coordinate pos)
	{
		setCenterPos(pos);
	}
};

class Triangle
{
	coordinate point[3];	
	double getArea;
};

class Rectabngle
{
	coordinate point[2];
	double width;
	double height;
	double getArea;
};



int main(void)
{
	Circle one(5, 100, 50);
	printf("Circle One(radius: %d) Area: %.2f\n", one.radius, one.getArea());

	Circle two(10, coordinate(30, 50));
	printf("Two area: %.2f\n", two.getArea());
}

