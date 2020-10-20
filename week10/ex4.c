#include <stdio.h>
#include <dirent.h>
#include <string.h>

int main(void) {
  DIR *dirp = opendir("./tmp");
  if(dirp == NULL) return 0;
  struct dirent* dp;
  char names[1000][1000];
  long inums[1000];
  int size = 0;
  while ((dp = readdir(dirp)) != NULL){
    strcpy(names[size], dp->d_name);
    inums[size] = dp->d_ino;
    size++;
  }
  int i, j, k;
  long now_inum;
  char results[100][100];
  for(i = 0; i < size; i++){
    if((now_inum=inums[i])>0){
      k = 0;
      for(j = i + 1; j < size; j++){
        if(inums[i]==inums[j]){
          inums[j] = -1;
          strcpy(results[k],names[j]);
          k++;
        }
      }
      if(k!=0){
        for(j = 0; j < k; j++){
          printf("%s, ", results[j]);
        }
        printf("%s. Inode number: %lu\n", names[i], inums[i]);
      }
    }
  }
  return 0;
}