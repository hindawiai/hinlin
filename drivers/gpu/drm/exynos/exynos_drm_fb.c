<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* exynos_drm_fb.c
 *
 * Copyright (c) 2011 Samsung Electronics Co., Ltd.
 * Authors:
 *	Inki Dae <inki.dae@samsung.com>
 *	Joonyoung Shim <jy0922.shim@samsung.com>
 *	Seung-Woo Kim <sw0312.kim@samsung.com>
 */

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_gem_framebuffer_helper.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/exynos_drm.h>

#समावेश "exynos_drm_crtc.h"
#समावेश "exynos_drm_drv.h"
#समावेश "exynos_drm_fb.h"
#समावेश "exynos_drm_fbdev.h"

अटल पूर्णांक check_fb_gem_memory_type(काष्ठा drm_device *drm_dev,
				    काष्ठा exynos_drm_gem *exynos_gem)
अणु
	अचिन्हित पूर्णांक flags;

	/*
	 * अगर exynos drm driver supports iommu then framebuffer can use
	 * all the buffer types.
	 */
	अगर (is_drm_iommu_supported(drm_dev))
		वापस 0;

	flags = exynos_gem->flags;

	/*
	 * Physically non-contiguous memory type क्रम framebuffer is not
	 * supported without IOMMU.
	 */
	अगर (IS_NONCONTIG_BUFFER(flags)) अणु
		DRM_DEV_ERROR(drm_dev->dev,
			      "Non-contiguous GEM memory is not supported.\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_framebuffer_funcs exynos_drm_fb_funcs = अणु
	.destroy	= drm_gem_fb_destroy,
	.create_handle	= drm_gem_fb_create_handle,
पूर्ण;

काष्ठा drm_framebuffer *
exynos_drm_framebuffer_init(काष्ठा drm_device *dev,
			    स्थिर काष्ठा drm_mode_fb_cmd2 *mode_cmd,
			    काष्ठा exynos_drm_gem **exynos_gem,
			    पूर्णांक count)
अणु
	काष्ठा drm_framebuffer *fb;
	पूर्णांक i;
	पूर्णांक ret;

	fb = kzalloc(माप(*fb), GFP_KERNEL);
	अगर (!fb)
		वापस ERR_PTR(-ENOMEM);

	क्रम (i = 0; i < count; i++) अणु
		ret = check_fb_gem_memory_type(dev, exynos_gem[i]);
		अगर (ret < 0)
			जाओ err;

		fb->obj[i] = &exynos_gem[i]->base;
	पूर्ण

	drm_helper_mode_fill_fb_काष्ठा(dev, fb, mode_cmd);

	ret = drm_framebuffer_init(dev, fb, &exynos_drm_fb_funcs);
	अगर (ret < 0) अणु
		DRM_DEV_ERROR(dev->dev,
			      "failed to initialize framebuffer\n");
		जाओ err;
	पूर्ण

	वापस fb;

err:
	kमुक्त(fb);
	वापस ERR_PTR(ret);
पूर्ण

अटल काष्ठा drm_framebuffer *
exynos_user_fb_create(काष्ठा drm_device *dev, काष्ठा drm_file *file_priv,
		      स्थिर काष्ठा drm_mode_fb_cmd2 *mode_cmd)
अणु
	स्थिर काष्ठा drm_क्रमmat_info *info = drm_get_क्रमmat_info(dev, mode_cmd);
	काष्ठा exynos_drm_gem *exynos_gem[MAX_FB_BUFFER];
	काष्ठा drm_framebuffer *fb;
	पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < info->num_planes; i++) अणु
		अचिन्हित पूर्णांक height = (i == 0) ? mode_cmd->height :
				     DIV_ROUND_UP(mode_cmd->height, info->vsub);
		अचिन्हित दीर्घ size = height * mode_cmd->pitches[i] +
				     mode_cmd->offsets[i];

		exynos_gem[i] = exynos_drm_gem_get(file_priv,
						   mode_cmd->handles[i]);
		अगर (!exynos_gem[i]) अणु
			DRM_DEV_ERROR(dev->dev,
				      "failed to lookup gem object\n");
			ret = -ENOENT;
			जाओ err;
		पूर्ण

		अगर (size > exynos_gem[i]->size) अणु
			i++;
			ret = -EINVAL;
			जाओ err;
		पूर्ण
	पूर्ण

	fb = exynos_drm_framebuffer_init(dev, mode_cmd, exynos_gem, i);
	अगर (IS_ERR(fb)) अणु
		ret = PTR_ERR(fb);
		जाओ err;
	पूर्ण

	वापस fb;

err:
	जबतक (i--)
		exynos_drm_gem_put(exynos_gem[i]);

	वापस ERR_PTR(ret);
पूर्ण

dma_addr_t exynos_drm_fb_dma_addr(काष्ठा drm_framebuffer *fb, पूर्णांक index)
अणु
	काष्ठा exynos_drm_gem *exynos_gem;

	अगर (WARN_ON_ONCE(index >= MAX_FB_BUFFER))
		वापस 0;

	exynos_gem = to_exynos_gem(fb->obj[index]);
	वापस exynos_gem->dma_addr + fb->offsets[index];
पूर्ण

अटल काष्ठा drm_mode_config_helper_funcs exynos_drm_mode_config_helpers = अणु
	.atomic_commit_tail = drm_atomic_helper_commit_tail_rpm,
पूर्ण;

अटल स्थिर काष्ठा drm_mode_config_funcs exynos_drm_mode_config_funcs = अणु
	.fb_create = exynos_user_fb_create,
	.output_poll_changed = drm_fb_helper_output_poll_changed,
	.atomic_check = drm_atomic_helper_check,
	.atomic_commit = drm_atomic_helper_commit,
पूर्ण;

व्योम exynos_drm_mode_config_init(काष्ठा drm_device *dev)
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

	dev->mode_config.funcs = &exynos_drm_mode_config_funcs;
	dev->mode_config.helper_निजी = &exynos_drm_mode_config_helpers;

	dev->mode_config.allow_fb_modअगरiers = true;

	dev->mode_config.normalize_zpos = true;
पूर्ण
