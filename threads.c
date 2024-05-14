#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
int a = 0;// инициализация глобальной статичнеской переменной доступной из каждого thread а
//функция выполняющаяся в рамках второго thread   
void *mythread(void *dummy){
	pthread_t mythid; //идентификатор threadа- для каждого имеет своё значение 
	mythid = pthread_self(); 
	a = a+1;
	printf("Thread %ld, Результат вычисления a= %d\n",mythid, a); // печать идентификатора текущего threadа и результата и значения  глобальной переменной
	return NULL;

}

int main () {
	pthread_t thid, mythid;
	int result;
	result = pthread_create(&thid, (pthread_attr_t *)NULL , mythread, NULL); // создание нового threadа при помощи вызова фугкции mythread
	if (result != 0){
		printf("Ошибка при создании нового thread\'a , возвращенное значение =%d\n",result);
		exit(-1);
	}
	printf("Thread создан , thid = %ld\n,", thid);
	mythid = pthread_self(); // сохраняем в переменной mythid идентификатор главного threadа
	a = a+1;
	printf("Thread %ld, Результат вычисления a= %d\n", mythid, a);
	pthread_join(thid, (void **)NULL); //ожидание завершения порожденного threada
	return 0;
}
