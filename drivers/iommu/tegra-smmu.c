<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2011-2014 NVIDIA CORPORATION.  All rights reserved.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/err.h>
#समावेश <linux/iommu.h>
#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pci.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/dma-mapping.h>

#समावेश <soc/tegra/ahb.h>
#समावेश <soc/tegra/mc.h>

काष्ठा tegra_smmu_group अणु
	काष्ठा list_head list;
	काष्ठा tegra_smmu *smmu;
	स्थिर काष्ठा tegra_smmu_group_soc *soc;
	काष्ठा iommu_group *group;
	अचिन्हित पूर्णांक swgroup;
पूर्ण;

काष्ठा tegra_smmu अणु
	व्योम __iomem *regs;
	काष्ठा device *dev;

	काष्ठा tegra_mc *mc;
	स्थिर काष्ठा tegra_smmu_soc *soc;

	काष्ठा list_head groups;

	अचिन्हित दीर्घ pfn_mask;
	अचिन्हित दीर्घ tlb_mask;

	अचिन्हित दीर्घ *asids;
	काष्ठा mutex lock;

	काष्ठा list_head list;

	काष्ठा dentry *debugfs;

	काष्ठा iommu_device iommu;	/* IOMMU Core code handle */
पूर्ण;

काष्ठा tegra_smmu_as अणु
	काष्ठा iommu_करोमुख्य करोमुख्य;
	काष्ठा tegra_smmu *smmu;
	अचिन्हित पूर्णांक use_count;
	spinlock_t lock;
	u32 *count;
	काष्ठा page **pts;
	काष्ठा page *pd;
	dma_addr_t pd_dma;
	अचिन्हित id;
	u32 attr;
पूर्ण;

अटल काष्ठा tegra_smmu_as *to_smmu_as(काष्ठा iommu_करोमुख्य *करोm)
अणु
	वापस container_of(करोm, काष्ठा tegra_smmu_as, करोमुख्य);
पूर्ण

अटल अंतरभूत व्योम smmu_ग_लिखोl(काष्ठा tegra_smmu *smmu, u32 value,
			       अचिन्हित दीर्घ offset)
अणु
	ग_लिखोl(value, smmu->regs + offset);
पूर्ण

अटल अंतरभूत u32 smmu_पढ़ोl(काष्ठा tegra_smmu *smmu, अचिन्हित दीर्घ offset)
अणु
	वापस पढ़ोl(smmu->regs + offset);
पूर्ण

#घोषणा SMMU_CONFIG 0x010
#घोषणा  SMMU_CONFIG_ENABLE (1 << 0)

#घोषणा SMMU_TLB_CONFIG 0x14
#घोषणा  SMMU_TLB_CONFIG_HIT_UNDER_MISS (1 << 29)
#घोषणा  SMMU_TLB_CONFIG_ROUND_ROBIN_ARBITRATION (1 << 28)
#घोषणा  SMMU_TLB_CONFIG_ACTIVE_LINES(smmu) \
	((smmu)->soc->num_tlb_lines & (smmu)->tlb_mask)

#घोषणा SMMU_PTC_CONFIG 0x18
#घोषणा  SMMU_PTC_CONFIG_ENABLE (1 << 29)
#घोषणा  SMMU_PTC_CONFIG_REQ_LIMIT(x) (((x) & 0x0f) << 24)
#घोषणा  SMMU_PTC_CONFIG_INDEX_MAP(x) ((x) & 0x3f)

#घोषणा SMMU_PTB_ASID 0x01c
#घोषणा  SMMU_PTB_ASID_VALUE(x) ((x) & 0x7f)

#घोषणा SMMU_PTB_DATA 0x020
#घोषणा  SMMU_PTB_DATA_VALUE(dma, attr) ((dma) >> 12 | (attr))

#घोषणा SMMU_MK_PDE(dma, attr) ((dma) >> SMMU_PTE_SHIFT | (attr))

#घोषणा SMMU_TLB_FLUSH 0x030
#घोषणा  SMMU_TLB_FLUSH_VA_MATCH_ALL     (0 << 0)
#घोषणा  SMMU_TLB_FLUSH_VA_MATCH_SECTION (2 << 0)
#घोषणा  SMMU_TLB_FLUSH_VA_MATCH_GROUP   (3 << 0)
#घोषणा  SMMU_TLB_FLUSH_VA_SECTION(addr) ((((addr) & 0xffc00000) >> 12) | \
					  SMMU_TLB_FLUSH_VA_MATCH_SECTION)
#घोषणा  SMMU_TLB_FLUSH_VA_GROUP(addr)   ((((addr) & 0xffffc000) >> 12) | \
					  SMMU_TLB_FLUSH_VA_MATCH_GROUP)
#घोषणा  SMMU_TLB_FLUSH_ASID_MATCH       (1 << 31)

#घोषणा SMMU_PTC_FLUSH 0x034
#घोषणा  SMMU_PTC_FLUSH_TYPE_ALL (0 << 0)
#घोषणा  SMMU_PTC_FLUSH_TYPE_ADR (1 << 0)

#घोषणा SMMU_PTC_FLUSH_HI 0x9b8
#घोषणा  SMMU_PTC_FLUSH_HI_MASK 0x3

/* per-SWGROUP SMMU_*_ASID रेजिस्टर */
#घोषणा SMMU_ASID_ENABLE (1 << 31)
#घोषणा SMMU_ASID_MASK 0x7f
#घोषणा SMMU_ASID_VALUE(x) ((x) & SMMU_ASID_MASK)

/* page table definitions */
#घोषणा SMMU_NUM_PDE 1024
#घोषणा SMMU_NUM_PTE 1024

#घोषणा SMMU_SIZE_PD (SMMU_NUM_PDE * 4)
#घोषणा SMMU_SIZE_PT (SMMU_NUM_PTE * 4)

#घोषणा SMMU_PDE_SHIFT 22
#घोषणा SMMU_PTE_SHIFT 12

