<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_LOCKREF_H
#घोषणा __LINUX_LOCKREF_H

/*
 * Locked reference counts.
 *
 * These are dअगरferent from just plain atomic refcounts in that they
 * are atomic with respect to the spinlock that goes with them.  In
 * particular, there can be implementations that करोn't actually get
 * the spinlock क्रम the common decrement/increment operations, but they
 * still have to check that the operation is करोne semantically as अगर
 * the spinlock had been taken (using a cmpxchg operation that covers
 * both the lock and the count word, or using memory transactions, क्रम
 * example).
 */

#समावेश <linux/spinlock.h>
#समावेश <generated/bounds.h>

#घोषणा USE_CMPXCHG_LOCKREF \
	(IS_ENABLED(CONFIG_ARCH_USE_CMPXCHG_LOCKREF) && \
	 IS_ENABLED(CONFIG_SMP) && SPINLOCK_SIZE <= 4)

काष्ठा lockref अणु
	जोड़ अणु
#अगर USE_CMPXCHG_LOCKREF
		aligned_u64 lock_count;
#पूर्ण_अगर
		काष्ठा अणु
			spinlock_t lock;
			पूर्णांक count;
		पूर्ण;
	पूर्ण;
पूर्ण;

बाह्य व्योम lockref_get(काष्ठा lockref *);
बाह्य पूर्णांक lockref_put_वापस(काष्ठा lockref *);
बाह्य पूर्णांक lockref_get_not_zero(काष्ठा lockref *);
बाह्य पूर्णांक lockref_put_not_zero(काष्ठा lockref *);
बाह्य पूर्णांक lockref_get_or_lock(काष्ठा lockref *);
बाह्य पूर्णांक lockref_put_or_lock(काष्ठा lockref *);

बाह्य व्योम lockref_mark_dead(काष्ठा lockref *);
बाह्य पूर्णांक lockref_get_not_dead(काष्ठा lockref *);

/* Must be called under spinlock क्रम reliable results */
अटल अंतरभूत bool __lockref_is_dead(स्थिर काष्ठा lockref *l)
अणु
	वापस ((पूर्णांक)l->count < 0);
पूर्ण

#पूर्ण_अगर /* __LINUX_LOCKREF_H */
