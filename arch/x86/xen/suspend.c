<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/types.h>
#समावेश <linux/tick.h>
#समावेश <linux/percpu-defs.h>

#समावेश <xen/xen.h>
#समावेश <xen/पूर्णांकerface/xen.h>
#समावेश <xen/grant_table.h>
#समावेश <xen/events.h>

#समावेश <यंत्र/cpufeatures.h>
#समावेश <यंत्र/msr-index.h>
#समावेश <यंत्र/xen/hypercall.h>
#समावेश <यंत्र/xen/page.h>
#समावेश <यंत्र/fixmap.h>

#समावेश "xen-ops.h"
#समावेश "mmu.h"
#समावेश "pmu.h"

अटल DEFINE_PER_CPU(u64, spec_ctrl);

व्योम xen_arch_pre_suspend(व्योम)
अणु
	xen_save_समय_memory_area();

	अगर (xen_pv_करोमुख्य())
		xen_pv_pre_suspend();
पूर्ण

व्योम xen_arch_post_suspend(पूर्णांक cancelled)
अणु
	अगर (xen_pv_करोमुख्य())
		xen_pv_post_suspend(cancelled);
	अन्यथा
		xen_hvm_post_suspend(cancelled);

	xen_restore_समय_memory_area();
पूर्ण

अटल व्योम xen_vcpu_notअगरy_restore(व्योम *data)
अणु
	अगर (xen_pv_करोमुख्य() && boot_cpu_has(X86_FEATURE_SPEC_CTRL))
		wrmsrl(MSR_IA32_SPEC_CTRL, this_cpu_पढ़ो(spec_ctrl));

	/* Boot processor notअगरied via generic समयkeeping_resume() */
	अगर (smp_processor_id() == 0)
		वापस;

	tick_resume_local();
पूर्ण

अटल व्योम xen_vcpu_notअगरy_suspend(व्योम *data)
अणु
	u64 पंचांगp;

	tick_suspend_local();

	अगर (xen_pv_करोमुख्य() && boot_cpu_has(X86_FEATURE_SPEC_CTRL)) अणु
		rdmsrl(MSR_IA32_SPEC_CTRL, पंचांगp);
		this_cpu_ग_लिखो(spec_ctrl, पंचांगp);
		wrmsrl(MSR_IA32_SPEC_CTRL, 0);
	पूर्ण
पूर्ण

व्योम xen_arch_resume(व्योम)
अणु
	पूर्णांक cpu;

	on_each_cpu(xen_vcpu_notअगरy_restore, शून्य, 1);

	क्रम_each_online_cpu(cpu)
		xen_pmu_init(cpu);
पूर्ण

व्योम xen_arch_suspend(व्योम)
अणु
	पूर्णांक cpu;

	क्रम_each_online_cpu(cpu)
		xen_pmu_finish(cpu);

	on_each_cpu(xen_vcpu_notअगरy_suspend, शून्य, 1);
पूर्ण
