<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2011,2016 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 */

#अगर_घोषित CONFIG_EXYNOS_IOMMU_DEBUG
#घोषणा DEBUG
#पूर्ण_अगर

#समावेश <linux/clk.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/iommu.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kmemleak.h>
#समावेश <linux/list.h>
#समावेश <linux/of.h>
#समावेश <linux/of_iommu.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>
#समावेश <linux/dma-iommu.h>

प्रकार u32 sysmmu_iova_t;
प्रकार u32 sysmmu_pte_t;

/* We करो not consider super section mapping (16MB) */
#घोषणा SECT_ORDER 20
#घोषणा LPAGE_ORDER 16
#घोषणा SPAGE_ORDER 12

#घोषणा SECT_SIZE (1 << SECT_ORDER)
#घोषणा LPAGE_SIZE (1 << LPAGE_ORDER)
#घोषणा SPAGE_SIZE (1 << SPAGE_ORDER)

#घोषणा SECT_MASK (~(SECT_SIZE - 1))
#घोषणा LPAGE_MASK (~(LPAGE_SIZE - 1))
#घोषणा SPAGE_MASK (~(SPAGE_SIZE - 1))

#घोषणा lv1ent_fault(sent) ((*(sent) == ZERO_LV2LINK) || \
			   ((*(sent) & 3) == 0) || ((*(sent) & 3) == 3))
#घोषणा lv1ent_zero(sent) (*(sent) == ZERO_LV2LINK)
#घोषणा lv1ent_page_zero(sent) ((*(sent) & 3) == 1)
#घोषणा lv1ent_page(sent) ((*(sent) != ZERO_LV2LINK) && \
			  ((*(sent) & 3) == 1))
#घोषणा lv1ent_section(sent) ((*(sent) & 3) == 2)

#घोषणा lv2ent_fault(pent) ((*(pent) & 3) == 0)
#घोषणा lv2ent_small(pent) ((*(pent) & 2) == 2)
#घोषणा lv2ent_large(pent) ((*(pent) & 3) == 1)

/*
 * v1.x - v3.x SYSMMU supports 32bit physical and 32bit भव address spaces
 * v5.0 पूर्णांकroduced support क्रम 36bit physical address space by shअगरting
 * all page entry values by 4 bits.
 * All SYSMMU controllers in the प्रणाली support the address spaces of the same
 * size, so PG_ENT_SHIFT can be initialized on first SYSMMU probe to proper
 * value (0 or 4).
 */
अटल लघु PG_ENT_SHIFT = -1;
#घोषणा SYSMMU_PG_ENT_SHIFT 0
#घोषणा SYSMMU_V5_PG_ENT_SHIFT 4

अटल स्थिर sysmmu_pte_t *LV1_PROT;
अटल स्थिर sysmmu_pte_t SYSMMU_LV1_PROT[] = अणु
	((0 << 15) | (0 << 10)), /* no access */
	((1 << 15) | (1 << 10)), /* IOMMU_READ only */
	((0 << 15) | (1 << 10)), /* IOMMU_WRITE not supported, use पढ़ो/ग_लिखो */
	((0 << 15) | (1 << 10)), /* IOMMU_READ | IOMMU_WRITE */
पूर्ण;
अटल स्थिर sysmmu_pte_t SYSMMU_V5_LV1_PROT[] = अणु
	(0 << 4), /* no access */
	(1 << 4), /* IOMMU_READ only */
	(2 << 4), /* IOMMU_WRITE only */
	(3 << 4), /* IOMMU_READ | IOMMU_WRITE */
पूर्ण;

अटल स्थिर sysmmu_pte_t *LV2_PROT;
अटल स्थिर sysmmu_pte_t SYSMMU_LV2_PROT[] = अणु
	((0 << 9) | (0 << 4)), /* no access */
	((1 << 9) | (1 << 4)), /* IOMMU_READ only */
	((0 << 9) | (1 << 4)), /* IOMMU_WRITE not supported, use पढ़ो/ग_लिखो */
	((0 << 9) | (1 << 4)), /* IOMMU_READ | IOMMU_WRITE */
पूर्ण;
अटल स्थिर sysmmu_pte_t SYSMMU_V5_LV2_PROT[] = अणु
	(0 << 2), /* no access */
	(1 << 2), /* IOMMU_READ only */
	(2 << 2), /* IOMMU_WRITE only */
	(3 << 2), /* IOMMU_READ | IOMMU_WRITE */
पूर्ण;

#घोषणा SYSMMU_SUPPORTED_PROT_BITS (IOMMU_READ | IOMMU_WRITE)

#घोषणा sect_to_phys(ent) (((phys_addr_t) ent) << PG_ENT_SHIFT)
#घोषणा section_phys(sent) (sect_to_phys(*(sent)) & SECT_MASK)
#घोषणा section_offs(iova) (iova & (SECT_SIZE - 1))
#घोषणा lpage_phys(pent) (sect_to_phys(*(pent)) & LPAGE_MASK)
#घोषणा lpage_offs(iova) (iova & (LPAGE_SIZE - 1))
#घोषणा spage_phys(pent) (sect_to_phys(*(pent)) & SPAGE_MASK)
#घोषणा spage_offs(iova) (iova & (SPAGE_SIZE - 1))

#घोषणा NUM_LV1ENTRIES 4096
#घोषणा NUM_LV2ENTRIES (SECT_SIZE / SPAGE_SIZE)

अटल u32 lv1ent_offset(sysmmu_iova_t iova)
अणु
	वापस iova >> SECT_ORDER;
पूर्ण

अटल u32 lv2ent_offset(sysmmu_iova_t iova)
अणु
	वापस (iova >> SPAGE_ORDER) & (NUM_LV2ENTRIES - 1);
पूर्ण

#घोषणा LV1TABLE_SIZE (NUM_LV1ENTRIES * माप(sysmmu_pte_t))
#घोषणा LV2TABLE_SIZE (NUM_LV2ENTRIES * माप(sysmmu_pte_t))

#घोषणा SPAGES_PER_LPAGE (LPAGE_SIZE / SPAGE_SIZE)
#घोषणा lv2table_base(sent) (sect_to_phys(*(sent) & 0xFFFFFFC0))

#घोषणा mk_lv1ent_sect(pa, prot) ((pa >> PG_ENT_SHIFT) | LV1_PROT[prot] | 2)
#घोषणा mk_lv1ent_page(pa) ((pa >> PG_ENT_SHIFT) | 1)
#घोषणा mk_lv2ent_lpage(pa, prot) ((pa >> PG_ENT_SHIFT) | LV2_PROT[prot] | 1)
#घोषणा mk_lv2ent_spage(pa, prot) ((pa >> PG_ENT_SHIFT) | LV2_PROT[prot] | 2)

#घोषणा CTRL_ENABLE	0x5
#घोषणा CTRL_BLOCK	0x7
#घोषणा CTRL_DISABLE	0x0

#घोषणा CFG_LRU		0x1
#घोषणा CFG_EAP		(1 << 2)
#घोषणा CFG_QOS(n)	((n & 0xF) << 7)
#घोषणा CFG_ACGEN	(1 << 24) /* System MMU 3.3 only */
#घोषणा CFG_SYSSEL	(1 << 22) /* System MMU 3.2 only */
#घोषणा CFG_FLPDCACHE	(1 << 20) /* System MMU 3.2+ only */

/* common रेजिस्टरs */
#घोषणा REG_MMU_CTRL		0x000
#घोषणा REG_MMU_CFG		0x004
#घोषणा REG_MMU_STATUS		0x008
#घोषणा REG_MMU_VERSION		0x034

#घोषणा MMU_MAJ_VER(val)	((val) >> 7)
#घोषणा MMU_MIN_VER(val)	((val) & 0x7F)
#घोषणा MMU_RAW_VER(reg)	(((reg) >> 21) & ((1 << 11) - 1)) /* 11 bits */

