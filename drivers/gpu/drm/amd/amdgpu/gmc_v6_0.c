<शैली गुरु>
/*
 * Copyright 2014 Advanced Micro Devices, Inc.
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

#समावेश <linux/firmware.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>

#समावेश <drm/drm_cache.h>
#समावेश "amdgpu.h"
#समावेश "gmc_v6_0.h"
#समावेश "amdgpu_ucode.h"
#समावेश "amdgpu_gem.h"

#समावेश "bif/bif_3_0_d.h"
#समावेश "bif/bif_3_0_sh_mask.h"
#समावेश "oss/oss_1_0_d.h"
#समावेश "oss/oss_1_0_sh_mask.h"
#समावेश "gmc/gmc_6_0_d.h"
#समावेश "gmc/gmc_6_0_sh_mask.h"
#समावेश "dce/dce_6_0_d.h"
#समावेश "dce/dce_6_0_sh_mask.h"
#समावेश "si_enums.h"

अटल व्योम gmc_v6_0_set_gmc_funcs(काष्ठा amdgpu_device *adev);
अटल व्योम gmc_v6_0_set_irq_funcs(काष्ठा amdgpu_device *adev);
अटल पूर्णांक gmc_v6_0_रुको_क्रम_idle(व्योम *handle);

MODULE_FIRMWARE("amdgpu/tahiti_mc.bin");
MODULE_FIRMWARE("amdgpu/pitcairn_mc.bin");
MODULE_FIRMWARE("amdgpu/verde_mc.bin");
MODULE_FIRMWARE("amdgpu/oland_mc.bin");
MODULE_FIRMWARE("amdgpu/hainan_mc.bin");
MODULE_FIRMWARE("amdgpu/si58_mc.bin");

#घोषणा MC_SEQ_MISC0__MT__MASK   0xf0000000
#घोषणा MC_SEQ_MISC0__MT__GDDR1  0x10000000
#घोषणा MC_SEQ_MISC0__MT__DDR2   0x20000000
#घोषणा MC_SEQ_MISC0__MT__GDDR3  0x30000000
#घोषणा MC_SEQ_MISC0__MT__GDDR4  0x40000000
#घोषणा MC_SEQ_MISC0__MT__GDDR5  0x50000000
#घोषणा MC_SEQ_MISC0__MT__HBM    0x60000000
#घोषणा MC_SEQ_MISC0__MT__DDR3   0xB0000000

अटल व्योम gmc_v6_0_mc_stop(काष्ठा amdgpu_device *adev)
अणु
	u32 blackout;

	gmc_v6_0_रुको_क्रम_idle((व्योम *)adev);

	blackout = RREG32(mmMC_SHARED_BLACKOUT_CNTL);
	अगर (REG_GET_FIELD(blackout, MC_SHARED_BLACKOUT_CNTL, BLACKOUT_MODE) != 1) अणु
		/* Block CPU access */
		WREG32(mmBIF_FB_EN, 0);
		/* blackout the MC */
		blackout = REG_SET_FIELD(blackout,
					 MC_SHARED_BLACKOUT_CNTL, BLACKOUT_MODE, 0);
		WREG32(mmMC_SHARED_BLACKOUT_CNTL, blackout | 1);
	पूर्ण
	/* रुको क्रम the MC to settle */
	udelay(100);

पूर्ण

अटल व्योम gmc_v6_0_mc_resume(काष्ठा amdgpu_device *adev)
अणु
	u32 पंचांगp;

	/* unblackout the MC */
	पंचांगp = RREG32(mmMC_SHARED_BLACKOUT_CNTL);
	पंचांगp = REG_SET_FIELD(पंचांगp, MC_SHARED_BLACKOUT_CNTL, BLACKOUT_MODE, 0);
	WREG32(mmMC_SHARED_BLACKOUT_CNTL, पंचांगp);
	/* allow CPU access */
	पंचांगp = REG_SET_FIELD(0, BIF_FB_EN, FB_READ_EN, 1);
	पंचांगp = REG_SET_FIELD(पंचांगp, BIF_FB_EN, FB_WRITE_EN, 1);
	WREG32(mmBIF_FB_EN, पंचांगp);
पूर्ण

अटल पूर्णांक gmc_v6_0_init_microcode(काष्ठा amdgpu_device *adev)
अणु
	स्थिर अक्षर *chip_name;
	अक्षर fw_name[30];
	पूर्णांक err;
	bool is_58_fw = false;

	DRM_DEBUG("\n");

	चयन (adev->asic_type) अणु
	हाल CHIP_TAHITI:
		chip_name = "tahiti";
		अवरोध;
	हाल CHIP_PITCAIRN:
		chip_name = "pitcairn";
		अवरोध;
	हाल CHIP_VERDE:
		chip_name = "verde";
		अवरोध;
	हाल CHIP_OLAND:
		chip_name = "oland";
		अवरोध;
	हाल CHIP_HAIन_अंक:
		chip_name = "hainan";
		अवरोध;
	शेष: BUG();
	पूर्ण

	/* this memory configuration requires special firmware */
	अगर (((RREG32(mmMC_SEQ_MISC0) & 0xff000000) >> 24) == 0x58)
		is_58_fw = true;

	अगर (is_58_fw)
		snम_लिखो(fw_name, माप(fw_name), "amdgpu/si58_mc.bin");
	अन्यथा
		snम_लिखो(fw_name, माप(fw_name), "amdgpu/%s_mc.bin", chip_name);
	err = request_firmware(&adev->gmc.fw, fw_name, adev->dev);
	अगर (err)
		जाओ out;

	err = amdgpu_ucode_validate(adev->gmc.fw);

