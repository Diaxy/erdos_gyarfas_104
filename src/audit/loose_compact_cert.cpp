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
namespace egcc {
constexpr int V=SIDE; using Line=std::array<int,3>; using Mask=unsigned __int128;
struct Counts{std::uint64_t states=0,attempted=0,structural=0,c8=0,c16=0,accepted=0,completions=0;};
struct BitWriter{FILE*f=nullptr; unsigned char byte=0; int used=0; std::uint64_t bytes=0; explicit BitWriter(const char*p){f=fopen(p,"wb");if(!f){perror(p);std::exit(90);}unsigned char h[6]={'E','G','L','C',2,(unsigned char)V};if(fwrite(h,1,6,f)!=6)std::exit(91);bytes=6;} void put(unsigned x){byte|=(unsigned char)((x&3u)<<(2*used));used++;if(used==4){if(fputc(byte,f)==EOF)std::exit(91);bytes++;byte=0;used=0;}} void close(){if(used){if(fputc(byte,f)==EOF)std::exit(91);bytes++;}if(fclose(f))std::exit(91);f=nullptr;} ~BitWriter(){if(f)fclose(f);}};
struct Branch{
 std::vector<Line> lines; std::array<std::vector<int>,V> through; std::array<int,V> degree{}; std::array<std::bitset<V>,V> together{}; int introduced=10; Counts c; BitWriter&w;
 explicit Branch(BitWriter&x):w(x){}
 void insert(Line e){int id=lines.size();lines.push_back(e);for(int p:e){degree[p]++;through[p].push_back(id);}for(int i=0;i<3;i++)for(int j=i+1;j<3;j++){together[e[i]].set(e[j]);together[e[j]].set(e[i]);}}
 void erase(){Line e=lines.back();lines.pop_back();for(int p:e){degree[p]--;through[p].pop_back();}for(int i=0;i<3;i++)for(int j=i+1;j<3;j++){together[e[i]].reset(e[j]);together[e[j]].reset(e[i]);}}
 bool path(int cur,int target,int d,int need,Mask seen)const{if(d==need)return cur==target;if(cur==target)return false;if(cur<V){for(int id:through[cur]){int nx=V+id;Mask bit=Mask(1)<<nx;if(seen&bit)continue;if(path(nx,target,d+1,need,seen|bit))return true;}}else{for(int nx:lines[cur-V]){Mask bit=Mask(1)<<nx;if(seen&bit)continue;if(nx==target&&d+1!=need)continue;if(path(nx,target,d+1,need,seen|bit))return true;}}return false;}
 bool closes(const Line&e,int need)const{for(int i=0;i<3;i++)for(int j=i+1;j<3;j++)if(path(e[i],e[j],0,need,Mask(1)<<e[i]))return true;return false;}
 bool bad(const Line&e,int old)const{for(int p:e)if(p<old&&degree[p]>=3)return true;for(int i=0;i<3;i++)for(int j=i+1;j<3;j++)if(e[i]<old&&e[j]<old&&together[e[i]].test(e[j]))return true;return false;}
 void rec(int p,int lq,int lr){c.states++;while(p<introduced&&degree[p]==3){p++;lq=lr=-1;}if(p>=introduced){if((int)lines.size()==introduced)c.completions++;return;}if((int)lines.size()>=V)return;int old=introduced;std::vector<int>vals;for(int q=p+1;q<old;q++)if(degree[q]<3&&!together[p].test(q))vals.push_back(q);if(old<V)vals.push_back(old);if(old+1<V)vals.push_back(old+1);for(size_t i=0;i<vals.size();i++)for(size_t j=i+1;j<vals.size();j++){int q=vals[i],r=vals[j];if(r==old+1&&q!=old)continue;if(lq>=0&&(q<lq||(q==lq&&r<=lr)))continue;c.attempted++;Line e{p,q,r};unsigned out;if(bad(e,old)){out=0;c.structural++;}else if(closes(e,6)){out=1;c.c8++;}else if(closes(e,14)){out=2;c.c16++;}else{out=3;c.accepted++;}w.put(out);if(out==3){int next=old;if(q==old||r==old)next++;if(r==old+1)next++;int save=introduced;introduced=next;insert(e);rec(p,q,r);erase();introduced=save;}}}
 Counts run(){insert({0,1,5});insert({1,2,6});insert({2,3,7});insert({3,4,8});insert({0,4,9});rec(0,-1,-1);return c;}
};}
int main(int argc,char**argv){if(argc!=2){std::fprintf(stderr,"usage: %s CERT\n",argv[0]);return 64;}auto st=std::chrono::steady_clock::now();egcc::BitWriter w(argv[1]);egcc::Branch b(w);auto c=b.run();w.close();double s=std::chrono::duration<double>(std::chrono::steady_clock::now()-st).count();std::printf("V=%d states=%llu attempted=%llu structural=%llu c8=%llu c16=%llu accepted=%llu completions=%llu bytes=%llu seconds=%.6f\n",egcc::V,(unsigned long long)c.states,(unsigned long long)c.attempted,(unsigned long long)c.structural,(unsigned long long)c.c8,(unsigned long long)c.c16,(unsigned long long)c.accepted,(unsigned long long)c.completions,(unsigned long long)w.bytes,s);return c.completions?2:0;}
