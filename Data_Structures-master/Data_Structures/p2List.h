#ifndef __p2List_H__
#define __p2List_H__

#include "p2Defs.h"

/**
* Manages a double linked list
*/
template<class TYPE>
class p2List
{
public:

	/**
	* Node implementation
	*/
	struct node
	{
		friend class p2List<TYPE>;
	public:
		mutable TYPE	data;

		inline node* next() const // hauria de ser const ho se
		{
			return nxt;
		}
		inline const node* prev() const
		{
			return prv;
		}

	private:
		node*   nxt = nullptr;
		node*   prv = nullptr;

		node(const TYPE& data) : data(data)
		{}

		/* mmm .... something to think about :)
		~node()
		{
		if(prv)
		prv->nxt = nullptr;
		if(nxt)
		nxt->prv = nullptr;
		}
		*/
	};

private:

	node*   start = nullptr;

public:

	// Constructors ------------------------------------------------------
	p2List(){}
	p2List(const p2List<TYPE>& new_list){

		node* new_node = new_list.start;
		while (new_node != NULL){
			this->push_back(new_node->data);
			new_node = new_node->next;
		}
	}
	// Destructor ---------------------------------------------------------
	~p2List()
	{
		clear();
	}

	// Operators ----------------------------------------------------------
	const p2List<TYPE>& operator +=(const p2List<TYPE>& list)
	{
		node* item = list.start;
		node* last = back_node();

		while(item != nullptr)
		{
			node* new_item = new node(item->data);

			if(last != nullptr)
			{
				new_item->prv = last;
				last->nxt = new_item;
			}
			else
				start = new_item;

			item = item->nxt;
			last = new_item;
		}

		return(*this);
	}

	// Data Management -----------------------------------------------------

	node* push_back(const TYPE& data)
	{
		node* item = new node(data);
		node* last = back_node();

		if(last != nullptr)
		{
			item->prv = last;
			last->nxt = item;
		}
		else
			start = item;

		return item;
	}

	node* push_front(const TYPE& item)
	{
		node* item = new node(item);

		if(start != nullptr)
		{
			item->nxt = start;
			start->prv = item;
		}
		
		start = item;

		return item;
	}

	bool pop_back(TYPE& data)
	{
		node* last = back_node();

		if(last != nullptr)
		{
			data = last->data;
			if(last->prv != nullptr)
				last->prv->nxt = nullptr;
			else
				start = nullptr;
			
			RELEASE(last);
			return true;
		}

		return false;
	}

	bool pop_front(TYPE& data)
	{
		if(start != nullptr)
		{
			data = start->data;
			node* second_node = start->nxt;
			RELEASE(start); // start is reset to nullptr inside RELEASE

			if(second_node != nullptr)
			{
				start = second_node;
				start->prv = nullptr;
			}
			return true;
		}
		return false;
	}

	void clear()
	{
		node*   item;
		node*   item_next;
		item = start;

		while(item != nullptr)
		{
			item_next = item->nxt;
			RELEASE(item);
			item = item_next;
		}

		start = nullptr;
	}

	node* Remove(uint position){
		node* new_node = new node(NULL);
		if (position > size()){
			printf("T'has passat\n");
		}
		else{
			node* tmp = start;
			if (tmp == NULL){
				printf("No hi ha llista\n");
			}
			else{

				for (uint i = 1; i < position; i++){
					tmp = tmp->nxt;
				}
				if (position == 1){
					if (tmp->nxt == NULL){
						start = NULL;
					}
					else{
						start = tmp->nxt;
						tmp->nxt->prv = NULL;
					}
					//node = tmp;
					new_node->data = tmp->data;
					delete tmp;
				}
				else if (position == size()){
					tmp->prv->nxt = NULL;
					//	node = tmp;
					new_node->data = tmp->data;
					delete tmp;
				}
				else{
					tmp->prv->nxt = tmp->nxt;
					tmp->nxt->prv = tmp->prv;
					//node = tmp;
					new_node->data = tmp->data;
					delete tmp;
				}
			}
		}
		return new_node;
	}

