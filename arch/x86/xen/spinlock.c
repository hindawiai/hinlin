<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Split spinlock implementation out पूर्णांकo its own file, so it can be
 * compiled in a FTRACE-compatible way.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>
#समावेश <linux/atomic.h>

#समावेश <यंत्र/paravirt.h>
#समावेश <यंत्र/qspinlock.h>

#समावेश <xen/events.h>

#समावेश "xen-ops.h"

अटल DEFINE_PER_CPU(पूर्णांक, lock_kicker_irq) = -1;
अटल DEFINE_PER_CPU(अक्षर *, irq_name);
अटल DEFINE_PER_CPU(atomic_t, xen_qlock_रुको_nest);
अटल bool xen_pvspin = true;

अटल व्योम xen_qlock_kick(पूर्णांक cpu)
अणु
	पूर्णांक irq = per_cpu(lock_kicker_irq, cpu);

	/* Don't kick if the target's kicker पूर्णांकerrupt is not initialized. */
	अगर (irq == -1)
		वापस;

	xen_send_IPI_one(cpu, XEN_SPIN_UNLOCK_VECTOR);
पूर्ण

/*
 * Halt the current CPU & release it back to the host
 */
अटल व्योम xen_qlock_रुको(u8 *byte, u8 val)
अणु
	पूर्णांक irq = __this_cpu_पढ़ो(lock_kicker_irq);
	atomic_t *nest_cnt = this_cpu_ptr(&xen_qlock_रुको_nest);

	/* If kicker पूर्णांकerrupts not initialized yet, just spin */
	अगर (irq == -1 || in_nmi())
		वापस;

	/* Detect reentry. */
	atomic_inc(nest_cnt);

	/* If irq pending alपढ़ोy and no nested call clear it. */
	अगर (atomic_पढ़ो(nest_cnt) == 1 && xen_test_irq_pending(irq)) अणु
		xen_clear_irq_pending(irq);
	पूर्ण अन्यथा अगर (READ_ONCE(*byte) == val) अणु
		/* Block until irq becomes pending (or a spurious wakeup) */
		xen_poll_irq(irq);
	पूर्ण

	atomic_dec(nest_cnt);
पूर्ण

अटल irqवापस_t dummy_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	BUG();
	वापस IRQ_HANDLED;
पूर्ण

व्योम xen_init_lock_cpu(पूर्णांक cpu)
अणु
	पूर्णांक irq;
	अक्षर *name;

	अगर (!xen_pvspin)
		वापस;

	WARN(per_cpu(lock_kicker_irq, cpu) >= 0, "spinlock on CPU%d exists on IRQ%d!\n",
	     cpu, per_cpu(lock_kicker_irq, cpu));

	name = kaप्र_लिखो(GFP_KERNEL, "spinlock%d", cpu);
	irq = bind_ipi_to_irqhandler(XEN_SPIN_UNLOCK_VECTOR,
				     cpu,
				     dummy_handler,
				     IRQF_PERCPU|IRQF_NOBALANCING,
				     name,
				     शून्य);

	अगर (irq >= 0) अणु
		disable_irq(irq); /* make sure it's never delivered */
		per_cpu(lock_kicker_irq, cpu) = irq;
		per_cpu(irq_name, cpu) = name;
	पूर्ण

	prपूर्णांकk("cpu %d spinlock event irq %d\n", cpu, irq);
पूर्ण

व्योम xen_uninit_lock_cpu(पूर्णांक cpu)
अणु
	पूर्णांक irq;

	अगर (!xen_pvspin)
		वापस;

	/*
	 * When booting the kernel with 'mitigations=auto,nosmt', the secondary
	 * CPUs are not activated, and lock_kicker_irq is not initialized.
	 */
	irq = per_cpu(lock_kicker_irq, cpu);
	अगर (irq == -1)
		वापस;

	unbind_from_irqhandler(irq, शून्य);
	per_cpu(lock_kicker_irq, cpu) = -1;
	kमुक्त(per_cpu(irq_name, cpu));
	per_cpu(irq_name, cpu) = शून्य;
पूर्ण

PV_CALLEE_SAVE_REGS_THUNK(xen_vcpu_stolen);

/*
 * Our init of PV spinlocks is split in two init functions due to us
 * using paravirt patching and jump labels patching and having to करो
 * all of this beक्रमe SMP code is invoked.
 *
 * The paravirt patching needs to be करोne _beक्रमe_ the alternative यंत्र code
 * is started, otherwise we would not patch the core kernel code.
 */
व्योम __init xen_init_spinlocks(व्योम)
अणु
	/*  Don't need to use pvqspinlock code अगर there is only 1 vCPU. */
	अगर (num_possible_cpus() == 1 || nopvspin)
		xen_pvspin = false;

	अगर (!xen_pvspin) अणु
		prपूर्णांकk(KERN_DEBUG "xen: PV spinlocks disabled\n");
		अटल_branch_disable(&virt_spin_lock_key);
		वापस;
	पूर्ण
	prपूर्णांकk(KERN_DEBUG "xen: PV spinlocks enabled\n");

	__pv_init_lock_hash();
	pv_ops.lock.queued_spin_lock_slowpath = __pv_queued_spin_lock_slowpath;
	pv_ops.lock.queued_spin_unlock =
		PV_CALLEE_SAVE(__pv_queued_spin_unlock);
	pv_ops.lock.रुको = xen_qlock_रुको;
	pv_ops.lock.kick = xen_qlock_kick;
	pv_ops.lock.vcpu_is_preempted = PV_CALLEE_SAVE(xen_vcpu_stolen);
पूर्ण

अटल __init पूर्णांक xen_parse_nopvspin(अक्षर *arg)
अणु
	pr_notice("\"xen_nopvspin\" is deprecated, please use \"nopvspin\" instead\n");
	xen_pvspin = false;
	वापस 0;
पूर्ण
early_param("xen_nopvspin", xen_parse_nopvspin);

