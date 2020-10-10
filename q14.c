#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int val;
    struct node* next;
}Node;

Node* createNode(int val){
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->next = NULL;
    new_node->val = val;
    return new_node;
}

void insert(Node* arr[], int x, int y){
    if(arr[x] == NULL){
        arr[x] = createNode(y);
        return;
    }
    Node* top = arr[x];
    Node* to_insert = createNode(y);
    to_insert->next = top;
    arr[x] = to_insert;
    return;
}

void DFS(Node* arr[], int visited[], int x){
    Node* curr = arr[x];
    visited[x] = 0;
    printf("%d ", x);
    while(curr){
        int val = curr->val;
        if(visited[val] == -1){
            DFS(arr, visited,val);
        }
        curr = curr->next;
    }
}

void exec_DFS(Node* arr[], int start, int n){

    if(start <= 0 || start > n){
        printf("Invalid Input!!!\n");
        return;
    }

    int visited[n+1];
    for(int i = 0; i < n+1; i++){
        visited[i] = -1;
    }
    printf("\nDFS of the graph is - ");
    DFS(arr, visited, start);
    printf("\n\n");
}

void BFS(Node* arr[], int x, int n){

    if(x <= 0 || x > n){
        printf("Invalid Input!!!\n");
        return;
    }

    int visited[n+1];
    for(int i = 0; i < n+1; i++){
        visited[i] = -1;
    }
    if(!arr[x]){
        printf("\nBFS of the graph is - %d", x);
        return;
    }
    Node* que = createNode(x);
    Node* endQ = que;
    printf("\nBFS of the graph is - ");
    visited[x] = 0;
    while(que){
        int val = que->val;
        printf("%d ", val);
        Node* currVal = arr[val];
        while(currVal){
            int y = currVal->val;
            if(visited[y] == -1){
                visited[y] = 0;
                Node* ins = createNode(y);
                endQ->next = ins;
                endQ = ins;
            }
            currVal = currVal->next;
        }
        Node* toFree =  que;
        que = que->next;
        free(toFree);
    }
    printf("\n\n");
}

void input(){
    int n, m;
    printf("Number of nodes - ");
    scanf("%d", &n);
    printf("Number of edges - ");
    scanf("%d", &m);
    printf("\n");
    Node* arr[n+1];
    for(int i = 1;  i <= n; i++){
        arr[i] = createNode(i);
    }
    printf("Enter the pairs: x y (Format)\n\n");
    for(int i = 0; i < m; i++){
        int x, y;
        printf("Enter the pairs: ");
        scanf("%d %d", &x, &y);
        insert(arr, x, y);
        insert(arr, y, x);
    }
    int choice = 0;
    // printf("%d %d", arr[1]->val, arr[1]->next->val);
    printf("\n1 - DFS; 2 - BFS; 0 - exit - ");
    scanf("%d", &choice);
    while(choice){
        int x;
        printf("\nEnter the root to start - ");
        scanf("%d", &x);
        if(choice == 1){
            exec_DFS(arr, x, n);
        }
        else{
            BFS(arr, x, n);
        }
        printf("\n1 - DFS; 2 - BFS; 0 - exit - ");
        scanf("%d", &choice);
    }
}

int main(){
    input();
}
