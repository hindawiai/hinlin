<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/**
 * पूर्णांकel-pasid.c - PASID idr, table and entry manipulation
 *
 * Copyright (C) 2018 Intel Corporation
 *
 * Author: Lu Baolu <baolu.lu@linux.पूर्णांकel.com>
 */

#घोषणा pr_fmt(fmt)	"DMAR: " fmt

#समावेश <linux/bitops.h>
#समावेश <linux/cpufeature.h>
#समावेश <linux/dmar.h>
#समावेश <linux/पूर्णांकel-iommu.h>
#समावेश <linux/iommu.h>
#समावेश <linux/memory.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci-ats.h>
#समावेश <linux/spinlock.h>

#समावेश "pasid.h"

/*
 * Intel IOMMU प्रणाली wide PASID name space:
 */
u32 पूर्णांकel_pasid_max_id = PASID_MAX;

पूर्णांक vcmd_alloc_pasid(काष्ठा पूर्णांकel_iommu *iommu, u32 *pasid)
अणु
	अचिन्हित दीर्घ flags;
	u8 status_code;
	पूर्णांक ret = 0;
	u64 res;

	raw_spin_lock_irqsave(&iommu->रेजिस्टर_lock, flags);
	dmar_ग_लिखोq(iommu->reg + DMAR_VCMD_REG, VCMD_CMD_ALLOC);
	IOMMU_WAIT_OP(iommu, DMAR_VCRSP_REG, dmar_पढ़ोq,
		      !(res & VCMD_VRSP_IP), res);
	raw_spin_unlock_irqrestore(&iommu->रेजिस्टर_lock, flags);

	status_code = VCMD_VRSP_SC(res);
	चयन (status_code) अणु
	हाल VCMD_VRSP_SC_SUCCESS:
		*pasid = VCMD_VRSP_RESULT_PASID(res);
		अवरोध;
	हाल VCMD_VRSP_SC_NO_PASID_AVAIL:
		pr_info("IOMMU: %s: No PASID available\n", iommu->name);
		ret = -ENOSPC;
		अवरोध;
	शेष:
		ret = -ENODEV;
		pr_warn("IOMMU: %s: Unexpected error code %d\n",
			iommu->name, status_code);
	पूर्ण

	वापस ret;
पूर्ण

व्योम vcmd_मुक्त_pasid(काष्ठा पूर्णांकel_iommu *iommu, u32 pasid)
अणु
	अचिन्हित दीर्घ flags;
	u8 status_code;
	u64 res;

	raw_spin_lock_irqsave(&iommu->रेजिस्टर_lock, flags);
	dmar_ग_लिखोq(iommu->reg + DMAR_VCMD_REG,
		    VCMD_CMD_OPERAND(pasid) | VCMD_CMD_FREE);
	IOMMU_WAIT_OP(iommu, DMAR_VCRSP_REG, dmar_पढ़ोq,
		      !(res & VCMD_VRSP_IP), res);
	raw_spin_unlock_irqrestore(&iommu->रेजिस्टर_lock, flags);

	status_code = VCMD_VRSP_SC(res);
	चयन (status_code) अणु
	हाल VCMD_VRSP_SC_SUCCESS:
		अवरोध;
	हाल VCMD_VRSP_SC_INVALID_PASID:
		pr_info("IOMMU: %s: Invalid PASID\n", iommu->name);
		अवरोध;
	शेष:
		pr_warn("IOMMU: %s: Unexpected error code %d\n",
			iommu->name, status_code);
	पूर्ण
पूर्ण

/*
 * Per device pasid table management:
 */
अटल अंतरभूत व्योम
device_attach_pasid_table(काष्ठा device_करोमुख्य_info *info,
			  काष्ठा pasid_table *pasid_table)
अणु
	info->pasid_table = pasid_table;
	list_add(&info->table, &pasid_table->dev);
पूर्ण

अटल अंतरभूत व्योम
device_detach_pasid_table(काष्ठा device_करोमुख्य_info *info,
			  काष्ठा pasid_table *pasid_table)
अणु
	info->pasid_table = शून्य;
	list_del(&info->table);
पूर्ण

काष्ठा pasid_table_opaque अणु
	काष्ठा pasid_table	**pasid_table;
	पूर्णांक			segment;
	पूर्णांक			bus;
	पूर्णांक			devfn;
पूर्ण;