out:
	अगर (err) अणु
		dev_err(adev->dev,
		       "si_mc: Failed to load firmware \"%s\"\n",
		       fw_name);
		release_firmware(adev->gmc.fw);
		adev->gmc.fw = शून्य;
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक gmc_v6_0_mc_load_microcode(काष्ठा amdgpu_device *adev)
अणु
	स्थिर __le32 *new_fw_data = शून्य;
	u32 running;
	स्थिर __le32 *new_io_mc_regs = शून्य;
	पूर्णांक i, regs_size, ucode_size;
	स्थिर काष्ठा mc_firmware_header_v1_0 *hdr;

	अगर (!adev->gmc.fw)
		वापस -EINVAL;

	hdr = (स्थिर काष्ठा mc_firmware_header_v1_0 *)adev->gmc.fw->data;

	amdgpu_ucode_prपूर्णांक_mc_hdr(&hdr->header);

	adev->gmc.fw_version = le32_to_cpu(hdr->header.ucode_version);
	regs_size = le32_to_cpu(hdr->io_debug_size_bytes) / (4 * 2);
	new_io_mc_regs = (स्थिर __le32 *)
		(adev->gmc.fw->data + le32_to_cpu(hdr->io_debug_array_offset_bytes));
	ucode_size = le32_to_cpu(hdr->header.ucode_size_bytes) / 4;
	new_fw_data = (स्थिर __le32 *)
		(adev->gmc.fw->data + le32_to_cpu(hdr->header.ucode_array_offset_bytes));

	running = RREG32(mmMC_SEQ_SUP_CNTL) & MC_SEQ_SUP_CNTL__RUN_MASK;

	अगर (running == 0) अणु

		/* reset the engine and set to writable */
		WREG32(mmMC_SEQ_SUP_CNTL, 0x00000008);
		WREG32(mmMC_SEQ_SUP_CNTL, 0x00000010);

		/* load mc io regs */
		क्रम (i = 0; i < regs_size; i++) अणु
			WREG32(mmMC_SEQ_IO_DEBUG_INDEX, le32_to_cpup(new_io_mc_regs++));
			WREG32(mmMC_SEQ_IO_DEBUG_DATA, le32_to_cpup(new_io_mc_regs++));
		पूर्ण
		/* load the MC ucode */
		क्रम (i = 0; i < ucode_size; i++) अणु
			WREG32(mmMC_SEQ_SUP_PGM, le32_to_cpup(new_fw_data++));
		पूर्ण

		/* put the engine back पूर्णांकo the active state */
		WREG32(mmMC_SEQ_SUP_CNTL, 0x00000008);
		WREG32(mmMC_SEQ_SUP_CNTL, 0x00000004);
		WREG32(mmMC_SEQ_SUP_CNTL, 0x00000001);

		/* रुको क्रम training to complete */
		क्रम (i = 0; i < adev->usec_समयout; i++) अणु
			अगर (RREG32(mmMC_SEQ_TRAIN_WAKEUP_CNTL) & MC_SEQ_TRAIN_WAKEUP_CNTL__TRAIN_DONE_D0_MASK)
				अवरोध;
			udelay(1);
		पूर्ण
		क्रम (i = 0; i < adev->usec_समयout; i++) अणु
			अगर (RREG32(mmMC_SEQ_TRAIN_WAKEUP_CNTL) & MC_SEQ_TRAIN_WAKEUP_CNTL__TRAIN_DONE_D1_MASK)
				अवरोध;
			udelay(1);
		पूर्ण

	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम gmc_v6_0_vram_gtt_location(काष्ठा amdgpu_device *adev,
				       काष्ठा amdgpu_gmc *mc)
अणु
	u64 base = RREG32(mmMC_VM_FB_LOCATION) & 0xFFFF;
	base <<= 24;

	amdgpu_gmc_vram_location(adev, mc, base);
	amdgpu_gmc_gart_location(adev, mc);
पूर्ण

