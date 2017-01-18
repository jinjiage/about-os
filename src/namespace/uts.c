#define _GNU_SOURCE
#include<sys/types.h>	//CLONE_NEWUTS
#include<stdio.h>	//printf
#include<sched.h>	//clone
#include<unistd.h>	//execv	
#include<sys/wait.h>	//waitpid
#include<signal.h>	//SIGCHLD
#define STACK_SIZE 1024*4
static char process_stack[STACK_SIZE];
const char* process_args[] = {
    "/bin/bash",
    NULL
};
int namespace_process_main(void* args){
	printf("enter namespace_process_main\n");
	sethostname("new namespace", 50);
	execv(process_args[0], (char* const)process_args);
	printf("exit namespace_process_main\n");
	return 1;
}

int main(){
	printf("enter main\n");
	int pid = clone(namespace_process_main, process_stack+STACK_SIZE, CLONE_NEWUTS | SIGCHLD, NULL);
	waitpid(pid, NULL, 0);
	printf("exit main\n");
	return 0;
}
