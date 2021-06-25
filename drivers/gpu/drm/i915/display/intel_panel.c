<शैली गुरु>
/*
 * Copyright तऊ 2006-2010 Intel Corporation
 * Copyright (c) 2006 Dave Airlie <airlied@linux.ie>
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * Authors:
 *	Eric Anholt <eric@anholt.net>
 *      Dave Airlie <airlied@linux.ie>
 *      Jesse Barnes <jesse.barnes@पूर्णांकel.com>
 *      Chris Wilson <chris@chris-wilson.co.uk>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/pwm.h>

#समावेश "intel_connector.h"
#समावेश "intel_display_types.h"
#समावेश "intel_dp_aux_backlight.h"
#समावेश "intel_dsi_dcs_backlight.h"
#समावेश "intel_panel.h"

व्योम
पूर्णांकel_fixed_panel_mode(स्थिर काष्ठा drm_display_mode *fixed_mode,
		       काष्ठा drm_display_mode *adjusted_mode)
अणु
	drm_mode_copy(adjusted_mode, fixed_mode);

	drm_mode_set_crtcinfo(adjusted_mode, 0);
पूर्ण

अटल bool is_करोwnघड़ी_mode(स्थिर काष्ठा drm_display_mode *करोwnघड़ी_mode,
			      स्थिर काष्ठा drm_display_mode *fixed_mode)
अणु
	वापस drm_mode_match(करोwnघड़ी_mode, fixed_mode,
			      DRM_MODE_MATCH_TIMINGS |
			      DRM_MODE_MATCH_FLAGS |
			      DRM_MODE_MATCH_3D_FLAGS) &&
		करोwnघड़ी_mode->घड़ी < fixed_mode->घड़ी;
पूर्ण

काष्ठा drm_display_mode *
पूर्णांकel_panel_edid_करोwnघड़ी_mode(काष्ठा पूर्णांकel_connector *connector,
				स्थिर काष्ठा drm_display_mode *fixed_mode)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	स्थिर काष्ठा drm_display_mode *scan, *best_mode = शून्य;
	काष्ठा drm_display_mode *करोwnघड़ी_mode;
	पूर्णांक best_घड़ी = fixed_mode->घड़ी;

	list_क्रम_each_entry(scan, &connector->base.probed_modes, head) अणु
		/*
		 * If one mode has the same resolution with the fixed_panel
		 * mode जबतक they have the dअगरferent refresh rate, it means
		 * that the reduced करोwnघड़ी is found. In such
		 * हाल we can set the dअगरferent FPx0/1 to dynamically select
		 * between low and high frequency.
		 */
		अगर (is_करोwnघड़ी_mode(scan, fixed_mode) &&
		    scan->घड़ी < best_घड़ी) अणु
			/*
			 * The करोwnघड़ी is alपढ़ोy found. But we
			 * expect to find the lower करोwnघड़ी.
			 */
			best_घड़ी = scan->घड़ी;
			best_mode = scan;
		पूर्ण
	पूर्ण

	अगर (!best_mode)
		वापस शून्य;

	करोwnघड़ी_mode = drm_mode_duplicate(&dev_priv->drm, best_mode);
	अगर (!करोwnघड़ी_mode)
		वापस शून्य;

	drm_dbg_kms(&dev_priv->drm,
		    "[CONNECTOR:%d:%s] using downclock mode from EDID: ",
		    connector->base.base.id, connector->base.name);
	drm_mode_debug_prपूर्णांकmodeline(करोwnघड़ी_mode);

	वापस करोwnघड़ी_mode;
पूर्ण

काष्ठा drm_display_mode *
पूर्णांकel_panel_edid_fixed_mode(काष्ठा पूर्णांकel_connector *connector)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	स्थिर काष्ठा drm_display_mode *scan;
	काष्ठा drm_display_mode *fixed_mode;

	अगर (list_empty(&connector->base.probed_modes))
		वापस शून्य;

	/* prefer fixed mode from EDID अगर available */
	list_क्रम_each_entry(scan, &connector->base.probed_modes, head) अणु
		अगर ((scan->type & DRM_MODE_TYPE_PREFERRED) == 0)
			जारी;

		fixed_mode = drm_mode_duplicate(&dev_priv->drm, scan);
		अगर (!fixed_mode)
			वापस शून्य;

		drm_dbg_kms(&dev_priv->drm,
			    "[CONNECTOR:%d:%s] using preferred mode from EDID: ",
			    connector->base.base.id, connector->base.name);
		drm_mode_debug_prपूर्णांकmodeline(fixed_mode);

		वापस fixed_mode;
	पूर्ण

	scan = list_first_entry(&connector->base.probed_modes,
				typeof(*scan), head);

	fixed_mode = drm_mode_duplicate(&dev_priv->drm, scan);
	अगर (!fixed_mode)
		वापस शून्य;

	fixed_mode->type |= DRM_MODE_TYPE_PREFERRED;

	drm_dbg_kms(&dev_priv->drm,
		    "[CONNECTOR:%d:%s] using first mode from EDID: ",
		    connector->base.base.id, connector->base.name);
	drm_mode_debug_prपूर्णांकmodeline(fixed_mode);

	वापस fixed_mode;
पूर्ण

काष्ठा drm_display_mode *
पूर्णांकel_panel_vbt_fixed_mode(काष्ठा पूर्णांकel_connector *connector)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	काष्ठा drm_display_info *info = &connector->base.display_info;
	काष्ठा drm_display_mode *fixed_mode;

	अगर (!dev_priv->vbt.lfp_lvds_vbt_mode)
		वापस शून्य;

	fixed_mode = drm_mode_duplicate(&dev_priv->drm,
					dev_priv->vbt.lfp_lvds_vbt_mode);
	अगर (!fixed_mode)
		वापस शून्य;

	fixed_mode->type |= DRM_MODE_TYPE_PREFERRED;

	drm_dbg_kms(&dev_priv->drm, "[CONNECTOR:%d:%s] using mode from VBT: ",
		    connector->base.base.id, connector->base.name);
	drm_mode_debug_prपूर्णांकmodeline(fixed_mode);

	info->width_mm = fixed_mode->width_mm;
	info->height_mm = fixed_mode->height_mm;

	वापस fixed_mode;
पूर्ण

