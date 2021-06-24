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
 * Authors: Alex Deucher
 */

#समावेश <linux/delay.h>
#समावेश <linux/firmware.h>
#समावेश <linux/module.h>

#समावेश "amdgpu.h"
#समावेश "amdgpu_ucode.h"
#समावेश "amdgpu_trace.h"
#समावेश "vi.h"
#समावेश "vid.h"

#समावेश "oss/oss_3_0_d.h"
#समावेश "oss/oss_3_0_sh_mask.h"

#समावेश "gmc/gmc_8_1_d.h"
#समावेश "gmc/gmc_8_1_sh_mask.h"

#समावेश "gca/gfx_8_0_d.h"
#समावेश "gca/gfx_8_0_enum.h"
#समावेश "gca/gfx_8_0_sh_mask.h"

#समावेश "bif/bif_5_0_d.h"
#समावेश "bif/bif_5_0_sh_mask.h"

#समावेश "tonga_sdma_pkt_open.h"

#समावेश "ivsrcid/ivsrcid_vislands30.h"

अटल व्योम sdma_v3_0_set_ring_funcs(काष्ठा amdgpu_device *adev);
अटल व्योम sdma_v3_0_set_buffer_funcs(काष्ठा amdgpu_device *adev);
अटल व्योम sdma_v3_0_set_vm_pte_funcs(काष्ठा amdgpu_device *adev);
अटल व्योम sdma_v3_0_set_irq_funcs(काष्ठा amdgpu_device *adev);

MODULE_FIRMWARE("amdgpu/tonga_sdma.bin");
MODULE_FIRMWARE("amdgpu/tonga_sdma1.bin");
MODULE_FIRMWARE("amdgpu/carrizo_sdma.bin");
MODULE_FIRMWARE("amdgpu/carrizo_sdma1.bin");
MODULE_FIRMWARE("amdgpu/fiji_sdma.bin");
MODULE_FIRMWARE("amdgpu/fiji_sdma1.bin");
MODULE_FIRMWARE("amdgpu/stoney_sdma.bin");
MODULE_FIRMWARE("amdgpu/polaris10_sdma.bin");
MODULE_FIRMWARE("amdgpu/polaris10_sdma1.bin");
MODULE_FIRMWARE("amdgpu/polaris11_sdma.bin");
MODULE_FIRMWARE("amdgpu/polaris11_sdma1.bin");
MODULE_FIRMWARE("amdgpu/polaris12_sdma.bin");
MODULE_FIRMWARE("amdgpu/polaris12_sdma1.bin");
MODULE_FIRMWARE("amdgpu/vegam_sdma.bin");
MODULE_FIRMWARE("amdgpu/vegam_sdma1.bin");


अटल स्थिर u32 sdma_offsets[SDMA_MAX_INSTANCE] =
अणु
	SDMA0_REGISTER_OFFSET,
	SDMA1_REGISTER_OFFSET
पूर्ण;

अटल स्थिर u32 golden_settings_tonga_a11[] =
अणु
	mmSDMA0_CHICKEN_BITS, 0xfc910007, 0x00810007,
	mmSDMA0_CLK_CTRL, 0xff000fff, 0x00000000,
	mmSDMA0_GFX_IB_CNTL, 0x800f0111, 0x00000100,
	mmSDMA0_RLC0_IB_CNTL, 0x800f0111, 0x00000100,
	mmSDMA0_RLC1_IB_CNTL, 0x800f0111, 0x00000100,
	mmSDMA1_CHICKEN_BITS, 0xfc910007, 0x00810007,
	mmSDMA1_CLK_CTRL, 0xff000fff, 0x00000000,
	mmSDMA1_GFX_IB_CNTL, 0x800f0111, 0x00000100,
	mmSDMA1_RLC0_IB_CNTL, 0x800f0111, 0x00000100,
	mmSDMA1_RLC1_IB_CNTL, 0x800f0111, 0x00000100,
पूर्ण;

अटल स्थिर u32 tonga_mgcg_cgcg_init[] =
अणु
	mmSDMA0_CLK_CTRL, 0xff000ff0, 0x00000100,
	mmSDMA1_CLK_CTRL, 0xff000ff0, 0x00000100
पूर्ण;

अटल स्थिर u32 golden_settings_fiji_a10[] =
अणु
	mmSDMA0_CHICKEN_BITS, 0xfc910007, 0x00810007,
	mmSDMA0_GFX_IB_CNTL, 0x800f0111, 0x00000100,
	mmSDMA0_RLC0_IB_CNTL, 0x800f0111, 0x00000100,
	mmSDMA0_RLC1_IB_CNTL, 0x800f0111, 0x00000100,
	mmSDMA1_CHICKEN_BITS, 0xfc910007, 0x00810007,
	mmSDMA1_GFX_IB_CNTL, 0x800f0111, 0x00000100,
	mmSDMA1_RLC0_IB_CNTL, 0x800f0111, 0x00000100,
	mmSDMA1_RLC1_IB_CNTL, 0x800f0111, 0x00000100,
पूर्ण;

अटल स्थिर u32 fiji_mgcg_cgcg_init[] =
अणु
	mmSDMA0_CLK_CTRL, 0xff000ff0, 0x00000100,
	mmSDMA1_CLK_CTRL, 0xff000ff0, 0x00000100
पूर्ण;

अटल स्थिर u32 golden_settings_polaris11_a11[] =
अणु
	mmSDMA0_CHICKEN_BITS, 0xfc910007, 0x00810007,
	mmSDMA0_CLK_CTRL, 0xff000fff, 0x00000000,
	mmSDMA0_GFX_IB_CNTL, 0x800f0111, 0x00000100,
	mmSDMA0_RLC0_IB_CNTL, 0x800f0111, 0x00000100,
	mmSDMA0_RLC1_IB_CNTL, 0x800f0111, 0x00000100,
	mmSDMA1_CHICKEN_BITS, 0xfc910007, 0x00810007,
	mmSDMA1_CLK_CTRL, 0xff000fff, 0x00000000,
	mmSDMA1_GFX_IB_CNTL, 0x800f0111, 0x00000100,
	mmSDMA1_RLC0_IB_CNTL, 0x800f0111, 0x00000100,
	mmSDMA1_RLC1_IB_CNTL, 0x800f0111, 0x00000100,
पूर्ण;

अटल स्थिर u32 golden_settings_polaris10_a11[] =
अणु
	mmSDMA0_CHICKEN_BITS, 0xfc910007, 0x00810007,
	mmSDMA0_CLK_CTRL, 0xff000fff, 0x00000000,
	mmSDMA0_GFX_IB_CNTL, 0x800f0111, 0x00000100,
	mmSDMA0_RLC0_IB_CNTL, 0x800f0111, 0x00000100,
	mmSDMA0_RLC1_IB_CNTL, 0x800f0111, 0x00000100,
	mmSDMA1_CHICKEN_BITS, 0xfc910007, 0x00810007,
	mmSDMA1_CLK_CTRL, 0xff000fff, 0x00000000,
	mmSDMA1_GFX_IB_CNTL, 0x800f0111, 0x00000100,
	mmSDMA1_RLC0_IB_CNTL, 0x800f0111, 0x00000100,
	mmSDMA1_RLC1_IB_CNTL, 0x800f0111, 0x00000100,
पूर्ण;

अटल स्थिर u32 cz_golden_settings_a11[] =
अणु
	mmSDMA0_CHICKEN_BITS, 0xfc910007, 0x00810007,
	mmSDMA0_CLK_CTRL, 0xff000fff, 0x00000000,
	mmSDMA0_GFX_IB_CNTL, 0x00000100, 0x00000100,
	mmSDMA0_POWER_CNTL, 0x00000800, 0x0003c800,
	mmSDMA0_RLC0_IB_CNTL, 0x00000100, 0x00000100,
	mmSDMA0_RLC1_IB_CNTL, 0x00000100, 0x00000100,
	mmSDMA1_CHICKEN_BITS, 0xfc910007, 0x00810007,
	mmSDMA1_CLK_CTRL, 0xff000fff, 0x00000000,
	mmSDMA1_GFX_IB_CNTL, 0x00000100, 0x00000100,
	mmSDMA1_POWER_CNTL, 0x00000800, 0x0003c800,
	mmSDMA1_RLC0_IB_CNTL, 0x00000100, 0x00000100,
	mmSDMA1_RLC1_IB_CNTL, 0x00000100, 0x00000100,
पूर्ण;

अटल स्थिर u32 cz_mgcg_cgcg_init[] =
अणु
	mmSDMA0_CLK_CTRL, 0xff000ff0, 0x00000100,
	mmSDMA1_CLK_CTRL, 0xff000ff0, 0x00000100
पूर्ण;

अटल स्थिर u32 stoney_golden_settings_a11[] =
अणु
	mmSDMA0_GFX_IB_CNTL, 0x00000100, 0x00000100,
	mmSDMA0_POWER_CNTL, 0x00000800, 0x0003c800,
	mmSDMA0_RLC0_IB_CNTL, 0x00000100, 0x00000100,
	mmSDMA0_RLC1_IB_CNTL, 0x00000100, 0x00000100,
पूर्ण;

अटल स्थिर u32 stoney_mgcg_cgcg_init[] =
अणु
	mmSDMA0_CLK_CTRL, 0xffffffff, 0x00000100,
पूर्ण;

