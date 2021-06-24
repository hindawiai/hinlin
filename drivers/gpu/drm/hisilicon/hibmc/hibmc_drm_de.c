<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Hisilicon Hibmc SoC drm driver
 *
 * Based on the bochs drm driver.
 *
 * Copyright (c) 2016 Huawei Limited.
 *
 * Author:
 *	Rongrong Zou <zourongrong@huawei.com>
 *	Rongrong Zou <zourongrong@gmail.com>
 *	Jianhua Li <lijianhua@huawei.com>
 */

#समावेश <linux/delay.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_gem_vram_helper.h>
#समावेश <drm/drm_vblank.h>

#समावेश "hibmc_drm_drv.h"
#समावेश "hibmc_drm_regs.h"

काष्ठा hibmc_display_panel_pll अणु
	u64 M;
	u64 N;
	u64 OD;
	u64 POD;
पूर्ण;

काष्ठा hibmc_dislay_pll_config अणु
	u64 hdisplay;
	u64 vdisplay;
	u32 pll1_config_value;
	u32 pll2_config_value;
पूर्ण;

अटल स्थिर काष्ठा hibmc_dislay_pll_config hibmc_pll_table[] = अणु
	अणु640, 480, CRT_PLL1_HS_25MHZ, CRT_PLL2_HS_25MHZपूर्ण,
	अणु800, 600, CRT_PLL1_HS_40MHZ, CRT_PLL2_HS_40MHZपूर्ण,
	अणु1024, 768, CRT_PLL1_HS_65MHZ, CRT_PLL2_HS_65MHZपूर्ण,
	अणु1152, 864, CRT_PLL1_HS_80MHZ_1152, CRT_PLL2_HS_80MHZपूर्ण,
	अणु1280, 768, CRT_PLL1_HS_80MHZ, CRT_PLL2_HS_80MHZपूर्ण,
	अणु1280, 720, CRT_PLL1_HS_74MHZ, CRT_PLL2_HS_74MHZपूर्ण,
	अणु1280, 960, CRT_PLL1_HS_108MHZ, CRT_PLL2_HS_108MHZपूर्ण,
	अणु1280, 1024, CRT_PLL1_HS_108MHZ, CRT_PLL2_HS_108MHZपूर्ण,
	अणु1440, 900, CRT_PLL1_HS_106MHZ, CRT_PLL2_HS_106MHZपूर्ण,
	अणु1600, 900, CRT_PLL1_HS_108MHZ, CRT_PLL2_HS_108MHZपूर्ण,
	अणु1600, 1200, CRT_PLL1_HS_162MHZ, CRT_PLL2_HS_162MHZपूर्ण,
	अणु1920, 1080, CRT_PLL1_HS_148MHZ, CRT_PLL2_HS_148MHZपूर्ण,
	अणु1920, 1200, CRT_PLL1_HS_193MHZ, CRT_PLL2_HS_193MHZपूर्ण,
पूर्ण;

