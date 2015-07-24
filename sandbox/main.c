#include <chained_string.h>
#include <stdio.h>

void	contains(t_chained_string chained, char *str)
{
	printf("Subject:\n");
	put_chained_string(chained);
	if (chained_string_contains(chained, str))
		printf("It does contain [%s]\n", str);
	else
		printf("It does not contain [%s]\n", str);
}

void	test(void)
{
	t_chained_string	chained;
	char *str;

	init_chained_string(&chained);
	push_stack_chained_string(&chained, "?");
	contains(chained, "Ca");
	push_hype_chained_string(&chained, "Va");
	contains(chained, "Ca");
	push_hype_chained_string(&chained, "Ca");
	contains(chained, "Ca");
	push_hype_chained_string(&chained, "Comment");
	contains(chained, "Comment");
	push_stack_chained_string(&chained, "Bonjour");
	contains(chained, NULL);
	put_chained_string(chained);
	free_chained_string(&chained);
	put_chained_string(chained);
}

int	main(void)
{
	test();
	return (0);
}