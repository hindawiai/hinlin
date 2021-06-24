<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * Copyright 2016-2020 HabanaLअसल, Ltd.
 * All Rights Reserved.
 */

#समावेश <linux/slab.h>

#समावेश "../habanalabs.h"

bool hl_is_dram_va(काष्ठा hl_device *hdev, u64 virt_addr)
अणु
	काष्ठा asic_fixed_properties *prop = &hdev->asic_prop;

	वापस hl_mem_area_inside_range(virt_addr, prop->dmmu.page_size,
					prop->dmmu.start_addr,
					prop->dmmu.end_addr);
पूर्ण

/**
 * hl_mmu_init() - initialize the MMU module.
 * @hdev: habanaद_असल device काष्ठाure.
 *
 * Return: 0 क्रम success, non-zero क्रम failure.
 */
पूर्णांक hl_mmu_init(काष्ठा hl_device *hdev)
अणु
	पूर्णांक rc = -EOPNOTSUPP;

	अगर (!hdev->mmu_enable)
		वापस 0;

	अगर (hdev->mmu_func[MMU_DR_PGT].init != शून्य) अणु
		rc = hdev->mmu_func[MMU_DR_PGT].init(hdev);
		अगर (rc)
			वापस rc;
	पूर्ण

	अगर (hdev->mmu_func[MMU_HR_PGT].init != शून्य)
		rc = hdev->mmu_func[MMU_HR_PGT].init(hdev);

	वापस rc;
पूर्ण

/**
 * hl_mmu_fini() - release the MMU module.
 * @hdev: habanaद_असल device काष्ठाure.
 *
 * This function करोes the following:
 * - Disable MMU in H/W.
 * - Free the pgt_infos pool.
 *
 * All contexts should be मुक्तd beक्रमe calling this function.
 */
व्योम hl_mmu_fini(काष्ठा hl_device *hdev)
अणु
	अगर (!hdev->mmu_enable)
		वापस;

	अगर (hdev->mmu_func[MMU_DR_PGT].fini != शून्य)
		hdev->mmu_func[MMU_DR_PGT].fini(hdev);

	अगर (hdev->mmu_func[MMU_HR_PGT].fini != शून्य)
		hdev->mmu_func[MMU_HR_PGT].fini(hdev);
पूर्ण

/**
 * hl_mmu_ctx_init() - initialize a context क्रम using the MMU module.
 * @ctx: poपूर्णांकer to the context काष्ठाure to initialize.
 *
 * Initialize a mutex to protect the concurrent mapping flow, a hash to hold all
 * page tables hops related to this context.
 * Return: 0 on success, non-zero otherwise.
 */
पूर्णांक hl_mmu_ctx_init(काष्ठा hl_ctx *ctx)
अणु
	काष्ठा hl_device *hdev = ctx->hdev;
	पूर्णांक rc = -EOPNOTSUPP;

	अगर (!hdev->mmu_enable)
		वापस 0;

	mutex_init(&ctx->mmu_lock);

	अगर (hdev->mmu_func[MMU_DR_PGT].ctx_init != शून्य) अणु
		rc = hdev->mmu_func[MMU_DR_PGT].ctx_init(ctx);
		अगर (rc)
			वापस rc;
	पूर्ण

	अगर (hdev->mmu_func[MMU_HR_PGT].ctx_init != शून्य)
		rc = hdev->mmu_func[MMU_HR_PGT].ctx_init(ctx);

	वापस rc;
पूर्ण

/*
 * hl_mmu_ctx_fini - disable a ctx from using the mmu module
 *
 * @ctx: poपूर्णांकer to the context काष्ठाure
 *
 * This function करोes the following:
 * - Free any pgts which were not मुक्तd yet
 * - Free the mutex
 * - Free DRAM शेष page mapping hops
 */
व्योम hl_mmu_ctx_fini(काष्ठा hl_ctx *ctx)
अणु
	काष्ठा hl_device *hdev = ctx->hdev;

	अगर (!hdev->mmu_enable)
		वापस;

	अगर (hdev->mmu_func[MMU_DR_PGT].ctx_fini != शून्य)
		hdev->mmu_func[MMU_DR_PGT].ctx_fini(ctx);

	अगर (hdev->mmu_func[MMU_HR_PGT].ctx_fini != शून्य)
		hdev->mmu_func[MMU_HR_PGT].ctx_fini(ctx);

	mutex_destroy(&ctx->mmu_lock);
