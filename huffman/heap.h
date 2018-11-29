#include <iostream>
#include <assert.h>
#include <algorithm>
using namespace std;
const int DEFAULT_SIZE=100;
template<class T>bool lt(T a,T b){
	return a->data<b->data;
}
template<class T>class minHeap{
private:
    T* heap;
    int maxSize;
    int currentSize;
    void _siftUp(int st);
    void _siftDown(int st,int ed);
public:
    minHeap(int maxsz=DEFAULT_SIZE);
    minHeap(T* arr,int n);
    ~minHeap(){delete[] heap;}

    bool insert(const T& x);
    T removeMin();

    bool isEmpty(){return currentSize==0;}
    bool isFull(){return currentSize==maxSize;}
    void makeEmpty(){currentSize=0;}
};
template<class T>minHeap<T>::minHeap(int maxsz){
    maxSize=max(maxsz,DEFAULT_SIZE);
    currentSize=0;
    heap=new T[maxSize];
    assert(heap!=NULL);
}
template<class T>minHeap<T>::minHeap(T* arr,int n){
    maxSize=max(n,DEFAULT_SIZE);
    currentSize=n;
    heap=new T[maxSize];
    assert(heap!=NULL);
    for(int i=0;i<n;i++)heap[i]=arr[i];
    int cur=(n-2)/2;
    while(cur>=0){
        _siftDown(cur,n-1);
        cur--;
    }
}
template<class T>void minHeap<T>::_siftUp(int st){
    T temp=heap[st];
    int j=st;
    int i=(j-1)/2;
    while(i>0 && lt(heap[j],heap[i])){
        heap[j]=heap[i];
        j=i;
        i=(j-1)/2;
    }
    heap[j]=temp;
}
template<class T>void minHeap<T>::_siftDown(int st,int ed){
    int j=st;
    int i=j*2+1;
    T temp=heap[j];
    while(i<=ed){
        if(i<ed && lt(heap[i+1],heap[i])){
            i++;
        }
        if(lt(temp,heap[i]))break;
        heap[j]=heap[i];
        j=i;
        i=j*2+1;
    }
    heap[j]=temp;
}
template<class T>bool minHeap<T>::insert(const T& x){
    if(currentSize==maxSize)return false;
    heap[currentSize]=x;
    _siftUp(currentSize);
    currentSize++;
    return true;
}
template<class T>T minHeap<T>::removeMin(){
    assert(currentSize!=0);
    T temp=heap[0];
    heap[0]=heap[currentSize-1];
    currentSize--;
    _siftDown(0,currentSize-1);
    return temp;
}











































