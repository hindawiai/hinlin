<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * IOMMU API क्रम MTK architected m4u v1 implementations
 *
 * Copyright (c) 2015-2016 MediaTek Inc.
 * Author: Honghui Zhang <honghui.zhang@mediatek.com>
 *
 * Based on driver/iommu/mtk_iommu.c
 */
#समावेश <linux/memblock.h>
#समावेश <linux/bug.h>
#समावेश <linux/clk.h>
#समावेश <linux/component.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dma-iommu.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/iommu.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_iommu.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <यंत्र/barrier.h>
#समावेश <यंत्र/dma-iommu.h>
#समावेश <linux/init.h>
#समावेश <dt-bindings/memory/mt2701-larb-port.h>
#समावेश <soc/mediatek/smi.h>
#समावेश "mtk_iommu.h"

#घोषणा REG_MMU_PT_BASE_ADDR			0x000

#घोषणा F_ALL_INVLD				0x2
#घोषणा F_MMU_INV_RANGE				0x1
#घोषणा F_INVLD_EN0				BIT(0)
#घोषणा F_INVLD_EN1				BIT(1)

#घोषणा F_MMU_FAULT_VA_MSK			0xfffff000
#घोषणा MTK_PROTECT_PA_ALIGN			128

#घोषणा REG_MMU_CTRL_REG			0x210
#घोषणा F_MMU_CTRL_COHERENT_EN			BIT(8)
#घोषणा REG_MMU_IVRP_PADDR			0x214
#घोषणा REG_MMU_INT_CONTROL			0x220
#घोषणा F_INT_TRANSLATION_FAULT			BIT(0)
#घोषणा F_INT_MAIN_MULTI_HIT_FAULT		BIT(1)
#घोषणा F_INT_INVALID_PA_FAULT			BIT(2)
#घोषणा F_INT_ENTRY_REPLACEMENT_FAULT		BIT(3)
#घोषणा F_INT_TABLE_WALK_FAULT			BIT(4)
#घोषणा F_INT_TLB_MISS_FAULT			BIT(5)
#घोषणा F_INT_PFH_DMA_FIFO_OVERFLOW		BIT(6)
#घोषणा F_INT_MISS_DMA_FIFO_OVERFLOW		BIT(7)

#घोषणा F_MMU_TF_PROTECT_SEL(prot)		(((prot) & 0x3) << 5)
#घोषणा F_INT_CLR_BIT				BIT(12)

#घोषणा REG_MMU_FAULT_ST			0x224
#घोषणा REG_MMU_FAULT_VA			0x228
#घोषणा REG_MMU_INVLD_PA			0x22C
#घोषणा REG_MMU_INT_ID				0x388
#घोषणा REG_MMU_INVALIDATE			0x5c0
#घोषणा REG_MMU_INVLD_START_A			0x5c4
#घोषणा REG_MMU_INVLD_END_A			0x5c8

#घोषणा REG_MMU_INV_SEL				0x5d8
#घोषणा REG_MMU_STANDARD_AXI_MODE		0x5e8

#घोषणा REG_MMU_DCM				0x5f0
#घोषणा F_MMU_DCM_ON				BIT(1)
#घोषणा REG_MMU_CPE_DONE			0x60c
#घोषणा F_DESC_VALID				0x2
#घोषणा F_DESC_NONSEC				BIT(3)
#घोषणा MT2701_M4U_TF_LARB(TF)			(6 - (((TF) >> 13) & 0x7))
#घोषणा MT2701_M4U_TF_PORT(TF)			(((TF) >> 8) & 0xF)
/* MTK generation one iommu HW only support 4K size mapping */
#घोषणा MT2701_IOMMU_PAGE_SHIFT			12
#घोषणा MT2701_IOMMU_PAGE_SIZE			(1UL << MT2701_IOMMU_PAGE_SHIFT)

/*
 * MTK m4u support 4GB iova address space, and only support 4K page
 * mapping. So the pagetable size should be exactly as 4M.
 */
#घोषणा M2701_IOMMU_PGT_SIZE			SZ_4M

काष्ठा mtk_iommu_करोमुख्य अणु
	spinlock_t			pgtlock; /* lock क्रम page table */
	काष्ठा iommu_करोमुख्य		करोमुख्य;
	u32				*pgt_va;
	dma_addr_t			pgt_pa;
	काष्ठा mtk_iommu_data		*data;
