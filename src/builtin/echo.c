#include "../include/minishell.h"
#include "../libft/libft.h"

int	echo(int argc, char **argv)
{
	int	i;
	int	flag;

	if (argc < 2)
		return (1);
	i = 1;
	flag = 0;
	if (argv[i] && strncmp(argv[i], "-n", 2) == 0)
	{
		flag = 1;
		i++;
	}
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	if (flag == 0)
		printf("\n");
	return (0);
}