अटल पूर्णांक search_pasid_table(काष्ठा device_करोमुख्य_info *info, व्योम *opaque)
अणु
	काष्ठा pasid_table_opaque *data = opaque;

	अगर (info->iommu->segment == data->segment &&
	    info->bus == data->bus &&
	    info->devfn == data->devfn &&
	    info->pasid_table) अणु
		*data->pasid_table = info->pasid_table;
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक get_alias_pasid_table(काष्ठा pci_dev *pdev, u16 alias, व्योम *opaque)
अणु
	काष्ठा pasid_table_opaque *data = opaque;

	data->segment = pci_करोमुख्य_nr(pdev->bus);
	data->bus = PCI_BUS_NUM(alias);
	data->devfn = alias & 0xff;

	वापस क्रम_each_device_करोमुख्य(&search_pasid_table, data);
पूर्ण

/*
 * Allocate a pasid table क्रम @dev. It should be called in a
 * single-thपढ़ो context.
 */
पूर्णांक पूर्णांकel_pasid_alloc_table(काष्ठा device *dev)
अणु
	काष्ठा device_करोमुख्य_info *info;
	काष्ठा pasid_table *pasid_table;
	काष्ठा pasid_table_opaque data;
	काष्ठा page *pages;
	u32 max_pasid = 0;
	पूर्णांक ret, order;
	पूर्णांक size;

	might_sleep();
	info = get_करोमुख्य_info(dev);
	अगर (WARN_ON(!info || !dev_is_pci(dev) || info->pasid_table))
		वापस -EINVAL;

	/* DMA alias device alपढ़ोy has a pasid table, use it: */
	data.pasid_table = &pasid_table;
	ret = pci_क्रम_each_dma_alias(to_pci_dev(dev),
				     &get_alias_pasid_table, &data);
	अगर (ret)
		जाओ attach_out;

	pasid_table = kzalloc(माप(*pasid_table), GFP_KERNEL);
	अगर (!pasid_table)
		वापस -ENOMEM;
	INIT_LIST_HEAD(&pasid_table->dev);

	अगर (info->pasid_supported)
		max_pasid = min_t(u32, pci_max_pasids(to_pci_dev(dev)),
				  पूर्णांकel_pasid_max_id);

	size = max_pasid >> (PASID_PDE_SHIFT - 3);
	order = size ? get_order(size) : 0;
	pages = alloc_pages_node(info->iommu->node,
				 GFP_KERNEL | __GFP_ZERO, order);
	अगर (!pages) अणु
		kमुक्त(pasid_table);
		वापस -ENOMEM;
	पूर्ण

	pasid_table->table = page_address(pages);
	pasid_table->order = order;
	pasid_table->max_pasid = 1 << (order + PAGE_SHIFT + 3);

attach_out:
	device_attach_pasid_table(info, pasid_table);

	वापस 0;
पूर्ण

व्योम पूर्णांकel_pasid_मुक्त_table(काष्ठा device *dev)
अणु
	काष्ठा device_करोमुख्य_info *info;
	काष्ठा pasid_table *pasid_table;
	काष्ठा pasid_dir_entry *dir;
	काष्ठा pasid_entry *table;
	पूर्णांक i, max_pde;

	info = get_करोमुख्य_info(dev);
	अगर (!info || !dev_is_pci(dev) || !info->pasid_table)
		वापस;

	pasid_table = info->pasid_table;
	device_detach_pasid_table(info, pasid_table);

	अगर (!list_empty(&pasid_table->dev))
		वापस;

	/* Free scalable mode PASID directory tables: */
	dir = pasid_table->table;
	max_pde = pasid_table->max_pasid >> PASID_PDE_SHIFT;
	क्रम (i = 0; i < max_pde; i++) अणु
		table = get_pasid_table_from_pde(&dir[i]);
		मुक्त_pgtable_page(table);
	पूर्ण

	मुक्त_pages((अचिन्हित दीर्घ)pasid_table->table, pasid_table->order);
	kमुक्त(pasid_table);
पूर्ण

काष्ठा pasid_table *पूर्णांकel_pasid_get_table(काष्ठा device *dev)
अणु
	काष्ठा device_करोमुख्य_info *info;

	info = get_करोमुख्य_info(dev);
	अगर (!info)
		वापस शून्य;

	वापस info->pasid_table;
पूर्ण

