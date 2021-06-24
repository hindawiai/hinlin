<शैली गुरु>
/*
 * Copyright 2007-8 Advanced Micro Devices, Inc.
 * Copyright 2008 Red Hat Inc.
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
 * Authors: Dave Airlie
 *          Alex Deucher
 */

#समावेश <drm/drm_crtc_helper.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_fixed.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_vblank.h>
#समावेश <drm/radeon_drm.h>

#समावेश "atom.h"
#समावेश "radeon.h"

अटल व्योम radeon_overscan_setup(काष्ठा drm_crtc *crtc,
				  काष्ठा drm_display_mode *mode)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);

	WREG32(RADEON_OVR_CLR + radeon_crtc->crtc_offset, 0);
	WREG32(RADEON_OVR_WID_LEFT_RIGHT + radeon_crtc->crtc_offset, 0);
	WREG32(RADEON_OVR_WID_TOP_BOTTOM + radeon_crtc->crtc_offset, 0);
पूर्ण

अटल व्योम radeon_legacy_rmx_mode_set(काष्ठा drm_crtc *crtc,
				       काष्ठा drm_display_mode *mode)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);
	पूर्णांक xres = mode->hdisplay;
	पूर्णांक yres = mode->vdisplay;
	bool hscale = true, vscale = true;
	पूर्णांक hsync_wid;
	पूर्णांक vsync_wid;
	पूर्णांक hsync_start;
	पूर्णांक blank_width;
	u32 scale, inc, crtc_more_cntl;
	u32 fp_horz_stretch, fp_vert_stretch, fp_horz_vert_active;
	u32 fp_h_sync_strt_wid, fp_crtc_h_total_disp;
	u32 fp_v_sync_strt_wid, fp_crtc_v_total_disp;
	काष्ठा drm_display_mode *native_mode = &radeon_crtc->native_mode;

	fp_vert_stretch = RREG32(RADEON_FP_VERT_STRETCH) &
		(RADEON_VERT_STRETCH_RESERVED |
		 RADEON_VERT_AUTO_RATIO_INC);
	fp_horz_stretch = RREG32(RADEON_FP_HORZ_STRETCH) &
		(RADEON_HORZ_FP_LOOP_STRETCH |
		 RADEON_HORZ_AUTO_RATIO_INC);

	crtc_more_cntl = 0;
	अगर ((rdev->family == CHIP_RS100) ||
	    (rdev->family == CHIP_RS200)) अणु
		/* This is to workaround the asic bug क्रम RMX, some versions
		   of BIOS करोsen't have this रेजिस्टर initialized correctly. */
		crtc_more_cntl |= RADEON_CRTC_H_CUTOFF_ACTIVE_EN;
	पूर्ण


	fp_crtc_h_total_disp = ((((mode->crtc_htotal / 8) - 1) & 0x3ff)
				| ((((mode->crtc_hdisplay / 8) - 1) & 0x1ff) << 16));

	hsync_wid = (mode->crtc_hsync_end - mode->crtc_hsync_start) / 8;
	अगर (!hsync_wid)
		hsync_wid = 1;
	hsync_start = mode->crtc_hsync_start - 8;

	fp_h_sync_strt_wid = ((hsync_start & 0x1fff)
			      | ((hsync_wid & 0x3f) << 16)
			      | ((mode->flags & DRM_MODE_FLAG_NHSYNC)
				 ? RADEON_CRTC_H_SYNC_POL
				 : 0));

	fp_crtc_v_total_disp = (((mode->crtc_vtotal - 1) & 0xffff)
				| ((mode->crtc_vdisplay - 1) << 16));

	vsync_wid = mode->crtc_vsync_end - mode->crtc_vsync_start;
	अगर (!vsync_wid)
		vsync_wid = 1;

	fp_v_sync_strt_wid = (((mode->crtc_vsync_start - 1) & 0xfff)
			      | ((vsync_wid & 0x1f) << 16)
			      | ((mode->flags & DRM_MODE_FLAG_NVSYNC)
				 ? RADEON_CRTC_V_SYNC_POL
				 : 0));

	fp_horz_vert_active = 0;

	अगर (native_mode->hdisplay == 0 ||
	    native_mode->vdisplay == 0) अणु
		hscale = false;
		vscale = false;
	पूर्ण अन्यथा अणु
		अगर (xres > native_mode->hdisplay)
			xres = native_mode->hdisplay;
		अगर (yres > native_mode->vdisplay)
			yres = native_mode->vdisplay;

		अगर (xres == native_mode->hdisplay)
			hscale = false;
		अगर (yres == native_mode->vdisplay)
			vscale = false;
	पूर्ण

	चयन (radeon_crtc->rmx_type) अणु
	हाल RMX_FULL:
	हाल RMX_ASPECT:
		अगर (!hscale)
			fp_horz_stretch |= ((xres/8-1) << 16);
		अन्यथा अणु
			inc = (fp_horz_stretch & RADEON_HORZ_AUTO_RATIO_INC) ? 1 : 0;
			scale = ((xres + inc) * RADEON_HORZ_STRETCH_RATIO_MAX)
				/ native_mode->hdisplay + 1;
			fp_horz_stretch |= (((scale) & RADEON_HORZ_STRETCH_RATIO_MASK) |
					RADEON_HORZ_STRETCH_BLEND |
					RADEON_HORZ_STRETCH_ENABLE |
					((native_mode->hdisplay/8-1) << 16));
		पूर्ण

		अगर (!vscale)
			fp_vert_stretch |= ((yres-1) << 12);
		अन्यथा अणु
			inc = (fp_vert_stretch & RADEON_VERT_AUTO_RATIO_INC) ? 1 : 0;
			scale = ((yres + inc) * RADEON_VERT_STRETCH_RATIO_MAX)
				/ native_mode->vdisplay + 1;
			fp_vert_stretch |= (((scale) & RADEON_VERT_STRETCH_RATIO_MASK) |
					RADEON_VERT_STRETCH_ENABLE |
					RADEON_VERT_STRETCH_BLEND |
					((native_mode->vdisplay-1) << 12));
		पूर्ण
		अवरोध;
	हाल RMX_CENTER:
		fp_horz_stretch |= ((xres/8-1) << 16);
		fp_vert_stretch |= ((yres-1) << 12);

		crtc_more_cntl |= (RADEON_CRTC_AUTO_HORZ_CENTER_EN |
				RADEON_CRTC_AUTO_VERT_CENTER_EN);

		blank_width = (mode->crtc_hblank_end - mode->crtc_hblank_start) / 8;
		अगर (blank_width > 110)
			blank_width = 110;

		fp_crtc_h_total_disp = (((blank_width) & 0x3ff)
				| ((((mode->crtc_hdisplay / 8) - 1) & 0x1ff) << 16));

		hsync_wid = (mode->crtc_hsync_end - mode->crtc_hsync_start) / 8;
		अगर (!hsync_wid)
			hsync_wid = 1;

		fp_h_sync_strt_wid = ((((mode->crtc_hsync_start - mode->crtc_hblank_start) / 8) & 0x1fff)
				| ((hsync_wid & 0x3f) << 16)
				| ((mode->flags & DRM_MODE_FLAG_NHSYNC)
					? RADEON_CRTC_H_SYNC_POL
					: 0));

		fp_crtc_v_total_disp = (((mode->crtc_vblank_end - mode->crtc_vblank_start) & 0xffff)
				| ((mode->crtc_vdisplay - 1) << 16));

		vsync_wid = mode->crtc_vsync_end - mode->crtc_vsync_start;
		अगर (!vsync_wid)
			vsync_wid = 1;

		fp_v_sync_strt_wid = ((((mode->crtc_vsync_start - mode->crtc_vblank_start) & 0xfff)
					| ((vsync_wid & 0x1f) << 16)
					| ((mode->flags & DRM_MODE_FLAG_NVSYNC)
						? RADEON_CRTC_V_SYNC_POL
						: 0)));

		fp_horz_vert_active = (((native_mode->vdisplay) & 0xfff) |
				(((native_mode->hdisplay / 8) & 0x1ff) << 16));
		अवरोध;
	हाल RMX_OFF:
	शेष:
		fp_horz_stretch |= ((xres/8-1) << 16);
		fp_vert_stretch |= ((yres-1) << 12);
		अवरोध;
	पूर्ण

	WREG32(RADEON_FP_HORZ_STRETCH,      fp_horz_stretch);
	WREG32(RADEON_FP_VERT_STRETCH,      fp_vert_stretch);
	WREG32(RADEON_CRTC_MORE_CNTL,       crtc_more_cntl);
	WREG32(RADEON_FP_HORZ_VERT_ACTIVE,  fp_horz_vert_active);
	WREG32(RADEON_FP_H_SYNC_STRT_WID,   fp_h_sync_strt_wid);
	WREG32(RADEON_FP_V_SYNC_STRT_WID,   fp_v_sync_strt_wid);
	WREG32(RADEON_FP_CRTC_H_TOTAL_DISP, fp_crtc_h_total_disp);
	WREG32(RADEON_FP_CRTC_V_TOTAL_DISP, fp_crtc_v_total_disp);
