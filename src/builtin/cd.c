#include "../include/minishell.h"
#include "../libft/libft.h"

void ft_change_path(char *path)
{
	chdir(path);
	printf(" change to %s\n", path);
}

void ft_home_dir()
{
	char *path;

	path = ft_strdup(getenv("HOME"));
	ft_change_path(path);
}

void ft_prev_dir(char *path)
{

	ft_change_path(path);
}

void check_old_path()
{
      char **s = environ;
      int i = 0;

  while (s[i]) 
  {
    if (strstr(s[i], "OLDPWD"))
    printf("%s\n [%d] \n", s[i], i);
    i++;
  }
}

char * save_old_path(char *now)
{
      char **s = environ;
      int i = 0;

  while (s[i]) 
  {
    if (strstr(s[i], "OLDPWD"))
	{
    printf("%s\n [%d] \n", s[i], i);
	size_t len = ft_strlen(s[i]);
	memcpy(s[i], now, len);
	printf("%s\n [%d] \n", s[i], i);
	}
    i++;
  }
  return (s[i]);
}


int	cd(int argc, char **argv)
{
	char *now;
	char arg[1024];
	char *curr;

	if (ft_strcmp(argv[1], "-"))
	{
		now = getcwd(arg, 1024);
		curr = save_old_path(now);
		}
	if (argc != 2)
	{
		printf("Usage: %s <directory>\n", argv[0]);
		return (1);
	}
	//if (chdir(argv[1]) != 0)
	//{
	//	perror("chdir");
	//	return (1);
	//}
	if (!ft_strcmp(argv[1], "~"))
	{
		ft_home_dir();
		return (0);
	}
	if (!ft_strcmp(argv[1], "-"))
	{
		ft_prev_dir(now);
		return (0);
	}
	else
	{
		chdir(argv[1]);
		printf("1\n");
	}
	
	return (0);
}
