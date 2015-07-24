#include <libft.h>
#include <chained_string.h>
#include <stdio.h>

t_list_string				*stack_list_string(char *str)
{
	t_list_string			*created;

	if (!(created = (t_list_string *)malloc(sizeof(t_list_string))))
		return (NULL);
	created->string = str;
	created->flag = NOT_ALLOCATED;
	created->next = NULL;
	return (created);

}

t_list_string				*hype_list_string(char *str)
{
	t_list_string			*created;

	if (!(created = (t_list_string *)malloc(sizeof(t_list_string))))
		return (NULL);
	created->string = ft_strdup(str);
	created->flag = ALLOCATED;
	created->next = NULL;
	return (created);
}

void						free_list_string(t_list_string *list)
{
	t_list_string			*ptr;
	t_list_string			*next;

	ptr = list;
	while (ptr)
	{
		next = ptr->next;
		if (ON_HYPE(ptr->flag))
			free(ptr->string);
		free(ptr);
		ptr = next;
	}
}

void						free_chained_string(t_chained_string *ptr)
{
	free_list_string(ptr->list);
	ptr->list = NULL;
	ptr->ptr = NULL;
	ptr->pos = 0;
	ptr->size = 0;
}

void						push_stack_chained_string(t_chained_string *ptr, char *str)
{
	t_list_string			*new_one;

	new_one = stack_list_string(str);
	new_one->next = ptr->list;
	ptr->list = new_one;
	ptr->size++;
}

void						push_hype_chained_string(t_chained_string *ptr, char *str)
{
	t_list_string			*new_one;

	new_one = hype_list_string(str);
	new_one->next = ptr->list;
	ptr->list = new_one;
	ptr->size++;
}

char						*foreach_chained_string(t_chained_string *chained)
{
	char					*ret;

	if (chained->pos == chained->size)
	{
		chained->pos = 0;
		chained->ptr = NULL;
		return (NULL);
	}
	if (!chained->ptr)
	{
		chained->ptr = chained->list->next;
		chained->pos = 1;
		return (chained->list->string);
	}
	ret = chained->ptr->string;
	chained->ptr = chained->ptr->next;
	chained->pos++;
	return (ret);
}

void						put_chained_string(t_chained_string chained)
{
	t_list_string			*ptr;

	if (!chained.list)
	{
		printf("Contained nothing: Empty chained string\n");
		return ;
	}
	ptr = chained.list;
	printf("Size = %i, pos = %i, contains: { ", chained.size, chained.pos);
	while (ptr)
	{
		if (ptr->next)
			printf("\"%s\", ", ptr->string);
		else
			printf("\"%s\" }\n", ptr->string);
		ptr = ptr->next;
	}
}

int							chained_string_contains(t_chained_string chained, char *str)
{
	t_list_string			*ptr;

	if (!chained.list || !str)
		return (0);
	ptr = chained.list;
	while (ptr)
	{
		if (!strcmp(ptr->string, str))
			return (1);
		ptr = ptr->next;
	}
	return (0);
}

void						init_chained_string(t_chained_string *chained)
{
	chained->list = NULL;
	chained->ptr = NULL;
	chained->pos = 0;
	chained->size = 0;
}