अटल पूर्णांक पूर्णांकel_pasid_get_dev_max_id(काष्ठा device *dev)
अणु
	काष्ठा device_करोमुख्य_info *info;

	info = get_करोमुख्य_info(dev);
	अगर (!info || !info->pasid_table)
		वापस 0;

	वापस info->pasid_table->max_pasid;
पूर्ण

अटल काष्ठा pasid_entry *पूर्णांकel_pasid_get_entry(काष्ठा device *dev, u32 pasid)
अणु
	काष्ठा device_करोमुख्य_info *info;
	काष्ठा pasid_table *pasid_table;
	काष्ठा pasid_dir_entry *dir;
	काष्ठा pasid_entry *entries;
	पूर्णांक dir_index, index;

	pasid_table = पूर्णांकel_pasid_get_table(dev);
	अगर (WARN_ON(!pasid_table || pasid >= पूर्णांकel_pasid_get_dev_max_id(dev)))
		वापस शून्य;

	dir = pasid_table->table;
	info = get_करोमुख्य_info(dev);
	dir_index = pasid >> PASID_PDE_SHIFT;
	index = pasid & PASID_PTE_MASK;

retry:
	entries = get_pasid_table_from_pde(&dir[dir_index]);
	अगर (!entries) अणु
		entries = alloc_pgtable_page(info->iommu->node);
		अगर (!entries)
			वापस शून्य;

		/*
		 * The pasid directory table entry won't be मुक्तd after
		 * allocation. No worry about the race with मुक्त and
		 * clear. However, this entry might be populated by others
		 * जबतक we are preparing it. Use theirs with a retry.
		 */
		अगर (cmpxchg64(&dir[dir_index].val, 0ULL,
			      (u64)virt_to_phys(entries) | PASID_PTE_PRESENT)) अणु
			मुक्त_pgtable_page(entries);
			जाओ retry;
		पूर्ण
	पूर्ण

	वापस &entries[index];
पूर्ण

/*
 * Interfaces क्रम PASID table entry manipulation:
 */
अटल अंतरभूत व्योम pasid_clear_entry(काष्ठा pasid_entry *pe)
अणु
	WRITE_ONCE(pe->val[0], 0);
	WRITE_ONCE(pe->val[1], 0);
	WRITE_ONCE(pe->val[2], 0);
	WRITE_ONCE(pe->val[3], 0);
	WRITE_ONCE(pe->val[4], 0);
	WRITE_ONCE(pe->val[5], 0);
	WRITE_ONCE(pe->val[6], 0);
	WRITE_ONCE(pe->val[7], 0);
पूर्ण

अटल अंतरभूत व्योम pasid_clear_entry_with_fpd(काष्ठा pasid_entry *pe)
अणु
	WRITE_ONCE(pe->val[0], PASID_PTE_FPD);
	WRITE_ONCE(pe->val[1], 0);
	WRITE_ONCE(pe->val[2], 0);
	WRITE_ONCE(pe->val[3], 0);
	WRITE_ONCE(pe->val[4], 0);
	WRITE_ONCE(pe->val[5], 0);
	WRITE_ONCE(pe->val[6], 0);
	WRITE_ONCE(pe->val[7], 0);
पूर्ण

अटल व्योम
पूर्णांकel_pasid_clear_entry(काष्ठा device *dev, u32 pasid, bool fault_ignore)
अणु
	काष्ठा pasid_entry *pe;

	pe = पूर्णांकel_pasid_get_entry(dev, pasid);
	अगर (WARN_ON(!pe))
		वापस;

	अगर (fault_ignore && pasid_pte_is_present(pe))
		pasid_clear_entry_with_fpd(pe);
	अन्यथा
		pasid_clear_entry(pe);
पूर्ण

अटल अंतरभूत व्योम pasid_set_bits(u64 *ptr, u64 mask, u64 bits)
अणु
	u64 old;

	old = READ_ONCE(*ptr);
	WRITE_ONCE(*ptr, (old & ~mask) | bits);
पूर्ण

/*
 * Setup the DID(Doमुख्य Identअगरier) field (Bit 64~79) of scalable mode
 * PASID entry.
 */
अटल अंतरभूत व्योम
pasid_set_करोमुख्य_id(काष्ठा pasid_entry *pe, u64 value)
अणु
	pasid_set_bits(&pe->val[1], GENMASK_ULL(15, 0), value);
पूर्ण

/*
 * Get करोमुख्य ID value of a scalable mode PASID entry.
 */
