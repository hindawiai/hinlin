<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * omap iommu: tlb and pagetable primitives
 *
 * Copyright (C) 2008-2010 Nokia Corporation
 * Copyright (C) 2013-2017 Texas Instruments Incorporated - https://www.ti.com/
 *
 * Written by Hiroshi DOYU <Hiroshi.DOYU@nokia.com>,
 *		Paul Mundt and Toshihiro Kobayashi
 */

#समावेश <linux/dma-mapping.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/iommu.h>
#समावेश <linux/omap-iommu.h>
#समावेश <linux/mutex.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पन.स>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/of.h>
#समावेश <linux/of_iommu.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/regmap.h>
#समावेश <linux/mfd/syscon.h>

#समावेश <linux/platक्रमm_data/iommu-omap.h>

#समावेश "omap-iopgtable.h"
#समावेश "omap-iommu.h"

अटल स्थिर काष्ठा iommu_ops omap_iommu_ops;

#घोषणा to_iommu(dev)	((काष्ठा omap_iommu *)dev_get_drvdata(dev))

/* biपंचांगap of the page sizes currently supported */
#घोषणा OMAP_IOMMU_PGSIZES	(SZ_4K | SZ_64K | SZ_1M | SZ_16M)

#घोषणा MMU_LOCK_BASE_SHIFT	10
#घोषणा MMU_LOCK_BASE_MASK	(0x1f << MMU_LOCK_BASE_SHIFT)
#घोषणा MMU_LOCK_BASE(x)	\
	((x & MMU_LOCK_BASE_MASK) >> MMU_LOCK_BASE_SHIFT)

#घोषणा MMU_LOCK_VICT_SHIFT	4
#घोषणा MMU_LOCK_VICT_MASK	(0x1f << MMU_LOCK_VICT_SHIFT)
#घोषणा MMU_LOCK_VICT(x)	\
	((x & MMU_LOCK_VICT_MASK) >> MMU_LOCK_VICT_SHIFT)

अटल काष्ठा platक्रमm_driver omap_iommu_driver;
अटल काष्ठा kmem_cache *iopte_cachep;

/**
 * to_omap_करोमुख्य - Get काष्ठा omap_iommu_करोमुख्य from generic iommu_करोमुख्य
 * @करोm:	generic iommu करोमुख्य handle
 **/
अटल काष्ठा omap_iommu_करोमुख्य *to_omap_करोमुख्य(काष्ठा iommu_करोमुख्य *करोm)
अणु
	वापस container_of(करोm, काष्ठा omap_iommu_करोमुख्य, करोमुख्य);
पूर्ण

/**
 * omap_iommu_save_ctx - Save रेजिस्टरs क्रम pm off-mode support
 * @dev:	client device
 *
 * This should be treated as an deprecated API. It is preserved only
 * to मुख्यtain existing functionality क्रम OMAP3 ISP driver.
 **/
व्योम omap_iommu_save_ctx(काष्ठा device *dev)
अणु
	काष्ठा omap_iommu_arch_data *arch_data = dev_iommu_priv_get(dev);
	काष्ठा omap_iommu *obj;
	u32 *p;
	पूर्णांक i;

	अगर (!arch_data)
		वापस;

	जबतक (arch_data->iommu_dev) अणु
		obj = arch_data->iommu_dev;
		p = obj->ctx;
		क्रम (i = 0; i < (MMU_REG_SIZE / माप(u32)); i++) अणु
			p[i] = iommu_पढ़ो_reg(obj, i * माप(u32));
			dev_dbg(obj->dev, "%s\t[%02d] %08x\n", __func__, i,
				p[i]);
		पूर्ण
		arch_data++;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(omap_iommu_save_ctx);

/**
 * omap_iommu_restore_ctx - Restore रेजिस्टरs क्रम pm off-mode support
 * @dev:	client device
 *
 * This should be treated as an deprecated API. It is preserved only
 * to मुख्यtain existing functionality क्रम OMAP3 ISP driver.
 **/
व्योम omap_iommu_restore_ctx(काष्ठा device *dev)
अणु
	काष्ठा omap_iommu_arch_data *arch_data = dev_iommu_priv_get(dev);
	काष्ठा omap_iommu *obj;
	u32 *p;
	पूर्णांक i;

	अगर (!arch_data)
		वापस;

	जबतक (arch_data->iommu_dev) अणु
		obj = arch_data->iommu_dev;
		p = obj->ctx;
		क्रम (i = 0; i < (MMU_REG_SIZE / माप(u32)); i++) अणु
			iommu_ग_लिखो_reg(obj, p[i], i * माप(u32));
			dev_dbg(obj->dev, "%s\t[%02d] %08x\n", __func__, i,
				p[i]);
		पूर्ण
		arch_data++;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(omap_iommu_restore_ctx);

अटल व्योम dra7_cfg_dspsys_mmu(काष्ठा omap_iommu *obj, bool enable)
अणु
	u32 val, mask;

	अगर (!obj->syscfg)
		वापस;

	mask = (1 << (obj->id * DSP_SYS_MMU_CONFIG_EN_SHIFT));
	val = enable ? mask : 0;
	regmap_update_bits(obj->syscfg, DSP_SYS_MMU_CONFIG, mask, val);
पूर्ण

अटल व्योम __iommu_set_twl(काष्ठा omap_iommu *obj, bool on)
अणु
	u32 l = iommu_पढ़ो_reg(obj, MMU_CNTL);

	अगर (on)
		iommu_ग_लिखो_reg(obj, MMU_IRQ_TWL_MASK, MMU_IRQENABLE);
	अन्यथा
		iommu_ग_लिखो_reg(obj, MMU_IRQ_TLB_MISS_MASK, MMU_IRQENABLE);

	l &= ~MMU_CNTL_MASK;
	अगर (on)
		l |= (MMU_CNTL_MMU_EN | MMU_CNTL_TWL_EN);
	अन्यथा
		l |= (MMU_CNTL_MMU_EN);

	iommu_ग_लिखो_reg(obj, l, MMU_CNTL);
पूर्ण

अटल पूर्णांक omap2_iommu_enable(काष्ठा omap_iommu *obj)
अणु
	u32 l, pa;

	अगर (!obj->iopgd || !IS_ALIGNED((अचिन्हित दीर्घ)obj->iopgd,  SZ_16K))
		वापस -EINVAL;

	pa = virt_to_phys(obj->iopgd);
	अगर (!IS_ALIGNED(pa, SZ_16K))
		वापस -EINVAL;

	l = iommu_पढ़ो_reg(obj, MMU_REVISION);
	dev_info(obj->dev, "%s: version %d.%d\n", obj->name,
		 (l >> 4) & 0xf, l & 0xf);

	iommu_ग_लिखो_reg(obj, pa, MMU_TTB);

	dra7_cfg_dspsys_mmu(obj, true);

	अगर (obj->has_bus_err_back)
		iommu_ग_लिखो_reg(obj, MMU_GP_REG_BUS_ERR_BACK_EN, MMU_GP_REG);

	__iommu_set_twl(obj, true);

	वापस 0;
पूर्ण

अटल व्योम omap2_iommu_disable(काष्ठा omap_iommu *obj)
अणु
	u32 l = iommu_पढ़ो_reg(obj, MMU_CNTL);

	l &= ~MMU_CNTL_MASK;
	iommu_ग_लिखो_reg(obj, l, MMU_CNTL);
	dra7_cfg_dspsys_mmu(obj, false);

	dev_dbg(obj->dev, "%s is shutting down\n", obj->name);
पूर्ण

अटल पूर्णांक iommu_enable(काष्ठा omap_iommu *obj)
अणु
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(obj->dev);
	अगर (ret < 0)
		pm_runसमय_put_noidle(obj->dev);

	वापस ret < 0 ? ret : 0;
पूर्ण

अटल व्योम iommu_disable(काष्ठा omap_iommu *obj)
अणु
	pm_runसमय_put_sync(obj->dev);
पूर्ण

/*
 *	TLB operations
 */
अटल u32 iotlb_cr_to_virt(काष्ठा cr_regs *cr)
अणु
	u32 page_size = cr->cam & MMU_CAM_PGSZ_MASK;
	u32 mask = get_cam_va_mask(cr->cam & page_size);

	वापस cr->cam & mask;
पूर्ण

