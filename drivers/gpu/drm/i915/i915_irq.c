<शैली गुरु>
/* i915_irq.c -- IRQ support क्रम the I915 -*- linux-c -*-
 */
/*
 * Copyright 2003 Tungsten Graphics, Inc., Cedar Park, Texas.
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
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT.
 * IN NO EVENT SHALL TUNGSTEN GRAPHICS AND/OR ITS SUPPLIERS BE LIABLE FOR
 * ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/circ_buf.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysrq.h>

#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_irq.h>

#समावेश "display/intel_display_types.h"
#समावेश "display/intel_fifo_underrun.h"
#समावेश "display/intel_hotplug.h"
#समावेश "display/intel_lpe_audio.h"
#समावेश "display/intel_psr.h"

#समावेश "gt/intel_breadcrumbs.h"
#समावेश "gt/intel_gt.h"
#समावेश "gt/intel_gt_irq.h"
#समावेश "gt/intel_gt_pm_irq.h"
#समावेश "gt/intel_rps.h"

#समावेश "i915_drv.h"
#समावेश "i915_irq.h"
#समावेश "i915_trace.h"
#समावेश "intel_pm.h"

/**
 * DOC: पूर्णांकerrupt handling
 *
 * These functions provide the basic support क्रम enabling and disabling the
 * पूर्णांकerrupt handling support. There's a lot more functionality in i915_irq.c
 * and related files, but that will be described in separate chapters.
 */

/*
 * Interrupt statistic क्रम PMU. Increments the counter only अगर the
 * पूर्णांकerrupt originated from the the GPU so पूर्णांकerrupts from a device which
 * shares the पूर्णांकerrupt line are not accounted.
 */
अटल अंतरभूत व्योम pmu_irq_stats(काष्ठा drm_i915_निजी *i915,
				 irqवापस_t res)
अणु
	अगर (unlikely(res != IRQ_HANDLED))
		वापस;

	/*
	 * A clever compiler translates that पूर्णांकo INC. A not so clever one
	 * should at least prevent store tearing.
	 */
	WRITE_ONCE(i915->pmu.irq_count, i915->pmu.irq_count + 1);
पूर्ण

प्रकार bool (*दीर्घ_pulse_detect_func)(क्रमागत hpd_pin pin, u32 val);
प्रकार u32 (*hotplug_enables_func)(काष्ठा drm_i915_निजी *i915,
				    क्रमागत hpd_pin pin);

अटल स्थिर u32 hpd_ilk[HPD_NUM_PINS] = अणु
	[HPD_PORT_A] = DE_DP_A_HOTPLUG,
पूर्ण;

अटल स्थिर u32 hpd_ivb[HPD_NUM_PINS] = अणु
	[HPD_PORT_A] = DE_DP_A_HOTPLUG_IVB,
पूर्ण;

अटल स्थिर u32 hpd_bdw[HPD_NUM_PINS] = अणु
	[HPD_PORT_A] = GEN8_DE_PORT_HOTPLUG(HPD_PORT_A),
पूर्ण;

अटल स्थिर u32 hpd_ibx[HPD_NUM_PINS] = अणु
	[HPD_CRT] = SDE_CRT_HOTPLUG,
	[HPD_SDVO_B] = SDE_SDVOB_HOTPLUG,
	[HPD_PORT_B] = SDE_PORTB_HOTPLUG,
	[HPD_PORT_C] = SDE_PORTC_HOTPLUG,
	[HPD_PORT_D] = SDE_PORTD_HOTPLUG,
पूर्ण;

अटल स्थिर u32 hpd_cpt[HPD_NUM_PINS] = अणु
	[HPD_CRT] = SDE_CRT_HOTPLUG_CPT,
	[HPD_SDVO_B] = SDE_SDVOB_HOTPLUG_CPT,
	[HPD_PORT_B] = SDE_PORTB_HOTPLUG_CPT,
	[HPD_PORT_C] = SDE_PORTC_HOTPLUG_CPT,
	[HPD_PORT_D] = SDE_PORTD_HOTPLUG_CPT,
पूर्ण;

अटल स्थिर u32 hpd_spt[HPD_NUM_PINS] = अणु
	[HPD_PORT_A] = SDE_PORTA_HOTPLUG_SPT,
	[HPD_PORT_B] = SDE_PORTB_HOTPLUG_CPT,
	[HPD_PORT_C] = SDE_PORTC_HOTPLUG_CPT,
	[HPD_PORT_D] = SDE_PORTD_HOTPLUG_CPT,
	[HPD_PORT_E] = SDE_PORTE_HOTPLUG_SPT,
पूर्ण;

अटल स्थिर u32 hpd_mask_i915[HPD_NUM_PINS] = अणु
	[HPD_CRT] = CRT_HOTPLUG_INT_EN,
	[HPD_SDVO_B] = SDVOB_HOTPLUG_INT_EN,
	[HPD_SDVO_C] = SDVOC_HOTPLUG_INT_EN,
	[HPD_PORT_B] = PORTB_HOTPLUG_INT_EN,
	[HPD_PORT_C] = PORTC_HOTPLUG_INT_EN,
	[HPD_PORT_D] = PORTD_HOTPLUG_INT_EN,
पूर्ण;

अटल स्थिर u32 hpd_status_g4x[HPD_NUM_PINS] = अणु
	[HPD_CRT] = CRT_HOTPLUG_INT_STATUS,
	[HPD_SDVO_B] = SDVOB_HOTPLUG_INT_STATUS_G4X,
	[HPD_SDVO_C] = SDVOC_HOTPLUG_INT_STATUS_G4X,
	[HPD_PORT_B] = PORTB_HOTPLUG_INT_STATUS,
	[HPD_PORT_C] = PORTC_HOTPLUG_INT_STATUS,
	[HPD_PORT_D] = PORTD_HOTPLUG_INT_STATUS,
पूर्ण;

अटल स्थिर u32 hpd_status_i915[HPD_NUM_PINS] = अणु
	[HPD_CRT] = CRT_HOTPLUG_INT_STATUS,
	[HPD_SDVO_B] = SDVOB_HOTPLUG_INT_STATUS_I915,
	[HPD_SDVO_C] = SDVOC_HOTPLUG_INT_STATUS_I915,
	[HPD_PORT_B] = PORTB_HOTPLUG_INT_STATUS,
	[HPD_PORT_C] = PORTC_HOTPLUG_INT_STATUS,
	[HPD_PORT_D] = PORTD_HOTPLUG_INT_STATUS,
पूर्ण;

अटल स्थिर u32 hpd_bxt[HPD_NUM_PINS] = अणु
	[HPD_PORT_A] = GEN8_DE_PORT_HOTPLUG(HPD_PORT_A),
	[HPD_PORT_B] = GEN8_DE_PORT_HOTPLUG(HPD_PORT_B),
	[HPD_PORT_C] = GEN8_DE_PORT_HOTPLUG(HPD_PORT_C),
पूर्ण;

अटल स्थिर u32 hpd_gen11[HPD_NUM_PINS] = अणु
	[HPD_PORT_TC1] = GEN11_TC_HOTPLUG(HPD_PORT_TC1) | GEN11_TBT_HOTPLUG(HPD_PORT_TC1),
	[HPD_PORT_TC2] = GEN11_TC_HOTPLUG(HPD_PORT_TC2) | GEN11_TBT_HOTPLUG(HPD_PORT_TC2),
	[HPD_PORT_TC3] = GEN11_TC_HOTPLUG(HPD_PORT_TC3) | GEN11_TBT_HOTPLUG(HPD_PORT_TC3),
	[HPD_PORT_TC4] = GEN11_TC_HOTPLUG(HPD_PORT_TC4) | GEN11_TBT_HOTPLUG(HPD_PORT_TC4),
	[HPD_PORT_TC5] = GEN11_TC_HOTPLUG(HPD_PORT_TC5) | GEN11_TBT_HOTPLUG(HPD_PORT_TC5),
	[HPD_PORT_TC6] = GEN11_TC_HOTPLUG(HPD_PORT_TC6) | GEN11_TBT_HOTPLUG(HPD_PORT_TC6),
पूर्ण;

अटल स्थिर u32 hpd_icp[HPD_NUM_PINS] = अणु
	[HPD_PORT_A] = SDE_DDI_HOTPLUG_ICP(HPD_PORT_A),
	[HPD_PORT_B] = SDE_DDI_HOTPLUG_ICP(HPD_PORT_B),
	[HPD_PORT_C] = SDE_DDI_HOTPLUG_ICP(HPD_PORT_C),
	[HPD_PORT_TC1] = SDE_TC_HOTPLUG_ICP(HPD_PORT_TC1),
	[HPD_PORT_TC2] = SDE_TC_HOTPLUG_ICP(HPD_PORT_TC2),
	[HPD_PORT_TC3] = SDE_TC_HOTPLUG_ICP(HPD_PORT_TC3),
	[HPD_PORT_TC4] = SDE_TC_HOTPLUG_ICP(HPD_PORT_TC4),
	[HPD_PORT_TC5] = SDE_TC_HOTPLUG_ICP(HPD_PORT_TC5),
	[HPD_PORT_TC6] = SDE_TC_HOTPLUG_ICP(HPD_PORT_TC6),
पूर्ण;

अटल स्थिर u32 hpd_sde_dg1[HPD_NUM_PINS] = अणु
	[HPD_PORT_A] = SDE_DDI_HOTPLUG_ICP(HPD_PORT_A),
	[HPD_PORT_B] = SDE_DDI_HOTPLUG_ICP(HPD_PORT_B),
	[HPD_PORT_C] = SDE_DDI_HOTPLUG_ICP(HPD_PORT_C),
	[HPD_PORT_D] = SDE_DDI_HOTPLUG_ICP(HPD_PORT_D),
पूर्ण;

अटल व्योम पूर्णांकel_hpd_init_pins(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा i915_hotplug *hpd = &dev_priv->hotplug;

	अगर (HAS_GMCH(dev_priv)) अणु
		अगर (IS_G4X(dev_priv) || IS_VALLEYVIEW(dev_priv) ||
		    IS_CHERRYVIEW(dev_priv))
			hpd->hpd = hpd_status_g4x;
		अन्यथा
			hpd->hpd = hpd_status_i915;
		वापस;
	पूर्ण

	अगर (DISPLAY_VER(dev_priv) >= 11)
		hpd->hpd = hpd_gen11;
	अन्यथा अगर (IS_GEN9_LP(dev_priv))
		hpd->hpd = hpd_bxt;
	अन्यथा अगर (DISPLAY_VER(dev_priv) >= 8)
		hpd->hpd = hpd_bdw;
	अन्यथा अगर (DISPLAY_VER(dev_priv) >= 7)
		hpd->hpd = hpd_ivb;
	अन्यथा
		hpd->hpd = hpd_ilk;

	अगर ((INTEL_PCH_TYPE(dev_priv) < PCH_DG1) &&
	    (!HAS_PCH_SPLIT(dev_priv) || HAS_PCH_NOP(dev_priv)))
		वापस;

	अगर (HAS_PCH_DG1(dev_priv))
		hpd->pch_hpd = hpd_sde_dg1;
	अन्यथा अगर (INTEL_PCH_TYPE(dev_priv) >= PCH_ICP)
		hpd->pch_hpd = hpd_icp;
	अन्यथा अगर (HAS_PCH_CNP(dev_priv) || HAS_PCH_SPT(dev_priv))
		hpd->pch_hpd = hpd_spt;
	अन्यथा अगर (HAS_PCH_LPT(dev_priv) || HAS_PCH_CPT(dev_priv))
		hpd->pch_hpd = hpd_cpt;
	अन्यथा अगर (HAS_PCH_IBX(dev_priv))
		hpd->pch_hpd = hpd_ibx;
	अन्यथा
		MISSING_CASE(INTEL_PCH_TYPE(dev_priv));
पूर्ण

अटल व्योम
पूर्णांकel_handle_vblank(काष्ठा drm_i915_निजी *dev_priv, क्रमागत pipe pipe)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = पूर्णांकel_get_crtc_क्रम_pipe(dev_priv, pipe);

	drm_crtc_handle_vblank(&crtc->base);
पूर्ण

व्योम gen3_irq_reset(काष्ठा पूर्णांकel_uncore *uncore, i915_reg_t imr,
		    i915_reg_t iir, i915_reg_t ier)
अणु
	पूर्णांकel_uncore_ग_लिखो(uncore, imr, 0xffffffff);
	पूर्णांकel_uncore_posting_पढ़ो(uncore, imr);

	पूर्णांकel_uncore_ग_लिखो(uncore, ier, 0);

	/* IIR can theoretically queue up two events. Be paranoid. */
	पूर्णांकel_uncore_ग_लिखो(uncore, iir, 0xffffffff);
	पूर्णांकel_uncore_posting_पढ़ो(uncore, iir);
	पूर्णांकel_uncore_ग_लिखो(uncore, iir, 0xffffffff);
	पूर्णांकel_uncore_posting_पढ़ो(uncore, iir);
पूर्ण

व्योम gen2_irq_reset(काष्ठा पूर्णांकel_uncore *uncore)
अणु
	पूर्णांकel_uncore_ग_लिखो16(uncore, GEN2_IMR, 0xffff);
	पूर्णांकel_uncore_posting_पढ़ो16(uncore, GEN2_IMR);

	पूर्णांकel_uncore_ग_लिखो16(uncore, GEN2_IER, 0);

	/* IIR can theoretically queue up two events. Be paranoid. */
	पूर्णांकel_uncore_ग_लिखो16(uncore, GEN2_IIR, 0xffff);
	पूर्णांकel_uncore_posting_पढ़ो16(uncore, GEN2_IIR);
	पूर्णांकel_uncore_ग_लिखो16(uncore, GEN2_IIR, 0xffff);
	पूर्णांकel_uncore_posting_पढ़ो16(uncore, GEN2_IIR);
पूर्ण

/*
 * We should clear IMR at preinstall/uninstall, and just check at postinstall.
 */
अटल व्योम gen3_निश्चित_iir_is_zero(काष्ठा पूर्णांकel_uncore *uncore, i915_reg_t reg)
अणु
	u32 val = पूर्णांकel_uncore_पढ़ो(uncore, reg);

	अगर (val == 0)
		वापस;

	drm_WARN(&uncore->i915->drm, 1,
		 "Interrupt register 0x%x is not zero: 0x%08x\n",
		 i915_mmio_reg_offset(reg), val);
	पूर्णांकel_uncore_ग_लिखो(uncore, reg, 0xffffffff);
	पूर्णांकel_uncore_posting_पढ़ो(uncore, reg);
	पूर्णांकel_uncore_ग_लिखो(uncore, reg, 0xffffffff);
	पूर्णांकel_uncore_posting_पढ़ो(uncore, reg);
पूर्ण

अटल व्योम gen2_निश्चित_iir_is_zero(काष्ठा पूर्णांकel_uncore *uncore)
अणु
	u16 val = पूर्णांकel_uncore_पढ़ो16(uncore, GEN2_IIR);

	अगर (val == 0)
		वापस;

	drm_WARN(&uncore->i915->drm, 1,
		 "Interrupt register 0x%x is not zero: 0x%08x\n",
		 i915_mmio_reg_offset(GEN2_IIR), val);
	पूर्णांकel_uncore_ग_लिखो16(uncore, GEN2_IIR, 0xffff);
	पूर्णांकel_uncore_posting_पढ़ो16(uncore, GEN2_IIR);
	पूर्णांकel_uncore_ग_लिखो16(uncore, GEN2_IIR, 0xffff);
	पूर्णांकel_uncore_posting_पढ़ो16(uncore, GEN2_IIR);
पूर्ण

व्योम gen3_irq_init(काष्ठा पूर्णांकel_uncore *uncore,
		   i915_reg_t imr, u32 imr_val,
		   i915_reg_t ier, u32 ier_val,
		   i915_reg_t iir)
अणु
	gen3_निश्चित_iir_is_zero(uncore, iir);

	पूर्णांकel_uncore_ग_लिखो(uncore, ier, ier_val);
	पूर्णांकel_uncore_ग_लिखो(uncore, imr, imr_val);
	पूर्णांकel_uncore_posting_पढ़ो(uncore, imr);
पूर्ण

व्योम gen2_irq_init(काष्ठा पूर्णांकel_uncore *uncore,
		   u32 imr_val, u32 ier_val)
अणु
	gen2_निश्चित_iir_is_zero(uncore);

	पूर्णांकel_uncore_ग_लिखो16(uncore, GEN2_IER, ier_val);
	पूर्णांकel_uncore_ग_लिखो16(uncore, GEN2_IMR, imr_val);
	पूर्णांकel_uncore_posting_पढ़ो16(uncore, GEN2_IMR);
पूर्ण

/* For display hotplug पूर्णांकerrupt */
अटल अंतरभूत व्योम
i915_hotplug_पूर्णांकerrupt_update_locked(काष्ठा drm_i915_निजी *dev_priv,
				     u32 mask,
				     u32 bits)
अणु
	u32 val;

	lockdep_निश्चित_held(&dev_priv->irq_lock);
	drm_WARN_ON(&dev_priv->drm, bits & ~mask);

	val = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, PORT_HOTPLUG_EN);
	val &= ~mask;
	val |= bits;
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, PORT_HOTPLUG_EN, val);
पूर्ण

/**
 * i915_hotplug_पूर्णांकerrupt_update - update hotplug पूर्णांकerrupt enable
 * @dev_priv: driver निजी
 * @mask: bits to update
 * @bits: bits to enable
 * NOTE: the HPD enable bits are modअगरied both inside and outside
 * of an पूर्णांकerrupt context. To aव्योम that पढ़ो-modअगरy-ग_लिखो cycles
 * पूर्णांकerfer, these bits are रक्षित by a spinlock. Since this
 * function is usually not called from a context where the lock is
 * held alपढ़ोy, this function acquires the lock itself. A non-locking
 * version is also available.
 */
व्योम i915_hotplug_पूर्णांकerrupt_update(काष्ठा drm_i915_निजी *dev_priv,
				   u32 mask,
				   u32 bits)
अणु
	spin_lock_irq(&dev_priv->irq_lock);
	i915_hotplug_पूर्णांकerrupt_update_locked(dev_priv, mask, bits);
	spin_unlock_irq(&dev_priv->irq_lock);
पूर्ण

/**
 * ilk_update_display_irq - update DEIMR
 * @dev_priv: driver निजी
 * @पूर्णांकerrupt_mask: mask of पूर्णांकerrupt bits to update
 * @enabled_irq_mask: mask of पूर्णांकerrupt bits to enable
 */
व्योम ilk_update_display_irq(काष्ठा drm_i915_निजी *dev_priv,
			    u32 पूर्णांकerrupt_mask,
			    u32 enabled_irq_mask)
अणु
	u32 new_val;

	lockdep_निश्चित_held(&dev_priv->irq_lock);
	drm_WARN_ON(&dev_priv->drm, enabled_irq_mask & ~पूर्णांकerrupt_mask);

	new_val = dev_priv->irq_mask;
	new_val &= ~पूर्णांकerrupt_mask;
	new_val |= (~enabled_irq_mask & पूर्णांकerrupt_mask);

	अगर (new_val != dev_priv->irq_mask &&
	    !drm_WARN_ON(&dev_priv->drm, !पूर्णांकel_irqs_enabled(dev_priv))) अणु
		dev_priv->irq_mask = new_val;
		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, DEIMR, dev_priv->irq_mask);
		पूर्णांकel_uncore_posting_पढ़ो(&dev_priv->uncore, DEIMR);
	पूर्ण
पूर्ण

/**
 * bdw_update_port_irq - update DE port पूर्णांकerrupt
 * @dev_priv: driver निजी
 * @पूर्णांकerrupt_mask: mask of पूर्णांकerrupt bits to update
 * @enabled_irq_mask: mask of पूर्णांकerrupt bits to enable
 */
अटल व्योम bdw_update_port_irq(काष्ठा drm_i915_निजी *dev_priv,
				u32 पूर्णांकerrupt_mask,
				u32 enabled_irq_mask)
अणु
	u32 new_val;
	u32 old_val;

	lockdep_निश्चित_held(&dev_priv->irq_lock);

	drm_WARN_ON(&dev_priv->drm, enabled_irq_mask & ~पूर्णांकerrupt_mask);

	अगर (drm_WARN_ON(&dev_priv->drm, !पूर्णांकel_irqs_enabled(dev_priv)))
		वापस;

	old_val = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, GEN8_DE_PORT_IMR);

	new_val = old_val;
	new_val &= ~पूर्णांकerrupt_mask;
	new_val |= (~enabled_irq_mask & पूर्णांकerrupt_mask);

	अगर (new_val != old_val) अणु
		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, GEN8_DE_PORT_IMR, new_val);
		पूर्णांकel_uncore_posting_पढ़ो(&dev_priv->uncore, GEN8_DE_PORT_IMR);
	पूर्ण
पूर्ण

/**
 * bdw_update_pipe_irq - update DE pipe पूर्णांकerrupt
 * @dev_priv: driver निजी
 * @pipe: pipe whose पूर्णांकerrupt to update
 * @पूर्णांकerrupt_mask: mask of पूर्णांकerrupt bits to update
 * @enabled_irq_mask: mask of पूर्णांकerrupt bits to enable
 */
व्योम bdw_update_pipe_irq(काष्ठा drm_i915_निजी *dev_priv,
			 क्रमागत pipe pipe,
			 u32 पूर्णांकerrupt_mask,
			 u32 enabled_irq_mask)
अणु
	u32 new_val;

	lockdep_निश्चित_held(&dev_priv->irq_lock);

	drm_WARN_ON(&dev_priv->drm, enabled_irq_mask & ~पूर्णांकerrupt_mask);

	अगर (drm_WARN_ON(&dev_priv->drm, !पूर्णांकel_irqs_enabled(dev_priv)))
		वापस;

	new_val = dev_priv->de_irq_mask[pipe];
	new_val &= ~पूर्णांकerrupt_mask;
	new_val |= (~enabled_irq_mask & पूर्णांकerrupt_mask);

	अगर (new_val != dev_priv->de_irq_mask[pipe]) अणु
		dev_priv->de_irq_mask[pipe] = new_val;
		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, GEN8_DE_PIPE_IMR(pipe), dev_priv->de_irq_mask[pipe]);
		पूर्णांकel_uncore_posting_पढ़ो(&dev_priv->uncore, GEN8_DE_PIPE_IMR(pipe));
	पूर्ण
पूर्ण

/**
 * ibx_display_पूर्णांकerrupt_update - update SDEIMR
 * @dev_priv: driver निजी
 * @पूर्णांकerrupt_mask: mask of पूर्णांकerrupt bits to update
 * @enabled_irq_mask: mask of पूर्णांकerrupt bits to enable
 */
व्योम ibx_display_पूर्णांकerrupt_update(काष्ठा drm_i915_निजी *dev_priv,
				  u32 पूर्णांकerrupt_mask,
				  u32 enabled_irq_mask)
अणु
	u32 sdeimr = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, SDEIMR);
	sdeimr &= ~पूर्णांकerrupt_mask;
	sdeimr |= (~enabled_irq_mask & पूर्णांकerrupt_mask);

	drm_WARN_ON(&dev_priv->drm, enabled_irq_mask & ~पूर्णांकerrupt_mask);

	lockdep_निश्चित_held(&dev_priv->irq_lock);

	अगर (drm_WARN_ON(&dev_priv->drm, !पूर्णांकel_irqs_enabled(dev_priv)))
		वापस;

	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, SDEIMR, sdeimr);
	पूर्णांकel_uncore_posting_पढ़ो(&dev_priv->uncore, SDEIMR);
पूर्ण

u32 i915_pipestat_enable_mask(काष्ठा drm_i915_निजी *dev_priv,
			      क्रमागत pipe pipe)
अणु
	u32 status_mask = dev_priv->pipestat_irq_mask[pipe];
	u32 enable_mask = status_mask << 16;

	lockdep_निश्चित_held(&dev_priv->irq_lock);

	अगर (DISPLAY_VER(dev_priv) < 5)
		जाओ out;

	/*
	 * On pipe A we करोn't support the PSR पूर्णांकerrupt yet,
	 * on pipe B and C the same bit MBZ.
	 */
	अगर (drm_WARN_ON_ONCE(&dev_priv->drm,
			     status_mask & PIPE_A_PSR_STATUS_VLV))
		वापस 0;
	/*
	 * On pipe B and C we करोn't support the PSR पूर्णांकerrupt yet, on pipe
	 * A the same bit is क्रम perf counters which we करोn't use either.
	 */
	अगर (drm_WARN_ON_ONCE(&dev_priv->drm,
			     status_mask & PIPE_B_PSR_STATUS_VLV))
		वापस 0;

	enable_mask &= ~(PIPE_FIFO_UNDERRUN_STATUS |
			 SPRITE0_FLIP_DONE_INT_EN_VLV |
			 SPRITE1_FLIP_DONE_INT_EN_VLV);
	अगर (status_mask & SPRITE0_FLIP_DONE_INT_STATUS_VLV)
		enable_mask |= SPRITE0_FLIP_DONE_INT_EN_VLV;
	अगर (status_mask & SPRITE1_FLIP_DONE_INT_STATUS_VLV)
		enable_mask |= SPRITE1_FLIP_DONE_INT_EN_VLV;

