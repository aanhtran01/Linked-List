/*
Purpose: create a linked list
Author: Anh Tran
Date: 10/03/2022
*/


#include <string>
#include <iostream>
#include <cassert>
#include "list.h"

using namespace std;

//constructs node
Node::Node(std::string s)
{
    previous = NULL;
    next = NULL;
    data = s; //assign given data to s
}

//contructs an empty list
List::List()
{
    first = NULL;
    last = NULL;
}

//function to add a node to the back of a linked list
void List::push_back(std::string data)
{
    Node* node = new Node(data); //create a new node and assign the string to it
    if (last != NULL) //if list is not empty
    {
        node->previous = last; //assign a previous pointer from the new node to the last node
        last->next = node; //assign a next pointer from the last node to the new node
        last = node; //assign the new node as the last node
    }
    else // if list is empty
    {
        first = node; //assign the new node to the first position
        last = node; // assign the new node to the last position
    }
}

//function to add a node to the front of a linked list
void List::push_front(std::string data)
{
    Node* node = new Node(data); //create a new node and assign the string to it
    if (first != NULL) //if list is not empty
    {
        node->next = first; //assign a next pointer from the new node to the first node
        first->previous = node; //assign a previous pointer from the first node to the new node
        first = node; //assign the new node as the first node
    }
    else //if list is empty
    {
        first = node; //assign the new node to the first position
        last = node;  // assign the new node to the last position
    }
}


//function to reverse the linked list
void List::reverse()
{
    Node* curr = first; //create a node prev and assign it to first
    
    if(curr != NULL)
    {
        Node* after = curr -> next; //create a after node with a next pointer from the first node to the current node
        
        if (curr ->previous == NULL) //if the node is the very first node in the list
        {
            curr->previous = after; //assign a previous pointer from the after node to the current nullptr
            curr->next = NULL; // there is no value for the next pointer of the previous node to go to so assign it to null
            last = curr; //assign last position to the current node
            
        }
        
        Node* after_after = after -> next; //create an after-after node with a next pointer from the after node to the after-after node
    
        //do-while loop with the ending condition if the linked list is empty to reverse the next and previous pointers
        do
        {
            after->next = curr; //when the node is not the first node in the list assign a next pointer from the current node to the after node
            after->previous = after_after; //assign a previous pointer from the after node to the node after it
            curr = after; //the current node is now assign to the after node
            after = after_after; //the after node is now assigned to the after_after node
          
            if (after_after != NULL) //if the after node is not the last node create a next pointer pointing to a nullptr to mark the end of the list
            {
                after_after = after_after -> next;
            }
        } while (after != NULL);
    
        first = curr; //there are no nodes left in the list the previous position becomes the first position
    }
    else  //logic_error here because we cannot reverse an empty list
    {
        throw std::logic_error("list is empty, cannot reverse");
    }
}


//function to swap linked list

/*
Cases that the function must be able to consider
1 if the node swapped are first and last nodes
2 if the node swapped are in the middle of the list
3 if the node swapped are adjacent
 
 Plan: swap all the next nodes then swap the previous nodes
 
*/
void List::swap(Iterator iter1, Iterator iter2)
{
    //create nodes and assign them to the iter1 and iter2 positions along with nodes for the nodes before and after them
    Node* current_1 = iter1.position;
    Node* before_1 = current_1->previous;
    Node* after_1 = current_1->next;

    Node* current_2 = iter2.position;
    Node* before_2 = current_2->previous;
    Node* after_2 = current_2->next;


    //if the node previous to iter1 position is empty
    if (before_1 == NULL)
    {
        first = current_2;  //first node will be the current node for iter2
    }
    else // if the previous node is not empty
    {
        before_1->next = current_2; //the pointer from the node previous to iter1 points to the current node for iter2
    }


    //if the node previous to iter2 position is empty
    if (before_2 == NULL)
    {
        first = current_1; //first node will be the current node for iter1
    }
    else //if the previous node is not empty
    {
        before_2->next = current_1; //the pointer from the node previous to iter2 points to the current node for iter1
    }

    //swap the next pointers
    Node* temp = current_2->next;
    current_2->next = current_1->next;
    current_1->next = temp;

    
    //if the node next to iter1 position is empty
    if (after_1 == NULL)
    {
        last = current_1; //last node will be the current node for iter2
    }
    else //if the after node is not empty
    {
        after_1->previous = current_2; //the pointer from the node after to iter1 points to the current node for iter2
    }


    //if the node next to iter2 position is not empty
    if (after_2 == NULL)
    {
        last = current_1; //last node will be the current node for iter1
    }
    else //if the after node is not empty
    {
        after_2->previous = current_1; //the pointer from the node after to iter2 points to the current node for iter1
    }

    //swap the previous nodes
    temp = current_2->previous;
    current_2->previous = current_1->previous;
    current_1->previous = temp;


}


//function to erase a node given an iter
Iterator List::erase(Iterator iter)
{
    if(iter.position == NULL) //iter.position cannot be null, error thrown
    {
        throw std::logic_error("node is NULL, please erase a valid node in the list");
    }
    else
    {
        //assign nodes to the iter.position, the previous and after positions
        Node *curr = iter.position, *pre = curr->previous, *after = curr->next;

        if (curr != first) //if the current node is the not first node
        {
            pre->next = after; //if the current node is not the first node, assign a next pointer from the previous node to the node after
        }
        
        if (curr == first)//if the node is the first node
        {
            first = after; //assign the first node to the after node
            curr = nullptr; //current node is now a nullptr
        }
        
        if (curr != last) //if the current node is not the last node
        {
            after->previous = pre; //assign a previous pointer from the after node to the pre node
            last = pre; //assign the last node to the previous node
            curr = nullptr; //current node is now a nullptr
        }
        
        if (curr == last)//if current node is the last node
        {
            last = pre; //assign the last node to the previous node
        }
 

        delete curr; //delete the current node after re-assigning the previous and next pointers


        //assign a iterator to the position after the removed element
        Iterator past_remove;
        past_remove.position = after;
        past_remove.container = this;
        return past_remove;
        
    }
}

//beginning of list
Iterator List::begin()
{
    Iterator begin;
    begin.position = first;
    begin.container = this;
    return begin;
}

//end of list return past end iterator
Iterator List::end()
{
    Iterator past_end;
    past_end.position = NULL;
    past_end.container = this;
    return past_end;
}




Iterator::Iterator()
{
    container = NULL;
    position = NULL;
}

std::string Iterator::get() const
{
    //assertion for get function, position cannot be empty
    if(position == NULL)
    {
      throw std::logic_error("there is no valid node for get function; if logic thrown after erase function, you have deleted the last node, there is no valid node to point to");
    }
    else
    {
        return position->data;
    }
}

void Iterator::next()
{
    //assertion for next function, position cannot be empty
    if(position == NULL)
    {
        throw std::logic_error("there is no valid next node to acess");
    }
    else
    {
    position = position->next;
    }
    
}

void Iterator::previous()
{
   //assertion cannot be first position
    if(position == container -> first)
    {
        throw std::logic_error("there is no previous position to access");
    }
    else
    {
        if (position != NULL) //if the position is not null
        {
            position = position->previous; //assign previoius pointer

        }
        else
        {
            position = container->last; //if the positon is null, it is the last position
        }
    }
    }

bool Iterator::equals(Iterator b) const //compares to iterators and return if they are equal
{
    return position == b.position;
}

