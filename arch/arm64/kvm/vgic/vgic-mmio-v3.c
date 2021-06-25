<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * VGICv3 MMIO handling functions
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/irqchip/arm-gic-v3.h>
#समावेश <linux/kvm.h>
#समावेश <linux/kvm_host.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <kvm/iodev.h>
#समावेश <kvm/arm_vgic.h>

#समावेश <यंत्र/kvm_emulate.h>
#समावेश <यंत्र/kvm_arm.h>
#समावेश <यंत्र/kvm_mmu.h>

#समावेश "vgic.h"
#समावेश "vgic-mmio.h"

/* extract @num bytes at @offset bytes offset in data */
अचिन्हित दीर्घ extract_bytes(u64 data, अचिन्हित पूर्णांक offset,
			    अचिन्हित पूर्णांक num)
अणु
	वापस (data >> (offset * 8)) & GENMASK_ULL(num * 8 - 1, 0);
पूर्ण

/* allows updates of any half of a 64-bit रेजिस्टर (or the whole thing) */
u64 update_64bit_reg(u64 reg, अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक len,
		     अचिन्हित दीर्घ val)
अणु
	पूर्णांक lower = (offset & 4) * 8;
	पूर्णांक upper = lower + 8 * len - 1;

	reg &= ~GENMASK_ULL(upper, lower);
	val &= GENMASK_ULL(len * 8 - 1, 0);

	वापस reg | ((u64)val << lower);
पूर्ण

bool vgic_has_its(काष्ठा kvm *kvm)
अणु
	काष्ठा vgic_dist *dist = &kvm->arch.vgic;

	अगर (dist->vgic_model != KVM_DEV_TYPE_ARM_VGIC_V3)
		वापस false;

	वापस dist->has_its;
पूर्ण

bool vgic_supports_direct_msis(काष्ठा kvm *kvm)
अणु
	वापस (kvm_vgic_global_state.has_gicv4_1 ||
		(kvm_vgic_global_state.has_gicv4 && vgic_has_its(kvm)));
पूर्ण

/*
 * The Revision field in the IIDR have the following meanings:
 *
 * Revision 2: Interrupt groups are guest-configurable and संकेतed using
 * 	       their configured groups.
 */

अटल अचिन्हित दीर्घ vgic_mmio_पढ़ो_v3_misc(काष्ठा kvm_vcpu *vcpu,
					    gpa_t addr, अचिन्हित पूर्णांक len)
अणु
	काष्ठा vgic_dist *vgic = &vcpu->kvm->arch.vgic;
	u32 value = 0;

	चयन (addr & 0x0c) अणु
	हाल GICD_CTLR:
		अगर (vgic->enabled)
			value |= GICD_CTLR_ENABLE_SS_G1;
		value |= GICD_CTLR_ARE_NS | GICD_CTLR_DS;
		अगर (vgic->nassgireq)
			value |= GICD_CTLR_nASSGIreq;
		अवरोध;
	हाल GICD_TYPER:
		value = vgic->nr_spis + VGIC_NR_PRIVATE_IRQS;
		value = (value >> 5) - 1;
		अगर (vgic_has_its(vcpu->kvm)) अणु
			value |= (INTERRUPT_ID_BITS_ITS - 1) << 19;
			value |= GICD_TYPER_LPIS;
		पूर्ण अन्यथा अणु
			value |= (INTERRUPT_ID_BITS_SPIS - 1) << 19;
		पूर्ण
		अवरोध;
	हाल GICD_TYPER2:
		अगर (kvm_vgic_global_state.has_gicv4_1 && gic_cpuअगर_has_vsgi())
			value = GICD_TYPER2_nASSGIcap;
		अवरोध;
	हाल GICD_IIDR:
		value = (PRODUCT_ID_KVM << GICD_IIDR_PRODUCT_ID_SHIFT) |
			(vgic->implementation_rev << GICD_IIDR_REVISION_SHIFT) |
			(IMPLEMENTER_ARM << GICD_IIDR_IMPLEMENTER_SHIFT);
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	वापस value;
पूर्ण

अटल व्योम vgic_mmio_ग_लिखो_v3_misc(काष्ठा kvm_vcpu *vcpu,
				    gpa_t addr, अचिन्हित पूर्णांक len,
				    अचिन्हित दीर्घ val)
अणु
	काष्ठा vgic_dist *dist = &vcpu->kvm->arch.vgic;

	चयन (addr & 0x0c) अणु
	हाल GICD_CTLR: अणु
		bool was_enabled, is_hwsgi;

		mutex_lock(&vcpu->kvm->lock);

		was_enabled = dist->enabled;
		is_hwsgi = dist->nassgireq;

		dist->enabled = val & GICD_CTLR_ENABLE_SS_G1;

		/* Not a GICv4.1? No HW SGIs */
		अगर (!kvm_vgic_global_state.has_gicv4_1 || !gic_cpuअगर_has_vsgi())
			val &= ~GICD_CTLR_nASSGIreq;

		/* Dist stays enabled? nASSGIreq is RO */
		अगर (was_enabled && dist->enabled) अणु
			val &= ~GICD_CTLR_nASSGIreq;
			val |= FIELD_PREP(GICD_CTLR_nASSGIreq, is_hwsgi);
		पूर्ण

		/* Switching HW SGIs? */
		dist->nassgireq = val & GICD_CTLR_nASSGIreq;
		अगर (is_hwsgi != dist->nassgireq)
			vgic_v4_configure_vsgis(vcpu->kvm);

		अगर (kvm_vgic_global_state.has_gicv4_1 &&
		    was_enabled != dist->enabled)
			kvm_make_all_cpus_request(vcpu->kvm, KVM_REQ_RELOAD_GICv4);
		अन्यथा अगर (!was_enabled && dist->enabled)
			vgic_kick_vcpus(vcpu->kvm);

		mutex_unlock(&vcpu->kvm->lock);
		अवरोध;
	पूर्ण
	हाल GICD_TYPER:
	हाल GICD_TYPER2:
	हाल GICD_IIDR:
		/* This is at best क्रम करोcumentation purposes... */
		वापस;
	पूर्ण
पूर्ण

अटल पूर्णांक vgic_mmio_uaccess_ग_लिखो_v3_misc(काष्ठा kvm_vcpu *vcpu,
					   gpa_t addr, अचिन्हित पूर्णांक len,
					   अचिन्हित दीर्घ val)
