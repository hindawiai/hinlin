<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * VGIC MMIO handling functions
 */

#समावेश <linux/bitops.h>
#समावेश <linux/द्वा_खोज.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/kvm.h>
#समावेश <linux/kvm_host.h>
#समावेश <kvm/iodev.h>
#समावेश <kvm/arm_arch_समयr.h>
#समावेश <kvm/arm_vgic.h>

#समावेश "vgic.h"
#समावेश "vgic-mmio.h"

अचिन्हित दीर्घ vgic_mmio_पढ़ो_raz(काष्ठा kvm_vcpu *vcpu,
				 gpa_t addr, अचिन्हित पूर्णांक len)
अणु
	वापस 0;
पूर्ण

अचिन्हित दीर्घ vgic_mmio_पढ़ो_rao(काष्ठा kvm_vcpu *vcpu,
				 gpa_t addr, अचिन्हित पूर्णांक len)
अणु
	वापस -1UL;
पूर्ण

व्योम vgic_mmio_ग_लिखो_wi(काष्ठा kvm_vcpu *vcpu, gpa_t addr,
			अचिन्हित पूर्णांक len, अचिन्हित दीर्घ val)
अणु
	/* Ignore */
पूर्ण

पूर्णांक vgic_mmio_uaccess_ग_लिखो_wi(काष्ठा kvm_vcpu *vcpu, gpa_t addr,
			       अचिन्हित पूर्णांक len, अचिन्हित दीर्घ val)
अणु
	/* Ignore */
	वापस 0;
पूर्ण

अचिन्हित दीर्घ vgic_mmio_पढ़ो_group(काष्ठा kvm_vcpu *vcpu,
				   gpa_t addr, अचिन्हित पूर्णांक len)
अणु
	u32 पूर्णांकid = VGIC_ADDR_TO_INTID(addr, 1);
	u32 value = 0;
	पूर्णांक i;

	/* Loop over all IRQs affected by this पढ़ो */
	क्रम (i = 0; i < len * 8; i++) अणु
		काष्ठा vgic_irq *irq = vgic_get_irq(vcpu->kvm, vcpu, पूर्णांकid + i);

		अगर (irq->group)
			value |= BIT(i);

		vgic_put_irq(vcpu->kvm, irq);
	पूर्ण

	वापस value;
पूर्ण

अटल व्योम vgic_update_vsgi(काष्ठा vgic_irq *irq)
अणु
	WARN_ON(its_prop_update_vsgi(irq->host_irq, irq->priority, irq->group));
पूर्ण

व्योम vgic_mmio_ग_लिखो_group(काष्ठा kvm_vcpu *vcpu, gpa_t addr,
			   अचिन्हित पूर्णांक len, अचिन्हित दीर्घ val)
अणु
	u32 पूर्णांकid = VGIC_ADDR_TO_INTID(addr, 1);
	पूर्णांक i;
	अचिन्हित दीर्घ flags;

	क्रम (i = 0; i < len * 8; i++) अणु
		काष्ठा vgic_irq *irq = vgic_get_irq(vcpu->kvm, vcpu, पूर्णांकid + i);

		raw_spin_lock_irqsave(&irq->irq_lock, flags);
		irq->group = !!(val & BIT(i));
		अगर (irq->hw && vgic_irq_is_sgi(irq->पूर्णांकid)) अणु
			vgic_update_vsgi(irq);
			raw_spin_unlock_irqrestore(&irq->irq_lock, flags);
		पूर्ण अन्यथा अणु
			vgic_queue_irq_unlock(vcpu->kvm, irq, flags);
		पूर्ण

		vgic_put_irq(vcpu->kvm, irq);
	पूर्ण
पूर्ण

/*
 * Read accesses to both GICD_ICENABLER and GICD_ISENABLER वापस the value
 * of the enabled bit, so there is only one function क्रम both here.
 */
अचिन्हित दीर्घ vgic_mmio_पढ़ो_enable(काष्ठा kvm_vcpu *vcpu,
				    gpa_t addr, अचिन्हित पूर्णांक len)
अणु
	u32 पूर्णांकid = VGIC_ADDR_TO_INTID(addr, 1);
	u32 value = 0;
	पूर्णांक i;

	/* Loop over all IRQs affected by this पढ़ो */
	क्रम (i = 0; i < len * 8; i++) अणु
		काष्ठा vgic_irq *irq = vgic_get_irq(vcpu->kvm, vcpu, पूर्णांकid + i);

		अगर (irq->enabled)
			value |= (1U << i);

		vgic_put_irq(vcpu->kvm, irq);
	पूर्ण

	वापस value;
पूर्ण

व्योम vgic_mmio_ग_लिखो_senable(काष्ठा kvm_vcpu *vcpu,
			     gpa_t addr, अचिन्हित पूर्णांक len,
			     अचिन्हित दीर्घ val)