out:
	drm_WARN_ONCE(&dev_priv->drm,
		      enable_mask & ~PIPESTAT_INT_ENABLE_MASK ||
		      status_mask & ~PIPESTAT_INT_STATUS_MASK,
		      "pipe %c: enable_mask=0x%x, status_mask=0x%x\n",
		      pipe_name(pipe), enable_mask, status_mask);

	वापस enable_mask;
पूर्ण

व्योम i915_enable_pipestat(काष्ठा drm_i915_निजी *dev_priv,
			  क्रमागत pipe pipe, u32 status_mask)
अणु
	i915_reg_t reg = PIPESTAT(pipe);
	u32 enable_mask;

	drm_WARN_ONCE(&dev_priv->drm, status_mask & ~PIPESTAT_INT_STATUS_MASK,
		      "pipe %c: status_mask=0x%x\n",
		      pipe_name(pipe), status_mask);

	lockdep_निश्चित_held(&dev_priv->irq_lock);
	drm_WARN_ON(&dev_priv->drm, !पूर्णांकel_irqs_enabled(dev_priv));

	अगर ((dev_priv->pipestat_irq_mask[pipe] & status_mask) == status_mask)
		वापस;

	dev_priv->pipestat_irq_mask[pipe] |= status_mask;
	enable_mask = i915_pipestat_enable_mask(dev_priv, pipe);

	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, reg, enable_mask | status_mask);
	पूर्णांकel_uncore_posting_पढ़ो(&dev_priv->uncore, reg);
पूर्ण

व्योम i915_disable_pipestat(काष्ठा drm_i915_निजी *dev_priv,
			   क्रमागत pipe pipe, u32 status_mask)
अणु
	i915_reg_t reg = PIPESTAT(pipe);
	u32 enable_mask;

	drm_WARN_ONCE(&dev_priv->drm, status_mask & ~PIPESTAT_INT_STATUS_MASK,
		      "pipe %c: status_mask=0x%x\n",
		      pipe_name(pipe), status_mask);

	lockdep_निश्चित_held(&dev_priv->irq_lock);
	drm_WARN_ON(&dev_priv->drm, !पूर्णांकel_irqs_enabled(dev_priv));

	अगर ((dev_priv->pipestat_irq_mask[pipe] & status_mask) == 0)
		वापस;

	dev_priv->pipestat_irq_mask[pipe] &= ~status_mask;
	enable_mask = i915_pipestat_enable_mask(dev_priv, pipe);

	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, reg, enable_mask | status_mask);
	पूर्णांकel_uncore_posting_पढ़ो(&dev_priv->uncore, reg);
पूर्ण

अटल bool i915_has_asle(काष्ठा drm_i915_निजी *dev_priv)
अणु
	अगर (!dev_priv->opregion.asle)
		वापस false;

	वापस IS_PINEVIEW(dev_priv) || IS_MOBILE(dev_priv);
पूर्ण

/**
 * i915_enable_asle_pipestat - enable ASLE pipestat क्रम OpRegion
 * @dev_priv: i915 device निजी
 */
अटल व्योम i915_enable_asle_pipestat(काष्ठा drm_i915_निजी *dev_priv)
अणु
	अगर (!i915_has_asle(dev_priv))
		वापस;

	spin_lock_irq(&dev_priv->irq_lock);

	i915_enable_pipestat(dev_priv, PIPE_B, PIPE_LEGACY_BLC_EVENT_STATUS);
	अगर (DISPLAY_VER(dev_priv) >= 4)
		i915_enable_pipestat(dev_priv, PIPE_A,
				     PIPE_LEGACY_BLC_EVENT_STATUS);

	spin_unlock_irq(&dev_priv->irq_lock);
पूर्ण

/*
 * This timing diagram depicts the video संकेत in and
 * around the vertical blanking period.
 *
 * Assumptions about the fictitious mode used in this example:
 *  vblank_start >= 3
 *  vsync_start = vblank_start + 1
 *  vsync_end = vblank_start + 2
 *  vtotal = vblank_start + 3
 *
 *           start of vblank:
 *           latch द्विगुन buffered रेजिस्टरs
 *           increment frame counter (ctg+)
 *           generate start of vblank पूर्णांकerrupt (gen4+)
 *           |
 *           |          frame start:
 *           |          generate frame start पूर्णांकerrupt (aka. vblank पूर्णांकerrupt) (gmch)
 *           |          may be shअगरted क्रमward 1-3 extra lines via PIPECONF
 *           |          |
 *           |          |  start of vsync:
 *           |          |  generate vsync पूर्णांकerrupt
 *           |          |  |
 * ___xxxx___    ___xxxx___    ___xxxx___    ___xxxx___    ___xxxx___    ___xxxx
 *       .   \hs/   .      \hs/          \hs/          \hs/   .      \hs/
 * ----va---> <-----------------vb--------------------> <--------va-------------
 *       |          |       <----vs----->                     |
 * -vbs-----> <---vbs+1---> <---vbs+2---> <-----0-----> <-----1-----> <-----2--- (scanline counter gen2)
 * -vbs-2---> <---vbs-1---> <---vbs-----> <---vbs+1---> <---vbs+2---> <-----0--- (scanline counter gen3+)
 * -vbs-2---> <---vbs-2---> <---vbs-1---> <---vbs-----> <---vbs+1---> <---vbs+2- (scanline counter hsw+ hdmi)
 *       |          |                                         |
 *       last visible pixel                                   first visible pixel
 *                  |                                         increment frame counter (gen3/4)
 *                  pixel counter = vblank_start * htotal     pixel counter = 0 (gen3/4)
 *
 * x  = horizontal active
 * _  = horizontal blanking
 * hs = horizontal sync
 * va = vertical active
 * vb = vertical blanking
 * vs = vertical sync
 * vbs = vblank_start (number)
 *
 * Summary:
 * - most events happen at the start of horizontal sync
 * - frame start happens at the start of horizontal blank, 1-4 lines
 *   (depending on PIPECONF settings) after the start of vblank
 * - gen3/4 pixel and frame counter are synchronized with the start
 *   of horizontal active on the first line of vertical active
 */

/* Called from drm generic code, passed a 'crtc', which
 * we use as a pipe index
 */
u32 i915_get_vblank_counter(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->dev);
	काष्ठा drm_vblank_crtc *vblank = &dev_priv->drm.vblank[drm_crtc_index(crtc)];
	स्थिर काष्ठा drm_display_mode *mode = &vblank->hwmode;
	क्रमागत pipe pipe = to_पूर्णांकel_crtc(crtc)->pipe;
	i915_reg_t high_frame, low_frame;
	u32 high1, high2, low, pixel, vbl_start, hsync_start, htotal;
	अचिन्हित दीर्घ irqflags;

	/*
	 * On i965gm TV output the frame counter only works up to
	 * the poपूर्णांक when we enable the TV encoder. After that the
	 * frame counter ceases to work and पढ़ोs zero. We need a
	 * vblank रुको beक्रमe enabling the TV encoder and so we
	 * have to enable vblank पूर्णांकerrupts जबतक the frame counter
	 * is still in a working state. However the core vblank code
	 * करोes not like us वापसing non-zero frame counter values
	 * when we've told it that we don't have a working frame
	 * counter. Thus we must stop non-zero values leaking out.
	 */
	अगर (!vblank->max_vblank_count)
		वापस 0;

	htotal = mode->crtc_htotal;
	hsync_start = mode->crtc_hsync_start;
	vbl_start = mode->crtc_vblank_start;
	अगर (mode->flags & DRM_MODE_FLAG_INTERLACE)
		vbl_start = DIV_ROUND_UP(vbl_start, 2);

	/* Convert to pixel count */
	vbl_start *= htotal;

	/* Start of vblank event occurs at start of hsync */
	vbl_start -= htotal - hsync_start;

	high_frame = PIPEFRAME(pipe);
	low_frame = PIPEFRAMEPIXEL(pipe);

	spin_lock_irqsave(&dev_priv->uncore.lock, irqflags);

	/*
	 * High & low रेजिस्टर fields aren't synchronized, so make sure
	 * we get a low value that's stable across two पढ़ोs of the high
	 * रेजिस्टर.
	 */
	करो अणु
		high1 = पूर्णांकel_de_पढ़ो_fw(dev_priv, high_frame) & PIPE_FRAME_HIGH_MASK;
		low   = पूर्णांकel_de_पढ़ो_fw(dev_priv, low_frame);
		high2 = पूर्णांकel_de_पढ़ो_fw(dev_priv, high_frame) & PIPE_FRAME_HIGH_MASK;
	पूर्ण जबतक (high1 != high2);

	spin_unlock_irqrestore(&dev_priv->uncore.lock, irqflags);

	high1 >>= PIPE_FRAME_HIGH_SHIFT;
	pixel = low & PIPE_PIXEL_MASK;
	low >>= PIPE_FRAME_LOW_SHIFT;

	/*
	 * The frame counter increments at beginning of active.
	 * Cook up a vblank counter by also checking the pixel
	 * counter against vblank start.
	 */
	वापस (((high1 << 8) | low) + (pixel >= vbl_start)) & 0xffffff;
पूर्ण

u32 g4x_get_vblank_counter(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->dev);
	काष्ठा drm_vblank_crtc *vblank = &dev_priv->drm.vblank[drm_crtc_index(crtc)];
	क्रमागत pipe pipe = to_पूर्णांकel_crtc(crtc)->pipe;

	अगर (!vblank->max_vblank_count)
		वापस 0;

	वापस पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, PIPE_FRMCOUNT_G4X(pipe));
पूर्ण

अटल u32 पूर्णांकel_crtc_scanlines_since_frame_बारtamp(काष्ठा पूर्णांकel_crtc *crtc)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	काष्ठा drm_vblank_crtc *vblank =
		&crtc->base.dev->vblank[drm_crtc_index(&crtc->base)];
	स्थिर काष्ठा drm_display_mode *mode = &vblank->hwmode;
	u32 htotal = mode->crtc_htotal;
	u32 घड़ी = mode->crtc_घड़ी;
	u32 scan_prev_समय, scan_curr_समय, scan_post_समय;

	/*
	 * To aव्योम the race condition where we might cross पूर्णांकo the
	 * next vblank just between the PIPE_FRMTMSTMP and TIMESTAMP_CTR
	 * पढ़ोs. We make sure we पढ़ो PIPE_FRMTMSTMP and TIMESTAMP_CTR
	 * during the same frame.
	 */
	करो अणु
		/*
		 * This field provides पढ़ो back of the display
		 * pipe frame समय stamp. The समय stamp value
		 * is sampled at every start of vertical blank.
		 */
		scan_prev_समय = पूर्णांकel_de_पढ़ो_fw(dev_priv,
						  PIPE_FRMTMSTMP(crtc->pipe));

		/*
		 * The TIMESTAMP_CTR रेजिस्टर has the current
		 * समय stamp value.
		 */
		scan_curr_समय = पूर्णांकel_de_पढ़ो_fw(dev_priv, IVB_TIMESTAMP_CTR);

		scan_post_समय = पूर्णांकel_de_पढ़ो_fw(dev_priv,
						  PIPE_FRMTMSTMP(crtc->pipe));
	पूर्ण जबतक (scan_post_समय != scan_prev_समय);

	वापस भाग_u64(mul_u32_u32(scan_curr_समय - scan_prev_समय,
				   घड़ी), 1000 * htotal);
पूर्ण

/*
 * On certain encoders on certain platक्रमms, pipe
 * scanline रेजिस्टर will not work to get the scanline,
 * since the timings are driven from the PORT or issues
 * with scanline रेजिस्टर updates.
 * This function will use Framestamp and current
 * बारtamp रेजिस्टरs to calculate the scanline.
 */
अटल u32 __पूर्णांकel_get_crtc_scanline_from_बारtamp(काष्ठा पूर्णांकel_crtc *crtc)
अणु
	काष्ठा drm_vblank_crtc *vblank =
		&crtc->base.dev->vblank[drm_crtc_index(&crtc->base)];
	स्थिर काष्ठा drm_display_mode *mode = &vblank->hwmode;
	u32 vblank_start = mode->crtc_vblank_start;
	u32 vtotal = mode->crtc_vtotal;
	u32 scanline;

	scanline = पूर्णांकel_crtc_scanlines_since_frame_बारtamp(crtc);
	scanline = min(scanline, vtotal - 1);
	scanline = (scanline + vblank_start) % vtotal;

	वापस scanline;
पूर्ण

/*
 * पूर्णांकel_de_पढ़ो_fw(), only क्रम fast पढ़ोs of display block, no need क्रम
 * क्रमcewake etc.
 */
अटल पूर्णांक __पूर्णांकel_get_crtc_scanline(काष्ठा पूर्णांकel_crtc *crtc)
अणु
	काष्ठा drm_device *dev = crtc->base.dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	स्थिर काष्ठा drm_display_mode *mode;
	काष्ठा drm_vblank_crtc *vblank;
	क्रमागत pipe pipe = crtc->pipe;
	पूर्णांक position, vtotal;

	अगर (!crtc->active)
		वापस 0;

	vblank = &crtc->base.dev->vblank[drm_crtc_index(&crtc->base)];
	mode = &vblank->hwmode;

	अगर (crtc->mode_flags & I915_MODE_FLAG_GET_SCANLINE_FROM_TIMESTAMP)
		वापस __पूर्णांकel_get_crtc_scanline_from_बारtamp(crtc);

	vtotal = mode->crtc_vtotal;
	अगर (mode->flags & DRM_MODE_FLAG_INTERLACE)
		vtotal /= 2;

	अगर (IS_DISPLAY_VER(dev_priv, 2))
		position = पूर्णांकel_de_पढ़ो_fw(dev_priv, PIPEDSL(pipe)) & DSL_LINEMASK_GEN2;
	अन्यथा
		position = पूर्णांकel_de_पढ़ो_fw(dev_priv, PIPEDSL(pipe)) & DSL_LINEMASK_GEN3;

	/*
	 * On HSW, the DSL reg (0x70000) appears to वापस 0 अगर we
	 * पढ़ो it just beक्रमe the start of vblank.  So try it again
	 * so we करोn't accidentally end up spanning a vblank frame
	 * increment, causing the pipe_update_end() code to squak at us.
	 *
	 * The nature of this problem means we can't simply check the ISR
	 * bit and वापस the vblank start value; nor can we use the scanline
	 * debug रेजिस्टर in the transcoder as it appears to have the same
	 * problem.  We may need to extend this to include other platक्रमms,
	 * but so far testing only shows the problem on HSW.
	 */
	अगर (HAS_DDI(dev_priv) && !position) अणु
		पूर्णांक i, temp;

		क्रम (i = 0; i < 100; i++) अणु
			udelay(1);
			temp = पूर्णांकel_de_पढ़ो_fw(dev_priv, PIPEDSL(pipe)) & DSL_LINEMASK_GEN3;
			अगर (temp != position) अणु
				position = temp;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * See update_scanline_offset() क्रम the details on the
	 * scanline_offset adjusपंचांगent.
	 */
	वापस (position + crtc->scanline_offset) % vtotal;
पूर्ण

अटल bool i915_get_crtc_scanoutpos(काष्ठा drm_crtc *_crtc,
				     bool in_vblank_irq,
				     पूर्णांक *vpos, पूर्णांक *hpos,
				     kसमय_प्रकार *sसमय, kसमय_प्रकार *eसमय,
				     स्थिर काष्ठा drm_display_mode *mode)
अणु
	काष्ठा drm_device *dev = _crtc->dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(_crtc);
	क्रमागत pipe pipe = crtc->pipe;
	पूर्णांक position;
	पूर्णांक vbl_start, vbl_end, hsync_start, htotal, vtotal;
	अचिन्हित दीर्घ irqflags;
	bool use_scanline_counter = DISPLAY_VER(dev_priv) >= 5 ||
		IS_G4X(dev_priv) || IS_DISPLAY_VER(dev_priv, 2) ||
		crtc->mode_flags & I915_MODE_FLAG_USE_SCANLINE_COUNTER;

	अगर (drm_WARN_ON(&dev_priv->drm, !mode->crtc_घड़ी)) अणु
		drm_dbg(&dev_priv->drm,
			"trying to get scanoutpos for disabled "
			"pipe %c\n", pipe_name(pipe));
		वापस false;
	पूर्ण

	htotal = mode->crtc_htotal;
	hsync_start = mode->crtc_hsync_start;
	vtotal = mode->crtc_vtotal;
	vbl_start = mode->crtc_vblank_start;
	vbl_end = mode->crtc_vblank_end;

	अगर (mode->flags & DRM_MODE_FLAG_INTERLACE) अणु
		vbl_start = DIV_ROUND_UP(vbl_start, 2);
		vbl_end /= 2;
		vtotal /= 2;
	पूर्ण

	/*
	 * Lock uncore.lock, as we will करो multiple timing critical raw
	 * रेजिस्टर पढ़ोs, potentially with preemption disabled, so the
	 * following code must not block on uncore.lock.
	 */
	spin_lock_irqsave(&dev_priv->uncore.lock, irqflags);

	/* preempt_disable_rt() should go right here in PREEMPT_RT patchset. */

	/* Get optional प्रणाली बारtamp beक्रमe query. */
	अगर (sसमय)
		*sसमय = kसमय_get();

	अगर (crtc->mode_flags & I915_MODE_FLAG_VRR) अणु
		पूर्णांक scanlines = पूर्णांकel_crtc_scanlines_since_frame_बारtamp(crtc);

		position = __पूर्णांकel_get_crtc_scanline(crtc);

		/*
		 * Alपढ़ोy निकासing vblank? If so, shअगरt our position
		 * so it looks like we're alपढ़ोy apporaching the full
		 * vblank end. This should make the generated बारtamp
		 * more or less match when the active portion will start.
		 */
		अगर (position >= vbl_start && scanlines < position)
			position = min(crtc->vmax_vblank_start + scanlines, vtotal - 1);
	पूर्ण अन्यथा अगर (use_scanline_counter) अणु
		/* No obvious pixelcount रेजिस्टर. Only query vertical
		 * scanout position from Display scan line रेजिस्टर.
		 */
		position = __पूर्णांकel_get_crtc_scanline(crtc);
	पूर्ण अन्यथा अणु
		/* Have access to pixelcount since start of frame.
		 * We can split this पूर्णांकo vertical and horizontal
		 * scanout position.
		 */
		position = (पूर्णांकel_de_पढ़ो_fw(dev_priv, PIPEFRAMEPIXEL(pipe)) & PIPE_PIXEL_MASK) >> PIPE_PIXEL_SHIFT;

		/* convert to pixel counts */
		vbl_start *= htotal;
		vbl_end *= htotal;
		vtotal *= htotal;

		/*
		 * In पूर्णांकerlaced modes, the pixel counter counts all pixels,
		 * so one field will have htotal more pixels. In order to aव्योम
		 * the reported position from jumping backwards when the pixel
		 * counter is beyond the length of the लघुer field, just
		 * clamp the position the length of the लघुer field. This
		 * matches how the scanline counter based position works since
		 * the scanline counter करोesn't count the two half lines.
		 */
		अगर (position >= vtotal)
			position = vtotal - 1;

		/*
		 * Start of vblank पूर्णांकerrupt is triggered at start of hsync,
		 * just prior to the first active line of vblank. However we
		 * consider lines to start at the leading edge of horizontal
		 * active. So, should we get here beक्रमe we've crossed पूर्णांकo
		 * the horizontal active of the first line in vblank, we would
		 * not set the DRM_SCANOUTPOS_INVBL flag. In order to fix that,
		 * always add htotal-hsync_start to the current pixel position.
		 */
		position = (position + htotal - hsync_start) % vtotal;
	पूर्ण

	/* Get optional प्रणाली बारtamp after query. */
	अगर (eसमय)
		*eसमय = kसमय_get();

	/* preempt_enable_rt() should go right here in PREEMPT_RT patchset. */

	spin_unlock_irqrestore(&dev_priv->uncore.lock, irqflags);

	/*
	 * While in vblank, position will be negative
	 * counting up towards 0 at vbl_end. And outside
	 * vblank, position will be positive counting
	 * up since vbl_end.
	 */
	अगर (position >= vbl_start)
		position -= vbl_end;
	अन्यथा
		position += vtotal - vbl_end;

	अगर (use_scanline_counter) अणु
		*vpos = position;
		*hpos = 0;
	पूर्ण अन्यथा अणु
		*vpos = position / htotal;
		*hpos = position - (*vpos * htotal);
	पूर्ण

	वापस true;
पूर्ण

bool पूर्णांकel_crtc_get_vblank_बारtamp(काष्ठा drm_crtc *crtc, पूर्णांक *max_error,
				     kसमय_प्रकार *vblank_समय, bool in_vblank_irq)
अणु
	वापस drm_crtc_vblank_helper_get_vblank_बारtamp_पूर्णांकernal(
		crtc, max_error, vblank_समय, in_vblank_irq,
		i915_get_crtc_scanoutpos);
पूर्ण

पूर्णांक पूर्णांकel_get_crtc_scanline(काष्ठा पूर्णांकel_crtc *crtc)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	अचिन्हित दीर्घ irqflags;
	पूर्णांक position;

	spin_lock_irqsave(&dev_priv->uncore.lock, irqflags);
	position = __पूर्णांकel_get_crtc_scanline(crtc);
	spin_unlock_irqrestore(&dev_priv->uncore.lock, irqflags);

	वापस position;
पूर्ण

/**
 * ivb_parity_work - Workqueue called when a parity error पूर्णांकerrupt
 * occurred.
 * @work: workqueue काष्ठा
 *
 * Doesn't actually करो anything except notअगरy userspace. As a consequence of
 * this event, userspace should try to remap the bad rows since statistically
 * it is likely the same row is more likely to go bad again.
 */
अटल व्योम ivb_parity_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा drm_i915_निजी *dev_priv =
		container_of(work, typeof(*dev_priv), l3_parity.error_work);
	काष्ठा पूर्णांकel_gt *gt = &dev_priv->gt;
	u32 error_status, row, bank, subbank;
	अक्षर *parity_event[6];
	u32 misccpctl;
	u8 slice = 0;

	/* We must turn off DOP level घड़ी gating to access the L3 रेजिस्टरs.
	 * In order to prevent a get/put style पूर्णांकerface, acquire काष्ठा mutex
	 * any समय we access those रेजिस्टरs.
	 */
	mutex_lock(&dev_priv->drm.काष्ठा_mutex);

	/* If we've screwed up tracking, just let the पूर्णांकerrupt fire again */
	अगर (drm_WARN_ON(&dev_priv->drm, !dev_priv->l3_parity.which_slice))
		जाओ out;

	misccpctl = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, GEN7_MISCCPCTL);
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, GEN7_MISCCPCTL, misccpctl & ~GEN7_DOP_CLOCK_GATE_ENABLE);
	पूर्णांकel_uncore_posting_पढ़ो(&dev_priv->uncore, GEN7_MISCCPCTL);

	जबतक ((slice = ffs(dev_priv->l3_parity.which_slice)) != 0) अणु
		i915_reg_t reg;

		slice--;
		अगर (drm_WARN_ON_ONCE(&dev_priv->drm,
				     slice >= NUM_L3_SLICES(dev_priv)))
			अवरोध;

		dev_priv->l3_parity.which_slice &= ~(1<<slice);

		reg = GEN7_L3CDERRST1(slice);

		error_status = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, reg);
		row = GEN7_PARITY_ERROR_ROW(error_status);
		bank = GEN7_PARITY_ERROR_BANK(error_status);
		subbank = GEN7_PARITY_ERROR_SUBBANK(error_status);

		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, reg, GEN7_PARITY_ERROR_VALID | GEN7_L3CDERRST1_ENABLE);
		पूर्णांकel_uncore_posting_पढ़ो(&dev_priv->uncore, reg);

		parity_event[0] = I915_L3_PARITY_UEVENT "=1";
		parity_event[1] = kaप्र_लिखो(GFP_KERNEL, "ROW=%d", row);
		parity_event[2] = kaप्र_लिखो(GFP_KERNEL, "BANK=%d", bank);
		parity_event[3] = kaप्र_लिखो(GFP_KERNEL, "SUBBANK=%d", subbank);
		parity_event[4] = kaप्र_लिखो(GFP_KERNEL, "SLICE=%d", slice);
		parity_event[5] = शून्य;

		kobject_uevent_env(&dev_priv->drm.primary->kdev->kobj,
				   KOBJ_CHANGE, parity_event);

		DRM_DEBUG("Parity error: Slice = %d, Row = %d, Bank = %d, Sub bank = %d.\n",
			  slice, row, bank, subbank);

		kमुक्त(parity_event[4]);
		kमुक्त(parity_event[3]);
		kमुक्त(parity_event[2]);
		kमुक्त(parity_event[1]);
	पूर्ण

	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, GEN7_MISCCPCTL, misccpctl);

