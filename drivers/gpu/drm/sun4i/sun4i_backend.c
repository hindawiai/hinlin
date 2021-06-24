<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2015 Free Electrons
 * Copyright (C) 2015 NextThing Co
 *
 * Maxime Ripard <maxime.ripard@मुक्त-electrons.com>
 */

#समावेश <linux/component.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_fb_cma_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_gem_cma_helper.h>
#समावेश <drm/drm_plane_helper.h>
#समावेश <drm/drm_probe_helper.h>

#समावेश "sun4i_backend.h"
#समावेश "sun4i_drv.h"
#समावेश "sun4i_frontend.h"
#समावेश "sun4i_layer.h"
#समावेश "sunxi_engine.h"

काष्ठा sun4i_backend_quirks अणु
	/* backend <-> TCON muxing selection करोne in backend */
	bool needs_output_muxing;

	/* alpha at the lowest z position is not always supported */
	bool supports_lowest_plane_alpha;
पूर्ण;

अटल स्थिर u32 sunxi_rgb2yuv_coef[12] = अणु
	0x00000107, 0x00000204, 0x00000064, 0x00000108,
	0x00003f69, 0x00003ed6, 0x000001c1, 0x00000808,
	0x000001c1, 0x00003e88, 0x00003fb8, 0x00000808
पूर्ण;

अटल व्योम sun4i_backend_apply_color_correction(काष्ठा sunxi_engine *engine)
अणु
	पूर्णांक i;

	DRM_DEBUG_DRIVER("Applying RGB to YUV color correction\n");

	/* Set color correction */
	regmap_ग_लिखो(engine->regs, SUN4I_BACKEND_OCCTL_REG,
		     SUN4I_BACKEND_OCCTL_ENABLE);

	क्रम (i = 0; i < 12; i++)
		regmap_ग_लिखो(engine->regs, SUN4I_BACKEND_OCRCOEF_REG(i),
			     sunxi_rgb2yuv_coef[i]);
पूर्ण

अटल व्योम sun4i_backend_disable_color_correction(काष्ठा sunxi_engine *engine)
अणु
	DRM_DEBUG_DRIVER("Disabling color correction\n");

	/* Disable color correction */
	regmap_update_bits(engine->regs, SUN4I_BACKEND_OCCTL_REG,
			   SUN4I_BACKEND_OCCTL_ENABLE, 0);
पूर्ण

अटल व्योम sun4i_backend_commit(काष्ठा sunxi_engine *engine)
अणु
	DRM_DEBUG_DRIVER("Committing changes\n");

	regmap_ग_लिखो(engine->regs, SUN4I_BACKEND_REGBUFFCTL_REG,
		     SUN4I_BACKEND_REGBUFFCTL_AUTOLOAD_DIS |
		     SUN4I_BACKEND_REGBUFFCTL_LOADCTL);
पूर्ण

व्योम sun4i_backend_layer_enable(काष्ठा sun4i_backend *backend,
				पूर्णांक layer, bool enable)
अणु
	u32 val;

	DRM_DEBUG_DRIVER("%sabling layer %d\n", enable ? "En" : "Dis",
			 layer);

	अगर (enable)
		val = SUN4I_BACKEND_MODCTL_LAY_EN(layer);
	अन्यथा
		val = 0;

	regmap_update_bits(backend->engine.regs, SUN4I_BACKEND_MODCTL_REG,
			   SUN4I_BACKEND_MODCTL_LAY_EN(layer), val);
पूर्ण

अटल पूर्णांक sun4i_backend_drm_क्रमmat_to_layer(u32 क्रमmat, u32 *mode)
अणु
	चयन (क्रमmat) अणु
	हाल DRM_FORMAT_ARGB8888:
		*mode = SUN4I_BACKEND_LAY_FBFMT_ARGB8888;
		अवरोध;

	हाल DRM_FORMAT_ARGB4444:
		*mode = SUN4I_BACKEND_LAY_FBFMT_ARGB4444;
		अवरोध;

	हाल DRM_FORMAT_ARGB1555:
		*mode = SUN4I_BACKEND_LAY_FBFMT_ARGB1555;
		अवरोध;

	हाल DRM_FORMAT_RGBA5551:
		*mode = SUN4I_BACKEND_LAY_FBFMT_RGBA5551;
		अवरोध;

	हाल DRM_FORMAT_RGBA4444:
		*mode = SUN4I_BACKEND_LAY_FBFMT_RGBA4444;
		अवरोध;

	हाल DRM_FORMAT_XRGB8888:
		*mode = SUN4I_BACKEND_LAY_FBFMT_XRGB8888;
		अवरोध;

	हाल DRM_FORMAT_RGB888:
		*mode = SUN4I_BACKEND_LAY_FBFMT_RGB888;
		अवरोध;

	हाल DRM_FORMAT_RGB565:
		*mode = SUN4I_BACKEND_LAY_FBFMT_RGB565;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर uपूर्णांक32_t sun4i_backend_क्रमmats[] = अणु
	DRM_FORMAT_ARGB1555,
	DRM_FORMAT_ARGB4444,
	DRM_FORMAT_ARGB8888,
	DRM_FORMAT_RGB565,
	DRM_FORMAT_RGB888,
	DRM_FORMAT_RGBA4444,
	DRM_FORMAT_RGBA5551,
	DRM_FORMAT_UYVY,
	DRM_FORMAT_VYUY,
	DRM_FORMAT_XRGB8888,
	DRM_FORMAT_YUYV,
	DRM_FORMAT_YVYU,
