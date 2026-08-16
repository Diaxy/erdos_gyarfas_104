#include <algorithm>
#include <array>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <chrono>
struct G{
 int m; std::vector<unsigned> masks; std::array<int,16> col{}; std::array<unsigned,16> rows{};
 uint64_t c4free_complete=0,c4c8free_complete=0,nodes=0,prune8=0; FILE*out;
 G(int M,const char*path):m(M){
  for(int a=0;a<m;a++)for(int b=a+1;b<m;b++)for(int c=b+1;c<m;c++)masks.push_back((1u<<a)|(1u<<b)|(1u<<c));
  out=fopen(path,"wb"); if(!out){perror(path);exit(1);} }
 ~G(){if(out)fclose(out);}
 bool path6_cols(int s,int t,int dep) const {
  for(int r1=0;r1<dep;r1++) if((rows[r1]>>s)&1u){
   unsigned c1s=rows[r1]&~(1u<<s);
   while(c1s){int c1=__builtin_ctz(c1s);c1s&=c1s-1;
    for(int r2=0;r2<dep;r2++) if(r2!=r1 && ((rows[r2]>>c1)&1u)){
     unsigned c2s=rows[r2]&~((1u<<c1)|(1u<<s));
     while(c2s){int c2=__builtin_ctz(c2s);c2s&=c2s-1;
      for(int r3=0;r3<dep;r3++) if(r3!=r1 && r3!=r2 && ((rows[r3]>>c2)&1u) && ((rows[r3]>>t)&1u)) return true;
     }
    }
   }
  }
  return false;
 }
 bool createsC8(unsigned r,int dep) const {
  int c[3],k=0; for(int j=0;j<m;j++)if((r>>j)&1u)c[k++]=j;
  for(int a=0;a<3;a++)for(int b=a+1;b<3;b++)if(path6_cols(c[a],c[b],dep))return true;
  return false;
 }
 void rec(int dep,int start){nodes++;int rem=m-dep;
  if(rem==0){for(int j=0;j<m;j++)if(col[j]!=3)return;c4free_complete++;c4c8free_complete++;for(int i=0;i<m;i++){uint16_t x=rows[i];fwrite(&x,sizeof x,1,out);}return;}
  for(int j=0;j<m;j++)if(col[j]+rem<3)return;
  for(int idx=start;idx<(int)masks.size();idx++){
   unsigned r=masks[idx];bool ok=true;
   for(int j=0;j<m;j++)if((r>>j&1)&&col[j]>=3){ok=false;break;} if(!ok)continue;
   for(int i=0;i<dep;i++)if(__builtin_popcount(rows[i]&r)>=2){ok=false;break;} if(!ok)continue;
   if(createsC8(r,dep)){prune8++;continue;}
   for(int j=0;j<m;j++)if(r>>j&1)col[j]++;rows[dep]=r;rec(dep+1,idx);for(int j=0;j<m;j++)if(r>>j&1)col[j]--;
  }
 }
};
int main(int argc,char**argv){if(argc!=3){fprintf(stderr,"usage M OUT\n");return 64;}int m=atoi(argv[1]);auto t=std::chrono::steady_clock::now();G g(m,argv[2]); unsigned root=(1u<<0)|(1u<<1)|(1u<<2); g.rows[0]=root; g.col[0]=g.col[1]=g.col[2]=1; g.rec(1,1);double s=std::chrono::duration<double>(std::chrono::steady_clock::now()-t).count();printf("m=%d order=%d nodes=%llu c4c8free_leftquot=%llu prune8=%llu seconds=%.6f\n",m,2*m,(unsigned long long)g.nodes,(unsigned long long)g.c4c8free_complete,(unsigned long long)g.prune8,s);}
