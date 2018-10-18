
//线性打表求素数
#include <stdio.h>
#include <string.h>

const int maxn = 1000000;
bool flag[maxn+5];
int prim[maxn/3], cnt;
//时间复杂度O(n), 空间复杂度为O(n), 不宜直接开prim[maxn]
//这样会由于开比较大的内存，使得时间复杂度提高，由于素数分布的比较少
//所以，只需要开maxn的1/3或者1/4就可以了
void calc_prim(){
	for(int i = 2; i <= maxn; i ++){
		if(!flag[i]) prim[cnt++] = i;
		for(int j = 0; j < cnt && prim[j]*i <= maxn; j ++){
			flag[i*prim[j]] = 1;
			if(i%prim[j]==0) break;
		}
	}
}

//线性求欧拉函数,以及求n阶farey数列的个数
//对于某个素数p n%p = 0
//n%p==0 && (n/p)%p==0 phi[n] = phi[n/p] * p
//n%p==0 && (n/p)%p!=0 phi[n] = phi[n/p] *(p-1)

#include <stdio.h>
#include <string.h>
const int maxn = 1000000;
int prim[maxn/3],phi[maxn+5], cnt = 0;
bool flag[maxn+2];
long long farey[maxn+5];

void calc_phi_farey(){
	for(int i = 2; i <= maxn; i ++){
		if(!flag[i]) prim[cnt ++] = i, phi[i] = i - 1;
		for(int j = 0; j < cnt && prim[j]*i <= maxn; j ++){
			flag[i*prim[j]] = 1;
			if(i%prim[j]==0){
				phi[i*prim[j]] = phi[i] * prim[j];
				break; 
			} 
			phi[i*prim[j]] = phi[i] *(prim[j]-1);
		}
	}
	//init farey[1] = 2;
	//对于n阶farey数列，farey[i] = farey[i-1]+phi[i]
	farey[1] = 2;
	for(int i = 2; i <= maxn; i ++)
		farey[i] = farey[i-1] + phi[i];
}

//线性求约数个数
//约数个数的性质：
//divnum[n] = (e1 + 1)(e2 + 1)(e3 + 1).....(ei表示第i个质因数的个数)
//传统方法对每个数进行分解质因数，获得各因数个数再用上式
// 如果i%prim[j]==0  divnum[i*prim[j]] = divnum[i]/(e[i]+1)*(e[i]+2)
//否则divnum[i*prim[j]] = divnum[i] * divnum(prim[j])
//其中e[i]表示第i个素因子的个数

#include <stdio.h>
#include <string.h>

const int maxn = 1000000
int prim[maxn/3], e[maxn/3], divnum[maxn+5], cnt;
bool flag[maxn+5];

void calc_factor_number(){ 
	for(i = 2; i <= maxn; i ++){
		if(!flag[i]) prim[cnt ++] = i, e[i] = 1, divnum[i] = 2;
		for(j = 0; j < cnt && i*prim[j]<= maxn; j ++){
			flag[i*prim[j]] = 1;
			if(i%prim[j]==0){
				divnum[i*prim[j]] = divnum[i]/(e[i]+1)*(e[i]+2);
				e[i*prim[j]] = e[i]+1;
				break;
			}
			divnum[i*prim[j]] = divnum[i]*divnum[prim[j]];
			e[i] = 1;
		}
	}
}