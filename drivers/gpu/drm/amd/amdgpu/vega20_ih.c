<शैली गुरु>
/*
 * Copyright 2020 Advanced Micro Devices, Inc.
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
#समावेश "soc15.h"

#समावेश "oss/osssys_4_2_0_offset.h"
#समावेश "oss/osssys_4_2_0_sh_mask.h"

#समावेश "soc15_common.h"
#समावेश "vega20_ih.h"

#घोषणा MAX_REARM_RETRY 10

#घोषणा mmIH_CHICKEN_ALDEBARAN			0x18d
#घोषणा mmIH_CHICKEN_ALDEBARAN_BASE_IDX		0

अटल व्योम vega20_ih_set_पूर्णांकerrupt_funcs(काष्ठा amdgpu_device *adev);

/**
 * vega20_ih_init_रेजिस्टर_offset - Initialize रेजिस्टर offset क्रम ih rings
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Initialize रेजिस्टर offset ih rings (VEGA20).
 */
अटल व्योम vega20_ih_init_रेजिस्टर_offset(काष्ठा amdgpu_device *adev)
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
 * vega20_ih_toggle_ring_पूर्णांकerrupts - toggle the पूर्णांकerrupt ring buffer
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @ih: amdgpu_ih_ring poपूर्णांकer
 * @enable: true - enable the पूर्णांकerrupts, false - disable the पूर्णांकerrupts
 *
 * Toggle the पूर्णांकerrupt ring buffer (VEGA20)
 */
अटल पूर्णांक vega20_ih_toggle_ring_पूर्णांकerrupts(काष्ठा amdgpu_device *adev,
					    काष्ठा amdgpu_ih_ring *ih,
					    bool enable)
अणु
	काष्ठा amdgpu_ih_regs *ih_regs;
	uपूर्णांक32_t पंचांगp;

	ih_regs = &ih->ih_regs;

	पंचांगp = RREG32(ih_regs->ih_rb_cntl);
	पंचांगp = REG_SET_FIELD(पंचांगp, IH_RB_CNTL, RB_ENABLE, (enable ? 1 : 0));
	पंचांगp = REG_SET_FIELD(पंचांगp, IH_RB_CNTL, RB_GPU_TS_ENABLE, 1);

	/* enable_पूर्णांकr field is only valid in ring0 */
	अगर (ih == &adev->irq.ih)
		पंचांगp = REG_SET_FIELD(पंचांगp, IH_RB_CNTL, ENABLE_INTR, (enable ? 1 : 0));
	अगर (amdgpu_sriov_vf(adev)) अणु
		अगर (psp_reg_program(&adev->psp, ih_regs->psp_reg_id, पंचांगp)) अणु
			dev_err(adev->dev, "PSP program IH_RB_CNTL failed!\n");
			वापस -ETIMEDOUT;
		पूर्ण
	पूर्ण अन्यथा अणु
		WREG32(ih_regs->ih_rb_cntl, पंचांगp);
	पूर्ण

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
 * vega20_ih_toggle_पूर्णांकerrupts - Toggle all the available पूर्णांकerrupt ring buffers
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @enable: enable or disable पूर्णांकerrupt ring buffers
 *
 * Toggle all the available पूर्णांकerrupt ring buffers (VEGA20).
 */
अटल पूर्णांक vega20_ih_toggle_पूर्णांकerrupts(काष्ठा amdgpu_device *adev, bool enable)
अणु
	काष्ठा amdgpu_ih_ring *ih[] = अणु&adev->irq.ih, &adev->irq.ih1, &adev->irq.ih2पूर्ण;
	पूर्णांक i;
	पूर्णांक r;

	क्रम (i = 0; i < ARRAY_SIZE(ih); i++) अणु
		अगर (ih[i]->ring_size) अणु
			r = vega20_ih_toggle_ring_पूर्णांकerrupts(adev, ih[i], enable);
			अगर (r)
				वापस r;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल uपूर्णांक32_t vega20_ih_rb_cntl(काष्ठा amdgpu_ih_ring *ih, uपूर्णांक32_t ih_rb_cntl)
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

अटल uपूर्णांक32_t vega20_ih_करोorbell_rptr(काष्ठा amdgpu_ih_ring *ih)
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
 * vega20_ih_enable_ring - enable an ih ring buffer
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @ih: amdgpu_ih_ring poपूर्णांकer
 *
 * Enable an ih ring buffer (VEGA20)
 */
अटल पूर्णांक vega20_ih_enable_ring(काष्ठा amdgpu_device *adev,
				 काष्ठा amdgpu_ih_ring *ih)
