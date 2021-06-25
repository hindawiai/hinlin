<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2013 Red Hat
 * Author: Rob Clark <robdclark@gmail.com>
 */

#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_fourcc.h>

#समावेश "msm_drv.h"
#समावेश "msm_gem.h"
#समावेश "msm_kms.h"

बाह्य पूर्णांक msm_gem_mmap_obj(काष्ठा drm_gem_object *obj,
					काष्ठा vm_area_काष्ठा *vma);
अटल पूर्णांक msm_fbdev_mmap(काष्ठा fb_info *info, काष्ठा vm_area_काष्ठा *vma);

/*
 * fbdev funcs, to implement legacy fbdev पूर्णांकerface on top of drm driver
 */

#घोषणा to_msm_fbdev(x) container_of(x, काष्ठा msm_fbdev, base)

काष्ठा msm_fbdev अणु
	काष्ठा drm_fb_helper base;
	काष्ठा drm_framebuffer *fb;
पूर्ण;

अटल स्थिर काष्ठा fb_ops msm_fb_ops = अणु
	.owner = THIS_MODULE,
	DRM_FB_HELPER_DEFAULT_OPS,

	/* Note: to properly handle manual update displays, we wrap the
	 * basic fbdev ops which ग_लिखो to the framebuffer
	 */
	.fb_पढ़ो = drm_fb_helper_sys_पढ़ो,
	.fb_ग_लिखो = drm_fb_helper_sys_ग_लिखो,
	.fb_fillrect = drm_fb_helper_sys_fillrect,
	.fb_copyarea = drm_fb_helper_sys_copyarea,
	.fb_imageblit = drm_fb_helper_sys_imageblit,
	.fb_mmap = msm_fbdev_mmap,
पूर्ण;

