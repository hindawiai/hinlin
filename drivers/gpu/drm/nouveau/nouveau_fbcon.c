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

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/tty.h>
#समावेश <linux/sysrq.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/screen_info.h>
#समावेश <linux/vga_चयनeroo.h>
#समावेश <linux/console.h>

#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_crtc_helper.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_atomic.h>

#समावेश "nouveau_drv.h"
#समावेश "nouveau_gem.h"
#समावेश "nouveau_bo.h"
#समावेश "nouveau_fbcon.h"
#समावेश "nouveau_chan.h"
#समावेश "nouveau_vmm.h"

#समावेश "nouveau_crtc.h"

MODULE_PARM_DESC(nofbaccel, "Disable fbcon acceleration");
पूर्णांक nouveau_nofbaccel = 0;
module_param_named(nofbaccel, nouveau_nofbaccel, पूर्णांक, 0400);

MODULE_PARM_DESC(fbcon_bpp, "fbcon bits-per-pixel (default: auto)");
अटल पूर्णांक nouveau_fbcon_bpp;
module_param_named(fbcon_bpp, nouveau_fbcon_bpp, पूर्णांक, 0400);

अटल व्योम
nouveau_fbcon_fillrect(काष्ठा fb_info *info, स्थिर काष्ठा fb_fillrect *rect)
अणु
	काष्ठा nouveau_fbdev *fbcon = info->par;
	काष्ठा nouveau_drm *drm = nouveau_drm(fbcon->helper.dev);
	काष्ठा nvअगर_device *device = &drm->client.device;
	पूर्णांक ret;

	अगर (info->state != FBINFO_STATE_RUNNING)
		वापस;

	ret = -ENODEV;
	अगर (!in_पूर्णांकerrupt() && !(info->flags & FBINFO_HWACCEL_DISABLED) &&
	    mutex_trylock(&drm->client.mutex)) अणु
		अगर (device->info.family < NV_DEVICE_INFO_V0_TESLA)
			ret = nv04_fbcon_fillrect(info, rect);
		अन्यथा
		अगर (device->info.family < NV_DEVICE_INFO_V0_FERMI)
			ret = nv50_fbcon_fillrect(info, rect);
		अन्यथा
			ret = nvc0_fbcon_fillrect(info, rect);
		mutex_unlock(&drm->client.mutex);
	पूर्ण

	अगर (ret == 0)
		वापस;

	अगर (ret != -ENODEV)
		nouveau_fbcon_gpu_lockup(info);
	drm_fb_helper_cfb_fillrect(info, rect);
पूर्ण

अटल व्योम
nouveau_fbcon_copyarea(काष्ठा fb_info *info, स्थिर काष्ठा fb_copyarea *image)
अणु
	काष्ठा nouveau_fbdev *fbcon = info->par;
	काष्ठा nouveau_drm *drm = nouveau_drm(fbcon->helper.dev);
	काष्ठा nvअगर_device *device = &drm->client.device;
	पूर्णांक ret;

	अगर (info->state != FBINFO_STATE_RUNNING)
		वापस;

	ret = -ENODEV;
	अगर (!in_पूर्णांकerrupt() && !(info->flags & FBINFO_HWACCEL_DISABLED) &&
	    mutex_trylock(&drm->client.mutex)) अणु
		अगर (device->info.family < NV_DEVICE_INFO_V0_TESLA)
			ret = nv04_fbcon_copyarea(info, image);
		अन्यथा
		अगर (device->info.family < NV_DEVICE_INFO_V0_FERMI)
			ret = nv50_fbcon_copyarea(info, image);
		अन्यथा
			ret = nvc0_fbcon_copyarea(info, image);
		mutex_unlock(&drm->client.mutex);
	पूर्ण

	अगर (ret == 0)
		वापस;

	अगर (ret != -ENODEV)
		nouveau_fbcon_gpu_lockup(info);
	drm_fb_helper_cfb_copyarea(info, image);
