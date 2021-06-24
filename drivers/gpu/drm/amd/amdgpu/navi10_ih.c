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

#समावेश <linux/pci.h>

#समावेश "amdgpu.h"
#समावेश "amdgpu_ih.h"

#समावेश "oss/osssys_5_0_0_offset.h"
#समावेश "oss/osssys_5_0_0_sh_mask.h"

#समावेश "soc15_common.h"
#समावेश "navi10_ih.h"

#घोषणा MAX_REARM_RETRY 10

#घोषणा mmIH_CHICKEN_Sienna_Cichlid                 0x018d
#घोषणा mmIH_CHICKEN_Sienna_Cichlid_BASE_IDX        0

अटल व्योम navi10_ih_set_पूर्णांकerrupt_funcs(काष्ठा amdgpu_device *adev);

/**
 * navi10_ih_init_रेजिस्टर_offset - Initialize रेजिस्टर offset क्रम ih rings
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Initialize रेजिस्टर offset ih rings (NAVI10).
 */
अटल व्योम navi10_ih_init_रेजिस्टर_offset(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_ih_regs *ih_regs;

	अगर (adev->irq.ih.ring_size) अणु
		ih_regs = &adev->irq.ih.ih_regs;
		ih_regs->ih_rb_base = SOC15_REG_OFFSET(OSSSYS, 0, mmIH_RB_BASE);
		ih_regs->ih_rb_base_hi = SOC15_REG_OFFSET(OSSSYS, 0, mmIH_RB_BASE_HI);
		ih_regs->ih_rb_cntl = SOC15_REG_OFFSET(OSSSYS, 0, mmIH_RB_CNTL);
		ih_regs->ih_rb_wptr = SOC15_REG_OFFSET(OSSSYS, 0, mmIH_RB_WPTR);
		ih_regs->ih_rb_rptr = SOC15_REG_OFFSET(OSSSYS, 0, mmIH_RB_RPTR);
		ih_regs->ih_करोorbell_rptr = SOC15_REG_OFFSET(OSSSYS, 0, mmIH_DOORBELL_RPTR);
		ih_regs->ih_rb_wptr_addr_lo = SOC15_REG_OFFSET(OSSSYS, 0, mmIH_RB_WPTR_ADDR_LO);
		ih_regs->ih_rb_wptr_addr_hi = SOC15_REG_OFFSET(OSSSYS, 0, mmIH_RB_WPTR_ADDR_HI);
		ih_regs->psp_reg_id = PSP_REG_IH_RB_CNTL;
	पूर्ण

	अगर (adev->irq.ih1.ring_size) अणु
		ih_regs = &adev->irq.ih1.ih_regs;
		ih_regs->ih_rb_base = SOC15_REG_OFFSET(OSSSYS, 0, mmIH_RB_BASE_RING1);
		ih_regs->ih_rb_base_hi = SOC15_REG_OFFSET(OSSSYS, 0, mmIH_RB_BASE_HI_RING1);
		ih_regs->ih_rb_cntl = SOC15_REG_OFFSET(OSSSYS, 0, mmIH_RB_CNTL_RING1);
		ih_regs->ih_rb_wptr = SOC15_REG_OFFSET(OSSSYS, 0, mmIH_RB_WPTR_RING1);
		ih_regs->ih_rb_rptr = SOC15_REG_OFFSET(OSSSYS, 0, mmIH_RB_RPTR_RING1);
		ih_regs->ih_करोorbell_rptr = SOC15_REG_OFFSET(OSSSYS, 0, mmIH_DOORBELL_RPTR_RING1);
		ih_regs->psp_reg_id = PSP_REG_IH_RB_CNTL_RING1;
	पूर्ण

	अगर (adev->irq.ih2.ring_size) अणु
		ih_regs = &adev->irq.ih2.ih_regs;
		ih_regs->ih_rb_base = SOC15_REG_OFFSET(OSSSYS, 0, mmIH_RB_BASE_RING2);
		ih_regs->ih_rb_base_hi = SOC15_REG_OFFSET(OSSSYS, 0, mmIH_RB_BASE_HI_RING2);
		ih_regs->ih_rb_cntl = SOC15_REG_OFFSET(OSSSYS, 0, mmIH_RB_CNTL_RING2);
		ih_regs->ih_rb_wptr = SOC15_REG_OFFSET(OSSSYS, 0, mmIH_RB_WPTR_RING2);
		ih_regs->ih_rb_rptr = SOC15_REG_OFFSET(OSSSYS, 0, mmIH_RB_RPTR_RING2);
		ih_regs->ih_करोorbell_rptr = SOC15_REG_OFFSET(OSSSYS, 0, mmIH_DOORBELL_RPTR_RING2);
		ih_regs->psp_reg_id = PSP_REG_IH_RB_CNTL_RING2;
	पूर्ण
पूर्ण

/**
 * क्रमce_update_wptr_क्रम_self_पूर्णांक - Force update the wptr क्रम self पूर्णांकerrupt
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @threshold: threshold to trigger the wptr reporting
 * @समयout: समयout to trigger the wptr reporting
 * @enabled: Enable/disable समयout flush mechanism
 *
 * threshold input range: 0 ~ 15, शेष 0,
 * real_threshold = 2^threshold
 * समयout input range: 0 ~ 20, शेष 8,
 * real_समयout = (2^समयout) * 1024 / (socclk_freq)
 *
 * Force update wptr क्रम self पूर्णांकerrupt ( >= SIENNA_CICHLID).
 */
अटल व्योम
क्रमce_update_wptr_क्रम_self_पूर्णांक(काष्ठा amdgpu_device *adev,
			       u32 threshold, u32 समयout, bool enabled)
अणु
	u32 ih_cntl, ih_rb_cntl;

	अगर (adev->asic_type < CHIP_SIENNA_CICHLID)
		वापस;

	ih_cntl = RREG32_SOC15(OSSSYS, 0, mmIH_CNTL2);
	ih_rb_cntl = RREG32_SOC15(OSSSYS, 0, mmIH_RB_CNTL_RING1);

	ih_cntl = REG_SET_FIELD(ih_cntl, IH_CNTL2,
				SELF_IV_FORCE_WPTR_UPDATE_TIMEOUT, समयout);
	ih_cntl = REG_SET_FIELD(ih_cntl, IH_CNTL2,
				SELF_IV_FORCE_WPTR_UPDATE_ENABLE, enabled);
	ih_rb_cntl = REG_SET_FIELD(ih_rb_cntl, IH_RB_CNTL_RING1,
				   RB_USED_INT_THRESHOLD, threshold);

	WREG32_SOC15(OSSSYS, 0, mmIH_RB_CNTL_RING1, ih_rb_cntl);
	ih_rb_cntl = RREG32_SOC15(OSSSYS, 0, mmIH_RB_CNTL_RING2);
	ih_rb_cntl = REG_SET_FIELD(ih_rb_cntl, IH_RB_CNTL_RING2,
				   RB_USED_INT_THRESHOLD, threshold);
	WREG32_SOC15(OSSSYS, 0, mmIH_RB_CNTL_RING2, ih_rb_cntl);
	WREG32_SOC15(OSSSYS, 0, mmIH_CNTL2, ih_cntl);
पूर्ण

/**
 * navi10_ih_toggle_ring_पूर्णांकerrupts - toggle the पूर्णांकerrupt ring buffer
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @ih: amdgpu_ih_ring poपूर्णांकet
 * @enable: true - enable the पूर्णांकerrupts, false - disable the पूर्णांकerrupts
 *
 * Toggle the पूर्णांकerrupt ring buffer (NAVI10)
 */
अटल पूर्णांक navi10_ih_toggle_ring_पूर्णांकerrupts(काष्ठा amdgpu_device *adev,
					    काष्ठा amdgpu_ih_ring *ih,
					    bool enable)
अणु
	काष्ठा amdgpu_ih_regs *ih_regs;
	uपूर्णांक32_t पंचांगp;

	ih_regs = &ih->ih_regs;

	पंचांगp = RREG32(ih_regs->ih_rb_cntl);
	पंचांगp = REG_SET_FIELD(पंचांगp, IH_RB_CNTL, RB_ENABLE, (enable ? 1 : 0));
	/* enable_पूर्णांकr field is only valid in ring0 */
	अगर (ih == &adev->irq.ih)
		पंचांगp = REG_SET_FIELD(पंचांगp, IH_RB_CNTL, ENABLE_INTR, (enable ? 1 : 0));
	WREG32(ih_regs->ih_rb_cntl, पंचांगp);

	अगर (enable) अणु
		ih->enabled = true;
	पूर्ण अन्यथा अणु
		/* set rptr, wptr to 0 */
		WREG32(ih_regs->ih_rb_rptr, 0);
		WREG32(ih_regs->ih_rb_wptr, 0);
		ih->enabled = false;
		ih->rptr = 0;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * navi10_ih_toggle_पूर्णांकerrupts - Toggle all the available पूर्णांकerrupt ring buffers
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @enable: enable or disable पूर्णांकerrupt ring buffers
 *
 * Toggle all the available पूर्णांकerrupt ring buffers (NAVI10).
 */
अटल पूर्णांक navi10_ih_toggle_पूर्णांकerrupts(काष्ठा amdgpu_device *adev, bool enable)
अणु
	काष्ठा amdgpu_ih_ring *ih[] = अणु&adev->irq.ih, &adev->irq.ih1, &adev->irq.ih2पूर्ण;
	पूर्णांक i;
	पूर्णांक r;

	क्रम (i = 0; i < ARRAY_SIZE(ih); i++) अणु
		अगर (ih[i]->ring_size) अणु
			r = navi10_ih_toggle_ring_पूर्णांकerrupts(adev, ih[i], enable);
			अगर (r)
				वापस r;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल uपूर्णांक32_t navi10_ih_rb_cntl(काष्ठा amdgpu_ih_ring *ih, uपूर्णांक32_t ih_rb_cntl)
अणु
	पूर्णांक rb_bufsz = order_base_2(ih->ring_size / 4);

	ih_rb_cntl = REG_SET_FIELD(ih_rb_cntl, IH_RB_CNTL,
				   MC_SPACE, ih->use_bus_addr ? 1 : 4);
	ih_rb_cntl = REG_SET_FIELD(ih_rb_cntl, IH_RB_CNTL,
				   WPTR_OVERFLOW_CLEAR, 1);
	ih_rb_cntl = REG_SET_FIELD(ih_rb_cntl, IH_RB_CNTL,
				   WPTR_OVERFLOW_ENABLE, 1);
	ih_rb_cntl = REG_SET_FIELD(ih_rb_cntl, IH_RB_CNTL, RB_SIZE, rb_bufsz);
	/* Ring Buffer ग_लिखो poपूर्णांकer ग_लिखोback. If enabled, IH_RB_WPTR रेजिस्टर
	 * value is written to memory
	 */
	ih_rb_cntl = REG_SET_FIELD(ih_rb_cntl, IH_RB_CNTL,
				   WPTR_WRITEBACK_ENABLE, 1);
	ih_rb_cntl = REG_SET_FIELD(ih_rb_cntl, IH_RB_CNTL, MC_SNOOP, 1);
	ih_rb_cntl = REG_SET_FIELD(ih_rb_cntl, IH_RB_CNTL, MC_RO, 0);
	ih_rb_cntl = REG_SET_FIELD(ih_rb_cntl, IH_RB_CNTL, MC_VMID, 0);

	वापस ih_rb_cntl;
पूर्ण

अटल uपूर्णांक32_t navi10_ih_करोorbell_rptr(काष्ठा amdgpu_ih_ring *ih)
अणु
	u32 ih_करोorbell_rtpr = 0;

	अगर (ih->use_करोorbell) अणु
		ih_करोorbell_rtpr = REG_SET_FIELD(ih_करोorbell_rtpr,
						 IH_DOORBELL_RPTR, OFFSET,
						 ih->करोorbell_index);
		ih_करोorbell_rtpr = REG_SET_FIELD(ih_करोorbell_rtpr,
						 IH_DOORBELL_RPTR,
						 ENABLE, 1);
	पूर्ण अन्यथा अणु
		ih_करोorbell_rtpr = REG_SET_FIELD(ih_करोorbell_rtpr,
						 IH_DOORBELL_RPTR,
						 ENABLE, 0);
	पूर्ण
	वापस ih_करोorbell_rtpr;
पूर्ण

/**
 * navi10_ih_enable_ring - enable an ih ring buffer
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @ih: amdgpu_ih_ring poपूर्णांकer
 *
 * Enable an ih ring buffer (NAVI10)
 */
अटल पूर्णांक navi10_ih_enable_ring(काष्ठा amdgpu_device *adev,
				 काष्ठा amdgpu_ih_ring *ih)
अणु
	काष्ठा amdgpu_ih_regs *ih_regs;
	uपूर्णांक32_t पंचांगp;

	ih_regs = &ih->ih_regs;

	/* Ring Buffer base. [39:8] of 40-bit address of the beginning of the ring buffer*/
	WREG32(ih_regs->ih_rb_base, ih->gpu_addr >> 8);
	WREG32(ih_regs->ih_rb_base_hi, (ih->gpu_addr >> 40) & 0xff);

	पंचांगp = RREG32(ih_regs->ih_rb_cntl);
	पंचांगp = navi10_ih_rb_cntl(ih, पंचांगp);
	अगर (ih == &adev->irq.ih)
		पंचांगp = REG_SET_FIELD(पंचांगp, IH_RB_CNTL, RPTR_REARM, !!adev->irq.msi_enabled);
	अगर (ih == &adev->irq.ih1) अणु
		पंचांगp = REG_SET_FIELD(पंचांगp, IH_RB_CNTL, WPTR_OVERFLOW_ENABLE, 0);
		पंचांगp = REG_SET_FIELD(पंचांगp, IH_RB_CNTL, RB_FULL_DRAIN_ENABLE, 1);
	पूर्ण
	WREG32(ih_regs->ih_rb_cntl, पंचांगp);

	अगर (ih == &adev->irq.ih) अणु
		/* set the ih ring 0 ग_लिखोback address whether it's enabled or not */
		WREG32(ih_regs->ih_rb_wptr_addr_lo, lower_32_bits(ih->wptr_addr));
		WREG32(ih_regs->ih_rb_wptr_addr_hi, upper_32_bits(ih->wptr_addr) & 0xFFFF);
	पूर्ण

	/* set rptr, wptr to 0 */
	WREG32(ih_regs->ih_rb_wptr, 0);
	WREG32(ih_regs->ih_rb_rptr, 0);

	WREG32(ih_regs->ih_करोorbell_rptr, navi10_ih_करोorbell_rptr(ih));

	वापस 0;
पूर्ण

/**
 * navi10_ih_irq_init - init and enable the पूर्णांकerrupt ring
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Allocate a ring buffer क्रम the पूर्णांकerrupt controller,
 * enable the RLC, disable पूर्णांकerrupts, enable the IH
 * ring buffer and enable it (NAVI).
 * Called at device load and reume.
 * Returns 0 क्रम success, errors क्रम failure.
 */
अटल पूर्णांक navi10_ih_irq_init(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_ih_ring *ih[] = अणु&adev->irq.ih, &adev->irq.ih1, &adev->irq.ih2पूर्ण;
	u32 ih_chicken;
	u32 पंचांगp;
	पूर्णांक ret;
	पूर्णांक i;

	/* disable irqs */
	ret = navi10_ih_toggle_पूर्णांकerrupts(adev, false);
	अगर (ret)
		वापस ret;

	adev->nbio.funcs->ih_control(adev);

	अगर (unlikely(adev->firmware.load_type == AMDGPU_FW_LOAD_सूचीECT)) अणु
		अगर (ih[0]->use_bus_addr) अणु
			चयन (adev->asic_type) अणु
			हाल CHIP_SIENNA_CICHLID:
			हाल CHIP_NAVY_FLOUNDER:
			हाल CHIP_VANGOGH:
			हाल CHIP_DIMGREY_CAVEFISH:
				ih_chicken = RREG32_SOC15(OSSSYS, 0, mmIH_CHICKEN_Sienna_Cichlid);
				ih_chicken = REG_SET_FIELD(ih_chicken,
						IH_CHICKEN, MC_SPACE_GPA_ENABLE, 1);
				WREG32_SOC15(OSSSYS, 0, mmIH_CHICKEN_Sienna_Cichlid, ih_chicken);
				अवरोध;
			शेष:
				ih_chicken = RREG32_SOC15(OSSSYS, 0, mmIH_CHICKEN);
				ih_chicken = REG_SET_FIELD(ih_chicken,
						IH_CHICKEN, MC_SPACE_GPA_ENABLE, 1);
				WREG32_SOC15(OSSSYS, 0, mmIH_CHICKEN, ih_chicken);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(ih); i++) अणु
		अगर (ih[i]->ring_size) अणु
			ret = navi10_ih_enable_ring(adev, ih[i]);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	/* update करोorbell range क्रम ih ring 0*/
	adev->nbio.funcs->ih_करोorbell_range(adev, ih[0]->use_करोorbell,
					    ih[0]->करोorbell_index);

	पंचांगp = RREG32_SOC15(OSSSYS, 0, mmIH_STORM_CLIENT_LIST_CNTL);
	पंचांगp = REG_SET_FIELD(पंचांगp, IH_STORM_CLIENT_LIST_CNTL,
			    CLIENT18_IS_STORM_CLIENT, 1);
	WREG32_SOC15(OSSSYS, 0, mmIH_STORM_CLIENT_LIST_CNTL, पंचांगp);

	पंचांगp = RREG32_SOC15(OSSSYS, 0, mmIH_INT_FLOOD_CNTL);
	पंचांगp = REG_SET_FIELD(पंचांगp, IH_INT_FLOOD_CNTL, FLOOD_CNTL_ENABLE, 1);
	WREG32_SOC15(OSSSYS, 0, mmIH_INT_FLOOD_CNTL, पंचांगp);

	pci_set_master(adev->pdev);

	/* enable पूर्णांकerrupts */
	ret = navi10_ih_toggle_पूर्णांकerrupts(adev, true);
	अगर (ret)
		वापस ret;
	/* enable wptr क्रमce update क्रम self पूर्णांक */
	क्रमce_update_wptr_क्रम_self_पूर्णांक(adev, 0, 8, true);

	अगर (adev->irq.ih_soft.ring_size)
		adev->irq.ih_soft.enabled = true;

	वापस 0;
पूर्ण

/**
 * navi10_ih_irq_disable - disable पूर्णांकerrupts
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Disable पूर्णांकerrupts on the hw (NAVI10).
 */
अटल व्योम navi10_ih_irq_disable(काष्ठा amdgpu_device *adev)
अणु
	क्रमce_update_wptr_क्रम_self_पूर्णांक(adev, 0, 8, false);
	navi10_ih_toggle_पूर्णांकerrupts(adev, false);

	/* Wait and acknowledge irq */
	mdelay(1);
पूर्ण

/**
 * navi10_ih_get_wptr - get the IH ring buffer wptr
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @ih: IH ring buffer to fetch wptr
 *
 * Get the IH ring buffer wptr from either the रेजिस्टर
 * or the ग_लिखोback memory buffer (NAVI10).  Also check क्रम
 * ring buffer overflow and deal with it.
 * Returns the value of the wptr.
 */
अटल u32 navi10_ih_get_wptr(काष्ठा amdgpu_device *adev,
			      काष्ठा amdgpu_ih_ring *ih)
अणु
	u32 wptr, पंचांगp;
	काष्ठा amdgpu_ih_regs *ih_regs;

	wptr = le32_to_cpu(*ih->wptr_cpu);
	ih_regs = &ih->ih_regs;

	अगर (!REG_GET_FIELD(wptr, IH_RB_WPTR, RB_OVERFLOW))
		जाओ out;

	wptr = RREG32_NO_KIQ(ih_regs->ih_rb_wptr);
	अगर (!REG_GET_FIELD(wptr, IH_RB_WPTR, RB_OVERFLOW))
		जाओ out;
	wptr = REG_SET_FIELD(wptr, IH_RB_WPTR, RB_OVERFLOW, 0);

	/* When a ring buffer overflow happen start parsing पूर्णांकerrupt
	 * from the last not overwritten vector (wptr + 32). Hopefully
	 * this should allow us to catch up.
	 */
	पंचांगp = (wptr + 32) & ih->ptr_mask;
	dev_warn(adev->dev, "IH ring buffer overflow "
		 "(0x%08X, 0x%08X, 0x%08X)\n",
		 wptr, ih->rptr, पंचांगp);
	ih->rptr = पंचांगp;

	पंचांगp = RREG32_NO_KIQ(ih_regs->ih_rb_cntl);
	पंचांगp = REG_SET_FIELD(पंचांगp, IH_RB_CNTL, WPTR_OVERFLOW_CLEAR, 1);
	WREG32_NO_KIQ(ih_regs->ih_rb_cntl, पंचांगp);
out:
	वापस (wptr & ih->ptr_mask);
पूर्ण

/**
 * navi10_ih_irq_rearm - rearm IRQ अगर lost
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @ih: IH ring to match
 *
 */
अटल व्योम navi10_ih_irq_rearm(काष्ठा amdgpu_device *adev,
			       काष्ठा amdgpu_ih_ring *ih)
अणु
	uपूर्णांक32_t v = 0;
	uपूर्णांक32_t i = 0;
	काष्ठा amdgpu_ih_regs *ih_regs;

	ih_regs = &ih->ih_regs;

	/* Rearm IRQ / re-ग_लिखो करोorbell अगर करोorbell ग_लिखो is lost */
	क्रम (i = 0; i < MAX_REARM_RETRY; i++) अणु
		v = RREG32_NO_KIQ(ih_regs->ih_rb_rptr);
		अगर ((v < ih->ring_size) && (v != ih->rptr))
			WDOORBELL32(ih->करोorbell_index, ih->rptr);
		अन्यथा
			अवरोध;
	पूर्ण
पूर्ण

/**
 * navi10_ih_set_rptr - set the IH ring buffer rptr
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * @ih: IH ring buffer to set rptr
 * Set the IH ring buffer rptr.
 */
अटल व्योम navi10_ih_set_rptr(काष्ठा amdgpu_device *adev,
			       काष्ठा amdgpu_ih_ring *ih)
अणु
	काष्ठा amdgpu_ih_regs *ih_regs;

	अगर (ih->use_करोorbell) अणु
		/* XXX check अगर swapping is necessary on BE */
		*ih->rptr_cpu = ih->rptr;
		WDOORBELL32(ih->करोorbell_index, ih->rptr);

		अगर (amdgpu_sriov_vf(adev))
			navi10_ih_irq_rearm(adev, ih);
	पूर्ण अन्यथा अणु
		ih_regs = &ih->ih_regs;
		WREG32(ih_regs->ih_rb_rptr, ih->rptr);
	पूर्ण
पूर्ण

/**
 * navi10_ih_self_irq - dispatch work क्रम ring 1 and 2
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @source: irq source
 * @entry: IV with WPTR update
 *
 * Update the WPTR from the IV and schedule work to handle the entries.
 */
अटल पूर्णांक navi10_ih_self_irq(काष्ठा amdgpu_device *adev,
			      काष्ठा amdgpu_irq_src *source,
			      काष्ठा amdgpu_iv_entry *entry)
अणु
	uपूर्णांक32_t wptr = cpu_to_le32(entry->src_data[0]);

	चयन (entry->ring_id) अणु
	हाल 1:
		*adev->irq.ih1.wptr_cpu = wptr;
		schedule_work(&adev->irq.ih1_work);
		अवरोध;
	हाल 2:
		*adev->irq.ih2.wptr_cpu = wptr;
		schedule_work(&adev->irq.ih2_work);
		अवरोध;
	शेष: अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा amdgpu_irq_src_funcs navi10_ih_self_irq_funcs = अणु
	.process = navi10_ih_self_irq,
पूर्ण;

अटल व्योम navi10_ih_set_self_irq_funcs(काष्ठा amdgpu_device *adev)
अणु
	adev->irq.self_irq.num_types = 0;
	adev->irq.self_irq.funcs = &navi10_ih_self_irq_funcs;
पूर्ण

अटल पूर्णांक navi10_ih_early_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	navi10_ih_set_पूर्णांकerrupt_funcs(adev);
	navi10_ih_set_self_irq_funcs(adev);
	वापस 0;
पूर्ण

अटल पूर्णांक navi10_ih_sw_init(व्योम *handle)
अणु
	पूर्णांक r;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	bool use_bus_addr;

	r = amdgpu_irq_add_id(adev, SOC15_IH_CLIENTID_IH, 0,
				&adev->irq.self_irq);

	अगर (r)
		वापस r;

	/* use gpu भव address क्रम ih ring
	 * until ih_checken is programmed to allow
	 * use bus address क्रम ih ring by psp bl */
	अगर ((adev->flags & AMD_IS_APU) ||
	    (adev->firmware.load_type == AMDGPU_FW_LOAD_PSP))
		use_bus_addr = false;
	अन्यथा
		use_bus_addr = true;
	r = amdgpu_ih_ring_init(adev, &adev->irq.ih, 256 * 1024, use_bus_addr);
	अगर (r)
		वापस r;

	adev->irq.ih.use_करोorbell = true;
	adev->irq.ih.करोorbell_index = adev->करोorbell_index.ih << 1;

	adev->irq.ih1.ring_size = 0;
	adev->irq.ih2.ring_size = 0;

	/* initialize ih control रेजिस्टरs offset */
	navi10_ih_init_रेजिस्टर_offset(adev);

	r = amdgpu_ih_ring_init(adev, &adev->irq.ih_soft, PAGE_SIZE, true);
	अगर (r)
		वापस r;

	r = amdgpu_irq_init(adev);

	वापस r;
पूर्ण

अटल पूर्णांक navi10_ih_sw_fini(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	amdgpu_irq_fini(adev);
	amdgpu_ih_ring_fini(adev, &adev->irq.ih_soft);
	amdgpu_ih_ring_fini(adev, &adev->irq.ih2);
	amdgpu_ih_ring_fini(adev, &adev->irq.ih1);
	amdgpu_ih_ring_fini(adev, &adev->irq.ih);

	वापस 0;
पूर्ण

अटल पूर्णांक navi10_ih_hw_init(व्योम *handle)
अणु
	पूर्णांक r;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	r = navi10_ih_irq_init(adev);
	अगर (r)
		वापस r;

	वापस 0;
पूर्ण

अटल पूर्णांक navi10_ih_hw_fini(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	navi10_ih_irq_disable(adev);

	वापस 0;
पूर्ण

अटल पूर्णांक navi10_ih_suspend(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	वापस navi10_ih_hw_fini(adev);
पूर्ण

अटल पूर्णांक navi10_ih_resume(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	वापस navi10_ih_hw_init(adev);
पूर्ण

अटल bool navi10_ih_is_idle(व्योम *handle)
अणु
	/* toकरो */
	वापस true;
पूर्ण

अटल पूर्णांक navi10_ih_रुको_क्रम_idle(व्योम *handle)
अणु
	/* toकरो */
	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक navi10_ih_soft_reset(व्योम *handle)
अणु
	/* toकरो */
	वापस 0;
पूर्ण

अटल व्योम navi10_ih_update_घड़ीgating_state(काष्ठा amdgpu_device *adev,
					       bool enable)
अणु
	uपूर्णांक32_t data, def, field_val;

	अगर (adev->cg_flags & AMD_CG_SUPPORT_IH_CG) अणु
		def = data = RREG32_SOC15(OSSSYS, 0, mmIH_CLK_CTRL);
		field_val = enable ? 0 : 1;
		data = REG_SET_FIELD(data, IH_CLK_CTRL,
				     DBUS_MUX_CLK_SOFT_OVERRIDE, field_val);
		data = REG_SET_FIELD(data, IH_CLK_CTRL,
				     OSSSYS_SHARE_CLK_SOFT_OVERRIDE, field_val);
		data = REG_SET_FIELD(data, IH_CLK_CTRL,
				     LIMIT_SMN_CLK_SOFT_OVERRIDE, field_val);
		data = REG_SET_FIELD(data, IH_CLK_CTRL,
				     DYN_CLK_SOFT_OVERRIDE, field_val);
		data = REG_SET_FIELD(data, IH_CLK_CTRL,
				     REG_CLK_SOFT_OVERRIDE, field_val);
		अगर (def != data)
			WREG32_SOC15(OSSSYS, 0, mmIH_CLK_CTRL, data);
	पूर्ण

	वापस;
पूर्ण

अटल पूर्णांक navi10_ih_set_घड़ीgating_state(व्योम *handle,
					   क्रमागत amd_घड़ीgating_state state)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	navi10_ih_update_घड़ीgating_state(adev,
				state == AMD_CG_STATE_GATE);
	वापस 0;
पूर्ण

अटल पूर्णांक navi10_ih_set_घातergating_state(व्योम *handle,
					   क्रमागत amd_घातergating_state state)
अणु
	वापस 0;
पूर्ण

अटल व्योम navi10_ih_get_घड़ीgating_state(व्योम *handle, u32 *flags)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	अगर (!RREG32_SOC15(OSSSYS, 0, mmIH_CLK_CTRL))
		*flags |= AMD_CG_SUPPORT_IH_CG;

	वापस;
पूर्ण

अटल स्थिर काष्ठा amd_ip_funcs navi10_ih_ip_funcs = अणु
	.name = "navi10_ih",
	.early_init = navi10_ih_early_init,
	.late_init = शून्य,
	.sw_init = navi10_ih_sw_init,
	.sw_fini = navi10_ih_sw_fini,
	.hw_init = navi10_ih_hw_init,
	.hw_fini = navi10_ih_hw_fini,
	.suspend = navi10_ih_suspend,
	.resume = navi10_ih_resume,
	.is_idle = navi10_ih_is_idle,
	.रुको_क्रम_idle = navi10_ih_रुको_क्रम_idle,
	.soft_reset = navi10_ih_soft_reset,
	.set_घड़ीgating_state = navi10_ih_set_घड़ीgating_state,
	.set_घातergating_state = navi10_ih_set_घातergating_state,
	.get_घड़ीgating_state = navi10_ih_get_घड़ीgating_state,
पूर्ण;

अटल स्थिर काष्ठा amdgpu_ih_funcs navi10_ih_funcs = अणु
	.get_wptr = navi10_ih_get_wptr,
	.decode_iv = amdgpu_ih_decode_iv_helper,
	.set_rptr = navi10_ih_set_rptr
पूर्ण;

अटल व्योम navi10_ih_set_पूर्णांकerrupt_funcs(काष्ठा amdgpu_device *adev)
अणु
	अगर (adev->irq.ih_funcs == शून्य)
		adev->irq.ih_funcs = &navi10_ih_funcs;
पूर्ण

स्थिर काष्ठा amdgpu_ip_block_version navi10_ih_ip_block =
अणु
	.type = AMD_IP_BLOCK_TYPE_IH,
	.major = 5,
	.minor = 0,
	.rev = 0,
	.funcs = &navi10_ih_ip_funcs,
पूर्ण;
