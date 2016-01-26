#ifndef _P2MAP_H_
#define _P2MAP_H_

#include "p2Defs.h"
#include "p2List.h"
template <typename...> class p2Map;

template <class TYPE, class TYPE2>
class p2Map<TYPE, TYPE2>{
public:
	struct NodeMap
	{
		TYPE key;
		TYPE2 value;

		NodeMap(const TYPE& data, const TYPE& key) : value(data), key(key)
		{}
	};

private:
	p2List<NodeMap*> map;
	

public:
	NodeMap* push_back(const TYPE& data, const TYPE& key)
	{
		p2List<NodeMap*>::node* tmp = map.front_node();
		TYPE data_compare;
		while (tmp != NULL){
			data_compare = key;
				if (key == tmp->data->key){
					return nullptr;
				}
				tmp = tmp->next();
		}
		NodeMap* new_vertice = new NodeMap(data, key);
		map.push_back(new_vertice);
		return new_vertice;
	}

	// Operators ----------------------------------------------------------
	TYPE2* operator[](TYPE k)
	{
		p2List<NodeMap*>::node* tmp = map.front_node();
		while (tmp != NULL){
		
			if (k == tmp->data->key){
				return (&tmp->data->value);
			}
			tmp = tmp->next();
		}
		
		return NULL;
	}

	bool Empty() const{
		return map.empty();
	}

	uint Size() const{
		return map.size();
	}

	void Clear(){
		const p2List<NodeMap*>::node* p = map.front_node();
		while (p != nullptr)
		{
			RELEASE(p->data);
			p = p->next();
		}
		map.clear();
	}

};

#endif

