#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<cmath>
using namespace std;
const int N=505;
struct Point{
    double x,y;
} p[N];
int n;

inline double Dis(Point a,Point b){
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
Point CircumCenter(Point a,Point b,Point c){
    Point ret;
    double a1=b.x-a.x,b1=b.y-a.y,c1=(a1*a1+b1*b1)/2;
    double a2=c.x-a.x,b2=c.y-a.y,c2=(a2*a2+b2*b2)/2;
    double d=a1*b2-a2*b1;
    ret.x=a.x+(c1*b2-c2*b1)/d;
    ret.y=a.y+(a1*c2-a2*c1)/d;
    return ret;
}

int main()
{
    while(scanf("%d",&n),n){
        for(int i=0;i<n;++i)
            scanf("%lf%lf",&p[i].x,&p[i].y);
        random_shuffle(p,p+n);
        Point c;double r=0;
        for(int i=1;i<n;++i){
            if(Dis(p[i],c)<=r) continue;
            c=p[i];r=0;
            for(int j=0;j<i;++j){
                if(Dis(p[j],c)<=r) continue;
                c.x=(p[i].x+p[j].x)/2;
                c.y=(p[i].y+p[j].y)/2;
                r=Dis(p[j],c);
                for(int k=0;k<j;++k){
                    if(Dis(p[k],c)<=r) continue;
                    c=CircumCenter(p[i],p[j],p[k]);
                    r=Dis(p[i],c);
                }
            }
        }
        printf("%.2f %.2f %.2f\n",c.x,c.y,r);
    }
    return 0;
}
