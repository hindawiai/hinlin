<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) Icenowy Zheng <icenowy@aosc.io>
 *
 * Based on sun4i_layer.h, which is:
 *   Copyright (C) 2015 Free Electrons
 *   Copyright (C) 2015 NextThing Co
 *
 *   Maxime Ripard <maxime.ripard@मुक्त-electrons.com>
 */

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_fb_cma_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_gem_atomic_helper.h>
#समावेश <drm/drm_gem_cma_helper.h>
#समावेश <drm/drm_plane_helper.h>
#समावेश <drm/drm_probe_helper.h>

#समावेश "sun8i_mixer.h"
#समावेश "sun8i_ui_layer.h"
#समावेश "sun8i_ui_scaler.h"

अटल व्योम sun8i_ui_layer_enable(काष्ठा sun8i_mixer *mixer, पूर्णांक channel,
				  पूर्णांक overlay, bool enable, अचिन्हित पूर्णांक zpos,
				  अचिन्हित पूर्णांक old_zpos)
अणु
	u32 val, bld_base, ch_base;

	bld_base = sun8i_blender_base(mixer);
	ch_base = sun8i_channel_base(mixer, channel);

	DRM_DEBUG_DRIVER("%sabling channel %d overlay %d\n",
			 enable ? "En" : "Dis", channel, overlay);

	अगर (enable)
		val = SUN8I_MIXER_CHAN_UI_LAYER_ATTR_EN;
	अन्यथा
		val = 0;

	regmap_update_bits(mixer->engine.regs,
			   SUN8I_MIXER_CHAN_UI_LAYER_ATTR(ch_base, overlay),
			   SUN8I_MIXER_CHAN_UI_LAYER_ATTR_EN, val);

	अगर (!enable || zpos != old_zpos) अणु
		regmap_update_bits(mixer->engine.regs,
				   SUN8I_MIXER_BLEND_PIPE_CTL(bld_base),
				   SUN8I_MIXER_BLEND_PIPE_CTL_EN(old_zpos),
				   0);

		regmap_update_bits(mixer->engine.regs,
				   SUN8I_MIXER_BLEND_ROUTE(bld_base),
				   SUN8I_MIXER_BLEND_ROUTE_PIPE_MSK(old_zpos),
				   0);
	पूर्ण

	अगर (enable) अणु
		val = SUN8I_MIXER_BLEND_PIPE_CTL_EN(zpos);

		regmap_update_bits(mixer->engine.regs,
				   SUN8I_MIXER_BLEND_PIPE_CTL(bld_base),
				   val, val);

		val = channel << SUN8I_MIXER_BLEND_ROUTE_PIPE_SHIFT(zpos);

		regmap_update_bits(mixer->engine.regs,
				   SUN8I_MIXER_BLEND_ROUTE(bld_base),
				   SUN8I_MIXER_BLEND_ROUTE_PIPE_MSK(zpos),
				   val);
	पूर्ण
पूर्ण

अटल व्योम sun8i_ui_layer_update_alpha(काष्ठा sun8i_mixer *mixer, पूर्णांक channel,
					पूर्णांक overlay, काष्ठा drm_plane *plane)
अणु
	u32 mask, val, ch_base;

	ch_base = sun8i_channel_base(mixer, channel);

	mask = SUN8I_MIXER_CHAN_UI_LAYER_ATTR_ALPHA_MODE_MASK |
		SUN8I_MIXER_CHAN_UI_LAYER_ATTR_ALPHA_MASK;

	val = SUN8I_MIXER_CHAN_UI_LAYER_ATTR_ALPHA(plane->state->alpha >> 8);

	val |= (plane->state->alpha == DRM_BLEND_ALPHA_OPAQUE) ?
		SUN8I_MIXER_CHAN_UI_LAYER_ATTR_ALPHA_MODE_PIXEL :
		SUN8I_MIXER_CHAN_UI_LAYER_ATTR_ALPHA_MODE_COMBINED;

	regmap_update_bits(mixer->engine.regs,
			   SUN8I_MIXER_CHAN_UI_LAYER_ATTR(ch_base, overlay),
			   mask, val);
पूर्ण

अटल पूर्णांक sun8i_ui_layer_update_coord(काष्ठा sun8i_mixer *mixer, पूर्णांक channel,
				       पूर्णांक overlay, काष्ठा drm_plane *plane,
				       अचिन्हित पूर्णांक zpos)
