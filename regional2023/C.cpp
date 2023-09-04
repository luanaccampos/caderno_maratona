#include<bits/stdc++.h>

using namespace std;

set<int> s;
int res[100001];
int likes[100001];
bool visitado[100001];
vector<int> tree[100001];

void dfs(int r)
{
    visitado[r] = true;
    int temp = -1;
    if(s.lower_bound(likes[r]) != s.end())
    {
        temp=*s.lower_bound(likes[r]);
        s.erase(s.lower_bound(likes[r]));
        s.insert(likes[r]);
    }
    else
        s.insert(likes[r]);
    
    res[r] = max(res[r], (int)s.size());

    for(int v : tree[r])
        if(!visitado[v])
            dfs(v);

    s.erase(likes[r]);
    if(temp!=-1)
        s.insert(temp);
}

int main()
{
    int n, a;
    scanf("%d", &n);

    for(int i = 2; i <= n; i++)
    {
        scanf("%d", &a);
        tree[i].push_back(a);
        tree[a].push_back(i);
    }

    memset(visitado, false, sizeof(visitado));
    memset(res, 0, sizeof(res));

    for(int i = 1; i <= n; i++)
        scanf("%d", &likes[i]);
    
    dfs(1);

    for(int i = 2; i <= n; i++)
        printf("%d ", res[i]);
    
    printf("\n");

    return 0;
}