अणु
	काष्ठा vgic_dist *dist = &vcpu->kvm->arch.vgic;

	चयन (addr & 0x0c) अणु
	हाल GICD_TYPER2:
	हाल GICD_IIDR:
		अगर (val != vgic_mmio_पढ़ो_v3_misc(vcpu, addr, len))
			वापस -EINVAL;
		वापस 0;
	हाल GICD_CTLR:
		/* Not a GICv4.1? No HW SGIs */
		अगर (!kvm_vgic_global_state.has_gicv4_1)
			val &= ~GICD_CTLR_nASSGIreq;

		dist->enabled = val & GICD_CTLR_ENABLE_SS_G1;
		dist->nassgireq = val & GICD_CTLR_nASSGIreq;
		वापस 0;
	पूर्ण

	vgic_mmio_ग_लिखो_v3_misc(vcpu, addr, len, val);
	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ vgic_mmio_पढ़ो_irouter(काष्ठा kvm_vcpu *vcpu,
					    gpa_t addr, अचिन्हित पूर्णांक len)
अणु
	पूर्णांक पूर्णांकid = VGIC_ADDR_TO_INTID(addr, 64);
	काष्ठा vgic_irq *irq = vgic_get_irq(vcpu->kvm, शून्य, पूर्णांकid);
	अचिन्हित दीर्घ ret = 0;

	अगर (!irq)
		वापस 0;

	/* The upper word is RAZ क्रम us. */
	अगर (!(addr & 4))
		ret = extract_bytes(READ_ONCE(irq->mpidr), addr & 7, len);

	vgic_put_irq(vcpu->kvm, irq);
	वापस ret;
पूर्ण

अटल व्योम vgic_mmio_ग_लिखो_irouter(काष्ठा kvm_vcpu *vcpu,
				    gpa_t addr, अचिन्हित पूर्णांक len,
				    अचिन्हित दीर्घ val)
अणु
	पूर्णांक पूर्णांकid = VGIC_ADDR_TO_INTID(addr, 64);
	काष्ठा vgic_irq *irq;
	अचिन्हित दीर्घ flags;

	/* The upper word is WI क्रम us since we करोn't implement Aff3. */
	अगर (addr & 4)
		वापस;

	irq = vgic_get_irq(vcpu->kvm, शून्य, पूर्णांकid);

	अगर (!irq)
		वापस;

	raw_spin_lock_irqsave(&irq->irq_lock, flags);

	/* We only care about and preserve Aff0, Aff1 and Aff2. */
	irq->mpidr = val & GENMASK(23, 0);
	irq->target_vcpu = kvm_mpidr_to_vcpu(vcpu->kvm, irq->mpidr);

	raw_spin_unlock_irqrestore(&irq->irq_lock, flags);
	vgic_put_irq(vcpu->kvm, irq);
पूर्ण

अटल अचिन्हित दीर्घ vgic_mmio_पढ़ो_v3r_ctlr(काष्ठा kvm_vcpu *vcpu,
					     gpa_t addr, अचिन्हित पूर्णांक len)
अणु
	काष्ठा vgic_cpu *vgic_cpu = &vcpu->arch.vgic_cpu;

	वापस vgic_cpu->lpis_enabled ? GICR_CTLR_ENABLE_LPIS : 0;
पूर्ण


अटल व्योम vgic_mmio_ग_लिखो_v3r_ctlr(काष्ठा kvm_vcpu *vcpu,
				     gpa_t addr, अचिन्हित पूर्णांक len,
				     अचिन्हित दीर्घ val)
अणु
	काष्ठा vgic_cpu *vgic_cpu = &vcpu->arch.vgic_cpu;
	bool was_enabled = vgic_cpu->lpis_enabled;

	अगर (!vgic_has_its(vcpu->kvm))
		वापस;

	vgic_cpu->lpis_enabled = val & GICR_CTLR_ENABLE_LPIS;

	अगर (was_enabled && !vgic_cpu->lpis_enabled) अणु
		vgic_flush_pending_lpis(vcpu);
		vgic_its_invalidate_cache(vcpu->kvm);
	पूर्ण

	अगर (!was_enabled && vgic_cpu->lpis_enabled)
		vgic_enable_lpis(vcpu);
पूर्ण

