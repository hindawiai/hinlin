<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * Copyright 2016-2019 HabanaLअसल, Ltd.
 * All Rights Reserved.
 */

#समावेश "../habanalabs.h"
#समावेश "../../include/hw_ip/mmu/mmu_general.h"

#समावेश <linux/slab.h>

अटल अंतरभूत u64 get_phys_addr(काष्ठा hl_ctx *ctx, u64 shaकरोw_addr);

अटल काष्ठा pgt_info *get_pgt_info(काष्ठा hl_ctx *ctx, u64 hop_addr)
अणु
	काष्ठा pgt_info *pgt_info = शून्य;

	hash_क्रम_each_possible(ctx->mmu_shaकरोw_hash, pgt_info, node,
				(अचिन्हित दीर्घ) hop_addr)
		अगर (hop_addr == pgt_info->shaकरोw_addr)
			अवरोध;

	वापस pgt_info;
पूर्ण

अटल व्योम _मुक्त_hop(काष्ठा hl_ctx *ctx, काष्ठा pgt_info *pgt_info)
अणु
	काष्ठा hl_device *hdev = ctx->hdev;

	gen_pool_मुक्त(hdev->mmu_priv.dr.mmu_pgt_pool, pgt_info->phys_addr,
			hdev->asic_prop.mmu_hop_table_size);
	hash_del(&pgt_info->node);
	kमुक्त((u64 *) (uपूर्णांकptr_t) pgt_info->shaकरोw_addr);
	kमुक्त(pgt_info);
पूर्ण

अटल व्योम मुक्त_hop(काष्ठा hl_ctx *ctx, u64 hop_addr)
अणु
	काष्ठा pgt_info *pgt_info = get_pgt_info(ctx, hop_addr);

	_मुक्त_hop(ctx, pgt_info);
पूर्ण

अटल u64 alloc_hop(काष्ठा hl_ctx *ctx)
अणु
	काष्ठा hl_device *hdev = ctx->hdev;
	काष्ठा asic_fixed_properties *prop = &hdev->asic_prop;
	काष्ठा pgt_info *pgt_info;
	u64 phys_addr, shaकरोw_addr;

	pgt_info = kदो_स्मृति(माप(*pgt_info), GFP_KERNEL);
	अगर (!pgt_info)
		वापस ULदीर्घ_उच्च;

	phys_addr = (u64) gen_pool_alloc(hdev->mmu_priv.dr.mmu_pgt_pool,
					prop->mmu_hop_table_size);
	अगर (!phys_addr) अणु
		dev_err(hdev->dev, "failed to allocate page\n");
		जाओ pool_add_err;
	पूर्ण

	shaकरोw_addr = (u64) (uपूर्णांकptr_t) kzalloc(prop->mmu_hop_table_size,
						GFP_KERNEL);
	अगर (!shaकरोw_addr)
		जाओ shaकरोw_err;

	pgt_info->phys_addr = phys_addr;
	pgt_info->shaकरोw_addr = shaकरोw_addr;
	pgt_info->ctx = ctx;
	pgt_info->num_of_ptes = 0;
	hash_add(ctx->mmu_shaकरोw_hash, &pgt_info->node, shaकरोw_addr);

	वापस shaकरोw_addr;

shaकरोw_err:
	gen_pool_मुक्त(hdev->mmu_priv.dr.mmu_pgt_pool, phys_addr,
			prop->mmu_hop_table_size);
pool_add_err:
	kमुक्त(pgt_info);

	वापस ULदीर्घ_उच्च;
पूर्ण

अटल अंतरभूत u64 get_phys_hop0_addr(काष्ठा hl_ctx *ctx)
अणु
	वापस ctx->hdev->asic_prop.mmu_pgt_addr +
			(ctx->asid * ctx->hdev->asic_prop.mmu_hop_table_size);
पूर्ण

अटल अंतरभूत u64 get_hop0_addr(काष्ठा hl_ctx *ctx)
अणु
	वापस (u64) (uपूर्णांकptr_t) ctx->hdev->mmu_priv.dr.mmu_shaकरोw_hop0 +
			(ctx->asid * ctx->hdev->asic_prop.mmu_hop_table_size);
पूर्ण

अटल व्योम flush(काष्ठा hl_ctx *ctx)
अणु
	/* flush all ग_लिखोs from all cores to reach PCI */
	mb();
	ctx->hdev->asic_funcs->पढ़ो_pte(ctx->hdev, get_phys_hop0_addr(ctx));
पूर्ण

/* transक्रमm the value to physical address when writing to H/W */
अटल अंतरभूत व्योम ग_लिखो_pte(काष्ठा hl_ctx *ctx, u64 shaकरोw_pte_addr, u64 val)
अणु
	/*
	 * The value to ग_लिखो is actually the address of the next shaकरोw hop +
	 * flags at the 12 LSBs.
	 * Hence in order to get the value to ग_लिखो to the physical PTE, we
	 * clear the 12 LSBs and translate the shaकरोw hop to its associated
	 * physical hop, and add back the original 12 LSBs.
	 */
	u64 phys_val = get_phys_addr(ctx, val & HOP_PHYS_ADDR_MASK) |
				(val & FLAGS_MASK);

	ctx->hdev->asic_funcs->ग_लिखो_pte(ctx->hdev,
					get_phys_addr(ctx, shaकरोw_pte_addr),
					phys_val);

	*(u64 *) (uपूर्णांकptr_t) shaकरोw_pte_addr = val;