पूर्ण

अटल व्योम radeon_pll_रुको_क्रम_पढ़ो_update_complete(काष्ठा drm_device *dev)
अणु
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	पूर्णांक i = 0;

	/* FIXME: Certain revisions of R300 can't recover here.  Not sure of
	   the cause yet, but this workaround will mask the problem क्रम now.
	   Other chips usually will pass at the very first test, so the
	   workaround shouldn't have any effect on them. */
	क्रम (i = 0;
	     (i < 10000 &&
	      RREG32_PLL(RADEON_PPLL_REF_DIV) & RADEON_PPLL_ATOMIC_UPDATE_R);
	     i++);
पूर्ण

अटल व्योम radeon_pll_ग_लिखो_update(काष्ठा drm_device *dev)
अणु
	काष्ठा radeon_device *rdev = dev->dev_निजी;

	जबतक (RREG32_PLL(RADEON_PPLL_REF_DIV) & RADEON_PPLL_ATOMIC_UPDATE_R);

	WREG32_PLL_P(RADEON_PPLL_REF_DIV,
			   RADEON_PPLL_ATOMIC_UPDATE_W,
			   ~(RADEON_PPLL_ATOMIC_UPDATE_W));
पूर्ण

अटल व्योम radeon_pll2_रुको_क्रम_पढ़ो_update_complete(काष्ठा drm_device *dev)
अणु
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	पूर्णांक i = 0;


	/* FIXME: Certain revisions of R300 can't recover here.  Not sure of
	   the cause yet, but this workaround will mask the problem क्रम now.
	   Other chips usually will pass at the very first test, so the
	   workaround shouldn't have any effect on them. */
	क्रम (i = 0;
	     (i < 10000 &&
	      RREG32_PLL(RADEON_P2PLL_REF_DIV) & RADEON_P2PLL_ATOMIC_UPDATE_R);
	     i++);
पूर्ण

अटल व्योम radeon_pll2_ग_लिखो_update(काष्ठा drm_device *dev)
अणु
	काष्ठा radeon_device *rdev = dev->dev_निजी;

	जबतक (RREG32_PLL(RADEON_P2PLL_REF_DIV) & RADEON_P2PLL_ATOMIC_UPDATE_R);

	WREG32_PLL_P(RADEON_P2PLL_REF_DIV,
			   RADEON_P2PLL_ATOMIC_UPDATE_W,
			   ~(RADEON_P2PLL_ATOMIC_UPDATE_W));
पूर्ण

अटल uपूर्णांक8_t radeon_compute_pll_gain(uपूर्णांक16_t ref_freq, uपूर्णांक16_t ref_भाग,
				       uपूर्णांक16_t fb_भाग)
अणु
	अचिन्हित पूर्णांक vcoFreq;

	अगर (!ref_भाग)
		वापस 1;

	vcoFreq = ((अचिन्हित)ref_freq * fb_भाग) / ref_भाग;

	/*
	 * This is horribly crude: the VCO frequency range is भागided पूर्णांकo
	 * 3 parts, each part having a fixed PLL gain value.
	 */
	अगर (vcoFreq >= 30000)
		/*
		 * [300..max] MHz : 7
		 */
		वापस 7;
	अन्यथा अगर (vcoFreq >= 18000)
		/*
		 * [180..300) MHz : 4
		 */
		वापस 4;
	अन्यथा
		/*
		 * [0..180) MHz : 1
		 */
		वापस 1;
पूर्ण

