#pragma once
#include <iostream>

class Widget
{	
public:

	Widget()
	{
		std::cout << "Default Constructor" << std::endl;
	}

	Widget(int x, int y) : x_(x), y_(y)
	{
		std::cout << "Parameterized Constructor" << std::endl;
	}

	Widget(const Widget& rhs)
	{
		std::cout << "Copy constructor" << std::endl;
		x_ = rhs.x_;
		y_ = rhs.y_;
	}

	Widget(const Widget&& rhs)
	{
		std::cout << "Move constructor" << std::endl;
		x_ = rhs.x_;
		y_ = rhs.y_;
	}

	Widget& operator = (const Widget& rhs)
	{
		std::cout << "Copy assignment operator" << std::endl;
		x_ = rhs.x_;
		y_ = rhs.y_;
		return *this;
	}

	Widget& operator = (const Widget&&)
	{
		std::cout << "Move assignment operator" << std::endl;
		return *this;
	}

	friend std::ostream& operator << (std::ostream& os, const Widget& w)
	{
		os << w.x_ << ", " << w.y_;
		return os;
	}

	~Widget()
	{
		std::cout << "Destructor" << std::endl;
	}

	int x_;
	int y_;
};

void c_api(Widget* ptr, size_t size)
{
	for (int i = 0; i < size; i++)
	{
		std::cout << *ptr << std::endl;
		++ptr;
	}
}