पूर्ण

अटल व्योम
nouveau_fbcon_imageblit(काष्ठा fb_info *info, स्थिर काष्ठा fb_image *image)
अणु
	काष्ठा nouveau_fbdev *fbcon = info->par;
	काष्ठा nouveau_drm *drm = nouveau_drm(fbcon->helper.dev);
	काष्ठा nvअगर_device *device = &drm->client.device;
	पूर्णांक ret;

	अगर (info->state != FBINFO_STATE_RUNNING)
		वापस;

	ret = -ENODEV;
	अगर (!in_पूर्णांकerrupt() && !(info->flags & FBINFO_HWACCEL_DISABLED) &&
	    mutex_trylock(&drm->client.mutex)) अणु
		अगर (device->info.family < NV_DEVICE_INFO_V0_TESLA)
			ret = nv04_fbcon_imageblit(info, image);
		अन्यथा
		अगर (device->info.family < NV_DEVICE_INFO_V0_FERMI)
			ret = nv50_fbcon_imageblit(info, image);
		अन्यथा
			ret = nvc0_fbcon_imageblit(info, image);
		mutex_unlock(&drm->client.mutex);
	पूर्ण

	अगर (ret == 0)
		वापस;

	अगर (ret != -ENODEV)
		nouveau_fbcon_gpu_lockup(info);
	drm_fb_helper_cfb_imageblit(info, image);
पूर्ण

अटल पूर्णांक
nouveau_fbcon_sync(काष्ठा fb_info *info)
अणु
	काष्ठा nouveau_fbdev *fbcon = info->par;
	काष्ठा nouveau_drm *drm = nouveau_drm(fbcon->helper.dev);
	काष्ठा nouveau_channel *chan = drm->channel;
	पूर्णांक ret;

	अगर (!chan || !chan->accel_करोne || in_पूर्णांकerrupt() ||
	    info->state != FBINFO_STATE_RUNNING ||
	    info->flags & FBINFO_HWACCEL_DISABLED)
		वापस 0;

	अगर (!mutex_trylock(&drm->client.mutex))
		वापस 0;

	ret = nouveau_channel_idle(chan);
	mutex_unlock(&drm->client.mutex);
	अगर (ret) अणु
		nouveau_fbcon_gpu_lockup(info);
		वापस 0;
	पूर्ण

	chan->accel_करोne = false;
	वापस 0;
पूर्ण

अटल पूर्णांक
nouveau_fbcon_खोलो(काष्ठा fb_info *info, पूर्णांक user)
अणु
	काष्ठा nouveau_fbdev *fbcon = info->par;
	काष्ठा nouveau_drm *drm = nouveau_drm(fbcon->helper.dev);
	पूर्णांक ret = pm_runसमय_get_sync(drm->dev->dev);
	अगर (ret < 0 && ret != -EACCES) अणु
		pm_runसमय_put(drm->dev->dev);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
nouveau_fbcon_release(काष्ठा fb_info *info, पूर्णांक user)
अणु
	काष्ठा nouveau_fbdev *fbcon = info->par;
	काष्ठा nouveau_drm *drm = nouveau_drm(fbcon->helper.dev);
	pm_runसमय_put(drm->dev->dev);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fb_ops nouveau_fbcon_ops = अणु
	.owner = THIS_MODULE,
	DRM_FB_HELPER_DEFAULT_OPS,
	.fb_खोलो = nouveau_fbcon_खोलो,
	.fb_release = nouveau_fbcon_release,
	.fb_fillrect = nouveau_fbcon_fillrect,
	.fb_copyarea = nouveau_fbcon_copyarea,
	.fb_imageblit = nouveau_fbcon_imageblit,
	.fb_sync = nouveau_fbcon_sync,
पूर्ण;

