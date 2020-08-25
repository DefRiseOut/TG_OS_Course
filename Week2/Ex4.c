#include <stdio.h>


void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    printf("Please write two integers: ");
    int a, b;
    scanf("%d %d", &a, &b);
    swap(&a, &b);
    printf("Swaped integers: ");
    printf("%d %d", a, b);
}
