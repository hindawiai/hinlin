<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *	klist.h - Some generic list helpers, extending काष्ठा list_head a bit.
 *
 *	Implementations are found in lib/klist.c
 *
 *	Copyright (C) 2005 Patrick Mochel
 */

#अगर_अघोषित _LINUX_KLIST_H
#घोषणा _LINUX_KLIST_H

#समावेश <linux/spinlock.h>
#समावेश <linux/kref.h>
#समावेश <linux/list.h>

काष्ठा klist_node;
काष्ठा klist अणु
	spinlock_t		k_lock;
	काष्ठा list_head	k_list;
	व्योम			(*get)(काष्ठा klist_node *);
	व्योम			(*put)(काष्ठा klist_node *);
पूर्ण __attribute__ ((aligned (माप(व्योम *))));

#घोषणा KLIST_INIT(_name, _get, _put)					\
	अणु .k_lock	= __SPIN_LOCK_UNLOCKED(_name.k_lock),		\
	  .k_list	= LIST_HEAD_INIT(_name.k_list),			\
	  .get		= _get,						\
	  .put		= _put, पूर्ण

#घोषणा DEFINE_KLIST(_name, _get, _put)					\
	काष्ठा klist _name = KLIST_INIT(_name, _get, _put)

बाह्य व्योम klist_init(काष्ठा klist *k, व्योम (*get)(काष्ठा klist_node *),
		       व्योम (*put)(काष्ठा klist_node *));

काष्ठा klist_node अणु
	व्योम			*n_klist;	/* never access directly */
	काष्ठा list_head	n_node;
	काष्ठा kref		n_ref;
पूर्ण;

बाह्य व्योम klist_add_tail(काष्ठा klist_node *n, काष्ठा klist *k);
बाह्य व्योम klist_add_head(काष्ठा klist_node *n, काष्ठा klist *k);
बाह्य व्योम klist_add_behind(काष्ठा klist_node *n, काष्ठा klist_node *pos);
बाह्य व्योम klist_add_beक्रमe(काष्ठा klist_node *n, काष्ठा klist_node *pos);

बाह्य व्योम klist_del(काष्ठा klist_node *n);
बाह्य व्योम klist_हटाओ(काष्ठा klist_node *n);

बाह्य पूर्णांक klist_node_attached(काष्ठा klist_node *n);


काष्ठा klist_iter अणु
	काष्ठा klist		*i_klist;
	काष्ठा klist_node	*i_cur;
पूर्ण;


बाह्य व्योम klist_iter_init(काष्ठा klist *k, काष्ठा klist_iter *i);
बाह्य व्योम klist_iter_init_node(काष्ठा klist *k, काष्ठा klist_iter *i,
				 काष्ठा klist_node *n);
बाह्य व्योम klist_iter_निकास(काष्ठा klist_iter *i);
बाह्य काष्ठा klist_node *klist_prev(काष्ठा klist_iter *i);
बाह्य काष्ठा klist_node *klist_next(काष्ठा klist_iter *i);

#पूर्ण_अगर
