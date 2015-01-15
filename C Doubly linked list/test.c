#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/* David Barbet */
/* Testing doubly linked list.
 */
typedef struct person_t
{
    char* name;
    int age;
} Person;


// Create a new Person
Person* create_person(const char* name, int age)
{
    Person* p = (Person*) malloc(sizeof(Person));
    p->name = strdup(name);
    p->age = age;
    return p;
}

// Make a deep copy of a Person
void* copy_person(const void* data)
{
    Person *p = (Person*) data;
    return create_person(p->name, p->age);
}

// Print a Person
void print_person(void* data)
{
    Person *p = (Person*) data;
    printf("%s, %d\n", p->name, p->age);
}

// Free a Person
void free_person(void* data)
{
    Person *p = (Person*) data;
    // free any malloc'd pointers contained in the Person struct
    free(p->name);
    free(p);
}

// Return 1 if the person's name is 8+ characters long
int long_name(const void *data)
{
	Person *p = (Person*) data;
	return strlen(p->name) > 7;
}

int main(void)
{
	list* llist = create_list();

  	/* Print empty list */
  	printf("TEST CASE 1\nAn Empty list should print nothing here:\n");
  	traverse(llist, print_person);
	printf("\n");

 	/* Add front */
 	push_front(llist, create_person("Andrew", 24));
 	printf("TEST CASE 2\nA List with one person should print that person:\n");
 	traverse(llist, print_person);
 	printf("\n");

 	/* Remove front */
 	remove_front(llist, free_person);
 	printf("TEST CASE 3\nAnother Empty list should print nothing here:\n");
 	traverse(llist, print_person);
 	printf("\n");

 	/* Add 2 front */
 	push_front(llist, create_person("Nick", 22));
 	push_front(llist, create_person("Randal", 21));
 	printf("TEST CASE 4\nA List with two people should print those two people:\n");
 	traverse(llist, print_person);
 	printf("\n");

	/* Copy list */
	list* llist2 = copy_list(llist, copy_person);
	printf("TEST CASE 5\nA copied list should print out the same two people:\n");
 	traverse(llist2, print_person);
 	printf("\n");

  	/* Empty list */
  	empty_list(llist, free_person);
 	printf("TEST CASE 6\nAfter freeing all nodes the list should be empty:\n");
 	traverse(llist, print_person);
	printf("\n");

	/* Should remove anyone whose name is 8+ characters long */
	push_front(llist, create_person("Josephine", 27));
	push_front(llist, create_person("Dave", 34));
	push_front(llist, create_person("Benjamin", 23));
	push_front(llist, create_person("Lisa", 41));
	push_front(llist, create_person("Maximilian", 24));
	remove_if(llist, long_name, free_person);
	printf("TEST CASE 7\nShould only print 2 people with short names:\n");
	traverse(llist, print_person);
  printf("\n");
  
  /*Testing adding lots to fronts + traversal*/
  list* llist9 = create_list();
  push_front(llist9, create_person("Josephine", 27));
  push_front(llist9, create_person("Dave", 34));
  push_front(llist9, create_person("John", 45));
  push_front(llist9, create_person("Benjamin", 23));
  push_front(llist9, create_person("Lisa", 41));
  push_front(llist9, create_person("Maximilian", 24));
  push_front(llist9, create_person("Andrew", 24));
  printf("TEST CASE 7.5\nShould print long list (ADDFRONT WORKS)\n");
  traverse(llist9, print_person);
  printf("\n");

  /*test remove front*/
  remove_front(llist9, free_person);
  remove_front(llist9, free_person);
  remove_front(llist9, free_person);
  remove_front(llist9, free_person);
  remove_back(llist9, free_person);
  printf("TEST CASE 7.8\nTesting Remove front with remove back + updating head/tail\n");
  printf("Head is : ");
  print_person(front(llist9));
  printf("Tail is : ");
  print_person(back(llist9));
  printf("\n");
  printf("New list should contain 2 people: \n");
  printf("Size of list is: %d\n", size(llist9));
  printf("is_empty should be false: %d\n", is_empty(llist9));
  traverse(llist9, print_person);
  printf("\n");

  /*Testing emptying list with remove*/
  remove_front(llist9, free_person);
  remove_back(llist9, free_person);
  printf("TEST CASE 7.9\nTesting remove all\n");
  printf("List should be empty: \n");
  printf("Size of list is: %d\n", size(llist9));
  printf("is_empty should be true: %d\n", is_empty(llist9));
  traverse(llist9, print_person);
  printf("\n");

  /*Testing push_back for 1 */
  list* llist10 = create_list();
  push_back(llist10, create_person("Andrew", 24));
  push_back(llist10, create_person("John", 45));
  push_back(llist10, create_person("Josephine", 27));
  push_back(llist10, create_person("Dave", 34));
  push_back(llist10, create_person("Benjamin", 23));
  push_back(llist10, create_person("Lisa", 41));
  push_back(llist10, create_person("Maximilian", 24));
  printf("TEST CASE 8\nA Should print 7 length list (ADDBACK WORKS)\n");
  printf("Size of list is: %d\n", size(llist10));
  printf("is_empty should be false: %d\n", is_empty(llist10));
  traverse(llist10, print_person);
  printf("\n");
  /*Testing push_back for 2*/
  remove_back(llist10, free_person);
  remove_back(llist10, free_person);
  remove_back(llist10, free_person);
  remove_back(llist10, free_person);
  remove_back(llist10, free_person);
  remove_back(llist10, free_person);
  remove_back(llist10, free_person);
  printf("TEST CASE 9\nA long list removed from back should be empty (REMOVEBACK WORKS:\n");
  printf("Size of list is: %d\n", size(llist10));
  printf("is_empty should be true: %d\n", is_empty(llist10));
  traverse(llist10, print_person);
  printf("\n");
 	/* Testing over clean up*/
	empty_list(llist, free_person);
 	free(llist);
	empty_list(llist2, free_person);
	free(llist2);
  empty_list(llist10, free_person);
  free(llist10);
  empty_list(llist9, free_person);
  free(llist9);
  	return 0;
}