अटल स्थिर काष्ठा fb_ops nouveau_fbcon_sw_ops = अणु
	.owner = THIS_MODULE,
	DRM_FB_HELPER_DEFAULT_OPS,
	.fb_खोलो = nouveau_fbcon_खोलो,
	.fb_release = nouveau_fbcon_release,
	.fb_fillrect = drm_fb_helper_cfb_fillrect,
	.fb_copyarea = drm_fb_helper_cfb_copyarea,
	.fb_imageblit = drm_fb_helper_cfb_imageblit,
पूर्ण;

व्योम
nouveau_fbcon_accel_save_disable(काष्ठा drm_device *dev)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	अगर (drm->fbcon && drm->fbcon->helper.fbdev) अणु
		drm->fbcon->saved_flags = drm->fbcon->helper.fbdev->flags;
		drm->fbcon->helper.fbdev->flags |= FBINFO_HWACCEL_DISABLED;
	पूर्ण
पूर्ण

व्योम
nouveau_fbcon_accel_restore(काष्ठा drm_device *dev)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	अगर (drm->fbcon && drm->fbcon->helper.fbdev) अणु
		drm->fbcon->helper.fbdev->flags = drm->fbcon->saved_flags;
	पूर्ण
पूर्ण

अटल व्योम
nouveau_fbcon_accel_fini(काष्ठा drm_device *dev)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nouveau_fbdev *fbcon = drm->fbcon;
	अगर (fbcon && drm->channel) अणु
		console_lock();
		अगर (fbcon->helper.fbdev)
			fbcon->helper.fbdev->flags |= FBINFO_HWACCEL_DISABLED;
		console_unlock();
		nouveau_channel_idle(drm->channel);
		nvअगर_object_dtor(&fbcon->twod);
		nvअगर_object_dtor(&fbcon->blit);
		nvअगर_object_dtor(&fbcon->gdi);
		nvअगर_object_dtor(&fbcon->patt);
		nvअगर_object_dtor(&fbcon->rop);
		nvअगर_object_dtor(&fbcon->clip);
		nvअगर_object_dtor(&fbcon->surf2d);
	पूर्ण
पूर्ण

अटल व्योम
nouveau_fbcon_accel_init(काष्ठा drm_device *dev)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nouveau_fbdev *fbcon = drm->fbcon;
	काष्ठा fb_info *info = fbcon->helper.fbdev;
	पूर्णांक ret;

	अगर (drm->client.device.info.family < NV_DEVICE_INFO_V0_TESLA)
		ret = nv04_fbcon_accel_init(info);
	अन्यथा
	अगर (drm->client.device.info.family < NV_DEVICE_INFO_V0_FERMI)
		ret = nv50_fbcon_accel_init(info);
	अन्यथा
		ret = nvc0_fbcon_accel_init(info);

	अगर (ret == 0)
		info->fbops = &nouveau_fbcon_ops;
पूर्ण

अटल व्योम
nouveau_fbcon_zfill(काष्ठा drm_device *dev, काष्ठा nouveau_fbdev *fbcon)
अणु
	काष्ठा fb_info *info = fbcon->helper.fbdev;
	काष्ठा fb_fillrect rect;

	/* Clear the entire fbcon.  The drm will program every connector
	 * with it's preferred mode.  If the sizes dअगरfer, one display will
	 * quite likely have garbage around the console.
	 */
	rect.dx = rect.dy = 0;
	rect.width = info->var.xres_भव;
	rect.height = info->var.yres_भव;
	rect.color = 0;
	rect.rop = ROP_COPY;
	info->fbops->fb_fillrect(info, &rect);
पूर्ण

अटल पूर्णांक
nouveau_fbcon_create(काष्ठा drm_fb_helper *helper,
		     काष्ठा drm_fb_helper_surface_size *sizes)
