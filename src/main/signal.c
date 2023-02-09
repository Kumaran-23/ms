#include "../include/minishell.h"

//ctrl c = sigint (intrrup process) ---> new prompt  || done!
//ctrl \ = sigquit (quit process) ---->nothing   |||done!
//ctrl z = sigstp ()
//ctrl d = eof --> exit || done!

void sig_handler(int signum)
{
	printf("%d done", signum);
}

static void
int_handler() {
    printf("\n"); // Move to a new line
    rl_on_new_line(); // Regenerate the prompt on a newline
    rl_replace_line(" ", 0); // Clear the previous text
    rl_redisplay();
}


void disable_veof(void)
{
	struct termios ori_settings;

    tcgetattr(STDIN_FILENO, &ori_settings);
    struct termios new_settings = ori_settings;
    new_settings.c_cc[VEOF] = 3;
	//new_settings.c_cc[VINTR] = 4;
	
	tcsetattr(STDIN_FILENO, TCSANOW, &new_settings);
}

void define_signal(void)
{
	disable_veof();
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, int_handler);
	
}