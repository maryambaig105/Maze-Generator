//
// Created by Maryam Baig on 30/10/23.
//
#include <iostream>
#ifndef CS300_STACK_H
#define CS300_STACK_H
template <class Temp>
class Stack {
private:
    struct ListNode
    {
        Temp   coordinatex,coordinatey;
        ListNode *next;

        ListNode(  Temp  numberx, Temp  numbery,ListNode * n =NULL )
                :  coordinatex(numberx),coordinatey(numbery),next( n ) { }
    };

    ListNode *topOfStack;  // list itself is the stack

public:
    Stack();

    ~Stack();

    bool isEmpty() ;

    void pop();

    void push( Temp x, Temp y);

    Temp topx() ;
    Temp topy() ;



};
#endif //CS300_STACK_H
template <class Temp>
Stack<Temp>::Stack()
{
    topOfStack = NULL;
}

template <class Temp>
bool Stack<Temp>::isEmpty( )
{
    return topOfStack == NULL;
}
template <class Temp>
Temp Stack<Temp>::topx( )
{
    if ( !isEmpty( ) ){
        return topOfStack->coordinatex;
    }
    else return 0;

}
template <class Temp>
Temp  Stack<Temp>::topy( )
{
    if ( !isEmpty( ) ){
        return topOfStack->coordinatey;
    }
    else return 0;

}
template <class Temp>
void Stack<Temp>::pop( )
{
    if ( !isEmpty( ) ){
        ListNode *oldTop = topOfStack;
        topOfStack = topOfStack->next;
        delete oldTop;
    }

}
template <class Temp>
void Stack<Temp>::push( Temp  x, Temp y )
{

    ListNode* new_node = new ListNode( x,y, topOfStack );
    if(topOfStack==NULL){
        topOfStack=new_node;
    }
    else{
        ListNode*temp=topOfStack;
        topOfStack = new_node;
        new_node ->next = temp;
    }



}

template <class Temp>
Stack<Temp>::~Stack()
{
    while(!isEmpty()){
        pop();
    }
}