#घोषणा MAKE_MMU_VER(maj, min)	((((maj) & 0xF) << 7) | ((min) & 0x7F))

/* v1.x - v3.x रेजिस्टरs */
#घोषणा REG_MMU_FLUSH		0x00C
#घोषणा REG_MMU_FLUSH_ENTRY	0x010
#घोषणा REG_PT_BASE_ADDR	0x014
#घोषणा REG_INT_STATUS		0x018
#घोषणा REG_INT_CLEAR		0x01C

#घोषणा REG_PAGE_FAULT_ADDR	0x024
#घोषणा REG_AW_FAULT_ADDR	0x028
#घोषणा REG_AR_FAULT_ADDR	0x02C
#घोषणा REG_DEFAULT_SLAVE_ADDR	0x030

/* v5.x रेजिस्टरs */
#घोषणा REG_V5_PT_BASE_PFN	0x00C
#घोषणा REG_V5_MMU_FLUSH_ALL	0x010
#घोषणा REG_V5_MMU_FLUSH_ENTRY	0x014
#घोषणा REG_V5_MMU_FLUSH_RANGE	0x018
#घोषणा REG_V5_MMU_FLUSH_START	0x020
#घोषणा REG_V5_MMU_FLUSH_END	0x024
#घोषणा REG_V5_INT_STATUS	0x060
#घोषणा REG_V5_INT_CLEAR	0x064
#घोषणा REG_V5_FAULT_AR_VA	0x070
#घोषणा REG_V5_FAULT_AW_VA	0x080

#घोषणा has_sysmmu(dev)		(dev_iommu_priv_get(dev) != शून्य)

अटल काष्ठा device *dma_dev;
अटल काष्ठा kmem_cache *lv2table_kmem_cache;
अटल sysmmu_pte_t *zero_lv2_table;
#घोषणा ZERO_LV2LINK mk_lv1ent_page(virt_to_phys(zero_lv2_table))

अटल sysmmu_pte_t *section_entry(sysmmu_pte_t *pgtable, sysmmu_iova_t iova)
अणु
	वापस pgtable + lv1ent_offset(iova);
पूर्ण

अटल sysmmu_pte_t *page_entry(sysmmu_pte_t *sent, sysmmu_iova_t iova)
अणु
	वापस (sysmmu_pte_t *)phys_to_virt(
				lv2table_base(sent)) + lv2ent_offset(iova);
पूर्ण

/*
 * IOMMU fault inक्रमmation रेजिस्टर
 */
काष्ठा sysmmu_fault_info अणु
	अचिन्हित पूर्णांक bit;	/* bit number in STATUS रेजिस्टर */
	अचिन्हित लघु addr_reg; /* रेजिस्टर to पढ़ो VA fault address */
	स्थिर अक्षर *name;	/* human पढ़ोable fault name */
	अचिन्हित पूर्णांक type;	/* fault type क्रम report_iommu_fault */
पूर्ण;

अटल स्थिर काष्ठा sysmmu_fault_info sysmmu_faults[] = अणु
	अणु 0, REG_PAGE_FAULT_ADDR, "PAGE", IOMMU_FAULT_READ पूर्ण,
	अणु 1, REG_AR_FAULT_ADDR, "AR MULTI-HIT", IOMMU_FAULT_READ पूर्ण,
	अणु 2, REG_AW_FAULT_ADDR, "AW MULTI-HIT", IOMMU_FAULT_WRITE पूर्ण,
	अणु 3, REG_DEFAULT_SLAVE_ADDR, "BUS ERROR", IOMMU_FAULT_READ पूर्ण,
	अणु 4, REG_AR_FAULT_ADDR, "AR SECURITY PROTECTION", IOMMU_FAULT_READ पूर्ण,
	अणु 5, REG_AR_FAULT_ADDR, "AR ACCESS PROTECTION", IOMMU_FAULT_READ पूर्ण,
	अणु 6, REG_AW_FAULT_ADDR, "AW SECURITY PROTECTION", IOMMU_FAULT_WRITE पूर्ण,
	अणु 7, REG_AW_FAULT_ADDR, "AW ACCESS PROTECTION", IOMMU_FAULT_WRITE पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा sysmmu_fault_info sysmmu_v5_faults[] = अणु
	अणु 0, REG_V5_FAULT_AR_VA, "AR PTW", IOMMU_FAULT_READ पूर्ण,
	अणु 1, REG_V5_FAULT_AR_VA, "AR PAGE", IOMMU_FAULT_READ पूर्ण,
	अणु 2, REG_V5_FAULT_AR_VA, "AR MULTI-HIT", IOMMU_FAULT_READ पूर्ण,
	अणु 3, REG_V5_FAULT_AR_VA, "AR ACCESS PROTECTION", IOMMU_FAULT_READ पूर्ण,
	अणु 4, REG_V5_FAULT_AR_VA, "AR SECURITY PROTECTION", IOMMU_FAULT_READ पूर्ण,
	अणु 16, REG_V5_FAULT_AW_VA, "AW PTW", IOMMU_FAULT_WRITE पूर्ण,
	अणु 17, REG_V5_FAULT_AW_VA, "AW PAGE", IOMMU_FAULT_WRITE पूर्ण,
	अणु 18, REG_V5_FAULT_AW_VA, "AW MULTI-HIT", IOMMU_FAULT_WRITE पूर्ण,
	अणु 19, REG_V5_FAULT_AW_VA, "AW ACCESS PROTECTION", IOMMU_FAULT_WRITE पूर्ण,
	अणु 20, REG_V5_FAULT_AW_VA, "AW SECURITY PROTECTION", IOMMU_FAULT_WRITE पूर्ण,
पूर्ण;

/*
 * This काष्ठाure is attached to dev->iommu->priv of the master device
 * on device add, contains a list of SYSMMU controllers defined by device tree,
 * which are bound to given master device. It is usually referenced by 'owner'
 * poपूर्णांकer.
*/
काष्ठा exynos_iommu_owner अणु
	काष्ठा list_head controllers;	/* list of sysmmu_drvdata.owner_node */
	काष्ठा iommu_करोमुख्य *करोमुख्य;	/* करोमुख्य this device is attached */
	काष्ठा mutex rpm_lock;		/* क्रम runसमय pm of all sysmmus */
पूर्ण;

/*
 * This काष्ठाure exynos specअगरic generalization of काष्ठा iommu_करोमुख्य.
 * It contains list of SYSMMU controllers from all master devices, which has
 * been attached to this करोमुख्य and page tables of IO address space defined by
 * it. It is usually referenced by 'domain' poपूर्णांकer.
 */
काष्ठा exynos_iommu_करोमुख्य अणु
	काष्ठा list_head clients; /* list of sysmmu_drvdata.करोमुख्य_node */
	sysmmu_pte_t *pgtable;	/* lv1 page table, 16KB */
	लघु *lv2entcnt;	/* मुक्त lv2 entry counter क्रम each section */
	spinlock_t lock;	/* lock क्रम modyfying list of clients */
	spinlock_t pgtablelock;	/* lock क्रम modअगरying page table @ pgtable */
	काष्ठा iommu_करोमुख्य करोमुख्य; /* generic करोमुख्य data काष्ठाure */
पूर्ण;

/*
 * This काष्ठाure hold all data of a single SYSMMU controller, this includes
 * hw resources like रेजिस्टरs and घड़ीs, poपूर्णांकers and list nodes to connect
 * it to all other काष्ठाures, पूर्णांकernal state and parameters पढ़ो from device
 * tree. It is usually referenced by 'data' poपूर्णांकer.
 */
