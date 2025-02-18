/*
** EPITECH PROJECT, 2021
** void *list
** File description:
** void *list
*/

#include <stdlib.h>

#include "generic_list.h"

bool list_add_elem_at_front(list_t *front_ptr, void *elem) {
    list_t new_node = malloc(sizeof(node_t));

    if (!new_node) {
        return (false);
    }
    new_node->value = elem;
    new_node->next = *front_ptr;
    *front_ptr = new_node;
    return (true);
}

bool list_add_elem_at_back(list_t *front_ptr, void *elem) {
    list_t new_node = malloc(sizeof(node_t));
    list_t tmp = *front_ptr;
    list_t copy = tmp;

    if (!new_node)
        return (false);
    new_node->value = elem;
    new_node->next = NULL;
    if (!tmp) {
        *front_ptr = new_node;
        return (true);
    }
    while (tmp->next) {
        tmp = tmp->next;
    }
    tmp->next = new_node;
    *front_ptr = copy;
    return (true);
}

bool list_add_elem_at_position(
  list_t *front_ptr, void *elem, unsigned int position
) {
    list_t new_node = malloc(sizeof(node_t));
    list_t tmp = *front_ptr;
    list_t copy = tmp;

    if (position == 0 || position > list_get_size(*front_ptr)) {
        return list_add_elem_at_front(front_ptr, elem);
    }
    if (!new_node) {
        return (false);
    }
    new_node->value = elem;
    new_node->next = NULL;
    for (unsigned int i = 0; i < position - 1; ++i)
        tmp = tmp->next;
    new_node->next = tmp->next;
    tmp->next = new_node;
    *front_ptr = copy;
    return (true);
}

bool list_del_node(list_t *front_ptr, node_t *node_ptr) {
    list_t tmp = *front_ptr;
    node_t *to_delete = NULL;

    if (tmp == node_ptr)
        return (list_del_elem_at_front(front_ptr));
    while (tmp && tmp->next != node_ptr) {
        tmp = tmp->next;
    }
    if (!tmp)
        return (false);
    to_delete = tmp->next;
    tmp = tmp->next->next;
    free(to_delete);
    return (true);
}