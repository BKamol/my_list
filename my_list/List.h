#pragma once
#include <iostream>

using namespace std;

template <class T>
struct elem
{
	T data;
	elem* next;
};

template <class T>
class List
{
protected:
	elem<T>* top;
	elem<T>* p;
	elem<T>* prev;

	void delete_first()
	{
		if (top)
		{
			elem<T>* q = top;
			top = top->next;
			delete q;
		}
	}
	void del_list()
	{
		while (top)
			delete_first();
		p = nullptr;
		prev = nullptr;
	}


public:
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
		Iterator(elem<T>* _current, elem<T>* _prev = nullptr)
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

	List()
	{
		top = nullptr;
		p = nullptr;
		prev = nullptr;
	}

	List(List& other)
	{
		other.to_start();
		while (other.p)
		{
			push_back(other.p->data);
			other.next();
		}
	}

	List(List&& moved)
	{
		top = moved.top;
		p = moved.p;
		prev = moved.prev;
		moved.top = nullptr;
		moved.p = nullptr;
		moved.prev = nullptr;
	}

	void next()
	{
		if (p)
		{
			prev = p;
			p = p->next;
		}
	}

	bool is_end()
	{
		return p && p->next == nullptr;
	}
	bool is_empty()
	{
		return top == nullptr;
	}
	void to_start()
	{
		p = top;
		prev = nullptr;
	}

	void push_back(T data)
	{
		elem<T>* q = new elem<T>;
		q->data = data;
		q->next = nullptr; 
		if (is_empty())
		{
			top = q;
			p = q;
		}
		else
		{
			while (!is_end())
				next();
			p->next = q;
		}
		to_start();
	}

	friend istream& operator>>(istream& in, List& other)
	{
		if (other.top) other.del_list();
		cout << "Input size of list: " << endl;
		int n;
		in >> n;
		cout << "Input " << n << " elements of list: " << endl;
		T data;
		for (int i = 0; i < n; i++)
		{
			in >> data;
			other.push_back(data);
		}
		return in;
	}

	friend ostream& operator<<(ostream& out, List& other)
	{
		if (other.is_empty())
		{
			out << "Empty list" << endl;
			return out;
		}
		other.to_start();
		out << "( ";
		while (other.p)
		{
			out << other.p->data << ' ';
			other.next();
		}
		out << ")" << endl;
		other.to_start();
		return out;
	}

	void add_after_current(T data)
	{
		elem<T>* q = new elem<T>;
		q->data = data;
		q->next = p->next;
		p->next = q;
	}
	void add_before_current(T data)
	{
		elem<T>* q = new elem<T>;
		q->data = data;
		if (prev != nullptr)
		{
			q->next = prev->next;
			prev->next = q;
		}
		else
		{
			q->next = top;
			top = q;
		}
	}

	List& operator=(List& other)
	{
		if (this == &other)
			return *this;
		if (top != nullptr)
			del_list();
		other.to_start();
		T data;
		while (other.p)
		{
			data = other.p->data;
			push_back(data);
			other.next();
		}
		other.to_start();
		return *this;
	}

	bool operator==(List& other)
	{
		to_start();
		other.to_start();
		while (p && other.p)
		{
			if (p->data != other.p->data)
				return false;
			next();
			other.next();
		}
		if (!p && other.p || p && !other.p)
			return false;
		return true;
	}

	bool contains(T data)
	{
		bool c = false;
		to_start();
		while (p && !c)
		{
			if (p->data == data) c = true;
			next();
		}
		to_start();
		return c;
	}

	elem<T>* get_p() { return p; }
	T get_value() { return p->data; }

	Iterator begin()
	{
		return Iterator(top, nullptr);
	}
	Iterator end()
	{
		to_start();
		while (p) next();
		elem<T>* _p = p;
		elem<T>* _prev = prev;
		to_start();
		return Iterator(_p, _prev);
	}

	~List()
	{
		del_list();
	}
};

template <class T>
class SortedList : public List<T>
{
public:
	SortedList<T>() : List<T>() {};

	SortedList<T>(List<T>& other)
	{
		other.to_start();
		while (other.get_p())
		{
			insert(other.get_value());
			other.next();
		}
		other.to_start();
	}

	void insert(T data)
	{

		List<T>::to_start();
		if (List<T>::top == nullptr)
			List<T>::push_back(data);
		else if (data < List<T>::top->data)
		{
			elem<T>* q = new elem<T>;
			q->data = data;
			q->next = nullptr;
			q->next = List<T>::top;
			List<T>::top = q;
		}
		else
		{
			while (List<T>::p->next && data > List<T>::p->next->data)
				List<T>::next();
			List<T>::add_after_current(data);
		}
	}

	void add_before_current(T data)
	{
		insert(data);
	}
	void add_after_current(T data)
	{
		insert(data);
	}

	friend istream& operator>>(istream& in, SortedList& other)
	{
		cout << "Input size of list: " << endl;
		int n;
		in >> n;
		cout << "Input " << n << " elements :" << endl;
		T data;
		for (int i = 0; i < n; i++)
		{
			in >> data;
			other.insert(data);
		}
		return in;
	};
};