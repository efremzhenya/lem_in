#include "../includes/lem-in.h"

void	print_adj_list(t_lemin **lemin)
{
	size_t i;
	t_ilist *list;

	i = 0;
	if ((*lemin)->rooms > 0)
	{
		while (i < ((*lemin)->rooms))
		{
			ft_putnbr((*lemin)->adj[i]->index);
			if ((*lemin)->adj[i]->links)
			{
				write(1, ": ", 2);
				list = (*lemin)->adj[i]->links;
				while (list->next)
				{
					ft_putnbr(list->index);
					write(1, ", ", 2);
					list = list->next;
				}
				ft_putnbr(list->index);
			}
			write(1, "\n", 1);
			i++;
		}
	}
}