out:
	drm_WARN_ON(&dev_priv->drm, dev_priv->l3_parity.which_slice);
	spin_lock_irq(&gt->irq_lock);
	gen5_gt_enable_irq(gt, GT_PARITY_ERROR(dev_priv));
	spin_unlock_irq(&gt->irq_lock);

	mutex_unlock(&dev_priv->drm.काष्ठा_mutex);
पूर्ण

अटल bool gen11_port_hotplug_दीर्घ_detect(क्रमागत hpd_pin pin, u32 val)
अणु
	चयन (pin) अणु
	हाल HPD_PORT_TC1:
	हाल HPD_PORT_TC2:
	हाल HPD_PORT_TC3:
	हाल HPD_PORT_TC4:
	हाल HPD_PORT_TC5:
	हाल HPD_PORT_TC6:
		वापस val & GEN11_HOTPLUG_CTL_LONG_DETECT(pin);
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool bxt_port_hotplug_दीर्घ_detect(क्रमागत hpd_pin pin, u32 val)
अणु
	चयन (pin) अणु
	हाल HPD_PORT_A:
		वापस val & PORTA_HOTPLUG_LONG_DETECT;
	हाल HPD_PORT_B:
		वापस val & PORTB_HOTPLUG_LONG_DETECT;
	हाल HPD_PORT_C:
		वापस val & PORTC_HOTPLUG_LONG_DETECT;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool icp_ddi_port_hotplug_दीर्घ_detect(क्रमागत hpd_pin pin, u32 val)
अणु
	चयन (pin) अणु
	हाल HPD_PORT_A:
	हाल HPD_PORT_B:
	हाल HPD_PORT_C:
	हाल HPD_PORT_D:
		वापस val & SHOTPLUG_CTL_DDI_HPD_LONG_DETECT(pin);
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool icp_tc_port_hotplug_दीर्घ_detect(क्रमागत hpd_pin pin, u32 val)
अणु
	चयन (pin) अणु
	हाल HPD_PORT_TC1:
	हाल HPD_PORT_TC2:
	हाल HPD_PORT_TC3:
	हाल HPD_PORT_TC4:
	हाल HPD_PORT_TC5:
	हाल HPD_PORT_TC6:
		वापस val & ICP_TC_HPD_LONG_DETECT(pin);
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool spt_port_hotplug2_दीर्घ_detect(क्रमागत hpd_pin pin, u32 val)
अणु
	चयन (pin) अणु
	हाल HPD_PORT_E:
		वापस val & PORTE_HOTPLUG_LONG_DETECT;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool spt_port_hotplug_दीर्घ_detect(क्रमागत hpd_pin pin, u32 val)
अणु
	चयन (pin) अणु
	हाल HPD_PORT_A:
		वापस val & PORTA_HOTPLUG_LONG_DETECT;
	हाल HPD_PORT_B:
		वापस val & PORTB_HOTPLUG_LONG_DETECT;
	हाल HPD_PORT_C:
		वापस val & PORTC_HOTPLUG_LONG_DETECT;
	हाल HPD_PORT_D:
		वापस val & PORTD_HOTPLUG_LONG_DETECT;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool ilk_port_hotplug_दीर्घ_detect(क्रमागत hpd_pin pin, u32 val)
अणु
	चयन (pin) अणु
	हाल HPD_PORT_A:
		वापस val & DIGITAL_PORTA_HOTPLUG_LONG_DETECT;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool pch_port_hotplug_दीर्घ_detect(क्रमागत hpd_pin pin, u32 val)
अणु
	चयन (pin) अणु
	हाल HPD_PORT_B:
		वापस val & PORTB_HOTPLUG_LONG_DETECT;
	हाल HPD_PORT_C:
		वापस val & PORTC_HOTPLUG_LONG_DETECT;
	हाल HPD_PORT_D:
		वापस val & PORTD_HOTPLUG_LONG_DETECT;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool i9xx_port_hotplug_दीर्घ_detect(क्रमागत hpd_pin pin, u32 val)
अणु
	चयन (pin) अणु
	हाल HPD_PORT_B:
		वापस val & PORTB_HOTPLUG_INT_LONG_PULSE;
	हाल HPD_PORT_C:
		वापस val & PORTC_HOTPLUG_INT_LONG_PULSE;
	हाल HPD_PORT_D:
		वापस val & PORTD_HOTPLUG_INT_LONG_PULSE;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

/*
 * Get a bit mask of pins that have triggered, and which ones may be दीर्घ.
 * This can be called multiple बार with the same masks to accumulate
 * hotplug detection results from several रेजिस्टरs.
 *
 * Note that the caller is expected to zero out the masks initially.
 */
अटल व्योम पूर्णांकel_get_hpd_pins(काष्ठा drm_i915_निजी *dev_priv,
			       u32 *pin_mask, u32 *दीर्घ_mask,
			       u32 hotplug_trigger, u32 dig_hotplug_reg,
			       स्थिर u32 hpd[HPD_NUM_PINS],
			       bool दीर्घ_pulse_detect(क्रमागत hpd_pin pin, u32 val))
अणु
	क्रमागत hpd_pin pin;

	BUILD_BUG_ON(BITS_PER_TYPE(*pin_mask) < HPD_NUM_PINS);

	क्रम_each_hpd_pin(pin) अणु
		अगर ((hpd[pin] & hotplug_trigger) == 0)
			जारी;

		*pin_mask |= BIT(pin);

		अगर (दीर्घ_pulse_detect(pin, dig_hotplug_reg))
			*दीर्घ_mask |= BIT(pin);
	पूर्ण

	drm_dbg(&dev_priv->drm,
		"hotplug event received, stat 0x%08x, dig 0x%08x, pins 0x%08x, long 0x%08x\n",
		hotplug_trigger, dig_hotplug_reg, *pin_mask, *दीर्घ_mask);

पूर्ण

अटल u32 पूर्णांकel_hpd_enabled_irqs(काष्ठा drm_i915_निजी *dev_priv,
				  स्थिर u32 hpd[HPD_NUM_PINS])
अणु
	काष्ठा पूर्णांकel_encoder *encoder;
	u32 enabled_irqs = 0;

	क्रम_each_पूर्णांकel_encoder(&dev_priv->drm, encoder)
		अगर (dev_priv->hotplug.stats[encoder->hpd_pin].state == HPD_ENABLED)
			enabled_irqs |= hpd[encoder->hpd_pin];

	वापस enabled_irqs;
पूर्ण

अटल u32 पूर्णांकel_hpd_hotplug_irqs(काष्ठा drm_i915_निजी *dev_priv,
				  स्थिर u32 hpd[HPD_NUM_PINS])
अणु
	काष्ठा पूर्णांकel_encoder *encoder;
	u32 hotplug_irqs = 0;

	क्रम_each_पूर्णांकel_encoder(&dev_priv->drm, encoder)
		hotplug_irqs |= hpd[encoder->hpd_pin];

	वापस hotplug_irqs;
पूर्ण

अटल u32 पूर्णांकel_hpd_hotplug_enables(काष्ठा drm_i915_निजी *i915,
				     hotplug_enables_func hotplug_enables)
अणु
	काष्ठा पूर्णांकel_encoder *encoder;
	u32 hotplug = 0;

	क्रम_each_पूर्णांकel_encoder(&i915->drm, encoder)
		hotplug |= hotplug_enables(i915, encoder->hpd_pin);

	वापस hotplug;
पूर्ण

अटल व्योम gmbus_irq_handler(काष्ठा drm_i915_निजी *dev_priv)
अणु
	wake_up_all(&dev_priv->gmbus_रुको_queue);
पूर्ण

अटल व्योम dp_aux_irq_handler(काष्ठा drm_i915_निजी *dev_priv)
अणु
	wake_up_all(&dev_priv->gmbus_रुको_queue);
पूर्ण

#अगर defined(CONFIG_DEBUG_FS)
अटल व्योम display_pipe_crc_irq_handler(काष्ठा drm_i915_निजी *dev_priv,
					 क्रमागत pipe pipe,
					 u32 crc0, u32 crc1,
					 u32 crc2, u32 crc3,
					 u32 crc4)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = पूर्णांकel_get_crtc_क्रम_pipe(dev_priv, pipe);
	काष्ठा पूर्णांकel_pipe_crc *pipe_crc = &crtc->pipe_crc;
	u32 crcs[5] = अणु crc0, crc1, crc2, crc3, crc4 पूर्ण;

	trace_पूर्णांकel_pipe_crc(crtc, crcs);

	spin_lock(&pipe_crc->lock);
	/*
	 * For some not yet identअगरied reason, the first CRC is
	 * bonkers. So let's just रुको क्रम the next vblank and पढ़ो
	 * out the buggy result.
	 *
	 * On GEN8+ someबार the second CRC is bonkers as well, so
	 * करोn't trust that one either.
	 */
	अगर (pipe_crc->skipped <= 0 ||
	    (DISPLAY_VER(dev_priv) >= 8 && pipe_crc->skipped == 1)) अणु
		pipe_crc->skipped++;
		spin_unlock(&pipe_crc->lock);
		वापस;
	पूर्ण
	spin_unlock(&pipe_crc->lock);

	drm_crtc_add_crc_entry(&crtc->base, true,
				drm_crtc_accurate_vblank_count(&crtc->base),
				crcs);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम
display_pipe_crc_irq_handler(काष्ठा drm_i915_निजी *dev_priv,
			     क्रमागत pipe pipe,
			     u32 crc0, u32 crc1,
			     u32 crc2, u32 crc3,
			     u32 crc4) अणुपूर्ण
#पूर्ण_अगर

अटल व्योम flip_करोne_handler(काष्ठा drm_i915_निजी *i915,
			      क्रमागत pipe pipe)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = पूर्णांकel_get_crtc_क्रम_pipe(i915, pipe);
	काष्ठा drm_crtc_state *crtc_state = crtc->base.state;
	काष्ठा drm_pending_vblank_event *e = crtc_state->event;
	काष्ठा drm_device *dev = &i915->drm;
	अचिन्हित दीर्घ irqflags;

	spin_lock_irqsave(&dev->event_lock, irqflags);

	crtc_state->event = शून्य;

	drm_crtc_send_vblank_event(&crtc->base, e);

	spin_unlock_irqrestore(&dev->event_lock, irqflags);
पूर्ण

अटल व्योम hsw_pipe_crc_irq_handler(काष्ठा drm_i915_निजी *dev_priv,
				     क्रमागत pipe pipe)
अणु
	display_pipe_crc_irq_handler(dev_priv, pipe,
				     पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, PIPE_CRC_RES_1_IVB(pipe)),
				     0, 0, 0, 0);
पूर्ण

अटल व्योम ivb_pipe_crc_irq_handler(काष्ठा drm_i915_निजी *dev_priv,
				     क्रमागत pipe pipe)
अणु
	display_pipe_crc_irq_handler(dev_priv, pipe,
				     पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, PIPE_CRC_RES_1_IVB(pipe)),
				     पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, PIPE_CRC_RES_2_IVB(pipe)),
				     पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, PIPE_CRC_RES_3_IVB(pipe)),
				     पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, PIPE_CRC_RES_4_IVB(pipe)),
				     पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, PIPE_CRC_RES_5_IVB(pipe)));
पूर्ण

अटल व्योम i9xx_pipe_crc_irq_handler(काष्ठा drm_i915_निजी *dev_priv,
				      क्रमागत pipe pipe)
अणु
	u32 res1, res2;

	अगर (DISPLAY_VER(dev_priv) >= 3)
		res1 = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, PIPE_CRC_RES_RES1_I915(pipe));
	अन्यथा
		res1 = 0;

	अगर (DISPLAY_VER(dev_priv) >= 5 || IS_G4X(dev_priv))
		res2 = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, PIPE_CRC_RES_RES2_G4X(pipe));
	अन्यथा
		res2 = 0;

	display_pipe_crc_irq_handler(dev_priv, pipe,
				     पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, PIPE_CRC_RES_RED(pipe)),
				     पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, PIPE_CRC_RES_GREEN(pipe)),
				     पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, PIPE_CRC_RES_BLUE(pipe)),
				     res1, res2);
पूर्ण

अटल व्योम i9xx_pipestat_irq_reset(काष्ठा drm_i915_निजी *dev_priv)
अणु
	क्रमागत pipe pipe;

	क्रम_each_pipe(dev_priv, pipe) अणु
		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, PIPESTAT(pipe),
			   PIPESTAT_INT_STATUS_MASK |
			   PIPE_FIFO_UNDERRUN_STATUS);

		dev_priv->pipestat_irq_mask[pipe] = 0;
	पूर्ण
पूर्ण

अटल व्योम i9xx_pipestat_irq_ack(काष्ठा drm_i915_निजी *dev_priv,
				  u32 iir, u32 pipe_stats[I915_MAX_PIPES])
अणु
	क्रमागत pipe pipe;

	spin_lock(&dev_priv->irq_lock);

	अगर (!dev_priv->display_irqs_enabled) अणु
		spin_unlock(&dev_priv->irq_lock);
		वापस;
	पूर्ण

	क्रम_each_pipe(dev_priv, pipe) अणु
		i915_reg_t reg;
		u32 status_mask, enable_mask, iir_bit = 0;

		/*
		 * PIPESTAT bits get संकेतled even when the पूर्णांकerrupt is
		 * disabled with the mask bits, and some of the status bits करो
		 * not generate पूर्णांकerrupts at all (like the underrun bit). Hence
		 * we need to be careful that we only handle what we want to
		 * handle.
		 */

		/* fअगरo underruns are filterered in the underrun handler. */
		status_mask = PIPE_FIFO_UNDERRUN_STATUS;

		चयन (pipe) अणु
		शेष:
		हाल PIPE_A:
			iir_bit = I915_DISPLAY_PIPE_A_EVENT_INTERRUPT;
			अवरोध;
		हाल PIPE_B:
			iir_bit = I915_DISPLAY_PIPE_B_EVENT_INTERRUPT;
			अवरोध;
		हाल PIPE_C:
			iir_bit = I915_DISPLAY_PIPE_C_EVENT_INTERRUPT;
			अवरोध;
		पूर्ण
		अगर (iir & iir_bit)
			status_mask |= dev_priv->pipestat_irq_mask[pipe];

		अगर (!status_mask)
			जारी;

		reg = PIPESTAT(pipe);
		pipe_stats[pipe] = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, reg) & status_mask;
		enable_mask = i915_pipestat_enable_mask(dev_priv, pipe);

		/*
		 * Clear the PIPE*STAT regs beक्रमe the IIR
		 *
		 * Toggle the enable bits to make sure we get an
		 * edge in the ISR pipe event bit अगर we करोn't clear
		 * all the enabled status bits. Otherwise the edge
		 * triggered IIR on i965/g4x wouldn't notice that
		 * an पूर्णांकerrupt is still pending.
		 */
		अगर (pipe_stats[pipe]) अणु
			पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, reg, pipe_stats[pipe]);
			पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, reg, enable_mask);
		पूर्ण
	पूर्ण
	spin_unlock(&dev_priv->irq_lock);
पूर्ण

अटल व्योम i8xx_pipestat_irq_handler(काष्ठा drm_i915_निजी *dev_priv,
				      u16 iir, u32 pipe_stats[I915_MAX_PIPES])
अणु
	क्रमागत pipe pipe;

	क्रम_each_pipe(dev_priv, pipe) अणु
		अगर (pipe_stats[pipe] & PIPE_VBLANK_INTERRUPT_STATUS)
			पूर्णांकel_handle_vblank(dev_priv, pipe);

		अगर (pipe_stats[pipe] & PIPE_CRC_DONE_INTERRUPT_STATUS)
			i9xx_pipe_crc_irq_handler(dev_priv, pipe);

		अगर (pipe_stats[pipe] & PIPE_FIFO_UNDERRUN_STATUS)
			पूर्णांकel_cpu_fअगरo_underrun_irq_handler(dev_priv, pipe);
	पूर्ण
पूर्ण

अटल व्योम i915_pipestat_irq_handler(काष्ठा drm_i915_निजी *dev_priv,
				      u32 iir, u32 pipe_stats[I915_MAX_PIPES])
अणु
	bool blc_event = false;
	क्रमागत pipe pipe;

	क्रम_each_pipe(dev_priv, pipe) अणु
		अगर (pipe_stats[pipe] & PIPE_VBLANK_INTERRUPT_STATUS)
			पूर्णांकel_handle_vblank(dev_priv, pipe);

		अगर (pipe_stats[pipe] & PIPE_LEGACY_BLC_EVENT_STATUS)
			blc_event = true;

		अगर (pipe_stats[pipe] & PIPE_CRC_DONE_INTERRUPT_STATUS)
			i9xx_pipe_crc_irq_handler(dev_priv, pipe);

		अगर (pipe_stats[pipe] & PIPE_FIFO_UNDERRUN_STATUS)
			पूर्णांकel_cpu_fअगरo_underrun_irq_handler(dev_priv, pipe);
	पूर्ण

	अगर (blc_event || (iir & I915_ASLE_INTERRUPT))
		पूर्णांकel_opregion_asle_पूर्णांकr(dev_priv);
पूर्ण

अटल व्योम i965_pipestat_irq_handler(काष्ठा drm_i915_निजी *dev_priv,
				      u32 iir, u32 pipe_stats[I915_MAX_PIPES])
अणु
	bool blc_event = false;
	क्रमागत pipe pipe;

	क्रम_each_pipe(dev_priv, pipe) अणु
		अगर (pipe_stats[pipe] & PIPE_START_VBLANK_INTERRUPT_STATUS)
			पूर्णांकel_handle_vblank(dev_priv, pipe);

		अगर (pipe_stats[pipe] & PIPE_LEGACY_BLC_EVENT_STATUS)
			blc_event = true;

		अगर (pipe_stats[pipe] & PIPE_CRC_DONE_INTERRUPT_STATUS)
			i9xx_pipe_crc_irq_handler(dev_priv, pipe);

		अगर (pipe_stats[pipe] & PIPE_FIFO_UNDERRUN_STATUS)
			पूर्णांकel_cpu_fअगरo_underrun_irq_handler(dev_priv, pipe);
	पूर्ण

	अगर (blc_event || (iir & I915_ASLE_INTERRUPT))
		पूर्णांकel_opregion_asle_पूर्णांकr(dev_priv);

	अगर (pipe_stats[0] & PIPE_GMBUS_INTERRUPT_STATUS)
		gmbus_irq_handler(dev_priv);
पूर्ण

अटल व्योम valleyview_pipestat_irq_handler(काष्ठा drm_i915_निजी *dev_priv,
					    u32 pipe_stats[I915_MAX_PIPES])
अणु
	क्रमागत pipe pipe;

	क्रम_each_pipe(dev_priv, pipe) अणु
		अगर (pipe_stats[pipe] & PIPE_START_VBLANK_INTERRUPT_STATUS)
			पूर्णांकel_handle_vblank(dev_priv, pipe);

		अगर (pipe_stats[pipe] & PLANE_FLIP_DONE_INT_STATUS_VLV)
			flip_करोne_handler(dev_priv, pipe);

		अगर (pipe_stats[pipe] & PIPE_CRC_DONE_INTERRUPT_STATUS)
			i9xx_pipe_crc_irq_handler(dev_priv, pipe);

		अगर (pipe_stats[pipe] & PIPE_FIFO_UNDERRUN_STATUS)
			पूर्णांकel_cpu_fअगरo_underrun_irq_handler(dev_priv, pipe);
	पूर्ण

	अगर (pipe_stats[0] & PIPE_GMBUS_INTERRUPT_STATUS)
		gmbus_irq_handler(dev_priv);
पूर्ण

अटल u32 i9xx_hpd_irq_ack(काष्ठा drm_i915_निजी *dev_priv)
अणु
	u32 hotplug_status = 0, hotplug_status_mask;
	पूर्णांक i;

	अगर (IS_G4X(dev_priv) ||
	    IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv))
		hotplug_status_mask = HOTPLUG_INT_STATUS_G4X |
			DP_AUX_CHANNEL_MASK_INT_STATUS_G4X;
	अन्यथा
		hotplug_status_mask = HOTPLUG_INT_STATUS_I915;

	/*
	 * We असलolutely have to clear all the pending पूर्णांकerrupt
	 * bits in PORT_HOTPLUG_STAT. Otherwise the ISR port
	 * पूर्णांकerrupt bit won't have an edge, and the i965/g4x
	 * edge triggered IIR will not notice that an पूर्णांकerrupt
	 * is still pending. We can't use PORT_HOTPLUG_EN to
	 * guarantee the edge as the act of toggling the enable
	 * bits can itself generate a new hotplug पूर्णांकerrupt :(
	 */
	क्रम (i = 0; i < 10; i++) अणु
		u32 पंचांगp = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, PORT_HOTPLUG_STAT) & hotplug_status_mask;

		अगर (पंचांगp == 0)
			वापस hotplug_status;

		hotplug_status |= पंचांगp;
		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, PORT_HOTPLUG_STAT, hotplug_status);
	पूर्ण

	drm_WARN_ONCE(&dev_priv->drm, 1,
		      "PORT_HOTPLUG_STAT did not clear (0x%08x)\n",
		      पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, PORT_HOTPLUG_STAT));

	वापस hotplug_status;
पूर्ण

अटल व्योम i9xx_hpd_irq_handler(काष्ठा drm_i915_निजी *dev_priv,
				 u32 hotplug_status)
अणु
	u32 pin_mask = 0, दीर्घ_mask = 0;
	u32 hotplug_trigger;

	अगर (IS_G4X(dev_priv) ||
	    IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv))
		hotplug_trigger = hotplug_status & HOTPLUG_INT_STATUS_G4X;
	अन्यथा
		hotplug_trigger = hotplug_status & HOTPLUG_INT_STATUS_I915;

	अगर (hotplug_trigger) अणु
		पूर्णांकel_get_hpd_pins(dev_priv, &pin_mask, &दीर्घ_mask,
				   hotplug_trigger, hotplug_trigger,
				   dev_priv->hotplug.hpd,
				   i9xx_port_hotplug_दीर्घ_detect);

		पूर्णांकel_hpd_irq_handler(dev_priv, pin_mask, दीर्घ_mask);
	पूर्ण

	अगर ((IS_G4X(dev_priv) ||
	     IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv)) &&
	    hotplug_status & DP_AUX_CHANNEL_MASK_INT_STATUS_G4X)
		dp_aux_irq_handler(dev_priv);
पूर्ण

अटल irqवापस_t valleyview_irq_handler(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा drm_i915_निजी *dev_priv = arg;
	irqवापस_t ret = IRQ_NONE;

	अगर (!पूर्णांकel_irqs_enabled(dev_priv))
		वापस IRQ_NONE;

	/* IRQs are synced during runसमय_suspend, we करोn't require a wakeref */
	disable_rpm_wakeref_निश्चितs(&dev_priv->runसमय_pm);

	करो अणु
		u32 iir, gt_iir, pm_iir;
		u32 pipe_stats[I915_MAX_PIPES] = अणुपूर्ण;
		u32 hotplug_status = 0;
		u32 ier = 0;

		gt_iir = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, GTIIR);
		pm_iir = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, GEN6_PMIIR);
		iir = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, VLV_IIR);

		अगर (gt_iir == 0 && pm_iir == 0 && iir == 0)
			अवरोध;

		ret = IRQ_HANDLED;

		/*
		 * Theory on पूर्णांकerrupt generation, based on empirical evidence:
		 *
		 * x = ((VLV_IIR & VLV_IER) ||
		 *      (((GT_IIR & GT_IER) || (GEN6_PMIIR & GEN6_PMIER)) &&
		 *       (VLV_MASTER_IER & MASTER_INTERRUPT_ENABLE)));
		 *
		 * A CPU पूर्णांकerrupt will only be उठाओd when 'x' has a 0->1 edge.
		 * Hence we clear MASTER_INTERRUPT_ENABLE and VLV_IER to
		 * guarantee the CPU पूर्णांकerrupt will be उठाओd again even अगर we
		 * करोn't end up clearing all the VLV_IIR, GT_IIR, GEN6_PMIIR
		 * bits this समय around.
		 */
		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, VLV_MASTER_IER, 0);
		ier = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, VLV_IER);
		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, VLV_IER, 0);

		अगर (gt_iir)
			पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, GTIIR, gt_iir);
		अगर (pm_iir)
			पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, GEN6_PMIIR, pm_iir);

		अगर (iir & I915_DISPLAY_PORT_INTERRUPT)
			hotplug_status = i9xx_hpd_irq_ack(dev_priv);

		/* Call regardless, as some status bits might not be
		 * संकेतled in iir */
		i9xx_pipestat_irq_ack(dev_priv, iir, pipe_stats);

		अगर (iir & (I915_LPE_PIPE_A_INTERRUPT |
			   I915_LPE_PIPE_B_INTERRUPT))
			पूर्णांकel_lpe_audio_irq_handler(dev_priv);

		/*
		 * VLV_IIR is single buffered, and reflects the level
		 * from PIPESTAT/PORT_HOTPLUG_STAT, hence clear it last.
		 */
		अगर (iir)
			पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, VLV_IIR, iir);

		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, VLV_IER, ier);
		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, VLV_MASTER_IER, MASTER_INTERRUPT_ENABLE);

		अगर (gt_iir)
			gen6_gt_irq_handler(&dev_priv->gt, gt_iir);
		अगर (pm_iir)
			gen6_rps_irq_handler(&dev_priv->gt.rps, pm_iir);

		अगर (hotplug_status)
			i9xx_hpd_irq_handler(dev_priv, hotplug_status);

		valleyview_pipestat_irq_handler(dev_priv, pipe_stats);
	पूर्ण जबतक (0);

	pmu_irq_stats(dev_priv, ret);

	enable_rpm_wakeref_निश्चितs(&dev_priv->runसमय_pm);

	वापस ret;
