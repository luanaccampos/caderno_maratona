#include<bits/stdc++.h>

using namespace std;
typedef pair<int, int> ii;

map<ii, int> ids;


struct pt {
    double x, y;
};

vector<pt> a;

int orientation(pt a, pt b, pt c) {
    double v = a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y);
    if (v < 0) return -1; // clockwise
    if (v > 0) return +1; // counter-clockwise
    return 0;
}

bool cw(pt a, pt b, pt c, bool include_collinear) {
    int o = orientation(a, b, c);
    return o < 0 || (include_collinear && o == 0);
}
bool ccw(pt a, pt b, pt c, bool include_collinear) {
    int o = orientation(a, b, c);
    return o > 0 || (include_collinear && o == 0);
}

bool cmp(pt a, pt b)
{
    if(a.x < b.x)
        return true;
    else if(a.x == b.x)
    {
        return a.y < b.y;
    }

    return false;
}

void convex_hull(bool include_collinear = false) {
    if (a.size() == 1)
        return;

    sort(a.begin(), a.end(), cmp);

    pt p1 = a[0], p2 = a.back();
    vector<pt> up, down;
    up.push_back(p1);
    down.push_back(p1);
    for (int i = 1; i < (int)a.size(); i++) {
        if (i == a.size() - 1 || cw(p1, a[i], p2, include_collinear)) {
            while (up.size() >= 2 && !cw(up[up.size()-2], up[up.size()-1], a[i], include_collinear))
                up.pop_back();
            up.push_back(a[i]);
        }
        if (i == a.size() - 1 || ccw(p1, a[i], p2, include_collinear)) {
            while (down.size() >= 2 && !ccw(down[down.size()-2], down[down.size()-1], a[i], include_collinear))
                down.pop_back();
            down.push_back(a[i]);
        }
    }

    if (include_collinear && up.size() == a.size()) {
        reverse(a.begin(), a.end());
        return;
    }
    a.clear();
    for (int i = 0; i < (int)up.size(); i++)
        a.push_back(up[i]);
    for (int i = down.size() - 2; i > 0; i--)
        a.push_back(down[i]);
}

int main()
{
    int n;
    pt p;

    scanf("%d", &n);

    for(int i = 1; i <= n; i++)
    {
        scanf("%lf %lf", &p.x, &p.y);
        a.push_back(p);
        ids[make_pair(p.x, p.y)] = i;
    }

    convex_hull(true);
    vector<int> ans;

    for(int i = 0; i < a.size(); i++)
        ans.push_back(ids[make_pair(a[i].x, a[i].y)]);
    
    sort(ans.begin(), ans.end());

    for(int i = 0; i < a.size(); i++)
        printf("%d ", ans[i]);
    
    printf("\n");

    return 0;
}