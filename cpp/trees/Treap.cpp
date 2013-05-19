#include <iostream>
#include <random>
#include <set>

using namespace std;

struct treap_item {
	int key;
	int prior;
	treap_item * l, * r;
	set<int> ss;
	treap_item() {};
	treap_item(int key, int prior) : key(key), prior(prior), l (NULL), r (NULL) {};
};

typedef treap_item * pitem;

void insert(pitem t, int val) {
	if (!t)
		return;
	t->ss.insert(val);
}

void remove(pitem t, int val) {
	if (!t)
		return;
	t->ss.erase(val);
}

bool contains(pitem t, int val) {
	if (!t)
		return false;
	return t->ss.find(val) != t->ss.end();
}

bool test() {
	treap_item root;
	set<int> std_set;
	for (int i = 0; i < 100; i++) {
		if (i % 2 == 0) {
			std_set.insert(i);
			insert(&root, i);
		}
	}
	for (int i =0; i < 100; i++) {
		bool exist_my_algo = contains(&root, i);
		bool exist_std_set = (std_set.find(i) != std_set.end());
		if (exist_my_algo != exist_std_set)
			return false;
	}
	for (int i = 0; i < 100000; i++) {
		int val = rand() % 300;
		if (rand() % 2 == 0) {
			// insert
			std_set.insert(val);
			insert(&root, val);
		} else {
			if (rand() % 2== 0) {
				// remove
				std_set.erase(val);
				remove(&root, val);
			} else {
				// check
				bool exist_my_algo = contains(&root, val);
				bool exist_std_set = (std_set.find(val) != std_set.end());
				if (exist_my_algo != exist_std_set)
					return false;
			}
		}
	}
	return true;
}


int main() {
	srand(time(0));
	if (!test()) {
		cout << "fail" << endl;
	} else {
		cout << "all tests passed" << endl;
	}

}