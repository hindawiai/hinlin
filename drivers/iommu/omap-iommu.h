<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * omap iommu: मुख्य काष्ठाures
 *
 * Copyright (C) 2008-2009 Nokia Corporation
 *
 * Written by Hiroshi DOYU <Hiroshi.DOYU@nokia.com>
 */

#अगर_अघोषित _OMAP_IOMMU_H
#घोषणा _OMAP_IOMMU_H

#समावेश <linux/bitops.h>
#समावेश <linux/iommu.h>

#घोषणा क्रम_each_iotlb_cr(obj, n, __i, cr)				\
	क्रम (__i = 0;							\
	     (__i < (n)) && (cr = __iotlb_पढ़ो_cr((obj), __i), true);	\
	     __i++)

काष्ठा iotlb_entry अणु
	u32 da;
	u32 pa;
	u32 pgsz, prsvd, valid;
	u32 endian, elsz, mixed;
पूर्ण;

/**
 * काष्ठा omap_iommu_device - omap iommu device data
 * @pgtable:	page table used by an omap iommu attached to a करोमुख्य
 * @iommu_dev:	poपूर्णांकer to store an omap iommu instance attached to a करोमुख्य
 */
काष्ठा omap_iommu_device अणु
	u32 *pgtable;
	काष्ठा omap_iommu *iommu_dev;
पूर्ण;

/**
 * काष्ठा omap_iommu_करोमुख्य - omap iommu करोमुख्य
 * @num_iommus: number of iommus in this करोमुख्य
 * @iommus:	omap iommu device data क्रम all iommus in this करोमुख्य
 * @dev:	Device using this करोमुख्य.
 * @lock:	करोमुख्य lock, should be taken when attaching/detaching
 * @करोमुख्य:	generic करोमुख्य handle used by iommu core code
 */
काष्ठा omap_iommu_करोमुख्य अणु
	u32 num_iommus;
	काष्ठा omap_iommu_device *iommus;
	काष्ठा device *dev;
	spinlock_t lock;
	काष्ठा iommu_करोमुख्य करोमुख्य;
पूर्ण;

काष्ठा omap_iommu अणु
	स्थिर अक्षर	*name;
	व्योम __iomem	*regbase;
	काष्ठा regmap	*syscfg;
	काष्ठा device	*dev;
	काष्ठा iommu_करोमुख्य *करोमुख्य;
	काष्ठा dentry	*debug_dir;

	spinlock_t	iommu_lock;	/* global क्रम this whole object */

	/*
	 * We करोn't change iopgd क्रम a situation like pgd क्रम a task,
	 * but share it globally क्रम each iommu.
	 */
	u32		*iopgd;
	spinlock_t	page_table_lock; /* protect iopgd */
	dma_addr_t	pd_dma;

	पूर्णांक		nr_tlb_entries;

	व्योम *ctx; /* iommu context: registres saved area */

	काष्ठा cr_regs *cr_ctx;
	u32 num_cr_ctx;

	पूर्णांक has_bus_err_back;
	u32 id;

	काष्ठा iommu_device iommu;
	काष्ठा iommu_group *group;

	u8 pwrst;
पूर्ण;

/**
 * काष्ठा omap_iommu_arch_data - omap iommu निजी data
 * @iommu_dev: handle of the OMAP iommu device
 * @dev: handle of the iommu device
 *
 * This is an omap iommu निजी data object, which binds an iommu user
 * to its iommu device. This object should be placed at the iommu user's
 * dev_archdata so generic IOMMU API can be used without having to
 * utilize omap-specअगरic plumbing anymore.
 */
काष्ठा omap_iommu_arch_data अणु
	काष्ठा omap_iommu *iommu_dev;
	काष्ठा device *dev;
पूर्ण;

काष्ठा cr_regs अणु
	u32 cam;
	u32 ram;
पूर्ण;

काष्ठा iotlb_lock अणु
	लघु base;
	लघु vict;
पूर्ण;

/*
 * MMU Register offsets
 */
#घोषणा MMU_REVISION		0x00
#घोषणा MMU_IRQSTATUS		0x18
#घोषणा MMU_IRQENABLE		0x1c
#घोषणा MMU_WALKING_ST		0x40
#घोषणा MMU_CNTL		0x44
#घोषणा MMU_FAULT_AD		0x48
#घोषणा MMU_TTB			0x4c
#घोषणा MMU_LOCK		0x50
#घोषणा MMU_LD_TLB		0x54
#घोषणा MMU_CAM			0x58
#घोषणा MMU_RAM			0x5c
#घोषणा MMU_GFLUSH		0x60
#घोषणा MMU_FLUSH_ENTRY		0x64
#घोषणा MMU_READ_CAM		0x68
#घोषणा MMU_READ_RAM		0x6c
#घोषणा MMU_EMU_FAULT_AD	0x70
#घोषणा MMU_GP_REG		0x88