पूर्ण;

अटल काष्ठा mtk_iommu_करोमुख्य *to_mtk_करोमुख्य(काष्ठा iommu_करोमुख्य *करोm)
अणु
	वापस container_of(करोm, काष्ठा mtk_iommu_करोमुख्य, करोमुख्य);
पूर्ण

अटल स्थिर पूर्णांक mt2701_m4u_in_larb[] = अणु
	LARB0_PORT_OFFSET, LARB1_PORT_OFFSET,
	LARB2_PORT_OFFSET, LARB3_PORT_OFFSET
पूर्ण;

अटल अंतरभूत पूर्णांक mt2701_m4u_to_larb(पूर्णांक id)
अणु
	पूर्णांक i;

	क्रम (i = ARRAY_SIZE(mt2701_m4u_in_larb) - 1; i >= 0; i--)
		अगर ((id) >= mt2701_m4u_in_larb[i])
			वापस i;

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक mt2701_m4u_to_port(पूर्णांक id)
अणु
	पूर्णांक larb = mt2701_m4u_to_larb(id);

	वापस id - mt2701_m4u_in_larb[larb];
पूर्ण

अटल व्योम mtk_iommu_tlb_flush_all(काष्ठा mtk_iommu_data *data)
अणु
	ग_लिखोl_relaxed(F_INVLD_EN1 | F_INVLD_EN0,
			data->base + REG_MMU_INV_SEL);
	ग_लिखोl_relaxed(F_ALL_INVLD, data->base + REG_MMU_INVALIDATE);
	wmb(); /* Make sure the tlb flush all करोne */
पूर्ण

अटल व्योम mtk_iommu_tlb_flush_range(काष्ठा mtk_iommu_data *data,
				अचिन्हित दीर्घ iova, माप_प्रकार size)
अणु
	पूर्णांक ret;
	u32 पंचांगp;

	ग_लिखोl_relaxed(F_INVLD_EN1 | F_INVLD_EN0,
		data->base + REG_MMU_INV_SEL);
	ग_लिखोl_relaxed(iova & F_MMU_FAULT_VA_MSK,
		data->base + REG_MMU_INVLD_START_A);
	ग_लिखोl_relaxed((iova + size - 1) & F_MMU_FAULT_VA_MSK,
		data->base + REG_MMU_INVLD_END_A);
	ग_लिखोl_relaxed(F_MMU_INV_RANGE, data->base + REG_MMU_INVALIDATE);

	ret = पढ़ोl_poll_समयout_atomic(data->base + REG_MMU_CPE_DONE,
				पंचांगp, पंचांगp != 0, 10, 100000);
	अगर (ret) अणु
		dev_warn(data->dev,
			 "Partial TLB flush timed out, falling back to full flush\n");
		mtk_iommu_tlb_flush_all(data);
	पूर्ण
	/* Clear the CPE status */
	ग_लिखोl_relaxed(0, data->base + REG_MMU_CPE_DONE);
पूर्ण

अटल irqवापस_t mtk_iommu_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mtk_iommu_data *data = dev_id;
	काष्ठा mtk_iommu_करोमुख्य *करोm = data->m4u_करोm;
	u32 पूर्णांक_state, regval, fault_iova, fault_pa;
	अचिन्हित पूर्णांक fault_larb, fault_port;

	/* Read error inक्रमmation from रेजिस्टरs */
	पूर्णांक_state = पढ़ोl_relaxed(data->base + REG_MMU_FAULT_ST);
	fault_iova = पढ़ोl_relaxed(data->base + REG_MMU_FAULT_VA);

	fault_iova &= F_MMU_FAULT_VA_MSK;
	fault_pa = पढ़ोl_relaxed(data->base + REG_MMU_INVLD_PA);
	regval = पढ़ोl_relaxed(data->base + REG_MMU_INT_ID);
	fault_larb = MT2701_M4U_TF_LARB(regval);
	fault_port = MT2701_M4U_TF_PORT(regval);

	/*
	 * MTK v1 iommu HW could not determine whether the fault is पढ़ो or
	 * ग_लिखो fault, report as पढ़ो fault.
	 */
	अगर (report_iommu_fault(&करोm->करोमुख्य, data->dev, fault_iova,
			IOMMU_FAULT_READ))
		dev_err_ratelimited(data->dev,
			"fault type=0x%x iova=0x%x pa=0x%x larb=%d port=%d\n",
			पूर्णांक_state, fault_iova, fault_pa,
			fault_larb, fault_port);

	/* Interrupt clear */
	regval = पढ़ोl_relaxed(data->base + REG_MMU_INT_CONTROL);
	regval |= F_INT_CLR_BIT;
	ग_लिखोl_relaxed(regval, data->base + REG_MMU_INT_CONTROL);

	mtk_iommu_tlb_flush_all(data);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम mtk_iommu_config(काष्ठा mtk_iommu_data *data,
			     काष्ठा device *dev, bool enable)
