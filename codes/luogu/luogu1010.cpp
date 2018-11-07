#include <bits/stdc++.h>
using namespace std;

void print2(int n){
    vector <int> ans;
    for (int i = 15; i >= 0; i--){
        if ((1<<i) & n) {
            ans.push_back(i);
            //printf("---> push_back = %d\n", i);
        }
    }

    for (int i = 0; i < ans.size(); i++){
        printf("2");
        if (ans[i] == 1) printf("");
        else if (ans[i] == 0 || ans[i] == 2)printf("(%d)", ans[i]);
        else {
            printf("(");
            print2(ans[i]);
            printf(")");
        }

        if (i != ans.size()-1) printf("+");
    }
}

/*
1010 = 2^0 * 0 + 2^1 * 1 + 2^2*0 + 2^3 * 1
100100110  & 与 and
000100000
-----------
000100000 ==> n的第5位，二进制下是1
*/


int main(){
    freopen("in.txt", "r", stdin);
    int n;
    scanf("%d", &n);
    print2(n);
    puts("");
    return 0;
}
