<शैली गुरु>
/*
 * Copyright 2019 Advanced Micro Devices, Inc.
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
#समावेश "gfxhub_v2_0.h"

#समावेश "gc/gc_10_1_0_offset.h"
#समावेश "gc/gc_10_1_0_sh_mask.h"
#समावेश "gc/gc_10_1_0_default.h"
#समावेश "navi10_enum.h"

#समावेश "soc15_common.h"

अटल स्थिर अक्षर *gfxhub_client_ids[] = अणु
	"CB/DB",
	"Reserved",
	"GE1",
	"GE2",
	"CPF",
	"CPC",
	"CPG",
	"RLC",
	"TCP",
	"SQC (inst)",
	"SQC (data)",
	"SQG",
	"Reserved",
	"SDMA0",
	"SDMA1",
	"GCR",
	"SDMA2",
	"SDMA3",
पूर्ण;

अटल uपूर्णांक32_t gfxhub_v2_0_get_invalidate_req(अचिन्हित पूर्णांक vmid,
					       uपूर्णांक32_t flush_type)
अणु
	u32 req = 0;

	/* invalidate using legacy mode on vmid*/
	req = REG_SET_FIELD(req, GCVM_INVALIDATE_ENG0_REQ,
			    PER_VMID_INVALIDATE_REQ, 1 << vmid);
	req = REG_SET_FIELD(req, GCVM_INVALIDATE_ENG0_REQ, FLUSH_TYPE, flush_type);
	req = REG_SET_FIELD(req, GCVM_INVALIDATE_ENG0_REQ, INVALIDATE_L2_PTES, 1);
	req = REG_SET_FIELD(req, GCVM_INVALIDATE_ENG0_REQ, INVALIDATE_L2_PDE0, 1);
	req = REG_SET_FIELD(req, GCVM_INVALIDATE_ENG0_REQ, INVALIDATE_L2_PDE1, 1);
	req = REG_SET_FIELD(req, GCVM_INVALIDATE_ENG0_REQ, INVALIDATE_L2_PDE2, 1);
	req = REG_SET_FIELD(req, GCVM_INVALIDATE_ENG0_REQ, INVALIDATE_L1_PTES, 1);
	req = REG_SET_FIELD(req, GCVM_INVALIDATE_ENG0_REQ,
			    CLEAR_PROTECTION_FAULT_STATUS_ADDR,	0);

	वापस req;
पूर्ण

अटल व्योम
gfxhub_v2_0_prपूर्णांक_l2_protection_fault_status(काष्ठा amdgpu_device *adev,
					     uपूर्णांक32_t status)
अणु
	u32 cid = REG_GET_FIELD(status,
				GCVM_L2_PROTECTION_FAULT_STATUS, CID);

	dev_err(adev->dev,
		"GCVM_L2_PROTECTION_FAULT_STATUS:0x%08X\n",
		status);
	dev_err(adev->dev, "\t Faulty UTCL2 client ID: %s (0x%x)\n",
		cid >= ARRAY_SIZE(gfxhub_client_ids) ? "unknown" : gfxhub_client_ids[cid],
		cid);
	dev_err(adev->dev, "\t MORE_FAULTS: 0x%lx\n",
		REG_GET_FIELD(status,
		GCVM_L2_PROTECTION_FAULT_STATUS, MORE_FAULTS));
	dev_err(adev->dev, "\t WALKER_ERROR: 0x%lx\n",
		REG_GET_FIELD(status,
		GCVM_L2_PROTECTION_FAULT_STATUS, WALKER_ERROR));
	dev_err(adev->dev, "\t PERMISSION_FAULTS: 0x%lx\n",
		REG_GET_FIELD(status,
		GCVM_L2_PROTECTION_FAULT_STATUS, PERMISSION_FAULTS));
	dev_err(adev->dev, "\t MAPPING_ERROR: 0x%lx\n",
		REG_GET_FIELD(status,
		GCVM_L2_PROTECTION_FAULT_STATUS, MAPPING_ERROR));
	dev_err(adev->dev, "\t RW: 0x%lx\n",
		REG_GET_FIELD(status,
		GCVM_L2_PROTECTION_FAULT_STATUS, RW));
