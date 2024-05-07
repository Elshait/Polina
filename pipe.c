#include<sys/types.h> 
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
int main(){
	int fd1[2], fd2[2];
	pid_t result;
	size_t size;
	char string1[] = "Hello, child!", string2[] = "Hello, parent!";
	char resstring1[13], resstring2[14];
	//Попытка создать пайп
	if (pipe(fd1)<0) {
		//если пайп не удалось вывести печатаем спредупреждающее сообщение
		printf("Не получиолось создать pipe()");
		exit(-1);
	}
	if (pipe(fd2)<0) {
                //если пайп не удалось вывести печатаем спредупреждающее сообщение
                printf("Не получиолось создать pipe()");
                exit(-1);
	}
	result = fork();
	if (result<0){
		printf("Ошибка выполнения fork()\n");
		exit(-1);
	}
	else if (result>0){
		if (close(fd1[0])<0){
			printf("Ошибка при закрытии пайп на чтение\n");
			exit(-1);
		}
                if (close(fd2[1])<0){
                        printf("Ошибка при закрытии пайп на чтение\n");
                        exit(-1);
                }
//Запишем в пайп 14 байт
		size = write(fd1[1], string1,13);
		if(size !=13){
			printf("Can\'t write all string\n");
			exit(-1);
		}
		printf("Процесс родитель записал информацию в pipe\n");
		size = read(fd2[0],resstring2,14);
                if(size != 14){
                        printf("Can\'t read string\n");
                        exit(-1);
		}
		printf("Информация от дочернего процесса: ", resstring2);
		for(int i=0; i<14; i++) printf("%c", resstring2[i]);
		printf("\n");
		if (close(fd1[1])<0){
			printf("Не получилось закрыть исходящий поток\n");
			exit(-1);
		}
		if (close(fd2[0])<0){
                        printf("Не получилось закрыть исходящий поток\n");
                        exit(-1);
		}

	}
	else {
		if (close(fd1[1])<0){
                	printf("Не получилось закрыть исходящий поток\n");
                	exit(-1);
		}
		if (close(fd2[0])<0){ 
                        printf("Не получилось закрыть входящий поток\n");
                        exit(-1);
                }

//Если запись прошла и количество байт меньше, пишем сообщение
		size = read(fd1[0],resstring1,13);
		if(size !=13){
			printf("Can\'t read string\n");
			exit(-1);
		}
//Закрытие пайп для записи
		printf("Информация от родителя: ");
                for(int i=0; i<13; i++) printf("%c", resstring1[i]);
                printf("\n");
		size = write(fd2[1], string2, 14);
                if(size !=14){
                        printf("Can\'t write all string\n");
                        exit(-1);
                }
                printf("Процесс ребенок  записал информацию в пайп\n");
		if(close(fd1[0])<0){
			printf("Can\'t close output stream\n");
			exit(-1);
		}
		if(close(fd2[1])<0){
                        printf("Can\'t close output stream\n");
                        exit(-1);
               	}
	}
	return 0;
}