अणु
	काष्ठा mtk_smi_larb_iommu    *larb_mmu;
	अचिन्हित पूर्णांक                 larbid, portid;
	काष्ठा iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);
	पूर्णांक i;

	क्रम (i = 0; i < fwspec->num_ids; ++i) अणु
		larbid = mt2701_m4u_to_larb(fwspec->ids[i]);
		portid = mt2701_m4u_to_port(fwspec->ids[i]);
		larb_mmu = &data->larb_imu[larbid];

		dev_dbg(dev, "%s iommu port: %d\n",
			enable ? "enable" : "disable", portid);

		अगर (enable)
			larb_mmu->mmu |= MTK_SMI_MMU_EN(portid);
		अन्यथा
			larb_mmu->mmu &= ~MTK_SMI_MMU_EN(portid);
	पूर्ण
पूर्ण

अटल पूर्णांक mtk_iommu_करोमुख्य_finalise(काष्ठा mtk_iommu_data *data)
अणु
	काष्ठा mtk_iommu_करोमुख्य *करोm = data->m4u_करोm;

	spin_lock_init(&करोm->pgtlock);

	करोm->pgt_va = dma_alloc_coherent(data->dev, M2701_IOMMU_PGT_SIZE,
					 &करोm->pgt_pa, GFP_KERNEL);
	अगर (!करोm->pgt_va)
		वापस -ENOMEM;

	ग_लिखोl(करोm->pgt_pa, data->base + REG_MMU_PT_BASE_ADDR);

	करोm->data = data;

	वापस 0;
पूर्ण

अटल काष्ठा iommu_करोमुख्य *mtk_iommu_करोमुख्य_alloc(अचिन्हित type)
अणु
	काष्ठा mtk_iommu_करोमुख्य *करोm;

	अगर (type != IOMMU_DOMAIN_UNMANAGED)
		वापस शून्य;

	करोm = kzalloc(माप(*करोm), GFP_KERNEL);
	अगर (!करोm)
		वापस शून्य;

	वापस &करोm->करोमुख्य;
पूर्ण

अटल व्योम mtk_iommu_करोमुख्य_मुक्त(काष्ठा iommu_करोमुख्य *करोमुख्य)
अणु
	काष्ठा mtk_iommu_करोमुख्य *करोm = to_mtk_करोमुख्य(करोमुख्य);
	काष्ठा mtk_iommu_data *data = करोm->data;

	dma_मुक्त_coherent(data->dev, M2701_IOMMU_PGT_SIZE,
			करोm->pgt_va, करोm->pgt_pa);
	kमुक्त(to_mtk_करोमुख्य(करोमुख्य));
पूर्ण

अटल पूर्णांक mtk_iommu_attach_device(काष्ठा iommu_करोमुख्य *करोमुख्य,
				   काष्ठा device *dev)
अणु
	काष्ठा mtk_iommu_data *data = dev_iommu_priv_get(dev);
	काष्ठा mtk_iommu_करोमुख्य *करोm = to_mtk_करोमुख्य(करोमुख्य);
	काष्ठा dma_iommu_mapping *mtk_mapping;
	पूर्णांक ret;

	/* Only allow the करोमुख्य created पूर्णांकernally. */
	mtk_mapping = data->mapping;
	अगर (mtk_mapping->करोमुख्य != करोमुख्य)
		वापस 0;

	अगर (!data->m4u_करोm) अणु
		data->m4u_करोm = करोm;
		ret = mtk_iommu_करोमुख्य_finalise(data);
		अगर (ret) अणु
			data->m4u_करोm = शून्य;
			वापस ret;
		पूर्ण
	पूर्ण

	mtk_iommu_config(data, dev, true);
	वापस 0;
