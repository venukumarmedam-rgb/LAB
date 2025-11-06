#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
 
#define MAX_VERTICES 100
#define INF INT_MAX
 
typedef struct {
   int vertex;
   int dist;
} HeapNode;
 
typedef struct {
   int size;
   int capacity;
   int *pos;
   HeapNode **array;
} MinHeap;
 
HeapNode* newHeapNode(int v, int dist) {
   HeapNode* node = (HeapNode*)malloc(sizeof(HeapNode));
   node->vertex = v;
   node->dist = dist;
   return node;
}
 
MinHeap* createMinHeap(int capacity) {
   MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
   minHeap->pos = (int*)malloc(capacity * sizeof(int));
   minHeap->size = 0;
   minHeap->capacity = capacity;
   minHeap->array = (HeapNode**)malloc(capacity * sizeof(HeapNode*));
   return minHeap;
}
 
void swapHeapNode(HeapNode** a, HeapNode** b) {
   HeapNode* temp = *a;
   *a = *b;
   *b = temp;
}
 
void minHeapify(MinHeap* minHeap, int idx) {
   int smallest = idx;
   int left = 2 * idx + 1;
   int right = 2 * idx + 2;
 
   if (left < minHeap->size &&
       minHeap->array[left]->dist < minHeap->array[smallest]->dist)
       smallest = left;
 
   if (right < minHeap->size &&
       minHeap->array[right]->dist < minHeap->array[smallest]->dist)
       smallest = right;
 
   if (smallest != idx) {
       HeapNode *smallestNode = minHeap->array[smallest];
       HeapNode *idxNode = minHeap->array[idx];
       minHeap->pos[smallestNode->vertex] = idx;
       minHeap->pos[idxNode->vertex] = smallest;
       swapHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
       minHeapify(minHeap, smallest);
   }
}
 
int isEmpty(MinHeap* minHeap) {
   return minHeap->size == 0;
}
 
void build_heap(MinHeap* minHeap) {
   int n = minHeap->size;
   for (int i = (n - 1) / 2; i >= 0; i--)
       minHeapify(minHeap, i);
}
 
HeapNode* extract_min(MinHeap* minHeap) {
   if (isEmpty(minHeap))
       return NULL;
 
   HeapNode* root = minHeap->array[0];
   HeapNode* lastNode = minHeap->array[minHeap->size - 1];
   minHeap->array[0] = lastNode;
   minHeap->pos[root->vertex] = minHeap->size - 1;
   minHeap->pos[lastNode->vertex] = 0;
   minHeap->size--;
   minHeapify(minHeap, 0);
   return root;
}
 
void decrease_key(MinHeap* minHeap, int v, int dist) {
   int i = minHeap->pos[v];
   minHeap->array[i]->dist = dist;
   while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist) {
       minHeap->pos[minHeap->array[i]->vertex] = (i - 1) / 2;
       minHeap->pos[minHeap->array[(i - 1) / 2]->vertex] = i;
       swapHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);
       i = (i - 1) / 2;
   }
}
 
int isInMinHeap(MinHeap *minHeap, int v) {
   if (minHeap->pos[v] < minHeap->size)
       return 1;
   return 0;
}
 
void dijkstra(int graph[MAX_VERTICES][MAX_VERTICES], int V, int src) {
   int dist[MAX_VERTICES];
   MinHeap* minHeap = createMinHeap(V);
 
   for (int v = 0; v < V; v++) {
       dist[v] = INF;
       minHeap->array[v] = newHeapNode(v, dist[v]);
       minHeap->pos[v] = v;
   }
 
   dist[src] = 0;
   minHeap->array[src]->dist = 0;
   minHeap->size = V;
   build_heap(minHeap);
 
   while (!isEmpty(minHeap)) {
       HeapNode* minNode = extract_min(minHeap);
       int u = minNode->vertex;
 
       for (int v = 0; v < V; v++) {
           if (graph[u][v] && isInMinHeap(minHeap, v) && dist[u] != INF &&
               graph[u][v] + dist[u] < dist[v]) {
               dist[v] = dist[u] + graph[u][v];
               decrease_key(minHeap, v, dist[v]);
           }
       }
   }
 
   printf("Vertex\tDistance from Source\n");
   for (int i = 0; i < V; i++)
       printf("%d\t\t%d\n", i, dist[i]);
}
 
int main() {
   int V = 5;
   int graph[MAX_VERTICES][MAX_VERTICES] = {
       {0, 9, 0, 0, 10},
       {9, 0, 6, 5, 0},
       {0, 6, 0, 2, 0},
       {0, 5, 2, 0, 1},
       {10, 0, 0, 1, 0}
   };
 
   dijkstra(graph, V, 0);
   return 0;
}
 