#घोषणा SMMU_PAGE_MASK		(~(SMMU_SIZE_PT-1))
#घोषणा SMMU_OFFSET_IN_PAGE(x)	((अचिन्हित दीर्घ)(x) & ~SMMU_PAGE_MASK)
#घोषणा SMMU_PFN_PHYS(x)	((phys_addr_t)(x) << SMMU_PTE_SHIFT)
#घोषणा SMMU_PHYS_PFN(x)	((अचिन्हित दीर्घ)((x) >> SMMU_PTE_SHIFT))

#घोषणा SMMU_PD_READABLE	(1 << 31)
#घोषणा SMMU_PD_WRITABLE	(1 << 30)
#घोषणा SMMU_PD_NONSECURE	(1 << 29)

#घोषणा SMMU_PDE_READABLE	(1 << 31)
#घोषणा SMMU_PDE_WRITABLE	(1 << 30)
#घोषणा SMMU_PDE_NONSECURE	(1 << 29)
#घोषणा SMMU_PDE_NEXT		(1 << 28)

#घोषणा SMMU_PTE_READABLE	(1 << 31)
#घोषणा SMMU_PTE_WRITABLE	(1 << 30)
#घोषणा SMMU_PTE_NONSECURE	(1 << 29)

#घोषणा SMMU_PDE_ATTR		(SMMU_PDE_READABLE | SMMU_PDE_WRITABLE | \
				 SMMU_PDE_NONSECURE)

अटल अचिन्हित पूर्णांक iova_pd_index(अचिन्हित दीर्घ iova)
अणु
	वापस (iova >> SMMU_PDE_SHIFT) & (SMMU_NUM_PDE - 1);
पूर्ण

अटल अचिन्हित पूर्णांक iova_pt_index(अचिन्हित दीर्घ iova)
अणु
	वापस (iova >> SMMU_PTE_SHIFT) & (SMMU_NUM_PTE - 1);
पूर्ण

अटल bool smmu_dma_addr_valid(काष्ठा tegra_smmu *smmu, dma_addr_t addr)
अणु
	addr >>= 12;
	वापस (addr & smmu->pfn_mask) == addr;
पूर्ण

अटल dma_addr_t smmu_pde_to_dma(काष्ठा tegra_smmu *smmu, u32 pde)
अणु
	वापस (dma_addr_t)(pde & smmu->pfn_mask) << 12;
पूर्ण

अटल व्योम smmu_flush_ptc_all(काष्ठा tegra_smmu *smmu)
अणु
	smmu_ग_लिखोl(smmu, SMMU_PTC_FLUSH_TYPE_ALL, SMMU_PTC_FLUSH);
पूर्ण

अटल अंतरभूत व्योम smmu_flush_ptc(काष्ठा tegra_smmu *smmu, dma_addr_t dma,
				  अचिन्हित दीर्घ offset)
अणु
	u32 value;

	offset &= ~(smmu->mc->soc->atom_size - 1);

	अगर (smmu->mc->soc->num_address_bits > 32) अणु
#अगर_घोषित CONFIG_ARCH_DMA_ADDR_T_64BIT
		value = (dma >> 32) & SMMU_PTC_FLUSH_HI_MASK;
#अन्यथा
		value = 0;
#पूर्ण_अगर
		smmu_ग_लिखोl(smmu, value, SMMU_PTC_FLUSH_HI);
	पूर्ण

	value = (dma + offset) | SMMU_PTC_FLUSH_TYPE_ADR;
	smmu_ग_लिखोl(smmu, value, SMMU_PTC_FLUSH);
पूर्ण

अटल अंतरभूत व्योम smmu_flush_tlb(काष्ठा tegra_smmu *smmu)
अणु
	smmu_ग_लिखोl(smmu, SMMU_TLB_FLUSH_VA_MATCH_ALL, SMMU_TLB_FLUSH);
पूर्ण

अटल अंतरभूत व्योम smmu_flush_tlb_asid(काष्ठा tegra_smmu *smmu,
				       अचिन्हित दीर्घ asid)
अणु
	u32 value;

	अगर (smmu->soc->num_asids == 4)
		value = (asid & 0x3) << 29;
	अन्यथा
		value = (asid & 0x7f) << 24;

	value |= SMMU_TLB_FLUSH_ASID_MATCH | SMMU_TLB_FLUSH_VA_MATCH_ALL;
	smmu_ग_लिखोl(smmu, value, SMMU_TLB_FLUSH);
पूर्ण

अटल अंतरभूत व्योम smmu_flush_tlb_section(काष्ठा tegra_smmu *smmu,
					  अचिन्हित दीर्घ asid,
					  अचिन्हित दीर्घ iova)
अणु
	u32 value;

	अगर (smmu->soc->num_asids == 4)
		value = (asid & 0x3) << 29;
	अन्यथा
		value = (asid & 0x7f) << 24;

	value |= SMMU_TLB_FLUSH_ASID_MATCH | SMMU_TLB_FLUSH_VA_SECTION(iova);
	smmu_ग_लिखोl(smmu, value, SMMU_TLB_FLUSH);
पूर्ण

अटल अंतरभूत व्योम smmu_flush_tlb_group(काष्ठा tegra_smmu *smmu,
					अचिन्हित दीर्घ asid,
					अचिन्हित दीर्घ iova)
अणु
	u32 value;

	अगर (smmu->soc->num_asids == 4)
		value = (asid & 0x3) << 29;
	अन्यथा
		value = (asid & 0x7f) << 24;

	value |= SMMU_TLB_FLUSH_ASID_MATCH | SMMU_TLB_FLUSH_VA_GROUP(iova);
	smmu_ग_लिखोl(smmu, value, SMMU_TLB_FLUSH);
पूर्ण

अटल अंतरभूत व्योम smmu_flush(काष्ठा tegra_smmu *smmu)
अणु
	smmu_पढ़ोl(smmu, SMMU_PTB_ASID);
