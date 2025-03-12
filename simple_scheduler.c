#include "types.h"
#include "user.h"
#include "stat.h"
#include "syscall.h"

int main()
{
    
    int  b, c, d;
    char *args[7];
    
//     a = fork();
//     if (a == 0) {   
//         char *stressfs_args[] = {"stressfs", 0};
//         printf(1, "pid: %d\t name: stressfs\t job_position: %d\n", getpid(), job_position(getpid()));
//         exec("stressfs", stressfs_args);
//         exit();
//     }
    
b = fork();
if( b == 0){
       printf(1,"pid: %d\t name: uniq\t fifo_position: %d\n", getpid(), job_position(getpid()));
        args[0]="cat";
        args[1]="README";
        args[2]="|";
        args[3]="uniq";
        char *cat_args[] = {"uniq", "sampletext.txt", 0};
        sleep(100);
        exec("uniq", cat_args);
     
        exit(); 
        
}

c= fork();
if( c == 0){
        args[0]="find";
        args[1]=".";
        args[2]="-name";
        args[3]="README";
        args[4]=0;
        printf(1,"pid: %d\t name: find\t fifo_position: %d\n", getpid(), job_position(getpid()));
        sleep(200);
        exec("find", args);
        
        exit();
        
}
d = fork();
if(d==0){
        args[0]="mkdir";
        args[1]="sample_folder";
        printf(1,"pid: %d\t name: mkdir\t fifo_position: %d\n", getpid(), job_position(getpid()));
        sleep(300);
        exec("mkdir", args);
        
        exit();
        

}
    
//     wait();
    process_metrics();
    process_metrics();
    process_metrics();
    
    printf(1, "Test done\n");
    exit();
}
