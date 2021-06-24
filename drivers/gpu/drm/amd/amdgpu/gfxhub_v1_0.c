<शैली गुरु>
/*
 * Copyright 2016 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */
#समावेश "amdgpu.h"
#समावेश "gfxhub_v1_0.h"
#समावेश "gfxhub_v1_1.h"

#समावेश "gc/gc_9_0_offset.h"
#समावेश "gc/gc_9_0_sh_mask.h"
#समावेश "gc/gc_9_0_default.h"
#समावेश "vega10_enum.h"

#समावेश "soc15_common.h"

अटल u64 gfxhub_v1_0_get_mc_fb_offset(काष्ठा amdgpu_device *adev)
अणु
	वापस (u64)RREG32_SOC15(GC, 0, mmMC_VM_FB_OFFSET) << 24;
पूर्ण

अटल व्योम gfxhub_v1_0_setup_vm_pt_regs(काष्ठा amdgpu_device *adev,
					 uपूर्णांक32_t vmid,
					 uपूर्णांक64_t page_table_base)
अणु
	काष्ठा amdgpu_vmhub *hub = &adev->vmhub[AMDGPU_GFXHUB_0];

	WREG32_SOC15_OFFSET(GC, 0, mmVM_CONTEXT0_PAGE_TABLE_BASE_ADDR_LO32,
			    hub->ctx_addr_distance * vmid,
			    lower_32_bits(page_table_base));

	WREG32_SOC15_OFFSET(GC, 0, mmVM_CONTEXT0_PAGE_TABLE_BASE_ADDR_HI32,
			    hub->ctx_addr_distance * vmid,
			    upper_32_bits(page_table_base));
पूर्ण