	bool erase(uint index)
	{
		node* item = at(index);
		

		if(item != nullptr)
		{
			if(item->nxt != nullptr)
				item->nxt->prv = item->prv;

			if(item->prv != nullptr)
				item->prv->nxt = item->nxt;
			new_node->data = item->data;
			RELEASE(item);
			return true;
		}
		return false;
	}

	bool erase(node* item)
	{
		if(item != nullptr)
		{
			if(item->nxt != nullptr)
				item->nxt->prv = item->prv;

			if(item->prv != nullptr)
				item->prv->nxt = item->nxt;

			RELEASE(item);
			return true;
		}
		return false;
	}

	void Insert(uint position, const TYPE& new_data){

		if (position > size() + 1){
			printf("T'has passat\n");
		}
		else{
			node* new_node = new node(new_data);
			node* tmp = start;

			if (position = size() + 1){
				position = size();
			}

			for (uint i = 1; i < position; i++){
				tmp = tmp->nxt;
			}
			if (start == NULL){
				start = new_node;
				new_node->prv = NULL;
				new_node->nxt = NULL;
			}
			else if (tmp->nxt == NULL){
				tmp->nxt = new_node;
				new_node->prv = tmp;
				new_node->nxt = NULL;
			}
			else{
				new_node->nxt = tmp;
				new_node->prv = tmp->prv;
				tmp->prv->nxt = new_node;
				tmp->prv = new_node;
			}
		}
	}

	bool insert(const TYPE& data, uint position)
	{
		node* item = at_node(position);

		if(item != nullptr)
		{
			node* new_item = new node(data);
			new_item->nxt = item;
			new_item->prv = item->prv;

			if(new_item->prv != nullptr)
				new_item->prv->nxt = new_item;

			item->prv = new_item;
			return true;
		}

		return false;
	}

	bool insert(const p2List<TYPE>& list, uint position)
	{
		node* item = at_node(position);
		node* other_list = list.start;

		if(item != nullptr && other_list != nullptr)
		{
			// copy the whole list
			node* start_new_list = nullptr;
			node* end_new_list = nullptr;

			while(other_list != nullptr)
			{
				node* new_item = new node(other_list->data);

				if(start_new_list != nullptr)
				{
					new_item->prv = end_new_list;
					end_new_list->nxt = new_item;
				}
				else
					start_new_list = new_item;

				end_new_list = new_item;
				other_list = other_list->nxt;
			}

			// now exchange pointers
			end_new_list->nxt = item;
			start_new_list->prv = item->prv;

			if(start_new_list->prv != nullptr)
				start_new_list->prv->nxt = start_new_list;

			item->prv = end_new_list;

			return true;
		}
		return false;
	}

	TYPE* at(uint index)
	{
		uint counter = 0;
		node* item = start;

		while(item != nullptr)
		{
			if(counter++ == index)
				return &(item->data);
			item = item->nxt;
		}

		return nullptr;
	}

	const TYPE* at(uint index) const
	{
		uint counter = 0;
		node* item = start;

		while(item != nullptr)
		{
			if(counter++ == index)
				return &(item->data);
			item = item->nxt;
		}

		return nullptr;
	}

	node* at_node(uint index)
	{
		uint counter = 0;
		node* item = start;

		while(item != nullptr)
		{
			if(counter++ == index)
				return item;
			item = item->nxt;
		}

		return nullptr;
	}

	const node* at_node(uint index) const
	{
		uint counter = 0;
		node* item = start;

		while(item != nullptr)
		{
			if(counter++ == index)
				return item;
			item = item->nxt;
		}

		return nullptr;
	}

	// Utils ------------------------------------------------------------
	uint size() const
	{
		uint ret = 0;

		for(node* item = start; item != nullptr; item = item->nxt)
			++ret;

		return ret;
	}

