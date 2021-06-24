<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2014 Free Electrons
 * Copyright (C) 2014 Aपंचांगel
 *
 * Author: Boris BREZILLON <boris.brezillon@मुक्त-electrons.com>
 */

#समावेश <linux/dmapool.h>
#समावेश <linux/mfd/aपंचांगel-hlcdc.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_fb_cma_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_gem_cma_helper.h>
#समावेश <drm/drm_plane_helper.h>

#समावेश "atmel_hlcdc_dc.h"

/**
 * काष्ठा aपंचांगel_hlcdc_plane_state - Aपंचांगel HLCDC Plane state काष्ठाure.
 *
 * @base: DRM plane state
 * @crtc_x: x position of the plane relative to the CRTC
 * @crtc_y: y position of the plane relative to the CRTC
 * @crtc_w: visible width of the plane
 * @crtc_h: visible height of the plane
 * @src_x: x buffer position
 * @src_y: y buffer position
 * @src_w: buffer width
 * @src_h: buffer height
 * @disc_x: x discard position
 * @disc_y: y discard position
 * @disc_w: discard width
 * @disc_h: discard height
 * @ahb_id: AHB identअगरication number
 * @bpp: bytes per pixel deduced from pixel_क्रमmat
 * @offsets: offsets to apply to the GEM buffers
 * @xstride: value to add to the pixel poपूर्णांकer between each line
 * @pstride: value to add to the pixel poपूर्णांकer between each pixel
 * @nplanes: number of planes (deduced from pixel_क्रमmat)
 * @dscrs: DMA descriptors
 */
काष्ठा aपंचांगel_hlcdc_plane_state अणु
	काष्ठा drm_plane_state base;
	पूर्णांक crtc_x;
	पूर्णांक crtc_y;
	अचिन्हित पूर्णांक crtc_w;
	अचिन्हित पूर्णांक crtc_h;
	uपूर्णांक32_t src_x;
	uपूर्णांक32_t src_y;
	uपूर्णांक32_t src_w;
	uपूर्णांक32_t src_h;

	पूर्णांक disc_x;
	पूर्णांक disc_y;
	पूर्णांक disc_w;
	पूर्णांक disc_h;

	पूर्णांक ahb_id;

	/* These fields are निजी and should not be touched */
	पूर्णांक bpp[ATMEL_HLCDC_LAYER_MAX_PLANES];
	अचिन्हित पूर्णांक offsets[ATMEL_HLCDC_LAYER_MAX_PLANES];
	पूर्णांक xstride[ATMEL_HLCDC_LAYER_MAX_PLANES];
	पूर्णांक pstride[ATMEL_HLCDC_LAYER_MAX_PLANES];
	पूर्णांक nplanes;

	/* DMA descriptors. */
	काष्ठा aपंचांगel_hlcdc_dma_channel_dscr *dscrs[ATMEL_HLCDC_LAYER_MAX_PLANES];
पूर्ण;

अटल अंतरभूत काष्ठा aपंचांगel_hlcdc_plane_state *
drm_plane_state_to_aपंचांगel_hlcdc_plane_state(काष्ठा drm_plane_state *s)
अणु
	वापस container_of(s, काष्ठा aपंचांगel_hlcdc_plane_state, base);
पूर्ण

#घोषणा SUBPIXEL_MASK			0xffff

अटल uपूर्णांक32_t rgb_क्रमmats[] = अणु
	DRM_FORMAT_C8,
	DRM_FORMAT_XRGB4444,
	DRM_FORMAT_ARGB4444,
	DRM_FORMAT_RGBA4444,
	DRM_FORMAT_ARGB1555,
	DRM_FORMAT_RGB565,
	DRM_FORMAT_RGB888,
	DRM_FORMAT_XRGB8888,
	DRM_FORMAT_ARGB8888,
	DRM_FORMAT_RGBA8888,
पूर्ण;

काष्ठा aपंचांगel_hlcdc_क्रमmats aपंचांगel_hlcdc_plane_rgb_क्रमmats = अणु
	.क्रमmats = rgb_क्रमmats,
	.nक्रमmats = ARRAY_SIZE(rgb_क्रमmats),
पूर्ण;

अटल uपूर्णांक32_t rgb_and_yuv_क्रमmats[] = अणु
	DRM_FORMAT_C8,
	DRM_FORMAT_XRGB4444,
	DRM_FORMAT_ARGB4444,
	DRM_FORMAT_RGBA4444,
	DRM_FORMAT_ARGB1555,
	DRM_FORMAT_RGB565,
	DRM_FORMAT_RGB888,
	DRM_FORMAT_XRGB8888,
	DRM_FORMAT_ARGB8888,
	DRM_FORMAT_RGBA8888,
	DRM_FORMAT_AYUV,
	DRM_FORMAT_YUYV,
	DRM_FORMAT_UYVY,
	DRM_FORMAT_YVYU,
	DRM_FORMAT_VYUY,
	DRM_FORMAT_NV21,
	DRM_FORMAT_NV61,
	DRM_FORMAT_YUV422,
	DRM_FORMAT_YUV420,
पूर्ण;

काष्ठा aपंचांगel_hlcdc_क्रमmats aपंचांगel_hlcdc_plane_rgb_and_yuv_क्रमmats = अणु
	.क्रमmats = rgb_and_yuv_क्रमmats,
	.nक्रमmats = ARRAY_SIZE(rgb_and_yuv_क्रमmats),
पूर्ण;

