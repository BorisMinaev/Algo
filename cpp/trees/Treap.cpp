#include <iostream>
#include <random>
#include <set>

using namespace std;

struct treap_item {
   int key;
   int prior;
   treap_item * l, * r;
   treap_item() {};
   treap_item(int key, int prior) : key(key), prior(prior), l (NULL), r (NULL) {};
};

typedef treap_item * pitem;

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
   if (!t) {
      l = r = NULL;
   } else {
      if (key < t->key) {
         split(t -> l, key, l, t->l);
         r = t;
      } else {
         split(t -> r, key, t->r, r);
         l = t;
      }
   }
}

void insert(pitem & t, pitem new_item, bool check = true) {
   if (check && contains(t, new_item->key))
      return;
   if (!t) {
      t = new_item;
      return;
   }
   if (new_item->prior > t->prior) {
      split(t, new_item->key, new_item->l, new_item->r);
      t = new_item;
   } else {
      if (new_item->key < t->key)
         insert(t->l, new_item, false); else
      insert(t->r, new_item, false);
   }
}

void merge(pitem & t, pitem l, pitem r) {
   if (!l || !r) {
      if (!l) {
         t = r;
      } else {
         t = l;
      }
   } else {
      if (l->prior > r->prior) {
         merge(l->r, l->r, r);
         t = l;
      } else {
         merge(r->l, l, r->l);
         t = r;
      }
   }
}

void remove(pitem & t, int val) {
   if (!t)
      return;
   if (t->key == val) {
      merge(t, t->l, t->r);
   } else {
      if (t->key > val)
         remove(t->l, val); else
      remove(t->r, val);
   }
}

bool test() {
   pitem root = NULL;
   set<int> std_set;
   for (int i = 0; i < 100; i++) {
      if (i % 2 == 0) {
         std_set.insert(i);
         insert(root, new treap_item(i, rand()));
      }
   }
   for (int i =0; i < 100; i++) {
      bool exist_my_algo = contains(root, i);
      bool exist_std_set = (std_set.find(i) != std_set.end());
      if (exist_my_algo != exist_std_set)
         return false;
   }
   for (int i = 0; i < 1000000; i++) {
      int val = i % 2 == 0 ? -i : i;
      if (rand() % 2 == 0) {
         // insert
         std_set.insert(val);
         insert(root, new treap_item(val, rand()));
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