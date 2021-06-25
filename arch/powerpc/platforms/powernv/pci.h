<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __POWERNV_PCI_H
#घोषणा __POWERNV_PCI_H

#समावेश <linux/compiler.h>		/* क्रम __म_लिखो */
#समावेश <linux/iommu.h>
#समावेश <यंत्र/iommu.h>
#समावेश <यंत्र/msi_biपंचांगap.h>

काष्ठा pci_dn;

क्रमागत pnv_phb_type अणु
	PNV_PHB_IODA1,
	PNV_PHB_IODA2,
	PNV_PHB_NPU_OCAPI,
पूर्ण;

/* Precise PHB model क्रम error management */
क्रमागत pnv_phb_model अणु
	PNV_PHB_MODEL_UNKNOWN,
	PNV_PHB_MODEL_P7IOC,
	PNV_PHB_MODEL_PHB3,
पूर्ण;

#घोषणा PNV_PCI_DIAG_BUF_SIZE	8192
#घोषणा PNV_IODA_PE_DEV		(1 << 0)	/* PE has single PCI device	*/
#घोषणा PNV_IODA_PE_BUS		(1 << 1)	/* PE has primary PCI bus	*/
#घोषणा PNV_IODA_PE_BUS_ALL	(1 << 2)	/* PE has subordinate buses	*/
#घोषणा PNV_IODA_PE_MASTER	(1 << 3)	/* Master PE in compound हाल	*/
#घोषणा PNV_IODA_PE_SLAVE	(1 << 4)	/* Slave PE in compound हाल	*/
#घोषणा PNV_IODA_PE_VF		(1 << 5)	/* PE क्रम one VF 		*/

/*
 * A brief note on PNV_IODA_PE_BUS_ALL
 *
 * This is needed because of the behaviour of PCIe-to-PCI bridges. The PHB uses
 * the Requester ID field of the PCIe request header to determine the device
 * (and PE) that initiated a DMA. In legacy PCI inभागidual memory पढ़ो/ग_लिखो
 * requests aren't tagged with the RID. To work around this the PCIe-to-PCI
 * bridge will use (secondary_bus_no << 8) | 0x00 as the RID on the PCIe side.
 *
 * PCIe-to-X bridges have a similar issue even though PCI-X requests also have
 * a RID in the transaction header. The PCIe-to-X bridge is permitted to "take
 * ownership" of a transaction by a PCI-X device when क्रमwarding it to the PCIe
 * side of the bridge.
 *
 * To work around these problems we use the BUS_ALL flag since every subordinate
 * bus of the bridge should go पूर्णांकo the same PE.
 */

/* Indicates operations are frozen क्रम a PE: MMIO in PESTA & DMA in PESTB. */
#घोषणा PNV_IODA_STOPPED_STATE	0x8000000000000000

/* Data associated with a PE, including IOMMU tracking etc.. */
काष्ठा pnv_phb;
काष्ठा pnv_ioda_pe अणु
	अचिन्हित दीर्घ		flags;
	काष्ठा pnv_phb		*phb;
	पूर्णांक			device_count;

	/* A PE can be associated with a single device or an
	 * entire bus (& children). In the क्रमmer हाल, pdev
	 * is populated, in the later हाल, pbus is.
	 */
#अगर_घोषित CONFIG_PCI_IOV
	काष्ठा pci_dev          *parent_dev;
#पूर्ण_अगर
	काष्ठा pci_dev		*pdev;
	काष्ठा pci_bus		*pbus;

	/* Effective RID (device RID क्रम a device PE and base bus
	 * RID with devfn 0 क्रम a bus PE)
	 */
	अचिन्हित पूर्णांक		rid;

	/* PE number */
	अचिन्हित पूर्णांक		pe_number;

	/* "Base" iommu table, ie, 4K TCEs, 32-bit DMA */
	काष्ठा iommu_table_group table_group;

	/* 64-bit TCE bypass region */
	bool			tce_bypass_enabled;
	uपूर्णांक64_t		tce_bypass_base;

	/*
	 * Used to track whether we've करोne DMA setup क्रम this PE or not. We
	 * want to defer allocating TCE tables, etc until we've added a
	 * non-bridge device to the PE.
	 */
	bool			dma_setup_करोne;

	/* MSIs. MVE index is identical क्रम 32 and 64 bit MSI
	 * and -1 अगर not supported. (It's actually identical to the
	 * PE number)
	 */
	पूर्णांक			mve_number;

	/* PEs in compound हाल */
	काष्ठा pnv_ioda_pe	*master;
	काष्ठा list_head	slaves;

	/* Link in list of PE#s */
	काष्ठा list_head	list;
