#include <stdio.h>
#include <stdlib.h>
int main()
{
    int n;
    scanf("%d",&n);
    int *ints = malloc(sizeof(int)*n);
    ints[0] = 0;
    for(int i = 1; i < n; i++){
        ints[i] = ints[i-1]+1;
    }
    for(int i = 0; i < n; i++){
        printf("%d ", ints[i]);
    }
    free(ints);
    return 0;
}
