<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_S390_PCI_H
#घोषणा __ASM_S390_PCI_H

#समावेश <linux/pci.h>
#समावेश <linux/mutex.h>
#समावेश <linux/iommu.h>
#समावेश <linux/pci_hotplug.h>
#समावेश <यंत्र-generic/pci.h>
#समावेश <यंत्र/pci_clp.h>
#समावेश <यंत्र/pci_debug.h>
#समावेश <यंत्र/sclp.h>

#घोषणा PCIBIOS_MIN_IO		0x1000
#घोषणा PCIBIOS_MIN_MEM		0x10000000

#घोषणा pcibios_assign_all_busses()	(0)

व्योम __iomem *pci_iomap(काष्ठा pci_dev *, पूर्णांक, अचिन्हित दीर्घ);
व्योम pci_iounmap(काष्ठा pci_dev *, व्योम __iomem *);
पूर्णांक pci_करोमुख्य_nr(काष्ठा pci_bus *);
पूर्णांक pci_proc_करोमुख्य(काष्ठा pci_bus *);

#घोषणा ZPCI_BUS_NR			0	/* शेष bus number */

#घोषणा ZPCI_NR_DMA_SPACES		1
#घोषणा ZPCI_NR_DEVICES			CONFIG_PCI_NR_FUNCTIONS
#घोषणा ZPCI_DOMAIN_BITMAP_SIZE		(1 << 16)

#अगर_घोषित PCI
#अगर (ZPCI_NR_DEVICES > ZPCI_DOMAIN_BITMAP_SIZE)
# error ZPCI_NR_DEVICES can not be bigger than ZPCI_DOMAIN_BITMAP_SIZE
#पूर्ण_अगर
#पूर्ण_अगर /* PCI */

/* PCI Function Controls */
#घोषणा ZPCI_FC_FN_ENABLED		0x80
#घोषणा ZPCI_FC_ERROR			0x40
#घोषणा ZPCI_FC_BLOCKED			0x20
#घोषणा ZPCI_FC_DMA_ENABLED		0x10

#घोषणा ZPCI_FMB_DMA_COUNTER_VALID	(1 << 23)

काष्ठा zpci_fmb_fmt0 अणु
	u64 dma_rbytes;
	u64 dma_wbytes;
पूर्ण;

काष्ठा zpci_fmb_fmt1 अणु
	u64 rx_bytes;
	u64 rx_packets;
	u64 tx_bytes;
	u64 tx_packets;
पूर्ण;

काष्ठा zpci_fmb_fmt2 अणु
	u64 consumed_work_units;
	u64 max_work_units;
पूर्ण;

काष्ठा zpci_fmb_fmt3 अणु
	u64 tx_bytes;
पूर्ण;

काष्ठा zpci_fmb अणु
	u32 क्रमmat	: 8;
	u32 fmt_ind	: 24;
	u32 samples;
	u64 last_update;
	/* common counters */
	u64 ld_ops;
	u64 st_ops;
	u64 stb_ops;
	u64 rpcit_ops;
	/* क्रमmat specअगरic counters */
	जोड़ अणु
		काष्ठा zpci_fmb_fmt0 fmt0;
		काष्ठा zpci_fmb_fmt1 fmt1;
		काष्ठा zpci_fmb_fmt2 fmt2;
		काष्ठा zpci_fmb_fmt3 fmt3;
	पूर्ण;
पूर्ण __packed __aligned(128);

क्रमागत zpci_state अणु
	ZPCI_FN_STATE_STANDBY = 0,
	ZPCI_FN_STATE_CONFIGURED = 1,
	ZPCI_FN_STATE_RESERVED = 2,
पूर्ण;

काष्ठा zpci_bar_काष्ठा अणु
	काष्ठा resource *res;		/* bus resource */
	व्योम __iomem	*mio_wb;
	व्योम __iomem	*mio_wt;
	u32		val;		/* bar start & 3 flag bits */
	u16		map_idx;	/* index पूर्णांकo bar mapping array */
	u8		size;		/* order 2 exponent */
पूर्ण;

काष्ठा s390_करोमुख्य;

#घोषणा ZPCI_FUNCTIONS_PER_BUS 256
काष्ठा zpci_bus अणु
	काष्ठा kref		kref;
	काष्ठा pci_bus		*bus;
	काष्ठा zpci_dev		*function[ZPCI_FUNCTIONS_PER_BUS];
	काष्ठा list_head	resources;
	काष्ठा list_head	bus_next;
	काष्ठा resource		bus_resource;
	पूर्णांक			pchid;
	पूर्णांक			करोमुख्य_nr;
	bool			multअगरunction;
	क्रमागत pci_bus_speed	max_bus_speed;
