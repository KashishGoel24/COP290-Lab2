#ifndef LIST_H
#define LIST_H

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
//Vidushi and Kashish designed the functions list_rm and list_add
void list_rm(struct list* l, struct listentry* e)    // Remove an item from the list 
{
    if (l->head==e){
        l->head=e->next;
        free (e);
        return;
    }
    if(l->tail==e){
        l->tail=e->prev;
        free(e);
        return;
    }

    e->prev->next=e->next;
    e->next->prev=e->prev;
    free(e);
    return;
}

struct listentry* list_add(struct list* l, void* data)  // Add an item to the list
{  
    if (l->tail==NULL){    
        struct listentry* item = malloc(sizeof(struct listentry));
        item->prev=NULL;
        item->next=NULL;
        item->data=data;
        l->head=item;
        l->tail=item;
        return item;  
    }else{
        struct listentry* item = malloc(sizeof(struct listentry));
        item-> next=NULL;
        item->data=data;
        l->tail->next=item;
        item->prev=l->tail;
        l->tail=item;  
        return item;
    }  
}

//Adithya designed the bottom 2 functions
struct list* list_new()  // Return an initialized list
{
    struct list* l= malloc (sizeof (struct list));
    l->head=NULL;
    l->tail=NULL;
    return l;

}
int is_empty(struct list* l)  // Check if list is empty or not
{
    if ((l->head) ==NULL) return 1;
    
    return 0;
}

#endif