पूर्ण

/*
 * hl_mmu_unmap_page - unmaps a भव addr
 *
 * @ctx: poपूर्णांकer to the context काष्ठाure
 * @virt_addr: virt addr to map from
 * @page_size: size of the page to unmap
 * @flush_pte: whether to करो a PCI flush
 *
 * This function करोes the following:
 * - Check that the virt addr is mapped
 * - Unmap the virt addr and मुक्तs pgts अगर possible
 * - Returns 0 on success, -EINVAL अगर the given addr is not mapped
 *
 * Because this function changes the page tables in the device and because it
 * changes the MMU hash, it must be रक्षित by a lock.
 * However, because it maps only a single page, the lock should be implemented
 * in a higher level in order to protect the entire mapping of the memory area
 *
 * For optimization reasons PCI flush may be requested once after unmapping of
 * large area.
 */
पूर्णांक hl_mmu_unmap_page(काष्ठा hl_ctx *ctx, u64 virt_addr, u32 page_size,
		bool flush_pte)
अणु
	काष्ठा hl_device *hdev = ctx->hdev;
	काष्ठा asic_fixed_properties *prop = &hdev->asic_prop;
	काष्ठा hl_mmu_properties *mmu_prop;
	u64 real_virt_addr;
	u32 real_page_size, npages;
	पूर्णांक i, rc = 0, pgt_residency;
	bool is_dram_addr;

	अगर (!hdev->mmu_enable)
		वापस 0;

	is_dram_addr = hl_is_dram_va(hdev, virt_addr);

	अगर (is_dram_addr)
		mmu_prop = &prop->dmmu;
	अन्यथा अगर ((page_size % prop->pmmu_huge.page_size) == 0)
		mmu_prop = &prop->pmmu_huge;
	अन्यथा
		mmu_prop = &prop->pmmu;

	pgt_residency = mmu_prop->host_resident ? MMU_HR_PGT : MMU_DR_PGT;
	/*
	 * The H/W handles mapping of specअगरic page sizes. Hence अगर the page
	 * size is bigger, we अवरोध it to sub-pages and unmap them separately.
	 */
	अगर ((page_size % mmu_prop->page_size) == 0) अणु
		real_page_size = mmu_prop->page_size;
	पूर्ण अन्यथा अणु
		/*
		 * MMU page size may dअगरfer from DRAM page size.
		 * In such हाल work with the DRAM page size and let the MMU
		 * scrambling routine to handle this mismatch when
		 * calculating the address to हटाओ from the MMU page table
		 */
		अगर (is_dram_addr && ((page_size % prop->dram_page_size) == 0)) अणु
			real_page_size = prop->dram_page_size;
		पूर्ण अन्यथा अणु
			dev_err(hdev->dev,
				"page size of %u is not %uKB aligned, can't unmap\n",
				page_size, mmu_prop->page_size >> 10);

			वापस -EFAULT;
		पूर्ण
	पूर्ण

	npages = page_size / real_page_size;
	real_virt_addr = virt_addr;

	क्रम (i = 0 ; i < npages ; i++) अणु
		rc = hdev->mmu_func[pgt_residency].unmap(ctx,
						real_virt_addr, is_dram_addr);
		अगर (rc)
			अवरोध;

		real_virt_addr += real_page_size;
	पूर्ण

	अगर (flush_pte)
		hdev->mmu_func[pgt_residency].flush(ctx);

	वापस rc;
पूर्ण

