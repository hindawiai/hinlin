<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2015-2016 MediaTek Inc.
 * Author: Yong Wu <yong.wu@mediatek.com>
 */
#समावेश <linux/bitfield.h>
#समावेश <linux/bug.h>
#समावेश <linux/clk.h>
#समावेश <linux/component.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-direct.h>
#समावेश <linux/dma-iommu.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/iommu.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/list.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_iommu.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/soc/mediatek/infracfg.h>
#समावेश <यंत्र/barrier.h>
#समावेश <soc/mediatek/smi.h>

#समावेश "mtk_iommu.h"

#घोषणा REG_MMU_PT_BASE_ADDR			0x000
#घोषणा MMU_PT_ADDR_MASK			GENMASK(31, 7)

#घोषणा REG_MMU_INVALIDATE			0x020
#घोषणा F_ALL_INVLD				0x2
#घोषणा F_MMU_INV_RANGE				0x1

#घोषणा REG_MMU_INVLD_START_A			0x024
#घोषणा REG_MMU_INVLD_END_A			0x028

#घोषणा REG_MMU_INV_SEL_GEN2			0x02c
#घोषणा REG_MMU_INV_SEL_GEN1			0x038
#घोषणा F_INVLD_EN0				BIT(0)
#घोषणा F_INVLD_EN1				BIT(1)

#घोषणा REG_MMU_MISC_CTRL			0x048
#घोषणा F_MMU_IN_ORDER_WR_EN_MASK		(BIT(1) | BIT(17))
#घोषणा F_MMU_STANDARD_AXI_MODE_MASK		(BIT(3) | BIT(19))

#घोषणा REG_MMU_DCM_DIS				0x050
#घोषणा REG_MMU_WR_LEN_CTRL			0x054
#घोषणा F_MMU_WR_THROT_DIS_MASK			(BIT(5) | BIT(21))

#घोषणा REG_MMU_CTRL_REG			0x110
#घोषणा F_MMU_TF_PROT_TO_PROGRAM_ADDR		(2 << 4)
#घोषणा F_MMU_PREFETCH_RT_REPLACE_MOD		BIT(4)
#घोषणा F_MMU_TF_PROT_TO_PROGRAM_ADDR_MT8173	(2 << 5)

#घोषणा REG_MMU_IVRP_PADDR			0x114

#घोषणा REG_MMU_VLD_PA_RNG			0x118
#घोषणा F_MMU_VLD_PA_RNG(EA, SA)		(((EA) << 8) | (SA))

#घोषणा REG_MMU_INT_CONTROL0			0x120
#घोषणा F_L2_MULIT_HIT_EN			BIT(0)
#घोषणा F_TABLE_WALK_FAULT_INT_EN		BIT(1)
#घोषणा F_PREETCH_FIFO_OVERFLOW_INT_EN		BIT(2)
#घोषणा F_MISS_FIFO_OVERFLOW_INT_EN		BIT(3)
#घोषणा F_PREFETCH_FIFO_ERR_INT_EN		BIT(5)
#घोषणा F_MISS_FIFO_ERR_INT_EN			BIT(6)
#घोषणा F_INT_CLR_BIT				BIT(12)

#घोषणा REG_MMU_INT_MAIN_CONTROL		0x124
						/* mmu0 | mmu1 */
#घोषणा F_INT_TRANSLATION_FAULT			(BIT(0) | BIT(7))
#घोषणा F_INT_MAIN_MULTI_HIT_FAULT		(BIT(1) | BIT(8))
#घोषणा F_INT_INVALID_PA_FAULT			(BIT(2) | BIT(9))
#घोषणा F_INT_ENTRY_REPLACEMENT_FAULT		(BIT(3) | BIT(10))
#घोषणा F_INT_TLB_MISS_FAULT			(BIT(4) | BIT(11))
#घोषणा F_INT_MISS_TRANSACTION_FIFO_FAULT	(BIT(5) | BIT(12))
#घोषणा F_INT_PRETETCH_TRANSATION_FIFO_FAULT	(BIT(6) | BIT(13))

#घोषणा REG_MMU_CPE_DONE			0x12C

#घोषणा REG_MMU_FAULT_ST1			0x134
#घोषणा F_REG_MMU0_FAULT_MASK			GENMASK(6, 0)
#घोषणा F_REG_MMU1_FAULT_MASK			GENMASK(13, 7)

#घोषणा REG_MMU0_FAULT_VA			0x13c
#घोषणा F_MMU_INVAL_VA_31_12_MASK		GENMASK(31, 12)
#घोषणा F_MMU_INVAL_VA_34_32_MASK		GENMASK(11, 9)
#घोषणा F_MMU_INVAL_PA_34_32_MASK		GENMASK(8, 6)
#घोषणा F_MMU_FAULT_VA_WRITE_BIT		BIT(1)
#घोषणा F_MMU_FAULT_VA_LAYER_BIT		BIT(0)

#घोषणा REG_MMU0_INVLD_PA			0x140
#घोषणा REG_MMU1_FAULT_VA			0x144
#घोषणा REG_MMU1_INVLD_PA			0x148
#घोषणा REG_MMU0_INT_ID				0x150
#घोषणा REG_MMU1_INT_ID				0x154
#घोषणा F_MMU_INT_ID_COMM_ID(a)			(((a) >> 9) & 0x7)
#घोषणा F_MMU_INT_ID_SUB_COMM_ID(a)		(((a) >> 7) & 0x3)
#घोषणा F_MMU_INT_ID_LARB_ID(a)			(((a) >> 7) & 0x7)
#घोषणा F_MMU_INT_ID_PORT_ID(a)			(((a) >> 2) & 0x1f)

#घोषणा MTK_PROTECT_PA_ALIGN			256

#घोषणा HAS_4GB_MODE			BIT(0)
/* HW will use the EMI घड़ी अगर there isn't the "bclk". */
#घोषणा HAS_BCLK			BIT(1)
#घोषणा HAS_VLD_PA_RNG			BIT(2)
#घोषणा RESET_AXI			BIT(3)
#घोषणा OUT_ORDER_WR_EN			BIT(4)
#घोषणा HAS_SUB_COMM			BIT(5)
#घोषणा WR_THROT_EN			BIT(6)
#घोषणा HAS_LEGACY_IVRP_PADDR		BIT(7)
#घोषणा IOVA_34_EN			BIT(8)

#घोषणा MTK_IOMMU_HAS_FLAG(pdata, _x) \
		((((pdata)->flags) & (_x)) == (_x))

