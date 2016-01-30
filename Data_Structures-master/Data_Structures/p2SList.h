#ifndef __p2SList_H__
#define __p2SList_H__

#include "p2Defs.h"

/**
* Manages a single linked list
*/
template<class TYPE>
class p2SList
{

public:

	/**
	* node implementation
	*/
	struct node
	{
		friend class p2SList<TYPE>;
	public:
		mutable TYPE	data;

		inline const node* next() const
		{
			return nxt;
		}

	private:
		node*   nxt = nullptr;

		node(const TYPE& data) : data(data)
		{}

		/* mmm .... something to think about :)
		~node()
		{
		if(nxt)
		nxt->prv = nullptr;
		}
		*/
	};

private:

	node*   start = nullptr;

public:

	// Constructors ------------------------------------------------------

	// Destructor ---------------------------------------------------------
	~p2SList()
	{
		//clear();
	}

	// Operators ----------------------------------------------------------
	const p2SList<TYPE>& operator +=(const p2SList<TYPE>& list)
	{
		node* item = list.start;
		node* last = back_node();

		while(item != nullptr)
		{
			node* new_item = new node(item->data);

			if(last != nullptr)
				last->nxt = new_item;
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
			last->nxt = item;
		else
			start = item;

		return item;
	}

	node* push_front(const TYPE& item)
	{
		node* item = new node(item);

		if(start != nullptr)
			item->nxt = start;

		start = item;

		return item;
	}

	bool pop_back(TYPE& data)
	{
		node* last = back_node();

		if(last != nullptr)
		{
			data = last->data;
			node* prev = prev_node(last);

			if(prev != nullptr)
				prev->nxt = nullptr;
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
				start = second_node;

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

	bool erase(uint index)
	{
		node* item = at(index);

		if(item != nullptr)
		{
			node* prev = prev_node(item);

			if(prev != nullptr)
				prev->nxt = item->nxt;

			RELEASE(item);
			return true;
		}
		return false;
	}

	bool erase(node* item)
	{
		if(item != nullptr)
		{
			node* prev = prev_node(item);

			if(prev != nullptr)
				prev->nxt = item->nxt;

			RELEASE(item);
			return true;
		}
		return false;
	}

	bool insert(const TYPE& data, uint position)
	{
		node* item = at_node(position);

		if(item != nullptr)
		{
			node* prev = prev_node(item);

			node* new_item = new node(data);
			new_item->nxt = item;

			if(prev != nullptr)
				prev->nxt = new_item;

			return true;
		}

		return false;
	}

	bool insert(const p2SList<TYPE>& list, uint position)
	{
		node* item = at_node(position);
		node* other_list = list.start;

		if(item != nullptr && other_list != nullptr)
		{
			node* prev = prev_node(item);

			// copy the whole list
			node* start_new_list = nullptr;
			node* end_new_list = nullptr;

			while(other_list != nullptr)
			{
				node* new_item = new node(other_list->data);

				if(start_new_list != nullptr)
					end_new_list->nxt = new_item;
				else
					start_new_list = new_item;

				end_new_list = new_item;
				other_list = other_list->nxt;
			}

			// now exchange pointers
			end_new_list->nxt = item;

			if(prev != nullptr)
				prev->nxt = start_new_list;

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

	node* prev_node(node* n)
	{
		node* item =(n == start) ? nullptr : start;
		
		while(item != nullptr && item->nxt != n)
			item = item->nxt;

		return item;
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

	const TYPE* front() const
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

	//splice ----------------------------------------------------------

	//cambia un nodo de una lista a otra
	void splice(int position_insert_node, int position_to_remove, p2SList<TYPE> _list)
	{
		const  node* tmp = NULL;
			
		 
		tmp = this->remove(position_to_remove);
		this->insert(position_insert_node, tmp->data);
	}

	//Swap -------------------------------------------------------------

	void swap(node* node1, node* node2)
	{
		if (node1->nxt != NULL)
		{
			node* tmp_nxt = node1->nxt;
			node* tmp1_nxt = node2->nxt;
			
			node* tmp_prev = prev_node(node1);
			node* tmp1_prev = prev_node(node2);

			node1->nxt = tmp1_nxt;
			node2->nxt = tmp_nxt;

			if (tmp_prev != nullptr)
				tmp_prev->nxt = node2;
			else
				start = node2;

			if (tmp1_prev != nullptr)
				tmp1_prev->nxt = node1;
			else
				start = node1;
         }
      }
	
	//remove ------------------------------------------------------------
	
	//remueve el elemento de la posicion indcada
	node* remove(uint position)
	{
		node* tmp = start;

		if (start == NULL)
		{
			return 0;
		}
		else
		{
			node* tmp1 = tmp;
			node* tmp2;
			
			for (int count = 1; count < position; count++)
			{
				tmp1 = tmp;
				tmp = tmp->nxt;
			}
			if (start->nxt == NULL)
			{
				start = NULL;
			}
			else
			{
				tmp2 = tmp;
				tmp = tmp1;
				tmp->nxt = tmp2->nxt;
				delete tmp2;
				return tmp;
			}	
		}
	}
	




	//unique -------------------------------------------------------------

	//remueve los elementos iguales
	void unique()
	{
		p2SList<TYPE>* new_list(this);
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
					this->remove(position);
				}
				if (j <= 0){
					tmp = tmp->nxt;
					position++;
				}
			}
			tmp1 = tmp1->nxt;
			
			
		}

	}

	//change ------------------------------------------------------------

	//mete los elementos del array dentro de la lista que le indicamos
	p2SList change(p2SList<TYPE> new_list,p2DynArray<TYPE>& _dynarray)
	{
	
	if (start == NULL)
		{
			
			for (int i = 0; i < _dynarray.size(); i++)
			{
				new_list.push_back(_dynarray[i]);
			}
        }
	   else
	    { 
            for (int i = 0; i < _dynarray.size(); i++)
			{
				new_list.push_back(_dynarray[i]);
			}
	   }
	  return(*this);
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
					// Not ideal: should be adjusting pointers instead of Swapping data
					SWAP(tmp->data, tmp->nxt->data);
					swapped = true;
				}

				tmp = tmp->nxt;
			}
		}

		return ret;
	}



};
#endif /*__p2SList_H__*/