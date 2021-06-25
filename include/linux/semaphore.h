<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2008 Intel Corporation
 * Author: Matthew Wilcox <willy@linux.पूर्णांकel.com>
 *
 * Please see kernel/locking/semaphore.c क्रम करोcumentation of these functions
 */
#अगर_अघोषित __LINUX_SEMAPHORE_H
#घोषणा __LINUX_SEMAPHORE_H

#समावेश <linux/list.h>
#समावेश <linux/spinlock.h>

/* Please करोn't access any members of this काष्ठाure directly */
काष्ठा semaphore अणु
	raw_spinlock_t		lock;
	अचिन्हित पूर्णांक		count;
	काष्ठा list_head	रुको_list;
पूर्ण;

#घोषणा __SEMAPHORE_INITIALIZER(name, n)				\
अणु									\
	.lock		= __RAW_SPIN_LOCK_UNLOCKED((name).lock),	\
	.count		= n,						\
	.रुको_list	= LIST_HEAD_INIT((name).रुको_list),		\
पूर्ण

#घोषणा DEFINE_SEMAPHORE(name)	\
	काष्ठा semaphore name = __SEMAPHORE_INITIALIZER(name, 1)

अटल अंतरभूत व्योम sema_init(काष्ठा semaphore *sem, पूर्णांक val)
अणु
	अटल काष्ठा lock_class_key __key;
	*sem = (काष्ठा semaphore) __SEMAPHORE_INITIALIZER(*sem, val);
	lockdep_init_map(&sem->lock.dep_map, "semaphore->lock", &__key, 0);
पूर्ण

बाह्य व्योम करोwn(काष्ठा semaphore *sem);
बाह्य पूर्णांक __must_check करोwn_पूर्णांकerruptible(काष्ठा semaphore *sem);
बाह्य पूर्णांक __must_check करोwn_समाप्तable(काष्ठा semaphore *sem);
बाह्य पूर्णांक __must_check करोwn_trylock(काष्ठा semaphore *sem);
बाह्य पूर्णांक __must_check करोwn_समयout(काष्ठा semaphore *sem, दीर्घ jअगरfies);
बाह्य व्योम up(काष्ठा semaphore *sem);

#पूर्ण_अगर /* __LINUX_SEMAPHORE_H */
