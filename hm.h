#include "mythread.h"
#include "list.h"
#define SZ 4096
/**
 * @brief This is the data structure to store the elememt of the hashmap
 * 
 */
struct hashmap_element_s {
  char *key;
  void *data;
};

/**
 * @brief This is the data structure to store the hashmap
 * 
 */
struct hashmap_s {
  struct list* table[SZ];
  struct lock* lk[SZ];
};

/**
 * @brief This function initializes a hashmap
 * 
 * @param out_hashmap A pointer to the hashmap
 * @return int
 */
int hashmap_create(struct hashmap_s *const out_hashmap);   // Initialize a hashmap

/**
 * @brief This function modifies the value of a key to the given value. A new key with the given value is made if the key is not present.
 * 
 * @param hashmap A pointer to the hasmap
 * @param key A pointer to the key 
 * @param data A pointer to the (new)value of the key
 * @return int 
 */
int hashmap_put(struct hashmap_s *const hashmap, const char* key, void* data);   // Set value of the key as data in hashmap. You can use any method to resolve conflicts. Also write your own hashing function

/**
 * @brief The function returns the value of a key
 * 
 * @param hashmap A pointer to the hashmap
 * @param key The key whose value is to be extracted
 * @return void* A pointer to the value of the key
 */
void* hashmap_get(struct hashmap_s *const hashmap, const char* key);    // Fetch value of a key from hashmap

/**
 * @brief This function execute the arguement function on each key-value pair in hashmap
 * 
 * @param hashmap A pointer to the hashmap
 * @param f A pointer to the function that is to be executed
 */
void hashmap_iterator(struct hashmap_s* const hashmap, 
                        int (*f)(struct hashmap_element_s *const));  // Execute argument function on each key-value pair in hashmap
/**
 * @brief This function acquires lock on a hashmap slot
 * 
 * @param hashmap A pointer to the hashmap
 * @param key A pointer to the key whose slot is to be locked
 * @return int 
 */
int acquire_bucket(struct hashmap_s *const hashmap, const char* key);   // Acquire lock on a hashmap slot

/**
 * @brief This function releases the acquired lock
 * 
 * @param hashmap A pointer to the hashmap
 * @param key A pointer to the key whose slot is to be released
 * @return int 
 */
int release_bucket(struct hashmap_s *const hashmap, const char* key);   // Release acquired lock
