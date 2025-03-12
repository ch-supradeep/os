#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  if(argc != 2){
    printf(2, "Usage: ticks_running must have pid as an argument\n");
    exit();
  }
  int pid = atoi(argv[1]);
  int ticks_time = ticks_running(pid);
  if(ticks_time==-1) {
printf(2, "process does not exist with pid %d: %d\n", pid, ticks_time);
  }
  else if(ticks_time==0) {
    printf(2, "unscheduled process with pid %d: %d\n", pid, ticks_time);
  }
  else {
    
    printf(1, "Scheduled time for process %d: %d\n", pid, ticks_time);
  }
  exit();
}