#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int father[501] = {0};

void init() {
    for (int i = 1; i <= 500; ++i) {
        father[i] = i;
    }
}

int find(int x){
    if (x != father[x]){
        father[x] = find(father[x]);    
    }         
    return father[x];
}

void merge(int x, int y) {
    x = find(x);
    y = find(y);
    if (x != y) { // 不在同一个集合
        father[y] = x;
    }
}

struct path {
    int node1;
    int node2;
    int cost;
    path();
    path(int n1, int n2, int c):node1(n1), node2(n2), cost(c) {}
};

struct comp {
    comp() {}
    ~comp() {}
    bool operator()(path a, path b) {
        return a.cost > b.cost;
    }
};

int main(int argc, char const *argv[])
{
    int n, m, k;
    cin >> n >> m >> k;
    init();
    priority_queue<path, vector<path>, comp> queue;
    for (int i = 0; i < m; ++i) {
        int node1, node2;
        cin >> node1 >> node2;
        merge(node1, node2);
    }
    for (int i = 0; i < k; ++i) {
        int node1, node2, cost;
        cin >> node1 >> node2 >> cost;
        path p(node1, node2, cost);
        queue.push(p);
    }
    long long cost = 0;
    int root = 0;
    for (int i = 1; i <= n; ++i) {
        if (father[i] == i)
            ++root;
    }
    while (root > 1) {
        path temp = queue.top();
        queue.pop();
        if (find(temp.node1) == find(temp.node2))
            continue;
        merge(temp.node1, temp.node2);
        cost += temp.cost;
        --root;
    }
    cout << cost << endl;
    return 0;
}
