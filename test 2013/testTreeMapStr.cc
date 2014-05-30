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
    freopen("../randstr.txt", "r", stdin);
    // TreeMap<int, int> hii;
    
    // cur = getTime();
    // for (int i = 0; i < 2*N; ++i) hii.put(rand() % N, rand() % N);
    // print_time();
    // cout << hii.size() << endl;
    // for (int i = 0; i < N; ++i) {
    //     int _tmp = rand() % N;
    //     if (hii.containsKey(_tmp)) hii.remove(_tmp);
    // }
    // print_time();
    // cout << hii.size() << endl;

    TreeMap<string, int> hsi;
    // std::vector<string> vs;
    // std::vector<int> vi;
    string _s;
    for (int i = 0; i < N; ++i) {
        // string _tmp = get_a_rand_string();
        cin >> _s;
        hsi.put(_s, i);
        hsi.put(_s, i+1);
        // hsi.put(_tmp, rand() % N);
        // hsi.put(_tmp, rand() % N);
    }
    // print_time();
    cout << hsi.size() << endl;
    for (int i = 0; i < 2*N; ++i) {
        // string _tmp = get_a_rand_string();
        string _tmp;
        cin >> _tmp;
        if (hsi.containsKey(_tmp)) hsi.remove(_tmp);
    }  
    // print_time();
    cout << hsi.size() << endl;
}

int main() {
    // srand(0);
    test_tree_map();
    return 0;
}
