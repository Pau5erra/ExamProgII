#ifndef __p2String_H__
#define __p2String_H__

//#include <stdlib.h>
//#include <stdarg.h>
#include <string.h>
#include "p2Defs.h"

class p2String
{
public:

	// Constructors
	p2String()
	{
		Alloc(1);
		clear();
	}

	p2String(uint max_capacity)
	{
		Alloc(MAX(1,max_capacity));
		clear();
	}

	p2String(const p2String& string)
	{
		Alloc(string.length() + 1);
		strcpy_s(str, max_capacity, string.str);
	}

	p2String(const char *string)
	{
		if(string != nullptr)
		{
			Alloc(strlen(string) + 1);
			strcpy_s(str, max_capacity, string);
		}
		else
		{
			Alloc(1);
			clear();
		}
	}
	
	// Destructor
	 ~p2String()
	{
		RELEASE_ARRAY(str);
	}

	// Operators
	bool operator== (const p2String& string) const
	{
		return strcmp(string.str, str) == 0;
	}

	bool operator== (const char* string) const
	{
		if(string != nullptr)
			return strcmp(string, str) == 0;
		return false;
	}

	bool operator!= (const p2String& string) const
	{
		return strcmp(string.str, str) != 0;
	}

	bool operator!= (const char* string) const
	{
		if(string != nullptr)
			return strcmp(string, str) != 0;
		return true;
	}
	
	const p2String& operator= (const p2String& string)
	{
		if(string.length() + 1 > this->max_capacity)
		{
			RELEASE_ARRAY(str);
			Alloc(string.length() + 1);
		}

		strcpy_s(str, max_capacity, string.str);

		return(*this);
	}

	const p2String& operator= (const char* string)
	{
		if(string != nullptr)
		{
			if(strlen(string) + 1 > max_capacity)
			{
				RELEASE_ARRAY(str);
				Alloc(strlen(string)+1);
			}

			strcpy_s(str, max_capacity, string);
		}
		else
			clear();

		return(*this);
	}
	
	const p2String& operator+= (const p2String& string)
	{
		unsigned int need_max_capacity = string.length() + length() + 1;

		if(need_max_capacity > max_capacity)
		{
			char* tmp = str;
			Alloc(need_max_capacity);
			strcpy_s(str, max_capacity, tmp);
			RELEASE_ARRAY(tmp);
		}

		strcat_s(str, max_capacity, string.str);

		return(*this);
	}

	const p2String& operator+= (const char* string)
	{
		if(string != nullptr)
		{
			unsigned int need_max_capacity = strlen(string) + length() + 1;

			if(need_max_capacity > max_capacity)
			{
				char* tmp = str;
				Alloc(need_max_capacity);
				strcpy_s(str, max_capacity, tmp);
				RELEASE_ARRAY(tmp);
			}

			strcat_s(str, max_capacity, string);
		}

		return(*this);
	}

	// Utils
	uint length() const
	{
		return strlen(str);
	}

	uint size() const
	{
		return strlen(str);
	}

	bool empty() const
	{
		return strlen(str) == 0;
	}

	void clear()
	{
		str[0] = '\0';
	}

	const char* c_str() const
	{
		return str;
	}

	uint capacity() const
	{
		return max_capacity;
	}

private:

	void Alloc(unsigned int required_memory)
	{
		max_capacity = required_memory;
		str = new char[max_capacity];
	}

private:

	char* str;
	uint max_capacity;

};

#endif // __p2String_H__

