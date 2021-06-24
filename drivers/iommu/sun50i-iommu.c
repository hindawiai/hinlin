<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
// Copyright (C) 2016-2018, Allwinner Technology CO., LTD.
// Copyright (C) 2019-2020, Cerno

#समावेश <linux/bitfield.h>
#समावेश <linux/bug.h>
#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-direction.h>
#समावेश <linux/dma-iommu.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/err.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/iommu.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/ioport.h>
#समावेश <linux/log2.h>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/reset.h>
#समावेश <linux/sizes.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>

#घोषणा IOMMU_RESET_REG			0x010
#घोषणा IOMMU_ENABLE_REG		0x020
#घोषणा IOMMU_ENABLE_ENABLE			BIT(0)

#घोषणा IOMMU_BYPASS_REG		0x030
#घोषणा IOMMU_AUTO_GATING_REG		0x040
#घोषणा IOMMU_AUTO_GATING_ENABLE		BIT(0)

#घोषणा IOMMU_WBUF_CTRL_REG		0x044
#घोषणा IOMMU_OOO_CTRL_REG		0x048
#घोषणा IOMMU_4KB_BDY_PRT_CTRL_REG	0x04c
#घोषणा IOMMU_TTB_REG			0x050
#घोषणा IOMMU_TLB_ENABLE_REG		0x060
#घोषणा IOMMU_TLB_PREFETCH_REG		0x070
#घोषणा IOMMU_TLB_PREFETCH_MASTER_ENABLE(m)	BIT(m)

#घोषणा IOMMU_TLB_FLUSH_REG		0x080
#घोषणा IOMMU_TLB_FLUSH_PTW_CACHE		BIT(17)
#घोषणा IOMMU_TLB_FLUSH_MACRO_TLB		BIT(16)
#घोषणा IOMMU_TLB_FLUSH_MICRO_TLB(i)		(BIT(i) & GENMASK(5, 0))

#घोषणा IOMMU_TLB_IVLD_ADDR_REG		0x090
#घोषणा IOMMU_TLB_IVLD_ADDR_MASK_REG	0x094
#घोषणा IOMMU_TLB_IVLD_ENABLE_REG	0x098
#घोषणा IOMMU_TLB_IVLD_ENABLE_ENABLE		BIT(0)

#घोषणा IOMMU_PC_IVLD_ADDR_REG		0x0a0
#घोषणा IOMMU_PC_IVLD_ENABLE_REG	0x0a8
#घोषणा IOMMU_PC_IVLD_ENABLE_ENABLE		BIT(0)

#घोषणा IOMMU_DM_AUT_CTRL_REG(d)	(0x0b0 + ((d) / 2) * 4)
#घोषणा IOMMU_DM_AUT_CTRL_RD_UNAVAIL(d, m)	(1 << (((d & 1) * 16) + ((m) * 2)))
#घोषणा IOMMU_DM_AUT_CTRL_WR_UNAVAIL(d, m)	(1 << (((d & 1) * 16) + ((m) * 2) + 1))

#घोषणा IOMMU_DM_AUT_OVWT_REG		0x0d0
#घोषणा IOMMU_INT_ENABLE_REG		0x100
#घोषणा IOMMU_INT_CLR_REG		0x104
#घोषणा IOMMU_INT_STA_REG		0x108
#घोषणा IOMMU_INT_ERR_ADDR_REG(i)	(0x110 + (i) * 4)
#घोषणा IOMMU_INT_ERR_ADDR_L1_REG	0x130
#घोषणा IOMMU_INT_ERR_ADDR_L2_REG	0x134
#घोषणा IOMMU_INT_ERR_DATA_REG(i)	(0x150 + (i) * 4)
#घोषणा IOMMU_L1PG_INT_REG		0x0180
#घोषणा IOMMU_L2PG_INT_REG		0x0184

#घोषणा IOMMU_INT_INVALID_L2PG			BIT(17)
#घोषणा IOMMU_INT_INVALID_L1PG			BIT(16)
#घोषणा IOMMU_INT_MASTER_PERMISSION(m)		BIT(m)
#घोषणा IOMMU_INT_MASTER_MASK			(IOMMU_INT_MASTER_PERMISSION(0) | \
						 IOMMU_INT_MASTER_PERMISSION(1) | \
						 IOMMU_INT_MASTER_PERMISSION(2) | \
						 IOMMU_INT_MASTER_PERMISSION(3) | \
						 IOMMU_INT_MASTER_PERMISSION(4) | \
						 IOMMU_INT_MASTER_PERMISSION(5))
#घोषणा IOMMU_INT_MASK				(IOMMU_INT_INVALID_L1PG | \
						 IOMMU_INT_INVALID_L2PG | \
						 IOMMU_INT_MASTER_MASK)

#घोषणा PT_ENTRY_SIZE			माप(u32)

#घोषणा NUM_DT_ENTRIES			4096
#घोषणा DT_SIZE				(NUM_DT_ENTRIES * PT_ENTRY_SIZE)

#घोषणा NUM_PT_ENTRIES			256
#घोषणा PT_SIZE				(NUM_PT_ENTRIES * PT_ENTRY_SIZE)

काष्ठा sun50i_iommu अणु
	काष्ठा iommu_device iommu;

	/* Lock to modअगरy the IOMMU रेजिस्टरs */
	spinlock_t iommu_lock;

	काष्ठा device *dev;
	व्योम __iomem *base;
	काष्ठा reset_control *reset;
	काष्ठा clk *clk;

	काष्ठा iommu_करोमुख्य *करोमुख्य;
	काष्ठा iommu_group *group;
	काष्ठा kmem_cache *pt_pool;
पूर्ण;

काष्ठा sun50i_iommu_करोमुख्य अणु
	काष्ठा iommu_करोमुख्य करोमुख्य;

	/* Number of devices attached to the करोमुख्य */
	refcount_t refcnt;

	/* L1 Page Table */
	u32 *dt;
	dma_addr_t dt_dma;

	काष्ठा sun50i_iommu *iommu;
