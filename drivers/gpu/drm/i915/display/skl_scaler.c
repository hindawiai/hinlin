<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2020 Intel Corporation
 */
#समावेश "intel_display_types.h"
#समावेश "skl_scaler.h"
#समावेश "skl_universal_plane.h"

/*
 * The hardware phase 0.0 refers to the center of the pixel.
 * We want to start from the top/left edge which is phase
 * -0.5. That matches how the hardware calculates the scaling
 * factors (from top-left of the first pixel to bottom-right
 * of the last pixel, as opposed to the pixel centers).
 *
 * For 4:2:0 subsampled chroma planes we obviously have to
 * adjust that so that the chroma sample position lands in
 * the right spot.
 *
 * Note that क्रम packed YCbCr 4:2:2 क्रमmats there is no way to
 * control chroma siting. The hardware simply replicates the
 * chroma samples क्रम both of the luma samples, and thus we करोn't
 * actually get the expected MPEG2 chroma siting convention :(
 * The same behaviour is observed on pre-SKL platक्रमms as well.
 *
 * Theory behind the क्रमmula (note that we ignore sub-pixel
 * source coordinates):
 * s = source sample position
 * d = destination sample position
 *
 * Downscaling 4:1:
 * -0.5
 * | 0.0
 * | |     1.5 (initial phase)
 * | |     |
 * v v     v
 * | s | s | s | s |
 * |       d       |
 *
 * Upscaling 1:4:
 * -0.5
 * | -0.375 (initial phase)
 * | |     0.0
 * | |     |
 * v v     v
 * |       s       |
 * | d | d | d | d |
 */
अटल u16 skl_scaler_calc_phase(पूर्णांक sub, पूर्णांक scale, bool chroma_cosited)
अणु
	पूर्णांक phase = -0x8000;
	u16 trip = 0;

	अगर (chroma_cosited)
		phase += (sub - 1) * 0x8000 / sub;

	phase += scale / (2 * sub);

	/*
	 * Hardware initial phase limited to [-0.5:1.5].
	 * Since the max hardware scale factor is 3.0, we
	 * should never actually excdeed 1.0 here.
	 */
	WARN_ON(phase < -0x8000 || phase > 0x18000);

	अगर (phase < 0)
		phase = 0x10000 + phase;
	अन्यथा
		trip = PS_PHASE_TRIP;

	वापस ((phase >> 2) & PS_PHASE_MASK) | trip;
पूर्ण

#घोषणा SKL_MIN_SRC_W 8
#घोषणा SKL_MAX_SRC_W 4096
#घोषणा SKL_MIN_SRC_H 8
#घोषणा SKL_MAX_SRC_H 4096
#घोषणा SKL_MIN_DST_W 8
#घोषणा SKL_MAX_DST_W 4096
#घोषणा SKL_MIN_DST_H 8
#घोषणा SKL_MAX_DST_H 4096
#घोषणा ICL_MAX_SRC_W 5120
#घोषणा ICL_MAX_SRC_H 4096
#घोषणा ICL_MAX_DST_W 5120
#घोषणा ICL_MAX_DST_H 4096
#घोषणा SKL_MIN_YUV_420_SRC_W 16
#घोषणा SKL_MIN_YUV_420_SRC_H 16

अटल पूर्णांक
skl_update_scaler(काष्ठा पूर्णांकel_crtc_state *crtc_state, bool क्रमce_detach,
		  अचिन्हित पूर्णांक scaler_user, पूर्णांक *scaler_id,
		  पूर्णांक src_w, पूर्णांक src_h, पूर्णांक dst_w, पूर्णांक dst_h,
		  स्थिर काष्ठा drm_क्रमmat_info *क्रमmat,
		  u64 modअगरier, bool need_scaler)
