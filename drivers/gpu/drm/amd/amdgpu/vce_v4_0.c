<शैली गुरु>
/*
 * Copyright 2016 Advanced Micro Devices, Inc.
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

#समावेश <linux/firmware.h>

#समावेश "amdgpu.h"
#समावेश "amdgpu_vce.h"
#समावेश "soc15.h"
#समावेश "soc15d.h"
#समावेश "soc15_common.h"
#समावेश "mmsch_v1_0.h"

#समावेश "vce/vce_4_0_offset.h"
#समावेश "vce/vce_4_0_default.h"
#समावेश "vce/vce_4_0_sh_mask.h"
#समावेश "mmhub/mmhub_1_0_offset.h"
#समावेश "mmhub/mmhub_1_0_sh_mask.h"

#समावेश "ivsrcid/vce/irqsrcs_vce_4_0.h"

#घोषणा VCE_STATUS_VCPU_REPORT_FW_LOADED_MASK	0x02

#घोषणा VCE_V4_0_FW_SIZE	(384 * 1024)
#घोषणा VCE_V4_0_STACK_SIZE	(64 * 1024)
#घोषणा VCE_V4_0_DATA_SIZE	((16 * 1024 * AMDGPU_MAX_VCE_HANDLES) + (52 * 1024))

अटल व्योम vce_v4_0_mc_resume(काष्ठा amdgpu_device *adev);
अटल व्योम vce_v4_0_set_ring_funcs(काष्ठा amdgpu_device *adev);
अटल व्योम vce_v4_0_set_irq_funcs(काष्ठा amdgpu_device *adev);

/**
 * vce_v4_0_ring_get_rptr - get पढ़ो poपूर्णांकer
 *
 * @ring: amdgpu_ring poपूर्णांकer
 *
 * Returns the current hardware पढ़ो poपूर्णांकer
 */
अटल uपूर्णांक64_t vce_v4_0_ring_get_rptr(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	अगर (ring->me == 0)
		वापस RREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_RB_RPTR));
	अन्यथा अगर (ring->me == 1)
		वापस RREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_RB_RPTR2));
	अन्यथा
		वापस RREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_RB_RPTR3));
पूर्ण

/**
 * vce_v4_0_ring_get_wptr - get ग_लिखो poपूर्णांकer
 *
 * @ring: amdgpu_ring poपूर्णांकer
 *
 * Returns the current hardware ग_लिखो poपूर्णांकer
 */
अटल uपूर्णांक64_t vce_v4_0_ring_get_wptr(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	अगर (ring->use_करोorbell)
		वापस adev->wb.wb[ring->wptr_offs];

	अगर (ring->me == 0)
		वापस RREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_RB_WPTR));
	अन्यथा अगर (ring->me == 1)
		वापस RREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_RB_WPTR2));
	अन्यथा
		वापस RREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_RB_WPTR3));
पूर्ण

/**
 * vce_v4_0_ring_set_wptr - set ग_लिखो poपूर्णांकer
 *
 * @ring: amdgpu_ring poपूर्णांकer
 *
 * Commits the ग_लिखो poपूर्णांकer to the hardware
 */
अटल व्योम vce_v4_0_ring_set_wptr(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	अगर (ring->use_करोorbell) अणु
		/* XXX check अगर swapping is necessary on BE */
		adev->wb.wb[ring->wptr_offs] = lower_32_bits(ring->wptr);
		WDOORBELL32(ring->करोorbell_index, lower_32_bits(ring->wptr));
		वापस;
	पूर्ण

	अगर (ring->me == 0)
		WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_RB_WPTR),
			lower_32_bits(ring->wptr));
	अन्यथा अगर (ring->me == 1)
		WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_RB_WPTR2),
			lower_32_bits(ring->wptr));
	अन्यथा
		WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_RB_WPTR3),
			lower_32_bits(ring->wptr));
पूर्ण

अटल पूर्णांक vce_v4_0_firmware_loaded(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i, j;

	क्रम (i = 0; i < 10; ++i) अणु
		क्रम (j = 0; j < 100; ++j) अणु
			uपूर्णांक32_t status =
				RREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_STATUS));

			अगर (status & VCE_STATUS_VCPU_REPORT_FW_LOADED_MASK)
				वापस 0;
			mdelay(10);
		पूर्ण

		DRM_ERROR("VCE not responding, trying to reset the ECPU!!!\n");
		WREG32_P(SOC15_REG_OFFSET(VCE, 0, mmVCE_SOFT_RESET),
				VCE_SOFT_RESET__ECPU_SOFT_RESET_MASK,
				~VCE_SOFT_RESET__ECPU_SOFT_RESET_MASK);
		mdelay(10);
		WREG32_P(SOC15_REG_OFFSET(VCE, 0, mmVCE_SOFT_RESET), 0,
				~VCE_SOFT_RESET__ECPU_SOFT_RESET_MASK);
		mdelay(10);

	पूर्ण

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक vce_v4_0_mmsch_start(काष्ठा amdgpu_device *adev,
				काष्ठा amdgpu_mm_table *table)
