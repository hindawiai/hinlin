<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Ingenic JZ47xx IPU driver
//
// Copyright (C) 2020, Paul Cercueil <paul@crapouillou.net>
// Copyright (C) 2020, Daniel Silsby <dansilsby@gmail.com>

#समावेश "ingenic-drm.h"
#समावेश "ingenic-ipu.h"

#समावेश <linux/clk.h>
#समावेश <linux/component.h>
#समावेश <linux/gcd.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/समय.स>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_fb_cma_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_gem_atomic_helper.h>
#समावेश <drm/drm_plane.h>
#समावेश <drm/drm_plane_helper.h>
#समावेश <drm/drm_property.h>
#समावेश <drm/drm_vblank.h>

काष्ठा ingenic_ipu;

काष्ठा soc_info अणु
	स्थिर u32 *क्रमmats;
	माप_प्रकार num_क्रमmats;
	bool has_bicubic;
	bool manual_restart;

	व्योम (*set_coefs)(काष्ठा ingenic_ipu *ipu, अचिन्हित पूर्णांक reg,
			  अचिन्हित पूर्णांक sharpness, bool करोwnscale,
			  अचिन्हित पूर्णांक weight, अचिन्हित पूर्णांक offset);
पूर्ण;

काष्ठा ingenic_ipu अणु
	काष्ठा drm_plane plane;
	काष्ठा drm_device *drm;
	काष्ठा device *dev, *master;
	काष्ठा regmap *map;
	काष्ठा clk *clk;
	स्थिर काष्ठा soc_info *soc_info;
	bool clk_enabled;

	अचिन्हित पूर्णांक num_w, num_h, denom_w, denom_h;

	dma_addr_t addr_y, addr_u, addr_v;

	काष्ठा drm_property *sharpness_prop;
	अचिन्हित पूर्णांक sharpness;
पूर्ण;

/* Signed 15.16 fixed-poपूर्णांक math (क्रम bicubic scaling coefficients) */
#घोषणा I2F(i) ((s32)(i) * 65536)
#घोषणा F2I(f) ((f) / 65536)
#घोषणा FMUL(fa, fb) ((s32)(((s64)(fa) * (s64)(fb)) / 65536))
#घोषणा SHARPNESS_INCR (I2F(-1) / 8)

अटल अंतरभूत काष्ठा ingenic_ipu *plane_to_ingenic_ipu(काष्ठा drm_plane *plane)
अणु
	वापस container_of(plane, काष्ठा ingenic_ipu, plane);
पूर्ण

/*
 * Apply conventional cubic convolution kernel. Both parameters
 *  and वापस value are 15.16 चिन्हित fixed-poपूर्णांक.
 *
 *  @f_a: Sharpness factor, typically in range [-4.0, -0.25].
 *        A larger magnitude increases perceived sharpness, but going past
 *        -2.0 might cause ringing artअगरacts to outweigh any improvement.
 *        Nice values on a 320x240 LCD are between -0.75 and -2.0.
 *
 *  @f_x: Absolute distance in pixels from 'pixel 0' sample position
 *        aदीर्घ horizontal (or vertical) source axis. Range is [0, +2.0].
 *
 *  वापसs: Weight of this pixel within 4-pixel sample group. Range is
 *           [-2.0, +2.0]. For moderate (i.e. > -3.0) sharpness factors,
 *           range is within [-1.0, +1.0].
 */
अटल अंतरभूत s32 cubic_conv(s32 f_a, s32 f_x)
अणु
	स्थिर s32 f_1 = I2F(1);
	स्थिर s32 f_2 = I2F(2);
	स्थिर s32 f_3 = I2F(3);
	स्थिर s32 f_4 = I2F(4);
	स्थिर s32 f_x2 = FMUL(f_x, f_x);
	स्थिर s32 f_x3 = FMUL(f_x, f_x2);

	अगर (f_x <= f_1)
		वापस FMUL((f_a + f_2), f_x3) - FMUL((f_a + f_3), f_x2) + f_1;
	अन्यथा अगर (f_x <= f_2)
		वापस FMUL(f_a, (f_x3 - 5 * f_x2 + 8 * f_x - f_4));
	अन्यथा
		वापस 0;
पूर्ण

/*
 * On entry, "weight" is a coefficient suitable क्रम bilinear mode,
 *  which is converted to a set of four suitable क्रम bicubic mode.
 *
 * "weight 512" means all of pixel 0;
 * "weight 256" means half of pixel 0 and half of pixel 1;
 * "weight 0" means all of pixel 1;
 *
 * "offset" is increment to next source pixel sample location.
 */
अटल व्योम jz4760_set_coefs(काष्ठा ingenic_ipu *ipu, अचिन्हित पूर्णांक reg,
			     अचिन्हित पूर्णांक sharpness, bool करोwnscale,
			     अचिन्हित पूर्णांक weight, अचिन्हित पूर्णांक offset)