अटल व्योम radeon_crtc_dpms(काष्ठा drm_crtc *crtc, पूर्णांक mode)
अणु
	काष्ठा radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	uपूर्णांक32_t crtc_ext_cntl = 0;
	uपूर्णांक32_t mask;

	अगर (radeon_crtc->crtc_id)
		mask = (RADEON_CRTC2_DISP_DIS |
			RADEON_CRTC2_VSYNC_DIS |
			RADEON_CRTC2_HSYNC_DIS |
			RADEON_CRTC2_DISP_REQ_EN_B);
	अन्यथा
		mask = (RADEON_CRTC_DISPLAY_DIS |
			RADEON_CRTC_VSYNC_DIS |
			RADEON_CRTC_HSYNC_DIS);

	/*
	 * On all dual CRTC GPUs this bit controls the CRTC of the primary DAC.
	 * Thereक्रमe it is set in the DAC DMPS function.
	 * This is dअगरferent क्रम GPU's with a single CRTC but a primary and a
	 * TV DAC: here it controls the single CRTC no matter where it is
	 * routed. Thereक्रमe we set it here.
	 */
	अगर (rdev->flags & RADEON_SINGLE_CRTC)
		crtc_ext_cntl = RADEON_CRTC_CRT_ON;
	
	चयन (mode) अणु
	हाल DRM_MODE_DPMS_ON:
		radeon_crtc->enabled = true;
		/* adjust pm to dpms changes BEFORE enabling crtcs */
		radeon_pm_compute_घड़ीs(rdev);
		अगर (radeon_crtc->crtc_id)
			WREG32_P(RADEON_CRTC2_GEN_CNTL, RADEON_CRTC2_EN, ~(RADEON_CRTC2_EN | mask));
		अन्यथा अणु
			WREG32_P(RADEON_CRTC_GEN_CNTL, RADEON_CRTC_EN, ~(RADEON_CRTC_EN |
									 RADEON_CRTC_DISP_REQ_EN_B));
			WREG32_P(RADEON_CRTC_EXT_CNTL, crtc_ext_cntl, ~(mask | crtc_ext_cntl));
		पूर्ण
		अगर (dev->num_crtcs > radeon_crtc->crtc_id)
			drm_crtc_vblank_on(crtc);
		radeon_crtc_load_lut(crtc);
		अवरोध;
	हाल DRM_MODE_DPMS_STANDBY:
	हाल DRM_MODE_DPMS_SUSPEND:
	हाल DRM_MODE_DPMS_OFF:
		अगर (dev->num_crtcs > radeon_crtc->crtc_id)
			drm_crtc_vblank_off(crtc);
		अगर (radeon_crtc->crtc_id)
			WREG32_P(RADEON_CRTC2_GEN_CNTL, mask, ~(RADEON_CRTC2_EN | mask));
		अन्यथा अणु
			WREG32_P(RADEON_CRTC_GEN_CNTL, RADEON_CRTC_DISP_REQ_EN_B, ~(RADEON_CRTC_EN |
										    RADEON_CRTC_DISP_REQ_EN_B));
			WREG32_P(RADEON_CRTC_EXT_CNTL, mask, ~(mask | crtc_ext_cntl));
		पूर्ण
		radeon_crtc->enabled = false;
		/* adjust pm to dpms changes AFTER disabling crtcs */
		radeon_pm_compute_घड़ीs(rdev);
		अवरोध;
	पूर्ण
पूर्ण

पूर्णांक radeon_crtc_set_base(काष्ठा drm_crtc *crtc, पूर्णांक x, पूर्णांक y,
			 काष्ठा drm_framebuffer *old_fb)
अणु
	वापस radeon_crtc_करो_set_base(crtc, old_fb, x, y, 0);
पूर्ण

पूर्णांक radeon_crtc_set_base_atomic(काष्ठा drm_crtc *crtc,
				काष्ठा drm_framebuffer *fb,
				पूर्णांक x, पूर्णांक y, क्रमागत mode_set_atomic state)
अणु
	वापस radeon_crtc_करो_set_base(crtc, fb, x, y, 1);
पूर्ण

पूर्णांक radeon_crtc_करो_set_base(काष्ठा drm_crtc *crtc,
			 काष्ठा drm_framebuffer *fb,
			 पूर्णांक x, पूर्णांक y, पूर्णांक atomic)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);
	काष्ठा drm_framebuffer *target_fb;
	काष्ठा drm_gem_object *obj;
	काष्ठा radeon_bo *rbo;
	uपूर्णांक64_t base;
	uपूर्णांक32_t crtc_offset, crtc_offset_cntl, crtc_tile_x0_y0 = 0;
	uपूर्णांक32_t crtc_pitch, pitch_pixels;
	uपूर्णांक32_t tiling_flags;
	पूर्णांक क्रमmat;
	uपूर्णांक32_t gen_cntl_reg, gen_cntl_val;
	पूर्णांक r;

	DRM_DEBUG_KMS("\n");
	/* no fb bound */
	अगर (!atomic && !crtc->primary->fb) अणु
		DRM_DEBUG_KMS("No FB bound\n");
		वापस 0;
	पूर्ण

	अगर (atomic)
		target_fb = fb;
	अन्यथा
		target_fb = crtc->primary->fb;

	चयन (target_fb->क्रमmat->cpp[0] * 8) अणु
	हाल 8:
		क्रमmat = 2;
		अवरोध;
	हाल 15:      /*  555 */
		क्रमmat = 3;
		अवरोध;
	हाल 16:      /*  565 */
		क्रमmat = 4;
		अवरोध;
	हाल 24:      /*  RGB */
		क्रमmat = 5;
		अवरोध;
	हाल 32:      /* xRGB */
		क्रमmat = 6;
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	/* Pin framebuffer & get tilling inक्रमmations */
	obj = target_fb->obj[0];
	rbo = gem_to_radeon_bo(obj);
