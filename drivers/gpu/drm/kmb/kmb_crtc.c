<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright तऊ 2018-2020 Intel Corporation
 */

#समावेश <linux/clk.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_crtc_helper.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_vblank.h>
#समावेश <drm/drm_modeset_helper_vtables.h>

#समावेश "kmb_drv.h"
#समावेश "kmb_dsi.h"
#समावेश "kmb_plane.h"
#समावेश "kmb_regs.h"

काष्ठा kmb_crtc_timing अणु
	u32 vfront_porch;
	u32 vback_porch;
	u32 vsync_len;
	u32 hfront_porch;
	u32 hback_porch;
	u32 hsync_len;
पूर्ण;

अटल पूर्णांक kmb_crtc_enable_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा kmb_drm_निजी *kmb = to_kmb(dev);

	/* Clear पूर्णांकerrupt */
	kmb_ग_लिखो_lcd(kmb, LCD_INT_CLEAR, LCD_INT_VERT_COMP);
	/* Set which पूर्णांकerval to generate vertical पूर्णांकerrupt */
	kmb_ग_लिखो_lcd(kmb, LCD_VSTATUS_COMPARE,
		      LCD_VSTATUS_COMPARE_VSYNC);
	/* Enable vertical पूर्णांकerrupt */
	kmb_set_biपंचांगask_lcd(kmb, LCD_INT_ENABLE,
			    LCD_INT_VERT_COMP);
	वापस 0;
पूर्ण

अटल व्योम kmb_crtc_disable_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा kmb_drm_निजी *kmb = to_kmb(dev);

	/* Clear पूर्णांकerrupt */
	kmb_ग_लिखो_lcd(kmb, LCD_INT_CLEAR, LCD_INT_VERT_COMP);
	/* Disable vertical पूर्णांकerrupt */
	kmb_clr_biपंचांगask_lcd(kmb, LCD_INT_ENABLE,
			    LCD_INT_VERT_COMP);
पूर्ण

अटल स्थिर काष्ठा drm_crtc_funcs kmb_crtc_funcs = अणु
	.destroy = drm_crtc_cleanup,
	.set_config = drm_atomic_helper_set_config,
	.page_flip = drm_atomic_helper_page_flip,
	.reset = drm_atomic_helper_crtc_reset,
	.atomic_duplicate_state = drm_atomic_helper_crtc_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_crtc_destroy_state,
	.enable_vblank = kmb_crtc_enable_vblank,
	.disable_vblank = kmb_crtc_disable_vblank,
पूर्ण;

