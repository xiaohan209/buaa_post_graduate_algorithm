//
// Created by xiaohan209 on 2022/10/31.
//

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <string>

#define PROJECT_NUM 3
#define INVEST_NUM 8

using namespace std;

int invest() {
    int projectProfit[PROJECT_NUM][INVEST_NUM+1] = {
            {0,5,15,40,80,90,95,98,100},
            {0,5,15,40,60,70,73,74,75},
            {0,4,26,40,45,50,51,52,53},
    };
    int investProfit[PROJECT_NUM][INVEST_NUM+1] = {{0}};
    int investProject[PROJECT_NUM][INVEST_NUM+1] = {{0}};
    int remainProfit = 0;
    int remainInvest = 0;

    for (int i=0;i<PROJECT_NUM;i++) {
        for (int j=0;j<=INVEST_NUM;j++) {
            int max = -1;
            int nowInvest = 0;
            int nowProfit = 0;

            while (nowInvest <= j) {
                remainInvest = j - nowInvest;
                nowProfit = projectProfit[i][nowInvest];
                if (i == 0) {
                    remainProfit = 0;
                }
                else {
                    remainProfit = investProfit[i-1][remainInvest];
                }
                int profit = remainProfit + nowProfit;
                if (profit > max) {
                    max = profit;
                    investProject[i][j] = nowInvest;
                }
                nowInvest++;
            }
            investProfit[i][j] = max;
        }
    }
    for (int i=0;i<PROJECT_NUM;i++) {
        for (int j=0;j<=INVEST_NUM;j++) {
            cout << investProfit[i][j] << " ";
        }
        cout << endl;
    }
    cout << "-------------------------" << endl;
    int invest[PROJECT_NUM] = {0};
    int remain = INVEST_NUM;
    for (int i = PROJECT_NUM - 1;i >= 0;i--) {
        int cost = investProject[i][remain];
        remain -= cost;
        invest[i] = cost;
    }
    for (int i=0; i< PROJECT_NUM;i++) {
        cout << invest[i] << " ";
    }
    cout << endl;
    return 0;
}
