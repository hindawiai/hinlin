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
#समावेश "cikd.h"
#समावेश "vce.h"

#घोषणा VCE_V2_0_FW_SIZE	(256 * 1024)
#घोषणा VCE_V2_0_STACK_SIZE	(64 * 1024)
#घोषणा VCE_V2_0_DATA_SIZE	(23552 * RADEON_MAX_VCE_HANDLES)

अटल व्योम vce_v2_0_set_sw_cg(काष्ठा radeon_device *rdev, bool gated)
अणु
	u32 पंचांगp;

	अगर (gated) अणु
		पंचांगp = RREG32(VCE_CLOCK_GATING_B);
		पंचांगp |= 0xe70000;
		WREG32(VCE_CLOCK_GATING_B, पंचांगp);

		पंचांगp = RREG32(VCE_UENC_CLOCK_GATING);
		पंचांगp |= 0xff000000;
		WREG32(VCE_UENC_CLOCK_GATING, पंचांगp);

		पंचांगp = RREG32(VCE_UENC_REG_CLOCK_GATING);
		पंचांगp &= ~0x3fc;
		WREG32(VCE_UENC_REG_CLOCK_GATING, पंचांगp);

		WREG32(VCE_CGTT_CLK_OVERRIDE, 0);
	पूर्ण अन्यथा अणु
		पंचांगp = RREG32(VCE_CLOCK_GATING_B);
		पंचांगp |= 0xe7;
		पंचांगp &= ~0xe70000;
		WREG32(VCE_CLOCK_GATING_B, पंचांगp);

		पंचांगp = RREG32(VCE_UENC_CLOCK_GATING);
		पंचांगp |= 0x1fe000;
		पंचांगp &= ~0xff000000;
		WREG32(VCE_UENC_CLOCK_GATING, पंचांगp);

		पंचांगp = RREG32(VCE_UENC_REG_CLOCK_GATING);
		पंचांगp |= 0x3fc;
		WREG32(VCE_UENC_REG_CLOCK_GATING, पंचांगp);
	पूर्ण
पूर्ण

अटल व्योम vce_v2_0_set_dyn_cg(काष्ठा radeon_device *rdev, bool gated)
अणु
	u32 orig, पंचांगp;

	पंचांगp = RREG32(VCE_CLOCK_GATING_B);
	पंचांगp &= ~0x00060006;
	अगर (gated) अणु
		पंचांगp |= 0xe10000;
	पूर्ण अन्यथा अणु
		पंचांगp |= 0xe1;
		पंचांगp &= ~0xe10000;
	पूर्ण
	WREG32(VCE_CLOCK_GATING_B, पंचांगp);

	orig = पंचांगp = RREG32(VCE_UENC_CLOCK_GATING);
	पंचांगp &= ~0x1fe000;
	पंचांगp &= ~0xff000000;
	अगर (पंचांगp != orig)
		WREG32(VCE_UENC_CLOCK_GATING, पंचांगp);

	orig = पंचांगp = RREG32(VCE_UENC_REG_CLOCK_GATING);
	पंचांगp &= ~0x3fc;
	अगर (पंचांगp != orig)
		WREG32(VCE_UENC_REG_CLOCK_GATING, पंचांगp);

	अगर (gated)
		WREG32(VCE_CGTT_CLK_OVERRIDE, 0);
पूर्ण

अटल व्योम vce_v2_0_disable_cg(काष्ठा radeon_device *rdev)
अणु
	WREG32(VCE_CGTT_CLK_OVERRIDE, 7);
पूर्ण

/*
 * Local variable sw_cg is used क्रम debugging purposes, in हाल we
 * ran पूर्णांकo problems with dynamic घड़ी gating. Don't हटाओ it.
 */
व्योम vce_v2_0_enable_mgcg(काष्ठा radeon_device *rdev, bool enable)
अणु
	bool sw_cg = false;

	अगर (enable && (rdev->cg_flags & RADEON_CG_SUPPORT_VCE_MGCG)) अणु
		अगर (sw_cg)
			vce_v2_0_set_sw_cg(rdev, true);
		अन्यथा
			vce_v2_0_set_dyn_cg(rdev, true);
	पूर्ण अन्यथा अणु
		vce_v2_0_disable_cg(rdev);

		अगर (sw_cg)
			vce_v2_0_set_sw_cg(rdev, false);
		अन्यथा
			vce_v2_0_set_dyn_cg(rdev, false);
	पूर्ण
