#include "mythread.h"
#include "list.h"
#include <string.h>
#define SZ 4096

struct hashmap_element_s {
  char *key;
  void *data;
};

struct hashmap_s {
  struct list* table[SZ];
  struct lock* lk[SZ];
};

// This is a  dummy hashfunction
int hashfunciton( char string[],int len)
{   if (len=0)
    return 0;
    else
    return (4096*((int) (string[len-1]))+ hashfunction(string,(len-1)))%4096;
}

void create_listelement (struct hashmap_s *const hashmap, const char* key, void* data)   // Set value of the key as data in hashmap. You can use any method to resolve conflicts. Also write your own hashing function

   {// first, I am trying to find the length of the word (by finding the position of the \0 ). This is required to make an array to store the word
   int length=0;
   char* curr=key;
   while (*curr !='/0')
   {
    length++;
    curr++;
   }// At the end of this loop, the varable "length will contain the length of the word"
   char word [length+1];
   word[length]='\0';
   curr=key;
   for(int i =0;i<length;i++)
   {
    word [i]=*curr;
    curr++;
   }
   struct hashmap_element_s* dat=malloc(sizeof(struct hashmap_element_s));
   dat-> key=key;
   dat->data=data;
   int bucket=hashfunciton(word,length);
   list_add(hashmap->table[bucket],dat);
   
}

int hashmap_create(struct hashmap_s *const out_hashmap);   // Initialize a hashmap
int hashmap_put(struct hashmap_s *const hashmap, const char* key, void* data)   // Set value of the key as data in hashmap. You can use any method to resolve conflicts. Also write your own hashing function

   {// first, I am trying to find the length of the word (by finding the position of the \0 ). This is required to make an array to store the word
   int length=0;
   char* curr=key;
   while (*curr !='/0')
   {
    length++;
    curr++;
   }// At the end of this loop, the varable "length will contain the length of the word"
   char word [length+1];
   word[length]='\0';
   curr=key;
   for(int i =0;i<length;i++)
   {
    word [i]=*curr;
    curr++;
   }
   int bucket=hashfunciton(word,length);
   struct listentry* pointer=hashmap->table[bucket]->head;
   // checking if the word already exists in the table
   while (pointer!=NULL)
   {
    if (strcomp(((struct hashmap_element_s*)(pointer->data))->key,key))
    {
      ((struct hashmap_element_s*)(pointer->data))->data=data;
      return 0;
    }
    pointer=pointer->next;
   }// The loop ends if the word is not the table. In this case, we have to make a new list_element

   create_listelement(hashmap,key,data);
   return 0;
}
void* hashmap_get(struct hashmap_s *const hashmap, const char* key)    // Fetch value of a key from hashmap
{
  int length=0;
   char* curr=key;
   while (*curr !='/0')
   {
    length++;
    curr++;
   }// At the end of this loop, the varable "length will contain the length of the word"
   char word [length+1];
   word[length]='\0';
   curr=key;
   for(int i =0;i<length;i++)
   {
    word [i]=*curr;
    curr++;
   }
   int bucket=hashfunciton(word,length);
   struct listentry* pointer=hashmap->table[bucket]->head;
   // checking if the word already exists in the table
   while (pointer !=NULL)
   {
    if (strcomp(((struct hashmap_emement_s*)(pointer->data))->key,key))
    {
      return ((struct hashmap_element_s*)(pointer->data));
    }
    pointer=pointer->next;
   }// The loop ends if the word is not the table. In this case, we have to make a new list_eleme
   retrun NULL;
}
void hashmap_iterator(struct hashmap_s* const hashmap, 
                        int (*f)(struct hashmap_element_s *const));  // Execute argument function on each key-value pair in hashmap

int acquire_bucket(struct hashmap_s *const hashmap, const char* key);   // Acquire lock on a hashmap slot
int release_bucket(struct hashmap_s *const hashmap, const char* key);   // Release acquired lock