पूर्ण

अटल irqवापस_t cherryview_irq_handler(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा drm_i915_निजी *dev_priv = arg;
	irqवापस_t ret = IRQ_NONE;

	अगर (!पूर्णांकel_irqs_enabled(dev_priv))
		वापस IRQ_NONE;

	/* IRQs are synced during runसमय_suspend, we करोn't require a wakeref */
	disable_rpm_wakeref_निश्चितs(&dev_priv->runसमय_pm);

	करो अणु
		u32 master_ctl, iir;
		u32 pipe_stats[I915_MAX_PIPES] = अणुपूर्ण;
		u32 hotplug_status = 0;
		u32 ier = 0;

		master_ctl = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, GEN8_MASTER_IRQ) & ~GEN8_MASTER_IRQ_CONTROL;
		iir = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, VLV_IIR);

		अगर (master_ctl == 0 && iir == 0)
			अवरोध;

		ret = IRQ_HANDLED;

		/*
		 * Theory on पूर्णांकerrupt generation, based on empirical evidence:
		 *
		 * x = ((VLV_IIR & VLV_IER) ||
		 *      ((GEN8_MASTER_IRQ & ~GEN8_MASTER_IRQ_CONTROL) &&
		 *       (GEN8_MASTER_IRQ & GEN8_MASTER_IRQ_CONTROL)));
		 *
		 * A CPU पूर्णांकerrupt will only be उठाओd when 'x' has a 0->1 edge.
		 * Hence we clear GEN8_MASTER_IRQ_CONTROL and VLV_IER to
		 * guarantee the CPU पूर्णांकerrupt will be उठाओd again even अगर we
		 * करोn't end up clearing all the VLV_IIR and GEN8_MASTER_IRQ_CONTROL
		 * bits this समय around.
		 */
		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, GEN8_MASTER_IRQ, 0);
		ier = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, VLV_IER);
		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, VLV_IER, 0);

		gen8_gt_irq_handler(&dev_priv->gt, master_ctl);

		अगर (iir & I915_DISPLAY_PORT_INTERRUPT)
			hotplug_status = i9xx_hpd_irq_ack(dev_priv);

		/* Call regardless, as some status bits might not be
		 * संकेतled in iir */
		i9xx_pipestat_irq_ack(dev_priv, iir, pipe_stats);

		अगर (iir & (I915_LPE_PIPE_A_INTERRUPT |
			   I915_LPE_PIPE_B_INTERRUPT |
			   I915_LPE_PIPE_C_INTERRUPT))
			पूर्णांकel_lpe_audio_irq_handler(dev_priv);

		/*
		 * VLV_IIR is single buffered, and reflects the level
		 * from PIPESTAT/PORT_HOTPLUG_STAT, hence clear it last.
		 */
		अगर (iir)
			पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, VLV_IIR, iir);

		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, VLV_IER, ier);
		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, GEN8_MASTER_IRQ, GEN8_MASTER_IRQ_CONTROL);

		अगर (hotplug_status)
			i9xx_hpd_irq_handler(dev_priv, hotplug_status);

		valleyview_pipestat_irq_handler(dev_priv, pipe_stats);
	पूर्ण जबतक (0);

	pmu_irq_stats(dev_priv, ret);

	enable_rpm_wakeref_निश्चितs(&dev_priv->runसमय_pm);

	वापस ret;
पूर्ण

अटल व्योम ibx_hpd_irq_handler(काष्ठा drm_i915_निजी *dev_priv,
				u32 hotplug_trigger)
अणु
	u32 dig_hotplug_reg, pin_mask = 0, दीर्घ_mask = 0;

	/*
	 * Somehow the PCH करोesn't seem to really ack the पूर्णांकerrupt to the CPU
	 * unless we touch the hotplug रेजिस्टर, even अगर hotplug_trigger is
	 * zero. Not acking leads to "The master control interrupt lied (SDE)!"
	 * errors.
	 */
	dig_hotplug_reg = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, PCH_PORT_HOTPLUG);
	अगर (!hotplug_trigger) अणु
		u32 mask = PORTA_HOTPLUG_STATUS_MASK |
			PORTD_HOTPLUG_STATUS_MASK |
			PORTC_HOTPLUG_STATUS_MASK |
			PORTB_HOTPLUG_STATUS_MASK;
		dig_hotplug_reg &= ~mask;
	पूर्ण

	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, PCH_PORT_HOTPLUG, dig_hotplug_reg);
	अगर (!hotplug_trigger)
		वापस;

	पूर्णांकel_get_hpd_pins(dev_priv, &pin_mask, &दीर्घ_mask,
			   hotplug_trigger, dig_hotplug_reg,
			   dev_priv->hotplug.pch_hpd,
			   pch_port_hotplug_दीर्घ_detect);

	पूर्णांकel_hpd_irq_handler(dev_priv, pin_mask, दीर्घ_mask);
पूर्ण

अटल व्योम ibx_irq_handler(काष्ठा drm_i915_निजी *dev_priv, u32 pch_iir)
अणु
	क्रमागत pipe pipe;
	u32 hotplug_trigger = pch_iir & SDE_HOTPLUG_MASK;

	ibx_hpd_irq_handler(dev_priv, hotplug_trigger);

	अगर (pch_iir & SDE_AUDIO_POWER_MASK) अणु
		पूर्णांक port = ffs((pch_iir & SDE_AUDIO_POWER_MASK) >>
			       SDE_AUDIO_POWER_SHIFT);
		drm_dbg(&dev_priv->drm, "PCH audio power change on port %d\n",
			port_name(port));
	पूर्ण

	अगर (pch_iir & SDE_AUX_MASK)
		dp_aux_irq_handler(dev_priv);

	अगर (pch_iir & SDE_GMBUS)
		gmbus_irq_handler(dev_priv);

	अगर (pch_iir & SDE_AUDIO_HDCP_MASK)
		drm_dbg(&dev_priv->drm, "PCH HDCP audio interrupt\n");

	अगर (pch_iir & SDE_AUDIO_TRANS_MASK)
		drm_dbg(&dev_priv->drm, "PCH transcoder audio interrupt\n");

	अगर (pch_iir & SDE_POISON)
		drm_err(&dev_priv->drm, "PCH poison interrupt\n");

	अगर (pch_iir & SDE_FDI_MASK) अणु
		क्रम_each_pipe(dev_priv, pipe)
			drm_dbg(&dev_priv->drm, "  pipe %c FDI IIR: 0x%08x\n",
				pipe_name(pipe),
				पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, FDI_RX_IIR(pipe)));
	पूर्ण

	अगर (pch_iir & (SDE_TRANSB_CRC_DONE | SDE_TRANSA_CRC_DONE))
		drm_dbg(&dev_priv->drm, "PCH transcoder CRC done interrupt\n");

	अगर (pch_iir & (SDE_TRANSB_CRC_ERR | SDE_TRANSA_CRC_ERR))
		drm_dbg(&dev_priv->drm,
			"PCH transcoder CRC error interrupt\n");

	अगर (pch_iir & SDE_TRANSA_FIFO_UNDER)
		पूर्णांकel_pch_fअगरo_underrun_irq_handler(dev_priv, PIPE_A);

	अगर (pch_iir & SDE_TRANSB_FIFO_UNDER)
		पूर्णांकel_pch_fअगरo_underrun_irq_handler(dev_priv, PIPE_B);
पूर्ण

अटल व्योम ivb_err_पूर्णांक_handler(काष्ठा drm_i915_निजी *dev_priv)
अणु
	u32 err_पूर्णांक = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, GEN7_ERR_INT);
	क्रमागत pipe pipe;

	अगर (err_पूर्णांक & ERR_INT_POISON)
		drm_err(&dev_priv->drm, "Poison interrupt\n");

	क्रम_each_pipe(dev_priv, pipe) अणु
		अगर (err_पूर्णांक & ERR_INT_FIFO_UNDERRUN(pipe))
			पूर्णांकel_cpu_fअगरo_underrun_irq_handler(dev_priv, pipe);

		अगर (err_पूर्णांक & ERR_INT_PIPE_CRC_DONE(pipe)) अणु
			अगर (IS_IVYBRIDGE(dev_priv))
				ivb_pipe_crc_irq_handler(dev_priv, pipe);
			अन्यथा
				hsw_pipe_crc_irq_handler(dev_priv, pipe);
		पूर्ण
	पूर्ण

	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, GEN7_ERR_INT, err_पूर्णांक);
पूर्ण

अटल व्योम cpt_serr_पूर्णांक_handler(काष्ठा drm_i915_निजी *dev_priv)
अणु
	u32 serr_पूर्णांक = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, SERR_INT);
	क्रमागत pipe pipe;

	अगर (serr_पूर्णांक & SERR_INT_POISON)
		drm_err(&dev_priv->drm, "PCH poison interrupt\n");

	क्रम_each_pipe(dev_priv, pipe)
		अगर (serr_पूर्णांक & SERR_INT_TRANS_FIFO_UNDERRUN(pipe))
			पूर्णांकel_pch_fअगरo_underrun_irq_handler(dev_priv, pipe);

	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, SERR_INT, serr_पूर्णांक);
पूर्ण

अटल व्योम cpt_irq_handler(काष्ठा drm_i915_निजी *dev_priv, u32 pch_iir)
अणु
	क्रमागत pipe pipe;
	u32 hotplug_trigger = pch_iir & SDE_HOTPLUG_MASK_CPT;

	ibx_hpd_irq_handler(dev_priv, hotplug_trigger);

	अगर (pch_iir & SDE_AUDIO_POWER_MASK_CPT) अणु
		पूर्णांक port = ffs((pch_iir & SDE_AUDIO_POWER_MASK_CPT) >>
			       SDE_AUDIO_POWER_SHIFT_CPT);
		drm_dbg(&dev_priv->drm, "PCH audio power change on port %c\n",
			port_name(port));
	पूर्ण

	अगर (pch_iir & SDE_AUX_MASK_CPT)
		dp_aux_irq_handler(dev_priv);

	अगर (pch_iir & SDE_GMBUS_CPT)
		gmbus_irq_handler(dev_priv);

	अगर (pch_iir & SDE_AUDIO_CP_REQ_CPT)
		drm_dbg(&dev_priv->drm, "Audio CP request interrupt\n");

	अगर (pch_iir & SDE_AUDIO_CP_CHG_CPT)
		drm_dbg(&dev_priv->drm, "Audio CP change interrupt\n");

	अगर (pch_iir & SDE_FDI_MASK_CPT) अणु
		क्रम_each_pipe(dev_priv, pipe)
			drm_dbg(&dev_priv->drm, "  pipe %c FDI IIR: 0x%08x\n",
				pipe_name(pipe),
				पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, FDI_RX_IIR(pipe)));
	पूर्ण

	अगर (pch_iir & SDE_ERROR_CPT)
		cpt_serr_पूर्णांक_handler(dev_priv);
पूर्ण

अटल व्योम icp_irq_handler(काष्ठा drm_i915_निजी *dev_priv, u32 pch_iir)
अणु
	u32 ddi_hotplug_trigger = pch_iir & SDE_DDI_HOTPLUG_MASK_ICP;
	u32 tc_hotplug_trigger = pch_iir & SDE_TC_HOTPLUG_MASK_ICP;
	u32 pin_mask = 0, दीर्घ_mask = 0;

	अगर (ddi_hotplug_trigger) अणु
		u32 dig_hotplug_reg;

		dig_hotplug_reg = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, SHOTPLUG_CTL_DDI);
		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, SHOTPLUG_CTL_DDI, dig_hotplug_reg);

		पूर्णांकel_get_hpd_pins(dev_priv, &pin_mask, &दीर्घ_mask,
				   ddi_hotplug_trigger, dig_hotplug_reg,
				   dev_priv->hotplug.pch_hpd,
				   icp_ddi_port_hotplug_दीर्घ_detect);
	पूर्ण

	अगर (tc_hotplug_trigger) अणु
		u32 dig_hotplug_reg;

		dig_hotplug_reg = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, SHOTPLUG_CTL_TC);
		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, SHOTPLUG_CTL_TC, dig_hotplug_reg);

		पूर्णांकel_get_hpd_pins(dev_priv, &pin_mask, &दीर्घ_mask,
				   tc_hotplug_trigger, dig_hotplug_reg,
				   dev_priv->hotplug.pch_hpd,
				   icp_tc_port_hotplug_दीर्घ_detect);
	पूर्ण

	अगर (pin_mask)
		पूर्णांकel_hpd_irq_handler(dev_priv, pin_mask, दीर्घ_mask);

	अगर (pch_iir & SDE_GMBUS_ICP)
		gmbus_irq_handler(dev_priv);
पूर्ण

अटल व्योम spt_irq_handler(काष्ठा drm_i915_निजी *dev_priv, u32 pch_iir)
अणु
	u32 hotplug_trigger = pch_iir & SDE_HOTPLUG_MASK_SPT &
		~SDE_PORTE_HOTPLUG_SPT;
	u32 hotplug2_trigger = pch_iir & SDE_PORTE_HOTPLUG_SPT;
	u32 pin_mask = 0, दीर्घ_mask = 0;

	अगर (hotplug_trigger) अणु
		u32 dig_hotplug_reg;

		dig_hotplug_reg = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, PCH_PORT_HOTPLUG);
		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, PCH_PORT_HOTPLUG, dig_hotplug_reg);

		पूर्णांकel_get_hpd_pins(dev_priv, &pin_mask, &दीर्घ_mask,
				   hotplug_trigger, dig_hotplug_reg,
				   dev_priv->hotplug.pch_hpd,
				   spt_port_hotplug_दीर्घ_detect);
	पूर्ण

	अगर (hotplug2_trigger) अणु
		u32 dig_hotplug_reg;

		dig_hotplug_reg = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, PCH_PORT_HOTPLUG2);
		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, PCH_PORT_HOTPLUG2, dig_hotplug_reg);

		पूर्णांकel_get_hpd_pins(dev_priv, &pin_mask, &दीर्घ_mask,
				   hotplug2_trigger, dig_hotplug_reg,
				   dev_priv->hotplug.pch_hpd,
				   spt_port_hotplug2_दीर्घ_detect);
	पूर्ण

	अगर (pin_mask)
		पूर्णांकel_hpd_irq_handler(dev_priv, pin_mask, दीर्घ_mask);

	अगर (pch_iir & SDE_GMBUS_CPT)
		gmbus_irq_handler(dev_priv);
पूर्ण

अटल व्योम ilk_hpd_irq_handler(काष्ठा drm_i915_निजी *dev_priv,
				u32 hotplug_trigger)
अणु
	u32 dig_hotplug_reg, pin_mask = 0, दीर्घ_mask = 0;

	dig_hotplug_reg = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, DIGITAL_PORT_HOTPLUG_CNTRL);
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, DIGITAL_PORT_HOTPLUG_CNTRL, dig_hotplug_reg);

	पूर्णांकel_get_hpd_pins(dev_priv, &pin_mask, &दीर्घ_mask,
			   hotplug_trigger, dig_hotplug_reg,
			   dev_priv->hotplug.hpd,
			   ilk_port_hotplug_दीर्घ_detect);

	पूर्णांकel_hpd_irq_handler(dev_priv, pin_mask, दीर्घ_mask);
पूर्ण

अटल व्योम ilk_display_irq_handler(काष्ठा drm_i915_निजी *dev_priv,
				    u32 de_iir)
अणु
	क्रमागत pipe pipe;
	u32 hotplug_trigger = de_iir & DE_DP_A_HOTPLUG;

	अगर (hotplug_trigger)
		ilk_hpd_irq_handler(dev_priv, hotplug_trigger);

	अगर (de_iir & DE_AUX_CHANNEL_A)
		dp_aux_irq_handler(dev_priv);

	अगर (de_iir & DE_GSE)
		पूर्णांकel_opregion_asle_पूर्णांकr(dev_priv);

	अगर (de_iir & DE_POISON)
		drm_err(&dev_priv->drm, "Poison interrupt\n");

	क्रम_each_pipe(dev_priv, pipe) अणु
		अगर (de_iir & DE_PIPE_VBLANK(pipe))
			पूर्णांकel_handle_vblank(dev_priv, pipe);

		अगर (de_iir & DE_PLANE_FLIP_DONE(pipe))
			flip_करोne_handler(dev_priv, pipe);

		अगर (de_iir & DE_PIPE_FIFO_UNDERRUN(pipe))
			पूर्णांकel_cpu_fअगरo_underrun_irq_handler(dev_priv, pipe);

		अगर (de_iir & DE_PIPE_CRC_DONE(pipe))
			i9xx_pipe_crc_irq_handler(dev_priv, pipe);
	पूर्ण

	/* check event from PCH */
	अगर (de_iir & DE_PCH_EVENT) अणु
		u32 pch_iir = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, SDEIIR);

		अगर (HAS_PCH_CPT(dev_priv))
			cpt_irq_handler(dev_priv, pch_iir);
		अन्यथा
			ibx_irq_handler(dev_priv, pch_iir);

		/* should clear PCH hotplug event beक्रमe clear CPU irq */
		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, SDEIIR, pch_iir);
	पूर्ण

	अगर (IS_DISPLAY_VER(dev_priv, 5) && de_iir & DE_PCU_EVENT)
		gen5_rps_irq_handler(&dev_priv->gt.rps);
पूर्ण

अटल व्योम ivb_display_irq_handler(काष्ठा drm_i915_निजी *dev_priv,
				    u32 de_iir)
अणु
	क्रमागत pipe pipe;
	u32 hotplug_trigger = de_iir & DE_DP_A_HOTPLUG_IVB;

	अगर (hotplug_trigger)
		ilk_hpd_irq_handler(dev_priv, hotplug_trigger);

	अगर (de_iir & DE_ERR_INT_IVB)
		ivb_err_पूर्णांक_handler(dev_priv);

	अगर (de_iir & DE_EDP_PSR_INT_HSW) अणु
		काष्ठा पूर्णांकel_encoder *encoder;

		क्रम_each_पूर्णांकel_encoder_with_psr(&dev_priv->drm, encoder) अणु
			काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = enc_to_पूर्णांकel_dp(encoder);

			u32 psr_iir = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore,
							EDP_PSR_IIR);

			पूर्णांकel_psr_irq_handler(पूर्णांकel_dp, psr_iir);
			पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore,
					   EDP_PSR_IIR, psr_iir);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (de_iir & DE_AUX_CHANNEL_A_IVB)
		dp_aux_irq_handler(dev_priv);

	अगर (de_iir & DE_GSE_IVB)
		पूर्णांकel_opregion_asle_पूर्णांकr(dev_priv);

	क्रम_each_pipe(dev_priv, pipe) अणु
		अगर (de_iir & DE_PIPE_VBLANK_IVB(pipe))
			पूर्णांकel_handle_vblank(dev_priv, pipe);

		अगर (de_iir & DE_PLANE_FLIP_DONE_IVB(pipe))
			flip_करोne_handler(dev_priv, pipe);
	पूर्ण

	/* check event from PCH */
	अगर (!HAS_PCH_NOP(dev_priv) && (de_iir & DE_PCH_EVENT_IVB)) अणु
		u32 pch_iir = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, SDEIIR);

		cpt_irq_handler(dev_priv, pch_iir);

		/* clear PCH hotplug event beक्रमe clear CPU irq */
		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, SDEIIR, pch_iir);
	पूर्ण
पूर्ण

/*
 * To handle irqs with the minimum potential races with fresh पूर्णांकerrupts, we:
 * 1 - Disable Master Interrupt Control.
 * 2 - Find the source(s) of the पूर्णांकerrupt.
 * 3 - Clear the Interrupt Identity bits (IIR).
 * 4 - Process the पूर्णांकerrupt(s) that had bits set in the IIRs.
 * 5 - Re-enable Master Interrupt Control.
 */
अटल irqवापस_t ilk_irq_handler(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा drm_i915_निजी *i915 = arg;
	व्योम __iomem * स्थिर regs = i915->uncore.regs;
	u32 de_iir, gt_iir, de_ier, sde_ier = 0;
	irqवापस_t ret = IRQ_NONE;

	अगर (unlikely(!पूर्णांकel_irqs_enabled(i915)))
		वापस IRQ_NONE;

	/* IRQs are synced during runसमय_suspend, we करोn't require a wakeref */
	disable_rpm_wakeref_निश्चितs(&i915->runसमय_pm);

	/* disable master पूर्णांकerrupt beक्रमe clearing iir  */
	de_ier = raw_reg_पढ़ो(regs, DEIER);
	raw_reg_ग_लिखो(regs, DEIER, de_ier & ~DE_MASTER_IRQ_CONTROL);

	/* Disable south पूर्णांकerrupts. We'll only ग_लिखो to SDEIIR once, so further
	 * पूर्णांकerrupts will will be stored on its back queue, and then we'll be
	 * able to process them after we restore SDEIER (as soon as we restore
	 * it, we'll get an पूर्णांकerrupt अगर SDEIIR still has something to process
	 * due to its back queue). */
	अगर (!HAS_PCH_NOP(i915)) अणु
		sde_ier = raw_reg_पढ़ो(regs, SDEIER);
		raw_reg_ग_लिखो(regs, SDEIER, 0);
	पूर्ण

	/* Find, clear, then process each source of पूर्णांकerrupt */

	gt_iir = raw_reg_पढ़ो(regs, GTIIR);
	अगर (gt_iir) अणु
		raw_reg_ग_लिखो(regs, GTIIR, gt_iir);
		अगर (INTEL_GEN(i915) >= 6)
			gen6_gt_irq_handler(&i915->gt, gt_iir);
		अन्यथा
			gen5_gt_irq_handler(&i915->gt, gt_iir);
		ret = IRQ_HANDLED;
	पूर्ण

	de_iir = raw_reg_पढ़ो(regs, DEIIR);
	अगर (de_iir) अणु
		raw_reg_ग_लिखो(regs, DEIIR, de_iir);
		अगर (DISPLAY_VER(i915) >= 7)
			ivb_display_irq_handler(i915, de_iir);
		अन्यथा
			ilk_display_irq_handler(i915, de_iir);
		ret = IRQ_HANDLED;
	पूर्ण

	अगर (INTEL_GEN(i915) >= 6) अणु
		u32 pm_iir = raw_reg_पढ़ो(regs, GEN6_PMIIR);
		अगर (pm_iir) अणु
			raw_reg_ग_लिखो(regs, GEN6_PMIIR, pm_iir);
			gen6_rps_irq_handler(&i915->gt.rps, pm_iir);
			ret = IRQ_HANDLED;
		पूर्ण
	पूर्ण

	raw_reg_ग_लिखो(regs, DEIER, de_ier);
	अगर (sde_ier)
		raw_reg_ग_लिखो(regs, SDEIER, sde_ier);

	pmu_irq_stats(i915, ret);

	/* IRQs are synced during runसमय_suspend, we करोn't require a wakeref */
	enable_rpm_wakeref_निश्चितs(&i915->runसमय_pm);

	वापस ret;
पूर्ण

अटल व्योम bxt_hpd_irq_handler(काष्ठा drm_i915_निजी *dev_priv,
				u32 hotplug_trigger)
अणु
	u32 dig_hotplug_reg, pin_mask = 0, दीर्घ_mask = 0;

	dig_hotplug_reg = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, PCH_PORT_HOTPLUG);
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, PCH_PORT_HOTPLUG, dig_hotplug_reg);

	पूर्णांकel_get_hpd_pins(dev_priv, &pin_mask, &दीर्घ_mask,
			   hotplug_trigger, dig_hotplug_reg,
			   dev_priv->hotplug.hpd,
			   bxt_port_hotplug_दीर्घ_detect);

	पूर्णांकel_hpd_irq_handler(dev_priv, pin_mask, दीर्घ_mask);