अणु
	काष्ठा nouveau_fbdev *fbcon =
		container_of(helper, काष्ठा nouveau_fbdev, helper);
	काष्ठा drm_device *dev = fbcon->helper.dev;
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nvअगर_device *device = &drm->client.device;
	काष्ठा fb_info *info;
	काष्ठा drm_framebuffer *fb;
	काष्ठा nouveau_channel *chan;
	काष्ठा nouveau_bo *nvbo;
	काष्ठा drm_mode_fb_cmd2 mode_cmd = अणुपूर्ण;
	पूर्णांक ret;

	mode_cmd.width = sizes->surface_width;
	mode_cmd.height = sizes->surface_height;

	mode_cmd.pitches[0] = mode_cmd.width * (sizes->surface_bpp >> 3);
	mode_cmd.pitches[0] = roundup(mode_cmd.pitches[0], 256);

	mode_cmd.pixel_क्रमmat = drm_mode_legacy_fb_क्रमmat(sizes->surface_bpp,
							  sizes->surface_depth);

	ret = nouveau_gem_new(&drm->client, mode_cmd.pitches[0] *
			      mode_cmd.height, 0, NOUVEAU_GEM_DOMAIN_VRAM,
			      0, 0x0000, &nvbo);
	अगर (ret) अणु
		NV_ERROR(drm, "failed to allocate framebuffer\n");
		जाओ out;
	पूर्ण

	ret = nouveau_framebuffer_new(dev, &mode_cmd, &nvbo->bo.base, &fb);
	अगर (ret)
		जाओ out_unref;

	ret = nouveau_bo_pin(nvbo, NOUVEAU_GEM_DOMAIN_VRAM, false);
	अगर (ret) अणु
		NV_ERROR(drm, "failed to pin fb: %d\n", ret);
		जाओ out_unref;
	पूर्ण

	ret = nouveau_bo_map(nvbo);
	अगर (ret) अणु
		NV_ERROR(drm, "failed to map fb: %d\n", ret);
		जाओ out_unpin;
	पूर्ण

	chan = nouveau_nofbaccel ? शून्य : drm->channel;
	अगर (chan && device->info.family >= NV_DEVICE_INFO_V0_TESLA) अणु
		ret = nouveau_vma_new(nvbo, chan->vmm, &fbcon->vma);
		अगर (ret) अणु
			NV_ERROR(drm, "failed to map fb into chan: %d\n", ret);
			chan = शून्य;
		पूर्ण
	पूर्ण

	info = drm_fb_helper_alloc_fbi(helper);
	अगर (IS_ERR(info)) अणु
		ret = PTR_ERR(info);
		जाओ out_unlock;
	पूर्ण

	/* setup helper */
	fbcon->helper.fb = fb;

	अगर (!chan)
		info->flags = FBINFO_HWACCEL_DISABLED;
	अन्यथा
		info->flags = FBINFO_HWACCEL_COPYAREA |
			      FBINFO_HWACCEL_FILLRECT |
			      FBINFO_HWACCEL_IMAGEBLIT;
	info->fbops = &nouveau_fbcon_sw_ops;
	info->fix.smem_start = nvbo->bo.mem.bus.offset;
	info->fix.smem_len = nvbo->bo.mem.num_pages << PAGE_SHIFT;

	info->screen_base = nvbo_kmap_obj_ioभव(nvbo);
	info->screen_size = nvbo->bo.mem.num_pages << PAGE_SHIFT;

	drm_fb_helper_fill_info(info, &fbcon->helper, sizes);

	/* Use शेष scratch pixmap (info->pixmap.flags = FB_PIXMAP_SYSTEM) */

	अगर (chan)
		nouveau_fbcon_accel_init(dev);
	nouveau_fbcon_zfill(dev, fbcon);

	/* To allow resizeing without swapping buffers */
	NV_INFO(drm, "allocated %dx%d fb: 0x%llx, bo %p\n",
		fb->width, fb->height, nvbo->offset, nvbo);

	अगर (dev_is_pci(dev->dev))
		vga_चयनeroo_client_fb_set(to_pci_dev(dev->dev), info);

	वापस 0;

