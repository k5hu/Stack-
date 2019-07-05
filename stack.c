#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "stack.h"

// Edit only after this line //
/** 
 * File Header - stack.c
 * --------------------------------
 * Keyi Hu
 * May 14 2019
 * This file includes basic functions that can be performed in a stack.
 * It also includes how the stack is created.
 */
/**
 * pop: pop function for stack
 * s: pointer to a stack that we pop from
 * return: pointer to the element that we pop out
 */
Element* pop(Stack* s){
    //return null if the stack is empty
    if(isEmpty(s))
        return NULL;
    //pointer point to popout element 
    Element* e =s->elements[s->top];
    //popout pointer point to null
    s->elements[s->top] = NULL;
    //decrement top
    s->top--;
    //determine if stack need to shrink
    if(s->shrinkFactor!=0&&(s->top)!=0&&
            (s->top)<(int)((s->shrinkFactor)*getCapacity(s))){
        //halve the capacity of stack
        s->capacity = s->capacity/2;
        //create new pointer points to store original array
        Element** temp = s->elements;
        //create space for new array
        s->elements=malloc(sizeof(Element*)*(s->capacity));
        //deep copy element 
        for(int i = 0;i<s->capacity;i++){
            s->elements[i]= temp[i];
        }
        //free original array
        free(temp);
        
    }
    //return popout item
    return e;
}

/**
 * multipop: pop multiple elements from stack
 * s: pointer to the stack that we pop from
 * k: number of element that we want to pop out
 * return the popped out element as an array
 */
Element** multiPop(Stack* s, int k){
    //return null if the stack is empty
    if(isEmpty(s))
        return NULL;
    //reset k if necessary
    if(k>=s->top+1)
        k=s->top+1;
    
    //create new pointer points to store original array
    Element** e = malloc(sizeof(Element*)*k);
    //pop out item and store them in array
    for(int  i =0; i<k;i++){
        e[i]=pop(s);
    }
    //return popout item
    return e;
}

/**
 * Utility function: add element for push
 * s: pointer to the stack that we want to add the element
 * k: key of the element 
 * v: pointer to the value of element
 */
void addE(Stack* s, int k, char* v) {
    //increment top
    s->top++;
    //create new pointer points to store new element 
    Element* e = malloc(sizeof(Element));
    //store value in space created
    e->key = k;
    e->value = v;
    //assign new element to top of stack
    s->elements[s->top]=e;
    
}

/**
 * Utility function: expandCapacity for push
 * s: pointer to the stack that we want to add the element
 */
void expandCapacity(Stack* s) {
    //return if the stack can not grow
    if(!s->dynamic)
        return;
    //determine if the stack need to grow
    if((s->top) +1>= (int)((s->growthFactor)*(s->capacity))){
        //store original array in new element array pointer
        Element** temp = s->elements;
        //assign elements to a new space with double capacity
        s->elements=malloc(sizeof(Element*)*(s->capacity)*2);
        //deep copy original element to the new space
        for(int i = 0;i<s->capacity;i++){
            s->elements[i]= temp[i];
        }
        //free the temporary pointer and original array
        free(temp);
        //double capacity number
        s->capacity = s->capacity*2;
    }
}

/**
 * push: push new elements in for stack
 * s: pointer to the stack that we want to add the element
 * k: key of the element 
 * v: pointer to the value of element
 * return: boolean if the element is successfully pushed into the stack
 */
bool push(Stack* s, int k, char* v){
    //return false if cannot push new element
    if(s->growthFactor==0 && isFull(s))
        return false;
    //expand capacity depends on situation of each stack
    expandCapacity(s);
    //add element into stack
    addE(s,k,v);
    //return true because successfully add elements
    return true;


}

/**
 * pushUnique:push unique function for stack; push element if it will be unique in
 * the
 * stack
 * s: pointer to the stack that we want to add the element
 * k: key of the element 
 * v: pointer to the value of element
 * return: boolean if the element is successfully pushed into the stack
 */
bool pushUnique(Stack* s, int k, char* v){
    //return false if there is same element exist in the array
    if(search(s,k,v)!=-1)
        return false;
    //push unique element in
    push(s,k,v);
    //return true 
    return true;

}

/**
 * reverse: reverse the elements in stack
 * s: pointer to the stack that we want to reverse.
 */