पूर्ण

/* करो not transक्रमm the value to physical address when writing to H/W */
अटल अंतरभूत व्योम ग_लिखो_final_pte(काष्ठा hl_ctx *ctx, u64 shaकरोw_pte_addr,
					u64 val)
अणु
	ctx->hdev->asic_funcs->ग_लिखो_pte(ctx->hdev,
					get_phys_addr(ctx, shaकरोw_pte_addr),
					val);
	*(u64 *) (uपूर्णांकptr_t) shaकरोw_pte_addr = val;
पूर्ण

/* clear the last and present bits */
अटल अंतरभूत व्योम clear_pte(काष्ठा hl_ctx *ctx, u64 pte_addr)
अणु
	/* no need to transक्रमm the value to physical address */
	ग_लिखो_final_pte(ctx, pte_addr, 0);
पूर्ण

अटल अंतरभूत व्योम get_pte(काष्ठा hl_ctx *ctx, u64 hop_addr)
अणु
	get_pgt_info(ctx, hop_addr)->num_of_ptes++;
पूर्ण

/*
 * put_pte - decrement the num of ptes and मुक्त the hop अगर possible
 *
 * @ctx: poपूर्णांकer to the context काष्ठाure
 * @hop_addr: addr of the hop
 *
 * This function वापसs the number of ptes left on this hop. If the number is
 * 0, it means the pte was मुक्तd.
 */
अटल अंतरभूत पूर्णांक put_pte(काष्ठा hl_ctx *ctx, u64 hop_addr)
अणु
	काष्ठा pgt_info *pgt_info = get_pgt_info(ctx, hop_addr);
	पूर्णांक num_of_ptes_left;

	pgt_info->num_of_ptes--;

	/*
	 * Need to save the number of ptes left because मुक्त_hop might मुक्त
	 * the pgt_info
	 */
	num_of_ptes_left = pgt_info->num_of_ptes;
	अगर (!num_of_ptes_left)
		_मुक्त_hop(ctx, pgt_info);

	वापस num_of_ptes_left;
पूर्ण

अटल अंतरभूत u64 get_hopN_pte_addr(काष्ठा hl_ctx *ctx, u64 hop_addr,
					u64 virt_addr, u64 mask, u64 shअगरt)
अणु
	वापस hop_addr + ctx->hdev->asic_prop.mmu_pte_size *
			((virt_addr & mask) >> shअगरt);
पूर्ण

अटल अंतरभूत u64 get_hop0_pte_addr(काष्ठा hl_ctx *ctx,
					काष्ठा hl_mmu_properties *mmu_prop,
					u64 hop_addr, u64 vaddr)
अणु
	वापस get_hopN_pte_addr(ctx, hop_addr, vaddr, mmu_prop->hop0_mask,
					mmu_prop->hop0_shअगरt);
पूर्ण

अटल अंतरभूत u64 get_hop1_pte_addr(काष्ठा hl_ctx *ctx,
					काष्ठा hl_mmu_properties *mmu_prop,
					u64 hop_addr, u64 vaddr)
अणु
	वापस get_hopN_pte_addr(ctx, hop_addr, vaddr, mmu_prop->hop1_mask,
					mmu_prop->hop1_shअगरt);
पूर्ण

अटल अंतरभूत u64 get_hop2_pte_addr(काष्ठा hl_ctx *ctx,
					काष्ठा hl_mmu_properties *mmu_prop,
					u64 hop_addr, u64 vaddr)
अणु
	वापस get_hopN_pte_addr(ctx, hop_addr, vaddr, mmu_prop->hop2_mask,
					mmu_prop->hop2_shअगरt);
पूर्ण

अटल अंतरभूत u64 get_hop3_pte_addr(काष्ठा hl_ctx *ctx,
					काष्ठा hl_mmu_properties *mmu_prop,
					u64 hop_addr, u64 vaddr)
अणु
	वापस get_hopN_pte_addr(ctx, hop_addr, vaddr, mmu_prop->hop3_mask,
					mmu_prop->hop3_shअगरt);
पूर्ण

अटल अंतरभूत u64 get_hop4_pte_addr(काष्ठा hl_ctx *ctx,
					काष्ठा hl_mmu_properties *mmu_prop,
					u64 hop_addr, u64 vaddr)
अणु
	वापस get_hopN_pte_addr(ctx, hop_addr, vaddr, mmu_prop->hop4_mask,
					mmu_prop->hop4_shअगरt);
पूर्ण

अटल अंतरभूत u64 get_next_hop_addr(काष्ठा hl_ctx *ctx, u64 curr_pte)
अणु
	अगर (curr_pte & PAGE_PRESENT_MASK)
		वापस curr_pte & HOP_PHYS_ADDR_MASK;
	अन्यथा
		वापस ULदीर्घ_उच्च;
पूर्ण

अटल अंतरभूत u64 get_alloc_next_hop_addr(काष्ठा hl_ctx *ctx, u64 curr_pte,
						bool *is_new_hop)
