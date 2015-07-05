#include <inputs.h>
#include <stdio.h>

int main(void)
{
	char *str;

	while ((str = ft_get_inputs("Test > ")))
	{
		printf("Str = %s\n", str);
		free(str);
	}
	free(str);
}
