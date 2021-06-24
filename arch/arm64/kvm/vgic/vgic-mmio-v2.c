<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * VGICv2 MMIO handling functions
 */

#समावेश <linux/irqchip/arm-gic.h>
#समावेश <linux/kvm.h>
#समावेश <linux/kvm_host.h>
#समावेश <linux/nospec.h>

#समावेश <kvm/iodev.h>
#समावेश <kvm/arm_vgic.h>

#समावेश "vgic.h"
#समावेश "vgic-mmio.h"

/*
 * The Revision field in the IIDR have the following meanings:
 *
 * Revision 1: Report GICv2 पूर्णांकerrupts as group 0 instead of group 1
 * Revision 2: Interrupt groups are guest-configurable and संकेतed using
 * 	       their configured groups.
 */

अटल अचिन्हित दीर्घ vgic_mmio_पढ़ो_v2_misc(काष्ठा kvm_vcpu *vcpu,
					    gpa_t addr, अचिन्हित पूर्णांक len)
अणु
	काष्ठा vgic_dist *vgic = &vcpu->kvm->arch.vgic;
	u32 value;

	चयन (addr & 0x0c) अणु
	हाल GIC_DIST_CTRL:
		value = vgic->enabled ? GICD_ENABLE : 0;
		अवरोध;
	हाल GIC_DIST_CTR:
		value = vgic->nr_spis + VGIC_NR_PRIVATE_IRQS;
		value = (value >> 5) - 1;
		value |= (atomic_पढ़ो(&vcpu->kvm->online_vcpus) - 1) << 5;
		अवरोध;
	हाल GIC_DIST_IIDR:
		value = (PRODUCT_ID_KVM << GICD_IIDR_PRODUCT_ID_SHIFT) |
			(vgic->implementation_rev << GICD_IIDR_REVISION_SHIFT) |
			(IMPLEMENTER_ARM << GICD_IIDR_IMPLEMENTER_SHIFT);
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	वापस value;
पूर्ण

अटल व्योम vgic_mmio_ग_लिखो_v2_misc(काष्ठा kvm_vcpu *vcpu,
				    gpa_t addr, अचिन्हित पूर्णांक len,
				    अचिन्हित दीर्घ val)
अणु
	काष्ठा vgic_dist *dist = &vcpu->kvm->arch.vgic;
	bool was_enabled = dist->enabled;

	चयन (addr & 0x0c) अणु
	हाल GIC_DIST_CTRL:
		dist->enabled = val & GICD_ENABLE;
		अगर (!was_enabled && dist->enabled)
			vgic_kick_vcpus(vcpu->kvm);
		अवरोध;
	हाल GIC_DIST_CTR:
	हाल GIC_DIST_IIDR:
		/* Nothing to करो */
		वापस;
	पूर्ण
पूर्ण

अटल पूर्णांक vgic_mmio_uaccess_ग_लिखो_v2_misc(काष्ठा kvm_vcpu *vcpu,
					   gpa_t addr, अचिन्हित पूर्णांक len,
					   अचिन्हित दीर्घ val)
अणु
	चयन (addr & 0x0c) अणु
	हाल GIC_DIST_IIDR:
		अगर (val != vgic_mmio_पढ़ो_v2_misc(vcpu, addr, len))
			वापस -EINVAL;

		/*
		 * If we observe a ग_लिखो to GICD_IIDR we know that userspace
		 * has been updated and has had a chance to cope with older
		 * kernels (VGICv2 IIDR.Revision == 0) incorrectly reporting
		 * पूर्णांकerrupts as group 1, and thereक्रमe we now allow groups to
		 * be user writable.  Doing this by शेष would अवरोध
		 * migration from old kernels to new kernels with legacy
		 * userspace.
		 */
		vcpu->kvm->arch.vgic.v2_groups_user_writable = true;
		वापस 0;
	पूर्ण

	vgic_mmio_ग_लिखो_v2_misc(vcpu, addr, len, val);
	वापस 0;
