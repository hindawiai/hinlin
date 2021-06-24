<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2015, 2016 ARM Ltd.
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/kvm.h>
#समावेश <linux/kvm_host.h>
#समावेश <linux/list_sort.h>
#समावेश <linux/nospec.h>

#समावेश <यंत्र/kvm_hyp.h>

#समावेश "vgic.h"

#घोषणा CREATE_TRACE_POINTS
#समावेश "trace.h"

काष्ठा vgic_global kvm_vgic_global_state __ro_after_init = अणु
	.gicv3_cpuअगर = STATIC_KEY_FALSE_INIT,
पूर्ण;

/*
 * Locking order is always:
 * kvm->lock (mutex)
 *   its->cmd_lock (mutex)
 *     its->its_lock (mutex)
 *       vgic_cpu->ap_list_lock		must be taken with IRQs disabled
 *         kvm->lpi_list_lock		must be taken with IRQs disabled
 *           vgic_irq->irq_lock		must be taken with IRQs disabled
 *
 * As the ap_list_lock might be taken from the समयr पूर्णांकerrupt handler,
 * we have to disable IRQs beक्रमe taking this lock and everything lower
 * than it.
 *
 * If you need to take multiple locks, always take the upper lock first,
 * then the lower ones, e.g. first take the its_lock, then the irq_lock.
 * If you are alपढ़ोy holding a lock and need to take a higher one, you
 * have to drop the lower ranking lock first and re-aquire it after having
 * taken the upper one.
 *
 * When taking more than one ap_list_lock at the same समय, always take the
 * lowest numbered VCPU's ap_list_lock first, so:
 *   vcpuX->vcpu_id < vcpuY->vcpu_id:
 *     raw_spin_lock(vcpuX->arch.vgic_cpu.ap_list_lock);
 *     raw_spin_lock(vcpuY->arch.vgic_cpu.ap_list_lock);
 *
 * Since the VGIC must support injecting भव पूर्णांकerrupts from ISRs, we have
 * to use the raw_spin_lock_irqsave/raw_spin_unlock_irqrestore versions of outer
 * spinlocks क्रम any lock that may be taken जबतक injecting an पूर्णांकerrupt.
 */

/*
 * Iterate over the VM's list of mapped LPIs to find the one with a
 * matching पूर्णांकerrupt ID and वापस a reference to the IRQ काष्ठाure.
 */
अटल काष्ठा vgic_irq *vgic_get_lpi(काष्ठा kvm *kvm, u32 पूर्णांकid)
अणु
	काष्ठा vgic_dist *dist = &kvm->arch.vgic;
	काष्ठा vgic_irq *irq = शून्य;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&dist->lpi_list_lock, flags);

	list_क्रम_each_entry(irq, &dist->lpi_list_head, lpi_list) अणु
		अगर (irq->पूर्णांकid != पूर्णांकid)
			जारी;

		/*
		 * This increases the refcount, the caller is expected to
		 * call vgic_put_irq() later once it's finished with the IRQ.
		 */
		vgic_get_irq_kref(irq);
		जाओ out_unlock;
	पूर्ण
	irq = शून्य;

out_unlock:
	raw_spin_unlock_irqrestore(&dist->lpi_list_lock, flags);

	वापस irq;
पूर्ण

/*
 * This looks up the भव पूर्णांकerrupt ID to get the corresponding
 * काष्ठा vgic_irq. It also increases the refcount, so any caller is expected
 * to call vgic_put_irq() once it's finished with this IRQ.
 */
काष्ठा vgic_irq *vgic_get_irq(काष्ठा kvm *kvm, काष्ठा kvm_vcpu *vcpu,
			      u32 पूर्णांकid)
अणु
	/* SGIs and PPIs */
	अगर (पूर्णांकid <= VGIC_MAX_PRIVATE) अणु
		पूर्णांकid = array_index_nospec(पूर्णांकid, VGIC_MAX_PRIVATE + 1);
		वापस &vcpu->arch.vgic_cpu.निजी_irqs[पूर्णांकid];
	पूर्ण

	/* SPIs */
	अगर (पूर्णांकid < (kvm->arch.vgic.nr_spis + VGIC_NR_PRIVATE_IRQS)) अणु
		पूर्णांकid = array_index_nospec(पूर्णांकid, kvm->arch.vgic.nr_spis + VGIC_NR_PRIVATE_IRQS);
		वापस &kvm->arch.vgic.spis[पूर्णांकid - VGIC_NR_PRIVATE_IRQS];
	पूर्ण

	/* LPIs */
	अगर (पूर्णांकid >= VGIC_MIN_LPI)
		वापस vgic_get_lpi(kvm, पूर्णांकid);

	WARN(1, "Looking up struct vgic_irq for reserved INTID");
	वापस शून्य;
पूर्ण

/*
 * We can't करो anything in here, because we lack the kvm poपूर्णांकer to
 * lock and हटाओ the item from the lpi_list. So we keep this function
 * empty and use the वापस value of kref_put() to trigger the मुक्तing.
 */
अटल व्योम vgic_irq_release(काष्ठा kref *ref)
अणु
पूर्ण