अणु
	u32 val;
	s32 w0, w1, w2, w3; /* Pixel weights at X (or Y) offsets -1,0,1,2 */

	weight = clamp_val(weight, 0, 512);

	अगर (sharpness < 2) अणु
		/*
		 *  When sharpness setting is 0, emulate nearest-neighbor.
		 *  When sharpness setting is 1, emulate bilinear.
		 */

		अगर (sharpness == 0)
			weight = weight >= 256 ? 512 : 0;
		w0 = 0;
		w1 = weight;
		w2 = 512 - weight;
		w3 = 0;
	पूर्ण अन्यथा अणु
		स्थिर s32 f_a = SHARPNESS_INCR * sharpness;
		स्थिर s32 f_h = I2F(1) / 2; /* Round up 0.5 */

		/*
		 * Note that always rounding towards +infinity here is पूर्णांकended.
		 * The resulting coefficients match a round-to-nearest-पूर्णांक
		 * द्विगुन भग्नing-poपूर्णांक implementation.
		 */

		weight = 512 - weight;
		w0 = F2I(f_h + 512 * cubic_conv(f_a, I2F(512  + weight) / 512));
		w1 = F2I(f_h + 512 * cubic_conv(f_a, I2F(0    + weight) / 512));
		w2 = F2I(f_h + 512 * cubic_conv(f_a, I2F(512  - weight) / 512));
		w3 = F2I(f_h + 512 * cubic_conv(f_a, I2F(1024 - weight) / 512));
		w0 = clamp_val(w0, -1024, 1023);
		w1 = clamp_val(w1, -1024, 1023);
		w2 = clamp_val(w2, -1024, 1023);
		w3 = clamp_val(w3, -1024, 1023);
	पूर्ण

	val = ((w1 & JZ4760_IPU_RSZ_COEF_MASK) << JZ4760_IPU_RSZ_COEF31_LSB) |
		((w0 & JZ4760_IPU_RSZ_COEF_MASK) << JZ4760_IPU_RSZ_COEF20_LSB);
	regmap_ग_लिखो(ipu->map, reg, val);

	val = ((w3 & JZ4760_IPU_RSZ_COEF_MASK) << JZ4760_IPU_RSZ_COEF31_LSB) |
		((w2 & JZ4760_IPU_RSZ_COEF_MASK) << JZ4760_IPU_RSZ_COEF20_LSB) |
		((offset & JZ4760_IPU_RSZ_OFFSET_MASK) << JZ4760_IPU_RSZ_OFFSET_LSB);
	regmap_ग_लिखो(ipu->map, reg, val);
पूर्ण

अटल व्योम jz4725b_set_coefs(काष्ठा ingenic_ipu *ipu, अचिन्हित पूर्णांक reg,
			      अचिन्हित पूर्णांक sharpness, bool करोwnscale,
			      अचिन्हित पूर्णांक weight, अचिन्हित पूर्णांक offset)
अणु
	u32 val = JZ4725B_IPU_RSZ_LUT_OUT_EN;
	अचिन्हित पूर्णांक i;

	weight = clamp_val(weight, 0, 512);

	अगर (sharpness == 0)
		weight = weight >= 256 ? 512 : 0;

	val |= (weight & JZ4725B_IPU_RSZ_LUT_COEF_MASK) << JZ4725B_IPU_RSZ_LUT_COEF_LSB;
	अगर (करोwnscale || !!offset)
		val |= JZ4725B_IPU_RSZ_LUT_IN_EN;

	regmap_ग_लिखो(ipu->map, reg, val);

	अगर (करोwnscale) अणु
		क्रम (i = 1; i < offset; i++)
			regmap_ग_लिखो(ipu->map, reg, JZ4725B_IPU_RSZ_LUT_IN_EN);
	पूर्ण
पूर्ण

अटल व्योम ingenic_ipu_set_करोwnscale_coefs(काष्ठा ingenic_ipu *ipu,
					    अचिन्हित पूर्णांक reg,
					    अचिन्हित पूर्णांक num,
					    अचिन्हित पूर्णांक denom)
अणु
	अचिन्हित पूर्णांक i, offset, weight, weight_num = denom;

	क्रम (i = 0; i < num; i++) अणु
		weight_num = num + (weight_num - num) % (num * 2);
		weight = 512 - 512 * (weight_num - num) / (num * 2);
		weight_num += denom * 2;
		offset = (weight_num - num) / (num * 2);

		ipu->soc_info->set_coefs(ipu, reg, ipu->sharpness,
					 true, weight, offset);
	पूर्ण
पूर्ण

अटल व्योम ingenic_ipu_set_पूर्णांकeger_upscale_coefs(काष्ठा ingenic_ipu *ipu,
						  अचिन्हित पूर्णांक reg,
						  अचिन्हित पूर्णांक num)
अणु
	/*
	 * Force nearest-neighbor scaling and use simple math when upscaling
	 * by an पूर्णांकeger ratio. It looks better, and fixes a few problem हालs.
	 */
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < num; i++)
		ipu->soc_info->set_coefs(ipu, reg, 0, false, 512, i == num - 1);
पूर्ण