पूर्ण;

अटल काष्ठा sun50i_iommu_करोमुख्य *to_sun50i_करोमुख्य(काष्ठा iommu_करोमुख्य *करोमुख्य)
अणु
	वापस container_of(करोमुख्य, काष्ठा sun50i_iommu_करोमुख्य, करोमुख्य);
पूर्ण

अटल काष्ठा sun50i_iommu *sun50i_iommu_from_dev(काष्ठा device *dev)
अणु
	वापस dev_iommu_priv_get(dev);
पूर्ण

अटल u32 iommu_पढ़ो(काष्ठा sun50i_iommu *iommu, u32 offset)
अणु
	वापस पढ़ोl(iommu->base + offset);
पूर्ण

अटल व्योम iommu_ग_लिखो(काष्ठा sun50i_iommu *iommu, u32 offset, u32 value)
अणु
	ग_लिखोl(value, iommu->base + offset);
पूर्ण

/*
 * The Allwinner H6 IOMMU uses a 2-level page table.
 *
 * The first level is the usual Directory Table (DT), that consists of
 * 4096 4-bytes Directory Table Entries (DTE), each poपूर्णांकing to a Page
 * Table (PT).
 *
 * Each PT consits of 256 4-bytes Page Table Entries (PTE), each
 * poपूर्णांकing to a 4kB page of physical memory.
 *
 * The IOMMU supports a single DT, poपूर्णांकed by the IOMMU_TTB_REG
 * रेजिस्टर that contains its physical address.
 */

#घोषणा SUN50I_IOVA_DTE_MASK	GENMASK(31, 20)
#घोषणा SUN50I_IOVA_PTE_MASK	GENMASK(19, 12)
#घोषणा SUN50I_IOVA_PAGE_MASK	GENMASK(11, 0)

अटल u32 sun50i_iova_get_dte_index(dma_addr_t iova)
अणु
	वापस FIELD_GET(SUN50I_IOVA_DTE_MASK, iova);
पूर्ण

अटल u32 sun50i_iova_get_pte_index(dma_addr_t iova)
अणु
	वापस FIELD_GET(SUN50I_IOVA_PTE_MASK, iova);
पूर्ण

अटल u32 sun50i_iova_get_page_offset(dma_addr_t iova)
अणु
	वापस FIELD_GET(SUN50I_IOVA_PAGE_MASK, iova);
पूर्ण

/*
 * Each Directory Table Entry has a Page Table address and a valid
 * bit:

 * +---------------------+-----------+-+
 * | PT address          | Reserved  |V|
 * +---------------------+-----------+-+
 *  31:10 - Page Table address
 *   9:2  - Reserved
 *   1:0  - 1 अगर the entry is valid
 */

#घोषणा SUN50I_DTE_PT_ADDRESS_MASK	GENMASK(31, 10)
#घोषणा SUN50I_DTE_PT_ATTRS		GENMASK(1, 0)
#घोषणा SUN50I_DTE_PT_VALID		1

अटल phys_addr_t sun50i_dte_get_pt_address(u32 dte)
अणु
	वापस (phys_addr_t)dte & SUN50I_DTE_PT_ADDRESS_MASK;
पूर्ण

अटल bool sun50i_dte_is_pt_valid(u32 dte)
अणु
	वापस (dte & SUN50I_DTE_PT_ATTRS) == SUN50I_DTE_PT_VALID;
पूर्ण

अटल u32 sun50i_mk_dte(dma_addr_t pt_dma)
अणु
	वापस (pt_dma & SUN50I_DTE_PT_ADDRESS_MASK) | SUN50I_DTE_PT_VALID;
पूर्ण

/*
 * Each PTE has a Page address, an authority index and a valid bit:
 *
 * +----------------+-----+-----+-----+---+-----+
 * | Page address   | Rsv | ACI | Rsv | V | Rsv |
 * +----------------+-----+-----+-----+---+-----+
 *  31:12 - Page address
 *  11:8  - Reserved
 *   7:4  - Authority Control Index
 *   3:2  - Reserved
 *     1  - 1 अगर the entry is valid
 *     0  - Reserved
 *
 * The way permissions work is that the IOMMU has 16 "domains" that
 * can be configured to give each masters either पढ़ो or ग_लिखो
 * permissions through the IOMMU_DM_AUT_CTRL_REG रेजिस्टरs. The करोमुख्य
 * 0 seems like the शेष करोमुख्य, and its permissions in the
 * IOMMU_DM_AUT_CTRL_REG are only पढ़ो-only, so it's not really
 * useful to enक्रमce any particular permission.
 *
 * Each page entry will then have a reference to the करोमुख्य they are
 * affected to, so that we can actually enक्रमce them on a per-page
 * basis.
 *
 * In order to make it work with the IOMMU framework, we will be using
 * 4 dअगरferent करोमुख्यs, starting at 1: RD_WR, RD, WR and NONE
 * depending on the permission we want to enक्रमce. Each करोमुख्य will
 * have each master setup in the same way, since the IOMMU framework
 * करोesn't seem to restrict page access on a per-device basis. And
 * then we will use the relevant करोमुख्य index when generating the page
 * table entry depending on the permissions we want to be enक्रमced.
 */

क्रमागत sun50i_iommu_aci अणु
	SUN50I_IOMMU_ACI_DO_NOT_USE = 0,
	SUN50I_IOMMU_ACI_NONE,
	SUN50I_IOMMU_ACI_RD,
	SUN50I_IOMMU_ACI_WR,
	SUN50I_IOMMU_ACI_RD_WR,
पूर्ण;