retry:
	r = radeon_bo_reserve(rbo, false);
	अगर (unlikely(r != 0))
		वापस r;
	/* Only 27 bit offset क्रम legacy CRTC */
	r = radeon_bo_pin_restricted(rbo, RADEON_GEM_DOMAIN_VRAM, 1 << 27,
				     &base);
	अगर (unlikely(r != 0)) अणु
		radeon_bo_unreserve(rbo);

		/* On old GPU like RN50 with little vram pining can fails because
		 * current fb is taking all space needed. So instead of unpining
		 * the old buffer after pining the new one, first unpin old one
		 * and then retry pining new one.
		 *
		 * As only master can set mode only master can pin and it is
		 * unlikely the master client will race with itself especialy
		 * on those old gpu with single crtc.
		 *
		 * We करोn't shutकरोwn the display controller because new buffer
		 * will end up in same spot.
		 */
		अगर (!atomic && fb && fb != crtc->primary->fb) अणु
			काष्ठा radeon_bo *old_rbo;
			अचिन्हित दीर्घ nsize, osize;

			old_rbo = gem_to_radeon_bo(fb->obj[0]);
			osize = radeon_bo_size(old_rbo);
			nsize = radeon_bo_size(rbo);
			अगर (nsize <= osize && !radeon_bo_reserve(old_rbo, false)) अणु
				radeon_bo_unpin(old_rbo);
				radeon_bo_unreserve(old_rbo);
				fb = शून्य;
				जाओ retry;
			पूर्ण
		पूर्ण
		वापस -EINVAL;
	पूर्ण
	radeon_bo_get_tiling_flags(rbo, &tiling_flags, शून्य);
	radeon_bo_unreserve(rbo);
	अगर (tiling_flags & RADEON_TILING_MICRO)
		DRM_ERROR("trying to scanout microtiled buffer\n");

	/* अगर scanout was in GTT this really wouldn't work */
	/* crtc offset is from display base addr not FB location */
	radeon_crtc->legacy_display_base_addr = rdev->mc.vram_start;

	base -= radeon_crtc->legacy_display_base_addr;

	crtc_offset_cntl = 0;

	pitch_pixels = target_fb->pitches[0] / target_fb->क्रमmat->cpp[0];
	crtc_pitch = DIV_ROUND_UP(pitch_pixels * target_fb->क्रमmat->cpp[0] * 8,
				  target_fb->क्रमmat->cpp[0] * 8 * 8);
	crtc_pitch |= crtc_pitch << 16;

	crtc_offset_cntl |= RADEON_CRTC_GUI_TRIG_OFFSET_LEFT_EN;
	अगर (tiling_flags & RADEON_TILING_MACRO) अणु
		अगर (ASIC_IS_R300(rdev))
			crtc_offset_cntl |= (R300_CRTC_X_Y_MODE_EN |
					     R300_CRTC_MICRO_TILE_BUFFER_DIS |
					     R300_CRTC_MACRO_TILE_EN);
		अन्यथा
			crtc_offset_cntl |= RADEON_CRTC_TILE_EN;
	पूर्ण अन्यथा अणु
		अगर (ASIC_IS_R300(rdev))
			crtc_offset_cntl &= ~(R300_CRTC_X_Y_MODE_EN |
					      R300_CRTC_MICRO_TILE_BUFFER_DIS |
					      R300_CRTC_MACRO_TILE_EN);
		अन्यथा
			crtc_offset_cntl &= ~RADEON_CRTC_TILE_EN;
	पूर्ण

	अगर (tiling_flags & RADEON_TILING_MACRO) अणु
		अगर (ASIC_IS_R300(rdev)) अणु
			crtc_tile_x0_y0 = x | (y << 16);
			base &= ~0x7ff;
		पूर्ण अन्यथा अणु
			पूर्णांक byteshअगरt = target_fb->क्रमmat->cpp[0] * 8 >> 4;
			पूर्णांक tile_addr = (((y >> 3) * pitch_pixels +  x) >> (8 - byteshअगरt)) << 11;
			base += tile_addr + ((x << byteshअगरt) % 256) + ((y % 8) << 8);
			crtc_offset_cntl |= (y % 16);
		पूर्ण
	पूर्ण अन्यथा अणु
		पूर्णांक offset = y * pitch_pixels + x;
		चयन (target_fb->क्रमmat->cpp[0] * 8) अणु
		हाल 8:
			offset *= 1;
			अवरोध;
		हाल 15:
		हाल 16:
			offset *= 2;
			अवरोध;
		हाल 24:
			offset *= 3;
			अवरोध;
		हाल 32:
			offset *= 4;
			अवरोध;
		शेष:
			वापस false;
		पूर्ण
		base += offset;
	पूर्ण

	base &= ~7;

	अगर (radeon_crtc->crtc_id == 1)
		gen_cntl_reg = RADEON_CRTC2_GEN_CNTL;
	अन्यथा
		gen_cntl_reg = RADEON_CRTC_GEN_CNTL;

	gen_cntl_val = RREG32(gen_cntl_reg);
	gen_cntl_val &= ~(0xf << 8);
	gen_cntl_val |= (क्रमmat << 8);
	gen_cntl_val &= ~RADEON_CRTC_VSTAT_MODE_MASK;
	WREG32(gen_cntl_reg, gen_cntl_val);

	crtc_offset = (u32)base;

	WREG32(RADEON_DISPLAY_BASE_ADDR + radeon_crtc->crtc_offset, radeon_crtc->legacy_display_base_addr);

	अगर (ASIC_IS_R300(rdev)) अणु
		अगर (radeon_crtc->crtc_id)
			WREG32(R300_CRTC2_TILE_X0_Y0, crtc_tile_x0_y0);
		अन्यथा
			WREG32(R300_CRTC_TILE_X0_Y0, crtc_tile_x0_y0);
	पूर्ण
	WREG32(RADEON_CRTC_OFFSET_CNTL + radeon_crtc->crtc_offset, crtc_offset_cntl);
	WREG32(RADEON_CRTC_OFFSET + radeon_crtc->crtc_offset, crtc_offset);
	WREG32(RADEON_CRTC_PITCH + radeon_crtc->crtc_offset, crtc_pitch);

	अगर (!atomic && fb && fb != crtc->primary->fb) अणु
		rbo = gem_to_radeon_bo(fb->obj[0]);
		r = radeon_bo_reserve(rbo, false);
		अगर (unlikely(r != 0))
			वापस r;
		radeon_bo_unpin(rbo);
		radeon_bo_unreserve(rbo);
	पूर्ण

	/* Bytes per pixel may have changed */
	radeon_bandwidth_update(rdev);

	वापस 0;
पूर्ण

