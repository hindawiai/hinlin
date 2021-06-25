<शैली गुरु>
/*
 * Copyright (C) 2013-2015 ARM Limited
 * Author: Liviu Dudau <Liviu.Dudau@arm.com>
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 *
 *  Implementation of a CRTC class क्रम the HDLCD driver.
 */

#समावेश <linux/clk.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/platक्रमm_data/simplefb.h>

#समावेश <video/videomode.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_fb_cma_helper.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_gem_cma_helper.h>
#समावेश <drm/drm_of.h>
#समावेश <drm/drm_plane_helper.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_vblank.h>

#समावेश "hdlcd_drv.h"
#समावेश "hdlcd_regs.h"

/*
 * The HDLCD controller is a dumb RGB streamer that माला_लो connected to
 * a single HDMI transmitter or in the हाल of the ARM Models it माला_लो
 * emulated by the software that करोes the actual rendering.
 *
 */

अटल व्योम hdlcd_crtc_cleanup(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा hdlcd_drm_निजी *hdlcd = crtc_to_hdlcd_priv(crtc);

	/* stop the controller on cleanup */
	hdlcd_ग_लिखो(hdlcd, HDLCD_REG_COMMAND, 0);
	drm_crtc_cleanup(crtc);
पूर्ण

अटल पूर्णांक hdlcd_crtc_enable_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा hdlcd_drm_निजी *hdlcd = crtc_to_hdlcd_priv(crtc);
	अचिन्हित पूर्णांक mask = hdlcd_पढ़ो(hdlcd, HDLCD_REG_INT_MASK);

	hdlcd_ग_लिखो(hdlcd, HDLCD_REG_INT_MASK, mask | HDLCD_INTERRUPT_VSYNC);

	वापस 0;
पूर्ण

अटल व्योम hdlcd_crtc_disable_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा hdlcd_drm_निजी *hdlcd = crtc_to_hdlcd_priv(crtc);
	अचिन्हित पूर्णांक mask = hdlcd_पढ़ो(hdlcd, HDLCD_REG_INT_MASK);

	hdlcd_ग_लिखो(hdlcd, HDLCD_REG_INT_MASK, mask & ~HDLCD_INTERRUPT_VSYNC);
पूर्ण

अटल स्थिर काष्ठा drm_crtc_funcs hdlcd_crtc_funcs = अणु
	.destroy = hdlcd_crtc_cleanup,
	.set_config = drm_atomic_helper_set_config,
	.page_flip = drm_atomic_helper_page_flip,
	.reset = drm_atomic_helper_crtc_reset,
	.atomic_duplicate_state = drm_atomic_helper_crtc_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_crtc_destroy_state,
	.enable_vblank = hdlcd_crtc_enable_vblank,
	.disable_vblank = hdlcd_crtc_disable_vblank,
पूर्ण;

अटल काष्ठा simplefb_क्रमmat supported_क्रमmats[] = SIMPLEFB_FORMATS;

/*
 * Setup the HDLCD रेजिस्टरs क्रम decoding the pixels out of the framebuffer
 */
अटल पूर्णांक hdlcd_set_pxl_fmt(काष्ठा drm_crtc *crtc)
अणु
	अचिन्हित पूर्णांक btpp;
	काष्ठा hdlcd_drm_निजी *hdlcd = crtc_to_hdlcd_priv(crtc);
	स्थिर काष्ठा drm_framebuffer *fb = crtc->primary->state->fb;
	uपूर्णांक32_t pixel_क्रमmat;
	काष्ठा simplefb_क्रमmat *क्रमmat = शून्य;
	पूर्णांक i;

	pixel_क्रमmat = fb->क्रमmat->क्रमmat;

	क्रम (i = 0; i < ARRAY_SIZE(supported_क्रमmats); i++) अणु
		अगर (supported_क्रमmats[i].fourcc == pixel_क्रमmat)
			क्रमmat = &supported_क्रमmats[i];
	पूर्ण

	अगर (WARN_ON(!क्रमmat))
		वापस 0;

	/* HDLCD uses 'bytes per pixel', zero means 1 byte */
	btpp = (क्रमmat->bits_per_pixel + 7) / 8;
	hdlcd_ग_लिखो(hdlcd, HDLCD_REG_PIXEL_FORMAT, (btpp - 1) << 3);

	/*
	 * The क्रमmat of the HDLCD_REG_<color>_SELECT रेजिस्टर is:
	 *   - bits[23:16] - शेष value क्रम that color component
	 *   - bits[11:8]  - number of bits to extract क्रम each color component
	 *   - bits[4:0]   - index of the lowest bit to extract
	 *
	 * The शेष color value is used when bits[11:8] are zero, when the
	 * pixel is outside the visible frame area or when there is a
	 * buffer underrun.
	 */
	hdlcd_ग_लिखो(hdlcd, HDLCD_REG_RED_SELECT, क्रमmat->red.offset |
#अगर_घोषित CONFIG_DRM_HDLCD_SHOW_UNDERRUN
		    0x00ff0000 |	/* show underruns in red */
#पूर्ण_अगर
		    ((क्रमmat->red.length & 0xf) << 8));
	hdlcd_ग_लिखो(hdlcd, HDLCD_REG_GREEN_SELECT, क्रमmat->green.offset |
		    ((क्रमmat->green.length & 0xf) << 8));
	hdlcd_ग_लिखो(hdlcd, HDLCD_REG_BLUE_SELECT, क्रमmat->blue.offset |
		    ((क्रमmat->blue.length & 0xf) << 8));

	वापस 0;
पूर्ण

अटल व्योम hdlcd_crtc_mode_set_nofb(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा hdlcd_drm_निजी *hdlcd = crtc_to_hdlcd_priv(crtc);
	काष्ठा drm_display_mode *m = &crtc->state->adjusted_mode;
	काष्ठा videomode vm;
	अचिन्हित पूर्णांक polarities, err;

	vm.vfront_porch = m->crtc_vsync_start - m->crtc_vdisplay;
	vm.vback_porch = m->crtc_vtotal - m->crtc_vsync_end;
	vm.vsync_len = m->crtc_vsync_end - m->crtc_vsync_start;
	vm.hfront_porch = m->crtc_hsync_start - m->crtc_hdisplay;
	vm.hback_porch = m->crtc_htotal - m->crtc_hsync_end;
	vm.hsync_len = m->crtc_hsync_end - m->crtc_hsync_start;

	polarities = HDLCD_POLARITY_DATAEN | HDLCD_POLARITY_DATA;

	अगर (m->flags & DRM_MODE_FLAG_PHSYNC)
		polarities |= HDLCD_POLARITY_HSYNC;
	अगर (m->flags & DRM_MODE_FLAG_PVSYNC)
		polarities |= HDLCD_POLARITY_VSYNC;

	/* Allow max number of outstanding requests and largest burst size */
	hdlcd_ग_लिखो(hdlcd, HDLCD_REG_BUS_OPTIONS,
		    HDLCD_BUS_MAX_OUTSTAND | HDLCD_BUS_BURST_16);

	hdlcd_ग_लिखो(hdlcd, HDLCD_REG_V_DATA, m->crtc_vdisplay - 1);
	hdlcd_ग_लिखो(hdlcd, HDLCD_REG_V_BACK_PORCH, vm.vback_porch - 1);
	hdlcd_ग_लिखो(hdlcd, HDLCD_REG_V_FRONT_PORCH, vm.vfront_porch - 1);
	hdlcd_ग_लिखो(hdlcd, HDLCD_REG_V_SYNC, vm.vsync_len - 1);
	hdlcd_ग_लिखो(hdlcd, HDLCD_REG_H_DATA, m->crtc_hdisplay - 1);
	hdlcd_ग_लिखो(hdlcd, HDLCD_REG_H_BACK_PORCH, vm.hback_porch - 1);
	hdlcd_ग_लिखो(hdlcd, HDLCD_REG_H_FRONT_PORCH, vm.hfront_porch - 1);
	hdlcd_ग_लिखो(hdlcd, HDLCD_REG_H_SYNC, vm.hsync_len - 1);
	hdlcd_ग_लिखो(hdlcd, HDLCD_REG_POLARITIES, polarities);

	err = hdlcd_set_pxl_fmt(crtc);
	अगर (err)
		वापस;

	clk_set_rate(hdlcd->clk, m->crtc_घड़ी * 1000);
पूर्ण

अटल व्योम hdlcd_crtc_atomic_enable(काष्ठा drm_crtc *crtc,
				     काष्ठा drm_atomic_state *state)
अणु
	काष्ठा hdlcd_drm_निजी *hdlcd = crtc_to_hdlcd_priv(crtc);

	clk_prepare_enable(hdlcd->clk);
	hdlcd_crtc_mode_set_nofb(crtc);
	hdlcd_ग_लिखो(hdlcd, HDLCD_REG_COMMAND, 1);
	drm_crtc_vblank_on(crtc);
पूर्ण

अटल व्योम hdlcd_crtc_atomic_disable(काष्ठा drm_crtc *crtc,
				      काष्ठा drm_atomic_state *state)
अणु
	काष्ठा hdlcd_drm_निजी *hdlcd = crtc_to_hdlcd_priv(crtc);

	drm_crtc_vblank_off(crtc);
	hdlcd_ग_लिखो(hdlcd, HDLCD_REG_COMMAND, 0);
	clk_disable_unprepare(hdlcd->clk);
पूर्ण

अटल क्रमागत drm_mode_status hdlcd_crtc_mode_valid(काष्ठा drm_crtc *crtc,
		स्थिर काष्ठा drm_display_mode *mode)
अणु
	काष्ठा hdlcd_drm_निजी *hdlcd = crtc_to_hdlcd_priv(crtc);
	दीर्घ rate, clk_rate = mode->घड़ी * 1000;

	rate = clk_round_rate(hdlcd->clk, clk_rate);
	/* 0.1% seems a बंद enough tolerance क्रम the TDA19988 on Juno */
	अगर (असल(rate - clk_rate) * 1000 > clk_rate) अणु
		/* घड़ी required by mode not supported by hardware */
		वापस MODE_NOCLOCK;
	पूर्ण

	वापस MODE_OK;
पूर्ण

अटल व्योम hdlcd_crtc_atomic_begin(काष्ठा drm_crtc *crtc,
				    काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_pending_vblank_event *event = crtc->state->event;

	अगर (event) अणु
		crtc->state->event = शून्य;

		spin_lock_irq(&crtc->dev->event_lock);
		अगर (drm_crtc_vblank_get(crtc) == 0)
			drm_crtc_arm_vblank_event(crtc, event);
		अन्यथा
			drm_crtc_send_vblank_event(crtc, event);
		spin_unlock_irq(&crtc->dev->event_lock);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा drm_crtc_helper_funcs hdlcd_crtc_helper_funcs = अणु
	.mode_valid	= hdlcd_crtc_mode_valid,
	.atomic_begin	= hdlcd_crtc_atomic_begin,
	.atomic_enable	= hdlcd_crtc_atomic_enable,
	.atomic_disable	= hdlcd_crtc_atomic_disable,
पूर्ण;

अटल पूर्णांक hdlcd_plane_atomic_check(काष्ठा drm_plane *plane,
				    काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *new_plane_state = drm_atomic_get_new_plane_state(state,
										 plane);
	पूर्णांक i;
	काष्ठा drm_crtc *crtc;
	काष्ठा drm_crtc_state *crtc_state;
	u32 src_h = new_plane_state->src_h >> 16;

	/* only the HDLCD_REG_FB_LINE_COUNT रेजिस्टर has a limit */
	अगर (src_h >= HDLCD_MAX_YRES) अणु
		DRM_DEBUG_KMS("Invalid source width: %d\n", src_h);
		वापस -EINVAL;
	पूर्ण

	क्रम_each_new_crtc_in_state(state, crtc, crtc_state,
				   i) अणु
		/* we cannot disable the plane जबतक the CRTC is active */
		अगर (!new_plane_state->fb && crtc_state->active)
			वापस -EINVAL;
		वापस drm_atomic_helper_check_plane_state(new_plane_state,
							   crtc_state,
							   DRM_PLANE_HELPER_NO_SCALING,
							   DRM_PLANE_HELPER_NO_SCALING,
							   false, true);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम hdlcd_plane_atomic_update(काष्ठा drm_plane *plane,
				      काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *new_plane_state = drm_atomic_get_new_plane_state(state,
										 plane);
	काष्ठा drm_framebuffer *fb = new_plane_state->fb;
	काष्ठा hdlcd_drm_निजी *hdlcd;
	u32 dest_h;
	dma_addr_t scanout_start;

	अगर (!fb)
		वापस;

	dest_h = drm_rect_height(&new_plane_state->dst);
	scanout_start = drm_fb_cma_get_gem_addr(fb, new_plane_state, 0);

	hdlcd = plane->dev->dev_निजी;
	hdlcd_ग_लिखो(hdlcd, HDLCD_REG_FB_LINE_LENGTH, fb->pitches[0]);
	hdlcd_ग_लिखो(hdlcd, HDLCD_REG_FB_LINE_PITCH, fb->pitches[0]);
	hdlcd_ग_लिखो(hdlcd, HDLCD_REG_FB_LINE_COUNT, dest_h - 1);
	hdlcd_ग_लिखो(hdlcd, HDLCD_REG_FB_BASE, scanout_start);
पूर्ण

अटल स्थिर काष्ठा drm_plane_helper_funcs hdlcd_plane_helper_funcs = अणु
	.atomic_check = hdlcd_plane_atomic_check,
	.atomic_update = hdlcd_plane_atomic_update,
पूर्ण;

अटल स्थिर काष्ठा drm_plane_funcs hdlcd_plane_funcs = अणु
	.update_plane		= drm_atomic_helper_update_plane,
	.disable_plane		= drm_atomic_helper_disable_plane,
	.destroy		= drm_plane_cleanup,
	.reset			= drm_atomic_helper_plane_reset,
	.atomic_duplicate_state = drm_atomic_helper_plane_duplicate_state,
	.atomic_destroy_state	= drm_atomic_helper_plane_destroy_state,
पूर्ण;

अटल काष्ठा drm_plane *hdlcd_plane_init(काष्ठा drm_device *drm)
अणु
	काष्ठा hdlcd_drm_निजी *hdlcd = drm->dev_निजी;
	काष्ठा drm_plane *plane = शून्य;
	u32 क्रमmats[ARRAY_SIZE(supported_क्रमmats)], i;
	पूर्णांक ret;

	plane = devm_kzalloc(drm->dev, माप(*plane), GFP_KERNEL);
	अगर (!plane)
		वापस ERR_PTR(-ENOMEM);

	क्रम (i = 0; i < ARRAY_SIZE(supported_क्रमmats); i++)
		क्रमmats[i] = supported_क्रमmats[i].fourcc;

	ret = drm_universal_plane_init(drm, plane, 0xff, &hdlcd_plane_funcs,
				       क्रमmats, ARRAY_SIZE(क्रमmats),
				       शून्य,
				       DRM_PLANE_TYPE_PRIMARY, शून्य);
	अगर (ret)
		वापस ERR_PTR(ret);

	drm_plane_helper_add(plane, &hdlcd_plane_helper_funcs);
	hdlcd->plane = plane;

	वापस plane;
पूर्ण

पूर्णांक hdlcd_setup_crtc(काष्ठा drm_device *drm)
अणु
	काष्ठा hdlcd_drm_निजी *hdlcd = drm->dev_निजी;
	काष्ठा drm_plane *primary;
	पूर्णांक ret;

	primary = hdlcd_plane_init(drm);
	अगर (IS_ERR(primary))
		वापस PTR_ERR(primary);

	ret = drm_crtc_init_with_planes(drm, &hdlcd->crtc, primary, शून्य,
					&hdlcd_crtc_funcs, शून्य);
	अगर (ret)
		वापस ret;

	drm_crtc_helper_add(&hdlcd->crtc, &hdlcd_crtc_helper_funcs);
	वापस 0;
पूर्ण
