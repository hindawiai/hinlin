<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2017 Free Electrons
 * Maxime Ripard <maxime.ripard@मुक्त-electrons.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/component.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/reset.h>

#समावेश <drm/drm_device.h>
#समावेश <drm/drm_fb_cma_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_framebuffer.h>
#समावेश <drm/drm_gem_cma_helper.h>
#समावेश <drm/drm_plane.h>

#समावेश "sun4i_drv.h"
#समावेश "sun4i_frontend.h"

अटल स्थिर u32 sun4i_frontend_vert_coef[32] = अणु
	0x00004000, 0x000140ff, 0x00033ffe, 0x00043ffd,
	0x00063efc, 0xff083dfc, 0x000a3bfb, 0xff0d39fb,
	0xff0f37fb, 0xff1136fa, 0xfe1433fb, 0xfe1631fb,
	0xfd192ffb, 0xfd1c2cfb, 0xfd1f29fb, 0xfc2127fc,
	0xfc2424fc, 0xfc2721fc, 0xfb291ffd, 0xfb2c1cfd,
	0xfb2f19fd, 0xfb3116fe, 0xfb3314fe, 0xfa3611ff,
	0xfb370fff, 0xfb390dff, 0xfb3b0a00, 0xfc3d08ff,
	0xfc3e0600, 0xfd3f0400, 0xfe3f0300, 0xff400100,
पूर्ण;

अटल स्थिर u32 sun4i_frontend_horz_coef[64] = अणु
	0x40000000, 0x00000000, 0x40fe0000, 0x0000ff03,
	0x3ffd0000, 0x0000ff05, 0x3ffc0000, 0x0000ff06,
	0x3efb0000, 0x0000ff08, 0x3dfb0000, 0x0000ff09,
	0x3bfa0000, 0x0000fe0d, 0x39fa0000, 0x0000fe0f,
	0x38fa0000, 0x0000fe10, 0x36fa0000, 0x0000fe12,
	0x33fa0000, 0x0000fd16, 0x31fa0000, 0x0000fd18,
	0x2ffa0000, 0x0000fd1a, 0x2cfa0000, 0x0000fc1e,
	0x29fa0000, 0x0000fc21, 0x27fb0000, 0x0000fb23,
	0x24fb0000, 0x0000fb26, 0x21fb0000, 0x0000fb29,
	0x1ffc0000, 0x0000fa2b, 0x1cfc0000, 0x0000fa2e,
	0x19fd0000, 0x0000fa30, 0x16fd0000, 0x0000fa33,
	0x14fd0000, 0x0000fa35, 0x11fe0000, 0x0000fa37,
	0x0ffe0000, 0x0000fa39, 0x0dfe0000, 0x0000fa3b,
	0x0afe0000, 0x0000fa3e, 0x08ff0000, 0x0000fb3e,
	0x06ff0000, 0x0000fb40, 0x05ff0000, 0x0000fc40,
	0x03ff0000, 0x0000fd41, 0x01ff0000, 0x0000fe42,
पूर्ण;

/*
 * These coefficients are taken from the A33 BSP from Allwinner.
 *
 * The first three values of each row are coded as 13-bit चिन्हित fixed-poपूर्णांक
 * numbers, with 10 bits क्रम the fractional part. The fourth value is a
 * स्थिरant coded as a 14-bit चिन्हित fixed-poपूर्णांक number with 4 bits क्रम the
 * fractional part.
 *
 * The values in table order give the following colorspace translation:
 * G = 1.164 * Y - 0.391 * U - 0.813 * V + 135
 * R = 1.164 * Y + 1.596 * V - 222
 * B = 1.164 * Y + 2.018 * U + 276
 *
 * This seems to be a conversion from Y[16:235] UV[16:240] to RGB[0:255],
 * following the BT601 spec.
 */
स्थिर u32 sunxi_bt601_yuv2rgb_coef[12] = अणु
	0x000004a7, 0x00001e6f, 0x00001cbf, 0x00000877,
	0x000004a7, 0x00000000, 0x00000662, 0x00003211,
	0x000004a7, 0x00000812, 0x00000000, 0x00002eb1,
पूर्ण;
EXPORT_SYMBOL(sunxi_bt601_yuv2rgb_coef);