अटल पूर्णांक hibmc_plane_atomic_check(काष्ठा drm_plane *plane,
				    काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *new_plane_state = drm_atomic_get_new_plane_state(state,
										 plane);
	काष्ठा drm_framebuffer *fb = new_plane_state->fb;
	काष्ठा drm_crtc *crtc = new_plane_state->crtc;
	काष्ठा drm_crtc_state *crtc_state;
	u32 src_w = new_plane_state->src_w >> 16;
	u32 src_h = new_plane_state->src_h >> 16;

	अगर (!crtc || !fb)
		वापस 0;

	crtc_state = drm_atomic_get_crtc_state(state, crtc);
	अगर (IS_ERR(crtc_state))
		वापस PTR_ERR(crtc_state);

	अगर (src_w != new_plane_state->crtc_w || src_h != new_plane_state->crtc_h) अणु
		drm_dbg_atomic(plane->dev, "scale not support\n");
		वापस -EINVAL;
	पूर्ण

	अगर (new_plane_state->crtc_x < 0 || new_plane_state->crtc_y < 0) अणु
		drm_dbg_atomic(plane->dev, "crtc_x/y of drm_plane state is invalid\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!crtc_state->enable)
		वापस 0;

	अगर (new_plane_state->crtc_x + new_plane_state->crtc_w >
	    crtc_state->adjusted_mode.hdisplay ||
	    new_plane_state->crtc_y + new_plane_state->crtc_h >
	    crtc_state->adjusted_mode.vdisplay) अणु
		drm_dbg_atomic(plane->dev, "visible portion of plane is invalid\n");
		वापस -EINVAL;
	पूर्ण

	अगर (new_plane_state->fb->pitches[0] % 128 != 0) अणु
		drm_dbg_atomic(plane->dev, "wrong stride with 128-byte aligned\n");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम hibmc_plane_atomic_update(काष्ठा drm_plane *plane,
				      काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *new_state = drm_atomic_get_new_plane_state(state,
									   plane);
	u32 reg;
	s64 gpu_addr = 0;
	u32 line_l;
	काष्ठा hibmc_drm_निजी *priv = to_hibmc_drm_निजी(plane->dev);
	काष्ठा drm_gem_vram_object *gbo;

	अगर (!new_state->fb)
		वापस;

	gbo = drm_gem_vram_of_gem(new_state->fb->obj[0]);

	gpu_addr = drm_gem_vram_offset(gbo);
	अगर (WARN_ON_ONCE(gpu_addr < 0))
		वापस; /* Bug: we didn't pin the BO to VRAM in prepare_fb. */

	ग_लिखोl(gpu_addr, priv->mmio + HIBMC_CRT_FB_ADDRESS);

	reg = new_state->fb->width * (new_state->fb->क्रमmat->cpp[0]);

	line_l = new_state->fb->pitches[0];
	ग_लिखोl(HIBMC_FIELD(HIBMC_CRT_FB_WIDTH_WIDTH, reg) |
	       HIBMC_FIELD(HIBMC_CRT_FB_WIDTH_OFFS, line_l),
	       priv->mmio + HIBMC_CRT_FB_WIDTH);

	/* SET PIXEL FORMAT */
	reg = पढ़ोl(priv->mmio + HIBMC_CRT_DISP_CTL);
	reg &= ~HIBMC_CRT_DISP_CTL_FORMAT_MASK;
	reg |= HIBMC_FIELD(HIBMC_CRT_DISP_CTL_FORMAT,
			   new_state->fb->क्रमmat->cpp[0] * 8 / 16);
	ग_लिखोl(reg, priv->mmio + HIBMC_CRT_DISP_CTL);
पूर्ण

अटल स्थिर u32 channel_क्रमmats1[] = अणु
	DRM_FORMAT_RGB565, DRM_FORMAT_BGR565, DRM_FORMAT_RGB888,
	DRM_FORMAT_BGR888, DRM_FORMAT_XRGB8888, DRM_FORMAT_XBGR8888,
	DRM_FORMAT_RGBA8888, DRM_FORMAT_BGRA8888, DRM_FORMAT_ARGB8888,
	DRM_FORMAT_ABGR8888
पूर्ण;

अटल स्थिर काष्ठा drm_plane_funcs hibmc_plane_funcs = अणु
	.update_plane	= drm_atomic_helper_update_plane,
	.disable_plane	= drm_atomic_helper_disable_plane,
	.destroy = drm_plane_cleanup,
	.reset = drm_atomic_helper_plane_reset,
	.atomic_duplicate_state = drm_atomic_helper_plane_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_plane_destroy_state,
पूर्ण;

अटल स्थिर काष्ठा drm_plane_helper_funcs hibmc_plane_helper_funcs = अणु
	.prepare_fb	= drm_gem_vram_plane_helper_prepare_fb,
	.cleanup_fb	= drm_gem_vram_plane_helper_cleanup_fb,
	.atomic_check = hibmc_plane_atomic_check,
	.atomic_update = hibmc_plane_atomic_update,
पूर्ण;

अटल व्योम hibmc_crtc_dpms(काष्ठा drm_crtc *crtc, u32 dpms)
अणु
	काष्ठा hibmc_drm_निजी *priv = to_hibmc_drm_निजी(crtc->dev);
	u32 reg;

	reg = पढ़ोl(priv->mmio + HIBMC_CRT_DISP_CTL);
	reg &= ~HIBMC_CRT_DISP_CTL_DPMS_MASK;
	reg |= HIBMC_FIELD(HIBMC_CRT_DISP_CTL_DPMS, dpms);
	reg &= ~HIBMC_CRT_DISP_CTL_TIMING_MASK;
	अगर (dpms == HIBMC_CRT_DPMS_ON)
		reg |= HIBMC_CRT_DISP_CTL_TIMING(1);
	ग_लिखोl(reg, priv->mmio + HIBMC_CRT_DISP_CTL);
पूर्ण

अटल व्योम hibmc_crtc_atomic_enable(काष्ठा drm_crtc *crtc,
				     काष्ठा drm_atomic_state *state)
अणु
	u32 reg;
	काष्ठा hibmc_drm_निजी *priv = to_hibmc_drm_निजी(crtc->dev);

	hibmc_set_घातer_mode(priv, HIBMC_PW_MODE_CTL_MODE_MODE0);

	/* Enable display घातer gate & LOCALMEM घातer gate*/
	reg = पढ़ोl(priv->mmio + HIBMC_CURRENT_GATE);
	reg &= ~HIBMC_CURR_GATE_LOCALMEM_MASK;
	reg &= ~HIBMC_CURR_GATE_DISPLAY_MASK;
	reg |= HIBMC_CURR_GATE_LOCALMEM(1);
	reg |= HIBMC_CURR_GATE_DISPLAY(1);
	hibmc_set_current_gate(priv, reg);
	drm_crtc_vblank_on(crtc);
	hibmc_crtc_dpms(crtc, HIBMC_CRT_DPMS_ON);
पूर्ण

अटल व्योम hibmc_crtc_atomic_disable(काष्ठा drm_crtc *crtc,
				      काष्ठा drm_atomic_state *state)
अणु
	u32 reg;
	काष्ठा hibmc_drm_निजी *priv = to_hibmc_drm_निजी(crtc->dev);

	hibmc_crtc_dpms(crtc, HIBMC_CRT_DPMS_OFF);
	drm_crtc_vblank_off(crtc);

	hibmc_set_घातer_mode(priv, HIBMC_PW_MODE_CTL_MODE_SLEEP);

	/* Enable display घातer gate & LOCALMEM घातer gate*/
	reg = पढ़ोl(priv->mmio + HIBMC_CURRENT_GATE);
	reg &= ~HIBMC_CURR_GATE_LOCALMEM_MASK;
	reg &= ~HIBMC_CURR_GATE_DISPLAY_MASK;
	reg |= HIBMC_CURR_GATE_LOCALMEM(0);
	reg |= HIBMC_CURR_GATE_DISPLAY(0);
	hibmc_set_current_gate(priv, reg);
पूर्ण

अटल क्रमागत drm_mode_status
hibmc_crtc_mode_valid(काष्ठा drm_crtc *crtc,
		      स्थिर काष्ठा drm_display_mode *mode)
अणु
	माप_प्रकार i = 0;
	पूर्णांक vrefresh = drm_mode_vrefresh(mode);

	अगर (vrefresh < 59 || vrefresh > 61)
		वापस MODE_NOCLOCK;

	क्रम (i = 0; i < ARRAY_SIZE(hibmc_pll_table); i++) अणु
		अगर (hibmc_pll_table[i].hdisplay == mode->hdisplay &&
		    hibmc_pll_table[i].vdisplay == mode->vdisplay)
			वापस MODE_OK;
	पूर्ण

	वापस MODE_BAD;
पूर्ण

अटल u32 क्रमmat_pll_reg(व्योम)
अणु
	u32 pllreg = 0;
	काष्ठा hibmc_display_panel_pll pll = अणु0पूर्ण;

	/*
	 * Note that all PLL's have the same क्रमmat. Here,
	 * we just use Panel PLL parameter to work out the bit
	 * fields in the रेजिस्टर.On वापसing a 32 bit number, the value can
	 * be applied to any PLL in the calling function.
	 */
	pllreg |= HIBMC_FIELD(HIBMC_PLL_CTRL_BYPASS, 0);
	pllreg |= HIBMC_FIELD(HIBMC_PLL_CTRL_POWER, 1);
	pllreg |= HIBMC_FIELD(HIBMC_PLL_CTRL_INPUT, 0);
	pllreg |= HIBMC_FIELD(HIBMC_PLL_CTRL_POD, pll.POD);
	pllreg |= HIBMC_FIELD(HIBMC_PLL_CTRL_OD, pll.OD);
	pllreg |= HIBMC_FIELD(HIBMC_PLL_CTRL_N, pll.N);
	pllreg |= HIBMC_FIELD(HIBMC_PLL_CTRL_M, pll.M);

	वापस pllreg;
पूर्ण

अटल व्योम set_vघड़ी_hisilicon(काष्ठा drm_device *dev, u64 pll)
अणु
	u32 val;
	काष्ठा hibmc_drm_निजी *priv = to_hibmc_drm_निजी(dev);

	val = पढ़ोl(priv->mmio + CRT_PLL1_HS);
	val &= ~(CRT_PLL1_HS_OUTER_BYPASS(1));
	ग_लिखोl(val, priv->mmio + CRT_PLL1_HS);

	val = CRT_PLL1_HS_INTER_BYPASS(1) | CRT_PLL1_HS_POWERON(1);
	ग_लिखोl(val, priv->mmio + CRT_PLL1_HS);

	ग_लिखोl(pll, priv->mmio + CRT_PLL1_HS);

	usleep_range(1000, 2000);

	val = pll & ~(CRT_PLL1_HS_POWERON(1));
	ग_लिखोl(val, priv->mmio + CRT_PLL1_HS);

	usleep_range(1000, 2000);

	val &= ~(CRT_PLL1_HS_INTER_BYPASS(1));
	ग_लिखोl(val, priv->mmio + CRT_PLL1_HS);

	usleep_range(1000, 2000);

	val |= CRT_PLL1_HS_OUTER_BYPASS(1);
	ग_लिखोl(val, priv->mmio + CRT_PLL1_HS);
पूर्ण

अटल व्योम get_pll_config(u64 x, u64 y, u32 *pll1, u32 *pll2)
अणु
	माप_प्रकार i;
	माप_प्रकार count = ARRAY_SIZE(hibmc_pll_table);

	क्रम (i = 0; i < count; i++) अणु
		अगर (hibmc_pll_table[i].hdisplay == x &&
		    hibmc_pll_table[i].vdisplay == y) अणु
			*pll1 = hibmc_pll_table[i].pll1_config_value;
			*pll2 = hibmc_pll_table[i].pll2_config_value;
			वापस;
		पूर्ण
	पूर्ण

	/* अगर found none, we use शेष value */
	*pll1 = CRT_PLL1_HS_25MHZ;
	*pll2 = CRT_PLL2_HS_25MHZ;
पूर्ण

/*
 * This function takes care the extra रेजिस्टरs and bit fields required to
 * setup a mode in board.
 * Explanation about Display Control रेजिस्टर:
 * FPGA only supports 7 predefined pixel घड़ीs, and घड़ी select is
 * in bit 4:0 of new रेजिस्टर 0x802a8.
 */
अटल u32 display_ctrl_adjust(काष्ठा drm_device *dev,
			       काष्ठा drm_display_mode *mode,
			       u32 ctrl)
अणु
	u64 x, y;
	u32 pll1; /* bit[31:0] of PLL */
	u32 pll2; /* bit[63:32] of PLL */
	काष्ठा hibmc_drm_निजी *priv = to_hibmc_drm_निजी(dev);

	x = mode->hdisplay;
	y = mode->vdisplay;

	get_pll_config(x, y, &pll1, &pll2);
	ग_लिखोl(pll2, priv->mmio + CRT_PLL2_HS);
	set_vघड़ी_hisilicon(dev, pll1);

	/*
	 * Hisilicon has to set up the top-left and bottom-right
	 * रेजिस्टरs as well.
	 * Note that normal chip only use those two रेजिस्टर क्रम
	 * स्वतः-centering mode.
	 */
	ग_लिखोl(HIBMC_FIELD(HIBMC_CRT_AUTO_CENTERING_TL_TOP, 0) |
	       HIBMC_FIELD(HIBMC_CRT_AUTO_CENTERING_TL_LEFT, 0),
	       priv->mmio + HIBMC_CRT_AUTO_CENTERING_TL);

	ग_लिखोl(HIBMC_FIELD(HIBMC_CRT_AUTO_CENTERING_BR_BOTTOM, y - 1) |
	       HIBMC_FIELD(HIBMC_CRT_AUTO_CENTERING_BR_RIGHT, x - 1),
	       priv->mmio + HIBMC_CRT_AUTO_CENTERING_BR);

	/*
	 * Assume common fields in ctrl have been properly set beक्रमe
	 * calling this function.
	 * This function only sets the extra fields in ctrl.
	 */

	/* Set bit 25 of display controller: Select CRT or VGA घड़ी */
	ctrl &= ~HIBMC_CRT_DISP_CTL_CRTSELECT_MASK;
	ctrl &= ~HIBMC_CRT_DISP_CTL_CLOCK_PHASE_MASK;

	ctrl |= HIBMC_CRT_DISP_CTL_CRTSELECT(HIBMC_CRTSELECT_CRT);

	/* घड़ी_phase_polarity is 0 */
	ctrl |= HIBMC_CRT_DISP_CTL_CLOCK_PHASE(0);

	ग_लिखोl(ctrl, priv->mmio + HIBMC_CRT_DISP_CTL);

	वापस ctrl;
पूर्ण

अटल व्योम hibmc_crtc_mode_set_nofb(काष्ठा drm_crtc *crtc)
अणु
	u32 val;
	काष्ठा drm_display_mode *mode = &crtc->state->mode;
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा hibmc_drm_निजी *priv = to_hibmc_drm_निजी(dev);
	u32 width = mode->hsync_end - mode->hsync_start;
	u32 height = mode->vsync_end - mode->vsync_start;

	ग_लिखोl(क्रमmat_pll_reg(), priv->mmio + HIBMC_CRT_PLL_CTRL);
	ग_लिखोl(HIBMC_FIELD(HIBMC_CRT_HORZ_TOTAL_TOTAL, mode->htotal - 1) |
	       HIBMC_FIELD(HIBMC_CRT_HORZ_TOTAL_DISP_END, mode->hdisplay - 1),
	       priv->mmio + HIBMC_CRT_HORZ_TOTAL);

	ग_लिखोl(HIBMC_FIELD(HIBMC_CRT_HORZ_SYNC_WIDTH, width) |
	       HIBMC_FIELD(HIBMC_CRT_HORZ_SYNC_START, mode->hsync_start - 1),
	       priv->mmio + HIBMC_CRT_HORZ_SYNC);

	ग_लिखोl(HIBMC_FIELD(HIBMC_CRT_VERT_TOTAL_TOTAL, mode->vtotal - 1) |
	       HIBMC_FIELD(HIBMC_CRT_VERT_TOTAL_DISP_END, mode->vdisplay - 1),
	       priv->mmio + HIBMC_CRT_VERT_TOTAL);

	ग_लिखोl(HIBMC_FIELD(HIBMC_CRT_VERT_SYNC_HEIGHT, height) |
	       HIBMC_FIELD(HIBMC_CRT_VERT_SYNC_START, mode->vsync_start - 1),
	       priv->mmio + HIBMC_CRT_VERT_SYNC);

	val = HIBMC_FIELD(HIBMC_CRT_DISP_CTL_VSYNC_PHASE, 0);
	val |= HIBMC_FIELD(HIBMC_CRT_DISP_CTL_HSYNC_PHASE, 0);
	val |= HIBMC_CRT_DISP_CTL_TIMING(1);
	val |= HIBMC_CRT_DISP_CTL_PLANE(1);

	display_ctrl_adjust(dev, mode, val);
पूर्ण

अटल व्योम hibmc_crtc_atomic_begin(काष्ठा drm_crtc *crtc,
				    काष्ठा drm_atomic_state *state)
अणु
	u32 reg;
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा hibmc_drm_निजी *priv = to_hibmc_drm_निजी(dev);

	hibmc_set_घातer_mode(priv, HIBMC_PW_MODE_CTL_MODE_MODE0);

	/* Enable display घातer gate & LOCALMEM घातer gate*/
	reg = पढ़ोl(priv->mmio + HIBMC_CURRENT_GATE);
	reg &= ~HIBMC_CURR_GATE_DISPLAY_MASK;
	reg &= ~HIBMC_CURR_GATE_LOCALMEM_MASK;
	reg |= HIBMC_CURR_GATE_DISPLAY(1);
	reg |= HIBMC_CURR_GATE_LOCALMEM(1);
	hibmc_set_current_gate(priv, reg);

	/* We can add more initialization as needed. */
पूर्ण

अटल व्योम hibmc_crtc_atomic_flush(काष्ठा drm_crtc *crtc,
				    काष्ठा drm_atomic_state *state)

अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&crtc->dev->event_lock, flags);
	अगर (crtc->state->event)
		drm_crtc_send_vblank_event(crtc, crtc->state->event);
	crtc->state->event = शून्य;
	spin_unlock_irqrestore(&crtc->dev->event_lock, flags);
पूर्ण

अटल पूर्णांक hibmc_crtc_enable_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा hibmc_drm_निजी *priv = to_hibmc_drm_निजी(crtc->dev);

	ग_लिखोl(HIBMC_RAW_INTERRUPT_EN_VBLANK(1),
	       priv->mmio + HIBMC_RAW_INTERRUPT_EN);

	वापस 0;
पूर्ण

अटल व्योम hibmc_crtc_disable_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा hibmc_drm_निजी *priv = to_hibmc_drm_निजी(crtc->dev);

	ग_लिखोl(HIBMC_RAW_INTERRUPT_EN_VBLANK(0),
	       priv->mmio + HIBMC_RAW_INTERRUPT_EN);
पूर्ण

अटल व्योम hibmc_crtc_load_lut(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा hibmc_drm_निजी *priv = to_hibmc_drm_निजी(crtc->dev);
	व्योम __iomem   *mmio = priv->mmio;
	u16 *r, *g, *b;
	u32 reg;
	u32 i;

	r = crtc->gamma_store;
	g = r + crtc->gamma_size;
	b = g + crtc->gamma_size;

	क्रम (i = 0; i < crtc->gamma_size; i++) अणु
		u32 offset = i << 2;
		u8 red = *r++ >> 8;
		u8 green = *g++ >> 8;
		u8 blue = *b++ >> 8;
		u32 rgb = (red << 16) | (green << 8) | blue;

		ग_लिखोl(rgb, mmio + HIBMC_CRT_PALETTE + offset);
	पूर्ण

	reg = पढ़ोl(priv->mmio + HIBMC_CRT_DISP_CTL);
	reg |= HIBMC_FIELD(HIBMC_CTL_DISP_CTL_GAMMA, 1);
	ग_लिखोl(reg, priv->mmio + HIBMC_CRT_DISP_CTL);
पूर्ण

अटल पूर्णांक hibmc_crtc_gamma_set(काष्ठा drm_crtc *crtc, u16 *red, u16 *green,
				u16 *blue, uपूर्णांक32_t size,
				काष्ठा drm_modeset_acquire_ctx *ctx)
अणु
	hibmc_crtc_load_lut(crtc);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_crtc_funcs hibmc_crtc_funcs = अणु
	.page_flip = drm_atomic_helper_page_flip,
	.set_config = drm_atomic_helper_set_config,
	.destroy = drm_crtc_cleanup,
	.reset = drm_atomic_helper_crtc_reset,
	.atomic_duplicate_state =  drm_atomic_helper_crtc_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_crtc_destroy_state,
	.enable_vblank = hibmc_crtc_enable_vblank,
	.disable_vblank = hibmc_crtc_disable_vblank,
	.gamma_set = hibmc_crtc_gamma_set,
पूर्ण;

अटल स्थिर काष्ठा drm_crtc_helper_funcs hibmc_crtc_helper_funcs = अणु
	.mode_set_nofb	= hibmc_crtc_mode_set_nofb,
	.atomic_begin	= hibmc_crtc_atomic_begin,
	.atomic_flush	= hibmc_crtc_atomic_flush,
	.atomic_enable	= hibmc_crtc_atomic_enable,
	.atomic_disable	= hibmc_crtc_atomic_disable,
	.mode_valid = hibmc_crtc_mode_valid,
पूर्ण;

पूर्णांक hibmc_de_init(काष्ठा hibmc_drm_निजी *priv)
अणु
	काष्ठा drm_device *dev = &priv->dev;
	काष्ठा drm_crtc *crtc = &priv->crtc;
	काष्ठा drm_plane *plane = &priv->primary_plane;
	पूर्णांक ret;

	ret = drm_universal_plane_init(dev, plane, 1, &hibmc_plane_funcs,
				       channel_क्रमmats1,
				       ARRAY_SIZE(channel_क्रमmats1),
				       शून्य,
				       DRM_PLANE_TYPE_PRIMARY,
				       शून्य);

	अगर (ret) अणु
		drm_err(dev, "failed to init plane: %d\n", ret);
		वापस ret;
	पूर्ण

	drm_plane_helper_add(plane, &hibmc_plane_helper_funcs);

	ret = drm_crtc_init_with_planes(dev, crtc, plane,
					शून्य, &hibmc_crtc_funcs, शून्य);
	अगर (ret) अणु
		drm_err(dev, "failed to init crtc: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = drm_mode_crtc_set_gamma_size(crtc, 256);
	अगर (ret) अणु
		drm_err(dev, "failed to set gamma size: %d\n", ret);
		वापस ret;
	पूर्ण
	drm_crtc_helper_add(crtc, &hibmc_crtc_helper_funcs);

	वापस 0;
पूर्ण
