#ifndef LIST_H
#define LIST_H
/**
 * @brief This is the data structure to store a list
 * 
 */
struct list {
	struct listentry* head;
	struct listentry* tail;
};

/**
 * @brief This is the data structure for a node in the list
 * 
 */
struct listentry {
	void *data;
	struct listentry *prev;
	struct listentry *next;
};
/**
 * @brief This function removes a node from the list
 * 
 * @param l A pointer to the list
 * @param e A pointer to the node to be removed
 */
void list_rm(struct list* l, struct listentry* e);    // Remove an item from the list
/**
 * @brief This function adds a node to the end of the list
 * 
 * @param l A pointer to the list
 * @param data A pointer to the data which should be associated with the newly added node
 * @return struct listentry* A pointer to the newly added node
 */
struct listentry* list_add(struct list* l, void* data);  // Add an item to the list
/**
 * @brief This function return an initialized list
 * 
 * @return struct list* A pointer to the list
 */
struct list* list_new();  // Return an initialized list
/**
 * @brief This function checks if list is empty or not
 * 
 * @param l A pointer to teh list
 * @return int returns 1 if the list is empty and 0 if the list is non-empty
 */
int is_empty(struct list* l);  // Check if list is empty or not
#endif
