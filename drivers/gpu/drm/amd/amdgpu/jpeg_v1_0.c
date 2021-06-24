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
#समावेश "amdgpu_jpeg.h"
#समावेश "soc15.h"
#समावेश "soc15d.h"
#समावेश "vcn_v1_0.h"
#समावेश "jpeg_v1_0.h"

#समावेश "vcn/vcn_1_0_offset.h"
#समावेश "vcn/vcn_1_0_sh_mask.h"

अटल व्योम jpeg_v1_0_set_dec_ring_funcs(काष्ठा amdgpu_device *adev);
अटल व्योम jpeg_v1_0_set_irq_funcs(काष्ठा amdgpu_device *adev);
अटल व्योम jpeg_v1_0_ring_begin_use(काष्ठा amdgpu_ring *ring);

अटल व्योम jpeg_v1_0_decode_ring_patch_wreg(काष्ठा amdgpu_ring *ring, uपूर्णांक32_t *ptr, uपूर्णांक32_t reg_offset, uपूर्णांक32_t val)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;
	ring->ring[(*ptr)++] = PACKETJ(SOC15_REG_OFFSET(JPEG, 0, mmUVD_JRBC_EXTERNAL_REG_BASE), 0, 0, PACKETJ_TYPE0);
	अगर (((reg_offset >= 0x1f800) && (reg_offset <= 0x21fff)) ||
		((reg_offset >= 0x1e000) && (reg_offset <= 0x1e1ff))) अणु
		ring->ring[(*ptr)++] = 0;
		ring->ring[(*ptr)++] = PACKETJ((reg_offset >> 2), 0, 0, PACKETJ_TYPE0);
	पूर्ण अन्यथा अणु
		ring->ring[(*ptr)++] = reg_offset;
		ring->ring[(*ptr)++] = PACKETJ(0, 0, 0, PACKETJ_TYPE0);
	पूर्ण
	ring->ring[(*ptr)++] = val;
पूर्ण

