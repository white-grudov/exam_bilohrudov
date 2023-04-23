// Developed by Daniil Bilohrudov on 15.05.2022
#ifndef _LIST_H_
#define _LIST_H_
#include <iostream>
using namespace std;

template<typename T>
class List
{
public:
	class BadList;
	explicit List();
	explicit List(initializer_list<T> args);
	~List();

	List& insert(const T& elem, size_t index = numeric_limits<size_t>::max());
	List& remove(size_t index = numeric_limits<size_t>::max());
	T& operator[](const size_t index);
	const T& operator[](const size_t index) const;

	size_t size() const { return _size; }
	bool empty() const { return _size == 0; }
	void clear();
private:
	struct ListNode
	{
		T elem;
		ListNode* next;
	};
	ListNode* _head;
	size_t _size;
	List(const List&) = delete;
	List& operator=(const List&) = delete;
};
template<typename T>
ostream& operator<<(ostream&, const List<T>&);
template<typename T>
class List<T>::BadList
{
public:
	BadList(const string& reason = "", const size_t = 0);
	~BadList() {}
	void diagnose() const;
private:
	size_t _index;
	string _reason;
};
template<typename T>
List<T>::BadList::BadList(const string& reason, const size_t index) : _reason(reason), _index(index)
{
	return;
}
template<typename T>
void List<T>::BadList::diagnose() const
{
	cerr << _reason;
	if (_index != 0)
		cerr << _index;
}
template<typename T>
List<T>::List() : _size(0), _head(nullptr)
{
	return;
}
template<typename T>
List<T>::List(initializer_list<T> args) : _size(args.size()), _head(nullptr)
{
	_head = new ListNode(args[0], nullptr);
	ListNode* current = _head;
	for (int i = 1; i < args.size(); ++i)
	{
		current->next = new ListNode(args[i], nullptr);
	}
	return;
}
template<typename T>
List<T>::~List()
{
	ListNode* first = _head;
	while (first != nullptr)
	{
		ListNode* next = first->next;
		delete first;
		first = next;
	}
	return;
}
template<typename T>
List<T>& List<T>::insert(const T& elem, size_t index)
{
	ListNode* newNode = new ListNode{ elem, nullptr };
	if (empty()) _head = newNode;
	else if (_size < index)
	{
		ListNode* current = _head;
		while (current->next != nullptr) current = current->next;
		current->next = newNode;
	}
	else if (index == 0)
	{
		newNode->next = _head;
		_head = newNode;
	}
	else
	{
		ListNode* current = _head;
		for (size_t i = 0; i < index - 1; ++i)
			current = current->next;
		newNode->next = current->next;
		current->next = newNode;
	}
	++_size;
	return *this;
}
template<typename T>
List<T>& List<T>::remove(size_t index)
{
	if (empty()) throw BadList("Deleting from empty list!");
	if (_size < index)
	{
		ListNode* current = _head;
		while (current->next->next != nullptr) current = current->next;
		delete current->next;
		current->next = nullptr;
	}
	else if (index == 0)
	{
		ListNode* temp = _head;
		_head = _head->next;
		delete temp;
	}
	else
	{
		ListNode* current = _head->next;
		ListNode* previous = _head;
		for (size_t i = 0; i < index - 1; ++i)
		{
			previous = current;
			current = current->next;
		}
		previous->next = current->next;
		delete current;
	}
	--_size;
	return*this;
}
template<typename T>
T& List<T>::operator[](const size_t index)
{
	if (_size <= index) throw BadList("Index error: ", index);
	ListNode* current = _head;
	for (size_t i = 0; i < index; ++i)
		current = current->next;
	return current->elem;
}
template<typename T>
const T& List<T>::operator[](const size_t index) const
{
	if (_size <= index) throw BadList("Index error: ", index);
	ListNode* current = _head;
	for (size_t i = 0; i < index; ++i)
		current = current->next;
	return current->elem;
}
template<typename T>
inline void List<T>::clear()
{
	ListNode* first = _head;
	while (first != nullptr)
	{
		ListNode* next = first->next;
		delete first;
		first = next;
	}
	_size = 0;
	_head = nullptr;
}
template<typename T>
ostream& operator<<(ostream& os, const List<T>& list)
{
	string chr = "[";
	for (size_t i = 0; i < list.size(); i++) {
		os << chr << list[i];
		if (chr == "[") chr = ", ";
	}
	os << ']';
	return os;
}
#endif