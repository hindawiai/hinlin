<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) Fuzhou Rockchip Electronics Co.Ltd
 * Author:Mark Yao <mark.yao@rock-chips.com>
 */

#समावेश <linux/kernel.h>

#समावेश <drm/drm.h>
#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_damage_helper.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_gem_framebuffer_helper.h>
#समावेश <drm/drm_probe_helper.h>

#समावेश "rockchip_drm_drv.h"
#समावेश "rockchip_drm_fb.h"
#समावेश "rockchip_drm_gem.h"

अटल स्थिर काष्ठा drm_framebuffer_funcs rockchip_drm_fb_funcs = अणु
	.destroy       = drm_gem_fb_destroy,
	.create_handle = drm_gem_fb_create_handle,
	.dirty	       = drm_atomic_helper_dirtyfb,
पूर्ण;

अटल काष्ठा drm_framebuffer *
rockchip_fb_alloc(काष्ठा drm_device *dev, स्थिर काष्ठा drm_mode_fb_cmd2 *mode_cmd,
		  काष्ठा drm_gem_object **obj, अचिन्हित पूर्णांक num_planes)
अणु
	काष्ठा drm_framebuffer *fb;
	पूर्णांक ret;
	पूर्णांक i;

	fb = kzalloc(माप(*fb), GFP_KERNEL);
	अगर (!fb)
		वापस ERR_PTR(-ENOMEM);

	drm_helper_mode_fill_fb_काष्ठा(dev, fb, mode_cmd);

	क्रम (i = 0; i < num_planes; i++)
		fb->obj[i] = obj[i];

	ret = drm_framebuffer_init(dev, fb, &rockchip_drm_fb_funcs);
	अगर (ret) अणु
		DRM_DEV_ERROR(dev->dev,
			      "Failed to initialize framebuffer: %d\n",
			      ret);
		kमुक्त(fb);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस fb;
पूर्ण

अटल स्थिर काष्ठा drm_mode_config_helper_funcs rockchip_mode_config_helpers = अणु
	.atomic_commit_tail = drm_atomic_helper_commit_tail_rpm,
पूर्ण;

अटल काष्ठा drm_framebuffer *
rockchip_fb_create(काष्ठा drm_device *dev, काष्ठा drm_file *file,
		   स्थिर काष्ठा drm_mode_fb_cmd2 *mode_cmd)
अणु
	काष्ठा drm_afbc_framebuffer *afbc_fb;
	स्थिर काष्ठा drm_क्रमmat_info *info;
	पूर्णांक ret;

	info = drm_get_क्रमmat_info(dev, mode_cmd);
	अगर (!info)
		वापस ERR_PTR(-ENOMEM);

	afbc_fb = kzalloc(माप(*afbc_fb), GFP_KERNEL);
	अगर (!afbc_fb)
		वापस ERR_PTR(-ENOMEM);

	ret = drm_gem_fb_init_with_funcs(dev, &afbc_fb->base, file, mode_cmd,
					 &rockchip_drm_fb_funcs);
	अगर (ret) अणु
		kमुक्त(afbc_fb);
		वापस ERR_PTR(ret);
	पूर्ण

	अगर (drm_is_afbc(mode_cmd->modअगरier[0])) अणु
		पूर्णांक ret, i;

		ret = drm_gem_fb_afbc_init(dev, mode_cmd, afbc_fb);
		अगर (ret) अणु
			काष्ठा drm_gem_object **obj = afbc_fb->base.obj;

			क्रम (i = 0; i < info->num_planes; ++i)
				drm_gem_object_put(obj[i]);

			kमुक्त(afbc_fb);
			वापस ERR_PTR(ret);
		पूर्ण
	पूर्ण

	वापस &afbc_fb->base;
पूर्ण

अटल स्थिर काष्ठा drm_mode_config_funcs rockchip_drm_mode_config_funcs = अणु
	.fb_create = rockchip_fb_create,
	.output_poll_changed = drm_fb_helper_output_poll_changed,
	.atomic_check = drm_atomic_helper_check,
	.atomic_commit = drm_atomic_helper_commit,
पूर्ण;

काष्ठा drm_framebuffer *
rockchip_drm_framebuffer_init(काष्ठा drm_device *dev,
			      स्थिर काष्ठा drm_mode_fb_cmd2 *mode_cmd,
			      काष्ठा drm_gem_object *obj)
अणु
	काष्ठा drm_framebuffer *fb;

	fb = rockchip_fb_alloc(dev, mode_cmd, &obj, 1);
	अगर (IS_ERR(fb))
		वापस ERR_CAST(fb);

	वापस fb;
पूर्ण

व्योम rockchip_drm_mode_config_init(काष्ठा drm_device *dev)
अणु
	dev->mode_config.min_width = 0;
	dev->mode_config.min_height = 0;

	/*
	 * set max width and height as शेष value(4096x4096).
	 * this value would be used to check framebuffer size limitation
	 * at drm_mode_addfb().
	 */
	dev->mode_config.max_width = 4096;
	dev->mode_config.max_height = 4096;

	dev->mode_config.funcs = &rockchip_drm_mode_config_funcs;
	dev->mode_config.helper_निजी = &rockchip_mode_config_helpers;
पूर्ण
