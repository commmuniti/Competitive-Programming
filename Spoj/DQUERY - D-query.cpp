/*
*  Author : pritish.thakkar 
*/

#include<bits/stdc++.h>
#define         pb                      push_back
#define         mkp                     make_pair
#define         inf                     1000000007
#define         rep(i,n)                for(int i=0;i<n;i++)
#define         fr                      first
#define         sc                      second
#define         clr(a)                  memset(a,0LL,sizeof a);
#define         pi                      3.141592653589793
#define         gc                      getchar
#define         all(v)                  v.begin(), v.end()
#define         filein                  freopen("input.in" , "r" , stdin)
#define         fileout                 freopen("output.in" , "w" , stdout)
#define         TEST                    ll t; cin >> t; while(t--)
#define         NTEST                   ll t; t = 1;    while(t--)
#define         sz(x)                   x.size()
using           namespace               std;

typedef         unsigned long long      ull;
typedef         long long               ll;
typedef         vector<ll>              vi;
typedef         pair<ll,ll>             ii;
typedef         vector<ii>              vii;
typedef         set<ll>::iterator       sit;
typedef         map<ll,ll>::iterator    mit;
typedef         vector<int>::iterator   vit;

template<class T>inline bool read(T &x){int c=gc();int sgn=1;while(~c&&c<'0'||c>'9'){if(c=='-')sgn=-1;c=gc();}for(x=0;~c&&'0'<=c&&c<='9';c=gc())x=x*10+c-'0';x*=sgn;return ~c;}

//_____________________________

bool isUpper(char c) {return (c >= 'A' && c <= 'Z');}
bool isLower(char c) {return (c >= 'a' && c <= 'z');}
bool iplpha(char c) {return (c >= 'A' && c <= 'Z')||(c >= 'a' && c <= 'z');}
bool iplnum(char c) {return (c >= 'A' && c <= 'Z')||(c >= 'a' && c <= 'z')||(c >= '0' && c <= '9');}
char toUpper(char c){return isUpper(c)?c:c-'a'+'A';}
char toLower(char c){return isLower(c)?c:c+'a'-'A';}
template<typename t> t gcd(t a, t b){return ((b == 0) ? a : gcd(b, a%b));} 
template<typename t> t lcm(t a, t b){return (a * (b / gcd(a, b)));}

ll modpow(ll base, ll expo, ll mod){
    base  = base % mod;
    ll ret = 1LL;while(expo > 0){
        if(expo & 1LL){ret =( ret * base) % mod;}
        base = (base * base )% mod;expo >>= 1LL;
    }
    return ret;
}

bool p[10000001];
vi primes;
void sieve(ll n){
    memset(p,1,sizeof p);
    p[0] = p[1] = 0;
    for(int i = 2 ; i <= sqrt(n) ; i++){
        if(p[i]){
            for(int j = i * i ; j < n ; j+=i){p[j] = 0;}
        }
    }
    for(int i = 2 ; i <= n ; i ++){if(p[i]){primes.pb(i);}}
}

bool isPrime(ll n){
    if(n < 1000001){
        return p[n];
    }
    ll ans = 0;
    for(int i= 0 ; i < primes.size() && primes[i] * primes[i] <= n  ; i ++){
        if(n % primes[i] == 0){return 0;}
    }return 1;
}

ll phi(ll n){
    ll ans = n;
    vi v;
    v.clear();
    for(int i = 0; i < primes.size() && primes[i] * primes[i] <= n; i ++){
        if(n % primes[i] == 0){
            v.push_back(primes[i]);
            while(n % primes[i] == 0){
                n /= primes[i];
            }
        }
    }
    if(n != 1){
        v.push_back(n);}
    for(int i = 0 ; i < v.size() ; i ++){
        ans = ans - ans / v[i];
    }
    return ans;
}

ull nCr(ll n, ll r){
    if(r > n / 2){
        r = n - r;
    }
    ull ret = 1;
    for(ll i = 1 ; i<= r ; i ++){
        ret *=  (n - r + i);
        ret /= i;
    }
    return ret;
}

template<class T >
string toString(T n){
    string v = "";
    while(n){
        v.pb(n % 10 + '0');
        n /= 10;
    }
    reverse(all(v));
    return v;
}

ll toInt(string s){
    ll ret = 0;
    for(int i = 0 ; i < s.size() ; i ++){
        ret = ret * 10 + (s[i] - '0');
    }
    return ret;
}

//__________________________________

ll BLOCK;

struct data{
    ll index, left, right; 
};

bool comp(data a, data b){
    if(a.left/BLOCK != b.left/BLOCK)
        return (a.left/BLOCK < b.left/BLOCK);
    return (a.right < b.right);
}

void solve(){  
    int f[1111111];
    NTEST{
        memset(f, 0, sizeof(f));
        ll n;
        read(n);
        ll i;
        ll a[n];
        rep(i,n){
            read(a[i]);
        }   
        ll q;
        read(q);
        BLOCK = sqrt(n);
        data d[q];
        rep(i, q){
            read(d[i].left);
            read(d[i].right);
            d[i].left--;
            d[i].right--;
            d[i].index = i;
        }
        sort(d, d + q, comp);
        ll nowlo = 0, nowhi = 0;
        ii Q[q];
        ll ans = 0;
        for(int i = 0 ; i < q ; i ++){
            ll lo, hi;
            lo = d[i].left;
            hi = d[i].right;
            while(lo < nowlo){
                f[a[nowlo-1]]++;
                if(f[a[nowlo-1]] == 1){
                    ans++;
                }
                nowlo--;
            }
            while(nowlo < lo){
                f[a[nowlo]]--;
                if(f[a[nowlo]] == 0){
                    ans--;
                }
                nowlo++;
            }
            while(nowhi <= hi){
                f[a[nowhi]]++;
                if(f[a[nowhi]] == 1){
                    ans++;
                }
                nowhi++;
            }
            while(nowhi > hi + 1){
                f[a[nowhi-1]]--;
                if(f[a[nowhi-1]] == 0){
                    ans--;
                }
                nowhi--;
            }
            Q[i] = ii((ll)d[i].index, (ll)ans);
        }
        sort(Q, Q + q);
        rep(i, q){
            printf("%lld\n" , Q[i].sc);
        }
    }
}

//________________________________

int main(int argc, char *argv[]){
    std::ios::sync_with_stdio(0);
    // filein; fileout;
    solve();
}
 
 
