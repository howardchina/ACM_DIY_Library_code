#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
#define fs(x) ((x)<0 ? (-(x)):(x))
using namespace std;
const int N =1010;
const double eps=1e-8;
pair<double,double> se[N];
struct Circle{
    int x,y,r;
} c[N],nc[N];
int xl[N],xr[N],s[N],n,L,R;

inline bool cmp1(int a,int b){
    if(c[a].x-c[a].r==c[b].x-c[b].r)
        return c[a].x+c[a].r<c[b].x+c[b].r;
    return c[a].x-c[a].r<c[b].x-c[b].r;
}
inline bool cmp2(int a,int b){return c[a].r>c[b].r;}

double f(double v){
    int sz=0,i,j,res;double ret=0.;
    for(i=L;i<R;++i){
        if(v<=xl[i] || v>=xr[i]) continue;
        j=s[i];
        double d=sqrt(c[j].r-(v-c[j].x)*(v-c[j].x));
        se[sz].first=c[j].y-d;
        se[sz].second=c[j].y+d;
        ++sz;
    }
    sort(se,se+sz);
    for(i=0;i<sz;++i){
        double nowl=se[i].first,nowr=se[i].second;
        for(j=i+1;j<sz;++j)
            if(se[j].first>nowr) break;
            else nowr=max(nowr,se[j].second);
        ret+=nowr-nowl;
        i=j-1;
    }
    return ret;
}
double rsimp(double l,double m,double r,double sl,double sm,double sr,double tot){
    double m1=(l+m)*0.5,m2=(m+r)*0.5;
    double s0=f(m1),s2=f(m2);
    double gl=(sl+sm+s0*4)*(m-l),gr=(sm+sr+s2*4)*(r-m);
    if(fs(gl+gr-tot)<eps) return gl+gr;
    return rsimp(l,m1,m,sl,s0,sm,gl)+rsimp(m,m2,r,sm,s2,sr,gr);
}

void work(){
    sort(s,s+n,cmp1);
    double lo,hi,ans=0.;
    int i,j;
    for(i=0;i<n;++i)
        xl[i]=c[s[i]].x-c[s[i]].r,
        xr[i]=c[s[i]].x+c[s[i]].r,
        c[s[i]].r*=c[s[i]].r;
    for(i=0;i<n;++i){
        int ilo,ihi;
        ilo=xl[i];ihi=xr[i];
        for(j=i+1;j<n;++j){//分段积分
            if(xl[j]>ihi) break;
            ihi=max(ihi,xr[j]);
        }
        lo=ilo,hi=ihi;
        L=i;R=j;
        double mid=(lo+hi)*0.5;
        double sl=f(lo),sm=f(mid),sr=f(hi);
        double tot=sl+sr+sm*4;
        ans+=rsimp(lo,mid,hi,sl,sm,sr,tot);
        i=j-1;
    }
    printf("%.3f\n",ans/6.0);
}

int main()
{
    while(scanf("%d",&n)!=EOF){
        int i,k,j=0;
        for(i=0;i<n;++i)
            scanf("%d%d%d",&c[i].x,&c[i].y,&c[i].r),s[i]=i;
        sort(s,s+n,cmp2);
        /*
        (1) 去掉被包含(内含 or 内切)的小圆 ()
        (2) 去掉相同的圆
        */
        for(i=0;i<n;++i){
            for(k=0;k<j;++k)
                if( (nc[k].x-c[s[i]].x)*(nc[k].x-c[s[i]].x)+(nc[k].y-c[s[i]].y)*(nc[k].y-c[s[i]].y)
                     <=(nc[k].r-c[s[i]].r)*(nc[k].r-c[s[i]].r) ) break;
            if(k==j){
                nc[j]=c[s[i]];
                s[j]=j;++j;
            }
        }
        n=j;
        for(i=0;i<n;++i) c[i]=nc[i];
        work();//开始积分....
    }
    return 0;
}
