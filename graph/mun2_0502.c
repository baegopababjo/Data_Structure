#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
 
typedef struct edge {
    int num1, num2, m1, m2;
    struct edge* link1, * link2;
}edge;
 
edge* head[20];
edge* adjacenyList[20];
 
void insert(int i, int first, int second) {
    //초기 값 저장
    adjacenyList[i]->num1 = first;
    adjacenyList[i]->num2 = second;
    adjacenyList[i]->m1 = 0;
    adjacenyList[i]->m2 = 0;
    //처음이면 바로 나가기
    if (i == 0) {
        return;
    }
    //처음이 아니라면 맨 위부터 값이 있는지 searching
    for (int j = i - 1; j >= 0; j--) {
        //첫 번째 값이 한 단계 adjacenyList에 num1 또는 num2에 있고 해당 adjacencyList의 첫번째 값이 사용된 적이 없다면(m1==0)
        if ((first == adjacenyList[j]->num1 || first == adjacenyList[j]->num2) && adjacenyList[i]->m1 == 0) {
            adjacenyList[i]->link1 = adjacenyList[j]; //첫 번째 숫자니까 link1을 연결
            adjacenyList[i]->m1 = 1; // 해당 숫자를 사용했다는 의미로 m1을 1로 변경
        }
        //같은 방법
        if ((second == adjacenyList[j]->num2 || second == adjacenyList[j]->num1) && adjacenyList[i]->m2 == 0) {
            adjacenyList[i]->link2 = adjacenyList[j];
            adjacenyList[i]->m2 = 1;
        }
    }
}
 
int main() {
    FILE* file = fopen("in2.txt", "rt");
    int vertexs = 0, edges = 0, vertex1 = 0, vertex2 = 0;
    if (file == NULL) {
        printf("파일 열기 실패!\n");
        return 0;
    }
    fscanf(file, "%d ", &vertexs);
    fscanf(file, "%d ", &edges);
 
    //vertexs 크기만큼 만들어주기
    for (int i = 0; i < vertexs; i++) {
        head[i] = (edge*)malloc(sizeof(edge) * vertexs);
        head[i]->link1 = NULL;
        head[i]->link2 = NULL;
    }
    //edges 크기만큼 만들어주기
    for (int i = 0; i < edges; i++) {
        adjacenyList[i] = (edge*)malloc(sizeof(edge) * edges);
        adjacenyList[i]->link1 = NULL;
        adjacenyList[i]->link2 = NULL;
    }
    
    //edges크기만큼 입력받고 insert시키기
    for (int i = 0; i < edges; i++) {
        fscanf(file, "%d %d ", &vertex1, &vertex2);
        insert(i, vertex1, vertex2);
    }
 
    //head[i]에서 i가 adjacencyList의 값과 같은지 파악후 같으면 연결(높은 adjacencyList 부터)
    for (int i = 0; i < vertexs; i++) {
        for (int j = edges - 1; j >= 0; j--) {
            if (i == adjacenyList[j]->num1 || i == adjacenyList[j]->num2) {
                head[i] = adjacenyList[j];
                break;
            }
        }
    }

    //출력
    for (int i = 0; i < vertexs; i++) {
        edge* cur = head[i];
        printf("Vertex %d:   ", i);
        while (cur != NULL) {
            printf("(%d, %d)", cur->num1, cur->num2);
            if (i == cur->num1) {
                cur = cur->link1;
            }
            else if (i == cur->num2) {
                cur = cur->link2;
            }
        }
        printf("\n");
    }
    fclose(file);
    return 0;
}