काष्ठा sysmmu_drvdata अणु
	काष्ठा device *sysmmu;		/* SYSMMU controller device */
	काष्ठा device *master;		/* master device (owner) */
	काष्ठा device_link *link;	/* runसमय PM link to master */
	व्योम __iomem *sfrbase;		/* our रेजिस्टरs */
	काष्ठा clk *clk;		/* SYSMMU's घड़ी */
	काष्ठा clk *aclk;		/* SYSMMU's aclk घड़ी */
	काष्ठा clk *pclk;		/* SYSMMU's pclk घड़ी */
	काष्ठा clk *clk_master;		/* master's device घड़ी */
	spinlock_t lock;		/* lock क्रम modyfying state */
	bool active;			/* current status */
	काष्ठा exynos_iommu_करोमुख्य *करोमुख्य; /* करोमुख्य we beदीर्घ to */
	काष्ठा list_head करोमुख्य_node;	/* node क्रम करोमुख्य clients list */
	काष्ठा list_head owner_node;	/* node क्रम owner controllers list */
	phys_addr_t pgtable;		/* asचिन्हित page table काष्ठाure */
	अचिन्हित पूर्णांक version;		/* our version */

	काष्ठा iommu_device iommu;	/* IOMMU core handle */
पूर्ण;

अटल काष्ठा exynos_iommu_करोमुख्य *to_exynos_करोमुख्य(काष्ठा iommu_करोमुख्य *करोm)
अणु
	वापस container_of(करोm, काष्ठा exynos_iommu_करोमुख्य, करोमुख्य);
पूर्ण

अटल व्योम sysmmu_unblock(काष्ठा sysmmu_drvdata *data)
अणु
	ग_लिखोl(CTRL_ENABLE, data->sfrbase + REG_MMU_CTRL);
पूर्ण

अटल bool sysmmu_block(काष्ठा sysmmu_drvdata *data)
अणु
	पूर्णांक i = 120;

	ग_लिखोl(CTRL_BLOCK, data->sfrbase + REG_MMU_CTRL);
	जबतक ((i > 0) && !(पढ़ोl(data->sfrbase + REG_MMU_STATUS) & 1))
		--i;

	अगर (!(पढ़ोl(data->sfrbase + REG_MMU_STATUS) & 1)) अणु
		sysmmu_unblock(data);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम __sysmmu_tlb_invalidate(काष्ठा sysmmu_drvdata *data)
अणु
	अगर (MMU_MAJ_VER(data->version) < 5)
		ग_लिखोl(0x1, data->sfrbase + REG_MMU_FLUSH);
	अन्यथा
		ग_लिखोl(0x1, data->sfrbase + REG_V5_MMU_FLUSH_ALL);
पूर्ण

अटल व्योम __sysmmu_tlb_invalidate_entry(काष्ठा sysmmu_drvdata *data,
				sysmmu_iova_t iova, अचिन्हित पूर्णांक num_inv)
अणु
	अचिन्हित पूर्णांक i;

	अगर (MMU_MAJ_VER(data->version) < 5) अणु
		क्रम (i = 0; i < num_inv; i++) अणु
			ग_लिखोl((iova & SPAGE_MASK) | 1,
				     data->sfrbase + REG_MMU_FLUSH_ENTRY);
			iova += SPAGE_SIZE;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (num_inv == 1) अणु
			ग_लिखोl((iova & SPAGE_MASK) | 1,
				     data->sfrbase + REG_V5_MMU_FLUSH_ENTRY);
		पूर्ण अन्यथा अणु
			ग_लिखोl((iova & SPAGE_MASK),
				     data->sfrbase + REG_V5_MMU_FLUSH_START);
			ग_लिखोl((iova & SPAGE_MASK) + (num_inv - 1) * SPAGE_SIZE,
				     data->sfrbase + REG_V5_MMU_FLUSH_END);
			ग_लिखोl(1, data->sfrbase + REG_V5_MMU_FLUSH_RANGE);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम __sysmmu_set_ptbase(काष्ठा sysmmu_drvdata *data, phys_addr_t pgd)
अणु
	अगर (MMU_MAJ_VER(data->version) < 5)
		ग_लिखोl(pgd, data->sfrbase + REG_PT_BASE_ADDR);
	अन्यथा
		ग_लिखोl(pgd >> PAGE_SHIFT,
			     data->sfrbase + REG_V5_PT_BASE_PFN);

	__sysmmu_tlb_invalidate(data);
पूर्ण

अटल व्योम __sysmmu_enable_घड़ीs(काष्ठा sysmmu_drvdata *data)
अणु
	BUG_ON(clk_prepare_enable(data->clk_master));
	BUG_ON(clk_prepare_enable(data->clk));
	BUG_ON(clk_prepare_enable(data->pclk));
	BUG_ON(clk_prepare_enable(data->aclk));
पूर्ण

अटल व्योम __sysmmu_disable_घड़ीs(काष्ठा sysmmu_drvdata *data)
अणु
	clk_disable_unprepare(data->aclk);
	clk_disable_unprepare(data->pclk);
	clk_disable_unprepare(data->clk);
	clk_disable_unprepare(data->clk_master);
पूर्ण

अटल व्योम __sysmmu_get_version(काष्ठा sysmmu_drvdata *data)
अणु
	u32 ver;

	__sysmmu_enable_घड़ीs(data);

	ver = पढ़ोl(data->sfrbase + REG_MMU_VERSION);

	/* controllers on some SoCs करोn't report proper version */
	अगर (ver == 0x80000001u)
		data->version = MAKE_MMU_VER(1, 0);
	अन्यथा
		data->version = MMU_RAW_VER(ver);

	dev_dbg(data->sysmmu, "hardware version: %d.%d\n",
		MMU_MAJ_VER(data->version), MMU_MIN_VER(data->version));

	__sysmmu_disable_घड़ीs(data);
पूर्ण

अटल व्योम show_fault_inक्रमmation(काष्ठा sysmmu_drvdata *data,
				   स्थिर काष्ठा sysmmu_fault_info *finfo,
				   sysmmu_iova_t fault_addr)
अणु
	sysmmu_pte_t *ent;

	dev_err(data->sysmmu, "%s: %s FAULT occurred at %#x\n",
		dev_name(data->master), finfo->name, fault_addr);
	dev_dbg(data->sysmmu, "Page table base: %pa\n", &data->pgtable);
	ent = section_entry(phys_to_virt(data->pgtable), fault_addr);
	dev_dbg(data->sysmmu, "\tLv1 entry: %#x\n", *ent);
	अगर (lv1ent_page(ent)) अणु
		ent = page_entry(ent, fault_addr);
		dev_dbg(data->sysmmu, "\t Lv2 entry: %#x\n", *ent);
	पूर्ण
पूर्ण

