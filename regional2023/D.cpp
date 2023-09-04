#include<bits/stdc++.h>

using namespace std;

#define inf 0x3f3f3f3f

typedef pair<int, int> ii;

vector<ii> g[301];
vector<ii> arestas;
int dist[301];

priority_queue<ii, vector<ii>, greater<ii> >pq;

bool proibido(int a, int b, int i)
{
    return arestas[i].first == a and arestas[i].second == b;
}

void dijkstra(int r, int i)
{
    memset(dist, inf, sizeof(dist));
    dist[r] = 0;
    pq.push(make_pair(0, r));

    while(!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
    
            
            for(ii x : g[u])
            {
                int v = x.second;
                int w = x.first;

                if(!proibido(u, v, i))
                {
                    if(dist[v] > dist[u] + w)
                    {
                        dist[v] = dist[u] + w;
                        pq.push(make_pair(dist[v], v));
                    }
                }
            }
    }
}

int main()
{
    int n, m, a, b, p;
    scanf("%d %d", &n, &m);

    for(int i = 0; i < m; i++)
    {
        scanf("%d %d %d", &a, &b, &p);
        g[a].push_back(make_pair(p, b));
        g[b].push_back(make_pair(p, a));
        arestas.push_back(make_pair(a, b));
    }

    for(int i = 0; i < m; i++)
    {
        a = arestas[i].first;
        b = arestas[i].second;

        dijkstra(a, i);

        if(dist[b] == inf)
            printf("-1\n");
        else
            printf("%d\n", dist[b]);
    }


    return 0;
}