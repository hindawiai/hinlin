<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1999, 2000, 06 Ralf Baechle (ralf@linux-mips.org)
 * Copyright (C) 1999, 2000 Silicon Graphics, Inc.
 */
#अगर_अघोषित _ASM_SPINLOCK_H
#घोषणा _ASM_SPINLOCK_H

#समावेश <यंत्र/processor.h>

#समावेश <यंत्र-generic/qspinlock_types.h>

#घोषणा	queued_spin_unlock queued_spin_unlock
/**
 * queued_spin_unlock - release a queued spinlock
 * @lock : Poपूर्णांकer to queued spinlock काष्ठाure
 */
अटल अंतरभूत व्योम queued_spin_unlock(काष्ठा qspinlock *lock)
अणु
	/* This could be optimised with ARCH_HAS_MMIOWB */
	mmiowb();
	smp_store_release(&lock->locked, 0);
पूर्ण

#समावेश <यंत्र/qspinlock.h>
#समावेश <यंत्र/qrwlock.h>

#पूर्ण_अगर /* _ASM_SPINLOCK_H */