अणु
	uपूर्णांक32_t data = 0, loop;
	uपूर्णांक64_t addr = table->gpu_addr;
	काष्ठा mmsch_v1_0_init_header *header = (काष्ठा mmsch_v1_0_init_header *)table->cpu_addr;
	uपूर्णांक32_t size;

	size = header->header_size + header->vce_table_size + header->uvd_table_size;

	/* 1, ग_लिखो to vce_mmsch_vf_ctx_addr_lo/hi रेजिस्टर with GPU mc addr of memory descriptor location */
	WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_MMSCH_VF_CTX_ADDR_LO), lower_32_bits(addr));
	WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_MMSCH_VF_CTX_ADDR_HI), upper_32_bits(addr));

	/* 2, update vmid of descriptor */
	data = RREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_MMSCH_VF_VMID));
	data &= ~VCE_MMSCH_VF_VMID__VF_CTX_VMID_MASK;
	data |= (0 << VCE_MMSCH_VF_VMID__VF_CTX_VMID__SHIFT); /* use करोमुख्य0 क्रम MM scheduler */
	WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_MMSCH_VF_VMID), data);

	/* 3, notअगरy mmsch about the size of this descriptor */
	WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_MMSCH_VF_CTX_SIZE), size);

	/* 4, set resp to zero */
	WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_MMSCH_VF_MAILBOX_RESP), 0);

	WDOORBELL32(adev->vce.ring[0].करोorbell_index, 0);
	adev->wb.wb[adev->vce.ring[0].wptr_offs] = 0;
	adev->vce.ring[0].wptr = 0;
	adev->vce.ring[0].wptr_old = 0;

	/* 5, kick off the initialization and रुको until VCE_MMSCH_VF_MAILBOX_RESP becomes non-zero */
	WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_MMSCH_VF_MAILBOX_HOST), 0x10000001);

	data = RREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_MMSCH_VF_MAILBOX_RESP));
	loop = 1000;
	जबतक ((data & 0x10000002) != 0x10000002) अणु
		udelay(10);
		data = RREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_MMSCH_VF_MAILBOX_RESP));
		loop--;
		अगर (!loop)
			अवरोध;
	पूर्ण

	अगर (!loop) अणु
		dev_err(adev->dev, "failed to init MMSCH, mmVCE_MMSCH_VF_MAILBOX_RESP = %x\n", data);
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vce_v4_0_sriov_start(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_ring *ring;
	uपूर्णांक32_t offset, size;
	uपूर्णांक32_t table_size = 0;
	काष्ठा mmsch_v1_0_cmd_direct_ग_लिखो direct_wt = अणु अणु 0 पूर्ण पूर्ण;
	काष्ठा mmsch_v1_0_cmd_direct_पढ़ो_modअगरy_ग_लिखो direct_rd_mod_wt = अणु अणु 0 पूर्ण पूर्ण;
	काष्ठा mmsch_v1_0_cmd_direct_polling direct_poll = अणु अणु 0 पूर्ण पूर्ण;
	काष्ठा mmsch_v1_0_cmd_end end = अणु अणु 0 पूर्ण पूर्ण;
	uपूर्णांक32_t *init_table = adev->virt.mm_table.cpu_addr;
	काष्ठा mmsch_v1_0_init_header *header = (काष्ठा mmsch_v1_0_init_header *)init_table;

	direct_wt.cmd_header.command_type = MMSCH_COMMAND__सूचीECT_REG_WRITE;
	direct_rd_mod_wt.cmd_header.command_type = MMSCH_COMMAND__सूचीECT_REG_READ_MODIFY_WRITE;
	direct_poll.cmd_header.command_type = MMSCH_COMMAND__सूचीECT_REG_POLLING;
	end.cmd_header.command_type = MMSCH_COMMAND__END;

	अगर (header->vce_table_offset == 0 && header->vce_table_size == 0) अणु
		header->version = MMSCH_VERSION;
		header->header_size = माप(काष्ठा mmsch_v1_0_init_header) >> 2;

		अगर (header->uvd_table_offset == 0 && header->uvd_table_size == 0)
			header->vce_table_offset = header->header_size;
		अन्यथा
			header->vce_table_offset = header->uvd_table_size + header->uvd_table_offset;

		init_table += header->vce_table_offset;

		ring = &adev->vce.ring[0];
		MMSCH_V1_0_INSERT_सूचीECT_WT(SOC15_REG_OFFSET(VCE, 0, mmVCE_RB_BASE_LO),
					    lower_32_bits(ring->gpu_addr));
		MMSCH_V1_0_INSERT_सूचीECT_WT(SOC15_REG_OFFSET(VCE, 0, mmVCE_RB_BASE_HI),
					    upper_32_bits(ring->gpu_addr));
		MMSCH_V1_0_INSERT_सूचीECT_WT(SOC15_REG_OFFSET(VCE, 0, mmVCE_RB_SIZE),
					    ring->ring_size / 4);

		/* BEGING OF MC_RESUME */
		MMSCH_V1_0_INSERT_सूचीECT_WT(SOC15_REG_OFFSET(VCE, 0, mmVCE_LMI_CTRL), 0x398000);
		MMSCH_V1_0_INSERT_सूचीECT_RD_MOD_WT(SOC15_REG_OFFSET(VCE, 0, mmVCE_LMI_CACHE_CTRL), ~0x1, 0);
		MMSCH_V1_0_INSERT_सूचीECT_WT(SOC15_REG_OFFSET(VCE, 0, mmVCE_LMI_SWAP_CNTL), 0);
		MMSCH_V1_0_INSERT_सूचीECT_WT(SOC15_REG_OFFSET(VCE, 0, mmVCE_LMI_SWAP_CNTL1), 0);
		MMSCH_V1_0_INSERT_सूचीECT_WT(SOC15_REG_OFFSET(VCE, 0, mmVCE_LMI_VM_CTRL), 0);

		offset = AMDGPU_VCE_FIRMWARE_OFFSET;
		अगर (adev->firmware.load_type == AMDGPU_FW_LOAD_PSP) अणु
			uपूर्णांक32_t low = adev->firmware.ucode[AMDGPU_UCODE_ID_VCE].पंचांगr_mc_addr_lo;
			uपूर्णांक32_t hi = adev->firmware.ucode[AMDGPU_UCODE_ID_VCE].पंचांगr_mc_addr_hi;
			uपूर्णांक64_t पंचांगr_mc_addr = (uपूर्णांक64_t)(hi) << 32 | low;

			MMSCH_V1_0_INSERT_सूचीECT_WT(SOC15_REG_OFFSET(VCE, 0,
						mmVCE_LMI_VCPU_CACHE_40BIT_BAR0), पंचांगr_mc_addr >> 8);
			MMSCH_V1_0_INSERT_सूचीECT_WT(SOC15_REG_OFFSET(VCE, 0,
						mmVCE_LMI_VCPU_CACHE_64BIT_BAR0),
						(पंचांगr_mc_addr >> 40) & 0xff);
			MMSCH_V1_0_INSERT_सूचीECT_WT(SOC15_REG_OFFSET(VCE, 0, mmVCE_VCPU_CACHE_OFFSET0), 0);
		पूर्ण अन्यथा अणु
			MMSCH_V1_0_INSERT_सूचीECT_WT(SOC15_REG_OFFSET(VCE, 0,
						mmVCE_LMI_VCPU_CACHE_40BIT_BAR0),
						adev->vce.gpu_addr >> 8);
			MMSCH_V1_0_INSERT_सूचीECT_WT(SOC15_REG_OFFSET(VCE, 0,
						mmVCE_LMI_VCPU_CACHE_64BIT_BAR0),
						(adev->vce.gpu_addr >> 40) & 0xff);
			MMSCH_V1_0_INSERT_सूचीECT_WT(SOC15_REG_OFFSET(VCE, 0, mmVCE_VCPU_CACHE_OFFSET0),
						offset & ~0x0f000000);

		पूर्ण
		MMSCH_V1_0_INSERT_सूचीECT_WT(SOC15_REG_OFFSET(VCE, 0,
						mmVCE_LMI_VCPU_CACHE_40BIT_BAR1),
						adev->vce.gpu_addr >> 8);
		MMSCH_V1_0_INSERT_सूचीECT_WT(SOC15_REG_OFFSET(VCE, 0,
						mmVCE_LMI_VCPU_CACHE_64BIT_BAR1),
						(adev->vce.gpu_addr >> 40) & 0xff);
		MMSCH_V1_0_INSERT_सूचीECT_WT(SOC15_REG_OFFSET(VCE, 0,
						mmVCE_LMI_VCPU_CACHE_40BIT_BAR2),
						adev->vce.gpu_addr >> 8);
		MMSCH_V1_0_INSERT_सूचीECT_WT(SOC15_REG_OFFSET(VCE, 0,
						mmVCE_LMI_VCPU_CACHE_64BIT_BAR2),
						(adev->vce.gpu_addr >> 40) & 0xff);

		size = VCE_V4_0_FW_SIZE;
		MMSCH_V1_0_INSERT_सूचीECT_WT(SOC15_REG_OFFSET(VCE, 0, mmVCE_VCPU_CACHE_SIZE0), size);

		offset = (adev->firmware.load_type != AMDGPU_FW_LOAD_PSP) ? offset + size : 0;
		size = VCE_V4_0_STACK_SIZE;
		MMSCH_V1_0_INSERT_सूचीECT_WT(SOC15_REG_OFFSET(VCE, 0, mmVCE_VCPU_CACHE_OFFSET1),
					(offset & ~0x0f000000) | (1 << 24));
		MMSCH_V1_0_INSERT_सूचीECT_WT(SOC15_REG_OFFSET(VCE, 0, mmVCE_VCPU_CACHE_SIZE1), size);

		offset += size;
		size = VCE_V4_0_DATA_SIZE;
		MMSCH_V1_0_INSERT_सूचीECT_WT(SOC15_REG_OFFSET(VCE, 0, mmVCE_VCPU_CACHE_OFFSET2),
					(offset & ~0x0f000000) | (2 << 24));
		MMSCH_V1_0_INSERT_सूचीECT_WT(SOC15_REG_OFFSET(VCE, 0, mmVCE_VCPU_CACHE_SIZE2), size);

		MMSCH_V1_0_INSERT_सूचीECT_RD_MOD_WT(SOC15_REG_OFFSET(VCE, 0, mmVCE_LMI_CTRL2), ~0x100, 0);
		MMSCH_V1_0_INSERT_सूचीECT_RD_MOD_WT(SOC15_REG_OFFSET(VCE, 0, mmVCE_SYS_INT_EN),
						   VCE_SYS_INT_EN__VCE_SYS_INT_TRAP_INTERRUPT_EN_MASK,
						   VCE_SYS_INT_EN__VCE_SYS_INT_TRAP_INTERRUPT_EN_MASK);

		/* end of MC_RESUME */
		MMSCH_V1_0_INSERT_सूचीECT_RD_MOD_WT(SOC15_REG_OFFSET(VCE, 0, mmVCE_STATUS),
						   VCE_STATUS__JOB_BUSY_MASK, ~VCE_STATUS__JOB_BUSY_MASK);
		MMSCH_V1_0_INSERT_सूचीECT_RD_MOD_WT(SOC15_REG_OFFSET(VCE, 0, mmVCE_VCPU_CNTL),
						   ~0x200001, VCE_VCPU_CNTL__CLK_EN_MASK);
		MMSCH_V1_0_INSERT_सूचीECT_RD_MOD_WT(SOC15_REG_OFFSET(VCE, 0, mmVCE_SOFT_RESET),
						   ~VCE_SOFT_RESET__ECPU_SOFT_RESET_MASK, 0);

		MMSCH_V1_0_INSERT_सूचीECT_POLL(SOC15_REG_OFFSET(VCE, 0, mmVCE_STATUS),
					      VCE_STATUS_VCPU_REPORT_FW_LOADED_MASK,
					      VCE_STATUS_VCPU_REPORT_FW_LOADED_MASK);

		/* clear BUSY flag */
		MMSCH_V1_0_INSERT_सूचीECT_RD_MOD_WT(SOC15_REG_OFFSET(VCE, 0, mmVCE_STATUS),
						   ~VCE_STATUS__JOB_BUSY_MASK, 0);

		/* add end packet */
		स_नकल((व्योम *)init_table, &end, माप(काष्ठा mmsch_v1_0_cmd_end));
		table_size += माप(काष्ठा mmsch_v1_0_cmd_end) / 4;
		header->vce_table_size = table_size;
	पूर्ण

	वापस vce_v4_0_mmsch_start(adev, &adev->virt.mm_table);
पूर्ण

/**
 * vce_v4_0_start - start VCE block
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Setup and start the VCE block
 */
अटल पूर्णांक vce_v4_0_start(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_ring *ring;
	पूर्णांक r;

	ring = &adev->vce.ring[0];

	WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_RB_RPTR), lower_32_bits(ring->wptr));
	WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_RB_WPTR), lower_32_bits(ring->wptr));
	WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_RB_BASE_LO), ring->gpu_addr);
	WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_RB_BASE_HI), upper_32_bits(ring->gpu_addr));
	WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_RB_SIZE), ring->ring_size / 4);

	ring = &adev->vce.ring[1];

	WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_RB_RPTR2), lower_32_bits(ring->wptr));
	WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_RB_WPTR2), lower_32_bits(ring->wptr));
	WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_RB_BASE_LO2), ring->gpu_addr);
	WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_RB_BASE_HI2), upper_32_bits(ring->gpu_addr));
	WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_RB_SIZE2), ring->ring_size / 4);

	ring = &adev->vce.ring[2];

	WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_RB_RPTR3), lower_32_bits(ring->wptr));
	WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_RB_WPTR3), lower_32_bits(ring->wptr));
	WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_RB_BASE_LO3), ring->gpu_addr);
	WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_RB_BASE_HI3), upper_32_bits(ring->gpu_addr));
	WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_RB_SIZE3), ring->ring_size / 4);

	vce_v4_0_mc_resume(adev);
	WREG32_P(SOC15_REG_OFFSET(VCE, 0, mmVCE_STATUS), VCE_STATUS__JOB_BUSY_MASK,
			~VCE_STATUS__JOB_BUSY_MASK);

	WREG32_P(SOC15_REG_OFFSET(VCE, 0, mmVCE_VCPU_CNTL), 1, ~0x200001);

	WREG32_P(SOC15_REG_OFFSET(VCE, 0, mmVCE_SOFT_RESET), 0,
			~VCE_SOFT_RESET__ECPU_SOFT_RESET_MASK);
	mdelay(100);

	r = vce_v4_0_firmware_loaded(adev);

	/* clear BUSY flag */
	WREG32_P(SOC15_REG_OFFSET(VCE, 0, mmVCE_STATUS), 0, ~VCE_STATUS__JOB_BUSY_MASK);

	अगर (r) अणु
		DRM_ERROR("VCE not responding, giving up!!!\n");
		वापस r;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vce_v4_0_stop(काष्ठा amdgpu_device *adev)
