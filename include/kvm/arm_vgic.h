<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2015, 2016 ARM Ltd.
 */
#अगर_अघोषित __KVM_ARM_VGIC_H
#घोषणा __KVM_ARM_VGIC_H

#समावेश <linux/kernel.h>
#समावेश <linux/kvm.h>
#समावेश <linux/irqवापस.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/अटल_key.h>
#समावेश <linux/types.h>
#समावेश <kvm/iodev.h>
#समावेश <linux/list.h>
#समावेश <linux/jump_label.h>

#समावेश <linux/irqchip/arm-gic-v4.h>

#घोषणा VGIC_V3_MAX_CPUS	512
#घोषणा VGIC_V2_MAX_CPUS	8
#घोषणा VGIC_NR_IRQS_LEGACY     256
#घोषणा VGIC_NR_SGIS		16
#घोषणा VGIC_NR_PPIS		16
#घोषणा VGIC_NR_PRIVATE_IRQS	(VGIC_NR_SGIS + VGIC_NR_PPIS)
#घोषणा VGIC_MAX_PRIVATE	(VGIC_NR_PRIVATE_IRQS - 1)
#घोषणा VGIC_MAX_SPI		1019
#घोषणा VGIC_MAX_RESERVED	1023
#घोषणा VGIC_MIN_LPI		8192
#घोषणा KVM_IRQCHIP_NUM_PINS	(1020 - 32)

#घोषणा irq_is_ppi(irq) ((irq) >= VGIC_NR_SGIS && (irq) < VGIC_NR_PRIVATE_IRQS)
#घोषणा irq_is_spi(irq) ((irq) >= VGIC_NR_PRIVATE_IRQS && \
			 (irq) <= VGIC_MAX_SPI)

क्रमागत vgic_type अणु
	VGIC_V2,		/* Good ol' GICv2 */
	VGIC_V3,		/* New fancy GICv3 */
पूर्ण;

/* same क्रम all guests, as depending only on the _host's_ GIC model */
काष्ठा vgic_global अणु
	/* type of the host GIC */
	क्रमागत vgic_type		type;

	/* Physical address of vgic भव cpu पूर्णांकerface */
	phys_addr_t		vcpu_base;

	/* GICV mapping, kernel VA */
	व्योम __iomem		*vcpu_base_va;
	/* GICV mapping, HYP VA */
	व्योम __iomem		*vcpu_hyp_va;

	/* भव control पूर्णांकerface mapping, kernel VA */
	व्योम __iomem		*vctrl_base;
	/* भव control पूर्णांकerface mapping, HYP VA */
	व्योम __iomem		*vctrl_hyp;

	/* Number of implemented list रेजिस्टरs */
	पूर्णांक			nr_lr;

	/* Maपूर्णांकenance IRQ number */
	अचिन्हित पूर्णांक		मुख्यt_irq;

	/* maximum number of VCPUs allowed (GICv2 limits us to 8) */
	पूर्णांक			max_gic_vcpus;

	/* Only needed क्रम the legacy KVM_CREATE_IRQCHIP */
	bool			can_emulate_gicv2;

	/* Hardware has GICv4? */
	bool			has_gicv4;
	bool			has_gicv4_1;

	/* GIC प्रणाली रेजिस्टर CPU पूर्णांकerface */
	काष्ठा अटल_key_false gicv3_cpuअगर;

	u32			ich_vtr_el2;
पूर्ण;

बाह्य काष्ठा vgic_global kvm_vgic_global_state;

#घोषणा VGIC_V2_MAX_LRS		(1 << 6)
#घोषणा VGIC_V3_MAX_LRS		16
#घोषणा VGIC_V3_LR_INDEX(lr)	(VGIC_V3_MAX_LRS - 1 - lr)

क्रमागत vgic_irq_config अणु
	VGIC_CONFIG_EDGE = 0,
	VGIC_CONFIG_LEVEL
पूर्ण;