	bool empty() const
	{
		return start == nullptr;
	}

	node* front_node()
	{
		return start;
	}

	const node* front_node() const
	{
		return start;
	}

	node* back_node()
	{
		node* item = start;
		node* last_item = nullptr;
		while(item != nullptr)
		{
			last_item = item;
			item = item->nxt;
		}

		return last_item;
	}

	const node* back_node() const
	{
		node* item = start;
		node* last_item = nullptr;
		while(item != nullptr)
		{
			last_item = item;
			item = item->nxt;
		}

		return last_item;
	}

	TYPE* front()
	{
		if(start != nullptr)
			return &(start->data);
		return nullptr;
	}

	const node* front() const
	{
		if(start != nullptr)
			return &(start->data);
		return nullptr;
	}

	TYPE* back()
	{
		node* item = start;
		node* last_item = nullptr;
		while(item != nullptr)
		{
			last_item = item;
			item = item->nxt;
		}

		return (last_item != nullptr) ? &(last_item->data) : nullptr;
	}

	const TYPE* back() const
	{
		node* item = start;
		node* last_item = nullptr;
		while(item != nullptr)
		{
			last_item = item;
			item = item->nxt;
		}

		return (last_item != nullptr) ? &(last_item->data) : nullptr;
	}

	// Sort -------------------------------------------------------------
	int BubbleSort()
	{
		int ret = 0;
		bool swapped = true;

		while(swapped)
		{
			swapped = false;
			node* tmp = start;

			while(tmp != nullptr && tmp->nxt != nullptr)
			{
				++ret;
				if(tmp->data > tmp->nxt->data)
				{
					SWAP(tmp->data, tmp->nxt->data);
					swapped = true;
				}

				tmp = tmp->nxt;
			}
		}

		return ret;
	}

	//PAU
	//Remove duplicate values
	void Unique(){
		p2List<TYPE>* new_list(this);
		node* tmp1 = new_list->start;
		node* tmp = start;
		TYPE data;
		while (tmp1 != NULL){
			data = tmp1->data;
			tmp = start;
			int position = 1;
			int i = 0;
			while (tmp != NULL){
				int j = 0;
				if (data == tmp->data && i <= 0){
					i++;
				}
				else if (data == tmp->data && i >= 0){
					tmp = tmp->nxt;
					j++;
					this->Remove(position);
				}
				if (j <= 0){
					tmp = tmp->nxt;
					position++;
				}
			}
			tmp1 = tmp1->nxt;
		}

	}

	//Change node from a list to another list
	void Splice(int position_to_insert, int position_to_remove, p2List<TYPE>& list){
		const node* tmp = NULL;

		tmp = list.Remove(position_to_remove);
		this->Insert(position_to_insert, tmp->data);

	}

	//Flip the data of the list
	const p2List& Flip(){
		node* tmp = start;
		node* tmp1 = start;
		while (tmp1->nxt){
			tmp1 = tmp1->nxt;
		}
		TYPE save_data;
		int i = 0;
		while (i < this->size() / 2){
			save_data = tmp1->data;
			tmp1->data = tmp->data;
			tmp->data = save_data;
			tmp = tmp->nxt;
			tmp1 = tmp1->prv;
			i++;
		}

		return (*this);
	}

