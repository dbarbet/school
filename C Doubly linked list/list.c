/*David Barbet */
/**
 * CS 2110 - Spring 2014 - Homework #12
 * Edited by: Brandon Whitehead, Andrew Wilder
 * Completed by: David Barbet
 * list.c: Doubly linked list.
 */

#include <stdlib.h>
#include <stdio.h>
#include "list.h"

/* The node struct.  Has a prev pointer, next pointer, and data. */
typedef struct lnode
{
  struct lnode* prev; /* Pointer to previous node */
  struct lnode* next; /* Pointer to next node */
  void* data; /* User data */
} node;


static node* create_node(void* data);

/** create_node
  *
  * Creates a new node with data on the heap.
  * @param data a void pointer to data the user wants to store in the list
  * @return a node
  */
static node* create_node(void* data)
{
    node *newNode;
    newNode = malloc(sizeof(node));
    if (NULL == newNode) {
      printf("Failed creating node");
      return NULL;
    }
    newNode->next = NULL;
    newNode->prev = NULL;
    newNode->data = data;
    return newNode;
}

/** create_list
  *
  * Creates a new list on the heap.
  * @return an empty linked list
  */
list* create_list(void)
{
    list *newList;
    newList = malloc(sizeof(list));
    if (NULL == newList) {
      return NULL;
    }
    newList->head = NULL;
    newList->tail = NULL;
    newList->size = 0;
    return newList;
}

/** push_front
  *
  * Adds the data to the front of the linked list
  *
  * @param llist a pointer to the list.
  * @param data, new data to be added to the list.
  */
void push_front(list* llist, void* data)
{
    if (llist->size == 0) {
      node *newNode = create_node(data);
      newNode->prev = NULL;
      newNode->next = NULL;
      llist->head = newNode;
      llist->tail = newNode;
      llist->size = llist->size + 1;
    } else if (llist->size == 1) {
      node *newNode = create_node(data);
      node *oldHead = llist->head;
      newNode->next = llist->head;
      oldHead->prev = newNode;
      newNode->prev = NULL;
      llist->head = newNode;
      llist->size = llist->size + 1;
    } else {
      node *newNode = create_node(data);
      newNode->prev = NULL;
      newNode->next = llist->head;
      node *oldHead = llist->head;
      oldHead->prev = newNode;
      llist->head = newNode;
      llist->size = llist->size + 1;
    }
}

/** push_back
  *
  * Adds the data to the back/end of the linked list
  *
  * @param llist a pointer to the list.
  * @param data, new data to be added to the list.
  */
void push_back(list* llist, void* data)
{
    if (llist->size == 0) {
      node *newNode = create_node(data);
      newNode->prev = NULL;
      newNode->next = NULL;
      llist->head = newNode;
      llist->tail = newNode;
      llist->size = llist->size + 1;
    } else if (llist->size == 1) {
      node *newNode = create_node(data);
      newNode->prev = llist->tail;
      newNode->next = NULL;
      llist->tail->next = newNode;
      llist->tail = newNode;
      llist->size = llist->size + 1;
    } else {
      node *newNode = create_node(data);
      newNode->prev = llist->tail;
      newNode->next = NULL;
      llist->tail->next = newNode;
      llist->tail = newNode;
      llist->size = llist->size + 1;
    }
}

/** front
  *
  * Gets the data at the front of the linked list
  * If the list is empty return NULL.
  *
  * @param llist a pointer to the list
  * @return The data at the head of the list, or null.
  */
void* front(list* llist)
{
    if (llist->size == 0) {
      printf("Correct size\n");
      return NULL;
    }
    node *curHead = llist->head;
    return curHead->data;
}

/** back
  *
  * Gets the data at the back of the linked list.
  *
  * @param llist a pointer to the list
  * @return The data at the tail, or null.
  */
void* back(list* llist)
{
  if (llist->size == 0) {
    printf("Correct size");
    return NULL;
  }
    node *curTail = llist->tail;
    return curTail->data;
}

/** remove_front
  *
  * Removes the node at the front of the linked list
  * @param llist a pointer to the list.
  * @param free_func, pointer to function to free the data contained in the node.
  * @return -1 if the remove failed, 0 if the remove succeeded.
  */
int remove_front(list* llist, list_op free_func)
{
    if (llist->size == 0) {
      return -1;
    } else if (llist->size == 1) {
      node *onlyNode = llist->head;
      free_func(onlyNode->data);
      free(onlyNode);
      llist->head = NULL;
      llist->tail = NULL;
      llist->size = 0;
    } else if (llist->size == 2) {
      node *removeNode = llist->head;
      node *nextHead = removeNode->next;
      free_func(removeNode->data);
      free(removeNode);
      nextHead->prev = NULL;
      llist->head = nextHead;
      llist->tail = nextHead;
      llist->size = llist->size - 1;
    } else {
      node *removeNode = llist->head;
      node *nextHead = removeNode->next;
      free_func(removeNode->data);
      free(removeNode);
      nextHead->prev = NULL;
      llist->head = nextHead;
      llist->size = llist->size - 1;
    }
    return 0;
}