अणु
	u64 hop_addr = get_next_hop_addr(ctx, curr_pte);

	अगर (hop_addr == ULदीर्घ_उच्च) अणु
		hop_addr = alloc_hop(ctx);
		*is_new_hop = (hop_addr != ULदीर्घ_उच्च);
	पूर्ण

	वापस hop_addr;
पूर्ण

/* translates shaकरोw address inside hop to a physical address */
अटल अंतरभूत u64 get_phys_addr(काष्ठा hl_ctx *ctx, u64 shaकरोw_addr)
अणु
	u64 page_mask = (ctx->hdev->asic_prop.mmu_hop_table_size - 1);
	u64 shaकरोw_hop_addr = shaकरोw_addr & ~page_mask;
	u64 pte_offset = shaकरोw_addr & page_mask;
	u64 phys_hop_addr;

	अगर (shaकरोw_hop_addr != get_hop0_addr(ctx))
		phys_hop_addr = get_pgt_info(ctx, shaकरोw_hop_addr)->phys_addr;
	अन्यथा
		phys_hop_addr = get_phys_hop0_addr(ctx);

	वापस phys_hop_addr + pte_offset;
पूर्ण

अटल पूर्णांक dram_शेष_mapping_init(काष्ठा hl_ctx *ctx)
अणु
	काष्ठा hl_device *hdev = ctx->hdev;
	काष्ठा asic_fixed_properties *prop = &hdev->asic_prop;
	u64 num_of_hop3, total_hops, hop0_addr, hop1_addr, hop2_addr,
		hop2_pte_addr, hop3_pte_addr, pte_val;
	पूर्णांक rc, i, j, hop3_allocated = 0;

	अगर ((!prop->dram_supports_भव_memory) ||
			(!hdev->dram_शेष_page_mapping) ||
			(ctx->asid == HL_KERNEL_ASID_ID))
		वापस 0;

	num_of_hop3 = prop->dram_size_क्रम_शेष_page_mapping;
	करो_भाग(num_of_hop3, prop->dram_page_size);
	करो_भाग(num_of_hop3, PTE_ENTRIES_IN_HOP);

	/* add hop1 and hop2 */
	total_hops = num_of_hop3 + 2;

	ctx->dram_शेष_hops = kzalloc(HL_PTE_SIZE * total_hops,  GFP_KERNEL);
	अगर (!ctx->dram_शेष_hops)
		वापस -ENOMEM;

	hop0_addr = get_hop0_addr(ctx);

	hop1_addr = alloc_hop(ctx);
	अगर (hop1_addr == ULदीर्घ_उच्च) अणु
		dev_err(hdev->dev, "failed to alloc hop 1\n");
		rc = -ENOMEM;
		जाओ hop1_err;
	पूर्ण

	ctx->dram_शेष_hops[total_hops - 1] = hop1_addr;

	hop2_addr = alloc_hop(ctx);
	अगर (hop2_addr == ULदीर्घ_उच्च) अणु
		dev_err(hdev->dev, "failed to alloc hop 2\n");
		rc = -ENOMEM;
		जाओ hop2_err;
	पूर्ण

	ctx->dram_शेष_hops[total_hops - 2] = hop2_addr;

	क्रम (i = 0 ; i < num_of_hop3 ; i++) अणु
		ctx->dram_शेष_hops[i] = alloc_hop(ctx);
		अगर (ctx->dram_शेष_hops[i] == ULदीर्घ_उच्च) अणु
			dev_err(hdev->dev, "failed to alloc hop 3, i: %d\n", i);
			rc = -ENOMEM;
			जाओ hop3_err;
		पूर्ण
		hop3_allocated++;
	पूर्ण

	/* need only pte 0 in hops 0 and 1 */
	pte_val = (hop1_addr & HOP_PHYS_ADDR_MASK) | PAGE_PRESENT_MASK;
	ग_लिखो_pte(ctx, hop0_addr, pte_val);

	pte_val = (hop2_addr & HOP_PHYS_ADDR_MASK) | PAGE_PRESENT_MASK;
	ग_लिखो_pte(ctx, hop1_addr, pte_val);
	get_pte(ctx, hop1_addr);

	hop2_pte_addr = hop2_addr;
	क्रम (i = 0 ; i < num_of_hop3 ; i++) अणु
		pte_val = (ctx->dram_शेष_hops[i] & HOP_PHYS_ADDR_MASK) |
				PAGE_PRESENT_MASK;
		ग_लिखो_pte(ctx, hop2_pte_addr, pte_val);
		get_pte(ctx, hop2_addr);
		hop2_pte_addr += HL_PTE_SIZE;
	पूर्ण

	pte_val = (prop->mmu_dram_शेष_page_addr & HOP_PHYS_ADDR_MASK) |
			LAST_MASK | PAGE_PRESENT_MASK;

	क्रम (i = 0 ; i < num_of_hop3 ; i++) अणु
		hop3_pte_addr = ctx->dram_शेष_hops[i];
		क्रम (j = 0 ; j < PTE_ENTRIES_IN_HOP ; j++) अणु
			ग_लिखो_final_pte(ctx, hop3_pte_addr, pte_val);
			get_pte(ctx, ctx->dram_शेष_hops[i]);
			hop3_pte_addr += HL_PTE_SIZE;
		पूर्ण
	पूर्ण

	flush(ctx);

	वापस 0;

