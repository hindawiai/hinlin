<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Uniprocessor-only support functions.  The counterpart to kernel/smp.c
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/smp.h>
#समावेश <linux/hypervisor.h>

पूर्णांक smp_call_function_single(पूर्णांक cpu, व्योम (*func) (व्योम *info), व्योम *info,
				पूर्णांक रुको)
अणु
	अचिन्हित दीर्घ flags;

	अगर (cpu != 0)
		वापस -ENXIO;

	local_irq_save(flags);
	func(info);
	local_irq_restore(flags);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(smp_call_function_single);

पूर्णांक smp_call_function_single_async(पूर्णांक cpu, काष्ठा __call_single_data *csd)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	csd->func(csd->info);
	local_irq_restore(flags);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(smp_call_function_single_async);

/*
 * Preemption is disabled here to make sure the cond_func is called under the
 * same conditions in UP and SMP.
 */
व्योम on_each_cpu_cond_mask(smp_cond_func_t cond_func, smp_call_func_t func,
			   व्योम *info, bool रुको, स्थिर काष्ठा cpumask *mask)
अणु
	अचिन्हित दीर्घ flags;

	preempt_disable();
	अगर ((!cond_func || cond_func(0, info)) && cpumask_test_cpu(0, mask)) अणु
		local_irq_save(flags);
		func(info);
		local_irq_restore(flags);
	पूर्ण
	preempt_enable();
पूर्ण
EXPORT_SYMBOL(on_each_cpu_cond_mask);

पूर्णांक smp_call_on_cpu(अचिन्हित पूर्णांक cpu, पूर्णांक (*func)(व्योम *), व्योम *par, bool phys)
अणु
	पूर्णांक ret;

	अगर (cpu != 0)
		वापस -ENXIO;

	अगर (phys)
		hypervisor_pin_vcpu(0);
	ret = func(par);
	अगर (phys)
		hypervisor_pin_vcpu(-1);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(smp_call_on_cpu);
