#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS

typedef struct graph {
    int data;
    struct graph* next;
}graph;
 
graph *head[20];
int *visited;
 
void insert(int i, int data) {
    int a = 0;
    graph * new;
    new = (graph*)malloc(sizeof(struct graph));
 
    new->data = data;
    new->next = head[i]->next;
    head[i]->next = new;
}

void dfs(int index){
    graph* cur;
    visited[index] = 1;
    for(cur = head[index]->next; cur; cur = cur->next){
        if(!visited[cur->data]){
            dfs(cur->data);
        }
    }
}

void connect(int vertex){
    int count = 0;
    for(int i = 0; i <vertex; i++){
        if(!visited[i]){
            dfs(i);
            count ++;
        }
    }
    printf("%d\n",count);
}


int main() {
    FILE* file = fopen("in.txt", "rt");
    int** arr = NULL;
    int vertex = 0;

    if (file == NULL) {
        printf("파일 열기 실패!\n");
        return 0;
    }
 
    fscanf(file, "%d ", &vertex);

    //visited 배열 동적할당
    visited = (int *) malloc(sizeof(int)*vertex);
    for(int i = 0; i < vertex; i++) {
        visited[i] = 0;
    }

    //2차원 배열 동적할당
    arr = (int**)malloc(vertex * sizeof(int*));
    for (int i = 0; i < vertex; i++) {
        arr[i] = (int*)malloc(sizeof(int) * vertex);
    }

    for (int i = 0; i < vertex; i++) {
        head[i] = (graph*)malloc(sizeof(graph));
        head[i]->next = NULL;
    }
    //값 넣기
    for (int i = 0; i < vertex; i++) {
        arr[i][i] = 0;
        for (int j = i + 1; j < vertex; j++) {
            fscanf(file, "%d ", &arr[i][j]);
            arr[j][i] = arr[i][j];
        }
    }

    for (int i = 0; i < vertex; i++) {
        for (int j = 0; j < vertex; j++) {
            if (arr[i][j] == 1) {
                insert(i, j);
            }
        }
    }
    connect(vertex);
    fclose(file);
    return 0;
}