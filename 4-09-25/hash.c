#include <stdio.h>
#include <stdlib.h>
#define TABLE_SIZE 10 
typedef struct Node {
    int key;
    struct Node* next;
} Node;
Node* hashTable[TABLE_SIZE];
int hashFunction(int key) {
    return key % TABLE_SIZE;
}
void insert(int key) {
    int index = hashFunction(key);
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation failed\n");
        return;
    }
    newNode->key = key;
    newNode->next = hashTable[index];
    hashTable[index] = newNode;
    printf("Inserted key %d\n", key);
}
Node* search(int key) {
    int index = hashFunction(key);
    Node* current = hashTable[index];
    while (current) {
        if (current->key == key)
            return current;
        current = current->next;
    }
    return NULL;
}
void deleteKey(int key) {
    int index = hashFunction(key);
    Node* current = hashTable[index];
    Node* prev = NULL;
    while (current) {
        if (current->key == key) {
            if (prev == NULL) {
                hashTable[index] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            printf("Key %d deleted\n", key);
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Key %d not found\n", key);
}
void display() {
    printf("\nHash Table:\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("[%d]: ", i);
        Node* current = hashTable[i];
        if (!current) {
            printf("NULL");
        }
        while (current) {
            printf("%d -> ", current->key);
            current = current->next;
        }
        printf("NULL\n");
    }
    printf("\n");
}
int main() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = NULL;
    }
    int choice, key;
 printf("Choose operation:\n");
        printf("1. Insert\n2. Search\n3. Delete\n4. Display\n5. Exit\n");
    while (1) {
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                insert(key);
                break;
            case 2:
                printf("Enter key to search: ");
                scanf("%d", &key);
                if (search(key))
                    printf("Key %d found in the hash table\n", key);
                else
                    printf("Key %d not found\n", key);
                break;
            case 3:
                printf("Enter key to delete: ");
                scanf("%d", &key);
                deleteKey(key);
                break;
            case 4:
                display();
                break;

            case 5:
                printf("Exiting...\n");
				    for (int i = 0; i < TABLE_SIZE; i++) {
                    Node* current = hashTable[i];
                    while (current) {
                        Node* temp = current;
                        current = current->next;
                        free(temp);
                    }
                }
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}