अणु
	u32 पूर्णांकid = VGIC_ADDR_TO_INTID(addr, 1);
	पूर्णांक i;
	अचिन्हित दीर्घ flags;

	क्रम_each_set_bit(i, &val, len * 8) अणु
		काष्ठा vgic_irq *irq = vgic_get_irq(vcpu->kvm, vcpu, पूर्णांकid + i);

		raw_spin_lock_irqsave(&irq->irq_lock, flags);
		अगर (irq->hw && vgic_irq_is_sgi(irq->पूर्णांकid)) अणु
			अगर (!irq->enabled) अणु
				काष्ठा irq_data *data;

				irq->enabled = true;
				data = &irq_to_desc(irq->host_irq)->irq_data;
				जबतक (irqd_irq_disabled(data))
					enable_irq(irq->host_irq);
			पूर्ण

			raw_spin_unlock_irqrestore(&irq->irq_lock, flags);
			vgic_put_irq(vcpu->kvm, irq);

			जारी;
		पूर्ण अन्यथा अगर (vgic_irq_is_mapped_level(irq)) अणु
			bool was_high = irq->line_level;

			/*
			 * We need to update the state of the पूर्णांकerrupt because
			 * the guest might have changed the state of the device
			 * जबतक the पूर्णांकerrupt was disabled at the VGIC level.
			 */
			irq->line_level = vgic_get_phys_line_level(irq);
			/*
			 * Deactivate the physical पूर्णांकerrupt so the GIC will let
			 * us know when it is निश्चितed again.
			 */
			अगर (!irq->active && was_high && !irq->line_level)
				vgic_irq_set_phys_active(irq, false);
		पूर्ण
		irq->enabled = true;
		vgic_queue_irq_unlock(vcpu->kvm, irq, flags);

		vgic_put_irq(vcpu->kvm, irq);
	पूर्ण
पूर्ण

व्योम vgic_mmio_ग_लिखो_cenable(काष्ठा kvm_vcpu *vcpu,
			     gpa_t addr, अचिन्हित पूर्णांक len,
			     अचिन्हित दीर्घ val)
अणु
	u32 पूर्णांकid = VGIC_ADDR_TO_INTID(addr, 1);
	पूर्णांक i;
	अचिन्हित दीर्घ flags;

	क्रम_each_set_bit(i, &val, len * 8) अणु
		काष्ठा vgic_irq *irq = vgic_get_irq(vcpu->kvm, vcpu, पूर्णांकid + i);

		raw_spin_lock_irqsave(&irq->irq_lock, flags);
		अगर (irq->hw && vgic_irq_is_sgi(irq->पूर्णांकid) && irq->enabled)
			disable_irq_nosync(irq->host_irq);

		irq->enabled = false;

		raw_spin_unlock_irqrestore(&irq->irq_lock, flags);
		vgic_put_irq(vcpu->kvm, irq);
	पूर्ण
पूर्ण

पूर्णांक vgic_uaccess_ग_लिखो_senable(काष्ठा kvm_vcpu *vcpu,
			       gpa_t addr, अचिन्हित पूर्णांक len,
			       अचिन्हित दीर्घ val)
अणु
	u32 पूर्णांकid = VGIC_ADDR_TO_INTID(addr, 1);
	पूर्णांक i;
	अचिन्हित दीर्घ flags;

	क्रम_each_set_bit(i, &val, len * 8) अणु
		काष्ठा vgic_irq *irq = vgic_get_irq(vcpu->kvm, vcpu, पूर्णांकid + i);

		raw_spin_lock_irqsave(&irq->irq_lock, flags);
		irq->enabled = true;
		vgic_queue_irq_unlock(vcpu->kvm, irq, flags);

		vgic_put_irq(vcpu->kvm, irq);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक vgic_uaccess_ग_लिखो_cenable(काष्ठा kvm_vcpu *vcpu,
			       gpa_t addr, अचिन्हित पूर्णांक len,
			       अचिन्हित दीर्घ val)
अणु
	u32 पूर्णांकid = VGIC_ADDR_TO_INTID(addr, 1);
	पूर्णांक i;
	अचिन्हित दीर्घ flags;

	क्रम_each_set_bit(i, &val, len * 8) अणु
		काष्ठा vgic_irq *irq = vgic_get_irq(vcpu->kvm, vcpu, पूर्णांकid + i);

		raw_spin_lock_irqsave(&irq->irq_lock, flags);
		irq->enabled = false;
		raw_spin_unlock_irqrestore(&irq->irq_lock, flags);

		vgic_put_irq(vcpu->kvm, irq);
	पूर्ण

	वापस 0;
पूर्ण

अचिन्हित दीर्घ vgic_mmio_पढ़ो_pending(काष्ठा kvm_vcpu *vcpu,
				     gpa_t addr, अचिन्हित पूर्णांक len)
अणु
	u32 पूर्णांकid = VGIC_ADDR_TO_INTID(addr, 1);
	u32 value = 0;
	पूर्णांक i;

	/* Loop over all IRQs affected by this पढ़ो */
	क्रम (i = 0; i < len * 8; i++) अणु
		काष्ठा vgic_irq *irq = vgic_get_irq(vcpu->kvm, vcpu, पूर्णांकid + i);
		अचिन्हित दीर्घ flags;
		bool val;

		raw_spin_lock_irqsave(&irq->irq_lock, flags);
		अगर (irq->hw && vgic_irq_is_sgi(irq->पूर्णांकid)) अणु
			पूर्णांक err;

			val = false;
			err = irq_get_irqchip_state(irq->host_irq,
						    IRQCHIP_STATE_PENDING,
						    &val);
			WARN_RATELIMIT(err, "IRQ %d", irq->host_irq);
		पूर्ण अन्यथा अणु
			val = irq_is_pending(irq);
		पूर्ण

		value |= ((u32)val << i);
		raw_spin_unlock_irqrestore(&irq->irq_lock, flags);

		vgic_put_irq(vcpu->kvm, irq);
	पूर्ण

	वापस value;
पूर्ण

अटल bool is_vgic_v2_sgi(काष्ठा kvm_vcpu *vcpu, काष्ठा vgic_irq *irq)
अणु
	वापस (vgic_irq_is_sgi(irq->पूर्णांकid) &&
		vcpu->kvm->arch.vgic.vgic_model == KVM_DEV_TYPE_ARM_VGIC_V2);
पूर्ण

व्योम vgic_mmio_ग_लिखो_spending(काष्ठा kvm_vcpu *vcpu,
			      gpa_t addr, अचिन्हित पूर्णांक len,
			      अचिन्हित दीर्घ val)