पूर्ण;

/* Private data per function */
काष्ठा zpci_dev अणु
	काष्ठा zpci_bus *zbus;
	काष्ठा list_head entry;		/* list of all zpci_devices, needed क्रम hotplug, etc. */
	काष्ठा list_head bus_next;
	काष्ठा kref kref;
	काष्ठा hotplug_slot hotplug_slot;

	क्रमागत zpci_state state;
	u32		fid;		/* function ID, used by sclp */
	u32		fh;		/* function handle, used by insn's */
	u16		vfn;		/* भव function number */
	u16		pchid;		/* physical channel ID */
	u8		pfgid;		/* function group ID */
	u8		pft;		/* pci function type */
	u8		port;
	u8		rid_available	: 1;
	u8		has_hp_slot	: 1;
	u8		has_resources	: 1;
	u8		is_physfn	: 1;
	u8		util_str_avail	: 1;
	u8		reserved	: 3;
	अचिन्हित पूर्णांक	devfn;		/* DEVFN part of the RID*/

	काष्ठा mutex lock;
	u8 pfip[CLP_PFIP_NR_SEGMENTS];	/* pci function पूर्णांकernal path */
	u32 uid;			/* user defined id */
	u8 util_str[CLP_UTIL_STR_LEN];	/* utility string */

	/* IRQ stuff */
	u64		msi_addr;	/* MSI address */
	अचिन्हित पूर्णांक	max_msi;	/* maximum number of MSI's */
	अचिन्हित पूर्णांक	msi_first_bit;
	अचिन्हित पूर्णांक	msi_nr_irqs;
	काष्ठा airq_iv *aibv;		/* adapter पूर्णांकerrupt bit vector */
	अचिन्हित दीर्घ	aisb;		/* number of the summary bit */

	/* DMA stuff */
	अचिन्हित दीर्घ	*dma_table;
	spinlock_t	dma_table_lock;
	पूर्णांक		tlb_refresh;

	spinlock_t	iommu_biपंचांगap_lock;
	अचिन्हित दीर्घ	*iommu_biपंचांगap;
	अचिन्हित दीर्घ	*lazy_biपंचांगap;
	अचिन्हित दीर्घ	iommu_size;
	अचिन्हित दीर्घ	iommu_pages;
	अचिन्हित पूर्णांक	next_bit;

	काष्ठा iommu_device iommu_dev;  /* IOMMU core handle */

	अक्षर res_name[16];
	bool mio_capable;
	काष्ठा zpci_bar_काष्ठा bars[PCI_STD_NUM_BARS];

	u64		start_dma;	/* Start of available DMA addresses */
	u64		end_dma;	/* End of available DMA addresses */
	u64		dma_mask;	/* DMA address space mask */

	/* Function measurement block */
	काष्ठा zpci_fmb *fmb;
	u16		fmb_update;	/* update पूर्णांकerval */
	u16		fmb_length;
	/* software counters */
	atomic64_t allocated_pages;
	atomic64_t mapped_pages;
	atomic64_t unmapped_pages;

	u8		version;
	क्रमागत pci_bus_speed max_bus_speed;

	काष्ठा dentry	*debugfs_dev;

	काष्ठा s390_करोमुख्य *s390_करोमुख्य; /* s390 IOMMU करोमुख्य data */
पूर्ण;

अटल अंतरभूत bool zdev_enabled(काष्ठा zpci_dev *zdev)
अणु
	वापस (zdev->fh & (1UL << 31)) ? true : false;
पूर्ण

बाह्य स्थिर काष्ठा attribute_group *zpci_attr_groups[];
बाह्य अचिन्हित पूर्णांक s390_pci_क्रमce_भग्नing __initdata;
बाह्य अचिन्हित पूर्णांक s390_pci_no_rid;

/* -----------------------------------------------------------------------------
  Prototypes
----------------------------------------------------------------------------- */
/* Base stuff */
काष्ठा zpci_dev *zpci_create_device(u32 fid, u32 fh, क्रमागत zpci_state state);
पूर्णांक zpci_enable_device(काष्ठा zpci_dev *);
पूर्णांक zpci_disable_device(काष्ठा zpci_dev *);
पूर्णांक zpci_scan_configured_device(काष्ठा zpci_dev *zdev, u32 fh);
पूर्णांक zpci_deconfigure_device(काष्ठा zpci_dev *zdev);

