#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const int N=100010;
struct Point{
    double x,y;
    Point(){}
    Point(double _x,double _y):x(_x),y(_y){}
} p[N];
int q[N],n;
bool cmp(Point a,Point b){return a.x<b.x;}
bool cmpy(int a,int b){return p[a].y<p[b].y;}
double Dis(Point a,Point b){
    double x=a.x-b.x,y=a.y-b.y;
    return sqrt(x*x+y*y);
}
double NearPoint(int l,int r){
    if(l>=r) return 1e30;
    int n=0,mid=(l+r)>>1;
    double a=min(NearPoint(l,mid),NearPoint(mid+1,r));
    for(int i=mid;i>=l;--i)
        if(p[mid].x-p[i].x<a) q[n++]=i;
    for(int i=mid+1;i<=r;++i)
        if(p[i].x-p[mid].x<a) q[n++]=i;
    sort(q,q+n,cmpy);
    for(int i=0;i<n;++i)
        for(int j=i+1;j<n;++j)
            if(p[q[j]].y-p[q[i]].y<a)
                a=min(a,Dis(p[q[i]],p[q[j]]));
            else
                break;
    return a;
}
int main(){
    while(scanf("%d",&n),n){
        for(int i=0;i<n;++i)
            scanf("%lf%lf",&p[i].x,&p[i].y);
        sort(p,p+n,cmp);
        printf("%.2f\n",NearPoint(0,n-1)/2);
    }
    return 0;
}
//两种点集的最近点对
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define N 200050
#define INF 0xfffffff
using namespace std;
struct Point{
	double x,y;
	bool flag;
} px[N],py[N],p1[N],p2[N];
struct spair{
	Point a,b;
	double dis;
};
bool cmp1(Point a,Point b){
	if(a.x==b.x) return a.y<b.y;
	return a.x<b.x;
}
bool cmp2(Point a,Point b){
	if(a.y==b.y) return a.x<b.x;
	return a.y<b.y;
}
bool cmpequal(Point a,Point b){
	return a.x==b.x && a.y==b.y && a.flag==b.flag;
}
spair solve(int a,int b){
	spair s;
	s.dis=INF,s.a=s.b=px[a];
	for(int i=a;i<b;++i)
		for(int j=i+1;j<b;++j){
			double dis;
			if(px[i].flag!=px[j].flag && (dis=Dis(px[i],px[j]))<s.dis){
				s.dis=dis;
				s.a=px[i],s.b=px[j];
			}
		}
	return s;
}
spair solve(int a,int b,int c,int d){
	if(b-a<=3) return solve(a,b);
	else{
		int mid=(a+b)/2+1,cnt=mid-a;
		double x0=px[mid-1].x;
		int i,j,k,cnt1=0,cnt2=0;
		for(i=c;i<d && cnt1<cnt;++i){
			if(py[i].x<=x0) p1[cnt1++]=py[i];
			else p2[cnt2++]=py[i];
		}
		for(;i<d;++i) p2[cnt2++]=py[i];
		for(i=0;i<cnt1;++i) py[c+i]=p1[i];
		for(i=0;i<cnt2;++i) py[c+cnt1+i]=p2[i];
		spair s1=solve(a,mid,c,c+cnt1),s2=solve(mid,b,c+cnt1,d),s;
		if(s1.dis<=s2.dis) s=s1;else s=s2;
		memcpy(p1,py+c,cnt1*sizeof(Point));
		memcpy(p2,py+c+cnt1,cnt2*sizeof(Point));
		merge(p1,p1+cnt,p2,p2+cnt2,py+c,cmp2);
		for(i=c,j=0;i<d;++i)
			if(fabs(py[i].x-x0)<=s.dis) p1[j++]=py[i];
		for(i=0;i<j;++i)
			for(k=1;k<=7 && k+i<j;++k){
				double dis;
				if(p1[i].flag!=p1[i+k].flag && (dis=Dis(p1[i],p1[i+k]))<s.dis){
					s.dis=dis;
					s.a=p1[i];
					s.b=p1[i+k];
				}
			}
		return s;
	}
}

int main()
{
	int t,n;scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=0;i<n;++i){
			scanf("%lf%lf",&px[i].x,&px[i].y);
			px[i].flag=0;
		}
		for(int i=n;i<2*n;++i){
			scanf("%lf%lf",&px[i].x,&px[i].y);
			px[i].flag=1;
		}
		sort(px,px+2*n,cmp1);
		n=unique(px,px+2*n,cmpequal)-px;
		memcpy(py,px,sizeof py);
		sort(py,py+n,cmp2);
		spair ans=solve(0,n,0,n);
		printf("%.3f\n",ans.dis);
	}
	return 0;
}
