#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

int64_t Multiply(const vector<pair<int,int>>& params,int size){
    auto **dp = new int64_t*[size];
    for(int  i =0; i < size;i++){
        dp[i] = new int64_t[size];
    }
    for(int i = 0;i < size;i++){
        for(int  j = 0;j < size;j++){
            dp[i][j] = 100000000000;
        }
    }
    for(int i = 0;i < size;i++){
        dp[i][i] = 0;
    }
    for (int i = size-1; i >= 0 ; i--) {
        for (int j = i+1; j < size ; j++) {
            for (int k = i; k < j; k++) {
                dp[i][j] = min(dp[i][j],dp[i][k] + dp[k + 1][j] + params[i].first * params[k].second * params[j].second);
            }
        }
    }
    return dp[0][size-1];
}

int main(){
    ifstream in("input.txt");
    int s = 0;
    in >> s;
    vector<pair<int,int>> params(s);
    for(auto& p : params){
        in >> p.first >> p.second;
    }
    ofstream out("output.txt");
    out << Multiply(params,s);
    return 0;
}