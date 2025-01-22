/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzyberaj <uzyberaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:20:02 by ulyssezyber       #+#    #+#             */
/*   Updated: 2025/01/21 19:38:22 by uzyberaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// Vérifie s'il y un \n dans la liste chainée
// Si oui, retourne 1, sinon 0
// Utilisé par create_list pour savoir si la lecture d'une ligne peut s'arrêter
int	found_newline(t_list *list)
{
	int	i;

	if (NULL == list)
		return (0);
	while (list)
	{
		i = 0;
		while (list->str_buf[i] && i < BUFFER_SIZE)
		{
			if (list->str_buf[i] == '\n')
				return (1);
			++i;
		}
		list = list->next;
	}
	return (0);
}

// Parcours la liste chainée et retourne le dernier noeud
// Celui dont le next est NULL
// Utilisé par add_to_list pour ajouter un nouveau noeud à la fin
t_list	*find_last_node(t_list *list)
{
	if (NULL == list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

// Calcule la longueur totale jusqu'à un \n dans la liste
// Utilisé par get_line pour allouer une chaine de la taille de la ligne
int	len_to_newline(t_list *list)
{
	int	i;
	int	len;

	if (NULL == list)
		return (0);
	len = 0;
	while (list)
	{
		i = 0;
		while (list->str_buf[i])
		{
			if (list->str_buf[i] == '\n')
			{
				++len;
				return (len);
			}
			++i;
			++len;
		}
		list = list->next;
	}
	return (len);
}

// Copie les caractères de la liste chainée dans une chaine jusqu'à un \n
// Utilisé par get_line pour extraire la ligne sous forme de chaine
void	copy_str(t_list *list, char *str)
{
	int	i;
	int	k;

	if (NULL == list)
		return ;
	k = 0;
	while (list)
	{
		i = 0;
		while (list->str_buf[i])
		{
			if (list->str_buf[i] == '\n')
			{
				str[k++] = '\n';
				str[k] = '\0';
				return ;
			}
			str[k++] = list->str_buf[i++];
		}
		list = list->next;
	}
	str[k] = '\0';
}

// Nettoie la liste chaînée après l'extraction d'une ligne complète
// Libère la mémoire des nœuds de la liste chaînée déjà traités
// S'il reste des données après le \n, on les conserve dans clean_node
// Utilisé par polish_list pour nettoyer la liste après l'extraction d'une ligne
void	dealloc(t_list **list, t_list *clean_node, char *buf)
{
	t_list	*tmp;

	if (NULL == *list)
		return ;
	while (*list)
	{
		tmp = (*list)->next;
		free((*list)->str_buf);
		free(*list);
		*list = tmp;
	}
	*list = NULL;
	if (clean_node->str_buf[0])
		*list = clean_node;
	else
	{
		free(buf);
		free(clean_node);
	}
}
