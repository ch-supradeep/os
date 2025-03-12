#include "types.h"
#include "user.h"

int main(int argc,char *argv[]) {
    if(argc != 2){
        printf(2, "Usage: job_position must have pid as an argument\n");
        exit();
    }
    int pid = atoi(argv[1]);
    int position = job_position(pid);
    if(position==-1) {
        printf(1,"either process %d may not exist or not in runnable state\n",pid);
    }
    else {
        printf(1,"process %d is present at %d in execution queue\n",pid,job_position);
    }
    exit();
}