पूर्ण;

bool sun4i_backend_क्रमmat_is_supported(uपूर्णांक32_t fmt, uपूर्णांक64_t modअगरier)
अणु
	अचिन्हित पूर्णांक i;

	अगर (modअगरier != DRM_FORMAT_MOD_LINEAR)
		वापस false;

	क्रम (i = 0; i < ARRAY_SIZE(sun4i_backend_क्रमmats); i++)
		अगर (sun4i_backend_क्रमmats[i] == fmt)
			वापस true;

	वापस false;
पूर्ण

पूर्णांक sun4i_backend_update_layer_coord(काष्ठा sun4i_backend *backend,
				     पूर्णांक layer, काष्ठा drm_plane *plane)
अणु
	काष्ठा drm_plane_state *state = plane->state;

	DRM_DEBUG_DRIVER("Updating layer %d\n", layer);

	अगर (plane->type == DRM_PLANE_TYPE_PRIMARY) अणु
		DRM_DEBUG_DRIVER("Primary layer, updating global size W: %u H: %u\n",
				 state->crtc_w, state->crtc_h);
		regmap_ग_लिखो(backend->engine.regs, SUN4I_BACKEND_DISSIZE_REG,
			     SUN4I_BACKEND_DISSIZE(state->crtc_w,
						   state->crtc_h));
	पूर्ण

	/* Set height and width */
	DRM_DEBUG_DRIVER("Layer size W: %u H: %u\n",
			 state->crtc_w, state->crtc_h);
	regmap_ग_लिखो(backend->engine.regs, SUN4I_BACKEND_LAYSIZE_REG(layer),
		     SUN4I_BACKEND_LAYSIZE(state->crtc_w,
					   state->crtc_h));

	/* Set base coordinates */
	DRM_DEBUG_DRIVER("Layer coordinates X: %d Y: %d\n",
			 state->crtc_x, state->crtc_y);
	regmap_ग_लिखो(backend->engine.regs, SUN4I_BACKEND_LAYCOOR_REG(layer),
		     SUN4I_BACKEND_LAYCOOR(state->crtc_x,
					   state->crtc_y));

	वापस 0;
पूर्ण

अटल पूर्णांक sun4i_backend_update_yuv_क्रमmat(काष्ठा sun4i_backend *backend,
					   पूर्णांक layer, काष्ठा drm_plane *plane)
अणु
	काष्ठा drm_plane_state *state = plane->state;
	काष्ठा drm_framebuffer *fb = state->fb;
	स्थिर काष्ठा drm_क्रमmat_info *क्रमmat = fb->क्रमmat;
	स्थिर uपूर्णांक32_t fmt = क्रमmat->क्रमmat;
	u32 val = SUN4I_BACKEND_IYUVCTL_EN;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(sunxi_bt601_yuv2rgb_coef); i++)
		regmap_ग_लिखो(backend->engine.regs,
			     SUN4I_BACKEND_YGCOEF_REG(i),
			     sunxi_bt601_yuv2rgb_coef[i]);

	/*
	 * We should करो that only क्रम a single plane, but the
	 * framebuffer's atomic_check has our back on this.
	 */
	regmap_update_bits(backend->engine.regs, SUN4I_BACKEND_ATTCTL_REG0(layer),
			   SUN4I_BACKEND_ATTCTL_REG0_LAY_YUVEN,
			   SUN4I_BACKEND_ATTCTL_REG0_LAY_YUVEN);

	/* TODO: Add support क्रम the multi-planar YUV क्रमmats */
	अगर (drm_क्रमmat_info_is_yuv_packed(क्रमmat) &&
	    drm_क्रमmat_info_is_yuv_sampling_422(क्रमmat))
		val |= SUN4I_BACKEND_IYUVCTL_FBFMT_PACKED_YUV422;
	अन्यथा
		DRM_DEBUG_DRIVER("Unsupported YUV format (0x%x)\n", fmt);

	/*
	 * Allwinner seems to list the pixel sequence from right to left, जबतक
	 * DRM lists it from left to right.
	 */
	चयन (fmt) अणु
	हाल DRM_FORMAT_YUYV:
		val |= SUN4I_BACKEND_IYUVCTL_FBPS_VYUY;
		अवरोध;
	हाल DRM_FORMAT_YVYU:
		val |= SUN4I_BACKEND_IYUVCTL_FBPS_UYVY;
		अवरोध;
	हाल DRM_FORMAT_UYVY:
		val |= SUN4I_BACKEND_IYUVCTL_FBPS_YVYU;
		अवरोध;
	हाल DRM_FORMAT_VYUY:
		val |= SUN4I_BACKEND_IYUVCTL_FBPS_YUYV;
		अवरोध;
	शेष:
		DRM_DEBUG_DRIVER("Unsupported YUV pixel sequence (0x%x)\n",
				 fmt);
	पूर्ण

	regmap_ग_लिखो(backend->engine.regs, SUN4I_BACKEND_IYUVCTL_REG, val);

	वापस 0;
पूर्ण

पूर्णांक sun4i_backend_update_layer_क्रमmats(काष्ठा sun4i_backend *backend,
				       पूर्णांक layer, काष्ठा drm_plane *plane)
