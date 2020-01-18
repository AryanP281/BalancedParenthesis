#pragma once
/*************************Preprocessor Directives********************/
#include <iostream>

/*************************Namespace********************/
namespace DataStructures
{
	/*************************Class********************/
	template<typename T> class Stack
	{
	private:
		//Variables
		T* data; //The data contained in the stack
		int len; //The current length of the stack
		const int ALLOCATION_STEP; //The size step in which memory allocated for the data
		int allocatedMemory; //The memory that has been allocated to the current point

		//Functions
		void HandleMemoryAllocation(); //Handles memory allocation for the data
		void HandleMemoryDeallocation(int itemsToDelete = 1); /*Deallocates memory*/


	public:
		//Constructors And Destructors
		Stack();
		~Stack();

		//Methods
		bool Empty() const; //Tells whether the stack is empty
		int Size() const; //Returns the Size of the stack
		T& Top(); //Returns a reference to the top element in the stack
		const T& Top() const; /*Returns a constant reference to the top element 
							  in the stack*/
		void Push(const T& val); //Adds a element to the top of the stack
		void Pop(); //Removes the top-element from the stack
	};
}