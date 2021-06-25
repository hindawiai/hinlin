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
#समावेश "gmc_v8_0.h"
#समावेश "amdgpu_ucode.h"
#समावेश "amdgpu_amdkfd.h"
#समावेश "amdgpu_gem.h"

#समावेश "gmc/gmc_8_1_d.h"
#समावेश "gmc/gmc_8_1_sh_mask.h"

#समावेश "bif/bif_5_0_d.h"
#समावेश "bif/bif_5_0_sh_mask.h"

#समावेश "oss/oss_3_0_d.h"
#समावेश "oss/oss_3_0_sh_mask.h"

#समावेश "dce/dce_10_0_d.h"
#समावेश "dce/dce_10_0_sh_mask.h"

#समावेश "vid.h"
#समावेश "vi.h"

#समावेश "amdgpu_atombios.h"

#समावेश "ivsrcid/ivsrcid_vislands30.h"

अटल व्योम gmc_v8_0_set_gmc_funcs(काष्ठा amdgpu_device *adev);
अटल व्योम gmc_v8_0_set_irq_funcs(काष्ठा amdgpu_device *adev);
अटल पूर्णांक gmc_v8_0_रुको_क्रम_idle(व्योम *handle);

MODULE_FIRMWARE("amdgpu/tonga_mc.bin");
MODULE_FIRMWARE("amdgpu/polaris11_mc.bin");
MODULE_FIRMWARE("amdgpu/polaris10_mc.bin");
MODULE_FIRMWARE("amdgpu/polaris12_mc.bin");
MODULE_FIRMWARE("amdgpu/polaris12_32_mc.bin");
MODULE_FIRMWARE("amdgpu/polaris11_k_mc.bin");
MODULE_FIRMWARE("amdgpu/polaris10_k_mc.bin");
MODULE_FIRMWARE("amdgpu/polaris12_k_mc.bin");

अटल स्थिर u32 golden_settings_tonga_a11[] =
अणु
	mmMC_ARB_WTM_GRPWT_RD, 0x00000003, 0x00000000,
	mmMC_HUB_RDREQ_DMIF_LIMIT, 0x0000007f, 0x00000028,
	mmMC_HUB_WDP_UMC, 0x00007fb6, 0x00000991,
	mmVM_PRT_APERTURE0_LOW_ADDR, 0x0fffffff, 0x0fffffff,
	mmVM_PRT_APERTURE1_LOW_ADDR, 0x0fffffff, 0x0fffffff,
	mmVM_PRT_APERTURE2_LOW_ADDR, 0x0fffffff, 0x0fffffff,
	mmVM_PRT_APERTURE3_LOW_ADDR, 0x0fffffff, 0x0fffffff,
पूर्ण;

अटल स्थिर u32 tonga_mgcg_cgcg_init[] =
अणु
	mmMC_MEM_POWER_LS, 0xffffffff, 0x00000104
पूर्ण;

अटल स्थिर u32 golden_settings_fiji_a10[] =
अणु
	mmVM_PRT_APERTURE0_LOW_ADDR, 0x0fffffff, 0x0fffffff,
	mmVM_PRT_APERTURE1_LOW_ADDR, 0x0fffffff, 0x0fffffff,
	mmVM_PRT_APERTURE2_LOW_ADDR, 0x0fffffff, 0x0fffffff,
	mmVM_PRT_APERTURE3_LOW_ADDR, 0x0fffffff, 0x0fffffff,
पूर्ण;

अटल स्थिर u32 fiji_mgcg_cgcg_init[] =
अणु
	mmMC_MEM_POWER_LS, 0xffffffff, 0x00000104
पूर्ण;

अटल स्थिर u32 golden_settings_polaris11_a11[] =
अणु
	mmVM_PRT_APERTURE0_LOW_ADDR, 0x0fffffff, 0x0fffffff,
	mmVM_PRT_APERTURE1_LOW_ADDR, 0x0fffffff, 0x0fffffff,
	mmVM_PRT_APERTURE2_LOW_ADDR, 0x0fffffff, 0x0fffffff,
	mmVM_PRT_APERTURE3_LOW_ADDR, 0x0fffffff, 0x0fffffff
पूर्ण;

अटल स्थिर u32 golden_settings_polaris10_a11[] =
अणु
	mmMC_ARB_WTM_GRPWT_RD, 0x00000003, 0x00000000,
	mmVM_PRT_APERTURE0_LOW_ADDR, 0x0fffffff, 0x0fffffff,
	mmVM_PRT_APERTURE1_LOW_ADDR, 0x0fffffff, 0x0fffffff,
	mmVM_PRT_APERTURE2_LOW_ADDR, 0x0fffffff, 0x0fffffff,
	mmVM_PRT_APERTURE3_LOW_ADDR, 0x0fffffff, 0x0fffffff
पूर्ण;

अटल स्थिर u32 cz_mgcg_cgcg_init[] =
अणु
	mmMC_MEM_POWER_LS, 0xffffffff, 0x00000104
पूर्ण;

अटल स्थिर u32 stoney_mgcg_cgcg_init[] =
अणु
	mmATC_MISC_CG, 0xffffffff, 0x000c0200,
	mmMC_MEM_POWER_LS, 0xffffffff, 0x00000104
पूर्ण;

अटल स्थिर u32 golden_settings_stoney_common[] =
अणु
	mmMC_HUB_RDREQ_UVD, MC_HUB_RDREQ_UVD__PRESCALE_MASK, 0x00000004,
	mmMC_RD_GRP_OTH, MC_RD_GRP_OTH__UVD_MASK, 0x00600000
पूर्ण;

अटल व्योम gmc_v8_0_init_golden_रेजिस्टरs(काष्ठा amdgpu_device *adev)
अणु
	चयन (adev->asic_type) अणु
	हाल CHIP_FIJI:
		amdgpu_device_program_रेजिस्टर_sequence(adev,
							fiji_mgcg_cgcg_init,
							ARRAY_SIZE(fiji_mgcg_cgcg_init));
		amdgpu_device_program_रेजिस्टर_sequence(adev,
							golden_settings_fiji_a10,
							ARRAY_SIZE(golden_settings_fiji_a10));
		अवरोध;
	हाल CHIP_TONGA:
		amdgpu_device_program_रेजिस्टर_sequence(adev,
							tonga_mgcg_cgcg_init,
							ARRAY_SIZE(tonga_mgcg_cgcg_init));
		amdgpu_device_program_रेजिस्टर_sequence(adev,
							golden_settings_tonga_a11,
							ARRAY_SIZE(golden_settings_tonga_a11));
		अवरोध;
	हाल CHIP_POLARIS11:
	हाल CHIP_POLARIS12:
	हाल CHIP_VEGAM:
		amdgpu_device_program_रेजिस्टर_sequence(adev,
							golden_settings_polaris11_a11,
							ARRAY_SIZE(golden_settings_polaris11_a11));
		अवरोध;
	हाल CHIP_POLARIS10:
		amdgpu_device_program_रेजिस्टर_sequence(adev,
							golden_settings_polaris10_a11,
							ARRAY_SIZE(golden_settings_polaris10_a11));
		अवरोध;
	हाल CHIP_CARRIZO:
		amdgpu_device_program_रेजिस्टर_sequence(adev,
							cz_mgcg_cgcg_init,
							ARRAY_SIZE(cz_mgcg_cgcg_init));
		अवरोध;
	हाल CHIP_STONEY:
		amdgpu_device_program_रेजिस्टर_sequence(adev,
							stoney_mgcg_cgcg_init,
							ARRAY_SIZE(stoney_mgcg_cgcg_init));
		amdgpu_device_program_रेजिस्टर_sequence(adev,
							golden_settings_stoney_common,
							ARRAY_SIZE(golden_settings_stoney_common));
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम gmc_v8_0_mc_stop(काष्ठा amdgpu_device *adev)
अणु
	u32 blackout;

	gmc_v8_0_रुको_क्रम_idle(adev);

	blackout = RREG32(mmMC_SHARED_BLACKOUT_CNTL);
	अगर (REG_GET_FIELD(blackout, MC_SHARED_BLACKOUT_CNTL, BLACKOUT_MODE) != 1) अणु
		/* Block CPU access */
		WREG32(mmBIF_FB_EN, 0);
		/* blackout the MC */
		blackout = REG_SET_FIELD(blackout,
					 MC_SHARED_BLACKOUT_CNTL, BLACKOUT_MODE, 1);
		WREG32(mmMC_SHARED_BLACKOUT_CNTL, blackout);
	पूर्ण
	/* रुको क्रम the MC to settle */
	udelay(100);
पूर्ण

अटल व्योम gmc_v8_0_mc_resume(काष्ठा amdgpu_device *adev)
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

/**
 * gmc_v8_0_init_microcode - load ucode images from disk
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Use the firmware पूर्णांकerface to load the ucode images पूर्णांकo
 * the driver (not loaded पूर्णांकo hw).
 * Returns 0 on success, error on failure.
 */