अटल व्योम gfxhub_v1_0_init_gart_aperture_regs(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक64_t pt_base;

	अगर (adev->gmc.pdb0_bo)
		pt_base = amdgpu_gmc_pd_addr(adev->gmc.pdb0_bo);
	अन्यथा
		pt_base = amdgpu_gmc_pd_addr(adev->gart.bo);

	gfxhub_v1_0_setup_vm_pt_regs(adev, 0, pt_base);

	/* If use GART क्रम FB translation, vmid0 page table covers both
	 * vram and प्रणाली memory (gart)
	 */
	अगर (adev->gmc.pdb0_bo) अणु
		WREG32_SOC15(GC, 0, mmVM_CONTEXT0_PAGE_TABLE_START_ADDR_LO32,
				(u32)(adev->gmc.fb_start >> 12));
		WREG32_SOC15(GC, 0, mmVM_CONTEXT0_PAGE_TABLE_START_ADDR_HI32,
				(u32)(adev->gmc.fb_start >> 44));

		WREG32_SOC15(GC, 0, mmVM_CONTEXT0_PAGE_TABLE_END_ADDR_LO32,
				(u32)(adev->gmc.gart_end >> 12));
		WREG32_SOC15(GC, 0, mmVM_CONTEXT0_PAGE_TABLE_END_ADDR_HI32,
				(u32)(adev->gmc.gart_end >> 44));
	पूर्ण अन्यथा अणु
		WREG32_SOC15(GC, 0, mmVM_CONTEXT0_PAGE_TABLE_START_ADDR_LO32,
				(u32)(adev->gmc.gart_start >> 12));
		WREG32_SOC15(GC, 0, mmVM_CONTEXT0_PAGE_TABLE_START_ADDR_HI32,
				(u32)(adev->gmc.gart_start >> 44));

		WREG32_SOC15(GC, 0, mmVM_CONTEXT0_PAGE_TABLE_END_ADDR_LO32,
				(u32)(adev->gmc.gart_end >> 12));
		WREG32_SOC15(GC, 0, mmVM_CONTEXT0_PAGE_TABLE_END_ADDR_HI32,
				(u32)(adev->gmc.gart_end >> 44));
	पूर्ण
पूर्ण

अटल व्योम gfxhub_v1_0_init_प्रणाली_aperture_regs(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक64_t value;

	/* Program the AGP BAR */
	WREG32_SOC15_RLC(GC, 0, mmMC_VM_AGP_BASE, 0);
	WREG32_SOC15_RLC(GC, 0, mmMC_VM_AGP_BOT, adev->gmc.agp_start >> 24);
	WREG32_SOC15_RLC(GC, 0, mmMC_VM_AGP_TOP, adev->gmc.agp_end >> 24);

	अगर (!amdgpu_sriov_vf(adev) || adev->asic_type <= CHIP_VEGA10) अणु
		/* Program the प्रणाली aperture low logical page number. */
		WREG32_SOC15_RLC(GC, 0, mmMC_VM_SYSTEM_APERTURE_LOW_ADDR,
			min(adev->gmc.fb_start, adev->gmc.agp_start) >> 18);

		अगर (adev->apu_flags & AMD_APU_IS_RAVEN2)
			/*
			* Raven2 has a HW issue that it is unable to use the
			* vram which is out of MC_VM_SYSTEM_APERTURE_HIGH_ADDR.
			* So here is the workaround that increase प्रणाली
			* aperture high address (add 1) to get rid of the VM
			* fault and hardware hang.
			*/
			WREG32_SOC15_RLC(GC, 0,
					 mmMC_VM_SYSTEM_APERTURE_HIGH_ADDR,
					 max((adev->gmc.fb_end >> 18) + 0x1,
					     adev->gmc.agp_end >> 18));
		अन्यथा
			WREG32_SOC15_RLC(
				GC, 0, mmMC_VM_SYSTEM_APERTURE_HIGH_ADDR,
				max(adev->gmc.fb_end, adev->gmc.agp_end) >> 18);

		/* Set शेष page address. */
		value = amdgpu_gmc_vram_mc2pa(adev, adev->vram_scratch.gpu_addr);
		WREG32_SOC15(GC, 0, mmMC_VM_SYSTEM_APERTURE_DEFAULT_ADDR_LSB,
			     (u32)(value >> 12));
		WREG32_SOC15(GC, 0, mmMC_VM_SYSTEM_APERTURE_DEFAULT_ADDR_MSB,
			     (u32)(value >> 44));

		/* Program "protection fault". */
		WREG32_SOC15(GC, 0, mmVM_L2_PROTECTION_FAULT_DEFAULT_ADDR_LO32,
			     (u32)(adev->dummy_page_addr >> 12));
		WREG32_SOC15(GC, 0, mmVM_L2_PROTECTION_FAULT_DEFAULT_ADDR_HI32,
			     (u32)((u64)adev->dummy_page_addr >> 44));

		WREG32_FIELD15(GC, 0, VM_L2_PROTECTION_FAULT_CNTL2,
			       ACTIVE_PAGE_MIGRATION_PTE_READ_RETRY, 1);
	पूर्ण

	/* In the हाल squeezing vram पूर्णांकo GART aperture, we करोn't use
	 * FB aperture and AGP aperture. Disable them.
	 */
	अगर (adev->gmc.pdb0_bo) अणु
		WREG32_SOC15(GC, 0, mmMC_VM_FB_LOCATION_TOP, 0);
		WREG32_SOC15(GC, 0, mmMC_VM_FB_LOCATION_BASE, 0x00FFFFFF);
		WREG32_SOC15(GC, 0, mmMC_VM_AGP_TOP, 0);
		WREG32_SOC15(GC, 0, mmMC_VM_AGP_BOT, 0xFFFFFF);
		WREG32_SOC15(GC, 0, mmMC_VM_SYSTEM_APERTURE_LOW_ADDR, 0x3FFFFFFF);
		WREG32_SOC15(GC, 0, mmMC_VM_SYSTEM_APERTURE_HIGH_ADDR, 0);
	पूर्ण
पूर्ण

अटल व्योम gfxhub_v1_0_init_tlb_regs(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक32_t पंचांगp;

	/* Setup TLB control */
	पंचांगp = RREG32_SOC15(GC, 0, mmMC_VM_MX_L1_TLB_CNTL);

	पंचांगp = REG_SET_FIELD(पंचांगp, MC_VM_MX_L1_TLB_CNTL, ENABLE_L1_TLB, 1);
	पंचांगp = REG_SET_FIELD(पंचांगp, MC_VM_MX_L1_TLB_CNTL, SYSTEM_ACCESS_MODE, 3);
	पंचांगp = REG_SET_FIELD(पंचांगp, MC_VM_MX_L1_TLB_CNTL,
			    ENABLE_ADVANCED_DRIVER_MODEL, 1);
	पंचांगp = REG_SET_FIELD(पंचांगp, MC_VM_MX_L1_TLB_CNTL,
			    SYSTEM_APERTURE_UNMAPPED_ACCESS, 0);
	पंचांगp = REG_SET_FIELD(पंचांगp, MC_VM_MX_L1_TLB_CNTL, ECO_BITS, 0);
	पंचांगp = REG_SET_FIELD(पंचांगp, MC_VM_MX_L1_TLB_CNTL,
			    MTYPE, MTYPE_UC);/* XXX क्रम emulation. */
	पंचांगp = REG_SET_FIELD(पंचांगp, MC_VM_MX_L1_TLB_CNTL, ATC_EN, 1);

	WREG32_SOC15_RLC(GC, 0, mmMC_VM_MX_L1_TLB_CNTL, पंचांगp);
पूर्ण

अटल व्योम gfxhub_v1_0_init_cache_regs(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक32_t पंचांगp;

	/* Setup L2 cache */
	पंचांगp = RREG32_SOC15(GC, 0, mmVM_L2_CNTL);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_L2_CNTL, ENABLE_L2_CACHE, 1);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_L2_CNTL, ENABLE_L2_FRAGMENT_PROCESSING, 1);
	/* XXX क्रम emulation, Refer to बंदd source code.*/
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_L2_CNTL, L2_PDE0_CACHE_TAG_GENERATION_MODE,
			    0);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_L2_CNTL, PDE_FAULT_CLASSIFICATION, 0);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_L2_CNTL, CONTEXT1_IDENTITY_ACCESS_MODE, 1);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_L2_CNTL, IDENTITY_MODE_FRAGMENT_SIZE, 0);
	WREG32_SOC15_RLC(GC, 0, mmVM_L2_CNTL, पंचांगp);

	पंचांगp = RREG32_SOC15(GC, 0, mmVM_L2_CNTL2);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_L2_CNTL2, INVALIDATE_ALL_L1_TLBS, 1);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_L2_CNTL2, INVALIDATE_L2_CACHE, 1);
	WREG32_SOC15_RLC(GC, 0, mmVM_L2_CNTL2, पंचांगp);

	पंचांगp = mmVM_L2_CNTL3_DEFAULT;
	अगर (adev->gmc.translate_further) अणु
		पंचांगp = REG_SET_FIELD(पंचांगp, VM_L2_CNTL3, BANK_SELECT, 12);
		पंचांगp = REG_SET_FIELD(पंचांगp, VM_L2_CNTL3,
				    L2_CACHE_BIGK_FRAGMENT_SIZE, 9);
	पूर्ण अन्यथा अणु
		पंचांगp = REG_SET_FIELD(पंचांगp, VM_L2_CNTL3, BANK_SELECT, 9);
		पंचांगp = REG_SET_FIELD(पंचांगp, VM_L2_CNTL3,
				    L2_CACHE_BIGK_FRAGMENT_SIZE, 6);
	पूर्ण
	WREG32_SOC15_RLC(GC, 0, mmVM_L2_CNTL3, पंचांगp);

	पंचांगp = mmVM_L2_CNTL4_DEFAULT;
	अगर (adev->gmc.xgmi.connected_to_cpu) अणु
		पंचांगp = REG_SET_FIELD(पंचांगp, VM_L2_CNTL4, VMC_TAP_PDE_REQUEST_PHYSICAL, 1);
		पंचांगp = REG_SET_FIELD(पंचांगp, VM_L2_CNTL4, VMC_TAP_PTE_REQUEST_PHYSICAL, 1);
	पूर्ण अन्यथा अणु
		पंचांगp = REG_SET_FIELD(पंचांगp, VM_L2_CNTL4, VMC_TAP_PDE_REQUEST_PHYSICAL, 0);
		पंचांगp = REG_SET_FIELD(पंचांगp, VM_L2_CNTL4, VMC_TAP_PTE_REQUEST_PHYSICAL, 0);
	पूर्ण
	WREG32_SOC15_RLC(GC, 0, mmVM_L2_CNTL4, पंचांगp);
