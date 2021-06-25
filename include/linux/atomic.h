<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Atomic operations usable in machine independent code */
#अगर_अघोषित _LINUX_ATOMIC_H
#घोषणा _LINUX_ATOMIC_H
#समावेश <linux/types.h>

#समावेश <यंत्र/atomic.h>
#समावेश <यंत्र/barrier.h>

/*
 * Relaxed variants of xchg, cmpxchg and some atomic operations.
 *
 * We support four variants:
 *
 * - Fully ordered: The शेष implementation, no suffix required.
 * - Acquire: Provides ACQUIRE semantics, _acquire suffix.
 * - Release: Provides RELEASE semantics, _release suffix.
 * - Relaxed: No ordering guarantees, _relaxed suffix.
 *
 * For compound atomics perक्रमming both a load and a store, ACQUIRE
 * semantics apply only to the load and RELEASE semantics only to the
 * store portion of the operation. Note that a failed cmpxchg_acquire
 * करोes -not- imply any memory ordering स्थिरraपूर्णांकs.
 *
 * See Documentation/memory-barriers.txt क्रम ACQUIRE/RELEASE definitions.
 */

#घोषणा atomic_cond_पढ़ो_acquire(v, c) smp_cond_load_acquire(&(v)->counter, (c))
#घोषणा atomic_cond_पढ़ो_relaxed(v, c) smp_cond_load_relaxed(&(v)->counter, (c))

#घोषणा atomic64_cond_पढ़ो_acquire(v, c) smp_cond_load_acquire(&(v)->counter, (c))
#घोषणा atomic64_cond_पढ़ो_relaxed(v, c) smp_cond_load_relaxed(&(v)->counter, (c))

/*
 * The idea here is to build acquire/release variants by adding explicit
 * barriers on top of the relaxed variant. In the हाल where the relaxed
 * variant is alपढ़ोy fully ordered, no additional barriers are needed.
 *
 * If an architecture overrides __atomic_acquire_fence() it will probably
 * want to define smp_mb__after_spinlock().
 */
#अगर_अघोषित __atomic_acquire_fence
#घोषणा __atomic_acquire_fence		smp_mb__after_atomic
#पूर्ण_अगर

#अगर_अघोषित __atomic_release_fence
#घोषणा __atomic_release_fence		smp_mb__beक्रमe_atomic
#पूर्ण_अगर

#अगर_अघोषित __atomic_pre_full_fence
#घोषणा __atomic_pre_full_fence		smp_mb__beक्रमe_atomic
#पूर्ण_अगर

#अगर_अघोषित __atomic_post_full_fence
#घोषणा __atomic_post_full_fence	smp_mb__after_atomic
#पूर्ण_अगर

#घोषणा __atomic_op_acquire(op, args...)				\
(अणु									\
	typeof(op##_relaxed(args)) __ret  = op##_relaxed(args);		\
	__atomic_acquire_fence();					\
	__ret;								\
पूर्ण)

#घोषणा __atomic_op_release(op, args...)				\
(अणु									\
	__atomic_release_fence();					\
	op##_relaxed(args);						\
पूर्ण)

#घोषणा __atomic_op_fence(op, args...)					\
(अणु									\
	typeof(op##_relaxed(args)) __ret;				\
	__atomic_pre_full_fence();					\
	__ret = op##_relaxed(args);					\
	__atomic_post_full_fence();					\
	__ret;								\
पूर्ण)

#अगर_घोषित ARCH_ATOMIC
#समावेश <linux/atomic-arch-fallback.h>
#समावेश <यंत्र-generic/atomic-instrumented.h>
#अन्यथा
#समावेश <linux/atomic-fallback.h>
#पूर्ण_अगर

#समावेश <यंत्र-generic/atomic-दीर्घ.h>

#पूर्ण_अगर /* _LINUX_ATOMIC_H */
