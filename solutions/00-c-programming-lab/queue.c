/* 
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    if (q == NULL) {
        return NULL;
    }
    /* What if malloc returned NULL? */
    q->head = NULL;
    q->tail = NULL;
    q->len = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if (q == NULL) {
        return;
    }
    /* How about freeing the list elements and the strings? */
    list_ele_t *head = q->head;
    while (head != NULL) {
        list_ele_t *ele = head;
        head = ele->next;
        free(ele->value);
        free(ele);
    }
    /* Free queue structure */
    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    if (q == NULL) {
      return false;
    }
    list_ele_t* new_ele = malloc(sizeof(list_ele_t));
    if (new_ele == NULL) {
        return false;
    }
    char *new_s = malloc((strlen(s) + 1) * sizeof(char));
    if (new_s == NULL) {
        free(new_ele);
        return false;
    }
    strcpy(new_s, s);
    new_ele->value = new_s;
    new_ele->next = q->head;
    q->head = new_ele;
    if (q->tail == NULL) {
      q->tail = new_ele;
    }
    q->len += 1;
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    if (q == NULL) {
      return false;
    }
    list_ele_t* new_ele = malloc(sizeof(list_ele_t));
    if (new_ele == NULL) {
        return false;
    }
    char *new_s = malloc((strlen(s) + 1) * sizeof(char));
    if (new_s == NULL) {
        free(new_ele);
        return false;
    }
    strcpy(new_s, s);
    new_ele->value = new_s;
    new_ele->next = NULL;
    q->tail->next = new_ele;
    q->tail = new_ele;
    if (q->head == NULL) {
      q->head = new_ele;
    }
    q->len += 1;
    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* You need to fix up this code. */
    if (q == NULL || q->head == NULL) {
      return false;
    }
    if (bufsize > 0 && sp != NULL) {
        strncpy(sp, q->head->value, bufsize);
        sp[bufsize-1] = '\0';
    }
    list_ele_t* next_ele = q->head->next;
    free(q->head->value);
    free(q->head);
    q->head = next_ele;
    if (next_ele == NULL) {
      q->tail = NULL;
    }
    q->len -= 1;
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    if (q == NULL) {
        return 0;
    }
    return q->len;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* You need to write the code for this function */
    if (q == NULL || q->head == NULL) {
        return;
    }
    q->tail = q->head;
    list_ele_t* next_ele;
    while (q->tail->next != NULL) {
        next_ele = q->tail->next;
        q->tail->next = next_ele->next;
        next_ele->next = q->head;
        q->head = next_ele;
    }
}