पूर्णांक zpci_रेजिस्टर_ioat(काष्ठा zpci_dev *, u8, u64, u64, u64);
पूर्णांक zpci_unरेजिस्टर_ioat(काष्ठा zpci_dev *, u8);
व्योम zpci_हटाओ_reserved_devices(व्योम);

/* CLP */
पूर्णांक clp_setup_ग_लिखोback_mio(व्योम);
पूर्णांक clp_scan_pci_devices(व्योम);
पूर्णांक clp_query_pci_fn(काष्ठा zpci_dev *zdev);
पूर्णांक clp_enable_fh(काष्ठा zpci_dev *, u8);
पूर्णांक clp_disable_fh(काष्ठा zpci_dev *);
पूर्णांक clp_get_state(u32 fid, क्रमागत zpci_state *state);

/* UID */
व्योम update_uid_checking(bool new);

/* IOMMU Interface */
पूर्णांक zpci_init_iommu(काष्ठा zpci_dev *zdev);
व्योम zpci_destroy_iommu(काष्ठा zpci_dev *zdev);

#अगर_घोषित CONFIG_PCI
अटल अंतरभूत bool zpci_use_mio(काष्ठा zpci_dev *zdev)
अणु
	वापस अटल_branch_likely(&have_mio) && zdev->mio_capable;
पूर्ण

/* Error handling and recovery */
व्योम zpci_event_error(व्योम *);
व्योम zpci_event_availability(व्योम *);
bool zpci_is_enabled(व्योम);
#अन्यथा /* CONFIG_PCI */
अटल अंतरभूत व्योम zpci_event_error(व्योम *e) अणुपूर्ण
अटल अंतरभूत व्योम zpci_event_availability(व्योम *e) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_PCI */

#अगर_घोषित CONFIG_HOTPLUG_PCI_S390
पूर्णांक zpci_init_slot(काष्ठा zpci_dev *);
व्योम zpci_निकास_slot(काष्ठा zpci_dev *);
#अन्यथा /* CONFIG_HOTPLUG_PCI_S390 */
अटल अंतरभूत पूर्णांक zpci_init_slot(काष्ठा zpci_dev *zdev)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम zpci_निकास_slot(काष्ठा zpci_dev *zdev) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_HOTPLUG_PCI_S390 */

/* Helpers */
अटल अंतरभूत काष्ठा zpci_dev *to_zpci(काष्ठा pci_dev *pdev)
अणु
	काष्ठा zpci_bus *zbus = pdev->sysdata;

	वापस zbus->function[pdev->devfn];
पूर्ण

अटल अंतरभूत काष्ठा zpci_dev *to_zpci_dev(काष्ठा device *dev)
अणु
	वापस to_zpci(to_pci_dev(dev));
पूर्ण

काष्ठा zpci_dev *get_zdev_by_fid(u32);

/* DMA */
पूर्णांक zpci_dma_init(व्योम);
व्योम zpci_dma_निकास(व्योम);

पूर्णांक __init zpci_irq_init(व्योम);
व्योम __init zpci_irq_निकास(व्योम);

/* FMB */
पूर्णांक zpci_fmb_enable_device(काष्ठा zpci_dev *);
पूर्णांक zpci_fmb_disable_device(काष्ठा zpci_dev *);

/* Debug */
पूर्णांक zpci_debug_init(व्योम);
व्योम zpci_debug_निकास(व्योम);
व्योम zpci_debug_init_device(काष्ठा zpci_dev *, स्थिर अक्षर *);
व्योम zpci_debug_निकास_device(काष्ठा zpci_dev *);

/* Error reporting */
पूर्णांक zpci_report_error(काष्ठा pci_dev *, काष्ठा zpci_report_error_header *);

#अगर_घोषित CONFIG_NUMA

/* Returns the node based on PCI bus */
अटल अंतरभूत पूर्णांक __pcibus_to_node(स्थिर काष्ठा pci_bus *bus)
अणु
	वापस NUMA_NO_NODE;
पूर्ण

अटल अंतरभूत स्थिर काष्ठा cpumask *
cpumask_of_pcibus(स्थिर काष्ठा pci_bus *bus)
अणु
	वापस cpu_online_mask;
पूर्ण

#पूर्ण_अगर /* CONFIG_NUMA */

#पूर्ण_अगर
