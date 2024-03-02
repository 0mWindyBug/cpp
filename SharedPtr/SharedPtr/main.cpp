#include <main.h>

template <typename T>
void print_shared_resource(const SharedPtr<T> ptr)
{
	std::cout << "[*] resource holds " << ptr.Get() << std::endl;

	std::cout << "[*] number of references to pointer is " << ptr.get_number_of_references() << std::endl;
}


int main()
{
	std::cout << "[*] shared ptr demonstration" << std::endl;

	std::string* resource = new std::string;
	*resource = "Hello World";

	SharedPtr<std::string> shared_ptr(resource);

	print_shared_resource(shared_ptr);


//	SharedPtr<std::string> another_shared_ptr = shared_ptr;
	


	return 0; 
}