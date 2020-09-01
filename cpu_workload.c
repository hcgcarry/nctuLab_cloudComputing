/* Short test program to test the pthread_setaffinity_np
* (which sets the affinity of threads to processors).
* Compile: gcc pthread_setaffinity_np_test.c
*              -o pthread_setaffinity_np_test -lm -lpthread
* Usage: ./pthread_setaffinity_test
*
* Open a "top"-window at the same time and see all the work
* being done on CPU 0 first and after a short wait on CPU 1.
* Repeat with different numbers to make sure, it is not a
* coincidence.
*/
#define _GNU_SOURCE
 
#include <stdio.h>
#include <math.h>
#include <pthread.h>
#include <stdlib.h>
#include "cpu_info.h"
cpu_set_t cpuset,cpuget;
 
double waste_time(float workload_level)
{
    struct tms tmsstart, tmsend;
    float workload_level = 0.8;
    int workTime = 1000 * workload_level;
    int idelTime = 1000 - workTime;
    times(&tmsstart);
    while (1){
        int i=100;
        while(i--){
        }
        times(&tmsend);
        if((tmsend->tms_utime - tmsstart->tms_utime)){
            sleep(idelTime);
            times(&tmsstart)
        }

    }
}
 
void *thread_func(void *param)
{   
    int *thread_param = (int*)param;
    CPU_ZERO(&cpuset);
    CPU_SET(thread_param[0], &cpuset); /* cpu 0 is in cpuset now */
    
    /* bind process to processor 0 */
    if (pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset) !=0) {
        perror("pthread_setaffinity_np");
    }  


    printf("Core %d is running!\n",thread_param[0]);
    /* waste some time so the work is visible with "top" */
	  printf("result: %f\n", waste_time(5));
    pthread_exit(NULL);

}
 
int *thread_param[CPU_NUM];

int main(int argc, char *argv[])
{ 

    int workload_level = 60;
    pthread_t cpu_thread[CPU_NUM];
    time_t startwtime, endwtime;
    startwtime = time (NULL); 

    // initial
    for(int i=0;i<CPU_NUM;i++){
        thread_param[i] = (int*)malloc(sizeof(int)*6);
        thread_param[i][0] = i;
        thread_param[i][1] = workload_level;
    }
    

    for(int i=0;i<CPU_NUM;i++){
        if (pthread_create(&cpu_thread[i], NULL, thread_func,
            (void*)thread_param[i]) != 0) {
            perror("pthread_create");
        }
        else{
            printf("thread %d created\n",i);
        }
        
    }

    // join
    for(int i=0;i<CPU_NUM;i++){
        pthread_join(cpu_thread[i],NULL);
    }
    endwtime = time (NULL);
    printf ("wall clock time = %ld\n", (endwtime - startwtime));
    return 0;
}