अणु
	काष्ठा amdgpu_ih_regs *ih_regs;
	uपूर्णांक32_t पंचांगp;

	ih_regs = &ih->ih_regs;

	/* Ring Buffer base. [39:8] of 40-bit address of the beginning of the ring buffer*/
	WREG32(ih_regs->ih_rb_base, ih->gpu_addr >> 8);
	WREG32(ih_regs->ih_rb_base_hi, (ih->gpu_addr >> 40) & 0xff);

	पंचांगp = RREG32(ih_regs->ih_rb_cntl);
	पंचांगp = vega20_ih_rb_cntl(ih, पंचांगp);
	अगर (ih == &adev->irq.ih)
		पंचांगp = REG_SET_FIELD(पंचांगp, IH_RB_CNTL, RPTR_REARM, !!adev->irq.msi_enabled);
	अगर (ih == &adev->irq.ih1)
		पंचांगp = REG_SET_FIELD(पंचांगp, IH_RB_CNTL, RB_FULL_DRAIN_ENABLE, 1);
	अगर (amdgpu_sriov_vf(adev)) अणु
		अगर (psp_reg_program(&adev->psp, ih_regs->psp_reg_id, पंचांगp)) अणु
			dev_err(adev->dev, "PSP program IH_RB_CNTL failed!\n");
			वापस -ETIMEDOUT;
		पूर्ण
	पूर्ण अन्यथा अणु
		WREG32(ih_regs->ih_rb_cntl, पंचांगp);
	पूर्ण

	अगर (ih == &adev->irq.ih) अणु
		/* set the ih ring 0 ग_लिखोback address whether it's enabled or not */
		WREG32(ih_regs->ih_rb_wptr_addr_lo, lower_32_bits(ih->wptr_addr));
		WREG32(ih_regs->ih_rb_wptr_addr_hi, upper_32_bits(ih->wptr_addr) & 0xFFFF);
	पूर्ण

	/* set rptr, wptr to 0 */
	WREG32(ih_regs->ih_rb_wptr, 0);
	WREG32(ih_regs->ih_rb_rptr, 0);

	WREG32(ih_regs->ih_करोorbell_rptr, vega20_ih_करोorbell_rptr(ih));

	वापस 0;
पूर्ण

/**
 * vega20_ih_reroute_ih - reroute VMC/UTCL2 ih to an ih ring
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Reroute VMC and UMC पूर्णांकerrupts on primary ih ring to
 * ih ring 1 so they won't lose when bunches of page faults
 * पूर्णांकerrupts overwhelms the पूर्णांकerrupt handler(VEGA20)
 */
