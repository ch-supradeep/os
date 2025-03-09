#include "stat.h"
#include "types.h"
#include "user.h"
#include "fcntl.h"
#include <stddef.h>


#define MAX_LINE 1024

void write_to_file(char *path) {
    int fd = open(path, O_CREATE | O_WRONLY);
    if (fd < 0) {
        printf(1, "Error opening file.\n");
        exit();
    }
    char *str;
    str = "I understand Operating system.";
    write(fd, str, strlen(str));
    write(fd, "\n", 1);  
    str = "I understand Operating system.";
    write(fd, str, strlen(str));
    write(fd, "\n", 1); 
    str = "I understand Operating system.";
    write(fd, str, strlen(str));
    write(fd, "\n", 1); 
    str = "I LOVE TO WORK ON OS.";
    write(fd, str, strlen(str));
    write(fd, "\n", 1); 
    // str = "I Love to work on OS.";
    // write(fd, str, strlen(str));
    // write(fd, "\n", 1); 
    // str = "Abcd";
    // write(fd, str, strlen(str));
    // write(fd, "\n", 1); 
    // str = "1234";
    // write(fd, str, strlen(str));
    // write(fd, "\n", 1); 
    // close(fd);
}

void print_line(const char* line, int count, int showCount) {
    if (showCount) {
        printf(1, "%d ", count);
    }
    printf(1, "%s\n", line);
}

int compare_ignore_case(const char *s1, const char *s2) {
    while (*s1 && *s2) {
        char c1 = (*s1 >= 'A' && *s1 <= 'Z') ? (*s1 ^ 32) : *s1;
        char c2 = (*s2 >= 'A' && *s2 <= 'Z') ? (*s2 ^ 32) : *s2;
        if (c1 != c2) {
            return 0;
        }
        s1++;
        s2++;
    }
    return (*s1 == '\0' && *s2 == '\0');
}

void process_file(char *path, int cFlag, int iFlag, int dFlag) {
    int file_descriptor;
    if (path == NULL) {
        file_descriptor = 0;  
    } else {
        file_descriptor = open(path, O_RDONLY);
        if (file_descriptor < 0) {
            printf(1, "uniq: cannot open %s\n", path);
            exit();
        }
    }
    char current_line[MAX_LINE];
    char prev_line[MAX_LINE] = "";
    int count = 1;
    int index = 0;
    char ch;
    int print = 0;
    while (read(file_descriptor, &ch, 1) == 1) {
        if (ch != '\n') {
            current_line[index++] = ch;
            continue;
        }
        current_line[index] = '\0';
        index = 0;
        if (prev_line[0] == '\0') {
            strcpy(prev_line, current_line);
            continue;
        }
        int is_duplicate = iFlag ? compare_ignore_case(prev_line, current_line) :(strcmp(prev_line, current_line) == 0);
        if (is_duplicate) {
            count++;
        } else {
            print = 1;
            if (dFlag && count == 1) {
                print = 0; 
            }
            if (print) {
                print_line(prev_line, count, cFlag);
            }
            strcpy(prev_line, current_line);
            count = 1;
        }
    }
    if (prev_line[0] != '\0') {
        print = 1;
        
        if (dFlag && count == 1) {
            print = 0;
        }

        if (print) {
            print_line(prev_line, count, cFlag);
        }
    }

    if (file_descriptor != 0) {
        close(file_descriptor);
    }
}

int main(int argc, char *argv[]) {
    int cFlag = 0, iFlag = 0, dFlag = 0;
    char *path = NULL;
    if (argc < 2) {
        path = NULL;
    }
    int i = 1;
    
    while (i < argc) {
        if (argv[i][0] == '-') {  
            int j = 1;
            while (argv[i][j] != '\0') {
                if (argv[i][j] == 'c') {
                    cFlag = 1;
                } else if (argv[i][j] == 'd') {
                    dFlag = 1;
                } else if (argv[i][j] == 'i') {
                    iFlag = 1;
                } else {
                    printf(1, "Invalid flag: -%c. Use -c, -d, or -i\n", argv[i][j]);
                    exit();
                }
                j++;
            }
        } else {  
            path = argv[i];
        }
        i++;  
    }
    //write_to_file(path);
    process_file(path, cFlag, iFlag, dFlag);
    exit();
}