अणु

	/* Disable VCPU */
	WREG32_P(SOC15_REG_OFFSET(VCE, 0, mmVCE_VCPU_CNTL), 0, ~0x200001);

	/* hold on ECPU */
	WREG32_P(SOC15_REG_OFFSET(VCE, 0, mmVCE_SOFT_RESET),
			VCE_SOFT_RESET__ECPU_SOFT_RESET_MASK,
			~VCE_SOFT_RESET__ECPU_SOFT_RESET_MASK);

	/* clear VCE_STATUS */
	WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_STATUS), 0);

	/* Set Clock-Gating off */
	/* अगर (adev->cg_flags & AMD_CG_SUPPORT_VCE_MGCG)
		vce_v4_0_set_vce_sw_घड़ी_gating(adev, false);
	*/

	वापस 0;
पूर्ण

अटल पूर्णांक vce_v4_0_early_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	अगर (amdgpu_sriov_vf(adev)) /* currently only VCN0 support SRIOV */
		adev->vce.num_rings = 1;
	अन्यथा
		adev->vce.num_rings = 3;

	vce_v4_0_set_ring_funcs(adev);
	vce_v4_0_set_irq_funcs(adev);

	वापस 0;
पूर्ण

अटल पूर्णांक vce_v4_0_sw_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	काष्ठा amdgpu_ring *ring;

	अचिन्हित size;
	पूर्णांक r, i;

	r = amdgpu_irq_add_id(adev, SOC15_IH_CLIENTID_VCE0, 167, &adev->vce.irq);
	अगर (r)
		वापस r;

	size  = VCE_V4_0_STACK_SIZE + VCE_V4_0_DATA_SIZE;
	अगर (adev->firmware.load_type != AMDGPU_FW_LOAD_PSP)
		size += VCE_V4_0_FW_SIZE;

	r = amdgpu_vce_sw_init(adev, size);
	अगर (r)
		वापस r;

	अगर (adev->firmware.load_type == AMDGPU_FW_LOAD_PSP) अणु
		स्थिर काष्ठा common_firmware_header *hdr;
		अचिन्हित size = amdgpu_bo_size(adev->vce.vcpu_bo);

		adev->vce.saved_bo = kvदो_स्मृति(size, GFP_KERNEL);
		अगर (!adev->vce.saved_bo)
			वापस -ENOMEM;

		hdr = (स्थिर काष्ठा common_firmware_header *)adev->vce.fw->data;
		adev->firmware.ucode[AMDGPU_UCODE_ID_VCE].ucode_id = AMDGPU_UCODE_ID_VCE;
		adev->firmware.ucode[AMDGPU_UCODE_ID_VCE].fw = adev->vce.fw;
		adev->firmware.fw_size +=
			ALIGN(le32_to_cpu(hdr->ucode_size_bytes), PAGE_SIZE);
		DRM_INFO("PSP loading VCE firmware\n");
	पूर्ण अन्यथा अणु
		r = amdgpu_vce_resume(adev);
		अगर (r)
			वापस r;
	पूर्ण

	क्रम (i = 0; i < adev->vce.num_rings; i++) अणु
		ring = &adev->vce.ring[i];
		प्र_लिखो(ring->name, "vce%d", i);
		अगर (amdgpu_sriov_vf(adev)) अणु
			/* DOORBELL only works under SRIOV */
			ring->use_करोorbell = true;

			/* currently only use the first encoding ring क्रम sriov,
			 * so set unused location क्रम other unused rings.
			 */
			अगर (i == 0)
				ring->करोorbell_index = adev->करोorbell_index.uvd_vce.vce_ring0_1 * 2;
			अन्यथा
				ring->करोorbell_index = adev->करोorbell_index.uvd_vce.vce_ring2_3 * 2 + 1;
		पूर्ण
		r = amdgpu_ring_init(adev, ring, 512, &adev->vce.irq, 0,
				     AMDGPU_RING_PRIO_DEFAULT, शून्य);
		अगर (r)
			वापस r;
	पूर्ण


	r = amdgpu_vce_entity_init(adev);
	अगर (r)
		वापस r;

	r = amdgpu_virt_alloc_mm_table(adev);
	अगर (r)
		वापस r;

	वापस r;
