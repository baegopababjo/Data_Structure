#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
 
typedef struct graph {
    int data;
    struct graph* next;
}graph;
 
graph *head[20];
 
void insert(int i, int data) {
    graph* cur, * new;
    new = (graph*)malloc(sizeof(struct graph));
 
    new->data = data;
    new->next = NULL;
    cur = head[i];
    while (cur->next!= NULL) {
        cur = cur->next;
    }
    cur->next = new;
}
 
int main() {
    FILE* file = fopen("in1.txt", "rt");
    int** arr = NULL;
    int vertex = 0;
    if (file == NULL) {
        printf("파일 열기 실패!\n");
        return 0;
    }
 
    fscanf(file, "%d ", &vertex);
 
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
                insert(i, j + 1);
            }
        }
    }
    for (int i = 0; i < vertex; i++) {
        graph* cur = head[i]->next;
        printf("Vertex %d: ", i + 1);
        while (cur->next != NULL) {
            printf("%d ", cur->data);
            cur = cur->next;
        }
        printf("%d ", cur->data);
        printf("\n");
    }
 
    fclose(file);
    return 0;
}