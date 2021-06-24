<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * lib/plist.c
 *
 * Descending-priority-sorted द्विगुन-linked list
 *
 * (C) 2002-2003 Intel Corp
 * Inaky Perez-Gonzalez <inaky.perez-gonzalez@पूर्णांकel.com>.
 *
 * 2001-2005 (c) MontaVista Software, Inc.
 * Daniel Walker <dwalker@mvista.com>
 *
 * (C) 2005 Thomas Gleixner <tglx@linutronix.de>
 *
 * Simplअगरications of the original code by
 * Oleg Nesterov <oleg@tv-sign.ru>
 *
 * Based on simple lists (include/linux/list.h).
 *
 * This file contains the add / del functions which are considered to
 * be too large to अंतरभूत. See include/linux/plist.h क्रम further
 * inक्रमmation.
 */

#समावेश <linux/bug.h>
#समावेश <linux/plist.h>

#अगर_घोषित CONFIG_DEBUG_PLIST

अटल काष्ठा plist_head test_head;

अटल व्योम plist_check_prev_next(काष्ठा list_head *t, काष्ठा list_head *p,
				  काष्ठा list_head *n)
अणु
	WARN(n->prev != p || p->next != n,
			"top: %p, n: %p, p: %p\n"
			"prev: %p, n: %p, p: %p\n"
			"next: %p, n: %p, p: %p\n",
			 t, t->next, t->prev,
			p, p->next, p->prev,
			n, n->next, n->prev);
पूर्ण

अटल व्योम plist_check_list(काष्ठा list_head *top)
अणु
	काष्ठा list_head *prev = top, *next = top->next;

	plist_check_prev_next(top, prev, next);
	जबतक (next != top) अणु
		prev = next;
		next = prev->next;
		plist_check_prev_next(top, prev, next);
	पूर्ण
पूर्ण

अटल व्योम plist_check_head(काष्ठा plist_head *head)
अणु
	अगर (!plist_head_empty(head))
		plist_check_list(&plist_first(head)->prio_list);
	plist_check_list(&head->node_list);
पूर्ण

#अन्यथा
# define plist_check_head(h)	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

/**
 * plist_add - add @node to @head
 *
 * @node:	&काष्ठा plist_node poपूर्णांकer
 * @head:	&काष्ठा plist_head poपूर्णांकer
 */
व्योम plist_add(काष्ठा plist_node *node, काष्ठा plist_head *head)
अणु
	काष्ठा plist_node *first, *iter, *prev = शून्य;
	काष्ठा list_head *node_next = &head->node_list;

	plist_check_head(head);
	WARN_ON(!plist_node_empty(node));
	WARN_ON(!list_empty(&node->prio_list));

	अगर (plist_head_empty(head))
		जाओ ins_node;

	first = iter = plist_first(head);

	करो अणु
		अगर (node->prio < iter->prio) अणु
			node_next = &iter->node_list;
			अवरोध;
		पूर्ण

		prev = iter;
		iter = list_entry(iter->prio_list.next,
				काष्ठा plist_node, prio_list);
	पूर्ण जबतक (iter != first);

	अगर (!prev || prev->prio != node->prio)
		list_add_tail(&node->prio_list, &iter->prio_list);
ins_node:
	list_add_tail(&node->node_list, node_next);

	plist_check_head(head);
पूर्ण

/**
 * plist_del - Remove a @node from plist.
 *
 * @node:	&काष्ठा plist_node poपूर्णांकer - entry to be हटाओd
 * @head:	&काष्ठा plist_head poपूर्णांकer - list head
 */
व्योम plist_del(काष्ठा plist_node *node, काष्ठा plist_head *head)
अणु
	plist_check_head(head);

	अगर (!list_empty(&node->prio_list)) अणु
		अगर (node->node_list.next != &head->node_list) अणु
			काष्ठा plist_node *next;

			next = list_entry(node->node_list.next,
					काष्ठा plist_node, node_list);

			/* add the next plist_node पूर्णांकo prio_list */
			अगर (list_empty(&next->prio_list))
				list_add(&next->prio_list, &node->prio_list);
		पूर्ण
		list_del_init(&node->prio_list);
	पूर्ण

	list_del_init(&node->node_list);

	plist_check_head(head);