अटल व्योम sun4i_frontend_scaler_init(काष्ठा sun4i_frontend *frontend)
अणु
	पूर्णांक i;

	अगर (frontend->data->has_coef_access_ctrl)
		regmap_ग_लिखो_bits(frontend->regs, SUN4I_FRONTEND_FRM_CTRL_REG,
				  SUN4I_FRONTEND_FRM_CTRL_COEF_ACCESS_CTRL,
				  SUN4I_FRONTEND_FRM_CTRL_COEF_ACCESS_CTRL);

	क्रम (i = 0; i < 32; i++) अणु
		regmap_ग_लिखो(frontend->regs, SUN4I_FRONTEND_CH0_HORZCOEF0_REG(i),
			     sun4i_frontend_horz_coef[2 * i]);
		regmap_ग_लिखो(frontend->regs, SUN4I_FRONTEND_CH1_HORZCOEF0_REG(i),
			     sun4i_frontend_horz_coef[2 * i]);
		regmap_ग_लिखो(frontend->regs, SUN4I_FRONTEND_CH0_HORZCOEF1_REG(i),
			     sun4i_frontend_horz_coef[2 * i + 1]);
		regmap_ग_लिखो(frontend->regs, SUN4I_FRONTEND_CH1_HORZCOEF1_REG(i),
			     sun4i_frontend_horz_coef[2 * i + 1]);
		regmap_ग_लिखो(frontend->regs, SUN4I_FRONTEND_CH0_VERTCOEF_REG(i),
			     sun4i_frontend_vert_coef[i]);
		regmap_ग_लिखो(frontend->regs, SUN4I_FRONTEND_CH1_VERTCOEF_REG(i),
			     sun4i_frontend_vert_coef[i]);
	पूर्ण

	अगर (frontend->data->has_coef_rdy)
		regmap_ग_लिखो_bits(frontend->regs,
				  SUN4I_FRONTEND_FRM_CTRL_REG,
				  SUN4I_FRONTEND_FRM_CTRL_COEF_RDY,
				  SUN4I_FRONTEND_FRM_CTRL_COEF_RDY);
पूर्ण

पूर्णांक sun4i_frontend_init(काष्ठा sun4i_frontend *frontend)
अणु
	वापस pm_runसमय_get_sync(frontend->dev);
पूर्ण
EXPORT_SYMBOL(sun4i_frontend_init);

व्योम sun4i_frontend_निकास(काष्ठा sun4i_frontend *frontend)
अणु
	pm_runसमय_put(frontend->dev);
पूर्ण
EXPORT_SYMBOL(sun4i_frontend_निकास);

अटल bool sun4i_frontend_क्रमmat_chroma_requires_swap(uपूर्णांक32_t fmt)
अणु
	चयन (fmt) अणु
	हाल DRM_FORMAT_YVU411:
	हाल DRM_FORMAT_YVU420:
	हाल DRM_FORMAT_YVU422:
	हाल DRM_FORMAT_YVU444:
		वापस true;

	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool sun4i_frontend_क्रमmat_supports_tiling(uपूर्णांक32_t fmt)
अणु
	चयन (fmt) अणु
	हाल DRM_FORMAT_NV12:
	हाल DRM_FORMAT_NV16:
	हाल DRM_FORMAT_NV21:
	हाल DRM_FORMAT_NV61:
	हाल DRM_FORMAT_YUV411:
	हाल DRM_FORMAT_YUV420:
	हाल DRM_FORMAT_YUV422:
	हाल DRM_FORMAT_YVU420:
	हाल DRM_FORMAT_YVU422:
	हाल DRM_FORMAT_YVU411:
		वापस true;

	शेष:
		वापस false;
	पूर्ण
पूर्ण

व्योम sun4i_frontend_update_buffer(काष्ठा sun4i_frontend *frontend,
				  काष्ठा drm_plane *plane)
