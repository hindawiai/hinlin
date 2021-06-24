<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_PARISC_ROPES_H_
#घोषणा _ASM_PARISC_ROPES_H_

#समावेश <यंत्र/parisc-device.h>

#अगर_घोषित CONFIG_64BIT
/* "low end" PA8800 machines use ZX1 chipset: PAT PDC and only run 64-bit */
#घोषणा ZX1_SUPPORT
#पूर्ण_अगर

#अगर_घोषित CONFIG_PROC_FS
/* depends on proc fs support. But costs CPU perक्रमmance */
#अघोषित SBA_COLLECT_STATS
#पूर्ण_अगर

/*
** The number of pdir entries to "free" beक्रमe issuing
** a पढ़ो to PCOM रेजिस्टर to flush out PCOM ग_लिखोs.
** Interacts with allocation granularity (ie 4 or 8 entries
** allocated and मुक्त'd/purged at a समय might make this
** less पूर्णांकeresting).
*/
#घोषणा DELAYED_RESOURCE_CNT	16

#घोषणा MAX_IOC		2	/* per Ike. Pluto/Astro only have 1. */
#घोषणा ROPES_PER_IOC	8	/* per Ike half or Pluto/Astro */

काष्ठा ioc अणु
	व्योम __iomem	*ioc_hpa;	/* I/O MMU base address */
	अक्षर		*res_map;	/* resource map, bit == pdir entry */
	u64		*pdir_base;	/* physical base address */
	अचिन्हित दीर्घ	ibase;		/* pdir IOV Space base - shared w/lba_pci */
	अचिन्हित दीर्घ	imask;		/* pdir IOV Space mask - shared w/lba_pci */
#अगर_घोषित ZX1_SUPPORT
	अचिन्हित दीर्घ	iovp_mask;	/* help convert IOVA to IOVP */
#पूर्ण_अगर
	अचिन्हित दीर्घ	*res_hपूर्णांक;	/* next avail IOVP - circular search */
	spinlock_t	res_lock;
	अचिन्हित पूर्णांक	res_bitshअगरt;	/* from the LEFT! */
	अचिन्हित पूर्णांक	res_size;	/* size of resource map in bytes */
#अगर_घोषित SBA_HINT_SUPPORT
/* FIXME : DMA HINTs not used */
	अचिन्हित दीर्घ	hपूर्णांक_mask_pdir; /* bits used क्रम DMA hपूर्णांकs */
	अचिन्हित पूर्णांक	hपूर्णांक_shअगरt_pdir;
#पूर्ण_अगर
#अगर DELAYED_RESOURCE_CNT > 0
	पूर्णांक		saved_cnt;
	काष्ठा sba_dma_pair अणु
			dma_addr_t	iova;
			माप_प्रकार		size;
        पूर्ण saved[DELAYED_RESOURCE_CNT];
#पूर्ण_अगर

#अगर_घोषित SBA_COLLECT_STATS
#घोषणा SBA_SEARCH_SAMPLE	0x100
	अचिन्हित दीर्घ	avg_search[SBA_SEARCH_SAMPLE];
	अचिन्हित दीर्घ	avg_idx;	/* current index पूर्णांकo avg_search */
	अचिन्हित दीर्घ	used_pages;
	अचिन्हित दीर्घ	msingle_calls;
	अचिन्हित दीर्घ	msingle_pages;
	अचिन्हित दीर्घ	msg_calls;
	अचिन्हित दीर्घ	msg_pages;
	अचिन्हित दीर्घ	usingle_calls;
	अचिन्हित दीर्घ	usingle_pages;
	अचिन्हित दीर्घ	usg_calls;
	अचिन्हित दीर्घ	usg_pages;
#पूर्ण_अगर
        /* STUFF We करोn't need in perक्रमmance path */
	अचिन्हित पूर्णांक	pdir_size;	/* in bytes, determined by IOV Space size */
पूर्ण;