काष्ठा mtk_iommu_करोमुख्य अणु
	काष्ठा io_pgtable_cfg		cfg;
	काष्ठा io_pgtable_ops		*iop;

	काष्ठा mtk_iommu_data		*data;
	काष्ठा iommu_करोमुख्य		करोमुख्य;
पूर्ण;

अटल स्थिर काष्ठा iommu_ops mtk_iommu_ops;

अटल पूर्णांक mtk_iommu_hw_init(स्थिर काष्ठा mtk_iommu_data *data);

#घोषणा MTK_IOMMU_TLB_ADDR(iova) (अणु					\
	dma_addr_t _addr = iova;					\
	((lower_32_bits(_addr) & GENMASK(31, 12)) | upper_32_bits(_addr));\
पूर्ण)

/*
 * In M4U 4GB mode, the physical address is remapped as below:
 *
 * CPU Physical address:
 * ====================
 *
 * 0      1G       2G     3G       4G     5G
 * |---A---|---B---|---C---|---D---|---E---|
 * +--I/O--+------------Memory-------------+
 *
 * IOMMU output physical address:
 *  =============================
 *
 *                                 4G      5G     6G      7G      8G
 *                                 |---E---|---B---|---C---|---D---|
 *                                 +------------Memory-------------+
 *
 * The Region 'A'(I/O) can NOT be mapped by M4U; For Region 'B'/'C'/'D', the
 * bit32 of the CPU physical address always is needed to set, and क्रम Region
 * 'E', the CPU physical address keep as is.
 * Additionally, The iommu consumers always use the CPU phyiscal address.
 */
#घोषणा MTK_IOMMU_4GB_MODE_REMAP_BASE	 0x140000000UL

अटल LIST_HEAD(m4ulist);	/* List all the M4U HWs */

#घोषणा क्रम_each_m4u(data)	list_क्रम_each_entry(data, &m4ulist, list)

काष्ठा mtk_iommu_iova_region अणु
	dma_addr_t		iova_base;
	अचिन्हित दीर्घ दीर्घ	size;
पूर्ण;

अटल स्थिर काष्ठा mtk_iommu_iova_region single_करोमुख्य[] = अणु
	अणु.iova_base = 0,		.size = SZ_4Gपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mtk_iommu_iova_region mt8192_multi_करोm[] = अणु
	अणु .iova_base = 0x0,		.size = SZ_4Gपूर्ण,		/* disp: 0 ~ 4G */
	#अगर IS_ENABLED(CONFIG_ARCH_DMA_ADDR_T_64BIT)
	अणु .iova_base = SZ_4G,		.size = SZ_4Gपूर्ण,		/* vdec: 4G ~ 8G */
	अणु .iova_base = SZ_4G * 2,	.size = SZ_4Gपूर्ण,		/* CAM/MDP: 8G ~ 12G */
	अणु .iova_base = 0x240000000ULL,	.size = 0x4000000पूर्ण,	/* CCU0 */
	अणु .iova_base = 0x244000000ULL,	.size = 0x4000000पूर्ण,	/* CCU1 */
	#पूर्ण_अगर
पूर्ण;

/*
 * There may be 1 or 2 M4U HWs, But we always expect they are in the same करोमुख्य
 * क्रम the perक्रमmance.
 *
 * Here always वापस the mtk_iommu_data of the first probed M4U where the
 * iommu करोमुख्य inक्रमmation is recorded.
 */
अटल काष्ठा mtk_iommu_data *mtk_iommu_get_m4u_data(व्योम)
अणु
	काष्ठा mtk_iommu_data *data;

	क्रम_each_m4u(data)
		वापस data;

	वापस शून्य;
पूर्ण

अटल काष्ठा mtk_iommu_करोमुख्य *to_mtk_करोमुख्य(काष्ठा iommu_करोमुख्य *करोm)
अणु
	वापस container_of(करोm, काष्ठा mtk_iommu_करोमुख्य, करोमुख्य);
पूर्ण

अटल व्योम mtk_iommu_tlb_flush_all(काष्ठा mtk_iommu_data *data)
अणु
	क्रम_each_m4u(data) अणु
		अगर (pm_runसमय_get_अगर_in_use(data->dev) <= 0)
			जारी;

		ग_लिखोl_relaxed(F_INVLD_EN1 | F_INVLD_EN0,
			       data->base + data->plat_data->inv_sel_reg);
		ग_लिखोl_relaxed(F_ALL_INVLD, data->base + REG_MMU_INVALIDATE);
		wmb(); /* Make sure the tlb flush all करोne */

		pm_runसमय_put(data->dev);
	पूर्ण
पूर्ण

अटल व्योम mtk_iommu_tlb_flush_range_sync(अचिन्हित दीर्घ iova, माप_प्रकार size,
					   माप_प्रकार granule,
					   काष्ठा mtk_iommu_data *data)
अणु
	bool has_pm = !!data->dev->pm_करोमुख्य;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;
	u32 पंचांगp;

	क्रम_each_m4u(data) अणु
		अगर (has_pm) अणु
			अगर (pm_runसमय_get_अगर_in_use(data->dev) <= 0)
				जारी;
		पूर्ण

		spin_lock_irqsave(&data->tlb_lock, flags);
		ग_लिखोl_relaxed(F_INVLD_EN1 | F_INVLD_EN0,
			       data->base + data->plat_data->inv_sel_reg);

		ग_लिखोl_relaxed(MTK_IOMMU_TLB_ADDR(iova),
			       data->base + REG_MMU_INVLD_START_A);
		ग_लिखोl_relaxed(MTK_IOMMU_TLB_ADDR(iova + size - 1),
			       data->base + REG_MMU_INVLD_END_A);
		ग_लिखोl_relaxed(F_MMU_INV_RANGE,
			       data->base + REG_MMU_INVALIDATE);

		/* tlb sync */
		ret = पढ़ोl_poll_समयout_atomic(data->base + REG_MMU_CPE_DONE,
						पंचांगp, पंचांगp != 0, 10, 1000);
		अगर (ret) अणु
			dev_warn(data->dev,
				 "Partial TLB flush timed out, falling back to full flush\n");
			mtk_iommu_tlb_flush_all(data);
		पूर्ण
		/* Clear the CPE status */
		ग_लिखोl_relaxed(0, data->base + REG_MMU_CPE_DONE);
		spin_unlock_irqrestore(&data->tlb_lock, flags);

		अगर (has_pm)
			pm_runसमय_put(data->dev);
	पूर्ण
पूर्ण

