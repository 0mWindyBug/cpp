#pragma once
#include <main.h>

// allow * and + , == and cctor 
// implement iterator that will tarverse the stack and print all elements 


template <typename  T>
class Stack
{
public:
	Stack(size_t capacity)
	{
		std::cout << "[*] deafult ctor called" << std::endl;
		m_stack = new T[capacity];
		m_capacity = capacity;
		m_size = 0;
	}
	Stack(const Stack<T>& other)
	{
		std::cout << "[*] copy ctor called" << std::endl;
		T* old_stack = m_stack;
		m_stack = new T[other.m_size];
		memcpy(m_stack, other.m_stack, other.m_size);
		m_size = other.m_size;
		m_capacity = other.m_capacity;
		delete[] old_stack;
	}
	Stack(Stack<T>&& other) noexcept
		: m_stack(nullptr), m_size(0), m_capacity(0)
	{
		std::cout << "[*] move ctor called" << std::endl;
		T* old_stack = m_stack;

		m_stack = other.m_stack;
		m_size = other.m_size;
		m_capacity = other.m_capacity;

		other.m_stack = nullptr;
		other.m_size = 0;
		other.m_capacity = 0;

		delete[] old_stack;
	}
	~Stack()
	{
		std::cout << "[*] dtor called" << std::endl;
		if (m_stack)
		{
			delete[] m_stack;

		}
	}
	bool push(T element)
	{
		if (is_full())
			return false;
		m_stack[m_size] = element;
		m_size++;
		return true;
	}
	bool pop()
	{
		if (is_empty())
			return false;

		m_size--;
		return true;
	}
	bool operator==(const Stack<T>& other) const
	{
		if(this->sum() == other.sum())
			return true;
		return false;
	}
	Stack& operator=(const Stack& other)
	{
		if (this != other)
		{
			T* old_stack = m_stack;
			m_stack = new T[other.m_size];
			memcpy(m_stack, other.m_stack, other.m_size);
			m_size = other.m_size;
			m_capacity = other.m_capacity;
			delete[] old_stack;
		}
		return *this;
	}
	int operator+(const Stack& other) const 
	{
		return other.sum() + this->sum();
	}



private: 
	T* m_stack;
	size_t m_size;
	size_t m_capacity;
	int sum() const
	{
		int s = 0;
		for (int i = 0; i < m_size; i++)
		{
			s += m_stack[i];
		}
		return s;
	}
	bool is_full() { return m_capacity <= m_size; };
	bool is_empty() { return m_size == 0; };
};