अणु
	काष्ठा drm_plane_state *state = plane->state;
	u32 src_w, src_h, dst_w, dst_h;
	u32 bld_base, ch_base;
	u32 outsize, insize;
	u32 hphase, vphase;

	DRM_DEBUG_DRIVER("Updating UI channel %d overlay %d\n",
			 channel, overlay);

	bld_base = sun8i_blender_base(mixer);
	ch_base = sun8i_channel_base(mixer, channel);

	src_w = drm_rect_width(&state->src) >> 16;
	src_h = drm_rect_height(&state->src) >> 16;
	dst_w = drm_rect_width(&state->dst);
	dst_h = drm_rect_height(&state->dst);

	hphase = state->src.x1 & 0xffff;
	vphase = state->src.y1 & 0xffff;

	insize = SUN8I_MIXER_SIZE(src_w, src_h);
	outsize = SUN8I_MIXER_SIZE(dst_w, dst_h);

	अगर (plane->type == DRM_PLANE_TYPE_PRIMARY) अणु
		bool पूर्णांकerlaced = false;
		u32 val;

		DRM_DEBUG_DRIVER("Primary layer, updating global size W: %u H: %u\n",
				 dst_w, dst_h);
		regmap_ग_लिखो(mixer->engine.regs,
			     SUN8I_MIXER_GLOBAL_SIZE,
			     outsize);
		regmap_ग_लिखो(mixer->engine.regs,
			     SUN8I_MIXER_BLEND_OUTSIZE(bld_base), outsize);

		अगर (state->crtc)
			पूर्णांकerlaced = state->crtc->state->adjusted_mode.flags
				& DRM_MODE_FLAG_INTERLACE;

		अगर (पूर्णांकerlaced)
			val = SUN8I_MIXER_BLEND_OUTCTL_INTERLACED;
		अन्यथा
			val = 0;

		regmap_update_bits(mixer->engine.regs,
				   SUN8I_MIXER_BLEND_OUTCTL(bld_base),
				   SUN8I_MIXER_BLEND_OUTCTL_INTERLACED,
				   val);

		DRM_DEBUG_DRIVER("Switching display mixer interlaced mode %s\n",
				 पूर्णांकerlaced ? "on" : "off");
	पूर्ण

	/* Set height and width */
	DRM_DEBUG_DRIVER("Layer source offset X: %d Y: %d\n",
			 state->src.x1 >> 16, state->src.y1 >> 16);
	DRM_DEBUG_DRIVER("Layer source size W: %d H: %d\n", src_w, src_h);
	regmap_ग_लिखो(mixer->engine.regs,
		     SUN8I_MIXER_CHAN_UI_LAYER_SIZE(ch_base, overlay),
		     insize);
	regmap_ग_लिखो(mixer->engine.regs,
		     SUN8I_MIXER_CHAN_UI_OVL_SIZE(ch_base),
		     insize);

	अगर (insize != outsize || hphase || vphase) अणु
		u32 hscale, vscale;

		DRM_DEBUG_DRIVER("HW scaling is enabled\n");

		hscale = state->src_w / state->crtc_w;
		vscale = state->src_h / state->crtc_h;

		sun8i_ui_scaler_setup(mixer, channel, src_w, src_h, dst_w,
				      dst_h, hscale, vscale, hphase, vphase);
		sun8i_ui_scaler_enable(mixer, channel, true);
	पूर्ण अन्यथा अणु
		DRM_DEBUG_DRIVER("HW scaling is not needed\n");
		sun8i_ui_scaler_enable(mixer, channel, false);
	पूर्ण

	/* Set base coordinates */
	DRM_DEBUG_DRIVER("Layer destination coordinates X: %d Y: %d\n",
			 state->dst.x1, state->dst.y1);
	DRM_DEBUG_DRIVER("Layer destination size W: %d H: %d\n", dst_w, dst_h);
	regmap_ग_लिखो(mixer->engine.regs,
		     SUN8I_MIXER_BLEND_ATTR_COORD(bld_base, zpos),
		     SUN8I_MIXER_COORD(state->dst.x1, state->dst.y1));
	regmap_ग_लिखो(mixer->engine.regs,
		     SUN8I_MIXER_BLEND_ATTR_INSIZE(bld_base, zpos),
		     outsize);

	वापस 0;
पूर्ण

अटल पूर्णांक sun8i_ui_layer_update_क्रमmats(काष्ठा sun8i_mixer *mixer, पूर्णांक channel,
					 पूर्णांक overlay, काष्ठा drm_plane *plane)
अणु
	काष्ठा drm_plane_state *state = plane->state;
	स्थिर काष्ठा drm_क्रमmat_info *fmt;
	u32 val, ch_base, hw_fmt;
	पूर्णांक ret;

	ch_base = sun8i_channel_base(mixer, channel);

	fmt = state->fb->क्रमmat;
	ret = sun8i_mixer_drm_क्रमmat_to_hw(fmt->क्रमmat, &hw_fmt);
	अगर (ret || fmt->is_yuv) अणु
		DRM_DEBUG_DRIVER("Invalid format\n");
		वापस -EINVAL;
	पूर्ण

	val = hw_fmt << SUN8I_MIXER_CHAN_UI_LAYER_ATTR_FBFMT_OFFSET;
	regmap_update_bits(mixer->engine.regs,
			   SUN8I_MIXER_CHAN_UI_LAYER_ATTR(ch_base, overlay),
			   SUN8I_MIXER_CHAN_UI_LAYER_ATTR_FBFMT_MASK, val);

	वापस 0;