अटल अंतरभूत u16
pasid_get_करोमुख्य_id(काष्ठा pasid_entry *pe)
अणु
	वापस (u16)(READ_ONCE(pe->val[1]) & GENMASK_ULL(15, 0));
पूर्ण

/*
 * Setup the SLPTPTR(Second Level Page Table Poपूर्णांकer) field (Bit 12~63)
 * of a scalable mode PASID entry.
 */
अटल अंतरभूत व्योम
pasid_set_slptr(काष्ठा pasid_entry *pe, u64 value)
अणु
	pasid_set_bits(&pe->val[0], VTD_PAGE_MASK, value);
पूर्ण

/*
 * Setup the AW(Address Width) field (Bit 2~4) of a scalable mode PASID
 * entry.
 */
अटल अंतरभूत व्योम
pasid_set_address_width(काष्ठा pasid_entry *pe, u64 value)
अणु
	pasid_set_bits(&pe->val[0], GENMASK_ULL(4, 2), value << 2);
पूर्ण

/*
 * Setup the PGTT(PASID Granular Translation Type) field (Bit 6~8)
 * of a scalable mode PASID entry.
 */
अटल अंतरभूत व्योम
pasid_set_translation_type(काष्ठा pasid_entry *pe, u64 value)
अणु
	pasid_set_bits(&pe->val[0], GENMASK_ULL(8, 6), value << 6);
पूर्ण

/*
 * Enable fault processing by clearing the FPD(Fault Processing
 * Disable) field (Bit 1) of a scalable mode PASID entry.
 */
अटल अंतरभूत व्योम pasid_set_fault_enable(काष्ठा pasid_entry *pe)
अणु
	pasid_set_bits(&pe->val[0], 1 << 1, 0);
पूर्ण

/*
 * Setup the SRE(Supervisor Request Enable) field (Bit 128) of a
 * scalable mode PASID entry.
 */
अटल अंतरभूत व्योम pasid_set_sre(काष्ठा pasid_entry *pe)
अणु
	pasid_set_bits(&pe->val[2], 1 << 0, 1);
पूर्ण

/*
 * Setup the WPE(Write Protect Enable) field (Bit 132) of a
 * scalable mode PASID entry.
 */
अटल अंतरभूत व्योम pasid_set_wpe(काष्ठा pasid_entry *pe)
अणु
	pasid_set_bits(&pe->val[2], 1 << 4, 1 << 4);
पूर्ण

/*
 * Setup the P(Present) field (Bit 0) of a scalable mode PASID
 * entry.
 */
अटल अंतरभूत व्योम pasid_set_present(काष्ठा pasid_entry *pe)
अणु
	pasid_set_bits(&pe->val[0], 1 << 0, 1);
पूर्ण

/*
 * Setup Page Walk Snoop bit (Bit 87) of a scalable mode PASID
 * entry.
 */
अटल अंतरभूत व्योम pasid_set_page_snoop(काष्ठा pasid_entry *pe, bool value)
अणु
	pasid_set_bits(&pe->val[1], 1 << 23, value << 23);
पूर्ण

/*
 * Setup the Page Snoop (PGSNP) field (Bit 88) of a scalable mode
 * PASID entry.
 */
अटल अंतरभूत व्योम
pasid_set_pgsnp(काष्ठा pasid_entry *pe)
अणु
	pasid_set_bits(&pe->val[1], 1ULL << 24, 1ULL << 24);
पूर्ण

/*
 * Setup the First Level Page table Poपूर्णांकer field (Bit 140~191)
 * of a scalable mode PASID entry.
 */
अटल अंतरभूत व्योम
pasid_set_flptr(काष्ठा pasid_entry *pe, u64 value)
अणु
	pasid_set_bits(&pe->val[2], VTD_PAGE_MASK, value);
पूर्ण

/*
 * Setup the First Level Paging Mode field (Bit 130~131) of a
 * scalable mode PASID entry.
 */
अटल अंतरभूत व्योम
pasid_set_flpm(काष्ठा pasid_entry *pe, u64 value)
अणु
	pasid_set_bits(&pe->val[2], GENMASK_ULL(3, 2), value << 2);
पूर्ण

/*
 * Setup the Extended Access Flag Enable (EAFE) field (Bit 135)
 * of a scalable mode PASID entry.
 */
अटल अंतरभूत व्योम
pasid_set_eafe(काष्ठा pasid_entry *pe)
अणु
	pasid_set_bits(&pe->val[2], 1 << 7, 1 << 7);
