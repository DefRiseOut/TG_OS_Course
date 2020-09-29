#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void *my_realloc(void *ptr, size_t len){
    void *ptrNew;
    if(ptr == NULL){
        ptrNew = malloc(len);
        return ptrNew;
    }
    else if(len <= 0){
        free(ptr);
        return NULL;
    }
    else{
        ptrNew = malloc(len);
        memcpy(ptrNew, ptr, len); //Undefined bahavior. We dont know the size allocated to ptr, so we can only do this.
        free(ptr);
        return ptrNew;
    }
}
int main(){
	return 0;
}