अणु
	u32 पूर्णांकid = VGIC_ADDR_TO_INTID(addr, 1);
	पूर्णांक i;
	अचिन्हित दीर्घ flags;

	क्रम_each_set_bit(i, &val, len * 8) अणु
		काष्ठा vgic_irq *irq = vgic_get_irq(vcpu->kvm, vcpu, पूर्णांकid + i);

		/* GICD_ISPENDR0 SGI bits are WI */
		अगर (is_vgic_v2_sgi(vcpu, irq)) अणु
			vgic_put_irq(vcpu->kvm, irq);
			जारी;
		पूर्ण

		raw_spin_lock_irqsave(&irq->irq_lock, flags);

		अगर (irq->hw && vgic_irq_is_sgi(irq->पूर्णांकid)) अणु
			/* HW SGI? Ask the GIC to inject it */
			पूर्णांक err;
			err = irq_set_irqchip_state(irq->host_irq,
						    IRQCHIP_STATE_PENDING,
						    true);
			WARN_RATELIMIT(err, "IRQ %d", irq->host_irq);

			raw_spin_unlock_irqrestore(&irq->irq_lock, flags);
			vgic_put_irq(vcpu->kvm, irq);

			जारी;
		पूर्ण

		irq->pending_latch = true;
		अगर (irq->hw)
			vgic_irq_set_phys_active(irq, true);

		vgic_queue_irq_unlock(vcpu->kvm, irq, flags);
		vgic_put_irq(vcpu->kvm, irq);
	पूर्ण
पूर्ण

पूर्णांक vgic_uaccess_ग_लिखो_spending(काष्ठा kvm_vcpu *vcpu,
				gpa_t addr, अचिन्हित पूर्णांक len,
				अचिन्हित दीर्घ val)
अणु
	u32 पूर्णांकid = VGIC_ADDR_TO_INTID(addr, 1);
	पूर्णांक i;
	अचिन्हित दीर्घ flags;

	क्रम_each_set_bit(i, &val, len * 8) अणु
		काष्ठा vgic_irq *irq = vgic_get_irq(vcpu->kvm, vcpu, पूर्णांकid + i);

		raw_spin_lock_irqsave(&irq->irq_lock, flags);
		irq->pending_latch = true;

		/*
		 * GICv2 SGIs are terribly broken. We can't restore
		 * the source of the पूर्णांकerrupt, so just pick the vcpu
		 * itself as the source...
		 */
		अगर (is_vgic_v2_sgi(vcpu, irq))
			irq->source |= BIT(vcpu->vcpu_id);

		vgic_queue_irq_unlock(vcpu->kvm, irq, flags);

		vgic_put_irq(vcpu->kvm, irq);
	पूर्ण

	वापस 0;
पूर्ण

/* Must be called with irq->irq_lock held */
अटल व्योम vgic_hw_irq_cpending(काष्ठा kvm_vcpu *vcpu, काष्ठा vgic_irq *irq)
अणु
	irq->pending_latch = false;

	/*
	 * We करोn't want the guest to effectively mask the physical
	 * पूर्णांकerrupt by करोing a ग_लिखो to SPENDR followed by a ग_लिखो to
	 * CPENDR क्रम HW पूर्णांकerrupts, so we clear the active state on
	 * the physical side अगर the भव पूर्णांकerrupt is not active.
	 * This may lead to taking an additional पूर्णांकerrupt on the
	 * host, but that should not be a problem as the worst that
	 * can happen is an additional vgic injection.  We also clear
	 * the pending state to मुख्यtain proper semantics क्रम edge HW
	 * पूर्णांकerrupts.
	 */
	vgic_irq_set_phys_pending(irq, false);
	अगर (!irq->active)
		vgic_irq_set_phys_active(irq, false);
पूर्ण

व्योम vgic_mmio_ग_लिखो_cpending(काष्ठा kvm_vcpu *vcpu,
			      gpa_t addr, अचिन्हित पूर्णांक len,
			      अचिन्हित दीर्घ val)
अणु
	u32 पूर्णांकid = VGIC_ADDR_TO_INTID(addr, 1);
	पूर्णांक i;
	अचिन्हित दीर्घ flags;

	क्रम_each_set_bit(i, &val, len * 8) अणु
		काष्ठा vgic_irq *irq = vgic_get_irq(vcpu->kvm, vcpu, पूर्णांकid + i);

		/* GICD_ICPENDR0 SGI bits are WI */
		अगर (is_vgic_v2_sgi(vcpu, irq)) अणु
			vgic_put_irq(vcpu->kvm, irq);
			जारी;
		पूर्ण

		raw_spin_lock_irqsave(&irq->irq_lock, flags);

		अगर (irq->hw && vgic_irq_is_sgi(irq->पूर्णांकid)) अणु
			/* HW SGI? Ask the GIC to clear its pending bit */
			पूर्णांक err;
			err = irq_set_irqchip_state(irq->host_irq,
						    IRQCHIP_STATE_PENDING,
						    false);
			WARN_RATELIMIT(err, "IRQ %d", irq->host_irq);

			raw_spin_unlock_irqrestore(&irq->irq_lock, flags);
			vgic_put_irq(vcpu->kvm, irq);

			जारी;
		पूर्ण

		अगर (irq->hw)
			vgic_hw_irq_cpending(vcpu, irq);
		अन्यथा
			irq->pending_latch = false;

		raw_spin_unlock_irqrestore(&irq->irq_lock, flags);
		vgic_put_irq(vcpu->kvm, irq);
	पूर्ण
पूर्ण

पूर्णांक vgic_uaccess_ग_लिखो_cpending(काष्ठा kvm_vcpu *vcpu,
				gpa_t addr, अचिन्हित पूर्णांक len,
				अचिन्हित दीर्घ val)