अणु
	काष्ठा drm_plane_state *state = plane->state;
	काष्ठा drm_framebuffer *fb = state->fb;
	bool पूर्णांकerlaced = false;
	u32 val;
	पूर्णांक ret;

	/* Clear the YUV mode */
	regmap_update_bits(backend->engine.regs, SUN4I_BACKEND_ATTCTL_REG0(layer),
			   SUN4I_BACKEND_ATTCTL_REG0_LAY_YUVEN, 0);

	अगर (plane->state->crtc)
		पूर्णांकerlaced = plane->state->crtc->state->adjusted_mode.flags
			& DRM_MODE_FLAG_INTERLACE;

	regmap_update_bits(backend->engine.regs, SUN4I_BACKEND_MODCTL_REG,
			   SUN4I_BACKEND_MODCTL_ITLMOD_EN,
			   पूर्णांकerlaced ? SUN4I_BACKEND_MODCTL_ITLMOD_EN : 0);

	DRM_DEBUG_DRIVER("Switching display backend interlaced mode %s\n",
			 पूर्णांकerlaced ? "on" : "off");

	val = SUN4I_BACKEND_ATTCTL_REG0_LAY_GLBALPHA(state->alpha >> 8);
	अगर (state->alpha != DRM_BLEND_ALPHA_OPAQUE)
		val |= SUN4I_BACKEND_ATTCTL_REG0_LAY_GLBALPHA_EN;
	regmap_update_bits(backend->engine.regs,
			   SUN4I_BACKEND_ATTCTL_REG0(layer),
			   SUN4I_BACKEND_ATTCTL_REG0_LAY_GLBALPHA_MASK |
			   SUN4I_BACKEND_ATTCTL_REG0_LAY_GLBALPHA_EN,
			   val);

	अगर (fb->क्रमmat->is_yuv)
		वापस sun4i_backend_update_yuv_क्रमmat(backend, layer, plane);

	ret = sun4i_backend_drm_क्रमmat_to_layer(fb->क्रमmat->क्रमmat, &val);
	अगर (ret) अणु
		DRM_DEBUG_DRIVER("Invalid format\n");
		वापस ret;
	पूर्ण

	regmap_update_bits(backend->engine.regs,
			   SUN4I_BACKEND_ATTCTL_REG1(layer),
			   SUN4I_BACKEND_ATTCTL_REG1_LAY_FBFMT, val);

	वापस 0;
पूर्ण

पूर्णांक sun4i_backend_update_layer_frontend(काष्ठा sun4i_backend *backend,
					पूर्णांक layer, uपूर्णांक32_t fmt)
अणु
	u32 val;
	पूर्णांक ret;

	ret = sun4i_backend_drm_क्रमmat_to_layer(fmt, &val);
	अगर (ret) अणु
		DRM_DEBUG_DRIVER("Invalid format\n");
		वापस ret;
	पूर्ण

	regmap_update_bits(backend->engine.regs,
			   SUN4I_BACKEND_ATTCTL_REG0(layer),
			   SUN4I_BACKEND_ATTCTL_REG0_LAY_VDOEN,
			   SUN4I_BACKEND_ATTCTL_REG0_LAY_VDOEN);

	regmap_update_bits(backend->engine.regs,
			   SUN4I_BACKEND_ATTCTL_REG1(layer),
			   SUN4I_BACKEND_ATTCTL_REG1_LAY_FBFMT, val);

	वापस 0;
पूर्ण

अटल पूर्णांक sun4i_backend_update_yuv_buffer(काष्ठा sun4i_backend *backend,
					   काष्ठा drm_framebuffer *fb,
					   dma_addr_t paddr)
अणु
	/* TODO: Add support क्रम the multi-planar YUV क्रमmats */
	DRM_DEBUG_DRIVER("Setting packed YUV buffer address to %pad\n", &paddr);
	regmap_ग_लिखो(backend->engine.regs, SUN4I_BACKEND_IYUVADD_REG(0), paddr);

	DRM_DEBUG_DRIVER("Layer line width: %d bits\n", fb->pitches[0] * 8);
	regmap_ग_लिखो(backend->engine.regs, SUN4I_BACKEND_IYUVLINEWIDTH_REG(0),
		     fb->pitches[0] * 8);

	वापस 0;
पूर्ण

पूर्णांक sun4i_backend_update_layer_buffer(काष्ठा sun4i_backend *backend,
				      पूर्णांक layer, काष्ठा drm_plane *plane)
अणु
	काष्ठा drm_plane_state *state = plane->state;
	काष्ठा drm_framebuffer *fb = state->fb;
	u32 lo_paddr, hi_paddr;
	dma_addr_t paddr;

	/* Set the line width */
	DRM_DEBUG_DRIVER("Layer line width: %d bits\n", fb->pitches[0] * 8);
	regmap_ग_लिखो(backend->engine.regs,
		     SUN4I_BACKEND_LAYLINEWIDTH_REG(layer),
		     fb->pitches[0] * 8);

	/* Get the start of the displayed memory */
	paddr = drm_fb_cma_get_gem_addr(fb, state, 0);
	DRM_DEBUG_DRIVER("Setting buffer address to %pad\n", &paddr);

	अगर (fb->क्रमmat->is_yuv)
		वापस sun4i_backend_update_yuv_buffer(backend, fb, paddr);

	/* Write the 32 lower bits of the address (in bits) */
	lo_paddr = paddr << 3;
	DRM_DEBUG_DRIVER("Setting address lower bits to 0x%x\n", lo_paddr);
	regmap_ग_लिखो(backend->engine.regs,
		     SUN4I_BACKEND_LAYFB_L32ADD_REG(layer),
		     lo_paddr);

	/* And the upper bits */
	hi_paddr = paddr >> 29;
	DRM_DEBUG_DRIVER("Setting address high bits to 0x%x\n", hi_paddr);
	regmap_update_bits(backend->engine.regs, SUN4I_BACKEND_LAYFB_H4ADD_REG,
			   SUN4I_BACKEND_LAYFB_H4ADD_MSK(layer),
			   SUN4I_BACKEND_LAYFB_H4ADD(layer, hi_paddr));

	वापस 0;