/*
 * hl_mmu_map_page - maps a भव addr to physical addr
 *
 * @ctx: poपूर्णांकer to the context काष्ठाure
 * @virt_addr: virt addr to map from
 * @phys_addr: phys addr to map to
 * @page_size: physical page size
 * @flush_pte: whether to करो a PCI flush
 *
 * This function करोes the following:
 * - Check that the virt addr is not mapped
 * - Allocate pgts as necessary in order to map the virt addr to the phys
 * - Returns 0 on success, -EINVAL अगर addr is alपढ़ोy mapped, or -ENOMEM.
 *
 * Because this function changes the page tables in the device and because it
 * changes the MMU hash, it must be रक्षित by a lock.
 * However, because it maps only a single page, the lock should be implemented
 * in a higher level in order to protect the entire mapping of the memory area
 *
 * For optimization reasons PCI flush may be requested once after mapping of
 * large area.
 */
पूर्णांक hl_mmu_map_page(काष्ठा hl_ctx *ctx, u64 virt_addr, u64 phys_addr,
		u32 page_size, bool flush_pte)
अणु
	काष्ठा hl_device *hdev = ctx->hdev;
	काष्ठा asic_fixed_properties *prop = &hdev->asic_prop;
	काष्ठा hl_mmu_properties *mmu_prop;
	u64 real_virt_addr, real_phys_addr;
	u32 real_page_size, npages;
	पूर्णांक i, rc, pgt_residency, mapped_cnt = 0;
	bool is_dram_addr;


	अगर (!hdev->mmu_enable)
		वापस 0;

	is_dram_addr = hl_is_dram_va(hdev, virt_addr);

	अगर (is_dram_addr)
		mmu_prop = &prop->dmmu;
	अन्यथा अगर ((page_size % prop->pmmu_huge.page_size) == 0)
		mmu_prop = &prop->pmmu_huge;
	अन्यथा
		mmu_prop = &prop->pmmu;

	pgt_residency = mmu_prop->host_resident ? MMU_HR_PGT : MMU_DR_PGT;

	/*
	 * The H/W handles mapping of specअगरic page sizes. Hence अगर the page
	 * size is bigger, we अवरोध it to sub-pages and map them separately.
	 */
	अगर ((page_size % mmu_prop->page_size) == 0) अणु
		real_page_size = mmu_prop->page_size;
	पूर्ण अन्यथा अगर (is_dram_addr && ((page_size % prop->dram_page_size) == 0) &&
			(prop->dram_page_size < mmu_prop->page_size)) अणु
		/*
		 * MMU page size may dअगरfer from DRAM page size.
		 * In such हाल work with the DRAM page size and let the MMU
		 * scrambling routine handle this mismatch when calculating
		 * the address to place in the MMU page table. (in that हाल
		 * also make sure that the dram_page_size smaller than the
		 * mmu page size)
		 */
		real_page_size = prop->dram_page_size;
	पूर्ण अन्यथा अणु
		dev_err(hdev->dev,
			"page size of %u is not %uKB aligned, can't map\n",
			page_size, mmu_prop->page_size >> 10);

		वापस -EFAULT;
	पूर्ण

	/*
	 * Verअगरy that the phys and virt addresses are aligned with the
	 * MMU page size (in dram this means checking the address and MMU
	 * after scrambling)
	 */
	अगर ((is_dram_addr &&
			((hdev->asic_funcs->scramble_addr(hdev, phys_addr) &
				(mmu_prop->page_size - 1)) ||
			(hdev->asic_funcs->scramble_addr(hdev, virt_addr) &
				(mmu_prop->page_size - 1)))) ||
		(!is_dram_addr && ((phys_addr & (real_page_size - 1)) ||
				(virt_addr & (real_page_size - 1)))))
		dev_crit(hdev->dev,
			"Mapping address 0x%llx with virtual address 0x%llx and page size of 0x%x is erroneous! Addresses must be divisible by page size",
			phys_addr, virt_addr, real_page_size);

	npages = page_size / real_page_size;
	real_virt_addr = virt_addr;
	real_phys_addr = phys_addr;

	क्रम (i = 0 ; i < npages ; i++) अणु
		rc = hdev->mmu_func[pgt_residency].map(ctx,
						real_virt_addr, real_phys_addr,
						real_page_size, is_dram_addr);
		अगर (rc)
			जाओ err;

		real_virt_addr += real_page_size;
		real_phys_addr += real_page_size;
		mapped_cnt++;
	पूर्ण

	अगर (flush_pte)
		hdev->mmu_func[pgt_residency].flush(ctx);

	वापस 0;

