#include <iostream>
#include <cstring>
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
const int N = 10000;

void print_arrayList(ArrayList<int> &ai)
{
    for (ArrayList<int>::Iterator iter = ai.iterator();
            iter.hasNext(); )
        cout << iter.next() << " ";
    cout << endl;
    for (int i = 0; i < ai.size(); ++i)
        cout << ai.get(i) << " ";
    cout << endl;
}
void test_array_list()
{
    ArrayList<int> ai;
    freopen("../randInt.txt", "r", stdin);
    // cur = getTime();
    int _t;
    for (int i = 0; i < N; ++i) {
        scanf("%d", &_t);
        ai.add(_t);
    }
    for (int i = 0; i < N; ++i) ai.remove(i);
    // print_time();
    cout << ai.size() << endl;
}

int main() {
    // srand(0);
    test_array_list();
    return 0;
}
