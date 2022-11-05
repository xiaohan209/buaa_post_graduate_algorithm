#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <string>

using namespace std;

#define EDGE_NUM 8

int edge[EDGE_NUM][EDGE_NUM] = {
        {0,14,25,27,10,11,24,16},
        {14,0,18,15,27,28,16,14},
        {25,18,0,19,14,19,16,10},
        {27,15,19,0,22,23,15,14},
        {10,27,14,22,0,14,13,20},
        {11,28,19,23,14,0,15,18},
        {24,16,16,15,13,15,0,27},
        {16,14,10,14,20,18,27,0},
};
int weight[EDGE_NUM][EDGE_NUM] = {{0}};
int choose[EDGE_NUM][EDGE_NUM] = {{0}};


int triangle_weight(int start, int mid, int end) {
    return edge[start][mid] + edge[mid][end] + edge[end][start];
}

int print_plan(int scale, int start) {
    if (scale == 1) {
        return 0;
    }
    int point = choose[scale][start];
    int end = start + scale;
    print_plan(point - start,start);
    print_plan(end - point,point);
    if (scale != EDGE_NUM - 1) {
        printf("edge[v%d,v%d]: weight is %d\n",start + 1, end + 1,edge[start][end]);
    }
    return 0;
}

int polygon() {
    printf("matrix of polygon edge weight is: \n");
    for (int i=0;i < (EDGE_NUM + 1) * 3;i++) {
        putchar('-');
    }
    putchar('\n');
    for (int i=0;i<EDGE_NUM;i++) {
        printf("| ");
        for (int j=0;j<EDGE_NUM;j++) {
            printf("%2d ",edge[i][j]);
        }
        printf("|\r\n");
    }
    for (int i=0;i < (EDGE_NUM + 1) * 3;i++) {
        putchar('-');
    }
    putchar('\n');
    for (int start = 0; start < EDGE_NUM - 1;start++) {
        weight[1][start] = 0;
    }
    for (int scale = 2; scale < EDGE_NUM; scale++) {
        for (int start = 0; start < EDGE_NUM - scale; start++) {
            // 选取(start,start+scale)的所有点
            for (int k = start+1;k < start + scale;k++) {
                int tri = triangle_weight(start, k, start + scale);
                int left = weight[k - start][start];
                int right = weight[start + scale - k][k];
                int sum = tri + left + right;
                if (weight[scale][start] == 0 || sum < weight[scale][start]) {
                    // 记录权值最小的
                    weight[scale][start] = sum;
                    choose[scale][start] = k;
                }
            }
        }
    }
    printf("Final polygon weight is : %d\n", weight[EDGE_NUM-1][0]);
    for (int i=0;i < (EDGE_NUM + 1) * 3;i++) {
        putchar('-');
    }
    putchar('\n');
    printf("Choose edge set :\n");
    print_plan(EDGE_NUM - 1, 0);
    for (int i=0;i < (EDGE_NUM + 1) * 3;i++) {
        putchar('-');
    }
    putchar('\n');
    return 0;
}

int main() {
    polygon();
    return 0;
}