	//Swap de dos nodes
	void Swap(node* first, node* last){
		node* first_item = first;
		node* last_item = last;
		node* store_node;
		node* tmp_1;

		if (first_item->nxt == NULL && first_item->prv == NULL){
			printf("No linked");
		}
		else if (last_item->nxt == NULL && last_item->prv == NULL){
			printf("No linked");
		}
		else if (start == first_item && last->nxt == NULL){
			store_node = last_item->prv;
			tmp_1 = first_item->nxt;

			start = last_item;
			first_item->nxt = NULL;

			last_item->nxt = tmp_1;
			store_node->nxt = first_item;
		}
		else if (start == first_item && first_item->prv != NULL){
			store_node = last_item->prv;
			tmp_1 = first_item->nxt;

			start = last_item;
			first_item->nxt = last_item->nxt;

			last_item->nxt = tmp_1;
			store_node->nxt = first_item;

		}
		else if (last->nxt == NULL){
			store_node = last_item->prv;
			tmp_1 = first_item->prv;

			last_item->nxt = first_item->nxt;
			first_item->nxt = NULL;

			store_node->nxt = first_item;
			tmp_1->nxt = last_item;

		}
		else{
			store_node = last_item->prv;
			tmp_1 = first_item->nxt;

			first_item->nxt = last_item->nxt;
			last_item->nxt = tmp_1;

			tmp_1 = first_item->prv;
			tmp_1->nxt = last_item;
			store_node->nxt = first_item;

		}
	}

	//Assing new data to a node
	void Assign(node* new_node, const TYPE& new_data){
		new_node->data = new_data;
	}

	//Find a node given a value
	const node* Find(const TYPE& value)
	{
		node* item = start;

		while (item != nullptr)
		{
			if (item->data == value)
				return (item);
			item = item->nxt;
		}

		return nullptr;
	}

	//change ------------------------------------------------------------

	//mete los elementos del array dentro de la lista que le indicamos
	void change(const p2DynArray<TYPE>& _dynarray)
	{

		for (int i = 0; i < _dynarray.size(); i++)
		{
			this->push_back(_dynarray[i]);
		}


	}
};

#endif /*__p2List_H__*/

