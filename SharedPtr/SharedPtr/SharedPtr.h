#pragma once
#include <main.h>


template <typename T>
class SharedPtr
{
public:
	SharedPtr(T* resource)
	{
		m_ptr = resource; 
		m_ref_count = new int(1);
	}
	SharedPtr(const SharedPtr& other)
	{
		m_ref_count = other.m_ref_count;
		m_ptr = other.m_ptr;
		if (m_ref_count)
			*(m_ref_count)++;
	}
	SharedPtr& operator=(const SharedPtr& other)
	{
		if (this != &other) {
			free();
			m_ref_count = other.m_ref_count;
			m_ptr = other.m_ptr;
			if (m_ref_count)
				*(m_ref_count)++;
		}
		return *this;
	}

	T* operator->() const 
	{
		return m_ptr;
	}
	T& operator*() const 
	{
		if (m_ptr)
			return *m_ptr;
	}

	T Get() const
	{
		if (m_ptr)
			return *m_ptr;
	}

	int get_number_of_references() const
	{
		if (m_ref_count)
			return *(m_ref_count);
	}

	~SharedPtr()
	{
		free();
	}


private:
	T* m_ptr;
	int* m_ref_count;
	void free()
	{
		if (m_ref_count != nullptr)
		{
			if (--(*m_ref_count) == 0)
			{
				delete m_ref_count; 
				delete m_ptr;
				m_ref_count = nullptr;
				m_ptr = nullptr;
			}
		}
	}
};