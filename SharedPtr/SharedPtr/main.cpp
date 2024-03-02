#include <main.h>

template <typename T>
void print_shared_resource_no_ref(const SharedPtr<T>& ptr)
{
	std::cout << "[*] resource holds " << ptr.Get() << std::endl;

	std::cout << "[*] number of references to pointer is " << ptr.get_number_of_references() << std::endl;
}

template <typename T>
void print_shared_resource_take_ref(const SharedPtr<T> ptr)
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

	print_shared_resource_take_ref(shared_ptr);
	print_shared_resource_no_ref(shared_ptr);

//	SharedPtr<std::string> another_shared_ptr = shared_ptr;
	


	return 0; 
}