अणु
	u32 पूर्णांकid = VGIC_ADDR_TO_INTID(addr, 1);
	पूर्णांक i;
	अचिन्हित दीर्घ flags;

	क्रम_each_set_bit(i, &val, len * 8) अणु
		काष्ठा vgic_irq *irq = vgic_get_irq(vcpu->kvm, vcpu, पूर्णांकid + i);

		raw_spin_lock_irqsave(&irq->irq_lock, flags);
		/*
		 * More fun with GICv2 SGIs! If we're clearing one of them
		 * from userspace, which source vcpu to clear? Let's not
		 * even think of it, and blow the whole set.
		 */
		अगर (is_vgic_v2_sgi(vcpu, irq))
			irq->source = 0;

		irq->pending_latch = false;

		raw_spin_unlock_irqrestore(&irq->irq_lock, flags);

		vgic_put_irq(vcpu->kvm, irq);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * If we are fiddling with an IRQ's active state, we have to make sure the IRQ
 * is not queued on some running VCPU's LRs, because then the change to the
 * active state can be overwritten when the VCPU's state is synced coming back
 * from the guest.
 *
 * For shared पूर्णांकerrupts as well as GICv3 निजी पूर्णांकerrupts, we have to
 * stop all the VCPUs because पूर्णांकerrupts can be migrated जबतक we करोn't hold
 * the IRQ locks and we करोn't want to be chasing moving tarमाला_लो.
 *
 * For GICv2 निजी पूर्णांकerrupts we करोn't have to करो anything because
 * userspace accesses to the VGIC state alपढ़ोy require all VCPUs to be
 * stopped, and only the VCPU itself can modअगरy its निजी पूर्णांकerrupts
 * active state, which guarantees that the VCPU is not running.
 */
अटल व्योम vgic_access_active_prepare(काष्ठा kvm_vcpu *vcpu, u32 पूर्णांकid)
अणु
	अगर (vcpu->kvm->arch.vgic.vgic_model == KVM_DEV_TYPE_ARM_VGIC_V3 ||
	    पूर्णांकid >= VGIC_NR_PRIVATE_IRQS)
		kvm_arm_halt_guest(vcpu->kvm);
पूर्ण

/* See vgic_access_active_prepare */
अटल व्योम vgic_access_active_finish(काष्ठा kvm_vcpu *vcpu, u32 पूर्णांकid)
अणु
	अगर (vcpu->kvm->arch.vgic.vgic_model == KVM_DEV_TYPE_ARM_VGIC_V3 ||
	    पूर्णांकid >= VGIC_NR_PRIVATE_IRQS)
		kvm_arm_resume_guest(vcpu->kvm);
पूर्ण

अटल अचिन्हित दीर्घ __vgic_mmio_पढ़ो_active(काष्ठा kvm_vcpu *vcpu,
					     gpa_t addr, अचिन्हित पूर्णांक len)
अणु
	u32 पूर्णांकid = VGIC_ADDR_TO_INTID(addr, 1);
	u32 value = 0;
	पूर्णांक i;

	/* Loop over all IRQs affected by this पढ़ो */
	क्रम (i = 0; i < len * 8; i++) अणु
		काष्ठा vgic_irq *irq = vgic_get_irq(vcpu->kvm, vcpu, पूर्णांकid + i);

		/*
		 * Even क्रम HW पूर्णांकerrupts, करोn't evaluate the HW state as
		 * all the guest is पूर्णांकerested in is the भव state.
		 */
		अगर (irq->active)
			value |= (1U << i);

		vgic_put_irq(vcpu->kvm, irq);
	पूर्ण

	वापस value;
पूर्ण

अचिन्हित दीर्घ vgic_mmio_पढ़ो_active(काष्ठा kvm_vcpu *vcpu,
				    gpa_t addr, अचिन्हित पूर्णांक len)
अणु
	u32 पूर्णांकid = VGIC_ADDR_TO_INTID(addr, 1);
	u32 val;

	mutex_lock(&vcpu->kvm->lock);
	vgic_access_active_prepare(vcpu, पूर्णांकid);

	val = __vgic_mmio_पढ़ो_active(vcpu, addr, len);

	vgic_access_active_finish(vcpu, पूर्णांकid);
	mutex_unlock(&vcpu->kvm->lock);

	वापस val;
पूर्ण

अचिन्हित दीर्घ vgic_uaccess_पढ़ो_active(काष्ठा kvm_vcpu *vcpu,
				    gpa_t addr, अचिन्हित पूर्णांक len)
अणु
	वापस __vgic_mmio_पढ़ो_active(vcpu, addr, len);
पूर्ण

/* Must be called with irq->irq_lock held */
अटल व्योम vgic_hw_irq_change_active(काष्ठा kvm_vcpu *vcpu, काष्ठा vgic_irq *irq,
				      bool active, bool is_uaccess)
अणु
	अगर (is_uaccess)
		वापस;

	irq->active = active;
	vgic_irq_set_phys_active(irq, active);
पूर्ण