पूर्ण

अटल पूर्णांक vgic_mmio_uaccess_ग_लिखो_v2_group(काष्ठा kvm_vcpu *vcpu,
					    gpa_t addr, अचिन्हित पूर्णांक len,
					    अचिन्हित दीर्घ val)
अणु
	अगर (vcpu->kvm->arch.vgic.v2_groups_user_writable)
		vgic_mmio_ग_लिखो_group(vcpu, addr, len, val);

	वापस 0;
पूर्ण

अटल व्योम vgic_mmio_ग_लिखो_sgir(काष्ठा kvm_vcpu *source_vcpu,
				 gpa_t addr, अचिन्हित पूर्णांक len,
				 अचिन्हित दीर्घ val)
अणु
	पूर्णांक nr_vcpus = atomic_पढ़ो(&source_vcpu->kvm->online_vcpus);
	पूर्णांक पूर्णांकid = val & 0xf;
	पूर्णांक tarमाला_लो = (val >> 16) & 0xff;
	पूर्णांक mode = (val >> 24) & 0x03;
	पूर्णांक c;
	काष्ठा kvm_vcpu *vcpu;
	अचिन्हित दीर्घ flags;

	चयन (mode) अणु
	हाल 0x0:		/* as specअगरied by tarमाला_लो */
		अवरोध;
	हाल 0x1:
		tarमाला_लो = (1U << nr_vcpus) - 1;			/* all, ... */
		tarमाला_लो &= ~(1U << source_vcpu->vcpu_id);	/* but self */
		अवरोध;
	हाल 0x2:		/* this very vCPU only */
		tarमाला_लो = (1U << source_vcpu->vcpu_id);
		अवरोध;
	हाल 0x3:		/* reserved */
		वापस;
	पूर्ण

	kvm_क्रम_each_vcpu(c, vcpu, source_vcpu->kvm) अणु
		काष्ठा vgic_irq *irq;

		अगर (!(tarमाला_लो & (1U << c)))
			जारी;

		irq = vgic_get_irq(source_vcpu->kvm, vcpu, पूर्णांकid);

		raw_spin_lock_irqsave(&irq->irq_lock, flags);
		irq->pending_latch = true;
		irq->source |= 1U << source_vcpu->vcpu_id;

		vgic_queue_irq_unlock(source_vcpu->kvm, irq, flags);
		vgic_put_irq(source_vcpu->kvm, irq);
	पूर्ण
पूर्ण

अटल अचिन्हित दीर्घ vgic_mmio_पढ़ो_target(काष्ठा kvm_vcpu *vcpu,
					   gpa_t addr, अचिन्हित पूर्णांक len)
अणु
	u32 पूर्णांकid = VGIC_ADDR_TO_INTID(addr, 8);
	पूर्णांक i;
	u64 val = 0;

	क्रम (i = 0; i < len; i++) अणु
		काष्ठा vgic_irq *irq = vgic_get_irq(vcpu->kvm, vcpu, पूर्णांकid + i);

		val |= (u64)irq->tarमाला_लो << (i * 8);

		vgic_put_irq(vcpu->kvm, irq);
	पूर्ण

	वापस val;
पूर्ण

अटल व्योम vgic_mmio_ग_लिखो_target(काष्ठा kvm_vcpu *vcpu,
				   gpa_t addr, अचिन्हित पूर्णांक len,
				   अचिन्हित दीर्घ val)