अटल irqवापस_t mtk_iommu_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mtk_iommu_data *data = dev_id;
	काष्ठा mtk_iommu_करोमुख्य *करोm = data->m4u_करोm;
	अचिन्हित पूर्णांक fault_larb, fault_port, sub_comm = 0;
	u32 पूर्णांक_state, regval, va34_32, pa34_32;
	u64 fault_iova, fault_pa;
	bool layer, ग_लिखो;

	/* Read error info from रेजिस्टरs */
	पूर्णांक_state = पढ़ोl_relaxed(data->base + REG_MMU_FAULT_ST1);
	अगर (पूर्णांक_state & F_REG_MMU0_FAULT_MASK) अणु
		regval = पढ़ोl_relaxed(data->base + REG_MMU0_INT_ID);
		fault_iova = पढ़ोl_relaxed(data->base + REG_MMU0_FAULT_VA);
		fault_pa = पढ़ोl_relaxed(data->base + REG_MMU0_INVLD_PA);
	पूर्ण अन्यथा अणु
		regval = पढ़ोl_relaxed(data->base + REG_MMU1_INT_ID);
		fault_iova = पढ़ोl_relaxed(data->base + REG_MMU1_FAULT_VA);
		fault_pa = पढ़ोl_relaxed(data->base + REG_MMU1_INVLD_PA);
	पूर्ण
	layer = fault_iova & F_MMU_FAULT_VA_LAYER_BIT;
	ग_लिखो = fault_iova & F_MMU_FAULT_VA_WRITE_BIT;
	अगर (MTK_IOMMU_HAS_FLAG(data->plat_data, IOVA_34_EN)) अणु
		va34_32 = FIELD_GET(F_MMU_INVAL_VA_34_32_MASK, fault_iova);
		pa34_32 = FIELD_GET(F_MMU_INVAL_PA_34_32_MASK, fault_iova);
		fault_iova = fault_iova & F_MMU_INVAL_VA_31_12_MASK;
		fault_iova |= (u64)va34_32 << 32;
		fault_pa |= (u64)pa34_32 << 32;
	पूर्ण

	fault_port = F_MMU_INT_ID_PORT_ID(regval);
	अगर (MTK_IOMMU_HAS_FLAG(data->plat_data, HAS_SUB_COMM)) अणु
		fault_larb = F_MMU_INT_ID_COMM_ID(regval);
		sub_comm = F_MMU_INT_ID_SUB_COMM_ID(regval);
	पूर्ण अन्यथा अणु
		fault_larb = F_MMU_INT_ID_LARB_ID(regval);
	पूर्ण
	fault_larb = data->plat_data->larbid_remap[fault_larb][sub_comm];

	अगर (report_iommu_fault(&करोm->करोमुख्य, data->dev, fault_iova,
			       ग_लिखो ? IOMMU_FAULT_WRITE : IOMMU_FAULT_READ)) अणु
		dev_err_ratelimited(
			data->dev,
			"fault type=0x%x iova=0x%llx pa=0x%llx larb=%d port=%d layer=%d %s\n",
			पूर्णांक_state, fault_iova, fault_pa, fault_larb, fault_port,
			layer, ग_लिखो ? "write" : "read");
	पूर्ण

	/* Interrupt clear */
	regval = पढ़ोl_relaxed(data->base + REG_MMU_INT_CONTROL0);
	regval |= F_INT_CLR_BIT;
	ग_लिखोl_relaxed(regval, data->base + REG_MMU_INT_CONTROL0);

	mtk_iommu_tlb_flush_all(data);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक mtk_iommu_get_करोमुख्य_id(काष्ठा device *dev,
				   स्थिर काष्ठा mtk_iommu_plat_data *plat_data)
अणु
	स्थिर काष्ठा mtk_iommu_iova_region *rgn = plat_data->iova_region;
	स्थिर काष्ठा bus_dma_region *dma_rgn = dev->dma_range_map;
	पूर्णांक i, candidate = -1;
	dma_addr_t dma_end;

	अगर (!dma_rgn || plat_data->iova_region_nr == 1)
		वापस 0;

	dma_end = dma_rgn->dma_start + dma_rgn->size - 1;
	क्रम (i = 0; i < plat_data->iova_region_nr; i++, rgn++) अणु
		/* Best fit. */
		अगर (dma_rgn->dma_start == rgn->iova_base &&
		    dma_end == rgn->iova_base + rgn->size - 1)
			वापस i;
		/* ok अगर it is inside this region. */
		अगर (dma_rgn->dma_start >= rgn->iova_base &&
		    dma_end < rgn->iova_base + rgn->size)
			candidate = i;
	पूर्ण

	अगर (candidate >= 0)
		वापस candidate;
	dev_err(dev, "Can NOT find the iommu domain id(%pad 0x%llx).\n",
		&dma_rgn->dma_start, dma_rgn->size);
	वापस -EINVAL;
पूर्ण

अटल व्योम mtk_iommu_config(काष्ठा mtk_iommu_data *data, काष्ठा device *dev,
			     bool enable, अचिन्हित पूर्णांक करोmid)
अणु
	काष्ठा mtk_smi_larb_iommu    *larb_mmu;
	अचिन्हित पूर्णांक                 larbid, portid;
	काष्ठा iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);
	स्थिर काष्ठा mtk_iommu_iova_region *region;
	पूर्णांक i;

	क्रम (i = 0; i < fwspec->num_ids; ++i) अणु
		larbid = MTK_M4U_TO_LARB(fwspec->ids[i]);
		portid = MTK_M4U_TO_PORT(fwspec->ids[i]);

		larb_mmu = &data->larb_imu[larbid];

		region = data->plat_data->iova_region + करोmid;
		larb_mmu->bank[portid] = upper_32_bits(region->iova_base);

		dev_dbg(dev, "%s iommu for larb(%s) port %d dom %d bank %d.\n",
			enable ? "enable" : "disable", dev_name(larb_mmu->dev),
			portid, करोmid, larb_mmu->bank[portid]);

		अगर (enable)
			larb_mmu->mmu |= MTK_SMI_MMU_EN(portid);
		अन्यथा
			larb_mmu->mmu &= ~MTK_SMI_MMU_EN(portid);
	पूर्ण
पूर्ण

अटल पूर्णांक mtk_iommu_करोमुख्य_finalise(काष्ठा mtk_iommu_करोमुख्य *करोm,
				     काष्ठा mtk_iommu_data *data,
				     अचिन्हित पूर्णांक करोmid)
