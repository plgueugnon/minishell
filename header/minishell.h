/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 02:07:36 by jessy             #+#    #+#             */
/*   Updated: 2021/11/17 18:29:35 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include "libft.h"
# include "struct.h"
# include <errno.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <dirent.h>
# include <limits.h>

# define TOKEN 4

extern t_info	g_info;

/* BUILTINS */
int				error_code(t_err_code err_code);
int				exit2bis(char *cmd, int *i, int j);
int				exit2(char *cmd, int *i, int j);
void			exit3(char *cmd, int i);
void			ft_exit(char *cmd, t_err_code err_code);
void			pwd(char *cmd, int fd);
void			oldpwd(void);
int				cd1(char *cmd, int i, int *j);
void			cd2(char *cmd, int j);
void			cd(char *cmd);
void			env2(char *cmd);
void			env(char *cmd, int fd);
void			unset2(char *cmd, int j);
void			unset(char *cmd);
void			echo(char *cmd, int fd);
void			export1(int fd);
void			export2(char *cmd, int i);
void			export3(int *i, int *j, int *add, char *cmd);
void			export4(t_list	*tmp, char *cmd, int i, int j);
void			export5(t_list	*tmp, char *cmd, int i);
void			ft_export(char *cmd, int fd);
void			cd3(void);
/* EXEC_COMMAND */
int				check_builtins(t_dlist *mcmd);
char			**dup_env(t_list *env);
void			check_exec2(char *tmp, char **str);
int				check_exec(t_dlist *mcmd);
void			exec_command(t_dlist *list);
void			check_end(t_dlist **alst);
void			fill_gbc2(int *i, int *check, t_dlist *tmp);
t_dlist			*fill_gbc(t_dlist *lst, int i);
int				check_path2(char **path, char *tmp1);
int				check_path(char *tmp1);
int				check_exist(char *str);
int				check_binaire(char *str);
void			check_command4(t_dlist **dlsttmp1, int i);
int				check_command6(char *chrtmp1, t_dlist **dlsttmp1);
int				check_command7(char	*chrtmp1);
int				check_command5(t_dlist	**dlsttmp1, t_token *token1,
					char *chrtmp1);
int				check_command8(char *chrtmp1);
int				check_command3(t_token *token1, t_dlist *dlsttmp1,
					t_dlist *list);
int				check_command2(t_token *token1, t_dlist *dlsttmp1,
					t_dlist *list);
int				check_command(t_dlist *list);
void			joincmd(char **cmd, t_dlist *lst);
void			joincmd2(t_dlist *tmp1, int *i);
int				check_builtins2(char *cmd, int i);
/* EXIT */
void			clear_token(t_dlist *list, t_token *token);
void			clear_cmd_lst(t_dlist **lst);
int				clear_cmd_node(t_dlist **lst);
void			free_dbl(char **str);
/* EXPAND_ENV_UTILS */
void			replace_node_value(char **evar, t_dlist **iter);
int				valid_env_char(int c);
int				find_env_var(t_dlist **iter);
int				find_errno_type(t_dlist *lst);
void			replace_errno(char *str, t_dlist **lst);
char			**get_val_to_expand(t_token	*token);
int				check_if_value_in_env(char *envval, char *cmdval);
int				clean_tab(char **tab, int ret);
void			reparse_expanded_value(t_dlist **iter);
int				is_there_a_space(char *str);
/* EXPAND_ENV */
void			concat_node(t_token *atoken, t_token *btoken, t_dlist **iter);
void			concat_narrow_litvalue(void);
int				is_env_literal(t_dlist **iter);
void			expand_env(void);
void			concat_narrow_litvalue(void);
/* GBCOLLECTOR */
void			clearmaillon(t_gbc *lst);
void			gbcclear(t_gbc **alst);
void			gbcclear_one(t_gbc **alst, int maillon, int size);
t_gbc			*newgbc(int type, int fd, void *str);
void			lstaddback_gbc(t_gbc **alst, t_gbc *new);
/* MAIN */
char			**duplst(t_list *env);
void			init_struct(void);
void			change_shlv(t_list **env);
char			**fill_nullenv(void);
int				main(int ac, char **av, char **envp);
/* PARSE_ENV */
void			parse_env(void);
/* PARSE */
int				check_pipe(void);
int				check_error_pipe2(void);
int				check_error_pipe(void);
void			parse_token2(void);
void			parse_token(void);
int				next_identical_token(t_dlist **iter,
					t_dlist *node, t_token *src);
