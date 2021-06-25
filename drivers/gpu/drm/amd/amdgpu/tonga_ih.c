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

#समावेश <linux/pci.h>

#समावेश "amdgpu.h"
#समावेश "amdgpu_ih.h"
#समावेश "vid.h"

#समावेश "oss/oss_3_0_d.h"
#समावेश "oss/oss_3_0_sh_mask.h"

#समावेश "bif/bif_5_1_d.h"
#समावेश "bif/bif_5_1_sh_mask.h"

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

अटल व्योम tonga_ih_set_पूर्णांकerrupt_funcs(काष्ठा amdgpu_device *adev);

/**
 * tonga_ih_enable_पूर्णांकerrupts - Enable the पूर्णांकerrupt ring buffer
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Enable the पूर्णांकerrupt ring buffer (VI).
 */
अटल व्योम tonga_ih_enable_पूर्णांकerrupts(काष्ठा amdgpu_device *adev)
अणु
	u32 ih_rb_cntl = RREG32(mmIH_RB_CNTL);

	ih_rb_cntl = REG_SET_FIELD(ih_rb_cntl, IH_RB_CNTL, RB_ENABLE, 1);
	ih_rb_cntl = REG_SET_FIELD(ih_rb_cntl, IH_RB_CNTL, ENABLE_INTR, 1);
	WREG32(mmIH_RB_CNTL, ih_rb_cntl);
	adev->irq.ih.enabled = true;
पूर्ण

/**
 * tonga_ih_disable_पूर्णांकerrupts - Disable the पूर्णांकerrupt ring buffer
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Disable the पूर्णांकerrupt ring buffer (VI).
 */
अटल व्योम tonga_ih_disable_पूर्णांकerrupts(काष्ठा amdgpu_device *adev)
अणु
	u32 ih_rb_cntl = RREG32(mmIH_RB_CNTL);

	ih_rb_cntl = REG_SET_FIELD(ih_rb_cntl, IH_RB_CNTL, RB_ENABLE, 0);
	ih_rb_cntl = REG_SET_FIELD(ih_rb_cntl, IH_RB_CNTL, ENABLE_INTR, 0);
	WREG32(mmIH_RB_CNTL, ih_rb_cntl);
	/* set rptr, wptr to 0 */
	WREG32(mmIH_RB_RPTR, 0);
	WREG32(mmIH_RB_WPTR, 0);
	adev->irq.ih.enabled = false;
	adev->irq.ih.rptr = 0;
पूर्ण

/**
 * tonga_ih_irq_init - init and enable the पूर्णांकerrupt ring
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Allocate a ring buffer क्रम the पूर्णांकerrupt controller,
 * enable the RLC, disable पूर्णांकerrupts, enable the IH
 * ring buffer and enable it (VI).
 * Called at device load and reume.
 * Returns 0 क्रम success, errors क्रम failure.
 */
