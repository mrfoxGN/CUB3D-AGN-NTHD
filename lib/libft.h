/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntahadou <ntahadou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 11:20:43 by ntahadou          #+#    #+#             */
/*   Updated: 2025/09/18 14:50:02 by ntahadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <limits.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
char				*ft_strchr(const char *str, int sc);
int					ft_memcmp(const void *first, const void *second,
						size_t num);
void				ft_bzero(void *str, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t size);
char				*ft_strrchr(const char *str, int sc);
int					ft_strncmp(const char *first, const char *second,
						size_t length);
void				*ft_memcpy(void *dest, const void *src, size_t size);
void				*ft_memset(void *str, int value, size_t count);
size_t				ft_strlcpy(char *dest, const char *src, size_t size);
size_t				ft_strlcat(char *dest, const char *src, size_t size);
void				*ft_memchr(const void *ptr, int value, size_t num);
char				*ft_strnstr(const char *str, const char *word, size_t len);
long				ft_atoi(const char *str);
size_t				ft_strlen(const char *str);
char				*ft_strmapi(const char *str, char (*f)(unsigned int, char));
void				*ft_calloc(size_t nbr_elm, size_t elm_size);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strdup(const char *str);
t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
char				*ft_strtrim(char const *s, char const *set);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstclear(t_list **lst, void (*del)(void *));
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				**ft_split(const char *s, char c);
char				*ft_itoa(int n);
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
int					ft_lstsize(t_list *lst);
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

#endif