अटल u32 get_iopte_attr(काष्ठा iotlb_entry *e)
अणु
	u32 attr;

	attr = e->mixed << 5;
	attr |= e->endian;
	attr |= e->elsz >> 3;
	attr <<= (((e->pgsz == MMU_CAM_PGSZ_4K) ||
			(e->pgsz == MMU_CAM_PGSZ_64K)) ? 0 : 6);
	वापस attr;
पूर्ण

अटल u32 iommu_report_fault(काष्ठा omap_iommu *obj, u32 *da)
अणु
	u32 status, fault_addr;

	status = iommu_पढ़ो_reg(obj, MMU_IRQSTATUS);
	status &= MMU_IRQ_MASK;
	अगर (!status) अणु
		*da = 0;
		वापस 0;
	पूर्ण

	fault_addr = iommu_पढ़ो_reg(obj, MMU_FAULT_AD);
	*da = fault_addr;

	iommu_ग_लिखो_reg(obj, status, MMU_IRQSTATUS);

	वापस status;
पूर्ण

व्योम iotlb_lock_get(काष्ठा omap_iommu *obj, काष्ठा iotlb_lock *l)
अणु
	u32 val;

	val = iommu_पढ़ो_reg(obj, MMU_LOCK);

	l->base = MMU_LOCK_BASE(val);
	l->vict = MMU_LOCK_VICT(val);
पूर्ण

व्योम iotlb_lock_set(काष्ठा omap_iommu *obj, काष्ठा iotlb_lock *l)
अणु
	u32 val;

	val = (l->base << MMU_LOCK_BASE_SHIFT);
	val |= (l->vict << MMU_LOCK_VICT_SHIFT);

	iommu_ग_लिखो_reg(obj, val, MMU_LOCK);
पूर्ण

अटल व्योम iotlb_पढ़ो_cr(काष्ठा omap_iommu *obj, काष्ठा cr_regs *cr)
अणु
	cr->cam = iommu_पढ़ो_reg(obj, MMU_READ_CAM);
	cr->ram = iommu_पढ़ो_reg(obj, MMU_READ_RAM);
पूर्ण

अटल व्योम iotlb_load_cr(काष्ठा omap_iommu *obj, काष्ठा cr_regs *cr)
अणु
	iommu_ग_लिखो_reg(obj, cr->cam | MMU_CAM_V, MMU_CAM);
	iommu_ग_लिखो_reg(obj, cr->ram, MMU_RAM);

	iommu_ग_लिखो_reg(obj, 1, MMU_FLUSH_ENTRY);
	iommu_ग_लिखो_reg(obj, 1, MMU_LD_TLB);
पूर्ण

/* only used in iotlb iteration क्रम-loop */
काष्ठा cr_regs __iotlb_पढ़ो_cr(काष्ठा omap_iommu *obj, पूर्णांक n)
अणु
	काष्ठा cr_regs cr;
	काष्ठा iotlb_lock l;

	iotlb_lock_get(obj, &l);
	l.vict = n;
	iotlb_lock_set(obj, &l);
	iotlb_पढ़ो_cr(obj, &cr);

	वापस cr;
पूर्ण

#अगर_घोषित PREFETCH_IOTLB
अटल काष्ठा cr_regs *iotlb_alloc_cr(काष्ठा omap_iommu *obj,
				      काष्ठा iotlb_entry *e)
अणु
	काष्ठा cr_regs *cr;

	अगर (!e)
		वापस शून्य;

	अगर (e->da & ~(get_cam_va_mask(e->pgsz))) अणु
		dev_err(obj->dev, "%s:\twrong alignment: %08x\n", __func__,
			e->da);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	cr = kदो_स्मृति(माप(*cr), GFP_KERNEL);
	अगर (!cr)
		वापस ERR_PTR(-ENOMEM);

	cr->cam = (e->da & MMU_CAM_VATAG_MASK) | e->prsvd | e->pgsz | e->valid;
	cr->ram = e->pa | e->endian | e->elsz | e->mixed;

	वापस cr;
पूर्ण

/**
 * load_iotlb_entry - Set an iommu tlb entry
 * @obj:	target iommu
 * @e:		an iommu tlb entry info
 **/
अटल पूर्णांक load_iotlb_entry(काष्ठा omap_iommu *obj, काष्ठा iotlb_entry *e)
अणु
	पूर्णांक err = 0;
	काष्ठा iotlb_lock l;
	काष्ठा cr_regs *cr;

	अगर (!obj || !obj->nr_tlb_entries || !e)
		वापस -EINVAL;

	pm_runसमय_get_sync(obj->dev);

	iotlb_lock_get(obj, &l);
	अगर (l.base == obj->nr_tlb_entries) अणु
		dev_warn(obj->dev, "%s: preserve entries full\n", __func__);
		err = -EBUSY;
		जाओ out;
	पूर्ण
	अगर (!e->prsvd) अणु
		पूर्णांक i;
		काष्ठा cr_regs पंचांगp;

		क्रम_each_iotlb_cr(obj, obj->nr_tlb_entries, i, पंचांगp)
			अगर (!iotlb_cr_valid(&पंचांगp))
				अवरोध;

		अगर (i == obj->nr_tlb_entries) अणु
			dev_dbg(obj->dev, "%s: full: no entry\n", __func__);
			err = -EBUSY;
			जाओ out;
		पूर्ण

		iotlb_lock_get(obj, &l);
	पूर्ण अन्यथा अणु
		l.vict = l.base;
		iotlb_lock_set(obj, &l);
	पूर्ण

	cr = iotlb_alloc_cr(obj, e);
	अगर (IS_ERR(cr)) अणु
		pm_runसमय_put_sync(obj->dev);
		वापस PTR_ERR(cr);
	पूर्ण

	iotlb_load_cr(obj, cr);
	kमुक्त(cr);

	अगर (e->prsvd)
		l.base++;
	/* increment victim क्रम next tlb load */
	अगर (++l.vict == obj->nr_tlb_entries)
		l.vict = l.base;
	iotlb_lock_set(obj, &l);
out:
	pm_runसमय_put_sync(obj->dev);
	वापस err;
पूर्ण

#अन्यथा /* !PREFETCH_IOTLB */

अटल पूर्णांक load_iotlb_entry(काष्ठा omap_iommu *obj, काष्ठा iotlb_entry *e)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* !PREFETCH_IOTLB */

अटल पूर्णांक prefetch_iotlb_entry(काष्ठा omap_iommu *obj, काष्ठा iotlb_entry *e)
अणु
	वापस load_iotlb_entry(obj, e);
पूर्ण

/**
 * flush_iotlb_page - Clear an iommu tlb entry
 * @obj:	target iommu
 * @da:		iommu device भव address
 *
 * Clear an iommu tlb entry which includes 'da' address.
 **/
अटल व्योम flush_iotlb_page(काष्ठा omap_iommu *obj, u32 da)
अणु
	पूर्णांक i;
	काष्ठा cr_regs cr;

	pm_runसमय_get_sync(obj->dev);

	क्रम_each_iotlb_cr(obj, obj->nr_tlb_entries, i, cr) अणु
		u32 start;
		माप_प्रकार bytes;

		अगर (!iotlb_cr_valid(&cr))
			जारी;

		start = iotlb_cr_to_virt(&cr);
		bytes = iopgsz_to_bytes(cr.cam & 3);

		अगर ((start <= da) && (da < start + bytes)) अणु
			dev_dbg(obj->dev, "%s: %08x<=%08x(%zx)\n",
				__func__, start, da, bytes);
			iotlb_load_cr(obj, &cr);
			iommu_ग_लिखो_reg(obj, 1, MMU_FLUSH_ENTRY);
			अवरोध;
		पूर्ण
	पूर्ण
	pm_runसमय_put_sync(obj->dev);

	अगर (i == obj->nr_tlb_entries)
		dev_dbg(obj->dev, "%s: no page for %08x\n", __func__, da);
पूर्ण

/**
 * flush_iotlb_all - Clear all iommu tlb entries
 * @obj:	target iommu
 **/
अटल व्योम flush_iotlb_all(काष्ठा omap_iommu *obj)
अणु
	काष्ठा iotlb_lock l;

	pm_runसमय_get_sync(obj->dev);

	l.base = 0;
	l.vict = 0;
	iotlb_lock_set(obj, &l);

	iommu_ग_लिखो_reg(obj, 1, MMU_GFLUSH);

	pm_runसमय_put_sync(obj->dev);
पूर्ण

/*
 *	H/W pagetable operations
 */
