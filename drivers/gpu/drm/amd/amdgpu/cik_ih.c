<शैली गुरु>
/*
 * Copyright 2012 Advanced Micro Devices, Inc.
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
#समावेश "cikd.h"

#समावेश "bif/bif_4_1_d.h"
#समावेश "bif/bif_4_1_sh_mask.h"

#समावेश "oss/oss_2_0_d.h"
#समावेश "oss/oss_2_0_sh_mask.h"

/*
 * Interrupts
 * Starting with r6xx, पूर्णांकerrupts are handled via a ring buffer.
 * Ring buffers are areas of GPU accessible memory that the GPU
 * ग_लिखोs पूर्णांकerrupt vectors पूर्णांकo and the host पढ़ोs vectors out of.
 * There is a rptr (पढ़ो poपूर्णांकer) that determines where the
 * host is currently पढ़ोing, and a wptr (ग_लिखो poपूर्णांकer)
 * which determines where the GPU has written.  When the
 * poपूर्णांकers are equal, the ring is idle.  When the GPU
 * ग_लिखोs vectors to the ring buffer, it increments the
 * wptr.  When there is an पूर्णांकerrupt, the host then starts
 * fetching commands and processing them until the poपूर्णांकers are
 * equal again at which poपूर्णांक it updates the rptr.
 */

अटल व्योम cik_ih_set_पूर्णांकerrupt_funcs(काष्ठा amdgpu_device *adev);

/**
 * cik_ih_enable_पूर्णांकerrupts - Enable the पूर्णांकerrupt ring buffer
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Enable the पूर्णांकerrupt ring buffer (CIK).
 */
अटल व्योम cik_ih_enable_पूर्णांकerrupts(काष्ठा amdgpu_device *adev)
अणु
	u32 ih_cntl = RREG32(mmIH_CNTL);
	u32 ih_rb_cntl = RREG32(mmIH_RB_CNTL);

	ih_cntl |= IH_CNTL__ENABLE_INTR_MASK;
	ih_rb_cntl |= IH_RB_CNTL__RB_ENABLE_MASK;
	WREG32(mmIH_CNTL, ih_cntl);
	WREG32(mmIH_RB_CNTL, ih_rb_cntl);
	adev->irq.ih.enabled = true;
पूर्ण

/**
 * cik_ih_disable_पूर्णांकerrupts - Disable the पूर्णांकerrupt ring buffer
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Disable the पूर्णांकerrupt ring buffer (CIK).
 */
अटल व्योम cik_ih_disable_पूर्णांकerrupts(काष्ठा amdgpu_device *adev)
अणु
	u32 ih_rb_cntl = RREG32(mmIH_RB_CNTL);
	u32 ih_cntl = RREG32(mmIH_CNTL);

	ih_rb_cntl &= ~IH_RB_CNTL__RB_ENABLE_MASK;
	ih_cntl &= ~IH_CNTL__ENABLE_INTR_MASK;
	WREG32(mmIH_RB_CNTL, ih_rb_cntl);
	WREG32(mmIH_CNTL, ih_cntl);
	/* set rptr, wptr to 0 */
	WREG32(mmIH_RB_RPTR, 0);
	WREG32(mmIH_RB_WPTR, 0);
	adev->irq.ih.enabled = false;
	adev->irq.ih.rptr = 0;
पूर्ण

/**
 * cik_ih_irq_init - init and enable the पूर्णांकerrupt ring
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Allocate a ring buffer क्रम the पूर्णांकerrupt controller,
 * enable the RLC, disable पूर्णांकerrupts, enable the IH
 * ring buffer and enable it (CIK).
 * Called at device load and reume.
 * Returns 0 क्रम success, errors क्रम failure.
 */
