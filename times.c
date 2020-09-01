#include <sys/times.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

static void do_cmd(char *);
static void pr_times(clock_t, struct tms *, struct tms *);

int main(int argc, char *argv[]){
        int i;
        for(i=1; argv[i]!=NULL; i++){
                do_cmd(argv[i]);
        }
        exit(1);
}
static void do_cmd(char *cmd){
        struct tms tmsstart, tmsend;
        clock_t start, end;
        int status;
        if((start=times(&tmsstart))== -1)
                puts("times error");
        if((status=system(cmd))<0)
                puts("system error");
        if((end=times(&tmsend))== -1)
                puts("times error");
        pr_times(end-start, &tmsstart, &tmsend);
        exit(0);
}
static void pr_times(clock_t real, struct tms *tmsstart, struct tms *tmsend){
        static long clktck=0;
        if(0 == clktck)
                if((clktck=sysconf(_SC_CLK_TCK))<0)
                           puts("sysconf err");
        printf("real:%7.2f\n", real/(double)clktck);
        printf("user-cpu:%7.2f\n", (tmsend->tms_utime - tmsstart->tms_utime)/(double)clktck);
        printf("system-cpu:%7.2f\n", (tmsend->tms_stime - tmsstart->tms_stime)/(double)clktck);
        printf("child-user-cpu:%7.2f\n", (tmsend->tms_cutime - tmsstart->tms_cutime)/(double)clktck);
        printf("child-system-cpu:%7.2f\n", (tmsend->tms_cstime - tmsstart->tms_cstime)/(double)clktck);
}