पूर्ण

अटल पूर्णांक sun8i_ui_layer_update_buffer(काष्ठा sun8i_mixer *mixer, पूर्णांक channel,
					पूर्णांक overlay, काष्ठा drm_plane *plane)
अणु
	काष्ठा drm_plane_state *state = plane->state;
	काष्ठा drm_framebuffer *fb = state->fb;
	काष्ठा drm_gem_cma_object *gem;
	dma_addr_t paddr;
	u32 ch_base;
	पूर्णांक bpp;

	ch_base = sun8i_channel_base(mixer, channel);

	/* Get the physical address of the buffer in memory */
	gem = drm_fb_cma_get_gem_obj(fb, 0);

	DRM_DEBUG_DRIVER("Using GEM @ %pad\n", &gem->paddr);

	/* Compute the start of the displayed memory */
	bpp = fb->क्रमmat->cpp[0];
	paddr = gem->paddr + fb->offsets[0];

	/* Fixup framebuffer address क्रम src coordinates */
	paddr += (state->src.x1 >> 16) * bpp;
	paddr += (state->src.y1 >> 16) * fb->pitches[0];

	/* Set the line width */
	DRM_DEBUG_DRIVER("Layer line width: %d bytes\n", fb->pitches[0]);
	regmap_ग_लिखो(mixer->engine.regs,
		     SUN8I_MIXER_CHAN_UI_LAYER_PITCH(ch_base, overlay),
		     fb->pitches[0]);

	DRM_DEBUG_DRIVER("Setting buffer address to %pad\n", &paddr);

	regmap_ग_लिखो(mixer->engine.regs,
		     SUN8I_MIXER_CHAN_UI_LAYER_TOP_LADDR(ch_base, overlay),
		     lower_32_bits(paddr));

	वापस 0;
पूर्ण