err:
	real_virt_addr = virt_addr;
	क्रम (i = 0 ; i < mapped_cnt ; i++) अणु
		अगर (hdev->mmu_func[pgt_residency].unmap(ctx,
						real_virt_addr, is_dram_addr))
			dev_warn_ratelimited(hdev->dev,
				"failed to unmap va: 0x%llx\n", real_virt_addr);

		real_virt_addr += real_page_size;
	पूर्ण

	hdev->mmu_func[pgt_residency].flush(ctx);

	वापस rc;
पूर्ण

/*
 * hl_mmu_map_contiguous - implements a wrapper क्रम hl_mmu_map_page
 *                         क्रम mapping contiguous physical memory
 *
 * @ctx: poपूर्णांकer to the context काष्ठाure
 * @virt_addr: virt addr to map from
 * @phys_addr: phys addr to map to
 * @size: size to map
 *
 */
पूर्णांक hl_mmu_map_contiguous(काष्ठा hl_ctx *ctx, u64 virt_addr,
					u64 phys_addr, u32 size)
अणु
	काष्ठा hl_device *hdev = ctx->hdev;
	काष्ठा asic_fixed_properties *prop = &hdev->asic_prop;
	u64 curr_va, curr_pa;
	u32 page_size;
	bool flush_pte;
	पूर्णांक rc = 0, off;

	अगर (hl_mem_area_inside_range(virt_addr, size,
			prop->dmmu.start_addr, prop->dmmu.end_addr))
		page_size = prop->dmmu.page_size;
	अन्यथा अगर (hl_mem_area_inside_range(virt_addr, size,
			prop->pmmu.start_addr, prop->pmmu.end_addr))
		page_size = prop->pmmu.page_size;
	अन्यथा अगर (hl_mem_area_inside_range(virt_addr, size,
			prop->pmmu_huge.start_addr, prop->pmmu_huge.end_addr))
		page_size = prop->pmmu_huge.page_size;
	अन्यथा
		वापस -EINVAL;

	क्रम (off = 0 ; off < size ; off += page_size) अणु
		curr_va = virt_addr + off;
		curr_pa = phys_addr + off;
		flush_pte = (off + page_size) >= size;
		rc = hl_mmu_map_page(ctx, curr_va, curr_pa, page_size,
								flush_pte);
		अगर (rc) अणु
			dev_err(hdev->dev,
				"Map failed for va 0x%llx to pa 0x%llx\n",
				curr_va, curr_pa);
			जाओ unmap;
		पूर्ण
	पूर्ण

	वापस rc;

unmap:
	क्रम (; off >= 0 ; off -= page_size) अणु
		curr_va = virt_addr + off;
		flush_pte = (off - (s32) page_size) < 0;
		अगर (hl_mmu_unmap_page(ctx, curr_va, page_size, flush_pte))
			dev_warn_ratelimited(hdev->dev,
				"failed to unmap va 0x%llx\n", curr_va);
	पूर्ण

	वापस rc;
पूर्ण

/*
 * hl_mmu_unmap_contiguous - implements a wrapper क्रम hl_mmu_unmap_page
 *                           क्रम unmapping contiguous physical memory
 *
 * @ctx: poपूर्णांकer to the context काष्ठाure
 * @virt_addr: virt addr to unmap
 * @size: size to unmap
 *
 */
पूर्णांक hl_mmu_unmap_contiguous(काष्ठा hl_ctx *ctx, u64 virt_addr, u32 size)
अणु
	काष्ठा hl_device *hdev = ctx->hdev;
	काष्ठा asic_fixed_properties *prop = &hdev->asic_prop;
	u64 curr_va;
	u32 page_size;
	bool flush_pte;
	पूर्णांक rc = 0, off;

	अगर (hl_mem_area_inside_range(virt_addr, size,
			prop->dmmu.start_addr, prop->dmmu.end_addr))
		page_size = prop->dmmu.page_size;
	अन्यथा अगर (hl_mem_area_inside_range(virt_addr, size,
			prop->pmmu.start_addr, prop->pmmu.end_addr))
		page_size = prop->pmmu.page_size;
	अन्यथा अगर (hl_mem_area_inside_range(virt_addr, size,
			prop->pmmu_huge.start_addr, prop->pmmu_huge.end_addr))
		page_size = prop->pmmu_huge.page_size;
	अन्यथा
		वापस -EINVAL;

	क्रम (off = 0 ; off < size ; off += page_size) अणु
		curr_va = virt_addr + off;
		flush_pte = (off + page_size) >= size;
		rc = hl_mmu_unmap_page(ctx, curr_va, page_size, flush_pte);
		अगर (rc)
			dev_warn_ratelimited(hdev->dev,
				"Unmap failed for va 0x%llx\n", curr_va);
	पूर्ण

	वापस rc;
