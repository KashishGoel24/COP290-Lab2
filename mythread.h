#ifndef THREAD_H
#define THREAD_H
#include "list.h"
#include<stdio.h>
#include<stdlib.h>
#include<ucontext.h>
#include<signal.h>
#include<sys/time.h>
#include<unistd.h>
struct list* thread_list;
ucontext_t dummy;
void mythread_init()     // Initialize threads list
{
	thread_list=list_new();
}
ucontext_t* mythread_create(void func(void*), void* arg)  // Create a new thread
{
	ucontext_t* thread;
	getcontext(thread);
	char st1[8192];
	*thread.uc_stack.ss_sp = st1;
    *thread.uc_stack.ss_size = sizeof st1;
    *thread.uc_link = &dummy;
	makecontext(thread,func(arg) ,1);
	list_add(thread_list,thread);
	return thread;
}

void mythread_join()  // Waits for other thread to complete. It is used in case of dependent threads.
{
	struct listentry* curr=thread_list->head;
	while (curr!=NULL)
	{	swapcontext (&dummy,curr->data);
		curr=curr->next;
	}
}
void mythread_yield();  // Perform context switching here

struct lock {
	ucontext_t* ctx;
};
struct lock* lock_new();   // return an initialized lock object
void lock_acquire(struct lock* lk);   // Set lock. Yield if lock is acquired by some other thread.
int lock_release(struct lock* lk);   // Release lock

#endif
