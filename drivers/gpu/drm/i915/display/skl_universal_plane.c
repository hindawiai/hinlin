<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2020 Intel Corporation
 */

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_damage_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_plane_helper.h>

#समावेश "i915_drv.h"
#समावेश "intel_atomic_plane.h"
#समावेश "intel_display_types.h"
#समावेश "intel_fb.h"
#समावेश "intel_pm.h"
#समावेश "intel_psr.h"
#समावेश "intel_sprite.h"
#समावेश "skl_scaler.h"
#समावेश "skl_universal_plane.h"

अटल स्थिर u32 skl_plane_क्रमmats[] = अणु
	DRM_FORMAT_C8,
	DRM_FORMAT_RGB565,
	DRM_FORMAT_XRGB8888,
	DRM_FORMAT_XBGR8888,
	DRM_FORMAT_ARGB8888,
	DRM_FORMAT_ABGR8888,
	DRM_FORMAT_XRGB2101010,
	DRM_FORMAT_XBGR2101010,
	DRM_FORMAT_XRGB16161616F,
	DRM_FORMAT_XBGR16161616F,
	DRM_FORMAT_YUYV,
	DRM_FORMAT_YVYU,
	DRM_FORMAT_UYVY,
	DRM_FORMAT_VYUY,
	DRM_FORMAT_XYUV8888,
पूर्ण;

अटल स्थिर u32 skl_planar_क्रमmats[] = अणु
	DRM_FORMAT_C8,
	DRM_FORMAT_RGB565,
	DRM_FORMAT_XRGB8888,
	DRM_FORMAT_XBGR8888,
	DRM_FORMAT_ARGB8888,
	DRM_FORMAT_ABGR8888,
	DRM_FORMAT_XRGB2101010,
	DRM_FORMAT_XBGR2101010,
	DRM_FORMAT_XRGB16161616F,
	DRM_FORMAT_XBGR16161616F,
	DRM_FORMAT_YUYV,
	DRM_FORMAT_YVYU,
	DRM_FORMAT_UYVY,
	DRM_FORMAT_VYUY,
	DRM_FORMAT_NV12,
	DRM_FORMAT_XYUV8888,
पूर्ण;

अटल स्थिर u32 glk_planar_क्रमmats[] = अणु
	DRM_FORMAT_C8,
	DRM_FORMAT_RGB565,
	DRM_FORMAT_XRGB8888,
	DRM_FORMAT_XBGR8888,
	DRM_FORMAT_ARGB8888,
	DRM_FORMAT_ABGR8888,
	DRM_FORMAT_XRGB2101010,
	DRM_FORMAT_XBGR2101010,
	DRM_FORMAT_XRGB16161616F,
	DRM_FORMAT_XBGR16161616F,
	DRM_FORMAT_YUYV,
	DRM_FORMAT_YVYU,
	DRM_FORMAT_UYVY,
	DRM_FORMAT_VYUY,
	DRM_FORMAT_NV12,
	DRM_FORMAT_XYUV8888,
	DRM_FORMAT_P010,
	DRM_FORMAT_P012,
	DRM_FORMAT_P016,
पूर्ण;

अटल स्थिर u32 icl_sdr_y_plane_क्रमmats[] = अणु
	DRM_FORMAT_C8,
	DRM_FORMAT_RGB565,
	DRM_FORMAT_XRGB8888,
	DRM_FORMAT_XBGR8888,
	DRM_FORMAT_ARGB8888,
	DRM_FORMAT_ABGR8888,
	DRM_FORMAT_XRGB2101010,
	DRM_FORMAT_XBGR2101010,
	DRM_FORMAT_ARGB2101010,
	DRM_FORMAT_ABGR2101010,
	DRM_FORMAT_YUYV,
	DRM_FORMAT_YVYU,
	DRM_FORMAT_UYVY,
	DRM_FORMAT_VYUY,
	DRM_FORMAT_Y210,
	DRM_FORMAT_Y212,
	DRM_FORMAT_Y216,
	DRM_FORMAT_XYUV8888,
	DRM_FORMAT_XVYU2101010,
	DRM_FORMAT_XVYU12_16161616,
	DRM_FORMAT_XVYU16161616,
पूर्ण;

अटल स्थिर u32 icl_sdr_uv_plane_क्रमmats[] = अणु
	DRM_FORMAT_C8,
	DRM_FORMAT_RGB565,
	DRM_FORMAT_XRGB8888,
	DRM_FORMAT_XBGR8888,
	DRM_FORMAT_ARGB8888,
	DRM_FORMAT_ABGR8888,
	DRM_FORMAT_XRGB2101010,
	DRM_FORMAT_XBGR2101010,
	DRM_FORMAT_ARGB2101010,
	DRM_FORMAT_ABGR2101010,
	DRM_FORMAT_YUYV,
	DRM_FORMAT_YVYU,
	DRM_FORMAT_UYVY,
	DRM_FORMAT_VYUY,
	DRM_FORMAT_NV12,
	DRM_FORMAT_P010,
	DRM_FORMAT_P012,
	DRM_FORMAT_P016,
	DRM_FORMAT_Y210,
	DRM_FORMAT_Y212,
	DRM_FORMAT_Y216,
	DRM_FORMAT_XYUV8888,
	DRM_FORMAT_XVYU2101010,
	DRM_FORMAT_XVYU12_16161616,
	DRM_FORMAT_XVYU16161616,
पूर्ण;

अटल स्थिर u32 icl_hdr_plane_क्रमmats[] = अणु
	DRM_FORMAT_C8,
	DRM_FORMAT_RGB565,
	DRM_FORMAT_XRGB8888,
	DRM_FORMAT_XBGR8888,
	DRM_FORMAT_ARGB8888,
	DRM_FORMAT_ABGR8888,
	DRM_FORMAT_XRGB2101010,
	DRM_FORMAT_XBGR2101010,
	DRM_FORMAT_ARGB2101010,
	DRM_FORMAT_ABGR2101010,
	DRM_FORMAT_XRGB16161616F,
	DRM_FORMAT_XBGR16161616F,
	DRM_FORMAT_ARGB16161616F,
	DRM_FORMAT_ABGR16161616F,
	DRM_FORMAT_YUYV,
	DRM_FORMAT_YVYU,
	DRM_FORMAT_UYVY,
	DRM_FORMAT_VYUY,
	DRM_FORMAT_NV12,
	DRM_FORMAT_P010,
	DRM_FORMAT_P012,
	DRM_FORMAT_P016,
	DRM_FORMAT_Y210,
	DRM_FORMAT_Y212,
	DRM_FORMAT_Y216,
	DRM_FORMAT_XYUV8888,
	DRM_FORMAT_XVYU2101010,
	DRM_FORMAT_XVYU12_16161616,
	DRM_FORMAT_XVYU16161616,
पूर्ण;

अटल स्थिर u64 skl_plane_क्रमmat_modअगरiers_noccs[] = अणु
	I915_FORMAT_MOD_Yf_TILED,
	I915_FORMAT_MOD_Y_TILED,
	I915_FORMAT_MOD_X_TILED,
	DRM_FORMAT_MOD_LINEAR,
	DRM_FORMAT_MOD_INVALID
पूर्ण;

अटल स्थिर u64 skl_plane_क्रमmat_modअगरiers_ccs[] = अणु
	I915_FORMAT_MOD_Yf_TILED_CCS,
	I915_FORMAT_MOD_Y_TILED_CCS,
	I915_FORMAT_MOD_Yf_TILED,
	I915_FORMAT_MOD_Y_TILED,
	I915_FORMAT_MOD_X_TILED,
	DRM_FORMAT_MOD_LINEAR,
	DRM_FORMAT_MOD_INVALID
पूर्ण;

अटल स्थिर u64 gen12_plane_क्रमmat_modअगरiers_mc_ccs[] = अणु
	I915_FORMAT_MOD_Y_TILED_GEN12_MC_CCS,
	I915_FORMAT_MOD_Y_TILED_GEN12_RC_CCS,
	I915_FORMAT_MOD_Y_TILED_GEN12_RC_CCS_CC,
	I915_FORMAT_MOD_Y_TILED,
	I915_FORMAT_MOD_X_TILED,
	DRM_FORMAT_MOD_LINEAR,
	DRM_FORMAT_MOD_INVALID
पूर्ण;

अटल स्थिर u64 gen12_plane_क्रमmat_modअगरiers_rc_ccs[] = अणु
	I915_FORMAT_MOD_Y_TILED_GEN12_RC_CCS,
	I915_FORMAT_MOD_Y_TILED_GEN12_RC_CCS_CC,
	I915_FORMAT_MOD_Y_TILED,
	I915_FORMAT_MOD_X_TILED,
	DRM_FORMAT_MOD_LINEAR,
	DRM_FORMAT_MOD_INVALID
पूर्ण;

पूर्णांक skl_क्रमmat_to_fourcc(पूर्णांक क्रमmat, bool rgb_order, bool alpha)
अणु
	चयन (क्रमmat) अणु
	हाल PLANE_CTL_FORMAT_RGB_565:
		वापस DRM_FORMAT_RGB565;
	हाल PLANE_CTL_FORMAT_NV12:
		वापस DRM_FORMAT_NV12;
	हाल PLANE_CTL_FORMAT_XYUV:
		वापस DRM_FORMAT_XYUV8888;
	हाल PLANE_CTL_FORMAT_P010:
		वापस DRM_FORMAT_P010;
	हाल PLANE_CTL_FORMAT_P012:
		वापस DRM_FORMAT_P012;
	हाल PLANE_CTL_FORMAT_P016:
		वापस DRM_FORMAT_P016;
	हाल PLANE_CTL_FORMAT_Y210:
		वापस DRM_FORMAT_Y210;
	हाल PLANE_CTL_FORMAT_Y212:
		वापस DRM_FORMAT_Y212;
	हाल PLANE_CTL_FORMAT_Y216:
		वापस DRM_FORMAT_Y216;
	हाल PLANE_CTL_FORMAT_Y410:
		वापस DRM_FORMAT_XVYU2101010;
	हाल PLANE_CTL_FORMAT_Y412:
		वापस DRM_FORMAT_XVYU12_16161616;
	हाल PLANE_CTL_FORMAT_Y416:
		वापस DRM_FORMAT_XVYU16161616;
	शेष:
	हाल PLANE_CTL_FORMAT_XRGB_8888:
		अगर (rgb_order) अणु
			अगर (alpha)
				वापस DRM_FORMAT_ABGR8888;
			अन्यथा
				वापस DRM_FORMAT_XBGR8888;
		पूर्ण अन्यथा अणु
			अगर (alpha)
				वापस DRM_FORMAT_ARGB8888;
			अन्यथा
				वापस DRM_FORMAT_XRGB8888;
		पूर्ण
	हाल PLANE_CTL_FORMAT_XRGB_2101010:
		अगर (rgb_order) अणु
			अगर (alpha)
				वापस DRM_FORMAT_ABGR2101010;
			अन्यथा
				वापस DRM_FORMAT_XBGR2101010;
		पूर्ण अन्यथा अणु
			अगर (alpha)
				वापस DRM_FORMAT_ARGB2101010;
			अन्यथा
				वापस DRM_FORMAT_XRGB2101010;
		पूर्ण
	हाल PLANE_CTL_FORMAT_XRGB_16161616F:
		अगर (rgb_order) अणु
			अगर (alpha)
				वापस DRM_FORMAT_ABGR16161616F;
			अन्यथा
				वापस DRM_FORMAT_XBGR16161616F;
		पूर्ण अन्यथा अणु
			अगर (alpha)
				वापस DRM_FORMAT_ARGB16161616F;
			अन्यथा
				वापस DRM_FORMAT_XRGB16161616F;
		पूर्ण
	पूर्ण
पूर्ण

अटल u8 icl_nv12_y_plane_mask(काष्ठा drm_i915_निजी *i915)
अणु
	अगर (HAS_D12_PLANE_MINIMIZATION(i915))
		वापस BIT(PLANE_SPRITE2) | BIT(PLANE_SPRITE3);
	अन्यथा
		वापस BIT(PLANE_SPRITE4) | BIT(PLANE_SPRITE5);
पूर्ण

bool icl_is_nv12_y_plane(काष्ठा drm_i915_निजी *dev_priv,
			 क्रमागत plane_id plane_id)