अणु
	u32 पूर्णांकid = VGIC_ADDR_TO_INTID(addr, 8);
	u8 cpu_mask = GENMASK(atomic_पढ़ो(&vcpu->kvm->online_vcpus) - 1, 0);
	पूर्णांक i;
	अचिन्हित दीर्घ flags;

	/* GICD_ITARGETSR[0-7] are पढ़ो-only */
	अगर (पूर्णांकid < VGIC_NR_PRIVATE_IRQS)
		वापस;

	क्रम (i = 0; i < len; i++) अणु
		काष्ठा vgic_irq *irq = vgic_get_irq(vcpu->kvm, शून्य, पूर्णांकid + i);
		पूर्णांक target;

		raw_spin_lock_irqsave(&irq->irq_lock, flags);

		irq->tarमाला_लो = (val >> (i * 8)) & cpu_mask;
		target = irq->tarमाला_लो ? __ffs(irq->tarमाला_लो) : 0;
		irq->target_vcpu = kvm_get_vcpu(vcpu->kvm, target);

		raw_spin_unlock_irqrestore(&irq->irq_lock, flags);
		vgic_put_irq(vcpu->kvm, irq);
	पूर्ण
पूर्ण

अटल अचिन्हित दीर्घ vgic_mmio_पढ़ो_sgipend(काष्ठा kvm_vcpu *vcpu,
					    gpa_t addr, अचिन्हित पूर्णांक len)
अणु
	u32 पूर्णांकid = addr & 0x0f;
	पूर्णांक i;
	u64 val = 0;

	क्रम (i = 0; i < len; i++) अणु
		काष्ठा vgic_irq *irq = vgic_get_irq(vcpu->kvm, vcpu, पूर्णांकid + i);

		val |= (u64)irq->source << (i * 8);

		vgic_put_irq(vcpu->kvm, irq);
	पूर्ण
	वापस val;
पूर्ण

अटल व्योम vgic_mmio_ग_लिखो_sgipendc(काष्ठा kvm_vcpu *vcpu,
				     gpa_t addr, अचिन्हित पूर्णांक len,
				     अचिन्हित दीर्घ val)
अणु
	u32 पूर्णांकid = addr & 0x0f;
	पूर्णांक i;
	अचिन्हित दीर्घ flags;

	क्रम (i = 0; i < len; i++) अणु
		काष्ठा vgic_irq *irq = vgic_get_irq(vcpu->kvm, vcpu, पूर्णांकid + i);

		raw_spin_lock_irqsave(&irq->irq_lock, flags);

		irq->source &= ~((val >> (i * 8)) & 0xff);
		अगर (!irq->source)
			irq->pending_latch = false;

		raw_spin_unlock_irqrestore(&irq->irq_lock, flags);
		vgic_put_irq(vcpu->kvm, irq);
	पूर्ण
पूर्ण

अटल व्योम vgic_mmio_ग_लिखो_sgipends(काष्ठा kvm_vcpu *vcpu,
				     gpa_t addr, अचिन्हित पूर्णांक len,
				     अचिन्हित दीर्घ val)
अणु
	u32 पूर्णांकid = addr & 0x0f;
	पूर्णांक i;
	अचिन्हित दीर्घ flags;

	क्रम (i = 0; i < len; i++) अणु
		काष्ठा vgic_irq *irq = vgic_get_irq(vcpu->kvm, vcpu, पूर्णांकid + i);

		raw_spin_lock_irqsave(&irq->irq_lock, flags);

		irq->source |= (val >> (i * 8)) & 0xff;

		अगर (irq->source) अणु
			irq->pending_latch = true;
			vgic_queue_irq_unlock(vcpu->kvm, irq, flags);
		पूर्ण अन्यथा अणु
			raw_spin_unlock_irqrestore(&irq->irq_lock, flags);
		पूर्ण
		vgic_put_irq(vcpu->kvm, irq);
	पूर्ण
पूर्ण

#घोषणा GICC_ARCH_VERSION_V2	0x2

/* These are क्रम userland accesses only, there is no guest-facing emulation. */
अटल अचिन्हित दीर्घ vgic_mmio_पढ़ो_vcpuअगर(काष्ठा kvm_vcpu *vcpu,
					   gpa_t addr, अचिन्हित पूर्णांक len)
