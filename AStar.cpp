/*
********渣实现。。。
********
********
*/
#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <memory>
using namespace std;
const int maxW = 10;
const int maxH = 10;
const int cost = 10;

struct point{
    point* parent;
    int x,y;
    int f,g,h;
    point(int tx = 0, int ty = 0):x(tx), y(ty), parent(nullptr){
        f = g = h = 0;
    }
    void calcF(){
        f = g + h;
    }
    bool operator< (const point &o) const {
        return f < o.f;
    }
    point(const point &o){
        parent = o.parent;
        x = o.x;
        y = o.y;
        f = o.f;
        g = o.g;
        h = o.h;
    }
    point& operator= (const point &o){
        parent = o.parent;
        x = o.x;
        y = o.y;
        f = o.f;
        g = o.g;
        h = o.h;
        return *this;
    }
};

vector<point> open;
vector<point*> cleanPool;

bool close[maxW][maxH];
int change[4][2] = {{-1,0}, {0,1}, {1,0}, {0,-1}};
point s,e,ans;

bool is_in(const point &o){
    if(o.x < 0 || o.y < 0 || o.x >= maxW || o.y >=maxH) return false;
    return true;
}

int calcH(const point &o){
    return sqrt((o.x - e.x) * (o.x - e.x) + (o.y - e.y) * (o.y - e.y)) * cost;
}

int calcG(const point &o){
    int G = cost;
    if(o.parent != nullptr) G += (o.parent)-> g;
    return G;
}

vector<point>::iterator is_in_que(const point &o){
    auto it = open.begin();
    for(; it != open.end() ; ++it)
    {
        if(o.x == it -> x && o.y == it -> y) break;
    }
    return it;
}

int main()
{
    memset(close,0,sizeof(close));

    //cin >> s.x >> s.y >> e.x >> e.y;
    s.x = s.y = 9;
    e.x = e.y = 0;
    //test
    s.g = 0;
    s.h = calcH(s);
    s.calcF();
    close[s.x][s.y] = true;
    open.push_back(s);

    int n,x,y ;
    //cin >> n;
    n = 0;
    //test
    for(int i = 0 ; i < n ; ++i)
    {
        cin >> x >> y;
        close[x][y] = true;
    }

    point *t;
    point *tmp;

    while(!open.empty())
    {
        sort(open.begin(), open.end());
        t = new point(*open.begin());
        cleanPool.push_back(t);
        open.erase(open.begin());
        close[t->x][t->y] = true;

        if(t->x == e.x && t->y == e.y){
            ans = *t;
            break;
        }

        for(int i = 0 ; i < 4 ; ++i)
        {
            tmp = new point(t -> x + change[i][0], t-> y + change[i][1]);
            cleanPool.push_back(tmp);

            if(is_in(*tmp) && close[tmp -> x][tmp -> y] == false){

                auto iter = is_in_que(*tmp);

                if( iter == open.end()){
                    tmp -> parent = t;
                    tmp -> g = calcG(*tmp);
                    tmp -> h = calcH(*tmp);
                    tmp -> calcF();
                    open.push_back(*tmp);

                }else{
                    tmp -> parent = t;
                    tmp -> g = calcG(*tmp);
                    int G = iter -> g;

                    if(G > tmp -> g){
                        iter -> parent = tmp -> parent;
                        calcG(*iter);
                        iter -> calcF();
                    }
                }
            }
        }
    }
    point *p = &ans;
    while(p -> parent != nullptr)
    {
        cout << "x: " << p -> x << " y: " << p -> y << endl;
        p = p->parent;
    }
    cout << "x: " << s.x << " y: " << s.y << endl;

    vector<point*>::iterator iter;
    for(iter = cleanPool.begin(); iter != cleanPool.end(); ++iter){
        delete *iter;
        *iter = nullptr;
    }
}
