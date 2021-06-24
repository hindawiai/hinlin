<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Copyright (c) 2016 Facebook
 */
#अगर_अघोषित __PERCPU_FREELIST_H__
#घोषणा __PERCPU_FREELIST_H__
#समावेश <linux/spinlock.h>
#समावेश <linux/percpu.h>

काष्ठा pcpu_मुक्तlist_head अणु
	काष्ठा pcpu_मुक्तlist_node *first;
	raw_spinlock_t lock;
पूर्ण;

काष्ठा pcpu_मुक्तlist अणु
	काष्ठा pcpu_मुक्तlist_head __percpu *मुक्तlist;
	काष्ठा pcpu_मुक्तlist_head extralist;
पूर्ण;

काष्ठा pcpu_मुक्तlist_node अणु
	काष्ठा pcpu_मुक्तlist_node *next;
पूर्ण;

/* pcpu_मुक्तlist_* करो spin_lock_irqsave. */
व्योम pcpu_मुक्तlist_push(काष्ठा pcpu_मुक्तlist *, काष्ठा pcpu_मुक्तlist_node *);
काष्ठा pcpu_मुक्तlist_node *pcpu_मुक्तlist_pop(काष्ठा pcpu_मुक्तlist *);
/* __pcpu_मुक्तlist_* करो spin_lock only. caller must disable irqs. */
व्योम __pcpu_मुक्तlist_push(काष्ठा pcpu_मुक्तlist *, काष्ठा pcpu_मुक्तlist_node *);
काष्ठा pcpu_मुक्तlist_node *__pcpu_मुक्तlist_pop(काष्ठा pcpu_मुक्तlist *);
व्योम pcpu_मुक्तlist_populate(काष्ठा pcpu_मुक्तlist *s, व्योम *buf, u32 elem_size,
			    u32 nr_elems);
पूर्णांक pcpu_मुक्तlist_init(काष्ठा pcpu_मुक्तlist *);
व्योम pcpu_मुक्तlist_destroy(काष्ठा pcpu_मुक्तlist *s);
#पूर्ण_अगर
