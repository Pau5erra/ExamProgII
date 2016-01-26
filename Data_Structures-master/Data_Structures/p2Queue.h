// ----------------------------------------------------
// FIFO implementation with single linked list  -------
// ----------------------------------------------------

#ifndef __p2Queue_H__
#define __p2Queue_H__

#include "p2Defs.h"
#include "p2SList.h"

/**
* Queue using a single linked list
*/
template<class TYPE>
class p2Queue
{
public:

	/**
	* Get Size
	*/
	unsigned int size() const
	{
		return list.size();
	}

	/**
	* push new item
	*/
	void push(const TYPE& item)
	{
		list.push_back(item);
	}

	/**
	* Deletes an item from the list
	*/
	bool pop(TYPE& item)
	{
		return list.pop_front(item);
	}

	/**
	* Reads the next value to pop
	*/
	const TYPE* peek() const
	{
		return list.front();
	}

	/**
	* Destroy and free all mem
	*/
	void clear()
	{
		list.clear();
	}

	/**
	* Check if it is empty
	*/
	bool empty()
	{
		return list.empty();
	}

private:
	p2SList<TYPE> list;

};
#endif /*__p2Queue_H__*/

/*

// constructing queues
#include <iostream>       // std::cout
#include <deque>          // std::deque
#include <list>           // std::list
#include <queue>          // std::queue

int main ()
{
std::deque<int> mydeck (3,100);        // deque with 3 elements
std::list<int> mylist (2,200);         // list with 2 elements

std::queue<int> first;                 // empty queue
std::queue<int> second (mydeck);       // queue initialized to copy of deque

std::queue<int,std::list<int> > third; // empty queue with list as underlying container
std::queue<int,std::list<int> > fourth (mylist);

std::cout << "size of first: " << first.size() << '\n';
std::cout << "size of second: " << second.size() << '\n';
std::cout << "size of third: " << third.size() << '\n';
std::cout << "size of fourth: " << fourth.size() << '\n';

return 0;
}

// queue::empty
#include <iostream>       // std::cout
#include <queue>          // std::queue

int main ()
{
std::queue<int> myqueue;
int sum (0);

for (int i=1;i<=10;i++) myqueue.push(i);

while (!myqueue.empty())
{
sum += myqueue.front();
myqueue.pop();
}

std::cout << "total: " << sum << '\n';

return 0;
}

// queue::size
#include <iostream>       // std::cout
#include <queue>          // std::queue

int main ()
{
std::queue<int> myints;
std::cout << "0. size: " << myints.size() << '\n';

for (int i=0; i<5; i++) myints.push(i);
std::cout << "1. size: " << myints.size() << '\n';

myints.pop();
std::cout << "2. size: " << myints.size() << '\n';

return 0;
}

// queue::front
#include <iostream>       // std::cout
#include <queue>          // std::queue

int main ()
{
std::queue<int> myqueue;

myqueue.push(77);
myqueue.push(16);

myqueue.front() -= myqueue.back();    // 77-16=61

std::cout << "myqueue.front() is now " << myqueue.front() << '\n';

return 0;
}

// queue::back
#include <iostream>       // std::cout
#include <queue>          // std::queue

int main ()
{
std::queue<int> myqueue;

myqueue.push(12);
myqueue.push(75);   // this is now the back

myqueue.back() -= myqueue.front();

std::cout << "myqueue.back() is now " << myqueue.back() << '\n';

return 0;
}

// queue::push/pop
#include <iostream>       // std::cin, std::cout
#include <queue>          // std::queue

int main ()
{
std::queue<int> myqueue;
int myint;

std::cout << "Please enter some integers (enter 0 to end):\n";

do {
std::cin >> myint;
myqueue.push (myint);
} while (myint);

std::cout << "myqueue contains: ";
while (!myqueue.empty())
{
std::cout << ' ' << myqueue.front();
myqueue.pop();
}
std::cout << '\n';

return 0;
}

// queue::emplace
#include <iostream>       // std::cin, std::cout
#include <queue>          // std::queue
#include <string>         // std::string, std::getline(string)

int main ()
{
std::queue<std::string> myqueue;

myqueue.emplace ("First sentence");
myqueue.emplace ("Second sentence");

std::cout << "myqueue contains:\n";
while (!myqueue.empty())
{
std::cout << myqueue.front() << '\n';
myqueue.pop();
}

return 0;
}

// queue::push/pop
#include <iostream>       // std::cin, std::cout
#include <queue>          // std::queue

int main ()
{
std::queue<int> myqueue;
int myint;

std::cout << "Please enter some integers (enter 0 to end):\n";

do {
std::cin >> myint;
myqueue.push (myint);
} while (myint);

std::cout << "myqueue contains: ";
while (!myqueue.empty())
{
std::cout << ' ' << myqueue.front();
myqueue.pop();
}
std::cout << '\n';

return 0;
}

// queue::swap
#include <iostream>       // std::cout
#include <queue>          // std::queue

int main ()
{
std::queue<int> foo,bar;
foo.push (10); foo.push(20); foo.push(30);
bar.push (111); bar.push(222);

foo.swap(bar);

std::cout << "size of foo: " << foo.size() << '\n';
std::cout << "size of bar: " << bar.size() << '\n';

return 0;
}

*/