अटल व्योम vgic_mmio_change_active(काष्ठा kvm_vcpu *vcpu, काष्ठा vgic_irq *irq,
				    bool active)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा kvm_vcpu *requester_vcpu = kvm_get_running_vcpu();

	raw_spin_lock_irqsave(&irq->irq_lock, flags);

	अगर (irq->hw && !vgic_irq_is_sgi(irq->पूर्णांकid)) अणु
		vgic_hw_irq_change_active(vcpu, irq, active, !requester_vcpu);
	पूर्ण अन्यथा अगर (irq->hw && vgic_irq_is_sgi(irq->पूर्णांकid)) अणु
		/*
		 * GICv4.1 VSGI feature करोesn't track an active state,
		 * so let's not kid ourselves, there is nothing we can
		 * करो here.
		 */
		irq->active = false;
	पूर्ण अन्यथा अणु
		u32 model = vcpu->kvm->arch.vgic.vgic_model;
		u8 active_source;

		irq->active = active;

		/*
		 * The GICv2 architecture indicates that the source CPUID क्रम
		 * an SGI should be provided during an EOI which implies that
		 * the active state is stored somewhere, but at the same समय
		 * this state is not architecturally exposed anywhere and we
		 * have no way of knowing the right source.
		 *
		 * This may lead to a VCPU not being able to receive
		 * additional instances of a particular SGI after migration
		 * क्रम a GICv2 VM on some GIC implementations.  Oh well.
		 */
		active_source = (requester_vcpu) ? requester_vcpu->vcpu_id : 0;

		अगर (model == KVM_DEV_TYPE_ARM_VGIC_V2 &&
		    active && vgic_irq_is_sgi(irq->पूर्णांकid))
			irq->active_source = active_source;
	पूर्ण

	अगर (irq->active)
		vgic_queue_irq_unlock(vcpu->kvm, irq, flags);
	अन्यथा
		raw_spin_unlock_irqrestore(&irq->irq_lock, flags);
पूर्ण

अटल व्योम __vgic_mmio_ग_लिखो_cactive(काष्ठा kvm_vcpu *vcpu,
				      gpa_t addr, अचिन्हित पूर्णांक len,
				      अचिन्हित दीर्घ val)
अणु
	u32 पूर्णांकid = VGIC_ADDR_TO_INTID(addr, 1);
	पूर्णांक i;

	क्रम_each_set_bit(i, &val, len * 8) अणु
		काष्ठा vgic_irq *irq = vgic_get_irq(vcpu->kvm, vcpu, पूर्णांकid + i);
		vgic_mmio_change_active(vcpu, irq, false);
		vgic_put_irq(vcpu->kvm, irq);
	पूर्ण
पूर्ण

व्योम vgic_mmio_ग_लिखो_cactive(काष्ठा kvm_vcpu *vcpu,
			     gpa_t addr, अचिन्हित पूर्णांक len,
			     अचिन्हित दीर्घ val)
अणु
	u32 पूर्णांकid = VGIC_ADDR_TO_INTID(addr, 1);

	mutex_lock(&vcpu->kvm->lock);
	vgic_access_active_prepare(vcpu, पूर्णांकid);

	__vgic_mmio_ग_लिखो_cactive(vcpu, addr, len, val);

	vgic_access_active_finish(vcpu, पूर्णांकid);
	mutex_unlock(&vcpu->kvm->lock);
पूर्ण

पूर्णांक vgic_mmio_uaccess_ग_लिखो_cactive(काष्ठा kvm_vcpu *vcpu,
				     gpa_t addr, अचिन्हित पूर्णांक len,
				     अचिन्हित दीर्घ val)
अणु
	__vgic_mmio_ग_लिखो_cactive(vcpu, addr, len, val);
	वापस 0;
पूर्ण

अटल व्योम __vgic_mmio_ग_लिखो_sactive(काष्ठा kvm_vcpu *vcpu,
				      gpa_t addr, अचिन्हित पूर्णांक len,
				      अचिन्हित दीर्घ val)
अणु
	u32 पूर्णांकid = VGIC_ADDR_TO_INTID(addr, 1);
	पूर्णांक i;

	क्रम_each_set_bit(i, &val, len * 8) अणु
		काष्ठा vgic_irq *irq = vgic_get_irq(vcpu->kvm, vcpu, पूर्णांकid + i);
		vgic_mmio_change_active(vcpu, irq, true);
		vgic_put_irq(vcpu->kvm, irq);
	पूर्ण
पूर्ण

व्योम vgic_mmio_ग_लिखो_sactive(काष्ठा kvm_vcpu *vcpu,
			     gpa_t addr, अचिन्हित पूर्णांक len,
			     अचिन्हित दीर्घ val)
अणु
	u32 पूर्णांकid = VGIC_ADDR_TO_INTID(addr, 1);

	mutex_lock(&vcpu->kvm->lock);
	vgic_access_active_prepare(vcpu, पूर्णांकid);

	__vgic_mmio_ग_लिखो_sactive(vcpu, addr, len, val);

	vgic_access_active_finish(vcpu, पूर्णांकid);
	mutex_unlock(&vcpu->kvm->lock);
पूर्ण

पूर्णांक vgic_mmio_uaccess_ग_लिखो_sactive(काष्ठा kvm_vcpu *vcpu,
				     gpa_t addr, अचिन्हित पूर्णांक len,
				     अचिन्हित दीर्घ val)
अणु
	__vgic_mmio_ग_लिखो_sactive(vcpu, addr, len, val);
	वापस 0;
पूर्ण

अचिन्हित दीर्घ vgic_mmio_पढ़ो_priority(काष्ठा kvm_vcpu *vcpu,
				      gpa_t addr, अचिन्हित पूर्णांक len)
अणु
	u32 पूर्णांकid = VGIC_ADDR_TO_INTID(addr, 8);
	पूर्णांक i;
	u64 val = 0;

	क्रम (i = 0; i < len; i++) अणु
		काष्ठा vgic_irq *irq = vgic_get_irq(vcpu->kvm, vcpu, पूर्णांकid + i);

		val |= (u64)irq->priority << (i * 8);

		vgic_put_irq(vcpu->kvm, irq);
	पूर्ण

	वापस val;
पूर्ण