अटल व्योम vega20_ih_reroute_ih(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक32_t पंचांगp;

	/* vega20 ih reroute will go through psp this
	 * function is used क्रम newer asics starting arcturus
	 */
	अगर (adev->asic_type >= CHIP_ARCTURUS) अणु
		/* Reroute to IH ring 1 क्रम VMC */
		WREG32_SOC15(OSSSYS, 0, mmIH_CLIENT_CFG_INDEX, 0x12);
		पंचांगp = RREG32_SOC15(OSSSYS, 0, mmIH_CLIENT_CFG_DATA);
		पंचांगp = REG_SET_FIELD(पंचांगp, IH_CLIENT_CFG_DATA, CLIENT_TYPE, 1);
		पंचांगp = REG_SET_FIELD(पंचांगp, IH_CLIENT_CFG_DATA, RING_ID, 1);
		WREG32_SOC15(OSSSYS, 0, mmIH_CLIENT_CFG_DATA, पंचांगp);

		/* Reroute IH ring 1 क्रम UTCL2 */
		WREG32_SOC15(OSSSYS, 0, mmIH_CLIENT_CFG_INDEX, 0x1B);
		पंचांगp = RREG32_SOC15(OSSSYS, 0, mmIH_CLIENT_CFG_DATA);
		पंचांगp = REG_SET_FIELD(पंचांगp, IH_CLIENT_CFG_DATA, RING_ID, 1);
		WREG32_SOC15(OSSSYS, 0, mmIH_CLIENT_CFG_DATA, पंचांगp);
	पूर्ण
पूर्ण

/**
 * vega20_ih_irq_init - init and enable the पूर्णांकerrupt ring
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Allocate a ring buffer क्रम the पूर्णांकerrupt controller,
 * enable the RLC, disable पूर्णांकerrupts, enable the IH
 * ring buffer and enable it (VI).
 * Called at device load and reume.
 * Returns 0 क्रम success, errors क्रम failure.
 */
अटल पूर्णांक vega20_ih_irq_init(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_ih_ring *ih[] = अणु&adev->irq.ih, &adev->irq.ih1, &adev->irq.ih2पूर्ण;
	u32 ih_chicken;
	पूर्णांक ret;
	पूर्णांक i;

	/* disable irqs */
	ret = vega20_ih_toggle_पूर्णांकerrupts(adev, false);
	अगर (ret)
		वापस ret;

	adev->nbio.funcs->ih_control(adev);

	अगर (adev->asic_type == CHIP_ARCTURUS &&
	    adev->firmware.load_type == AMDGPU_FW_LOAD_सूचीECT) अणु
		ih_chicken = RREG32_SOC15(OSSSYS, 0, mmIH_CHICKEN);
		अगर (adev->irq.ih.use_bus_addr) अणु
			ih_chicken = REG_SET_FIELD(ih_chicken, IH_CHICKEN,
						   MC_SPACE_GPA_ENABLE, 1);
		पूर्ण
		WREG32_SOC15(OSSSYS, 0, mmIH_CHICKEN, ih_chicken);
	पूर्ण

	/* psp firmware won't program IH_CHICKEN क्रम aldebaran
	 * driver needs to program it properly according to
	 * MC_SPACE type in IH_RB_CNTL */
	अगर (adev->asic_type == CHIP_ALDEBARAN) अणु
		ih_chicken = RREG32_SOC15(OSSSYS, 0, mmIH_CHICKEN_ALDEBARAN);
		अगर (adev->irq.ih.use_bus_addr) अणु
			ih_chicken = REG_SET_FIELD(ih_chicken, IH_CHICKEN,
						   MC_SPACE_GPA_ENABLE, 1);
		पूर्ण
		WREG32_SOC15(OSSSYS, 0, mmIH_CHICKEN_ALDEBARAN, ih_chicken);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(ih); i++) अणु
		अगर (ih[i]->ring_size) अणु
			अगर (i == 1)
				vega20_ih_reroute_ih(adev);
			ret = vega20_ih_enable_ring(adev, ih[i]);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	pci_set_master(adev->pdev);

	/* enable पूर्णांकerrupts */
	ret = vega20_ih_toggle_पूर्णांकerrupts(adev, true);
	अगर (ret)
		वापस ret;

	अगर (adev->irq.ih_soft.ring_size)
		adev->irq.ih_soft.enabled = true;

	वापस 0;
पूर्ण

/**
 * vega20_ih_irq_disable - disable पूर्णांकerrupts
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Disable पूर्णांकerrupts on the hw (VEGA20).
 */
अटल व्योम vega20_ih_irq_disable(काष्ठा amdgpu_device *adev)
अणु
	vega20_ih_toggle_पूर्णांकerrupts(adev, false);

	/* Wait and acknowledge irq */
	mdelay(1);
पूर्ण

/**
 * vega20_ih_get_wptr - get the IH ring buffer wptr
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @ih: amdgpu_ih_ring poपूर्णांकer
 *
 * Get the IH ring buffer wptr from either the रेजिस्टर
 * or the ग_लिखोback memory buffer (VEGA20).  Also check क्रम
 * ring buffer overflow and deal with it.
 * Returns the value of the wptr.
 */
अटल u32 vega20_ih_get_wptr(काष्ठा amdgpu_device *adev,
			      काष्ठा amdgpu_ih_ring *ih)
अणु
	u32 wptr, पंचांगp;
	काष्ठा amdgpu_ih_regs *ih_regs;

	अगर (ih == &adev->irq.ih) अणु
		/* Only ring0 supports ग_लिखोback. On other rings fall back
		 * to रेजिस्टर-based code with overflow checking below.
		 */
		wptr = le32_to_cpu(*ih->wptr_cpu);

		अगर (!REG_GET_FIELD(wptr, IH_RB_WPTR, RB_OVERFLOW))
			जाओ out;
	पूर्ण

	ih_regs = &ih->ih_regs;

	/* Double check that the overflow wasn't alपढ़ोy cleared. */
	wptr = RREG32_NO_KIQ(ih_regs->ih_rb_wptr);
	अगर (!REG_GET_FIELD(wptr, IH_RB_WPTR, RB_OVERFLOW))
		जाओ out;

	wptr = REG_SET_FIELD(wptr, IH_RB_WPTR, RB_OVERFLOW, 0);

	/* When a ring buffer overflow happen start parsing पूर्णांकerrupt
	 * from the last not overwritten vector (wptr + 32). Hopefully
	 * this should allow us to catchup.
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
 * vega20_ih_irq_rearm - rearm IRQ अगर lost
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @ih: amdgpu_ih_ring poपूर्णांकer
 *
 */
अटल व्योम vega20_ih_irq_rearm(काष्ठा amdgpu_device *adev,
			       काष्ठा amdgpu_ih_ring *ih)
अणु
	uपूर्णांक32_t v = 0;
	uपूर्णांक32_t i = 0;
	काष्ठा amdgpu_ih_regs *ih_regs;

	ih_regs = &ih->ih_regs;

	/* Rearm IRQ / re-wग_लिखो करोorbell अगर करोorbell ग_लिखो is lost */
	क्रम (i = 0; i < MAX_REARM_RETRY; i++) अणु
		v = RREG32_NO_KIQ(ih_regs->ih_rb_rptr);
		अगर ((v < ih->ring_size) && (v != ih->rptr))
			WDOORBELL32(ih->करोorbell_index, ih->rptr);
		अन्यथा
			अवरोध;
	पूर्ण
पूर्ण

/**
 * vega20_ih_set_rptr - set the IH ring buffer rptr
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @ih: amdgpu_ih_ring poपूर्णांकer
 *
 * Set the IH ring buffer rptr.
 */
अटल व्योम vega20_ih_set_rptr(काष्ठा amdgpu_device *adev,
			       काष्ठा amdgpu_ih_ring *ih)
अणु
	काष्ठा amdgpu_ih_regs *ih_regs;

	अगर (ih->use_करोorbell) अणु
		/* XXX check अगर swapping is necessary on BE */
		*ih->rptr_cpu = ih->rptr;
		WDOORBELL32(ih->करोorbell_index, ih->rptr);

		अगर (amdgpu_sriov_vf(adev))
			vega20_ih_irq_rearm(adev, ih);
	पूर्ण अन्यथा अणु
		ih_regs = &ih->ih_regs;
		WREG32(ih_regs->ih_rb_rptr, ih->rptr);
	पूर्ण
पूर्ण

/**
 * vega20_ih_self_irq - dispatch work क्रम ring 1 and 2
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @source: irq source
 * @entry: IV with WPTR update
 *
 * Update the WPTR from the IV and schedule work to handle the entries.
 */
अटल पूर्णांक vega20_ih_self_irq(काष्ठा amdgpu_device *adev,
			      काष्ठा amdgpu_irq_src *source,
			      काष्ठा amdgpu_iv_entry *entry)
अणु
	चयन (entry->ring_id) अणु
	हाल 1:
		schedule_work(&adev->irq.ih1_work);
		अवरोध;
	हाल 2:
		schedule_work(&adev->irq.ih2_work);
		अवरोध;
	शेष: अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा amdgpu_irq_src_funcs vega20_ih_self_irq_funcs = अणु
	.process = vega20_ih_self_irq,
पूर्ण;

अटल व्योम vega20_ih_set_self_irq_funcs(काष्ठा amdgpu_device *adev)
अणु
	adev->irq.self_irq.num_types = 0;
	adev->irq.self_irq.funcs = &vega20_ih_self_irq_funcs;
पूर्ण

अटल पूर्णांक vega20_ih_early_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	vega20_ih_set_पूर्णांकerrupt_funcs(adev);
	vega20_ih_set_self_irq_funcs(adev);
	वापस 0;
पूर्ण

अटल पूर्णांक vega20_ih_sw_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	पूर्णांक r;

	r = amdgpu_irq_add_id(adev, SOC15_IH_CLIENTID_IH, 0,
			      &adev->irq.self_irq);
	अगर (r)
		वापस r;

	r = amdgpu_ih_ring_init(adev, &adev->irq.ih, 256 * 1024, true);
	अगर (r)
		वापस r;

	adev->irq.ih.use_करोorbell = true;
	adev->irq.ih.करोorbell_index = adev->करोorbell_index.ih << 1;

	r = amdgpu_ih_ring_init(adev, &adev->irq.ih1, PAGE_SIZE, true);
	अगर (r)
		वापस r;

	adev->irq.ih1.use_करोorbell = true;
	adev->irq.ih1.करोorbell_index = (adev->करोorbell_index.ih + 1) << 1;

	r = amdgpu_ih_ring_init(adev, &adev->irq.ih2, PAGE_SIZE, true);
	अगर (r)
		वापस r;

	adev->irq.ih2.use_करोorbell = true;
	adev->irq.ih2.करोorbell_index = (adev->करोorbell_index.ih + 2) << 1;

	/* initialize ih control रेजिस्टरs offset */
	vega20_ih_init_रेजिस्टर_offset(adev);

	r = amdgpu_ih_ring_init(adev, &adev->irq.ih_soft, PAGE_SIZE, true);
	अगर (r)
		वापस r;

	r = amdgpu_irq_init(adev);

	वापस r;
पूर्ण

अटल पूर्णांक vega20_ih_sw_fini(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	amdgpu_irq_fini(adev);
	amdgpu_ih_ring_fini(adev, &adev->irq.ih_soft);
	amdgpu_ih_ring_fini(adev, &adev->irq.ih2);
	amdgpu_ih_ring_fini(adev, &adev->irq.ih1);
	amdgpu_ih_ring_fini(adev, &adev->irq.ih);

	वापस 0;
पूर्ण

अटल पूर्णांक vega20_ih_hw_init(व्योम *handle)
अणु
	पूर्णांक r;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	r = vega20_ih_irq_init(adev);
	अगर (r)
		वापस r;

	वापस 0;
पूर्ण

अटल पूर्णांक vega20_ih_hw_fini(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	vega20_ih_irq_disable(adev);

	वापस 0;
पूर्ण

अटल पूर्णांक vega20_ih_suspend(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	वापस vega20_ih_hw_fini(adev);
पूर्ण

अटल पूर्णांक vega20_ih_resume(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	वापस vega20_ih_hw_init(adev);
पूर्ण

अटल bool vega20_ih_is_idle(व्योम *handle)
अणु
	/* toकरो */
	वापस true;
पूर्ण

अटल पूर्णांक vega20_ih_रुको_क्रम_idle(व्योम *handle)
अणु
	/* toकरो */
	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक vega20_ih_soft_reset(व्योम *handle)
अणु
	/* toकरो */

	वापस 0;
पूर्ण

अटल व्योम vega20_ih_update_घड़ीgating_state(काष्ठा amdgpu_device *adev,
					       bool enable)
अणु
	uपूर्णांक32_t data, def, field_val;

	अगर (adev->cg_flags & AMD_CG_SUPPORT_IH_CG) अणु
		def = data = RREG32_SOC15(OSSSYS, 0, mmIH_CLK_CTRL);
		field_val = enable ? 0 : 1;
		data = REG_SET_FIELD(data, IH_CLK_CTRL,
				     IH_RETRY_INT_CAM_MEM_CLK_SOFT_OVERRIDE, field_val);
		data = REG_SET_FIELD(data, IH_CLK_CTRL,
				     IH_BUFFER_MEM_CLK_SOFT_OVERRIDE, field_val);
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
पूर्ण

अटल पूर्णांक vega20_ih_set_घड़ीgating_state(व्योम *handle,
					  क्रमागत amd_घड़ीgating_state state)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	vega20_ih_update_घड़ीgating_state(adev,
				state == AMD_CG_STATE_GATE);
	वापस 0;

पूर्ण

अटल पूर्णांक vega20_ih_set_घातergating_state(व्योम *handle,
					  क्रमागत amd_घातergating_state state)
अणु
	वापस 0;
पूर्ण

स्थिर काष्ठा amd_ip_funcs vega20_ih_ip_funcs = अणु
	.name = "vega20_ih",
	.early_init = vega20_ih_early_init,
	.late_init = शून्य,
	.sw_init = vega20_ih_sw_init,
	.sw_fini = vega20_ih_sw_fini,
	.hw_init = vega20_ih_hw_init,
	.hw_fini = vega20_ih_hw_fini,
	.suspend = vega20_ih_suspend,
	.resume = vega20_ih_resume,
	.is_idle = vega20_ih_is_idle,
	.रुको_क्रम_idle = vega20_ih_रुको_क्रम_idle,
	.soft_reset = vega20_ih_soft_reset,
	.set_घड़ीgating_state = vega20_ih_set_घड़ीgating_state,
	.set_घातergating_state = vega20_ih_set_घातergating_state,
पूर्ण;

अटल स्थिर काष्ठा amdgpu_ih_funcs vega20_ih_funcs = अणु
	.get_wptr = vega20_ih_get_wptr,
	.decode_iv = amdgpu_ih_decode_iv_helper,
	.set_rptr = vega20_ih_set_rptr
पूर्ण;

अटल व्योम vega20_ih_set_पूर्णांकerrupt_funcs(काष्ठा amdgpu_device *adev)
अणु
	adev->irq.ih_funcs = &vega20_ih_funcs;
पूर्ण

स्थिर काष्ठा amdgpu_ip_block_version vega20_ih_ip_block =
अणु
	.type = AMD_IP_BLOCK_TYPE_IH,
	.major = 4,
	.minor = 2,
	.rev = 0,
	.funcs = &vega20_ih_ip_funcs,
पूर्ण;