अणु
	काष्ठा vgic_vmcr vmcr;
	u32 val;

	vgic_get_vmcr(vcpu, &vmcr);

	चयन (addr & 0xff) अणु
	हाल GIC_CPU_CTRL:
		val = vmcr.grpen0 << GIC_CPU_CTRL_EnableGrp0_SHIFT;
		val |= vmcr.grpen1 << GIC_CPU_CTRL_EnableGrp1_SHIFT;
		val |= vmcr.ackctl << GIC_CPU_CTRL_AckCtl_SHIFT;
		val |= vmcr.fiqen << GIC_CPU_CTRL_FIQEn_SHIFT;
		val |= vmcr.cbpr << GIC_CPU_CTRL_CBPR_SHIFT;
		val |= vmcr.eoim << GIC_CPU_CTRL_EOImodeNS_SHIFT;

		अवरोध;
	हाल GIC_CPU_PRIMASK:
		/*
		 * Our KVM_DEV_TYPE_ARM_VGIC_V2 device ABI exports the
		 * the PMR field as GICH_VMCR.VMPriMask rather than
		 * GICC_PMR.Priority, so we expose the upper five bits of
		 * priority mask to userspace using the lower bits in the
		 * अचिन्हित दीर्घ.
		 */
		val = (vmcr.pmr & GICV_PMR_PRIORITY_MASK) >>
			GICV_PMR_PRIORITY_SHIFT;
		अवरोध;
	हाल GIC_CPU_BINPOINT:
		val = vmcr.bpr;
		अवरोध;
	हाल GIC_CPU_ALIAS_BINPOINT:
		val = vmcr.abpr;
		अवरोध;
	हाल GIC_CPU_IDENT:
		val = ((PRODUCT_ID_KVM << 20) |
		       (GICC_ARCH_VERSION_V2 << 16) |
		       IMPLEMENTER_ARM);
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	वापस val;
पूर्ण

अटल व्योम vgic_mmio_ग_लिखो_vcpuअगर(काष्ठा kvm_vcpu *vcpu,
				   gpa_t addr, अचिन्हित पूर्णांक len,
				   अचिन्हित दीर्घ val)
अणु
	काष्ठा vgic_vmcr vmcr;

	vgic_get_vmcr(vcpu, &vmcr);

	चयन (addr & 0xff) अणु
	हाल GIC_CPU_CTRL:
		vmcr.grpen0 = !!(val & GIC_CPU_CTRL_EnableGrp0);
		vmcr.grpen1 = !!(val & GIC_CPU_CTRL_EnableGrp1);
		vmcr.ackctl = !!(val & GIC_CPU_CTRL_AckCtl);
		vmcr.fiqen = !!(val & GIC_CPU_CTRL_FIQEn);
		vmcr.cbpr = !!(val & GIC_CPU_CTRL_CBPR);
		vmcr.eoim = !!(val & GIC_CPU_CTRL_EOImodeNS);

		अवरोध;
	हाल GIC_CPU_PRIMASK:
		/*
		 * Our KVM_DEV_TYPE_ARM_VGIC_V2 device ABI exports the
		 * the PMR field as GICH_VMCR.VMPriMask rather than
		 * GICC_PMR.Priority, so we expose the upper five bits of
		 * priority mask to userspace using the lower bits in the
		 * अचिन्हित दीर्घ.
		 */
		vmcr.pmr = (val << GICV_PMR_PRIORITY_SHIFT) &
			GICV_PMR_PRIORITY_MASK;
		अवरोध;
	हाल GIC_CPU_BINPOINT:
		vmcr.bpr = val;
		अवरोध;
	हाल GIC_CPU_ALIAS_BINPOINT:
		vmcr.abpr = val;
		अवरोध;
	पूर्ण

	vgic_set_vmcr(vcpu, &vmcr);
पूर्ण

अटल अचिन्हित दीर्घ vgic_mmio_पढ़ो_apr(काष्ठा kvm_vcpu *vcpu,
					gpa_t addr, अचिन्हित पूर्णांक len)
