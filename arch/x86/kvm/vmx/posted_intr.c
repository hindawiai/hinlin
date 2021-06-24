<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/kvm_host.h>

#समावेश <यंत्र/irq_remapping.h>
#समावेश <यंत्र/cpu.h>

#समावेश "lapic.h"
#समावेश "posted_intr.h"
#समावेश "trace.h"
#समावेश "vmx.h"

/*
 * We मुख्यtain a per-CPU linked-list of vCPU, so in wakeup_handler() we
 * can find which vCPU should be waken up.
 */
अटल DEFINE_PER_CPU(काष्ठा list_head, blocked_vcpu_on_cpu);
अटल DEFINE_PER_CPU(spinlock_t, blocked_vcpu_on_cpu_lock);

अटल अंतरभूत काष्ठा pi_desc *vcpu_to_pi_desc(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस &(to_vmx(vcpu)->pi_desc);
पूर्ण

व्योम vmx_vcpu_pi_load(काष्ठा kvm_vcpu *vcpu, पूर्णांक cpu)
अणु
	काष्ठा pi_desc *pi_desc = vcpu_to_pi_desc(vcpu);
	काष्ठा pi_desc old, new;
	अचिन्हित पूर्णांक dest;

	/*
	 * In हाल of hot-plug or hot-unplug, we may have to unकरो
	 * vmx_vcpu_pi_put even अगर there is no asचिन्हित device.  And we
	 * always keep PI.NDST up to date क्रम simplicity: it makes the
	 * code easier, and CPU migration is not a fast path.
	 */
	अगर (!pi_test_sn(pi_desc) && vcpu->cpu == cpu)
		वापस;

	/*
	 * If the 'nv' field is POSTED_INTR_WAKEUP_VECTOR, करो not change
	 * PI.NDST: pi_post_block is the one expected to change PID.NDST and the
	 * wakeup handler expects the vCPU to be on the blocked_vcpu_list that
	 * matches PI.NDST. Otherwise, a vcpu may not be able to be woken up
	 * correctly.
	 */
	अगर (pi_desc->nv == POSTED_INTR_WAKEUP_VECTOR || vcpu->cpu == cpu) अणु
		pi_clear_sn(pi_desc);
		जाओ after_clear_sn;
	पूर्ण

	/* The full हाल.  */
	करो अणु
		old.control = new.control = pi_desc->control;

		dest = cpu_physical_id(cpu);

		अगर (x2apic_mode)
			new.ndst = dest;
		अन्यथा
			new.ndst = (dest << 8) & 0xFF00;

		new.sn = 0;
	पूर्ण जबतक (cmpxchg64(&pi_desc->control, old.control,
			   new.control) != old.control);

after_clear_sn:

	/*
	 * Clear SN beक्रमe पढ़ोing the biपंचांगap.  The VT-d firmware
	 * ग_लिखोs the biपंचांगap and पढ़ोs SN atomically (5.2.3 in the
	 * spec), so it करोesn't really have a memory barrier that
	 * pairs with this, but we cannot करो that and we need one.
	 */
	smp_mb__after_atomic();

	अगर (!pi_is_pir_empty(pi_desc))
		pi_set_on(pi_desc);
पूर्ण

व्योम vmx_vcpu_pi_put(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा pi_desc *pi_desc = vcpu_to_pi_desc(vcpu);

	अगर (!kvm_arch_has_asचिन्हित_device(vcpu->kvm) ||
		!irq_remapping_cap(IRQ_POSTING_CAP)  ||
		!kvm_vcpu_apicv_active(vcpu))
		वापस;

	/* Set SN when the vCPU is preempted */
	अगर (vcpu->preempted)
		pi_set_sn(pi_desc);
पूर्ण

अटल व्योम __pi_post_block(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा pi_desc *pi_desc = vcpu_to_pi_desc(vcpu);
	काष्ठा pi_desc old, new;
	अचिन्हित पूर्णांक dest;

	करो अणु
		old.control = new.control = pi_desc->control;
		WARN(old.nv != POSTED_INTR_WAKEUP_VECTOR,
		     "Wakeup handler not enabled while the VCPU is blocked\n");

		dest = cpu_physical_id(vcpu->cpu);

		अगर (x2apic_mode)
			new.ndst = dest;
		अन्यथा
			new.ndst = (dest << 8) & 0xFF00;

		/* set 'NV' to 'notification vector' */
		new.nv = POSTED_INTR_VECTOR;
	पूर्ण जबतक (cmpxchg64(&pi_desc->control, old.control,
			   new.control) != old.control);

	अगर (!WARN_ON_ONCE(vcpu->pre_pcpu == -1)) अणु
		spin_lock(&per_cpu(blocked_vcpu_on_cpu_lock, vcpu->pre_pcpu));
		list_del(&vcpu->blocked_vcpu_list);
		spin_unlock(&per_cpu(blocked_vcpu_on_cpu_lock, vcpu->pre_pcpu));
		vcpu->pre_pcpu = -1;
	पूर्ण
पूर्ण

/*
 * This routine करोes the following things क्रम vCPU which is going
 * to be blocked अगर VT-d PI is enabled.
 * - Store the vCPU to the wakeup list, so when पूर्णांकerrupts happen
 *   we can find the right vCPU to wake up.
 * - Change the Posted-पूर्णांकerrupt descriptor as below:
 *      'NDST' <-- vcpu->pre_pcpu
 *      'NV' <-- POSTED_INTR_WAKEUP_VECTOR
 * - If 'ON' is set during this process, which means at least one
 *   पूर्णांकerrupt is posted क्रम this vCPU, we cannot block it, in
 *   this हाल, वापस 1, otherwise, वापस 0.
 *
 */
पूर्णांक pi_pre_block(काष्ठा kvm_vcpu *vcpu)
अणु
	अचिन्हित पूर्णांक dest;
	काष्ठा pi_desc old, new;
	काष्ठा pi_desc *pi_desc = vcpu_to_pi_desc(vcpu);

	अगर (!kvm_arch_has_asचिन्हित_device(vcpu->kvm) ||
		!irq_remapping_cap(IRQ_POSTING_CAP)  ||
		!kvm_vcpu_apicv_active(vcpu))
		वापस 0;

	WARN_ON(irqs_disabled());
	local_irq_disable();
	अगर (!WARN_ON_ONCE(vcpu->pre_pcpu != -1)) अणु
		vcpu->pre_pcpu = vcpu->cpu;
		spin_lock(&per_cpu(blocked_vcpu_on_cpu_lock, vcpu->pre_pcpu));
		list_add_tail(&vcpu->blocked_vcpu_list,
			      &per_cpu(blocked_vcpu_on_cpu,
				       vcpu->pre_pcpu));
		spin_unlock(&per_cpu(blocked_vcpu_on_cpu_lock, vcpu->pre_pcpu));
	पूर्ण

	करो अणु
		old.control = new.control = pi_desc->control;

		WARN((pi_desc->sn == 1),
		     "Warning: SN field of posted-interrupts "
		     "is set before blocking\n");

		/*
		 * Since vCPU can be preempted during this process,
		 * vcpu->cpu could be dअगरferent with pre_pcpu, we
		 * need to set pre_pcpu as the destination of wakeup
		 * notअगरication event, then we can find the right vCPU
		 * to wakeup in wakeup handler अगर पूर्णांकerrupts happen
		 * when the vCPU is in blocked state.
		 */
		dest = cpu_physical_id(vcpu->pre_pcpu);

		अगर (x2apic_mode)
			new.ndst = dest;
		अन्यथा
			new.ndst = (dest << 8) & 0xFF00;

		/* set 'NV' to 'wakeup vector' */
		new.nv = POSTED_INTR_WAKEUP_VECTOR;
	पूर्ण जबतक (cmpxchg64(&pi_desc->control, old.control,
			   new.control) != old.control);

	/* We should not block the vCPU अगर an पूर्णांकerrupt is posted क्रम it.  */
	अगर (pi_test_on(pi_desc) == 1)
		__pi_post_block(vcpu);

	local_irq_enable();
	वापस (vcpu->pre_pcpu == -1);
पूर्ण

व्योम pi_post_block(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (vcpu->pre_pcpu == -1)
		वापस;

	WARN_ON(irqs_disabled());
	local_irq_disable();
	__pi_post_block(vcpu);
	local_irq_enable();
पूर्ण

/*
 * Handler क्रम POSTED_INTERRUPT_WAKEUP_VECTOR.
 */
व्योम pi_wakeup_handler(व्योम)
अणु
	काष्ठा kvm_vcpu *vcpu;
	पूर्णांक cpu = smp_processor_id();

	spin_lock(&per_cpu(blocked_vcpu_on_cpu_lock, cpu));
	list_क्रम_each_entry(vcpu, &per_cpu(blocked_vcpu_on_cpu, cpu),
			blocked_vcpu_list) अणु
		काष्ठा pi_desc *pi_desc = vcpu_to_pi_desc(vcpu);

		अगर (pi_test_on(pi_desc) == 1)
			kvm_vcpu_kick(vcpu);
	पूर्ण
	spin_unlock(&per_cpu(blocked_vcpu_on_cpu_lock, cpu));
पूर्ण

व्योम __init pi_init_cpu(पूर्णांक cpu)
अणु
	INIT_LIST_HEAD(&per_cpu(blocked_vcpu_on_cpu, cpu));
	spin_lock_init(&per_cpu(blocked_vcpu_on_cpu_lock, cpu));
पूर्ण

bool pi_has_pending_पूर्णांकerrupt(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा pi_desc *pi_desc = vcpu_to_pi_desc(vcpu);

	वापस pi_test_on(pi_desc) ||
		(pi_test_sn(pi_desc) && !pi_is_pir_empty(pi_desc));
पूर्ण


/*
 * Bail out of the block loop अगर the VM has an asचिन्हित
 * device, but the blocking vCPU didn't reconfigure the
 * PI.NV to the wakeup vector, i.e. the asचिन्हित device
 * came aदीर्घ after the initial check in pi_pre_block().
 */
व्योम vmx_pi_start_assignment(काष्ठा kvm *kvm)
अणु
	अगर (!irq_remapping_cap(IRQ_POSTING_CAP))
		वापस;

	kvm_make_all_cpus_request(kvm, KVM_REQ_UNBLOCK);
पूर्ण

/*
 * pi_update_irte - set IRTE क्रम Posted-Interrupts
 *
 * @kvm: kvm
 * @host_irq: host irq of the पूर्णांकerrupt
 * @guest_irq: gsi of the पूर्णांकerrupt
 * @set: set or unset PI
 * वापसs 0 on success, < 0 on failure
 */
पूर्णांक pi_update_irte(काष्ठा kvm *kvm, अचिन्हित पूर्णांक host_irq, uपूर्णांक32_t guest_irq,
		   bool set)
अणु
	काष्ठा kvm_kernel_irq_routing_entry *e;
	काष्ठा kvm_irq_routing_table *irq_rt;
	काष्ठा kvm_lapic_irq irq;
	काष्ठा kvm_vcpu *vcpu;
	काष्ठा vcpu_data vcpu_info;
	पूर्णांक idx, ret = 0;

	अगर (!kvm_arch_has_asचिन्हित_device(kvm) ||
	    !irq_remapping_cap(IRQ_POSTING_CAP) ||
	    !kvm_vcpu_apicv_active(kvm->vcpus[0]))
		वापस 0;

	idx = srcu_पढ़ो_lock(&kvm->irq_srcu);
	irq_rt = srcu_dereference(kvm->irq_routing, &kvm->irq_srcu);
	अगर (guest_irq >= irq_rt->nr_rt_entries ||
	    hlist_empty(&irq_rt->map[guest_irq])) अणु
		pr_warn_once("no route for guest_irq %u/%u (broken user space?)\n",
			     guest_irq, irq_rt->nr_rt_entries);
		जाओ out;
	पूर्ण

	hlist_क्रम_each_entry(e, &irq_rt->map[guest_irq], link) अणु
		अगर (e->type != KVM_IRQ_ROUTING_MSI)
			जारी;
		/*
		 * VT-d PI cannot support posting multicast/broadcast
		 * पूर्णांकerrupts to a vCPU, we still use पूर्णांकerrupt remapping
		 * क्रम these kind of पूर्णांकerrupts.
		 *
		 * For lowest-priority पूर्णांकerrupts, we only support
		 * those with single CPU as the destination, e.g. user
		 * configures the पूर्णांकerrupts via /proc/irq or uses
		 * irqbalance to make the पूर्णांकerrupts single-CPU.
		 *
		 * We will support full lowest-priority पूर्णांकerrupt later.
		 *
		 * In addition, we can only inject generic पूर्णांकerrupts using
		 * the PI mechanism, refuse to route others through it.
		 */

		kvm_set_msi_irq(kvm, e, &irq);
		अगर (!kvm_पूर्णांकr_is_single_vcpu(kvm, &irq, &vcpu) ||
		    !kvm_irq_is_postable(&irq)) अणु
			/*
			 * Make sure the IRTE is in remapped mode अगर
			 * we करोn't handle it in posted mode.
			 */
			ret = irq_set_vcpu_affinity(host_irq, शून्य);
			अगर (ret < 0) अणु
				prपूर्णांकk(KERN_INFO
				   "failed to back to remapped mode, irq: %u\n",
				   host_irq);
				जाओ out;
			पूर्ण

			जारी;
		पूर्ण

		vcpu_info.pi_desc_addr = __pa(&to_vmx(vcpu)->pi_desc);
		vcpu_info.vector = irq.vector;

		trace_kvm_pi_irte_update(host_irq, vcpu->vcpu_id, e->gsi,
				vcpu_info.vector, vcpu_info.pi_desc_addr, set);

		अगर (set)
			ret = irq_set_vcpu_affinity(host_irq, &vcpu_info);
		अन्यथा
			ret = irq_set_vcpu_affinity(host_irq, शून्य);

		अगर (ret < 0) अणु
			prपूर्णांकk(KERN_INFO "%s: failed to update PI IRTE\n",
					__func__);
			जाओ out;
		पूर्ण
	पूर्ण

	ret = 0;
out:
	srcu_पढ़ो_unlock(&kvm->irq_srcu, idx);
	वापस ret;
पूर्ण
