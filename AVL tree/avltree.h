#include <cstdio>
#include <iostream>
#include <algorithm>
#include <stack>
#include <queue>
#include <cstring>
using namespace std;
template<class V> class AVLNode{
public:
	V value;
	AVLNode<V>* leftChild;
	AVLNode<V>* rightChild;
	int bf;
	AVLNode(AVLNode<V>* l=NULL,AVLNode<V>* r=NULL):leftChild(l),rightChild(r),bf(0){};
	AVLNode(V v,AVLNode<V>* l=NULL,AVLNode<V>* r=NULL):value(v),leftChild(l),rightChild(r),bf(0){};
};
template<class V> class AVLTree{
private:
	AVLNode<V>* root;
	void trackback(AVLNode<V>* ptr);
public:
	AVLTree<V>(){root=NULL;}//initially empty tree
    bool insert(V value);
	bool remove(V value);
	bool search(V value);
    void RotateR(AVLNode<V>*& ptr);
    void RotateL(AVLNode<V>*& ptr);
    void RotateLR(AVLNode<V>*& ptr);
    void RotateRL(AVLNode<V>*& ptr);
	~AVLTree();
	void output(){cout << "output:";trackback(root);cout << "\n";}
	void build();
};
template<class V>void AVLTree<V>::trackback(AVLNode<V>* ptr){
	if(!ptr)return;
	if(!ptr->leftChild && !ptr->rightChild){
		cout << ptr->value;
		return;
	}
	cout << ptr->value << "(";
	if(ptr->leftChild)trackback(ptr->leftChild);
	cout << ",";
	if(ptr->rightChild)trackback(ptr->rightChild);
	cout << ")";
}
template<class V>void AVLTree<V>::build(){
	int N;cin >> N;
	while(N--){
		V x;cin >> x;
		if(!insert(x))cout << x << " inserted failed";
	}
	cout << "\n";
}
template<class V>void AVLTree<V>::RotateL(AVLNode<V>*& ptr){
	AVLNode<V>* subL=ptr;
	ptr=subL->rightChild;//rename
	subL->rightChild=ptr->leftChild;
	ptr->leftChild=subL;
	if(ptr->bf>=0)subL->bf++;
	else subL->bf=subL->bf+1-ptr->bf;
	if(subL->bf<=0)ptr->bf++;
	else ptr->bf=ptr->bf+1+subL->bf;
}
template<class V>void AVLTree<V>::RotateR(AVLNode<V>*& ptr){
	AVLNode<V>* subR=ptr;
	ptr=subR->leftChild;//rename
	subR->leftChild=ptr->rightChild;
	ptr->rightChild=subR;
	if(ptr->bf<=0)subR->bf--;
	else subR->bf=subR->bf-1+ptr->bf;
	if(subR->bf>=0)ptr->bf--;
	else ptr->bf=ptr->bf-1-subR->bf;
}
template<class V>void AVLTree<V>::RotateRL(AVLNode<V>*& ptr){
	AVLNode<V> *subL=ptr,*subR=ptr->rightChild;
	ptr=subR->leftChild;//rename
	RotateR(subR);
	subL->rightChild=subR;
	RotateL(subL);
}
template<class V>void AVLTree<V>::RotateLR(AVLNode<V>*& ptr){
	AVLNode<V> *subR=ptr,*subL=ptr->leftChild;
	ptr=subL->rightChild;//rename
	RotateL(subL);
	subR->leftChild=subL;
	RotateR(subR);
}
template<class V>bool AVLTree<V>::insert(V value){
	stack<AVLNode<V>* >s;
	AVLNode<V> *ptr=root,*p;
	if(!ptr){
		root=new AVLNode<V>(value);
		return true;
	}
	while(ptr){
		if(ptr->value==value){
			return false;
		}
		s.push(ptr);
		if(value>ptr->value){
			ptr=ptr->rightChild;
		}
		else{
			ptr=ptr->leftChild;
		}
	}
	p=new AVLNode<V>(value);
	ptr=s.top();
	if(p->value>ptr->value){
		ptr->rightChild=p;
	}
	else{
		ptr->leftChild=p;
	}
	ptr=p;
	while(!s.empty()){
		p=ptr;
		ptr=s.top();
		s.pop();
		if(p->value>ptr->value){
			ptr->bf--;
		}
		else{
			ptr->bf++;
		}
		if(ptr->bf==0){
			break;
		}
		if(ptr->bf==-1 || ptr->bf==1){
			continue;
		}
		if(ptr->bf==2){
			if(p->bf==1){
				RotateR(ptr);
				if(!s.empty())if(ptr->value>s.top()->value)s.top()->rightChild=ptr;
				else s.top()->leftChild=ptr;else root=ptr;
			}
			else{
				RotateLR(ptr);
				if(!s.empty())if(ptr->value>s.top()->value)s.top()->rightChild=ptr;
				else s.top()->leftChild=ptr;else root=ptr;
			}
			break;
		}
		else{
			if(p->bf==1){
				RotateRL(ptr);
				if(!s.empty())if(ptr->value>s.top()->value)s.top()->rightChild=ptr;
				else s.top()->leftChild=ptr;else root=ptr;
			}
			else{
				RotateL(ptr);
				if(!s.empty())if(ptr->value>s.top()->value)s.top()->rightChild=ptr;
				else s.top()->leftChild=ptr;else root=ptr;
			}
			break;
		}
	}
	return true;
}
template<class V>bool AVLTree<V>::remove(V value){
	AVLNode<V>* ptr=root,*p;
	stack<AVLNode<V>* >s;
	while(ptr&&ptr->value!=value){
		s.push(ptr);
		if(value<ptr->value){
			ptr=ptr->leftChild;
		}
		else{
			ptr=ptr->rightChild;
		}
	}
	if(!ptr){
		cout << "no such value";
		return false;
	}
	AVLNode<V>* p0=ptr;
	if(ptr->leftChild&&ptr->rightChild){
		//find the inOrder immediately precursor
		s.push(ptr);
		p0=ptr;
		ptr=ptr->leftChild;
		while(ptr->rightChild){
			s.push(ptr);
			ptr=ptr->rightChild;
		}
	}
	//ptr is the node to remove
	//ptr isn't in the stack
	//ptr may has one Child
	if(root==ptr){
		if(ptr->rightChild)root=ptr->rightChild;
		else root=ptr->leftChild;
		delete ptr;
		return true;
	}
    if(ptr->leftChild)p=ptr->leftChild;
	else p=ptr->rightChild;
	//p is the son of ptr
	if(!s.empty())if(s.top()->value>ptr->value)s.top()->leftChild=p;
	else s.top()->rightChild=p;
	AVLNode<V>* q=ptr;
	AVLNode<V>* pt=new AVLNode<V>(ptr->value);
	p=pt;
	ptr=p;
	while(!s.empty()){
		p=ptr;
		ptr=s.top();
		s.pop();
		if(p->value>ptr->value){
			ptr->bf++;
		}
		else{
			ptr->bf--;
		}
		if(ptr->bf==1 || ptr->bf==-1){
			break;
		}
		if(ptr->bf==0){
			continue;
		}
		if(ptr->bf==2){
			p=ptr->leftChild;
			if(p->bf==-1){
				RotateLR(ptr);
				if(!s.empty())if(ptr->value>s.top()->value)s.top()->rightChild=ptr;
				else s.top()->leftChild=ptr;else root=ptr;
			}
			else{
				bool flag=false;
				if(p->bf==0)flag=true;
				RotateR(ptr);
				if(!s.empty())if(ptr->value>s.top()->value)s.top()->rightChild=ptr;
				else s.top()->leftChild=ptr;else root=ptr;
				if(flag)break;
			}
		}
		else if(ptr->bf==-2){
			p=ptr->rightChild;
			if(p->bf==1){
				RotateRL(ptr);
				if(!s.empty())if(ptr->value>s.top()->value)s.top()->rightChild=ptr;
				else s.top()->leftChild=ptr;else root=ptr;
			}
			else{
				bool flag=false;
				if(p->bf==0)flag=true;
				RotateL(ptr);
				if(!s.empty())if(ptr->value>s.top()->value)s.top()->rightChild=ptr;
				else s.top()->leftChild=ptr;else root=ptr;
				if(flag)break;
			}
		}
	}
	p0->value=q->value;
	delete q;
	delete pt;
	return true;
}
template<class V>AVLTree<V>::~AVLTree(){
	queue<AVLNode<V>* >q;
	if(root==NULL)return;
	q.push(root);
	while(!q.empty()){
		AVLNode<V>* ptr=q.front();
		q.pop();
		if(ptr==NULL)continue;
		q.push(ptr->leftChild);
		q.push(ptr->rightChild);
		delete ptr;
	}//stack is also ok,and I just wanna practice coding queue
}














































































