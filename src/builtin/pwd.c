#include "../include/minishell.h"

int	pwd(void)
{
	char	*path;

	path = getcwd(NULL, 1024);
	if (!path)
	{
		free(path);
		return (1);
	}
	printf("%s\n", path);
	free(path);
	return (0);
}