काष्ठा sba_device अणु
	काष्ठा sba_device	*next;  /* list of SBA's in प्रणाली */
	काष्ठा parisc_device	*dev;   /* dev found in bus walk */
	स्थिर अक्षर		*name;
	व्योम __iomem		*sba_hpa; /* base address */
	spinlock_t		sba_lock;
	अचिन्हित पूर्णांक		flags;  /* state/functionality enabled */
	अचिन्हित पूर्णांक		hw_rev;  /* HW revision of chip */

	काष्ठा resource		chip_resv; /* MMIO reserved क्रम chip */
	काष्ठा resource		iommu_resv; /* MMIO reserved क्रम iommu */

	अचिन्हित पूर्णांक		num_ioc;  /* number of on-board IOC's */
	काष्ठा ioc		ioc[MAX_IOC];
पूर्ण;

#घोषणा ASTRO_RUNWAY_PORT	0x582
#घोषणा IKE_MERCED_PORT		0x803
#घोषणा REO_MERCED_PORT		0x804
#घोषणा REOG_MERCED_PORT	0x805
#घोषणा PLUTO_MCKINLEY_PORT	0x880

अटल अंतरभूत पूर्णांक IS_ASTRO(काष्ठा parisc_device *d) अणु
	वापस d->id.hversion == ASTRO_RUNWAY_PORT;
पूर्ण

अटल अंतरभूत पूर्णांक IS_IKE(काष्ठा parisc_device *d) अणु
	वापस d->id.hversion == IKE_MERCED_PORT;
पूर्ण

अटल अंतरभूत पूर्णांक IS_PLUTO(काष्ठा parisc_device *d) अणु
	वापस d->id.hversion == PLUTO_MCKINLEY_PORT;
पूर्ण

#घोषणा PLUTO_IOVA_BASE	(1UL*1024*1024*1024)	/* 1GB */
#घोषणा PLUTO_IOVA_SIZE	(1UL*1024*1024*1024)	/* 1GB */
#घोषणा PLUTO_GART_SIZE	(PLUTO_IOVA_SIZE / 2)

#घोषणा SBA_Pसूची_VALID_BIT	0x8000000000000000ULL

#घोषणा SBA_AGPGART_COOKIE	0x0000badbadc0ffeeULL

#घोषणा SBA_FUNC_ID	0x0000	/* function id */
#घोषणा SBA_FCLASS	0x0008	/* function class, bist, header, rev... */

#घोषणा SBA_FUNC_SIZE 4096   /* SBA configuration function reg set */

#घोषणा ASTRO_IOC_OFFSET	(32 * SBA_FUNC_SIZE)
#घोषणा PLUTO_IOC_OFFSET	(1 * SBA_FUNC_SIZE)
/* Ike's IOC's occupy functions 2 and 3 */
#घोषणा IKE_IOC_OFFSET(p)	((p+2) * SBA_FUNC_SIZE)

#घोषणा IOC_CTRL          0x8	/* IOC_CTRL offset */
#घोषणा IOC_CTRL_TC       (1 << 0) /* TOC Enable */
#घोषणा IOC_CTRL_CE       (1 << 1) /* Coalesce Enable */
#घोषणा IOC_CTRL_DE       (1 << 2) /* Dillon Enable */
#घोषणा IOC_CTRL_RM       (1 << 8) /* Real Mode */
#घोषणा IOC_CTRL_NC       (1 << 9) /* Non Coherent Mode */
#घोषणा IOC_CTRL_D4       (1 << 11) /* Disable 4-byte coalescing */
#घोषणा IOC_CTRL_DD       (1 << 13) /* Disable distr. LMMIO range coalescing */

/*
** Offsets पूर्णांकo MBIB (Function 0 on Ike and hopefully Astro)
** Firmware programs this stuff. Don't touch it.
*/
#घोषणा LMMIO_सूचीECT0_BASE  0x300
#घोषणा LMMIO_सूचीECT0_MASK  0x308
#घोषणा LMMIO_सूचीECT0_ROUTE 0x310

#घोषणा LMMIO_DIST_BASE  0x360
#घोषणा LMMIO_DIST_MASK  0x368
#घोषणा LMMIO_DIST_ROUTE 0x370

#घोषणा IOS_DIST_BASE	0x390
#घोषणा IOS_DIST_MASK	0x398
#घोषणा IOS_DIST_ROUTE	0x3A0

#घोषणा IOS_सूचीECT_BASE	0x3C0
#घोषणा IOS_सूचीECT_MASK	0x3C8
#घोषणा IOS_सूचीECT_ROUTE 0x3D0