अणु
	वापस DISPLAY_VER(dev_priv) >= 11 &&
		icl_nv12_y_plane_mask(dev_priv) & BIT(plane_id);
पूर्ण

bool icl_is_hdr_plane(काष्ठा drm_i915_निजी *dev_priv, क्रमागत plane_id plane_id)
अणु
	वापस DISPLAY_VER(dev_priv) >= 11 &&
		icl_hdr_plane_mask() & BIT(plane_id);
पूर्ण

अटल व्योम
skl_plane_ratio(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
		स्थिर काष्ठा पूर्णांकel_plane_state *plane_state,
		अचिन्हित पूर्णांक *num, अचिन्हित पूर्णांक *den)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(plane_state->uapi.plane->dev);
	स्थिर काष्ठा drm_framebuffer *fb = plane_state->hw.fb;

	अगर (fb->क्रमmat->cpp[0] == 8) अणु
		अगर (DISPLAY_VER(dev_priv) >= 10) अणु
			*num = 10;
			*den = 8;
		पूर्ण अन्यथा अणु
			*num = 9;
			*den = 8;
		पूर्ण
	पूर्ण अन्यथा अणु
		*num = 1;
		*den = 1;
	पूर्ण
पूर्ण

अटल पूर्णांक skl_plane_min_cdclk(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			       स्थिर काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(plane_state->uapi.plane->dev);
	अचिन्हित पूर्णांक num, den;
	अचिन्हित पूर्णांक pixel_rate = पूर्णांकel_plane_pixel_rate(crtc_state, plane_state);

	skl_plane_ratio(crtc_state, plane_state, &num, &den);

	/* two pixels per घड़ी on glk+ */
	अगर (DISPLAY_VER(dev_priv) >= 10)
		den *= 2;

	वापस DIV_ROUND_UP(pixel_rate * num, den);
पूर्ण

अटल पूर्णांक skl_plane_max_width(स्थिर काष्ठा drm_framebuffer *fb,
			       पूर्णांक color_plane,
			       अचिन्हित पूर्णांक rotation)
अणु
	पूर्णांक cpp = fb->क्रमmat->cpp[color_plane];

	चयन (fb->modअगरier) अणु
	हाल DRM_FORMAT_MOD_LINEAR:
	हाल I915_FORMAT_MOD_X_TILED:
		/*
		 * Validated limit is 4k, but has 5k should
		 * work apart from the following features:
		 * - Ytile (alपढ़ोy limited to 4k)
		 * - FP16 (alपढ़ोy limited to 4k)
		 * - render compression (alपढ़ोy limited to 4k)
		 * - KVMR sprite and cursor (करोn't care)
		 * - horizontal panning (TODO verअगरy this)
		 * - pipe and plane scaling (TODO verअगरy this)
		 */
		अगर (cpp == 8)
			वापस 4096;
		अन्यथा
			वापस 5120;
	हाल I915_FORMAT_MOD_Y_TILED_CCS:
	हाल I915_FORMAT_MOD_Yf_TILED_CCS:
	हाल I915_FORMAT_MOD_Y_TILED_GEN12_MC_CCS:
		/* FIXME AUX plane? */
	हाल I915_FORMAT_MOD_Y_TILED:
	हाल I915_FORMAT_MOD_Yf_TILED:
		अगर (cpp == 8)
			वापस 2048;
		अन्यथा
			वापस 4096;
	शेष:
		MISSING_CASE(fb->modअगरier);
		वापस 2048;
	पूर्ण
पूर्ण

अटल पूर्णांक glk_plane_max_width(स्थिर काष्ठा drm_framebuffer *fb,
			       पूर्णांक color_plane,
			       अचिन्हित पूर्णांक rotation)
अणु
	पूर्णांक cpp = fb->क्रमmat->cpp[color_plane];

	चयन (fb->modअगरier) अणु
	हाल DRM_FORMAT_MOD_LINEAR:
	हाल I915_FORMAT_MOD_X_TILED:
		अगर (cpp == 8)
			वापस 4096;
		अन्यथा
			वापस 5120;
	हाल I915_FORMAT_MOD_Y_TILED_CCS:
	हाल I915_FORMAT_MOD_Yf_TILED_CCS:
		/* FIXME AUX plane? */
	हाल I915_FORMAT_MOD_Y_TILED:
	हाल I915_FORMAT_MOD_Yf_TILED:
		अगर (cpp == 8)
			वापस 2048;
		अन्यथा
			वापस 5120;
	शेष:
		MISSING_CASE(fb->modअगरier);
		वापस 2048;
	पूर्ण
पूर्ण

अटल पूर्णांक icl_plane_min_width(स्थिर काष्ठा drm_framebuffer *fb,
			       पूर्णांक color_plane,
			       अचिन्हित पूर्णांक rotation)
अणु
	/* Wa_14011264657, Wa_14011050563: gen11+ */
	चयन (fb->क्रमmat->क्रमmat) अणु
	हाल DRM_FORMAT_C8:
		वापस 18;
	हाल DRM_FORMAT_RGB565:
		वापस 10;
	हाल DRM_FORMAT_XRGB8888:
	हाल DRM_FORMAT_XBGR8888:
	हाल DRM_FORMAT_ARGB8888:
	हाल DRM_FORMAT_ABGR8888:
	हाल DRM_FORMAT_XRGB2101010:
	हाल DRM_FORMAT_XBGR2101010:
	हाल DRM_FORMAT_ARGB2101010:
	हाल DRM_FORMAT_ABGR2101010:
	हाल DRM_FORMAT_XVYU2101010:
	हाल DRM_FORMAT_Y212:
	हाल DRM_FORMAT_Y216:
		वापस 6;
	हाल DRM_FORMAT_NV12:
		वापस 20;
	हाल DRM_FORMAT_P010:
	हाल DRM_FORMAT_P012:
	हाल DRM_FORMAT_P016:
		वापस 12;
	हाल DRM_FORMAT_XRGB16161616F:
	हाल DRM_FORMAT_XBGR16161616F:
	हाल DRM_FORMAT_ARGB16161616F:
	हाल DRM_FORMAT_ABGR16161616F:
	हाल DRM_FORMAT_XVYU12_16161616:
	हाल DRM_FORMAT_XVYU16161616:
		वापस 4;
	शेष:
		वापस 1;
	पूर्ण
पूर्ण

अटल पूर्णांक icl_plane_max_width(स्थिर काष्ठा drm_framebuffer *fb,
			       पूर्णांक color_plane,
			       अचिन्हित पूर्णांक rotation)
अणु
	वापस 5120;
पूर्ण

अटल पूर्णांक skl_plane_max_height(स्थिर काष्ठा drm_framebuffer *fb,
				पूर्णांक color_plane,
				अचिन्हित पूर्णांक rotation)
अणु
	वापस 4096;
पूर्ण

अटल पूर्णांक icl_plane_max_height(स्थिर काष्ठा drm_framebuffer *fb,
				पूर्णांक color_plane,
				अचिन्हित पूर्णांक rotation)
अणु
	वापस 4320;
पूर्ण

अटल अचिन्हित पूर्णांक
skl_plane_max_stride(काष्ठा पूर्णांकel_plane *plane,
		     u32 pixel_क्रमmat, u64 modअगरier,
		     अचिन्हित पूर्णांक rotation)
अणु
	स्थिर काष्ठा drm_क्रमmat_info *info = drm_क्रमmat_info(pixel_क्रमmat);
	पूर्णांक cpp = info->cpp[0];

	/*
	 * "The stride in bytes must not exceed the
	 * of the size of 8K pixels and 32K bytes."
	 */
	अगर (drm_rotation_90_or_270(rotation))
		वापस min(8192, 32768 / cpp);
	अन्यथा
		वापस min(8192 * cpp, 32768);
पूर्ण


/* Preoffset values क्रम YUV to RGB Conversion */
#घोषणा PRखातापूर्णF_YUV_TO_RGB_HI		0x1800
#घोषणा PRखातापूर्णF_YUV_TO_RGB_ME		0x0000
#घोषणा PRखातापूर्णF_YUV_TO_RGB_LO		0x1800

#घोषणा  ROFF(x)          (((x) & 0xffff) << 16)
#घोषणा  GOFF(x)          (((x) & 0xffff) << 0)
#घोषणा  BOFF(x)          (((x) & 0xffff) << 16)

/*
 * Programs the input color space conversion stage क्रम ICL HDR planes.
 * Note that it is assumed that this stage always happens after YUV
 * range correction. Thus, the input to this stage is assumed to be
 * in full-range YCbCr.
 */
अटल व्योम
icl_program_input_csc(काष्ठा पूर्णांकel_plane *plane,
		      स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
		      स्थिर काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(plane->base.dev);
	क्रमागत pipe pipe = plane->pipe;
	क्रमागत plane_id plane_id = plane->id;

	अटल स्थिर u16 input_csc_matrix[][9] = अणु
		/*
		 * BT.601 full range YCbCr -> full range RGB
		 * The matrix required is :
		 * [1.000, 0.000, 1.371,
		 *  1.000, -0.336, -0.698,
		 *  1.000, 1.732, 0.0000]
		 */
		[DRM_COLOR_YCBCR_BT601] = अणु
			0x7AF8, 0x7800, 0x0,
			0x8B28, 0x7800, 0x9AC0,
			0x0, 0x7800, 0x7DD8,
		पूर्ण,
		/*
		 * BT.709 full range YCbCr -> full range RGB
		 * The matrix required is :
		 * [1.000, 0.000, 1.574,
		 *  1.000, -0.187, -0.468,
		 *  1.000, 1.855, 0.0000]
		 */
		[DRM_COLOR_YCBCR_BT709] = अणु
			0x7C98, 0x7800, 0x0,
			0x9EF8, 0x7800, 0xAC00,
			0x0, 0x7800,  0x7ED8,
		पूर्ण,
		/*
		 * BT.2020 full range YCbCr -> full range RGB
		 * The matrix required is :
		 * [1.000, 0.000, 1.474,
		 *  1.000, -0.1645, -0.5713,
		 *  1.000, 1.8814, 0.0000]
		 */
		[DRM_COLOR_YCBCR_BT2020] = अणु
			0x7BC8, 0x7800, 0x0,
			0x8928, 0x7800, 0xAA88,
			0x0, 0x7800, 0x7F10,
		पूर्ण,
	पूर्ण;
	स्थिर u16 *csc = input_csc_matrix[plane_state->hw.color_encoding];

	पूर्णांकel_de_ग_लिखो_fw(dev_priv, PLANE_INPUT_CSC_COEFF(pipe, plane_id, 0),
			  ROFF(csc[0]) | GOFF(csc[1]));
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, PLANE_INPUT_CSC_COEFF(pipe, plane_id, 1),
			  BOFF(csc[2]));
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, PLANE_INPUT_CSC_COEFF(pipe, plane_id, 2),
			  ROFF(csc[3]) | GOFF(csc[4]));
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, PLANE_INPUT_CSC_COEFF(pipe, plane_id, 3),
			  BOFF(csc[5]));
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, PLANE_INPUT_CSC_COEFF(pipe, plane_id, 4),
			  ROFF(csc[6]) | GOFF(csc[7]));
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, PLANE_INPUT_CSC_COEFF(pipe, plane_id, 5),
			  BOFF(csc[8]));

	पूर्णांकel_de_ग_लिखो_fw(dev_priv, PLANE_INPUT_CSC_PRखातापूर्णF(pipe, plane_id, 0),
			  PRखातापूर्णF_YUV_TO_RGB_HI);
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, PLANE_INPUT_CSC_PRखातापूर्णF(pipe, plane_id, 1),
			  PRखातापूर्णF_YUV_TO_RGB_ME);
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, PLANE_INPUT_CSC_PRखातापूर्णF(pipe, plane_id, 2),
			  PRखातापूर्णF_YUV_TO_RGB_LO);
	पूर्णांकel_de_ग_लिखो_fw(dev_priv,
			  PLANE_INPUT_CSC_POSTOFF(pipe, plane_id, 0), 0x0);
	पूर्णांकel_de_ग_लिखो_fw(dev_priv,
			  PLANE_INPUT_CSC_POSTOFF(pipe, plane_id, 1), 0x0);
	पूर्णांकel_de_ग_लिखो_fw(dev_priv,
			  PLANE_INPUT_CSC_POSTOFF(pipe, plane_id, 2), 0x0);