out_unlock:
	अगर (chan)
		nouveau_vma_del(&fbcon->vma);
	nouveau_bo_unmap(nvbo);
out_unpin:
	nouveau_bo_unpin(nvbo);
out_unref:
	nouveau_bo_ref(शून्य, &nvbo);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक
nouveau_fbcon_destroy(काष्ठा drm_device *dev, काष्ठा nouveau_fbdev *fbcon)
अणु
	काष्ठा drm_framebuffer *fb = fbcon->helper.fb;
	काष्ठा nouveau_bo *nvbo;

	drm_fb_helper_unरेजिस्टर_fbi(&fbcon->helper);
	drm_fb_helper_fini(&fbcon->helper);

	अगर (fb && fb->obj[0]) अणु
		nvbo = nouveau_gem_object(fb->obj[0]);
		nouveau_vma_del(&fbcon->vma);
		nouveau_bo_unmap(nvbo);
		nouveau_bo_unpin(nvbo);
		drm_framebuffer_put(fb);
	पूर्ण

	वापस 0;
पूर्ण

व्योम nouveau_fbcon_gpu_lockup(काष्ठा fb_info *info)
अणु
	काष्ठा nouveau_fbdev *fbcon = info->par;
	काष्ठा nouveau_drm *drm = nouveau_drm(fbcon->helper.dev);

	NV_ERROR(drm, "GPU lockup - switching to software fbcon\n");
	info->flags |= FBINFO_HWACCEL_DISABLED;
पूर्ण

अटल स्थिर काष्ठा drm_fb_helper_funcs nouveau_fbcon_helper_funcs = अणु
	.fb_probe = nouveau_fbcon_create,
पूर्ण;

अटल व्योम
nouveau_fbcon_set_suspend_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nouveau_drm *drm = container_of(work, typeof(*drm), fbcon_work);
	पूर्णांक state = READ_ONCE(drm->fbcon_new_state);

	अगर (state == FBINFO_STATE_RUNNING)
		pm_runसमय_get_sync(drm->dev->dev);

	console_lock();
	अगर (state == FBINFO_STATE_RUNNING)
		nouveau_fbcon_accel_restore(drm->dev);
	drm_fb_helper_set_suspend(&drm->fbcon->helper, state);
	अगर (state != FBINFO_STATE_RUNNING)
		nouveau_fbcon_accel_save_disable(drm->dev);
	console_unlock();

	अगर (state == FBINFO_STATE_RUNNING) अणु
		nouveau_fbcon_hotplug_resume(drm->fbcon);
		pm_runसमय_mark_last_busy(drm->dev->dev);
		pm_runसमय_put_sync(drm->dev->dev);
	पूर्ण
पूर्ण

व्योम
nouveau_fbcon_set_suspend(काष्ठा drm_device *dev, पूर्णांक state)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);

	अगर (!drm->fbcon)
		वापस;

	drm->fbcon_new_state = state;
	/* Since runसमय resume can happen as a result of a sysfs operation,
	 * it's possible we alपढ़ोy have the console locked. So handle fbcon
	 * init/deinit from a seperate work thपढ़ो
	 */
	schedule_work(&drm->fbcon_work);
पूर्ण

व्योम
nouveau_fbcon_output_poll_changed(काष्ठा drm_device *dev)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nouveau_fbdev *fbcon = drm->fbcon;
	पूर्णांक ret;

	अगर (!fbcon)
		वापस;

	mutex_lock(&fbcon->hotplug_lock);

	ret = pm_runसमय_get(dev->dev);
	अगर (ret == 1 || ret == -EACCES) अणु
		drm_fb_helper_hotplug_event(&fbcon->helper);

		pm_runसमय_mark_last_busy(dev->dev);
		pm_runसमय_put_स्वतःsuspend(dev->dev);
	पूर्ण अन्यथा अगर (ret == 0) अणु
		/* If the GPU was alपढ़ोy in the process of suspending beक्रमe
		 * this event happened, then we can't block here as we'll
		 * deadlock the runसमय pmops since they रुको क्रम us to
		 * finish. So, just defer this event क्रम when we runसमय
		 * resume again. It will be handled by fbcon_work.
		 */
		NV_DEBUG(drm, "fbcon HPD event deferred until runtime resume\n");
		fbcon->hotplug_रुकोing = true;
		pm_runसमय_put_noidle(drm->dev->dev);
	पूर्ण अन्यथा अणु
		DRM_WARN("fbcon HPD event lost due to RPM failure: %d\n",
			 ret);
	पूर्ण

	mutex_unlock(&fbcon->hotplug_lock);