पूर्ण

अटल व्योम gen11_hpd_irq_handler(काष्ठा drm_i915_निजी *dev_priv, u32 iir)
अणु
	u32 pin_mask = 0, दीर्घ_mask = 0;
	u32 trigger_tc = iir & GEN11_DE_TC_HOTPLUG_MASK;
	u32 trigger_tbt = iir & GEN11_DE_TBT_HOTPLUG_MASK;

	अगर (trigger_tc) अणु
		u32 dig_hotplug_reg;

		dig_hotplug_reg = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, GEN11_TC_HOTPLUG_CTL);
		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, GEN11_TC_HOTPLUG_CTL, dig_hotplug_reg);

		पूर्णांकel_get_hpd_pins(dev_priv, &pin_mask, &दीर्घ_mask,
				   trigger_tc, dig_hotplug_reg,
				   dev_priv->hotplug.hpd,
				   gen11_port_hotplug_दीर्घ_detect);
	पूर्ण

	अगर (trigger_tbt) अणु
		u32 dig_hotplug_reg;

		dig_hotplug_reg = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, GEN11_TBT_HOTPLUG_CTL);
		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, GEN11_TBT_HOTPLUG_CTL, dig_hotplug_reg);

		पूर्णांकel_get_hpd_pins(dev_priv, &pin_mask, &दीर्घ_mask,
				   trigger_tbt, dig_hotplug_reg,
				   dev_priv->hotplug.hpd,
				   gen11_port_hotplug_दीर्घ_detect);
	पूर्ण

	अगर (pin_mask)
		पूर्णांकel_hpd_irq_handler(dev_priv, pin_mask, दीर्घ_mask);
	अन्यथा
		drm_err(&dev_priv->drm,
			"Unexpected DE HPD interrupt 0x%08x\n", iir);
पूर्ण

अटल u32 gen8_de_port_aux_mask(काष्ठा drm_i915_निजी *dev_priv)
अणु
	u32 mask;

	अगर (DISPLAY_VER(dev_priv) >= 12)
		वापस TGL_DE_PORT_AUX_DDIA |
			TGL_DE_PORT_AUX_DDIB |
			TGL_DE_PORT_AUX_DDIC |
			TGL_DE_PORT_AUX_USBC1 |
			TGL_DE_PORT_AUX_USBC2 |
			TGL_DE_PORT_AUX_USBC3 |
			TGL_DE_PORT_AUX_USBC4 |
			TGL_DE_PORT_AUX_USBC5 |
			TGL_DE_PORT_AUX_USBC6;


	mask = GEN8_AUX_CHANNEL_A;
	अगर (DISPLAY_VER(dev_priv) >= 9)
		mask |= GEN9_AUX_CHANNEL_B |
			GEN9_AUX_CHANNEL_C |
			GEN9_AUX_CHANNEL_D;

	अगर (IS_CNL_WITH_PORT_F(dev_priv) || IS_DISPLAY_VER(dev_priv, 11))
		mask |= CNL_AUX_CHANNEL_F;

	अगर (IS_DISPLAY_VER(dev_priv, 11))
		mask |= ICL_AUX_CHANNEL_E;

	वापस mask;
पूर्ण

अटल u32 gen8_de_pipe_fault_mask(काष्ठा drm_i915_निजी *dev_priv)
अणु
	अगर (HAS_D12_PLANE_MINIMIZATION(dev_priv))
		वापस RKL_DE_PIPE_IRQ_FAULT_ERRORS;
	अन्यथा अगर (DISPLAY_VER(dev_priv) >= 11)
		वापस GEN11_DE_PIPE_IRQ_FAULT_ERRORS;
	अन्यथा अगर (DISPLAY_VER(dev_priv) >= 9)
		वापस GEN9_DE_PIPE_IRQ_FAULT_ERRORS;
	अन्यथा
		वापस GEN8_DE_PIPE_IRQ_FAULT_ERRORS;
पूर्ण

अटल व्योम
gen8_de_misc_irq_handler(काष्ठा drm_i915_निजी *dev_priv, u32 iir)
अणु
	bool found = false;

	अगर (iir & GEN8_DE_MISC_GSE) अणु
		पूर्णांकel_opregion_asle_पूर्णांकr(dev_priv);
		found = true;
	पूर्ण

	अगर (iir & GEN8_DE_EDP_PSR) अणु
		काष्ठा पूर्णांकel_encoder *encoder;
		u32 psr_iir;
		i915_reg_t iir_reg;

		क्रम_each_पूर्णांकel_encoder_with_psr(&dev_priv->drm, encoder) अणु
			काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = enc_to_पूर्णांकel_dp(encoder);

			अगर (DISPLAY_VER(dev_priv) >= 12)
				iir_reg = TRANS_PSR_IIR(पूर्णांकel_dp->psr.transcoder);
			अन्यथा
				iir_reg = EDP_PSR_IIR;

			psr_iir = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, iir_reg);
			पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, iir_reg, psr_iir);

			अगर (psr_iir)
				found = true;

			पूर्णांकel_psr_irq_handler(पूर्णांकel_dp, psr_iir);

			/* prior GEN12 only have one EDP PSR */
			अगर (DISPLAY_VER(dev_priv) < 12)
				अवरोध;
		पूर्ण
	पूर्ण

	अगर (!found)
		drm_err(&dev_priv->drm, "Unexpected DE Misc interrupt\n");
पूर्ण

अटल व्योम gen11_dsi_te_पूर्णांकerrupt_handler(काष्ठा drm_i915_निजी *dev_priv,
					   u32 te_trigger)
अणु
	क्रमागत pipe pipe = INVALID_PIPE;
	क्रमागत transcoder dsi_trans;
	क्रमागत port port;
	u32 val, पंचांगp;

	/*
	 * Inहाल of dual link, TE comes from DSI_1
	 * this is to check अगर dual link is enabled
	 */
	val = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, TRANS_DDI_FUNC_CTL2(TRANSCODER_DSI_0));
	val &= PORT_SYNC_MODE_ENABLE;

	/*
	 * अगर dual link is enabled, then पढ़ो DSI_0
	 * transcoder रेजिस्टरs
	 */
	port = ((te_trigger & DSI1_TE && val) || (te_trigger & DSI0_TE)) ?
						  PORT_A : PORT_B;
	dsi_trans = (port == PORT_A) ? TRANSCODER_DSI_0 : TRANSCODER_DSI_1;

	/* Check अगर DSI configured in command mode */
	val = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, DSI_TRANS_FUNC_CONF(dsi_trans));
	val = val & OP_MODE_MASK;

	अगर (val != CMD_MODE_NO_GATE && val != CMD_MODE_TE_GATE) अणु
		drm_err(&dev_priv->drm, "DSI trancoder not configured in command mode\n");
		वापस;
	पूर्ण

	/* Get PIPE क्रम handling VBLANK event */
	val = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, TRANS_DDI_FUNC_CTL(dsi_trans));
	चयन (val & TRANS_DDI_EDP_INPUT_MASK) अणु
	हाल TRANS_DDI_EDP_INPUT_A_ON:
		pipe = PIPE_A;
		अवरोध;
	हाल TRANS_DDI_EDP_INPUT_B_ONOFF:
		pipe = PIPE_B;
		अवरोध;
	हाल TRANS_DDI_EDP_INPUT_C_ONOFF:
		pipe = PIPE_C;
		अवरोध;
	शेष:
		drm_err(&dev_priv->drm, "Invalid PIPE\n");
		वापस;
	पूर्ण

	पूर्णांकel_handle_vblank(dev_priv, pipe);

	/* clear TE in dsi IIR */
	port = (te_trigger & DSI1_TE) ? PORT_B : PORT_A;
	पंचांगp = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, DSI_INTR_IDENT_REG(port));
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, DSI_INTR_IDENT_REG(port), पंचांगp);
पूर्ण

अटल u32 gen8_de_pipe_flip_करोne_mask(काष्ठा drm_i915_निजी *i915)
अणु
	अगर (DISPLAY_VER(i915) >= 9)
		वापस GEN9_PIPE_PLANE1_FLIP_DONE;
	अन्यथा
		वापस GEN8_PIPE_PRIMARY_FLIP_DONE;
पूर्ण

अटल irqवापस_t
gen8_de_irq_handler(काष्ठा drm_i915_निजी *dev_priv, u32 master_ctl)
अणु
	irqवापस_t ret = IRQ_NONE;
	u32 iir;
	क्रमागत pipe pipe;

	अगर (master_ctl & GEN8_DE_MISC_IRQ) अणु
		iir = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, GEN8_DE_MISC_IIR);
		अगर (iir) अणु
			पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, GEN8_DE_MISC_IIR, iir);
			ret = IRQ_HANDLED;
			gen8_de_misc_irq_handler(dev_priv, iir);
		पूर्ण अन्यथा अणु
			drm_err(&dev_priv->drm,
				"The master control interrupt lied (DE MISC)!\n");
		पूर्ण
	पूर्ण

	अगर (DISPLAY_VER(dev_priv) >= 11 && (master_ctl & GEN11_DE_HPD_IRQ)) अणु
		iir = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, GEN11_DE_HPD_IIR);
		अगर (iir) अणु
			पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, GEN11_DE_HPD_IIR, iir);
			ret = IRQ_HANDLED;
			gen11_hpd_irq_handler(dev_priv, iir);
		पूर्ण अन्यथा अणु
			drm_err(&dev_priv->drm,
				"The master control interrupt lied, (DE HPD)!\n");
		पूर्ण
	पूर्ण

	अगर (master_ctl & GEN8_DE_PORT_IRQ) अणु
		iir = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, GEN8_DE_PORT_IIR);
		अगर (iir) अणु
			bool found = false;

			पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, GEN8_DE_PORT_IIR, iir);
			ret = IRQ_HANDLED;

			अगर (iir & gen8_de_port_aux_mask(dev_priv)) अणु
				dp_aux_irq_handler(dev_priv);
				found = true;
			पूर्ण

			अगर (IS_GEN9_LP(dev_priv)) अणु
				u32 hotplug_trigger = iir & BXT_DE_PORT_HOTPLUG_MASK;

				अगर (hotplug_trigger) अणु
					bxt_hpd_irq_handler(dev_priv, hotplug_trigger);
					found = true;
				पूर्ण
			पूर्ण अन्यथा अगर (IS_BROADWELL(dev_priv)) अणु
				u32 hotplug_trigger = iir & BDW_DE_PORT_HOTPLUG_MASK;

				अगर (hotplug_trigger) अणु
					ilk_hpd_irq_handler(dev_priv, hotplug_trigger);
					found = true;
				पूर्ण
			पूर्ण

			अगर (IS_GEN9_LP(dev_priv) && (iir & BXT_DE_PORT_GMBUS)) अणु
				gmbus_irq_handler(dev_priv);
				found = true;
			पूर्ण

			अगर (DISPLAY_VER(dev_priv) >= 11) अणु
				u32 te_trigger = iir & (DSI0_TE | DSI1_TE);

				अगर (te_trigger) अणु
					gen11_dsi_te_पूर्णांकerrupt_handler(dev_priv, te_trigger);
					found = true;
				पूर्ण
			पूर्ण

			अगर (!found)
				drm_err(&dev_priv->drm,
					"Unexpected DE Port interrupt\n");
		पूर्ण
		अन्यथा
			drm_err(&dev_priv->drm,
				"The master control interrupt lied (DE PORT)!\n");
	पूर्ण

	क्रम_each_pipe(dev_priv, pipe) अणु
		u32 fault_errors;

		अगर (!(master_ctl & GEN8_DE_PIPE_IRQ(pipe)))
			जारी;

		iir = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, GEN8_DE_PIPE_IIR(pipe));
		अगर (!iir) अणु
			drm_err(&dev_priv->drm,
				"The master control interrupt lied (DE PIPE)!\n");
			जारी;
		पूर्ण

		ret = IRQ_HANDLED;
		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, GEN8_DE_PIPE_IIR(pipe), iir);

		अगर (iir & GEN8_PIPE_VBLANK)
			पूर्णांकel_handle_vblank(dev_priv, pipe);

		अगर (iir & gen8_de_pipe_flip_करोne_mask(dev_priv))
			flip_करोne_handler(dev_priv, pipe);

		अगर (iir & GEN8_PIPE_CDCLK_CRC_DONE)
			hsw_pipe_crc_irq_handler(dev_priv, pipe);

		अगर (iir & GEN8_PIPE_FIFO_UNDERRUN)
			पूर्णांकel_cpu_fअगरo_underrun_irq_handler(dev_priv, pipe);

		fault_errors = iir & gen8_de_pipe_fault_mask(dev_priv);
		अगर (fault_errors)
			drm_err(&dev_priv->drm,
				"Fault errors on pipe %c: 0x%08x\n",
				pipe_name(pipe),
				fault_errors);
	पूर्ण

	अगर (HAS_PCH_SPLIT(dev_priv) && !HAS_PCH_NOP(dev_priv) &&
	    master_ctl & GEN8_DE_PCH_IRQ) अणु
		/*
		 * FIXME(BDW): Assume क्रम now that the new पूर्णांकerrupt handling
		 * scheme also बंदd the SDE पूर्णांकerrupt handling race we've seen
		 * on older pch-split platक्रमms. But this needs testing.
		 */
		iir = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, SDEIIR);
		अगर (iir) अणु
			पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, SDEIIR, iir);
			ret = IRQ_HANDLED;

			अगर (INTEL_PCH_TYPE(dev_priv) >= PCH_ICP)
				icp_irq_handler(dev_priv, iir);
			अन्यथा अगर (INTEL_PCH_TYPE(dev_priv) >= PCH_SPT)
				spt_irq_handler(dev_priv, iir);
			अन्यथा
				cpt_irq_handler(dev_priv, iir);
		पूर्ण अन्यथा अणु
			/*
			 * Like on previous PCH there seems to be something
			 * fishy going on with क्रमwarding PCH पूर्णांकerrupts.
			 */
			drm_dbg(&dev_priv->drm,
				"The master control interrupt lied (SDE)!\n");
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल अंतरभूत u32 gen8_master_पूर्णांकr_disable(व्योम __iomem * स्थिर regs)
अणु
	raw_reg_ग_लिखो(regs, GEN8_MASTER_IRQ, 0);

	/*
	 * Now with master disabled, get a sample of level indications
	 * क्रम this पूर्णांकerrupt. Indications will be cleared on related acks.
	 * New indications can and will light up during processing,
	 * and will generate new पूर्णांकerrupt after enabling master.
	 */
	वापस raw_reg_पढ़ो(regs, GEN8_MASTER_IRQ);
पूर्ण

अटल अंतरभूत व्योम gen8_master_पूर्णांकr_enable(व्योम __iomem * स्थिर regs)
अणु
	raw_reg_ग_लिखो(regs, GEN8_MASTER_IRQ, GEN8_MASTER_IRQ_CONTROL);
पूर्ण

अटल irqवापस_t gen8_irq_handler(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा drm_i915_निजी *dev_priv = arg;
	व्योम __iomem * स्थिर regs = dev_priv->uncore.regs;
	u32 master_ctl;

	अगर (!पूर्णांकel_irqs_enabled(dev_priv))
		वापस IRQ_NONE;

	master_ctl = gen8_master_पूर्णांकr_disable(regs);
	अगर (!master_ctl) अणु
		gen8_master_पूर्णांकr_enable(regs);
		वापस IRQ_NONE;
	पूर्ण

	/* Find, queue (onto bottom-halves), then clear each source */
	gen8_gt_irq_handler(&dev_priv->gt, master_ctl);

	/* IRQs are synced during runसमय_suspend, we करोn't require a wakeref */
	अगर (master_ctl & ~GEN8_GT_IRQS) अणु
		disable_rpm_wakeref_निश्चितs(&dev_priv->runसमय_pm);
		gen8_de_irq_handler(dev_priv, master_ctl);
		enable_rpm_wakeref_निश्चितs(&dev_priv->runसमय_pm);
	पूर्ण

	gen8_master_पूर्णांकr_enable(regs);

	pmu_irq_stats(dev_priv, IRQ_HANDLED);

	वापस IRQ_HANDLED;
पूर्ण

अटल u32
gen11_gu_misc_irq_ack(काष्ठा पूर्णांकel_gt *gt, स्थिर u32 master_ctl)
अणु
	व्योम __iomem * स्थिर regs = gt->uncore->regs;
	u32 iir;

	अगर (!(master_ctl & GEN11_GU_MISC_IRQ))
		वापस 0;

	iir = raw_reg_पढ़ो(regs, GEN11_GU_MISC_IIR);
	अगर (likely(iir))
		raw_reg_ग_लिखो(regs, GEN11_GU_MISC_IIR, iir);

	वापस iir;
पूर्ण

अटल व्योम
gen11_gu_misc_irq_handler(काष्ठा पूर्णांकel_gt *gt, स्थिर u32 iir)
अणु
	अगर (iir & GEN11_GU_MISC_GSE)
		पूर्णांकel_opregion_asle_पूर्णांकr(gt->i915);
पूर्ण

अटल अंतरभूत u32 gen11_master_पूर्णांकr_disable(व्योम __iomem * स्थिर regs)
अणु
	raw_reg_ग_लिखो(regs, GEN11_GFX_MSTR_IRQ, 0);

	/*
	 * Now with master disabled, get a sample of level indications
	 * क्रम this पूर्णांकerrupt. Indications will be cleared on related acks.
	 * New indications can and will light up during processing,
	 * and will generate new पूर्णांकerrupt after enabling master.
	 */
	वापस raw_reg_पढ़ो(regs, GEN11_GFX_MSTR_IRQ);
पूर्ण

अटल अंतरभूत व्योम gen11_master_पूर्णांकr_enable(व्योम __iomem * स्थिर regs)
अणु
	raw_reg_ग_लिखो(regs, GEN11_GFX_MSTR_IRQ, GEN11_MASTER_IRQ);
पूर्ण

अटल व्योम
gen11_display_irq_handler(काष्ठा drm_i915_निजी *i915)
अणु
	व्योम __iomem * स्थिर regs = i915->uncore.regs;
	स्थिर u32 disp_ctl = raw_reg_पढ़ो(regs, GEN11_DISPLAY_INT_CTL);

	disable_rpm_wakeref_निश्चितs(&i915->runसमय_pm);
	/*
	 * GEN11_DISPLAY_INT_CTL has same क्रमmat as GEN8_MASTER_IRQ
	 * क्रम the display related bits.
	 */
	raw_reg_ग_लिखो(regs, GEN11_DISPLAY_INT_CTL, 0x0);
	gen8_de_irq_handler(i915, disp_ctl);
	raw_reg_ग_लिखो(regs, GEN11_DISPLAY_INT_CTL,
		      GEN11_DISPLAY_IRQ_ENABLE);

	enable_rpm_wakeref_निश्चितs(&i915->runसमय_pm);
पूर्ण

अटल __always_अंतरभूत irqवापस_t
__gen11_irq_handler(काष्ठा drm_i915_निजी * स्थिर i915,
		    u32 (*पूर्णांकr_disable)(व्योम __iomem * स्थिर regs),
		    व्योम (*पूर्णांकr_enable)(व्योम __iomem * स्थिर regs))
अणु
	व्योम __iomem * स्थिर regs = i915->uncore.regs;
	काष्ठा पूर्णांकel_gt *gt = &i915->gt;
	u32 master_ctl;
	u32 gu_misc_iir;

	अगर (!पूर्णांकel_irqs_enabled(i915))
		वापस IRQ_NONE;

	master_ctl = पूर्णांकr_disable(regs);
	अगर (!master_ctl) अणु
		पूर्णांकr_enable(regs);
		वापस IRQ_NONE;
	पूर्ण

	/* Find, queue (onto bottom-halves), then clear each source */
	gen11_gt_irq_handler(gt, master_ctl);

	/* IRQs are synced during runसमय_suspend, we करोn't require a wakeref */
	अगर (master_ctl & GEN11_DISPLAY_IRQ)
		gen11_display_irq_handler(i915);

	gu_misc_iir = gen11_gu_misc_irq_ack(gt, master_ctl);

	पूर्णांकr_enable(regs);

	gen11_gu_misc_irq_handler(gt, gu_misc_iir);

	pmu_irq_stats(i915, IRQ_HANDLED);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t gen11_irq_handler(पूर्णांक irq, व्योम *arg)
अणु
	वापस __gen11_irq_handler(arg,
				   gen11_master_पूर्णांकr_disable,
				   gen11_master_पूर्णांकr_enable);
पूर्ण

अटल u32 dg1_master_पूर्णांकr_disable_and_ack(व्योम __iomem * स्थिर regs)
अणु
	u32 val;

	/* First disable पूर्णांकerrupts */
	raw_reg_ग_लिखो(regs, DG1_MSTR_UNIT_INTR, 0);

	/* Get the indication levels and ack the master unit */
	val = raw_reg_पढ़ो(regs, DG1_MSTR_UNIT_INTR);
	अगर (unlikely(!val))
		वापस 0;

	raw_reg_ग_लिखो(regs, DG1_MSTR_UNIT_INTR, val);

	/*
	 * Now with master disabled, get a sample of level indications
	 * क्रम this पूर्णांकerrupt and ack them right away - we keep GEN11_MASTER_IRQ
	 * out as this bit करोesn't exist anymore क्रम DG1
	 */
	val = raw_reg_पढ़ो(regs, GEN11_GFX_MSTR_IRQ) & ~GEN11_MASTER_IRQ;
	अगर (unlikely(!val))
		वापस 0;

	raw_reg_ग_लिखो(regs, GEN11_GFX_MSTR_IRQ, val);

	वापस val;
पूर्ण

अटल अंतरभूत व्योम dg1_master_पूर्णांकr_enable(व्योम __iomem * स्थिर regs)
अणु
	raw_reg_ग_लिखो(regs, DG1_MSTR_UNIT_INTR, DG1_MSTR_IRQ);
पूर्ण

अटल irqवापस_t dg1_irq_handler(पूर्णांक irq, व्योम *arg)
अणु
	वापस __gen11_irq_handler(arg,
				   dg1_master_पूर्णांकr_disable_and_ack,
				   dg1_master_पूर्णांकr_enable);
पूर्ण

/* Called from drm generic code, passed 'crtc' which
 * we use as a pipe index
 */
पूर्णांक i8xx_enable_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->dev);
	क्रमागत pipe pipe = to_पूर्णांकel_crtc(crtc)->pipe;
	अचिन्हित दीर्घ irqflags;

	spin_lock_irqsave(&dev_priv->irq_lock, irqflags);
	i915_enable_pipestat(dev_priv, pipe, PIPE_VBLANK_INTERRUPT_STATUS);
	spin_unlock_irqrestore(&dev_priv->irq_lock, irqflags);

	वापस 0;
पूर्ण

पूर्णांक i915gm_enable_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->dev);

	/*
	 * Vblank पूर्णांकerrupts fail to wake the device up from C2+.
	 * Disabling render घड़ी gating during C-states aव्योमs
	 * the problem. There is a small घातer cost so we करो this
	 * only when vblank पूर्णांकerrupts are actually enabled.
	 */
	अगर (dev_priv->vblank_enabled++ == 0)
		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, SCPD0, _MASKED_BIT_ENABLE(CSTATE_RENDER_CLOCK_GATE_DISABLE));

	वापस i8xx_enable_vblank(crtc);
पूर्ण

पूर्णांक i965_enable_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->dev);
	क्रमागत pipe pipe = to_पूर्णांकel_crtc(crtc)->pipe;
	अचिन्हित दीर्घ irqflags;

	spin_lock_irqsave(&dev_priv->irq_lock, irqflags);
	i915_enable_pipestat(dev_priv, pipe,
			     PIPE_START_VBLANK_INTERRUPT_STATUS);
	spin_unlock_irqrestore(&dev_priv->irq_lock, irqflags);

	वापस 0;
पूर्ण

पूर्णांक ilk_enable_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->dev);
	क्रमागत pipe pipe = to_पूर्णांकel_crtc(crtc)->pipe;
	अचिन्हित दीर्घ irqflags;
	u32 bit = DISPLAY_VER(dev_priv) >= 7 ?
		DE_PIPE_VBLANK_IVB(pipe) : DE_PIPE_VBLANK(pipe);

	spin_lock_irqsave(&dev_priv->irq_lock, irqflags);
	ilk_enable_display_irq(dev_priv, bit);
	spin_unlock_irqrestore(&dev_priv->irq_lock, irqflags);

	/* Even though there is no DMC, frame counter can get stuck when
	 * PSR is active as no frames are generated.
	 */
	अगर (HAS_PSR(dev_priv))
		drm_crtc_vblank_restore(crtc);

	वापस 0;