अणु
	काष्ठा पूर्णांकel_crtc_scaler_state *scaler_state =
		&crtc_state->scaler_state;
	काष्ठा पूर्णांकel_crtc *पूर्णांकel_crtc =
		to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(पूर्णांकel_crtc->base.dev);
	स्थिर काष्ठा drm_display_mode *adjusted_mode =
		&crtc_state->hw.adjusted_mode;

	/*
	 * Src coordinates are alपढ़ोy rotated by 270 degrees क्रम
	 * the 90/270 degree plane rotation हालs (to match the
	 * GTT mapping), hence no need to account क्रम rotation here.
	 */
	अगर (src_w != dst_w || src_h != dst_h)
		need_scaler = true;

	/*
	 * Scaling/fitting not supported in IF-ID mode in GEN9+
	 * TODO: Interlace fetch mode करोesn't support YUV420 planar क्रमmats.
	 * Once NV12 is enabled, handle it here जबतक allocating scaler
	 * क्रम NV12.
	 */
	अगर (DISPLAY_VER(dev_priv) >= 9 && crtc_state->hw.enable &&
	    need_scaler && adjusted_mode->flags & DRM_MODE_FLAG_INTERLACE) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "Pipe/Plane scaling not supported with IF-ID mode\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * अगर plane is being disabled or scaler is no more required or क्रमce detach
	 *  - मुक्त scaler binded to this plane/crtc
	 *  - in order to करो this, update crtc->scaler_usage
	 *
	 * Here scaler state in crtc_state is set मुक्त so that
	 * scaler can be asचिन्हित to other user. Actual रेजिस्टर
	 * update to मुक्त the scaler is करोne in plane/panel-fit programming.
	 * For this purpose crtc/plane_state->scaler_id isn't reset here.
	 */
	अगर (क्रमce_detach || !need_scaler) अणु
		अगर (*scaler_id >= 0) अणु
			scaler_state->scaler_users &= ~(1 << scaler_user);
			scaler_state->scalers[*scaler_id].in_use = 0;

			drm_dbg_kms(&dev_priv->drm,
				    "scaler_user index %u.%u: "
				    "Staged freeing scaler id %d scaler_users = 0x%x\n",
				    पूर्णांकel_crtc->pipe, scaler_user, *scaler_id,
				    scaler_state->scaler_users);
			*scaler_id = -1;
		पूर्ण
		वापस 0;
	पूर्ण

	अगर (क्रमmat && पूर्णांकel_क्रमmat_info_is_yuv_semiplanar(क्रमmat, modअगरier) &&
	    (src_h < SKL_MIN_YUV_420_SRC_H || src_w < SKL_MIN_YUV_420_SRC_W)) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "Planar YUV: src dimensions not met\n");
		वापस -EINVAL;
	पूर्ण

	/* range checks */
	अगर (src_w < SKL_MIN_SRC_W || src_h < SKL_MIN_SRC_H ||
	    dst_w < SKL_MIN_DST_W || dst_h < SKL_MIN_DST_H ||
	    (DISPLAY_VER(dev_priv) >= 11 &&
	     (src_w > ICL_MAX_SRC_W || src_h > ICL_MAX_SRC_H ||
	      dst_w > ICL_MAX_DST_W || dst_h > ICL_MAX_DST_H)) ||
	    (DISPLAY_VER(dev_priv) < 11 &&
	     (src_w > SKL_MAX_SRC_W || src_h > SKL_MAX_SRC_H ||
	      dst_w > SKL_MAX_DST_W || dst_h > SKL_MAX_DST_H)))	अणु
		drm_dbg_kms(&dev_priv->drm,
			    "scaler_user index %u.%u: src %ux%u dst %ux%u "
			    "size is out of scaler range\n",
			    पूर्णांकel_crtc->pipe, scaler_user, src_w, src_h,
			    dst_w, dst_h);
		वापस -EINVAL;
	पूर्ण

	/* mark this plane as a scaler user in crtc_state */
	scaler_state->scaler_users |= (1 << scaler_user);
	drm_dbg_kms(&dev_priv->drm, "scaler_user index %u.%u: "
		    "staged scaling request for %ux%u->%ux%u scaler_users = 0x%x\n",
		    पूर्णांकel_crtc->pipe, scaler_user, src_w, src_h, dst_w, dst_h,
		    scaler_state->scaler_users);

	वापस 0;
पूर्ण

