<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) Jernej Skrabec <jernej.skrabec@siol.net>
 */

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_fb_cma_helper.h>
#समावेश <drm/drm_gem_atomic_helper.h>
#समावेश <drm/drm_gem_cma_helper.h>
#समावेश <drm/drm_plane_helper.h>
#समावेश <drm/drm_probe_helper.h>

#समावेश "sun8i_csc.h"
#समावेश "sun8i_mixer.h"
#समावेश "sun8i_vi_layer.h"
#समावेश "sun8i_vi_scaler.h"

अटल व्योम sun8i_vi_layer_enable(काष्ठा sun8i_mixer *mixer, पूर्णांक channel,
				  पूर्णांक overlay, bool enable, अचिन्हित पूर्णांक zpos,
				  अचिन्हित पूर्णांक old_zpos)
अणु
	u32 val, bld_base, ch_base;

	bld_base = sun8i_blender_base(mixer);
	ch_base = sun8i_channel_base(mixer, channel);

	DRM_DEBUG_DRIVER("%sabling VI channel %d overlay %d\n",
			 enable ? "En" : "Dis", channel, overlay);

	अगर (enable)
		val = SUN8I_MIXER_CHAN_VI_LAYER_ATTR_EN;
	अन्यथा
		val = 0;

	regmap_update_bits(mixer->engine.regs,
			   SUN8I_MIXER_CHAN_VI_LAYER_ATTR(ch_base, overlay),
			   SUN8I_MIXER_CHAN_VI_LAYER_ATTR_EN, val);

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

अटल व्योम sun8i_vi_layer_update_alpha(काष्ठा sun8i_mixer *mixer, पूर्णांक channel,
					पूर्णांक overlay, काष्ठा drm_plane *plane)
अणु
	u32 mask, val, ch_base;

	ch_base = sun8i_channel_base(mixer, channel);

	अगर (mixer->cfg->is_de3) अणु
		mask = SUN50I_MIXER_CHAN_VI_LAYER_ATTR_ALPHA_MASK |
		       SUN50I_MIXER_CHAN_VI_LAYER_ATTR_ALPHA_MODE_MASK;
		val = SUN50I_MIXER_CHAN_VI_LAYER_ATTR_ALPHA
			(plane->state->alpha >> 8);

		val |= (plane->state->alpha == DRM_BLEND_ALPHA_OPAQUE) ?
			SUN50I_MIXER_CHAN_VI_LAYER_ATTR_ALPHA_MODE_PIXEL :
			SUN50I_MIXER_CHAN_VI_LAYER_ATTR_ALPHA_MODE_COMBINED;

		regmap_update_bits(mixer->engine.regs,
				   SUN8I_MIXER_CHAN_VI_LAYER_ATTR(ch_base,
								  overlay),
				   mask, val);
	पूर्ण अन्यथा अगर (mixer->cfg->vi_num == 1) अणु
		regmap_update_bits(mixer->engine.regs,
				   SUN8I_MIXER_FCC_GLOBAL_ALPHA_REG,
				   SUN8I_MIXER_FCC_GLOBAL_ALPHA_MASK,
				   SUN8I_MIXER_FCC_GLOBAL_ALPHA
					(plane->state->alpha >> 8));
	पूर्ण
पूर्ण

अटल पूर्णांक sun8i_vi_layer_update_coord(काष्ठा sun8i_mixer *mixer, पूर्णांक channel,
				       पूर्णांक overlay, काष्ठा drm_plane *plane,
				       अचिन्हित पूर्णांक zpos)