पूर्ण

अटल व्योम
pasid_cache_invalidation_with_pasid(काष्ठा पूर्णांकel_iommu *iommu,
				    u16 did, u32 pasid)
अणु
	काष्ठा qi_desc desc;

	desc.qw0 = QI_PC_DID(did) | QI_PC_GRAN(QI_PC_PASID_SEL) |
		QI_PC_PASID(pasid) | QI_PC_TYPE;
	desc.qw1 = 0;
	desc.qw2 = 0;
	desc.qw3 = 0;

	qi_submit_sync(iommu, &desc, 1, 0);
पूर्ण

अटल व्योम
devtlb_invalidation_with_pasid(काष्ठा पूर्णांकel_iommu *iommu,
			       काष्ठा device *dev, u32 pasid)
अणु
	काष्ठा device_करोमुख्य_info *info;
	u16 sid, qdep, pfsid;

	info = get_करोमुख्य_info(dev);
	अगर (!info || !info->ats_enabled)
		वापस;

	sid = info->bus << 8 | info->devfn;
	qdep = info->ats_qdep;
	pfsid = info->pfsid;

	/*
	 * When PASID 0 is used, it indicates RID2PASID(DMA request w/o PASID),
	 * devTLB flush w/o PASID should be used. For non-zero PASID under
	 * SVA usage, device could करो DMA with multiple PASIDs. It is more
	 * efficient to flush devTLB specअगरic to the PASID.
	 */
	अगर (pasid == PASID_RID2PASID)
		qi_flush_dev_iotlb(iommu, sid, pfsid, qdep, 0, 64 - VTD_PAGE_SHIFT);
	अन्यथा
		qi_flush_dev_iotlb_pasid(iommu, sid, pfsid, pasid, qdep, 0, 64 - VTD_PAGE_SHIFT);
पूर्ण

व्योम पूर्णांकel_pasid_tear_करोwn_entry(काष्ठा पूर्णांकel_iommu *iommu, काष्ठा device *dev,
				 u32 pasid, bool fault_ignore)
अणु
	काष्ठा pasid_entry *pte;
	u16 did;

	pte = पूर्णांकel_pasid_get_entry(dev, pasid);
	अगर (WARN_ON(!pte))
		वापस;

	अगर (!(pte->val[0] & PASID_PTE_PRESENT))
		वापस;

	did = pasid_get_करोमुख्य_id(pte);
	पूर्णांकel_pasid_clear_entry(dev, pasid, fault_ignore);

	अगर (!ecap_coherent(iommu->ecap))
		clflush_cache_range(pte, माप(*pte));

	pasid_cache_invalidation_with_pasid(iommu, did, pasid);
	qi_flush_piotlb(iommu, did, pasid, 0, -1, 0);

	/* Device IOTLB करोesn't need to be flushed in caching mode. */
	अगर (!cap_caching_mode(iommu->cap))
		devtlb_invalidation_with_pasid(iommu, dev, pasid);
पूर्ण

अटल व्योम pasid_flush_caches(काष्ठा पूर्णांकel_iommu *iommu,
				काष्ठा pasid_entry *pte,
			       u32 pasid, u16 did)
अणु
	अगर (!ecap_coherent(iommu->ecap))
		clflush_cache_range(pte, माप(*pte));

	अगर (cap_caching_mode(iommu->cap)) अणु
		pasid_cache_invalidation_with_pasid(iommu, did, pasid);
		qi_flush_piotlb(iommu, did, pasid, 0, -1, 0);
	पूर्ण अन्यथा अणु
		iommu_flush_ग_लिखो_buffer(iommu);
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक pasid_enable_wpe(काष्ठा pasid_entry *pte)
अणु
#अगर_घोषित CONFIG_X86
	अचिन्हित दीर्घ cr0 = पढ़ो_cr0();

	/* CR0.WP is normally set but just to be sure */
	अगर (unlikely(!(cr0 & X86_CR0_WP))) अणु
		pr_err_ratelimited("No CPU write protect!\n");
		वापस -EINVAL;
	पूर्ण
#पूर्ण_अगर
	pasid_set_wpe(pte);

	वापस 0;
पूर्ण;

/*
 * Set up the scalable mode pasid table entry क्रम first only
 * translation type.
 */
