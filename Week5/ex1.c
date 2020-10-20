#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <pthread.h>

#After a fix, threads could not be scheduled in any order, because threads would only be created after the previous has exited.
void *threadFunct(void *threadID){
    int *myID = (int *)threadID;
    printf("%s", "Printing from thread number ");
    printf("%d\n", *myID);
    return NULL;
}

int main()
{
    int N = 3;
    pthread_t thrdId;
    for(int i = 0; i < N; i++){
        printf("Creating thread number %d\n", i);
        pthread_create(&thrdId, NULL, threadFunct, &i); 
        pthread_join(thrdId, NULL);
    }
    
    return 0;
}
