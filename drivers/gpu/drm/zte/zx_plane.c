<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2016 Linaro Ltd.
 * Copyright 2016 ZTE Corporation.
 */

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_fb_cma_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_gem_cma_helper.h>
#समावेश <drm/drm_modeset_helper_vtables.h>
#समावेश <drm/drm_plane_helper.h>

#समावेश "zx_common_regs.h"
#समावेश "zx_drm_drv.h"
#समावेश "zx_plane.h"
#समावेश "zx_plane_regs.h"
#समावेश "zx_vou.h"

अटल स्थिर uपूर्णांक32_t gl_क्रमmats[] = अणु
	DRM_FORMAT_ARGB8888,
	DRM_FORMAT_XRGB8888,
	DRM_FORMAT_RGB888,
	DRM_FORMAT_RGB565,
	DRM_FORMAT_ARGB1555,
	DRM_FORMAT_ARGB4444,
पूर्ण;

अटल स्थिर uपूर्णांक32_t vl_क्रमmats[] = अणु
	DRM_FORMAT_NV12,	/* Semi-planar YUV420 */
	DRM_FORMAT_YUV420,	/* Planar YUV420 */
	DRM_FORMAT_YUYV,	/* Packed YUV422 */
	DRM_FORMAT_YVYU,
	DRM_FORMAT_UYVY,
	DRM_FORMAT_VYUY,
	DRM_FORMAT_YUV444,	/* YUV444 8bit */
	/*
	 * TODO: add क्रमmats below that HW supports:
	 *  - YUV420 P010
	 *  - YUV420 Hantro
	 *  - YUV444 10bit
	 */
पूर्ण;

#घोषणा FRAC_16_16(mult, भाग)    (((mult) << 16) / (भाग))

