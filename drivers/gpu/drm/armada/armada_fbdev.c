<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012 Russell King
 *  Written from the i915 driver.
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>

#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_fourcc.h>

#समावेश "armada_crtc.h"
#समावेश "armada_drm.h"
#समावेश "armada_fb.h"
#समावेश "armada_gem.h"

अटल स्थिर काष्ठा fb_ops armada_fb_ops = अणु
	.owner		= THIS_MODULE,
	DRM_FB_HELPER_DEFAULT_OPS,
	.fb_fillrect	= drm_fb_helper_cfb_fillrect,
	.fb_copyarea	= drm_fb_helper_cfb_copyarea,
	.fb_imageblit	= drm_fb_helper_cfb_imageblit,
पूर्ण;

अटल पूर्णांक armada_fbdev_create(काष्ठा drm_fb_helper *fbh,
	काष्ठा drm_fb_helper_surface_size *sizes)
अणु
	काष्ठा drm_device *dev = fbh->dev;
	काष्ठा drm_mode_fb_cmd2 mode;
	काष्ठा armada_framebuffer *dfb;
	काष्ठा armada_gem_object *obj;
	काष्ठा fb_info *info;
	पूर्णांक size, ret;
	व्योम *ptr;

	स_रखो(&mode, 0, माप(mode));
	mode.width = sizes->surface_width;
	mode.height = sizes->surface_height;
	mode.pitches[0] = armada_pitch(mode.width, sizes->surface_bpp);
	mode.pixel_क्रमmat = drm_mode_legacy_fb_क्रमmat(sizes->surface_bpp,
					sizes->surface_depth);

	size = mode.pitches[0] * mode.height;
	obj = armada_gem_alloc_निजी_object(dev, size);
	अगर (!obj) अणु
		DRM_ERROR("failed to allocate fb memory\n");
		वापस -ENOMEM;
	पूर्ण

	ret = armada_gem_linear_back(dev, obj);
	अगर (ret) अणु
		drm_gem_object_put(&obj->obj);
		वापस ret;
	पूर्ण

	ptr = armada_gem_map_object(dev, obj);
	अगर (!ptr) अणु
		drm_gem_object_put(&obj->obj);
		वापस -ENOMEM;
	पूर्ण

	dfb = armada_framebuffer_create(dev, &mode, obj);

	/*
	 * A reference is now held by the framebuffer object अगर
	 * successful, otherwise this drops the ref क्रम the error path.
	 */
	drm_gem_object_put(&obj->obj);

	अगर (IS_ERR(dfb))
		वापस PTR_ERR(dfb);

	info = drm_fb_helper_alloc_fbi(fbh);
	अगर (IS_ERR(info)) अणु
		ret = PTR_ERR(info);
		जाओ err_fballoc;
	पूर्ण

	info->fbops = &armada_fb_ops;
	info->fix.smem_start = obj->phys_addr;
	info->fix.smem_len = obj->obj.size;
	info->screen_size = obj->obj.size;
	info->screen_base = ptr;
	fbh->fb = &dfb->fb;

	drm_fb_helper_fill_info(info, fbh, sizes);

	DRM_DEBUG_KMS("allocated %dx%d %dbpp fb: 0x%08llx\n",
		dfb->fb.width, dfb->fb.height, dfb->fb.क्रमmat->cpp[0] * 8,
		(अचिन्हित दीर्घ दीर्घ)obj->phys_addr);

	वापस 0;

 err_fballoc:
	dfb->fb.funcs->destroy(&dfb->fb);
	वापस ret;
पूर्ण

अटल पूर्णांक armada_fb_probe(काष्ठा drm_fb_helper *fbh,
	काष्ठा drm_fb_helper_surface_size *sizes)
अणु
	पूर्णांक ret = 0;

	अगर (!fbh->fb) अणु
		ret = armada_fbdev_create(fbh, sizes);
		अगर (ret == 0)
			ret = 1;
	पूर्ण
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा drm_fb_helper_funcs armada_fb_helper_funcs = अणु
	.fb_probe	= armada_fb_probe,
पूर्ण;

पूर्णांक armada_fbdev_init(काष्ठा drm_device *dev)
अणु
	काष्ठा armada_निजी *priv = drm_to_armada_dev(dev);
	काष्ठा drm_fb_helper *fbh;
	पूर्णांक ret;

	fbh = devm_kzalloc(dev->dev, माप(*fbh), GFP_KERNEL);
	अगर (!fbh)
		वापस -ENOMEM;

	priv->fbdev = fbh;

	drm_fb_helper_prepare(dev, fbh, &armada_fb_helper_funcs);

	ret = drm_fb_helper_init(dev, fbh);
	अगर (ret) अणु
		DRM_ERROR("failed to initialize drm fb helper\n");
		जाओ err_fb_helper;
	पूर्ण

	ret = drm_fb_helper_initial_config(fbh, 32);
	अगर (ret) अणु
		DRM_ERROR("failed to set initial config\n");
		जाओ err_fb_setup;
	पूर्ण

	वापस 0;
 err_fb_setup:
	drm_fb_helper_fini(fbh);
 err_fb_helper:
	priv->fbdev = शून्य;
	वापस ret;
पूर्ण

व्योम armada_fbdev_fini(काष्ठा drm_device *dev)
अणु
	काष्ठा armada_निजी *priv = drm_to_armada_dev(dev);
	काष्ठा drm_fb_helper *fbh = priv->fbdev;

	अगर (fbh) अणु
		drm_fb_helper_unरेजिस्टर_fbi(fbh);

		drm_fb_helper_fini(fbh);

		अगर (fbh->fb)
			fbh->fb->funcs->destroy(fbh->fb);

		priv->fbdev = शून्य;
	पूर्ण
पूर्ण