अटल व्योम ingenic_ipu_set_upscale_coefs(काष्ठा ingenic_ipu *ipu,
					  अचिन्हित पूर्णांक reg,
					  अचिन्हित पूर्णांक num,
					  अचिन्हित पूर्णांक denom)
अणु
	अचिन्हित पूर्णांक i, offset, weight, weight_num = 0;

	क्रम (i = 0; i < num; i++) अणु
		weight = 512 - 512 * weight_num / num;
		weight_num += denom;
		offset = weight_num >= num;

		अगर (offset)
			weight_num -= num;

		ipu->soc_info->set_coefs(ipu, reg, ipu->sharpness,
					 false, weight, offset);
	पूर्ण
पूर्ण

अटल व्योम ingenic_ipu_set_coefs(काष्ठा ingenic_ipu *ipu, अचिन्हित पूर्णांक reg,
				  अचिन्हित पूर्णांक num, अचिन्हित पूर्णांक denom)
अणु
	/* Begin programming the LUT */
	regmap_ग_लिखो(ipu->map, reg, -1);

	अगर (denom > num)
		ingenic_ipu_set_करोwnscale_coefs(ipu, reg, num, denom);
	अन्यथा अगर (denom == 1)
		ingenic_ipu_set_पूर्णांकeger_upscale_coefs(ipu, reg, num);
	अन्यथा
		ingenic_ipu_set_upscale_coefs(ipu, reg, num, denom);
पूर्ण

अटल पूर्णांक reduce_fraction(अचिन्हित पूर्णांक *num, अचिन्हित पूर्णांक *denom)
अणु
	अचिन्हित दीर्घ d = gcd(*num, *denom);

	/* The scaling table has only 31 entries */
	अगर (*num > 31 * d)
		वापस -EINVAL;

	*num /= d;
	*denom /= d;
	वापस 0;
पूर्ण

अटल अंतरभूत bool osd_changed(काष्ठा drm_plane_state *state,
			       काष्ठा drm_plane_state *oldstate)
अणु
	वापस state->src_x != oldstate->src_x ||
		state->src_y != oldstate->src_y ||
		state->src_w != oldstate->src_w ||
		state->src_h != oldstate->src_h ||
		state->crtc_x != oldstate->crtc_x ||
		state->crtc_y != oldstate->crtc_y ||
		state->crtc_w != oldstate->crtc_w ||
		state->crtc_h != oldstate->crtc_h;
पूर्ण

अटल व्योम ingenic_ipu_plane_atomic_update(काष्ठा drm_plane *plane,
					    काष्ठा drm_atomic_state *state)
