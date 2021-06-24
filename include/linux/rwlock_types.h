<शैली गुरु>
#अगर_अघोषित __LINUX_RWLOCK_TYPES_H
#घोषणा __LINUX_RWLOCK_TYPES_H

/*
 * include/linux/rwlock_types.h - generic rwlock type definitions
 *				  and initializers
 *
 * portions Copyright 2005, Red Hat, Inc., Ingo Molnar
 * Released under the General Public License (GPL).
 */
प्रकार काष्ठा अणु
	arch_rwlock_t raw_lock;
#अगर_घोषित CONFIG_DEBUG_SPINLOCK
	अचिन्हित पूर्णांक magic, owner_cpu;
	व्योम *owner;
#पूर्ण_अगर
#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC
	काष्ठा lockdep_map dep_map;
#पूर्ण_अगर
पूर्ण rwlock_t;

#घोषणा RWLOCK_MAGIC		0xdeaf1eed

#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC
# define RW_DEP_MAP_INIT(lockname)					\
	.dep_map = अणु							\
		.name = #lockname,					\
		.रुको_type_inner = LD_WAIT_CONFIG,			\
	पूर्ण
#अन्यथा
# define RW_DEP_MAP_INIT(lockname)
#पूर्ण_अगर

#अगर_घोषित CONFIG_DEBUG_SPINLOCK
#घोषणा __RW_LOCK_UNLOCKED(lockname)					\
	(rwlock_t)	अणु	.raw_lock = __ARCH_RW_LOCK_UNLOCKED,	\
				.magic = RWLOCK_MAGIC,			\
				.owner = SPINLOCK_OWNER_INIT,		\
				.owner_cpu = -1,			\
				RW_DEP_MAP_INIT(lockname) पूर्ण
#अन्यथा
#घोषणा __RW_LOCK_UNLOCKED(lockname) \
	(rwlock_t)	अणु	.raw_lock = __ARCH_RW_LOCK_UNLOCKED,	\
				RW_DEP_MAP_INIT(lockname) पूर्ण
#पूर्ण_अगर

#घोषणा DEFINE_RWLOCK(x)	rwlock_t x = __RW_LOCK_UNLOCKED(x)

#पूर्ण_अगर /* __LINUX_RWLOCK_TYPES_H */
