<शैली गुरु>
/*
 * Copyright तऊ 2007 David Airlie
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * Authors:
 *     David Airlie
 */

#समावेश <linux/async.h>
#समावेश <linux/console.h>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/sysrq.h>
#समावेश <linux/tty.h>
#समावेश <linux/vga_चयनeroo.h>

#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_fourcc.h>

#समावेश "i915_drv.h"
#समावेश "intel_display_types.h"
#समावेश "intel_fbdev.h"
#समावेश "intel_frontbuffer.h"

अटल काष्ठा पूर्णांकel_frontbuffer *to_frontbuffer(काष्ठा पूर्णांकel_fbdev *अगरbdev)
अणु
	वापस अगरbdev->fb->frontbuffer;
पूर्ण

अटल व्योम पूर्णांकel_fbdev_invalidate(काष्ठा पूर्णांकel_fbdev *अगरbdev)
अणु
	पूर्णांकel_frontbuffer_invalidate(to_frontbuffer(अगरbdev), ORIGIN_CPU);
पूर्ण

अटल पूर्णांक पूर्णांकel_fbdev_set_par(काष्ठा fb_info *info)
अणु
	काष्ठा drm_fb_helper *fb_helper = info->par;
	काष्ठा पूर्णांकel_fbdev *अगरbdev =
		container_of(fb_helper, काष्ठा पूर्णांकel_fbdev, helper);
	पूर्णांक ret;

	ret = drm_fb_helper_set_par(info);
	अगर (ret == 0)
		पूर्णांकel_fbdev_invalidate(अगरbdev);

	वापस ret;
पूर्ण

अटल पूर्णांक पूर्णांकel_fbdev_blank(पूर्णांक blank, काष्ठा fb_info *info)
अणु
	काष्ठा drm_fb_helper *fb_helper = info->par;
	काष्ठा पूर्णांकel_fbdev *अगरbdev =
		container_of(fb_helper, काष्ठा पूर्णांकel_fbdev, helper);
	पूर्णांक ret;

	ret = drm_fb_helper_blank(blank, info);
	अगर (ret == 0)
		पूर्णांकel_fbdev_invalidate(अगरbdev);

	वापस ret;
पूर्ण

अटल पूर्णांक पूर्णांकel_fbdev_pan_display(काष्ठा fb_var_screeninfo *var,
				   काष्ठा fb_info *info)
अणु
	काष्ठा drm_fb_helper *fb_helper = info->par;
	काष्ठा पूर्णांकel_fbdev *अगरbdev =
		container_of(fb_helper, काष्ठा पूर्णांकel_fbdev, helper);
	पूर्णांक ret;

	ret = drm_fb_helper_pan_display(var, info);
	अगर (ret == 0)
		पूर्णांकel_fbdev_invalidate(अगरbdev);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा fb_ops पूर्णांकelfb_ops = अणु
	.owner = THIS_MODULE,
	DRM_FB_HELPER_DEFAULT_OPS,
	.fb_set_par = पूर्णांकel_fbdev_set_par,
	.fb_fillrect = drm_fb_helper_cfb_fillrect,
	.fb_copyarea = drm_fb_helper_cfb_copyarea,
	.fb_imageblit = drm_fb_helper_cfb_imageblit,
	.fb_pan_display = पूर्णांकel_fbdev_pan_display,
	.fb_blank = पूर्णांकel_fbdev_blank,
पूर्ण;

अटल पूर्णांक पूर्णांकelfb_alloc(काष्ठा drm_fb_helper *helper,
			 काष्ठा drm_fb_helper_surface_size *sizes)