अणु
	स्थिर काष्ठा mtk_iommu_iova_region *region;

	/* Use the exist करोमुख्य as there is only one pgtable here. */
	अगर (data->m4u_करोm) अणु
		करोm->iop = data->m4u_करोm->iop;
		करोm->cfg = data->m4u_करोm->cfg;
		करोm->करोमुख्य.pgsize_biपंचांगap = data->m4u_करोm->cfg.pgsize_biपंचांगap;
		जाओ update_iova_region;
	पूर्ण

	करोm->cfg = (काष्ठा io_pgtable_cfg) अणु
		.quirks = IO_PGTABLE_QUIRK_ARM_NS |
			IO_PGTABLE_QUIRK_NO_PERMS |
			IO_PGTABLE_QUIRK_ARM_MTK_EXT,
		.pgsize_biपंचांगap = mtk_iommu_ops.pgsize_biपंचांगap,
		.ias = MTK_IOMMU_HAS_FLAG(data->plat_data, IOVA_34_EN) ? 34 : 32,
		.iommu_dev = data->dev,
	पूर्ण;

	अगर (MTK_IOMMU_HAS_FLAG(data->plat_data, HAS_4GB_MODE))
		करोm->cfg.oas = data->enable_4GB ? 33 : 32;
	अन्यथा
		करोm->cfg.oas = 35;

	करोm->iop = alloc_io_pgtable_ops(ARM_V7S, &करोm->cfg, data);
	अगर (!करोm->iop) अणु
		dev_err(data->dev, "Failed to alloc io pgtable\n");
		वापस -EINVAL;
	पूर्ण

	/* Update our support page sizes biपंचांगap */
	करोm->करोमुख्य.pgsize_biपंचांगap = करोm->cfg.pgsize_biपंचांगap;

update_iova_region:
	/* Update the iova region क्रम this करोमुख्य */
	region = data->plat_data->iova_region + करोmid;
	करोm->करोमुख्य.geometry.aperture_start = region->iova_base;
	करोm->करोमुख्य.geometry.aperture_end = region->iova_base + region->size - 1;
	करोm->करोमुख्य.geometry.क्रमce_aperture = true;
	वापस 0;
पूर्ण

अटल काष्ठा iommu_करोमुख्य *mtk_iommu_करोमुख्य_alloc(अचिन्हित type)
अणु
	काष्ठा mtk_iommu_करोमुख्य *करोm;

	अगर (type != IOMMU_DOMAIN_DMA)
		वापस शून्य;

	करोm = kzalloc(माप(*करोm), GFP_KERNEL);
	अगर (!करोm)
		वापस शून्य;

	अगर (iommu_get_dma_cookie(&करोm->करोमुख्य)) अणु
		kमुक्त(करोm);
		वापस शून्य;
	पूर्ण

	वापस &करोm->करोमुख्य;
पूर्ण

अटल व्योम mtk_iommu_करोमुख्य_मुक्त(काष्ठा iommu_करोमुख्य *करोमुख्य)
अणु
	iommu_put_dma_cookie(करोमुख्य);
	kमुक्त(to_mtk_करोमुख्य(करोमुख्य));
पूर्ण

अटल पूर्णांक mtk_iommu_attach_device(काष्ठा iommu_करोमुख्य *करोमुख्य,
				   काष्ठा device *dev)
अणु
	काष्ठा mtk_iommu_data *data = dev_iommu_priv_get(dev);
	काष्ठा mtk_iommu_करोमुख्य *करोm = to_mtk_करोमुख्य(करोमुख्य);
	काष्ठा device *m4udev = data->dev;
	पूर्णांक ret, करोmid;

	करोmid = mtk_iommu_get_करोमुख्य_id(dev, data->plat_data);
	अगर (करोmid < 0)
		वापस करोmid;

	अगर (!करोm->data) अणु
		अगर (mtk_iommu_करोमुख्य_finalise(करोm, data, करोmid))
			वापस -ENODEV;
		करोm->data = data;
	पूर्ण

	अगर (!data->m4u_करोm) अणु /* Initialize the M4U HW */
		ret = pm_runसमय_resume_and_get(m4udev);
		अगर (ret < 0)
			वापस ret;

		ret = mtk_iommu_hw_init(data);
		अगर (ret) अणु
			pm_runसमय_put(m4udev);
			वापस ret;
		पूर्ण
		data->m4u_करोm = करोm;
		ग_लिखोl(करोm->cfg.arm_v7s_cfg.ttbr & MMU_PT_ADDR_MASK,
		       data->base + REG_MMU_PT_BASE_ADDR);

		pm_runसमय_put(m4udev);
	पूर्ण

	mtk_iommu_config(data, dev, true, करोmid);
	वापस 0;
पूर्ण

अटल व्योम mtk_iommu_detach_device(काष्ठा iommu_करोमुख्य *करोमुख्य,
				    काष्ठा device *dev)
अणु
	काष्ठा mtk_iommu_data *data = dev_iommu_priv_get(dev);

	mtk_iommu_config(data, dev, false, 0);
पूर्ण

अटल पूर्णांक mtk_iommu_map(काष्ठा iommu_करोमुख्य *करोमुख्य, अचिन्हित दीर्घ iova,
			 phys_addr_t paddr, माप_प्रकार size, पूर्णांक prot, gfp_t gfp)
अणु
	काष्ठा mtk_iommu_करोमुख्य *करोm = to_mtk_करोमुख्य(करोमुख्य);

	/* The "4GB mode" M4U physically can not use the lower remap of Dram. */
	अगर (करोm->data->enable_4GB)
		paddr |= BIT_ULL(32);

	/* Synchronize with the tlb_lock */
	वापस करोm->iop->map(करोm->iop, iova, paddr, size, prot, gfp);
पूर्ण

अटल माप_प्रकार mtk_iommu_unmap(काष्ठा iommu_करोमुख्य *करोमुख्य,
			      अचिन्हित दीर्घ iova, माप_प्रकार size,
			      काष्ठा iommu_iotlb_gather *gather)
अणु
	काष्ठा mtk_iommu_करोमुख्य *करोm = to_mtk_करोमुख्य(करोमुख्य);
	अचिन्हित दीर्घ end = iova + size - 1;

	अगर (gather->start > iova)
		gather->start = iova;
	अगर (gather->end < end)
		gather->end = end;
	वापस करोm->iop->unmap(करोm->iop, iova, size, gather);
पूर्ण

अटल व्योम mtk_iommu_flush_iotlb_all(काष्ठा iommu_करोमुख्य *करोमुख्य)
अणु
	काष्ठा mtk_iommu_करोमुख्य *करोm = to_mtk_करोमुख्य(करोमुख्य);

	mtk_iommu_tlb_flush_all(करोm->data);