अटल पूर्णांक aपंचांगel_hlcdc_क्रमmat_to_plane_mode(u32 क्रमmat, u32 *mode)
अणु
	चयन (क्रमmat) अणु
	हाल DRM_FORMAT_C8:
		*mode = ATMEL_HLCDC_C8_MODE;
		अवरोध;
	हाल DRM_FORMAT_XRGB4444:
		*mode = ATMEL_HLCDC_XRGB4444_MODE;
		अवरोध;
	हाल DRM_FORMAT_ARGB4444:
		*mode = ATMEL_HLCDC_ARGB4444_MODE;
		अवरोध;
	हाल DRM_FORMAT_RGBA4444:
		*mode = ATMEL_HLCDC_RGBA4444_MODE;
		अवरोध;
	हाल DRM_FORMAT_RGB565:
		*mode = ATMEL_HLCDC_RGB565_MODE;
		अवरोध;
	हाल DRM_FORMAT_RGB888:
		*mode = ATMEL_HLCDC_RGB888_MODE;
		अवरोध;
	हाल DRM_FORMAT_ARGB1555:
		*mode = ATMEL_HLCDC_ARGB1555_MODE;
		अवरोध;
	हाल DRM_FORMAT_XRGB8888:
		*mode = ATMEL_HLCDC_XRGB8888_MODE;
		अवरोध;
	हाल DRM_FORMAT_ARGB8888:
		*mode = ATMEL_HLCDC_ARGB8888_MODE;
		अवरोध;
	हाल DRM_FORMAT_RGBA8888:
		*mode = ATMEL_HLCDC_RGBA8888_MODE;
		अवरोध;
	हाल DRM_FORMAT_AYUV:
		*mode = ATMEL_HLCDC_AYUV_MODE;
		अवरोध;
	हाल DRM_FORMAT_YUYV:
		*mode = ATMEL_HLCDC_YUYV_MODE;
		अवरोध;
	हाल DRM_FORMAT_UYVY:
		*mode = ATMEL_HLCDC_UYVY_MODE;
		अवरोध;
	हाल DRM_FORMAT_YVYU:
		*mode = ATMEL_HLCDC_YVYU_MODE;
		अवरोध;
	हाल DRM_FORMAT_VYUY:
		*mode = ATMEL_HLCDC_VYUY_MODE;
		अवरोध;
	हाल DRM_FORMAT_NV21:
		*mode = ATMEL_HLCDC_NV21_MODE;
		अवरोध;
	हाल DRM_FORMAT_NV61:
		*mode = ATMEL_HLCDC_NV61_MODE;
		अवरोध;
	हाल DRM_FORMAT_YUV420:
		*mode = ATMEL_HLCDC_YUV420_MODE;
		अवरोध;
	हाल DRM_FORMAT_YUV422:
		*mode = ATMEL_HLCDC_YUV422_MODE;
		अवरोध;
	शेष:
		वापस -ENOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल u32 heo_करोwnscaling_xcoef[] = अणु
	0x11343311,
	0x000000f7,
	0x1635300c,
	0x000000f9,
	0x1b362c08,
	0x000000fb,
	0x1f372804,
	0x000000fe,
	0x24382400,
	0x00000000,
	0x28371ffe,
	0x00000004,
	0x2c361bfb,
	0x00000008,
	0x303516f9,
	0x0000000c,
पूर्ण;

अटल u32 heo_करोwnscaling_ycoef[] = अणु
	0x00123737,
	0x00173732,
	0x001b382d,
	0x001f3928,
	0x00243824,
	0x0028391f,
	0x002d381b,
	0x00323717,
पूर्ण;

अटल u32 heo_upscaling_xcoef[] = अणु
	0xf74949f7,
	0x00000000,
	0xf55f33fb,
	0x000000fe,
	0xf5701efe,
	0x000000ff,
	0xf87c0dff,
	0x00000000,
	0x00800000,
	0x00000000,
	0x0d7cf800,
	0x000000ff,
	0x1e70f5ff,
	0x000000fe,
	0x335ff5fe,
	0x000000fb,
पूर्ण;

अटल u32 heo_upscaling_ycoef[] = अणु
	0x00004040,
	0x00075920,
	0x00056f0c,
	0x00027b03,
	0x00008000,
	0x00037b02,
	0x000c6f05,
	0x00205907,
पूर्ण;

#घोषणा ATMEL_HLCDC_XPHIDEF	4
#घोषणा ATMEL_HLCDC_YPHIDEF	4

अटल u32 aपंचांगel_hlcdc_plane_phiscaler_get_factor(u32 srcsize,
						  u32 dstsize,
						  u32 phidef)
अणु
	u32 factor, max_memsize;

	factor = (256 * ((8 * (srcsize - 1)) - phidef)) / (dstsize - 1);
	max_memsize = ((factor * (dstsize - 1)) + (256 * phidef)) / 2048;

	अगर (max_memsize > srcsize - 1)
		factor--;

	वापस factor;
पूर्ण

अटल व्योम
aपंचांगel_hlcdc_plane_scaler_set_phicoeff(काष्ठा aपंचांगel_hlcdc_plane *plane,
				      स्थिर u32 *coeff_tab, पूर्णांक size,
				      अचिन्हित पूर्णांक cfg_offs)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < size; i++)
		aपंचांगel_hlcdc_layer_ग_लिखो_cfg(&plane->layer, cfg_offs + i,
					    coeff_tab[i]);
पूर्ण

अटल व्योम aपंचांगel_hlcdc_plane_setup_scaler(काष्ठा aपंचांगel_hlcdc_plane *plane,
					   काष्ठा aपंचांगel_hlcdc_plane_state *state)