अणु
	काष्ठा पूर्णांकel_fbdev *अगरbdev =
		container_of(helper, काष्ठा पूर्णांकel_fbdev, helper);
	काष्ठा drm_framebuffer *fb;
	काष्ठा drm_device *dev = helper->dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	काष्ठा drm_mode_fb_cmd2 mode_cmd = अणुपूर्ण;
	काष्ठा drm_i915_gem_object *obj;
	पूर्णांक size;

	/* we करोn't करो packed 24bpp */
	अगर (sizes->surface_bpp == 24)
		sizes->surface_bpp = 32;

	mode_cmd.width = sizes->surface_width;
	mode_cmd.height = sizes->surface_height;

	mode_cmd.pitches[0] = ALIGN(mode_cmd.width *
				    DIV_ROUND_UP(sizes->surface_bpp, 8), 64);
	mode_cmd.pixel_क्रमmat = drm_mode_legacy_fb_क्रमmat(sizes->surface_bpp,
							  sizes->surface_depth);

	size = mode_cmd.pitches[0] * mode_cmd.height;
	size = PAGE_ALIGN(size);

	/* If the FB is too big, just करोn't use it since fbdev is not very
	 * important and we should probably use that space with FBC or other
	 * features. */
	obj = ERR_PTR(-ENODEV);
	अगर (size * 2 < dev_priv->stolen_usable_size)
		obj = i915_gem_object_create_stolen(dev_priv, size);
	अगर (IS_ERR(obj))
		obj = i915_gem_object_create_shmem(dev_priv, size);
	अगर (IS_ERR(obj)) अणु
		drm_err(&dev_priv->drm, "failed to allocate framebuffer\n");
		वापस PTR_ERR(obj);
	पूर्ण

	fb = पूर्णांकel_framebuffer_create(obj, &mode_cmd);
	i915_gem_object_put(obj);
	अगर (IS_ERR(fb))
		वापस PTR_ERR(fb);

	अगरbdev->fb = to_पूर्णांकel_framebuffer(fb);
	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकelfb_create(काष्ठा drm_fb_helper *helper,
			  काष्ठा drm_fb_helper_surface_size *sizes)
अणु
	काष्ठा पूर्णांकel_fbdev *अगरbdev =
		container_of(helper, काष्ठा पूर्णांकel_fbdev, helper);
	काष्ठा पूर्णांकel_framebuffer *पूर्णांकel_fb = अगरbdev->fb;
	काष्ठा drm_device *dev = helper->dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	काष्ठा pci_dev *pdev = to_pci_dev(dev_priv->drm.dev);
	काष्ठा i915_ggtt *ggtt = &dev_priv->ggtt;
	स्थिर काष्ठा i915_ggtt_view view = अणु
		.type = I915_GGTT_VIEW_NORMAL,
	पूर्ण;
	पूर्णांकel_wakeref_t wakeref;
	काष्ठा fb_info *info;
	काष्ठा i915_vma *vma;
	अचिन्हित दीर्घ flags = 0;
	bool pपुनः_स्मृति = false;
	व्योम __iomem *vaddr;
	पूर्णांक ret;

	अगर (पूर्णांकel_fb &&
	    (sizes->fb_width > पूर्णांकel_fb->base.width ||
	     sizes->fb_height > पूर्णांकel_fb->base.height)) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "BIOS fb too small (%dx%d), we require (%dx%d),"
			    " releasing it\n",
			    पूर्णांकel_fb->base.width, पूर्णांकel_fb->base.height,
			    sizes->fb_width, sizes->fb_height);
		drm_framebuffer_put(&पूर्णांकel_fb->base);
		पूर्णांकel_fb = अगरbdev->fb = शून्य;
	पूर्ण
	अगर (!पूर्णांकel_fb || drm_WARN_ON(dev, !पूर्णांकel_fb_obj(&पूर्णांकel_fb->base))) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "no BIOS fb, allocating a new one\n");
		ret = पूर्णांकelfb_alloc(helper, sizes);
		अगर (ret)
			वापस ret;
		पूर्णांकel_fb = अगरbdev->fb;
	पूर्ण अन्यथा अणु
		drm_dbg_kms(&dev_priv->drm, "re-using BIOS fb\n");
		pपुनः_स्मृति = true;
		sizes->fb_width = पूर्णांकel_fb->base.width;
		sizes->fb_height = पूर्णांकel_fb->base.height;
	पूर्ण

	wakeref = पूर्णांकel_runसमय_pm_get(&dev_priv->runसमय_pm);

	/* Pin the GGTT vma क्रम our access via info->screen_base.
	 * This also validates that any existing fb inherited from the
	 * BIOS is suitable क्रम own access.
	 */
	vma = पूर्णांकel_pin_and_fence_fb_obj(&अगरbdev->fb->base, false,
					 &view, false, &flags);
	अगर (IS_ERR(vma)) अणु
		ret = PTR_ERR(vma);
		जाओ out_unlock;
	पूर्ण

	पूर्णांकel_frontbuffer_flush(to_frontbuffer(अगरbdev), ORIGIN_सूचीTYFB);

	info = drm_fb_helper_alloc_fbi(helper);
	अगर (IS_ERR(info)) अणु
		drm_err(&dev_priv->drm, "Failed to allocate fb_info\n");
		ret = PTR_ERR(info);
		जाओ out_unpin;
	पूर्ण

	अगरbdev->helper.fb = &अगरbdev->fb->base;

	info->fbops = &पूर्णांकelfb_ops;

	/* setup aperture base/size क्रम vesafb takeover */
	info->apertures->ranges[0].base = ggtt->gmadr.start;
	info->apertures->ranges[0].size = ggtt->mappable_end;

	/* Our framebuffer is the entirety of fbdev's प्रणाली memory */
	info->fix.smem_start =
		(अचिन्हित दीर्घ)(ggtt->gmadr.start + vma->node.start);
	info->fix.smem_len = vma->node.size;

	vaddr = i915_vma_pin_iomap(vma);
	अगर (IS_ERR(vaddr)) अणु
		drm_err(&dev_priv->drm,
			"Failed to remap framebuffer into virtual memory\n");
		ret = PTR_ERR(vaddr);
		जाओ out_unpin;
	पूर्ण
	info->screen_base = vaddr;
	info->screen_size = vma->node.size;

	drm_fb_helper_fill_info(info, &अगरbdev->helper, sizes);

	/* If the object is shmemfs backed, it will have given us zeroed pages.
	 * If the object is stolen however, it will be full of whatever
	 * garbage was left in there.
	 */
	अगर (!i915_gem_object_is_shmem(vma->obj) && !pपुनः_स्मृति)
		स_रखो_io(info->screen_base, 0, info->screen_size);

	/* Use शेष scratch pixmap (info->pixmap.flags = FB_PIXMAP_SYSTEM) */

	drm_dbg_kms(&dev_priv->drm, "allocated %dx%d fb: 0x%08x\n",
		    अगरbdev->fb->base.width, अगरbdev->fb->base.height,
		    i915_ggtt_offset(vma));
	अगरbdev->vma = vma;
	अगरbdev->vma_flags = flags;

	पूर्णांकel_runसमय_pm_put(&dev_priv->runसमय_pm, wakeref);
	vga_चयनeroo_client_fb_set(pdev, info);
	वापस 0;

