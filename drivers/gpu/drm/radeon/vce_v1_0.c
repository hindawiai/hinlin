<शैली गुरु>
/*
 * Copyright 2013 Advanced Micro Devices, Inc.
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
 * Authors: Christian Kथघnig <christian.koenig@amd.com>
 */

#समावेश <linux/firmware.h>

#समावेश "radeon.h"
#समावेश "radeon_asic.h"
#समावेश "sid.h"
#समावेश "vce.h"

#घोषणा VCE_V1_0_FW_SIZE	(256 * 1024)
#घोषणा VCE_V1_0_STACK_SIZE	(64 * 1024)
#घोषणा VCE_V1_0_DATA_SIZE	(7808 * (RADEON_MAX_VCE_HANDLES + 1))

काष्ठा vce_v1_0_fw_signature
अणु
	पूर्णांक32_t off;
	uपूर्णांक32_t len;
	पूर्णांक32_t num;
	काष्ठा अणु
		uपूर्णांक32_t chip_id;
		uपूर्णांक32_t keyselect;
		uपूर्णांक32_t nonce[4];
		uपूर्णांक32_t sigval[4];
	पूर्ण val[8];
पूर्ण;

/**
 * vce_v1_0_get_rptr - get पढ़ो poपूर्णांकer
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ring: radeon_ring poपूर्णांकer
 *
 * Returns the current hardware पढ़ो poपूर्णांकer
 */
uपूर्णांक32_t vce_v1_0_get_rptr(काष्ठा radeon_device *rdev,
			   काष्ठा radeon_ring *ring)
अणु
	अगर (ring->idx == TN_RING_TYPE_VCE1_INDEX)
		वापस RREG32(VCE_RB_RPTR);
	अन्यथा
		वापस RREG32(VCE_RB_RPTR2);
पूर्ण

/**
 * vce_v1_0_get_wptr - get ग_लिखो poपूर्णांकer
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ring: radeon_ring poपूर्णांकer
 *
 * Returns the current hardware ग_लिखो poपूर्णांकer
 */
uपूर्णांक32_t vce_v1_0_get_wptr(काष्ठा radeon_device *rdev,
			   काष्ठा radeon_ring *ring)
अणु
	अगर (ring->idx == TN_RING_TYPE_VCE1_INDEX)
		वापस RREG32(VCE_RB_WPTR);
	अन्यथा
		वापस RREG32(VCE_RB_WPTR2);
पूर्ण

/**
 * vce_v1_0_set_wptr - set ग_लिखो poपूर्णांकer
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ring: radeon_ring poपूर्णांकer
 *
 * Commits the ग_लिखो poपूर्णांकer to the hardware
 */
व्योम vce_v1_0_set_wptr(काष्ठा radeon_device *rdev,
		       काष्ठा radeon_ring *ring)
अणु
	अगर (ring->idx == TN_RING_TYPE_VCE1_INDEX)
		WREG32(VCE_RB_WPTR, ring->wptr);
	अन्यथा
		WREG32(VCE_RB_WPTR2, ring->wptr);
पूर्ण

व्योम vce_v1_0_enable_mgcg(काष्ठा radeon_device *rdev, bool enable)
अणु
	u32 पंचांगp;

	अगर (enable && (rdev->cg_flags & RADEON_CG_SUPPORT_VCE_MGCG)) अणु
		पंचांगp = RREG32(VCE_CLOCK_GATING_A);
		पंचांगp |= CGC_DYN_CLOCK_MODE;
		WREG32(VCE_CLOCK_GATING_A, पंचांगp);

		पंचांगp = RREG32(VCE_UENC_CLOCK_GATING);
		पंचांगp &= ~0x1ff000;
		पंचांगp |= 0xff800000;
		WREG32(VCE_UENC_CLOCK_GATING, पंचांगp);

		पंचांगp = RREG32(VCE_UENC_REG_CLOCK_GATING);
		पंचांगp &= ~0x3ff;
		WREG32(VCE_UENC_REG_CLOCK_GATING, पंचांगp);
	पूर्ण अन्यथा अणु
		पंचांगp = RREG32(VCE_CLOCK_GATING_A);
		पंचांगp &= ~CGC_DYN_CLOCK_MODE;
		WREG32(VCE_CLOCK_GATING_A, पंचांगp);

		पंचांगp = RREG32(VCE_UENC_CLOCK_GATING);
		पंचांगp |= 0x1ff000;
		पंचांगp &= ~0xff800000;
		WREG32(VCE_UENC_CLOCK_GATING, पंचांगp);

		पंचांगp = RREG32(VCE_UENC_REG_CLOCK_GATING);
		पंचांगp |= 0x3ff;
		WREG32(VCE_UENC_REG_CLOCK_GATING, पंचांगp);
	पूर्ण
पूर्ण