पूर्ण

अटल पूर्णांक vce_v4_0_sw_fini(व्योम *handle)
अणु
	पूर्णांक r;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	/* मुक्त MM table */
	amdgpu_virt_मुक्त_mm_table(adev);

	अगर (adev->firmware.load_type == AMDGPU_FW_LOAD_PSP) अणु
		kvमुक्त(adev->vce.saved_bo);
		adev->vce.saved_bo = शून्य;
	पूर्ण

	r = amdgpu_vce_suspend(adev);
	अगर (r)
		वापस r;

	वापस amdgpu_vce_sw_fini(adev);
पूर्ण

अटल पूर्णांक vce_v4_0_hw_init(व्योम *handle)
अणु
	पूर्णांक r, i;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	अगर (amdgpu_sriov_vf(adev))
		r = vce_v4_0_sriov_start(adev);
	अन्यथा
		r = vce_v4_0_start(adev);
	अगर (r)
		वापस r;

	क्रम (i = 0; i < adev->vce.num_rings; i++) अणु
		r = amdgpu_ring_test_helper(&adev->vce.ring[i]);
		अगर (r)
			वापस r;
	पूर्ण

	DRM_INFO("VCE initialized successfully.\n");

	वापस 0;
पूर्ण

अटल पूर्णांक vce_v4_0_hw_fini(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	अगर (!amdgpu_sriov_vf(adev)) अणु
		/* vce_v4_0_रुको_क्रम_idle(handle); */
		vce_v4_0_stop(adev);
	पूर्ण अन्यथा अणु
		/* full access mode, so करोn't touch any VCE रेजिस्टर */
		DRM_DEBUG("For SRIOV client, shouldn't do anything.\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vce_v4_0_suspend(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	पूर्णांक r;

	अगर (adev->vce.vcpu_bo == शून्य)
		वापस 0;

	अगर (adev->firmware.load_type == AMDGPU_FW_LOAD_PSP) अणु
		अचिन्हित size = amdgpu_bo_size(adev->vce.vcpu_bo);
		व्योम *ptr = adev->vce.cpu_addr;

		स_नकल_fromio(adev->vce.saved_bo, ptr, size);
	पूर्ण

	r = vce_v4_0_hw_fini(adev);
	अगर (r)
		वापस r;

	वापस amdgpu_vce_suspend(adev);
पूर्ण

अटल पूर्णांक vce_v4_0_resume(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	पूर्णांक r;

	अगर (adev->vce.vcpu_bo == शून्य)
		वापस -EINVAL;

	अगर (adev->firmware.load_type == AMDGPU_FW_LOAD_PSP) अणु
		अचिन्हित size = amdgpu_bo_size(adev->vce.vcpu_bo);
		व्योम *ptr = adev->vce.cpu_addr;

		स_नकल_toio(ptr, adev->vce.saved_bo, size);
	पूर्ण अन्यथा अणु
		r = amdgpu_vce_resume(adev);
		अगर (r)
			वापस r;
	पूर्ण

	वापस vce_v4_0_hw_init(adev);
पूर्ण

अटल व्योम vce_v4_0_mc_resume(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक32_t offset, size;
	uपूर्णांक64_t पंचांगr_mc_addr;

	WREG32_P(SOC15_REG_OFFSET(VCE, 0, mmVCE_CLOCK_GATING_A), 0, ~(1 << 16));
	WREG32_P(SOC15_REG_OFFSET(VCE, 0, mmVCE_UENC_CLOCK_GATING), 0x1FF000, ~0xFF9FF000);
	WREG32_P(SOC15_REG_OFFSET(VCE, 0, mmVCE_UENC_REG_CLOCK_GATING), 0x3F, ~0x3F);
	WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_CLOCK_GATING_B), 0x1FF);

	WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_LMI_CTRL), 0x00398000);
	WREG32_P(SOC15_REG_OFFSET(VCE, 0, mmVCE_LMI_CACHE_CTRL), 0x0, ~0x1);
	WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_LMI_SWAP_CNTL), 0);
	WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_LMI_SWAP_CNTL1), 0);
	WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_LMI_VM_CTRL), 0);

	offset = AMDGPU_VCE_FIRMWARE_OFFSET;

	अगर (adev->firmware.load_type == AMDGPU_FW_LOAD_PSP) अणु
		पंचांगr_mc_addr = (uपूर्णांक64_t)(adev->firmware.ucode[AMDGPU_UCODE_ID_VCE].पंचांगr_mc_addr_hi) << 32 |
										adev->firmware.ucode[AMDGPU_UCODE_ID_VCE].पंचांगr_mc_addr_lo;
		WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_LMI_VCPU_CACHE_40BIT_BAR0),
			(पंचांगr_mc_addr >> 8));
		WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_LMI_VCPU_CACHE_64BIT_BAR0),
			(पंचांगr_mc_addr >> 40) & 0xff);
		WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_VCPU_CACHE_OFFSET0), 0);
	पूर्ण अन्यथा अणु
		WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_LMI_VCPU_CACHE_40BIT_BAR0),
			(adev->vce.gpu_addr >> 8));
		WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_LMI_VCPU_CACHE_64BIT_BAR0),
			(adev->vce.gpu_addr >> 40) & 0xff);
		WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_VCPU_CACHE_OFFSET0), offset & ~0x0f000000);
	पूर्ण

	size = VCE_V4_0_FW_SIZE;
	WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_VCPU_CACHE_SIZE0), size);

	WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_LMI_VCPU_CACHE_40BIT_BAR1), (adev->vce.gpu_addr >> 8));
	WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_LMI_VCPU_CACHE_64BIT_BAR1), (adev->vce.gpu_addr >> 40) & 0xff);
	offset = (adev->firmware.load_type != AMDGPU_FW_LOAD_PSP) ? offset + size : 0;
	size = VCE_V4_0_STACK_SIZE;
	WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_VCPU_CACHE_OFFSET1), (offset & ~0x0f000000) | (1 << 24));
	WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_VCPU_CACHE_SIZE1), size);

	WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_LMI_VCPU_CACHE_40BIT_BAR2), (adev->vce.gpu_addr >> 8));
	WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_LMI_VCPU_CACHE_64BIT_BAR2), (adev->vce.gpu_addr >> 40) & 0xff);
	offset += size;
	size = VCE_V4_0_DATA_SIZE;
	WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_VCPU_CACHE_OFFSET2), (offset & ~0x0f000000) | (2 << 24));
	WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_VCPU_CACHE_SIZE2), size);

	WREG32_P(SOC15_REG_OFFSET(VCE, 0, mmVCE_LMI_CTRL2), 0x0, ~0x100);
	WREG32_P(SOC15_REG_OFFSET(VCE, 0, mmVCE_SYS_INT_EN),
			VCE_SYS_INT_EN__VCE_SYS_INT_TRAP_INTERRUPT_EN_MASK,
			~VCE_SYS_INT_EN__VCE_SYS_INT_TRAP_INTERRUPT_EN_MASK);
