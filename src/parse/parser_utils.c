#include "../include/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

//prints out the different tokens and their types
void print_tokens(t_token *tokens)
{
 	t_token	*curr;

 	curr = tokens;
 	while (curr)
 	{
 		printf("token : |%s| type : %d\n", curr->str, curr->type);
 		curr = curr->next;
 	}
}