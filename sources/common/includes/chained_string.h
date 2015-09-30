#include <libft.h>

typedef enum
{
	ALLOCATED = 0,
	NOT_ALLOCATED = -1
}	e_status;

#define ON_HYPE(flag) (flag == ALLOCATED)

typedef struct				s_list_string
{
	char					*string;
	e_status				flag;				
	struct s_list_string	*next;
}							t_list_string;

typedef struct				s_chained_string
{
	t_list_string			*list;
	t_list_string			*ptr;
	int						pos;
	int						size;
}							t_chained_string;

t_list_string				*stack_list_string(char *str);
t_list_string				*hype_list_string(char *str);
void						free_list_string(t_list_string *list);
void						free_chained_string(t_chained_string *ptr);
void						push_stack_chained_string(t_chained_string *ptr, char *str);
void						push_hype_chained_string(t_chained_string *ptr, char *str);
void						push_allocated_chained_string(t_chained_string *ptr, char *str);
char						*foreach_chained_string(t_chained_string *chained);
int							chained_string_contains(t_chained_string chained, char *str);
int							chained_string_cross(t_chained_string c1, t_chained_string c2);
void						put_chained_string(t_chained_string chained);
void						init_chained_string(t_chained_string *chained);
int							chained_string_remove(t_chained_string *chained, char *str);