अणु
	काष्ठा ingenic_ipu *ipu = plane_to_ingenic_ipu(plane);
	काष्ठा drm_plane_state *newstate = drm_atomic_get_new_plane_state(state,
									  plane);
	स्थिर काष्ठा drm_क्रमmat_info *finfo;
	u32 ctrl, stride = 0, coef_index = 0, क्रमmat = 0;
	bool needs_modeset, upscaling_w, upscaling_h;
	पूर्णांक err;

	अगर (!newstate || !newstate->fb)
		वापस;

	finfo = drm_क्रमmat_info(newstate->fb->क्रमmat->क्रमmat);

	अगर (!ipu->clk_enabled) अणु
		err = clk_enable(ipu->clk);
		अगर (err) अणु
			dev_err(ipu->dev, "Unable to enable clock: %d\n", err);
			वापस;
		पूर्ण

		ipu->clk_enabled = true;
	पूर्ण

	/* Reset all the रेजिस्टरs अगर needed */
	needs_modeset = drm_atomic_crtc_needs_modeset(newstate->crtc->state);
	अगर (needs_modeset) अणु
		regmap_set_bits(ipu->map, JZ_REG_IPU_CTRL, JZ_IPU_CTRL_RST);

		/* Enable the chip */
		regmap_set_bits(ipu->map, JZ_REG_IPU_CTRL,
				JZ_IPU_CTRL_CHIP_EN | JZ_IPU_CTRL_LCDC_SEL);
	पूर्ण

	/* New addresses will be committed in vblank handler... */
	ipu->addr_y = drm_fb_cma_get_gem_addr(newstate->fb, newstate, 0);
	अगर (finfo->num_planes > 1)
		ipu->addr_u = drm_fb_cma_get_gem_addr(newstate->fb, newstate,
						      1);
	अगर (finfo->num_planes > 2)
		ipu->addr_v = drm_fb_cma_get_gem_addr(newstate->fb, newstate,
						      2);

	अगर (!needs_modeset)
		वापस;

	/* Or right here अगर we're करोing a full modeset. */
	regmap_ग_लिखो(ipu->map, JZ_REG_IPU_Y_ADDR, ipu->addr_y);
	regmap_ग_लिखो(ipu->map, JZ_REG_IPU_U_ADDR, ipu->addr_u);
	regmap_ग_लिखो(ipu->map, JZ_REG_IPU_V_ADDR, ipu->addr_v);

	अगर (finfo->num_planes == 1)
		regmap_set_bits(ipu->map, JZ_REG_IPU_CTRL, JZ_IPU_CTRL_SPKG_SEL);

	ingenic_drm_plane_config(ipu->master, plane, DRM_FORMAT_XRGB8888);

	/* Set the input height/width/strides */
	अगर (finfo->num_planes > 2)
		stride = ((newstate->src_w >> 16) * finfo->cpp[2] / finfo->hsub)
			<< JZ_IPU_UV_STRIDE_V_LSB;

	अगर (finfo->num_planes > 1)
		stride |= ((newstate->src_w >> 16) * finfo->cpp[1] / finfo->hsub)
			<< JZ_IPU_UV_STRIDE_U_LSB;

	regmap_ग_लिखो(ipu->map, JZ_REG_IPU_UV_STRIDE, stride);

	stride = ((newstate->src_w >> 16) * finfo->cpp[0]) << JZ_IPU_Y_STRIDE_Y_LSB;
	regmap_ग_लिखो(ipu->map, JZ_REG_IPU_Y_STRIDE, stride);

	regmap_ग_लिखो(ipu->map, JZ_REG_IPU_IN_GS,
		     (stride << JZ_IPU_IN_GS_W_LSB) |
		     ((newstate->src_h >> 16) << JZ_IPU_IN_GS_H_LSB));

	चयन (finfo->क्रमmat) अणु
	हाल DRM_FORMAT_XRGB1555:
		क्रमmat = JZ_IPU_D_FMT_IN_FMT_RGB555 |
			JZ_IPU_D_FMT_RGB_OUT_OFT_RGB;
		अवरोध;
	हाल DRM_FORMAT_XBGR1555:
		क्रमmat = JZ_IPU_D_FMT_IN_FMT_RGB555 |
			JZ_IPU_D_FMT_RGB_OUT_OFT_BGR;
		अवरोध;
	हाल DRM_FORMAT_RGB565:
		क्रमmat = JZ_IPU_D_FMT_IN_FMT_RGB565 |
			JZ_IPU_D_FMT_RGB_OUT_OFT_RGB;
		अवरोध;
	हाल DRM_FORMAT_BGR565:
		क्रमmat = JZ_IPU_D_FMT_IN_FMT_RGB565 |
			JZ_IPU_D_FMT_RGB_OUT_OFT_BGR;
		अवरोध;
	हाल DRM_FORMAT_XRGB8888:
	हाल DRM_FORMAT_XYUV8888:
		क्रमmat = JZ_IPU_D_FMT_IN_FMT_RGB888 |
			JZ_IPU_D_FMT_RGB_OUT_OFT_RGB;
		अवरोध;
	हाल DRM_FORMAT_XBGR8888:
		क्रमmat = JZ_IPU_D_FMT_IN_FMT_RGB888 |
			JZ_IPU_D_FMT_RGB_OUT_OFT_BGR;
		अवरोध;
	हाल DRM_FORMAT_YUYV:
		क्रमmat = JZ_IPU_D_FMT_IN_FMT_YUV422 |
			JZ_IPU_D_FMT_YUV_VY1UY0;
		अवरोध;
	हाल DRM_FORMAT_YVYU:
		क्रमmat = JZ_IPU_D_FMT_IN_FMT_YUV422 |
			JZ_IPU_D_FMT_YUV_UY1VY0;
		अवरोध;
	हाल DRM_FORMAT_UYVY:
		क्रमmat = JZ_IPU_D_FMT_IN_FMT_YUV422 |
			JZ_IPU_D_FMT_YUV_Y1VY0U;
		अवरोध;
	हाल DRM_FORMAT_VYUY:
		क्रमmat = JZ_IPU_D_FMT_IN_FMT_YUV422 |
			JZ_IPU_D_FMT_YUV_Y1UY0V;
		अवरोध;
	हाल DRM_FORMAT_YUV411:
		क्रमmat = JZ_IPU_D_FMT_IN_FMT_YUV411;
		अवरोध;
	हाल DRM_FORMAT_YUV420:
		क्रमmat = JZ_IPU_D_FMT_IN_FMT_YUV420;
		अवरोध;
	हाल DRM_FORMAT_YUV422:
		क्रमmat = JZ_IPU_D_FMT_IN_FMT_YUV422;
		अवरोध;
	हाल DRM_FORMAT_YUV444:
		क्रमmat = JZ_IPU_D_FMT_IN_FMT_YUV444;
		अवरोध;
	शेष:
		WARN_ONCE(1, "Unsupported format");
		अवरोध;
	पूर्ण

	/* Fix output to RGB888 */
	क्रमmat |= JZ_IPU_D_FMT_OUT_FMT_RGB888;

	/* Set pixel क्रमmat */
	regmap_ग_लिखो(ipu->map, JZ_REG_IPU_D_FMT, क्रमmat);

	/* Set the output height/width/stride */
	regmap_ग_लिखो(ipu->map, JZ_REG_IPU_OUT_GS,
		     ((newstate->crtc_w * 4) << JZ_IPU_OUT_GS_W_LSB)
		     | newstate->crtc_h << JZ_IPU_OUT_GS_H_LSB);
	regmap_ग_लिखो(ipu->map, JZ_REG_IPU_OUT_STRIDE, newstate->crtc_w * 4);

	अगर (finfo->is_yuv) अणु
		regmap_set_bits(ipu->map, JZ_REG_IPU_CTRL, JZ_IPU_CTRL_CSC_EN);

		/*
		 * Offsets क्रम Chroma/Luma.
		 * y = source Y - LUMA,
		 * u = source Cb - CHROMA,
		 * v = source Cr - CHROMA
		 */
		regmap_ग_लिखो(ipu->map, JZ_REG_IPU_CSC_OFFSET,
			     128 << JZ_IPU_CSC_OFFSET_CHROMA_LSB |
			     0 << JZ_IPU_CSC_OFFSET_LUMA_LSB);

		/*
		 * YUV422 to RGB conversion table.
		 * R = C0 / 0x400 * y + C1 / 0x400 * v
		 * G = C0 / 0x400 * y - C2 / 0x400 * u - C3 / 0x400 * v
		 * B = C0 / 0x400 * y + C4 / 0x400 * u
		 */
		regmap_ग_लिखो(ipu->map, JZ_REG_IPU_CSC_C0_COEF, 0x4a8);
		regmap_ग_लिखो(ipu->map, JZ_REG_IPU_CSC_C1_COEF, 0x662);
		regmap_ग_लिखो(ipu->map, JZ_REG_IPU_CSC_C2_COEF, 0x191);
		regmap_ग_लिखो(ipu->map, JZ_REG_IPU_CSC_C3_COEF, 0x341);
		regmap_ग_लिखो(ipu->map, JZ_REG_IPU_CSC_C4_COEF, 0x811);
	पूर्ण

	ctrl = 0;

	/*
	 * Must set ZOOM_SEL beक्रमe programming bicubic LUTs.
	 * If the IPU supports bicubic, we enable it unconditionally, since it
	 * can करो anything bilinear can and more.
	 */
	अगर (ipu->soc_info->has_bicubic)
		ctrl |= JZ_IPU_CTRL_ZOOM_SEL;

	upscaling_w = ipu->num_w > ipu->denom_w;
	अगर (upscaling_w)
		ctrl |= JZ_IPU_CTRL_HSCALE;

	अगर (ipu->num_w != 1 || ipu->denom_w != 1) अणु
		अगर (!ipu->soc_info->has_bicubic && !upscaling_w)
			coef_index |= (ipu->denom_w - 1) << 16;
		अन्यथा
			coef_index |= (ipu->num_w - 1) << 16;
		ctrl |= JZ_IPU_CTRL_HRSZ_EN;
	पूर्ण

	upscaling_h = ipu->num_h > ipu->denom_h;
	अगर (upscaling_h)
		ctrl |= JZ_IPU_CTRL_VSCALE;

	अगर (ipu->num_h != 1 || ipu->denom_h != 1) अणु
		अगर (!ipu->soc_info->has_bicubic && !upscaling_h)
			coef_index |= ipu->denom_h - 1;
		अन्यथा
			coef_index |= ipu->num_h - 1;
		ctrl |= JZ_IPU_CTRL_VRSZ_EN;
	पूर्ण

	regmap_update_bits(ipu->map, JZ_REG_IPU_CTRL, JZ_IPU_CTRL_ZOOM_SEL |
			   JZ_IPU_CTRL_HRSZ_EN | JZ_IPU_CTRL_VRSZ_EN |
			   JZ_IPU_CTRL_HSCALE | JZ_IPU_CTRL_VSCALE, ctrl);

	/* Set the LUT index रेजिस्टर */
	regmap_ग_लिखो(ipu->map, JZ_REG_IPU_RSZ_COEF_INDEX, coef_index);

	अगर (ipu->num_w != 1 || ipu->denom_w != 1)
		ingenic_ipu_set_coefs(ipu, JZ_REG_IPU_HRSZ_COEF_LUT,
				      ipu->num_w, ipu->denom_w);

	अगर (ipu->num_h != 1 || ipu->denom_h != 1)
		ingenic_ipu_set_coefs(ipu, JZ_REG_IPU_VRSZ_COEF_LUT,
				      ipu->num_h, ipu->denom_h);

	/* Clear STATUS रेजिस्टर */
	regmap_ग_लिखो(ipu->map, JZ_REG_IPU_STATUS, 0);

	/* Start IPU */
	regmap_set_bits(ipu->map, JZ_REG_IPU_CTRL,
			JZ_IPU_CTRL_RUN | JZ_IPU_CTRL_FM_IRQ_EN);

	dev_dbg(ipu->dev, "Scaling %ux%u to %ux%u (%u:%u horiz, %u:%u vert)\n",
		newstate->src_w >> 16, newstate->src_h >> 16,
		newstate->crtc_w, newstate->crtc_h,
		ipu->num_w, ipu->denom_w, ipu->num_h, ipu->denom_h);
