#include<iostream>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
const int ending = -10010;
const double eps = 1e-08;
const double pi = acos(-1.0);
const double tau = pi*2;
inline int sig(double o){return (o>eps)-(o<-eps);}
typedef pair<double, double> interval;
bool valid[1010];
int n,keymr;

struct circle{
    double x, y, r;
    circle(){}
    circle(double x0, double y0, double r0):x(x0),y(y0),r(r0){}
} list[1010];
struct rec{
    double ang; int pwr;
    rec(void){}
    rec(double a0, int p0):ang(a0),pwr(p0){}
    bool operator < (const rec& a) const{
        if (sig(ang-a.ang)) return sig(ang-a.ang) == -1;
        else return pwr > a.pwr;
    }
} key[5010];

inline int judge(const circle& a, const circle& b){
    double dx=b.x-a.x, dy=b.y-a.y;
    double d=sqrt(dx*dx+dy*dy);
    if (sig(a.r+b.r-d) <= 0) return 1;
    else if (sig(a.r+d-b.r) <= 0) return 2;
    else if (sig(b.r+d-a.r) <= 0) return 3;
    else return 0;
}
inline interval intersect (const circle& a, const circle& b){
    double dx=b.x-a.x, dy=b.y-a.y;
    double d=dx*dx+dy*dy;
    double ag=atan2(dy,dx);
    double tg=acos((a.r*a.r+d-b.r*b.r)/(2*a.r*sqrt(d)));
    if(sig(ag-tg) == -1) return make_pair(ag-tg+tau,ag+tg+tau);
    else return make_pair(ag-tg,ag+tg);
}
inline double cal (const circle& c, double a0, double a1){
    double da=a1-a0;
    if (sig(da) == 0) return 0;
    double px0=c.x+c.r*cos(a0),py0=c.y+c.r*sin(a0);
    double px1=c.x+c.r*cos(a1),py1=c.y+c.r*sin(a1);
    double s=c.r*c.r*(da-sin(da))+(px0*py1-px1*py0);
    return s;
}
double stat (int cnt){
    keymr=0; double res=0;
    if (valid[cnt] == false) return 0;
    for (int i=0;i<n;i++){
        if (i == cnt || valid[i] == false) continue;
        int res=judge(list[cnt],list[i]);
        if (res == 2){
			valid[cnt]=false;
			return 0;
		}
        else if (res == 3) valid[i]=false;
        else if (res == 0){
            interval tt=intersect(list[cnt], list[i]);
            if (sig(tau-tt.second) == -1){
                key[keymr++]=rec(tt.first,1);
                key[keymr++]=rec(tau,-1);
                key[keymr++]=rec(0,1);
                key[keymr++]=rec(tt.second-tau,-1);
            }
            else{
                key[keymr++]=rec(tt.first,1);
                key[keymr++]=rec(tt.second,-1);
            }
        }
    }
    if (keymr == 0) res=pi*list[cnt].r*list[cnt].r*2;
    else{
        key[keymr++]=rec(tau,ending);
        sort(key,key+keymr);
        int stack=0;
        res+=cal(list[cnt],0,key[0].ang);
        for (int i=0;i<keymr;i++){
            stack+=key[i].pwr;
            if (stack == 0) res+=cal(list[cnt],key[i].ang,key[i+1].ang);
        }
    }
    return res;
}
int main (){
    int cnt;
    scanf("%d",&cnt),n=0;
    for (int i=0;i<cnt;i++){
        int x0,y0,r0;
        scanf("%d %d %d",&x0,&y0,&r0);
        if (r0) list[n++]=circle(x0,y0,r0);
    }
    memset(valid,true,sizeof valid);
    double ans=0;
    for (int i=0;i<n;i++) ans+=stat(i);
    printf("%.3f\n",ans*0.5);
    return 0;
}