अटल पूर्णांक zx_vl_plane_atomic_check(काष्ठा drm_plane *plane,
				    काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *plane_state = drm_atomic_get_new_plane_state(state,
									     plane);
	काष्ठा drm_framebuffer *fb = plane_state->fb;
	काष्ठा drm_crtc *crtc = plane_state->crtc;
	काष्ठा drm_crtc_state *crtc_state;
	पूर्णांक min_scale = FRAC_16_16(1, 8);
	पूर्णांक max_scale = FRAC_16_16(8, 1);

	अगर (!crtc || WARN_ON(!fb))
		वापस 0;

	crtc_state = drm_atomic_get_existing_crtc_state(state,
							crtc);
	अगर (WARN_ON(!crtc_state))
		वापस -EINVAL;

	/* nothing to check when disabling or disabled */
	अगर (!crtc_state->enable)
		वापस 0;

	/* plane must be enabled */
	अगर (!plane_state->crtc)
		वापस -EINVAL;

	वापस drm_atomic_helper_check_plane_state(plane_state, crtc_state,
						   min_scale, max_scale,
						   true, true);
पूर्ण

अटल पूर्णांक zx_vl_get_fmt(uपूर्णांक32_t क्रमmat)
अणु
	चयन (क्रमmat) अणु
	हाल DRM_FORMAT_NV12:
		वापस VL_FMT_YUV420;
	हाल DRM_FORMAT_YUV420:
		वापस VL_YUV420_PLANAR | VL_FMT_YUV420;
	हाल DRM_FORMAT_YUYV:
		वापस VL_YUV422_YUYV | VL_FMT_YUV422;
	हाल DRM_FORMAT_YVYU:
		वापस VL_YUV422_YVYU | VL_FMT_YUV422;
	हाल DRM_FORMAT_UYVY:
		वापस VL_YUV422_UYVY | VL_FMT_YUV422;
	हाल DRM_FORMAT_VYUY:
		वापस VL_YUV422_VYUY | VL_FMT_YUV422;
	हाल DRM_FORMAT_YUV444:
		वापस VL_FMT_YUV444_8BIT;
	शेष:
		WARN_ONCE(1, "invalid pixel format %d\n", क्रमmat);
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम zx_vl_set_update(काष्ठा zx_plane *zplane)
अणु
	व्योम __iomem *layer = zplane->layer;

	zx_ग_लिखोl_mask(layer + VL_CTRL0, VL_UPDATE, VL_UPDATE);
पूर्ण

अटल अंतरभूत व्योम zx_vl_rsz_set_update(काष्ठा zx_plane *zplane)
अणु
	zx_ग_लिखोl(zplane->rsz + RSZ_VL_ENABLE_CFG, 1);
पूर्ण

अटल पूर्णांक zx_vl_rsz_get_fmt(uपूर्णांक32_t क्रमmat)
अणु
	चयन (क्रमmat) अणु
	हाल DRM_FORMAT_NV12:
	हाल DRM_FORMAT_YUV420:
		वापस RSZ_VL_FMT_YCBCR420;
	हाल DRM_FORMAT_YUYV:
	हाल DRM_FORMAT_YVYU:
	हाल DRM_FORMAT_UYVY:
	हाल DRM_FORMAT_VYUY:
		वापस RSZ_VL_FMT_YCBCR422;
	हाल DRM_FORMAT_YUV444:
		वापस RSZ_VL_FMT_YCBCR444;
	शेष:
		WARN_ONCE(1, "invalid pixel format %d\n", क्रमmat);
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल अंतरभूत u32 rsz_step_value(u32 src, u32 dst)
अणु
	u32 val = 0;

	अगर (src == dst)
		val = 0;
	अन्यथा अगर (src < dst)
		val = RSZ_PARA_STEP((src << 16) / dst);
	अन्यथा अगर (src > dst)
		val = RSZ_DATA_STEP(src / dst) |
		      RSZ_PARA_STEP(((src << 16) / dst) & 0xffff);

	वापस val;
पूर्ण

अटल व्योम zx_vl_rsz_setup(काष्ठा zx_plane *zplane, uपूर्णांक32_t क्रमmat,
			    u32 src_w, u32 src_h, u32 dst_w, u32 dst_h)
अणु
	व्योम __iomem *rsz = zplane->rsz;
	u32 src_chroma_w = src_w;
	u32 src_chroma_h = src_h;
	पूर्णांक fmt;

	/* Set up source and destination resolution */
	zx_ग_लिखोl(rsz + RSZ_SRC_CFG, RSZ_VER(src_h - 1) | RSZ_HOR(src_w - 1));
	zx_ग_लिखोl(rsz + RSZ_DEST_CFG, RSZ_VER(dst_h - 1) | RSZ_HOR(dst_w - 1));

	/* Configure data क्रमmat क्रम VL RSZ */
	fmt = zx_vl_rsz_get_fmt(क्रमmat);
	अगर (fmt >= 0)
		zx_ग_लिखोl_mask(rsz + RSZ_VL_CTRL_CFG, RSZ_VL_FMT_MASK, fmt);

	/* Calculate Chroma height and width */
	अगर (fmt == RSZ_VL_FMT_YCBCR420) अणु
		src_chroma_w = src_w >> 1;
		src_chroma_h = src_h >> 1;
	पूर्ण अन्यथा अगर (fmt == RSZ_VL_FMT_YCBCR422) अणु
		src_chroma_w = src_w >> 1;
	पूर्ण

	/* Set up Luma and Chroma step रेजिस्टरs */
	zx_ग_लिखोl(rsz + RSZ_VL_LUMA_HOR, rsz_step_value(src_w, dst_w));
	zx_ग_लिखोl(rsz + RSZ_VL_LUMA_VER, rsz_step_value(src_h, dst_h));
	zx_ग_लिखोl(rsz + RSZ_VL_CHROMA_HOR, rsz_step_value(src_chroma_w, dst_w));
	zx_ग_लिखोl(rsz + RSZ_VL_CHROMA_VER, rsz_step_value(src_chroma_h, dst_h));

	zx_vl_rsz_set_update(zplane);
पूर्ण

अटल व्योम zx_vl_plane_atomic_update(काष्ठा drm_plane *plane,
				      काष्ठा drm_atomic_state *state)
अणु
	काष्ठा zx_plane *zplane = to_zx_plane(plane);
	काष्ठा drm_plane_state *new_state = drm_atomic_get_new_plane_state(state,
									   plane);
	काष्ठा drm_framebuffer *fb = new_state->fb;
	काष्ठा drm_rect *src = &new_state->src;
	काष्ठा drm_rect *dst = &new_state->dst;
	काष्ठा drm_gem_cma_object *cma_obj;
	व्योम __iomem *layer = zplane->layer;
	व्योम __iomem *hbsc = zplane->hbsc;
	व्योम __iomem *paddr_reg;
	dma_addr_t paddr;
	u32 src_x, src_y, src_w, src_h;
	u32 dst_x, dst_y, dst_w, dst_h;
	uपूर्णांक32_t क्रमmat;
	पूर्णांक fmt;
	पूर्णांक i;

	अगर (!fb)
		वापस;

	क्रमmat = fb->क्रमmat->क्रमmat;

	src_x = src->x1 >> 16;
	src_y = src->y1 >> 16;
	src_w = drm_rect_width(src) >> 16;
	src_h = drm_rect_height(src) >> 16;

	dst_x = dst->x1;
	dst_y = dst->y1;
	dst_w = drm_rect_width(dst);
	dst_h = drm_rect_height(dst);

	/* Set up data address रेजिस्टरs क्रम Y, Cb and Cr planes */
	paddr_reg = layer + VL_Y;
	क्रम (i = 0; i < fb->क्रमmat->num_planes; i++) अणु
		cma_obj = drm_fb_cma_get_gem_obj(fb, i);
		paddr = cma_obj->paddr + fb->offsets[i];
		paddr += src_y * fb->pitches[i];
		paddr += src_x * fb->क्रमmat->cpp[i];
		zx_ग_लिखोl(paddr_reg, paddr);
		paddr_reg += 4;
	पूर्ण

	/* Set up source height/width रेजिस्टर */
	zx_ग_लिखोl(layer + VL_SRC_SIZE, GL_SRC_W(src_w) | GL_SRC_H(src_h));

	/* Set up start position रेजिस्टर */
	zx_ग_लिखोl(layer + VL_POS_START, GL_POS_X(dst_x) | GL_POS_Y(dst_y));

	/* Set up end position रेजिस्टर */
	zx_ग_लिखोl(layer + VL_POS_END,
		  GL_POS_X(dst_x + dst_w) | GL_POS_Y(dst_y + dst_h));

	/* Strides of Cb and Cr planes should be identical */
	zx_ग_लिखोl(layer + VL_STRIDE, LUMA_STRIDE(fb->pitches[0]) |
		  CHROMA_STRIDE(fb->pitches[1]));

	/* Set up video layer data क्रमmat */
	fmt = zx_vl_get_fmt(क्रमmat);
	अगर (fmt >= 0)
		zx_ग_लिखोl(layer + VL_CTRL1, fmt);

	/* Always use scaler since it exists (set क्रम not bypass) */
	zx_ग_लिखोl_mask(layer + VL_CTRL2, VL_SCALER_BYPASS_MODE,
		       VL_SCALER_BYPASS_MODE);

	zx_vl_rsz_setup(zplane, क्रमmat, src_w, src_h, dst_w, dst_h);

	/* Enable HBSC block */
	zx_ग_लिखोl_mask(hbsc + HBSC_CTRL0, HBSC_CTRL_EN, HBSC_CTRL_EN);

	zx_vou_layer_enable(plane);

	zx_vl_set_update(zplane);
पूर्ण

अटल व्योम zx_plane_atomic_disable(काष्ठा drm_plane *plane,
				    काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *old_state = drm_atomic_get_old_plane_state(state,
									   plane);
	काष्ठा zx_plane *zplane = to_zx_plane(plane);
	व्योम __iomem *hbsc = zplane->hbsc;

	zx_vou_layer_disable(plane, old_state);

	/* Disable HBSC block */
	zx_ग_लिखोl_mask(hbsc + HBSC_CTRL0, HBSC_CTRL_EN, 0);
पूर्ण

अटल स्थिर काष्ठा drm_plane_helper_funcs zx_vl_plane_helper_funcs = अणु
	.atomic_check = zx_vl_plane_atomic_check,
	.atomic_update = zx_vl_plane_atomic_update,
	.atomic_disable = zx_plane_atomic_disable,
पूर्ण;

अटल पूर्णांक zx_gl_plane_atomic_check(काष्ठा drm_plane *plane,
				    काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *plane_state = drm_atomic_get_new_plane_state(state,
									     plane);
	काष्ठा drm_framebuffer *fb = plane_state->fb;
	काष्ठा drm_crtc *crtc = plane_state->crtc;
	काष्ठा drm_crtc_state *crtc_state;

	अगर (!crtc || WARN_ON(!fb))
		वापस 0;

	crtc_state = drm_atomic_get_existing_crtc_state(state,
							crtc);
	अगर (WARN_ON(!crtc_state))
		वापस -EINVAL;

	/* nothing to check when disabling or disabled */
	अगर (!crtc_state->enable)
		वापस 0;

	/* plane must be enabled */
	अगर (!plane_state->crtc)
		वापस -EINVAL;

	वापस drm_atomic_helper_check_plane_state(plane_state, crtc_state,
						   DRM_PLANE_HELPER_NO_SCALING,
						   DRM_PLANE_HELPER_NO_SCALING,
						   false, true);
पूर्ण

अटल पूर्णांक zx_gl_get_fmt(uपूर्णांक32_t क्रमmat)
अणु
	चयन (क्रमmat) अणु
	हाल DRM_FORMAT_ARGB8888:
	हाल DRM_FORMAT_XRGB8888:
		वापस GL_FMT_ARGB8888;
	हाल DRM_FORMAT_RGB888:
		वापस GL_FMT_RGB888;
	हाल DRM_FORMAT_RGB565:
		वापस GL_FMT_RGB565;
	हाल DRM_FORMAT_ARGB1555:
		वापस GL_FMT_ARGB1555;
	हाल DRM_FORMAT_ARGB4444:
		वापस GL_FMT_ARGB4444;
	शेष:
		WARN_ONCE(1, "invalid pixel format %d\n", क्रमmat);
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम zx_gl_set_update(काष्ठा zx_plane *zplane)
अणु
	व्योम __iomem *layer = zplane->layer;

	zx_ग_लिखोl_mask(layer + GL_CTRL0, GL_UPDATE, GL_UPDATE);
पूर्ण

अटल अंतरभूत व्योम zx_gl_rsz_set_update(काष्ठा zx_plane *zplane)
अणु
	zx_ग_लिखोl(zplane->rsz + RSZ_ENABLE_CFG, 1);
पूर्ण

अटल व्योम zx_gl_rsz_setup(काष्ठा zx_plane *zplane, u32 src_w, u32 src_h,
			    u32 dst_w, u32 dst_h)
अणु
	व्योम __iomem *rsz = zplane->rsz;

	zx_ग_लिखोl(rsz + RSZ_SRC_CFG, RSZ_VER(src_h - 1) | RSZ_HOR(src_w - 1));
	zx_ग_लिखोl(rsz + RSZ_DEST_CFG, RSZ_VER(dst_h - 1) | RSZ_HOR(dst_w - 1));

	zx_gl_rsz_set_update(zplane);
पूर्ण

अटल व्योम zx_gl_plane_atomic_update(काष्ठा drm_plane *plane,
				      काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *new_state = drm_atomic_get_new_plane_state(state,
									   plane);
	काष्ठा zx_plane *zplane = to_zx_plane(plane);
	काष्ठा drm_framebuffer *fb = new_state->fb;
	काष्ठा drm_gem_cma_object *cma_obj;
	व्योम __iomem *layer = zplane->layer;
	व्योम __iomem *csc = zplane->csc;
	व्योम __iomem *hbsc = zplane->hbsc;
	u32 src_x, src_y, src_w, src_h;
	u32 dst_x, dst_y, dst_w, dst_h;
	अचिन्हित पूर्णांक bpp;
	uपूर्णांक32_t क्रमmat;
	dma_addr_t paddr;
	u32 stride;
	पूर्णांक fmt;

	अगर (!fb)
		वापस;

	क्रमmat = fb->क्रमmat->क्रमmat;
	stride = fb->pitches[0];

	src_x = new_state->src_x >> 16;
	src_y = new_state->src_y >> 16;
	src_w = new_state->src_w >> 16;
	src_h = new_state->src_h >> 16;

	dst_x = new_state->crtc_x;
	dst_y = new_state->crtc_y;
	dst_w = new_state->crtc_w;
	dst_h = new_state->crtc_h;

	bpp = fb->क्रमmat->cpp[0];

	cma_obj = drm_fb_cma_get_gem_obj(fb, 0);
	paddr = cma_obj->paddr + fb->offsets[0];
	paddr += src_y * stride + src_x * bpp / 8;
	zx_ग_लिखोl(layer + GL_ADDR, paddr);

	/* Set up source height/width रेजिस्टर */
	zx_ग_लिखोl(layer + GL_SRC_SIZE, GL_SRC_W(src_w) | GL_SRC_H(src_h));

	/* Set up start position रेजिस्टर */
	zx_ग_लिखोl(layer + GL_POS_START, GL_POS_X(dst_x) | GL_POS_Y(dst_y));

	/* Set up end position रेजिस्टर */
	zx_ग_लिखोl(layer + GL_POS_END,
		  GL_POS_X(dst_x + dst_w) | GL_POS_Y(dst_y + dst_h));

	/* Set up stride रेजिस्टर */
	zx_ग_लिखोl(layer + GL_STRIDE, stride & 0xffff);

	/* Set up graphic layer data क्रमmat */
	fmt = zx_gl_get_fmt(क्रमmat);
	अगर (fmt >= 0)
		zx_ग_लिखोl_mask(layer + GL_CTRL1, GL_DATA_FMT_MASK,
			       fmt << GL_DATA_FMT_SHIFT);

	/* Initialize global alpha with a sane value */
	zx_ग_लिखोl_mask(layer + GL_CTRL2, GL_GLOBAL_ALPHA_MASK,
		       0xff << GL_GLOBAL_ALPHA_SHIFT);

	/* Setup CSC क्रम the GL */
	अगर (dst_h > 720)
		zx_ग_लिखोl_mask(csc + CSC_CTRL0, CSC_COV_MODE_MASK,
			       CSC_BT709_IMAGE_RGB2YCBCR << CSC_COV_MODE_SHIFT);
	अन्यथा
		zx_ग_लिखोl_mask(csc + CSC_CTRL0, CSC_COV_MODE_MASK,
			       CSC_BT601_IMAGE_RGB2YCBCR << CSC_COV_MODE_SHIFT);
	zx_ग_लिखोl_mask(csc + CSC_CTRL0, CSC_WORK_ENABLE, CSC_WORK_ENABLE);

	/* Always use scaler since it exists (set क्रम not bypass) */
	zx_ग_लिखोl_mask(layer + GL_CTRL3, GL_SCALER_BYPASS_MODE,
		       GL_SCALER_BYPASS_MODE);

	zx_gl_rsz_setup(zplane, src_w, src_h, dst_w, dst_h);

	/* Enable HBSC block */
	zx_ग_लिखोl_mask(hbsc + HBSC_CTRL0, HBSC_CTRL_EN, HBSC_CTRL_EN);

	zx_vou_layer_enable(plane);

	zx_gl_set_update(zplane);
पूर्ण

अटल स्थिर काष्ठा drm_plane_helper_funcs zx_gl_plane_helper_funcs = अणु
	.atomic_check = zx_gl_plane_atomic_check,
	.atomic_update = zx_gl_plane_atomic_update,
	.atomic_disable = zx_plane_atomic_disable,
पूर्ण;

अटल स्थिर काष्ठा drm_plane_funcs zx_plane_funcs = अणु
	.update_plane = drm_atomic_helper_update_plane,
	.disable_plane = drm_atomic_helper_disable_plane,
	.destroy = drm_plane_cleanup,
	.reset = drm_atomic_helper_plane_reset,
	.atomic_duplicate_state = drm_atomic_helper_plane_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_plane_destroy_state,
पूर्ण;

व्योम zx_plane_set_update(काष्ठा drm_plane *plane)
अणु
	काष्ठा zx_plane *zplane = to_zx_plane(plane);

	/* Do nothing अगर the plane is not enabled */
	अगर (!plane->state->crtc)
		वापस;

	चयन (plane->type) अणु
	हाल DRM_PLANE_TYPE_PRIMARY:
		zx_gl_rsz_set_update(zplane);
		zx_gl_set_update(zplane);
		अवरोध;
	हाल DRM_PLANE_TYPE_OVERLAY:
		zx_vl_rsz_set_update(zplane);
		zx_vl_set_update(zplane);
		अवरोध;
	शेष:
		WARN_ONCE(1, "unsupported plane type %d\n", plane->type);
	पूर्ण
पूर्ण

अटल व्योम zx_plane_hbsc_init(काष्ठा zx_plane *zplane)
अणु
	व्योम __iomem *hbsc = zplane->hbsc;

	/*
	 *  Initialize HBSC block with a sane configuration per recommedation
	 *  from ZTE BSP code.
	 */
	zx_ग_लिखोl(hbsc + HBSC_SATURATION, 0x200);
	zx_ग_लिखोl(hbsc + HBSC_HUE, 0x0);
	zx_ग_लिखोl(hbsc + HBSC_BRIGHT, 0x0);
	zx_ग_लिखोl(hbsc + HBSC_CONTRAST, 0x200);

	zx_ग_लिखोl(hbsc + HBSC_THRESHOLD_COL1, (0x3ac << 16) | 0x40);
	zx_ग_लिखोl(hbsc + HBSC_THRESHOLD_COL2, (0x3c0 << 16) | 0x40);
	zx_ग_लिखोl(hbsc + HBSC_THRESHOLD_COL3, (0x3c0 << 16) | 0x40);
पूर्ण

पूर्णांक zx_plane_init(काष्ठा drm_device *drm, काष्ठा zx_plane *zplane,
		  क्रमागत drm_plane_type type)
अणु
	स्थिर काष्ठा drm_plane_helper_funcs *helper;
	काष्ठा drm_plane *plane = &zplane->plane;
	काष्ठा device *dev = zplane->dev;
	स्थिर uपूर्णांक32_t *क्रमmats;
	अचिन्हित पूर्णांक क्रमmat_count;
	पूर्णांक ret;

	zx_plane_hbsc_init(zplane);

	चयन (type) अणु
	हाल DRM_PLANE_TYPE_PRIMARY:
		helper = &zx_gl_plane_helper_funcs;
		क्रमmats = gl_क्रमmats;
		क्रमmat_count = ARRAY_SIZE(gl_क्रमmats);
		अवरोध;
	हाल DRM_PLANE_TYPE_OVERLAY:
		helper = &zx_vl_plane_helper_funcs;
		क्रमmats = vl_क्रमmats;
		क्रमmat_count = ARRAY_SIZE(vl_क्रमmats);
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण

	ret = drm_universal_plane_init(drm, plane, VOU_CRTC_MASK,
				       &zx_plane_funcs, क्रमmats, क्रमmat_count,
				       शून्य, type, शून्य);
	अगर (ret) अणु
		DRM_DEV_ERROR(dev, "failed to init universal plane: %d\n", ret);
		वापस ret;
	पूर्ण

	drm_plane_helper_add(plane, helper);

	वापस 0;
पूर्ण
