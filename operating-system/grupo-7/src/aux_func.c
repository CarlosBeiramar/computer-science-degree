#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

ssize_t readln(int fd, char *line, size_t size){
    //não podemos usar o line porque o apontador está sempre a apontar para o inicio do array
    int next_pos = 0;
    int read_bytes = 0;

    while((read(fd, line + next_pos, 1) > 0) && next_pos < size){  // line + next_post != line[next_post]
        read_bytes ++; //para ler o '\n'
        if (line[next_pos] == '\n'){                             //line + next_post avança com o apontador
            break;                                               // line[next_post] dá me o valor que está nessa posição que será um char e nao um apontador
        }                        
        next_pos ++;                                             
    }
    return read_bytes;
}