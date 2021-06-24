<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_SPINLOCK_H
#घोषणा _ASM_X86_SPINLOCK_H

#समावेश <linux/jump_label.h>
#समावेश <linux/atomic.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/processor.h>
#समावेश <linux/compiler.h>
#समावेश <यंत्र/paravirt.h>
#समावेश <यंत्र/bitops.h>

/*
 * Your basic SMP spinlocks, allowing only a single CPU anywhere
 *
 * Simple spin lock operations.  There are two variants, one clears IRQ's
 * on the local processor, one करोes not.
 *
 * These are fair FIFO ticket locks, which support up to 2^16 CPUs.
 *
 * (the type definitions are in यंत्र/spinlock_types.h)
 */

/* How दीर्घ a lock should spin beक्रमe we consider blocking */
#घोषणा SPIN_THRESHOLD	(1 << 15)

#समावेश <यंत्र/qspinlock.h>

/*
 * Read-ग_लिखो spinlocks, allowing multiple पढ़ोers
 * but only one ग_लिखोr.
 *
 * NOTE! it is quite common to have पढ़ोers in पूर्णांकerrupts
 * but no पूर्णांकerrupt ग_लिखोrs. For those circumstances we
 * can "mix" irq-safe locks - any ग_लिखोr needs to get a
 * irq-safe ग_लिखो-lock, but पढ़ोers can get non-irqsafe
 * पढ़ो-locks.
 *
 * On x86, we implement पढ़ो-ग_लिखो locks using the generic qrwlock with
 * x86 specअगरic optimization.
 */

#समावेश <यंत्र/qrwlock.h>

#पूर्ण_अगर /* _ASM_X86_SPINLOCK_H */