hop3_err:
	क्रम (i = 0 ; i < hop3_allocated ; i++)
		मुक्त_hop(ctx, ctx->dram_शेष_hops[i]);

	मुक्त_hop(ctx, hop2_addr);
hop2_err:
	मुक्त_hop(ctx, hop1_addr);
hop1_err:
	kमुक्त(ctx->dram_शेष_hops);

	वापस rc;
पूर्ण

अटल व्योम dram_शेष_mapping_fini(काष्ठा hl_ctx *ctx)
अणु
	काष्ठा hl_device *hdev = ctx->hdev;
	काष्ठा asic_fixed_properties *prop = &hdev->asic_prop;
	u64 num_of_hop3, total_hops, hop0_addr, hop1_addr, hop2_addr,
		hop2_pte_addr, hop3_pte_addr;
	पूर्णांक i, j;

	अगर ((!prop->dram_supports_भव_memory) ||
			(!hdev->dram_शेष_page_mapping) ||
			(ctx->asid == HL_KERNEL_ASID_ID))
		वापस;

	num_of_hop3 = prop->dram_size_क्रम_शेष_page_mapping;
	करो_भाग(num_of_hop3, prop->dram_page_size);
	करो_भाग(num_of_hop3, PTE_ENTRIES_IN_HOP);

	hop0_addr = get_hop0_addr(ctx);
	/* add hop1 and hop2 */
	total_hops = num_of_hop3 + 2;
	hop1_addr = ctx->dram_शेष_hops[total_hops - 1];
	hop2_addr = ctx->dram_शेष_hops[total_hops - 2];

	क्रम (i = 0 ; i < num_of_hop3 ; i++) अणु
		hop3_pte_addr = ctx->dram_शेष_hops[i];
		क्रम (j = 0 ; j < PTE_ENTRIES_IN_HOP ; j++) अणु
			clear_pte(ctx, hop3_pte_addr);
			put_pte(ctx, ctx->dram_शेष_hops[i]);
			hop3_pte_addr += HL_PTE_SIZE;
		पूर्ण
	पूर्ण

	hop2_pte_addr = hop2_addr;
	hop2_pte_addr = hop2_addr;
	क्रम (i = 0 ; i < num_of_hop3 ; i++) अणु
		clear_pte(ctx, hop2_pte_addr);
		put_pte(ctx, hop2_addr);
		hop2_pte_addr += HL_PTE_SIZE;
	पूर्ण

	clear_pte(ctx, hop1_addr);
	put_pte(ctx, hop1_addr);
	clear_pte(ctx, hop0_addr);

	kमुक्त(ctx->dram_शेष_hops);

	flush(ctx);
पूर्ण

/**
 * hl_mmu_v1_init() - initialize the MMU module.
 * @hdev: habanaद_असल device काष्ठाure.
 *
 * This function करोes the following:
 * - Create a pool of pages क्रम pgt_infos.
 * - Create a shaकरोw table क्रम pgt
 *
 * Return: 0 क्रम success, non-zero क्रम failure.
 */
अटल पूर्णांक hl_mmu_v1_init(काष्ठा hl_device *hdev)
अणु
	काष्ठा asic_fixed_properties *prop = &hdev->asic_prop;
	पूर्णांक rc;

	hdev->mmu_priv.dr.mmu_pgt_pool =
			gen_pool_create(__ffs(prop->mmu_hop_table_size), -1);

	अगर (!hdev->mmu_priv.dr.mmu_pgt_pool) अणु
		dev_err(hdev->dev, "Failed to create page gen pool\n");
		वापस -ENOMEM;
	पूर्ण

	rc = gen_pool_add(hdev->mmu_priv.dr.mmu_pgt_pool, prop->mmu_pgt_addr +
			prop->mmu_hop0_tables_total_size,
			prop->mmu_pgt_size - prop->mmu_hop0_tables_total_size,
			-1);
	अगर (rc) अणु
		dev_err(hdev->dev, "Failed to add memory to page gen pool\n");
		जाओ err_pool_add;
	पूर्ण

	hdev->mmu_priv.dr.mmu_shaकरोw_hop0 = kvदो_स्मृति_array(prop->max_asid,
						prop->mmu_hop_table_size,
						GFP_KERNEL | __GFP_ZERO);
	अगर (ZERO_OR_शून्य_PTR(hdev->mmu_priv.dr.mmu_shaकरोw_hop0)) अणु
		rc = -ENOMEM;
		जाओ err_pool_add;
	पूर्ण

	/* MMU H/W init will be करोne in device hw_init() */

	वापस 0;

err_pool_add:
	gen_pool_destroy(hdev->mmu_priv.dr.mmu_pgt_pool);

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
अटल व्योम hl_mmu_v1_fini(काष्ठा hl_device *hdev)
अणु
	/* MMU H/W fini was alपढ़ोy करोne in device hw_fini() */

	अगर (!ZERO_OR_शून्य_PTR(hdev->mmu_priv.hr.mmu_shaकरोw_hop0)) अणु
		kvमुक्त(hdev->mmu_priv.dr.mmu_shaकरोw_hop0);
		gen_pool_destroy(hdev->mmu_priv.dr.mmu_pgt_pool);
	पूर्ण

	/* Make sure that अगर we arrive here again without init was called we
	 * won't cause kernel panic. This can happen क्रम example अगर we fail
	 * during hard reset code at certain poपूर्णांकs
	 */
	hdev->mmu_priv.dr.mmu_shaकरोw_hop0 = शून्य;