पूर्ण

अटल पूर्णांक tegra_smmu_alloc_asid(काष्ठा tegra_smmu *smmu, अचिन्हित पूर्णांक *idp)
अणु
	अचिन्हित दीर्घ id;

	id = find_first_zero_bit(smmu->asids, smmu->soc->num_asids);
	अगर (id >= smmu->soc->num_asids)
		वापस -ENOSPC;

	set_bit(id, smmu->asids);
	*idp = id;

	वापस 0;
पूर्ण

अटल व्योम tegra_smmu_मुक्त_asid(काष्ठा tegra_smmu *smmu, अचिन्हित पूर्णांक id)
अणु
	clear_bit(id, smmu->asids);
पूर्ण

अटल bool tegra_smmu_capable(क्रमागत iommu_cap cap)
अणु
	वापस false;
पूर्ण

अटल काष्ठा iommu_करोमुख्य *tegra_smmu_करोमुख्य_alloc(अचिन्हित type)
अणु
	काष्ठा tegra_smmu_as *as;

	अगर (type != IOMMU_DOMAIN_UNMANAGED)
		वापस शून्य;

	as = kzalloc(माप(*as), GFP_KERNEL);
	अगर (!as)
		वापस शून्य;

	as->attr = SMMU_PD_READABLE | SMMU_PD_WRITABLE | SMMU_PD_NONSECURE;

	as->pd = alloc_page(GFP_KERNEL | __GFP_DMA | __GFP_ZERO);
	अगर (!as->pd) अणु
		kमुक्त(as);
		वापस शून्य;
	पूर्ण

	as->count = kसुस्मृति(SMMU_NUM_PDE, माप(u32), GFP_KERNEL);
	अगर (!as->count) अणु
		__मुक्त_page(as->pd);
		kमुक्त(as);
		वापस शून्य;
	पूर्ण

	as->pts = kसुस्मृति(SMMU_NUM_PDE, माप(*as->pts), GFP_KERNEL);
	अगर (!as->pts) अणु
		kमुक्त(as->count);
		__मुक्त_page(as->pd);
		kमुक्त(as);
		वापस शून्य;
	पूर्ण

	spin_lock_init(&as->lock);

	/* setup aperture */
	as->करोमुख्य.geometry.aperture_start = 0;
	as->करोमुख्य.geometry.aperture_end = 0xffffffff;
	as->करोमुख्य.geometry.क्रमce_aperture = true;

	वापस &as->करोमुख्य;
पूर्ण

अटल व्योम tegra_smmu_करोमुख्य_मुक्त(काष्ठा iommu_करोमुख्य *करोमुख्य)
अणु
	काष्ठा tegra_smmu_as *as = to_smmu_as(करोमुख्य);

	/* TODO: मुक्त page directory and page tables */

	WARN_ON_ONCE(as->use_count);
	kमुक्त(as->count);
	kमुक्त(as->pts);
	kमुक्त(as);
पूर्ण

अटल स्थिर काष्ठा tegra_smmu_swgroup *
tegra_smmu_find_swgroup(काष्ठा tegra_smmu *smmu, अचिन्हित पूर्णांक swgroup)
अणु
	स्थिर काष्ठा tegra_smmu_swgroup *group = शून्य;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < smmu->soc->num_swgroups; i++) अणु
		अगर (smmu->soc->swgroups[i].swgroup == swgroup) अणु
			group = &smmu->soc->swgroups[i];
			अवरोध;
		पूर्ण
	पूर्ण

	वापस group;
पूर्ण

अटल व्योम tegra_smmu_enable(काष्ठा tegra_smmu *smmu, अचिन्हित पूर्णांक swgroup,
			      अचिन्हित पूर्णांक asid)
अणु
	स्थिर काष्ठा tegra_smmu_swgroup *group;
	अचिन्हित पूर्णांक i;
	u32 value;

	group = tegra_smmu_find_swgroup(smmu, swgroup);
	अगर (group) अणु
		value = smmu_पढ़ोl(smmu, group->reg);
		value &= ~SMMU_ASID_MASK;
		value |= SMMU_ASID_VALUE(asid);
		value |= SMMU_ASID_ENABLE;
		smmu_ग_लिखोl(smmu, value, group->reg);
	पूर्ण अन्यथा अणु
		pr_warn("%s group from swgroup %u not found\n", __func__,
				swgroup);
		/* No poपूर्णांक moving ahead अगर group was not found */
		वापस;
	पूर्ण

	क्रम (i = 0; i < smmu->soc->num_clients; i++) अणु
		स्थिर काष्ठा tegra_mc_client *client = &smmu->soc->clients[i];

		अगर (client->swgroup != swgroup)
			जारी;

		value = smmu_पढ़ोl(smmu, client->smmu.reg);
		value |= BIT(client->smmu.bit);
		smmu_ग_लिखोl(smmu, value, client->smmu.reg);
	पूर्ण
पूर्ण

अटल व्योम tegra_smmu_disable(काष्ठा tegra_smmu *smmu, अचिन्हित पूर्णांक swgroup,
			       अचिन्हित पूर्णांक asid)
अणु
	स्थिर काष्ठा tegra_smmu_swgroup *group;
	अचिन्हित पूर्णांक i;
	u32 value;

	group = tegra_smmu_find_swgroup(smmu, swgroup);
	अगर (group) अणु
		value = smmu_पढ़ोl(smmu, group->reg);
		value &= ~SMMU_ASID_MASK;
		value |= SMMU_ASID_VALUE(asid);
		value &= ~SMMU_ASID_ENABLE;
		smmu_ग_लिखोl(smmu, value, group->reg);
	पूर्ण

	क्रम (i = 0; i < smmu->soc->num_clients; i++) अणु
		स्थिर काष्ठा tegra_mc_client *client = &smmu->soc->clients[i];

		अगर (client->swgroup != swgroup)
			जारी;

		value = smmu_पढ़ोl(smmu, client->smmu.reg);
		value &= ~BIT(client->smmu.bit);
		smmu_ग_लिखोl(smmu, value, client->smmu.reg);
	पूर्ण