/*
 * sDMA - System DMA
 * Starting with CIK, the GPU has new asynchronous
 * DMA engines.  These engines are used क्रम compute
 * and gfx.  There are two DMA engines (SDMA0, SDMA1)
 * and each one supports 1 ring buffer used क्रम gfx
 * and 2 queues used क्रम compute.
 *
 * The programming model is very similar to the CP
 * (ring buffer, IBs, etc.), but sDMA has it's own
 * packet क्रमmat that is dअगरferent from the PM4 क्रमmat
 * used by the CP. sDMA supports copying data, writing
 * embedded data, solid fills, and a number of other
 * things.  It also has support क्रम tiling/detiling of
 * buffers.
 */

अटल व्योम sdma_v3_0_init_golden_रेजिस्टरs(काष्ठा amdgpu_device *adev)
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
		amdgpu_device_program_रेजिस्टर_sequence(adev,
							cz_golden_settings_a11,
							ARRAY_SIZE(cz_golden_settings_a11));
		अवरोध;
	हाल CHIP_STONEY:
		amdgpu_device_program_रेजिस्टर_sequence(adev,
							stoney_mgcg_cgcg_init,
							ARRAY_SIZE(stoney_mgcg_cgcg_init));
		amdgpu_device_program_रेजिस्टर_sequence(adev,
							stoney_golden_settings_a11,
							ARRAY_SIZE(stoney_golden_settings_a11));
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम sdma_v3_0_मुक्त_microcode(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < adev->sdma.num_instances; i++) अणु
		release_firmware(adev->sdma.instance[i].fw);
		adev->sdma.instance[i].fw = शून्य;
	पूर्ण
पूर्ण

/**
 * sdma_v3_0_init_microcode - load ucode images from disk
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Use the firmware पूर्णांकerface to load the ucode images पूर्णांकo
 * the driver (not loaded पूर्णांकo hw).
 * Returns 0 on success, error on failure.
 */
अटल पूर्णांक sdma_v3_0_init_microcode(काष्ठा amdgpu_device *adev)
अणु
	स्थिर अक्षर *chip_name;
	अक्षर fw_name[30];
	पूर्णांक err = 0, i;
	काष्ठा amdgpu_firmware_info *info = शून्य;
	स्थिर काष्ठा common_firmware_header *header = शून्य;
	स्थिर काष्ठा sdma_firmware_header_v1_0 *hdr;

	DRM_DEBUG("\n");

	चयन (adev->asic_type) अणु
	हाल CHIP_TONGA:
		chip_name = "tonga";
		अवरोध;
	हाल CHIP_FIJI:
		chip_name = "fiji";
		अवरोध;
	हाल CHIP_POLARIS10:
		chip_name = "polaris10";
		अवरोध;
	हाल CHIP_POLARIS11:
		chip_name = "polaris11";
		अवरोध;
	हाल CHIP_POLARIS12:
		chip_name = "polaris12";
		अवरोध;
	हाल CHIP_VEGAM:
		chip_name = "vegam";
		अवरोध;
	हाल CHIP_CARRIZO:
		chip_name = "carrizo";
		अवरोध;
	हाल CHIP_STONEY:
		chip_name = "stoney";
		अवरोध;
	शेष: BUG();
	पूर्ण

	क्रम (i = 0; i < adev->sdma.num_instances; i++) अणु
		अगर (i == 0)
			snम_लिखो(fw_name, माप(fw_name), "amdgpu/%s_sdma.bin", chip_name);
		अन्यथा
			snम_लिखो(fw_name, माप(fw_name), "amdgpu/%s_sdma1.bin", chip_name);
		err = request_firmware(&adev->sdma.instance[i].fw, fw_name, adev->dev);
		अगर (err)
			जाओ out;
		err = amdgpu_ucode_validate(adev->sdma.instance[i].fw);
		अगर (err)
			जाओ out;
		hdr = (स्थिर काष्ठा sdma_firmware_header_v1_0 *)adev->sdma.instance[i].fw->data;
		adev->sdma.instance[i].fw_version = le32_to_cpu(hdr->header.ucode_version);
		adev->sdma.instance[i].feature_version = le32_to_cpu(hdr->ucode_feature_version);
		अगर (adev->sdma.instance[i].feature_version >= 20)
			adev->sdma.instance[i].burst_nop = true;

		info = &adev->firmware.ucode[AMDGPU_UCODE_ID_SDMA0 + i];
		info->ucode_id = AMDGPU_UCODE_ID_SDMA0 + i;
		info->fw = adev->sdma.instance[i].fw;
		header = (स्थिर काष्ठा common_firmware_header *)info->fw->data;
		adev->firmware.fw_size +=
			ALIGN(le32_to_cpu(header->ucode_size_bytes), PAGE_SIZE);

	पूर्ण
out:
	अगर (err) अणु
		pr_err("sdma_v3_0: Failed to load firmware \"%s\"\n", fw_name);
		क्रम (i = 0; i < adev->sdma.num_instances; i++) अणु
			release_firmware(adev->sdma.instance[i].fw);
			adev->sdma.instance[i].fw = शून्य;
		पूर्ण
	पूर्ण
	वापस err;
पूर्ण

/**
 * sdma_v3_0_ring_get_rptr - get the current पढ़ो poपूर्णांकer
 *
 * @ring: amdgpu ring poपूर्णांकer
 *
 * Get the current rptr from the hardware (VI+).
 */
अटल uपूर्णांक64_t sdma_v3_0_ring_get_rptr(काष्ठा amdgpu_ring *ring)
अणु
	/* XXX check अगर swapping is necessary on BE */
	वापस ring->adev->wb.wb[ring->rptr_offs] >> 2;
पूर्ण

/**
 * sdma_v3_0_ring_get_wptr - get the current ग_लिखो poपूर्णांकer
 *
 * @ring: amdgpu ring poपूर्णांकer
 *
 * Get the current wptr from the hardware (VI+).
 */
