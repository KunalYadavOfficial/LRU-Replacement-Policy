
#include <bits/stdc++.h>
using namespace std;
#define ll              long long int
#define ld              long double
#define mod             1000000007
#define inf             1e18
#define endl            "\n"
#define pb              push_back
#define vi              vector<ll>
#define vs              vector<string>
#define pii             pair<ll,ll>
#define ump             unordered_map
#define mp              make_pair
#define pq_max          priority_queue<ll>
#define pq_min          priority_queue<ll,vi,greater<ll> >
#define all(n)          n.begin(),n.end()
#define ff              first
#define ss              second
#define mid(l,r)        (l+(r-l)/2)
#define bitc(n)         __builtin_popcount(n)
#define loop(i,a,b)     for(int i=(a);i<=(b);i++)
#define looprev(i,a,b)  for(int i=(a);i>=(b);i--)
#define iter(container, it) for(__typeof(container.begin()) it = container.begin(); it != container.end(); it++)
#define log(args...)    { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
#define logarr(arr,a,b) for(int z=(a);z<=(b);z++) cout<<(arr[z])<<" ";cout<<endl;   
template <typename T> T gcd(T a, T b){if(a%b) return gcd(b,a%b);return b;}
template <typename T> T lcm(T a, T b){return (a*(b/gcd(a,b)));}
vs tokenizer(string str,char ch) {std::istringstream var((str)); vs v; string t; while(getline((var), t, (ch))) {v.pb(t);} return v;}


void err(istream_iterator<string> it) {}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
    cout << *it << " = " << a << endl;
    err(++it, args...);
}

void debugMode() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif // ONLINE_JUDGE
}
struct hash_pair {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const
    {
        auto hash1 = hash<T1>{}(p.first);
        auto hash2 = hash<T2>{}(p.second);
        return hash1 ^ hash2;
    }
};


class DLLNode
{
public:
    int key;
    int value;
    DLLNode* next;
    DLLNode* prev;
    DLLNode(int k,int v)
    {
        this->key = k;
        this->value = v;
        this->next=NULL;
        this->prev=NULL;
    }
};

DLLNode* head = new DLLNode(-1,-1);
DLLNode* tail = new DLLNode(-1,-1);
ump<int,DLLNode *> cache;
int size;
int capacity;


void AddToHead(DLLNode* node)
{
    node->next = head->next;
    node->next->prev = node;
    head->next = node;
    node->prev = head;
    return;
}
void RemoveNode(DLLNode * node)
{
    /*node->prev->next=node->next;
   node->next->prev = node->prev;*/

   DLLNode *prev = node->prev;
   DLLNode *next = node->next;
   prev->next = next;
   next->prev = prev;
}
void MoveToHead(DLLNode* node)
{
    cout<<"Moving the key:"<<node->key<<" to Head\n";
   RemoveNode(node);
   AddToHead(node);

}

int RemoveFromTail()
{
    DLLNode * temp = tail->prev;
    RemoveNode(temp);
    return temp->key;
}
int get(int k)
{
    if(cache.count(k)==0){
        cout<<"Given key is not present in the cache\n";
        return INT_MIN;
    }
    else
    {
        DLLNode* node= cache[k];
        MoveToHead(node);
        return node->value;
    }

}

void put(int k,int v)
{
   if(cache.count(k)==0)
   {
    DLLNode *node = new DLLNode(k,v);
    cache[k]=node;
    cout<<"Added a key "<<k<<endl;
    AddToHead(node);
    capacity++;
    if(capacity>size)
    {
        int removedkey = RemoveFromTail();
        cout<<"Key: "<<removedkey<<" Removed from Cache\n";
        capacity--;
        cache.erase(removedkey);
    }
   }
   else
   {
    DLLNode * node = cache[k];
    //MoveToHead(node);
    //RemoveNode(node);
    MoveToHead(node);
   } 
}




int main()
{
    clock_t begin = clock();
    debugMode();
    head->next = tail;
    tail->prev = head;
    cout<<"enter cache size \n";
    cin>>size;
    cout<<"Size of cache is:"<<size<<"\n";
    cout<<"enter the queries-->p for put and g for get\n";
    int q;
    cin>>q;
    while(q--)
    {
        char type;
        cin>>type;
        int k,v;
        if(type=='g')
        {
            int k;
            cin>>k;
            int value = get(k);
            cout<<"Value at key:"<<k<<" is: "<<value<<"\n";
        }
        else
        {
            cin>>k>>v;
            put(k,v);
        }

    }

    #ifndef ONLINE_JUDGE 
      clock_t end = clock();
      cout<<"\n\nExecuted In: "<<double(end - begin) / CLOCKS_PER_SEC*1000<<" ms";
    #endif
    
    
    return 0;
    
}