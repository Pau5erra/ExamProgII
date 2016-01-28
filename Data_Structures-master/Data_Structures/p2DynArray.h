// ----------------------------------------------------
// Array that resizes dynamically   -------------------
// ----------------------------------------------------

#ifndef __P2DYNARRAY_H__
#define __P2DYNARRAY_H__

#include "p2Defs.h"
#include <assert.h>

#define DYN_ARRAY_BLOCK_SIZE 16

template<class TYPE>
class p2DynArray
{
private:

	TYPE* data = nullptr;
	unsigned int	mem_capacity = 0;
	unsigned int	num_elements = 0;

public:

	// Constructors ------------------------------------------------------
	p2DynArray()
	{
		Alloc(DYN_ARRAY_BLOCK_SIZE);
	}

	p2DynArray(uint capacity)
	{
		Alloc(capacity);
	}

	// Destructor ---------------------------------------------------------
	~p2DynArray()
	{
		RELEASE_ARRAY(data);
	}

	// Operators ----------------------------------------------------------
	TYPE& operator[](uint index)
	{
		assert(index < num_elements);
		return data[index];
	}

	const TYPE& operator[](uint index) const
	{
		assert(index < num_elements);
		return data[index];
	}

	const p2DynArray<TYPE>& operator+= (const p2DynArray<TYPE>& array)
	{
		if(num_elements + array.num_elements > mem_capacity)
			Alloc(num_elements + array.num_elements);

		for(uint i = 0; i < array.num_elements; ++i)
			data[num_elements++] = array.data[i];

		return(*this);
	}

	// Data Management -----------------------------------------------------
	//PAU treu els repetits del dyn
	int remove_repeated(){

		p2DynArray<TYPE>* new_dyn(this);

		TYPE value;
		int times = 0;

		for (int i = 0; i < num_elements; i++){

			value = data[i];
			int take_count = 0;
			for (int j = 0; j < num_elements; j++){
				if (new_dyn->data[j] == value && take_count <= 0){
					take_count++;
				}
				else if (new_dyn->data[j] == value && take_count >= 0){
					erase(j);
					times++;
				}
			}
		}
	}

	void Fill(const TYPE& element){
		for (int i = 0; i < capacity(); i++){
			push_back(element);
		}
	}

	void push_back(const TYPE& element)
	{
		if(num_elements >= mem_capacity)
		{
			Alloc(mem_capacity + DYN_ARRAY_BLOCK_SIZE);
		}

		data[num_elements++] = element;
	}

	bool pop_back(TYPE& result)
	{
		if(num_elements > 0)
		{
			result = data[--num_elements];
			return true;
		}
		return false;
	}

	void clear()
	{
		num_elements = 0;
	}

	bool erase(uint index)
	{
		if(index < num_elements)
		{
			for(uint i = index; i < num_elements - 1; ++i)
			{
				data[i] = data[i + 1];
			}
			--num_elements;
			
			return true;
		}
		return false;
	}

	bool insert(const TYPE& element, uint position)
	{
		if(position > num_elements)
			return false;

		if(position == num_elements)
		{
			push_back(element);
			return true;
		}

		if(num_elements + 1 > mem_capacity)
			Alloc(mem_capacity + DYN_ARRAY_BLOCK_SIZE); // potential optimization if we do the Alloc manually

		for(uint i = num_elements; i > position; --i)
		{
			data[i] = data[i - 1];
		}

		data[position] = element;
		++num_elements;

		return true;
	}

	bool insert(const p2DynArray<TYPE>& array, uint position)
	{
		if(position > num_elements)
			return false;

		if(num_elements + array.num_elements > mem_capacity)
			Alloc(num_elements + array.num_elements + DYN_ARRAY_BLOCK_SIZE);

		for(uint i = position; i < position + array.num_elements; ++i)
		{
			data[i + array.num_elements] = data[i];
			data[i] = array[i - position];
			++num_elements;
		}

		return true;
	}