अणु
	स्थिर काष्ठा aपंचांगel_hlcdc_layer_desc *desc = plane->layer.desc;
	u32 xfactor, yfactor;

	अगर (!desc->layout.scaler_config)
		वापस;

	अगर (state->crtc_w == state->src_w && state->crtc_h == state->src_h) अणु
		aपंचांगel_hlcdc_layer_ग_लिखो_cfg(&plane->layer,
					    desc->layout.scaler_config, 0);
		वापस;
	पूर्ण

	अगर (desc->layout.phicoeffs.x) अणु
		xfactor = aपंचांगel_hlcdc_plane_phiscaler_get_factor(state->src_w,
							state->crtc_w,
							ATMEL_HLCDC_XPHIDEF);

		yfactor = aपंचांगel_hlcdc_plane_phiscaler_get_factor(state->src_h,
							state->crtc_h,
							ATMEL_HLCDC_YPHIDEF);

		aपंचांगel_hlcdc_plane_scaler_set_phicoeff(plane,
				state->crtc_w < state->src_w ?
				heo_करोwnscaling_xcoef :
				heo_upscaling_xcoef,
				ARRAY_SIZE(heo_upscaling_xcoef),
				desc->layout.phicoeffs.x);

		aपंचांगel_hlcdc_plane_scaler_set_phicoeff(plane,
				state->crtc_h < state->src_h ?
				heo_करोwnscaling_ycoef :
				heo_upscaling_ycoef,
				ARRAY_SIZE(heo_upscaling_ycoef),
				desc->layout.phicoeffs.y);
	पूर्ण अन्यथा अणु
		xfactor = (1024 * state->src_w) / state->crtc_w;
		yfactor = (1024 * state->src_h) / state->crtc_h;
	पूर्ण

	aपंचांगel_hlcdc_layer_ग_लिखो_cfg(&plane->layer, desc->layout.scaler_config,
				    ATMEL_HLCDC_LAYER_SCALER_ENABLE |
				    ATMEL_HLCDC_LAYER_SCALER_FACTORS(xfactor,
								     yfactor));
पूर्ण

अटल व्योम
aपंचांगel_hlcdc_plane_update_pos_and_size(काष्ठा aपंचांगel_hlcdc_plane *plane,
				      काष्ठा aपंचांगel_hlcdc_plane_state *state)
अणु
	स्थिर काष्ठा aपंचांगel_hlcdc_layer_desc *desc = plane->layer.desc;

	अगर (desc->layout.size)
		aपंचांगel_hlcdc_layer_ग_लिखो_cfg(&plane->layer, desc->layout.size,
					ATMEL_HLCDC_LAYER_SIZE(state->crtc_w,
							       state->crtc_h));

	अगर (desc->layout.memsize)
		aपंचांगel_hlcdc_layer_ग_लिखो_cfg(&plane->layer,
					desc->layout.memsize,
					ATMEL_HLCDC_LAYER_SIZE(state->src_w,
							       state->src_h));

	अगर (desc->layout.pos)
		aपंचांगel_hlcdc_layer_ग_लिखो_cfg(&plane->layer, desc->layout.pos,
					ATMEL_HLCDC_LAYER_POS(state->crtc_x,
							      state->crtc_y));

	aपंचांगel_hlcdc_plane_setup_scaler(plane, state);
पूर्ण

अटल व्योम
aपंचांगel_hlcdc_plane_update_general_settings(काष्ठा aपंचांगel_hlcdc_plane *plane,
					काष्ठा aपंचांगel_hlcdc_plane_state *state)
अणु
	अचिन्हित पूर्णांक cfg = ATMEL_HLCDC_LAYER_DMA_BLEN_INCR16 | state->ahb_id;
	स्थिर काष्ठा aपंचांगel_hlcdc_layer_desc *desc = plane->layer.desc;
	स्थिर काष्ठा drm_क्रमmat_info *क्रमmat = state->base.fb->क्रमmat;

	/*
	 * Rotation optimization is not working on RGB888 (rotation is still
	 * working but without any optimization).
	 */
	अगर (क्रमmat->क्रमmat == DRM_FORMAT_RGB888)
		cfg |= ATMEL_HLCDC_LAYER_DMA_ROTDIS;

	aपंचांगel_hlcdc_layer_ग_लिखो_cfg(&plane->layer, ATMEL_HLCDC_LAYER_DMA_CFG,
				    cfg);

	cfg = ATMEL_HLCDC_LAYER_DMA | ATMEL_HLCDC_LAYER_REP;

	अगर (plane->base.type != DRM_PLANE_TYPE_PRIMARY) अणु
		cfg |= ATMEL_HLCDC_LAYER_OVR | ATMEL_HLCDC_LAYER_ITER2BL |
		       ATMEL_HLCDC_LAYER_ITER;

		अगर (क्रमmat->has_alpha)
			cfg |= ATMEL_HLCDC_LAYER_LAEN;
		अन्यथा
			cfg |= ATMEL_HLCDC_LAYER_GAEN |
			       ATMEL_HLCDC_LAYER_GA(state->base.alpha);
	पूर्ण

	अगर (state->disc_h && state->disc_w)
		cfg |= ATMEL_HLCDC_LAYER_DISCEN;

	aपंचांगel_hlcdc_layer_ग_लिखो_cfg(&plane->layer, desc->layout.general_config,
				    cfg);
पूर्ण

अटल व्योम aपंचांगel_hlcdc_plane_update_क्रमmat(काष्ठा aपंचांगel_hlcdc_plane *plane,
					काष्ठा aपंचांगel_hlcdc_plane_state *state)