/*
 * We currently करोn't handle changing the priority of an पूर्णांकerrupt that
 * is alपढ़ोy pending on a VCPU. If there is a need क्रम this, we would
 * need to make this VCPU निकास and re-evaluate the priorities, potentially
 * leading to this पूर्णांकerrupt getting presented now to the guest (अगर it has
 * been masked by the priority mask beक्रमe).
 */
व्योम vgic_mmio_ग_लिखो_priority(काष्ठा kvm_vcpu *vcpu,
			      gpa_t addr, अचिन्हित पूर्णांक len,
			      अचिन्हित दीर्घ val)
अणु
	u32 पूर्णांकid = VGIC_ADDR_TO_INTID(addr, 8);
	पूर्णांक i;
	अचिन्हित दीर्घ flags;

	क्रम (i = 0; i < len; i++) अणु
		काष्ठा vgic_irq *irq = vgic_get_irq(vcpu->kvm, vcpu, पूर्णांकid + i);

		raw_spin_lock_irqsave(&irq->irq_lock, flags);
		/* Narrow the priority range to what we actually support */
		irq->priority = (val >> (i * 8)) & GENMASK(7, 8 - VGIC_PRI_BITS);
		अगर (irq->hw && vgic_irq_is_sgi(irq->पूर्णांकid))
			vgic_update_vsgi(irq);
		raw_spin_unlock_irqrestore(&irq->irq_lock, flags);

		vgic_put_irq(vcpu->kvm, irq);
	पूर्ण
पूर्ण

अचिन्हित दीर्घ vgic_mmio_पढ़ो_config(काष्ठा kvm_vcpu *vcpu,
				    gpa_t addr, अचिन्हित पूर्णांक len)
अणु
	u32 पूर्णांकid = VGIC_ADDR_TO_INTID(addr, 2);
	u32 value = 0;
	पूर्णांक i;

	क्रम (i = 0; i < len * 4; i++) अणु
		काष्ठा vgic_irq *irq = vgic_get_irq(vcpu->kvm, vcpu, पूर्णांकid + i);

		अगर (irq->config == VGIC_CONFIG_EDGE)
			value |= (2U << (i * 2));

		vgic_put_irq(vcpu->kvm, irq);
	पूर्ण

	वापस value;
पूर्ण

व्योम vgic_mmio_ग_लिखो_config(काष्ठा kvm_vcpu *vcpu,
			    gpa_t addr, अचिन्हित पूर्णांक len,
			    अचिन्हित दीर्घ val)
अणु
	u32 पूर्णांकid = VGIC_ADDR_TO_INTID(addr, 2);
	पूर्णांक i;
	अचिन्हित दीर्घ flags;

	क्रम (i = 0; i < len * 4; i++) अणु
		काष्ठा vgic_irq *irq;

		/*
		 * The configuration cannot be changed क्रम SGIs in general,
		 * क्रम PPIs this is IMPLEMENTATION DEFINED. The arch समयr
		 * code relies on PPIs being level triggered, so we also
		 * make them पढ़ो-only here.
		 */
		अगर (पूर्णांकid + i < VGIC_NR_PRIVATE_IRQS)
			जारी;

		irq = vgic_get_irq(vcpu->kvm, vcpu, पूर्णांकid + i);
		raw_spin_lock_irqsave(&irq->irq_lock, flags);

		अगर (test_bit(i * 2 + 1, &val))
			irq->config = VGIC_CONFIG_EDGE;
		अन्यथा
			irq->config = VGIC_CONFIG_LEVEL;

		raw_spin_unlock_irqrestore(&irq->irq_lock, flags);
		vgic_put_irq(vcpu->kvm, irq);
	पूर्ण
पूर्ण

u64 vgic_पढ़ो_irq_line_level_info(काष्ठा kvm_vcpu *vcpu, u32 पूर्णांकid)
अणु
	पूर्णांक i;
	u64 val = 0;
	पूर्णांक nr_irqs = vcpu->kvm->arch.vgic.nr_spis + VGIC_NR_PRIVATE_IRQS;

	क्रम (i = 0; i < 32; i++) अणु
		काष्ठा vgic_irq *irq;

		अगर ((पूर्णांकid + i) < VGIC_NR_SGIS || (पूर्णांकid + i) >= nr_irqs)
			जारी;

		irq = vgic_get_irq(vcpu->kvm, vcpu, पूर्णांकid + i);
		अगर (irq->config == VGIC_CONFIG_LEVEL && irq->line_level)
			val |= (1U << i);

		vgic_put_irq(vcpu->kvm, irq);
	पूर्ण

	वापस val;
पूर्ण

व्योम vgic_ग_लिखो_irq_line_level_info(काष्ठा kvm_vcpu *vcpu, u32 पूर्णांकid,
				    स्थिर u64 val)
अणु
	पूर्णांक i;
	पूर्णांक nr_irqs = vcpu->kvm->arch.vgic.nr_spis + VGIC_NR_PRIVATE_IRQS;
	अचिन्हित दीर्घ flags;

	क्रम (i = 0; i < 32; i++) अणु
		काष्ठा vgic_irq *irq;
		bool new_level;

		अगर ((पूर्णांकid + i) < VGIC_NR_SGIS || (पूर्णांकid + i) >= nr_irqs)
			जारी;

		irq = vgic_get_irq(vcpu->kvm, vcpu, पूर्णांकid + i);

		/*
		 * Line level is set irrespective of irq type
		 * (level or edge) to aव्योम dependency that VM should
		 * restore irq config beक्रमe line level.
		 */
		new_level = !!(val & (1U << i));
		raw_spin_lock_irqsave(&irq->irq_lock, flags);
		irq->line_level = new_level;
		अगर (new_level)
			vgic_queue_irq_unlock(vcpu->kvm, irq, flags);
		अन्यथा
			raw_spin_unlock_irqrestore(&irq->irq_lock, flags);

		vgic_put_irq(vcpu->kvm, irq);
	पूर्ण
