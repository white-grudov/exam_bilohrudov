// Developed by Daniil Bilohrudov on 15.05.2022
#ifndef _ARRAY_H_
#define _ARRAY_H_
#include <iostream>
using namespace std;

template<typename T>
class Array
{
public:
	class BadArray;
	explicit Array(size_t size);
	explicit Array(initializer_list<T> args);
	~Array();
	T& operator[](const size_t index);
	const T& operator[](const size_t index) const;
	size_t size() const { return _size; }
private:
	const size_t _size;
	T* _allocator;
	Array(const Array&) = delete;
	Array& operator=(const Array&) = delete;
};
template<typename T>
ostream& operator<<(ostream&, const Array<T>&);
template<typename T>
class Array<T>::BadArray
{
public:
	BadArray(const string& reason = "", const size_t = 0);
	~BadArray() {}
	void diagnose() const;
private:
	size_t _index;
	string _reason;
};
template<typename T>
Array<T>::BadArray::BadArray(const string& reason, const size_t index) : _reason(reason), _index(index)
{
	return;
}
template<typename T>
void Array<T>::BadArray::diagnose() const
{
	cerr << _reason;
	if (_index != 0)
		cerr << _index;
}

template<typename T>
Array<T>::Array(size_t size) : _size(size), _allocator(new T[_size])
{
	for (size_t count = 0; count < _size; ++count) _allocator[count] = NULL;
	return;
}
template<typename T>
inline Array<T>::Array(initializer_list<T> args) : _size(args.size()), _allocator(new T[_size])
{
	int count = 0;
	for (auto& element : args)
	{
		_allocator[count] = element;
		if (++count > _size) throw BadArray("Bad array size: ", _size);
	}
	for (count; count < _size; ++count) _allocator[count] = NULL;
	return;
}
template<typename T>
Array<T>::~Array()
{
	delete[] _allocator;
	return;
}
template<typename T>
const T& Array<T>::operator[](const size_t index) const
{
	if (index >= _size) throw BadArray("Index error: ", index);
	return _allocator[index];
}
template<typename T>
T& Array<T>::operator[](const size_t index)
{
	if (index >= _size) throw BadArray("Index error: ", index);
	return _allocator[index];
}
template<typename T>
ostream& operator<<(ostream& os, const Array<T>& arr)
{
	string chr = "[";
	for (size_t i = 0; i < arr.size(); i++)
	{
		if (arr[i] == NULL) continue;
		os << chr << arr[i];
		if (chr == "[") chr = ", ";
	}
	os << ']';
	return os;
}
#endif
