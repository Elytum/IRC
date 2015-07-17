#include <libft.h>

enum status
{
	ALLOCATED = 0,
	NOT_ALLOCATED = -1
};

#define ON_HYPE(status flag) (flag == ALLOCATED)

typedef struct				s_list_string
{
	char					*string;
	status					flag;				
	struct s_list_string	*next;
}							t_list_string;


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

typedef struct				s_chained_string
{
	t_list_string			*list;
	t_list_string			*ptr;
	int						pos;
	int						size;
}							t_chained_string;

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

	if (!chained || !chained->ptr)
		return (NULL);
	ret = chained->ptr->string;
	chained->ptr = chained->ptr->next;
	if (!chained->ptr)
		chained->ptr = chained->list;
	return (ret);
}
