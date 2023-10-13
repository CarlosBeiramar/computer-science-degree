#include "structs.h"

//global variable for number of clients
int client_counter = 0;
//global variable for number of filters
int filter_counter = 0;
//global variable for number of tasks
int task_counter = 0;


void create_fifo(){
    if (mkfifo("../tmp/fifo", 0666) < 0){
        perror("fifo");
        _exit(1);
    }
}

int store_clients(Client **cl_array, char *buf){
    // cl_array -> apontador de apontadores
    //cria um array temporário exatamente igual ao bug
    char * tmp = calloc(sizeof(buf) + 1, sizeof(char)); 
    strcpy(tmp,buf);
    // array temporário 
    Client* new_client_array = realloc(*cl_array, sizeof(Client) * (client_counter + 1));
    //verifica se foi bem criado
    if (!new_client_array) return 0;
    //põe o array do argumento a apontar para o temporario
    *cl_array = new_client_array;
    //cria o cliente
    Client c;
    //guarda o pid
    c.pid = strdup (strtok (tmp, ":"));
    //guarda a mensagem
    c.message = strdup (strtok (NULL, "\0"));
    //guarda no temporário o cliente criado
    new_client_array[client_counter++] = c;

    return 1;
}

int store_filters(Filter ** flt_array, char *config){

    //array para o path
    char path[100]={"../"};

    //concatena o path com o array
    strcat(path,config);

    //descritor para o ficheiro config
    int file_fd = open(path, O_RDONLY);

    // verifica se foi bem aberto
    if (file_fd < 0){
        perror("Filter descripter");
        _exit(0);
    }

    int bytes_read = 0;
    char buf[1024];

    // ciclo para ler o ficheiro
    while ((bytes_read = readln(file_fd,buf,1024)) > 0){
        buf[bytes_read] = '\0';
        //array temporário para os filtros
        Filter *tmp = realloc(*flt_array, sizeof(Filter) * (filter_counter + 1));
        //verifica se o array foi criado
        if (!tmp) return 0;
        //coloca o array da main a apontar para o temporário
        (*flt_array) = tmp;
        //filter f
        Filter f;
        //copiar do buf e duplicar o apontador
        f.name = strdup(strtok(buf, " "));
        f.name[strlen(f.name)] = '\0';
        //copiar do buf e duplicar o apontador
        f.exec = strdup(strtok(NULL," "));
        f.exec[strlen(f.exec)] = '\0';
        //copiar do buf e duplicar o apontador
        f.max = atoi(strtok(NULL,"\0"));
        //quando se cria não ha nenhum processo a correr
        f.running = 0;
        //guarda-se no temporário e incrementa-se o filter_counter
        tmp[filter_counter++] = f;
    }
    //fechar o descritor
    close(file_fd);
    return 1;
}

int store_task(Task **tsk_array, char *transf){

    int counter = 0;

    char *tmp_transf = calloc(strlen(transf) + 1, sizeof(char));
    strcpy(tmp_transf, transf);
    
    Task *tmp = realloc(*tsk_array, sizeof(Task) * (task_counter + 1));

    if (!tmp) return 0;

    (*tsk_array) = tmp;

    Task t;
    
    t.client_pid = strdup(strtok(transf, ":"));
    
    strtok(NULL, " ");
    
    t.input = strdup(strtok(NULL, " "));
    
    t.output = strdup(strtok(NULL, " "));

    t.filters = strdup(strtok(NULL, "\0"));

    for (int i = 0; t.filters[i] != '\0';i++){
            if (t.filters[i] == ' ' && t.filters[i+1] != ' ')
                counter++;    
        }

    t.n_filters = counter;

    tmp[task_counter++] = t;

    free(tmp_transf);
    return 1;
}

// para remover o elemento preciso de saber em que posição do array é q ele está.
int remove_elem(Client ** cl_array, int index){
    //criar um array temporario
    Client *tmp = malloc(sizeof(Client) * (index));
    //verifica se foi bem criado
    if (!tmp) return 0;
    // verifica se o indice do elemento nao é 0
    if (index != 0){
        //copia do inicio do array até à posição a remover
        memmove(tmp, (*cl_array), sizeof(Client) * (index));
        //copia desde a posição a remover até ao final do array
        memmove(tmp + index, (*cl_array) + index + 1, sizeof(Client) * (client_counter - (index + 1)));
    }
    //decrementa o número de clientes;
    client_counter--;
    //aponta o array para o temporario
    (*cl_array) = tmp;
    
    return 1;
}