पूर्ण

अटल व्योम mtk_iommu_detach_device(काष्ठा iommu_करोमुख्य *करोमुख्य,
				    काष्ठा device *dev)
अणु
	काष्ठा mtk_iommu_data *data = dev_iommu_priv_get(dev);

	mtk_iommu_config(data, dev, false);
पूर्ण

अटल पूर्णांक mtk_iommu_map(काष्ठा iommu_करोमुख्य *करोमुख्य, अचिन्हित दीर्घ iova,
			 phys_addr_t paddr, माप_प्रकार size, पूर्णांक prot, gfp_t gfp)
अणु
	काष्ठा mtk_iommu_करोमुख्य *करोm = to_mtk_करोमुख्य(करोमुख्य);
	अचिन्हित पूर्णांक page_num = size >> MT2701_IOMMU_PAGE_SHIFT;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक i;
	u32 *pgt_base_iova = करोm->pgt_va + (iova  >> MT2701_IOMMU_PAGE_SHIFT);
	u32 pabase = (u32)paddr;
	पूर्णांक map_size = 0;

	spin_lock_irqsave(&करोm->pgtlock, flags);
	क्रम (i = 0; i < page_num; i++) अणु
		अगर (pgt_base_iova[i]) अणु
			स_रखो(pgt_base_iova, 0, i * माप(u32));
			अवरोध;
		पूर्ण
		pgt_base_iova[i] = pabase | F_DESC_VALID | F_DESC_NONSEC;
		pabase += MT2701_IOMMU_PAGE_SIZE;
		map_size += MT2701_IOMMU_PAGE_SIZE;
	पूर्ण

	spin_unlock_irqrestore(&करोm->pgtlock, flags);

	mtk_iommu_tlb_flush_range(करोm->data, iova, size);

	वापस map_size == size ? 0 : -EEXIST;
पूर्ण

अटल माप_प्रकार mtk_iommu_unmap(काष्ठा iommu_करोमुख्य *करोमुख्य,
			      अचिन्हित दीर्घ iova, माप_प्रकार size,
			      काष्ठा iommu_iotlb_gather *gather)
अणु
	काष्ठा mtk_iommu_करोमुख्य *करोm = to_mtk_करोमुख्य(करोमुख्य);
	अचिन्हित दीर्घ flags;
	u32 *pgt_base_iova = करोm->pgt_va + (iova  >> MT2701_IOMMU_PAGE_SHIFT);
	अचिन्हित पूर्णांक page_num = size >> MT2701_IOMMU_PAGE_SHIFT;

	spin_lock_irqsave(&करोm->pgtlock, flags);
	स_रखो(pgt_base_iova, 0, page_num * माप(u32));
	spin_unlock_irqrestore(&करोm->pgtlock, flags);

	mtk_iommu_tlb_flush_range(करोm->data, iova, size);

	वापस size;
पूर्ण

अटल phys_addr_t mtk_iommu_iova_to_phys(काष्ठा iommu_करोमुख्य *करोमुख्य,
					  dma_addr_t iova)
अणु
	काष्ठा mtk_iommu_करोमुख्य *करोm = to_mtk_करोमुख्य(करोमुख्य);
	अचिन्हित दीर्घ flags;
	phys_addr_t pa;

	spin_lock_irqsave(&करोm->pgtlock, flags);
	pa = *(करोm->pgt_va + (iova >> MT2701_IOMMU_PAGE_SHIFT));
	pa = pa & (~(MT2701_IOMMU_PAGE_SIZE - 1));
	spin_unlock_irqrestore(&करोm->pgtlock, flags);

	वापस pa;
पूर्ण

अटल स्थिर काष्ठा iommu_ops mtk_iommu_ops;

/*
 * MTK generation one iommu HW only support one iommu करोमुख्य, and all the client
 * sharing the same iova address space.
 */
अटल पूर्णांक mtk_iommu_create_mapping(काष्ठा device *dev,
				    काष्ठा of_phandle_args *args)