अटल व्योम kmb_crtc_set_mode(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा drm_display_mode *m = &crtc->state->adjusted_mode;
	काष्ठा kmb_crtc_timing vm;
	काष्ठा kmb_drm_निजी *kmb = to_kmb(dev);
	अचिन्हित पूर्णांक val = 0;

	/* Initialize mipi */
	kmb_dsi_mode_set(kmb->kmb_dsi, m, kmb->sys_clk_mhz);
	drm_info(dev,
		 "vfp= %d vbp= %d vsync_len=%d hfp=%d hbp=%d hsync_len=%d\n",
		 m->crtc_vsync_start - m->crtc_vdisplay,
		 m->crtc_vtotal - m->crtc_vsync_end,
		 m->crtc_vsync_end - m->crtc_vsync_start,
		 m->crtc_hsync_start - m->crtc_hdisplay,
		 m->crtc_htotal - m->crtc_hsync_end,
		 m->crtc_hsync_end - m->crtc_hsync_start);
	val = kmb_पढ़ो_lcd(kmb, LCD_INT_ENABLE);
	kmb_clr_biपंचांगask_lcd(kmb, LCD_INT_ENABLE, val);
	kmb_set_biपंचांगask_lcd(kmb, LCD_INT_CLEAR, ~0x0);
	vm.vfront_porch = 2;
	vm.vback_porch = 2;
	vm.vsync_len = 8;
	vm.hfront_porch = 0;
	vm.hback_porch = 0;
	vm.hsync_len = 28;

	drm_dbg(dev, "%s : %dactive height= %d vbp=%d vfp=%d vsync-w=%d h-active=%d h-bp=%d h-fp=%d hsync-l=%d",
		__func__, __LINE__,
			m->crtc_vdisplay, vm.vback_porch, vm.vfront_porch,
			vm.vsync_len, m->crtc_hdisplay, vm.hback_porch,
			vm.hfront_porch, vm.hsync_len);
	kmb_ग_लिखो_lcd(kmb, LCD_V_ACTIVEHEIGHT,
		      m->crtc_vdisplay - 1);
	kmb_ग_लिखो_lcd(kmb, LCD_V_BACKPORCH, vm.vback_porch);
	kmb_ग_लिखो_lcd(kmb, LCD_V_FRONTPORCH, vm.vfront_porch);
	kmb_ग_लिखो_lcd(kmb, LCD_VSYNC_WIDTH, vm.vsync_len - 1);
	kmb_ग_लिखो_lcd(kmb, LCD_H_ACTIVEWIDTH,
		      m->crtc_hdisplay - 1);
	kmb_ग_लिखो_lcd(kmb, LCD_H_BACKPORCH, vm.hback_porch);
	kmb_ग_लिखो_lcd(kmb, LCD_H_FRONTPORCH, vm.hfront_porch);
	kmb_ग_लिखो_lcd(kmb, LCD_HSYNC_WIDTH, vm.hsync_len - 1);
	/* This is hardcoded as 0 in the Myriadx code */
	kmb_ग_लिखो_lcd(kmb, LCD_VSYNC_START, 0);
	kmb_ग_लिखो_lcd(kmb, LCD_VSYNC_END, 0);
	/* Back ground color */
	kmb_ग_लिखो_lcd(kmb, LCD_BG_COLOUR_LS, 0x4);
	अगर (m->flags == DRM_MODE_FLAG_INTERLACE) अणु
		kmb_ग_लिखो_lcd(kmb,
			      LCD_VSYNC_WIDTH_EVEN, vm.vsync_len - 1);
		kmb_ग_लिखो_lcd(kmb,
			      LCD_V_BACKPORCH_EVEN, vm.vback_porch);
		kmb_ग_लिखो_lcd(kmb,
			      LCD_V_FRONTPORCH_EVEN, vm.vfront_porch);
		kmb_ग_लिखो_lcd(kmb, LCD_V_ACTIVEHEIGHT_EVEN,
			      m->crtc_vdisplay - 1);
		/* This is hardcoded as 10 in the Myriadx code */
		kmb_ग_लिखो_lcd(kmb, LCD_VSYNC_START_EVEN, 10);
		kmb_ग_लिखो_lcd(kmb, LCD_VSYNC_END_EVEN, 10);
	पूर्ण
	kmb_ग_लिखो_lcd(kmb, LCD_TIMING_GEN_TRIG, 1);
	kmb_set_biपंचांगask_lcd(kmb, LCD_CONTROL, LCD_CTRL_ENABLE);
	kmb_set_biपंचांगask_lcd(kmb, LCD_INT_ENABLE, val);
पूर्ण

अटल व्योम kmb_crtc_atomic_enable(काष्ठा drm_crtc *crtc,
				   काष्ठा drm_atomic_state *state)
अणु
	काष्ठा kmb_drm_निजी *kmb = crtc_to_kmb_priv(crtc);

	clk_prepare_enable(kmb->kmb_clk.clk_lcd);
	kmb_crtc_set_mode(crtc);
	drm_crtc_vblank_on(crtc);
पूर्ण

अटल व्योम kmb_crtc_atomic_disable(काष्ठा drm_crtc *crtc,
				    काष्ठा drm_atomic_state *state)
अणु
	काष्ठा kmb_drm_निजी *kmb = crtc_to_kmb_priv(crtc);
	काष्ठा drm_crtc_state *old_state = drm_atomic_get_old_crtc_state(state, crtc);

	/* due to hw limitations, planes need to be off when crtc is off */
	drm_atomic_helper_disable_planes_on_crtc(old_state, false);

	drm_crtc_vblank_off(crtc);
	clk_disable_unprepare(kmb->kmb_clk.clk_lcd);
पूर्ण

अटल व्योम kmb_crtc_atomic_begin(काष्ठा drm_crtc *crtc,
				  काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा kmb_drm_निजी *kmb = to_kmb(dev);

	kmb_clr_biपंचांगask_lcd(kmb, LCD_INT_ENABLE,
			    LCD_INT_VERT_COMP);
पूर्ण

अटल व्योम kmb_crtc_atomic_flush(काष्ठा drm_crtc *crtc,
				  काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा kmb_drm_निजी *kmb = to_kmb(dev);

	kmb_set_biपंचांगask_lcd(kmb, LCD_INT_ENABLE,
			    LCD_INT_VERT_COMP);

	spin_lock_irq(&crtc->dev->event_lock);
	अगर (crtc->state->event) अणु
		अगर (drm_crtc_vblank_get(crtc) == 0)
			drm_crtc_arm_vblank_event(crtc, crtc->state->event);
		अन्यथा
			drm_crtc_send_vblank_event(crtc, crtc->state->event);
	पूर्ण
	crtc->state->event = शून्य;
	spin_unlock_irq(&crtc->dev->event_lock);
पूर्ण

अटल स्थिर काष्ठा drm_crtc_helper_funcs kmb_crtc_helper_funcs = अणु
	.atomic_begin = kmb_crtc_atomic_begin,
	.atomic_enable = kmb_crtc_atomic_enable,
	.atomic_disable = kmb_crtc_atomic_disable,
	.atomic_flush = kmb_crtc_atomic_flush,
पूर्ण;

पूर्णांक kmb_setup_crtc(काष्ठा drm_device *drm)
अणु
	काष्ठा kmb_drm_निजी *kmb = to_kmb(drm);
	काष्ठा kmb_plane *primary;
	पूर्णांक ret;

	primary = kmb_plane_init(drm);
	अगर (IS_ERR(primary))
		वापस PTR_ERR(primary);

	ret = drm_crtc_init_with_planes(drm, &kmb->crtc, &primary->base_plane,
					शून्य, &kmb_crtc_funcs, शून्य);
	अगर (ret) अणु
		kmb_plane_destroy(&primary->base_plane);
		वापस ret;
	पूर्ण

	drm_crtc_helper_add(&kmb->crtc, &kmb_crtc_helper_funcs);
	वापस 0;
पूर्ण