अणु
	काष्ठा drm_plane_state *state = plane->state;
	काष्ठा drm_framebuffer *fb = state->fb;
	अचिन्हित पूर्णांक strides[3] = अणुपूर्ण;

	dma_addr_t paddr;
	bool swap;

	अगर (fb->modअगरier == DRM_FORMAT_MOD_ALLWINNER_TILED) अणु
		अचिन्हित पूर्णांक width = state->src_w >> 16;
		अचिन्हित पूर्णांक offset;

		strides[0] = SUN4I_FRONTEND_LINESTRD_TILED(fb->pitches[0]);

		/*
		 * The X1 offset is the offset to the bottom-right poपूर्णांक in the
		 * end tile, which is the final pixel (at offset width - 1)
		 * within the end tile (with a 32-byte mask).
		 */
		offset = (width - 1) & (32 - 1);

		regmap_ग_लिखो(frontend->regs, SUN4I_FRONTEND_TB_OFF0_REG,
			     SUN4I_FRONTEND_TB_OFF_X1(offset));

		अगर (fb->क्रमmat->num_planes > 1) अणु
			strides[1] =
				SUN4I_FRONTEND_LINESTRD_TILED(fb->pitches[1]);

			regmap_ग_लिखो(frontend->regs, SUN4I_FRONTEND_TB_OFF1_REG,
				     SUN4I_FRONTEND_TB_OFF_X1(offset));
		पूर्ण

		अगर (fb->क्रमmat->num_planes > 2) अणु
			strides[2] =
				SUN4I_FRONTEND_LINESTRD_TILED(fb->pitches[2]);

			regmap_ग_लिखो(frontend->regs, SUN4I_FRONTEND_TB_OFF2_REG,
				     SUN4I_FRONTEND_TB_OFF_X1(offset));
		पूर्ण
	पूर्ण अन्यथा अणु
		strides[0] = fb->pitches[0];

		अगर (fb->क्रमmat->num_planes > 1)
			strides[1] = fb->pitches[1];

		अगर (fb->क्रमmat->num_planes > 2)
			strides[2] = fb->pitches[2];
	पूर्ण

	/* Set the line width */
	DRM_DEBUG_DRIVER("Frontend stride: %d bytes\n", fb->pitches[0]);
	regmap_ग_लिखो(frontend->regs, SUN4I_FRONTEND_LINESTRD0_REG,
		     strides[0]);

	अगर (fb->क्रमmat->num_planes > 1)
		regmap_ग_लिखो(frontend->regs, SUN4I_FRONTEND_LINESTRD1_REG,
			     strides[1]);

	अगर (fb->क्रमmat->num_planes > 2)
		regmap_ग_लिखो(frontend->regs, SUN4I_FRONTEND_LINESTRD2_REG,
			     strides[2]);

	/* Some planar क्रमmats require chroma channel swapping by hand. */
	swap = sun4i_frontend_क्रमmat_chroma_requires_swap(fb->क्रमmat->क्रमmat);

	/* Set the physical address of the buffer in memory */
	paddr = drm_fb_cma_get_gem_addr(fb, state, 0);
	paddr -= PHYS_OFFSET;
	DRM_DEBUG_DRIVER("Setting buffer #0 address to %pad\n", &paddr);
	regmap_ग_लिखो(frontend->regs, SUN4I_FRONTEND_BUF_ADDR0_REG, paddr);

	अगर (fb->क्रमmat->num_planes > 1) अणु
		paddr = drm_fb_cma_get_gem_addr(fb, state, swap ? 2 : 1);
		paddr -= PHYS_OFFSET;
		DRM_DEBUG_DRIVER("Setting buffer #1 address to %pad\n", &paddr);
		regmap_ग_लिखो(frontend->regs, SUN4I_FRONTEND_BUF_ADDR1_REG,
			     paddr);
	पूर्ण

	अगर (fb->क्रमmat->num_planes > 2) अणु
		paddr = drm_fb_cma_get_gem_addr(fb, state, swap ? 1 : 2);
		paddr -= PHYS_OFFSET;
		DRM_DEBUG_DRIVER("Setting buffer #2 address to %pad\n", &paddr);
		regmap_ग_लिखो(frontend->regs, SUN4I_FRONTEND_BUF_ADDR2_REG,
			     paddr);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(sun4i_frontend_update_buffer);

अटल पूर्णांक
sun4i_frontend_drm_क्रमmat_to_input_fmt(स्थिर काष्ठा drm_क्रमmat_info *क्रमmat,
				       u32 *val)
