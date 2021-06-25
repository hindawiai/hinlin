<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Generic barrier definitions.
 *
 * It should be possible to use these on really simple architectures,
 * but it serves more as a starting poपूर्णांक क्रम new ports.
 *
 * Copyright (C) 2007 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */
#अगर_अघोषित __ASM_GENERIC_BARRIER_H
#घोषणा __ASM_GENERIC_BARRIER_H

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/compiler.h>
#समावेश <यंत्र/rwonce.h>

#अगर_अघोषित nop
#घोषणा nop()	यंत्र अस्थिर ("nop")
#पूर्ण_अगर

/*
 * Force strict CPU ordering. And yes, this is required on UP too when we're
 * talking to devices.
 *
 * Fall back to compiler barriers अगर nothing better is provided.
 */

#अगर_अघोषित mb
#घोषणा mb()	barrier()
#पूर्ण_अगर

#अगर_अघोषित rmb
#घोषणा rmb()	mb()
#पूर्ण_अगर

#अगर_अघोषित wmb
#घोषणा wmb()	mb()
#पूर्ण_अगर

#अगर_अघोषित dma_rmb
#घोषणा dma_rmb()	rmb()
#पूर्ण_अगर

#अगर_अघोषित dma_wmb
#घोषणा dma_wmb()	wmb()
#पूर्ण_अगर

#अगर_अघोषित __smp_mb
#घोषणा __smp_mb()	mb()
#पूर्ण_अगर

#अगर_अघोषित __smp_rmb
#घोषणा __smp_rmb()	rmb()
#पूर्ण_अगर

#अगर_अघोषित __smp_wmb
#घोषणा __smp_wmb()	wmb()
#पूर्ण_अगर

#अगर_घोषित CONFIG_SMP

#अगर_अघोषित smp_mb
#घोषणा smp_mb()	__smp_mb()
#पूर्ण_अगर

#अगर_अघोषित smp_rmb
#घोषणा smp_rmb()	__smp_rmb()
#पूर्ण_अगर

#अगर_अघोषित smp_wmb
#घोषणा smp_wmb()	__smp_wmb()
#पूर्ण_अगर

#अन्यथा	/* !CONFIG_SMP */

#अगर_अघोषित smp_mb
#घोषणा smp_mb()	barrier()
#पूर्ण_अगर

#अगर_अघोषित smp_rmb
#घोषणा smp_rmb()	barrier()
#पूर्ण_अगर

#अगर_अघोषित smp_wmb
#घोषणा smp_wmb()	barrier()
#पूर्ण_अगर

#पूर्ण_अगर	/* CONFIG_SMP */

#अगर_अघोषित __smp_store_mb
#घोषणा __smp_store_mb(var, value)  करो अणु WRITE_ONCE(var, value); __smp_mb(); पूर्ण जबतक (0)
#पूर्ण_अगर

#अगर_अघोषित __smp_mb__beक्रमe_atomic
#घोषणा __smp_mb__beक्रमe_atomic()	__smp_mb()
#पूर्ण_अगर

#अगर_अघोषित __smp_mb__after_atomic
#घोषणा __smp_mb__after_atomic()	__smp_mb()
#पूर्ण_अगर

#अगर_अघोषित __smp_store_release
#घोषणा __smp_store_release(p, v)					\
करो अणु									\
	compileसमय_निश्चित_atomic_type(*p);				\
	__smp_mb();							\
	WRITE_ONCE(*p, v);						\
पूर्ण जबतक (0)
#पूर्ण_अगर

#अगर_अघोषित __smp_load_acquire
#घोषणा __smp_load_acquire(p)						\
(अणु									\
	__unqual_scalar_typeof(*p) ___p1 = READ_ONCE(*p);		\
	compileसमय_निश्चित_atomic_type(*p);				\
	__smp_mb();							\
	(typeof(*p))___p1;						\
पूर्ण)
#पूर्ण_अगर

#अगर_घोषित CONFIG_SMP

#अगर_अघोषित smp_store_mb
#घोषणा smp_store_mb(var, value)  __smp_store_mb(var, value)
#पूर्ण_अगर

#अगर_अघोषित smp_mb__beक्रमe_atomic
#घोषणा smp_mb__beक्रमe_atomic()	__smp_mb__beक्रमe_atomic()
#पूर्ण_अगर

#अगर_अघोषित smp_mb__after_atomic
#घोषणा smp_mb__after_atomic()	__smp_mb__after_atomic()
#पूर्ण_अगर

#अगर_अघोषित smp_store_release
#घोषणा smp_store_release(p, v) __smp_store_release(p, v)
#पूर्ण_अगर

#अगर_अघोषित smp_load_acquire
#घोषणा smp_load_acquire(p) __smp_load_acquire(p)
#पूर्ण_अगर

#अन्यथा	/* !CONFIG_SMP */