पूर्ण

अटल व्योम mtk_iommu_iotlb_sync(काष्ठा iommu_करोमुख्य *करोमुख्य,
				 काष्ठा iommu_iotlb_gather *gather)
अणु
	काष्ठा mtk_iommu_करोमुख्य *करोm = to_mtk_करोमुख्य(करोमुख्य);
	माप_प्रकार length = gather->end - gather->start + 1;

	mtk_iommu_tlb_flush_range_sync(gather->start, length, gather->pgsize,
				       करोm->data);
पूर्ण

अटल व्योम mtk_iommu_sync_map(काष्ठा iommu_करोमुख्य *करोमुख्य, अचिन्हित दीर्घ iova,
			       माप_प्रकार size)
अणु
	काष्ठा mtk_iommu_करोमुख्य *करोm = to_mtk_करोमुख्य(करोमुख्य);

	mtk_iommu_tlb_flush_range_sync(iova, size, size, करोm->data);
पूर्ण

अटल phys_addr_t mtk_iommu_iova_to_phys(काष्ठा iommu_करोमुख्य *करोमुख्य,
					  dma_addr_t iova)
अणु
	काष्ठा mtk_iommu_करोमुख्य *करोm = to_mtk_करोमुख्य(करोमुख्य);
	phys_addr_t pa;

	pa = करोm->iop->iova_to_phys(करोm->iop, iova);
	अगर (करोm->data->enable_4GB && pa >= MTK_IOMMU_4GB_MODE_REMAP_BASE)
		pa &= ~BIT_ULL(32);

	वापस pa;
पूर्ण

अटल काष्ठा iommu_device *mtk_iommu_probe_device(काष्ठा device *dev)
अणु
	काष्ठा iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);
	काष्ठा mtk_iommu_data *data;

	अगर (!fwspec || fwspec->ops != &mtk_iommu_ops)
		वापस ERR_PTR(-ENODEV); /* Not a iommu client device */

	data = dev_iommu_priv_get(dev);

	वापस &data->iommu;
पूर्ण

अटल व्योम mtk_iommu_release_device(काष्ठा device *dev)
अणु
	काष्ठा iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);

	अगर (!fwspec || fwspec->ops != &mtk_iommu_ops)
		वापस;

	iommu_fwspec_मुक्त(dev);
पूर्ण

अटल काष्ठा iommu_group *mtk_iommu_device_group(काष्ठा device *dev)
अणु
	काष्ठा mtk_iommu_data *data = mtk_iommu_get_m4u_data();
	काष्ठा iommu_group *group;
	पूर्णांक करोmid;

	अगर (!data)
		वापस ERR_PTR(-ENODEV);

	करोmid = mtk_iommu_get_करोमुख्य_id(dev, data->plat_data);
	अगर (करोmid < 0)
		वापस ERR_PTR(करोmid);

	group = data->m4u_group[करोmid];
	अगर (!group) अणु
		group = iommu_group_alloc();
		अगर (!IS_ERR(group))
			data->m4u_group[करोmid] = group;
	पूर्ण अन्यथा अणु
		iommu_group_ref_get(group);
	पूर्ण
	वापस group;
पूर्ण

अटल पूर्णांक mtk_iommu_of_xlate(काष्ठा device *dev, काष्ठा of_phandle_args *args)
अणु
	काष्ठा platक्रमm_device *m4updev;

	अगर (args->args_count != 1) अणु
		dev_err(dev, "invalid #iommu-cells(%d) property for IOMMU\n",
			args->args_count);
		वापस -EINVAL;
	पूर्ण

	अगर (!dev_iommu_priv_get(dev)) अणु
		/* Get the m4u device */
		m4updev = of_find_device_by_node(args->np);
		अगर (WARN_ON(!m4updev))
			वापस -EINVAL;

		dev_iommu_priv_set(dev, platक्रमm_get_drvdata(m4updev));
	पूर्ण

	वापस iommu_fwspec_add_ids(dev, args->args, 1);
पूर्ण

अटल व्योम mtk_iommu_get_resv_regions(काष्ठा device *dev,
				       काष्ठा list_head *head)
अणु
	काष्ठा mtk_iommu_data *data = dev_iommu_priv_get(dev);
	अचिन्हित पूर्णांक करोmid = mtk_iommu_get_करोमुख्य_id(dev, data->plat_data), i;
	स्थिर काष्ठा mtk_iommu_iova_region *resv, *curकरोm;
	काष्ठा iommu_resv_region *region;
	पूर्णांक prot = IOMMU_WRITE | IOMMU_READ;

	अगर ((पूर्णांक)करोmid < 0)
		वापस;
	curकरोm = data->plat_data->iova_region + करोmid;
	क्रम (i = 0; i < data->plat_data->iova_region_nr; i++) अणु
		resv = data->plat_data->iova_region + i;

		/* Only reserve when the region is inside the current करोमुख्य */
		अगर (resv->iova_base <= curकरोm->iova_base ||
		    resv->iova_base + resv->size >= curकरोm->iova_base + curकरोm->size)
			जारी;

		region = iommu_alloc_resv_region(resv->iova_base, resv->size,
						 prot, IOMMU_RESV_RESERVED);
		अगर (!region)
			वापस;

		list_add_tail(&region->list, head);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा iommu_ops mtk_iommu_ops = अणु
	.करोमुख्य_alloc	= mtk_iommu_करोमुख्य_alloc,
	.करोमुख्य_मुक्त	= mtk_iommu_करोमुख्य_मुक्त,
	.attach_dev	= mtk_iommu_attach_device,
	.detach_dev	= mtk_iommu_detach_device,
	.map		= mtk_iommu_map,
	.unmap		= mtk_iommu_unmap,
	.flush_iotlb_all = mtk_iommu_flush_iotlb_all,
	.iotlb_sync	= mtk_iommu_iotlb_sync,
	.iotlb_sync_map	= mtk_iommu_sync_map,
	.iova_to_phys	= mtk_iommu_iova_to_phys,
	.probe_device	= mtk_iommu_probe_device,
	.release_device	= mtk_iommu_release_device,
	.device_group	= mtk_iommu_device_group,
	.of_xlate	= mtk_iommu_of_xlate,
	.get_resv_regions = mtk_iommu_get_resv_regions,
	.put_resv_regions = generic_iommu_put_resv_regions,
	.pgsize_biपंचांगap	= SZ_4K | SZ_64K | SZ_1M | SZ_16M,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक mtk_iommu_hw_init(स्थिर काष्ठा mtk_iommu_data *data)