अणु
	अगर (!क्रमmat->is_yuv)
		*val = SUN4I_FRONTEND_INPUT_FMT_DATA_FMT_RGB;
	अन्यथा अगर (drm_क्रमmat_info_is_yuv_sampling_411(क्रमmat))
		*val = SUN4I_FRONTEND_INPUT_FMT_DATA_FMT_YUV411;
	अन्यथा अगर (drm_क्रमmat_info_is_yuv_sampling_420(क्रमmat))
		*val = SUN4I_FRONTEND_INPUT_FMT_DATA_FMT_YUV420;
	अन्यथा अगर (drm_क्रमmat_info_is_yuv_sampling_422(क्रमmat))
		*val = SUN4I_FRONTEND_INPUT_FMT_DATA_FMT_YUV422;
	अन्यथा अगर (drm_क्रमmat_info_is_yuv_sampling_444(क्रमmat))
		*val = SUN4I_FRONTEND_INPUT_FMT_DATA_FMT_YUV444;
	अन्यथा
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक
sun4i_frontend_drm_क्रमmat_to_input_mode(स्थिर काष्ठा drm_क्रमmat_info *क्रमmat,
					uपूर्णांक64_t modअगरier, u32 *val)
अणु
	bool tiled = (modअगरier == DRM_FORMAT_MOD_ALLWINNER_TILED);

	चयन (क्रमmat->num_planes) अणु
	हाल 1:
		*val = SUN4I_FRONTEND_INPUT_FMT_DATA_MOD_PACKED;
		वापस 0;

	हाल 2:
		*val = tiled ? SUN4I_FRONTEND_INPUT_FMT_DATA_MOD_MB32_SEMIPLANAR
			     : SUN4I_FRONTEND_INPUT_FMT_DATA_MOD_SEMIPLANAR;
		वापस 0;

	हाल 3:
		*val = tiled ? SUN4I_FRONTEND_INPUT_FMT_DATA_MOD_MB32_PLANAR
			     : SUN4I_FRONTEND_INPUT_FMT_DATA_MOD_PLANAR;
		वापस 0;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक
sun4i_frontend_drm_क्रमmat_to_input_sequence(स्थिर काष्ठा drm_क्रमmat_info *क्रमmat,
					    u32 *val)
अणु
	/* Planar क्रमmats have an explicit input sequence. */
	अगर (drm_क्रमmat_info_is_yuv_planar(क्रमmat)) अणु
		*val = 0;
		वापस 0;
	पूर्ण

	चयन (क्रमmat->क्रमmat) अणु
	हाल DRM_FORMAT_BGRX8888:
		*val = SUN4I_FRONTEND_INPUT_FMT_DATA_PS_BGRX;
		वापस 0;

	हाल DRM_FORMAT_NV12:
		*val = SUN4I_FRONTEND_INPUT_FMT_DATA_PS_UV;
		वापस 0;

	हाल DRM_FORMAT_NV16:
		*val = SUN4I_FRONTEND_INPUT_FMT_DATA_PS_UV;
		वापस 0;

	हाल DRM_FORMAT_NV21:
		*val = SUN4I_FRONTEND_INPUT_FMT_DATA_PS_VU;
		वापस 0;

	हाल DRM_FORMAT_NV61:
		*val = SUN4I_FRONTEND_INPUT_FMT_DATA_PS_VU;
		वापस 0;

	हाल DRM_FORMAT_UYVY:
		*val = SUN4I_FRONTEND_INPUT_FMT_DATA_PS_UYVY;
		वापस 0;

	हाल DRM_FORMAT_VYUY:
		*val = SUN4I_FRONTEND_INPUT_FMT_DATA_PS_VYUY;
		वापस 0;

	हाल DRM_FORMAT_XRGB8888:
		*val = SUN4I_FRONTEND_INPUT_FMT_DATA_PS_XRGB;
		वापस 0;

	हाल DRM_FORMAT_YUYV:
		*val = SUN4I_FRONTEND_INPUT_FMT_DATA_PS_YUYV;
		वापस 0;

	हाल DRM_FORMAT_YVYU:
		*val = SUN4I_FRONTEND_INPUT_FMT_DATA_PS_YVYU;
		वापस 0;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक sun4i_frontend_drm_क्रमmat_to_output_fmt(uपूर्णांक32_t fmt, u32 *val)
