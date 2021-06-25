<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012 ARM Ltd.
 */
#अगर_अघोषित __ASM_SPINLOCK_H
#घोषणा __ASM_SPINLOCK_H

#समावेश <यंत्र/qspinlock.h>
#समावेश <यंत्र/qrwlock.h>

/* See include/linux/spinlock.h */
#घोषणा smp_mb__after_spinlock()	smp_mb()

/*
 * Changing this will अवरोध osq_lock() thanks to the call inside
 * smp_cond_load_relaxed().
 *
 * See:
 * https://lore.kernel.org/lkml/20200110100612.GC2827@hirez.programming.kicks-ass.net
 */
#घोषणा vcpu_is_preempted vcpu_is_preempted
अटल अंतरभूत bool vcpu_is_preempted(पूर्णांक cpu)
अणु
	वापस false;
पूर्ण

#पूर्ण_अगर /* __ASM_SPINLOCK_H */
