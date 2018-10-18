#include <stdio.h>
#include <string.h>
#include <algorithm>

#define maxn 3000000
const int S = 26;
int next[maxn][26], fail[maxn], flag[maxn];
int pos;

int newnode(){
	memset(next[pos], 0, sizeof(next[pos]));
	fail[pos] = flag[pos] = 0;
	return pos ++;
}
void insert(char *word){
	int  r = 0;
	for(int i = 0; word[i]; i ++){
		int &x = next[x][ word[i] - 'a' ];
		r = x ? x : x = newnode();
	}
	flag[r] = 1;
}
int q[maxn], front, rear;
void makefail(){
	q[front = rear = 0] = 0, rear ++;
	while(front < rear){
		int u = q[front ++];
		for(int i = 0; i < S; i ++){
			int v = next[u][i];
			if(v) q[rear++] = v;
			else next[u][i] = next[fail[u]][i];
			if(v&&u) fail[v] = next[fail[u]][i]; 
		}
	}
}
int main(){
	int n; scanf("%d", &n);
	for(int i = 0; i < n; i ++){
		scanf("%s", str);
		insert(str);
	}
	makefail();
	return 0;
}