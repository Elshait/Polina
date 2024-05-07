#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

int main(){
	int *array;
	int shmid;
	int new = 1;
	char pathname[] = "forftok.ipc";
	key_t key;
	if ((key = ftok(pathname, 0)) < 0) {
		printf("не удалось сгенерировать ипс ключ\n");
		exit(-1);
	}
	if ((shmid = shmget(key, 3*sizeof(int), 0666|IPC_CREAT|IPC_EXCL)) < 0) {
		if (errno != EEXIST) {
			printf("не удалось создать область разделяемой памяти\n");
			exit(-1);
		}
		else {
			if ((shmid = shmget(key, 3*sizeof(int), 0)) < 0) {
				printf("не удалось найти область разделяемой памяти\n");
				exit(-1);
			}
			new = 0;

		}

	}
	if((array= (int *)shmat(shmid, NULL, 0)) ==(int *)(-1)){
		printf("не удалось добавить разделяемую память в адресное пространство процесса\n");
		exit(-1);
	}
	if(new) {
		array[0] = 1;
		array[1] = 0;
		array[2] = 1;
	}
	else {
		array[0] += 1;
		array[2] += 1;
	}
	printf("Программа 1 была запущена %d раз(a), программа 2 - %d рвз(a), всего - %d\n", array[0], array[1], array[2]);
	if(shmdt(array)<0){
		printf("Не удается исключить раздилимю память из адресного прострнства процесса\n");
		exit(-1);
	}
	return 0;
}