अटल व्योम gmc_v6_0_mc_program(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i, j;

	/* Initialize HDP */
	क्रम (i = 0, j = 0; i < 32; i++, j += 0x6) अणु
		WREG32((0xb05 + j), 0x00000000);
		WREG32((0xb06 + j), 0x00000000);
		WREG32((0xb07 + j), 0x00000000);
		WREG32((0xb08 + j), 0x00000000);
		WREG32((0xb09 + j), 0x00000000);
	पूर्ण
	WREG32(mmHDP_REG_COHERENCY_FLUSH_CNTL, 0);

	अगर (gmc_v6_0_रुको_क्रम_idle((व्योम *)adev)) अणु
		dev_warn(adev->dev, "Wait for MC idle timedout !\n");
	पूर्ण

	अगर (adev->mode_info.num_crtc) अणु
		u32 पंचांगp;

		/* Lockout access through VGA aperture*/
		पंचांगp = RREG32(mmVGA_HDP_CONTROL);
		पंचांगp |= VGA_HDP_CONTROL__VGA_MEMORY_DISABLE_MASK;
		WREG32(mmVGA_HDP_CONTROL, पंचांगp);

		/* disable VGA render */
		पंचांगp = RREG32(mmVGA_RENDER_CONTROL);
		पंचांगp &= ~VGA_VSTATUS_CNTL;
		WREG32(mmVGA_RENDER_CONTROL, पंचांगp);
	पूर्ण
	/* Update configuration */
	WREG32(mmMC_VM_SYSTEM_APERTURE_LOW_ADDR,
	       adev->gmc.vram_start >> 12);
	WREG32(mmMC_VM_SYSTEM_APERTURE_HIGH_ADDR,
	       adev->gmc.vram_end >> 12);
	WREG32(mmMC_VM_SYSTEM_APERTURE_DEFAULT_ADDR,
	       adev->vram_scratch.gpu_addr >> 12);
	WREG32(mmMC_VM_AGP_BASE, 0);
	WREG32(mmMC_VM_AGP_TOP, 0x0FFFFFFF);
	WREG32(mmMC_VM_AGP_BOT, 0x0FFFFFFF);

	अगर (gmc_v6_0_रुको_क्रम_idle((व्योम *)adev)) अणु
		dev_warn(adev->dev, "Wait for MC idle timedout !\n");
	पूर्ण
पूर्ण

अटल पूर्णांक gmc_v6_0_mc_init(काष्ठा amdgpu_device *adev)
अणु

	u32 पंचांगp;
	पूर्णांक chansize, numchan;
	पूर्णांक r;

	पंचांगp = RREG32(mmMC_ARB_RAMCFG);
	अगर (पंचांगp & (1 << 11)) अणु
		chansize = 16;
	पूर्ण अन्यथा अगर (पंचांगp & MC_ARB_RAMCFG__CHANSIZE_MASK) अणु
		chansize = 64;
	पूर्ण अन्यथा अणु
		chansize = 32;
	पूर्ण
	पंचांगp = RREG32(mmMC_SHARED_CHMAP);
	चयन ((पंचांगp & MC_SHARED_CHMAP__NOOFCHAN_MASK) >> MC_SHARED_CHMAP__NOOFCHAN__SHIFT) अणु
	हाल 0:
	शेष:
		numchan = 1;
		अवरोध;
	हाल 1:
		numchan = 2;
		अवरोध;
	हाल 2:
		numchan = 4;
		अवरोध;
	हाल 3:
		numchan = 8;
		अवरोध;
	हाल 4:
		numchan = 3;
		अवरोध;
	हाल 5:
		numchan = 6;
		अवरोध;
	हाल 6:
		numchan = 10;
		अवरोध;
	हाल 7:
		numchan = 12;
		अवरोध;
	हाल 8:
		numchan = 16;
		अवरोध;
	पूर्ण
	adev->gmc.vram_width = numchan * chansize;
	/* size in MB on si */
	adev->gmc.mc_vram_size = RREG32(mmCONFIG_MEMSIZE) * 1024ULL * 1024ULL;
	adev->gmc.real_vram_size = RREG32(mmCONFIG_MEMSIZE) * 1024ULL * 1024ULL;

	अगर (!(adev->flags & AMD_IS_APU)) अणु
		r = amdgpu_device_resize_fb_bar(adev);
		अगर (r)
			वापस r;
	पूर्ण
	adev->gmc.aper_base = pci_resource_start(adev->pdev, 0);
	adev->gmc.aper_size = pci_resource_len(adev->pdev, 0);
	adev->gmc.visible_vram_size = adev->gmc.aper_size;

	/* set the gart size */
	अगर (amdgpu_gart_size == -1) अणु
		चयन (adev->asic_type) अणु
		हाल CHIP_HAIन_अंक:    /* no MM engines */
		शेष:
			adev->gmc.gart_size = 256ULL << 20;
			अवरोध;
		हाल CHIP_VERDE:    /* UVD, VCE करो not support GPUVM */
		हाल CHIP_TAHITI:   /* UVD, VCE करो not support GPUVM */
		हाल CHIP_PITCAIRN: /* UVD, VCE करो not support GPUVM */
		हाल CHIP_OLAND:    /* UVD, VCE करो not support GPUVM */
			adev->gmc.gart_size = 1024ULL << 20;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		adev->gmc.gart_size = (u64)amdgpu_gart_size << 20;
	पूर्ण

	adev->gmc.gart_size += adev->pm.smu_prv_buffer_size;
	gmc_v6_0_vram_gtt_location(adev, &adev->gmc);

	वापस 0;
पूर्ण

अटल व्योम gmc_v6_0_flush_gpu_tlb(काष्ठा amdgpu_device *adev, uपूर्णांक32_t vmid,
					uपूर्णांक32_t vmhub, uपूर्णांक32_t flush_type)
अणु
	WREG32(mmVM_INVALIDATE_REQUEST, 1 << vmid);
पूर्ण

अटल uपूर्णांक64_t gmc_v6_0_emit_flush_gpu_tlb(काष्ठा amdgpu_ring *ring,
					    अचिन्हित vmid, uपूर्णांक64_t pd_addr)
अणु
	uपूर्णांक32_t reg;

	/* ग_लिखो new base address */
	अगर (vmid < 8)
		reg = mmVM_CONTEXT0_PAGE_TABLE_BASE_ADDR + vmid;
	अन्यथा
		reg = mmVM_CONTEXT8_PAGE_TABLE_BASE_ADDR + (vmid - 8);
	amdgpu_ring_emit_wreg(ring, reg, pd_addr >> 12);

	/* bits 0-15 are the VM contexts0-15 */
	amdgpu_ring_emit_wreg(ring, mmVM_INVALIDATE_REQUEST, 1 << vmid);

	वापस pd_addr;
पूर्ण

अटल व्योम gmc_v6_0_get_vm_pde(काष्ठा amdgpu_device *adev, पूर्णांक level,
				uपूर्णांक64_t *addr, uपूर्णांक64_t *flags)
अणु
	BUG_ON(*addr & 0xFFFFFF0000000FFFULL);
पूर्ण

अटल व्योम gmc_v6_0_get_vm_pte(काष्ठा amdgpu_device *adev,
				काष्ठा amdgpu_bo_va_mapping *mapping,
				uपूर्णांक64_t *flags)
अणु
	*flags &= ~AMDGPU_PTE_EXECUTABLE;
	*flags &= ~AMDGPU_PTE_PRT;
पूर्ण

अटल व्योम gmc_v6_0_set_fault_enable_शेष(काष्ठा amdgpu_device *adev,
					      bool value)
अणु
	u32 पंचांगp;

	पंचांगp = RREG32(mmVM_CONTEXT1_CNTL);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_CONTEXT1_CNTL,
			    RANGE_PROTECTION_FAULT_ENABLE_DEFAULT, value);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_CONTEXT1_CNTL,
			    DUMMY_PAGE_PROTECTION_FAULT_ENABLE_DEFAULT, value);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_CONTEXT1_CNTL,
			    PDE0_PROTECTION_FAULT_ENABLE_DEFAULT, value);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_CONTEXT1_CNTL,
			    VALID_PROTECTION_FAULT_ENABLE_DEFAULT, value);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_CONTEXT1_CNTL,
			    READ_PROTECTION_FAULT_ENABLE_DEFAULT, value);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_CONTEXT1_CNTL,
			    WRITE_PROTECTION_FAULT_ENABLE_DEFAULT, value);
	WREG32(mmVM_CONTEXT1_CNTL, पंचांगp);
पूर्ण

 /**
   + * gmc_v8_0_set_prt - set PRT VM fault
   + *
   + * @adev: amdgpu_device poपूर्णांकer
   + * @enable: enable/disable VM fault handling क्रम PRT
   +*/
अटल व्योम gmc_v6_0_set_prt(काष्ठा amdgpu_device *adev, bool enable)
अणु
	u32 पंचांगp;

	अगर (enable && !adev->gmc.prt_warning) अणु
		dev_warn(adev->dev, "Disabling VM faults because of PRT request!\n");
		adev->gmc.prt_warning = true;
	पूर्ण

	पंचांगp = RREG32(mmVM_PRT_CNTL);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_PRT_CNTL,
			    CB_DISABLE_FAULT_ON_UNMAPPED_ACCESS,
			    enable);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_PRT_CNTL,
			    TC_DISABLE_FAULT_ON_UNMAPPED_ACCESS,
			    enable);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_PRT_CNTL,
			    L2_CACHE_STORE_INVALID_ENTRIES,
			    enable);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_PRT_CNTL,
			    L1_TLB_STORE_INVALID_ENTRIES,
			    enable);
	WREG32(mmVM_PRT_CNTL, पंचांगp);

	अगर (enable) अणु
		uपूर्णांक32_t low = AMDGPU_VA_RESERVED_SIZE >> AMDGPU_GPU_PAGE_SHIFT;
		uपूर्णांक32_t high = adev->vm_manager.max_pfn -
			(AMDGPU_VA_RESERVED_SIZE >> AMDGPU_GPU_PAGE_SHIFT);

		WREG32(mmVM_PRT_APERTURE0_LOW_ADDR, low);
		WREG32(mmVM_PRT_APERTURE1_LOW_ADDR, low);
		WREG32(mmVM_PRT_APERTURE2_LOW_ADDR, low);
		WREG32(mmVM_PRT_APERTURE3_LOW_ADDR, low);
		WREG32(mmVM_PRT_APERTURE0_HIGH_ADDR, high);
		WREG32(mmVM_PRT_APERTURE1_HIGH_ADDR, high);
		WREG32(mmVM_PRT_APERTURE2_HIGH_ADDR, high);
		WREG32(mmVM_PRT_APERTURE3_HIGH_ADDR, high);
	पूर्ण अन्यथा अणु
		WREG32(mmVM_PRT_APERTURE0_LOW_ADDR, 0xfffffff);
		WREG32(mmVM_PRT_APERTURE1_LOW_ADDR, 0xfffffff);
		WREG32(mmVM_PRT_APERTURE2_LOW_ADDR, 0xfffffff);
		WREG32(mmVM_PRT_APERTURE3_LOW_ADDR, 0xfffffff);
		WREG32(mmVM_PRT_APERTURE0_HIGH_ADDR, 0x0);
		WREG32(mmVM_PRT_APERTURE1_HIGH_ADDR, 0x0);
		WREG32(mmVM_PRT_APERTURE2_HIGH_ADDR, 0x0);
		WREG32(mmVM_PRT_APERTURE3_HIGH_ADDR, 0x0);
	पूर्ण