पूर्ण;

#घोषणा PNV_PHB_FLAG_EEH	(1 << 0)

काष्ठा pnv_phb अणु
	काष्ठा pci_controller	*hose;
	क्रमागत pnv_phb_type	type;
	क्रमागत pnv_phb_model	model;
	u64			hub_id;
	u64			opal_id;
	पूर्णांक			flags;
	व्योम __iomem		*regs;
	u64			regs_phys;
	spinlock_t		lock;

#अगर_घोषित CONFIG_DEBUG_FS
	पूर्णांक			has_dbgfs;
	काष्ठा dentry		*dbgfs;
#पूर्ण_अगर

	अचिन्हित पूर्णांक		msi_base;
	अचिन्हित पूर्णांक		msi32_support;
	काष्ठा msi_biपंचांगap	msi_bmp;
	पूर्णांक (*msi_setup)(काष्ठा pnv_phb *phb, काष्ठा pci_dev *dev,
			 अचिन्हित पूर्णांक hwirq, अचिन्हित पूर्णांक virq,
			 अचिन्हित पूर्णांक is_64, काष्ठा msi_msg *msg);
	पूर्णांक (*init_m64)(काष्ठा pnv_phb *phb);
	पूर्णांक (*get_pe_state)(काष्ठा pnv_phb *phb, पूर्णांक pe_no);
	व्योम (*मुक्तze_pe)(काष्ठा pnv_phb *phb, पूर्णांक pe_no);
	पूर्णांक (*unमुक्तze_pe)(काष्ठा pnv_phb *phb, पूर्णांक pe_no, पूर्णांक opt);

	काष्ठा अणु
		/* Global bridge info */
		अचिन्हित पूर्णांक		total_pe_num;
		अचिन्हित पूर्णांक		reserved_pe_idx;
		अचिन्हित पूर्णांक		root_pe_idx;

		/* 32-bit MMIO winकरोw */
		अचिन्हित पूर्णांक		m32_size;
		अचिन्हित पूर्णांक		m32_segsize;
		अचिन्हित पूर्णांक		m32_pci_base;

		/* 64-bit MMIO winकरोw */
		अचिन्हित पूर्णांक		m64_bar_idx;
		अचिन्हित दीर्घ		m64_size;
		अचिन्हित दीर्घ		m64_segsize;
		अचिन्हित दीर्घ		m64_base;
#घोषणा MAX_M64_BARS 64
		अचिन्हित दीर्घ		m64_bar_alloc;

		/* IO ports */
		अचिन्हित पूर्णांक		io_size;
		अचिन्हित पूर्णांक		io_segsize;
		अचिन्हित पूर्णांक		io_pci_base;

		/* PE allocation */
		काष्ठा mutex		pe_alloc_mutex;
		अचिन्हित दीर्घ		*pe_alloc;
		काष्ठा pnv_ioda_pe	*pe_array;

		/* M32 & IO segment maps */
		अचिन्हित पूर्णांक		*m64_segmap;
		अचिन्हित पूर्णांक		*m32_segmap;
		अचिन्हित पूर्णांक		*io_segmap;

		/* DMA32 segment maps - IODA1 only */
		अचिन्हित पूर्णांक		dma32_count;
		अचिन्हित पूर्णांक		*dma32_segmap;

		/* IRQ chip */
		पूर्णांक			irq_chip_init;
		काष्ठा irq_chip		irq_chip;

		/* Sorted list of used PE's based
		 * on the sequence of creation
		 */
		काष्ठा list_head	pe_list;
		काष्ठा mutex            pe_list_mutex;

		/* Reverse map of PEs, indexed by अणुbus, devfnपूर्ण */
		अचिन्हित पूर्णांक		pe_rmap[0x10000];
	पूर्ण ioda;

	/* PHB and hub diagnostics */
	अचिन्हित पूर्णांक		diag_data_size;
	u8			*diag_data;
पूर्ण;


/* IODA PE management */

अटल अंतरभूत bool pnv_pci_is_m64(काष्ठा pnv_phb *phb, काष्ठा resource *r)
अणु
	/*
	 * WARNING: We cannot rely on the resource flags. The Linux PCI
	 * allocation code someबार decides to put a 64-bit prefetchable
	 * BAR in the 32-bit winकरोw, so we have to compare the addresses.
	 *
	 * For simplicity we only test resource start.
	 */
	वापस (r->start >= phb->ioda.m64_base &&
		r->start < (phb->ioda.m64_base + phb->ioda.m64_size));
