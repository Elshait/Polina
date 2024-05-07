#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
	int fd;
	size_t size;
	//Символьный массив где будет храниться имя файла ФИФО
	char name[] = "fifo1.fifo";
	//Процесс  комментирования. процесс создания фифо
/* 	if (mknod(name, S_IFIFO | 0666, 0) < 0){
		printf("не удалось создать файл Fifo\n");
		exit(-1);
	}
	//ПРОЦЕСС РОДИТЕЛЬ ПИШЕТ ИНФОРМАЦИЮ ФИФО
*/
		if((fd = open(name, O_WRONLY)) < 0) {
			printf("Не удалось открыть файл на запись\n");
			exit(-1);
		}
		size = write(fd, "Hello, all!", 11);
		if (size !=11) {
			printf("Не получилось записать 11  байт в FIFO\n");
			exit(-1);
		}
		if (close(fd)<0) { 
			printf("Не получилось закрыть FIFO\n");
			exit(-1);
		}
		printf("Процесс записал информацию в FIFO и завершил работу\n");

		return 0;
}