int				is_it_literal(t_dlist *node, t_token *token);
int				check_pipe2(t_dlist *tmp, t_token *token);
int				check_if_quoted(t_dlist *node, t_token *token);
/* PIPELINE */
void			exec_child(t_dlist *iter, int *fd, int cfd);
void			free_cmdpipe(t_dlist *list, int i, int *tabpid);
void			exec_parent(int *fd, int *cfd, t_dlist **iter);
void			exec_pipeline(t_dlist *list, int *tabpid, int i, int cfd);
void			create_pipe3(t_dlist **tmp, t_dlist **lr, t_dlist **pipe);
void			create_pipe2(t_dlist **pipe);
void			create_pipeline(void);
void			check_if_exit(t_dlist *list);
void			check_if_exit2(t_dlist	*tmp);
/* PROMPT_UTILS */
void			ft_get_path2(char **path, char *buff, char *color, int i);
int				ft_get_path(char **path, char *buff, char *color);
int				catch_eof_signal(char *line, char *path);
char			*get_prompt(void);
/* PROMPT */
void			ft_sighandler(int signum);
void			refill_pwd(void);
void			ft_prompt(void);
/* QUOTE_UTILS */
int				find_token_type(t_token_type type, t_token *token);
void			clear_sublst(t_dlist *begin, t_dlist *end);
t_dlist			*samequote_begin_or_end(t_dlist *begin, t_dlist *end);
t_dlist			*clean_sublst(t_dlist *begin, t_dlist *end);
void			clear_buffer(char *buf, char *tmp);
/* QUOTE */
char			*concate_node(t_dlist **sub, t_token_type type);
t_dlist			*concate_quoted(t_dlist *sub, t_token_type type);
void			parse_quote(void);
/* REDIRECTION */
void			go_redirect3b(t_dlist *tmp, t_token *token, t_dlist *mcmd);
void			go_redirect3(t_dlist *tmp, t_dlist *rdrct,
					t_token *token, t_dlist *mcmd);
void			go_redirect(t_dlist *rdrct, t_dlist *mcmd);
void			redirection2(t_dlist **stock_rdrct, t_dlist **stockcmd);
void			redirection(void);
int				check_redirecterr(t_gbc *allcmd);
int				check_directory2(char *str, char **dir);
int				check_directory(char *str);
int				createfile2err(t_token *token, DIR *check);
int				createfile2b(t_token *token);
int				createfile2(t_dlist *tmp, t_token *token);
int				createfile3(t_dlist *tmp, t_token *token, int i);
int				createfile4(t_dlist *tmp, t_token *token, int i);
void			createfile5(t_dlist *tmp, t_token *token);
int				createfileb(t_dlist *tmp, t_token *token, int i);
int				createfile(t_dlist *allfile);
t_dlist			*clear_struct2(t_dlist **tmp, t_token **token,
					t_dlist **tmp2, t_dlist **lst);
t_dlist			*clear_struct(t_dlist **lst);
void			go_redirect2b(void);
void			go_redirect2t(t_dlist *tmp, t_dlist *rdrct,
					t_token *token, int *fdio);
void			go_redirect2(t_dlist *tmp, t_dlist *rdrct,
					t_token *token, t_dlist *mcmd);
void			expand_dlb_left_input(char **str);
void			ambiguous_redirect_msg(t_token	*token);
/* TOKENIZE */
t_token_type	ft_define_token(char charset);
t_token			*ft_malloc_token(char *input, t_token_type type, int i, int j);
int				is_it_double_redir(char *s, int i);
t_token			*ft_find_token(char *s, int *i);
void			ft_create_token(char *s);
/* UTILS */
void			tmplstclear(t_dlist **lst);
void			init_var(void);
size_t			ft_strlen_utils(const char *s, char stop);
void			ft_get_env(char **envp);
void			init_tab_token(void);
int				ft_go_malloc(char **str, int len);
void			error_dbl(char **ret, int size);
char			**dbl_chardup2(char **envp, int i, int j, char ***dest);
char			**dbl_chardup(char **envp);
char			*strpthjoin(char *s1, char *s2);
long long int	ft_atoll(char *str, int *error);
char			*supp_add(char *str);
int				ft_strcmp(char *s1, char *s2);
int				createfilestop(char *str);
void			clean_split(char **tab);
int				free_ret(void *p, int ret);

#endif