#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define op operator
#define cp const Point&
#define N 510
using namespace std;
const double eps=1e-9;
inline int sig(double x){return (x>eps)-(x<-eps);}
struct Point{
    double x,y,z;
    Point(double a=0,double b=0,double c=0):x(a),y(b),z(c){}
    void in(){scanf("%lf%lf%lf",&x,&y,&z);}
    Point op+(cp a)const{return Point(x+a.x,y+a.y,z+a.z);}
    Point op-(cp a)const{return Point(x-a.x,y-a.y,z-a.z);}
    Point op*(const double&k)const{return Point(x*k,y*k,z*k);}
    Point op^(cp a)const{return Point(y*a.z-a.y*z,z*a.x-a.z*x,x*a.y-a.x*y);}
    double op*(cp a)const{return x*a.x+y*a.y+z*a.z;}
    Point cross(Point a,Point b){return (a-*this)^(b-*this);}
    double dot(Point a,Point b){return (a-*this)*(b-*this);}
    double L(){return sqrt(x*x+y*y+z*z);}
    double V6(Point b,Point c){return (b^c)*(*this);}
} p[N];
int n;
double diff_vol,max_diff;
struct convex{
    int cnt,blg[N][N];
    struct face{
        int a,b,c,is;
        face(int x=0,int y=0,int z=0,int w=0):a(x),b(y),c(z),is(w){}
        int visible(Point me){
            return sig(p[a].cross(p[b],p[c])*(me-p[a]))>0;
        }
    } fac[N*10];
    int col(int a,int b,int c){return p[a].cross(p[b],p[c]).L()<eps;}
    int cop(int a,int b,int c,int d){return !sig(p[a].cross(p[b],p[c])*(p[d]-p[a]));}
    void deal(int k,int a,int b){
        int f=blg[a][b];
        if(fac[f].is){
            if(fac[f].visible(p[k])) dfs(k,f);
            else{
                face add=face(b,a,k,1);
                blg[b][a]=blg[a][k]=blg[k][b]=cnt;
                fac[cnt++]=add;
            }
        }
    }
    void dfs(int k,int cur){
        fac[cur].is=0;
        deal(k,fac[cur].b,fac[cur].a);
        deal(k,fac[cur].c,fac[cur].b);
        deal(k,fac[cur].a,fac[cur].c);
    }
    void init(){
        cnt=0;
        for(int i=0;i<4;++i){
            face add=face((i+1)%4,(i+2)%4,(i+3)%4,1);
            if(add.visible(p[i])) swap(add.b,add.c);
            blg[add.a][add.b]=blg[add.b][add.c]=blg[add.c][add.a]=cnt;
            fac[cnt++]=add;
        }
    }
    void update(int k){
        for(int i=0;i<cnt;++i)
            if(fac[i].is && fac[i].visible(p[k])){
                dfs(k,i);break;
            }
    }
    double volume(){
        double v=0;
        for(int i=0;i<cnt;++i)
            v+=fac[i].is*p[fac[i].a].V6(p[fac[i].b],p[fac[i].c]);
        return v/6.;
    }
    double Cal(){
        double v=0;
        for(int i=0;i<cnt;++i)
            if(fac[i].is){
                v+=(p[fac[i].b]-p[fac[i].a])^(p[fac[i].c]-p[fac[i].a]).L()/2;
            }
        return v;
    }
}hull;
int main(){
    int n;double x,y,z;
    while(scanf("%d",&n)!=EOF){
        if(n<4){
            for(int i=0;i<n;++i)
                scanf("%lf%lf%lf",&x,&y,&z);
            printf("0.000\n");
            continue;
        }
        max_diff=0;int tag=1;double sum=0;
        p[0].in();
        for(int i=1;i<n;++i){
            p[i].in();
            if(tag==1){
                tag+=sig((p[0]-p[i]).L());
                if(tag>1) swap(p[1],p[i]);
                continue;
            }
            if(tag==2){
                tag+=sig((p[0].cross(p[1],p[i])).L());
                if(tag>2) swap(p[2],p[i]);
                continue;
            }
            if(tag==3){
                tag+=sig(p[0].cross(p[1],p[2])*(p[i]-p[0]))!=0;
                if(tag>3){
                    swap(p[3],p[i]);
                    hull.init();
                    for(int j=4;j<=i;++j) hull.update(j);
                }
                continue;
            }
            hull.update(i);
        }
        sum=hull.Cal();
        printf("%.3f\n",sum);
    }
    return 0;
}
