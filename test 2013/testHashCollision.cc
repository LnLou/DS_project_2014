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
#define N 10000
using namespace std;

class HashInt {
public:
    static int hashCode(int obj) {
        return 0;
    }
};

HashMap<int, int, HashInt> hashMap;

void testHashCollision()
{
    for (int i = 0; i < N; ++i)
        hashMap.put(i, i);

    int fail = 0;
    for (int i = 0; i < N; ++i)
        if (hashMap.containsKey(i) == 0 || hashMap.get(i) != i)
            fail = 1;
    for (int i = N; i < N * 2; ++i)
        if (hashMap.containsKey(i))
            fail = 1;
    cout << fail << endl;
}

int main()
{
    testHashCollision();
    return 0;
}
