#include<stdio.h>//printf
#include<string.h>
#include<unistd.h>//unix speciific
#include<sys/types.h>//pid_t
#include<sys/wait.h>//wait
#include<stdlib.h>
#include<errno.h>

int main(int argc, char const *argv[])
{
    if(argc>1){
        char *endptr;
        errno = 0;
        long numArgs = strtol(argv[1], &endptr, 10);
        if (endptr == argv[1] || *endptr != '\0' || errno == ERANGE) {
            printf("can not convert to integer\n");
            return 1;   
        }
        pid_t pid=fork();
        if(pid==0){
            printf("Child Process: PID=%d, Parent PID=%d\n", getpid(), getppid());
        }
        int* parentArr=malloc(sizeof(int)*numArgs);
        for(long i=0;i<numArgs;i++){
            parentArr[i]=i;
        }
        if(pid==0){
            printf("Parent PID=%d\n", getppid());
            int* childArr=malloc(sizeof(int)*numArgs);
            for(long i=0;i<numArgs;i++){
                childArr[i]=i;
            }
            printf("Child Array: ");
            for(long i=0;i<numArgs;i++){
                printf("%d ",childArr[i]);
            }
            printf("\n");
            free(childArr);
            childArr=NULL;
            exit(0);
        }else{
            wait(NULL);
            printf("Parent Array: ");
            for(long i=0;i<numArgs;i++){
                printf("%d ",parentArr[i]);

            }
            printf("\n");
            free(parentArr);
            parentArr=NULL;
        }
        

    }
    return 0;
}
