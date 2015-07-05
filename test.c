#define BUF_SIZE 40960
#include <stdio.h>
#include <unistd.h>

int main(void)
{
	char buffer[BUF_SIZE];

	fgets(buffer, BUF_SIZE - 1, stdin);
	write(1, buffer, BUF_SIZE);
	write(1, "\n", 1);
	return (0);
}