पूर्ण

अटल पूर्णांक tegra_smmu_as_prepare(काष्ठा tegra_smmu *smmu,
				 काष्ठा tegra_smmu_as *as)
अणु
	u32 value;
	पूर्णांक err = 0;

	mutex_lock(&smmu->lock);

	अगर (as->use_count > 0) अणु
		as->use_count++;
		जाओ unlock;
	पूर्ण

	as->pd_dma = dma_map_page(smmu->dev, as->pd, 0, SMMU_SIZE_PD,
				  DMA_TO_DEVICE);
	अगर (dma_mapping_error(smmu->dev, as->pd_dma)) अणु
		err = -ENOMEM;
		जाओ unlock;
	पूर्ण

	/* We can't handle 64-bit DMA addresses */
	अगर (!smmu_dma_addr_valid(smmu, as->pd_dma)) अणु
		err = -ENOMEM;
		जाओ err_unmap;
	पूर्ण

	err = tegra_smmu_alloc_asid(smmu, &as->id);
	अगर (err < 0)
		जाओ err_unmap;

	smmu_flush_ptc(smmu, as->pd_dma, 0);
	smmu_flush_tlb_asid(smmu, as->id);

	smmu_ग_लिखोl(smmu, as->id & 0x7f, SMMU_PTB_ASID);
	value = SMMU_PTB_DATA_VALUE(as->pd_dma, as->attr);
	smmu_ग_लिखोl(smmu, value, SMMU_PTB_DATA);
	smmu_flush(smmu);

	as->smmu = smmu;
	as->use_count++;

	mutex_unlock(&smmu->lock);

	वापस 0;

err_unmap:
	dma_unmap_page(smmu->dev, as->pd_dma, SMMU_SIZE_PD, DMA_TO_DEVICE);
unlock:
	mutex_unlock(&smmu->lock);

	वापस err;
पूर्ण

अटल व्योम tegra_smmu_as_unprepare(काष्ठा tegra_smmu *smmu,
				    काष्ठा tegra_smmu_as *as)
अणु
	mutex_lock(&smmu->lock);

	अगर (--as->use_count > 0) अणु
		mutex_unlock(&smmu->lock);
		वापस;
	पूर्ण

	tegra_smmu_मुक्त_asid(smmu, as->id);

	dma_unmap_page(smmu->dev, as->pd_dma, SMMU_SIZE_PD, DMA_TO_DEVICE);

	as->smmu = शून्य;

	mutex_unlock(&smmu->lock);
पूर्ण

अटल पूर्णांक tegra_smmu_attach_dev(काष्ठा iommu_करोमुख्य *करोमुख्य,
				 काष्ठा device *dev)
अणु
	काष्ठा iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);
	काष्ठा tegra_smmu *smmu = dev_iommu_priv_get(dev);
	काष्ठा tegra_smmu_as *as = to_smmu_as(करोमुख्य);
	अचिन्हित पूर्णांक index;
	पूर्णांक err;

	अगर (!fwspec)
		वापस -ENOENT;

	क्रम (index = 0; index < fwspec->num_ids; index++) अणु
		err = tegra_smmu_as_prepare(smmu, as);
		अगर (err)
			जाओ disable;

		tegra_smmu_enable(smmu, fwspec->ids[index], as->id);
	पूर्ण

	अगर (index == 0)
		वापस -ENODEV;

	वापस 0;

disable:
	जबतक (index--) अणु
		tegra_smmu_disable(smmu, fwspec->ids[index], as->id);
		tegra_smmu_as_unprepare(smmu, as);
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम tegra_smmu_detach_dev(काष्ठा iommu_करोमुख्य *करोमुख्य, काष्ठा device *dev)
अणु
	काष्ठा iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);
	काष्ठा tegra_smmu_as *as = to_smmu_as(करोमुख्य);
	काष्ठा tegra_smmu *smmu = as->smmu;
	अचिन्हित पूर्णांक index;

	अगर (!fwspec)
		वापस;

	क्रम (index = 0; index < fwspec->num_ids; index++) अणु
		tegra_smmu_disable(smmu, fwspec->ids[index], as->id);
		tegra_smmu_as_unprepare(smmu, as);
	पूर्ण
पूर्ण

अटल व्योम tegra_smmu_set_pde(काष्ठा tegra_smmu_as *as, अचिन्हित दीर्घ iova,
			       u32 value)
अणु
	अचिन्हित पूर्णांक pd_index = iova_pd_index(iova);
	काष्ठा tegra_smmu *smmu = as->smmu;
	u32 *pd = page_address(as->pd);
	अचिन्हित दीर्घ offset = pd_index * माप(*pd);

	/* Set the page directory entry first */
	pd[pd_index] = value;

	/* The flush the page directory entry from caches */
	dma_sync_single_range_क्रम_device(smmu->dev, as->pd_dma, offset,
					 माप(*pd), DMA_TO_DEVICE);

	/* And flush the iommu */
	smmu_flush_ptc(smmu, as->pd_dma, offset);
	smmu_flush_tlb_section(smmu, as->id, iova);
	smmu_flush(smmu);
पूर्ण

अटल u32 *tegra_smmu_pte_offset(काष्ठा page *pt_page, अचिन्हित दीर्घ iova)
अणु
	u32 *pt = page_address(pt_page);

	वापस pt + iova_pt_index(iova);
पूर्ण

अटल u32 *tegra_smmu_pte_lookup(काष्ठा tegra_smmu_as *as, अचिन्हित दीर्घ iova,
				  dma_addr_t *dmap)
