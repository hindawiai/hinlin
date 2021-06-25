<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2015, 2016 ARM Ltd.
 */
#अगर_अघोषित __KVM_ARM_VGIC_NEW_H__
#घोषणा __KVM_ARM_VGIC_NEW_H__

#समावेश <linux/irqchip/arm-gic-common.h>

#घोषणा PRODUCT_ID_KVM		0x4b	/* ASCII code K */
#घोषणा IMPLEMENTER_ARM		0x43b

#घोषणा VGIC_ADDR_UNDEF		(-1)
#घोषणा IS_VGIC_ADDR_UNDEF(_x)  ((_x) == VGIC_ADDR_UNDEF)

#घोषणा INTERRUPT_ID_BITS_SPIS	10
#घोषणा INTERRUPT_ID_BITS_ITS	16
#घोषणा VGIC_PRI_BITS		5

#घोषणा vgic_irq_is_sgi(पूर्णांकid) ((पूर्णांकid) < VGIC_NR_SGIS)

#घोषणा VGIC_AFFINITY_0_SHIFT 0
#घोषणा VGIC_AFFINITY_0_MASK (0xffUL << VGIC_AFFINITY_0_SHIFT)
#घोषणा VGIC_AFFINITY_1_SHIFT 8
#घोषणा VGIC_AFFINITY_1_MASK (0xffUL << VGIC_AFFINITY_1_SHIFT)
#घोषणा VGIC_AFFINITY_2_SHIFT 16
#घोषणा VGIC_AFFINITY_2_MASK (0xffUL << VGIC_AFFINITY_2_SHIFT)
#घोषणा VGIC_AFFINITY_3_SHIFT 24
#घोषणा VGIC_AFFINITY_3_MASK (0xffUL << VGIC_AFFINITY_3_SHIFT)