पूर्ण

अटल पूर्णांक vce_v4_0_set_घड़ीgating_state(व्योम *handle,
					  क्रमागत amd_घड़ीgating_state state)
अणु
	/* needed क्रम driver unload*/
	वापस 0;
पूर्ण

#अगर 0
अटल bool vce_v4_0_is_idle(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	u32 mask = 0;

	mask |= (adev->vce.harvest_config & AMDGPU_VCE_HARVEST_VCE0) ? 0 : SRBM_STATUS2__VCE0_BUSY_MASK;
	mask |= (adev->vce.harvest_config & AMDGPU_VCE_HARVEST_VCE1) ? 0 : SRBM_STATUS2__VCE1_BUSY_MASK;

	वापस !(RREG32(mmSRBM_STATUS2) & mask);
पूर्ण

अटल पूर्णांक vce_v4_0_रुको_क्रम_idle(व्योम *handle)
अणु
	अचिन्हित i;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	क्रम (i = 0; i < adev->usec_समयout; i++)
		अगर (vce_v4_0_is_idle(handle))
			वापस 0;

	वापस -ETIMEDOUT;
पूर्ण

#घोषणा  VCE_STATUS_VCPU_REPORT_AUTO_BUSY_MASK  0x00000008L   /* AUTO_BUSY */
#घोषणा  VCE_STATUS_VCPU_REPORT_RB0_BUSY_MASK   0x00000010L   /* RB0_BUSY */
#घोषणा  VCE_STATUS_VCPU_REPORT_RB1_BUSY_MASK   0x00000020L   /* RB1_BUSY */
#घोषणा  AMDGPU_VCE_STATUS_BUSY_MASK (VCE_STATUS_VCPU_REPORT_AUTO_BUSY_MASK | \
				      VCE_STATUS_VCPU_REPORT_RB0_BUSY_MASK)

