#include <bits/stdc++.h>
using namespace std;
const int N = 11;
const int id[N][N] ={
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	{0, 1, 1, 1, 2, 2, 2, 3, 3, 3};
	{0, 1, 1, 1, 2, 2, 2, 3, 3, 3};
	{0, 1, 1, 1, 2, 2, 2, 3, 3, 3};
	{0, 4, 4, 4, 5, 5, 5, 6, 6, 6};
	{0, 4, 4, 4, 5, 5, 5, 6, 6, 6};
	{0, 4, 4, 4, 5, 5, 5, 6, 6, 6};
	{0, 7, 7, 7, 8, 8, 8, 9, 9, 9};
	{0, 7, 7, 7, 8, 8, 8, 9, 9, 9};
	{0, 7, 7, 7, 8, 8, 8, 9, 9, 9};
}

struct Blank{
	int x, y;
} arr[N*N];
int A;

int row[N][N], col[N][N], area[N][N];
int g[N][N];

void putNum(int x, int y, int k){
	g[x][y] = k;
	row[x][k] = col[y][k] = area[id[x][y]][k] = true;
}

void dfs(int dep){
	if (dep == A+1){
		print(); // ans = max(ans, get_score());
		return;
	}

	for (int num = 1; num <= 9; num++){
		int x = arr[dep].x;
		int y = arr[dep].y;
		if (canotPut(x, y, num)) continue;
		putNum(x, y, num);
		dfs(dep+1);
		removeNum(x, y, num);
	}
}

int main(){
	A = 0;
	for (int i = 1; i <= 9; i++){
		for (int j = 1; j <= 9; j++){
			scanf("%d", &g[i][j]);
			if (g[i][j] == 0){
				arr[++A] = Blank{i, j};
			} else{
				putNum(i, j, g[i][j]);
			}
		}
	}
	dfs(1);
	return 0;
}