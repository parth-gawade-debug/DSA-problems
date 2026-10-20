/*
 * Assignment: Workshop Enrollment Management System (Singly Linked List)
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef INTERACTIVE
#define PROMPT(...) printf(__VA_ARGS__)
#else
#define PROMPT(...)
#endif

// Node structure for Student Registration
typedef struct Node {
    int regNo;
    char name[50];
    struct Node* next;
} Node;

// Function Prototypes
Node* createHead(void);
Node* createNode(int regNo, const char* name);
void addStudent(Node* head);
void displayList(Node* head);
void countParticipants(Node* head);
void sortList(Node* head);
void reverseList(Node* head);
void addAtPosition(Node* head);
void deleteAtPosition(Node* head);
void freeList(Node* head);

/* ---------------- provided - do not modify ---------------- */
int main() {
    Node* head = createHead();
    int choice, r, c;

    while (1) {
        PROMPT("\n============================================\n");
        PROMPT("   WORKSHOP ENROLLMENT MANAGEMENT SYSTEM   \n");
        PROMPT("============================================\n");
        PROMPT("1. Add Students\n");
        PROMPT("2. Display Registered Students\n");
        PROMPT("3. Count Total Participants\n");
        PROMPT("4. Sort Student List (By Reg No)\n");
        PROMPT("5. Reverse Student List\n");
        PROMPT("6. Add a Student at Position\n");
        PROMPT("7. Delete a Student at Position\n");
        PROMPT("8. Delete All Students & Exit\n");
        PROMPT("--------------------------------------------\n");
        PROMPT("Enter your choice (1-8): ");
        r = scanf("%d", &choice);
        if (r == EOF) {                 // end of input: stop instead of looping forever
            freeList(head);
            return 0;
        }
        if (r != 1) {
            printf("Invalid input! Please enter a number.\n");
            while ((c = getchar()) != '\n' && c != EOF); // Clear buffer
            continue;
        }

        switch (choice) {
            case 1:
                addStudent(head);
                break;
            case 2:
                displayList(head);
                break;
            case 3:
                countParticipants(head);
                break;
            case 4:
                sortList(head);
                break;
            case 5:
                reverseList(head);
                break;
            case 6:
                addAtPosition(head);
                break;
            case 7:
                deleteAtPosition(head);
                break;
            case 8:
                freeList(head);
                printf("All student records deleted. Exiting program...\n");
                exit(0);
            default:
                printf("Invalid choice! Please select between 1 and 8.\n");
        }
    }

    return 0;
}
/* ---------------- end of provided code ---------------- */

// Create the dummy header node: no student data, next = NULL. Return it.
Node* createHead(void) {
    Node* head = (Node*)malloc(sizeof(Node));
    if (head != NULL) {
        head->regNo = 0;
        head->name[0] = '\0';
        head->next = NULL;
    }
    return head;
}

// Function to allocate memory and create a new node
// (copy at most 49 characters of name; next must be NULL)
Node* createNode(int regNo, const char* name) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode != NULL) {
        newNode->regNo = regNo;
        strncpy(newNode->name, name, 49);
        newNode->name[49] = '\0';
        newNode->next = NULL;
    }
    return newNode;
}

// a) Add Students at the END of the list, one after another, while the user
//    enters 1. Students already in the list must be kept (new ones go after them).
// Message after adding each student:  "Student added successfully."
void addStudent(Node* head) {
    int regNo;
    char name[50];
    int ch = 1;

    Node* last = head;
    while (last->next != NULL) {
        last = last->next;
    }

    while (ch == 1) {
        PROMPT("Enter Registration Number: ");              // provided
        if (scanf("%d", &regNo) != 1) break;                // provided
        PROMPT("Enter Student Name: ");                     // provided
        scanf(" %49[^\n]", name);                           // provided: reads a name with spaces

        Node* newNode = createNode(regNo, name);
        if (newNode != NULL) {
            last->next = newNode;
            last = newNode;
            printf("Student added successfully.\n");
        }

        PROMPT("\n Enter 1 if you wish to add new node ");  // provided
        if (scanf("%d", &ch) != 1) ch = 0;                  // provided
    }
}

