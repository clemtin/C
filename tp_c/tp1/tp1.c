#include <stdio.h>
#include <math.h>

void ex2(){
    printf("Hello world\n");
}

void ex3(){
    int a;
    printf("Choisi un entier\n");
    scanf("%d",&a);
    int x = a*a;
    printf("%d\n",x);

}
void ex4(){
    double a;
    printf("Choisi un entier positif\n");
    scanf("%lf",&a);
    double x = sqrt(a);
    printf("%lf\n",x);
}

void ex5(){
    int a,b,x=0;
    printf("choisi deux entier\n");
    scanf("%d %d",&a,&b);
    x=a;
    a=b;
    b=x;
    printf("x=%d,a=%d,b=%d\n",x,a,b);

}

void ex6(){
    int farenheit;
    printf("Temperature en farenheit\n");
    scanf("%d",&farenheit);
    int celsius = 0;
    celsius = (5*(farenheit-32))/9;
    printf("%d",celsius);
}

int main(void){

    ex2();
    ex3();
    ex4();
    ex5();
    ex6();
    return 0;
}