अटल irqवापस_t exynos_sysmmu_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	/* SYSMMU is in blocked state when पूर्णांकerrupt occurred. */
	काष्ठा sysmmu_drvdata *data = dev_id;
	स्थिर काष्ठा sysmmu_fault_info *finfo;
	अचिन्हित पूर्णांक i, n, itype;
	sysmmu_iova_t fault_addr;
	अचिन्हित लघु reg_status, reg_clear;
	पूर्णांक ret = -ENOSYS;

	WARN_ON(!data->active);

	अगर (MMU_MAJ_VER(data->version) < 5) अणु
		reg_status = REG_INT_STATUS;
		reg_clear = REG_INT_CLEAR;
		finfo = sysmmu_faults;
		n = ARRAY_SIZE(sysmmu_faults);
	पूर्ण अन्यथा अणु
		reg_status = REG_V5_INT_STATUS;
		reg_clear = REG_V5_INT_CLEAR;
		finfo = sysmmu_v5_faults;
		n = ARRAY_SIZE(sysmmu_v5_faults);
	पूर्ण

	spin_lock(&data->lock);

	clk_enable(data->clk_master);

	itype = __ffs(पढ़ोl(data->sfrbase + reg_status));
	क्रम (i = 0; i < n; i++, finfo++)
		अगर (finfo->bit == itype)
			अवरोध;
	/* unknown/unsupported fault */
	BUG_ON(i == n);

	/* prपूर्णांक debug message */
	fault_addr = पढ़ोl(data->sfrbase + finfo->addr_reg);
	show_fault_inक्रमmation(data, finfo, fault_addr);

	अगर (data->करोमुख्य)
		ret = report_iommu_fault(&data->करोमुख्य->करोमुख्य,
					data->master, fault_addr, finfo->type);
	/* fault is not recovered by fault handler */
	BUG_ON(ret != 0);

	ग_लिखोl(1 << itype, data->sfrbase + reg_clear);

	sysmmu_unblock(data);

	clk_disable(data->clk_master);

	spin_unlock(&data->lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम __sysmmu_disable(काष्ठा sysmmu_drvdata *data)
अणु
	अचिन्हित दीर्घ flags;

	clk_enable(data->clk_master);

	spin_lock_irqsave(&data->lock, flags);
	ग_लिखोl(CTRL_DISABLE, data->sfrbase + REG_MMU_CTRL);
	ग_लिखोl(0, data->sfrbase + REG_MMU_CFG);
	data->active = false;
	spin_unlock_irqrestore(&data->lock, flags);

	__sysmmu_disable_घड़ीs(data);
पूर्ण

अटल व्योम __sysmmu_init_config(काष्ठा sysmmu_drvdata *data)
अणु
	अचिन्हित पूर्णांक cfg;

	अगर (data->version <= MAKE_MMU_VER(3, 1))
		cfg = CFG_LRU | CFG_QOS(15);
	अन्यथा अगर (data->version <= MAKE_MMU_VER(3, 2))
		cfg = CFG_LRU | CFG_QOS(15) | CFG_FLPDCACHE | CFG_SYSSEL;
	अन्यथा
		cfg = CFG_QOS(15) | CFG_FLPDCACHE | CFG_ACGEN;

	cfg |= CFG_EAP; /* enable access protection bits check */

	ग_लिखोl(cfg, data->sfrbase + REG_MMU_CFG);
पूर्ण

अटल व्योम __sysmmu_enable(काष्ठा sysmmu_drvdata *data)
अणु
	अचिन्हित दीर्घ flags;

	__sysmmu_enable_घड़ीs(data);

	spin_lock_irqsave(&data->lock, flags);
	ग_लिखोl(CTRL_BLOCK, data->sfrbase + REG_MMU_CTRL);
	__sysmmu_init_config(data);
	__sysmmu_set_ptbase(data, data->pgtable);
	ग_लिखोl(CTRL_ENABLE, data->sfrbase + REG_MMU_CTRL);
	data->active = true;
	spin_unlock_irqrestore(&data->lock, flags);

	/*
	 * SYSMMU driver keeps master's घड़ी enabled only क्रम the लघु
	 * समय, जबतक accessing the रेजिस्टरs. For perक्रमming address
	 * translation during DMA transaction it relies on the client
	 * driver to enable it.
	 */
	clk_disable(data->clk_master);
पूर्ण

अटल व्योम sysmmu_tlb_invalidate_flpdcache(काष्ठा sysmmu_drvdata *data,
					    sysmmu_iova_t iova)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&data->lock, flags);
	अगर (data->active && data->version >= MAKE_MMU_VER(3, 3)) अणु
		clk_enable(data->clk_master);
		अगर (sysmmu_block(data)) अणु
			अगर (data->version >= MAKE_MMU_VER(5, 0))
				__sysmmu_tlb_invalidate(data);
			अन्यथा
				__sysmmu_tlb_invalidate_entry(data, iova, 1);
			sysmmu_unblock(data);
		पूर्ण
		clk_disable(data->clk_master);
	पूर्ण
	spin_unlock_irqrestore(&data->lock, flags);
पूर्ण

अटल व्योम sysmmu_tlb_invalidate_entry(काष्ठा sysmmu_drvdata *data,
					sysmmu_iova_t iova, माप_प्रकार size)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&data->lock, flags);
	अगर (data->active) अणु
		अचिन्हित पूर्णांक num_inv = 1;

		clk_enable(data->clk_master);

		/*
		 * L2TLB invalidation required
		 * 4KB page: 1 invalidation
		 * 64KB page: 16 invalidations
		 * 1MB page: 64 invalidations
		 * because it is set-associative TLB
		 * with 8-way and 64 sets.
		 * 1MB page can be cached in one of all sets.
		 * 64KB page can be one of 16 consecutive sets.
		 */
		अगर (MMU_MAJ_VER(data->version) == 2)
			num_inv = min_t(अचिन्हित पूर्णांक, size / PAGE_SIZE, 64);

		अगर (sysmmu_block(data)) अणु
			__sysmmu_tlb_invalidate_entry(data, iova, num_inv);
			sysmmu_unblock(data);
		पूर्ण
		clk_disable(data->clk_master);
	पूर्ण
	spin_unlock_irqrestore(&data->lock, flags);
पूर्ण

अटल स्थिर काष्ठा iommu_ops exynos_iommu_ops;