काष्ठा vgic_irq अणु
	raw_spinlock_t irq_lock;	/* Protects the content of the काष्ठा */
	काष्ठा list_head lpi_list;	/* Used to link all LPIs together */
	काष्ठा list_head ap_list;

	काष्ठा kvm_vcpu *vcpu;		/* SGIs and PPIs: The VCPU
					 * SPIs and LPIs: The VCPU whose ap_list
					 * this is queued on.
					 */

	काष्ठा kvm_vcpu *target_vcpu;	/* The VCPU that this पूर्णांकerrupt should
					 * be sent to, as a result of the
					 * tarमाला_लो reg (v2) or the
					 * affinity reg (v3).
					 */

	u32 पूर्णांकid;			/* Guest visible INTID */
	bool line_level;		/* Level only */
	bool pending_latch;		/* The pending latch state used to calculate
					 * the pending state क्रम both level
					 * and edge triggered IRQs. */
	bool active;			/* not used क्रम LPIs */
	bool enabled;
	bool hw;			/* Tied to HW IRQ */
	काष्ठा kref refcount;		/* Used क्रम LPIs */
	u32 hwपूर्णांकid;			/* HW INTID number */
	अचिन्हित पूर्णांक host_irq;		/* linux irq corresponding to hwपूर्णांकid */
	जोड़ अणु
		u8 tarमाला_लो;			/* GICv2 target VCPUs mask */
		u32 mpidr;			/* GICv3 target VCPU */
	पूर्ण;
	u8 source;			/* GICv2 SGIs only */
	u8 active_source;		/* GICv2 SGIs only */
	u8 priority;
	u8 group;			/* 0 == group 0, 1 == group 1 */
	क्रमागत vgic_irq_config config;	/* Level or edge */

	/*
	 * Callback function poपूर्णांकer to in-kernel devices that can tell us the
	 * state of the input level of mapped level-triggered IRQ faster than
	 * peaking पूर्णांकo the physical GIC.
	 *
	 * Always called in non-preemptible section and the functions can use
	 * kvm_arm_get_running_vcpu() to get the vcpu poपूर्णांकer क्रम निजी
	 * IRQs.
	 */
	bool (*get_input_level)(पूर्णांक vपूर्णांकid);

	व्योम *owner;			/* Opaque poपूर्णांकer to reserve an पूर्णांकerrupt
					   क्रम in-kernel devices. */
पूर्ण;

काष्ठा vgic_रेजिस्टर_region;
काष्ठा vgic_its;

क्रमागत iodev_type अणु
	IODEV_CPUIF,
	IODEV_DIST,
	IODEV_REDIST,
	IODEV_ITS
पूर्ण;

काष्ठा vgic_io_device अणु
	gpa_t base_addr;
	जोड़ अणु
		काष्ठा kvm_vcpu *redist_vcpu;
		काष्ठा vgic_its *its;
	पूर्ण;
	स्थिर काष्ठा vgic_रेजिस्टर_region *regions;
	क्रमागत iodev_type iodev_type;
	पूर्णांक nr_regions;
	काष्ठा kvm_io_device dev;
पूर्ण;

काष्ठा vgic_its अणु
	/* The base address of the ITS control रेजिस्टर frame */
	gpa_t			vgic_its_base;

	bool			enabled;
	काष्ठा vgic_io_device	iodev;
	काष्ठा kvm_device	*dev;

	/* These रेजिस्टरs correspond to GITS_BASERअणु0,1पूर्ण */
	u64			baser_device_table;
	u64			baser_coll_table;

	/* Protects the command queue */
	काष्ठा mutex		cmd_lock;
	u64			cbaser;
	u32			cपढ़ोr;
	u32			cग_लिखोr;

	/* migration ABI revision in use */
	u32			abi_rev;

	/* Protects the device and collection lists */
	काष्ठा mutex		its_lock;
	काष्ठा list_head	device_list;
	काष्ठा list_head	collection_list;
पूर्ण;

काष्ठा vgic_state_iter;

काष्ठा vgic_redist_region अणु
	u32 index;
	gpa_t base;
	u32 count; /* number of redistributors or 0 अगर single region */
	u32 मुक्त_index; /* index of the next मुक्त redistributor */
	काष्ठा list_head list;
पूर्ण;

