<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2006, Intel Corporation.
 *
 * Copyright (C) Ashok Raj <ashok.raj@पूर्णांकel.com>
 * Copyright (C) Shaohua Li <shaohua.li@पूर्णांकel.com>
 */

#अगर_अघोषित __DMAR_H__
#घोषणा __DMAR_H__

#समावेश <linux/acpi.h>
#समावेश <linux/types.h>
#समावेश <linux/msi.h>
#समावेश <linux/irqवापस.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/rculist.h>

काष्ठा acpi_dmar_header;

#अगर_घोषित	CONFIG_X86
# define	DMAR_UNITS_SUPPORTED	MAX_IO_APICS
#अन्यथा
# define	DMAR_UNITS_SUPPORTED	64
#पूर्ण_अगर

/* DMAR Flags */
#घोषणा DMAR_INTR_REMAP		0x1
#घोषणा DMAR_X2APIC_OPT_OUT	0x2
#घोषणा DMAR_PLATFORM_OPT_IN	0x4

काष्ठा पूर्णांकel_iommu;

काष्ठा dmar_dev_scope अणु
	काष्ठा device __rcu *dev;
	u8 bus;
	u8 devfn;
पूर्ण;

#अगर_घोषित CONFIG_DMAR_TABLE
बाह्य काष्ठा acpi_table_header *dmar_tbl;
काष्ठा dmar_drhd_unit अणु
	काष्ठा list_head list;		/* list of drhd units	*/
	काष्ठा  acpi_dmar_header *hdr;	/* ACPI header		*/
	u64	reg_base_addr;		/* रेजिस्टर base address*/
	काष्ठा	dmar_dev_scope *devices;/* target device array	*/
	पूर्णांक	devices_cnt;		/* target device count	*/
	u16	segment;		/* PCI करोमुख्य		*/
	u8	ignored:1; 		/* ignore drhd		*/
	u8	include_all:1;
	u8	gfx_dedicated:1;	/* graphic dedicated	*/
	काष्ठा पूर्णांकel_iommu *iommu;
पूर्ण;

काष्ठा dmar_pci_path अणु
	u8 bus;
	u8 device;
	u8 function;
पूर्ण;

काष्ठा dmar_pci_notअगरy_info अणु
	काष्ठा pci_dev			*dev;
	अचिन्हित दीर्घ			event;
	पूर्णांक				bus;
	u16				seg;
	u16				level;
	काष्ठा dmar_pci_path		path[];
पूर्ण  __attribute__((packed));

बाह्य काष्ठा rw_semaphore dmar_global_lock;
बाह्य काष्ठा list_head dmar_drhd_units;

#घोषणा क्रम_each_drhd_unit(drhd)					\
	list_क्रम_each_entry_rcu(drhd, &dmar_drhd_units, list,		\
				dmar_rcu_check())

#घोषणा क्रम_each_active_drhd_unit(drhd)					\
	list_क्रम_each_entry_rcu(drhd, &dmar_drhd_units, list,		\
				dmar_rcu_check())			\
		अगर (drhd->ignored) अणुपूर्ण अन्यथा

#घोषणा क्रम_each_active_iommu(i, drhd)					\
	list_क्रम_each_entry_rcu(drhd, &dmar_drhd_units, list,		\
				dmar_rcu_check())			\
		अगर (i=drhd->iommu, drhd->ignored) अणुपूर्ण अन्यथा

#घोषणा क्रम_each_iommu(i, drhd)						\
	list_क्रम_each_entry_rcu(drhd, &dmar_drhd_units, list,		\
				dmar_rcu_check())			\
		अगर (i=drhd->iommu, 0) अणुपूर्ण अन्यथा 

अटल अंतरभूत bool dmar_rcu_check(व्योम)
अणु
	वापस rwsem_is_locked(&dmar_global_lock) ||
	       प्रणाली_state == SYSTEM_BOOTING;
पूर्ण

#घोषणा	dmar_rcu_dereference(p)	rcu_dereference_check((p), dmar_rcu_check())

#घोषणा क्रम_each_dev_scope(devs, cnt, i, पंचांगp)				\
	क्रम ((i) = 0; ((पंचांगp) = (i) < (cnt) ?				\
	    dmar_rcu_dereference((devs)[(i)].dev) : शून्य, (i) < (cnt)); \
	    (i)++)

#घोषणा क्रम_each_active_dev_scope(devs, cnt, i, पंचांगp)			\
	क्रम_each_dev_scope((devs), (cnt), (i), (पंचांगp))			\
		अगर (!(पंचांगp)) अणु जारी; पूर्ण अन्यथा

