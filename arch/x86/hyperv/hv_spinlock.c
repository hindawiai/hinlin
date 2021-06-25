<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * Hyper-V specअगरic spinlock code.
 *
 * Copyright (C) 2018, Intel, Inc.
 *
 * Author : Yi Sun <yi.y.sun@पूर्णांकel.com>
 */

#घोषणा pr_fmt(fmt) "Hyper-V: " fmt

#समावेश <linux/spinlock.h>

#समावेश <यंत्र/mshyperv.h>
#समावेश <यंत्र/paravirt.h>
#समावेश <यंत्र/apic.h>

अटल bool __initdata hv_pvspin = true;

अटल व्योम hv_qlock_kick(पूर्णांक cpu)
अणु
	apic->send_IPI(cpu, X86_PLATFORM_IPI_VECTOR);
पूर्ण

अटल व्योम hv_qlock_रुको(u8 *byte, u8 val)
अणु
	अचिन्हित दीर्घ flags;

	अगर (in_nmi())
		वापस;

	/*
	 * Reading HV_X64_MSR_GUEST_IDLE MSR tells the hypervisor that the
	 * vCPU can be put पूर्णांकo 'idle' state. This 'idle' state is
	 * terminated by an IPI, usually from hv_qlock_kick(), even अगर
	 * पूर्णांकerrupts are disabled on the vCPU.
	 *
	 * To prevent a race against the unlock path it is required to
	 * disable पूर्णांकerrupts beक्रमe accessing the HV_X64_MSR_GUEST_IDLE
	 * MSR. Otherwise, अगर the IPI from hv_qlock_kick() arrives between
	 * the lock value check and the rdmsrl() then the vCPU might be put
	 * पूर्णांकo 'idle' state by the hypervisor and kept in that state क्रम
	 * an unspecअगरied amount of समय.
	 */
	local_irq_save(flags);
	/*
	 * Only issue the rdmsrl() when the lock state has not changed.
	 */
	अगर (READ_ONCE(*byte) == val) अणु
		अचिन्हित दीर्घ msr_val;

		rdmsrl(HV_X64_MSR_GUEST_IDLE, msr_val);

		(व्योम)msr_val;
	पूर्ण
	local_irq_restore(flags);
पूर्ण

/*
 * Hyper-V करोes not support this so far.
 */
__visible bool hv_vcpu_is_preempted(पूर्णांक vcpu)
अणु
	वापस false;
पूर्ण
PV_CALLEE_SAVE_REGS_THUNK(hv_vcpu_is_preempted);

व्योम __init hv_init_spinlocks(व्योम)
अणु
	अगर (!hv_pvspin || !apic ||
	    !(ms_hyperv.hपूर्णांकs & HV_X64_CLUSTER_IPI_RECOMMENDED) ||
	    !(ms_hyperv.features & HV_MSR_GUEST_IDLE_AVAILABLE)) अणु
		pr_info("PV spinlocks disabled\n");
		वापस;
	पूर्ण
	pr_info("PV spinlocks enabled\n");

	__pv_init_lock_hash();
	pv_ops.lock.queued_spin_lock_slowpath = __pv_queued_spin_lock_slowpath;
	pv_ops.lock.queued_spin_unlock = PV_CALLEE_SAVE(__pv_queued_spin_unlock);
	pv_ops.lock.रुको = hv_qlock_रुको;
	pv_ops.lock.kick = hv_qlock_kick;
	pv_ops.lock.vcpu_is_preempted = PV_CALLEE_SAVE(hv_vcpu_is_preempted);
पूर्ण

अटल __init पूर्णांक hv_parse_nopvspin(अक्षर *arg)
अणु
	hv_pvspin = false;
	वापस 0;
पूर्ण
early_param("hv_nopvspin", hv_parse_nopvspin);