अणु
	चयन (fmt) अणु
	हाल DRM_FORMAT_BGRX8888:
		*val = SUN4I_FRONTEND_OUTPUT_FMT_DATA_FMT_BGRX8888;
		वापस 0;

	हाल DRM_FORMAT_XRGB8888:
		*val = SUN4I_FRONTEND_OUTPUT_FMT_DATA_FMT_XRGB8888;
		वापस 0;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर uपूर्णांक32_t sun4i_frontend_क्रमmats[] = अणु
	DRM_FORMAT_BGRX8888,
	DRM_FORMAT_NV12,
	DRM_FORMAT_NV16,
	DRM_FORMAT_NV21,
	DRM_FORMAT_NV61,
	DRM_FORMAT_UYVY,
	DRM_FORMAT_VYUY,
	DRM_FORMAT_XRGB8888,
	DRM_FORMAT_YUV411,
	DRM_FORMAT_YUV420,
	DRM_FORMAT_YUV422,
	DRM_FORMAT_YUV444,
	DRM_FORMAT_YUYV,
	DRM_FORMAT_YVU411,
	DRM_FORMAT_YVU420,
	DRM_FORMAT_YVU422,
	DRM_FORMAT_YVU444,
	DRM_FORMAT_YVYU,
पूर्ण;

bool sun4i_frontend_क्रमmat_is_supported(uपूर्णांक32_t fmt, uपूर्णांक64_t modअगरier)
अणु
	अचिन्हित पूर्णांक i;

	अगर (modअगरier == DRM_FORMAT_MOD_ALLWINNER_TILED)
		वापस sun4i_frontend_क्रमmat_supports_tiling(fmt);
	अन्यथा अगर (modअगरier != DRM_FORMAT_MOD_LINEAR)
		वापस false;

	क्रम (i = 0; i < ARRAY_SIZE(sun4i_frontend_क्रमmats); i++)
		अगर (sun4i_frontend_क्रमmats[i] == fmt)
			वापस true;

	वापस false;
पूर्ण
EXPORT_SYMBOL(sun4i_frontend_क्रमmat_is_supported);

पूर्णांक sun4i_frontend_update_क्रमmats(काष्ठा sun4i_frontend *frontend,
				  काष्ठा drm_plane *plane, uपूर्णांक32_t out_fmt)
