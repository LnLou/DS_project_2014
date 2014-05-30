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

class HashInt {
public:
    static int hashCode(int obj) {
        return obj;
    }
};

void print_hashMap(HashMap<int, int, HashInt> his)
{
    std::vector<int> vi;
    for (HashMap<int, int, HashInt>::Iterator iter = his.iterator();
            iter.hasNext(); )
    {
        vi.push_back(iter.next().getKey());
    }
    sort(vi.begin(), vi.end());
    foreach(it,vi)
    {
        cout << *it << " " << his.get(*it) << endl;
    }
}

void test_hash_map()
{
    HashMap<int, int, HashInt> hii;
    for (int i = 0; i < 10; ++i) hii.put(i, i);
    print_hashMap(hii);
    HashMap<int, int, HashInt> hij = hii;
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
    cout << endl;
    for (int i = 0; i < 10; ++i)
        cout << hii.get(i) << " ";
    cout << endl;
    for (int i = 0; i < 10; ++i)
    {
        hii.remove(i);
        print_hashMap(hii);
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
    test_hash_map();
    return 0;
}