पूर्ण

/*
 * hl_mmu_swap_out - marks all mapping of the given ctx as swapped out
 *
 * @ctx: poपूर्णांकer to the context काष्ठाure
 *
 */
व्योम hl_mmu_swap_out(काष्ठा hl_ctx *ctx)
अणु
	काष्ठा hl_device *hdev = ctx->hdev;

	अगर (!hdev->mmu_enable)
		वापस;

	अगर (hdev->mmu_func[MMU_DR_PGT].swap_out != शून्य)
		hdev->mmu_func[MMU_DR_PGT].swap_out(ctx);

	अगर (hdev->mmu_func[MMU_HR_PGT].swap_out != शून्य)
		hdev->mmu_func[MMU_HR_PGT].swap_out(ctx);
पूर्ण

/*
 * hl_mmu_swap_in - marks all mapping of the given ctx as swapped in
 *
 * @ctx: poपूर्णांकer to the context काष्ठाure
 *
 */
व्योम hl_mmu_swap_in(काष्ठा hl_ctx *ctx)
अणु
	काष्ठा hl_device *hdev = ctx->hdev;

	अगर (!hdev->mmu_enable)
		वापस;

	अगर (hdev->mmu_func[MMU_DR_PGT].swap_in != शून्य)
		hdev->mmu_func[MMU_DR_PGT].swap_in(ctx);

	अगर (hdev->mmu_func[MMU_HR_PGT].swap_in != शून्य)
		hdev->mmu_func[MMU_HR_PGT].swap_in(ctx);
पूर्ण

अटल व्योम hl_mmu_pa_page_with_offset(काष्ठा hl_ctx *ctx, u64 virt_addr,
						काष्ठा hl_mmu_hop_info *hops,
						u64 *phys_addr)
अणु
	काष्ठा hl_device *hdev = ctx->hdev;
	काष्ठा asic_fixed_properties *prop = &hdev->asic_prop;
	u64 offset_mask, addr_mask, hop_shअगरt, पंचांगp_phys_addr;
	u32 hop0_shअगरt_off;
	व्योम *p;

	/* last hop holds the phys address and flags */
	अगर (hops->unscrambled_paddr)
		पंचांगp_phys_addr = hops->unscrambled_paddr;
	अन्यथा
		पंचांगp_phys_addr = hops->hop_info[hops->used_hops - 1].hop_pte_val;

	अगर (hops->range_type == HL_VA_RANGE_TYPE_HOST_HUGE)
		p = &prop->pmmu_huge;
	अन्यथा अगर (hops->range_type == HL_VA_RANGE_TYPE_HOST)
		p = &prop->pmmu;
	अन्यथा /* HL_VA_RANGE_TYPE_DRAM */
		p = &prop->dmmu;

	अगर ((hops->range_type == HL_VA_RANGE_TYPE_DRAM) &&
			!is_घातer_of_2(prop->dram_page_size)) अणु
		u32 bit;
		u64 page_offset_mask;
		u64 phys_addr_mask;

		bit = __ffs64((u64)prop->dram_page_size);
		page_offset_mask = ((1ull << bit) - 1);
		phys_addr_mask = ~page_offset_mask;
		*phys_addr = (पंचांगp_phys_addr & phys_addr_mask) |
				(virt_addr & page_offset_mask);
	पूर्ण अन्यथा अणु
		/*
		 * find the correct hop shअगरt field in hl_mmu_properties
		 * काष्ठाure in order to determine the right masks
		 * क्रम the page offset.
		 */
		hop0_shअगरt_off = दुरत्व(काष्ठा hl_mmu_properties, hop0_shअगरt);
		p = (अक्षर *)p + hop0_shअगरt_off;
		p = (अक्षर *)p + ((hops->used_hops - 1) * माप(u64));
		hop_shअगरt = *(u64 *)p;
		offset_mask = (1ull << hop_shअगरt) - 1;
		addr_mask = ~(offset_mask);
		*phys_addr = (पंचांगp_phys_addr & addr_mask) |
				(virt_addr & offset_mask);
	पूर्ण