पूर्ण

/**
 * hl_mmu_ctx_init() - initialize a context क्रम using the MMU module.
 * @ctx: poपूर्णांकer to the context काष्ठाure to initialize.
 *
 * Initialize a mutex to protect the concurrent mapping flow, a hash to hold all
 * page tables hops related to this context.
 * Return: 0 on success, non-zero otherwise.
 */
अटल पूर्णांक hl_mmu_v1_ctx_init(काष्ठा hl_ctx *ctx)
अणु
	hash_init(ctx->mmu_shaकरोw_hash);
	वापस dram_शेष_mapping_init(ctx);
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
अटल व्योम hl_mmu_v1_ctx_fini(काष्ठा hl_ctx *ctx)
अणु
	काष्ठा hl_device *hdev = ctx->hdev;
	काष्ठा pgt_info *pgt_info;
	काष्ठा hlist_node *पंचांगp;
	पूर्णांक i;

	dram_शेष_mapping_fini(ctx);

	अगर (!hash_empty(ctx->mmu_shaकरोw_hash))
		dev_err(hdev->dev, "ctx %d is freed while it has pgts in use\n",
			ctx->asid);

	hash_क्रम_each_safe(ctx->mmu_shaकरोw_hash, i, पंचांगp, pgt_info, node) अणु
		dev_err_ratelimited(hdev->dev,
			"pgt_info of addr 0x%llx of asid %d was not destroyed, num_ptes: %d\n",
			pgt_info->phys_addr, ctx->asid, pgt_info->num_of_ptes);
		_मुक्त_hop(ctx, pgt_info);
	पूर्ण
पूर्ण

अटल पूर्णांक _hl_mmu_v1_unmap(काष्ठा hl_ctx *ctx,
				u64 virt_addr, bool is_dram_addr)
अणु
	काष्ठा hl_device *hdev = ctx->hdev;
	काष्ठा asic_fixed_properties *prop = &hdev->asic_prop;
	काष्ठा hl_mmu_properties *mmu_prop;
	u64 hop0_addr = 0, hop0_pte_addr = 0,
		hop1_addr = 0, hop1_pte_addr = 0,
		hop2_addr = 0, hop2_pte_addr = 0,
		hop3_addr = 0, hop3_pte_addr = 0,
		hop4_addr = 0, hop4_pte_addr = 0,
		curr_pte;
	bool is_huge, clear_hop3 = true;

	/* shअगरts and masks are the same in PMMU and HPMMU, use one of them */
	mmu_prop = is_dram_addr ? &prop->dmmu : &prop->pmmu;

	hop0_addr = get_hop0_addr(ctx);
	hop0_pte_addr = get_hop0_pte_addr(ctx, mmu_prop, hop0_addr, virt_addr);

	curr_pte = *(u64 *) (uपूर्णांकptr_t) hop0_pte_addr;

	hop1_addr = get_next_hop_addr(ctx, curr_pte);

	अगर (hop1_addr == ULदीर्घ_उच्च)
		जाओ not_mapped;

	hop1_pte_addr = get_hop1_pte_addr(ctx, mmu_prop, hop1_addr, virt_addr);

	curr_pte = *(u64 *) (uपूर्णांकptr_t) hop1_pte_addr;

	hop2_addr = get_next_hop_addr(ctx, curr_pte);

	अगर (hop2_addr == ULदीर्घ_उच्च)
		जाओ not_mapped;

	hop2_pte_addr = get_hop2_pte_addr(ctx, mmu_prop, hop2_addr, virt_addr);

	curr_pte = *(u64 *) (uपूर्णांकptr_t) hop2_pte_addr;

	hop3_addr = get_next_hop_addr(ctx, curr_pte);

	अगर (hop3_addr == ULदीर्घ_उच्च)
		जाओ not_mapped;

	hop3_pte_addr = get_hop3_pte_addr(ctx, mmu_prop, hop3_addr, virt_addr);

	curr_pte = *(u64 *) (uपूर्णांकptr_t) hop3_pte_addr;

	is_huge = curr_pte & LAST_MASK;

	अगर (is_dram_addr && !is_huge) अणु
		dev_err(hdev->dev,
				"DRAM unmapping should use huge pages only\n");
		वापस -EFAULT;
	पूर्ण

	अगर (!is_huge) अणु
		hop4_addr = get_next_hop_addr(ctx, curr_pte);

		अगर (hop4_addr == ULदीर्घ_उच्च)
			जाओ not_mapped;

		hop4_pte_addr = get_hop4_pte_addr(ctx, mmu_prop, hop4_addr,
							virt_addr);

		curr_pte = *(u64 *) (uपूर्णांकptr_t) hop4_pte_addr;

		clear_hop3 = false;
	पूर्ण

	अगर (hdev->dram_शेष_page_mapping && is_dram_addr) अणु
		u64 शेष_pte = (prop->mmu_dram_शेष_page_addr &
				HOP_PHYS_ADDR_MASK) | LAST_MASK |
					PAGE_PRESENT_MASK;
		अगर (curr_pte == शेष_pte) अणु
			dev_err(hdev->dev,
				"DRAM: hop3 PTE points to zero page, can't unmap, va: 0x%llx\n",
					virt_addr);
			जाओ not_mapped;
		पूर्ण

		अगर (!(curr_pte & PAGE_PRESENT_MASK)) अणु
			dev_err(hdev->dev,
				"DRAM: hop3 PTE is cleared! can't unmap, va: 0x%llx\n",
					virt_addr);
			जाओ not_mapped;
		पूर्ण

		ग_लिखो_final_pte(ctx, hop3_pte_addr, शेष_pte);
		put_pte(ctx, hop3_addr);
	पूर्ण अन्यथा अणु
		अगर (!(curr_pte & PAGE_PRESENT_MASK))
			जाओ not_mapped;

		अगर (hop4_addr)
			clear_pte(ctx, hop4_pte_addr);
		अन्यथा
			clear_pte(ctx, hop3_pte_addr);

		अगर (hop4_addr && !put_pte(ctx, hop4_addr))
			clear_hop3 = true;

		अगर (!clear_hop3)
			जाओ mapped;

		clear_pte(ctx, hop3_pte_addr);

		अगर (put_pte(ctx, hop3_addr))
			जाओ mapped;

		clear_pte(ctx, hop2_pte_addr);

		अगर (put_pte(ctx, hop2_addr))
			जाओ mapped;

		clear_pte(ctx, hop1_pte_addr);

		अगर (put_pte(ctx, hop1_addr))
			जाओ mapped;

		clear_pte(ctx, hop0_pte_addr);
	पूर्ण

