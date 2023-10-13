#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <ctype.h>
#include "aux_func.c"
#define max_size 1024

ssize_t readln(int fd, char *line, size_t size);

//struct to define a client
typedef struct client{
    char *pid;
    char *message;
}Client;


// struct to define a filter
typedef struct filter{
    char *name;
    char *exec;
    int max;
    int running;
}Filter;

//struct to define tasks
typedef struct task{
    char *input;
    char *output;
    char *filters; 
    char *client_pid;
    int n_filters;
}Task;