अटल व्योम vce_v1_0_init_cg(काष्ठा radeon_device *rdev)
अणु
	u32 पंचांगp;

	पंचांगp = RREG32(VCE_CLOCK_GATING_A);
	पंचांगp |= CGC_DYN_CLOCK_MODE;
	WREG32(VCE_CLOCK_GATING_A, पंचांगp);

	पंचांगp = RREG32(VCE_CLOCK_GATING_B);
	पंचांगp |= 0x1e;
	पंचांगp &= ~0xe100e1;
	WREG32(VCE_CLOCK_GATING_B, पंचांगp);

	पंचांगp = RREG32(VCE_UENC_CLOCK_GATING);
	पंचांगp &= ~0xff9ff000;
	WREG32(VCE_UENC_CLOCK_GATING, पंचांगp);

	पंचांगp = RREG32(VCE_UENC_REG_CLOCK_GATING);
	पंचांगp &= ~0x3ff;
	WREG32(VCE_UENC_REG_CLOCK_GATING, पंचांगp);
पूर्ण

पूर्णांक vce_v1_0_load_fw(काष्ठा radeon_device *rdev, uपूर्णांक32_t *data)
अणु
	काष्ठा vce_v1_0_fw_signature *sign = (व्योम*)rdev->vce_fw->data;
	uपूर्णांक32_t chip_id;
	पूर्णांक i;

	चयन (rdev->family) अणु
	हाल CHIP_TAHITI:
		chip_id = 0x01000014;
		अवरोध;
	हाल CHIP_VERDE:
		chip_id = 0x01000015;
		अवरोध;
	हाल CHIP_PITCAIRN:
		chip_id = 0x01000016;
		अवरोध;
	हाल CHIP_ARUBA:
		chip_id = 0x01000017;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < le32_to_cpu(sign->num); ++i) अणु
		अगर (le32_to_cpu(sign->val[i].chip_id) == chip_id)
			अवरोध;
	पूर्ण

	अगर (i == le32_to_cpu(sign->num))
		वापस -EINVAL;

	data += (256 - 64) / 4;
	data[0] = sign->val[i].nonce[0];
	data[1] = sign->val[i].nonce[1];
	data[2] = sign->val[i].nonce[2];
	data[3] = sign->val[i].nonce[3];
	data[4] = cpu_to_le32(le32_to_cpu(sign->len) + 64);

	स_रखो(&data[5], 0, 44);
	स_नकल(&data[16], &sign[1], rdev->vce_fw->size - माप(*sign));

	data += (le32_to_cpu(sign->len) + 64) / 4;
	data[0] = sign->val[i].sigval[0];
	data[1] = sign->val[i].sigval[1];
	data[2] = sign->val[i].sigval[2];
	data[3] = sign->val[i].sigval[3];

	rdev->vce.keyselect = le32_to_cpu(sign->val[i].keyselect);

	वापस 0;
पूर्ण

अचिन्हित vce_v1_0_bo_size(काष्ठा radeon_device *rdev)
अणु
	WARN_ON(VCE_V1_0_FW_SIZE < rdev->vce_fw->size);
	वापस VCE_V1_0_FW_SIZE + VCE_V1_0_STACK_SIZE + VCE_V1_0_DATA_SIZE;
पूर्ण

पूर्णांक vce_v1_0_resume(काष्ठा radeon_device *rdev)
अणु
	uपूर्णांक64_t addr = rdev->vce.gpu_addr;
	uपूर्णांक32_t size;
	पूर्णांक i;

	WREG32_P(VCE_CLOCK_GATING_A, 0, ~(1 << 16));
	WREG32_P(VCE_UENC_CLOCK_GATING, 0x1FF000, ~0xFF9FF000);
	WREG32_P(VCE_UENC_REG_CLOCK_GATING, 0x3F, ~0x3F);
	WREG32(VCE_CLOCK_GATING_B, 0);

	WREG32_P(VCE_LMI_FW_PERIODIC_CTRL, 0x4, ~0x4);

	WREG32(VCE_LMI_CTRL, 0x00398000);
	WREG32_P(VCE_LMI_CACHE_CTRL, 0x0, ~0x1);
	WREG32(VCE_LMI_SWAP_CNTL, 0);
	WREG32(VCE_LMI_SWAP_CNTL1, 0);
	WREG32(VCE_LMI_VM_CTRL, 0);

	WREG32(VCE_VCPU_SCRATCH7, RADEON_MAX_VCE_HANDLES);

	addr += 256;
	size = VCE_V1_0_FW_SIZE;
	WREG32(VCE_VCPU_CACHE_OFFSET0, addr & 0x7fffffff);
	WREG32(VCE_VCPU_CACHE_SIZE0, size);

	addr += size;
	size = VCE_V1_0_STACK_SIZE;
	WREG32(VCE_VCPU_CACHE_OFFSET1, addr & 0x7fffffff);
	WREG32(VCE_VCPU_CACHE_SIZE1, size);

	addr += size;
	size = VCE_V1_0_DATA_SIZE;
	WREG32(VCE_VCPU_CACHE_OFFSET2, addr & 0x7fffffff);
	WREG32(VCE_VCPU_CACHE_SIZE2, size);

	WREG32_P(VCE_LMI_CTRL2, 0x0, ~0x100);

	WREG32(VCE_LMI_FW_START_KEYSEL, rdev->vce.keyselect);

	क्रम (i = 0; i < 10; ++i) अणु
		mdelay(10);
		अगर (RREG32(VCE_FW_REG_STATUS) & VCE_FW_REG_STATUS_DONE)
			अवरोध;
	पूर्ण

	अगर (i == 10)
		वापस -ETIMEDOUT;

	अगर (!(RREG32(VCE_FW_REG_STATUS) & VCE_FW_REG_STATUS_PASS))
		वापस -EINVAL;

	क्रम (i = 0; i < 10; ++i) अणु
		mdelay(10);
		अगर (!(RREG32(VCE_FW_REG_STATUS) & VCE_FW_REG_STATUS_BUSY))
			अवरोध;
	पूर्ण

	अगर (i == 10)
		वापस -ETIMEDOUT;

	vce_v1_0_init_cg(rdev);

	वापस 0;
