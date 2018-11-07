#include<bits/stdc++.h>
using namespace std;
string str[20];
int use[20], length = 0, n;

bool cover(string str1, string str2, int len){
	for (int i = 0; i < len; i++){
		if (str1[str1.length()-len+i] != str2[i]) return false;
	}
	return true;
}

int canlink(string str1, string str2){
	for (int i = 1; i < min(str1.length(), str2.length()); i++){
		if (cover(str1, str2, i)) return i;
	}
	return 0;
}

void solve(string strnow, int lengthnow) {
    length = max(lengthnow, length);//更新最大长度
    
    for(int i = 0; i < n; i++) {
        if(use[i] >= 2) continue;//该字符串使用次数需要小于2
        int c = canlink(strnow, str[i]);//获取重叠长度
        if(c > 0) {//有重叠部分就开始dfs
            use[i]++;
            solve(str[i], lengthnow + str[i].length() - c);
            use[i]--;
        }
    }
}

main() {
    cin >> n;
    for(int i = 0; i <= n; i++) use[i] = 0, cin >> str[i];//str[n]为开始字符 
    solve(' '+str[n], 1);//有必要解释一下开始阶段。为了指定第一个字符，而且因为canlink需要重叠部分小于最短长度-1，所以要从前面添加一个无意义充长度的‘ ’。这样就强制了canlink函数比较最后一位。
    cout << length ;
}