पूर्ण

अटल पूर्णांक ingenic_ipu_plane_atomic_check(काष्ठा drm_plane *plane,
					  काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *old_plane_state = drm_atomic_get_old_plane_state(state,
										 plane);
	काष्ठा drm_plane_state *new_plane_state = drm_atomic_get_new_plane_state(state,
										 plane);
	अचिन्हित पूर्णांक num_w, denom_w, num_h, denom_h, xres, yres, max_w, max_h;
	काष्ठा ingenic_ipu *ipu = plane_to_ingenic_ipu(plane);
	काष्ठा drm_crtc *crtc = new_plane_state->crtc ?: old_plane_state->crtc;
	काष्ठा drm_crtc_state *crtc_state;

	अगर (!crtc)
		वापस 0;

	crtc_state = drm_atomic_get_existing_crtc_state(state, crtc);
	अगर (WARN_ON(!crtc_state))
		वापस -EINVAL;

	/* Request a full modeset अगर we are enabling or disabling the IPU. */
	अगर (!old_plane_state->crtc ^ !new_plane_state->crtc)
		crtc_state->mode_changed = true;

	अगर (!new_plane_state->crtc ||
	    !crtc_state->mode.hdisplay || !crtc_state->mode.vdisplay)
		वापस 0;

	/* Plane must be fully visible */
	अगर (new_plane_state->crtc_x < 0 || new_plane_state->crtc_y < 0 ||
	    new_plane_state->crtc_x + new_plane_state->crtc_w > crtc_state->mode.hdisplay ||
	    new_plane_state->crtc_y + new_plane_state->crtc_h > crtc_state->mode.vdisplay)
		वापस -EINVAL;

	/* Minimum size is 4x4 */
	अगर ((new_plane_state->src_w >> 16) < 4 || (new_plane_state->src_h >> 16) < 4)
		वापस -EINVAL;

	/* Input and output lines must have an even number of pixels. */
	अगर (((new_plane_state->src_w >> 16) & 1) || (new_plane_state->crtc_w & 1))
		वापस -EINVAL;

	अगर (!osd_changed(new_plane_state, old_plane_state))
		वापस 0;

	crtc_state->mode_changed = true;

	xres = new_plane_state->src_w >> 16;
	yres = new_plane_state->src_h >> 16;

	/*
	 * Increase the scaled image's theorical width/height until we find a
	 * configuration that has valid scaling coefficients, up to 102% of the
	 * screen's resolution. This makes sure that we can scale from almost
	 * every resolution possible at the cost of a very small distorsion.
	 * The CRTC_W / CRTC_H are not modअगरied.
	 */
	max_w = crtc_state->mode.hdisplay * 102 / 100;
	max_h = crtc_state->mode.vdisplay * 102 / 100;

	क्रम (denom_w = xres, num_w = new_plane_state->crtc_w; num_w <= max_w; num_w++)
		अगर (!reduce_fraction(&num_w, &denom_w))
			अवरोध;
	अगर (num_w > max_w)
		वापस -EINVAL;

	क्रम (denom_h = yres, num_h = new_plane_state->crtc_h; num_h <= max_h; num_h++)
		अगर (!reduce_fraction(&num_h, &denom_h))
			अवरोध;
	अगर (num_h > max_h)
		वापस -EINVAL;

	ipu->num_w = num_w;
	ipu->num_h = num_h;
	ipu->denom_w = denom_w;
	ipu->denom_h = denom_h;

	वापस 0;
पूर्ण

अटल व्योम ingenic_ipu_plane_atomic_disable(काष्ठा drm_plane *plane,
					     काष्ठा drm_atomic_state *state)
अणु
	काष्ठा ingenic_ipu *ipu = plane_to_ingenic_ipu(plane);

	regmap_set_bits(ipu->map, JZ_REG_IPU_CTRL, JZ_IPU_CTRL_STOP);
	regmap_clear_bits(ipu->map, JZ_REG_IPU_CTRL, JZ_IPU_CTRL_CHIP_EN);

	ingenic_drm_plane_disable(ipu->master, plane);

	अगर (ipu->clk_enabled) अणु
		clk_disable(ipu->clk);
		ipu->clk_enabled = false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा drm_plane_helper_funcs ingenic_ipu_plane_helper_funcs = अणु
	.atomic_update		= ingenic_ipu_plane_atomic_update,
	.atomic_check		= ingenic_ipu_plane_atomic_check,
	.atomic_disable		= ingenic_ipu_plane_atomic_disable,
	.prepare_fb		= drm_gem_plane_helper_prepare_fb,
पूर्ण;

अटल पूर्णांक
ingenic_ipu_plane_atomic_get_property(काष्ठा drm_plane *plane,
				      स्थिर काष्ठा drm_plane_state *state,
				      काष्ठा drm_property *property, u64 *val)
अणु
	काष्ठा ingenic_ipu *ipu = plane_to_ingenic_ipu(plane);

	अगर (property != ipu->sharpness_prop)
		वापस -EINVAL;

	*val = ipu->sharpness;

	वापस 0;
पूर्ण

अटल पूर्णांक
ingenic_ipu_plane_atomic_set_property(काष्ठा drm_plane *plane,
				      काष्ठा drm_plane_state *state,
				      काष्ठा drm_property *property, u64 val)
अणु
	काष्ठा ingenic_ipu *ipu = plane_to_ingenic_ipu(plane);
	काष्ठा drm_crtc_state *crtc_state;

	अगर (property != ipu->sharpness_prop)
		वापस -EINVAL;

	ipu->sharpness = val;

	अगर (state->crtc) अणु
		crtc_state = drm_atomic_get_existing_crtc_state(state->state, state->crtc);
		अगर (WARN_ON(!crtc_state))
			वापस -EINVAL;

		crtc_state->mode_changed = true;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_plane_funcs ingenic_ipu_plane_funcs = अणु
	.update_plane		= drm_atomic_helper_update_plane,
	.disable_plane		= drm_atomic_helper_disable_plane,
	.reset			= drm_atomic_helper_plane_reset,
	.destroy		= drm_plane_cleanup,

	.atomic_duplicate_state	= drm_atomic_helper_plane_duplicate_state,
	.atomic_destroy_state	= drm_atomic_helper_plane_destroy_state,

	.atomic_get_property	= ingenic_ipu_plane_atomic_get_property,
	.atomic_set_property	= ingenic_ipu_plane_atomic_set_property,
पूर्ण;

अटल irqवापस_t ingenic_ipu_irq_handler(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा ingenic_ipu *ipu = arg;
	काष्ठा drm_crtc *crtc = drm_crtc_from_index(ipu->drm, 0);
	अचिन्हित पूर्णांक dummy;

	/* dummy पढ़ो allows CPU to reconfigure IPU */
	अगर (ipu->soc_info->manual_restart)
		regmap_पढ़ो(ipu->map, JZ_REG_IPU_STATUS, &dummy);

	/* ACK पूर्णांकerrupt */
	regmap_ग_लिखो(ipu->map, JZ_REG_IPU_STATUS, 0);

	/* Set previously cached addresses */
	regmap_ग_लिखो(ipu->map, JZ_REG_IPU_Y_ADDR, ipu->addr_y);
	regmap_ग_लिखो(ipu->map, JZ_REG_IPU_U_ADDR, ipu->addr_u);
	regmap_ग_लिखो(ipu->map, JZ_REG_IPU_V_ADDR, ipu->addr_v);

	/* Run IPU क्रम the new frame */
	अगर (ipu->soc_info->manual_restart)
		regmap_set_bits(ipu->map, JZ_REG_IPU_CTRL, JZ_IPU_CTRL_RUN);

	drm_crtc_handle_vblank(crtc);

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा regmap_config ingenic_ipu_regmap_config = अणु
	.reg_bits = 32,
	.val_bits = 32,
	.reg_stride = 4,

	.max_रेजिस्टर = JZ_REG_IPU_OUT_PHY_T_ADDR,
पूर्ण;

अटल पूर्णांक ingenic_ipu_bind(काष्ठा device *dev, काष्ठा device *master, व्योम *d)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	स्थिर काष्ठा soc_info *soc_info;
	काष्ठा drm_device *drm = d;
	काष्ठा drm_plane *plane;
	काष्ठा ingenic_ipu *ipu;
	व्योम __iomem *base;
	अचिन्हित पूर्णांक sharpness_max;
	पूर्णांक err, irq;

	ipu = devm_kzalloc(dev, माप(*ipu), GFP_KERNEL);
	अगर (!ipu)
		वापस -ENOMEM;

	soc_info = of_device_get_match_data(dev);
	अगर (!soc_info) अणु
		dev_err(dev, "Missing platform data\n");
		वापस -EINVAL;
	पूर्ण

	ipu->dev = dev;
	ipu->drm = drm;
	ipu->master = master;
	ipu->soc_info = soc_info;

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base)) अणु
		dev_err(dev, "Failed to get memory resource\n");
		वापस PTR_ERR(base);
	पूर्ण

	ipu->map = devm_regmap_init_mmio(dev, base, &ingenic_ipu_regmap_config);
	अगर (IS_ERR(ipu->map)) अणु
		dev_err(dev, "Failed to create regmap\n");
		वापस PTR_ERR(ipu->map);
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	ipu->clk = devm_clk_get(dev, "ipu");
	अगर (IS_ERR(ipu->clk)) अणु
		dev_err(dev, "Failed to get pixel clock\n");
		वापस PTR_ERR(ipu->clk);
	पूर्ण

	err = devm_request_irq(dev, irq, ingenic_ipu_irq_handler, 0,
			       dev_name(dev), ipu);
	अगर (err) अणु
		dev_err(dev, "Unable to request IRQ\n");
		वापस err;
	पूर्ण

	plane = &ipu->plane;
	dev_set_drvdata(dev, plane);

	drm_plane_helper_add(plane, &ingenic_ipu_plane_helper_funcs);

	err = drm_universal_plane_init(drm, plane, 1, &ingenic_ipu_plane_funcs,
				       soc_info->क्रमmats, soc_info->num_क्रमmats,
				       शून्य, DRM_PLANE_TYPE_PRIMARY, शून्य);
	अगर (err) अणु
		dev_err(dev, "Failed to init plane: %i\n", err);
		वापस err;
	पूर्ण

	/*
	 * Sharpness settings range is [0,32]
	 * 0       : nearest-neighbor
	 * 1       : bilinear
	 * 2 .. 32 : bicubic (translated to sharpness factor -0.25 .. -4.0)
	 */
	sharpness_max = soc_info->has_bicubic ? 32 : 1;
	ipu->sharpness_prop = drm_property_create_range(drm, 0, "sharpness",
							0, sharpness_max);
	अगर (!ipu->sharpness_prop) अणु
		dev_err(dev, "Unable to create sharpness property\n");
		वापस -ENOMEM;
	पूर्ण

	/* Default sharpness factor: -0.125 * 8 = -1.0 */
	ipu->sharpness = soc_info->has_bicubic ? 8 : 1;
	drm_object_attach_property(&plane->base, ipu->sharpness_prop,
				   ipu->sharpness);

	err = clk_prepare(ipu->clk);
	अगर (err) अणु
		dev_err(dev, "Unable to prepare clock\n");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ingenic_ipu_unbind(काष्ठा device *dev,
			       काष्ठा device *master, व्योम *d)