अणु
	काष्ठा iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);
	काष्ठा mtk_iommu_data *data;
	काष्ठा platक्रमm_device *m4updev;
	काष्ठा dma_iommu_mapping *mtk_mapping;
	पूर्णांक ret;

	अगर (args->args_count != 1) अणु
		dev_err(dev, "invalid #iommu-cells(%d) property for IOMMU\n",
			args->args_count);
		वापस -EINVAL;
	पूर्ण

	अगर (!fwspec) अणु
		ret = iommu_fwspec_init(dev, &args->np->fwnode, &mtk_iommu_ops);
		अगर (ret)
			वापस ret;
		fwspec = dev_iommu_fwspec_get(dev);
	पूर्ण अन्यथा अगर (dev_iommu_fwspec_get(dev)->ops != &mtk_iommu_ops) अणु
		वापस -EINVAL;
	पूर्ण

	अगर (!dev_iommu_priv_get(dev)) अणु
		/* Get the m4u device */
		m4updev = of_find_device_by_node(args->np);
		अगर (WARN_ON(!m4updev))
			वापस -EINVAL;

		dev_iommu_priv_set(dev, platक्रमm_get_drvdata(m4updev));
	पूर्ण

	ret = iommu_fwspec_add_ids(dev, args->args, 1);
	अगर (ret)
		वापस ret;

	data = dev_iommu_priv_get(dev);
	mtk_mapping = data->mapping;
	अगर (!mtk_mapping) अणु
		/* MTK iommu support 4GB iova address space. */
		mtk_mapping = arm_iommu_create_mapping(&platक्रमm_bus_type,
						0, 1ULL << 32);
		अगर (IS_ERR(mtk_mapping))
			वापस PTR_ERR(mtk_mapping);

		data->mapping = mtk_mapping;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_iommu_def_करोमुख्य_type(काष्ठा device *dev)
अणु
	वापस IOMMU_DOMAIN_UNMANAGED;
पूर्ण

अटल काष्ठा iommu_device *mtk_iommu_probe_device(काष्ठा device *dev)
अणु
	काष्ठा iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);
	काष्ठा of_phandle_args iommu_spec;
	काष्ठा mtk_iommu_data *data;
	पूर्णांक err, idx = 0;

	जबतक (!of_parse_phandle_with_args(dev->of_node, "iommus",
					   "#iommu-cells",
					   idx, &iommu_spec)) अणु

		err = mtk_iommu_create_mapping(dev, &iommu_spec);
		of_node_put(iommu_spec.np);
		अगर (err)
			वापस ERR_PTR(err);

		/* dev->iommu_fwspec might have changed */
		fwspec = dev_iommu_fwspec_get(dev);
		idx++;
	पूर्ण

	अगर (!fwspec || fwspec->ops != &mtk_iommu_ops)
		वापस ERR_PTR(-ENODEV); /* Not a iommu client device */

	data = dev_iommu_priv_get(dev);

	वापस &data->iommu;
पूर्ण

अटल व्योम mtk_iommu_probe_finalize(काष्ठा device *dev)
अणु
	काष्ठा dma_iommu_mapping *mtk_mapping;
	काष्ठा mtk_iommu_data *data;
	पूर्णांक err;

	data        = dev_iommu_priv_get(dev);
	mtk_mapping = data->mapping;

	err = arm_iommu_attach_device(dev, mtk_mapping);
	अगर (err)
		dev_err(dev, "Can't create IOMMU mapping - DMA-OPS will not work\n");
पूर्ण

अटल व्योम mtk_iommu_release_device(काष्ठा device *dev)
अणु
	काष्ठा iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);

	अगर (!fwspec || fwspec->ops != &mtk_iommu_ops)
		वापस;

	iommu_fwspec_मुक्त(dev);
पूर्ण