पूर्ण

अटल अचिन्हित पूर्णांक skl_plane_stride_mult(स्थिर काष्ठा drm_framebuffer *fb,
					  पूर्णांक color_plane, अचिन्हित पूर्णांक rotation)
अणु
	/*
	 * The stride is either expressed as a multiple of 64 bytes chunks क्रम
	 * linear buffers or in number of tiles क्रम tiled buffers.
	 */
	अगर (is_surface_linear(fb, color_plane))
		वापस 64;
	अन्यथा अगर (drm_rotation_90_or_270(rotation))
		वापस पूर्णांकel_tile_height(fb, color_plane);
	अन्यथा
		वापस पूर्णांकel_tile_width_bytes(fb, color_plane);
पूर्ण

अटल u32 skl_plane_stride(स्थिर काष्ठा पूर्णांकel_plane_state *plane_state,
			    पूर्णांक color_plane)
अणु
	स्थिर काष्ठा drm_framebuffer *fb = plane_state->hw.fb;
	अचिन्हित पूर्णांक rotation = plane_state->hw.rotation;
	u32 stride = plane_state->view.color_plane[color_plane].stride;

	अगर (color_plane >= fb->क्रमmat->num_planes)
		वापस 0;

	वापस stride / skl_plane_stride_mult(fb, color_plane, rotation);
पूर्ण

अटल व्योम
skl_disable_plane(काष्ठा पूर्णांकel_plane *plane,
		  स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(plane->base.dev);
	क्रमागत plane_id plane_id = plane->id;
	क्रमागत pipe pipe = plane->pipe;
	अचिन्हित दीर्घ irqflags;

	spin_lock_irqsave(&dev_priv->uncore.lock, irqflags);

	अगर (icl_is_hdr_plane(dev_priv, plane_id))
		पूर्णांकel_de_ग_लिखो_fw(dev_priv, PLANE_CUS_CTL(pipe, plane_id), 0);

	skl_ग_लिखो_plane_wm(plane, crtc_state);

	पूर्णांकel_de_ग_लिखो_fw(dev_priv, PLANE_CTL(pipe, plane_id), 0);
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, PLANE_SURF(pipe, plane_id), 0);

	spin_unlock_irqrestore(&dev_priv->uncore.lock, irqflags);
पूर्ण

अटल bool
skl_plane_get_hw_state(काष्ठा पूर्णांकel_plane *plane,
		       क्रमागत pipe *pipe)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(plane->base.dev);
	क्रमागत पूर्णांकel_display_घातer_करोमुख्य घातer_करोमुख्य;
	क्रमागत plane_id plane_id = plane->id;
	पूर्णांकel_wakeref_t wakeref;
	bool ret;

	घातer_करोमुख्य = POWER_DOMAIN_PIPE(plane->pipe);
	wakeref = पूर्णांकel_display_घातer_get_अगर_enabled(dev_priv, घातer_करोमुख्य);
	अगर (!wakeref)
		वापस false;

	ret = पूर्णांकel_de_पढ़ो(dev_priv, PLANE_CTL(plane->pipe, plane_id)) & PLANE_CTL_ENABLE;

	*pipe = plane->pipe;

	पूर्णांकel_display_घातer_put(dev_priv, घातer_करोमुख्य, wakeref);

	वापस ret;
पूर्ण

अटल u32 skl_plane_ctl_क्रमmat(u32 pixel_क्रमmat)
अणु
	चयन (pixel_क्रमmat) अणु
	हाल DRM_FORMAT_C8:
		वापस PLANE_CTL_FORMAT_INDEXED;
	हाल DRM_FORMAT_RGB565:
		वापस PLANE_CTL_FORMAT_RGB_565;
	हाल DRM_FORMAT_XBGR8888:
	हाल DRM_FORMAT_ABGR8888:
		वापस PLANE_CTL_FORMAT_XRGB_8888 | PLANE_CTL_ORDER_RGBX;
	हाल DRM_FORMAT_XRGB8888:
	हाल DRM_FORMAT_ARGB8888:
		वापस PLANE_CTL_FORMAT_XRGB_8888;
	हाल DRM_FORMAT_XBGR2101010:
	हाल DRM_FORMAT_ABGR2101010:
		वापस PLANE_CTL_FORMAT_XRGB_2101010 | PLANE_CTL_ORDER_RGBX;
	हाल DRM_FORMAT_XRGB2101010:
	हाल DRM_FORMAT_ARGB2101010:
		वापस PLANE_CTL_FORMAT_XRGB_2101010;
	हाल DRM_FORMAT_XBGR16161616F:
	हाल DRM_FORMAT_ABGR16161616F:
		वापस PLANE_CTL_FORMAT_XRGB_16161616F | PLANE_CTL_ORDER_RGBX;
	हाल DRM_FORMAT_XRGB16161616F:
	हाल DRM_FORMAT_ARGB16161616F:
		वापस PLANE_CTL_FORMAT_XRGB_16161616F;
	हाल DRM_FORMAT_XYUV8888:
		वापस PLANE_CTL_FORMAT_XYUV;
	हाल DRM_FORMAT_YUYV:
		वापस PLANE_CTL_FORMAT_YUV422 | PLANE_CTL_YUV422_YUYV;
	हाल DRM_FORMAT_YVYU:
		वापस PLANE_CTL_FORMAT_YUV422 | PLANE_CTL_YUV422_YVYU;
	हाल DRM_FORMAT_UYVY:
		वापस PLANE_CTL_FORMAT_YUV422 | PLANE_CTL_YUV422_UYVY;
	हाल DRM_FORMAT_VYUY:
		वापस PLANE_CTL_FORMAT_YUV422 | PLANE_CTL_YUV422_VYUY;
	हाल DRM_FORMAT_NV12:
		वापस PLANE_CTL_FORMAT_NV12;
	हाल DRM_FORMAT_P010:
		वापस PLANE_CTL_FORMAT_P010;
	हाल DRM_FORMAT_P012:
		वापस PLANE_CTL_FORMAT_P012;
	हाल DRM_FORMAT_P016:
		वापस PLANE_CTL_FORMAT_P016;
	हाल DRM_FORMAT_Y210:
		वापस PLANE_CTL_FORMAT_Y210;
	हाल DRM_FORMAT_Y212:
		वापस PLANE_CTL_FORMAT_Y212;
	हाल DRM_FORMAT_Y216:
		वापस PLANE_CTL_FORMAT_Y216;
	हाल DRM_FORMAT_XVYU2101010:
		वापस PLANE_CTL_FORMAT_Y410;
	हाल DRM_FORMAT_XVYU12_16161616:
		वापस PLANE_CTL_FORMAT_Y412;
	हाल DRM_FORMAT_XVYU16161616:
		वापस PLANE_CTL_FORMAT_Y416;
	शेष:
		MISSING_CASE(pixel_क्रमmat);
	पूर्ण

	वापस 0;
पूर्ण

