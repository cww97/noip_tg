/**
 * 国王游戏
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1003;
const int MAXN = 6003;
int B = 10;

struct bign{ // big number
    int len, s[MAXN];
    
    bign (){
        memset(s, 0, sizeof(s));
        len = 1;
    }
    bign (int num) { *this = num; }
    bign (const char *num) { *this = num; }

    bign operator = (const int num){
        char s[MAXN];
        sprintf(s, "%d", num);
        *this = s;
        return *this;
    }

    void clean(){
        while(len > 1 && !s[len-1]) len--;
    } 

    bign operator = (const char *num){
    	memset(s, 0, sizeof s);
    	len = strlen(num);
        for(int i = 0; i < len; i++) {
        	if (isdigit(num[len-i-1])) s[i] = num[len-i-1] - '0';
        	else s[i] = num[len-i-1] - 'A' + 10;
        }
        clean();
        return *this;
    }

    bign operator + (const bign &b) const{
        bign c;
        c.len = max(len, b.len);
        for (int i = 0; i < c.len; i++){
            c.s[i] += s[i] + b.s[i];
            c.s[i+1] += c.s[i] / B; // B default = 10
            c.s[i] %= B;
        }
        if (c.s[c.len]) c.len++;
        c.clean();
        return c;
    }
    
    bign operator += (const bign &b){
        *this = *this + b;
        return *this;
    }

    bign operator * (const bign &b) {//*
        bign c;
        c.len = len + b.len;
        for(int i = 0; i < len; i++)
            for(int j = 0; j < b.len; j++){
            	c.s[i+j] += s[i] * b.s[j];
            }
                
        for(int i = 0; i < c.len; i++){
        	c.s[i+1] += c.s[i]/10;
        	c.s[i] %= 10;
        }
            
        c.clean();
        return c;
    }
    bign operator *= (const bign &b){
        *this = *this * b;
        return *this;
    }
    bign operator - (const bign &b){
        bign c;
        c.len = 0;
        for(int i = 0, g = 0; i < len; i++){
            int x = s[i] - g;
            if(i < b.len) x -= b.s[i];
            if(x >= 0) g = 0;
            else{
                g = 1;
                x += 10;
            }
            c.s[c.len++] = x;
        }
        c.clean();
        return c;
    }
    bign operator -= (const bign &b){
        *this = *this - b;
        return *this;
    }
    bign operator / (const int &b){
    	int f = 0;
    	bign c;
    	for (int i = len-1; i >= 0; i--){
    		f = f *10 + s[i];
    		c.s[i] = f / b;
    		f %= b;
    	}
    	c.len = len;
    	c.clean();
    	return c;
    }
    bign operator / (const bign &b){
        bign c, f = 0;
        for(int i = len-1; i >= 0; i--){
        	
            f = f*10; // f = 0
            f.s[0] = s[i]; // f = 1
            while(f > b || f == b){
                
                f -= b;
                c.s[i]++;
            }
        }
        c.len = len;
        c.clean();
        return c;
    }
    bign operator /= (const bign &b){
        *this  = *this / b;
        return *this;
    }
    bign operator % (const bign &b){
        bign r = *this / b;
        r = *this - r*b;
        return r;
    }
    bign operator %= (const bign &b){
        *this = *this % b;
        return *this;
    }

    bool operator < (const bign &b){
        if(len != b.len) return len < b.len;
        for(int i = len-1; i >= 0; i--){
            if(s[i] != b.s[i]) return s[i] < b.s[i];
        }
        return false;
    }

    bool operator > (const bign &b){
        if(len != b.len) return len > b.len;
        for(int i = len-1; i >= 0; i--){
            if(s[i] != b.s[i]) return s[i] > b.s[i];
        }
        return false;
    }

    bool operator == (const bign &b){
        return !(*this > b) && !(*this < b);
    }

    string str() const{
        string res = "";  // result
        for (int i = 0; i < len; i++) {
        	if (s[i] < 10) res = char(s[i]+'0') + res;
        	else res = char(s[i] + 'A' - 10) + res;
        }
        return res;
    }
} a, b, c;

struct people{
    int l, r, mon;
    
    void scan(int i){
        scanf("%d %d", &l, &r);
        mon = r * l;
    }
    
    bool operator < (const people &b)const{
        if(mon != b.mon) return mon < b.mon;
        return r < b.r;
    }
}peo[N];

int main() {
    //freopen("in.txt", "r", stdin);
    int n;
    scanf("%d", &n);
    for(int i = 0; i <= n; i++){
        peo[i].scan(i);
    }
    
    sort(peo + 1, peo + 1+n);
    
    bign mone = peo[0].l, ans = 0;
    for(int i = 1; i <= n; i++){
    	//bign t = bign();
        bign tmp = (mone / peo[i].r);
    	if (tmp > ans) ans = tmp;
        mone *= bign(peo[i].l);
    }
    cout << ans.str() << endl;
    return 0;
}