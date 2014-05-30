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
    LinkedList<string> as;
    freopen("../randStr.txt", "r", stdin);
    string _s;
    for (int i = 0; i < N; ++i) {
        cin >> _s;
        as.addLast(_s);
    }
    for (LinkedList<string>::Iterator iter = as.iterator(); iter.hasNext(); ) {
        iter.next();
        iter.remove();
    }
    // print_time();
    cout << as.size() << endl;
}

int main() {
    // srand(0);
    test_linked_list();
    return 0;
}
