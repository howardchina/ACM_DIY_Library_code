#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
const double PI=acos(-1.);
const double eps=1e-6;
const int N=55;
inline int Sig(double x){return (x>eps)-(x<-eps);}
template<class T> T sqr(T x){return x*x;}
struct Point{
    double x,y;
    Point(){}
    Point(double xx,double yy):x(xx),y(yy){}
    Point operator + (Point a){return Point(x+a.x,y+a.y);}
    Point operator - (Point a){return Point(x-a.x,y-a.y);}
    Point operator * (double p){return Point(x*p,y*p);}
    Point operator / (double p){return Point(x/p,y/p);}
    bool operator < (Point a){
        return Sig(x-a.x)<0 || (Sig(x-a.x)==0 && y<a.y);
    }
    bool operator == (Point a){
        return Sig(x-a.x)==0 && Sig(y-a.y)==0;
    }
} pt[N];
double dot(Point a,Point b){return a.x*b.x+a.y*b.y;}
double cross(Point a,Point b){return a.x*b.y-b.x*a.y;}
double veclen(Point x){return sqrt(dot(x,x));}
double angle(Point x){return atan2(x.y,x.x);}
Point normal(Point x){return Point(-x.y,x.x)/veclen(x);}
Point vecunit(Point x){return x/veclen(x);}

struct Line{
    Point s,t;
    Line(){}
    Line(Point s,Point t):s(s),t(t){}
    Point vec(){return t-s;}
    Point point(double p){return s+vec()*p;}
};
bool OnSeg(Point x,Point s,Point t){
    return Sig(cross(s-x,t-x))==0 && Sig(dot(s-x,t-x))<0;
}
Point llint(Line a,Line b){
    return a.point(cross(b.vec(),a.s-b.s)/cross(a.vec(),b.vec()));
}

struct Circle{
    Point c;
    double r;
    Circle(){}
    Circle(Point c,double r):c(c),r(r){}
} ori;
bool InCircle(Point x,Circle c){return Sig(c.r-veclen(c.c-x))>=0;}

int lcint(Line l,Circle c,Point *sol){
    Point nor=normal(l.vec()),ip=llint(l,Line(c.c,c.c+nor));
    double dis=veclen(ip-c.c);
    if(Sig(dis-c.r)>=0) return 0;
    Point dxy=vecunit(l.vec())*sqrt(sqr(c.r)-sqr(dis));
    int ret=0;
    sol[ret]=ip+dxy;
    if(OnSeg(sol[ret],l.s,l.t)) ++ret;
    sol[ret]=ip-dxy;
    if(OnSeg(sol[ret],l.s,l.t)) ++ret;
    return ret;
}

double Getsec(Circle c,Point a,Point b){
    double a1=angle(a-c.c),a2=angle(b-c.c),da=fabs(a1-a2);
    if(da>PI) da=PI*2.0-da;
    return da*Sig(cross(a-c.c,b-c.c))*sqr(c.r)/2.0;
}
double Gettri(Point o,Point a,Point b){return cross(a-o,b-o)/2.0;}

double Getarea(Point *p,int n){
    p[n]=p[0];Point tmp[2];
    double ret=0.;
    for(int i=0;i<n;++i){
        int ipc=lcint(Line(p[i],p[i+1]),ori,tmp);
        if(ipc==0){
            if(!InCircle(p[i],ori) || !InCircle(p[i+1],ori))
                ret+=Getsec(ori,p[i],p[i+1]);
            else
                ret+=Gettri(ori.c,p[i],p[i+1]);
        }
        if(ipc==1){
            if(InCircle(p[i],ori) && !InCircle(p[i+1],ori))
                ret+=Gettri(ori.c,p[i],tmp[0]),
                ret+=Getsec(ori,tmp[0],p[i+1]);
            else
                ret+=Getsec(ori,p[i],tmp[0]),
                ret+=Gettri(ori.c,tmp[0],p[i+1]);
        }
        if(ipc==2){
            if((p[i]<p[i+1])^(tmp[0]<tmp[1])) swap(tmp[0],tmp[1]);
            ret+=Getsec(ori,p[i],tmp[0]);
            ret+=Gettri(ori.c,tmp[0],tmp[1]);
            ret+=Getsec(ori,tmp[1],p[i+1]);
        }
    }
    return fabs(ret);
}

int main()
{
    int n;double r;
    while(scanf("%lf%d",&r,&n)!=EOF){
        for(int i=0;i<n;++i)
            scanf("%lf%lf",&pt[i].x,&pt[i].y);
        ori=Circle(Point(0.,0.),r);
        printf("%.2f\n",Getarea(pt,n));
    }
    return 0;
}