पूर्णांक skl_update_scaler_crtc(काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	स्थिर काष्ठा drm_display_mode *pipe_mode = &crtc_state->hw.pipe_mode;
	पूर्णांक width, height;

	अगर (crtc_state->pch_pfit.enabled) अणु
		width = drm_rect_width(&crtc_state->pch_pfit.dst);
		height = drm_rect_height(&crtc_state->pch_pfit.dst);
	पूर्ण अन्यथा अणु
		width = pipe_mode->crtc_hdisplay;
		height = pipe_mode->crtc_vdisplay;
	पूर्ण
	वापस skl_update_scaler(crtc_state, !crtc_state->hw.active,
				 SKL_CRTC_INDEX,
				 &crtc_state->scaler_state.scaler_id,
				 crtc_state->pipe_src_w, crtc_state->pipe_src_h,
				 width, height, शून्य, 0,
				 crtc_state->pch_pfit.enabled);
पूर्ण

/**
 * skl_update_scaler_plane - Stages update to scaler state क्रम a given plane.
 * @crtc_state: crtc's scaler state
 * @plane_state: atomic plane state to update
 *
 * Return
 *     0 - scaler_usage updated successfully
 *    error - requested scaling cannot be supported or other error condition
 */
पूर्णांक skl_update_scaler_plane(काष्ठा पूर्णांकel_crtc_state *crtc_state,
			    काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	काष्ठा पूर्णांकel_plane *पूर्णांकel_plane =
		to_पूर्णांकel_plane(plane_state->uapi.plane);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(पूर्णांकel_plane->base.dev);
	काष्ठा drm_framebuffer *fb = plane_state->hw.fb;
	पूर्णांक ret;
	bool क्रमce_detach = !fb || !plane_state->uapi.visible;
	bool need_scaler = false;

	/* Pre-gen11 and SDR planes always need a scaler क्रम planar क्रमmats. */
	अगर (!icl_is_hdr_plane(dev_priv, पूर्णांकel_plane->id) &&
	    fb && पूर्णांकel_क्रमmat_info_is_yuv_semiplanar(fb->क्रमmat, fb->modअगरier))
		need_scaler = true;

	ret = skl_update_scaler(crtc_state, क्रमce_detach,
				drm_plane_index(&पूर्णांकel_plane->base),
				&plane_state->scaler_id,
				drm_rect_width(&plane_state->uapi.src) >> 16,
				drm_rect_height(&plane_state->uapi.src) >> 16,
				drm_rect_width(&plane_state->uapi.dst),
				drm_rect_height(&plane_state->uapi.dst),
				fb ? fb->क्रमmat : शून्य,
				fb ? fb->modअगरier : 0,
				need_scaler);

	अगर (ret || plane_state->scaler_id < 0)
		वापस ret;

	/* check colorkey */
	अगर (plane_state->ckey.flags) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "[PLANE:%d:%s] scaling with color key not allowed",
			    पूर्णांकel_plane->base.base.id,
			    पूर्णांकel_plane->base.name);
		वापस -EINVAL;
	पूर्ण

	/* Check src क्रमmat */
	चयन (fb->क्रमmat->क्रमmat) अणु
	हाल DRM_FORMAT_RGB565:
	हाल DRM_FORMAT_XBGR8888:
	हाल DRM_FORMAT_XRGB8888:
	हाल DRM_FORMAT_ABGR8888:
	हाल DRM_FORMAT_ARGB8888:
	हाल DRM_FORMAT_XRGB2101010:
	हाल DRM_FORMAT_XBGR2101010:
	हाल DRM_FORMAT_ARGB2101010:
	हाल DRM_FORMAT_ABGR2101010:
	हाल DRM_FORMAT_YUYV:
	हाल DRM_FORMAT_YVYU:
	हाल DRM_FORMAT_UYVY:
	हाल DRM_FORMAT_VYUY:
	हाल DRM_FORMAT_NV12:
	हाल DRM_FORMAT_XYUV8888:
	हाल DRM_FORMAT_P010:
	हाल DRM_FORMAT_P012:
	हाल DRM_FORMAT_P016:
	हाल DRM_FORMAT_Y210:
	हाल DRM_FORMAT_Y212:
	हाल DRM_FORMAT_Y216:
	हाल DRM_FORMAT_XVYU2101010:
	हाल DRM_FORMAT_XVYU12_16161616:
	हाल DRM_FORMAT_XVYU16161616:
		अवरोध;
	हाल DRM_FORMAT_XBGR16161616F:
	हाल DRM_FORMAT_ABGR16161616F:
	हाल DRM_FORMAT_XRGB16161616F:
	हाल DRM_FORMAT_ARGB16161616F:
		अगर (DISPLAY_VER(dev_priv) >= 11)
			अवरोध;
		fallthrough;
	शेष:
		drm_dbg_kms(&dev_priv->drm,
			    "[PLANE:%d:%s] FB:%d unsupported scaling format 0x%x\n",
			    पूर्णांकel_plane->base.base.id, पूर्णांकel_plane->base.name,
			    fb->base.id, fb->क्रमmat->क्रमmat);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cnl_coef_tap(पूर्णांक i)
अणु
	वापस i % 7;
पूर्ण

अटल u16 cnl_nearest_filter_coef(पूर्णांक t)
अणु
	वापस t == 3 ? 0x0800 : 0x3000;
पूर्ण

/*
 *  Theory behind setting nearest-neighbor पूर्णांकeger scaling:
 *
 *  17 phase of 7 taps requires 119 coefficients in 60 dwords per set.
 *  The letter represents the filter tap (D is the center tap) and the number
 *  represents the coefficient set क्रम a phase (0-16).
 *
 *         +------------+------------------------+------------------------+
 *         |Index value | Data value coeffient 1 | Data value coeffient 2 |
 *         +------------+------------------------+------------------------+
 *         |   00h      |          B0            |          A0            |
 *         +------------+------------------------+------------------------+
 *         |   01h      |          D0            |          C0            |
 *         +------------+------------------------+------------------------+
 *         |   02h      |          F0            |          E0            |
 *         +------------+------------------------+------------------------+
 *         |   03h      |          A1            |          G0            |
 *         +------------+------------------------+------------------------+
 *         |   04h      |          C1            |          B1            |
 *         +------------+------------------------+------------------------+
 *         |   ...      |          ...           |          ...           |
 *         +------------+------------------------+------------------------+
 *         |   38h      |          B16           |          A16           |
 *         +------------+------------------------+------------------------+
 *         |   39h      |          D16           |          C16           |
 *         +------------+------------------------+------------------------+
 *         |   3Ah      |          F16           |          C16           |
 *         +------------+------------------------+------------------------+
 *         |   3Bh      |        Reserved        |          G16           |
 *         +------------+------------------------+------------------------+
 *
 *  To enable nearest-neighbor scaling:  program scaler coefficents with
 *  the center tap (Dxx) values set to 1 and all other values set to 0 as per
 *  SCALER_COEFFICIENT_FORMAT
 *
 */

अटल व्योम cnl_program_nearest_filter_coefs(काष्ठा drm_i915_निजी *dev_priv,
					     क्रमागत pipe pipe, पूर्णांक id, पूर्णांक set)
अणु
	पूर्णांक i;

	पूर्णांकel_de_ग_लिखो_fw(dev_priv, CNL_PS_COEF_INDEX_SET(pipe, id, set),
			  PS_COEE_INDEX_AUTO_INC);

	क्रम (i = 0; i < 17 * 7; i += 2) अणु
		u32 पंचांगp;
		पूर्णांक t;

		t = cnl_coef_tap(i);
		पंचांगp = cnl_nearest_filter_coef(t);

		t = cnl_coef_tap(i + 1);
		पंचांगp |= cnl_nearest_filter_coef(t) << 16;

		पूर्णांकel_de_ग_लिखो_fw(dev_priv, CNL_PS_COEF_DATA_SET(pipe, id, set),
				  पंचांगp);
	पूर्ण

	पूर्णांकel_de_ग_लिखो_fw(dev_priv, CNL_PS_COEF_INDEX_SET(pipe, id, set), 0);
पूर्ण

अटल u32 skl_scaler_get_filter_select(क्रमागत drm_scaling_filter filter, पूर्णांक set)
अणु
	अगर (filter == DRM_SCALING_FILTER_NEAREST_NEIGHBOR) अणु
		वापस (PS_FILTER_PROGRAMMED |
			PS_Y_VERT_FILTER_SELECT(set) |
			PS_Y_HORZ_FILTER_SELECT(set) |
			PS_UV_VERT_FILTER_SELECT(set) |
			PS_UV_HORZ_FILTER_SELECT(set));
	पूर्ण

	वापस PS_FILTER_MEDIUM;
पूर्ण

अटल व्योम skl_scaler_setup_filter(काष्ठा drm_i915_निजी *dev_priv, क्रमागत pipe pipe,
				    पूर्णांक id, पूर्णांक set, क्रमागत drm_scaling_filter filter)
अणु
	चयन (filter) अणु
	हाल DRM_SCALING_FILTER_DEFAULT:
		अवरोध;
	हाल DRM_SCALING_FILTER_NEAREST_NEIGHBOR:
		cnl_program_nearest_filter_coefs(dev_priv, pipe, id, set);
		अवरोध;
	शेष:
		MISSING_CASE(filter);
	पूर्ण
पूर्ण

व्योम skl_pfit_enable(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	स्थिर काष्ठा पूर्णांकel_crtc_scaler_state *scaler_state =
		&crtc_state->scaler_state;
	काष्ठा drm_rect src = अणु
		.x2 = crtc_state->pipe_src_w << 16,
		.y2 = crtc_state->pipe_src_h << 16,
	पूर्ण;
	स्थिर काष्ठा drm_rect *dst = &crtc_state->pch_pfit.dst;
	u16 uv_rgb_hphase, uv_rgb_vphase;
	क्रमागत pipe pipe = crtc->pipe;
	पूर्णांक width = drm_rect_width(dst);
	पूर्णांक height = drm_rect_height(dst);
	पूर्णांक x = dst->x1;
	पूर्णांक y = dst->y1;
	पूर्णांक hscale, vscale;
	अचिन्हित दीर्घ irqflags;
	पूर्णांक id;
	u32 ps_ctrl;

	अगर (!crtc_state->pch_pfit.enabled)
		वापस;

	अगर (drm_WARN_ON(&dev_priv->drm,
			crtc_state->scaler_state.scaler_id < 0))
		वापस;

	hscale = drm_rect_calc_hscale(&src, dst, 0, पूर्णांक_उच्च);
	vscale = drm_rect_calc_vscale(&src, dst, 0, पूर्णांक_उच्च);

	uv_rgb_hphase = skl_scaler_calc_phase(1, hscale, false);
	uv_rgb_vphase = skl_scaler_calc_phase(1, vscale, false);

	id = scaler_state->scaler_id;

	ps_ctrl = skl_scaler_get_filter_select(crtc_state->hw.scaling_filter, 0);
	ps_ctrl |=  PS_SCALER_EN | scaler_state->scalers[id].mode;

	spin_lock_irqsave(&dev_priv->uncore.lock, irqflags);

	skl_scaler_setup_filter(dev_priv, pipe, id, 0,
				crtc_state->hw.scaling_filter);

	पूर्णांकel_de_ग_लिखो_fw(dev_priv, SKL_PS_CTRL(pipe, id), ps_ctrl);

	पूर्णांकel_de_ग_लिखो_fw(dev_priv, SKL_PS_VPHASE(pipe, id),
			  PS_Y_PHASE(0) | PS_UV_RGB_PHASE(uv_rgb_vphase));
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, SKL_PS_HPHASE(pipe, id),
			  PS_Y_PHASE(0) | PS_UV_RGB_PHASE(uv_rgb_hphase));
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, SKL_PS_WIN_POS(pipe, id),
			  x << 16 | y);
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, SKL_PS_WIN_SZ(pipe, id),
			  width << 16 | height);

	spin_unlock_irqrestore(&dev_priv->uncore.lock, irqflags);