पूर्ण

अटल bool gen11_dsi_configure_te(काष्ठा पूर्णांकel_crtc *पूर्णांकel_crtc,
				   bool enable)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(पूर्णांकel_crtc->base.dev);
	क्रमागत port port;
	u32 पंचांगp;

	अगर (!(पूर्णांकel_crtc->mode_flags &
	    (I915_MODE_FLAG_DSI_USE_TE1 | I915_MODE_FLAG_DSI_USE_TE0)))
		वापस false;

	/* क्रम dual link हालs we consider TE from slave */
	अगर (पूर्णांकel_crtc->mode_flags & I915_MODE_FLAG_DSI_USE_TE1)
		port = PORT_B;
	अन्यथा
		port = PORT_A;

	पंचांगp =  पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, DSI_INTR_MASK_REG(port));
	अगर (enable)
		पंचांगp &= ~DSI_TE_EVENT;
	अन्यथा
		पंचांगp |= DSI_TE_EVENT;

	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, DSI_INTR_MASK_REG(port), पंचांगp);

	पंचांगp = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, DSI_INTR_IDENT_REG(port));
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, DSI_INTR_IDENT_REG(port), पंचांगp);

	वापस true;
पूर्ण

पूर्णांक bdw_enable_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->dev);
	काष्ठा पूर्णांकel_crtc *पूर्णांकel_crtc = to_पूर्णांकel_crtc(crtc);
	क्रमागत pipe pipe = पूर्णांकel_crtc->pipe;
	अचिन्हित दीर्घ irqflags;

	अगर (gen11_dsi_configure_te(पूर्णांकel_crtc, true))
		वापस 0;

	spin_lock_irqsave(&dev_priv->irq_lock, irqflags);
	bdw_enable_pipe_irq(dev_priv, pipe, GEN8_PIPE_VBLANK);
	spin_unlock_irqrestore(&dev_priv->irq_lock, irqflags);

	/* Even अगर there is no DMC, frame counter can get stuck when
	 * PSR is active as no frames are generated, so check only क्रम PSR.
	 */
	अगर (HAS_PSR(dev_priv))
		drm_crtc_vblank_restore(crtc);

	वापस 0;
पूर्ण

/* Called from drm generic code, passed 'crtc' which
 * we use as a pipe index
 */
व्योम i8xx_disable_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->dev);
	क्रमागत pipe pipe = to_पूर्णांकel_crtc(crtc)->pipe;
	अचिन्हित दीर्घ irqflags;

	spin_lock_irqsave(&dev_priv->irq_lock, irqflags);
	i915_disable_pipestat(dev_priv, pipe, PIPE_VBLANK_INTERRUPT_STATUS);
	spin_unlock_irqrestore(&dev_priv->irq_lock, irqflags);
पूर्ण

व्योम i915gm_disable_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->dev);

	i8xx_disable_vblank(crtc);

	अगर (--dev_priv->vblank_enabled == 0)
		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, SCPD0, _MASKED_BIT_DISABLE(CSTATE_RENDER_CLOCK_GATE_DISABLE));
पूर्ण

व्योम i965_disable_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->dev);
	क्रमागत pipe pipe = to_पूर्णांकel_crtc(crtc)->pipe;
	अचिन्हित दीर्घ irqflags;

	spin_lock_irqsave(&dev_priv->irq_lock, irqflags);
	i915_disable_pipestat(dev_priv, pipe,
			      PIPE_START_VBLANK_INTERRUPT_STATUS);
	spin_unlock_irqrestore(&dev_priv->irq_lock, irqflags);
पूर्ण

व्योम ilk_disable_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->dev);
	क्रमागत pipe pipe = to_पूर्णांकel_crtc(crtc)->pipe;
	अचिन्हित दीर्घ irqflags;
	u32 bit = DISPLAY_VER(dev_priv) >= 7 ?
		DE_PIPE_VBLANK_IVB(pipe) : DE_PIPE_VBLANK(pipe);

	spin_lock_irqsave(&dev_priv->irq_lock, irqflags);
	ilk_disable_display_irq(dev_priv, bit);
	spin_unlock_irqrestore(&dev_priv->irq_lock, irqflags);
पूर्ण

व्योम bdw_disable_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->dev);
	काष्ठा पूर्णांकel_crtc *पूर्णांकel_crtc = to_पूर्णांकel_crtc(crtc);
	क्रमागत pipe pipe = पूर्णांकel_crtc->pipe;
	अचिन्हित दीर्घ irqflags;

	अगर (gen11_dsi_configure_te(पूर्णांकel_crtc, false))
		वापस;

	spin_lock_irqsave(&dev_priv->irq_lock, irqflags);
	bdw_disable_pipe_irq(dev_priv, pipe, GEN8_PIPE_VBLANK);
	spin_unlock_irqrestore(&dev_priv->irq_lock, irqflags);
पूर्ण

अटल व्योम ibx_irq_reset(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = &dev_priv->uncore;

	अगर (HAS_PCH_NOP(dev_priv))
		वापस;

	GEN3_IRQ_RESET(uncore, SDE);

	अगर (HAS_PCH_CPT(dev_priv) || HAS_PCH_LPT(dev_priv))
		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, SERR_INT, 0xffffffff);
पूर्ण

अटल व्योम vlv_display_irq_reset(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = &dev_priv->uncore;

	अगर (IS_CHERRYVIEW(dev_priv))
		पूर्णांकel_uncore_ग_लिखो(uncore, DPINVGTT, DPINVGTT_STATUS_MASK_CHV);
	अन्यथा
		पूर्णांकel_uncore_ग_लिखो(uncore, DPINVGTT, DPINVGTT_STATUS_MASK);

	i915_hotplug_पूर्णांकerrupt_update_locked(dev_priv, 0xffffffff, 0);
	पूर्णांकel_uncore_ग_लिखो(uncore, PORT_HOTPLUG_STAT, पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, PORT_HOTPLUG_STAT));

	i9xx_pipestat_irq_reset(dev_priv);

	GEN3_IRQ_RESET(uncore, VLV_);
	dev_priv->irq_mask = ~0u;
पूर्ण

अटल व्योम vlv_display_irq_postinstall(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = &dev_priv->uncore;

	u32 pipestat_mask;
	u32 enable_mask;
	क्रमागत pipe pipe;

	pipestat_mask = PIPE_CRC_DONE_INTERRUPT_STATUS;

	i915_enable_pipestat(dev_priv, PIPE_A, PIPE_GMBUS_INTERRUPT_STATUS);
	क्रम_each_pipe(dev_priv, pipe)
		i915_enable_pipestat(dev_priv, pipe, pipestat_mask);

	enable_mask = I915_DISPLAY_PORT_INTERRUPT |
		I915_DISPLAY_PIPE_A_EVENT_INTERRUPT |
		I915_DISPLAY_PIPE_B_EVENT_INTERRUPT |
		I915_LPE_PIPE_A_INTERRUPT |
		I915_LPE_PIPE_B_INTERRUPT;

	अगर (IS_CHERRYVIEW(dev_priv))
		enable_mask |= I915_DISPLAY_PIPE_C_EVENT_INTERRUPT |
			I915_LPE_PIPE_C_INTERRUPT;

	drm_WARN_ON(&dev_priv->drm, dev_priv->irq_mask != ~0u);

	dev_priv->irq_mask = ~enable_mask;

	GEN3_IRQ_INIT(uncore, VLV_, dev_priv->irq_mask, enable_mask);
पूर्ण

/* drm_dma.h hooks
*/
अटल व्योम ilk_irq_reset(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = &dev_priv->uncore;

	GEN3_IRQ_RESET(uncore, DE);
	dev_priv->irq_mask = ~0u;

	अगर (IS_GEN(dev_priv, 7))
		पूर्णांकel_uncore_ग_लिखो(uncore, GEN7_ERR_INT, 0xffffffff);

	अगर (IS_HASWELL(dev_priv)) अणु
		पूर्णांकel_uncore_ग_लिखो(uncore, EDP_PSR_IMR, 0xffffffff);
		पूर्णांकel_uncore_ग_लिखो(uncore, EDP_PSR_IIR, 0xffffffff);
	पूर्ण

	gen5_gt_irq_reset(&dev_priv->gt);

	ibx_irq_reset(dev_priv);
पूर्ण

अटल व्योम valleyview_irq_reset(काष्ठा drm_i915_निजी *dev_priv)
अणु
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, VLV_MASTER_IER, 0);
	पूर्णांकel_uncore_posting_पढ़ो(&dev_priv->uncore, VLV_MASTER_IER);

	gen5_gt_irq_reset(&dev_priv->gt);

	spin_lock_irq(&dev_priv->irq_lock);
	अगर (dev_priv->display_irqs_enabled)
		vlv_display_irq_reset(dev_priv);
	spin_unlock_irq(&dev_priv->irq_lock);
पूर्ण

अटल व्योम cnp_display_घड़ी_wa(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = &dev_priv->uncore;

	/*
	 * Wa_14010685332:cnp/cmp,tgp,adp
	 * TODO: Clarअगरy which platक्रमms this applies to
	 * TODO: Figure out अगर this workaround can be applied in the s0ix suspend/resume handlers as
	 * on earlier platक्रमms and whether the workaround is also needed क्रम runसमय suspend/resume
	 */
	अगर (INTEL_PCH_TYPE(dev_priv) == PCH_CNP ||
	    (INTEL_PCH_TYPE(dev_priv) >= PCH_TGP && INTEL_PCH_TYPE(dev_priv) < PCH_DG1)) अणु
		पूर्णांकel_uncore_rmw(uncore, SOUTH_CHICKEN1, SBCLK_RUN_REFCLK_DIS,
				 SBCLK_RUN_REFCLK_DIS);
		पूर्णांकel_uncore_rmw(uncore, SOUTH_CHICKEN1, SBCLK_RUN_REFCLK_DIS, 0);
	पूर्ण
पूर्ण

अटल व्योम gen8_irq_reset(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = &dev_priv->uncore;
	क्रमागत pipe pipe;

	gen8_master_पूर्णांकr_disable(dev_priv->uncore.regs);

	gen8_gt_irq_reset(&dev_priv->gt);

	पूर्णांकel_uncore_ग_लिखो(uncore, EDP_PSR_IMR, 0xffffffff);
	पूर्णांकel_uncore_ग_लिखो(uncore, EDP_PSR_IIR, 0xffffffff);

	क्रम_each_pipe(dev_priv, pipe)
		अगर (पूर्णांकel_display_घातer_is_enabled(dev_priv,
						   POWER_DOMAIN_PIPE(pipe)))
			GEN8_IRQ_RESET_NDX(uncore, DE_PIPE, pipe);

	GEN3_IRQ_RESET(uncore, GEN8_DE_PORT_);
	GEN3_IRQ_RESET(uncore, GEN8_DE_MISC_);
	GEN3_IRQ_RESET(uncore, GEN8_PCU_);

	अगर (HAS_PCH_SPLIT(dev_priv))
		ibx_irq_reset(dev_priv);

	cnp_display_घड़ी_wa(dev_priv);
पूर्ण

अटल व्योम gen11_display_irq_reset(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = &dev_priv->uncore;
	क्रमागत pipe pipe;
	u32 trans_mask = BIT(TRANSCODER_A) | BIT(TRANSCODER_B) |
		BIT(TRANSCODER_C) | BIT(TRANSCODER_D);

	पूर्णांकel_uncore_ग_लिखो(uncore, GEN11_DISPLAY_INT_CTL, 0);

	अगर (DISPLAY_VER(dev_priv) >= 12) अणु
		क्रमागत transcoder trans;

		क्रम_each_cpu_transcoder_masked(dev_priv, trans, trans_mask) अणु
			क्रमागत पूर्णांकel_display_घातer_करोमुख्य करोमुख्य;

			करोमुख्य = POWER_DOMAIN_TRANSCODER(trans);
			अगर (!पूर्णांकel_display_घातer_is_enabled(dev_priv, करोमुख्य))
				जारी;

			पूर्णांकel_uncore_ग_लिखो(uncore, TRANS_PSR_IMR(trans), 0xffffffff);
			पूर्णांकel_uncore_ग_लिखो(uncore, TRANS_PSR_IIR(trans), 0xffffffff);
		पूर्ण
	पूर्ण अन्यथा अणु
		पूर्णांकel_uncore_ग_लिखो(uncore, EDP_PSR_IMR, 0xffffffff);
		पूर्णांकel_uncore_ग_लिखो(uncore, EDP_PSR_IIR, 0xffffffff);
	पूर्ण

	क्रम_each_pipe(dev_priv, pipe)
		अगर (पूर्णांकel_display_घातer_is_enabled(dev_priv,
						   POWER_DOMAIN_PIPE(pipe)))
			GEN8_IRQ_RESET_NDX(uncore, DE_PIPE, pipe);

	GEN3_IRQ_RESET(uncore, GEN8_DE_PORT_);
	GEN3_IRQ_RESET(uncore, GEN8_DE_MISC_);
	GEN3_IRQ_RESET(uncore, GEN11_DE_HPD_);

	अगर (INTEL_PCH_TYPE(dev_priv) >= PCH_ICP)
		GEN3_IRQ_RESET(uncore, SDE);

	cnp_display_घड़ी_wa(dev_priv);
पूर्ण

अटल व्योम gen11_irq_reset(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = &dev_priv->uncore;

	अगर (HAS_MASTER_UNIT_IRQ(dev_priv))
		dg1_master_पूर्णांकr_disable_and_ack(dev_priv->uncore.regs);
	अन्यथा
		gen11_master_पूर्णांकr_disable(dev_priv->uncore.regs);

	gen11_gt_irq_reset(&dev_priv->gt);
	gen11_display_irq_reset(dev_priv);

	GEN3_IRQ_RESET(uncore, GEN11_GU_MISC_);
	GEN3_IRQ_RESET(uncore, GEN8_PCU_);
पूर्ण

व्योम gen8_irq_घातer_well_post_enable(काष्ठा drm_i915_निजी *dev_priv,
				     u8 pipe_mask)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = &dev_priv->uncore;
	u32 extra_ier = GEN8_PIPE_VBLANK | GEN8_PIPE_FIFO_UNDERRUN |
		gen8_de_pipe_flip_करोne_mask(dev_priv);
	क्रमागत pipe pipe;

	spin_lock_irq(&dev_priv->irq_lock);

	अगर (!पूर्णांकel_irqs_enabled(dev_priv)) अणु
		spin_unlock_irq(&dev_priv->irq_lock);
		वापस;
	पूर्ण

	क्रम_each_pipe_masked(dev_priv, pipe, pipe_mask)
		GEN8_IRQ_INIT_NDX(uncore, DE_PIPE, pipe,
				  dev_priv->de_irq_mask[pipe],
				  ~dev_priv->de_irq_mask[pipe] | extra_ier);

	spin_unlock_irq(&dev_priv->irq_lock);
पूर्ण

व्योम gen8_irq_घातer_well_pre_disable(काष्ठा drm_i915_निजी *dev_priv,
				     u8 pipe_mask)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = &dev_priv->uncore;
	क्रमागत pipe pipe;

	spin_lock_irq(&dev_priv->irq_lock);

	अगर (!पूर्णांकel_irqs_enabled(dev_priv)) अणु
		spin_unlock_irq(&dev_priv->irq_lock);
		वापस;
	पूर्ण

	क्रम_each_pipe_masked(dev_priv, pipe, pipe_mask)
		GEN8_IRQ_RESET_NDX(uncore, DE_PIPE, pipe);

	spin_unlock_irq(&dev_priv->irq_lock);

	/* make sure we're करोne processing display irqs */
	पूर्णांकel_synchronize_irq(dev_priv);
पूर्ण

अटल व्योम cherryview_irq_reset(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = &dev_priv->uncore;

	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, GEN8_MASTER_IRQ, 0);
	पूर्णांकel_uncore_posting_पढ़ो(&dev_priv->uncore, GEN8_MASTER_IRQ);

	gen8_gt_irq_reset(&dev_priv->gt);

	GEN3_IRQ_RESET(uncore, GEN8_PCU_);

	spin_lock_irq(&dev_priv->irq_lock);
	अगर (dev_priv->display_irqs_enabled)
		vlv_display_irq_reset(dev_priv);
	spin_unlock_irq(&dev_priv->irq_lock);
पूर्ण

अटल u32 ibx_hotplug_enables(काष्ठा drm_i915_निजी *i915,
			       क्रमागत hpd_pin pin)
अणु
	चयन (pin) अणु
	हाल HPD_PORT_A:
		/*
		 * When CPU and PCH are on the same package, port A
		 * HPD must be enabled in both north and south.
		 */
		वापस HAS_PCH_LPT_LP(i915) ?
			PORTA_HOTPLUG_ENABLE : 0;
	हाल HPD_PORT_B:
		वापस PORTB_HOTPLUG_ENABLE |
			PORTB_PULSE_DURATION_2ms;
	हाल HPD_PORT_C:
		वापस PORTC_HOTPLUG_ENABLE |
			PORTC_PULSE_DURATION_2ms;
	हाल HPD_PORT_D:
		वापस PORTD_HOTPLUG_ENABLE |
			PORTD_PULSE_DURATION_2ms;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल व्योम ibx_hpd_detection_setup(काष्ठा drm_i915_निजी *dev_priv)
अणु
	u32 hotplug;

	/*
	 * Enable digital hotplug on the PCH, and configure the DP लघु pulse
	 * duration to 2ms (which is the minimum in the Display Port spec).
	 * The pulse duration bits are reserved on LPT+.
	 */
	hotplug = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, PCH_PORT_HOTPLUG);
	hotplug &= ~(PORTA_HOTPLUG_ENABLE |
		     PORTB_HOTPLUG_ENABLE |
		     PORTC_HOTPLUG_ENABLE |
		     PORTD_HOTPLUG_ENABLE |
		     PORTB_PULSE_DURATION_MASK |
		     PORTC_PULSE_DURATION_MASK |
		     PORTD_PULSE_DURATION_MASK);
	hotplug |= पूर्णांकel_hpd_hotplug_enables(dev_priv, ibx_hotplug_enables);
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, PCH_PORT_HOTPLUG, hotplug);
पूर्ण

अटल व्योम ibx_hpd_irq_setup(काष्ठा drm_i915_निजी *dev_priv)
अणु
	u32 hotplug_irqs, enabled_irqs;

	enabled_irqs = पूर्णांकel_hpd_enabled_irqs(dev_priv, dev_priv->hotplug.pch_hpd);
	hotplug_irqs = पूर्णांकel_hpd_hotplug_irqs(dev_priv, dev_priv->hotplug.pch_hpd);

	ibx_display_पूर्णांकerrupt_update(dev_priv, hotplug_irqs, enabled_irqs);

	ibx_hpd_detection_setup(dev_priv);
पूर्ण

अटल u32 icp_ddi_hotplug_enables(काष्ठा drm_i915_निजी *i915,
				   क्रमागत hpd_pin pin)
अणु
	चयन (pin) अणु
	हाल HPD_PORT_A:
	हाल HPD_PORT_B:
	हाल HPD_PORT_C:
	हाल HPD_PORT_D:
		वापस SHOTPLUG_CTL_DDI_HPD_ENABLE(pin);
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल u32 icp_tc_hotplug_enables(काष्ठा drm_i915_निजी *i915,
				  क्रमागत hpd_pin pin)
अणु
	चयन (pin) अणु
	हाल HPD_PORT_TC1:
	हाल HPD_PORT_TC2:
	हाल HPD_PORT_TC3:
	हाल HPD_PORT_TC4:
	हाल HPD_PORT_TC5:
	हाल HPD_PORT_TC6:
		वापस ICP_TC_HPD_ENABLE(pin);
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल व्योम icp_ddi_hpd_detection_setup(काष्ठा drm_i915_निजी *dev_priv)
अणु
	u32 hotplug;

	hotplug = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, SHOTPLUG_CTL_DDI);
	hotplug &= ~(SHOTPLUG_CTL_DDI_HPD_ENABLE(HPD_PORT_A) |
		     SHOTPLUG_CTL_DDI_HPD_ENABLE(HPD_PORT_B) |
		     SHOTPLUG_CTL_DDI_HPD_ENABLE(HPD_PORT_C) |
		     SHOTPLUG_CTL_DDI_HPD_ENABLE(HPD_PORT_D));
	hotplug |= पूर्णांकel_hpd_hotplug_enables(dev_priv, icp_ddi_hotplug_enables);
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, SHOTPLUG_CTL_DDI, hotplug);
पूर्ण

अटल व्योम icp_tc_hpd_detection_setup(काष्ठा drm_i915_निजी *dev_priv)
अणु
	u32 hotplug;

	hotplug = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, SHOTPLUG_CTL_TC);
	hotplug &= ~(ICP_TC_HPD_ENABLE(HPD_PORT_TC1) |
		     ICP_TC_HPD_ENABLE(HPD_PORT_TC2) |
		     ICP_TC_HPD_ENABLE(HPD_PORT_TC3) |
		     ICP_TC_HPD_ENABLE(HPD_PORT_TC4) |
		     ICP_TC_HPD_ENABLE(HPD_PORT_TC5) |
		     ICP_TC_HPD_ENABLE(HPD_PORT_TC6));
	hotplug |= पूर्णांकel_hpd_hotplug_enables(dev_priv, icp_tc_hotplug_enables);
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, SHOTPLUG_CTL_TC, hotplug);
पूर्ण

अटल व्योम icp_hpd_irq_setup(काष्ठा drm_i915_निजी *dev_priv)
अणु
	u32 hotplug_irqs, enabled_irqs;

	enabled_irqs = पूर्णांकel_hpd_enabled_irqs(dev_priv, dev_priv->hotplug.pch_hpd);
	hotplug_irqs = पूर्णांकel_hpd_hotplug_irqs(dev_priv, dev_priv->hotplug.pch_hpd);

	अगर (INTEL_PCH_TYPE(dev_priv) <= PCH_TGP)
		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, SHPD_FILTER_CNT, SHPD_FILTER_CNT_500_ADJ);

	ibx_display_पूर्णांकerrupt_update(dev_priv, hotplug_irqs, enabled_irqs);

	icp_ddi_hpd_detection_setup(dev_priv);
	icp_tc_hpd_detection_setup(dev_priv);
पूर्ण

अटल u32 gen11_hotplug_enables(काष्ठा drm_i915_निजी *i915,
				 क्रमागत hpd_pin pin)
अणु
	चयन (pin) अणु
	हाल HPD_PORT_TC1:
	हाल HPD_PORT_TC2:
	हाल HPD_PORT_TC3:
	हाल HPD_PORT_TC4:
	हाल HPD_PORT_TC5:
	हाल HPD_PORT_TC6:
		वापस GEN11_HOTPLUG_CTL_ENABLE(pin);
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल व्योम dg1_hpd_irq_setup(काष्ठा drm_i915_निजी *dev_priv)
अणु
	u32 val;

	val = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, SOUTH_CHICKEN1);
	val |= (INVERT_DDIA_HPD |
		INVERT_DDIB_HPD |
		INVERT_DDIC_HPD |
		INVERT_DDID_HPD);
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, SOUTH_CHICKEN1, val);

	icp_hpd_irq_setup(dev_priv);
पूर्ण

अटल व्योम gen11_tc_hpd_detection_setup(काष्ठा drm_i915_निजी *dev_priv)
अणु
	u32 hotplug;

	hotplug = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, GEN11_TC_HOTPLUG_CTL);
	hotplug &= ~(GEN11_HOTPLUG_CTL_ENABLE(HPD_PORT_TC1) |
		     GEN11_HOTPLUG_CTL_ENABLE(HPD_PORT_TC2) |
		     GEN11_HOTPLUG_CTL_ENABLE(HPD_PORT_TC3) |
		     GEN11_HOTPLUG_CTL_ENABLE(HPD_PORT_TC4) |
		     GEN11_HOTPLUG_CTL_ENABLE(HPD_PORT_TC5) |
		     GEN11_HOTPLUG_CTL_ENABLE(HPD_PORT_TC6));
	hotplug |= पूर्णांकel_hpd_hotplug_enables(dev_priv, gen11_hotplug_enables);
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, GEN11_TC_HOTPLUG_CTL, hotplug);
पूर्ण

