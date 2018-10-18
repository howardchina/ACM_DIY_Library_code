
//���Դ��������
#include <stdio.h>
#include <string.h>

const int maxn = 1000000;
bool flag[maxn+5];
int prim[maxn/3], cnt;
//ʱ�临�Ӷ�O(n), �ռ临�Ӷ�ΪO(n), ����ֱ�ӿ�prim[maxn]
//���������ڿ��Ƚϴ���ڴ棬ʹ��ʱ�临�Ӷ���ߣ����������ֲ��ıȽ���
//���ԣ�ֻ��Ҫ��maxn��1/3����1/4�Ϳ�����
void calc_prim(){
	for(int i = 2; i <= maxn; i ++){
		if(!flag[i]) prim[cnt++] = i;
		for(int j = 0; j < cnt && prim[j]*i <= maxn; j ++){
			flag[i*prim[j]] = 1;
			if(i%prim[j]==0) break;
		}
	}
}

//������ŷ������,�Լ���n��farey���еĸ���
//����ĳ������p n%p = 0
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
	//����n��farey���У�farey[i] = farey[i-1]+phi[i]
	farey[1] = 2;
	for(int i = 2; i <= maxn; i ++)
		farey[i] = farey[i-1] + phi[i];
}

//������Լ������
//Լ�����������ʣ�
//divnum[n] = (e1 + 1)(e2 + 1)(e3 + 1).....(ei��ʾ��i���������ĸ���)
//��ͳ������ÿ�������зֽ�����������ø���������������ʽ
// ���i%prim[j]==0  divnum[i*prim[j]] = divnum[i]/(e[i]+1)*(e[i]+2)
//����divnum[i*prim[j]] = divnum[i] * divnum(prim[j])
//����e[i]��ʾ��i�������ӵĸ���

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