पूर्ण

अटल व्योम vce_v2_0_init_cg(काष्ठा radeon_device *rdev)
अणु
	u32 पंचांगp;

	पंचांगp = RREG32(VCE_CLOCK_GATING_A);
	पंचांगp &= ~(CGC_CLK_GATE_DLY_TIMER_MASK | CGC_CLK_GATER_OFF_DLY_TIMER_MASK);
	पंचांगp |= (CGC_CLK_GATE_DLY_TIMER(0) | CGC_CLK_GATER_OFF_DLY_TIMER(4));
	पंचांगp |= CGC_UENC_WAIT_AWAKE;
	WREG32(VCE_CLOCK_GATING_A, पंचांगp);

	पंचांगp = RREG32(VCE_UENC_CLOCK_GATING);
	पंचांगp &= ~(CLOCK_ON_DELAY_MASK | CLOCK_OFF_DELAY_MASK);
	पंचांगp |= (CLOCK_ON_DELAY(0) | CLOCK_OFF_DELAY(4));
	WREG32(VCE_UENC_CLOCK_GATING, पंचांगp);

	पंचांगp = RREG32(VCE_CLOCK_GATING_B);
	पंचांगp |= 0x10;
	पंचांगp &= ~0x100000;
	WREG32(VCE_CLOCK_GATING_B, पंचांगp);
पूर्ण

अचिन्हित vce_v2_0_bo_size(काष्ठा radeon_device *rdev)
अणु
	WARN_ON(rdev->vce_fw->size > VCE_V2_0_FW_SIZE);
	वापस VCE_V2_0_FW_SIZE + VCE_V2_0_STACK_SIZE + VCE_V2_0_DATA_SIZE;
पूर्ण

पूर्णांक vce_v2_0_resume(काष्ठा radeon_device *rdev)
अणु
	uपूर्णांक64_t addr = rdev->vce.gpu_addr;
	uपूर्णांक32_t size;

	WREG32_P(VCE_CLOCK_GATING_A, 0, ~(1 << 16));
	WREG32_P(VCE_UENC_CLOCK_GATING, 0x1FF000, ~0xFF9FF000);
	WREG32_P(VCE_UENC_REG_CLOCK_GATING, 0x3F, ~0x3F);
	WREG32(VCE_CLOCK_GATING_B, 0xf7);

	WREG32(VCE_LMI_CTRL, 0x00398000);
	WREG32_P(VCE_LMI_CACHE_CTRL, 0x0, ~0x1);
	WREG32(VCE_LMI_SWAP_CNTL, 0);
	WREG32(VCE_LMI_SWAP_CNTL1, 0);
	WREG32(VCE_LMI_VM_CTRL, 0);

	WREG32(VCE_LMI_VCPU_CACHE_40BIT_BAR, addr >> 8);

	addr &= 0xff;
	size = VCE_V2_0_FW_SIZE;
	WREG32(VCE_VCPU_CACHE_OFFSET0, addr & 0x7fffffff);
	WREG32(VCE_VCPU_CACHE_SIZE0, size);

	addr += size;
	size = VCE_V2_0_STACK_SIZE;
	WREG32(VCE_VCPU_CACHE_OFFSET1, addr & 0x7fffffff);
	WREG32(VCE_VCPU_CACHE_SIZE1, size);

	addr += size;
	size = VCE_V2_0_DATA_SIZE;
	WREG32(VCE_VCPU_CACHE_OFFSET2, addr & 0x7fffffff);
	WREG32(VCE_VCPU_CACHE_SIZE2, size);

	WREG32_P(VCE_LMI_CTRL2, 0x0, ~0x100);

	WREG32_P(VCE_SYS_INT_EN, VCE_SYS_INT_TRAP_INTERRUPT_EN,
		 ~VCE_SYS_INT_TRAP_INTERRUPT_EN);

	vce_v2_0_init_cg(rdev);

	वापस 0;
पूर्ण