// b) Display the List (students only, never the header node)
// Empty list:  "No students registered."
void displayList(Node* head) {
    if (head == NULL || head->next == NULL) {
        printf("No students registered.\n");
        return;
    }
    printf("\n--- Registered Students ---\n");
    printf("%-15s %-30s\n", "Reg No", "Name");
    printf("--------------------------------------------\n");

    Node* curr = head->next;
    while (curr != NULL) {
        printf("%-15d %-30s\n", curr->regNo, curr->name);
        curr = curr->next;
    }
}

// c) Count Total Participants (do not count the header node)
// Message:  "Total registered students: %d"
void countParticipants(Node* head) {
    int count = 0;
    Node* curr = (head != NULL) ? head->next : NULL;
    while (curr != NULL) {
        count++;
        curr = curr->next;
    }
    printf("Total registered students: %d\n", count);
}

// d) Sort List in Ascending Order by Registration Number
// (swapping data or relinking nodes are both fine; the header node stays in
//  front; students with equal Registration Numbers keep their original order)
void sortList(Node* head) {
    if (head == NULL || head->next == NULL || head->next->next == NULL) {
        printf("List sorted successfully (or already contains 0 or 1 item).\n");
        return;
    }

    int swapped;
    Node* ptr1;
    Node* lptr = NULL;

    do {
        swapped = 0;
        ptr1 = head->next;

        while (ptr1->next != lptr) {
            if (ptr1->regNo > ptr1->next->regNo) {
                // Swap regNo
                int tempReg = ptr1->regNo;
                ptr1->regNo = ptr1->next->regNo;
                ptr1->next->regNo = tempReg;

                // Swap name
                char tempName[50];
                strcpy(tempName, ptr1->name);
                strcpy(ptr1->name, ptr1->next->name);
                strcpy(ptr1->next->name, tempName);

                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);

    printf("Students are sorted in ascending order of Registration Number.\n");
}

// e) Reverse the List iteratively (reverse the students; the header node
//    stays in front and must point to the new first student)
void reverseList(Node* head) {
    if (head == NULL || head->next == NULL) {
        printf("No students registered to reverse.\n");
        return;
    }

    Node* prev = NULL;
    Node* curr = head->next;
    Node* next = NULL;

    while (curr != NULL) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    head->next = prev;
    printf("Student records reversed successfully.\n");
}

// f) Add a Student at a given Position (1 = first, count+1 = end)
void addAtPosition(Node* head) {
    int pos, regNo;
    char name[50];

    PROMPT("Enter Position: ");                 // provided
    scanf("%d", &pos);                          // provided
    PROMPT("Enter Registration Number: ");      // provided
    scanf("%d", &regNo);                        // provided
    PROMPT("Enter Student Name: ");             // provided
    scanf(" %49[^\n]", name);                   // provided: reads a name with spaces

    int count = 0;
    Node* curr = (head != NULL) ? head->next : NULL;
    while (curr != NULL) {
        count++;
        curr = curr->next;
    }

    if (pos < 1 || pos > count + 1) {
        printf("Invalid position!\n");
        return;
    }

    Node* prev = head;
    for (int i = 1; i < pos; i++) {
        prev = prev->next;
    }

    Node* newNode = createNode(regNo, name);
    if (newNode != NULL) {
        newNode->next = prev->next;
        prev->next = newNode;
        printf("Student added successfully.\n");
    }
}

// g) Delete the Student at a given Position (1 = first)
void deleteAtPosition(Node* head) {
    if (head == NULL || head->next == NULL) {
        printf("List is empty. No students to remove.\n");
        return;
    }

    int pos;
    PROMPT("Enter Position to delete: ");       // provided
    scanf("%d", &pos);                          // provided

    int count = 0;
    Node* curr = head->next;
    while (curr != NULL) {
        count++;
        curr = curr->next;
    }

    if (pos < 1 || pos > count) {
        printf("Invalid position!\n");
        return;
    }

    Node* prev = head;
    for (int i = 1; i < pos; i++) {
        prev = prev->next;
    }

    Node* toDelete = prev->next;
    prev->next = toDelete->next;
    free(toDelete);

    printf("Student record deleted successfully.\n");
}

// Free all memory in the list: every student AND the header node
void freeList(Node* head) {
    Node* curr = head;
    while (curr != NULL) {
        Node* temp = curr;
        curr = curr->next;
        free(temp);
    }
}