#घोषणा MMU_REG_SIZE		256

/*
 * MMU Register bit definitions
 */
/* IRQSTATUS & IRQENABLE */
#घोषणा MMU_IRQ_MULTIHITFAULT	BIT(4)
#घोषणा MMU_IRQ_TABLEWALKFAULT	BIT(3)
#घोषणा MMU_IRQ_EMUMISS		BIT(2)
#घोषणा MMU_IRQ_TRANSLATIONFAULT	BIT(1)
#घोषणा MMU_IRQ_TLBMISS		BIT(0)

#घोषणा __MMU_IRQ_FAULT		\
	(MMU_IRQ_MULTIHITFAULT | MMU_IRQ_EMUMISS | MMU_IRQ_TRANSLATIONFAULT)
#घोषणा MMU_IRQ_MASK		\
	(__MMU_IRQ_FAULT | MMU_IRQ_TABLEWALKFAULT | MMU_IRQ_TLBMISS)
#घोषणा MMU_IRQ_TWL_MASK	(__MMU_IRQ_FAULT | MMU_IRQ_TABLEWALKFAULT)
#घोषणा MMU_IRQ_TLB_MISS_MASK	(__MMU_IRQ_FAULT | MMU_IRQ_TLBMISS)

/* MMU_CNTL */
#घोषणा MMU_CNTL_SHIFT		1
#घोषणा MMU_CNTL_MASK		(7 << MMU_CNTL_SHIFT)
#घोषणा MMU_CNTL_EML_TLB	BIT(3)
#घोषणा MMU_CNTL_TWL_EN		BIT(2)
#घोषणा MMU_CNTL_MMU_EN		BIT(1)

/* CAM */
#घोषणा MMU_CAM_VATAG_SHIFT	12
#घोषणा MMU_CAM_VATAG_MASK \
	((~0UL >> MMU_CAM_VATAG_SHIFT) << MMU_CAM_VATAG_SHIFT)
#घोषणा MMU_CAM_P		BIT(3)
#घोषणा MMU_CAM_V		BIT(2)
#घोषणा MMU_CAM_PGSZ_MASK	3
#घोषणा MMU_CAM_PGSZ_1M		(0 << 0)
#घोषणा MMU_CAM_PGSZ_64K	(1 << 0)
#घोषणा MMU_CAM_PGSZ_4K		(2 << 0)
#घोषणा MMU_CAM_PGSZ_16M	(3 << 0)

/* RAM */
#घोषणा MMU_RAM_PADDR_SHIFT	12
#घोषणा MMU_RAM_PADDR_MASK \
	((~0UL >> MMU_RAM_PADDR_SHIFT) << MMU_RAM_PADDR_SHIFT)

#घोषणा MMU_RAM_ENDIAN_SHIFT	9
#घोषणा MMU_RAM_ENDIAN_MASK	BIT(MMU_RAM_ENDIAN_SHIFT)
#घोषणा MMU_RAM_ENDIAN_LITTLE	(0 << MMU_RAM_ENDIAN_SHIFT)
#घोषणा MMU_RAM_ENDIAN_BIG	BIT(MMU_RAM_ENDIAN_SHIFT)

#घोषणा MMU_RAM_ELSZ_SHIFT	7
#घोषणा MMU_RAM_ELSZ_MASK	(3 << MMU_RAM_ELSZ_SHIFT)
#घोषणा MMU_RAM_ELSZ_8		(0 << MMU_RAM_ELSZ_SHIFT)
#घोषणा MMU_RAM_ELSZ_16		(1 << MMU_RAM_ELSZ_SHIFT)
#घोषणा MMU_RAM_ELSZ_32		(2 << MMU_RAM_ELSZ_SHIFT)
#घोषणा MMU_RAM_ELSZ_NONE	(3 << MMU_RAM_ELSZ_SHIFT)
#घोषणा MMU_RAM_MIXED_SHIFT	6
#घोषणा MMU_RAM_MIXED_MASK	BIT(MMU_RAM_MIXED_SHIFT)
#घोषणा MMU_RAM_MIXED		MMU_RAM_MIXED_MASK

