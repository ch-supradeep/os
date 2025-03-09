#include "stat.h"
#include "types.h"
#include "user.h"


int main(int argc,char *argv[]) {
    if(argc<2) {
        printf(1,"please specify time\n");
       
    }
    else {
        int duration = atoi(argv[1]);
        if(duration>0) {
            sleep(duration);
        }
        else {
            printf(1,"time cannot be in negative\n");
        }
    }
     exit();
} 