अटल पूर्णांक msm_fbdev_mmap(काष्ठा fb_info *info, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा drm_fb_helper *helper = (काष्ठा drm_fb_helper *)info->par;
	काष्ठा msm_fbdev *fbdev = to_msm_fbdev(helper);
	काष्ठा drm_gem_object *bo = msm_framebuffer_bo(fbdev->fb, 0);
	पूर्णांक ret = 0;

	ret = drm_gem_mmap_obj(bo, bo->size, vma);
	अगर (ret) अणु
		pr_err("%s:drm_gem_mmap_obj fail\n", __func__);
		वापस ret;
	पूर्ण

	वापस msm_gem_mmap_obj(bo, vma);
पूर्ण

अटल पूर्णांक msm_fbdev_create(काष्ठा drm_fb_helper *helper,
		काष्ठा drm_fb_helper_surface_size *sizes)
अणु
	काष्ठा msm_fbdev *fbdev = to_msm_fbdev(helper);
	काष्ठा drm_device *dev = helper->dev;
	काष्ठा msm_drm_निजी *priv = dev->dev_निजी;
	काष्ठा drm_framebuffer *fb = शून्य;
	काष्ठा drm_gem_object *bo;
	काष्ठा fb_info *fbi = शून्य;
	uपूर्णांक64_t paddr;
	uपूर्णांक32_t क्रमmat;
	पूर्णांक ret, pitch;

	क्रमmat = drm_mode_legacy_fb_क्रमmat(sizes->surface_bpp, sizes->surface_depth);

	DBG("create fbdev: %dx%d@%d (%dx%d)", sizes->surface_width,
			sizes->surface_height, sizes->surface_bpp,
			sizes->fb_width, sizes->fb_height);

	pitch = align_pitch(sizes->surface_width, sizes->surface_bpp);
	fb = msm_alloc_stolen_fb(dev, sizes->surface_width,
			sizes->surface_height, pitch, क्रमmat);

	अगर (IS_ERR(fb)) अणु
		DRM_DEV_ERROR(dev->dev, "failed to allocate fb\n");
		वापस PTR_ERR(fb);
	पूर्ण

	bo = msm_framebuffer_bo(fb, 0);

	mutex_lock(&dev->काष्ठा_mutex);

	/*
	 * NOTE: अगर we can be guaranteed to be able to map buffer
	 * in panic (ie. lock-safe, etc) we could aव्योम pinning the
	 * buffer now:
	 */
	ret = msm_gem_get_and_pin_iova(bo, priv->kms->aspace, &paddr);
	अगर (ret) अणु
		DRM_DEV_ERROR(dev->dev, "failed to get buffer obj iova: %d\n", ret);
		जाओ fail_unlock;
	पूर्ण

	fbi = drm_fb_helper_alloc_fbi(helper);
	अगर (IS_ERR(fbi)) अणु
		DRM_DEV_ERROR(dev->dev, "failed to allocate fb info\n");
		ret = PTR_ERR(fbi);
		जाओ fail_unlock;
	पूर्ण

	DBG("fbi=%p, dev=%p", fbi, dev);

	fbdev->fb = fb;
	helper->fb = fb;

	fbi->fbops = &msm_fb_ops;

	drm_fb_helper_fill_info(fbi, helper, sizes);

	dev->mode_config.fb_base = paddr;

	fbi->screen_base = msm_gem_get_vaddr(bo);
	अगर (IS_ERR(fbi->screen_base)) अणु
		ret = PTR_ERR(fbi->screen_base);
		जाओ fail_unlock;
	पूर्ण
	fbi->screen_size = bo->size;
	fbi->fix.smem_start = paddr;
	fbi->fix.smem_len = bo->size;

	DBG("par=%p, %dx%d", fbi->par, fbi->var.xres, fbi->var.yres);
	DBG("allocated %dx%d fb", fbdev->fb->width, fbdev->fb->height);

	mutex_unlock(&dev->काष्ठा_mutex);

	वापस 0;

fail_unlock:
	mutex_unlock(&dev->काष्ठा_mutex);
	drm_framebuffer_हटाओ(fb);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा drm_fb_helper_funcs msm_fb_helper_funcs = अणु
	.fb_probe = msm_fbdev_create,
पूर्ण;

/* initialize fbdev helper */
काष्ठा drm_fb_helper *msm_fbdev_init(काष्ठा drm_device *dev)
अणु
	काष्ठा msm_drm_निजी *priv = dev->dev_निजी;
	काष्ठा msm_fbdev *fbdev = शून्य;
	काष्ठा drm_fb_helper *helper;
	पूर्णांक ret;

	fbdev = kzalloc(माप(*fbdev), GFP_KERNEL);
	अगर (!fbdev)
		जाओ fail;

	helper = &fbdev->base;

	drm_fb_helper_prepare(dev, helper, &msm_fb_helper_funcs);

	ret = drm_fb_helper_init(dev, helper);
	अगर (ret) अणु
		DRM_DEV_ERROR(dev->dev, "could not init fbdev: ret=%d\n", ret);
		जाओ fail;
	पूर्ण

	/* the fw fb could be anywhere in memory */
	drm_fb_helper_हटाओ_conflicting_framebuffers(शून्य, "msm", false);

	ret = drm_fb_helper_initial_config(helper, 32);
	अगर (ret)
		जाओ fini;

	priv->fbdev = helper;

	वापस helper;

fini:
	drm_fb_helper_fini(helper);
fail:
	kमुक्त(fbdev);
	वापस शून्य;
पूर्ण

व्योम msm_fbdev_मुक्त(काष्ठा drm_device *dev)
अणु
	काष्ठा msm_drm_निजी *priv = dev->dev_निजी;
	काष्ठा drm_fb_helper *helper = priv->fbdev;
	काष्ठा msm_fbdev *fbdev;

	DBG();

	drm_fb_helper_unरेजिस्टर_fbi(helper);

	drm_fb_helper_fini(helper);

	fbdev = to_msm_fbdev(priv->fbdev);

	/* this will मुक्त the backing object */
	अगर (fbdev->fb) अणु
		काष्ठा drm_gem_object *bo =
			msm_framebuffer_bo(fbdev->fb, 0);
		msm_gem_put_vaddr(bo);
		drm_framebuffer_हटाओ(fbdev->fb);
	पूर्ण

	kमुक्त(fbdev);

	priv->fbdev = शून्य;
पूर्ण