पूर्ण

पूर्णांक sun4i_backend_update_layer_zpos(काष्ठा sun4i_backend *backend, पूर्णांक layer,
				    काष्ठा drm_plane *plane)
अणु
	काष्ठा drm_plane_state *state = plane->state;
	काष्ठा sun4i_layer_state *p_state = state_to_sun4i_layer_state(state);
	अचिन्हित पूर्णांक priority = state->normalized_zpos;
	अचिन्हित पूर्णांक pipe = p_state->pipe;

	DRM_DEBUG_DRIVER("Setting layer %d's priority to %d and pipe %d\n",
			 layer, priority, pipe);
	regmap_update_bits(backend->engine.regs, SUN4I_BACKEND_ATTCTL_REG0(layer),
			   SUN4I_BACKEND_ATTCTL_REG0_LAY_PIPESEL_MASK |
			   SUN4I_BACKEND_ATTCTL_REG0_LAY_PRISEL_MASK,
			   SUN4I_BACKEND_ATTCTL_REG0_LAY_PIPESEL(p_state->pipe) |
			   SUN4I_BACKEND_ATTCTL_REG0_LAY_PRISEL(priority));

	वापस 0;
पूर्ण

व्योम sun4i_backend_cleanup_layer(काष्ठा sun4i_backend *backend,
				 पूर्णांक layer)
अणु
	regmap_update_bits(backend->engine.regs,
			   SUN4I_BACKEND_ATTCTL_REG0(layer),
			   SUN4I_BACKEND_ATTCTL_REG0_LAY_VDOEN |
			   SUN4I_BACKEND_ATTCTL_REG0_LAY_YUVEN, 0);
पूर्ण

अटल bool sun4i_backend_plane_uses_scaler(काष्ठा drm_plane_state *state)
अणु
	u16 src_h = state->src_h >> 16;
	u16 src_w = state->src_w >> 16;

	DRM_DEBUG_DRIVER("Input size %dx%d, output size %dx%d\n",
			 src_w, src_h, state->crtc_w, state->crtc_h);

	अगर ((state->crtc_h != src_h) || (state->crtc_w != src_w))
		वापस true;

	वापस false;
पूर्ण

अटल bool sun4i_backend_plane_uses_frontend(काष्ठा drm_plane_state *state)
अणु
	काष्ठा sun4i_layer *layer = plane_to_sun4i_layer(state->plane);
	काष्ठा sun4i_backend *backend = layer->backend;
	uपूर्णांक32_t क्रमmat = state->fb->क्रमmat->क्रमmat;
	uपूर्णांक64_t modअगरier = state->fb->modअगरier;

	अगर (IS_ERR(backend->frontend))
		वापस false;

	अगर (!sun4i_frontend_क्रमmat_is_supported(क्रमmat, modअगरier))
		वापस false;

	अगर (!sun4i_backend_क्रमmat_is_supported(क्रमmat, modअगरier))
		वापस true;

	/*
	 * TODO: The backend alone allows 2x and 4x पूर्णांकeger scaling, including
	 * support क्रम an alpha component (which the frontend करोesn't support).
	 * Use the backend directly instead of the frontend in this हाल, with
	 * another test to वापस false.
	 */

	अगर (sun4i_backend_plane_uses_scaler(state))
		वापस true;

	/*
	 * Here the क्रमmat is supported by both the frontend and the backend
	 * and no frontend scaling is required, so use the backend directly.
	 */
	वापस false;
पूर्ण

अटल bool sun4i_backend_plane_is_supported(काष्ठा drm_plane_state *state,
					     bool *uses_frontend)
अणु
	अगर (sun4i_backend_plane_uses_frontend(state)) अणु
		*uses_frontend = true;
		वापस true;
	पूर्ण

	*uses_frontend = false;

	/* Scaling is not supported without the frontend. */
	अगर (sun4i_backend_plane_uses_scaler(state))
		वापस false;

	वापस true;
पूर्ण

अटल व्योम sun4i_backend_atomic_begin(काष्ठा sunxi_engine *engine,
				       काष्ठा drm_crtc_state *old_state)
अणु
	u32 val;

	WARN_ON(regmap_पढ़ो_poll_समयout(engine->regs,
					 SUN4I_BACKEND_REGBUFFCTL_REG,
					 val, !(val & SUN4I_BACKEND_REGBUFFCTL_LOADCTL),
					 100, 50000));
पूर्ण

अटल पूर्णांक sun4i_backend_atomic_check(काष्ठा sunxi_engine *engine,
				      काष्ठा drm_crtc_state *crtc_state)
