<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/**************************************************************************
 * Copyright (c) 2007, Intel Corporation.
 * All Rights Reserved.
 *
 * Intel funded Tungsten Graphics (http://www.tungstengraphics.com) to
 * develop this driver.
 *
 **************************************************************************/

#समावेश <drm/drm_vblank.h>

#समावेश "power.h"
#समावेश "psb_drv.h"
#समावेश "psb_intel_reg.h"
#समावेश "psb_irq.h"
#समावेश "psb_reg.h"

/*
 * अंतरभूत functions
 */

अटल अंतरभूत u32
psb_pipestat(पूर्णांक pipe)
अणु
	अगर (pipe == 0)
		वापस PIPEASTAT;
	अगर (pipe == 1)
		वापस PIPEBSTAT;
	अगर (pipe == 2)
		वापस PIPECSTAT;
	BUG();
पूर्ण

अटल अंतरभूत u32
mid_pipe_event(पूर्णांक pipe)
अणु
	अगर (pipe == 0)
		वापस _PSB_PIPEA_EVENT_FLAG;
	अगर (pipe == 1)
		वापस _MDFLD_PIPEB_EVENT_FLAG;
	अगर (pipe == 2)
		वापस _MDFLD_PIPEC_EVENT_FLAG;
	BUG();
पूर्ण

अटल अंतरभूत u32
mid_pipe_vsync(पूर्णांक pipe)
अणु
	अगर (pipe == 0)
		वापस _PSB_VSYNC_PIPEA_FLAG;
	अगर (pipe == 1)
		वापस _PSB_VSYNC_PIPEB_FLAG;
	अगर (pipe == 2)
		वापस _MDFLD_PIPEC_VBLANK_FLAG;
	BUG();
पूर्ण

अटल अंतरभूत u32
mid_pipeconf(पूर्णांक pipe)
अणु
	अगर (pipe == 0)
		वापस PIPEACONF;
	अगर (pipe == 1)
		वापस PIPEBCONF;
	अगर (pipe == 2)
		वापस PIPECCONF;
	BUG();
पूर्ण

व्योम
psb_enable_pipestat(काष्ठा drm_psb_निजी *dev_priv, पूर्णांक pipe, u32 mask)
अणु
	अगर ((dev_priv->pipestat[pipe] & mask) != mask) अणु
		u32 reg = psb_pipestat(pipe);
		dev_priv->pipestat[pipe] |= mask;
		/* Enable the पूर्णांकerrupt, clear any pending status */
		अगर (gma_घातer_begin(dev_priv->dev, false)) अणु
			u32 ग_लिखोVal = PSB_RVDC32(reg);
			ग_लिखोVal |= (mask | (mask >> 16));
			PSB_WVDC32(ग_लिखोVal, reg);
			(व्योम) PSB_RVDC32(reg);
			gma_घातer_end(dev_priv->dev);
		पूर्ण
	पूर्ण
पूर्ण

व्योम
psb_disable_pipestat(काष्ठा drm_psb_निजी *dev_priv, पूर्णांक pipe, u32 mask)
अणु
	अगर ((dev_priv->pipestat[pipe] & mask) != 0) अणु
		u32 reg = psb_pipestat(pipe);
		dev_priv->pipestat[pipe] &= ~mask;
		अगर (gma_घातer_begin(dev_priv->dev, false)) अणु
			u32 ग_लिखोVal = PSB_RVDC32(reg);
			ग_लिखोVal &= ~mask;
			PSB_WVDC32(ग_लिखोVal, reg);
			(व्योम) PSB_RVDC32(reg);
			gma_घातer_end(dev_priv->dev);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Display controller पूर्णांकerrupt handler क्रम pipe event.
 */
