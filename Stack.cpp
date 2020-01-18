/*************************Preprocessor Directives********************/
#include <exception>
#include "Misc.h"
#include "Stack.h"

namespace DataStructures
{
	/*************************Constructors And Destructors********************/
	template<typename T>
	Stack<T>::Stack() : ALLOCATION_STEP(20)
	{
		//Initializing the length to zero
		this->len = 0;
		this->allocatedMemory = 0;

		HandleMemoryAllocation();
	}

	template<typename T>
	Stack<T>::~Stack()
	{
		//Checking if the stack contains data
		if (this->len != 0)
		{
			delete[] this->data;
		}
	}

	/*************************Methods********************/
	template<typename T>
	bool Stack<T>::Empty() const
	{
		return len == 0;
	}

	template<typename T>
	int Stack<T>::Size() const
	{
		return this->len;
	}

	template<typename T>
	T& Stack<T>::Top()
	{
		//Checking if the stack is empty
		if (!this->Empty())
		{
			return this->data[this->Size() - 1];
		}
		else
			throw std::exception("Cannot access top element as stack is empty");
	}

	template<typename T>
	const T& Stack<T>::Top() const
	{
		//Checking if the stack is empty
		if (!this->Empty())
		{
			return this->data[this->Size() - 1];
		}
		else
			throw std::exception("Cannot access top element as stack is empty");
	}

	template<typename T>
	void Stack<T>::Push(const T& val)
	{
		//Managing memory
		this->HandleMemoryAllocation();

		//Adding the new element to the stack
		this->data[this->len] = val;

		//Updating the length counter
		this->len++;
	}

	template<typename T>
	void Stack<T>::Pop()
	{
		//Checking if the stack is empty
		if (this->len != 0)
		{
			this->HandleMemoryDeallocation();
		}
		else
			throw std::exception("Cannot pop element as stack is empty");
	}

	/*************************Functions********************/
	template<typename T>
	void Stack<T>::HandleMemoryAllocation()
	{
		//Checking if space is left in the stack
		if (this->len == this->allocatedMemory)
		{
			T* temp = new T[this->len]; //A temporary buffer for holding the data during resizing
			Misc::CopyArray<T>(this->data, temp, this->len); /*Copying the data to the 
															 buffer*/
			
			//Allocating more memory
			if(this->len != 0)
				delete[] this->data; //Deleting previous data
			this->data = new T[this->allocatedMemory + this->ALLOCATION_STEP];/*Allocating the required
			amount of memory*/

			//Updating the allocated memory counter
			this->allocatedMemory += this->ALLOCATION_STEP;

			//Restoring the data
			Misc::CopyArray<T>(temp, this->data, this->len);

			//Deallocating the buffer
			delete[] temp;
		}
		
	}

	template<typename T>
	void Stack<T>::HandleMemoryDeallocation(int itemsToDelete)
	{
		if (this->len != 0)
		{
			
			T* temp = new T[this->len - itemsToDelete]; //A temporary buffer for holding the data during resizing
			Misc::CopyArray<T>(this->data, temp, this->len - itemsToDelete); /*Copying
			the data to the buffer*/

			//Deallcoating memory that is not required
			delete[] this->data;
			this->data = new T[this->allocatedMemory - itemsToDelete]; /*Allocating 
			the required amount of memory*/

			//Restoring the data
			Misc::CopyArray<T>(temp, this->data, this->len - itemsToDelete);

			//Updating the counters
			this->len -= itemsToDelete;
			this->allocatedMemory -= itemsToDelete;

		}
		else
			throw std::exception("Stack is empty");

	}

}