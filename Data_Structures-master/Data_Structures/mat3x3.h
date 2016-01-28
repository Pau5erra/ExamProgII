#ifndef _MAT3x3_
#define _MAT3x3_

#include "p2DynArray.h"

template <class TYPE>
class mat3x3{
private:
	p2DynArray<TYPE> elements;

public:

	mat3x3(){}
	mat3x3(int a, int b, int c, int d, int e, int f, int g, int h, int i){
		elements.push_back(a);
		elements.push_back(b);
		elements.push_back(c);
		elements.push_back(d);
		elements.push_back(e);
		elements.push_back(f);
		elements.push_back(g);
		elements.push_back(h);
		elements.push_back(i);
	}

	mat3x3(const mat3x3& new_mat){
		for (int i = 0; i < new_mat.elements.size(); i++){
			elements[i] = new_mat.elements[i];
		}

	}

	~mat3x3(){}

	const mat3x3& operator + (const mat3x3 &new_mat) const
	{
	
		mat3x3<TYPE> ret_mat = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		int count = 0;
		for (int i = 0; i < elements.size(); i++){
			int j = this->elements[i] + new_mat.elements[i];
			elements[i];
			ret_mat.elements[i] = j;
			count++ ;
			if (count == 9){
				return (ret_mat);
			}
		}

		return (ret_mat);
	}

	const TYPE& operator[](uint index){

		return elements[index];

	}

};

typedef mat3x3<int> iMat3x3;
typedef mat3x3<float>  fMat3x3;

#endif