/* adjusted_mode has been preset to be the panel's fixed mode */
पूर्णांक पूर्णांकel_pch_panel_fitting(काष्ठा पूर्णांकel_crtc_state *crtc_state,
			    स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	स्थिर काष्ठा drm_display_mode *adjusted_mode =
		&crtc_state->hw.adjusted_mode;
	पूर्णांक x, y, width, height;

	/* Native modes करोn't need fitting */
	अगर (adjusted_mode->crtc_hdisplay == crtc_state->pipe_src_w &&
	    adjusted_mode->crtc_vdisplay == crtc_state->pipe_src_h &&
	    crtc_state->output_क्रमmat != INTEL_OUTPUT_FORMAT_YCBCR420)
		वापस 0;

	चयन (conn_state->scaling_mode) अणु
	हाल DRM_MODE_SCALE_CENTER:
		width = crtc_state->pipe_src_w;
		height = crtc_state->pipe_src_h;
		x = (adjusted_mode->crtc_hdisplay - width + 1)/2;
		y = (adjusted_mode->crtc_vdisplay - height + 1)/2;
		अवरोध;

	हाल DRM_MODE_SCALE_ASPECT:
		/* Scale but preserve the aspect ratio */
		अणु
			u32 scaled_width = adjusted_mode->crtc_hdisplay
				* crtc_state->pipe_src_h;
			u32 scaled_height = crtc_state->pipe_src_w
				* adjusted_mode->crtc_vdisplay;
			अगर (scaled_width > scaled_height) अणु /* pillar */
				width = scaled_height / crtc_state->pipe_src_h;
				अगर (width & 1)
					width++;
				x = (adjusted_mode->crtc_hdisplay - width + 1) / 2;
				y = 0;
				height = adjusted_mode->crtc_vdisplay;
			पूर्ण अन्यथा अगर (scaled_width < scaled_height) अणु /* letter */
				height = scaled_width / crtc_state->pipe_src_w;
				अगर (height & 1)
				    height++;
				y = (adjusted_mode->crtc_vdisplay - height + 1) / 2;
				x = 0;
				width = adjusted_mode->crtc_hdisplay;
			पूर्ण अन्यथा अणु
				x = y = 0;
				width = adjusted_mode->crtc_hdisplay;
				height = adjusted_mode->crtc_vdisplay;
			पूर्ण
		पूर्ण
		अवरोध;

	हाल DRM_MODE_SCALE_NONE:
		WARN_ON(adjusted_mode->crtc_hdisplay != crtc_state->pipe_src_w);
		WARN_ON(adjusted_mode->crtc_vdisplay != crtc_state->pipe_src_h);
		fallthrough;
	हाल DRM_MODE_SCALE_FULLSCREEN:
		x = y = 0;
		width = adjusted_mode->crtc_hdisplay;
		height = adjusted_mode->crtc_vdisplay;
		अवरोध;

	शेष:
		MISSING_CASE(conn_state->scaling_mode);
		वापस -EINVAL;
	पूर्ण

	drm_rect_init(&crtc_state->pch_pfit.dst,
		      x, y, width, height);
	crtc_state->pch_pfit.enabled = true;

	वापस 0;
पूर्ण

अटल व्योम
centre_horizontally(काष्ठा drm_display_mode *adjusted_mode,
		    पूर्णांक width)
अणु
	u32 border, sync_pos, blank_width, sync_width;

	/* keep the hsync and hblank widths स्थिरant */
	sync_width = adjusted_mode->crtc_hsync_end - adjusted_mode->crtc_hsync_start;
	blank_width = adjusted_mode->crtc_hblank_end - adjusted_mode->crtc_hblank_start;
	sync_pos = (blank_width - sync_width + 1) / 2;

	border = (adjusted_mode->crtc_hdisplay - width + 1) / 2;
	border += border & 1; /* make the border even */

	adjusted_mode->crtc_hdisplay = width;
	adjusted_mode->crtc_hblank_start = width + border;
	adjusted_mode->crtc_hblank_end = adjusted_mode->crtc_hblank_start + blank_width;

	adjusted_mode->crtc_hsync_start = adjusted_mode->crtc_hblank_start + sync_pos;
	adjusted_mode->crtc_hsync_end = adjusted_mode->crtc_hsync_start + sync_width;
पूर्ण

अटल व्योम
centre_vertically(काष्ठा drm_display_mode *adjusted_mode,
		  पूर्णांक height)
अणु
	u32 border, sync_pos, blank_width, sync_width;

	/* keep the vsync and vblank widths स्थिरant */
	sync_width = adjusted_mode->crtc_vsync_end - adjusted_mode->crtc_vsync_start;
	blank_width = adjusted_mode->crtc_vblank_end - adjusted_mode->crtc_vblank_start;
	sync_pos = (blank_width - sync_width + 1) / 2;

	border = (adjusted_mode->crtc_vdisplay - height + 1) / 2;

	adjusted_mode->crtc_vdisplay = height;
	adjusted_mode->crtc_vblank_start = height + border;
	adjusted_mode->crtc_vblank_end = adjusted_mode->crtc_vblank_start + blank_width;

	adjusted_mode->crtc_vsync_start = adjusted_mode->crtc_vblank_start + sync_pos;
	adjusted_mode->crtc_vsync_end = adjusted_mode->crtc_vsync_start + sync_width;
पूर्ण

अटल u32 panel_fitter_scaling(u32 source, u32 target)
अणु
	/*
	 * Floating poपूर्णांक operation is not supported. So the FACTOR
	 * is defined, which can aव्योम the भग्नing poपूर्णांक computation
	 * when calculating the panel ratio.
	 */
#घोषणा ACCURACY 12
#घोषणा FACTOR (1 << ACCURACY)
	u32 ratio = source * FACTOR / target;
	वापस (FACTOR * ratio + FACTOR/2) / FACTOR;
पूर्ण

अटल व्योम i965_scale_aspect(काष्ठा पूर्णांकel_crtc_state *crtc_state,
			      u32 *pfit_control)
अणु
	स्थिर काष्ठा drm_display_mode *adjusted_mode =
		&crtc_state->hw.adjusted_mode;
	u32 scaled_width = adjusted_mode->crtc_hdisplay *
		crtc_state->pipe_src_h;
	u32 scaled_height = crtc_state->pipe_src_w *
		adjusted_mode->crtc_vdisplay;

	/* 965+ is easy, it करोes everything in hw */
	अगर (scaled_width > scaled_height)
		*pfit_control |= PFIT_ENABLE |
			PFIT_SCALING_PILLAR;
	अन्यथा अगर (scaled_width < scaled_height)
		*pfit_control |= PFIT_ENABLE |
			PFIT_SCALING_LETTER;
	अन्यथा अगर (adjusted_mode->crtc_hdisplay != crtc_state->pipe_src_w)
		*pfit_control |= PFIT_ENABLE | PFIT_SCALING_AUTO;
पूर्ण

अटल व्योम i9xx_scale_aspect(काष्ठा पूर्णांकel_crtc_state *crtc_state,
			      u32 *pfit_control, u32 *pfit_pgm_ratios,
			      u32 *border)
अणु
	काष्ठा drm_display_mode *adjusted_mode = &crtc_state->hw.adjusted_mode;
	u32 scaled_width = adjusted_mode->crtc_hdisplay *
		crtc_state->pipe_src_h;
	u32 scaled_height = crtc_state->pipe_src_w *
		adjusted_mode->crtc_vdisplay;
	u32 bits;

	/*
	 * For earlier chips we have to calculate the scaling
	 * ratio by hand and program it पूर्णांकo the
	 * PFIT_PGM_RATIO रेजिस्टर
	 */
	अगर (scaled_width > scaled_height) अणु /* pillar */
		centre_horizontally(adjusted_mode,
				    scaled_height /
				    crtc_state->pipe_src_h);

		*border = LVDS_BORDER_ENABLE;
		अगर (crtc_state->pipe_src_h != adjusted_mode->crtc_vdisplay) अणु
			bits = panel_fitter_scaling(crtc_state->pipe_src_h,
						    adjusted_mode->crtc_vdisplay);

			*pfit_pgm_ratios |= (bits << PFIT_HORIZ_SCALE_SHIFT |
					     bits << PFIT_VERT_SCALE_SHIFT);
			*pfit_control |= (PFIT_ENABLE |
					  VERT_INTERP_BILINEAR |
					  HORIZ_INTERP_BILINEAR);
		पूर्ण
	पूर्ण अन्यथा अगर (scaled_width < scaled_height) अणु /* letter */
		centre_vertically(adjusted_mode,
				  scaled_width /
				  crtc_state->pipe_src_w);

		*border = LVDS_BORDER_ENABLE;
		अगर (crtc_state->pipe_src_w != adjusted_mode->crtc_hdisplay) अणु
			bits = panel_fitter_scaling(crtc_state->pipe_src_w,
						    adjusted_mode->crtc_hdisplay);

			*pfit_pgm_ratios |= (bits << PFIT_HORIZ_SCALE_SHIFT |
					     bits << PFIT_VERT_SCALE_SHIFT);
			*pfit_control |= (PFIT_ENABLE |
					  VERT_INTERP_BILINEAR |
					  HORIZ_INTERP_BILINEAR);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Aspects match, Let hw scale both directions */
		*pfit_control |= (PFIT_ENABLE |
				  VERT_AUTO_SCALE | HORIZ_AUTO_SCALE |
				  VERT_INTERP_BILINEAR |
				  HORIZ_INTERP_BILINEAR);
	पूर्ण
पूर्ण

पूर्णांक पूर्णांकel_gmch_panel_fitting(काष्ठा पूर्णांकel_crtc_state *crtc_state,
			     स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	u32 pfit_control = 0, pfit_pgm_ratios = 0, border = 0;
	काष्ठा drm_display_mode *adjusted_mode = &crtc_state->hw.adjusted_mode;

	/* Native modes करोn't need fitting */
	अगर (adjusted_mode->crtc_hdisplay == crtc_state->pipe_src_w &&
	    adjusted_mode->crtc_vdisplay == crtc_state->pipe_src_h)
		जाओ out;

	चयन (conn_state->scaling_mode) अणु
	हाल DRM_MODE_SCALE_CENTER:
		/*
		 * For centered modes, we have to calculate border widths &
		 * heights and modअगरy the values programmed पूर्णांकo the CRTC.
		 */
		centre_horizontally(adjusted_mode, crtc_state->pipe_src_w);
		centre_vertically(adjusted_mode, crtc_state->pipe_src_h);
		border = LVDS_BORDER_ENABLE;
		अवरोध;
	हाल DRM_MODE_SCALE_ASPECT:
		/* Scale but preserve the aspect ratio */
		अगर (DISPLAY_VER(dev_priv) >= 4)
			i965_scale_aspect(crtc_state, &pfit_control);
		अन्यथा
			i9xx_scale_aspect(crtc_state, &pfit_control,
					  &pfit_pgm_ratios, &border);
		अवरोध;
	हाल DRM_MODE_SCALE_FULLSCREEN:
		/*
		 * Full scaling, even अगर it changes the aspect ratio.
		 * Fortunately this is all करोne क्रम us in hw.
		 */
		अगर (crtc_state->pipe_src_h != adjusted_mode->crtc_vdisplay ||
		    crtc_state->pipe_src_w != adjusted_mode->crtc_hdisplay) अणु
			pfit_control |= PFIT_ENABLE;
			अगर (DISPLAY_VER(dev_priv) >= 4)
				pfit_control |= PFIT_SCALING_AUTO;
			अन्यथा
				pfit_control |= (VERT_AUTO_SCALE |
						 VERT_INTERP_BILINEAR |
						 HORIZ_AUTO_SCALE |
						 HORIZ_INTERP_BILINEAR);
		पूर्ण
		अवरोध;
	शेष:
		MISSING_CASE(conn_state->scaling_mode);
		वापस -EINVAL;
	पूर्ण

	/* 965+ wants fuzzy fitting */
	/* FIXME: handle multiple panels by failing gracefully */
	अगर (DISPLAY_VER(dev_priv) >= 4)
		pfit_control |= PFIT_PIPE(crtc->pipe) | PFIT_FILTER_FUZZY;

out:
	अगर ((pfit_control & PFIT_ENABLE) == 0) अणु
		pfit_control = 0;
		pfit_pgm_ratios = 0;
	पूर्ण

	/* Make sure pre-965 set dither correctly क्रम 18bpp panels. */
	अगर (DISPLAY_VER(dev_priv) < 4 && crtc_state->pipe_bpp == 18)
		pfit_control |= PANEL_8TO6_DITHER_ENABLE;

	crtc_state->gmch_pfit.control = pfit_control;
	crtc_state->gmch_pfit.pgm_ratios = pfit_pgm_ratios;
	crtc_state->gmch_pfit.lvds_border_bits = border;

	वापस 0;
पूर्ण

/**
 * scale - scale values from one range to another
 * @source_val: value in range [@source_min..@source_max]
 * @source_min: minimum legal value क्रम @source_val
 * @source_max: maximum legal value क्रम @source_val
 * @target_min: corresponding target value क्रम @source_min
 * @target_max: corresponding target value क्रम @source_max
 *
 * Return @source_val in range [@source_min..@source_max] scaled to range
 * [@target_min..@target_max].
 */
अटल u32 scale(u32 source_val,
		 u32 source_min, u32 source_max,
		 u32 target_min, u32 target_max)
अणु
	u64 target_val;

	WARN_ON(source_min > source_max);
	WARN_ON(target_min > target_max);

	/* defensive */
	source_val = clamp(source_val, source_min, source_max);

	/* aव्योम overflows */
	target_val = mul_u32_u32(source_val - source_min,
				 target_max - target_min);
	target_val = DIV_ROUND_CLOSEST_ULL(target_val, source_max - source_min);
	target_val += target_min;

	वापस target_val;
पूर्ण

/* Scale user_level in range [0..user_max] to [0..hw_max], clamping the result
 * to [hw_min..hw_max]. */
अटल u32 clamp_user_to_hw(काष्ठा पूर्णांकel_connector *connector,
			    u32 user_level, u32 user_max)
अणु
	काष्ठा पूर्णांकel_panel *panel = &connector->panel;
	u32 hw_level;

	hw_level = scale(user_level, 0, user_max, 0, panel->backlight.max);
	hw_level = clamp(hw_level, panel->backlight.min, panel->backlight.max);

	वापस hw_level;
पूर्ण

/* Scale hw_level in range [hw_min..hw_max] to [0..user_max]. */
अटल u32 scale_hw_to_user(काष्ठा पूर्णांकel_connector *connector,
			    u32 hw_level, u32 user_max)
अणु
	काष्ठा पूर्णांकel_panel *panel = &connector->panel;

	वापस scale(hw_level, panel->backlight.min, panel->backlight.max,
		     0, user_max);
पूर्ण

u32 पूर्णांकel_panel_invert_pwm_level(काष्ठा पूर्णांकel_connector *connector, u32 val)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	काष्ठा पूर्णांकel_panel *panel = &connector->panel;

	drm_WARN_ON(&dev_priv->drm, panel->backlight.pwm_level_max == 0);

	अगर (dev_priv->params.invert_brightness < 0)
		वापस val;

	अगर (dev_priv->params.invert_brightness > 0 ||
	    dev_priv->quirks & QUIRK_INVERT_BRIGHTNESS) अणु
		वापस panel->backlight.pwm_level_max - val + panel->backlight.pwm_level_min;
	पूर्ण

	वापस val;
पूर्ण

व्योम पूर्णांकel_panel_set_pwm_level(स्थिर काष्ठा drm_connector_state *conn_state, u32 val)
अणु
	काष्ठा पूर्णांकel_connector *connector = to_पूर्णांकel_connector(conn_state->connector);
	काष्ठा drm_i915_निजी *i915 = to_i915(connector->base.dev);
	काष्ठा पूर्णांकel_panel *panel = &connector->panel;

	drm_dbg_kms(&i915->drm, "set backlight PWM = %d\n", val);
	panel->backlight.pwm_funcs->set(conn_state, val);
पूर्ण

u32 पूर्णांकel_panel_backlight_level_to_pwm(काष्ठा पूर्णांकel_connector *connector, u32 val)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	काष्ठा पूर्णांकel_panel *panel = &connector->panel;

	drm_WARN_ON_ONCE(&dev_priv->drm,
			 panel->backlight.max == 0 || panel->backlight.pwm_level_max == 0);

	val = scale(val, panel->backlight.min, panel->backlight.max,
		    panel->backlight.pwm_level_min, panel->backlight.pwm_level_max);

	वापस पूर्णांकel_panel_invert_pwm_level(connector, val);
पूर्ण

u32 पूर्णांकel_panel_backlight_level_from_pwm(काष्ठा पूर्णांकel_connector *connector, u32 val)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	काष्ठा पूर्णांकel_panel *panel = &connector->panel;

	drm_WARN_ON_ONCE(&dev_priv->drm,
			 panel->backlight.max == 0 || panel->backlight.pwm_level_max == 0);

	अगर (dev_priv->params.invert_brightness > 0 ||
	    (dev_priv->params.invert_brightness == 0 && dev_priv->quirks & QUIRK_INVERT_BRIGHTNESS))
		val = panel->backlight.pwm_level_max - (val - panel->backlight.pwm_level_min);

	वापस scale(val, panel->backlight.pwm_level_min, panel->backlight.pwm_level_max,
		     panel->backlight.min, panel->backlight.max);
पूर्ण

अटल u32 lpt_get_backlight(काष्ठा पूर्णांकel_connector *connector, क्रमागत pipe unused)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);

	वापस पूर्णांकel_de_पढ़ो(dev_priv, BLC_PWM_PCH_CTL2) & BACKLIGHT_DUTY_CYCLE_MASK;
पूर्ण

अटल u32 pch_get_backlight(काष्ठा पूर्णांकel_connector *connector, क्रमागत pipe unused)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);

	वापस पूर्णांकel_de_पढ़ो(dev_priv, BLC_PWM_CPU_CTL) & BACKLIGHT_DUTY_CYCLE_MASK;
पूर्ण