अणु
	काष्ठा drm_plane_state *state = plane->state;
	स्थिर काष्ठा drm_क्रमmat_info *क्रमmat = state->fb->क्रमmat;
	u32 src_w, src_h, dst_w, dst_h;
	u32 bld_base, ch_base;
	u32 outsize, insize;
	u32 hphase, vphase;
	u32 hn = 0, hm = 0;
	u32 vn = 0, vm = 0;
	bool subsampled;

	DRM_DEBUG_DRIVER("Updating VI channel %d overlay %d\n",
			 channel, overlay);

	bld_base = sun8i_blender_base(mixer);
	ch_base = sun8i_channel_base(mixer, channel);

	src_w = drm_rect_width(&state->src) >> 16;
	src_h = drm_rect_height(&state->src) >> 16;
	dst_w = drm_rect_width(&state->dst);
	dst_h = drm_rect_height(&state->dst);

	hphase = state->src.x1 & 0xffff;
	vphase = state->src.y1 & 0xffff;

	/* make coordinates भागidable by subsampling factor */
	अगर (क्रमmat->hsub > 1) अणु
		पूर्णांक mask, reमुख्यder;

		mask = क्रमmat->hsub - 1;
		reमुख्यder = (state->src.x1 >> 16) & mask;
		src_w = (src_w + reमुख्यder) & ~mask;
		hphase += reमुख्यder << 16;
	पूर्ण

	अगर (क्रमmat->vsub > 1) अणु
		पूर्णांक mask, reमुख्यder;

		mask = क्रमmat->vsub - 1;
		reमुख्यder = (state->src.y1 >> 16) & mask;
		src_h = (src_h + reमुख्यder) & ~mask;
		vphase += reमुख्यder << 16;
	पूर्ण

	insize = SUN8I_MIXER_SIZE(src_w, src_h);
	outsize = SUN8I_MIXER_SIZE(dst_w, dst_h);

	/* Set height and width */
	DRM_DEBUG_DRIVER("Layer source offset X: %d Y: %d\n",
			 (state->src.x1 >> 16) & ~(क्रमmat->hsub - 1),
			 (state->src.y1 >> 16) & ~(क्रमmat->vsub - 1));
	DRM_DEBUG_DRIVER("Layer source size W: %d H: %d\n", src_w, src_h);
	regmap_ग_लिखो(mixer->engine.regs,
		     SUN8I_MIXER_CHAN_VI_LAYER_SIZE(ch_base, overlay),
		     insize);
	regmap_ग_लिखो(mixer->engine.regs,
		     SUN8I_MIXER_CHAN_VI_OVL_SIZE(ch_base),
		     insize);

	/*
	 * Scaler must be enabled क्रम subsampled क्रमmats, so it scales
	 * chroma to same size as luma.
	 */
	subsampled = क्रमmat->hsub > 1 || क्रमmat->vsub > 1;

	अगर (insize != outsize || subsampled || hphase || vphase) अणु
		अचिन्हित पूर्णांक scanline, required;
		काष्ठा drm_display_mode *mode;
		u32 hscale, vscale, fps;
		u64 ability;

		DRM_DEBUG_DRIVER("HW scaling is enabled\n");

		mode = &plane->state->crtc->state->mode;
		fps = (mode->घड़ी * 1000) / (mode->vtotal * mode->htotal);
		ability = clk_get_rate(mixer->mod_clk);
		/* BSP algorithm assumes 80% efficiency of VI scaler unit */
		ability *= 80;
		करो_भाग(ability, mode->vdisplay * fps * max(src_w, dst_w));

		required = src_h * 100 / dst_h;

		अगर (ability < required) अणु
			DRM_DEBUG_DRIVER("Using vertical coarse scaling\n");
			vm = src_h;
			vn = (u32)ability * dst_h / 100;
			src_h = vn;
		पूर्ण

		/* it seems that every RGB scaler has buffer क्रम 2048 pixels */
		scanline = subsampled ? mixer->cfg->scanline_yuv : 2048;

		अगर (src_w > scanline) अणु
			DRM_DEBUG_DRIVER("Using horizontal coarse scaling\n");
			hm = src_w;
			hn = scanline;
			src_w = hn;
		पूर्ण

		hscale = (src_w << 16) / dst_w;
		vscale = (src_h << 16) / dst_h;

		sun8i_vi_scaler_setup(mixer, channel, src_w, src_h, dst_w,
				      dst_h, hscale, vscale, hphase, vphase,
				      क्रमmat);
		sun8i_vi_scaler_enable(mixer, channel, true);
	पूर्ण अन्यथा अणु
		DRM_DEBUG_DRIVER("HW scaling is not needed\n");
		sun8i_vi_scaler_enable(mixer, channel, false);
	पूर्ण

	regmap_ग_लिखो(mixer->engine.regs,
		     SUN8I_MIXER_CHAN_VI_HDS_Y(ch_base),
		     SUN8I_MIXER_CHAN_VI_DS_N(hn) |
		     SUN8I_MIXER_CHAN_VI_DS_M(hm));
	regmap_ग_लिखो(mixer->engine.regs,
		     SUN8I_MIXER_CHAN_VI_HDS_UV(ch_base),
		     SUN8I_MIXER_CHAN_VI_DS_N(hn) |
		     SUN8I_MIXER_CHAN_VI_DS_M(hm));
	regmap_ग_लिखो(mixer->engine.regs,
		     SUN8I_MIXER_CHAN_VI_VDS_Y(ch_base),
		     SUN8I_MIXER_CHAN_VI_DS_N(vn) |
		     SUN8I_MIXER_CHAN_VI_DS_M(vm));
	regmap_ग_लिखो(mixer->engine.regs,
		     SUN8I_MIXER_CHAN_VI_VDS_UV(ch_base),
		     SUN8I_MIXER_CHAN_VI_DS_N(vn) |
		     SUN8I_MIXER_CHAN_VI_DS_M(vm));

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