अटल u32 skl_plane_ctl_alpha(स्थिर काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	अगर (!plane_state->hw.fb->क्रमmat->has_alpha)
		वापस PLANE_CTL_ALPHA_DISABLE;

	चयन (plane_state->hw.pixel_blend_mode) अणु
	हाल DRM_MODE_BLEND_PIXEL_NONE:
		वापस PLANE_CTL_ALPHA_DISABLE;
	हाल DRM_MODE_BLEND_PREMULTI:
		वापस PLANE_CTL_ALPHA_SW_PREMULTIPLY;
	हाल DRM_MODE_BLEND_COVERAGE:
		वापस PLANE_CTL_ALPHA_HW_PREMULTIPLY;
	शेष:
		MISSING_CASE(plane_state->hw.pixel_blend_mode);
		वापस PLANE_CTL_ALPHA_DISABLE;
	पूर्ण
पूर्ण

अटल u32 glk_plane_color_ctl_alpha(स्थिर काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	अगर (!plane_state->hw.fb->क्रमmat->has_alpha)
		वापस PLANE_COLOR_ALPHA_DISABLE;

	चयन (plane_state->hw.pixel_blend_mode) अणु
	हाल DRM_MODE_BLEND_PIXEL_NONE:
		वापस PLANE_COLOR_ALPHA_DISABLE;
	हाल DRM_MODE_BLEND_PREMULTI:
		वापस PLANE_COLOR_ALPHA_SW_PREMULTIPLY;
	हाल DRM_MODE_BLEND_COVERAGE:
		वापस PLANE_COLOR_ALPHA_HW_PREMULTIPLY;
	शेष:
		MISSING_CASE(plane_state->hw.pixel_blend_mode);
		वापस PLANE_COLOR_ALPHA_DISABLE;
	पूर्ण
पूर्ण

अटल u32 skl_plane_ctl_tiling(u64 fb_modअगरier)
अणु
	चयन (fb_modअगरier) अणु
	हाल DRM_FORMAT_MOD_LINEAR:
		अवरोध;
	हाल I915_FORMAT_MOD_X_TILED:
		वापस PLANE_CTL_TILED_X;
	हाल I915_FORMAT_MOD_Y_TILED:
		वापस PLANE_CTL_TILED_Y;
	हाल I915_FORMAT_MOD_Y_TILED_CCS:
	हाल I915_FORMAT_MOD_Y_TILED_GEN12_RC_CCS_CC:
		वापस PLANE_CTL_TILED_Y | PLANE_CTL_RENDER_DECOMPRESSION_ENABLE;
	हाल I915_FORMAT_MOD_Y_TILED_GEN12_RC_CCS:
		वापस PLANE_CTL_TILED_Y |
		       PLANE_CTL_RENDER_DECOMPRESSION_ENABLE |
		       PLANE_CTL_CLEAR_COLOR_DISABLE;
	हाल I915_FORMAT_MOD_Y_TILED_GEN12_MC_CCS:
		वापस PLANE_CTL_TILED_Y | PLANE_CTL_MEDIA_DECOMPRESSION_ENABLE;
	हाल I915_FORMAT_MOD_Yf_TILED:
		वापस PLANE_CTL_TILED_YF;
	हाल I915_FORMAT_MOD_Yf_TILED_CCS:
		वापस PLANE_CTL_TILED_YF | PLANE_CTL_RENDER_DECOMPRESSION_ENABLE;
	शेष:
		MISSING_CASE(fb_modअगरier);
	पूर्ण

	वापस 0;
पूर्ण

अटल u32 skl_plane_ctl_rotate(अचिन्हित पूर्णांक rotate)
अणु
	चयन (rotate) अणु
	हाल DRM_MODE_ROTATE_0:
		अवरोध;
	/*
	 * DRM_MODE_ROTATE_ is counter घड़ीwise to stay compatible with Xअक्रमr
	 * जबतक i915 HW rotation is घड़ीwise, thats why this swapping.
	 */
	हाल DRM_MODE_ROTATE_90:
		वापस PLANE_CTL_ROTATE_270;
	हाल DRM_MODE_ROTATE_180:
		वापस PLANE_CTL_ROTATE_180;
	हाल DRM_MODE_ROTATE_270:
		वापस PLANE_CTL_ROTATE_90;
	शेष:
		MISSING_CASE(rotate);
	पूर्ण

	वापस 0;
पूर्ण

अटल u32 cnl_plane_ctl_flip(अचिन्हित पूर्णांक reflect)
अणु
	चयन (reflect) अणु
	हाल 0:
		अवरोध;
	हाल DRM_MODE_REFLECT_X:
		वापस PLANE_CTL_FLIP_HORIZONTAL;
	हाल DRM_MODE_REFLECT_Y:
	शेष:
		MISSING_CASE(reflect);
	पूर्ण

	वापस 0;
पूर्ण

अटल u32 skl_plane_ctl_crtc(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc_state->uapi.crtc->dev);
	u32 plane_ctl = 0;

	अगर (DISPLAY_VER(dev_priv) >= 10)
		वापस plane_ctl;

	अगर (crtc_state->gamma_enable)
		plane_ctl |= PLANE_CTL_PIPE_GAMMA_ENABLE;

	अगर (crtc_state->csc_enable)
		plane_ctl |= PLANE_CTL_PIPE_CSC_ENABLE;

	वापस plane_ctl;
पूर्ण

अटल u32 skl_plane_ctl(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			 स्थिर काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv =
		to_i915(plane_state->uapi.plane->dev);
	स्थिर काष्ठा drm_framebuffer *fb = plane_state->hw.fb;
	अचिन्हित पूर्णांक rotation = plane_state->hw.rotation;
	स्थिर काष्ठा drm_पूर्णांकel_sprite_colorkey *key = &plane_state->ckey;
	u32 plane_ctl;

	plane_ctl = PLANE_CTL_ENABLE;

	अगर (DISPLAY_VER(dev_priv) < 10 && !IS_GEMINILAKE(dev_priv)) अणु
		plane_ctl |= skl_plane_ctl_alpha(plane_state);
		plane_ctl |= PLANE_CTL_PLANE_GAMMA_DISABLE;

		अगर (plane_state->hw.color_encoding == DRM_COLOR_YCBCR_BT709)
			plane_ctl |= PLANE_CTL_YUV_TO_RGB_CSC_FORMAT_BT709;

		अगर (plane_state->hw.color_range == DRM_COLOR_YCBCR_FULL_RANGE)
			plane_ctl |= PLANE_CTL_YUV_RANGE_CORRECTION_DISABLE;
	पूर्ण

	plane_ctl |= skl_plane_ctl_क्रमmat(fb->क्रमmat->क्रमmat);
	plane_ctl |= skl_plane_ctl_tiling(fb->modअगरier);
	plane_ctl |= skl_plane_ctl_rotate(rotation & DRM_MODE_ROTATE_MASK);

	अगर (DISPLAY_VER(dev_priv) >= 11 || IS_CANNONLAKE(dev_priv))
		plane_ctl |= cnl_plane_ctl_flip(rotation &
						DRM_MODE_REFLECT_MASK);

	अगर (key->flags & I915_SET_COLORKEY_DESTINATION)
		plane_ctl |= PLANE_CTL_KEY_ENABLE_DESTINATION;
	अन्यथा अगर (key->flags & I915_SET_COLORKEY_SOURCE)
		plane_ctl |= PLANE_CTL_KEY_ENABLE_SOURCE;

	वापस plane_ctl;
पूर्ण

अटल u32 glk_plane_color_ctl_crtc(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc_state->uapi.crtc->dev);
	u32 plane_color_ctl = 0;

	अगर (DISPLAY_VER(dev_priv) >= 11)
		वापस plane_color_ctl;

	अगर (crtc_state->gamma_enable)
		plane_color_ctl |= PLANE_COLOR_PIPE_GAMMA_ENABLE;

	अगर (crtc_state->csc_enable)
		plane_color_ctl |= PLANE_COLOR_PIPE_CSC_ENABLE;

	वापस plane_color_ctl;
पूर्ण

अटल u32 glk_plane_color_ctl(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			       स्थिर काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv =
		to_i915(plane_state->uapi.plane->dev);
	स्थिर काष्ठा drm_framebuffer *fb = plane_state->hw.fb;
	काष्ठा पूर्णांकel_plane *plane = to_पूर्णांकel_plane(plane_state->uapi.plane);
	u32 plane_color_ctl = 0;

	plane_color_ctl |= PLANE_COLOR_PLANE_GAMMA_DISABLE;
	plane_color_ctl |= glk_plane_color_ctl_alpha(plane_state);

	अगर (fb->क्रमmat->is_yuv && !icl_is_hdr_plane(dev_priv, plane->id)) अणु
		चयन (plane_state->hw.color_encoding) अणु
		हाल DRM_COLOR_YCBCR_BT709:
			plane_color_ctl |= PLANE_COLOR_CSC_MODE_YUV709_TO_RGB709;
			अवरोध;
		हाल DRM_COLOR_YCBCR_BT2020:
			plane_color_ctl |=
				PLANE_COLOR_CSC_MODE_YUV2020_TO_RGB2020;
			अवरोध;
		शेष:
			plane_color_ctl |=
				PLANE_COLOR_CSC_MODE_YUV601_TO_RGB601;
		पूर्ण
		अगर (plane_state->hw.color_range == DRM_COLOR_YCBCR_FULL_RANGE)
			plane_color_ctl |= PLANE_COLOR_YUV_RANGE_CORRECTION_DISABLE;
	पूर्ण अन्यथा अगर (fb->क्रमmat->is_yuv) अणु
		plane_color_ctl |= PLANE_COLOR_INPUT_CSC_ENABLE;
		अगर (plane_state->hw.color_range == DRM_COLOR_YCBCR_FULL_RANGE)
			plane_color_ctl |= PLANE_COLOR_YUV_RANGE_CORRECTION_DISABLE;
	पूर्ण

	वापस plane_color_ctl;
पूर्ण

अटल व्योम
skl_program_plane(काष्ठा पूर्णांकel_plane *plane,
		  स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
		  स्थिर काष्ठा पूर्णांकel_plane_state *plane_state,
		  पूर्णांक color_plane)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(plane->base.dev);
	क्रमागत plane_id plane_id = plane->id;
	क्रमागत pipe pipe = plane->pipe;
	स्थिर काष्ठा drm_पूर्णांकel_sprite_colorkey *key = &plane_state->ckey;
	u32 surf_addr = plane_state->view.color_plane[color_plane].offset;
	u32 stride = skl_plane_stride(plane_state, color_plane);
	स्थिर काष्ठा drm_framebuffer *fb = plane_state->hw.fb;
	पूर्णांक aux_plane = skl_मुख्य_to_aux_plane(fb, color_plane);
	पूर्णांक crtc_x = plane_state->uapi.dst.x1;
	पूर्णांक crtc_y = plane_state->uapi.dst.y1;
	u32 x = plane_state->view.color_plane[color_plane].x;
	u32 y = plane_state->view.color_plane[color_plane].y;
	u32 src_w = drm_rect_width(&plane_state->uapi.src) >> 16;
	u32 src_h = drm_rect_height(&plane_state->uapi.src) >> 16;
	u8 alpha = plane_state->hw.alpha >> 8;
	u32 plane_color_ctl = 0, aux_dist = 0;
	अचिन्हित दीर्घ irqflags;
	u32 keymsk, keymax;
	u32 plane_ctl = plane_state->ctl;

	plane_ctl |= skl_plane_ctl_crtc(crtc_state);

	अगर (DISPLAY_VER(dev_priv) >= 10)
		plane_color_ctl = plane_state->color_ctl |
			glk_plane_color_ctl_crtc(crtc_state);

	/* Sizes are 0 based */
	src_w--;
	src_h--;

	keymax = (key->max_value & 0xffffff) | PLANE_KEYMAX_ALPHA(alpha);

	keymsk = key->channel_mask & 0x7ffffff;
	अगर (alpha < 0xff)
		keymsk |= PLANE_KEYMSK_ALPHA_ENABLE;

	/* The scaler will handle the output position */
	अगर (plane_state->scaler_id >= 0) अणु
		crtc_x = 0;
		crtc_y = 0;
	पूर्ण

	अगर (aux_plane) अणु
		aux_dist = plane_state->view.color_plane[aux_plane].offset - surf_addr;

		अगर (DISPLAY_VER(dev_priv) < 12)
			aux_dist |= skl_plane_stride(plane_state, aux_plane);
	पूर्ण

	spin_lock_irqsave(&dev_priv->uncore.lock, irqflags);

	पूर्णांकel_de_ग_लिखो_fw(dev_priv, PLANE_STRIDE(pipe, plane_id), stride);
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, PLANE_POS(pipe, plane_id),
			  (crtc_y << 16) | crtc_x);
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, PLANE_SIZE(pipe, plane_id),
			  (src_h << 16) | src_w);

	पूर्णांकel_de_ग_लिखो_fw(dev_priv, PLANE_AUX_DIST(pipe, plane_id), aux_dist);

	अगर (icl_is_hdr_plane(dev_priv, plane_id))
		पूर्णांकel_de_ग_लिखो_fw(dev_priv, PLANE_CUS_CTL(pipe, plane_id),
				  plane_state->cus_ctl);

	अगर (DISPLAY_VER(dev_priv) >= 10)
		पूर्णांकel_de_ग_लिखो_fw(dev_priv, PLANE_COLOR_CTL(pipe, plane_id),
				  plane_color_ctl);

	अगर (fb->क्रमmat->is_yuv && icl_is_hdr_plane(dev_priv, plane_id))
		icl_program_input_csc(plane, crtc_state, plane_state);

	अगर (fb->modअगरier == I915_FORMAT_MOD_Y_TILED_GEN12_RC_CCS_CC)
		पूर्णांकel_uncore_ग_लिखो64_fw(&dev_priv->uncore,
					PLANE_CC_VAL(pipe, plane_id), plane_state->ccval);

	skl_ग_लिखो_plane_wm(plane, crtc_state);

	पूर्णांकel_de_ग_लिखो_fw(dev_priv, PLANE_KEYVAL(pipe, plane_id),
			  key->min_value);
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, PLANE_KEYMSK(pipe, plane_id), keymsk);
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, PLANE_KEYMAX(pipe, plane_id), keymax);

	पूर्णांकel_de_ग_लिखो_fw(dev_priv, PLANE_OFFSET(pipe, plane_id),
			  (y << 16) | x);

	अगर (DISPLAY_VER(dev_priv) < 11)
		पूर्णांकel_de_ग_लिखो_fw(dev_priv, PLANE_AUX_OFFSET(pipe, plane_id),
				  (plane_state->view.color_plane[1].y << 16) |
				   plane_state->view.color_plane[1].x);

	अगर (!drm_atomic_crtc_needs_modeset(&crtc_state->uapi))
		पूर्णांकel_psr2_program_plane_sel_fetch(plane, crtc_state, plane_state, color_plane);

	/*
	 * The control रेजिस्टर self-arms अगर the plane was previously
	 * disabled. Try to make the plane enable atomic by writing
	 * the control रेजिस्टर just beक्रमe the surface रेजिस्टर.
	 */
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, PLANE_CTL(pipe, plane_id), plane_ctl);
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, PLANE_SURF(pipe, plane_id),
			  पूर्णांकel_plane_ggtt_offset(plane_state) + surf_addr);

	अगर (plane_state->scaler_id >= 0)
		skl_program_plane_scaler(plane, crtc_state, plane_state);

	spin_unlock_irqrestore(&dev_priv->uncore.lock, irqflags);
पूर्ण

अटल व्योम
skl_plane_async_flip(काष्ठा पूर्णांकel_plane *plane,
		     स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
		     स्थिर काष्ठा पूर्णांकel_plane_state *plane_state,
		     bool async_flip)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(plane->base.dev);
	अचिन्हित दीर्घ irqflags;
	क्रमागत plane_id plane_id = plane->id;
	क्रमागत pipe pipe = plane->pipe;
	u32 surf_addr = plane_state->view.color_plane[0].offset;
	u32 plane_ctl = plane_state->ctl;

	plane_ctl |= skl_plane_ctl_crtc(crtc_state);

	अगर (async_flip)
		plane_ctl |= PLANE_CTL_ASYNC_FLIP;

	spin_lock_irqsave(&dev_priv->uncore.lock, irqflags);

	पूर्णांकel_de_ग_लिखो_fw(dev_priv, PLANE_CTL(pipe, plane_id), plane_ctl);
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, PLANE_SURF(pipe, plane_id),
			  पूर्णांकel_plane_ggtt_offset(plane_state) + surf_addr);

	spin_unlock_irqrestore(&dev_priv->uncore.lock, irqflags);
पूर्ण

