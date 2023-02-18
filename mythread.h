#ifndef THREAD_H
#define THREAD_H
#include "list.h"
#include<stdio.h>
#include<stdlib.h>
#include<ucontext.h>
#include<signal.h>
#include<sys/time.h>
#include<unistd.h>

typedef void (* ucfunc_t)(void);
struct list* thread_list;

static ucontext_t* dummy;
static ucontext_t* glob;
static struct listentry* curr;
void mythread_init()     // Initialize threads list
{
    dummy=(ucontext_t*)malloc(sizeof(ucontext_t));
	glob=(ucontext_t*)malloc(sizeof(ucontext_t));
	curr=malloc(sizeof(struct listentry));
    thread_list=list_new();
}

ucontext_t* mythread_create(void func(void*), void* arg)  // Create a new thread
{  
    ucontext_t* thread=(ucontext_t*)malloc(sizeof(ucontext_t));
    getcontext(thread);
    char* st1=(char*)malloc(8192*sizeof(char));
    (thread)->uc_stack.ss_sp = st1;
    (thread)->uc_stack.ss_size = 8192;
    (thread)->uc_link = dummy;
    makecontext(thread,(ucfunc_t)func,1,arg);
    list_add(thread_list,thread);
    return thread; 
}

void mythread_join()  // Waits for other thread to complete. It is used in case of dependent threads.
{
    curr = thread_list->head;
    if (curr->data == NULL){
		return;
    }
    while (curr!=NULL)
    {   
        swapcontext (dummy,curr->data);
        curr=curr->next;
		//list_rm(thread_list,curr->prev);
		//thread_list->head=curr;
		//curr->prev=NULL;
    }
	// if(thread_list->head==NULL)
	// {
	// 	return;
	// }
	// ucontext_t smth = 
	// smth=(ucontext_t*)thread_list->head->data;
	// thread_list->head=thread_list->head->next;
	// thread_list->head->prev=NULL;
	// swapcontext(dummy,smth);
	// mythread_join();

	// if(thread_list->head->data==NULL){
	// }
	// while(thread_list->head!=NULL){
	// 	swapcontext(dummy,thread_list->head->data);
	// 	list_rm(thread_list,thread_list->head);
	// }
     return;
}

void mythread_yield()  // Perform context switching here
{
	struct listentry* halo=(struct listentry*)malloc(sizeof(struct listentry));
	halo=curr;
	curr=curr->next;
	list_add(thread_list,halo);
	swapcontext((ucontext_t*)halo->data,(ucontext_t*)curr->data);
}
struct lock {
    ucontext_t* ctx;
};

struct lock* lock_new();   // return an initialized lock object
void lock_acquire(struct lock* lk);   // Set lock. Yield if lock is acquired by some other thread.
int lock_release(struct lock* lk);   // Release lock

#endif