/*
// constructing maps
#include <iostream>
#include <map>

bool fncomp (char lhs, char rhs) {return lhs<rhs;}

struct classcomp {
bool operator() (const char& lhs, const char& rhs) const
{return lhs<rhs;}
};

int main ()
{
std::map<char,int> first;

first['a']=10;
first['b']=30;
first['c']=50;
first['d']=70;

std::map<char,int> second (first.begin(),first.end());

std::map<char,int> third (second);

std::map<char,int,classcomp> fourth;                 // class as Compare

bool(*fn_pt)(char,char) = fncomp;
std::map<char,int,bool(*)(char,char)> fifth (fn_pt); // function pointer as Compare

return 0;
}

// assignment operator with maps
#include <iostream>
#include <map>

int main ()
{
std::map<char,int> first;
std::map<char,int> second;

first['x']=8;
first['y']=16;
first['z']=32;

second=first;                // second now contains 3 ints
first=std::map<char,int>();  // and first is now empty

std::cout << "Size of first: " << first.size() << '\n';
std::cout << "Size of second: " << second.size() << '\n';
return 0;
}

// map::begin
#include <iostream>
#include <map>

int main ()
{
std::map<char,int> mymap;

mymap['b'] = 100;
mymap['a'] = 200;
mymap['c'] = 300;

// show content:
for (std::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
std::cout << it->first << " => " << it->second << '\n';

return 0;
}

// map::end
#include <iostream>
#include <map>

int main ()
{
std::map<char,int> mymap;

mymap['b'] = 100;
mymap['a'] = 200;
mymap['c'] = 300;

// show content:
for (std::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
std::cout << it->first << " => " << it->second << '\n';

return 0;
}

// map::empty
#include <iostream>
#include <map>

int main ()
{
std::map<char,int> mymap;

mymap['a']=10;
mymap['b']=20;
mymap['c']=30;

while (!mymap.empty())
{
std::cout << mymap.begin()->first << " => " << mymap.begin()->second << '\n';
mymap.erase(mymap.begin());
}

return 0;
}

// map::size
#include <iostream>
#include <map>

int main ()
{
std::map<char,int> mymap;
mymap['a']=101;
mymap['b']=202;
mymap['c']=302;

std::cout << "mymap.size() is " << mymap.size() << '\n';

return 0;
}

// accessing mapped values
#include <iostream>
#include <map>
#include <string>

int main ()
{
std::map<char,std::string> mymap;

mymap['a']="an element";
mymap['b']="another element";
mymap['c']=mymap['b'];

std::cout << "mymap['a'] is " << mymap['a'] << '\n';
std::cout << "mymap['b'] is " << mymap['b'] << '\n';
std::cout << "mymap['c'] is " << mymap['c'] << '\n';
std::cout << "mymap['d'] is " << mymap['d'] << '\n';

std::cout << "mymap now contains " << mymap.size() << " elements.\n";

return 0;
}

// map::at
#include <iostream>
#include <string>
#include <map>

int main ()
{
std::map<std::string,int> mymap = {
{ "alpha", 0 },
{ "beta", 0 },
{ "gamma", 0 } };

mymap.at("alpha") = 10;
mymap.at("beta") = 20;
mymap.at("gamma") = 30;

for (auto& x: mymap) {
std::cout << x.first << ": " << x.second << '\n';
}

return 0;
}

// map::insert (C++98)
#include <iostream>
#include <map>

int main ()
{
std::map<char,int> mymap;

// first insert function version (single parameter):
mymap.insert ( std::pair<char,int>('a',100) );
mymap.insert ( std::pair<char,int>('z',200) );

std::pair<std::map<char,int>::iterator,bool> ret;
ret = mymap.insert ( std::pair<char,int>('z',500) );
if (ret.second==false) {
std::cout << "element 'z' already existed";
std::cout << " with a value of " << ret.first->second << '\n';
}

// second insert function version (with hint position):
std::map<char,int>::iterator it = mymap.begin();
mymap.insert (it, std::pair<char,int>('b',300));  // max efficiency inserting
mymap.insert (it, std::pair<char,int>('c',400));  // no max efficiency inserting

// third insert function version (range insertion):
std::map<char,int> anothermap;
anothermap.insert(mymap.begin(),mymap.find('c'));

// showing contents:
std::cout << "mymap contains:\n";
for (it=mymap.begin(); it!=mymap.end(); ++it)
std::cout << it->first << " => " << it->second << '\n';

std::cout << "anothermap contains:\n";
for (it=anothermap.begin(); it!=anothermap.end(); ++it)
std::cout << it->first << " => " << it->second << '\n';

return 0;
}

// erasing from map
#include <iostream>
#include <map>

int main ()
{
std::map<char,int> mymap;
std::map<char,int>::iterator it;

// insert some values:
mymap['a']=10;
mymap['b']=20;
mymap['c']=30;
mymap['d']=40;
mymap['e']=50;
mymap['f']=60;

it=mymap.find('b');
mymap.erase (it);                   // erasing by iterator

mymap.erase ('c');                  // erasing by key

it=mymap.find ('e');
mymap.erase ( it, mymap.end() );    // erasing by range

// show content:
for (it=mymap.begin(); it!=mymap.end(); ++it)
std::cout << it->first << " => " << it->second << '\n';

return 0;
}

// swap maps
#include <iostream>
#include <map>

int main ()
{
std::map<char,int> foo,bar;

foo['x']=100;
foo['y']=200;

bar['a']=11;
bar['b']=22;
bar['c']=33;

foo.swap(bar);

std::cout << "foo contains:\n";
for (std::map<char,int>::iterator it=foo.begin(); it!=foo.end(); ++it)
std::cout << it->first << " => " << it->second << '\n';

std::cout << "bar contains:\n";
for (std::map<char,int>::iterator it=bar.begin(); it!=bar.end(); ++it)
std::cout << it->first << " => " << it->second << '\n';

return 0;
}

// map::clear
#include <iostream>
#include <map>

int main ()
{
std::map<char,int> mymap;

mymap['x']=100;
mymap['y']=200;
mymap['z']=300;

std::cout << "mymap contains:\n";
for (std::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
std::cout << it->first << " => " << it->second << '\n';

mymap.clear();
mymap['a']=1101;
mymap['b']=2202;

std::cout << "mymap contains:\n";
for (std::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
std::cout << it->first << " => " << it->second << '\n';

return 0;
}

// map::emplace-------Construct and insert element
#include <iostream>
#include <map>

int main ()
{
std::map<char,int> mymap;

mymap.emplace('x',100);
mymap.emplace('y',200);
mymap.emplace('z',100);

std::cout << "mymap contains:";
for (auto& x: mymap)
std::cout << " [" << x.first << ':' << x.second << ']';
std::cout << '\n';

return 0;
}

// map::find
#include <iostream>
#include <map>

int main ()
{
std::map<char,int> mymap;
std::map<char,int>::iterator it;

mymap['a']=50;
mymap['b']=100;
mymap['c']=150;
mymap['d']=200;

it = mymap.find('b');
if (it != mymap.end())
mymap.erase (it);

// print content:
std::cout << "elements in mymap:" << '\n';
std::cout << "a => " << mymap.find('a')->second << '\n';
std::cout << "c => " << mymap.find('c')->second << '\n';
std::cout << "d => " << mymap.find('d')->second << '\n';

return 0;
}

// map::count
#include <iostream>
#include <map>

int main ()
{
std::map<char,int> mymap;
char c;

mymap ['a']=101;
mymap ['c']=202;
mymap ['f']=303;

for (c='a'; c<'h'; c++)
{
std::cout << c;
if (mymap.count(c)>0)
std::cout << " is an element of mymap.\n";
else
std::cout << " is not an element of mymap.\n";
}

return 0;
}


*/