/*
** Offsets पूर्णांकo I/O TLB (Function 2 and 3 on Ike)
*/
#घोषणा ROPE0_CTL	0x200  /* "regbus pci0" */
#घोषणा ROPE1_CTL	0x208
#घोषणा ROPE2_CTL	0x210
#घोषणा ROPE3_CTL	0x218
#घोषणा ROPE4_CTL	0x220
#घोषणा ROPE5_CTL	0x228
#घोषणा ROPE6_CTL	0x230
#घोषणा ROPE7_CTL	0x238

#घोषणा IOC_ROPE0_CFG	0x500	/* pluto only */
#घोषणा   IOC_ROPE_AO	  0x10	/* Allow "Relaxed Ordering" */

#घोषणा HF_ENABLE	0x40

#घोषणा IOC_IBASE	0x300	/* IO TLB */
#घोषणा IOC_IMASK	0x308
#घोषणा IOC_PCOM	0x310
#घोषणा IOC_TCNFG	0x318
#घोषणा IOC_Pसूची_BASE	0x320

/*
** IOC supports 4/8/16/64KB page sizes (see TCNFG रेजिस्टर)
** It's safer (aव्योम memory corruption) to keep DMA page mappings
** equivalently sized to VM PAGE_SIZE.
**
** We really can't aव्योम generating a new mapping क्रम each
** page since the Virtual Coherence Index has to be generated
** and updated क्रम each page.
**
** PAGE_SIZE could be greater than IOVP_SIZE. But not the inverse.
*/
#घोषणा IOVP_SIZE	PAGE_SIZE
#घोषणा IOVP_SHIFT	PAGE_SHIFT
#घोषणा IOVP_MASK	PAGE_MASK

#घोषणा SBA_PERF_CFG	0x708	/* Perक्रमmance Counter stuff */
#घोषणा SBA_PERF_MASK1	0x718
#घोषणा SBA_PERF_MASK2	0x730

/*
** Offsets पूर्णांकo PCI Perक्रमmance Counters (functions 12 and 13)
** Controlled by PERF रेजिस्टरs in function 2 & 3 respectively.
*/
#घोषणा SBA_PERF_CNT1	0x200
#घोषणा SBA_PERF_CNT2	0x208
#घोषणा SBA_PERF_CNT3	0x210

/*
** lba_device: Per instance Elroy data काष्ठाure
*/
काष्ठा lba_device अणु
	काष्ठा pci_hba_data	hba;

	spinlock_t		lba_lock;
	व्योम			*iosapic_obj;

#अगर_घोषित CONFIG_64BIT
	व्योम __iomem		*iop_base;	/* PA_VIEW - क्रम IO port accessor funcs */
#पूर्ण_अगर

	पूर्णांक			flags;		/* state/functionality enabled */
	पूर्णांक			hw_rev;		/* HW revision of chip */
पूर्ण;

#घोषणा ELROY_HVERS		0x782
#घोषणा MERCURY_HVERS		0x783
#घोषणा QUICKSILVER_HVERS	0x784

अटल अंतरभूत पूर्णांक IS_ELROY(काष्ठा parisc_device *d) अणु
	वापस (d->id.hversion == ELROY_HVERS);
पूर्ण

अटल अंतरभूत पूर्णांक IS_MERCURY(काष्ठा parisc_device *d) अणु
	वापस (d->id.hversion == MERCURY_HVERS);
पूर्ण

अटल अंतरभूत पूर्णांक IS_QUICKSILVER(काष्ठा parisc_device *d) अणु
	वापस (d->id.hversion == QUICKSILVER_HVERS);
पूर्ण

अटल अंतरभूत पूर्णांक agp_mode_mercury(व्योम __iomem *hpa) अणु
	u64 bus_mode;

	bus_mode = पढ़ोl(hpa + 0x0620);
	अगर (bus_mode & 1)
		वापस 1;

	वापस 0;
पूर्ण

/*
** I/O SAPIC init function
** Caller knows where an I/O SAPIC is. LBA has an पूर्णांकegrated I/O SAPIC.
** Call setup as part of per instance initialization.
** (ie *not* init_module() function unless only one is present.)
** fixup_irq is to initialize PCI IRQ line support and
** भवize pcidev->irq value. To be called by pci_fixup_bus().
*/
बाह्य व्योम *iosapic_रेजिस्टर(अचिन्हित दीर्घ hpa);
बाह्य पूर्णांक iosapic_fixup_irq(व्योम *obj, काष्ठा pci_dev *pcidev);

