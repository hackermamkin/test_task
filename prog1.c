#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
int useful_fix;

char	*ft_itoa(int n)
{
	int		nb;
	int		i;
	int		j;
	int		a;
	int		p;
	char	*str;

	i = 0;
	a = 1;
	p = 0;
	if (n == -2147483648)
	{
		p++;
		n++;
	}
	if (n < 0)
	{
		n *= -1;
		p++;
	}
	nb = n;
	while (nb % 10 > 0)
	{
		nb /= 10;
		i++;
	}
	nb = n;
	str = (char *)malloc(sizeof(char) * (i + 1));
	j = 0;
	if (p)
	{
		str[0] = '-';
		j++;
		i--;
	}
	while (i)
	{
		a *= 10;
		i--;
	}
	a /= 10;
	while (a > 0)
	{
		str[j] = nb / a + '0';
		nb %= a;
		if (j == 1 && p == 2)
		{
			nb++;
		}
		a /= 10;
		j++;
	}
	return (str);
}

int		find_slesh_n(char *str, int i) //поиск индекса перевода символа строки
{
	while (str[i] != '\n')
		i++;
	return (i);
}

char	*del_space(char *str) // форматирование
{
	char	*str_new;
	int		i;
	int		j;
	int		value_spaces;

	i = 0;
	j = 0;
	value_spaces = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '	')
			value_spaces++;
		i++;
	}
	str_new = (char *)malloc(sizeof(char) * (i - value_spaces + 1));
	i = 0;
	while (str[i])
	{
		if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') ||
				(str[i] >= '0' && str[i] <= '9') || str[i] == '.' || str[i] == '\n')
		{
			str_new[j] = str[i];
			j++;
		}
		i++;
	}
	str_new[j] = '\0';
	return (str_new);
}

char	*del_nums(char *str) // форматирование
{
	int		j;
	int		i;
	int		num;
	char	*str_new;

	i = 0;
	j = 0;
	num = 0;
	while (str[i])
	{
		if (i == 0 || str[i] == '\n')
		{
			i++;
			while (str[i] == '\n' || (str[i] >= '0' && str[i] <= '9'))
			{
				i++;
				num++;
			}
		}
		i++;
	}
	str_new = (char *)malloc(sizeof(char) * (i - num + 1));
	i = 0;
	while (str[i])
	{
		if (i == 0 || str[i - 1] == '\n')
		{
			i++;
			while (str[i] == '\n' || (str[i] >= '0' && str[i] <= '9'))
			{
				i++;
				num++;
			}
		}
		str_new[j] = str[i];
		j++;
		i++;
	}
	str_new[j] = '\0';
	return (str_new);
}

char    **search_and_del(char **str)
{
	int i = 0;
	int j = 0;
	int fix_j = 0;;

	while (fix_j <= useful_fix)
	{
		j = fix_j + 1;
		while (j <= useful_fix)
		{
			if(strcmp(str[fix_j], str[j]) == 0)
			{
				while (str[j][i])
				{
					str[j][i] = '0';
					i++;
				}
				i = 0;
			}
			j++;
		}
		j = 0;
		fix_j++;
	}
	return (str);
}

int		divstr(char *str1, char *str2) //// тут начинается sort_params
{
	int i;

	i = 0;
	while (str1[i] == str2[i] && str1[i] && str2[i])
		i++;
	if (str1[i] - str2[i] > 0)
		return (1);
	return (0);
}

void	putstrs(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		putchar(str[i]);
		i++;
	}
	putchar('\n');
}

void	swap_str(char **a, char **b)
{
	char *c;

	c = *a;
	*a = *b;
	*b = c;
}

char	**sort_params(char **argv, int argc) // здесь заканчивается sort_params 
{
	int i;
	int i1;
	int point;

	point = 0;
	i = 1;
	i1 = 1;
	while (i != argc - 1 && argc > 1 && i1++)
	{
		if (i1 != argc && divstr(argv[i], argv[i1]) && ++point)
			swap_str(&argv[i], &argv[i1]);
		if (i1 == argc)
		{
			if (point == 0)
				i++;
			point = 0;
			i1 = i;
		}
	}
	return (argv);
}

