/*
** EPITECH PROJECT, 2021
** double list
** File description:
** double list
*/

#include <stdlib.h>

#include "generic_list.h"

bool list_del_elem_at_front(list_t *front_ptr)
{
    list_t tmp = *front_ptr;

    if (!front_ptr || !tmp)
        return false;
    *front_ptr = (*front_ptr)->next;
    free(tmp);
    return true;
}

bool list_del_elem_at_back(list_t *front_ptr)
{
    list_t tmp = *front_ptr;

    if (!(*front_ptr)) {
        return false;
    }
    if (!tmp->next) {
        *front_ptr = (*front_ptr)->next;
        return true;
    }
    while (tmp->next && tmp->next->next) {
        tmp = tmp->next;
    }
    tmp->next = NULL;
    return true;
}

bool list_del_elem_at_position(list_t *front_ptr, unsigned int position)
{
    list_t tmp = *front_ptr;

    if (!(*front_ptr))
        return false;
    if (position == 0) {
        return list_del_elem_at_front(front_ptr);
    } else if (position == list_get_size(*front_ptr) - 1)
        return list_del_elem_at_back(front_ptr);
    for (unsigned int i = 0; i < position - 1 && tmp->next; ++i) {
        tmp = tmp->next;
    }
    if (!tmp->next || !tmp->next->next)
        return (false);
    tmp->next = tmp->next->next;
    return true;
}

void list_clear(list_t *front_ptr)
{
    list_t tmp = *front_ptr;
    node_t *node = NULL;

    while (tmp && tmp->next) {
        node = tmp;
        tmp = tmp->next;
        free(node);
    }
    *front_ptr = NULL;
}