	TYPE* at(uint index)
	{
		if(index < num_elements)
			return &data[index];
		
		return nullptr;
	}

	const TYPE* at(uint index) const
	{
		if(index < num_elements)
			return &data[index];

		return nullptr;
	}

	void flip()
	{
		TYPE* start = &data[0];
		TYPE* end = &data[num_elements - 1];

		while(start < end)
			SWAP(*start++, *end--);
	}

	void shrink_to_fit()
	{
		if(num_elements < capacity)
		{
			Alloc(num_elements);
		}
	}

	uint find(const TYPE& value)
	{
		uint i = 0;
		for(; i < num_elements; ++i)
		{
			if(data[i] == value)
				break;
		}
		return i;
	}

	// Utils ------------------------------------------------------------
	uint capacity() const
	{
		return mem_capacity;
	}

	uint size() const
	{
		return num_elements;
	}

	bool empty() const
	{
		return num_elements == 0;
	}

	TYPE* front()
	{
		if(num_elements > 0)
			return &(data[0]);
		return nullptr;
	}

	const TYPE* front() const
	{
		if(num_elements > 0)
			return &(data[0]);
		return nullptr;
	}

	TYPE* back()
	{
		if(num_elements > 0)
			return &data[num_elements-1];
		return nullptr;
	}

	const TYPE* back() const
	{
		if(num_elements > 0)
			return &data[num_elements - 1];
		return nullptr;
	}

	// Sort -------------------------------------------------------------
	int BubbleSort()
	{
		int ret = 0;
		bool swapped = true;

		while(swapped)
		{
			swapped = false;
			for(unsigned int i = 0; i < num_elements - 2; ++i)
			{
				++ret;
				if(data[i] > data[i + 1])
				{
					SWAP(data[i], data[i + 1]);
					swapped = true;
				}
			}
		}

		return ret;
	}

	int BubbleSortOptimized()
	{
		int ret = 0;
		unsigned int count;
		unsigned int last = num_elements - 2;

		while(last > 0)
		{
			count = last;
			last = 0;
			for(unsigned int i = 0; i < count; ++i)
			{
				++ret;
				if(data[i] > data[i + 1])
				{
					SWAP(data[i], data[i + 1]);
					last = i;
				}
			}
		}
		return ret;
	}

	int CombSort()
	{
		int ret = 0;
		bool swapped = true;
		int gap = num_elements - 1;
		float shrink = 1.3f;

		while(swapped || gap > 1)
		{
			gap = MAX(1, gap / shrink);

			swapped = false;
			for(unsigned int i = 0; i + gap < num_elements - 1; ++i)
			{
				++ret;
				if(data[i] > data[i + gap])
				{
					SWAP(data[i], data[i + gap]);
					swapped = true;
				}
			}
		}

		return ret;
	}

private:

	// Allocates a new size and copies all data
	void Alloc(unsigned int mem)
	{
		TYPE* tmp = data;
		data = new TYPE[mem];

		mem_capacity = mem;
		num_elements = MIN(mem_capacity, num_elements);

		for(uint i = 0; i < num_elements; ++i)
			data[i] = tmp[i];

		RELEASE_ARRAY(tmp);
	}
};

#endif // __P2DYNARRAY_H__

