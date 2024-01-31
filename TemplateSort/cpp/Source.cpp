#include <iostream>



template <typename t> void swap_elems(t* arr_i, t* arr_i_1)
{
	t temp;
	temp = *arr_i;
	*arr_i = *arr_i_1;
	*arr_i_1 = temp;
}

template <typename t> void sort_arr(t arr[] , int length)
{
	t temp;
	for (int i = 0; i < length - 1; i++)
	{
		for (int j = 0; j < length - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				swap_elems(&arr[j], &arr[j + 1]);
			}
		}
	}

}


template <typename t> void print_arr(t arr[], int length)
{
	for (int i = 0; i < length; i++)
	{
		std::cout << arr[i] << std::endl;
	}
}

int main()
{
	int arr[] = { 10, 2,3,4,22,0 };
	print_arr(arr, sizeof(arr) /4 );
	sort_arr(arr, sizeof(arr) /4 );
	std::cout << "\n\n sorted\n" << std::endl;
	print_arr(arr, sizeof(arr) /4 );






	return 0; 
}