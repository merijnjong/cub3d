/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merijnjong <merijnjong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:22:54 by mjong             #+#    #+#             */
/*   Updated: 2025/06/06 14:53:07 by merijnjong       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <fcntl.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 600
# endif

int		ft_atoi(const char *nptr);
long	ft_atol(const char *nptr);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		ft_isspacei(int c);
int		ft_isspacec(char c);
char	*ft_itoa(int n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_qsort(char **array, int low, int high, int (*cmp)(const char *,
				const char *));
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *s, int c);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strdup(const char *s);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
int		ft_strlen(const char *str);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strncpy(char *dest, const char *src, size_t n);
char	*ft_strndup(const char *s, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strrchr(const char *s, int c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(const char *s, unsigned int start, size_t len);
int		ft_tolower(int c);
int		ft_toupper(int c);
char	*get_next_line(int fd);
char	*ft_strjoin2(char *s1, char *s2);
int		ft_strlen2(const char *str);
char	*ft_strchr2(char *s, int c);
void	ft_free(char **str);
char	*ft_free2(char **str);
int		ft_printf(const char *s, ...);
int		ft_printc(char c);
int		ft_printd(int n);
int		ft_printp(void *p);
int		ft_printp2(void *p);
int		ft_prints(char *s);
int		ft_printu(unsigned int n);
int		ft_printx_lo(long n);
int		ft_printx_up(long n);
int		ft_fprintp2(int fd, void *p);
int		ft_fprintp(int fd, void *p);
int		ft_fprintu(int fd, unsigned int n);
int		ft_fprintx_up(int fd, long n);
int		ft_fprintd(int fd, int n);
int		ft_fprints(int fd, char *s);
int		ft_fprintc(int fd, char c);
int		ft_fprintf(int fd, const char *s, ...);
int		ft_fprintx_lo(int fd, long n);

#endif
