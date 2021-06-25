<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * IRQ flags handling
 */
#अगर_अघोषित _ASM_IRQFLAGS_H
#घोषणा _ASM_IRQFLAGS_H

#अगर_अघोषित __ASSEMBLY__
/*
 * Get definitions क्रम arch_local_save_flags(x), etc.
 */
#समावेश <यंत्र/hw_irq.h>

#अन्यथा
#अगर_घोषित CONFIG_TRACE_IRQFLAGS
#अगर_घोषित CONFIG_IRQSOFF_TRACER
/*
 * Since the ftrace irqsoff latency trace checks CALLER_ADDR1,
 * which is the stack frame here, we need to क्रमce a stack frame
 * in हाल we came from user space.
 */
#घोषणा TRACE_WITH_FRAME_BUFFER(func)		\
	mflr	r0;				\
	stdu	r1, -STACK_FRAME_OVERHEAD(r1);	\
	std	r0, 16(r1);			\
	stdu	r1, -STACK_FRAME_OVERHEAD(r1);	\
	bl func;				\
	ld	r1, 0(r1);			\
	ld	r1, 0(r1);
#अन्यथा
#घोषणा TRACE_WITH_FRAME_BUFFER(func)		\
	bl func;
#पूर्ण_अगर

/*
 * These are calls to C code, so the caller must be prepared क्रम अस्थिरs to
 * be clobbered.
 */
#घोषणा TRACE_ENABLE_INTS	TRACE_WITH_FRAME_BUFFER(trace_hardirqs_on)
#घोषणा TRACE_DISABLE_INTS	TRACE_WITH_FRAME_BUFFER(trace_hardirqs_off)

/*
 * This is used by assembly code to soft-disable पूर्णांकerrupts first and
 * reconcile irq state.
 *
 * NB: This may call C code, so the caller must be prepared क्रम अस्थिरs to
 * be clobbered.
 */
#घोषणा RECONCILE_IRQ_STATE(__rA, __rB)		\
	lbz	__rA,PACAIRQSOFTMASK(r13);	\
	lbz	__rB,PACAIRQHAPPENED(r13);	\
	andi.	__rA,__rA,IRQS_DISABLED;	\
	li	__rA,IRQS_DISABLED;		\
	ori	__rB,__rB,PACA_IRQ_HARD_DIS;	\
	stb	__rB,PACAIRQHAPPENED(r13);	\
	bne	44f;				\
	stb	__rA,PACAIRQSOFTMASK(r13);	\
	TRACE_DISABLE_INTS;			\
44:

#अन्यथा
#घोषणा TRACE_ENABLE_INTS
#घोषणा TRACE_DISABLE_INTS

#घोषणा RECONCILE_IRQ_STATE(__rA, __rB)		\
	lbz	__rA,PACAIRQHAPPENED(r13);	\
	li	__rB,IRQS_DISABLED;		\
	ori	__rA,__rA,PACA_IRQ_HARD_DIS;	\
	stb	__rB,PACAIRQSOFTMASK(r13);	\
	stb	__rA,PACAIRQHAPPENED(r13)
#पूर्ण_अगर
#पूर्ण_अगर

#पूर्ण_अगर