पूर्ण

अटल पूर्णांक match_region(स्थिर व्योम *key, स्थिर व्योम *elt)
अणु
	स्थिर अचिन्हित पूर्णांक offset = (अचिन्हित दीर्घ)key;
	स्थिर काष्ठा vgic_रेजिस्टर_region *region = elt;

	अगर (offset < region->reg_offset)
		वापस -1;

	अगर (offset >= region->reg_offset + region->len)
		वापस 1;

	वापस 0;
पूर्ण

स्थिर काष्ठा vgic_रेजिस्टर_region *
vgic_find_mmio_region(स्थिर काष्ठा vgic_रेजिस्टर_region *regions,
		      पूर्णांक nr_regions, अचिन्हित पूर्णांक offset)
अणु
	वापस द्वा_खोज((व्योम *)(uपूर्णांकptr_t)offset, regions, nr_regions,
		       माप(regions[0]), match_region);
पूर्ण

व्योम vgic_set_vmcr(काष्ठा kvm_vcpu *vcpu, काष्ठा vgic_vmcr *vmcr)
अणु
	अगर (kvm_vgic_global_state.type == VGIC_V2)
		vgic_v2_set_vmcr(vcpu, vmcr);
	अन्यथा
		vgic_v3_set_vmcr(vcpu, vmcr);
पूर्ण

व्योम vgic_get_vmcr(काष्ठा kvm_vcpu *vcpu, काष्ठा vgic_vmcr *vmcr)
अणु
	अगर (kvm_vgic_global_state.type == VGIC_V2)
		vgic_v2_get_vmcr(vcpu, vmcr);
	अन्यथा
		vgic_v3_get_vmcr(vcpu, vmcr);
पूर्ण

/*
 * kvm_mmio_पढ़ो_buf() वापसs a value in a क्रमmat where it can be converted
 * to a byte array and be directly observed as the guest wanted it to appear
 * in memory अगर it had करोne the store itself, which is LE क्रम the GIC, as the
 * guest knows the GIC is always LE.
 *
 * We convert this value to the CPUs native क्रमmat to deal with it as a data
 * value.
 */
अचिन्हित दीर्घ vgic_data_mmio_bus_to_host(स्थिर व्योम *val, अचिन्हित पूर्णांक len)
अणु
	अचिन्हित दीर्घ data = kvm_mmio_पढ़ो_buf(val, len);

	चयन (len) अणु
	हाल 1:
		वापस data;
	हाल 2:
		वापस le16_to_cpu(data);
	हाल 4:
		वापस le32_to_cpu(data);
	शेष:
		वापस le64_to_cpu(data);
	पूर्ण
पूर्ण

/*
 * kvm_mmio_ग_लिखो_buf() expects a value in a क्रमmat such that अगर converted to
 * a byte array it is observed as the guest would see it अगर it could perक्रमm
 * the load directly.  Since the GIC is LE, and the guest knows this, the
 * guest expects a value in little endian क्रमmat.
 *
 * We convert the data value from the CPUs native क्रमmat to LE so that the
 * value is वापसed in the proper क्रमmat.
 */
व्योम vgic_data_host_to_mmio_bus(व्योम *buf, अचिन्हित पूर्णांक len,
				अचिन्हित दीर्घ data)
अणु
	चयन (len) अणु
	हाल 1:
		अवरोध;
	हाल 2:
		data = cpu_to_le16(data);
		अवरोध;
	हाल 4:
		data = cpu_to_le32(data);
		अवरोध;
	शेष:
		data = cpu_to_le64(data);
	पूर्ण

	kvm_mmio_ग_लिखो_buf(buf, len, data);
पूर्ण

अटल
काष्ठा vgic_io_device *kvm_to_vgic_iodev(स्थिर काष्ठा kvm_io_device *dev)
अणु
	वापस container_of(dev, काष्ठा vgic_io_device, dev);
पूर्ण

अटल bool check_region(स्थिर काष्ठा kvm *kvm,
			 स्थिर काष्ठा vgic_रेजिस्टर_region *region,
			 gpa_t addr, पूर्णांक len)
अणु
	पूर्णांक flags, nr_irqs = kvm->arch.vgic.nr_spis + VGIC_NR_PRIVATE_IRQS;

	चयन (len) अणु
	हाल माप(u8):
		flags = VGIC_ACCESS_8bit;
		अवरोध;
	हाल माप(u32):
		flags = VGIC_ACCESS_32bit;
		अवरोध;
	हाल माप(u64):
		flags = VGIC_ACCESS_64bit;
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	अगर ((region->access_flags & flags) && IS_ALIGNED(addr, len)) अणु
		अगर (!region->bits_per_irq)
			वापस true;

		/* Do we access a non-allocated IRQ? */
		वापस VGIC_ADDR_TO_INTID(addr, region->bits_per_irq) < nr_irqs;
	पूर्ण

	वापस false;
पूर्ण

स्थिर काष्ठा vgic_रेजिस्टर_region *
vgic_get_mmio_region(काष्ठा kvm_vcpu *vcpu, काष्ठा vgic_io_device *iodev,
		     gpa_t addr, पूर्णांक len)
अणु
	स्थिर काष्ठा vgic_रेजिस्टर_region *region;

	region = vgic_find_mmio_region(iodev->regions, iodev->nr_regions,
				       addr - iodev->base_addr);
	अगर (!region || !check_region(vcpu->kvm, region, addr, len))
		वापस शून्य;

	वापस region;
पूर्ण

अटल पूर्णांक vgic_uaccess_पढ़ो(काष्ठा kvm_vcpu *vcpu, काष्ठा vgic_io_device *iodev,
			     gpa_t addr, u32 *val)