अटल bool vgic_mmio_vcpu_rdist_is_last(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vgic_dist *vgic = &vcpu->kvm->arch.vgic;
	काष्ठा vgic_cpu *vgic_cpu = &vcpu->arch.vgic_cpu;
	काष्ठा vgic_redist_region *iter, *rdreg = vgic_cpu->rdreg;

	अगर (!rdreg)
		वापस false;

	अगर (vgic_cpu->rdreg_index < rdreg->मुक्त_index - 1) अणु
		वापस false;
	पूर्ण अन्यथा अगर (rdreg->count && vgic_cpu->rdreg_index == (rdreg->count - 1)) अणु
		काष्ठा list_head *rd_regions = &vgic->rd_regions;
		gpa_t end = rdreg->base + rdreg->count * KVM_VGIC_V3_REDIST_SIZE;

		/*
		 * the rdist is the last one of the redist region,
		 * check whether there is no other contiguous rdist region
		 */
		list_क्रम_each_entry(iter, rd_regions, list) अणु
			अगर (iter->base == end && iter->मुक्त_index > 0)
				वापस false;
		पूर्ण
	पूर्ण
	वापस true;
पूर्ण

अटल अचिन्हित दीर्घ vgic_mmio_पढ़ो_v3r_typer(काष्ठा kvm_vcpu *vcpu,
					      gpa_t addr, अचिन्हित पूर्णांक len)
अणु
	अचिन्हित दीर्घ mpidr = kvm_vcpu_get_mpidr_aff(vcpu);
	पूर्णांक target_vcpu_id = vcpu->vcpu_id;
	u64 value;

	value = (u64)(mpidr & GENMASK(23, 0)) << 32;
	value |= ((target_vcpu_id & 0xffff) << 8);

	अगर (vgic_has_its(vcpu->kvm))
		value |= GICR_TYPER_PLPIS;

	अगर (vgic_mmio_vcpu_rdist_is_last(vcpu))
		value |= GICR_TYPER_LAST;

	वापस extract_bytes(value, addr & 7, len);
पूर्ण

अटल अचिन्हित दीर्घ vgic_mmio_पढ़ो_v3r_iidr(काष्ठा kvm_vcpu *vcpu,
					     gpa_t addr, अचिन्हित पूर्णांक len)
अणु
	वापस (PRODUCT_ID_KVM << 24) | (IMPLEMENTER_ARM << 0);
पूर्ण

अटल अचिन्हित दीर्घ vgic_mmio_पढ़ो_v3_idregs(काष्ठा kvm_vcpu *vcpu,
					      gpa_t addr, अचिन्हित पूर्णांक len)
अणु
	चयन (addr & 0xffff) अणु
	हाल GICD_PIDR2:
		/* report a GICv3 compliant implementation */
		वापस 0x3b;
	पूर्ण

	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ vgic_v3_uaccess_पढ़ो_pending(काष्ठा kvm_vcpu *vcpu,
						  gpa_t addr, अचिन्हित पूर्णांक len)
अणु
	u32 पूर्णांकid = VGIC_ADDR_TO_INTID(addr, 1);
	u32 value = 0;
	पूर्णांक i;

	/*
	 * pending state of पूर्णांकerrupt is latched in pending_latch variable.
	 * Userspace will save and restore pending state and line_level
	 * separately.
	 * Refer to Documentation/virt/kvm/devices/arm-vgic-v3.rst
	 * क्रम handling of ISPENDR and ICPENDR.
	 */
	क्रम (i = 0; i < len * 8; i++) अणु
		काष्ठा vgic_irq *irq = vgic_get_irq(vcpu->kvm, vcpu, पूर्णांकid + i);
		bool state = irq->pending_latch;

		अगर (irq->hw && vgic_irq_is_sgi(irq->पूर्णांकid)) अणु
			पूर्णांक err;

			err = irq_get_irqchip_state(irq->host_irq,
						    IRQCHIP_STATE_PENDING,
						    &state);
			WARN_ON(err);
		पूर्ण

		अगर (state)
			value |= (1U << i);

		vgic_put_irq(vcpu->kvm, irq);
	पूर्ण

	वापस value;
पूर्ण

अटल पूर्णांक vgic_v3_uaccess_ग_लिखो_pending(काष्ठा kvm_vcpu *vcpu,
					 gpa_t addr, अचिन्हित पूर्णांक len,
					 अचिन्हित दीर्घ val)
अणु
	u32 पूर्णांकid = VGIC_ADDR_TO_INTID(addr, 1);
	पूर्णांक i;
	अचिन्हित दीर्घ flags;

	क्रम (i = 0; i < len * 8; i++) अणु
		काष्ठा vgic_irq *irq = vgic_get_irq(vcpu->kvm, vcpu, पूर्णांकid + i);

		raw_spin_lock_irqsave(&irq->irq_lock, flags);
		अगर (test_bit(i, &val)) अणु
			/*
			 * pending_latch is set irrespective of irq type
			 * (level or edge) to aव्योम dependency that VM should
			 * restore irq config beक्रमe pending info.
			 */
			irq->pending_latch = true;
			vgic_queue_irq_unlock(vcpu->kvm, irq, flags);
		पूर्ण अन्यथा अणु
			irq->pending_latch = false;
			raw_spin_unlock_irqrestore(&irq->irq_lock, flags);
		पूर्ण

		vgic_put_irq(vcpu->kvm, irq);
	पूर्ण

	वापस 0;
पूर्ण

/* We want to aव्योम outer shareable. */
u64 vgic_sanitise_shareability(u64 field)
अणु
	चयन (field) अणु
	हाल GIC_BASER_OuterShareable:
		वापस GIC_BASER_InnerShareable;
	शेष:
		वापस field;
	पूर्ण
पूर्ण

/* Aव्योम any inner non-cacheable mapping. */
u64 vgic_sanitise_inner_cacheability(u64 field)
अणु
	चयन (field) अणु
	हाल GIC_BASER_CACHE_nCnB:
	हाल GIC_BASER_CACHE_nC:
		वापस GIC_BASER_CACHE_RaWb;
	शेष:
		वापस field;
	पूर्ण
पूर्ण

/* Non-cacheable or same-as-inner are OK. */
u64 vgic_sanitise_outer_cacheability(u64 field)
अणु
	चयन (field) अणु
	हाल GIC_BASER_CACHE_SameAsInner:
	हाल GIC_BASER_CACHE_nC:
		वापस field;
	शेष:
		वापस GIC_BASER_CACHE_SameAsInner;
	पूर्ण
पूर्ण

u64 vgic_sanitise_field(u64 reg, u64 field_mask, पूर्णांक field_shअगरt,
			u64 (*sanitise_fn)(u64))
अणु
	u64 field = (reg & field_mask) >> field_shअगरt;

	field = sanitise_fn(field) << field_shअगरt;
	वापस (reg & ~field_mask) | field;
पूर्ण

#घोषणा PROPBASER_RES0_MASK						\
	(GENMASK_ULL(63, 59) | GENMASK_ULL(55, 52) | GENMASK_ULL(6, 5))
#घोषणा PENDBASER_RES0_MASK						\
	(BIT_ULL(63) | GENMASK_ULL(61, 59) | GENMASK_ULL(55, 52) |	\
	 GENMASK_ULL(15, 12) | GENMASK_ULL(6, 0))

अटल u64 vgic_sanitise_pendbaser(u64 reg)
अणु
	reg = vgic_sanitise_field(reg, GICR_PENDBASER_SHAREABILITY_MASK,
				  GICR_PENDBASER_SHAREABILITY_SHIFT,
				  vgic_sanitise_shareability);
	reg = vgic_sanitise_field(reg, GICR_PENDBASER_INNER_CACHEABILITY_MASK,
				  GICR_PENDBASER_INNER_CACHEABILITY_SHIFT,
				  vgic_sanitise_inner_cacheability);
	reg = vgic_sanitise_field(reg, GICR_PENDBASER_OUTER_CACHEABILITY_MASK,
				  GICR_PENDBASER_OUTER_CACHEABILITY_SHIFT,
				  vgic_sanitise_outer_cacheability);

	reg &= ~PENDBASER_RES0_MASK;

	वापस reg;
पूर्ण

अटल u64 vgic_sanitise_propbaser(u64 reg)
अणु
	reg = vgic_sanitise_field(reg, GICR_PROPBASER_SHAREABILITY_MASK,
				  GICR_PROPBASER_SHAREABILITY_SHIFT,
				  vgic_sanitise_shareability);
	reg = vgic_sanitise_field(reg, GICR_PROPBASER_INNER_CACHEABILITY_MASK,
				  GICR_PROPBASER_INNER_CACHEABILITY_SHIFT,
				  vgic_sanitise_inner_cacheability);
	reg = vgic_sanitise_field(reg, GICR_PROPBASER_OUTER_CACHEABILITY_MASK,
				  GICR_PROPBASER_OUTER_CACHEABILITY_SHIFT,
				  vgic_sanitise_outer_cacheability);

	reg &= ~PROPBASER_RES0_MASK;
	वापस reg;
पूर्ण

अटल अचिन्हित दीर्घ vgic_mmio_पढ़ो_propbase(काष्ठा kvm_vcpu *vcpu,
					     gpa_t addr, अचिन्हित पूर्णांक len)
अणु
	काष्ठा vgic_dist *dist = &vcpu->kvm->arch.vgic;

	वापस extract_bytes(dist->propbaser, addr & 7, len);
पूर्ण

अटल व्योम vgic_mmio_ग_लिखो_propbase(काष्ठा kvm_vcpu *vcpu,
				     gpa_t addr, अचिन्हित पूर्णांक len,
				     अचिन्हित दीर्घ val)
अणु
	काष्ठा vgic_dist *dist = &vcpu->kvm->arch.vgic;
	काष्ठा vgic_cpu *vgic_cpu = &vcpu->arch.vgic_cpu;
	u64 old_propbaser, propbaser;

	/* Storing a value with LPIs alपढ़ोy enabled is undefined */
	अगर (vgic_cpu->lpis_enabled)
		वापस;

	करो अणु
		old_propbaser = READ_ONCE(dist->propbaser);
		propbaser = old_propbaser;
		propbaser = update_64bit_reg(propbaser, addr & 4, len, val);
		propbaser = vgic_sanitise_propbaser(propbaser);
	पूर्ण जबतक (cmpxchg64(&dist->propbaser, old_propbaser,
			   propbaser) != old_propbaser);
पूर्ण

अटल अचिन्हित दीर्घ vgic_mmio_पढ़ो_pendbase(काष्ठा kvm_vcpu *vcpu,
					     gpa_t addr, अचिन्हित पूर्णांक len)
अणु
	काष्ठा vgic_cpu *vgic_cpu = &vcpu->arch.vgic_cpu;
	u64 value = vgic_cpu->pendbaser;

	value &= ~GICR_PENDBASER_PTZ;

	वापस extract_bytes(value, addr & 7, len);
पूर्ण

अटल व्योम vgic_mmio_ग_लिखो_pendbase(काष्ठा kvm_vcpu *vcpu,
				     gpa_t addr, अचिन्हित पूर्णांक len,
				     अचिन्हित दीर्घ val)
अणु
	काष्ठा vgic_cpu *vgic_cpu = &vcpu->arch.vgic_cpu;
	u64 old_pendbaser, pendbaser;

	/* Storing a value with LPIs alपढ़ोy enabled is undefined */
	अगर (vgic_cpu->lpis_enabled)
		वापस;

	करो अणु
		old_pendbaser = READ_ONCE(vgic_cpu->pendbaser);
		pendbaser = old_pendbaser;
		pendbaser = update_64bit_reg(pendbaser, addr & 4, len, val);
		pendbaser = vgic_sanitise_pendbaser(pendbaser);
	पूर्ण जबतक (cmpxchg64(&vgic_cpu->pendbaser, old_pendbaser,
			   pendbaser) != old_pendbaser);
पूर्ण

/*
 * The GICv3 per-IRQ रेजिस्टरs are split to control PPIs and SGIs in the
 * redistributors, जबतक SPIs are covered by रेजिस्टरs in the distributor
 * block. Trying to set निजी IRQs in this block माला_लो ignored.
 * We take some special care here to fix the calculation of the रेजिस्टर
 * offset.
 */
#घोषणा REGISTER_DESC_WITH_BITS_PER_IRQ_SHARED(off, rd, wr, ur, uw, bpi, acc) \
	अणु								\
		.reg_offset = off,					\
		.bits_per_irq = bpi,					\
		.len = (bpi * VGIC_NR_PRIVATE_IRQS) / 8,		\
		.access_flags = acc,					\
		.पढ़ो = vgic_mmio_पढ़ो_raz,				\
		.ग_लिखो = vgic_mmio_ग_लिखो_wi,				\
	पूर्ण, अणु								\
		.reg_offset = off + (bpi * VGIC_NR_PRIVATE_IRQS) / 8,	\
		.bits_per_irq = bpi,					\
		.len = (bpi * (1024 - VGIC_NR_PRIVATE_IRQS)) / 8,	\
		.access_flags = acc,					\
		.पढ़ो = rd,						\
		.ग_लिखो = wr,						\
		.uaccess_पढ़ो = ur,					\
		.uaccess_ग_लिखो = uw,					\
	पूर्ण

अटल स्थिर काष्ठा vgic_रेजिस्टर_region vgic_v3_dist_रेजिस्टरs[] = अणु
	REGISTER_DESC_WITH_LENGTH_UACCESS(GICD_CTLR,
		vgic_mmio_पढ़ो_v3_misc, vgic_mmio_ग_लिखो_v3_misc,
		शून्य, vgic_mmio_uaccess_ग_लिखो_v3_misc,
		16, VGIC_ACCESS_32bit),
	REGISTER_DESC_WITH_LENGTH(GICD_STATUSR,
		vgic_mmio_पढ़ो_rao, vgic_mmio_ग_लिखो_wi, 4,
		VGIC_ACCESS_32bit),
	REGISTER_DESC_WITH_BITS_PER_IRQ_SHARED(GICD_IGROUPR,
		vgic_mmio_पढ़ो_group, vgic_mmio_ग_लिखो_group, शून्य, शून्य, 1,
		VGIC_ACCESS_32bit),
	REGISTER_DESC_WITH_BITS_PER_IRQ_SHARED(GICD_ISENABLER,
		vgic_mmio_पढ़ो_enable, vgic_mmio_ग_लिखो_senable,
		शून्य, vgic_uaccess_ग_लिखो_senable, 1,
		VGIC_ACCESS_32bit),
	REGISTER_DESC_WITH_BITS_PER_IRQ_SHARED(GICD_ICENABLER,
		vgic_mmio_पढ़ो_enable, vgic_mmio_ग_लिखो_cenable,
	       शून्य, vgic_uaccess_ग_लिखो_cenable, 1,
		VGIC_ACCESS_32bit),
	REGISTER_DESC_WITH_BITS_PER_IRQ_SHARED(GICD_ISPENDR,
		vgic_mmio_पढ़ो_pending, vgic_mmio_ग_लिखो_spending,
		vgic_v3_uaccess_पढ़ो_pending, vgic_v3_uaccess_ग_लिखो_pending, 1,
		VGIC_ACCESS_32bit),
	REGISTER_DESC_WITH_BITS_PER_IRQ_SHARED(GICD_ICPENDR,
		vgic_mmio_पढ़ो_pending, vgic_mmio_ग_लिखो_cpending,
		vgic_mmio_पढ़ो_raz, vgic_mmio_uaccess_ग_लिखो_wi, 1,
		VGIC_ACCESS_32bit),
	REGISTER_DESC_WITH_BITS_PER_IRQ_SHARED(GICD_ISACTIVER,
		vgic_mmio_पढ़ो_active, vgic_mmio_ग_लिखो_sactive,
		vgic_uaccess_पढ़ो_active, vgic_mmio_uaccess_ग_लिखो_sactive, 1,
		VGIC_ACCESS_32bit),
	REGISTER_DESC_WITH_BITS_PER_IRQ_SHARED(GICD_ICACTIVER,
		vgic_mmio_पढ़ो_active, vgic_mmio_ग_लिखो_cactive,
		vgic_uaccess_पढ़ो_active, vgic_mmio_uaccess_ग_लिखो_cactive,
		1, VGIC_ACCESS_32bit),
	REGISTER_DESC_WITH_BITS_PER_IRQ_SHARED(GICD_IPRIORITYR,
		vgic_mmio_पढ़ो_priority, vgic_mmio_ग_लिखो_priority, शून्य, शून्य,
		8, VGIC_ACCESS_32bit | VGIC_ACCESS_8bit),
	REGISTER_DESC_WITH_BITS_PER_IRQ_SHARED(GICD_ITARGETSR,
		vgic_mmio_पढ़ो_raz, vgic_mmio_ग_लिखो_wi, शून्य, शून्य, 8,
		VGIC_ACCESS_32bit | VGIC_ACCESS_8bit),
	REGISTER_DESC_WITH_BITS_PER_IRQ_SHARED(GICD_ICFGR,
		vgic_mmio_पढ़ो_config, vgic_mmio_ग_लिखो_config, शून्य, शून्य, 2,
		VGIC_ACCESS_32bit),
	REGISTER_DESC_WITH_BITS_PER_IRQ_SHARED(GICD_IGRPMODR,
		vgic_mmio_पढ़ो_raz, vgic_mmio_ग_लिखो_wi, शून्य, शून्य, 1,
		VGIC_ACCESS_32bit),
	REGISTER_DESC_WITH_BITS_PER_IRQ_SHARED(GICD_IROUTER,
		vgic_mmio_पढ़ो_irouter, vgic_mmio_ग_लिखो_irouter, शून्य, शून्य, 64,
		VGIC_ACCESS_64bit | VGIC_ACCESS_32bit),
	REGISTER_DESC_WITH_LENGTH(GICD_IDREGS,
		vgic_mmio_पढ़ो_v3_idregs, vgic_mmio_ग_लिखो_wi, 48,
		VGIC_ACCESS_32bit),
पूर्ण;

अटल स्थिर काष्ठा vgic_रेजिस्टर_region vgic_v3_rd_रेजिस्टरs[] = अणु
	/* RD_base रेजिस्टरs */
	REGISTER_DESC_WITH_LENGTH(GICR_CTLR,
		vgic_mmio_पढ़ो_v3r_ctlr, vgic_mmio_ग_लिखो_v3r_ctlr, 4,
		VGIC_ACCESS_32bit),
	REGISTER_DESC_WITH_LENGTH(GICR_STATUSR,
		vgic_mmio_पढ़ो_raz, vgic_mmio_ग_लिखो_wi, 4,
		VGIC_ACCESS_32bit),
	REGISTER_DESC_WITH_LENGTH(GICR_IIDR,
		vgic_mmio_पढ़ो_v3r_iidr, vgic_mmio_ग_लिखो_wi, 4,
		VGIC_ACCESS_32bit),
	REGISTER_DESC_WITH_LENGTH_UACCESS(GICR_TYPER,
		vgic_mmio_पढ़ो_v3r_typer, vgic_mmio_ग_लिखो_wi,
		शून्य, vgic_mmio_uaccess_ग_लिखो_wi, 8,
		VGIC_ACCESS_64bit | VGIC_ACCESS_32bit),
	REGISTER_DESC_WITH_LENGTH(GICR_WAKER,
		vgic_mmio_पढ़ो_raz, vgic_mmio_ग_लिखो_wi, 4,
		VGIC_ACCESS_32bit),
	REGISTER_DESC_WITH_LENGTH(GICR_PROPBASER,
		vgic_mmio_पढ़ो_propbase, vgic_mmio_ग_लिखो_propbase, 8,
		VGIC_ACCESS_64bit | VGIC_ACCESS_32bit),
	REGISTER_DESC_WITH_LENGTH(GICR_PENDBASER,
		vgic_mmio_पढ़ो_pendbase, vgic_mmio_ग_लिखो_pendbase, 8,
		VGIC_ACCESS_64bit | VGIC_ACCESS_32bit),
	REGISTER_DESC_WITH_LENGTH(GICR_IDREGS,
		vgic_mmio_पढ़ो_v3_idregs, vgic_mmio_ग_लिखो_wi, 48,
		VGIC_ACCESS_32bit),
	/* SGI_base रेजिस्टरs */
	REGISTER_DESC_WITH_LENGTH(SZ_64K + GICR_IGROUPR0,
		vgic_mmio_पढ़ो_group, vgic_mmio_ग_लिखो_group, 4,
		VGIC_ACCESS_32bit),
	REGISTER_DESC_WITH_LENGTH_UACCESS(SZ_64K + GICR_ISENABLER0,
		vgic_mmio_पढ़ो_enable, vgic_mmio_ग_लिखो_senable,
		शून्य, vgic_uaccess_ग_लिखो_senable, 4,
		VGIC_ACCESS_32bit),
	REGISTER_DESC_WITH_LENGTH_UACCESS(SZ_64K + GICR_ICENABLER0,
		vgic_mmio_पढ़ो_enable, vgic_mmio_ग_लिखो_cenable,
		शून्य, vgic_uaccess_ग_लिखो_cenable, 4,
		VGIC_ACCESS_32bit),
	REGISTER_DESC_WITH_LENGTH_UACCESS(SZ_64K + GICR_ISPENDR0,
		vgic_mmio_पढ़ो_pending, vgic_mmio_ग_लिखो_spending,
		vgic_v3_uaccess_पढ़ो_pending, vgic_v3_uaccess_ग_लिखो_pending, 4,
		VGIC_ACCESS_32bit),
	REGISTER_DESC_WITH_LENGTH_UACCESS(SZ_64K + GICR_ICPENDR0,
		vgic_mmio_पढ़ो_pending, vgic_mmio_ग_लिखो_cpending,
		vgic_mmio_पढ़ो_raz, vgic_mmio_uaccess_ग_लिखो_wi, 4,
		VGIC_ACCESS_32bit),
	REGISTER_DESC_WITH_LENGTH_UACCESS(SZ_64K + GICR_ISACTIVER0,
		vgic_mmio_पढ़ो_active, vgic_mmio_ग_लिखो_sactive,
		vgic_uaccess_पढ़ो_active, vgic_mmio_uaccess_ग_लिखो_sactive, 4,
		VGIC_ACCESS_32bit),
	REGISTER_DESC_WITH_LENGTH_UACCESS(SZ_64K + GICR_ICACTIVER0,
		vgic_mmio_पढ़ो_active, vgic_mmio_ग_लिखो_cactive,
		vgic_uaccess_पढ़ो_active, vgic_mmio_uaccess_ग_लिखो_cactive, 4,
		VGIC_ACCESS_32bit),
	REGISTER_DESC_WITH_LENGTH(SZ_64K + GICR_IPRIORITYR0,
		vgic_mmio_पढ़ो_priority, vgic_mmio_ग_लिखो_priority, 32,
		VGIC_ACCESS_32bit | VGIC_ACCESS_8bit),
	REGISTER_DESC_WITH_LENGTH(SZ_64K + GICR_ICFGR0,
		vgic_mmio_पढ़ो_config, vgic_mmio_ग_लिखो_config, 8,
		VGIC_ACCESS_32bit),
	REGISTER_DESC_WITH_LENGTH(SZ_64K + GICR_IGRPMODR0,
		vgic_mmio_पढ़ो_raz, vgic_mmio_ग_लिखो_wi, 4,
		VGIC_ACCESS_32bit),
	REGISTER_DESC_WITH_LENGTH(SZ_64K + GICR_NSACR,
		vgic_mmio_पढ़ो_raz, vgic_mmio_ग_लिखो_wi, 4,
		VGIC_ACCESS_32bit),
पूर्ण;

अचिन्हित पूर्णांक vgic_v3_init_dist_iodev(काष्ठा vgic_io_device *dev)
अणु
	dev->regions = vgic_v3_dist_रेजिस्टरs;
	dev->nr_regions = ARRAY_SIZE(vgic_v3_dist_रेजिस्टरs);

	kvm_iodevice_init(&dev->dev, &kvm_io_gic_ops);

	वापस SZ_64K;
पूर्ण

/**
 * vgic_रेजिस्टर_redist_iodev - रेजिस्टर a single redist iodev
 * @vcpu:    The VCPU to which the redistributor beदीर्घs
 *
 * Register a KVM iodev क्रम this VCPU's redistributor using the address
 * provided.
 *
 * Return 0 on success, -ERRNO otherwise.
 */
पूर्णांक vgic_रेजिस्टर_redist_iodev(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm *kvm = vcpu->kvm;
	काष्ठा vgic_dist *vgic = &kvm->arch.vgic;
	काष्ठा vgic_cpu *vgic_cpu = &vcpu->arch.vgic_cpu;
	काष्ठा vgic_io_device *rd_dev = &vcpu->arch.vgic_cpu.rd_iodev;
	काष्ठा vgic_redist_region *rdreg;
	gpa_t rd_base;
	पूर्णांक ret;

	अगर (!IS_VGIC_ADDR_UNDEF(vgic_cpu->rd_iodev.base_addr))
		वापस 0;

	/*
	 * We may be creating VCPUs beक्रमe having set the base address क्रम the
	 * redistributor region, in which हाल we will come back to this
	 * function क्रम all VCPUs when the base address is set.  Just वापस
	 * without करोing any work क्रम now.
	 */
	rdreg = vgic_v3_rdist_मुक्त_slot(&vgic->rd_regions);
	अगर (!rdreg)
		वापस 0;

	अगर (!vgic_v3_check_base(kvm))
		वापस -EINVAL;

	vgic_cpu->rdreg = rdreg;
	vgic_cpu->rdreg_index = rdreg->मुक्त_index;

	rd_base = rdreg->base + rdreg->मुक्त_index * KVM_VGIC_V3_REDIST_SIZE;

	kvm_iodevice_init(&rd_dev->dev, &kvm_io_gic_ops);
	rd_dev->base_addr = rd_base;
	rd_dev->iodev_type = IODEV_REDIST;
	rd_dev->regions = vgic_v3_rd_रेजिस्टरs;
	rd_dev->nr_regions = ARRAY_SIZE(vgic_v3_rd_रेजिस्टरs);
	rd_dev->redist_vcpu = vcpu;

	mutex_lock(&kvm->slots_lock);
	ret = kvm_io_bus_रेजिस्टर_dev(kvm, KVM_MMIO_BUS, rd_base,
				      2 * SZ_64K, &rd_dev->dev);
	mutex_unlock(&kvm->slots_lock);

	अगर (ret)
		वापस ret;

	rdreg->मुक्त_index++;
	वापस 0;
पूर्ण

अटल व्योम vgic_unरेजिस्टर_redist_iodev(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vgic_io_device *rd_dev = &vcpu->arch.vgic_cpu.rd_iodev;

	kvm_io_bus_unरेजिस्टर_dev(vcpu->kvm, KVM_MMIO_BUS, &rd_dev->dev);
पूर्ण

अटल पूर्णांक vgic_रेजिस्टर_all_redist_iodevs(काष्ठा kvm *kvm)
अणु
	काष्ठा kvm_vcpu *vcpu;
	पूर्णांक c, ret = 0;

	kvm_क्रम_each_vcpu(c, vcpu, kvm) अणु
		ret = vgic_रेजिस्टर_redist_iodev(vcpu);
		अगर (ret)
			अवरोध;
	पूर्ण

	अगर (ret) अणु
		/* The current c failed, so we start with the previous one. */
		mutex_lock(&kvm->slots_lock);
		क्रम (c--; c >= 0; c--) अणु
			vcpu = kvm_get_vcpu(kvm, c);
			vgic_unरेजिस्टर_redist_iodev(vcpu);
		पूर्ण
		mutex_unlock(&kvm->slots_lock);
	पूर्ण

	वापस ret;
पूर्ण

/**
 * vgic_v3_alloc_redist_region - Allocate a new redistributor region
 *
 * Perक्रमms various checks beक्रमe inserting the rdist region in the list.
 * Those tests depend on whether the size of the rdist region is known
 * (ie. count != 0). The list is sorted by rdist region index.
 *
 * @kvm: kvm handle
 * @index: redist region index
 * @base: base of the new rdist region
 * @count: number of redistributors the region is made of (0 in the old style
 * single region, whose size is induced from the number of vcpus)
 *
 * Return 0 on success, < 0 otherwise
 */
अटल पूर्णांक vgic_v3_alloc_redist_region(काष्ठा kvm *kvm, uपूर्णांक32_t index,
				       gpa_t base, uपूर्णांक32_t count)
अणु
	काष्ठा vgic_dist *d = &kvm->arch.vgic;
	काष्ठा vgic_redist_region *rdreg;
	काष्ठा list_head *rd_regions = &d->rd_regions;
	माप_प्रकार size = count * KVM_VGIC_V3_REDIST_SIZE;
	पूर्णांक ret;

	/* cross the end of memory ? */
	अगर (base + size < base)
		वापस -EINVAL;

	अगर (list_empty(rd_regions)) अणु
		अगर (index != 0)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		rdreg = list_last_entry(rd_regions,
					काष्ठा vgic_redist_region, list);

		/* Don't mix single region and discrete redist regions */
		अगर (!count && rdreg->count)
			वापस -EINVAL;

		अगर (!count)
			वापस -EEXIST;

		अगर (index != rdreg->index + 1)
			वापस -EINVAL;
	पूर्ण

	/*
	 * For legacy single-region redistributor regions (!count),
	 * check that the redistributor region करोes not overlap with the
	 * distributor's address space.
	 */
	अगर (!count && !IS_VGIC_ADDR_UNDEF(d->vgic_dist_base) &&
		vgic_dist_overlap(kvm, base, size))
		वापस -EINVAL;

	/* collision with any other rdist region? */
	अगर (vgic_v3_rdist_overlap(kvm, base, size))
		वापस -EINVAL;

	rdreg = kzalloc(माप(*rdreg), GFP_KERNEL);
	अगर (!rdreg)
		वापस -ENOMEM;

	rdreg->base = VGIC_ADDR_UNDEF;

	ret = vgic_check_ioaddr(kvm, &rdreg->base, base, SZ_64K);
	अगर (ret)
		जाओ मुक्त;

	rdreg->base = base;
	rdreg->count = count;
	rdreg->मुक्त_index = 0;
	rdreg->index = index;

	list_add_tail(&rdreg->list, rd_regions);
	वापस 0;
मुक्त:
	kमुक्त(rdreg);
	वापस ret;
पूर्ण

व्योम vgic_v3_मुक्त_redist_region(काष्ठा vgic_redist_region *rdreg)
अणु
	list_del(&rdreg->list);
	kमुक्त(rdreg);
पूर्ण

पूर्णांक vgic_v3_set_redist_base(काष्ठा kvm *kvm, u32 index, u64 addr, u32 count)
अणु
	पूर्णांक ret;

	ret = vgic_v3_alloc_redist_region(kvm, index, addr, count);
	अगर (ret)
		वापस ret;

	/*
	 * Register iodevs क्रम each existing VCPU.  Adding more VCPUs
	 * afterwards will रेजिस्टर the iodevs when needed.
	 */
	ret = vgic_रेजिस्टर_all_redist_iodevs(kvm);
	अगर (ret) अणु
		काष्ठा vgic_redist_region *rdreg;

		rdreg = vgic_v3_rdist_region_from_index(kvm, index);
		vgic_v3_मुक्त_redist_region(rdreg);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक vgic_v3_has_attr_regs(काष्ठा kvm_device *dev, काष्ठा kvm_device_attr *attr)
अणु
	स्थिर काष्ठा vgic_रेजिस्टर_region *region;
	काष्ठा vgic_io_device iodev;
	काष्ठा vgic_reg_attr reg_attr;
	काष्ठा kvm_vcpu *vcpu;
	gpa_t addr;
	पूर्णांक ret;

	ret = vgic_v3_parse_attr(dev, attr, &reg_attr);
	अगर (ret)
		वापस ret;

	vcpu = reg_attr.vcpu;
	addr = reg_attr.addr;

	चयन (attr->group) अणु
	हाल KVM_DEV_ARM_VGIC_GRP_DIST_REGS:
		iodev.regions = vgic_v3_dist_रेजिस्टरs;
		iodev.nr_regions = ARRAY_SIZE(vgic_v3_dist_रेजिस्टरs);
		iodev.base_addr = 0;
		अवरोध;
	हाल KVM_DEV_ARM_VGIC_GRP_REDIST_REGS:अणु
		iodev.regions = vgic_v3_rd_रेजिस्टरs;
		iodev.nr_regions = ARRAY_SIZE(vgic_v3_rd_रेजिस्टरs);
		iodev.base_addr = 0;
		अवरोध;
	पूर्ण
	हाल KVM_DEV_ARM_VGIC_GRP_CPU_SYSREGS: अणु
		u64 reg, id;

		id = (attr->attr & KVM_DEV_ARM_VGIC_SYSREG_INSTR_MASK);
		वापस vgic_v3_has_cpu_sysregs_attr(vcpu, 0, id, &reg);
	पूर्ण
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
/*
 * Compare a given affinity (level 1-3 and a level 0 mask, from the SGI
 * generation रेजिस्टर ICC_SGI1R_EL1) with a given VCPU.
 * If the VCPU's MPIDR matches, वापस the level0 affinity, otherwise
 * वापस -1.
 */
अटल पूर्णांक match_mpidr(u64 sgi_aff, u16 sgi_cpu_mask, काष्ठा kvm_vcpu *vcpu)
अणु
	अचिन्हित दीर्घ affinity;
	पूर्णांक level0;

	/*
	 * Split the current VCPU's MPIDR पूर्णांकo affinity level 0 and the
	 * rest as this is what we have to compare against.
	 */
	affinity = kvm_vcpu_get_mpidr_aff(vcpu);
	level0 = MPIDR_AFFINITY_LEVEL(affinity, 0);
	affinity &= ~MPIDR_LEVEL_MASK;

	/* bail out अगर the upper three levels करोn't match */
	अगर (sgi_aff != affinity)
		वापस -1;

	/* Is this VCPU's bit set in the mask ? */
	अगर (!(sgi_cpu_mask & BIT(level0)))
		वापस -1;

	वापस level0;
पूर्ण

/*
 * The ICC_SGI* रेजिस्टरs encode the affinity dअगरferently from the MPIDR,
 * so provide a wrapper to use the existing defines to isolate a certain
 * affinity level.
 */
#घोषणा SGI_AFFINITY_LEVEL(reg, level) \
	((((reg) & ICC_SGI1R_AFFINITY_## level ##_MASK) \
	>> ICC_SGI1R_AFFINITY_## level ##_SHIFT) << MPIDR_LEVEL_SHIFT(level))

/**
 * vgic_v3_dispatch_sgi - handle SGI requests from VCPUs
 * @vcpu: The VCPU requesting a SGI
 * @reg: The value written पूर्णांकo ICC_अणुASGI1,SGI0,SGI1पूर्णR by that VCPU
 * @allow_group1: Does the sysreg access allow generation of G1 SGIs
 *
 * With GICv3 (and ARE=1) CPUs trigger SGIs by writing to a प्रणाली रेजिस्टर.
 * This will trap in sys_regs.c and call this function.
 * This ICC_SGI1R_EL1 रेजिस्टर contains the upper three affinity levels of the
 * target processors as well as a biपंचांगask of 16 Aff0 CPUs.
 * If the पूर्णांकerrupt routing mode bit is not set, we iterate over all VCPUs to
 * check क्रम matching ones. If this bit is set, we संकेत all, but not the
 * calling VCPU.
 */
व्योम vgic_v3_dispatch_sgi(काष्ठा kvm_vcpu *vcpu, u64 reg, bool allow_group1)
अणु
	काष्ठा kvm *kvm = vcpu->kvm;
	काष्ठा kvm_vcpu *c_vcpu;
	u16 target_cpus;
	u64 mpidr;
	पूर्णांक sgi, c;
	पूर्णांक vcpu_id = vcpu->vcpu_id;
	bool broadcast;
	अचिन्हित दीर्घ flags;

	sgi = (reg & ICC_SGI1R_SGI_ID_MASK) >> ICC_SGI1R_SGI_ID_SHIFT;
	broadcast = reg & BIT_ULL(ICC_SGI1R_IRQ_ROUTING_MODE_BIT);
	target_cpus = (reg & ICC_SGI1R_TARGET_LIST_MASK) >> ICC_SGI1R_TARGET_LIST_SHIFT;
	mpidr = SGI_AFFINITY_LEVEL(reg, 3);
	mpidr |= SGI_AFFINITY_LEVEL(reg, 2);
	mpidr |= SGI_AFFINITY_LEVEL(reg, 1);

	/*
	 * We iterate over all VCPUs to find the MPIDRs matching the request.
	 * If we have handled one CPU, we clear its bit to detect early
	 * अगर we are alपढ़ोy finished. This aव्योमs iterating through all
	 * VCPUs when most of the बार we just संकेत a single VCPU.
	 */
	kvm_क्रम_each_vcpu(c, c_vcpu, kvm) अणु
		काष्ठा vgic_irq *irq;

		/* Exit early अगर we have dealt with all requested CPUs */
		अगर (!broadcast && target_cpus == 0)
			अवरोध;

		/* Don't संकेत the calling VCPU */
		अगर (broadcast && c == vcpu_id)
			जारी;

		अगर (!broadcast) अणु
			पूर्णांक level0;

			level0 = match_mpidr(mpidr, target_cpus, c_vcpu);
			अगर (level0 == -1)
				जारी;

			/* हटाओ this matching VCPU from the mask */
			target_cpus &= ~BIT(level0);
		पूर्ण

		irq = vgic_get_irq(vcpu->kvm, c_vcpu, sgi);

		raw_spin_lock_irqsave(&irq->irq_lock, flags);

		/*
		 * An access targeting Group0 SGIs can only generate
		 * those, जबतक an access targeting Group1 SGIs can
		 * generate पूर्णांकerrupts of either group.
		 */
		अगर (!irq->group || allow_group1) अणु
			अगर (!irq->hw) अणु
				irq->pending_latch = true;
				vgic_queue_irq_unlock(vcpu->kvm, irq, flags);
			पूर्ण अन्यथा अणु
				/* HW SGI? Ask the GIC to inject it */
				पूर्णांक err;
				err = irq_set_irqchip_state(irq->host_irq,
							    IRQCHIP_STATE_PENDING,
							    true);
				WARN_RATELIMIT(err, "IRQ %d", irq->host_irq);
				raw_spin_unlock_irqrestore(&irq->irq_lock, flags);
			पूर्ण
		पूर्ण अन्यथा अणु
			raw_spin_unlock_irqrestore(&irq->irq_lock, flags);
		पूर्ण

		vgic_put_irq(vcpu->kvm, irq);
	पूर्ण
पूर्ण

पूर्णांक vgic_v3_dist_uaccess(काष्ठा kvm_vcpu *vcpu, bool is_ग_लिखो,
			 पूर्णांक offset, u32 *val)
अणु
	काष्ठा vgic_io_device dev = अणु
		.regions = vgic_v3_dist_रेजिस्टरs,
		.nr_regions = ARRAY_SIZE(vgic_v3_dist_रेजिस्टरs),
	पूर्ण;

	वापस vgic_uaccess(vcpu, &dev, is_ग_लिखो, offset, val);
पूर्ण

पूर्णांक vgic_v3_redist_uaccess(काष्ठा kvm_vcpu *vcpu, bool is_ग_लिखो,
			   पूर्णांक offset, u32 *val)
अणु
	काष्ठा vgic_io_device rd_dev = अणु
		.regions = vgic_v3_rd_रेजिस्टरs,
		.nr_regions = ARRAY_SIZE(vgic_v3_rd_रेजिस्टरs),
	पूर्ण;

	वापस vgic_uaccess(vcpu, &rd_dev, is_ग_लिखो, offset, val);
पूर्ण

पूर्णांक vgic_v3_line_level_info_uaccess(काष्ठा kvm_vcpu *vcpu, bool is_ग_लिखो,
				    u32 पूर्णांकid, u64 *val)
अणु
	अगर (पूर्णांकid % 32)
		वापस -EINVAL;

	अगर (is_ग_लिखो)
		vgic_ग_लिखो_irq_line_level_info(vcpu, पूर्णांकid, *val);
	अन्यथा
		*val = vgic_पढ़ो_irq_line_level_info(vcpu, पूर्णांकid);

	वापस 0;
पूर्ण
