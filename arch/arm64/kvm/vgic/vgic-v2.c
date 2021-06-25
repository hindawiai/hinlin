<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2015, 2016 ARM Ltd.
 */

#समावेश <linux/irqchip/arm-gic.h>
#समावेश <linux/kvm.h>
#समावेश <linux/kvm_host.h>
#समावेश <kvm/arm_vgic.h>
#समावेश <यंत्र/kvm_mmu.h>

#समावेश "vgic.h"

अटल अंतरभूत व्योम vgic_v2_ग_लिखो_lr(पूर्णांक lr, u32 val)
अणु
	व्योम __iomem *base = kvm_vgic_global_state.vctrl_base;

	ग_लिखोl_relaxed(val, base + GICH_LR0 + (lr * 4));
पूर्ण

व्योम vgic_v2_init_lrs(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < kvm_vgic_global_state.nr_lr; i++)
		vgic_v2_ग_लिखो_lr(i, 0);
पूर्ण

व्योम vgic_v2_set_underflow(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vgic_v2_cpu_अगर *cpuअगर = &vcpu->arch.vgic_cpu.vgic_v2;

	cpuअगर->vgic_hcr |= GICH_HCR_UIE;
पूर्ण

अटल bool lr_संकेतs_eoi_mi(u32 lr_val)
अणु
	वापस !(lr_val & GICH_LR_STATE) && (lr_val & GICH_LR_EOI) &&
	       !(lr_val & GICH_LR_HW);
पूर्ण

/*
 * transfer the content of the LRs back पूर्णांकo the corresponding ap_list:
 * - active bit is transferred as is
 * - pending bit is
 *   - transferred as is in हाल of edge sensitive IRQs
 *   - set to the line-level (resample समय) क्रम level sensitive IRQs
 */
व्योम vgic_v2_fold_lr_state(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vgic_cpu *vgic_cpu = &vcpu->arch.vgic_cpu;
	काष्ठा vgic_v2_cpu_अगर *cpuअगर = &vgic_cpu->vgic_v2;
	पूर्णांक lr;

	DEBUG_SPINLOCK_BUG_ON(!irqs_disabled());

	cpuअगर->vgic_hcr &= ~GICH_HCR_UIE;

	क्रम (lr = 0; lr < vgic_cpu->vgic_v2.used_lrs; lr++) अणु
		u32 val = cpuअगर->vgic_lr[lr];
		u32 cpuid, पूर्णांकid = val & GICH_LR_VIRTUALID;
		काष्ठा vgic_irq *irq;

		/* Extract the source vCPU id from the LR */
		cpuid = val & GICH_LR_PHYSID_CPUID;
		cpuid >>= GICH_LR_PHYSID_CPUID_SHIFT;
		cpuid &= 7;

		/* Notअगरy fds when the guest EOI'ed a level-triggered SPI */
		अगर (lr_संकेतs_eoi_mi(val) && vgic_valid_spi(vcpu->kvm, पूर्णांकid))
			kvm_notअगरy_acked_irq(vcpu->kvm, 0,
					     पूर्णांकid - VGIC_NR_PRIVATE_IRQS);

		irq = vgic_get_irq(vcpu->kvm, vcpu, पूर्णांकid);

		raw_spin_lock(&irq->irq_lock);

		/* Always preserve the active bit */
		irq->active = !!(val & GICH_LR_ACTIVE_BIT);

		अगर (irq->active && vgic_irq_is_sgi(पूर्णांकid))
			irq->active_source = cpuid;

		/* Edge is the only हाल where we preserve the pending bit */
		अगर (irq->config == VGIC_CONFIG_EDGE &&
		    (val & GICH_LR_PENDING_BIT)) अणु
			irq->pending_latch = true;

			अगर (vgic_irq_is_sgi(पूर्णांकid))
				irq->source |= (1 << cpuid);
		पूर्ण

		/*
		 * Clear soft pending state when level irqs have been acked.
		 */
		अगर (irq->config == VGIC_CONFIG_LEVEL && !(val & GICH_LR_STATE))
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
		अगर (vgic_irq_is_mapped_level(irq) && (val & GICH_LR_PENDING_BIT)) अणु
			irq->line_level = vgic_get_phys_line_level(irq);

			अगर (!irq->line_level)
				vgic_irq_set_phys_active(irq, false);
		पूर्ण

		raw_spin_unlock(&irq->irq_lock);
		vgic_put_irq(vcpu->kvm, irq);
	पूर्ण

	cpuअगर->used_lrs = 0;
पूर्ण

/*
 * Populates the particular LR with the state of a given IRQ:
 * - क्रम an edge sensitive IRQ the pending state is cleared in काष्ठा vgic_irq
 * - क्रम a level sensitive IRQ the pending state value is unchanged;
 *   it is dictated directly by the input level
 *
 * If @irq describes an SGI with multiple sources, we choose the
 * lowest-numbered source VCPU and clear that bit in the source biपंचांगap.
 *
 * The irq_lock must be held by the caller.
 */
व्योम vgic_v2_populate_lr(काष्ठा kvm_vcpu *vcpu, काष्ठा vgic_irq *irq, पूर्णांक lr)
अणु
	u32 val = irq->पूर्णांकid;
	bool allow_pending = true;

	अगर (irq->active) अणु
		val |= GICH_LR_ACTIVE_BIT;
		अगर (vgic_irq_is_sgi(irq->पूर्णांकid))
			val |= irq->active_source << GICH_LR_PHYSID_CPUID_SHIFT;
		अगर (vgic_irq_is_multi_sgi(irq)) अणु
			allow_pending = false;
			val |= GICH_LR_EOI;
		पूर्ण
	पूर्ण

	अगर (irq->group)
		val |= GICH_LR_GROUP1;

	अगर (irq->hw) अणु
		val |= GICH_LR_HW;
		val |= irq->hwपूर्णांकid << GICH_LR_PHYSID_CPUID_SHIFT;
		/*
		 * Never set pending+active on a HW पूर्णांकerrupt, as the
		 * pending state is kept at the physical distributor
		 * level.
		 */
		अगर (irq->active)
			allow_pending = false;
	पूर्ण अन्यथा अणु
		अगर (irq->config == VGIC_CONFIG_LEVEL) अणु
			val |= GICH_LR_EOI;

			/*
			 * Software resampling करोesn't work very well
			 * अगर we allow P+A, so let's not करो that.
			 */
			अगर (irq->active)
				allow_pending = false;
		पूर्ण
	पूर्ण

	अगर (allow_pending && irq_is_pending(irq)) अणु
		val |= GICH_LR_PENDING_BIT;

		अगर (irq->config == VGIC_CONFIG_EDGE)
			irq->pending_latch = false;

		अगर (vgic_irq_is_sgi(irq->पूर्णांकid)) अणु
			u32 src = ffs(irq->source);

			अगर (WARN_RATELIMIT(!src, "No SGI source for INTID %d\n",
					   irq->पूर्णांकid))
				वापस;

			val |= (src - 1) << GICH_LR_PHYSID_CPUID_SHIFT;
			irq->source &= ~(1 << (src - 1));
			अगर (irq->source) अणु
				irq->pending_latch = true;
				val |= GICH_LR_EOI;
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * Level-triggered mapped IRQs are special because we only observe
	 * rising edges as input to the VGIC.  We thereक्रमe lower the line
	 * level here, so that we can take new भव IRQs.  See
	 * vgic_v2_fold_lr_state क्रम more info.
	 */
	अगर (vgic_irq_is_mapped_level(irq) && (val & GICH_LR_PENDING_BIT))
		irq->line_level = false;

	/* The GICv2 LR only holds five bits of priority. */
	val |= (irq->priority >> 3) << GICH_LR_PRIORITY_SHIFT;

	vcpu->arch.vgic_cpu.vgic_v2.vgic_lr[lr] = val;
पूर्ण

व्योम vgic_v2_clear_lr(काष्ठा kvm_vcpu *vcpu, पूर्णांक lr)
अणु
	vcpu->arch.vgic_cpu.vgic_v2.vgic_lr[lr] = 0;
पूर्ण

व्योम vgic_v2_set_vmcr(काष्ठा kvm_vcpu *vcpu, काष्ठा vgic_vmcr *vmcrp)
अणु
	काष्ठा vgic_v2_cpu_अगर *cpu_अगर = &vcpu->arch.vgic_cpu.vgic_v2;
	u32 vmcr;

	vmcr = (vmcrp->grpen0 << GICH_VMCR_ENABLE_GRP0_SHIFT) &
		GICH_VMCR_ENABLE_GRP0_MASK;
	vmcr |= (vmcrp->grpen1 << GICH_VMCR_ENABLE_GRP1_SHIFT) &
		GICH_VMCR_ENABLE_GRP1_MASK;
	vmcr |= (vmcrp->ackctl << GICH_VMCR_ACK_CTL_SHIFT) &
		GICH_VMCR_ACK_CTL_MASK;
	vmcr |= (vmcrp->fiqen << GICH_VMCR_FIQ_EN_SHIFT) &
		GICH_VMCR_FIQ_EN_MASK;
	vmcr |= (vmcrp->cbpr << GICH_VMCR_CBPR_SHIFT) &
		GICH_VMCR_CBPR_MASK;
	vmcr |= (vmcrp->eoim << GICH_VMCR_EOI_MODE_SHIFT) &
		GICH_VMCR_EOI_MODE_MASK;
	vmcr |= (vmcrp->abpr << GICH_VMCR_ALIAS_BINPOINT_SHIFT) &
		GICH_VMCR_ALIAS_BINPOINT_MASK;
	vmcr |= (vmcrp->bpr << GICH_VMCR_BINPOINT_SHIFT) &
		GICH_VMCR_BINPOINT_MASK;
	vmcr |= ((vmcrp->pmr >> GICV_PMR_PRIORITY_SHIFT) <<
		 GICH_VMCR_PRIMASK_SHIFT) & GICH_VMCR_PRIMASK_MASK;

	cpu_अगर->vgic_vmcr = vmcr;
पूर्ण

व्योम vgic_v2_get_vmcr(काष्ठा kvm_vcpu *vcpu, काष्ठा vgic_vmcr *vmcrp)
अणु
	काष्ठा vgic_v2_cpu_अगर *cpu_अगर = &vcpu->arch.vgic_cpu.vgic_v2;
	u32 vmcr;

	vmcr = cpu_अगर->vgic_vmcr;

	vmcrp->grpen0 = (vmcr & GICH_VMCR_ENABLE_GRP0_MASK) >>
		GICH_VMCR_ENABLE_GRP0_SHIFT;
	vmcrp->grpen1 = (vmcr & GICH_VMCR_ENABLE_GRP1_MASK) >>
		GICH_VMCR_ENABLE_GRP1_SHIFT;
	vmcrp->ackctl = (vmcr & GICH_VMCR_ACK_CTL_MASK) >>
		GICH_VMCR_ACK_CTL_SHIFT;
	vmcrp->fiqen = (vmcr & GICH_VMCR_FIQ_EN_MASK) >>
		GICH_VMCR_FIQ_EN_SHIFT;
	vmcrp->cbpr = (vmcr & GICH_VMCR_CBPR_MASK) >>
		GICH_VMCR_CBPR_SHIFT;
	vmcrp->eoim = (vmcr & GICH_VMCR_EOI_MODE_MASK) >>
		GICH_VMCR_EOI_MODE_SHIFT;

	vmcrp->abpr = (vmcr & GICH_VMCR_ALIAS_BINPOINT_MASK) >>
			GICH_VMCR_ALIAS_BINPOINT_SHIFT;
	vmcrp->bpr  = (vmcr & GICH_VMCR_BINPOINT_MASK) >>
			GICH_VMCR_BINPOINT_SHIFT;
	vmcrp->pmr  = ((vmcr & GICH_VMCR_PRIMASK_MASK) >>
			GICH_VMCR_PRIMASK_SHIFT) << GICV_PMR_PRIORITY_SHIFT;
पूर्ण

व्योम vgic_v2_enable(काष्ठा kvm_vcpu *vcpu)
अणु
	/*
	 * By क्रमcing VMCR to zero, the GIC will restore the binary
	 * poपूर्णांकs to their reset values. Anything अन्यथा resets to zero
	 * anyway.
	 */
	vcpu->arch.vgic_cpu.vgic_v2.vgic_vmcr = 0;

	/* Get the show on the road... */
	vcpu->arch.vgic_cpu.vgic_v2.vgic_hcr = GICH_HCR_EN;
पूर्ण

/* check क्रम overlapping regions and क्रम regions crossing the end of memory */
अटल bool vgic_v2_check_base(gpa_t dist_base, gpa_t cpu_base)
अणु
	अगर (dist_base + KVM_VGIC_V2_DIST_SIZE < dist_base)
		वापस false;
	अगर (cpu_base + KVM_VGIC_V2_CPU_SIZE < cpu_base)
		वापस false;

	अगर (dist_base + KVM_VGIC_V2_DIST_SIZE <= cpu_base)
		वापस true;
	अगर (cpu_base + KVM_VGIC_V2_CPU_SIZE <= dist_base)
		वापस true;

	वापस false;
पूर्ण

पूर्णांक vgic_v2_map_resources(काष्ठा kvm *kvm)
अणु
	काष्ठा vgic_dist *dist = &kvm->arch.vgic;
	पूर्णांक ret = 0;

	अगर (IS_VGIC_ADDR_UNDEF(dist->vgic_dist_base) ||
	    IS_VGIC_ADDR_UNDEF(dist->vgic_cpu_base)) अणु
		kvm_err("Need to set vgic cpu and dist addresses first\n");
		वापस -ENXIO;
	पूर्ण

	अगर (!vgic_v2_check_base(dist->vgic_dist_base, dist->vgic_cpu_base)) अणु
		kvm_err("VGIC CPU and dist frames overlap\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * Initialize the vgic अगर this hasn't alपढ़ोy been करोne on demand by
	 * accessing the vgic state from userspace.
	 */
	ret = vgic_init(kvm);
	अगर (ret) अणु
		kvm_err("Unable to initialize VGIC dynamic data structures\n");
		वापस ret;
	पूर्ण

	ret = vgic_रेजिस्टर_dist_iodev(kvm, dist->vgic_dist_base, VGIC_V2);
	अगर (ret) अणु
		kvm_err("Unable to register VGIC MMIO regions\n");
		वापस ret;
	पूर्ण

	अगर (!अटल_branch_unlikely(&vgic_v2_cpuअगर_trap)) अणु
		ret = kvm_phys_addr_ioremap(kvm, dist->vgic_cpu_base,
					    kvm_vgic_global_state.vcpu_base,
					    KVM_VGIC_V2_CPU_SIZE, true);
		अगर (ret) अणु
			kvm_err("Unable to remap VGIC CPU to VCPU\n");
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

DEFINE_STATIC_KEY_FALSE(vgic_v2_cpuअगर_trap);

/**
 * vgic_v2_probe - probe क्रम a VGICv2 compatible पूर्णांकerrupt controller
 * @info:	poपूर्णांकer to the GIC description
 *
 * Returns 0 अगर the VGICv2 has been probed successfully, वापसs an error code
 * otherwise
 */
पूर्णांक vgic_v2_probe(स्थिर काष्ठा gic_kvm_info *info)
अणु
	पूर्णांक ret;
	u32 vtr;

	अगर (!info->vctrl.start) अणु
		kvm_err("GICH not present in the firmware table\n");
		वापस -ENXIO;
	पूर्ण

	अगर (!PAGE_ALIGNED(info->vcpu.start) ||
	    !PAGE_ALIGNED(resource_size(&info->vcpu))) अणु
		kvm_info("GICV region size/alignment is unsafe, using trapping (reduced performance)\n");

		ret = create_hyp_io_mappings(info->vcpu.start,
					     resource_size(&info->vcpu),
					     &kvm_vgic_global_state.vcpu_base_va,
					     &kvm_vgic_global_state.vcpu_hyp_va);
		अगर (ret) अणु
			kvm_err("Cannot map GICV into hyp\n");
			जाओ out;
		पूर्ण

		अटल_branch_enable(&vgic_v2_cpuअगर_trap);
	पूर्ण

	ret = create_hyp_io_mappings(info->vctrl.start,
				     resource_size(&info->vctrl),
				     &kvm_vgic_global_state.vctrl_base,
				     &kvm_vgic_global_state.vctrl_hyp);
	अगर (ret) अणु
		kvm_err("Cannot map VCTRL into hyp\n");
		जाओ out;
	पूर्ण

	vtr = पढ़ोl_relaxed(kvm_vgic_global_state.vctrl_base + GICH_VTR);
	kvm_vgic_global_state.nr_lr = (vtr & 0x3f) + 1;

	ret = kvm_रेजिस्टर_vgic_device(KVM_DEV_TYPE_ARM_VGIC_V2);
	अगर (ret) अणु
		kvm_err("Cannot register GICv2 KVM device\n");
		जाओ out;
	पूर्ण

	kvm_vgic_global_state.can_emulate_gicv2 = true;
	kvm_vgic_global_state.vcpu_base = info->vcpu.start;
	kvm_vgic_global_state.type = VGIC_V2;
	kvm_vgic_global_state.max_gic_vcpus = VGIC_V2_MAX_CPUS;

	kvm_debug("vgic-v2@%llx\n", info->vctrl.start);

	वापस 0;
out:
	अगर (kvm_vgic_global_state.vctrl_base)
		iounmap(kvm_vgic_global_state.vctrl_base);
	अगर (kvm_vgic_global_state.vcpu_base_va)
		iounmap(kvm_vgic_global_state.vcpu_base_va);

	वापस ret;
पूर्ण

अटल व्योम save_lrs(काष्ठा kvm_vcpu *vcpu, व्योम __iomem *base)
अणु
	काष्ठा vgic_v2_cpu_अगर *cpu_अगर = &vcpu->arch.vgic_cpu.vgic_v2;
	u64 used_lrs = cpu_अगर->used_lrs;
	u64 elrsr;
	पूर्णांक i;

	elrsr = पढ़ोl_relaxed(base + GICH_ELRSR0);
	अगर (unlikely(used_lrs > 32))
		elrsr |= ((u64)पढ़ोl_relaxed(base + GICH_ELRSR1)) << 32;

	क्रम (i = 0; i < used_lrs; i++) अणु
		अगर (elrsr & (1UL << i))
			cpu_अगर->vgic_lr[i] &= ~GICH_LR_STATE;
		अन्यथा
			cpu_अगर->vgic_lr[i] = पढ़ोl_relaxed(base + GICH_LR0 + (i * 4));

		ग_लिखोl_relaxed(0, base + GICH_LR0 + (i * 4));
	पूर्ण
पूर्ण

व्योम vgic_v2_save_state(काष्ठा kvm_vcpu *vcpu)
अणु
	व्योम __iomem *base = kvm_vgic_global_state.vctrl_base;
	u64 used_lrs = vcpu->arch.vgic_cpu.vgic_v2.used_lrs;

	अगर (!base)
		वापस;

	अगर (used_lrs) अणु
		save_lrs(vcpu, base);
		ग_लिखोl_relaxed(0, base + GICH_HCR);
	पूर्ण
पूर्ण

व्योम vgic_v2_restore_state(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vgic_v2_cpu_अगर *cpu_अगर = &vcpu->arch.vgic_cpu.vgic_v2;
	व्योम __iomem *base = kvm_vgic_global_state.vctrl_base;
	u64 used_lrs = cpu_अगर->used_lrs;
	पूर्णांक i;

	अगर (!base)
		वापस;

	अगर (used_lrs) अणु
		ग_लिखोl_relaxed(cpu_अगर->vgic_hcr, base + GICH_HCR);
		क्रम (i = 0; i < used_lrs; i++) अणु
			ग_लिखोl_relaxed(cpu_अगर->vgic_lr[i],
				       base + GICH_LR0 + (i * 4));
		पूर्ण
	पूर्ण
पूर्ण

व्योम vgic_v2_load(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vgic_v2_cpu_अगर *cpu_अगर = &vcpu->arch.vgic_cpu.vgic_v2;

	ग_लिखोl_relaxed(cpu_अगर->vgic_vmcr,
		       kvm_vgic_global_state.vctrl_base + GICH_VMCR);
	ग_लिखोl_relaxed(cpu_अगर->vgic_apr,
		       kvm_vgic_global_state.vctrl_base + GICH_APR);
पूर्ण

व्योम vgic_v2_vmcr_sync(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vgic_v2_cpu_अगर *cpu_अगर = &vcpu->arch.vgic_cpu.vgic_v2;

	cpu_अगर->vgic_vmcr = पढ़ोl_relaxed(kvm_vgic_global_state.vctrl_base + GICH_VMCR);
पूर्ण

व्योम vgic_v2_put(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vgic_v2_cpu_अगर *cpu_अगर = &vcpu->arch.vgic_cpu.vgic_v2;

	vgic_v2_vmcr_sync(vcpu);
	cpu_अगर->vgic_apr = पढ़ोl_relaxed(kvm_vgic_global_state.vctrl_base + GICH_APR);
पूर्ण
