#include "types.h"
#include "user.h"
#include "stat.h"
int main()
{
    char *args[6];
    int a,b,c,d;
        a = fork();
        if(a == 0)
        {   
                char* ls_args[] = {"ls", 0};
                set_sched_priority(1);
                printf(1,"pid: %d\t name: ls\t priority: %d\n", getpid(), get_sched_priority(getpid()));
                exec("ls", ls_args);
                exit();
        }
        b = fork();
        if( b == 0){
                args[0]="mkdir";
                args[1]="sample_folder";
                args[2]=0;
                set_sched_priority(3);
                printf(1,"pid: %d\t name: mkdir\t priority: %d\n", getpid(), get_sched_priority(getpid()));
                sleep(300);
                exec("mkdir", args);
                
                exit();
                
        }
        
        c= fork();
        if( c == 0){
                args[0]="find";
                args[1]=".";
                args[2]="-name";
                args[3]="README";
                args[4]=0;
                printf(1,"pid: %d\t name: find\t priority: %d\n", getpid(), get_sched_priority(getpid()));
                sleep(200);
                exec("find", args);
                
                exit();
                
        }
        d = fork();
        if(d==0){

                printf(1,"pid: %d\t name: uniq\t priority: %d\n", getpid(), get_sched_priority(getpid()));
                args[0]="cat";
                args[1]="README";
                args[2]="|";
                args[3]="uniq";
                char *cat_args[] = {"uniq", "sampletext.txt", 0};
                sleep(100);
                exec("uniq", cat_args);

                exit(); 
  
        }
        process_metrics();
        process_metrics();
        process_metrics();
        process_metrics();

    printf(1,"Test done\n");
    exit();
}