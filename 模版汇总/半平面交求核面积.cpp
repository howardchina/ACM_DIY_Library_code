#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
const double eps=1e-8;
const int N=2000;

struct Point{
    double x,y;
} p[N],q[N],pp[N];
int n,m;
double a,b,c;

void getline(Point x,Point y){
    a=y.y-x.y;
    b=x.x-y.x;
    c=y.x*x.y-x.x*y.y;
}

Point Intersect(Point x,Point y){
    double u=fabs(a*x.x+b*x.y+c),v=fabs(a*y.x+b*y.y+c);
    Point ans;
    ans.x=(x.x*v+y.x*u)/(u+v);
    ans.y=(x.y*v+y.y*u)/(u+v);
    return ans;
}

void cut(){
    int cutm=0;
    for(int i=1;i<=m;++i)
        if(a*p[i].x+b*p[i].y+c>=0)
            q[++cutm]=p[i];
        else{
            if(a*p[i-1].x+b*p[i-1].y+c>0)
                q[++cutm]=Intersect(p[i-1],p[i]);
            if(a*p[i+1].x+b*p[i+1].y+c>0)
                q[++cutm]=Intersect(p[i+1],p[i]);
        }
    for(int i=1;i<=cutm;++i) p[i]=q[i];
    p[cutm+1]=q[1];
    p[0]=q[cutm];
    m=cutm;
}

void solve(){
    for(int i=1;i<=n;++i) p[i]=pp[i];
    pp[n+1]=pp[1];
    p[n+1]=p[1];
    p[0]=p[n];
    m=n;
    for(int i=1;i<=n;++i){
        getline(pp[i],pp[i+1]);
        cut();
    }
}

int main()
{
    int cas;scanf("%d",&cas);
    while(cas--){
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
            scanf("%lf%lf",&pp[i].x,&pp[i].y);
            solve();
            double s=0;
            if(m>=2){
                s=p[0].y*(p[m-1].x-p[1].x);
                p[m]=p[0];
                for(int i=1;i<m;++i)
                    s+=p[i].y*(p[i-1].x-p[i+1].x);
                s=fabs(s*0.5);
            }
            printf("%.2f\n",s);
    }
    return 0;
}
