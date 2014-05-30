#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "ArrayList.h"
#include "LinkedList.h"
#include "HashMap.h"
#include "TreeMap.h"

using namespace std;
#define foreach(itr,c) for(__typeof((c).begin()) itr=(c).begin();itr!=(c).end();++itr) 

const int N = 10000;
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
    for (int i = 0; i < 10; ++i) hii.put(i, i);
    print_treeMap(hii);
    TreeMap<int, int> hij = hii;
    for (int i = 0; i < 10; ++i)
        cout << hii.get(i) << " ";
    cout << endl;
    for (int i = 0; i < 10; ++i) hii.put(i, i+1);
    for (int i = 0; i < 20; ++i)
    {
        if (hii.containsKey(i)) cout << 1 << " ";
        else cout << 0 << " ";
        if (hii.containsValue(i)) cout << 1 << " ";
        else cout << 0 << " ";
    }
    for (int i = 0; i < 10; ++i)
        cout << hii.get(i) << " ";
    cout << endl;
    for (int i = 0; i < 10; ++i)
    {
        hii.remove(i);
        print_treeMap(hii);
        cout << hii.size() << endl;
    }
    if (hii.isEmpty()) cout << 1 << endl;
    else cout << 0 << endl;
    hij.clear();
    if (hij.isEmpty()) cout << 1 << endl;
    else cout << 0 << endl;
}
int main()
{
    // srand(0);
    test_tree_map();
    return 0;
}