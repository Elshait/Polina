//подключение библеотек
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
//главная функция программы с аргументом 
int main(int argc, char *argv[], char *envp[]) {
	int result1;
	//Объявление переменных
	pid_t procid, parentid;//Индификаторы процессов
	pid_t result;//Результат системного вызова fork()
	int a = 0;// Переменна для проверки работы процессора-родителя и процессе-ребенка
	result = fork();
	if (result < 0){
		printf("Щшибка при выполнении fork()\n");
		exit (-1);
	}
	else if (result ==0){
		a=a+1;
		procid =getppid();//Получение идентификаторатекущего процесса
		parentid = getppid();//Полцяение идентификатора родительского процесса
		printf("Ид. процесса: %d, ид. родителя: %d, значение переменной a: %d\n", procid, parentid, a);
		 result1 = execle("/bin/cat", "/bin/cat", "otchetPT.txt", 0, envp);
       		 //принтф выполняется тольо в случае ошибки вызова эксесл
       		 printf("Ошибка при выполнении системного execle()\n");
       		 exit(-1);

	}
	else {
		a = a +555;
		procid =getppid();//Получение идентификаторатекущего процесса
        	parentid = getppid();//Полцяение идентификатора родительского процесса
        	printf("Ид. процесса: %d, ид. родителя: %d, значение переменной a: %d\n", procid, parentid, a);
	}

	return 0; //никогда не выполняется
}
