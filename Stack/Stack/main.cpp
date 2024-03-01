#include <main.h>

template <typename T>
void compare_stacks(const Stack<T>& stack1, const Stack<T>& stack2)
{
	if (stack1 == stack2)
		std::cout << "[*] stacks are equal" << std::endl;
	else
		std::cout << "[*] stacks are not equal" << std::endl;
}

template <typename T>
void sum_stacks(const Stack<T>& stack1, const Stack<T>& stack2)
{
	std::cout << "[*] sum of stacks elements is " << stack1 + stack2 << std::endl;
}


int main()
{
	std::cout << "[*] instantuating a stack" << std::endl;

	Stack<int> stack(2);
	Stack<int>stack2(1);

	stack.push(10);
	stack.push(12);
	stack2.push(22);


	compare_stacks(stack, stack2);

	Stack<int> stack3(stack2);
	Stack<int> stack4 = stack3;

	stack4.pop();

	compare_stacks(stack4,stack);

	sum_stacks(stack, stack4);
	
	Stack<int> stack5(std::move(stack2));

	//	stack2.push(10);  this will crush dont do this 
	stack5.push(10);

	std::cout << "[*] finished" << std::endl;

	return 0; 
}