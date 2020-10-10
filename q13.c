#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int val;
  int weight;
  struct node* next;
} Node;

typedef struct vertex {
  int vertice;
  int weight;
} Vertex;

Node* createNode(int val, int weight) {
  Node* new_node = (Node*)malloc(sizeof(Node));
  new_node->next = NULL;
  new_node->val = val;
  new_node->weight = weight;
  return new_node;
}

void insert(Node* arr[], int x, int y, int weight) {
  if (arr[x] == NULL) {
    arr[x] = createNode(y, weight);
    return;
  }
  Node* top = arr[x];
  Node* to_insert = createNode(y, weight);
  to_insert->next = top;
  arr[x] = to_insert;
  return;
}

void PercolateDown(Vertex* arr[], int indices[], int index, int n) {
  int min = index;
  int l = (index * 2) + 1;
  int r = l + 1;

  if (l < n && arr[min]->weight > arr[l]->weight) {
    min = l;
  }

  if (r < n && arr[min]->weight > arr[r]->weight) {
    min = r;
  }

  if (min != index) {
    // Swap nodes
    Vertex* temp = arr[min];
    arr[min] = arr[index];
    arr[index] = temp;

    // update the index
    indices[arr[min]->vertice] = min;
    indices[arr[index]->vertice] = index;

    // Continue heapify for their descendents
    PercolateDown(arr, indices, min, n);
  }
}

void PercolateUp(Vertex* arr[], int indices[], int index, int n) {
  int par = (n - 1) / 2;

  if (index > 0) {
    if (arr[index]->weight > arr[par]->weight) {
      // Swap the array elements
      Vertex* temp = arr[index];
      arr[index] = arr[par];
      arr[par] = temp;

      // Change their index
      indices[arr[par]->vertice] = par;
      indices[arr[index]->vertice] = index;

      // Percolate up for further changes
      PercolateUp(arr, indices, par, n);
    }
  }
}

void decreaseKey(Vertex* arr[], int indices[], int vertex, int newWeight,
                 int n) {
  int currIndex = indices[vertex];
  arr[currIndex]->weight = newWeight;
  PercolateUp(arr, indices, currIndex, n);
}

Vertex* minKey(Vertex* arr[], int indices[], int n) {
  Vertex* temp = arr[0];
  arr[0] = arr[n - 1];
  arr[n - 1] = temp;

  indices[arr[0]->vertice] = 0;
  indices[arr[n - 1]->vertice] = n - 1;

  PercolateDown(arr, indices, 0, n - 1);

  return temp;
}

int getKey(Vertex* arr[], int indices[], int vertex) {
  int index = indices[vertex];
  return arr[index]->weight;
}

void input() {
  int n, m;
  printf("Number of nodes - ");
  scanf("%d", &n);
  printf("Number of edges - ");
  scanf("%d", &m);
  printf("\n");
  Node* arr[n];
  short visited[n];
  for (int i = 0; i <= n - 1; i++) {
    arr[i] = createNode(i, 0);
    visited[i] = 0;
  }
  printf("Enter the pairs: u v weight (Format u,v ==> (0, n-1))\n\n");
  int x, y, w;
  for (int i = 0; i < m; i++) {
    printf("Enter the pairs: ");
    scanf("%d %d %d", &x, &y, &w);
    insert(arr, x, y, w);
    insert(arr, y, x, w);
  }

  // Create an array of n vertices initialized to infy
  Vertex* minHeap[n];
  int indices[n];
  for (int i = 0; i < n; i++) {
    minHeap[i] = (Vertex*)malloc(sizeof(Vertex));
    indices[i] = i;
    minHeap[i]->vertice = i;
    minHeap[i]->weight = 1000;
  }

  // Set the first vertice to 0
  minHeap[0]->weight = 0;

  int vertex = 0;
  int currKey = 0;

  for (int i = 0; i < n; i++) {
    visited[vertex] = 1;

    Node* currentNeighbour = arr[vertex];
    while (currentNeighbour) {
      if (!visited[currentNeighbour->val]) {
        int getKeyNeighbour = getKey(minHeap, indices, currentNeighbour->val);
        if (currentNeighbour->weight + currKey < getKeyNeighbour) {
          decreaseKey(minHeap, indices, currentNeighbour->val,
                      currentNeighbour->weight + currKey, n - i);
        }
      }
      currentNeighbour = currentNeighbour->next;
    }

    Vertex* min = minKey(minHeap, indices, n - i);

    vertex = min->vertice;
    currKey = min->weight;
  }
  for (int i = 0; i < n; i++) {
    printf("%d --> %d\n", i, getKey(minHeap, indices, i));
  }
}

int main() { input(); }
