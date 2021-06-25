<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2016,2017 ARM Limited, All Rights Reserved.
 * Author: Marc Zyngier <marc.zyngier@arm.com>
 */

#अगर_अघोषित __LINUX_IRQCHIP_ARM_GIC_V4_H
#घोषणा __LINUX_IRQCHIP_ARM_GIC_V4_H

काष्ठा its_vpe;

/*
 * Maximum number of ITTs when GITS_TYPER.VMOVP == 0, using the
 * ITSList mechanism to perक्रमm पूर्णांकer-ITS synchronization.
 */
#घोषणा GICv4_ITS_LIST_MAX		16

/* Embedded in kvm.arch */
काष्ठा its_vm अणु
	काष्ठा fwnode_handle	*fwnode;
	काष्ठा irq_करोमुख्य	*करोमुख्य;
	काष्ठा page		*vprop_page;
	काष्ठा its_vpe		**vpes;
	पूर्णांक			nr_vpes;
	irq_hw_number_t		db_lpi_base;
	अचिन्हित दीर्घ		*db_biपंचांगap;
	पूर्णांक			nr_db_lpis;
	u32			vlpi_count[GICv4_ITS_LIST_MAX];
पूर्ण;

/* Embedded in kvm_vcpu.arch */
काष्ठा its_vpe अणु
	काष्ठा page 		*vpt_page;
	काष्ठा its_vm		*its_vm;
	/* per-vPE VLPI tracking */
	atomic_t		vlpi_count;
	/* Doorbell पूर्णांकerrupt */
	पूर्णांक			irq;
	irq_hw_number_t		vpe_db_lpi;
	/* VPE resident */
	bool			resident;
	/* VPT parse complete */
	bool			पढ़ोy;
	जोड़ अणु
		/* GICv4.0 implementations */
		काष्ठा अणु
			/* VPE proxy mapping */
			पूर्णांक	vpe_proxy_event;
			/* Implementation Defined Area Invalid */
			bool	idai;
		पूर्ण;
		/* GICv4.1 implementations */
		काष्ठा अणु
			काष्ठा fwnode_handle	*fwnode;
			काष्ठा irq_करोमुख्य	*sgi_करोमुख्य;
			काष्ठा अणु
				u8	priority;
				bool	enabled;
				bool	group;
			पूर्ण			sgi_config[16];
			atomic_t vmapp_count;
		पूर्ण;
	पूर्ण;

	/*
	 * Ensures mutual exclusion between affinity setting of the
	 * vPE and vLPI operations using vpe->col_idx.
	 */
	raw_spinlock_t		vpe_lock;
	/*
	 * This collection ID is used to indirect the target
	 * redistributor क्रम this VPE. The ID itself isn't involved in
	 * programming of the ITS.
	 */
	u16			col_idx;
	/* Unique (प्रणाली-wide) VPE identअगरier */
	u16			vpe_id;
	/* Pending VLPIs on schedule out? */
	bool			pending_last;
पूर्ण;

/*
 * काष्ठा its_vlpi_map: काष्ठाure describing the mapping of a
 * VLPI. Only to be पूर्णांकerpreted in the context of a physical पूर्णांकerrupt
 * it complements.  To be used as the vcpu_info passed to
 * irq_set_vcpu_affinity().
 *
 * @vm:		Poपूर्णांकer to the GICv4 notion of a VM
 * @vpe:	Poपूर्णांकer to the GICv4 notion of a भव CPU (VPE)
 * @vपूर्णांकid:	Virtual LPI number
 * @properties:	Priority and enable bits (as written in the prop table)
 * @db_enabled:	Is the VPE करोorbell to be generated?
 */
काष्ठा its_vlpi_map अणु
	काष्ठा its_vm		*vm;
	काष्ठा its_vpe		*vpe;
	u32			vपूर्णांकid;
	u8			properties;
	bool			db_enabled;
पूर्ण;

क्रमागत its_vcpu_info_cmd_type अणु
	MAP_VLPI,
	GET_VLPI,
	PROP_UPDATE_VLPI,
	PROP_UPDATE_AND_INV_VLPI,
	SCHEDULE_VPE,
	DESCHEDULE_VPE,
	COMMIT_VPE,
	INVALL_VPE,
	PROP_UPDATE_VSGI,
पूर्ण;

काष्ठा its_cmd_info अणु
	क्रमागत its_vcpu_info_cmd_type	cmd_type;
	जोड़ अणु
		काष्ठा its_vlpi_map	*map;
		u8			config;
		bool			req_db;
		काष्ठा अणु
			bool		g0en;
			bool		g1en;
		पूर्ण;
		काष्ठा अणु
			u8		priority;
			bool		group;
		पूर्ण;
	पूर्ण;
पूर्ण;

पूर्णांक its_alloc_vcpu_irqs(काष्ठा its_vm *vm);
व्योम its_मुक्त_vcpu_irqs(काष्ठा its_vm *vm);
पूर्णांक its_make_vpe_resident(काष्ठा its_vpe *vpe, bool g0en, bool g1en);
पूर्णांक its_make_vpe_non_resident(काष्ठा its_vpe *vpe, bool db);
पूर्णांक its_commit_vpe(काष्ठा its_vpe *vpe);
पूर्णांक its_invall_vpe(काष्ठा its_vpe *vpe);
पूर्णांक its_map_vlpi(पूर्णांक irq, काष्ठा its_vlpi_map *map);
पूर्णांक its_get_vlpi(पूर्णांक irq, काष्ठा its_vlpi_map *map);
पूर्णांक its_unmap_vlpi(पूर्णांक irq);
पूर्णांक its_prop_update_vlpi(पूर्णांक irq, u8 config, bool inv);
पूर्णांक its_prop_update_vsgi(पूर्णांक irq, u8 priority, bool group);

काष्ठा irq_करोमुख्य_ops;
पूर्णांक its_init_v4(काष्ठा irq_करोमुख्य *करोमुख्य,
		स्थिर काष्ठा irq_करोमुख्य_ops *vpe_ops,
		स्थिर काष्ठा irq_करोमुख्य_ops *sgi_ops);

bool gic_cpuअगर_has_vsgi(व्योम);

#पूर्ण_अगर
