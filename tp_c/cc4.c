#include <stdlib.h>
#include <stdio.h>


void testcc(int *p){
    *p=1;
}

void q1(){
        int i=1;
        for(i=1; i<=4;i++)
            printf("%d",i);
            printf("%d",i);

printf("\n");
}

void q2(){

int a=0, Tab[4]={1,2,3,4};
while(a<4)
{
    Tab[a]=Tab[a]+1;
    a=a+2;
    
}
for(int b=0;b<4;b++){
    printf("%d",Tab[b]);
}

printf("\n");
}

void q3(){
int w=1,aza=3,z=2;
if(w<aza)
{
    if(aza<z) printf("a<b<c");

}
else printf("a>=b");
}

void q4(){

int val;
int compteur = 0;
scanf("%d",&val);
while (val!=0){
    if (val>0){
        compteur++;}
    scanf("%d",&val);

}
printf("%d\n",compteur);




char ch[5]= "abcd";
ch[0]='z';
ch[3]='z';


char ahah[3] = "12";
char *p;
p=ch+1;
// cela signifie que le poitneur p 
// pointe sur 2



}

int main(void){

int *aka;
testcc(aka);
printf("%d",*aka);

return 0;
}