पूर्ण

अटल अंतरभूत bool pnv_pci_is_m64_flags(अचिन्हित दीर्घ resource_flags)
अणु
	अचिन्हित दीर्घ flags = (IORESOURCE_MEM_64 | IORESOURCE_PREFETCH);

	वापस (resource_flags & flags) == flags;
पूर्ण

पूर्णांक pnv_ioda_configure_pe(काष्ठा pnv_phb *phb, काष्ठा pnv_ioda_pe *pe);
पूर्णांक pnv_ioda_deconfigure_pe(काष्ठा pnv_phb *phb, काष्ठा pnv_ioda_pe *pe);

व्योम pnv_pci_ioda2_setup_dma_pe(काष्ठा pnv_phb *phb, काष्ठा pnv_ioda_pe *pe);
व्योम pnv_pci_ioda2_release_pe_dma(काष्ठा pnv_ioda_pe *pe);

काष्ठा pnv_ioda_pe *pnv_ioda_alloc_pe(काष्ठा pnv_phb *phb, पूर्णांक count);
व्योम pnv_ioda_मुक्त_pe(काष्ठा pnv_ioda_pe *pe);

#अगर_घोषित CONFIG_PCI_IOV
/*
 * For SR-IOV we want to put each VF's MMIO resource in to a separate PE.
 * This requires a bit of acrobatics with the MMIO -> PE configuration
 * and this काष्ठाure is used to keep track of it all.
 */
काष्ठा pnv_iov_data अणु
	/* number of VFs enabled */
	u16     num_vfs;

	/* poपूर्णांकer to the array of VF PEs. num_vfs दीर्घ*/
	काष्ठा pnv_ioda_pe *vf_pe_arr;

	/* Did we map the VF BAR with single-PE IODA BARs? */
	bool    m64_single_mode[PCI_SRIOV_NUM_BARS];

	/*
	 * True अगर we're using any segmented winकरोws. In that हाल we need
	 * shअगरt the start of the IOV resource the segment corresponding to
	 * the allocated PE.
	 */
	bool    need_shअगरt;

	/*
	 * Bit mask used to track which m64 winकरोws are used to map the
	 * SR-IOV BARs क्रम this device.
	 */
	DECLARE_BITMAP(used_m64_bar_mask, MAX_M64_BARS);

	/*
	 * If we map the SR-IOV BARs with a segmented winकरोw then
	 * parts of that winकरोw will be "claimed" by other PEs.
	 *
	 * "holes" here is used to reserve the leading portion
	 * of the winकरोw that is used by other (non VF) PEs.
	 */
	काष्ठा resource holes[PCI_SRIOV_NUM_BARS];
पूर्ण;

अटल अंतरभूत काष्ठा pnv_iov_data *pnv_iov_get(काष्ठा pci_dev *pdev)
अणु
	वापस pdev->dev.archdata.iov_data;
पूर्ण

व्योम pnv_pci_ioda_fixup_iov(काष्ठा pci_dev *pdev);
resource_माप_प्रकार pnv_pci_iov_resource_alignment(काष्ठा pci_dev *pdev, पूर्णांक resno);

पूर्णांक pnv_pcibios_sriov_enable(काष्ठा pci_dev *pdev, u16 num_vfs);
पूर्णांक pnv_pcibios_sriov_disable(काष्ठा pci_dev *pdev);
#पूर्ण_अगर /* CONFIG_PCI_IOV */

बाह्य काष्ठा pci_ops pnv_pci_ops;

व्योम pnv_pci_dump_phb_diag_data(काष्ठा pci_controller *hose,
				अचिन्हित अक्षर *log_buff);
पूर्णांक pnv_pci_cfg_पढ़ो(काष्ठा pci_dn *pdn,
		     पूर्णांक where, पूर्णांक size, u32 *val);
पूर्णांक pnv_pci_cfg_ग_लिखो(काष्ठा pci_dn *pdn,
		      पूर्णांक where, पूर्णांक size, u32 val);
बाह्य काष्ठा iommu_table *pnv_pci_table_alloc(पूर्णांक nid);

बाह्य व्योम pnv_pci_init_ioda_hub(काष्ठा device_node *np);
बाह्य व्योम pnv_pci_init_ioda2_phb(काष्ठा device_node *np);
बाह्य व्योम pnv_pci_init_npu2_खोलोcapi_phb(काष्ठा device_node *np);
बाह्य व्योम pnv_pci_reset_secondary_bus(काष्ठा pci_dev *dev);
बाह्य पूर्णांक pnv_eeh_phb_reset(काष्ठा pci_controller *hose, पूर्णांक option);