काष्ठा vgic_dist अणु
	bool			in_kernel;
	bool			पढ़ोy;
	bool			initialized;

	/* vGIC model the kernel emulates क्रम the guest (GICv2 or GICv3) */
	u32			vgic_model;

	/* Implementation revision as reported in the GICD_IIDR */
	u32			implementation_rev;

	/* Userspace can ग_लिखो to GICv2 IGROUPR */
	bool			v2_groups_user_writable;

	/* Do injected MSIs require an additional device ID? */
	bool			msis_require_devid;

	पूर्णांक			nr_spis;

	/* base addresses in guest physical address space: */
	gpa_t			vgic_dist_base;		/* distributor */
	जोड़ अणु
		/* either a GICv2 CPU पूर्णांकerface */
		gpa_t			vgic_cpu_base;
		/* or a number of GICv3 redistributor regions */
		काष्ठा list_head rd_regions;
	पूर्ण;

	/* distributor enabled */
	bool			enabled;

	/* Wants SGIs without active state */
	bool			nassgireq;

	काष्ठा vgic_irq		*spis;

	काष्ठा vgic_io_device	dist_iodev;

	bool			has_its;

	/*
	 * Contains the attributes and gpa of the LPI configuration table.
	 * Since we report GICR_TYPER.CommonLPIAff as 0b00, we can share
	 * one address across all redistributors.
	 * GICv3 spec: IHI 0069E 6.1.1 "LPI Configuration tables"
	 */
	u64			propbaser;

	/* Protects the lpi_list and the count value below. */
	raw_spinlock_t		lpi_list_lock;
	काष्ठा list_head	lpi_list_head;
	पूर्णांक			lpi_list_count;

	/* LPI translation cache */
	काष्ठा list_head	lpi_translation_cache;

	/* used by vgic-debug */
	काष्ठा vgic_state_iter *iter;

	/*
	 * GICv4 ITS per-VM data, containing the IRQ करोमुख्य, the VPE
	 * array, the property table poपूर्णांकer as well as allocation
	 * data. This essentially ties the Linux IRQ core and ITS
	 * together, and aव्योमs leaking KVM's data काष्ठाures anywhere
	 * अन्यथा.
	 */
	काष्ठा its_vm		its_vm;
पूर्ण;

काष्ठा vgic_v2_cpu_अगर अणु
	u32		vgic_hcr;
	u32		vgic_vmcr;
	u32		vgic_apr;
	u32		vgic_lr[VGIC_V2_MAX_LRS];

	अचिन्हित पूर्णांक used_lrs;
पूर्ण;

काष्ठा vgic_v3_cpu_अगर अणु
	u32		vgic_hcr;
	u32		vgic_vmcr;
	u32		vgic_sre;	/* Restored only, change ignored */
	u32		vgic_ap0r[4];
	u32		vgic_ap1r[4];
	u64		vgic_lr[VGIC_V3_MAX_LRS];

	/*
	 * GICv4 ITS per-VPE data, containing the करोorbell IRQ, the
	 * pending table poपूर्णांकer, the its_vm poपूर्णांकer and a few other
	 * HW specअगरic things. As क्रम the its_vm काष्ठाure, this is
	 * linking the Linux IRQ subप्रणाली and the ITS together.
	 */
	काष्ठा its_vpe	its_vpe;

	अचिन्हित पूर्णांक used_lrs;
पूर्ण;

काष्ठा vgic_cpu अणु
	/* CPU vअगर control रेजिस्टरs क्रम world चयन */
	जोड़ अणु
		काष्ठा vgic_v2_cpu_अगर	vgic_v2;
		काष्ठा vgic_v3_cpu_अगर	vgic_v3;
	पूर्ण;

	काष्ठा vgic_irq निजी_irqs[VGIC_NR_PRIVATE_IRQS];

	raw_spinlock_t ap_list_lock;	/* Protects the ap_list */

	/*
	 * List of IRQs that this VCPU should consider because they are either
	 * Active or Pending (hence the name; AP list), or because they recently
	 * were one of the two and need to be migrated off this list to another
	 * VCPU.
	 */
	काष्ठा list_head ap_list_head;

	/*
	 * Members below are used with GICv3 emulation only and represent
	 * parts of the redistributor.
	 */
	काष्ठा vgic_io_device	rd_iodev;
	काष्ठा vgic_redist_region *rdreg;
	u32 rdreg_index;

	/* Contains the attributes and gpa of the LPI pending tables. */
	u64 pendbaser;

	bool lpis_enabled;

	/* Cache guest priority bits */
	u32 num_pri_bits;

	/* Cache guest पूर्णांकerrupt ID bits */
	u32 num_id_bits;
पूर्ण;

बाह्य काष्ठा अटल_key_false vgic_v2_cpuअगर_trap;
बाह्य काष्ठा अटल_key_false vgic_v3_cpuअगर_trap;

