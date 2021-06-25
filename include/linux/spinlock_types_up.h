<शैली गुरु>
#अगर_अघोषित __LINUX_SPINLOCK_TYPES_UP_H
#घोषणा __LINUX_SPINLOCK_TYPES_UP_H

#अगर_अघोषित __LINUX_SPINLOCK_TYPES_H
# error "please don't include this file directly"
#पूर्ण_अगर

/*
 * include/linux/spinlock_types_up.h - spinlock type definitions क्रम UP
 *
 * portions Copyright 2005, Red Hat, Inc., Ingo Molnar
 * Released under the General Public License (GPL).
 */

#अगर_घोषित CONFIG_DEBUG_SPINLOCK

प्रकार काष्ठा अणु
	अस्थिर अचिन्हित पूर्णांक slock;
पूर्ण arch_spinlock_t;

#घोषणा __ARCH_SPIN_LOCK_UNLOCKED अणु 1 पूर्ण

#अन्यथा

प्रकार काष्ठा अणु पूर्ण arch_spinlock_t;

#घोषणा __ARCH_SPIN_LOCK_UNLOCKED अणु पूर्ण

#पूर्ण_अगर

प्रकार काष्ठा अणु
	/* no debug version on UP */
पूर्ण arch_rwlock_t;

#घोषणा __ARCH_RW_LOCK_UNLOCKED अणु पूर्ण

#पूर्ण_अगर /* __LINUX_SPINLOCK_TYPES_UP_H */
