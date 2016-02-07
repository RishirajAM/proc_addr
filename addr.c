#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define INSMOD_ARGV "insmod proc_addr.ko pid_mem=%d"

int var_data = 100;
int var_bss;

void function1(void)
{
	int var_f1_local = 2000;
	printf("address of var_f1_local = %p, \n", &var_f1_local);
}

int main(void)
{
	int var_local = 1000;
	char argv[35] = {0};

	printf("***Process : pid \t= %d***\n", getpid());
	printf("Application Space->\n");
	printf("address of var_data \t= %p,\n", &var_data);
	printf("addrees of var_bss \t= %p, \n", &var_bss);
	printf("address of var_local \t= %p, \n", &var_local);
	function1();

	printf("Kernel Space->\n");
	system("dmesg -C");
	sprintf(argv, INSMOD_ARGV, getpid());
	system(argv);
	sleep(1);
	system("dmesg");
	system("rmmod proc_addr.ko");
	system("dmesg -C");
	return 0;
}
