<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_LOCAL_LOCK_H
# error "Do not include directly, include linux/local_lock.h"
#पूर्ण_अगर

#समावेश <linux/percpu-defs.h>
#समावेश <linux/lockdep.h>

प्रकार काष्ठा अणु
#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC
	काष्ठा lockdep_map	dep_map;
	काष्ठा task_काष्ठा	*owner;
#पूर्ण_अगर
पूर्ण local_lock_t;

#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC
# define LL_DEP_MAP_INIT(lockname)			\
	.dep_map = अणु					\
		.name = #lockname,			\
		.रुको_type_inner = LD_WAIT_CONFIG,	\
		.lock_type = LD_LOCK_PERCPU,			\
	पूर्ण
#अन्यथा
# define LL_DEP_MAP_INIT(lockname)
#पूर्ण_अगर

#घोषणा INIT_LOCAL_LOCK(lockname)	अणु LL_DEP_MAP_INIT(lockname) पूर्ण

#घोषणा __local_lock_init(lock)					\
करो अणु								\
	अटल काष्ठा lock_class_key __key;			\
								\
	debug_check_no_locks_मुक्तd((व्योम *)lock, माप(*lock));\
	lockdep_init_map_type(&(lock)->dep_map, #lock, &__key, 0, \
			      LD_WAIT_CONFIG, LD_WAIT_INV,	\
			      LD_LOCK_PERCPU);			\
पूर्ण जबतक (0)

#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC
अटल अंतरभूत व्योम local_lock_acquire(local_lock_t *l)
अणु
	lock_map_acquire(&l->dep_map);
	DEBUG_LOCKS_WARN_ON(l->owner);
	l->owner = current;
पूर्ण

अटल अंतरभूत व्योम local_lock_release(local_lock_t *l)
अणु
	DEBUG_LOCKS_WARN_ON(l->owner != current);
	l->owner = शून्य;
	lock_map_release(&l->dep_map);
पूर्ण

#अन्यथा /* CONFIG_DEBUG_LOCK_ALLOC */
अटल अंतरभूत व्योम local_lock_acquire(local_lock_t *l) अणु पूर्ण
अटल अंतरभूत व्योम local_lock_release(local_lock_t *l) अणु पूर्ण
#पूर्ण_अगर /* !CONFIG_DEBUG_LOCK_ALLOC */

#घोषणा __local_lock(lock)					\
	करो अणु							\
		preempt_disable();				\
		local_lock_acquire(this_cpu_ptr(lock));		\
	पूर्ण जबतक (0)

#घोषणा __local_lock_irq(lock)					\
	करो अणु							\
		local_irq_disable();				\
		local_lock_acquire(this_cpu_ptr(lock));		\
	पूर्ण जबतक (0)

#घोषणा __local_lock_irqsave(lock, flags)			\
	करो अणु							\
		local_irq_save(flags);				\
		local_lock_acquire(this_cpu_ptr(lock));		\
	पूर्ण जबतक (0)

#घोषणा __local_unlock(lock)					\
	करो अणु							\
		local_lock_release(this_cpu_ptr(lock));		\
		preempt_enable();				\
	पूर्ण जबतक (0)

#घोषणा __local_unlock_irq(lock)				\
	करो अणु							\
		local_lock_release(this_cpu_ptr(lock));		\
		local_irq_enable();				\
	पूर्ण जबतक (0)

#घोषणा __local_unlock_irqrestore(lock, flags)			\
	करो अणु							\
		local_lock_release(this_cpu_ptr(lock));		\
		local_irq_restore(flags);			\
	पूर्ण जबतक (0)
