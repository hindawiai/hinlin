<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * lib/smp_processor_id.c
 *
 * DEBUG_PREEMPT variant of smp_processor_id().
 */
#समावेश <linux/export.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/sched.h>

noinstr अटल
अचिन्हित पूर्णांक check_preemption_disabled(स्थिर अक्षर *what1, स्थिर अक्षर *what2)
अणु
	पूर्णांक this_cpu = raw_smp_processor_id();

	अगर (likely(preempt_count()))
		जाओ out;

	अगर (irqs_disabled())
		जाओ out;

	/*
	 * Kernel thपढ़ोs bound to a single CPU can safely use
	 * smp_processor_id():
	 */
	अगर (current->nr_cpus_allowed == 1)
		जाओ out;

#अगर_घोषित CONFIG_SMP
	अगर (current->migration_disabled)
		जाओ out;
#पूर्ण_अगर

	/*
	 * It is valid to assume CPU-locality during early bootup:
	 */
	अगर (प्रणाली_state < SYSTEM_SCHEDULING)
		जाओ out;

	/*
	 * Aव्योम recursion:
	 */
	preempt_disable_notrace();

	instrumentation_begin();
	अगर (!prपूर्णांकk_ratelimit())
		जाओ out_enable;

	prपूर्णांकk(KERN_ERR "BUG: using %s%s() in preemptible [%08x] code: %s/%d\n",
		what1, what2, preempt_count() - 1, current->comm, current->pid);

	prपूर्णांकk("caller is %pS\n", __builtin_वापस_address(0));
	dump_stack();
	instrumentation_end();

out_enable:
	preempt_enable_no_resched_notrace();
out:
	वापस this_cpu;
पूर्ण

noinstr अचिन्हित पूर्णांक debug_smp_processor_id(व्योम)
अणु
	वापस check_preemption_disabled("smp_processor_id", "");
पूर्ण
EXPORT_SYMBOL(debug_smp_processor_id);

noinstr व्योम __this_cpu_preempt_check(स्थिर अक्षर *op)
अणु
	check_preemption_disabled("__this_cpu_", op);
पूर्ण
EXPORT_SYMBOL(__this_cpu_preempt_check);
