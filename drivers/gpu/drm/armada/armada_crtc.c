<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012 Russell King
 *  Rewritten from the करोvefb driver, and Armada510 manuals.
 */

#समावेश <linux/clk.h>
#समावेश <linux/component.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_plane_helper.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_vblank.h>

#समावेश "armada_crtc.h"
#समावेश "armada_drm.h"
#समावेश "armada_fb.h"
#समावेश "armada_gem.h"
#समावेश "armada_hw.h"
#समावेश "armada_plane.h"
#समावेश "armada_trace.h"

/*
 * A note about पूर्णांकerlacing.  Let's consider HDMI 1920x1080i.
 * The timing parameters we have from X are:
 *  Hact HsyA HsyI Htot  Vact VsyA VsyI Vtot
 *  1920 2448 2492 2640  1080 1084 1094 1125
 * Which get translated to:
 *  Hact HsyA HsyI Htot  Vact VsyA VsyI Vtot
 *  1920 2448 2492 2640   540  542  547  562
 *
 * This is how it is defined by CEA-861-D - line and pixel numbers are
 * referenced to the rising edge of VSYNC and HSYNC.  Total घड़ीs per
 * line: 2640.  The odd frame, the first active line is at line 21, and
 * the even frame, the first active line is 584.
 *
 * LN:    560     561     562     563             567     568    569
 * DE:    ~~~|____________________________//__________________________
 * HSYNC: ____|~|_____|~|_____|~|_____|~|_//__|~|_____|~|_____|~|_____
 * VSYNC: _________________________|~~~~~~//~~~~~~~~~~~~~~~|__________
 *  22 blanking lines.  VSYNC at 1320 (referenced to the HSYNC rising edge).
 *
 * LN:    1123   1124    1125      1               5       6      7
 * DE:    ~~~|____________________________//__________________________
 * HSYNC: ____|~|_____|~|_____|~|_____|~|_//__|~|_____|~|_____|~|_____
 * VSYNC: ____________________|~~~~~~~~~~~//~~~~~~~~~~|_______________
 *  23 blanking lines
 *
 * The Armada LCD Controller line and pixel numbers are, like X timings,
 * referenced to the top left of the active frame.
 *
 * So, translating these to our LCD controller:
 *  Odd frame, 563 total lines, VSYNC at line 543-548, pixel 1128.
 *  Even frame, 562 total lines, VSYNC at line 542-547, pixel 2448.
 * Note: Vsync front porch reमुख्यs स्थिरant!
 *
 * अगर (odd_frame) अणु
 *   vtotal = mode->crtc_vtotal + 1;
 *   vbackporch = mode->crtc_vsync_start - mode->crtc_vdisplay + 1;
 *   vhorizpos = mode->crtc_hsync_start - mode->crtc_htotal / 2
 * पूर्ण अन्यथा अणु
 *   vtotal = mode->crtc_vtotal;
 *   vbackporch = mode->crtc_vsync_start - mode->crtc_vdisplay;
 *   vhorizpos = mode->crtc_hsync_start;
 * पूर्ण
 * vfrontporch = mode->crtc_vtotal - mode->crtc_vsync_end;
 *
 * So, we need to reprogram these रेजिस्टरs on each vsync event:
 *  LCD_SPU_V_PORCH, LCD_SPU_ADV_REG, LCD_SPUT_V_H_TOTAL
 *
 * Note: we करो not use the frame करोne पूर्णांकerrupts because these appear
 * to happen too early, and lead to jitter on the display (presumably
 * they occur at the end of the last active line, beक्रमe the vsync back
 * porch, which we're reprogramming.)
 */

व्योम
armada_drm_crtc_update_regs(काष्ठा armada_crtc *dcrtc, काष्ठा armada_regs *regs)
अणु
	जबतक (regs->offset != ~0) अणु
		व्योम __iomem *reg = dcrtc->base + regs->offset;
		uपूर्णांक32_t val;

		val = regs->mask;
		अगर (val != 0)
			val &= पढ़ोl_relaxed(reg);
		ग_लिखोl_relaxed(val | regs->val, reg);
		++regs;
	पूर्ण
पूर्ण

अटल व्योम armada_drm_crtc_update(काष्ठा armada_crtc *dcrtc, bool enable)
अणु
	uपूर्णांक32_t dumb_ctrl;

	dumb_ctrl = dcrtc->cfg_dumb_ctrl;

	अगर (enable)
		dumb_ctrl |= CFG_DUMB_ENA;

	/*
	 * When the dumb पूर्णांकerface isn't in DUMB24_RGB888_0 mode, it might
	 * be using SPI or GPIO.  If we set this to DUMB_BLANK, we will
	 * क्रमce LCD_D[23:0] to output blank color, overriding the GPIO or
	 * SPI usage.  So leave it as-is unless in DUMB24_RGB888_0 mode.
	 */
	अगर (!enable && (dumb_ctrl & DUMB_MASK) == DUMB24_RGB888_0) अणु
		dumb_ctrl &= ~DUMB_MASK;
		dumb_ctrl |= DUMB_BLANK;
	पूर्ण

	armada_updatel(dumb_ctrl,
		       ~(CFG_INV_CSYNC | CFG_INV_HSYNC | CFG_INV_VSYNC),
		       dcrtc->base + LCD_SPU_DUMB_CTRL);
पूर्ण