अटल व्योम flush_iopte_range(काष्ठा device *dev, dma_addr_t dma,
			      अचिन्हित दीर्घ offset, पूर्णांक num_entries)
अणु
	माप_प्रकार size = num_entries * माप(u32);

	dma_sync_single_range_क्रम_device(dev, dma, offset, size, DMA_TO_DEVICE);
पूर्ण

अटल व्योम iopte_मुक्त(काष्ठा omap_iommu *obj, u32 *iopte, bool dma_valid)
अणु
	dma_addr_t pt_dma;

	/* Note: मुक्तd iopte's must be clean पढ़ोy क्रम re-use */
	अगर (iopte) अणु
		अगर (dma_valid) अणु
			pt_dma = virt_to_phys(iopte);
			dma_unmap_single(obj->dev, pt_dma, IOPTE_TABLE_SIZE,
					 DMA_TO_DEVICE);
		पूर्ण

		kmem_cache_मुक्त(iopte_cachep, iopte);
	पूर्ण
पूर्ण

अटल u32 *iopte_alloc(काष्ठा omap_iommu *obj, u32 *iopgd,
			dma_addr_t *pt_dma, u32 da)
अणु
	u32 *iopte;
	अचिन्हित दीर्घ offset = iopgd_index(da) * माप(da);

	/* a table has alपढ़ोy existed */
	अगर (*iopgd)
		जाओ pte_पढ़ोy;

	/*
	 * करो the allocation outside the page table lock
	 */
	spin_unlock(&obj->page_table_lock);
	iopte = kmem_cache_zalloc(iopte_cachep, GFP_KERNEL);
	spin_lock(&obj->page_table_lock);

	अगर (!*iopgd) अणु
		अगर (!iopte)
			वापस ERR_PTR(-ENOMEM);

		*pt_dma = dma_map_single(obj->dev, iopte, IOPTE_TABLE_SIZE,
					 DMA_TO_DEVICE);
		अगर (dma_mapping_error(obj->dev, *pt_dma)) अणु
			dev_err(obj->dev, "DMA map error for L2 table\n");
			iopte_मुक्त(obj, iopte, false);
			वापस ERR_PTR(-ENOMEM);
		पूर्ण

		/*
		 * we rely on dma address and the physical address to be
		 * the same क्रम mapping the L2 table
		 */
		अगर (WARN_ON(*pt_dma != virt_to_phys(iopte))) अणु
			dev_err(obj->dev, "DMA translation error for L2 table\n");
			dma_unmap_single(obj->dev, *pt_dma, IOPTE_TABLE_SIZE,
					 DMA_TO_DEVICE);
			iopte_मुक्त(obj, iopte, false);
			वापस ERR_PTR(-ENOMEM);
		पूर्ण

		*iopgd = virt_to_phys(iopte) | IOPGD_TABLE;

		flush_iopte_range(obj->dev, obj->pd_dma, offset, 1);
		dev_vdbg(obj->dev, "%s: a new pte:%p\n", __func__, iopte);
	पूर्ण अन्यथा अणु
		/* We raced, मुक्त the reduniovant table */
		iopte_मुक्त(obj, iopte, false);
	पूर्ण

pte_पढ़ोy:
	iopte = iopte_offset(iopgd, da);
	*pt_dma = iopgd_page_paddr(iopgd);
	dev_vdbg(obj->dev,
		 "%s: da:%08x pgd:%p *pgd:%08x pte:%p *pte:%08x\n",
		 __func__, da, iopgd, *iopgd, iopte, *iopte);

	वापस iopte;
पूर्ण

अटल पूर्णांक iopgd_alloc_section(काष्ठा omap_iommu *obj, u32 da, u32 pa, u32 prot)
अणु
	u32 *iopgd = iopgd_offset(obj, da);
	अचिन्हित दीर्घ offset = iopgd_index(da) * माप(da);

	अगर ((da | pa) & ~IOSECTION_MASK) अणु
		dev_err(obj->dev, "%s: %08x:%08x should aligned on %08lx\n",
			__func__, da, pa, IOSECTION_SIZE);
		वापस -EINVAL;
	पूर्ण

	*iopgd = (pa & IOSECTION_MASK) | prot | IOPGD_SECTION;
	flush_iopte_range(obj->dev, obj->pd_dma, offset, 1);
	वापस 0;
पूर्ण

अटल पूर्णांक iopgd_alloc_super(काष्ठा omap_iommu *obj, u32 da, u32 pa, u32 prot)
अणु
	u32 *iopgd = iopgd_offset(obj, da);
	अचिन्हित दीर्घ offset = iopgd_index(da) * माप(da);
	पूर्णांक i;

	अगर ((da | pa) & ~IOSUPER_MASK) अणु
		dev_err(obj->dev, "%s: %08x:%08x should aligned on %08lx\n",
			__func__, da, pa, IOSUPER_SIZE);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < 16; i++)
		*(iopgd + i) = (pa & IOSUPER_MASK) | prot | IOPGD_SUPER;
	flush_iopte_range(obj->dev, obj->pd_dma, offset, 16);
	वापस 0;
पूर्ण

अटल पूर्णांक iopte_alloc_page(काष्ठा omap_iommu *obj, u32 da, u32 pa, u32 prot)
अणु
	u32 *iopgd = iopgd_offset(obj, da);
	dma_addr_t pt_dma;
	u32 *iopte = iopte_alloc(obj, iopgd, &pt_dma, da);
	अचिन्हित दीर्घ offset = iopte_index(da) * माप(da);

	अगर (IS_ERR(iopte))
		वापस PTR_ERR(iopte);

	*iopte = (pa & IOPAGE_MASK) | prot | IOPTE_SMALL;
	flush_iopte_range(obj->dev, pt_dma, offset, 1);

	dev_vdbg(obj->dev, "%s: da:%08x pa:%08x pte:%p *pte:%08x\n",
		 __func__, da, pa, iopte, *iopte);

	वापस 0;
पूर्ण

अटल पूर्णांक iopte_alloc_large(काष्ठा omap_iommu *obj, u32 da, u32 pa, u32 prot)
अणु
	u32 *iopgd = iopgd_offset(obj, da);
	dma_addr_t pt_dma;
	u32 *iopte = iopte_alloc(obj, iopgd, &pt_dma, da);
	अचिन्हित दीर्घ offset = iopte_index(da) * माप(da);
	पूर्णांक i;

	अगर ((da | pa) & ~IOLARGE_MASK) अणु
		dev_err(obj->dev, "%s: %08x:%08x should aligned on %08lx\n",
			__func__, da, pa, IOLARGE_SIZE);
		वापस -EINVAL;
	पूर्ण

	अगर (IS_ERR(iopte))
		वापस PTR_ERR(iopte);

	क्रम (i = 0; i < 16; i++)
		*(iopte + i) = (pa & IOLARGE_MASK) | prot | IOPTE_LARGE;
	flush_iopte_range(obj->dev, pt_dma, offset, 16);
	वापस 0;
पूर्ण

अटल पूर्णांक
iopgtable_store_entry_core(काष्ठा omap_iommu *obj, काष्ठा iotlb_entry *e)
अणु
	पूर्णांक (*fn)(काष्ठा omap_iommu *, u32, u32, u32);
	u32 prot;
	पूर्णांक err;

	अगर (!obj || !e)
		वापस -EINVAL;

	चयन (e->pgsz) अणु
	हाल MMU_CAM_PGSZ_16M:
		fn = iopgd_alloc_super;
		अवरोध;
	हाल MMU_CAM_PGSZ_1M:
		fn = iopgd_alloc_section;
		अवरोध;
	हाल MMU_CAM_PGSZ_64K:
		fn = iopte_alloc_large;
		अवरोध;
	हाल MMU_CAM_PGSZ_4K:
		fn = iopte_alloc_page;
		अवरोध;
	शेष:
		fn = शून्य;
		अवरोध;
	पूर्ण

	अगर (WARN_ON(!fn))
		वापस -EINVAL;

	prot = get_iopte_attr(e);

	spin_lock(&obj->page_table_lock);
	err = fn(obj, e->da, e->pa, prot);
	spin_unlock(&obj->page_table_lock);

	वापस err;
पूर्ण

/**
 * omap_iopgtable_store_entry - Make an iommu pte entry
 * @obj:	target iommu
 * @e:		an iommu tlb entry info
 **/
