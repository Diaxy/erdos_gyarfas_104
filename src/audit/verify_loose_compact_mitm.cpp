#include <array>
#include <bitset>
#include <chrono>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>
#ifndef SIDE
#define SIDE 35
#endif
namespace egcv {
constexpr int V=SIDE; static_assert(2*V<=128); using Line=std::array<int,3>; using Mask=unsigned __int128;
struct Counts{std::uint64_t states=0,attempted=0,structural=0,c8=0,c16=0,accepted=0,completions=0;}; struct HP{unsigned char endpoint;Mask mask;};
struct BitReader{FILE*f=nullptr;unsigned char byte=0;int used=4;std::uint64_t bytes=0;explicit BitReader(const char*p){f=fopen(p,"rb");if(!f){perror(p);std::exit(66);}unsigned char got[6];if(fread(got,1,6,f)!=6){std::fprintf(stderr,"truncated header\n");std::exit(2);}bytes=6;unsigned char exp[6]={'E','G','L','C',2,(unsigned char)V};for(int i=0;i<6;i++)if(got[i]!=exp[i]){std::fprintf(stderr,"bad header byte %d\n",i);std::exit(2);}}unsigned get(){if(used==4){int x=fgetc(f);if(x==EOF){std::fprintf(stderr,"truncated certificate after %llu bytes\n",(unsigned long long)bytes);std::exit(2);}byte=(unsigned char)x;bytes++;used=0;}unsigned x=(byte>>(2*used))&3u;used++;return x;}void finish(){if(used<4){unsigned shift=2*used;unsigned mask=(0xffu<<shift)&0xffu;if(byte&mask){std::fprintf(stderr,"nonzero padding\n");std::exit(2);}}if(fgetc(f)!=EOF){std::fprintf(stderr,"trailing data\n");std::exit(2);}}~BitReader(){if(f)fclose(f);}};
struct Branch{
 std::vector<Line> lines;std::array<std::vector<int>,V>through;std::array<int,V>degree{};std::array<std::bitset<V>,V>together{};int introduced=10;Counts c;BitReader&r;explicit Branch(BitReader&x):r(x){}
 void insert(Line e){int id=lines.size();lines.push_back(e);for(int p:e){degree[p]++;through[p].push_back(id);}for(int i=0;i<3;i++)for(int j=i+1;j<3;j++){together[e[i]].set(e[j]);together[e[j]].set(e[i]);}}
 void erase(){Line e=lines.back();lines.pop_back();for(int p:e){degree[p]--;through[p].pop_back();}for(int i=0;i<3;i++)for(int j=i+1;j<3;j++){together[e[i]].reset(e[j]);together[e[j]].reset(e[i]);}}
 bool exact_path(int cur,int target,int d,int need,Mask seen)const{if(d==need)return cur==target;if(cur==target)return false;if(cur<V){for(int id:through[cur]){int nx=V+id;Mask bit=Mask(1)<<nx;if(seen&bit)continue;if(exact_path(nx,target,d+1,need,seen|bit))return true;}}else{for(int nx:lines[cur-V]){Mask bit=Mask(1)<<nx;if(seen&bit)continue;if(nx==target&&d+1!=need)continue;if(exact_path(nx,target,d+1,need,seen|bit))return true;}}return false;}
 bool closes8(const Line&e)const{for(int i=0;i<3;i++)for(int j=i+1;j<3;j++)if(exact_path(e[i],e[j],0,6,Mask(1)<<e[i]))return true;return false;}
 void halves(int cur,int d,Mask mask,std::vector<HP>&out)const{if(d==7){out.push_back({(unsigned char)cur,mask});return;}if(cur<V){for(int id:through[cur]){int nx=V+id;Mask bit=Mask(1)<<nx;if(mask&bit)continue;halves(nx,d+1,mask|bit,out);}}else{for(int nx:lines[cur-V]){Mask bit=Mask(1)<<nx;if(mask&bit)continue;halves(nx,d+1,mask|bit,out);}}}
 bool p14(int x,int y)const{std::vector<HP>L,R;L.reserve(192);R.reserve(192);halves(x,0,Mask(1)<<x,L);halves(y,0,Mask(1)<<y,R);std::array<std::vector<Mask>,2*V>by;for(auto&h:L)by[h.endpoint].push_back(h.mask);for(auto&h:R){Mask mid=Mask(1)<<h.endpoint;for(Mask lm:by[h.endpoint])if((lm&h.mask)==mid)return true;}return false;}
 bool closes16(const Line&e)const{for(int i=0;i<3;i++)for(int j=i+1;j<3;j++)if(p14(e[i],e[j]))return true;return false;}
 bool bad(const Line&e,int old)const{for(int p:e)if(p<old&&degree[p]>=3)return true;for(int i=0;i<3;i++)for(int j=i+1;j<3;j++)if(e[i]<old&&e[j]<old&&together[e[i]].test(e[j]))return true;return false;}
 [[noreturn]] void mismatch(std::uint64_t idx,unsigned got,unsigned exp)const{std::fprintf(stderr,"outcome mismatch candidate=%llu got=%u expected=%u\n",(unsigned long long)idx,got,exp);std::exit(2);}
 void rec(int p,int lq,int lr){c.states++;while(p<introduced&&degree[p]==3){p++;lq=lr=-1;}if(p>=introduced){if((int)lines.size()==introduced)c.completions++;return;}if((int)lines.size()>=V)return;int old=introduced;std::vector<int>vals;for(int q=p+1;q<old;q++)if(degree[q]<3&&!together[p].test(q))vals.push_back(q);if(old<V)vals.push_back(old);if(old+1<V)vals.push_back(old+1);for(size_t i=0;i<vals.size();i++)for(size_t j=i+1;j<vals.size();j++){int q=vals[i],rr=vals[j];if(rr==old+1&&q!=old)continue;if(lq>=0&&(q<lq||(q==lq&&rr<=lr)))continue;std::uint64_t idx=c.attempted++;Line e{p,q,rr};unsigned exp;if(bad(e,old)){exp=0;c.structural++;}else if(closes8(e)){exp=1;c.c8++;}else if(closes16(e)){exp=2;c.c16++;}else{exp=3;c.accepted++;}unsigned got=r.get();if(got!=exp)mismatch(idx,got,exp);if(exp==3){int next=old;if(q==old||rr==old)next++;if(rr==old+1)next++;int save=introduced;introduced=next;insert(e);rec(p,q,rr);erase();introduced=save;}}}
 Counts run(){insert({0,1,5});insert({1,2,6});insert({2,3,7});insert({3,4,8});insert({0,4,9});rec(0,-1,-1);r.finish();return c;}
};}
int main(int argc,char**argv){if(argc!=2){std::fprintf(stderr,"usage: %s CERT\n",argv[0]);return 64;}auto st=std::chrono::steady_clock::now();egcv::BitReader r(argv[1]);egcv::Branch b(r);auto c=b.run();double s=std::chrono::duration<double>(std::chrono::steady_clock::now()-st).count();std::printf("ACCEPT V=%d states=%llu attempted=%llu structural=%llu c8=%llu c16=%llu accepted=%llu completions=%llu bytes=%llu seconds=%.6f\n",egcv::V,(unsigned long long)c.states,(unsigned long long)c.attempted,(unsigned long long)c.structural,(unsigned long long)c.c8,(unsigned long long)c.c16,(unsigned long long)c.accepted,(unsigned long long)c.completions,(unsigned long long)r.bytes,s);return c.completions?3:0;}
