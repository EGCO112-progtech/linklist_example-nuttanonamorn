// Fig. 12.3: fig12_03.c
// Inserting and deleting nodes in a list
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// self-referential structure
struct Node {
    int id;
    char name[50];
    struct Node *nextPtr; // next node
    struct Node *pPtr; // previous node
}; // end structure listNode

typedef struct Node LLnode; // synonym for struct listNode
typedef LLnode *LLPtr;      // synonym for ListNode*



int isEmpty ( LLnode *head )
{
    return head == NULL;
}

LLnode *printList ( LLnode *head )
{
   if ( isEmpty( head ) ) {
      puts( "List is empty.\n" );
   } // end if
   else {
      puts( "\nThe list is:" );

      while ( head->nextPtr!= NULL ) {
         printf( "ID: %d\nName: %s \n--------------------------\n", head->id, head->name );
         head = head->nextPtr;  
      }

      printf( "ID: %d\nName: %s\n",head->id, head->name );
       
   }
}

LLnode *printReverseList ( LLnode *head )
{
   if ( isEmpty( head ) ) {
      puts( "List is empty.\n" );
   }
   else {
      puts( "\nThe Reversed list is:" );
      while ( head->nextPtr!= NULL ) {
         head = head->nextPtr;  
      }
      while ( head->pPtr!= NULL ) {
         printf( "ID: %d\nName: %s \n--------------------------\n", head->id, head->name );
         head = head->pPtr;  
      }
      printf( "ID: %d\nName: %s\n",head->id, head->name );
   }
}

void instructions()
{
   puts( "Enter your choice:\n"
      "   1 to insert an element into the list.\n"
      "   2 to delete an element from the list.\n"
      "   3 to end." );
}

LLnode *createNode ( int id, char *name )
{
    LLnode *result = malloc(sizeof(LLnode));
    result->id = id;
    // result->name = malloc(strlen(name) + 1);
    strcpy(result->name, name);
    result->nextPtr = NULL;
    result->pPtr = NULL;
    return result;
}

void insert (LLnode **head, LLnode* new_node)
{
    LLnode *tmp;

    if (*head == NULL) *head = new_node;
    else if ((*head)->id > new_node->id)
    {
        new_node->nextPtr = *head;
        new_node->nextPtr->pPtr = new_node;
        *head = new_node;
    }
    else 
    {
        tmp = *head;
        while (tmp->nextPtr != NULL && tmp->nextPtr->id < new_node->id) tmp = tmp->nextPtr;

        new_node->nextPtr = tmp->nextPtr;
        tmp->nextPtr = new_node;
        new_node->pPtr = tmp;
        if( new_node->nextPtr != NULL ) new_node->nextPtr->pPtr = new_node;
    }
}

void removeNode ( LLnode **head, LLnode *node_to_remove)
{
    if(*head == node_to_remove)
    {
        LLnode *tmp = *head;
        *head = (*head)->nextPtr;
        if ((*head) != NULL) (*head)->pPtr = NULL;
        free(tmp);
        return;
    }
    else
    {
        LLnode *tmp = node_to_remove;
        node_to_remove->pPtr->nextPtr = node_to_remove->nextPtr;
        if(node_to_remove->nextPtr != NULL) node_to_remove->nextPtr->pPtr = node_to_remove->pPtr;
        free(tmp);
    }
    return;
}

LLnode *findNode ( LLnode *head, int id)
{
    LLnode *tmp = head;
    while (tmp != NULL)
    {
        if (tmp->id == id) return tmp;
        tmp = tmp->nextPtr;
    }
    return NULL;
}

int main (void)
{
    LLnode *head = NULL;

    unsigned int choice;
    int item;
    char name[50];

    instructions();
    printf( "%s", "? " );
    scanf( "%u", &choice );
    while ( choice != 3 ) {
        switch ( choice ) {
            case 1:
            printf( "%s", "Enter a ID: " );
            scanf( "%d", &item );
            printf( "%s", "Enter a Name: " );
            scanf( " %s", name );
            insert( &head , createNode(item, name) );
            printList( head );
            printReverseList( head );
            break;
          
            case 2: // delete an element
            // if list is not empty
            if ( !isEmpty( head ) ) {
                printf( "%s", "Enter number to be deleted: " );
                scanf( "%d", &item );
                if ( findNode(head, item) ) 
                { 
                    removeNode( &head, findNode(head, item));
                    printf( "%d deleted.\n", item );
                    printList( head );
                    printReverseList( head );
                } // end if
                else
                  printf( "%d not found.\n\n", item ); // end else
            } // end whole if
            else
              puts( "List is now empty.\n" ); // end else
            break;
          
            default:
            puts( "Invalid choice.\n" );
            instructions();
            break;
        } // end switch

    printf( "%s", "? " );
    scanf( "%u", &choice );
   } // end while

    return 1;
}