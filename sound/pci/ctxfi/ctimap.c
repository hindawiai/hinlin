<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2008, Creative Technology Ltd. All Rights Reserved.
 *
 * @File	ctimap.c
 *
 * @Brief
 * This file contains the implementation of generic input mapper operations
 * क्रम input mapper management.
 *
 * @Author	Liu Chun
 * @Date 	May 23 2008
 */

#समावेश "ctimap.h"
#समावेश <linux/slab.h>

पूर्णांक input_mapper_add(काष्ठा list_head *mappers, काष्ठा imapper *entry,
		     पूर्णांक (*map_op)(व्योम *, काष्ठा imapper *), व्योम *data)
अणु
	काष्ठा list_head *pos, *pre, *head;
	काष्ठा imapper *pre_ent, *pos_ent;

	head = mappers;

	अगर (list_empty(head)) अणु
		entry->next = entry->addr;
		map_op(data, entry);
		list_add(&entry->list, head);
		वापस 0;
	पूर्ण

	list_क्रम_each(pos, head) अणु
		pos_ent = list_entry(pos, काष्ठा imapper, list);
		अगर (pos_ent->slot > entry->slot) अणु
			/* found a position in list */
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (pos != head) अणु
		pre = pos->prev;
		अगर (pre == head)
			pre = head->prev;

		__list_add(&entry->list, pos->prev, pos);
	पूर्ण अन्यथा अणु
		pre = head->prev;
		pos = head->next;
		list_add_tail(&entry->list, head);
	पूर्ण

	pre_ent = list_entry(pre, काष्ठा imapper, list);
	pos_ent = list_entry(pos, काष्ठा imapper, list);

	entry->next = pos_ent->addr;
	map_op(data, entry);
	pre_ent->next = entry->addr;
	map_op(data, pre_ent);

	वापस 0;
पूर्ण

पूर्णांक input_mapper_delete(काष्ठा list_head *mappers, काष्ठा imapper *entry,
		     पूर्णांक (*map_op)(व्योम *, काष्ठा imapper *), व्योम *data)
अणु
	काष्ठा list_head *next, *pre, *head;
	काष्ठा imapper *pre_ent, *next_ent;

	head = mappers;

	अगर (list_empty(head))
		वापस 0;

	pre = (entry->list.prev == head) ? head->prev : entry->list.prev;
	next = (entry->list.next == head) ? head->next : entry->list.next;

	अगर (pre == &entry->list) अणु
		/* entry is the only one node in mappers list */
		entry->next = entry->addr = entry->user = entry->slot = 0;
		map_op(data, entry);
		list_del(&entry->list);
		वापस 0;
	पूर्ण

	pre_ent = list_entry(pre, काष्ठा imapper, list);
	next_ent = list_entry(next, काष्ठा imapper, list);

	pre_ent->next = next_ent->addr;
	map_op(data, pre_ent);
	list_del(&entry->list);

	वापस 0;
पूर्ण

व्योम मुक्त_input_mapper_list(काष्ठा list_head *head)
अणु
	काष्ठा imapper *entry;
	काष्ठा list_head *pos;

	जबतक (!list_empty(head)) अणु
		pos = head->next;
		list_del(pos);
		entry = list_entry(pos, काष्ठा imapper, list);
		kमुक्त(entry);
	पूर्ण
पूर्ण