अटल पूर्णांक
omap_iopgtable_store_entry(काष्ठा omap_iommu *obj, काष्ठा iotlb_entry *e)
अणु
	पूर्णांक err;

	flush_iotlb_page(obj, e->da);
	err = iopgtable_store_entry_core(obj, e);
	अगर (!err)
		prefetch_iotlb_entry(obj, e);
	वापस err;
पूर्ण

/**
 * iopgtable_lookup_entry - Lookup an iommu pte entry
 * @obj:	target iommu
 * @da:		iommu device भव address
 * @ppgd:	iommu pgd entry poपूर्णांकer to be वापसed
 * @ppte:	iommu pte entry poपूर्णांकer to be वापसed
 **/
अटल व्योम
iopgtable_lookup_entry(काष्ठा omap_iommu *obj, u32 da, u32 **ppgd, u32 **ppte)
अणु
	u32 *iopgd, *iopte = शून्य;

	iopgd = iopgd_offset(obj, da);
	अगर (!*iopgd)
		जाओ out;

	अगर (iopgd_is_table(*iopgd))
		iopte = iopte_offset(iopgd, da);
out:
	*ppgd = iopgd;
	*ppte = iopte;
पूर्ण

अटल माप_प्रकार iopgtable_clear_entry_core(काष्ठा omap_iommu *obj, u32 da)
अणु
	माप_प्रकार bytes;
	u32 *iopgd = iopgd_offset(obj, da);
	पूर्णांक nent = 1;
	dma_addr_t pt_dma;
	अचिन्हित दीर्घ pd_offset = iopgd_index(da) * माप(da);
	अचिन्हित दीर्घ pt_offset = iopte_index(da) * माप(da);

	अगर (!*iopgd)
		वापस 0;

	अगर (iopgd_is_table(*iopgd)) अणु
		पूर्णांक i;
		u32 *iopte = iopte_offset(iopgd, da);

		bytes = IOPTE_SIZE;
		अगर (*iopte & IOPTE_LARGE) अणु
			nent *= 16;
			/* शुरुआत to the 1st entry */
			iopte = iopte_offset(iopgd, (da & IOLARGE_MASK));
		पूर्ण
		bytes *= nent;
		स_रखो(iopte, 0, nent * माप(*iopte));
		pt_dma = iopgd_page_paddr(iopgd);
		flush_iopte_range(obj->dev, pt_dma, pt_offset, nent);

		/*
		 * करो table walk to check अगर this table is necessary or not
		 */
		iopte = iopte_offset(iopgd, 0);
		क्रम (i = 0; i < PTRS_PER_IOPTE; i++)
			अगर (iopte[i])
				जाओ out;

		iopte_मुक्त(obj, iopte, true);
		nent = 1; /* क्रम the next L1 entry */
	पूर्ण अन्यथा अणु
		bytes = IOPGD_SIZE;
		अगर ((*iopgd & IOPGD_SUPER) == IOPGD_SUPER) अणु
			nent *= 16;
			/* शुरुआत to the 1st entry */
			iopgd = iopgd_offset(obj, (da & IOSUPER_MASK));
		पूर्ण
		bytes *= nent;
	पूर्ण
	स_रखो(iopgd, 0, nent * माप(*iopgd));
	flush_iopte_range(obj->dev, obj->pd_dma, pd_offset, nent);
out:
	वापस bytes;
पूर्ण

/**
 * iopgtable_clear_entry - Remove an iommu pte entry
 * @obj:	target iommu
 * @da:		iommu device भव address
 **/
अटल माप_प्रकार iopgtable_clear_entry(काष्ठा omap_iommu *obj, u32 da)
अणु
	माप_प्रकार bytes;

	spin_lock(&obj->page_table_lock);

	bytes = iopgtable_clear_entry_core(obj, da);
	flush_iotlb_page(obj, da);

	spin_unlock(&obj->page_table_lock);

	वापस bytes;
पूर्ण

अटल व्योम iopgtable_clear_entry_all(काष्ठा omap_iommu *obj)
अणु
	अचिन्हित दीर्घ offset;
	पूर्णांक i;

	spin_lock(&obj->page_table_lock);

	क्रम (i = 0; i < PTRS_PER_IOPGD; i++) अणु
		u32 da;
		u32 *iopgd;

		da = i << IOPGD_SHIFT;
		iopgd = iopgd_offset(obj, da);
		offset = iopgd_index(da) * माप(da);

		अगर (!*iopgd)
			जारी;

		अगर (iopgd_is_table(*iopgd))
			iopte_मुक्त(obj, iopte_offset(iopgd, 0), true);

		*iopgd = 0;
		flush_iopte_range(obj->dev, obj->pd_dma, offset, 1);
	पूर्ण

	flush_iotlb_all(obj);

	spin_unlock(&obj->page_table_lock);
पूर्ण

/*
 *	Device IOMMU generic operations
 */
अटल irqवापस_t iommu_fault_handler(पूर्णांक irq, व्योम *data)
अणु
	u32 da, errs;
	u32 *iopgd, *iopte;
	काष्ठा omap_iommu *obj = data;
	काष्ठा iommu_करोमुख्य *करोमुख्य = obj->करोमुख्य;
	काष्ठा omap_iommu_करोमुख्य *omap_करोमुख्य = to_omap_करोमुख्य(करोमुख्य);

	अगर (!omap_करोमुख्य->dev)
		वापस IRQ_NONE;

	errs = iommu_report_fault(obj, &da);
	अगर (errs == 0)
		वापस IRQ_HANDLED;

	/* Fault callback or TLB/PTE Dynamic loading */
	अगर (!report_iommu_fault(करोमुख्य, obj->dev, da, 0))
		वापस IRQ_HANDLED;

	iommu_ग_लिखो_reg(obj, 0, MMU_IRQENABLE);

	iopgd = iopgd_offset(obj, da);

	अगर (!iopgd_is_table(*iopgd)) अणु
		dev_err(obj->dev, "%s: errs:0x%08x da:0x%08x pgd:0x%p *pgd:px%08x\n",
			obj->name, errs, da, iopgd, *iopgd);
		वापस IRQ_NONE;
	पूर्ण

	iopte = iopte_offset(iopgd, da);

	dev_err(obj->dev, "%s: errs:0x%08x da:0x%08x pgd:0x%p *pgd:0x%08x pte:0x%p *pte:0x%08x\n",
		obj->name, errs, da, iopgd, *iopgd, iopte, *iopte);

	वापस IRQ_NONE;
पूर्ण

/**
 * omap_iommu_attach() - attach iommu device to an iommu करोमुख्य
 * @obj:	target omap iommu device
 * @iopgd:	page table
 **/
अटल पूर्णांक omap_iommu_attach(काष्ठा omap_iommu *obj, u32 *iopgd)
अणु
	पूर्णांक err;

	spin_lock(&obj->iommu_lock);

	obj->pd_dma = dma_map_single(obj->dev, iopgd, IOPGD_TABLE_SIZE,
				     DMA_TO_DEVICE);
	अगर (dma_mapping_error(obj->dev, obj->pd_dma)) अणु
		dev_err(obj->dev, "DMA map error for L1 table\n");
		err = -ENOMEM;
		जाओ out_err;
	पूर्ण

	obj->iopgd = iopgd;
	err = iommu_enable(obj);
	अगर (err)
		जाओ out_err;
	flush_iotlb_all(obj);

	spin_unlock(&obj->iommu_lock);

	dev_dbg(obj->dev, "%s: %s\n", __func__, obj->name);

	वापस 0;

out_err:
	spin_unlock(&obj->iommu_lock);

	वापस err;
पूर्ण

/**
 * omap_iommu_detach - release iommu device
 * @obj:	target iommu
 **/
अटल व्योम omap_iommu_detach(काष्ठा omap_iommu *obj)
अणु
	अगर (!obj || IS_ERR(obj))
		वापस;

	spin_lock(&obj->iommu_lock);

	dma_unmap_single(obj->dev, obj->pd_dma, IOPGD_TABLE_SIZE,
			 DMA_TO_DEVICE);
	obj->pd_dma = 0;
	obj->iopgd = शून्य;
	iommu_disable(obj);

	spin_unlock(&obj->iommu_lock);

	dev_dbg(obj->dev, "%s: %s\n", __func__, obj->name);
पूर्ण

