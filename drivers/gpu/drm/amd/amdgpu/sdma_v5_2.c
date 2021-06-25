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

#समावेश <linux/delay.h>
#समावेश <linux/firmware.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>

#समावेश "amdgpu.h"
#समावेश "amdgpu_ucode.h"
#समावेश "amdgpu_trace.h"

#समावेश "gc/gc_10_3_0_offset.h"
#समावेश "gc/gc_10_3_0_sh_mask.h"
#समावेश "ivsrcid/sdma0/irqsrcs_sdma0_5_0.h"
#समावेश "ivsrcid/sdma1/irqsrcs_sdma1_5_0.h"
#समावेश "ivsrcid/sdma2/irqsrcs_sdma2_5_0.h"
#समावेश "ivsrcid/sdma3/irqsrcs_sdma3_5_0.h"

#समावेश "soc15_common.h"
#समावेश "soc15.h"
#समावेश "navi10_sdma_pkt_open.h"
#समावेश "nbio_v2_3.h"
#समावेश "sdma_common.h"
#समावेश "sdma_v5_2.h"

MODULE_FIRMWARE("amdgpu/sienna_cichlid_sdma.bin");
MODULE_FIRMWARE("amdgpu/navy_flounder_sdma.bin");
MODULE_FIRMWARE("amdgpu/dimgrey_cavefish_sdma.bin");

MODULE_FIRMWARE("amdgpu/vangogh_sdma.bin");

#घोषणा SDMA1_REG_OFFSET 0x600
#घोषणा SDMA3_REG_OFFSET 0x400
#घोषणा SDMA0_HYP_DEC_REG_START 0x5880
#घोषणा SDMA0_HYP_DEC_REG_END 0x5893
#घोषणा SDMA1_HYP_DEC_REG_OFFSET 0x20

अटल व्योम sdma_v5_2_set_ring_funcs(काष्ठा amdgpu_device *adev);
अटल व्योम sdma_v5_2_set_buffer_funcs(काष्ठा amdgpu_device *adev);
अटल व्योम sdma_v5_2_set_vm_pte_funcs(काष्ठा amdgpu_device *adev);
अटल व्योम sdma_v5_2_set_irq_funcs(काष्ठा amdgpu_device *adev);

अटल u32 sdma_v5_2_get_reg_offset(काष्ठा amdgpu_device *adev, u32 instance, u32 पूर्णांकernal_offset)
अणु
	u32 base;

	अगर (पूर्णांकernal_offset >= SDMA0_HYP_DEC_REG_START &&
	    पूर्णांकernal_offset <= SDMA0_HYP_DEC_REG_END) अणु
		base = adev->reg_offset[GC_HWIP][0][1];
		अगर (instance != 0)
			पूर्णांकernal_offset += SDMA1_HYP_DEC_REG_OFFSET * instance;
	पूर्ण अन्यथा अणु
		अगर (instance < 2) अणु
			base = adev->reg_offset[GC_HWIP][0][0];
			अगर (instance == 1)
				पूर्णांकernal_offset += SDMA1_REG_OFFSET;
		पूर्ण अन्यथा अणु
			base = adev->reg_offset[GC_HWIP][0][2];
			अगर (instance == 3)
				पूर्णांकernal_offset += SDMA3_REG_OFFSET;
		पूर्ण
	पूर्ण

	वापस base + पूर्णांकernal_offset;
पूर्ण

अटल व्योम sdma_v5_2_init_golden_रेजिस्टरs(काष्ठा amdgpu_device *adev)
अणु
	चयन (adev->asic_type) अणु
	हाल CHIP_SIENNA_CICHLID:
	हाल CHIP_NAVY_FLOUNDER:
	हाल CHIP_VANGOGH:
	हाल CHIP_DIMGREY_CAVEFISH:
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक sdma_v5_2_init_inst_ctx(काष्ठा amdgpu_sdma_instance *sdma_inst)
अणु
	पूर्णांक err = 0;
	स्थिर काष्ठा sdma_firmware_header_v1_0 *hdr;

	err = amdgpu_ucode_validate(sdma_inst->fw);
	अगर (err)
		वापस err;

	hdr = (स्थिर काष्ठा sdma_firmware_header_v1_0 *)sdma_inst->fw->data;
	sdma_inst->fw_version = le32_to_cpu(hdr->header.ucode_version);
	sdma_inst->feature_version = le32_to_cpu(hdr->ucode_feature_version);

	अगर (sdma_inst->feature_version >= 20)
		sdma_inst->burst_nop = true;

	वापस 0;
पूर्ण

अटल व्योम sdma_v5_2_destroy_inst_ctx(काष्ठा amdgpu_device *adev)
अणु
	release_firmware(adev->sdma.instance[0].fw);

	स_रखो((व्योम *)adev->sdma.instance, 0,
	       माप(काष्ठा amdgpu_sdma_instance) * AMDGPU_MAX_SDMA_INSTANCES);
पूर्ण

/**
 * sdma_v5_2_init_microcode - load ucode images from disk
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Use the firmware पूर्णांकerface to load the ucode images पूर्णांकo
 * the driver (not loaded पूर्णांकo hw).
 * Returns 0 on success, error on failure.
 */

// emulation only, won't work on real chip
// navi10 real chip need to use PSP to load firmware
अटल पूर्णांक sdma_v5_2_init_microcode(काष्ठा amdgpu_device *adev)
अणु
	स्थिर अक्षर *chip_name;
	अक्षर fw_name[40];
	पूर्णांक err = 0, i;
	काष्ठा amdgpu_firmware_info *info = शून्य;
	स्थिर काष्ठा common_firmware_header *header = शून्य;

	अगर (amdgpu_sriov_vf(adev) && (adev->asic_type == CHIP_SIENNA_CICHLID))
		वापस 0;

	DRM_DEBUG("\n");

	चयन (adev->asic_type) अणु
	हाल CHIP_SIENNA_CICHLID:
		chip_name = "sienna_cichlid";
		अवरोध;
	हाल CHIP_NAVY_FLOUNDER:
		chip_name = "navy_flounder";
		अवरोध;
	हाल CHIP_VANGOGH:
		chip_name = "vangogh";
		अवरोध;
	हाल CHIP_DIMGREY_CAVEFISH:
		chip_name = "dimgrey_cavefish";
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	snम_लिखो(fw_name, माप(fw_name), "amdgpu/%s_sdma.bin", chip_name);

	err = request_firmware(&adev->sdma.instance[0].fw, fw_name, adev->dev);
	अगर (err)
		जाओ out;

	err = sdma_v5_2_init_inst_ctx(&adev->sdma.instance[0]);
	अगर (err)
		जाओ out;

	क्रम (i = 1; i < adev->sdma.num_instances; i++)
		स_नकल((व्योम *)&adev->sdma.instance[i],
		       (व्योम *)&adev->sdma.instance[0],
		       माप(काष्ठा amdgpu_sdma_instance));

	DRM_DEBUG("psp_load == '%s'\n",
		  adev->firmware.load_type == AMDGPU_FW_LOAD_PSP ? "true" : "false");

	अगर (adev->firmware.load_type == AMDGPU_FW_LOAD_PSP) अणु
		क्रम (i = 0; i < adev->sdma.num_instances; i++) अणु
			info = &adev->firmware.ucode[AMDGPU_UCODE_ID_SDMA0 + i];
			info->ucode_id = AMDGPU_UCODE_ID_SDMA0 + i;
			info->fw = adev->sdma.instance[i].fw;
			header = (स्थिर काष्ठा common_firmware_header *)info->fw->data;
			adev->firmware.fw_size +=
				ALIGN(le32_to_cpu(header->ucode_size_bytes), PAGE_SIZE);
		पूर्ण
	पूर्ण

out:
	अगर (err) अणु
		DRM_ERROR("sdma_v5_2: Failed to load firmware \"%s\"\n", fw_name);
		sdma_v5_2_destroy_inst_ctx(adev);
	पूर्ण
	वापस err;
पूर्ण

अटल अचिन्हित sdma_v5_2_ring_init_cond_exec(काष्ठा amdgpu_ring *ring)
अणु
	अचिन्हित ret;

	amdgpu_ring_ग_लिखो(ring, SDMA_PKT_HEADER_OP(SDMA_OP_COND_EXE));
	amdgpu_ring_ग_लिखो(ring, lower_32_bits(ring->cond_exe_gpu_addr));
	amdgpu_ring_ग_लिखो(ring, upper_32_bits(ring->cond_exe_gpu_addr));
	amdgpu_ring_ग_लिखो(ring, 1);
	ret = ring->wptr & ring->buf_mask;/* this is the offset we need patch later */
	amdgpu_ring_ग_लिखो(ring, 0x55aa55aa);/* insert dummy here and patch it later */

	वापस ret;
पूर्ण

अटल व्योम sdma_v5_2_ring_patch_cond_exec(काष्ठा amdgpu_ring *ring,
					   अचिन्हित offset)
अणु
	अचिन्हित cur;

	BUG_ON(offset > ring->buf_mask);
	BUG_ON(ring->ring[offset] != 0x55aa55aa);

	cur = (ring->wptr - 1) & ring->buf_mask;
	अगर (cur > offset)
		ring->ring[offset] = cur - offset;
	अन्यथा
		ring->ring[offset] = (ring->buf_mask + 1) - offset + cur;
पूर्ण

/**
 * sdma_v5_2_ring_get_rptr - get the current पढ़ो poपूर्णांकer
 *
 * @ring: amdgpu ring poपूर्णांकer
 *
 * Get the current rptr from the hardware (NAVI10+).
 */
अटल uपूर्णांक64_t sdma_v5_2_ring_get_rptr(काष्ठा amdgpu_ring *ring)
अणु
	u64 *rptr;

	/* XXX check अगर swapping is necessary on BE */
	rptr = ((u64 *)&ring->adev->wb.wb[ring->rptr_offs]);

	DRM_DEBUG("rptr before shift == 0x%016llx\n", *rptr);
	वापस ((*rptr) >> 2);
