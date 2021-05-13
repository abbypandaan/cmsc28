#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node {
   int data;
   struct Node *next;
};

// To add at the start of the list
int addStart(struct Node** head_ref, int new_data) {

    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));

    new_node->data = new_data;

    new_node->next = (*head_ref);

    (*head_ref) = new_node;

    return 0;
}

// To add at the end of the list
int addEnd(struct Node** head_ref, int new_data) {

    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));

    struct Node *last = *head_ref;

    new_node->data = new_data;

    new_node->next = NULL;

    if (*head_ref == NULL)
    {
       *head_ref = new_node;
       return 0;
    }

    while (last->next != NULL)
        last = last->next;

    last->next = new_node;

    return 0;
}

// To add at a specific position
int addAtPosition(struct Node** head_ref, int new_data, int position) {

    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));

    struct Node *current = *head_ref;
    struct Node *previous = NULL;

    if (*head_ref == NULL) {
       *head_ref = new_node;
       return 0;
    }
    else {
        int currentPosition = 1;
        int success = 0;
        while (success == 0) {
            if (position == currentPosition) {
                if (previous == NULL) {
                    return 1;
                }
                else {
                    new_node->data = new_data;
                    previous->next = new_node;
                    new_node->next = current;
                    success = 1;
                }
            }
            else if (current->next == NULL && position > currentPosition) {
                return 2;
            }
            else {
                currentPosition++;
                previous = current;
                current = current->next;
            }
        }
    }
    return 0;
}

// To delete item
int deleteItem(struct Node** head_ref, int key) {

    struct Node *temp = *head_ref, *prev;
    int currentPosition = 1;

    if (temp != NULL && temp->data == key) {
        *head_ref = temp->next;
        free(temp);
        return currentPosition;
    }

    while (temp != NULL && temp->data != key) {
        prev = temp;
        temp = temp->next;
        currentPosition++;
    }

    if (temp == NULL)
        return 0;

    prev->next = temp->next;

    free(temp);
    return currentPosition;
}

// To display list
void displayList(struct Node* n) {

    int position = 1;
   	while (n != NULL) {
        printf("%i, at position %i\n", n->data, position);
        n = n->next;
        position++;
    }
}

// To delete list
int deleteList(struct Node** head_ref) {

   struct Node* current = *head_ref;
   struct Node* next;

   while (current != NULL)
   {
       next = current->next;
       free(current);
       current = next;
   }

   *head_ref = NULL;
   return 0;
}

// To search item
int searchItem(struct Node** head_ref, int key) {

    struct Node *temp = *head_ref;
    int currentPosition = 1;

    if (temp != NULL && temp->data == key) {
        *head_ref = temp->next;
        return currentPosition;
    }

    while (temp != NULL && temp->data != key) {
        temp = temp->next;
        currentPosition++;
    }

    if (temp == NULL)
        return 0;

    return currentPosition;
}

int main () {

    struct Node* head = NULL;

    addStart (&head, 10);
    addStart (&head, 5);
    addEnd (&head, 15);

    int choice = 1;
    int item;
    int position;
    int result;

    while(choice != 0)
    {
        printf("List Menu:\n [1] Add Item\n [2] Delete Item\n [3] Display List\n [4] Delete List\n [5] Search Item\n [0] Exit Program\n Enter choice: ");
        scanf("%i", &choice);

        // To add item
        if (choice == 1) {
            printf("Please enter the item to be added: ");
            scanf("%i", &item);

            printf("Where to add the item?\n [1] Start of the list\n [2] End of the list\n [3] Specific position\n [0] Cancel\n Enter choice: ");
            scanf("%i", &choice);

                if (choice == 1) {
                    addStart (&head, item);
                }

                else if (choice == 2) {
                    addEnd (&head, item);
                }

                else if (choice == 3) {
                    printf("Please enter the position: ");
                    scanf("%i", &position);
                    result = addAtPosition(&head, item, position);
                    if (result == 1) {
                        addStart (&head, item);
                    }
                    else if (result == 2) {
                        addEnd (&head, item);
                    }
                }

                else if (choice == 0) {
                }

                else {
                    printf("Invalid input!\n");
                }
        }

        // To delete item
        else if (choice == 2) {
            printf("Please enter the item to be deleted: ");
            scanf("%i", &item);
            result = deleteItem(&head, item);
            if (result > 0) {
                printf("The element %i, which is at position %i, has been deleted\n", item, result);
            }
            else {
                printf("The list contains no such element\n");
            }
        }

        // To display list
        else if (choice == 3) {
            displayList(head);
        }

        // To delete list
        else if (choice == 4) {
            deleteList(&head);
            printf("The list has been emptied!\n");
        }

        // To search for an item
        else if (choice == 5) {
            printf("Please enter the item to be searched: ");
            scanf("%i", &item);
            result = searchItem(&head, item);
            if (result > 0) {
                printf("Item is located at position %i\n", result);
            }
            else {
                printf("Item not found on the list\n");
            }
        }

        // To exit
        else if (choice == 0) {
        }

        else {
            printf("Invalid input!\n");
        }
    }
    return 0;
}