/** remove_back
  *
  * Removes the node at the tail of the linked list
  * @param llist a pointer to the list.
  * @param free_func, pointer to function to free the data contained in the node.
  * @return -1 if the remove failed 0 if the remove succeeded.
  */
int remove_back(list* llist, list_op free_func)
{
    if (llist->size == 0) {
      return -1;
    } else if (llist->size == 1) {
      node *onlyNode = llist->tail;
      free_func(onlyNode->data);
      free(onlyNode);
      llist->head = NULL;
      llist->tail = NULL;
      llist->size = 0;
    } else if (llist->size == 2) {
      node *removeNode = llist->tail;
      node *newTail = removeNode->prev;
      free_func(removeNode->data);
      free(removeNode);
      newTail->next = NULL;
      newTail->prev = NULL;
      llist->head = newTail;
      llist->tail = newTail;
      llist->size = llist->size - 1;
    } else {
      node *removeNode = llist->tail;
      node *nextTail = removeNode->prev;
      free_func(removeNode->data);
      free(removeNode);
      nextTail->next = NULL;
      llist->tail = nextTail;
      llist->size = llist->size - 1;
    }
    return 0;
}

/** copy_list
  *
  * Deep copy of a given list.
  * @param llist A pointer to the linked list to make a copy of
  * @param copy_func, a function pointer that makes a deep copy of the data.
  * @return The linked list created by copying the old one
  */
list* copy_list(list* llist, list_cpy copy_func)
{
  list *newList = create_list();
  node *iterNode = llist->head;
  while (newList->size < llist->size) {
    push_back(newList, copy_func(iterNode->data));
    iterNode = iterNode->next;
  }
	return newList;
}

/** size
  *
  * Gets the size of the linked list
  *
  * @param llist a pointer to the list
  * @return The size of the linked list
  */
int size(list* llist)
{
    ///@note simply return the size of the linked list.  Its that easy!
    return llist->size;
}

/** remove_if
  *
  * Removes all nodes whose data when passed into the predicate function returns true
  *
  * @param llist a pointer to the list
  * @param pred_func a pointer to a function that when it returns true it will remove the element from the list and do nothing otherwise
  * @param free_func a pointer to a function that is responsible for freeing the node's data
  * @return the number of nodes that were removed.
  */
int remove_if(list* llist, list_pred pred_func, list_op free_func)
{
    node *iterNode = llist->head;
    int numRemoved = 0;
    while (iterNode != NULL) {
      node *nextNode = iterNode->next;
      if (pred_func(iterNode->data)) {
        numRemoved += 1;
        if (NULL == iterNode->prev) {
          //Node being removed is head.
          remove_front(llist, free_func);
          nextNode = llist->head;
        } else if (NULL == iterNode->next) {
          nextNode = NULL;
          //Node being removed is tail.
          remove_back(llist, free_func);
        } else {
          //Node being removed is in the middle.
          nextNode = iterNode->next;
          node *removeNode = iterNode;
          node *prevN = iterNode->prev;
          node *nextN = iterNode->next;
          free_func(removeNode->data);
          free(removeNode);
          prevN->next = nextN;
          nextN->prev = prevN;
          llist->size = llist->size - 1;
        }
      }
      iterNode = nextNode;
    }
    return numRemoved;
}

/** is_empty
  *
  * Checks to see if the list is empty.
  *
  * @param llist a pointer to the list
  * @return 1 if the list is indeed empty 0 otherwise.
  */
int is_empty(list* llist)
{
    ///@note an empty list by the way we want you to implement it has a size of zero and head points to NULL.
    if ((llist->size == 0) && (llist->head == NULL)) {
      return 1;
    } else {
      return 0;
    }
}

/** empty_list
  *
  * Empties the list after this is called the list should be empty.
  *
  * @param llist a pointer to a linked list.
  * @param free_func function used to free the node's data.
  */
void empty_list(list* llist, list_op free_func)
{
    while (llist->size > 0) {
      remove_front(llist, free_func);
    }
}

/** traverse
  *
  * Traverses the linked list calling a function on each node's data.
  *
  * @param llist a pointer to a linked list.
  * @param do_func a function that does something to each node's data.
  */
void traverse(list* llist, list_op do_func)
{
    int i;
    node *newNode = llist->head;
    for (i = 0; i < llist->size; i++) {
      do_func(newNode->data);
      newNode = newNode->next;
    }
}
