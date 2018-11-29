#include <cstdio>
#include <iostream>
#include <cstring>
#include "avltree.h"
using namespace std;
int main(){
    while(true){
        AVLTree<int>tree;
        tree.build();
        tree.output();
        int x;
        while(cin >> x){
            if(x==-1)break;
            if(tree.remove(x))cout << "deleted\n";
            tree.output();
        }
	}
	return 0;
}
