#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


static int i, k=0, status, n;
static int p1[2], buf[35], wbuf[35], p[2];

// 解决pipe不回收问题
int prime(int p_read){
    pipe(p);
    // printf("%d\n",p[0]);
    n = read(p_read, buf, sizeof(buf));//read返回0怎么办/n=字节数，要除sizeof int
    if(n == 0){
        exit(0);
    }
    close(p_read);
    printf("prime %d\n", buf[0]);
    for(i = 0; i<n/sizeof(int); i++){
        if(buf[i] % buf[0] != 0){
            wbuf[k] = buf[i];
            k++;
        }
    }
    write(p[1], wbuf, k*sizeof(int));
    k=0;
    close(p[1]);
    if(fork() == 0){
        prime(p[0]);
    }
    else{
        close(p[0]);
        wait(&status);
    }
    exit(0);
}


int main(){
    pipe(p1);//可以一个个传递
    for(i = 2; i<=35; i++){
        buf[k] = i; 
        k++;        
    }
    write(p1[1], buf, k*sizeof(int));
    k=0;
    close(p1[1]);
    if(fork() == 0){
        prime(p1[0]);//不用退出进程了，在prime里退出
    }
    else{
        close(p1[0]);//父进程关闭管道对子进程没有影响？_没有
        wait(&status);
    }
    exit(0);
}