अटल u32 i9xx_get_backlight(काष्ठा पूर्णांकel_connector *connector, क्रमागत pipe unused)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	काष्ठा पूर्णांकel_panel *panel = &connector->panel;
	u32 val;

	val = पूर्णांकel_de_पढ़ो(dev_priv, BLC_PWM_CTL) & BACKLIGHT_DUTY_CYCLE_MASK;
	अगर (DISPLAY_VER(dev_priv) < 4)
		val >>= 1;

	अगर (panel->backlight.combination_mode) अणु
		u8 lbpc;

		pci_पढ़ो_config_byte(to_pci_dev(dev_priv->drm.dev), LBPC, &lbpc);
		val *= lbpc;
	पूर्ण

	वापस val;
पूर्ण

अटल u32 vlv_get_backlight(काष्ठा पूर्णांकel_connector *connector, क्रमागत pipe pipe)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);

	अगर (drm_WARN_ON(&dev_priv->drm, pipe != PIPE_A && pipe != PIPE_B))
		वापस 0;

	वापस पूर्णांकel_de_पढ़ो(dev_priv, VLV_BLC_PWM_CTL(pipe)) & BACKLIGHT_DUTY_CYCLE_MASK;
पूर्ण

अटल u32 bxt_get_backlight(काष्ठा पूर्णांकel_connector *connector, क्रमागत pipe unused)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	काष्ठा पूर्णांकel_panel *panel = &connector->panel;

	वापस पूर्णांकel_de_पढ़ो(dev_priv,
			     BXT_BLC_PWM_DUTY(panel->backlight.controller));
पूर्ण

अटल u32 ext_pwm_get_backlight(काष्ठा पूर्णांकel_connector *connector, क्रमागत pipe unused)
अणु
	काष्ठा पूर्णांकel_panel *panel = &connector->panel;
	काष्ठा pwm_state state;

	pwm_get_state(panel->backlight.pwm, &state);
	वापस pwm_get_relative_duty_cycle(&state, 100);
पूर्ण

अटल व्योम lpt_set_backlight(स्थिर काष्ठा drm_connector_state *conn_state, u32 level)
अणु
	काष्ठा पूर्णांकel_connector *connector = to_पूर्णांकel_connector(conn_state->connector);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);

	u32 val = पूर्णांकel_de_पढ़ो(dev_priv, BLC_PWM_PCH_CTL2) & ~BACKLIGHT_DUTY_CYCLE_MASK;
	पूर्णांकel_de_ग_लिखो(dev_priv, BLC_PWM_PCH_CTL2, val | level);
पूर्ण

अटल व्योम pch_set_backlight(स्थिर काष्ठा drm_connector_state *conn_state, u32 level)
अणु
	काष्ठा पूर्णांकel_connector *connector = to_पूर्णांकel_connector(conn_state->connector);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	u32 पंचांगp;

	पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, BLC_PWM_CPU_CTL) & ~BACKLIGHT_DUTY_CYCLE_MASK;
	पूर्णांकel_de_ग_लिखो(dev_priv, BLC_PWM_CPU_CTL, पंचांगp | level);
पूर्ण

अटल व्योम i9xx_set_backlight(स्थिर काष्ठा drm_connector_state *conn_state, u32 level)
अणु
	काष्ठा पूर्णांकel_connector *connector = to_पूर्णांकel_connector(conn_state->connector);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	काष्ठा पूर्णांकel_panel *panel = &connector->panel;
	u32 पंचांगp, mask;

	drm_WARN_ON(&dev_priv->drm, panel->backlight.pwm_level_max == 0);

	अगर (panel->backlight.combination_mode) अणु
		u8 lbpc;

		lbpc = level * 0xfe / panel->backlight.pwm_level_max + 1;
		level /= lbpc;
		pci_ग_लिखो_config_byte(to_pci_dev(dev_priv->drm.dev), LBPC, lbpc);
	पूर्ण

	अगर (IS_DISPLAY_VER(dev_priv, 4)) अणु
		mask = BACKLIGHT_DUTY_CYCLE_MASK;
	पूर्ण अन्यथा अणु
		level <<= 1;
		mask = BACKLIGHT_DUTY_CYCLE_MASK_PNV;
	पूर्ण

	पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, BLC_PWM_CTL) & ~mask;
	पूर्णांकel_de_ग_लिखो(dev_priv, BLC_PWM_CTL, पंचांगp | level);
पूर्ण

अटल व्योम vlv_set_backlight(स्थिर काष्ठा drm_connector_state *conn_state, u32 level)
अणु
	काष्ठा पूर्णांकel_connector *connector = to_पूर्णांकel_connector(conn_state->connector);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	क्रमागत pipe pipe = to_पूर्णांकel_crtc(conn_state->crtc)->pipe;
	u32 पंचांगp;

	पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, VLV_BLC_PWM_CTL(pipe)) & ~BACKLIGHT_DUTY_CYCLE_MASK;
	पूर्णांकel_de_ग_लिखो(dev_priv, VLV_BLC_PWM_CTL(pipe), पंचांगp | level);
पूर्ण

अटल व्योम bxt_set_backlight(स्थिर काष्ठा drm_connector_state *conn_state, u32 level)
अणु
	काष्ठा पूर्णांकel_connector *connector = to_पूर्णांकel_connector(conn_state->connector);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	काष्ठा पूर्णांकel_panel *panel = &connector->panel;

	पूर्णांकel_de_ग_लिखो(dev_priv,
		       BXT_BLC_PWM_DUTY(panel->backlight.controller), level);
पूर्ण

अटल व्योम ext_pwm_set_backlight(स्थिर काष्ठा drm_connector_state *conn_state, u32 level)
अणु
	काष्ठा पूर्णांकel_panel *panel = &to_पूर्णांकel_connector(conn_state->connector)->panel;

	pwm_set_relative_duty_cycle(&panel->backlight.pwm_state, level, 100);
	pwm_apply_state(panel->backlight.pwm, &panel->backlight.pwm_state);
पूर्ण

अटल व्योम
पूर्णांकel_panel_actually_set_backlight(स्थिर काष्ठा drm_connector_state *conn_state, u32 level)
अणु
	काष्ठा पूर्णांकel_connector *connector = to_पूर्णांकel_connector(conn_state->connector);
	काष्ठा drm_i915_निजी *i915 = to_i915(connector->base.dev);
	काष्ठा पूर्णांकel_panel *panel = &connector->panel;

	drm_dbg_kms(&i915->drm, "set backlight level = %d\n", level);

	panel->backlight.funcs->set(conn_state, level);
पूर्ण

/* set backlight brightness to level in range [0..max], assuming hw min is
 * respected.
 */
व्योम पूर्णांकel_panel_set_backlight_acpi(स्थिर काष्ठा drm_connector_state *conn_state,
				    u32 user_level, u32 user_max)
अणु
	काष्ठा पूर्णांकel_connector *connector = to_पूर्णांकel_connector(conn_state->connector);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	काष्ठा पूर्णांकel_panel *panel = &connector->panel;
	u32 hw_level;

	/*
	 * Lack of crtc may occur during driver init because
	 * connection_mutex isn't held across the entire backlight
	 * setup + modeset पढ़ोout, and the BIOS can issue the
	 * requests at any समय.
	 */
	अगर (!panel->backlight.present || !conn_state->crtc)
		वापस;

	mutex_lock(&dev_priv->backlight_lock);

	drm_WARN_ON(&dev_priv->drm, panel->backlight.max == 0);

	hw_level = clamp_user_to_hw(connector, user_level, user_max);
	panel->backlight.level = hw_level;

	अगर (panel->backlight.device)
		panel->backlight.device->props.brightness =
			scale_hw_to_user(connector,
					 panel->backlight.level,
					 panel->backlight.device->props.max_brightness);

	अगर (panel->backlight.enabled)
		पूर्णांकel_panel_actually_set_backlight(conn_state, hw_level);

	mutex_unlock(&dev_priv->backlight_lock);
पूर्ण

अटल व्योम lpt_disable_backlight(स्थिर काष्ठा drm_connector_state *old_conn_state, u32 level)
अणु
	काष्ठा पूर्णांकel_connector *connector = to_पूर्णांकel_connector(old_conn_state->connector);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	u32 पंचांगp;

	पूर्णांकel_panel_set_pwm_level(old_conn_state, level);

	/*
	 * Although we करोn't support or enable CPU PWM with LPT/SPT based
	 * प्रणालीs, it may have been enabled prior to loading the
	 * driver. Disable to aव्योम warnings on LCPLL disable.
	 *
	 * This needs rework अगर we need to add support क्रम CPU PWM on PCH split
	 * platक्रमms.
	 */
	पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, BLC_PWM_CPU_CTL2);
	अगर (पंचांगp & BLM_PWM_ENABLE) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "cpu backlight was enabled, disabling\n");
		पूर्णांकel_de_ग_लिखो(dev_priv, BLC_PWM_CPU_CTL2,
			       पंचांगp & ~BLM_PWM_ENABLE);
	पूर्ण

	पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, BLC_PWM_PCH_CTL1);
	पूर्णांकel_de_ग_लिखो(dev_priv, BLC_PWM_PCH_CTL1, पंचांगp & ~BLM_PCH_PWM_ENABLE);
पूर्ण

अटल व्योम pch_disable_backlight(स्थिर काष्ठा drm_connector_state *old_conn_state, u32 val)
अणु
	काष्ठा पूर्णांकel_connector *connector = to_पूर्णांकel_connector(old_conn_state->connector);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	u32 पंचांगp;

	पूर्णांकel_panel_set_pwm_level(old_conn_state, val);

	पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, BLC_PWM_CPU_CTL2);
	पूर्णांकel_de_ग_लिखो(dev_priv, BLC_PWM_CPU_CTL2, पंचांगp & ~BLM_PWM_ENABLE);

	पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, BLC_PWM_PCH_CTL1);
	पूर्णांकel_de_ग_लिखो(dev_priv, BLC_PWM_PCH_CTL1, पंचांगp & ~BLM_PCH_PWM_ENABLE);
पूर्ण

अटल व्योम i9xx_disable_backlight(स्थिर काष्ठा drm_connector_state *old_conn_state, u32 val)
अणु
	पूर्णांकel_panel_set_pwm_level(old_conn_state, val);
पूर्ण

अटल व्योम i965_disable_backlight(स्थिर काष्ठा drm_connector_state *old_conn_state, u32 val)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(old_conn_state->connector->dev);
	u32 पंचांगp;

	पूर्णांकel_panel_set_pwm_level(old_conn_state, val);

	पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, BLC_PWM_CTL2);
	पूर्णांकel_de_ग_लिखो(dev_priv, BLC_PWM_CTL2, पंचांगp & ~BLM_PWM_ENABLE);
पूर्ण

अटल व्योम vlv_disable_backlight(स्थिर काष्ठा drm_connector_state *old_conn_state, u32 val)
अणु
	काष्ठा पूर्णांकel_connector *connector = to_पूर्णांकel_connector(old_conn_state->connector);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	क्रमागत pipe pipe = to_पूर्णांकel_crtc(old_conn_state->crtc)->pipe;
	u32 पंचांगp;

	पूर्णांकel_panel_set_pwm_level(old_conn_state, val);

	पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, VLV_BLC_PWM_CTL2(pipe));
	पूर्णांकel_de_ग_लिखो(dev_priv, VLV_BLC_PWM_CTL2(pipe),
		       पंचांगp & ~BLM_PWM_ENABLE);
पूर्ण

अटल व्योम bxt_disable_backlight(स्थिर काष्ठा drm_connector_state *old_conn_state, u32 val)
अणु
	काष्ठा पूर्णांकel_connector *connector = to_पूर्णांकel_connector(old_conn_state->connector);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	काष्ठा पूर्णांकel_panel *panel = &connector->panel;
	u32 पंचांगp;

	पूर्णांकel_panel_set_pwm_level(old_conn_state, val);

	पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv,
			    BXT_BLC_PWM_CTL(panel->backlight.controller));
	पूर्णांकel_de_ग_लिखो(dev_priv, BXT_BLC_PWM_CTL(panel->backlight.controller),
		       पंचांगp & ~BXT_BLC_PWM_ENABLE);

	अगर (panel->backlight.controller == 1) अणु
		val = पूर्णांकel_de_पढ़ो(dev_priv, UTIL_PIN_CTL);
		val &= ~UTIL_PIN_ENABLE;
		पूर्णांकel_de_ग_लिखो(dev_priv, UTIL_PIN_CTL, val);
	पूर्ण