mapped:
	वापस 0;

not_mapped:
	dev_err(hdev->dev, "virt addr 0x%llx is not mapped to phys addr\n",
		virt_addr);

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक _hl_mmu_v1_map(काष्ठा hl_ctx *ctx, u64 virt_addr, u64 phys_addr,
			u32 page_size, bool is_dram_addr)
अणु
	काष्ठा hl_device *hdev = ctx->hdev;
	काष्ठा asic_fixed_properties *prop = &hdev->asic_prop;
	काष्ठा hl_mmu_properties *mmu_prop;
	u64 hop0_addr = 0, hop0_pte_addr = 0,
		hop1_addr = 0, hop1_pte_addr = 0,
		hop2_addr = 0, hop2_pte_addr = 0,
		hop3_addr = 0, hop3_pte_addr = 0,
		hop4_addr = 0, hop4_pte_addr = 0,
		curr_pte = 0;
	bool hop1_new = false, hop2_new = false, hop3_new = false,
		hop4_new = false, is_huge;
	पूर्णांक rc = -ENOMEM;

	/*
	 * This mapping function can map a page or a huge page. For huge page
	 * there are only 3 hops rather than 4. Currently the DRAM allocation
	 * uses huge pages only but user memory could have been allocated with
	 * one of the two page sizes. Since this is a common code क्रम all the
	 * three हालs, we need this hugs page check.
	 */
	अगर (is_dram_addr) अणु
		mmu_prop = &prop->dmmu;
		is_huge = true;
	पूर्ण अन्यथा अगर (page_size == prop->pmmu_huge.page_size) अणु
		mmu_prop = &prop->pmmu_huge;
		is_huge = true;
	पूर्ण अन्यथा अणु
		mmu_prop = &prop->pmmu;
		is_huge = false;
	पूर्ण

	hop0_addr = get_hop0_addr(ctx);
	hop0_pte_addr = get_hop0_pte_addr(ctx, mmu_prop, hop0_addr, virt_addr);
	curr_pte = *(u64 *) (uपूर्णांकptr_t) hop0_pte_addr;

	hop1_addr = get_alloc_next_hop_addr(ctx, curr_pte, &hop1_new);
	अगर (hop1_addr == ULदीर्घ_उच्च)
		जाओ err;

	hop1_pte_addr = get_hop1_pte_addr(ctx, mmu_prop, hop1_addr, virt_addr);
	curr_pte = *(u64 *) (uपूर्णांकptr_t) hop1_pte_addr;

	hop2_addr = get_alloc_next_hop_addr(ctx, curr_pte, &hop2_new);
	अगर (hop2_addr == ULदीर्घ_उच्च)
		जाओ err;

	hop2_pte_addr = get_hop2_pte_addr(ctx, mmu_prop, hop2_addr, virt_addr);
	curr_pte = *(u64 *) (uपूर्णांकptr_t) hop2_pte_addr;

	hop3_addr = get_alloc_next_hop_addr(ctx, curr_pte, &hop3_new);
	अगर (hop3_addr == ULदीर्घ_उच्च)
		जाओ err;

	hop3_pte_addr = get_hop3_pte_addr(ctx, mmu_prop, hop3_addr, virt_addr);
	curr_pte = *(u64 *) (uपूर्णांकptr_t) hop3_pte_addr;

	अगर (!is_huge) अणु
		hop4_addr = get_alloc_next_hop_addr(ctx, curr_pte, &hop4_new);
		अगर (hop4_addr == ULदीर्घ_उच्च)
			जाओ err;

		hop4_pte_addr = get_hop4_pte_addr(ctx, mmu_prop, hop4_addr,
							virt_addr);
		curr_pte = *(u64 *) (uपूर्णांकptr_t) hop4_pte_addr;
	पूर्ण

	अगर (hdev->dram_शेष_page_mapping && is_dram_addr) अणु
		u64 शेष_pte = (prop->mmu_dram_शेष_page_addr &
					HOP_PHYS_ADDR_MASK) | LAST_MASK |
						PAGE_PRESENT_MASK;

		अगर (curr_pte != शेष_pte) अणु
			dev_err(hdev->dev,
				"DRAM: mapping already exists for virt_addr 0x%llx\n",
					virt_addr);
			rc = -EINVAL;
			जाओ err;
		पूर्ण

		अगर (hop1_new || hop2_new || hop3_new || hop4_new) अणु
			dev_err(hdev->dev,
				"DRAM mapping should not allocate more hops\n");
			rc = -EFAULT;
			जाओ err;
		पूर्ण
	पूर्ण अन्यथा अगर (curr_pte & PAGE_PRESENT_MASK) अणु
		dev_err(hdev->dev,
			"mapping already exists for virt_addr 0x%llx\n",
				virt_addr);

		dev_dbg(hdev->dev, "hop0 pte: 0x%llx (0x%llx)\n",
			*(u64 *) (uपूर्णांकptr_t) hop0_pte_addr, hop0_pte_addr);
		dev_dbg(hdev->dev, "hop1 pte: 0x%llx (0x%llx)\n",
			*(u64 *) (uपूर्णांकptr_t) hop1_pte_addr, hop1_pte_addr);
		dev_dbg(hdev->dev, "hop2 pte: 0x%llx (0x%llx)\n",
			*(u64 *) (uपूर्णांकptr_t) hop2_pte_addr, hop2_pte_addr);
		dev_dbg(hdev->dev, "hop3 pte: 0x%llx (0x%llx)\n",
			*(u64 *) (uपूर्णांकptr_t) hop3_pte_addr, hop3_pte_addr);

		अगर (!is_huge)
			dev_dbg(hdev->dev, "hop4 pte: 0x%llx (0x%llx)\n",
				*(u64 *) (uपूर्णांकptr_t) hop4_pte_addr,
				hop4_pte_addr);

		rc = -EINVAL;
		जाओ err;
	पूर्ण

	curr_pte = (phys_addr & HOP_PHYS_ADDR_MASK) | LAST_MASK
			| PAGE_PRESENT_MASK;

	अगर (is_huge)
		ग_लिखो_final_pte(ctx, hop3_pte_addr, curr_pte);
	अन्यथा
		ग_लिखो_final_pte(ctx, hop4_pte_addr, curr_pte);

	अगर (hop1_new) अणु
		curr_pte =
			(hop1_addr & HOP_PHYS_ADDR_MASK) | PAGE_PRESENT_MASK;
		ग_लिखो_pte(ctx, hop0_pte_addr, curr_pte);
	पूर्ण
	अगर (hop2_new) अणु
		curr_pte =
			(hop2_addr & HOP_PHYS_ADDR_MASK) | PAGE_PRESENT_MASK;
		ग_लिखो_pte(ctx, hop1_pte_addr, curr_pte);
		get_pte(ctx, hop1_addr);
	पूर्ण
	अगर (hop3_new) अणु
		curr_pte =
			(hop3_addr & HOP_PHYS_ADDR_MASK) | PAGE_PRESENT_MASK;
		ग_लिखो_pte(ctx, hop2_pte_addr, curr_pte);
		get_pte(ctx, hop2_addr);
	पूर्ण

	अगर (!is_huge) अणु
		अगर (hop4_new) अणु
			curr_pte = (hop4_addr & HOP_PHYS_ADDR_MASK) |
					PAGE_PRESENT_MASK;
			ग_लिखो_pte(ctx, hop3_pte_addr, curr_pte);
			get_pte(ctx, hop3_addr);
		पूर्ण

		get_pte(ctx, hop4_addr);
	पूर्ण अन्यथा अणु
		get_pte(ctx, hop3_addr);
	पूर्ण

	वापस 0;