अटल पूर्णांक sun8i_ui_layer_atomic_check(काष्ठा drm_plane *plane,
				       काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *new_plane_state = drm_atomic_get_new_plane_state(state,
										 plane);
	काष्ठा sun8i_ui_layer *layer = plane_to_sun8i_ui_layer(plane);
	काष्ठा drm_crtc *crtc = new_plane_state->crtc;
	काष्ठा drm_crtc_state *crtc_state;
	पूर्णांक min_scale, max_scale;

	अगर (!crtc)
		वापस 0;

	crtc_state = drm_atomic_get_existing_crtc_state(state,
							crtc);
	अगर (WARN_ON(!crtc_state))
		वापस -EINVAL;

	min_scale = DRM_PLANE_HELPER_NO_SCALING;
	max_scale = DRM_PLANE_HELPER_NO_SCALING;

	अगर (layer->mixer->cfg->scaler_mask & BIT(layer->channel)) अणु
		min_scale = SUN8I_UI_SCALER_SCALE_MIN;
		max_scale = SUN8I_UI_SCALER_SCALE_MAX;
	पूर्ण

	वापस drm_atomic_helper_check_plane_state(new_plane_state,
						   crtc_state,
						   min_scale, max_scale,
						   true, true);
पूर्ण

अटल व्योम sun8i_ui_layer_atomic_disable(काष्ठा drm_plane *plane,
					  काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *old_state = drm_atomic_get_old_plane_state(state,
									   plane);
	काष्ठा sun8i_ui_layer *layer = plane_to_sun8i_ui_layer(plane);
	अचिन्हित पूर्णांक old_zpos = old_state->normalized_zpos;
	काष्ठा sun8i_mixer *mixer = layer->mixer;

	sun8i_ui_layer_enable(mixer, layer->channel, layer->overlay, false, 0,
			      old_zpos);
पूर्ण

अटल व्योम sun8i_ui_layer_atomic_update(काष्ठा drm_plane *plane,
					 काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *old_state = drm_atomic_get_old_plane_state(state,
									   plane);
	काष्ठा drm_plane_state *new_state = drm_atomic_get_new_plane_state(state,
									   plane);
	काष्ठा sun8i_ui_layer *layer = plane_to_sun8i_ui_layer(plane);
	अचिन्हित पूर्णांक zpos = new_state->normalized_zpos;
	अचिन्हित पूर्णांक old_zpos = old_state->normalized_zpos;
	काष्ठा sun8i_mixer *mixer = layer->mixer;

	अगर (!new_state->visible) अणु
		sun8i_ui_layer_enable(mixer, layer->channel,
				      layer->overlay, false, 0, old_zpos);
		वापस;
	पूर्ण

	sun8i_ui_layer_update_coord(mixer, layer->channel,
				    layer->overlay, plane, zpos);
	sun8i_ui_layer_update_alpha(mixer, layer->channel,
				    layer->overlay, plane);
	sun8i_ui_layer_update_क्रमmats(mixer, layer->channel,
				      layer->overlay, plane);
	sun8i_ui_layer_update_buffer(mixer, layer->channel,
				     layer->overlay, plane);
	sun8i_ui_layer_enable(mixer, layer->channel, layer->overlay,
			      true, zpos, old_zpos);
पूर्ण

अटल स्थिर काष्ठा drm_plane_helper_funcs sun8i_ui_layer_helper_funcs = अणु
	.prepare_fb	= drm_gem_plane_helper_prepare_fb,
	.atomic_check	= sun8i_ui_layer_atomic_check,
	.atomic_disable	= sun8i_ui_layer_atomic_disable,
	.atomic_update	= sun8i_ui_layer_atomic_update,
पूर्ण;

अटल स्थिर काष्ठा drm_plane_funcs sun8i_ui_layer_funcs = अणु
	.atomic_destroy_state	= drm_atomic_helper_plane_destroy_state,
	.atomic_duplicate_state	= drm_atomic_helper_plane_duplicate_state,
	.destroy		= drm_plane_cleanup,
	.disable_plane		= drm_atomic_helper_disable_plane,
	.reset			= drm_atomic_helper_plane_reset,
	.update_plane		= drm_atomic_helper_update_plane,
पूर्ण;

अटल स्थिर u32 sun8i_ui_layer_क्रमmats[] = अणु
	DRM_FORMAT_ABGR1555,
	DRM_FORMAT_ABGR4444,
	DRM_FORMAT_ABGR8888,
	DRM_FORMAT_ARGB1555,
	DRM_FORMAT_ARGB4444,
	DRM_FORMAT_ARGB8888,
	DRM_FORMAT_BGR565,
	DRM_FORMAT_BGR888,
	DRM_FORMAT_BGRA5551,
	DRM_FORMAT_BGRA4444,
	DRM_FORMAT_BGRA8888,
	DRM_FORMAT_BGRX8888,
	DRM_FORMAT_RGB565,
	DRM_FORMAT_RGB888,
	DRM_FORMAT_RGBA4444,
	DRM_FORMAT_RGBA5551,
	DRM_FORMAT_RGBA8888,
	DRM_FORMAT_RGBX8888,
	DRM_FORMAT_XBGR8888,
	DRM_FORMAT_XRGB8888,
पूर्ण;

काष्ठा sun8i_ui_layer *sun8i_ui_layer_init_one(काष्ठा drm_device *drm,
					       काष्ठा sun8i_mixer *mixer,
					       पूर्णांक index)
अणु
	क्रमागत drm_plane_type type = DRM_PLANE_TYPE_OVERLAY;
	पूर्णांक channel = mixer->cfg->vi_num + index;
	काष्ठा sun8i_ui_layer *layer;
	अचिन्हित पूर्णांक plane_cnt;
	पूर्णांक ret;

	layer = devm_kzalloc(drm->dev, माप(*layer), GFP_KERNEL);
	अगर (!layer)
		वापस ERR_PTR(-ENOMEM);

	अगर (index == 0)
		type = DRM_PLANE_TYPE_PRIMARY;

	/* possible crtcs are set later */
	ret = drm_universal_plane_init(drm, &layer->plane, 0,
				       &sun8i_ui_layer_funcs,
				       sun8i_ui_layer_क्रमmats,
				       ARRAY_SIZE(sun8i_ui_layer_क्रमmats),
				       शून्य, type, शून्य);
	अगर (ret) अणु
		dev_err(drm->dev, "Couldn't initialize layer\n");
		वापस ERR_PTR(ret);
	पूर्ण

	plane_cnt = mixer->cfg->ui_num + mixer->cfg->vi_num;

	ret = drm_plane_create_alpha_property(&layer->plane);
	अगर (ret) अणु
		dev_err(drm->dev, "Couldn't add alpha property\n");
		वापस ERR_PTR(ret);
	पूर्ण

	ret = drm_plane_create_zpos_property(&layer->plane, channel,
					     0, plane_cnt - 1);
	अगर (ret) अणु
		dev_err(drm->dev, "Couldn't add zpos property\n");
		वापस ERR_PTR(ret);
	पूर्ण

	drm_plane_helper_add(&layer->plane, &sun8i_ui_layer_helper_funcs);
	layer->mixer = mixer;
	layer->channel = channel;
	layer->overlay = 0;

	वापस layer;
पूर्ण