अटल bool radeon_set_crtc_timing(काष्ठा drm_crtc *crtc, काष्ठा drm_display_mode *mode)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);
	स्थिर काष्ठा drm_framebuffer *fb = crtc->primary->fb;
	काष्ठा drm_encoder *encoder;
	पूर्णांक क्रमmat;
	पूर्णांक hsync_start;
	पूर्णांक hsync_wid;
	पूर्णांक vsync_wid;
	uपूर्णांक32_t crtc_h_total_disp;
	uपूर्णांक32_t crtc_h_sync_strt_wid;
	uपूर्णांक32_t crtc_v_total_disp;
	uपूर्णांक32_t crtc_v_sync_strt_wid;
	bool is_tv = false;

	DRM_DEBUG_KMS("\n");
	list_क्रम_each_entry(encoder, &dev->mode_config.encoder_list, head) अणु
		अगर (encoder->crtc == crtc) अणु
			काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
			अगर (radeon_encoder->active_device & ATOM_DEVICE_TV_SUPPORT) अणु
				is_tv = true;
				DRM_INFO("crtc %d is connected to a TV\n", radeon_crtc->crtc_id);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	चयन (fb->क्रमmat->cpp[0] * 8) अणु
	हाल 8:
		क्रमmat = 2;
		अवरोध;
	हाल 15:      /*  555 */
		क्रमmat = 3;
		अवरोध;
	हाल 16:      /*  565 */
		क्रमmat = 4;
		अवरोध;
	हाल 24:      /*  RGB */
		क्रमmat = 5;
		अवरोध;
	हाल 32:      /* xRGB */
		क्रमmat = 6;
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	crtc_h_total_disp = ((((mode->crtc_htotal / 8) - 1) & 0x3ff)
			     | ((((mode->crtc_hdisplay / 8) - 1) & 0x1ff) << 16));

	hsync_wid = (mode->crtc_hsync_end - mode->crtc_hsync_start) / 8;
	अगर (!hsync_wid)
		hsync_wid = 1;
	hsync_start = mode->crtc_hsync_start - 8;

	crtc_h_sync_strt_wid = ((hsync_start & 0x1fff)
				| ((hsync_wid & 0x3f) << 16)
				| ((mode->flags & DRM_MODE_FLAG_NHSYNC)
				   ? RADEON_CRTC_H_SYNC_POL
				   : 0));

	/* This works क्रम द्विगुन scan mode. */
	crtc_v_total_disp = (((mode->crtc_vtotal - 1) & 0xffff)
			     | ((mode->crtc_vdisplay - 1) << 16));

	vsync_wid = mode->crtc_vsync_end - mode->crtc_vsync_start;
	अगर (!vsync_wid)
		vsync_wid = 1;

	crtc_v_sync_strt_wid = (((mode->crtc_vsync_start - 1) & 0xfff)
				| ((vsync_wid & 0x1f) << 16)
				| ((mode->flags & DRM_MODE_FLAG_NVSYNC)
				   ? RADEON_CRTC_V_SYNC_POL
				   : 0));

	अगर (radeon_crtc->crtc_id) अणु
		uपूर्णांक32_t crtc2_gen_cntl;
		uपूर्णांक32_t disp2_merge_cntl;

		/* अगर TV DAC is enabled क्रम another crtc and keep it enabled */
		crtc2_gen_cntl = RREG32(RADEON_CRTC2_GEN_CNTL) & 0x00718080;
		crtc2_gen_cntl |= ((क्रमmat << 8)
				   | RADEON_CRTC2_VSYNC_DIS
				   | RADEON_CRTC2_HSYNC_DIS
				   | RADEON_CRTC2_DISP_DIS
				   | RADEON_CRTC2_DISP_REQ_EN_B
				   | ((mode->flags & DRM_MODE_FLAG_DBLSCAN)
				      ? RADEON_CRTC2_DBL_SCAN_EN
				      : 0)
				   | ((mode->flags & DRM_MODE_FLAG_CSYNC)
				      ? RADEON_CRTC2_CSYNC_EN
				      : 0)
				   | ((mode->flags & DRM_MODE_FLAG_INTERLACE)
				      ? RADEON_CRTC2_INTERLACE_EN
				      : 0));

		/* rs4xx chips seem to like to have the crtc enabled when the timing is set */
		अगर ((rdev->family == CHIP_RS400) || (rdev->family == CHIP_RS480))
			crtc2_gen_cntl |= RADEON_CRTC2_EN;

		disp2_merge_cntl = RREG32(RADEON_DISP2_MERGE_CNTL);
		disp2_merge_cntl &= ~RADEON_DISP2_RGB_OFFSET_EN;

		WREG32(RADEON_DISP2_MERGE_CNTL, disp2_merge_cntl);
		WREG32(RADEON_CRTC2_GEN_CNTL, crtc2_gen_cntl);

		WREG32(RADEON_FP_H2_SYNC_STRT_WID, crtc_h_sync_strt_wid);
		WREG32(RADEON_FP_V2_SYNC_STRT_WID, crtc_v_sync_strt_wid);
	पूर्ण अन्यथा अणु
		uपूर्णांक32_t crtc_gen_cntl;
		uपूर्णांक32_t crtc_ext_cntl;
		uपूर्णांक32_t disp_merge_cntl;

		crtc_gen_cntl = RREG32(RADEON_CRTC_GEN_CNTL) & 0x00718000;
		crtc_gen_cntl |= (RADEON_CRTC_EXT_DISP_EN
				 | (क्रमmat << 8)
				 | RADEON_CRTC_DISP_REQ_EN_B
				 | ((mode->flags & DRM_MODE_FLAG_DBLSCAN)
				    ? RADEON_CRTC_DBL_SCAN_EN
				    : 0)
				 | ((mode->flags & DRM_MODE_FLAG_CSYNC)
				    ? RADEON_CRTC_CSYNC_EN
				    : 0)
				 | ((mode->flags & DRM_MODE_FLAG_INTERLACE)
				    ? RADEON_CRTC_INTERLACE_EN
				    : 0));

		/* rs4xx chips seem to like to have the crtc enabled when the timing is set */
		अगर ((rdev->family == CHIP_RS400) || (rdev->family == CHIP_RS480))
			crtc_gen_cntl |= RADEON_CRTC_EN;

		crtc_ext_cntl = RREG32(RADEON_CRTC_EXT_CNTL);
		crtc_ext_cntl |= (RADEON_XCRT_CNT_EN |
				  RADEON_CRTC_VSYNC_DIS |
				  RADEON_CRTC_HSYNC_DIS |
				  RADEON_CRTC_DISPLAY_DIS);

		disp_merge_cntl = RREG32(RADEON_DISP_MERGE_CNTL);
		disp_merge_cntl &= ~RADEON_DISP_RGB_OFFSET_EN;

		WREG32(RADEON_DISP_MERGE_CNTL, disp_merge_cntl);
		WREG32(RADEON_CRTC_GEN_CNTL, crtc_gen_cntl);
		WREG32(RADEON_CRTC_EXT_CNTL, crtc_ext_cntl);
	पूर्ण

	अगर (is_tv)
		radeon_legacy_tv_adjust_crtc_reg(encoder, &crtc_h_total_disp,
						 &crtc_h_sync_strt_wid, &crtc_v_total_disp,
						 &crtc_v_sync_strt_wid);

	WREG32(RADEON_CRTC_H_TOTAL_DISP + radeon_crtc->crtc_offset, crtc_h_total_disp);
	WREG32(RADEON_CRTC_H_SYNC_STRT_WID + radeon_crtc->crtc_offset, crtc_h_sync_strt_wid);
	WREG32(RADEON_CRTC_V_TOTAL_DISP + radeon_crtc->crtc_offset, crtc_v_total_disp);
	WREG32(RADEON_CRTC_V_SYNC_STRT_WID + radeon_crtc->crtc_offset, crtc_v_sync_strt_wid);

	वापस true;
