#include <chained_string.h>
#include <stdio.h>

void	test(void)
{
	t_chained_string	chained;
	char *str;

	init_chained_string(&chained);
	push_stack_chained_string(&chained, "?");
	push_hype_chained_string(&chained, "Va");
	push_hype_chained_string(&chained, "Ca");
	push_hype_chained_string(&chained, "Comment");
	push_stack_chained_string(&chained, "Bonjour");
	str = foreach_chained_string(&chained);
	str = foreach_chained_string(&chained);
	str = foreach_chained_string(&chained);
	str = foreach_chained_string(&chained);
	printf("Testing [%s]\n", str);
	put_chained_string(chained);

	while ((str = foreach_chained_string(&chained)) != NULL)
		printf("Found [%s]\n", str);
	while ((str = foreach_chained_string(&chained)) != NULL)
		printf("Found [%s]\n", str);
	while ((str = foreach_chained_string(&chained)) != NULL)
		printf("Found [%s]\n", str);
	while ((str = foreach_chained_string(&chained)) != NULL)
		printf("Found [%s]\n", str);

	free_chained_string(&chained);
	put_chained_string(chained);
}

int	main(void)
{
	test();
	return (0);
}