void reverse(Stack* s){
    //store original top value
    int k = s->top;
    //store original elements data
    Element** e = s->elements;
    //create a new array using multipop() and assign the array to elements
    s->elements = multiPop(s,s->top+1);
    //free original elements data
    free(e);
    //assign top value to original array
    s->top = k;
    
}

/**
 * peek: peek function for stack; get the top of the stack
 * s: pointer to the stack that we want to peek.
 * return: Element in the top of the stack
 */
Element* peek(Stack* s){
    //return NULL if the stack is empty
    if(isEmpty(s))
        return NULL;
    //return the top of the elements array
    return s->elements[s->top];

}

/**
 * search: search for element from top of stack
 * s: pointer to the stack that we want to search the element
 * k: key of the element 
 * v: pointer to the value of element
 * return: index of the element in the stack
 */
int search(Stack* s, int k, char* v){
    //iterate through elements array to find same element 
    for(int i =0;i<=(s->top);i++){
        if(s->elements[i]->key == k&& s->elements[i]->value == v)
            //return the index as from the bottom of the array
            return s->top-i+1;

    }
    //return -1 if not found
    return -1;
}

/**
 * getCapacity: get current capacity of stack
 * s: pointer to the stack that we want to know about
 * return: capacity of the stack
 */
int getCapacity(Stack* s){
    //return capacity of the stack
    return s->capacity;

}

/**
 * isFull: check if stack is full
 * s: pointer to the stack that we want to check
 * return: boolean if the stackis full
 */
bool isFull(Stack* s){
    if(s->top+1>=s->capacity)
        return true;
    return false;

}

/**
 * clear: clear the stack
 * s: pointer to the stack that we want to clear elements
 */
void clear(Stack *s) {
    //pop out items in elements array and free them while elements is not empty
    while(!isEmpty(s)){
        free(pop(s));
    }
}

/**
 * cleanStack: clean the stack
 * s: pointer to the stack that we want to clean
 */
void cleanStack(Stack *s) {
    //iterate array to free element from array
    for(int i = 0; i < s->capacity; i++) {
        free(s->elements[i]);
    }
    //free elements array pointer
    free(s->elements);
    //free the stack
	free(s);
}

/**
 * currentSize: getter method for current size of stack
 * s: pointer to the stack that we want to know about
 * return: size of the stack
 */
int currentSize(Stack* s){
    //return top index+1
    return s->top+1;
}

/**
 * isEmpty: check if stack empty
 * s: pointer to the stack that we want to check
 * return: if the stack is empty
 */
bool isEmpty(Stack* s){
    //return true if the top is -1
    if(s->top ==-1)
        return true;
    return false;
}

/**
 * makeStack: Ctor for Stack with fixed capacity
 * cap: capacity of the stack we want to create
 * return: pointer to the stack that we create
 */
Stack* makeStack(int cap){
    //create space for stack
    Stack* s = malloc(sizeof(Stack));
    //assign values in
    s->capacity = cap; 
    s->dynamic= false;
    s->growthFactor = 0;
    s->shrinkFactor = 0;
    s->top = -1;
    //create space for elements array in stack
    s->elements = malloc(sizeof(Element*)*s->capacity);
    //return stack pointer
    return s;
}

/**
 * makeStackG: Ctor for Stack that can grow
 * cap: capacity of the stack that we want to create
 * growF: growthFactor of the stack
 * return: pointer to the stack that we create
 */
Stack* makeStackG(int cap, float growF){
    //create space for stack
    Stack *s = malloc(sizeof(Stack));
    s->capacity = cap;
    s->growthFactor = growF;
    s->shrinkFactor = 0;
    s->dynamic= true;
    s->top=-1;
    //create space for elements array in stack
    s->elements = malloc(sizeof(Element*)*s->capacity);
    //return stack pointer
    return s;


}

/**
 * makeStackGnS: Ctor for Stack that can grow and shrink
 * cap: capacity of the stack that we want to create
 * growF: growthFactor of the stack
 * shrinkF: shrinkFactor of the stack
 * return: pointer to the stack that we create
 */
Stack* makeStackGnS(int cap, float growF, float shrinkF){
    //create space for stack
    Stack *s=malloc(sizeof(Stack));
    s->capacity = cap;
    s->shrinkFactor = shrinkF;
    s->growthFactor = growF; 
    s->dynamic= true;
    s->top = -1;
    //create space for elements array in stack
    s->elements = malloc(sizeof(Element*)*s->capacity);
    //return stack pointer
    return s;
}