अटल पूर्णांक mtk_iommu_hw_init(स्थिर काष्ठा mtk_iommu_data *data)
अणु
	u32 regval;
	पूर्णांक ret;

	ret = clk_prepare_enable(data->bclk);
	अगर (ret) अणु
		dev_err(data->dev, "Failed to enable iommu bclk(%d)\n", ret);
		वापस ret;
	पूर्ण

	regval = F_MMU_CTRL_COHERENT_EN | F_MMU_TF_PROTECT_SEL(2);
	ग_लिखोl_relaxed(regval, data->base + REG_MMU_CTRL_REG);

	regval = F_INT_TRANSLATION_FAULT |
		F_INT_MAIN_MULTI_HIT_FAULT |
		F_INT_INVALID_PA_FAULT |
		F_INT_ENTRY_REPLACEMENT_FAULT |
		F_INT_TABLE_WALK_FAULT |
		F_INT_TLB_MISS_FAULT |
		F_INT_PFH_DMA_FIFO_OVERFLOW |
		F_INT_MISS_DMA_FIFO_OVERFLOW;
	ग_लिखोl_relaxed(regval, data->base + REG_MMU_INT_CONTROL);

	/* protect memory,hw will ग_लिखो here जबतक translation fault */
	ग_लिखोl_relaxed(data->protect_base,
			data->base + REG_MMU_IVRP_PADDR);

	ग_लिखोl_relaxed(F_MMU_DCM_ON, data->base + REG_MMU_DCM);

	अगर (devm_request_irq(data->dev, data->irq, mtk_iommu_isr, 0,
			     dev_name(data->dev), (व्योम *)data)) अणु
		ग_लिखोl_relaxed(0, data->base + REG_MMU_PT_BASE_ADDR);
		clk_disable_unprepare(data->bclk);
		dev_err(data->dev, "Failed @ IRQ-%d Request\n", data->irq);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iommu_ops mtk_iommu_ops = अणु
	.करोमुख्य_alloc	= mtk_iommu_करोमुख्य_alloc,
	.करोमुख्य_मुक्त	= mtk_iommu_करोमुख्य_मुक्त,
	.attach_dev	= mtk_iommu_attach_device,
	.detach_dev	= mtk_iommu_detach_device,
	.map		= mtk_iommu_map,
	.unmap		= mtk_iommu_unmap,
	.iova_to_phys	= mtk_iommu_iova_to_phys,
	.probe_device	= mtk_iommu_probe_device,
	.probe_finalize = mtk_iommu_probe_finalize,
	.release_device	= mtk_iommu_release_device,
	.def_करोमुख्य_type = mtk_iommu_def_करोमुख्य_type,
	.device_group	= generic_device_group,
	.pgsize_biपंचांगap	= ~0UL << MT2701_IOMMU_PAGE_SHIFT,
	.owner          = THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा of_device_id mtk_iommu_of_ids[] = अणु
	अणु .compatible = "mediatek,mt2701-m4u", पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा component_master_ops mtk_iommu_com_ops = अणु
	.bind		= mtk_iommu_bind,
	.unbind		= mtk_iommu_unbind,
पूर्ण;

अटल पूर्णांक mtk_iommu_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mtk_iommu_data		*data;
	काष्ठा device			*dev = &pdev->dev;
	काष्ठा resource			*res;
	काष्ठा component_match		*match = शून्य;
	व्योम				*protect;
	पूर्णांक				larb_nr, ret, i;

	data = devm_kzalloc(dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->dev = dev;

	/* Protect memory. HW will access here जबतक translation fault.*/
	protect = devm_kzalloc(dev, MTK_PROTECT_PA_ALIGN * 2,
			GFP_KERNEL | GFP_DMA);
	अगर (!protect)
		वापस -ENOMEM;
	data->protect_base = ALIGN(virt_to_phys(protect), MTK_PROTECT_PA_ALIGN);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	data->base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(data->base))
		वापस PTR_ERR(data->base);

	data->irq = platक्रमm_get_irq(pdev, 0);
	अगर (data->irq < 0)
		वापस data->irq;

	data->bclk = devm_clk_get(dev, "bclk");
	अगर (IS_ERR(data->bclk))
		वापस PTR_ERR(data->bclk);

	larb_nr = of_count_phandle_with_args(dev->of_node,
					     "mediatek,larbs", शून्य);
	अगर (larb_nr < 0)
		वापस larb_nr;

	क्रम (i = 0; i < larb_nr; i++) अणु
		काष्ठा device_node *larbnode;
		काष्ठा platक्रमm_device *plarbdev;

		larbnode = of_parse_phandle(dev->of_node, "mediatek,larbs", i);
		अगर (!larbnode)
			वापस -EINVAL;

		अगर (!of_device_is_available(larbnode)) अणु
			of_node_put(larbnode);
			जारी;
		पूर्ण

		plarbdev = of_find_device_by_node(larbnode);
		अगर (!plarbdev) अणु
			of_node_put(larbnode);
			वापस -EPROBE_DEFER;
		पूर्ण
		data->larb_imu[i].dev = &plarbdev->dev;

		component_match_add_release(dev, &match, release_of,
					    compare_of, larbnode);
	पूर्ण

	platक्रमm_set_drvdata(pdev, data);

	ret = mtk_iommu_hw_init(data);
	अगर (ret)
		वापस ret;

	ret = iommu_device_sysfs_add(&data->iommu, &pdev->dev, शून्य,
				     dev_name(&pdev->dev));
	अगर (ret)
		वापस ret;

	ret = iommu_device_रेजिस्टर(&data->iommu, &mtk_iommu_ops, dev);
	अगर (ret)
		जाओ out_sysfs_हटाओ;

	अगर (!iommu_present(&platक्रमm_bus_type)) अणु
		ret = bus_set_iommu(&platक्रमm_bus_type,  &mtk_iommu_ops);
		अगर (ret)
			जाओ out_dev_unreg;
	पूर्ण

	ret = component_master_add_with_match(dev, &mtk_iommu_com_ops, match);
	अगर (ret)
		जाओ out_bus_set_null;
	वापस ret;

