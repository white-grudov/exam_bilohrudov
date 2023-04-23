// Developed by Daniil Bilohrudov on 15.05.2022
#pragma once
#ifndef _IPRIORITY_QUEUE_H_
#define _IPRIORITY_QUEUE_H_
#include <iostream>
using namespace std;

template<typename T>
class IPriorityQueue
{
public:
	class BadPriorityQueue;
	IPriorityQueue() {}
	virtual ~IPriorityQueue() {}

	bool empty() const { return doEmpty(); }
	bool full() const { return doFull(); }
	const T& front() const { return doFront(); }
	IPriorityQueue<T>& pop() { return doPop(); }
	IPriorityQueue<T>& put(const T& value, const size_t priority) { return doPut(value, priority); }
	size_t capacity() const { return doCapacity(); }
	size_t size() const { return doSize(); }
	void show() { return doShow(); }
private:
	virtual bool doEmpty() const = 0;
	virtual bool doFull() const = 0;
	virtual const T& doFront() const = 0;
	virtual IPriorityQueue<T>& doPop() = 0;
	virtual IPriorityQueue<T>& doPut(const T& value, const size_t priority) = 0;
	virtual size_t doCapacity() const = 0;
	virtual size_t doSize() const = 0;
	virtual void doShow() = 0;

	IPriorityQueue(const IPriorityQueue&) = delete;
	IPriorityQueue& operator=(const IPriorityQueue&) = delete;
};
template<typename T>
class IPriorityQueue<T>::BadPriorityQueue
{
public:
	BadPriorityQueue(const string& reason = "", const size_t = 0);
	~BadPriorityQueue() {}
	void diagnose() const;
private:
	size_t _index;
	string _reason;
};
template<typename T>
IPriorityQueue<T>::BadPriorityQueue::BadPriorityQueue(const string& reason, const size_t index) : _reason(reason), _index(index)
{
	return;
}
template<typename T>
void IPriorityQueue<T>::BadPriorityQueue::diagnose() const
{
	cerr << _reason;
	if (_index != 0)
		cerr << _index;
}
#endif