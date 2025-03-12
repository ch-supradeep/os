#include "types.h"
#include "user.h"

int main() {
    int start, end;
    int pid = getpid();
    start = ticks_running(pid);
    for(volatile int i=0;i<1000000000;i++) {
        // wasting some cpu cycles
    }
    end = ticks_running(pid);
    printf(1,"process %d has taken %d ticks\n",pid,end-start);

    exit();
}
