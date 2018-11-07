#include <bits/stdc++.h>
using namespace std;
const int N = 1e4 + 7;

struct Carpet{
    int a, b, g, k;

    void read(){
        scanf("%d%d%d%d", &a, &b, &g, &k);
    }

    int cover(int x, int y){
        return a<=x && x<=a+g && b<=y && y<=b+k;
    }
} carpets[N];

int main(){
    int n, x, y;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++){
        carpets[i].read();
    }
    scanf("%d%d", &x, &y);

    int ans = -1;
    for (int i = n; i >= 1; i--){
        if (carpets[i].cover(x, y)){
            ans = i;
            break;
        }
    }
    printf("%d\n", ans);
    return 0;
}