अटल व्योम gen11_tbt_hpd_detection_setup(काष्ठा drm_i915_निजी *dev_priv)
अणु
	u32 hotplug;

	hotplug = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, GEN11_TBT_HOTPLUG_CTL);
	hotplug &= ~(GEN11_HOTPLUG_CTL_ENABLE(HPD_PORT_TC1) |
		     GEN11_HOTPLUG_CTL_ENABLE(HPD_PORT_TC2) |
		     GEN11_HOTPLUG_CTL_ENABLE(HPD_PORT_TC3) |
		     GEN11_HOTPLUG_CTL_ENABLE(HPD_PORT_TC4) |
		     GEN11_HOTPLUG_CTL_ENABLE(HPD_PORT_TC5) |
		     GEN11_HOTPLUG_CTL_ENABLE(HPD_PORT_TC6));
	hotplug |= पूर्णांकel_hpd_hotplug_enables(dev_priv, gen11_hotplug_enables);
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, GEN11_TBT_HOTPLUG_CTL, hotplug);
पूर्ण

अटल व्योम gen11_hpd_irq_setup(काष्ठा drm_i915_निजी *dev_priv)
अणु
	u32 hotplug_irqs, enabled_irqs;
	u32 val;

	enabled_irqs = पूर्णांकel_hpd_enabled_irqs(dev_priv, dev_priv->hotplug.hpd);
	hotplug_irqs = पूर्णांकel_hpd_hotplug_irqs(dev_priv, dev_priv->hotplug.hpd);

	val = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, GEN11_DE_HPD_IMR);
	val &= ~hotplug_irqs;
	val |= ~enabled_irqs & hotplug_irqs;
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, GEN11_DE_HPD_IMR, val);
	पूर्णांकel_uncore_posting_पढ़ो(&dev_priv->uncore, GEN11_DE_HPD_IMR);

	gen11_tc_hpd_detection_setup(dev_priv);
	gen11_tbt_hpd_detection_setup(dev_priv);

	अगर (INTEL_PCH_TYPE(dev_priv) >= PCH_ICP)
		icp_hpd_irq_setup(dev_priv);
पूर्ण

अटल u32 spt_hotplug_enables(काष्ठा drm_i915_निजी *i915,
			       क्रमागत hpd_pin pin)
अणु
	चयन (pin) अणु
	हाल HPD_PORT_A:
		वापस PORTA_HOTPLUG_ENABLE;
	हाल HPD_PORT_B:
		वापस PORTB_HOTPLUG_ENABLE;
	हाल HPD_PORT_C:
		वापस PORTC_HOTPLUG_ENABLE;
	हाल HPD_PORT_D:
		वापस PORTD_HOTPLUG_ENABLE;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल u32 spt_hotplug2_enables(काष्ठा drm_i915_निजी *i915,
				क्रमागत hpd_pin pin)
अणु
	चयन (pin) अणु
	हाल HPD_PORT_E:
		वापस PORTE_HOTPLUG_ENABLE;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल व्योम spt_hpd_detection_setup(काष्ठा drm_i915_निजी *dev_priv)
अणु
	u32 val, hotplug;

	/* Display WA #1179 WaHardHangonHotPlug: cnp */
	अगर (HAS_PCH_CNP(dev_priv)) अणु
		val = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, SOUTH_CHICKEN1);
		val &= ~CHASSIS_CLK_REQ_DURATION_MASK;
		val |= CHASSIS_CLK_REQ_DURATION(0xf);
		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, SOUTH_CHICKEN1, val);
	पूर्ण

	/* Enable digital hotplug on the PCH */
	hotplug = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, PCH_PORT_HOTPLUG);
	hotplug &= ~(PORTA_HOTPLUG_ENABLE |
		     PORTB_HOTPLUG_ENABLE |
		     PORTC_HOTPLUG_ENABLE |
		     PORTD_HOTPLUG_ENABLE);
	hotplug |= पूर्णांकel_hpd_hotplug_enables(dev_priv, spt_hotplug_enables);
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, PCH_PORT_HOTPLUG, hotplug);

	hotplug = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, PCH_PORT_HOTPLUG2);
	hotplug &= ~PORTE_HOTPLUG_ENABLE;
	hotplug |= पूर्णांकel_hpd_hotplug_enables(dev_priv, spt_hotplug2_enables);
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, PCH_PORT_HOTPLUG2, hotplug);
पूर्ण

अटल व्योम spt_hpd_irq_setup(काष्ठा drm_i915_निजी *dev_priv)
अणु
	u32 hotplug_irqs, enabled_irqs;

	अगर (INTEL_PCH_TYPE(dev_priv) >= PCH_CNP)
		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, SHPD_FILTER_CNT, SHPD_FILTER_CNT_500_ADJ);

	enabled_irqs = पूर्णांकel_hpd_enabled_irqs(dev_priv, dev_priv->hotplug.pch_hpd);
	hotplug_irqs = पूर्णांकel_hpd_hotplug_irqs(dev_priv, dev_priv->hotplug.pch_hpd);

	ibx_display_पूर्णांकerrupt_update(dev_priv, hotplug_irqs, enabled_irqs);

	spt_hpd_detection_setup(dev_priv);
पूर्ण

अटल u32 ilk_hotplug_enables(काष्ठा drm_i915_निजी *i915,
			       क्रमागत hpd_pin pin)
अणु
	चयन (pin) अणु
	हाल HPD_PORT_A:
		वापस DIGITAL_PORTA_HOTPLUG_ENABLE |
			DIGITAL_PORTA_PULSE_DURATION_2ms;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल व्योम ilk_hpd_detection_setup(काष्ठा drm_i915_निजी *dev_priv)
अणु
	u32 hotplug;

	/*
	 * Enable digital hotplug on the CPU, and configure the DP लघु pulse
	 * duration to 2ms (which is the minimum in the Display Port spec)
	 * The pulse duration bits are reserved on HSW+.
	 */
	hotplug = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, DIGITAL_PORT_HOTPLUG_CNTRL);
	hotplug &= ~(DIGITAL_PORTA_HOTPLUG_ENABLE |
		     DIGITAL_PORTA_PULSE_DURATION_MASK);
	hotplug |= पूर्णांकel_hpd_hotplug_enables(dev_priv, ilk_hotplug_enables);
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, DIGITAL_PORT_HOTPLUG_CNTRL, hotplug);
पूर्ण

अटल व्योम ilk_hpd_irq_setup(काष्ठा drm_i915_निजी *dev_priv)
अणु
	u32 hotplug_irqs, enabled_irqs;

	enabled_irqs = पूर्णांकel_hpd_enabled_irqs(dev_priv, dev_priv->hotplug.hpd);
	hotplug_irqs = पूर्णांकel_hpd_hotplug_irqs(dev_priv, dev_priv->hotplug.hpd);

	अगर (DISPLAY_VER(dev_priv) >= 8)
		bdw_update_port_irq(dev_priv, hotplug_irqs, enabled_irqs);
	अन्यथा
		ilk_update_display_irq(dev_priv, hotplug_irqs, enabled_irqs);

	ilk_hpd_detection_setup(dev_priv);

	ibx_hpd_irq_setup(dev_priv);
पूर्ण

अटल u32 bxt_hotplug_enables(काष्ठा drm_i915_निजी *i915,
			       क्रमागत hpd_pin pin)
अणु
	u32 hotplug;

	चयन (pin) अणु
	हाल HPD_PORT_A:
		hotplug = PORTA_HOTPLUG_ENABLE;
		अगर (पूर्णांकel_bios_is_port_hpd_inverted(i915, PORT_A))
			hotplug |= BXT_DDIA_HPD_INVERT;
		वापस hotplug;
	हाल HPD_PORT_B:
		hotplug = PORTB_HOTPLUG_ENABLE;
		अगर (पूर्णांकel_bios_is_port_hpd_inverted(i915, PORT_B))
			hotplug |= BXT_DDIB_HPD_INVERT;
		वापस hotplug;
	हाल HPD_PORT_C:
		hotplug = PORTC_HOTPLUG_ENABLE;
		अगर (पूर्णांकel_bios_is_port_hpd_inverted(i915, PORT_C))
			hotplug |= BXT_DDIC_HPD_INVERT;
		वापस hotplug;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल व्योम bxt_hpd_detection_setup(काष्ठा drm_i915_निजी *dev_priv)
अणु
	u32 hotplug;

	hotplug = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, PCH_PORT_HOTPLUG);
	hotplug &= ~(PORTA_HOTPLUG_ENABLE |
		     PORTB_HOTPLUG_ENABLE |
		     PORTC_HOTPLUG_ENABLE |
		     BXT_DDIA_HPD_INVERT |
		     BXT_DDIB_HPD_INVERT |
		     BXT_DDIC_HPD_INVERT);
	hotplug |= पूर्णांकel_hpd_hotplug_enables(dev_priv, bxt_hotplug_enables);
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, PCH_PORT_HOTPLUG, hotplug);
पूर्ण

अटल व्योम bxt_hpd_irq_setup(काष्ठा drm_i915_निजी *dev_priv)
अणु
	u32 hotplug_irqs, enabled_irqs;

	enabled_irqs = पूर्णांकel_hpd_enabled_irqs(dev_priv, dev_priv->hotplug.hpd);
	hotplug_irqs = पूर्णांकel_hpd_hotplug_irqs(dev_priv, dev_priv->hotplug.hpd);

	bdw_update_port_irq(dev_priv, hotplug_irqs, enabled_irqs);

	bxt_hpd_detection_setup(dev_priv);
पूर्ण

/*
 * SDEIER is also touched by the पूर्णांकerrupt handler to work around missed PCH
 * पूर्णांकerrupts. Hence we can't update it after the पूर्णांकerrupt handler is enabled -
 * instead we unconditionally enable all PCH पूर्णांकerrupt sources here, but then
 * only unmask them as needed with SDEIMR.
 *
 * Note that we currently करो this after installing the पूर्णांकerrupt handler,
 * but beक्रमe we enable the master पूर्णांकerrupt. That should be sufficient
 * to aव्योम races with the irq handler, assuming we have MSI. Shared legacy
 * पूर्णांकerrupts could still race.
 */
अटल व्योम ibx_irq_postinstall(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = &dev_priv->uncore;
	u32 mask;

	अगर (HAS_PCH_NOP(dev_priv))
		वापस;

	अगर (HAS_PCH_IBX(dev_priv))
		mask = SDE_GMBUS | SDE_AUX_MASK | SDE_POISON;
	अन्यथा अगर (HAS_PCH_CPT(dev_priv) || HAS_PCH_LPT(dev_priv))
		mask = SDE_GMBUS_CPT | SDE_AUX_MASK_CPT;
	अन्यथा
		mask = SDE_GMBUS_CPT;

	GEN3_IRQ_INIT(uncore, SDE, ~mask, 0xffffffff);
पूर्ण

अटल व्योम ilk_irq_postinstall(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = &dev_priv->uncore;
	u32 display_mask, extra_mask;

	अगर (INTEL_GEN(dev_priv) >= 7) अणु
		display_mask = (DE_MASTER_IRQ_CONTROL | DE_GSE_IVB |
				DE_PCH_EVENT_IVB | DE_AUX_CHANNEL_A_IVB);
		extra_mask = (DE_PIPEC_VBLANK_IVB | DE_PIPEB_VBLANK_IVB |
			      DE_PIPEA_VBLANK_IVB | DE_ERR_INT_IVB |
			      DE_PLANE_FLIP_DONE_IVB(PLANE_C) |
			      DE_PLANE_FLIP_DONE_IVB(PLANE_B) |
			      DE_PLANE_FLIP_DONE_IVB(PLANE_A) |
			      DE_DP_A_HOTPLUG_IVB);
	पूर्ण अन्यथा अणु
		display_mask = (DE_MASTER_IRQ_CONTROL | DE_GSE | DE_PCH_EVENT |
				DE_AUX_CHANNEL_A | DE_PIPEB_CRC_DONE |
				DE_PIPEA_CRC_DONE | DE_POISON);
		extra_mask = (DE_PIPEA_VBLANK | DE_PIPEB_VBLANK |
			      DE_PIPEB_FIFO_UNDERRUN | DE_PIPEA_FIFO_UNDERRUN |
			      DE_PLANE_FLIP_DONE(PLANE_A) |
			      DE_PLANE_FLIP_DONE(PLANE_B) |
			      DE_DP_A_HOTPLUG);
	पूर्ण

	अगर (IS_HASWELL(dev_priv)) अणु
		gen3_निश्चित_iir_is_zero(uncore, EDP_PSR_IIR);
		display_mask |= DE_EDP_PSR_INT_HSW;
	पूर्ण

	अगर (IS_IRONLAKE_M(dev_priv))
		extra_mask |= DE_PCU_EVENT;

	dev_priv->irq_mask = ~display_mask;

	ibx_irq_postinstall(dev_priv);

	gen5_gt_irq_postinstall(&dev_priv->gt);

	GEN3_IRQ_INIT(uncore, DE, dev_priv->irq_mask,
		      display_mask | extra_mask);
पूर्ण

व्योम valleyview_enable_display_irqs(काष्ठा drm_i915_निजी *dev_priv)
अणु
	lockdep_निश्चित_held(&dev_priv->irq_lock);

	अगर (dev_priv->display_irqs_enabled)
		वापस;

	dev_priv->display_irqs_enabled = true;

	अगर (पूर्णांकel_irqs_enabled(dev_priv)) अणु
		vlv_display_irq_reset(dev_priv);
		vlv_display_irq_postinstall(dev_priv);
	पूर्ण
पूर्ण

व्योम valleyview_disable_display_irqs(काष्ठा drm_i915_निजी *dev_priv)
अणु
	lockdep_निश्चित_held(&dev_priv->irq_lock);

	अगर (!dev_priv->display_irqs_enabled)
		वापस;

	dev_priv->display_irqs_enabled = false;

	अगर (पूर्णांकel_irqs_enabled(dev_priv))
		vlv_display_irq_reset(dev_priv);
पूर्ण


अटल व्योम valleyview_irq_postinstall(काष्ठा drm_i915_निजी *dev_priv)
अणु
	gen5_gt_irq_postinstall(&dev_priv->gt);

	spin_lock_irq(&dev_priv->irq_lock);
	अगर (dev_priv->display_irqs_enabled)
		vlv_display_irq_postinstall(dev_priv);
	spin_unlock_irq(&dev_priv->irq_lock);

	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, VLV_MASTER_IER, MASTER_INTERRUPT_ENABLE);
	पूर्णांकel_uncore_posting_पढ़ो(&dev_priv->uncore, VLV_MASTER_IER);
पूर्ण

अटल व्योम gen8_de_irq_postinstall(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = &dev_priv->uncore;

	u32 de_pipe_masked = gen8_de_pipe_fault_mask(dev_priv) |
		GEN8_PIPE_CDCLK_CRC_DONE;
	u32 de_pipe_enables;
	u32 de_port_masked = gen8_de_port_aux_mask(dev_priv);
	u32 de_port_enables;
	u32 de_misc_masked = GEN8_DE_EDP_PSR;
	u32 trans_mask = BIT(TRANSCODER_A) | BIT(TRANSCODER_B) |
		BIT(TRANSCODER_C) | BIT(TRANSCODER_D);
	क्रमागत pipe pipe;

	अगर (DISPLAY_VER(dev_priv) <= 10)
		de_misc_masked |= GEN8_DE_MISC_GSE;

	अगर (IS_GEN9_LP(dev_priv))
		de_port_masked |= BXT_DE_PORT_GMBUS;

	अगर (DISPLAY_VER(dev_priv) >= 11) अणु
		क्रमागत port port;

		अगर (पूर्णांकel_bios_is_dsi_present(dev_priv, &port))
			de_port_masked |= DSI0_TE | DSI1_TE;
	पूर्ण

	de_pipe_enables = de_pipe_masked |
		GEN8_PIPE_VBLANK | GEN8_PIPE_FIFO_UNDERRUN |
		gen8_de_pipe_flip_करोne_mask(dev_priv);

	de_port_enables = de_port_masked;
	अगर (IS_GEN9_LP(dev_priv))
		de_port_enables |= BXT_DE_PORT_HOTPLUG_MASK;
	अन्यथा अगर (IS_BROADWELL(dev_priv))
		de_port_enables |= BDW_DE_PORT_HOTPLUG_MASK;

	अगर (DISPLAY_VER(dev_priv) >= 12) अणु
		क्रमागत transcoder trans;

		क्रम_each_cpu_transcoder_masked(dev_priv, trans, trans_mask) अणु
			क्रमागत पूर्णांकel_display_घातer_करोमुख्य करोमुख्य;

			करोमुख्य = POWER_DOMAIN_TRANSCODER(trans);
			अगर (!पूर्णांकel_display_घातer_is_enabled(dev_priv, करोमुख्य))
				जारी;

			gen3_निश्चित_iir_is_zero(uncore, TRANS_PSR_IIR(trans));
		पूर्ण
	पूर्ण अन्यथा अणु
		gen3_निश्चित_iir_is_zero(uncore, EDP_PSR_IIR);
	पूर्ण

	क्रम_each_pipe(dev_priv, pipe) अणु
		dev_priv->de_irq_mask[pipe] = ~de_pipe_masked;

		अगर (पूर्णांकel_display_घातer_is_enabled(dev_priv,
				POWER_DOMAIN_PIPE(pipe)))
			GEN8_IRQ_INIT_NDX(uncore, DE_PIPE, pipe,
					  dev_priv->de_irq_mask[pipe],
					  de_pipe_enables);
	पूर्ण

	GEN3_IRQ_INIT(uncore, GEN8_DE_PORT_, ~de_port_masked, de_port_enables);
	GEN3_IRQ_INIT(uncore, GEN8_DE_MISC_, ~de_misc_masked, de_misc_masked);

	अगर (DISPLAY_VER(dev_priv) >= 11) अणु
		u32 de_hpd_masked = 0;
		u32 de_hpd_enables = GEN11_DE_TC_HOTPLUG_MASK |
				     GEN11_DE_TBT_HOTPLUG_MASK;

		GEN3_IRQ_INIT(uncore, GEN11_DE_HPD_, ~de_hpd_masked,
			      de_hpd_enables);
	पूर्ण
पूर्ण

अटल व्योम icp_irq_postinstall(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = &dev_priv->uncore;
	u32 mask = SDE_GMBUS_ICP;

	GEN3_IRQ_INIT(uncore, SDE, ~mask, 0xffffffff);
पूर्ण

अटल व्योम gen8_irq_postinstall(काष्ठा drm_i915_निजी *dev_priv)
अणु
	अगर (INTEL_PCH_TYPE(dev_priv) >= PCH_ICP)
		icp_irq_postinstall(dev_priv);
	अन्यथा अगर (HAS_PCH_SPLIT(dev_priv))
		ibx_irq_postinstall(dev_priv);

	gen8_gt_irq_postinstall(&dev_priv->gt);
	gen8_de_irq_postinstall(dev_priv);

	gen8_master_पूर्णांकr_enable(dev_priv->uncore.regs);
पूर्ण


अटल व्योम gen11_irq_postinstall(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = &dev_priv->uncore;
	u32 gu_misc_masked = GEN11_GU_MISC_GSE;

	अगर (INTEL_PCH_TYPE(dev_priv) >= PCH_ICP)
		icp_irq_postinstall(dev_priv);

	gen11_gt_irq_postinstall(&dev_priv->gt);
	gen8_de_irq_postinstall(dev_priv);

	GEN3_IRQ_INIT(uncore, GEN11_GU_MISC_, ~gu_misc_masked, gu_misc_masked);

	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, GEN11_DISPLAY_INT_CTL, GEN11_DISPLAY_IRQ_ENABLE);

	अगर (HAS_MASTER_UNIT_IRQ(dev_priv)) अणु
		dg1_master_पूर्णांकr_enable(uncore->regs);
		पूर्णांकel_uncore_posting_पढ़ो(&dev_priv->uncore, DG1_MSTR_UNIT_INTR);
	पूर्ण अन्यथा अणु
		gen11_master_पूर्णांकr_enable(uncore->regs);
		पूर्णांकel_uncore_posting_पढ़ो(&dev_priv->uncore, GEN11_GFX_MSTR_IRQ);
	पूर्ण
पूर्ण

अटल व्योम cherryview_irq_postinstall(काष्ठा drm_i915_निजी *dev_priv)
अणु
	gen8_gt_irq_postinstall(&dev_priv->gt);

	spin_lock_irq(&dev_priv->irq_lock);
	अगर (dev_priv->display_irqs_enabled)
		vlv_display_irq_postinstall(dev_priv);
	spin_unlock_irq(&dev_priv->irq_lock);

	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, GEN8_MASTER_IRQ, GEN8_MASTER_IRQ_CONTROL);
	पूर्णांकel_uncore_posting_पढ़ो(&dev_priv->uncore, GEN8_MASTER_IRQ);
पूर्ण

अटल व्योम i8xx_irq_reset(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = &dev_priv->uncore;

	i9xx_pipestat_irq_reset(dev_priv);

	GEN2_IRQ_RESET(uncore);
	dev_priv->irq_mask = ~0u;
पूर्ण

अटल व्योम i8xx_irq_postinstall(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = &dev_priv->uncore;
	u16 enable_mask;

	पूर्णांकel_uncore_ग_लिखो16(uncore,
			     EMR,
			     ~(I915_ERROR_PAGE_TABLE |
			       I915_ERROR_MEMORY_REFRESH));

	/* Unmask the पूर्णांकerrupts that we always want on. */
	dev_priv->irq_mask =
		~(I915_DISPLAY_PIPE_A_EVENT_INTERRUPT |
		  I915_DISPLAY_PIPE_B_EVENT_INTERRUPT |
		  I915_MASTER_ERROR_INTERRUPT);

	enable_mask =
		I915_DISPLAY_PIPE_A_EVENT_INTERRUPT |
		I915_DISPLAY_PIPE_B_EVENT_INTERRUPT |
		I915_MASTER_ERROR_INTERRUPT |
		I915_USER_INTERRUPT;

	GEN2_IRQ_INIT(uncore, dev_priv->irq_mask, enable_mask);

	/* Interrupt setup is alपढ़ोy guaranteed to be single-thपढ़ोed, this is
	 * just to make the निश्चित_spin_locked check happy. */
	spin_lock_irq(&dev_priv->irq_lock);
	i915_enable_pipestat(dev_priv, PIPE_A, PIPE_CRC_DONE_INTERRUPT_STATUS);
	i915_enable_pipestat(dev_priv, PIPE_B, PIPE_CRC_DONE_INTERRUPT_STATUS);
	spin_unlock_irq(&dev_priv->irq_lock);
पूर्ण

अटल व्योम i8xx_error_irq_ack(काष्ठा drm_i915_निजी *i915,
			       u16 *eir, u16 *eir_stuck)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = &i915->uncore;
	u16 emr;

	*eir = पूर्णांकel_uncore_पढ़ो16(uncore, EIR);

	अगर (*eir)
		पूर्णांकel_uncore_ग_लिखो16(uncore, EIR, *eir);

	*eir_stuck = पूर्णांकel_uncore_पढ़ो16(uncore, EIR);
	अगर (*eir_stuck == 0)
		वापस;

	/*
	 * Toggle all EMR bits to make sure we get an edge
	 * in the ISR master error bit अगर we करोn't clear
	 * all the EIR bits. Otherwise the edge triggered
	 * IIR on i965/g4x wouldn't notice that an पूर्णांकerrupt
	 * is still pending. Also some EIR bits can't be
	 * cleared except by handling the underlying error
	 * (or by a GPU reset) so we mask any bit that
	 * reमुख्यs set.
	 */
	emr = पूर्णांकel_uncore_पढ़ो16(uncore, EMR);
	पूर्णांकel_uncore_ग_लिखो16(uncore, EMR, 0xffff);
	पूर्णांकel_uncore_ग_लिखो16(uncore, EMR, emr | *eir_stuck);
पूर्ण

अटल व्योम i8xx_error_irq_handler(काष्ठा drm_i915_निजी *dev_priv,
				   u16 eir, u16 eir_stuck)
अणु
	DRM_DEBUG("Master Error: EIR 0x%04x\n", eir);

	अगर (eir_stuck)
		drm_dbg(&dev_priv->drm, "EIR stuck: 0x%04x, masked\n",
			eir_stuck);
पूर्ण

अटल व्योम i9xx_error_irq_ack(काष्ठा drm_i915_निजी *dev_priv,
			       u32 *eir, u32 *eir_stuck)
अणु
	u32 emr;

	*eir = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, EIR);

	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, EIR, *eir);

	*eir_stuck = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, EIR);
	अगर (*eir_stuck == 0)
		वापस;

	/*
	 * Toggle all EMR bits to make sure we get an edge
	 * in the ISR master error bit अगर we करोn't clear
	 * all the EIR bits. Otherwise the edge triggered
	 * IIR on i965/g4x wouldn't notice that an पूर्णांकerrupt
	 * is still pending. Also some EIR bits can't be
	 * cleared except by handling the underlying error
	 * (or by a GPU reset) so we mask any bit that
	 * reमुख्यs set.
	 */
	emr = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, EMR);
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, EMR, 0xffffffff);
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, EMR, emr | *eir_stuck);
पूर्ण

