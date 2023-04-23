// Developed by Daniil Bilohrudov on 15.05.2022
#include <iostream>
#include "Trapezoid.h"
#include "IDeque.h"
#include "ListDeque.h"
#include "ArrayDeque.h"
#include "IPriorityQueue.h"
#include "ListPriorityQueue.h"
#include "ArrayPriorityQueue.h"
#include "PeekBack.h"
using namespace std;

template <typename T>
void testDeque(IDeque<T>& id);
template <typename T>
void testPriorityQueue(IPriorityQueue<T>& ipq);
template <typename T>
void testPeekBack(PeekBack<T>& pb);

int main()
{
	{
		// 1
		// trapezoid is initialized by 4 points in clockwise order
		// only two segments are parallel, and other two don't intersect
		Trapezoid abcd(Point(1, 1), Point(4, 7), Point(5, 4), Point(4, 2));
		Trapezoid clone(abcd);
		cout << "1. Trapezoid ABCD: " << abcd << endl;
		try
		{
			Trapezoid bad(Point(1, 1), Point(1, 2), Point(2, 2), Point(2, 1));
		}
		catch (Trapezoid::BadTrapezoid bt)
		{
			bt.diagnose();
		}
		// 2
		abcd.setApexB(Point(3, 5));
		cout << endl << "2. Apex B changed: " << abcd.apexB() << endl;
		// 3
		cout << endl << "3. Side AB: " << abcd.sideAB() << ",  length: " << abcd.sideAB().length() << endl;
		// 4
		cout << endl << "4. Perimeter = " << abcd.perimeter() << "; area = " << abcd.area() << endl;
		Trapezoid klmn(Point(3, 1), Point(2, 3), Point(4, 4), Point(6, 0)); // trapezoid with the same area
		cout << boolalpha;
		cout << "Trapezoid KLMN: " << klmn << endl;
		cout << "ABCD == KLMN: " << (abcd == klmn) << endl;
		cout << "ABCD new == ABCD old: " << (abcd == clone) << endl;
	}
	{
		// 5-8
		IDeque<char>* ld = new ListDeque<char>();
		IDeque<char>* ad = new ArrayDeque<char>();
		IDeque<char>* adu = new ArrayDequeUnlim<char>();

		cout << endl << "6. List Deque:" << endl;
		testDeque<char>(*ld);
		cout << endl << "7. Array Deque:" << endl;
		testDeque<char>(*ad);
		cout << endl << "8. Array Deque Unlim:" << endl;
		testDeque<char>(*adu);

		delete ld;
		delete ad;
		delete adu;
	}
	{
		// 9
		IPriorityQueue<char>* lpq = new ListPriorityQueue<char>();
		IPriorityQueue<char>* apq = new ArrayPriorityQueue<char>();
		IPriorityQueue<char>* apqu = new ArrayPriorityQueueUnlim<char>();
		cout << endl << "9. List Priority Queue:" << endl;
		testPriorityQueue<char>(*lpq);
		cout << endl << "Array Priority Queue:" << endl;
		testPriorityQueue<char>(*apq);
		cout << endl << "Array Priority Queue Unlim:" << endl;
		testPriorityQueue<char>(*apqu);

		delete lpq;
		delete apq;
		delete apqu;
	}
	{
		// 10
		cout << endl << "10. Peekback:" << endl;
		PeekBackDeque<char>* pd = new PeekBackArrayDeque<char>();
		(*pd).put('a').put('b').put('c');
		PeekBackPriorityQueue<char>* pq = new PeekBackListPriorityQueue<char>();
		(*pq).put('a', 1).put('b', 2).put('c', 3);

		cout << "Peekback deque: " << endl;
		pd->show();
		testPeekBack(*pd);
		cout << "Peekback queue: " << endl;
		pq->show();
		testPeekBack(*pq);

		delete pd;
		delete pq;
	}
	return 0;
}
template <typename T>
void testDeque(IDeque<T>& id)
{
	cout << "Put b, put c, put front a:" << endl;
	id.put('b').put('c').putFront('a');
	id.show();
	cout << "Front: " << id.front() << ", back: " << id.back();
	cout << ", size: " << id.size() << ", capacity: " << id.capacity() << endl;
	cout << "Get, get back:" << endl;
	id.get().getBack();
	id.show();
}
template <typename T>
void testPriorityQueue(IPriorityQueue<T>& ipq)
{
	ipq.put('a', 1).put('b', 3).put('c', 2);
	ipq.show();
	cout << "Front: " << ipq.front() << endl;
	ipq.pop();
	cout << "Pop, front: " << ipq.front() << endl;
	ipq.pop();
	cout << "Pop, front: " << ipq.front() << endl;
}
template <typename T>
void testPeekBack(PeekBack<T>& pb)
{
	T peek;
	pb.peekback(1, peek);
	cout << "Peekback[1]: " << peek << endl;
}