पूर्ण

अटल पूर्णांक gmc_v6_0_gart_enable(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक64_t table_addr;
	पूर्णांक r, i;
	u32 field;

	अगर (adev->gart.bo == शून्य) अणु
		dev_err(adev->dev, "No VRAM object for PCIE GART.\n");
		वापस -EINVAL;
	पूर्ण
	r = amdgpu_gart_table_vram_pin(adev);
	अगर (r)
		वापस r;

	table_addr = amdgpu_bo_gpu_offset(adev->gart.bo);

	/* Setup TLB control */
	WREG32(mmMC_VM_MX_L1_TLB_CNTL,
	       (0xA << 7) |
	       MC_VM_MX_L1_TLB_CNTL__ENABLE_L1_TLB_MASK |
	       MC_VM_MX_L1_TLB_CNTL__ENABLE_L1_FRAGMENT_PROCESSING_MASK |
	       MC_VM_MX_L1_TLB_CNTL__SYSTEM_ACCESS_MODE_MASK |
	       MC_VM_MX_L1_TLB_CNTL__ENABLE_ADVANCED_DRIVER_MODEL_MASK |
	       (0UL << MC_VM_MX_L1_TLB_CNTL__SYSTEM_APERTURE_UNMAPPED_ACCESS__SHIFT));
	/* Setup L2 cache */
	WREG32(mmVM_L2_CNTL,
	       VM_L2_CNTL__ENABLE_L2_CACHE_MASK |
	       VM_L2_CNTL__ENABLE_L2_FRAGMENT_PROCESSING_MASK |
	       VM_L2_CNTL__ENABLE_L2_PTE_CACHE_LRU_UPDATE_BY_WRITE_MASK |
	       VM_L2_CNTL__ENABLE_L2_PDE0_CACHE_LRU_UPDATE_BY_WRITE_MASK |
	       (7UL << VM_L2_CNTL__EFFECTIVE_L2_QUEUE_SIZE__SHIFT) |
	       (1UL << VM_L2_CNTL__CONTEXT1_IDENTITY_ACCESS_MODE__SHIFT));
	WREG32(mmVM_L2_CNTL2,
	       VM_L2_CNTL2__INVALIDATE_ALL_L1_TLBS_MASK |
	       VM_L2_CNTL2__INVALIDATE_L2_CACHE_MASK);

	field = adev->vm_manager.fragment_size;
	WREG32(mmVM_L2_CNTL3,
	       VM_L2_CNTL3__L2_CACHE_BIGK_ASSOCIATIVITY_MASK |
	       (field << VM_L2_CNTL3__BANK_SELECT__SHIFT) |
	       (field << VM_L2_CNTL3__L2_CACHE_BIGK_FRAGMENT_SIZE__SHIFT));
	/* setup context0 */
	WREG32(mmVM_CONTEXT0_PAGE_TABLE_START_ADDR, adev->gmc.gart_start >> 12);
	WREG32(mmVM_CONTEXT0_PAGE_TABLE_END_ADDR, adev->gmc.gart_end >> 12);
	WREG32(mmVM_CONTEXT0_PAGE_TABLE_BASE_ADDR, table_addr >> 12);
	WREG32(mmVM_CONTEXT0_PROTECTION_FAULT_DEFAULT_ADDR,
			(u32)(adev->dummy_page_addr >> 12));
	WREG32(mmVM_CONTEXT0_CNTL2, 0);
	WREG32(mmVM_CONTEXT0_CNTL,
	       VM_CONTEXT0_CNTL__ENABLE_CONTEXT_MASK |
	       (0UL << VM_CONTEXT0_CNTL__PAGE_TABLE_DEPTH__SHIFT) |
	       VM_CONTEXT0_CNTL__RANGE_PROTECTION_FAULT_ENABLE_DEFAULT_MASK);

	WREG32(0x575, 0);
	WREG32(0x576, 0);
	WREG32(0x577, 0);

	/* empty context1-15 */
	/* set vm size, must be a multiple of 4 */
	WREG32(mmVM_CONTEXT1_PAGE_TABLE_START_ADDR, 0);
	WREG32(mmVM_CONTEXT1_PAGE_TABLE_END_ADDR, adev->vm_manager.max_pfn - 1);
	/* Assign the pt base to something valid क्रम now; the pts used क्रम
	 * the VMs are determined by the application and setup and asचिन्हित
	 * on the fly in the vm part of radeon_gart.c
	 */
	क्रम (i = 1; i < AMDGPU_NUM_VMID; i++) अणु
		अगर (i < 8)
			WREG32(mmVM_CONTEXT0_PAGE_TABLE_BASE_ADDR + i,
			       table_addr >> 12);
		अन्यथा
			WREG32(mmVM_CONTEXT8_PAGE_TABLE_BASE_ADDR + i - 8,
			       table_addr >> 12);
	पूर्ण

	/* enable context1-15 */
	WREG32(mmVM_CONTEXT1_PROTECTION_FAULT_DEFAULT_ADDR,
	       (u32)(adev->dummy_page_addr >> 12));
	WREG32(mmVM_CONTEXT1_CNTL2, 4);
	WREG32(mmVM_CONTEXT1_CNTL,
	       VM_CONTEXT1_CNTL__ENABLE_CONTEXT_MASK |
	       (1UL << VM_CONTEXT1_CNTL__PAGE_TABLE_DEPTH__SHIFT) |
	       ((adev->vm_manager.block_size - 9)
	       << VM_CONTEXT1_CNTL__PAGE_TABLE_BLOCK_SIZE__SHIFT));
	अगर (amdgpu_vm_fault_stop == AMDGPU_VM_FAULT_STOP_ALWAYS)
		gmc_v6_0_set_fault_enable_शेष(adev, false);
	अन्यथा
		gmc_v6_0_set_fault_enable_शेष(adev, true);

	gmc_v6_0_flush_gpu_tlb(adev, 0, 0, 0);
	dev_info(adev->dev, "PCIE GART of %uM enabled (table at 0x%016llX).\n",
		 (अचिन्हित)(adev->gmc.gart_size >> 20),
		 (अचिन्हित दीर्घ दीर्घ)table_addr);
	adev->gart.पढ़ोy = true;
	वापस 0;
पूर्ण

अटल पूर्णांक gmc_v6_0_gart_init(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक r;

	अगर (adev->gart.bo) अणु
		dev_warn(adev->dev, "gmc_v6_0 PCIE GART already initialized\n");
		वापस 0;
	पूर्ण
	r = amdgpu_gart_init(adev);
	अगर (r)
		वापस r;
	adev->gart.table_size = adev->gart.num_gpu_pages * 8;
	adev->gart.gart_pte_flags = 0;
	वापस amdgpu_gart_table_vram_alloc(adev);
पूर्ण

अटल व्योम gmc_v6_0_gart_disable(काष्ठा amdgpu_device *adev)
अणु
	/*अचिन्हित i;

	क्रम (i = 1; i < 16; ++i) अणु
		uपूर्णांक32_t reg;
		अगर (i < 8)
			reg = VM_CONTEXT0_PAGE_TABLE_BASE_ADDR + i ;
		अन्यथा
			reg = VM_CONTEXT8_PAGE_TABLE_BASE_ADDR + (i - 8);
		adev->vm_manager.saved_table_addr[i] = RREG32(reg);
	पूर्ण*/

	/* Disable all tables */
	WREG32(mmVM_CONTEXT0_CNTL, 0);
	WREG32(mmVM_CONTEXT1_CNTL, 0);
	/* Setup TLB control */
	WREG32(mmMC_VM_MX_L1_TLB_CNTL,
	       MC_VM_MX_L1_TLB_CNTL__SYSTEM_ACCESS_MODE_MASK |
	       (0UL << MC_VM_MX_L1_TLB_CNTL__SYSTEM_APERTURE_UNMAPPED_ACCESS__SHIFT));
	/* Setup L2 cache */
	WREG32(mmVM_L2_CNTL,
	       VM_L2_CNTL__ENABLE_L2_PTE_CACHE_LRU_UPDATE_BY_WRITE_MASK |
	       VM_L2_CNTL__ENABLE_L2_PDE0_CACHE_LRU_UPDATE_BY_WRITE_MASK |
	       (7UL << VM_L2_CNTL__EFFECTIVE_L2_QUEUE_SIZE__SHIFT) |
	       (1UL << VM_L2_CNTL__CONTEXT1_IDENTITY_ACCESS_MODE__SHIFT));
	WREG32(mmVM_L2_CNTL2, 0);
	WREG32(mmVM_L2_CNTL3,
	       VM_L2_CNTL3__L2_CACHE_BIGK_ASSOCIATIVITY_MASK |
	       (0UL << VM_L2_CNTL3__L2_CACHE_BIGK_FRAGMENT_SIZE__SHIFT));
	amdgpu_gart_table_vram_unpin(adev);
पूर्ण

अटल व्योम gmc_v6_0_vm_decode_fault(काष्ठा amdgpu_device *adev,
				     u32 status, u32 addr, u32 mc_client)
अणु
	u32 mc_id;
	u32 vmid = REG_GET_FIELD(status, VM_CONTEXT1_PROTECTION_FAULT_STATUS, VMID);
	u32 protections = REG_GET_FIELD(status, VM_CONTEXT1_PROTECTION_FAULT_STATUS,
					PROTECTIONS);
	अक्षर block[5] = अणु mc_client >> 24, (mc_client >> 16) & 0xff,
		(mc_client >> 8) & 0xff, mc_client & 0xff, 0 पूर्ण;

	mc_id = REG_GET_FIELD(status, VM_CONTEXT1_PROTECTION_FAULT_STATUS,
			      MEMORY_CLIENT_ID);

	dev_err(adev->dev, "VM fault (0x%02x, vmid %d) at page %u, %s from '%s' (0x%08x) (%d)\n",
	       protections, vmid, addr,
	       REG_GET_FIELD(status, VM_CONTEXT1_PROTECTION_FAULT_STATUS,
			     MEMORY_CLIENT_RW) ?
	       "write" : "read", block, mc_client, mc_id);
पूर्ण

/*
अटल स्थिर u32 mc_cg_रेजिस्टरs[] = अणु
	MC_HUB_MISC_HUB_CG,
	MC_HUB_MISC_SIP_CG,
	MC_HUB_MISC_VM_CG,
	MC_XPB_CLK_GAT,
	ATC_MISC_CG,
	MC_CITF_MISC_WR_CG,
	MC_CITF_MISC_RD_CG,
	MC_CITF_MISC_VM_CG,
	VM_L2_CG,
पूर्ण;

अटल स्थिर u32 mc_cg_ls_en[] = अणु
	MC_HUB_MISC_HUB_CG__MEM_LS_ENABLE_MASK,
	MC_HUB_MISC_SIP_CG__MEM_LS_ENABLE_MASK,
	MC_HUB_MISC_VM_CG__MEM_LS_ENABLE_MASK,
	MC_XPB_CLK_GAT__MEM_LS_ENABLE_MASK,
	ATC_MISC_CG__MEM_LS_ENABLE_MASK,
	MC_CITF_MISC_WR_CG__MEM_LS_ENABLE_MASK,
	MC_CITF_MISC_RD_CG__MEM_LS_ENABLE_MASK,
	MC_CITF_MISC_VM_CG__MEM_LS_ENABLE_MASK,
	VM_L2_CG__MEM_LS_ENABLE_MASK,
पूर्ण;

अटल स्थिर u32 mc_cg_en[] = अणु
	MC_HUB_MISC_HUB_CG__ENABLE_MASK,
	MC_HUB_MISC_SIP_CG__ENABLE_MASK,
	MC_HUB_MISC_VM_CG__ENABLE_MASK,
	MC_XPB_CLK_GAT__ENABLE_MASK,
	ATC_MISC_CG__ENABLE_MASK,
	MC_CITF_MISC_WR_CG__ENABLE_MASK,
	MC_CITF_MISC_RD_CG__ENABLE_MASK,
	MC_CITF_MISC_VM_CG__ENABLE_MASK,
	VM_L2_CG__ENABLE_MASK,
पूर्ण;

अटल व्योम gmc_v6_0_enable_mc_ls(काष्ठा amdgpu_device *adev,
				  bool enable)
अणु
	पूर्णांक i;
	u32 orig, data;

	क्रम (i = 0; i < ARRAY_SIZE(mc_cg_रेजिस्टरs); i++) अणु
		orig = data = RREG32(mc_cg_रेजिस्टरs[i]);
		अगर (enable && (adev->cg_flags & AMDGPU_CG_SUPPORT_MC_LS))
			data |= mc_cg_ls_en[i];
		अन्यथा
			data &= ~mc_cg_ls_en[i];
		अगर (data != orig)
			WREG32(mc_cg_रेजिस्टरs[i], data);
	पूर्ण
पूर्ण

अटल व्योम gmc_v6_0_enable_mc_mgcg(काष्ठा amdgpu_device *adev,
				    bool enable)
अणु
	पूर्णांक i;
	u32 orig, data;

	क्रम (i = 0; i < ARRAY_SIZE(mc_cg_रेजिस्टरs); i++) अणु
		orig = data = RREG32(mc_cg_रेजिस्टरs[i]);
		अगर (enable && (adev->cg_flags & AMDGPU_CG_SUPPORT_MC_MGCG))
			data |= mc_cg_en[i];
		अन्यथा
			data &= ~mc_cg_en[i];
		अगर (data != orig)
			WREG32(mc_cg_रेजिस्टरs[i], data);
	पूर्ण
पूर्ण

अटल व्योम gmc_v6_0_enable_bअगर_mgls(काष्ठा amdgpu_device *adev,
				     bool enable)
अणु
	u32 orig, data;

	orig = data = RREG32_PCIE(ixPCIE_CNTL2);

	अगर (enable && (adev->cg_flags & AMDGPU_CG_SUPPORT_BIF_LS)) अणु
		data = REG_SET_FIELD(data, PCIE_CNTL2, SLV_MEM_LS_EN, 1);
		data = REG_SET_FIELD(data, PCIE_CNTL2, MST_MEM_LS_EN, 1);
		data = REG_SET_FIELD(data, PCIE_CNTL2, REPLAY_MEM_LS_EN, 1);
		data = REG_SET_FIELD(data, PCIE_CNTL2, SLV_MEM_AGGRESSIVE_LS_EN, 1);
	पूर्ण अन्यथा अणु
		data = REG_SET_FIELD(data, PCIE_CNTL2, SLV_MEM_LS_EN, 0);
		data = REG_SET_FIELD(data, PCIE_CNTL2, MST_MEM_LS_EN, 0);
		data = REG_SET_FIELD(data, PCIE_CNTL2, REPLAY_MEM_LS_EN, 0);
		data = REG_SET_FIELD(data, PCIE_CNTL2, SLV_MEM_AGGRESSIVE_LS_EN, 0);
	पूर्ण

	अगर (orig != data)
		WREG32_PCIE(ixPCIE_CNTL2, data);
पूर्ण

अटल व्योम gmc_v6_0_enable_hdp_mgcg(काष्ठा amdgpu_device *adev,
				     bool enable)
अणु
	u32 orig, data;

	orig = data = RREG32(mmHDP_HOST_PATH_CNTL);

	अगर (enable && (adev->cg_flags & AMDGPU_CG_SUPPORT_HDP_MGCG))
		data = REG_SET_FIELD(data, HDP_HOST_PATH_CNTL, CLOCK_GATING_DIS, 0);
	अन्यथा
		data = REG_SET_FIELD(data, HDP_HOST_PATH_CNTL, CLOCK_GATING_DIS, 1);

	अगर (orig != data)
		WREG32(mmHDP_HOST_PATH_CNTL, data);
पूर्ण

अटल व्योम gmc_v6_0_enable_hdp_ls(काष्ठा amdgpu_device *adev,
				   bool enable)
अणु
	u32 orig, data;

	orig = data = RREG32(mmHDP_MEM_POWER_LS);

	अगर (enable && (adev->cg_flags & AMDGPU_CG_SUPPORT_HDP_LS))
		data = REG_SET_FIELD(data, HDP_MEM_POWER_LS, LS_ENABLE, 1);
	अन्यथा
		data = REG_SET_FIELD(data, HDP_MEM_POWER_LS, LS_ENABLE, 0);

	अगर (orig != data)
		WREG32(mmHDP_MEM_POWER_LS, data);
पूर्ण
*/

अटल पूर्णांक gmc_v6_0_convert_vram_type(पूर्णांक mc_seq_vram_type)
अणु
	चयन (mc_seq_vram_type) अणु
	हाल MC_SEQ_MISC0__MT__GDDR1:
		वापस AMDGPU_VRAM_TYPE_GDDR1;
	हाल MC_SEQ_MISC0__MT__DDR2:
		वापस AMDGPU_VRAM_TYPE_DDR2;
	हाल MC_SEQ_MISC0__MT__GDDR3:
		वापस AMDGPU_VRAM_TYPE_GDDR3;
	हाल MC_SEQ_MISC0__MT__GDDR4:
		वापस AMDGPU_VRAM_TYPE_GDDR4;
	हाल MC_SEQ_MISC0__MT__GDDR5:
		वापस AMDGPU_VRAM_TYPE_GDDR5;
	हाल MC_SEQ_MISC0__MT__DDR3:
		वापस AMDGPU_VRAM_TYPE_DDR3;
	शेष:
		वापस AMDGPU_VRAM_TYPE_UNKNOWN;
	पूर्ण
पूर्ण

अटल पूर्णांक gmc_v6_0_early_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	gmc_v6_0_set_gmc_funcs(adev);
	gmc_v6_0_set_irq_funcs(adev);

	वापस 0;
पूर्ण

अटल पूर्णांक gmc_v6_0_late_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	अगर (amdgpu_vm_fault_stop != AMDGPU_VM_FAULT_STOP_ALWAYS)
		वापस amdgpu_irq_get(adev, &adev->gmc.vm_fault, 0);
	अन्यथा
		वापस 0;
पूर्ण

अटल अचिन्हित gmc_v6_0_get_vbios_fb_size(काष्ठा amdgpu_device *adev)
अणु
	u32 d1vga_control = RREG32(mmD1VGA_CONTROL);
	अचिन्हित size;

	अगर (REG_GET_FIELD(d1vga_control, D1VGA_CONTROL, D1VGA_MODE_ENABLE)) अणु
		size = AMDGPU_VBIOS_VGA_ALLOCATION;
	पूर्ण अन्यथा अणु
		u32 viewport = RREG32(mmVIEWPORT_SIZE);
		size = (REG_GET_FIELD(viewport, VIEWPORT_SIZE, VIEWPORT_HEIGHT) *
			REG_GET_FIELD(viewport, VIEWPORT_SIZE, VIEWPORT_WIDTH) *
			4);
	पूर्ण
	वापस size;
पूर्ण

अटल पूर्णांक gmc_v6_0_sw_init(व्योम *handle)
अणु
	पूर्णांक r;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	adev->num_vmhubs = 1;

	अगर (adev->flags & AMD_IS_APU) अणु
		adev->gmc.vram_type = AMDGPU_VRAM_TYPE_UNKNOWN;
	पूर्ण अन्यथा अणु
		u32 पंचांगp = RREG32(mmMC_SEQ_MISC0);
		पंचांगp &= MC_SEQ_MISC0__MT__MASK;
		adev->gmc.vram_type = gmc_v6_0_convert_vram_type(पंचांगp);
	पूर्ण

	r = amdgpu_irq_add_id(adev, AMDGPU_IRQ_CLIENTID_LEGACY, 146, &adev->gmc.vm_fault);
	अगर (r)
		वापस r;

	r = amdgpu_irq_add_id(adev, AMDGPU_IRQ_CLIENTID_LEGACY, 147, &adev->gmc.vm_fault);
	अगर (r)
		वापस r;

	amdgpu_vm_adjust_size(adev, 64, 9, 1, 40);

	adev->gmc.mc_mask = 0xffffffffffULL;

	r = dma_set_mask_and_coherent(adev->dev, DMA_BIT_MASK(44));
	अगर (r) अणु
		dev_warn(adev->dev, "No suitable DMA available.\n");
		वापस r;
	पूर्ण
	adev->need_swiotlb = drm_need_swiotlb(44);

	r = gmc_v6_0_init_microcode(adev);
	अगर (r) अणु
		dev_err(adev->dev, "Failed to load mc firmware!\n");
		वापस r;
	पूर्ण

	r = gmc_v6_0_mc_init(adev);
	अगर (r)
		वापस r;

	amdgpu_gmc_get_vbios_allocations(adev);

	r = amdgpu_bo_init(adev);
	अगर (r)
		वापस r;

	r = gmc_v6_0_gart_init(adev);
	अगर (r)
		वापस r;

	/*
	 * number of VMs
	 * VMID 0 is reserved क्रम System
	 * amdgpu graphics/compute will use VMIDs 1-7
	 * amdkfd will use VMIDs 8-15
	 */
	adev->vm_manager.first_kfd_vmid = 8;
	amdgpu_vm_manager_init(adev);

	/* base offset of vram pages */
	अगर (adev->flags & AMD_IS_APU) अणु
		u64 पंचांगp = RREG32(mmMC_VM_FB_OFFSET);

		पंचांगp <<= 22;
		adev->vm_manager.vram_base_offset = पंचांगp;
	पूर्ण अन्यथा अणु
		adev->vm_manager.vram_base_offset = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gmc_v6_0_sw_fini(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	amdgpu_gem_क्रमce_release(adev);
	amdgpu_vm_manager_fini(adev);
	amdgpu_gart_table_vram_मुक्त(adev);
	amdgpu_bo_fini(adev);
	amdgpu_gart_fini(adev);
	release_firmware(adev->gmc.fw);
	adev->gmc.fw = शून्य;

	वापस 0;
पूर्ण

अटल पूर्णांक gmc_v6_0_hw_init(व्योम *handle)
अणु
	पूर्णांक r;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	gmc_v6_0_mc_program(adev);

	अगर (!(adev->flags & AMD_IS_APU)) अणु
		r = gmc_v6_0_mc_load_microcode(adev);
		अगर (r) अणु
			dev_err(adev->dev, "Failed to load MC firmware!\n");
			वापस r;
		पूर्ण
	पूर्ण

	r = gmc_v6_0_gart_enable(adev);
	अगर (r)
		वापस r;

	वापस r;
पूर्ण

अटल पूर्णांक gmc_v6_0_hw_fini(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	amdgpu_irq_put(adev, &adev->gmc.vm_fault, 0);
	gmc_v6_0_gart_disable(adev);

	वापस 0;
पूर्ण

अटल पूर्णांक gmc_v6_0_suspend(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	gmc_v6_0_hw_fini(adev);

	वापस 0;
पूर्ण

अटल पूर्णांक gmc_v6_0_resume(व्योम *handle)
अणु
	पूर्णांक r;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	r = gmc_v6_0_hw_init(adev);
	अगर (r)
		वापस r;

	amdgpu_vmid_reset_all(adev);

	वापस 0;
पूर्ण

अटल bool gmc_v6_0_is_idle(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	u32 पंचांगp = RREG32(mmSRBM_STATUS);

	अगर (पंचांगp & (SRBM_STATUS__MCB_BUSY_MASK | SRBM_STATUS__MCB_NON_DISPLAY_BUSY_MASK |
		   SRBM_STATUS__MCC_BUSY_MASK | SRBM_STATUS__MCD_BUSY_MASK | SRBM_STATUS__VMC_BUSY_MASK))
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक gmc_v6_0_रुको_क्रम_idle(व्योम *handle)
अणु
	अचिन्हित i;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	क्रम (i = 0; i < adev->usec_समयout; i++) अणु
		अगर (gmc_v6_0_is_idle(handle))
			वापस 0;
		udelay(1);
	पूर्ण
	वापस -ETIMEDOUT;

पूर्ण

अटल पूर्णांक gmc_v6_0_soft_reset(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	u32 srbm_soft_reset = 0;
	u32 पंचांगp = RREG32(mmSRBM_STATUS);

	अगर (पंचांगp & SRBM_STATUS__VMC_BUSY_MASK)
		srbm_soft_reset = REG_SET_FIELD(srbm_soft_reset,
						SRBM_SOFT_RESET, SOFT_RESET_VMC, 1);

	अगर (पंचांगp & (SRBM_STATUS__MCB_BUSY_MASK | SRBM_STATUS__MCB_NON_DISPLAY_BUSY_MASK |
		   SRBM_STATUS__MCC_BUSY_MASK | SRBM_STATUS__MCD_BUSY_MASK)) अणु
		अगर (!(adev->flags & AMD_IS_APU))
			srbm_soft_reset = REG_SET_FIELD(srbm_soft_reset,
							SRBM_SOFT_RESET, SOFT_RESET_MC, 1);
	पूर्ण

	अगर (srbm_soft_reset) अणु
		gmc_v6_0_mc_stop(adev);
		अगर (gmc_v6_0_रुको_क्रम_idle(adev)) अणु
			dev_warn(adev->dev, "Wait for GMC idle timed out !\n");
		पूर्ण


		पंचांगp = RREG32(mmSRBM_SOFT_RESET);
		पंचांगp |= srbm_soft_reset;
		dev_info(adev->dev, "SRBM_SOFT_RESET=0x%08X\n", पंचांगp);
		WREG32(mmSRBM_SOFT_RESET, पंचांगp);
		पंचांगp = RREG32(mmSRBM_SOFT_RESET);

		udelay(50);

		पंचांगp &= ~srbm_soft_reset;
		WREG32(mmSRBM_SOFT_RESET, पंचांगp);
		पंचांगp = RREG32(mmSRBM_SOFT_RESET);

		udelay(50);

		gmc_v6_0_mc_resume(adev);
		udelay(50);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gmc_v6_0_vm_fault_पूर्णांकerrupt_state(काष्ठा amdgpu_device *adev,
					     काष्ठा amdgpu_irq_src *src,
					     अचिन्हित type,
					     क्रमागत amdgpu_पूर्णांकerrupt_state state)
अणु
	u32 पंचांगp;
	u32 bits = (VM_CONTEXT1_CNTL__RANGE_PROTECTION_FAULT_ENABLE_INTERRUPT_MASK |
		    VM_CONTEXT1_CNTL__DUMMY_PAGE_PROTECTION_FAULT_ENABLE_INTERRUPT_MASK |
		    VM_CONTEXT1_CNTL__PDE0_PROTECTION_FAULT_ENABLE_INTERRUPT_MASK |
		    VM_CONTEXT1_CNTL__VALID_PROTECTION_FAULT_ENABLE_INTERRUPT_MASK |
		    VM_CONTEXT1_CNTL__READ_PROTECTION_FAULT_ENABLE_INTERRUPT_MASK |
		    VM_CONTEXT1_CNTL__WRITE_PROTECTION_FAULT_ENABLE_INTERRUPT_MASK);

	चयन (state) अणु
	हाल AMDGPU_IRQ_STATE_DISABLE:
		पंचांगp = RREG32(mmVM_CONTEXT0_CNTL);
		पंचांगp &= ~bits;
		WREG32(mmVM_CONTEXT0_CNTL, पंचांगp);
		पंचांगp = RREG32(mmVM_CONTEXT1_CNTL);
		पंचांगp &= ~bits;
		WREG32(mmVM_CONTEXT1_CNTL, पंचांगp);
		अवरोध;
	हाल AMDGPU_IRQ_STATE_ENABLE:
		पंचांगp = RREG32(mmVM_CONTEXT0_CNTL);
		पंचांगp |= bits;
		WREG32(mmVM_CONTEXT0_CNTL, पंचांगp);
		पंचांगp = RREG32(mmVM_CONTEXT1_CNTL);
		पंचांगp |= bits;
		WREG32(mmVM_CONTEXT1_CNTL, पंचांगp);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gmc_v6_0_process_पूर्णांकerrupt(काष्ठा amdgpu_device *adev,
				      काष्ठा amdgpu_irq_src *source,
				      काष्ठा amdgpu_iv_entry *entry)
अणु
	u32 addr, status;

	addr = RREG32(mmVM_CONTEXT1_PROTECTION_FAULT_ADDR);
	status = RREG32(mmVM_CONTEXT1_PROTECTION_FAULT_STATUS);
	WREG32_P(mmVM_CONTEXT1_CNTL2, 1, ~1);

	अगर (!addr && !status)
		वापस 0;

	अगर (amdgpu_vm_fault_stop == AMDGPU_VM_FAULT_STOP_FIRST)
		gmc_v6_0_set_fault_enable_शेष(adev, false);

	अगर (prपूर्णांकk_ratelimit()) अणु
		dev_err(adev->dev, "GPU fault detected: %d 0x%08x\n",
			entry->src_id, entry->src_data[0]);
		dev_err(adev->dev, "  VM_CONTEXT1_PROTECTION_FAULT_ADDR   0x%08X\n",
			addr);
		dev_err(adev->dev, "  VM_CONTEXT1_PROTECTION_FAULT_STATUS 0x%08X\n",
			status);
		gmc_v6_0_vm_decode_fault(adev, status, addr, 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gmc_v6_0_set_घड़ीgating_state(व्योम *handle,
					  क्रमागत amd_घड़ीgating_state state)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक gmc_v6_0_set_घातergating_state(व्योम *handle,
					  क्रमागत amd_घातergating_state state)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा amd_ip_funcs gmc_v6_0_ip_funcs = अणु
	.name = "gmc_v6_0",
	.early_init = gmc_v6_0_early_init,
	.late_init = gmc_v6_0_late_init,
	.sw_init = gmc_v6_0_sw_init,
	.sw_fini = gmc_v6_0_sw_fini,
	.hw_init = gmc_v6_0_hw_init,
	.hw_fini = gmc_v6_0_hw_fini,
	.suspend = gmc_v6_0_suspend,
	.resume = gmc_v6_0_resume,
	.is_idle = gmc_v6_0_is_idle,
	.रुको_क्रम_idle = gmc_v6_0_रुको_क्रम_idle,
	.soft_reset = gmc_v6_0_soft_reset,
	.set_घड़ीgating_state = gmc_v6_0_set_घड़ीgating_state,
	.set_घातergating_state = gmc_v6_0_set_घातergating_state,
पूर्ण;

अटल स्थिर काष्ठा amdgpu_gmc_funcs gmc_v6_0_gmc_funcs = अणु
	.flush_gpu_tlb = gmc_v6_0_flush_gpu_tlb,
	.emit_flush_gpu_tlb = gmc_v6_0_emit_flush_gpu_tlb,
	.set_prt = gmc_v6_0_set_prt,
	.get_vm_pde = gmc_v6_0_get_vm_pde,
	.get_vm_pte = gmc_v6_0_get_vm_pte,
	.get_vbios_fb_size = gmc_v6_0_get_vbios_fb_size,
पूर्ण;

अटल स्थिर काष्ठा amdgpu_irq_src_funcs gmc_v6_0_irq_funcs = अणु
	.set = gmc_v6_0_vm_fault_पूर्णांकerrupt_state,
	.process = gmc_v6_0_process_पूर्णांकerrupt,
पूर्ण;

अटल व्योम gmc_v6_0_set_gmc_funcs(काष्ठा amdgpu_device *adev)
अणु
	adev->gmc.gmc_funcs = &gmc_v6_0_gmc_funcs;
पूर्ण

अटल व्योम gmc_v6_0_set_irq_funcs(काष्ठा amdgpu_device *adev)
अणु
	adev->gmc.vm_fault.num_types = 1;
	adev->gmc.vm_fault.funcs = &gmc_v6_0_irq_funcs;
पूर्ण

स्थिर काष्ठा amdgpu_ip_block_version gmc_v6_0_ip_block =
अणु
	.type = AMD_IP_BLOCK_TYPE_GMC,
	.major = 6,
	.minor = 0,
	.rev = 0,
	.funcs = &gmc_v6_0_ip_funcs,
पूर्ण;