#घोषणा SUN50I_PTE_PAGE_ADDRESS_MASK	GENMASK(31, 12)
#घोषणा SUN50I_PTE_ACI_MASK		GENMASK(7, 4)
#घोषणा SUN50I_PTE_PAGE_VALID		BIT(1)

अटल phys_addr_t sun50i_pte_get_page_address(u32 pte)
अणु
	वापस (phys_addr_t)pte & SUN50I_PTE_PAGE_ADDRESS_MASK;
पूर्ण

अटल क्रमागत sun50i_iommu_aci sun50i_get_pte_aci(u32 pte)
अणु
	वापस FIELD_GET(SUN50I_PTE_ACI_MASK, pte);
पूर्ण

अटल bool sun50i_pte_is_page_valid(u32 pte)
अणु
	वापस pte & SUN50I_PTE_PAGE_VALID;
पूर्ण

अटल u32 sun50i_mk_pte(phys_addr_t page, पूर्णांक prot)
अणु
	क्रमागत sun50i_iommu_aci aci;
	u32 flags = 0;

	अगर (prot & (IOMMU_READ | IOMMU_WRITE))
		aci = SUN50I_IOMMU_ACI_RD_WR;
	अन्यथा अगर (prot & IOMMU_READ)
		aci = SUN50I_IOMMU_ACI_RD;
	अन्यथा अगर (prot & IOMMU_WRITE)
		aci = SUN50I_IOMMU_ACI_WR;
	अन्यथा
		aci = SUN50I_IOMMU_ACI_NONE;

	flags |= FIELD_PREP(SUN50I_PTE_ACI_MASK, aci);
	page &= SUN50I_PTE_PAGE_ADDRESS_MASK;
	वापस page | flags | SUN50I_PTE_PAGE_VALID;
पूर्ण

अटल व्योम sun50i_table_flush(काष्ठा sun50i_iommu_करोमुख्य *sun50i_करोमुख्य,
			       व्योम *vaddr, अचिन्हित पूर्णांक count)
अणु
	काष्ठा sun50i_iommu *iommu = sun50i_करोमुख्य->iommu;
	dma_addr_t dma = virt_to_phys(vaddr);
	माप_प्रकार size = count * PT_ENTRY_SIZE;

	dma_sync_single_क्रम_device(iommu->dev, dma, size, DMA_TO_DEVICE);
पूर्ण

अटल पूर्णांक sun50i_iommu_flush_all_tlb(काष्ठा sun50i_iommu *iommu)
अणु
	u32 reg;
	पूर्णांक ret;

	निश्चित_spin_locked(&iommu->iommu_lock);

	iommu_ग_लिखो(iommu,
		    IOMMU_TLB_FLUSH_REG,
		    IOMMU_TLB_FLUSH_PTW_CACHE |
		    IOMMU_TLB_FLUSH_MACRO_TLB |
		    IOMMU_TLB_FLUSH_MICRO_TLB(5) |
		    IOMMU_TLB_FLUSH_MICRO_TLB(4) |
		    IOMMU_TLB_FLUSH_MICRO_TLB(3) |
		    IOMMU_TLB_FLUSH_MICRO_TLB(2) |
		    IOMMU_TLB_FLUSH_MICRO_TLB(1) |
		    IOMMU_TLB_FLUSH_MICRO_TLB(0));

	ret = पढ़ोl_poll_समयout_atomic(iommu->base + IOMMU_TLB_FLUSH_REG,
					reg, !reg,
					1, 2000);
	अगर (ret)
		dev_warn(iommu->dev, "TLB Flush timed out!\n");

	वापस ret;
पूर्ण

अटल व्योम sun50i_iommu_flush_iotlb_all(काष्ठा iommu_करोमुख्य *करोमुख्य)
अणु
	काष्ठा sun50i_iommu_करोमुख्य *sun50i_करोमुख्य = to_sun50i_करोमुख्य(करोमुख्य);
	काष्ठा sun50i_iommu *iommu = sun50i_करोमुख्य->iommu;
	अचिन्हित दीर्घ flags;

	/*
	 * At boot, we'll have a first call पूर्णांकo .flush_iotlb_all right after
	 * .probe_device, and since we link our (single) करोमुख्य to our iommu in
	 * the .attach_device callback, we करोn't have that poपूर्णांकer set.
	 *
	 * It shouldn't really be any trouble to ignore it though since we flush
	 * all caches as part of the device घातerup.
	 */
	अगर (!iommu)
		वापस;

	spin_lock_irqsave(&iommu->iommu_lock, flags);
	sun50i_iommu_flush_all_tlb(iommu);
	spin_unlock_irqrestore(&iommu->iommu_lock, flags);
पूर्ण

अटल व्योम sun50i_iommu_iotlb_sync(काष्ठा iommu_करोमुख्य *करोमुख्य,
				    काष्ठा iommu_iotlb_gather *gather)
अणु
	sun50i_iommu_flush_iotlb_all(करोमुख्य);
पूर्ण

