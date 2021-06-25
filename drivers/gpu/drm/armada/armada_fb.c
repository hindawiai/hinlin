<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012 Russell King
 */

#समावेश <drm/drm_modeset_helper.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_gem_framebuffer_helper.h>

#समावेश "armada_drm.h"
#समावेश "armada_fb.h"
#समावेश "armada_gem.h"
#समावेश "armada_hw.h"

अटल स्थिर काष्ठा drm_framebuffer_funcs armada_fb_funcs = अणु
	.destroy	= drm_gem_fb_destroy,
	.create_handle	= drm_gem_fb_create_handle,
पूर्ण;

काष्ठा armada_framebuffer *armada_framebuffer_create(काष्ठा drm_device *dev,
	स्थिर काष्ठा drm_mode_fb_cmd2 *mode, काष्ठा armada_gem_object *obj)
अणु
	काष्ठा armada_framebuffer *dfb;
	uपूर्णांक8_t क्रमmat, config;
	पूर्णांक ret;

	चयन (mode->pixel_क्रमmat) अणु
#घोषणा FMT(drm, fmt, mod)		\
	हाल DRM_FORMAT_##drm:		\
		क्रमmat = CFG_##fmt;	\
		config = mod;		\
		अवरोध
	FMT(RGB565,	565,		CFG_SWAPRB);
	FMT(BGR565,	565,		0);
	FMT(ARGB1555,	1555,		CFG_SWAPRB);
	FMT(ABGR1555,	1555,		0);
	FMT(RGB888,	888PACK,	CFG_SWAPRB);
	FMT(BGR888,	888PACK,	0);
	FMT(XRGB8888,	X888,		CFG_SWAPRB);
	FMT(XBGR8888,	X888,		0);
	FMT(ARGB8888,	8888,		CFG_SWAPRB);
	FMT(ABGR8888,	8888,		0);
	FMT(YUYV,	422PACK,	CFG_YUV2RGB | CFG_SWAPYU | CFG_SWAPUV);
	FMT(UYVY,	422PACK,	CFG_YUV2RGB);
	FMT(VYUY,	422PACK,	CFG_YUV2RGB | CFG_SWAPUV);
	FMT(YVYU,	422PACK,	CFG_YUV2RGB | CFG_SWAPYU);
	FMT(YUV422,	422,		CFG_YUV2RGB);
	FMT(YVU422,	422,		CFG_YUV2RGB | CFG_SWAPUV);
	FMT(YUV420,	420,		CFG_YUV2RGB);
	FMT(YVU420,	420,		CFG_YUV2RGB | CFG_SWAPUV);
	FMT(C8,		PSEUDO8,	0);
#अघोषित FMT
	शेष:
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	dfb = kzalloc(माप(*dfb), GFP_KERNEL);
	अगर (!dfb) अणु
		DRM_ERROR("failed to allocate Armada fb object\n");
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	dfb->fmt = क्रमmat;
	dfb->mod = config;
	dfb->fb.obj[0] = &obj->obj;

	drm_helper_mode_fill_fb_काष्ठा(dev, &dfb->fb, mode);

	ret = drm_framebuffer_init(dev, &dfb->fb, &armada_fb_funcs);
	अगर (ret) अणु
		kमुक्त(dfb);
		वापस ERR_PTR(ret);
	पूर्ण

	/*
	 * Take a reference on our object as we're successful - the
	 * caller alपढ़ोy holds a reference, which keeps us safe क्रम
	 * the above call, but the caller will drop their reference
	 * to it.  Hence we need to take our own reference.
	 */
	drm_gem_object_get(&obj->obj);

	वापस dfb;
पूर्ण

काष्ठा drm_framebuffer *armada_fb_create(काष्ठा drm_device *dev,
	काष्ठा drm_file *dfile, स्थिर काष्ठा drm_mode_fb_cmd2 *mode)
अणु
	स्थिर काष्ठा drm_क्रमmat_info *info = drm_get_क्रमmat_info(dev, mode);
	काष्ठा armada_gem_object *obj;
	काष्ठा armada_framebuffer *dfb;
	पूर्णांक ret;

	DRM_DEBUG_DRIVER("w%u h%u pf%08x f%u p%u,%u,%u\n",
		mode->width, mode->height, mode->pixel_क्रमmat,
		mode->flags, mode->pitches[0], mode->pitches[1],
		mode->pitches[2]);

	/* We can only handle a single plane at the moment */
	अगर (info->num_planes > 1 &&
	    (mode->handles[0] != mode->handles[1] ||
	     mode->handles[0] != mode->handles[2])) अणु
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	obj = armada_gem_object_lookup(dfile, mode->handles[0]);
	अगर (!obj) अणु
		ret = -ENOENT;
		जाओ err;
	पूर्ण

	अगर (obj->obj.import_attach && !obj->sgt) अणु
		ret = armada_gem_map_import(obj);
		अगर (ret)
			जाओ err_unref;
	पूर्ण

	/* Framebuffer objects must have a valid device address क्रम scanout */
	अगर (!obj->mapped) अणु
		ret = -EINVAL;
		जाओ err_unref;
	पूर्ण

	dfb = armada_framebuffer_create(dev, mode, obj);
	अगर (IS_ERR(dfb)) अणु
		ret = PTR_ERR(dfb);
		जाओ err;
	पूर्ण

	drm_gem_object_put(&obj->obj);

	वापस &dfb->fb;

 err_unref:
	drm_gem_object_put(&obj->obj);
 err:
	DRM_ERROR("failed to initialize framebuffer: %d\n", ret);
	वापस ERR_PTR(ret);
पूर्ण
