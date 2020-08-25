#include <stdio.h>
#include <stdlib.h>
 
int main(int argc, char *argv[]) {
    int n;
    sscanf(argv[1], "%d", &n);
    int k = 1;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < 2*n-1; j++){
            if(abs(j-n+1)>=k){
                printf("%c", ' ');
            }
            else{
                printf("%c", '*');
            }
        }
        k=k+1;
        printf("\n");
    }
    return 0;
}