out_unpin:
	पूर्णांकel_unpin_fb_vma(vma, flags);
out_unlock:
	पूर्णांकel_runसमय_pm_put(&dev_priv->runसमय_pm, wakeref);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा drm_fb_helper_funcs पूर्णांकel_fb_helper_funcs = अणु
	.fb_probe = पूर्णांकelfb_create,
पूर्ण;

अटल व्योम पूर्णांकel_fbdev_destroy(काष्ठा पूर्णांकel_fbdev *अगरbdev)
अणु
	/* We rely on the object-मुक्त to release the VMA pinning क्रम
	 * the info->screen_base mmaping. Leaking the VMA is simpler than
	 * trying to rectअगरy all the possible error paths leading here.
	 */

	drm_fb_helper_fini(&अगरbdev->helper);

	अगर (अगरbdev->vma)
		पूर्णांकel_unpin_fb_vma(अगरbdev->vma, अगरbdev->vma_flags);

	अगर (अगरbdev->fb)
		drm_framebuffer_हटाओ(&अगरbdev->fb->base);

	kमुक्त(अगरbdev);
पूर्ण

/*
 * Build an पूर्णांकel_fbdev काष्ठा using a BIOS allocated framebuffer, अगर possible.
 * The core display code will have पढ़ो out the current plane configuration,
 * so we use that to figure out अगर there's an object क्रम us to use as the
 * fb, and अगर so, we re-use it क्रम the fbdev configuration.
 *
 * Note we only support a single fb shared across pipes क्रम boot (mostly क्रम
 * fbcon), so we just find the biggest and use that.
 */