char	**str_to_sstr(char *str) // перевод строки в двумерный массив
{
	int i = 0;
	int j = 0;
	int fix_n;
	int index = 0;
	char **str_new;

	while (str[index] == '\n')
		index++;
	while (str[index])
	{
		if (str[index] == '\n')
			i++;
		index++;
	}
	fix_n = i;
	str_new = (char **)malloc(sizeof(char *) * (i));
	i = 0;
	index = 0;
	while (fix_n >= j)
	{
		while (str[index] == '\n')
			index++;
		str_new[j] = (char *)malloc(sizeof(char) * (find_slesh_n(str, index) - index + 1));
		while (str[index] != '\n')
		{
			str_new[j][i] = str[index];
			index++;
			i++;
		}
		str_new[j][i] = '\0';
		i = 0;
		j++;
	}
	useful_fix = fix_n;
	return (str_new);
}


int		main()
{
	int		f;
	char	c;
	int		i;
	int j = 0;
	char *str1;
	char *str2;
	char *str;
	int len;
	FILE *fo;

	fo = fopen("student_file.txt", "wt");
	fclose(fo);
	i = 0;
	f = open("student_file_1.txt", O_RDONLY);
	while (read(f, &c, 1))
		i++;
	close(f);
	str1 = (char *)malloc(sizeof(char) * (i + 1));
	f = open("student_file_1.txt", O_RDONLY);
	i = 0;
	while (read(f, &c, 1))
	{
		str1[i] = c;
		i++;
	}
	str1[i] = '\0';
	close(f);

	i = 0;
	f = open("student_file_2.txt", O_RDONLY);
	while (read(f, &c, 1))
		i++;
	close(f);
	str2 = (char *)malloc(sizeof(char) * (i + 1));
	f = open("student_file_2.txt", O_RDONLY);
	i = 0;
	while (read(f, &c, 1))
	{
		str2[i] = c;
		i++;
	}
	str2[i] = '\0';
	close(f);
	str1 = del_nums(del_space(str1));
	str2 = del_nums(del_space(str2));
	len = strlen(str1);
	str = strcat(str1, str2);
	char **sst;
	sst = sort_params(str_to_sstr(str), useful_fix - 1);
	char **st = search_and_del(sst);
	f = open("student_file.txt", O_WRONLY);
	i = 0;
	j = 0;
	char q = '\n';
	char *w;
	int l = 0;
	char r;
	while (j <= useful_fix)
	{
		if (st[j][0] != '0')
			write(f, &q, 1);
		w = ft_itoa(j + 1);
		while (l <= strlen(w))
		{
			r = w[l];
			write (f, &r, 1);
			l++;
		}
		r = '	';
		write (f, &r, 1);
		r = ' ';
		l = 0;
		if (st[j][0] != '0')
		{
			while (st[j][i])
			{	
				c = st[j][i];
				if (st[j][i - 1] >= 'a' && st[j][i - 1] <= 'z' && st[j][i] >= 'A' && st[j][i] <= 'Z')
					write(f, &r, 1);
				if (st[j][i - 1] >= 'a' && st[j][i - 1] <= 'z' && st[j][i] >= '0' && st[j][i] <= '9')
					write(f, &r, 1);
				if (st[j][i] >= 'a' && st[j][i] <= 'z' && st[j][i - 1] >= '0' && st[j][i - 1] <= '9')
				{
					write(f, &q, 1);
					w = ft_itoa(j);
					while (l <= strlen(w))
					{
						r = w[l];
						write (f, &r, 1);
						l++;
					}
					r = '	';
					write (f, &r, 1);
					r = ' ';
					l = 0;
				}
				write(f, &c, 1);
				i++;
			}
		}
		i = 0;
		j++;
	}
	write(f, "\n", 1);
	close(f);
	return (0);
}