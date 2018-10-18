#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define maxn 1005
using namespace std;
const double eps=1e-8;
int dcmp(double x){return (x>eps)-(x<-eps);}

struct Point{
    double x,y;
} p[maxn],res[maxn];
int n;

bool mult(Point a,Point b,Point c){
    return (a.x-c.x)*(b.y-c.y)>=(b.x-c.x)*(a.y-c.y);
}
bool cmp(Point l,Point r){
    return l.y<r.y || (l.y==r.y && l.x<r.x);
}

int Graham(Point pnt[],int n,Point res[]){
    int len,top=1;
    if(n<2){
        res[0]=pnt[0];return 1;
    }
    sort(pnt,pnt+n,cmp);
    res[0]=pnt[0];res[1]=pnt[1];
    for(int i=2;i<n;++i){
        while(top && mult(pnt[i],res[top],res[top-1])) --top;
        res[++top]=pnt[i];
    }
    len=top;res[++top]=pnt[n-2];
    for(int i=n-3;i>=0;--i){
        while(top!=len && mult(pnt[i],res[top],res[top-1])) --top;
        res[++top]=pnt[i];
    }
    return top;
}
int main()
{
    double ans;int tot;
    while(scanf("%d",&n)!=EOF){
        for(int i=0;i<n;++i){
            scanf("%lf%lf",&p[i].x,&p[i].y);
        }
        tot=Graham(p,n,res);
        //res为答案，tot为凸包点数。
    }
    return 0;
}
