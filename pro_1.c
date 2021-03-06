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
//#include <unistd.h>　

cpu_set_t cpuset,cpuget;
 
double waste_time(long n)
{
    /*
    double res = 0;
    long i = 0;
    while (i <n * 200000000) {
        i++;
        res += sqrt(i);
    }
    return res;
    */
   while(1){

   }
}
 
void *thread_func(void *param)
{   


    printf("Core 0 is running!\n");
    /* waste some time so the work is visible with "top" */
    waste_time(1);

    pthread_exit(NULL);

}
 
int main(int argc, char *argv[])
{ 

    pthread_t my_thread;
    time_t startwtime, endwtime;
    startwtime = time (NULL); 
    
    /* bind process to processor 0 */

    if (pthread_create(&my_thread, NULL, thread_func,
        NULL) != 0) {
        perror("pthread_create");
    }

    CPU_ZERO(&cpuset);
    CPU_SET(0, &cpuset); /* cpu 0 is in cpuset now */
    if (pthread_setaffinity_np(my_thread, sizeof(cpu_set_t), &cpuset) !=0) {
        perror("pthread_setaffinity_np error");
    }  
    

    sleep(6);
    printf("switch cpu\n");


    CPU_ZERO(&cpuset);

    CPU_SET(8, &cpuset); /* cpu 0 is in cpuset now */
    
    /* bind process to processor 0 */
    if (pthread_setaffinity_np(my_thread, sizeof(cpu_set_t), &cpuset) !=0) {
        perror("pthread_setaffinity_np error");
    }  

    pthread_join(my_thread,NULL);
    endwtime = time (NULL);
    printf ("wall clock time = %d\n", (endwtime - startwtime));
    return 0;
}

