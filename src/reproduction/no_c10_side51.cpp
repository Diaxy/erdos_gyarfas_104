#include <array>
#include <bitset>
#include <chrono>
#include <cstdint>
#include <cstdio>
#include <vector>
#ifndef SIDE
#define SIDE 51
#endif
namespace nc {
constexpr int V=SIDE; using Line=std::array<int,3>; using Mask=unsigned __int128;
struct C{uint64_t states=0,attempted=0,structural=0,c8=0,c10=0,c16=0,accepted=0,completions=0; C&operator+=(const C&o){states+=o.states;attempted+=o.attempted;structural+=o.structural;c8+=o.c8;c10+=o.c10;c16+=o.c16;accepted+=o.accepted;completions+=o.completions;return *this;}};
struct B{
 std::vector<Line>L; std::array<std::vector<int>,V>inc; std::array<int,V>deg{}; std::array<std::bitset<V>,V>pair{}; std::array<std::array<int,V>,V>pb; int introduced=6; C c;
 B(){for(auto&r:pb)r.fill(-1);}
 void add(Line e){int id=L.size();L.push_back(e);for(int p:e){deg[p]++;inc[p].push_back(id);}for(int i=0;i<3;i++)for(int j=i+1;j<3;j++){pair[e[i]].set(e[j]);pair[e[j]].set(e[i]);pb[e[i]][e[j]]=pb[e[j]][e[i]]=id;}}
 void rem(){auto e=L.back();L.pop_back();for(int p:e){deg[p]--;inc[p].pop_back();}for(int i=0;i<3;i++)for(int j=i+1;j<3;j++){pair[e[i]].reset(e[j]);pair[e[j]].reset(e[i]);pb[e[i]][e[j]]=pb[e[j]][e[i]]=-1;}}
 bool bad(Line e,int old)const{for(int x:e)if(x<old&&deg[x]>=3)return true;for(int i=0;i<3;i++)for(int j=i+1;j<3;j++)if(e[i]<old&&e[j]<old&&pair[e[i]].test(e[j]))return true;return false;}
 bool c8(Line e)const{for(int a=0;a<3;a++)for(int b=a+1;b<3;b++){int x=e[a],y=e[b];for(int ai:inc[x])for(int u:L[ai]){if(u==x||u==y)continue;for(int ci:inc[y]){if(ci==ai)continue;for(int v:L[ci]){if(v==x||v==y||v==u)continue;int bi=pb[u][v];if(bi>=0&&bi!=ai&&bi!=ci)return true;}}}}return false;}
 bool pk(int cur,int tar,int d,int k,Mask sp,Mask sb)const{if(d==k)return cur==tar;if(cur==tar)return false;for(int id:inc[cur]){Mask bm=Mask(1)<<id;if(sb&bm)continue;for(int nx:L[id]){if(nx==cur)continue;Mask pm=Mask(1)<<nx;if(sp&pm)continue;if(nx==tar&&d+1!=k)continue;if(pk(nx,tar,d+1,k,sp|pm,sb|bm))return true;}}return false;}
 bool closes(Line e,int k)const{for(int i=0;i<3;i++)for(int j=i+1;j<3;j++)if(pk(e[i],e[j],0,k,Mask(1)<<e[i],0))return true;return false;}
 void rec(int p,int lq,int lr){c.states++;while(p<introduced&&deg[p]==3){p++;lq=lr=-1;}if(p>=introduced){if((int)L.size()==introduced)c.completions++;return;}if((int)L.size()>=V)return;int old=introduced;std::vector<int>v;for(int q=p+1;q<old;q++)if(deg[q]<3&&!pair[p].test(q))v.push_back(q);if(old<V)v.push_back(old);if(old+1<V)v.push_back(old+1);for(size_t i=0;i<v.size();i++)for(size_t j=i+1;j<v.size();j++){int q=v[i],r=v[j];if(r==old+1&&q!=old)continue;if(lq>=0&&(q<lq||(q==lq&&r<=lr)))continue;c.attempted++;Line e{p,q,r};if(bad(e,old)){c.structural++;continue;}if(c8(e)){c.c8++;continue;}if(closes(e,4)){c.c10++;continue;}if(closes(e,7)){c.c16++;continue;}c.accepted++;int nxt=old;if(q==old||r==old)nxt++;if(r==old+1)nxt++;int sv=introduced;introduced=nxt;add(e);rec(p,q,r);rem();introduced=sv;}}
 C run(Line first,int nextIntro){add({0,1,3});add({1,2,4});add({0,2,5});add(first);introduced=nextIntro;rec(0,-1,-1);return c;}
};}
int main(){auto st=std::chrono::steady_clock::now(); nc::B a,b; auto x=a.run({0,4,6},7); auto y=b.run({0,6,7},8); x+=y; double s=std::chrono::duration<double>(std::chrono::steady_clock::now()-st).count(); printf("TOTAL V=%d states=%llu attempted=%llu structural=%llu c8=%llu c10=%llu c16=%llu accepted=%llu completions=%llu seconds=%.6f\n",nc::V,(unsigned long long)x.states,(unsigned long long)x.attempted,(unsigned long long)x.structural,(unsigned long long)x.c8,(unsigned long long)x.c10,(unsigned long long)x.c16,(unsigned long long)x.accepted,(unsigned long long)x.completions,s);return x.completions?2:0;}