अटल पूर्णांक sun50i_iommu_enable(काष्ठा sun50i_iommu *iommu)
अणु
	काष्ठा sun50i_iommu_करोमुख्य *sun50i_करोमुख्य;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	अगर (!iommu->करोमुख्य)
		वापस 0;

	sun50i_करोमुख्य = to_sun50i_करोमुख्य(iommu->करोमुख्य);

	ret = reset_control_deनिश्चित(iommu->reset);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(iommu->clk);
	अगर (ret)
		जाओ err_reset_निश्चित;

	spin_lock_irqsave(&iommu->iommu_lock, flags);

	iommu_ग_लिखो(iommu, IOMMU_TTB_REG, sun50i_करोमुख्य->dt_dma);
	iommu_ग_लिखो(iommu, IOMMU_TLB_PREFETCH_REG,
		    IOMMU_TLB_PREFETCH_MASTER_ENABLE(0) |
		    IOMMU_TLB_PREFETCH_MASTER_ENABLE(1) |
		    IOMMU_TLB_PREFETCH_MASTER_ENABLE(2) |
		    IOMMU_TLB_PREFETCH_MASTER_ENABLE(3) |
		    IOMMU_TLB_PREFETCH_MASTER_ENABLE(4) |
		    IOMMU_TLB_PREFETCH_MASTER_ENABLE(5));
	iommu_ग_लिखो(iommu, IOMMU_INT_ENABLE_REG, IOMMU_INT_MASK);
	iommu_ग_लिखो(iommu, IOMMU_DM_AUT_CTRL_REG(SUN50I_IOMMU_ACI_NONE),
		    IOMMU_DM_AUT_CTRL_RD_UNAVAIL(SUN50I_IOMMU_ACI_NONE, 0) |
		    IOMMU_DM_AUT_CTRL_WR_UNAVAIL(SUN50I_IOMMU_ACI_NONE, 0) |
		    IOMMU_DM_AUT_CTRL_RD_UNAVAIL(SUN50I_IOMMU_ACI_NONE, 1) |
		    IOMMU_DM_AUT_CTRL_WR_UNAVAIL(SUN50I_IOMMU_ACI_NONE, 1) |
		    IOMMU_DM_AUT_CTRL_RD_UNAVAIL(SUN50I_IOMMU_ACI_NONE, 2) |
		    IOMMU_DM_AUT_CTRL_WR_UNAVAIL(SUN50I_IOMMU_ACI_NONE, 2) |
		    IOMMU_DM_AUT_CTRL_RD_UNAVAIL(SUN50I_IOMMU_ACI_NONE, 3) |
		    IOMMU_DM_AUT_CTRL_WR_UNAVAIL(SUN50I_IOMMU_ACI_NONE, 3) |
		    IOMMU_DM_AUT_CTRL_RD_UNAVAIL(SUN50I_IOMMU_ACI_NONE, 4) |
		    IOMMU_DM_AUT_CTRL_WR_UNAVAIL(SUN50I_IOMMU_ACI_NONE, 4) |
		    IOMMU_DM_AUT_CTRL_RD_UNAVAIL(SUN50I_IOMMU_ACI_NONE, 5) |
		    IOMMU_DM_AUT_CTRL_WR_UNAVAIL(SUN50I_IOMMU_ACI_NONE, 5));

	iommu_ग_लिखो(iommu, IOMMU_DM_AUT_CTRL_REG(SUN50I_IOMMU_ACI_RD),
		    IOMMU_DM_AUT_CTRL_WR_UNAVAIL(SUN50I_IOMMU_ACI_RD, 0) |
		    IOMMU_DM_AUT_CTRL_WR_UNAVAIL(SUN50I_IOMMU_ACI_RD, 1) |
		    IOMMU_DM_AUT_CTRL_WR_UNAVAIL(SUN50I_IOMMU_ACI_RD, 2) |
		    IOMMU_DM_AUT_CTRL_WR_UNAVAIL(SUN50I_IOMMU_ACI_RD, 3) |
		    IOMMU_DM_AUT_CTRL_WR_UNAVAIL(SUN50I_IOMMU_ACI_RD, 4) |
		    IOMMU_DM_AUT_CTRL_WR_UNAVAIL(SUN50I_IOMMU_ACI_RD, 5));

	iommu_ग_लिखो(iommu, IOMMU_DM_AUT_CTRL_REG(SUN50I_IOMMU_ACI_WR),
		    IOMMU_DM_AUT_CTRL_RD_UNAVAIL(SUN50I_IOMMU_ACI_WR, 0) |
		    IOMMU_DM_AUT_CTRL_RD_UNAVAIL(SUN50I_IOMMU_ACI_WR, 1) |
		    IOMMU_DM_AUT_CTRL_RD_UNAVAIL(SUN50I_IOMMU_ACI_WR, 2) |
		    IOMMU_DM_AUT_CTRL_RD_UNAVAIL(SUN50I_IOMMU_ACI_WR, 3) |
		    IOMMU_DM_AUT_CTRL_RD_UNAVAIL(SUN50I_IOMMU_ACI_WR, 4) |
		    IOMMU_DM_AUT_CTRL_RD_UNAVAIL(SUN50I_IOMMU_ACI_WR, 5));

	ret = sun50i_iommu_flush_all_tlb(iommu);
	अगर (ret) अणु
		spin_unlock_irqrestore(&iommu->iommu_lock, flags);
		जाओ err_clk_disable;
	पूर्ण

	iommu_ग_लिखो(iommu, IOMMU_AUTO_GATING_REG, IOMMU_AUTO_GATING_ENABLE);
	iommu_ग_लिखो(iommu, IOMMU_ENABLE_REG, IOMMU_ENABLE_ENABLE);

	spin_unlock_irqrestore(&iommu->iommu_lock, flags);

	वापस 0;

err_clk_disable:
	clk_disable_unprepare(iommu->clk);

err_reset_निश्चित:
	reset_control_निश्चित(iommu->reset);

	वापस ret;
पूर्ण

अटल व्योम sun50i_iommu_disable(काष्ठा sun50i_iommu *iommu)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&iommu->iommu_lock, flags);

	iommu_ग_लिखो(iommu, IOMMU_ENABLE_REG, 0);
	iommu_ग_लिखो(iommu, IOMMU_TTB_REG, 0);

	spin_unlock_irqrestore(&iommu->iommu_lock, flags);

	clk_disable_unprepare(iommu->clk);
	reset_control_निश्चित(iommu->reset);
पूर्ण

अटल व्योम *sun50i_iommu_alloc_page_table(काष्ठा sun50i_iommu *iommu,
					   gfp_t gfp)
