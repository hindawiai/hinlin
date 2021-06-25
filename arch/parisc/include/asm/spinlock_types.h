<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SPINLOCK_TYPES_H
#घोषणा __ASM_SPINLOCK_TYPES_H

प्रकार काष्ठा अणु
#अगर_घोषित CONFIG_PA20
	अस्थिर अचिन्हित पूर्णांक slock;
# define __ARCH_SPIN_LOCK_UNLOCKED अणु 1 पूर्ण
#अन्यथा
	अस्थिर अचिन्हित पूर्णांक lock[4];
# define __ARCH_SPIN_LOCK_UNLOCKED	अणु अणु 1, 1, 1, 1 पूर्ण पूर्ण
#पूर्ण_अगर
पूर्ण arch_spinlock_t;


/* counter:
 * Unlocked     : 0x0100_0000
 * Read lock(s) : 0x00FF_FFFF to 0x01  (Multiple Readers decrement it)
 * Write lock   : 0x0, but only अगर prior value is "unlocked" 0x0100_0000
 */
प्रकार काष्ठा अणु
	arch_spinlock_t		lock_mutex;
	अस्थिर अचिन्हित पूर्णांक	counter;
पूर्ण arch_rwlock_t;

#घोषणा __ARCH_RW_LOCK_UNLOCKED__       0x01000000
#घोषणा __ARCH_RW_LOCK_UNLOCKED         अणु .lock_mutex = __ARCH_SPIN_LOCK_UNLOCKED, \
					.counter = __ARCH_RW_LOCK_UNLOCKED__ पूर्ण

#पूर्ण_अगर
