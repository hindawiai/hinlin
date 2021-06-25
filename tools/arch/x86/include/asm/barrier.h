<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _TOOLS_LINUX_ASM_X86_BARRIER_H
#घोषणा _TOOLS_LINUX_ASM_X86_BARRIER_H

/*
 * Copied from the Linux kernel sources, and also moving code
 * out from tools/perf/perf-sys.h so as to make it be located
 * in a place similar as in the kernel sources.
 *
 * Force strict CPU ordering.
 * And yes, this is required on UP too when we're talking
 * to devices.
 */

#अगर defined(__i386__)
/*
 * Some non-Intel clones support out of order store. wmb() ceases to be a
 * nop क्रम these.
 */
#घोषणा mb()	यंत्र अस्थिर("lock; addl $0,0(%%esp)" ::: "memory")
#घोषणा rmb()	यंत्र अस्थिर("lock; addl $0,0(%%esp)" ::: "memory")
#घोषणा wmb()	यंत्र अस्थिर("lock; addl $0,0(%%esp)" ::: "memory")
#या_अगर defined(__x86_64__)
#घोषणा mb()	यंत्र अस्थिर("mfence" ::: "memory")
#घोषणा rmb()	यंत्र अस्थिर("lfence" ::: "memory")
#घोषणा wmb()	यंत्र अस्थिर("sfence" ::: "memory")
#घोषणा smp_rmb() barrier()
#घोषणा smp_wmb() barrier()
#घोषणा smp_mb()  यंत्र अस्थिर("lock; addl $0,-132(%%rsp)" ::: "memory", "cc")
#पूर्ण_अगर

#अगर defined(__x86_64__)
#घोषणा smp_store_release(p, v)			\
करो अणु						\
	barrier();				\
	WRITE_ONCE(*p, v);			\
पूर्ण जबतक (0)

#घोषणा smp_load_acquire(p)			\
(अणु						\
	typeof(*p) ___p1 = READ_ONCE(*p);	\
	barrier();				\
	___p1;					\
पूर्ण)
#पूर्ण_अगर /* defined(__x86_64__) */
#पूर्ण_अगर /* _TOOLS_LINUX_ASM_X86_BARRIER_H */
