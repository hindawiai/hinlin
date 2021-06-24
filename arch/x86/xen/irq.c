<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/hardirq.h>

#समावेश <यंत्र/x86_init.h>

#समावेश <xen/पूर्णांकerface/xen.h>
#समावेश <xen/पूर्णांकerface/sched.h>
#समावेश <xen/पूर्णांकerface/vcpu.h>
#समावेश <xen/features.h>
#समावेश <xen/events.h>

#समावेश <यंत्र/xen/hypercall.h>
#समावेश <यंत्र/xen/hypervisor.h>

#समावेश "xen-ops.h"

/*
 * Force a proper event-channel callback from Xen after clearing the
 * callback mask. We करो this in a very simple manner, by making a call
 * करोwn पूर्णांकo Xen. The pending flag will be checked by Xen on वापस.
 */
व्योम xen_क्रमce_evtchn_callback(व्योम)
अणु
	(व्योम)HYPERVISOR_xen_version(0, शून्य);
पूर्ण

यंत्रlinkage __visible अचिन्हित दीर्घ xen_save_fl(व्योम)
अणु
	काष्ठा vcpu_info *vcpu;
	अचिन्हित दीर्घ flags;

	vcpu = this_cpu_पढ़ो(xen_vcpu);

	/* flag has opposite sense of mask */
	flags = !vcpu->evtchn_upcall_mask;

	/* convert to IF type flag
	   -0 -> 0x00000000
	   -1 -> 0xffffffff
	*/
	वापस (-flags) & X86_EFLAGS_IF;
पूर्ण
PV_CALLEE_SAVE_REGS_THUNK(xen_save_fl);

यंत्रlinkage __visible व्योम xen_irq_disable(व्योम)
अणु
	/* There's a one inकाष्ठाion preempt winकरोw here.  We need to
	   make sure we're don't चयन CPUs between getting the vcpu
	   poपूर्णांकer and updating the mask. */
	preempt_disable();
	this_cpu_पढ़ो(xen_vcpu)->evtchn_upcall_mask = 1;
	preempt_enable_no_resched();
पूर्ण
PV_CALLEE_SAVE_REGS_THUNK(xen_irq_disable);

यंत्रlinkage __visible व्योम xen_irq_enable(व्योम)
अणु
	काष्ठा vcpu_info *vcpu;

	/*
	 * We may be preempted as soon as vcpu->evtchn_upcall_mask is
	 * cleared, so disable preemption to ensure we check क्रम
	 * events on the VCPU we are still running on.
	 */
	preempt_disable();

	vcpu = this_cpu_पढ़ो(xen_vcpu);
	vcpu->evtchn_upcall_mask = 0;

	/* Doesn't matter अगर we get preempted here, because any
	   pending event will get dealt with anyway. */

	barrier(); /* unmask then check (aव्योम races) */
	अगर (unlikely(vcpu->evtchn_upcall_pending))
		xen_क्रमce_evtchn_callback();

	preempt_enable();
पूर्ण
PV_CALLEE_SAVE_REGS_THUNK(xen_irq_enable);

अटल व्योम xen_safe_halt(व्योम)
अणु
	/* Blocking includes an implicit local_irq_enable(). */
	अगर (HYPERVISOR_sched_op(SCHEDOP_block, शून्य) != 0)
		BUG();
पूर्ण

अटल व्योम xen_halt(व्योम)
अणु
	अगर (irqs_disabled())
		HYPERVISOR_vcpu_op(VCPUOP_करोwn,
				   xen_vcpu_nr(smp_processor_id()), शून्य);
	अन्यथा
		xen_safe_halt();
पूर्ण

अटल स्थिर काष्ठा pv_irq_ops xen_irq_ops __initस्थिर = अणु
	.save_fl = PV_CALLEE_SAVE(xen_save_fl),
	.irq_disable = PV_CALLEE_SAVE(xen_irq_disable),
	.irq_enable = PV_CALLEE_SAVE(xen_irq_enable),

	.safe_halt = xen_safe_halt,
	.halt = xen_halt,
पूर्ण;

व्योम __init xen_init_irq_ops(व्योम)
अणु
	pv_ops.irq = xen_irq_ops;
	x86_init.irqs.पूर्णांकr_init = xen_init_IRQ;
पूर्ण