पूर्ण

अटल व्योम gfxhub_v1_0_enable_प्रणाली_करोमुख्य(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक32_t पंचांगp;

	पंचांगp = RREG32_SOC15(GC, 0, mmVM_CONTEXT0_CNTL);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_CONTEXT0_CNTL, ENABLE_CONTEXT, 1);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_CONTEXT0_CNTL, PAGE_TABLE_DEPTH,
			adev->gmc.vmid0_page_table_depth);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_CONTEXT0_CNTL, PAGE_TABLE_BLOCK_SIZE,
			adev->gmc.vmid0_page_table_block_size);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_CONTEXT0_CNTL,
			    RETRY_PERMISSION_OR_INVALID_PAGE_FAULT, 0);
	WREG32_SOC15(GC, 0, mmVM_CONTEXT0_CNTL, पंचांगp);
पूर्ण

अटल व्योम gfxhub_v1_0_disable_identity_aperture(काष्ठा amdgpu_device *adev)
अणु
	WREG32_SOC15(GC, 0, mmVM_L2_CONTEXT1_IDENTITY_APERTURE_LOW_ADDR_LO32,
		     0XFFFFFFFF);
	WREG32_SOC15(GC, 0, mmVM_L2_CONTEXT1_IDENTITY_APERTURE_LOW_ADDR_HI32,
		     0x0000000F);

	WREG32_SOC15(GC, 0, mmVM_L2_CONTEXT1_IDENTITY_APERTURE_HIGH_ADDR_LO32,
		     0);
	WREG32_SOC15(GC, 0, mmVM_L2_CONTEXT1_IDENTITY_APERTURE_HIGH_ADDR_HI32,
		     0);

	WREG32_SOC15(GC, 0, mmVM_L2_CONTEXT_IDENTITY_PHYSICAL_OFFSET_LO32, 0);
	WREG32_SOC15(GC, 0, mmVM_L2_CONTEXT_IDENTITY_PHYSICAL_OFFSET_HI32, 0);