अटल व्योम mid_pipe_event_handler(काष्ठा drm_device *dev, पूर्णांक pipe)
अणु
	काष्ठा drm_psb_निजी *dev_priv =
	    (काष्ठा drm_psb_निजी *) dev->dev_निजी;

	uपूर्णांक32_t pipe_stat_val = 0;
	uपूर्णांक32_t pipe_stat_reg = psb_pipestat(pipe);
	uपूर्णांक32_t pipe_enable = dev_priv->pipestat[pipe];
	uपूर्णांक32_t pipe_status = dev_priv->pipestat[pipe] >> 16;
	uपूर्णांक32_t pipe_clear;
	uपूर्णांक32_t i = 0;

	spin_lock(&dev_priv->irqmask_lock);

	pipe_stat_val = PSB_RVDC32(pipe_stat_reg);
	pipe_stat_val &= pipe_enable | pipe_status;
	pipe_stat_val &= pipe_stat_val >> 16;

	spin_unlock(&dev_priv->irqmask_lock);

	/* Clear the 2nd level पूर्णांकerrupt status bits
	 * Someबार the bits are very sticky so we repeat until they unstick */
	क्रम (i = 0; i < 0xffff; i++) अणु
		PSB_WVDC32(PSB_RVDC32(pipe_stat_reg), pipe_stat_reg);
		pipe_clear = PSB_RVDC32(pipe_stat_reg) & pipe_status;

		अगर (pipe_clear == 0)
			अवरोध;
	पूर्ण

	अगर (pipe_clear)
		dev_err(dev->dev,
		"%s, can't clear status bits for pipe %d, its value = 0x%x.\n",
		__func__, pipe, PSB_RVDC32(pipe_stat_reg));

	अगर (pipe_stat_val & PIPE_VBLANK_STATUS) अणु
		काष्ठा drm_crtc *crtc = drm_crtc_from_index(dev, pipe);
		काष्ठा gma_crtc *gma_crtc = to_gma_crtc(crtc);
		अचिन्हित दीर्घ flags;

		drm_handle_vblank(dev, pipe);

		spin_lock_irqsave(&dev->event_lock, flags);
		अगर (gma_crtc->page_flip_event) अणु
			drm_crtc_send_vblank_event(crtc,
						   gma_crtc->page_flip_event);
			gma_crtc->page_flip_event = शून्य;
			drm_crtc_vblank_put(crtc);
		पूर्ण
		spin_unlock_irqrestore(&dev->event_lock, flags);
	पूर्ण
पूर्ण

/*
 * Display controller पूर्णांकerrupt handler.
 */
अटल व्योम psb_vdc_पूर्णांकerrupt(काष्ठा drm_device *dev, uपूर्णांक32_t vdc_stat)
अणु
	अगर (vdc_stat & _PSB_IRQ_ASLE)
		psb_पूर्णांकel_opregion_asle_पूर्णांकr(dev);

	अगर (vdc_stat & _PSB_VSYNC_PIPEA_FLAG)
		mid_pipe_event_handler(dev, 0);

	अगर (vdc_stat & _PSB_VSYNC_PIPEB_FLAG)
		mid_pipe_event_handler(dev, 1);
पूर्ण

/*
 * SGX पूर्णांकerrupt handler
 */
अटल व्योम psb_sgx_पूर्णांकerrupt(काष्ठा drm_device *dev, u32 stat_1, u32 stat_2)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	u32 val, addr;

	अगर (stat_1 & _PSB_CE_TWOD_COMPLETE)
		val = PSB_RSGX32(PSB_CR_2D_BLIT_STATUS);

	अगर (stat_2 & _PSB_CE2_BIF_REQUESTER_FAULT) अणु
		val = PSB_RSGX32(PSB_CR_BIF_INT_STAT);
		addr = PSB_RSGX32(PSB_CR_BIF_FAULT);
		अगर (val) अणु
			अगर (val & _PSB_CBI_STAT_PF_N_RW)
				DRM_ERROR("SGX MMU page fault:");
			अन्यथा
				DRM_ERROR("SGX MMU read / write protection fault:");

			अगर (val & _PSB_CBI_STAT_FAULT_CACHE)
				DRM_ERROR("\tCache requestor");
			अगर (val & _PSB_CBI_STAT_FAULT_TA)
				DRM_ERROR("\tTA requestor");
			अगर (val & _PSB_CBI_STAT_FAULT_VDM)
				DRM_ERROR("\tVDM requestor");
			अगर (val & _PSB_CBI_STAT_FAULT_2D)
				DRM_ERROR("\t2D requestor");
			अगर (val & _PSB_CBI_STAT_FAULT_PBE)
				DRM_ERROR("\tPBE requestor");
			अगर (val & _PSB_CBI_STAT_FAULT_TSP)
				DRM_ERROR("\tTSP requestor");
			अगर (val & _PSB_CBI_STAT_FAULT_ISP)
				DRM_ERROR("\tISP requestor");
			अगर (val & _PSB_CBI_STAT_FAULT_USSEPDS)
				DRM_ERROR("\tUSSEPDS requestor");
			अगर (val & _PSB_CBI_STAT_FAULT_HOST)
				DRM_ERROR("\tHost requestor");

			DRM_ERROR("\tMMU failing address is 0x%08x.\n",
				  (अचिन्हित पूर्णांक)addr);
		पूर्ण
	पूर्ण

	/* Clear bits */
	PSB_WSGX32(stat_1, PSB_CR_EVENT_HOST_CLEAR);
	PSB_WSGX32(stat_2, PSB_CR_EVENT_HOST_CLEAR2);
	PSB_RSGX32(PSB_CR_EVENT_HOST_CLEAR2);