अटल पूर्णांक exynos_sysmmu_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक irq, ret;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा sysmmu_drvdata *data;
	काष्ठा resource *res;

	data = devm_kzalloc(dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	data->sfrbase = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(data->sfrbase))
		वापस PTR_ERR(data->sfrbase);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq <= 0)
		वापस irq;

	ret = devm_request_irq(dev, irq, exynos_sysmmu_irq, 0,
				dev_name(dev), data);
	अगर (ret) अणु
		dev_err(dev, "Unabled to register handler of irq %d\n", irq);
		वापस ret;
	पूर्ण

	data->clk = devm_clk_get(dev, "sysmmu");
	अगर (PTR_ERR(data->clk) == -ENOENT)
		data->clk = शून्य;
	अन्यथा अगर (IS_ERR(data->clk))
		वापस PTR_ERR(data->clk);

	data->aclk = devm_clk_get(dev, "aclk");
	अगर (PTR_ERR(data->aclk) == -ENOENT)
		data->aclk = शून्य;
	अन्यथा अगर (IS_ERR(data->aclk))
		वापस PTR_ERR(data->aclk);

	data->pclk = devm_clk_get(dev, "pclk");
	अगर (PTR_ERR(data->pclk) == -ENOENT)
		data->pclk = शून्य;
	अन्यथा अगर (IS_ERR(data->pclk))
		वापस PTR_ERR(data->pclk);

	अगर (!data->clk && (!data->aclk || !data->pclk)) अणु
		dev_err(dev, "Failed to get device clock(s)!\n");
		वापस -ENOSYS;
	पूर्ण

	data->clk_master = devm_clk_get(dev, "master");
	अगर (PTR_ERR(data->clk_master) == -ENOENT)
		data->clk_master = शून्य;
	अन्यथा अगर (IS_ERR(data->clk_master))
		वापस PTR_ERR(data->clk_master);

	data->sysmmu = dev;
	spin_lock_init(&data->lock);

	ret = iommu_device_sysfs_add(&data->iommu, &pdev->dev, शून्य,
				     dev_name(data->sysmmu));
	अगर (ret)
		वापस ret;

	ret = iommu_device_रेजिस्टर(&data->iommu, &exynos_iommu_ops, dev);
	अगर (ret)
		वापस ret;

	platक्रमm_set_drvdata(pdev, data);

	__sysmmu_get_version(data);
	अगर (PG_ENT_SHIFT < 0) अणु
		अगर (MMU_MAJ_VER(data->version) < 5) अणु
			PG_ENT_SHIFT = SYSMMU_PG_ENT_SHIFT;
			LV1_PROT = SYSMMU_LV1_PROT;
			LV2_PROT = SYSMMU_LV2_PROT;
		पूर्ण अन्यथा अणु
			PG_ENT_SHIFT = SYSMMU_V5_PG_ENT_SHIFT;
			LV1_PROT = SYSMMU_V5_LV1_PROT;
			LV2_PROT = SYSMMU_V5_LV2_PROT;
		पूर्ण
	पूर्ण

	/*
	 * use the first रेजिस्टरed sysmmu device क्रम perक्रमming
	 * dma mapping operations on iommu page tables (cpu cache flush)
	 */
	अगर (!dma_dev)
		dma_dev = &pdev->dev;

	pm_runसमय_enable(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused exynos_sysmmu_suspend(काष्ठा device *dev)
अणु
	काष्ठा sysmmu_drvdata *data = dev_get_drvdata(dev);
	काष्ठा device *master = data->master;

	अगर (master) अणु
		काष्ठा exynos_iommu_owner *owner = dev_iommu_priv_get(master);

		mutex_lock(&owner->rpm_lock);
		अगर (data->करोमुख्य) अणु
			dev_dbg(data->sysmmu, "saving state\n");
			__sysmmu_disable(data);
		पूर्ण
		mutex_unlock(&owner->rpm_lock);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused exynos_sysmmu_resume(काष्ठा device *dev)
अणु
	काष्ठा sysmmu_drvdata *data = dev_get_drvdata(dev);
	काष्ठा device *master = data->master;

	अगर (master) अणु
		काष्ठा exynos_iommu_owner *owner = dev_iommu_priv_get(master);

		mutex_lock(&owner->rpm_lock);
		अगर (data->करोमुख्य) अणु
			dev_dbg(data->sysmmu, "restoring state\n");
			__sysmmu_enable(data);
		पूर्ण
		mutex_unlock(&owner->rpm_lock);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops sysmmu_pm_ops = अणु
	SET_RUNTIME_PM_OPS(exynos_sysmmu_suspend, exynos_sysmmu_resume, शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
पूर्ण;

अटल स्थिर काष्ठा of_device_id sysmmu_of_match[] = अणु
	अणु .compatible	= "samsung,exynos-sysmmu", पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver exynos_sysmmu_driver __refdata = अणु
	.probe	= exynos_sysmmu_probe,
	.driver	= अणु
		.name		= "exynos-sysmmu",
		.of_match_table	= sysmmu_of_match,
		.pm		= &sysmmu_pm_ops,
		.suppress_bind_attrs = true,
	पूर्ण
पूर्ण;

अटल अंतरभूत व्योम exynos_iommu_set_pte(sysmmu_pte_t *ent, sysmmu_pte_t val)
अणु
	dma_sync_single_क्रम_cpu(dma_dev, virt_to_phys(ent), माप(*ent),
				DMA_TO_DEVICE);
	*ent = cpu_to_le32(val);
	dma_sync_single_क्रम_device(dma_dev, virt_to_phys(ent), माप(*ent),
				   DMA_TO_DEVICE);
पूर्ण

अटल काष्ठा iommu_करोमुख्य *exynos_iommu_करोमुख्य_alloc(अचिन्हित type)
अणु
	काष्ठा exynos_iommu_करोमुख्य *करोमुख्य;
	dma_addr_t handle;
	पूर्णांक i;

	/* Check अगर correct PTE offsets are initialized */
	BUG_ON(PG_ENT_SHIFT < 0 || !dma_dev);

	करोमुख्य = kzalloc(माप(*करोमुख्य), GFP_KERNEL);
	अगर (!करोमुख्य)
		वापस शून्य;

	अगर (type == IOMMU_DOMAIN_DMA) अणु
		अगर (iommu_get_dma_cookie(&करोमुख्य->करोमुख्य) != 0)
			जाओ err_pgtable;
	पूर्ण अन्यथा अगर (type != IOMMU_DOMAIN_UNMANAGED) अणु
		जाओ err_pgtable;
	पूर्ण

	करोमुख्य->pgtable = (sysmmu_pte_t *)__get_मुक्त_pages(GFP_KERNEL, 2);
	अगर (!करोमुख्य->pgtable)
		जाओ err_dma_cookie;

	करोमुख्य->lv2entcnt = (लघु *)__get_मुक्त_pages(GFP_KERNEL | __GFP_ZERO, 1);
	अगर (!करोमुख्य->lv2entcnt)
		जाओ err_counter;

	/* Workaround क्रम System MMU v3.3 to prevent caching 1MiB mapping */
	क्रम (i = 0; i < NUM_LV1ENTRIES; i++)
		करोमुख्य->pgtable[i] = ZERO_LV2LINK;

	handle = dma_map_single(dma_dev, करोमुख्य->pgtable, LV1TABLE_SIZE,
				DMA_TO_DEVICE);
	/* For mapping page table entries we rely on dma == phys */
	BUG_ON(handle != virt_to_phys(करोमुख्य->pgtable));
	अगर (dma_mapping_error(dma_dev, handle))
		जाओ err_lv2ent;

	spin_lock_init(&करोमुख्य->lock);
	spin_lock_init(&करोमुख्य->pgtablelock);
	INIT_LIST_HEAD(&करोमुख्य->clients);

	करोमुख्य->करोमुख्य.geometry.aperture_start = 0;
	करोमुख्य->करोमुख्य.geometry.aperture_end   = ~0UL;
	करोमुख्य->करोमुख्य.geometry.क्रमce_aperture = true;

	वापस &करोमुख्य->करोमुख्य;

err_lv2ent:
	मुक्त_pages((अचिन्हित दीर्घ)करोमुख्य->lv2entcnt, 1);
err_counter:
	मुक्त_pages((अचिन्हित दीर्घ)करोमुख्य->pgtable, 2);
err_dma_cookie:
	अगर (type == IOMMU_DOMAIN_DMA)
		iommu_put_dma_cookie(&करोमुख्य->करोमुख्य);
err_pgtable:
	kमुक्त(करोमुख्य);
	वापस शून्य;
पूर्ण

अटल व्योम exynos_iommu_करोमुख्य_मुक्त(काष्ठा iommu_करोमुख्य *iommu_करोमुख्य)
अणु
	काष्ठा exynos_iommu_करोमुख्य *करोमुख्य = to_exynos_करोमुख्य(iommu_करोमुख्य);
	काष्ठा sysmmu_drvdata *data, *next;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	WARN_ON(!list_empty(&करोमुख्य->clients));

	spin_lock_irqsave(&करोमुख्य->lock, flags);

	list_क्रम_each_entry_safe(data, next, &करोमुख्य->clients, करोमुख्य_node) अणु
		spin_lock(&data->lock);
		__sysmmu_disable(data);
		data->pgtable = 0;
		data->करोमुख्य = शून्य;
		list_del_init(&data->करोमुख्य_node);
		spin_unlock(&data->lock);
	पूर्ण

	spin_unlock_irqrestore(&करोमुख्य->lock, flags);

	अगर (iommu_करोमुख्य->type == IOMMU_DOMAIN_DMA)
		iommu_put_dma_cookie(iommu_करोमुख्य);

	dma_unmap_single(dma_dev, virt_to_phys(करोमुख्य->pgtable), LV1TABLE_SIZE,
			 DMA_TO_DEVICE);

	क्रम (i = 0; i < NUM_LV1ENTRIES; i++)
		अगर (lv1ent_page(करोमुख्य->pgtable + i)) अणु
			phys_addr_t base = lv2table_base(करोमुख्य->pgtable + i);

			dma_unmap_single(dma_dev, base, LV2TABLE_SIZE,
					 DMA_TO_DEVICE);
			kmem_cache_मुक्त(lv2table_kmem_cache,
					phys_to_virt(base));
		पूर्ण

	मुक्त_pages((अचिन्हित दीर्घ)करोमुख्य->pgtable, 2);
	मुक्त_pages((अचिन्हित दीर्घ)करोमुख्य->lv2entcnt, 1);
	kमुक्त(करोमुख्य);
पूर्ण

अटल व्योम exynos_iommu_detach_device(काष्ठा iommu_करोमुख्य *iommu_करोमुख्य,
				    काष्ठा device *dev)
अणु
	काष्ठा exynos_iommu_करोमुख्य *करोमुख्य = to_exynos_करोमुख्य(iommu_करोमुख्य);
	काष्ठा exynos_iommu_owner *owner = dev_iommu_priv_get(dev);
	phys_addr_t pagetable = virt_to_phys(करोमुख्य->pgtable);
	काष्ठा sysmmu_drvdata *data, *next;
	अचिन्हित दीर्घ flags;

	अगर (!has_sysmmu(dev) || owner->करोमुख्य != iommu_करोमुख्य)
		वापस;

	mutex_lock(&owner->rpm_lock);

	list_क्रम_each_entry(data, &owner->controllers, owner_node) अणु
		pm_runसमय_get_noresume(data->sysmmu);
		अगर (pm_runसमय_active(data->sysmmu))
			__sysmmu_disable(data);
		pm_runसमय_put(data->sysmmu);
	पूर्ण

	spin_lock_irqsave(&करोमुख्य->lock, flags);
	list_क्रम_each_entry_safe(data, next, &करोमुख्य->clients, करोमुख्य_node) अणु
		spin_lock(&data->lock);
		data->pgtable = 0;
		data->करोमुख्य = शून्य;
		list_del_init(&data->करोमुख्य_node);
		spin_unlock(&data->lock);
	पूर्ण
	owner->करोमुख्य = शून्य;
	spin_unlock_irqrestore(&करोमुख्य->lock, flags);

	mutex_unlock(&owner->rpm_lock);

	dev_dbg(dev, "%s: Detached IOMMU with pgtable %pa\n", __func__,
		&pagetable);
पूर्ण

अटल पूर्णांक exynos_iommu_attach_device(काष्ठा iommu_करोमुख्य *iommu_करोमुख्य,
				   काष्ठा device *dev)
अणु
	काष्ठा exynos_iommu_करोमुख्य *करोमुख्य = to_exynos_करोमुख्य(iommu_करोमुख्य);
	काष्ठा exynos_iommu_owner *owner = dev_iommu_priv_get(dev);
	काष्ठा sysmmu_drvdata *data;
	phys_addr_t pagetable = virt_to_phys(करोमुख्य->pgtable);
	अचिन्हित दीर्घ flags;

	अगर (!has_sysmmu(dev))
		वापस -ENODEV;

	अगर (owner->करोमुख्य)
		exynos_iommu_detach_device(owner->करोमुख्य, dev);

	mutex_lock(&owner->rpm_lock);

	spin_lock_irqsave(&करोमुख्य->lock, flags);
	list_क्रम_each_entry(data, &owner->controllers, owner_node) अणु
		spin_lock(&data->lock);
		data->pgtable = pagetable;
		data->करोमुख्य = करोमुख्य;
		list_add_tail(&data->करोमुख्य_node, &करोमुख्य->clients);
		spin_unlock(&data->lock);
	पूर्ण
	owner->करोमुख्य = iommu_करोमुख्य;
	spin_unlock_irqrestore(&करोमुख्य->lock, flags);

	list_क्रम_each_entry(data, &owner->controllers, owner_node) अणु
		pm_runसमय_get_noresume(data->sysmmu);
		अगर (pm_runसमय_active(data->sysmmu))
			__sysmmu_enable(data);
		pm_runसमय_put(data->sysmmu);
	पूर्ण

	mutex_unlock(&owner->rpm_lock);

	dev_dbg(dev, "%s: Attached IOMMU with pgtable %pa\n", __func__,
		&pagetable);

	वापस 0;
पूर्ण

अटल sysmmu_pte_t *alloc_lv2entry(काष्ठा exynos_iommu_करोमुख्य *करोमुख्य,
		sysmmu_pte_t *sent, sysmmu_iova_t iova, लघु *pgcounter)
अणु
	अगर (lv1ent_section(sent)) अणु
		WARN(1, "Trying mapping on %#08x mapped with 1MiB page", iova);
		वापस ERR_PTR(-EADDRINUSE);
	पूर्ण

	अगर (lv1ent_fault(sent)) अणु
		dma_addr_t handle;
		sysmmu_pte_t *pent;
		bool need_flush_flpd_cache = lv1ent_zero(sent);

		pent = kmem_cache_zalloc(lv2table_kmem_cache, GFP_ATOMIC);
		BUG_ON((uपूर्णांकptr_t)pent & (LV2TABLE_SIZE - 1));
		अगर (!pent)
			वापस ERR_PTR(-ENOMEM);

		exynos_iommu_set_pte(sent, mk_lv1ent_page(virt_to_phys(pent)));
		kmemleak_ignore(pent);
		*pgcounter = NUM_LV2ENTRIES;
		handle = dma_map_single(dma_dev, pent, LV2TABLE_SIZE,
					DMA_TO_DEVICE);
		अगर (dma_mapping_error(dma_dev, handle)) अणु
			kmem_cache_मुक्त(lv2table_kmem_cache, pent);
			वापस ERR_PTR(-EADDRINUSE);
		पूर्ण

		/*
		 * If pre-fetched SLPD is a faulty SLPD in zero_l2_table,
		 * FLPD cache may cache the address of zero_l2_table. This
		 * function replaces the zero_l2_table with new L2 page table
		 * to ग_लिखो valid mappings.
		 * Accessing the valid area may cause page fault since FLPD
		 * cache may still cache zero_l2_table क्रम the valid area
		 * instead of new L2 page table that has the mapping
		 * inक्रमmation of the valid area.
		 * Thus any replacement of zero_l2_table with other valid L2
		 * page table must involve FLPD cache invalidation क्रम System
		 * MMU v3.3.
		 * FLPD cache invalidation is perक्रमmed with TLB invalidation
		 * by VPN without blocking. It is safe to invalidate TLB without
		 * blocking because the target address of TLB invalidation is
		 * not currently mapped.
		 */
		अगर (need_flush_flpd_cache) अणु
			काष्ठा sysmmu_drvdata *data;

			spin_lock(&करोमुख्य->lock);
			list_क्रम_each_entry(data, &करोमुख्य->clients, करोमुख्य_node)
				sysmmu_tlb_invalidate_flpdcache(data, iova);
			spin_unlock(&करोमुख्य->lock);
		पूर्ण
	पूर्ण

	वापस page_entry(sent, iova);
पूर्ण

अटल पूर्णांक lv1set_section(काष्ठा exynos_iommu_करोमुख्य *करोमुख्य,
			  sysmmu_pte_t *sent, sysmmu_iova_t iova,
			  phys_addr_t paddr, पूर्णांक prot, लघु *pgcnt)
अणु
	अगर (lv1ent_section(sent)) अणु
		WARN(1, "Trying mapping on 1MiB@%#08x that is mapped",
			iova);
		वापस -EADDRINUSE;
	पूर्ण

	अगर (lv1ent_page(sent)) अणु
		अगर (*pgcnt != NUM_LV2ENTRIES) अणु
			WARN(1, "Trying mapping on 1MiB@%#08x that is mapped",
				iova);
			वापस -EADDRINUSE;
		पूर्ण

		kmem_cache_मुक्त(lv2table_kmem_cache, page_entry(sent, 0));
		*pgcnt = 0;
	पूर्ण

	exynos_iommu_set_pte(sent, mk_lv1ent_sect(paddr, prot));

	spin_lock(&करोमुख्य->lock);
	अगर (lv1ent_page_zero(sent)) अणु
		काष्ठा sysmmu_drvdata *data;
		/*
		 * Flushing FLPD cache in System MMU v3.3 that may cache a FLPD
		 * entry by speculative prefetch of SLPD which has no mapping.
		 */
		list_क्रम_each_entry(data, &करोमुख्य->clients, करोमुख्य_node)
			sysmmu_tlb_invalidate_flpdcache(data, iova);
	पूर्ण
	spin_unlock(&करोमुख्य->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक lv2set_page(sysmmu_pte_t *pent, phys_addr_t paddr, माप_प्रकार size,
		       पूर्णांक prot, लघु *pgcnt)
अणु
	अगर (size == SPAGE_SIZE) अणु
		अगर (WARN_ON(!lv2ent_fault(pent)))
			वापस -EADDRINUSE;

		exynos_iommu_set_pte(pent, mk_lv2ent_spage(paddr, prot));
		*pgcnt -= 1;
	पूर्ण अन्यथा अणु /* size == LPAGE_SIZE */
		पूर्णांक i;
		dma_addr_t pent_base = virt_to_phys(pent);

		dma_sync_single_क्रम_cpu(dma_dev, pent_base,
					माप(*pent) * SPAGES_PER_LPAGE,
					DMA_TO_DEVICE);
		क्रम (i = 0; i < SPAGES_PER_LPAGE; i++, pent++) अणु
			अगर (WARN_ON(!lv2ent_fault(pent))) अणु
				अगर (i > 0)
					स_रखो(pent - i, 0, माप(*pent) * i);
				वापस -EADDRINUSE;
			पूर्ण

			*pent = mk_lv2ent_lpage(paddr, prot);
		पूर्ण
		dma_sync_single_क्रम_device(dma_dev, pent_base,
					   माप(*pent) * SPAGES_PER_LPAGE,
					   DMA_TO_DEVICE);
		*pgcnt -= SPAGES_PER_LPAGE;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * *CAUTION* to the I/O भव memory managers that support exynos-iommu:
 *
 * System MMU v3.x has advanced logic to improve address translation
 * perक्रमmance with caching more page table entries by a page table walk.
 * However, the logic has a bug that जबतक caching faulty page table entries,
 * System MMU reports page fault अगर the cached fault entry is hit even though
 * the fault entry is updated to a valid entry after the entry is cached.
 * To prevent caching faulty page table entries which may be updated to valid
 * entries later, the भव memory manager should care about the workaround
 * क्रम the problem. The following describes the workaround.
 *
 * Any two consecutive I/O भव address regions must have a hole of 128KiB
 * at maximum to prevent misbehavior of System MMU 3.x (workaround क्रम h/w bug).
 *
 * Precisely, any start address of I/O भव region must be aligned with
 * the following sizes क्रम System MMU v3.1 and v3.2.
 * System MMU v3.1: 128KiB
 * System MMU v3.2: 256KiB
 *
 * Because System MMU v3.3 caches page table entries more aggressively, it needs
 * more workarounds.
 * - Any two consecutive I/O भव regions must have a hole of size larger
 *   than or equal to 128KiB.
 * - Start address of an I/O भव region must be aligned by 128KiB.
 */
अटल पूर्णांक exynos_iommu_map(काष्ठा iommu_करोमुख्य *iommu_करोमुख्य,
			    अचिन्हित दीर्घ l_iova, phys_addr_t paddr, माप_प्रकार size,
			    पूर्णांक prot, gfp_t gfp)
अणु
	काष्ठा exynos_iommu_करोमुख्य *करोमुख्य = to_exynos_करोमुख्य(iommu_करोमुख्य);
	sysmmu_pte_t *entry;
	sysmmu_iova_t iova = (sysmmu_iova_t)l_iova;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = -ENOMEM;

	BUG_ON(करोमुख्य->pgtable == शून्य);
	prot &= SYSMMU_SUPPORTED_PROT_BITS;

	spin_lock_irqsave(&करोमुख्य->pgtablelock, flags);

	entry = section_entry(करोमुख्य->pgtable, iova);

	अगर (size == SECT_SIZE) अणु
		ret = lv1set_section(करोमुख्य, entry, iova, paddr, prot,
				     &करोमुख्य->lv2entcnt[lv1ent_offset(iova)]);
	पूर्ण अन्यथा अणु
		sysmmu_pte_t *pent;

		pent = alloc_lv2entry(करोमुख्य, entry, iova,
				      &करोमुख्य->lv2entcnt[lv1ent_offset(iova)]);

		अगर (IS_ERR(pent))
			ret = PTR_ERR(pent);
		अन्यथा
			ret = lv2set_page(pent, paddr, size, prot,
				       &करोमुख्य->lv2entcnt[lv1ent_offset(iova)]);
	पूर्ण

	अगर (ret)
		pr_err("%s: Failed(%d) to map %#zx bytes @ %#x\n",
			__func__, ret, size, iova);

	spin_unlock_irqrestore(&करोमुख्य->pgtablelock, flags);

	वापस ret;
पूर्ण

अटल व्योम exynos_iommu_tlb_invalidate_entry(काष्ठा exynos_iommu_करोमुख्य *करोमुख्य,
					      sysmmu_iova_t iova, माप_प्रकार size)
अणु
	काष्ठा sysmmu_drvdata *data;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&करोमुख्य->lock, flags);

	list_क्रम_each_entry(data, &करोमुख्य->clients, करोमुख्य_node)
		sysmmu_tlb_invalidate_entry(data, iova, size);

	spin_unlock_irqrestore(&करोमुख्य->lock, flags);
पूर्ण

अटल माप_प्रकार exynos_iommu_unmap(काष्ठा iommu_करोमुख्य *iommu_करोमुख्य,
				 अचिन्हित दीर्घ l_iova, माप_प्रकार size,
				 काष्ठा iommu_iotlb_gather *gather)
अणु
	काष्ठा exynos_iommu_करोमुख्य *करोमुख्य = to_exynos_करोमुख्य(iommu_करोमुख्य);
	sysmmu_iova_t iova = (sysmmu_iova_t)l_iova;
	sysmmu_pte_t *ent;
	माप_प्रकार err_pgsize;
	अचिन्हित दीर्घ flags;

	BUG_ON(करोमुख्य->pgtable == शून्य);

	spin_lock_irqsave(&करोमुख्य->pgtablelock, flags);

	ent = section_entry(करोमुख्य->pgtable, iova);

	अगर (lv1ent_section(ent)) अणु
		अगर (WARN_ON(size < SECT_SIZE)) अणु
			err_pgsize = SECT_SIZE;
			जाओ err;
		पूर्ण

		/* workaround क्रम h/w bug in System MMU v3.3 */
		exynos_iommu_set_pte(ent, ZERO_LV2LINK);
		size = SECT_SIZE;
		जाओ करोne;
	पूर्ण

	अगर (unlikely(lv1ent_fault(ent))) अणु
		अगर (size > SECT_SIZE)
			size = SECT_SIZE;
		जाओ करोne;
	पूर्ण

	/* lv1ent_page(sent) == true here */

	ent = page_entry(ent, iova);

	अगर (unlikely(lv2ent_fault(ent))) अणु
		size = SPAGE_SIZE;
		जाओ करोne;
	पूर्ण

	अगर (lv2ent_small(ent)) अणु
		exynos_iommu_set_pte(ent, 0);
		size = SPAGE_SIZE;
		करोमुख्य->lv2entcnt[lv1ent_offset(iova)] += 1;
		जाओ करोne;
	पूर्ण

	/* lv1ent_large(ent) == true here */
	अगर (WARN_ON(size < LPAGE_SIZE)) अणु
		err_pgsize = LPAGE_SIZE;
		जाओ err;
	पूर्ण

	dma_sync_single_क्रम_cpu(dma_dev, virt_to_phys(ent),
				माप(*ent) * SPAGES_PER_LPAGE,
				DMA_TO_DEVICE);
	स_रखो(ent, 0, माप(*ent) * SPAGES_PER_LPAGE);
	dma_sync_single_क्रम_device(dma_dev, virt_to_phys(ent),
				   माप(*ent) * SPAGES_PER_LPAGE,
				   DMA_TO_DEVICE);
	size = LPAGE_SIZE;
	करोमुख्य->lv2entcnt[lv1ent_offset(iova)] += SPAGES_PER_LPAGE;
करोne:
	spin_unlock_irqrestore(&करोमुख्य->pgtablelock, flags);

	exynos_iommu_tlb_invalidate_entry(करोमुख्य, iova, size);

	वापस size;
err:
	spin_unlock_irqrestore(&करोमुख्य->pgtablelock, flags);

	pr_err("%s: Failed: size(%#zx) @ %#x is smaller than page size %#zx\n",
		__func__, size, iova, err_pgsize);

	वापस 0;
पूर्ण

अटल phys_addr_t exynos_iommu_iova_to_phys(काष्ठा iommu_करोमुख्य *iommu_करोमुख्य,
					  dma_addr_t iova)
अणु
	काष्ठा exynos_iommu_करोमुख्य *करोमुख्य = to_exynos_करोमुख्य(iommu_करोमुख्य);
	sysmmu_pte_t *entry;
	अचिन्हित दीर्घ flags;
	phys_addr_t phys = 0;

	spin_lock_irqsave(&करोमुख्य->pgtablelock, flags);

	entry = section_entry(करोमुख्य->pgtable, iova);

	अगर (lv1ent_section(entry)) अणु
		phys = section_phys(entry) + section_offs(iova);
	पूर्ण अन्यथा अगर (lv1ent_page(entry)) अणु
		entry = page_entry(entry, iova);

		अगर (lv2ent_large(entry))
			phys = lpage_phys(entry) + lpage_offs(iova);
		अन्यथा अगर (lv2ent_small(entry))
			phys = spage_phys(entry) + spage_offs(iova);
	पूर्ण

	spin_unlock_irqrestore(&करोमुख्य->pgtablelock, flags);

	वापस phys;
पूर्ण

अटल काष्ठा iommu_device *exynos_iommu_probe_device(काष्ठा device *dev)
अणु
	काष्ठा exynos_iommu_owner *owner = dev_iommu_priv_get(dev);
	काष्ठा sysmmu_drvdata *data;

	अगर (!has_sysmmu(dev))
		वापस ERR_PTR(-ENODEV);

	list_क्रम_each_entry(data, &owner->controllers, owner_node) अणु
		/*
		 * SYSMMU will be runसमय activated via device link
		 * (dependency) to its master device, so there are no
		 * direct calls to pm_runसमय_get/put in this driver.
		 */
		data->link = device_link_add(dev, data->sysmmu,
					     DL_FLAG_STATELESS |
					     DL_FLAG_PM_RUNTIME);
	पूर्ण

	/* There is always at least one entry, see exynos_iommu_of_xlate() */
	data = list_first_entry(&owner->controllers,
				काष्ठा sysmmu_drvdata, owner_node);

	वापस &data->iommu;
पूर्ण

अटल व्योम exynos_iommu_release_device(काष्ठा device *dev)
अणु
	काष्ठा exynos_iommu_owner *owner = dev_iommu_priv_get(dev);
	काष्ठा sysmmu_drvdata *data;

	अगर (!has_sysmmu(dev))
		वापस;

	अगर (owner->करोमुख्य) अणु
		काष्ठा iommu_group *group = iommu_group_get(dev);

		अगर (group) अणु
			WARN_ON(owner->करोमुख्य !=
				iommu_group_शेष_करोमुख्य(group));
			exynos_iommu_detach_device(owner->करोमुख्य, dev);
			iommu_group_put(group);
		पूर्ण
	पूर्ण

	list_क्रम_each_entry(data, &owner->controllers, owner_node)
		device_link_del(data->link);
पूर्ण

अटल पूर्णांक exynos_iommu_of_xlate(काष्ठा device *dev,
				 काष्ठा of_phandle_args *spec)
अणु
	काष्ठा platक्रमm_device *sysmmu = of_find_device_by_node(spec->np);
	काष्ठा exynos_iommu_owner *owner = dev_iommu_priv_get(dev);
	काष्ठा sysmmu_drvdata *data, *entry;

	अगर (!sysmmu)
		वापस -ENODEV;

	data = platक्रमm_get_drvdata(sysmmu);
	अगर (!data) अणु
		put_device(&sysmmu->dev);
		वापस -ENODEV;
	पूर्ण

	अगर (!owner) अणु
		owner = kzalloc(माप(*owner), GFP_KERNEL);
		अगर (!owner) अणु
			put_device(&sysmmu->dev);
			वापस -ENOMEM;
		पूर्ण

		INIT_LIST_HEAD(&owner->controllers);
		mutex_init(&owner->rpm_lock);
		dev_iommu_priv_set(dev, owner);
	पूर्ण

	list_क्रम_each_entry(entry, &owner->controllers, owner_node)
		अगर (entry == data)
			वापस 0;

	list_add_tail(&data->owner_node, &owner->controllers);
	data->master = dev;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iommu_ops exynos_iommu_ops = अणु
	.करोमुख्य_alloc = exynos_iommu_करोमुख्य_alloc,
	.करोमुख्य_मुक्त = exynos_iommu_करोमुख्य_मुक्त,
	.attach_dev = exynos_iommu_attach_device,
	.detach_dev = exynos_iommu_detach_device,
	.map = exynos_iommu_map,
	.unmap = exynos_iommu_unmap,
	.iova_to_phys = exynos_iommu_iova_to_phys,
	.device_group = generic_device_group,
	.probe_device = exynos_iommu_probe_device,
	.release_device = exynos_iommu_release_device,
	.pgsize_biपंचांगap = SECT_SIZE | LPAGE_SIZE | SPAGE_SIZE,
	.of_xlate = exynos_iommu_of_xlate,
पूर्ण;

अटल पूर्णांक __init exynos_iommu_init(व्योम)
अणु
	काष्ठा device_node *np;
	पूर्णांक ret;

	np = of_find_matching_node(शून्य, sysmmu_of_match);
	अगर (!np)
		वापस 0;

	of_node_put(np);

	lv2table_kmem_cache = kmem_cache_create("exynos-iommu-lv2table",
				LV2TABLE_SIZE, LV2TABLE_SIZE, 0, शून्य);
	अगर (!lv2table_kmem_cache) अणु
		pr_err("%s: Failed to create kmem cache\n", __func__);
		वापस -ENOMEM;
	पूर्ण

	ret = platक्रमm_driver_रेजिस्टर(&exynos_sysmmu_driver);
	अगर (ret) अणु
		pr_err("%s: Failed to register driver\n", __func__);
		जाओ err_reg_driver;
	पूर्ण

	zero_lv2_table = kmem_cache_zalloc(lv2table_kmem_cache, GFP_KERNEL);
	अगर (zero_lv2_table == शून्य) अणु
		pr_err("%s: Failed to allocate zero level2 page table\n",
			__func__);
		ret = -ENOMEM;
		जाओ err_zero_lv2;
	पूर्ण

	ret = bus_set_iommu(&platक्रमm_bus_type, &exynos_iommu_ops);
	अगर (ret) अणु
		pr_err("%s: Failed to register exynos-iommu driver.\n",
								__func__);
		जाओ err_set_iommu;
	पूर्ण

	वापस 0;
err_set_iommu:
	kmem_cache_मुक्त(lv2table_kmem_cache, zero_lv2_table);
err_zero_lv2:
	platक्रमm_driver_unरेजिस्टर(&exynos_sysmmu_driver);
err_reg_driver:
	kmem_cache_destroy(lv2table_kmem_cache);
	वापस ret;
पूर्ण
core_initcall(exynos_iommu_init);