अणु
	काष्ठा ingenic_ipu *ipu = dev_get_drvdata(dev);

	clk_unprepare(ipu->clk);
पूर्ण

अटल स्थिर काष्ठा component_ops ingenic_ipu_ops = अणु
	.bind = ingenic_ipu_bind,
	.unbind = ingenic_ipu_unbind,
पूर्ण;

अटल पूर्णांक ingenic_ipu_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस component_add(&pdev->dev, &ingenic_ipu_ops);
पूर्ण

अटल पूर्णांक ingenic_ipu_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	component_del(&pdev->dev, &ingenic_ipu_ops);
	वापस 0;
पूर्ण

अटल स्थिर u32 jz4725b_ipu_क्रमmats[] = अणु
	/*
	 * While officially supported, packed YUV 4:2:2 क्रमmats can cause
	 * अक्रमom hardware crashes on JZ4725B under certain circumstances.
	 * It seems to happen with some specअगरic resize ratios.
	 * Until a proper workaround or fix is found, disable these क्रमmats.
	DRM_FORMAT_YUYV,
	DRM_FORMAT_YVYU,
	DRM_FORMAT_UYVY,
	DRM_FORMAT_VYUY,
	*/
	DRM_FORMAT_YUV411,
	DRM_FORMAT_YUV420,
	DRM_FORMAT_YUV422,
	DRM_FORMAT_YUV444,