अटल bool पूर्णांकel_fbdev_init_bios(काष्ठा drm_device *dev,
				 काष्ठा पूर्णांकel_fbdev *अगरbdev)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(dev);
	काष्ठा पूर्णांकel_framebuffer *fb = शून्य;
	काष्ठा drm_crtc *crtc;
	काष्ठा पूर्णांकel_crtc *पूर्णांकel_crtc;
	अचिन्हित पूर्णांक max_size = 0;

	/* Find the largest fb */
	क्रम_each_crtc(dev, crtc) अणु
		काष्ठा drm_i915_gem_object *obj =
			पूर्णांकel_fb_obj(crtc->primary->state->fb);
		पूर्णांकel_crtc = to_पूर्णांकel_crtc(crtc);

		अगर (!crtc->state->active || !obj) अणु
			drm_dbg_kms(&i915->drm,
				    "pipe %c not active or no fb, skipping\n",
				    pipe_name(पूर्णांकel_crtc->pipe));
			जारी;
		पूर्ण

		अगर (obj->base.size > max_size) अणु
			drm_dbg_kms(&i915->drm,
				    "found possible fb from plane %c\n",
				    pipe_name(पूर्णांकel_crtc->pipe));
			fb = to_पूर्णांकel_framebuffer(crtc->primary->state->fb);
			max_size = obj->base.size;
		पूर्ण
	पूर्ण

	अगर (!fb) अणु
		drm_dbg_kms(&i915->drm,
			    "no active fbs found, not using BIOS config\n");
		जाओ out;
	पूर्ण

	/* Now make sure all the pipes will fit पूर्णांकo it */
	क्रम_each_crtc(dev, crtc) अणु
		अचिन्हित पूर्णांक cur_size;

		पूर्णांकel_crtc = to_पूर्णांकel_crtc(crtc);

		अगर (!crtc->state->active) अणु
			drm_dbg_kms(&i915->drm,
				    "pipe %c not active, skipping\n",
				    pipe_name(पूर्णांकel_crtc->pipe));
			जारी;
		पूर्ण

		drm_dbg_kms(&i915->drm, "checking plane %c for BIOS fb\n",
			    pipe_name(पूर्णांकel_crtc->pipe));

		/*
		 * See अगर the plane fb we found above will fit on this
		 * pipe.  Note we need to use the selected fb's pitch and bpp
		 * rather than the current pipe's, since they dअगरfer.
		 */
		cur_size = crtc->state->adjusted_mode.crtc_hdisplay;
		cur_size = cur_size * fb->base.क्रमmat->cpp[0];
		अगर (fb->base.pitches[0] < cur_size) अणु
			drm_dbg_kms(&i915->drm,
				    "fb not wide enough for plane %c (%d vs %d)\n",
				    pipe_name(पूर्णांकel_crtc->pipe),
				    cur_size, fb->base.pitches[0]);
			fb = शून्य;
			अवरोध;
		पूर्ण

		cur_size = crtc->state->adjusted_mode.crtc_vdisplay;
		cur_size = पूर्णांकel_fb_align_height(&fb->base, 0, cur_size);
		cur_size *= fb->base.pitches[0];
		drm_dbg_kms(&i915->drm,
			    "pipe %c area: %dx%d, bpp: %d, size: %d\n",
			    pipe_name(पूर्णांकel_crtc->pipe),
			    crtc->state->adjusted_mode.crtc_hdisplay,
			    crtc->state->adjusted_mode.crtc_vdisplay,
			    fb->base.क्रमmat->cpp[0] * 8,
			    cur_size);

		अगर (cur_size > max_size) अणु
			drm_dbg_kms(&i915->drm,
				    "fb not big enough for plane %c (%d vs %d)\n",
				    pipe_name(पूर्णांकel_crtc->pipe),
				    cur_size, max_size);
			fb = शून्य;
			अवरोध;
		पूर्ण

		drm_dbg_kms(&i915->drm,
			    "fb big enough for plane %c (%d >= %d)\n",
			    pipe_name(पूर्णांकel_crtc->pipe),
			    max_size, cur_size);
	पूर्ण

	अगर (!fb) अणु
		drm_dbg_kms(&i915->drm,
			    "BIOS fb not suitable for all pipes, not using\n");
		जाओ out;
	पूर्ण

	अगरbdev->preferred_bpp = fb->base.क्रमmat->cpp[0] * 8;
	अगरbdev->fb = fb;

	drm_framebuffer_get(&अगरbdev->fb->base);

	/* Final pass to check अगर any active pipes करोn't have fbs */
	क्रम_each_crtc(dev, crtc) अणु
		पूर्णांकel_crtc = to_पूर्णांकel_crtc(crtc);

		अगर (!crtc->state->active)
			जारी;

		drm_WARN(dev, !crtc->primary->state->fb,
			 "re-used BIOS config but lost an fb on crtc %d\n",
			 crtc->base.id);
	पूर्ण


	drm_dbg_kms(&i915->drm, "using BIOS fb for initial console\n");
	वापस true;

