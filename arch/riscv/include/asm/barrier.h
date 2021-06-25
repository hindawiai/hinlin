<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Based on arch/arm/include/यंत्र/barrier.h
 *
 * Copyright (C) 2012 ARM Ltd.
 * Copyright (C) 2013 Regents of the University of Calअगरornia
 * Copyright (C) 2017 SiFive
 */

#अगर_अघोषित _ASM_RISCV_BARRIER_H
#घोषणा _ASM_RISCV_BARRIER_H

#अगर_अघोषित __ASSEMBLY__

#घोषणा nop()		__यंत्र__ __अस्थिर__ ("nop")

#घोषणा RISCV_FENCE(p, s) \
	__यंत्र__ __अस्थिर__ ("fence " #p "," #s : : : "memory")

/* These barriers need to enक्रमce ordering on both devices or memory. */
#घोषणा mb()		RISCV_FENCE(iorw,iorw)
#घोषणा rmb()		RISCV_FENCE(ir,ir)
#घोषणा wmb()		RISCV_FENCE(ow,ow)

/* These barriers करो not need to enक्रमce ordering on devices, just memory. */
#घोषणा __smp_mb()	RISCV_FENCE(rw,rw)
#घोषणा __smp_rmb()	RISCV_FENCE(r,r)
#घोषणा __smp_wmb()	RISCV_FENCE(w,w)

#घोषणा __smp_store_release(p, v)					\
करो अणु									\
	compileसमय_निश्चित_atomic_type(*p);				\
	RISCV_FENCE(rw,w);						\
	WRITE_ONCE(*p, v);						\
पूर्ण जबतक (0)

#घोषणा __smp_load_acquire(p)						\
(अणु									\
	typeof(*p) ___p1 = READ_ONCE(*p);				\
	compileसमय_निश्चित_atomic_type(*p);				\
	RISCV_FENCE(r,rw);						\
	___p1;								\
पूर्ण)

/*
 * This is a very specअगरic barrier: it's currently only used in two places in
 * the kernel, both in the scheduler.  See include/linux/spinlock.h क्रम the two
 * orderings it guarantees, but the "critical section is RCsc" guarantee
 * mandates a barrier on RISC-V.  The sequence looks like:
 *
 *    lr.aq lock
 *    sc    lock <= LOCKED
 *    smp_mb__after_spinlock()
 *    // critical section
 *    lr    lock
 *    sc.rl lock <= UNLOCKED
 *
 * The AQ/RL pair provides a RCpc critical section, but there's not really any
 * way we can take advantage of that here because the ordering is only enक्रमced
 * on that one lock.  Thus, we're just करोing a full fence.
 *
 * Since we allow ग_लिखोX to be called from preemptive regions we need at least
 * an "o" in the predecessor set to ensure device ग_लिखोs are visible beक्रमe the
 * task is marked as available क्रम scheduling on a new hart.  While I करोn't see
 * any concrete reason we need a full IO fence, it seems safer to just upgrade
 * this in order to aव्योम any IO crossing a scheduling boundary.  In both
 * instances the scheduler pairs this with an mb(), so nothing is necessary on
 * the new hart.
 */
#घोषणा smp_mb__after_spinlock()	RISCV_FENCE(iorw,iorw)

#समावेश <यंत्र-generic/barrier.h>

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* _ASM_RISCV_BARRIER_H */
