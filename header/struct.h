/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 02:13:05 by jessy             #+#    #+#             */
/*   Updated: 2021/11/12 21:35:44 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_gbcollector
{
	int						type;
	int						fd;
	void					*str;
	struct s_gbcollector	*next;
}				t_gbc;

typedef enum e_token_type
{
	pipeline,
	dollar,
	space,
	redir_right,
	redir_left,
	dble_redir_right,
	dble_redir_left,
	sgle_quote,
	dble_quote,
	literal,
	errno_call,
	env_quoted,
	lit_quoted,
}				t_token_type;

typedef enum e_error_code
{
	no_err,
	err_malloc,
	err_pid,
	err_fd,
}				t_err_code;

typedef struct s_token
{
	void			*value;
	t_token_type	type;
	t_token_type	qstat;
}				t_token;

typedef struct s_info
{
	t_list	*env;
	t_dlist	*cmd;
	t_dlist	*cmdpipe;
	t_list	*path;
	t_gbc	*gbc;
	char	**evrm;
	char	*pwd;
	t_dlist	**pipe;
	t_list	*dlb_redir_left_str;
	int		tmperrno;
	int		nbpipe;
	int		redir_left;
	int		redir_right;
	int		child;
	int		stop;
	int		gnl;
	char	*killgnl;
	t_token	tab_token[11];
}				t_info;

#endif
