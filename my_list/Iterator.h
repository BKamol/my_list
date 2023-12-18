#pragma once

template <class T>
struct elem
{
	T data;
	elem* next;
};

template <class T>
class Iterator
{
protected:
	elem<T>* current;
	elem<T>* prev;

public:
	Iterator()
	{
		current = nullptr;
		prev = nullptr;
	}
	Iterator(elem<T>* _current, elem<T>* _prev=nullptr)
	{
		current = _current;
		prev = _prev;
	}

	T& operator*()
	{
		return current->data;
	}

	bool operator==(const Iterator& other)
	{
		return current == other.current;
	}
	bool operator!=(const Iterator& other)
	{
		return !(*this == other);
	}

	Iterator& operator++()
	{
		if (current)
			current = current->next;
		return *this;
	}
	Iterator& operator++(int)
	{
		Iterator it = *this;
		++*this;
		return it;
	}

	Iterator& operator--()
	{
		if (prev)
		{
			current = prev;
			prev--;
		}
		return *this;
	}
	Iterator& operator--(int)
	{
		Iterator it = *this;
		--*this;
		return it;
	}

	Iterator& operator+(int num)
	{
		while (num > 0)
		{
			*this++;
			num--;
		}
		return *this;
	}
	void operator+=(int num)
	{
		while (current && num > 0)
		{
			current++;
			prev++;
			num--;
		}
	}
	Iterator& operator-(int num)
	{
		while (num > 0)
		{
			*this--;
			num--;
		}
		return *this;
	}
	void operator-=(int num)
	{
		while (prev && num > 0)
		{
			current--;
			prev--;
			num--;
		}
	}

};