अटल uपूर्णांक64_t sdma_v3_0_ring_get_wptr(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;
	u32 wptr;

	अगर (ring->use_करोorbell || ring->use_pollmem) अणु
		/* XXX check अगर swapping is necessary on BE */
		wptr = ring->adev->wb.wb[ring->wptr_offs] >> 2;
	पूर्ण अन्यथा अणु
		wptr = RREG32(mmSDMA0_GFX_RB_WPTR + sdma_offsets[ring->me]) >> 2;
	पूर्ण

	वापस wptr;
पूर्ण

/**
 * sdma_v3_0_ring_set_wptr - commit the ग_लिखो poपूर्णांकer
 *
 * @ring: amdgpu ring poपूर्णांकer
 *
 * Write the wptr back to the hardware (VI+).
 */
अटल व्योम sdma_v3_0_ring_set_wptr(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	अगर (ring->use_करोorbell) अणु
		u32 *wb = (u32 *)&adev->wb.wb[ring->wptr_offs];
		/* XXX check अगर swapping is necessary on BE */
		WRITE_ONCE(*wb, (lower_32_bits(ring->wptr) << 2));
		WDOORBELL32(ring->करोorbell_index, lower_32_bits(ring->wptr) << 2);
	पूर्ण अन्यथा अगर (ring->use_pollmem) अणु
		u32 *wb = (u32 *)&adev->wb.wb[ring->wptr_offs];

		WRITE_ONCE(*wb, (lower_32_bits(ring->wptr) << 2));
	पूर्ण अन्यथा अणु
		WREG32(mmSDMA0_GFX_RB_WPTR + sdma_offsets[ring->me], lower_32_bits(ring->wptr) << 2);
	पूर्ण
पूर्ण

अटल व्योम sdma_v3_0_ring_insert_nop(काष्ठा amdgpu_ring *ring, uपूर्णांक32_t count)
अणु
	काष्ठा amdgpu_sdma_instance *sdma = amdgpu_sdma_get_instance_from_ring(ring);
	पूर्णांक i;

	क्रम (i = 0; i < count; i++)
		अगर (sdma && sdma->burst_nop && (i == 0))
			amdgpu_ring_ग_लिखो(ring, ring->funcs->nop |
				SDMA_PKT_NOP_HEADER_COUNT(count - 1));
		अन्यथा
			amdgpu_ring_ग_लिखो(ring, ring->funcs->nop);
पूर्ण

/**
 * sdma_v3_0_ring_emit_ib - Schedule an IB on the DMA engine
 *
 * @ring: amdgpu ring poपूर्णांकer
 * @job: job to retrieve vmid from
 * @ib: IB object to schedule
 * @flags: unused
 *
 * Schedule an IB in the DMA ring (VI).
 */
अटल व्योम sdma_v3_0_ring_emit_ib(काष्ठा amdgpu_ring *ring,
				   काष्ठा amdgpu_job *job,
				   काष्ठा amdgpu_ib *ib,
				   uपूर्णांक32_t flags)
अणु
	अचिन्हित vmid = AMDGPU_JOB_GET_VMID(job);

	/* IB packet must end on a 8 DW boundary */
	sdma_v3_0_ring_insert_nop(ring, (2 - lower_32_bits(ring->wptr)) & 7);

	amdgpu_ring_ग_लिखो(ring, SDMA_PKT_HEADER_OP(SDMA_OP_INसूचीECT) |
			  SDMA_PKT_INसूचीECT_HEADER_VMID(vmid & 0xf));
	/* base must be 32 byte aligned */
	amdgpu_ring_ग_लिखो(ring, lower_32_bits(ib->gpu_addr) & 0xffffffe0);
	amdgpu_ring_ग_लिखो(ring, upper_32_bits(ib->gpu_addr));
	amdgpu_ring_ग_लिखो(ring, ib->length_dw);
	amdgpu_ring_ग_लिखो(ring, 0);
	amdgpu_ring_ग_लिखो(ring, 0);

पूर्ण

/**
 * sdma_v3_0_ring_emit_hdp_flush - emit an hdp flush on the DMA ring
 *
 * @ring: amdgpu ring poपूर्णांकer
 *
 * Emit an hdp flush packet on the requested DMA ring.
 */
अटल व्योम sdma_v3_0_ring_emit_hdp_flush(काष्ठा amdgpu_ring *ring)
अणु
	u32 ref_and_mask = 0;

	अगर (ring->me == 0)
		ref_and_mask = REG_SET_FIELD(ref_and_mask, GPU_HDP_FLUSH_DONE, SDMA0, 1);
	अन्यथा
		ref_and_mask = REG_SET_FIELD(ref_and_mask, GPU_HDP_FLUSH_DONE, SDMA1, 1);

	amdgpu_ring_ग_लिखो(ring, SDMA_PKT_HEADER_OP(SDMA_OP_POLL_REGMEM) |
			  SDMA_PKT_POLL_REGMEM_HEADER_HDP_FLUSH(1) |
			  SDMA_PKT_POLL_REGMEM_HEADER_FUNC(3)); /* == */
	amdgpu_ring_ग_लिखो(ring, mmGPU_HDP_FLUSH_DONE << 2);
	amdgpu_ring_ग_लिखो(ring, mmGPU_HDP_FLUSH_REQ << 2);
	amdgpu_ring_ग_लिखो(ring, ref_and_mask); /* reference */
	amdgpu_ring_ग_लिखो(ring, ref_and_mask); /* mask */
	amdgpu_ring_ग_लिखो(ring, SDMA_PKT_POLL_REGMEM_DW5_RETRY_COUNT(0xfff) |
			  SDMA_PKT_POLL_REGMEM_DW5_INTERVAL(10)); /* retry count, poll पूर्णांकerval */
पूर्ण

/**
 * sdma_v3_0_ring_emit_fence - emit a fence on the DMA ring
 *
 * @ring: amdgpu ring poपूर्णांकer
 * @addr: address
 * @seq: sequence number
 * @flags: fence related flags
 *
 * Add a DMA fence packet to the ring to ग_लिखो
 * the fence seq number and DMA trap packet to generate
 * an पूर्णांकerrupt अगर needed (VI).
 */
अटल व्योम sdma_v3_0_ring_emit_fence(काष्ठा amdgpu_ring *ring, u64 addr, u64 seq,
				      अचिन्हित flags)
अणु
	bool ग_लिखो64bit = flags & AMDGPU_FENCE_FLAG_64BIT;
	/* ग_लिखो the fence */
	amdgpu_ring_ग_लिखो(ring, SDMA_PKT_HEADER_OP(SDMA_OP_FENCE));
	amdgpu_ring_ग_लिखो(ring, lower_32_bits(addr));
	amdgpu_ring_ग_लिखो(ring, upper_32_bits(addr));
	amdgpu_ring_ग_लिखो(ring, lower_32_bits(seq));

	/* optionally ग_लिखो high bits as well */
	अगर (ग_लिखो64bit) अणु
		addr += 4;
		amdgpu_ring_ग_लिखो(ring, SDMA_PKT_HEADER_OP(SDMA_OP_FENCE));
		amdgpu_ring_ग_लिखो(ring, lower_32_bits(addr));
		amdgpu_ring_ग_लिखो(ring, upper_32_bits(addr));
		amdgpu_ring_ग_लिखो(ring, upper_32_bits(seq));
	पूर्ण

	/* generate an पूर्णांकerrupt */
	amdgpu_ring_ग_लिखो(ring, SDMA_PKT_HEADER_OP(SDMA_OP_TRAP));
	amdgpu_ring_ग_लिखो(ring, SDMA_PKT_TRAP_INT_CONTEXT_INT_CONTEXT(0));
पूर्ण

/**
 * sdma_v3_0_gfx_stop - stop the gfx async dma engines
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Stop the gfx async dma ring buffers (VI).
 */
अटल व्योम sdma_v3_0_gfx_stop(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_ring *sdma0 = &adev->sdma.instance[0].ring;
	काष्ठा amdgpu_ring *sdma1 = &adev->sdma.instance[1].ring;
	u32 rb_cntl, ib_cntl;
	पूर्णांक i;

	अगर ((adev->mman.buffer_funcs_ring == sdma0) ||
	    (adev->mman.buffer_funcs_ring == sdma1))
		amdgpu_tपंचांग_set_buffer_funcs_status(adev, false);

	क्रम (i = 0; i < adev->sdma.num_instances; i++) अणु
		rb_cntl = RREG32(mmSDMA0_GFX_RB_CNTL + sdma_offsets[i]);
		rb_cntl = REG_SET_FIELD(rb_cntl, SDMA0_GFX_RB_CNTL, RB_ENABLE, 0);
		WREG32(mmSDMA0_GFX_RB_CNTL + sdma_offsets[i], rb_cntl);
		ib_cntl = RREG32(mmSDMA0_GFX_IB_CNTL + sdma_offsets[i]);
		ib_cntl = REG_SET_FIELD(ib_cntl, SDMA0_GFX_IB_CNTL, IB_ENABLE, 0);
		WREG32(mmSDMA0_GFX_IB_CNTL + sdma_offsets[i], ib_cntl);
	पूर्ण
पूर्ण

/**
 * sdma_v3_0_rlc_stop - stop the compute async dma engines
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Stop the compute async dma queues (VI).
 */
अटल व्योम sdma_v3_0_rlc_stop(काष्ठा amdgpu_device *adev)
अणु
	/* XXX toकरो */
पूर्ण

/**
 * sdma_v3_0_ctx_चयन_enable - stop the async dma engines context चयन
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @enable: enable/disable the DMA MEs context चयन.
 *
 * Halt or unhalt the async dma engines context चयन (VI).
 */
अटल व्योम sdma_v3_0_ctx_चयन_enable(काष्ठा amdgpu_device *adev, bool enable)
अणु
	u32 f32_cntl, phase_quantum = 0;
	पूर्णांक i;

	अगर (amdgpu_sdma_phase_quantum) अणु
		अचिन्हित value = amdgpu_sdma_phase_quantum;
		अचिन्हित unit = 0;

		जबतक (value > (SDMA0_PHASE0_QUANTUM__VALUE_MASK >>
				SDMA0_PHASE0_QUANTUM__VALUE__SHIFT)) अणु
			value = (value + 1) >> 1;
			unit++;
		पूर्ण
		अगर (unit > (SDMA0_PHASE0_QUANTUM__UNIT_MASK >>
			    SDMA0_PHASE0_QUANTUM__UNIT__SHIFT)) अणु
			value = (SDMA0_PHASE0_QUANTUM__VALUE_MASK >>
				 SDMA0_PHASE0_QUANTUM__VALUE__SHIFT);
			unit = (SDMA0_PHASE0_QUANTUM__UNIT_MASK >>
				SDMA0_PHASE0_QUANTUM__UNIT__SHIFT);
			WARN_ONCE(1,
			"clamping sdma_phase_quantum to %uK clock cycles\n",
				  value << unit);
		पूर्ण
		phase_quantum =
			value << SDMA0_PHASE0_QUANTUM__VALUE__SHIFT |
			unit  << SDMA0_PHASE0_QUANTUM__UNIT__SHIFT;
	पूर्ण

	क्रम (i = 0; i < adev->sdma.num_instances; i++) अणु
		f32_cntl = RREG32(mmSDMA0_CNTL + sdma_offsets[i]);
		अगर (enable) अणु
			f32_cntl = REG_SET_FIELD(f32_cntl, SDMA0_CNTL,
					AUTO_CTXSW_ENABLE, 1);
			f32_cntl = REG_SET_FIELD(f32_cntl, SDMA0_CNTL,
					ATC_L1_ENABLE, 1);
			अगर (amdgpu_sdma_phase_quantum) अणु
				WREG32(mmSDMA0_PHASE0_QUANTUM + sdma_offsets[i],
				       phase_quantum);
				WREG32(mmSDMA0_PHASE1_QUANTUM + sdma_offsets[i],
				       phase_quantum);
			पूर्ण
		पूर्ण अन्यथा अणु
			f32_cntl = REG_SET_FIELD(f32_cntl, SDMA0_CNTL,
					AUTO_CTXSW_ENABLE, 0);
			f32_cntl = REG_SET_FIELD(f32_cntl, SDMA0_CNTL,
					ATC_L1_ENABLE, 1);
		पूर्ण

		WREG32(mmSDMA0_CNTL + sdma_offsets[i], f32_cntl);
	पूर्ण
पूर्ण

/**
 * sdma_v3_0_enable - stop the async dma engines
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @enable: enable/disable the DMA MEs.
 *
 * Halt or unhalt the async dma engines (VI).
 */
अटल व्योम sdma_v3_0_enable(काष्ठा amdgpu_device *adev, bool enable)
अणु
	u32 f32_cntl;
	पूर्णांक i;

	अगर (!enable) अणु
		sdma_v3_0_gfx_stop(adev);
		sdma_v3_0_rlc_stop(adev);
	पूर्ण

	क्रम (i = 0; i < adev->sdma.num_instances; i++) अणु
		f32_cntl = RREG32(mmSDMA0_F32_CNTL + sdma_offsets[i]);
		अगर (enable)
			f32_cntl = REG_SET_FIELD(f32_cntl, SDMA0_F32_CNTL, HALT, 0);
		अन्यथा
			f32_cntl = REG_SET_FIELD(f32_cntl, SDMA0_F32_CNTL, HALT, 1);
		WREG32(mmSDMA0_F32_CNTL + sdma_offsets[i], f32_cntl);
	पूर्ण
पूर्ण

/**
 * sdma_v3_0_gfx_resume - setup and start the async dma engines
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Set up the gfx DMA ring buffers and enable them (VI).
 * Returns 0 क्रम success, error क्रम failure.
 */
अटल पूर्णांक sdma_v3_0_gfx_resume(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_ring *ring;
	u32 rb_cntl, ib_cntl, wptr_poll_cntl;
	u32 rb_bufsz;
	u32 wb_offset;
	u32 करोorbell;
	u64 wptr_gpu_addr;
	पूर्णांक i, j, r;

	क्रम (i = 0; i < adev->sdma.num_instances; i++) अणु
		ring = &adev->sdma.instance[i].ring;
		amdgpu_ring_clear_ring(ring);
		wb_offset = (ring->rptr_offs * 4);

		mutex_lock(&adev->srbm_mutex);
		क्रम (j = 0; j < 16; j++) अणु
			vi_srbm_select(adev, 0, 0, 0, j);
			/* SDMA GFX */
			WREG32(mmSDMA0_GFX_VIRTUAL_ADDR + sdma_offsets[i], 0);
			WREG32(mmSDMA0_GFX_APE1_CNTL + sdma_offsets[i], 0);
		पूर्ण
		vi_srbm_select(adev, 0, 0, 0, 0);
		mutex_unlock(&adev->srbm_mutex);

		WREG32(mmSDMA0_TILING_CONFIG + sdma_offsets[i],
		       adev->gfx.config.gb_addr_config & 0x70);

		WREG32(mmSDMA0_SEM_WAIT_FAIL_TIMER_CNTL + sdma_offsets[i], 0);

		/* Set ring buffer size in dwords */
		rb_bufsz = order_base_2(ring->ring_size / 4);
		rb_cntl = RREG32(mmSDMA0_GFX_RB_CNTL + sdma_offsets[i]);
		rb_cntl = REG_SET_FIELD(rb_cntl, SDMA0_GFX_RB_CNTL, RB_SIZE, rb_bufsz);
#अगर_घोषित __BIG_ENDIAN
		rb_cntl = REG_SET_FIELD(rb_cntl, SDMA0_GFX_RB_CNTL, RB_SWAP_ENABLE, 1);
		rb_cntl = REG_SET_FIELD(rb_cntl, SDMA0_GFX_RB_CNTL,
					RPTR_WRITEBACK_SWAP_ENABLE, 1);
#पूर्ण_अगर
		WREG32(mmSDMA0_GFX_RB_CNTL + sdma_offsets[i], rb_cntl);

		/* Initialize the ring buffer's पढ़ो and ग_लिखो poपूर्णांकers */
		ring->wptr = 0;
		WREG32(mmSDMA0_GFX_RB_RPTR + sdma_offsets[i], 0);
		sdma_v3_0_ring_set_wptr(ring);
		WREG32(mmSDMA0_GFX_IB_RPTR + sdma_offsets[i], 0);
		WREG32(mmSDMA0_GFX_IB_OFFSET + sdma_offsets[i], 0);

		/* set the wb address whether it's enabled or not */
		WREG32(mmSDMA0_GFX_RB_RPTR_ADDR_HI + sdma_offsets[i],
		       upper_32_bits(adev->wb.gpu_addr + wb_offset) & 0xFFFFFFFF);
		WREG32(mmSDMA0_GFX_RB_RPTR_ADDR_LO + sdma_offsets[i],
		       lower_32_bits(adev->wb.gpu_addr + wb_offset) & 0xFFFFFFFC);

		rb_cntl = REG_SET_FIELD(rb_cntl, SDMA0_GFX_RB_CNTL, RPTR_WRITEBACK_ENABLE, 1);

		WREG32(mmSDMA0_GFX_RB_BASE + sdma_offsets[i], ring->gpu_addr >> 8);
		WREG32(mmSDMA0_GFX_RB_BASE_HI + sdma_offsets[i], ring->gpu_addr >> 40);

		करोorbell = RREG32(mmSDMA0_GFX_DOORBELL + sdma_offsets[i]);

		अगर (ring->use_करोorbell) अणु
			करोorbell = REG_SET_FIELD(करोorbell, SDMA0_GFX_DOORBELL,
						 OFFSET, ring->करोorbell_index);
			करोorbell = REG_SET_FIELD(करोorbell, SDMA0_GFX_DOORBELL, ENABLE, 1);
		पूर्ण अन्यथा अणु
			करोorbell = REG_SET_FIELD(करोorbell, SDMA0_GFX_DOORBELL, ENABLE, 0);
		पूर्ण
		WREG32(mmSDMA0_GFX_DOORBELL + sdma_offsets[i], करोorbell);

		/* setup the wptr shaकरोw polling */
		wptr_gpu_addr = adev->wb.gpu_addr + (ring->wptr_offs * 4);

		WREG32(mmSDMA0_GFX_RB_WPTR_POLL_ADDR_LO + sdma_offsets[i],
		       lower_32_bits(wptr_gpu_addr));
		WREG32(mmSDMA0_GFX_RB_WPTR_POLL_ADDR_HI + sdma_offsets[i],
		       upper_32_bits(wptr_gpu_addr));
		wptr_poll_cntl = RREG32(mmSDMA0_GFX_RB_WPTR_POLL_CNTL + sdma_offsets[i]);
		अगर (ring->use_pollmem) अणु
			/*wptr polling is not enogh fast, directly clean the wptr रेजिस्टर */
			WREG32(mmSDMA0_GFX_RB_WPTR + sdma_offsets[i], 0);
			wptr_poll_cntl = REG_SET_FIELD(wptr_poll_cntl,
						       SDMA0_GFX_RB_WPTR_POLL_CNTL,
						       ENABLE, 1);
		पूर्ण अन्यथा अणु
			wptr_poll_cntl = REG_SET_FIELD(wptr_poll_cntl,
						       SDMA0_GFX_RB_WPTR_POLL_CNTL,
						       ENABLE, 0);
		पूर्ण
		WREG32(mmSDMA0_GFX_RB_WPTR_POLL_CNTL + sdma_offsets[i], wptr_poll_cntl);

		/* enable DMA RB */
		rb_cntl = REG_SET_FIELD(rb_cntl, SDMA0_GFX_RB_CNTL, RB_ENABLE, 1);
		WREG32(mmSDMA0_GFX_RB_CNTL + sdma_offsets[i], rb_cntl);

		ib_cntl = RREG32(mmSDMA0_GFX_IB_CNTL + sdma_offsets[i]);
		ib_cntl = REG_SET_FIELD(ib_cntl, SDMA0_GFX_IB_CNTL, IB_ENABLE, 1);
#अगर_घोषित __BIG_ENDIAN
		ib_cntl = REG_SET_FIELD(ib_cntl, SDMA0_GFX_IB_CNTL, IB_SWAP_ENABLE, 1);
#पूर्ण_अगर
		/* enable DMA IBs */
		WREG32(mmSDMA0_GFX_IB_CNTL + sdma_offsets[i], ib_cntl);

		ring->sched.पढ़ोy = true;
	पूर्ण

	/* unhalt the MEs */
	sdma_v3_0_enable(adev, true);
	/* enable sdma ring preemption */
	sdma_v3_0_ctx_चयन_enable(adev, true);

	क्रम (i = 0; i < adev->sdma.num_instances; i++) अणु
		ring = &adev->sdma.instance[i].ring;
		r = amdgpu_ring_test_helper(ring);
		अगर (r)
			वापस r;

		अगर (adev->mman.buffer_funcs_ring == ring)
			amdgpu_tपंचांग_set_buffer_funcs_status(adev, true);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * sdma_v3_0_rlc_resume - setup and start the async dma engines
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Set up the compute DMA queues and enable them (VI).
 * Returns 0 क्रम success, error क्रम failure.
 */
अटल पूर्णांक sdma_v3_0_rlc_resume(काष्ठा amdgpu_device *adev)
अणु
	/* XXX toकरो */
	वापस 0;
पूर्ण

/**
 * sdma_v3_0_start - setup and start the async dma engines
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Set up the DMA engines and enable them (VI).
 * Returns 0 क्रम success, error क्रम failure.
 */
अटल पूर्णांक sdma_v3_0_start(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक r;

	/* disable sdma engine beक्रमe programing it */
	sdma_v3_0_ctx_चयन_enable(adev, false);
	sdma_v3_0_enable(adev, false);

	/* start the gfx rings and rlc compute queues */
	r = sdma_v3_0_gfx_resume(adev);
	अगर (r)
		वापस r;
	r = sdma_v3_0_rlc_resume(adev);
	अगर (r)
		वापस r;

	वापस 0;
पूर्ण

/**
 * sdma_v3_0_ring_test_ring - simple async dma engine test
 *
 * @ring: amdgpu_ring काष्ठाure holding ring inक्रमmation
 *
 * Test the DMA engine by writing using it to ग_लिखो an
 * value to memory. (VI).
 * Returns 0 क्रम success, error क्रम failure.
 */
अटल पूर्णांक sdma_v3_0_ring_test_ring(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;
	अचिन्हित i;
	अचिन्हित index;
	पूर्णांक r;
	u32 पंचांगp;
	u64 gpu_addr;

	r = amdgpu_device_wb_get(adev, &index);
	अगर (r)
		वापस r;

	gpu_addr = adev->wb.gpu_addr + (index * 4);
	पंचांगp = 0xCAFEDEAD;
	adev->wb.wb[index] = cpu_to_le32(पंचांगp);

	r = amdgpu_ring_alloc(ring, 5);
	अगर (r)
		जाओ error_मुक्त_wb;

	amdgpu_ring_ग_लिखो(ring, SDMA_PKT_HEADER_OP(SDMA_OP_WRITE) |
			  SDMA_PKT_HEADER_SUB_OP(SDMA_SUBOP_WRITE_LINEAR));
	amdgpu_ring_ग_लिखो(ring, lower_32_bits(gpu_addr));
	amdgpu_ring_ग_लिखो(ring, upper_32_bits(gpu_addr));
	amdgpu_ring_ग_लिखो(ring, SDMA_PKT_WRITE_UNTILED_DW_3_COUNT(1));
	amdgpu_ring_ग_लिखो(ring, 0xDEADBEEF);
	amdgpu_ring_commit(ring);

	क्रम (i = 0; i < adev->usec_समयout; i++) अणु
		पंचांगp = le32_to_cpu(adev->wb.wb[index]);
		अगर (पंचांगp == 0xDEADBEEF)
			अवरोध;
		udelay(1);
	पूर्ण

	अगर (i >= adev->usec_समयout)
		r = -ETIMEDOUT;

error_मुक्त_wb:
	amdgpu_device_wb_मुक्त(adev, index);
	वापस r;
पूर्ण

/**
 * sdma_v3_0_ring_test_ib - test an IB on the DMA engine
 *
 * @ring: amdgpu_ring काष्ठाure holding ring inक्रमmation
 * @समयout: समयout value in jअगरfies, or MAX_SCHEDULE_TIMEOUT
 *
 * Test a simple IB in the DMA ring (VI).
 * Returns 0 on success, error on failure.
 */
अटल पूर्णांक sdma_v3_0_ring_test_ib(काष्ठा amdgpu_ring *ring, दीर्घ समयout)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;
	काष्ठा amdgpu_ib ib;
	काष्ठा dma_fence *f = शून्य;
	अचिन्हित index;
	u32 पंचांगp = 0;
	u64 gpu_addr;
	दीर्घ r;

	r = amdgpu_device_wb_get(adev, &index);
	अगर (r)
		वापस r;

	gpu_addr = adev->wb.gpu_addr + (index * 4);
	पंचांगp = 0xCAFEDEAD;
	adev->wb.wb[index] = cpu_to_le32(पंचांगp);
	स_रखो(&ib, 0, माप(ib));
	r = amdgpu_ib_get(adev, शून्य, 256,
					AMDGPU_IB_POOL_सूचीECT, &ib);
	अगर (r)
		जाओ err0;

	ib.ptr[0] = SDMA_PKT_HEADER_OP(SDMA_OP_WRITE) |
		SDMA_PKT_HEADER_SUB_OP(SDMA_SUBOP_WRITE_LINEAR);
	ib.ptr[1] = lower_32_bits(gpu_addr);
	ib.ptr[2] = upper_32_bits(gpu_addr);
	ib.ptr[3] = SDMA_PKT_WRITE_UNTILED_DW_3_COUNT(1);
	ib.ptr[4] = 0xDEADBEEF;
	ib.ptr[5] = SDMA_PKT_NOP_HEADER_OP(SDMA_OP_NOP);
	ib.ptr[6] = SDMA_PKT_NOP_HEADER_OP(SDMA_OP_NOP);
	ib.ptr[7] = SDMA_PKT_NOP_HEADER_OP(SDMA_OP_NOP);
	ib.length_dw = 8;

	r = amdgpu_ib_schedule(ring, 1, &ib, शून्य, &f);
	अगर (r)
		जाओ err1;

	r = dma_fence_रुको_समयout(f, false, समयout);
	अगर (r == 0) अणु
		r = -ETIMEDOUT;
		जाओ err1;
	पूर्ण अन्यथा अगर (r < 0) अणु
		जाओ err1;
	पूर्ण
	पंचांगp = le32_to_cpu(adev->wb.wb[index]);
	अगर (पंचांगp == 0xDEADBEEF)
		r = 0;
	अन्यथा
		r = -EINVAL;
err1:
	amdgpu_ib_मुक्त(adev, &ib, शून्य);
	dma_fence_put(f);
err0:
	amdgpu_device_wb_मुक्त(adev, index);
	वापस r;
पूर्ण

/**
 * sdma_v3_0_vm_copy_pte - update PTEs by copying them from the GART
 *
 * @ib: indirect buffer to fill with commands
 * @pe: addr of the page entry
 * @src: src addr to copy from
 * @count: number of page entries to update
 *
 * Update PTEs by copying them from the GART using sDMA (CIK).
 */
अटल व्योम sdma_v3_0_vm_copy_pte(काष्ठा amdgpu_ib *ib,
				  uपूर्णांक64_t pe, uपूर्णांक64_t src,
				  अचिन्हित count)
अणु
	अचिन्हित bytes = count * 8;

	ib->ptr[ib->length_dw++] = SDMA_PKT_HEADER_OP(SDMA_OP_COPY) |
		SDMA_PKT_HEADER_SUB_OP(SDMA_SUBOP_COPY_LINEAR);
	ib->ptr[ib->length_dw++] = bytes;
	ib->ptr[ib->length_dw++] = 0; /* src/dst endian swap */
	ib->ptr[ib->length_dw++] = lower_32_bits(src);
	ib->ptr[ib->length_dw++] = upper_32_bits(src);
	ib->ptr[ib->length_dw++] = lower_32_bits(pe);
	ib->ptr[ib->length_dw++] = upper_32_bits(pe);
पूर्ण

/**
 * sdma_v3_0_vm_ग_लिखो_pte - update PTEs by writing them manually
 *
 * @ib: indirect buffer to fill with commands
 * @pe: addr of the page entry
 * @value: dst addr to ग_लिखो पूर्णांकo pe
 * @count: number of page entries to update
 * @incr: increase next addr by incr bytes
 *
 * Update PTEs by writing them manually using sDMA (CIK).
 */
अटल व्योम sdma_v3_0_vm_ग_लिखो_pte(काष्ठा amdgpu_ib *ib, uपूर्णांक64_t pe,
				   uपूर्णांक64_t value, अचिन्हित count,
				   uपूर्णांक32_t incr)
अणु
	अचिन्हित ndw = count * 2;

	ib->ptr[ib->length_dw++] = SDMA_PKT_HEADER_OP(SDMA_OP_WRITE) |
		SDMA_PKT_HEADER_SUB_OP(SDMA_SUBOP_WRITE_LINEAR);
	ib->ptr[ib->length_dw++] = lower_32_bits(pe);
	ib->ptr[ib->length_dw++] = upper_32_bits(pe);
	ib->ptr[ib->length_dw++] = ndw;
	क्रम (; ndw > 0; ndw -= 2) अणु
		ib->ptr[ib->length_dw++] = lower_32_bits(value);
		ib->ptr[ib->length_dw++] = upper_32_bits(value);
		value += incr;
	पूर्ण
पूर्ण

/**
 * sdma_v3_0_vm_set_pte_pde - update the page tables using sDMA
 *
 * @ib: indirect buffer to fill with commands
 * @pe: addr of the page entry
 * @addr: dst addr to ग_लिखो पूर्णांकo pe
 * @count: number of page entries to update
 * @incr: increase next addr by incr bytes
 * @flags: access flags
 *
 * Update the page tables using sDMA (CIK).
 */
अटल व्योम sdma_v3_0_vm_set_pte_pde(काष्ठा amdgpu_ib *ib, uपूर्णांक64_t pe,
				     uपूर्णांक64_t addr, अचिन्हित count,
				     uपूर्णांक32_t incr, uपूर्णांक64_t flags)
अणु
	/* क्रम physically contiguous pages (vram) */
	ib->ptr[ib->length_dw++] = SDMA_PKT_HEADER_OP(SDMA_OP_GEN_PTEPDE);
	ib->ptr[ib->length_dw++] = lower_32_bits(pe); /* dst addr */
	ib->ptr[ib->length_dw++] = upper_32_bits(pe);
	ib->ptr[ib->length_dw++] = lower_32_bits(flags); /* mask */
	ib->ptr[ib->length_dw++] = upper_32_bits(flags);
	ib->ptr[ib->length_dw++] = lower_32_bits(addr); /* value */
	ib->ptr[ib->length_dw++] = upper_32_bits(addr);
	ib->ptr[ib->length_dw++] = incr; /* increment size */
	ib->ptr[ib->length_dw++] = 0;
	ib->ptr[ib->length_dw++] = count; /* number of entries */
पूर्ण

/**
 * sdma_v3_0_ring_pad_ib - pad the IB to the required number of dw
 *
 * @ring: amdgpu_ring काष्ठाure holding ring inक्रमmation
 * @ib: indirect buffer to fill with padding
 *
 */
अटल व्योम sdma_v3_0_ring_pad_ib(काष्ठा amdgpu_ring *ring, काष्ठा amdgpu_ib *ib)
अणु
	काष्ठा amdgpu_sdma_instance *sdma = amdgpu_sdma_get_instance_from_ring(ring);
	u32 pad_count;
	पूर्णांक i;

	pad_count = (-ib->length_dw) & 7;
	क्रम (i = 0; i < pad_count; i++)
		अगर (sdma && sdma->burst_nop && (i == 0))
			ib->ptr[ib->length_dw++] =
				SDMA_PKT_HEADER_OP(SDMA_OP_NOP) |
				SDMA_PKT_NOP_HEADER_COUNT(pad_count - 1);
		अन्यथा
			ib->ptr[ib->length_dw++] =
				SDMA_PKT_HEADER_OP(SDMA_OP_NOP);
पूर्ण

/**
 * sdma_v3_0_ring_emit_pipeline_sync - sync the pipeline
 *
 * @ring: amdgpu_ring poपूर्णांकer
 *
 * Make sure all previous operations are completed (CIK).
 */
अटल व्योम sdma_v3_0_ring_emit_pipeline_sync(काष्ठा amdgpu_ring *ring)
अणु
	uपूर्णांक32_t seq = ring->fence_drv.sync_seq;
	uपूर्णांक64_t addr = ring->fence_drv.gpu_addr;

	/* रुको क्रम idle */
	amdgpu_ring_ग_लिखो(ring, SDMA_PKT_HEADER_OP(SDMA_OP_POLL_REGMEM) |
			  SDMA_PKT_POLL_REGMEM_HEADER_HDP_FLUSH(0) |
			  SDMA_PKT_POLL_REGMEM_HEADER_FUNC(3) | /* equal */
			  SDMA_PKT_POLL_REGMEM_HEADER_MEM_POLL(1));
	amdgpu_ring_ग_लिखो(ring, addr & 0xfffffffc);
	amdgpu_ring_ग_लिखो(ring, upper_32_bits(addr) & 0xffffffff);
	amdgpu_ring_ग_लिखो(ring, seq); /* reference */
	amdgpu_ring_ग_लिखो(ring, 0xffffffff); /* mask */
	amdgpu_ring_ग_लिखो(ring, SDMA_PKT_POLL_REGMEM_DW5_RETRY_COUNT(0xfff) |
			  SDMA_PKT_POLL_REGMEM_DW5_INTERVAL(4)); /* retry count, poll पूर्णांकerval */
पूर्ण

/**
 * sdma_v3_0_ring_emit_vm_flush - cik vm flush using sDMA
 *
 * @ring: amdgpu_ring poपूर्णांकer
 * @vmid: vmid number to use
 * @pd_addr: address
 *
 * Update the page table base and flush the VM TLB
 * using sDMA (VI).
 */
अटल व्योम sdma_v3_0_ring_emit_vm_flush(काष्ठा amdgpu_ring *ring,
					 अचिन्हित vmid, uपूर्णांक64_t pd_addr)
अणु
	amdgpu_gmc_emit_flush_gpu_tlb(ring, vmid, pd_addr);

	/* रुको क्रम flush */
	amdgpu_ring_ग_लिखो(ring, SDMA_PKT_HEADER_OP(SDMA_OP_POLL_REGMEM) |
			  SDMA_PKT_POLL_REGMEM_HEADER_HDP_FLUSH(0) |
			  SDMA_PKT_POLL_REGMEM_HEADER_FUNC(0)); /* always */
	amdgpu_ring_ग_लिखो(ring, mmVM_INVALIDATE_REQUEST << 2);
	amdgpu_ring_ग_लिखो(ring, 0);
	amdgpu_ring_ग_लिखो(ring, 0); /* reference */
	amdgpu_ring_ग_लिखो(ring, 0); /* mask */
	amdgpu_ring_ग_लिखो(ring, SDMA_PKT_POLL_REGMEM_DW5_RETRY_COUNT(0xfff) |
			  SDMA_PKT_POLL_REGMEM_DW5_INTERVAL(10)); /* retry count, poll पूर्णांकerval */
पूर्ण

अटल व्योम sdma_v3_0_ring_emit_wreg(काष्ठा amdgpu_ring *ring,
				     uपूर्णांक32_t reg, uपूर्णांक32_t val)
अणु
	amdgpu_ring_ग_लिखो(ring, SDMA_PKT_HEADER_OP(SDMA_OP_SRBM_WRITE) |
			  SDMA_PKT_SRBM_WRITE_HEADER_BYTE_EN(0xf));
	amdgpu_ring_ग_लिखो(ring, reg);
	amdgpu_ring_ग_लिखो(ring, val);
पूर्ण

अटल पूर्णांक sdma_v3_0_early_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	चयन (adev->asic_type) अणु
	हाल CHIP_STONEY:
		adev->sdma.num_instances = 1;
		अवरोध;
	शेष:
		adev->sdma.num_instances = SDMA_MAX_INSTANCE;
		अवरोध;
	पूर्ण

	sdma_v3_0_set_ring_funcs(adev);
	sdma_v3_0_set_buffer_funcs(adev);
	sdma_v3_0_set_vm_pte_funcs(adev);
	sdma_v3_0_set_irq_funcs(adev);

	वापस 0;
पूर्ण

अटल पूर्णांक sdma_v3_0_sw_init(व्योम *handle)
अणु
	काष्ठा amdgpu_ring *ring;
	पूर्णांक r, i;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	/* SDMA trap event */
	r = amdgpu_irq_add_id(adev, AMDGPU_IRQ_CLIENTID_LEGACY, VISLANDS30_IV_SRCID_SDMA_TRAP,
			      &adev->sdma.trap_irq);
	अगर (r)
		वापस r;

	/* SDMA Privileged inst */
	r = amdgpu_irq_add_id(adev, AMDGPU_IRQ_CLIENTID_LEGACY, 241,
			      &adev->sdma.illegal_inst_irq);
	अगर (r)
		वापस r;

	/* SDMA Privileged inst */
	r = amdgpu_irq_add_id(adev, AMDGPU_IRQ_CLIENTID_LEGACY, VISLANDS30_IV_SRCID_SDMA_SRBM_WRITE,
			      &adev->sdma.illegal_inst_irq);
	अगर (r)
		वापस r;

	r = sdma_v3_0_init_microcode(adev);
	अगर (r) अणु
		DRM_ERROR("Failed to load sdma firmware!\n");
		वापस r;
	पूर्ण

	क्रम (i = 0; i < adev->sdma.num_instances; i++) अणु
		ring = &adev->sdma.instance[i].ring;
		ring->ring_obj = शून्य;
		अगर (!amdgpu_sriov_vf(adev)) अणु
			ring->use_करोorbell = true;
			ring->करोorbell_index = adev->करोorbell_index.sdma_engine[i];
		पूर्ण अन्यथा अणु
			ring->use_pollmem = true;
		पूर्ण

		प्र_लिखो(ring->name, "sdma%d", i);
		r = amdgpu_ring_init(adev, ring, 1024, &adev->sdma.trap_irq,
				     (i == 0) ? AMDGPU_SDMA_IRQ_INSTANCE0 :
				     AMDGPU_SDMA_IRQ_INSTANCE1,
				     AMDGPU_RING_PRIO_DEFAULT, शून्य);
		अगर (r)
			वापस r;
	पूर्ण

	वापस r;
पूर्ण

अटल पूर्णांक sdma_v3_0_sw_fini(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	पूर्णांक i;

	क्रम (i = 0; i < adev->sdma.num_instances; i++)
		amdgpu_ring_fini(&adev->sdma.instance[i].ring);

	sdma_v3_0_मुक्त_microcode(adev);
	वापस 0;
पूर्ण

अटल पूर्णांक sdma_v3_0_hw_init(व्योम *handle)
अणु
	पूर्णांक r;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	sdma_v3_0_init_golden_रेजिस्टरs(adev);

	r = sdma_v3_0_start(adev);
	अगर (r)
		वापस r;

	वापस r;
पूर्ण

अटल पूर्णांक sdma_v3_0_hw_fini(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	sdma_v3_0_ctx_चयन_enable(adev, false);
	sdma_v3_0_enable(adev, false);

	वापस 0;
पूर्ण

अटल पूर्णांक sdma_v3_0_suspend(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	वापस sdma_v3_0_hw_fini(adev);
पूर्ण

अटल पूर्णांक sdma_v3_0_resume(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	वापस sdma_v3_0_hw_init(adev);
पूर्ण

अटल bool sdma_v3_0_is_idle(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	u32 पंचांगp = RREG32(mmSRBM_STATUS2);

	अगर (पंचांगp & (SRBM_STATUS2__SDMA_BUSY_MASK |
		   SRBM_STATUS2__SDMA1_BUSY_MASK))
	    वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक sdma_v3_0_रुको_क्रम_idle(व्योम *handle)
अणु
	अचिन्हित i;
	u32 पंचांगp;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	क्रम (i = 0; i < adev->usec_समयout; i++) अणु
		पंचांगp = RREG32(mmSRBM_STATUS2) & (SRBM_STATUS2__SDMA_BUSY_MASK |
				SRBM_STATUS2__SDMA1_BUSY_MASK);

		अगर (!पंचांगp)
			वापस 0;
		udelay(1);
	पूर्ण
	वापस -ETIMEDOUT;
पूर्ण

अटल bool sdma_v3_0_check_soft_reset(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	u32 srbm_soft_reset = 0;
	u32 पंचांगp = RREG32(mmSRBM_STATUS2);

	अगर ((पंचांगp & SRBM_STATUS2__SDMA_BUSY_MASK) ||
	    (पंचांगp & SRBM_STATUS2__SDMA1_BUSY_MASK)) अणु
		srbm_soft_reset |= SRBM_SOFT_RESET__SOFT_RESET_SDMA_MASK;
		srbm_soft_reset |= SRBM_SOFT_RESET__SOFT_RESET_SDMA1_MASK;
	पूर्ण

	अगर (srbm_soft_reset) अणु
		adev->sdma.srbm_soft_reset = srbm_soft_reset;
		वापस true;
	पूर्ण अन्यथा अणु
		adev->sdma.srbm_soft_reset = 0;
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक sdma_v3_0_pre_soft_reset(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	u32 srbm_soft_reset = 0;

	अगर (!adev->sdma.srbm_soft_reset)
		वापस 0;

	srbm_soft_reset = adev->sdma.srbm_soft_reset;

	अगर (REG_GET_FIELD(srbm_soft_reset, SRBM_SOFT_RESET, SOFT_RESET_SDMA) ||
	    REG_GET_FIELD(srbm_soft_reset, SRBM_SOFT_RESET, SOFT_RESET_SDMA1)) अणु
		sdma_v3_0_ctx_चयन_enable(adev, false);
		sdma_v3_0_enable(adev, false);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sdma_v3_0_post_soft_reset(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	u32 srbm_soft_reset = 0;

	अगर (!adev->sdma.srbm_soft_reset)
		वापस 0;

	srbm_soft_reset = adev->sdma.srbm_soft_reset;

	अगर (REG_GET_FIELD(srbm_soft_reset, SRBM_SOFT_RESET, SOFT_RESET_SDMA) ||
	    REG_GET_FIELD(srbm_soft_reset, SRBM_SOFT_RESET, SOFT_RESET_SDMA1)) अणु
		sdma_v3_0_gfx_resume(adev);
		sdma_v3_0_rlc_resume(adev);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sdma_v3_0_soft_reset(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	u32 srbm_soft_reset = 0;
	u32 पंचांगp;

	अगर (!adev->sdma.srbm_soft_reset)
		वापस 0;

	srbm_soft_reset = adev->sdma.srbm_soft_reset;

	अगर (srbm_soft_reset) अणु
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

अटल पूर्णांक sdma_v3_0_set_trap_irq_state(काष्ठा amdgpu_device *adev,
					काष्ठा amdgpu_irq_src *source,
					अचिन्हित type,
					क्रमागत amdgpu_पूर्णांकerrupt_state state)
अणु
	u32 sdma_cntl;

	चयन (type) अणु
	हाल AMDGPU_SDMA_IRQ_INSTANCE0:
		चयन (state) अणु
		हाल AMDGPU_IRQ_STATE_DISABLE:
			sdma_cntl = RREG32(mmSDMA0_CNTL + SDMA0_REGISTER_OFFSET);
			sdma_cntl = REG_SET_FIELD(sdma_cntl, SDMA0_CNTL, TRAP_ENABLE, 0);
			WREG32(mmSDMA0_CNTL + SDMA0_REGISTER_OFFSET, sdma_cntl);
			अवरोध;
		हाल AMDGPU_IRQ_STATE_ENABLE:
			sdma_cntl = RREG32(mmSDMA0_CNTL + SDMA0_REGISTER_OFFSET);
			sdma_cntl = REG_SET_FIELD(sdma_cntl, SDMA0_CNTL, TRAP_ENABLE, 1);
			WREG32(mmSDMA0_CNTL + SDMA0_REGISTER_OFFSET, sdma_cntl);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल AMDGPU_SDMA_IRQ_INSTANCE1:
		चयन (state) अणु
		हाल AMDGPU_IRQ_STATE_DISABLE:
			sdma_cntl = RREG32(mmSDMA0_CNTL + SDMA1_REGISTER_OFFSET);
			sdma_cntl = REG_SET_FIELD(sdma_cntl, SDMA0_CNTL, TRAP_ENABLE, 0);
			WREG32(mmSDMA0_CNTL + SDMA1_REGISTER_OFFSET, sdma_cntl);
			अवरोध;
		हाल AMDGPU_IRQ_STATE_ENABLE:
			sdma_cntl = RREG32(mmSDMA0_CNTL + SDMA1_REGISTER_OFFSET);
			sdma_cntl = REG_SET_FIELD(sdma_cntl, SDMA0_CNTL, TRAP_ENABLE, 1);
			WREG32(mmSDMA0_CNTL + SDMA1_REGISTER_OFFSET, sdma_cntl);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक sdma_v3_0_process_trap_irq(काष्ठा amdgpu_device *adev,
				      काष्ठा amdgpu_irq_src *source,
				      काष्ठा amdgpu_iv_entry *entry)
अणु
	u8 instance_id, queue_id;

	instance_id = (entry->ring_id & 0x3) >> 0;
	queue_id = (entry->ring_id & 0xc) >> 2;
	DRM_DEBUG("IH: SDMA trap\n");
	चयन (instance_id) अणु
	हाल 0:
		चयन (queue_id) अणु
		हाल 0:
			amdgpu_fence_process(&adev->sdma.instance[0].ring);
			अवरोध;
		हाल 1:
			/* XXX compute */
			अवरोध;
		हाल 2:
			/* XXX compute */
			अवरोध;
		पूर्ण
		अवरोध;
	हाल 1:
		चयन (queue_id) अणु
		हाल 0:
			amdgpu_fence_process(&adev->sdma.instance[1].ring);
			अवरोध;
		हाल 1:
			/* XXX compute */
			अवरोध;
		हाल 2:
			/* XXX compute */
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक sdma_v3_0_process_illegal_inst_irq(काष्ठा amdgpu_device *adev,
					      काष्ठा amdgpu_irq_src *source,
					      काष्ठा amdgpu_iv_entry *entry)
अणु
	u8 instance_id, queue_id;

	DRM_ERROR("Illegal instruction in SDMA command stream\n");
	instance_id = (entry->ring_id & 0x3) >> 0;
	queue_id = (entry->ring_id & 0xc) >> 2;

	अगर (instance_id <= 1 && queue_id == 0)
		drm_sched_fault(&adev->sdma.instance[instance_id].ring.sched);
	वापस 0;
पूर्ण

अटल व्योम sdma_v3_0_update_sdma_medium_grain_घड़ी_gating(
		काष्ठा amdgpu_device *adev,
		bool enable)
अणु
	uपूर्णांक32_t temp, data;
	पूर्णांक i;

	अगर (enable && (adev->cg_flags & AMD_CG_SUPPORT_SDMA_MGCG)) अणु
		क्रम (i = 0; i < adev->sdma.num_instances; i++) अणु
			temp = data = RREG32(mmSDMA0_CLK_CTRL + sdma_offsets[i]);
			data &= ~(SDMA0_CLK_CTRL__SOFT_OVERRIDE7_MASK |
				  SDMA0_CLK_CTRL__SOFT_OVERRIDE6_MASK |
				  SDMA0_CLK_CTRL__SOFT_OVERRIDE5_MASK |
				  SDMA0_CLK_CTRL__SOFT_OVERRIDE4_MASK |
				  SDMA0_CLK_CTRL__SOFT_OVERRIDE3_MASK |
				  SDMA0_CLK_CTRL__SOFT_OVERRIDE2_MASK |
				  SDMA0_CLK_CTRL__SOFT_OVERRIDE1_MASK |
				  SDMA0_CLK_CTRL__SOFT_OVERRIDE0_MASK);
			अगर (data != temp)
				WREG32(mmSDMA0_CLK_CTRL + sdma_offsets[i], data);
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < adev->sdma.num_instances; i++) अणु
			temp = data = RREG32(mmSDMA0_CLK_CTRL + sdma_offsets[i]);
			data |= SDMA0_CLK_CTRL__SOFT_OVERRIDE7_MASK |
				SDMA0_CLK_CTRL__SOFT_OVERRIDE6_MASK |
				SDMA0_CLK_CTRL__SOFT_OVERRIDE5_MASK |
				SDMA0_CLK_CTRL__SOFT_OVERRIDE4_MASK |
				SDMA0_CLK_CTRL__SOFT_OVERRIDE3_MASK |
				SDMA0_CLK_CTRL__SOFT_OVERRIDE2_MASK |
				SDMA0_CLK_CTRL__SOFT_OVERRIDE1_MASK |
				SDMA0_CLK_CTRL__SOFT_OVERRIDE0_MASK;

			अगर (data != temp)
				WREG32(mmSDMA0_CLK_CTRL + sdma_offsets[i], data);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम sdma_v3_0_update_sdma_medium_grain_light_sleep(
		काष्ठा amdgpu_device *adev,
		bool enable)
अणु
	uपूर्णांक32_t temp, data;
	पूर्णांक i;

	अगर (enable && (adev->cg_flags & AMD_CG_SUPPORT_SDMA_LS)) अणु
		क्रम (i = 0; i < adev->sdma.num_instances; i++) अणु
			temp = data = RREG32(mmSDMA0_POWER_CNTL + sdma_offsets[i]);
			data |= SDMA0_POWER_CNTL__MEM_POWER_OVERRIDE_MASK;

			अगर (temp != data)
				WREG32(mmSDMA0_POWER_CNTL + sdma_offsets[i], data);
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < adev->sdma.num_instances; i++) अणु
			temp = data = RREG32(mmSDMA0_POWER_CNTL + sdma_offsets[i]);
			data &= ~SDMA0_POWER_CNTL__MEM_POWER_OVERRIDE_MASK;

			अगर (temp != data)
				WREG32(mmSDMA0_POWER_CNTL + sdma_offsets[i], data);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक sdma_v3_0_set_घड़ीgating_state(व्योम *handle,
					  क्रमागत amd_घड़ीgating_state state)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	अगर (amdgpu_sriov_vf(adev))
		वापस 0;

	चयन (adev->asic_type) अणु
	हाल CHIP_FIJI:
	हाल CHIP_CARRIZO:
	हाल CHIP_STONEY:
		sdma_v3_0_update_sdma_medium_grain_घड़ी_gating(adev,
				state == AMD_CG_STATE_GATE);
		sdma_v3_0_update_sdma_medium_grain_light_sleep(adev,
				state == AMD_CG_STATE_GATE);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक sdma_v3_0_set_घातergating_state(व्योम *handle,
					  क्रमागत amd_घातergating_state state)
अणु
	वापस 0;
पूर्ण

अटल व्योम sdma_v3_0_get_घड़ीgating_state(व्योम *handle, u32 *flags)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	पूर्णांक data;

	अगर (amdgpu_sriov_vf(adev))
		*flags = 0;

	/* AMD_CG_SUPPORT_SDMA_MGCG */
	data = RREG32(mmSDMA0_CLK_CTRL + sdma_offsets[0]);
	अगर (!(data & SDMA0_CLK_CTRL__SOFT_OVERRIDE0_MASK))
		*flags |= AMD_CG_SUPPORT_SDMA_MGCG;

	/* AMD_CG_SUPPORT_SDMA_LS */
	data = RREG32(mmSDMA0_POWER_CNTL + sdma_offsets[0]);
	अगर (data & SDMA0_POWER_CNTL__MEM_POWER_OVERRIDE_MASK)
		*flags |= AMD_CG_SUPPORT_SDMA_LS;
पूर्ण

अटल स्थिर काष्ठा amd_ip_funcs sdma_v3_0_ip_funcs = अणु
	.name = "sdma_v3_0",
	.early_init = sdma_v3_0_early_init,
	.late_init = शून्य,
	.sw_init = sdma_v3_0_sw_init,
	.sw_fini = sdma_v3_0_sw_fini,
	.hw_init = sdma_v3_0_hw_init,
	.hw_fini = sdma_v3_0_hw_fini,
	.suspend = sdma_v3_0_suspend,
	.resume = sdma_v3_0_resume,
	.is_idle = sdma_v3_0_is_idle,
	.रुको_क्रम_idle = sdma_v3_0_रुको_क्रम_idle,
	.check_soft_reset = sdma_v3_0_check_soft_reset,
	.pre_soft_reset = sdma_v3_0_pre_soft_reset,
	.post_soft_reset = sdma_v3_0_post_soft_reset,
	.soft_reset = sdma_v3_0_soft_reset,
	.set_घड़ीgating_state = sdma_v3_0_set_घड़ीgating_state,
	.set_घातergating_state = sdma_v3_0_set_घातergating_state,
	.get_घड़ीgating_state = sdma_v3_0_get_घड़ीgating_state,
पूर्ण;

अटल स्थिर काष्ठा amdgpu_ring_funcs sdma_v3_0_ring_funcs = अणु
	.type = AMDGPU_RING_TYPE_SDMA,
	.align_mask = 0xf,
	.nop = SDMA_PKT_NOP_HEADER_OP(SDMA_OP_NOP),
	.support_64bit_ptrs = false,
	.get_rptr = sdma_v3_0_ring_get_rptr,
	.get_wptr = sdma_v3_0_ring_get_wptr,
	.set_wptr = sdma_v3_0_ring_set_wptr,
	.emit_frame_size =
		6 + /* sdma_v3_0_ring_emit_hdp_flush */
		3 + /* hdp invalidate */
		6 + /* sdma_v3_0_ring_emit_pipeline_sync */
		VI_FLUSH_GPU_TLB_NUM_WREG * 3 + 6 + /* sdma_v3_0_ring_emit_vm_flush */
		10 + 10 + 10, /* sdma_v3_0_ring_emit_fence x3 क्रम user fence, vm fence */
	.emit_ib_size = 7 + 6, /* sdma_v3_0_ring_emit_ib */
	.emit_ib = sdma_v3_0_ring_emit_ib,
	.emit_fence = sdma_v3_0_ring_emit_fence,
	.emit_pipeline_sync = sdma_v3_0_ring_emit_pipeline_sync,
	.emit_vm_flush = sdma_v3_0_ring_emit_vm_flush,
	.emit_hdp_flush = sdma_v3_0_ring_emit_hdp_flush,
	.test_ring = sdma_v3_0_ring_test_ring,
	.test_ib = sdma_v3_0_ring_test_ib,
	.insert_nop = sdma_v3_0_ring_insert_nop,
	.pad_ib = sdma_v3_0_ring_pad_ib,
	.emit_wreg = sdma_v3_0_ring_emit_wreg,
पूर्ण;

अटल व्योम sdma_v3_0_set_ring_funcs(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < adev->sdma.num_instances; i++) अणु
		adev->sdma.instance[i].ring.funcs = &sdma_v3_0_ring_funcs;
		adev->sdma.instance[i].ring.me = i;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा amdgpu_irq_src_funcs sdma_v3_0_trap_irq_funcs = अणु
	.set = sdma_v3_0_set_trap_irq_state,
	.process = sdma_v3_0_process_trap_irq,
पूर्ण;

अटल स्थिर काष्ठा amdgpu_irq_src_funcs sdma_v3_0_illegal_inst_irq_funcs = अणु
	.process = sdma_v3_0_process_illegal_inst_irq,
पूर्ण;

अटल व्योम sdma_v3_0_set_irq_funcs(काष्ठा amdgpu_device *adev)
अणु
	adev->sdma.trap_irq.num_types = AMDGPU_SDMA_IRQ_LAST;
	adev->sdma.trap_irq.funcs = &sdma_v3_0_trap_irq_funcs;
	adev->sdma.illegal_inst_irq.funcs = &sdma_v3_0_illegal_inst_irq_funcs;
पूर्ण

/**
 * sdma_v3_0_emit_copy_buffer - copy buffer using the sDMA engine
 *
 * @ib: indirect buffer to copy to
 * @src_offset: src GPU address
 * @dst_offset: dst GPU address
 * @byte_count: number of bytes to xfer
 * @पंचांगz: unused
 *
 * Copy GPU buffers using the DMA engine (VI).
 * Used by the amdgpu tपंचांग implementation to move pages अगर
 * रेजिस्टरed as the asic copy callback.
 */
अटल व्योम sdma_v3_0_emit_copy_buffer(काष्ठा amdgpu_ib *ib,
				       uपूर्णांक64_t src_offset,
				       uपूर्णांक64_t dst_offset,
				       uपूर्णांक32_t byte_count,
				       bool पंचांगz)
अणु
	ib->ptr[ib->length_dw++] = SDMA_PKT_HEADER_OP(SDMA_OP_COPY) |
		SDMA_PKT_HEADER_SUB_OP(SDMA_SUBOP_COPY_LINEAR);
	ib->ptr[ib->length_dw++] = byte_count;
	ib->ptr[ib->length_dw++] = 0; /* src/dst endian swap */
	ib->ptr[ib->length_dw++] = lower_32_bits(src_offset);
	ib->ptr[ib->length_dw++] = upper_32_bits(src_offset);
	ib->ptr[ib->length_dw++] = lower_32_bits(dst_offset);
	ib->ptr[ib->length_dw++] = upper_32_bits(dst_offset);
पूर्ण

/**
 * sdma_v3_0_emit_fill_buffer - fill buffer using the sDMA engine
 *
 * @ib: indirect buffer to copy to
 * @src_data: value to ग_लिखो to buffer
 * @dst_offset: dst GPU address
 * @byte_count: number of bytes to xfer
 *
 * Fill GPU buffers using the DMA engine (VI).
 */
अटल व्योम sdma_v3_0_emit_fill_buffer(काष्ठा amdgpu_ib *ib,
				       uपूर्णांक32_t src_data,
				       uपूर्णांक64_t dst_offset,
				       uपूर्णांक32_t byte_count)
अणु
	ib->ptr[ib->length_dw++] = SDMA_PKT_HEADER_OP(SDMA_OP_CONST_FILL);
	ib->ptr[ib->length_dw++] = lower_32_bits(dst_offset);
	ib->ptr[ib->length_dw++] = upper_32_bits(dst_offset);
	ib->ptr[ib->length_dw++] = src_data;
	ib->ptr[ib->length_dw++] = byte_count;
पूर्ण

अटल स्थिर काष्ठा amdgpu_buffer_funcs sdma_v3_0_buffer_funcs = अणु
	.copy_max_bytes = 0x3fffe0, /* not 0x3fffff due to HW limitation */
	.copy_num_dw = 7,
	.emit_copy_buffer = sdma_v3_0_emit_copy_buffer,

	.fill_max_bytes = 0x3fffe0, /* not 0x3fffff due to HW limitation */
	.fill_num_dw = 5,
	.emit_fill_buffer = sdma_v3_0_emit_fill_buffer,
पूर्ण;

अटल व्योम sdma_v3_0_set_buffer_funcs(काष्ठा amdgpu_device *adev)
अणु
	adev->mman.buffer_funcs = &sdma_v3_0_buffer_funcs;
	adev->mman.buffer_funcs_ring = &adev->sdma.instance[0].ring;
पूर्ण

अटल स्थिर काष्ठा amdgpu_vm_pte_funcs sdma_v3_0_vm_pte_funcs = अणु
	.copy_pte_num_dw = 7,
	.copy_pte = sdma_v3_0_vm_copy_pte,

	.ग_लिखो_pte = sdma_v3_0_vm_ग_लिखो_pte,
	.set_pte_pde = sdma_v3_0_vm_set_pte_pde,
पूर्ण;

अटल व्योम sdma_v3_0_set_vm_pte_funcs(काष्ठा amdgpu_device *adev)
अणु
	अचिन्हित i;

	adev->vm_manager.vm_pte_funcs = &sdma_v3_0_vm_pte_funcs;
	क्रम (i = 0; i < adev->sdma.num_instances; i++) अणु
		adev->vm_manager.vm_pte_scheds[i] =
			 &adev->sdma.instance[i].ring.sched;
	पूर्ण
	adev->vm_manager.vm_pte_num_scheds = adev->sdma.num_instances;
पूर्ण

स्थिर काष्ठा amdgpu_ip_block_version sdma_v3_0_ip_block =
अणु
	.type = AMD_IP_BLOCK_TYPE_SDMA,
	.major = 3,
	.minor = 0,
	.rev = 0,
	.funcs = &sdma_v3_0_ip_funcs,
पूर्ण;

स्थिर काष्ठा amdgpu_ip_block_version sdma_v3_1_ip_block =
अणु
	.type = AMD_IP_BLOCK_TYPE_SDMA,
	.major = 3,
	.minor = 1,
	.rev = 0,
	.funcs = &sdma_v3_0_ip_funcs,
पूर्ण;
