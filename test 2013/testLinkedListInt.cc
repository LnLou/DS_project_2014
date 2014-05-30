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

void print_linkedList(LinkedList<int> &ai)
{
    for (LinkedList<int>::Iterator iter = ai.iterator();
            iter.hasNext(); )
        cout << iter.next() << " ";
    cout << endl;
    for (int i = 0; i < ai.size(); ++i)
        cout << ai.get(i) << " ";
    cout << endl;
}
void test_linked_list()
{
    LinkedList<int> ai;
    freopen("../randInt.txt", "r", stdin);
    int _t;
    // std::vector<int> vi;
    
    // cur = getTime();
    for (int i = 0; i < N; ++i) {
        scanf("%d", &_t);
        ai.addLast(_t);
    }
    for (LinkedList<int>::Iterator iter = ai.iterator(); iter.hasNext(); ){
        iter.next();
        iter.remove();
    }
    // print_time();
    cout << ai.size() << endl;
}

int main() {
    // srand(0);
    test_linked_list();
    return 0;
}