अणु
	अचिन्हित पूर्णांक pd_index = iova_pd_index(iova);
	काष्ठा tegra_smmu *smmu = as->smmu;
	काष्ठा page *pt_page;
	u32 *pd;

	pt_page = as->pts[pd_index];
	अगर (!pt_page)
		वापस शून्य;

	pd = page_address(as->pd);
	*dmap = smmu_pde_to_dma(smmu, pd[pd_index]);

	वापस tegra_smmu_pte_offset(pt_page, iova);
पूर्ण

अटल u32 *as_get_pte(काष्ठा tegra_smmu_as *as, dma_addr_t iova,
		       dma_addr_t *dmap, काष्ठा page *page)
अणु
	अचिन्हित पूर्णांक pde = iova_pd_index(iova);
	काष्ठा tegra_smmu *smmu = as->smmu;

	अगर (!as->pts[pde]) अणु
		dma_addr_t dma;

		dma = dma_map_page(smmu->dev, page, 0, SMMU_SIZE_PT,
				   DMA_TO_DEVICE);
		अगर (dma_mapping_error(smmu->dev, dma)) अणु
			__मुक्त_page(page);
			वापस शून्य;
		पूर्ण

		अगर (!smmu_dma_addr_valid(smmu, dma)) अणु
			dma_unmap_page(smmu->dev, dma, SMMU_SIZE_PT,
				       DMA_TO_DEVICE);
			__मुक्त_page(page);
			वापस शून्य;
		पूर्ण

		as->pts[pde] = page;

		tegra_smmu_set_pde(as, iova, SMMU_MK_PDE(dma, SMMU_PDE_ATTR |
							      SMMU_PDE_NEXT));

		*dmap = dma;
	पूर्ण अन्यथा अणु
		u32 *pd = page_address(as->pd);

		*dmap = smmu_pde_to_dma(smmu, pd[pde]);
	पूर्ण

	वापस tegra_smmu_pte_offset(as->pts[pde], iova);
पूर्ण

अटल व्योम tegra_smmu_pte_get_use(काष्ठा tegra_smmu_as *as, अचिन्हित दीर्घ iova)
अणु
	अचिन्हित पूर्णांक pd_index = iova_pd_index(iova);

	as->count[pd_index]++;
पूर्ण

अटल व्योम tegra_smmu_pte_put_use(काष्ठा tegra_smmu_as *as, अचिन्हित दीर्घ iova)
अणु
	अचिन्हित पूर्णांक pde = iova_pd_index(iova);
	काष्ठा page *page = as->pts[pde];

	/*
	 * When no entries in this page table are used anymore, वापस the
	 * memory page to the प्रणाली.
	 */
	अगर (--as->count[pde] == 0) अणु
		काष्ठा tegra_smmu *smmu = as->smmu;
		u32 *pd = page_address(as->pd);
		dma_addr_t pte_dma = smmu_pde_to_dma(smmu, pd[pde]);

		tegra_smmu_set_pde(as, iova, 0);

		dma_unmap_page(smmu->dev, pte_dma, SMMU_SIZE_PT, DMA_TO_DEVICE);
		__मुक्त_page(page);
		as->pts[pde] = शून्य;
	पूर्ण
पूर्ण

अटल व्योम tegra_smmu_set_pte(काष्ठा tegra_smmu_as *as, अचिन्हित दीर्घ iova,
			       u32 *pte, dma_addr_t pte_dma, u32 val)
अणु
	काष्ठा tegra_smmu *smmu = as->smmu;
	अचिन्हित दीर्घ offset = SMMU_OFFSET_IN_PAGE(pte);

	*pte = val;

	dma_sync_single_range_क्रम_device(smmu->dev, pte_dma, offset,
					 4, DMA_TO_DEVICE);
	smmu_flush_ptc(smmu, pte_dma, offset);
	smmu_flush_tlb_group(smmu, as->id, iova);
	smmu_flush(smmu);
पूर्ण

अटल काष्ठा page *as_get_pde_page(काष्ठा tegra_smmu_as *as,
				    अचिन्हित दीर्घ iova, gfp_t gfp,
				    अचिन्हित दीर्घ *flags)
अणु
	अचिन्हित पूर्णांक pde = iova_pd_index(iova);
	काष्ठा page *page = as->pts[pde];

	/* at first check whether allocation needs to be करोne at all */
	अगर (page)
		वापस page;

	/*
	 * In order to prevent exhaustion of the atomic memory pool, we
	 * allocate page in a sleeping context अगर GFP flags permit. Hence
	 * spinlock needs to be unlocked and re-locked after allocation.
	 */
	अगर (!(gfp & __GFP_ATOMIC))
		spin_unlock_irqrestore(&as->lock, *flags);

	page = alloc_page(gfp | __GFP_DMA | __GFP_ZERO);

	अगर (!(gfp & __GFP_ATOMIC))
		spin_lock_irqsave(&as->lock, *flags);

	/*
	 * In a हाल of blocking allocation, a concurrent mapping may win
	 * the PDE allocation. In this हाल the allocated page isn't needed
	 * अगर allocation succeeded and the allocation failure isn't fatal.
	 */
	अगर (as->pts[pde]) अणु
		अगर (page)
			__मुक्त_page(page);

		page = as->pts[pde];
	पूर्ण

	वापस page;
पूर्ण

अटल पूर्णांक
__tegra_smmu_map(काष्ठा iommu_करोमुख्य *करोमुख्य, अचिन्हित दीर्घ iova,
		 phys_addr_t paddr, माप_प्रकार size, पूर्णांक prot, gfp_t gfp,
		 अचिन्हित दीर्घ *flags)
