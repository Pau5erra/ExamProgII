#include "p2Defs.h"
#include "p2DynArray.h"
#include "p2SList.h"
#include "p2List.h"
#include "p2Point.h"
#include "p2Queue.h"
#include "p2Queue2.h"
#include "p2Stack.h"
#include "p2Stack2.h"
#include "p2String.h"
#include "p2Graph.h"
#include "p2Map.h"
#include "mat3x3.h"
#include "p2Rectangle.h"

#include <iostream>
#include <map>
#include <string>

uint done = 0;
uint failed = 0;

#define TEST(msg, test) done++; printf("\t%s\t%s\n", !(##test) ? failed++,"FAIL" : "OK", msg)

int main()
{
	// DynArray -------------------
	{
		printf("Testing DynArray ...\n");
		p2DynArray<int> container;
		TEST("Empty constructor", container.capacity() == DYN_ARRAY_BLOCK_SIZE);
		p2DynArray<int> container1(5);
		TEST("Capacity constructor", container1.capacity() == 5);
		container.push_back(1);
		container.push_back(2);
		container.push_back(3);
		TEST("Push Back", container[2] == 3 && container.size() == 3);
		TEST("Front", *(container.front()) == 1);
		TEST("Back", *(container.back()) == 3);
		TEST("Empty", container.empty() == false);
		int d;
		container.pop_back(d);
		container.pop_back(d);
		container.pop_back(d);
		TEST("Pop Back", d == 1 && container.pop_back(d) == false);
	}

	// List -------------------
	{
		printf("Testing Double Linked List ...\n");
		p2List<int> container;
		p2List<int> container1;
		container.push_back(1);
		container.push_back(2);
		container.push_back(3);
	/*	for (int i = 1; i <= 10; i++){
			container.push_back(5);
		}
		container.Unique();
		container1.Splice(1, 2, container);
		*/
		TEST("Push Back", container.size() == 3);
		TEST("Front", *(container.front()) == 1);
		TEST("Back", *(container.back()) == 3);
		TEST("Empty", container.empty() == false);
		int d;
		container.pop_back(d);
		container.pop_back(d);
		container.pop_back(d);
		TEST("Pop Back", d == 1 && container.pop_back(d) == false);
	}

	// Single List -------------------
	{
		printf("Testing Single Linked List ...\n");
		p2SList<int> container;
		container.push_back(1);
		container.push_back(2);
		container.push_back(3);
		TEST("Push Back", container.size() == 3);
		TEST("Front", *(container.front()) == 1);
		TEST("Back", *(container.back()) == 3);
		TEST("Empty", container.empty() == false);
		int d;
		container.pop_back(d);
		container.pop_back(d);
		container.pop_back(d);
		TEST("Pop Back", d == 1 && container.pop_back(d) == false);
	}

	// Queue List -------------------
	{
		printf("Testing Queue implemented with Single Linked List ...\n");
		p2Queue<int> container;
		container.push(1);
		container.push(2);
		container.push(3);
		TEST("Push", container.size() == 3);
		TEST("Empty", container.empty() == false);
		TEST("Peek", *(container.peek()) == 1);
		int d;
		container.pop(d);
		container.pop(d);
		container.pop(d);
		TEST("Pop", d == 3 && container.pop(d) == false);
	}

	// Queue2 DynArray -------------------
	{
		printf("Testing Queue implemented with Dynamic Array ...\n");
		p2Queue2<int> container;
		container.push(1);
		container.push(2);
		container.push(3);
		TEST("Push", container.size() == 3);
		TEST("Empty", container.empty() == false);
		TEST("Peek", *(container.peek()) == 1);
		int d;
		container.pop(d);
		container.pop(d);
		container.pop(d);
		TEST("Pop", d == 3 && container.pop(d) == false);
	}

	// Stack List -------------------
	{
		printf("Testing Stack implemented with Dynamic Array ...\n");
		p2Stack<int> container;
		container.push(1);
		container.push(2);
		container.push(3);
		TEST("Push", container.size() == 3);
		TEST("Empty", container.empty() == false);
		TEST("Peek", *(container.peek()) == 3);
		int d;
		container.pop(d);
		container.pop(d);
		container.pop(d);
		TEST("Pop", d == 1 && container.pop(d) == false);
	}

	// Stack2 List -------------------
	{
		printf("Testing Stack implemented with SIngle Linked List ...\n");
		p2Stack2<int> container;
		container.push(1);
		container.push(2);
		container.push(3);
		TEST("Push", container.size() == 3);
		TEST("Empty", container.empty() == false);
		TEST("Peek", *(container.peek()) == 3);
		int d;
		container.pop(d);
		container.pop(d);
		container.pop(d);
		TEST("Pop", d == 1 && container.pop(d) == false);
	}

	// String -------------------
	{
		printf("Testing String ...\n");
		p2String str;
		TEST("Empty Constructor", str.capacity() == 1 && str.size() == 0);
		p2String str1(25);
		TEST("Capacity Constructor", str1.capacity() == 25 && str1.size() == 0);
		p2String str2("hello world");
		TEST("C String Constructor", str2.capacity() == 12 && str2.size() == 11);
		TEST("Operator == string", !(str2 == str1));
		TEST("Operator == c string", str2 == "hello world");
		str1 = str2;
		TEST("Operator = string", str1 == "hello world");
		str2 = "bye world";
		TEST("Operator = c string", str2 == "bye world");
		str2 += " test";
		TEST("Operator += c string", str2 == "bye world test");
	}

	// Point -------------------
	{
		printf("Testing Point ...\n");
		iPoint a(2, 2);
		iPoint b = a + a;

		TEST("Operator + Point", b == iPoint(4, 4));
		TEST("Operator -= Point", (b -= a) == iPoint(2, 2));
		//TEST("Distance", iPoint(2, 2).DistanceTo(iPoint(2,5)) == 3);
	}

	// Graph -------------------
	{
		printf("Testing Graph ...\n");
		p2Graph<int> container;
		TEST("Empty", container.empty() == true);
		p2Graph<int>::vertice* vertice_1 = container.push_back(1);
		p2Graph<int>::vertice* vertice_2 = container.push_back(2);
		p2Graph<int>::vertice* vertice_3 = container.push_back(3);
		TEST("Push Back", container.size() == 3);
		vertice_1->links.push_back(vertice_2);
		vertice_2->links.push_back(vertice_3);
		vertice_3->links.push_back(vertice_3); // loop
		vertice_3->links.push_back(vertice_2);
		TEST("Push Back", container.size() == 3);
		TEST("is_reachable_iterative A", container.is_reachable_iterative(vertice_1, vertice_3) == true);
		TEST("is_reachable_iterative B", container.is_reachable_iterative(vertice_3, vertice_1) == false);
		TEST("is_reachable_recursive A", container.is_reachable_recursive(vertice_1, vertice_3) == true);
		TEST("is_reachable_recursive B", container.is_reachable_recursive(vertice_3, vertice_1) == false);
		container.clear();
		TEST("Clear", container.size() == 0);
	}

	//Map---------------------------------
	printf("Testing Map....\n");
	p2Map<int, float> container;
	p2Map<int, float>::NodeMap* node1 = container.push_back(1, 1);
	p2Map<int, float>::NodeMap* node2 = container.push_back(2, 1);
	p2Map<int, float>::NodeMap* node3 = container.push_back(3, 2);
	p2Map<int, float>::NodeMap* node4 = container.push_back(4, 3);
	p2Map<int, float>::NodeMap* node5 = container.push_back(4, 3);

	container[5];

	container.Empty();
	container.Size();
	container.Clear();
	container.Empty();
	container.Size();



	std::map<char, std::string> mymap;

	mymap['a'] = "an element";
	mymap['b'] = "another element";
	mymap['c'] = mymap['b'];

	std::cout << "mymap['a'] is " << mymap['a'] << '\n';
	std::cout << "mymap['b'] is " << mymap['b'] << '\n';
	std::cout << "mymap['c'] is " << mymap['c'] << '\n';
	std::cout << "mymap['d'] is " << mymap['d'] << '\n';

	std::cout << "mymap now contains " << mymap.size() << " elements.\n";

	iMat3x3 mat1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	iMat3x3 mat2 = { 10, 20, 30, 40, 50, 60, 70, 80, 90 };
	//iMat3x3 mat3 = mat1 + mat2;
	//TEST("2. p2Mat3x3::op+ and p2Mat3x3::op[]", false /*mat3[0] == 11 && mat3[8] == 99*/);

	p2List<int> list;
	p2List<int>::node* first = list.push_back(1);
	list.push_back(2);
	p2List<int>::node* last = list.push_back(3);
	list.Swap(first, last);
	TEST("3. p2SList::swap()", *(list.front()) == 3 && *(list.back()) == 1);
	list.Assign(first, 4);

	//p2Rectangle-------------------------
	printf("rectangle test");
	p2Rectangle<int> r(10, 10, 40, 50);
	p2Rectangle<int> r2(r);
	TEST("r.position.x == 10", r.position.x == 10);
	TEST("r2.position.y == 10)", r2.position.y == 10);
	TEST("r2.GetArea() == 2000",r2.GetArea() == 2000);
	TEST("r2.Intersects(r) == true",r2.Intersects(r) == true);

	printf("\nFailures: %d/%d", failed, done);

	getchar();
	return 0;
}