/*----------------------------------------------------------
 *				HTBLA-Leonding / Klasse: <your class>
 * ---------------------------------------------------------
 * Exercise Number: 0
 * Title:			dictionary.cpp
 * Author:			P. Bauer
 * Due Date:		November 25, 2012
 * ----------------------------------------------------------
 * Description:
 * Implementation of dictionary.h.
 * ----------------------------------------------------------
 */
#include "dictionary.h"
#include "general.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <strings.h>
typedef struct NodeImplementation* Node;

struct NodeImplementation
{
  const char* word;
  Node next;
};

struct DictionaryImplementation
{
  int length;
  Node head;
  bool Interated;
};

Dictionary 	new_dictionary ()
{
  Dictionary dictionary = (Dictionary)malloc(sizeof(struct DictionaryImplementation));
  dictionary->length = 0;
  dictionary->head = 0;
  dictionary->Interated = false;
  return dictionary;
}

void 	delete_dictionary (Dictionary dictionary)
{
  Node current = dictionary->head;
  while (current != 0)
  {
    Node del = current;
    current = current->next;
    sfree(del);
  }
  dictionary->length = 0;
  dictionary->head = 0;
  sfree(dictionary);
}

 void 	add (Dictionary dict, const char *word)
 {
   Node insert = (Node)malloc(sizeof(struct NodeImplementation));
   insert->word = word;
   insert->next = 0;
   Node current = dict->head;
   if (is_in_dict(dict,word))
   {
     return;
   }
   if (dict->head == 0)
   {
     dict->head = insert;
   }
   else
   {
     while (current->next != 0)
     {
       current = current->next;
     }
     current->next = insert;
   }
   dict->length++;
 }

 int 	get_size (Dictionary dict)
 {
   return dict->length;
 }

 bool 	is_in_dict (Dictionary dict, const char *word)
 {
     Node current = dict->head;
       while (current != 0)
       {
         if (strcasecmp(current->word,word) == 0)
          {
                return true;
          }
         current = current->next;
       }
       return false;
 }

 void 	start_iterating (Dictionary dict)
 {
   dict->Interated = true;
 }

 bool 	has_next (Dictionary dict)
 {
   if (dict->head != 0 && dict->Interated == true)
   {
     return true;
   }
   return false;
 }

 const char * 	get_next_entry (Dictionary dict)
 {
   if (has_next(dict) && dict->Interated == true)
   {
     const char* w = dict->head->word;
     dict->head = dict->head->next;
     return w;
   }
   return 0;
 }

 void 	insert_sorted (Dictionary dict, const char *word)
 {
   if (dict->head == 0)
     {
         add(dict,word); // Removed if and added add function
     }
     else
     {
       if (is_in_dict(dict,word)) //Added if
       {
          return;
       }

       Node w =(Node)malloc(sizeof(NodeImplementation));
       w->word=word;
       w->next=0;
       if (strcasecmp(dict->head->word,word)>0) //Added contains of if and changed < to >
       {
         w->next=dict->head;
         dict->head=w;
         dict->length++; //Added
       }
       else
       {
         Node current=dict->head;
         while (current->next !=0 && strcasecmp(current->next->word,word)<0) // && strcasecmp(current->next->word,word)<0
         {
           current=current->next;
         }

         if (current->next == 0) // Added if
         {
           add(dict,word);
         }

         if (strcasecmp(current->next->word,word)>0) // Moved the if from the while into here
         {
           w->next=current->next;
           current->next=w;
           dict->length++; // Added
         }
       }
     }
 }
