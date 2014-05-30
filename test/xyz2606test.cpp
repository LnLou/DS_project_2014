#include"PriorityQueue.h"
#include"ArrayList.h"
#include"TreeMap.h"
#include"HashMap.h"
#include"LinkedList.h"
#include"Deque.h"
#include"__xyz2606__memory.h"
#include<algorithm>
#include<cstdio>
#include<map>
#include<cstring>
#include<deque>
#include<ctime>
#include<vector>
bool FLAG;
using namespace std;
void ____()
{FLAG = false;
	printf("·ÃÎÊÁËÆæ¹ÖµÄÄÚŽæ.ÇëŒì²é³öÏÖÎ»ÖÃ.\n");
}
unsigned int id, x, y;
int N, LIM, cnt[200001], CNT;
bool flag;
struct _test_
{
	unsigned int value, id;
	_test_(const unsigned int value) : value(value), id(::id)
	{CNT++;}
	_test_(){id = ::id;CNT++;}
	_test_(const _test_ & that)
	{
		if(that.id != ::id) ____();
		value = that.value;
		id = ::id;
		CNT++;
	}
	_test_ & operator = (const _test_ & that)
	{
		if(that.id != ::id) ____();
		value = that.value;
		id = ::id;
	}
	~_test_(){if(id != ::id) ____(); CNT--;}
};
class Hash
{
	public:
	static int hashCode(_test_ a)
	{
		if(a.id != ::id) ____();
		return a.value;
	}
};
bool operator != (const _test_ & a, const _test_ & b)
{if(a.id != id or b.id != id) ____();
	return a.value != b.value;
}
bool operator == (const _test_ & a, const _test_ & b)
{if(a.id != id or b.id != id) ____();
	return a.value == b.value;
}
bool operator < (const _test_ & a, const _test_ & b)
{if(a.id != id or b.id != id) ____();
	return a.value < b.value;
}
struct _cmp_
{
	bool operator () (const _test_ & a, const _test_ & b)
	{if(a.id != id or b.id != id) ____(); return a.value < b.value;}
};
int main()
{
	FLAG = true;
	CNT = 0;
	printf("ÏÂÃæÊÇArrayListµÄ²âÊÔ:\n");
	{
		id = random();
		ArrayList<_test_> AL;
		vector<_test_> vec;
		N = 1000;
		printf("  Ëæ»úÖÖ×Ó:%u\n", (unsigned int)(x = time(0)));
		srandom(x);
		for(int i = 1; i <= N; i++)
		{
			if(AL.isEmpty() or random() <= 0x5fffffffu)
			{
				x = random() % (AL.size() + 1);
				y = random();
				AL.add(x, _test_(y));
				vec.insert(vec.begin() + x, _test_(y));
			}else
			{
				x = random() % AL.size();
				vec.erase(vec.begin() + x);
				AL.removeIndex(x);
			}
		}
		flag = true;
		if(AL.size() == vec.size())for(int i = 0; i < vec.size(); i++)
		{
			if(AL.get(i) != vec[i]) 
			{
				flag = false;
				break;
			}
		}else flag = false;
		printf("  ²âÊÔ:ArrayListÔÚËæ»úÎ»ÖÃ²åÈëºÍÉŸ³ýÔªËØ:");
		if(flag)  printf("  ÓëC++ vectorÔËÐÐœá¹ûÒ»ÖÂ.\n");
		else printf("  ÓëC++ vectorÔËÐÐœá¹û²»Ò»ÖÂ!\n");
		FLAG = FLAG and flag;
	}
	if(CNT != 0) printf("  ÔÚžÕ²ÅµÄ²âÊÔÖÐ ÈÝÆ÷Ê¹ÓÃµÄ¶ÔÏóÃ»ÓÐÈ«²¿Îö¹¹!\n");
	else printf("  ÔÚžÕ²ÅµÄ²âÊÔÖÐ ËùÓÐ¹¹ÔìµÄ¶ÔÏó¶ŒÎö¹¹ÁË.\n");

	CNT = 0;
	printf("ÏÂÃæÊÇDequeµÄ²âÊÔ:\n");
	{
		id = random();
		Deque<_test_> AL;
		deque<_test_> vec;
		N = 1000;
		printf("  Ëæ»úÖÖ×Ó:%u\n", (unsigned int)(x = time(0)));
		srandom(x);
		for(int i = 1; i <= N; i++)
		{
			if(AL.isEmpty() or random() <= 0x5fffffffu)
			{
				x = random() % 2;
				y = random();
				if(x == 0)
				{
					AL.addFirst(_test_(y));
					vec.push_front(_test_(y));
				}else
				{
					AL.addLast(_test_(y));
					vec.push_back(_test_(y));
				}
			}else
			{
				x = random() % 2;
				if(x == 0)
				{
					AL.removeFirst();
					vec.pop_front();
				}else
				{
					AL.removeLast();
					vec.pop_back();
				}
			}
		}
		flag = true;
		if(AL.size() == vec.size())for(int i = 0; i < vec.size(); i++)
		{
			if(AL.get(i) != vec[i]) 
			{
				flag = false;
				break;
			}
		}else flag = false;
		printf("  ²âÊÔ:DequeÔÚËæ»úÍ·»òÎ²Î»ÖÃ²åÈëºÍÉŸ³ýÔªËØ:");
		if(flag)  printf("  ÓëC++ dequeÔËÐÐœá¹ûÒ»ÖÂ.\n");
		else printf("  ÓëC++ dequeÔËÐÐœá¹û²»Ò»ÖÂ!\n");
		FLAG = FLAG and flag;
	}
	if(CNT != 0) printf("  ÔÚžÕ²ÅµÄ²âÊÔÖÐ ÈÝÆ÷Ê¹ÓÃµÄ¶ÔÏóÃ»ÓÐÈ«²¿Îö¹¹!\n");
	else printf("  ÔÚžÕ²ÅµÄ²âÊÔÖÐ ËùÓÐ¹¹ÔìµÄ¶ÔÏó¶ŒÎö¹¹ÁË.\n");
	
	CNT = 0;
	printf("ÏÂÃæLinkedListµÄ²âÊÔ:\n");
	{
		id = random();
		LinkedList<_test_> AL;
		vector<_test_> vec;
		N = 1000;
		printf("  Ëæ»úÖÖ×Ó:%u\n", (unsigned int)(x = time(0)));
		srandom(x);
		for(int i = 1; i <= N; i++)
		{
			if(AL.isEmpty() or random() <= 0x5fffffffu)
			{
				x = random() % (AL.size() + 1);
				y = random();
				AL.add(x, _test_(y));
				vec.insert(vec.begin() + x, _test_(y));
			}else
			{
				x = random() % AL.size();
				vec.erase(vec.begin() + x);
				AL.removeIndex(x);
			}
		}
		flag = true;
		if(AL.size() == vec.size())for(int i = 0; i < vec.size(); i++)
		{
			if(AL.get(i) != vec[i]) 
			{
				flag = false;
				break;
			}
		}else flag = false;
		printf("  ²âÊÔ:LinkedListÔÚËæ»úÎ»ÖÃ²åÈëºÍÉŸ³ýÔªËØ:");
		if(flag)  printf("  ÓëC++ vectorÔËÐÐœá¹ûÒ»ÖÂ.\n");
		else printf("  ÓëC++ vectorÔËÐÐœá¹û²»Ò»ÖÂ!\n");
		FLAG = FLAG and flag;
	}
	if(CNT != 0) printf("  ÔÚžÕ²ÅµÄ²âÊÔÖÐ ÈÝÆ÷Ê¹ÓÃµÄ¶ÔÏóÃ»ÓÐÈ«²¿Îö¹¹!\n");
	else printf("  ÔÚžÕ²ÅµÄ²âÊÔÖÐ ËùÓÐ¹¹ÔìµÄ¶ÔÏó¶ŒÎö¹¹ÁË.\n");

	CNT = 0;
	printf("ÏÂÃæÊÇPriorityQueueµÄ²âÊÔ:\n");
	{
		id = random();
		PriorityQueue<_test_, _cmp_> PQ;
		memset(cnt, 0, sizeof(cnt));
		N = 100000;
		printf("  Ëæ»úÖÖ×Ó:%u\n", (unsigned int)(x = time(0)));
		srandom(x);
		LIM = 100000;
		for(int i = 1; i <= N; i++)
		{
			x = random() % LIM;
			cnt[x]++;
			PQ.push(_test_(x));
		}
		for(PriorityQueue<_test_, _cmp_>::Iterator itr = PQ.iterator(); itr.hasNext(); )
		{
			cnt[itr.next().value] --;
			if(random() <= 0x3fffffffu) itr.remove();
		}
		flag = true;
		for(int i = 0; i < LIM; i++) if(cnt[i] != 0)
		{
			printf("  ÖµÎª%dµÄÔªËØ·ÃÎÊŽÎÊý²»¶Ô:»¹Ê£%dŽÎ\n", i, cnt[i]);
			flag = false;
		}
		printf("  ²âÊÔ:ÓÅÏÈŒ¶¶ÓÁÐµüŽúÆ÷ÔÚÓÐÉŸ³ý²Ù×÷µÄÇé¿öÏÂÄÜ·ñ±éÀúÈÝÆ÷ÖÐËùÓÐÔªËØ:");
		if(flag)  printf("Íš¹ý.\n");
		else printf("ÎŽÍš¹ý!\n");
		FLAG = FLAG and flag;
	}
	if(CNT != 0) printf("  ÔÚžÕ²ÅµÄ²âÊÔÖÐ ÈÝÆ÷Ê¹ÓÃµÄ¶ÔÏóÃ»ÓÐÈ«²¿Îö¹¹!\n");
	else printf("  ÔÚžÕ²ÅµÄ²âÊÔÖÐ ËùÓÐ¹¹ÔìµÄ¶ÔÏó¶ŒÎö¹¹ÁË.\n");

	CNT = 0;
	printf("ÏÂÃæÊÇTreeMap²âÊÔ:\n");
	{
		id = random();
		TreeMap<_test_, _test_> TM;
		map<_test_, _test_> mp;

		printf("  Ëæ»úÖÖ×Ó:%u\n", (unsigned int)(x = time(0)));
		srandom(x);
		N = 100000;
		LIM = 50000;
		for(int i = 1; i <= N; i++)
		{
			x = random() % LIM;
			y = random() % LIM;
			TM.put(_test_(x), _test_(y));
			if(mp.find(_test_(x)) != mp.end()) mp.erase(_test_(x));
		       	mp.insert(make_pair(_test_(x), _test_(y)));
		}
		flag = true;
		for(int i = 1; i <= N / 2; i++)
		{
			x = random() % LIM;
			if(TM.containsKey(_test_(x)) != (mp.find(_test_(x)) != mp.end()))
			{
				flag = false;
				break;
			}else if(TM.containsKey(_test_(x)))
			{
				TM.remove(_test_(x));
				mp.erase(_test_(x));
			}
		}
		if(mp.size() != TM.size()) flag = false; else
		{
			map<_test_, _test_>::iterator it = mp.begin();
			for(TreeMap<_test_, _test_>::Iterator itr = TM.iterator(); itr.hasNext(); it++)
			{
				const TreeMap<_test_, _test_>::Entry & tmp = itr.next();
				if(tmp.getKey() != it->first or tmp.getValue() != it->second)
				{
					flag = false;
					//break;
				}
			}
		}
		printf("  ²âÊÔ:Ëæ»úŒÓÈëÔªËØ, Ëæ»úÉŸ³ý²¢ÓÃµüŽúÆ÷±éÀú:\n");
		if(flag) printf("  œá¹ûÓëC++ mapÒ»ÖÂ.\n");
		else printf("  œá¹ûÓëC++ map²»Ò»ÖÂ!\n");
		FLAG = FLAG and flag;
	}
	if(CNT != 0) printf("  ÔÚžÕ²ÅµÄ²âÊÔÖÐ ÈÝÆ÷Ê¹ÓÃµÄ¶ÔÏóÃ»ÓÐÈ«²¿Îö¹¹!\n");
	else printf("  ÔÚžÕ²ÅµÄ²âÊÔÖÐ ËùÓÐ¹¹ÔìµÄ¶ÔÏó¶ŒÎö¹¹ÁË.\n");

	CNT = 0;
	printf("ÏÂÃæÊÇHashMap²âÊÔ:\n");
	{
		id = random();
		HashMap<_test_, _test_, Hash> TM;
		map<_test_, _test_> mp, mp1;

		printf("  Ëæ»úÖÖ×Ó:%u\n", (unsigned int)(x = time(0)));
		srandom(x);
		N = 100000;
		LIM = 1000000;
		for(int i = 1; i <= N; i++)
		{
			x = random() % LIM;
			y = random() % LIM;
			TM.put(_test_(x), _test_(y));
			if(mp.find(_test_(x)) != mp.end()) mp.erase(_test_(x));
		       	mp.insert(make_pair(_test_(x), _test_(y)));
		}
		flag = true;
		for(int i = 1; i <= N / 2; i++)
		{
			x = random() % LIM;
			if(TM.containsKey(_test_(x)) != (mp.find(_test_(x)) != mp.end()))
			{
				flag = false;
				break;
			}else if(TM.containsKey(_test_(x)))
			{
				TM.remove(_test_(x));
				mp.erase(_test_(x));
			}
		}
		if(mp.size() != TM.size()) flag = false; else
		{
			for(HashMap<_test_, _test_, Hash>::Iterator itr = TM.iterator(); itr.hasNext();)
			{
				const HashMap<_test_, _test_, Hash>::Entry & tmp = itr.next();
				mp1.insert(make_pair(tmp.getKey(), tmp.getValue()));
			}
			flag = mp == mp1;
		}
		printf("  ²âÊÔ:Ëæ»úŒÓÈëÔªËØ, Ëæ»úÉŸ³ý²¢ÓÃµüŽúÆ÷±éÀú:\n");
		if(flag) printf("  œá¹ûÓëC++ mapÒ»ÖÂ.\n");
		else printf("  œá¹ûÓëC++ map²»Ò»ÖÂ!\n");
		FLAG = FLAG and flag;
	}
	if(CNT != 0) printf("  ÔÚžÕ²ÅµÄ²âÊÔÖÐ ÈÝÆ÷Ê¹ÓÃµÄ¶ÔÏóÃ»ÓÐÈ«²¿Îö¹¹!\n");
	else printf("  ÔÚžÕ²ÅµÄ²âÊÔÖÐ ËùÓÐ¹¹ÔìµÄ¶ÔÏó¶ŒÎö¹¹ÁË.\n");
	if(FLAG) printf("¹§Ï²ÄúÍš¹ýÁËËùÓÐµÄ²âÊÔ, CONGRATULATIONS!\n");
	else printf("ÇëŒì²é²âÊÔÖÐ·¢ÏÖµÄÎÊÌâ!\n");
}