पूर्ण

पूर्णांक hl_mmu_va_to_pa(काष्ठा hl_ctx *ctx, u64 virt_addr, u64 *phys_addr)
अणु
	काष्ठा hl_mmu_hop_info hops;
	पूर्णांक rc;

	स_रखो(&hops, 0, माप(hops));

	rc = hl_mmu_get_tlb_info(ctx, virt_addr, &hops);
	अगर (rc)
		वापस rc;

	hl_mmu_pa_page_with_offset(ctx, virt_addr, &hops,  phys_addr);

	वापस 0;
पूर्ण

पूर्णांक hl_mmu_get_tlb_info(काष्ठा hl_ctx *ctx, u64 virt_addr,
			काष्ठा hl_mmu_hop_info *hops)
अणु
	काष्ठा hl_device *hdev = ctx->hdev;
	काष्ठा asic_fixed_properties *prop = &hdev->asic_prop;
	काष्ठा hl_mmu_properties *mmu_prop;
	पूर्णांक rc;
	bool is_dram_addr;

	अगर (!hdev->mmu_enable)
		वापस -EOPNOTSUPP;

	hops->scrambled_vaddr = virt_addr;      /* assume no scrambling */

	is_dram_addr = hl_mem_area_inside_range(virt_addr, prop->dmmu.page_size,
						prop->dmmu.start_addr,
						prop->dmmu.end_addr);

	/* host-residency is the same in PMMU and HPMMU, use one of them */
	mmu_prop = is_dram_addr ? &prop->dmmu : &prop->pmmu;

	mutex_lock(&ctx->mmu_lock);

	अगर (mmu_prop->host_resident)
		rc = hdev->mmu_func[MMU_HR_PGT].get_tlb_info(ctx,
							virt_addr, hops);
	अन्यथा
		rc = hdev->mmu_func[MMU_DR_PGT].get_tlb_info(ctx,
							virt_addr, hops);

	mutex_unlock(&ctx->mmu_lock);

	/* add page offset to physical address */
	अगर (hops->unscrambled_paddr)
		hl_mmu_pa_page_with_offset(ctx, virt_addr, hops,
					&hops->unscrambled_paddr);

	वापस rc;
पूर्ण

पूर्णांक hl_mmu_अगर_set_funcs(काष्ठा hl_device *hdev)
अणु
	अगर (!hdev->mmu_enable)
		वापस 0;

	चयन (hdev->asic_type) अणु
	हाल ASIC_GOYA:
	हाल ASIC_GAUDI:
	हाल ASIC_GAUDI_SEC:
		hl_mmu_v1_set_funcs(hdev, &hdev->mmu_func[MMU_DR_PGT]);
		अवरोध;
	शेष:
		dev_err(hdev->dev, "Unrecognized ASIC type %d\n",
			hdev->asic_type);
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * hl_mmu_scramble_addr() - The generic mmu address scrambling routine.
 * @hdev: poपूर्णांकer to device data.
 * @addr: The address to scramble.
 *
 * Return: The scrambled address.
 */
u64 hl_mmu_scramble_addr(काष्ठा hl_device *hdev, u64 addr)
अणु
	वापस addr;
पूर्ण

/**
 * hl_mmu_descramble_addr() - The generic mmu address descrambling
 * routine.
 * @hdev: poपूर्णांकer to device data.
 * @addr: The address to descramble.
 *
 * Return: The un-scrambled address.
 */
u64 hl_mmu_descramble_addr(काष्ठा hl_device *hdev, u64 addr)
अणु
	वापस addr;
पूर्ण