अटल पूर्णांक tonga_ih_irq_init(काष्ठा amdgpu_device *adev)
अणु
	u32 पूर्णांकerrupt_cntl, ih_rb_cntl, ih_करोorbell_rtpr;
	काष्ठा amdgpu_ih_ring *ih = &adev->irq.ih;
	पूर्णांक rb_bufsz;

	/* disable irqs */
	tonga_ih_disable_पूर्णांकerrupts(adev);

	/* setup पूर्णांकerrupt control */
	WREG32(mmINTERRUPT_CNTL2, adev->dummy_page_addr >> 8);
	पूर्णांकerrupt_cntl = RREG32(mmINTERRUPT_CNTL);
	/* INTERRUPT_CNTL__IH_DUMMY_RD_OVERRIDE_MASK=0 - dummy पढ़ो disabled with msi, enabled without msi
	 * INTERRUPT_CNTL__IH_DUMMY_RD_OVERRIDE_MASK=1 - dummy पढ़ो controlled by IH_DUMMY_RD_EN
	 */
	पूर्णांकerrupt_cntl = REG_SET_FIELD(पूर्णांकerrupt_cntl, INTERRUPT_CNTL, IH_DUMMY_RD_OVERRIDE, 0);
	/* INTERRUPT_CNTL__IH_REQ_NONSNOOP_EN_MASK=1 अगर ring is in non-cacheable memory, e.g., vram */
	पूर्णांकerrupt_cntl = REG_SET_FIELD(पूर्णांकerrupt_cntl, INTERRUPT_CNTL, IH_REQ_NONSNOOP_EN, 0);
	WREG32(mmINTERRUPT_CNTL, पूर्णांकerrupt_cntl);

	/* Ring Buffer base. [39:8] of 40-bit address of the beginning of the ring buffer*/
	WREG32(mmIH_RB_BASE, ih->gpu_addr >> 8);

	rb_bufsz = order_base_2(adev->irq.ih.ring_size / 4);
	ih_rb_cntl = REG_SET_FIELD(0, IH_RB_CNTL, WPTR_OVERFLOW_CLEAR, 1);
	ih_rb_cntl = REG_SET_FIELD(ih_rb_cntl, IH_RB_CNTL, RB_SIZE, rb_bufsz);
	/* Ring Buffer ग_लिखो poपूर्णांकer ग_लिखोback. If enabled, IH_RB_WPTR रेजिस्टर value is written to memory */
	ih_rb_cntl = REG_SET_FIELD(ih_rb_cntl, IH_RB_CNTL, WPTR_WRITEBACK_ENABLE, 1);
	ih_rb_cntl = REG_SET_FIELD(ih_rb_cntl, IH_RB_CNTL, MC_VMID, 0);

	अगर (adev->irq.msi_enabled)
		ih_rb_cntl = REG_SET_FIELD(ih_rb_cntl, IH_RB_CNTL, RPTR_REARM, 1);

	WREG32(mmIH_RB_CNTL, ih_rb_cntl);

	/* set the ग_लिखोback address whether it's enabled or not */
	WREG32(mmIH_RB_WPTR_ADDR_LO, lower_32_bits(ih->wptr_addr));
	WREG32(mmIH_RB_WPTR_ADDR_HI, upper_32_bits(ih->wptr_addr) & 0xFF);

	/* set rptr, wptr to 0 */
	WREG32(mmIH_RB_RPTR, 0);
	WREG32(mmIH_RB_WPTR, 0);

	ih_करोorbell_rtpr = RREG32(mmIH_DOORBELL_RPTR);
	अगर (adev->irq.ih.use_करोorbell) अणु
		ih_करोorbell_rtpr = REG_SET_FIELD(ih_करोorbell_rtpr, IH_DOORBELL_RPTR,
						 OFFSET, adev->irq.ih.करोorbell_index);
		ih_करोorbell_rtpr = REG_SET_FIELD(ih_करोorbell_rtpr, IH_DOORBELL_RPTR,
						 ENABLE, 1);
	पूर्ण अन्यथा अणु
		ih_करोorbell_rtpr = REG_SET_FIELD(ih_करोorbell_rtpr, IH_DOORBELL_RPTR,
						 ENABLE, 0);
	पूर्ण
	WREG32(mmIH_DOORBELL_RPTR, ih_करोorbell_rtpr);

	pci_set_master(adev->pdev);

	/* enable पूर्णांकerrupts */
	tonga_ih_enable_पूर्णांकerrupts(adev);

	वापस 0;
पूर्ण

/**
 * tonga_ih_irq_disable - disable पूर्णांकerrupts
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Disable पूर्णांकerrupts on the hw (VI).
 */
अटल व्योम tonga_ih_irq_disable(काष्ठा amdgpu_device *adev)
अणु
	tonga_ih_disable_पूर्णांकerrupts(adev);

	/* Wait and acknowledge irq */
	mdelay(1);
पूर्ण

/**
 * tonga_ih_get_wptr - get the IH ring buffer wptr
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @ih: IH ring buffer to fetch wptr
 *
 * Get the IH ring buffer wptr from either the रेजिस्टर
 * or the ग_लिखोback memory buffer (VI).  Also check क्रम
 * ring buffer overflow and deal with it.
 * Used by cz_irq_process(VI).
 * Returns the value of the wptr.
 */
अटल u32 tonga_ih_get_wptr(काष्ठा amdgpu_device *adev,
			     काष्ठा amdgpu_ih_ring *ih)
