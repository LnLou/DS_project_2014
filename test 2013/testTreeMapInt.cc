#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sys/time.h>
#include "ArrayList.h"
#include "LinkedList.h"
#include "HashMap.h"
#include "TreeMap.h"
#include <cstdio>
using namespace std;
#define foreach(itr,c) for(__typeof((c).begin()) itr=(c).begin();itr!=(c).end();++itr) 
// double cur;
const int N = 100000;

void print_treeMap(TreeMap<int, int> his)
{
    for (TreeMap<int, int>::Iterator iter = his.iterator();
            iter.hasNext(); )
    {
        TreeMap<int, int>::Entry he = iter.next();
        cout << he.getKey() << " " << he.getValue() << endl;
    }
}

void test_tree_map()
{
    TreeMap<int, int> hii;
    freopen("../randInt.txt", "r", stdin);
    // cur = getTime();
    // std::vector<int> v;
    int _t;
    // for (int i = 0; i < 3*N; ++i) {
    //     scanf("%d", &_t);
    //     v.push_back(_t);
    // }
    for (int i = 0; i < 2*N; ++i) {
        scanf("%d", &_t);
        hii.put(_t, i);
    }
    // print_time();
    cout << hii.size() << endl;
    for (int i = 0; i < N; ++i) {
        scanf("%d", &_t);
        // int _tmp = v[2*N+i];
        if (hii.containsKey(_t)) hii.remove(_t);
    }
    // print_time();
    cout << hii.size() << endl;
}

int main() {
    // srand(0);
    test_tree_map();
    return 0;
}