अटल व्योम omap_iommu_save_tlb_entries(काष्ठा omap_iommu *obj)
अणु
	काष्ठा iotlb_lock lock;
	काष्ठा cr_regs cr;
	काष्ठा cr_regs *पंचांगp;
	पूर्णांक i;

	/* check अगर there are any locked tlbs to save */
	iotlb_lock_get(obj, &lock);
	obj->num_cr_ctx = lock.base;
	अगर (!obj->num_cr_ctx)
		वापस;

	पंचांगp = obj->cr_ctx;
	क्रम_each_iotlb_cr(obj, obj->num_cr_ctx, i, cr)
		* पंचांगp++ = cr;
पूर्ण

अटल व्योम omap_iommu_restore_tlb_entries(काष्ठा omap_iommu *obj)
अणु
	काष्ठा iotlb_lock l;
	काष्ठा cr_regs *पंचांगp;
	पूर्णांक i;

	/* no locked tlbs to restore */
	अगर (!obj->num_cr_ctx)
		वापस;

	l.base = 0;
	पंचांगp = obj->cr_ctx;
	क्रम (i = 0; i < obj->num_cr_ctx; i++, पंचांगp++) अणु
		l.vict = i;
		iotlb_lock_set(obj, &l);
		iotlb_load_cr(obj, पंचांगp);
	पूर्ण
	l.base = obj->num_cr_ctx;
	l.vict = i;
	iotlb_lock_set(obj, &l);
पूर्ण

/**
 * omap_iommu_करोमुख्य_deactivate - deactivate attached iommu devices
 * @करोमुख्य: iommu करोमुख्य attached to the target iommu device
 *
 * This API allows the client devices of IOMMU devices to suspend
 * the IOMMUs they control at runसमय, after they are idled and
 * suspended all activity. System Suspend will leverage the PM
 * driver late callbacks.
 **/
पूर्णांक omap_iommu_करोमुख्य_deactivate(काष्ठा iommu_करोमुख्य *करोमुख्य)
अणु
	काष्ठा omap_iommu_करोमुख्य *omap_करोमुख्य = to_omap_करोमुख्य(करोमुख्य);
	काष्ठा omap_iommu_device *iommu;
	काष्ठा omap_iommu *oiommu;
	पूर्णांक i;

	अगर (!omap_करोमुख्य->dev)
		वापस 0;

	iommu = omap_करोमुख्य->iommus;
	iommu += (omap_करोमुख्य->num_iommus - 1);
	क्रम (i = 0; i < omap_करोमुख्य->num_iommus; i++, iommu--) अणु
		oiommu = iommu->iommu_dev;
		pm_runसमय_put_sync(oiommu->dev);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(omap_iommu_करोमुख्य_deactivate);

/**
 * omap_iommu_करोमुख्य_activate - activate attached iommu devices
 * @करोमुख्य: iommu करोमुख्य attached to the target iommu device
 *
 * This API allows the client devices of IOMMU devices to resume the
 * IOMMUs they control at runसमय, beक्रमe they can resume operations.
 * System Resume will leverage the PM driver late callbacks.
 **/
पूर्णांक omap_iommu_करोमुख्य_activate(काष्ठा iommu_करोमुख्य *करोमुख्य)
अणु
	काष्ठा omap_iommu_करोमुख्य *omap_करोमुख्य = to_omap_करोमुख्य(करोमुख्य);
	काष्ठा omap_iommu_device *iommu;
	काष्ठा omap_iommu *oiommu;
	पूर्णांक i;

	अगर (!omap_करोमुख्य->dev)
		वापस 0;

	iommu = omap_करोमुख्य->iommus;
	क्रम (i = 0; i < omap_करोमुख्य->num_iommus; i++, iommu++) अणु
		oiommu = iommu->iommu_dev;
		pm_runसमय_get_sync(oiommu->dev);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(omap_iommu_करोमुख्य_activate);

/**
 * omap_iommu_runसमय_suspend - disable an iommu device
 * @dev:	iommu device
 *
 * This function perक्रमms all that is necessary to disable an
 * IOMMU device, either during final detachment from a client
 * device, or during प्रणाली/runसमय suspend of the device. This
 * includes programming all the appropriate IOMMU रेजिस्टरs, and
 * managing the associated omap_hwmod's state and the device's
 * reset line. This function also saves the context of any
 * locked TLBs अगर suspending.
 **/
अटल __maybe_unused पूर्णांक omap_iommu_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा iommu_platक्रमm_data *pdata = dev_get_platdata(dev);
	काष्ठा omap_iommu *obj = to_iommu(dev);
	पूर्णांक ret;

	/* save the TLBs only during suspend, and not क्रम घातer करोwn */
	अगर (obj->करोमुख्य && obj->iopgd)
		omap_iommu_save_tlb_entries(obj);

	omap2_iommu_disable(obj);

	अगर (pdata && pdata->device_idle)
		pdata->device_idle(pdev);

	अगर (pdata && pdata->निश्चित_reset)
		pdata->निश्चित_reset(pdev, pdata->reset_name);

	अगर (pdata && pdata->set_pwrdm_स्थिरraपूर्णांक) अणु
		ret = pdata->set_pwrdm_स्थिरraपूर्णांक(pdev, false, &obj->pwrst);
		अगर (ret) अणु
			dev_warn(obj->dev, "pwrdm_constraint failed to be reset, status = %d\n",
				 ret);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * omap_iommu_runसमय_resume - enable an iommu device
 * @dev:	iommu device
 *
 * This function perक्रमms all that is necessary to enable an
 * IOMMU device, either during initial attachment to a client
 * device, or during प्रणाली/runसमय resume of the device. This
 * includes programming all the appropriate IOMMU रेजिस्टरs, and
 * managing the associated omap_hwmod's state and the device's
 * reset line. The function also restores any locked TLBs अगर
 * resuming after a suspend.
 **/