अटल व्योम
skl_update_plane(काष्ठा पूर्णांकel_plane *plane,
		 स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
		 स्थिर काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	पूर्णांक color_plane = 0;

	अगर (plane_state->planar_linked_plane && !plane_state->planar_slave)
		/* Program the UV plane on planar master */
		color_plane = 1;

	skl_program_plane(plane, crtc_state, plane_state, color_plane);
पूर्ण

अटल bool पूर्णांकel_क्रमmat_is_p01x(u32 क्रमmat)
अणु
	चयन (क्रमmat) अणु
	हाल DRM_FORMAT_P010:
	हाल DRM_FORMAT_P012:
	हाल DRM_FORMAT_P016:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक skl_plane_check_fb(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			      स्थिर काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	काष्ठा पूर्णांकel_plane *plane = to_पूर्णांकel_plane(plane_state->uapi.plane);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(plane->base.dev);
	स्थिर काष्ठा drm_framebuffer *fb = plane_state->hw.fb;
	अचिन्हित पूर्णांक rotation = plane_state->hw.rotation;
	काष्ठा drm_क्रमmat_name_buf क्रमmat_name;

	अगर (!fb)
		वापस 0;

	अगर (rotation & ~(DRM_MODE_ROTATE_0 | DRM_MODE_ROTATE_180) &&
	    is_ccs_modअगरier(fb->modअगरier)) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "RC support only with 0/180 degree rotation (%x)\n",
			    rotation);
		वापस -EINVAL;
	पूर्ण

	अगर (rotation & DRM_MODE_REFLECT_X &&
	    fb->modअगरier == DRM_FORMAT_MOD_LINEAR) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "horizontal flip is not supported with linear surface formats\n");
		वापस -EINVAL;
	पूर्ण

	अगर (drm_rotation_90_or_270(rotation)) अणु
		अगर (fb->modअगरier != I915_FORMAT_MOD_Y_TILED &&
		    fb->modअगरier != I915_FORMAT_MOD_Yf_TILED) अणु
			drm_dbg_kms(&dev_priv->drm,
				    "Y/Yf tiling required for 90/270!\n");
			वापस -EINVAL;
		पूर्ण

		/*
		 * 90/270 is not allowed with RGB64 16:16:16:16 and
		 * Indexed 8-bit. RGB 16-bit 5:6:5 is allowed gen11 onwards.
		 */
		चयन (fb->क्रमmat->क्रमmat) अणु
		हाल DRM_FORMAT_RGB565:
			अगर (DISPLAY_VER(dev_priv) >= 11)
				अवरोध;
			fallthrough;
		हाल DRM_FORMAT_C8:
		हाल DRM_FORMAT_XRGB16161616F:
		हाल DRM_FORMAT_XBGR16161616F:
		हाल DRM_FORMAT_ARGB16161616F:
		हाल DRM_FORMAT_ABGR16161616F:
		हाल DRM_FORMAT_Y210:
		हाल DRM_FORMAT_Y212:
		हाल DRM_FORMAT_Y216:
		हाल DRM_FORMAT_XVYU12_16161616:
		हाल DRM_FORMAT_XVYU16161616:
			drm_dbg_kms(&dev_priv->drm,
				    "Unsupported pixel format %s for 90/270!\n",
				    drm_get_क्रमmat_name(fb->क्रमmat->क्रमmat,
							&क्रमmat_name));
			वापस -EINVAL;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	/* Y-tiling is not supported in IF-ID Interlace mode */
	अगर (crtc_state->hw.enable &&
	    crtc_state->hw.adjusted_mode.flags & DRM_MODE_FLAG_INTERLACE &&
	    (fb->modअगरier == I915_FORMAT_MOD_Y_TILED ||
	     fb->modअगरier == I915_FORMAT_MOD_Yf_TILED ||
	     fb->modअगरier == I915_FORMAT_MOD_Y_TILED_CCS ||
	     fb->modअगरier == I915_FORMAT_MOD_Yf_TILED_CCS ||
	     fb->modअगरier == I915_FORMAT_MOD_Y_TILED_GEN12_RC_CCS ||
	     fb->modअगरier == I915_FORMAT_MOD_Y_TILED_GEN12_MC_CCS ||
	     fb->modअगरier == I915_FORMAT_MOD_Y_TILED_GEN12_RC_CCS_CC)) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "Y/Yf tiling not supported in IF-ID mode\n");
		वापस -EINVAL;
	पूर्ण

	/* Wa_1606054188:tgl,adl-s */
	अगर ((IS_ALDERLAKE_S(dev_priv) || IS_TIGERLAKE(dev_priv)) &&
	    plane_state->ckey.flags & I915_SET_COLORKEY_SOURCE &&
	    पूर्णांकel_क्रमmat_is_p01x(fb->क्रमmat->क्रमmat)) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "Source color keying not supported with P01x formats\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक skl_plane_check_dst_coordinates(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
					   स्थिर काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv =
		to_i915(plane_state->uapi.plane->dev);
	पूर्णांक crtc_x = plane_state->uapi.dst.x1;
	पूर्णांक crtc_w = drm_rect_width(&plane_state->uapi.dst);
	पूर्णांक pipe_src_w = crtc_state->pipe_src_w;

	/*
	 * Display WA #1175: cnl,glk
	 * Planes other than the cursor may cause FIFO underflow and display
	 * corruption अगर starting less than 4 pixels from the right edge of
	 * the screen.
	 * Besides the above WA fix the similar problem, where planes other
	 * than the cursor ending less than 4 pixels from the left edge of the
	 * screen may cause FIFO underflow and display corruption.
	 */
	अगर (IS_DISPLAY_VER(dev_priv, 10) &&
	    (crtc_x + crtc_w < 4 || crtc_x > pipe_src_w - 4)) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "requested plane X %s position %d invalid (valid range %d-%d)\n",
			    crtc_x + crtc_w < 4 ? "end" : "start",
			    crtc_x + crtc_w < 4 ? crtc_x + crtc_w : crtc_x,
			    4, pipe_src_w - 4);
		वापस -दुस्फल;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक skl_plane_check_nv12_rotation(स्थिर काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	स्थिर काष्ठा drm_framebuffer *fb = plane_state->hw.fb;
	अचिन्हित पूर्णांक rotation = plane_state->hw.rotation;
	पूर्णांक src_w = drm_rect_width(&plane_state->uapi.src) >> 16;

	/* Display WA #1106 */
	अगर (पूर्णांकel_क्रमmat_info_is_yuv_semiplanar(fb->क्रमmat, fb->modअगरier) &&
	    src_w & 3 &&
	    (rotation == DRM_MODE_ROTATE_270 ||
	     rotation == (DRM_MODE_REFLECT_X | DRM_MODE_ROTATE_90))) अणु
		DRM_DEBUG_KMS("src width must be multiple of 4 for rotated planar YUV\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक skl_plane_max_scale(काष्ठा drm_i915_निजी *dev_priv,
			       स्थिर काष्ठा drm_framebuffer *fb)
अणु
	/*
	 * We करोn't yet know the final source width nor
	 * whether we can use the HQ scaler mode. Assume
	 * the best हाल.
	 * FIXME need to properly check this later.
	 */
	अगर (DISPLAY_VER(dev_priv) >= 10 ||
	    !पूर्णांकel_क्रमmat_info_is_yuv_semiplanar(fb->क्रमmat, fb->modअगरier))
		वापस 0x30000 - 1;
	अन्यथा
		वापस 0x20000 - 1;
पूर्ण

अटल पूर्णांक पूर्णांकel_plane_min_width(काष्ठा पूर्णांकel_plane *plane,
				 स्थिर काष्ठा drm_framebuffer *fb,
				 पूर्णांक color_plane,
				 अचिन्हित पूर्णांक rotation)
अणु
	अगर (plane->min_width)
		वापस plane->min_width(fb, color_plane, rotation);
	अन्यथा
		वापस 1;
पूर्ण

अटल पूर्णांक पूर्णांकel_plane_max_width(काष्ठा पूर्णांकel_plane *plane,
				 स्थिर काष्ठा drm_framebuffer *fb,
				 पूर्णांक color_plane,
				 अचिन्हित पूर्णांक rotation)
अणु
	अगर (plane->max_width)
		वापस plane->max_width(fb, color_plane, rotation);
	अन्यथा
		वापस पूर्णांक_उच्च;
पूर्ण

अटल पूर्णांक पूर्णांकel_plane_max_height(काष्ठा पूर्णांकel_plane *plane,
				  स्थिर काष्ठा drm_framebuffer *fb,
				  पूर्णांक color_plane,
				  अचिन्हित पूर्णांक rotation)
अणु
	अगर (plane->max_height)
		वापस plane->max_height(fb, color_plane, rotation);
	अन्यथा
		वापस पूर्णांक_उच्च;
पूर्ण

अटल bool
skl_check_मुख्य_ccs_coordinates(काष्ठा पूर्णांकel_plane_state *plane_state,
			       पूर्णांक मुख्य_x, पूर्णांक मुख्य_y, u32 मुख्य_offset,
			       पूर्णांक ccs_plane)
अणु
	स्थिर काष्ठा drm_framebuffer *fb = plane_state->hw.fb;
	पूर्णांक aux_x = plane_state->view.color_plane[ccs_plane].x;
	पूर्णांक aux_y = plane_state->view.color_plane[ccs_plane].y;
	u32 aux_offset = plane_state->view.color_plane[ccs_plane].offset;
	u32 alignment = पूर्णांकel_surf_alignment(fb, ccs_plane);
	पूर्णांक hsub;
	पूर्णांक vsub;

	पूर्णांकel_fb_plane_get_subsampling(&hsub, &vsub, fb, ccs_plane);
	जबतक (aux_offset >= मुख्य_offset && aux_y <= मुख्य_y) अणु
		पूर्णांक x, y;

		अगर (aux_x == मुख्य_x && aux_y == मुख्य_y)
			अवरोध;

		अगर (aux_offset == 0)
			अवरोध;

		x = aux_x / hsub;
		y = aux_y / vsub;
		aux_offset = पूर्णांकel_plane_adjust_aligned_offset(&x, &y,
							       plane_state,
							       ccs_plane,
							       aux_offset,
							       aux_offset -
								alignment);
		aux_x = x * hsub + aux_x % hsub;
		aux_y = y * vsub + aux_y % vsub;
	पूर्ण

	अगर (aux_x != मुख्य_x || aux_y != मुख्य_y)
		वापस false;

	plane_state->view.color_plane[ccs_plane].offset = aux_offset;
	plane_state->view.color_plane[ccs_plane].x = aux_x;
	plane_state->view.color_plane[ccs_plane].y = aux_y;

	वापस true;
पूर्ण


पूर्णांक skl_calc_मुख्य_surface_offset(स्थिर काष्ठा पूर्णांकel_plane_state *plane_state,
				 पूर्णांक *x, पूर्णांक *y, u32 *offset)
अणु
	काष्ठा पूर्णांकel_plane *plane = to_पूर्णांकel_plane(plane_state->uapi.plane);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(plane->base.dev);
	स्थिर काष्ठा drm_framebuffer *fb = plane_state->hw.fb;
	स्थिर पूर्णांक aux_plane = skl_मुख्य_to_aux_plane(fb, 0);
	स्थिर u32 aux_offset = plane_state->view.color_plane[aux_plane].offset;
	स्थिर u32 alignment = पूर्णांकel_surf_alignment(fb, 0);
	स्थिर पूर्णांक w = drm_rect_width(&plane_state->uapi.src) >> 16;

	पूर्णांकel_add_fb_offsets(x, y, plane_state, 0);
	*offset = पूर्णांकel_plane_compute_aligned_offset(x, y, plane_state, 0);
	अगर (drm_WARN_ON(&dev_priv->drm, alignment && !is_घातer_of_2(alignment)))
		वापस -EINVAL;

	/*
	 * AUX surface offset is specअगरied as the distance from the
	 * मुख्य surface offset, and it must be non-negative. Make
	 * sure that is what we will get.
	 */
	अगर (aux_plane && *offset > aux_offset)
		*offset = पूर्णांकel_plane_adjust_aligned_offset(x, y, plane_state, 0,
							    *offset,
							    aux_offset & ~(alignment - 1));

	/*
	 * When using an X-tiled surface, the plane blows up
	 * अगर the x offset + width exceed the stride.
	 *
	 * TODO: linear and Y-tiled seem fine, Yf untested,
	 */
	अगर (fb->modअगरier == I915_FORMAT_MOD_X_TILED) अणु
		पूर्णांक cpp = fb->क्रमmat->cpp[0];

		जबतक ((*x + w) * cpp > plane_state->view.color_plane[0].stride) अणु
			अगर (*offset == 0) अणु
				drm_dbg_kms(&dev_priv->drm,
					    "Unable to find suitable display surface offset due to X-tiling\n");
				वापस -EINVAL;
			पूर्ण

			*offset = पूर्णांकel_plane_adjust_aligned_offset(x, y, plane_state, 0,
								    *offset,
								    *offset - alignment);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक skl_check_मुख्य_surface(काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	काष्ठा पूर्णांकel_plane *plane = to_पूर्णांकel_plane(plane_state->uapi.plane);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(plane->base.dev);
	स्थिर काष्ठा drm_framebuffer *fb = plane_state->hw.fb;
	स्थिर अचिन्हित पूर्णांक rotation = plane_state->hw.rotation;
	पूर्णांक x = plane_state->uapi.src.x1 >> 16;
	पूर्णांक y = plane_state->uapi.src.y1 >> 16;
	स्थिर पूर्णांक w = drm_rect_width(&plane_state->uapi.src) >> 16;
	स्थिर पूर्णांक h = drm_rect_height(&plane_state->uapi.src) >> 16;
	स्थिर पूर्णांक min_width = पूर्णांकel_plane_min_width(plane, fb, 0, rotation);
	स्थिर पूर्णांक max_width = पूर्णांकel_plane_max_width(plane, fb, 0, rotation);
	स्थिर पूर्णांक max_height = पूर्णांकel_plane_max_height(plane, fb, 0, rotation);
	स्थिर पूर्णांक aux_plane = skl_मुख्य_to_aux_plane(fb, 0);
	स्थिर u32 alignment = पूर्णांकel_surf_alignment(fb, 0);
	u32 offset;
	पूर्णांक ret;

	अगर (w > max_width || w < min_width || h > max_height) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "requested Y/RGB source size %dx%d outside limits (min: %dx1 max: %dx%d)\n",
			    w, h, min_width, max_width, max_height);
		वापस -EINVAL;
	पूर्ण

	ret = skl_calc_मुख्य_surface_offset(plane_state, &x, &y, &offset);
	अगर (ret)
		वापस ret;

	/*
	 * CCS AUX surface करोesn't have its own x/y offsets, we must make sure
	 * they match with the मुख्य surface x/y offsets.
	 */
	अगर (is_ccs_modअगरier(fb->modअगरier)) अणु
		जबतक (!skl_check_मुख्य_ccs_coordinates(plane_state, x, y,
						       offset, aux_plane)) अणु
			अगर (offset == 0)
				अवरोध;

			offset = पूर्णांकel_plane_adjust_aligned_offset(&x, &y, plane_state, 0,
								   offset, offset - alignment);
		पूर्ण

		अगर (x != plane_state->view.color_plane[aux_plane].x ||
		    y != plane_state->view.color_plane[aux_plane].y) अणु
			drm_dbg_kms(&dev_priv->drm,
				    "Unable to find suitable display surface offset due to CCS\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	drm_WARN_ON(&dev_priv->drm, x > 8191 || y > 8191);

	plane_state->view.color_plane[0].offset = offset;
	plane_state->view.color_plane[0].x = x;
	plane_state->view.color_plane[0].y = y;

	/*
	 * Put the final coordinates back so that the src
	 * coordinate checks will see the right values.
	 */
	drm_rect_translate_to(&plane_state->uapi.src,
			      x << 16, y << 16);

	वापस 0;
पूर्ण

अटल पूर्णांक skl_check_nv12_aux_surface(काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	काष्ठा पूर्णांकel_plane *plane = to_पूर्णांकel_plane(plane_state->uapi.plane);
	काष्ठा drm_i915_निजी *i915 = to_i915(plane->base.dev);
	स्थिर काष्ठा drm_framebuffer *fb = plane_state->hw.fb;
	अचिन्हित पूर्णांक rotation = plane_state->hw.rotation;
	पूर्णांक uv_plane = 1;
	पूर्णांक max_width = पूर्णांकel_plane_max_width(plane, fb, uv_plane, rotation);
	पूर्णांक max_height = पूर्णांकel_plane_max_height(plane, fb, uv_plane, rotation);
	पूर्णांक x = plane_state->uapi.src.x1 >> 17;
	पूर्णांक y = plane_state->uapi.src.y1 >> 17;
	पूर्णांक w = drm_rect_width(&plane_state->uapi.src) >> 17;
	पूर्णांक h = drm_rect_height(&plane_state->uapi.src) >> 17;
	u32 offset;

	/* FIXME not quite sure how/अगर these apply to the chroma plane */
	अगर (w > max_width || h > max_height) अणु
		drm_dbg_kms(&i915->drm,
			    "CbCr source size %dx%d too big (limit %dx%d)\n",
			    w, h, max_width, max_height);
		वापस -EINVAL;
	पूर्ण

	पूर्णांकel_add_fb_offsets(&x, &y, plane_state, uv_plane);
	offset = पूर्णांकel_plane_compute_aligned_offset(&x, &y,
						    plane_state, uv_plane);

	अगर (is_ccs_modअगरier(fb->modअगरier)) अणु
		पूर्णांक ccs_plane = मुख्य_to_ccs_plane(fb, uv_plane);
		u32 aux_offset = plane_state->view.color_plane[ccs_plane].offset;
		u32 alignment = पूर्णांकel_surf_alignment(fb, uv_plane);

		अगर (offset > aux_offset)
			offset = पूर्णांकel_plane_adjust_aligned_offset(&x, &y,
								   plane_state,
								   uv_plane,
								   offset,
								   aux_offset & ~(alignment - 1));

		जबतक (!skl_check_मुख्य_ccs_coordinates(plane_state, x, y,
						       offset, ccs_plane)) अणु
			अगर (offset == 0)
				अवरोध;

			offset = पूर्णांकel_plane_adjust_aligned_offset(&x, &y,
								   plane_state,
								   uv_plane,
								   offset, offset - alignment);
		पूर्ण

		अगर (x != plane_state->view.color_plane[ccs_plane].x ||
		    y != plane_state->view.color_plane[ccs_plane].y) अणु
			drm_dbg_kms(&i915->drm,
				    "Unable to find suitable display surface offset due to CCS\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	drm_WARN_ON(&i915->drm, x > 8191 || y > 8191);

	plane_state->view.color_plane[uv_plane].offset = offset;
	plane_state->view.color_plane[uv_plane].x = x;
	plane_state->view.color_plane[uv_plane].y = y;

	वापस 0;
पूर्ण

अटल पूर्णांक skl_check_ccs_aux_surface(काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	स्थिर काष्ठा drm_framebuffer *fb = plane_state->hw.fb;
	पूर्णांक src_x = plane_state->uapi.src.x1 >> 16;
	पूर्णांक src_y = plane_state->uapi.src.y1 >> 16;
	u32 offset;
	पूर्णांक ccs_plane;

	क्रम (ccs_plane = 0; ccs_plane < fb->क्रमmat->num_planes; ccs_plane++) अणु
		पूर्णांक मुख्य_hsub, मुख्य_vsub;
		पूर्णांक hsub, vsub;
		पूर्णांक x, y;

		अगर (!is_ccs_plane(fb, ccs_plane) ||
		    is_gen12_ccs_cc_plane(fb, ccs_plane))
			जारी;

		पूर्णांकel_fb_plane_get_subsampling(&मुख्य_hsub, &मुख्य_vsub, fb,
					       skl_ccs_to_मुख्य_plane(fb, ccs_plane));
		पूर्णांकel_fb_plane_get_subsampling(&hsub, &vsub, fb, ccs_plane);

		hsub *= मुख्य_hsub;
		vsub *= मुख्य_vsub;
		x = src_x / hsub;
		y = src_y / vsub;

		पूर्णांकel_add_fb_offsets(&x, &y, plane_state, ccs_plane);

		offset = पूर्णांकel_plane_compute_aligned_offset(&x, &y,
							    plane_state,
							    ccs_plane);

		plane_state->view.color_plane[ccs_plane].offset = offset;
		plane_state->view.color_plane[ccs_plane].x = (x * hsub + src_x % hsub) / मुख्य_hsub;
		plane_state->view.color_plane[ccs_plane].y = (y * vsub + src_y % vsub) / मुख्य_vsub;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक skl_check_plane_surface(काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	स्थिर काष्ठा drm_framebuffer *fb = plane_state->hw.fb;
	पूर्णांक ret;

	ret = पूर्णांकel_plane_compute_gtt(plane_state);
	अगर (ret)
		वापस ret;

	अगर (!plane_state->uapi.visible)
		वापस 0;

	/*
	 * Handle the AUX surface first since the मुख्य surface setup depends on
	 * it.
	 */
	अगर (is_ccs_modअगरier(fb->modअगरier)) अणु
		ret = skl_check_ccs_aux_surface(plane_state);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (पूर्णांकel_क्रमmat_info_is_yuv_semiplanar(fb->क्रमmat,
						fb->modअगरier)) अणु
		ret = skl_check_nv12_aux_surface(plane_state);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = skl_check_मुख्य_surface(plane_state);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल bool skl_fb_scalable(स्थिर काष्ठा drm_framebuffer *fb)
अणु
	अगर (!fb)
		वापस false;

	चयन (fb->क्रमmat->क्रमmat) अणु
	हाल DRM_FORMAT_C8:
		वापस false;
	हाल DRM_FORMAT_XRGB16161616F:
	हाल DRM_FORMAT_ARGB16161616F:
	हाल DRM_FORMAT_XBGR16161616F:
	हाल DRM_FORMAT_ABGR16161616F:
		वापस DISPLAY_VER(to_i915(fb->dev)) >= 11;
	शेष:
		वापस true;
	पूर्ण
पूर्ण

अटल पूर्णांक skl_plane_check(काष्ठा पूर्णांकel_crtc_state *crtc_state,
			   काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	काष्ठा पूर्णांकel_plane *plane = to_पूर्णांकel_plane(plane_state->uapi.plane);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(plane->base.dev);
	स्थिर काष्ठा drm_framebuffer *fb = plane_state->hw.fb;
	पूर्णांक min_scale = DRM_PLANE_HELPER_NO_SCALING;
	पूर्णांक max_scale = DRM_PLANE_HELPER_NO_SCALING;
	पूर्णांक ret;

	ret = skl_plane_check_fb(crtc_state, plane_state);
	अगर (ret)
		वापस ret;

	/* use scaler when colorkey is not required */
	अगर (!plane_state->ckey.flags && skl_fb_scalable(fb)) अणु
		min_scale = 1;
		max_scale = skl_plane_max_scale(dev_priv, fb);
	पूर्ण

	ret = पूर्णांकel_atomic_plane_check_clipping(plane_state, crtc_state,
						min_scale, max_scale, true);
	अगर (ret)
		वापस ret;

	ret = skl_check_plane_surface(plane_state);
	अगर (ret)
		वापस ret;

	अगर (!plane_state->uapi.visible)
		वापस 0;

	ret = skl_plane_check_dst_coordinates(crtc_state, plane_state);
	अगर (ret)
		वापस ret;

	ret = पूर्णांकel_plane_check_src_coordinates(plane_state);
	अगर (ret)
		वापस ret;

	ret = skl_plane_check_nv12_rotation(plane_state);
	अगर (ret)
		वापस ret;

	/* HW only has 8 bits pixel precision, disable plane अगर invisible */
	अगर (!(plane_state->hw.alpha >> 8))
		plane_state->uapi.visible = false;

	plane_state->ctl = skl_plane_ctl(crtc_state, plane_state);

	अगर (DISPLAY_VER(dev_priv) >= 10)
		plane_state->color_ctl = glk_plane_color_ctl(crtc_state,
							     plane_state);

	अगर (पूर्णांकel_क्रमmat_info_is_yuv_semiplanar(fb->क्रमmat, fb->modअगरier) &&
	    icl_is_hdr_plane(dev_priv, plane->id))
		/* Enable and use MPEG-2 chroma siting */
		plane_state->cus_ctl = PLANE_CUS_ENABLE |
			PLANE_CUS_HPHASE_0 |
			PLANE_CUS_VPHASE_SIGN_NEGATIVE | PLANE_CUS_VPHASE_0_25;
	अन्यथा
		plane_state->cus_ctl = 0;

	वापस 0;
पूर्ण

अटल bool skl_plane_has_fbc(काष्ठा drm_i915_निजी *dev_priv,
			      क्रमागत pipe pipe, क्रमागत plane_id plane_id)
अणु
	अगर (!HAS_FBC(dev_priv))
		वापस false;

	वापस pipe == PIPE_A && plane_id == PLANE_PRIMARY;
पूर्ण

अटल bool skl_plane_has_planar(काष्ठा drm_i915_निजी *dev_priv,
				 क्रमागत pipe pipe, क्रमागत plane_id plane_id)
अणु
	/* Display WA #0870: skl, bxt */
	अगर (IS_SKYLAKE(dev_priv) || IS_BROXTON(dev_priv))
		वापस false;

	अगर (IS_DISPLAY_VER(dev_priv, 9) && pipe == PIPE_C)
		वापस false;

	अगर (plane_id != PLANE_PRIMARY && plane_id != PLANE_SPRITE0)
		वापस false;

	वापस true;
पूर्ण

अटल स्थिर u32 *skl_get_plane_क्रमmats(काष्ठा drm_i915_निजी *dev_priv,
					क्रमागत pipe pipe, क्रमागत plane_id plane_id,
					पूर्णांक *num_क्रमmats)
अणु
	अगर (skl_plane_has_planar(dev_priv, pipe, plane_id)) अणु
		*num_क्रमmats = ARRAY_SIZE(skl_planar_क्रमmats);
		वापस skl_planar_क्रमmats;
	पूर्ण अन्यथा अणु
		*num_क्रमmats = ARRAY_SIZE(skl_plane_क्रमmats);
		वापस skl_plane_क्रमmats;
	पूर्ण
पूर्ण

अटल स्थिर u32 *glk_get_plane_क्रमmats(काष्ठा drm_i915_निजी *dev_priv,
					क्रमागत pipe pipe, क्रमागत plane_id plane_id,
					पूर्णांक *num_क्रमmats)
अणु
	अगर (skl_plane_has_planar(dev_priv, pipe, plane_id)) अणु
		*num_क्रमmats = ARRAY_SIZE(glk_planar_क्रमmats);
		वापस glk_planar_क्रमmats;
	पूर्ण अन्यथा अणु
		*num_क्रमmats = ARRAY_SIZE(skl_plane_क्रमmats);
		वापस skl_plane_क्रमmats;
	पूर्ण
पूर्ण

अटल स्थिर u32 *icl_get_plane_क्रमmats(काष्ठा drm_i915_निजी *dev_priv,
					क्रमागत pipe pipe, क्रमागत plane_id plane_id,
					पूर्णांक *num_क्रमmats)
अणु
	अगर (icl_is_hdr_plane(dev_priv, plane_id)) अणु
		*num_क्रमmats = ARRAY_SIZE(icl_hdr_plane_क्रमmats);
		वापस icl_hdr_plane_क्रमmats;
	पूर्ण अन्यथा अगर (icl_is_nv12_y_plane(dev_priv, plane_id)) अणु
		*num_क्रमmats = ARRAY_SIZE(icl_sdr_y_plane_क्रमmats);
		वापस icl_sdr_y_plane_क्रमmats;
	पूर्ण अन्यथा अणु
		*num_क्रमmats = ARRAY_SIZE(icl_sdr_uv_plane_क्रमmats);
		वापस icl_sdr_uv_plane_क्रमmats;
	पूर्ण
पूर्ण

अटल bool skl_plane_has_ccs(काष्ठा drm_i915_निजी *dev_priv,
			      क्रमागत pipe pipe, क्रमागत plane_id plane_id)
अणु
	अगर (plane_id == PLANE_CURSOR)
		वापस false;

	अगर (DISPLAY_VER(dev_priv) >= 11 || IS_CANNONLAKE(dev_priv))
		वापस true;

	अगर (IS_GEMINILAKE(dev_priv))
		वापस pipe != PIPE_C;

	वापस pipe != PIPE_C &&
		(plane_id == PLANE_PRIMARY ||
		 plane_id == PLANE_SPRITE0);
पूर्ण

अटल bool skl_plane_क्रमmat_mod_supported(काष्ठा drm_plane *_plane,
					   u32 क्रमmat, u64 modअगरier)
अणु
	काष्ठा पूर्णांकel_plane *plane = to_पूर्णांकel_plane(_plane);

	चयन (modअगरier) अणु
	हाल DRM_FORMAT_MOD_LINEAR:
	हाल I915_FORMAT_MOD_X_TILED:
	हाल I915_FORMAT_MOD_Y_TILED:
	हाल I915_FORMAT_MOD_Yf_TILED:
		अवरोध;
	हाल I915_FORMAT_MOD_Y_TILED_CCS:
	हाल I915_FORMAT_MOD_Yf_TILED_CCS:
		अगर (!plane->has_ccs)
			वापस false;
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	चयन (क्रमmat) अणु
	हाल DRM_FORMAT_XRGB8888:
	हाल DRM_FORMAT_XBGR8888:
	हाल DRM_FORMAT_ARGB8888:
	हाल DRM_FORMAT_ABGR8888:
		अगर (is_ccs_modअगरier(modअगरier))
			वापस true;
		fallthrough;
	हाल DRM_FORMAT_RGB565:
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
	हाल DRM_FORMAT_XVYU2101010:
		अगर (modअगरier == I915_FORMAT_MOD_Yf_TILED)
			वापस true;
		fallthrough;
	हाल DRM_FORMAT_C8:
	हाल DRM_FORMAT_XBGR16161616F:
	हाल DRM_FORMAT_ABGR16161616F:
	हाल DRM_FORMAT_XRGB16161616F:
	हाल DRM_FORMAT_ARGB16161616F:
	हाल DRM_FORMAT_Y210:
	हाल DRM_FORMAT_Y212:
	हाल DRM_FORMAT_Y216:
	हाल DRM_FORMAT_XVYU12_16161616:
	हाल DRM_FORMAT_XVYU16161616:
		अगर (modअगरier == DRM_FORMAT_MOD_LINEAR ||
		    modअगरier == I915_FORMAT_MOD_X_TILED ||
		    modअगरier == I915_FORMAT_MOD_Y_TILED)
			वापस true;
		fallthrough;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool gen12_plane_supports_mc_ccs(काष्ठा drm_i915_निजी *dev_priv,
					क्रमागत plane_id plane_id)
अणु
	/* Wa_14010477008:tgl[a0..c0],rkl[all],dg1[all] */
	अगर (IS_DG1(dev_priv) || IS_ROCKETLAKE(dev_priv) ||
	    IS_TGL_DISPLAY_STEP(dev_priv, STEP_A0, STEP_C0))
		वापस false;

	वापस plane_id < PLANE_SPRITE4;
पूर्ण

अटल bool gen12_plane_क्रमmat_mod_supported(काष्ठा drm_plane *_plane,
					     u32 क्रमmat, u64 modअगरier)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(_plane->dev);
	काष्ठा पूर्णांकel_plane *plane = to_पूर्णांकel_plane(_plane);

	चयन (modअगरier) अणु
	हाल I915_FORMAT_MOD_Y_TILED_GEN12_MC_CCS:
		अगर (!gen12_plane_supports_mc_ccs(dev_priv, plane->id))
			वापस false;
		fallthrough;
	हाल DRM_FORMAT_MOD_LINEAR:
	हाल I915_FORMAT_MOD_X_TILED:
	हाल I915_FORMAT_MOD_Y_TILED:
	हाल I915_FORMAT_MOD_Y_TILED_GEN12_RC_CCS:
	हाल I915_FORMAT_MOD_Y_TILED_GEN12_RC_CCS_CC:
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	चयन (क्रमmat) अणु
	हाल DRM_FORMAT_XRGB8888:
	हाल DRM_FORMAT_XBGR8888:
	हाल DRM_FORMAT_ARGB8888:
	हाल DRM_FORMAT_ABGR8888:
		अगर (is_ccs_modअगरier(modअगरier))
			वापस true;
		fallthrough;
	हाल DRM_FORMAT_YUYV:
	हाल DRM_FORMAT_YVYU:
	हाल DRM_FORMAT_UYVY:
	हाल DRM_FORMAT_VYUY:
	हाल DRM_FORMAT_NV12:
	हाल DRM_FORMAT_XYUV8888:
	हाल DRM_FORMAT_P010:
	हाल DRM_FORMAT_P012:
	हाल DRM_FORMAT_P016:
		अगर (modअगरier == I915_FORMAT_MOD_Y_TILED_GEN12_MC_CCS)
			वापस true;
		fallthrough;
	हाल DRM_FORMAT_RGB565:
	हाल DRM_FORMAT_XRGB2101010:
	हाल DRM_FORMAT_XBGR2101010:
	हाल DRM_FORMAT_ARGB2101010:
	हाल DRM_FORMAT_ABGR2101010:
	हाल DRM_FORMAT_XVYU2101010:
	हाल DRM_FORMAT_C8:
	हाल DRM_FORMAT_XBGR16161616F:
	हाल DRM_FORMAT_ABGR16161616F:
	हाल DRM_FORMAT_XRGB16161616F:
	हाल DRM_FORMAT_ARGB16161616F:
	हाल DRM_FORMAT_Y210:
	हाल DRM_FORMAT_Y212:
	हाल DRM_FORMAT_Y216:
	हाल DRM_FORMAT_XVYU12_16161616:
	हाल DRM_FORMAT_XVYU16161616:
		अगर (modअगरier == DRM_FORMAT_MOD_LINEAR ||
		    modअगरier == I915_FORMAT_MOD_X_TILED ||
		    modअगरier == I915_FORMAT_MOD_Y_TILED)
			वापस true;
		fallthrough;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर u64 *gen12_get_plane_modअगरiers(काष्ठा drm_i915_निजी *dev_priv,
					    क्रमागत plane_id plane_id)
अणु
	अगर (gen12_plane_supports_mc_ccs(dev_priv, plane_id))
		वापस gen12_plane_क्रमmat_modअगरiers_mc_ccs;
	अन्यथा
		वापस gen12_plane_क्रमmat_modअगरiers_rc_ccs;
पूर्ण

अटल स्थिर काष्ठा drm_plane_funcs skl_plane_funcs = अणु
	.update_plane = drm_atomic_helper_update_plane,
	.disable_plane = drm_atomic_helper_disable_plane,
	.destroy = पूर्णांकel_plane_destroy,
	.atomic_duplicate_state = पूर्णांकel_plane_duplicate_state,
	.atomic_destroy_state = पूर्णांकel_plane_destroy_state,
	.क्रमmat_mod_supported = skl_plane_क्रमmat_mod_supported,
पूर्ण;

अटल स्थिर काष्ठा drm_plane_funcs gen12_plane_funcs = अणु
	.update_plane = drm_atomic_helper_update_plane,
	.disable_plane = drm_atomic_helper_disable_plane,
	.destroy = पूर्णांकel_plane_destroy,
	.atomic_duplicate_state = पूर्णांकel_plane_duplicate_state,
	.atomic_destroy_state = पूर्णांकel_plane_destroy_state,
	.क्रमmat_mod_supported = gen12_plane_क्रमmat_mod_supported,
पूर्ण;

अटल व्योम
skl_plane_enable_flip_करोne(काष्ठा पूर्णांकel_plane *plane)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(plane->base.dev);
	क्रमागत pipe pipe = plane->pipe;

	spin_lock_irq(&i915->irq_lock);
	bdw_enable_pipe_irq(i915, pipe, GEN9_PIPE_PLANE_FLIP_DONE(plane->id));
	spin_unlock_irq(&i915->irq_lock);
पूर्ण

अटल व्योम
skl_plane_disable_flip_करोne(काष्ठा पूर्णांकel_plane *plane)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(plane->base.dev);
	क्रमागत pipe pipe = plane->pipe;

	spin_lock_irq(&i915->irq_lock);
	bdw_disable_pipe_irq(i915, pipe, GEN9_PIPE_PLANE_FLIP_DONE(plane->id));
	spin_unlock_irq(&i915->irq_lock);
पूर्ण

काष्ठा पूर्णांकel_plane *
skl_universal_plane_create(काष्ठा drm_i915_निजी *dev_priv,
			   क्रमागत pipe pipe, क्रमागत plane_id plane_id)
अणु
	स्थिर काष्ठा drm_plane_funcs *plane_funcs;
	काष्ठा पूर्णांकel_plane *plane;
	क्रमागत drm_plane_type plane_type;
	अचिन्हित पूर्णांक supported_rotations;
	अचिन्हित पूर्णांक supported_csc;
	स्थिर u64 *modअगरiers;
	स्थिर u32 *क्रमmats;
	पूर्णांक num_क्रमmats;
	पूर्णांक ret;

	plane = पूर्णांकel_plane_alloc();
	अगर (IS_ERR(plane))
		वापस plane;

	plane->pipe = pipe;
	plane->id = plane_id;
	plane->frontbuffer_bit = INTEL_FRONTBUFFER(pipe, plane_id);

	plane->has_fbc = skl_plane_has_fbc(dev_priv, pipe, plane_id);
	अगर (plane->has_fbc) अणु
		काष्ठा पूर्णांकel_fbc *fbc = &dev_priv->fbc;

		fbc->possible_framebuffer_bits |= plane->frontbuffer_bit;
	पूर्ण

	अगर (DISPLAY_VER(dev_priv) >= 11) अणु
		plane->min_width = icl_plane_min_width;
		plane->max_width = icl_plane_max_width;
		plane->max_height = icl_plane_max_height;
	पूर्ण अन्यथा अगर (DISPLAY_VER(dev_priv) >= 10) अणु
		plane->max_width = glk_plane_max_width;
		plane->max_height = skl_plane_max_height;
	पूर्ण अन्यथा अणु
		plane->max_width = skl_plane_max_width;
		plane->max_height = skl_plane_max_height;
	पूर्ण

	plane->max_stride = skl_plane_max_stride;
	plane->update_plane = skl_update_plane;
	plane->disable_plane = skl_disable_plane;
	plane->get_hw_state = skl_plane_get_hw_state;
	plane->check_plane = skl_plane_check;
	plane->min_cdclk = skl_plane_min_cdclk;

	अगर (plane_id == PLANE_PRIMARY) अणु
		plane->need_async_flip_disable_wa = IS_DISPLAY_RANGE(dev_priv,
								     9, 10);
		plane->async_flip = skl_plane_async_flip;
		plane->enable_flip_करोne = skl_plane_enable_flip_करोne;
		plane->disable_flip_करोne = skl_plane_disable_flip_करोne;
	पूर्ण

	अगर (DISPLAY_VER(dev_priv) >= 11)
		क्रमmats = icl_get_plane_क्रमmats(dev_priv, pipe,
						plane_id, &num_क्रमmats);
	अन्यथा अगर (DISPLAY_VER(dev_priv) >= 10)
		क्रमmats = glk_get_plane_क्रमmats(dev_priv, pipe,
						plane_id, &num_क्रमmats);
	अन्यथा
		क्रमmats = skl_get_plane_क्रमmats(dev_priv, pipe,
						plane_id, &num_क्रमmats);

	plane->has_ccs = skl_plane_has_ccs(dev_priv, pipe, plane_id);
	अगर (DISPLAY_VER(dev_priv) >= 12) अणु
		modअगरiers = gen12_get_plane_modअगरiers(dev_priv, plane_id);
		plane_funcs = &gen12_plane_funcs;
	पूर्ण अन्यथा अणु
		अगर (plane->has_ccs)
			modअगरiers = skl_plane_क्रमmat_modअगरiers_ccs;
		अन्यथा
			modअगरiers = skl_plane_क्रमmat_modअगरiers_noccs;
		plane_funcs = &skl_plane_funcs;
	पूर्ण

	अगर (plane_id == PLANE_PRIMARY)
		plane_type = DRM_PLANE_TYPE_PRIMARY;
	अन्यथा
		plane_type = DRM_PLANE_TYPE_OVERLAY;

	ret = drm_universal_plane_init(&dev_priv->drm, &plane->base,
				       0, plane_funcs,
				       क्रमmats, num_क्रमmats, modअगरiers,
				       plane_type,
				       "plane %d%c", plane_id + 1,
				       pipe_name(pipe));
	अगर (ret)
		जाओ fail;

	supported_rotations =
		DRM_MODE_ROTATE_0 | DRM_MODE_ROTATE_90 |
		DRM_MODE_ROTATE_180 | DRM_MODE_ROTATE_270;

	अगर (DISPLAY_VER(dev_priv) >= 11 || IS_CANNONLAKE(dev_priv))
		supported_rotations |= DRM_MODE_REFLECT_X;

	drm_plane_create_rotation_property(&plane->base,
					   DRM_MODE_ROTATE_0,
					   supported_rotations);

	supported_csc = BIT(DRM_COLOR_YCBCR_BT601) | BIT(DRM_COLOR_YCBCR_BT709);

	अगर (DISPLAY_VER(dev_priv) >= 10)
		supported_csc |= BIT(DRM_COLOR_YCBCR_BT2020);

	drm_plane_create_color_properties(&plane->base,
					  supported_csc,
					  BIT(DRM_COLOR_YCBCR_LIMITED_RANGE) |
					  BIT(DRM_COLOR_YCBCR_FULL_RANGE),
					  DRM_COLOR_YCBCR_BT709,
					  DRM_COLOR_YCBCR_LIMITED_RANGE);

	drm_plane_create_alpha_property(&plane->base);
	drm_plane_create_blend_mode_property(&plane->base,
					     BIT(DRM_MODE_BLEND_PIXEL_NONE) |
					     BIT(DRM_MODE_BLEND_PREMULTI) |
					     BIT(DRM_MODE_BLEND_COVERAGE));

	drm_plane_create_zpos_immutable_property(&plane->base, plane_id);

	अगर (DISPLAY_VER(dev_priv) >= 12)
		drm_plane_enable_fb_damage_clips(&plane->base);

	अगर (DISPLAY_VER(dev_priv) >= 11 || IS_CANNONLAKE(dev_priv))
		drm_plane_create_scaling_filter_property(&plane->base,
						BIT(DRM_SCALING_FILTER_DEFAULT) |
						BIT(DRM_SCALING_FILTER_NEAREST_NEIGHBOR));

	drm_plane_helper_add(&plane->base, &पूर्णांकel_plane_helper_funcs);

	वापस plane;

fail:
	पूर्णांकel_plane_मुक्त(plane);

	वापस ERR_PTR(ret);
पूर्ण

व्योम
skl_get_initial_plane_config(काष्ठा पूर्णांकel_crtc *crtc,
			     काष्ठा पूर्णांकel_initial_plane_config *plane_config)
अणु
	काष्ठा पूर्णांकel_crtc_state *crtc_state = to_पूर्णांकel_crtc_state(crtc->base.state);
	काष्ठा drm_device *dev = crtc->base.dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	काष्ठा पूर्णांकel_plane *plane = to_पूर्णांकel_plane(crtc->base.primary);
	क्रमागत plane_id plane_id = plane->id;
	क्रमागत pipe pipe;
	u32 val, base, offset, stride_mult, tiling, alpha;
	पूर्णांक fourcc, pixel_क्रमmat;
	अचिन्हित पूर्णांक aligned_height;
	काष्ठा drm_framebuffer *fb;
	काष्ठा पूर्णांकel_framebuffer *पूर्णांकel_fb;

	अगर (!plane->get_hw_state(plane, &pipe))
		वापस;

	drm_WARN_ON(dev, pipe != crtc->pipe);

	अगर (crtc_state->bigjoiner) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "Unsupported bigjoiner configuration for initial FB\n");
		वापस;
	पूर्ण

	पूर्णांकel_fb = kzalloc(माप(*पूर्णांकel_fb), GFP_KERNEL);
	अगर (!पूर्णांकel_fb) अणु
		drm_dbg_kms(&dev_priv->drm, "failed to alloc fb\n");
		वापस;
	पूर्ण

	fb = &पूर्णांकel_fb->base;

	fb->dev = dev;

	val = पूर्णांकel_de_पढ़ो(dev_priv, PLANE_CTL(pipe, plane_id));

	अगर (DISPLAY_VER(dev_priv) >= 11)
		pixel_क्रमmat = val & ICL_PLANE_CTL_FORMAT_MASK;
	अन्यथा
		pixel_क्रमmat = val & PLANE_CTL_FORMAT_MASK;

	अगर (DISPLAY_VER(dev_priv) >= 10) अणु
		alpha = पूर्णांकel_de_पढ़ो(dev_priv,
				      PLANE_COLOR_CTL(pipe, plane_id));
		alpha &= PLANE_COLOR_ALPHA_MASK;
	पूर्ण अन्यथा अणु
		alpha = val & PLANE_CTL_ALPHA_MASK;
	पूर्ण

	fourcc = skl_क्रमmat_to_fourcc(pixel_क्रमmat,
				      val & PLANE_CTL_ORDER_RGBX, alpha);
	fb->क्रमmat = drm_क्रमmat_info(fourcc);

	tiling = val & PLANE_CTL_TILED_MASK;
	चयन (tiling) अणु
	हाल PLANE_CTL_TILED_LINEAR:
		fb->modअगरier = DRM_FORMAT_MOD_LINEAR;
		अवरोध;
	हाल PLANE_CTL_TILED_X:
		plane_config->tiling = I915_TILING_X;
		fb->modअगरier = I915_FORMAT_MOD_X_TILED;
		अवरोध;
	हाल PLANE_CTL_TILED_Y:
		plane_config->tiling = I915_TILING_Y;
		अगर (val & PLANE_CTL_RENDER_DECOMPRESSION_ENABLE)
			fb->modअगरier = DISPLAY_VER(dev_priv) >= 12 ?
				I915_FORMAT_MOD_Y_TILED_GEN12_RC_CCS :
				I915_FORMAT_MOD_Y_TILED_CCS;
		अन्यथा अगर (val & PLANE_CTL_MEDIA_DECOMPRESSION_ENABLE)
			fb->modअगरier = I915_FORMAT_MOD_Y_TILED_GEN12_MC_CCS;
		अन्यथा
			fb->modअगरier = I915_FORMAT_MOD_Y_TILED;
		अवरोध;
	हाल PLANE_CTL_TILED_YF:
		अगर (val & PLANE_CTL_RENDER_DECOMPRESSION_ENABLE)
			fb->modअगरier = I915_FORMAT_MOD_Yf_TILED_CCS;
		अन्यथा
			fb->modअगरier = I915_FORMAT_MOD_Yf_TILED;
		अवरोध;
	शेष:
		MISSING_CASE(tiling);
		जाओ error;
	पूर्ण

	/*
	 * DRM_MODE_ROTATE_ is counter घड़ीwise to stay compatible with Xअक्रमr
	 * जबतक i915 HW rotation is घड़ीwise, thats why this swapping.
	 */
	चयन (val & PLANE_CTL_ROTATE_MASK) अणु
	हाल PLANE_CTL_ROTATE_0:
		plane_config->rotation = DRM_MODE_ROTATE_0;
		अवरोध;
	हाल PLANE_CTL_ROTATE_90:
		plane_config->rotation = DRM_MODE_ROTATE_270;
		अवरोध;
	हाल PLANE_CTL_ROTATE_180:
		plane_config->rotation = DRM_MODE_ROTATE_180;
		अवरोध;
	हाल PLANE_CTL_ROTATE_270:
		plane_config->rotation = DRM_MODE_ROTATE_90;
		अवरोध;
	पूर्ण

	अगर ((DISPLAY_VER(dev_priv) >= 11 || IS_CANNONLAKE(dev_priv)) && val & PLANE_CTL_FLIP_HORIZONTAL)
		plane_config->rotation |= DRM_MODE_REFLECT_X;

	/* 90/270 degree rotation would require extra work */
	अगर (drm_rotation_90_or_270(plane_config->rotation))
		जाओ error;

	base = पूर्णांकel_de_पढ़ो(dev_priv, PLANE_SURF(pipe, plane_id)) & 0xfffff000;
	plane_config->base = base;

	offset = पूर्णांकel_de_पढ़ो(dev_priv, PLANE_OFFSET(pipe, plane_id));

	val = पूर्णांकel_de_पढ़ो(dev_priv, PLANE_SIZE(pipe, plane_id));
	fb->height = ((val >> 16) & 0xffff) + 1;
	fb->width = ((val >> 0) & 0xffff) + 1;

	val = पूर्णांकel_de_पढ़ो(dev_priv, PLANE_STRIDE(pipe, plane_id));
	stride_mult = skl_plane_stride_mult(fb, 0, DRM_MODE_ROTATE_0);
	fb->pitches[0] = (val & 0x3ff) * stride_mult;

	aligned_height = पूर्णांकel_fb_align_height(fb, 0, fb->height);

	plane_config->size = fb->pitches[0] * aligned_height;

	drm_dbg_kms(&dev_priv->drm,
		    "%s/%s with fb: size=%dx%d@%d, offset=%x, pitch %d, size 0x%x\n",
		    crtc->base.name, plane->base.name, fb->width, fb->height,
		    fb->क्रमmat->cpp[0] * 8, base, fb->pitches[0],
		    plane_config->size);

	plane_config->fb = पूर्णांकel_fb;
	वापस;

error:
	kमुक्त(पूर्णांकel_fb);
पूर्ण

