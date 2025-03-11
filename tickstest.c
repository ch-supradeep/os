#include "types.h"
#include "stat.h"
#include "user.h"

int main() {
    int pid = fork(); // Create a child process

    if (pid < 0) {
        printf(1, "Fork failed!\n");
    } else if (pid == 0) {
        // Child process: Run for some time
        for (int i=0;i<10;i++){} // Waste some CPU time
        exit();
    } else {
        // Parent process: Wait a bit, then check scheduled time
        sleep(10);
        int ticks = ticks_running(pid);
        while (ticks != -1) {
            printf(1, "Scheduled time for PID %d: %d ticks\n", pid, ticks);
            sleep(15); // Small delay to avoid excessive CPU usage
            ticks = ticks_running(pid);
        }
        printf(1, "Process %d has exited. Final tick count: %d\n", pid, ticks);
        wait();
    }
    exit();
}
