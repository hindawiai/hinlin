<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __ASM_CSKY_SPINLOCK_TYPES_H
#घोषणा __ASM_CSKY_SPINLOCK_TYPES_H

#अगर_अघोषित __LINUX_SPINLOCK_TYPES_H
# error "please don't include this file directly"
#पूर्ण_अगर

#घोषणा TICKET_NEXT	16

प्रकार काष्ठा अणु
	जोड़ अणु
		u32 lock;
		काष्ठा __raw_tickets अणु
			/* little endian */
			u16 owner;
			u16 next;
		पूर्ण tickets;
	पूर्ण;
पूर्ण arch_spinlock_t;

#घोषणा __ARCH_SPIN_LOCK_UNLOCKED	अणु अणु 0 पूर्ण पूर्ण

#समावेश <यंत्र-generic/qrwlock_types.h>

#पूर्ण_अगर /* __ASM_CSKY_SPINLOCK_TYPES_H */