अटल पूर्णांक gmc_v8_0_init_microcode(काष्ठा amdgpu_device *adev)
अणु
	स्थिर अक्षर *chip_name;
	अक्षर fw_name[30];
	पूर्णांक err;

	DRM_DEBUG("\n");

	चयन (adev->asic_type) अणु
	हाल CHIP_TONGA:
		chip_name = "tonga";
		अवरोध;
	हाल CHIP_POLARIS11:
		अगर (ASICID_IS_P21(adev->pdev->device, adev->pdev->revision) ||
		    ASICID_IS_P31(adev->pdev->device, adev->pdev->revision))
			chip_name = "polaris11_k";
		अन्यथा
			chip_name = "polaris11";
		अवरोध;
	हाल CHIP_POLARIS10:
		अगर (ASICID_IS_P30(adev->pdev->device, adev->pdev->revision))
			chip_name = "polaris10_k";
		अन्यथा
			chip_name = "polaris10";
		अवरोध;
	हाल CHIP_POLARIS12:
		अगर (ASICID_IS_P23(adev->pdev->device, adev->pdev->revision)) अणु
			chip_name = "polaris12_k";
		पूर्ण अन्यथा अणु
			WREG32(mmMC_SEQ_IO_DEBUG_INDEX, ixMC_IO_DEBUG_UP_159);
			/* Polaris12 32bit ASIC needs a special MC firmware */
			अगर (RREG32(mmMC_SEQ_IO_DEBUG_DATA) == 0x05b4dc40)
				chip_name = "polaris12_32";
			अन्यथा
				chip_name = "polaris12";
		पूर्ण
		अवरोध;
	हाल CHIP_FIJI:
	हाल CHIP_CARRIZO:
	हाल CHIP_STONEY:
	हाल CHIP_VEGAM:
		वापस 0;
	शेष: BUG();
	पूर्ण

	snम_लिखो(fw_name, माप(fw_name), "amdgpu/%s_mc.bin", chip_name);
	err = request_firmware(&adev->gmc.fw, fw_name, adev->dev);
	अगर (err)
		जाओ out;
	err = amdgpu_ucode_validate(adev->gmc.fw);

out:
	अगर (err) अणु
		pr_err("mc: Failed to load firmware \"%s\"\n", fw_name);
		release_firmware(adev->gmc.fw);
		adev->gmc.fw = शून्य;
	पूर्ण
	वापस err;
पूर्ण

/**
 * gmc_v8_0_tonga_mc_load_microcode - load tonga MC ucode पूर्णांकo the hw
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Load the GDDR MC ucode पूर्णांकo the hw (VI).
 * Returns 0 on success, error on failure.
 */
अटल पूर्णांक gmc_v8_0_tonga_mc_load_microcode(काष्ठा amdgpu_device *adev)
अणु
	स्थिर काष्ठा mc_firmware_header_v1_0 *hdr;
	स्थिर __le32 *fw_data = शून्य;
	स्थिर __le32 *io_mc_regs = शून्य;
	u32 running;
	पूर्णांक i, ucode_size, regs_size;

	/* Skip MC ucode loading on SR-IOV capable boards.
	 * vbios करोes this क्रम us in asic_init in that हाल.
	 * Skip MC ucode loading on VF, because hypervisor will करो that
	 * क्रम this adaptor.
	 */
	अगर (amdgpu_sriov_bios(adev))
		वापस 0;

	अगर (!adev->gmc.fw)
		वापस -EINVAL;

	hdr = (स्थिर काष्ठा mc_firmware_header_v1_0 *)adev->gmc.fw->data;
	amdgpu_ucode_prपूर्णांक_mc_hdr(&hdr->header);

	adev->gmc.fw_version = le32_to_cpu(hdr->header.ucode_version);
	regs_size = le32_to_cpu(hdr->io_debug_size_bytes) / (4 * 2);
	io_mc_regs = (स्थिर __le32 *)
		(adev->gmc.fw->data + le32_to_cpu(hdr->io_debug_array_offset_bytes));
	ucode_size = le32_to_cpu(hdr->header.ucode_size_bytes) / 4;
	fw_data = (स्थिर __le32 *)
		(adev->gmc.fw->data + le32_to_cpu(hdr->header.ucode_array_offset_bytes));

	running = REG_GET_FIELD(RREG32(mmMC_SEQ_SUP_CNTL), MC_SEQ_SUP_CNTL, RUN);

	अगर (running == 0) अणु
		/* reset the engine and set to writable */
		WREG32(mmMC_SEQ_SUP_CNTL, 0x00000008);
		WREG32(mmMC_SEQ_SUP_CNTL, 0x00000010);

		/* load mc io regs */
		क्रम (i = 0; i < regs_size; i++) अणु
			WREG32(mmMC_SEQ_IO_DEBUG_INDEX, le32_to_cpup(io_mc_regs++));
			WREG32(mmMC_SEQ_IO_DEBUG_DATA, le32_to_cpup(io_mc_regs++));
		पूर्ण
		/* load the MC ucode */
		क्रम (i = 0; i < ucode_size; i++)
			WREG32(mmMC_SEQ_SUP_PGM, le32_to_cpup(fw_data++));

		/* put the engine back पूर्णांकo the active state */
		WREG32(mmMC_SEQ_SUP_CNTL, 0x00000008);
		WREG32(mmMC_SEQ_SUP_CNTL, 0x00000004);
		WREG32(mmMC_SEQ_SUP_CNTL, 0x00000001);

		/* रुको क्रम training to complete */
		क्रम (i = 0; i < adev->usec_समयout; i++) अणु
			अगर (REG_GET_FIELD(RREG32(mmMC_SEQ_TRAIN_WAKEUP_CNTL),
					  MC_SEQ_TRAIN_WAKEUP_CNTL, TRAIN_DONE_D0))
				अवरोध;
			udelay(1);
		पूर्ण
		क्रम (i = 0; i < adev->usec_समयout; i++) अणु
			अगर (REG_GET_FIELD(RREG32(mmMC_SEQ_TRAIN_WAKEUP_CNTL),
					  MC_SEQ_TRAIN_WAKEUP_CNTL, TRAIN_DONE_D1))
				अवरोध;
			udelay(1);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gmc_v8_0_polaris_mc_load_microcode(काष्ठा amdgpu_device *adev)
अणु
	स्थिर काष्ठा mc_firmware_header_v1_0 *hdr;
	स्थिर __le32 *fw_data = शून्य;
	स्थिर __le32 *io_mc_regs = शून्य;
	u32 data;
	पूर्णांक i, ucode_size, regs_size;

	/* Skip MC ucode loading on SR-IOV capable boards.
	 * vbios करोes this क्रम us in asic_init in that हाल.
	 * Skip MC ucode loading on VF, because hypervisor will करो that
	 * क्रम this adaptor.
	 */
	अगर (amdgpu_sriov_bios(adev))
		वापस 0;

	अगर (!adev->gmc.fw)
		वापस -EINVAL;

	hdr = (स्थिर काष्ठा mc_firmware_header_v1_0 *)adev->gmc.fw->data;
	amdgpu_ucode_prपूर्णांक_mc_hdr(&hdr->header);

	adev->gmc.fw_version = le32_to_cpu(hdr->header.ucode_version);
	regs_size = le32_to_cpu(hdr->io_debug_size_bytes) / (4 * 2);
	io_mc_regs = (स्थिर __le32 *)
		(adev->gmc.fw->data + le32_to_cpu(hdr->io_debug_array_offset_bytes));
	ucode_size = le32_to_cpu(hdr->header.ucode_size_bytes) / 4;
	fw_data = (स्थिर __le32 *)
		(adev->gmc.fw->data + le32_to_cpu(hdr->header.ucode_array_offset_bytes));

	data = RREG32(mmMC_SEQ_MISC0);
	data &= ~(0x40);
	WREG32(mmMC_SEQ_MISC0, data);

	/* load mc io regs */
	क्रम (i = 0; i < regs_size; i++) अणु
		WREG32(mmMC_SEQ_IO_DEBUG_INDEX, le32_to_cpup(io_mc_regs++));
		WREG32(mmMC_SEQ_IO_DEBUG_DATA, le32_to_cpup(io_mc_regs++));
	पूर्ण

	WREG32(mmMC_SEQ_SUP_CNTL, 0x00000008);
	WREG32(mmMC_SEQ_SUP_CNTL, 0x00000010);

	/* load the MC ucode */
	क्रम (i = 0; i < ucode_size; i++)
		WREG32(mmMC_SEQ_SUP_PGM, le32_to_cpup(fw_data++));

	/* put the engine back पूर्णांकo the active state */
	WREG32(mmMC_SEQ_SUP_CNTL, 0x00000008);
	WREG32(mmMC_SEQ_SUP_CNTL, 0x00000004);
	WREG32(mmMC_SEQ_SUP_CNTL, 0x00000001);

	/* रुको क्रम training to complete */
	क्रम (i = 0; i < adev->usec_समयout; i++) अणु
		data = RREG32(mmMC_SEQ_MISC0);
		अगर (data & 0x80)
			अवरोध;
		udelay(1);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम gmc_v8_0_vram_gtt_location(काष्ठा amdgpu_device *adev,
				       काष्ठा amdgpu_gmc *mc)
