<शैली गुरु>
#अगर_अघोषित __LINUX_SPINLOCK_TYPES_H
#घोषणा __LINUX_SPINLOCK_TYPES_H

/*
 * include/linux/spinlock_types.h - generic spinlock type definitions
 *                                  and initializers
 *
 * portions Copyright 2005, Red Hat, Inc., Ingo Molnar
 * Released under the General Public License (GPL).
 */

#अगर defined(CONFIG_SMP)
# include <यंत्र/spinlock_types.h>
#अन्यथा
# include <linux/spinlock_types_up.h>
#पूर्ण_अगर

#समावेश <linux/lockdep_types.h>

प्रकार काष्ठा raw_spinlock अणु
	arch_spinlock_t raw_lock;
#अगर_घोषित CONFIG_DEBUG_SPINLOCK
	अचिन्हित पूर्णांक magic, owner_cpu;
	व्योम *owner;
#पूर्ण_अगर
#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC
	काष्ठा lockdep_map dep_map;
#पूर्ण_अगर
पूर्ण raw_spinlock_t;

#घोषणा SPINLOCK_MAGIC		0xdead4ead

#घोषणा SPINLOCK_OWNER_INIT	((व्योम *)-1L)

#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC
# define RAW_SPIN_DEP_MAP_INIT(lockname)		\
	.dep_map = अणु					\
		.name = #lockname,			\
		.रुको_type_inner = LD_WAIT_SPIN,	\
	पूर्ण
# define SPIN_DEP_MAP_INIT(lockname)			\
	.dep_map = अणु					\
		.name = #lockname,			\
		.रुको_type_inner = LD_WAIT_CONFIG,	\
	पूर्ण
#अन्यथा
# define RAW_SPIN_DEP_MAP_INIT(lockname)
# define SPIN_DEP_MAP_INIT(lockname)
#पूर्ण_अगर

#अगर_घोषित CONFIG_DEBUG_SPINLOCK
# define SPIN_DEBUG_INIT(lockname)		\
	.magic = SPINLOCK_MAGIC,		\
	.owner_cpu = -1,			\
	.owner = SPINLOCK_OWNER_INIT,
#अन्यथा
# define SPIN_DEBUG_INIT(lockname)
#पूर्ण_अगर

#घोषणा __RAW_SPIN_LOCK_INITIALIZER(lockname)	\
	अणु					\
	.raw_lock = __ARCH_SPIN_LOCK_UNLOCKED,	\
	SPIN_DEBUG_INIT(lockname)		\
	RAW_SPIN_DEP_MAP_INIT(lockname) पूर्ण

#घोषणा __RAW_SPIN_LOCK_UNLOCKED(lockname)	\
	(raw_spinlock_t) __RAW_SPIN_LOCK_INITIALIZER(lockname)

#घोषणा DEFINE_RAW_SPINLOCK(x)	raw_spinlock_t x = __RAW_SPIN_LOCK_UNLOCKED(x)

प्रकार काष्ठा spinlock अणु
	जोड़ अणु
		काष्ठा raw_spinlock rlock;

#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC
# define LOCK_PADSIZE (दुरत्व(काष्ठा raw_spinlock, dep_map))
		काष्ठा अणु
			u8 __padding[LOCK_PADSIZE];
			काष्ठा lockdep_map dep_map;
		पूर्ण;
#पूर्ण_अगर
	पूर्ण;
पूर्ण spinlock_t;

#घोषणा ___SPIN_LOCK_INITIALIZER(lockname)	\
	अणु					\
	.raw_lock = __ARCH_SPIN_LOCK_UNLOCKED,	\
	SPIN_DEBUG_INIT(lockname)		\
	SPIN_DEP_MAP_INIT(lockname) पूर्ण

#घोषणा __SPIN_LOCK_INITIALIZER(lockname) \
	अणु अणु .rlock = ___SPIN_LOCK_INITIALIZER(lockname) पूर्ण पूर्ण

#घोषणा __SPIN_LOCK_UNLOCKED(lockname) \
	(spinlock_t) __SPIN_LOCK_INITIALIZER(lockname)

#घोषणा DEFINE_SPINLOCK(x)	spinlock_t x = __SPIN_LOCK_UNLOCKED(x)

#समावेश <linux/rwlock_types.h>

#पूर्ण_अगर /* __LINUX_SPINLOCK_TYPES_H */