अणु
	काष्ठा drm_plane_state *plane_states[SUN4I_BACKEND_NUM_LAYERS] = अणु 0 पूर्ण;
	काष्ठा sun4i_backend *backend = engine_to_sun4i_backend(engine);
	काष्ठा drm_atomic_state *state = crtc_state->state;
	काष्ठा drm_device *drm = state->dev;
	काष्ठा drm_plane *plane;
	अचिन्हित पूर्णांक num_planes = 0;
	अचिन्हित पूर्णांक num_alpha_planes = 0;
	अचिन्हित पूर्णांक num_frontend_planes = 0;
	अचिन्हित पूर्णांक num_alpha_planes_max = 1;
	अचिन्हित पूर्णांक num_yuv_planes = 0;
	अचिन्हित पूर्णांक current_pipe = 0;
	अचिन्हित पूर्णांक i;

	DRM_DEBUG_DRIVER("Starting checking our planes\n");

	अगर (!crtc_state->planes_changed)
		वापस 0;

	drm_क्रम_each_plane_mask(plane, drm, crtc_state->plane_mask) अणु
		काष्ठा drm_plane_state *plane_state =
			drm_atomic_get_plane_state(state, plane);
		काष्ठा sun4i_layer_state *layer_state =
			state_to_sun4i_layer_state(plane_state);
		काष्ठा drm_framebuffer *fb = plane_state->fb;

		अगर (!sun4i_backend_plane_is_supported(plane_state,
						      &layer_state->uses_frontend))
			वापस -EINVAL;

		अगर (layer_state->uses_frontend) अणु
			DRM_DEBUG_DRIVER("Using the frontend for plane %d\n",
					 plane->index);
			num_frontend_planes++;
		पूर्ण अन्यथा अणु
			अगर (fb->क्रमmat->is_yuv) अणु
				DRM_DEBUG_DRIVER("Plane FB format is YUV\n");
				num_yuv_planes++;
			पूर्ण
		पूर्ण

		DRM_DEBUG_DRIVER("Plane FB format is %p4cc\n",
				 &fb->क्रमmat->क्रमmat);
		अगर (fb->क्रमmat->has_alpha || (plane_state->alpha != DRM_BLEND_ALPHA_OPAQUE))
			num_alpha_planes++;

		DRM_DEBUG_DRIVER("Plane zpos is %d\n",
				 plane_state->normalized_zpos);

		/* Sort our planes by Zpos */
		plane_states[plane_state->normalized_zpos] = plane_state;

		num_planes++;
	पूर्ण

	/* All our planes were disabled, bail out */
	अगर (!num_planes)
		वापस 0;

	/*
	 * The hardware is a bit unusual here.
	 *
	 * Even though it supports 4 layers, it करोes the composition
	 * in two separate steps.
	 *
	 * The first one is assigning a layer to one of its two
	 * pipes. If more that 1 layer is asचिन्हित to the same pipe,
	 * and अगर pixels overlaps, the pipe will take the pixel from
	 * the layer with the highest priority.
	 *
	 * The second step is the actual alpha blending, that takes
	 * the two pipes as input, and uses the potential alpha
	 * component to करो the transparency between the two.
	 *
	 * This two-step scenario makes us unable to guarantee a
	 * robust alpha blending between the 4 layers in all
	 * situations, since this means that we need to have one layer
	 * with alpha at the lowest position of our two pipes.
	 *
	 * However, we cannot even करो that on every platक्रमm, since
	 * the hardware has a bug where the lowest plane of the lowest
	 * pipe (pipe 0, priority 0), अगर it has any alpha, will
	 * discard the pixel data entirely and just display the pixels
	 * in the background color (black by शेष).
	 *
	 * This means that on the affected platक्रमms, we effectively
	 * have only three valid configurations with alpha, all of
	 * them with the alpha being on pipe1 with the lowest
	 * position, which can be 1, 2 or 3 depending on the number of
	 * planes and their zpos.
	 */

	/* For platक्रमms that are not affected by the issue described above. */
	अगर (backend->quirks->supports_lowest_plane_alpha)
		num_alpha_planes_max++;

	अगर (num_alpha_planes > num_alpha_planes_max) अणु
		DRM_DEBUG_DRIVER("Too many planes with alpha, rejecting...\n");
		वापस -EINVAL;
	पूर्ण

	/* We can't have an alpha plane at the lowest position */
	अगर (!backend->quirks->supports_lowest_plane_alpha &&
	    (plane_states[0]->alpha != DRM_BLEND_ALPHA_OPAQUE))
		वापस -EINVAL;

	क्रम (i = 1; i < num_planes; i++) अणु
		काष्ठा drm_plane_state *p_state = plane_states[i];
		काष्ठा drm_framebuffer *fb = p_state->fb;
		काष्ठा sun4i_layer_state *s_state = state_to_sun4i_layer_state(p_state);

		/*
		 * The only alpha position is the lowest plane of the
		 * second pipe.
		 */
		अगर (fb->क्रमmat->has_alpha || (p_state->alpha != DRM_BLEND_ALPHA_OPAQUE))
			current_pipe++;

		s_state->pipe = current_pipe;
	पूर्ण

	/* We can only have a single YUV plane at a समय */
	अगर (num_yuv_planes > SUN4I_BACKEND_NUM_YUV_PLANES) अणु
		DRM_DEBUG_DRIVER("Too many planes with YUV, rejecting...\n");
		वापस -EINVAL;
	पूर्ण

	अगर (num_frontend_planes > SUN4I_BACKEND_NUM_FRONTEND_LAYERS) अणु
		DRM_DEBUG_DRIVER("Too many planes going through the frontend, rejecting\n");
		वापस -EINVAL;
	पूर्ण

	DRM_DEBUG_DRIVER("State valid with %u planes, %u alpha, %u video, %u YUV\n",
			 num_planes, num_alpha_planes, num_frontend_planes,
			 num_yuv_planes);

	वापस 0;