/*

// string constructor
#include <iostream>
#include <string>

int main ()
{
std::string s0 ("Initial string");

// constructors used in the same order as described above:
std::string s1;
std::string s2 (s0);
std::string s3 (s0, 8, 3);
std::string s4 ("A character sequence", 6);
std::string s5 ("Another character sequence");
std::string s6a (10, 'x');
std::string s6b (10, 42);      // 42 is the ASCII code for '*'
std::string s7 (s0.begin(), s0.begin()+7);

std::cout << "s1: " << s1 << "\ns2: " << s2 << "\ns3: " << s3;
std::cout << "\ns4: " << s4 << "\ns5: " << s5 << "\ns6a: " << s6a;
std::cout << "\ns6b: " << s6b << "\ns7: " << s7 << '\n';
return 0;
}

// string::begin
#include <iostream>
#include <string>

int main ()
{
std::string str ("Test string");
for ( std::string::iterator it=str.begin(); it!=str.end(); ++it)
std::cout << *it;
std::cout << '\n';

return 0;
}

// string::end
#include <iostream>
#include <string>

int main ()
{
std::string str ("Test string");
for ( std::string::iterator it=str.begin(); it!=str.end(); ++it)
std::cout << *it;
std::cout << '\n';

return 0;
}

// string::size
#include <iostream>
#include <string>

int main ()
{
std::string str ("Test string");
std::cout << "The size of str is " << str.size() << " bytes.\n";
return 0;
}

// string::length
#include <iostream>
#include <string>

int main ()
{
std::string str ("Test string");
std::cout << "The size of str is " << str.length() << " bytes.\n";
return 0;
}

// comparing length
#include <iostream>
#include <string>

int main ()
{
std::string str ("Test string");
std::cout << "size: " << str.size() << "\n";
std::cout << "length: " << str.length() << "\n";
std::cout << "capacity: " << str.capacity() << "\n";
std::cout << "max_size: " << str.max_size() << "\n";
return 0;
}

// comparing max_size
#include <iostream>
#include <string>

int main ()
{
std::string str ("Test string");
std::cout << "size: " << str.size() << "\n";
std::cout << "length: " << str.length() << "\n";
std::cout << "capacity: " << str.capacity() << "\n";
std::cout << "max_size: " << str.max_size() << "\n";
return 0;
}

//capacity
#include <iostream>
#include <string>

int main ()
{
std::string str ("Test string");
std::cout << "size: " << str.size() << "\n";
std::cout << "length: " << str.length() << "\n";
std::cout << "capacity: " << str.capacity() << "\n";
std::cout << "max_size: " << str.max_size() << "\n";
return 0;
}


// string::reserve Request a change in capacity
#include <iostream>
#include <fstream>
#include <string>

int main ()
{
std::string str;

std::ifstream file ("test.txt",std::ios::in|std::ios::ate);
if (file) {
std::ifstream::streampos filesize = file.tellg();
str.reserve(filesize);

file.seekg(0);
while (!file.eof())
{
str += file.get();
}
std::cout << str;
}
return 0;
}


// string::clear
#include <iostream>
#include <string>

int main ()
{
char c;
std::string str;
std::cout << "Please type some lines of text. Enter a dot (.) to finish:\n";
do {
c = std::cin.get();
str += c;
if (c=='\n')
{
std::cout << str;
str.clear();
}
} while (c!='.');
return 0;
}

// string::empty
#include <iostream>
#include <string>

int main ()
{
std::string content;
std::string line;
std::cout << "Please introduce a text. Enter an empty line to finish:\n";
do {
getline(std::cin,line);
content += line + '\n';
} while (!line.empty());
std::cout << "The text you introduced was:\n" << content;
return 0;
}

// string::shrink_to_fit
#include <iostream>
#include <string>

int main ()
{
std::string str (100,'x');
std::cout << "1. capacity of str: " << str.capacity() << '\n';

str.resize(10);
std::cout << "2. capacity of str: " << str.capacity() << '\n';

str.shrink_to_fit();
std::cout << "3. capacity of str: " << str.capacity() << '\n';

return 0;
}

// string::operator[]
#include <iostream>
#include <string>

int main ()
{
std::string str ("Test string");
for (int i=0; i<str.length(); ++i)
{
std::cout << str[i];
}
return 0;
}

// string::at
#include <iostream>
#include <string>

int main ()
{
std::string str ("Test string");
for (unsigned i=0; i<str.length(); ++i)
{
std::cout << str.at(i);
}
return 0;
}

// string::back
#include <iostream>
#include <string>

int main ()
{
std::string str ("hello world.");
str.back() = '!';
std::cout << str << '\n';
return 0;
}

// string::front
#include <iostream>
#include <string>

int main ()
{
std::string str ("test string");
str.front() = 'T';
std::cout << str << '\n';
return 0;
}


// string::operator+=
#include <iostream>
#include <string>

int main ()
{
std::string name ("John");
std::string family ("Smith");
name += " K. ";         // c-string
name += family;         // string
name += '\n';           // character

std::cout << name;
return 0;
}

// appending to string
#include <iostream>
#include <string>

int main ()
{
std::string str;
std::string str2="Writing ";
std::string str3="print 10 and then 5 more";

// used in the same order as described above:
str.append(str2);                       // "Writing "
str.append(str3,6,3);                   // "10 "
str.append("dots are cool",5);          // "dots "
str.append("here: ");                   // "here: "
str.append(10u,'.');                    // ".........."
str.append(str3.begin()+8,str3.end());  // " and then 5 more"
str.append<int>(5,0x2E);                // "....."

std::cout << str << '\n';
return 0;
}

// string::push_back
#include <iostream>
#include <fstream>
#include <string>

int main ()
{
std::string str;
std::ifstream file ("test.txt",std::ios::in);
if (file) {
while (!file.eof()) str.push_back(file.get());
}
std::cout << str << '\n';
return 0;
}

// string::assign
#include <iostream>
#include <string>

int main ()
{
std::string str;
std::string base="The quick brown fox jumps over a lazy dog.";

// used in the same order as described above:

str.assign(base);
std::cout << str << '\n';

str.assign(base,10,9);
std::cout << str << '\n';         // "brown fox"

str.assign("pangrams are cool",7);
std::cout << str << '\n';         // "pangram"

str.assign("c-string");
std::cout << str << '\n';         // "c-string"

str.assign(10,'*');
std::cout << str << '\n';         // "**********"

str.assign<int>(10,0x2D);
std::cout << str << '\n';         // "----------"

str.assign(base.begin()+16,base.end()-12);
std::cout << str << '\n';         // "fox jumps over"

return 0;
}

// inserting into a string
#include <iostream>
#include <string>

int main ()
{
std::string str="to be question";
std::string str2="the ";
std::string str3="or not to be";
std::string::iterator it;

// used in the same order as described above:
str.insert(6,str2);                 // to be (the )question
str.insert(6,str3,3,4);             // to be (not )the question
str.insert(10,"that is cool",8);    // to be not (that is )the question
str.insert(10,"to be ");            // to be not (to be )that is the question
str.insert(15,1,':');               // to be not to be(:) that is the question
it = str.insert(str.begin()+5,','); // to be(,) not to be: that is the question
str.insert (str.end(),3,'.');       // to be, not to be: that is the question(...)
str.insert (it+2,str3.begin(),str3.begin()+3); // (or )

std::cout << str << '\n';
return 0;
}

// string::erase
#include <iostream>
#include <string>

int main ()
{
std::string str ("This is an example sentence.");
std::cout << str << '\n';
// "This is an example sentence."
str.erase (10,8);                        //            ^^^^^^^^
std::cout << str << '\n';
// "This is an sentence."
str.erase (str.begin()+9);               //           ^
std::cout << str << '\n';
// "This is a sentence."
str.erase (str.begin()+5, str.end()-9);  //       ^^^^^
std::cout << str << '\n';
// "This sentence."
return 0;
}

// replacing in a string
#include <iostream>
#include <string>

int main ()
{
std::string base="this is a test string.";
std::string str2="n example";
std::string str3="sample phrase";
std::string str4="useful.";

// replace signatures used in the same order as described above:

// Using positions:                 0123456789*123456789*12345
std::string str=base;           // "this is a test string."
str.replace(9,5,str2);          // "this is an example string." (1)
str.replace(19,6,str3,7,6);     // "this is an example phrase." (2)
str.replace(8,10,"just a");     // "this is just a phrase."     (3)
str.replace(8,6,"a shorty",7);  // "this is a short phrase."    (4)
str.replace(22,1,3,'!');        // "this is a short phrase!!!"  (5)

// Using iterators:                                               0123456789*123456789*
str.replace(str.begin(),str.end()-3,str3);                    // "sample phrase!!!"      (1)
str.replace(str.begin(),str.begin()+6,"replace");             // "replace phrase!!!"     (3)
str.replace(str.begin()+8,str.begin()+14,"is coolness",7);    // "replace is cool!!!"    (4)
str.replace(str.begin()+12,str.end()-4,4,'o');                // "replace is cooool!!!"  (5)
str.replace(str.begin()+11,str.end(),str4.begin(),str4.end());// "replace is useful."    (6)
std::cout << str << '\n';
return 0;
}

// swap strings
#include <iostream>
#include <string>

main ()
{
std::string buyer ("money");
std::string seller ("goods");

std::cout << "Before the swap, buyer has " << buyer;
std::cout << " and seller has " << seller << '\n';

seller.swap (buyer);

std::cout << " After the swap, buyer has " << buyer;
std::cout << " and seller has " << seller << '\n';

return 0;
}

// string::pop_back
#include <iostream>
#include <string>

int main ()
{
std::string str ("hello world!");
str.pop_back();
std::cout << str << '\n';
return 0;
}

// strings and c-strings Get C string equivalent
#include <iostream>
#include <cstring>
#include <string>

int main ()
{
std::string str ("Please split this sentence into tokens");

char * cstr = new char [str.length()+1];
std::strcpy (cstr, str.c_str());

// cstr now contains a c-string copy of str

char * p = std::strtok (cstr," ");
while (p!=0)
{
std::cout << p << '\n';
p = std::strtok(NULL," ");
}

delete[] cstr;
return 0;
}

// string::data
#include <iostream>
#include <string>
#include <cstring>

int main ()
{
int length;

std::string str = "Test string";
char* cstr = "Test string";

if ( str.length() == std::strlen(cstr) )
{
std::cout << "str and cstr have the same length.\n";

if ( memcmp (cstr, str.data(), str.length() ) == 0 )
std::cout << "str and cstr have the same content.\n";
}
return 0;
}


// string::copy
#include <iostream>
#include <string>

int main ()
{
char buffer[20];
std::string str ("Test string...");
std::size_t length = str.copy(buffer,6,5);
buffer[length]='\0';
std::cout << "buffer contains: " << buffer << '\n';
return 0;
}

// string::find Find content in string
#include <iostream>       // std::cout
#include <string>         // std::string

int main ()
{
std::string str ("There are two needles in this haystack with needles.");
std::string str2 ("needle");

// different member versions of find in the same order as above:
std::size_t found = str.find(str2);
if (found!=std::string::npos)
std::cout << "first 'needle' found at: " << found << '\n';

found=str.find("needles are small",found+1,6);
if (found!=std::string::npos)
std::cout << "second 'needle' found at: " << found << '\n';

found=str.find("haystack");
if (found!=std::string::npos)
std::cout << "'haystack' also found at: " << found << '\n';

found=str.find('.');
if (found!=std::string::npos)
std::cout << "Period found at: " << found << '\n';

// let's replace the first needle:
str.replace(str.find(str2),str2.length(),"preposition");
std::cout << str << '\n';

return 0;
}

// string::find_first_of
#include <iostream>       // std::cout
#include <string>         // std::string
#include <cstddef>        // std::size_t

int main ()
{
std::string str ("Please, replace the vowels in this sentence by asterisks.");
std::size_t found = str.find_first_of("aeiou");
while (found!=std::string::npos)
{
str[found]='*';
found=str.find_first_of("aeiou",found+1);
}

std::cout << str << '\n';

return 0;
}

// string::find_last_of
#include <iostream>       // std::cout
#include <string>         // std::string
#inlude <cstddef>         // std::size_t

void SplitFilename (const std::string& str)
{
std::cout << "Splitting: " << str << '\n';
std::size_t found = str.find_last_of("/\\");
std::cout << " path: " << str.substr(0,found) << '\n';
std::cout << " file: " << str.substr(found+1) << '\n';
}

int main ()
{
std::string str1 ("/usr/bin/man");
std::string str2 ("c:\\windows\\winhelp.exe");

SplitFilename (str1);
SplitFilename (str2);

return 0;
}

// string::find_first_not_of
#include <iostream>       // std::cout
#include <string>         // std::string
#include <cstddef>        // std::size_t

int main ()
{
std::string str ("look for non-alphabetic characters...");

std::size_t found = str.find_first_not_of("abcdefghijklmnopqrstuvwxyz ");

if (found!=std::string::npos)
{
std::cout << "The first non-alphabetic character is " << str[found];
std::cout << " at position " << found << '\n';
}

return 0;
}


// string::find_last_not_of
#include <iostream>       // std::cout
#include <string>         // std::string
#include <cstddef>        // std::size_t

int main ()
{
std::string str ("Please, erase trailing white-spaces   \n");
std::string whitespaces (" \t\f\v\n\r");

std::size_t found = str.find_last_not_of(whitespaces);
if (found!=std::string::npos)
str.erase(found+1);
else
str.clear();            // str is all whitespace

std::cout << '[' << str << "]\n";

return 0;
}

*/