पूर्ण

अटल व्योम radeon_set_pll(काष्ठा drm_crtc *crtc, काष्ठा drm_display_mode *mode)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);
	काष्ठा drm_encoder *encoder;
	uपूर्णांक32_t feedback_भाग = 0;
	uपूर्णांक32_t frac_fb_भाग = 0;
	uपूर्णांक32_t reference_भाग = 0;
	uपूर्णांक32_t post_भागider = 0;
	uपूर्णांक32_t freq = 0;
	uपूर्णांक8_t pll_gain;
	bool use_bios_भागs = false;
	/* PLL रेजिस्टरs */
	uपूर्णांक32_t pll_ref_भाग = 0;
	uपूर्णांक32_t pll_fb_post_भाग = 0;
	uपूर्णांक32_t htotal_cntl = 0;
	bool is_tv = false;
	काष्ठा radeon_pll *pll;

	काष्ठा अणु
		पूर्णांक भागider;
		पूर्णांक bitvalue;
	पूर्ण *post_भाग, post_भागs[]   = अणु
		/* From RAGE 128 VR/RAGE 128 GL Register
		 * Reference Manual (Technical Reference
		 * Manual P/N RRG-G04100-C Rev. 0.04), page
		 * 3-17 (PLL_DIV_[3:0]).
		 */
		अणु  1, 0 पूर्ण,              /* VCLK_SRC                 */
		अणु  2, 1 पूर्ण,              /* VCLK_SRC/2               */
		अणु  4, 2 पूर्ण,              /* VCLK_SRC/4               */
		अणु  8, 3 पूर्ण,              /* VCLK_SRC/8               */
		अणु  3, 4 पूर्ण,              /* VCLK_SRC/3               */
		अणु 16, 5 पूर्ण,              /* VCLK_SRC/16              */
		अणु  6, 6 पूर्ण,              /* VCLK_SRC/6               */
		अणु 12, 7 पूर्ण,              /* VCLK_SRC/12              */
		अणु  0, 0 पूर्ण
	पूर्ण;

	अगर (radeon_crtc->crtc_id)
		pll = &rdev->घड़ी.p2pll;
	अन्यथा
		pll = &rdev->घड़ी.p1pll;

	pll->flags = RADEON_PLL_LEGACY;

	अगर (mode->घड़ी > 200000) /* range limits??? */
		pll->flags |= RADEON_PLL_PREFER_HIGH_FB_DIV;
	अन्यथा
		pll->flags |= RADEON_PLL_PREFER_LOW_REF_DIV;

	list_क्रम_each_entry(encoder, &dev->mode_config.encoder_list, head) अणु
		अगर (encoder->crtc == crtc) अणु
			काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);

			अगर (radeon_encoder->active_device & ATOM_DEVICE_TV_SUPPORT) अणु
				is_tv = true;
				अवरोध;
			पूर्ण

			अगर (encoder->encoder_type != DRM_MODE_ENCODER_DAC)
				pll->flags |= RADEON_PLL_NO_ODD_POST_DIV;
			अगर (encoder->encoder_type == DRM_MODE_ENCODER_LVDS) अणु
				अगर (!rdev->is_atom_bios) अणु
					काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
					काष्ठा radeon_encoder_lvds *lvds = (काष्ठा radeon_encoder_lvds *)radeon_encoder->enc_priv;
					अगर (lvds) अणु
						अगर (lvds->use_bios_भागiders) अणु
							pll_ref_भाग = lvds->panel_ref_भागider;
							pll_fb_post_भाग   = (lvds->panel_fb_भागider |
									     (lvds->panel_post_भागider << 16));
							htotal_cntl  = 0;
							use_bios_भागs = true;
						पूर्ण
					पूर्ण
				पूर्ण
				pll->flags |= RADEON_PLL_USE_REF_DIV;
			पूर्ण
		पूर्ण
	पूर्ण

	DRM_DEBUG_KMS("\n");

	अगर (!use_bios_भागs) अणु
		radeon_compute_pll_legacy(pll, mode->घड़ी,
					  &freq, &feedback_भाग, &frac_fb_भाग,
					  &reference_भाग, &post_भागider);

		क्रम (post_भाग = &post_भागs[0]; post_भाग->भागider; ++post_भाग) अणु
			अगर (post_भाग->भागider == post_भागider)
				अवरोध;
		पूर्ण

		अगर (!post_भाग->भागider)
			post_भाग = &post_भागs[0];

		DRM_DEBUG_KMS("dc=%u, fd=%d, rd=%d, pd=%d\n",
			  (अचिन्हित)freq,
			  feedback_भाग,
			  reference_भाग,
			  post_भागider);

		pll_ref_भाग   = reference_भाग;
#अगर defined(__घातerpc__) && (0) /* TODO */
		/* apparently programming this otherwise causes a hang??? */
		अगर (info->MacModel == RADEON_MAC_IBOOK)
			pll_fb_post_भाग = 0x000600ad;
		अन्यथा
