/*
** EPITECH PROJECT, 2021
** double list
** File description:
** double list
*/

#include <stdlib.h>

#include "generic_list.h"

node_t  *list_get_first_node_with_value(
    list_t list,
    void *value,
    value_comparator_t val_comp
)
{
    while (val_comp(list->value, value) && list) {
        list = list->next;
    }
    if (!list)
        return NULL;
    else {
        return ((void *)list);
    }
}