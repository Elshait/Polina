#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

int main(){
	int *array; // указатель на массив расположенный в разделённой памяти
	int shmid;//идентификатор области разделимой памяти
	int new = 1;//признак необходимости создания нового массива
	char pathname[] = "forftok.ipc";//файл необходимый для необходимости генеразции ключа ипс
	key_t key; //переменная для хранения ключа ипс
	//попытка генеразации ключа
	if ((key = ftok(pathname, 0)) < 0) {
		printf("не удалось сгенерировать ипс ключ\n");
		exit(-1);
	} 
	//попытка создания создания области разделенной памяти
	if ((shmid = shmget(key, 3*sizeof(int), 0666|IPC_CREAT|IPC_EXCL)) < 0) {
		//проверяет что ошибка при создании области разделяемой памяти не связана с тем что область уже существует
		if (errno != EEXIST) {
			printf("не удалось создать область разделяемой памяти\n");
			exit(-1);
		}
		//получение идентификатора области разделенной памяти если область уже существует
		else {
			if ((shmid = shmget(key, 3*sizeof(int), 0)) < 0) {
				printf("не удалось найти область разделяемой памяти\n");
				exit(-1);
			}
			new = 0;// установка признака уже сущетсмвуещей области разделяемой памяти

		}

	}
	//включение разделяемой памяти в адресное пространство текущего процесса
	if((array= (int *)shmat(shmid, NULL, 0)) ==(int *)(-1)){
		printf("не удалось добавить разделяемую память в адресное пространство процесса\n");
		exit(-1);
	}
	//операции над вновь созданным массивом 
	if(new) {
		array[0] = 1;
		array[1] = 0;
		array[2] = 1;
	}
	//операции над уже существующим массивом
	else {
		array[0] += 1;
		array[2] += 1;
	}
	printf("Программа 1 была запущена %d раз(a), программа 2 - %d рвз(a), всего - %d\n", array[0], array[1], array[2]);
	//исключение области разделяемой памяти из адресного пространтсва текщего процесса
	if(shmdt(array)<0){
		printf("Не удается исключить раздилимю память из адресного прострнства процесса\n");
		exit(-1);
	}
	return 0;
}