void write_message(int pid_pipe, Filter *filter_array, Task *task_array ,int pid){
    char buf_filter[8] = "filter ";
    char runMax[5];
    char pidMessage[15];
    int length = 0;
    char buf_task[20] = "task #";
    if (task_counter > 0 ){
        for (int i = 0; i < task_counter; i++){
            char aux[5];
            sprintf(aux , "%d", i+1);
            strcat(aux, ":");
            strcat(buf_task,aux);

            write(pid_pipe, buf_task, strlen(buf_task));

            write(pid_pipe, " transform", 10);

            write(pid_pipe, " ", 1);

            write(pid_pipe, task_array[i].input, strlen(task_array[i].input));

            write(pid_pipe, " ", 1);

            write(pid_pipe, task_array[i].output, strlen(task_array[i].output));

            write(pid_pipe, " ", 1);

            write(pid_pipe, task_array[i].filters, strlen(task_array[i].filters));

            write(pid_pipe, "\n", 1 );
        }

    }else{
        write(pid_pipe, "No running tasks\n", 17);
    }

    for (int i = 0; i < filter_counter; i++){

        //escreve no fifo a palavra "filter"
        write(pid_pipe, buf_filter,strlen(buf_filter));
        //escreve no fifo o nome do filtro
        write(pid_pipe,filter_array[i].name,strlen(filter_array[i].name));
        //escreve ": "
        write(pid_pipe, ": ", 2);

        //adiciona ao array runMax -> running/max
        length = sprintf(runMax, "%d", filter_array[i].running);
        strcat(runMax,"/"); length++;
        sprintf(runMax + length,"%d",filter_array[i].max);
        //escreve no pipe pid o array runMax
        write(pid_pipe,runMax,strlen(runMax));
        //escreve (running/max) no pipe
        write(pid_pipe," (running/max)",15);
        write(pid_pipe, "\n", 1);
    }
    //concatena "pid:"
    strcat(pidMessage,"pid:");
    //insere um espaço
    strcat(pidMessage, " ");
    //insere o pid
    sprintf(pidMessage + strlen(pidMessage), "%d", pid);
    //escreve no fifo
    write(pid_pipe,pidMessage,strlen(pidMessage));
    //insere \n
    write(pid_pipe, "\n", 1);
}

int check_task(char* buf){

    char *tmp = calloc(strlen(buf) + 1, sizeof(char));
    strcpy(tmp,buf);

    strtok(tmp,":");

    if (!strcmp("transform", strtok(NULL," "))){
        return 1;
    }
    return 0;
}