अणु
	u32 regval;

	अगर (data->plat_data->m4u_plat == M4U_MT8173) अणु
		regval = F_MMU_PREFETCH_RT_REPLACE_MOD |
			 F_MMU_TF_PROT_TO_PROGRAM_ADDR_MT8173;
	पूर्ण अन्यथा अणु
		regval = पढ़ोl_relaxed(data->base + REG_MMU_CTRL_REG);
		regval |= F_MMU_TF_PROT_TO_PROGRAM_ADDR;
	पूर्ण
	ग_लिखोl_relaxed(regval, data->base + REG_MMU_CTRL_REG);

	regval = F_L2_MULIT_HIT_EN |
		F_TABLE_WALK_FAULT_INT_EN |
		F_PREETCH_FIFO_OVERFLOW_INT_EN |
		F_MISS_FIFO_OVERFLOW_INT_EN |
		F_PREFETCH_FIFO_ERR_INT_EN |
		F_MISS_FIFO_ERR_INT_EN;
	ग_लिखोl_relaxed(regval, data->base + REG_MMU_INT_CONTROL0);

	regval = F_INT_TRANSLATION_FAULT |
		F_INT_MAIN_MULTI_HIT_FAULT |
		F_INT_INVALID_PA_FAULT |
		F_INT_ENTRY_REPLACEMENT_FAULT |
		F_INT_TLB_MISS_FAULT |
		F_INT_MISS_TRANSACTION_FIFO_FAULT |
		F_INT_PRETETCH_TRANSATION_FIFO_FAULT;
	ग_लिखोl_relaxed(regval, data->base + REG_MMU_INT_MAIN_CONTROL);

	अगर (MTK_IOMMU_HAS_FLAG(data->plat_data, HAS_LEGACY_IVRP_PADDR))
		regval = (data->protect_base >> 1) | (data->enable_4GB << 31);
	अन्यथा
		regval = lower_32_bits(data->protect_base) |
			 upper_32_bits(data->protect_base);
	ग_लिखोl_relaxed(regval, data->base + REG_MMU_IVRP_PADDR);

	अगर (data->enable_4GB &&
	    MTK_IOMMU_HAS_FLAG(data->plat_data, HAS_VLD_PA_RNG)) अणु
		/*
		 * If 4GB mode is enabled, the validate PA range is from
		 * 0x1_0000_0000 to 0x1_ffff_ffff. here record bit[32:30].
		 */
		regval = F_MMU_VLD_PA_RNG(7, 4);
		ग_लिखोl_relaxed(regval, data->base + REG_MMU_VLD_PA_RNG);
	पूर्ण
	ग_लिखोl_relaxed(0, data->base + REG_MMU_DCM_DIS);
	अगर (MTK_IOMMU_HAS_FLAG(data->plat_data, WR_THROT_EN)) अणु
		/* ग_लिखो command throttling mode */
		regval = पढ़ोl_relaxed(data->base + REG_MMU_WR_LEN_CTRL);
		regval &= ~F_MMU_WR_THROT_DIS_MASK;
		ग_लिखोl_relaxed(regval, data->base + REG_MMU_WR_LEN_CTRL);
	पूर्ण

	अगर (MTK_IOMMU_HAS_FLAG(data->plat_data, RESET_AXI)) अणु
		/* The रेजिस्टर is called STANDARD_AXI_MODE in this हाल */
		regval = 0;
	पूर्ण अन्यथा अणु
		regval = पढ़ोl_relaxed(data->base + REG_MMU_MISC_CTRL);
		regval &= ~F_MMU_STANDARD_AXI_MODE_MASK;
		अगर (MTK_IOMMU_HAS_FLAG(data->plat_data, OUT_ORDER_WR_EN))
			regval &= ~F_MMU_IN_ORDER_WR_EN_MASK;
	पूर्ण
	ग_लिखोl_relaxed(regval, data->base + REG_MMU_MISC_CTRL);

	अगर (devm_request_irq(data->dev, data->irq, mtk_iommu_isr, 0,
			     dev_name(data->dev), (व्योम *)data)) अणु
		ग_लिखोl_relaxed(0, data->base + REG_MMU_PT_BASE_ADDR);
		dev_err(data->dev, "Failed @ IRQ-%d Request\n", data->irq);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा component_master_ops mtk_iommu_com_ops = अणु
	.bind		= mtk_iommu_bind,
	.unbind		= mtk_iommu_unbind,
पूर्ण;