अटल पूर्णांक cik_ih_irq_init(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_ih_ring *ih = &adev->irq.ih;
	पूर्णांक rb_bufsz;
	u32 पूर्णांकerrupt_cntl, ih_cntl, ih_rb_cntl;

	/* disable irqs */
	cik_ih_disable_पूर्णांकerrupts(adev);

	/* setup पूर्णांकerrupt control */
	WREG32(mmINTERRUPT_CNTL2, adev->dummy_page_addr >> 8);
	पूर्णांकerrupt_cntl = RREG32(mmINTERRUPT_CNTL);
	/* INTERRUPT_CNTL__IH_DUMMY_RD_OVERRIDE_MASK=0 - dummy पढ़ो disabled with msi, enabled without msi
	 * INTERRUPT_CNTL__IH_DUMMY_RD_OVERRIDE_MASK=1 - dummy पढ़ो controlled by IH_DUMMY_RD_EN
	 */
	पूर्णांकerrupt_cntl &= ~INTERRUPT_CNTL__IH_DUMMY_RD_OVERRIDE_MASK;
	/* INTERRUPT_CNTL__IH_REQ_NONSNOOP_EN_MASK=1 अगर ring is in non-cacheable memory, e.g., vram */
	पूर्णांकerrupt_cntl &= ~INTERRUPT_CNTL__IH_REQ_NONSNOOP_EN_MASK;
	WREG32(mmINTERRUPT_CNTL, पूर्णांकerrupt_cntl);

	WREG32(mmIH_RB_BASE, adev->irq.ih.gpu_addr >> 8);
	rb_bufsz = order_base_2(adev->irq.ih.ring_size / 4);

	ih_rb_cntl = (IH_RB_CNTL__WPTR_OVERFLOW_ENABLE_MASK |
		      IH_RB_CNTL__WPTR_OVERFLOW_CLEAR_MASK |
		      (rb_bufsz << 1));

	ih_rb_cntl |= IH_RB_CNTL__WPTR_WRITEBACK_ENABLE_MASK;

	/* set the ग_लिखोback address whether it's enabled or not */
	WREG32(mmIH_RB_WPTR_ADDR_LO, lower_32_bits(ih->wptr_addr));
	WREG32(mmIH_RB_WPTR_ADDR_HI, upper_32_bits(ih->wptr_addr) & 0xFF);

	WREG32(mmIH_RB_CNTL, ih_rb_cntl);

	/* set rptr, wptr to 0 */
	WREG32(mmIH_RB_RPTR, 0);
	WREG32(mmIH_RB_WPTR, 0);

	/* Default settings क्रम IH_CNTL (disabled at first) */
	ih_cntl = (0x10 << IH_CNTL__MC_WRREQ_CREDIT__SHIFT) |
		(0x10 << IH_CNTL__MC_WR_CLEAN_CNT__SHIFT) |
		(0 << IH_CNTL__MC_VMID__SHIFT);
	/* IH_CNTL__RPTR_REARM_MASK only works अगर msi's are enabled */
	अगर (adev->irq.msi_enabled)
		ih_cntl |= IH_CNTL__RPTR_REARM_MASK;
	WREG32(mmIH_CNTL, ih_cntl);

	pci_set_master(adev->pdev);

	/* enable irqs */
	cik_ih_enable_पूर्णांकerrupts(adev);

	वापस 0;
पूर्ण

/**
 * cik_ih_irq_disable - disable पूर्णांकerrupts
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Disable पूर्णांकerrupts on the hw (CIK).
 */
अटल व्योम cik_ih_irq_disable(काष्ठा amdgpu_device *adev)
अणु
	cik_ih_disable_पूर्णांकerrupts(adev);
	/* Wait and acknowledge irq */
	mdelay(1);
पूर्ण

/**
 * cik_ih_get_wptr - get the IH ring buffer wptr
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @ih: IH ring buffer to fetch wptr
 *
 * Get the IH ring buffer wptr from either the रेजिस्टर
 * or the ग_लिखोback memory buffer (CIK).  Also check क्रम
 * ring buffer overflow and deal with it.
 * Used by cik_irq_process().
 * Returns the value of the wptr.
 */
अटल u32 cik_ih_get_wptr(काष्ठा amdgpu_device *adev,
			   काष्ठा amdgpu_ih_ring *ih)
अणु
	u32 wptr, पंचांगp;

	wptr = le32_to_cpu(*ih->wptr_cpu);

	अगर (wptr & IH_RB_WPTR__RB_OVERFLOW_MASK) अणु
		wptr &= ~IH_RB_WPTR__RB_OVERFLOW_MASK;
		/* When a ring buffer overflow happen start parsing पूर्णांकerrupt
		 * from the last not overwritten vector (wptr + 16). Hopefully
		 * this should allow us to catchup.
		 */
		dev_warn(adev->dev, "IH ring buffer overflow (0x%08X, 0x%08X, 0x%08X)\n",
			 wptr, ih->rptr, (wptr + 16) & ih->ptr_mask);
		ih->rptr = (wptr + 16) & ih->ptr_mask;
		पंचांगp = RREG32(mmIH_RB_CNTL);
		पंचांगp |= IH_RB_CNTL__WPTR_OVERFLOW_CLEAR_MASK;
		WREG32(mmIH_RB_CNTL, पंचांगp);
	पूर्ण
	वापस (wptr & ih->ptr_mask);
पूर्ण

/*        CIK IV Ring
 * Each IV ring entry is 128 bits:
 * [7:0]    - पूर्णांकerrupt source id
 * [31:8]   - reserved
 * [59:32]  - पूर्णांकerrupt source data
 * [63:60]  - reserved
 * [71:64]  - RINGID
 *            CP:
 *            ME_ID [1:0], PIPE_ID[1:0], QUEUE_ID[2:0]
 *            QUEUE_ID - क्रम compute, which of the 8 queues owned by the dispatcher
 *                     - क्रम gfx, hw shader state (0=PS...5=LS, 6=CS)
 *            ME_ID - 0 = gfx, 1 = first 4 CS pipes, 2 = second 4 CS pipes
 *            PIPE_ID - ME0 0=3D
 *                    - ME1&2 compute dispatcher (4 pipes each)
 *            SDMA:
 *            INSTANCE_ID [1:0], QUEUE_ID[1:0]
 *            INSTANCE_ID - 0 = sdma0, 1 = sdma1
 *            QUEUE_ID - 0 = gfx, 1 = rlc0, 2 = rlc1
 * [79:72]  - VMID
 * [95:80]  - PASID
 * [127:96] - reserved
 */

 /**
 * cik_ih_decode_iv - decode an पूर्णांकerrupt vector
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Decodes the पूर्णांकerrupt vector at the current rptr
 * position and also advance the position.
 */
अटल व्योम cik_ih_decode_iv(काष्ठा amdgpu_device *adev,
			     काष्ठा amdgpu_ih_ring *ih,
			     काष्ठा amdgpu_iv_entry *entry)
अणु
	/* wptr/rptr are in bytes! */
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
	entry->pasid = (dw[2] >> 16) & 0xffff;

	/* wptr/rptr are in bytes! */
	ih->rptr += 16;
पूर्ण

/**
 * cik_ih_set_rptr - set the IH ring buffer rptr
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @ih: IH ring buffer to set wptr
 *
 * Set the IH ring buffer rptr.
 */
अटल व्योम cik_ih_set_rptr(काष्ठा amdgpu_device *adev,
			    काष्ठा amdgpu_ih_ring *ih)
अणु
	WREG32(mmIH_RB_RPTR, ih->rptr);
पूर्ण

अटल पूर्णांक cik_ih_early_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	पूर्णांक ret;

	ret = amdgpu_irq_add_करोमुख्य(adev);
	अगर (ret)
		वापस ret;

	cik_ih_set_पूर्णांकerrupt_funcs(adev);

	वापस 0;
पूर्ण

अटल पूर्णांक cik_ih_sw_init(व्योम *handle)
अणु
	पूर्णांक r;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	r = amdgpu_ih_ring_init(adev, &adev->irq.ih, 64 * 1024, false);
	अगर (r)
		वापस r;

	r = amdgpu_irq_init(adev);

	वापस r;
पूर्ण

अटल पूर्णांक cik_ih_sw_fini(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	amdgpu_irq_fini(adev);
	amdgpu_ih_ring_fini(adev, &adev->irq.ih);
	amdgpu_irq_हटाओ_करोमुख्य(adev);

	वापस 0;
पूर्ण

अटल पूर्णांक cik_ih_hw_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	वापस cik_ih_irq_init(adev);
पूर्ण

अटल पूर्णांक cik_ih_hw_fini(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	cik_ih_irq_disable(adev);

	वापस 0;
पूर्ण

अटल पूर्णांक cik_ih_suspend(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	वापस cik_ih_hw_fini(adev);
पूर्ण

अटल पूर्णांक cik_ih_resume(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	वापस cik_ih_hw_init(adev);
पूर्ण

अटल bool cik_ih_is_idle(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	u32 पंचांगp = RREG32(mmSRBM_STATUS);

	अगर (पंचांगp & SRBM_STATUS__IH_BUSY_MASK)
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक cik_ih_रुको_क्रम_idle(व्योम *handle)
अणु
	अचिन्हित i;
	u32 पंचांगp;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	क्रम (i = 0; i < adev->usec_समयout; i++) अणु
		/* पढ़ो MC_STATUS */
		पंचांगp = RREG32(mmSRBM_STATUS) & SRBM_STATUS__IH_BUSY_MASK;
		अगर (!पंचांगp)
			वापस 0;
		udelay(1);
	पूर्ण
	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक cik_ih_soft_reset(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	u32 srbm_soft_reset = 0;
	u32 पंचांगp = RREG32(mmSRBM_STATUS);

	अगर (पंचांगp & SRBM_STATUS__IH_BUSY_MASK)
		srbm_soft_reset |= SRBM_SOFT_RESET__SOFT_RESET_IH_MASK;

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

अटल पूर्णांक cik_ih_set_घड़ीgating_state(व्योम *handle,
					  क्रमागत amd_घड़ीgating_state state)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक cik_ih_set_घातergating_state(व्योम *handle,
					  क्रमागत amd_घातergating_state state)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा amd_ip_funcs cik_ih_ip_funcs = अणु
	.name = "cik_ih",
	.early_init = cik_ih_early_init,
	.late_init = शून्य,
	.sw_init = cik_ih_sw_init,
	.sw_fini = cik_ih_sw_fini,
	.hw_init = cik_ih_hw_init,
	.hw_fini = cik_ih_hw_fini,
	.suspend = cik_ih_suspend,
	.resume = cik_ih_resume,
	.is_idle = cik_ih_is_idle,
	.रुको_क्रम_idle = cik_ih_रुको_क्रम_idle,
	.soft_reset = cik_ih_soft_reset,
	.set_घड़ीgating_state = cik_ih_set_घड़ीgating_state,
	.set_घातergating_state = cik_ih_set_घातergating_state,
पूर्ण;

अटल स्थिर काष्ठा amdgpu_ih_funcs cik_ih_funcs = अणु
	.get_wptr = cik_ih_get_wptr,
	.decode_iv = cik_ih_decode_iv,
	.set_rptr = cik_ih_set_rptr
पूर्ण;

अटल व्योम cik_ih_set_पूर्णांकerrupt_funcs(काष्ठा amdgpu_device *adev)
अणु
	adev->irq.ih_funcs = &cik_ih_funcs;
पूर्ण

स्थिर काष्ठा amdgpu_ip_block_version cik_ih_ip_block =
अणु
	.type = AMD_IP_BLOCK_TYPE_IH,
	.major = 2,
	.minor = 0,
	.rev = 0,
	.funcs = &cik_ih_ip_funcs,
पूर्ण;