बाह्य पूर्णांक dmar_table_init(व्योम);
बाह्य पूर्णांक dmar_dev_scope_init(व्योम);
बाह्य व्योम dmar_रेजिस्टर_bus_notअगरier(व्योम);
बाह्य पूर्णांक dmar_parse_dev_scope(व्योम *start, व्योम *end, पूर्णांक *cnt,
				काष्ठा dmar_dev_scope **devices, u16 segment);
बाह्य व्योम *dmar_alloc_dev_scope(व्योम *start, व्योम *end, पूर्णांक *cnt);
बाह्य व्योम dmar_मुक्त_dev_scope(काष्ठा dmar_dev_scope **devices, पूर्णांक *cnt);
बाह्य पूर्णांक dmar_insert_dev_scope(काष्ठा dmar_pci_notअगरy_info *info,
				 व्योम *start, व्योम*end, u16 segment,
				 काष्ठा dmar_dev_scope *devices,
				 पूर्णांक devices_cnt);
बाह्य पूर्णांक dmar_हटाओ_dev_scope(काष्ठा dmar_pci_notअगरy_info *info,
				 u16 segment, काष्ठा dmar_dev_scope *devices,
				 पूर्णांक count);
/* Intel IOMMU detection */
बाह्य पूर्णांक detect_पूर्णांकel_iommu(व्योम);
बाह्य पूर्णांक enable_drhd_fault_handling(व्योम);
बाह्य पूर्णांक dmar_device_add(acpi_handle handle);
बाह्य पूर्णांक dmar_device_हटाओ(acpi_handle handle);

अटल अंतरभूत पूर्णांक dmar_res_noop(काष्ठा acpi_dmar_header *hdr, व्योम *arg)
अणु
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_INTEL_IOMMU
बाह्य पूर्णांक iommu_detected, no_iommu;
बाह्य पूर्णांक पूर्णांकel_iommu_init(व्योम);
बाह्य व्योम पूर्णांकel_iommu_shutकरोwn(व्योम);
बाह्य पूर्णांक dmar_parse_one_rmrr(काष्ठा acpi_dmar_header *header, व्योम *arg);
बाह्य पूर्णांक dmar_parse_one_atsr(काष्ठा acpi_dmar_header *header, व्योम *arg);
बाह्य पूर्णांक dmar_check_one_atsr(काष्ठा acpi_dmar_header *hdr, व्योम *arg);
बाह्य पूर्णांक dmar_parse_one_satc(काष्ठा acpi_dmar_header *hdr, व्योम *arg);
बाह्य पूर्णांक dmar_release_one_atsr(काष्ठा acpi_dmar_header *hdr, व्योम *arg);
बाह्य पूर्णांक dmar_iommu_hotplug(काष्ठा dmar_drhd_unit *dmaru, bool insert);
बाह्य पूर्णांक dmar_iommu_notअगरy_scope_dev(काष्ठा dmar_pci_notअगरy_info *info);
#अन्यथा /* !CONFIG_INTEL_IOMMU: */
अटल अंतरभूत पूर्णांक पूर्णांकel_iommu_init(व्योम) अणु वापस -ENODEV; पूर्ण
अटल अंतरभूत व्योम पूर्णांकel_iommu_shutकरोwn(व्योम) अणु पूर्ण

#घोषणा	dmar_parse_one_rmrr		dmar_res_noop
#घोषणा	dmar_parse_one_atsr		dmar_res_noop
#घोषणा	dmar_check_one_atsr		dmar_res_noop
#घोषणा	dmar_release_one_atsr		dmar_res_noop
#घोषणा	dmar_parse_one_satc		dmar_res_noop

अटल अंतरभूत पूर्णांक dmar_iommu_notअगरy_scope_dev(काष्ठा dmar_pci_notअगरy_info *info)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक dmar_iommu_hotplug(काष्ठा dmar_drhd_unit *dmaru, bool insert)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_INTEL_IOMMU */

#अगर_घोषित CONFIG_IRQ_REMAP
बाह्य पूर्णांक dmar_ir_hotplug(काष्ठा dmar_drhd_unit *dmaru, bool insert);
#अन्यथा  /* CONFIG_IRQ_REMAP */
अटल अंतरभूत पूर्णांक dmar_ir_hotplug(काष्ठा dmar_drhd_unit *dmaru, bool insert)
अणु वापस 0; पूर्ण
#पूर्ण_अगर /* CONFIG_IRQ_REMAP */

बाह्य bool dmar_platक्रमm_optin(व्योम);

#अन्यथा /* CONFIG_DMAR_TABLE */