अटल व्योम jpeg_v1_0_decode_ring_set_patch_ring(काष्ठा amdgpu_ring *ring, uपूर्णांक32_t ptr)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	uपूर्णांक32_t reg, reg_offset, val, mask, i;

	// 1st: program mmUVD_LMI_JRBC_RB_MEM_RD_64BIT_BAR_LOW
	reg = SOC15_REG_OFFSET(JPEG, 0, mmUVD_LMI_JRBC_RB_MEM_RD_64BIT_BAR_LOW);
	reg_offset = (reg << 2);
	val = lower_32_bits(ring->gpu_addr);
	jpeg_v1_0_decode_ring_patch_wreg(ring, &ptr, reg_offset, val);

	// 2nd: program mmUVD_LMI_JRBC_RB_MEM_RD_64BIT_BAR_HIGH
	reg = SOC15_REG_OFFSET(JPEG, 0, mmUVD_LMI_JRBC_RB_MEM_RD_64BIT_BAR_HIGH);
	reg_offset = (reg << 2);
	val = upper_32_bits(ring->gpu_addr);
	jpeg_v1_0_decode_ring_patch_wreg(ring, &ptr, reg_offset, val);

	// 3rd to 5th: issue MEM_READ commands
	क्रम (i = 0; i <= 2; i++) अणु
		ring->ring[ptr++] = PACKETJ(0, 0, 0, PACKETJ_TYPE2);
		ring->ring[ptr++] = 0;
	पूर्ण

	// 6th: program mmUVD_JRBC_RB_CNTL रेजिस्टर to enable NO_FETCH and RPTR ग_लिखो ability
	reg = SOC15_REG_OFFSET(JPEG, 0, mmUVD_JRBC_RB_CNTL);
	reg_offset = (reg << 2);
	val = 0x13;
	jpeg_v1_0_decode_ring_patch_wreg(ring, &ptr, reg_offset, val);

	// 7th: program mmUVD_JRBC_RB_REF_DATA
	reg = SOC15_REG_OFFSET(JPEG, 0, mmUVD_JRBC_RB_REF_DATA);
	reg_offset = (reg << 2);
	val = 0x1;
	jpeg_v1_0_decode_ring_patch_wreg(ring, &ptr, reg_offset, val);

	// 8th: issue conditional रेजिस्टर पढ़ो mmUVD_JRBC_RB_CNTL
	reg = SOC15_REG_OFFSET(JPEG, 0, mmUVD_JRBC_RB_CNTL);
	reg_offset = (reg << 2);
	val = 0x1;
	mask = 0x1;

	ring->ring[ptr++] = PACKETJ(SOC15_REG_OFFSET(JPEG, 0, mmUVD_JRBC_RB_COND_RD_TIMER), 0, 0, PACKETJ_TYPE0);
	ring->ring[ptr++] = 0x01400200;
	ring->ring[ptr++] = PACKETJ(SOC15_REG_OFFSET(JPEG, 0, mmUVD_JRBC_RB_REF_DATA), 0, 0, PACKETJ_TYPE0);
	ring->ring[ptr++] = val;
	ring->ring[ptr++] = PACKETJ(SOC15_REG_OFFSET(JPEG, 0, mmUVD_JRBC_EXTERNAL_REG_BASE), 0, 0, PACKETJ_TYPE0);
	अगर (((reg_offset >= 0x1f800) && (reg_offset <= 0x21fff)) ||
		((reg_offset >= 0x1e000) && (reg_offset <= 0x1e1ff))) अणु
		ring->ring[ptr++] = 0;
		ring->ring[ptr++] = PACKETJ((reg_offset >> 2), 0, 0, PACKETJ_TYPE3);
	पूर्ण अन्यथा अणु
		ring->ring[ptr++] = reg_offset;
		ring->ring[ptr++] = PACKETJ(0, 0, 0, PACKETJ_TYPE3);
	पूर्ण
	ring->ring[ptr++] = mask;

	//9th to 21st: insert no-op
	क्रम (i = 0; i <= 12; i++) अणु
		ring->ring[ptr++] = PACKETJ(0, 0, 0, PACKETJ_TYPE6);
		ring->ring[ptr++] = 0;
	पूर्ण

	//22nd: reset mmUVD_JRBC_RB_RPTR
	reg = SOC15_REG_OFFSET(JPEG, 0, mmUVD_JRBC_RB_RPTR);
	reg_offset = (reg << 2);
	val = 0;
	jpeg_v1_0_decode_ring_patch_wreg(ring, &ptr, reg_offset, val);

	//23rd: program mmUVD_JRBC_RB_CNTL to disable no_fetch
	reg = SOC15_REG_OFFSET(JPEG, 0, mmUVD_JRBC_RB_CNTL);
	reg_offset = (reg << 2);
	val = 0x12;
	jpeg_v1_0_decode_ring_patch_wreg(ring, &ptr, reg_offset, val);
पूर्ण

/**
 * jpeg_v1_0_decode_ring_get_rptr - get पढ़ो poपूर्णांकer
 *
 * @ring: amdgpu_ring poपूर्णांकer
 *
 * Returns the current hardware पढ़ो poपूर्णांकer
 */
