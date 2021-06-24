<शैली गुरु>
/*
 * Copyright 2015 Advanced Micro Devices, Inc.
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

#समावेश <linux/pci.h>

#समावेश "amdgpu.h"
#समावेश "amdgpu_ih.h"
#समावेश "sid.h"
#समावेश "si_ih.h"
#समावेश "oss/oss_1_0_d.h"
#समावेश "oss/oss_1_0_sh_mask.h"

अटल व्योम si_ih_set_पूर्णांकerrupt_funcs(काष्ठा amdgpu_device *adev);

अटल व्योम si_ih_enable_पूर्णांकerrupts(काष्ठा amdgpu_device *adev)
अणु
	u32 ih_cntl = RREG32(IH_CNTL);
	u32 ih_rb_cntl = RREG32(IH_RB_CNTL);

	ih_cntl |= ENABLE_INTR;
	ih_rb_cntl |= IH_RB_ENABLE;
	WREG32(IH_CNTL, ih_cntl);
	WREG32(IH_RB_CNTL, ih_rb_cntl);
	adev->irq.ih.enabled = true;
पूर्ण

अटल व्योम si_ih_disable_पूर्णांकerrupts(काष्ठा amdgpu_device *adev)
अणु
	u32 ih_rb_cntl = RREG32(IH_RB_CNTL);
	u32 ih_cntl = RREG32(IH_CNTL);

	ih_rb_cntl &= ~IH_RB_ENABLE;
	ih_cntl &= ~ENABLE_INTR;
	WREG32(IH_RB_CNTL, ih_rb_cntl);
	WREG32(IH_CNTL, ih_cntl);
	WREG32(IH_RB_RPTR, 0);
	WREG32(IH_RB_WPTR, 0);
	adev->irq.ih.enabled = false;
	adev->irq.ih.rptr = 0;
पूर्ण

अटल पूर्णांक si_ih_irq_init(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_ih_ring *ih = &adev->irq.ih;
	पूर्णांक rb_bufsz;
	u32 पूर्णांकerrupt_cntl, ih_cntl, ih_rb_cntl;

	si_ih_disable_पूर्णांकerrupts(adev);
	/* set dummy पढ़ो address to dummy page address */
	WREG32(INTERRUPT_CNTL2, adev->dummy_page_addr >> 8);
	पूर्णांकerrupt_cntl = RREG32(INTERRUPT_CNTL);
	पूर्णांकerrupt_cntl &= ~IH_DUMMY_RD_OVERRIDE;
	पूर्णांकerrupt_cntl &= ~IH_REQ_NONSNOOP_EN;
	WREG32(INTERRUPT_CNTL, पूर्णांकerrupt_cntl);

	WREG32(IH_RB_BASE, adev->irq.ih.gpu_addr >> 8);
	rb_bufsz = order_base_2(adev->irq.ih.ring_size / 4);

	ih_rb_cntl = IH_WPTR_OVERFLOW_ENABLE |
		     IH_WPTR_OVERFLOW_CLEAR |
		     (rb_bufsz << 1) |
		     IH_WPTR_WRITEBACK_ENABLE;

	WREG32(IH_RB_WPTR_ADDR_LO, lower_32_bits(ih->wptr_addr));
	WREG32(IH_RB_WPTR_ADDR_HI, upper_32_bits(ih->wptr_addr) & 0xFF);
	WREG32(IH_RB_CNTL, ih_rb_cntl);
	WREG32(IH_RB_RPTR, 0);
	WREG32(IH_RB_WPTR, 0);

	ih_cntl = MC_WRREQ_CREDIT(0x10) | MC_WR_CLEAN_CNT(0x10) | MC_VMID(0);
	अगर (adev->irq.msi_enabled)
		ih_cntl |= RPTR_REARM;
	WREG32(IH_CNTL, ih_cntl);

	pci_set_master(adev->pdev);
	si_ih_enable_पूर्णांकerrupts(adev);

	वापस 0;
पूर्ण

अटल व्योम si_ih_irq_disable(काष्ठा amdgpu_device *adev)
अणु
	si_ih_disable_पूर्णांकerrupts(adev);
	mdelay(1);
पूर्ण

अटल u32 si_ih_get_wptr(काष्ठा amdgpu_device *adev,
			  काष्ठा amdgpu_ih_ring *ih)
अणु
	u32 wptr, पंचांगp;

	wptr = le32_to_cpu(*ih->wptr_cpu);

	अगर (wptr & IH_RB_WPTR__RB_OVERFLOW_MASK) अणु
		wptr &= ~IH_RB_WPTR__RB_OVERFLOW_MASK;
		dev_warn(adev->dev, "IH ring buffer overflow (0x%08X, 0x%08X, 0x%08X)\n",
			wptr, ih->rptr, (wptr + 16) & ih->ptr_mask);
		ih->rptr = (wptr + 16) & ih->ptr_mask;
		पंचांगp = RREG32(IH_RB_CNTL);
		पंचांगp |= IH_RB_CNTL__WPTR_OVERFLOW_CLEAR_MASK;
		WREG32(IH_RB_CNTL, पंचांगp);
	पूर्ण
	वापस (wptr & ih->ptr_mask);
पूर्ण

अटल व्योम si_ih_decode_iv(काष्ठा amdgpu_device *adev,
			    काष्ठा amdgpu_ih_ring *ih,
			    काष्ठा amdgpu_iv_entry *entry)
