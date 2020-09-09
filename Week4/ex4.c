#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string>
#define Size 50

int main() {
    char *str[Size];
    fgets(str, Size , stdin);
    system(str);
    return 0;
}
