#include <iostream>
#include <vector>
#include <ostream>
#include <iostream>
#include <functional>

#include "../include/vector.hpp"
#include "../include/Widget.hpp"
#include "../include/string.hpp"
#include "../include/Unique_ptr.hpp"
#include "../include/shared_ptr.hpp"
#include "../include/ThreadPool.hpp"

void Test_Vector();
void Test_String();
void Test_UniquePtr();
void Test_SharedPtr();
void Test_ThreadPool();

int main()
{	
	Test_Vector();
}

void Test_ThreadPool()
{
	custom::ThreadPool<std::function<void()>> tp(3);
	std::function<void()> func([]() { std::cout << "Executing task on " << std::this_thread::get_id() << std::endl; });

	for (int i = 0; i < 10; i++)
	{
		tp.AddTask(func);
		std::this_thread::sleep_for(std::chrono::seconds(2));
	}

	tp.Stop();
}

void Test_SharedPtr()
{
	custom::shared_ptr sp1 = custom::make_shared<Widget>(2, 3);

	auto sp2 = sp1; // copy construtor
		
	custom::shared_ptr<Widget> sp3;
	sp3 = sp1; // assignment operator	

	custom::shared_ptr<Widget> sp4 = std::move(sp3); // move constructor
}

void Test_UniquePtr()
{
	auto instance = custom::make_unique<Widget>(11, 12);
	if (instance)
		std::cout << instance->x_ << ", " << instance->y_ << std::endl;

	auto in = std::make_unique<Widget>(11, 12);
	if (in)
		std::cout << in->x_ << ", " << in->y_ << std::endl;

	custom::unique_ptr<Widget> p(new Widget(1,2));	
	if (p)
		std::cout << p->x_ << std::endl;
	else
		std::cout << "Not pointing to anything" << std::endl;
	auto val = p.release();
	delete val;

	if (p)
		std::cout << p->x_ << std::endl;		
	else
	{
		std::cout << "Not pointing to anything" << std::endl;
		p.reset(new Widget(3, 4));
	}

	 auto p2 = std::move(p);	
	
	custom::unique_ptr<Widget[]> ptr(new Widget[2]);
	ptr[0].x_ = 20;
	ptr[0].y_ = 30;

	ptr[1].x_ = 40;
	ptr[1].y_ = 50;

	std::cout << ptr[1] << std::endl;
}

void Test_String()
{
	std::string str;
	custom::string cstr;
	std::string str1("Mithun");
	custom::string cstr1("Mithun");
	std::cout << str1.size() << ", " << cstr1.size() << std::endl;
	std::cout << str1.capacity() << ", " << cstr1.capacity() << std::endl;
	std::string str2 = "Murthy";
	custom::string cstr2 = "Murthy";

	str1 += str2;
	cstr1 += cstr2;

	if (str1 != str2)
	{
		std::cout << "They are not equal" << std::endl;
	}

	if (cstr1 != cstr2)
	{
		std::cout << "They are not equal" << std::endl;
	}

	str2 = str1;
	if (str1 == str2)
	{
		std::cout << "They are equal" << std::endl;
	}
	cstr2 = cstr1;
	if (cstr1 == cstr2)
	{
		std::cout << "They are equal" << std::endl;
	}

	if (str1.empty())
		std::cout << "String is null" << std::endl;

	if ( cstr1.empty())
		std::cout << "String is null" << std::endl;

	std::cout << str1.size() << std::endl;
	std::cout << cstr1.size() << std::endl;

	std::string str3 = std::move(str1);
	custom::string cstr3 = std::move(cstr1);

	auto str4 = str3 + str2;
	auto cstr4 = cstr3 + cstr2;
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