अणु
	पूर्णांक n; /* which APRn is this */

	n = (addr >> 2) & 0x3;

	अगर (kvm_vgic_global_state.type == VGIC_V2) अणु
		/* GICv2 hardware प्रणालीs support max. 32 groups */
		अगर (n != 0)
			वापस 0;
		वापस vcpu->arch.vgic_cpu.vgic_v2.vgic_apr;
	पूर्ण अन्यथा अणु
		काष्ठा vgic_v3_cpu_अगर *vgicv3 = &vcpu->arch.vgic_cpu.vgic_v3;

		अगर (n > vgic_v3_max_apr_idx(vcpu))
			वापस 0;

		n = array_index_nospec(n, 4);

		/* GICv3 only uses ICH_AP1Rn क्रम memory mapped (GICv2) guests */
		वापस vgicv3->vgic_ap1r[n];
	पूर्ण
पूर्ण

अटल व्योम vgic_mmio_ग_लिखो_apr(काष्ठा kvm_vcpu *vcpu,
				gpa_t addr, अचिन्हित पूर्णांक len,
				अचिन्हित दीर्घ val)
अणु
	पूर्णांक n; /* which APRn is this */

	n = (addr >> 2) & 0x3;

	अगर (kvm_vgic_global_state.type == VGIC_V2) अणु
		/* GICv2 hardware प्रणालीs support max. 32 groups */
		अगर (n != 0)
			वापस;
		vcpu->arch.vgic_cpu.vgic_v2.vgic_apr = val;
	पूर्ण अन्यथा अणु
		काष्ठा vgic_v3_cpu_अगर *vgicv3 = &vcpu->arch.vgic_cpu.vgic_v3;

		अगर (n > vgic_v3_max_apr_idx(vcpu))
			वापस;

		n = array_index_nospec(n, 4);

		/* GICv3 only uses ICH_AP1Rn क्रम memory mapped (GICv2) guests */
		vgicv3->vgic_ap1r[n] = val;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा vgic_रेजिस्टर_region vgic_v2_dist_रेजिस्टरs[] = अणु
	REGISTER_DESC_WITH_LENGTH_UACCESS(GIC_DIST_CTRL,
		vgic_mmio_पढ़ो_v2_misc, vgic_mmio_ग_लिखो_v2_misc,
		शून्य, vgic_mmio_uaccess_ग_लिखो_v2_misc,
		12, VGIC_ACCESS_32bit),
	REGISTER_DESC_WITH_BITS_PER_IRQ(GIC_DIST_IGROUP,
		vgic_mmio_पढ़ो_group, vgic_mmio_ग_लिखो_group,
		शून्य, vgic_mmio_uaccess_ग_लिखो_v2_group, 1,
		VGIC_ACCESS_32bit),
	REGISTER_DESC_WITH_BITS_PER_IRQ(GIC_DIST_ENABLE_SET,
		vgic_mmio_पढ़ो_enable, vgic_mmio_ग_लिखो_senable,
		शून्य, vgic_uaccess_ग_लिखो_senable, 1,
		VGIC_ACCESS_32bit),
	REGISTER_DESC_WITH_BITS_PER_IRQ(GIC_DIST_ENABLE_CLEAR,
		vgic_mmio_पढ़ो_enable, vgic_mmio_ग_लिखो_cenable,
		शून्य, vgic_uaccess_ग_लिखो_cenable, 1,
		VGIC_ACCESS_32bit),
	REGISTER_DESC_WITH_BITS_PER_IRQ(GIC_DIST_PENDING_SET,
		vgic_mmio_पढ़ो_pending, vgic_mmio_ग_लिखो_spending,
		शून्य, vgic_uaccess_ग_लिखो_spending, 1,
		VGIC_ACCESS_32bit),
	REGISTER_DESC_WITH_BITS_PER_IRQ(GIC_DIST_PENDING_CLEAR,
		vgic_mmio_पढ़ो_pending, vgic_mmio_ग_लिखो_cpending,
		शून्य, vgic_uaccess_ग_लिखो_cpending, 1,
		VGIC_ACCESS_32bit),
	REGISTER_DESC_WITH_BITS_PER_IRQ(GIC_DIST_ACTIVE_SET,
		vgic_mmio_पढ़ो_active, vgic_mmio_ग_लिखो_sactive,
		vgic_uaccess_पढ़ो_active, vgic_mmio_uaccess_ग_लिखो_sactive, 1,
		VGIC_ACCESS_32bit),
	REGISTER_DESC_WITH_BITS_PER_IRQ(GIC_DIST_ACTIVE_CLEAR,
		vgic_mmio_पढ़ो_active, vgic_mmio_ग_लिखो_cactive,
		vgic_uaccess_पढ़ो_active, vgic_mmio_uaccess_ग_लिखो_cactive, 1,
		VGIC_ACCESS_32bit),
	REGISTER_DESC_WITH_BITS_PER_IRQ(GIC_DIST_PRI,
		vgic_mmio_पढ़ो_priority, vgic_mmio_ग_लिखो_priority, शून्य, शून्य,
		8, VGIC_ACCESS_32bit | VGIC_ACCESS_8bit),
	REGISTER_DESC_WITH_BITS_PER_IRQ(GIC_DIST_TARGET,
		vgic_mmio_पढ़ो_target, vgic_mmio_ग_लिखो_target, शून्य, शून्य, 8,
		VGIC_ACCESS_32bit | VGIC_ACCESS_8bit),
	REGISTER_DESC_WITH_BITS_PER_IRQ(GIC_DIST_CONFIG,
		vgic_mmio_पढ़ो_config, vgic_mmio_ग_लिखो_config, शून्य, शून्य, 2,
		VGIC_ACCESS_32bit),
	REGISTER_DESC_WITH_LENGTH(GIC_DIST_SOFTINT,
		vgic_mmio_पढ़ो_raz, vgic_mmio_ग_लिखो_sgir, 4,
		VGIC_ACCESS_32bit),
	REGISTER_DESC_WITH_LENGTH(GIC_DIST_SGI_PENDING_CLEAR,
		vgic_mmio_पढ़ो_sgipend, vgic_mmio_ग_लिखो_sgipendc, 16,
		VGIC_ACCESS_32bit | VGIC_ACCESS_8bit),
	REGISTER_DESC_WITH_LENGTH(GIC_DIST_SGI_PENDING_SET,
		vgic_mmio_पढ़ो_sgipend, vgic_mmio_ग_लिखो_sgipends, 16,
		VGIC_ACCESS_32bit | VGIC_ACCESS_8bit),
