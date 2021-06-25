<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SPINLOCK_TYPES_H
#घोषणा __ASM_SPINLOCK_TYPES_H

#अगर_अघोषित __LINUX_SPINLOCK_TYPES_H
# error "please don't include this file directly"
#पूर्ण_अगर

प्रकार काष्ठा अणु
	पूर्णांक lock;
पूर्ण arch_spinlock_t;

#घोषणा __ARCH_SPIN_LOCK_UNLOCKED अणु .lock = 0, पूर्ण

प्रकार काष्ठा अणु
	पूर्णांक cnts;
	arch_spinlock_t रुको;
पूर्ण arch_rwlock_t;

#घोषणा __ARCH_RW_LOCK_UNLOCKED		अणु 0 पूर्ण

#पूर्ण_अगर