/*
 * Drop the refcount on the LPI. Must be called with lpi_list_lock held.
 */
व्योम __vgic_put_lpi_locked(काष्ठा kvm *kvm, काष्ठा vgic_irq *irq)
अणु
	काष्ठा vgic_dist *dist = &kvm->arch.vgic;

	अगर (!kref_put(&irq->refcount, vgic_irq_release))
		वापस;

	list_del(&irq->lpi_list);
	dist->lpi_list_count--;

	kमुक्त(irq);
पूर्ण

व्योम vgic_put_irq(काष्ठा kvm *kvm, काष्ठा vgic_irq *irq)
अणु
	काष्ठा vgic_dist *dist = &kvm->arch.vgic;
	अचिन्हित दीर्घ flags;

	अगर (irq->पूर्णांकid < VGIC_MIN_LPI)
		वापस;

	raw_spin_lock_irqsave(&dist->lpi_list_lock, flags);
	__vgic_put_lpi_locked(kvm, irq);
	raw_spin_unlock_irqrestore(&dist->lpi_list_lock, flags);
पूर्ण

व्योम vgic_flush_pending_lpis(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vgic_cpu *vgic_cpu = &vcpu->arch.vgic_cpu;
	काष्ठा vgic_irq *irq, *पंचांगp;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&vgic_cpu->ap_list_lock, flags);

	list_क्रम_each_entry_safe(irq, पंचांगp, &vgic_cpu->ap_list_head, ap_list) अणु
		अगर (irq->पूर्णांकid >= VGIC_MIN_LPI) अणु
			raw_spin_lock(&irq->irq_lock);
			list_del(&irq->ap_list);
			irq->vcpu = शून्य;
			raw_spin_unlock(&irq->irq_lock);
			vgic_put_irq(vcpu->kvm, irq);
		पूर्ण
	पूर्ण

	raw_spin_unlock_irqrestore(&vgic_cpu->ap_list_lock, flags);
पूर्ण

व्योम vgic_irq_set_phys_pending(काष्ठा vgic_irq *irq, bool pending)
अणु
	WARN_ON(irq_set_irqchip_state(irq->host_irq,
				      IRQCHIP_STATE_PENDING,
				      pending));
पूर्ण

bool vgic_get_phys_line_level(काष्ठा vgic_irq *irq)
अणु
	bool line_level;

	BUG_ON(!irq->hw);

	अगर (irq->get_input_level)
		वापस irq->get_input_level(irq->पूर्णांकid);

	WARN_ON(irq_get_irqchip_state(irq->host_irq,
				      IRQCHIP_STATE_PENDING,
				      &line_level));
	वापस line_level;
पूर्ण

/* Set/Clear the physical active state */
व्योम vgic_irq_set_phys_active(काष्ठा vgic_irq *irq, bool active)
अणु

	BUG_ON(!irq->hw);
	WARN_ON(irq_set_irqchip_state(irq->host_irq,
				      IRQCHIP_STATE_ACTIVE,
				      active));
पूर्ण

/**
 * kvm_vgic_target_oracle - compute the target vcpu क्रम an irq
 *
 * @irq:	The irq to route. Must be alपढ़ोy locked.
 *
 * Based on the current state of the पूर्णांकerrupt (enabled, pending,
 * active, vcpu and target_vcpu), compute the next vcpu this should be
 * given to. Return शून्य अगर this shouldn't be injected at all.
 *
 * Requires the IRQ lock to be held.
 */
अटल काष्ठा kvm_vcpu *vgic_target_oracle(काष्ठा vgic_irq *irq)
अणु
	lockdep_निश्चित_held(&irq->irq_lock);

	/* If the पूर्णांकerrupt is active, it must stay on the current vcpu */
	अगर (irq->active)
		वापस irq->vcpu ? : irq->target_vcpu;

	/*
	 * If the IRQ is not active but enabled and pending, we should direct
	 * it to its configured target VCPU.
	 * If the distributor is disabled, pending पूर्णांकerrupts shouldn't be
	 * क्रमwarded.
	 */
	अगर (irq->enabled && irq_is_pending(irq)) अणु
		अगर (unlikely(irq->target_vcpu &&
			     !irq->target_vcpu->kvm->arch.vgic.enabled))
			वापस शून्य;

		वापस irq->target_vcpu;
	पूर्ण

	/* If neither active nor pending and enabled, then this IRQ should not
	 * be queued to any VCPU.
	 */
	वापस शून्य;
पूर्ण

/*
 * The order of items in the ap_lists defines how we'll pack things in LRs as
 * well, the first items in the list being the first things populated in the
 * LRs.
 *
 * A hard rule is that active पूर्णांकerrupts can never be pushed out of the LRs
 * (and thereक्रमe take priority) since we cannot reliably trap on deactivation
 * of IRQs and thereक्रमe they have to be present in the LRs.
 *
 * Otherwise things should be sorted by the priority field and the GIC
 * hardware support will take care of preemption of priority groups etc.
 *
 * Return negative अगर "a" sorts beक्रमe "b", 0 to preserve order, and positive
 * to sort "b" beक्रमe "a".
 */
