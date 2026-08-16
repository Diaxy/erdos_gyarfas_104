#include <algorithm>
#include <array>
#include <bitset>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <unordered_set>
#include <vector>
#include <chrono>

struct Census {
 int m; std::vector<unsigned> masks; std::vector<std::vector<unsigned char>> maps; std::vector<std::array<int,8>> perms;
 std::array<int,8> col{}; std::array<unsigned char,8> rows{}; uint64_t row_multisets=0;
 std::unordered_set<std::string> reps;
 Census(int M):m(M){
  for(int a=0;a<m;a++)for(int b=a+1;b<m;b++)for(int c=b+1;c<m;c++)masks.push_back((1u<<a)|(1u<<b)|(1u<<c));
  std::array<int,8> p{};for(int i=0;i<m;i++)p[i]=i;
  do {perms.push_back(p);} while(std::next_permutation(p.begin(),p.begin()+m));
  maps.resize(perms.size(), std::vector<unsigned char>(1u<<m));
  for(size_t z=0;z<perms.size();z++)for(unsigned x=0;x<(1u<<m);x++){unsigned y=0;for(int j=0;j<m;j++)if(x>>j&1)y|=1u<<perms[z][j];maps[z][x]=(unsigned char)y;}
 }
 std::string half(const std::array<unsigned char,8>& rr){
  std::array<unsigned char,8> t{}; std::string best; bool first=true;
  for(auto &mp:maps){for(int i=0;i<m;i++)t[i]=mp[rr[i]];std::sort(t.begin(),t.begin()+m);std::string s((char*)t.data(),m);if(first||s<best){best=s;first=false;}}
  return best;
 }
 std::string canon(){
  auto a=half(rows); std::array<unsigned char,8> tr{};
  for(int j=0;j<m;j++){unsigned x=0;for(int i=0;i<m;i++)if(rows[i]>>j&1)x|=1u<<i;tr[j]=(unsigned char)x;}std::sort(tr.begin(),tr.begin()+m);
  auto save=rows;rows=tr;auto b=half(rows);rows=save;return std::min(a,b);
 }
 void rec(int depth,int start){
  int rem=m-depth;if(rem==0){for(int j=0;j<m;j++)if(col[j]!=3)return;row_multisets++;reps.insert(canon());return;}
  for(int j=0;j<m;j++)if(col[j]>3||col[j]+rem<3)return;
  for(int idx=start;idx<(int)masks.size();idx++){
   unsigned x=masks[idx]; bool ok=true;for(int j=0;j<m;j++)if((x>>j&1)&&col[j]>=3){ok=false;break;}if(!ok)continue;
   for(int j=0;j<m;j++)if(x>>j&1)col[j]++;
   rows[depth]=(unsigned char)x;rec(depth+1,idx);
   for(int j=0;j<m;j++)if(x>>j&1)col[j]--;
  }
 }
};

bool has_cycle(const std::vector<uint32_t>& adj,int k){int n=adj.size();
 for(int s=0;s<n;s++){
  auto dfs=[&](auto&& self,int v,int d,uint32_t seen)->bool{
   if(d==k)return (adj[v]>>s)&1u;
   uint32_t nb=adj[v]&~seen; nb &= ~((1u<<s)-1u); nb &= ~(1u<<s);
   while(nb){int w=__builtin_ctz(nb);nb&=nb-1;if(self(self,w,d+1,seen|(1u<<w)))return true;}return false;};
  if(dfs(dfs,s,1,1u<<s))return true;
 }return false;}

struct C10Info{char cls='B';int cycles=0;std::array<int,6> hist{};bool bad=false;};
C10Info c10info(const std::vector<uint32_t>& adj){int n=adj.size(); C10Info z; bool loose=false;
 for(int s=0;s<n;s++){
  std::array<int,10> path{};path[0]=s;
  auto dfs=[&](auto&& self,int v,int d,uint32_t seen)->void{
   if(d==10){if(!((adj[v]>>s)&1u))return; if(path[1]>path[9])return;
    z.cycles++; uint32_t S=0;for(int i=0;i<10;i++)S|=1u<<path[i];int e=0;for(int i=0;i<10;i++)e+=__builtin_popcount(adj[path[i]]&S);e/=2;int ch=e-10;if(ch>=0&&ch<(int)z.hist.size())z.hist[ch]++;else z.bad=true;if(ch==0)loose=true;if(ch>1)z.bad=true;return;}
   uint32_t nb=adj[v]&~seen; nb &= ~((1u<<s)-1u); nb &= ~(1u<<s);
   while(nb){int w=__builtin_ctz(nb);nb&=nb-1;path[d]=w;self(self,w,d+1,seen|(1u<<w));}
  };
  dfs(dfs,s,1,1u<<s);
 }
 z.cls=z.cycles==0?'B':(loose?'A':'C');return z;}

std::vector<uint32_t> adj_from(const std::string& key,int m){std::vector<uint32_t>a(2*m);for(int i=0;i<m;i++){unsigned r=(unsigned char)key[i];for(int j=0;j<m;j++)if(r>>j&1){a[i]|=1u<<(m+j);a[m+j]|=1u<<i;}}return a;}
int main(int argc,char**argv){int maxm=argc>1?atoi(argv[1]):8;for(int m=3;m<=maxm;m++){auto st=std::chrono::steady_clock::now();Census c(m);c.rec(0,0);uint64_t c4f=0,c4c8=0,surv=0,bad=0;uint64_t class48[3]={},classsurv[3]={};
  for(auto&k:c.reps){auto a=adj_from(k,m);bool q4=has_cycle(a,4),q8=has_cycle(a,8),q16=(2*m>=16&&has_cycle(a,16));auto x=c10info(a);if(x.bad)bad++;if(!q4)c4f++;if(!q4&&!q8){c4c8++;int id=x.cls=='A'?0:x.cls=='B'?1:2;class48[id]++;}if(!q4&&!q8&&!q16){surv++;int id=x.cls=='A'?0:x.cls=='B'?1:2;classsurv[id]++;}}
 double sec=std::chrono::duration<double>(std::chrono::steady_clock::now()-st).count();
 printf("m=%d order=%d row_multisets=%llu unlabeled=%zu c4free=%llu c4c8free=%llu A48=%llu B48=%llu C48=%llu survivors=%llu As=%llu Bs=%llu Cs=%llu badC10=%llu seconds=%.6f\n",m,2*m,(unsigned long long)c.row_multisets,c.reps.size(),(unsigned long long)c4f,(unsigned long long)c4c8,(unsigned long long)class48[0],(unsigned long long)class48[1],(unsigned long long)class48[2],(unsigned long long)surv,(unsigned long long)classsurv[0],(unsigned long long)classsurv[1],(unsigned long long)classsurv[2],(unsigned long long)bad,sec);fflush(stdout);
 }
}