पूर्ण

अटल व्योम cnp_disable_backlight(स्थिर काष्ठा drm_connector_state *old_conn_state, u32 val)
अणु
	काष्ठा पूर्णांकel_connector *connector = to_पूर्णांकel_connector(old_conn_state->connector);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	काष्ठा पूर्णांकel_panel *panel = &connector->panel;
	u32 पंचांगp;

	पूर्णांकel_panel_set_pwm_level(old_conn_state, val);

	पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv,
			    BXT_BLC_PWM_CTL(panel->backlight.controller));
	पूर्णांकel_de_ग_लिखो(dev_priv, BXT_BLC_PWM_CTL(panel->backlight.controller),
		       पंचांगp & ~BXT_BLC_PWM_ENABLE);
पूर्ण

अटल व्योम ext_pwm_disable_backlight(स्थिर काष्ठा drm_connector_state *old_conn_state, u32 level)
अणु
	काष्ठा पूर्णांकel_connector *connector = to_पूर्णांकel_connector(old_conn_state->connector);
	काष्ठा पूर्णांकel_panel *panel = &connector->panel;

	panel->backlight.pwm_state.enabled = false;
	pwm_apply_state(panel->backlight.pwm, &panel->backlight.pwm_state);
पूर्ण

व्योम पूर्णांकel_panel_disable_backlight(स्थिर काष्ठा drm_connector_state *old_conn_state)
अणु
	काष्ठा पूर्णांकel_connector *connector = to_पूर्णांकel_connector(old_conn_state->connector);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	काष्ठा पूर्णांकel_panel *panel = &connector->panel;

	अगर (!panel->backlight.present)
		वापस;

	/*
	 * Do not disable backlight on the vga_चयनeroo path. When चयनing
	 * away from i915, the other client may depend on i915 to handle the
	 * backlight. This will leave the backlight on unnecessarily when
	 * another client is not activated.
	 */
	अगर (dev_priv->drm.चयन_घातer_state == DRM_SWITCH_POWER_CHANGING) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "Skipping backlight disable on vga switch\n");
		वापस;
	पूर्ण

	mutex_lock(&dev_priv->backlight_lock);

	अगर (panel->backlight.device)
		panel->backlight.device->props.घातer = FB_BLANK_POWERDOWN;
	panel->backlight.enabled = false;
	panel->backlight.funcs->disable(old_conn_state, 0);

	mutex_unlock(&dev_priv->backlight_lock);
पूर्ण

अटल व्योम lpt_enable_backlight(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				 स्थिर काष्ठा drm_connector_state *conn_state, u32 level)
अणु
	काष्ठा पूर्णांकel_connector *connector = to_पूर्णांकel_connector(conn_state->connector);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	काष्ठा पूर्णांकel_panel *panel = &connector->panel;
	u32 pch_ctl1, pch_ctl2, schicken;

	pch_ctl1 = पूर्णांकel_de_पढ़ो(dev_priv, BLC_PWM_PCH_CTL1);
	अगर (pch_ctl1 & BLM_PCH_PWM_ENABLE) अणु
		drm_dbg_kms(&dev_priv->drm, "pch backlight already enabled\n");
		pch_ctl1 &= ~BLM_PCH_PWM_ENABLE;
		पूर्णांकel_de_ग_लिखो(dev_priv, BLC_PWM_PCH_CTL1, pch_ctl1);
	पूर्ण

	अगर (HAS_PCH_LPT(dev_priv)) अणु
		schicken = पूर्णांकel_de_पढ़ो(dev_priv, SOUTH_CHICKEN2);
		अगर (panel->backlight.alternate_pwm_increment)
			schicken |= LPT_PWM_GRANULARITY;
		अन्यथा
			schicken &= ~LPT_PWM_GRANULARITY;
		पूर्णांकel_de_ग_लिखो(dev_priv, SOUTH_CHICKEN2, schicken);
	पूर्ण अन्यथा अणु
		schicken = पूर्णांकel_de_पढ़ो(dev_priv, SOUTH_CHICKEN1);
		अगर (panel->backlight.alternate_pwm_increment)
			schicken |= SPT_PWM_GRANULARITY;
		अन्यथा
			schicken &= ~SPT_PWM_GRANULARITY;
		पूर्णांकel_de_ग_लिखो(dev_priv, SOUTH_CHICKEN1, schicken);
	पूर्ण

	pch_ctl2 = panel->backlight.pwm_level_max << 16;
	पूर्णांकel_de_ग_लिखो(dev_priv, BLC_PWM_PCH_CTL2, pch_ctl2);

	pch_ctl1 = 0;
	अगर (panel->backlight.active_low_pwm)
		pch_ctl1 |= BLM_PCH_POLARITY;

	/* After LPT, override is the शेष. */
	अगर (HAS_PCH_LPT(dev_priv))
		pch_ctl1 |= BLM_PCH_OVERRIDE_ENABLE;

	पूर्णांकel_de_ग_लिखो(dev_priv, BLC_PWM_PCH_CTL1, pch_ctl1);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, BLC_PWM_PCH_CTL1);
	पूर्णांकel_de_ग_लिखो(dev_priv, BLC_PWM_PCH_CTL1,
		       pch_ctl1 | BLM_PCH_PWM_ENABLE);

	/* This won't stick until the above enable. */
	पूर्णांकel_panel_set_pwm_level(conn_state, level);
पूर्ण

अटल व्योम pch_enable_backlight(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				 स्थिर काष्ठा drm_connector_state *conn_state, u32 level)
अणु
	काष्ठा पूर्णांकel_connector *connector = to_पूर्णांकel_connector(conn_state->connector);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	काष्ठा पूर्णांकel_panel *panel = &connector->panel;
	क्रमागत transcoder cpu_transcoder = crtc_state->cpu_transcoder;
	u32 cpu_ctl2, pch_ctl1, pch_ctl2;

	cpu_ctl2 = पूर्णांकel_de_पढ़ो(dev_priv, BLC_PWM_CPU_CTL2);
	अगर (cpu_ctl2 & BLM_PWM_ENABLE) अणु
		drm_dbg_kms(&dev_priv->drm, "cpu backlight already enabled\n");
		cpu_ctl2 &= ~BLM_PWM_ENABLE;
		पूर्णांकel_de_ग_लिखो(dev_priv, BLC_PWM_CPU_CTL2, cpu_ctl2);
	पूर्ण

	pch_ctl1 = पूर्णांकel_de_पढ़ो(dev_priv, BLC_PWM_PCH_CTL1);
	अगर (pch_ctl1 & BLM_PCH_PWM_ENABLE) अणु
		drm_dbg_kms(&dev_priv->drm, "pch backlight already enabled\n");
		pch_ctl1 &= ~BLM_PCH_PWM_ENABLE;
		पूर्णांकel_de_ग_लिखो(dev_priv, BLC_PWM_PCH_CTL1, pch_ctl1);
	पूर्ण

	अगर (cpu_transcoder == TRANSCODER_EDP)
		cpu_ctl2 = BLM_TRANSCODER_EDP;
	अन्यथा
		cpu_ctl2 = BLM_PIPE(cpu_transcoder);
	पूर्णांकel_de_ग_लिखो(dev_priv, BLC_PWM_CPU_CTL2, cpu_ctl2);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, BLC_PWM_CPU_CTL2);
	पूर्णांकel_de_ग_लिखो(dev_priv, BLC_PWM_CPU_CTL2, cpu_ctl2 | BLM_PWM_ENABLE);

	/* This won't stick until the above enable. */
	पूर्णांकel_panel_set_pwm_level(conn_state, level);

	pch_ctl2 = panel->backlight.pwm_level_max << 16;
	पूर्णांकel_de_ग_लिखो(dev_priv, BLC_PWM_PCH_CTL2, pch_ctl2);

	pch_ctl1 = 0;
	अगर (panel->backlight.active_low_pwm)
		pch_ctl1 |= BLM_PCH_POLARITY;

	पूर्णांकel_de_ग_लिखो(dev_priv, BLC_PWM_PCH_CTL1, pch_ctl1);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, BLC_PWM_PCH_CTL1);
	पूर्णांकel_de_ग_लिखो(dev_priv, BLC_PWM_PCH_CTL1,
		       pch_ctl1 | BLM_PCH_PWM_ENABLE);
पूर्ण

अटल व्योम i9xx_enable_backlight(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				  स्थिर काष्ठा drm_connector_state *conn_state, u32 level)
अणु
	काष्ठा पूर्णांकel_connector *connector = to_पूर्णांकel_connector(conn_state->connector);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	काष्ठा पूर्णांकel_panel *panel = &connector->panel;
	u32 ctl, freq;

	ctl = पूर्णांकel_de_पढ़ो(dev_priv, BLC_PWM_CTL);
	अगर (ctl & BACKLIGHT_DUTY_CYCLE_MASK_PNV) अणु
		drm_dbg_kms(&dev_priv->drm, "backlight already enabled\n");
		पूर्णांकel_de_ग_लिखो(dev_priv, BLC_PWM_CTL, 0);
	पूर्ण

	freq = panel->backlight.pwm_level_max;
	अगर (panel->backlight.combination_mode)
		freq /= 0xff;

	ctl = freq << 17;
	अगर (panel->backlight.combination_mode)
		ctl |= BLM_LEGACY_MODE;
	अगर (IS_PINEVIEW(dev_priv) && panel->backlight.active_low_pwm)
		ctl |= BLM_POLARITY_PNV;

	पूर्णांकel_de_ग_लिखो(dev_priv, BLC_PWM_CTL, ctl);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, BLC_PWM_CTL);

	/* XXX: combine this पूर्णांकo above ग_लिखो? */
	पूर्णांकel_panel_set_pwm_level(conn_state, level);

	/*
	 * Needed to enable backlight on some 855gm models. BLC_HIST_CTL is
	 * 855gm only, but checking क्रम gen2 is safe, as 855gm is the only gen2
	 * that has backlight.
	 */
	अगर (IS_DISPLAY_VER(dev_priv, 2))
		पूर्णांकel_de_ग_लिखो(dev_priv, BLC_HIST_CTL, BLM_HISTOGRAM_ENABLE);
पूर्ण

अटल व्योम i965_enable_backlight(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				  स्थिर काष्ठा drm_connector_state *conn_state, u32 level)
अणु
	काष्ठा पूर्णांकel_connector *connector = to_पूर्णांकel_connector(conn_state->connector);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	काष्ठा पूर्णांकel_panel *panel = &connector->panel;
	क्रमागत pipe pipe = to_पूर्णांकel_crtc(conn_state->crtc)->pipe;
	u32 ctl, ctl2, freq;

	ctl2 = पूर्णांकel_de_पढ़ो(dev_priv, BLC_PWM_CTL2);
	अगर (ctl2 & BLM_PWM_ENABLE) अणु
		drm_dbg_kms(&dev_priv->drm, "backlight already enabled\n");
		ctl2 &= ~BLM_PWM_ENABLE;
		पूर्णांकel_de_ग_लिखो(dev_priv, BLC_PWM_CTL2, ctl2);
	पूर्ण

	freq = panel->backlight.pwm_level_max;
	अगर (panel->backlight.combination_mode)
		freq /= 0xff;

	ctl = freq << 16;
	पूर्णांकel_de_ग_लिखो(dev_priv, BLC_PWM_CTL, ctl);

	ctl2 = BLM_PIPE(pipe);
	अगर (panel->backlight.combination_mode)
		ctl2 |= BLM_COMBINATION_MODE;
	अगर (panel->backlight.active_low_pwm)
		ctl2 |= BLM_POLARITY_I965;
	पूर्णांकel_de_ग_लिखो(dev_priv, BLC_PWM_CTL2, ctl2);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, BLC_PWM_CTL2);
	पूर्णांकel_de_ग_लिखो(dev_priv, BLC_PWM_CTL2, ctl2 | BLM_PWM_ENABLE);

	पूर्णांकel_panel_set_pwm_level(conn_state, level);
पूर्ण

