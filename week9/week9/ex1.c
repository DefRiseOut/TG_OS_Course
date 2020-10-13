#include <stdio.h>
#include <stdbool.h>
#include <math.h>

int main(void) {
  // Opening the file for reading.
  FILE *file;
  file = fopen("input.txt","r");
  // Number of page frames.
  int fnum = 100;
  
  int the_numba = pow(2, 15);

  int pages[fnum], page_ref[fnum];
  int j;
  for(j = 0; j < fnum; j++){
    pages[j] = -1; //Page frames.
    page_ref[j] = 0; //References of page frames.
  }
  
  // Current page number.
  int pn;

  //Variables used during the algorithm.
  int index, min_ref;
  bool flag;

  //Counters.
  int hits = 0, misses = 0;   

  while (!feof (file)){
    fscanf (file, "%d", &pn); //Read the next page reference.

    index = -1;
    for(j = 0; j < fnum; j++){ //Hit detection.
      if(pn == pages[j]){
        hits++;
        index = j;
        break;
      }
    }

    if(index != -1){ //If a hit oocured.
      for(j = 0; j < fnum; j++){
        page_ref[j] = page_ref[j]/2;//Shift right.
      }
      page_ref[index]+=the_numba;//1st bit in 16-bit reference code is 1.
    }
    else{ //Page fault.
      misses++;
      min_ref = page_ref[0];
      index = 0;
      flag = true;
      for(j = 0; j < fnum; j++){//Find the lowest reference value or an empty page if possible.
        if(pages[j] == -1 && flag){ //First empty page.
          min_ref = 0;
          index = j;
          flag = false;
        }
        if(page_ref[j]<min_ref){
          min_ref = page_ref[j];
          index = j;
        }
        page_ref[j] = page_ref[j]/2;//Shift right after the check.
      }
      pages[index] = pn; //Switch the page.
      page_ref[index] = the_numba;
    }      
  }
  float hitratio = (float)(hits)/(misses+hits), missratio = (float)(misses)/(misses+hits);
  printf("Hit ratio:%f\nMiss ratio:%f\n",hitratio,missratio);
  return 0;
}