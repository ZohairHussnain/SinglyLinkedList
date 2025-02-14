#pragma once
#include<iostream>
using namespace std;

class List
{
private:
	struct Node
	{
		int data;
		Node* next;
		Node* prev;
		Node() : data(0), next(nullptr), prev(nullptr) {}
		Node(int data) : data(data), next(nullptr), prev(nullptr) {}
	};
	Node* head;
	Node* tail;
public:
	List() : head(nullptr), tail(nullptr) {}
	List(int data) : head(new Node(data)), tail(head) {}
	List(const List& rhs)
	{
		cout << "List()" << endl;
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
	}
	List& operator=(const List& rhs)
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

		return *this;
	}
	~List()
	{
		cout << "~List()" << endl;
		while (head)
		{
			Node* temp = head->next;
			delete head;
			head = temp;
		}
	}
	void push(int data)
	{
		Node* newNode = new Node(data);
		newNode->next = head;
		//newNode->prev = head;
		head = newNode;
	}
	void push_back(int data)
	{

	}
	int pop()
	{
		if (!head)
		{
			throw runtime_error("List is empty, cannot pop!");
		}
		int val{ head->data };
		Node* temp = head->next;
		delete head;
		head = temp;
		return val;
	}
	int size() const
	{
		int size{ 0 };
		for (auto itr = head; itr != nullptr; itr = itr->next)
			size++;
		return size;
	}
	class iterator
	{
	private:
		Node* current;
	public:
		iterator() : current(nullptr) {}
		iterator(Node* node) : current(node) {}
		int& operator*()
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
			if (current) current = current->next;
			return temp;
		}
	};
	iterator begin()
	{
		return iterator(head);
	}
	iterator end()
	{
		return iterator(nullptr);
	}
	List(List&& rhs) noexcept
	{
		cout << "List(&&)" << endl;
		head = rhs.head;
		rhs.head = nullptr;
	}
	List& operator=(List&& rhs) noexcept
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
		rhs.head = nullptr;
		return *this;
	}
};