पूर्णांक पूर्णांकel_pasid_setup_first_level(काष्ठा पूर्णांकel_iommu *iommu,
				  काष्ठा device *dev, pgd_t *pgd,
				  u32 pasid, u16 did, पूर्णांक flags)
अणु
	काष्ठा pasid_entry *pte;

	अगर (!ecap_flts(iommu->ecap)) अणु
		pr_err("No first level translation support on %s\n",
		       iommu->name);
		वापस -EINVAL;
	पूर्ण

	pte = पूर्णांकel_pasid_get_entry(dev, pasid);
	अगर (WARN_ON(!pte))
		वापस -EINVAL;

	pasid_clear_entry(pte);

	/* Setup the first level page table poपूर्णांकer: */
	pasid_set_flptr(pte, (u64)__pa(pgd));
	अगर (flags & PASID_FLAG_SUPERVISOR_MODE) अणु
		अगर (!ecap_srs(iommu->ecap)) अणु
			pr_err("No supervisor request support on %s\n",
			       iommu->name);
			वापस -EINVAL;
		पूर्ण
		pasid_set_sre(pte);
		अगर (pasid_enable_wpe(pte))
			वापस -EINVAL;

	पूर्ण

	अगर (flags & PASID_FLAG_FL5LP) अणु
		अगर (cap_5lp_support(iommu->cap)) अणु
			pasid_set_flpm(pte, 1);
		पूर्ण अन्यथा अणु
			pr_err("No 5-level paging support for first-level\n");
			pasid_clear_entry(pte);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (flags & PASID_FLAG_PAGE_SNOOP)
		pasid_set_pgsnp(pte);

	pasid_set_करोमुख्य_id(pte, did);
	pasid_set_address_width(pte, iommu->agaw);
	pasid_set_page_snoop(pte, !!ecap_smpwc(iommu->ecap));

	/* Setup Present and PASID Granular Transfer Type: */
	pasid_set_translation_type(pte, PASID_ENTRY_PGTT_FL_ONLY);
	pasid_set_present(pte);
	pasid_flush_caches(iommu, pte, pasid, did);

	वापस 0;
पूर्ण

/*
 * Skip top levels of page tables क्रम iommu which has less agaw
 * than शेष. Unnecessary क्रम PT mode.
 */
अटल अंतरभूत पूर्णांक iommu_skip_agaw(काष्ठा dmar_करोमुख्य *करोमुख्य,
				  काष्ठा पूर्णांकel_iommu *iommu,
				  काष्ठा dma_pte **pgd)
अणु
	पूर्णांक agaw;

	क्रम (agaw = करोमुख्य->agaw; agaw > iommu->agaw; agaw--) अणु
		*pgd = phys_to_virt(dma_pte_addr(*pgd));
		अगर (!dma_pte_present(*pgd))
			वापस -EINVAL;
	पूर्ण

	वापस agaw;
पूर्ण

/*
 * Set up the scalable mode pasid entry क्रम second only translation type.
 */
पूर्णांक पूर्णांकel_pasid_setup_second_level(काष्ठा पूर्णांकel_iommu *iommu,
				   काष्ठा dmar_करोमुख्य *करोमुख्य,
				   काष्ठा device *dev, u32 pasid)
अणु
	काष्ठा pasid_entry *pte;
	काष्ठा dma_pte *pgd;
	u64 pgd_val;
	पूर्णांक agaw;
	u16 did;

	/*
	 * If hardware advertises no support क्रम second level
	 * translation, वापस directly.
	 */
	अगर (!ecap_slts(iommu->ecap)) अणु
		pr_err("No second level translation support on %s\n",
		       iommu->name);
		वापस -EINVAL;
	पूर्ण

	pgd = करोमुख्य->pgd;
	agaw = iommu_skip_agaw(करोमुख्य, iommu, &pgd);
	अगर (agaw < 0) अणु
		dev_err(dev, "Invalid domain page table\n");
		वापस -EINVAL;
	पूर्ण

	pgd_val = virt_to_phys(pgd);
	did = करोमुख्य->iommu_did[iommu->seq_id];

	pte = पूर्णांकel_pasid_get_entry(dev, pasid);
	अगर (!pte) अणु
		dev_err(dev, "Failed to get pasid entry of PASID %d\n", pasid);
		वापस -ENODEV;
	पूर्ण

	pasid_clear_entry(pte);
	pasid_set_करोमुख्य_id(pte, did);
	pasid_set_slptr(pte, pgd_val);
	pasid_set_address_width(pte, agaw);
	pasid_set_translation_type(pte, PASID_ENTRY_PGTT_SL_ONLY);
	pasid_set_fault_enable(pte);
	pasid_set_page_snoop(pte, !!ecap_smpwc(iommu->ecap));

	अगर (करोमुख्य->करोमुख्य.type == IOMMU_DOMAIN_UNMANAGED)
		pasid_set_pgsnp(pte);

	/*
	 * Since it is a second level only translation setup, we should
	 * set SRE bit as well (addresses are expected to be GPAs).
	 */
	अगर (pasid != PASID_RID2PASID)
		pasid_set_sre(pte);
	pasid_set_present(pte);
	pasid_flush_caches(iommu, pte, pasid, did);

	वापस 0;