/*
// memcpy example 
#include <stdio.h>
#include <string.h>

struct {
	char name[40];
	int age;
} person, person_copy;

int main()
{
	char myname[] = "Pierre de Fermat";

	// using memcpy to copy string: 
	memcpy(person.name, myname, strlen(myname) + 1);
	person.age = 46;

	// using memcpy to copy structure: 
	memcpy(&person_copy, &person, sizeof(person));

	printf("person_copy: %s, %d \n", person_copy.name, person_copy.age);

	return 0;
}

// memmove example 
#include <stdio.h>
#include <string.h>

int main()
{
	char str[] = "memmove can be very useful......";
	memmove(str + 20, str + 15, 11);
	puts(str);
	return 0;
}

// strcpy example 
#include <stdio.h>
#include <string.h>

int main()
{
	char str1[] = "Sample string";
	char str2[40];
	char str3[40];
	strcpy(str2, str1);
	strcpy(str3, "copy successful");
	printf("str1: %s\nstr2: %s\nstr3: %s\n", str1, str2, str3);
	return 0;
}

// strncpy example 
#include <stdio.h>
#include <string.h>

int main()
{
	char str1[] = "To be or not to be";
	char str2[40];
	char str3[40];

	// copy to sized buffer (overflow safe): 
	strncpy(str2, str1, sizeof(str2));

	// partial copy (only 5 chars):
	strncpy(str3, str2, 5);
	str3[5] = '\0';   // null character manually added

	puts(str1);
	puts(str2);
	puts(str3);

	return 0;
}


// strcat example
#include <stdio.h>
#include <string.h>

int main()
{
	char str[80];
	strcpy(str, "these ");
	strcat(str, "strings ");
	strcat(str, "are ");
	strcat(str, "concatenated.");
	puts(str);
	return 0;
}

// strncat example
#include <stdio.h>
#include <string.h>

int main()
{
	char str1[20];
	char str2[20];
	strcpy(str1, "To be ");
	strcpy(str2, "or not to be");
	strncat(str1, str2, 6);
	puts(str1);
	return 0;
}

// memcmp example
#include <stdio.h>
#include <string.h>

int main()
{
	char buffer1[] = "DWgaOtP12df0";
	char buffer2[] = "DWGAOTP12DF0";

	int n;

	n = memcmp(buffer1, buffer2, sizeof(buffer1));

	if (n>0) printf("'%s' is greater than '%s'.\n", buffer1, buffer2);
	else if (n<0) printf("'%s' is less than '%s'.\n", buffer1, buffer2);
	else printf("'%s' is the same as '%s'.\n", buffer1, buffer2);

	return 0;
}

//strcmp
#include <stdio.h>
#include <string.h>

int main ()
{
char key[] = "apple";
char buffer[80];
do {
printf ("Guess my favorite fruit? ");
fflush (stdout);
scanf ("%79s",buffer);
} while (strcmp (key,buffer) != 0);
puts ("Correct answer!");
return 0;
}

// strncmp example 
#include <stdio.h>
#include <string.h>

int main()
{
	char str[][5] = { "R2D2", "C3PO", "R2A6" };
	int n;
	puts("Looking for R2 astromech droids...");
	for (n = 0; n<3; n++)
		if (strncmp(str[n], "R2xx", 2) == 0)
		{
			printf("found %s\n", str[n]);
		}
	return 0;
}

*/