#include<stdio.h>
#define Maxsize 100

struct{
char ch;
int pri;
}Lpri[]={{'=',0},{'(',1},{'*',5},{'/',5},{'+',3},{'-',3},{')',6}},
 Rpri[]={{'=',0},{'(',6},{'*',4},{'/',4},{'+',2},{'-',2},{')',1}};//Set up priority

int LeftPri(char op){  //Find LeftPri
    int i=0;
    while(i<7){
        if(Lpri[i].ch==op)return Lpri[i].pri;
        i++;
    }
    return 0;
}
int RightPri(char op){  //Find RightPri
    int i=0;            //"i"can be declared there again
    while(i<7){
        if(Rpri[i].ch==op)return Rpri[i].pri;
        i++;
    }
    return 0;
}
int isop(char op){
    if(op=='('||op==')'||op=='*'||op=='/'||op=='+'||op=='-')return 1;
    else return 0;
}
int Precede(char op1,char op2){      //The reference books named this function for "Precede"
    if(LeftPri(op1)==RightPri(op2))
        return 0;
    else if(LeftPri(op1)>RightPri(op2))return 1;
         else return -1;
}
void Trans(char*exp,char*Postexp){   //Most important and most complex and hardest function,手动微笑
                                     //转化成后缀表达式
    struct{char Data[Maxsize];               //exp:算术表达式  Postexp：后缀表达式 op:临时的用于存放运算符的栈，用后即焚;
           int top;                     //栈指针，top=数组中的元素个数-1，故top的初值为1
           }op;
           op.top=-1;
    int i=0;
    op.top++;
    op.Data[op.top]='=';        //这两个语句入栈时常用
    while(*exp!='\0'){       //挨个扫描exp
        if(!isop(*exp))       //当此时的数组exp的元素是数字
            {
            while(*exp>='0'&&*exp<='9')//进一步直接的确定是数字
            {
                Postexp[i++]=*(exp++);//把exp里面的 数字 放在Postexp
            }
            Postexp[i++]='E';
            }   //每个数字结束都标记一个END
        else                 //当此时的数组exp的元素是操作符
            switch(Precede(op.Data[op.top],*exp))  //此时op栈顶的操作符(op.Data[top])的LeftPri 和 此时exp的操作符的RightPri 进行比较
            {
            case 0:
                op.top--;   //直接把op里面的括号退栈退掉
                exp++;  //exp里面的括号不做处理，直接去处理下一个元素
                break;
            case 1:        //当op中的操作符左优先级比较高，分为两种情况：第一种是op的操作符是
                Postexp[i++]=op.Data[op.top];            //”*“或者“/”;exp的操作符是“+”或者“-”，这时应该先把op里面的乘除退到Postexp
                op.top--;                                //里面，再把加减退到Postexp.第二种情况是op里面是加减乘除，exp里面是右括号，
                break;                                   //这时候就要把op里面除了等号以外所有东西都退出来，然后不
            case -1:
                op.top++;
                op.Data[op.top]=*(exp++);
                break;
            }


    }//这是一开始那个while的括号
    while(op.Data[op.top]!='=')//exp扫描完了，给op擦屁股
        Postexp[i++]=op.Data[op.top--];
    Postexp[i]='\0'; //Postexp结束啦！

}//这是函数结束的括号啦哈哈哈哈哈哈哈终于明白这个鬼计算器是怎么工作的啦哈哈哈哈哈
float CalculatePostexp(char*Postexp){    //这里要用float，不然就会搞出来一个算不了小数点的计算器
    struct{float Data[Maxsize];   //和op一样用后即焚，刚才op用的数组Data占的内存已经被free掉了
           int top;            //top是一个道理
    }st;
    st.top=-1;                         //st代表数值栈
    float a,b,c;
    while(*Postexp!=0)            //一直扫描到Postexp的最后一个元素
    {
        switch(*Postexp){
            case '+':   //这里的算法相对简单许多。只要提出来的是操作符，就把前两个数扽出来算，把算好的数再入栈
                a=st.Data[st.top--];
                b=st.Data[st.top--];//把操作符前两个数提出来分别赋值给a和b
                c=a+b;
                st.Data[++st.top]=c;
                break;
            case'-'://CtrlC+CtrlV
                a=st.Data[st.top--];
                b=st.Data[st.top--];//把操作符前两个数提出来分别赋值给a和b
                c=b-a;
                st.Data[++st.top]=c;
                break;
            case'*':
                a=st.Data[st.top--];
                b=st.Data[st.top--];//把操作符前两个数提出来分别赋值给a和b
                c=a*b;
                st.Data[++st.top]=c;
                break;
            case'/':
                a=st.Data[st.top--];
                b=st.Data[st.top--];//把操作符前两个数提出来分别赋值给a和b
                c=b/a;
                st.Data[++st.top]=c;
                break;
            default://是数字
                c=0;
                while(*Postexp!='E'&&*Postexp>='0'&&*Postexp<='9')
                {
                    c=10*c+(*Postexp-'0');//少用一个变量d
                    Postexp++;
                }
                st.Data[++st.top]=c;
                break;
        }
    Postexp++;//继续扫描下一个
    }
    return st.Data[0];//书上写的st.Data[st.top],其实都一样
}
int main(){//
    char exp[Maxsize];
    scanf("%s",exp);
    printf("%s\n",exp);
    char Postexp[Maxsize];
    Trans(exp,Postexp);
    printf("%s\n",Postexp);
    printf("%.2f\n",CalculatePostexp(Postexp));
    return 0;
}



