अणु
	dma_addr_t pt_dma;
	u32 *page_table;

	page_table = kmem_cache_zalloc(iommu->pt_pool, gfp);
	अगर (!page_table)
		वापस ERR_PTR(-ENOMEM);

	pt_dma = dma_map_single(iommu->dev, page_table, PT_SIZE, DMA_TO_DEVICE);
	अगर (dma_mapping_error(iommu->dev, pt_dma)) अणु
		dev_err(iommu->dev, "Couldn't map L2 Page Table\n");
		kmem_cache_मुक्त(iommu->pt_pool, page_table);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	/* We rely on the physical address and DMA address being the same */
	WARN_ON(pt_dma != virt_to_phys(page_table));

	वापस page_table;
पूर्ण

अटल व्योम sun50i_iommu_मुक्त_page_table(काष्ठा sun50i_iommu *iommu,
					 u32 *page_table)
अणु
	phys_addr_t pt_phys = virt_to_phys(page_table);

	dma_unmap_single(iommu->dev, pt_phys, PT_SIZE, DMA_TO_DEVICE);
	kmem_cache_मुक्त(iommu->pt_pool, page_table);
पूर्ण

अटल u32 *sun50i_dte_get_page_table(काष्ठा sun50i_iommu_करोमुख्य *sun50i_करोमुख्य,
				      dma_addr_t iova, gfp_t gfp)
अणु
	काष्ठा sun50i_iommu *iommu = sun50i_करोमुख्य->iommu;
	u32 *page_table;
	u32 *dte_addr;
	u32 old_dte;
	u32 dte;

	dte_addr = &sun50i_करोमुख्य->dt[sun50i_iova_get_dte_index(iova)];
	dte = *dte_addr;
	अगर (sun50i_dte_is_pt_valid(dte)) अणु
		phys_addr_t pt_phys = sun50i_dte_get_pt_address(dte);
		वापस (u32 *)phys_to_virt(pt_phys);
	पूर्ण

	page_table = sun50i_iommu_alloc_page_table(iommu, gfp);
	अगर (IS_ERR(page_table))
		वापस page_table;

	dte = sun50i_mk_dte(virt_to_phys(page_table));
	old_dte = cmpxchg(dte_addr, 0, dte);
	अगर (old_dte) अणु
		phys_addr_t installed_pt_phys =
			sun50i_dte_get_pt_address(old_dte);
		u32 *installed_pt = phys_to_virt(installed_pt_phys);
		u32 *drop_pt = page_table;

		page_table = installed_pt;
		dte = old_dte;
		sun50i_iommu_मुक्त_page_table(iommu, drop_pt);
	पूर्ण

	sun50i_table_flush(sun50i_करोमुख्य, page_table, PT_SIZE);
	sun50i_table_flush(sun50i_करोमुख्य, dte_addr, 1);

	वापस page_table;
पूर्ण

अटल पूर्णांक sun50i_iommu_map(काष्ठा iommu_करोमुख्य *करोमुख्य, अचिन्हित दीर्घ iova,
			    phys_addr_t paddr, माप_प्रकार size, पूर्णांक prot, gfp_t gfp)
अणु
	काष्ठा sun50i_iommu_करोमुख्य *sun50i_करोमुख्य = to_sun50i_करोमुख्य(करोमुख्य);
	काष्ठा sun50i_iommu *iommu = sun50i_करोमुख्य->iommu;
	u32 pte_index;
	u32 *page_table, *pte_addr;
	पूर्णांक ret = 0;

	page_table = sun50i_dte_get_page_table(sun50i_करोमुख्य, iova, gfp);
	अगर (IS_ERR(page_table)) अणु
		ret = PTR_ERR(page_table);
		जाओ out;
	पूर्ण

	pte_index = sun50i_iova_get_pte_index(iova);
	pte_addr = &page_table[pte_index];
	अगर (unlikely(sun50i_pte_is_page_valid(*pte_addr))) अणु
		phys_addr_t page_phys = sun50i_pte_get_page_address(*pte_addr);
		dev_err(iommu->dev,
			"iova %pad already mapped to %pa cannot remap to %pa prot: %#x\n",
			&iova, &page_phys, &paddr, prot);
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	*pte_addr = sun50i_mk_pte(paddr, prot);
	sun50i_table_flush(sun50i_करोमुख्य, pte_addr, 1);

out:
	वापस ret;
पूर्ण

अटल माप_प्रकार sun50i_iommu_unmap(काष्ठा iommu_करोमुख्य *करोमुख्य, अचिन्हित दीर्घ iova,
				 माप_प्रकार size, काष्ठा iommu_iotlb_gather *gather)
अणु
	काष्ठा sun50i_iommu_करोमुख्य *sun50i_करोमुख्य = to_sun50i_करोमुख्य(करोमुख्य);
	phys_addr_t pt_phys;
	u32 *pte_addr;
	u32 dte;

	dte = sun50i_करोमुख्य->dt[sun50i_iova_get_dte_index(iova)];
	अगर (!sun50i_dte_is_pt_valid(dte))
		वापस 0;

	pt_phys = sun50i_dte_get_pt_address(dte);
	pte_addr = (u32 *)phys_to_virt(pt_phys) + sun50i_iova_get_pte_index(iova);

	अगर (!sun50i_pte_is_page_valid(*pte_addr))
		वापस 0;

	स_रखो(pte_addr, 0, माप(*pte_addr));
	sun50i_table_flush(sun50i_करोमुख्य, pte_addr, 1);

	वापस SZ_4K;
पूर्ण

अटल phys_addr_t sun50i_iommu_iova_to_phys(काष्ठा iommu_करोमुख्य *करोमुख्य,
					     dma_addr_t iova)