अटल uपूर्णांक64_t jpeg_v1_0_decode_ring_get_rptr(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	वापस RREG32_SOC15(JPEG, 0, mmUVD_JRBC_RB_RPTR);
पूर्ण

/**
 * jpeg_v1_0_decode_ring_get_wptr - get ग_लिखो poपूर्णांकer
 *
 * @ring: amdgpu_ring poपूर्णांकer
 *
 * Returns the current hardware ग_लिखो poपूर्णांकer
 */
अटल uपूर्णांक64_t jpeg_v1_0_decode_ring_get_wptr(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	वापस RREG32_SOC15(JPEG, 0, mmUVD_JRBC_RB_WPTR);
पूर्ण

/**
 * jpeg_v1_0_decode_ring_set_wptr - set ग_लिखो poपूर्णांकer
 *
 * @ring: amdgpu_ring poपूर्णांकer
 *
 * Commits the ग_लिखो poपूर्णांकer to the hardware
 */
अटल व्योम jpeg_v1_0_decode_ring_set_wptr(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	WREG32_SOC15(JPEG, 0, mmUVD_JRBC_RB_WPTR, lower_32_bits(ring->wptr));
पूर्ण

/**
 * jpeg_v1_0_decode_ring_insert_start - insert a start command
 *
 * @ring: amdgpu_ring poपूर्णांकer
 *
 * Write a start command to the ring.
 */
अटल व्योम jpeg_v1_0_decode_ring_insert_start(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	amdgpu_ring_ग_लिखो(ring,
		PACKETJ(SOC15_REG_OFFSET(JPEG, 0, mmUVD_JRBC_EXTERNAL_REG_BASE), 0, 0, PACKETJ_TYPE0));
	amdgpu_ring_ग_लिखो(ring, 0x68e04);

	amdgpu_ring_ग_लिखो(ring, PACKETJ(0, 0, 0, PACKETJ_TYPE0));
	amdgpu_ring_ग_लिखो(ring, 0x80010000);
पूर्ण

/**
 * jpeg_v1_0_decode_ring_insert_end - insert a end command
 *
 * @ring: amdgpu_ring poपूर्णांकer
 *
 * Write a end command to the ring.
 */
अटल व्योम jpeg_v1_0_decode_ring_insert_end(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	amdgpu_ring_ग_लिखो(ring,
		PACKETJ(SOC15_REG_OFFSET(JPEG, 0, mmUVD_JRBC_EXTERNAL_REG_BASE), 0, 0, PACKETJ_TYPE0));
	amdgpu_ring_ग_लिखो(ring, 0x68e04);

	amdgpu_ring_ग_लिखो(ring, PACKETJ(0, 0, 0, PACKETJ_TYPE0));
	amdgpu_ring_ग_लिखो(ring, 0x00010000);
पूर्ण

/**
 * jpeg_v1_0_decode_ring_emit_fence - emit an fence & trap command
 *
 * @ring: amdgpu_ring poपूर्णांकer
 * @addr: address
 * @seq: sequence number
 * @flags: fence related flags
 *
 * Write a fence and a trap command to the ring.
 */
अटल व्योम jpeg_v1_0_decode_ring_emit_fence(काष्ठा amdgpu_ring *ring, u64 addr, u64 seq,
				     अचिन्हित flags)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	WARN_ON(flags & AMDGPU_FENCE_FLAG_64BIT);

	amdgpu_ring_ग_लिखो(ring,
		PACKETJ(SOC15_REG_OFFSET(JPEG, 0, mmUVD_JPEG_GPCOM_DATA0), 0, 0, PACKETJ_TYPE0));
	amdgpu_ring_ग_लिखो(ring, seq);

	amdgpu_ring_ग_लिखो(ring,
		PACKETJ(SOC15_REG_OFFSET(JPEG, 0, mmUVD_JPEG_GPCOM_DATA1), 0, 0, PACKETJ_TYPE0));
	amdgpu_ring_ग_लिखो(ring, seq);

	amdgpu_ring_ग_लिखो(ring,
		PACKETJ(SOC15_REG_OFFSET(JPEG, 0, mmUVD_LMI_JRBC_RB_MEM_WR_64BIT_BAR_LOW), 0, 0, PACKETJ_TYPE0));
	amdgpu_ring_ग_लिखो(ring, lower_32_bits(addr));

	amdgpu_ring_ग_लिखो(ring,
		PACKETJ(SOC15_REG_OFFSET(JPEG, 0, mmUVD_LMI_JRBC_RB_MEM_WR_64BIT_BAR_HIGH), 0, 0, PACKETJ_TYPE0));
	amdgpu_ring_ग_लिखो(ring, upper_32_bits(addr));

	amdgpu_ring_ग_लिखो(ring,
		PACKETJ(SOC15_REG_OFFSET(JPEG, 0, mmUVD_JPEG_GPCOM_CMD), 0, 0, PACKETJ_TYPE0));
	amdgpu_ring_ग_लिखो(ring, 0x8);

	amdgpu_ring_ग_लिखो(ring,
		PACKETJ(SOC15_REG_OFFSET(JPEG, 0, mmUVD_JPEG_GPCOM_CMD), 0, PACKETJ_CONDITION_CHECK0, PACKETJ_TYPE4));
	amdgpu_ring_ग_लिखो(ring, 0);

	amdgpu_ring_ग_लिखो(ring,
		PACKETJ(SOC15_REG_OFFSET(JPEG, 0, mmUVD_JRBC_RB_COND_RD_TIMER), 0, 0, PACKETJ_TYPE0));
	amdgpu_ring_ग_लिखो(ring, 0x01400200);

	amdgpu_ring_ग_लिखो(ring,
		PACKETJ(SOC15_REG_OFFSET(JPEG, 0, mmUVD_JRBC_RB_REF_DATA), 0, 0, PACKETJ_TYPE0));
	amdgpu_ring_ग_लिखो(ring, seq);

	amdgpu_ring_ग_लिखो(ring,
		PACKETJ(SOC15_REG_OFFSET(JPEG, 0, mmUVD_LMI_JRBC_RB_MEM_RD_64BIT_BAR_LOW), 0, 0, PACKETJ_TYPE0));
	amdgpu_ring_ग_लिखो(ring, lower_32_bits(addr));

	amdgpu_ring_ग_लिखो(ring,
		PACKETJ(SOC15_REG_OFFSET(JPEG, 0, mmUVD_LMI_JRBC_RB_MEM_RD_64BIT_BAR_HIGH), 0, 0, PACKETJ_TYPE0));
	amdgpu_ring_ग_लिखो(ring, upper_32_bits(addr));

	amdgpu_ring_ग_लिखो(ring,
		PACKETJ(0, 0, PACKETJ_CONDITION_CHECK3, PACKETJ_TYPE2));
	amdgpu_ring_ग_लिखो(ring, 0xffffffff);

	amdgpu_ring_ग_लिखो(ring,
		PACKETJ(SOC15_REG_OFFSET(JPEG, 0, mmUVD_JRBC_EXTERNAL_REG_BASE), 0, 0, PACKETJ_TYPE0));
	amdgpu_ring_ग_लिखो(ring, 0x3fbc);

	amdgpu_ring_ग_लिखो(ring,
		PACKETJ(0, 0, 0, PACKETJ_TYPE0));
	amdgpu_ring_ग_लिखो(ring, 0x1);

	/* emit trap */
	amdgpu_ring_ग_लिखो(ring, PACKETJ(0, 0, 0, PACKETJ_TYPE7));
	amdgpu_ring_ग_लिखो(ring, 0);
पूर्ण

/**
 * jpeg_v1_0_decode_ring_emit_ib - execute indirect buffer
 *
 * @ring: amdgpu_ring poपूर्णांकer
 * @job: job to retrieve vmid from
 * @ib: indirect buffer to execute
 * @flags: unused
 *
 * Write ring commands to execute the indirect buffer.
 */
अटल व्योम jpeg_v1_0_decode_ring_emit_ib(काष्ठा amdgpu_ring *ring,
					काष्ठा amdgpu_job *job,
					काष्ठा amdgpu_ib *ib,
					uपूर्णांक32_t flags)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;
	अचिन्हित vmid = AMDGPU_JOB_GET_VMID(job);

	amdgpu_ring_ग_लिखो(ring,
		PACKETJ(SOC15_REG_OFFSET(JPEG, 0, mmUVD_LMI_JRBC_IB_VMID), 0, 0, PACKETJ_TYPE0));
	amdgpu_ring_ग_लिखो(ring, (vmid | (vmid << 4)));

	amdgpu_ring_ग_लिखो(ring,
		PACKETJ(SOC15_REG_OFFSET(JPEG, 0, mmUVD_LMI_JPEG_VMID), 0, 0, PACKETJ_TYPE0));
	amdgpu_ring_ग_लिखो(ring, (vmid | (vmid << 4)));

	amdgpu_ring_ग_लिखो(ring,
		PACKETJ(SOC15_REG_OFFSET(JPEG, 0, mmUVD_LMI_JRBC_IB_64BIT_BAR_LOW), 0, 0, PACKETJ_TYPE0));
	amdgpu_ring_ग_लिखो(ring, lower_32_bits(ib->gpu_addr));

	amdgpu_ring_ग_लिखो(ring,
		PACKETJ(SOC15_REG_OFFSET(JPEG, 0, mmUVD_LMI_JRBC_IB_64BIT_BAR_HIGH), 0, 0, PACKETJ_TYPE0));
	amdgpu_ring_ग_लिखो(ring, upper_32_bits(ib->gpu_addr));

	amdgpu_ring_ग_लिखो(ring,
		PACKETJ(SOC15_REG_OFFSET(JPEG, 0, mmUVD_JRBC_IB_SIZE), 0, 0, PACKETJ_TYPE0));
	amdgpu_ring_ग_लिखो(ring, ib->length_dw);

	amdgpu_ring_ग_लिखो(ring,
		PACKETJ(SOC15_REG_OFFSET(JPEG, 0, mmUVD_LMI_JRBC_RB_MEM_RD_64BIT_BAR_LOW), 0, 0, PACKETJ_TYPE0));
	amdgpu_ring_ग_लिखो(ring, lower_32_bits(ring->gpu_addr));

	amdgpu_ring_ग_लिखो(ring,
		PACKETJ(SOC15_REG_OFFSET(JPEG, 0, mmUVD_LMI_JRBC_RB_MEM_RD_64BIT_BAR_HIGH), 0, 0, PACKETJ_TYPE0));
	amdgpu_ring_ग_लिखो(ring, upper_32_bits(ring->gpu_addr));

	amdgpu_ring_ग_लिखो(ring,
		PACKETJ(0, 0, PACKETJ_CONDITION_CHECK0, PACKETJ_TYPE2));
	amdgpu_ring_ग_लिखो(ring, 0);

	amdgpu_ring_ग_लिखो(ring,
		PACKETJ(SOC15_REG_OFFSET(JPEG, 0, mmUVD_JRBC_RB_COND_RD_TIMER), 0, 0, PACKETJ_TYPE0));
	amdgpu_ring_ग_लिखो(ring, 0x01400200);

	amdgpu_ring_ग_लिखो(ring,
		PACKETJ(SOC15_REG_OFFSET(JPEG, 0, mmUVD_JRBC_RB_REF_DATA), 0, 0, PACKETJ_TYPE0));
	amdgpu_ring_ग_लिखो(ring, 0x2);

	amdgpu_ring_ग_लिखो(ring,
		PACKETJ(SOC15_REG_OFFSET(JPEG, 0, mmUVD_JRBC_STATUS), 0, PACKETJ_CONDITION_CHECK3, PACKETJ_TYPE3));
	amdgpu_ring_ग_लिखो(ring, 0x2);
पूर्ण

अटल व्योम jpeg_v1_0_decode_ring_emit_reg_रुको(काष्ठा amdgpu_ring *ring,
					    uपूर्णांक32_t reg, uपूर्णांक32_t val,
					    uपूर्णांक32_t mask)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;
	uपूर्णांक32_t reg_offset = (reg << 2);

	amdgpu_ring_ग_लिखो(ring,
		PACKETJ(SOC15_REG_OFFSET(JPEG, 0, mmUVD_JRBC_RB_COND_RD_TIMER), 0, 0, PACKETJ_TYPE0));
	amdgpu_ring_ग_लिखो(ring, 0x01400200);

	amdgpu_ring_ग_लिखो(ring,
		PACKETJ(SOC15_REG_OFFSET(JPEG, 0, mmUVD_JRBC_RB_REF_DATA), 0, 0, PACKETJ_TYPE0));
	amdgpu_ring_ग_लिखो(ring, val);

	amdgpu_ring_ग_लिखो(ring,
		PACKETJ(SOC15_REG_OFFSET(JPEG, 0, mmUVD_JRBC_EXTERNAL_REG_BASE), 0, 0, PACKETJ_TYPE0));
	अगर (((reg_offset >= 0x1f800) && (reg_offset <= 0x21fff)) ||
		((reg_offset >= 0x1e000) && (reg_offset <= 0x1e1ff))) अणु
		amdgpu_ring_ग_लिखो(ring, 0);
		amdgpu_ring_ग_लिखो(ring,
			PACKETJ((reg_offset >> 2), 0, 0, PACKETJ_TYPE3));
	पूर्ण अन्यथा अणु
		amdgpu_ring_ग_लिखो(ring, reg_offset);
		amdgpu_ring_ग_लिखो(ring,
			PACKETJ(0, 0, 0, PACKETJ_TYPE3));
	पूर्ण
	amdgpu_ring_ग_लिखो(ring, mask);
पूर्ण

अटल व्योम jpeg_v1_0_decode_ring_emit_vm_flush(काष्ठा amdgpu_ring *ring,
		अचिन्हित vmid, uपूर्णांक64_t pd_addr)
अणु
	काष्ठा amdgpu_vmhub *hub = &ring->adev->vmhub[ring->funcs->vmhub];
	uपूर्णांक32_t data0, data1, mask;

	pd_addr = amdgpu_gmc_emit_flush_gpu_tlb(ring, vmid, pd_addr);

	/* रुको क्रम रेजिस्टर ग_लिखो */
	data0 = hub->ctx0_ptb_addr_lo32 + vmid * hub->ctx_addr_distance;
	data1 = lower_32_bits(pd_addr);
	mask = 0xffffffff;
	jpeg_v1_0_decode_ring_emit_reg_रुको(ring, data0, data1, mask);
पूर्ण

अटल व्योम jpeg_v1_0_decode_ring_emit_wreg(काष्ठा amdgpu_ring *ring,
					uपूर्णांक32_t reg, uपूर्णांक32_t val)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;
	uपूर्णांक32_t reg_offset = (reg << 2);

	amdgpu_ring_ग_लिखो(ring,
		PACKETJ(SOC15_REG_OFFSET(JPEG, 0, mmUVD_JRBC_EXTERNAL_REG_BASE), 0, 0, PACKETJ_TYPE0));
	अगर (((reg_offset >= 0x1f800) && (reg_offset <= 0x21fff)) ||
			((reg_offset >= 0x1e000) && (reg_offset <= 0x1e1ff))) अणु
		amdgpu_ring_ग_लिखो(ring, 0);
		amdgpu_ring_ग_लिखो(ring,
			PACKETJ((reg_offset >> 2), 0, 0, PACKETJ_TYPE0));
	पूर्ण अन्यथा अणु
		amdgpu_ring_ग_लिखो(ring, reg_offset);
		amdgpu_ring_ग_लिखो(ring,
			PACKETJ(0, 0, 0, PACKETJ_TYPE0));
	पूर्ण
	amdgpu_ring_ग_लिखो(ring, val);
पूर्ण

अटल व्योम jpeg_v1_0_decode_ring_nop(काष्ठा amdgpu_ring *ring, uपूर्णांक32_t count)
अणु
	पूर्णांक i;

	WARN_ON(ring->wptr % 2 || count % 2);

	क्रम (i = 0; i < count / 2; i++) अणु
		amdgpu_ring_ग_लिखो(ring, PACKETJ(0, 0, 0, PACKETJ_TYPE6));
		amdgpu_ring_ग_लिखो(ring, 0);
	पूर्ण
पूर्ण

अटल पूर्णांक jpeg_v1_0_set_पूर्णांकerrupt_state(काष्ठा amdgpu_device *adev,
					काष्ठा amdgpu_irq_src *source,
					अचिन्हित type,
					क्रमागत amdgpu_पूर्णांकerrupt_state state)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक jpeg_v1_0_process_पूर्णांकerrupt(काष्ठा amdgpu_device *adev,
				      काष्ठा amdgpu_irq_src *source,
				      काष्ठा amdgpu_iv_entry *entry)
अणु
	DRM_DEBUG("IH: JPEG decode TRAP\n");

	चयन (entry->src_id) अणु
	हाल 126:
		amdgpu_fence_process(&adev->jpeg.inst->ring_dec);
		अवरोध;
	शेष:
		DRM_ERROR("Unhandled interrupt: %d %d\n",
			  entry->src_id, entry->src_data[0]);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * jpeg_v1_0_early_init - set function poपूर्णांकers
 *
 * @handle: amdgpu_device poपूर्णांकer
 *
 * Set ring and irq function poपूर्णांकers
 */
पूर्णांक jpeg_v1_0_early_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	adev->jpeg.num_jpeg_inst = 1;

	jpeg_v1_0_set_dec_ring_funcs(adev);
	jpeg_v1_0_set_irq_funcs(adev);

	वापस 0;
पूर्ण

/**
 * jpeg_v1_0_sw_init - sw init क्रम JPEG block
 *
 * @handle: amdgpu_device poपूर्णांकer
 *
 */
पूर्णांक jpeg_v1_0_sw_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	काष्ठा amdgpu_ring *ring;
	पूर्णांक r;

	/* JPEG TRAP */
	r = amdgpu_irq_add_id(adev, SOC15_IH_CLIENTID_VCN, 126, &adev->jpeg.inst->irq);
	अगर (r)
		वापस r;

	ring = &adev->jpeg.inst->ring_dec;
	प्र_लिखो(ring->name, "jpeg_dec");
	r = amdgpu_ring_init(adev, ring, 512, &adev->jpeg.inst->irq,
			     0, AMDGPU_RING_PRIO_DEFAULT, शून्य);
	अगर (r)
		वापस r;

	adev->jpeg.पूर्णांकernal.jpeg_pitch = adev->jpeg.inst->बाह्यal.jpeg_pitch =
		SOC15_REG_OFFSET(JPEG, 0, mmUVD_JPEG_PITCH);

	वापस 0;
पूर्ण

/**
 * jpeg_v1_0_sw_fini - sw fini क्रम JPEG block
 *
 * @handle: amdgpu_device poपूर्णांकer
 *
 * JPEG मुक्त up sw allocation
 */
व्योम jpeg_v1_0_sw_fini(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	amdgpu_ring_fini(&adev->jpeg.inst[0].ring_dec);
पूर्ण

/**
 * jpeg_v1_0_start - start JPEG block
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @mode: SPG or DPG mode
 *
 * Setup and start the JPEG block
 */
व्योम jpeg_v1_0_start(काष्ठा amdgpu_device *adev, पूर्णांक mode)
अणु
	काष्ठा amdgpu_ring *ring = &adev->jpeg.inst->ring_dec;

	अगर (mode == 0) अणु
		WREG32_SOC15(JPEG, 0, mmUVD_LMI_JRBC_RB_VMID, 0);
		WREG32_SOC15(JPEG, 0, mmUVD_JRBC_RB_CNTL, UVD_JRBC_RB_CNTL__RB_NO_FETCH_MASK |
				UVD_JRBC_RB_CNTL__RB_RPTR_WR_EN_MASK);
		WREG32_SOC15(JPEG, 0, mmUVD_LMI_JRBC_RB_64BIT_BAR_LOW, lower_32_bits(ring->gpu_addr));
		WREG32_SOC15(JPEG, 0, mmUVD_LMI_JRBC_RB_64BIT_BAR_HIGH, upper_32_bits(ring->gpu_addr));
		WREG32_SOC15(JPEG, 0, mmUVD_JRBC_RB_RPTR, 0);
		WREG32_SOC15(JPEG, 0, mmUVD_JRBC_RB_WPTR, 0);
		WREG32_SOC15(JPEG, 0, mmUVD_JRBC_RB_CNTL, UVD_JRBC_RB_CNTL__RB_RPTR_WR_EN_MASK);
	पूर्ण

	/* initialize wptr */
	ring->wptr = RREG32_SOC15(JPEG, 0, mmUVD_JRBC_RB_WPTR);

	/* copy patch commands to the jpeg ring */
	jpeg_v1_0_decode_ring_set_patch_ring(ring,
		(ring->wptr + ring->max_dw * amdgpu_sched_hw_submission));
पूर्ण

अटल स्थिर काष्ठा amdgpu_ring_funcs jpeg_v1_0_decode_ring_vm_funcs = अणु
	.type = AMDGPU_RING_TYPE_VCN_JPEG,
	.align_mask = 0xf,
	.nop = PACKET0(0x81ff, 0),
	.support_64bit_ptrs = false,
	.no_user_fence = true,
	.vmhub = AMDGPU_MMHUB_0,
	.extra_dw = 64,
	.get_rptr = jpeg_v1_0_decode_ring_get_rptr,
	.get_wptr = jpeg_v1_0_decode_ring_get_wptr,
	.set_wptr = jpeg_v1_0_decode_ring_set_wptr,
	.emit_frame_size =
		6 + 6 + /* hdp invalidate / flush */
		SOC15_FLUSH_GPU_TLB_NUM_WREG * 6 +
		SOC15_FLUSH_GPU_TLB_NUM_REG_WAIT * 8 +
		8 + /* jpeg_v1_0_decode_ring_emit_vm_flush */
		26 + 26 + /* jpeg_v1_0_decode_ring_emit_fence x2 vm fence */
		6,
	.emit_ib_size = 22, /* jpeg_v1_0_decode_ring_emit_ib */
	.emit_ib = jpeg_v1_0_decode_ring_emit_ib,
	.emit_fence = jpeg_v1_0_decode_ring_emit_fence,
	.emit_vm_flush = jpeg_v1_0_decode_ring_emit_vm_flush,
	.test_ring = amdgpu_jpeg_dec_ring_test_ring,
	.test_ib = amdgpu_jpeg_dec_ring_test_ib,
	.insert_nop = jpeg_v1_0_decode_ring_nop,
	.insert_start = jpeg_v1_0_decode_ring_insert_start,
	.insert_end = jpeg_v1_0_decode_ring_insert_end,
	.pad_ib = amdgpu_ring_generic_pad_ib,
	.begin_use = jpeg_v1_0_ring_begin_use,
	.end_use = vcn_v1_0_ring_end_use,
	.emit_wreg = jpeg_v1_0_decode_ring_emit_wreg,
	.emit_reg_रुको = jpeg_v1_0_decode_ring_emit_reg_रुको,
	.emit_reg_ग_लिखो_reg_रुको = amdgpu_ring_emit_reg_ग_लिखो_reg_रुको_helper,
पूर्ण;

अटल व्योम jpeg_v1_0_set_dec_ring_funcs(काष्ठा amdgpu_device *adev)
अणु
	adev->jpeg.inst->ring_dec.funcs = &jpeg_v1_0_decode_ring_vm_funcs;
	DRM_INFO("JPEG decode is enabled in VM mode\n");
पूर्ण

अटल स्थिर काष्ठा amdgpu_irq_src_funcs jpeg_v1_0_irq_funcs = अणु
	.set = jpeg_v1_0_set_पूर्णांकerrupt_state,
	.process = jpeg_v1_0_process_पूर्णांकerrupt,
पूर्ण;

अटल व्योम jpeg_v1_0_set_irq_funcs(काष्ठा amdgpu_device *adev)
अणु
	adev->jpeg.inst->irq.funcs = &jpeg_v1_0_irq_funcs;
पूर्ण

अटल व्योम jpeg_v1_0_ring_begin_use(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा	amdgpu_device *adev = ring->adev;
	bool	set_घड़ीs = !cancel_delayed_work_sync(&adev->vcn.idle_work);
	पूर्णांक		cnt = 0;

	mutex_lock(&adev->vcn.vcn1_jpeg1_workaround);

	अगर (amdgpu_fence_रुको_empty(&adev->vcn.inst->ring_dec))
		DRM_ERROR("JPEG dec: vcn dec ring may not be empty\n");

	क्रम (cnt = 0; cnt < adev->vcn.num_enc_rings; cnt++) अणु
		अगर (amdgpu_fence_रुको_empty(&adev->vcn.inst->ring_enc[cnt]))
			DRM_ERROR("JPEG dec: vcn enc ring[%d] may not be empty\n", cnt);
	पूर्ण

	vcn_v1_0_set_pg_क्रम_begin_use(ring, set_घड़ीs);
पूर्ण
