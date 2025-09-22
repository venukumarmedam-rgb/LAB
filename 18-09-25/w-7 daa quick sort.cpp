#include <stdio.h>
struct Item {
   int price;
   int weight;
   double ratio;
};
void swap(struct Item *a, struct Item *b) {
   struct Item temp = *a;
   *a = *b;
   *b = temp;
}
int partitionRatio(struct Item arr[], int low, int high) {
   double pivot = arr[high].ratio;
   int i = low - 1;
   for (int j = low; j < high; j++) {
       if (arr[j].ratio > pivot) {
           i++;
           swap(&arr[i], &arr[j]);
       }
   }
   swap(&arr[i + 1], &arr[high]);
   return i + 1;
}
void quickSortRatio(struct Item arr[], int low, int high) {
   if (low < high) {
       int pi = partitionRatio(arr, low, high);
       quickSortRatio(arr, low, pi - 1);
       quickSortRatio(arr, pi + 1, high);
   }
}
int partitionPrice(struct Item arr[], int low, int high) {
   int pivot = arr[high].price;
   int i = low - 1;
   for (int j = low; j < high; j++) {
       if (arr[j].price > pivot) {
           i++;
           swap(&arr[i], &arr[j]);
       }
   }
   swap(&arr[i + 1], &arr[high]);
   return i + 1;
}
void quickSortPrice(struct Item arr[], int low, int high) {
   if (low < high) {
       int pi = partitionPrice(arr, low, high);
       quickSortPrice(arr, low, pi - 1);
       quickSortPrice(arr, pi + 1, high);
   }
}
int partitionWeight(struct Item arr[], int low, int high) {
   int pivot = arr[high].weight;
   int i = low - 1;
   for (int j = low; j < high; j++) {
       if (arr[j].weight < pivot) {
           i++;
           swap(&arr[i], &arr[j]);
       }
   }
   swap(&arr[i + 1], &arr[high]);
   return i + 1;
}
void quickSortWeight(struct Item arr[], int low, int high) {
   if (low < high) {
       int pi = partitionWeight(arr, low, high);
       quickSortWeight(arr, low, pi - 1);
       quickSortWeight(arr, pi + 1, high);
   }
}
struct Result {
   double totalPrice;
   double totalItems;
};
struct Result fractionalKnapsackCalc(int W, struct Item items[], int n) {
   double totalPrice = 0.0;
   double totalItems = 0.0;
   
   for (int i = 0; i < n; i++) {
       if (W == 0) break;
 
       if (items[i].weight <= W) {
           W -= items[i].weight;
           totalPrice += items[i].price;
           totalItems += 1.0;
       } else {
           double fraction = (double)W / items[i].weight;
           totalPrice += items[i].price * fraction;
           totalItems += fraction;
           W = 0;
       }
   }
   struct Result res = {totalPrice, totalItems};
   return res;
}
int main() {
   int val[] = {50,60,70};
   int wt[] = {10, 20, 30};
   int W = 40;
   int n = sizeof(val) / sizeof(val[0]);
   struct Item itemsRatio[n], itemsPrice[n], itemsWeight[n];
   for (int i = 0; i < n; i++) {
       itemsRatio[i].price = val[i];
       itemsRatio[i].weight = wt[i];
       itemsRatio[i].ratio = (double)val[i] / wt[i];
       itemsPrice[i].price = val[i];
       itemsPrice[i].weight = wt[i];
       itemsPrice[i].ratio = 0;
       itemsWeight[i].price = val[i];
       itemsWeight[i].weight = wt[i];
       itemsWeight[i].ratio = 0;
   }
   quickSortRatio(itemsRatio, 0, n - 1);
   struct Result resRatio = fractionalKnapsackCalc(W, itemsRatio, n);
   quickSortPrice(itemsPrice, 0, n - 1);
   struct Result resPrice = fractionalKnapsackCalc(W, itemsPrice, n);
   quickSortWeight(itemsWeight, 0, n - 1);
   struct Result resWeight = fractionalKnapsackCalc(W, itemsWeight, n);
   struct Result best = resRatio;
   char *bestApproach = "Value to Weight Ratio";
   if (resWeight.totalPrice > best.totalPrice) {
       best = resWeight;
       bestApproach = "Lightest Weight Items";
   }
   if (resPrice.totalPrice > best.totalPrice) {
       best = resPrice;
       bestApproach = "Items with High Price";
   }
   printf("Best approach: %s\n", bestApproach);
   printf("Total price: %.2f\n", best.totalPrice);
   return 0;

}
