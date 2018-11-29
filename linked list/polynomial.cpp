#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
struct LinkNode{
    float coef;
    int exp;
    LinkNode* link;
    LinkNode(const int e,const float c,LinkNode* p = NULL){
        coef=c;
        exp=e;
        link = p;
    }
    LinkNode* insertAfter(int e,float c);
};
LinkNode* LinkNode::insertAfter(int e,float c){//插入链表中间
    link = new LinkNode(e,c,link);
    return link;
}
class Polynomal{
public:
    Polynomal(){first = new LinkNode(-1,0);}
    Polynomal(LinkNode& L);//复制构造函数，复制L
    ~Polynomal(){Empty();}//析构函数直接置空表即可
    void Empty();
    int maxOrder();
    //int Len()const;
    LinkNode* getFirst()const{return first;}
    //void setData(const int i,const T& x);//将第i个元素改为x
    //void Insert(const int i,const T& x);//insert x after i
    bool isEmpty()const{
        return first->link == NULL;
    }
    Polynomal operator = (Polynomal& P);//赋值函数重载
    friend Polynomal operator + (Polynomal& ,Polynomal& );
    friend Polynomal operator * (Polynomal& ,Polynomal& );
    void input();
    void output();
private:
    LinkNode* first;
};
Polynomal::Polynomal(LinkNode& P){//复制构造函数
    first = new LinkNode(-1,0);
    LinkNode* temp=first;//temp从first开始
    LinkNode* cur=P.link;//cur从指向L的第一个元素开始
    while(cur !=NULL){
        temp->insertAfter(cur->exp,cur->coef);
    }
    cur=cur->link;
    temp=temp->link;
}
int Polynomal::maxOrder(){
    LinkNode* cur=first;
    while(cur->link != NULL){
        cur=cur->link;
    }
    return cur->exp;
}
Polynomal Polynomal::operator = (Polynomal& P){
    LinkNode* tempfirst=first=new LinkNode(-1,0);
    LinkNode* cur=P.getFirst()->link;
    while(cur != NULL){
        tempfirst=tempfirst->insertAfter(cur->exp,cur->coef);
        cur=cur->link;
    }
    return* this;//返回操作对象，this is 操作对象指针
}
void Polynomal::Empty(){
    LinkNode* temp=first;
    while(temp->link != NULL){
        first=temp->link;
        delete temp;
        temp=first;
    }
    delete temp;
}
void Polynomal::input(){
    int N;
    int e;
    float c;
    cin >> N;
    LinkNode* rear=first;
    for(int i=0;i<N;i++){
        cin >> e >> c;
        rear->link=new LinkNode(e,c);
        rear=rear->link;
    }
}
void Polynomal::output(){
    LinkNode* temp=first->link;
    int cnt=0;
    while(temp != NULL){
        //coef
        if(temp->coef>1e-6 && cnt)cout << '+';//need +
        if(temp->coef-1.0 > 1e-6)cout << temp->coef;//omit 1,need coef
        if(temp->exp==0 && temp->coef-1.0 < 1e-6)cout << 1;//not omit 1
        //exp
        switch(temp->exp){
            case 0:break;//hasn't x,coef straightly
            case 1:cout << "x";break;//has x only
            default: cout << "x" << temp->exp;break;
        }

        temp=temp->link;
        cnt++;
    }
    cout << "\n";
}
Polynomal operator + (Polynomal& PA,Polynomal& PB){
    LinkNode* pa;
    LinkNode* pb;
    LinkNode* pc;
    Polynomal C;
    float sum;
    pc=C.getFirst();
    pa=PA.getFirst()->link;
    pb=PB.getFirst()->link;

    while(pa != NULL && pb != NULL){
        if(pa->exp == pb->exp){
            sum=pa->coef+pb->coef;
            if(fabs(sum)>1e-6){
                pc=pc->insertAfter(pa->exp,sum);
            }
            pa=pa->link;
            pb=pb->link;
        }
        else{
            if(pa->exp < pb->exp){
                pc=pc->insertAfter(pa->exp,pa->coef);
                pa=pa->link;
            }
            else{
                if(pa->exp > pb->exp){
                    pc=pc->insertAfter(pb->exp,pb->coef);
                    pb=pb->link;
                }
            }
        }
    }
    while(pa != NULL){
        pc=pc->insertAfter(pa->exp,pa->coef);
        pa=pa->link;
    }
    while(pb != NULL){
        pc=pc->insertAfter(pb->exp,pb->coef);
        pb=pb->link;
    }
    return C;
}
Polynomal operator * (Polynomal& PA,Polynomal& PB){
    Polynomal D;
    LinkNode* pd=D.getFirst();
    int OA=PA.maxOrder();
    int OB=PB.maxOrder();
    int OD=OA+OB;
    float *res=new float[OD+5];
    for(int i=0;i<=OD;i++)res[i]=0.0;
    LinkNode* pa=PA.getFirst()->link;
    LinkNode* pb=PB.getFirst()->link;
    while(pa){
        pb=PB.getFirst()->link;
        while(pb){
            int newexp=pa->exp+pb->exp;
            float newcoef=pa->coef*pb->coef;
            res[newexp]+=newcoef;
            pb=pb->link;
        }
        pa=pa->link;
    }
    for(int i=0;i<=OD;i++)if(fabs(res[i])>1e-6){
        pd=pd->insertAfter(i,res[i]);
    }
    return D;
}
int main(){
    Polynomal A,B;
    A.input();
    B.input();
    cout << "Polynomal A: ";
    A.output();
    cout << "Polynomal B: ";
    B.output();
    Polynomal C=A+B;
    cout << "Polynomal C=A+B: ";
    C.output();
    Polynomal D=A*B;
    cout << "Polynomal D=A*B: ";
    D.output();
    return 0;
}
/*
3
0 1
2 1
3 1
2
1 3
4 4
*/

