पूर्ण

अटल व्योम gfxhub_v1_0_setup_vmid_config(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_vmhub *hub = &adev->vmhub[AMDGPU_GFXHUB_0];
	अचिन्हित num_level, block_size;
	uपूर्णांक32_t पंचांगp;
	पूर्णांक i;

	num_level = adev->vm_manager.num_level;
	block_size = adev->vm_manager.block_size;
	अगर (adev->gmc.translate_further)
		num_level -= 1;
	अन्यथा
		block_size -= 9;

	क्रम (i = 0; i <= 14; i++) अणु
		पंचांगp = RREG32_SOC15_OFFSET(GC, 0, mmVM_CONTEXT1_CNTL, i);
		पंचांगp = REG_SET_FIELD(पंचांगp, VM_CONTEXT1_CNTL, ENABLE_CONTEXT, 1);
		पंचांगp = REG_SET_FIELD(पंचांगp, VM_CONTEXT1_CNTL, PAGE_TABLE_DEPTH,
				    num_level);
		पंचांगp = REG_SET_FIELD(पंचांगp, VM_CONTEXT1_CNTL,
				    RANGE_PROTECTION_FAULT_ENABLE_DEFAULT, 1);
		पंचांगp = REG_SET_FIELD(पंचांगp, VM_CONTEXT1_CNTL,
				    DUMMY_PAGE_PROTECTION_FAULT_ENABLE_DEFAULT,
				    1);
		पंचांगp = REG_SET_FIELD(पंचांगp, VM_CONTEXT1_CNTL,
				    PDE0_PROTECTION_FAULT_ENABLE_DEFAULT, 1);
		पंचांगp = REG_SET_FIELD(पंचांगp, VM_CONTEXT1_CNTL,
				    VALID_PROTECTION_FAULT_ENABLE_DEFAULT, 1);
		पंचांगp = REG_SET_FIELD(पंचांगp, VM_CONTEXT1_CNTL,
				    READ_PROTECTION_FAULT_ENABLE_DEFAULT, 1);
		पंचांगp = REG_SET_FIELD(पंचांगp, VM_CONTEXT1_CNTL,
				    WRITE_PROTECTION_FAULT_ENABLE_DEFAULT, 1);
		पंचांगp = REG_SET_FIELD(पंचांगp, VM_CONTEXT1_CNTL,
				    EXECUTE_PROTECTION_FAULT_ENABLE_DEFAULT, 1);
		पंचांगp = REG_SET_FIELD(पंचांगp, VM_CONTEXT1_CNTL,
				    PAGE_TABLE_BLOCK_SIZE,
				    block_size);
		/* Send no-retry XNACK on fault to suppress VM fault storm. */
		पंचांगp = REG_SET_FIELD(पंचांगp, VM_CONTEXT1_CNTL,
				    RETRY_PERMISSION_OR_INVALID_PAGE_FAULT,
				    !adev->gmc.noretry);
		WREG32_SOC15_OFFSET(GC, 0, mmVM_CONTEXT1_CNTL,
				    i * hub->ctx_distance, पंचांगp);
		WREG32_SOC15_OFFSET(GC, 0, mmVM_CONTEXT1_PAGE_TABLE_START_ADDR_LO32,
				    i * hub->ctx_addr_distance, 0);
		WREG32_SOC15_OFFSET(GC, 0, mmVM_CONTEXT1_PAGE_TABLE_START_ADDR_HI32,
				    i * hub->ctx_addr_distance, 0);
		WREG32_SOC15_OFFSET(GC, 0, mmVM_CONTEXT1_PAGE_TABLE_END_ADDR_LO32,
				    i * hub->ctx_addr_distance,
				    lower_32_bits(adev->vm_manager.max_pfn - 1));
		WREG32_SOC15_OFFSET(GC, 0, mmVM_CONTEXT1_PAGE_TABLE_END_ADDR_HI32,
				    i * hub->ctx_addr_distance,
				    upper_32_bits(adev->vm_manager.max_pfn - 1));
	पूर्ण
पूर्ण

अटल व्योम gfxhub_v1_0_program_invalidation(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_vmhub *hub = &adev->vmhub[AMDGPU_GFXHUB_0];
	अचिन्हित i;

	क्रम (i = 0 ; i < 18; ++i) अणु
		WREG32_SOC15_OFFSET(GC, 0, mmVM_INVALIDATE_ENG0_ADDR_RANGE_LO32,
				    i * hub->eng_addr_distance, 0xffffffff);
		WREG32_SOC15_OFFSET(GC, 0, mmVM_INVALIDATE_ENG0_ADDR_RANGE_HI32,
				    i * hub->eng_addr_distance, 0x1f);
	पूर्ण
पूर्ण

अटल पूर्णांक gfxhub_v1_0_gart_enable(काष्ठा amdgpu_device *adev)
अणु
	अगर (amdgpu_sriov_vf(adev) && adev->asic_type != CHIP_ARCTURUS) अणु
		/*
		 * MC_VM_FB_LOCATION_BASE/TOP is शून्य क्रम VF, becuase they are
		 * VF copy रेजिस्टरs so vbios post करोesn't program them, क्रम
		 * SRIOV driver need to program them
		 */
		WREG32_SOC15_RLC(GC, 0, mmMC_VM_FB_LOCATION_BASE,
			     adev->gmc.vram_start >> 24);
		WREG32_SOC15_RLC(GC, 0, mmMC_VM_FB_LOCATION_TOP,
			     adev->gmc.vram_end >> 24);
	पूर्ण

	/* GART Enable. */
	gfxhub_v1_0_init_gart_aperture_regs(adev);
	gfxhub_v1_0_init_प्रणाली_aperture_regs(adev);
	gfxhub_v1_0_init_tlb_regs(adev);
	अगर (!amdgpu_sriov_vf(adev))
		gfxhub_v1_0_init_cache_regs(adev);

	gfxhub_v1_0_enable_प्रणाली_करोमुख्य(adev);
	अगर (!amdgpu_sriov_vf(adev))
		gfxhub_v1_0_disable_identity_aperture(adev);
	gfxhub_v1_0_setup_vmid_config(adev);
	gfxhub_v1_0_program_invalidation(adev);

	वापस 0;
पूर्ण

अटल व्योम gfxhub_v1_0_gart_disable(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_vmhub *hub = &adev->vmhub[AMDGPU_GFXHUB_0];
	u32 पंचांगp;
	u32 i;

	/* Disable all tables */
	क्रम (i = 0; i < 16; i++)
		WREG32_SOC15_OFFSET(GC, 0, mmVM_CONTEXT0_CNTL,
				    i * hub->ctx_distance, 0);

	/* Setup TLB control */
	पंचांगp = RREG32_SOC15(GC, 0, mmMC_VM_MX_L1_TLB_CNTL);
	पंचांगp = REG_SET_FIELD(पंचांगp, MC_VM_MX_L1_TLB_CNTL, ENABLE_L1_TLB, 0);
	पंचांगp = REG_SET_FIELD(पंचांगp,
				MC_VM_MX_L1_TLB_CNTL,
				ENABLE_ADVANCED_DRIVER_MODEL,
				0);
	WREG32_SOC15_RLC(GC, 0, mmMC_VM_MX_L1_TLB_CNTL, पंचांगp);

	/* Setup L2 cache */
	WREG32_FIELD15(GC, 0, VM_L2_CNTL, ENABLE_L2_CACHE, 0);
	WREG32_SOC15(GC, 0, mmVM_L2_CNTL3, 0);
पूर्ण

/**
 * gfxhub_v1_0_set_fault_enable_शेष - update GART/VM fault handling
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @value: true redirects VM faults to the शेष page
 */
अटल व्योम gfxhub_v1_0_set_fault_enable_शेष(काष्ठा amdgpu_device *adev,
						 bool value)
अणु
	u32 पंचांगp;
	पंचांगp = RREG32_SOC15(GC, 0, mmVM_L2_PROTECTION_FAULT_CNTL);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_L2_PROTECTION_FAULT_CNTL,
			RANGE_PROTECTION_FAULT_ENABLE_DEFAULT, value);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_L2_PROTECTION_FAULT_CNTL,
			PDE0_PROTECTION_FAULT_ENABLE_DEFAULT, value);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_L2_PROTECTION_FAULT_CNTL,
			PDE1_PROTECTION_FAULT_ENABLE_DEFAULT, value);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_L2_PROTECTION_FAULT_CNTL,
			PDE2_PROTECTION_FAULT_ENABLE_DEFAULT, value);
	पंचांगp = REG_SET_FIELD(पंचांगp,
			VM_L2_PROTECTION_FAULT_CNTL,
			TRANSLATE_FURTHER_PROTECTION_FAULT_ENABLE_DEFAULT,
			value);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_L2_PROTECTION_FAULT_CNTL,
			NACK_PROTECTION_FAULT_ENABLE_DEFAULT, value);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_L2_PROTECTION_FAULT_CNTL,
			DUMMY_PAGE_PROTECTION_FAULT_ENABLE_DEFAULT, value);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_L2_PROTECTION_FAULT_CNTL,
			VALID_PROTECTION_FAULT_ENABLE_DEFAULT, value);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_L2_PROTECTION_FAULT_CNTL,
			READ_PROTECTION_FAULT_ENABLE_DEFAULT, value);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_L2_PROTECTION_FAULT_CNTL,
			WRITE_PROTECTION_FAULT_ENABLE_DEFAULT, value);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_L2_PROTECTION_FAULT_CNTL,
			EXECUTE_PROTECTION_FAULT_ENABLE_DEFAULT, value);
	अगर (!value) अणु
		पंचांगp = REG_SET_FIELD(पंचांगp, VM_L2_PROTECTION_FAULT_CNTL,
				CRASH_ON_NO_RETRY_FAULT, 1);
		पंचांगp = REG_SET_FIELD(पंचांगp, VM_L2_PROTECTION_FAULT_CNTL,
				CRASH_ON_RETRY_FAULT, 1);
	पूर्ण
	WREG32_SOC15(GC, 0, mmVM_L2_PROTECTION_FAULT_CNTL, पंचांगp);
