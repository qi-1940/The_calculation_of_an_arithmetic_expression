#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#include "stack.h"

element * to_postfix(element * s){
    element * o=(element *)calloc(100,sizeof(element));
    for(int i=0;i<100;i++){
        o[i].kind=-1;
    }
    Stack op=creat_stack();
    int i=0,j=0;
    while(s[i].kind!=-1){
        if(s[i].kind==DOUBLE_KIND){
            
            o[j++]=s[i];
        }
        else{
            char temp =(char)(op->array[op->top].u.c);
             if(isEmpty(op)){
                push(op,s[i]);
             }
             else if (s[i].u.c==')')
             {
                while((char)(op->array[op->top].u.c)!='('){
                    o[j++]=pop(op);
                }
                pop(op);
                
             }
             else if ((temp=='+'||temp=='-')&&(s[i].u.c=='+'||s[i].u.c=='-'))
             {
                o[j++]=pop(op);
                push(op,s[i]);
             }
             else if ((temp=='*'||temp=='/')&&(s[i].u.c=='+'||s[i].u.c=='-'))
             {
                while((char)(op->array[op->top].u.c)=='*'||(char)(op->array[op->top].u.c)=='/'||
                (char)(op->array[op->top].u.c)=='+'||(char)(op->array[op->top].u.c)=='-'
                ){
                    o[j++]=pop(op);
                }
                push(op,s[i]);
             }
             else if (s[i].u.c=='(')
             {
                push(op,s[i]);
             }
             else
             {
                push(op,s[i]);
             }
        }
        i++;
    }

    while(!isEmpty(op)){
        o[j++]=pop(op);
    }
    free(op);
    return o;
}

double evaluate_by_pfix(element * s){
    double outcome;
    Stack op = creat_stack();
    int i=0;
    while(s[i].kind!=-1){
        if(s[i].kind==DOUBLE_KIND){
            push(op,s[i]);
        }
        else{
            if(s[i].u.c=='+'){
                element e;
                e.kind=DOUBLE_KIND;

                double a,b;
                a=pop(op).u.d;
                b=pop(op).u.d;
                e.u.d=b+a;
                push(op,e);
            }
            else if (s[i].u.c=='-')
            {
                element e;
                e.kind=DOUBLE_KIND;
                double a,b;
                a=pop(op).u.d;
                b=pop(op).u.d;
                e.u.d=b-a;
                push(op,e);
            }
            else if (s[i].u.c=='*')
            {
                element e;
                e.kind=DOUBLE_KIND;
                double a,b;
                a=pop(op).u.d;
                b=pop(op).u.d;
                e.u.d=b*a;
                push(op,e);
            }
            else if (s[i].u.c=='/')
            {
                element e;
                e.kind=DOUBLE_KIND;
                double a,b;
                a=pop(op).u.d;
                b=pop(op).u.d;
                e.u.d=b/a;
                push(op,e);
            }
        }
        i++;
    }
    outcome=pop(op).u.d;
    free(op);
    return outcome;
}

double tran(char * in){
    int i=0;
    double out=0;
    while(in[i]!=0&&in[i]!='.'){

        i++;
    }
    for (int j=0;j<i;j++){
        out+=(in[j]-'0')*pow(10.0,(double)(i-1-j));
    }
    i++;
    int ii=0;
    while(in[i++]!=0){
        ii++;
    }
    i-=ii;
    i--;
    for (int j=0;j<ii;j++){
        out+=(in[j+i]-'0')*pow(10.0,(double)((-j)-1));
    }
    return out;
}

element * cut_apart(char * in){
    char temp[10];
    element * in_;
    int j=0;
    in_=(element*)calloc(100,sizeof(element));
    for(int i=0;i<100;i++){
        in_[i].kind=-1;
    }
    for(int i=0;in[i]!=0&&in[i]!='\n'&&i<=99;i++){

        for(int i=0;i<=9;i++){
            temp[i]='\0';
        }
        
        if((!isdigit(in[i]))&&(in[i]!='.')){
            in_[j].kind=CHAR_KIND;
            in_[j++].u.c=(char)in[i];
        }
        else{
            int o=0;
            temp[o++]=in[i];
            while(isdigit(in[i+1])||in[i+1]=='.'){
                i++;
                temp[o++]=in[i];
            }
            in_[j].kind=DOUBLE_KIND;
            in_[j++].u.d=tran(temp);
        }

    }
    return in_;
}

int main (void){

    //Get the intial input.
    printf("Please input an arithmetic expression:\n");
    char in[100]={'\0'};
    scanf("%s",in);

    //Cut apart the intial input.
    element * in_;
    in_=cut_apart(in);

    //Transform the input into postfix.
    //Evaluate through postfix expression and show the outcome.
    printf("The outcome is %5.5g .\n",evaluate_by_pfix(to_postfix(in_)));

    return 0;
}