अणु
	काष्ठा drm_plane_state *state = plane->state;
	काष्ठा drm_framebuffer *fb = state->fb;
	स्थिर काष्ठा drm_क्रमmat_info *क्रमmat = fb->क्रमmat;
	uपूर्णांक64_t modअगरier = fb->modअगरier;
	अचिन्हित पूर्णांक ch1_phase_idx;
	u32 out_fmt_val;
	u32 in_fmt_val, in_mod_val, in_ps_val;
	अचिन्हित पूर्णांक i;
	u32 bypass;
	पूर्णांक ret;

	ret = sun4i_frontend_drm_क्रमmat_to_input_fmt(क्रमmat, &in_fmt_val);
	अगर (ret) अणु
		DRM_DEBUG_DRIVER("Invalid input format\n");
		वापस ret;
	पूर्ण

	ret = sun4i_frontend_drm_क्रमmat_to_input_mode(क्रमmat, modअगरier,
						      &in_mod_val);
	अगर (ret) अणु
		DRM_DEBUG_DRIVER("Invalid input mode\n");
		वापस ret;
	पूर्ण

	ret = sun4i_frontend_drm_क्रमmat_to_input_sequence(क्रमmat, &in_ps_val);
	अगर (ret) अणु
		DRM_DEBUG_DRIVER("Invalid pixel sequence\n");
		वापस ret;
	पूर्ण

	ret = sun4i_frontend_drm_क्रमmat_to_output_fmt(out_fmt, &out_fmt_val);
	अगर (ret) अणु
		DRM_DEBUG_DRIVER("Invalid output format\n");
		वापस ret;
	पूर्ण

	/*
	 * I have no idea what this करोes exactly, but it seems to be
	 * related to the scaler FIR filter phase parameters.
	 */
	ch1_phase_idx = (क्रमmat->num_planes > 1) ? 1 : 0;
	regmap_ग_लिखो(frontend->regs, SUN4I_FRONTEND_CH0_HORZPHASE_REG,
		     frontend->data->ch_phase[0]);
	regmap_ग_लिखो(frontend->regs, SUN4I_FRONTEND_CH1_HORZPHASE_REG,
		     frontend->data->ch_phase[ch1_phase_idx]);
	regmap_ग_लिखो(frontend->regs, SUN4I_FRONTEND_CH0_VERTPHASE0_REG,
		     frontend->data->ch_phase[0]);
	regmap_ग_लिखो(frontend->regs, SUN4I_FRONTEND_CH1_VERTPHASE0_REG,
		     frontend->data->ch_phase[ch1_phase_idx]);
	regmap_ग_लिखो(frontend->regs, SUN4I_FRONTEND_CH0_VERTPHASE1_REG,
		     frontend->data->ch_phase[0]);
	regmap_ग_लिखो(frontend->regs, SUN4I_FRONTEND_CH1_VERTPHASE1_REG,
		     frontend->data->ch_phase[ch1_phase_idx]);

	/*
	 * Checking the input क्रमmat is sufficient since we currently only
	 * support RGB output क्रमmats to the backend. If YUV output क्रमmats
	 * ever get supported, an YUV input and output would require bypassing
	 * the CSC engine too.
	 */
	अगर (क्रमmat->is_yuv) अणु
		/* Setup the CSC engine क्रम YUV to RGB conversion. */
		bypass = 0;

		क्रम (i = 0; i < ARRAY_SIZE(sunxi_bt601_yuv2rgb_coef); i++)
			regmap_ग_लिखो(frontend->regs,
				     SUN4I_FRONTEND_CSC_COEF_REG(i),
				     sunxi_bt601_yuv2rgb_coef[i]);
	पूर्ण अन्यथा अणु
		bypass = SUN4I_FRONTEND_BYPASS_CSC_EN;
	पूर्ण

	regmap_update_bits(frontend->regs, SUN4I_FRONTEND_BYPASS_REG,
			   SUN4I_FRONTEND_BYPASS_CSC_EN, bypass);

	regmap_ग_लिखो(frontend->regs, SUN4I_FRONTEND_INPUT_FMT_REG,
		     in_mod_val | in_fmt_val | in_ps_val);

	/*
	 * TODO: It look like the A31 and A80 at least will need the
	 * bit 7 (ALPHA_EN) enabled when using a क्रमmat with alpha (so
	 * ARGB8888).
	 */
	regmap_ग_लिखो(frontend->regs, SUN4I_FRONTEND_OUTPUT_FMT_REG,
		     out_fmt_val);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(sun4i_frontend_update_क्रमmats);

व्योम sun4i_frontend_update_coord(काष्ठा sun4i_frontend *frontend,
				 काष्ठा drm_plane *plane)
अणु
	काष्ठा drm_plane_state *state = plane->state;
	काष्ठा drm_framebuffer *fb = state->fb;
	uपूर्णांक32_t luma_width, luma_height;
	uपूर्णांक32_t chroma_width, chroma_height;

	/* Set height and width */
	DRM_DEBUG_DRIVER("Frontend size W: %u H: %u\n",
			 state->crtc_w, state->crtc_h);

	luma_width = state->src_w >> 16;
	luma_height = state->src_h >> 16;

	chroma_width = DIV_ROUND_UP(luma_width, fb->क्रमmat->hsub);
	chroma_height = DIV_ROUND_UP(luma_height, fb->क्रमmat->vsub);

	regmap_ग_लिखो(frontend->regs, SUN4I_FRONTEND_CH0_INSIZE_REG,
		     SUN4I_FRONTEND_INSIZE(luma_height, luma_width));
	regmap_ग_लिखो(frontend->regs, SUN4I_FRONTEND_CH1_INSIZE_REG,
		     SUN4I_FRONTEND_INSIZE(chroma_height, chroma_width));

	regmap_ग_लिखो(frontend->regs, SUN4I_FRONTEND_CH0_OUTSIZE_REG,
		     SUN4I_FRONTEND_OUTSIZE(state->crtc_h, state->crtc_w));
	regmap_ग_लिखो(frontend->regs, SUN4I_FRONTEND_CH1_OUTSIZE_REG,
		     SUN4I_FRONTEND_OUTSIZE(state->crtc_h, state->crtc_w));

	regmap_ग_लिखो(frontend->regs, SUN4I_FRONTEND_CH0_HORZFACT_REG,
		     (luma_width << 16) / state->crtc_w);
	regmap_ग_लिखो(frontend->regs, SUN4I_FRONTEND_CH1_HORZFACT_REG,
		     (chroma_width << 16) / state->crtc_w);

	regmap_ग_लिखो(frontend->regs, SUN4I_FRONTEND_CH0_VERTFACT_REG,
		     (luma_height << 16) / state->crtc_h);
	regmap_ग_लिखो(frontend->regs, SUN4I_FRONTEND_CH1_VERTFACT_REG,
		     (chroma_height << 16) / state->crtc_h);

	regmap_ग_लिखो_bits(frontend->regs, SUN4I_FRONTEND_FRM_CTRL_REG,
			  SUN4I_FRONTEND_FRM_CTRL_REG_RDY,
			  SUN4I_FRONTEND_FRM_CTRL_REG_RDY);
