#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <math.h>
typedef long long lint;

lint gcd(lint a, lint b){
	return b==0?a:gcd(b, a%b);
}
void extgcd(lint a, lint b, lint &g, lint &x, lint &y){
	if(b==0){
		g = a, x = 1, y = 0;
		return;
	}
	extgcd(b, a%b, g, y, x);
	y-=a/b*x;
}
/*ax = b (mod c)*/
lint solution(lint a, lint b, lint c){
	lint x, y, g;
	extgcd(a, c, g, x, y);
	if(b%g) return -1;
	int t = c/g, s = b/g;
	x = x * s %t;
	return (x + t)%t;
}
/***
ax = 1 (mod c)
***/
lint inv(lint a, lint b, lint c){
	lint x, y, g;
	extgcd(a, c, g, x, y);
	x = x * b %c;
	return (x+c)%c;
}
/***
LCM
***/
lint LCM(lint a, lint b){
	return a/gcd(a,b)*b;
}
/***
A * B % C;
***/
lint mul_mod(lint a, lint b, lint c){
	a = a%n;
	lint res = 0;
	for(;b; b>>=1){
		if(b&1){
			res = res  + a;
			if(res >= n) res = res - n;
		}
		a = a<<1;
		if(a>=n) a = a - n;
	}
	return res;
}
/***
A1x = B1 mod M1
A2x = B2 mod M2
A3x = B3 mod M3
...............
Anx = Bn mod Mn
转变为：
x = b1 mod r1
x = b2 mod r2
x = b3 mod r3
.............
x = bn mod rn
***/
/**
x = R[i]%A[i]; 0 =< i < n
**/
pair<int, int> reminder(lint A[], lint R[], int n){
	LL tm = A[0], tr = R[0], g, x, y;
	for(int i = 1; i < n; i ++){
		extgcd(tm, A[i], g, x, y);
		if((tr-R[i])%g){
			return make_pair(0, -1);
		}
		x = (R[i] - tr)/g * x;
		x = (x%(A[i]/g)+A[i]/g)%(A[i]/g);
		tr = tm * x + tr;
		tm = LCM(tm, A[i]);
		tr = (tr%tm + tm)%tm;
	}
	return make_pair(1, tr);
}
/***
m[i]两两互质
***/
lint chineseReminder(lint a[], lint m[], lint n){
	lint M = 1, ans = 0, x, y, g;
	for(int i = 0; i < n; i ++) M *= m[i];
	for(int i = 0; i < n; i ++){
		lint mi = M/m[i];
		extgcd(mi, m[i], g, x, y);
		ans = (ans + a[i]*mi*x)%M;
	}
	return (ans%M+M)%M;
}
/*euler*/
lint euler(lint n){
	lint res = n;
	for(int i = 2; i*i <= n; i ++){
		if(n%i==0){
			res = res/i*(i-1);
			while(n%i==0) n=n/i;
		}
	}
	if(n!=1) res = res /n*(n-1);
	return res;
}
/***
A^B%C
if(B > C) then
B = B%(euler(c)) + euler(c);
***/
lint power_mod(lint A, lint B, lint C){
	lint res = 1;
	for(;B;B>>=1){
		if(B&1) res = res * A %C;
		A = A * A%C;
	}
	return res;
}
/***
C(n, m)%p, n,m<10^9, p<100000;
fac[k] = k!%p
***/
void init(lint p){
	fac[0] = 1;
	for(int i = 1; i <= p; i ++){
		fac[i] = fac[i-1]*i%p;
	}
}
lint C(lint n, lint m, lint p){
	return n>=m? fac[n]*power_mod(fac[k]*fac[n-k]%p, p-2, p)%p:0;
}
lint lucas(lint n, lint m, lint p){
	lint ans = 1;
	while(n&&m&ans){
		ans = ans * C(n%p, m%p, p)%p;
		n/=p;
		m/=p;
	}
	return ans;
}
/***
扩展BSGS
***/
const int SIZE = 65535;
struct HashMap{
	struct Edge{
		lint y, L;
		Edge*next;
	}*ls[SIZE+1], g[SIZE+10];
	int e;
	void init(){
		e = 0;
		memset(ls, 0, sizeof(ls));
	}
	void add(lint y, lint L){
		if(find(y) != -1) return;
		g[e].y = y;
		g[e].L = L;
		g[e].next = ls[y&SIZE];
		ls[y&SIZE] = &g[e ++];
	}
	lint find(lint y){
		for(Edge*t = ls[y&SIZE]; t; t = t->next){
			if(t->y ==y) return t->L;
		}
		return -1;
	}
}hash;
lint BabyStepGiantStep(lint A, lint B, lint C){
	hash.init();
	lint tmp, D = 1%C, Giant, i, x, g, S;

	for(i = 0, tmp = 1%C; i <=100; tmp = tmp*A%C, i ++){
		if(tmp == B) return i;
	}
	for(x = 0; (g = gcd(A, C))!=1; x ++){
		if(B%g) return -1;
		C/=g , B/=g, D=D*(A/g)%C;
	}
	S = (Lint)Ceil(sqrt(C*1.0));
	for(tmp = 1%C, i = 0; i <= S; i ++, tmp = tmp * A%C){
		hash.add(tmp, i);
	}
	for(i = 0, Giant = power_mod(A, S, C); i <= S; D = D * Giant%C, i ++){
		lint t = inv(D, B, C);
		if((tmp = hash.find(t))!= -1){
			return S * i + tmp + x;
		}
	}
	return -1;
}
/***
佩尔方程
***/