err:
	अगर (hop4_new)
		मुक्त_hop(ctx, hop4_addr);
	अगर (hop3_new)
		मुक्त_hop(ctx, hop3_addr);
	अगर (hop2_new)
		मुक्त_hop(ctx, hop2_addr);
	अगर (hop1_new)
		मुक्त_hop(ctx, hop1_addr);

	वापस rc;
पूर्ण

/*
 * hl_mmu_v1_swap_out - marks all mapping of the given ctx as swapped out
 *
 * @ctx: poपूर्णांकer to the context काष्ठाure
 *
 */
अटल व्योम hl_mmu_v1_swap_out(काष्ठा hl_ctx *ctx)
अणु

पूर्ण

/*
 * hl_mmu_v1_swap_in - marks all mapping of the given ctx as swapped in
 *
 * @ctx: poपूर्णांकer to the context काष्ठाure
 *
 */
अटल व्योम hl_mmu_v1_swap_in(काष्ठा hl_ctx *ctx)
अणु

पूर्ण

अटल अंतरभूत u64 get_hop_pte_addr(काष्ठा hl_ctx *ctx,
				काष्ठा hl_mmu_properties *mmu_prop,
				पूर्णांक hop_num, u64 hop_addr, u64 virt_addr)
अणु
	चयन (hop_num) अणु
	हाल 0:
		वापस get_hop0_pte_addr(ctx, mmu_prop, hop_addr, virt_addr);
	हाल 1:
		वापस get_hop1_pte_addr(ctx, mmu_prop, hop_addr, virt_addr);
	हाल 2:
		वापस get_hop2_pte_addr(ctx, mmu_prop, hop_addr, virt_addr);
	हाल 3:
		वापस get_hop3_pte_addr(ctx, mmu_prop, hop_addr, virt_addr);
	हाल 4:
		वापस get_hop4_pte_addr(ctx, mmu_prop, hop_addr, virt_addr);
	शेष:
		अवरोध;
	पूर्ण
	वापस U64_MAX;
