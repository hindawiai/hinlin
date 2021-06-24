<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित _ASM_POWERPC_PARAVIRT_H
#घोषणा _ASM_POWERPC_PARAVIRT_H

#समावेश <linux/jump_label.h>
#समावेश <यंत्र/smp.h>
#अगर_घोषित CONFIG_PPC64
#समावेश <यंत्र/paca.h>
#समावेश <यंत्र/hvcall.h>
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_SPLPAR
#समावेश <linux/smp.h>
#समावेश <यंत्र/kvm_guest.h>
#समावेश <यंत्र/cputhपढ़ोs.h>

DECLARE_STATIC_KEY_FALSE(shared_processor);

अटल अंतरभूत bool is_shared_processor(व्योम)
अणु
	वापस अटल_branch_unlikely(&shared_processor);
पूर्ण

/* If bit 0 is set, the cpu has been preempted */
अटल अंतरभूत u32 yield_count_of(पूर्णांक cpu)
अणु
	__be32 yield_count = READ_ONCE(lppaca_of(cpu).yield_count);
	वापस be32_to_cpu(yield_count);
पूर्ण

/*
 * Spinlock code confers and prods, so करोn't trace the hcalls because the
 * tracing code takes spinlocks which can cause recursion deadlocks.
 *
 * These calls are made जबतक the lock is not held: the lock slowpath yields अगर
 * it can not acquire the lock, and unlock slow path might prod अगर a रुकोer has
 * yielded). So this may not be a problem क्रम simple spin locks because the
 * tracing करोes not technically recurse on the lock, but we aव्योम it anyway.
 *
 * However the queued spin lock contended path is more strictly ordered: the
 * H_CONFER hcall is made after the task has queued itself on the lock, so then
 * recursing on that lock will cause the task to then queue up again behind the
 * first instance (or worse: queued spinlocks use tricks that assume a context
 * never रुकोs on more than one spinlock, so such recursion may cause अक्रमom
 * corruption in the lock code).
 */
अटल अंतरभूत व्योम yield_to_preempted(पूर्णांक cpu, u32 yield_count)
अणु
	plpar_hcall_norets_notrace(H_CONFER, get_hard_smp_processor_id(cpu), yield_count);
पूर्ण

अटल अंतरभूत व्योम prod_cpu(पूर्णांक cpu)
अणु
	plpar_hcall_norets_notrace(H_PROD, get_hard_smp_processor_id(cpu));
पूर्ण

अटल अंतरभूत व्योम yield_to_any(व्योम)
अणु
	plpar_hcall_norets_notrace(H_CONFER, -1, 0);
पूर्ण
#अन्यथा
अटल अंतरभूत bool is_shared_processor(व्योम)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत u32 yield_count_of(पूर्णांक cpu)
अणु
	वापस 0;
पूर्ण

बाह्य व्योम ___bad_yield_to_preempted(व्योम);
अटल अंतरभूत व्योम yield_to_preempted(पूर्णांक cpu, u32 yield_count)
अणु
	___bad_yield_to_preempted(); /* This would be a bug */
पूर्ण

बाह्य व्योम ___bad_yield_to_any(व्योम);
अटल अंतरभूत व्योम yield_to_any(व्योम)
अणु
	___bad_yield_to_any(); /* This would be a bug */
पूर्ण

बाह्य व्योम ___bad_prod_cpu(व्योम);
अटल अंतरभूत व्योम prod_cpu(पूर्णांक cpu)
अणु
	___bad_prod_cpu(); /* This would be a bug */
पूर्ण

#पूर्ण_अगर

#घोषणा vcpu_is_preempted vcpu_is_preempted
अटल अंतरभूत bool vcpu_is_preempted(पूर्णांक cpu)
अणु
	अगर (!is_shared_processor())
		वापस false;

#अगर_घोषित CONFIG_PPC_SPLPAR
	अगर (!is_kvm_guest()) अणु
		पूर्णांक first_cpu = cpu_first_thपढ़ो_sibling(smp_processor_id());

		/*
		 * Preemption can only happen at core granularity. This CPU
		 * is not preempted अगर one of the CPU of this core is not
		 * preempted.
		 */
		अगर (cpu_first_thपढ़ो_sibling(cpu) == first_cpu)
			वापस false;
	पूर्ण
#पूर्ण_अगर

	अगर (yield_count_of(cpu) & 1)
		वापस true;
	वापस false;
पूर्ण

अटल अंतरभूत bool pv_is_native_spin_unlock(व्योम)
अणु
	वापस !is_shared_processor();
पूर्ण

#पूर्ण_अगर /* _ASM_POWERPC_PARAVIRT_H */