अणु
	काष्ठा tegra_smmu_as *as = to_smmu_as(करोमुख्य);
	dma_addr_t pte_dma;
	काष्ठा page *page;
	u32 pte_attrs;
	u32 *pte;

	page = as_get_pde_page(as, iova, gfp, flags);
	अगर (!page)
		वापस -ENOMEM;

	pte = as_get_pte(as, iova, &pte_dma, page);
	अगर (!pte)
		वापस -ENOMEM;

	/* If we aren't overwriting a pre-existing entry, increment use */
	अगर (*pte == 0)
		tegra_smmu_pte_get_use(as, iova);

	pte_attrs = SMMU_PTE_NONSECURE;

	अगर (prot & IOMMU_READ)
		pte_attrs |= SMMU_PTE_READABLE;

	अगर (prot & IOMMU_WRITE)
		pte_attrs |= SMMU_PTE_WRITABLE;

	tegra_smmu_set_pte(as, iova, pte, pte_dma,
			   SMMU_PHYS_PFN(paddr) | pte_attrs);

	वापस 0;
पूर्ण

अटल माप_प्रकार
__tegra_smmu_unmap(काष्ठा iommu_करोमुख्य *करोमुख्य, अचिन्हित दीर्घ iova,
		   माप_प्रकार size, काष्ठा iommu_iotlb_gather *gather)
अणु
	काष्ठा tegra_smmu_as *as = to_smmu_as(करोमुख्य);
	dma_addr_t pte_dma;
	u32 *pte;

	pte = tegra_smmu_pte_lookup(as, iova, &pte_dma);
	अगर (!pte || !*pte)
		वापस 0;

	tegra_smmu_set_pte(as, iova, pte, pte_dma, 0);
	tegra_smmu_pte_put_use(as, iova);

	वापस size;
पूर्ण

अटल पूर्णांक tegra_smmu_map(काष्ठा iommu_करोमुख्य *करोमुख्य, अचिन्हित दीर्घ iova,
			  phys_addr_t paddr, माप_प्रकार size, पूर्णांक prot, gfp_t gfp)
अणु
	काष्ठा tegra_smmu_as *as = to_smmu_as(करोमुख्य);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&as->lock, flags);
	ret = __tegra_smmu_map(करोमुख्य, iova, paddr, size, prot, gfp, &flags);
	spin_unlock_irqrestore(&as->lock, flags);

	वापस ret;
पूर्ण

अटल माप_प्रकार tegra_smmu_unmap(काष्ठा iommu_करोमुख्य *करोमुख्य, अचिन्हित दीर्घ iova,
			       माप_प्रकार size, काष्ठा iommu_iotlb_gather *gather)
अणु
	काष्ठा tegra_smmu_as *as = to_smmu_as(करोमुख्य);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&as->lock, flags);
	size = __tegra_smmu_unmap(करोमुख्य, iova, size, gather);
	spin_unlock_irqrestore(&as->lock, flags);

	वापस size;
पूर्ण

अटल phys_addr_t tegra_smmu_iova_to_phys(काष्ठा iommu_करोमुख्य *करोमुख्य,
					   dma_addr_t iova)
अणु
	काष्ठा tegra_smmu_as *as = to_smmu_as(करोमुख्य);
	अचिन्हित दीर्घ pfn;
	dma_addr_t pte_dma;
	u32 *pte;

	pte = tegra_smmu_pte_lookup(as, iova, &pte_dma);
	अगर (!pte || !*pte)
		वापस 0;

	pfn = *pte & as->smmu->pfn_mask;

	वापस SMMU_PFN_PHYS(pfn) + SMMU_OFFSET_IN_PAGE(iova);
पूर्ण

अटल काष्ठा tegra_smmu *tegra_smmu_find(काष्ठा device_node *np)
अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा tegra_mc *mc;

	pdev = of_find_device_by_node(np);
	अगर (!pdev)
		वापस शून्य;

	mc = platक्रमm_get_drvdata(pdev);
	अगर (!mc)
		वापस शून्य;

	वापस mc->smmu;
पूर्ण

अटल पूर्णांक tegra_smmu_configure(काष्ठा tegra_smmu *smmu, काष्ठा device *dev,
				काष्ठा of_phandle_args *args)
अणु
	स्थिर काष्ठा iommu_ops *ops = smmu->iommu.ops;
	पूर्णांक err;

	err = iommu_fwspec_init(dev, &dev->of_node->fwnode, ops);
	अगर (err < 0) अणु
		dev_err(dev, "failed to initialize fwspec: %d\n", err);
		वापस err;
	पूर्ण

	err = ops->of_xlate(dev, args);
	अगर (err < 0) अणु
		dev_err(dev, "failed to parse SW group ID: %d\n", err);
		iommu_fwspec_मुक्त(dev);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा iommu_device *tegra_smmu_probe_device(काष्ठा device *dev)
अणु
	काष्ठा device_node *np = dev->of_node;
	काष्ठा tegra_smmu *smmu = शून्य;
	काष्ठा of_phandle_args args;
	अचिन्हित पूर्णांक index = 0;
	पूर्णांक err;

	जबतक (of_parse_phandle_with_args(np, "iommus", "#iommu-cells", index,
					  &args) == 0) अणु
		smmu = tegra_smmu_find(args.np);
		अगर (smmu) अणु
			err = tegra_smmu_configure(smmu, dev, &args);

			अगर (err < 0) अणु
				of_node_put(args.np);
				वापस ERR_PTR(err);
			पूर्ण
		पूर्ण

		of_node_put(args.np);
		index++;
	पूर्ण

	smmu = dev_iommu_priv_get(dev);
	अगर (!smmu)
		वापस ERR_PTR(-ENODEV);

	वापस &smmu->iommu;
पूर्ण

अटल व्योम tegra_smmu_release_device(काष्ठा device *dev) अणुपूर्ण

अटल स्थिर काष्ठा tegra_smmu_group_soc *
tegra_smmu_find_group(काष्ठा tegra_smmu *smmu, अचिन्हित पूर्णांक swgroup)
अणु
	अचिन्हित पूर्णांक i, j;

	क्रम (i = 0; i < smmu->soc->num_groups; i++)
		क्रम (j = 0; j < smmu->soc->groups[i].num_swgroups; j++)
			अगर (smmu->soc->groups[i].swgroups[j] == swgroup)
				वापस &smmu->soc->groups[i];

	वापस शून्य;