पूर्ण

व्योम
skl_program_plane_scaler(काष्ठा पूर्णांकel_plane *plane,
			 स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			 स्थिर काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(plane->base.dev);
	स्थिर काष्ठा drm_framebuffer *fb = plane_state->hw.fb;
	क्रमागत pipe pipe = plane->pipe;
	पूर्णांक scaler_id = plane_state->scaler_id;
	स्थिर काष्ठा पूर्णांकel_scaler *scaler =
		&crtc_state->scaler_state.scalers[scaler_id];
	पूर्णांक crtc_x = plane_state->uapi.dst.x1;
	पूर्णांक crtc_y = plane_state->uapi.dst.y1;
	u32 crtc_w = drm_rect_width(&plane_state->uapi.dst);
	u32 crtc_h = drm_rect_height(&plane_state->uapi.dst);
	u16 y_hphase, uv_rgb_hphase;
	u16 y_vphase, uv_rgb_vphase;
	पूर्णांक hscale, vscale;
	u32 ps_ctrl;

	hscale = drm_rect_calc_hscale(&plane_state->uapi.src,
				      &plane_state->uapi.dst,
				      0, पूर्णांक_उच्च);
	vscale = drm_rect_calc_vscale(&plane_state->uapi.src,
				      &plane_state->uapi.dst,
				      0, पूर्णांक_उच्च);

	/* TODO: handle sub-pixel coordinates */
	अगर (पूर्णांकel_क्रमmat_info_is_yuv_semiplanar(fb->क्रमmat, fb->modअगरier) &&
	    !icl_is_hdr_plane(dev_priv, plane->id)) अणु
		y_hphase = skl_scaler_calc_phase(1, hscale, false);
		y_vphase = skl_scaler_calc_phase(1, vscale, false);

		/* MPEG2 chroma siting convention */
		uv_rgb_hphase = skl_scaler_calc_phase(2, hscale, true);
		uv_rgb_vphase = skl_scaler_calc_phase(2, vscale, false);
	पूर्ण अन्यथा अणु
		/* not used */
		y_hphase = 0;
		y_vphase = 0;

		uv_rgb_hphase = skl_scaler_calc_phase(1, hscale, false);
		uv_rgb_vphase = skl_scaler_calc_phase(1, vscale, false);
	पूर्ण

	ps_ctrl = skl_scaler_get_filter_select(plane_state->hw.scaling_filter, 0);
	ps_ctrl |= PS_SCALER_EN | PS_PLANE_SEL(plane->id) | scaler->mode;

	skl_scaler_setup_filter(dev_priv, pipe, scaler_id, 0,
				plane_state->hw.scaling_filter);

	पूर्णांकel_de_ग_लिखो_fw(dev_priv, SKL_PS_CTRL(pipe, scaler_id), ps_ctrl);
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, SKL_PS_VPHASE(pipe, scaler_id),
			  PS_Y_PHASE(y_vphase) | PS_UV_RGB_PHASE(uv_rgb_vphase));
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, SKL_PS_HPHASE(pipe, scaler_id),
			  PS_Y_PHASE(y_hphase) | PS_UV_RGB_PHASE(uv_rgb_hphase));
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, SKL_PS_WIN_POS(pipe, scaler_id),
			  (crtc_x << 16) | crtc_y);
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, SKL_PS_WIN_SZ(pipe, scaler_id),
			  (crtc_w << 16) | crtc_h);