अटल पूर्णांक vgic_irq_cmp(व्योम *priv, स्थिर काष्ठा list_head *a,
			स्थिर काष्ठा list_head *b)
अणु
	काष्ठा vgic_irq *irqa = container_of(a, काष्ठा vgic_irq, ap_list);
	काष्ठा vgic_irq *irqb = container_of(b, काष्ठा vgic_irq, ap_list);
	bool penda, pendb;
	पूर्णांक ret;

	/*
	 * list_sort may call this function with the same element when
	 * the list is fairly दीर्घ.
	 */
	अगर (unlikely(irqa == irqb))
		वापस 0;

	raw_spin_lock(&irqa->irq_lock);
	raw_spin_lock_nested(&irqb->irq_lock, SINGLE_DEPTH_NESTING);

	अगर (irqa->active || irqb->active) अणु
		ret = (पूर्णांक)irqb->active - (पूर्णांक)irqa->active;
		जाओ out;
	पूर्ण

	penda = irqa->enabled && irq_is_pending(irqa);
	pendb = irqb->enabled && irq_is_pending(irqb);

	अगर (!penda || !pendb) अणु
		ret = (पूर्णांक)pendb - (पूर्णांक)penda;
		जाओ out;
	पूर्ण

	/* Both pending and enabled, sort by priority */
	ret = irqa->priority - irqb->priority;
out:
	raw_spin_unlock(&irqb->irq_lock);
	raw_spin_unlock(&irqa->irq_lock);
	वापस ret;
पूर्ण