अटल व्योम vlv_enable_backlight(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				 स्थिर काष्ठा drm_connector_state *conn_state, u32 level)
अणु
	काष्ठा पूर्णांकel_connector *connector = to_पूर्णांकel_connector(conn_state->connector);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	काष्ठा पूर्णांकel_panel *panel = &connector->panel;
	क्रमागत pipe pipe = to_पूर्णांकel_crtc(crtc_state->uapi.crtc)->pipe;
	u32 ctl, ctl2;

	ctl2 = पूर्णांकel_de_पढ़ो(dev_priv, VLV_BLC_PWM_CTL2(pipe));
	अगर (ctl2 & BLM_PWM_ENABLE) अणु
		drm_dbg_kms(&dev_priv->drm, "backlight already enabled\n");
		ctl2 &= ~BLM_PWM_ENABLE;
		पूर्णांकel_de_ग_लिखो(dev_priv, VLV_BLC_PWM_CTL2(pipe), ctl2);
	पूर्ण

	ctl = panel->backlight.pwm_level_max << 16;
	पूर्णांकel_de_ग_लिखो(dev_priv, VLV_BLC_PWM_CTL(pipe), ctl);

	/* XXX: combine this पूर्णांकo above ग_लिखो? */
	पूर्णांकel_panel_set_pwm_level(conn_state, level);

	ctl2 = 0;
	अगर (panel->backlight.active_low_pwm)
		ctl2 |= BLM_POLARITY_I965;
	पूर्णांकel_de_ग_लिखो(dev_priv, VLV_BLC_PWM_CTL2(pipe), ctl2);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, VLV_BLC_PWM_CTL2(pipe));
	पूर्णांकel_de_ग_लिखो(dev_priv, VLV_BLC_PWM_CTL2(pipe),
		       ctl2 | BLM_PWM_ENABLE);
पूर्ण

अटल व्योम bxt_enable_backlight(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				 स्थिर काष्ठा drm_connector_state *conn_state, u32 level)
अणु
	काष्ठा पूर्णांकel_connector *connector = to_पूर्णांकel_connector(conn_state->connector);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	काष्ठा पूर्णांकel_panel *panel = &connector->panel;
	क्रमागत pipe pipe = to_पूर्णांकel_crtc(crtc_state->uapi.crtc)->pipe;
	u32 pwm_ctl, val;

	/* Controller 1 uses the utility pin. */
	अगर (panel->backlight.controller == 1) अणु
		val = पूर्णांकel_de_पढ़ो(dev_priv, UTIL_PIN_CTL);
		अगर (val & UTIL_PIN_ENABLE) अणु
			drm_dbg_kms(&dev_priv->drm,
				    "util pin already enabled\n");
			val &= ~UTIL_PIN_ENABLE;
			पूर्णांकel_de_ग_लिखो(dev_priv, UTIL_PIN_CTL, val);
		पूर्ण

		val = 0;
		अगर (panel->backlight.util_pin_active_low)
			val |= UTIL_PIN_POLARITY;
		पूर्णांकel_de_ग_लिखो(dev_priv, UTIL_PIN_CTL,
			       val | UTIL_PIN_PIPE(pipe) | UTIL_PIN_MODE_PWM | UTIL_PIN_ENABLE);
	पूर्ण

	pwm_ctl = पूर्णांकel_de_पढ़ो(dev_priv,
				BXT_BLC_PWM_CTL(panel->backlight.controller));
	अगर (pwm_ctl & BXT_BLC_PWM_ENABLE) अणु
		drm_dbg_kms(&dev_priv->drm, "backlight already enabled\n");
		pwm_ctl &= ~BXT_BLC_PWM_ENABLE;
		पूर्णांकel_de_ग_लिखो(dev_priv,
			       BXT_BLC_PWM_CTL(panel->backlight.controller),
			       pwm_ctl);
	पूर्ण

	पूर्णांकel_de_ग_लिखो(dev_priv,
		       BXT_BLC_PWM_FREQ(panel->backlight.controller),
		       panel->backlight.pwm_level_max);

	पूर्णांकel_panel_set_pwm_level(conn_state, level);

	pwm_ctl = 0;
	अगर (panel->backlight.active_low_pwm)
		pwm_ctl |= BXT_BLC_PWM_POLARITY;

	पूर्णांकel_de_ग_लिखो(dev_priv, BXT_BLC_PWM_CTL(panel->backlight.controller),
		       pwm_ctl);
	पूर्णांकel_de_posting_पढ़ो(dev_priv,
			      BXT_BLC_PWM_CTL(panel->backlight.controller));
	पूर्णांकel_de_ग_लिखो(dev_priv, BXT_BLC_PWM_CTL(panel->backlight.controller),
		       pwm_ctl | BXT_BLC_PWM_ENABLE);
पूर्ण

अटल व्योम cnp_enable_backlight(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				 स्थिर काष्ठा drm_connector_state *conn_state, u32 level)
अणु
	काष्ठा पूर्णांकel_connector *connector = to_पूर्णांकel_connector(conn_state->connector);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	काष्ठा पूर्णांकel_panel *panel = &connector->panel;
	u32 pwm_ctl;

	pwm_ctl = पूर्णांकel_de_पढ़ो(dev_priv,
				BXT_BLC_PWM_CTL(panel->backlight.controller));
	अगर (pwm_ctl & BXT_BLC_PWM_ENABLE) अणु
		drm_dbg_kms(&dev_priv->drm, "backlight already enabled\n");
		pwm_ctl &= ~BXT_BLC_PWM_ENABLE;
		पूर्णांकel_de_ग_लिखो(dev_priv,
			       BXT_BLC_PWM_CTL(panel->backlight.controller),
			       pwm_ctl);
	पूर्ण

	पूर्णांकel_de_ग_लिखो(dev_priv,
		       BXT_BLC_PWM_FREQ(panel->backlight.controller),
		       panel->backlight.pwm_level_max);

	पूर्णांकel_panel_set_pwm_level(conn_state, level);

	pwm_ctl = 0;
	अगर (panel->backlight.active_low_pwm)
		pwm_ctl |= BXT_BLC_PWM_POLARITY;

	पूर्णांकel_de_ग_लिखो(dev_priv, BXT_BLC_PWM_CTL(panel->backlight.controller),
		       pwm_ctl);
	पूर्णांकel_de_posting_पढ़ो(dev_priv,
			      BXT_BLC_PWM_CTL(panel->backlight.controller));
	पूर्णांकel_de_ग_लिखो(dev_priv, BXT_BLC_PWM_CTL(panel->backlight.controller),
		       pwm_ctl | BXT_BLC_PWM_ENABLE);
पूर्ण

अटल व्योम ext_pwm_enable_backlight(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				     स्थिर काष्ठा drm_connector_state *conn_state, u32 level)
अणु
	काष्ठा पूर्णांकel_connector *connector = to_पूर्णांकel_connector(conn_state->connector);
	काष्ठा पूर्णांकel_panel *panel = &connector->panel;

	pwm_set_relative_duty_cycle(&panel->backlight.pwm_state, level, 100);
	panel->backlight.pwm_state.enabled = true;
	pwm_apply_state(panel->backlight.pwm, &panel->backlight.pwm_state);
पूर्ण