पूर्ण;

अटल स्थिर काष्ठा vgic_रेजिस्टर_region vgic_v2_cpu_रेजिस्टरs[] = अणु
	REGISTER_DESC_WITH_LENGTH(GIC_CPU_CTRL,
		vgic_mmio_पढ़ो_vcpuअगर, vgic_mmio_ग_लिखो_vcpuअगर, 4,
		VGIC_ACCESS_32bit),
	REGISTER_DESC_WITH_LENGTH(GIC_CPU_PRIMASK,
		vgic_mmio_पढ़ो_vcpuअगर, vgic_mmio_ग_लिखो_vcpuअगर, 4,
		VGIC_ACCESS_32bit),
	REGISTER_DESC_WITH_LENGTH(GIC_CPU_BINPOINT,
		vgic_mmio_पढ़ो_vcpuअगर, vgic_mmio_ग_लिखो_vcpuअगर, 4,
		VGIC_ACCESS_32bit),
	REGISTER_DESC_WITH_LENGTH(GIC_CPU_ALIAS_BINPOINT,
		vgic_mmio_पढ़ो_vcpuअगर, vgic_mmio_ग_लिखो_vcpuअगर, 4,
		VGIC_ACCESS_32bit),
	REGISTER_DESC_WITH_LENGTH(GIC_CPU_ACTIVEPRIO,
		vgic_mmio_पढ़ो_apr, vgic_mmio_ग_लिखो_apr, 16,
		VGIC_ACCESS_32bit),
	REGISTER_DESC_WITH_LENGTH(GIC_CPU_IDENT,
		vgic_mmio_पढ़ो_vcpuअगर, vgic_mmio_ग_लिखो_vcpuअगर, 4,
		VGIC_ACCESS_32bit),
