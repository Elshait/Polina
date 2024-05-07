#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
//Подключние библиотеки для управления файлами
#include <fcntl.h>
int main  () {
	int fd;
	size_t size;
	char string[]="Group 3.120.2.21\n";
//Открытие файла на заись
	if((fd = open("file.txt",O_WRONLY|O_CREAT, 0666))<0) {
	printf("ошибка при открытии файла на запись\n");
	exit(-1);
	}
	size = write(fd, string, 18);
	if (size !=18){
		printf("Не удалось записать всю строку файла\n");
		exit(-1);
	}
//Закрытие файла
	if(close(fd)<0){
		printf("Не улдалось закрыть файл\n");
		exit(-1);
	}
	return 0;
}