अटल u32 sun8i_vi_layer_get_csc_mode(स्थिर काष्ठा drm_क्रमmat_info *क्रमmat)
अणु
	अगर (!क्रमmat->is_yuv)
		वापस SUN8I_CSC_MODE_OFF;

	चयन (क्रमmat->क्रमmat) अणु
	हाल DRM_FORMAT_YVU411:
	हाल DRM_FORMAT_YVU420:
	हाल DRM_FORMAT_YVU422:
	हाल DRM_FORMAT_YVU444:
		वापस SUN8I_CSC_MODE_YVU2RGB;
	शेष:
		वापस SUN8I_CSC_MODE_YUV2RGB;
	पूर्ण
पूर्ण

अटल पूर्णांक sun8i_vi_layer_update_क्रमmats(काष्ठा sun8i_mixer *mixer, पूर्णांक channel,
					 पूर्णांक overlay, काष्ठा drm_plane *plane)
अणु
	काष्ठा drm_plane_state *state = plane->state;
	u32 val, ch_base, csc_mode, hw_fmt;
	स्थिर काष्ठा drm_क्रमmat_info *fmt;
	पूर्णांक ret;

	ch_base = sun8i_channel_base(mixer, channel);

	fmt = state->fb->क्रमmat;
	ret = sun8i_mixer_drm_क्रमmat_to_hw(fmt->क्रमmat, &hw_fmt);
	अगर (ret) अणु
		DRM_DEBUG_DRIVER("Invalid format\n");
		वापस ret;
	पूर्ण

	val = hw_fmt << SUN8I_MIXER_CHAN_VI_LAYER_ATTR_FBFMT_OFFSET;
	regmap_update_bits(mixer->engine.regs,
			   SUN8I_MIXER_CHAN_VI_LAYER_ATTR(ch_base, overlay),
			   SUN8I_MIXER_CHAN_VI_LAYER_ATTR_FBFMT_MASK, val);

	csc_mode = sun8i_vi_layer_get_csc_mode(fmt);
	अगर (csc_mode != SUN8I_CSC_MODE_OFF) अणु
		sun8i_csc_set_ccsc_coefficients(mixer, channel, csc_mode,
						state->color_encoding,
						state->color_range);
		sun8i_csc_enable_ccsc(mixer, channel, true);
	पूर्ण अन्यथा अणु
		sun8i_csc_enable_ccsc(mixer, channel, false);
	पूर्ण

	अगर (!fmt->is_yuv)
		val = SUN8I_MIXER_CHAN_VI_LAYER_ATTR_RGB_MODE;
	अन्यथा
		val = 0;

	regmap_update_bits(mixer->engine.regs,
			   SUN8I_MIXER_CHAN_VI_LAYER_ATTR(ch_base, overlay),
			   SUN8I_MIXER_CHAN_VI_LAYER_ATTR_RGB_MODE, val);

	वापस 0;
पूर्ण

अटल पूर्णांक sun8i_vi_layer_update_buffer(काष्ठा sun8i_mixer *mixer, पूर्णांक channel,
					पूर्णांक overlay, काष्ठा drm_plane *plane)
