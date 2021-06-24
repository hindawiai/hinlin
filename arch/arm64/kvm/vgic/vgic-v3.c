<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

#समावेश <linux/irqchip/arm-gic-v3.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/kvm.h>
#समावेश <linux/kvm_host.h>
#समावेश <kvm/arm_vgic.h>
#समावेश <यंत्र/kvm_hyp.h>
#समावेश <यंत्र/kvm_mmu.h>
#समावेश <यंत्र/kvm_यंत्र.h>

#समावेश "vgic.h"

अटल bool group0_trap;
अटल bool group1_trap;
अटल bool common_trap;
अटल bool gicv4_enable;

व्योम vgic_v3_set_underflow(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vgic_v3_cpu_अगर *cpuअगर = &vcpu->arch.vgic_cpu.vgic_v3;

	cpuअगर->vgic_hcr |= ICH_HCR_UIE;
पूर्ण

अटल bool lr_संकेतs_eoi_mi(u64 lr_val)
अणु
	वापस !(lr_val & ICH_LR_STATE) && (lr_val & ICH_LR_EOI) &&
	       !(lr_val & ICH_LR_HW);
पूर्ण

व्योम vgic_v3_fold_lr_state(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vgic_cpu *vgic_cpu = &vcpu->arch.vgic_cpu;
	काष्ठा vgic_v3_cpu_अगर *cpuअगर = &vgic_cpu->vgic_v3;
	u32 model = vcpu->kvm->arch.vgic.vgic_model;
	पूर्णांक lr;

	DEBUG_SPINLOCK_BUG_ON(!irqs_disabled());

	cpuअगर->vgic_hcr &= ~ICH_HCR_UIE;

	क्रम (lr = 0; lr < cpuअगर->used_lrs; lr++) अणु
		u64 val = cpuअगर->vgic_lr[lr];
		u32 पूर्णांकid, cpuid;
		काष्ठा vgic_irq *irq;
		bool is_v2_sgi = false;

		cpuid = val & GICH_LR_PHYSID_CPUID;
		cpuid >>= GICH_LR_PHYSID_CPUID_SHIFT;

		अगर (model == KVM_DEV_TYPE_ARM_VGIC_V3) अणु
			पूर्णांकid = val & ICH_LR_VIRTUAL_ID_MASK;
		पूर्ण अन्यथा अणु
			पूर्णांकid = val & GICH_LR_VIRTUALID;
			is_v2_sgi = vgic_irq_is_sgi(पूर्णांकid);
		पूर्ण

		/* Notअगरy fds when the guest EOI'ed a level-triggered IRQ */
		अगर (lr_संकेतs_eoi_mi(val) && vgic_valid_spi(vcpu->kvm, पूर्णांकid))
			kvm_notअगरy_acked_irq(vcpu->kvm, 0,
					     पूर्णांकid - VGIC_NR_PRIVATE_IRQS);

		irq = vgic_get_irq(vcpu->kvm, vcpu, पूर्णांकid);
		अगर (!irq)	/* An LPI could have been unmapped. */
			जारी;

		raw_spin_lock(&irq->irq_lock);

		/* Always preserve the active bit */
		irq->active = !!(val & ICH_LR_ACTIVE_BIT);

		अगर (irq->active && is_v2_sgi)
			irq->active_source = cpuid;

		/* Edge is the only हाल where we preserve the pending bit */
		अगर (irq->config == VGIC_CONFIG_EDGE &&
		    (val & ICH_LR_PENDING_BIT)) अणु
			irq->pending_latch = true;

			अगर (is_v2_sgi)
				irq->source |= (1 << cpuid);
		पूर्ण

		/*
		 * Clear soft pending state when level irqs have been acked.
		 */
		अगर (irq->config == VGIC_CONFIG_LEVEL && !(val & ICH_LR_STATE))
			irq->pending_latch = false;

		/*
		 * Level-triggered mapped IRQs are special because we only
		 * observe rising edges as input to the VGIC.
		 *
		 * If the guest never acked the पूर्णांकerrupt we have to sample
		 * the physical line and set the line level, because the
		 * device state could have changed or we simply need to
		 * process the still pending पूर्णांकerrupt later.
		 *
		 * If this causes us to lower the level, we have to also clear
		 * the physical active state, since we will otherwise never be
		 * told when the पूर्णांकerrupt becomes निश्चितed again.
		 */
		अगर (vgic_irq_is_mapped_level(irq) && (val & ICH_LR_PENDING_BIT)) अणु
			irq->line_level = vgic_get_phys_line_level(irq);

			अगर (!irq->line_level)
				vgic_irq_set_phys_active(irq, false);
		पूर्ण

		raw_spin_unlock(&irq->irq_lock);
		vgic_put_irq(vcpu->kvm, irq);
	पूर्ण

	cpuअगर->used_lrs = 0;
पूर्ण

/* Requires the irq to be locked alपढ़ोy */
व्योम vgic_v3_populate_lr(काष्ठा kvm_vcpu *vcpu, काष्ठा vgic_irq *irq, पूर्णांक lr)
अणु
	u32 model = vcpu->kvm->arch.vgic.vgic_model;
	u64 val = irq->पूर्णांकid;
	bool allow_pending = true, is_v2_sgi;

	is_v2_sgi = (vgic_irq_is_sgi(irq->पूर्णांकid) &&
		     model == KVM_DEV_TYPE_ARM_VGIC_V2);

	अगर (irq->active) अणु
		val |= ICH_LR_ACTIVE_BIT;
		अगर (is_v2_sgi)
			val |= irq->active_source << GICH_LR_PHYSID_CPUID_SHIFT;
		अगर (vgic_irq_is_multi_sgi(irq)) अणु
			allow_pending = false;
			val |= ICH_LR_EOI;
		पूर्ण
	पूर्ण

	अगर (irq->hw) अणु
		val |= ICH_LR_HW;
		val |= ((u64)irq->hwपूर्णांकid) << ICH_LR_PHYS_ID_SHIFT;
		/*
		 * Never set pending+active on a HW पूर्णांकerrupt, as the
		 * pending state is kept at the physical distributor
		 * level.
		 */
		अगर (irq->active)
			allow_pending = false;
	पूर्ण अन्यथा अणु
		अगर (irq->config == VGIC_CONFIG_LEVEL) अणु
			val |= ICH_LR_EOI;

			/*
			 * Software resampling करोesn't work very well
			 * अगर we allow P+A, so let's not करो that.
			 */
			अगर (irq->active)
				allow_pending = false;
		पूर्ण
	पूर्ण

	अगर (allow_pending && irq_is_pending(irq)) अणु
		val |= ICH_LR_PENDING_BIT;

		अगर (irq->config == VGIC_CONFIG_EDGE)
			irq->pending_latch = false;

		अगर (vgic_irq_is_sgi(irq->पूर्णांकid) &&
		    model == KVM_DEV_TYPE_ARM_VGIC_V2) अणु
			u32 src = ffs(irq->source);

			अगर (WARN_RATELIMIT(!src, "No SGI source for INTID %d\n",
					   irq->पूर्णांकid))
				वापस;

			val |= (src - 1) << GICH_LR_PHYSID_CPUID_SHIFT;
			irq->source &= ~(1 << (src - 1));
			अगर (irq->source) अणु
				irq->pending_latch = true;
				val |= ICH_LR_EOI;
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * Level-triggered mapped IRQs are special because we only observe
	 * rising edges as input to the VGIC.  We thereक्रमe lower the line
	 * level here, so that we can take new भव IRQs.  See
	 * vgic_v3_fold_lr_state क्रम more info.
	 */
	अगर (vgic_irq_is_mapped_level(irq) && (val & ICH_LR_PENDING_BIT))
		irq->line_level = false;

	अगर (irq->group)
		val |= ICH_LR_GROUP;

	val |= (u64)irq->priority << ICH_LR_PRIORITY_SHIFT;

	vcpu->arch.vgic_cpu.vgic_v3.vgic_lr[lr] = val;
पूर्ण

व्योम vgic_v3_clear_lr(काष्ठा kvm_vcpu *vcpu, पूर्णांक lr)
अणु
	vcpu->arch.vgic_cpu.vgic_v3.vgic_lr[lr] = 0;
पूर्ण

व्योम vgic_v3_set_vmcr(काष्ठा kvm_vcpu *vcpu, काष्ठा vgic_vmcr *vmcrp)
अणु
	काष्ठा vgic_v3_cpu_अगर *cpu_अगर = &vcpu->arch.vgic_cpu.vgic_v3;
	u32 model = vcpu->kvm->arch.vgic.vgic_model;
	u32 vmcr;

	अगर (model == KVM_DEV_TYPE_ARM_VGIC_V2) अणु
		vmcr = (vmcrp->ackctl << ICH_VMCR_ACK_CTL_SHIFT) &
			ICH_VMCR_ACK_CTL_MASK;
		vmcr |= (vmcrp->fiqen << ICH_VMCR_FIQ_EN_SHIFT) &
			ICH_VMCR_FIQ_EN_MASK;
	पूर्ण अन्यथा अणु
		/*
		 * When emulating GICv3 on GICv3 with SRE=1 on the
		 * VFIQEn bit is RES1 and the VAckCtl bit is RES0.
		 */
		vmcr = ICH_VMCR_FIQ_EN_MASK;
	पूर्ण

	vmcr |= (vmcrp->cbpr << ICH_VMCR_CBPR_SHIFT) & ICH_VMCR_CBPR_MASK;
	vmcr |= (vmcrp->eoim << ICH_VMCR_EOIM_SHIFT) & ICH_VMCR_EOIM_MASK;
	vmcr |= (vmcrp->abpr << ICH_VMCR_BPR1_SHIFT) & ICH_VMCR_BPR1_MASK;
	vmcr |= (vmcrp->bpr << ICH_VMCR_BPR0_SHIFT) & ICH_VMCR_BPR0_MASK;
	vmcr |= (vmcrp->pmr << ICH_VMCR_PMR_SHIFT) & ICH_VMCR_PMR_MASK;
	vmcr |= (vmcrp->grpen0 << ICH_VMCR_ENG0_SHIFT) & ICH_VMCR_ENG0_MASK;
	vmcr |= (vmcrp->grpen1 << ICH_VMCR_ENG1_SHIFT) & ICH_VMCR_ENG1_MASK;

	cpu_अगर->vgic_vmcr = vmcr;
पूर्ण

व्योम vgic_v3_get_vmcr(काष्ठा kvm_vcpu *vcpu, काष्ठा vgic_vmcr *vmcrp)
अणु
	काष्ठा vgic_v3_cpu_अगर *cpu_अगर = &vcpu->arch.vgic_cpu.vgic_v3;
	u32 model = vcpu->kvm->arch.vgic.vgic_model;
	u32 vmcr;

	vmcr = cpu_अगर->vgic_vmcr;

	अगर (model == KVM_DEV_TYPE_ARM_VGIC_V2) अणु
		vmcrp->ackctl = (vmcr & ICH_VMCR_ACK_CTL_MASK) >>
			ICH_VMCR_ACK_CTL_SHIFT;
		vmcrp->fiqen = (vmcr & ICH_VMCR_FIQ_EN_MASK) >>
			ICH_VMCR_FIQ_EN_SHIFT;
	पूर्ण अन्यथा अणु
		/*
		 * When emulating GICv3 on GICv3 with SRE=1 on the
		 * VFIQEn bit is RES1 and the VAckCtl bit is RES0.
		 */
		vmcrp->fiqen = 1;
		vmcrp->ackctl = 0;
	पूर्ण

	vmcrp->cbpr = (vmcr & ICH_VMCR_CBPR_MASK) >> ICH_VMCR_CBPR_SHIFT;
	vmcrp->eoim = (vmcr & ICH_VMCR_EOIM_MASK) >> ICH_VMCR_EOIM_SHIFT;
	vmcrp->abpr = (vmcr & ICH_VMCR_BPR1_MASK) >> ICH_VMCR_BPR1_SHIFT;
	vmcrp->bpr  = (vmcr & ICH_VMCR_BPR0_MASK) >> ICH_VMCR_BPR0_SHIFT;
	vmcrp->pmr  = (vmcr & ICH_VMCR_PMR_MASK) >> ICH_VMCR_PMR_SHIFT;
	vmcrp->grpen0 = (vmcr & ICH_VMCR_ENG0_MASK) >> ICH_VMCR_ENG0_SHIFT;
	vmcrp->grpen1 = (vmcr & ICH_VMCR_ENG1_MASK) >> ICH_VMCR_ENG1_SHIFT;
पूर्ण

#घोषणा INITIAL_PENDBASER_VALUE						  \
	(GIC_BASER_CACHEABILITY(GICR_PENDBASER, INNER, RaWb)		| \
	GIC_BASER_CACHEABILITY(GICR_PENDBASER, OUTER, SameAsInner)	| \
	GIC_BASER_SHAREABILITY(GICR_PENDBASER, InnerShareable))

व्योम vgic_v3_enable(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vgic_v3_cpu_अगर *vgic_v3 = &vcpu->arch.vgic_cpu.vgic_v3;

	/*
	 * By क्रमcing VMCR to zero, the GIC will restore the binary
	 * poपूर्णांकs to their reset values. Anything अन्यथा resets to zero
	 * anyway.
	 */
	vgic_v3->vgic_vmcr = 0;

	/*
	 * If we are emulating a GICv3, we करो it in an non-GICv2-compatible
	 * way, so we क्रमce SRE to 1 to demonstrate this to the guest.
	 * Also, we करोn't support any क्रमm of IRQ/FIQ bypass.
	 * This goes with the spec allowing the value to be RAO/WI.
	 */
	अगर (vcpu->kvm->arch.vgic.vgic_model == KVM_DEV_TYPE_ARM_VGIC_V3) अणु
		vgic_v3->vgic_sre = (ICC_SRE_EL1_DIB |
				     ICC_SRE_EL1_DFB |
				     ICC_SRE_EL1_SRE);
		vcpu->arch.vgic_cpu.pendbaser = INITIAL_PENDBASER_VALUE;
	पूर्ण अन्यथा अणु
		vgic_v3->vgic_sre = 0;
	पूर्ण

	vcpu->arch.vgic_cpu.num_id_bits = (kvm_vgic_global_state.ich_vtr_el2 &
					   ICH_VTR_ID_BITS_MASK) >>
					   ICH_VTR_ID_BITS_SHIFT;
	vcpu->arch.vgic_cpu.num_pri_bits = ((kvm_vgic_global_state.ich_vtr_el2 &
					    ICH_VTR_PRI_BITS_MASK) >>
					    ICH_VTR_PRI_BITS_SHIFT) + 1;

	/* Get the show on the road... */
	vgic_v3->vgic_hcr = ICH_HCR_EN;
	अगर (group0_trap)
		vgic_v3->vgic_hcr |= ICH_HCR_TALL0;
	अगर (group1_trap)
		vgic_v3->vgic_hcr |= ICH_HCR_TALL1;
	अगर (common_trap)
		vgic_v3->vgic_hcr |= ICH_HCR_TC;
पूर्ण

पूर्णांक vgic_v3_lpi_sync_pending_status(काष्ठा kvm *kvm, काष्ठा vgic_irq *irq)
अणु
	काष्ठा kvm_vcpu *vcpu;
	पूर्णांक byte_offset, bit_nr;
	gpa_t pendbase, ptr;
	bool status;
	u8 val;
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;

retry:
	vcpu = irq->target_vcpu;
	अगर (!vcpu)
		वापस 0;

	pendbase = GICR_PENDBASER_ADDRESS(vcpu->arch.vgic_cpu.pendbaser);

	byte_offset = irq->पूर्णांकid / BITS_PER_BYTE;
	bit_nr = irq->पूर्णांकid % BITS_PER_BYTE;
	ptr = pendbase + byte_offset;

	ret = kvm_पढ़ो_guest_lock(kvm, ptr, &val, 1);
	अगर (ret)
		वापस ret;

	status = val & (1 << bit_nr);

	raw_spin_lock_irqsave(&irq->irq_lock, flags);
	अगर (irq->target_vcpu != vcpu) अणु
		raw_spin_unlock_irqrestore(&irq->irq_lock, flags);
		जाओ retry;
	पूर्ण
	irq->pending_latch = status;
	vgic_queue_irq_unlock(vcpu->kvm, irq, flags);

	अगर (status) अणु
		/* clear consumed data */
		val &= ~(1 << bit_nr);
		ret = kvm_ग_लिखो_guest_lock(kvm, ptr, &val, 1);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * The deactivation of the करोorbell पूर्णांकerrupt will trigger the
 * unmapping of the associated vPE.
 */
अटल व्योम unmap_all_vpes(काष्ठा vgic_dist *dist)
अणु
	काष्ठा irq_desc *desc;
	पूर्णांक i;

	क्रम (i = 0; i < dist->its_vm.nr_vpes; i++) अणु
		desc = irq_to_desc(dist->its_vm.vpes[i]->irq);
		irq_करोमुख्य_deactivate_irq(irq_desc_get_irq_data(desc));
	पूर्ण
पूर्ण

अटल व्योम map_all_vpes(काष्ठा vgic_dist *dist)
अणु
	काष्ठा irq_desc *desc;
	पूर्णांक i;

	क्रम (i = 0; i < dist->its_vm.nr_vpes; i++) अणु
		desc = irq_to_desc(dist->its_vm.vpes[i]->irq);
		irq_करोमुख्य_activate_irq(irq_desc_get_irq_data(desc), false);
	पूर्ण
पूर्ण

/**
 * vgic_v3_save_pending_tables - Save the pending tables पूर्णांकo guest RAM
 * kvm lock and all vcpu lock must be held
 */
पूर्णांक vgic_v3_save_pending_tables(काष्ठा kvm *kvm)
अणु
	काष्ठा vgic_dist *dist = &kvm->arch.vgic;
	काष्ठा vgic_irq *irq;
	gpa_t last_ptr = ~(gpa_t)0;
	bool vlpi_avail = false;
	पूर्णांक ret = 0;
	u8 val;

	अगर (unlikely(!vgic_initialized(kvm)))
		वापस -ENXIO;

	/*
	 * A preparation क्रम getting any VLPI states.
	 * The above vgic initialized check also ensures that the allocation
	 * and enabling of the करोorbells have alपढ़ोy been करोne.
	 */
	अगर (kvm_vgic_global_state.has_gicv4_1) अणु
		unmap_all_vpes(dist);
		vlpi_avail = true;
	पूर्ण

	list_क्रम_each_entry(irq, &dist->lpi_list_head, lpi_list) अणु
		पूर्णांक byte_offset, bit_nr;
		काष्ठा kvm_vcpu *vcpu;
		gpa_t pendbase, ptr;
		bool is_pending;
		bool stored;

		vcpu = irq->target_vcpu;
		अगर (!vcpu)
			जारी;

		pendbase = GICR_PENDBASER_ADDRESS(vcpu->arch.vgic_cpu.pendbaser);

		byte_offset = irq->पूर्णांकid / BITS_PER_BYTE;
		bit_nr = irq->पूर्णांकid % BITS_PER_BYTE;
		ptr = pendbase + byte_offset;

		अगर (ptr != last_ptr) अणु
			ret = kvm_पढ़ो_guest_lock(kvm, ptr, &val, 1);
			अगर (ret)
				जाओ out;
			last_ptr = ptr;
		पूर्ण

		stored = val & (1U << bit_nr);

		is_pending = irq->pending_latch;

		अगर (irq->hw && vlpi_avail)
			vgic_v4_get_vlpi_state(irq, &is_pending);

		अगर (stored == is_pending)
			जारी;

		अगर (is_pending)
			val |= 1 << bit_nr;
		अन्यथा
			val &= ~(1 << bit_nr);

		ret = kvm_ग_लिखो_guest_lock(kvm, ptr, &val, 1);
		अगर (ret)
			जाओ out;
	पूर्ण

out:
	अगर (vlpi_avail)
		map_all_vpes(dist);

	वापस ret;
पूर्ण

/**
 * vgic_v3_rdist_overlap - check अगर a region overlaps with any
 * existing redistributor region
 *
 * @kvm: kvm handle
 * @base: base of the region
 * @size: size of region
 *
 * Return: true अगर there is an overlap
 */
bool vgic_v3_rdist_overlap(काष्ठा kvm *kvm, gpa_t base, माप_प्रकार size)
अणु
	काष्ठा vgic_dist *d = &kvm->arch.vgic;
	काष्ठा vgic_redist_region *rdreg;

	list_क्रम_each_entry(rdreg, &d->rd_regions, list) अणु
		अगर ((base + size > rdreg->base) &&
			(base < rdreg->base + vgic_v3_rd_region_size(kvm, rdreg)))
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

/*
 * Check क्रम overlapping regions and क्रम regions crossing the end of memory
 * क्रम base addresses which have alपढ़ोy been set.
 */
bool vgic_v3_check_base(काष्ठा kvm *kvm)
अणु
	काष्ठा vgic_dist *d = &kvm->arch.vgic;
	काष्ठा vgic_redist_region *rdreg;

	अगर (!IS_VGIC_ADDR_UNDEF(d->vgic_dist_base) &&
	    d->vgic_dist_base + KVM_VGIC_V3_DIST_SIZE < d->vgic_dist_base)
		वापस false;

	list_क्रम_each_entry(rdreg, &d->rd_regions, list) अणु
		अगर (rdreg->base + vgic_v3_rd_region_size(kvm, rdreg) <
			rdreg->base)
			वापस false;
	पूर्ण

	अगर (IS_VGIC_ADDR_UNDEF(d->vgic_dist_base))
		वापस true;

	वापस !vgic_v3_rdist_overlap(kvm, d->vgic_dist_base,
				      KVM_VGIC_V3_DIST_SIZE);
पूर्ण

/**
 * vgic_v3_rdist_मुक्त_slot - Look up रेजिस्टरed rdist regions and identअगरy one
 * which has मुक्त space to put a new rdist region.
 *
 * @rd_regions: redistributor region list head
 *
 * A redistributor regions maps n redistributors, n = region size / (2 x 64kB).
 * Stride between redistributors is 0 and regions are filled in the index order.
 *
 * Return: the redist region handle, अगर any, that has space to map a new rdist
 * region.
 */
काष्ठा vgic_redist_region *vgic_v3_rdist_मुक्त_slot(काष्ठा list_head *rd_regions)
अणु
	काष्ठा vgic_redist_region *rdreg;

	list_क्रम_each_entry(rdreg, rd_regions, list) अणु
		अगर (!vgic_v3_redist_region_full(rdreg))
			वापस rdreg;
	पूर्ण
	वापस शून्य;
पूर्ण

काष्ठा vgic_redist_region *vgic_v3_rdist_region_from_index(काष्ठा kvm *kvm,
							   u32 index)
अणु
	काष्ठा list_head *rd_regions = &kvm->arch.vgic.rd_regions;
	काष्ठा vgic_redist_region *rdreg;

	list_क्रम_each_entry(rdreg, rd_regions, list) अणु
		अगर (rdreg->index == index)
			वापस rdreg;
	पूर्ण
	वापस शून्य;
पूर्ण


पूर्णांक vgic_v3_map_resources(काष्ठा kvm *kvm)
अणु
	काष्ठा vgic_dist *dist = &kvm->arch.vgic;
	काष्ठा kvm_vcpu *vcpu;
	पूर्णांक ret = 0;
	पूर्णांक c;

	kvm_क्रम_each_vcpu(c, vcpu, kvm) अणु
		काष्ठा vgic_cpu *vgic_cpu = &vcpu->arch.vgic_cpu;

		अगर (IS_VGIC_ADDR_UNDEF(vgic_cpu->rd_iodev.base_addr)) अणु
			kvm_debug("vcpu %d redistributor base not set\n", c);
			वापस -ENXIO;
		पूर्ण
	पूर्ण

	अगर (IS_VGIC_ADDR_UNDEF(dist->vgic_dist_base)) अणु
		kvm_err("Need to set vgic distributor addresses first\n");
		वापस -ENXIO;
	पूर्ण

	अगर (!vgic_v3_check_base(kvm)) अणु
		kvm_err("VGIC redist and dist frames overlap\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * For a VGICv3 we require the userland to explicitly initialize
	 * the VGIC beक्रमe we need to use it.
	 */
	अगर (!vgic_initialized(kvm)) अणु
		वापस -EBUSY;
	पूर्ण

	ret = vgic_रेजिस्टर_dist_iodev(kvm, dist->vgic_dist_base, VGIC_V3);
	अगर (ret) अणु
		kvm_err("Unable to register VGICv3 dist MMIO regions\n");
		वापस ret;
	पूर्ण

	अगर (kvm_vgic_global_state.has_gicv4_1)
		vgic_v4_configure_vsgis(kvm);

	वापस 0;
पूर्ण

DEFINE_STATIC_KEY_FALSE(vgic_v3_cpuअगर_trap);

अटल पूर्णांक __init early_group0_trap_cfg(अक्षर *buf)
अणु
	वापस strtobool(buf, &group0_trap);
पूर्ण
early_param("kvm-arm.vgic_v3_group0_trap", early_group0_trap_cfg);

अटल पूर्णांक __init early_group1_trap_cfg(अक्षर *buf)
अणु
	वापस strtobool(buf, &group1_trap);
पूर्ण
early_param("kvm-arm.vgic_v3_group1_trap", early_group1_trap_cfg);

अटल पूर्णांक __init early_common_trap_cfg(अक्षर *buf)
अणु
	वापस strtobool(buf, &common_trap);
पूर्ण
early_param("kvm-arm.vgic_v3_common_trap", early_common_trap_cfg);

अटल पूर्णांक __init early_gicv4_enable(अक्षर *buf)
अणु
	वापस strtobool(buf, &gicv4_enable);
पूर्ण
early_param("kvm-arm.vgic_v4_enable", early_gicv4_enable);

/**
 * vgic_v3_probe - probe क्रम a VGICv3 compatible पूर्णांकerrupt controller
 * @info:	poपूर्णांकer to the GIC description
 *
 * Returns 0 अगर the VGICv3 has been probed successfully, वापसs an error code
 * otherwise
 */
पूर्णांक vgic_v3_probe(स्थिर काष्ठा gic_kvm_info *info)
अणु
	u64 ich_vtr_el2 = kvm_call_hyp_ret(__vgic_v3_get_gic_config);
	bool has_v2;
	पूर्णांक ret;

	has_v2 = ich_vtr_el2 >> 63;
	ich_vtr_el2 = (u32)ich_vtr_el2;

	/*
	 * The ListRegs field is 5 bits, but there is an architectural
	 * maximum of 16 list रेजिस्टरs. Just ignore bit 4...
	 */
	kvm_vgic_global_state.nr_lr = (ich_vtr_el2 & 0xf) + 1;
	kvm_vgic_global_state.can_emulate_gicv2 = false;
	kvm_vgic_global_state.ich_vtr_el2 = ich_vtr_el2;

	/* GICv4 support? */
	अगर (info->has_v4) अणु
		kvm_vgic_global_state.has_gicv4 = gicv4_enable;
		kvm_vgic_global_state.has_gicv4_1 = info->has_v4_1 && gicv4_enable;
		kvm_info("GICv4%s support %sabled\n",
			 kvm_vgic_global_state.has_gicv4_1 ? ".1" : "",
			 gicv4_enable ? "en" : "dis");
	पूर्ण

	kvm_vgic_global_state.vcpu_base = 0;

	अगर (!info->vcpu.start) अणु
		kvm_info("GICv3: no GICV resource entry\n");
	पूर्ण अन्यथा अगर (!has_v2) अणु
		pr_warn(FW_BUG "CPU interface incapable of MMIO access\n");
	पूर्ण अन्यथा अगर (!PAGE_ALIGNED(info->vcpu.start)) अणु
		pr_warn("GICV physical address 0x%llx not page aligned\n",
			(अचिन्हित दीर्घ दीर्घ)info->vcpu.start);
	पूर्ण अन्यथा अणु
		kvm_vgic_global_state.vcpu_base = info->vcpu.start;
		kvm_vgic_global_state.can_emulate_gicv2 = true;
		ret = kvm_रेजिस्टर_vgic_device(KVM_DEV_TYPE_ARM_VGIC_V2);
		अगर (ret) अणु
			kvm_err("Cannot register GICv2 KVM device.\n");
			वापस ret;
		पूर्ण
		kvm_info("vgic-v2@%llx\n", info->vcpu.start);
	पूर्ण
	ret = kvm_रेजिस्टर_vgic_device(KVM_DEV_TYPE_ARM_VGIC_V3);
	अगर (ret) अणु
		kvm_err("Cannot register GICv3 KVM device.\n");
		kvm_unरेजिस्टर_device_ops(KVM_DEV_TYPE_ARM_VGIC_V2);
		वापस ret;
	पूर्ण

	अगर (kvm_vgic_global_state.vcpu_base == 0)
		kvm_info("disabling GICv2 emulation\n");

	अगर (cpus_have_स्थिर_cap(ARM64_WORKAROUND_CAVIUM_30115)) अणु
		group0_trap = true;
		group1_trap = true;
	पूर्ण

	अगर (group0_trap || group1_trap || common_trap) अणु
		kvm_info("GICv3 sysreg trapping enabled ([%s%s%s], reduced performance)\n",
			 group0_trap ? "G0" : "",
			 group1_trap ? "G1" : "",
			 common_trap ? "C"  : "");
		अटल_branch_enable(&vgic_v3_cpuअगर_trap);
	पूर्ण

	kvm_vgic_global_state.vctrl_base = शून्य;
	kvm_vgic_global_state.type = VGIC_V3;
	kvm_vgic_global_state.max_gic_vcpus = VGIC_V3_MAX_CPUS;

	वापस 0;
पूर्ण

व्योम vgic_v3_load(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vgic_v3_cpu_अगर *cpu_अगर = &vcpu->arch.vgic_cpu.vgic_v3;

	/*
	 * If dealing with a GICv2 emulation on GICv3, VMCR_EL2.VFIQen
	 * is dependent on ICC_SRE_EL1.SRE, and we have to perक्रमm the
	 * VMCR_EL2 save/restore in the world चयन.
	 */
	अगर (likely(cpu_अगर->vgic_sre))
		kvm_call_hyp(__vgic_v3_ग_लिखो_vmcr, cpu_अगर->vgic_vmcr);

	kvm_call_hyp(__vgic_v3_restore_aprs, cpu_अगर);

	अगर (has_vhe())
		__vgic_v3_activate_traps(cpu_अगर);

	WARN_ON(vgic_v4_load(vcpu));
पूर्ण

व्योम vgic_v3_vmcr_sync(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vgic_v3_cpu_अगर *cpu_अगर = &vcpu->arch.vgic_cpu.vgic_v3;

	अगर (likely(cpu_अगर->vgic_sre))
		cpu_अगर->vgic_vmcr = kvm_call_hyp_ret(__vgic_v3_पढ़ो_vmcr);
पूर्ण

व्योम vgic_v3_put(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vgic_v3_cpu_अगर *cpu_अगर = &vcpu->arch.vgic_cpu.vgic_v3;

	WARN_ON(vgic_v4_put(vcpu, false));

	vgic_v3_vmcr_sync(vcpu);

	kvm_call_hyp(__vgic_v3_save_aprs, cpu_अगर);

	अगर (has_vhe())
		__vgic_v3_deactivate_traps(cpu_अगर);
पूर्ण