अटल bool vce_v4_0_check_soft_reset(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	u32 srbm_soft_reset = 0;

	/* According to VCE team , we should use VCE_STATUS instead
	 * SRBM_STATUS.VCE_BUSY bit क्रम busy status checking.
	 * GRBM_GFX_INDEX.INSTANCE_INDEX is used to specअगरy which VCE
	 * instance's रेजिस्टरs are accessed
	 * (0 क्रम 1st instance, 10 क्रम 2nd instance).
	 *
	 *VCE_STATUS
	 *|UENC|ACPI|AUTO ACTIVE|RB1 |RB0 |RB2 |          |FW_LOADED|JOB |
	 *|----+----+-----------+----+----+----+----------+---------+----|
	 *|bit8|bit7|    bit6   |bit5|bit4|bit3|   bit2   |  bit1   |bit0|
	 *
	 * VCE team suggest use bit 3--bit 6 क्रम busy status check
	 */
	mutex_lock(&adev->grbm_idx_mutex);
	WREG32_FIELD(GRBM_GFX_INDEX, INSTANCE_INDEX, 0);
	अगर (RREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_STATUS) & AMDGPU_VCE_STATUS_BUSY_MASK) अणु
		srbm_soft_reset = REG_SET_FIELD(srbm_soft_reset, SRBM_SOFT_RESET, SOFT_RESET_VCE0, 1);
		srbm_soft_reset = REG_SET_FIELD(srbm_soft_reset, SRBM_SOFT_RESET, SOFT_RESET_VCE1, 1);
	पूर्ण
	WREG32_FIELD(GRBM_GFX_INDEX, INSTANCE_INDEX, 0x10);
	अगर (RREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_STATUS) & AMDGPU_VCE_STATUS_BUSY_MASK) अणु
		srbm_soft_reset = REG_SET_FIELD(srbm_soft_reset, SRBM_SOFT_RESET, SOFT_RESET_VCE0, 1);
		srbm_soft_reset = REG_SET_FIELD(srbm_soft_reset, SRBM_SOFT_RESET, SOFT_RESET_VCE1, 1);
	पूर्ण
	WREG32_FIELD(GRBM_GFX_INDEX, INSTANCE_INDEX, 0);
	mutex_unlock(&adev->grbm_idx_mutex);

	अगर (srbm_soft_reset) अणु
		adev->vce.srbm_soft_reset = srbm_soft_reset;
		वापस true;
	पूर्ण अन्यथा अणु
		adev->vce.srbm_soft_reset = 0;
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक vce_v4_0_soft_reset(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	u32 srbm_soft_reset;

	अगर (!adev->vce.srbm_soft_reset)
		वापस 0;
	srbm_soft_reset = adev->vce.srbm_soft_reset;

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

अटल पूर्णांक vce_v4_0_pre_soft_reset(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	अगर (!adev->vce.srbm_soft_reset)
		वापस 0;

	mdelay(5);

	वापस vce_v4_0_suspend(adev);
पूर्ण


अटल पूर्णांक vce_v4_0_post_soft_reset(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	अगर (!adev->vce.srbm_soft_reset)
		वापस 0;

	mdelay(5);

	वापस vce_v4_0_resume(adev);
पूर्ण

अटल व्योम vce_v4_0_override_vce_घड़ी_gating(काष्ठा amdgpu_device *adev, bool override)
अणु
	u32 पंचांगp, data;

	पंचांगp = data = RREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_RB_ARB_CTRL));
	अगर (override)
		data |= VCE_RB_ARB_CTRL__VCE_CGTT_OVERRIDE_MASK;
	अन्यथा
		data &= ~VCE_RB_ARB_CTRL__VCE_CGTT_OVERRIDE_MASK;

	अगर (पंचांगp != data)
		WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_RB_ARB_CTRL), data);
पूर्ण

अटल व्योम vce_v4_0_set_vce_sw_घड़ी_gating(काष्ठा amdgpu_device *adev,
					     bool gated)
अणु
	u32 data;

	/* Set Override to disable Clock Gating */
	vce_v4_0_override_vce_घड़ी_gating(adev, true);

	/* This function enables MGCG which is controlled by firmware.
	   With the घड़ीs in the gated state the core is still
	   accessible but the firmware will throttle the घड़ीs on the
	   fly as necessary.
	*/
	अगर (gated) अणु
		data = RREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_CLOCK_GATING_B));
		data |= 0x1ff;
		data &= ~0xef0000;
		WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_CLOCK_GATING_B), data);

		data = RREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_UENC_CLOCK_GATING));
		data |= 0x3ff000;
		data &= ~0xffc00000;
		WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_UENC_CLOCK_GATING), data);

		data = RREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_UENC_CLOCK_GATING_2));
		data |= 0x2;
		data &= ~0x00010000;
		WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_UENC_CLOCK_GATING_2), data);

		data = RREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_UENC_REG_CLOCK_GATING));
		data |= 0x37f;
		WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_UENC_REG_CLOCK_GATING), data);

		data = RREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_UENC_DMA_DCLK_CTRL));
		data |= VCE_UENC_DMA_DCLK_CTRL__WRDMCLK_FORCEON_MASK |
			VCE_UENC_DMA_DCLK_CTRL__RDDMCLK_FORCEON_MASK |
			VCE_UENC_DMA_DCLK_CTRL__REGCLK_FORCEON_MASK  |
			0x8;
		WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_UENC_DMA_DCLK_CTRL), data);
	पूर्ण अन्यथा अणु
		data = RREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_CLOCK_GATING_B));
		data &= ~0x80010;
		data |= 0xe70008;
		WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_CLOCK_GATING_B), data);

		data = RREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_UENC_CLOCK_GATING));
		data |= 0xffc00000;
		WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_UENC_CLOCK_GATING), data);

		data = RREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_UENC_CLOCK_GATING_2));
		data |= 0x10000;
		WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_UENC_CLOCK_GATING_2), data);

		data = RREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_UENC_REG_CLOCK_GATING));
		data &= ~0xffc00000;
		WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_UENC_REG_CLOCK_GATING), data);

		data = RREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_UENC_DMA_DCLK_CTRL));
		data &= ~(VCE_UENC_DMA_DCLK_CTRL__WRDMCLK_FORCEON_MASK |
			  VCE_UENC_DMA_DCLK_CTRL__RDDMCLK_FORCEON_MASK |
			  VCE_UENC_DMA_DCLK_CTRL__REGCLK_FORCEON_MASK  |
			  0x8);
		WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_UENC_DMA_DCLK_CTRL), data);
	पूर्ण
	vce_v4_0_override_vce_घड़ी_gating(adev, false);