अणु
	u32 ring_index = ih->rptr >> 2;
	uपूर्णांक32_t dw[4];

	dw[0] = le32_to_cpu(ih->ring[ring_index + 0]);
	dw[1] = le32_to_cpu(ih->ring[ring_index + 1]);
	dw[2] = le32_to_cpu(ih->ring[ring_index + 2]);
	dw[3] = le32_to_cpu(ih->ring[ring_index + 3]);

	entry->client_id = AMDGPU_IRQ_CLIENTID_LEGACY;
	entry->src_id = dw[0] & 0xff;
	entry->src_data[0] = dw[1] & 0xfffffff;
	entry->ring_id = dw[2] & 0xff;
	entry->vmid = (dw[2] >> 8) & 0xff;

	ih->rptr += 16;
पूर्ण

अटल व्योम si_ih_set_rptr(काष्ठा amdgpu_device *adev,
			   काष्ठा amdgpu_ih_ring *ih)
अणु
	WREG32(IH_RB_RPTR, ih->rptr);
पूर्ण

अटल पूर्णांक si_ih_early_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	si_ih_set_पूर्णांकerrupt_funcs(adev);

	वापस 0;
पूर्ण

अटल पूर्णांक si_ih_sw_init(व्योम *handle)
अणु
	पूर्णांक r;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	r = amdgpu_ih_ring_init(adev, &adev->irq.ih, 64 * 1024, false);
	अगर (r)
		वापस r;

	वापस amdgpu_irq_init(adev);
पूर्ण

अटल पूर्णांक si_ih_sw_fini(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	amdgpu_irq_fini(adev);
	amdgpu_ih_ring_fini(adev, &adev->irq.ih);

	वापस 0;
पूर्ण

अटल पूर्णांक si_ih_hw_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	वापस si_ih_irq_init(adev);
पूर्ण

अटल पूर्णांक si_ih_hw_fini(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	si_ih_irq_disable(adev);

	वापस 0;
पूर्ण

अटल पूर्णांक si_ih_suspend(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	वापस si_ih_hw_fini(adev);
पूर्ण

अटल पूर्णांक si_ih_resume(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	वापस si_ih_hw_init(adev);
पूर्ण

अटल bool si_ih_is_idle(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	u32 पंचांगp = RREG32(SRBM_STATUS);

	अगर (पंचांगp & SRBM_STATUS__IH_BUSY_MASK)
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक si_ih_रुको_क्रम_idle(व्योम *handle)
अणु
	अचिन्हित i;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	क्रम (i = 0; i < adev->usec_समयout; i++) अणु
		अगर (si_ih_is_idle(handle))
			वापस 0;
		udelay(1);
	पूर्ण
	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक si_ih_soft_reset(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	u32 srbm_soft_reset = 0;
	u32 पंचांगp = RREG32(SRBM_STATUS);

	अगर (पंचांगp & SRBM_STATUS__IH_BUSY_MASK)
		srbm_soft_reset |= SRBM_SOFT_RESET__SOFT_RESET_IH_MASK;

	अगर (srbm_soft_reset) अणु
		पंचांगp = RREG32(SRBM_SOFT_RESET);
		पंचांगp |= srbm_soft_reset;
		dev_info(adev->dev, "SRBM_SOFT_RESET=0x%08X\n", पंचांगp);
		WREG32(SRBM_SOFT_RESET, पंचांगp);
		पंचांगp = RREG32(SRBM_SOFT_RESET);

		udelay(50);

		पंचांगp &= ~srbm_soft_reset;
		WREG32(SRBM_SOFT_RESET, पंचांगp);
		पंचांगp = RREG32(SRBM_SOFT_RESET);

		udelay(50);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक si_ih_set_घड़ीgating_state(व्योम *handle,
					  क्रमागत amd_घड़ीgating_state state)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक si_ih_set_घातergating_state(व्योम *handle,
					  क्रमागत amd_घातergating_state state)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा amd_ip_funcs si_ih_ip_funcs = अणु
	.name = "si_ih",
	.early_init = si_ih_early_init,
	.late_init = शून्य,
	.sw_init = si_ih_sw_init,
	.sw_fini = si_ih_sw_fini,
	.hw_init = si_ih_hw_init,
	.hw_fini = si_ih_hw_fini,
	.suspend = si_ih_suspend,
	.resume = si_ih_resume,
	.is_idle = si_ih_is_idle,
	.रुको_क्रम_idle = si_ih_रुको_क्रम_idle,
	.soft_reset = si_ih_soft_reset,
	.set_घड़ीgating_state = si_ih_set_घड़ीgating_state,
	.set_घातergating_state = si_ih_set_घातergating_state,
पूर्ण;

अटल स्थिर काष्ठा amdgpu_ih_funcs si_ih_funcs = अणु
	.get_wptr = si_ih_get_wptr,
	.decode_iv = si_ih_decode_iv,
	.set_rptr = si_ih_set_rptr
पूर्ण;

अटल व्योम si_ih_set_पूर्णांकerrupt_funcs(काष्ठा amdgpu_device *adev)
अणु
	adev->irq.ih_funcs = &si_ih_funcs;
पूर्ण

स्थिर काष्ठा amdgpu_ip_block_version si_ih_ip_block =
अणु
	.type = AMD_IP_BLOCK_TYPE_IH,
	.major = 1,
	.minor = 0,
	.rev = 0,
	.funcs = &si_ih_ip_funcs,
पूर्ण;