/*

//constructors vector
#include <iostream>
#include <vector>

int main ()
{
// constructors used in the same order as described above:
std::vector<int> first;                                // empty vector of ints
std::vector<int> second (4,100);                       // four ints with value 100
std::vector<int> third (second.begin(),second.end());  // iterating through second
std::vector<int> fourth (third);                       // a copy of third

// the iterator constructor can also be used to construct from arrays:
int myints[] = {16,2,77,29};
std::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

std::cout << "The contents of fifth are:";
for (std::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
std::cout << ' ' << *it;
std::cout << '\n';

return 0;
}

// vector assign, operador igual Asignar contenido (función miembro pública)
#include <iostream>
#include <vector>

int main ()
{
std::vector<int> first;
std::vector<int> second;
std::vector<int> third;

first.assign (7,100);             // 7 ints with a value of 100

std::vector<int>::iterator it;
it=first.begin()+1;

second.assign (it,first.end()-1); // the 5 central values of first

int myints[] = {1776,7,4};
third.assign (myints,myints+3);   // assigning from array.

std::cout << "Size of first: " << int (first.size()) << '\n';
std::cout << "Size of second: " << int (second.size()) << '\n';
std::cout << "Size of third: " << int (third.size()) << '\n';
return 0;
}

//begin Return iterator to beginning (public member function )

// vector::begin/end
#include <iostream>
#include <vector>

int main ()
{
std::vector<int> myvector;
for (int i=1; i<=5; i++) myvector.push_back(i);

std::cout << "myvector contains:";
for (std::vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
std::cout << ' ' << *it;
std::cout << '\n';

return 0;
}

//end Return iterator to end (public member function )
// vector::begin/end
#include <iostream>
#include <vector>

int main ()
{
std::vector<int> myvector;
for (int i=1; i<=5; i++) myvector.push_back(i);

std::cout << "myvector contains:";
for (std::vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
std::cout << ' ' << *it;
std::cout << '\n';

return 0;
}

//size Return size (public member function )
// vector::size
#include <iostream>
#include <vector>

int main ()
{
std::vector<int> myints;
std::cout << "0. size: " << myints.size() << '\n';

for (int i=0; i<10; i++) myints.push_back(i);
std::cout << "1. size: " << myints.size() << '\n';

myints.insert (myints.end(),10,100);
std::cout << "2. size: " << myints.size() << '\n';

myints.pop_back();
std::cout << "3. size: " << myints.size() << '\n';

return 0;
}

//max_size Return maximum size (public member function )
#include <iostream>
#include <vector>

int main ()
{
std::vector<int> myvector;

// set some content in the vector:
for (int i=0; i<100; i++) myvector.push_back(i);

std::cout << "size: " << myvector.size() << "\n";
std::cout << "capacity: " << myvector.capacity() << "\n";
std::cout << "max_size: " << myvector.max_size() << "\n";
return 0;
}

//resize Change size (public member function )
#include <iostream>
#include <vector>

int main ()
{
std::vector<int> myvector;

// set some initial content:
for (int i=1;i<10;i++) myvector.push_back(i);

myvector.resize(5);
myvector.resize(8,100);
myvector.resize(12);

std::cout << "myvector contains:";
for (int i=0;i<myvector.size();i++)
std::cout << ' ' << myvector[i];
std::cout << '\n';

return 0;
}

//capacity Return size of allocated storage capacity (public member function )
#include <iostream>
#include <vector>

int main ()
{
std::vector<int> myvector;

// set some content in the vector:
for (int i=0; i<100; i++) myvector.push_back(i);

std::cout << "size: " << (int) myvector.size() << '\n';
std::cout << "capacity: " << (int) myvector.capacity() << '\n';
std::cout << "max_size: " << (int) myvector.max_size() << '\n';
return 0;
}

//empty Test whether vector is empty (public member function )
include <iostream>
#include <vector>

int main ()
{
std::vector<int> myvector;
int sum (0);

for (int i=1;i<=10;i++) myvector.push_back(i);

while (!myvector.empty())
{
sum += myvector.back();
myvector.pop_back();
}

std::cout << "total: " << sum << '\n';

return 0;
}

//reserve Request a change in capacity (public member function )
#include <iostream>
#include <vector>

int main ()
{
std::vector<int>::size_type sz;

std::vector<int> foo;
sz = foo.capacity();
std::cout << "making foo grow:\n";
for (int i=0; i<100; ++i) {
foo.push_back(i);
if (sz!=foo.capacity()) {
sz = foo.capacity();
std::cout << "capacity changed: " << sz << '\n';
}
}

std::vector<int> bar;
sz = bar.capacity();
bar.reserve(100);   // this is the only difference with foo above
std::cout << "making bar grow:\n";
for (int i=0; i<100; ++i) {
bar.push_back(i);
if (sz!=bar.capacity()) {
sz = bar.capacity();
std::cout << "capacity changed: " << sz << '\n';
}
}
return 0;
}

//Shrink to fit (public member function )
#include <iostream>
#include <vector>

int main ()
{
std::vector<int> myvector (100);
std::cout << "1. capacity of myvector: " << myvector.capacity() << '\n';

myvector.resize(10);
std::cout << "2. capacity of myvector: " << myvector.capacity() << '\n';

myvector.shrink_to_fit();
std::cout << "3. capacity of myvector: " << myvector.capacity() << '\n';

return 0;
}

//operator[] Access element (public member function )
#include <iostream>
#include <vector>

int main ()
{
std::vector<int> myvector (10);   // 10 zero-initialized elements

std::vector<int>::size_type sz = myvector.size();

// assign some values:
for (unsigned i=0; i<sz; i++) myvector[i]=i;

// reverse vector using operator[]:
for (unsigned i=0; i<sz/2; i++)
{
int temp;
temp = myvector[sz-1-i];
myvector[sz-1-i]=myvector[i];
myvector[i]=temp;
}

std::cout << "myvector contains:";
for (unsigned i=0; i<sz; i++)
std::cout << ' ' << myvector[i];
std::cout << '\n';

return 0;
}


//at Access element (public member function )
#include <iostream>
#include <vector>

int main ()
{
std::vector<int> myvector (10);   // 10 zero-initialized ints

// assign some values:
for (unsigned i=0; i<myvector.size(); i++)
myvector.at(i)=i;

std::cout << "myvector contains:";
for (unsigned i=0; i<myvector.size(); i++)
std::cout << ' ' << myvector.at(i);
std::cout << '\n';

//front Access first element (public member function )
#include <iostream>
#include <vector>

int main ()
{
std::vector<int> myvector;

myvector.push_back(78);
myvector.push_back(16);

// now front equals 78, and back 16

myvector.front() -= myvector.back();

std::cout << "myvector.front() is now " << myvector.front() << '\n';

return 0;
}

// vector::back
#include <iostream>
#include <vector>

int main ()
{
std::vector<int> myvector;

myvector.push_back(10);

while (myvector.back() != 0)
{
myvector.push_back ( myvector.back() -1 );
}

std::cout << "myvector contains:";
for (unsigned i=0; i<myvector.size() ; i++)
std::cout << ' ' << myvector[i];
std::cout << '\n';

return 0;
}

// vector::data
#include <iostream>
#include <vector>

int main ()
{
std::vector<int> myvector (5);

int* p = myvector.data();

*p = 10;
++p;
*p = 20;
p[2] = 100;

std::cout << "myvector contains:";
for (unsigned i=0; i<myvector.size(); ++i)
std::cout << ' ' << myvector[i];
std::cout << '\n';

return 0;
}

//Assign vector content (public member function )
#include <iostream>
#include <vector>

int main ()
{
std::vector<int> first;
std::vector<int> second;
std::vector<int> third;

first.assign (7,100);             // 7 ints with a value of 100

std::vector<int>::iterator it;
it=first.begin()+1;

second.assign (it,first.end()-1); // the 5 central values of first

int myints[] = {1776,7,4};
third.assign (myints,myints+3);   // assigning from array.

std::cout << "Size of first: " << int (first.size()) << '\n';
std::cout << "Size of second: " << int (second.size()) << '\n';
std::cout << "Size of third: " << int (third.size()) << '\n';
return 0;
}

//push_back Add element at the end (public member function )
include <iostream>
#include <vector>

int main ()
{
std::vector<int> myvector;
int myint;

std::cout << "Please enter some integers (enter 0 to end):\n";

do {
std::cin >> myint;
myvector.push_back (myint);
} while (myint);

std::cout << "myvector stores " << int(myvector.size()) << " numbers.\n";

return 0;
}

//pop_back Delete last element (public member function )
#include <iostream>
#include <vector>

int main ()
{
std::vector<int> myvector;
int sum (0);
myvector.push_back (100);
myvector.push_back (200);
myvector.push_back (300);

while (!myvector.empty())
{
sum+=myvector.back();
myvector.pop_back();
}

std::cout << "The elements of myvector add up to " << sum << '\n';

return 0;
}

//insert
#include <iostream>
#include <vector>

int main ()
{
std::vector<int> myvector (3,100);
std::vector<int>::iterator it;

it = myvector.begin();
it = myvector.insert ( it , 200 );

myvector.insert (it,2,300);

// "it" no longer valid, get a new one:
it = myvector.begin();

std::vector<int> anothervector (2,400);
myvector.insert (it+2,anothervector.begin(),anothervector.end());

int myarray [] = { 501,502,503 };
myvector.insert (myvector.begin(), myarray, myarray+3);

std::cout << "myvector contains:";
for (it=myvector.begin(); it<myvector.end(); it++)
std::cout << ' ' << *it;
std::cout << '\n';

return 0;
}

//erase
#include <iostream>
#include <vector>

int main ()
{
std::vector<int> myvector;

// set some values (from 1 to 10)
for (int i=1; i<=10; i++) myvector.push_back(i);

// erase the 6th element
myvector.erase (myvector.begin()+5);

// erase the first 3 elements:
myvector.erase (myvector.begin(),myvector.begin()+3);

std::cout << "myvector contains:";
for (unsigned i=0; i<myvector.size(); ++i)
std::cout << ' ' << myvector[i];
std::cout << '\n';

return 0;
}

//swap
#include <iostream>
#include <vector>

int main ()
{
std::vector<int> foo (3,100);   // three ints with a value of 100
std::vector<int> bar (5,200);   // five ints with a value of 200

foo.swap(bar);

std::cout << "foo contains:";
for (unsigned i=0; i<foo.size(); i++)
std::cout << ' ' << foo[i];
std::cout << '\n';

std::cout << "bar contains:";
for (unsigned i=0; i<bar.size(); i++)
std::cout << ' ' << bar[i];
std::cout << '\n';

return 0;
}

//clear
#include <iostream>
#include <vector>

int main ()
{
std::vector<int> myvector;
myvector.push_back (100);
myvector.push_back (200);
myvector.push_back (300);

std::cout << "myvector contains:";
for (unsigned i=0; i<myvector.size(); i++)
std::cout << ' ' << myvector[i];
std::cout << '\n';

myvector.clear();
myvector.push_back (1101);
myvector.push_back (2202);

std::cout << "myvector contains:";
for (unsigned i=0; i<myvector.size(); i++)
std::cout << ' ' << myvector[i];
std::cout << '\n';

return 0;
}

//emplace Construct and insert element (public member function )
#include <iostream>
#include <vector>

int main ()
{
std::vector<int> myvector = {10,20,30};

auto it = myvector.emplace ( myvector.begin()+1, 100 );
myvector.emplace ( it, 200 );
myvector.emplace ( myvector.end(), 300 );

std::cout << "myvector contains:";
for (auto& x: myvector)
std::cout << ' ' << x;
std::cout << '\n';

return 0;
}

//emplace back
#include <iostream>
#include <vector>

int main ()
{
std::vector<int> myvector = {10,20,30};

myvector.emplace_back (100);
myvector.emplace_back (200);

std::cout << "myvector contains:";
for (auto& x: myvector)
std::cout << ' ' << x;
std::cout << '\n';

return 0;
}

*/
