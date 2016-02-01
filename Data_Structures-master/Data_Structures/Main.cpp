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

		// test flip de ro -----------------------------------------------
		p2DynArray<int> container2;
		container2.push_back(1);
		container2.push_back(2);
		container2.push_back(3);
		container2.push_back(4);
		container2.push_back(5);

		container2.Flip();
		TEST("12. Testing Flip DynArray", container2[0] == 5);
		TEST("12. Testing Flip DynArray", container2[1] == 4);
		TEST("12. Testing Flip DynArray", container2[2] == 3);
		TEST("12. Testing Flip DynArray", container2[3] == 2);
		TEST("12. Testing Flip DynArray", container2[4] == 1);
	}

	// List -------------------
	{
		printf("Testing Double Linked List ...\n");
		p2List<int> container;
		p2List<int> container1;
		container.push_back(1);
		container.push_back(2);
		container.push_back(3);
		/*
		for (int i = 1; i <= 10; i++){
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
		
		
		                //TEST DE LOS NUEVOS METODOS \\
		
		                     // parte sergio \\
		//prueba del swap ------------------------------------------------------
		p2SList<int> list;
		p2SList<int>::node* first = list.push_back(1);
		list.push_back(2);
		p2SList<int>::node* last = list.push_back(3);
		list.swap(first, last);
		TEST("swap", *(list.front()) == 3 && *(list.back()) == 1);

		//prueba del unique -----------------------------------------------------
		p2SList<int> list1;
		list1.push_back(1);
		list1.push_back(2);
		list1.push_back(1);
		list1.push_back(2);
		list1.push_back(3);
		list1.push_back(4);
		list1.unique();
		TEST("Unique", list1.size() == 4);
		
		//prueba del splice ---------------------------------------------------
		/*
		list1.splice(1, 2, list);
		TEST("splice", *(list1.at(1)) == 1);
		*/

		//prueba change -------------------------------------------------------
		// ARRAY TO LIST ------------------------------------------------------
		p2DynArray<int>_array(4);
		_array.push_back(1);
		_array.push_back(2);
		_array.push_back(3);
		
		p2SList<int> prueba;
		prueba.push_back(0);
		prueba.change(_array);
		TEST("change", prueba.size() == 4);
		

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

	
	// Str functions (they are inside p2Defs.h) -----------------------------------------------------------------------------------------------------------------
	// MyStrcmp------------------
	char b[80] = "hello";
	char c[90] = "hello";
	char d[10] = "world";

	TEST("2. my_strcmp", my_strcmp(b, c) == true);
	TEST("2. my_strcmp", my_strcmp(b, d) == false);

	// MyStrlen-----------------
	char e[] = "hello world";

	TEST("3. my_strlen", my_strlen(e) == 11);
	
	/*
	// MyStrlen-----------------
	char f[10] = "Test.";
	char g[20] = "This is a test.";

	my_strcpy(g, f);
	
	TEST("4. my_strcpy", my_strcmp(f, g) == true);
	*/
	
	// MyStrchr-----------------
	char h[] = "This is a sample string.";

	TEST("5. my_strchr", my_strchr(h, 's') == 4);

	// MyStrcspn----------------
	char i[] = "Hi it's me 2anivia 7spaghetti and meatballs.";
	char j[] = "123456789";

	uint test = my_strcspn(i, j);
	
	TEST("5. my_strcspn", test == 12);
	
	/*
	// DoubleVocals-------------
	p2String s("Hola Mundo");

	uint testing = s.doubleVocals();

	TEST("7. doubleVocals()", testing == 4);
	TEST("7. doubleVocals()", s == "Hoolaa Muundoo");
	*/
	
	// trim()-------------------
	p2String s2("This is a sample string");

	uint spaces = s2.trim();

	TEST("8. trim()", spaces == 4);
	TEST("8. trim()", s2 == "Thisisasamplestring");

	/*
	// doubleSpace()------------
	p2String s3("Hola Mundo");

	uint spaces2 = s3.doubleSpace();

	TEST("9. doubleSpace()", spaces2 == 1);
	TEST("9. doubleSpace()", s3 == "Hola  Mundo");
	*/

	// deleteCharacter()--------
	p2String s4("Hola Mundo");

	uint character = s4.deleteCharacter('o');

	TEST("10. deleteCharacter()", character == 2);
	TEST("10. deleteCharacter()", s4 == "Hla Mund");

	printf("\nFailures: %d/%d\n", failed, done);
	
	


	// Alexis map tests --------------------------------------------------------------------------------------
	//MAP TEST 1 ------------------------------------------------------------
	printf("Aquí se testea lo de copiar el contenido en otro y una forma de hacer el empty:\n\n");
	std::map<char, int> first1;

	first1['a'] = 10;
	first1['b'] = 20;
	first1['c'] = 40;
	first1['d'] = 50;

	std::map<char, int> second = first1; //Second contains 4 ints now
	first1 = std::map<char, int>(); //First is empty now

	printf("First size: %i\n", first1.size());
	printf("Second size: %i\n\n", second.size());
	//std::map<char, int> second(first.begin(), first.end());
	//std::map<char, int> third(second);

	//MAP TEST 2 ------------------------------------------------------------
	printf("Aquí se testea los métodos at, para ver el contenido de una key; el insert apra introducir algo al map y el size: \n\n");
	std::map<char, int>::iterator it;
	std::map<std::string, int> test_map =
	{
		{ "Alpha", 0 },
		{ "Beta", 0 },
		{ "Gamma", 0 }
	};

	test_map.at("Alpha") = 10;
	test_map.at("Beta") = 20;
	test_map.at("Gamma") = 30;

	printf("Alpha: %i\n", test_map.at("Alpha"));
	printf("test_map size: %i\n\n", test_map.size());

	test_map.insert(std::pair<std::string, int>("Delta", 40));
	printf("We insert another pair.\n");
	printf("test_map size: %i\n\n", test_map.size());

	//MAP TEST 3 ------------------------------------------------------------
	printf("Aquí se testea el erase y el swap: \n\n");
	std::map<char, int> map2;

	map2['a'] = 1;
	map2['b'] = 2;
	map2['c'] = 3;
	map2['d'] = 4;
	map2['e'] = 5;

	map2.erase('c');

	//swap
	std::map<char, int> map3;

	map3['x'] = 10;
	map3['y'] = 20;

	map2.swap(map3); //a,b,c,d,e are now inside map3; x,y are now inside map2
	map3.clear(); //Removes all elements from map3, size = 0
	printf("Size of map3 one cleared: %i\n\n", map3.size());

	//MAP TEST 4 ------------------------------------------------------------
	printf("Aquí se testea el find, que es para mostra el contenido de las keys uniéndolo con el count para mirar si los elementos forman parte del map o no: \n\n");
	std::map<char, int> map4;
	char c1;

	map4['a'] = 1;
	map4['b'] = 2;
	map4['c'] = 3;
	map4['d'] = 4;
	map4['e'] = 5;

	printf("a => %i\n", map4.find('a')->second);
	printf("b => %i\n", map4.find('b')->second);
	printf("c => %i\n", map4.find('c')->second);
	printf("d => %i\n", map4.find('d')->second);
	printf("e => %i\n", map4.find('e')->second);

	for (c1 = 'a'; c1 < 'h'; ++c1) //Recorre el abecedario hasta la H, los elementos que estén en esta franja dentro del map, sadrá como que pertenecen al map, los que no, dirá que no peretenecen
		if (map4.count(c1) > 0)
			printf("%c is an element of map4.\n", c1);
		else
			printf("%c is not an element of map4.\n", c1);


	return 0;
}