पूर्ण

अटल व्योम tegra_smmu_group_release(व्योम *iommu_data)
अणु
	काष्ठा tegra_smmu_group *group = iommu_data;
	काष्ठा tegra_smmu *smmu = group->smmu;

	mutex_lock(&smmu->lock);
	list_del(&group->list);
	mutex_unlock(&smmu->lock);
पूर्ण

अटल काष्ठा iommu_group *tegra_smmu_device_group(काष्ठा device *dev)
अणु
	काष्ठा iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);
	काष्ठा tegra_smmu *smmu = dev_iommu_priv_get(dev);
	स्थिर काष्ठा tegra_smmu_group_soc *soc;
	अचिन्हित पूर्णांक swgroup = fwspec->ids[0];
	काष्ठा tegra_smmu_group *group;
	काष्ठा iommu_group *grp;

	/* Find group_soc associating with swgroup */
	soc = tegra_smmu_find_group(smmu, swgroup);

	mutex_lock(&smmu->lock);

	/* Find existing iommu_group associating with swgroup or group_soc */
	list_क्रम_each_entry(group, &smmu->groups, list)
		अगर ((group->swgroup == swgroup) || (soc && group->soc == soc)) अणु
			grp = iommu_group_ref_get(group->group);
			mutex_unlock(&smmu->lock);
			वापस grp;
		पूर्ण

	group = devm_kzalloc(smmu->dev, माप(*group), GFP_KERNEL);
	अगर (!group) अणु
		mutex_unlock(&smmu->lock);
		वापस शून्य;
	पूर्ण

	INIT_LIST_HEAD(&group->list);
	group->swgroup = swgroup;
	group->smmu = smmu;
	group->soc = soc;

	अगर (dev_is_pci(dev))
		group->group = pci_device_group(dev);
	अन्यथा
		group->group = generic_device_group(dev);

	अगर (IS_ERR(group->group)) अणु
		devm_kमुक्त(smmu->dev, group);
		mutex_unlock(&smmu->lock);
		वापस शून्य;
	पूर्ण

	iommu_group_set_iommudata(group->group, group, tegra_smmu_group_release);
	अगर (soc)
		iommu_group_set_name(group->group, soc->name);
	list_add_tail(&group->list, &smmu->groups);
	mutex_unlock(&smmu->lock);

	वापस group->group;
पूर्ण

अटल पूर्णांक tegra_smmu_of_xlate(काष्ठा device *dev,
			       काष्ठा of_phandle_args *args)
अणु
	काष्ठा platक्रमm_device *iommu_pdev = of_find_device_by_node(args->np);
	काष्ठा tegra_mc *mc = platक्रमm_get_drvdata(iommu_pdev);
	u32 id = args->args[0];

	/*
	 * Note: we are here releasing the reference of &iommu_pdev->dev, which
	 * is mc->dev. Although some functions in tegra_smmu_ops may keep using
	 * its निजी data beyond this poपूर्णांक, it's still safe to करो so because
	 * the SMMU parent device is the same as the MC, so the reference count
	 * isn't strictly necessary.
	 */
	put_device(&iommu_pdev->dev);

	dev_iommu_priv_set(dev, mc->smmu);

	वापस iommu_fwspec_add_ids(dev, &id, 1);
पूर्ण

अटल स्थिर काष्ठा iommu_ops tegra_smmu_ops = अणु
	.capable = tegra_smmu_capable,
	.करोमुख्य_alloc = tegra_smmu_करोमुख्य_alloc,
	.करोमुख्य_मुक्त = tegra_smmu_करोमुख्य_मुक्त,
	.attach_dev = tegra_smmu_attach_dev,
	.detach_dev = tegra_smmu_detach_dev,
	.probe_device = tegra_smmu_probe_device,
	.release_device = tegra_smmu_release_device,
	.device_group = tegra_smmu_device_group,
	.map = tegra_smmu_map,
	.unmap = tegra_smmu_unmap,
	.iova_to_phys = tegra_smmu_iova_to_phys,
	.of_xlate = tegra_smmu_of_xlate,
	.pgsize_biपंचांगap = SZ_4K,
पूर्ण;

अटल व्योम tegra_smmu_ahb_enable(व्योम)
अणु
	अटल स्थिर काष्ठा of_device_id ahb_match[] = अणु
		अणु .compatible = "nvidia,tegra30-ahb", पूर्ण,
		अणु पूर्ण
	पूर्ण;
	काष्ठा device_node *ahb;

	ahb = of_find_matching_node(शून्य, ahb_match);
	अगर (ahb) अणु
		tegra_ahb_enable_smmu(ahb);
		of_node_put(ahb);
	पूर्ण
पूर्ण

अटल पूर्णांक tegra_smmu_swgroups_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा tegra_smmu *smmu = s->निजी;
	अचिन्हित पूर्णांक i;
	u32 value;

	seq_म_लिखो(s, "swgroup    enabled  ASID\n");
	seq_म_लिखो(s, "------------------------\n");

	क्रम (i = 0; i < smmu->soc->num_swgroups; i++) अणु
		स्थिर काष्ठा tegra_smmu_swgroup *group = &smmu->soc->swgroups[i];
		स्थिर अक्षर *status;
		अचिन्हित पूर्णांक asid;

		value = smmu_पढ़ोl(smmu, group->reg);

		अगर (value & SMMU_ASID_ENABLE)
			status = "yes";
		अन्यथा
			status = "no";

		asid = value & SMMU_ASID_MASK;

		seq_म_लिखो(s, "%-9s  %-7s  %#04x\n", group->name, status,
			   asid);
	पूर्ण

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(tegra_smmu_swgroups);

