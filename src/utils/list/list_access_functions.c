/*
** EPITECH PROJECT, 2021
** double list
** File description:
** double list
*/

#include "generic_list.h"

void *list_get_elem_at_front(list_t list) {
    if (!list) {
        return (0);
    }
    return (list->value);
}

void *list_get_elem_at_back(list_t list) {
    list_t tmp = list;

    while (tmp->next) {
        tmp = tmp->next;
    }
    return (tmp->value);
}

void *list_get_elem_at_position(list_t list, unsigned int position) {
    list_t tmp = list;

    for (unsigned int i = 0; i < position && tmp->next; ++i) {
        tmp = tmp->next;
    }
    return (tmp->value);
}