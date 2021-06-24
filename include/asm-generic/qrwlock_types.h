<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_GENERIC_QRWLOCK_TYPES_H
#घोषणा __ASM_GENERIC_QRWLOCK_TYPES_H

#समावेश <linux/types.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/spinlock_types.h>

/*
 * The queue पढ़ो/ग_लिखो lock data काष्ठाure
 */

प्रकार काष्ठा qrwlock अणु
	जोड़ अणु
		atomic_t cnts;
		काष्ठा अणु
#अगर_घोषित __LITTLE_ENDIAN
			u8 wlocked;	/* Locked क्रम ग_लिखो? */
			u8 __lstate[3];
#अन्यथा
			u8 __lstate[3];
			u8 wlocked;	/* Locked क्रम ग_लिखो? */
#पूर्ण_अगर
		पूर्ण;
	पूर्ण;
	arch_spinlock_t		रुको_lock;
पूर्ण arch_rwlock_t;

#घोषणा	__ARCH_RW_LOCK_UNLOCKED अणु		\
	अणु .cnts = ATOMIC_INIT(0), पूर्ण,		\
	.रुको_lock = __ARCH_SPIN_LOCK_UNLOCKED,	\
पूर्ण

#पूर्ण_अगर /* __ASM_GENERIC_QRWLOCK_TYPES_H */