#पूर्ण_अगर
			pll_fb_post_भाग     = (feedback_भाग | (post_भाग->bitvalue << 16));

		htotal_cntl    = mode->htotal & 0x7;

	पूर्ण

	pll_gain = radeon_compute_pll_gain(pll->reference_freq,
					   pll_ref_भाग & 0x3ff,
					   pll_fb_post_भाग & 0x7ff);

	अगर (radeon_crtc->crtc_id) अणु
		uपूर्णांक32_t pixclks_cntl = ((RREG32_PLL(RADEON_PIXCLKS_CNTL) &
					  ~(RADEON_PIX2CLK_SRC_SEL_MASK)) |
					 RADEON_PIX2CLK_SRC_SEL_P2PLLCLK);

		अगर (is_tv) अणु
			radeon_legacy_tv_adjust_pll2(encoder, &htotal_cntl,
						     &pll_ref_भाग, &pll_fb_post_भाग,
						     &pixclks_cntl);
		पूर्ण

		WREG32_PLL_P(RADEON_PIXCLKS_CNTL,
			     RADEON_PIX2CLK_SRC_SEL_CPUCLK,
			     ~(RADEON_PIX2CLK_SRC_SEL_MASK));

		WREG32_PLL_P(RADEON_P2PLL_CNTL,
			     RADEON_P2PLL_RESET
			     | RADEON_P2PLL_ATOMIC_UPDATE_EN
			     | ((uपूर्णांक32_t)pll_gain << RADEON_P2PLL_PVG_SHIFT),
			     ~(RADEON_P2PLL_RESET
			       | RADEON_P2PLL_ATOMIC_UPDATE_EN
			       | RADEON_P2PLL_PVG_MASK));

		WREG32_PLL_P(RADEON_P2PLL_REF_DIV,
			     pll_ref_भाग,
			     ~RADEON_P2PLL_REF_DIV_MASK);

		WREG32_PLL_P(RADEON_P2PLL_DIV_0,
			     pll_fb_post_भाग,
			     ~RADEON_P2PLL_FB0_DIV_MASK);

		WREG32_PLL_P(RADEON_P2PLL_DIV_0,
			     pll_fb_post_भाग,
			     ~RADEON_P2PLL_POST0_DIV_MASK);

		radeon_pll2_ग_लिखो_update(dev);
		radeon_pll2_रुको_क्रम_पढ़ो_update_complete(dev);

		WREG32_PLL(RADEON_HTOTAL2_CNTL, htotal_cntl);

		WREG32_PLL_P(RADEON_P2PLL_CNTL,
			     0,
			     ~(RADEON_P2PLL_RESET
			       | RADEON_P2PLL_SLEEP
			       | RADEON_P2PLL_ATOMIC_UPDATE_EN));

		DRM_DEBUG_KMS("Wrote2: 0x%08x 0x%08x 0x%08x (0x%08x)\n",
			  (अचिन्हित)pll_ref_भाग,
			  (अचिन्हित)pll_fb_post_भाग,
			  (अचिन्हित)htotal_cntl,
			  RREG32_PLL(RADEON_P2PLL_CNTL));
		DRM_DEBUG_KMS("Wrote2: rd=%u, fd=%u, pd=%u\n",
			  (अचिन्हित)pll_ref_भाग & RADEON_P2PLL_REF_DIV_MASK,
			  (अचिन्हित)pll_fb_post_भाग & RADEON_P2PLL_FB0_DIV_MASK,
			  (अचिन्हित)((pll_fb_post_भाग &
				      RADEON_P2PLL_POST0_DIV_MASK) >> 16));

		mdelay(50); /* Let the घड़ी to lock */

		WREG32_PLL_P(RADEON_PIXCLKS_CNTL,
			     RADEON_PIX2CLK_SRC_SEL_P2PLLCLK,
			     ~(RADEON_PIX2CLK_SRC_SEL_MASK));

		WREG32_PLL(RADEON_PIXCLKS_CNTL, pixclks_cntl);
	पूर्ण अन्यथा अणु
		uपूर्णांक32_t pixclks_cntl;


		अगर (is_tv) अणु
			pixclks_cntl = RREG32_PLL(RADEON_PIXCLKS_CNTL);
			radeon_legacy_tv_adjust_pll1(encoder, &htotal_cntl, &pll_ref_भाग,
						     &pll_fb_post_भाग, &pixclks_cntl);
		पूर्ण

		अगर (rdev->flags & RADEON_IS_MOBILITY) अणु
			/* A temporal workaround क्रम the occasional blanking on certain laptop panels.
			   This appears to related to the PLL भागider रेजिस्टरs (fail to lock?).
			   It occurs even when all भागiders are the same with their old settings.
			   In this हाल we really करोn't need to fiddle with PLL रेजिस्टरs.
			   By करोing this we can aव्योम the blanking problem with some panels.
			*/
			अगर ((pll_ref_भाग == (RREG32_PLL(RADEON_PPLL_REF_DIV) & RADEON_PPLL_REF_DIV_MASK)) &&
			    (pll_fb_post_भाग == (RREG32_PLL(RADEON_PPLL_DIV_3) &
						 (RADEON_PPLL_POST3_DIV_MASK | RADEON_PPLL_FB3_DIV_MASK)))) अणु
				WREG32_P(RADEON_CLOCK_CNTL_INDEX,
					 RADEON_PLL_DIV_SEL,
					 ~(RADEON_PLL_DIV_SEL));
				r100_pll_errata_after_index(rdev);
				वापस;
			पूर्ण
		पूर्ण

		WREG32_PLL_P(RADEON_VCLK_ECP_CNTL,
			     RADEON_VCLK_SRC_SEL_CPUCLK,
			     ~(RADEON_VCLK_SRC_SEL_MASK));
		WREG32_PLL_P(RADEON_PPLL_CNTL,
			     RADEON_PPLL_RESET
			     | RADEON_PPLL_ATOMIC_UPDATE_EN
			     | RADEON_PPLL_VGA_ATOMIC_UPDATE_EN
			     | ((uपूर्णांक32_t)pll_gain << RADEON_PPLL_PVG_SHIFT),
			     ~(RADEON_PPLL_RESET
			       | RADEON_PPLL_ATOMIC_UPDATE_EN
			       | RADEON_PPLL_VGA_ATOMIC_UPDATE_EN
			       | RADEON_PPLL_PVG_MASK));

		WREG32_P(RADEON_CLOCK_CNTL_INDEX,
			 RADEON_PLL_DIV_SEL,
			 ~(RADEON_PLL_DIV_SEL));
		r100_pll_errata_after_index(rdev);

		अगर (ASIC_IS_R300(rdev) ||
		    (rdev->family == CHIP_RS300) ||
		    (rdev->family == CHIP_RS400) ||
		    (rdev->family == CHIP_RS480)) अणु
			अगर (pll_ref_भाग & R300_PPLL_REF_DIV_ACC_MASK) अणु
				/* When restoring console mode, use saved PPLL_REF_DIV
				 * setting.
				 */
				WREG32_PLL_P(RADEON_PPLL_REF_DIV,
					     pll_ref_भाग,
					     0);
			पूर्ण अन्यथा अणु
				/* R300 uses ref_भाग_acc field as real ref भागider */
				WREG32_PLL_P(RADEON_PPLL_REF_DIV,
					     (pll_ref_भाग << R300_PPLL_REF_DIV_ACC_SHIFT),
					     ~R300_PPLL_REF_DIV_ACC_MASK);
			पूर्ण
		पूर्ण अन्यथा
			WREG32_PLL_P(RADEON_PPLL_REF_DIV,
				     pll_ref_भाग,
				     ~RADEON_PPLL_REF_DIV_MASK);

		WREG32_PLL_P(RADEON_PPLL_DIV_3,
			     pll_fb_post_भाग,
			     ~RADEON_PPLL_FB3_DIV_MASK);

		WREG32_PLL_P(RADEON_PPLL_DIV_3,
			     pll_fb_post_भाग,
			     ~RADEON_PPLL_POST3_DIV_MASK);

		radeon_pll_ग_लिखो_update(dev);
		radeon_pll_रुको_क्रम_पढ़ो_update_complete(dev);

		WREG32_PLL(RADEON_HTOTAL_CNTL, htotal_cntl);

		WREG32_PLL_P(RADEON_PPLL_CNTL,
			     0,
			     ~(RADEON_PPLL_RESET
			       | RADEON_PPLL_SLEEP
			       | RADEON_PPLL_ATOMIC_UPDATE_EN
			       | RADEON_PPLL_VGA_ATOMIC_UPDATE_EN));

		DRM_DEBUG_KMS("Wrote: 0x%08x 0x%08x 0x%08x (0x%08x)\n",
			  pll_ref_भाग,
			  pll_fb_post_भाग,
			  (अचिन्हित)htotal_cntl,
			  RREG32_PLL(RADEON_PPLL_CNTL));
		DRM_DEBUG_KMS("Wrote: rd=%d, fd=%d, pd=%d\n",
			  pll_ref_भाग & RADEON_PPLL_REF_DIV_MASK,
			  pll_fb_post_भाग & RADEON_PPLL_FB3_DIV_MASK,
			  (pll_fb_post_भाग & RADEON_PPLL_POST3_DIV_MASK) >> 16);

		mdelay(50); /* Let the घड़ी to lock */

		WREG32_PLL_P(RADEON_VCLK_ECP_CNTL,
			     RADEON_VCLK_SRC_SEL_PPLLCLK,
			     ~(RADEON_VCLK_SRC_SEL_MASK));

		अगर (is_tv)
			WREG32_PLL(RADEON_PIXCLKS_CNTL, pixclks_cntl);
	पूर्ण
