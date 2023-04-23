// Developed by Daniil Bilohrudov on 15.05.2022
#ifndef _ARRAY_DEQUE_H_
#define _ARRAY_DEQUE_H_
#include "Array.h"
#include "PeekBack.h"
const static size_t DEQUE_DEFAULT_SIZE = 100;

template <typename T>
class IDeque;
template <typename T>
class ArrayDeque : virtual public IDeque<T>
{
public:
	ArrayDeque(size_t capacity = DEQUE_DEFAULT_SIZE) : _allocator(new Array<T>(capacity)) , _size(0)
	{
		return;
	}
	~ArrayDeque()
	{
		delete _allocator;
		return;
	}
protected:
	Array<T>* _allocator;
	size_t _size;

private:
	bool doEmpty() const
	{
		return _size == 0;
	}
	bool doFull() const
	{
		return _size == _allocator->size();
	}
	size_t doCapacity() const
	{
		return _allocator->size();;
	}
	size_t doSize() const
	{
		return _size;
	}
	const T& doFront() const
	{
		return (*_allocator)[0];
	}
	const T& doBack() const
	{
		return (*_allocator)[_size - 1];
	}
	IDeque<T>& doGet()
	{
		if (doEmpty()) throw IDeque<T>::BadDeque("Trying to get from empty deque!");
		for (size_t i = 1; i < _size; ++i)
			(*_allocator)[i - 1] = (*_allocator)[i];
		(*_allocator)[_size - 1] = NULL;
		--_size;
		return *this;
	}
	IDeque<T>& doGetBack()
	{
		if (doEmpty()) throw IDeque<T>::BadDeque("Trying to get from empty deque!");
		(*_allocator)[_size - 1] = NULL;
		--_size;
		return *this;
	}
	IDeque<T>& doPut(const T& elem)
	{
		if (doFull()) throw IDeque<T>::BadDeque("Deque is full!", _allocator->size());
		(*_allocator)[_size] = elem;
		++_size;
		return *this;
	}
	IDeque<T>& doPutFront(const T& elem)
	{
		if (doFull()) throw IDeque<T>::BadDeque("Deque is full!", _allocator->size());
		for (size_t i = _size; i > 0; --i)
			(*_allocator)[i] = (*_allocator)[i - 1];
		(*_allocator)[0] = elem;
		++_size;
		return *this;
	}
	void doShow() const
	{
		string chr = "[";
		for (size_t i = 0; i < _size; i++)
		{
			cout << chr << (*_allocator)[i];
			if (chr == "[") chr = ", ";
		}
		cout << ']' << endl;
	}
};
template <typename T>
class ArrayDequeUnlim : public ArrayDeque<T>, virtual public IDeque<T>
{
	using AD = ArrayDeque<T>;
public:
	explicit ArrayDequeUnlim() : AD()
	{
		return;
	}
	virtual ~ArrayDequeUnlim() { }
private:
	IDeque<T>& doPut(const T& value)
	{
		if (AD::_size == AD::_allocator->size()) enlarge();
		(*AD::_allocator)[AD::_size] = value;
		++AD::_size;
		return *this;
	}
	IDeque<T>& doPutFront(const T& elem)
	{
		if (AD::_size == AD::_allocator->size()) enlarge();
		for (size_t i = AD::_size; i > 0; --i)
			(*AD::_allocator)[i] = (*AD::_allocator)[i - 1];
		(*AD::_allocator)[0] = elem;
		++AD::_size;
		return *this;
	}
	void enlarge()
	{
		Array<T>* newArray = new Array<T>(2 * AD::_allocator->size() + AD::capacity() + 1);
		for (size_t i = 0; i < AD::_size; i++)
			(*newArray)[i] = (*AD::_allocator)[i];
		delete AD::_allocator;

		AD::_allocator = newArray;
	}
};
template <typename T>
class PeekBackArrayDeque : public ArrayDeque<T>, public PeekBackDeque<T>
{
	using AD = ArrayDeque<T>;
public:
	explicit PeekBackArrayDeque(size_t capacity = DEQUE_DEFAULT_SIZE) : AD(capacity) {}
	virtual ~PeekBackArrayDeque() {}

	bool peekback(const size_t i, T& elem)
	{
		if (AD::_size == 0) throw IDeque<T>::BadDeque("Trying to peek in empty deque!");
		if (i >= AD::_size) return false;
		elem = (*AD::_allocator)[i];
		return true;
	}
};
template <typename T>
class PeekBackArrayDequeUnlim : public ArrayDequeUnlim<T>, public PeekBackDeque<T>
{
	using ADU = ArrayDequeUnlim<T>;
public:
	explicit PeekBackArrayDequeUnlim() : ADU() {}
	virtual ~PeekBackArrayDequeUnlim() {}

	bool peekback(const size_t i, T& elem)
	{
		if (ADU::_size == 0) throw IDeque<T>::BadDeque("Trying to peek in empty deque!");
		if (i >= ADU::_size) return false;
		elem = (*ADU::_allocator)[i];
		return true;
	}
};
#endif