#include <main.h>

#define TAG 'list'

// T must support 'next' and 'value' , value will be searchwd for in is_present 
// T must  overload the == operator 
// example type 

typedef struct kString
{
	UNICODE_STRING value;
	kString* next;
	bool operator==(const kString& other)
	{
		UNICODE_STRING value = this->value;
		UNICODE_STRING other_value = other.value;
		return !RtlCompareUnicodeString(&value, &other_value, false);
	}
}String , * pString;






template <typename T>
class kList
{
public:
	kList() { m_lock.Init(); m_head = nullptr; };

	void insert(T* NewObject)
	{
		AutoLock<Mutex> lock(m_lock);
		// build new node
		T* New = new(NonPagedPool, TAG)T;
		if (!New)
			return;
		RtlCopyMemory(New, NewObject, sizeof(T));
		New->next = nullptr;

		if (!m_head)
		{
			m_head = New;
			return;
		}
		T* current = m_head;
		while (current->next != nullptr)
			current = current->next;
		current->next = New;
	}

	bool is_present(T object)  {
		AutoLock<Mutex> lock(m_lock);
		if (!m_head)
			return false;
		T* current = m_head;
		while (current != nullptr)
		{
			if (*current == object)
				return true;
			current = current->next;
		}
		return false;
	}
	int count_elements()
	{
		AutoLock<Mutex> lock(m_lock);
		int count = 0;
		if (!m_head)
			return 0;
		T* current = m_head;
		while (current != nullptr)
		{
			count++;
			current = current->next;
		}
		return count;
	}
	void destroy()
	{
		AutoLock<Mutex> lock(m_lock);
		if (!m_head)
			return;
		T* current = m_head;
		while (current != nullptr)
		{
			DbgPrint("[*] inside iteration trying to delete\n");
			delete current;
			current = current->next;
		}
		m_head = nullptr;
	}

private:
	T* m_head;
	Mutex m_lock;
};