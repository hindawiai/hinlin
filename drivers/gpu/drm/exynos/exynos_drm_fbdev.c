<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* exynos_drm_fbdev.c
 *
 * Copyright (c) 2011 Samsung Electronics Co., Ltd.
 * Authors:
 *	Inki Dae <inki.dae@samsung.com>
 *	Joonyoung Shim <jy0922.shim@samsung.com>
 *	Seung-Woo Kim <sw0312.kim@samsung.com>
 */

#समावेश <linux/console.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/exynos_drm.h>

#समावेश "exynos_drm_drv.h"
#समावेश "exynos_drm_fb.h"
#समावेश "exynos_drm_fbdev.h"

#घोषणा MAX_CONNECTOR		4
#घोषणा PREFERRED_BPP		32

#घोषणा to_exynos_fbdev(x)	container_of(x, काष्ठा exynos_drm_fbdev,\
				drm_fb_helper)

काष्ठा exynos_drm_fbdev अणु
	काष्ठा drm_fb_helper	drm_fb_helper;
	काष्ठा exynos_drm_gem	*exynos_gem;
पूर्ण;

अटल पूर्णांक exynos_drm_fb_mmap(काष्ठा fb_info *info,
			काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा drm_fb_helper *helper = info->par;
	काष्ठा exynos_drm_fbdev *exynos_fbd = to_exynos_fbdev(helper);
	काष्ठा exynos_drm_gem *exynos_gem = exynos_fbd->exynos_gem;
	अचिन्हित दीर्घ vm_size;
	पूर्णांक ret;

	vma->vm_flags |= VM_IO | VM_DONTEXPAND | VM_DONTDUMP;

	vm_size = vma->vm_end - vma->vm_start;

	अगर (vm_size > exynos_gem->size)
		वापस -EINVAL;

	ret = dma_mmap_attrs(to_dma_dev(helper->dev), vma, exynos_gem->cookie,
			     exynos_gem->dma_addr, exynos_gem->size,
			     exynos_gem->dma_attrs);
	अगर (ret < 0) अणु
		DRM_DEV_ERROR(to_dma_dev(helper->dev), "failed to mmap.\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fb_ops exynos_drm_fb_ops = अणु
	.owner		= THIS_MODULE,
	DRM_FB_HELPER_DEFAULT_OPS,
	.fb_mmap        = exynos_drm_fb_mmap,
	.fb_fillrect	= drm_fb_helper_cfb_fillrect,
	.fb_copyarea	= drm_fb_helper_cfb_copyarea,
	.fb_imageblit	= drm_fb_helper_cfb_imageblit,
पूर्ण;

अटल पूर्णांक exynos_drm_fbdev_update(काष्ठा drm_fb_helper *helper,
				   काष्ठा drm_fb_helper_surface_size *sizes,
				   काष्ठा exynos_drm_gem *exynos_gem)
अणु
	काष्ठा fb_info *fbi;
	काष्ठा drm_framebuffer *fb = helper->fb;
	अचिन्हित पूर्णांक size = fb->width * fb->height * fb->क्रमmat->cpp[0];
	अचिन्हित दीर्घ offset;

	fbi = drm_fb_helper_alloc_fbi(helper);
	अगर (IS_ERR(fbi)) अणु
		DRM_DEV_ERROR(to_dma_dev(helper->dev),
			      "failed to allocate fb info.\n");
		वापस PTR_ERR(fbi);
	पूर्ण

	fbi->fbops = &exynos_drm_fb_ops;

	drm_fb_helper_fill_info(fbi, helper, sizes);

	offset = fbi->var.xoffset * fb->क्रमmat->cpp[0];
	offset += fbi->var.yoffset * fb->pitches[0];

	fbi->screen_buffer = exynos_gem->kvaddr + offset;
	fbi->screen_size = size;
	fbi->fix.smem_len = size;

	वापस 0;
पूर्ण

अटल पूर्णांक exynos_drm_fbdev_create(काष्ठा drm_fb_helper *helper,
				    काष्ठा drm_fb_helper_surface_size *sizes)
अणु
	काष्ठा exynos_drm_fbdev *exynos_fbdev = to_exynos_fbdev(helper);
	काष्ठा exynos_drm_gem *exynos_gem;
	काष्ठा drm_device *dev = helper->dev;
	काष्ठा drm_mode_fb_cmd2 mode_cmd = अणु 0 पूर्ण;
	अचिन्हित दीर्घ size;
	पूर्णांक ret;

	DRM_DEV_DEBUG_KMS(dev->dev,
			  "surface width(%d), height(%d) and bpp(%d\n",
			  sizes->surface_width, sizes->surface_height,
			  sizes->surface_bpp);

	mode_cmd.width = sizes->surface_width;
	mode_cmd.height = sizes->surface_height;
	mode_cmd.pitches[0] = sizes->surface_width * (sizes->surface_bpp >> 3);
	mode_cmd.pixel_क्रमmat = drm_mode_legacy_fb_क्रमmat(sizes->surface_bpp,
							  sizes->surface_depth);

	size = mode_cmd.pitches[0] * mode_cmd.height;

	exynos_gem = exynos_drm_gem_create(dev, EXYNOS_BO_WC, size, true);
	अगर (IS_ERR(exynos_gem))
		वापस PTR_ERR(exynos_gem);

	exynos_fbdev->exynos_gem = exynos_gem;

	helper->fb =
		exynos_drm_framebuffer_init(dev, &mode_cmd, &exynos_gem, 1);
	अगर (IS_ERR(helper->fb)) अणु
		DRM_DEV_ERROR(dev->dev, "failed to create drm framebuffer.\n");
		ret = PTR_ERR(helper->fb);
		जाओ err_destroy_gem;
	पूर्ण

	ret = exynos_drm_fbdev_update(helper, sizes, exynos_gem);
	अगर (ret < 0)
		जाओ err_destroy_framebuffer;

	वापस ret;

err_destroy_framebuffer:
	drm_framebuffer_cleanup(helper->fb);
err_destroy_gem:
	exynos_drm_gem_destroy(exynos_gem);

	/*
	 * अगर failed, all resources allocated above would be released by
	 * drm_mode_config_cleanup() when drm_load() had been called prior
	 * to any specअगरic driver such as fimd or hdmi driver.
	 */

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा drm_fb_helper_funcs exynos_drm_fb_helper_funcs = अणु
	.fb_probe =	exynos_drm_fbdev_create,
पूर्ण;

पूर्णांक exynos_drm_fbdev_init(काष्ठा drm_device *dev)
अणु
	काष्ठा exynos_drm_fbdev *fbdev;
	काष्ठा exynos_drm_निजी *निजी = dev->dev_निजी;
	काष्ठा drm_fb_helper *helper;
	पूर्णांक ret;

	अगर (!dev->mode_config.num_crtc)
		वापस 0;

	fbdev = kzalloc(माप(*fbdev), GFP_KERNEL);
	अगर (!fbdev)
		वापस -ENOMEM;

	निजी->fb_helper = helper = &fbdev->drm_fb_helper;

	drm_fb_helper_prepare(dev, helper, &exynos_drm_fb_helper_funcs);

	ret = drm_fb_helper_init(dev, helper);
	अगर (ret < 0) अणु
		DRM_DEV_ERROR(dev->dev,
			      "failed to initialize drm fb helper.\n");
		जाओ err_init;
	पूर्ण

	ret = drm_fb_helper_initial_config(helper, PREFERRED_BPP);
	अगर (ret < 0) अणु
		DRM_DEV_ERROR(dev->dev,
			      "failed to set up hw configuration.\n");
		जाओ err_setup;
	पूर्ण

	वापस 0;

err_setup:
	drm_fb_helper_fini(helper);

err_init:
	निजी->fb_helper = शून्य;
	kमुक्त(fbdev);

	वापस ret;
पूर्ण

अटल व्योम exynos_drm_fbdev_destroy(काष्ठा drm_device *dev,
				      काष्ठा drm_fb_helper *fb_helper)
अणु
	काष्ठा drm_framebuffer *fb;

	/* release drm framebuffer and real buffer */
	अगर (fb_helper->fb && fb_helper->fb->funcs) अणु
		fb = fb_helper->fb;
		अगर (fb)
			drm_framebuffer_हटाओ(fb);
	पूर्ण

	drm_fb_helper_unरेजिस्टर_fbi(fb_helper);

	drm_fb_helper_fini(fb_helper);
पूर्ण

व्योम exynos_drm_fbdev_fini(काष्ठा drm_device *dev)
अणु
	काष्ठा exynos_drm_निजी *निजी = dev->dev_निजी;
	काष्ठा exynos_drm_fbdev *fbdev;

	अगर (!निजी || !निजी->fb_helper)
		वापस;

	fbdev = to_exynos_fbdev(निजी->fb_helper);

	exynos_drm_fbdev_destroy(dev, निजी->fb_helper);
	kमुक्त(fbdev);
	निजी->fb_helper = शून्य;
पूर्ण

