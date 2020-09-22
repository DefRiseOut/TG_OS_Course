#include <stdio.h>
#include <stdbool.h>

int main()
{
  int n;
  scanf("%d",&n);
  int at[n], bt[n];
  bool comp[n];
  for(int i = 0; i<n; ++i){
    scanf("%d %d",&at[i],&bt[i]);
    comp[i] = false;
  }
  int flag = n;
  int  time = 0;
  int temp_time, proc_id, sched_time, time_i, totalTAT=0, totalWT=0;
  bool free = true;
  while(flag!=0){
    if(time>=sched_time&&!free){
      comp[proc_id] = true;
      flag--;
      free = true;
      totalTAT+=time-time_i;
      totalWT+=time-time_i-bt[proc_id];
      printf("Process number %d: CT:%d, TAT:%d, WT:%d.\n", proc_id+1,time, time-time_i, time-time_i-bt[proc_id]);
    }
    if(free){
      temp_time = 10000000;
      proc_id = -1;
      for(int i = 0; i<n; ++i){
        if(!comp[i]&&at[i]<temp_time){
          temp_time = at[i];
          proc_id = i;
        }
      }
      if(at[proc_id]<=time){
        sched_time = time+bt[proc_id];
        time_i = time;
        free = false;
      }
      else{
        time = at[proc_id];
        sched_time = time+bt[proc_id];
        time_i = time;
        free = false;
      }
    }
    time++;
  }
  printf("Summary: Average TAT:%f, Average WT:%f.", (float)(totalTAT)/n,(float)(totalWT)/n);
  return 0;
}