out:

	वापस false;
पूर्ण

अटल व्योम पूर्णांकel_fbdev_suspend_worker(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांकel_fbdev_set_suspend(&container_of(work,
					      काष्ठा drm_i915_निजी,
					      fbdev_suspend_work)->drm,
				FBINFO_STATE_RUNNING,
				true);
पूर्ण

पूर्णांक पूर्णांकel_fbdev_init(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	काष्ठा पूर्णांकel_fbdev *अगरbdev;
	पूर्णांक ret;

	अगर (drm_WARN_ON(dev, !HAS_DISPLAY(dev_priv)))
		वापस -ENODEV;

	अगरbdev = kzalloc(माप(काष्ठा पूर्णांकel_fbdev), GFP_KERNEL);
	अगर (अगरbdev == शून्य)
		वापस -ENOMEM;

	mutex_init(&अगरbdev->hpd_lock);
	drm_fb_helper_prepare(dev, &अगरbdev->helper, &पूर्णांकel_fb_helper_funcs);

	अगर (!पूर्णांकel_fbdev_init_bios(dev, अगरbdev))
		अगरbdev->preferred_bpp = 32;

	ret = drm_fb_helper_init(dev, &अगरbdev->helper);
	अगर (ret) अणु
		kमुक्त(अगरbdev);
		वापस ret;
	पूर्ण

	dev_priv->fbdev = अगरbdev;
	INIT_WORK(&dev_priv->fbdev_suspend_work, पूर्णांकel_fbdev_suspend_worker);

	वापस 0;
पूर्ण

अटल व्योम पूर्णांकel_fbdev_initial_config(व्योम *data, async_cookie_t cookie)
अणु
	काष्ठा पूर्णांकel_fbdev *अगरbdev = data;

	/* Due to peculiar init order wrt to hpd handling this is separate. */
	अगर (drm_fb_helper_initial_config(&अगरbdev->helper,
					 अगरbdev->preferred_bpp))
		पूर्णांकel_fbdev_unरेजिस्टर(to_i915(अगरbdev->helper.dev));
पूर्ण

व्योम पूर्णांकel_fbdev_initial_config_async(काष्ठा drm_device *dev)
अणु
	काष्ठा पूर्णांकel_fbdev *अगरbdev = to_i915(dev)->fbdev;

	अगर (!अगरbdev)
		वापस;

	अगरbdev->cookie = async_schedule(पूर्णांकel_fbdev_initial_config, अगरbdev);
पूर्ण

अटल व्योम पूर्णांकel_fbdev_sync(काष्ठा पूर्णांकel_fbdev *अगरbdev)
अणु
	अगर (!अगरbdev->cookie)
		वापस;

	/* Only serialises with all preceding async calls, hence +1 */
	async_synchronize_cookie(अगरbdev->cookie + 1);
	अगरbdev->cookie = 0;
पूर्ण

व्योम पूर्णांकel_fbdev_unरेजिस्टर(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_fbdev *अगरbdev = dev_priv->fbdev;

	अगर (!अगरbdev)
		वापस;

	cancel_work_sync(&dev_priv->fbdev_suspend_work);
	अगर (!current_is_async())
		पूर्णांकel_fbdev_sync(अगरbdev);

	drm_fb_helper_unरेजिस्टर_fbi(&अगरbdev->helper);
पूर्ण

व्योम पूर्णांकel_fbdev_fini(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_fbdev *अगरbdev = fetch_and_zero(&dev_priv->fbdev);

	अगर (!अगरbdev)
		वापस;

	पूर्णांकel_fbdev_destroy(अगरbdev);
पूर्ण

/* Suspends/resumes fbdev processing of incoming HPD events. When resuming HPD
 * processing, fbdev will perक्रमm a full connector reprobe अगर a hotplug event
 * was received जबतक HPD was suspended.
 */
अटल व्योम पूर्णांकel_fbdev_hpd_set_suspend(काष्ठा drm_i915_निजी *i915, पूर्णांक state)
अणु
	काष्ठा पूर्णांकel_fbdev *अगरbdev = i915->fbdev;
	bool send_hpd = false;

	mutex_lock(&अगरbdev->hpd_lock);
	अगरbdev->hpd_suspended = state == FBINFO_STATE_SUSPENDED;
	send_hpd = !अगरbdev->hpd_suspended && अगरbdev->hpd_रुकोing;
	अगरbdev->hpd_रुकोing = false;
	mutex_unlock(&अगरbdev->hpd_lock);

	अगर (send_hpd) अणु
		drm_dbg_kms(&i915->drm, "Handling delayed fbcon HPD event\n");
		drm_fb_helper_hotplug_event(&अगरbdev->helper);
	पूर्ण
पूर्ण

व्योम पूर्णांकel_fbdev_set_suspend(काष्ठा drm_device *dev, पूर्णांक state, bool synchronous)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	काष्ठा पूर्णांकel_fbdev *अगरbdev = dev_priv->fbdev;
	काष्ठा fb_info *info;

	अगर (!अगरbdev || !अगरbdev->vma)
		वापस;

	info = अगरbdev->helper.fbdev;

	अगर (synchronous) अणु
		/* Flush any pending work to turn the console on, and then
		 * रुको to turn it off. It must be synchronous as we are
		 * about to suspend or unload the driver.
		 *
		 * Note that from within the work-handler, we cannot flush
		 * ourselves, so only flush outstanding work upon suspend!
		 */
		अगर (state != FBINFO_STATE_RUNNING)
			flush_work(&dev_priv->fbdev_suspend_work);

		console_lock();
	पूर्ण अन्यथा अणु
		/*
		 * The console lock can be pretty contented on resume due
		 * to all the prपूर्णांकk activity.  Try to keep it out of the hot
		 * path of resume अगर possible.
		 */
		drm_WARN_ON(dev, state != FBINFO_STATE_RUNNING);
		अगर (!console_trylock()) अणु
			/* Don't block our own workqueue as this can
			 * be run in parallel with other i915.ko tasks.
			 */
			schedule_work(&dev_priv->fbdev_suspend_work);
			वापस;
		पूर्ण
	पूर्ण

	/* On resume from hibernation: If the object is shmemfs backed, it has
	 * been restored from swap. If the object is stolen however, it will be
	 * full of whatever garbage was left in there.
	 */
	अगर (state == FBINFO_STATE_RUNNING &&
	    !i915_gem_object_is_shmem(पूर्णांकel_fb_obj(&अगरbdev->fb->base)))
		स_रखो_io(info->screen_base, 0, info->screen_size);

	drm_fb_helper_set_suspend(&अगरbdev->helper, state);
	console_unlock();

	पूर्णांकel_fbdev_hpd_set_suspend(dev_priv, state);
पूर्ण

व्योम पूर्णांकel_fbdev_output_poll_changed(काष्ठा drm_device *dev)
अणु
	काष्ठा पूर्णांकel_fbdev *अगरbdev = to_i915(dev)->fbdev;
	bool send_hpd;

	अगर (!अगरbdev)
		वापस;

	पूर्णांकel_fbdev_sync(अगरbdev);

	mutex_lock(&अगरbdev->hpd_lock);
	send_hpd = !अगरbdev->hpd_suspended;
	अगरbdev->hpd_रुकोing = true;
	mutex_unlock(&अगरbdev->hpd_lock);

	अगर (send_hpd && (अगरbdev->vma || अगरbdev->helper.deferred_setup))
		drm_fb_helper_hotplug_event(&अगरbdev->helper);
पूर्ण

व्योम पूर्णांकel_fbdev_restore_mode(काष्ठा drm_device *dev)
अणु
	काष्ठा पूर्णांकel_fbdev *अगरbdev = to_i915(dev)->fbdev;

	अगर (!अगरbdev)
		वापस;

	पूर्णांकel_fbdev_sync(अगरbdev);
	अगर (!अगरbdev->vma)
		वापस;

	अगर (drm_fb_helper_restore_fbdev_mode_unlocked(&अगरbdev->helper) == 0)
		पूर्णांकel_fbdev_invalidate(अगरbdev);
पूर्ण
