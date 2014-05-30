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
    for (int i = 0; i < 10; ++i)
        ai.add(i);
    LinkedList<int> bi = ai;
    print_linkedList(ai);
    print_linkedList(bi);
    for (int i = 0; i < 20; ++i)
    {
        if (ai.contains(i))
            cout << 1 << " ";
        else
            cout << 0 << " ";
    }
    cout << endl;
    for (int i = -10; i < 0; ++i)
        ai.add(0, i);
    print_linkedList(ai);
    for (int i = 0; i < 10; ++i)
        ai.set(i, i);
    print_linkedList(ai);
    for (int i = 0; i < 5; ++i)
        ai.removeIndex(i);
    print_linkedList(ai);
    for (int i = 5; i < 10; ++i)
        ai.remove(i);
    print_linkedList(ai);

    for (LinkedList<int>::Iterator iter = bi.iterator();
            iter.hasNext(); )
    {
        iter.next();
        iter.remove();
        if (iter.hasNext())
            iter.next();
        else            
            break;
    }
    print_linkedList(bi);

    for (int i = 0; i < 5; ++i) {
        ai.addFirst(i);
        ai.addLast(i);
        cout << ai.getFirst() << " " << ai.getLast() <<  endl;
    }
}
int main()
{
    // srand(0);
    test_linked_list();
    return 0;
}
