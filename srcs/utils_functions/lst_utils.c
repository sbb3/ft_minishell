
#include "../parser/parser.h"

t_component	*ft_lstnew(char *content, int tkn_type)
{
	t_component	*element;

	element = malloc(sizeof(t_component));
	exit_if_null(element, "Allocation failed");
	element->content = ft_strdup(content);
	element->type = tkn_type;
	element->next = NULL;
	return (element);
}

void	ft_lstadd_back(t_component **head, t_component *new)
{
	t_component	*current_node;

	if ((*head) == NULL)
		(*head) = new;
	else
	{
		current_node = (*head);
		while (current_node->next != NULL)
			current_node = current_node->next;
		current_node->next = new;
	}
}

t_env	*lstinit(char *key, char *value)
{
	t_env	*element;

	element = malloc(sizeof(t_env));
	exit_if_null(element, "Allocation failed");
	element->key = key;
	element->value = value;
	element->next = NULL;
	return (element);
}

void	pushback(t_env **head, t_env *new)
{
	t_env	*current_node;

	if ((*head) == NULL)
		(*head) = new;
	else
	{
		current_node = (*head);
		while (current_node->next != NULL)
			current_node = current_node->next;
		current_node->next = new;
	}
}