पूर्ण

अटल u64 gfxhub_v2_0_get_fb_location(काष्ठा amdgpu_device *adev)
अणु
	u64 base = RREG32_SOC15(GC, 0, mmGCMC_VM_FB_LOCATION_BASE);

	base &= GCMC_VM_FB_LOCATION_BASE__FB_BASE_MASK;
	base <<= 24;

	वापस base;
पूर्ण

अटल u64 gfxhub_v2_0_get_mc_fb_offset(काष्ठा amdgpu_device *adev)
अणु
	वापस (u64)RREG32_SOC15(GC, 0, mmGCMC_VM_FB_OFFSET) << 24;
पूर्ण

अटल व्योम gfxhub_v2_0_setup_vm_pt_regs(काष्ठा amdgpu_device *adev, uपूर्णांक32_t vmid,
				uपूर्णांक64_t page_table_base)
अणु
	काष्ठा amdgpu_vmhub *hub = &adev->vmhub[AMDGPU_GFXHUB_0];

	WREG32_SOC15_OFFSET(GC, 0, mmGCVM_CONTEXT0_PAGE_TABLE_BASE_ADDR_LO32,
			    hub->ctx_addr_distance * vmid,
			    lower_32_bits(page_table_base));

	WREG32_SOC15_OFFSET(GC, 0, mmGCVM_CONTEXT0_PAGE_TABLE_BASE_ADDR_HI32,
			    hub->ctx_addr_distance * vmid,
			    upper_32_bits(page_table_base));
पूर्ण