बाह्य पूर्णांक pnv_setup_msi_irqs(काष्ठा pci_dev *pdev, पूर्णांक nvec, पूर्णांक type);
बाह्य व्योम pnv_tearकरोwn_msi_irqs(काष्ठा pci_dev *pdev);
बाह्य काष्ठा pnv_ioda_pe *pnv_pci_bdfn_to_pe(काष्ठा pnv_phb *phb, u16 bdfn);
बाह्य काष्ठा pnv_ioda_pe *pnv_ioda_get_pe(काष्ठा pci_dev *dev);
बाह्य व्योम pnv_set_msi_irq_chip(काष्ठा pnv_phb *phb, अचिन्हित पूर्णांक virq);
बाह्य अचिन्हित दीर्घ pnv_pci_ioda2_get_table_size(__u32 page_shअगरt,
		__u64 winकरोw_size, __u32 levels);
बाह्य पूर्णांक pnv_eeh_post_init(व्योम);

__म_लिखो(3, 4)
बाह्य व्योम pe_level_prपूर्णांकk(स्थिर काष्ठा pnv_ioda_pe *pe, स्थिर अक्षर *level,
			    स्थिर अक्षर *fmt, ...);
#घोषणा pe_err(pe, fmt, ...)					\
	pe_level_prपूर्णांकk(pe, KERN_ERR, fmt, ##__VA_ARGS__)
#घोषणा pe_warn(pe, fmt, ...)					\
	pe_level_prपूर्णांकk(pe, KERN_WARNING, fmt, ##__VA_ARGS__)
#घोषणा pe_info(pe, fmt, ...)					\
	pe_level_prपूर्णांकk(pe, KERN_INFO, fmt, ##__VA_ARGS__)

/* pci-ioda-tce.c */
#घोषणा POWERNV_IOMMU_DEFAULT_LEVELS	2
#घोषणा POWERNV_IOMMU_MAX_LEVELS	5

बाह्य पूर्णांक pnv_tce_build(काष्ठा iommu_table *tbl, दीर्घ index, दीर्घ npages,
		अचिन्हित दीर्घ uaddr, क्रमागत dma_data_direction direction,
		अचिन्हित दीर्घ attrs);
बाह्य व्योम pnv_tce_मुक्त(काष्ठा iommu_table *tbl, दीर्घ index, दीर्घ npages);
बाह्य पूर्णांक pnv_tce_xchg(काष्ठा iommu_table *tbl, दीर्घ index,
		अचिन्हित दीर्घ *hpa, क्रमागत dma_data_direction *direction,
		bool alloc);
बाह्य __be64 *pnv_tce_useraddrptr(काष्ठा iommu_table *tbl, दीर्घ index,
		bool alloc);
बाह्य अचिन्हित दीर्घ pnv_tce_get(काष्ठा iommu_table *tbl, दीर्घ index);

बाह्य दीर्घ pnv_pci_ioda2_table_alloc_pages(पूर्णांक nid, __u64 bus_offset,
		__u32 page_shअगरt, __u64 winकरोw_size, __u32 levels,
		bool alloc_userspace_copy, काष्ठा iommu_table *tbl);
बाह्य व्योम pnv_pci_ioda2_table_मुक्त_pages(काष्ठा iommu_table *tbl);

बाह्य दीर्घ pnv_pci_link_table_and_group(पूर्णांक node, पूर्णांक num,
		काष्ठा iommu_table *tbl,
		काष्ठा iommu_table_group *table_group);
बाह्य व्योम pnv_pci_unlink_table_and_group(काष्ठा iommu_table *tbl,
		काष्ठा iommu_table_group *table_group);
बाह्य व्योम pnv_pci_setup_iommu_table(काष्ठा iommu_table *tbl,
		व्योम *tce_mem, u64 tce_size,
		u64 dma_offset, अचिन्हित पूर्णांक page_shअगरt);

बाह्य अचिन्हित दीर्घ pnv_ioda_parse_tce_sizes(काष्ठा pnv_phb *phb);

अटल अंतरभूत काष्ठा pnv_phb *pci_bus_to_pnvhb(काष्ठा pci_bus *bus)
अणु
	काष्ठा pci_controller *hose = bus->sysdata;

	अगर (hose)
		वापस hose->निजी_data;

	वापस शून्य;
पूर्ण

#पूर्ण_अगर /* __POWERNV_PCI_H */