#अगर_अघोषित smp_store_mb
#घोषणा smp_store_mb(var, value)  करो अणु WRITE_ONCE(var, value); barrier(); पूर्ण जबतक (0)
#पूर्ण_अगर

#अगर_अघोषित smp_mb__beक्रमe_atomic
#घोषणा smp_mb__beक्रमe_atomic()	barrier()
#पूर्ण_अगर

#अगर_अघोषित smp_mb__after_atomic
#घोषणा smp_mb__after_atomic()	barrier()
#पूर्ण_अगर

#अगर_अघोषित smp_store_release
#घोषणा smp_store_release(p, v)						\
करो अणु									\
	compileसमय_निश्चित_atomic_type(*p);				\
	barrier();							\
	WRITE_ONCE(*p, v);						\
पूर्ण जबतक (0)
#पूर्ण_अगर

#अगर_अघोषित smp_load_acquire
#घोषणा smp_load_acquire(p)						\
(अणु									\
	__unqual_scalar_typeof(*p) ___p1 = READ_ONCE(*p);		\
	compileसमय_निश्चित_atomic_type(*p);				\
	barrier();							\
	(typeof(*p))___p1;						\
पूर्ण)
#पूर्ण_अगर

#पूर्ण_अगर	/* CONFIG_SMP */

/* Barriers क्रम भव machine guests when talking to an SMP host */
#घोषणा virt_mb() __smp_mb()
#घोषणा virt_rmb() __smp_rmb()
#घोषणा virt_wmb() __smp_wmb()
#घोषणा virt_store_mb(var, value) __smp_store_mb(var, value)
#घोषणा virt_mb__beक्रमe_atomic() __smp_mb__beक्रमe_atomic()
#घोषणा virt_mb__after_atomic()	__smp_mb__after_atomic()
#घोषणा virt_store_release(p, v) __smp_store_release(p, v)
#घोषणा virt_load_acquire(p) __smp_load_acquire(p)

/**
 * smp_acquire__after_ctrl_dep() - Provide ACQUIRE ordering after a control dependency
 *
 * A control dependency provides a LOAD->STORE order, the additional RMB
 * provides LOAD->LOAD order, together they provide LOAD->अणुLOAD,STOREपूर्ण order,
 * aka. (load)-ACQUIRE.
 *
 * Architectures that करो not करो load speculation can have this be barrier().
 */
#अगर_अघोषित smp_acquire__after_ctrl_dep
#घोषणा smp_acquire__after_ctrl_dep()		smp_rmb()
#पूर्ण_अगर

/**
 * smp_cond_load_relaxed() - (Spin) रुको क्रम cond with no ordering guarantees
 * @ptr: poपूर्णांकer to the variable to रुको on
 * @cond: boolean expression to रुको क्रम
 *
 * Equivalent to using READ_ONCE() on the condition variable.
 *
 * Due to C lacking lambda expressions we load the value of *ptr पूर्णांकo a
 * pre-named variable @VAL to be used in @cond.
 */
#अगर_अघोषित smp_cond_load_relaxed
#घोषणा smp_cond_load_relaxed(ptr, cond_expr) (अणु		\
	typeof(ptr) __PTR = (ptr);				\
	__unqual_scalar_typeof(*ptr) VAL;			\
	क्रम (;;) अणु						\
		VAL = READ_ONCE(*__PTR);			\
		अगर (cond_expr)					\
			अवरोध;					\
		cpu_relax();					\
	पूर्ण							\
	(typeof(*ptr))VAL;					\
पूर्ण)
#पूर्ण_अगर

/**
 * smp_cond_load_acquire() - (Spin) रुको क्रम cond with ACQUIRE ordering
 * @ptr: poपूर्णांकer to the variable to रुको on
 * @cond: boolean expression to रुको क्रम
 *
 * Equivalent to using smp_load_acquire() on the condition variable but employs
 * the control dependency of the रुको to reduce the barrier on many platक्रमms.
 */
#अगर_अघोषित smp_cond_load_acquire
#घोषणा smp_cond_load_acquire(ptr, cond_expr) (अणु		\
	__unqual_scalar_typeof(*ptr) _val;			\
	_val = smp_cond_load_relaxed(ptr, cond_expr);		\
	smp_acquire__after_ctrl_dep();				\
	(typeof(*ptr))_val;					\
पूर्ण)
#पूर्ण_अगर

/*
 * pmem_wmb() ensures that all stores क्रम which the modअगरication
 * are written to persistent storage by preceding inकाष्ठाions have
 * updated persistent storage beक्रमe any data  access or data transfer
 * caused by subsequent inकाष्ठाions is initiated.
 */
#अगर_अघोषित pmem_wmb
#घोषणा pmem_wmb()	wmb()
#पूर्ण_अगर

#पूर्ण_अगर /* !__ASSEMBLY__ */
#पूर्ण_अगर /* __ASM_GENERIC_BARRIER_H */