पूर्ण

/*
 * Set up the scalable mode pasid entry क्रम passthrough translation type.
 */
पूर्णांक पूर्णांकel_pasid_setup_pass_through(काष्ठा पूर्णांकel_iommu *iommu,
				   काष्ठा dmar_करोमुख्य *करोमुख्य,
				   काष्ठा device *dev, u32 pasid)
अणु
	u16 did = FLPT_DEFAULT_DID;
	काष्ठा pasid_entry *pte;

	pte = पूर्णांकel_pasid_get_entry(dev, pasid);
	अगर (!pte) अणु
		dev_err(dev, "Failed to get pasid entry of PASID %d\n", pasid);
		वापस -ENODEV;
	पूर्ण

	pasid_clear_entry(pte);
	pasid_set_करोमुख्य_id(pte, did);
	pasid_set_address_width(pte, iommu->agaw);
	pasid_set_translation_type(pte, PASID_ENTRY_PGTT_PT);
	pasid_set_fault_enable(pte);
	pasid_set_page_snoop(pte, !!ecap_smpwc(iommu->ecap));

	/*
	 * We should set SRE bit as well since the addresses are expected
	 * to be GPAs.
	 */
	pasid_set_sre(pte);
	pasid_set_present(pte);
	pasid_flush_caches(iommu, pte, pasid, did);

	वापस 0;
पूर्ण

अटल पूर्णांक
पूर्णांकel_pasid_setup_bind_data(काष्ठा पूर्णांकel_iommu *iommu, काष्ठा pasid_entry *pte,
			    काष्ठा iommu_gpasid_bind_data_vtd *pasid_data)
अणु
	/*
	 * Not all guest PASID table entry fields are passed करोwn during bind,
	 * here we only set up the ones that are dependent on guest settings.
	 * Execution related bits such as NXE, SMEP are not supported.
	 * Other fields, such as snoop related, are set based on host needs
	 * regardless of guest settings.
	 */
	अगर (pasid_data->flags & IOMMU_SVA_VTD_GPASID_SRE) अणु
		अगर (!ecap_srs(iommu->ecap)) अणु
			pr_err_ratelimited("No supervisor request support on %s\n",
					   iommu->name);
			वापस -EINVAL;
		पूर्ण
		pasid_set_sre(pte);
		/* Enable ग_लिखो protect WP अगर guest requested */
		अगर (pasid_data->flags & IOMMU_SVA_VTD_GPASID_WPE)
			pasid_set_wpe(pte);
	पूर्ण

	अगर (pasid_data->flags & IOMMU_SVA_VTD_GPASID_EAFE) अणु
		अगर (!ecap_eafs(iommu->ecap)) अणु
			pr_err_ratelimited("No extended access flag support on %s\n",
					   iommu->name);
			वापस -EINVAL;
		पूर्ण
		pasid_set_eafe(pte);
	पूर्ण

	/*
	 * Memory type is only applicable to devices inside processor coherent
	 * करोमुख्य. Will add MTS support once coherent devices are available.
	 */
	अगर (pasid_data->flags & IOMMU_SVA_VTD_GPASID_MTS_MASK) अणु
		pr_warn_ratelimited("No memory type support %s\n",
				    iommu->name);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * पूर्णांकel_pasid_setup_nested() - Set up PASID entry क्रम nested translation.
 * This could be used क्रम guest shared भव address. In this हाल, the
 * first level page tables are used क्रम GVA-GPA translation in the guest,
 * second level page tables are used क्रम GPA-HPA translation.
 *
 * @iommu:      IOMMU which the device beदीर्घ to
 * @dev:        Device to be set up क्रम translation
 * @gpgd:       FLPTPTR: First Level Page translation poपूर्णांकer in GPA
 * @pasid:      PASID to be programmed in the device PASID table
 * @pasid_data: Additional PASID info from the guest bind request
 * @करोमुख्य:     Doमुख्य info क्रम setting up second level page tables
 * @addr_width: Address width of the first level (guest)
 */
