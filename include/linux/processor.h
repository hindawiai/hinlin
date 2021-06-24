<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Misc low level processor primitives */
#अगर_अघोषित _LINUX_PROCESSOR_H
#घोषणा _LINUX_PROCESSOR_H

#समावेश <यंत्र/processor.h>

/*
 * spin_begin is used beक्रमe beginning a busy-रुको loop, and must be paired
 * with spin_end when the loop is निकासed. spin_cpu_relax must be called
 * within the loop.
 *
 * The loop body should be as small and fast as possible, on the order of
 * tens of inकाष्ठाions/cycles as a guide. It should and aव्योम calling
 * cpu_relax, or any "spin" or sleep type of primitive including nested uses
 * of these primitives. It should not lock or take any other resource.
 * Violations of these guidelies will not cause a bug, but may cause sub
 * optimal perक्रमmance.
 *
 * These loops are optimized to be used where रुको बार are expected to be
 * less than the cost of a context चयन (and associated overhead).
 *
 * Detection of resource owner and decision to spin or sleep or guest-yield
 * (e.g., spin lock holder vcpu preempted, or mutex owner not on CPU) can be
 * tested within the loop body.
 */
#अगर_अघोषित spin_begin
#घोषणा spin_begin()
#पूर्ण_अगर

#अगर_अघोषित spin_cpu_relax
#घोषणा spin_cpu_relax() cpu_relax()
#पूर्ण_अगर

#अगर_अघोषित spin_end
#घोषणा spin_end()
#पूर्ण_अगर

/*
 * spin_until_cond can be used to रुको क्रम a condition to become true. It
 * may be expected that the first iteration will true in the common हाल
 * (no spinning), so that callers should not require a first "likely" test
 * क्रम the uncontended हाल beक्रमe using this primitive.
 *
 * Usage and implementation guidelines are the same as क्रम the spin_begin
 * primitives, above.
 */
#अगर_अघोषित spin_until_cond
#घोषणा spin_until_cond(cond)					\
करो अणु								\
	अगर (unlikely(!(cond))) अणु				\
		spin_begin();					\
		करो अणु						\
			spin_cpu_relax();			\
		पूर्ण जबतक (!(cond));				\
		spin_end();					\
	पूर्ण							\
पूर्ण जबतक (0)

#पूर्ण_अगर

#पूर्ण_अगर /* _LINUX_PROCESSOR_H */