अणु
	काष्ठा sun50i_iommu_करोमुख्य *sun50i_करोमुख्य = to_sun50i_करोमुख्य(करोमुख्य);
	phys_addr_t pt_phys;
	u32 *page_table;
	u32 dte, pte;

	dte = sun50i_करोमुख्य->dt[sun50i_iova_get_dte_index(iova)];
	अगर (!sun50i_dte_is_pt_valid(dte))
		वापस 0;

	pt_phys = sun50i_dte_get_pt_address(dte);
	page_table = (u32 *)phys_to_virt(pt_phys);
	pte = page_table[sun50i_iova_get_pte_index(iova)];
	अगर (!sun50i_pte_is_page_valid(pte))
		वापस 0;

	वापस sun50i_pte_get_page_address(pte) +
		sun50i_iova_get_page_offset(iova);
पूर्ण

अटल काष्ठा iommu_करोमुख्य *sun50i_iommu_करोमुख्य_alloc(अचिन्हित type)
अणु
	काष्ठा sun50i_iommu_करोमुख्य *sun50i_करोमुख्य;

	अगर (type != IOMMU_DOMAIN_DMA &&
	    type != IOMMU_DOMAIN_IDENTITY &&
	    type != IOMMU_DOMAIN_UNMANAGED)
		वापस शून्य;

	sun50i_करोमुख्य = kzalloc(माप(*sun50i_करोमुख्य), GFP_KERNEL);
	अगर (!sun50i_करोमुख्य)
		वापस शून्य;

	अगर (type == IOMMU_DOMAIN_DMA &&
	    iommu_get_dma_cookie(&sun50i_करोमुख्य->करोमुख्य))
		जाओ err_मुक्त_करोमुख्य;

	sun50i_करोमुख्य->dt = (u32 *)__get_मुक्त_pages(GFP_KERNEL | __GFP_ZERO,
						    get_order(DT_SIZE));
	अगर (!sun50i_करोमुख्य->dt)
		जाओ err_put_cookie;

	refcount_set(&sun50i_करोमुख्य->refcnt, 1);

	sun50i_करोमुख्य->करोमुख्य.geometry.aperture_start = 0;
	sun50i_करोमुख्य->करोमुख्य.geometry.aperture_end = DMA_BIT_MASK(32);
	sun50i_करोमुख्य->करोमुख्य.geometry.क्रमce_aperture = true;

	वापस &sun50i_करोमुख्य->करोमुख्य;

err_put_cookie:
	अगर (type == IOMMU_DOMAIN_DMA)
		iommu_put_dma_cookie(&sun50i_करोमुख्य->करोमुख्य);

err_मुक्त_करोमुख्य:
	kमुक्त(sun50i_करोमुख्य);

	वापस शून्य;
पूर्ण

अटल व्योम sun50i_iommu_करोमुख्य_मुक्त(काष्ठा iommu_करोमुख्य *करोमुख्य)
अणु
	काष्ठा sun50i_iommu_करोमुख्य *sun50i_करोमुख्य = to_sun50i_करोमुख्य(करोमुख्य);

	मुक्त_pages((अचिन्हित दीर्घ)sun50i_करोमुख्य->dt, get_order(DT_SIZE));
	sun50i_करोमुख्य->dt = शून्य;

	iommu_put_dma_cookie(करोमुख्य);

	kमुक्त(sun50i_करोमुख्य);
पूर्ण

अटल पूर्णांक sun50i_iommu_attach_करोमुख्य(काष्ठा sun50i_iommu *iommu,
				      काष्ठा sun50i_iommu_करोमुख्य *sun50i_करोमुख्य)
अणु
	iommu->करोमुख्य = &sun50i_करोमुख्य->करोमुख्य;
	sun50i_करोमुख्य->iommu = iommu;

	sun50i_करोमुख्य->dt_dma = dma_map_single(iommu->dev, sun50i_करोमुख्य->dt,
					       DT_SIZE, DMA_TO_DEVICE);
	अगर (dma_mapping_error(iommu->dev, sun50i_करोमुख्य->dt_dma)) अणु
		dev_err(iommu->dev, "Couldn't map L1 Page Table\n");
		वापस -ENOMEM;
	पूर्ण

	वापस sun50i_iommu_enable(iommu);
पूर्ण

अटल व्योम sun50i_iommu_detach_करोमुख्य(काष्ठा sun50i_iommu *iommu,
				       काष्ठा sun50i_iommu_करोमुख्य *sun50i_करोमुख्य)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < NUM_DT_ENTRIES; i++) अणु
		phys_addr_t pt_phys;
		u32 *page_table;
		u32 *dte_addr;
		u32 dte;

		dte_addr = &sun50i_करोमुख्य->dt[i];
		dte = *dte_addr;
		अगर (!sun50i_dte_is_pt_valid(dte))
			जारी;

		स_रखो(dte_addr, 0, माप(*dte_addr));
		sun50i_table_flush(sun50i_करोमुख्य, dte_addr, 1);

		pt_phys = sun50i_dte_get_pt_address(dte);
		page_table = phys_to_virt(pt_phys);
		sun50i_iommu_मुक्त_page_table(iommu, page_table);
	पूर्ण


	sun50i_iommu_disable(iommu);

	dma_unmap_single(iommu->dev, virt_to_phys(sun50i_करोमुख्य->dt),
			 DT_SIZE, DMA_TO_DEVICE);

	iommu->करोमुख्य = शून्य;
पूर्ण

अटल व्योम sun50i_iommu_detach_device(काष्ठा iommu_करोमुख्य *करोमुख्य,
				       काष्ठा device *dev)
अणु
	काष्ठा sun50i_iommu_करोमुख्य *sun50i_करोमुख्य = to_sun50i_करोमुख्य(करोमुख्य);
	काष्ठा sun50i_iommu *iommu = dev_iommu_priv_get(dev);

	dev_dbg(dev, "Detaching from IOMMU domain\n");

	अगर (iommu->करोमुख्य != करोमुख्य)
		वापस;

	अगर (refcount_dec_and_test(&sun50i_करोमुख्य->refcnt))
		sun50i_iommu_detach_करोमुख्य(iommu, sun50i_करोमुख्य);