पूर्ण

अटल पूर्णांक hl_mmu_v1_get_tlb_info(काष्ठा hl_ctx *ctx, u64 virt_addr,
				काष्ठा hl_mmu_hop_info *hops)
अणु
	काष्ठा hl_device *hdev = ctx->hdev;
	काष्ठा asic_fixed_properties *prop = &hdev->asic_prop;
	काष्ठा hl_mmu_properties *mmu_prop;
	bool is_dram_addr, is_pmmu_addr, is_pmmu_h_addr, is_huge;
	पूर्णांक i, used_hops;

	is_dram_addr = hl_mem_area_inside_range(virt_addr, prop->dmmu.page_size,
						prop->dmmu.start_addr,
						prop->dmmu.end_addr);
	is_pmmu_addr = hl_mem_area_inside_range(virt_addr, prop->pmmu.page_size,
						prop->pmmu.start_addr,
						prop->pmmu.end_addr);
	is_pmmu_h_addr = hl_mem_area_inside_range(virt_addr,
						prop->pmmu_huge.page_size,
						prop->pmmu_huge.start_addr,
						prop->pmmu_huge.end_addr);
	अगर (is_dram_addr) अणु
		mmu_prop = &prop->dmmu;
		is_huge = true;
	पूर्ण अन्यथा अगर (is_pmmu_addr) अणु
		mmu_prop = &prop->pmmu;
		is_huge = false;
	पूर्ण अन्यथा अगर (is_pmmu_h_addr) अणु
		mmu_prop = &prop->pmmu_huge;
		is_huge = true;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	used_hops = mmu_prop->num_hops;

	/* huge pages use lesser hops */
	अगर (is_huge)
		used_hops--;

	hops->hop_info[0].hop_addr = get_phys_hop0_addr(ctx);
	hops->hop_info[0].hop_pte_addr =
			get_hop_pte_addr(ctx, mmu_prop, 0,
					hops->hop_info[0].hop_addr, virt_addr);
	hops->hop_info[0].hop_pte_val =
			hdev->asic_funcs->पढ़ो_pte(hdev,
						hops->hop_info[0].hop_pte_addr);

	क्रम (i = 1 ; i < used_hops ; i++) अणु
		hops->hop_info[i].hop_addr =
			get_next_hop_addr(ctx,
					hops->hop_info[i - 1].hop_pte_val);
		अगर (hops->hop_info[i].hop_addr == ULदीर्घ_उच्च)
			वापस -EFAULT;

		hops->hop_info[i].hop_pte_addr =
				get_hop_pte_addr(ctx, mmu_prop, i,
						hops->hop_info[i].hop_addr,
						virt_addr);
		hops->hop_info[i].hop_pte_val =
				hdev->asic_funcs->पढ़ो_pte(hdev,
						hops->hop_info[i].hop_pte_addr);

		अगर (!(hops->hop_info[i].hop_pte_val & PAGE_PRESENT_MASK))
			वापस -EFAULT;

		अगर (hops->hop_info[i].hop_pte_val & LAST_MASK)
			अवरोध;
	पूर्ण

	/* अगर passed over all hops then no last hop was found */
	अगर (i == mmu_prop->num_hops)
		वापस -EFAULT;

	अगर (!(hops->hop_info[i].hop_pte_val & PAGE_PRESENT_MASK))
		वापस -EFAULT;

	hops->used_hops = i + 1;

	वापस 0;
पूर्ण

/*
 * hl_mmu_v1_prepare - prepare mmu  क्रम working with mmu v1
 *
 * @hdev: poपूर्णांकer to the device काष्ठाure
 */
व्योम hl_mmu_v1_set_funcs(काष्ठा hl_device *hdev, काष्ठा hl_mmu_funcs *mmu)
अणु
	mmu->init = hl_mmu_v1_init;
	mmu->fini = hl_mmu_v1_fini;
	mmu->ctx_init = hl_mmu_v1_ctx_init;
	mmu->ctx_fini = hl_mmu_v1_ctx_fini;
	mmu->map = _hl_mmu_v1_map;
	mmu->unmap = _hl_mmu_v1_unmap;
	mmu->flush = flush;
	mmu->swap_out = hl_mmu_v1_swap_out;
	mmu->swap_in = hl_mmu_v1_swap_in;
	mmu->get_tlb_info = hl_mmu_v1_get_tlb_info;
पूर्ण
