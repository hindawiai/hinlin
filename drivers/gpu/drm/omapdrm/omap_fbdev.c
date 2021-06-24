<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2011 Texas Instruments Incorporated - https://www.ti.com/
 * Author: Rob Clark <rob@ti.com>
 */

#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_util.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_fourcc.h>

#समावेश "omap_drv.h"

MODULE_PARM_DESC(ywrap, "Enable ywrap scrolling (omap44xx and later, default 'y')");
अटल bool ywrap_enabled = true;
module_param_named(ywrap, ywrap_enabled, bool, 0644);

/*
 * fbdev funcs, to implement legacy fbdev पूर्णांकerface on top of drm driver
 */

#घोषणा to_omap_fbdev(x) container_of(x, काष्ठा omap_fbdev, base)

काष्ठा omap_fbdev अणु
	काष्ठा drm_fb_helper base;
	काष्ठा drm_framebuffer *fb;
	काष्ठा drm_gem_object *bo;
	bool ywrap_enabled;

	/* क्रम deferred dmm roll when getting called in atomic ctx */
	काष्ठा work_काष्ठा work;
पूर्ण;

अटल काष्ठा drm_fb_helper *get_fb(काष्ठा fb_info *fbi);

अटल व्योम pan_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा omap_fbdev *fbdev = container_of(work, काष्ठा omap_fbdev, work);
	काष्ठा fb_info *fbi = fbdev->base.fbdev;
	पूर्णांक npages;

	/* DMM roll shअगरts in 4K pages: */
	npages = fbi->fix.line_length >> PAGE_SHIFT;
	omap_gem_roll(fbdev->bo, fbi->var.yoffset * npages);
पूर्ण

अटल पूर्णांक omap_fbdev_pan_display(काष्ठा fb_var_screeninfo *var,
		काष्ठा fb_info *fbi)
अणु
	काष्ठा drm_fb_helper *helper = get_fb(fbi);
	काष्ठा omap_fbdev *fbdev = to_omap_fbdev(helper);

	अगर (!helper)
		जाओ fallback;

	अगर (!fbdev->ywrap_enabled)
		जाओ fallback;

	अगर (drm_can_sleep()) अणु
		pan_worker(&fbdev->work);
	पूर्ण अन्यथा अणु
		काष्ठा omap_drm_निजी *priv = helper->dev->dev_निजी;
		queue_work(priv->wq, &fbdev->work);
	पूर्ण

	वापस 0;

fallback:
	वापस drm_fb_helper_pan_display(var, fbi);
पूर्ण

अटल स्थिर काष्ठा fb_ops omap_fb_ops = अणु
	.owner = THIS_MODULE,

	.fb_check_var	= drm_fb_helper_check_var,
	.fb_set_par	= drm_fb_helper_set_par,
	.fb_setcmap	= drm_fb_helper_setcmap,
	.fb_blank	= drm_fb_helper_blank,
	.fb_pan_display = omap_fbdev_pan_display,
	.fb_ioctl	= drm_fb_helper_ioctl,

	.fb_पढ़ो = drm_fb_helper_sys_पढ़ो,
	.fb_ग_लिखो = drm_fb_helper_sys_ग_लिखो,
	.fb_fillrect = drm_fb_helper_sys_fillrect,
	.fb_copyarea = drm_fb_helper_sys_copyarea,
	.fb_imageblit = drm_fb_helper_sys_imageblit,
पूर्ण;

अटल पूर्णांक omap_fbdev_create(काष्ठा drm_fb_helper *helper,
		काष्ठा drm_fb_helper_surface_size *sizes)