अटल अंतरभूत पूर्णांक dmar_device_add(व्योम *handle)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक dmar_device_हटाओ(व्योम *handle)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत bool dmar_platक्रमm_optin(व्योम)
अणु
	वापस false;
पूर्ण

#पूर्ण_अगर /* CONFIG_DMAR_TABLE */

काष्ठा irte अणु
	जोड़ अणु
		/* Shared between remapped and posted mode*/
		काष्ठा अणु
			__u64	present		: 1,  /*  0      */
				fpd		: 1,  /*  1      */
				__res0		: 6,  /*  2 -  6 */
				avail		: 4,  /*  8 - 11 */
				__res1		: 3,  /* 12 - 14 */
				pst		: 1,  /* 15      */
				vector		: 8,  /* 16 - 23 */
				__res2		: 40; /* 24 - 63 */
		पूर्ण;

		/* Remapped mode */
		काष्ठा अणु
			__u64	r_present	: 1,  /*  0      */
				r_fpd		: 1,  /*  1      */
				dst_mode	: 1,  /*  2      */
				redir_hपूर्णांक	: 1,  /*  3      */
				trigger_mode	: 1,  /*  4      */
				dlvry_mode	: 3,  /*  5 -  7 */
				r_avail		: 4,  /*  8 - 11 */
				r_res0		: 4,  /* 12 - 15 */
				r_vector	: 8,  /* 16 - 23 */
				r_res1		: 8,  /* 24 - 31 */
				dest_id		: 32; /* 32 - 63 */
		पूर्ण;

		/* Posted mode */
		काष्ठा अणु
			__u64	p_present	: 1,  /*  0      */
				p_fpd		: 1,  /*  1      */
				p_res0		: 6,  /*  2 -  7 */
				p_avail		: 4,  /*  8 - 11 */
				p_res1		: 2,  /* 12 - 13 */
				p_urgent	: 1,  /* 14      */
				p_pst		: 1,  /* 15      */
				p_vector	: 8,  /* 16 - 23 */
				p_res2		: 14, /* 24 - 37 */
				pda_l		: 26; /* 38 - 63 */
		पूर्ण;
		__u64 low;
	पूर्ण;

	जोड़ अणु
		/* Shared between remapped and posted mode*/
		काष्ठा अणु
			__u64	sid		: 16,  /* 64 - 79  */
				sq		: 2,   /* 80 - 81  */
				svt		: 2,   /* 82 - 83  */
				__res3		: 44;  /* 84 - 127 */
		पूर्ण;

		/* Posted mode*/
		काष्ठा अणु
			__u64	p_sid		: 16,  /* 64 - 79  */
				p_sq		: 2,   /* 80 - 81  */
				p_svt		: 2,   /* 82 - 83  */
				p_res3		: 12,  /* 84 - 95  */
				pda_h		: 32;  /* 96 - 127 */
		पूर्ण;
		__u64 high;
	पूर्ण;
पूर्ण;

अटल अंतरभूत व्योम dmar_copy_shared_irte(काष्ठा irte *dst, काष्ठा irte *src)
अणु
	dst->present	= src->present;
	dst->fpd	= src->fpd;
	dst->avail	= src->avail;
	dst->pst	= src->pst;
	dst->vector	= src->vector;
	dst->sid	= src->sid;
	dst->sq		= src->sq;
	dst->svt	= src->svt;
पूर्ण

#घोषणा PDA_LOW_BIT    26
#घोषणा PDA_HIGH_BIT   32

/* Can't use the common MSI पूर्णांकerrupt functions
 * since DMAR is not a pci device
 */
काष्ठा irq_data;
बाह्य व्योम dmar_msi_unmask(काष्ठा irq_data *data);
बाह्य व्योम dmar_msi_mask(काष्ठा irq_data *data);
बाह्य व्योम dmar_msi_पढ़ो(पूर्णांक irq, काष्ठा msi_msg *msg);
बाह्य व्योम dmar_msi_ग_लिखो(पूर्णांक irq, काष्ठा msi_msg *msg);
बाह्य पूर्णांक dmar_set_पूर्णांकerrupt(काष्ठा पूर्णांकel_iommu *iommu);
बाह्य irqवापस_t dmar_fault(पूर्णांक irq, व्योम *dev_id);
बाह्य पूर्णांक dmar_alloc_hwirq(पूर्णांक id, पूर्णांक node, व्योम *arg);
बाह्य व्योम dmar_मुक्त_hwirq(पूर्णांक irq);

#पूर्ण_अगर /* __DMAR_H__ */
