#include <iostream>
#include "Vector.h"

template <typename T>
Vector<T> build_vector(const T& value, size_t count)
{
	Vector<T> v;
	for (int i = 0; i < count; i++)
	{
		v.push_back(value);
	}
	return v;
}



int main()
{
	std::cout << "[*] instantuating vector " << std::endl;

	// this invokes a deafult ctor + move ctor 
	/*Vector<int> vec1(std::move(build_vector(8, 2)));
	vec1.debug();
	*/ 

	// this invokes param ctor + resize
	
	Vector<int>vec2(2);
	vec2.push_back(10);
	vec2.push_back(12);
	vec2.push_back(14);


	for (auto it = vec2.begin(); it != vec2.end(); it++)
	{
		std::cout << "[*] iterator points at : " << *it << std::endl;
		*it = 2; // in order to prevent that from the user we can const qualify the * operator Iterator reference 
	}
	
	vec2.debug();

	/*
	std::string str = "Hello World";
	std::string str2 = "World Hello";

	Vector<std::string> v3;
	v3.push_back(str);
	v3.push_back(str2);
	Vector<std::string>v4 = v3;
	v4.debug();
	*/


}