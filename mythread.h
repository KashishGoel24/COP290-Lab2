#ifndef THREAD_H
#define THREAD_H

#include<stdio.h>
#include<stdlib.h>
#include<ucontext.h>
#include<signal.h>
#include<sys/time.h>
#include<unistd.h>
/**
 * @brief This function intializes threads list
 * 
 */
void mythread_init();      // Initialize threads list
/**
 * @brief This function creates a new thread linked with the function it recieves as the arguement.
 * 
 * @param func A pointer to the function that is to be linked with the thread
 * @param arg A pointer to the argurement that is to be passed to the function
 * @return ucontext_t* Returns a pointer to the newly created thread
 */
ucontext_t* mythread_create(void func(void*), void* arg);  // Create a new thread
/**
 * @brief This function waits for other thread to complete. It is used in case of dependent threads.
 * 
 */
void mythread_join();  // Waits for other thread to complete. It is used in case of dependent threads.
/**
 * @brief This function performs context switching
 * 
 */
void mythread_yield();  // Perform context switching here
/**
 * @brief This is the data structure for the lock
 * 
 */
struct lock {
	ucontext_t* ctx;
};
/**
 * @brief This function returns an intitialzed lock object
 * 
 * @return struct lock* 
 */
struct lock* lock_new();   // return an initialized lock object
/**
 * @brief This function sets the value of the lock to the current thread and calls mythread_yield if the lock is acquired by some other thread.
 * 
 * @param lk A pointer to the lock 
 */
void lock_acquire(struct lock* lk);   // Set lock. Yield if lock is acquired by some other thread.
/**
 * @brief This function releases a lock
 * 
 * @param lk A pointer to the lock
 * @return int 
 */
int lock_release(struct lock* lk);   // Release lock

#endif