अटल व्योम armada_drm_crtc_queue_state_event(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा armada_crtc *dcrtc = drm_to_armada_crtc(crtc);
	काष्ठा drm_pending_vblank_event *event;

	/* If we have an event, we need vblank events enabled */
	event = xchg(&crtc->state->event, शून्य);
	अगर (event) अणु
		WARN_ON(drm_crtc_vblank_get(crtc) != 0);
		dcrtc->event = event;
	पूर्ण
पूर्ण

अटल व्योम armada_drm_update_gamma(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_property_blob *blob = crtc->state->gamma_lut;
	व्योम __iomem *base = drm_to_armada_crtc(crtc)->base;
	पूर्णांक i;

	अगर (blob) अणु
		काष्ठा drm_color_lut *lut = blob->data;

		armada_updatel(CFG_CSB_256x8, CFG_CSB_256x8 | CFG_PDWN256x8,
			       base + LCD_SPU_SRAM_PARA1);

		क्रम (i = 0; i < 256; i++) अणु
			ग_लिखोl_relaxed(drm_color_lut_extract(lut[i].red, 8),
				       base + LCD_SPU_SRAM_WRDAT);
			ग_लिखोl_relaxed(i | SRAM_WRITE | SRAM_GAMMA_YR,
				       base + LCD_SPU_SRAM_CTRL);
			पढ़ोl_relaxed(base + LCD_SPU_HWC_OVSA_HPXL_VLN);
			ग_लिखोl_relaxed(drm_color_lut_extract(lut[i].green, 8),
				       base + LCD_SPU_SRAM_WRDAT);
			ग_लिखोl_relaxed(i | SRAM_WRITE | SRAM_GAMMA_UG,
				       base + LCD_SPU_SRAM_CTRL);
			पढ़ोl_relaxed(base + LCD_SPU_HWC_OVSA_HPXL_VLN);
			ग_लिखोl_relaxed(drm_color_lut_extract(lut[i].blue, 8),
				       base + LCD_SPU_SRAM_WRDAT);
			ग_लिखोl_relaxed(i | SRAM_WRITE | SRAM_GAMMA_VB,
				       base + LCD_SPU_SRAM_CTRL);
			पढ़ोl_relaxed(base + LCD_SPU_HWC_OVSA_HPXL_VLN);
		पूर्ण
		armada_updatel(CFG_GAMMA_ENA, CFG_GAMMA_ENA,
			       base + LCD_SPU_DMA_CTRL0);
	पूर्ण अन्यथा अणु
		armada_updatel(0, CFG_GAMMA_ENA, base + LCD_SPU_DMA_CTRL0);
		armada_updatel(CFG_PDWN256x8, CFG_CSB_256x8 | CFG_PDWN256x8,
			       base + LCD_SPU_SRAM_PARA1);
	पूर्ण
पूर्ण

अटल क्रमागत drm_mode_status armada_drm_crtc_mode_valid(काष्ठा drm_crtc *crtc,
	स्थिर काष्ठा drm_display_mode *mode)
अणु
	काष्ठा armada_crtc *dcrtc = drm_to_armada_crtc(crtc);

	अगर (mode->vscan > 1)
		वापस MODE_NO_VSCAN;

	अगर (mode->flags & DRM_MODE_FLAG_DBLSCAN)
		वापस MODE_NO_DBLESCAN;

	अगर (mode->flags & DRM_MODE_FLAG_HSKEW)
		वापस MODE_H_ILLEGAL;

	/* We can't do interlaced modes if we don't have the SPU_ADV_REG */
	अगर (!dcrtc->variant->has_spu_adv_reg &&
	    mode->flags & DRM_MODE_FLAG_INTERLACE)
		वापस MODE_NO_INTERLACE;

	अगर (mode->flags & (DRM_MODE_FLAG_BCAST | DRM_MODE_FLAG_PIXMUX |
			   DRM_MODE_FLAG_CLKDIV2))
		वापस MODE_BAD;

	वापस MODE_OK;
पूर्ण

/* The mode_config.mutex will be held क्रम this call */
अटल bool armada_drm_crtc_mode_fixup(काष्ठा drm_crtc *crtc,
	स्थिर काष्ठा drm_display_mode *mode, काष्ठा drm_display_mode *adj)
अणु
	काष्ठा armada_crtc *dcrtc = drm_to_armada_crtc(crtc);
	पूर्णांक ret;

	/*
	 * Set CRTC modesetting parameters क्रम the adjusted mode.  This is
	 * applied after the connectors, bridges, and encoders have fixed up
	 * this mode, as described above drm_atomic_helper_check_modeset().
	 */
	drm_mode_set_crtcinfo(adj, CRTC_INTERLACE_HALVE_V);

	/*
	 * Validate the adjusted mode in हाल an encoder/bridge has set
	 * something we करोn't support.
	 */
	अगर (armada_drm_crtc_mode_valid(crtc, adj) != MODE_OK)
		वापस false;

	/* Check whether the display mode is possible */
	ret = dcrtc->variant->compute_घड़ी(dcrtc, adj, शून्य);
	अगर (ret)
		वापस false;

	वापस true;
पूर्ण

/* These are locked by dev->vbl_lock */
अटल व्योम armada_drm_crtc_disable_irq(काष्ठा armada_crtc *dcrtc, u32 mask)
अणु
	अगर (dcrtc->irq_ena & mask) अणु
		dcrtc->irq_ena &= ~mask;
		ग_लिखोl(dcrtc->irq_ena, dcrtc->base + LCD_SPU_IRQ_ENA);
	पूर्ण
पूर्ण

अटल व्योम armada_drm_crtc_enable_irq(काष्ठा armada_crtc *dcrtc, u32 mask)
अणु
	अगर ((dcrtc->irq_ena & mask) != mask) अणु
		dcrtc->irq_ena |= mask;
		ग_लिखोl(dcrtc->irq_ena, dcrtc->base + LCD_SPU_IRQ_ENA);
		अगर (पढ़ोl_relaxed(dcrtc->base + LCD_SPU_IRQ_ISR) & mask)
			ग_लिखोl(0, dcrtc->base + LCD_SPU_IRQ_ISR);
	पूर्ण
पूर्ण

अटल व्योम armada_drm_crtc_irq(काष्ठा armada_crtc *dcrtc, u32 stat)
अणु
	काष्ठा drm_pending_vblank_event *event;
	व्योम __iomem *base = dcrtc->base;

	अगर (stat & DMA_FF_UNDERFLOW)
		DRM_ERROR("video underflow on crtc %u\n", dcrtc->num);
	अगर (stat & GRA_FF_UNDERFLOW)
		DRM_ERROR("graphics underflow on crtc %u\n", dcrtc->num);

	अगर (stat & VSYNC_IRQ)
		drm_crtc_handle_vblank(&dcrtc->crtc);

	spin_lock(&dcrtc->irq_lock);
	अगर (stat & GRA_FRAME_IRQ && dcrtc->पूर्णांकerlaced) अणु
		पूर्णांक i = stat & GRA_FRAME_IRQ0 ? 0 : 1;
		uपूर्णांक32_t val;

		ग_लिखोl_relaxed(dcrtc->v[i].spu_v_porch, base + LCD_SPU_V_PORCH);
		ग_लिखोl_relaxed(dcrtc->v[i].spu_v_h_total,
			       base + LCD_SPUT_V_H_TOTAL);

		val = पढ़ोl_relaxed(base + LCD_SPU_ADV_REG);
		val &= ~(ADV_VSYNC_L_OFF | ADV_VSYNC_H_OFF | ADV_VSYNCOFFEN);
		val |= dcrtc->v[i].spu_adv_reg;
		ग_लिखोl_relaxed(val, base + LCD_SPU_ADV_REG);
	पूर्ण

	अगर (stat & dcrtc->irq_ena & DUMB_FRAMEDONE) अणु
		अगर (dcrtc->update_pending) अणु
			armada_drm_crtc_update_regs(dcrtc, dcrtc->regs);
			dcrtc->update_pending = false;
		पूर्ण
		अगर (dcrtc->cursor_update) अणु
			ग_लिखोl_relaxed(dcrtc->cursor_hw_pos,
				       base + LCD_SPU_HWC_OVSA_HPXL_VLN);
			ग_लिखोl_relaxed(dcrtc->cursor_hw_sz,
				       base + LCD_SPU_HWC_HPXL_VLN);
			armada_updatel(CFG_HWC_ENA,
				       CFG_HWC_ENA | CFG_HWC_1BITMOD |
				       CFG_HWC_1BITENA,
				       base + LCD_SPU_DMA_CTRL0);
			dcrtc->cursor_update = false;
		पूर्ण
		armada_drm_crtc_disable_irq(dcrtc, DUMB_FRAMEDONE_ENA);
	पूर्ण
	spin_unlock(&dcrtc->irq_lock);

	अगर (stat & VSYNC_IRQ && !dcrtc->update_pending) अणु
		event = xchg(&dcrtc->event, शून्य);
		अगर (event) अणु
			spin_lock(&dcrtc->crtc.dev->event_lock);
			drm_crtc_send_vblank_event(&dcrtc->crtc, event);
			spin_unlock(&dcrtc->crtc.dev->event_lock);
			drm_crtc_vblank_put(&dcrtc->crtc);
		पूर्ण
	पूर्ण
पूर्ण

अटल irqवापस_t armada_drm_irq(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा armada_crtc *dcrtc = arg;
	u32 v, stat = पढ़ोl_relaxed(dcrtc->base + LCD_SPU_IRQ_ISR);

	/*
	 * Reading the ISR appears to clear bits provided CLEAN_SPU_IRQ_ISR
	 * is set.  Writing has some other effect to acknowledge the IRQ -
	 * without this, we only get a single IRQ.
	 */
	ग_लिखोl_relaxed(0, dcrtc->base + LCD_SPU_IRQ_ISR);

	trace_armada_drm_irq(&dcrtc->crtc, stat);

	/* Mask out those पूर्णांकerrupts we haven't enabled */
	v = stat & dcrtc->irq_ena;

	अगर (v & (VSYNC_IRQ|GRA_FRAME_IRQ|DUMB_FRAMEDONE)) अणु
		armada_drm_crtc_irq(dcrtc, stat);
		वापस IRQ_HANDLED;
	पूर्ण
	वापस IRQ_NONE;
पूर्ण

/* The mode_config.mutex will be held क्रम this call */
अटल व्योम armada_drm_crtc_mode_set_nofb(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_display_mode *adj = &crtc->state->adjusted_mode;
	काष्ठा armada_crtc *dcrtc = drm_to_armada_crtc(crtc);
	काष्ठा armada_regs regs[17];
	uपूर्णांक32_t lm, rm, पंचांग, bm, val, sclk;
	अचिन्हित दीर्घ flags;
	अचिन्हित i;
	bool पूर्णांकerlaced = !!(adj->flags & DRM_MODE_FLAG_INTERLACE);

	i = 0;
	rm = adj->crtc_hsync_start - adj->crtc_hdisplay;
	lm = adj->crtc_htotal - adj->crtc_hsync_end;
	bm = adj->crtc_vsync_start - adj->crtc_vdisplay;
	पंचांग = adj->crtc_vtotal - adj->crtc_vsync_end;

	DRM_DEBUG_KMS("[CRTC:%d:%s] mode " DRM_MODE_FMT "\n",
		      crtc->base.id, crtc->name, DRM_MODE_ARG(adj));
	DRM_DEBUG_KMS("lm %d rm %d tm %d bm %d\n", lm, rm, पंचांग, bm);

	/* Now compute the भागider क्रम real */
	dcrtc->variant->compute_घड़ी(dcrtc, adj, &sclk);

	armada_reg_queue_set(regs, i, sclk, LCD_CFG_SCLK_DIV);

	spin_lock_irqsave(&dcrtc->irq_lock, flags);

	dcrtc->पूर्णांकerlaced = पूर्णांकerlaced;
	/* Even पूर्णांकerlaced/progressive frame */
	dcrtc->v[1].spu_v_h_total = adj->crtc_vtotal << 16 |
				    adj->crtc_htotal;
	dcrtc->v[1].spu_v_porch = पंचांग << 16 | bm;
	val = adj->crtc_hsync_start;
	dcrtc->v[1].spu_adv_reg = val << 20 | val | ADV_VSYNCOFFEN;

	अगर (पूर्णांकerlaced) अणु
		/* Odd पूर्णांकerlaced frame */
		val -= adj->crtc_htotal / 2;
		dcrtc->v[0].spu_adv_reg = val << 20 | val | ADV_VSYNCOFFEN;
		dcrtc->v[0].spu_v_h_total = dcrtc->v[1].spu_v_h_total +
						(1 << 16);
		dcrtc->v[0].spu_v_porch = dcrtc->v[1].spu_v_porch + 1;
	पूर्ण अन्यथा अणु
		dcrtc->v[0] = dcrtc->v[1];
	पूर्ण

	val = adj->crtc_vdisplay << 16 | adj->crtc_hdisplay;

	armada_reg_queue_set(regs, i, val, LCD_SPU_V_H_ACTIVE);
	armada_reg_queue_set(regs, i, (lm << 16) | rm, LCD_SPU_H_PORCH);
	armada_reg_queue_set(regs, i, dcrtc->v[0].spu_v_porch, LCD_SPU_V_PORCH);
	armada_reg_queue_set(regs, i, dcrtc->v[0].spu_v_h_total,
			   LCD_SPUT_V_H_TOTAL);

	अगर (dcrtc->variant->has_spu_adv_reg)
		armada_reg_queue_mod(regs, i, dcrtc->v[0].spu_adv_reg,
				     ADV_VSYNC_L_OFF | ADV_VSYNC_H_OFF |
				     ADV_VSYNCOFFEN, LCD_SPU_ADV_REG);

	val = adj->flags & DRM_MODE_FLAG_NVSYNC ? CFG_VSYNC_INV : 0;
	armada_reg_queue_mod(regs, i, val, CFG_VSYNC_INV, LCD_SPU_DMA_CTRL1);

	/*
	 * The करोcumentation करोesn't indicate what the normal state of
	 * the sync संकेतs are.  Sebastian Hesselbart kindly probed
	 * these संकेतs on his board to determine their state.
	 *
	 * The non-inverted state of the sync संकेतs is active high.
	 * Setting these bits makes the appropriate संकेत active low.
	 */
	val = 0;
	अगर (adj->flags & DRM_MODE_FLAG_NCSYNC)
		val |= CFG_INV_CSYNC;
	अगर (adj->flags & DRM_MODE_FLAG_NHSYNC)
		val |= CFG_INV_HSYNC;
	अगर (adj->flags & DRM_MODE_FLAG_NVSYNC)
		val |= CFG_INV_VSYNC;
	armada_reg_queue_mod(regs, i, val, CFG_INV_CSYNC | CFG_INV_HSYNC |
			     CFG_INV_VSYNC, LCD_SPU_DUMB_CTRL);
	armada_reg_queue_end(regs, i);

	armada_drm_crtc_update_regs(dcrtc, regs);
	spin_unlock_irqrestore(&dcrtc->irq_lock, flags);
पूर्ण

अटल पूर्णांक armada_drm_crtc_atomic_check(काष्ठा drm_crtc *crtc,
					काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_crtc_state *crtc_state = drm_atomic_get_new_crtc_state(state,
									  crtc);
	DRM_DEBUG_KMS("[CRTC:%d:%s]\n", crtc->base.id, crtc->name);

	अगर (crtc_state->gamma_lut && drm_color_lut_size(crtc_state->gamma_lut) != 256)
		वापस -EINVAL;

	अगर (crtc_state->color_mgmt_changed)
		crtc_state->planes_changed = true;

	वापस 0;
पूर्ण

अटल व्योम armada_drm_crtc_atomic_begin(काष्ठा drm_crtc *crtc,
					 काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_crtc_state *crtc_state = drm_atomic_get_new_crtc_state(state,
									  crtc);
	काष्ठा armada_crtc *dcrtc = drm_to_armada_crtc(crtc);

	DRM_DEBUG_KMS("[CRTC:%d:%s]\n", crtc->base.id, crtc->name);

	अगर (crtc_state->color_mgmt_changed)
		armada_drm_update_gamma(crtc);

	dcrtc->regs_idx = 0;
	dcrtc->regs = dcrtc->atomic_regs;
पूर्ण

अटल व्योम armada_drm_crtc_atomic_flush(काष्ठा drm_crtc *crtc,
					 काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_crtc_state *crtc_state = drm_atomic_get_new_crtc_state(state,
									  crtc);
	काष्ठा armada_crtc *dcrtc = drm_to_armada_crtc(crtc);

	DRM_DEBUG_KMS("[CRTC:%d:%s]\n", crtc->base.id, crtc->name);

	armada_reg_queue_end(dcrtc->regs, dcrtc->regs_idx);

	/*
	 * If we aren't करोing a full modeset, then we need to queue
	 * the event here.
	 */
	अगर (!drm_atomic_crtc_needs_modeset(crtc_state)) अणु
		dcrtc->update_pending = true;
		armada_drm_crtc_queue_state_event(crtc);
		spin_lock_irq(&dcrtc->irq_lock);
		armada_drm_crtc_enable_irq(dcrtc, DUMB_FRAMEDONE_ENA);
		spin_unlock_irq(&dcrtc->irq_lock);
	पूर्ण अन्यथा अणु
		spin_lock_irq(&dcrtc->irq_lock);
		armada_drm_crtc_update_regs(dcrtc, dcrtc->regs);
		spin_unlock_irq(&dcrtc->irq_lock);
	पूर्ण
पूर्ण

अटल व्योम armada_drm_crtc_atomic_disable(काष्ठा drm_crtc *crtc,
					   काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_crtc_state *old_state = drm_atomic_get_old_crtc_state(state,
									 crtc);
	काष्ठा armada_crtc *dcrtc = drm_to_armada_crtc(crtc);
	काष्ठा drm_pending_vblank_event *event;

	DRM_DEBUG_KMS("[CRTC:%d:%s]\n", crtc->base.id, crtc->name);

	अगर (old_state->adjusted_mode.flags & DRM_MODE_FLAG_INTERLACE)
		drm_crtc_vblank_put(crtc);

	drm_crtc_vblank_off(crtc);
	armada_drm_crtc_update(dcrtc, false);

	अगर (!crtc->state->active) अणु
		/*
		 * This modeset will be leaving the CRTC disabled, so
		 * call the backend to disable upstream घड़ीs etc.
		 */
		अगर (dcrtc->variant->disable)
			dcrtc->variant->disable(dcrtc);

		/*
		 * We will not receive any further vblank events.
		 * Send the flip_करोne event manually.
		 */
		event = crtc->state->event;
		crtc->state->event = शून्य;
		अगर (event) अणु
			spin_lock_irq(&crtc->dev->event_lock);
			drm_crtc_send_vblank_event(crtc, event);
			spin_unlock_irq(&crtc->dev->event_lock);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम armada_drm_crtc_atomic_enable(काष्ठा drm_crtc *crtc,
					  काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_crtc_state *old_state = drm_atomic_get_old_crtc_state(state,
									 crtc);
	काष्ठा armada_crtc *dcrtc = drm_to_armada_crtc(crtc);

	DRM_DEBUG_KMS("[CRTC:%d:%s]\n", crtc->base.id, crtc->name);

	अगर (!old_state->active) अणु
		/*
		 * This modeset is enabling the CRTC after it having
		 * been disabled.  Reverse the call to ->disable in
		 * the atomic_disable().
		 */
		अगर (dcrtc->variant->enable)
			dcrtc->variant->enable(dcrtc, &crtc->state->adjusted_mode);
	पूर्ण
	armada_drm_crtc_update(dcrtc, true);
	drm_crtc_vblank_on(crtc);

	अगर (crtc->state->adjusted_mode.flags & DRM_MODE_FLAG_INTERLACE)
		WARN_ON(drm_crtc_vblank_get(crtc));

	armada_drm_crtc_queue_state_event(crtc);
पूर्ण

अटल स्थिर काष्ठा drm_crtc_helper_funcs armada_crtc_helper_funcs = अणु
	.mode_valid	= armada_drm_crtc_mode_valid,
	.mode_fixup	= armada_drm_crtc_mode_fixup,
	.mode_set_nofb	= armada_drm_crtc_mode_set_nofb,
	.atomic_check	= armada_drm_crtc_atomic_check,
	.atomic_begin	= armada_drm_crtc_atomic_begin,
	.atomic_flush	= armada_drm_crtc_atomic_flush,
	.atomic_disable	= armada_drm_crtc_atomic_disable,
	.atomic_enable	= armada_drm_crtc_atomic_enable,
पूर्ण;

अटल व्योम armada_load_cursor_argb(व्योम __iomem *base, uपूर्णांक32_t *pix,
	अचिन्हित stride, अचिन्हित width, अचिन्हित height)
अणु
	uपूर्णांक32_t addr;
	अचिन्हित y;

	addr = SRAM_HWC32_RAM1;
	क्रम (y = 0; y < height; y++) अणु
		uपूर्णांक32_t *p = &pix[y * stride];
		अचिन्हित x;

		क्रम (x = 0; x < width; x++, p++) अणु
			uपूर्णांक32_t val = *p;

			/*
			 * In "ARGB888" (HWC32) mode, writing to the SRAM
			 * requires these bits to contain:
			 * 31:24 = alpha 23:16 = blue 15:8 = green 7:0 = red
			 * So, it's actually ABGR8888.  This is independent
			 * of the SWAPRB bits in DMA control रेजिस्टर 0.
			 */
			val = (val & 0xff00ff00) |
			      (val & 0x000000ff) << 16 |
			      (val & 0x00ff0000) >> 16;

			ग_लिखोl_relaxed(val,
				       base + LCD_SPU_SRAM_WRDAT);
			ग_लिखोl_relaxed(addr | SRAM_WRITE,
				       base + LCD_SPU_SRAM_CTRL);
			पढ़ोl_relaxed(base + LCD_SPU_HWC_OVSA_HPXL_VLN);
			addr += 1;
			अगर ((addr & 0x00ff) == 0)
				addr += 0xf00;
			अगर ((addr & 0x30ff) == 0)
				addr = SRAM_HWC32_RAM2;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम armada_drm_crtc_cursor_tran(व्योम __iomem *base)
अणु
	अचिन्हित addr;

	क्रम (addr = 0; addr < 256; addr++) अणु
		/* ग_लिखो the शेष value */
		ग_लिखोl_relaxed(0x55555555, base + LCD_SPU_SRAM_WRDAT);
		ग_लिखोl_relaxed(addr | SRAM_WRITE | SRAM_HWC32_TRAN,
			       base + LCD_SPU_SRAM_CTRL);
	पूर्ण
पूर्ण

अटल पूर्णांक armada_drm_crtc_cursor_update(काष्ठा armada_crtc *dcrtc, bool reload)
अणु
	uपूर्णांक32_t xoff, xscr, w = dcrtc->cursor_w, s;
	uपूर्णांक32_t yoff, yscr, h = dcrtc->cursor_h;
	uपूर्णांक32_t para1;

	/*
	 * Calculate the visible width and height of the cursor,
	 * screen position, and the position in the cursor biपंचांगap.
	 */
	अगर (dcrtc->cursor_x < 0) अणु
		xoff = -dcrtc->cursor_x;
		xscr = 0;
		w -= min(xoff, w);
	पूर्ण अन्यथा अगर (dcrtc->cursor_x + w > dcrtc->crtc.mode.hdisplay) अणु
		xoff = 0;
		xscr = dcrtc->cursor_x;
		w = max_t(पूर्णांक, dcrtc->crtc.mode.hdisplay - dcrtc->cursor_x, 0);
	पूर्ण अन्यथा अणु
		xoff = 0;
		xscr = dcrtc->cursor_x;
	पूर्ण

	अगर (dcrtc->cursor_y < 0) अणु
		yoff = -dcrtc->cursor_y;
		yscr = 0;
		h -= min(yoff, h);
	पूर्ण अन्यथा अगर (dcrtc->cursor_y + h > dcrtc->crtc.mode.vdisplay) अणु
		yoff = 0;
		yscr = dcrtc->cursor_y;
		h = max_t(पूर्णांक, dcrtc->crtc.mode.vdisplay - dcrtc->cursor_y, 0);
	पूर्ण अन्यथा अणु
		yoff = 0;
		yscr = dcrtc->cursor_y;
	पूर्ण

	/* On पूर्णांकerlaced modes, the vertical cursor size must be halved */
	s = dcrtc->cursor_w;
	अगर (dcrtc->पूर्णांकerlaced) अणु
		s *= 2;
		yscr /= 2;
		h /= 2;
	पूर्ण

	अगर (!dcrtc->cursor_obj || !h || !w) अणु
		spin_lock_irq(&dcrtc->irq_lock);
		dcrtc->cursor_update = false;
		armada_updatel(0, CFG_HWC_ENA, dcrtc->base + LCD_SPU_DMA_CTRL0);
		spin_unlock_irq(&dcrtc->irq_lock);
		वापस 0;
	पूर्ण

	spin_lock_irq(&dcrtc->irq_lock);
	para1 = पढ़ोl_relaxed(dcrtc->base + LCD_SPU_SRAM_PARA1);
	armada_updatel(CFG_CSB_256x32, CFG_CSB_256x32 | CFG_PDWN256x32,
		       dcrtc->base + LCD_SPU_SRAM_PARA1);
	spin_unlock_irq(&dcrtc->irq_lock);

	/*
	 * Initialize the transparency अगर the SRAM was घातered करोwn.
	 * We must also reload the cursor data as well.
	 */
	अगर (!(para1 & CFG_CSB_256x32)) अणु
		armada_drm_crtc_cursor_tran(dcrtc->base);
		reload = true;
	पूर्ण

	अगर (dcrtc->cursor_hw_sz != (h << 16 | w)) अणु
		spin_lock_irq(&dcrtc->irq_lock);
		dcrtc->cursor_update = false;
		armada_updatel(0, CFG_HWC_ENA, dcrtc->base + LCD_SPU_DMA_CTRL0);
		spin_unlock_irq(&dcrtc->irq_lock);
		reload = true;
	पूर्ण
	अगर (reload) अणु
		काष्ठा armada_gem_object *obj = dcrtc->cursor_obj;
		uपूर्णांक32_t *pix;
		/* Set the top-left corner of the cursor image */
		pix = obj->addr;
		pix += yoff * s + xoff;
		armada_load_cursor_argb(dcrtc->base, pix, s, w, h);
	पूर्ण

	/* Reload the cursor position, size and enable in the IRQ handler */
	spin_lock_irq(&dcrtc->irq_lock);
	dcrtc->cursor_hw_pos = yscr << 16 | xscr;
	dcrtc->cursor_hw_sz = h << 16 | w;
	dcrtc->cursor_update = true;
	armada_drm_crtc_enable_irq(dcrtc, DUMB_FRAMEDONE_ENA);
	spin_unlock_irq(&dcrtc->irq_lock);

	वापस 0;
पूर्ण

अटल व्योम cursor_update(व्योम *data)
अणु
	armada_drm_crtc_cursor_update(data, true);
पूर्ण

अटल पूर्णांक armada_drm_crtc_cursor_set(काष्ठा drm_crtc *crtc,
	काष्ठा drm_file *file, uपूर्णांक32_t handle, uपूर्णांक32_t w, uपूर्णांक32_t h)
अणु
	काष्ठा armada_crtc *dcrtc = drm_to_armada_crtc(crtc);
	काष्ठा armada_gem_object *obj = शून्य;
	पूर्णांक ret;

	/* If no cursor support, replicate drm's वापस value */
	अगर (!dcrtc->variant->has_spu_adv_reg)
		वापस -ENXIO;

	अगर (handle && w > 0 && h > 0) अणु
		/* maximum size is 64x32 or 32x64 */
		अगर (w > 64 || h > 64 || (w > 32 && h > 32))
			वापस -ENOMEM;

		obj = armada_gem_object_lookup(file, handle);
		अगर (!obj)
			वापस -ENOENT;

		/* Must be a kernel-mapped object */
		अगर (!obj->addr) अणु
			drm_gem_object_put(&obj->obj);
			वापस -EINVAL;
		पूर्ण

		अगर (obj->obj.size < w * h * 4) अणु
			DRM_ERROR("buffer is too small\n");
			drm_gem_object_put(&obj->obj);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	अगर (dcrtc->cursor_obj) अणु
		dcrtc->cursor_obj->update = शून्य;
		dcrtc->cursor_obj->update_data = शून्य;
		drm_gem_object_put(&dcrtc->cursor_obj->obj);
	पूर्ण
	dcrtc->cursor_obj = obj;
	dcrtc->cursor_w = w;
	dcrtc->cursor_h = h;
	ret = armada_drm_crtc_cursor_update(dcrtc, true);
	अगर (obj) अणु
		obj->update_data = dcrtc;
		obj->update = cursor_update;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक armada_drm_crtc_cursor_move(काष्ठा drm_crtc *crtc, पूर्णांक x, पूर्णांक y)
अणु
	काष्ठा armada_crtc *dcrtc = drm_to_armada_crtc(crtc);
	पूर्णांक ret;

	/* If no cursor support, replicate drm's वापस value */
	अगर (!dcrtc->variant->has_spu_adv_reg)
		वापस -EFAULT;

	dcrtc->cursor_x = x;
	dcrtc->cursor_y = y;
	ret = armada_drm_crtc_cursor_update(dcrtc, false);

	वापस ret;
पूर्ण

अटल व्योम armada_drm_crtc_destroy(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा armada_crtc *dcrtc = drm_to_armada_crtc(crtc);
	काष्ठा armada_निजी *priv = drm_to_armada_dev(crtc->dev);

	अगर (dcrtc->cursor_obj)
		drm_gem_object_put(&dcrtc->cursor_obj->obj);

	priv->dcrtc[dcrtc->num] = शून्य;
	drm_crtc_cleanup(&dcrtc->crtc);

	अगर (dcrtc->variant->disable)
		dcrtc->variant->disable(dcrtc);

	ग_लिखोl_relaxed(0, dcrtc->base + LCD_SPU_IRQ_ENA);

	of_node_put(dcrtc->crtc.port);

	kमुक्त(dcrtc);
पूर्ण

अटल पूर्णांक armada_drm_crtc_late_रेजिस्टर(काष्ठा drm_crtc *crtc)
अणु
	अगर (IS_ENABLED(CONFIG_DEBUG_FS))
		armada_drm_crtc_debugfs_init(drm_to_armada_crtc(crtc));

	वापस 0;
पूर्ण

/* These are called under the vbl_lock. */
अटल पूर्णांक armada_drm_crtc_enable_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा armada_crtc *dcrtc = drm_to_armada_crtc(crtc);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dcrtc->irq_lock, flags);
	armada_drm_crtc_enable_irq(dcrtc, VSYNC_IRQ_ENA);
	spin_unlock_irqrestore(&dcrtc->irq_lock, flags);
	वापस 0;
पूर्ण

अटल व्योम armada_drm_crtc_disable_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा armada_crtc *dcrtc = drm_to_armada_crtc(crtc);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dcrtc->irq_lock, flags);
	armada_drm_crtc_disable_irq(dcrtc, VSYNC_IRQ_ENA);
	spin_unlock_irqrestore(&dcrtc->irq_lock, flags);
पूर्ण

अटल स्थिर काष्ठा drm_crtc_funcs armada_crtc_funcs = अणु
	.reset		= drm_atomic_helper_crtc_reset,
	.cursor_set	= armada_drm_crtc_cursor_set,
	.cursor_move	= armada_drm_crtc_cursor_move,
	.destroy	= armada_drm_crtc_destroy,
	.set_config	= drm_atomic_helper_set_config,
	.page_flip	= drm_atomic_helper_page_flip,
	.atomic_duplicate_state = drm_atomic_helper_crtc_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_crtc_destroy_state,
	.late_रेजिस्टर	= armada_drm_crtc_late_रेजिस्टर,
	.enable_vblank	= armada_drm_crtc_enable_vblank,
	.disable_vblank	= armada_drm_crtc_disable_vblank,
पूर्ण;

पूर्णांक armada_crtc_select_घड़ी(काष्ठा armada_crtc *dcrtc,
			     काष्ठा armada_clk_result *res,
			     स्थिर काष्ठा armada_घड़ीing_params *params,
			     काष्ठा clk *clks[], माप_प्रकार num_clks,
			     अचिन्हित दीर्घ desired_khz)
अणु
	अचिन्हित दीर्घ desired_hz = desired_khz * 1000;
	अचिन्हित दीर्घ desired_clk_hz;	// requested clk input
	अचिन्हित दीर्घ real_clk_hz;	// actual clk input
	अचिन्हित दीर्घ real_hz;		// actual pixel clk
	अचिन्हित दीर्घ permillage;
	काष्ठा clk *clk;
	u32 भाग;
	पूर्णांक i;

	DRM_DEBUG_KMS("[CRTC:%u:%s] desired clock=%luHz\n",
		      dcrtc->crtc.base.id, dcrtc->crtc.name, desired_hz);

	क्रम (i = 0; i < num_clks; i++) अणु
		clk = clks[i];
		अगर (!clk)
			जारी;

		अगर (params->settable & BIT(i)) अणु
			real_clk_hz = clk_round_rate(clk, desired_hz);
			desired_clk_hz = desired_hz;
		पूर्ण अन्यथा अणु
			real_clk_hz = clk_get_rate(clk);
			desired_clk_hz = real_clk_hz;
		पूर्ण

		/* If the घड़ी can करो exactly the desired rate, we're करोne */
		अगर (real_clk_hz == desired_hz) अणु
			real_hz = real_clk_hz;
			भाग = 1;
			जाओ found;
		पूर्ण

		/* Calculate the भागider - अगर invalid, we can't करो this rate */
		भाग = DIV_ROUND_CLOSEST(real_clk_hz, desired_hz);
		अगर (भाग == 0 || भाग > params->भाग_max)
			जारी;

		/* Calculate the actual rate - HDMI requires -0.6%..+0.5% */
		real_hz = DIV_ROUND_CLOSEST(real_clk_hz, भाग);

		DRM_DEBUG_KMS("[CRTC:%u:%s] clk=%u %luHz div=%u real=%luHz\n",
			dcrtc->crtc.base.id, dcrtc->crtc.name,
			i, real_clk_hz, भाग, real_hz);

		/* Aव्योम repeated भागision */
		अगर (real_hz < desired_hz) अणु
			permillage = real_hz / desired_khz;
			अगर (permillage < params->permillage_min)
				जारी;
		पूर्ण अन्यथा अणु
			permillage = DIV_ROUND_UP(real_hz, desired_khz);
			अगर (permillage > params->permillage_max)
				जारी;
		पूर्ण
		जाओ found;
	पूर्ण

	वापस -दुस्फल;

found:
	DRM_DEBUG_KMS("[CRTC:%u:%s] selected clk=%u %luHz div=%u real=%luHz\n",
		dcrtc->crtc.base.id, dcrtc->crtc.name,
		i, real_clk_hz, भाग, real_hz);

	res->desired_clk_hz = desired_clk_hz;
	res->clk = clk;
	res->भाग = भाग;

	वापस i;
पूर्ण

अटल पूर्णांक armada_drm_crtc_create(काष्ठा drm_device *drm, काष्ठा device *dev,
	काष्ठा resource *res, पूर्णांक irq, स्थिर काष्ठा armada_variant *variant,
	काष्ठा device_node *port)
अणु
	काष्ठा armada_निजी *priv = drm_to_armada_dev(drm);
	काष्ठा armada_crtc *dcrtc;
	काष्ठा drm_plane *primary;
	व्योम __iomem *base;
	पूर्णांक ret;

	base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	dcrtc = kzalloc(माप(*dcrtc), GFP_KERNEL);
	अगर (!dcrtc) अणु
		DRM_ERROR("failed to allocate Armada crtc\n");
		वापस -ENOMEM;
	पूर्ण

	अगर (dev != drm->dev)
		dev_set_drvdata(dev, dcrtc);

	dcrtc->variant = variant;
	dcrtc->base = base;
	dcrtc->num = drm->mode_config.num_crtc;
	dcrtc->cfg_dumb_ctrl = DUMB24_RGB888_0;
	dcrtc->spu_iopad_ctrl = CFG_VSCALE_LN_EN | CFG_IOPAD_DUMB24;
	spin_lock_init(&dcrtc->irq_lock);
	dcrtc->irq_ena = CLEAN_SPU_IRQ_ISR;

	/* Initialize some रेजिस्टरs which we करोn't otherwise set */
	ग_लिखोl_relaxed(0x00000001, dcrtc->base + LCD_CFG_SCLK_DIV);
	ग_लिखोl_relaxed(0x00000000, dcrtc->base + LCD_SPU_BLANKCOLOR);
	ग_लिखोl_relaxed(dcrtc->spu_iopad_ctrl,
		       dcrtc->base + LCD_SPU_IOPAD_CONTROL);
	ग_लिखोl_relaxed(0x00000000, dcrtc->base + LCD_SPU_SRAM_PARA0);
	ग_लिखोl_relaxed(CFG_PDWN256x32 | CFG_PDWN256x24 | CFG_PDWN256x8 |
		       CFG_PDWN32x32 | CFG_PDWN16x66 | CFG_PDWN32x66 |
		       CFG_PDWN64x66, dcrtc->base + LCD_SPU_SRAM_PARA1);
	ग_लिखोl_relaxed(0x2032ff81, dcrtc->base + LCD_SPU_DMA_CTRL1);
	ग_लिखोl_relaxed(dcrtc->irq_ena, dcrtc->base + LCD_SPU_IRQ_ENA);
	पढ़ोl_relaxed(dcrtc->base + LCD_SPU_IRQ_ISR);
	ग_लिखोl_relaxed(0, dcrtc->base + LCD_SPU_IRQ_ISR);

	ret = devm_request_irq(dev, irq, armada_drm_irq, 0, "armada_drm_crtc",
			       dcrtc);
	अगर (ret < 0)
		जाओ err_crtc;

	अगर (dcrtc->variant->init) अणु
		ret = dcrtc->variant->init(dcrtc, dev);
		अगर (ret)
			जाओ err_crtc;
	पूर्ण

	/* Ensure AXI pipeline is enabled */
	armada_updatel(CFG_ARBFAST_ENA, 0, dcrtc->base + LCD_SPU_DMA_CTRL0);

	priv->dcrtc[dcrtc->num] = dcrtc;

	dcrtc->crtc.port = port;

	primary = kzalloc(माप(*primary), GFP_KERNEL);
	अगर (!primary) अणु
		ret = -ENOMEM;
		जाओ err_crtc;
	पूर्ण

	ret = armada_drm_primary_plane_init(drm, primary);
	अगर (ret) अणु
		kमुक्त(primary);
		जाओ err_crtc;
	पूर्ण

	ret = drm_crtc_init_with_planes(drm, &dcrtc->crtc, primary, शून्य,
					&armada_crtc_funcs, शून्य);
	अगर (ret)
		जाओ err_crtc_init;

	drm_crtc_helper_add(&dcrtc->crtc, &armada_crtc_helper_funcs);

	ret = drm_mode_crtc_set_gamma_size(&dcrtc->crtc, 256);
	अगर (ret)
		वापस ret;

	drm_crtc_enable_color_mgmt(&dcrtc->crtc, 0, false, 256);

	वापस armada_overlay_plane_create(drm, 1 << dcrtc->num);

err_crtc_init:
	primary->funcs->destroy(primary);
err_crtc:
	kमुक्त(dcrtc);

	वापस ret;
पूर्ण

अटल पूर्णांक
armada_lcd_bind(काष्ठा device *dev, काष्ठा device *master, व्योम *data)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा drm_device *drm = data;
	काष्ठा resource *res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	पूर्णांक irq = platक्रमm_get_irq(pdev, 0);
	स्थिर काष्ठा armada_variant *variant;
	काष्ठा device_node *port = शून्य;

	अगर (irq < 0)
		वापस irq;

	अगर (!dev->of_node) अणु
		स्थिर काष्ठा platक्रमm_device_id *id;

		id = platक्रमm_get_device_id(pdev);
		अगर (!id)
			वापस -ENXIO;

		variant = (स्थिर काष्ठा armada_variant *)id->driver_data;
	पूर्ण अन्यथा अणु
		स्थिर काष्ठा of_device_id *match;
		काष्ठा device_node *np, *parent = dev->of_node;

		match = of_match_device(dev->driver->of_match_table, dev);
		अगर (!match)
			वापस -ENXIO;

		np = of_get_child_by_name(parent, "ports");
		अगर (np)
			parent = np;
		port = of_get_child_by_name(parent, "port");
		of_node_put(np);
		अगर (!port) अणु
			dev_err(dev, "no port node found in %pOF\n", parent);
			वापस -ENXIO;
		पूर्ण

		variant = match->data;
	पूर्ण

	वापस armada_drm_crtc_create(drm, dev, res, irq, variant, port);
पूर्ण

अटल व्योम
armada_lcd_unbind(काष्ठा device *dev, काष्ठा device *master, व्योम *data)
अणु
	काष्ठा armada_crtc *dcrtc = dev_get_drvdata(dev);

	armada_drm_crtc_destroy(&dcrtc->crtc);
पूर्ण

अटल स्थिर काष्ठा component_ops armada_lcd_ops = अणु
	.bind = armada_lcd_bind,
	.unbind = armada_lcd_unbind,
पूर्ण;

अटल पूर्णांक armada_lcd_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस component_add(&pdev->dev, &armada_lcd_ops);
पूर्ण

अटल पूर्णांक armada_lcd_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	component_del(&pdev->dev, &armada_lcd_ops);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id armada_lcd_of_match[] = अणु
	अणु
		.compatible	= "marvell,dove-lcd",
		.data		= &armada510_ops,
	पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, armada_lcd_of_match);

अटल स्थिर काष्ठा platक्रमm_device_id armada_lcd_platक्रमm_ids[] = अणु
	अणु
		.name		= "armada-lcd",
		.driver_data	= (अचिन्हित दीर्घ)&armada510_ops,
	पूर्ण, अणु
		.name		= "armada-510-lcd",
		.driver_data	= (अचिन्हित दीर्घ)&armada510_ops,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, armada_lcd_platक्रमm_ids);

काष्ठा platक्रमm_driver armada_lcd_platक्रमm_driver = अणु
	.probe	= armada_lcd_probe,
	.हटाओ	= armada_lcd_हटाओ,
	.driver = अणु
		.name	= "armada-lcd",
		.owner	=  THIS_MODULE,
		.of_match_table = armada_lcd_of_match,
	पूर्ण,
	.id_table = armada_lcd_platक्रमm_ids,
पूर्ण;
