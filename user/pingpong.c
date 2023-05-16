#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]){
    int p1[2],p2[2];
    int status;
    uchar buf[1];
    uchar wbuf[]={0x86};
    pipe(p1);
    pipe(p2);
    if(fork()==0){
        read(p1[0],buf,sizeof(buf));
        if(buf[0]==0x86){
            printf("%d: received ping\n",getpid());
            write(p2[1],wbuf,1);
        }
        exit(0);
    }
    else{
        write(p1[1],wbuf,1);
        wait(&status);
        read(p2[0],buf,sizeof(buf));      
        if(buf[0]==0x86){
            printf("%d: received pong\n",getpid());
        }
    }
    exit(0);
}