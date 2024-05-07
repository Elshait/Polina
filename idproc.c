#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
//Главная функция программа
int main() {
//Объявление переменных
        pid_t process;
        pid_t parents;
//Системный вызов
        process = getpid();

        printf("Ид. текущего процесса: %d\n", process);
        printf("Ид. процесса родителя: %d\n", parents);
//Возврат значения
        return 0;

}

