// Reconstructed and regression-checked after runtime reset.
// Fixed singly-chorded C10 root; RGS completion; rejection order structural -> C8 -> loose C10 -> C16.
#include <algorithm>
#include <array>
#include <bitset>
#include <chrono>
#include <cstdint>
#include <cstdio>
#include <vector>
#ifndef SIDE
#define SIDE 38
#endif
namespace cp {
constexpr int V=SIDE; static_assert(2*V<=128); using Line=std::array<int,3>; using Mask=unsigned __int128;
struct C{std::uint64_t states=0,attempted=0,structural=0,loose10=0,c8=0,c16=0,completions=0;};
struct B{std::vector<Line>L;std::array<std::vector<int>,V>inc;std::array<int,V>deg{};std::array<std::bitset<V>,V>pair{};int introduced=9,max_blocks=0;C c;
void add(Line e){int id=L.size();L.push_back(e);for(int p:e){deg[p]++;inc[p].push_back(id);}for(int i=0;i<3;i++)for(int j=i+1;j<3;j++){pair[e[i]].set(e[j]);pair[e[j]].set(e[i]);}}
void rem(){auto e=L.back();L.pop_back();for(int p:e){deg[p]--;inc[p].pop_back();}for(int i=0;i<3;i++)for(int j=i+1;j<3;j++){pair[e[i]].reset(e[j]);pair[e[j]].reset(e[i]);}}
bool path(int cur,int tar,int d,int need,Mask seen)const{if(d==need)return cur==tar;if(cur==tar)return false;if(cur<V){for(int id:inc[cur]){int nx=V+id;Mask bit=Mask(1)<<nx;if(seen&bit)continue;if(path(nx,tar,d+1,need,seen|bit))return true;}}else for(int nx:L[cur-V]){Mask bit=Mask(1)<<nx;if(seen&bit)continue;if(nx==tar&&d+1!=need)continue;if(path(nx,tar,d+1,need,seen|bit))return true;}return false;}
bool closes(const Line&e,int need)const{for(int i=0;i<3;i++)for(int j=i+1;j<3;j++)if(path(e[i],e[j],0,need,Mask(1)<<e[i]))return true;return false;}
static int inter(const Line&a,const Line&b){int z=0;for(int x:a)for(int y:b)z+=x==y;return z;}
bool induced5(const Line&e,const std::array<int,4>&ids)const{std::array<Line,5>a{e,L[ids[0]],L[ids[1]],L[ids[2]],L[ids[3]]};for(int i=0;i<5;i++)for(int j=i+1;j<5;j++){int d=j-i;bool con=(d==1||d==4);int z=inter(a[i],a[j]);if(con?(z!=1):(z!=0))return false;}return true;}
bool loose_dfs(int cur,int tar,int d,Mask seen,const Line&e,std::array<int,4>&ids,int nb)const{if(d==8)return cur==tar&&nb==4&&induced5(e,ids);if(cur==tar)return false;if(cur<V){if(nb>=4)return false;for(int id:inc[cur]){int nx=V+id;Mask bit=Mask(1)<<nx;if(seen&bit)continue;ids[nb]=id;if(loose_dfs(nx,tar,d+1,seen|bit,e,ids,nb+1))return true;}}else for(int nx:L[cur-V]){Mask bit=Mask(1)<<nx;if(seen&bit)continue;if(nx==tar&&d+1!=8)continue;if(loose_dfs(nx,tar,d+1,seen|bit,e,ids,nb))return true;}return false;}
bool creates_loose(const Line&e)const{for(int i=0;i<3;i++)for(int j=i+1;j<3;j++){std::array<int,4>ids{};if(loose_dfs(e[i],e[j],0,Mask(1)<<e[i],e,ids,0))return true;}return false;}
bool bad(const Line&e,int old)const{for(int p:e)if(p<old&&deg[p]>=3)return true;for(int i=0;i<3;i++)for(int j=i+1;j<3;j++)if(e[i]<old&&e[j]<old&&pair[e[i]].test(e[j]))return true;return false;}
void rec(int p,int lq,int lr){c.states++;max_blocks=std::max(max_blocks,(int)L.size());while(p<introduced&&deg[p]==3){p++;lq=lr=-1;}if(p>=introduced){if((int)L.size()==introduced)c.completions++;return;}if((int)L.size()>=V)return;int old=introduced;std::vector<int>v;for(int q=p+1;q<old;q++)if(deg[q]<3&&!pair[p].test(q))v.push_back(q);if(old<V)v.push_back(old);if(old+1<V)v.push_back(old+1);for(size_t i=0;i<v.size();i++)for(size_t j=i+1;j<v.size();j++){int q=v[i],r=v[j];if(r==old+1&&q!=old)continue;if(lq>=0&&(q<lq||(q==lq&&r<=lr)))continue;c.attempted++;Line e{p,q,r};if(bad(e,old)){c.structural++;continue;}if(closes(e,6)){c.c8++;continue;}if(creates_loose(e)){c.loose10++;continue;}if(closes(e,14)){c.c16++;continue;}int nxt=old;if(q==old||r==old)nxt++;if(r==old+1)nxt++;int sv=introduced;introduced=nxt;add(e);rec(p,q,r);rem();introduced=sv;}}
C run(){add({0,1,3});add({1,2,5});add({2,3,6});add({3,4,7});add({0,4,8});rec(0,-1,-1);return c;}};}
int main(){auto st=std::chrono::steady_clock::now();cp::B b;auto c=b.run();double s=std::chrono::duration<double>(std::chrono::steady_clock::now()-st).count();printf("TOTAL V=%d states=%llu attempted=%llu structural=%llu loose10=%llu c8=%llu c16=%llu completions=%llu max_blocks=%d seconds=%.6f\n",cp::V,(unsigned long long)c.states,(unsigned long long)c.attempted,(unsigned long long)c.structural,(unsigned long long)c.loose10,(unsigned long long)c.c8,(unsigned long long)c.c16,(unsigned long long)c.completions,b.max_blocks,s);return c.completions?2:0;}
