#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
int main (){
	uid_t userid;
	gid_t groupid;
	userid = getuid();
	groupid = getgid();
	printf("Ид. пользователя: %d\n", userid);
	printf("Ид. группы пользователя: %d\n", groupid);
	return 0;
}
