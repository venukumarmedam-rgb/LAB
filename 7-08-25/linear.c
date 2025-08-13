#include <stdio.h>
int main() {
    int n, key, flag = 0;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    int Arr[n];
    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &Arr[i]);
    }
    printf("Enter the element to search: ");
    scanf("%d", &key);
    for (int i = 0; i < n; i++) {
        if (Arr[i] == key) {
            printf("Element found at position %d\n", i + 1);
            flag = 1;
            break; 
        }
    }
    if (!flag) {
        printf("Element not found\n");
    }
    return 0;
}