अणु
	काष्ठा drm_plane_state *state = plane->state;
	काष्ठा drm_framebuffer *fb = state->fb;
	स्थिर काष्ठा drm_क्रमmat_info *क्रमmat = fb->क्रमmat;
	काष्ठा drm_gem_cma_object *gem;
	u32 dx, dy, src_x, src_y;
	dma_addr_t paddr;
	u32 ch_base;
	पूर्णांक i;

	ch_base = sun8i_channel_base(mixer, channel);

	/* Adjust x and y to be भागidable by subsampling factor */
	src_x = (state->src.x1 >> 16) & ~(क्रमmat->hsub - 1);
	src_y = (state->src.y1 >> 16) & ~(क्रमmat->vsub - 1);

	क्रम (i = 0; i < क्रमmat->num_planes; i++) अणु
		/* Get the physical address of the buffer in memory */
		gem = drm_fb_cma_get_gem_obj(fb, i);

		DRM_DEBUG_DRIVER("Using GEM @ %pad\n", &gem->paddr);

		/* Compute the start of the displayed memory */
		paddr = gem->paddr + fb->offsets[i];

		dx = src_x;
		dy = src_y;

		अगर (i > 0) अणु
			dx /= क्रमmat->hsub;
			dy /= क्रमmat->vsub;
		पूर्ण

		/* Fixup framebuffer address क्रम src coordinates */
		paddr += dx * क्रमmat->cpp[i];
		paddr += dy * fb->pitches[i];

		/* Set the line width */
		DRM_DEBUG_DRIVER("Layer %d. line width: %d bytes\n",
				 i + 1, fb->pitches[i]);
		regmap_ग_लिखो(mixer->engine.regs,
			     SUN8I_MIXER_CHAN_VI_LAYER_PITCH(ch_base,
							     overlay, i),
			     fb->pitches[i]);

		DRM_DEBUG_DRIVER("Setting %d. buffer address to %pad\n",
				 i + 1, &paddr);

		regmap_ग_लिखो(mixer->engine.regs,
			     SUN8I_MIXER_CHAN_VI_LAYER_TOP_LADDR(ch_base,
								 overlay, i),
			     lower_32_bits(paddr));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sun8i_vi_layer_atomic_check(काष्ठा drm_plane *plane,
				       काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *new_plane_state = drm_atomic_get_new_plane_state(state,
										 plane);
	काष्ठा sun8i_vi_layer *layer = plane_to_sun8i_vi_layer(plane);
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
		min_scale = SUN8I_VI_SCALER_SCALE_MIN;
		max_scale = SUN8I_VI_SCALER_SCALE_MAX;
	पूर्ण

	वापस drm_atomic_helper_check_plane_state(new_plane_state,
						   crtc_state,
						   min_scale, max_scale,
						   true, true);
पूर्ण

अटल व्योम sun8i_vi_layer_atomic_disable(काष्ठा drm_plane *plane,
					  काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *old_state = drm_atomic_get_old_plane_state(state,
									   plane);
	काष्ठा sun8i_vi_layer *layer = plane_to_sun8i_vi_layer(plane);
	अचिन्हित पूर्णांक old_zpos = old_state->normalized_zpos;
	काष्ठा sun8i_mixer *mixer = layer->mixer;

	sun8i_vi_layer_enable(mixer, layer->channel, layer->overlay, false, 0,
			      old_zpos);
पूर्ण

अटल व्योम sun8i_vi_layer_atomic_update(काष्ठा drm_plane *plane,
					 काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *old_state = drm_atomic_get_old_plane_state(state,
									   plane);
	काष्ठा drm_plane_state *new_state = drm_atomic_get_new_plane_state(state,
									   plane);
	काष्ठा sun8i_vi_layer *layer = plane_to_sun8i_vi_layer(plane);
	अचिन्हित पूर्णांक zpos = new_state->normalized_zpos;
	अचिन्हित पूर्णांक old_zpos = old_state->normalized_zpos;
	काष्ठा sun8i_mixer *mixer = layer->mixer;

	अगर (!new_state->visible) अणु
		sun8i_vi_layer_enable(mixer, layer->channel,
				      layer->overlay, false, 0, old_zpos);
		वापस;
	पूर्ण

	sun8i_vi_layer_update_coord(mixer, layer->channel,
				    layer->overlay, plane, zpos);
	sun8i_vi_layer_update_alpha(mixer, layer->channel,
				    layer->overlay, plane);
	sun8i_vi_layer_update_क्रमmats(mixer, layer->channel,
				      layer->overlay, plane);
	sun8i_vi_layer_update_buffer(mixer, layer->channel,
				     layer->overlay, plane);
	sun8i_vi_layer_enable(mixer, layer->channel, layer->overlay,
			      true, zpos, old_zpos);
पूर्ण

अटल स्थिर काष्ठा drm_plane_helper_funcs sun8i_vi_layer_helper_funcs = अणु
	.prepare_fb	= drm_gem_plane_helper_prepare_fb,
	.atomic_check	= sun8i_vi_layer_atomic_check,
	.atomic_disable	= sun8i_vi_layer_atomic_disable,
	.atomic_update	= sun8i_vi_layer_atomic_update,
पूर्ण;

अटल स्थिर काष्ठा drm_plane_funcs sun8i_vi_layer_funcs = अणु
	.atomic_destroy_state	= drm_atomic_helper_plane_destroy_state,
	.atomic_duplicate_state	= drm_atomic_helper_plane_duplicate_state,
	.destroy		= drm_plane_cleanup,
	.disable_plane		= drm_atomic_helper_disable_plane,
	.reset			= drm_atomic_helper_plane_reset,
	.update_plane		= drm_atomic_helper_update_plane,
पूर्ण;

/*
 * While DE2 VI layer supports same RGB क्रमmats as UI layer, alpha
 * channel is ignored. This काष्ठाure lists all unique variants
 * where alpha channel is replaced with "don't care" (X) channel.
 */
अटल स्थिर u32 sun8i_vi_layer_क्रमmats[] = अणु
	DRM_FORMAT_BGR565,
	DRM_FORMAT_BGR888,
	DRM_FORMAT_BGRX4444,
	DRM_FORMAT_BGRX5551,
	DRM_FORMAT_BGRX8888,
	DRM_FORMAT_RGB565,
	DRM_FORMAT_RGB888,
	DRM_FORMAT_RGBX4444,
	DRM_FORMAT_RGBX5551,
	DRM_FORMAT_RGBX8888,
	DRM_FORMAT_XBGR1555,
	DRM_FORMAT_XBGR4444,
	DRM_FORMAT_XBGR8888,
	DRM_FORMAT_XRGB1555,
	DRM_FORMAT_XRGB4444,
	DRM_FORMAT_XRGB8888,

	DRM_FORMAT_NV16,
	DRM_FORMAT_NV12,
	DRM_FORMAT_NV21,
	DRM_FORMAT_NV61,
	DRM_FORMAT_UYVY,
	DRM_FORMAT_VYUY,
	DRM_FORMAT_YUYV,
	DRM_FORMAT_YVYU,
	DRM_FORMAT_YUV411,
	DRM_FORMAT_YUV420,
	DRM_FORMAT_YUV422,
	DRM_FORMAT_YVU411,
	DRM_FORMAT_YVU420,
	DRM_FORMAT_YVU422,
पूर्ण;

अटल स्थिर u32 sun8i_vi_layer_de3_क्रमmats[] = अणु
	DRM_FORMAT_ABGR1555,
	DRM_FORMAT_ABGR2101010,
	DRM_FORMAT_ABGR4444,
	DRM_FORMAT_ABGR8888,
	DRM_FORMAT_ARGB1555,
	DRM_FORMAT_ARGB2101010,
	DRM_FORMAT_ARGB4444,
	DRM_FORMAT_ARGB8888,
	DRM_FORMAT_BGR565,
	DRM_FORMAT_BGR888,
	DRM_FORMAT_BGRA1010102,
	DRM_FORMAT_BGRA5551,
	DRM_FORMAT_BGRA4444,
	DRM_FORMAT_BGRA8888,
	DRM_FORMAT_BGRX8888,
	DRM_FORMAT_RGB565,
	DRM_FORMAT_RGB888,
	DRM_FORMAT_RGBA1010102,
	DRM_FORMAT_RGBA4444,
	DRM_FORMAT_RGBA5551,
	DRM_FORMAT_RGBA8888,
	DRM_FORMAT_RGBX8888,
	DRM_FORMAT_XBGR8888,
	DRM_FORMAT_XRGB8888,

	DRM_FORMAT_NV16,
	DRM_FORMAT_NV12,
	DRM_FORMAT_NV21,
	DRM_FORMAT_NV61,
	DRM_FORMAT_P010,
	DRM_FORMAT_P210,
	DRM_FORMAT_UYVY,
	DRM_FORMAT_VYUY,
	DRM_FORMAT_YUYV,
	DRM_FORMAT_YVYU,
	DRM_FORMAT_YUV411,
	DRM_FORMAT_YUV420,
	DRM_FORMAT_YUV422,
	DRM_FORMAT_YVU411,
	DRM_FORMAT_YVU420,
	DRM_FORMAT_YVU422,
पूर्ण;

काष्ठा sun8i_vi_layer *sun8i_vi_layer_init_one(काष्ठा drm_device *drm,
					       काष्ठा sun8i_mixer *mixer,
					       पूर्णांक index)
अणु
	u32 supported_encodings, supported_ranges;
	अचिन्हित पूर्णांक plane_cnt, क्रमmat_count;
	काष्ठा sun8i_vi_layer *layer;
	स्थिर u32 *क्रमmats;
	पूर्णांक ret;

	layer = devm_kzalloc(drm->dev, माप(*layer), GFP_KERNEL);
	अगर (!layer)
		वापस ERR_PTR(-ENOMEM);

	अगर (mixer->cfg->is_de3) अणु
		क्रमmats = sun8i_vi_layer_de3_क्रमmats;
		क्रमmat_count = ARRAY_SIZE(sun8i_vi_layer_de3_क्रमmats);
	पूर्ण अन्यथा अणु
		क्रमmats = sun8i_vi_layer_क्रमmats;
		क्रमmat_count = ARRAY_SIZE(sun8i_vi_layer_क्रमmats);
	पूर्ण

	/* possible crtcs are set later */
	ret = drm_universal_plane_init(drm, &layer->plane, 0,
				       &sun8i_vi_layer_funcs,
				       क्रमmats, क्रमmat_count,
				       शून्य, DRM_PLANE_TYPE_OVERLAY, शून्य);
	अगर (ret) अणु
		dev_err(drm->dev, "Couldn't initialize layer\n");
		वापस ERR_PTR(ret);
	पूर्ण

	plane_cnt = mixer->cfg->ui_num + mixer->cfg->vi_num;

	अगर (mixer->cfg->vi_num == 1 || mixer->cfg->is_de3) अणु
		ret = drm_plane_create_alpha_property(&layer->plane);
		अगर (ret) अणु
			dev_err(drm->dev, "Couldn't add alpha property\n");
			वापस ERR_PTR(ret);
		पूर्ण
	पूर्ण

	ret = drm_plane_create_zpos_property(&layer->plane, index,
					     0, plane_cnt - 1);
	अगर (ret) अणु
		dev_err(drm->dev, "Couldn't add zpos property\n");
		वापस ERR_PTR(ret);
	पूर्ण

	supported_encodings = BIT(DRM_COLOR_YCBCR_BT601) |
			      BIT(DRM_COLOR_YCBCR_BT709);
	अगर (mixer->cfg->is_de3)
		supported_encodings |= BIT(DRM_COLOR_YCBCR_BT2020);

	supported_ranges = BIT(DRM_COLOR_YCBCR_LIMITED_RANGE) |
			   BIT(DRM_COLOR_YCBCR_FULL_RANGE);

	ret = drm_plane_create_color_properties(&layer->plane,
						supported_encodings,
						supported_ranges,
						DRM_COLOR_YCBCR_BT709,
						DRM_COLOR_YCBCR_LIMITED_RANGE);
	अगर (ret) अणु
		dev_err(drm->dev, "Couldn't add encoding and range properties!\n");
		वापस ERR_PTR(ret);
	पूर्ण

	drm_plane_helper_add(&layer->plane, &sun8i_vi_layer_helper_funcs);
	layer->mixer = mixer;
	layer->channel = index;
	layer->overlay = 0;

	वापस layer;
पूर्ण