#घोषणा VGIC_AFFINITY_LEVEL(reg, level) \
	((((reg) & VGIC_AFFINITY_## level ##_MASK) \
	>> VGIC_AFFINITY_## level ##_SHIFT) << MPIDR_LEVEL_SHIFT(level))

/*
 * The Userspace encodes the affinity dअगरferently from the MPIDR,
 * Below macro converts vgic userspace क्रमmat to MPIDR reg क्रमmat.
 */
#घोषणा VGIC_TO_MPIDR(val) (VGIC_AFFINITY_LEVEL(val, 0) | \
			    VGIC_AFFINITY_LEVEL(val, 1) | \
			    VGIC_AFFINITY_LEVEL(val, 2) | \
			    VGIC_AFFINITY_LEVEL(val, 3))

/*
 * As per Documentation/virt/kvm/devices/arm-vgic-v3.rst,
 * below macros are defined क्रम CPUREG encoding.
 */
#घोषणा KVM_REG_ARM_VGIC_SYSREG_OP0_MASK   0x000000000000c000
#घोषणा KVM_REG_ARM_VGIC_SYSREG_OP0_SHIFT  14
#घोषणा KVM_REG_ARM_VGIC_SYSREG_OP1_MASK   0x0000000000003800
#घोषणा KVM_REG_ARM_VGIC_SYSREG_OP1_SHIFT  11
#घोषणा KVM_REG_ARM_VGIC_SYSREG_CRN_MASK   0x0000000000000780
#घोषणा KVM_REG_ARM_VGIC_SYSREG_CRN_SHIFT  7
#घोषणा KVM_REG_ARM_VGIC_SYSREG_CRM_MASK   0x0000000000000078
#घोषणा KVM_REG_ARM_VGIC_SYSREG_CRM_SHIFT  3
#घोषणा KVM_REG_ARM_VGIC_SYSREG_OP2_MASK   0x0000000000000007
#घोषणा KVM_REG_ARM_VGIC_SYSREG_OP2_SHIFT  0

#घोषणा KVM_DEV_ARM_VGIC_SYSREG_MASK (KVM_REG_ARM_VGIC_SYSREG_OP0_MASK | \
				      KVM_REG_ARM_VGIC_SYSREG_OP1_MASK | \
				      KVM_REG_ARM_VGIC_SYSREG_CRN_MASK | \
				      KVM_REG_ARM_VGIC_SYSREG_CRM_MASK | \
				      KVM_REG_ARM_VGIC_SYSREG_OP2_MASK)

/*
 * As per Documentation/virt/kvm/devices/arm-vgic-its.rst,
 * below macros are defined क्रम ITS table entry encoding.
 */
#घोषणा KVM_ITS_CTE_VALID_SHIFT		63
#घोषणा KVM_ITS_CTE_VALID_MASK		BIT_ULL(63)
#घोषणा KVM_ITS_CTE_RDBASE_SHIFT	16
#घोषणा KVM_ITS_CTE_ICID_MASK		GENMASK_ULL(15, 0)
#घोषणा KVM_ITS_ITE_NEXT_SHIFT		48
#घोषणा KVM_ITS_ITE_PINTID_SHIFT	16
#घोषणा KVM_ITS_ITE_PINTID_MASK		GENMASK_ULL(47, 16)
#घोषणा KVM_ITS_ITE_ICID_MASK		GENMASK_ULL(15, 0)
#घोषणा KVM_ITS_DTE_VALID_SHIFT		63
#घोषणा KVM_ITS_DTE_VALID_MASK		BIT_ULL(63)
#घोषणा KVM_ITS_DTE_NEXT_SHIFT		49
#घोषणा KVM_ITS_DTE_NEXT_MASK		GENMASK_ULL(62, 49)
#घोषणा KVM_ITS_DTE_ITTADDR_SHIFT	5
#घोषणा KVM_ITS_DTE_ITTADDR_MASK	GENMASK_ULL(48, 5)
#घोषणा KVM_ITS_DTE_SIZE_MASK		GENMASK_ULL(4, 0)
#घोषणा KVM_ITS_L1E_VALID_MASK		BIT_ULL(63)
/* we only support 64 kB translation table page size */
#घोषणा KVM_ITS_L1E_ADDR_MASK		GENMASK_ULL(51, 16)

#घोषणा KVM_VGIC_V3_RDIST_INDEX_MASK	GENMASK_ULL(11, 0)
#घोषणा KVM_VGIC_V3_RDIST_FLAGS_MASK	GENMASK_ULL(15, 12)
#घोषणा KVM_VGIC_V3_RDIST_FLAGS_SHIFT	12
#घोषणा KVM_VGIC_V3_RDIST_BASE_MASK	GENMASK_ULL(51, 16)
#घोषणा KVM_VGIC_V3_RDIST_COUNT_MASK	GENMASK_ULL(63, 52)
#घोषणा KVM_VGIC_V3_RDIST_COUNT_SHIFT	52

#अगर_घोषित CONFIG_DEBUG_SPINLOCK
#घोषणा DEBUG_SPINLOCK_BUG_ON(p) BUG_ON(p)
#अन्यथा
#घोषणा DEBUG_SPINLOCK_BUG_ON(p)
#पूर्ण_अगर

/* Requires the irq_lock to be held by the caller. */
अटल अंतरभूत bool irq_is_pending(काष्ठा vgic_irq *irq)
अणु
	अगर (irq->config == VGIC_CONFIG_EDGE)
		वापस irq->pending_latch;
	अन्यथा
		वापस irq->pending_latch || irq->line_level;
पूर्ण

अटल अंतरभूत bool vgic_irq_is_mapped_level(काष्ठा vgic_irq *irq)
अणु
	वापस irq->config == VGIC_CONFIG_LEVEL && irq->hw;
पूर्ण

अटल अंतरभूत पूर्णांक vgic_irq_get_lr_count(काष्ठा vgic_irq *irq)
अणु
	/* Account क्रम the active state as an पूर्णांकerrupt */
	अगर (vgic_irq_is_sgi(irq->पूर्णांकid) && irq->source)
		वापस hweight8(irq->source) + irq->active;

	वापस irq_is_pending(irq) || irq->active;
पूर्ण

अटल अंतरभूत bool vgic_irq_is_multi_sgi(काष्ठा vgic_irq *irq)
अणु
	वापस vgic_irq_get_lr_count(irq) > 1;
पूर्ण

/*
 * This काष्ठा provides an पूर्णांकermediate representation of the fields contained
 * in the GICH_VMCR and ICH_VMCR रेजिस्टरs, such that code exporting the GIC
 * state to userspace can generate either GICv2 or GICv3 CPU पूर्णांकerface
 * रेजिस्टरs regardless of the hardware backed GIC used.
 */
काष्ठा vgic_vmcr अणु
	u32	grpen0;
	u32	grpen1;

	u32	ackctl;
	u32	fiqen;
	u32	cbpr;
	u32	eoim;

	u32	abpr;
	u32	bpr;
	u32	pmr;  /* Priority mask field in the GICC_PMR and
		       * ICC_PMR_EL1 priority field क्रमmat */
पूर्ण;

काष्ठा vgic_reg_attr अणु
	काष्ठा kvm_vcpu *vcpu;
	gpa_t addr;
पूर्ण;

पूर्णांक vgic_v3_parse_attr(काष्ठा kvm_device *dev, काष्ठा kvm_device_attr *attr,
		       काष्ठा vgic_reg_attr *reg_attr);
पूर्णांक vgic_v2_parse_attr(काष्ठा kvm_device *dev, काष्ठा kvm_device_attr *attr,
		       काष्ठा vgic_reg_attr *reg_attr);
स्थिर काष्ठा vgic_रेजिस्टर_region *
vgic_get_mmio_region(काष्ठा kvm_vcpu *vcpu, काष्ठा vgic_io_device *iodev,
		     gpa_t addr, पूर्णांक len);
काष्ठा vgic_irq *vgic_get_irq(काष्ठा kvm *kvm, काष्ठा kvm_vcpu *vcpu,
			      u32 पूर्णांकid);
व्योम __vgic_put_lpi_locked(काष्ठा kvm *kvm, काष्ठा vgic_irq *irq);
व्योम vgic_put_irq(काष्ठा kvm *kvm, काष्ठा vgic_irq *irq);
bool vgic_get_phys_line_level(काष्ठा vgic_irq *irq);
व्योम vgic_irq_set_phys_pending(काष्ठा vgic_irq *irq, bool pending);
व्योम vgic_irq_set_phys_active(काष्ठा vgic_irq *irq, bool active);
bool vgic_queue_irq_unlock(काष्ठा kvm *kvm, काष्ठा vgic_irq *irq,
			   अचिन्हित दीर्घ flags);
व्योम vgic_kick_vcpus(काष्ठा kvm *kvm);

पूर्णांक vgic_check_ioaddr(काष्ठा kvm *kvm, phys_addr_t *ioaddr,
		      phys_addr_t addr, phys_addr_t alignment);

व्योम vgic_v2_fold_lr_state(काष्ठा kvm_vcpu *vcpu);
व्योम vgic_v2_populate_lr(काष्ठा kvm_vcpu *vcpu, काष्ठा vgic_irq *irq, पूर्णांक lr);
व्योम vgic_v2_clear_lr(काष्ठा kvm_vcpu *vcpu, पूर्णांक lr);
व्योम vgic_v2_set_underflow(काष्ठा kvm_vcpu *vcpu);
व्योम vgic_v2_set_npie(काष्ठा kvm_vcpu *vcpu);
पूर्णांक vgic_v2_has_attr_regs(काष्ठा kvm_device *dev, काष्ठा kvm_device_attr *attr);
पूर्णांक vgic_v2_dist_uaccess(काष्ठा kvm_vcpu *vcpu, bool is_ग_लिखो,
			 पूर्णांक offset, u32 *val);
पूर्णांक vgic_v2_cpuअगर_uaccess(काष्ठा kvm_vcpu *vcpu, bool is_ग_लिखो,
			  पूर्णांक offset, u32 *val);
व्योम vgic_v2_set_vmcr(काष्ठा kvm_vcpu *vcpu, काष्ठा vgic_vmcr *vmcr);
व्योम vgic_v2_get_vmcr(काष्ठा kvm_vcpu *vcpu, काष्ठा vgic_vmcr *vmcr);
व्योम vgic_v2_enable(काष्ठा kvm_vcpu *vcpu);
पूर्णांक vgic_v2_probe(स्थिर काष्ठा gic_kvm_info *info);
पूर्णांक vgic_v2_map_resources(काष्ठा kvm *kvm);
पूर्णांक vgic_रेजिस्टर_dist_iodev(काष्ठा kvm *kvm, gpa_t dist_base_address,
			     क्रमागत vgic_type);

व्योम vgic_v2_init_lrs(व्योम);
व्योम vgic_v2_load(काष्ठा kvm_vcpu *vcpu);
व्योम vgic_v2_put(काष्ठा kvm_vcpu *vcpu);
व्योम vgic_v2_vmcr_sync(काष्ठा kvm_vcpu *vcpu);

व्योम vgic_v2_save_state(काष्ठा kvm_vcpu *vcpu);
व्योम vgic_v2_restore_state(काष्ठा kvm_vcpu *vcpu);

अटल अंतरभूत व्योम vgic_get_irq_kref(काष्ठा vgic_irq *irq)
अणु
	अगर (irq->पूर्णांकid < VGIC_MIN_LPI)
		वापस;

	kref_get(&irq->refcount);
पूर्ण

व्योम vgic_v3_fold_lr_state(काष्ठा kvm_vcpu *vcpu);
व्योम vgic_v3_populate_lr(काष्ठा kvm_vcpu *vcpu, काष्ठा vgic_irq *irq, पूर्णांक lr);
व्योम vgic_v3_clear_lr(काष्ठा kvm_vcpu *vcpu, पूर्णांक lr);
व्योम vgic_v3_set_underflow(काष्ठा kvm_vcpu *vcpu);
व्योम vgic_v3_set_npie(काष्ठा kvm_vcpu *vcpu);
व्योम vgic_v3_set_vmcr(काष्ठा kvm_vcpu *vcpu, काष्ठा vgic_vmcr *vmcr);
व्योम vgic_v3_get_vmcr(काष्ठा kvm_vcpu *vcpu, काष्ठा vgic_vmcr *vmcr);
व्योम vgic_v3_enable(काष्ठा kvm_vcpu *vcpu);
पूर्णांक vgic_v3_probe(स्थिर काष्ठा gic_kvm_info *info);
पूर्णांक vgic_v3_map_resources(काष्ठा kvm *kvm);
पूर्णांक vgic_v3_lpi_sync_pending_status(काष्ठा kvm *kvm, काष्ठा vgic_irq *irq);
पूर्णांक vgic_v3_save_pending_tables(काष्ठा kvm *kvm);
पूर्णांक vgic_v3_set_redist_base(काष्ठा kvm *kvm, u32 index, u64 addr, u32 count);
पूर्णांक vgic_रेजिस्टर_redist_iodev(काष्ठा kvm_vcpu *vcpu);
bool vgic_v3_check_base(काष्ठा kvm *kvm);

व्योम vgic_v3_load(काष्ठा kvm_vcpu *vcpu);
व्योम vgic_v3_put(काष्ठा kvm_vcpu *vcpu);
व्योम vgic_v3_vmcr_sync(काष्ठा kvm_vcpu *vcpu);

bool vgic_has_its(काष्ठा kvm *kvm);
पूर्णांक kvm_vgic_रेजिस्टर_its_device(व्योम);
व्योम vgic_enable_lpis(काष्ठा kvm_vcpu *vcpu);
व्योम vgic_flush_pending_lpis(काष्ठा kvm_vcpu *vcpu);
पूर्णांक vgic_its_inject_msi(काष्ठा kvm *kvm, काष्ठा kvm_msi *msi);
पूर्णांक vgic_v3_has_attr_regs(काष्ठा kvm_device *dev, काष्ठा kvm_device_attr *attr);
पूर्णांक vgic_v3_dist_uaccess(काष्ठा kvm_vcpu *vcpu, bool is_ग_लिखो,
			 पूर्णांक offset, u32 *val);
पूर्णांक vgic_v3_redist_uaccess(काष्ठा kvm_vcpu *vcpu, bool is_ग_लिखो,
			 पूर्णांक offset, u32 *val);
पूर्णांक vgic_v3_cpu_sysregs_uaccess(काष्ठा kvm_vcpu *vcpu, bool is_ग_लिखो,
			 u64 id, u64 *val);
पूर्णांक vgic_v3_has_cpu_sysregs_attr(काष्ठा kvm_vcpu *vcpu, bool is_ग_लिखो, u64 id,
				u64 *reg);
पूर्णांक vgic_v3_line_level_info_uaccess(काष्ठा kvm_vcpu *vcpu, bool is_ग_लिखो,
				    u32 पूर्णांकid, u64 *val);
पूर्णांक kvm_रेजिस्टर_vgic_device(अचिन्हित दीर्घ type);
व्योम vgic_set_vmcr(काष्ठा kvm_vcpu *vcpu, काष्ठा vgic_vmcr *vmcr);
व्योम vgic_get_vmcr(काष्ठा kvm_vcpu *vcpu, काष्ठा vgic_vmcr *vmcr);
पूर्णांक vgic_lazy_init(काष्ठा kvm *kvm);
पूर्णांक vgic_init(काष्ठा kvm *kvm);

व्योम vgic_debug_init(काष्ठा kvm *kvm);
व्योम vgic_debug_destroy(काष्ठा kvm *kvm);

bool lock_all_vcpus(काष्ठा kvm *kvm);
व्योम unlock_all_vcpus(काष्ठा kvm *kvm);

अटल अंतरभूत पूर्णांक vgic_v3_max_apr_idx(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vgic_cpu *cpu_अगर = &vcpu->arch.vgic_cpu;

	/*
	 * num_pri_bits are initialized with HW supported values.
	 * We can rely safely on num_pri_bits even अगर VM has not
	 * restored ICC_CTLR_EL1 beक्रमe restoring APnR रेजिस्टरs.
	 */
	चयन (cpu_अगर->num_pri_bits) अणु
	हाल 7: वापस 3;
	हाल 6: वापस 1;
	शेष: वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत bool
vgic_v3_redist_region_full(काष्ठा vgic_redist_region *region)
अणु
	अगर (!region->count)
		वापस false;

	वापस (region->मुक्त_index >= region->count);
पूर्ण

काष्ठा vgic_redist_region *vgic_v3_rdist_मुक्त_slot(काष्ठा list_head *rdregs);

अटल अंतरभूत माप_प्रकार
vgic_v3_rd_region_size(काष्ठा kvm *kvm, काष्ठा vgic_redist_region *rdreg)
अणु
	अगर (!rdreg->count)
		वापस atomic_पढ़ो(&kvm->online_vcpus) * KVM_VGIC_V3_REDIST_SIZE;
	अन्यथा
		वापस rdreg->count * KVM_VGIC_V3_REDIST_SIZE;
पूर्ण

काष्ठा vgic_redist_region *vgic_v3_rdist_region_from_index(काष्ठा kvm *kvm,
							   u32 index);
व्योम vgic_v3_मुक्त_redist_region(काष्ठा vgic_redist_region *rdreg);

bool vgic_v3_rdist_overlap(काष्ठा kvm *kvm, gpa_t base, माप_प्रकार size);

अटल अंतरभूत bool vgic_dist_overlap(काष्ठा kvm *kvm, gpa_t base, माप_प्रकार size)
अणु
	काष्ठा vgic_dist *d = &kvm->arch.vgic;

	वापस (base + size > d->vgic_dist_base) &&
		(base < d->vgic_dist_base + KVM_VGIC_V3_DIST_SIZE);
पूर्ण

पूर्णांक vgic_copy_lpi_list(काष्ठा kvm *kvm, काष्ठा kvm_vcpu *vcpu, u32 **पूर्णांकid_ptr);
पूर्णांक vgic_its_resolve_lpi(काष्ठा kvm *kvm, काष्ठा vgic_its *its,
			 u32 devid, u32 eventid, काष्ठा vgic_irq **irq);
काष्ठा vgic_its *vgic_msi_to_its(काष्ठा kvm *kvm, काष्ठा kvm_msi *msi);
पूर्णांक vgic_its_inject_cached_translation(काष्ठा kvm *kvm, काष्ठा kvm_msi *msi);
व्योम vgic_lpi_translation_cache_init(काष्ठा kvm *kvm);
व्योम vgic_lpi_translation_cache_destroy(काष्ठा kvm *kvm);
व्योम vgic_its_invalidate_cache(काष्ठा kvm *kvm);

bool vgic_supports_direct_msis(काष्ठा kvm *kvm);
पूर्णांक vgic_v4_init(काष्ठा kvm *kvm);
व्योम vgic_v4_tearकरोwn(काष्ठा kvm *kvm);
व्योम vgic_v4_configure_vsgis(काष्ठा kvm *kvm);
व्योम vgic_v4_get_vlpi_state(काष्ठा vgic_irq *irq, bool *val);

#पूर्ण_अगर