अणु
	u64 base = 0;

	अगर (!amdgpu_sriov_vf(adev))
		base = RREG32(mmMC_VM_FB_LOCATION) & 0xFFFF;
	base <<= 24;

	amdgpu_gmc_vram_location(adev, mc, base);
	amdgpu_gmc_gart_location(adev, mc);
पूर्ण

/**
 * gmc_v8_0_mc_program - program the GPU memory controller
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Set the location of vram, gart, and AGP in the GPU's
 * physical address space (VI).
 */
अटल व्योम gmc_v8_0_mc_program(काष्ठा amdgpu_device *adev)
अणु
	u32 पंचांगp;
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

	अगर (gmc_v8_0_रुको_क्रम_idle((व्योम *)adev)) अणु
		dev_warn(adev->dev, "Wait for MC idle timedout !\n");
	पूर्ण
	अगर (adev->mode_info.num_crtc) अणु
		/* Lockout access through VGA aperture*/
		पंचांगp = RREG32(mmVGA_HDP_CONTROL);
		पंचांगp = REG_SET_FIELD(पंचांगp, VGA_HDP_CONTROL, VGA_MEMORY_DISABLE, 1);
		WREG32(mmVGA_HDP_CONTROL, पंचांगp);

		/* disable VGA render */
		पंचांगp = RREG32(mmVGA_RENDER_CONTROL);
		पंचांगp = REG_SET_FIELD(पंचांगp, VGA_RENDER_CONTROL, VGA_VSTATUS_CNTL, 0);
		WREG32(mmVGA_RENDER_CONTROL, पंचांगp);
	पूर्ण
	/* Update configuration */
	WREG32(mmMC_VM_SYSTEM_APERTURE_LOW_ADDR,
	       adev->gmc.vram_start >> 12);
	WREG32(mmMC_VM_SYSTEM_APERTURE_HIGH_ADDR,
	       adev->gmc.vram_end >> 12);
	WREG32(mmMC_VM_SYSTEM_APERTURE_DEFAULT_ADDR,
	       adev->vram_scratch.gpu_addr >> 12);

	अगर (amdgpu_sriov_vf(adev)) अणु
		पंचांगp = ((adev->gmc.vram_end >> 24) & 0xFFFF) << 16;
		पंचांगp |= ((adev->gmc.vram_start >> 24) & 0xFFFF);
		WREG32(mmMC_VM_FB_LOCATION, पंचांगp);
		/* XXX द्विगुन check these! */
		WREG32(mmHDP_NONSURFACE_BASE, (adev->gmc.vram_start >> 8));
		WREG32(mmHDP_NONSURFACE_INFO, (2 << 7) | (1 << 30));
		WREG32(mmHDP_NONSURFACE_SIZE, 0x3FFFFFFF);
	पूर्ण

	WREG32(mmMC_VM_AGP_BASE, 0);
	WREG32(mmMC_VM_AGP_TOP, 0x0FFFFFFF);
	WREG32(mmMC_VM_AGP_BOT, 0x0FFFFFFF);
	अगर (gmc_v8_0_रुको_क्रम_idle((व्योम *)adev)) अणु
		dev_warn(adev->dev, "Wait for MC idle timedout !\n");
	पूर्ण

	WREG32(mmBIF_FB_EN, BIF_FB_EN__FB_READ_EN_MASK | BIF_FB_EN__FB_WRITE_EN_MASK);

	पंचांगp = RREG32(mmHDP_MISC_CNTL);
	पंचांगp = REG_SET_FIELD(पंचांगp, HDP_MISC_CNTL, FLUSH_INVALIDATE_CACHE, 0);
	WREG32(mmHDP_MISC_CNTL, पंचांगp);

	पंचांगp = RREG32(mmHDP_HOST_PATH_CNTL);
	WREG32(mmHDP_HOST_PATH_CNTL, पंचांगp);
पूर्ण

/**
 * gmc_v8_0_mc_init - initialize the memory controller driver params
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Look up the amount of vram, vram width, and decide how to place
 * vram and gart within the GPU's physical address space (VI).
 * Returns 0 क्रम success.
 */
अटल पूर्णांक gmc_v8_0_mc_init(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक r;

	adev->gmc.vram_width = amdgpu_atombios_get_vram_width(adev);
	अगर (!adev->gmc.vram_width) अणु
		u32 पंचांगp;
		पूर्णांक chansize, numchan;

		/* Get VRAM inक्रमmations */
		पंचांगp = RREG32(mmMC_ARB_RAMCFG);
		अगर (REG_GET_FIELD(पंचांगp, MC_ARB_RAMCFG, CHANSIZE)) अणु
			chansize = 64;
		पूर्ण अन्यथा अणु
			chansize = 32;
		पूर्ण
		पंचांगp = RREG32(mmMC_SHARED_CHMAP);
		चयन (REG_GET_FIELD(पंचांगp, MC_SHARED_CHMAP, NOOFCHAN)) अणु
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
	पूर्ण
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

#अगर_घोषित CONFIG_X86_64
	अगर (adev->flags & AMD_IS_APU) अणु
		adev->gmc.aper_base = ((u64)RREG32(mmMC_VM_FB_OFFSET)) << 22;
		adev->gmc.aper_size = adev->gmc.real_vram_size;
	पूर्ण
#पूर्ण_अगर

	/* In हाल the PCI BAR is larger than the actual amount of vram */
	adev->gmc.visible_vram_size = adev->gmc.aper_size;
	अगर (adev->gmc.visible_vram_size > adev->gmc.real_vram_size)
		adev->gmc.visible_vram_size = adev->gmc.real_vram_size;

	/* set the gart size */
	अगर (amdgpu_gart_size == -1) अणु
		चयन (adev->asic_type) अणु
		हाल CHIP_POLARIS10: /* all engines support GPUVM */
		हाल CHIP_POLARIS11: /* all engines support GPUVM */
		हाल CHIP_POLARIS12: /* all engines support GPUVM */
		हाल CHIP_VEGAM:     /* all engines support GPUVM */
		शेष:
			adev->gmc.gart_size = 256ULL << 20;
			अवरोध;
		हाल CHIP_TONGA:   /* UVD, VCE करो not support GPUVM */
		हाल CHIP_FIJI:    /* UVD, VCE करो not support GPUVM */
		हाल CHIP_CARRIZO: /* UVD, VCE करो not support GPUVM, DCE SG support */
		हाल CHIP_STONEY:  /* UVD करोes not support GPUVM, DCE SG support */
			adev->gmc.gart_size = 1024ULL << 20;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		adev->gmc.gart_size = (u64)amdgpu_gart_size << 20;
	पूर्ण

	adev->gmc.gart_size += adev->pm.smu_prv_buffer_size;
	gmc_v8_0_vram_gtt_location(adev, &adev->gmc);

	वापस 0;
पूर्ण

/**
 * gmc_v8_0_flush_gpu_tlb_pasid - tlb flush via pasid
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @pasid: pasid to be flush
 * @flush_type: type of flush
 * @all_hub: flush all hubs
 *
 * Flush the TLB क्रम the requested pasid.
 */
अटल पूर्णांक gmc_v8_0_flush_gpu_tlb_pasid(काष्ठा amdgpu_device *adev,
					uपूर्णांक16_t pasid, uपूर्णांक32_t flush_type,
					bool all_hub)
अणु
	पूर्णांक vmid;
	अचिन्हित पूर्णांक पंचांगp;

	अगर (amdgpu_in_reset(adev))
		वापस -EIO;

	क्रम (vmid = 1; vmid < 16; vmid++) अणु

		पंचांगp = RREG32(mmATC_VMID0_PASID_MAPPING + vmid);
		अगर ((पंचांगp & ATC_VMID0_PASID_MAPPING__VALID_MASK) &&
			(पंचांगp & ATC_VMID0_PASID_MAPPING__PASID_MASK) == pasid) अणु
			WREG32(mmVM_INVALIDATE_REQUEST, 1 << vmid);
			RREG32(mmVM_INVALIDATE_RESPONSE);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;

पूर्ण

/*
 * GART
 * VMID 0 is the physical GPU addresses as used by the kernel.
 * VMIDs 1-15 are used क्रम userspace clients and are handled
 * by the amdgpu vm/hsa code.
 */

/**
 * gmc_v8_0_flush_gpu_tlb - gart tlb flush callback
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @vmid: vm instance to flush
 * @vmhub: which hub to flush
 * @flush_type: type of flush
 *
 * Flush the TLB क्रम the requested page table (VI).
 */
अटल व्योम gmc_v8_0_flush_gpu_tlb(काष्ठा amdgpu_device *adev, uपूर्णांक32_t vmid,
					uपूर्णांक32_t vmhub, uपूर्णांक32_t flush_type)
अणु
	/* bits 0-15 are the VM contexts0-15 */
	WREG32(mmVM_INVALIDATE_REQUEST, 1 << vmid);
पूर्ण

अटल uपूर्णांक64_t gmc_v8_0_emit_flush_gpu_tlb(काष्ठा amdgpu_ring *ring,
					    अचिन्हित vmid, uपूर्णांक64_t pd_addr)
अणु
	uपूर्णांक32_t reg;

	अगर (vmid < 8)
		reg = mmVM_CONTEXT0_PAGE_TABLE_BASE_ADDR + vmid;
	अन्यथा
		reg = mmVM_CONTEXT8_PAGE_TABLE_BASE_ADDR + vmid - 8;
	amdgpu_ring_emit_wreg(ring, reg, pd_addr >> 12);

	/* bits 0-15 are the VM contexts0-15 */
	amdgpu_ring_emit_wreg(ring, mmVM_INVALIDATE_REQUEST, 1 << vmid);

	वापस pd_addr;
पूर्ण

अटल व्योम gmc_v8_0_emit_pasid_mapping(काष्ठा amdgpu_ring *ring, अचिन्हित vmid,
					अचिन्हित pasid)
अणु
	amdgpu_ring_emit_wreg(ring, mmIH_VMID_0_LUT + vmid, pasid);
पूर्ण

/*
 * PTE क्रमmat on VI:
 * 63:40 reserved
 * 39:12 4k physical page base address
 * 11:7 fragment
 * 6 ग_लिखो
 * 5 पढ़ो
 * 4 exe
 * 3 reserved
 * 2 snooped
 * 1 प्रणाली
 * 0 valid
 *
 * PDE क्रमmat on VI:
 * 63:59 block fragment size
 * 58:40 reserved
 * 39:1 physical base address of PTE
 * bits 5:1 must be 0.
 * 0 valid
 */

अटल व्योम gmc_v8_0_get_vm_pde(काष्ठा amdgpu_device *adev, पूर्णांक level,
				uपूर्णांक64_t *addr, uपूर्णांक64_t *flags)
अणु
	BUG_ON(*addr & 0xFFFFFF0000000FFFULL);
पूर्ण

अटल व्योम gmc_v8_0_get_vm_pte(काष्ठा amdgpu_device *adev,
				काष्ठा amdgpu_bo_va_mapping *mapping,
				uपूर्णांक64_t *flags)
अणु
	*flags &= ~AMDGPU_PTE_EXECUTABLE;
	*flags |= mapping->flags & AMDGPU_PTE_EXECUTABLE;
	*flags &= ~AMDGPU_PTE_PRT;
पूर्ण

/**
 * gmc_v8_0_set_fault_enable_शेष - update VM fault handling
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @value: true redirects VM faults to the शेष page
 */
अटल व्योम gmc_v8_0_set_fault_enable_शेष(काष्ठा amdgpu_device *adev,
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
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_CONTEXT1_CNTL,
			    EXECUTE_PROTECTION_FAULT_ENABLE_DEFAULT, value);
	WREG32(mmVM_CONTEXT1_CNTL, पंचांगp);
पूर्ण

/**
 * gmc_v8_0_set_prt - set PRT VM fault
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @enable: enable/disable VM fault handling क्रम PRT
*/
अटल व्योम gmc_v8_0_set_prt(काष्ठा amdgpu_device *adev, bool enable)
अणु
	u32 पंचांगp;

	अगर (enable && !adev->gmc.prt_warning) अणु
		dev_warn(adev->dev, "Disabling VM faults because of PRT request!\n");
		adev->gmc.prt_warning = true;
	पूर्ण

	पंचांगp = RREG32(mmVM_PRT_CNTL);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_PRT_CNTL,
			    CB_DISABLE_READ_FAULT_ON_UNMAPPED_ACCESS, enable);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_PRT_CNTL,
			    CB_DISABLE_WRITE_FAULT_ON_UNMAPPED_ACCESS, enable);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_PRT_CNTL,
			    TC_DISABLE_READ_FAULT_ON_UNMAPPED_ACCESS, enable);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_PRT_CNTL,
			    TC_DISABLE_WRITE_FAULT_ON_UNMAPPED_ACCESS, enable);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_PRT_CNTL,
			    L2_CACHE_STORE_INVALID_ENTRIES, enable);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_PRT_CNTL,
			    L1_TLB_STORE_INVALID_ENTRIES, enable);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_PRT_CNTL,
			    MASK_PDE0_FAULT, enable);
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

