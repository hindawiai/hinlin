<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Queued spinlock
 *
 * (C) Copyright 2013-2015 Hewlett-Packard Development Company, L.P.
 *
 * Authors: Waiman Long <waiman.दीर्घ@hp.com>
 */
#अगर_अघोषित __ASM_GENERIC_QSPINLOCK_TYPES_H
#घोषणा __ASM_GENERIC_QSPINLOCK_TYPES_H

#समावेश <linux/types.h>

प्रकार काष्ठा qspinlock अणु
	जोड़ अणु
		atomic_t val;

		/*
		 * By using the whole 2nd least signअगरicant byte क्रम the
		 * pending bit, we can allow better optimization of the lock
		 * acquisition क्रम the pending bit holder.
		 */
#अगर_घोषित __LITTLE_ENDIAN
		काष्ठा अणु
			u8	locked;
			u8	pending;
		पूर्ण;
		काष्ठा अणु
			u16	locked_pending;
			u16	tail;
		पूर्ण;
#अन्यथा
		काष्ठा अणु
			u16	tail;
			u16	locked_pending;
		पूर्ण;
		काष्ठा अणु
			u8	reserved[2];
			u8	pending;
			u8	locked;
		पूर्ण;
#पूर्ण_अगर
	पूर्ण;
पूर्ण arch_spinlock_t;

/*
 * Initializier
 */
#घोषणा	__ARCH_SPIN_LOCK_UNLOCKED	अणु अणु .val = ATOMIC_INIT(0) पूर्ण पूर्ण

/*
 * Bitfields in the atomic value:
 *
 * When NR_CPUS < 16K
 *  0- 7: locked byte
 *     8: pending
 *  9-15: not used
 * 16-17: tail index
 * 18-31: tail cpu (+1)
 *
 * When NR_CPUS >= 16K
 *  0- 7: locked byte
 *     8: pending
 *  9-10: tail index
 * 11-31: tail cpu (+1)
 */
#घोषणा	_Q_SET_MASK(type)	(((1U << _Q_ ## type ## _BITS) - 1)\
				      << _Q_ ## type ## _OFFSET)
#घोषणा _Q_LOCKED_OFFSET	0
#घोषणा _Q_LOCKED_BITS		8
#घोषणा _Q_LOCKED_MASK		_Q_SET_MASK(LOCKED)

#घोषणा _Q_PENDING_OFFSET	(_Q_LOCKED_OFFSET + _Q_LOCKED_BITS)
#अगर CONFIG_NR_CPUS < (1U << 14)
#घोषणा _Q_PENDING_BITS		8
#अन्यथा
#घोषणा _Q_PENDING_BITS		1
#पूर्ण_अगर
#घोषणा _Q_PENDING_MASK		_Q_SET_MASK(PENDING)

#घोषणा _Q_TAIL_IDX_OFFSET	(_Q_PENDING_OFFSET + _Q_PENDING_BITS)
#घोषणा _Q_TAIL_IDX_BITS	2
#घोषणा _Q_TAIL_IDX_MASK	_Q_SET_MASK(TAIL_IDX)

#घोषणा _Q_TAIL_CPU_OFFSET	(_Q_TAIL_IDX_OFFSET + _Q_TAIL_IDX_BITS)
#घोषणा _Q_TAIL_CPU_BITS	(32 - _Q_TAIL_CPU_OFFSET)
#घोषणा _Q_TAIL_CPU_MASK	_Q_SET_MASK(TAIL_CPU)

#घोषणा _Q_TAIL_OFFSET		_Q_TAIL_IDX_OFFSET
#घोषणा _Q_TAIL_MASK		(_Q_TAIL_IDX_MASK | _Q_TAIL_CPU_MASK)

#घोषणा _Q_LOCKED_VAL		(1U << _Q_LOCKED_OFFSET)
#घोषणा _Q_PENDING_VAL		(1U << _Q_PENDING_OFFSET)

#पूर्ण_अगर /* __ASM_GENERIC_QSPINLOCK_TYPES_H */
