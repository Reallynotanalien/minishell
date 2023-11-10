# include "../../includes/minishell.h"

/* 
1- Suppression of the "unused variable" warning for signum parameter.
2- Ensuring the program's output appears on a new line with printf "\n".
3- Informing Readline that a new line has started (to maintain proper
command line editing and input handling).
4- Clearing the current input line and replacing content with an empty string.
5- Instructing Readline to redisplay the prompt & cleared input line (this is
necessary to ensure the terminal is in the correct state after SIGINT). */
void	interruption_handler(int signum)
{
	(void) signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/*Since we do not want the ^C characters to be echoed when we press Ctrl+C,
the terminal's attributes are modified to mute this echo.
If the SIGINT signal (Ctrl+C) is pressed, the interruption_handler
takes care of it. 
If the SIGQUIT signal (Ctrl+\) is pressed, nothing happens (it is
ignored), avoiding the default behavior of quitting and generating
a core dump.*/
void	signals(void)
{
	disable_ctrlc();
	signal(SIGINT, interruption_handler);
	signal(SIGQUIT, SIG_IGN);
}
