#ifndef LIST_H
#define LIST_H
// Adithya added the bottom three headers
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct list {
	struct listentry* head;
	struct listentry* tail;
};

struct listentry {
	void *data;
	struct listentry *prev;
	struct listentry *next;
};

void list_rm(struct list* l, struct listentry* e)    // Remove an item from the list 
{// I am assuming that the item is there in the list
    struct listentry* curr=l->head;
    if (curr=e){// Adithya is not sure of what they ment by equal
        l->head=curr-> next;
        free (curr);
        return;
    }
    while (curr->next)// Head and tail requires sepreate handling
    {
        if (curr==e)
        {   
            curr->prev->next=curr->next;
            curr->next->prev=curr->prev;
            free (curr);
            return;
        }
        curr=curr->next;
    }
    if (curr=e){
        l->tail=curr->prev;
        free (curr);
        return;

    }
}
struct listentry* list_add(struct list* l, void* data)  // Add an item to the list
// Adithya is adding the newly created listentry to the end (tail) of the list
// Adithya is  considering that an empty list has both head and tail as NULL
{
    struct listentry* item = malloc(sizeof(struct listentry));
    item->prev=NULL;
    item-> next=NULL;
    if (l->tail==NULL)
    {
        l->head=item;
        l->tail=item;
    }
    else
    {
        l->tail->next=item;
        item->prev=l->tail;
        l->tail=item;
        }
    return item;
    }
struct list* list_new()  // Return an initialized list
{
    struct list* l= malloc (sizeof (struct list));
    l->head=NULL;
    l->tail=NULL;
    return l;

}
int is_empty(struct list* l)  // Check if list is empty or not
{
    if ((l->head) ==NULL)
    return 0;
    else
    return 1;
}
#endif
