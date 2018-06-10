////    最大可计算20个节点数的最小生成树
///     rank[]:每个元素。若节点数小于10，则均为两位数。其中各位代表
/**
 * 定义所有边的边集E
 * 定义所有节点的点集V（目前为空）
 * 定义一个最小生成树的边集Em（目前此集合为空）
 * 首先任选一个节点加入到V中
 * 对E中所有边按边权排序
 * 每一次循环由低到高搜寻
 * 若有边的两端，有一端属于V
 * 另一端不在V中，则将另一端点加入到V中
 * 将此边加入到E中
 * 并在Em中移除此边
 * 直到将所有节点全部纳入V中
 * */

#include <stdio.h>
#include <stdlib.h>

#define SIZE 7
#define EXIST 1
#define UNEXIST 0
#define P_ADD 3
#define A_ADD 4
#define E_UNEXIST 7
#define E_EXIST 11

typedef struct edge {
    int prV;
    int W;
    int afV;
} Edge;

void sortEm(Edge *Em, int size);

int getEm(int matrix[][SIZE], Edge Em[]);

int isExist(Edge E, int V[]);

void del(int index, Edge Em[],int size);

void main(void) {

    int i, j, k;

    int Matrix[SIZE][SIZE]={
            0,1,0,0,0,10,3,
            1,0,3,0,0,0,4,
            0,3,0,2,0,0,2,
            0,0,2,0,0,0,3,
            0,0,0,0,0,6,6,
            10,0,0,0,6,0,7,
            3,4,2,3,6,7,0,
    };
    int V[SIZE]={-1,-1,-1,-1,-1,-1,-1};
    Edge E[SIZE];
    Edge Em[(SIZE - 1) * (SIZE - 1) / 2-2];

//    for (i = 0; i < SIZE; i++) {
//        printf("Input %d line\n", i);
//        for (j = 0; j < SIZE; j++) {
//            scanf("%d", &Matrix[i][j]);
//        }
//    }
    printf("Waiting...\n");
    int size = getEm(Matrix, Em);
    printf("size:%d\n",size);
    sortEm(Em, size);
    k=0;
    V[0] = Em[0].prV;
    V[1] = Em[0].afV;
    E[k]=Em[0];
    k++;
    del(0,Em,size);
    for (i = 1; i<size; i++) {
        int tell=E_EXIST;
        for (j = 0; j < size; j++) {
            if (Em[j].W != 0) {
                int temp = isExist(Em[j], V);
                if (temp==A_ADD||temp== P_ADD) {
                    V[k+1]=(temp==A_ADD?Em[j].afV:Em[j].prV);
                    E[k] = Em[j];
                    k++;
                    del(j, Em,size);
                    tell=E_EXIST;
                    break;
                } else if(temp == E_UNEXIST)
                    tell=E_UNEXIST;
            }
        }
        if(tell==E_UNEXIST){
            E[k]=Em[i];
            V[k+1]=Em[i].prV;
            k++;
        }
        if(k==SIZE){
            break;
        }
    }
    E[SIZE-1].W=0;
    k=0;
    for (i = 0; i < SIZE; i++) {
            k += E[i].W;
        printf("E[%d]= %d, %d,%d\t",i,E[i].prV,E[i].W,E[i].afV);
        printf("V[%d] = %d\n",i,V[i]);
    }
    printf("sum of weight:%d", k);
}

void sortEm(Edge Em[], int size) {
    int min = 0;
    Edge temp;
    int i, j;
    for (i = 0; i < size; ++i) {
        min = i;
        for (j = i + 1; j < size; j++) {
            if (Em[min].W > Em[j].W) {
                min = j;
            }
        }
        temp = Em[i];
        Em[i] = Em[min];
        Em[min] = temp;
        printf("getE[%d].w:%d\n",i,Em[i].W);
    }
}

int getEm(int matrix[][SIZE], Edge Em[]) {
    int i, j, k;
    for (i = 0, k = 0; i < SIZE - 1; ++i) {
        for (j = i + 1; j < SIZE; j++) {
            if (matrix[i][j] != 0) {
                Em[k].prV = i;
                Em[k].W = matrix[i][j];
                Em[k].afV = j;
                k++;
            }
        }
    }
    return k;
}

int isExist(Edge E, int V[]) {
    int i;
    int a = UNEXIST;
    int p = UNEXIST;
    for (i = 0; V[i]!=-1; ++i) {
        if (V[i] == E.prV) {
            p = EXIST;
        }
        if (V[i] == E.afV) {
            a = EXIST;
        }
    }
    if (a != p) {
        return a == UNEXIST ? A_ADD : P_ADD;
    } else if(a==UNEXIST&&p==UNEXIST){
        return E_UNEXIST;
    }
    return EXIST;
}

void del(int index, Edge Em[],int size) {
    Edge p=Em[index];
   int i;
    for (i = index; i < size-1; ++i) {
        Em[i] = Em[i + 1];
    }
    Em[size-1]= p;
    Em[size-1].W = 0;
}
