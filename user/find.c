#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

char buf[512], *p;
int fd;
struct stat st;
struct dirent de;

char*
fmtname(char *path)//路径变为文件名
{
  static char buf[DIRSIZ+1];
  char *p;

  // Find first character after last slash.
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  // Return blank-padded name.
  if(strlen(p) >= DIRSIZ)
    return p;
  memmove(buf, p, strlen(p));
  memset(buf+strlen(p), ' ', DIRSIZ-strlen(p));
  return buf;
}

void find(char *path, char *fname){
    fd = open(path, 0);
    strcpy(buf, path);
    p=buf+strlen(path);
    *p++ = '/';
    // printf("%d", fd);
    //对文件夹里的每个项目查找，文件就做字符串对比，文件夹就递归调用
    while(read(fd, &de, sizeof(de)) == sizeof(de)){
        //改为文件夹内部路径
        if(de.inum == 0){
            continue;
        }
        memmove(p, de.name, sizeof(de.name));
        p[sizeof(de.name)]=0;
        // printf("%s", buf);
        stat(buf, &st);
        if (st.type == T_FILE)
        {
            if (strcmp(de.name, fname) == 0)
            {
                printf("%s\n", buf);
            }
        }
        else if(st.type == T_DIR){
            if(strcmp(de.name, ".") && strcmp(de.name, ".."))
                find(buf, fname);
        }
    }
}

int main(int argc, char *argv[]){
    if (argc <= 2){
        fprintf(2, "paremeter error");
    }
    else{
        find(argv[1], argv[2]);
    }
    exit(0);
}