#घोषणा MMU_GP_REG_BUS_ERR_BACK_EN	0x1

#घोषणा get_cam_va_mask(pgsz)				\
	(((pgsz) == MMU_CAM_PGSZ_16M) ? 0xff000000 :	\
	 ((pgsz) == MMU_CAM_PGSZ_1M)  ? 0xfff00000 :	\
	 ((pgsz) == MMU_CAM_PGSZ_64K) ? 0xffff0000 :	\
	 ((pgsz) == MMU_CAM_PGSZ_4K)  ? 0xfffff000 : 0)

/*
 * DSP_SYSTEM रेजिस्टरs and bit definitions (applicable only क्रम DRA7xx DSP)
 */
#घोषणा DSP_SYS_REVISION		0x00
#घोषणा DSP_SYS_MMU_CONFIG		0x18
#घोषणा DSP_SYS_MMU_CONFIG_EN_SHIFT	4

/*
 * utilities क्रम super page(16MB, 1MB, 64KB and 4KB)
 */

#घोषणा iopgsz_max(bytes)			\
	(((bytes) >= SZ_16M) ? SZ_16M :		\
	 ((bytes) >= SZ_1M)  ? SZ_1M  :		\
	 ((bytes) >= SZ_64K) ? SZ_64K :		\
	 ((bytes) >= SZ_4K)  ? SZ_4K  :	0)

#घोषणा bytes_to_iopgsz(bytes)				\
	(((bytes) == SZ_16M) ? MMU_CAM_PGSZ_16M :	\
	 ((bytes) == SZ_1M)  ? MMU_CAM_PGSZ_1M  :	\
	 ((bytes) == SZ_64K) ? MMU_CAM_PGSZ_64K :	\
	 ((bytes) == SZ_4K)  ? MMU_CAM_PGSZ_4K  : -1)

#घोषणा iopgsz_to_bytes(iopgsz)				\
	(((iopgsz) == MMU_CAM_PGSZ_16M)	? SZ_16M :	\
	 ((iopgsz) == MMU_CAM_PGSZ_1M)	? SZ_1M  :	\
	 ((iopgsz) == MMU_CAM_PGSZ_64K)	? SZ_64K :	\
	 ((iopgsz) == MMU_CAM_PGSZ_4K)	? SZ_4K  : 0)

#घोषणा iopgsz_ok(bytes) (bytes_to_iopgsz(bytes) >= 0)

/*
 * global functions
 */

काष्ठा cr_regs __iotlb_पढ़ो_cr(काष्ठा omap_iommu *obj, पूर्णांक n);
व्योम iotlb_lock_get(काष्ठा omap_iommu *obj, काष्ठा iotlb_lock *l);
व्योम iotlb_lock_set(काष्ठा omap_iommu *obj, काष्ठा iotlb_lock *l);

#अगर_घोषित CONFIG_OMAP_IOMMU_DEBUG
व्योम omap_iommu_debugfs_init(व्योम);
व्योम omap_iommu_debugfs_निकास(व्योम);

व्योम omap_iommu_debugfs_add(काष्ठा omap_iommu *obj);
व्योम omap_iommu_debugfs_हटाओ(काष्ठा omap_iommu *obj);
#अन्यथा
अटल अंतरभूत व्योम omap_iommu_debugfs_init(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम omap_iommu_debugfs_निकास(व्योम) अणु पूर्ण

अटल अंतरभूत व्योम omap_iommu_debugfs_add(काष्ठा omap_iommu *obj) अणु पूर्ण
अटल अंतरभूत व्योम omap_iommu_debugfs_हटाओ(काष्ठा omap_iommu *obj) अणु पूर्ण
#पूर्ण_अगर

/*
 * रेजिस्टर accessors
 */
अटल अंतरभूत u32 iommu_पढ़ो_reg(काष्ठा omap_iommu *obj, माप_प्रकार offs)
अणु
	वापस __raw_पढ़ोl(obj->regbase + offs);
पूर्ण

अटल अंतरभूत व्योम iommu_ग_लिखो_reg(काष्ठा omap_iommu *obj, u32 val, माप_प्रकार offs)
अणु
	__raw_ग_लिखोl(val, obj->regbase + offs);
पूर्ण

अटल अंतरभूत पूर्णांक iotlb_cr_valid(काष्ठा cr_regs *cr)
अणु
	अगर (!cr)
		वापस -EINVAL;

	वापस cr->cam & MMU_CAM_V;
पूर्ण

#पूर्ण_अगर /* _OMAP_IOMMU_H */
