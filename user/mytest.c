#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(){
    int p[2];
    pipe(p);
    printf("%d\n", p[0]);
    if(fork() == 0){
        printf("c:%d\n", p[0]);
        printf("%d", p[1]);

    }
    else{
        // printf("p:%d\n",p[0]);
        // close(p[0]);
    }
    exit(0);
}