अटल व्योम __पूर्णांकel_panel_enable_backlight(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
					   स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा पूर्णांकel_connector *connector = to_पूर्णांकel_connector(conn_state->connector);
	काष्ठा पूर्णांकel_panel *panel = &connector->panel;

	WARN_ON(panel->backlight.max == 0);

	अगर (panel->backlight.level <= panel->backlight.min) अणु
		panel->backlight.level = panel->backlight.max;
		अगर (panel->backlight.device)
			panel->backlight.device->props.brightness =
				scale_hw_to_user(connector,
						 panel->backlight.level,
						 panel->backlight.device->props.max_brightness);
	पूर्ण

	panel->backlight.funcs->enable(crtc_state, conn_state, panel->backlight.level);
	panel->backlight.enabled = true;
	अगर (panel->backlight.device)
		panel->backlight.device->props.घातer = FB_BLANK_UNBLANK;
पूर्ण

व्योम पूर्णांकel_panel_enable_backlight(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				  स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा पूर्णांकel_connector *connector = to_पूर्णांकel_connector(conn_state->connector);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	काष्ठा पूर्णांकel_panel *panel = &connector->panel;
	क्रमागत pipe pipe = to_पूर्णांकel_crtc(crtc_state->uapi.crtc)->pipe;

	अगर (!panel->backlight.present)
		वापस;

	drm_dbg_kms(&dev_priv->drm, "pipe %c\n", pipe_name(pipe));

	mutex_lock(&dev_priv->backlight_lock);

	__पूर्णांकel_panel_enable_backlight(crtc_state, conn_state);

	mutex_unlock(&dev_priv->backlight_lock);
पूर्ण

#अगर IS_ENABLED(CONFIG_BACKLIGHT_CLASS_DEVICE)
अटल u32 पूर्णांकel_panel_get_backlight(काष्ठा पूर्णांकel_connector *connector)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	काष्ठा पूर्णांकel_panel *panel = &connector->panel;
	u32 val = 0;

	mutex_lock(&dev_priv->backlight_lock);

	अगर (panel->backlight.enabled)
		val = panel->backlight.funcs->get(connector, पूर्णांकel_connector_get_pipe(connector));

	mutex_unlock(&dev_priv->backlight_lock);

	drm_dbg_kms(&dev_priv->drm, "get backlight PWM = %d\n", val);
	वापस val;
पूर्ण

/* Scale user_level in range [0..user_max] to [hw_min..hw_max]. */
अटल u32 scale_user_to_hw(काष्ठा पूर्णांकel_connector *connector,
			    u32 user_level, u32 user_max)
अणु
	काष्ठा पूर्णांकel_panel *panel = &connector->panel;

	वापस scale(user_level, 0, user_max,
		     panel->backlight.min, panel->backlight.max);
पूर्ण

/* set backlight brightness to level in range [0..max], scaling wrt hw min */
अटल व्योम पूर्णांकel_panel_set_backlight(स्थिर काष्ठा drm_connector_state *conn_state,
				      u32 user_level, u32 user_max)
अणु
	काष्ठा पूर्णांकel_connector *connector = to_पूर्णांकel_connector(conn_state->connector);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	काष्ठा पूर्णांकel_panel *panel = &connector->panel;
	u32 hw_level;

	अगर (!panel->backlight.present)
		वापस;

	mutex_lock(&dev_priv->backlight_lock);

	drm_WARN_ON(&dev_priv->drm, panel->backlight.max == 0);

	hw_level = scale_user_to_hw(connector, user_level, user_max);
	panel->backlight.level = hw_level;

	अगर (panel->backlight.enabled)
		पूर्णांकel_panel_actually_set_backlight(conn_state, hw_level);

	mutex_unlock(&dev_priv->backlight_lock);
पूर्ण

अटल पूर्णांक पूर्णांकel_backlight_device_update_status(काष्ठा backlight_device *bd)
अणु
	काष्ठा पूर्णांकel_connector *connector = bl_get_data(bd);
	काष्ठा पूर्णांकel_panel *panel = &connector->panel;
	काष्ठा drm_device *dev = connector->base.dev;

	drm_modeset_lock(&dev->mode_config.connection_mutex, शून्य);
	DRM_DEBUG_KMS("updating intel_backlight, brightness=%d/%d\n",
		      bd->props.brightness, bd->props.max_brightness);
	पूर्णांकel_panel_set_backlight(connector->base.state, bd->props.brightness,
				  bd->props.max_brightness);

	/*
	 * Allow flipping bl_घातer as a sub-state of enabled. Sadly the
	 * backlight class device करोes not make it easy to to dअगरferentiate
	 * between callbacks क्रम brightness and bl_घातer, so our backlight_घातer
	 * callback needs to take this पूर्णांकo account.
	 */
	अगर (panel->backlight.enabled) अणु
		अगर (panel->backlight.घातer) अणु
			bool enable = bd->props.घातer == FB_BLANK_UNBLANK &&
				bd->props.brightness != 0;
			panel->backlight.घातer(connector, enable);
		पूर्ण
	पूर्ण अन्यथा अणु
		bd->props.घातer = FB_BLANK_POWERDOWN;
	पूर्ण

	drm_modeset_unlock(&dev->mode_config.connection_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_backlight_device_get_brightness(काष्ठा backlight_device *bd)
अणु
	काष्ठा पूर्णांकel_connector *connector = bl_get_data(bd);
	काष्ठा drm_device *dev = connector->base.dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	पूर्णांकel_wakeref_t wakeref;
	पूर्णांक ret = 0;

	with_पूर्णांकel_runसमय_pm(&dev_priv->runसमय_pm, wakeref) अणु
		u32 hw_level;

		drm_modeset_lock(&dev->mode_config.connection_mutex, शून्य);

		hw_level = पूर्णांकel_panel_get_backlight(connector);
		ret = scale_hw_to_user(connector,
				       hw_level, bd->props.max_brightness);

		drm_modeset_unlock(&dev->mode_config.connection_mutex);
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा backlight_ops पूर्णांकel_backlight_device_ops = अणु
	.update_status = पूर्णांकel_backlight_device_update_status,
	.get_brightness = पूर्णांकel_backlight_device_get_brightness,
पूर्ण;

पूर्णांक पूर्णांकel_backlight_device_रेजिस्टर(काष्ठा पूर्णांकel_connector *connector)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(connector->base.dev);
	काष्ठा पूर्णांकel_panel *panel = &connector->panel;
	काष्ठा backlight_properties props;

	अगर (WARN_ON(panel->backlight.device))
		वापस -ENODEV;

	अगर (!panel->backlight.present)
		वापस 0;

	WARN_ON(panel->backlight.max == 0);

	स_रखो(&props, 0, माप(props));
	props.type = BACKLIGHT_RAW;

	/*
	 * Note: Everything should work even अगर the backlight device max
	 * presented to the userspace is arbitrarily chosen.
	 */
	props.max_brightness = panel->backlight.max;
	props.brightness = scale_hw_to_user(connector,
					    panel->backlight.level,
					    props.max_brightness);

	अगर (panel->backlight.enabled)
		props.घातer = FB_BLANK_UNBLANK;
	अन्यथा
		props.घातer = FB_BLANK_POWERDOWN;

	/*
	 * Note: using the same name independent of the connector prevents
	 * registration of multiple backlight devices in the driver.
	 */
	panel->backlight.device =
		backlight_device_रेजिस्टर("intel_backlight",
					  connector->base.kdev,
					  connector,
					  &पूर्णांकel_backlight_device_ops, &props);

	अगर (IS_ERR(panel->backlight.device)) अणु
		drm_err(&i915->drm, "Failed to register backlight: %ld\n",
			PTR_ERR(panel->backlight.device));
		panel->backlight.device = शून्य;
		वापस -ENODEV;
	पूर्ण

	drm_dbg_kms(&i915->drm,
		    "Connector %s backlight sysfs interface registered\n",
		    connector->base.name);

	वापस 0;
पूर्ण

व्योम पूर्णांकel_backlight_device_unरेजिस्टर(काष्ठा पूर्णांकel_connector *connector)
अणु
	काष्ठा पूर्णांकel_panel *panel = &connector->panel;

	अगर (panel->backlight.device) अणु
		backlight_device_unरेजिस्टर(panel->backlight.device);
		panel->backlight.device = शून्य;
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_BACKLIGHT_CLASS_DEVICE */

/*
 * CNP: PWM घड़ी frequency is 19.2 MHz or 24 MHz.
 *      PWM increment = 1
 */
अटल u32 cnp_hz_to_pwm(काष्ठा पूर्णांकel_connector *connector, u32 pwm_freq_hz)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);

	वापस DIV_ROUND_CLOSEST(KHz(RUNTIME_INFO(dev_priv)->rawclk_freq),
				 pwm_freq_hz);
पूर्ण

/*
 * BXT: PWM घड़ी frequency = 19.2 MHz.
 */
अटल u32 bxt_hz_to_pwm(काष्ठा पूर्णांकel_connector *connector, u32 pwm_freq_hz)
अणु
	वापस DIV_ROUND_CLOSEST(KHz(19200), pwm_freq_hz);
पूर्ण

/*
 * SPT: This value represents the period of the PWM stream in घड़ी periods
 * multiplied by 16 (शेष increment) or 128 (alternate increment selected in
 * SCHICKEN_1 bit 0). PWM घड़ी is 24 MHz.
 */
अटल u32 spt_hz_to_pwm(काष्ठा पूर्णांकel_connector *connector, u32 pwm_freq_hz)
अणु
	काष्ठा पूर्णांकel_panel *panel = &connector->panel;
	u32 mul;

	अगर (panel->backlight.alternate_pwm_increment)
		mul = 128;
	अन्यथा
		mul = 16;

	वापस DIV_ROUND_CLOSEST(MHz(24), pwm_freq_hz * mul);
पूर्ण

/*
 * LPT: This value represents the period of the PWM stream in घड़ी periods
 * multiplied by 128 (शेष increment) or 16 (alternate increment, selected in
 * LPT SOUTH_CHICKEN2 रेजिस्टर bit 5).
 */
अटल u32 lpt_hz_to_pwm(काष्ठा पूर्णांकel_connector *connector, u32 pwm_freq_hz)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	काष्ठा पूर्णांकel_panel *panel = &connector->panel;
	u32 mul, घड़ी;

	अगर (panel->backlight.alternate_pwm_increment)
		mul = 16;
	अन्यथा
		mul = 128;

	अगर (HAS_PCH_LPT_H(dev_priv))
		घड़ी = MHz(135); /* LPT:H */
	अन्यथा
		घड़ी = MHz(24); /* LPT:LP */

	वापस DIV_ROUND_CLOSEST(घड़ी, pwm_freq_hz * mul);
पूर्ण

/*
 * ILK/SNB/IVB: This value represents the period of the PWM stream in PCH
 * display raw घड़ीs multiplied by 128.
 */
अटल u32 pch_hz_to_pwm(काष्ठा पूर्णांकel_connector *connector, u32 pwm_freq_hz)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);

	वापस DIV_ROUND_CLOSEST(KHz(RUNTIME_INFO(dev_priv)->rawclk_freq),
				 pwm_freq_hz * 128);
पूर्ण

/*
 * Gen2: This field determines the number of समय base events (display core
 * घड़ी frequency/32) in total क्रम a complete cycle of modulated backlight
 * control.
 *
 * Gen3: A समय base event equals the display core घड़ी ([DevPNV] HRAW घड़ी)
 * भागided by 32.
 */
अटल u32 i9xx_hz_to_pwm(काष्ठा पूर्णांकel_connector *connector, u32 pwm_freq_hz)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	पूर्णांक घड़ी;

	अगर (IS_PINEVIEW(dev_priv))
		घड़ी = KHz(RUNTIME_INFO(dev_priv)->rawclk_freq);
	अन्यथा
		घड़ी = KHz(dev_priv->cdclk.hw.cdclk);

	वापस DIV_ROUND_CLOSEST(घड़ी, pwm_freq_hz * 32);
पूर्ण

/*
 * Gen4: This value represents the period of the PWM stream in display core
 * घड़ीs ([DevCTG] HRAW घड़ीs) multiplied by 128.
 *
 */
अटल u32 i965_hz_to_pwm(काष्ठा पूर्णांकel_connector *connector, u32 pwm_freq_hz)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	पूर्णांक घड़ी;

	अगर (IS_G4X(dev_priv))
		घड़ी = KHz(RUNTIME_INFO(dev_priv)->rawclk_freq);
	अन्यथा
		घड़ी = KHz(dev_priv->cdclk.hw.cdclk);

	वापस DIV_ROUND_CLOSEST(घड़ी, pwm_freq_hz * 128);
पूर्ण

/*
 * VLV: This value represents the period of the PWM stream in display core
 * घड़ीs ([DevCTG] 200MHz HRAW घड़ीs) multiplied by 128 or 25MHz S0IX घड़ीs
 * multiplied by 16. CHV uses a 19.2MHz S0IX घड़ी.
 */
अटल u32 vlv_hz_to_pwm(काष्ठा पूर्णांकel_connector *connector, u32 pwm_freq_hz)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	पूर्णांक mul, घड़ी;

	अगर ((पूर्णांकel_de_पढ़ो(dev_priv, CBR1_VLV) & CBR_PWM_CLOCK_MUX_SELECT) == 0) अणु
		अगर (IS_CHERRYVIEW(dev_priv))
			घड़ी = KHz(19200);
		अन्यथा
			घड़ी = MHz(25);
		mul = 16;
	पूर्ण अन्यथा अणु
		घड़ी = KHz(RUNTIME_INFO(dev_priv)->rawclk_freq);
		mul = 128;
	पूर्ण

	वापस DIV_ROUND_CLOSEST(घड़ी, pwm_freq_hz * mul);
पूर्ण

अटल u16 get_vbt_pwm_freq(काष्ठा drm_i915_निजी *dev_priv)
अणु
	u16 pwm_freq_hz = dev_priv->vbt.backlight.pwm_freq_hz;

	अगर (pwm_freq_hz) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "VBT defined backlight frequency %u Hz\n",
			    pwm_freq_hz);
	पूर्ण अन्यथा अणु
		pwm_freq_hz = 200;
		drm_dbg_kms(&dev_priv->drm,
			    "default backlight frequency %u Hz\n",
			    pwm_freq_hz);
	पूर्ण

	वापस pwm_freq_hz;
पूर्ण

अटल u32 get_backlight_max_vbt(काष्ठा पूर्णांकel_connector *connector)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	काष्ठा पूर्णांकel_panel *panel = &connector->panel;
	u16 pwm_freq_hz = get_vbt_pwm_freq(dev_priv);
	u32 pwm;

	अगर (!panel->backlight.pwm_funcs->hz_to_pwm) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "backlight frequency conversion not supported\n");
		वापस 0;
	पूर्ण

	pwm = panel->backlight.pwm_funcs->hz_to_pwm(connector, pwm_freq_hz);
	अगर (!pwm) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "backlight frequency conversion failed\n");
		वापस 0;
	पूर्ण

	वापस pwm;
पूर्ण

/*
 * Note: The setup hooks can't assume pipe is set!
 */
अटल u32 get_backlight_min_vbt(काष्ठा पूर्णांकel_connector *connector)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	काष्ठा पूर्णांकel_panel *panel = &connector->panel;
	पूर्णांक min;

	drm_WARN_ON(&dev_priv->drm, panel->backlight.pwm_level_max == 0);

	/*
	 * XXX: If the vbt value is 255, it makes min equal to max, which leads
	 * to problems. There are such machines out there. Either our
	 * पूर्णांकerpretation is wrong or the vbt has bogus data. Or both. Safeguard
	 * against this by letting the minimum be at most (arbitrarily chosen)
	 * 25% of the max.
	 */
	min = clamp_t(पूर्णांक, dev_priv->vbt.backlight.min_brightness, 0, 64);
	अगर (min != dev_priv->vbt.backlight.min_brightness) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "clamping VBT min backlight %d/255 to %d/255\n",
			    dev_priv->vbt.backlight.min_brightness, min);
	पूर्ण

	/* vbt value is a coefficient in range [0..255] */
	वापस scale(min, 0, 255, 0, panel->backlight.pwm_level_max);
पूर्ण