अणु
	u32 wptr, पंचांगp;

	wptr = le32_to_cpu(*ih->wptr_cpu);

	अगर (!REG_GET_FIELD(wptr, IH_RB_WPTR, RB_OVERFLOW))
		जाओ out;

	/* Double check that the overflow wasn't alपढ़ोy cleared. */
	wptr = RREG32(mmIH_RB_WPTR);

	अगर (!REG_GET_FIELD(wptr, IH_RB_WPTR, RB_OVERFLOW))
		जाओ out;

	wptr = REG_SET_FIELD(wptr, IH_RB_WPTR, RB_OVERFLOW, 0);

	/* When a ring buffer overflow happen start parsing पूर्णांकerrupt
	 * from the last not overwritten vector (wptr + 16). Hopefully
	 * this should allow us to catchup.
	 */

	dev_warn(adev->dev, "IH ring buffer overflow (0x%08X, 0x%08X, 0x%08X)\n",
		wptr, ih->rptr, (wptr + 16) & ih->ptr_mask);
	ih->rptr = (wptr + 16) & ih->ptr_mask;
	पंचांगp = RREG32(mmIH_RB_CNTL);
	पंचांगp = REG_SET_FIELD(पंचांगp, IH_RB_CNTL, WPTR_OVERFLOW_CLEAR, 1);
	WREG32(mmIH_RB_CNTL, पंचांगp);

out:
	वापस (wptr & ih->ptr_mask);
पूर्ण

/**
 * tonga_ih_decode_iv - decode an पूर्णांकerrupt vector
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @ih: IH ring buffer to decode
 * @entry: IV entry to place decoded inक्रमmation पूर्णांकo
 *
 * Decodes the पूर्णांकerrupt vector at the current rptr
 * position and also advance the position.
 */