पूर्ण

अटल पूर्णांक sun50i_iommu_attach_device(काष्ठा iommu_करोमुख्य *करोमुख्य,
				      काष्ठा device *dev)
अणु
	काष्ठा sun50i_iommu_करोमुख्य *sun50i_करोमुख्य = to_sun50i_करोमुख्य(करोमुख्य);
	काष्ठा sun50i_iommu *iommu;

	iommu = sun50i_iommu_from_dev(dev);
	अगर (!iommu)
		वापस -ENODEV;

	dev_dbg(dev, "Attaching to IOMMU domain\n");

	refcount_inc(&sun50i_करोमुख्य->refcnt);

	अगर (iommu->करोमुख्य == करोमुख्य)
		वापस 0;

	अगर (iommu->करोमुख्य)
		sun50i_iommu_detach_device(iommu->करोमुख्य, dev);

	sun50i_iommu_attach_करोमुख्य(iommu, sun50i_करोमुख्य);

	वापस 0;
पूर्ण

अटल काष्ठा iommu_device *sun50i_iommu_probe_device(काष्ठा device *dev)
अणु
	काष्ठा sun50i_iommu *iommu;

	iommu = sun50i_iommu_from_dev(dev);
	अगर (!iommu)
		वापस ERR_PTR(-ENODEV);

	वापस &iommu->iommu;
पूर्ण

अटल व्योम sun50i_iommu_release_device(काष्ठा device *dev) अणुपूर्ण

अटल काष्ठा iommu_group *sun50i_iommu_device_group(काष्ठा device *dev)
अणु
	काष्ठा sun50i_iommu *iommu = sun50i_iommu_from_dev(dev);

	वापस iommu_group_ref_get(iommu->group);
पूर्ण

अटल पूर्णांक sun50i_iommu_of_xlate(काष्ठा device *dev,
				 काष्ठा of_phandle_args *args)
अणु
	काष्ठा platक्रमm_device *iommu_pdev = of_find_device_by_node(args->np);
	अचिन्हित id = args->args[0];

	dev_iommu_priv_set(dev, platक्रमm_get_drvdata(iommu_pdev));

	वापस iommu_fwspec_add_ids(dev, &id, 1);
पूर्ण

अटल स्थिर काष्ठा iommu_ops sun50i_iommu_ops = अणु
	.pgsize_biपंचांगap	= SZ_4K,
	.attach_dev	= sun50i_iommu_attach_device,
	.detach_dev	= sun50i_iommu_detach_device,
	.device_group	= sun50i_iommu_device_group,
	.करोमुख्य_alloc	= sun50i_iommu_करोमुख्य_alloc,
	.करोमुख्य_मुक्त	= sun50i_iommu_करोमुख्य_मुक्त,
	.flush_iotlb_all = sun50i_iommu_flush_iotlb_all,
	.iotlb_sync	= sun50i_iommu_iotlb_sync,
	.iova_to_phys	= sun50i_iommu_iova_to_phys,
	.map		= sun50i_iommu_map,
	.of_xlate	= sun50i_iommu_of_xlate,
	.probe_device	= sun50i_iommu_probe_device,
	.release_device	= sun50i_iommu_release_device,
	.unmap		= sun50i_iommu_unmap,
पूर्ण;

अटल व्योम sun50i_iommu_report_fault(काष्ठा sun50i_iommu *iommu,
				      अचिन्हित master, phys_addr_t iova,
				      अचिन्हित prot)
अणु
	dev_err(iommu->dev, "Page fault for %pad (master %d, dir %s)\n",
		&iova, master, (prot == IOMMU_FAULT_WRITE) ? "wr" : "rd");

	अगर (iommu->करोमुख्य)
		report_iommu_fault(iommu->करोमुख्य, iommu->dev, iova, prot);
	अन्यथा
		dev_err(iommu->dev, "Page fault while iommu not attached to any domain?\n");
पूर्ण

अटल phys_addr_t sun50i_iommu_handle_pt_irq(काष्ठा sun50i_iommu *iommu,
					      अचिन्हित addr_reg,
					      अचिन्हित blame_reg)
अणु
	phys_addr_t iova;
	अचिन्हित master;
	u32 blame;

	निश्चित_spin_locked(&iommu->iommu_lock);

	iova = iommu_पढ़ो(iommu, addr_reg);
	blame = iommu_पढ़ो(iommu, blame_reg);
	master = ilog2(blame & IOMMU_INT_MASTER_MASK);

	/*
	 * If the address is not in the page table, we can't get what
	 * operation triggered the fault. Assume it's a पढ़ो
	 * operation.
	 */
	sun50i_iommu_report_fault(iommu, master, iova, IOMMU_FAULT_READ);

	वापस iova;
पूर्ण

अटल phys_addr_t sun50i_iommu_handle_perm_irq(काष्ठा sun50i_iommu *iommu)
अणु
	क्रमागत sun50i_iommu_aci aci;
	phys_addr_t iova;
	अचिन्हित master;
	अचिन्हित dir;
	u32 blame;

	निश्चित_spin_locked(&iommu->iommu_lock);

	blame = iommu_पढ़ो(iommu, IOMMU_INT_STA_REG);
	master = ilog2(blame & IOMMU_INT_MASTER_MASK);
	iova = iommu_पढ़ो(iommu, IOMMU_INT_ERR_ADDR_REG(master));
	aci = sun50i_get_pte_aci(iommu_पढ़ो(iommu,
					    IOMMU_INT_ERR_DATA_REG(master)));

	चयन (aci) अणु
		/*
		 * If we are in the पढ़ो-only करोमुख्य, then it means we
		 * tried to ग_लिखो.
		 */
	हाल SUN50I_IOMMU_ACI_RD:
		dir = IOMMU_FAULT_WRITE;
		अवरोध;

		/*
		 * If we are in the ग_लिखो-only करोमुख्य, then it means
		 * we tried to पढ़ो.
		 */
	हाल SUN50I_IOMMU_ACI_WR:

		/*
		 * If we are in the करोमुख्य without any permission, we
		 * can't really tell. Let's शेष to a पढ़ो
		 * operation.
		 */
	हाल SUN50I_IOMMU_ACI_NONE:

		/* WTF? */
	हाल SUN50I_IOMMU_ACI_RD_WR:
	शेष:
		dir = IOMMU_FAULT_READ;
		अवरोध;
	पूर्ण

	/*
	 * If the address is not in the page table, we can't get what
	 * operation triggered the fault. Assume it's a पढ़ो
	 * operation.
	 */
	sun50i_iommu_report_fault(iommu, master, iova, dir);

	वापस iova;
