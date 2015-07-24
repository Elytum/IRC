#include <chained_string.h>
#include <stdio.h>

// void	contains(t_chained_string chained, char *str)
// {
// 	printf("Subject:\n");
// 	put_chained_string(chained);
// 	if (chained_string_contains(chained, str))
// 		printf("It does contain [%s]\n", str);
// 	else
// 		printf("It does not contain [%s]\n", str);
// }

void	cross(t_chained_string c1, t_chained_string c2)
{
	printf("\n   --------------   \n\t\tSubject 1:\n");
	put_chained_string(c1);
	printf("   --------------   \n\t\tSubject 2:\n");
	put_chained_string(c2);
	if (chained_string_cross(c1, c2))
		printf("\nIt does cross\n\n");
	else
		printf("\nIt does not cross\n\n");
}

void	test(void)
{
	t_chained_string	c1;
	t_chained_string	c2;

	init_chained_string(&c1);
	init_chained_string(&c2);
	cross(c1, c2);
	free_chained_string(&c1);
	free_chained_string(&c2);
	put_chained_string(c1);
}

int	main(void)
{
	test();
	return (0);
}