अटल व्योम tonga_ih_decode_iv(काष्ठा amdgpu_device *adev,
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
 * tonga_ih_set_rptr - set the IH ring buffer rptr
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @ih: IH ring buffer to set rptr
 *
 * Set the IH ring buffer rptr.
 */
अटल व्योम tonga_ih_set_rptr(काष्ठा amdgpu_device *adev,
			      काष्ठा amdgpu_ih_ring *ih)
अणु
	अगर (ih->use_करोorbell) अणु
		/* XXX check अगर swapping is necessary on BE */
		*ih->rptr_cpu = ih->rptr;
		WDOORBELL32(ih->करोorbell_index, ih->rptr);
	पूर्ण अन्यथा अणु
		WREG32(mmIH_RB_RPTR, ih->rptr);
	पूर्ण
पूर्ण

अटल पूर्णांक tonga_ih_early_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	पूर्णांक ret;

	ret = amdgpu_irq_add_करोमुख्य(adev);
	अगर (ret)
		वापस ret;

	tonga_ih_set_पूर्णांकerrupt_funcs(adev);

	वापस 0;
पूर्ण

अटल पूर्णांक tonga_ih_sw_init(व्योम *handle)
अणु
	पूर्णांक r;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	r = amdgpu_ih_ring_init(adev, &adev->irq.ih, 64 * 1024, true);
	अगर (r)
		वापस r;

	adev->irq.ih.use_करोorbell = true;
	adev->irq.ih.करोorbell_index = adev->करोorbell_index.ih;

	r = amdgpu_irq_init(adev);

	वापस r;
पूर्ण

अटल पूर्णांक tonga_ih_sw_fini(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	amdgpu_irq_fini(adev);
	amdgpu_ih_ring_fini(adev, &adev->irq.ih);
	amdgpu_irq_हटाओ_करोमुख्य(adev);

	वापस 0;
पूर्ण

अटल पूर्णांक tonga_ih_hw_init(व्योम *handle)
अणु
	पूर्णांक r;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	r = tonga_ih_irq_init(adev);
	अगर (r)
		वापस r;

	वापस 0;
पूर्ण

अटल पूर्णांक tonga_ih_hw_fini(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	tonga_ih_irq_disable(adev);

	वापस 0;
पूर्ण

अटल पूर्णांक tonga_ih_suspend(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	वापस tonga_ih_hw_fini(adev);
पूर्ण

अटल पूर्णांक tonga_ih_resume(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	वापस tonga_ih_hw_init(adev);
पूर्ण

अटल bool tonga_ih_is_idle(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	u32 पंचांगp = RREG32(mmSRBM_STATUS);

	अगर (REG_GET_FIELD(पंचांगp, SRBM_STATUS, IH_BUSY))
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक tonga_ih_रुको_क्रम_idle(व्योम *handle)
अणु
	अचिन्हित i;
	u32 पंचांगp;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	क्रम (i = 0; i < adev->usec_समयout; i++) अणु
		/* पढ़ो MC_STATUS */
		पंचांगp = RREG32(mmSRBM_STATUS);
		अगर (!REG_GET_FIELD(पंचांगp, SRBM_STATUS, IH_BUSY))
			वापस 0;
		udelay(1);
	पूर्ण
	वापस -ETIMEDOUT;
पूर्ण

अटल bool tonga_ih_check_soft_reset(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	u32 srbm_soft_reset = 0;
	u32 पंचांगp = RREG32(mmSRBM_STATUS);

	अगर (पंचांगp & SRBM_STATUS__IH_BUSY_MASK)
		srbm_soft_reset = REG_SET_FIELD(srbm_soft_reset, SRBM_SOFT_RESET,
						SOFT_RESET_IH, 1);

	अगर (srbm_soft_reset) अणु
		adev->irq.srbm_soft_reset = srbm_soft_reset;
		वापस true;
	पूर्ण अन्यथा अणु
		adev->irq.srbm_soft_reset = 0;
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक tonga_ih_pre_soft_reset(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	अगर (!adev->irq.srbm_soft_reset)
		वापस 0;

	वापस tonga_ih_hw_fini(adev);
पूर्ण

अटल पूर्णांक tonga_ih_post_soft_reset(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	अगर (!adev->irq.srbm_soft_reset)
		वापस 0;

	वापस tonga_ih_hw_init(adev);
पूर्ण

अटल पूर्णांक tonga_ih_soft_reset(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	u32 srbm_soft_reset;

	अगर (!adev->irq.srbm_soft_reset)
		वापस 0;
	srbm_soft_reset = adev->irq.srbm_soft_reset;

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

अटल पूर्णांक tonga_ih_set_घड़ीgating_state(व्योम *handle,
					  क्रमागत amd_घड़ीgating_state state)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक tonga_ih_set_घातergating_state(व्योम *handle,
					  क्रमागत amd_घातergating_state state)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा amd_ip_funcs tonga_ih_ip_funcs = अणु
	.name = "tonga_ih",
	.early_init = tonga_ih_early_init,
	.late_init = शून्य,
	.sw_init = tonga_ih_sw_init,
	.sw_fini = tonga_ih_sw_fini,
	.hw_init = tonga_ih_hw_init,
	.hw_fini = tonga_ih_hw_fini,
	.suspend = tonga_ih_suspend,
	.resume = tonga_ih_resume,
	.is_idle = tonga_ih_is_idle,
	.रुको_क्रम_idle = tonga_ih_रुको_क्रम_idle,
	.check_soft_reset = tonga_ih_check_soft_reset,
	.pre_soft_reset = tonga_ih_pre_soft_reset,
	.soft_reset = tonga_ih_soft_reset,
	.post_soft_reset = tonga_ih_post_soft_reset,
	.set_घड़ीgating_state = tonga_ih_set_घड़ीgating_state,
	.set_घातergating_state = tonga_ih_set_घातergating_state,
पूर्ण;

अटल स्थिर काष्ठा amdgpu_ih_funcs tonga_ih_funcs = अणु
	.get_wptr = tonga_ih_get_wptr,
	.decode_iv = tonga_ih_decode_iv,
	.set_rptr = tonga_ih_set_rptr
पूर्ण;

अटल व्योम tonga_ih_set_पूर्णांकerrupt_funcs(काष्ठा amdgpu_device *adev)
अणु
	adev->irq.ih_funcs = &tonga_ih_funcs;
पूर्ण

स्थिर काष्ठा amdgpu_ip_block_version tonga_ih_ip_block =
अणु
	.type = AMD_IP_BLOCK_TYPE_IH,
	.major = 3,
	.minor = 0,
	.rev = 0,
	.funcs = &tonga_ih_ip_funcs,
पूर्ण;
