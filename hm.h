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
int hashfunction( char string[],int len)
{   if (len == 0)
      {
        return 0;
      }
    else
    return (3023*((int) (string[len-1]))+ hashfunction(string,(len-1)))%4096;// A  completely random hash funciton.
}

int hashmap_create(struct hashmap_s *const out_hashmap)   // Initialize a hashmap
{
  for (int i=0;i<SZ;i++)
  {
    out_hashmap->table[i]=list_new();
    // out_hashmap->lk[i]=lock_new();
  }
}


int hashmap_put(struct hashmap_s const* hashmap, const char* key, void* data)   // Set value of the key as data in hashmap. You can use any method to resolve conflicts. Also write your own hashing function

   {  
    char * duuum = (char*)(key);
    int num=hashfunction(duuum,strlen(duuum));
    struct list*  raghav_list= hashmap->table[num];
    struct listentry* raghav_ka_element = raghav_list->head;
    while(raghav_ka_element!=NULL)
    {
      struct hashmap_element_s* hs=(struct hashmap_element_s*)raghav_ka_element->data;
      if((strcmp(hs->key,duuum)))
      {
          raghav_ka_element = raghav_ka_element->next;
      }
      else
      {
        hs->data=data;
        return -1;

      }
    }
    struct hashmap_element_s* newww = (struct hashmap_element_s*)malloc(sizeof(struct hashmap_element_s));
    newww->key=malloc((strlen(duuum)+1)*sizeof(char));
    strcpy(newww->key,key);
    newww->data=data;
    printf("%s\n\n",newww->key);
    list_add(raghav_list,newww);
    return -1;
}

void* hashmap_get(struct hashmap_s const* hashmap, const char* key)    // Fetch value of a key from hashmap
{

  char * duuum = (char*)(key);
    int num=hashfunction(duuum,strlen(duuum));
    struct list*  raghav_list= hashmap->table[num];
    struct listentry* raghav_ka_element = raghav_list->head;
    while(raghav_ka_element!=NULL)
    {
      struct hashmap_element_s* hs=(struct hashmap_element_s*)raghav_ka_element->data;
      if(strcmp(hs->key,duuum))
      {
          raghav_ka_element = raghav_ka_element->next;
      }
      else
      {
        return hs->data;

      }

    }
    return NULL;

}


void hashmap_iterator(struct hashmap_s* const hashmap, int (*f)(struct hashmap_element_s *const))  // Execute argument function on each key-value pair in hashmap
{
  for(int i =0; i<SZ;i++)
  {
    struct listentry* curr= hashmap->table[i]->head;
    while (curr!=NULL)
    {
        (f)((struct hashmap_element_s*)(curr->data));
        curr=curr->next;
    }
  }
}


int acquire_bucket(struct hashmap_s const hashmap, const char key);   // Acquire lock on a hashmap slot
int release_bucket(struct hashmap_s const hashmap, const char key);   // Release acquired lock
