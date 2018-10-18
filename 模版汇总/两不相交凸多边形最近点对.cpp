#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define N 10010
using namespace std;
const double eps=1e-8;
inline int Sig(double x){
    return (x>eps)-(x<-eps);
}
struct Point{
    double x,y;
    Point(){}
    Point(double _x,double _y):x(_x),y(_y){}
    Point operator-(const Point a){return Point(x-a.x,y-a.y);}
} s;
struct Polygon{
    int n;
    Point p[N];
} ply1,ply2;

double Dis(Point a,Point b){
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
double cross(Point a,Point b,Point c){
    Point s=(b-a),t=(c-a);
    return s.x*t.y-s.y*t.x;
}
bool cmop(Point a,Point b){
    if(Sig(a.x-b.x)==0) return a.y<b.y;
    return a.x<b.y;
}
bool cmp(Point a,Point b){
    int d1=Sig(cross(s,a,b));
    return d1>0 || (d1==0 && Dis(s,a)<Dis(s,b));
}

Polygon graham(Polygon ply){
    int i,j,k;
    sort(ply.p,ply.p+ply.n,cmop);
    s=ply.p[0];k=2;
    sort(ply.p+1,ply.p+ply.n,cmp);
    for(i=2,k=2;i<ply.n;++i){
        while(k>1 && Sig(cross(ply.p[k-2],ply.p[i],ply.p[k-1]))>=0) --k;
        ply.p[k++]=ply.p[i];
    }
    ply.n=k;
    return ply;
}
double disps(Point a,Point b,Point c){
    Point s=(a-b),t=(c-b);
    if(s.x*t.x+s.y*t.y<0) return Dis(a,b);
    s=(a-c);t=(b-c);
    if(s.x*t.x+s.y*t.y<0) return Dis(a,c);
    return fabs(cross(a,b,c))/(Dis(b,c));
}
double disss(Point a,Point b,Point c,Point d){
    return min(min(disps(a,c,d),disps(b,c,d)),min(disps(c,a,b),disps(d,a,b)));
}
double solve(Polygon pl,Polygon pr,int p,int q){
    int i;
    double tmp,Min=1e90;
    pl.p[pl.n]=pl.p[0];pr.p[pr.n]=pr.p[0];
    for(i=0;i<pl.n;++i){
        while((tmp=cross(pl.p[p+1],pr.p[q+1],pl.p[p])-cross(pl.p[p+1],pr.p[q],pl.p[p]))>eps)
            ++q,q%=pr.n;
        if(tmp<-eps) Min=min(Min,disps(pr.p[q],pl.p[p],pl.p[p+1]));
        else Min=min(Min,disss(pl.p[p],pl.p[p+1],pr.p[q],pr.p[q+1]));
        ++p,p%=pl.n;
    }
    return Min;
}

int main()
{
    while(scanf("%d%d",&ply1.n,&ply2.n),ply1.n&&ply2.n){
        int i,l,r;
        for(int i=0;i<ply1.n;++i)
            scanf("%lf%lf",&ply1.p[i].x,&ply1.p[i].y);
        for(int i=0;i<ply2.n;++i)
            scanf("%lf%lf",&ply2.p[i].x,&ply2.p[i].y);
        ply1=graham(ply1);ply2=graham(ply2);
        l=r=0;
        for(int i=0;i<ply1.n;++i)
            if(Sig(ply1.p[i].y-ply1.p[l].y)<0) l=i;
        for(int i=0;i<ply2.n;++i)
            if(Sig(ply2.p[i].y-ply2.p[r].y)>0) r=i;
        double mindis=min(solve(ply1,ply2,l,r),solve(ply2,ply1,r,l));
        printf("%.5f\n",mindis);
    }
    return 0;
}