अणु
	u32 cfg;
	पूर्णांक ret;

	ret = aपंचांगel_hlcdc_क्रमmat_to_plane_mode(state->base.fb->क्रमmat->क्रमmat,
					       &cfg);
	अगर (ret)
		वापस;

	अगर ((state->base.fb->क्रमmat->क्रमmat == DRM_FORMAT_YUV422 ||
	     state->base.fb->क्रमmat->क्रमmat == DRM_FORMAT_NV61) &&
	    drm_rotation_90_or_270(state->base.rotation))
		cfg |= ATMEL_HLCDC_YUV422ROT;

	aपंचांगel_hlcdc_layer_ग_लिखो_cfg(&plane->layer,
				    ATMEL_HLCDC_LAYER_FORMAT_CFG, cfg);
पूर्ण

अटल व्योम aपंचांगel_hlcdc_plane_update_clut(काष्ठा aपंचांगel_hlcdc_plane *plane,
					  काष्ठा aपंचांगel_hlcdc_plane_state *state)
अणु
	काष्ठा drm_crtc *crtc = state->base.crtc;
	काष्ठा drm_color_lut *lut;
	पूर्णांक idx;

	अगर (!crtc || !crtc->state)
		वापस;

	अगर (!crtc->state->color_mgmt_changed || !crtc->state->gamma_lut)
		वापस;

	lut = (काष्ठा drm_color_lut *)crtc->state->gamma_lut->data;

	क्रम (idx = 0; idx < ATMEL_HLCDC_CLUT_SIZE; idx++, lut++) अणु
		u32 val = ((lut->red << 8) & 0xff0000) |
			(lut->green & 0xff00) |
			(lut->blue >> 8);

		aपंचांगel_hlcdc_layer_ग_लिखो_clut(&plane->layer, idx, val);
	पूर्ण
पूर्ण

अटल व्योम aपंचांगel_hlcdc_plane_update_buffers(काष्ठा aपंचांगel_hlcdc_plane *plane,
					काष्ठा aपंचांगel_hlcdc_plane_state *state)
अणु
	स्थिर काष्ठा aपंचांगel_hlcdc_layer_desc *desc = plane->layer.desc;
	काष्ठा drm_framebuffer *fb = state->base.fb;
	u32 sr;
	पूर्णांक i;

	sr = aपंचांगel_hlcdc_layer_पढ़ो_reg(&plane->layer, ATMEL_HLCDC_LAYER_CHSR);

	क्रम (i = 0; i < state->nplanes; i++) अणु
		काष्ठा drm_gem_cma_object *gem = drm_fb_cma_get_gem_obj(fb, i);

		state->dscrs[i]->addr = gem->paddr + state->offsets[i];

		aपंचांगel_hlcdc_layer_ग_लिखो_reg(&plane->layer,
					    ATMEL_HLCDC_LAYER_PLANE_HEAD(i),
					    state->dscrs[i]->self);

		अगर (!(sr & ATMEL_HLCDC_LAYER_EN)) अणु
			aपंचांगel_hlcdc_layer_ग_लिखो_reg(&plane->layer,
					ATMEL_HLCDC_LAYER_PLANE_ADDR(i),
					state->dscrs[i]->addr);
			aपंचांगel_hlcdc_layer_ग_लिखो_reg(&plane->layer,
					ATMEL_HLCDC_LAYER_PLANE_CTRL(i),
					state->dscrs[i]->ctrl);
			aपंचांगel_hlcdc_layer_ग_लिखो_reg(&plane->layer,
					ATMEL_HLCDC_LAYER_PLANE_NEXT(i),
					state->dscrs[i]->self);
		पूर्ण

		अगर (desc->layout.xstride[i])
			aपंचांगel_hlcdc_layer_ग_लिखो_cfg(&plane->layer,
						    desc->layout.xstride[i],
						    state->xstride[i]);

		अगर (desc->layout.pstride[i])
			aपंचांगel_hlcdc_layer_ग_लिखो_cfg(&plane->layer,
						    desc->layout.pstride[i],
						    state->pstride[i]);
	पूर्ण
पूर्ण

पूर्णांक aपंचांगel_hlcdc_plane_prepare_ahb_routing(काष्ठा drm_crtc_state *c_state)
अणु
	अचिन्हित पूर्णांक ahb_load[2] = अणु पूर्ण;
	काष्ठा drm_plane *plane;

	drm_atomic_crtc_state_क्रम_each_plane(plane, c_state) अणु
		काष्ठा aपंचांगel_hlcdc_plane_state *plane_state;
		काष्ठा drm_plane_state *plane_s;
		अचिन्हित पूर्णांक pixels, load = 0;
		पूर्णांक i;

		plane_s = drm_atomic_get_plane_state(c_state->state, plane);
		अगर (IS_ERR(plane_s))
			वापस PTR_ERR(plane_s);

		plane_state =
			drm_plane_state_to_aपंचांगel_hlcdc_plane_state(plane_s);

		pixels = (plane_state->src_w * plane_state->src_h) -
			 (plane_state->disc_w * plane_state->disc_h);

		क्रम (i = 0; i < plane_state->nplanes; i++)
			load += pixels * plane_state->bpp[i];

		अगर (ahb_load[0] <= ahb_load[1])
			plane_state->ahb_id = 0;
		अन्यथा
			plane_state->ahb_id = 1;

		ahb_load[plane_state->ahb_id] += load;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक
aपंचांगel_hlcdc_plane_prepare_disc_area(काष्ठा drm_crtc_state *c_state)
अणु
	पूर्णांक disc_x = 0, disc_y = 0, disc_w = 0, disc_h = 0;
	स्थिर काष्ठा aपंचांगel_hlcdc_layer_cfg_layout *layout;
	काष्ठा aपंचांगel_hlcdc_plane_state *primary_state;
	काष्ठा drm_plane_state *primary_s;
	काष्ठा aपंचांगel_hlcdc_plane *primary;
	काष्ठा drm_plane *ovl;

	primary = drm_plane_to_aपंचांगel_hlcdc_plane(c_state->crtc->primary);
	layout = &primary->layer.desc->layout;
	अगर (!layout->disc_pos || !layout->disc_size)
		वापस 0;

	primary_s = drm_atomic_get_plane_state(c_state->state,
					       &primary->base);
	अगर (IS_ERR(primary_s))
		वापस PTR_ERR(primary_s);

	primary_state = drm_plane_state_to_aपंचांगel_hlcdc_plane_state(primary_s);

	drm_atomic_crtc_state_क्रम_each_plane(ovl, c_state) अणु
		काष्ठा aपंचांगel_hlcdc_plane_state *ovl_state;
		काष्ठा drm_plane_state *ovl_s;

		अगर (ovl == c_state->crtc->primary)
			जारी;

		ovl_s = drm_atomic_get_plane_state(c_state->state, ovl);
		अगर (IS_ERR(ovl_s))
			वापस PTR_ERR(ovl_s);

		ovl_state = drm_plane_state_to_aपंचांगel_hlcdc_plane_state(ovl_s);

		अगर (!ovl_s->visible ||
		    !ovl_s->fb ||
		    ovl_s->fb->क्रमmat->has_alpha ||
		    ovl_s->alpha != DRM_BLEND_ALPHA_OPAQUE)
			जारी;

		/* TODO: implement a smarter hidden area detection */
		अगर (ovl_state->crtc_h * ovl_state->crtc_w < disc_h * disc_w)
			जारी;

		disc_x = ovl_state->crtc_x;
		disc_y = ovl_state->crtc_y;
		disc_h = ovl_state->crtc_h;
		disc_w = ovl_state->crtc_w;
	पूर्ण

	primary_state->disc_x = disc_x;
	primary_state->disc_y = disc_y;
	primary_state->disc_w = disc_w;
	primary_state->disc_h = disc_h;

	वापस 0;
पूर्ण

अटल व्योम
aपंचांगel_hlcdc_plane_update_disc_area(काष्ठा aपंचांगel_hlcdc_plane *plane,
				   काष्ठा aपंचांगel_hlcdc_plane_state *state)
अणु
	स्थिर काष्ठा aपंचांगel_hlcdc_layer_cfg_layout *layout;

	layout = &plane->layer.desc->layout;
	अगर (!layout->disc_pos || !layout->disc_size)
		वापस;

	aपंचांगel_hlcdc_layer_ग_लिखो_cfg(&plane->layer, layout->disc_pos,
				ATMEL_HLCDC_LAYER_DISC_POS(state->disc_x,
							   state->disc_y));

	aपंचांगel_hlcdc_layer_ग_लिखो_cfg(&plane->layer, layout->disc_size,
				ATMEL_HLCDC_LAYER_DISC_SIZE(state->disc_w,
							    state->disc_h));
पूर्ण