/* Must be called with the ap_list_lock held */
अटल व्योम vgic_sort_ap_list(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vgic_cpu *vgic_cpu = &vcpu->arch.vgic_cpu;

	lockdep_निश्चित_held(&vgic_cpu->ap_list_lock);

	list_sort(शून्य, &vgic_cpu->ap_list_head, vgic_irq_cmp);
पूर्ण

/*
 * Only valid injection अगर changing level क्रम level-triggered IRQs or क्रम a
 * rising edge, and in-kernel connected IRQ lines can only be controlled by
 * their owner.
 */
अटल bool vgic_validate_injection(काष्ठा vgic_irq *irq, bool level, व्योम *owner)
अणु
	अगर (irq->owner != owner)
		वापस false;

	चयन (irq->config) अणु
	हाल VGIC_CONFIG_LEVEL:
		वापस irq->line_level != level;
	हाल VGIC_CONFIG_EDGE:
		वापस level;
	पूर्ण

	वापस false;
पूर्ण

/*
 * Check whether an IRQ needs to (and can) be queued to a VCPU's ap list.
 * Do the queuing अगर necessary, taking the right locks in the right order.
 * Returns true when the IRQ was queued, false otherwise.
 *
 * Needs to be entered with the IRQ lock alपढ़ोy held, but will वापस
 * with all locks dropped.
 */
bool vgic_queue_irq_unlock(काष्ठा kvm *kvm, काष्ठा vgic_irq *irq,
			   अचिन्हित दीर्घ flags)
अणु
	काष्ठा kvm_vcpu *vcpu;

	lockdep_निश्चित_held(&irq->irq_lock);

retry:
	vcpu = vgic_target_oracle(irq);
	अगर (irq->vcpu || !vcpu) अणु
		/*
		 * If this IRQ is alपढ़ोy on a VCPU's ap_list, then it
		 * cannot be moved or modअगरied and there is no more work क्रम
		 * us to करो.
		 *
		 * Otherwise, अगर the irq is not pending and enabled, it करोes
		 * not need to be inserted पूर्णांकo an ap_list and there is also
		 * no more work क्रम us to करो.
		 */
		raw_spin_unlock_irqrestore(&irq->irq_lock, flags);

		/*
		 * We have to kick the VCPU here, because we could be
		 * queueing an edge-triggered पूर्णांकerrupt क्रम which we
		 * get no EOI मुख्यtenance पूर्णांकerrupt. In that हाल,
		 * जबतक the IRQ is alपढ़ोy on the VCPU's AP list, the
		 * VCPU could have EOI'ed the original पूर्णांकerrupt and
		 * won't see this one until it निकासs क्रम some other
		 * reason.
		 */
		अगर (vcpu) अणु
			kvm_make_request(KVM_REQ_IRQ_PENDING, vcpu);
			kvm_vcpu_kick(vcpu);
		पूर्ण
		वापस false;
	पूर्ण

	/*
	 * We must unlock the irq lock to take the ap_list_lock where
	 * we are going to insert this new pending पूर्णांकerrupt.
	 */
	raw_spin_unlock_irqrestore(&irq->irq_lock, flags);

	/* someone can करो stuff here, which we re-check below */

	raw_spin_lock_irqsave(&vcpu->arch.vgic_cpu.ap_list_lock, flags);
	raw_spin_lock(&irq->irq_lock);

	/*
	 * Did something change behind our backs?
	 *
	 * There are two हालs:
	 * 1) The irq lost its pending state or was disabled behind our
	 *    backs and/or it was queued to another VCPU's ap_list.
	 * 2) Someone changed the affinity on this irq behind our
	 *    backs and we are now holding the wrong ap_list_lock.
	 *
	 * In both हालs, drop the locks and retry.
	 */

	अगर (unlikely(irq->vcpu || vcpu != vgic_target_oracle(irq))) अणु
		raw_spin_unlock(&irq->irq_lock);
		raw_spin_unlock_irqrestore(&vcpu->arch.vgic_cpu.ap_list_lock,
					   flags);

		raw_spin_lock_irqsave(&irq->irq_lock, flags);
		जाओ retry;
	पूर्ण

	/*
	 * Grab a reference to the irq to reflect the fact that it is
	 * now in the ap_list.
	 */
	vgic_get_irq_kref(irq);
	list_add_tail(&irq->ap_list, &vcpu->arch.vgic_cpu.ap_list_head);
	irq->vcpu = vcpu;

	raw_spin_unlock(&irq->irq_lock);
	raw_spin_unlock_irqrestore(&vcpu->arch.vgic_cpu.ap_list_lock, flags);

	kvm_make_request(KVM_REQ_IRQ_PENDING, vcpu);
	kvm_vcpu_kick(vcpu);

	वापस true;
पूर्ण

/**
 * kvm_vgic_inject_irq - Inject an IRQ from a device to the vgic
 * @kvm:     The VM काष्ठाure poपूर्णांकer
 * @cpuid:   The CPU क्रम PPIs
 * @पूर्णांकid:   The INTID to inject a new state to.
 * @level:   Edge-triggered:  true:  to trigger the पूर्णांकerrupt
 *			      false: to ignore the call
 *	     Level-sensitive  true:  उठाओ the input संकेत
 *			      false: lower the input संकेत
 * @owner:   The opaque poपूर्णांकer to the owner of the IRQ being उठाओd to verअगरy
 *           that the caller is allowed to inject this IRQ.  Userspace
 *           injections will have owner == शून्य.
 *
 * The VGIC is not concerned with devices being active-LOW or active-HIGH क्रम
 * level-sensitive पूर्णांकerrupts.  You can think of the level parameter as 1
 * being HIGH and 0 being LOW and all devices being active-HIGH.
 */
पूर्णांक kvm_vgic_inject_irq(काष्ठा kvm *kvm, पूर्णांक cpuid, अचिन्हित पूर्णांक पूर्णांकid,
			bool level, व्योम *owner)
अणु
	काष्ठा kvm_vcpu *vcpu;
	काष्ठा vgic_irq *irq;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	trace_vgic_update_irq_pending(cpuid, पूर्णांकid, level);

	ret = vgic_lazy_init(kvm);
	अगर (ret)
		वापस ret;

	vcpu = kvm_get_vcpu(kvm, cpuid);
	अगर (!vcpu && पूर्णांकid < VGIC_NR_PRIVATE_IRQS)
		वापस -EINVAL;

	irq = vgic_get_irq(kvm, vcpu, पूर्णांकid);
	अगर (!irq)
		वापस -EINVAL;

	raw_spin_lock_irqsave(&irq->irq_lock, flags);

	अगर (!vgic_validate_injection(irq, level, owner)) अणु
		/* Nothing to see here, move aदीर्घ... */
		raw_spin_unlock_irqrestore(&irq->irq_lock, flags);
		vgic_put_irq(kvm, irq);
		वापस 0;
	पूर्ण

	अगर (irq->config == VGIC_CONFIG_LEVEL)
		irq->line_level = level;
	अन्यथा
		irq->pending_latch = true;

	vgic_queue_irq_unlock(kvm, irq, flags);
	vgic_put_irq(kvm, irq);

	वापस 0;
पूर्ण

/* @irq->irq_lock must be held */
अटल पूर्णांक kvm_vgic_map_irq(काष्ठा kvm_vcpu *vcpu, काष्ठा vgic_irq *irq,
			    अचिन्हित पूर्णांक host_irq,
			    bool (*get_input_level)(पूर्णांक vindid))
अणु
	काष्ठा irq_desc *desc;
	काष्ठा irq_data *data;

	/*
	 * Find the physical IRQ number corresponding to @host_irq
	 */
	desc = irq_to_desc(host_irq);
	अगर (!desc) अणु
		kvm_err("%s: no interrupt descriptor\n", __func__);
		वापस -EINVAL;
	पूर्ण
	data = irq_desc_get_irq_data(desc);
	जबतक (data->parent_data)
		data = data->parent_data;

	irq->hw = true;
	irq->host_irq = host_irq;
	irq->hwपूर्णांकid = data->hwirq;
	irq->get_input_level = get_input_level;
	वापस 0;
पूर्ण

/* @irq->irq_lock must be held */
अटल अंतरभूत व्योम kvm_vgic_unmap_irq(काष्ठा vgic_irq *irq)
अणु
	irq->hw = false;
	irq->hwपूर्णांकid = 0;
	irq->get_input_level = शून्य;
पूर्ण

पूर्णांक kvm_vgic_map_phys_irq(काष्ठा kvm_vcpu *vcpu, अचिन्हित पूर्णांक host_irq,
			  u32 vपूर्णांकid, bool (*get_input_level)(पूर्णांक vindid))
अणु
	काष्ठा vgic_irq *irq = vgic_get_irq(vcpu->kvm, vcpu, vपूर्णांकid);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	BUG_ON(!irq);

	raw_spin_lock_irqsave(&irq->irq_lock, flags);
	ret = kvm_vgic_map_irq(vcpu, irq, host_irq, get_input_level);
	raw_spin_unlock_irqrestore(&irq->irq_lock, flags);
	vgic_put_irq(vcpu->kvm, irq);

	वापस ret;
पूर्ण

/**
 * kvm_vgic_reset_mapped_irq - Reset a mapped IRQ
 * @vcpu: The VCPU poपूर्णांकer
 * @vपूर्णांकid: The INTID of the पूर्णांकerrupt
 *
 * Reset the active and pending states of a mapped पूर्णांकerrupt.  Kernel
 * subप्रणालीs injecting mapped पूर्णांकerrupts should reset their पूर्णांकerrupt lines
 * when we are करोing a reset of the VM.
 */
व्योम kvm_vgic_reset_mapped_irq(काष्ठा kvm_vcpu *vcpu, u32 vपूर्णांकid)
अणु
	काष्ठा vgic_irq *irq = vgic_get_irq(vcpu->kvm, vcpu, vपूर्णांकid);
	अचिन्हित दीर्घ flags;

	अगर (!irq->hw)
		जाओ out;

	raw_spin_lock_irqsave(&irq->irq_lock, flags);
	irq->active = false;
	irq->pending_latch = false;
	irq->line_level = false;
	raw_spin_unlock_irqrestore(&irq->irq_lock, flags);
out:
	vgic_put_irq(vcpu->kvm, irq);
पूर्ण

पूर्णांक kvm_vgic_unmap_phys_irq(काष्ठा kvm_vcpu *vcpu, अचिन्हित पूर्णांक vपूर्णांकid)
अणु
	काष्ठा vgic_irq *irq;
	अचिन्हित दीर्घ flags;

	अगर (!vgic_initialized(vcpu->kvm))
		वापस -EAGAIN;

	irq = vgic_get_irq(vcpu->kvm, vcpu, vपूर्णांकid);
	BUG_ON(!irq);

	raw_spin_lock_irqsave(&irq->irq_lock, flags);
	kvm_vgic_unmap_irq(irq);
	raw_spin_unlock_irqrestore(&irq->irq_lock, flags);
	vgic_put_irq(vcpu->kvm, irq);

	वापस 0;
पूर्ण

/**
 * kvm_vgic_set_owner - Set the owner of an पूर्णांकerrupt क्रम a VM
 *
 * @vcpu:   Poपूर्णांकer to the VCPU (used क्रम PPIs)
 * @पूर्णांकid:  The भव INTID identअगरying the पूर्णांकerrupt (PPI or SPI)
 * @owner:  Opaque poपूर्णांकer to the owner
 *
 * Returns 0 अगर पूर्णांकid is not alपढ़ोy used by another in-kernel device and the
 * owner is set, otherwise वापसs an error code.
 */
पूर्णांक kvm_vgic_set_owner(काष्ठा kvm_vcpu *vcpu, अचिन्हित पूर्णांक पूर्णांकid, व्योम *owner)
अणु
	काष्ठा vgic_irq *irq;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	अगर (!vgic_initialized(vcpu->kvm))
		वापस -EAGAIN;

	/* SGIs and LPIs cannot be wired up to any device */
	अगर (!irq_is_ppi(पूर्णांकid) && !vgic_valid_spi(vcpu->kvm, पूर्णांकid))
		वापस -EINVAL;

	irq = vgic_get_irq(vcpu->kvm, vcpu, पूर्णांकid);
	raw_spin_lock_irqsave(&irq->irq_lock, flags);
	अगर (irq->owner && irq->owner != owner)
		ret = -EEXIST;
	अन्यथा
		irq->owner = owner;
	raw_spin_unlock_irqrestore(&irq->irq_lock, flags);

	वापस ret;
पूर्ण

/**
 * vgic_prune_ap_list - Remove non-relevant पूर्णांकerrupts from the list
 *
 * @vcpu: The VCPU poपूर्णांकer
 *
 * Go over the list of "interesting" पूर्णांकerrupts, and prune those that we
 * won't have to consider in the near future.
 */
अटल व्योम vgic_prune_ap_list(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vgic_cpu *vgic_cpu = &vcpu->arch.vgic_cpu;
	काष्ठा vgic_irq *irq, *पंचांगp;

	DEBUG_SPINLOCK_BUG_ON(!irqs_disabled());

retry:
	raw_spin_lock(&vgic_cpu->ap_list_lock);

	list_क्रम_each_entry_safe(irq, पंचांगp, &vgic_cpu->ap_list_head, ap_list) अणु
		काष्ठा kvm_vcpu *target_vcpu, *vcpuA, *vcpuB;
		bool target_vcpu_needs_kick = false;

		raw_spin_lock(&irq->irq_lock);

		BUG_ON(vcpu != irq->vcpu);

		target_vcpu = vgic_target_oracle(irq);

		अगर (!target_vcpu) अणु
			/*
			 * We करोn't need to process this पूर्णांकerrupt any
			 * further, move it off the list.
			 */
			list_del(&irq->ap_list);
			irq->vcpu = शून्य;
			raw_spin_unlock(&irq->irq_lock);

			/*
			 * This vgic_put_irq call matches the
			 * vgic_get_irq_kref in vgic_queue_irq_unlock,
			 * where we added the LPI to the ap_list. As
			 * we हटाओ the irq from the list, we drop
			 * also drop the refcount.
			 */
			vgic_put_irq(vcpu->kvm, irq);
			जारी;
		पूर्ण

		अगर (target_vcpu == vcpu) अणु
			/* We're on the right CPU */
			raw_spin_unlock(&irq->irq_lock);
			जारी;
		पूर्ण

		/* This पूर्णांकerrupt looks like it has to be migrated. */

		raw_spin_unlock(&irq->irq_lock);
		raw_spin_unlock(&vgic_cpu->ap_list_lock);

		/*
		 * Ensure locking order by always locking the smallest
		 * ID first.
		 */
		अगर (vcpu->vcpu_id < target_vcpu->vcpu_id) अणु
			vcpuA = vcpu;
			vcpuB = target_vcpu;
		पूर्ण अन्यथा अणु
			vcpuA = target_vcpu;
			vcpuB = vcpu;
		पूर्ण

		raw_spin_lock(&vcpuA->arch.vgic_cpu.ap_list_lock);
		raw_spin_lock_nested(&vcpuB->arch.vgic_cpu.ap_list_lock,
				      SINGLE_DEPTH_NESTING);
		raw_spin_lock(&irq->irq_lock);

		/*
		 * If the affinity has been preserved, move the
		 * पूर्णांकerrupt around. Otherwise, it means things have
		 * changed जबतक the पूर्णांकerrupt was unlocked, and we
		 * need to replay this.
		 *
		 * In all हालs, we cannot trust the list not to have
		 * changed, so we restart from the beginning.
		 */
		अगर (target_vcpu == vgic_target_oracle(irq)) अणु
			काष्ठा vgic_cpu *new_cpu = &target_vcpu->arch.vgic_cpu;

			list_del(&irq->ap_list);
			irq->vcpu = target_vcpu;
			list_add_tail(&irq->ap_list, &new_cpu->ap_list_head);
			target_vcpu_needs_kick = true;
		पूर्ण

		raw_spin_unlock(&irq->irq_lock);
		raw_spin_unlock(&vcpuB->arch.vgic_cpu.ap_list_lock);
		raw_spin_unlock(&vcpuA->arch.vgic_cpu.ap_list_lock);

		अगर (target_vcpu_needs_kick) अणु
			kvm_make_request(KVM_REQ_IRQ_PENDING, target_vcpu);
			kvm_vcpu_kick(target_vcpu);
		पूर्ण

		जाओ retry;
	पूर्ण

	raw_spin_unlock(&vgic_cpu->ap_list_lock);
पूर्ण

अटल अंतरभूत व्योम vgic_fold_lr_state(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (kvm_vgic_global_state.type == VGIC_V2)
		vgic_v2_fold_lr_state(vcpu);
	अन्यथा
		vgic_v3_fold_lr_state(vcpu);
पूर्ण

/* Requires the irq_lock to be held. */
अटल अंतरभूत व्योम vgic_populate_lr(काष्ठा kvm_vcpu *vcpu,
				    काष्ठा vgic_irq *irq, पूर्णांक lr)
अणु
	lockdep_निश्चित_held(&irq->irq_lock);

	अगर (kvm_vgic_global_state.type == VGIC_V2)
		vgic_v2_populate_lr(vcpu, irq, lr);
	अन्यथा
		vgic_v3_populate_lr(vcpu, irq, lr);
पूर्ण

अटल अंतरभूत व्योम vgic_clear_lr(काष्ठा kvm_vcpu *vcpu, पूर्णांक lr)
अणु
	अगर (kvm_vgic_global_state.type == VGIC_V2)
		vgic_v2_clear_lr(vcpu, lr);
	अन्यथा
		vgic_v3_clear_lr(vcpu, lr);
पूर्ण

अटल अंतरभूत व्योम vgic_set_underflow(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (kvm_vgic_global_state.type == VGIC_V2)
		vgic_v2_set_underflow(vcpu);
	अन्यथा
		vgic_v3_set_underflow(vcpu);
पूर्ण

/* Requires the ap_list_lock to be held. */
अटल पूर्णांक compute_ap_list_depth(काष्ठा kvm_vcpu *vcpu,
				 bool *multi_sgi)
अणु
	काष्ठा vgic_cpu *vgic_cpu = &vcpu->arch.vgic_cpu;
	काष्ठा vgic_irq *irq;
	पूर्णांक count = 0;

	*multi_sgi = false;

	lockdep_निश्चित_held(&vgic_cpu->ap_list_lock);

	list_क्रम_each_entry(irq, &vgic_cpu->ap_list_head, ap_list) अणु
		पूर्णांक w;

		raw_spin_lock(&irq->irq_lock);
		/* GICv2 SGIs can count क्रम more than one... */
		w = vgic_irq_get_lr_count(irq);
		raw_spin_unlock(&irq->irq_lock);

		count += w;
		*multi_sgi |= (w > 1);
	पूर्ण
	वापस count;
पूर्ण

/* Requires the VCPU's ap_list_lock to be held. */
अटल व्योम vgic_flush_lr_state(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vgic_cpu *vgic_cpu = &vcpu->arch.vgic_cpu;
	काष्ठा vgic_irq *irq;
	पूर्णांक count;
	bool multi_sgi;
	u8 prio = 0xff;
	पूर्णांक i = 0;

	lockdep_निश्चित_held(&vgic_cpu->ap_list_lock);

	count = compute_ap_list_depth(vcpu, &multi_sgi);
	अगर (count > kvm_vgic_global_state.nr_lr || multi_sgi)
		vgic_sort_ap_list(vcpu);

	count = 0;

	list_क्रम_each_entry(irq, &vgic_cpu->ap_list_head, ap_list) अणु
		raw_spin_lock(&irq->irq_lock);

		/*
		 * If we have multi-SGIs in the pipeline, we need to
		 * guarantee that they are all seen beक्रमe any IRQ of
		 * lower priority. In that हाल, we need to filter out
		 * these पूर्णांकerrupts by निकासing early. This is easy as
		 * the AP list has been sorted alपढ़ोy.
		 */
		अगर (multi_sgi && irq->priority > prio) अणु
			_raw_spin_unlock(&irq->irq_lock);
			अवरोध;
		पूर्ण

		अगर (likely(vgic_target_oracle(irq) == vcpu)) अणु
			vgic_populate_lr(vcpu, irq, count++);

			अगर (irq->source)
				prio = irq->priority;
		पूर्ण

		raw_spin_unlock(&irq->irq_lock);

		अगर (count == kvm_vgic_global_state.nr_lr) अणु
			अगर (!list_is_last(&irq->ap_list,
					  &vgic_cpu->ap_list_head))
				vgic_set_underflow(vcpu);
			अवरोध;
		पूर्ण
	पूर्ण

	/* Nuke reमुख्यing LRs */
	क्रम (i = count ; i < kvm_vgic_global_state.nr_lr; i++)
		vgic_clear_lr(vcpu, i);

	अगर (!अटल_branch_unlikely(&kvm_vgic_global_state.gicv3_cpuअगर))
		vcpu->arch.vgic_cpu.vgic_v2.used_lrs = count;
	अन्यथा
		vcpu->arch.vgic_cpu.vgic_v3.used_lrs = count;
पूर्ण

अटल अंतरभूत bool can_access_vgic_from_kernel(व्योम)
अणु
	/*
	 * GICv2 can always be accessed from the kernel because it is
	 * memory-mapped, and VHE प्रणालीs can access GICv3 EL2 प्रणाली
	 * रेजिस्टरs.
	 */
	वापस !अटल_branch_unlikely(&kvm_vgic_global_state.gicv3_cpuअगर) || has_vhe();
पूर्ण

अटल अंतरभूत व्योम vgic_save_state(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (!अटल_branch_unlikely(&kvm_vgic_global_state.gicv3_cpuअगर))
		vgic_v2_save_state(vcpu);
	अन्यथा
		__vgic_v3_save_state(&vcpu->arch.vgic_cpu.vgic_v3);
पूर्ण

/* Sync back the hardware VGIC state पूर्णांकo our emulation after a guest's run. */
व्योम kvm_vgic_sync_hwstate(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक used_lrs;

	/* An empty ap_list_head implies used_lrs == 0 */
	अगर (list_empty(&vcpu->arch.vgic_cpu.ap_list_head))
		वापस;

	अगर (can_access_vgic_from_kernel())
		vgic_save_state(vcpu);

	अगर (!अटल_branch_unlikely(&kvm_vgic_global_state.gicv3_cpuअगर))
		used_lrs = vcpu->arch.vgic_cpu.vgic_v2.used_lrs;
	अन्यथा
		used_lrs = vcpu->arch.vgic_cpu.vgic_v3.used_lrs;

	अगर (used_lrs)
		vgic_fold_lr_state(vcpu);
	vgic_prune_ap_list(vcpu);
पूर्ण

अटल अंतरभूत व्योम vgic_restore_state(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (!अटल_branch_unlikely(&kvm_vgic_global_state.gicv3_cpuअगर))
		vgic_v2_restore_state(vcpu);
	अन्यथा
		__vgic_v3_restore_state(&vcpu->arch.vgic_cpu.vgic_v3);
पूर्ण

/* Flush our emulation state पूर्णांकo the GIC hardware beक्रमe entering the guest. */
व्योम kvm_vgic_flush_hwstate(काष्ठा kvm_vcpu *vcpu)
अणु
	/*
	 * If there are no भव पूर्णांकerrupts active or pending क्रम this
	 * VCPU, then there is no work to करो and we can bail out without
	 * taking any lock.  There is a potential race with someone injecting
	 * पूर्णांकerrupts to the VCPU, but it is a benign race as the VCPU will
	 * either observe the new पूर्णांकerrupt beक्रमe or after करोing this check,
	 * and पूर्णांकroducing additional synchronization mechanism करोesn't change
	 * this.
	 *
	 * Note that we still need to go through the whole thing अगर anything
	 * can be directly injected (GICv4).
	 */
	अगर (list_empty(&vcpu->arch.vgic_cpu.ap_list_head) &&
	    !vgic_supports_direct_msis(vcpu->kvm))
		वापस;

	DEBUG_SPINLOCK_BUG_ON(!irqs_disabled());

	अगर (!list_empty(&vcpu->arch.vgic_cpu.ap_list_head)) अणु
		raw_spin_lock(&vcpu->arch.vgic_cpu.ap_list_lock);
		vgic_flush_lr_state(vcpu);
		raw_spin_unlock(&vcpu->arch.vgic_cpu.ap_list_lock);
	पूर्ण

	अगर (can_access_vgic_from_kernel())
		vgic_restore_state(vcpu);

	अगर (vgic_supports_direct_msis(vcpu->kvm))
		vgic_v4_commit(vcpu);
पूर्ण

व्योम kvm_vgic_load(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (unlikely(!vgic_initialized(vcpu->kvm)))
		वापस;

	अगर (kvm_vgic_global_state.type == VGIC_V2)
		vgic_v2_load(vcpu);
	अन्यथा
		vgic_v3_load(vcpu);
पूर्ण

व्योम kvm_vgic_put(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (unlikely(!vgic_initialized(vcpu->kvm)))
		वापस;

	अगर (kvm_vgic_global_state.type == VGIC_V2)
		vgic_v2_put(vcpu);
	अन्यथा
		vgic_v3_put(vcpu);
पूर्ण

व्योम kvm_vgic_vmcr_sync(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (unlikely(!irqchip_in_kernel(vcpu->kvm)))
		वापस;

	अगर (kvm_vgic_global_state.type == VGIC_V2)
		vgic_v2_vmcr_sync(vcpu);
	अन्यथा
		vgic_v3_vmcr_sync(vcpu);
पूर्ण

पूर्णांक kvm_vgic_vcpu_pending_irq(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vgic_cpu *vgic_cpu = &vcpu->arch.vgic_cpu;
	काष्ठा vgic_irq *irq;
	bool pending = false;
	अचिन्हित दीर्घ flags;
	काष्ठा vgic_vmcr vmcr;

	अगर (!vcpu->kvm->arch.vgic.enabled)
		वापस false;

	अगर (vcpu->arch.vgic_cpu.vgic_v3.its_vpe.pending_last)
		वापस true;

	vgic_get_vmcr(vcpu, &vmcr);

	raw_spin_lock_irqsave(&vgic_cpu->ap_list_lock, flags);

	list_क्रम_each_entry(irq, &vgic_cpu->ap_list_head, ap_list) अणु
		raw_spin_lock(&irq->irq_lock);
		pending = irq_is_pending(irq) && irq->enabled &&
			  !irq->active &&
			  irq->priority < vmcr.pmr;
		raw_spin_unlock(&irq->irq_lock);

		अगर (pending)
			अवरोध;
	पूर्ण

	raw_spin_unlock_irqrestore(&vgic_cpu->ap_list_lock, flags);

	वापस pending;
पूर्ण

व्योम vgic_kick_vcpus(काष्ठा kvm *kvm)
अणु
	काष्ठा kvm_vcpu *vcpu;
	पूर्णांक c;

	/*
	 * We've injected an पूर्णांकerrupt, समय to find out who deserves
	 * a good kick...
	 */
	kvm_क्रम_each_vcpu(c, vcpu, kvm) अणु
		अगर (kvm_vgic_vcpu_pending_irq(vcpu)) अणु
			kvm_make_request(KVM_REQ_IRQ_PENDING, vcpu);
			kvm_vcpu_kick(vcpu);
		पूर्ण
	पूर्ण
पूर्ण

bool kvm_vgic_map_is_active(काष्ठा kvm_vcpu *vcpu, अचिन्हित पूर्णांक vपूर्णांकid)
अणु
	काष्ठा vgic_irq *irq;
	bool map_is_active;
	अचिन्हित दीर्घ flags;

	अगर (!vgic_initialized(vcpu->kvm))
		वापस false;

	irq = vgic_get_irq(vcpu->kvm, vcpu, vपूर्णांकid);
	raw_spin_lock_irqsave(&irq->irq_lock, flags);
	map_is_active = irq->hw && irq->active;
	raw_spin_unlock_irqrestore(&irq->irq_lock, flags);
	vgic_put_irq(vcpu->kvm, irq);

	वापस map_is_active;
पूर्ण