पूर्ण

/**
 * sdma_v5_2_ring_get_wptr - get the current ग_लिखो poपूर्णांकer
 *
 * @ring: amdgpu ring poपूर्णांकer
 *
 * Get the current wptr from the hardware (NAVI10+).
 */
अटल uपूर्णांक64_t sdma_v5_2_ring_get_wptr(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;
	u64 wptr;

	अगर (ring->use_करोorbell) अणु
		/* XXX check अगर swapping is necessary on BE */
		wptr = READ_ONCE(*((u64 *)&adev->wb.wb[ring->wptr_offs]));
		DRM_DEBUG("wptr/doorbell before shift == 0x%016llx\n", wptr);
	पूर्ण अन्यथा अणु
		wptr = RREG32(sdma_v5_2_get_reg_offset(adev, ring->me, mmSDMA0_GFX_RB_WPTR_HI));
		wptr = wptr << 32;
		wptr |= RREG32(sdma_v5_2_get_reg_offset(adev, ring->me, mmSDMA0_GFX_RB_WPTR));
		DRM_DEBUG("wptr before shift [%i] wptr == 0x%016llx\n", ring->me, wptr);
	पूर्ण

	वापस wptr >> 2;
पूर्ण

/**
 * sdma_v5_2_ring_set_wptr - commit the ग_लिखो poपूर्णांकer
 *
 * @ring: amdgpu ring poपूर्णांकer
 *
 * Write the wptr back to the hardware (NAVI10+).
 */
अटल व्योम sdma_v5_2_ring_set_wptr(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	DRM_DEBUG("Setting write pointer\n");
	अगर (ring->use_करोorbell) अणु
		DRM_DEBUG("Using doorbell -- "
				"wptr_offs == 0x%08x "
				"lower_32_bits(ring->wptr) << 2 == 0x%08x "
				"upper_32_bits(ring->wptr) << 2 == 0x%08x\n",
				ring->wptr_offs,
				lower_32_bits(ring->wptr << 2),
				upper_32_bits(ring->wptr << 2));
		/* XXX check अगर swapping is necessary on BE */
		adev->wb.wb[ring->wptr_offs] = lower_32_bits(ring->wptr << 2);
		adev->wb.wb[ring->wptr_offs + 1] = upper_32_bits(ring->wptr << 2);
		DRM_DEBUG("calling WDOORBELL64(0x%08x, 0x%016llx)\n",
				ring->करोorbell_index, ring->wptr << 2);
		WDOORBELL64(ring->करोorbell_index, ring->wptr << 2);
	पूर्ण अन्यथा अणु
		DRM_DEBUG("Not using doorbell -- "
				"mmSDMA%i_GFX_RB_WPTR == 0x%08x "
				"mmSDMA%i_GFX_RB_WPTR_HI == 0x%08x\n",
				ring->me,
				lower_32_bits(ring->wptr << 2),
				ring->me,
				upper_32_bits(ring->wptr << 2));
		WREG32(sdma_v5_2_get_reg_offset(adev, ring->me, mmSDMA0_GFX_RB_WPTR),
			lower_32_bits(ring->wptr << 2));
		WREG32(sdma_v5_2_get_reg_offset(adev, ring->me, mmSDMA0_GFX_RB_WPTR_HI),
			upper_32_bits(ring->wptr << 2));
	पूर्ण
पूर्ण

अटल व्योम sdma_v5_2_ring_insert_nop(काष्ठा amdgpu_ring *ring, uपूर्णांक32_t count)
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
 * sdma_v5_2_ring_emit_ib - Schedule an IB on the DMA engine
 *
 * @ring: amdgpu ring poपूर्णांकer
 * @job: job to retrieve vmid from
 * @ib: IB object to schedule
 * @flags: unused
 *
 * Schedule an IB in the DMA ring.
 */
अटल व्योम sdma_v5_2_ring_emit_ib(काष्ठा amdgpu_ring *ring,
				   काष्ठा amdgpu_job *job,
				   काष्ठा amdgpu_ib *ib,
				   uपूर्णांक32_t flags)
अणु
	अचिन्हित vmid = AMDGPU_JOB_GET_VMID(job);
	uपूर्णांक64_t csa_mc_addr = amdgpu_sdma_get_csa_mc_addr(ring, vmid);

	/* An IB packet must end on a 8 DW boundary--the next dword
	 * must be on a 8-dword boundary. Our IB packet below is 6
	 * dwords दीर्घ, thus add x number of NOPs, such that, in
	 * modular arithmetic,
	 * wptr + 6 + x = 8k, k >= 0, which in C is,
	 * (wptr + 6 + x) % 8 = 0.
	 * The expression below, is a solution of x.
	 */
	sdma_v5_2_ring_insert_nop(ring, (2 - lower_32_bits(ring->wptr)) & 7);

	amdgpu_ring_ग_लिखो(ring, SDMA_PKT_HEADER_OP(SDMA_OP_INसूचीECT) |
			  SDMA_PKT_INसूचीECT_HEADER_VMID(vmid & 0xf));
	/* base must be 32 byte aligned */
	amdgpu_ring_ग_लिखो(ring, lower_32_bits(ib->gpu_addr) & 0xffffffe0);
	amdgpu_ring_ग_लिखो(ring, upper_32_bits(ib->gpu_addr));
	amdgpu_ring_ग_लिखो(ring, ib->length_dw);
	amdgpu_ring_ग_लिखो(ring, lower_32_bits(csa_mc_addr));
	amdgpu_ring_ग_लिखो(ring, upper_32_bits(csa_mc_addr));
पूर्ण

/**
 * sdma_v5_2_ring_emit_mem_sync - flush the IB by graphics cache rinse
 *
 * @ring: amdgpu ring poपूर्णांकer
 * @job: job to retrieve vmid from
 * @ib: IB object to schedule
 *
 * flush the IB by graphics cache rinse.
 */
अटल व्योम sdma_v5_2_ring_emit_mem_sync(काष्ठा amdgpu_ring *ring)
अणु
    uपूर्णांक32_t gcr_cntl =
		    SDMA_GCR_GL2_INV | SDMA_GCR_GL2_WB | SDMA_GCR_GLM_INV |
			SDMA_GCR_GL1_INV | SDMA_GCR_GLV_INV | SDMA_GCR_GLK_INV |
			SDMA_GCR_GLI_INV(1);

	/* flush entire cache L0/L1/L2, this can be optimized by perक्रमmance requirement */
	amdgpu_ring_ग_लिखो(ring, SDMA_PKT_HEADER_OP(SDMA_OP_GCR_REQ));
	amdgpu_ring_ग_लिखो(ring, SDMA_PKT_GCR_REQ_PAYLOAD1_BASE_VA_31_7(0));
	amdgpu_ring_ग_लिखो(ring, SDMA_PKT_GCR_REQ_PAYLOAD2_GCR_CONTROL_15_0(gcr_cntl) |
			SDMA_PKT_GCR_REQ_PAYLOAD2_BASE_VA_47_32(0));
	amdgpu_ring_ग_लिखो(ring, SDMA_PKT_GCR_REQ_PAYLOAD3_LIMIT_VA_31_7(0) |
			SDMA_PKT_GCR_REQ_PAYLOAD3_GCR_CONTROL_18_16(gcr_cntl >> 16));
	amdgpu_ring_ग_लिखो(ring, SDMA_PKT_GCR_REQ_PAYLOAD4_LIMIT_VA_47_32(0) |
			SDMA_PKT_GCR_REQ_PAYLOAD4_VMID(0));
पूर्ण

/**
 * sdma_v5_2_ring_emit_hdp_flush - emit an hdp flush on the DMA ring
 *
 * @ring: amdgpu ring poपूर्णांकer
 *
 * Emit an hdp flush packet on the requested DMA ring.
 */
अटल व्योम sdma_v5_2_ring_emit_hdp_flush(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;
	u32 ref_and_mask = 0;
	स्थिर काष्ठा nbio_hdp_flush_reg *nbio_hf_reg = adev->nbपन.सdp_flush_reg;

	ref_and_mask = nbio_hf_reg->ref_and_mask_sdma0 << ring->me;

	amdgpu_ring_ग_लिखो(ring, SDMA_PKT_HEADER_OP(SDMA_OP_POLL_REGMEM) |
			  SDMA_PKT_POLL_REGMEM_HEADER_HDP_FLUSH(1) |
			  SDMA_PKT_POLL_REGMEM_HEADER_FUNC(3)); /* == */
	amdgpu_ring_ग_लिखो(ring, (adev->nbio.funcs->get_hdp_flush_करोne_offset(adev)) << 2);
	amdgpu_ring_ग_लिखो(ring, (adev->nbio.funcs->get_hdp_flush_req_offset(adev)) << 2);
	amdgpu_ring_ग_लिखो(ring, ref_and_mask); /* reference */
	amdgpu_ring_ग_लिखो(ring, ref_and_mask); /* mask */
	amdgpu_ring_ग_लिखो(ring, SDMA_PKT_POLL_REGMEM_DW5_RETRY_COUNT(0xfff) |
			  SDMA_PKT_POLL_REGMEM_DW5_INTERVAL(10)); /* retry count, poll पूर्णांकerval */
पूर्ण

/**
 * sdma_v5_2_ring_emit_fence - emit a fence on the DMA ring
 *
 * @ring: amdgpu ring poपूर्णांकer
 * @addr: address
 * @seq: sequence number
 * @flags: fence related flags
 *
 * Add a DMA fence packet to the ring to ग_लिखो
 * the fence seq number and DMA trap packet to generate
 * an पूर्णांकerrupt अगर needed.
 */
अटल व्योम sdma_v5_2_ring_emit_fence(काष्ठा amdgpu_ring *ring, u64 addr, u64 seq,
				      अचिन्हित flags)
अणु
	bool ग_लिखो64bit = flags & AMDGPU_FENCE_FLAG_64BIT;
	/* ग_लिखो the fence */
	amdgpu_ring_ग_लिखो(ring, SDMA_PKT_HEADER_OP(SDMA_OP_FENCE) |
			  SDMA_PKT_FENCE_HEADER_MTYPE(0x3)); /* Ucached(UC) */
	/* zero in first two bits */
	BUG_ON(addr & 0x3);
	amdgpu_ring_ग_लिखो(ring, lower_32_bits(addr));
	amdgpu_ring_ग_लिखो(ring, upper_32_bits(addr));
	amdgpu_ring_ग_लिखो(ring, lower_32_bits(seq));

	/* optionally ग_लिखो high bits as well */
	अगर (ग_लिखो64bit) अणु
		addr += 4;
		amdgpu_ring_ग_लिखो(ring, SDMA_PKT_HEADER_OP(SDMA_OP_FENCE) |
				  SDMA_PKT_FENCE_HEADER_MTYPE(0x3));
		/* zero in first two bits */
		BUG_ON(addr & 0x3);
		amdgpu_ring_ग_लिखो(ring, lower_32_bits(addr));
		amdgpu_ring_ग_लिखो(ring, upper_32_bits(addr));
		amdgpu_ring_ग_लिखो(ring, upper_32_bits(seq));
	पूर्ण

	अगर (flags & AMDGPU_FENCE_FLAG_INT) अणु
		/* generate an पूर्णांकerrupt */
		amdgpu_ring_ग_लिखो(ring, SDMA_PKT_HEADER_OP(SDMA_OP_TRAP));
		amdgpu_ring_ग_लिखो(ring, SDMA_PKT_TRAP_INT_CONTEXT_INT_CONTEXT(0));
	पूर्ण
पूर्ण


/**
 * sdma_v5_2_gfx_stop - stop the gfx async dma engines
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Stop the gfx async dma ring buffers.
 */
अटल व्योम sdma_v5_2_gfx_stop(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_ring *sdma0 = &adev->sdma.instance[0].ring;
	काष्ठा amdgpu_ring *sdma1 = &adev->sdma.instance[1].ring;
	काष्ठा amdgpu_ring *sdma2 = &adev->sdma.instance[2].ring;
	काष्ठा amdgpu_ring *sdma3 = &adev->sdma.instance[3].ring;
	u32 rb_cntl, ib_cntl;
	पूर्णांक i;

	अगर ((adev->mman.buffer_funcs_ring == sdma0) ||
	    (adev->mman.buffer_funcs_ring == sdma1) ||
	    (adev->mman.buffer_funcs_ring == sdma2) ||
	    (adev->mman.buffer_funcs_ring == sdma3))
		amdgpu_tपंचांग_set_buffer_funcs_status(adev, false);

	क्रम (i = 0; i < adev->sdma.num_instances; i++) अणु
		rb_cntl = RREG32(sdma_v5_2_get_reg_offset(adev, i, mmSDMA0_GFX_RB_CNTL));
		rb_cntl = REG_SET_FIELD(rb_cntl, SDMA0_GFX_RB_CNTL, RB_ENABLE, 0);
		WREG32(sdma_v5_2_get_reg_offset(adev, i, mmSDMA0_GFX_RB_CNTL), rb_cntl);
		ib_cntl = RREG32(sdma_v5_2_get_reg_offset(adev, i, mmSDMA0_GFX_IB_CNTL));
		ib_cntl = REG_SET_FIELD(ib_cntl, SDMA0_GFX_IB_CNTL, IB_ENABLE, 0);
		WREG32(sdma_v5_2_get_reg_offset(adev, i, mmSDMA0_GFX_IB_CNTL), ib_cntl);
	पूर्ण
पूर्ण

/**
 * sdma_v5_2_rlc_stop - stop the compute async dma engines
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Stop the compute async dma queues.
 */
अटल व्योम sdma_v5_2_rlc_stop(काष्ठा amdgpu_device *adev)
अणु
	/* XXX toकरो */
पूर्ण

/**
 * sdma_v_0_ctx_चयन_enable - stop the async dma engines context चयन
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @enable: enable/disable the DMA MEs context चयन.
 *
 * Halt or unhalt the async dma engines context चयन.
 */
अटल व्योम sdma_v5_2_ctx_चयन_enable(काष्ठा amdgpu_device *adev, bool enable)
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
		f32_cntl = RREG32(sdma_v5_2_get_reg_offset(adev, i, mmSDMA0_CNTL));
		f32_cntl = REG_SET_FIELD(f32_cntl, SDMA0_CNTL,
				AUTO_CTXSW_ENABLE, enable ? 1 : 0);
		अगर (enable && amdgpu_sdma_phase_quantum) अणु
			WREG32(sdma_v5_2_get_reg_offset(adev, i, mmSDMA0_PHASE0_QUANTUM),
			       phase_quantum);
			WREG32(sdma_v5_2_get_reg_offset(adev, i, mmSDMA0_PHASE1_QUANTUM),
			       phase_quantum);
			WREG32(sdma_v5_2_get_reg_offset(adev, i, mmSDMA0_PHASE2_QUANTUM),
			       phase_quantum);
		पूर्ण
		WREG32(sdma_v5_2_get_reg_offset(adev, i, mmSDMA0_CNTL), f32_cntl);
	पूर्ण

पूर्ण

/**
 * sdma_v5_2_enable - stop the async dma engines
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @enable: enable/disable the DMA MEs.
 *
 * Halt or unhalt the async dma engines.
 */
अटल व्योम sdma_v5_2_enable(काष्ठा amdgpu_device *adev, bool enable)
अणु
	u32 f32_cntl;
	पूर्णांक i;

	अगर (!enable) अणु
		sdma_v5_2_gfx_stop(adev);
		sdma_v5_2_rlc_stop(adev);
	पूर्ण

	क्रम (i = 0; i < adev->sdma.num_instances; i++) अणु
		f32_cntl = RREG32(sdma_v5_2_get_reg_offset(adev, i, mmSDMA0_F32_CNTL));
		f32_cntl = REG_SET_FIELD(f32_cntl, SDMA0_F32_CNTL, HALT, enable ? 0 : 1);
		WREG32(sdma_v5_2_get_reg_offset(adev, i, mmSDMA0_F32_CNTL), f32_cntl);
	पूर्ण
पूर्ण

/**
 * sdma_v5_2_gfx_resume - setup and start the async dma engines
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Set up the gfx DMA ring buffers and enable them.
 * Returns 0 क्रम success, error क्रम failure.
 */
अटल पूर्णांक sdma_v5_2_gfx_resume(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_ring *ring;
	u32 rb_cntl, ib_cntl;
	u32 rb_bufsz;
	u32 wb_offset;
	u32 करोorbell;
	u32 करोorbell_offset;
	u32 temp;
	u32 wptr_poll_cntl;
	u64 wptr_gpu_addr;
	पूर्णांक i, r;

	क्रम (i = 0; i < adev->sdma.num_instances; i++) अणु
		ring = &adev->sdma.instance[i].ring;
		wb_offset = (ring->rptr_offs * 4);

		WREG32(sdma_v5_2_get_reg_offset(adev, i, mmSDMA0_SEM_WAIT_FAIL_TIMER_CNTL), 0);

		/* Set ring buffer size in dwords */
		rb_bufsz = order_base_2(ring->ring_size / 4);
		rb_cntl = RREG32(sdma_v5_2_get_reg_offset(adev, i, mmSDMA0_GFX_RB_CNTL));
		rb_cntl = REG_SET_FIELD(rb_cntl, SDMA0_GFX_RB_CNTL, RB_SIZE, rb_bufsz);
#अगर_घोषित __BIG_ENDIAN
		rb_cntl = REG_SET_FIELD(rb_cntl, SDMA0_GFX_RB_CNTL, RB_SWAP_ENABLE, 1);
		rb_cntl = REG_SET_FIELD(rb_cntl, SDMA0_GFX_RB_CNTL,
					RPTR_WRITEBACK_SWAP_ENABLE, 1);
#पूर्ण_अगर
		WREG32(sdma_v5_2_get_reg_offset(adev, i, mmSDMA0_GFX_RB_CNTL), rb_cntl);

		/* Initialize the ring buffer's पढ़ो and ग_लिखो poपूर्णांकers */
		WREG32(sdma_v5_2_get_reg_offset(adev, i, mmSDMA0_GFX_RB_RPTR), 0);
		WREG32(sdma_v5_2_get_reg_offset(adev, i, mmSDMA0_GFX_RB_RPTR_HI), 0);
		WREG32(sdma_v5_2_get_reg_offset(adev, i, mmSDMA0_GFX_RB_WPTR), 0);
		WREG32(sdma_v5_2_get_reg_offset(adev, i, mmSDMA0_GFX_RB_WPTR_HI), 0);

		/* setup the wptr shaकरोw polling */
		wptr_gpu_addr = adev->wb.gpu_addr + (ring->wptr_offs * 4);
		WREG32(sdma_v5_2_get_reg_offset(adev, i, mmSDMA0_GFX_RB_WPTR_POLL_ADDR_LO),
		       lower_32_bits(wptr_gpu_addr));
		WREG32(sdma_v5_2_get_reg_offset(adev, i, mmSDMA0_GFX_RB_WPTR_POLL_ADDR_HI),
		       upper_32_bits(wptr_gpu_addr));
		wptr_poll_cntl = RREG32(sdma_v5_2_get_reg_offset(adev, i,
							 mmSDMA0_GFX_RB_WPTR_POLL_CNTL));
		wptr_poll_cntl = REG_SET_FIELD(wptr_poll_cntl,
					       SDMA0_GFX_RB_WPTR_POLL_CNTL,
					       F32_POLL_ENABLE, 1);
		WREG32(sdma_v5_2_get_reg_offset(adev, i, mmSDMA0_GFX_RB_WPTR_POLL_CNTL),
		       wptr_poll_cntl);

		/* set the wb address whether it's enabled or not */
		WREG32(sdma_v5_2_get_reg_offset(adev, i, mmSDMA0_GFX_RB_RPTR_ADDR_HI),
		       upper_32_bits(adev->wb.gpu_addr + wb_offset) & 0xFFFFFFFF);
		WREG32(sdma_v5_2_get_reg_offset(adev, i, mmSDMA0_GFX_RB_RPTR_ADDR_LO),
		       lower_32_bits(adev->wb.gpu_addr + wb_offset) & 0xFFFFFFFC);

		rb_cntl = REG_SET_FIELD(rb_cntl, SDMA0_GFX_RB_CNTL, RPTR_WRITEBACK_ENABLE, 1);

		WREG32(sdma_v5_2_get_reg_offset(adev, i, mmSDMA0_GFX_RB_BASE), ring->gpu_addr >> 8);
		WREG32(sdma_v5_2_get_reg_offset(adev, i, mmSDMA0_GFX_RB_BASE_HI), ring->gpu_addr >> 40);

		ring->wptr = 0;

		/* beक्रमe programing wptr to a less value, need set minor_ptr_update first */
		WREG32(sdma_v5_2_get_reg_offset(adev, i, mmSDMA0_GFX_MINOR_PTR_UPDATE), 1);

		अगर (!amdgpu_sriov_vf(adev)) अणु /* only bare-metal use रेजिस्टर ग_लिखो क्रम wptr */
			WREG32(sdma_v5_2_get_reg_offset(adev, i, mmSDMA0_GFX_RB_WPTR), lower_32_bits(ring->wptr) << 2);
			WREG32(sdma_v5_2_get_reg_offset(adev, i, mmSDMA0_GFX_RB_WPTR_HI), upper_32_bits(ring->wptr) << 2);
		पूर्ण

		करोorbell = RREG32(sdma_v5_2_get_reg_offset(adev, i, mmSDMA0_GFX_DOORBELL));
		करोorbell_offset = RREG32(sdma_v5_2_get_reg_offset(adev, i, mmSDMA0_GFX_DOORBELL_OFFSET));

		अगर (ring->use_करोorbell) अणु
			करोorbell = REG_SET_FIELD(करोorbell, SDMA0_GFX_DOORBELL, ENABLE, 1);
			करोorbell_offset = REG_SET_FIELD(करोorbell_offset, SDMA0_GFX_DOORBELL_OFFSET,
					OFFSET, ring->करोorbell_index);
		पूर्ण अन्यथा अणु
			करोorbell = REG_SET_FIELD(करोorbell, SDMA0_GFX_DOORBELL, ENABLE, 0);
		पूर्ण
		WREG32(sdma_v5_2_get_reg_offset(adev, i, mmSDMA0_GFX_DOORBELL), करोorbell);
		WREG32(sdma_v5_2_get_reg_offset(adev, i, mmSDMA0_GFX_DOORBELL_OFFSET), करोorbell_offset);

		adev->nbio.funcs->sdma_करोorbell_range(adev, i, ring->use_करोorbell,
						      ring->करोorbell_index,
						      adev->करोorbell_index.sdma_करोorbell_range);

		अगर (amdgpu_sriov_vf(adev))
			sdma_v5_2_ring_set_wptr(ring);

		/* set minor_ptr_update to 0 after wptr programed */
		WREG32(sdma_v5_2_get_reg_offset(adev, i, mmSDMA0_GFX_MINOR_PTR_UPDATE), 0);

		/* set utc l1 enable flag always to 1 */
		temp = RREG32(sdma_v5_2_get_reg_offset(adev, i, mmSDMA0_CNTL));
		temp = REG_SET_FIELD(temp, SDMA0_CNTL, UTC_L1_ENABLE, 1);

		/* enable MCBP */
		temp = REG_SET_FIELD(temp, SDMA0_CNTL, MIDCMD_PREEMPT_ENABLE, 1);
		WREG32(sdma_v5_2_get_reg_offset(adev, i, mmSDMA0_CNTL), temp);

		/* Set up RESP_MODE to non-copy addresses */
		temp = RREG32(sdma_v5_2_get_reg_offset(adev, i, mmSDMA0_UTCL1_CNTL));
		temp = REG_SET_FIELD(temp, SDMA0_UTCL1_CNTL, RESP_MODE, 3);
		temp = REG_SET_FIELD(temp, SDMA0_UTCL1_CNTL, REDO_DELAY, 9);
		WREG32(sdma_v5_2_get_reg_offset(adev, i, mmSDMA0_UTCL1_CNTL), temp);

		/* program शेष cache पढ़ो and ग_लिखो policy */
		temp = RREG32(sdma_v5_2_get_reg_offset(adev, i, mmSDMA0_UTCL1_PAGE));
		/* clean पढ़ो policy and ग_लिखो policy bits */
		temp &= 0xFF0FFF;
		temp |= ((CACHE_READ_POLICY_L2__DEFAULT << 12) |
			 (CACHE_WRITE_POLICY_L2__DEFAULT << 14) |
			 SDMA0_UTCL1_PAGE__LLC_NOALLOC_MASK);
		WREG32(sdma_v5_2_get_reg_offset(adev, i, mmSDMA0_UTCL1_PAGE), temp);

		अगर (!amdgpu_sriov_vf(adev)) अणु
			/* unhalt engine */
			temp = RREG32(sdma_v5_2_get_reg_offset(adev, i, mmSDMA0_F32_CNTL));
			temp = REG_SET_FIELD(temp, SDMA0_F32_CNTL, HALT, 0);
			WREG32(sdma_v5_2_get_reg_offset(adev, i, mmSDMA0_F32_CNTL), temp);
		पूर्ण

		/* enable DMA RB */
		rb_cntl = REG_SET_FIELD(rb_cntl, SDMA0_GFX_RB_CNTL, RB_ENABLE, 1);
		WREG32(sdma_v5_2_get_reg_offset(adev, i, mmSDMA0_GFX_RB_CNTL), rb_cntl);

		ib_cntl = RREG32(sdma_v5_2_get_reg_offset(adev, i, mmSDMA0_GFX_IB_CNTL));
		ib_cntl = REG_SET_FIELD(ib_cntl, SDMA0_GFX_IB_CNTL, IB_ENABLE, 1);
#अगर_घोषित __BIG_ENDIAN
		ib_cntl = REG_SET_FIELD(ib_cntl, SDMA0_GFX_IB_CNTL, IB_SWAP_ENABLE, 1);
#पूर्ण_अगर
		/* enable DMA IBs */
		WREG32(sdma_v5_2_get_reg_offset(adev, i, mmSDMA0_GFX_IB_CNTL), ib_cntl);

		ring->sched.पढ़ोy = true;

		अगर (amdgpu_sriov_vf(adev)) अणु /* bare-metal sequence करोesn't need below to lines */
			sdma_v5_2_ctx_चयन_enable(adev, true);
			sdma_v5_2_enable(adev, true);
		पूर्ण

		r = amdgpu_ring_test_ring(ring);
		अगर (r) अणु
			ring->sched.पढ़ोy = false;
			वापस r;
		पूर्ण

		अगर (adev->mman.buffer_funcs_ring == ring)
			amdgpu_tपंचांग_set_buffer_funcs_status(adev, true);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * sdma_v5_2_rlc_resume - setup and start the async dma engines
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Set up the compute DMA queues and enable them.
 * Returns 0 क्रम success, error क्रम failure.
 */
अटल पूर्णांक sdma_v5_2_rlc_resume(काष्ठा amdgpu_device *adev)
अणु
	वापस 0;
पूर्ण

/**
 * sdma_v5_2_load_microcode - load the sDMA ME ucode
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Loads the sDMA0/1/2/3 ucode.
 * Returns 0 क्रम success, -EINVAL अगर the ucode is not available.
 */
अटल पूर्णांक sdma_v5_2_load_microcode(काष्ठा amdgpu_device *adev)
अणु
	स्थिर काष्ठा sdma_firmware_header_v1_0 *hdr;
	स्थिर __le32 *fw_data;
	u32 fw_size;
	पूर्णांक i, j;

	/* halt the MEs */
	sdma_v5_2_enable(adev, false);

	क्रम (i = 0; i < adev->sdma.num_instances; i++) अणु
		अगर (!adev->sdma.instance[i].fw)
			वापस -EINVAL;

		hdr = (स्थिर काष्ठा sdma_firmware_header_v1_0 *)adev->sdma.instance[i].fw->data;
		amdgpu_ucode_prपूर्णांक_sdma_hdr(&hdr->header);
		fw_size = le32_to_cpu(hdr->header.ucode_size_bytes) / 4;

		fw_data = (स्थिर __le32 *)
			(adev->sdma.instance[i].fw->data +
				le32_to_cpu(hdr->header.ucode_array_offset_bytes));

		WREG32(sdma_v5_2_get_reg_offset(adev, i, mmSDMA0_UCODE_ADDR), 0);

		क्रम (j = 0; j < fw_size; j++) अणु
			अगर (amdgpu_emu_mode == 1 && j % 500 == 0)
				msleep(1);
			WREG32(sdma_v5_2_get_reg_offset(adev, i, mmSDMA0_UCODE_DATA), le32_to_cpup(fw_data++));
		पूर्ण

		WREG32(sdma_v5_2_get_reg_offset(adev, i, mmSDMA0_UCODE_ADDR), adev->sdma.instance[i].fw_version);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sdma_v5_2_soft_reset(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	u32 grbm_soft_reset;
	u32 पंचांगp;
	पूर्णांक i;

	क्रम (i = 0; i < adev->sdma.num_instances; i++) अणु
		grbm_soft_reset = REG_SET_FIELD(0,
						GRBM_SOFT_RESET, SOFT_RESET_SDMA0,
						1);
		grbm_soft_reset <<= i;

		पंचांगp = RREG32_SOC15(GC, 0, mmGRBM_SOFT_RESET);
		पंचांगp |= grbm_soft_reset;
		DRM_DEBUG("GRBM_SOFT_RESET=0x%08X\n", पंचांगp);
		WREG32_SOC15(GC, 0, mmGRBM_SOFT_RESET, पंचांगp);
		पंचांगp = RREG32_SOC15(GC, 0, mmGRBM_SOFT_RESET);

		udelay(50);

		पंचांगp &= ~grbm_soft_reset;
		WREG32_SOC15(GC, 0, mmGRBM_SOFT_RESET, पंचांगp);
		पंचांगp = RREG32_SOC15(GC, 0, mmGRBM_SOFT_RESET);

		udelay(50);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * sdma_v5_2_start - setup and start the async dma engines
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Set up the DMA engines and enable them.
 * Returns 0 क्रम success, error क्रम failure.
 */
अटल पूर्णांक sdma_v5_2_start(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक r = 0;

	अगर (amdgpu_sriov_vf(adev)) अणु
		sdma_v5_2_ctx_चयन_enable(adev, false);
		sdma_v5_2_enable(adev, false);

		/* set RB रेजिस्टरs */
		r = sdma_v5_2_gfx_resume(adev);
		वापस r;
	पूर्ण

	अगर (adev->firmware.load_type == AMDGPU_FW_LOAD_सूचीECT) अणु
		r = sdma_v5_2_load_microcode(adev);
		अगर (r)
			वापस r;

		/* The value of mmSDMA_F32_CNTL is invalid the moment after loading fw */
		अगर (amdgpu_emu_mode == 1)
			msleep(1000);
	पूर्ण

	sdma_v5_2_soft_reset(adev);
	/* unhalt the MEs */
	sdma_v5_2_enable(adev, true);
	/* enable sdma ring preemption */
	sdma_v5_2_ctx_चयन_enable(adev, true);

	/* start the gfx rings and rlc compute queues */
	r = sdma_v5_2_gfx_resume(adev);
	अगर (r)
		वापस r;
	r = sdma_v5_2_rlc_resume(adev);

	वापस r;
पूर्ण

/**
 * sdma_v5_2_ring_test_ring - simple async dma engine test
 *
 * @ring: amdgpu_ring काष्ठाure holding ring inक्रमmation
 *
 * Test the DMA engine by writing using it to ग_लिखो an
 * value to memory.
 * Returns 0 क्रम success, error क्रम failure.
 */
अटल पूर्णांक sdma_v5_2_ring_test_ring(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;
	अचिन्हित i;
	अचिन्हित index;
	पूर्णांक r;
	u32 पंचांगp;
	u64 gpu_addr;

	r = amdgpu_device_wb_get(adev, &index);
	अगर (r) अणु
		dev_err(adev->dev, "(%d) failed to allocate wb slot\n", r);
		वापस r;
	पूर्ण

	gpu_addr = adev->wb.gpu_addr + (index * 4);
	पंचांगp = 0xCAFEDEAD;
	adev->wb.wb[index] = cpu_to_le32(पंचांगp);

	r = amdgpu_ring_alloc(ring, 5);
	अगर (r) अणु
		DRM_ERROR("amdgpu: dma failed to lock ring %d (%d).\n", ring->idx, r);
		amdgpu_device_wb_मुक्त(adev, index);
		वापस r;
	पूर्ण

	amdgpu_ring_ग_लिखो(ring, SDMA_PKT_HEADER_OP(SDMA_OP_WRITE) |
			  SDMA_PKT_HEADER_SUB_OP(SDMA_SUBOP_WRITE_LINEAR));
	amdgpu_ring_ग_लिखो(ring, lower_32_bits(gpu_addr));
	amdgpu_ring_ग_लिखो(ring, upper_32_bits(gpu_addr));
	amdgpu_ring_ग_लिखो(ring, SDMA_PKT_WRITE_UNTILED_DW_3_COUNT(0));
	amdgpu_ring_ग_लिखो(ring, 0xDEADBEEF);
	amdgpu_ring_commit(ring);

	क्रम (i = 0; i < adev->usec_समयout; i++) अणु
		पंचांगp = le32_to_cpu(adev->wb.wb[index]);
		अगर (पंचांगp == 0xDEADBEEF)
			अवरोध;
		अगर (amdgpu_emu_mode == 1)
			msleep(1);
		अन्यथा
			udelay(1);
	पूर्ण

	अगर (i >= adev->usec_समयout)
		r = -ETIMEDOUT;

	amdgpu_device_wb_मुक्त(adev, index);

	वापस r;
पूर्ण

/**
 * sdma_v5_2_ring_test_ib - test an IB on the DMA engine
 *
 * @ring: amdgpu_ring काष्ठाure holding ring inक्रमmation
 * @समयout: समयout value in jअगरfies, or MAX_SCHEDULE_TIMEOUT
 *
 * Test a simple IB in the DMA ring.
 * Returns 0 on success, error on failure.
 */
अटल पूर्णांक sdma_v5_2_ring_test_ib(काष्ठा amdgpu_ring *ring, दीर्घ समयout)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;
	काष्ठा amdgpu_ib ib;
	काष्ठा dma_fence *f = शून्य;
	अचिन्हित index;
	दीर्घ r;
	u32 पंचांगp = 0;
	u64 gpu_addr;

	r = amdgpu_device_wb_get(adev, &index);
	अगर (r) अणु
		dev_err(adev->dev, "(%ld) failed to allocate wb slot\n", r);
		वापस r;
	पूर्ण

	gpu_addr = adev->wb.gpu_addr + (index * 4);
	पंचांगp = 0xCAFEDEAD;
	adev->wb.wb[index] = cpu_to_le32(पंचांगp);
	स_रखो(&ib, 0, माप(ib));
	r = amdgpu_ib_get(adev, शून्य, 256, AMDGPU_IB_POOL_सूचीECT, &ib);
	अगर (r) अणु
		DRM_ERROR("amdgpu: failed to get ib (%ld).\n", r);
		जाओ err0;
	पूर्ण

	ib.ptr[0] = SDMA_PKT_HEADER_OP(SDMA_OP_WRITE) |
		SDMA_PKT_HEADER_SUB_OP(SDMA_SUBOP_WRITE_LINEAR);
	ib.ptr[1] = lower_32_bits(gpu_addr);
	ib.ptr[2] = upper_32_bits(gpu_addr);
	ib.ptr[3] = SDMA_PKT_WRITE_UNTILED_DW_3_COUNT(0);
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
		DRM_ERROR("amdgpu: IB test timed out\n");
		r = -ETIMEDOUT;
		जाओ err1;
	पूर्ण अन्यथा अगर (r < 0) अणु
		DRM_ERROR("amdgpu: fence wait failed (%ld).\n", r);
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
 * sdma_v5_2_vm_copy_pte - update PTEs by copying them from the GART
 *
 * @ib: indirect buffer to fill with commands
 * @pe: addr of the page entry
 * @src: src addr to copy from
 * @count: number of page entries to update
 *
 * Update PTEs by copying them from the GART using sDMA.
 */
अटल व्योम sdma_v5_2_vm_copy_pte(काष्ठा amdgpu_ib *ib,
				  uपूर्णांक64_t pe, uपूर्णांक64_t src,
				  अचिन्हित count)
अणु
	अचिन्हित bytes = count * 8;

	ib->ptr[ib->length_dw++] = SDMA_PKT_HEADER_OP(SDMA_OP_COPY) |
		SDMA_PKT_HEADER_SUB_OP(SDMA_SUBOP_COPY_LINEAR);
	ib->ptr[ib->length_dw++] = bytes - 1;
	ib->ptr[ib->length_dw++] = 0; /* src/dst endian swap */
	ib->ptr[ib->length_dw++] = lower_32_bits(src);
	ib->ptr[ib->length_dw++] = upper_32_bits(src);
	ib->ptr[ib->length_dw++] = lower_32_bits(pe);
	ib->ptr[ib->length_dw++] = upper_32_bits(pe);

पूर्ण

/**
 * sdma_v5_2_vm_ग_लिखो_pte - update PTEs by writing them manually
 *
 * @ib: indirect buffer to fill with commands
 * @pe: addr of the page entry
 * @value: dst addr to ग_लिखो पूर्णांकo pe
 * @count: number of page entries to update
 * @incr: increase next addr by incr bytes
 *
 * Update PTEs by writing them manually using sDMA.
 */
अटल व्योम sdma_v5_2_vm_ग_लिखो_pte(काष्ठा amdgpu_ib *ib, uपूर्णांक64_t pe,
				   uपूर्णांक64_t value, अचिन्हित count,
				   uपूर्णांक32_t incr)
अणु
	अचिन्हित ndw = count * 2;

	ib->ptr[ib->length_dw++] = SDMA_PKT_HEADER_OP(SDMA_OP_WRITE) |
		SDMA_PKT_HEADER_SUB_OP(SDMA_SUBOP_WRITE_LINEAR);
	ib->ptr[ib->length_dw++] = lower_32_bits(pe);
	ib->ptr[ib->length_dw++] = upper_32_bits(pe);
	ib->ptr[ib->length_dw++] = ndw - 1;
	क्रम (; ndw > 0; ndw -= 2) अणु
		ib->ptr[ib->length_dw++] = lower_32_bits(value);
		ib->ptr[ib->length_dw++] = upper_32_bits(value);
		value += incr;
	पूर्ण
पूर्ण

/**
 * sdma_v5_2_vm_set_pte_pde - update the page tables using sDMA
 *
 * @ib: indirect buffer to fill with commands
 * @pe: addr of the page entry
 * @addr: dst addr to ग_लिखो पूर्णांकo pe
 * @count: number of page entries to update
 * @incr: increase next addr by incr bytes
 * @flags: access flags
 *
 * Update the page tables using sDMA.
 */
अटल व्योम sdma_v5_2_vm_set_pte_pde(काष्ठा amdgpu_ib *ib,
				     uपूर्णांक64_t pe,
				     uपूर्णांक64_t addr, अचिन्हित count,
				     uपूर्णांक32_t incr, uपूर्णांक64_t flags)
अणु
	/* क्रम physically contiguous pages (vram) */
	ib->ptr[ib->length_dw++] = SDMA_PKT_HEADER_OP(SDMA_OP_PTEPDE);
	ib->ptr[ib->length_dw++] = lower_32_bits(pe); /* dst addr */
	ib->ptr[ib->length_dw++] = upper_32_bits(pe);
	ib->ptr[ib->length_dw++] = lower_32_bits(flags); /* mask */
	ib->ptr[ib->length_dw++] = upper_32_bits(flags);
	ib->ptr[ib->length_dw++] = lower_32_bits(addr); /* value */
	ib->ptr[ib->length_dw++] = upper_32_bits(addr);
	ib->ptr[ib->length_dw++] = incr; /* increment size */
	ib->ptr[ib->length_dw++] = 0;
	ib->ptr[ib->length_dw++] = count - 1; /* number of entries */
पूर्ण

/**
 * sdma_v5_2_ring_pad_ib - pad the IB
 *
 * @ib: indirect buffer to fill with padding
 * @ring: amdgpu_ring काष्ठाure holding ring inक्रमmation
 *
 * Pad the IB with NOPs to a boundary multiple of 8.
 */
अटल व्योम sdma_v5_2_ring_pad_ib(काष्ठा amdgpu_ring *ring, काष्ठा amdgpu_ib *ib)
अणु
	काष्ठा amdgpu_sdma_instance *sdma = amdgpu_sdma_get_instance_from_ring(ring);
	u32 pad_count;
	पूर्णांक i;

	pad_count = (-ib->length_dw) & 0x7;
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
 * sdma_v5_2_ring_emit_pipeline_sync - sync the pipeline
 *
 * @ring: amdgpu_ring poपूर्णांकer
 *
 * Make sure all previous operations are completed (CIK).
 */
अटल व्योम sdma_v5_2_ring_emit_pipeline_sync(काष्ठा amdgpu_ring *ring)
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
 * sdma_v5_2_ring_emit_vm_flush - vm flush using sDMA
 *
 * @ring: amdgpu_ring poपूर्णांकer
 * @vmid: vmid number to use
 * @pd_addr: address
 *
 * Update the page table base and flush the VM TLB
 * using sDMA.
 */
अटल व्योम sdma_v5_2_ring_emit_vm_flush(काष्ठा amdgpu_ring *ring,
					 अचिन्हित vmid, uपूर्णांक64_t pd_addr)
अणु
	amdgpu_gmc_emit_flush_gpu_tlb(ring, vmid, pd_addr);
पूर्ण

अटल व्योम sdma_v5_2_ring_emit_wreg(काष्ठा amdgpu_ring *ring,
				     uपूर्णांक32_t reg, uपूर्णांक32_t val)
अणु
	amdgpu_ring_ग_लिखो(ring, SDMA_PKT_HEADER_OP(SDMA_OP_SRBM_WRITE) |
			  SDMA_PKT_SRBM_WRITE_HEADER_BYTE_EN(0xf));
	amdgpu_ring_ग_लिखो(ring, reg);
	amdgpu_ring_ग_लिखो(ring, val);
पूर्ण

अटल व्योम sdma_v5_2_ring_emit_reg_रुको(काष्ठा amdgpu_ring *ring, uपूर्णांक32_t reg,
					 uपूर्णांक32_t val, uपूर्णांक32_t mask)
अणु
	amdgpu_ring_ग_लिखो(ring, SDMA_PKT_HEADER_OP(SDMA_OP_POLL_REGMEM) |
			  SDMA_PKT_POLL_REGMEM_HEADER_HDP_FLUSH(0) |
			  SDMA_PKT_POLL_REGMEM_HEADER_FUNC(3)); /* equal */
	amdgpu_ring_ग_लिखो(ring, reg << 2);
	amdgpu_ring_ग_लिखो(ring, 0);
	amdgpu_ring_ग_लिखो(ring, val); /* reference */
	amdgpu_ring_ग_लिखो(ring, mask); /* mask */
	amdgpu_ring_ग_लिखो(ring, SDMA_PKT_POLL_REGMEM_DW5_RETRY_COUNT(0xfff) |
			  SDMA_PKT_POLL_REGMEM_DW5_INTERVAL(10));
पूर्ण

अटल व्योम sdma_v5_2_ring_emit_reg_ग_लिखो_reg_रुको(काष्ठा amdgpu_ring *ring,
						   uपूर्णांक32_t reg0, uपूर्णांक32_t reg1,
						   uपूर्णांक32_t ref, uपूर्णांक32_t mask)
अणु
	amdgpu_ring_emit_wreg(ring, reg0, ref);
	/* रुको क्रम a cycle to reset vm_inv_eng*_ack */
	amdgpu_ring_emit_reg_रुको(ring, reg0, 0, 0);
	amdgpu_ring_emit_reg_रुको(ring, reg1, mask, mask);
पूर्ण

अटल पूर्णांक sdma_v5_2_early_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	चयन (adev->asic_type) अणु
	हाल CHIP_SIENNA_CICHLID:
		adev->sdma.num_instances = 4;
		अवरोध;
	हाल CHIP_NAVY_FLOUNDER:
	हाल CHIP_DIMGREY_CAVEFISH:
		adev->sdma.num_instances = 2;
		अवरोध;
	हाल CHIP_VANGOGH:
		adev->sdma.num_instances = 1;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	sdma_v5_2_set_ring_funcs(adev);
	sdma_v5_2_set_buffer_funcs(adev);
	sdma_v5_2_set_vm_pte_funcs(adev);
	sdma_v5_2_set_irq_funcs(adev);

	वापस 0;
पूर्ण

अटल अचिन्हित sdma_v5_2_seq_to_irq_id(पूर्णांक seq_num)
अणु
	चयन (seq_num) अणु
	हाल 0:
		वापस SOC15_IH_CLIENTID_SDMA0;
	हाल 1:
		वापस SOC15_IH_CLIENTID_SDMA1;
	हाल 2:
		वापस SOC15_IH_CLIENTID_SDMA2;
	हाल 3:
		वापस SOC15_IH_CLIENTID_SDMA3_Sienna_Cichlid;
	शेष:
		अवरोध;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल अचिन्हित sdma_v5_2_seq_to_trap_id(पूर्णांक seq_num)
अणु
	चयन (seq_num) अणु
	हाल 0:
		वापस SDMA0_5_0__SRCID__SDMA_TRAP;
	हाल 1:
		वापस SDMA1_5_0__SRCID__SDMA_TRAP;
	हाल 2:
		वापस SDMA2_5_0__SRCID__SDMA_TRAP;
	हाल 3:
		वापस SDMA3_5_0__SRCID__SDMA_TRAP;
	शेष:
		अवरोध;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक sdma_v5_2_sw_init(व्योम *handle)
अणु
	काष्ठा amdgpu_ring *ring;
	पूर्णांक r, i;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	/* SDMA trap event */
	क्रम (i = 0; i < adev->sdma.num_instances; i++) अणु
		r = amdgpu_irq_add_id(adev, sdma_v5_2_seq_to_irq_id(i),
				      sdma_v5_2_seq_to_trap_id(i),
				      &adev->sdma.trap_irq);
		अगर (r)
			वापस r;
	पूर्ण

	r = sdma_v5_2_init_microcode(adev);
	अगर (r) अणु
		DRM_ERROR("Failed to load sdma firmware!\n");
		वापस r;
	पूर्ण

	क्रम (i = 0; i < adev->sdma.num_instances; i++) अणु
		ring = &adev->sdma.instance[i].ring;
		ring->ring_obj = शून्य;
		ring->use_करोorbell = true;
		ring->me = i;

		DRM_INFO("use_doorbell being set to: [%s]\n",
				ring->use_करोorbell?"true":"false");

		ring->करोorbell_index =
			(adev->करोorbell_index.sdma_engine[i] << 1); //get DWORD offset

		प्र_लिखो(ring->name, "sdma%d", i);
		r = amdgpu_ring_init(adev, ring, 1024, &adev->sdma.trap_irq,
				     AMDGPU_SDMA_IRQ_INSTANCE0 + i,
				     AMDGPU_RING_PRIO_DEFAULT, शून्य);
		अगर (r)
			वापस r;
	पूर्ण

	वापस r;
पूर्ण

अटल पूर्णांक sdma_v5_2_sw_fini(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	पूर्णांक i;

	क्रम (i = 0; i < adev->sdma.num_instances; i++)
		amdgpu_ring_fini(&adev->sdma.instance[i].ring);

	sdma_v5_2_destroy_inst_ctx(adev);

	वापस 0;
पूर्ण

अटल पूर्णांक sdma_v5_2_hw_init(व्योम *handle)
अणु
	पूर्णांक r;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	sdma_v5_2_init_golden_रेजिस्टरs(adev);

	r = sdma_v5_2_start(adev);

	वापस r;
पूर्ण

अटल पूर्णांक sdma_v5_2_hw_fini(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	अगर (amdgpu_sriov_vf(adev))
		वापस 0;

	sdma_v5_2_ctx_चयन_enable(adev, false);
	sdma_v5_2_enable(adev, false);

	वापस 0;
पूर्ण

अटल पूर्णांक sdma_v5_2_suspend(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	वापस sdma_v5_2_hw_fini(adev);
पूर्ण

अटल पूर्णांक sdma_v5_2_resume(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	वापस sdma_v5_2_hw_init(adev);
पूर्ण

अटल bool sdma_v5_2_is_idle(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	u32 i;

	क्रम (i = 0; i < adev->sdma.num_instances; i++) अणु
		u32 पंचांगp = RREG32(sdma_v5_2_get_reg_offset(adev, i, mmSDMA0_STATUS_REG));

		अगर (!(पंचांगp & SDMA0_STATUS_REG__IDLE_MASK))
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक sdma_v5_2_रुको_क्रम_idle(व्योम *handle)
अणु
	अचिन्हित i;
	u32 sdma0, sdma1, sdma2, sdma3;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	क्रम (i = 0; i < adev->usec_समयout; i++) अणु
		sdma0 = RREG32(sdma_v5_2_get_reg_offset(adev, 0, mmSDMA0_STATUS_REG));
		sdma1 = RREG32(sdma_v5_2_get_reg_offset(adev, 1, mmSDMA0_STATUS_REG));
		sdma2 = RREG32(sdma_v5_2_get_reg_offset(adev, 2, mmSDMA0_STATUS_REG));
		sdma3 = RREG32(sdma_v5_2_get_reg_offset(adev, 3, mmSDMA0_STATUS_REG));

		अगर (sdma0 & sdma1 & sdma2 & sdma3 & SDMA0_STATUS_REG__IDLE_MASK)
			वापस 0;
		udelay(1);
	पूर्ण
	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक sdma_v5_2_ring_preempt_ib(काष्ठा amdgpu_ring *ring)
अणु
	पूर्णांक i, r = 0;
	काष्ठा amdgpu_device *adev = ring->adev;
	u32 index = 0;
	u64 sdma_gfx_preempt;

	amdgpu_sdma_get_index_from_ring(ring, &index);
	sdma_gfx_preempt =
		sdma_v5_2_get_reg_offset(adev, index, mmSDMA0_GFX_PREEMPT);

	/* निश्चित preemption condition */
	amdgpu_ring_set_preempt_cond_exec(ring, false);

	/* emit the trailing fence */
	ring->trail_seq += 1;
	amdgpu_ring_alloc(ring, 10);
	sdma_v5_2_ring_emit_fence(ring, ring->trail_fence_gpu_addr,
				  ring->trail_seq, 0);
	amdgpu_ring_commit(ring);

	/* निश्चित IB preemption */
	WREG32(sdma_gfx_preempt, 1);

	/* poll the trailing fence */
	क्रम (i = 0; i < adev->usec_समयout; i++) अणु
		अगर (ring->trail_seq ==
		    le32_to_cpu(*(ring->trail_fence_cpu_addr)))
			अवरोध;
		udelay(1);
	पूर्ण

	अगर (i >= adev->usec_समयout) अणु
		r = -EINVAL;
		DRM_ERROR("ring %d failed to be preempted\n", ring->idx);
	पूर्ण

	/* deनिश्चित IB preemption */
	WREG32(sdma_gfx_preempt, 0);

	/* deनिश्चित the preemption condition */
	amdgpu_ring_set_preempt_cond_exec(ring, true);
	वापस r;
पूर्ण

अटल पूर्णांक sdma_v5_2_set_trap_irq_state(काष्ठा amdgpu_device *adev,
					काष्ठा amdgpu_irq_src *source,
					अचिन्हित type,
					क्रमागत amdgpu_पूर्णांकerrupt_state state)
अणु
	u32 sdma_cntl;

	u32 reg_offset = sdma_v5_2_get_reg_offset(adev, type, mmSDMA0_CNTL);

	sdma_cntl = RREG32(reg_offset);
	sdma_cntl = REG_SET_FIELD(sdma_cntl, SDMA0_CNTL, TRAP_ENABLE,
		       state == AMDGPU_IRQ_STATE_ENABLE ? 1 : 0);
	WREG32(reg_offset, sdma_cntl);

	वापस 0;
पूर्ण

अटल पूर्णांक sdma_v5_2_process_trap_irq(काष्ठा amdgpu_device *adev,
				      काष्ठा amdgpu_irq_src *source,
				      काष्ठा amdgpu_iv_entry *entry)
अणु
	DRM_DEBUG("IH: SDMA trap\n");
	चयन (entry->client_id) अणु
	हाल SOC15_IH_CLIENTID_SDMA0:
		चयन (entry->ring_id) अणु
		हाल 0:
			amdgpu_fence_process(&adev->sdma.instance[0].ring);
			अवरोध;
		हाल 1:
			/* XXX compute */
			अवरोध;
		हाल 2:
			/* XXX compute */
			अवरोध;
		हाल 3:
			/* XXX page queue*/
			अवरोध;
		पूर्ण
		अवरोध;
	हाल SOC15_IH_CLIENTID_SDMA1:
		चयन (entry->ring_id) अणु
		हाल 0:
			amdgpu_fence_process(&adev->sdma.instance[1].ring);
			अवरोध;
		हाल 1:
			/* XXX compute */
			अवरोध;
		हाल 2:
			/* XXX compute */
			अवरोध;
		हाल 3:
			/* XXX page queue*/
			अवरोध;
		पूर्ण
		अवरोध;
	हाल SOC15_IH_CLIENTID_SDMA2:
		चयन (entry->ring_id) अणु
		हाल 0:
			amdgpu_fence_process(&adev->sdma.instance[2].ring);
			अवरोध;
		हाल 1:
			/* XXX compute */
			अवरोध;
		हाल 2:
			/* XXX compute */
			अवरोध;
		हाल 3:
			/* XXX page queue*/
			अवरोध;
		पूर्ण
		अवरोध;
	हाल SOC15_IH_CLIENTID_SDMA3_Sienna_Cichlid:
		चयन (entry->ring_id) अणु
		हाल 0:
			amdgpu_fence_process(&adev->sdma.instance[3].ring);
			अवरोध;
		हाल 1:
			/* XXX compute */
			अवरोध;
		हाल 2:
			/* XXX compute */
			अवरोध;
		हाल 3:
			/* XXX page queue*/
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक sdma_v5_2_process_illegal_inst_irq(काष्ठा amdgpu_device *adev,
					      काष्ठा amdgpu_irq_src *source,
					      काष्ठा amdgpu_iv_entry *entry)
अणु
	वापस 0;
पूर्ण

अटल व्योम sdma_v5_2_update_medium_grain_घड़ी_gating(काष्ठा amdgpu_device *adev,
						       bool enable)
अणु
	uपूर्णांक32_t data, def;
	पूर्णांक i;

	क्रम (i = 0; i < adev->sdma.num_instances; i++) अणु
		अगर (enable && (adev->cg_flags & AMD_CG_SUPPORT_SDMA_MGCG)) अणु
			/* Enable sdma घड़ी gating */
			def = data = RREG32(sdma_v5_2_get_reg_offset(adev, i, mmSDMA0_CLK_CTRL));
			data &= ~(SDMA0_CLK_CTRL__SOFT_OVERRIDE4_MASK |
				  SDMA0_CLK_CTRL__SOFT_OVERRIDE3_MASK |
				  SDMA0_CLK_CTRL__SOFT_OVERRIDE2_MASK |
				  SDMA0_CLK_CTRL__SOFT_OVERRIDE1_MASK |
				  SDMA0_CLK_CTRL__SOFT_OVERRIDE0_MASK |
				  SDMA0_CLK_CTRL__SOFT_OVERRIDER_REG_MASK);
			अगर (def != data)
				WREG32(sdma_v5_2_get_reg_offset(adev, i, mmSDMA0_CLK_CTRL), data);
		पूर्ण अन्यथा अणु
			/* Disable sdma घड़ी gating */
			def = data = RREG32(sdma_v5_2_get_reg_offset(adev, i, mmSDMA0_CLK_CTRL));
			data |= (SDMA0_CLK_CTRL__SOFT_OVERRIDE4_MASK |
				 SDMA0_CLK_CTRL__SOFT_OVERRIDE3_MASK |
				 SDMA0_CLK_CTRL__SOFT_OVERRIDE2_MASK |
				 SDMA0_CLK_CTRL__SOFT_OVERRIDE1_MASK |
				 SDMA0_CLK_CTRL__SOFT_OVERRIDE0_MASK |
				 SDMA0_CLK_CTRL__SOFT_OVERRIDER_REG_MASK);
			अगर (def != data)
				WREG32(sdma_v5_2_get_reg_offset(adev, i, mmSDMA0_CLK_CTRL), data);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम sdma_v5_2_update_medium_grain_light_sleep(काष्ठा amdgpu_device *adev,
						      bool enable)
अणु
	uपूर्णांक32_t data, def;
	पूर्णांक i;

	क्रम (i = 0; i < adev->sdma.num_instances; i++) अणु
		अगर (enable && (adev->cg_flags & AMD_CG_SUPPORT_SDMA_LS)) अणु
			/* Enable sdma mem light sleep */
			def = data = RREG32(sdma_v5_2_get_reg_offset(adev, i, mmSDMA0_POWER_CNTL));
			data |= SDMA0_POWER_CNTL__MEM_POWER_OVERRIDE_MASK;
			अगर (def != data)
				WREG32(sdma_v5_2_get_reg_offset(adev, i, mmSDMA0_POWER_CNTL), data);

		पूर्ण अन्यथा अणु
			/* Disable sdma mem light sleep */
			def = data = RREG32(sdma_v5_2_get_reg_offset(adev, i, mmSDMA0_POWER_CNTL));
			data &= ~SDMA0_POWER_CNTL__MEM_POWER_OVERRIDE_MASK;
			अगर (def != data)
				WREG32(sdma_v5_2_get_reg_offset(adev, i, mmSDMA0_POWER_CNTL), data);

		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक sdma_v5_2_set_घड़ीgating_state(व्योम *handle,
					   क्रमागत amd_घड़ीgating_state state)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	अगर (amdgpu_sriov_vf(adev))
		वापस 0;

	चयन (adev->asic_type) अणु
	हाल CHIP_SIENNA_CICHLID:
	हाल CHIP_NAVY_FLOUNDER:
	हाल CHIP_VANGOGH:
	हाल CHIP_DIMGREY_CAVEFISH:
		sdma_v5_2_update_medium_grain_घड़ी_gating(adev,
				state == AMD_CG_STATE_GATE);
		sdma_v5_2_update_medium_grain_light_sleep(adev,
				state == AMD_CG_STATE_GATE);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sdma_v5_2_set_घातergating_state(व्योम *handle,
					  क्रमागत amd_घातergating_state state)
अणु
	वापस 0;
पूर्ण

अटल व्योम sdma_v5_2_get_घड़ीgating_state(व्योम *handle, u32 *flags)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	पूर्णांक data;

	अगर (amdgpu_sriov_vf(adev))
		*flags = 0;

	/* AMD_CG_SUPPORT_SDMA_LS */
	data = RREG32_KIQ(sdma_v5_2_get_reg_offset(adev, 0, mmSDMA0_POWER_CNTL));
	अगर (data & SDMA0_POWER_CNTL__MEM_POWER_OVERRIDE_MASK)
		*flags |= AMD_CG_SUPPORT_SDMA_LS;
पूर्ण

स्थिर काष्ठा amd_ip_funcs sdma_v5_2_ip_funcs = अणु
	.name = "sdma_v5_2",
	.early_init = sdma_v5_2_early_init,
	.late_init = शून्य,
	.sw_init = sdma_v5_2_sw_init,
	.sw_fini = sdma_v5_2_sw_fini,
	.hw_init = sdma_v5_2_hw_init,
	.hw_fini = sdma_v5_2_hw_fini,
	.suspend = sdma_v5_2_suspend,
	.resume = sdma_v5_2_resume,
	.is_idle = sdma_v5_2_is_idle,
	.रुको_क्रम_idle = sdma_v5_2_रुको_क्रम_idle,
	.soft_reset = sdma_v5_2_soft_reset,
	.set_घड़ीgating_state = sdma_v5_2_set_घड़ीgating_state,
	.set_घातergating_state = sdma_v5_2_set_घातergating_state,
	.get_घड़ीgating_state = sdma_v5_2_get_घड़ीgating_state,
पूर्ण;

अटल स्थिर काष्ठा amdgpu_ring_funcs sdma_v5_2_ring_funcs = अणु
	.type = AMDGPU_RING_TYPE_SDMA,
	.align_mask = 0xf,
	.nop = SDMA_PKT_NOP_HEADER_OP(SDMA_OP_NOP),
	.support_64bit_ptrs = true,
	.vmhub = AMDGPU_GFXHUB_0,
	.get_rptr = sdma_v5_2_ring_get_rptr,
	.get_wptr = sdma_v5_2_ring_get_wptr,
	.set_wptr = sdma_v5_2_ring_set_wptr,
	.emit_frame_size =
		5 + /* sdma_v5_2_ring_init_cond_exec */
		6 + /* sdma_v5_2_ring_emit_hdp_flush */
		3 + /* hdp_invalidate */
		6 + /* sdma_v5_2_ring_emit_pipeline_sync */
		/* sdma_v5_2_ring_emit_vm_flush */
		SOC15_FLUSH_GPU_TLB_NUM_WREG * 3 +
		SOC15_FLUSH_GPU_TLB_NUM_REG_WAIT * 6 +
		10 + 10 + 10, /* sdma_v5_2_ring_emit_fence x3 क्रम user fence, vm fence */
	.emit_ib_size = 7 + 6, /* sdma_v5_2_ring_emit_ib */
	.emit_ib = sdma_v5_2_ring_emit_ib,
	.emit_mem_sync = sdma_v5_2_ring_emit_mem_sync,
	.emit_fence = sdma_v5_2_ring_emit_fence,
	.emit_pipeline_sync = sdma_v5_2_ring_emit_pipeline_sync,
	.emit_vm_flush = sdma_v5_2_ring_emit_vm_flush,
	.emit_hdp_flush = sdma_v5_2_ring_emit_hdp_flush,
	.test_ring = sdma_v5_2_ring_test_ring,
	.test_ib = sdma_v5_2_ring_test_ib,
	.insert_nop = sdma_v5_2_ring_insert_nop,
	.pad_ib = sdma_v5_2_ring_pad_ib,
	.emit_wreg = sdma_v5_2_ring_emit_wreg,
	.emit_reg_रुको = sdma_v5_2_ring_emit_reg_रुको,
	.emit_reg_ग_लिखो_reg_रुको = sdma_v5_2_ring_emit_reg_ग_लिखो_reg_रुको,
	.init_cond_exec = sdma_v5_2_ring_init_cond_exec,
	.patch_cond_exec = sdma_v5_2_ring_patch_cond_exec,
	.preempt_ib = sdma_v5_2_ring_preempt_ib,
पूर्ण;

अटल व्योम sdma_v5_2_set_ring_funcs(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < adev->sdma.num_instances; i++) अणु
		adev->sdma.instance[i].ring.funcs = &sdma_v5_2_ring_funcs;
		adev->sdma.instance[i].ring.me = i;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा amdgpu_irq_src_funcs sdma_v5_2_trap_irq_funcs = अणु
	.set = sdma_v5_2_set_trap_irq_state,
	.process = sdma_v5_2_process_trap_irq,
पूर्ण;

अटल स्थिर काष्ठा amdgpu_irq_src_funcs sdma_v5_2_illegal_inst_irq_funcs = अणु
	.process = sdma_v5_2_process_illegal_inst_irq,
पूर्ण;

अटल व्योम sdma_v5_2_set_irq_funcs(काष्ठा amdgpu_device *adev)
अणु
	adev->sdma.trap_irq.num_types = AMDGPU_SDMA_IRQ_INSTANCE0 +
					adev->sdma.num_instances;
	adev->sdma.trap_irq.funcs = &sdma_v5_2_trap_irq_funcs;
	adev->sdma.illegal_inst_irq.funcs = &sdma_v5_2_illegal_inst_irq_funcs;
पूर्ण

/**
 * sdma_v5_2_emit_copy_buffer - copy buffer using the sDMA engine
 *
 * @ib: indirect buffer to copy to
 * @src_offset: src GPU address
 * @dst_offset: dst GPU address
 * @byte_count: number of bytes to xfer
 * @पंचांगz: अगर a secure copy should be used
 *
 * Copy GPU buffers using the DMA engine.
 * Used by the amdgpu tपंचांग implementation to move pages अगर
 * रेजिस्टरed as the asic copy callback.
 */
अटल व्योम sdma_v5_2_emit_copy_buffer(काष्ठा amdgpu_ib *ib,
				       uपूर्णांक64_t src_offset,
				       uपूर्णांक64_t dst_offset,
				       uपूर्णांक32_t byte_count,
				       bool पंचांगz)
अणु
	ib->ptr[ib->length_dw++] = SDMA_PKT_HEADER_OP(SDMA_OP_COPY) |
		SDMA_PKT_HEADER_SUB_OP(SDMA_SUBOP_COPY_LINEAR) |
		SDMA_PKT_COPY_LINEAR_HEADER_TMZ(पंचांगz ? 1 : 0);
	ib->ptr[ib->length_dw++] = byte_count - 1;
	ib->ptr[ib->length_dw++] = 0; /* src/dst endian swap */
	ib->ptr[ib->length_dw++] = lower_32_bits(src_offset);
	ib->ptr[ib->length_dw++] = upper_32_bits(src_offset);
	ib->ptr[ib->length_dw++] = lower_32_bits(dst_offset);
	ib->ptr[ib->length_dw++] = upper_32_bits(dst_offset);
पूर्ण

/**
 * sdma_v5_2_emit_fill_buffer - fill buffer using the sDMA engine
 *
 * @ib: indirect buffer to fill
 * @src_data: value to ग_लिखो to buffer
 * @dst_offset: dst GPU address
 * @byte_count: number of bytes to xfer
 *
 * Fill GPU buffers using the DMA engine.
 */
अटल व्योम sdma_v5_2_emit_fill_buffer(काष्ठा amdgpu_ib *ib,
				       uपूर्णांक32_t src_data,
				       uपूर्णांक64_t dst_offset,
				       uपूर्णांक32_t byte_count)
अणु
	ib->ptr[ib->length_dw++] = SDMA_PKT_HEADER_OP(SDMA_OP_CONST_FILL);
	ib->ptr[ib->length_dw++] = lower_32_bits(dst_offset);
	ib->ptr[ib->length_dw++] = upper_32_bits(dst_offset);
	ib->ptr[ib->length_dw++] = src_data;
	ib->ptr[ib->length_dw++] = byte_count - 1;
पूर्ण

अटल स्थिर काष्ठा amdgpu_buffer_funcs sdma_v5_2_buffer_funcs = अणु
	.copy_max_bytes = 0x400000,
	.copy_num_dw = 7,
	.emit_copy_buffer = sdma_v5_2_emit_copy_buffer,

	.fill_max_bytes = 0x400000,
	.fill_num_dw = 5,
	.emit_fill_buffer = sdma_v5_2_emit_fill_buffer,
पूर्ण;

अटल व्योम sdma_v5_2_set_buffer_funcs(काष्ठा amdgpu_device *adev)
अणु
	अगर (adev->mman.buffer_funcs == शून्य) अणु
		adev->mman.buffer_funcs = &sdma_v5_2_buffer_funcs;
		adev->mman.buffer_funcs_ring = &adev->sdma.instance[0].ring;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा amdgpu_vm_pte_funcs sdma_v5_2_vm_pte_funcs = अणु
	.copy_pte_num_dw = 7,
	.copy_pte = sdma_v5_2_vm_copy_pte,
	.ग_लिखो_pte = sdma_v5_2_vm_ग_लिखो_pte,
	.set_pte_pde = sdma_v5_2_vm_set_pte_pde,
पूर्ण;

अटल व्योम sdma_v5_2_set_vm_pte_funcs(काष्ठा amdgpu_device *adev)
अणु
	अचिन्हित i;

	अगर (adev->vm_manager.vm_pte_funcs == शून्य) अणु
		adev->vm_manager.vm_pte_funcs = &sdma_v5_2_vm_pte_funcs;
		क्रम (i = 0; i < adev->sdma.num_instances; i++) अणु
			adev->vm_manager.vm_pte_scheds[i] =
				&adev->sdma.instance[i].ring.sched;
		पूर्ण
		adev->vm_manager.vm_pte_num_scheds = adev->sdma.num_instances;
	पूर्ण
पूर्ण

स्थिर काष्ठा amdgpu_ip_block_version sdma_v5_2_ip_block = अणु
	.type = AMD_IP_BLOCK_TYPE_SDMA,
	.major = 5,
	.minor = 2,
	.rev = 0,
	.funcs = &sdma_v5_2_ip_funcs,
पूर्ण;
