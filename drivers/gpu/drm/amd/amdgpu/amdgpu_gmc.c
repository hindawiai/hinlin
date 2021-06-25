<शैली गुरु>
/*
 * Copyright 2018 Advanced Micro Devices, Inc.
 * All Rights Reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDERS, AUTHORS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 */

#समावेश <linux/io-64-nonatomic-lo-hi.h>

#समावेश "amdgpu.h"
#समावेश "amdgpu_gmc.h"
#समावेश "amdgpu_ras.h"
#समावेश "amdgpu_xgmi.h"

/**
 * amdgpu_gmc_pdb0_alloc - allocate vram क्रम pdb0
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Allocate video memory क्रम pdb0 and map it क्रम CPU access
 * Returns 0 क्रम success, error क्रम failure.
 */
पूर्णांक amdgpu_gmc_pdb0_alloc(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक r;
	काष्ठा amdgpu_bo_param bp;
	u64 vram_size = adev->gmc.xgmi.node_segment_size * adev->gmc.xgmi.num_physical_nodes;
	uपूर्णांक32_t pde0_page_shअगरt = adev->gmc.vmid0_page_table_block_size + 21;
	uपूर्णांक32_t npdes = (vram_size + (1ULL << pde0_page_shअगरt) -1) >> pde0_page_shअगरt;

	स_रखो(&bp, 0, माप(bp));
	bp.size = PAGE_ALIGN((npdes + 1) * 8);
	bp.byte_align = PAGE_SIZE;
	bp.करोमुख्य = AMDGPU_GEM_DOMAIN_VRAM;
	bp.flags = AMDGPU_GEM_CREATE_CPU_ACCESS_REQUIRED |
		AMDGPU_GEM_CREATE_VRAM_CONTIGUOUS;
	bp.type = tपंचांग_bo_type_kernel;
	bp.resv = शून्य;
	bp.bo_ptr_size = माप(काष्ठा amdgpu_bo);

	r = amdgpu_bo_create(adev, &bp, &adev->gmc.pdb0_bo);
	अगर (r)
		वापस r;

	r = amdgpu_bo_reserve(adev->gmc.pdb0_bo, false);
	अगर (unlikely(r != 0))
		जाओ bo_reserve_failure;

	r = amdgpu_bo_pin(adev->gmc.pdb0_bo, AMDGPU_GEM_DOMAIN_VRAM);
	अगर (r)
		जाओ bo_pin_failure;
	r = amdgpu_bo_kmap(adev->gmc.pdb0_bo, &adev->gmc.ptr_pdb0);
	अगर (r)
		जाओ bo_kmap_failure;

	amdgpu_bo_unreserve(adev->gmc.pdb0_bo);
	वापस 0;

bo_kmap_failure:
	amdgpu_bo_unpin(adev->gmc.pdb0_bo);
bo_pin_failure:
	amdgpu_bo_unreserve(adev->gmc.pdb0_bo);
bo_reserve_failure:
	amdgpu_bo_unref(&adev->gmc.pdb0_bo);
	वापस r;
पूर्ण

/**
 * amdgpu_gmc_get_pde_क्रम_bo - get the PDE क्रम a BO
 *
 * @bo: the BO to get the PDE क्रम
 * @level: the level in the PD hirarchy
 * @addr: resulting addr
 * @flags: resulting flags
 *
 * Get the address and flags to be used क्रम a PDE (Page Directory Entry).
 */
व्योम amdgpu_gmc_get_pde_क्रम_bo(काष्ठा amdgpu_bo *bo, पूर्णांक level,
			       uपूर्णांक64_t *addr, uपूर्णांक64_t *flags)
अणु
	काष्ठा amdgpu_device *adev = amdgpu_tपंचांग_adev(bo->tbo.bdev);

	चयन (bo->tbo.mem.mem_type) अणु
	हाल TTM_PL_TT:
		*addr = bo->tbo.tपंचांग->dma_address[0];
		अवरोध;
	हाल TTM_PL_VRAM:
		*addr = amdgpu_bo_gpu_offset(bo);
		अवरोध;
	शेष:
		*addr = 0;
		अवरोध;
	पूर्ण
	*flags = amdgpu_tपंचांग_tt_pde_flags(bo->tbo.tपंचांग, &bo->tbo.mem);
	amdgpu_gmc_get_vm_pde(adev, level, addr, flags);
पूर्ण

/*
 * amdgpu_gmc_pd_addr - वापस the address of the root directory
 */
uपूर्णांक64_t amdgpu_gmc_pd_addr(काष्ठा amdgpu_bo *bo)
अणु
	काष्ठा amdgpu_device *adev = amdgpu_tपंचांग_adev(bo->tbo.bdev);
	uपूर्णांक64_t pd_addr;

	/* TODO: move that पूर्णांकo ASIC specअगरic code */
	अगर (adev->asic_type >= CHIP_VEGA10) अणु
		uपूर्णांक64_t flags = AMDGPU_PTE_VALID;

		amdgpu_gmc_get_pde_क्रम_bo(bo, -1, &pd_addr, &flags);
		pd_addr |= flags;
	पूर्ण अन्यथा अणु
		pd_addr = amdgpu_bo_gpu_offset(bo);
	पूर्ण
	वापस pd_addr;
पूर्ण

/**
 * amdgpu_gmc_set_pte_pde - update the page tables using CPU
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @cpu_pt_addr: cpu address of the page table
 * @gpu_page_idx: entry in the page table to update
 * @addr: dst addr to ग_लिखो पूर्णांकo pte/pde
 * @flags: access flags
 *
 * Update the page tables using CPU.
 */
पूर्णांक amdgpu_gmc_set_pte_pde(काष्ठा amdgpu_device *adev, व्योम *cpu_pt_addr,
				uपूर्णांक32_t gpu_page_idx, uपूर्णांक64_t addr,
				uपूर्णांक64_t flags)
अणु
	व्योम __iomem *ptr = (व्योम *)cpu_pt_addr;
	uपूर्णांक64_t value;

	/*
	 * The following is क्रम PTE only. GART करोes not have PDEs.
	*/
	value = addr & 0x0000FFFFFFFFF000ULL;
	value |= flags;
	ग_लिखोq(value, ptr + (gpu_page_idx * 8));
	वापस 0;
पूर्ण

/**
 * amdgpu_gmc_agp_addr - वापस the address in the AGP address space
 *
 * @bo: TTM BO which needs the address, must be in GTT करोमुख्य
 *
 * Tries to figure out how to access the BO through the AGP aperture. Returns
 * AMDGPU_BO_INVALID_OFFSET अगर that is not possible.
 */
uपूर्णांक64_t amdgpu_gmc_agp_addr(काष्ठा tपंचांग_buffer_object *bo)
अणु
	काष्ठा amdgpu_device *adev = amdgpu_tपंचांग_adev(bo->bdev);

	अगर (bo->tपंचांग->num_pages != 1 || bo->tपंचांग->caching == tपंचांग_cached)
		वापस AMDGPU_BO_INVALID_OFFSET;

	अगर (bo->tपंचांग->dma_address[0] + PAGE_SIZE >= adev->gmc.agp_size)
		वापस AMDGPU_BO_INVALID_OFFSET;

	वापस adev->gmc.agp_start + bo->tपंचांग->dma_address[0];
पूर्ण

/**
 * amdgpu_gmc_vram_location - try to find VRAM location
 *
 * @adev: amdgpu device काष्ठाure holding all necessary inक्रमmation
 * @mc: memory controller काष्ठाure holding memory inक्रमmation
 * @base: base address at which to put VRAM
 *
 * Function will try to place VRAM at base address provided
 * as parameter.
 */
व्योम amdgpu_gmc_vram_location(काष्ठा amdgpu_device *adev, काष्ठा amdgpu_gmc *mc,
			      u64 base)
अणु
	uपूर्णांक64_t limit = (uपूर्णांक64_t)amdgpu_vram_limit << 20;

	mc->vram_start = base;
	mc->vram_end = mc->vram_start + mc->mc_vram_size - 1;
	अगर (limit && limit < mc->real_vram_size)
		mc->real_vram_size = limit;

	अगर (mc->xgmi.num_physical_nodes == 0) अणु
		mc->fb_start = mc->vram_start;
		mc->fb_end = mc->vram_end;
	पूर्ण
	dev_info(adev->dev, "VRAM: %lluM 0x%016llX - 0x%016llX (%lluM used)\n",
			mc->mc_vram_size >> 20, mc->vram_start,
			mc->vram_end, mc->real_vram_size >> 20);
पूर्ण

/** amdgpu_gmc_sysvm_location - place vram and gart in sysvm aperture
 *
 * @adev: amdgpu device काष्ठाure holding all necessary inक्रमmation
 * @mc: memory controller काष्ठाure holding memory inक्रमmation
 *
 * This function is only used अगर use GART क्रम FB translation. In such
 * हाल, we use sysvm aperture (vmid0 page tables) क्रम both vram
 * and gart (aka प्रणाली memory) access.
 *
 * GPUVM (and our organization of vmid0 page tables) require sysvm
 * aperture to be placed at a location aligned with 8 बार of native
 * page size. For example, अगर vm_context0_cntl.page_table_block_size
 * is 12, then native page size is 8G (2M*2^12), sysvm should start
 * with a 64G aligned address. For simplicity, we just put sysvm at
 * address 0. So vram start at address 0 and gart is right after vram.
 */
व्योम amdgpu_gmc_sysvm_location(काष्ठा amdgpu_device *adev, काष्ठा amdgpu_gmc *mc)
अणु
	u64 hive_vram_start = 0;
	u64 hive_vram_end = mc->xgmi.node_segment_size * mc->xgmi.num_physical_nodes - 1;
	mc->vram_start = mc->xgmi.node_segment_size * mc->xgmi.physical_node_id;
	mc->vram_end = mc->vram_start + mc->xgmi.node_segment_size - 1;
	mc->gart_start = hive_vram_end + 1;
	mc->gart_end = mc->gart_start + mc->gart_size - 1;
	mc->fb_start = hive_vram_start;
	mc->fb_end = hive_vram_end;
	dev_info(adev->dev, "VRAM: %lluM 0x%016llX - 0x%016llX (%lluM used)\n",
			mc->mc_vram_size >> 20, mc->vram_start,
			mc->vram_end, mc->real_vram_size >> 20);
	dev_info(adev->dev, "GART: %lluM 0x%016llX - 0x%016llX\n",
			mc->gart_size >> 20, mc->gart_start, mc->gart_end);
पूर्ण

/**
 * amdgpu_gmc_gart_location - try to find GART location
 *
 * @adev: amdgpu device काष्ठाure holding all necessary inक्रमmation
 * @mc: memory controller काष्ठाure holding memory inक्रमmation
 *
 * Function will place try to place GART beक्रमe or after VRAM.
 * If GART size is bigger than space left then we ajust GART size.
 * Thus function will never fails.
 */
व्योम amdgpu_gmc_gart_location(काष्ठा amdgpu_device *adev, काष्ठा amdgpu_gmc *mc)
अणु
	स्थिर uपूर्णांक64_t four_gb = 0x100000000ULL;
	u64 size_af, size_bf;
	/*To aव्योम the hole, limit the max mc address to AMDGPU_GMC_HOLE_START*/
	u64 max_mc_address = min(adev->gmc.mc_mask, AMDGPU_GMC_HOLE_START - 1);

	/* VCE करोesn't like it when BOs cross a 4GB segment, so align
	 * the GART base on a 4GB boundary as well.
	 */
	size_bf = mc->fb_start;
	size_af = max_mc_address + 1 - ALIGN(mc->fb_end + 1, four_gb);

	अगर (mc->gart_size > max(size_bf, size_af)) अणु
		dev_warn(adev->dev, "limiting GART\n");
		mc->gart_size = max(size_bf, size_af);
	पूर्ण

	अगर ((size_bf >= mc->gart_size && size_bf < size_af) ||
	    (size_af < mc->gart_size))
		mc->gart_start = 0;
	अन्यथा
		mc->gart_start = max_mc_address - mc->gart_size + 1;

	mc->gart_start &= ~(four_gb - 1);
	mc->gart_end = mc->gart_start + mc->gart_size - 1;
	dev_info(adev->dev, "GART: %lluM 0x%016llX - 0x%016llX\n",
			mc->gart_size >> 20, mc->gart_start, mc->gart_end);
पूर्ण

/**
 * amdgpu_gmc_agp_location - try to find AGP location
 * @adev: amdgpu device काष्ठाure holding all necessary inक्रमmation
 * @mc: memory controller काष्ठाure holding memory inक्रमmation
 *
 * Function will place try to find a place क्रम the AGP BAR in the MC address
 * space.
 *
 * AGP BAR will be asचिन्हित the largest available hole in the address space.
 * Should be called after VRAM and GART locations are setup.
 */
व्योम amdgpu_gmc_agp_location(काष्ठा amdgpu_device *adev, काष्ठा amdgpu_gmc *mc)
अणु
	स्थिर uपूर्णांक64_t sixteen_gb = 1ULL << 34;
	स्थिर uपूर्णांक64_t sixteen_gb_mask = ~(sixteen_gb - 1);
	u64 size_af, size_bf;

	अगर (amdgpu_sriov_vf(adev)) अणु
		mc->agp_start = 0xffffffffffff;
		mc->agp_end = 0x0;
		mc->agp_size = 0;

		वापस;
	पूर्ण

	अगर (mc->fb_start > mc->gart_start) अणु
		size_bf = (mc->fb_start & sixteen_gb_mask) -
			ALIGN(mc->gart_end + 1, sixteen_gb);
		size_af = mc->mc_mask + 1 - ALIGN(mc->fb_end + 1, sixteen_gb);
	पूर्ण अन्यथा अणु
		size_bf = mc->fb_start & sixteen_gb_mask;
		size_af = (mc->gart_start & sixteen_gb_mask) -
			ALIGN(mc->fb_end + 1, sixteen_gb);
	पूर्ण

	अगर (size_bf > size_af) अणु
		mc->agp_start = (mc->fb_start - size_bf) & sixteen_gb_mask;
		mc->agp_size = size_bf;
	पूर्ण अन्यथा अणु
		mc->agp_start = ALIGN(mc->fb_end + 1, sixteen_gb);
		mc->agp_size = size_af;
	पूर्ण

	mc->agp_end = mc->agp_start + mc->agp_size - 1;
	dev_info(adev->dev, "AGP: %lluM 0x%016llX - 0x%016llX\n",
			mc->agp_size >> 20, mc->agp_start, mc->agp_end);
पूर्ण

/**
 * amdgpu_gmc_filter_faults - filter VM faults
 *
 * @adev: amdgpu device काष्ठाure
 * @addr: address of the VM fault
 * @pasid: PASID of the process causing the fault
 * @बारtamp: बारtamp of the fault
 *
 * Returns:
 * True अगर the fault was filtered and should not be processed further.
 * False अगर the fault is a new one and needs to be handled.
 */
bool amdgpu_gmc_filter_faults(काष्ठा amdgpu_device *adev, uपूर्णांक64_t addr,
			      uपूर्णांक16_t pasid, uपूर्णांक64_t बारtamp)
अणु
	काष्ठा amdgpu_gmc *gmc = &adev->gmc;

	uपूर्णांक64_t stamp, key = addr << 4 | pasid;
	काष्ठा amdgpu_gmc_fault *fault;
	uपूर्णांक32_t hash;

	/* If we करोn't have space left in the ring buffer वापस immediately */
	stamp = max(बारtamp, AMDGPU_GMC_FAULT_TIMEOUT + 1) -
		AMDGPU_GMC_FAULT_TIMEOUT;
	अगर (gmc->fault_ring[gmc->last_fault].बारtamp >= stamp)
		वापस true;

	/* Try to find the fault in the hash */
	hash = hash_64(key, AMDGPU_GMC_FAULT_HASH_ORDER);
	fault = &gmc->fault_ring[gmc->fault_hash[hash].idx];
	जबतक (fault->बारtamp >= stamp) अणु
		uपूर्णांक64_t पंचांगp;

		अगर (fault->key == key)
			वापस true;

		पंचांगp = fault->बारtamp;
		fault = &gmc->fault_ring[fault->next];

		/* Check अगर the entry was reused */
		अगर (fault->बारtamp >= पंचांगp)
			अवरोध;
	पूर्ण

	/* Add the fault to the ring */
	fault = &gmc->fault_ring[gmc->last_fault];
	fault->key = key;
	fault->बारtamp = बारtamp;

	/* And update the hash */
	fault->next = gmc->fault_hash[hash].idx;
	gmc->fault_hash[hash].idx = gmc->last_fault++;
	वापस false;
पूर्ण

पूर्णांक amdgpu_gmc_ras_late_init(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक r;

	अगर (adev->umc.ras_funcs &&
	    adev->umc.ras_funcs->ras_late_init) अणु
		r = adev->umc.ras_funcs->ras_late_init(adev);
		अगर (r)
			वापस r;
	पूर्ण

	अगर (adev->mmhub.ras_funcs &&
	    adev->mmhub.ras_funcs->ras_late_init) अणु
		r = adev->mmhub.ras_funcs->ras_late_init(adev);
		अगर (r)
			वापस r;
	पूर्ण

	अगर (!adev->gmc.xgmi.connected_to_cpu)
		adev->gmc.xgmi.ras_funcs = &xgmi_ras_funcs;

	अगर (adev->gmc.xgmi.ras_funcs &&
	    adev->gmc.xgmi.ras_funcs->ras_late_init) अणु
		r = adev->gmc.xgmi.ras_funcs->ras_late_init(adev);
		अगर (r)
			वापस r;
	पूर्ण

	वापस 0;
पूर्ण

व्योम amdgpu_gmc_ras_fini(काष्ठा amdgpu_device *adev)
अणु
	अगर (adev->umc.ras_funcs &&
	    adev->umc.ras_funcs->ras_fini)
		adev->umc.ras_funcs->ras_fini(adev);

	अगर (adev->mmhub.ras_funcs &&
	    adev->mmhub.ras_funcs->ras_fini)
		amdgpu_mmhub_ras_fini(adev);

	अगर (adev->gmc.xgmi.ras_funcs &&
	    adev->gmc.xgmi.ras_funcs->ras_fini)
		adev->gmc.xgmi.ras_funcs->ras_fini(adev);
पूर्ण

	/*
	 * The latest engine allocation on gfx9/10 is:
	 * Engine 2, 3: firmware
	 * Engine 0, 1, 4~16: amdgpu ring,
	 *                    subject to change when ring number changes
	 * Engine 17: Gart flushes
	 */
#घोषणा GFXHUB_FREE_VM_INV_ENGS_BITMAP		0x1FFF3
#घोषणा MMHUB_FREE_VM_INV_ENGS_BITMAP		0x1FFF3

पूर्णांक amdgpu_gmc_allocate_vm_inv_eng(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_ring *ring;
	अचिन्हित vm_inv_engs[AMDGPU_MAX_VMHUBS] =
		अणुGFXHUB_FREE_VM_INV_ENGS_BITMAP, MMHUB_FREE_VM_INV_ENGS_BITMAP,
		GFXHUB_FREE_VM_INV_ENGS_BITMAPपूर्ण;
	अचिन्हित i;
	अचिन्हित vmhub, inv_eng;

	क्रम (i = 0; i < adev->num_rings; ++i) अणु
		ring = adev->rings[i];
		vmhub = ring->funcs->vmhub;

		अगर (ring == &adev->mes.ring)
			जारी;

		inv_eng = ffs(vm_inv_engs[vmhub]);
		अगर (!inv_eng) अणु
			dev_err(adev->dev, "no VM inv eng for ring %s\n",
				ring->name);
			वापस -EINVAL;
		पूर्ण

		ring->vm_inv_eng = inv_eng - 1;
		vm_inv_engs[vmhub] &= ~(1 << ring->vm_inv_eng);

		dev_info(adev->dev, "ring %s uses VM inv eng %u on hub %u\n",
			 ring->name, ring->vm_inv_eng, ring->funcs->vmhub);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * amdgpu_पंचांगz_set -- check and set अगर a device supports TMZ
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Check and set अगर an the device @adev supports Trusted Memory
 * Zones (TMZ).
 */
व्योम amdgpu_gmc_पंचांगz_set(काष्ठा amdgpu_device *adev)
अणु
	चयन (adev->asic_type) अणु
	हाल CHIP_RAVEN:
	हाल CHIP_RENOIR:
		अगर (amdgpu_पंचांगz == 0) अणु
			adev->gmc.पंचांगz_enabled = false;
			dev_info(adev->dev,
				 "Trusted Memory Zone (TMZ) feature disabled (cmd line)\n");
		पूर्ण अन्यथा अणु
			adev->gmc.पंचांगz_enabled = true;
			dev_info(adev->dev,
				 "Trusted Memory Zone (TMZ) feature enabled\n");
		पूर्ण
		अवरोध;
	हाल CHIP_NAVI10:
	हाल CHIP_NAVI14:
	हाल CHIP_NAVI12:
	हाल CHIP_VANGOGH:
		/* Don't enable it by शेष yet.
		 */
		अगर (amdgpu_पंचांगz < 1) अणु
			adev->gmc.पंचांगz_enabled = false;
			dev_info(adev->dev,
				 "Trusted Memory Zone (TMZ) feature disabled as experimental (default)\n");
		पूर्ण अन्यथा अणु
			adev->gmc.पंचांगz_enabled = true;
			dev_info(adev->dev,
				 "Trusted Memory Zone (TMZ) feature enabled as experimental (cmd line)\n");
		पूर्ण
		अवरोध;
	शेष:
		adev->gmc.पंचांगz_enabled = false;
		dev_warn(adev->dev,
			 "Trusted Memory Zone (TMZ) feature not supported\n");
		अवरोध;
	पूर्ण
पूर्ण

/**
 * amdgpu_noretry_set -- set per asic noretry शेषs
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Set a per asic शेष क्रम the no-retry parameter.
 *
 */
व्योम amdgpu_gmc_noretry_set(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_gmc *gmc = &adev->gmc;

	चयन (adev->asic_type) अणु
	हाल CHIP_VEGA10:
	हाल CHIP_VEGA20:
	हाल CHIP_ARCTURUS:
	हाल CHIP_ALDEBARAN:
		/*
		 * noretry = 0 will cause kfd page fault tests fail
		 * क्रम some ASICs, so set शेष to 1 क्रम these ASICs.
		 */
		अगर (amdgpu_noretry == -1)
			gmc->noretry = 1;
		अन्यथा
			gmc->noretry = amdgpu_noretry;
		अवरोध;
	हाल CHIP_RAVEN:
	शेष:
		/* Raven currently has issues with noretry
		 * regardless of what we decide क्रम other
		 * asics, we should leave raven with
		 * noretry = 0 until we root cause the
		 * issues.
		 *
		 * शेष this to 0 क्रम now, but we may want
		 * to change this in the future क्रम certain
		 * GPUs as it can increase perक्रमmance in
		 * certain हालs.
		 */
		अगर (amdgpu_noretry == -1)
			gmc->noretry = 0;
		अन्यथा
			gmc->noretry = amdgpu_noretry;
		अवरोध;
	पूर्ण
पूर्ण

व्योम amdgpu_gmc_set_vm_fault_masks(काष्ठा amdgpu_device *adev, पूर्णांक hub_type,
				   bool enable)
अणु
	काष्ठा amdgpu_vmhub *hub;
	u32 पंचांगp, reg, i;

	hub = &adev->vmhub[hub_type];
	क्रम (i = 0; i < 16; i++) अणु
		reg = hub->vm_context0_cntl + hub->ctx_distance * i;

		पंचांगp = RREG32(reg);
		अगर (enable)
			पंचांगp |= hub->vm_cntx_cntl_vm_fault;
		अन्यथा
			पंचांगp &= ~hub->vm_cntx_cntl_vm_fault;

		WREG32(reg, पंचांगp);
	पूर्ण
पूर्ण

व्योम amdgpu_gmc_get_vbios_allocations(काष्ठा amdgpu_device *adev)
अणु
	अचिन्हित size;

	/*
	 * TODO:
	 * Currently there is a bug where some memory client outside
	 * of the driver ग_लिखोs to first 8M of VRAM on S3 resume,
	 * this overrides GART which by शेष माला_लो placed in first 8M and
	 * causes VM_FAULTS once GTT is accessed.
	 * Keep the stolen memory reservation until the जबतक this is not solved.
	 */
	चयन (adev->asic_type) अणु
	हाल CHIP_VEGA10:
	हाल CHIP_RAVEN:
	हाल CHIP_RENOIR:
		adev->mman.keep_stolen_vga_memory = true;
		अवरोध;
	शेष:
		adev->mman.keep_stolen_vga_memory = false;
		अवरोध;
	पूर्ण

	अगर (amdgpu_sriov_vf(adev) ||
	    !amdgpu_device_ip_get_ip_block(adev, AMD_IP_BLOCK_TYPE_DCE)) अणु
		size = 0;
	पूर्ण अन्यथा अणु
		size = amdgpu_gmc_get_vbios_fb_size(adev);

		अगर (adev->mman.keep_stolen_vga_memory)
			size = max(size, (अचिन्हित)AMDGPU_VBIOS_VGA_ALLOCATION);
	पूर्ण

	/* set to 0 अगर the pre-OS buffer uses up most of vram */
	अगर ((adev->gmc.real_vram_size - size) < (8 * 1024 * 1024))
		size = 0;

	अगर (size > AMDGPU_VBIOS_VGA_ALLOCATION) अणु
		adev->mman.stolen_vga_size = AMDGPU_VBIOS_VGA_ALLOCATION;
		adev->mman.stolen_extended_size = size - adev->mman.stolen_vga_size;
	पूर्ण अन्यथा अणु
		adev->mman.stolen_vga_size = size;
		adev->mman.stolen_extended_size = 0;
	पूर्ण
पूर्ण

/**
 * amdgpu_gmc_init_pdb0 - initialize PDB0
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * This function is only used when GART page table is used
 * क्रम FB address translatioin. In such a हाल, we स्थिरruct
 * a 2-level प्रणाली VM page table: PDB0->PTB, to cover both
 * VRAM of the hive and प्रणाली memory.
 *
 * PDB0 is अटल, initialized once on driver initialization.
 * The first n entries of PDB0 are used as PTE by setting
 * P bit to 1, poपूर्णांकing to VRAM. The n+1'th entry poपूर्णांकs
 * to a big PTB covering प्रणाली memory.
 *
 */
व्योम amdgpu_gmc_init_pdb0(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i;
	uपूर्णांक64_t flags = adev->gart.gart_pte_flags; //TODO it is UC. explore NC/RW?
	/* Each PDE0 (used as PTE) covers (2^vmid0_page_table_block_size)*2M
	 */
	u64 vram_size = adev->gmc.xgmi.node_segment_size * adev->gmc.xgmi.num_physical_nodes;
	u64 pde0_page_size = (1ULL<<adev->gmc.vmid0_page_table_block_size)<<21;
	u64 vram_addr = adev->vm_manager.vram_base_offset -
		adev->gmc.xgmi.physical_node_id * adev->gmc.xgmi.node_segment_size;
	u64 vram_end = vram_addr + vram_size;
	u64 gart_ptb_gpu_pa = amdgpu_gmc_vram_pa(adev, adev->gart.bo);

	flags |= AMDGPU_PTE_VALID | AMDGPU_PTE_READABLE;
	flags |= AMDGPU_PTE_WRITEABLE;
	flags |= AMDGPU_PTE_SNOOPED;
	flags |= AMDGPU_PTE_FRAG((adev->gmc.vmid0_page_table_block_size + 9*1));
	flags |= AMDGPU_PDE_PTE;

	/* The first n PDE0 entries are used as PTE,
	 * poपूर्णांकing to vram
	 */
	क्रम (i = 0; vram_addr < vram_end; i++, vram_addr += pde0_page_size)
		amdgpu_gmc_set_pte_pde(adev, adev->gmc.ptr_pdb0, i, vram_addr, flags);

	/* The n+1'th PDE0 entry poपूर्णांकs to a huge
	 * PTB who has more than 512 entries each
	 * poपूर्णांकing to a 4K प्रणाली page
	 */
	flags = AMDGPU_PTE_VALID;
	flags |= AMDGPU_PDE_BFS(0) | AMDGPU_PTE_SNOOPED;
	/* Requires gart_ptb_gpu_pa to be 4K aligned */
	amdgpu_gmc_set_pte_pde(adev, adev->gmc.ptr_pdb0, i, gart_ptb_gpu_pa, flags);
पूर्ण

/**
 * amdgpu_gmc_vram_mc2pa - calculate vram buffer's physical address from MC
 * address
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @mc_addr: MC address of buffer
 */
uपूर्णांक64_t amdgpu_gmc_vram_mc2pa(काष्ठा amdgpu_device *adev, uपूर्णांक64_t mc_addr)
अणु
	वापस mc_addr - adev->gmc.vram_start + adev->vm_manager.vram_base_offset;
पूर्ण

/**
 * amdgpu_gmc_vram_pa - calculate vram buffer object's physical address from
 * GPU's view
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @bo: amdgpu buffer object
 */
uपूर्णांक64_t amdgpu_gmc_vram_pa(काष्ठा amdgpu_device *adev, काष्ठा amdgpu_bo *bo)
अणु
	वापस amdgpu_gmc_vram_mc2pa(adev, amdgpu_bo_gpu_offset(bo));
पूर्ण

/**
 * amdgpu_gmc_vram_cpu_pa - calculate vram buffer object's physical address
 * from CPU's view
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @bo: amdgpu buffer object
 */
uपूर्णांक64_t amdgpu_gmc_vram_cpu_pa(काष्ठा amdgpu_device *adev, काष्ठा amdgpu_bo *bo)
अणु
	वापस amdgpu_bo_gpu_offset(bo) - adev->gmc.vram_start + adev->gmc.aper_base;
पूर्ण
