// Developed by Daniil Bilohrudov on 15.05.2022
#ifndef _LIST_PRIORITY_QUEUE_H_
#define _LIST_PRIORITY_QUEUE_H_
#include "List.h"
#include "PeekBack.h"

template <typename T>
class IPriorityQueue;

template <typename T>
class ListPriorityQueue : virtual public IPriorityQueue<T>
{
public:
	struct Record;
	ListPriorityQueue() : _allocator(new List<Record>()), _highestPriority(0)
	{
		return;
	}
	~ListPriorityQueue()
	{
		delete _allocator;
		return;
	}

protected:
	List<Record>* _allocator;
	size_t _highestPriority;

private:
	bool doEmpty() const
	{
		return _allocator->size() == 0;
	}
	bool doFull() const
	{
		return _allocator->size() == numeric_limits<size_t>::max();
	}
	const T& doFront() const
	{
		size_t i = -1;
		while ((*_allocator)[++i].priority != _highestPriority);
		return (*_allocator)[i].elem;
	}
	IPriorityQueue<T>& doPop()
	{
		if (doEmpty()) throw IPriorityQueue<T>::BadPriorityQueue("Trying to pop from empty queue!");
		size_t i = -1;
		while ((*_allocator)[++i].priority != _highestPriority);
		_allocator->remove(i);
		if (_allocator->size() != 0)
		{
			i = 1;
			size_t newPriority = (*_allocator)[0].priority;
			for (; i < _allocator->size(); ++i)
				newPriority = (*_allocator)[i].priority > newPriority ? (*_allocator)[i].priority : newPriority;
			_highestPriority = newPriority;
		}
		return *this;
	}
	IPriorityQueue<T>& doPut(const T& value, const size_t priority)
	{
		_highestPriority = priority > _highestPriority ? priority : _highestPriority;
		_allocator->insert(Record{ value, priority });
		return *this;
	}
	size_t doCapacity() const
	{
		return numeric_limits<size_t>::max();
	}
	size_t doSize() const
	{
		return _allocator->size();
	}
	void doShow()
	{
		string chr = "[";
		for (size_t i = 0; i < _allocator->size(); i++) {
			cout << chr << "(" << (*_allocator)[i].elem << ", " << (*_allocator)[i].priority << ")";
			if (chr == "[") chr = ", ";
		}
		cout << ']' << endl;
	}
};
template<typename T>
struct ListPriorityQueue<T>::Record
{
	T elem;
	size_t priority;
};
template <typename T>
class PeekBackListPriorityQueue : public ListPriorityQueue<T>, public PeekBackPriorityQueue<T>
{
	using LPQ = ListPriorityQueue<T>;
public:
	explicit PeekBackListPriorityQueue() : LPQ() {}
	virtual ~PeekBackListPriorityQueue() {}

	bool peekback(const size_t i, T& elem)
	{
		if (LPQ::_allocator->size() == 0) throw IPriorityQueue<T>::BadPriorityQueue("Trying to peek in empty priority queue!");
		if (i >= LPQ::_allocator->size()) return false;
		elem = (*LPQ::_allocator)[i].elem;
		return true;
	}
};
#endif