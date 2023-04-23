// Developed by Daniil Bilohrudov on 15.05.2022
#ifndef _LISTDEQUE_H_
#define _LISTDEQUE_H_
#include "List.h"
#include "PeekBack.h"

template <typename T>
class IDeque;

template <typename T>
class ListDeque : virtual public IDeque<T>
{
public:
	ListDeque() : _allocator(new List<T>())
	{
		return;
	}
	~ListDeque()
	{
		delete _allocator;
		return;
	}
protected:
	List<T>* _allocator;

private:
	bool doEmpty() const
	{
		return _allocator->size() == 0;
	}
	bool doFull() const
	{
		return _allocator->size() == numeric_limits<size_t>::max();
	}
	size_t doCapacity() const
	{
		return numeric_limits<size_t>::max();
	}
	size_t doSize() const
	{
		return _allocator->size();
	}
	const T& doFront() const
	{
		return (*_allocator)[0];
	}
	const T& doBack() const
	{
		return (*_allocator)[_allocator->size() - 1];
	}
	IDeque<T>& doGet()
	{
		if (doEmpty()) throw IDeque<T>::BadDeque("Trying to get from empty deque!");
		_allocator->remove(0);
		return *this;
	}
	IDeque<T>& doGetBack()
	{
		if (doEmpty()) throw IDeque<T>::BadDeque("Trying to get from empty deque!");
		_allocator->remove();
		return *this;
	}
	IDeque<T>& doPut(const T& elem)
	{
		_allocator->insert(elem);
		return *this;
	}
	IDeque<T>& doPutFront(const T& elem)
	{
		_allocator->insert(elem, 0);
		return *this;
	}
	void doShow() const
	{
		cout << *_allocator << endl;
	}
};
template <typename T>
class PeekBackListDeque : public ListDeque<T>, public PeekBackDeque<T>
{
	using LD = ListDeque<T>;
public:
	explicit PeekBackListDeque() : LD() {}
	virtual ~PeekBackListDeque() {}
	
	bool peekback(const size_t i, T& elem)
	{
		if (LD::_allocator->size() == 0) throw IDeque<T>::BadDeque("Trying to peek in empty deque!");
		if (i >= LD::_allocator->size()) return false;
		elem = (*LD::_allocator)[i];
		return true;
	}
};
#endif