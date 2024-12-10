#include <iostream>
#include <vector>
#include <ostream>
#include "../vector/include/Vector.hpp"

class Widget
{
public:

	//Widget()
	//{
	//	cout << "Default Constructor" << endl;
	//}

	Widget(int x, int y) : x_(x), y_(y)
	{
		//cout << "Parameterized Constructor" << endl;
	}

	Widget(const Widget& rhs)
	{
		//cout << "Copy constructor" << endl;
		x_ = rhs.x_;
		y_ = rhs.y_;
	}

	Widget(const Widget&& rhs)
	{
		//cout << "Move constructor" << endl;
		x_ = rhs.x_;
		y_ = rhs.y_;
	}

	Widget& operator = (const Widget& rhs)
	{
		//cout << "Copy assignment operator" << endl;
		x_ = rhs.x_;
		y_ = rhs.y_;
		return *this;
	}

	Widget& operator = (const Widget&&)
	{
		//cout << "Move assignment operator" << endl;
		return *this;
	}

	friend std::ostream& operator << (std::ostream& os, const Widget& w)
	{
		os << w.x_ << ", " << w.y_;
		return os;
	}

	~Widget()
	{
		//cout << "Destructor" << endl;
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

int main()
{	
	//custom::Vector<Widget> v1;
	custom::Vector<Widget> v2(5, 10, 12);
	//custom::Vector<Widget> v3 = { (1,2), (4,5), (8,9) };
	
	Widget w(20, 30);
	v2.push_back(w);
	v2.push_back(w);
	v2.emplace_back(Widget(40, 50));

	for (int i = 0; i < v2.size(); i++)
	{
		std::cout << v2[i] << std::endl;
	}	
	
	v2.pop_back();
	std::cout << "Size = " << v2.size() << std::endl;
	std::cout << "Capacity = " << v2.capacity() << std::endl;
		
	v2.resize(3);
	v2.shrink_to_fit();
	for (int i = 0; i < v2.size(); i++)
	{
		std::cout << v2[i] << std::endl;
	}

	auto& v4 = v2;	
	custom::Vector<Widget> v1 = std::move(v2);
	c_api(v1.data(), v1.size());
	
	// TODO: test with iterators 
	
	// TODO: test with algorithms	
}