पूर्ण;

अटल स्थिर काष्ठा soc_info jz4725b_soc_info = अणु
	.क्रमmats	= jz4725b_ipu_क्रमmats,
	.num_क्रमmats	= ARRAY_SIZE(jz4725b_ipu_क्रमmats),
	.has_bicubic	= false,
	.manual_restart	= true,
	.set_coefs	= jz4725b_set_coefs,
पूर्ण;

अटल स्थिर u32 jz4760_ipu_क्रमmats[] = अणु
	DRM_FORMAT_XRGB1555,
	DRM_FORMAT_XBGR1555,
	DRM_FORMAT_RGB565,
	DRM_FORMAT_BGR565,
	DRM_FORMAT_XRGB8888,
	DRM_FORMAT_XBGR8888,
	DRM_FORMAT_YUYV,
	DRM_FORMAT_YVYU,
	DRM_FORMAT_UYVY,
	DRM_FORMAT_VYUY,
	DRM_FORMAT_YUV411,
	DRM_FORMAT_YUV420,
	DRM_FORMAT_YUV422,
	DRM_FORMAT_YUV444,
	DRM_FORMAT_XYUV8888,
पूर्ण;

अटल स्थिर काष्ठा soc_info jz4760_soc_info = अणु
	.क्रमmats	= jz4760_ipu_क्रमmats,
	.num_क्रमmats	= ARRAY_SIZE(jz4760_ipu_क्रमmats),
	.has_bicubic	= true,
	.manual_restart	= false,
	.set_coefs	= jz4760_set_coefs,
पूर्ण;

अटल स्थिर काष्ठा of_device_id ingenic_ipu_of_match[] = अणु
	अणु .compatible = "ingenic,jz4725b-ipu", .data = &jz4725b_soc_info पूर्ण,
	अणु .compatible = "ingenic,jz4760-ipu", .data = &jz4760_soc_info पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ingenic_ipu_of_match);

अटल काष्ठा platक्रमm_driver ingenic_ipu_driver = अणु
	.driver = अणु
		.name = "ingenic-ipu",
		.of_match_table = ingenic_ipu_of_match,
	पूर्ण,
	.probe = ingenic_ipu_probe,
	.हटाओ = ingenic_ipu_हटाओ,
पूर्ण;

काष्ठा platक्रमm_driver *ingenic_ipu_driver_ptr = &ingenic_ipu_driver;