पूर्ण

irqवापस_t psb_irq_handler(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा drm_device *dev = arg;
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	uपूर्णांक32_t vdc_stat, dsp_पूर्णांक = 0, sgx_पूर्णांक = 0, hotplug_पूर्णांक = 0;
	u32 sgx_stat_1, sgx_stat_2;
	पूर्णांक handled = 0;

	spin_lock(&dev_priv->irqmask_lock);

	vdc_stat = PSB_RVDC32(PSB_INT_IDENTITY_R);

	अगर (vdc_stat & (_PSB_PIPE_EVENT_FLAG|_PSB_IRQ_ASLE))
		dsp_पूर्णांक = 1;

	अगर (vdc_stat & _PSB_IRQ_SGX_FLAG)
		sgx_पूर्णांक = 1;
	अगर (vdc_stat & _PSB_IRQ_DISP_HOTSYNC)
		hotplug_पूर्णांक = 1;

	vdc_stat &= dev_priv->vdc_irq_mask;
	spin_unlock(&dev_priv->irqmask_lock);

	अगर (dsp_पूर्णांक && gma_घातer_is_on(dev)) अणु
		psb_vdc_पूर्णांकerrupt(dev, vdc_stat);
		handled = 1;
	पूर्ण

	अगर (sgx_पूर्णांक) अणु
		sgx_stat_1 = PSB_RSGX32(PSB_CR_EVENT_STATUS);
		sgx_stat_2 = PSB_RSGX32(PSB_CR_EVENT_STATUS2);
		psb_sgx_पूर्णांकerrupt(dev, sgx_stat_1, sgx_stat_2);
		handled = 1;
	पूर्ण

	/* Note: this bit has other meanings on some devices, so we will
	   need to address that later अगर it ever matters */
	अगर (hotplug_पूर्णांक && dev_priv->ops->hotplug) अणु
		handled = dev_priv->ops->hotplug(dev);
		REG_WRITE(PORT_HOTPLUG_STAT, REG_READ(PORT_HOTPLUG_STAT));
	पूर्ण

	PSB_WVDC32(vdc_stat, PSB_INT_IDENTITY_R);
	(व्योम) PSB_RVDC32(PSB_INT_IDENTITY_R);
	rmb();

	अगर (!handled)
		वापस IRQ_NONE;

	वापस IRQ_HANDLED;
पूर्ण

व्योम psb_irq_preinstall(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_psb_निजी *dev_priv =
	    (काष्ठा drm_psb_निजी *) dev->dev_निजी;
	अचिन्हित दीर्घ irqflags;

	spin_lock_irqsave(&dev_priv->irqmask_lock, irqflags);

	अगर (gma_घातer_is_on(dev)) अणु
		PSB_WVDC32(0xFFFFFFFF, PSB_HWSTAM);
		PSB_WVDC32(0x00000000, PSB_INT_MASK_R);
		PSB_WVDC32(0x00000000, PSB_INT_ENABLE_R);
		PSB_WSGX32(0x00000000, PSB_CR_EVENT_HOST_ENABLE);
		PSB_RSGX32(PSB_CR_EVENT_HOST_ENABLE);
	पूर्ण
	अगर (dev->vblank[0].enabled)
		dev_priv->vdc_irq_mask |= _PSB_VSYNC_PIPEA_FLAG;
	अगर (dev->vblank[1].enabled)
		dev_priv->vdc_irq_mask |= _PSB_VSYNC_PIPEB_FLAG;

	/* Revisit this area - want per device masks ? */
	अगर (dev_priv->ops->hotplug)
		dev_priv->vdc_irq_mask |= _PSB_IRQ_DISP_HOTSYNC;
	dev_priv->vdc_irq_mask |= _PSB_IRQ_ASLE | _PSB_IRQ_SGX_FLAG;

	/* This रेजिस्टर is safe even अगर display island is off */
	PSB_WVDC32(~dev_priv->vdc_irq_mask, PSB_INT_MASK_R);
	spin_unlock_irqrestore(&dev_priv->irqmask_lock, irqflags);
पूर्ण

पूर्णांक psb_irq_postinstall(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	अचिन्हित दीर्घ irqflags;
	अचिन्हित पूर्णांक i;

	spin_lock_irqsave(&dev_priv->irqmask_lock, irqflags);

	/* Enable 2D and MMU fault पूर्णांकerrupts */
	PSB_WSGX32(_PSB_CE2_BIF_REQUESTER_FAULT, PSB_CR_EVENT_HOST_ENABLE2);
	PSB_WSGX32(_PSB_CE_TWOD_COMPLETE, PSB_CR_EVENT_HOST_ENABLE);
	PSB_RSGX32(PSB_CR_EVENT_HOST_ENABLE); /* Post */

	/* This रेजिस्टर is safe even अगर display island is off */
	PSB_WVDC32(dev_priv->vdc_irq_mask, PSB_INT_ENABLE_R);
	PSB_WVDC32(0xFFFFFFFF, PSB_HWSTAM);

	क्रम (i = 0; i < dev->num_crtcs; ++i) अणु
		अगर (dev->vblank[i].enabled)
			psb_enable_pipestat(dev_priv, i, PIPE_VBLANK_INTERRUPT_ENABLE);
		अन्यथा
			psb_disable_pipestat(dev_priv, i, PIPE_VBLANK_INTERRUPT_ENABLE);
	पूर्ण

	अगर (dev_priv->ops->hotplug_enable)
		dev_priv->ops->hotplug_enable(dev, true);

	spin_unlock_irqrestore(&dev_priv->irqmask_lock, irqflags);
	वापस 0;
पूर्ण

व्योम psb_irq_uninstall(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	अचिन्हित दीर्घ irqflags;
	अचिन्हित पूर्णांक i;

	spin_lock_irqsave(&dev_priv->irqmask_lock, irqflags);

	अगर (dev_priv->ops->hotplug_enable)
		dev_priv->ops->hotplug_enable(dev, false);

	PSB_WVDC32(0xFFFFFFFF, PSB_HWSTAM);

	क्रम (i = 0; i < dev->num_crtcs; ++i) अणु
		अगर (dev->vblank[i].enabled)
			psb_disable_pipestat(dev_priv, i, PIPE_VBLANK_INTERRUPT_ENABLE);
	पूर्ण

	dev_priv->vdc_irq_mask &= _PSB_IRQ_SGX_FLAG |
				  _PSB_IRQ_MSVDX_FLAG |
				  _LNC_IRQ_TOPAZ_FLAG;

	/* These two रेजिस्टरs are safe even अगर display island is off */
	PSB_WVDC32(~dev_priv->vdc_irq_mask, PSB_INT_MASK_R);
	PSB_WVDC32(dev_priv->vdc_irq_mask, PSB_INT_ENABLE_R);

	wmb();

	/* This रेजिस्टर is safe even अगर display island is off */
	PSB_WVDC32(PSB_RVDC32(PSB_INT_IDENTITY_R), PSB_INT_IDENTITY_R);
	spin_unlock_irqrestore(&dev_priv->irqmask_lock, irqflags);
पूर्ण

/*
 * It is used to enable VBLANK पूर्णांकerrupt
 */
पूर्णांक psb_enable_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	अचिन्हित पूर्णांक pipe = crtc->index;
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	अचिन्हित दीर्घ irqflags;
	uपूर्णांक32_t reg_val = 0;
	uपूर्णांक32_t pipeconf_reg = mid_pipeconf(pipe);

	अगर (gma_घातer_begin(dev, false)) अणु
		reg_val = REG_READ(pipeconf_reg);
		gma_घातer_end(dev);
	पूर्ण

	अगर (!(reg_val & PIPEACONF_ENABLE))
		वापस -EINVAL;

	spin_lock_irqsave(&dev_priv->irqmask_lock, irqflags);

	अगर (pipe == 0)
		dev_priv->vdc_irq_mask |= _PSB_VSYNC_PIPEA_FLAG;
	अन्यथा अगर (pipe == 1)
		dev_priv->vdc_irq_mask |= _PSB_VSYNC_PIPEB_FLAG;

	PSB_WVDC32(~dev_priv->vdc_irq_mask, PSB_INT_MASK_R);
	PSB_WVDC32(dev_priv->vdc_irq_mask, PSB_INT_ENABLE_R);
	psb_enable_pipestat(dev_priv, pipe, PIPE_VBLANK_INTERRUPT_ENABLE);

	spin_unlock_irqrestore(&dev_priv->irqmask_lock, irqflags);

	वापस 0;
पूर्ण

/*
 * It is used to disable VBLANK पूर्णांकerrupt
 */
व्योम psb_disable_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	अचिन्हित पूर्णांक pipe = crtc->index;
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	अचिन्हित दीर्घ irqflags;

	spin_lock_irqsave(&dev_priv->irqmask_lock, irqflags);

	अगर (pipe == 0)
		dev_priv->vdc_irq_mask &= ~_PSB_VSYNC_PIPEA_FLAG;
	अन्यथा अगर (pipe == 1)
		dev_priv->vdc_irq_mask &= ~_PSB_VSYNC_PIPEB_FLAG;

	PSB_WVDC32(~dev_priv->vdc_irq_mask, PSB_INT_MASK_R);
	PSB_WVDC32(dev_priv->vdc_irq_mask, PSB_INT_ENABLE_R);
	psb_disable_pipestat(dev_priv, pipe, PIPE_VBLANK_INTERRUPT_ENABLE);

	spin_unlock_irqrestore(&dev_priv->irqmask_lock, irqflags);
पूर्ण

/* Called from drm generic code, passed a 'crtc', which
 * we use as a pipe index
 */
u32 psb_get_vblank_counter(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	अचिन्हित पूर्णांक pipe = crtc->index;
	uपूर्णांक32_t high_frame = PIPEAFRAMEHIGH;
	uपूर्णांक32_t low_frame = PIPEAFRAMEPIXEL;
	uपूर्णांक32_t pipeconf_reg = PIPEACONF;
	uपूर्णांक32_t reg_val = 0;
	uपूर्णांक32_t high1 = 0, high2 = 0, low = 0, count = 0;

	चयन (pipe) अणु
	हाल 0:
		अवरोध;
	हाल 1:
		high_frame = PIPEBFRAMEHIGH;
		low_frame = PIPEBFRAMEPIXEL;
		pipeconf_reg = PIPEBCONF;
		अवरोध;
	हाल 2:
		high_frame = PIPECFRAMEHIGH;
		low_frame = PIPECFRAMEPIXEL;
		pipeconf_reg = PIPECCONF;
		अवरोध;
	शेष:
		dev_err(dev->dev, "%s, invalid pipe.\n", __func__);
		वापस 0;
	पूर्ण

	अगर (!gma_घातer_begin(dev, false))
		वापस 0;

	reg_val = REG_READ(pipeconf_reg);

	अगर (!(reg_val & PIPEACONF_ENABLE)) अणु
		dev_err(dev->dev, "trying to get vblank count for disabled pipe %u\n",
								pipe);
		जाओ psb_get_vblank_counter_निकास;
	पूर्ण

	/*
	 * High & low रेजिस्टर fields aren't synchronized, so make sure
	 * we get a low value that's stable across two पढ़ोs of the high
	 * रेजिस्टर.
	 */
	करो अणु
		high1 = ((REG_READ(high_frame) & PIPE_FRAME_HIGH_MASK) >>
			 PIPE_FRAME_HIGH_SHIFT);
		low =  ((REG_READ(low_frame) & PIPE_FRAME_LOW_MASK) >>
			PIPE_FRAME_LOW_SHIFT);
		high2 = ((REG_READ(high_frame) & PIPE_FRAME_HIGH_MASK) >>
			 PIPE_FRAME_HIGH_SHIFT);
	पूर्ण जबतक (high1 != high2);

	count = (high1 << 8) | low;

psb_get_vblank_counter_निकास:

	gma_घातer_end(dev);

	वापस count;
पूर्ण

