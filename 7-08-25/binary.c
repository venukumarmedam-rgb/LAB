#include <stdio.h>
int main() {
    int n, key, first, last, mid;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    int Arr[n];
    printf("Enter %d sorted elements: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &Arr[i]);
    }
    printf("Enter the element to search: ");
    scanf("%d", &key);
    first = 0;
    last = n - 1;
    int flag = 0; 
    while (first <= last) {
        mid = (first + last) / 2;

        if (Arr[mid] == key) {
            printf("Element found at position %d\n", mid + 1); 
            flag = 1;
            break;
        }
        else if (Arr[mid] < key) {
            first = mid + 1; 
        }
        else {
            last = mid - 1; 
        }
    }

    if (!flag) {
        printf("Element not found\n");
    }

    return 0;
}