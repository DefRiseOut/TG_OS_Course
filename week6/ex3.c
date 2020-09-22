#include <stdio.h>
#include <stdbool.h>

int main()
{
  int n;
  scanf("%d",&n);
  int at[n], bt[n], rt[n];
  bool comp[n];
  for(int i = 0; i<n; ++i){
    scanf("%d %d",&at[i],&bt[i]);
    comp[i] = false;
    rt[i] = 0;
  }
  int quantum;
  scanf("%d",&quantum);
  int flag = n;
  int  time = 0;
  int proc_id = -1, temp_time, totalTAT=0, totalWT=0, last,time_i;
  bool free = true;
  while(flag!=0){
    if(!free&&rt[proc_id]>=bt[proc_id]){
      comp[proc_id] = true;
      flag--;
      free = true;
      totalTAT+=time-at[proc_id];
      totalWT+=time-at[proc_id]-bt[proc_id];
      printf("Process number %d: CT:%d, TAT:%d, WT:%d.\n", proc_id+1,time, time-at[proc_id], time-at[proc_id]-bt[proc_id]);
      if(flag==0){
        break;
      }
    }
    else if(!free&&time-time_i>=quantum){
      free = true;
    }
    else if(!free){
      rt[proc_id]++;
    }
    if(free){
      last = proc_id;
      for(int i = last+1; i<n;i++){
        if(!comp[i]&&at[i]<=time){
          proc_id=i;
          break;
        }
      }
      if(proc_id!=last){
        time_i = time;
        free=false;
        rt[proc_id]++;
      }
      else{
        proc_id=-1;
        for(int i = 0; i<n;i++){
          if(!comp[i]&&at[i]<=time){
            proc_id=i;
            break;
          }
        }
        if(proc_id>=0){
          time_i = time;
          free = false;
          rt[proc_id]++;
        }
        else{
          printf("%d", time);
          proc_id=-1;
          temp_time = 1000000;
          for(int i = 0; i<n;i++){
            if(!comp[i]&&at[i]<=temp_time){
              proc_id=i;
              temp_time = at[i];
            }
          }
          time = at[proc_id];
          time_i = time;
          free = false;
          rt[proc_id]++;
        }
      }
    }
    time++;
  }
  printf("Summary: Average TAT:%f, Average WT:%f.", (float)(totalTAT)/n,(float)(totalWT)/n);
  return 0;
}
