#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
//Бблиотека управления файлами
int main  () {
	int fd;
	size_t size;
//Инициируем массив символов
	char string[18];
//Открфтие файла на чтение
	if((fd = open("file.txt",O_RDONLY))<0) {
	printf("ошибка при открытии файла на чтение\n");
	exit(-1);
	}
//Чтение информаци из фйла
	size = read(fd, string, 18);
//Проверка количества прочитанных байт
	if (size !=18){
		printf("Не удалось прочетать всю строку файла\n");
		exit(-1);
	}
//Печать строки
	printf("%s", string);
//Закрытие файла
	if(close(fd)<0){
		printf("Не улдалось закрыть файл\n");
		exit(-1);
	}
	return 0;
}





