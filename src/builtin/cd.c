#include "../include/minishell.h"
#include "../libft/libft.h"

int	cd(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Usage: %s <directory>\n", argv[0]);
		return (1);
	}
	if (chdir(argv[1]) != 0)
	{
		perror("chdir");
		return (1);
	}
	else
		chdir("..");
	return (0);
}
