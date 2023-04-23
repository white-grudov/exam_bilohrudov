// Developed by Daniil Bilohrudov on 15.05.2022
#ifndef _PEEKBACK_H_
#define _PEEKBACK_H_
using namespace std;

template<typename T>
class IDeque;
template<typename T>
class IPriorityQueue;

template<typename T>
class PeekBack
{
public:
	PeekBack() {}
	virtual ~PeekBack() {}
	virtual bool peekback(const size_t i, T& elem) = 0;
};
template<typename T>
class PeekBackDeque : virtual public IDeque<T>, public PeekBack<T>
{
public:
	virtual ~PeekBackDeque() {}
	virtual bool peekback(const size_t i, T& elem) = 0;
};
template<typename T>
class PeekBackPriorityQueue : virtual public IPriorityQueue<T>, public PeekBack<T>
{
public:
	virtual ~PeekBackPriorityQueue() {}
	virtual bool peekback(const size_t i, T& elem) = 0;
};
#endif