पूर्ण

अटल व्योम vce_v4_0_set_bypass_mode(काष्ठा amdgpu_device *adev, bool enable)
अणु
	u32 पंचांगp = RREG32_SMC(ixGCK_DFS_BYPASS_CNTL);

	अगर (enable)
		पंचांगp |= GCK_DFS_BYPASS_CNTL__BYPASSECLK_MASK;
	अन्यथा
		पंचांगp &= ~GCK_DFS_BYPASS_CNTL__BYPASSECLK_MASK;

	WREG32_SMC(ixGCK_DFS_BYPASS_CNTL, पंचांगp);
पूर्ण

अटल पूर्णांक vce_v4_0_set_घड़ीgating_state(व्योम *handle,
					  क्रमागत amd_घड़ीgating_state state)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	bool enable = (state == AMD_CG_STATE_GATE);
	पूर्णांक i;

	अगर ((adev->asic_type == CHIP_POLARIS10) ||
		(adev->asic_type == CHIP_TONGA) ||
		(adev->asic_type == CHIP_FIJI))
		vce_v4_0_set_bypass_mode(adev, enable);

	अगर (!(adev->cg_flags & AMD_CG_SUPPORT_VCE_MGCG))
		वापस 0;

	mutex_lock(&adev->grbm_idx_mutex);
	क्रम (i = 0; i < 2; i++) अणु
		/* Program VCE Instance 0 or 1 अगर not harvested */
		अगर (adev->vce.harvest_config & (1 << i))
			जारी;

		WREG32_FIELD(GRBM_GFX_INDEX, VCE_INSTANCE, i);

		अगर (enable) अणु
			/* initialize VCE_CLOCK_GATING_A: Clock ON/OFF delay */
			uपूर्णांक32_t data = RREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_CLOCK_GATING_A);
			data &= ~(0xf | 0xff0);
			data |= ((0x0 << 0) | (0x04 << 4));
			WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_CLOCK_GATING_A, data);

			/* initialize VCE_UENC_CLOCK_GATING: Clock ON/OFF delay */
			data = RREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_UENC_CLOCK_GATING);
			data &= ~(0xf | 0xff0);
			data |= ((0x0 << 0) | (0x04 << 4));
			WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_UENC_CLOCK_GATING, data);
		पूर्ण

		vce_v4_0_set_vce_sw_घड़ी_gating(adev, enable);
	पूर्ण

	WREG32_FIELD(GRBM_GFX_INDEX, VCE_INSTANCE, 0);
	mutex_unlock(&adev->grbm_idx_mutex);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक vce_v4_0_set_घातergating_state(व्योम *handle,
					  क्रमागत amd_घातergating_state state)
अणु
	/* This करोesn't actually घातergate the VCE block.
	 * That's करोne in the dpm code via the SMC.  This
	 * just re-inits the block as necessary.  The actual
	 * gating still happens in the dpm code.  We should
	 * revisit this when there is a cleaner line between
	 * the smc and the hw blocks
	 */
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	अगर (state == AMD_PG_STATE_GATE)
		वापस vce_v4_0_stop(adev);
	अन्यथा
		वापस vce_v4_0_start(adev);
पूर्ण

अटल व्योम vce_v4_0_ring_emit_ib(काष्ठा amdgpu_ring *ring, काष्ठा amdgpu_job *job,
					काष्ठा amdgpu_ib *ib, uपूर्णांक32_t flags)
अणु
	अचिन्हित vmid = AMDGPU_JOB_GET_VMID(job);

	amdgpu_ring_ग_लिखो(ring, VCE_CMD_IB_VM);
	amdgpu_ring_ग_लिखो(ring, vmid);
	amdgpu_ring_ग_लिखो(ring, lower_32_bits(ib->gpu_addr));
	amdgpu_ring_ग_लिखो(ring, upper_32_bits(ib->gpu_addr));
	amdgpu_ring_ग_लिखो(ring, ib->length_dw);
पूर्ण

अटल व्योम vce_v4_0_ring_emit_fence(काष्ठा amdgpu_ring *ring, u64 addr,
			u64 seq, अचिन्हित flags)
अणु
	WARN_ON(flags & AMDGPU_FENCE_FLAG_64BIT);

	amdgpu_ring_ग_लिखो(ring, VCE_CMD_FENCE);
	amdgpu_ring_ग_लिखो(ring, addr);
	amdgpu_ring_ग_लिखो(ring, upper_32_bits(addr));
	amdgpu_ring_ग_लिखो(ring, seq);
	amdgpu_ring_ग_लिखो(ring, VCE_CMD_TRAP);
पूर्ण

अटल व्योम vce_v4_0_ring_insert_end(काष्ठा amdgpu_ring *ring)
अणु
	amdgpu_ring_ग_लिखो(ring, VCE_CMD_END);
पूर्ण

अटल व्योम vce_v4_0_emit_reg_रुको(काष्ठा amdgpu_ring *ring, uपूर्णांक32_t reg,
				   uपूर्णांक32_t val, uपूर्णांक32_t mask)
अणु
	amdgpu_ring_ग_लिखो(ring, VCE_CMD_REG_WAIT);
	amdgpu_ring_ग_लिखो(ring,	reg << 2);
	amdgpu_ring_ग_लिखो(ring, mask);
	amdgpu_ring_ग_लिखो(ring, val);
पूर्ण

अटल व्योम vce_v4_0_emit_vm_flush(काष्ठा amdgpu_ring *ring,
				   अचिन्हित पूर्णांक vmid, uपूर्णांक64_t pd_addr)
अणु
	काष्ठा amdgpu_vmhub *hub = &ring->adev->vmhub[ring->funcs->vmhub];

	pd_addr = amdgpu_gmc_emit_flush_gpu_tlb(ring, vmid, pd_addr);

	/* रुको क्रम reg ग_लिखोs */
	vce_v4_0_emit_reg_रुको(ring, hub->ctx0_ptb_addr_lo32 +
			       vmid * hub->ctx_addr_distance,
			       lower_32_bits(pd_addr), 0xffffffff);