पूर्ण

व्योम
nouveau_fbcon_hotplug_resume(काष्ठा nouveau_fbdev *fbcon)
अणु
	काष्ठा nouveau_drm *drm;

	अगर (!fbcon)
		वापस;
	drm = nouveau_drm(fbcon->helper.dev);

	mutex_lock(&fbcon->hotplug_lock);
	अगर (fbcon->hotplug_रुकोing) अणु
		fbcon->hotplug_रुकोing = false;

		NV_DEBUG(drm, "Handling deferred fbcon HPD events\n");
		drm_fb_helper_hotplug_event(&fbcon->helper);
	पूर्ण
	mutex_unlock(&fbcon->hotplug_lock);
पूर्ण

पूर्णांक
nouveau_fbcon_init(काष्ठा drm_device *dev)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nouveau_fbdev *fbcon;
	पूर्णांक preferred_bpp = nouveau_fbcon_bpp;
	पूर्णांक ret;

	अगर (!dev->mode_config.num_crtc ||
	    (to_pci_dev(dev->dev)->class >> 8) != PCI_CLASS_DISPLAY_VGA)
		वापस 0;

	fbcon = kzalloc(माप(काष्ठा nouveau_fbdev), GFP_KERNEL);
	अगर (!fbcon)
		वापस -ENOMEM;

	drm->fbcon = fbcon;
	INIT_WORK(&drm->fbcon_work, nouveau_fbcon_set_suspend_work);
	mutex_init(&fbcon->hotplug_lock);

	drm_fb_helper_prepare(dev, &fbcon->helper, &nouveau_fbcon_helper_funcs);

	ret = drm_fb_helper_init(dev, &fbcon->helper);
	अगर (ret)
		जाओ मुक्त;

	अगर (preferred_bpp != 8 && preferred_bpp != 16 && preferred_bpp != 32) अणु
		अगर (drm->client.device.info.ram_size <= 32 * 1024 * 1024)
			preferred_bpp = 8;
		अन्यथा
		अगर (drm->client.device.info.ram_size <= 64 * 1024 * 1024)
			preferred_bpp = 16;
		अन्यथा
			preferred_bpp = 32;
	पूर्ण

	/* disable all the possible outमाला_दो/crtcs beक्रमe entering KMS mode */
	अगर (!drm_drv_uses_atomic_modeset(dev))
		drm_helper_disable_unused_functions(dev);

	ret = drm_fb_helper_initial_config(&fbcon->helper, preferred_bpp);
	अगर (ret)
		जाओ fini;

	अगर (fbcon->helper.fbdev)
		fbcon->helper.fbdev->pixmap.buf_align = 4;
	वापस 0;

fini:
	drm_fb_helper_fini(&fbcon->helper);
मुक्त:
	kमुक्त(fbcon);
	drm->fbcon = शून्य;
	वापस ret;
पूर्ण

व्योम
nouveau_fbcon_fini(काष्ठा drm_device *dev)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);

	अगर (!drm->fbcon)
		वापस;

	nouveau_fbcon_accel_fini(dev);
	nouveau_fbcon_destroy(dev, drm->fbcon);
	kमुक्त(drm->fbcon);
	drm->fbcon = शून्य;
पूर्ण
