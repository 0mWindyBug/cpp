#pragma once
#include <iostream>



template <typename T>
class Vector
{
public:
	struct	Iterator
	{
	public:
		Iterator(T* ptr) : m_ptr(ptr) {};
		T& operator*() const { return *m_ptr; };
		T* operator->() { return m_ptr; };
		Iterator& operator++() { m_ptr++; return *this; };
		Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; };
		friend bool operator==(const Iterator& lhs, const Iterator& rhs) { return lhs.m_ptr == rhs.m_ptr; };
		friend bool operator!=(const Iterator& lhs, const Iterator& rhs) { return lhs.m_ptr != rhs.m_ptr; };
	private:
		T* m_ptr;
	};

	Iterator begin() { return Iterator(&m_data[0]); };
	Iterator end() { return Iterator(&m_data[m_current]); };

	Vector()
	{
		std::cout << "[*] default ctor" << std::endl;
		m_data = new T[10];
		m_current = 0;
		m_capacity = 10;
	}
	~Vector()
	{
		std::cout << "[*] inside dtor " << std::endl;
		if (m_data)
		{
			std::cout << "[*] delete invoked" << std::endl;
				delete[] m_data;

		}
	}
	Vector(size_t capacity)
	{
		std::cout << "[*] param ctor" << std::endl;
		m_data = new T[capacity];
		m_current = 0;
		m_capacity = capacity;
	}
	Vector(const Vector& other)
	{
		std::cout << "[*] copy ctor" << std::endl;
		m_data = new T[other.m_capacity];
		m_current = other.m_current; 
		m_capacity = other.m_capacity;
		
		for (int i = 0; i < m_current; i++)
		{
			m_data[i] = other.m_data[i];
		}
	}
	Vector(Vector&& other) noexcept
	{
		std::cout << "[*] move ctor" << std::endl;
		m_data = other.m_data;
		m_capacity = other.m_capacity;
		m_current = other.m_current;

		other.m_data = nullptr;
		other.m_current = 0; 
		other.m_capacity = 0;
	}
	const Vector& operator=(const Vector& rhs)
	{
		std::cout << "[*] assigning vector" << std::endl;
		T* old = m_data;
		m_data = new T[rhs.m_capacity];
		m_current = rhs.m_current;
		m_capacity = rhs.m_capacity;

		for (int i = 0; i < m_current; i++)
		{
			m_data[i] = rhs.m_data[i];
		}

		delete[] old;
	}
	T& operator[](int index) { return m_data[index]; };
	const T& operator[](int index) const  { return m_data[index]; };
	int size() { return m_current; };
	int capacity() { return m_capacity; };
	void resize(int new_capacity)
	{
		std::cout << "[*] resizing vector " << std::endl;
		if (new_capacity > m_capacity)
		{
			T* old = m_data;
			m_data = new T[new_capacity];
			for (int i = 0; i < m_current; i++)
			{
				m_data[i] = old[i];
			}
			m_capacity = new_capacity;

			delete[] old;
		}
	}
	void push_back(const T& value)
	{
		if (m_current >= m_capacity)
			resize(m_capacity * 2);
		m_data[m_current++] = value;
	}
	void pop()
	{
		if (m_current > 0)
			m_current--;
	}
	void debug() const
	{
		for (int i = 0; i < m_current; i++)
		{
			std::cout << "[*] vector element : " << m_data[i] << std::endl;
		}
	}
private:
	T* m_data;
	size_t m_current;
	size_t m_capacity;
};