अटल पूर्णांक mtk_iommu_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mtk_iommu_data   *data;
	काष्ठा device           *dev = &pdev->dev;
	काष्ठा device_node	*larbnode, *smicomm_node;
	काष्ठा platक्रमm_device	*plarbdev;
	काष्ठा device_link	*link;
	काष्ठा resource         *res;
	resource_माप_प्रकार		ioaddr;
	काष्ठा component_match  *match = शून्य;
	काष्ठा regmap		*infracfg;
	व्योम                    *protect;
	पूर्णांक                     i, larb_nr, ret;
	u32			val;
	अक्षर                    *p;

	data = devm_kzalloc(dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;
	data->dev = dev;
	data->plat_data = of_device_get_match_data(dev);

	/* Protect memory. HW will access here जबतक translation fault.*/
	protect = devm_kzalloc(dev, MTK_PROTECT_PA_ALIGN * 2, GFP_KERNEL);
	अगर (!protect)
		वापस -ENOMEM;
	data->protect_base = ALIGN(virt_to_phys(protect), MTK_PROTECT_PA_ALIGN);

	अगर (MTK_IOMMU_HAS_FLAG(data->plat_data, HAS_4GB_MODE)) अणु
		चयन (data->plat_data->m4u_plat) अणु
		हाल M4U_MT2712:
			p = "mediatek,mt2712-infracfg";
			अवरोध;
		हाल M4U_MT8173:
			p = "mediatek,mt8173-infracfg";
			अवरोध;
		शेष:
			p = शून्य;
		पूर्ण

		infracfg = syscon_regmap_lookup_by_compatible(p);

		अगर (IS_ERR(infracfg))
			वापस PTR_ERR(infracfg);

		ret = regmap_पढ़ो(infracfg, REG_INFRA_MISC, &val);
		अगर (ret)
			वापस ret;
		data->enable_4GB = !!(val & F_DDR_4GB_SUPPORT_EN);
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	data->base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(data->base))
		वापस PTR_ERR(data->base);
	ioaddr = res->start;

	data->irq = platक्रमm_get_irq(pdev, 0);
	अगर (data->irq < 0)
		वापस data->irq;

	अगर (MTK_IOMMU_HAS_FLAG(data->plat_data, HAS_BCLK)) अणु
		data->bclk = devm_clk_get(dev, "bclk");
		अगर (IS_ERR(data->bclk))
			वापस PTR_ERR(data->bclk);
	पूर्ण

	larb_nr = of_count_phandle_with_args(dev->of_node,
					     "mediatek,larbs", शून्य);
	अगर (larb_nr < 0)
		वापस larb_nr;

	क्रम (i = 0; i < larb_nr; i++) अणु
		u32 id;

		larbnode = of_parse_phandle(dev->of_node, "mediatek,larbs", i);
		अगर (!larbnode)
			वापस -EINVAL;

		अगर (!of_device_is_available(larbnode)) अणु
			of_node_put(larbnode);
			जारी;
		पूर्ण

		ret = of_property_पढ़ो_u32(larbnode, "mediatek,larb-id", &id);
		अगर (ret)/* The id is consecutive अगर there is no this property */
			id = i;

		plarbdev = of_find_device_by_node(larbnode);
		अगर (!plarbdev) अणु
			of_node_put(larbnode);
			वापस -EPROBE_DEFER;
		पूर्ण
		data->larb_imu[id].dev = &plarbdev->dev;

		component_match_add_release(dev, &match, release_of,
					    compare_of, larbnode);
	पूर्ण

	/* Get smi-common dev from the last larb. */
	smicomm_node = of_parse_phandle(larbnode, "mediatek,smi", 0);
	अगर (!smicomm_node)
		वापस -EINVAL;

	plarbdev = of_find_device_by_node(smicomm_node);
	of_node_put(smicomm_node);
	data->smicomm_dev = &plarbdev->dev;

	pm_runसमय_enable(dev);

	link = device_link_add(data->smicomm_dev, dev,
			DL_FLAG_STATELESS | DL_FLAG_PM_RUNTIME);
	अगर (!link) अणु
		dev_err(dev, "Unable to link %s.\n", dev_name(data->smicomm_dev));
		ret = -EINVAL;
		जाओ out_runसमय_disable;
	पूर्ण

	platक्रमm_set_drvdata(pdev, data);

	ret = iommu_device_sysfs_add(&data->iommu, dev, शून्य,
				     "mtk-iommu.%pa", &ioaddr);
	अगर (ret)
		जाओ out_link_हटाओ;

	ret = iommu_device_रेजिस्टर(&data->iommu, &mtk_iommu_ops, dev);
	अगर (ret)
		जाओ out_sysfs_हटाओ;

	spin_lock_init(&data->tlb_lock);
	list_add_tail(&data->list, &m4ulist);

	अगर (!iommu_present(&platक्रमm_bus_type)) अणु
		ret = bus_set_iommu(&platक्रमm_bus_type, &mtk_iommu_ops);
		अगर (ret)
			जाओ out_list_del;
	पूर्ण

	ret = component_master_add_with_match(dev, &mtk_iommu_com_ops, match);
	अगर (ret)
		जाओ out_bus_set_null;
	वापस ret;

out_bus_set_null:
	bus_set_iommu(&platक्रमm_bus_type, शून्य);
out_list_del:
	list_del(&data->list);
	iommu_device_unरेजिस्टर(&data->iommu);
out_sysfs_हटाओ:
	iommu_device_sysfs_हटाओ(&data->iommu);
out_link_हटाओ:
	device_link_हटाओ(data->smicomm_dev, dev);
out_runसमय_disable:
	pm_runसमय_disable(dev);
	वापस ret;
पूर्ण

अटल पूर्णांक mtk_iommu_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mtk_iommu_data *data = platक्रमm_get_drvdata(pdev);

	iommu_device_sysfs_हटाओ(&data->iommu);
	iommu_device_unरेजिस्टर(&data->iommu);

	अगर (iommu_present(&platक्रमm_bus_type))
		bus_set_iommu(&platक्रमm_bus_type, शून्य);

	clk_disable_unprepare(data->bclk);
	device_link_हटाओ(data->smicomm_dev, &pdev->dev);
	pm_runसमय_disable(&pdev->dev);
	devm_मुक्त_irq(&pdev->dev, data->irq, data);
	component_master_del(&pdev->dev, &mtk_iommu_com_ops);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused mtk_iommu_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा mtk_iommu_data *data = dev_get_drvdata(dev);
	काष्ठा mtk_iommu_suspend_reg *reg = &data->reg;
	व्योम __iomem *base = data->base;

	reg->wr_len_ctrl = पढ़ोl_relaxed(base + REG_MMU_WR_LEN_CTRL);
	reg->misc_ctrl = पढ़ोl_relaxed(base + REG_MMU_MISC_CTRL);
	reg->dcm_dis = पढ़ोl_relaxed(base + REG_MMU_DCM_DIS);
	reg->ctrl_reg = पढ़ोl_relaxed(base + REG_MMU_CTRL_REG);
	reg->पूर्णांक_control0 = पढ़ोl_relaxed(base + REG_MMU_INT_CONTROL0);
	reg->पूर्णांक_मुख्य_control = पढ़ोl_relaxed(base + REG_MMU_INT_MAIN_CONTROL);
	reg->ivrp_paddr = पढ़ोl_relaxed(base + REG_MMU_IVRP_PADDR);
	reg->vld_pa_rng = पढ़ोl_relaxed(base + REG_MMU_VLD_PA_RNG);
	clk_disable_unprepare(data->bclk);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused mtk_iommu_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा mtk_iommu_data *data = dev_get_drvdata(dev);
	काष्ठा mtk_iommu_suspend_reg *reg = &data->reg;
	काष्ठा mtk_iommu_करोमुख्य *m4u_करोm = data->m4u_करोm;
	व्योम __iomem *base = data->base;
	पूर्णांक ret;

	ret = clk_prepare_enable(data->bclk);
	अगर (ret) अणु
		dev_err(data->dev, "Failed to enable clk(%d) in resume\n", ret);
		वापस ret;
	पूर्ण

	/*
	 * Uppon first resume, only enable the clk and वापस, since the values of the
	 * रेजिस्टरs are not yet set.
	 */
	अगर (!m4u_करोm)
		वापस 0;

	ग_लिखोl_relaxed(reg->wr_len_ctrl, base + REG_MMU_WR_LEN_CTRL);
	ग_लिखोl_relaxed(reg->misc_ctrl, base + REG_MMU_MISC_CTRL);
	ग_लिखोl_relaxed(reg->dcm_dis, base + REG_MMU_DCM_DIS);
	ग_लिखोl_relaxed(reg->ctrl_reg, base + REG_MMU_CTRL_REG);
	ग_लिखोl_relaxed(reg->पूर्णांक_control0, base + REG_MMU_INT_CONTROL0);
	ग_लिखोl_relaxed(reg->पूर्णांक_मुख्य_control, base + REG_MMU_INT_MAIN_CONTROL);
	ग_लिखोl_relaxed(reg->ivrp_paddr, base + REG_MMU_IVRP_PADDR);
	ग_लिखोl_relaxed(reg->vld_pa_rng, base + REG_MMU_VLD_PA_RNG);
	ग_लिखोl(m4u_करोm->cfg.arm_v7s_cfg.ttbr & MMU_PT_ADDR_MASK, base + REG_MMU_PT_BASE_ADDR);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops mtk_iommu_pm_ops = अणु
	SET_RUNTIME_PM_OPS(mtk_iommu_runसमय_suspend, mtk_iommu_runसमय_resume, शून्य)
	SET_LATE_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				     pm_runसमय_क्रमce_resume)