पूर्ण;

अचिन्हित पूर्णांक vgic_v2_init_dist_iodev(काष्ठा vgic_io_device *dev)
अणु
	dev->regions = vgic_v2_dist_रेजिस्टरs;
	dev->nr_regions = ARRAY_SIZE(vgic_v2_dist_रेजिस्टरs);

	kvm_iodevice_init(&dev->dev, &kvm_io_gic_ops);

	वापस SZ_4K;
पूर्ण

पूर्णांक vgic_v2_has_attr_regs(काष्ठा kvm_device *dev, काष्ठा kvm_device_attr *attr)
अणु
	स्थिर काष्ठा vgic_रेजिस्टर_region *region;
	काष्ठा vgic_io_device iodev;
	काष्ठा vgic_reg_attr reg_attr;
	काष्ठा kvm_vcpu *vcpu;
	gpa_t addr;
	पूर्णांक ret;

	ret = vgic_v2_parse_attr(dev, attr, &reg_attr);
	अगर (ret)
		वापस ret;

	vcpu = reg_attr.vcpu;
	addr = reg_attr.addr;

	चयन (attr->group) अणु
	हाल KVM_DEV_ARM_VGIC_GRP_DIST_REGS:
		iodev.regions = vgic_v2_dist_रेजिस्टरs;
		iodev.nr_regions = ARRAY_SIZE(vgic_v2_dist_रेजिस्टरs);
		iodev.base_addr = 0;
		अवरोध;
	हाल KVM_DEV_ARM_VGIC_GRP_CPU_REGS:
		iodev.regions = vgic_v2_cpu_रेजिस्टरs;
		iodev.nr_regions = ARRAY_SIZE(vgic_v2_cpu_रेजिस्टरs);
		iodev.base_addr = 0;
		अवरोध;
	शेष:
		वापस -ENXIO;
	पूर्ण

	/* We only support aligned 32-bit accesses. */
	अगर (addr & 3)
		वापस -ENXIO;

	region = vgic_get_mmio_region(vcpu, &iodev, addr, माप(u32));
	अगर (!region)
		वापस -ENXIO;

	वापस 0;
पूर्ण

पूर्णांक vgic_v2_cpuअगर_uaccess(काष्ठा kvm_vcpu *vcpu, bool is_ग_लिखो,
			  पूर्णांक offset, u32 *val)
अणु
	काष्ठा vgic_io_device dev = अणु
		.regions = vgic_v2_cpu_रेजिस्टरs,
		.nr_regions = ARRAY_SIZE(vgic_v2_cpu_रेजिस्टरs),
		.iodev_type = IODEV_CPUIF,
	पूर्ण;

	वापस vgic_uaccess(vcpu, &dev, is_ग_लिखो, offset, val);
पूर्ण

पूर्णांक vgic_v2_dist_uaccess(काष्ठा kvm_vcpu *vcpu, bool is_ग_लिखो,
			 पूर्णांक offset, u32 *val)
अणु
	काष्ठा vgic_io_device dev = अणु
		.regions = vgic_v2_dist_रेजिस्टरs,
		.nr_regions = ARRAY_SIZE(vgic_v2_dist_रेजिस्टरs),
		.iodev_type = IODEV_DIST,
	पूर्ण;

	वापस vgic_uaccess(vcpu, &dev, is_ग_लिखो, offset, val);
पूर्ण