/*
// constructing lists
#include <iostream>
#include <list>

int main ()
{
// constructors used in the same order as described above:
std::list<int> first;                                // empty list of ints
std::list<int> second (4,100);                       // four ints with value 100
std::list<int> third (second.begin(),second.end());  // iterating through second
std::list<int> fourth (third);                       // a copy of third

// the iterator constructor can also be used to construct from arrays:
int myints[] = {16,2,77,29};
std::list<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

std::cout << "The contents of fifth are: ";
for (std::list<int>::iterator it = fifth.begin(); it != fifth.end(); it++)
std::cout << *it << ' ';

std::cout << '\n';

return 0;
}

// assignment operator with lists----- operator=
#include <iostream>
#include <list>

int main ()
{
  std::list<int> first (3);      // list of 3 zero-initialized ints
  std::list<int> second (5);     // list of 5 zero-initialized ints

  second = first;
  first = std::list<int>();

  std::cout << "Size of first: " << int (first.size()) << '\n';
  std::cout << "Size of second: " << int (second.size()) << '\n';
  return 0;
}

// list::begin
#include <iostream>
#include <list>

int main ()
{
int myints[] = {75,23,65,42,13};
std::list<int> mylist (myints,myints+5);

std::cout << "mylist contains:";
for (std::list<int>::iterator it=mylist.begin(); it != mylist.end(); ++it)
std::cout << ' ' << *it;

std::cout << '\n';

return 0;
}

// list::end
#include <iostream>
#include <list>

int main ()
{
int myints[] = {75,23,65,42,13};
std::list<int> mylist (myints,myints+5);

std::cout << "mylist contains:";
for (std::list<int>::iterator it=mylist.begin() ; it != mylist.end(); ++it)
std::cout << ' ' << *it;

std::cout << '\n';

return 0;
}

// list::rbegin-----Return reverse iterator to reverse beginning
#include <iostream>
#include <list>

int main ()
{
std::list<int> mylist;
for (int i=1; i<=5; ++i) mylist.push_back(i);

std::cout << "mylist backwards:";
for (std::list<int>::reverse_iterator rit=mylist.rbegin(); rit!=mylist.rend(); ++rit)
std::cout << ' ' << *rit;

std::cout << '\n';

return 0;
}

// list::rend-------Return reverse iterator to reverse end 
#include <iostream>
#include <list>

int main ()
{
std::list<int> mylist;
for (int i=1; i<=5; ++i) mylist.push_back(i);

std::cout << "mylist backwards:";
for (std::list<int>::reverse_iterator rit=mylist.rbegin(); rit!=mylist.rend(); ++rit)
std::cout << ' ' << *rit;

std::cout << '\n';

return 0;
}

// list::cbegin-----Return const_iterator to beginning
#include <iostream>
#include <list>

int main ()
{
std::list<int> mylist = {5,10,15,20};

std::cout << "mylist contains:";

for (auto it = mylist.cbegin(); it != mylist.cend(); ++it)
std::cout << ' ' << *it;

std::cout << '\n';

return 0;
}

// list::cend -------Return const_iterator to end
#include <iostream>
#include <list>

int main ()
{
std::list<int> mylist = {5,10,15,20};

std::cout << "mylist contains:";

for (auto it = mylist.cbegin(); it != mylist.cend(); ++it)
std::cout << ' ' << *it;

std::cout << '\n';

return 0;
}

// list::crbegin--------Return const_reverse_iterator to reverse beginning
#include <iostream>
#include <deque>

int main ()
{
std::list<int> mylist = {1,2,4,8,16};

std::cout << "mylist backwards:";
for (auto rit = mylist.crbegin(); rit != mylist.crend(); ++rit)
std::cout << ' ' << *rit;
std::cout << '\n';

return 0;
}

// list::crend--------------Return const_reverse_iterator to reverse end
#include <iostream>
#include <deque>

int main ()
{
std::list<int> mylist = {1,2,4,8,16};

std::cout << "mylist backwards:";
for (auto rit = mylist.crbegin(); rit != mylist.crend(); ++rit)
std::cout << ' ' << *rit;
std::cout << '\n';

return 0;
}

// list::empty
#include <iostream>
#include <list>

int main ()
{
std::list<int> mylist;
int sum (0);

for (int i=1;i<=10;++i) mylist.push_back(i);

while (!mylist.empty())
{
sum += mylist.front();
mylist.pop_front();
}

std::cout << "total: " << sum << '\n';

return 0;
}

// list::size
#include <iostream>
#include <list>

int main ()
{
std::list<int> myints;
std::cout << "0. size: " << myints.size() << '\n';

for (int i=0; i<10; i++) myints.push_back(i);
std::cout << "1. size: " << myints.size() << '\n';

myints.insert (myints.begin(),10,100);
std::cout << "2. size: " << myints.size() << '\n';

myints.pop_back();
std::cout << "3. size: " << myints.size() << '\n';

return 0;
}

// list::max_size
#include <iostream>
#include <list>

int main ()
{
unsigned int i;
std::list<int> mylist;

std::cout << "Enter number of elements: ";
std::cin >> i;

if (i<mylist.max_size()) mylist.resize(i);
else std::cout << "That size exceeds the limit.\n";

return 0;
}

// list::front
#include <iostream>
#include <list>

int main ()
{
std::list<int> mylist;

mylist.push_back(77);
mylist.push_back(22);

// now front equals 77, and back 22

mylist.front() -= mylist.back();

std::cout << "mylist.front() is now " << mylist.front() << '\n';

return 0;
}

// list::back
#include <iostream>
#include <list>

int main ()
{
std::list<int> mylist;

mylist.push_back(10);

while (mylist.back() != 0)
{
mylist.push_back ( mylist.back() -1 );
}

std::cout << "mylist contains:";
for (std::list<int>::iterator it=mylist.begin(); it!=mylist.end() ; ++it)
std::cout << ' ' << *it;

std::cout << '\n';

return 0;
}

// list::assign
#include <iostream>
#include <list>

int main ()
{
std::list<int> first;
std::list<int> second;

first.assign (7,100);                      // 7 ints with value 100

second.assign (first.begin(),first.end()); // a copy of first

int myints[]={1776,7,4};
first.assign (myints,myints+3);            // assigning from array

std::cout << "Size of first: " << int (first.size()) << '\n';
std::cout << "Size of second: " << int (second.size()) << '\n';
return 0;
}

// list::emplace_front
#include <iostream>
#include <list>

int main ()
{
std::list< std::pair<int,char> > mylist;

mylist.emplace_front(10,'a');
mylist.emplace_front(20,'b');
mylist.emplace_front(30,'c');

std::cout << "mylist contains:";
for (auto& x: mylist)
std::cout << " (" << x.first << "," << x.second << ")";

std::cout << std::endl;
return 0;
}

// list::push_front
#include <iostream>
#include <list>

int main ()
{
std::list<int> mylist (2,100);         // two ints with a value of 100
mylist.push_front (200);
mylist.push_front (300);

std::cout << "mylist contains:";
for (std::list<int>::iterator it=mylist.begin(); it!=mylist.end(); ++it)
std::cout << ' ' << *it;

std::cout << '\n';
return 0;
}

// list::emplace_back
#include <iostream>
#include <list>

int main ()
{
std::list< std::pair<int,char> > mylist;

mylist.emplace_back(10,'a');
mylist.emplace_back(20,'b');
mylist.emplace_back(30,'c');

std::cout << "mylist contains:";
for (auto& x: mylist)
std::cout << " (" << x.first << "," << x.second << ")";

std::cout << std::endl;
return 0;
}

// list::push_back
#include <iostream>
#include <list>

int main ()
{
std::list<int> mylist;
int myint;

std::cout << "Please enter some integers (enter 0 to end):\n";

do {
std::cin >> myint;
mylist.push_back (myint);
} while (myint);

std::cout << "mylist stores " << mylist.size() << " numbers.\n";

return 0;
}

// list::pop_back
#include <iostream>
#include <list>

int main ()
{
std::list<int> mylist;
int sum (0);
mylist.push_back (100);
mylist.push_back (200);
mylist.push_back (300);

while (!mylist.empty())
{
sum+=mylist.back();
mylist.pop_back();
}

std::cout << "The elements of mylist summed " << sum << '\n';

return 0;
}

// list::emplace
#include <iostream>
#include <list>

int main ()
{
std::list< std::pair<int,char> > mylist;

mylist.emplace ( mylist.begin(), 100, 'x' );
mylist.emplace ( mylist.begin(), 200, 'y' );

std::cout << "mylist contains:";
for (auto& x: mylist)
std::cout << " (" << x.first << "," << x.second << ")";

std::cout << '\n';
return 0;
}

// inserting into a list
#include <iostream>
#include <list>
#include <vector>

int main ()
{
std::list<int> mylist;
std::list<int>::iterator it;

// set some initial values:
for (int i=1; i<=5; ++i) mylist.push_back(i); // 1 2 3 4 5

it = mylist.begin();
++it;       // it points now to number 2           ^

mylist.insert (it,10);                        // 1 10 2 3 4 5

// "it" still points to number 2                      ^
mylist.insert (it,2,20);                      // 1 10 20 20 2 3 4 5

--it;       // it points now to the second 20            ^

std::vector<int> myvector (2,30);
mylist.insert (it,myvector.begin(),myvector.end());
// 1 10 20 30 30 20 2 3 4 5
//               ^
std::cout << "mylist contains:";
for (it=mylist.begin(); it!=mylist.end(); ++it)
std::cout << ' ' << *it;
std::cout << '\n';

return 0;
}

// erasing from list
#include <iostream>
#include <list>

int main ()
{
std::list<int> mylist;
std::list<int>::iterator it1,it2;

// set some values:
for (int i=1; i<10; ++i) mylist.push_back(i*10);

// 10 20 30 40 50 60 70 80 90
it1 = it2 = mylist.begin(); // ^^
advance (it2,6);            // ^                 ^
++it1;                      //    ^              ^

it1 = mylist.erase (it1);   // 10 30 40 50 60 70 80 90
//    ^           ^

it2 = mylist.erase (it2);   // 10 30 40 50 60 80 90
//    ^           ^

++it1;                      //       ^        ^
--it2;                      //       ^     ^

mylist.erase (it1,it2);     // 10 30 60 80 90
//        ^

std::cout << "mylist contains:";
for (it1=mylist.begin(); it1!=mylist.end(); ++it1)
std::cout << ' ' << *it1;
std::cout << '\n';

return 0;
}

// swap lists
#include <iostream>
#include <list>

int main ()
{
std::list<int> first (3,100);   // three ints with a value of 100
std::list<int> second (5,200);  // five ints with a value of 200

first.swap(second);

std::cout << "first contains:";
for (std::list<int>::iterator it=first.begin(); it!=first.end(); it++)
std::cout << ' ' << *it;
std::cout << '\n';

std::cout << "second contains:";
for (std::list<int>::iterator it=second.begin(); it!=second.end(); it++)
std::cout << ' ' << *it;
std::cout << '\n';

return 0;
}

// resizing list
#include <iostream>
#include <list>

int main ()
{
std::list<int> mylist;

// set some initial content:
for (int i=1; i<10; ++i) mylist.push_back(i);

mylist.resize(5);
mylist.resize(8,100);
mylist.resize(12);

std::cout << "mylist contains:";
for (std::list<int>::iterator it=mylist.begin(); it!=mylist.end(); ++it)
std::cout << ' ' << *it;

std::cout << '\n';

return 0;
}

// clearing lists
#include <iostream>
#include <list>

int main ()
{
std::list<int> mylist;
std::list<int>::iterator it;

mylist.push_back (100);
mylist.push_back (200);
mylist.push_back (300);

std::cout << "mylist contains:";
for (it=mylist.begin(); it!=mylist.end(); ++it)
std::cout << ' ' << *it;
std::cout << '\n';

mylist.clear();
mylist.push_back (1101);
mylist.push_back (2202);

std::cout << "mylist contains:";
for (it=mylist.begin(); it!=mylist.end(); ++it)
std::cout << ' ' << *it;
std::cout << '\n';

return 0;
}

// splicing lists
#include <iostream>
#include <list>

int main ()
{
std::list<int> mylist1, mylist2;
std::list<int>::iterator it;

// set some initial values:
for (int i=1; i<=4; ++i)
mylist1.push_back(i);      // mylist1: 1 2 3 4

for (int i=1; i<=3; ++i)
mylist2.push_back(i*10);   // mylist2: 10 20 30

it = mylist1.begin();
++it;                         // points to 2

mylist1.splice (it, mylist2); // mylist1: 1 10 20 30 2 3 4
// mylist2 (empty)
// "it" still points to 2 (the 5th element)

mylist2.splice (mylist2.begin(),mylist1, it);
// mylist1: 1 10 20 30 3 4
// mylist2: 2
// "it" is now invalid.
it = mylist1.begin();
std::advance(it,3);           // "it" points now to 30

mylist1.splice ( mylist1.begin(), mylist1, it, mylist1.end());
// mylist1: 30 3 4 1 10 20

std::cout << "mylist1 contains:";
for (it=mylist1.begin(); it!=mylist1.end(); ++it)
std::cout << ' ' << *it;
std::cout << '\n';

std::cout << "mylist2 contains:";
for (it=mylist2.begin(); it!=mylist2.end(); ++it)
std::cout << ' ' << *it;
std::cout << '\n';

return 0;
}

// remove from list
#include <iostream>
#include <list>

int main ()
{
int myints[]= {17,89,7,14};
std::list<int> mylist (myints,myints+4);

mylist.remove(89);

std::cout << "mylist contains:";
for (std::list<int>::iterator it=mylist.begin(); it!=mylist.end(); ++it)
std::cout << ' ' << *it;
std::cout << '\n';

return 0;
}

// list::remove_if
#include <iostream>
#include <list>

// a predicate implemented as a function:
bool single_digit (const int& value) { return (value<10); }

// a predicate implemented as a class:
struct is_odd {
bool operator() (const int& value) { return (value%2)==1; }
};

int main ()
{
int myints[]= {15,36,7,17,20,39,4,1};
std::list<int> mylist (myints,myints+8);   // 15 36 7 17 20 39 4 1

mylist.remove_if (single_digit);           // 15 36 17 20 39

mylist.remove_if (is_odd());               // 36 20

std::cout << "mylist contains:";
for (std::list<int>::iterator it=mylist.begin(); it!=mylist.end(); ++it)
std::cout << ' ' << *it;
std::cout << '\n';

return 0;
}

// list::unique
#include <iostream>
#include <cmath>
#include <list>

// a binary predicate implemented as a function:
bool same_integral_part (double first, double second)
{ return ( int(first)==int(second) ); }

// a binary predicate implemented as a class:
struct is_near {
bool operator() (double first, double second)
{ return (fabs(first-second)<5.0); }
};

int main ()
{
double mydoubles[]={ 12.15,  2.72, 73.0,  12.77,  3.14,
12.77, 73.35, 72.25, 15.3,  72.25 };
std::list<double> mylist (mydoubles,mydoubles+10);

mylist.sort();             //  2.72,  3.14, 12.15, 12.77, 12.77,
// 15.3,  72.25, 72.25, 73.0,  73.35

mylist.unique();           //  2.72,  3.14, 12.15, 12.77
// 15.3,  72.25, 73.0,  73.35

mylist.unique (same_integral_part);  //  2.72,  3.14, 12.15
// 15.3,  72.25, 73.0

mylist.unique (is_near());           //  2.72, 12.15, 72.25

std::cout << "mylist contains:";
for (std::list<double>::iterator it=mylist.begin(); it!=mylist.end(); ++it)
std::cout << ' ' << *it;
std::cout << '\n';

return 0;
}

// list::merge
#include <iostream>
#include <list>

// compare only integral part:
bool mycomparison (double first, double second)
{ return ( int(first)<int(second) ); }

int main ()
{
std::list<double> first, second;

first.push_back (3.1);
first.push_back (2.2);
first.push_back (2.9);

second.push_back (3.7);
second.push_back (7.1);
second.push_back (1.4);

first.sort();
second.sort();

first.merge(second);

// (second is now empty)

second.push_back (2.1);

first.merge(second,mycomparison);

std::cout << "first contains:";
for (std::list<double>::iterator it=first.begin(); it!=first.end(); ++it)
std::cout << ' ' << *it;
std::cout << '\n';

return 0;
}

// list::sort
#include <iostream>
#include <list>
#include <string>
#include <cctype>

// comparison, not case sensitive.
bool compare_nocase (const std::string& first, const std::string& second)
{
unsigned int i=0;
while ( (i<first.length()) && (i<second.length()) )
{
if (tolower(first[i])<tolower(second[i])) return true;
else if (tolower(first[i])>tolower(second[i])) return false;
++i;
}
return ( first.length() < second.length() );
}

int main ()
{
std::list<std::string> mylist;
std::list<std::string>::iterator it;
mylist.push_back ("one");
mylist.push_back ("two");
mylist.push_back ("Three");

mylist.sort();

std::cout << "mylist contains:";
for (it=mylist.begin(); it!=mylist.end(); ++it)
std::cout << ' ' << *it;
std::cout << '\n';

mylist.sort(compare_nocase);

std::cout << "mylist contains:";
for (it=mylist.begin(); it!=mylist.end(); ++it)
std::cout << ' ' << *it;
std::cout << '\n';

return 0;
}

// reversing list
#include <iostream>
#include <list>

int main ()
{
std::list<int> mylist;

for (int i=1; i<10; ++i) mylist.push_back(i);

mylist.reverse();

std::cout << "mylist contains:";
for (std::list<int>::iterator it=mylist.begin(); it!=mylist.end(); ++it)
std::cout << ' ' << *it;

std::cout << '\n';

return 0;
}

*/