out_bus_set_null:
	bus_set_iommu(&platक्रमm_bus_type, शून्य);
out_dev_unreg:
	iommu_device_unरेजिस्टर(&data->iommu);
out_sysfs_हटाओ:
	iommu_device_sysfs_हटाओ(&data->iommu);
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
	devm_मुक्त_irq(&pdev->dev, data->irq, data);
	component_master_del(&pdev->dev, &mtk_iommu_com_ops);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused mtk_iommu_suspend(काष्ठा device *dev)
अणु
	काष्ठा mtk_iommu_data *data = dev_get_drvdata(dev);
	काष्ठा mtk_iommu_suspend_reg *reg = &data->reg;
	व्योम __iomem *base = data->base;

	reg->standard_axi_mode = पढ़ोl_relaxed(base +
					       REG_MMU_STANDARD_AXI_MODE);
	reg->dcm_dis = पढ़ोl_relaxed(base + REG_MMU_DCM);
	reg->ctrl_reg = पढ़ोl_relaxed(base + REG_MMU_CTRL_REG);
	reg->पूर्णांक_control0 = पढ़ोl_relaxed(base + REG_MMU_INT_CONTROL);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused mtk_iommu_resume(काष्ठा device *dev)
अणु
	काष्ठा mtk_iommu_data *data = dev_get_drvdata(dev);
	काष्ठा mtk_iommu_suspend_reg *reg = &data->reg;
	व्योम __iomem *base = data->base;

	ग_लिखोl_relaxed(data->m4u_करोm->pgt_pa, base + REG_MMU_PT_BASE_ADDR);
	ग_लिखोl_relaxed(reg->standard_axi_mode,
		       base + REG_MMU_STANDARD_AXI_MODE);
	ग_लिखोl_relaxed(reg->dcm_dis, base + REG_MMU_DCM);
	ग_लिखोl_relaxed(reg->ctrl_reg, base + REG_MMU_CTRL_REG);
	ग_लिखोl_relaxed(reg->पूर्णांक_control0, base + REG_MMU_INT_CONTROL);
	ग_लिखोl_relaxed(data->protect_base, base + REG_MMU_IVRP_PADDR);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops mtk_iommu_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(mtk_iommu_suspend, mtk_iommu_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver mtk_iommu_driver = अणु
	.probe	= mtk_iommu_probe,
	.हटाओ	= mtk_iommu_हटाओ,
	.driver	= अणु
		.name = "mtk-iommu-v1",
		.of_match_table = mtk_iommu_of_ids,
		.pm = &mtk_iommu_pm_ops,
	पूर्ण
पूर्ण;
module_platक्रमm_driver(mtk_iommu_driver);

MODULE_DESCRIPTION("IOMMU API for MediaTek M4U v1 implementations");
MODULE_LICENSE("GPL v2");
