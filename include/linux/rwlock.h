<शैली गुरु>
#अगर_अघोषित __LINUX_RWLOCK_H
#घोषणा __LINUX_RWLOCK_H

#अगर_अघोषित __LINUX_SPINLOCK_H
# error "please don't include this file directly"
#पूर्ण_अगर

/*
 * rwlock related methods
 *
 * split out from spinlock.h
 *
 * portions Copyright 2005, Red Hat, Inc., Ingo Molnar
 * Released under the General Public License (GPL).
 */

#अगर_घोषित CONFIG_DEBUG_SPINLOCK
  बाह्य व्योम __rwlock_init(rwlock_t *lock, स्थिर अक्षर *name,
			    काष्ठा lock_class_key *key);
# define rwlock_init(lock)					\
करो अणु								\
	अटल काष्ठा lock_class_key __key;			\
								\
	__rwlock_init((lock), #lock, &__key);			\
पूर्ण जबतक (0)
#अन्यथा
# define rwlock_init(lock)					\
	करो अणु *(lock) = __RW_LOCK_UNLOCKED(lock); पूर्ण जबतक (0)
#पूर्ण_अगर

#अगर_घोषित CONFIG_DEBUG_SPINLOCK
 बाह्य व्योम करो_raw_पढ़ो_lock(rwlock_t *lock) __acquires(lock);
#घोषणा करो_raw_पढ़ो_lock_flags(lock, flags) करो_raw_पढ़ो_lock(lock)
 बाह्य पूर्णांक करो_raw_पढ़ो_trylock(rwlock_t *lock);
 बाह्य व्योम करो_raw_पढ़ो_unlock(rwlock_t *lock) __releases(lock);
 बाह्य व्योम करो_raw_ग_लिखो_lock(rwlock_t *lock) __acquires(lock);
#घोषणा करो_raw_ग_लिखो_lock_flags(lock, flags) करो_raw_ग_लिखो_lock(lock)
 बाह्य पूर्णांक करो_raw_ग_लिखो_trylock(rwlock_t *lock);
 बाह्य व्योम करो_raw_ग_लिखो_unlock(rwlock_t *lock) __releases(lock);
#अन्यथा

#अगर_अघोषित arch_पढ़ो_lock_flags
# define arch_पढ़ो_lock_flags(lock, flags)	arch_पढ़ो_lock(lock)
#पूर्ण_अगर

#अगर_अघोषित arch_ग_लिखो_lock_flags
# define arch_ग_लिखो_lock_flags(lock, flags)	arch_ग_लिखो_lock(lock)
#पूर्ण_अगर

# define करो_raw_पढ़ो_lock(rwlock)	करो अणु__acquire(lock); arch_पढ़ो_lock(&(rwlock)->raw_lock); पूर्ण जबतक (0)
# define करो_raw_पढ़ो_lock_flags(lock, flags) \
		करो अणु__acquire(lock); arch_पढ़ो_lock_flags(&(lock)->raw_lock, *(flags)); पूर्ण जबतक (0)
# define करो_raw_पढ़ो_trylock(rwlock)	arch_पढ़ो_trylock(&(rwlock)->raw_lock)
# define करो_raw_पढ़ो_unlock(rwlock)	करो अणुarch_पढ़ो_unlock(&(rwlock)->raw_lock); __release(lock); पूर्ण जबतक (0)
# define करो_raw_ग_लिखो_lock(rwlock)	करो अणु__acquire(lock); arch_ग_लिखो_lock(&(rwlock)->raw_lock); पूर्ण जबतक (0)
# define करो_raw_ग_लिखो_lock_flags(lock, flags) \
		करो अणु__acquire(lock); arch_ग_लिखो_lock_flags(&(lock)->raw_lock, *(flags)); पूर्ण जबतक (0)
# define करो_raw_ग_लिखो_trylock(rwlock)	arch_ग_लिखो_trylock(&(rwlock)->raw_lock)
# define करो_raw_ग_लिखो_unlock(rwlock)	करो अणुarch_ग_लिखो_unlock(&(rwlock)->raw_lock); __release(lock); पूर्ण जबतक (0)
#पूर्ण_अगर

/*
 * Define the various rw_lock methods.  Note we define these
 * regardless of whether CONFIG_SMP or CONFIG_PREEMPT are set. The various
 * methods are defined as nops in the हाल they are not required.
 */
#घोषणा पढ़ो_trylock(lock)	__cond_lock(lock, _raw_पढ़ो_trylock(lock))
#घोषणा ग_लिखो_trylock(lock)	__cond_lock(lock, _raw_ग_लिखो_trylock(lock))

#घोषणा ग_लिखो_lock(lock)	_raw_ग_लिखो_lock(lock)
#घोषणा पढ़ो_lock(lock)		_raw_पढ़ो_lock(lock)

#अगर defined(CONFIG_SMP) || defined(CONFIG_DEBUG_SPINLOCK)

#घोषणा पढ़ो_lock_irqsave(lock, flags)			\
	करो अणु						\
		typecheck(अचिन्हित दीर्घ, flags);	\
		flags = _raw_पढ़ो_lock_irqsave(lock);	\
	पूर्ण जबतक (0)
#घोषणा ग_लिखो_lock_irqsave(lock, flags)			\
	करो अणु						\
		typecheck(अचिन्हित दीर्घ, flags);	\
		flags = _raw_ग_लिखो_lock_irqsave(lock);	\
	पूर्ण जबतक (0)

#अन्यथा

#घोषणा पढ़ो_lock_irqsave(lock, flags)			\
	करो अणु						\
		typecheck(अचिन्हित दीर्घ, flags);	\
		_raw_पढ़ो_lock_irqsave(lock, flags);	\
	पूर्ण जबतक (0)
#घोषणा ग_लिखो_lock_irqsave(lock, flags)			\
	करो अणु						\
		typecheck(अचिन्हित दीर्घ, flags);	\
		_raw_ग_लिखो_lock_irqsave(lock, flags);	\
	पूर्ण जबतक (0)

#पूर्ण_अगर

#घोषणा पढ़ो_lock_irq(lock)		_raw_पढ़ो_lock_irq(lock)
#घोषणा पढ़ो_lock_bh(lock)		_raw_पढ़ो_lock_bh(lock)
#घोषणा ग_लिखो_lock_irq(lock)		_raw_ग_लिखो_lock_irq(lock)
#घोषणा ग_लिखो_lock_bh(lock)		_raw_ग_लिखो_lock_bh(lock)
#घोषणा पढ़ो_unlock(lock)		_raw_पढ़ो_unlock(lock)
#घोषणा ग_लिखो_unlock(lock)		_raw_ग_लिखो_unlock(lock)
#घोषणा पढ़ो_unlock_irq(lock)		_raw_पढ़ो_unlock_irq(lock)
#घोषणा ग_लिखो_unlock_irq(lock)		_raw_ग_लिखो_unlock_irq(lock)

#घोषणा पढ़ो_unlock_irqrestore(lock, flags)			\
	करो अणु							\
		typecheck(अचिन्हित दीर्घ, flags);		\
		_raw_पढ़ो_unlock_irqrestore(lock, flags);	\
	पूर्ण जबतक (0)
#घोषणा पढ़ो_unlock_bh(lock)		_raw_पढ़ो_unlock_bh(lock)

#घोषणा ग_लिखो_unlock_irqrestore(lock, flags)		\
	करो अणु						\
		typecheck(अचिन्हित दीर्घ, flags);	\
		_raw_ग_लिखो_unlock_irqrestore(lock, flags);	\
	पूर्ण जबतक (0)
#घोषणा ग_लिखो_unlock_bh(lock)		_raw_ग_लिखो_unlock_bh(lock)

#घोषणा ग_लिखो_trylock_irqsave(lock, flags) \
(अणु \
	local_irq_save(flags); \
	ग_लिखो_trylock(lock) ? \
	1 : (अणु local_irq_restore(flags); 0; पूर्ण); \
पूर्ण)

#अगर_घोषित arch_rwlock_is_contended
#घोषणा rwlock_is_contended(lock) \
	 arch_rwlock_is_contended(&(lock)->raw_lock)
#अन्यथा
#घोषणा rwlock_is_contended(lock)	((व्योम)(lock), 0)
#पूर्ण_अगर /* arch_rwlock_is_contended */

#पूर्ण_अगर /* __LINUX_RWLOCK_H */
