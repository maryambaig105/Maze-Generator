//
// Created by Maryam Baig on 30/10/23.
//
/*

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

}
template <class Temp>
Temp  Stack<Temp>::topy( )
{
    if ( !isEmpty( ) ){
        return topOfStack->coordinatey;
    }

}
template <class Temp>
void Stack<Temp>::pop( )
{
    if ( !isEmpty( ) ){
        ListNode *oldTop = topOfStack;
        topOfStack = topOfStack->next;
        delete oldTop;
    }
    counter--;
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
    counter++;


}

template <class Temp>
Stack<Temp>::~Stack()
{
    while(!isEmpty()){
        pop();
    }
}*/