पूर्ण

अटल bool radeon_crtc_mode_fixup(काष्ठा drm_crtc *crtc,
				   स्थिर काष्ठा drm_display_mode *mode,
				   काष्ठा drm_display_mode *adjusted_mode)
अणु
	अगर (!radeon_crtc_scaling_mode_fixup(crtc, mode, adjusted_mode))
		वापस false;
	वापस true;
पूर्ण

अटल पूर्णांक radeon_crtc_mode_set(काष्ठा drm_crtc *crtc,
				 काष्ठा drm_display_mode *mode,
				 काष्ठा drm_display_mode *adjusted_mode,
				 पूर्णांक x, पूर्णांक y, काष्ठा drm_framebuffer *old_fb)
अणु
	काष्ठा radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);

	/* TODO TV */
	radeon_crtc_set_base(crtc, x, y, old_fb);
	radeon_set_crtc_timing(crtc, adjusted_mode);
	radeon_set_pll(crtc, adjusted_mode);
	radeon_overscan_setup(crtc, adjusted_mode);
	अगर (radeon_crtc->crtc_id == 0) अणु
		radeon_legacy_rmx_mode_set(crtc, adjusted_mode);
	पूर्ण अन्यथा अणु
		अगर (radeon_crtc->rmx_type != RMX_OFF) अणु
			/* FIXME: only first crtc has rmx what should we
			 * करो ?
			 */
			DRM_ERROR("Mode need scaling but only first crtc can do that.\n");
		पूर्ण
	पूर्ण
	radeon_cursor_reset(crtc);
	वापस 0;
पूर्ण

अटल व्योम radeon_crtc_prepare(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा drm_crtc *crtci;

	/*
	* The hardware wedges someबार अगर you reconfigure one CRTC
	* whilst another is running (see fकरो bug #24611).
	*/
	list_क्रम_each_entry(crtci, &dev->mode_config.crtc_list, head)
		radeon_crtc_dpms(crtci, DRM_MODE_DPMS_OFF);
पूर्ण

अटल व्योम radeon_crtc_commit(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा drm_crtc *crtci;

	/*
	* Reenable the CRTCs that should be running.
	*/
	list_क्रम_each_entry(crtci, &dev->mode_config.crtc_list, head) अणु
		अगर (crtci->enabled)
			radeon_crtc_dpms(crtci, DRM_MODE_DPMS_ON);
	पूर्ण
पूर्ण

अटल व्योम radeon_crtc_disable(काष्ठा drm_crtc *crtc)
अणु
	radeon_crtc_dpms(crtc, DRM_MODE_DPMS_OFF);
	अगर (crtc->primary->fb) अणु
		पूर्णांक r;
		काष्ठा radeon_bo *rbo;

		rbo = gem_to_radeon_bo(crtc->primary->fb->obj[0]);
		r = radeon_bo_reserve(rbo, false);
		अगर (unlikely(r))
			DRM_ERROR("failed to reserve rbo before unpin\n");
		अन्यथा अणु
			radeon_bo_unpin(rbo);
			radeon_bo_unreserve(rbo);
		पूर्ण
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा drm_crtc_helper_funcs legacy_helper_funcs = अणु
	.dpms = radeon_crtc_dpms,
	.mode_fixup = radeon_crtc_mode_fixup,
	.mode_set = radeon_crtc_mode_set,
	.mode_set_base = radeon_crtc_set_base,
	.mode_set_base_atomic = radeon_crtc_set_base_atomic,
	.prepare = radeon_crtc_prepare,
	.commit = radeon_crtc_commit,
	.disable = radeon_crtc_disable,
	.get_scanout_position = radeon_get_crtc_scanout_position,
पूर्ण;


व्योम radeon_legacy_init_crtc(काष्ठा drm_device *dev,
			       काष्ठा radeon_crtc *radeon_crtc)
अणु
	अगर (radeon_crtc->crtc_id == 1)
		radeon_crtc->crtc_offset = RADEON_CRTC2_H_TOTAL_DISP - RADEON_CRTC_H_TOTAL_DISP;
	drm_crtc_helper_add(&radeon_crtc->base, &legacy_helper_funcs);
पूर्ण