void deal_request(Client *client_array, Filter *filter_array, Task *task_array ,int pid){
    int index = 0, j = 0;
    char result[30];
     
    for (int i = 0; i < client_counter; i++){
        //verifica se o pedido é status
        if (strcmp(client_array[i].message,"status") == 0){
            
            if (fork() == 0){
                //processo - filho
                char path_pipe[20] = {"../tmp/"};
                strcat(path_pipe,client_array[i].pid);
                //abre o pipe do processo
                int pid_pipe = open(path_pipe,O_WRONLY);
                //verifica o descritor
                if (pid_pipe < 0){
                    perror("Server: Pid pipe");
                    _exit(1);
                }
                //escreve a mensagem para o cliente através do seu pipe
                write_message(pid_pipe,filter_array, task_array,pid);
                close(pid_pipe);
                _exit(0);
            }
        }       
    }

    for(int i = 0; i < task_counter; i++){
        //array de string strings
        char *filters[task_array[i].n_filters];
        char *store[task_array[i].n_filters];
        char exec[50] = "aurrasd-filters/";
        int d = 0;
        char aux[50] = "../";

        int status;

        strcat(aux,task_array[i].input);

        //percorrer a string dos filtros  "alto eco rapido"
        while (index < strlen(task_array[i].filters)){ 
            //verificar se é espaco
            if (isspace(task_array[i].filters[index])){ 
                result[j] = '\0';
                
                //coloca o path do executável do filtro
                for(int x = 0; x < filter_counter; x++){
                    if (!strcmp(result,filter_array[x].name)){
                        //concatena o executável do filtro
                        filter_array[x].running++;
                        memset(exec + 16, '\0', sizeof(filter_array[x].name));
                        strcat(exec,filter_array[x].exec);
                        store[d] = strdup(result);
                        filters[d++] = strdup(exec);
                    }
                }
               //voltar à posição 0 do result
                index++;
                j = 0;
            }else{
                result[j++] = task_array[i].filters[index++];
            }
        }

        //descritor para o ficheiro input
        int fd_input = open(aux, O_RDONLY);
        //descritor para o ficheiro output
        int fd_output = open(task_array[i].output, O_WRONLY | O_CREAT | O_TRUNC , 0777);
        
        int fd[2];
        int fd1[2];

        int n_pipes = task_array[i].n_filters - 1;  // alto | eco | rapido
        
        if (n_pipes == 0){
            // alto 
            if (fork() == 0){
                dup2(fd_input, 0);
                close(fd_input);
                dup2(fd_output,1);
                close(fd_output);
                if (execl(filters[0],filters[0],NULL) == -1) perror("exec error_0");
            }else{
                wait(&status);
            }
        } else if(n_pipes == 1){
            // alto | eco
            pipe(fd);

            if (fork() == 0){
                sleep(5);
                dup2(fd_input,0);
                dup2(fd[1],1);
                close(fd[0]);
                close(fd[1]);
                if (execl(filters[0],filters[0],NULL) == -1) perror("exec error_1");
                _exit(1);
            }
            else{
                if (fork() == 0){
                    dup2(fd[0],0);
                    dup2(fd_output,1);
                    close(fd[0]);
                    close(fd[1]);
                    if (execl(filters[1],filters[1],NULL) == -1) perror("exec error_2");
                }else{
                    close(fd_input);
                    close(fd_output);
                    close(fd[0]);
                    close(fd[1]);
                    wait(&status);
                }
            }
        }else if(n_pipes == 2){
            // alto | eco | rapido
            pipe(fd);
            if (fork() == 0){
                dup2(fd_input,0);
                dup2(fd[1],1);
                close(fd[0]);
                close(fd[1]);
                if (execl(filters[0],filters[0],NULL) == -1) perror("exec error_1");
                _exit(1);
            }
            else{ 
                pipe(fd1);
                if (fork() == 0){
                    close(fd[1]);
                    dup2(fd[0],0);
                    close(fd[0]);

                    close(fd1[0]);
                    dup2(fd1[1],1);
                    close(fd1[1]);
                    if (execl(filters[1],filters[1],NULL) == -1) perror("exec error_2");
                    _exit(1);  
                }
                else{
                    if (fork() == 0){
                        close(fd[0]);
                        close(fd[1]);
                        dup2(fd1[0],0);
                        dup2(fd_output,1);
                        close(fd1[0]);
                        close(fd1[1]);
                        if (execl(filters[2],filters[2],NULL) == -1) perror("exec error_3");
                    }else{
                        close(fd_input);
                        close(fd_output);
                        close(fd[0]);
                        close(fd[1]);
                        close(fd1[0]);
                        close(fd1[1]);
                        wait(&status);
                    }
                }
            }
        }
        for (int j = 0; j < task_array[i].n_filters; j++){
            for (int x = 0; x < filter_counter; x++){
                if (!strcmp(store[j], filter_array[x].name)){
                    filter_array[x].running--;
                }
            }
        }
    }
}


int main (int argc, char *argv[]){
    //verifica o número de argumentos
    if (argc != 3){
        perror("Not enough arguments\n");
        _exit(0);
    }

    //array for clients
    Client *client_array = NULL;

    //array for filters
    Filter *filter_array = NULL;

    //array for tasks
    Task *task_array = NULL;

    //guarda os filtros e verifica se nao deu erro
    if (!store_filters(&filter_array, argv[1])){
        perror("Filter descripter");
        _exit(0);
    }
    //pid do servidor
    int pid = getpid();
    //cria o fifo
    create_fifo();
    int fifo_fd = open("../tmp/fifo", O_RDONLY);
    //verifica o descritor
    if (fifo_fd < 0){
        perror("fifo descripter");
        _exit(0);
    }

    //buf para a mensagem
    char buf[max_size];
    int bytes_read;
    
    while (1){

        if ((bytes_read = readln(fifo_fd,buf,max_size)) > 0 ){
            buf[bytes_read] = '\0';

            write(1,buf,bytes_read);
            write(1,"\n",1);
            //guarda o cliente 
            if (!store_clients(&client_array, buf)){
                perror("malloc: client");
            }
            
            //guardar a task
            if (check_task(buf)){
                if (!store_task(&task_array, buf)){
                    perror("malloc: task");
                };
            }
            //lidar com o pedido do cliente
            deal_request(client_array, filter_array, task_array ,pid); 
        }
    }
    close(fifo_fd);
    return 0;
}

// ./aurrasd etc/aurrasd.conf bin/aurras-filters