पूर्णांक पूर्णांकel_pasid_setup_nested(काष्ठा पूर्णांकel_iommu *iommu, काष्ठा device *dev,
			     pgd_t *gpgd, u32 pasid,
			     काष्ठा iommu_gpasid_bind_data_vtd *pasid_data,
			     काष्ठा dmar_करोमुख्य *करोमुख्य, पूर्णांक addr_width)
अणु
	काष्ठा pasid_entry *pte;
	काष्ठा dma_pte *pgd;
	पूर्णांक ret = 0;
	u64 pgd_val;
	पूर्णांक agaw;
	u16 did;

	अगर (!ecap_nest(iommu->ecap)) अणु
		pr_err_ratelimited("IOMMU: %s: No nested translation support\n",
				   iommu->name);
		वापस -EINVAL;
	पूर्ण

	अगर (!(करोमुख्य->flags & DOMAIN_FLAG_NESTING_MODE)) अणु
		pr_err_ratelimited("Domain is not in nesting mode, %x\n",
				   करोमुख्य->flags);
		वापस -EINVAL;
	पूर्ण

	pte = पूर्णांकel_pasid_get_entry(dev, pasid);
	अगर (WARN_ON(!pte))
		वापस -EINVAL;

	/*
	 * Caller must ensure PASID entry is not in use, i.e. not bind the
	 * same PASID to the same device twice.
	 */
	अगर (pasid_pte_is_present(pte))
		वापस -EBUSY;

	pasid_clear_entry(pte);

	/* Sanity checking perक्रमmed by caller to make sure address
	 * width matching in two dimensions:
	 * 1. CPU vs. IOMMU
	 * 2. Guest vs. Host.
	 */
	चयन (addr_width) अणु
#अगर_घोषित CONFIG_X86
	हाल ADDR_WIDTH_5LEVEL:
		अगर (!cpu_feature_enabled(X86_FEATURE_LA57) ||
		    !cap_5lp_support(iommu->cap)) अणु
			dev_err_ratelimited(dev,
					    "5-level paging not supported\n");
			वापस -EINVAL;
		पूर्ण

		pasid_set_flpm(pte, 1);
		अवरोध;
#पूर्ण_अगर
	हाल ADDR_WIDTH_4LEVEL:
		pasid_set_flpm(pte, 0);
		अवरोध;
	शेष:
		dev_err_ratelimited(dev, "Invalid guest address width %d\n",
				    addr_width);
		वापस -EINVAL;
	पूर्ण

	/* First level PGD is in GPA, must be supported by the second level */
	अगर ((uपूर्णांकptr_t)gpgd > करोमुख्य->max_addr) अणु
		dev_err_ratelimited(dev,
				    "Guest PGD %lx not supported, max %llx\n",
				    (uपूर्णांकptr_t)gpgd, करोमुख्य->max_addr);
		वापस -EINVAL;
	पूर्ण
	pasid_set_flptr(pte, (uपूर्णांकptr_t)gpgd);

	ret = पूर्णांकel_pasid_setup_bind_data(iommu, pte, pasid_data);
	अगर (ret)
		वापस ret;

	/* Setup the second level based on the given करोमुख्य */
	pgd = करोमुख्य->pgd;

	agaw = iommu_skip_agaw(करोमुख्य, iommu, &pgd);
	अगर (agaw < 0) अणु
		dev_err_ratelimited(dev, "Invalid domain page table\n");
		वापस -EINVAL;
	पूर्ण
	pgd_val = virt_to_phys(pgd);
	pasid_set_slptr(pte, pgd_val);
	pasid_set_fault_enable(pte);

	did = करोमुख्य->iommu_did[iommu->seq_id];
	pasid_set_करोमुख्य_id(pte, did);

	pasid_set_address_width(pte, agaw);
	pasid_set_page_snoop(pte, !!ecap_smpwc(iommu->ecap));

	pasid_set_translation_type(pte, PASID_ENTRY_PGTT_NESTED);
	pasid_set_present(pte);
	pasid_flush_caches(iommu, pte, pasid, did);

	वापस ret;
पूर्ण