अणु
	स्थिर काष्ठा vgic_रेजिस्टर_region *region;
	काष्ठा kvm_vcpu *r_vcpu;

	region = vgic_get_mmio_region(vcpu, iodev, addr, माप(u32));
	अगर (!region) अणु
		*val = 0;
		वापस 0;
	पूर्ण

	r_vcpu = iodev->redist_vcpu ? iodev->redist_vcpu : vcpu;
	अगर (region->uaccess_पढ़ो)
		*val = region->uaccess_पढ़ो(r_vcpu, addr, माप(u32));
	अन्यथा
		*val = region->पढ़ो(r_vcpu, addr, माप(u32));

	वापस 0;
पूर्ण

अटल पूर्णांक vgic_uaccess_ग_लिखो(काष्ठा kvm_vcpu *vcpu, काष्ठा vgic_io_device *iodev,
			      gpa_t addr, स्थिर u32 *val)
अणु
	स्थिर काष्ठा vgic_रेजिस्टर_region *region;
	काष्ठा kvm_vcpu *r_vcpu;

	region = vgic_get_mmio_region(vcpu, iodev, addr, माप(u32));
	अगर (!region)
		वापस 0;

	r_vcpu = iodev->redist_vcpu ? iodev->redist_vcpu : vcpu;
	अगर (region->uaccess_ग_लिखो)
		वापस region->uaccess_ग_लिखो(r_vcpu, addr, माप(u32), *val);

	region->ग_लिखो(r_vcpu, addr, माप(u32), *val);
	वापस 0;
पूर्ण

/*
 * Userland access to VGIC रेजिस्टरs.
 */
पूर्णांक vgic_uaccess(काष्ठा kvm_vcpu *vcpu, काष्ठा vgic_io_device *dev,
		 bool is_ग_लिखो, पूर्णांक offset, u32 *val)
अणु
	अगर (is_ग_लिखो)
		वापस vgic_uaccess_ग_लिखो(vcpu, dev, offset, val);
	अन्यथा
		वापस vgic_uaccess_पढ़ो(vcpu, dev, offset, val);
पूर्ण

अटल पूर्णांक dispatch_mmio_पढ़ो(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_io_device *dev,
			      gpa_t addr, पूर्णांक len, व्योम *val)
अणु
	काष्ठा vgic_io_device *iodev = kvm_to_vgic_iodev(dev);
	स्थिर काष्ठा vgic_रेजिस्टर_region *region;
	अचिन्हित दीर्घ data = 0;

	region = vgic_get_mmio_region(vcpu, iodev, addr, len);
	अगर (!region) अणु
		स_रखो(val, 0, len);
		वापस 0;
	पूर्ण

	चयन (iodev->iodev_type) अणु
	हाल IODEV_CPUIF:
		data = region->पढ़ो(vcpu, addr, len);
		अवरोध;
	हाल IODEV_DIST:
		data = region->पढ़ो(vcpu, addr, len);
		अवरोध;
	हाल IODEV_REDIST:
		data = region->पढ़ो(iodev->redist_vcpu, addr, len);
		अवरोध;
	हाल IODEV_ITS:
		data = region->its_पढ़ो(vcpu->kvm, iodev->its, addr, len);
		अवरोध;
	पूर्ण

	vgic_data_host_to_mmio_bus(val, len, data);
	वापस 0;
पूर्ण

अटल पूर्णांक dispatch_mmio_ग_लिखो(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_io_device *dev,
			       gpa_t addr, पूर्णांक len, स्थिर व्योम *val)
अणु
	काष्ठा vgic_io_device *iodev = kvm_to_vgic_iodev(dev);
	स्थिर काष्ठा vgic_रेजिस्टर_region *region;
	अचिन्हित दीर्घ data = vgic_data_mmio_bus_to_host(val, len);

	region = vgic_get_mmio_region(vcpu, iodev, addr, len);
	अगर (!region)
		वापस 0;

	चयन (iodev->iodev_type) अणु
	हाल IODEV_CPUIF:
		region->ग_लिखो(vcpu, addr, len, data);
		अवरोध;
	हाल IODEV_DIST:
		region->ग_लिखो(vcpu, addr, len, data);
		अवरोध;
	हाल IODEV_REDIST:
		region->ग_लिखो(iodev->redist_vcpu, addr, len, data);
		अवरोध;
	हाल IODEV_ITS:
		region->its_ग_लिखो(vcpu->kvm, iodev->its, addr, len, data);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा kvm_io_device_ops kvm_io_gic_ops = अणु
	.पढ़ो = dispatch_mmio_पढ़ो,
	.ग_लिखो = dispatch_mmio_ग_लिखो,
पूर्ण;

पूर्णांक vgic_रेजिस्टर_dist_iodev(काष्ठा kvm *kvm, gpa_t dist_base_address,
			     क्रमागत vgic_type type)
अणु
	काष्ठा vgic_io_device *io_device = &kvm->arch.vgic.dist_iodev;
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक len;

	चयन (type) अणु
	हाल VGIC_V2:
		len = vgic_v2_init_dist_iodev(io_device);
		अवरोध;
	हाल VGIC_V3:
		len = vgic_v3_init_dist_iodev(io_device);
		अवरोध;
	शेष:
		BUG_ON(1);
	पूर्ण

	io_device->base_addr = dist_base_address;
	io_device->iodev_type = IODEV_DIST;
	io_device->redist_vcpu = शून्य;

	mutex_lock(&kvm->slots_lock);
	ret = kvm_io_bus_रेजिस्टर_dev(kvm, KVM_MMIO_BUS, dist_base_address,
				      len, &io_device->dev);
	mutex_unlock(&kvm->slots_lock);

	वापस ret;
पूर्ण