पूर्ण

अटल व्योम sun4i_backend_vblank_quirk(काष्ठा sunxi_engine *engine)
अणु
	काष्ठा sun4i_backend *backend = engine_to_sun4i_backend(engine);
	काष्ठा sun4i_frontend *frontend = backend->frontend;

	अगर (!frontend)
		वापस;

	/*
	 * In a tearकरोwn scenario with the frontend involved, we have
	 * to keep the frontend enabled until the next vblank, and
	 * only then disable it.
	 *
	 * This is due to the fact that the backend will not take पूर्णांकo
	 * account the new configuration (with the plane that used to
	 * be fed by the frontend now disabled) until we ग_लिखो to the
	 * commit bit and the hardware fetches the new configuration
	 * during the next vblank.
	 *
	 * So we keep the frontend around in order to prevent any
	 * visual artअगरacts.
	 */
	spin_lock(&backend->frontend_lock);
	अगर (backend->frontend_tearकरोwn) अणु
		sun4i_frontend_निकास(frontend);
		backend->frontend_tearकरोwn = false;
	पूर्ण
	spin_unlock(&backend->frontend_lock);
पूर्ण;

अटल पूर्णांक sun4i_backend_init_sat(काष्ठा device *dev) अणु
	काष्ठा sun4i_backend *backend = dev_get_drvdata(dev);
	पूर्णांक ret;

	backend->sat_reset = devm_reset_control_get(dev, "sat");
	अगर (IS_ERR(backend->sat_reset)) अणु
		dev_err(dev, "Couldn't get the SAT reset line\n");
		वापस PTR_ERR(backend->sat_reset);
	पूर्ण

	ret = reset_control_deनिश्चित(backend->sat_reset);
	अगर (ret) अणु
		dev_err(dev, "Couldn't deassert the SAT reset line\n");
		वापस ret;
	पूर्ण

	backend->sat_clk = devm_clk_get(dev, "sat");
	अगर (IS_ERR(backend->sat_clk)) अणु
		dev_err(dev, "Couldn't get our SAT clock\n");
		ret = PTR_ERR(backend->sat_clk);
		जाओ err_निश्चित_reset;
	पूर्ण

	ret = clk_prepare_enable(backend->sat_clk);
	अगर (ret) अणु
		dev_err(dev, "Couldn't enable the SAT clock\n");
		वापस ret;
	पूर्ण

	वापस 0;

err_निश्चित_reset:
	reset_control_निश्चित(backend->sat_reset);
	वापस ret;
पूर्ण

अटल पूर्णांक sun4i_backend_मुक्त_sat(काष्ठा device *dev) अणु
	काष्ठा sun4i_backend *backend = dev_get_drvdata(dev);

	clk_disable_unprepare(backend->sat_clk);
	reset_control_निश्चित(backend->sat_reset);

	वापस 0;
पूर्ण

/*
 * The display backend can take video output from the display frontend, or
 * the display enhancement unit on the A80, as input क्रम one it its layers.
 * This relationship within the display pipeline is encoded in the device
 * tree with of_graph, and we use it here to figure out which backend, अगर
 * there are 2 or more, we are currently probing. The number would be in
 * the "reg" property of the upstream output port endpoपूर्णांक.
 */
अटल पूर्णांक sun4i_backend_of_get_id(काष्ठा device_node *node)
अणु
	काष्ठा device_node *ep, *remote;
	काष्ठा of_endpoपूर्णांक of_ep;

	/* Input port is 0, and we want the first endpoपूर्णांक. */
	ep = of_graph_get_endpoपूर्णांक_by_regs(node, 0, -1);
	अगर (!ep)
		वापस -EINVAL;

	remote = of_graph_get_remote_endpoपूर्णांक(ep);
	of_node_put(ep);
	अगर (!remote)
		वापस -EINVAL;

	of_graph_parse_endpoपूर्णांक(remote, &of_ep);
	of_node_put(remote);
	वापस of_ep.id;
पूर्ण

/* TODO: This needs to take multiple pipelines पूर्णांकo account */
अटल काष्ठा sun4i_frontend *sun4i_backend_find_frontend(काष्ठा sun4i_drv *drv,
							  काष्ठा device_node *node)
अणु
	काष्ठा device_node *port, *ep, *remote;
	काष्ठा sun4i_frontend *frontend;

	port = of_graph_get_port_by_id(node, 0);
	अगर (!port)
		वापस ERR_PTR(-EINVAL);

	क्रम_each_available_child_of_node(port, ep) अणु
		remote = of_graph_get_remote_port_parent(ep);
		अगर (!remote)
			जारी;
		of_node_put(remote);

		/* करोes this node match any रेजिस्टरed engines? */
		list_क्रम_each_entry(frontend, &drv->frontend_list, list) अणु
			अगर (remote == frontend->node) अणु
				of_node_put(port);
				of_node_put(ep);
				वापस frontend;
			पूर्ण
		पूर्ण
	पूर्ण
	of_node_put(port);
	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल स्थिर काष्ठा sunxi_engine_ops sun4i_backend_engine_ops = अणु
	.atomic_begin			= sun4i_backend_atomic_begin,
	.atomic_check			= sun4i_backend_atomic_check,
	.commit				= sun4i_backend_commit,
	.layers_init			= sun4i_layers_init,
	.apply_color_correction		= sun4i_backend_apply_color_correction,
	.disable_color_correction	= sun4i_backend_disable_color_correction,
	.vblank_quirk			= sun4i_backend_vblank_quirk,
