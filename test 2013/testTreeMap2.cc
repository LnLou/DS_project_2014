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
const int N = 1000000;

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
    // cur = getTime();
    TreeMap<int, int> his;
    for (int i = N; i >= 0; --i) his.put(i,i);
    // print_time();
    for (int i = 0; i < N; ++i) if (i==N-1) cout << his.containsKey(N-1) << endl;
        else his.containsKey(N-1);
    // print_time();
}

int main() {
    // srand(0);
    test_tree_map();
    return 0;
}