अणु
	काष्ठा omap_fbdev *fbdev = to_omap_fbdev(helper);
	काष्ठा drm_device *dev = helper->dev;
	काष्ठा omap_drm_निजी *priv = dev->dev_निजी;
	काष्ठा drm_framebuffer *fb = शून्य;
	जोड़ omap_gem_size gsize;
	काष्ठा fb_info *fbi = शून्य;
	काष्ठा drm_mode_fb_cmd2 mode_cmd = अणु0पूर्ण;
	dma_addr_t dma_addr;
	पूर्णांक ret;

	sizes->surface_bpp = 32;
	sizes->surface_depth = 24;

	DBG("create fbdev: %dx%d@%d (%dx%d)", sizes->surface_width,
			sizes->surface_height, sizes->surface_bpp,
			sizes->fb_width, sizes->fb_height);

	mode_cmd.pixel_क्रमmat = drm_mode_legacy_fb_क्रमmat(sizes->surface_bpp,
			sizes->surface_depth);

	mode_cmd.width = sizes->surface_width;
	mode_cmd.height = sizes->surface_height;

	mode_cmd.pitches[0] =
			DIV_ROUND_UP(mode_cmd.width * sizes->surface_bpp, 8);

	fbdev->ywrap_enabled = priv->has_dmm && ywrap_enabled;
	अगर (fbdev->ywrap_enabled) अणु
		/* need to align pitch to page size अगर using DMM scrolling */
		mode_cmd.pitches[0] = PAGE_ALIGN(mode_cmd.pitches[0]);
	पूर्ण

	/* allocate backing bo */
	gsize = (जोड़ omap_gem_size)अणु
		.bytes = PAGE_ALIGN(mode_cmd.pitches[0] * mode_cmd.height),
	पूर्ण;
	DBG("allocating %d bytes for fb %d", gsize.bytes, dev->primary->index);
	fbdev->bo = omap_gem_new(dev, gsize, OMAP_BO_SCANOUT | OMAP_BO_WC);
	अगर (!fbdev->bo) अणु
		dev_err(dev->dev, "failed to allocate buffer object\n");
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	fb = omap_framebuffer_init(dev, &mode_cmd, &fbdev->bo);
	अगर (IS_ERR(fb)) अणु
		dev_err(dev->dev, "failed to allocate fb\n");
		/* note: अगर fb creation failed, we can't rely on fb destroy
		 * to unref the bo:
		 */
		drm_gem_object_put(fbdev->bo);
		ret = PTR_ERR(fb);
		जाओ fail;
	पूर्ण

	/* note: this keeps the bo pinned.. which is perhaps not ideal,
	 * but is needed as दीर्घ as we use fb_mmap() to mmap to userspace
	 * (since this happens using fix.smem_start).  Possibly we could
	 * implement our own mmap using GEM mmap support to aव्योम this
	 * (non-tiled buffer करोesn't need to be pinned क्रम fbcon to ग_लिखो
	 * to it).  Then we just need to be sure that we are able to re-
	 * pin it in हाल of an opps.
	 */
	ret = omap_gem_pin(fbdev->bo, &dma_addr);
	अगर (ret) अणु
		dev_err(dev->dev, "could not pin framebuffer\n");
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	fbi = drm_fb_helper_alloc_fbi(helper);
	अगर (IS_ERR(fbi)) अणु
		dev_err(dev->dev, "failed to allocate fb info\n");
		ret = PTR_ERR(fbi);
		जाओ fail;
	पूर्ण

	DBG("fbi=%p, dev=%p", fbi, dev);

	fbdev->fb = fb;
	helper->fb = fb;

	fbi->fbops = &omap_fb_ops;

	drm_fb_helper_fill_info(fbi, helper, sizes);

	dev->mode_config.fb_base = dma_addr;

	fbi->screen_buffer = omap_gem_vaddr(fbdev->bo);
	fbi->screen_size = fbdev->bo->size;
	fbi->fix.smem_start = dma_addr;
	fbi->fix.smem_len = fbdev->bo->size;

	/* अगर we have DMM, then we can use it क्रम scrolling by just
	 * shuffling pages around in DMM rather than करोing sw blit.
	 */
	अगर (fbdev->ywrap_enabled) अणु
		DRM_INFO("Enabling DMM ywrap scrolling\n");
		fbi->flags |= FBINFO_HWACCEL_YWRAP | FBINFO_READS_FAST;
		fbi->fix.ywrapstep = 1;
	पूर्ण


	DBG("par=%p, %dx%d", fbi->par, fbi->var.xres, fbi->var.yres);
	DBG("allocated %dx%d fb", fbdev->fb->width, fbdev->fb->height);

	वापस 0;

fail:

	अगर (ret) अणु
		अगर (fb)
			drm_framebuffer_हटाओ(fb);
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा drm_fb_helper_funcs omap_fb_helper_funcs = अणु
	.fb_probe = omap_fbdev_create,
पूर्ण;

अटल काष्ठा drm_fb_helper *get_fb(काष्ठा fb_info *fbi)
अणु
	अगर (!fbi || म_भेद(fbi->fix.id, MODULE_NAME)) अणु
		/* these are not the fb's you're looking क्रम */
		वापस शून्य;
	पूर्ण
	वापस fbi->par;
पूर्ण

/* initialize fbdev helper */
व्योम omap_fbdev_init(काष्ठा drm_device *dev)
अणु
	काष्ठा omap_drm_निजी *priv = dev->dev_निजी;
	काष्ठा omap_fbdev *fbdev = शून्य;
	काष्ठा drm_fb_helper *helper;
	पूर्णांक ret = 0;

	अगर (!priv->num_pipes)
		वापस;

	fbdev = kzalloc(माप(*fbdev), GFP_KERNEL);
	अगर (!fbdev)
		जाओ fail;

	INIT_WORK(&fbdev->work, pan_worker);

	helper = &fbdev->base;

	drm_fb_helper_prepare(dev, helper, &omap_fb_helper_funcs);

	ret = drm_fb_helper_init(dev, helper);
	अगर (ret)
		जाओ fail;

	ret = drm_fb_helper_initial_config(helper, 32);
	अगर (ret)
		जाओ fini;

	priv->fbdev = helper;

	वापस;

fini:
	drm_fb_helper_fini(helper);
fail:
	kमुक्त(fbdev);

	dev_warn(dev->dev, "omap_fbdev_init failed\n");
पूर्ण

व्योम omap_fbdev_fini(काष्ठा drm_device *dev)
अणु
	काष्ठा omap_drm_निजी *priv = dev->dev_निजी;
	काष्ठा drm_fb_helper *helper = priv->fbdev;
	काष्ठा omap_fbdev *fbdev;

	DBG();

	अगर (!helper)
		वापस;

	drm_fb_helper_unरेजिस्टर_fbi(helper);

	drm_fb_helper_fini(helper);

	fbdev = to_omap_fbdev(helper);

	/* unpin the GEM object pinned in omap_fbdev_create() */
	अगर (fbdev->bo)
		omap_gem_unpin(fbdev->bo);

	/* this will मुक्त the backing object */
	अगर (fbdev->fb)
		drm_framebuffer_हटाओ(fbdev->fb);

	kमुक्त(fbdev);

	priv->fbdev = शून्य;
पूर्ण
