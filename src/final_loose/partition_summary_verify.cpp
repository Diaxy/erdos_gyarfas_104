#include <algorithm>
#include <array>
#include <bitset>
#include <chrono>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>
#ifndef SIDE
#define SIDE 43
#endif
#ifndef TASK_DEPTH
#define TASK_DEPTH 20
#endif
namespace pv {
constexpr int V=SIDE;
static_assert(2*V<=128,"incidence mask requires <=128 nodes");
using Line=std::array<int,3>; using Mask=unsigned __int128;
struct Counts{
 uint64_t states=0,attempted=0,structural=0,c8=0,c16=0,accepted=0,rootprune=0,completions=0;
 Counts& operator+=(const Counts&o){states+=o.states;attempted+=o.attempted;structural+=o.structural;c8+=o.c8;c16+=o.c16;accepted+=o.accepted;rootprune+=o.rootprune;completions+=o.completions;return *this;}
 bool same_record(const Counts&o)const{return states==o.states&&attempted==o.attempted&&structural==o.structural&&c8==o.c8&&c16==o.c16&&accepted==o.accepted&&completions==o.completions;}
};
struct Reader{
 FILE*f=nullptr; uint64_t bytes=0; int worker=-1,W=-1;
 Reader(const char*path,int ew,int eW){f=fopen(path,"rb");if(!f){perror(path);exit(66);} unsigned char h[9]; if(fread(h,1,9,f)!=9){fprintf(stderr,"truncated header\n");exit(2);}bytes=9; unsigned char exp[7]={'E','G','P','S',1,(unsigned char)V,(unsigned char)TASK_DEPTH};for(int i=0;i<7;i++)if(h[i]!=exp[i]){fprintf(stderr,"bad header byte %d\n",i);exit(2);}W=h[7];worker=h[8];if(W!=eW||worker!=ew){fprintf(stderr,"worker header mismatch got=%d/%d expected=%d/%d\n",worker,W,ew,eW);exit(2);}}
 unsigned char raw(){int x=fgetc(f);if(x==EOF){fprintf(stderr,"truncated certificate after %llu bytes\n",(unsigned long long)bytes);exit(2);}bytes++;return (unsigned char)x;}
 uint64_t u64(){uint64_t x=0;for(int i=0;i<8;i++)x|=uint64_t(raw())<<(8*i);return x;}
 Counts next(uint64_t expected_id){unsigned char tag=raw();if(tag!='T'){fprintf(stderr,"expected T for task %llu got 0x%02x\n",(unsigned long long)expected_id,(unsigned)tag);exit(2);}uint64_t id=u64();if(id!=expected_id){fprintf(stderr,"task id mismatch got=%llu expected=%llu\n",(unsigned long long)id,(unsigned long long)expected_id);exit(2);}Counts c;c.states=u64();c.attempted=u64();c.structural=u64();c.c8=u64();c.c16=u64();c.accepted=u64();c.completions=u64();return c;}
 void finish(){unsigned char t=raw();if(t!='E'){fprintf(stderr,"missing end marker\n");exit(2);}if(fgetc(f)!=EOF){fprintf(stderr,"trailing data\n");exit(2);}}
 ~Reader(){if(f)fclose(f);}
};
struct Half{unsigned char endpoint;Mask mask;};
struct Search{
 std::vector<Line> lines; std::array<std::vector<int>,V> through; std::array<int,V> degree{}; std::array<std::bitset<V>,V> together{}; int introduced=10;
 Counts prefix,sub; uint64_t task_count=0,assigned=0; int worker,W; Reader&r;
 Search(int ww,int WWW,Reader&rr):worker(ww),W(WWW),r(rr){}
 void insert(Line e){int id=(int)lines.size();lines.push_back(e);for(int p:e){degree[p]++;through[p].push_back(id);}for(int i=0;i<3;i++)for(int j=i+1;j<3;j++){together[e[i]].set(e[j]);together[e[j]].set(e[i]);}}
 void erase(){Line e=lines.back();lines.pop_back();for(int p:e){degree[p]--;through[p].pop_back();}for(int i=0;i<3;i++)for(int j=i+1;j<3;j++){together[e[i]].reset(e[j]);together[e[j]].reset(e[i]);}}
 bool structural(const Line&e,int old)const{for(int p:e)if(p<old&&degree[p]>=3)return true;for(int i=0;i<3;i++)for(int j=i+1;j<3;j++)if(e[i]<old&&e[j]<old&&together[e[i]].test(e[j]))return true;return false;}
 bool exact_path(int cur,int target,int d,int need,Mask seen)const{
  if(d==need)return cur==target; if(cur==target)return false;
  if(cur<V){for(int id:through[cur]){int nx=V+id;Mask bit=Mask(1)<<nx;if(seen&bit)continue;if(exact_path(nx,target,d+1,need,seen|bit))return true;}}
  else {const Line&e=lines[cur-V];for(int nx:e){Mask bit=Mask(1)<<nx;if(seen&bit)continue;if(nx==target&&d+1!=need)continue;if(exact_path(nx,target,d+1,need,seen|bit))return true;}}
  return false;
 }
 template<class Cache> bool closes8(const Line&e,Cache&cache)const{for(int i=0;i<3;i++)for(int j=i+1;j<3;j++){int a=e[i],b=e[j];signed char&z=cache[a][b];if(z<0){bool q=exact_path(a,b,0,6,Mask(1)<<a);z=cache[b][a]=(signed char)q;}if(z)return true;}return false;}
 void halves(int cur,int d,Mask seen,std::vector<Half>&out)const{
  if(d==7){out.push_back({(unsigned char)cur,seen});return;}
  if(cur<V){for(int id:through[cur]){int nx=V+id;Mask bit=Mask(1)<<nx;if(seen&bit)continue;halves(nx,d+1,seen|bit,out);}}
  else {for(int nx:lines[cur-V]){Mask bit=Mask(1)<<nx;if(seen&bit)continue;halves(nx,d+1,seen|bit,out);}}
 }
 bool path14_pair(int a,int b)const{
  std::vector<Half>L,R;L.reserve(192);R.reserve(192);halves(a,0,Mask(1)<<a,L);halves(b,0,Mask(1)<<b,R);std::array<std::vector<Mask>,2*V> by;for(const auto&h:L)by[h.endpoint].push_back(h.mask);for(const auto&h:R){Mask mid=Mask(1)<<h.endpoint;for(Mask lm:by[h.endpoint])if((lm&h.mask)==mid)return true;}return false;
 }
 template<class Cache> bool closes16(const Line&e,Cache&cache)const{for(int i=0;i<3;i++)for(int j=i+1;j<3;j++){int a=e[i],b=e[j];signed char&z=cache[a][b];if(z<0){bool q=path14_pair(a,b);z=cache[b][a]=(signed char)q;}if(z)return true;}return false;}
 std::array<int,10> root_key(int t)const{
  bool reflect=t>=5;int rot=reflect?t-5:t;std::array<int,5> old_to_new{};
  for(int old=0;old<5;old++)old_to_new[old]=reflect?((rot-old)%5+5)%5:(old+rot)%5;
  std::array<int,5> new_to_old{};for(int old=0;old<5;old++)new_to_old[old_to_new[old]]=old;
  std::array<int,5> edge_to_new{};
  for(int oldedge=0;oldedge<5;oldedge++){int a=old_to_new[oldedge],b=old_to_new[(oldedge+1)%5];for(int ne=0;ne<5;ne++)if((a==ne&&b==(ne+1)%5)||(b==ne&&a==(ne+1)%5)){edge_to_new[oldedge]=ne;break;}}
  std::array<int,5> completion{};completion.fill(-1);for(int p=0;p<5;p++)for(int id:through[p])if(id>=5){completion[p]=id;break;}
  std::array<int,V> pattern{};
  for(int newp=0;newp<5;newp++){int oldp=new_to_old[newp];int id=completion[oldp];if(id<0){fprintf(stderr,"missing completion block in canonical key\n");exit(2);}for(int x:lines[id])if(x>=10)pattern[x]|=(1<<newp);}
  std::array<int,10> key{};int z=0;
  for(int newp=0;newp<5;newp++){int oldp=new_to_old[newp],a=999,b=999;for(int x:lines[completion[oldp]])if(x!=oldp){int code;if(x<5)code=32+old_to_new[x];else if(x<10)code=32+5+edge_to_new[x-5];else code=pattern[x];if(code<a){b=a;a=code;}else b=code;}key[z++]=a;key[z++]=b;}
  return key;
 }
 bool canonical_root()const{auto k0=root_key(0);for(int t=1;t<10;t++)if(root_key(t)<k0)return false;return true;}
 Counts verify_subtree(int p,int lastq,int lastr){Counts local;subtree_rec(p,lastq,lastr,local);return local;}
 void subtree_rec(int p,int lastq,int lastr,Counts&c){
  c.states++;while(p<introduced&&degree[p]==3){p++;lastq=lastr=-1;}if(p>=introduced){if((int)lines.size()==introduced)c.completions++;return;}if((int)lines.size()>=V)return;
  std::array<std::array<signed char,V>,V> c8cache,c16cache;for(auto&x:c8cache)x.fill(-1);for(auto&x:c16cache)x.fill(-1);
  int old=introduced;std::vector<int> vals;for(int q=p+1;q<old;q++)if(degree[q]<3&&!together[p].test(q))vals.push_back(q);if(old<V)vals.push_back(old);if(old+1<V)vals.push_back(old+1);
  for(size_t i=0;i<vals.size();i++)for(size_t j=i+1;j<vals.size();j++){int q=vals[i],rr=vals[j];if(rr==old+1&&q!=old)continue;if(lastq>=0&&(q<lastq||(q==lastq&&rr<=lastr)))continue;c.attempted++;Line e{p,q,rr};int outcome;if(structural(e,old)){c.structural++;outcome=0;}else if(closes8(e,c8cache)){c.c8++;outcome=1;}else if(closes16(e,c16cache)){c.c16++;outcome=2;}else{c.accepted++;outcome=3;}if(outcome==3){int next=old;if(q==old||rr==old)next++;if(rr==old+1)next++;int save=introduced;introduced=next;insert(e);subtree_rec(p,q,rr,c);erase();introduced=save;}}
 }
 void prefix_rec(int p,int lastq,int lastr,bool oriented){
  while(p<introduced&&degree[p]==3){p++;lastq=lastr=-1;}bool counted=false;
  if(!oriented&&p>=5){prefix.states++;counted=true;if(!canonical_root()){prefix.rootprune++;return;}oriented=true;}
  if(oriented&&(int)lines.size()>=TASK_DEPTH){uint64_t id=task_count++;if((int)(id%W)==worker){assigned++;Counts stored=r.next(id);Counts actual=verify_subtree(p,lastq,lastr);if(!actual.same_record(stored)){fprintf(stderr,"counter mismatch task=%llu\nstored states=%llu attempted=%llu structural=%llu c8=%llu c16=%llu accepted=%llu completions=%llu\nactual states=%llu attempted=%llu structural=%llu c8=%llu c16=%llu accepted=%llu completions=%llu\n",(unsigned long long)id,(unsigned long long)stored.states,(unsigned long long)stored.attempted,(unsigned long long)stored.structural,(unsigned long long)stored.c8,(unsigned long long)stored.c16,(unsigned long long)stored.accepted,(unsigned long long)stored.completions,(unsigned long long)actual.states,(unsigned long long)actual.attempted,(unsigned long long)actual.structural,(unsigned long long)actual.c8,(unsigned long long)actual.c16,(unsigned long long)actual.accepted,(unsigned long long)actual.completions);exit(2);}if(actual.completions){fprintf(stderr,"nonzero completion task=%llu\n",(unsigned long long)id);exit(3);}sub+=actual;}return;}
  if(!counted)prefix.states++;if(p>=introduced){if((int)lines.size()==introduced)prefix.completions++;return;}if((int)lines.size()>=V)return;
  std::array<std::array<signed char,V>,V> c8cache,c16cache;for(auto&x:c8cache)x.fill(-1);for(auto&x:c16cache)x.fill(-1);
  int old=introduced;std::vector<int>vals;for(int q=p+1;q<old;q++)if(degree[q]<3&&!together[p].test(q))vals.push_back(q);if(old<V)vals.push_back(old);if(old+1<V)vals.push_back(old+1);
  for(size_t i=0;i<vals.size();i++)for(size_t j=i+1;j<vals.size();j++){int q=vals[i],rr=vals[j];if(rr==old+1&&q!=old)continue;if(lastq>=0&&(q<lastq||(q==lastq&&rr<=lastr)))continue;prefix.attempted++;Line e{p,q,rr};int outcome;if(structural(e,old)){prefix.structural++;outcome=0;}else if(closes8(e,c8cache)){prefix.c8++;outcome=1;}else if(closes16(e,c16cache)){prefix.c16++;outcome=2;}else{prefix.accepted++;outcome=3;}if(outcome==3){int next=old;if(q==old||rr==old)next++;if(rr==old+1)next++;int save=introduced;introduced=next;insert(e);prefix_rec(p,q,rr,oriented);erase();introduced=save;}}
 }
 void run(){insert({0,1,5});insert({1,2,6});insert({2,3,7});insert({3,4,8});insert({0,4,9});prefix_rec(0,-1,-1,false);r.finish();}
};
}
int main(int argc,char**argv){if(argc!=4){fprintf(stderr,"usage: %s WORKER W CERT\n",argv[0]);return 64;}int worker=atoi(argv[1]),W=atoi(argv[2]);if(worker<0||worker>=W||W<1||W>255)return 64;pv::Reader r(argv[3],worker,W);pv::Search s(worker,W,r);auto st=std::chrono::steady_clock::now();s.run();double sec=std::chrono::duration<double>(std::chrono::steady_clock::now()-st).count();printf("ACCEPT V=%d D=%d worker=%d W=%d tasks=%llu assigned=%llu PREFIX states=%llu attempted=%llu structural=%llu c8=%llu c16=%llu accepted=%llu rootprune=%llu completions=%llu SUB states=%llu attempted=%llu structural=%llu c8=%llu c16=%llu accepted=%llu completions=%llu bytes=%llu seconds=%.6f\n",pv::V,TASK_DEPTH,worker,W,(unsigned long long)s.task_count,(unsigned long long)s.assigned,(unsigned long long)s.prefix.states,(unsigned long long)s.prefix.attempted,(unsigned long long)s.prefix.structural,(unsigned long long)s.prefix.c8,(unsigned long long)s.prefix.c16,(unsigned long long)s.prefix.accepted,(unsigned long long)s.prefix.rootprune,(unsigned long long)s.prefix.completions,(unsigned long long)s.sub.states,(unsigned long long)s.sub.attempted,(unsigned long long)s.sub.structural,(unsigned long long)s.sub.c8,(unsigned long long)s.sub.c16,(unsigned long long)s.sub.accepted,(unsigned long long)s.sub.completions,(unsigned long long)r.bytes,sec);return (s.prefix.completions||s.sub.completions)?3:0;}