पूर्ण

अटल व्योम vce_v4_0_emit_wreg(काष्ठा amdgpu_ring *ring,
			       uपूर्णांक32_t reg, uपूर्णांक32_t val)
अणु
	amdgpu_ring_ग_लिखो(ring, VCE_CMD_REG_WRITE);
	amdgpu_ring_ग_लिखो(ring,	reg << 2);
	amdgpu_ring_ग_लिखो(ring, val);
पूर्ण

अटल पूर्णांक vce_v4_0_set_पूर्णांकerrupt_state(काष्ठा amdgpu_device *adev,
					काष्ठा amdgpu_irq_src *source,
					अचिन्हित type,
					क्रमागत amdgpu_पूर्णांकerrupt_state state)
अणु
	uपूर्णांक32_t val = 0;

	अगर (!amdgpu_sriov_vf(adev)) अणु
		अगर (state == AMDGPU_IRQ_STATE_ENABLE)
			val |= VCE_SYS_INT_EN__VCE_SYS_INT_TRAP_INTERRUPT_EN_MASK;

		WREG32_P(SOC15_REG_OFFSET(VCE, 0, mmVCE_SYS_INT_EN), val,
				~VCE_SYS_INT_EN__VCE_SYS_INT_TRAP_INTERRUPT_EN_MASK);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक vce_v4_0_process_पूर्णांकerrupt(काष्ठा amdgpu_device *adev,
				      काष्ठा amdgpu_irq_src *source,
				      काष्ठा amdgpu_iv_entry *entry)
अणु
	DRM_DEBUG("IH: VCE\n");

	चयन (entry->src_data[0]) अणु
	हाल 0:
	हाल 1:
	हाल 2:
		amdgpu_fence_process(&adev->vce.ring[entry->src_data[0]]);
		अवरोध;
	शेष:
		DRM_ERROR("Unhandled interrupt: %d %d\n",
			  entry->src_id, entry->src_data[0]);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

स्थिर काष्ठा amd_ip_funcs vce_v4_0_ip_funcs = अणु
	.name = "vce_v4_0",
	.early_init = vce_v4_0_early_init,
	.late_init = शून्य,
	.sw_init = vce_v4_0_sw_init,
	.sw_fini = vce_v4_0_sw_fini,
	.hw_init = vce_v4_0_hw_init,
	.hw_fini = vce_v4_0_hw_fini,
	.suspend = vce_v4_0_suspend,
	.resume = vce_v4_0_resume,
	.is_idle = शून्य /* vce_v4_0_is_idle */,
	.रुको_क्रम_idle = शून्य /* vce_v4_0_रुको_क्रम_idle */,
	.check_soft_reset = शून्य /* vce_v4_0_check_soft_reset */,
	.pre_soft_reset = शून्य /* vce_v4_0_pre_soft_reset */,
	.soft_reset = शून्य /* vce_v4_0_soft_reset */,
	.post_soft_reset = शून्य /* vce_v4_0_post_soft_reset */,
	.set_घड़ीgating_state = vce_v4_0_set_घड़ीgating_state,
	.set_घातergating_state = vce_v4_0_set_घातergating_state,
पूर्ण;

अटल स्थिर काष्ठा amdgpu_ring_funcs vce_v4_0_ring_vm_funcs = अणु
	.type = AMDGPU_RING_TYPE_VCE,
	.align_mask = 0x3f,
	.nop = VCE_CMD_NO_OP,
	.support_64bit_ptrs = false,
	.no_user_fence = true,
	.vmhub = AMDGPU_MMHUB_0,
	.get_rptr = vce_v4_0_ring_get_rptr,
	.get_wptr = vce_v4_0_ring_get_wptr,
	.set_wptr = vce_v4_0_ring_set_wptr,
	.parse_cs = amdgpu_vce_ring_parse_cs_vm,
	.emit_frame_size =
		SOC15_FLUSH_GPU_TLB_NUM_WREG * 3 +
		SOC15_FLUSH_GPU_TLB_NUM_REG_WAIT * 4 +
		4 + /* vce_v4_0_emit_vm_flush */
		5 + 5 + /* amdgpu_vce_ring_emit_fence x2 vm fence */
		1, /* vce_v4_0_ring_insert_end */
	.emit_ib_size = 5, /* vce_v4_0_ring_emit_ib */
	.emit_ib = vce_v4_0_ring_emit_ib,
	.emit_vm_flush = vce_v4_0_emit_vm_flush,
	.emit_fence = vce_v4_0_ring_emit_fence,
	.test_ring = amdgpu_vce_ring_test_ring,
	.test_ib = amdgpu_vce_ring_test_ib,
	.insert_nop = amdgpu_ring_insert_nop,
	.insert_end = vce_v4_0_ring_insert_end,
	.pad_ib = amdgpu_ring_generic_pad_ib,
	.begin_use = amdgpu_vce_ring_begin_use,
	.end_use = amdgpu_vce_ring_end_use,
	.emit_wreg = vce_v4_0_emit_wreg,
	.emit_reg_रुको = vce_v4_0_emit_reg_रुको,
	.emit_reg_ग_लिखो_reg_रुको = amdgpu_ring_emit_reg_ग_लिखो_reg_रुको_helper,
पूर्ण;

अटल व्योम vce_v4_0_set_ring_funcs(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < adev->vce.num_rings; i++) अणु
		adev->vce.ring[i].funcs = &vce_v4_0_ring_vm_funcs;
		adev->vce.ring[i].me = i;
	पूर्ण
	DRM_INFO("VCE enabled in VM mode\n");
पूर्ण

अटल स्थिर काष्ठा amdgpu_irq_src_funcs vce_v4_0_irq_funcs = अणु
	.set = vce_v4_0_set_पूर्णांकerrupt_state,
	.process = vce_v4_0_process_पूर्णांकerrupt,
पूर्ण;

अटल व्योम vce_v4_0_set_irq_funcs(काष्ठा amdgpu_device *adev)
अणु
	adev->vce.irq.num_types = 1;
	adev->vce.irq.funcs = &vce_v4_0_irq_funcs;
पूर्ण;

स्थिर काष्ठा amdgpu_ip_block_version vce_v4_0_ip_block =
अणु
	.type = AMD_IP_BLOCK_TYPE_VCE,
	.major = 4,
	.minor = 0,
	.rev = 0,
	.funcs = &vce_v4_0_ip_funcs,
पूर्ण;