पूर्ण
EXPORT_SYMBOL(sun4i_frontend_update_coord);

पूर्णांक sun4i_frontend_enable(काष्ठा sun4i_frontend *frontend)
अणु
	regmap_ग_लिखो_bits(frontend->regs, SUN4I_FRONTEND_FRM_CTRL_REG,
			  SUN4I_FRONTEND_FRM_CTRL_FRM_START,
			  SUN4I_FRONTEND_FRM_CTRL_FRM_START);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(sun4i_frontend_enable);

अटल स्थिर काष्ठा regmap_config sun4i_frontend_regmap_config = अणु
	.reg_bits	= 32,
	.val_bits	= 32,
	.reg_stride	= 4,
	.max_रेजिस्टर	= 0x0a14,
पूर्ण;

अटल पूर्णांक sun4i_frontend_bind(काष्ठा device *dev, काष्ठा device *master,
			 व्योम *data)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा sun4i_frontend *frontend;
	काष्ठा drm_device *drm = data;
	काष्ठा sun4i_drv *drv = drm->dev_निजी;
	काष्ठा resource *res;
	व्योम __iomem *regs;

	frontend = devm_kzalloc(dev, माप(*frontend), GFP_KERNEL);
	अगर (!frontend)
		वापस -ENOMEM;

	dev_set_drvdata(dev, frontend);
	frontend->dev = dev;
	frontend->node = dev->of_node;

	frontend->data = of_device_get_match_data(dev);
	अगर (!frontend->data)
		वापस -ENODEV;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	regs = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(regs))
		वापस PTR_ERR(regs);

	frontend->regs = devm_regmap_init_mmio(dev, regs,
					       &sun4i_frontend_regmap_config);
	अगर (IS_ERR(frontend->regs)) अणु
		dev_err(dev, "Couldn't create the frontend regmap\n");
		वापस PTR_ERR(frontend->regs);
	पूर्ण

	frontend->reset = devm_reset_control_get(dev, शून्य);
	अगर (IS_ERR(frontend->reset)) अणु
		dev_err(dev, "Couldn't get our reset line\n");
		वापस PTR_ERR(frontend->reset);
	पूर्ण

	frontend->bus_clk = devm_clk_get(dev, "ahb");
	अगर (IS_ERR(frontend->bus_clk)) अणु
		dev_err(dev, "Couldn't get our bus clock\n");
		वापस PTR_ERR(frontend->bus_clk);
	पूर्ण

	frontend->mod_clk = devm_clk_get(dev, "mod");
	अगर (IS_ERR(frontend->mod_clk)) अणु
		dev_err(dev, "Couldn't get our mod clock\n");
		वापस PTR_ERR(frontend->mod_clk);
	पूर्ण

	frontend->ram_clk = devm_clk_get(dev, "ram");
	अगर (IS_ERR(frontend->ram_clk)) अणु
		dev_err(dev, "Couldn't get our ram clock\n");
		वापस PTR_ERR(frontend->ram_clk);
	पूर्ण

	list_add_tail(&frontend->list, &drv->frontend_list);
	pm_runसमय_enable(dev);

	वापस 0;
पूर्ण