/**
 * gmc_v8_0_gart_enable - gart enable
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * This sets up the TLBs, programs the page tables क्रम VMID0,
 * sets up the hw क्रम VMIDs 1-15 which are allocated on
 * demand, and sets up the global locations क्रम the LDS, GDS,
 * and GPUVM क्रम FSA64 clients (VI).
 * Returns 0 क्रम success, errors क्रम failure.
 */
अटल पूर्णांक gmc_v8_0_gart_enable(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक64_t table_addr;
	पूर्णांक r, i;
	u32 पंचांगp, field;

	अगर (adev->gart.bo == शून्य) अणु
		dev_err(adev->dev, "No VRAM object for PCIE GART.\n");
		वापस -EINVAL;
	पूर्ण
	r = amdgpu_gart_table_vram_pin(adev);
	अगर (r)
		वापस r;

	table_addr = amdgpu_bo_gpu_offset(adev->gart.bo);

	/* Setup TLB control */
	पंचांगp = RREG32(mmMC_VM_MX_L1_TLB_CNTL);
	पंचांगp = REG_SET_FIELD(पंचांगp, MC_VM_MX_L1_TLB_CNTL, ENABLE_L1_TLB, 1);
	पंचांगp = REG_SET_FIELD(पंचांगp, MC_VM_MX_L1_TLB_CNTL, ENABLE_L1_FRAGMENT_PROCESSING, 1);
	पंचांगp = REG_SET_FIELD(पंचांगp, MC_VM_MX_L1_TLB_CNTL, SYSTEM_ACCESS_MODE, 3);
	पंचांगp = REG_SET_FIELD(पंचांगp, MC_VM_MX_L1_TLB_CNTL, ENABLE_ADVANCED_DRIVER_MODEL, 1);
	पंचांगp = REG_SET_FIELD(पंचांगp, MC_VM_MX_L1_TLB_CNTL, SYSTEM_APERTURE_UNMAPPED_ACCESS, 0);
	WREG32(mmMC_VM_MX_L1_TLB_CNTL, पंचांगp);
	/* Setup L2 cache */
	पंचांगp = RREG32(mmVM_L2_CNTL);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_L2_CNTL, ENABLE_L2_CACHE, 1);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_L2_CNTL, ENABLE_L2_FRAGMENT_PROCESSING, 1);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_L2_CNTL, ENABLE_L2_PTE_CACHE_LRU_UPDATE_BY_WRITE, 1);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_L2_CNTL, ENABLE_L2_PDE0_CACHE_LRU_UPDATE_BY_WRITE, 1);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_L2_CNTL, EFFECTIVE_L2_QUEUE_SIZE, 7);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_L2_CNTL, CONTEXT1_IDENTITY_ACCESS_MODE, 1);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_L2_CNTL, ENABLE_DEFAULT_PAGE_OUT_TO_SYSTEM_MEMORY, 1);
	WREG32(mmVM_L2_CNTL, पंचांगp);
	पंचांगp = RREG32(mmVM_L2_CNTL2);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_L2_CNTL2, INVALIDATE_ALL_L1_TLBS, 1);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_L2_CNTL2, INVALIDATE_L2_CACHE, 1);
	WREG32(mmVM_L2_CNTL2, पंचांगp);

	field = adev->vm_manager.fragment_size;
	पंचांगp = RREG32(mmVM_L2_CNTL3);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_L2_CNTL3, L2_CACHE_BIGK_ASSOCIATIVITY, 1);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_L2_CNTL3, BANK_SELECT, field);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_L2_CNTL3, L2_CACHE_BIGK_FRAGMENT_SIZE, field);
	WREG32(mmVM_L2_CNTL3, पंचांगp);
	/* XXX: set to enable PTE/PDE in प्रणाली memory */
	पंचांगp = RREG32(mmVM_L2_CNTL4);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_L2_CNTL4, VMC_TAP_CONTEXT0_PDE_REQUEST_PHYSICAL, 0);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_L2_CNTL4, VMC_TAP_CONTEXT0_PDE_REQUEST_SHARED, 0);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_L2_CNTL4, VMC_TAP_CONTEXT0_PDE_REQUEST_SNOOP, 0);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_L2_CNTL4, VMC_TAP_CONTEXT0_PTE_REQUEST_PHYSICAL, 0);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_L2_CNTL4, VMC_TAP_CONTEXT0_PTE_REQUEST_SHARED, 0);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_L2_CNTL4, VMC_TAP_CONTEXT0_PTE_REQUEST_SNOOP, 0);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_L2_CNTL4, VMC_TAP_CONTEXT1_PDE_REQUEST_PHYSICAL, 0);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_L2_CNTL4, VMC_TAP_CONTEXT1_PDE_REQUEST_SHARED, 0);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_L2_CNTL4, VMC_TAP_CONTEXT1_PDE_REQUEST_SNOOP, 0);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_L2_CNTL4, VMC_TAP_CONTEXT1_PTE_REQUEST_PHYSICAL, 0);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_L2_CNTL4, VMC_TAP_CONTEXT1_PTE_REQUEST_SHARED, 0);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_L2_CNTL4, VMC_TAP_CONTEXT1_PTE_REQUEST_SNOOP, 0);
	WREG32(mmVM_L2_CNTL4, पंचांगp);
	/* setup context0 */
	WREG32(mmVM_CONTEXT0_PAGE_TABLE_START_ADDR, adev->gmc.gart_start >> 12);
	WREG32(mmVM_CONTEXT0_PAGE_TABLE_END_ADDR, adev->gmc.gart_end >> 12);
	WREG32(mmVM_CONTEXT0_PAGE_TABLE_BASE_ADDR, table_addr >> 12);
	WREG32(mmVM_CONTEXT0_PROTECTION_FAULT_DEFAULT_ADDR,
			(u32)(adev->dummy_page_addr >> 12));
	WREG32(mmVM_CONTEXT0_CNTL2, 0);
	पंचांगp = RREG32(mmVM_CONTEXT0_CNTL);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_CONTEXT0_CNTL, ENABLE_CONTEXT, 1);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_CONTEXT0_CNTL, PAGE_TABLE_DEPTH, 0);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_CONTEXT0_CNTL, RANGE_PROTECTION_FAULT_ENABLE_DEFAULT, 1);
	WREG32(mmVM_CONTEXT0_CNTL, पंचांगp);

	WREG32(mmVM_L2_CONTEXT1_IDENTITY_APERTURE_LOW_ADDR, 0);
	WREG32(mmVM_L2_CONTEXT1_IDENTITY_APERTURE_HIGH_ADDR, 0);
	WREG32(mmVM_L2_CONTEXT_IDENTITY_PHYSICAL_OFFSET, 0);

	/* empty context1-15 */
	/* FIXME start with 4G, once using 2 level pt चयन to full
	 * vm size space
	 */
	/* set vm size, must be a multiple of 4 */
	WREG32(mmVM_CONTEXT1_PAGE_TABLE_START_ADDR, 0);
	WREG32(mmVM_CONTEXT1_PAGE_TABLE_END_ADDR, adev->vm_manager.max_pfn - 1);
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
	पंचांगp = RREG32(mmVM_CONTEXT1_CNTL);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_CONTEXT1_CNTL, ENABLE_CONTEXT, 1);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_CONTEXT1_CNTL, PAGE_TABLE_DEPTH, 1);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_CONTEXT1_CNTL, RANGE_PROTECTION_FAULT_ENABLE_DEFAULT, 1);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_CONTEXT1_CNTL, DUMMY_PAGE_PROTECTION_FAULT_ENABLE_DEFAULT, 1);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_CONTEXT1_CNTL, PDE0_PROTECTION_FAULT_ENABLE_DEFAULT, 1);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_CONTEXT1_CNTL, VALID_PROTECTION_FAULT_ENABLE_DEFAULT, 1);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_CONTEXT1_CNTL, READ_PROTECTION_FAULT_ENABLE_DEFAULT, 1);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_CONTEXT1_CNTL, WRITE_PROTECTION_FAULT_ENABLE_DEFAULT, 1);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_CONTEXT1_CNTL, EXECUTE_PROTECTION_FAULT_ENABLE_DEFAULT, 1);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_CONTEXT1_CNTL, PAGE_TABLE_BLOCK_SIZE,
			    adev->vm_manager.block_size - 9);
	WREG32(mmVM_CONTEXT1_CNTL, पंचांगp);
	अगर (amdgpu_vm_fault_stop == AMDGPU_VM_FAULT_STOP_ALWAYS)
		gmc_v8_0_set_fault_enable_शेष(adev, false);
	अन्यथा
		gmc_v8_0_set_fault_enable_शेष(adev, true);

	gmc_v8_0_flush_gpu_tlb(adev, 0, 0, 0);
	DRM_INFO("PCIE GART of %uM enabled (table at 0x%016llX).\n",
		 (अचिन्हित)(adev->gmc.gart_size >> 20),
		 (अचिन्हित दीर्घ दीर्घ)table_addr);
	adev->gart.पढ़ोy = true;
	वापस 0;
