<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) Fuzhou Rockchip Electronics Co.Ltd
 * Author:Mark Yao <mark.yao@rock-chips.com>
 */

#समावेश <drm/drm.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_probe_helper.h>

#समावेश "rockchip_drm_drv.h"
#समावेश "rockchip_drm_gem.h"
#समावेश "rockchip_drm_fb.h"
#समावेश "rockchip_drm_fbdev.h"

#घोषणा PREFERRED_BPP		32
#घोषणा to_drm_निजी(x) \
		container_of(x, काष्ठा rockchip_drm_निजी, fbdev_helper)

अटल पूर्णांक rockchip_fbdev_mmap(काष्ठा fb_info *info,
			       काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा drm_fb_helper *helper = info->par;
	काष्ठा rockchip_drm_निजी *निजी = to_drm_निजी(helper);

	वापस rockchip_gem_mmap_buf(निजी->fbdev_bo, vma);
पूर्ण

अटल स्थिर काष्ठा fb_ops rockchip_drm_fbdev_ops = अणु
	.owner		= THIS_MODULE,
	DRM_FB_HELPER_DEFAULT_OPS,
	.fb_mmap	= rockchip_fbdev_mmap,
	.fb_fillrect	= drm_fb_helper_cfb_fillrect,
	.fb_copyarea	= drm_fb_helper_cfb_copyarea,
	.fb_imageblit	= drm_fb_helper_cfb_imageblit,
पूर्ण;

अटल पूर्णांक rockchip_drm_fbdev_create(काष्ठा drm_fb_helper *helper,
				     काष्ठा drm_fb_helper_surface_size *sizes)
अणु
	काष्ठा rockchip_drm_निजी *निजी = to_drm_निजी(helper);
	काष्ठा drm_mode_fb_cmd2 mode_cmd = अणु 0 पूर्ण;
	काष्ठा drm_device *dev = helper->dev;
	काष्ठा rockchip_gem_object *rk_obj;
	काष्ठा drm_framebuffer *fb;
	अचिन्हित पूर्णांक bytes_per_pixel;
	अचिन्हित दीर्घ offset;
	काष्ठा fb_info *fbi;
	माप_प्रकार size;
	पूर्णांक ret;

	bytes_per_pixel = DIV_ROUND_UP(sizes->surface_bpp, 8);

	mode_cmd.width = sizes->surface_width;
	mode_cmd.height = sizes->surface_height;
	mode_cmd.pitches[0] = sizes->surface_width * bytes_per_pixel;
	mode_cmd.pixel_क्रमmat = drm_mode_legacy_fb_क्रमmat(sizes->surface_bpp,
		sizes->surface_depth);

	size = mode_cmd.pitches[0] * mode_cmd.height;

	rk_obj = rockchip_gem_create_object(dev, size, true);
	अगर (IS_ERR(rk_obj))
		वापस -ENOMEM;

	निजी->fbdev_bo = &rk_obj->base;

	fbi = drm_fb_helper_alloc_fbi(helper);
	अगर (IS_ERR(fbi)) अणु
		DRM_DEV_ERROR(dev->dev, "Failed to create framebuffer info.\n");
		ret = PTR_ERR(fbi);
		जाओ out;
	पूर्ण

	helper->fb = rockchip_drm_framebuffer_init(dev, &mode_cmd,
						   निजी->fbdev_bo);
	अगर (IS_ERR(helper->fb)) अणु
		DRM_DEV_ERROR(dev->dev,
			      "Failed to allocate DRM framebuffer.\n");
		ret = PTR_ERR(helper->fb);
		जाओ out;
	पूर्ण

	fbi->fbops = &rockchip_drm_fbdev_ops;

	fb = helper->fb;
	drm_fb_helper_fill_info(fbi, helper, sizes);

	offset = fbi->var.xoffset * bytes_per_pixel;
	offset += fbi->var.yoffset * fb->pitches[0];

	dev->mode_config.fb_base = 0;
	fbi->screen_base = rk_obj->kvaddr + offset;
	fbi->screen_size = rk_obj->base.size;
	fbi->fix.smem_len = rk_obj->base.size;

	DRM_DEBUG_KMS("FB [%dx%d]-%d kvaddr=%p offset=%ld size=%zu\n",
		      fb->width, fb->height, fb->क्रमmat->depth,
		      rk_obj->kvaddr,
		      offset, size);

	वापस 0;

out:
	rockchip_gem_मुक्त_object(&rk_obj->base);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा drm_fb_helper_funcs rockchip_drm_fb_helper_funcs = अणु
	.fb_probe = rockchip_drm_fbdev_create,
पूर्ण;

पूर्णांक rockchip_drm_fbdev_init(काष्ठा drm_device *dev)
अणु
	काष्ठा rockchip_drm_निजी *निजी = dev->dev_निजी;
	काष्ठा drm_fb_helper *helper;
	पूर्णांक ret;

	अगर (!dev->mode_config.num_crtc || !dev->mode_config.num_connector)
		वापस -EINVAL;

	helper = &निजी->fbdev_helper;

	drm_fb_helper_prepare(dev, helper, &rockchip_drm_fb_helper_funcs);

	ret = drm_fb_helper_init(dev, helper);
	अगर (ret < 0) अणु
		DRM_DEV_ERROR(dev->dev,
			      "Failed to initialize drm fb helper - %d.\n",
			      ret);
		वापस ret;
	पूर्ण

	ret = drm_fb_helper_initial_config(helper, PREFERRED_BPP);
	अगर (ret < 0) अणु
		DRM_DEV_ERROR(dev->dev,
			      "Failed to set initial hw config - %d.\n",
			      ret);
		जाओ err_drm_fb_helper_fini;
	पूर्ण

	वापस 0;

err_drm_fb_helper_fini:
	drm_fb_helper_fini(helper);
	वापस ret;
पूर्ण

व्योम rockchip_drm_fbdev_fini(काष्ठा drm_device *dev)
अणु
	काष्ठा rockchip_drm_निजी *निजी = dev->dev_निजी;
	काष्ठा drm_fb_helper *helper;

	helper = &निजी->fbdev_helper;

	drm_fb_helper_unरेजिस्टर_fbi(helper);

	अगर (helper->fb)
		drm_framebuffer_put(helper->fb);

	drm_fb_helper_fini(helper);
पूर्ण