अटल व्योम gfxhub_v2_0_init_gart_aperture_regs(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक64_t pt_base = amdgpu_gmc_pd_addr(adev->gart.bo);

	gfxhub_v2_0_setup_vm_pt_regs(adev, 0, pt_base);

	WREG32_SOC15(GC, 0, mmGCVM_CONTEXT0_PAGE_TABLE_START_ADDR_LO32,
		     (u32)(adev->gmc.gart_start >> 12));
	WREG32_SOC15(GC, 0, mmGCVM_CONTEXT0_PAGE_TABLE_START_ADDR_HI32,
		     (u32)(adev->gmc.gart_start >> 44));

	WREG32_SOC15(GC, 0, mmGCVM_CONTEXT0_PAGE_TABLE_END_ADDR_LO32,
		     (u32)(adev->gmc.gart_end >> 12));
	WREG32_SOC15(GC, 0, mmGCVM_CONTEXT0_PAGE_TABLE_END_ADDR_HI32,
		     (u32)(adev->gmc.gart_end >> 44));
पूर्ण

अटल व्योम gfxhub_v2_0_init_प्रणाली_aperture_regs(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक64_t value;

	अगर (!amdgpu_sriov_vf(adev)) अणु
		/* Program the AGP BAR */
		WREG32_SOC15(GC, 0, mmGCMC_VM_AGP_BASE, 0);
		WREG32_SOC15(GC, 0, mmGCMC_VM_AGP_BOT, adev->gmc.agp_start >> 24);
		WREG32_SOC15(GC, 0, mmGCMC_VM_AGP_TOP, adev->gmc.agp_end >> 24);

		/* Program the प्रणाली aperture low logical page number. */
		WREG32_SOC15(GC, 0, mmGCMC_VM_SYSTEM_APERTURE_LOW_ADDR,
			     min(adev->gmc.fb_start, adev->gmc.agp_start) >> 18);
		WREG32_SOC15(GC, 0, mmGCMC_VM_SYSTEM_APERTURE_HIGH_ADDR,
			     max(adev->gmc.fb_end, adev->gmc.agp_end) >> 18);

		/* Set शेष page address. */
		value = amdgpu_gmc_vram_mc2pa(adev, adev->vram_scratch.gpu_addr);
		WREG32_SOC15(GC, 0, mmGCMC_VM_SYSTEM_APERTURE_DEFAULT_ADDR_LSB,
			     (u32)(value >> 12));
		WREG32_SOC15(GC, 0, mmGCMC_VM_SYSTEM_APERTURE_DEFAULT_ADDR_MSB,
			     (u32)(value >> 44));
	पूर्ण

	/* Program "protection fault". */
	WREG32_SOC15(GC, 0, mmGCVM_L2_PROTECTION_FAULT_DEFAULT_ADDR_LO32,
		     (u32)(adev->dummy_page_addr >> 12));
	WREG32_SOC15(GC, 0, mmGCVM_L2_PROTECTION_FAULT_DEFAULT_ADDR_HI32,
		     (u32)((u64)adev->dummy_page_addr >> 44));

	WREG32_FIELD15(GC, 0, GCVM_L2_PROTECTION_FAULT_CNTL2,
		       ACTIVE_PAGE_MIGRATION_PTE_READ_RETRY, 1);
पूर्ण


अटल व्योम gfxhub_v2_0_init_tlb_regs(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक32_t पंचांगp;

	/* Setup TLB control */
	पंचांगp = RREG32_SOC15(GC, 0, mmGCMC_VM_MX_L1_TLB_CNTL);

	पंचांगp = REG_SET_FIELD(पंचांगp, GCMC_VM_MX_L1_TLB_CNTL, ENABLE_L1_TLB, 1);
	पंचांगp = REG_SET_FIELD(पंचांगp, GCMC_VM_MX_L1_TLB_CNTL, SYSTEM_ACCESS_MODE, 3);
	पंचांगp = REG_SET_FIELD(पंचांगp, GCMC_VM_MX_L1_TLB_CNTL,
			    ENABLE_ADVANCED_DRIVER_MODEL, 1);
	पंचांगp = REG_SET_FIELD(पंचांगp, GCMC_VM_MX_L1_TLB_CNTL,
			    SYSTEM_APERTURE_UNMAPPED_ACCESS, 0);
	पंचांगp = REG_SET_FIELD(पंचांगp, GCMC_VM_MX_L1_TLB_CNTL, ECO_BITS, 0);
	पंचांगp = REG_SET_FIELD(पंचांगp, GCMC_VM_MX_L1_TLB_CNTL,
			    MTYPE, MTYPE_UC); /* UC, uncached */

	WREG32_SOC15(GC, 0, mmGCMC_VM_MX_L1_TLB_CNTL, पंचांगp);
पूर्ण

अटल व्योम gfxhub_v2_0_init_cache_regs(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक32_t पंचांगp;

	/* These regs are not accessible क्रम VF, PF will program these in SRIOV */
	अगर (amdgpu_sriov_vf(adev))
		वापस;

	/* Setup L2 cache */
	पंचांगp = RREG32_SOC15(GC, 0, mmGCVM_L2_CNTL);
	पंचांगp = REG_SET_FIELD(पंचांगp, GCVM_L2_CNTL, ENABLE_L2_CACHE, 1);
	पंचांगp = REG_SET_FIELD(पंचांगp, GCVM_L2_CNTL, ENABLE_L2_FRAGMENT_PROCESSING, 0);
	पंचांगp = REG_SET_FIELD(पंचांगp, GCVM_L2_CNTL,
			    ENABLE_DEFAULT_PAGE_OUT_TO_SYSTEM_MEMORY, 1);
	/* XXX क्रम emulation, Refer to बंदd source code.*/
	पंचांगp = REG_SET_FIELD(पंचांगp, GCVM_L2_CNTL,
			    L2_PDE0_CACHE_TAG_GENERATION_MODE, 0);
	पंचांगp = REG_SET_FIELD(पंचांगp, GCVM_L2_CNTL, PDE_FAULT_CLASSIFICATION, 0);
	पंचांगp = REG_SET_FIELD(पंचांगp, GCVM_L2_CNTL, CONTEXT1_IDENTITY_ACCESS_MODE, 1);
	पंचांगp = REG_SET_FIELD(पंचांगp, GCVM_L2_CNTL, IDENTITY_MODE_FRAGMENT_SIZE, 0);
	WREG32_SOC15(GC, 0, mmGCVM_L2_CNTL, पंचांगp);

	पंचांगp = RREG32_SOC15(GC, 0, mmGCVM_L2_CNTL2);
	पंचांगp = REG_SET_FIELD(पंचांगp, GCVM_L2_CNTL2, INVALIDATE_ALL_L1_TLBS, 1);
	पंचांगp = REG_SET_FIELD(पंचांगp, GCVM_L2_CNTL2, INVALIDATE_L2_CACHE, 1);
	WREG32_SOC15(GC, 0, mmGCVM_L2_CNTL2, पंचांगp);

	पंचांगp = mmGCVM_L2_CNTL3_DEFAULT;
	अगर (adev->gmc.translate_further) अणु
		पंचांगp = REG_SET_FIELD(पंचांगp, GCVM_L2_CNTL3, BANK_SELECT, 12);
		पंचांगp = REG_SET_FIELD(पंचांगp, GCVM_L2_CNTL3,
				    L2_CACHE_BIGK_FRAGMENT_SIZE, 9);
	पूर्ण अन्यथा अणु
		पंचांगp = REG_SET_FIELD(पंचांगp, GCVM_L2_CNTL3, BANK_SELECT, 9);
		पंचांगp = REG_SET_FIELD(पंचांगp, GCVM_L2_CNTL3,
				    L2_CACHE_BIGK_FRAGMENT_SIZE, 6);
	पूर्ण
	WREG32_SOC15(GC, 0, mmGCVM_L2_CNTL3, पंचांगp);

	पंचांगp = mmGCVM_L2_CNTL4_DEFAULT;
	पंचांगp = REG_SET_FIELD(पंचांगp, GCVM_L2_CNTL4, VMC_TAP_PDE_REQUEST_PHYSICAL, 0);
	पंचांगp = REG_SET_FIELD(पंचांगp, GCVM_L2_CNTL4, VMC_TAP_PTE_REQUEST_PHYSICAL, 0);
	WREG32_SOC15(GC, 0, mmGCVM_L2_CNTL4, पंचांगp);

	पंचांगp = mmGCVM_L2_CNTL5_DEFAULT;
	पंचांगp = REG_SET_FIELD(पंचांगp, GCVM_L2_CNTL5, L2_CACHE_SMALLK_FRAGMENT_SIZE, 0);
	WREG32_SOC15(GC, 0, mmGCVM_L2_CNTL5, पंचांगp);
पूर्ण

अटल व्योम gfxhub_v2_0_enable_प्रणाली_करोमुख्य(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक32_t पंचांगp;

	पंचांगp = RREG32_SOC15(GC, 0, mmGCVM_CONTEXT0_CNTL);
	पंचांगp = REG_SET_FIELD(पंचांगp, GCVM_CONTEXT0_CNTL, ENABLE_CONTEXT, 1);
	पंचांगp = REG_SET_FIELD(पंचांगp, GCVM_CONTEXT0_CNTL, PAGE_TABLE_DEPTH, 0);
	पंचांगp = REG_SET_FIELD(पंचांगp, GCVM_CONTEXT0_CNTL,
			    RETRY_PERMISSION_OR_INVALID_PAGE_FAULT, 0);
	WREG32_SOC15(GC, 0, mmGCVM_CONTEXT0_CNTL, पंचांगp);
पूर्ण

अटल व्योम gfxhub_v2_0_disable_identity_aperture(काष्ठा amdgpu_device *adev)
अणु
	WREG32_SOC15(GC, 0, mmGCVM_L2_CONTEXT1_IDENTITY_APERTURE_LOW_ADDR_LO32,
		     0xFFFFFFFF);
	WREG32_SOC15(GC, 0, mmGCVM_L2_CONTEXT1_IDENTITY_APERTURE_LOW_ADDR_HI32,
		     0x0000000F);

	WREG32_SOC15(GC, 0, mmGCVM_L2_CONTEXT1_IDENTITY_APERTURE_HIGH_ADDR_LO32,
		     0);
	WREG32_SOC15(GC, 0, mmGCVM_L2_CONTEXT1_IDENTITY_APERTURE_HIGH_ADDR_HI32,
		     0);

	WREG32_SOC15(GC, 0, mmGCVM_L2_CONTEXT_IDENTITY_PHYSICAL_OFFSET_LO32, 0);
	WREG32_SOC15(GC, 0, mmGCVM_L2_CONTEXT_IDENTITY_PHYSICAL_OFFSET_HI32, 0);

पूर्ण

अटल व्योम gfxhub_v2_0_setup_vmid_config(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_vmhub *hub = &adev->vmhub[AMDGPU_GFXHUB_0];
	पूर्णांक i;
	uपूर्णांक32_t पंचांगp;

	क्रम (i = 0; i <= 14; i++) अणु
		पंचांगp = RREG32_SOC15_OFFSET(GC, 0, mmGCVM_CONTEXT1_CNTL, i);
		पंचांगp = REG_SET_FIELD(पंचांगp, GCVM_CONTEXT1_CNTL, ENABLE_CONTEXT, 1);
		पंचांगp = REG_SET_FIELD(पंचांगp, GCVM_CONTEXT1_CNTL, PAGE_TABLE_DEPTH,
				    adev->vm_manager.num_level);
		पंचांगp = REG_SET_FIELD(पंचांगp, GCVM_CONTEXT1_CNTL,
				RANGE_PROTECTION_FAULT_ENABLE_DEFAULT, 1);
		पंचांगp = REG_SET_FIELD(पंचांगp, GCVM_CONTEXT1_CNTL,
				DUMMY_PAGE_PROTECTION_FAULT_ENABLE_DEFAULT, 1);
		पंचांगp = REG_SET_FIELD(पंचांगp, GCVM_CONTEXT1_CNTL,
				PDE0_PROTECTION_FAULT_ENABLE_DEFAULT, 1);
		पंचांगp = REG_SET_FIELD(पंचांगp, GCVM_CONTEXT1_CNTL,
				VALID_PROTECTION_FAULT_ENABLE_DEFAULT, 1);
		पंचांगp = REG_SET_FIELD(पंचांगp, GCVM_CONTEXT1_CNTL,
				READ_PROTECTION_FAULT_ENABLE_DEFAULT, 1);
		पंचांगp = REG_SET_FIELD(पंचांगp, GCVM_CONTEXT1_CNTL,
				WRITE_PROTECTION_FAULT_ENABLE_DEFAULT, 1);
		पंचांगp = REG_SET_FIELD(पंचांगp, GCVM_CONTEXT1_CNTL,
				EXECUTE_PROTECTION_FAULT_ENABLE_DEFAULT, 1);
		पंचांगp = REG_SET_FIELD(पंचांगp, GCVM_CONTEXT1_CNTL,
				PAGE_TABLE_BLOCK_SIZE,
				adev->vm_manager.block_size - 9);
		/* Send no-retry XNACK on fault to suppress VM fault storm. */
		पंचांगp = REG_SET_FIELD(पंचांगp, GCVM_CONTEXT1_CNTL,
				    RETRY_PERMISSION_OR_INVALID_PAGE_FAULT,
				    !adev->gmc.noretry);
		WREG32_SOC15_OFFSET(GC, 0, mmGCVM_CONTEXT1_CNTL,
				    i * hub->ctx_distance, पंचांगp);
		WREG32_SOC15_OFFSET(GC, 0, mmGCVM_CONTEXT1_PAGE_TABLE_START_ADDR_LO32,
				    i * hub->ctx_addr_distance, 0);
		WREG32_SOC15_OFFSET(GC, 0, mmGCVM_CONTEXT1_PAGE_TABLE_START_ADDR_HI32,
				    i * hub->ctx_addr_distance, 0);
		WREG32_SOC15_OFFSET(GC, 0, mmGCVM_CONTEXT1_PAGE_TABLE_END_ADDR_LO32,
				    i * hub->ctx_addr_distance,
				    lower_32_bits(adev->vm_manager.max_pfn - 1));
		WREG32_SOC15_OFFSET(GC, 0, mmGCVM_CONTEXT1_PAGE_TABLE_END_ADDR_HI32,
				    i * hub->ctx_addr_distance,
				    upper_32_bits(adev->vm_manager.max_pfn - 1));
	पूर्ण
पूर्ण

अटल व्योम gfxhub_v2_0_program_invalidation(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_vmhub *hub = &adev->vmhub[AMDGPU_GFXHUB_0];
	अचिन्हित i;

	क्रम (i = 0 ; i < 18; ++i) अणु
		WREG32_SOC15_OFFSET(GC, 0, mmGCVM_INVALIDATE_ENG0_ADDR_RANGE_LO32,
				    i * hub->eng_addr_distance, 0xffffffff);
		WREG32_SOC15_OFFSET(GC, 0, mmGCVM_INVALIDATE_ENG0_ADDR_RANGE_HI32,
				    i * hub->eng_addr_distance, 0x1f);
	पूर्ण
पूर्ण

अटल पूर्णांक gfxhub_v2_0_gart_enable(काष्ठा amdgpu_device *adev)
अणु
	/* GART Enable. */
	gfxhub_v2_0_init_gart_aperture_regs(adev);
	gfxhub_v2_0_init_प्रणाली_aperture_regs(adev);
	gfxhub_v2_0_init_tlb_regs(adev);
	gfxhub_v2_0_init_cache_regs(adev);

	gfxhub_v2_0_enable_प्रणाली_करोमुख्य(adev);
	gfxhub_v2_0_disable_identity_aperture(adev);
	gfxhub_v2_0_setup_vmid_config(adev);
	gfxhub_v2_0_program_invalidation(adev);

	वापस 0;
पूर्ण

अटल व्योम gfxhub_v2_0_gart_disable(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_vmhub *hub = &adev->vmhub[AMDGPU_GFXHUB_0];
	u32 पंचांगp;
	u32 i;

	/* Disable all tables */
	क्रम (i = 0; i < 16; i++)
		WREG32_SOC15_OFFSET(GC, 0, mmGCVM_CONTEXT0_CNTL,
				    i * hub->ctx_distance, 0);

	/* Setup TLB control */
	पंचांगp = RREG32_SOC15(GC, 0, mmGCMC_VM_MX_L1_TLB_CNTL);
	पंचांगp = REG_SET_FIELD(पंचांगp, GCMC_VM_MX_L1_TLB_CNTL, ENABLE_L1_TLB, 0);
	पंचांगp = REG_SET_FIELD(पंचांगp, GCMC_VM_MX_L1_TLB_CNTL,
			    ENABLE_ADVANCED_DRIVER_MODEL, 0);
	WREG32_SOC15(GC, 0, mmGCMC_VM_MX_L1_TLB_CNTL, पंचांगp);

	अगर (!amdgpu_sriov_vf(adev)) अणु
		/* Setup L2 cache */
		WREG32_FIELD15(GC, 0, GCVM_L2_CNTL, ENABLE_L2_CACHE, 0);
		WREG32_SOC15(GC, 0, mmGCVM_L2_CNTL3, 0);
	पूर्ण
पूर्ण

/**
 * gfxhub_v2_0_set_fault_enable_शेष - update GART/VM fault handling
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @value: true redirects VM faults to the शेष page
 */
अटल व्योम gfxhub_v2_0_set_fault_enable_शेष(काष्ठा amdgpu_device *adev,
					  bool value)
अणु
	u32 पंचांगp;
	पंचांगp = RREG32_SOC15(GC, 0, mmGCVM_L2_PROTECTION_FAULT_CNTL);
	पंचांगp = REG_SET_FIELD(पंचांगp, GCVM_L2_PROTECTION_FAULT_CNTL,
			    RANGE_PROTECTION_FAULT_ENABLE_DEFAULT, value);
	पंचांगp = REG_SET_FIELD(पंचांगp, GCVM_L2_PROTECTION_FAULT_CNTL,
			    PDE0_PROTECTION_FAULT_ENABLE_DEFAULT, value);
	पंचांगp = REG_SET_FIELD(पंचांगp, GCVM_L2_PROTECTION_FAULT_CNTL,
			    PDE1_PROTECTION_FAULT_ENABLE_DEFAULT, value);
	पंचांगp = REG_SET_FIELD(पंचांगp, GCVM_L2_PROTECTION_FAULT_CNTL,
			    PDE2_PROTECTION_FAULT_ENABLE_DEFAULT, value);
	पंचांगp = REG_SET_FIELD(पंचांगp, GCVM_L2_PROTECTION_FAULT_CNTL,
			    TRANSLATE_FURTHER_PROTECTION_FAULT_ENABLE_DEFAULT,
			    value);
	पंचांगp = REG_SET_FIELD(पंचांगp, GCVM_L2_PROTECTION_FAULT_CNTL,
			    NACK_PROTECTION_FAULT_ENABLE_DEFAULT, value);
	पंचांगp = REG_SET_FIELD(पंचांगp, GCVM_L2_PROTECTION_FAULT_CNTL,
			    DUMMY_PAGE_PROTECTION_FAULT_ENABLE_DEFAULT, value);
	पंचांगp = REG_SET_FIELD(पंचांगp, GCVM_L2_PROTECTION_FAULT_CNTL,
			    VALID_PROTECTION_FAULT_ENABLE_DEFAULT, value);
	पंचांगp = REG_SET_FIELD(पंचांगp, GCVM_L2_PROTECTION_FAULT_CNTL,
			    READ_PROTECTION_FAULT_ENABLE_DEFAULT, value);
	पंचांगp = REG_SET_FIELD(पंचांगp, GCVM_L2_PROTECTION_FAULT_CNTL,
			    WRITE_PROTECTION_FAULT_ENABLE_DEFAULT, value);
	पंचांगp = REG_SET_FIELD(पंचांगp, GCVM_L2_PROTECTION_FAULT_CNTL,
			    EXECUTE_PROTECTION_FAULT_ENABLE_DEFAULT, value);
	अगर (!value) अणु
		पंचांगp = REG_SET_FIELD(पंचांगp, GCVM_L2_PROTECTION_FAULT_CNTL,
				CRASH_ON_NO_RETRY_FAULT, 1);
		पंचांगp = REG_SET_FIELD(पंचांगp, GCVM_L2_PROTECTION_FAULT_CNTL,
				CRASH_ON_RETRY_FAULT, 1);
	पूर्ण
	WREG32_SOC15(GC, 0, mmGCVM_L2_PROTECTION_FAULT_CNTL, पंचांगp);
पूर्ण

अटल स्थिर काष्ठा amdgpu_vmhub_funcs gfxhub_v2_0_vmhub_funcs = अणु
	.prपूर्णांक_l2_protection_fault_status = gfxhub_v2_0_prपूर्णांक_l2_protection_fault_status,
	.get_invalidate_req = gfxhub_v2_0_get_invalidate_req,
पूर्ण;

अटल व्योम gfxhub_v2_0_init(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_vmhub *hub = &adev->vmhub[AMDGPU_GFXHUB_0];

	hub->ctx0_ptb_addr_lo32 =
		SOC15_REG_OFFSET(GC, 0,
				 mmGCVM_CONTEXT0_PAGE_TABLE_BASE_ADDR_LO32);
	hub->ctx0_ptb_addr_hi32 =
		SOC15_REG_OFFSET(GC, 0,
				 mmGCVM_CONTEXT0_PAGE_TABLE_BASE_ADDR_HI32);
	hub->vm_inv_eng0_sem =
		SOC15_REG_OFFSET(GC, 0, mmGCVM_INVALIDATE_ENG0_SEM);
	hub->vm_inv_eng0_req =
		SOC15_REG_OFFSET(GC, 0, mmGCVM_INVALIDATE_ENG0_REQ);
	hub->vm_inv_eng0_ack =
		SOC15_REG_OFFSET(GC, 0, mmGCVM_INVALIDATE_ENG0_ACK);
	hub->vm_context0_cntl =
		SOC15_REG_OFFSET(GC, 0, mmGCVM_CONTEXT0_CNTL);
	hub->vm_l2_pro_fault_status =
		SOC15_REG_OFFSET(GC, 0, mmGCVM_L2_PROTECTION_FAULT_STATUS);
	hub->vm_l2_pro_fault_cntl =
		SOC15_REG_OFFSET(GC, 0, mmGCVM_L2_PROTECTION_FAULT_CNTL);

	hub->ctx_distance = mmGCVM_CONTEXT1_CNTL - mmGCVM_CONTEXT0_CNTL;
	hub->ctx_addr_distance = mmGCVM_CONTEXT1_PAGE_TABLE_BASE_ADDR_LO32 -
		mmGCVM_CONTEXT0_PAGE_TABLE_BASE_ADDR_LO32;
	hub->eng_distance = mmGCVM_INVALIDATE_ENG1_REQ -
		mmGCVM_INVALIDATE_ENG0_REQ;
	hub->eng_addr_distance = mmGCVM_INVALIDATE_ENG1_ADDR_RANGE_LO32 -
		mmGCVM_INVALIDATE_ENG0_ADDR_RANGE_LO32;

	hub->vm_cntx_cntl_vm_fault = GCVM_CONTEXT1_CNTL__RANGE_PROTECTION_FAULT_ENABLE_INTERRUPT_MASK |
		GCVM_CONTEXT1_CNTL__DUMMY_PAGE_PROTECTION_FAULT_ENABLE_INTERRUPT_MASK |
		GCVM_CONTEXT1_CNTL__PDE0_PROTECTION_FAULT_ENABLE_INTERRUPT_MASK |
		GCVM_CONTEXT1_CNTL__VALID_PROTECTION_FAULT_ENABLE_INTERRUPT_MASK |
		GCVM_CONTEXT1_CNTL__READ_PROTECTION_FAULT_ENABLE_INTERRUPT_MASK |
		GCVM_CONTEXT1_CNTL__WRITE_PROTECTION_FAULT_ENABLE_INTERRUPT_MASK |
		GCVM_CONTEXT1_CNTL__EXECUTE_PROTECTION_FAULT_ENABLE_INTERRUPT_MASK;

	hub->vmhub_funcs = &gfxhub_v2_0_vmhub_funcs;
पूर्ण

स्थिर काष्ठा amdgpu_gfxhub_funcs gfxhub_v2_0_funcs = अणु
	.get_fb_location = gfxhub_v2_0_get_fb_location,
	.get_mc_fb_offset = gfxhub_v2_0_get_mc_fb_offset,
	.setup_vm_pt_regs = gfxhub_v2_0_setup_vm_pt_regs,
	.gart_enable = gfxhub_v2_0_gart_enable,
	.gart_disable = gfxhub_v2_0_gart_disable,
	.set_fault_enable_शेष = gfxhub_v2_0_set_fault_enable_शेष,
	.init = gfxhub_v2_0_init,
पूर्ण;
