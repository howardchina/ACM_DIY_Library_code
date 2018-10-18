/*hdu 4449
    求凸多面体的最高放置方法，和最小投影
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define op operator
#define cp const Point&
using namespace std;
const int N = 51;
const double eps = 1e-8;

inline int sig(double x){return (x>eps)-(x<-eps);}
inline double Sqr(double x){return x*x;}
struct Point{
    double x,y,z;
    Point(double a=0,double b=0,double c=0):x(a),y(b),z(c){}
    void in(){scanf("%lf%lf%lf",&x,&y,&z);}
    Point op+(cp a)const{return Point(x+a.x,y+a.y,z+a.z);}
    Point op-(cp a)const{return Point(x-a.x,y-a.y,z-a.z);}
    Point op*(const double&k)const{return Point(x*k,y*k,z*k);}
    Point op^(cp a)const{return Point(y*a.z-a.y*z,z*a.x-a.z*x,x*a.y-a.x*y);}
    Point cross(Point a,Point b){return (a-*this)^(b-*this);}
    double op*(cp a)const{return x*a.x+y*a.y+z*a.z;}
    double dot(Point a,Point b){return (a-*this)*(b-*this);}
    double L(){return sqrt(x*x+y*y+z*z);}
    double Dis(Point b){return sqrt(Sqr(x-b.x)+Sqr(y-b.y)+Sqr(z-b.z));}
    double V6(Point b,Point c){return (b^c)*(*this);}
    double PtoLine(Point b,Point c){return b.cross(*this,c).L()/(c-b).L();}
    bool PinLine(Point b,Point c){return (*this).cross(b,c).L()<eps;}
    bool PonSeg(Point b,Point c){return !sig((*this).cross(b,c).L()) && (*this).dot(b,c)<=0;}
    bool operator<(const Point &p)const{
        if(!sig(x - p.x))
            if(!sig(y - p.y)) return z < p.z;
            else return y < p.y;
        return x < p.x;
    }
} p[N];

struct Convex{
    int cnt,blg[N][N];
    struct face{
        int a,b,c,is;
        Point fxl;
        face(int x=0,int y=0,int z=0,int w=0):a(x),b(y),c(z),is(w){
            fxl=p[a].cross(p[b],p[c]);
        }
        bool visible(Point me){return sig(p[a].cross(p[b],p[c])*(me-p[a]))>0;}
    } fac[N*10];
    int col(int a,int b,int c){return p[a].cross(p[b],p[c]).L()<eps;}
    int cop(int a,int b,int c,int d){return !sig(p[a].cross(p[b],p[c])*(p[d]-p[a]));}
    void deal(int k,int a,int b){
        int f=blg[a][b];
        if(fac[f].is)
            if(fac[f].visible(p[k])) dfs(k,f);
            else{
                face add=face(b,a,k,1);
                blg[b][a]=blg[a][k]=blg[k][b]=cnt;
                fac[cnt++]=add;
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
    struct TY{
        Point p[N],res[N];
        int n,m;void Init(){n=m=0;}
        void Graham(Point fx){
            int i,len;m=1;
            sort(p,p+n);res[0]=p[0];res[1]=p[1];
            for(i=2;i<n;++i){
                while(m && sig(res[m].cross(res[m-1],p[i])*fx)<=0) --m;
                res[++m]=p[i];
            }
            len=m;
            res[++m]=p[n-2];
            for(i=n-3;i>=0;--i){
                while(m!=len && sig(res[m].cross(res[m-1],p[i])*fx)<=0) --m;
                res[++m]=p[i];
            }
        }
        double PolygonArea(){
            if(m<3) return 0;
            double ret=0;
            for(int i=2;i<m;++i)
                ret+=res[0].cross(res[i-1],res[i]).L();
            return fabs(ret)*0.5;
        }
    } ty;
    double PtoPlane(Point pp,face f)
    {return (pp-p[f.a])*f.fxl/f.fxl.L();}
    double Area(face f)
    {return fabs(p[f.a].cross(p[f.b],p[f.c]).L())*0.5;}
    bool PonPlane(Point pp,face f)
    {return !sig((pp-p[f.a])*f.fxl);}
    Point PshPlane(Point p3,face f){
        Point t=p3+f.fxl*(PtoPlane(p3,f)/f.fxl.L());
        if(!PonPlane(t,f)) return p3+p3-t;
        return t;
    }
    void work(int n){
        double mdis=0,mar=1e30;
        for(int j=0;j<cnt;++j){
            if(fac[j].is){
                double ds=0,ar=0;
                ty.Init();
                for(int i=0;i<n;++i){
                    ds=max(ds,fabs(PtoPlane(p[i],fac[j])));
                    ty.p[ty.n++]=PshPlane(p[i],fac[j]);
                }
                ty.Graham(fac[j].fxl);
                ar=ty.PolygonArea();
                if(ds>mdis+eps) mdis=ds,mar=ar;
                else if(ds>mdis-eps && ar<mar+eps) mar=ar;
            }
        }
        printf("%.3f %.3f\n",mdis,mar);
    }
}hull;

int main()
{
    int n,tag;
    while(scanf("%d",&n),n){
        p[0].in();tag=1;
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
        hull.work(n);
    }
    return 0;
}