अटल व्योम i9xx_error_irq_handler(काष्ठा drm_i915_निजी *dev_priv,
				   u32 eir, u32 eir_stuck)
अणु
	DRM_DEBUG("Master Error, EIR 0x%08x\n", eir);

	अगर (eir_stuck)
		drm_dbg(&dev_priv->drm, "EIR stuck: 0x%08x, masked\n",
			eir_stuck);
पूर्ण

अटल irqवापस_t i8xx_irq_handler(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा drm_i915_निजी *dev_priv = arg;
	irqवापस_t ret = IRQ_NONE;

	अगर (!पूर्णांकel_irqs_enabled(dev_priv))
		वापस IRQ_NONE;

	/* IRQs are synced during runसमय_suspend, we करोn't require a wakeref */
	disable_rpm_wakeref_निश्चितs(&dev_priv->runसमय_pm);

	करो अणु
		u32 pipe_stats[I915_MAX_PIPES] = अणुपूर्ण;
		u16 eir = 0, eir_stuck = 0;
		u16 iir;

		iir = पूर्णांकel_uncore_पढ़ो16(&dev_priv->uncore, GEN2_IIR);
		अगर (iir == 0)
			अवरोध;

		ret = IRQ_HANDLED;

		/* Call regardless, as some status bits might not be
		 * संकेतled in iir */
		i9xx_pipestat_irq_ack(dev_priv, iir, pipe_stats);

		अगर (iir & I915_MASTER_ERROR_INTERRUPT)
			i8xx_error_irq_ack(dev_priv, &eir, &eir_stuck);

		पूर्णांकel_uncore_ग_लिखो16(&dev_priv->uncore, GEN2_IIR, iir);

		अगर (iir & I915_USER_INTERRUPT)
			पूर्णांकel_engine_संकेत_bपढ़ोcrumbs(dev_priv->gt.engine[RCS0]);

		अगर (iir & I915_MASTER_ERROR_INTERRUPT)
			i8xx_error_irq_handler(dev_priv, eir, eir_stuck);

		i8xx_pipestat_irq_handler(dev_priv, iir, pipe_stats);
	पूर्ण जबतक (0);

	pmu_irq_stats(dev_priv, ret);

	enable_rpm_wakeref_निश्चितs(&dev_priv->runसमय_pm);

	वापस ret;
पूर्ण

अटल व्योम i915_irq_reset(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = &dev_priv->uncore;

	अगर (I915_HAS_HOTPLUG(dev_priv)) अणु
		i915_hotplug_पूर्णांकerrupt_update(dev_priv, 0xffffffff, 0);
		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, PORT_HOTPLUG_STAT, पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, PORT_HOTPLUG_STAT));
	पूर्ण

	i9xx_pipestat_irq_reset(dev_priv);

	GEN3_IRQ_RESET(uncore, GEN2_);
	dev_priv->irq_mask = ~0u;
पूर्ण

अटल व्योम i915_irq_postinstall(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = &dev_priv->uncore;
	u32 enable_mask;

	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, EMR, ~(I915_ERROR_PAGE_TABLE |
			  I915_ERROR_MEMORY_REFRESH));

	/* Unmask the पूर्णांकerrupts that we always want on. */
	dev_priv->irq_mask =
		~(I915_ASLE_INTERRUPT |
		  I915_DISPLAY_PIPE_A_EVENT_INTERRUPT |
		  I915_DISPLAY_PIPE_B_EVENT_INTERRUPT |
		  I915_MASTER_ERROR_INTERRUPT);

	enable_mask =
		I915_ASLE_INTERRUPT |
		I915_DISPLAY_PIPE_A_EVENT_INTERRUPT |
		I915_DISPLAY_PIPE_B_EVENT_INTERRUPT |
		I915_MASTER_ERROR_INTERRUPT |
		I915_USER_INTERRUPT;

	अगर (I915_HAS_HOTPLUG(dev_priv)) अणु
		/* Enable in IER... */
		enable_mask |= I915_DISPLAY_PORT_INTERRUPT;
		/* and unmask in IMR */
		dev_priv->irq_mask &= ~I915_DISPLAY_PORT_INTERRUPT;
	पूर्ण

	GEN3_IRQ_INIT(uncore, GEN2_, dev_priv->irq_mask, enable_mask);

	/* Interrupt setup is alपढ़ोy guaranteed to be single-thपढ़ोed, this is
	 * just to make the निश्चित_spin_locked check happy. */
	spin_lock_irq(&dev_priv->irq_lock);
	i915_enable_pipestat(dev_priv, PIPE_A, PIPE_CRC_DONE_INTERRUPT_STATUS);
	i915_enable_pipestat(dev_priv, PIPE_B, PIPE_CRC_DONE_INTERRUPT_STATUS);
	spin_unlock_irq(&dev_priv->irq_lock);

	i915_enable_asle_pipestat(dev_priv);
पूर्ण

अटल irqवापस_t i915_irq_handler(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा drm_i915_निजी *dev_priv = arg;
	irqवापस_t ret = IRQ_NONE;

	अगर (!पूर्णांकel_irqs_enabled(dev_priv))
		वापस IRQ_NONE;

	/* IRQs are synced during runसमय_suspend, we करोn't require a wakeref */
	disable_rpm_wakeref_निश्चितs(&dev_priv->runसमय_pm);

	करो अणु
		u32 pipe_stats[I915_MAX_PIPES] = अणुपूर्ण;
		u32 eir = 0, eir_stuck = 0;
		u32 hotplug_status = 0;
		u32 iir;

		iir = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, GEN2_IIR);
		अगर (iir == 0)
			अवरोध;

		ret = IRQ_HANDLED;

		अगर (I915_HAS_HOTPLUG(dev_priv) &&
		    iir & I915_DISPLAY_PORT_INTERRUPT)
			hotplug_status = i9xx_hpd_irq_ack(dev_priv);

		/* Call regardless, as some status bits might not be
		 * संकेतled in iir */
		i9xx_pipestat_irq_ack(dev_priv, iir, pipe_stats);

		अगर (iir & I915_MASTER_ERROR_INTERRUPT)
			i9xx_error_irq_ack(dev_priv, &eir, &eir_stuck);

		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, GEN2_IIR, iir);

		अगर (iir & I915_USER_INTERRUPT)
			पूर्णांकel_engine_संकेत_bपढ़ोcrumbs(dev_priv->gt.engine[RCS0]);

		अगर (iir & I915_MASTER_ERROR_INTERRUPT)
			i9xx_error_irq_handler(dev_priv, eir, eir_stuck);

		अगर (hotplug_status)
			i9xx_hpd_irq_handler(dev_priv, hotplug_status);

		i915_pipestat_irq_handler(dev_priv, iir, pipe_stats);
	पूर्ण जबतक (0);

	pmu_irq_stats(dev_priv, ret);

	enable_rpm_wakeref_निश्चितs(&dev_priv->runसमय_pm);

	वापस ret;
पूर्ण

अटल व्योम i965_irq_reset(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = &dev_priv->uncore;

	i915_hotplug_पूर्णांकerrupt_update(dev_priv, 0xffffffff, 0);
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, PORT_HOTPLUG_STAT, पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, PORT_HOTPLUG_STAT));

	i9xx_pipestat_irq_reset(dev_priv);

	GEN3_IRQ_RESET(uncore, GEN2_);
	dev_priv->irq_mask = ~0u;
पूर्ण

अटल व्योम i965_irq_postinstall(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = &dev_priv->uncore;
	u32 enable_mask;
	u32 error_mask;

	/*
	 * Enable some error detection, note the inकाष्ठाion error mask
	 * bit is reserved, so we leave it masked.
	 */
	अगर (IS_G4X(dev_priv)) अणु
		error_mask = ~(GM45_ERROR_PAGE_TABLE |
			       GM45_ERROR_MEM_PRIV |
			       GM45_ERROR_CP_PRIV |
			       I915_ERROR_MEMORY_REFRESH);
	पूर्ण अन्यथा अणु
		error_mask = ~(I915_ERROR_PAGE_TABLE |
			       I915_ERROR_MEMORY_REFRESH);
	पूर्ण
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, EMR, error_mask);

	/* Unmask the पूर्णांकerrupts that we always want on. */
	dev_priv->irq_mask =
		~(I915_ASLE_INTERRUPT |
		  I915_DISPLAY_PORT_INTERRUPT |
		  I915_DISPLAY_PIPE_A_EVENT_INTERRUPT |
		  I915_DISPLAY_PIPE_B_EVENT_INTERRUPT |
		  I915_MASTER_ERROR_INTERRUPT);

	enable_mask =
		I915_ASLE_INTERRUPT |
		I915_DISPLAY_PORT_INTERRUPT |
		I915_DISPLAY_PIPE_A_EVENT_INTERRUPT |
		I915_DISPLAY_PIPE_B_EVENT_INTERRUPT |
		I915_MASTER_ERROR_INTERRUPT |
		I915_USER_INTERRUPT;

	अगर (IS_G4X(dev_priv))
		enable_mask |= I915_BSD_USER_INTERRUPT;

	GEN3_IRQ_INIT(uncore, GEN2_, dev_priv->irq_mask, enable_mask);

	/* Interrupt setup is alपढ़ोy guaranteed to be single-thपढ़ोed, this is
	 * just to make the निश्चित_spin_locked check happy. */
	spin_lock_irq(&dev_priv->irq_lock);
	i915_enable_pipestat(dev_priv, PIPE_A, PIPE_GMBUS_INTERRUPT_STATUS);
	i915_enable_pipestat(dev_priv, PIPE_A, PIPE_CRC_DONE_INTERRUPT_STATUS);
	i915_enable_pipestat(dev_priv, PIPE_B, PIPE_CRC_DONE_INTERRUPT_STATUS);
	spin_unlock_irq(&dev_priv->irq_lock);

	i915_enable_asle_pipestat(dev_priv);
पूर्ण

अटल व्योम i915_hpd_irq_setup(काष्ठा drm_i915_निजी *dev_priv)
अणु
	u32 hotplug_en;

	lockdep_निश्चित_held(&dev_priv->irq_lock);

	/* Note HDMI and DP share hotplug bits */
	/* enable bits are the same क्रम all generations */
	hotplug_en = पूर्णांकel_hpd_enabled_irqs(dev_priv, hpd_mask_i915);
	/* Programming the CRT detection parameters tends
	   to generate a spurious hotplug event about three
	   seconds later.  So just करो it once.
	*/
	अगर (IS_G4X(dev_priv))
		hotplug_en |= CRT_HOTPLUG_ACTIVATION_PERIOD_64;
	hotplug_en |= CRT_HOTPLUG_VOLTAGE_COMPARE_50;

	/* Ignore TV since it's buggy */
	i915_hotplug_पूर्णांकerrupt_update_locked(dev_priv,
					     HOTPLUG_INT_EN_MASK |
					     CRT_HOTPLUG_VOLTAGE_COMPARE_MASK |
					     CRT_HOTPLUG_ACTIVATION_PERIOD_64,
					     hotplug_en);
पूर्ण

अटल irqवापस_t i965_irq_handler(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा drm_i915_निजी *dev_priv = arg;
	irqवापस_t ret = IRQ_NONE;

	अगर (!पूर्णांकel_irqs_enabled(dev_priv))
		वापस IRQ_NONE;

	/* IRQs are synced during runसमय_suspend, we करोn't require a wakeref */
	disable_rpm_wakeref_निश्चितs(&dev_priv->runसमय_pm);

	करो अणु
		u32 pipe_stats[I915_MAX_PIPES] = अणुपूर्ण;
		u32 eir = 0, eir_stuck = 0;
		u32 hotplug_status = 0;
		u32 iir;

		iir = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, GEN2_IIR);
		अगर (iir == 0)
			अवरोध;

		ret = IRQ_HANDLED;

		अगर (iir & I915_DISPLAY_PORT_INTERRUPT)
			hotplug_status = i9xx_hpd_irq_ack(dev_priv);

		/* Call regardless, as some status bits might not be
		 * संकेतled in iir */
		i9xx_pipestat_irq_ack(dev_priv, iir, pipe_stats);

		अगर (iir & I915_MASTER_ERROR_INTERRUPT)
			i9xx_error_irq_ack(dev_priv, &eir, &eir_stuck);

		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, GEN2_IIR, iir);

		अगर (iir & I915_USER_INTERRUPT)
			पूर्णांकel_engine_संकेत_bपढ़ोcrumbs(dev_priv->gt.engine[RCS0]);

		अगर (iir & I915_BSD_USER_INTERRUPT)
			पूर्णांकel_engine_संकेत_bपढ़ोcrumbs(dev_priv->gt.engine[VCS0]);

		अगर (iir & I915_MASTER_ERROR_INTERRUPT)
			i9xx_error_irq_handler(dev_priv, eir, eir_stuck);

		अगर (hotplug_status)
			i9xx_hpd_irq_handler(dev_priv, hotplug_status);

		i965_pipestat_irq_handler(dev_priv, iir, pipe_stats);
	पूर्ण जबतक (0);

	pmu_irq_stats(dev_priv, IRQ_HANDLED);

	enable_rpm_wakeref_निश्चितs(&dev_priv->runसमय_pm);

	वापस ret;
पूर्ण

/**
 * पूर्णांकel_irq_init - initializes irq support
 * @dev_priv: i915 device instance
 *
 * This function initializes all the irq support including work items, समयrs
 * and all the vtables. It करोes not setup the पूर्णांकerrupt itself though.
 */
व्योम पूर्णांकel_irq_init(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा drm_device *dev = &dev_priv->drm;
	पूर्णांक i;

	INIT_WORK(&dev_priv->l3_parity.error_work, ivb_parity_work);
	क्रम (i = 0; i < MAX_L3_SLICES; ++i)
		dev_priv->l3_parity.remap_info[i] = शून्य;

	/* pre-gen11 the guc irqs bits are in the upper 16 bits of the pm reg */
	अगर (HAS_GT_UC(dev_priv) && INTEL_GEN(dev_priv) < 11)
		dev_priv->gt.pm_guc_events = GUC_INTR_GUC2HOST << 16;

	अगर (!HAS_DISPLAY(dev_priv))
		वापस;

	पूर्णांकel_hpd_init_pins(dev_priv);

	पूर्णांकel_hpd_init_work(dev_priv);

	dev->vblank_disable_immediate = true;

	/* Most platक्रमms treat the display irq block as an always-on
	 * घातer करोमुख्य. vlv/chv can disable it at runसमय and need
	 * special care to aव्योम writing any of the display block रेजिस्टरs
	 * outside of the घातer करोमुख्य. We defer setting up the display irqs
	 * in this हाल to the runसमय pm.
	 */
	dev_priv->display_irqs_enabled = true;
	अगर (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv))
		dev_priv->display_irqs_enabled = false;

	dev_priv->hotplug.hpd_storm_threshold = HPD_STORM_DEFAULT_THRESHOLD;
	/* If we have MST support, we want to aव्योम करोing लघु HPD IRQ storm
	 * detection, as लघु HPD storms will occur as a natural part of
	 * sideband messaging with MST.
	 * On older platक्रमms however, IRQ storms can occur with both दीर्घ and
	 * लघु pulses, as seen on some G4x प्रणालीs.
	 */
	dev_priv->hotplug.hpd_लघु_storm_enabled = !HAS_DP_MST(dev_priv);

	अगर (HAS_GMCH(dev_priv)) अणु
		अगर (I915_HAS_HOTPLUG(dev_priv))
			dev_priv->display.hpd_irq_setup = i915_hpd_irq_setup;
	पूर्ण अन्यथा अणु
		अगर (HAS_PCH_DG1(dev_priv))
			dev_priv->display.hpd_irq_setup = dg1_hpd_irq_setup;
		अन्यथा अगर (DISPLAY_VER(dev_priv) >= 11)
			dev_priv->display.hpd_irq_setup = gen11_hpd_irq_setup;
		अन्यथा अगर (IS_GEN9_LP(dev_priv))
			dev_priv->display.hpd_irq_setup = bxt_hpd_irq_setup;
		अन्यथा अगर (INTEL_PCH_TYPE(dev_priv) >= PCH_ICP)
			dev_priv->display.hpd_irq_setup = icp_hpd_irq_setup;
		अन्यथा अगर (INTEL_PCH_TYPE(dev_priv) >= PCH_SPT)
			dev_priv->display.hpd_irq_setup = spt_hpd_irq_setup;
		अन्यथा
			dev_priv->display.hpd_irq_setup = ilk_hpd_irq_setup;
	पूर्ण
पूर्ण

/**
 * पूर्णांकel_irq_fini - deinitializes IRQ support
 * @i915: i915 device instance
 *
 * This function deinitializes all the IRQ support.
 */
व्योम पूर्णांकel_irq_fini(काष्ठा drm_i915_निजी *i915)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MAX_L3_SLICES; ++i)
		kमुक्त(i915->l3_parity.remap_info[i]);
पूर्ण

अटल irq_handler_t पूर्णांकel_irq_handler(काष्ठा drm_i915_निजी *dev_priv)
अणु
	अगर (HAS_GMCH(dev_priv)) अणु
		अगर (IS_CHERRYVIEW(dev_priv))
			वापस cherryview_irq_handler;
		अन्यथा अगर (IS_VALLEYVIEW(dev_priv))
			वापस valleyview_irq_handler;
		अन्यथा अगर (IS_GEN(dev_priv, 4))
			वापस i965_irq_handler;
		अन्यथा अगर (IS_GEN(dev_priv, 3))
			वापस i915_irq_handler;
		अन्यथा
			वापस i8xx_irq_handler;
	पूर्ण अन्यथा अणु
		अगर (HAS_MASTER_UNIT_IRQ(dev_priv))
			वापस dg1_irq_handler;
		अगर (INTEL_GEN(dev_priv) >= 11)
			वापस gen11_irq_handler;
		अन्यथा अगर (INTEL_GEN(dev_priv) >= 8)
			वापस gen8_irq_handler;
		अन्यथा
			वापस ilk_irq_handler;
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_irq_reset(काष्ठा drm_i915_निजी *dev_priv)
अणु
	अगर (HAS_GMCH(dev_priv)) अणु
		अगर (IS_CHERRYVIEW(dev_priv))
			cherryview_irq_reset(dev_priv);
		अन्यथा अगर (IS_VALLEYVIEW(dev_priv))
			valleyview_irq_reset(dev_priv);
		अन्यथा अगर (IS_GEN(dev_priv, 4))
			i965_irq_reset(dev_priv);
		अन्यथा अगर (IS_GEN(dev_priv, 3))
			i915_irq_reset(dev_priv);
		अन्यथा
			i8xx_irq_reset(dev_priv);
	पूर्ण अन्यथा अणु
		अगर (INTEL_GEN(dev_priv) >= 11)
			gen11_irq_reset(dev_priv);
		अन्यथा अगर (INTEL_GEN(dev_priv) >= 8)
			gen8_irq_reset(dev_priv);
		अन्यथा
			ilk_irq_reset(dev_priv);
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_irq_postinstall(काष्ठा drm_i915_निजी *dev_priv)
अणु
	अगर (HAS_GMCH(dev_priv)) अणु
		अगर (IS_CHERRYVIEW(dev_priv))
			cherryview_irq_postinstall(dev_priv);
		अन्यथा अगर (IS_VALLEYVIEW(dev_priv))
			valleyview_irq_postinstall(dev_priv);
		अन्यथा अगर (IS_GEN(dev_priv, 4))
			i965_irq_postinstall(dev_priv);
		अन्यथा अगर (IS_GEN(dev_priv, 3))
			i915_irq_postinstall(dev_priv);
		अन्यथा
			i8xx_irq_postinstall(dev_priv);
	पूर्ण अन्यथा अणु
		अगर (INTEL_GEN(dev_priv) >= 11)
			gen11_irq_postinstall(dev_priv);
		अन्यथा अगर (INTEL_GEN(dev_priv) >= 8)
			gen8_irq_postinstall(dev_priv);
		अन्यथा
			ilk_irq_postinstall(dev_priv);
	पूर्ण
पूर्ण

/**
 * पूर्णांकel_irq_install - enables the hardware पूर्णांकerrupt
 * @dev_priv: i915 device instance
 *
 * This function enables the hardware पूर्णांकerrupt handling, but leaves the hotplug
 * handling still disabled. It is called after पूर्णांकel_irq_init().
 *
 * In the driver load and resume code we need working पूर्णांकerrupts in a few places
 * but करोn't want to deal with the hassle of concurrent probe and hotplug
 * workers. Hence the split पूर्णांकo this two-stage approach.
 */
पूर्णांक पूर्णांकel_irq_install(काष्ठा drm_i915_निजी *dev_priv)
अणु
	पूर्णांक irq = to_pci_dev(dev_priv->drm.dev)->irq;
	पूर्णांक ret;

	/*
	 * We enable some पूर्णांकerrupt sources in our postinstall hooks, so mark
	 * पूर्णांकerrupts as enabled _beक्रमe_ actually enabling them to aव्योम
	 * special हालs in our ordering checks.
	 */
	dev_priv->runसमय_pm.irqs_enabled = true;

	dev_priv->drm.irq_enabled = true;

	पूर्णांकel_irq_reset(dev_priv);

	ret = request_irq(irq, पूर्णांकel_irq_handler(dev_priv),
			  IRQF_SHARED, DRIVER_NAME, dev_priv);
	अगर (ret < 0) अणु
		dev_priv->drm.irq_enabled = false;
		वापस ret;
	पूर्ण

	पूर्णांकel_irq_postinstall(dev_priv);

	वापस ret;
पूर्ण

/**
 * पूर्णांकel_irq_uninstall - finilizes all irq handling
 * @dev_priv: i915 device instance
 *
 * This stops पूर्णांकerrupt and hotplug handling and unरेजिस्टरs and मुक्तs all
 * resources acquired in the init functions.
 */
व्योम पूर्णांकel_irq_uninstall(काष्ठा drm_i915_निजी *dev_priv)
अणु
	पूर्णांक irq = to_pci_dev(dev_priv->drm.dev)->irq;

	/*
	 * FIXME we can get called twice during driver probe
	 * error handling as well as during driver हटाओ due to
	 * पूर्णांकel_modeset_driver_हटाओ() calling us out of sequence.
	 * Would be nice अगर it didn't करो that...
	 */
	अगर (!dev_priv->drm.irq_enabled)
		वापस;

	dev_priv->drm.irq_enabled = false;

	पूर्णांकel_irq_reset(dev_priv);

	मुक्त_irq(irq, dev_priv);

	पूर्णांकel_hpd_cancel_work(dev_priv);
	dev_priv->runसमय_pm.irqs_enabled = false;
पूर्ण

/**
 * पूर्णांकel_runसमय_pm_disable_पूर्णांकerrupts - runसमय पूर्णांकerrupt disabling
 * @dev_priv: i915 device instance
 *
 * This function is used to disable पूर्णांकerrupts at runसमय, both in the runसमय
 * pm and the प्रणाली suspend/resume code.
 */
व्योम पूर्णांकel_runसमय_pm_disable_पूर्णांकerrupts(काष्ठा drm_i915_निजी *dev_priv)
अणु
	पूर्णांकel_irq_reset(dev_priv);
	dev_priv->runसमय_pm.irqs_enabled = false;
	पूर्णांकel_synchronize_irq(dev_priv);
पूर्ण

/**
 * पूर्णांकel_runसमय_pm_enable_पूर्णांकerrupts - runसमय पूर्णांकerrupt enabling
 * @dev_priv: i915 device instance
 *
 * This function is used to enable पूर्णांकerrupts at runसमय, both in the runसमय
 * pm and the प्रणाली suspend/resume code.
 */
व्योम पूर्णांकel_runसमय_pm_enable_पूर्णांकerrupts(काष्ठा drm_i915_निजी *dev_priv)
अणु
	dev_priv->runसमय_pm.irqs_enabled = true;
	पूर्णांकel_irq_reset(dev_priv);
	पूर्णांकel_irq_postinstall(dev_priv);
पूर्ण

bool पूर्णांकel_irqs_enabled(काष्ठा drm_i915_निजी *dev_priv)
अणु
	/*
	 * We only use drm_irq_uninstall() at unload and VT चयन, so
	 * this is the only thing we need to check.
	 */
	वापस dev_priv->runसमय_pm.irqs_enabled;
पूर्ण

व्योम पूर्णांकel_synchronize_irq(काष्ठा drm_i915_निजी *i915)
अणु
	synchronize_irq(to_pci_dev(i915->drm.dev)->irq);
पूर्ण
