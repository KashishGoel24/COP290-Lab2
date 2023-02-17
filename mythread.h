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
// ucontext_t dummy;

ucontext_t dummy;

void mythread_init()     // Initialize threads list
{
	// printf("in my thread init\n");
	thread_list=list_new();
}
ucontext_t* mythread_create(void func(void*), void* arg)  // Create a new thread
{  
	ucontext_t thread=malloc(sizeof(struct ucontext_t));

	printf("hemlo\n");
	getcontext(&thread);
	// char st1[8192];
	char* st1=malloc(8192*sizeof(char));
	thread.uc_stack.ss_sp = st1;
    thread.uc_stack.ss_size = sizeof st1;
    thread.uc_link = &dummy;
	makecontext(&thread,(ucfunc_t)func,1,arg);
	list_add(thread_list,&thread);
	return &thread;

	//(thread_list->head->data).uc_link 
}

void mythread_join()  // Waits for other thread to complete. It is used in case of dependent threads.
{
	// struct listentry* curr=thread_list->head;
	struct listentry* curr=malloc(sizeof(struct listentry));
	curr = thread_list->head;
	printf("fbafbakjbaf\n");
	while (curr!=NULL)
	{	
		printf("am in the loop\n");
		swapcontext (&dummy,curr->data);
		// getcontext(&dummy);
		// setcontext(curr->data);
		printf("going to the next line\n");
		curr=curr->next;
		printf("going to the next element of the list\n");
	}
	printf("out of the loop in the function mythread_join\n");
	return;
}
void mythread_yield();  // Perform context switching here

struct lock {
	ucontext_t* ctx;
};
struct lock* lock_new();   // return an initialized lock object
void lock_acquire(struct lock* lk);   // Set lock. Yield if lock is acquired by some other thread.
int lock_release(struct lock* lk);   // Release lock

#endif