पूर्णांक kvm_vgic_addr(काष्ठा kvm *kvm, अचिन्हित दीर्घ type, u64 *addr, bool ग_लिखो);
व्योम kvm_vgic_early_init(काष्ठा kvm *kvm);
पूर्णांक kvm_vgic_vcpu_init(काष्ठा kvm_vcpu *vcpu);
पूर्णांक kvm_vgic_create(काष्ठा kvm *kvm, u32 type);
व्योम kvm_vgic_destroy(काष्ठा kvm *kvm);
व्योम kvm_vgic_vcpu_destroy(काष्ठा kvm_vcpu *vcpu);
पूर्णांक kvm_vgic_map_resources(काष्ठा kvm *kvm);
पूर्णांक kvm_vgic_hyp_init(व्योम);
व्योम kvm_vgic_init_cpu_hardware(व्योम);

पूर्णांक kvm_vgic_inject_irq(काष्ठा kvm *kvm, पूर्णांक cpuid, अचिन्हित पूर्णांक पूर्णांकid,
			bool level, व्योम *owner);
पूर्णांक kvm_vgic_map_phys_irq(काष्ठा kvm_vcpu *vcpu, अचिन्हित पूर्णांक host_irq,
			  u32 vपूर्णांकid, bool (*get_input_level)(पूर्णांक vindid));
पूर्णांक kvm_vgic_unmap_phys_irq(काष्ठा kvm_vcpu *vcpu, अचिन्हित पूर्णांक vपूर्णांकid);
bool kvm_vgic_map_is_active(काष्ठा kvm_vcpu *vcpu, अचिन्हित पूर्णांक vपूर्णांकid);

पूर्णांक kvm_vgic_vcpu_pending_irq(काष्ठा kvm_vcpu *vcpu);

व्योम kvm_vgic_load(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_vgic_put(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_vgic_vmcr_sync(काष्ठा kvm_vcpu *vcpu);

#घोषणा irqchip_in_kernel(k)	(!!((k)->arch.vgic.in_kernel))
#घोषणा vgic_initialized(k)	((k)->arch.vgic.initialized)
#घोषणा vgic_पढ़ोy(k)		((k)->arch.vgic.पढ़ोy)
#घोषणा vgic_valid_spi(k, i)	(((i) >= VGIC_NR_PRIVATE_IRQS) && \
			((i) < (k)->arch.vgic.nr_spis + VGIC_NR_PRIVATE_IRQS))

bool kvm_vcpu_has_pending_irqs(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_vgic_sync_hwstate(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_vgic_flush_hwstate(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_vgic_reset_mapped_irq(काष्ठा kvm_vcpu *vcpu, u32 vपूर्णांकid);

व्योम vgic_v3_dispatch_sgi(काष्ठा kvm_vcpu *vcpu, u64 reg, bool allow_group1);

/**
 * kvm_vgic_get_max_vcpus - Get the maximum number of VCPUs allowed by HW
 *
 * The host's GIC naturally limits the maximum amount of VCPUs a guest
 * can use.
 */
अटल अंतरभूत पूर्णांक kvm_vgic_get_max_vcpus(व्योम)
अणु
	वापस kvm_vgic_global_state.max_gic_vcpus;
पूर्ण

/**
 * kvm_vgic_setup_शेष_irq_routing:
 * Setup a शेष flat gsi routing table mapping all SPIs
 */
पूर्णांक kvm_vgic_setup_शेष_irq_routing(काष्ठा kvm *kvm);

पूर्णांक kvm_vgic_set_owner(काष्ठा kvm_vcpu *vcpu, अचिन्हित पूर्णांक पूर्णांकid, व्योम *owner);

काष्ठा kvm_kernel_irq_routing_entry;

पूर्णांक kvm_vgic_v4_set_क्रमwarding(काष्ठा kvm *kvm, पूर्णांक irq,
			       काष्ठा kvm_kernel_irq_routing_entry *irq_entry);

पूर्णांक kvm_vgic_v4_unset_क्रमwarding(काष्ठा kvm *kvm, पूर्णांक irq,
				 काष्ठा kvm_kernel_irq_routing_entry *irq_entry);

पूर्णांक vgic_v4_load(काष्ठा kvm_vcpu *vcpu);
व्योम vgic_v4_commit(काष्ठा kvm_vcpu *vcpu);
पूर्णांक vgic_v4_put(काष्ठा kvm_vcpu *vcpu, bool need_db);

#पूर्ण_अगर /* __KVM_ARM_VGIC_H */
