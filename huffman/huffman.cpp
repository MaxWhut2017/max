#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
#include "heap.h"
//#include "binarytree.h"
//#define DEBUG
using namespace std;
template<class T>struct huffmanNode{
    T data;
	string s;
    huffmanNode<T>* leftChild;
    huffmanNode<T>* rightChild;
    huffmanNode():leftChild(NULL),rightChild(NULL){}
    huffmanNode(T elem,huffmanNode<T>* left,huffmanNode<T>* right):data(elem),leftChild(left),rightChild(right){}
    huffmanNode(huffmanNode<T> *node1,huffmanNode<T> *node2){
        leftChild=node1;
        rightChild=node2;
        data=node1->data+node2->data;
    }
};
template<class T>huffmanNode<T>* huffman(T* node,int n){
    minHeap<huffmanNode<T>* > hp;
    hp.makeEmpty();
    for(int i=0;i<n;i++){
        huffmanNode<T>* hn=new huffmanNode<T>(node[i],NULL,NULL);
        hp.insert(hn);
    }

    for(int i=0;i<n-1;i++){
        huffmanNode<T>* first=hp.removeMin();
        huffmanNode<T>* second=hp.removeMin();
		huffmanNode<T>* t=new huffmanNode<T>(first,second);
        hp.insert(t);
		//printf("%c %c %c\n",first->data.c,second->data.c,t->data.c);
    }
    return hp.removeMin();
}

struct word{
    char c='#';
    double f;
    bool operator < (const word& o)const{
        return f < o.f;
    }
    word operator + (const word& o){
        word ret;
        //ret.c='#';
        ret.f=f+o.f;
        return ret;
    }
}w[32];
string code[30];
void dfs(huffmanNode<word>* h,string s){
    
}
#ifndef DEBUG:

int main()
{
    char s[100];
	//char c;printf("%c",c);
    cin >> s;
    int cnt[30];memset(cnt,0,sizeof(cnt));
    for(int i=0;i<strlen(s);i++){
        cnt[s[i]-'a']++;
    }
    for(int i=0;i<26;i++){
        w[i].c='a'+i;
        w[i].f=(double)(cnt[i])/(double)strlen(s);
    }
	for(int i=0;i<26;i++){
		//printf("%c",w[i].c);
	}
    #ifdef DEBUG2:
    for(int i=0;i<26;i++){
        //printf("cnt[%d]=%d ",i,cnt[i]);
        //printf("w[%d].c=%c,w[%d].f=%lf\n",i,w[i].c,i,w[i].f);
    }
    #endif
    huffmanNode<word>* hN=huffman(w,26);
	//printf("%c\n",hN->leftChild->data.c);
    string str="#";
    
	queue<huffmanNode<word>* > q;
    q.push(hN);
	//hN->s=' ';
	//printf("%c\n",h->leftChild->data.c);
    while(!q.empty()){
        huffmanNode<word>* t=q.front();
        q.pop();	
        if(t->data.c!='#'){
			code[t->data.c-'a']=t->s;
			continue;
		}
        //printf("c=%c\n",t->data.c);
        //printf("%d\n",flag);
		q.push(t->leftChild);
        q.push(t->rightChild);
        t->leftChild->s=t->s+'0';
        t->rightChild->s=t->s+'1';

    }

    for(int i=0;i<strlen(s);i++){
        cout << code[s[i]-'a'];
    }
	printf("\n");
	for(int i=0;i<26;i++){
		printf("%c",i+'a');
		cout << code[i] << '\n';
	}
	string bitcode;
	cin >> bitcode;
	huffmanNode<word>* top=hN;
	for(int i=0;i<bitcode.size();i++){
		if(bitcode[i]=='0'){
			top=top->leftChild;
		}
		else if(bitcode[i]=='1'){
			top=top->rightChild;
		}
		if(top->data.c != '#'){
			printf("%c",top->data.c);
			top=hN;
		}
	}
    return 0;
}

#endif // DEBUG

#ifdef DEBUG:

int main(){
    printf("debug\n");
    double num[10]={2.2,5.5,536.3,354.5,6573564.6,23.77,54.5,32.5,67.0,3452.9};
    minHeap<double> hp(num,10);
    for(int i=0;i<=10;i++){
        printf("%lf ",hp.removeMin());
    }
    return 0;
}

#endif // DEBUG


















