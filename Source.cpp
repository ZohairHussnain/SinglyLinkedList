#include<iostream>
//#include"double.h"
using namespace std;
template <typename T>
class LinkedList
{
private:
	struct Node
	{
		T data;
		Node* next;
		Node() : data(0), next(nullptr){}
		Node(T data) : data(data), next(nullptr){}
	};
	Node* head;
	Node* tail;
public:
	LinkedList() : head(nullptr), tail(nullptr){}
	LinkedList(T data) : head(new Node(data)), tail(head){}
	LinkedList(const LinkedList& rhs)
	{
		cout << "LinkedList()" << endl;
		if (!rhs.head)
		{
			head = nullptr;
			return;
		}
		head = new Node(rhs.head->data);
		Node* current = head;
		for (Node* itr = rhs.head->next; itr != nullptr; itr = itr->next)
		{
			current->next = new Node(itr->data);
			current = current->next;
		}
		tail = current;
	}
	LinkedList& operator=(const LinkedList& rhs)
	{
		cout << "operator=()" << endl;
		if (this == &rhs) return *this;
		if (!rhs.head)
		{
			head = nullptr; return *this;
		}
		while (head)
		{
			Node* temp = head->next;
			delete head;
			head = temp;
		}
		head = new Node(rhs.head->data);
		Node* current = head;
		for (Node* itr = rhs.head->next; itr != nullptr; itr = itr->next)
		{
			current->next = new Node(itr->data);
			current = current->next;
		}
		tail = current;
		return *this;
	}
	~LinkedList()
	{
		cout << "~LinkedList()" << endl;
		while (head)
		{
			Node* temp = head->next;
			delete head;
			head = temp;
		}
		tail = nullptr;
	}
	void push_front(T data)
	{
		Node* newNode = new Node(data);
		newNode->next = head;
		head = newNode;
		if (!tail)
			tail = head;
	}
	void push_back(T data)
	{
		Node* newNode = new Node(data);
		newNode->next = nullptr;
		if (tail)
			tail->next = newNode;
		else
			head = newNode;
		tail = newNode;
	}
	T pop_front()
	{
		if (!head)
		{
			throw runtime_error("List is empty, cannot pop!");
		}
		T val{ head->data };
		Node* temp = head->next;
		delete head;
		head = temp;
		if (!head)
			tail = nullptr;
		return val;
	}
	T pop_back()
	{
		if (!tail)
			throw runtime_error("List is empty, cannot pop!");
		T val{ tail->data };
		if (head == tail)
		{
			delete tail;
			head = tail = nullptr;
			return val;
		}
		Node* current = head;
		while (current->next != tail)
			current = current->next;
		delete tail;
		tail = current;
		tail->next = nullptr;
		return val;

	}
	int size() const
	{
		int size{0};
		for (auto itr = head; itr != nullptr; itr = itr->next)
			size++;
		return size;
	}
	class iterator
	{
	private:
		Node* current;
	public:
		iterator() : current(nullptr){}
		iterator(Node* node) : current(node){}
		T& operator*()
		{
			return current->data;
		}
		bool operator!=(const iterator& rhs) const
		{
			return rhs.current != current;
		}
		iterator& operator++()
		{
			if (current) current = current->next;
			return *this;
		}
		iterator operator++(int)
		{
			iterator temp = *this;
			if(current) current = current->next;
			return temp;
		}
	};
	iterator begin() const
	{
		return iterator(head);
	}
	iterator end() const
	{
		return iterator(nullptr);
	}
	LinkedList(LinkedList&& rhs) noexcept
	{
		cout << "LinkedList(&&)" << endl;
		head = rhs.head;
		rhs.head = nullptr;
		rhs.tail = nullptr;
	}
	LinkedList& operator=(LinkedList&& rhs) noexcept
	{
		cout << "operator=(&&)" << endl;
		if (this == &rhs) return *this;
		while (head)
		{
			Node* temp = head->next;
			delete head;
			head = temp;
		}
		head = rhs.head;
		tail = rhs.tail;
		rhs.head = nullptr;
		rhs.tail = nullptr;
		return *this;
	}
};

