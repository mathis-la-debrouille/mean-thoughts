/*
** EPITECH PROJECT, 2021
** double list
** File description:
** double list
*/

#include <stdio.h>

#include "generic_list.h"

unsigned int list_get_size(list_t list) {
  int len = 0;

  for (; list; list = list->next) {
    ++len;
  }
  return (len);
}

bool list_is_empty(list_t list) { return (!list); }

void list_dump(list_t list, value_displayer_t val_disp) {
  list_t tmp = list;

  while (tmp) {
    val_disp(tmp->value);
    tmp = tmp->next;
  }
}