अटल पूर्णांक aपंचांगel_hlcdc_plane_atomic_check(काष्ठा drm_plane *p,
					  काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *s = drm_atomic_get_new_plane_state(state, p);
	काष्ठा aपंचांगel_hlcdc_plane *plane = drm_plane_to_aपंचांगel_hlcdc_plane(p);
	काष्ठा aपंचांगel_hlcdc_plane_state *hstate =
				drm_plane_state_to_aपंचांगel_hlcdc_plane_state(s);
	स्थिर काष्ठा aपंचांगel_hlcdc_layer_desc *desc = plane->layer.desc;
	काष्ठा drm_framebuffer *fb = hstate->base.fb;
	स्थिर काष्ठा drm_display_mode *mode;
	काष्ठा drm_crtc_state *crtc_state;
	पूर्णांक ret;
	पूर्णांक i;

	अगर (!hstate->base.crtc || WARN_ON(!fb))
		वापस 0;

	crtc_state = drm_atomic_get_existing_crtc_state(state, s->crtc);
	mode = &crtc_state->adjusted_mode;

	ret = drm_atomic_helper_check_plane_state(s, crtc_state,
						  (1 << 16) / 2048,
						  पूर्णांक_उच्च, true, true);
	अगर (ret || !s->visible)
		वापस ret;

	hstate->src_x = s->src.x1;
	hstate->src_y = s->src.y1;
	hstate->src_w = drm_rect_width(&s->src);
	hstate->src_h = drm_rect_height(&s->src);
	hstate->crtc_x = s->dst.x1;
	hstate->crtc_y = s->dst.y1;
	hstate->crtc_w = drm_rect_width(&s->dst);
	hstate->crtc_h = drm_rect_height(&s->dst);

	अगर ((hstate->src_x | hstate->src_y | hstate->src_w | hstate->src_h) &
	    SUBPIXEL_MASK)
		वापस -EINVAL;

	hstate->src_x >>= 16;
	hstate->src_y >>= 16;
	hstate->src_w >>= 16;
	hstate->src_h >>= 16;

	hstate->nplanes = fb->क्रमmat->num_planes;
	अगर (hstate->nplanes > ATMEL_HLCDC_LAYER_MAX_PLANES)
		वापस -EINVAL;

	क्रम (i = 0; i < hstate->nplanes; i++) अणु
		अचिन्हित पूर्णांक offset = 0;
		पूर्णांक xभाग = i ? fb->क्रमmat->hsub : 1;
		पूर्णांक yभाग = i ? fb->क्रमmat->vsub : 1;

		hstate->bpp[i] = fb->क्रमmat->cpp[i];
		अगर (!hstate->bpp[i])
			वापस -EINVAL;

		चयन (hstate->base.rotation & DRM_MODE_ROTATE_MASK) अणु
		हाल DRM_MODE_ROTATE_90:
			offset = (hstate->src_y / yभाग) *
				 fb->pitches[i];
			offset += ((hstate->src_x + hstate->src_w - 1) /
				   xभाग) * hstate->bpp[i];
			hstate->xstride[i] = -(((hstate->src_h - 1) / yभाग) *
					    fb->pitches[i]) -
					  (2 * hstate->bpp[i]);
			hstate->pstride[i] = fb->pitches[i] - hstate->bpp[i];
			अवरोध;
		हाल DRM_MODE_ROTATE_180:
			offset = ((hstate->src_y + hstate->src_h - 1) /
				  yभाग) * fb->pitches[i];
			offset += ((hstate->src_x + hstate->src_w - 1) /
				   xभाग) * hstate->bpp[i];
			hstate->xstride[i] = ((((hstate->src_w - 1) / xभाग) - 1) *
					   hstate->bpp[i]) - fb->pitches[i];
			hstate->pstride[i] = -2 * hstate->bpp[i];
			अवरोध;
		हाल DRM_MODE_ROTATE_270:
			offset = ((hstate->src_y + hstate->src_h - 1) /
				  yभाग) * fb->pitches[i];
			offset += (hstate->src_x / xभाग) * hstate->bpp[i];
			hstate->xstride[i] = ((hstate->src_h - 1) / yभाग) *
					  fb->pitches[i];
			hstate->pstride[i] = -fb->pitches[i] - hstate->bpp[i];
			अवरोध;
		हाल DRM_MODE_ROTATE_0:
		शेष:
			offset = (hstate->src_y / yभाग) * fb->pitches[i];
			offset += (hstate->src_x / xभाग) * hstate->bpp[i];
			hstate->xstride[i] = fb->pitches[i] -
					  ((hstate->src_w / xभाग) *
					   hstate->bpp[i]);
			hstate->pstride[i] = 0;
			अवरोध;
		पूर्ण

		hstate->offsets[i] = offset + fb->offsets[i];
	पूर्ण

	/*
	 * Swap width and size in हाल of 90 or 270 degrees rotation
	 */
	अगर (drm_rotation_90_or_270(hstate->base.rotation)) अणु
		swap(hstate->src_w, hstate->src_h);
	पूर्ण

	अगर (!desc->layout.size &&
	    (mode->hdisplay != hstate->crtc_w ||
	     mode->vdisplay != hstate->crtc_h))
		वापस -EINVAL;

	अगर ((hstate->crtc_h != hstate->src_h || hstate->crtc_w != hstate->src_w) &&
	    (!desc->layout.memsize ||
	     hstate->base.fb->क्रमmat->has_alpha))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल व्योम aपंचांगel_hlcdc_plane_atomic_disable(काष्ठा drm_plane *p,
					     काष्ठा drm_atomic_state *state)
अणु
	काष्ठा aपंचांगel_hlcdc_plane *plane = drm_plane_to_aपंचांगel_hlcdc_plane(p);

	/* Disable पूर्णांकerrupts */
	aपंचांगel_hlcdc_layer_ग_लिखो_reg(&plane->layer, ATMEL_HLCDC_LAYER_IDR,
				    0xffffffff);

	/* Disable the layer */
	aपंचांगel_hlcdc_layer_ग_लिखो_reg(&plane->layer, ATMEL_HLCDC_LAYER_CHDR,
				    ATMEL_HLCDC_LAYER_RST |
				    ATMEL_HLCDC_LAYER_A2Q |
				    ATMEL_HLCDC_LAYER_UPDATE);

	/* Clear all pending पूर्णांकerrupts */
	aपंचांगel_hlcdc_layer_पढ़ो_reg(&plane->layer, ATMEL_HLCDC_LAYER_ISR);
पूर्ण

अटल व्योम aपंचांगel_hlcdc_plane_atomic_update(काष्ठा drm_plane *p,
					    काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *new_s = drm_atomic_get_new_plane_state(state,
								       p);
	काष्ठा aपंचांगel_hlcdc_plane *plane = drm_plane_to_aपंचांगel_hlcdc_plane(p);
	काष्ठा aपंचांगel_hlcdc_plane_state *hstate =
			drm_plane_state_to_aपंचांगel_hlcdc_plane_state(new_s);
	u32 sr;

	अगर (!new_s->crtc || !new_s->fb)
		वापस;

	अगर (!hstate->base.visible) अणु
		aपंचांगel_hlcdc_plane_atomic_disable(p, state);
		वापस;
	पूर्ण

	aपंचांगel_hlcdc_plane_update_pos_and_size(plane, hstate);
	aपंचांगel_hlcdc_plane_update_general_settings(plane, hstate);
	aपंचांगel_hlcdc_plane_update_क्रमmat(plane, hstate);
	aपंचांगel_hlcdc_plane_update_clut(plane, hstate);
	aपंचांगel_hlcdc_plane_update_buffers(plane, hstate);
	aपंचांगel_hlcdc_plane_update_disc_area(plane, hstate);

	/* Enable the overrun पूर्णांकerrupts. */
	aपंचांगel_hlcdc_layer_ग_लिखो_reg(&plane->layer, ATMEL_HLCDC_LAYER_IER,
				    ATMEL_HLCDC_LAYER_OVR_IRQ(0) |
				    ATMEL_HLCDC_LAYER_OVR_IRQ(1) |
				    ATMEL_HLCDC_LAYER_OVR_IRQ(2));

	/* Apply the new config at the next SOF event. */
	sr = aपंचांगel_hlcdc_layer_पढ़ो_reg(&plane->layer, ATMEL_HLCDC_LAYER_CHSR);
	aपंचांगel_hlcdc_layer_ग_लिखो_reg(&plane->layer, ATMEL_HLCDC_LAYER_CHER,
			ATMEL_HLCDC_LAYER_UPDATE |
			(sr & ATMEL_HLCDC_LAYER_EN ?
			 ATMEL_HLCDC_LAYER_A2Q : ATMEL_HLCDC_LAYER_EN));
पूर्ण

अटल पूर्णांक aपंचांगel_hlcdc_plane_init_properties(काष्ठा aपंचांगel_hlcdc_plane *plane)
अणु
	स्थिर काष्ठा aपंचांगel_hlcdc_layer_desc *desc = plane->layer.desc;

	अगर (desc->type == ATMEL_HLCDC_OVERLAY_LAYER ||
	    desc->type == ATMEL_HLCDC_CURSOR_LAYER) अणु
		पूर्णांक ret;

		ret = drm_plane_create_alpha_property(&plane->base);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (desc->layout.xstride[0] && desc->layout.pstride[0]) अणु
		पूर्णांक ret;

		ret = drm_plane_create_rotation_property(&plane->base,
							 DRM_MODE_ROTATE_0,
							 DRM_MODE_ROTATE_0 |
							 DRM_MODE_ROTATE_90 |
							 DRM_MODE_ROTATE_180 |
							 DRM_MODE_ROTATE_270);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (desc->layout.csc) अणु
		/*
		 * TODO: decare a "yuv-to-rgb-conv-factors" property to let
		 * userspace modअगरy these factors (using a BLOB property ?).
		 */
		aपंचांगel_hlcdc_layer_ग_लिखो_cfg(&plane->layer,
					    desc->layout.csc,
					    0x4c900091);
		aपंचांगel_hlcdc_layer_ग_लिखो_cfg(&plane->layer,
					    desc->layout.csc + 1,
					    0x7a5f5090);
		aपंचांगel_hlcdc_layer_ग_लिखो_cfg(&plane->layer,
					    desc->layout.csc + 2,
					    0x40040890);
	पूर्ण

	वापस 0;
पूर्ण

व्योम aपंचांगel_hlcdc_plane_irq(काष्ठा aपंचांगel_hlcdc_plane *plane)
अणु
	स्थिर काष्ठा aपंचांगel_hlcdc_layer_desc *desc = plane->layer.desc;
	u32 isr;

	isr = aपंचांगel_hlcdc_layer_पढ़ो_reg(&plane->layer, ATMEL_HLCDC_LAYER_ISR);

	/*
	 * There's not much we can करो in हाल of overrun except inक्रमming
	 * the user. However, we are in पूर्णांकerrupt context here, hence the
	 * use of dev_dbg().
	 */
	अगर (isr &
	    (ATMEL_HLCDC_LAYER_OVR_IRQ(0) | ATMEL_HLCDC_LAYER_OVR_IRQ(1) |
	     ATMEL_HLCDC_LAYER_OVR_IRQ(2)))
		dev_dbg(plane->base.dev->dev, "overrun on plane %s\n",
			desc->name);
पूर्ण

अटल स्थिर काष्ठा drm_plane_helper_funcs aपंचांगel_hlcdc_layer_plane_helper_funcs = अणु
	.atomic_check = aपंचांगel_hlcdc_plane_atomic_check,
	.atomic_update = aपंचांगel_hlcdc_plane_atomic_update,
	.atomic_disable = aपंचांगel_hlcdc_plane_atomic_disable,
पूर्ण;

अटल पूर्णांक aपंचांगel_hlcdc_plane_alloc_dscrs(काष्ठा drm_plane *p,
					 काष्ठा aपंचांगel_hlcdc_plane_state *state)
अणु
	काष्ठा aपंचांगel_hlcdc_dc *dc = p->dev->dev_निजी;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(state->dscrs); i++) अणु
		काष्ठा aपंचांगel_hlcdc_dma_channel_dscr *dscr;
		dma_addr_t dscr_dma;

		dscr = dma_pool_alloc(dc->dscrpool, GFP_KERNEL, &dscr_dma);
		अगर (!dscr)
			जाओ err;

		dscr->addr = 0;
		dscr->next = dscr_dma;
		dscr->self = dscr_dma;
		dscr->ctrl = ATMEL_HLCDC_LAYER_DFETCH;

		state->dscrs[i] = dscr;
	पूर्ण

	वापस 0;

err:
	क्रम (i--; i >= 0; i--) अणु
		dma_pool_मुक्त(dc->dscrpool, state->dscrs[i],
			      state->dscrs[i]->self);
	पूर्ण

	वापस -ENOMEM;
पूर्ण

अटल व्योम aपंचांगel_hlcdc_plane_reset(काष्ठा drm_plane *p)
अणु
	काष्ठा aपंचांगel_hlcdc_plane_state *state;

	अगर (p->state) अणु
		state = drm_plane_state_to_aपंचांगel_hlcdc_plane_state(p->state);

		अगर (state->base.fb)
			drm_framebuffer_put(state->base.fb);

		kमुक्त(state);
		p->state = शून्य;
	पूर्ण

	state = kzalloc(माप(*state), GFP_KERNEL);
	अगर (state) अणु
		अगर (aपंचांगel_hlcdc_plane_alloc_dscrs(p, state)) अणु
			kमुक्त(state);
			dev_err(p->dev->dev,
				"Failed to allocate initial plane state\n");
			वापस;
		पूर्ण
		__drm_atomic_helper_plane_reset(p, &state->base);
	पूर्ण
पूर्ण

अटल काष्ठा drm_plane_state *
aपंचांगel_hlcdc_plane_atomic_duplicate_state(काष्ठा drm_plane *p)
अणु
	काष्ठा aपंचांगel_hlcdc_plane_state *state =
			drm_plane_state_to_aपंचांगel_hlcdc_plane_state(p->state);
	काष्ठा aपंचांगel_hlcdc_plane_state *copy;

	copy = kmemdup(state, माप(*state), GFP_KERNEL);
	अगर (!copy)
		वापस शून्य;

	अगर (aपंचांगel_hlcdc_plane_alloc_dscrs(p, copy)) अणु
		kमुक्त(copy);
		वापस शून्य;
	पूर्ण

	अगर (copy->base.fb)
		drm_framebuffer_get(copy->base.fb);

	वापस &copy->base;
पूर्ण

अटल व्योम aपंचांगel_hlcdc_plane_atomic_destroy_state(काष्ठा drm_plane *p,
						   काष्ठा drm_plane_state *s)
अणु
	काष्ठा aपंचांगel_hlcdc_plane_state *state =
			drm_plane_state_to_aपंचांगel_hlcdc_plane_state(s);
	काष्ठा aपंचांगel_hlcdc_dc *dc = p->dev->dev_निजी;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(state->dscrs); i++) अणु
		dma_pool_मुक्त(dc->dscrpool, state->dscrs[i],
			      state->dscrs[i]->self);
	पूर्ण

	अगर (s->fb)
		drm_framebuffer_put(s->fb);

	kमुक्त(state);
