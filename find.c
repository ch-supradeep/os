#include "stat.h"
#include "types.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"
#include <stddef.h>

char* fmtname(char *path) {
    static char buf[DIRSIZ+1];
    char *p;
    for (p = path + strlen(path); p >= path && *p != '/'; p--);
    p++;
    if (strlen(p) >= DIRSIZ)
        return p;
    memmove(buf, p, strlen(p));
    buf[strlen(p)] = '\0';
    return buf;
}

void find(char *path, char *filename, int type_flag, char type, int inum_flag, int inum, char iFlagSign, int printi_flag) {
    char buf[512], *p;
    int fd;
    struct stat st;
    struct dirent de;
    if ((fd = open(path, 0)) < 0) {
        printf(1, "cannot open %s\n", path);
        return;
    }
    if (fstat(fd, &st) < 0) {
        printf(1, "cannot stat %s\n", path);
        close(fd);
        return;
    }
    switch (st.type) {
        case T_FILE:
            if ((type_flag && type == 'f') || !type_flag) {
                if ((!inum_flag || (inum_flag && ((iFlagSign == '+' && st.ino >= inum) ||
                                                   (iFlagSign == '-' && st.ino <= inum) ||
                                                   (iFlagSign == '=' && st.ino == inum)))) &&
                    strcmp(fmtname(path), filename) == 0) {
                    if (printi_flag) {
                        printf(1, "%d %s\n", st.ino, path);
                    } else {
                        printf(1, "%s\n", path);
                    }
                }
            }
            break;

        case T_DIR:
            if ((type_flag && type == 'd') || !type_flag) {
                if ((!inum_flag || (inum_flag && ((iFlagSign == '+' && st.ino >= inum) ||
                                                   (iFlagSign == '-' && st.ino <= inum) ||
                                                   (iFlagSign == '=' && st.ino == inum)))) &&
                    strcmp(fmtname(path), filename) == 0) {
                   
                    if (printi_flag) {
                        printf(1, "%d %s\n", st.ino, path);
                    } else {
                        printf(1, "%s\n", path);
                    }
                }
            }
            if (strlen(path) + 1 + DIRSIZ + 1 > sizeof(buf)) {
                printf(1, "find: path too long\n");
                break;
            }
            strcpy(buf, path);
            p = buf + strlen(buf);
            *p++ = '/';
            while (read(fd, &de, sizeof(de)) == sizeof(de)) {
                if (de.inum == 0) continue;
                if (strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0) continue;
                memmove(p, de.name, DIRSIZ);
                p[DIRSIZ] = 0;
                find(buf, filename, type_flag, type, inum_flag, inum, iFlagSign, printi_flag);
            }
            break;
    }

    close(fd);
}

int main(int argc,char *argv[]) {
    if(argc<4) {
        printf(1,"please provide complete arguments for find\n");
        exit();
    }
    char *path = argv[1];
    char *filename="";
    int tFlag=0,iFlag=0,piFlag=0;
    char type='\0';
    int iNum = 0;
    int i=2;
    char iFlagSign='=';
    while(i<argc) {
        if(strcmp(argv[i],"-name")==0) {
            if(i+1>=argc) {
                printf(1,"find needs name to search\n");
                exit();
            }
            filename=argv[i+1];
            i=i+2;
        }
        else if(strcmp(argv[i],"-type")==0) {
            if(i+1>=argc) {
                printf(1,"missing type value\n");
                exit();
            }
            if(argv[i+1][0]!='f'&&argv[i+1][0]!='d') {
                printf(1,"it must be either f or d");
                exit();
            }
            tFlag = 1;
            type = argv[i+1][0];
            i=i+2;
        }
        else if(strcmp(argv[i],"-inum")==0) {
            if(i+1>=argc) {
                printf(1,"missing i number\n");
                exit();
            }
            iFlag = 1;
            if(argv[i+1][0]=='+') {
                iFlagSign='+';
                char *temp = argv[i+1] + 1;
                
                iNum = atoi(temp);
            }
            else if(argv[i+1][0]=='-') {
                iFlagSign='-';
                char *temp = argv[i+1] + 1;
                
                iNum = atoi(temp);
            }
            else {
                iNum = atoi(argv[i+1]);
            }
            i+=2;
        }
        else if(strcmp(argv[i],"-printi")==0) {
            piFlag=1;
            i++;
        }
        else {
            printf(1,"unknown flag %s\n",argv[i]);
            exit();
        }
    }
    find(path,filename,tFlag,type,iFlag,iNum,iFlagSign,piFlag);
    exit();
}