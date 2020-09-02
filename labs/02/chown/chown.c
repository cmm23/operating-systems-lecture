#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <errno.h>
#include <sys/stat.h>
#include <pwd.h>

int main (int argc, char const *argv[]){

	uid_t uid = -1;
	struct passwd *pwd;
	long num = -1;
	
	pwd = getpwnam(argv[2]);
	
	if (pwd == NULL){
		fprintf(stderr, "An error occurred: user cannot be found \n");
	}
	
	uid = pwd -> pw_uid;
	
	num =  chown(argv[1], uid, -1);
	
	if (num < 0){
		fprintf(stderr, "An error occurred \n");
		exit(0);
	}
	
	return 0;

}
