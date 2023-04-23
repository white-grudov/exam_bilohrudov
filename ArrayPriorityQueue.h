// Developed by Daniil Bilohrudov on 15.05.2022
#ifndef _ARRAY_PRIORITY_QUEUE_H_
#define _ARRAY_PRIORITY_QUEUE_H_
#include "Array.h"
#include "PeekBack.h"

const static size_t QUEUE_DEFAULT_SIZE = 100;
template <typename T>
class IPriorityQueue;

template <typename T>
class ArrayPriorityQueue : virtual public IPriorityQueue<T>
{
public:
	struct Record;
	ArrayPriorityQueue(const size_t capacity = QUEUE_DEFAULT_SIZE) : _allocator(new Array<Record*>(QUEUE_DEFAULT_SIZE)),
		_size(0), _highestPriority(0)
	{
		return;
	}
	~ArrayPriorityQueue()
	{
		delete _allocator;
		return;
	}
protected:
	Array<Record*>* _allocator;
	size_t _highestPriority;
	size_t _size;

	bool doEmpty() const
	{
		return _size == 0;
	}
	bool doFull() const
	{
		return _size == _allocator->size();
	}
	const T& doFront() const
	{
		size_t i = -1;
		while ((*_allocator)[++i]->priority != _highestPriority);
		return (*_allocator)[i]->elem;
	}
	IPriorityQueue<T>& doPop()
	{
		if (doEmpty()) throw IPriorityQueue<T>::BadPriorityQueue("Trying to pop from empty queue!");
		size_t i = -1;
		while ((*_allocator)[++i]->priority != _highestPriority);
		delete (*_allocator)[i];
		(*_allocator)[i++] = nullptr;
		for (; i < _size; ++i)
		{
			(*_allocator)[i - 1] = (*_allocator)[i];
			(*_allocator)[i] = nullptr;
		}
		--_size;
		if (_size != 0)
		{
			i = 1;
			size_t newPriority = (*_allocator)[0]->priority;
			for (; i < _size; ++i)
				newPriority = (*_allocator)[i]->priority > newPriority ? (*_allocator)[i]->priority : newPriority;
			_highestPriority = newPriority;
		}
		return *this;
	}
	IPriorityQueue<T>& doPut(const T& value, const size_t priority)
	{
		if (doFull()) throw IPriorityQueue<T>::BadPriorityQueue("Queue is full!", _allocator->size());
		_highestPriority = priority > _highestPriority ? priority : _highestPriority;
		(*_allocator)[_size] = new Record{value, priority};
		++_size;
		return *this;
	}
	size_t doCapacity() const
	{
		return _allocator->size();
	}
	size_t doSize() const
	{
		return _size;
	}
	void doShow()
	{
		string chr = "[";
		for (size_t i = 0; i < _size; i++) {
			cout << chr << "(" << (*_allocator)[i]->elem << ", " << (*_allocator)[i]->priority << ")";
			if (chr == "[") chr = ", ";
		}
		cout << ']' << endl;
	}
};
template <typename T>
class ArrayPriorityQueueUnlim : public ArrayPriorityQueue<T>, virtual public IPriorityQueue<T>
{
	using APQ = ArrayPriorityQueue<T>;
public:
	explicit ArrayPriorityQueueUnlim() : APQ()
	{
		return;
	}
	virtual ~ArrayPriorityQueueUnlim() { }
private:
	IPriorityQueue<T>& doPut(const T& value, const size_t priority)
	{
		if (APQ::doFull()) enlarge();
		APQ::_highestPriority = priority > APQ::_highestPriority ? priority : APQ::_highestPriority;
		(*APQ::_allocator)[APQ::_size] = new APQ::template Record{ value, priority };
		++APQ::_size;
		return *this;
	}
	void enlarge()
	{
		Array<APQ::template Record*>* newArray = new Array<APQ::template Record*>
			(2 * APQ::_allocator->size() + APQ::capacity() + 1);
		for (size_t i = 0; i < APQ::_size; i++)
		{
			(*newArray)[i] = (*APQ::_allocator)[i];
			(*APQ::_allocator)[i] = nullptr;
		}
		delete APQ::_allocator;

		APQ::_allocator = newArray;
	}
};
template<typename T>
struct ArrayPriorityQueue<T>::Record
{
	T elem;
	size_t priority;
};
template <typename T>
class PeekBackArrayPriorityQueue : public ArrayPriorityQueue<T>, public PeekBackPriorityQueue<T>
{
	using APQ = ArrayPriorityQueue<T>;
public:
	explicit PeekBackArrayPriorityQueue(size_t capacity = QUEUE_DEFAULT_SIZE) : APQ(capacity) {}
	virtual ~PeekBackArrayPriorityQueue() {}

	bool peekback(const size_t i, T& elem)
	{
		if (APQ::_size == 0) throw IPriorityQueue<T>::BadPriorityQueue("Trying to peek in empty deque!");
		if (i >= APQ::_size) return false;
		elem = (*APQ::_allocator)[i]->elem;
		return true;
	}
};
template <typename T>
class PeekBackArrayPriorityQueueUnlim : public ArrayPriorityQueueUnlim<T>, public PeekBackPriorityQueue<T>
{
	using APQU = ArrayPriorityQueueUnlim<T>;
public:
	explicit PeekBackArrayPriorityQueueUnlim() : APQU() {}
	virtual ~PeekBackArrayPriorityQueueUnlim() {}

	bool peekback(const size_t i, T& elem)
	{
		if (APQU::_size == 0) throw IPriorityQueue<T>::BadPriorityQueue("Trying to peek in empty deque!");
		if (i >= APQU::_size) return false;
		elem = (*APQU::_allocator)[i]->elem;
		return true;
	}
};
#endif