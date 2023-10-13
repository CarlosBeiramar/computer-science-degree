#include "structs.h"

void instruct_fun(){
    char instructions [5][150] = {
        "______________________INSTRUCTIONS______________________\n",
        "\n",
        "You have incorrectly used the program. Try this:\n",
        "./aurras status\n",
        "./aurras transform  input-filename output-filename filter-id-1 filter-id-2 ...\n"
    };
    write(1,instructions,sizeof(instructions));
}

//creacao do pipe individual
void create_pidPipe(char pid[]){
    if (mkfifo(pid,0666)< 0){
        perror("Cliente Pipe");
        _exit(1);
    }
}

//verifica se os filtros são válidos
int verify_filter(char *filter){
    if (!strcmp(filter, "alto")) return 1;
    if (!strcmp(filter, "baixo")) return 1;
    if (!strcmp(filter, "eco")) return 1;
    if (!strcmp(filter, "rapido")) return 1;
    if (!strcmp(filter, "lento")) return 1;
    return 0;
}

//informa se o filtro estava incorreto
void write_wrong_filter(char *argv){
    char wrong[5][100] = {
        "__________________FILTER DO NOT EXIST__________________\n",
        "\n",
        "The filter "
    };
    write(1, wrong, sizeof(wrong));
    write(1, argv, sizeof(argv));
    write(1, " do not exist.\n", 16);
}


int main(int argc, char *argv[]){
    
    int fifo_fd = open("../tmp/fifo", O_WRONLY);

    if (fifo_fd < 0){
        perror("fifo descripter");
        _exit(1);
    }
    switch (argc)
    {
    case 1:
        // ./aurras 
        instruct_fun();
        break;
    case 2:
        // ./aurras status
        if (!strcmp(argv[1], "status")){
            // pid do cliente
            int pid = getpid();
            //buf para a mensagem
            char message[max_size];
            //guarda o pid na mensagem
            sprintf(message,"%d",pid);
            //concatena "":"
            strcat(message,":");
            //concatena o "status"
            strcat(message,argv[1]);
            message[strlen(message)] = '\0';
            //escreve no fifo
            write(fifo_fd, message,strlen(message));
            close(fifo_fd);

            //create fifo
            char string_pid[20] = {"../tmp/"};
            strcat(string_pid, strtok(message,":"));
            //cria o fifo com o nome do cliente
            create_pidPipe(string_pid);
            //abre o fifo
            int pidPipe_fd = open(string_pid,O_RDONLY);

            if (pidPipe_fd < 0){
                perror("Client: Pid pipe");
                _exit(1);
            }

            char buf[100];
            int bytes_read;
            //lê o que vai ser escrito no fifo
            while ((bytes_read = readln(pidPipe_fd, buf, 100)) > 0){
                write(1, buf, bytes_read);
            }
            close(pidPipe_fd);
        }else{
            instruct_fun();
        }
        break;
    default:
        // ./aurras transform....
        if(!strcmp(argv[1],"transform") && argc > 4){
            int i = 4;
            int pid = getpid();
            char message[max_size];
            sprintf(message,"%d",pid);
            strcat(message,":");
            for (int i = 1; i < argc; i ++){
                strcat(message, argv[i]);
                strcat(message, " ");
            }
            message[strlen(message)] = '\0';
            
            while(argc - i != 0){
                if (!verify_filter(argv[i])){
                    write_wrong_filter(argv[i]);
                    _exit(0);
                }
                i++;
            }
            write(fifo_fd, message,strlen(message));
            close(fifo_fd);
        }else{
            instruct_fun();
        }
        break;
    }
    return 0;
}

// ./aurras transform samples/sample-1-so.m4a output.mp3 alto