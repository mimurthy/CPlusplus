#include <iostream>
#include <vector>
#include <ostream>
#include "../include/vector.hpp"
#include "../include/Widget.hpp"

void Test_Vector();

int main()
{	
	Test_Vector();
}

void Test_Vector()
{
	//custom::Vector<Widget> v1;
	custom::vector<Widget> v2(5, 10, 12);
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
	custom::vector<Widget> v1 = std::move(v2);
	c_api(v1.data(), v1.size());

	// TODO: test with iterators 

	// TODO: test with algorithms	
}