पूर्ण

अटल व्योम skl_detach_scaler(काष्ठा पूर्णांकel_crtc *पूर्णांकel_crtc, पूर्णांक id)
अणु
	काष्ठा drm_device *dev = पूर्णांकel_crtc->base.dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	अचिन्हित दीर्घ irqflags;

	spin_lock_irqsave(&dev_priv->uncore.lock, irqflags);

	पूर्णांकel_de_ग_लिखो_fw(dev_priv, SKL_PS_CTRL(पूर्णांकel_crtc->pipe, id), 0);
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, SKL_PS_WIN_POS(पूर्णांकel_crtc->pipe, id), 0);
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, SKL_PS_WIN_SZ(पूर्णांकel_crtc->pipe, id), 0);

	spin_unlock_irqrestore(&dev_priv->uncore.lock, irqflags);
पूर्ण

/*
 * This function detaches (aka. unbinds) unused scalers in hardware
 */
व्योम skl_detach_scalers(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *पूर्णांकel_crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	स्थिर काष्ठा पूर्णांकel_crtc_scaler_state *scaler_state =
		&crtc_state->scaler_state;
	पूर्णांक i;

	/* loop through and disable scalers that aren't in use */
	क्रम (i = 0; i < पूर्णांकel_crtc->num_scalers; i++) अणु
		अगर (!scaler_state->scalers[i].in_use)
			skl_detach_scaler(पूर्णांकel_crtc, i);
	पूर्ण
पूर्ण

व्योम skl_scaler_disable(स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(old_crtc_state->uapi.crtc);
	पूर्णांक i;

	क्रम (i = 0; i < crtc->num_scalers; i++)
		skl_detach_scaler(crtc, i);
पूर्ण
