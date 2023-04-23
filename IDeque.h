// Developed by Daniil Bilohrudov on 15.05.2022
#pragma once
#ifndef _IDEQUE_H_
#define _IDEQUE_H_
#include <iostream>
using namespace std;

template<typename T>
class IDeque
{
public:
	class BadDeque;
	IDeque() {}
	virtual ~IDeque() {}

	bool empty() const { return doEmpty(); }
	bool full() const { return doFull(); }
	size_t capacity() const { return doCapacity(); }
	size_t size() const { return doSize(); }
	const T& front() const { return doFront(); }
	const T& back() const { return doBack(); }
	IDeque<T>& get() { return doGet(); }
	IDeque<T>& getBack() { return doGetBack(); }
	IDeque<T>& put(const T& elem) { return doPut(elem); }
	IDeque<T>& putFront(const T& elem) { return doPutFront(elem); }
	void show() const { return doShow(); }
private:
	virtual bool doEmpty() const = 0;
	virtual bool doFull() const = 0;
	virtual size_t doCapacity() const = 0;
	virtual size_t doSize() const = 0;
	virtual const T& doFront() const = 0;
	virtual const T& doBack() const = 0;
	virtual IDeque<T>& doGet() = 0;
	virtual IDeque<T>& doGetBack() = 0;
	virtual IDeque<T>& doPut(const T& elem) = 0;
	virtual IDeque<T>& doPutFront(const T& elem) = 0;
	virtual void doShow() const = 0;

	IDeque(const IDeque&) = delete;
	IDeque& operator=(const IDeque&) = delete;
};
template<typename T>
class IDeque<T>::BadDeque
{
public:
	BadDeque(const string& reason = "", const size_t = 0);
	~BadDeque() {}
	void diagnose() const;
private:
	size_t _index;
	string _reason;
};
template<typename T>
IDeque<T>::BadDeque::BadDeque(const string& reason, const size_t index) : _reason(reason), _index(index)
{
	return;
}
template<typename T>
void IDeque<T>::BadDeque::diagnose() const
{
	cerr << _reason;
	if (_index != 0)
		cerr << _index;
}
#endif