पूर्ण

/**
 * vce_v1_0_start - start VCE block
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Setup and start the VCE block
 */
पूर्णांक vce_v1_0_start(काष्ठा radeon_device *rdev)
अणु
	काष्ठा radeon_ring *ring;
	पूर्णांक i, j, r;

	/* set BUSY flag */
	WREG32_P(VCE_STATUS, 1, ~1);

	ring = &rdev->ring[TN_RING_TYPE_VCE1_INDEX];
	WREG32(VCE_RB_RPTR, ring->wptr);
	WREG32(VCE_RB_WPTR, ring->wptr);
	WREG32(VCE_RB_BASE_LO, ring->gpu_addr);
	WREG32(VCE_RB_BASE_HI, upper_32_bits(ring->gpu_addr));
	WREG32(VCE_RB_SIZE, ring->ring_size / 4);

	ring = &rdev->ring[TN_RING_TYPE_VCE2_INDEX];
	WREG32(VCE_RB_RPTR2, ring->wptr);
	WREG32(VCE_RB_WPTR2, ring->wptr);
	WREG32(VCE_RB_BASE_LO2, ring->gpu_addr);
	WREG32(VCE_RB_BASE_HI2, upper_32_bits(ring->gpu_addr));
	WREG32(VCE_RB_SIZE2, ring->ring_size / 4);

	WREG32_P(VCE_VCPU_CNTL, VCE_CLK_EN, ~VCE_CLK_EN);

	WREG32_P(VCE_SOFT_RESET,
		 VCE_ECPU_SOFT_RESET |
		 VCE_FME_SOFT_RESET, ~(
		 VCE_ECPU_SOFT_RESET |
		 VCE_FME_SOFT_RESET));

	mdelay(100);

	WREG32_P(VCE_SOFT_RESET, 0, ~(
		 VCE_ECPU_SOFT_RESET |
		 VCE_FME_SOFT_RESET));

	क्रम (i = 0; i < 10; ++i) अणु
		uपूर्णांक32_t status;
		क्रम (j = 0; j < 100; ++j) अणु
			status = RREG32(VCE_STATUS);
			अगर (status & 2)
				अवरोध;
			mdelay(10);
		पूर्ण
		r = 0;
		अगर (status & 2)
			अवरोध;

		DRM_ERROR("VCE not responding, trying to reset the ECPU!!!\n");
		WREG32_P(VCE_SOFT_RESET, VCE_ECPU_SOFT_RESET, ~VCE_ECPU_SOFT_RESET);
		mdelay(10);
		WREG32_P(VCE_SOFT_RESET, 0, ~VCE_ECPU_SOFT_RESET);
		mdelay(10);
		r = -1;
	पूर्ण

	/* clear BUSY flag */
	WREG32_P(VCE_STATUS, 0, ~1);

	अगर (r) अणु
		DRM_ERROR("VCE not responding, giving up!!!\n");
		वापस r;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक vce_v1_0_init(काष्ठा radeon_device *rdev)
अणु
	काष्ठा radeon_ring *ring;
	पूर्णांक r;

	r = vce_v1_0_start(rdev);
	अगर (r)
		वापस r;

	ring = &rdev->ring[TN_RING_TYPE_VCE1_INDEX];
	ring->पढ़ोy = true;
	r = radeon_ring_test(rdev, TN_RING_TYPE_VCE1_INDEX, ring);
	अगर (r) अणु
		ring->पढ़ोy = false;
		वापस r;
	पूर्ण

	ring = &rdev->ring[TN_RING_TYPE_VCE2_INDEX];
	ring->पढ़ोy = true;
	r = radeon_ring_test(rdev, TN_RING_TYPE_VCE2_INDEX, ring);
	अगर (r) अणु
		ring->पढ़ोy = false;
		वापस r;
	पूर्ण

	DRM_INFO("VCE initialized successfully.\n");

	वापस 0;
पूर्ण