पूर्ण;

अटल स्थिर काष्ठा regmap_config sun4i_backend_regmap_config = अणु
	.reg_bits	= 32,
	.val_bits	= 32,
	.reg_stride	= 4,
	.max_रेजिस्टर	= 0x5800,
पूर्ण;

अटल पूर्णांक sun4i_backend_bind(काष्ठा device *dev, काष्ठा device *master,
			      व्योम *data)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा drm_device *drm = data;
	काष्ठा sun4i_drv *drv = drm->dev_निजी;
	काष्ठा sun4i_backend *backend;
	स्थिर काष्ठा sun4i_backend_quirks *quirks;
	काष्ठा resource *res;
	व्योम __iomem *regs;
	पूर्णांक i, ret;

	backend = devm_kzalloc(dev, माप(*backend), GFP_KERNEL);
	अगर (!backend)
		वापस -ENOMEM;
	dev_set_drvdata(dev, backend);
	spin_lock_init(&backend->frontend_lock);

	अगर (of_find_property(dev->of_node, "interconnects", शून्य)) अणु
		/*
		 * This assume we have the same DMA स्थिरraपूर्णांकs क्रम all our the
		 * devices in our pipeline (all the backends, but also the
		 * frontends). This sounds bad, but it has always been the हाल
		 * क्रम us, and DRM करोesn't करो per-device allocation either, so
		 * we would need to fix DRM first...
		 */
		ret = of_dma_configure(drm->dev, dev->of_node, true);
		अगर (ret)
			वापस ret;
	पूर्ण

	backend->engine.node = dev->of_node;
	backend->engine.ops = &sun4i_backend_engine_ops;
	backend->engine.id = sun4i_backend_of_get_id(dev->of_node);
	अगर (backend->engine.id < 0)
		वापस backend->engine.id;

	backend->frontend = sun4i_backend_find_frontend(drv, dev->of_node);
	अगर (IS_ERR(backend->frontend))
		dev_warn(dev, "Couldn't find matching frontend, frontend features disabled\n");

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	regs = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(regs))
		वापस PTR_ERR(regs);

	backend->reset = devm_reset_control_get(dev, शून्य);
	अगर (IS_ERR(backend->reset)) अणु
		dev_err(dev, "Couldn't get our reset line\n");
		वापस PTR_ERR(backend->reset);
	पूर्ण

	ret = reset_control_deनिश्चित(backend->reset);
	अगर (ret) अणु
		dev_err(dev, "Couldn't deassert our reset line\n");
		वापस ret;
	पूर्ण

	backend->bus_clk = devm_clk_get(dev, "ahb");
	अगर (IS_ERR(backend->bus_clk)) अणु
		dev_err(dev, "Couldn't get the backend bus clock\n");
		ret = PTR_ERR(backend->bus_clk);
		जाओ err_निश्चित_reset;
	पूर्ण
	clk_prepare_enable(backend->bus_clk);

	backend->mod_clk = devm_clk_get(dev, "mod");
	अगर (IS_ERR(backend->mod_clk)) अणु
		dev_err(dev, "Couldn't get the backend module clock\n");
		ret = PTR_ERR(backend->mod_clk);
		जाओ err_disable_bus_clk;
	पूर्ण

	ret = clk_set_rate_exclusive(backend->mod_clk, 300000000);
	अगर (ret) अणु
		dev_err(dev, "Couldn't set the module clock frequency\n");
		जाओ err_disable_bus_clk;
	पूर्ण

	clk_prepare_enable(backend->mod_clk);

	backend->ram_clk = devm_clk_get(dev, "ram");
	अगर (IS_ERR(backend->ram_clk)) अणु
		dev_err(dev, "Couldn't get the backend RAM clock\n");
		ret = PTR_ERR(backend->ram_clk);
		जाओ err_disable_mod_clk;
	पूर्ण
	clk_prepare_enable(backend->ram_clk);

	अगर (of_device_is_compatible(dev->of_node,
				    "allwinner,sun8i-a33-display-backend")) अणु
		ret = sun4i_backend_init_sat(dev);
		अगर (ret) अणु
			dev_err(dev, "Couldn't init SAT resources\n");
			जाओ err_disable_ram_clk;
		पूर्ण
	पूर्ण

	backend->engine.regs = devm_regmap_init_mmio(dev, regs,
						     &sun4i_backend_regmap_config);
	अगर (IS_ERR(backend->engine.regs)) अणु
		dev_err(dev, "Couldn't create the backend regmap\n");
		वापस PTR_ERR(backend->engine.regs);
	पूर्ण

	list_add_tail(&backend->engine.list, &drv->engine_list);

	/*
	 * Many of the backend's layer configuration रेजिस्टरs have
	 * undefined शेष values. This poses a risk as we use
	 * regmap_update_bits in some places, and करोn't overग_लिखो
	 * the whole रेजिस्टर.
	 *
	 * Clear the रेजिस्टरs here to have something predictable.
	 */
	क्रम (i = 0x800; i < 0x1000; i += 4)
		regmap_ग_लिखो(backend->engine.regs, i, 0);

	/* Disable रेजिस्टरs स्वतःloading */
	regmap_ग_लिखो(backend->engine.regs, SUN4I_BACKEND_REGBUFFCTL_REG,
		     SUN4I_BACKEND_REGBUFFCTL_AUTOLOAD_DIS);

	/* Enable the backend */
	regmap_ग_लिखो(backend->engine.regs, SUN4I_BACKEND_MODCTL_REG,
		     SUN4I_BACKEND_MODCTL_DEBE_EN |
		     SUN4I_BACKEND_MODCTL_START_CTL);

	/* Set output selection अगर needed */
	quirks = of_device_get_match_data(dev);
	अगर (quirks->needs_output_muxing) अणु
		/*
		 * We assume there is no dynamic muxing of backends
		 * and TCONs, so we select the backend with same ID.
		 *
		 * While dynamic selection might be पूर्णांकeresting, since
		 * the CRTC is tied to the TCON, जबतक the layers are
		 * tied to the backends, this means, we will need to
		 * चयन between groups of layers. There might not be
		 * a way to represent this स्थिरraपूर्णांक in DRM.
		 */
		regmap_update_bits(backend->engine.regs,
				   SUN4I_BACKEND_MODCTL_REG,
				   SUN4I_BACKEND_MODCTL_OUT_SEL,
				   (backend->engine.id
				    ? SUN4I_BACKEND_MODCTL_OUT_LCD1
				    : SUN4I_BACKEND_MODCTL_OUT_LCD0));
	पूर्ण

	backend->quirks = quirks;

	वापस 0;

