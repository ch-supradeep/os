#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include <stddef.h>

char*
fmtname(char *path)
{
  static char buf[DIRSIZ+1];
  char *p;

  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  if(strlen(p) >= DIRSIZ)
    return p;
  memmove(buf, p, strlen(p));
  memset(buf+strlen(p), ' ', DIRSIZ-strlen(p));
  return buf;
}

void
ls(char *path,int display_hidden)
{
  if(path==NULL) {
    path=".";
  }
  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;

  if((fd = open(path, 0)) < 0){
    printf(2, "ls: cannot open %s\n", path);
    return;
  }

  if(fstat(fd, &st) < 0){
    printf(2, "ls: cannot stat %s\n", path);
    close(fd);
    return;
  }

  switch(st.type){
  case T_FILE:
    printf(1, "%s %d %d %d\n", fmtname(path), st.type, st.ino, st.size);
    break;

  case T_DIR:
    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
      printf(1, "ls: path too long\n");
      break;
    }
    strcpy(buf, path);
    p = buf+strlen(buf);
    *p++ = '/';
    while(read(fd, &de, sizeof(de)) == sizeof(de)){
      if(de.inum == 0)
        continue;
      if(display_hidden==0&&de.name[0]=='.') {
        continue;
      }
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;
      if(stat(buf, &st) < 0){
        printf(1, "ls: cannot stat %s\n", buf);
        continue;
      }
      if(st.type==T_DIR) {
        printf(1, "%s/ %d %d %d\n", fmtname(buf), st.type, st.ino, st.size);
      }
      else {
        printf(1, "%s %d %d %d\n", fmtname(buf), st.type, st.ino, st.size);
      }
    }
    break;
  }
  close(fd);
}

int
main(int argc, char *argv[])
{
  int display_hidden=0;

  // if(argc < 2){
  //   ls(".",display_hidden);
  //   exit();
  // }
  // if(argc>=2&&argv[1][0]=='-'&&argv[1][1]=='a') {
  //   display_hidden=1;
  // }
  // for(int i=1; i<argc; i++)
  //   ls(argv[i],display_hidden);
  // exit();

  // char *dir_path = NULL;
  if(argc>1) {
    if(argc>=2&&argv[1][0]=='-'&&argv[1][1]=='a') {
      display_hidden=1;
    }
  }
  char *default_directory_path=".";
  ls(default_directory_path,display_hidden);
  exit();
}
