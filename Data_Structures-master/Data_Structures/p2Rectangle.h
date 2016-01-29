#ifndef _P2RECTANGLE_
#define _P2RECTANGLE_

#include "p2Defs.h"

template <class TYPE>

class p2Rectangle{
private:
	
public:
	TYPE w, h;
	p2Point<TYPE> position;
	
	p2Rectangle(){}

	p2Rectangle(const TYPE& x, const TYPE& y, const TYPE& w, const TYPE& h) : w(w), h(h)
	{
		position.x = x;
		position.y = y;
	}

	p2Rectangle(const p2Rectangle<TYPE>& new_rectangle){
		this->position.x = new_rectangle.position.x;
		this->position.y = new_rectangle.position.y;
		this->w = new_rectangle.w;
		this->h = new_rectangle.h;
	}

	~p2Rectangle(){}

	uint GetArea(){
		return (w*h);
	}

	bool Intersects(const p2Rectangle<TYPE>& rect){
		uint distancex;
		uint distancey;
		bool ret=false;
		distancex = this->position.x - rect.position.x;
		distancey = this->position.y - rect.position.y;

		if (distancex < (((this->w) / 2) + ((rect.w) / 2))){
			if (distancey < (((this->h) / 2) + ((rect.h) / 2))){
				ret = true;
			}
		}

		return ret;
	}

};


#endif