पूर्ण;

अटल स्थिर काष्ठा mtk_iommu_plat_data mt2712_data = अणु
	.m4u_plat     = M4U_MT2712,
	.flags        = HAS_4GB_MODE | HAS_BCLK | HAS_VLD_PA_RNG,
	.inv_sel_reg  = REG_MMU_INV_SEL_GEN1,
	.iova_region  = single_करोमुख्य,
	.iova_region_nr = ARRAY_SIZE(single_करोमुख्य),
	.larbid_remap = अणुअणु0पूर्ण, अणु1पूर्ण, अणु2पूर्ण, अणु3पूर्ण, अणु4पूर्ण, अणु5पूर्ण, अणु6पूर्ण, अणु7पूर्णपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mtk_iommu_plat_data mt6779_data = अणु
	.m4u_plat      = M4U_MT6779,
	.flags         = HAS_SUB_COMM | OUT_ORDER_WR_EN | WR_THROT_EN,
	.inv_sel_reg   = REG_MMU_INV_SEL_GEN2,
	.iova_region   = single_करोमुख्य,
	.iova_region_nr = ARRAY_SIZE(single_करोमुख्य),
	.larbid_remap  = अणुअणु0पूर्ण, अणु1पूर्ण, अणु2पूर्ण, अणु3पूर्ण, अणु5पूर्ण, अणु7, 8पूर्ण, अणु10पूर्ण, अणु9पूर्णपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mtk_iommu_plat_data mt8167_data = अणु
	.m4u_plat     = M4U_MT8167,
	.flags        = RESET_AXI | HAS_LEGACY_IVRP_PADDR,
	.inv_sel_reg  = REG_MMU_INV_SEL_GEN1,
	.iova_region  = single_करोमुख्य,
	.iova_region_nr = ARRAY_SIZE(single_करोमुख्य),
	.larbid_remap = अणुअणु0पूर्ण, अणु1पूर्ण, अणु2पूर्णपूर्ण, /* Linear mapping. */
पूर्ण;

अटल स्थिर काष्ठा mtk_iommu_plat_data mt8173_data = अणु
	.m4u_plat     = M4U_MT8173,
	.flags	      = HAS_4GB_MODE | HAS_BCLK | RESET_AXI |
			HAS_LEGACY_IVRP_PADDR,
	.inv_sel_reg  = REG_MMU_INV_SEL_GEN1,
	.iova_region  = single_करोमुख्य,
	.iova_region_nr = ARRAY_SIZE(single_करोमुख्य),
	.larbid_remap = अणुअणु0पूर्ण, अणु1पूर्ण, अणु2पूर्ण, अणु3पूर्ण, अणु4पूर्ण, अणु5पूर्णपूर्ण, /* Linear mapping. */
पूर्ण;

अटल स्थिर काष्ठा mtk_iommu_plat_data mt8183_data = अणु
	.m4u_plat     = M4U_MT8183,
	.flags        = RESET_AXI,
	.inv_sel_reg  = REG_MMU_INV_SEL_GEN1,
	.iova_region  = single_करोमुख्य,
	.iova_region_nr = ARRAY_SIZE(single_करोमुख्य),
	.larbid_remap = अणुअणु0पूर्ण, अणु4पूर्ण, अणु5पूर्ण, अणु6पूर्ण, अणु7पूर्ण, अणु2पूर्ण, अणु3पूर्ण, अणु1पूर्णपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mtk_iommu_plat_data mt8192_data = अणु
	.m4u_plat       = M4U_MT8192,
	.flags          = HAS_BCLK | HAS_SUB_COMM | OUT_ORDER_WR_EN |
			  WR_THROT_EN | IOVA_34_EN,
	.inv_sel_reg    = REG_MMU_INV_SEL_GEN2,
	.iova_region    = mt8192_multi_करोm,
	.iova_region_nr = ARRAY_SIZE(mt8192_multi_करोm),
	.larbid_remap   = अणुअणु0पूर्ण, अणु1पूर्ण, अणु4, 5पूर्ण, अणु7पूर्ण, अणु2पूर्ण, अणु9, 11, 19, 20पूर्ण,
			   अणु0, 14, 16पूर्ण, अणु0, 13, 18, 17पूर्णपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा of_device_id mtk_iommu_of_ids[] = अणु
	अणु .compatible = "mediatek,mt2712-m4u", .data = &mt2712_dataपूर्ण,
	अणु .compatible = "mediatek,mt6779-m4u", .data = &mt6779_dataपूर्ण,
	अणु .compatible = "mediatek,mt8167-m4u", .data = &mt8167_dataपूर्ण,
	अणु .compatible = "mediatek,mt8173-m4u", .data = &mt8173_dataपूर्ण,
	अणु .compatible = "mediatek,mt8183-m4u", .data = &mt8183_dataपूर्ण,
	अणु .compatible = "mediatek,mt8192-m4u", .data = &mt8192_dataपूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver mtk_iommu_driver = अणु
	.probe	= mtk_iommu_probe,
	.हटाओ	= mtk_iommu_हटाओ,
	.driver	= अणु
		.name = "mtk-iommu",
		.of_match_table = mtk_iommu_of_ids,
		.pm = &mtk_iommu_pm_ops,
	पूर्ण
पूर्ण;
module_platक्रमm_driver(mtk_iommu_driver);

MODULE_DESCRIPTION("IOMMU API for MediaTek M4U implementations");
MODULE_LICENSE("GPL v2");