पूर्ण

अटल व्योम gfxhub_v1_0_init(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_vmhub *hub = &adev->vmhub[AMDGPU_GFXHUB_0];

	hub->ctx0_ptb_addr_lo32 =
		SOC15_REG_OFFSET(GC, 0,
				 mmVM_CONTEXT0_PAGE_TABLE_BASE_ADDR_LO32);
	hub->ctx0_ptb_addr_hi32 =
		SOC15_REG_OFFSET(GC, 0,
				 mmVM_CONTEXT0_PAGE_TABLE_BASE_ADDR_HI32);
	hub->vm_inv_eng0_sem =
		SOC15_REG_OFFSET(GC, 0, mmVM_INVALIDATE_ENG0_SEM);
	hub->vm_inv_eng0_req =
		SOC15_REG_OFFSET(GC, 0, mmVM_INVALIDATE_ENG0_REQ);
	hub->vm_inv_eng0_ack =
		SOC15_REG_OFFSET(GC, 0, mmVM_INVALIDATE_ENG0_ACK);
	hub->vm_context0_cntl =
		SOC15_REG_OFFSET(GC, 0, mmVM_CONTEXT0_CNTL);
	hub->vm_l2_pro_fault_status =
		SOC15_REG_OFFSET(GC, 0, mmVM_L2_PROTECTION_FAULT_STATUS);
	hub->vm_l2_pro_fault_cntl =
		SOC15_REG_OFFSET(GC, 0, mmVM_L2_PROTECTION_FAULT_CNTL);

	hub->ctx_distance = mmVM_CONTEXT1_CNTL - mmVM_CONTEXT0_CNTL;
	hub->ctx_addr_distance = mmVM_CONTEXT1_PAGE_TABLE_BASE_ADDR_LO32 -
		mmVM_CONTEXT0_PAGE_TABLE_BASE_ADDR_LO32;
	hub->eng_distance = mmVM_INVALIDATE_ENG1_REQ - mmVM_INVALIDATE_ENG0_REQ;
	hub->eng_addr_distance = mmVM_INVALIDATE_ENG1_ADDR_RANGE_LO32 -
		mmVM_INVALIDATE_ENG0_ADDR_RANGE_LO32;
पूर्ण


स्थिर काष्ठा amdgpu_gfxhub_funcs gfxhub_v1_0_funcs = अणु
	.get_mc_fb_offset = gfxhub_v1_0_get_mc_fb_offset,
	.setup_vm_pt_regs = gfxhub_v1_0_setup_vm_pt_regs,
	.gart_enable = gfxhub_v1_0_gart_enable,
	.gart_disable = gfxhub_v1_0_gart_disable,
	.set_fault_enable_शेष = gfxhub_v1_0_set_fault_enable_शेष,
	.init = gfxhub_v1_0_init,
	.get_xgmi_info = gfxhub_v1_1_get_xgmi_info,
पूर्ण;