अटल पूर्णांक tegra_smmu_clients_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा tegra_smmu *smmu = s->निजी;
	अचिन्हित पूर्णांक i;
	u32 value;

	seq_म_लिखो(s, "client       enabled\n");
	seq_म_लिखो(s, "--------------------\n");

	क्रम (i = 0; i < smmu->soc->num_clients; i++) अणु
		स्थिर काष्ठा tegra_mc_client *client = &smmu->soc->clients[i];
		स्थिर अक्षर *status;

		value = smmu_पढ़ोl(smmu, client->smmu.reg);

		अगर (value & BIT(client->smmu.bit))
			status = "yes";
		अन्यथा
			status = "no";

		seq_म_लिखो(s, "%-12s %s\n", client->name, status);
	पूर्ण

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(tegra_smmu_clients);

अटल व्योम tegra_smmu_debugfs_init(काष्ठा tegra_smmu *smmu)
अणु
	smmu->debugfs = debugfs_create_dir("smmu", शून्य);
	अगर (!smmu->debugfs)
		वापस;

	debugfs_create_file("swgroups", S_IRUGO, smmu->debugfs, smmu,
			    &tegra_smmu_swgroups_fops);
	debugfs_create_file("clients", S_IRUGO, smmu->debugfs, smmu,
			    &tegra_smmu_clients_fops);
पूर्ण

अटल व्योम tegra_smmu_debugfs_निकास(काष्ठा tegra_smmu *smmu)
अणु
	debugfs_हटाओ_recursive(smmu->debugfs);
पूर्ण

काष्ठा tegra_smmu *tegra_smmu_probe(काष्ठा device *dev,
				    स्थिर काष्ठा tegra_smmu_soc *soc,
				    काष्ठा tegra_mc *mc)
अणु
	काष्ठा tegra_smmu *smmu;
	माप_प्रकार size;
	u32 value;
	पूर्णांक err;

	smmu = devm_kzalloc(dev, माप(*smmu), GFP_KERNEL);
	अगर (!smmu)
		वापस ERR_PTR(-ENOMEM);

	/*
	 * This is a bit of a hack. Ideally we'd want to simply वापस this
	 * value. However the IOMMU registration process will attempt to add
	 * all devices to the IOMMU when bus_set_iommu() is called. In order
	 * not to rely on global variables to track the IOMMU instance, we
	 * set it here so that it can be looked up from the .probe_device()
	 * callback via the IOMMU device's .drvdata field.
	 */
	mc->smmu = smmu;

	size = BITS_TO_LONGS(soc->num_asids) * माप(दीर्घ);

	smmu->asids = devm_kzalloc(dev, size, GFP_KERNEL);
	अगर (!smmu->asids)
		वापस ERR_PTR(-ENOMEM);

	INIT_LIST_HEAD(&smmu->groups);
	mutex_init(&smmu->lock);

	smmu->regs = mc->regs;
	smmu->soc = soc;
	smmu->dev = dev;
	smmu->mc = mc;

	smmu->pfn_mask =
		BIT_MASK(mc->soc->num_address_bits - SMMU_PTE_SHIFT) - 1;
	dev_dbg(dev, "address bits: %u, PFN mask: %#lx\n",
		mc->soc->num_address_bits, smmu->pfn_mask);
	smmu->tlb_mask = (1 << fls(smmu->soc->num_tlb_lines)) - 1;
	dev_dbg(dev, "TLB lines: %u, mask: %#lx\n", smmu->soc->num_tlb_lines,
		smmu->tlb_mask);

	value = SMMU_PTC_CONFIG_ENABLE | SMMU_PTC_CONFIG_INDEX_MAP(0x3f);

	अगर (soc->supports_request_limit)
		value |= SMMU_PTC_CONFIG_REQ_LIMIT(8);

	smmu_ग_लिखोl(smmu, value, SMMU_PTC_CONFIG);

	value = SMMU_TLB_CONFIG_HIT_UNDER_MISS |
		SMMU_TLB_CONFIG_ACTIVE_LINES(smmu);

	अगर (soc->supports_round_robin_arbitration)
		value |= SMMU_TLB_CONFIG_ROUND_ROBIN_ARBITRATION;

	smmu_ग_लिखोl(smmu, value, SMMU_TLB_CONFIG);

	smmu_flush_ptc_all(smmu);
	smmu_flush_tlb(smmu);
	smmu_ग_लिखोl(smmu, SMMU_CONFIG_ENABLE, SMMU_CONFIG);
	smmu_flush(smmu);

	tegra_smmu_ahb_enable();

	err = iommu_device_sysfs_add(&smmu->iommu, dev, शून्य, dev_name(dev));
	अगर (err)
		वापस ERR_PTR(err);

	err = iommu_device_रेजिस्टर(&smmu->iommu, &tegra_smmu_ops, dev);
	अगर (err)
		जाओ हटाओ_sysfs;

	err = bus_set_iommu(&platक्रमm_bus_type, &tegra_smmu_ops);
	अगर (err < 0)
		जाओ unरेजिस्टर;

#अगर_घोषित CONFIG_PCI
	err = bus_set_iommu(&pci_bus_type, &tegra_smmu_ops);
	अगर (err < 0)
		जाओ unset_platक्रमm_bus;
#पूर्ण_अगर

	अगर (IS_ENABLED(CONFIG_DEBUG_FS))
		tegra_smmu_debugfs_init(smmu);

	वापस smmu;

unset_platक्रमm_bus: __maybe_unused;
	bus_set_iommu(&platक्रमm_bus_type, शून्य);
unरेजिस्टर:
	iommu_device_unरेजिस्टर(&smmu->iommu);
हटाओ_sysfs:
	iommu_device_sysfs_हटाओ(&smmu->iommu);

	वापस ERR_PTR(err);
पूर्ण

व्योम tegra_smmu_हटाओ(काष्ठा tegra_smmu *smmu)
अणु
	iommu_device_unरेजिस्टर(&smmu->iommu);
	iommu_device_sysfs_हटाओ(&smmu->iommu);

	अगर (IS_ENABLED(CONFIG_DEBUG_FS))
		tegra_smmu_debugfs_निकास(smmu);
पूर्ण