पूर्ण

अटल स्थिर काष्ठा drm_plane_funcs layer_plane_funcs = अणु
	.update_plane = drm_atomic_helper_update_plane,
	.disable_plane = drm_atomic_helper_disable_plane,
	.destroy = drm_plane_cleanup,
	.reset = aपंचांगel_hlcdc_plane_reset,
	.atomic_duplicate_state = aपंचांगel_hlcdc_plane_atomic_duplicate_state,
	.atomic_destroy_state = aपंचांगel_hlcdc_plane_atomic_destroy_state,
पूर्ण;

अटल पूर्णांक aपंचांगel_hlcdc_plane_create(काष्ठा drm_device *dev,
				    स्थिर काष्ठा aपंचांगel_hlcdc_layer_desc *desc)
अणु
	काष्ठा aपंचांगel_hlcdc_dc *dc = dev->dev_निजी;
	काष्ठा aपंचांगel_hlcdc_plane *plane;
	क्रमागत drm_plane_type type;
	पूर्णांक ret;

	plane = devm_kzalloc(dev->dev, माप(*plane), GFP_KERNEL);
	अगर (!plane)
		वापस -ENOMEM;

	aपंचांगel_hlcdc_layer_init(&plane->layer, desc, dc->hlcdc->regmap);

	अगर (desc->type == ATMEL_HLCDC_BASE_LAYER)
		type = DRM_PLANE_TYPE_PRIMARY;
	अन्यथा अगर (desc->type == ATMEL_HLCDC_CURSOR_LAYER)
		type = DRM_PLANE_TYPE_CURSOR;
	अन्यथा
		type = DRM_PLANE_TYPE_OVERLAY;

	ret = drm_universal_plane_init(dev, &plane->base, 0,
				       &layer_plane_funcs,
				       desc->क्रमmats->क्रमmats,
				       desc->क्रमmats->nक्रमmats,
				       शून्य, type, शून्य);
	अगर (ret)
		वापस ret;

	drm_plane_helper_add(&plane->base,
			     &aपंचांगel_hlcdc_layer_plane_helper_funcs);

	/* Set शेष property values*/
	ret = aपंचांगel_hlcdc_plane_init_properties(plane);
	अगर (ret)
		वापस ret;

	dc->layers[desc->id] = &plane->layer;

	वापस 0;
पूर्ण

पूर्णांक aपंचांगel_hlcdc_create_planes(काष्ठा drm_device *dev)
अणु
	काष्ठा aपंचांगel_hlcdc_dc *dc = dev->dev_निजी;
	स्थिर काष्ठा aपंचांगel_hlcdc_layer_desc *descs = dc->desc->layers;
	पूर्णांक nlayers = dc->desc->nlayers;
	पूर्णांक i, ret;

	dc->dscrpool = dmam_pool_create("atmel-hlcdc-dscr", dev->dev,
				माप(काष्ठा aपंचांगel_hlcdc_dma_channel_dscr),
				माप(u64), 0);
	अगर (!dc->dscrpool)
		वापस -ENOMEM;

	क्रम (i = 0; i < nlayers; i++) अणु
		अगर (descs[i].type != ATMEL_HLCDC_BASE_LAYER &&
		    descs[i].type != ATMEL_HLCDC_OVERLAY_LAYER &&
		    descs[i].type != ATMEL_HLCDC_CURSOR_LAYER)
			जारी;

		ret = aपंचांगel_hlcdc_plane_create(dev, &descs[i]);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