अटल व्योम sun4i_frontend_unbind(काष्ठा device *dev, काष्ठा device *master,
			    व्योम *data)
अणु
	काष्ठा sun4i_frontend *frontend = dev_get_drvdata(dev);

	list_del(&frontend->list);
	pm_runसमय_क्रमce_suspend(dev);
पूर्ण

अटल स्थिर काष्ठा component_ops sun4i_frontend_ops = अणु
	.bind	= sun4i_frontend_bind,
	.unbind	= sun4i_frontend_unbind,
पूर्ण;

अटल पूर्णांक sun4i_frontend_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस component_add(&pdev->dev, &sun4i_frontend_ops);
पूर्ण

अटल पूर्णांक sun4i_frontend_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	component_del(&pdev->dev, &sun4i_frontend_ops);

	वापस 0;
पूर्ण

अटल पूर्णांक sun4i_frontend_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा sun4i_frontend *frontend = dev_get_drvdata(dev);
	पूर्णांक ret;

	clk_set_rate(frontend->mod_clk, 300000000);

	clk_prepare_enable(frontend->bus_clk);
	clk_prepare_enable(frontend->mod_clk);
	clk_prepare_enable(frontend->ram_clk);

	ret = reset_control_reset(frontend->reset);
	अगर (ret) अणु
		dev_err(dev, "Couldn't reset our device\n");
		वापस ret;
	पूर्ण

	regmap_update_bits(frontend->regs, SUN4I_FRONTEND_EN_REG,
			   SUN4I_FRONTEND_EN_EN,
			   SUN4I_FRONTEND_EN_EN);

	sun4i_frontend_scaler_init(frontend);

	वापस 0;
पूर्ण

अटल पूर्णांक sun4i_frontend_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा sun4i_frontend *frontend = dev_get_drvdata(dev);

	clk_disable_unprepare(frontend->ram_clk);
	clk_disable_unprepare(frontend->mod_clk);
	clk_disable_unprepare(frontend->bus_clk);

	reset_control_निश्चित(frontend->reset);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops sun4i_frontend_pm_ops = अणु
	.runसमय_resume		= sun4i_frontend_runसमय_resume,
	.runसमय_suspend	= sun4i_frontend_runसमय_suspend,
पूर्ण;

अटल स्थिर काष्ठा sun4i_frontend_data sun4i_a10_frontend = अणु
	.ch_phase		= अणु 0x000, 0xfc000 पूर्ण,
	.has_coef_rdy		= true,
पूर्ण;

अटल स्थिर काष्ठा sun4i_frontend_data sun8i_a33_frontend = अणु
	.ch_phase		= अणु 0x400, 0xfc400 पूर्ण,
	.has_coef_access_ctrl	= true,
पूर्ण;

स्थिर काष्ठा of_device_id sun4i_frontend_of_table[] = अणु
	अणु
		.compatible = "allwinner,sun4i-a10-display-frontend",
		.data = &sun4i_a10_frontend
	पूर्ण,
	अणु
		.compatible = "allwinner,sun7i-a20-display-frontend",
		.data = &sun4i_a10_frontend
	पूर्ण,
	अणु
		.compatible = "allwinner,sun8i-a23-display-frontend",
		.data = &sun8i_a33_frontend
	पूर्ण,
	अणु
		.compatible = "allwinner,sun8i-a33-display-frontend",
		.data = &sun8i_a33_frontend
	पूर्ण,
	अणु पूर्ण
पूर्ण;
EXPORT_SYMBOL(sun4i_frontend_of_table);
MODULE_DEVICE_TABLE(of, sun4i_frontend_of_table);

अटल काष्ठा platक्रमm_driver sun4i_frontend_driver = अणु
	.probe		= sun4i_frontend_probe,
	.हटाओ		= sun4i_frontend_हटाओ,
	.driver		= अणु
		.name		= "sun4i-frontend",
		.of_match_table	= sun4i_frontend_of_table,
		.pm		= &sun4i_frontend_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(sun4i_frontend_driver);

MODULE_AUTHOR("Maxime Ripard <maxime.ripard@free-electrons.com>");
MODULE_DESCRIPTION("Allwinner A10 Display Engine Frontend Driver");
MODULE_LICENSE("GPL");