पूर्ण

/**
 * plist_requeue - Requeue @node at end of same-prio entries.
 *
 * This is essentially an optimized plist_del() followed by
 * plist_add().  It moves an entry alपढ़ोy in the plist to
 * after any other same-priority entries.
 *
 * @node:	&काष्ठा plist_node poपूर्णांकer - entry to be moved
 * @head:	&काष्ठा plist_head poपूर्णांकer - list head
 */
व्योम plist_requeue(काष्ठा plist_node *node, काष्ठा plist_head *head)
अणु
	काष्ठा plist_node *iter;
	काष्ठा list_head *node_next = &head->node_list;

	plist_check_head(head);
	BUG_ON(plist_head_empty(head));
	BUG_ON(plist_node_empty(node));

	अगर (node == plist_last(head))
		वापस;

	iter = plist_next(node);

	अगर (node->prio != iter->prio)
		वापस;

	plist_del(node, head);

	plist_क्रम_each_जारी(iter, head) अणु
		अगर (node->prio != iter->prio) अणु
			node_next = &iter->node_list;
			अवरोध;
		पूर्ण
	पूर्ण
	list_add_tail(&node->node_list, node_next);

	plist_check_head(head);
पूर्ण

#अगर_घोषित CONFIG_DEBUG_PLIST
#समावेश <linux/sched.h>
#समावेश <linux/sched/घड़ी.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>

अटल काष्ठा plist_node __initdata test_node[241];

अटल व्योम __init plist_test_check(पूर्णांक nr_expect)
अणु
	काष्ठा plist_node *first, *prio_pos, *node_pos;

	अगर (plist_head_empty(&test_head)) अणु
		BUG_ON(nr_expect != 0);
		वापस;
	पूर्ण

	prio_pos = first = plist_first(&test_head);
	plist_क्रम_each(node_pos, &test_head) अणु
		अगर (nr_expect-- < 0)
			अवरोध;
		अगर (node_pos == first)
			जारी;
		अगर (node_pos->prio == prio_pos->prio) अणु
			BUG_ON(!list_empty(&node_pos->prio_list));
			जारी;
		पूर्ण

		BUG_ON(prio_pos->prio > node_pos->prio);
		BUG_ON(prio_pos->prio_list.next != &node_pos->prio_list);
		prio_pos = node_pos;
	पूर्ण

	BUG_ON(nr_expect != 0);
	BUG_ON(prio_pos->prio_list.next != &first->prio_list);
पूर्ण

अटल व्योम __init plist_test_requeue(काष्ठा plist_node *node)
अणु
	plist_requeue(node, &test_head);

	अगर (node != plist_last(&test_head))
		BUG_ON(node->prio == plist_next(node)->prio);
पूर्ण

अटल पूर्णांक  __init plist_test(व्योम)
अणु
	पूर्णांक nr_expect = 0, i, loop;
	अचिन्हित पूर्णांक r = local_घड़ी();

	prपूर्णांकk(KERN_DEBUG "start plist test\n");
	plist_head_init(&test_head);
	क्रम (i = 0; i < ARRAY_SIZE(test_node); i++)
		plist_node_init(test_node + i, 0);

	क्रम (loop = 0; loop < 1000; loop++) अणु
		r = r * 193939 % 47629;
		i = r % ARRAY_SIZE(test_node);
		अगर (plist_node_empty(test_node + i)) अणु
			r = r * 193939 % 47629;
			test_node[i].prio = r % 99;
			plist_add(test_node + i, &test_head);
			nr_expect++;
		पूर्ण अन्यथा अणु
			plist_del(test_node + i, &test_head);
			nr_expect--;
		पूर्ण
		plist_test_check(nr_expect);
		अगर (!plist_node_empty(test_node + i)) अणु
			plist_test_requeue(test_node + i);
			plist_test_check(nr_expect);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(test_node); i++) अणु
		अगर (plist_node_empty(test_node + i))
			जारी;
		plist_del(test_node + i, &test_head);
		nr_expect--;
		plist_test_check(nr_expect);
	पूर्ण

	prपूर्णांकk(KERN_DEBUG "end plist test\n");
	वापस 0;
पूर्ण

module_init(plist_test);

#पूर्ण_अगर
