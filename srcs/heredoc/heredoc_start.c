#include <structs.h>
#include <ft_strncmp.h>
#include <ft_strdup.h>
#include <ft_substr.h>
#include <ft_strjoin.h>
#include <lexer_clear.h>
#include <lexer_display.h>
#include <stdio.h>
#include <heredoc_line_parse.h>

void	init_heredoc_struct(t_heredoc *heredoc)
{
	heredoc->End = NULL;
	heredoc->has_quote = 0;
}

t_lexer *join_heredoc_quotes(t_lexer *head, t_heredoc *heredoc, char *input)
{
	t_lexer *tail;
	char	*temp;
	char	*temp_two;

	tail = head->next;
	heredoc->has_quote = 1;
	while(tail)
	{
		if (tail->token_type == Double_Quote || tail->token_type == Quote)
			break ;
		tail = tail->next;
	}
	temp = heredoc->End;
	temp_two = ft_substr(input, head->start + 1, tail->end - 1 - head->start);
	heredoc->End = ft_strjoin(temp, temp_two);
	free(temp);
	free(temp_two);
	return (tail);
}

t_lexer *remove_heredoc_list(t_lexer *head, t_lexer *tail)
{
	t_lexer *temp;

	temp = head->prev;
	while (head != tail)
		head = rm_one_from_lexer_list(head);
	head = rm_one_from_lexer_list(head);
	if (temp)
	{
		if (head)
			head->prev = temp;
		temp->next = head;
		return (temp);
	}
	else
		return (head);
		
}
t_lexer	*go_handle(t_lexer *lex_head, t_heredoc *heredoc, char *input)
{
	t_lexer *tail;
	char	*temp;

	tail = lex_head->next;
	heredoc->End = ft_strdup("\0");
	while (tail)
	{
		if (tail->token_type == Double_Quote || tail->token_type == Quote)
			tail = join_heredoc_quotes(tail, heredoc, input);
		else
		{
			temp = heredoc->End;
			heredoc->End = ft_strjoin(heredoc->End, tail->content);
			free(temp);
		}
		if (!tail->next || (tail->next->start - tail->end != 1))
			break ;
		tail = tail->next;
	}
	lex_head = remove_heredoc_list(lex_head, tail);
	return (lex_head);
}

t_parse	*handle_heredoc(t_lexer *lex_head, t_parse *head, char *input)
{
	t_lexer	*tail;
	t_heredoc heredoc;

	tail = lex_head;
	init_heredoc_struct(&heredoc);
	while (tail)
	{
		if (tail->token_type == Double_Lesser)
		{
			tail = go_handle(tail, &heredoc, input);
			head->heredoc_pipe = parse_line_heredoc(head, &heredoc);
		}
		if (tail->token_type == Pipe || head->heredoc_pipe == -2)
			break ;
		if (tail)
			tail = tail->next;
		heredoc.has_quote = 0;
	}
	return (head);
}