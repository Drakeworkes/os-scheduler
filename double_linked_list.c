#include "double_linked_list.h"
#include <stdlib.h>

DoublyLinkedList *create_list() {
    DoublyLinkedList *list = malloc(sizeof(DoublyLinkedList));
    list->head = NULL;
    list->tail = NULL;
    return list;
}

void append(DoublyLinkedList *list, Process *new_proc) {
    //create the new node
    Node *new_node = malloc(sizeof(Node));
    new_node->proc = new_proc;
    new_node->prev = list->tail;
    new_node->next = NULL;

    // list has a tail
    if (list->tail != NULL) {
        list->tail->next = new_node;
    }

    // set tail to new end
    list->tail = new_node;

    // if list has no head, 
    if (list->head == NULL) {
        list->head = new_node;
    }
}

//popFirst
//This function will return the head process of the doubly linked list
Process *popFirst(DoublyLinkedList *list){
    Node *oldHead = list->head;                 //Store the current head  
    
    if (oldHead == NULL){                       //Make sure list isn't empty
        return NULL;
    }

    if(list->head->next != NULL){               //Is there a next node
        list->head = list->head->next;          //Make the head's next the new head
        list->head->prev = NULL;                //Clear the old head from the current head's link
    }

    return oldHead->proc;                       //Return the process

}

//popHighP
//This function will return the highest priority process
Process *popHighP(DoublyLinkedList *list){
    int priorityCounter = 0;                    //Variable to keep track of the highest priority
    Node *curNode = list->head;                 //Store the head in the curNode variable;                             

    if(curNode == NULL){                        //Make sure the list isn't empty
        return NULL;
    }

    //Go through the list and find the highest priority
    while(curNode != NULL){

        //Overwrite the priorityCounter if the current node has a higher priority
        if(curNode->proc->priority > priorityCounter){
            if(curNode->proc->priority == 10){  //Check if this is the highest priority
                return curNode->proc;           //If it is, just return it
            }
            priorityCounter = curNode->proc->priority;
        }
        curNode = curNode->next;                //Set curNode to the next node
    }

    curNode = list->head;                       //Set curNode back to the list's head

    //Now go back through the lsit until we find the highest priority
    while(curNode != NULL){
        
        //Check to see if curNode matches our highest priority
        if(curNode->proc->priority == priorityCounter){
            return curNode->proc;               //Return this proc
        }
        curNode = curNode->next;                //Set curNode to the next node
    }
    return NULL;                                //Backup return in case something messes up
}

//popLeastTime
//This function will return the proc with the least total time remaining
Process *popLeastTimeTotal(DoublyLinkedList *list){
    int lowestTime = 9999;                      //Variable to keep track of the lowest time
    int timer = 0;                              //Variable to keep track of the current total time p0er proc
    Node *curNode = list->head;                 //Store the head in the curNode variable;                             

    if(curNode == NULL){                        //Make sure the list isn't empty
        return NULL;
    }

    while(curNode != NULL){

        timer = 0;                              //Reset timer back to zero

        //Add all of the burst times together from the current node
        for(int i = curNode->proc->index; i < curNode->proc->burst_count; i++){
            timer = timer + curNode->proc->burst_times[i];
        }
        
        if(timer < lowestTime){                 //Check if the total value is less than the lowest value
            lowestTime = timer;                 //Set lowestTime to the total time from the process
        }
    }

    curNode = list->head;                       //Set curNode back to the head

    while(curNode != NULL){

        timer = 0;                              //Reset timer back to zero

        //Add all of the burst times together from the current node
        for(int i = curNode->proc->index; i < curNode->proc->burst_count; i++){
            timer = timer + curNode->proc->burst_times[i];
        }

        if(timer == lowestTime){                //If this has the lowest time remaining return it
            return curNode->proc;
        }
    }
    return NULL;                                //Backup return if something bad happens



}
