#ifndef __P2DEFS_H__
#define __P2DEFS_H__

#include <stdio.h>

// Deletes a buffer
#define RELEASE( x ) \
    {                        \
    if( x != nullptr )        \
	    {                      \
      delete x;            \
	  x = nullptr;              \
	    }                      \
    }

// Deletes an array of buffers
#define RELEASE_ARRAY( x ) \
    {                              \
    if( x != nullptr )              \
	    {                            \
      delete[] x;                \
	  x = nullptr;                    \
	    }                            \
                              \
    }

#define IN_RANGE( value, min, max ) ( ((value) >= (min) && (value) <= (max)) ? 1 : 0 )
#define MIN( a, b ) ( ((a) < (b)) ? (a) : (b) )
#define MAX( a, b ) ( ((a) > (b)) ? (a) : (b) )

#define BLOCK 16
#define DYN_ARRAY_BLOCK_SIZE 16

typedef unsigned int uint;
typedef unsigned char uchar;

template <class VALUE_TYPE> void SWAP(VALUE_TYPE& a, VALUE_TYPE& b)
{
	VALUE_TYPE tmp = a;
	a = b;
	b = tmp;
}
// Str functions -----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------
const bool my_strcmp(char* a, char* b) //Compara el contenido de dos cadenas
{
	if (a[0] != b[0]) //Para empezar si el primer elemento de cada una es diferente, ya se devuelve false
		return(false);
	else
	{
		for (uint i = 0; a[i] != '\0'; ++i) //Si son iguales, se itera la cadena
		{
			if (a[i] != b[i]) //Y si se encuentra algo que difiera se devuelve false
				return(false);
		}

		return(true); //Si no encuentra ningún error, se devuelve true
	}

	//return(*a == *b); //Esta es la manera creo yo más óptima de hacerlo, lo de arriba es más visual
}
//-----------------------------------------------------------------
int my_strlen(const char* a) //Mira el número de elementos de una cadena
{
	uint characters = 0;
	uint i = 0;

	for (i; a[i] != '\0'; ++i) //Itera la cadena
	{
		characters++; //Va sumando un elemento a characters
	}

	return(characters);
}
//-----------------------------------------------------------------
void my_strcpy(char* src, char* dst) //Copia el contenido de una cadena en otra
{
	if (my_strlen(dst) >= my_strlen(src)) //Aquí entra si tiene espacio suficiente
	{
		uint i = 0;
		for (i; dst[i] != '\0' && src[i] != '\0'; ++i) //Itera la lista
		{
			dst[i] = src[i]; // Cambia cada caracter de origen por el de destino
		}
		dst[i] = '\0'; //Pone en la última posición '/0'
	}
	else //Si no hay suficiente espacio
	{
		while (*dst++ = *src++); //Si en my_strcpy, se borra todo lo de dentro, y se deja esta función, funciona. Pero tengo mi orgullo, lo de arriba me lo he currado, aunque al ver esta línea sirva para basura.
	}
}
//-----------------------------------------------------------------
uint my_strchr(char* phrase, uint want_to_find) // Se da una cadena y una letra o símbolo mediante 'd' y te dice el número de estos en la cadena
{
	uint i = 0;
	uint counter = 0;
	for (i; phrase[i] != '\0'; ++i) //Itera la cadena
	{
		if (phrase[i] == want_to_find) //Si en la posición en la que se encuentra la iteración se encuentra el elemento dado, se suma +1 al counter
			++counter;
		//printf("The character %c in the string %s is found at %i\n", want_to_find, phrase, i + 1); //Esto es un ejemplo para ver en qué posición se encuentra.
	}

	return(counter);
}
//-----------------------------------------------------------------
uint my_strcspn(const char* phrase, const char* want_to_find) //Dadas dos cadenas, da la posición en la que se encuentra el primer elemento que está dentro de la segunda cadena en al primera cadena
{
	uint i = 0;
	uint position = 0;
	for (i; phrase[i] != '\0'; ++i) //Se itera la primera cadena
	{
		for (uint j = 0; want_to_find[j] != '\0'; ++j) //Se itera la segunda cadena
		{
			if (phrase[i] == want_to_find[j]) //Si coinciden, se da la posición
			{
				position = i + 1;
				return(position);
			}
		}
	}
}



#endif