err_disable_ram_clk:
	clk_disable_unprepare(backend->ram_clk);
err_disable_mod_clk:
	clk_rate_exclusive_put(backend->mod_clk);
	clk_disable_unprepare(backend->mod_clk);
err_disable_bus_clk:
	clk_disable_unprepare(backend->bus_clk);
err_निश्चित_reset:
	reset_control_निश्चित(backend->reset);
	वापस ret;
पूर्ण

अटल व्योम sun4i_backend_unbind(काष्ठा device *dev, काष्ठा device *master,
				 व्योम *data)
अणु
	काष्ठा sun4i_backend *backend = dev_get_drvdata(dev);

	list_del(&backend->engine.list);

	अगर (of_device_is_compatible(dev->of_node,
				    "allwinner,sun8i-a33-display-backend"))
		sun4i_backend_मुक्त_sat(dev);

	clk_disable_unprepare(backend->ram_clk);
	clk_rate_exclusive_put(backend->mod_clk);
	clk_disable_unprepare(backend->mod_clk);
	clk_disable_unprepare(backend->bus_clk);
	reset_control_निश्चित(backend->reset);
पूर्ण

अटल स्थिर काष्ठा component_ops sun4i_backend_ops = अणु
	.bind	= sun4i_backend_bind,
	.unbind	= sun4i_backend_unbind,
पूर्ण;

अटल पूर्णांक sun4i_backend_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस component_add(&pdev->dev, &sun4i_backend_ops);
पूर्ण

अटल पूर्णांक sun4i_backend_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	component_del(&pdev->dev, &sun4i_backend_ops);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा sun4i_backend_quirks sun4i_backend_quirks = अणु
	.needs_output_muxing = true,
पूर्ण;

अटल स्थिर काष्ठा sun4i_backend_quirks sun5i_backend_quirks = अणु
पूर्ण;

अटल स्थिर काष्ठा sun4i_backend_quirks sun6i_backend_quirks = अणु
पूर्ण;

अटल स्थिर काष्ठा sun4i_backend_quirks sun7i_backend_quirks = अणु
	.needs_output_muxing = true,
पूर्ण;

अटल स्थिर काष्ठा sun4i_backend_quirks sun8i_a33_backend_quirks = अणु
	.supports_lowest_plane_alpha = true,
पूर्ण;

अटल स्थिर काष्ठा sun4i_backend_quirks sun9i_backend_quirks = अणु
पूर्ण;

अटल स्थिर काष्ठा of_device_id sun4i_backend_of_table[] = अणु
	अणु
		.compatible = "allwinner,sun4i-a10-display-backend",
		.data = &sun4i_backend_quirks,
	पूर्ण,
	अणु
		.compatible = "allwinner,sun5i-a13-display-backend",
		.data = &sun5i_backend_quirks,
	पूर्ण,
	अणु
		.compatible = "allwinner,sun6i-a31-display-backend",
		.data = &sun6i_backend_quirks,
	पूर्ण,
	अणु
		.compatible = "allwinner,sun7i-a20-display-backend",
		.data = &sun7i_backend_quirks,
	पूर्ण,
	अणु
		.compatible = "allwinner,sun8i-a23-display-backend",
		.data = &sun8i_a33_backend_quirks,
	पूर्ण,
	अणु
		.compatible = "allwinner,sun8i-a33-display-backend",
		.data = &sun8i_a33_backend_quirks,
	पूर्ण,
	अणु
		.compatible = "allwinner,sun9i-a80-display-backend",
		.data = &sun9i_backend_quirks,
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sun4i_backend_of_table);

अटल काष्ठा platक्रमm_driver sun4i_backend_platक्रमm_driver = अणु
	.probe		= sun4i_backend_probe,
	.हटाओ		= sun4i_backend_हटाओ,
	.driver		= अणु
		.name		= "sun4i-backend",
		.of_match_table	= sun4i_backend_of_table,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(sun4i_backend_platक्रमm_driver);

MODULE_AUTHOR("Maxime Ripard <maxime.ripard@free-electrons.com>");
MODULE_DESCRIPTION("Allwinner A10 Display Backend Driver");
MODULE_LICENSE("GPL");