अटल पूर्णांक lpt_setup_backlight(काष्ठा पूर्णांकel_connector *connector, क्रमागत pipe unused)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	काष्ठा पूर्णांकel_panel *panel = &connector->panel;
	u32 cpu_ctl2, pch_ctl1, pch_ctl2, val;
	bool alt, cpu_mode;

	अगर (HAS_PCH_LPT(dev_priv))
		alt = पूर्णांकel_de_पढ़ो(dev_priv, SOUTH_CHICKEN2) & LPT_PWM_GRANULARITY;
	अन्यथा
		alt = पूर्णांकel_de_पढ़ो(dev_priv, SOUTH_CHICKEN1) & SPT_PWM_GRANULARITY;
	panel->backlight.alternate_pwm_increment = alt;

	pch_ctl1 = पूर्णांकel_de_पढ़ो(dev_priv, BLC_PWM_PCH_CTL1);
	panel->backlight.active_low_pwm = pch_ctl1 & BLM_PCH_POLARITY;

	pch_ctl2 = पूर्णांकel_de_पढ़ो(dev_priv, BLC_PWM_PCH_CTL2);
	panel->backlight.pwm_level_max = pch_ctl2 >> 16;

	cpu_ctl2 = पूर्णांकel_de_पढ़ो(dev_priv, BLC_PWM_CPU_CTL2);

	अगर (!panel->backlight.pwm_level_max)
		panel->backlight.pwm_level_max = get_backlight_max_vbt(connector);

	अगर (!panel->backlight.pwm_level_max)
		वापस -ENODEV;

	panel->backlight.pwm_level_min = get_backlight_min_vbt(connector);

	panel->backlight.pwm_enabled = pch_ctl1 & BLM_PCH_PWM_ENABLE;

	cpu_mode = panel->backlight.pwm_enabled && HAS_PCH_LPT(dev_priv) &&
		   !(pch_ctl1 & BLM_PCH_OVERRIDE_ENABLE) &&
		   (cpu_ctl2 & BLM_PWM_ENABLE);

	अगर (cpu_mode) अणु
		val = pch_get_backlight(connector, unused);

		drm_dbg_kms(&dev_priv->drm,
			    "CPU backlight register was enabled, switching to PCH override\n");

		/* Write converted CPU PWM value to PCH override रेजिस्टर */
		lpt_set_backlight(connector->base.state, val);
		पूर्णांकel_de_ग_लिखो(dev_priv, BLC_PWM_PCH_CTL1,
			       pch_ctl1 | BLM_PCH_OVERRIDE_ENABLE);

		पूर्णांकel_de_ग_लिखो(dev_priv, BLC_PWM_CPU_CTL2,
			       cpu_ctl2 & ~BLM_PWM_ENABLE);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pch_setup_backlight(काष्ठा पूर्णांकel_connector *connector, क्रमागत pipe unused)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	काष्ठा पूर्णांकel_panel *panel = &connector->panel;
	u32 cpu_ctl2, pch_ctl1, pch_ctl2;

	pch_ctl1 = पूर्णांकel_de_पढ़ो(dev_priv, BLC_PWM_PCH_CTL1);
	panel->backlight.active_low_pwm = pch_ctl1 & BLM_PCH_POLARITY;

	pch_ctl2 = पूर्णांकel_de_पढ़ो(dev_priv, BLC_PWM_PCH_CTL2);
	panel->backlight.pwm_level_max = pch_ctl2 >> 16;

	अगर (!panel->backlight.pwm_level_max)
		panel->backlight.pwm_level_max = get_backlight_max_vbt(connector);

	अगर (!panel->backlight.pwm_level_max)
		वापस -ENODEV;

	panel->backlight.pwm_level_min = get_backlight_min_vbt(connector);

	cpu_ctl2 = पूर्णांकel_de_पढ़ो(dev_priv, BLC_PWM_CPU_CTL2);
	panel->backlight.pwm_enabled = (cpu_ctl2 & BLM_PWM_ENABLE) &&
		(pch_ctl1 & BLM_PCH_PWM_ENABLE);

	वापस 0;
पूर्ण

अटल पूर्णांक i9xx_setup_backlight(काष्ठा पूर्णांकel_connector *connector, क्रमागत pipe unused)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	काष्ठा पूर्णांकel_panel *panel = &connector->panel;
	u32 ctl, val;

	ctl = पूर्णांकel_de_पढ़ो(dev_priv, BLC_PWM_CTL);

	अगर (IS_DISPLAY_VER(dev_priv, 2) || IS_I915GM(dev_priv) || IS_I945GM(dev_priv))
		panel->backlight.combination_mode = ctl & BLM_LEGACY_MODE;

	अगर (IS_PINEVIEW(dev_priv))
		panel->backlight.active_low_pwm = ctl & BLM_POLARITY_PNV;

	panel->backlight.pwm_level_max = ctl >> 17;

	अगर (!panel->backlight.pwm_level_max) अणु
		panel->backlight.pwm_level_max = get_backlight_max_vbt(connector);
		panel->backlight.pwm_level_max >>= 1;
	पूर्ण

	अगर (!panel->backlight.pwm_level_max)
		वापस -ENODEV;

	अगर (panel->backlight.combination_mode)
		panel->backlight.pwm_level_max *= 0xff;

	panel->backlight.pwm_level_min = get_backlight_min_vbt(connector);

	val = i9xx_get_backlight(connector, unused);
	val = पूर्णांकel_panel_invert_pwm_level(connector, val);
	val = clamp(val, panel->backlight.pwm_level_min, panel->backlight.pwm_level_max);

	panel->backlight.pwm_enabled = val != 0;

	वापस 0;
पूर्ण

अटल पूर्णांक i965_setup_backlight(काष्ठा पूर्णांकel_connector *connector, क्रमागत pipe unused)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	काष्ठा पूर्णांकel_panel *panel = &connector->panel;
	u32 ctl, ctl2;

	ctl2 = पूर्णांकel_de_पढ़ो(dev_priv, BLC_PWM_CTL2);
	panel->backlight.combination_mode = ctl2 & BLM_COMBINATION_MODE;
	panel->backlight.active_low_pwm = ctl2 & BLM_POLARITY_I965;

	ctl = पूर्णांकel_de_पढ़ो(dev_priv, BLC_PWM_CTL);
	panel->backlight.pwm_level_max = ctl >> 16;

	अगर (!panel->backlight.pwm_level_max)
		panel->backlight.pwm_level_max = get_backlight_max_vbt(connector);

	अगर (!panel->backlight.pwm_level_max)
		वापस -ENODEV;

	अगर (panel->backlight.combination_mode)
		panel->backlight.pwm_level_max *= 0xff;

	panel->backlight.pwm_level_min = get_backlight_min_vbt(connector);

	panel->backlight.pwm_enabled = ctl2 & BLM_PWM_ENABLE;

	वापस 0;
पूर्ण

अटल पूर्णांक vlv_setup_backlight(काष्ठा पूर्णांकel_connector *connector, क्रमागत pipe pipe)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	काष्ठा पूर्णांकel_panel *panel = &connector->panel;
	u32 ctl, ctl2;

	अगर (drm_WARN_ON(&dev_priv->drm, pipe != PIPE_A && pipe != PIPE_B))
		वापस -ENODEV;

	ctl2 = पूर्णांकel_de_पढ़ो(dev_priv, VLV_BLC_PWM_CTL2(pipe));
	panel->backlight.active_low_pwm = ctl2 & BLM_POLARITY_I965;

	ctl = पूर्णांकel_de_पढ़ो(dev_priv, VLV_BLC_PWM_CTL(pipe));
	panel->backlight.pwm_level_max = ctl >> 16;

	अगर (!panel->backlight.pwm_level_max)
		panel->backlight.pwm_level_max = get_backlight_max_vbt(connector);

	अगर (!panel->backlight.pwm_level_max)
		वापस -ENODEV;

	panel->backlight.pwm_level_min = get_backlight_min_vbt(connector);

	panel->backlight.pwm_enabled = ctl2 & BLM_PWM_ENABLE;

	वापस 0;
पूर्ण

अटल पूर्णांक
bxt_setup_backlight(काष्ठा पूर्णांकel_connector *connector, क्रमागत pipe unused)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	काष्ठा पूर्णांकel_panel *panel = &connector->panel;
	u32 pwm_ctl, val;

	panel->backlight.controller = dev_priv->vbt.backlight.controller;

	pwm_ctl = पूर्णांकel_de_पढ़ो(dev_priv,
				BXT_BLC_PWM_CTL(panel->backlight.controller));

	/* Controller 1 uses the utility pin. */
	अगर (panel->backlight.controller == 1) अणु
		val = पूर्णांकel_de_पढ़ो(dev_priv, UTIL_PIN_CTL);
		panel->backlight.util_pin_active_low =
					val & UTIL_PIN_POLARITY;
	पूर्ण

	panel->backlight.active_low_pwm = pwm_ctl & BXT_BLC_PWM_POLARITY;
	panel->backlight.pwm_level_max =
		पूर्णांकel_de_पढ़ो(dev_priv, BXT_BLC_PWM_FREQ(panel->backlight.controller));

	अगर (!panel->backlight.pwm_level_max)
		panel->backlight.pwm_level_max = get_backlight_max_vbt(connector);

	अगर (!panel->backlight.pwm_level_max)
		वापस -ENODEV;

	panel->backlight.pwm_level_min = get_backlight_min_vbt(connector);

	panel->backlight.pwm_enabled = pwm_ctl & BXT_BLC_PWM_ENABLE;

	वापस 0;
पूर्ण

अटल पूर्णांक
cnp_setup_backlight(काष्ठा पूर्णांकel_connector *connector, क्रमागत pipe unused)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	काष्ठा पूर्णांकel_panel *panel = &connector->panel;
	u32 pwm_ctl;

	/*
	 * CNP has the BXT implementation of backlight, but with only one
	 * controller. TODO: ICP has multiple controllers but we only use
	 * controller 0 क्रम now.
	 */
	panel->backlight.controller = 0;

	pwm_ctl = पूर्णांकel_de_पढ़ो(dev_priv,
				BXT_BLC_PWM_CTL(panel->backlight.controller));

	panel->backlight.active_low_pwm = pwm_ctl & BXT_BLC_PWM_POLARITY;
	panel->backlight.pwm_level_max =
		पूर्णांकel_de_पढ़ो(dev_priv, BXT_BLC_PWM_FREQ(panel->backlight.controller));

	अगर (!panel->backlight.pwm_level_max)
		panel->backlight.pwm_level_max = get_backlight_max_vbt(connector);

	अगर (!panel->backlight.pwm_level_max)
		वापस -ENODEV;

	panel->backlight.pwm_level_min = get_backlight_min_vbt(connector);

	panel->backlight.pwm_enabled = pwm_ctl & BXT_BLC_PWM_ENABLE;

	वापस 0;
पूर्ण

अटल पूर्णांक ext_pwm_setup_backlight(काष्ठा पूर्णांकel_connector *connector,
				   क्रमागत pipe pipe)
अणु
	काष्ठा drm_device *dev = connector->base.dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	काष्ठा पूर्णांकel_panel *panel = &connector->panel;
	स्थिर अक्षर *desc;
	u32 level;

	/* Get the right PWM chip क्रम DSI backlight according to VBT */
	अगर (dev_priv->vbt.dsi.config->pwm_blc == PPS_BLC_PMIC) अणु
		panel->backlight.pwm = pwm_get(dev->dev, "pwm_pmic_backlight");
		desc = "PMIC";
	पूर्ण अन्यथा अणु
		panel->backlight.pwm = pwm_get(dev->dev, "pwm_soc_backlight");
		desc = "SoC";
	पूर्ण

	अगर (IS_ERR(panel->backlight.pwm)) अणु
		drm_err(&dev_priv->drm, "Failed to get the %s PWM chip\n",
			desc);
		panel->backlight.pwm = शून्य;
		वापस -ENODEV;
	पूर्ण

	panel->backlight.pwm_level_max = 100; /* 100% */
	panel->backlight.pwm_level_min = get_backlight_min_vbt(connector);

	अगर (pwm_is_enabled(panel->backlight.pwm)) अणु
		/* PWM is alपढ़ोy enabled, use existing settings */
		pwm_get_state(panel->backlight.pwm, &panel->backlight.pwm_state);

		level = pwm_get_relative_duty_cycle(&panel->backlight.pwm_state,
						    100);
		level = पूर्णांकel_panel_invert_pwm_level(connector, level);
		panel->backlight.pwm_enabled = true;

		drm_dbg_kms(&dev_priv->drm, "PWM already enabled at freq %ld, VBT freq %d, level %d\n",
			    NSEC_PER_SEC / (अचिन्हित दीर्घ)panel->backlight.pwm_state.period,
			    get_vbt_pwm_freq(dev_priv), level);
	पूर्ण अन्यथा अणु
		/* Set period from VBT frequency, leave other settings at 0. */
		panel->backlight.pwm_state.period =
			NSEC_PER_SEC / get_vbt_pwm_freq(dev_priv);
	पूर्ण

	drm_info(&dev_priv->drm, "Using %s PWM for LCD backlight control\n",
		 desc);
	वापस 0;
पूर्ण

