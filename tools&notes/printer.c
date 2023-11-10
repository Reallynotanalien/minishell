#include "../includes/minishell.h"
#include "../includes/parsing.h"
#include "../includes/exec.h"

int	main(void)
{
	//possiblement à modifier, selon la structure qu'on va utiliser
	t_data		*data;
	//t_dlist	*tokens;
	char	*line;
	
	printf("%i\n", PRINTER);
	sh = malloc(sizeof(t_data));
	//tokens = malloc(sizeof(t_dlist));
	signals();
	print_progress(PRINTER, SIGNALS_OK);
	//mini parsing
	print_progress(PRINTER, GLOBAL_PARSING_OK);
	while (1)
	{
		line = readline("minishell$> ");
		print_progress(PRINTER, READLINE_OK);
		if (line && *line)
		{
			//mettre add history après l'exec? pck si la commande est pas trouvée avec bash il la montre pas dans l'historique
			//parsing(line, tokens);
			parsing(line, sh);
			print_progress(PRINTER, PARSING_OK);
			if (data->error_flag != ERROR)
				exec(sh);
			print_progress(PRINTER, EXEC_OK);
			add_history(line);
			print_progress(PRINTER, HISTORY_OK);
			//free tokens
			print_progress(PRINTER, FREE_TOKENS_OK);
		}
		if (!line)
			break ;
		free(line);
		print_progress(PRINTER, FREE_LINE_OK);
	}
	print_progress(PRINTER, LOOP_ENDED);
	rl_clear_history();
	print_progress(PRINTER, CLEAR_HISTORY_OK);
	//free(tokens);
	free(sh);
	return (0);
}
