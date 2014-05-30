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

class HashInt {
public:
    static int hashCode(int obj) {
        return obj;
    }
};
// Time33 Hash: string -> int
class HashStr {
public:
    static int hashCode(string obj) {
        int res = 0;
        for (int i = 0; i < obj.size(); ++i)
            res = res * 33 + (int)obj[i];
        return res;
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
    HashMap<string, int, HashStr> hsi;
    string _s;
    freopen("../randStr.txt", "r", stdin);
    for (int i = 0; i < N; ++i) {
        // string _tmp = get_a_rand_string();
        cin >> _s;
        hsi.put(_s, i);
        hsi.put(_s, i+1);
    }
    // print_time();
    cout << hsi.size() << endl;
    for (int i = 0; i < 2*N; ++i) {
        // string _tmp = get_a_rand_string();
        cin >> _s;
        if (hsi.containsKey(_s)) hsi.remove(_s);
    }  
    // print_time();
    cout << hsi.size() << endl;
}

int main() {
    // srand(0);
    test_hash_map();
    return 0;
}