पूर्ण

अटल पूर्णांक gmc_v8_0_gart_init(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक r;

	अगर (adev->gart.bo) अणु
		WARN(1, "R600 PCIE GART already initialized\n");
		वापस 0;
	पूर्ण
	/* Initialize common gart काष्ठाure */
	r = amdgpu_gart_init(adev);
	अगर (r)
		वापस r;
	adev->gart.table_size = adev->gart.num_gpu_pages * 8;
	adev->gart.gart_pte_flags = AMDGPU_PTE_EXECUTABLE;
	वापस amdgpu_gart_table_vram_alloc(adev);
पूर्ण

/**
 * gmc_v8_0_gart_disable - gart disable
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * This disables all VM page table (VI).
 */
अटल व्योम gmc_v8_0_gart_disable(काष्ठा amdgpu_device *adev)
अणु
	u32 पंचांगp;

	/* Disable all tables */
	WREG32(mmVM_CONTEXT0_CNTL, 0);
	WREG32(mmVM_CONTEXT1_CNTL, 0);
	/* Setup TLB control */
	पंचांगp = RREG32(mmMC_VM_MX_L1_TLB_CNTL);
	पंचांगp = REG_SET_FIELD(पंचांगp, MC_VM_MX_L1_TLB_CNTL, ENABLE_L1_TLB, 0);
	पंचांगp = REG_SET_FIELD(पंचांगp, MC_VM_MX_L1_TLB_CNTL, ENABLE_L1_FRAGMENT_PROCESSING, 0);
	पंचांगp = REG_SET_FIELD(पंचांगp, MC_VM_MX_L1_TLB_CNTL, ENABLE_ADVANCED_DRIVER_MODEL, 0);
	WREG32(mmMC_VM_MX_L1_TLB_CNTL, पंचांगp);
	/* Setup L2 cache */
	पंचांगp = RREG32(mmVM_L2_CNTL);
	पंचांगp = REG_SET_FIELD(पंचांगp, VM_L2_CNTL, ENABLE_L2_CACHE, 0);
	WREG32(mmVM_L2_CNTL, पंचांगp);
	WREG32(mmVM_L2_CNTL2, 0);
	amdgpu_gart_table_vram_unpin(adev);
पूर्ण

/**
 * gmc_v8_0_vm_decode_fault - prपूर्णांक human पढ़ोable fault info
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @status: VM_CONTEXT1_PROTECTION_FAULT_STATUS रेजिस्टर value
 * @addr: VM_CONTEXT1_PROTECTION_FAULT_ADDR रेजिस्टर value
 * @mc_client: VM_CONTEXT1_PROTECTION_FAULT_MCCLIENT रेजिस्टर value
 * @pasid: debug logging only - no functional use
 *
 * Prपूर्णांक human पढ़ोable fault inक्रमmation (VI).
 */
अटल व्योम gmc_v8_0_vm_decode_fault(काष्ठा amdgpu_device *adev, u32 status,
				     u32 addr, u32 mc_client, अचिन्हित pasid)
अणु
	u32 vmid = REG_GET_FIELD(status, VM_CONTEXT1_PROTECTION_FAULT_STATUS, VMID);
	u32 protections = REG_GET_FIELD(status, VM_CONTEXT1_PROTECTION_FAULT_STATUS,
					PROTECTIONS);
	अक्षर block[5] = अणु mc_client >> 24, (mc_client >> 16) & 0xff,
		(mc_client >> 8) & 0xff, mc_client & 0xff, 0 पूर्ण;
	u32 mc_id;

	mc_id = REG_GET_FIELD(status, VM_CONTEXT1_PROTECTION_FAULT_STATUS,
			      MEMORY_CLIENT_ID);

	dev_err(adev->dev, "VM fault (0x%02x, vmid %d, pasid %d) at page %u, %s from '%s' (0x%08x) (%d)\n",
	       protections, vmid, pasid, addr,
	       REG_GET_FIELD(status, VM_CONTEXT1_PROTECTION_FAULT_STATUS,
			     MEMORY_CLIENT_RW) ?
	       "write" : "read", block, mc_client, mc_id);
पूर्ण

अटल पूर्णांक gmc_v8_0_convert_vram_type(पूर्णांक mc_seq_vram_type)
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
	हाल MC_SEQ_MISC0__MT__HBM:
		वापस AMDGPU_VRAM_TYPE_HBM;
	हाल MC_SEQ_MISC0__MT__DDR3:
		वापस AMDGPU_VRAM_TYPE_DDR3;
	शेष:
		वापस AMDGPU_VRAM_TYPE_UNKNOWN;
	पूर्ण
पूर्ण

अटल पूर्णांक gmc_v8_0_early_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	gmc_v8_0_set_gmc_funcs(adev);
	gmc_v8_0_set_irq_funcs(adev);

	adev->gmc.shared_aperture_start = 0x2000000000000000ULL;
	adev->gmc.shared_aperture_end =
		adev->gmc.shared_aperture_start + (4ULL << 30) - 1;
	adev->gmc.निजी_aperture_start =
		adev->gmc.shared_aperture_end + 1;
	adev->gmc.निजी_aperture_end =
		adev->gmc.निजी_aperture_start + (4ULL << 30) - 1;

	वापस 0;
पूर्ण

अटल पूर्णांक gmc_v8_0_late_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	अगर (amdgpu_vm_fault_stop != AMDGPU_VM_FAULT_STOP_ALWAYS)
		वापस amdgpu_irq_get(adev, &adev->gmc.vm_fault, 0);
	अन्यथा
		वापस 0;
पूर्ण

अटल अचिन्हित gmc_v8_0_get_vbios_fb_size(काष्ठा amdgpu_device *adev)
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

#घोषणा mmMC_SEQ_MISC0_FIJI 0xA71

अटल पूर्णांक gmc_v8_0_sw_init(व्योम *handle)
अणु
	पूर्णांक r;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	adev->num_vmhubs = 1;

	अगर (adev->flags & AMD_IS_APU) अणु
		adev->gmc.vram_type = AMDGPU_VRAM_TYPE_UNKNOWN;
	पूर्ण अन्यथा अणु
		u32 पंचांगp;

		अगर ((adev->asic_type == CHIP_FIJI) ||
		    (adev->asic_type == CHIP_VEGAM))
			पंचांगp = RREG32(mmMC_SEQ_MISC0_FIJI);
		अन्यथा
			पंचांगp = RREG32(mmMC_SEQ_MISC0);
		पंचांगp &= MC_SEQ_MISC0__MT__MASK;
		adev->gmc.vram_type = gmc_v8_0_convert_vram_type(पंचांगp);
	पूर्ण

	r = amdgpu_irq_add_id(adev, AMDGPU_IRQ_CLIENTID_LEGACY, VISLANDS30_IV_SRCID_GFX_PAGE_INV_FAULT, &adev->gmc.vm_fault);
	अगर (r)
		वापस r;

	r = amdgpu_irq_add_id(adev, AMDGPU_IRQ_CLIENTID_LEGACY, VISLANDS30_IV_SRCID_GFX_MEM_PROT_FAULT, &adev->gmc.vm_fault);
	अगर (r)
		वापस r;

	/* Adjust VM size here.
	 * Currently set to 4GB ((1 << 20) 4k pages).
	 * Max GPUVM size क्रम cayman and SI is 40 bits.
	 */
	amdgpu_vm_adjust_size(adev, 64, 9, 1, 40);

	/* Set the पूर्णांकernal MC address mask
	 * This is the max address of the GPU's
	 * पूर्णांकernal address space.
	 */
	adev->gmc.mc_mask = 0xffffffffffULL; /* 40 bit MC */

	r = dma_set_mask_and_coherent(adev->dev, DMA_BIT_MASK(40));
	अगर (r) अणु
		pr_warn("No suitable DMA available\n");
		वापस r;
	पूर्ण
	adev->need_swiotlb = drm_need_swiotlb(40);

	r = gmc_v8_0_init_microcode(adev);
	अगर (r) अणु
		DRM_ERROR("Failed to load mc firmware!\n");
		वापस r;
	पूर्ण

	r = gmc_v8_0_mc_init(adev);
	अगर (r)
		वापस r;

	amdgpu_gmc_get_vbios_allocations(adev);

	/* Memory manager */
	r = amdgpu_bo_init(adev);
	अगर (r)
		वापस r;

	r = gmc_v8_0_gart_init(adev);
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

	adev->gmc.vm_fault_info = kदो_स्मृति(माप(काष्ठा kfd_vm_fault_info),
					GFP_KERNEL);
	अगर (!adev->gmc.vm_fault_info)
		वापस -ENOMEM;
	atomic_set(&adev->gmc.vm_fault_info_updated, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक gmc_v8_0_sw_fini(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	amdgpu_gem_क्रमce_release(adev);
	amdgpu_vm_manager_fini(adev);
	kमुक्त(adev->gmc.vm_fault_info);
	amdgpu_gart_table_vram_मुक्त(adev);
	amdgpu_bo_fini(adev);
	amdgpu_gart_fini(adev);
	release_firmware(adev->gmc.fw);
	adev->gmc.fw = शून्य;

	वापस 0;
पूर्ण

अटल पूर्णांक gmc_v8_0_hw_init(व्योम *handle)
अणु
	पूर्णांक r;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	gmc_v8_0_init_golden_रेजिस्टरs(adev);

	gmc_v8_0_mc_program(adev);

	अगर (adev->asic_type == CHIP_TONGA) अणु
		r = gmc_v8_0_tonga_mc_load_microcode(adev);
		अगर (r) अणु
			DRM_ERROR("Failed to load MC firmware!\n");
			वापस r;
		पूर्ण
	पूर्ण अन्यथा अगर (adev->asic_type == CHIP_POLARIS11 ||
			adev->asic_type == CHIP_POLARIS10 ||
			adev->asic_type == CHIP_POLARIS12) अणु
		r = gmc_v8_0_polaris_mc_load_microcode(adev);
		अगर (r) अणु
			DRM_ERROR("Failed to load MC firmware!\n");
			वापस r;
		पूर्ण
	पूर्ण

	r = gmc_v8_0_gart_enable(adev);
	अगर (r)
		वापस r;

	वापस r;
पूर्ण

अटल पूर्णांक gmc_v8_0_hw_fini(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	amdgpu_irq_put(adev, &adev->gmc.vm_fault, 0);
	gmc_v8_0_gart_disable(adev);

	वापस 0;
पूर्ण

अटल पूर्णांक gmc_v8_0_suspend(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	gmc_v8_0_hw_fini(adev);

	वापस 0;
पूर्ण

अटल पूर्णांक gmc_v8_0_resume(व्योम *handle)
अणु
	पूर्णांक r;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	r = gmc_v8_0_hw_init(adev);
	अगर (r)
		वापस r;

	amdgpu_vmid_reset_all(adev);

	वापस 0;
पूर्ण

अटल bool gmc_v8_0_is_idle(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	u32 पंचांगp = RREG32(mmSRBM_STATUS);

	अगर (पंचांगp & (SRBM_STATUS__MCB_BUSY_MASK | SRBM_STATUS__MCB_NON_DISPLAY_BUSY_MASK |
		   SRBM_STATUS__MCC_BUSY_MASK | SRBM_STATUS__MCD_BUSY_MASK | SRBM_STATUS__VMC_BUSY_MASK))
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक gmc_v8_0_रुको_क्रम_idle(व्योम *handle)
अणु
	अचिन्हित i;
	u32 पंचांगp;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	क्रम (i = 0; i < adev->usec_समयout; i++) अणु
		/* पढ़ो MC_STATUS */
		पंचांगp = RREG32(mmSRBM_STATUS) & (SRBM_STATUS__MCB_BUSY_MASK |
					       SRBM_STATUS__MCB_NON_DISPLAY_BUSY_MASK |
					       SRBM_STATUS__MCC_BUSY_MASK |
					       SRBM_STATUS__MCD_BUSY_MASK |
					       SRBM_STATUS__VMC_BUSY_MASK |
					       SRBM_STATUS__VMC1_BUSY_MASK);
		अगर (!पंचांगp)
			वापस 0;
		udelay(1);
	पूर्ण
	वापस -ETIMEDOUT;

पूर्ण

अटल bool gmc_v8_0_check_soft_reset(व्योम *handle)
अणु
	u32 srbm_soft_reset = 0;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
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
		adev->gmc.srbm_soft_reset = srbm_soft_reset;
		वापस true;
	पूर्ण अन्यथा अणु
		adev->gmc.srbm_soft_reset = 0;
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक gmc_v8_0_pre_soft_reset(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	अगर (!adev->gmc.srbm_soft_reset)
		वापस 0;

	gmc_v8_0_mc_stop(adev);
	अगर (gmc_v8_0_रुको_क्रम_idle(adev)) अणु
		dev_warn(adev->dev, "Wait for GMC idle timed out !\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gmc_v8_0_soft_reset(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	u32 srbm_soft_reset;

	अगर (!adev->gmc.srbm_soft_reset)
		वापस 0;
	srbm_soft_reset = adev->gmc.srbm_soft_reset;

	अगर (srbm_soft_reset) अणु
		u32 पंचांगp;

		पंचांगp = RREG32(mmSRBM_SOFT_RESET);
		पंचांगp |= srbm_soft_reset;
		dev_info(adev->dev, "SRBM_SOFT_RESET=0x%08X\n", पंचांगp);
		WREG32(mmSRBM_SOFT_RESET, पंचांगp);
		पंचांगp = RREG32(mmSRBM_SOFT_RESET);

		udelay(50);

		पंचांगp &= ~srbm_soft_reset;
		WREG32(mmSRBM_SOFT_RESET, पंचांगp);
		पंचांगp = RREG32(mmSRBM_SOFT_RESET);

		/* Wait a little क्रम things to settle करोwn */
		udelay(50);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gmc_v8_0_post_soft_reset(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	अगर (!adev->gmc.srbm_soft_reset)
		वापस 0;

	gmc_v8_0_mc_resume(adev);
	वापस 0;
पूर्ण

अटल पूर्णांक gmc_v8_0_vm_fault_पूर्णांकerrupt_state(काष्ठा amdgpu_device *adev,
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
		    VM_CONTEXT1_CNTL__WRITE_PROTECTION_FAULT_ENABLE_INTERRUPT_MASK |
		    VM_CONTEXT1_CNTL__EXECUTE_PROTECTION_FAULT_ENABLE_INTERRUPT_MASK);

	चयन (state) अणु
	हाल AMDGPU_IRQ_STATE_DISABLE:
		/* प्रणाली context */
		पंचांगp = RREG32(mmVM_CONTEXT0_CNTL);
		पंचांगp &= ~bits;
		WREG32(mmVM_CONTEXT0_CNTL, पंचांगp);
		/* VMs */
		पंचांगp = RREG32(mmVM_CONTEXT1_CNTL);
		पंचांगp &= ~bits;
		WREG32(mmVM_CONTEXT1_CNTL, पंचांगp);
		अवरोध;
	हाल AMDGPU_IRQ_STATE_ENABLE:
		/* प्रणाली context */
		पंचांगp = RREG32(mmVM_CONTEXT0_CNTL);
		पंचांगp |= bits;
		WREG32(mmVM_CONTEXT0_CNTL, पंचांगp);
		/* VMs */
		पंचांगp = RREG32(mmVM_CONTEXT1_CNTL);
		पंचांगp |= bits;
		WREG32(mmVM_CONTEXT1_CNTL, पंचांगp);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gmc_v8_0_process_पूर्णांकerrupt(काष्ठा amdgpu_device *adev,
				      काष्ठा amdgpu_irq_src *source,
				      काष्ठा amdgpu_iv_entry *entry)
अणु
	u32 addr, status, mc_client, vmid;

	अगर (amdgpu_sriov_vf(adev)) अणु
		dev_err(adev->dev, "GPU fault detected: %d 0x%08x\n",
			entry->src_id, entry->src_data[0]);
		dev_err(adev->dev, " Can't decode VM fault info here on SRIOV VF\n");
		वापस 0;
	पूर्ण

	addr = RREG32(mmVM_CONTEXT1_PROTECTION_FAULT_ADDR);
	status = RREG32(mmVM_CONTEXT1_PROTECTION_FAULT_STATUS);
	mc_client = RREG32(mmVM_CONTEXT1_PROTECTION_FAULT_MCCLIENT);
	/* reset addr and status */
	WREG32_P(mmVM_CONTEXT1_CNTL2, 1, ~1);

	अगर (!addr && !status)
		वापस 0;

	अगर (amdgpu_vm_fault_stop == AMDGPU_VM_FAULT_STOP_FIRST)
		gmc_v8_0_set_fault_enable_शेष(adev, false);

	अगर (prपूर्णांकk_ratelimit()) अणु
		काष्ठा amdgpu_task_info task_info;

		स_रखो(&task_info, 0, माप(काष्ठा amdgpu_task_info));
		amdgpu_vm_get_task_info(adev, entry->pasid, &task_info);

		dev_err(adev->dev, "GPU fault detected: %d 0x%08x for process %s pid %d thread %s pid %d\n",
			entry->src_id, entry->src_data[0], task_info.process_name,
			task_info.tgid, task_info.task_name, task_info.pid);
		dev_err(adev->dev, "  VM_CONTEXT1_PROTECTION_FAULT_ADDR   0x%08X\n",
			addr);
		dev_err(adev->dev, "  VM_CONTEXT1_PROTECTION_FAULT_STATUS 0x%08X\n",
			status);
		gmc_v8_0_vm_decode_fault(adev, status, addr, mc_client,
					 entry->pasid);
	पूर्ण

	vmid = REG_GET_FIELD(status, VM_CONTEXT1_PROTECTION_FAULT_STATUS,
			     VMID);
	अगर (amdgpu_amdkfd_is_kfd_vmid(adev, vmid)
		&& !atomic_पढ़ो(&adev->gmc.vm_fault_info_updated)) अणु
		काष्ठा kfd_vm_fault_info *info = adev->gmc.vm_fault_info;
		u32 protections = REG_GET_FIELD(status,
					VM_CONTEXT1_PROTECTION_FAULT_STATUS,
					PROTECTIONS);

		info->vmid = vmid;
		info->mc_id = REG_GET_FIELD(status,
					    VM_CONTEXT1_PROTECTION_FAULT_STATUS,
					    MEMORY_CLIENT_ID);
		info->status = status;
		info->page_addr = addr;
		info->prot_valid = protections & 0x7 ? true : false;
		info->prot_पढ़ो = protections & 0x8 ? true : false;
		info->prot_ग_लिखो = protections & 0x10 ? true : false;
		info->prot_exec = protections & 0x20 ? true : false;
		mb();
		atomic_set(&adev->gmc.vm_fault_info_updated, 1);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम fiji_update_mc_medium_grain_घड़ी_gating(काष्ठा amdgpu_device *adev,
						     bool enable)
अणु
	uपूर्णांक32_t data;

	अगर (enable && (adev->cg_flags & AMD_CG_SUPPORT_MC_MGCG)) अणु
		data = RREG32(mmMC_HUB_MISC_HUB_CG);
		data |= MC_HUB_MISC_HUB_CG__ENABLE_MASK;
		WREG32(mmMC_HUB_MISC_HUB_CG, data);

		data = RREG32(mmMC_HUB_MISC_SIP_CG);
		data |= MC_HUB_MISC_SIP_CG__ENABLE_MASK;
		WREG32(mmMC_HUB_MISC_SIP_CG, data);

		data = RREG32(mmMC_HUB_MISC_VM_CG);
		data |= MC_HUB_MISC_VM_CG__ENABLE_MASK;
		WREG32(mmMC_HUB_MISC_VM_CG, data);

		data = RREG32(mmMC_XPB_CLK_GAT);
		data |= MC_XPB_CLK_GAT__ENABLE_MASK;
		WREG32(mmMC_XPB_CLK_GAT, data);

		data = RREG32(mmATC_MISC_CG);
		data |= ATC_MISC_CG__ENABLE_MASK;
		WREG32(mmATC_MISC_CG, data);

		data = RREG32(mmMC_CITF_MISC_WR_CG);
		data |= MC_CITF_MISC_WR_CG__ENABLE_MASK;
		WREG32(mmMC_CITF_MISC_WR_CG, data);

		data = RREG32(mmMC_CITF_MISC_RD_CG);
		data |= MC_CITF_MISC_RD_CG__ENABLE_MASK;
		WREG32(mmMC_CITF_MISC_RD_CG, data);

		data = RREG32(mmMC_CITF_MISC_VM_CG);
		data |= MC_CITF_MISC_VM_CG__ENABLE_MASK;
		WREG32(mmMC_CITF_MISC_VM_CG, data);

		data = RREG32(mmVM_L2_CG);
		data |= VM_L2_CG__ENABLE_MASK;
		WREG32(mmVM_L2_CG, data);
	पूर्ण अन्यथा अणु
		data = RREG32(mmMC_HUB_MISC_HUB_CG);
		data &= ~MC_HUB_MISC_HUB_CG__ENABLE_MASK;
		WREG32(mmMC_HUB_MISC_HUB_CG, data);

		data = RREG32(mmMC_HUB_MISC_SIP_CG);
		data &= ~MC_HUB_MISC_SIP_CG__ENABLE_MASK;
		WREG32(mmMC_HUB_MISC_SIP_CG, data);

		data = RREG32(mmMC_HUB_MISC_VM_CG);
		data &= ~MC_HUB_MISC_VM_CG__ENABLE_MASK;
		WREG32(mmMC_HUB_MISC_VM_CG, data);

		data = RREG32(mmMC_XPB_CLK_GAT);
		data &= ~MC_XPB_CLK_GAT__ENABLE_MASK;
		WREG32(mmMC_XPB_CLK_GAT, data);

		data = RREG32(mmATC_MISC_CG);
		data &= ~ATC_MISC_CG__ENABLE_MASK;
		WREG32(mmATC_MISC_CG, data);

		data = RREG32(mmMC_CITF_MISC_WR_CG);
		data &= ~MC_CITF_MISC_WR_CG__ENABLE_MASK;
		WREG32(mmMC_CITF_MISC_WR_CG, data);

		data = RREG32(mmMC_CITF_MISC_RD_CG);
		data &= ~MC_CITF_MISC_RD_CG__ENABLE_MASK;
		WREG32(mmMC_CITF_MISC_RD_CG, data);

		data = RREG32(mmMC_CITF_MISC_VM_CG);
		data &= ~MC_CITF_MISC_VM_CG__ENABLE_MASK;
		WREG32(mmMC_CITF_MISC_VM_CG, data);

		data = RREG32(mmVM_L2_CG);
		data &= ~VM_L2_CG__ENABLE_MASK;
		WREG32(mmVM_L2_CG, data);
	पूर्ण
पूर्ण

अटल व्योम fiji_update_mc_light_sleep(काष्ठा amdgpu_device *adev,
				       bool enable)
अणु
	uपूर्णांक32_t data;

	अगर (enable && (adev->cg_flags & AMD_CG_SUPPORT_MC_LS)) अणु
		data = RREG32(mmMC_HUB_MISC_HUB_CG);
		data |= MC_HUB_MISC_HUB_CG__MEM_LS_ENABLE_MASK;
		WREG32(mmMC_HUB_MISC_HUB_CG, data);

		data = RREG32(mmMC_HUB_MISC_SIP_CG);
		data |= MC_HUB_MISC_SIP_CG__MEM_LS_ENABLE_MASK;
		WREG32(mmMC_HUB_MISC_SIP_CG, data);

		data = RREG32(mmMC_HUB_MISC_VM_CG);
		data |= MC_HUB_MISC_VM_CG__MEM_LS_ENABLE_MASK;
		WREG32(mmMC_HUB_MISC_VM_CG, data);

		data = RREG32(mmMC_XPB_CLK_GAT);
		data |= MC_XPB_CLK_GAT__MEM_LS_ENABLE_MASK;
		WREG32(mmMC_XPB_CLK_GAT, data);

		data = RREG32(mmATC_MISC_CG);
		data |= ATC_MISC_CG__MEM_LS_ENABLE_MASK;
		WREG32(mmATC_MISC_CG, data);

		data = RREG32(mmMC_CITF_MISC_WR_CG);
		data |= MC_CITF_MISC_WR_CG__MEM_LS_ENABLE_MASK;
		WREG32(mmMC_CITF_MISC_WR_CG, data);

		data = RREG32(mmMC_CITF_MISC_RD_CG);
		data |= MC_CITF_MISC_RD_CG__MEM_LS_ENABLE_MASK;
		WREG32(mmMC_CITF_MISC_RD_CG, data);

		data = RREG32(mmMC_CITF_MISC_VM_CG);
		data |= MC_CITF_MISC_VM_CG__MEM_LS_ENABLE_MASK;
		WREG32(mmMC_CITF_MISC_VM_CG, data);

		data = RREG32(mmVM_L2_CG);
		data |= VM_L2_CG__MEM_LS_ENABLE_MASK;
		WREG32(mmVM_L2_CG, data);
	पूर्ण अन्यथा अणु
		data = RREG32(mmMC_HUB_MISC_HUB_CG);
		data &= ~MC_HUB_MISC_HUB_CG__MEM_LS_ENABLE_MASK;
		WREG32(mmMC_HUB_MISC_HUB_CG, data);

		data = RREG32(mmMC_HUB_MISC_SIP_CG);
		data &= ~MC_HUB_MISC_SIP_CG__MEM_LS_ENABLE_MASK;
		WREG32(mmMC_HUB_MISC_SIP_CG, data);

		data = RREG32(mmMC_HUB_MISC_VM_CG);
		data &= ~MC_HUB_MISC_VM_CG__MEM_LS_ENABLE_MASK;
		WREG32(mmMC_HUB_MISC_VM_CG, data);

		data = RREG32(mmMC_XPB_CLK_GAT);
		data &= ~MC_XPB_CLK_GAT__MEM_LS_ENABLE_MASK;
		WREG32(mmMC_XPB_CLK_GAT, data);

		data = RREG32(mmATC_MISC_CG);
		data &= ~ATC_MISC_CG__MEM_LS_ENABLE_MASK;
		WREG32(mmATC_MISC_CG, data);

		data = RREG32(mmMC_CITF_MISC_WR_CG);
		data &= ~MC_CITF_MISC_WR_CG__MEM_LS_ENABLE_MASK;
		WREG32(mmMC_CITF_MISC_WR_CG, data);

		data = RREG32(mmMC_CITF_MISC_RD_CG);
		data &= ~MC_CITF_MISC_RD_CG__MEM_LS_ENABLE_MASK;
		WREG32(mmMC_CITF_MISC_RD_CG, data);

		data = RREG32(mmMC_CITF_MISC_VM_CG);
		data &= ~MC_CITF_MISC_VM_CG__MEM_LS_ENABLE_MASK;
		WREG32(mmMC_CITF_MISC_VM_CG, data);

		data = RREG32(mmVM_L2_CG);
		data &= ~VM_L2_CG__MEM_LS_ENABLE_MASK;
		WREG32(mmVM_L2_CG, data);
	पूर्ण
पूर्ण

अटल पूर्णांक gmc_v8_0_set_घड़ीgating_state(व्योम *handle,
					  क्रमागत amd_घड़ीgating_state state)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	अगर (amdgpu_sriov_vf(adev))
		वापस 0;

	चयन (adev->asic_type) अणु
	हाल CHIP_FIJI:
		fiji_update_mc_medium_grain_घड़ी_gating(adev,
				state == AMD_CG_STATE_GATE);
		fiji_update_mc_light_sleep(adev,
				state == AMD_CG_STATE_GATE);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक gmc_v8_0_set_घातergating_state(व्योम *handle,
					  क्रमागत amd_घातergating_state state)
अणु
	वापस 0;
पूर्ण

अटल व्योम gmc_v8_0_get_घड़ीgating_state(व्योम *handle, u32 *flags)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	पूर्णांक data;

	अगर (amdgpu_sriov_vf(adev))
		*flags = 0;

	/* AMD_CG_SUPPORT_MC_MGCG */
	data = RREG32(mmMC_HUB_MISC_HUB_CG);
	अगर (data & MC_HUB_MISC_HUB_CG__ENABLE_MASK)
		*flags |= AMD_CG_SUPPORT_MC_MGCG;

	/* AMD_CG_SUPPORT_MC_LS */
	अगर (data & MC_HUB_MISC_HUB_CG__MEM_LS_ENABLE_MASK)
		*flags |= AMD_CG_SUPPORT_MC_LS;
पूर्ण

अटल स्थिर काष्ठा amd_ip_funcs gmc_v8_0_ip_funcs = अणु
	.name = "gmc_v8_0",
	.early_init = gmc_v8_0_early_init,
	.late_init = gmc_v8_0_late_init,
	.sw_init = gmc_v8_0_sw_init,
	.sw_fini = gmc_v8_0_sw_fini,
	.hw_init = gmc_v8_0_hw_init,
	.hw_fini = gmc_v8_0_hw_fini,
	.suspend = gmc_v8_0_suspend,
	.resume = gmc_v8_0_resume,
	.is_idle = gmc_v8_0_is_idle,
	.रुको_क्रम_idle = gmc_v8_0_रुको_क्रम_idle,
	.check_soft_reset = gmc_v8_0_check_soft_reset,
	.pre_soft_reset = gmc_v8_0_pre_soft_reset,
	.soft_reset = gmc_v8_0_soft_reset,
	.post_soft_reset = gmc_v8_0_post_soft_reset,
	.set_घड़ीgating_state = gmc_v8_0_set_घड़ीgating_state,
	.set_घातergating_state = gmc_v8_0_set_घातergating_state,
	.get_घड़ीgating_state = gmc_v8_0_get_घड़ीgating_state,
पूर्ण;

अटल स्थिर काष्ठा amdgpu_gmc_funcs gmc_v8_0_gmc_funcs = अणु
	.flush_gpu_tlb = gmc_v8_0_flush_gpu_tlb,
	.flush_gpu_tlb_pasid = gmc_v8_0_flush_gpu_tlb_pasid,
	.emit_flush_gpu_tlb = gmc_v8_0_emit_flush_gpu_tlb,
	.emit_pasid_mapping = gmc_v8_0_emit_pasid_mapping,
	.set_prt = gmc_v8_0_set_prt,
	.get_vm_pde = gmc_v8_0_get_vm_pde,
	.get_vm_pte = gmc_v8_0_get_vm_pte,
	.get_vbios_fb_size = gmc_v8_0_get_vbios_fb_size,
पूर्ण;

अटल स्थिर काष्ठा amdgpu_irq_src_funcs gmc_v8_0_irq_funcs = अणु
	.set = gmc_v8_0_vm_fault_पूर्णांकerrupt_state,
	.process = gmc_v8_0_process_पूर्णांकerrupt,
पूर्ण;

अटल व्योम gmc_v8_0_set_gmc_funcs(काष्ठा amdgpu_device *adev)
अणु
	adev->gmc.gmc_funcs = &gmc_v8_0_gmc_funcs;
पूर्ण

अटल व्योम gmc_v8_0_set_irq_funcs(काष्ठा amdgpu_device *adev)
अणु
	adev->gmc.vm_fault.num_types = 1;
	adev->gmc.vm_fault.funcs = &gmc_v8_0_irq_funcs;
पूर्ण

स्थिर काष्ठा amdgpu_ip_block_version gmc_v8_0_ip_block =
अणु
	.type = AMD_IP_BLOCK_TYPE_GMC,
	.major = 8,
	.minor = 0,
	.rev = 0,
	.funcs = &gmc_v8_0_ip_funcs,
पूर्ण;

स्थिर काष्ठा amdgpu_ip_block_version gmc_v8_1_ip_block =
अणु
	.type = AMD_IP_BLOCK_TYPE_GMC,
	.major = 8,
	.minor = 1,
	.rev = 0,
	.funcs = &gmc_v8_0_ip_funcs,
पूर्ण;

स्थिर काष्ठा amdgpu_ip_block_version gmc_v8_5_ip_block =
अणु
	.type = AMD_IP_BLOCK_TYPE_GMC,
	.major = 8,
	.minor = 5,
	.rev = 0,
	.funcs = &gmc_v8_0_ip_funcs,
पूर्ण;
