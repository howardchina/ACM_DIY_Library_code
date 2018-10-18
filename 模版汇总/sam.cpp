#include <stdio.h>
#include <string.h>
#define maxn 40005

struct sanode{
    sanode *f, *ch[26];
    int l, m, pos;
    sanode(){
        f = 0;
        memset(ch, 0, sizeof(ch));
        l = 0, m = 1;
    }
    void init(){
        f = 0;
        memset(ch, 0, sizeof(ch));
        l = 0, m = 1;
    }
}sam[maxn*2], *b[maxn*2];
int cnt[maxn], tot;
sanode *tail, *s;

void add(int c, int len){
    sanode *p = tail, *np = &sam[++tot];
    np->init();
    tail = np;
    np->l = len;
    np->pos = len;
    for(;p&&!p->ch[c]; p = p->f) p->ch[c] = np;
    if(!p) np->f = s;
    else{
        if(p->ch[c]->l == p->l + 1) np->f = p->ch[c];
        else{
            sanode *q = p->ch[c], *r = &sam[++tot];
            r->init();
            *r = *q;
            r->l = p->l + 1;
            r->m = 0;
            q->f = np->f = r;
            for(;p && p->ch[c]==q; p = p->f) p->ch[c] = q;
        }
    }
}

int min(int x, int y){
    return x < y ? x : y;
}

int main(){
    int m, len;
    char c;
    freopen("data.txt","r", stdin);
    while(scanf("%d", &m), m){
        getchar();
        len = 0;
        s = tail = &sam[tot = 0];
        s->init();
        for(c = getchar(); c!='\n';c = getchar()) add(c - 'a', ++len);

        for(int i = 0; i <= tot; i ++) cnt[sam[i].l] ++;
        for(int i = 1; i <= len; i ++) cnt[i] += cnt[i-1];
        for(int i = 0; i <= tot; i ++) b[--cnt[sam[i].l]] = &sam[i];

        int ans = 0, pos = 0;
        for(int i = tot; i > 0; i --){
            b[i]->f->m += b[i]->m;
            b[i]->f->pos = min(b[i]->pos, b[i]->f->pos);
            if(b[i]->m > m){
                if(ans < b[i]->l){
                    ans = b[i]->l;
                    pos = b[i]->pos;
                }
                else if(ans == b[i]->l && pos < b[i]->pos){
                        pos = b[i]->pos;
                }
            }
        }
        printf("%d %d\n", ans, pos);
    }
    return 0;
}
