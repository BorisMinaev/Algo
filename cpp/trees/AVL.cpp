#include <iostream>
#include <random>
#include <set>

using namespace std;

struct avl_item {
	int key;
	avl_item * l, * r;
	avl_item() {};
	avl_item(int key) : key(key), l (NULL), r (NULL) {};
};

typedef avl_item * pitem;

bool contains(pitem t, int val) {
	if (!t)
		return false;
	if (t->key == val)
		return true;
	if (t->key > val)
		return contains(t->l, val);
	return contains(t->r, val);
}

// >= -> right
// < -> left
void split(pitem t, int key, pitem & l, pitem & r) {
	
}

void insert(pitem & t, pitem new_item) {
	
}

void merge(pitem & t, pitem l, pitem r) {
	
}

void remove(pitem & t, int val) {
	
}

bool test() {
	pitem root = NULL;
	set<int> std_set;
	for (int i = 0; i < 100; i++) {
		if (i % 2 == 0) {
			std_set.insert(i);
			insert(root, new avl_item(i));
		}
	}
	for (int i =0; i < 100; i++) {
		bool exist_my_algo = contains(root, i);
		bool exist_std_set = (std_set.find(i) != std_set.end());
		if (exist_my_algo != exist_std_set)
			return false;
	}
	for (int i = 0; i < 100000; i++) {
		int val = rand() % 300;
		if (rand() % 2 == 0) {
			// insert
			std_set.insert(val);
			insert(root, new avl_item(val));
		} else {
			if (rand() % 2== 0) {
				// remove
				std_set.erase(val);
				remove(root, val);
			} else {
				// check
				bool exist_my_algo = contains(root, val);
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