#घोषणा LBA_FUNC_ID	0x0000	/* function id */
#घोषणा LBA_FCLASS	0x0008	/* function class, bist, header, rev... */
#घोषणा LBA_CAPABLE	0x0030	/* capabilities रेजिस्टर */

#घोषणा LBA_PCI_CFG_ADDR	0x0040	/* poke CFG address here */
#घोषणा LBA_PCI_CFG_DATA	0x0048	/* पढ़ो or ग_लिखो data here */

#घोषणा LBA_PMC_MTLT	0x0050	/* Firmware sets this - पढ़ो only. */
#घोषणा LBA_FW_SCRATCH	0x0058	/* Firmware ग_लिखोs the PCI bus number here. */
#घोषणा LBA_ERROR_ADDR	0x0070	/* On error, address माला_लो logged here */

#घोषणा LBA_ARB_MASK	0x0080	/* bit 0 enable arbitration. PAT/PDC enables */
#घोषणा LBA_ARB_PRI	0x0088	/* firmware sets this. */
#घोषणा LBA_ARB_MODE	0x0090	/* firmware sets this. */
#घोषणा LBA_ARB_MTLT	0x0098	/* firmware sets this. */

#घोषणा LBA_MOD_ID	0x0100	/* Module ID. PDC_PAT_CELL reports 4 */

#घोषणा LBA_STAT_CTL	0x0108	/* Status & Control */
#घोषणा   LBA_BUS_RESET		0x01	/*  Deनिश्चित PCI Bus Reset Signal */
#घोषणा   CLEAR_ERRLOG		0x10	/*  "Clear Error Log" cmd */
#घोषणा   CLEAR_ERRLOG_ENABLE	0x20	/*  "Clear Error Log" Enable */
#घोषणा   HF_ENABLE	0x40	/*    enable HF mode (शेष is -1 mode) */

#घोषणा LBA_LMMIO_BASE	0x0200	/* < 4GB I/O address range */
#घोषणा LBA_LMMIO_MASK	0x0208

#घोषणा LBA_GMMIO_BASE	0x0210	/* > 4GB I/O address range */
#घोषणा LBA_GMMIO_MASK	0x0218

#घोषणा LBA_WLMMIO_BASE	0x0220	/* All < 4GB ranges under the same *SBA* */
#घोषणा LBA_WLMMIO_MASK	0x0228

#घोषणा LBA_WGMMIO_BASE	0x0230	/* All > 4GB ranges under the same *SBA* */
#घोषणा LBA_WGMMIO_MASK	0x0238

#घोषणा LBA_IOS_BASE	0x0240	/* I/O port space क्रम this LBA */
#घोषणा LBA_IOS_MASK	0x0248

#घोषणा LBA_ELMMIO_BASE	0x0250	/* Extra LMMIO range */
#घोषणा LBA_ELMMIO_MASK	0x0258

#घोषणा LBA_EIOS_BASE	0x0260	/* Extra I/O port space */
#घोषणा LBA_EIOS_MASK	0x0268

#घोषणा LBA_GLOBAL_MASK	0x0270	/* Mercury only: Global Address Mask */
#घोषणा LBA_DMA_CTL	0x0278	/* firmware sets this */

#घोषणा LBA_IBASE	0x0300	/* SBA DMA support */
#घोषणा LBA_IMASK	0x0308

/* FIXME: ignore DMA Hपूर्णांक stuff until we can measure perक्रमmance */
#घोषणा LBA_HINT_CFG	0x0310
#घोषणा LBA_HINT_BASE	0x0380	/* 14 रेजिस्टरs at every 8 bytes. */

#घोषणा LBA_BUS_MODE	0x0620

/* ERROR regs are needed क्रम config cycle kluges */
#घोषणा LBA_ERROR_CONFIG 0x0680
#घोषणा     LBA_SMART_MODE 0x20
#घोषणा LBA_ERROR_STATUS 0x0688
#घोषणा LBA_ROPE_CTL     0x06A0

#घोषणा LBA_IOSAPIC_BASE	0x800 /* Offset of IRQ logic */

#पूर्ण_अगर /*_ASM_PARISC_ROPES_H_*/
