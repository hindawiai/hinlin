<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SPINLOCK_TYPES_H
#घोषणा __ASM_SPINLOCK_TYPES_H

#अगर_अघोषित __LINUX_SPINLOCK_TYPES_H
# error "please don't include this file directly"
#पूर्ण_अगर

#घोषणा TICKET_SHIFT	16

प्रकार काष्ठा अणु
	जोड़ अणु
		u32 slock;
		काष्ठा __raw_tickets अणु
#अगर_घोषित __ARMEB__
			u16 next;
			u16 owner;
#अन्यथा
			u16 owner;
			u16 next;
#पूर्ण_अगर
		पूर्ण tickets;
	पूर्ण;
पूर्ण arch_spinlock_t;

#घोषणा __ARCH_SPIN_LOCK_UNLOCKED	अणु अणु 0 पूर्ण पूर्ण

प्रकार काष्ठा अणु
	u32 lock;
पूर्ण arch_rwlock_t;

#घोषणा __ARCH_RW_LOCK_UNLOCKED		अणु 0 पूर्ण

#पूर्ण_अगर