अटल व्योम पूर्णांकel_pwm_set_backlight(स्थिर काष्ठा drm_connector_state *conn_state, u32 level)
अणु
	काष्ठा पूर्णांकel_connector *connector = to_पूर्णांकel_connector(conn_state->connector);
	काष्ठा पूर्णांकel_panel *panel = &connector->panel;

	panel->backlight.pwm_funcs->set(conn_state,
				       पूर्णांकel_panel_invert_pwm_level(connector, level));
पूर्ण

अटल u32 पूर्णांकel_pwm_get_backlight(काष्ठा पूर्णांकel_connector *connector, क्रमागत pipe pipe)
अणु
	काष्ठा पूर्णांकel_panel *panel = &connector->panel;

	वापस पूर्णांकel_panel_invert_pwm_level(connector,
					    panel->backlight.pwm_funcs->get(connector, pipe));
पूर्ण

अटल व्योम पूर्णांकel_pwm_enable_backlight(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				       स्थिर काष्ठा drm_connector_state *conn_state, u32 level)
अणु
	काष्ठा पूर्णांकel_connector *connector = to_पूर्णांकel_connector(conn_state->connector);
	काष्ठा पूर्णांकel_panel *panel = &connector->panel;

	panel->backlight.pwm_funcs->enable(crtc_state, conn_state,
					   पूर्णांकel_panel_invert_pwm_level(connector, level));
पूर्ण

अटल व्योम पूर्णांकel_pwm_disable_backlight(स्थिर काष्ठा drm_connector_state *conn_state, u32 level)
अणु
	काष्ठा पूर्णांकel_connector *connector = to_पूर्णांकel_connector(conn_state->connector);
	काष्ठा पूर्णांकel_panel *panel = &connector->panel;

	panel->backlight.pwm_funcs->disable(conn_state,
					    पूर्णांकel_panel_invert_pwm_level(connector, level));
पूर्ण

अटल पूर्णांक पूर्णांकel_pwm_setup_backlight(काष्ठा पूर्णांकel_connector *connector, क्रमागत pipe pipe)
अणु
	काष्ठा पूर्णांकel_panel *panel = &connector->panel;
	पूर्णांक ret = panel->backlight.pwm_funcs->setup(connector, pipe);

	अगर (ret < 0)
		वापस ret;

	panel->backlight.min = panel->backlight.pwm_level_min;
	panel->backlight.max = panel->backlight.pwm_level_max;
	panel->backlight.level = पूर्णांकel_pwm_get_backlight(connector, pipe);
	panel->backlight.enabled = panel->backlight.pwm_enabled;

	वापस 0;
पूर्ण

व्योम पूर्णांकel_panel_update_backlight(काष्ठा पूर्णांकel_atomic_state *state,
				  काष्ठा पूर्णांकel_encoder *encoder,
				  स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				  स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा पूर्णांकel_connector *connector = to_पूर्णांकel_connector(conn_state->connector);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	काष्ठा पूर्णांकel_panel *panel = &connector->panel;

	अगर (!panel->backlight.present)
		वापस;

	mutex_lock(&dev_priv->backlight_lock);
	अगर (!panel->backlight.enabled)
		__पूर्णांकel_panel_enable_backlight(crtc_state, conn_state);

	mutex_unlock(&dev_priv->backlight_lock);
पूर्ण

पूर्णांक पूर्णांकel_panel_setup_backlight(काष्ठा drm_connector *connector, क्रमागत pipe pipe)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->dev);
	काष्ठा पूर्णांकel_connector *पूर्णांकel_connector = to_पूर्णांकel_connector(connector);
	काष्ठा पूर्णांकel_panel *panel = &पूर्णांकel_connector->panel;
	पूर्णांक ret;

	अगर (!dev_priv->vbt.backlight.present) अणु
		अगर (dev_priv->quirks & QUIRK_BACKLIGHT_PRESENT) अणु
			drm_dbg_kms(&dev_priv->drm,
				    "no backlight present per VBT, but present per quirk\n");
		पूर्ण अन्यथा अणु
			drm_dbg_kms(&dev_priv->drm,
				    "no backlight present per VBT\n");
			वापस 0;
		पूर्ण
	पूर्ण

	/* ensure पूर्णांकel_panel has been initialized first */
	अगर (drm_WARN_ON(&dev_priv->drm, !panel->backlight.funcs))
		वापस -ENODEV;

	/* set level and max in panel काष्ठा */
	mutex_lock(&dev_priv->backlight_lock);
	ret = panel->backlight.funcs->setup(पूर्णांकel_connector, pipe);
	mutex_unlock(&dev_priv->backlight_lock);

	अगर (ret) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "failed to setup backlight for connector %s\n",
			    connector->name);
		वापस ret;
	पूर्ण

	panel->backlight.present = true;

	drm_dbg_kms(&dev_priv->drm,
		    "Connector %s backlight initialized, %s, brightness %u/%u\n",
		    connector->name,
		    enableddisabled(panel->backlight.enabled),
		    panel->backlight.level, panel->backlight.max);

	वापस 0;
पूर्ण

अटल व्योम पूर्णांकel_panel_destroy_backlight(काष्ठा पूर्णांकel_panel *panel)
अणु
	/* dispose of the pwm */
	अगर (panel->backlight.pwm)
		pwm_put(panel->backlight.pwm);

	panel->backlight.present = false;
पूर्ण

अटल स्थिर काष्ठा पूर्णांकel_panel_bl_funcs bxt_pwm_funcs = अणु
	.setup = bxt_setup_backlight,
	.enable = bxt_enable_backlight,
	.disable = bxt_disable_backlight,
	.set = bxt_set_backlight,
	.get = bxt_get_backlight,
	.hz_to_pwm = bxt_hz_to_pwm,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_panel_bl_funcs cnp_pwm_funcs = अणु
	.setup = cnp_setup_backlight,
	.enable = cnp_enable_backlight,
	.disable = cnp_disable_backlight,
	.set = bxt_set_backlight,
	.get = bxt_get_backlight,
	.hz_to_pwm = cnp_hz_to_pwm,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_panel_bl_funcs lpt_pwm_funcs = अणु
	.setup = lpt_setup_backlight,
	.enable = lpt_enable_backlight,
	.disable = lpt_disable_backlight,
	.set = lpt_set_backlight,
	.get = lpt_get_backlight,
	.hz_to_pwm = lpt_hz_to_pwm,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_panel_bl_funcs spt_pwm_funcs = अणु
	.setup = lpt_setup_backlight,
	.enable = lpt_enable_backlight,
	.disable = lpt_disable_backlight,
	.set = lpt_set_backlight,
	.get = lpt_get_backlight,
	.hz_to_pwm = spt_hz_to_pwm,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_panel_bl_funcs pch_pwm_funcs = अणु
	.setup = pch_setup_backlight,
	.enable = pch_enable_backlight,
	.disable = pch_disable_backlight,
	.set = pch_set_backlight,
	.get = pch_get_backlight,
	.hz_to_pwm = pch_hz_to_pwm,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_panel_bl_funcs ext_pwm_funcs = अणु
	.setup = ext_pwm_setup_backlight,
	.enable = ext_pwm_enable_backlight,
	.disable = ext_pwm_disable_backlight,
	.set = ext_pwm_set_backlight,
	.get = ext_pwm_get_backlight,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_panel_bl_funcs vlv_pwm_funcs = अणु
	.setup = vlv_setup_backlight,
	.enable = vlv_enable_backlight,
	.disable = vlv_disable_backlight,
	.set = vlv_set_backlight,
	.get = vlv_get_backlight,
	.hz_to_pwm = vlv_hz_to_pwm,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_panel_bl_funcs i965_pwm_funcs = अणु
	.setup = i965_setup_backlight,
	.enable = i965_enable_backlight,
	.disable = i965_disable_backlight,
	.set = i9xx_set_backlight,
	.get = i9xx_get_backlight,
	.hz_to_pwm = i965_hz_to_pwm,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_panel_bl_funcs i9xx_pwm_funcs = अणु
	.setup = i9xx_setup_backlight,
	.enable = i9xx_enable_backlight,
	.disable = i9xx_disable_backlight,
	.set = i9xx_set_backlight,
	.get = i9xx_get_backlight,
	.hz_to_pwm = i9xx_hz_to_pwm,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_panel_bl_funcs pwm_bl_funcs = अणु
	.setup = पूर्णांकel_pwm_setup_backlight,
	.enable = पूर्णांकel_pwm_enable_backlight,
	.disable = पूर्णांकel_pwm_disable_backlight,
	.set = पूर्णांकel_pwm_set_backlight,
	.get = पूर्णांकel_pwm_get_backlight,
पूर्ण;

/* Set up chip specअगरic backlight functions */
अटल व्योम
पूर्णांकel_panel_init_backlight_funcs(काष्ठा पूर्णांकel_panel *panel)
अणु
	काष्ठा पूर्णांकel_connector *connector =
		container_of(panel, काष्ठा पूर्णांकel_connector, panel);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);

	अगर (connector->base.connector_type == DRM_MODE_CONNECTOR_DSI &&
	    पूर्णांकel_dsi_dcs_init_backlight_funcs(connector) == 0)
		वापस;

	अगर (IS_GEN9_LP(dev_priv)) अणु
		panel->backlight.pwm_funcs = &bxt_pwm_funcs;
	पूर्ण अन्यथा अगर (INTEL_PCH_TYPE(dev_priv) >= PCH_CNP) अणु
		panel->backlight.pwm_funcs = &cnp_pwm_funcs;
	पूर्ण अन्यथा अगर (INTEL_PCH_TYPE(dev_priv) >= PCH_LPT) अणु
		अगर (HAS_PCH_LPT(dev_priv))
			panel->backlight.pwm_funcs = &lpt_pwm_funcs;
		अन्यथा
			panel->backlight.pwm_funcs = &spt_pwm_funcs;
	पूर्ण अन्यथा अगर (HAS_PCH_SPLIT(dev_priv)) अणु
		panel->backlight.pwm_funcs = &pch_pwm_funcs;
	पूर्ण अन्यथा अगर (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv)) अणु
		अगर (connector->base.connector_type == DRM_MODE_CONNECTOR_DSI) अणु
			panel->backlight.pwm_funcs = &ext_pwm_funcs;
		पूर्ण अन्यथा अणु
			panel->backlight.pwm_funcs = &vlv_pwm_funcs;
		पूर्ण
	पूर्ण अन्यथा अगर (IS_DISPLAY_VER(dev_priv, 4)) अणु
		panel->backlight.pwm_funcs = &i965_pwm_funcs;
	पूर्ण अन्यथा अणु
		panel->backlight.pwm_funcs = &i9xx_pwm_funcs;
	पूर्ण

	अगर (connector->base.connector_type == DRM_MODE_CONNECTOR_eDP &&
	    पूर्णांकel_dp_aux_init_backlight_funcs(connector) == 0)
		वापस;

	/* We're using a standard PWM backlight पूर्णांकerface */
	panel->backlight.funcs = &pwm_bl_funcs;
पूर्ण

क्रमागत drm_connector_status
पूर्णांकel_panel_detect(काष्ठा drm_connector *connector, bool क्रमce)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(connector->dev);

	अगर (!INTEL_DISPLAY_ENABLED(i915))
		वापस connector_status_disconnected;

	वापस connector_status_connected;
पूर्ण

पूर्णांक पूर्णांकel_panel_init(काष्ठा पूर्णांकel_panel *panel,
		     काष्ठा drm_display_mode *fixed_mode,
		     काष्ठा drm_display_mode *करोwnघड़ी_mode)
अणु
	पूर्णांकel_panel_init_backlight_funcs(panel);

	panel->fixed_mode = fixed_mode;
	panel->करोwnघड़ी_mode = करोwnघड़ी_mode;

	वापस 0;
पूर्ण

व्योम पूर्णांकel_panel_fini(काष्ठा पूर्णांकel_panel *panel)
अणु
	काष्ठा पूर्णांकel_connector *पूर्णांकel_connector =
		container_of(panel, काष्ठा पूर्णांकel_connector, panel);

	पूर्णांकel_panel_destroy_backlight(panel);

	अगर (panel->fixed_mode)
		drm_mode_destroy(पूर्णांकel_connector->base.dev, panel->fixed_mode);

	अगर (panel->करोwnघड़ी_mode)
		drm_mode_destroy(पूर्णांकel_connector->base.dev,
				panel->करोwnघड़ी_mode);
पूर्ण