अटल __maybe_unused पूर्णांक omap_iommu_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा iommu_platक्रमm_data *pdata = dev_get_platdata(dev);
	काष्ठा omap_iommu *obj = to_iommu(dev);
	पूर्णांक ret = 0;

	अगर (pdata && pdata->set_pwrdm_स्थिरraपूर्णांक) अणु
		ret = pdata->set_pwrdm_स्थिरraपूर्णांक(pdev, true, &obj->pwrst);
		अगर (ret) अणु
			dev_warn(obj->dev, "pwrdm_constraint failed to be set, status = %d\n",
				 ret);
		पूर्ण
	पूर्ण

	अगर (pdata && pdata->deनिश्चित_reset) अणु
		ret = pdata->deनिश्चित_reset(pdev, pdata->reset_name);
		अगर (ret) अणु
			dev_err(dev, "deassert_reset failed: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (pdata && pdata->device_enable)
		pdata->device_enable(pdev);

	/* restore the TLBs only during resume, and not क्रम घातer up */
	अगर (obj->करोमुख्य)
		omap_iommu_restore_tlb_entries(obj);

	ret = omap2_iommu_enable(obj);

	वापस ret;
पूर्ण

/**
 * omap_iommu_suspend_prepare - prepare() dev_pm_ops implementation
 * @dev:	iommu device
 *
 * This function perक्रमms the necessary checks to determine अगर the IOMMU
 * device needs suspending or not. The function checks अगर the runसमय_pm
 * status of the device is suspended, and वापसs 1 in that हाल. This
 * results in the PM core to skip invoking any of the Sleep PM callbacks
 * (suspend, suspend_late, resume, resume_early etc).
 */
अटल पूर्णांक omap_iommu_prepare(काष्ठा device *dev)
अणु
	अगर (pm_runसमय_status_suspended(dev))
		वापस 1;
	वापस 0;
पूर्ण

अटल bool omap_iommu_can_रेजिस्टर(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;

	अगर (!of_device_is_compatible(np, "ti,dra7-dsp-iommu"))
		वापस true;

	/*
	 * restrict IOMMU core registration only क्रम processor-port MDMA MMUs
	 * on DRA7 DSPs
	 */
	अगर ((!म_भेद(dev_name(&pdev->dev), "40d01000.mmu")) ||
	    (!म_भेद(dev_name(&pdev->dev), "41501000.mmu")))
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक omap_iommu_dra7_get_dsp_प्रणाली_cfg(काष्ठा platक्रमm_device *pdev,
					      काष्ठा omap_iommu *obj)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	पूर्णांक ret;

	अगर (!of_device_is_compatible(np, "ti,dra7-dsp-iommu"))
		वापस 0;

	अगर (!of_property_पढ़ो_bool(np, "ti,syscon-mmuconfig")) अणु
		dev_err(&pdev->dev, "ti,syscon-mmuconfig property is missing\n");
		वापस -EINVAL;
	पूर्ण

	obj->syscfg =
		syscon_regmap_lookup_by_phandle(np, "ti,syscon-mmuconfig");
	अगर (IS_ERR(obj->syscfg)) अणु
		/* can fail with -EPROBE_DEFER */
		ret = PTR_ERR(obj->syscfg);
		वापस ret;
	पूर्ण

	अगर (of_property_पढ़ो_u32_index(np, "ti,syscon-mmuconfig", 1,
				       &obj->id)) अणु
		dev_err(&pdev->dev, "couldn't get the IOMMU instance id within subsystem\n");
		वापस -EINVAL;
	पूर्ण

	अगर (obj->id != 0 && obj->id != 1) अणु
		dev_err(&pdev->dev, "invalid IOMMU instance id\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 *	OMAP Device MMU(IOMMU) detection
 */
अटल पूर्णांक omap_iommu_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक err = -ENODEV;
	पूर्णांक irq;
	काष्ठा omap_iommu *obj;
	काष्ठा resource *res;
	काष्ठा device_node *of = pdev->dev.of_node;

	अगर (!of) अणु
		pr_err("%s: only DT-based devices are supported\n", __func__);
		वापस -ENODEV;
	पूर्ण

	obj = devm_kzalloc(&pdev->dev, माप(*obj) + MMU_REG_SIZE, GFP_KERNEL);
	अगर (!obj)
		वापस -ENOMEM;

	/*
	 * self-manage the ordering dependencies between omap_device_enable/idle
	 * and omap_device_निश्चित/deनिश्चित_hardreset API
	 */
	अगर (pdev->dev.pm_करोमुख्य) अणु
		dev_dbg(&pdev->dev, "device pm_domain is being reset\n");
		pdev->dev.pm_करोमुख्य = शून्य;
	पूर्ण

	obj->name = dev_name(&pdev->dev);
	obj->nr_tlb_entries = 32;
	err = of_property_पढ़ो_u32(of, "ti,#tlb-entries", &obj->nr_tlb_entries);
	अगर (err && err != -EINVAL)
		वापस err;
	अगर (obj->nr_tlb_entries != 32 && obj->nr_tlb_entries != 8)
		वापस -EINVAL;
	अगर (of_find_property(of, "ti,iommu-bus-err-back", शून्य))
		obj->has_bus_err_back = MMU_GP_REG_BUS_ERR_BACK_EN;

	obj->dev = &pdev->dev;
	obj->ctx = (व्योम *)obj + माप(*obj);
	obj->cr_ctx = devm_kzalloc(&pdev->dev,
				   माप(*obj->cr_ctx) * obj->nr_tlb_entries,
				   GFP_KERNEL);
	अगर (!obj->cr_ctx)
		वापस -ENOMEM;

	spin_lock_init(&obj->iommu_lock);
	spin_lock_init(&obj->page_table_lock);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	obj->regbase = devm_ioremap_resource(obj->dev, res);
	अगर (IS_ERR(obj->regbase))
		वापस PTR_ERR(obj->regbase);

	err = omap_iommu_dra7_get_dsp_प्रणाली_cfg(pdev, obj);
	अगर (err)
		वापस err;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस -ENODEV;

	err = devm_request_irq(obj->dev, irq, iommu_fault_handler, IRQF_SHARED,
			       dev_name(obj->dev), obj);
	अगर (err < 0)
		वापस err;
	platक्रमm_set_drvdata(pdev, obj);

	अगर (omap_iommu_can_रेजिस्टर(pdev)) अणु
		obj->group = iommu_group_alloc();
		अगर (IS_ERR(obj->group))
			वापस PTR_ERR(obj->group);

		err = iommu_device_sysfs_add(&obj->iommu, obj->dev, शून्य,
					     obj->name);
		अगर (err)
			जाओ out_group;

		err = iommu_device_रेजिस्टर(&obj->iommu, &omap_iommu_ops, &pdev->dev);
		अगर (err)
			जाओ out_sysfs;
	पूर्ण

	pm_runसमय_enable(obj->dev);

	omap_iommu_debugfs_add(obj);

	dev_info(&pdev->dev, "%s registered\n", obj->name);

	/* Re-probe bus to probe device attached to this IOMMU */
	bus_iommu_probe(&platक्रमm_bus_type);

	वापस 0;

out_sysfs:
	iommu_device_sysfs_हटाओ(&obj->iommu);
out_group:
	iommu_group_put(obj->group);
	वापस err;
पूर्ण

अटल पूर्णांक omap_iommu_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा omap_iommu *obj = platक्रमm_get_drvdata(pdev);

	अगर (obj->group) अणु
		iommu_group_put(obj->group);
		obj->group = शून्य;

		iommu_device_sysfs_हटाओ(&obj->iommu);
		iommu_device_unरेजिस्टर(&obj->iommu);
	पूर्ण

	omap_iommu_debugfs_हटाओ(obj);

	pm_runसमय_disable(obj->dev);

	dev_info(&pdev->dev, "%s removed\n", obj->name);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops omap_iommu_pm_ops = अणु
	.prepare = omap_iommu_prepare,
	SET_LATE_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				     pm_runसमय_क्रमce_resume)
	SET_RUNTIME_PM_OPS(omap_iommu_runसमय_suspend,
			   omap_iommu_runसमय_resume, शून्य)
पूर्ण;

अटल स्थिर काष्ठा of_device_id omap_iommu_of_match[] = अणु
	अणु .compatible = "ti,omap2-iommu" पूर्ण,
	अणु .compatible = "ti,omap4-iommu" पूर्ण,
	अणु .compatible = "ti,dra7-iommu"	पूर्ण,
	अणु .compatible = "ti,dra7-dsp-iommu" पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver omap_iommu_driver = अणु
	.probe	= omap_iommu_probe,
	.हटाओ	= omap_iommu_हटाओ,
	.driver	= अणु
		.name	= "omap-iommu",
		.pm	= &omap_iommu_pm_ops,
		.of_match_table = of_match_ptr(omap_iommu_of_match),
	पूर्ण,
पूर्ण;

अटल u32 iotlb_init_entry(काष्ठा iotlb_entry *e, u32 da, u32 pa, पूर्णांक pgsz)
अणु
	स_रखो(e, 0, माप(*e));

	e->da		= da;
	e->pa		= pa;
	e->valid	= MMU_CAM_V;
	e->pgsz		= pgsz;
	e->endian	= MMU_RAM_ENDIAN_LITTLE;
	e->elsz		= MMU_RAM_ELSZ_8;
	e->mixed	= 0;

	वापस iopgsz_to_bytes(e->pgsz);
पूर्ण

अटल पूर्णांक omap_iommu_map(काष्ठा iommu_करोमुख्य *करोमुख्य, अचिन्हित दीर्घ da,
			  phys_addr_t pa, माप_प्रकार bytes, पूर्णांक prot, gfp_t gfp)
अणु
	काष्ठा omap_iommu_करोमुख्य *omap_करोमुख्य = to_omap_करोमुख्य(करोमुख्य);
	काष्ठा device *dev = omap_करोमुख्य->dev;
	काष्ठा omap_iommu_device *iommu;
	काष्ठा omap_iommu *oiommu;
	काष्ठा iotlb_entry e;
	पूर्णांक omap_pgsz;
	u32 ret = -EINVAL;
	पूर्णांक i;

	omap_pgsz = bytes_to_iopgsz(bytes);
	अगर (omap_pgsz < 0) अणु
		dev_err(dev, "invalid size to map: %zu\n", bytes);
		वापस -EINVAL;
	पूर्ण

	dev_dbg(dev, "mapping da 0x%lx to pa %pa size 0x%zx\n", da, &pa, bytes);

	iotlb_init_entry(&e, da, pa, omap_pgsz);

	iommu = omap_करोमुख्य->iommus;
	क्रम (i = 0; i < omap_करोमुख्य->num_iommus; i++, iommu++) अणु
		oiommu = iommu->iommu_dev;
		ret = omap_iopgtable_store_entry(oiommu, &e);
		अगर (ret) अणु
			dev_err(dev, "omap_iopgtable_store_entry failed: %d\n",
				ret);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (ret) अणु
		जबतक (i--) अणु
			iommu--;
			oiommu = iommu->iommu_dev;
			iopgtable_clear_entry(oiommu, da);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल माप_प्रकार omap_iommu_unmap(काष्ठा iommu_करोमुख्य *करोमुख्य, अचिन्हित दीर्घ da,
			       माप_प्रकार size, काष्ठा iommu_iotlb_gather *gather)
अणु
	काष्ठा omap_iommu_करोमुख्य *omap_करोमुख्य = to_omap_करोमुख्य(करोमुख्य);
	काष्ठा device *dev = omap_करोमुख्य->dev;
	काष्ठा omap_iommu_device *iommu;
	काष्ठा omap_iommu *oiommu;
	bool error = false;
	माप_प्रकार bytes = 0;
	पूर्णांक i;

	dev_dbg(dev, "unmapping da 0x%lx size %zu\n", da, size);

	iommu = omap_करोमुख्य->iommus;
	क्रम (i = 0; i < omap_करोमुख्य->num_iommus; i++, iommu++) अणु
		oiommu = iommu->iommu_dev;
		bytes = iopgtable_clear_entry(oiommu, da);
		अगर (!bytes)
			error = true;
	पूर्ण

	/*
	 * simplअगरy वापस - we are only checking अगर any of the iommus
	 * reported an error, but not अगर all of them are unmapping the
	 * same number of entries. This should not occur due to the
	 * mirror programming.
	 */
	वापस error ? 0 : bytes;
पूर्ण

अटल पूर्णांक omap_iommu_count(काष्ठा device *dev)
अणु
	काष्ठा omap_iommu_arch_data *arch_data = dev_iommu_priv_get(dev);
	पूर्णांक count = 0;

	जबतक (arch_data->iommu_dev) अणु
		count++;
		arch_data++;
	पूर्ण

	वापस count;
पूर्ण

/* caller should call cleanup अगर this function fails */
अटल पूर्णांक omap_iommu_attach_init(काष्ठा device *dev,
				  काष्ठा omap_iommu_करोमुख्य *oकरोमुख्य)
अणु
	काष्ठा omap_iommu_device *iommu;
	पूर्णांक i;

	oकरोमुख्य->num_iommus = omap_iommu_count(dev);
	अगर (!oकरोमुख्य->num_iommus)
		वापस -EINVAL;

	oकरोमुख्य->iommus = kसुस्मृति(oकरोमुख्य->num_iommus, माप(*iommu),
				  GFP_ATOMIC);
	अगर (!oकरोमुख्य->iommus)
		वापस -ENOMEM;

	iommu = oकरोमुख्य->iommus;
	क्रम (i = 0; i < oकरोमुख्य->num_iommus; i++, iommu++) अणु
		iommu->pgtable = kzalloc(IOPGD_TABLE_SIZE, GFP_ATOMIC);
		अगर (!iommu->pgtable)
			वापस -ENOMEM;

		/*
		 * should never fail, but please keep this around to ensure
		 * we keep the hardware happy
		 */
		अगर (WARN_ON(!IS_ALIGNED((दीर्घ)iommu->pgtable,
					IOPGD_TABLE_SIZE)))
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम omap_iommu_detach_fini(काष्ठा omap_iommu_करोमुख्य *oकरोमुख्य)
अणु
	पूर्णांक i;
	काष्ठा omap_iommu_device *iommu = oकरोमुख्य->iommus;

	क्रम (i = 0; iommu && i < oकरोमुख्य->num_iommus; i++, iommu++)
		kमुक्त(iommu->pgtable);

	kमुक्त(oकरोमुख्य->iommus);
	oकरोमुख्य->num_iommus = 0;
	oकरोमुख्य->iommus = शून्य;
पूर्ण

अटल पूर्णांक
omap_iommu_attach_dev(काष्ठा iommu_करोमुख्य *करोमुख्य, काष्ठा device *dev)
अणु
	काष्ठा omap_iommu_arch_data *arch_data = dev_iommu_priv_get(dev);
	काष्ठा omap_iommu_करोमुख्य *omap_करोमुख्य = to_omap_करोमुख्य(करोमुख्य);
	काष्ठा omap_iommu_device *iommu;
	काष्ठा omap_iommu *oiommu;
	पूर्णांक ret = 0;
	पूर्णांक i;

	अगर (!arch_data || !arch_data->iommu_dev) अणु
		dev_err(dev, "device doesn't have an associated iommu\n");
		वापस -EINVAL;
	पूर्ण

	spin_lock(&omap_करोमुख्य->lock);

	/* only a single client device can be attached to a करोमुख्य */
	अगर (omap_करोमुख्य->dev) अणु
		dev_err(dev, "iommu domain is already attached\n");
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	ret = omap_iommu_attach_init(dev, omap_करोमुख्य);
	अगर (ret) अणु
		dev_err(dev, "failed to allocate required iommu data %d\n",
			ret);
		जाओ init_fail;
	पूर्ण

	iommu = omap_करोमुख्य->iommus;
	क्रम (i = 0; i < omap_करोमुख्य->num_iommus; i++, iommu++, arch_data++) अणु
		/* configure and enable the omap iommu */
		oiommu = arch_data->iommu_dev;
		ret = omap_iommu_attach(oiommu, iommu->pgtable);
		अगर (ret) अणु
			dev_err(dev, "can't get omap iommu: %d\n", ret);
			जाओ attach_fail;
		पूर्ण

		oiommu->करोमुख्य = करोमुख्य;
		iommu->iommu_dev = oiommu;
	पूर्ण

	omap_करोमुख्य->dev = dev;

	जाओ out;

attach_fail:
	जबतक (i--) अणु
		iommu--;
		arch_data--;
		oiommu = iommu->iommu_dev;
		omap_iommu_detach(oiommu);
		iommu->iommu_dev = शून्य;
		oiommu->करोमुख्य = शून्य;
	पूर्ण
init_fail:
	omap_iommu_detach_fini(omap_करोमुख्य);
out:
	spin_unlock(&omap_करोमुख्य->lock);
	वापस ret;
पूर्ण

अटल व्योम _omap_iommu_detach_dev(काष्ठा omap_iommu_करोमुख्य *omap_करोमुख्य,
				   काष्ठा device *dev)
अणु
	काष्ठा omap_iommu_arch_data *arch_data = dev_iommu_priv_get(dev);
	काष्ठा omap_iommu_device *iommu = omap_करोमुख्य->iommus;
	काष्ठा omap_iommu *oiommu;
	पूर्णांक i;

	अगर (!omap_करोमुख्य->dev) अणु
		dev_err(dev, "domain has no attached device\n");
		वापस;
	पूर्ण

	/* only a single device is supported per करोमुख्य क्रम now */
	अगर (omap_करोमुख्य->dev != dev) अणु
		dev_err(dev, "invalid attached device\n");
		वापस;
	पूर्ण

	/*
	 * cleanup in the reverse order of attachment - this addresses
	 * any h/w dependencies between multiple instances, अगर any
	 */
	iommu += (omap_करोमुख्य->num_iommus - 1);
	arch_data += (omap_करोमुख्य->num_iommus - 1);
	क्रम (i = 0; i < omap_करोमुख्य->num_iommus; i++, iommu--, arch_data--) अणु
		oiommu = iommu->iommu_dev;
		iopgtable_clear_entry_all(oiommu);

		omap_iommu_detach(oiommu);
		iommu->iommu_dev = शून्य;
		oiommu->करोमुख्य = शून्य;
	पूर्ण

	omap_iommu_detach_fini(omap_करोमुख्य);

	omap_करोमुख्य->dev = शून्य;
पूर्ण

अटल व्योम omap_iommu_detach_dev(काष्ठा iommu_करोमुख्य *करोमुख्य,
				  काष्ठा device *dev)
अणु
	काष्ठा omap_iommu_करोमुख्य *omap_करोमुख्य = to_omap_करोमुख्य(करोमुख्य);

	spin_lock(&omap_करोमुख्य->lock);
	_omap_iommu_detach_dev(omap_करोमुख्य, dev);
	spin_unlock(&omap_करोमुख्य->lock);
पूर्ण

अटल काष्ठा iommu_करोमुख्य *omap_iommu_करोमुख्य_alloc(अचिन्हित type)
अणु
	काष्ठा omap_iommu_करोमुख्य *omap_करोमुख्य;

	अगर (type != IOMMU_DOMAIN_UNMANAGED)
		वापस शून्य;

	omap_करोमुख्य = kzalloc(माप(*omap_करोमुख्य), GFP_KERNEL);
	अगर (!omap_करोमुख्य)
		वापस शून्य;

	spin_lock_init(&omap_करोमुख्य->lock);

	omap_करोमुख्य->करोमुख्य.geometry.aperture_start = 0;
	omap_करोमुख्य->करोमुख्य.geometry.aperture_end   = (1ULL << 32) - 1;
	omap_करोमुख्य->करोमुख्य.geometry.क्रमce_aperture = true;

	वापस &omap_करोमुख्य->करोमुख्य;
पूर्ण

अटल व्योम omap_iommu_करोमुख्य_मुक्त(काष्ठा iommu_करोमुख्य *करोमुख्य)
अणु
	काष्ठा omap_iommu_करोमुख्य *omap_करोमुख्य = to_omap_करोमुख्य(करोमुख्य);

	/*
	 * An iommu device is still attached
	 * (currently, only one device can be attached) ?
	 */
	अगर (omap_करोमुख्य->dev)
		_omap_iommu_detach_dev(omap_करोमुख्य, omap_करोमुख्य->dev);

	kमुक्त(omap_करोमुख्य);
पूर्ण

अटल phys_addr_t omap_iommu_iova_to_phys(काष्ठा iommu_करोमुख्य *करोमुख्य,
					   dma_addr_t da)
अणु
	काष्ठा omap_iommu_करोमुख्य *omap_करोमुख्य = to_omap_करोमुख्य(करोमुख्य);
	काष्ठा omap_iommu_device *iommu = omap_करोमुख्य->iommus;
	काष्ठा omap_iommu *oiommu = iommu->iommu_dev;
	काष्ठा device *dev = oiommu->dev;
	u32 *pgd, *pte;
	phys_addr_t ret = 0;

	/*
	 * all the iommus within the करोमुख्य will have identical programming,
	 * so perक्रमm the lookup using just the first iommu
	 */
	iopgtable_lookup_entry(oiommu, da, &pgd, &pte);

	अगर (pte) अणु
		अगर (iopte_is_small(*pte))
			ret = omap_iommu_translate(*pte, da, IOPTE_MASK);
		अन्यथा अगर (iopte_is_large(*pte))
			ret = omap_iommu_translate(*pte, da, IOLARGE_MASK);
		अन्यथा
			dev_err(dev, "bogus pte 0x%x, da 0x%llx", *pte,
				(अचिन्हित दीर्घ दीर्घ)da);
	पूर्ण अन्यथा अणु
		अगर (iopgd_is_section(*pgd))
			ret = omap_iommu_translate(*pgd, da, IOSECTION_MASK);
		अन्यथा अगर (iopgd_is_super(*pgd))
			ret = omap_iommu_translate(*pgd, da, IOSUPER_MASK);
		अन्यथा
			dev_err(dev, "bogus pgd 0x%x, da 0x%llx", *pgd,
				(अचिन्हित दीर्घ दीर्घ)da);
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा iommu_device *omap_iommu_probe_device(काष्ठा device *dev)
अणु
	काष्ठा omap_iommu_arch_data *arch_data, *पंचांगp;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा omap_iommu *oiommu;
	काष्ठा device_node *np;
	पूर्णांक num_iommus, i;

	/*
	 * Allocate the per-device iommu काष्ठाure क्रम DT-based devices.
	 *
	 * TODO: Simplअगरy this when removing non-DT support completely from the
	 * IOMMU users.
	 */
	अगर (!dev->of_node)
		वापस ERR_PTR(-ENODEV);

	/*
	 * retrieve the count of IOMMU nodes using phandle size as element size
	 * since #iommu-cells = 0 क्रम OMAP
	 */
	num_iommus = of_property_count_elems_of_size(dev->of_node, "iommus",
						     माप(phandle));
	अगर (num_iommus < 0)
		वापस 0;

	arch_data = kसुस्मृति(num_iommus + 1, माप(*arch_data), GFP_KERNEL);
	अगर (!arch_data)
		वापस ERR_PTR(-ENOMEM);

	क्रम (i = 0, पंचांगp = arch_data; i < num_iommus; i++, पंचांगp++) अणु
		np = of_parse_phandle(dev->of_node, "iommus", i);
		अगर (!np) अणु
			kमुक्त(arch_data);
			वापस ERR_PTR(-EINVAL);
		पूर्ण

		pdev = of_find_device_by_node(np);
		अगर (!pdev) अणु
			of_node_put(np);
			kमुक्त(arch_data);
			वापस ERR_PTR(-ENODEV);
		पूर्ण

		oiommu = platक्रमm_get_drvdata(pdev);
		अगर (!oiommu) अणु
			of_node_put(np);
			kमुक्त(arch_data);
			वापस ERR_PTR(-EINVAL);
		पूर्ण

		पंचांगp->iommu_dev = oiommu;
		पंचांगp->dev = &pdev->dev;

		of_node_put(np);
	पूर्ण

	dev_iommu_priv_set(dev, arch_data);

	/*
	 * use the first IOMMU alone क्रम the sysfs device linking.
	 * TODO: Evaluate अगर a single iommu_group needs to be
	 * मुख्यtained क्रम both IOMMUs
	 */
	oiommu = arch_data->iommu_dev;

	वापस &oiommu->iommu;
पूर्ण

अटल व्योम omap_iommu_release_device(काष्ठा device *dev)
अणु
	काष्ठा omap_iommu_arch_data *arch_data = dev_iommu_priv_get(dev);

	अगर (!dev->of_node || !arch_data)
		वापस;

	dev_iommu_priv_set(dev, शून्य);
	kमुक्त(arch_data);

पूर्ण

अटल काष्ठा iommu_group *omap_iommu_device_group(काष्ठा device *dev)
अणु
	काष्ठा omap_iommu_arch_data *arch_data = dev_iommu_priv_get(dev);
	काष्ठा iommu_group *group = ERR_PTR(-EINVAL);

	अगर (!arch_data)
		वापस ERR_PTR(-ENODEV);

	अगर (arch_data->iommu_dev)
		group = iommu_group_ref_get(arch_data->iommu_dev->group);

	वापस group;
पूर्ण

अटल स्थिर काष्ठा iommu_ops omap_iommu_ops = अणु
	.करोमुख्य_alloc	= omap_iommu_करोमुख्य_alloc,
	.करोमुख्य_मुक्त	= omap_iommu_करोमुख्य_मुक्त,
	.attach_dev	= omap_iommu_attach_dev,
	.detach_dev	= omap_iommu_detach_dev,
	.map		= omap_iommu_map,
	.unmap		= omap_iommu_unmap,
	.iova_to_phys	= omap_iommu_iova_to_phys,
	.probe_device	= omap_iommu_probe_device,
	.release_device	= omap_iommu_release_device,
	.device_group	= omap_iommu_device_group,
	.pgsize_biपंचांगap	= OMAP_IOMMU_PGSIZES,
पूर्ण;

अटल पूर्णांक __init omap_iommu_init(व्योम)
अणु
	काष्ठा kmem_cache *p;
	स्थिर slab_flags_t flags = SLAB_HWCACHE_ALIGN;
	माप_प्रकार align = 1 << 10; /* L2 pagetable alignement */
	काष्ठा device_node *np;
	पूर्णांक ret;

	np = of_find_matching_node(शून्य, omap_iommu_of_match);
	अगर (!np)
		वापस 0;

	of_node_put(np);

	p = kmem_cache_create("iopte_cache", IOPTE_TABLE_SIZE, align, flags,
			      शून्य);
	अगर (!p)
		वापस -ENOMEM;
	iopte_cachep = p;

	omap_iommu_debugfs_init();

	ret = platक्रमm_driver_रेजिस्टर(&omap_iommu_driver);
	अगर (ret) अणु
		pr_err("%s: failed to register driver\n", __func__);
		जाओ fail_driver;
	पूर्ण

	ret = bus_set_iommu(&platक्रमm_bus_type, &omap_iommu_ops);
	अगर (ret)
		जाओ fail_bus;

	वापस 0;

fail_bus:
	platक्रमm_driver_unरेजिस्टर(&omap_iommu_driver);
fail_driver:
	kmem_cache_destroy(iopte_cachep);
	वापस ret;
पूर्ण
subsys_initcall(omap_iommu_init);
/* must be पढ़ोy beक्रमe omap3isp is probed */
