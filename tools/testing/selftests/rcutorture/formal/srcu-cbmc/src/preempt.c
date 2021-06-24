<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <config.h>

#समावेश "preempt.h"

#समावेश "assume.h"
#समावेश "locks.h"

/* Support NR_CPUS of at most 64 */
#घोषणा CPU_PREEMPTION_LOCKS_INIT0 LOCK_IMPL_INITIALIZER
#घोषणा CPU_PREEMPTION_LOCKS_INIT1 \
	CPU_PREEMPTION_LOCKS_INIT0, CPU_PREEMPTION_LOCKS_INIT0
#घोषणा CPU_PREEMPTION_LOCKS_INIT2 \
	CPU_PREEMPTION_LOCKS_INIT1, CPU_PREEMPTION_LOCKS_INIT1
#घोषणा CPU_PREEMPTION_LOCKS_INIT3 \
	CPU_PREEMPTION_LOCKS_INIT2, CPU_PREEMPTION_LOCKS_INIT2
#घोषणा CPU_PREEMPTION_LOCKS_INIT4 \
	CPU_PREEMPTION_LOCKS_INIT3, CPU_PREEMPTION_LOCKS_INIT3
#घोषणा CPU_PREEMPTION_LOCKS_INIT5 \
	CPU_PREEMPTION_LOCKS_INIT4, CPU_PREEMPTION_LOCKS_INIT4

/*
 * Simulate disabling preemption by locking a particular cpu. NR_CPUS
 * should be the actual number of cpus, not just the maximum.
 */
काष्ठा lock_impl cpu_preemption_locks[NR_CPUS] = अणु
	CPU_PREEMPTION_LOCKS_INIT0
#अगर (NR_CPUS - 1) & 1
	, CPU_PREEMPTION_LOCKS_INIT0
#पूर्ण_अगर
#अगर (NR_CPUS - 1) & 2
	, CPU_PREEMPTION_LOCKS_INIT1
#पूर्ण_अगर
#अगर (NR_CPUS - 1) & 4
	, CPU_PREEMPTION_LOCKS_INIT2
#पूर्ण_अगर
#अगर (NR_CPUS - 1) & 8
	, CPU_PREEMPTION_LOCKS_INIT3
#पूर्ण_अगर
#अगर (NR_CPUS - 1) & 16
	, CPU_PREEMPTION_LOCKS_INIT4
#पूर्ण_अगर
#अगर (NR_CPUS - 1) & 32
	, CPU_PREEMPTION_LOCKS_INIT5
#पूर्ण_अगर
पूर्ण;

#अघोषित CPU_PREEMPTION_LOCKS_INIT0
#अघोषित CPU_PREEMPTION_LOCKS_INIT1
#अघोषित CPU_PREEMPTION_LOCKS_INIT2
#अघोषित CPU_PREEMPTION_LOCKS_INIT3
#अघोषित CPU_PREEMPTION_LOCKS_INIT4
#अघोषित CPU_PREEMPTION_LOCKS_INIT5

__thपढ़ो पूर्णांक thपढ़ो_cpu_id;
__thपढ़ो पूर्णांक preempt_disable_count;

व्योम preempt_disable(व्योम)
अणु
	BUG_ON(preempt_disable_count < 0 || preempt_disable_count == पूर्णांक_उच्च);

	अगर (preempt_disable_count++)
		वापस;

	thपढ़ो_cpu_id = nondet_पूर्णांक();
	assume(thपढ़ो_cpu_id >= 0);
	assume(thपढ़ो_cpu_id < NR_CPUS);
	lock_impl_lock(&cpu_preemption_locks[thपढ़ो_cpu_id]);
पूर्ण

व्योम preempt_enable(व्योम)
अणु
	BUG_ON(preempt_disable_count < 1);

	अगर (--preempt_disable_count)
		वापस;

	lock_impl_unlock(&cpu_preemption_locks[thपढ़ो_cpu_id]);
पूर्ण
