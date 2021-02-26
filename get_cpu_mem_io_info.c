#include <stdio.h>
#include <string.h>


#include<stdlib.h>
int main()
{
    float reqMemPercentage = 0.9;
    FILE *fp;
    char buffer[180];
    fp = popen("bash get_mem_info.sh", "r");
    fgets(buffer, sizeof(buffer), fp);

    char *tmp;
    tmp=strtok(buffer,"/");
    int freeMem= atoi(tmp);
    tmp = strtok(NULL,"/");
    int totalMem = atoi(tmp);
    
    int needAlloMem = (reqMemPercentage*totalMem - (totalMem - freeMem));
    if(needAlloMem < 0){
        needAlloMem =0;
    }
    printf("curmem %d totalmem %d\n",freeMem,totalMem);
    printf("needAlloMem:%d\n",needAlloMem);
    int* allocateMem = malloc(1000*needAlloMem);
    for(int i=0;i<1000*needAlloMem/4;i++){
        allocateMem[i] = i;
    }
    while(1){

    }
    pclose(fp);
}
