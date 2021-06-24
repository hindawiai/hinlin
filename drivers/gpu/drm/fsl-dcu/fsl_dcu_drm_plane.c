<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2015 Freescale Semiconductor, Inc.
 *
 * Freescale DCU drm device driver
 */

#समावेश <linux/regmap.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_fb_cma_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_gem_cma_helper.h>
#समावेश <drm/drm_plane_helper.h>
#समावेश <drm/drm_probe_helper.h>

#समावेश "fsl_dcu_drm_drv.h"
#समावेश "fsl_dcu_drm_plane.h"

अटल पूर्णांक fsl_dcu_drm_plane_index(काष्ठा drm_plane *plane)
अणु
	काष्ठा fsl_dcu_drm_device *fsl_dev = plane->dev->dev_निजी;
	अचिन्हित पूर्णांक total_layer = fsl_dev->soc->total_layer;
	अचिन्हित पूर्णांक index;

	index = drm_plane_index(plane);
	अगर (index < total_layer)
		वापस total_layer - index - 1;

	dev_err(fsl_dev->dev, "No more layer left\n");
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक fsl_dcu_drm_plane_atomic_check(काष्ठा drm_plane *plane,
					  काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *new_plane_state = drm_atomic_get_new_plane_state(state,
										 plane);
	काष्ठा drm_framebuffer *fb = new_plane_state->fb;

	अगर (!new_plane_state->fb || !new_plane_state->crtc)
		वापस 0;

	चयन (fb->क्रमmat->क्रमmat) अणु
	हाल DRM_FORMAT_RGB565:
	हाल DRM_FORMAT_RGB888:
	हाल DRM_FORMAT_XRGB8888:
	हाल DRM_FORMAT_ARGB8888:
	हाल DRM_FORMAT_XRGB4444:
	हाल DRM_FORMAT_ARGB4444:
	हाल DRM_FORMAT_XRGB1555:
	हाल DRM_FORMAT_ARGB1555:
	हाल DRM_FORMAT_YUV422:
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल व्योम fsl_dcu_drm_plane_atomic_disable(काष्ठा drm_plane *plane,
					     काष्ठा drm_atomic_state *state)
अणु
	काष्ठा fsl_dcu_drm_device *fsl_dev = plane->dev->dev_निजी;
	अचिन्हित पूर्णांक value;
	पूर्णांक index;

	index = fsl_dcu_drm_plane_index(plane);
	अगर (index < 0)
		वापस;

	regmap_पढ़ो(fsl_dev->regmap, DCU_CTRLDESCLN(index, 4), &value);
	value &= ~DCU_LAYER_EN;
	regmap_ग_लिखो(fsl_dev->regmap, DCU_CTRLDESCLN(index, 4), value);
पूर्ण

अटल व्योम fsl_dcu_drm_plane_atomic_update(काष्ठा drm_plane *plane,
					    काष्ठा drm_atomic_state *state)

अणु
	काष्ठा fsl_dcu_drm_device *fsl_dev = plane->dev->dev_निजी;
	काष्ठा drm_plane_state *new_state = drm_atomic_get_new_plane_state(state,
									   plane);
	काष्ठा drm_framebuffer *fb = plane->state->fb;
	काष्ठा drm_gem_cma_object *gem;
	अचिन्हित पूर्णांक alpha = DCU_LAYER_AB_NONE, bpp;
	पूर्णांक index;

	अगर (!fb)
		वापस;

	index = fsl_dcu_drm_plane_index(plane);
	अगर (index < 0)
		वापस;

	gem = drm_fb_cma_get_gem_obj(fb, 0);

	चयन (fb->क्रमmat->क्रमmat) अणु
	हाल DRM_FORMAT_RGB565:
		bpp = FSL_DCU_RGB565;
		अवरोध;
	हाल DRM_FORMAT_RGB888:
		bpp = FSL_DCU_RGB888;
		अवरोध;
	हाल DRM_FORMAT_ARGB8888:
		alpha = DCU_LAYER_AB_WHOLE_FRAME;
		fallthrough;
	हाल DRM_FORMAT_XRGB8888:
		bpp = FSL_DCU_ARGB8888;
		अवरोध;
	हाल DRM_FORMAT_ARGB4444:
		alpha = DCU_LAYER_AB_WHOLE_FRAME;
		fallthrough;
	हाल DRM_FORMAT_XRGB4444:
		bpp = FSL_DCU_ARGB4444;
		अवरोध;
	हाल DRM_FORMAT_ARGB1555:
		alpha = DCU_LAYER_AB_WHOLE_FRAME;
		fallthrough;
	हाल DRM_FORMAT_XRGB1555:
		bpp = FSL_DCU_ARGB1555;
		अवरोध;
	हाल DRM_FORMAT_YUV422:
		bpp = FSL_DCU_YUV422;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	regmap_ग_लिखो(fsl_dev->regmap, DCU_CTRLDESCLN(index, 1),
		     DCU_LAYER_HEIGHT(new_state->crtc_h) |
		     DCU_LAYER_WIDTH(new_state->crtc_w));
	regmap_ग_लिखो(fsl_dev->regmap, DCU_CTRLDESCLN(index, 2),
		     DCU_LAYER_POSY(new_state->crtc_y) |
		     DCU_LAYER_POSX(new_state->crtc_x));
	regmap_ग_लिखो(fsl_dev->regmap,
		     DCU_CTRLDESCLN(index, 3), gem->paddr);
	regmap_ग_लिखो(fsl_dev->regmap, DCU_CTRLDESCLN(index, 4),
		     DCU_LAYER_EN |
		     DCU_LAYER_TRANS(0xff) |
		     DCU_LAYER_BPP(bpp) |
		     alpha);
	regmap_ग_लिखो(fsl_dev->regmap, DCU_CTRLDESCLN(index, 5),
		     DCU_LAYER_CKMAX_R(0xFF) |
		     DCU_LAYER_CKMAX_G(0xFF) |
		     DCU_LAYER_CKMAX_B(0xFF));
	regmap_ग_लिखो(fsl_dev->regmap, DCU_CTRLDESCLN(index, 6),
		     DCU_LAYER_CKMIN_R(0) |
		     DCU_LAYER_CKMIN_G(0) |
		     DCU_LAYER_CKMIN_B(0));
	regmap_ग_लिखो(fsl_dev->regmap, DCU_CTRLDESCLN(index, 7), 0);
	regmap_ग_लिखो(fsl_dev->regmap, DCU_CTRLDESCLN(index, 8),
		     DCU_LAYER_FG_FCOLOR(0));
	regmap_ग_लिखो(fsl_dev->regmap, DCU_CTRLDESCLN(index, 9),
		     DCU_LAYER_BG_BCOLOR(0));

	अगर (!म_भेद(fsl_dev->soc->name, "ls1021a")) अणु
		regmap_ग_लिखो(fsl_dev->regmap, DCU_CTRLDESCLN(index, 10),
			     DCU_LAYER_POST_SKIP(0) |
			     DCU_LAYER_PRE_SKIP(0));
	पूर्ण

	वापस;
पूर्ण

अटल स्थिर काष्ठा drm_plane_helper_funcs fsl_dcu_drm_plane_helper_funcs = अणु
	.atomic_check = fsl_dcu_drm_plane_atomic_check,
	.atomic_disable = fsl_dcu_drm_plane_atomic_disable,
	.atomic_update = fsl_dcu_drm_plane_atomic_update,
पूर्ण;

अटल व्योम fsl_dcu_drm_plane_destroy(काष्ठा drm_plane *plane)
अणु
	drm_plane_cleanup(plane);
	kमुक्त(plane);
पूर्ण

अटल स्थिर काष्ठा drm_plane_funcs fsl_dcu_drm_plane_funcs = अणु
	.atomic_duplicate_state = drm_atomic_helper_plane_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_plane_destroy_state,
	.destroy = fsl_dcu_drm_plane_destroy,
	.disable_plane = drm_atomic_helper_disable_plane,
	.reset = drm_atomic_helper_plane_reset,
	.update_plane = drm_atomic_helper_update_plane,
पूर्ण;

अटल स्थिर u32 fsl_dcu_drm_plane_क्रमmats[] = अणु
	DRM_FORMAT_RGB565,
	DRM_FORMAT_RGB888,
	DRM_FORMAT_XRGB8888,
	DRM_FORMAT_ARGB8888,
	DRM_FORMAT_XRGB4444,
	DRM_FORMAT_ARGB4444,
	DRM_FORMAT_XRGB1555,
	DRM_FORMAT_ARGB1555,
	DRM_FORMAT_YUV422,
पूर्ण;

व्योम fsl_dcu_drm_init_planes(काष्ठा drm_device *dev)
अणु
	काष्ठा fsl_dcu_drm_device *fsl_dev = dev->dev_निजी;
	पूर्णांक i, j;

	क्रम (i = 0; i < fsl_dev->soc->total_layer; i++) अणु
		क्रम (j = 1; j <= fsl_dev->soc->layer_regs; j++)
			regmap_ग_लिखो(fsl_dev->regmap, DCU_CTRLDESCLN(i, j), 0);
	पूर्ण
पूर्ण

काष्ठा drm_plane *fsl_dcu_drm_primary_create_plane(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_plane *primary;
	पूर्णांक ret;

	primary = kzalloc(माप(*primary), GFP_KERNEL);
	अगर (!primary) अणु
		DRM_DEBUG_KMS("Failed to allocate primary plane\n");
		वापस शून्य;
	पूर्ण

	/* possible_crtc's will be filled in later by crtc_init */
	ret = drm_universal_plane_init(dev, primary, 0,
				       &fsl_dcu_drm_plane_funcs,
				       fsl_dcu_drm_plane_क्रमmats,
				       ARRAY_SIZE(fsl_dcu_drm_plane_क्रमmats),
				       शून्य, DRM_PLANE_TYPE_PRIMARY, शून्य);
	अगर (ret) अणु
		kमुक्त(primary);
		primary = शून्य;
	पूर्ण
	drm_plane_helper_add(primary, &fsl_dcu_drm_plane_helper_funcs);

	वापस primary;
पूर्ण
