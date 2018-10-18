#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<queue>
using namespace std;
const int N = 200000;
const int INF = 0xffffff;

struct Link_Cut_Tree{
    int n,m,cnt;
    bool vis[N];
    int to[N],next[N],head[N];
	queue<int> Q;
    struct Node{
        int son[2],fa,mx,val;
    } Tr[N];
    inline void Init(){
        memset(head,-1,sizeof head);
        Tr[0].mx=-INF;cnt=0;
    }
    inline void pushup(int x){
        if(!x) return ;
        Tr[x].mx=max(Tr[x].val,max(Tr[Tr[x].son[0]].mx,Tr[Tr[x].son[1]].mx));
    }
    inline bool isroot(int x){
        return Tr[Tr[x].fa].son[0]!=x && Tr[Tr[x].fa].son[1]!=x;
    }
    inline void link(int x,int y,int c){
        Tr[x].fa=y;Tr[y].son[c]=x;
    }
    inline void rot(int x,int c){
        int y=Tr[x].fa;
        if(!isroot(y)) link(x,Tr[y].fa,Tr[Tr[y].fa].son[1]==y);
        else Tr[x].fa=Tr[y].fa;
        link(Tr[x].son[!c],y,c);
        link(y,x,!c);
        pushup(y);
    }
    inline void splay(int x){
        while(!isroot(x)){
            int y=Tr[x].fa;
            int cy=(Tr[Tr[y].fa].son[1]==y),cx=(Tr[y].son[1]==x);
            if(isroot(y)) rot(x,cx);
            else{
                if(cx==cy) rot(y,cy);
                else rot(x,cx);
                rot(x,cy);
            }
        }
        pushup(x);
    }
    inline int access(int x){
        int y;
        for(y=0;x;y=x,x=Tr[x].fa){
            splay(x);
            Tr[x].son[1]=y;
            pushup(x);
        }
        return y;
    }
    inline int querymax(int x,int y){
        access(x);
        int lca=access(y);
        splay(x);
        if(lca==x) return max(Tr[lca].val,Tr[Tr[lca].son[1]].mx);
        else return max(Tr[lca].val,max(Tr[Tr[lca].son[1]].mx,Tr[x].mx));
    }
    inline void change(int x,int w){
        splay(x);Tr[x].val+=w;pushup(x);
    }
    inline void add(int u,int v){
        to[cnt]=v;next[cnt]=head[u];head[u]=cnt++;
    }
    inline void bfs(){
        memset(vis,0,sizeof vis);
        vis[1]=true;Q.push(1);
        while(!Q.empty()){
            int u=Q.front();Q.pop();
            for(int i=head[u];~i;i=next[i])
                if(!vis[to[i]]){
                    Tr[to[i]].fa=u;
                    vis[to[i]]=true;
                    Q.push(to[i]);
                }
        }
    }
    void solve(){
		Init();
        scanf("%d",&n);
        for(int i=1,u,v;i<n;++i){
            scanf("%d%d",&u,&v);
            add(u,v);add(v,u);
        }
        for(int i=1;i<=n;++i) Tr[i].val=0;
        bfs();scanf("%d",&m);
        char str[10];int a,b;
        while(m--){
            scanf("%s",str);
            scanf("%d%d",&a,&b);
            if(str[0]=='I') change(a,b);
            else printf("%d\n",querymax(a,b));
        }
    }
} LCT;

int main()
{
    LCT.solve();
    return 0;
}