पूर्ण

अटल irqवापस_t sun50i_iommu_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा sun50i_iommu *iommu = dev_id;
	u32 status;

	spin_lock(&iommu->iommu_lock);

	status = iommu_पढ़ो(iommu, IOMMU_INT_STA_REG);
	अगर (!(status & IOMMU_INT_MASK)) अणु
		spin_unlock(&iommu->iommu_lock);
		वापस IRQ_NONE;
	पूर्ण

	अगर (status & IOMMU_INT_INVALID_L2PG)
		sun50i_iommu_handle_pt_irq(iommu,
					    IOMMU_INT_ERR_ADDR_L2_REG,
					    IOMMU_L2PG_INT_REG);
	अन्यथा अगर (status & IOMMU_INT_INVALID_L1PG)
		sun50i_iommu_handle_pt_irq(iommu,
					   IOMMU_INT_ERR_ADDR_L1_REG,
					   IOMMU_L1PG_INT_REG);
	अन्यथा
		sun50i_iommu_handle_perm_irq(iommu);

	iommu_ग_लिखो(iommu, IOMMU_INT_CLR_REG, status);

	iommu_ग_लिखो(iommu, IOMMU_RESET_REG, ~status);
	iommu_ग_लिखो(iommu, IOMMU_RESET_REG, status);

	spin_unlock(&iommu->iommu_lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक sun50i_iommu_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sun50i_iommu *iommu;
	पूर्णांक ret, irq;

	iommu = devm_kzalloc(&pdev->dev, माप(*iommu), GFP_KERNEL);
	अगर (!iommu)
		वापस -ENOMEM;
	spin_lock_init(&iommu->iommu_lock);
	platक्रमm_set_drvdata(pdev, iommu);
	iommu->dev = &pdev->dev;

	iommu->pt_pool = kmem_cache_create(dev_name(&pdev->dev),
					   PT_SIZE, PT_SIZE,
					   SLAB_HWCACHE_ALIGN,
					   शून्य);
	अगर (!iommu->pt_pool)
		वापस -ENOMEM;

	iommu->group = iommu_group_alloc();
	अगर (IS_ERR(iommu->group)) अणु
		ret = PTR_ERR(iommu->group);
		जाओ err_मुक्त_cache;
	पूर्ण

	iommu->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(iommu->base)) अणु
		ret = PTR_ERR(iommu->base);
		जाओ err_मुक्त_group;
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0) अणु
		ret = irq;
		जाओ err_मुक्त_group;
	पूर्ण

	iommu->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(iommu->clk)) अणु
		dev_err(&pdev->dev, "Couldn't get our clock.\n");
		ret = PTR_ERR(iommu->clk);
		जाओ err_मुक्त_group;
	पूर्ण

	iommu->reset = devm_reset_control_get(&pdev->dev, शून्य);
	अगर (IS_ERR(iommu->reset)) अणु
		dev_err(&pdev->dev, "Couldn't get our reset line.\n");
		ret = PTR_ERR(iommu->reset);
		जाओ err_मुक्त_group;
	पूर्ण

	ret = iommu_device_sysfs_add(&iommu->iommu, &pdev->dev,
				     शून्य, dev_name(&pdev->dev));
	अगर (ret)
		जाओ err_मुक्त_group;

	ret = iommu_device_रेजिस्टर(&iommu->iommu, &sun50i_iommu_ops, &pdev->dev);
	अगर (ret)
		जाओ err_हटाओ_sysfs;

	ret = devm_request_irq(&pdev->dev, irq, sun50i_iommu_irq, 0,
			       dev_name(&pdev->dev), iommu);
	अगर (ret < 0)
		जाओ err_unरेजिस्टर;

	bus_set_iommu(&platक्रमm_bus_type, &sun50i_iommu_ops);

	वापस 0;

err_unरेजिस्टर:
	iommu_device_unरेजिस्टर(&iommu->iommu);

err_हटाओ_sysfs:
	iommu_device_sysfs_हटाओ(&iommu->iommu);

err_मुक्त_group:
	iommu_group_put(iommu->group);

err_मुक्त_cache:
	kmem_cache_destroy(iommu->pt_pool);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id sun50i_iommu_dt[] = अणु
	अणु .compatible = "allwinner,sun50i-h6-iommu", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sun50i_iommu_dt);

अटल काष्ठा platक्रमm_driver sun50i_iommu_driver = अणु
	.driver		= अणु
		.name			= "sun50i-iommu",
		.of_match_table 	= sun50i_iommu_dt,
		.suppress_bind_attrs	= true,
	पूर्ण
पूर्ण;
builtin_platक्रमm_driver_probe(sun50i_iommu_driver, sun50i_iommu_probe);

MODULE_DESCRIPTION("Allwinner H6 IOMMU driver");
MODULE_AUTHOR("Maxime Ripard <maxime@cerno.tech>");
MODULE_AUTHOR("zhuxianbin <zhuxianbin@allwinnertech.com>");
MODULE_LICENSE("Dual BSD/GPL");
