<शैली गुरु>
/*
 * Copyright (c) 2006-2009 Red Hat Inc.
 * Copyright (c) 2006-2008 Intel Corporation
 * Copyright (c) 2007 Dave Airlie <airlied@linux.ie>
 *
 * DRM framebuffer helper functions
 *
 * Permission to use, copy, modअगरy, distribute, and sell this software and its
 * करोcumentation क्रम any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that copyright
 * notice and this permission notice appear in supporting करोcumentation, and
 * that the name of the copyright holders not be used in advertising or
 * खुलाity pertaining to distribution of the software without specअगरic,
 * written prior permission.  The copyright holders make no representations
 * about the suitability of this software क्रम any purpose.  It is provided "as
 * is" without express or implied warranty.
 *
 * THE COPYRIGHT HOLDERS DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
 * EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY SPECIAL, INसूचीECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THIS SOFTWARE.
 *
 * Authors:
 *      Dave Airlie <airlied@linux.ie>
 *      Jesse Barnes <jesse.barnes@पूर्णांकel.com>
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/console.h>
#समावेश <linux/dma-buf.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysrq.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_crtc_helper.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_vblank.h>

#समावेश "drm_crtc_helper_internal.h"
#समावेश "drm_internal.h"

अटल bool drm_fbdev_emulation = true;
module_param_named(fbdev_emulation, drm_fbdev_emulation, bool, 0600);
MODULE_PARM_DESC(fbdev_emulation,
		 "Enable legacy fbdev emulation [default=true]");

अटल पूर्णांक drm_fbdev_overalloc = CONFIG_DRM_FBDEV_OVERALLOC;
module_param(drm_fbdev_overalloc, पूर्णांक, 0444);
MODULE_PARM_DESC(drm_fbdev_overalloc,
		 "Overallocation of the fbdev buffer (%) [default="
		 __MODULE_STRING(CONFIG_DRM_FBDEV_OVERALLOC) "]");

/*
 * In order to keep user-space compatibility, we want in certain use-हालs
 * to keep leaking the fbdev physical address to the user-space program
 * handling the fbdev buffer.
 * This is a bad habit essentially kept पूर्णांकo बंदd source खोलोgl driver
 * that should really be moved पूर्णांकo खोलो-source upstream projects instead
 * of using legacy physical addresses in user space to communicate with
 * other out-of-tree kernel modules.
 *
 * This module_param *should* be हटाओd as soon as possible and be
 * considered as a broken and legacy behaviour from a modern fbdev device.
 */
#अगर IS_ENABLED(CONFIG_DRM_FBDEV_LEAK_PHYS_SMEM)
अटल bool drm_leak_fbdev_smem = false;
module_param_unsafe(drm_leak_fbdev_smem, bool, 0600);
MODULE_PARM_DESC(drm_leak_fbdev_smem,
		 "Allow unsafe leaking fbdev physical smem address [default=false]");
#पूर्ण_अगर

अटल LIST_HEAD(kernel_fb_helper_list);
अटल DEFINE_MUTEX(kernel_fb_helper_lock);

/**
 * DOC: fbdev helpers
 *
 * The fb helper functions are useful to provide an fbdev on top of a drm kernel
 * mode setting driver. They can be used mostly independently from the crtc
 * helper functions used by many drivers to implement the kernel mode setting
 * पूर्णांकerfaces.
 *
 * Drivers that support a dumb buffer with a भव address and mmap support,
 * should try out the generic fbdev emulation using drm_fbdev_generic_setup().
 * It will स्वतःmatically set up deferred I/O अगर the driver requires a shaकरोw
 * buffer.
 *
 * At runसमय drivers should restore the fbdev console by using
 * drm_fb_helper_lastबंद() as their &drm_driver.lastबंद callback.
 * They should also notअगरy the fb helper code from updates to the output
 * configuration by using drm_fb_helper_output_poll_changed() as their
 * &drm_mode_config_funcs.output_poll_changed callback.
 *
 * For suspend/resume consider using drm_mode_config_helper_suspend() and
 * drm_mode_config_helper_resume() which takes care of fbdev as well.
 *
 * All other functions exported by the fb helper library can be used to
 * implement the fbdev driver पूर्णांकerface by the driver.
 *
 * It is possible, though perhaps somewhat tricky, to implement race-मुक्त
 * hotplug detection using the fbdev helpers. The drm_fb_helper_prepare()
 * helper must be called first to initialize the minimum required to make
 * hotplug detection work. Drivers also need to make sure to properly set up
 * the &drm_mode_config.funcs member. After calling drm_kms_helper_poll_init()
 * it is safe to enable पूर्णांकerrupts and start processing hotplug events. At the
 * same समय, drivers should initialize all modeset objects such as CRTCs,
 * encoders and connectors. To finish up the fbdev helper initialization, the
 * drm_fb_helper_init() function is called. To probe क्रम all attached displays
 * and set up an initial configuration using the detected hardware, drivers
 * should call drm_fb_helper_initial_config().
 *
 * If &drm_framebuffer_funcs.dirty is set, the
 * drm_fb_helper_अणुcfb,sysपूर्ण_अणुग_लिखो,fillrect,copyarea,imageblitपूर्ण functions will
 * accumulate changes and schedule &drm_fb_helper.dirty_work to run right
 * away. This worker then calls the dirty() function ensuring that it will
 * always run in process context since the fb_*() function could be running in
 * atomic context. If drm_fb_helper_deferred_io() is used as the deferred_io
 * callback it will also schedule dirty_work with the damage collected from the
 * mmap page ग_लिखोs.
 *
 * Deferred I/O is not compatible with SHMEM. Such drivers should request an
 * fbdev shaकरोw buffer and call drm_fbdev_generic_setup() instead.
 */

अटल व्योम drm_fb_helper_restore_lut_atomic(काष्ठा drm_crtc *crtc)
अणु
	uपूर्णांक16_t *r_base, *g_base, *b_base;

	अगर (crtc->funcs->gamma_set == शून्य)
		वापस;

	r_base = crtc->gamma_store;
	g_base = r_base + crtc->gamma_size;
	b_base = g_base + crtc->gamma_size;

	crtc->funcs->gamma_set(crtc, r_base, g_base, b_base,
			       crtc->gamma_size, शून्य);
पूर्ण

/**
 * drm_fb_helper_debug_enter - implementation क्रम &fb_ops.fb_debug_enter
 * @info: fbdev रेजिस्टरed by the helper
 */
पूर्णांक drm_fb_helper_debug_enter(काष्ठा fb_info *info)
अणु
	काष्ठा drm_fb_helper *helper = info->par;
	स्थिर काष्ठा drm_crtc_helper_funcs *funcs;
	काष्ठा drm_mode_set *mode_set;

	list_क्रम_each_entry(helper, &kernel_fb_helper_list, kernel_fb_list) अणु
		mutex_lock(&helper->client.modeset_mutex);
		drm_client_क्रम_each_modeset(mode_set, &helper->client) अणु
			अगर (!mode_set->crtc->enabled)
				जारी;

			funcs =	mode_set->crtc->helper_निजी;
			अगर (funcs->mode_set_base_atomic == शून्य)
				जारी;

			अगर (drm_drv_uses_atomic_modeset(mode_set->crtc->dev))
				जारी;

			funcs->mode_set_base_atomic(mode_set->crtc,
						    mode_set->fb,
						    mode_set->x,
						    mode_set->y,
						    ENTER_ATOMIC_MODE_SET);
		पूर्ण
		mutex_unlock(&helper->client.modeset_mutex);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_fb_helper_debug_enter);

/**
 * drm_fb_helper_debug_leave - implementation क्रम &fb_ops.fb_debug_leave
 * @info: fbdev रेजिस्टरed by the helper
 */
पूर्णांक drm_fb_helper_debug_leave(काष्ठा fb_info *info)
अणु
	काष्ठा drm_fb_helper *helper = info->par;
	काष्ठा drm_client_dev *client = &helper->client;
	काष्ठा drm_device *dev = helper->dev;
	काष्ठा drm_crtc *crtc;
	स्थिर काष्ठा drm_crtc_helper_funcs *funcs;
	काष्ठा drm_mode_set *mode_set;
	काष्ठा drm_framebuffer *fb;

	mutex_lock(&client->modeset_mutex);
	drm_client_क्रम_each_modeset(mode_set, client) अणु
		crtc = mode_set->crtc;
		अगर (drm_drv_uses_atomic_modeset(crtc->dev))
			जारी;

		funcs = crtc->helper_निजी;
		fb = crtc->primary->fb;

		अगर (!crtc->enabled)
			जारी;

		अगर (!fb) अणु
			drm_err(dev, "no fb to restore?\n");
			जारी;
		पूर्ण

		अगर (funcs->mode_set_base_atomic == शून्य)
			जारी;

		drm_fb_helper_restore_lut_atomic(mode_set->crtc);
		funcs->mode_set_base_atomic(mode_set->crtc, fb, crtc->x,
					    crtc->y, LEAVE_ATOMIC_MODE_SET);
	पूर्ण
	mutex_unlock(&client->modeset_mutex);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_fb_helper_debug_leave);

अटल पूर्णांक
__drm_fb_helper_restore_fbdev_mode_unlocked(काष्ठा drm_fb_helper *fb_helper,
					    bool क्रमce)
अणु
	bool करो_delayed;
	पूर्णांक ret;

	अगर (!drm_fbdev_emulation || !fb_helper)
		वापस -ENODEV;

	अगर (READ_ONCE(fb_helper->deferred_setup))
		वापस 0;

	mutex_lock(&fb_helper->lock);
	अगर (क्रमce) अणु
		/*
		 * Yes this is the _locked version which expects the master lock
		 * to be held. But क्रम क्रमced restores we're पूर्णांकentionally
		 * racing here, see drm_fb_helper_set_par().
		 */
		ret = drm_client_modeset_commit_locked(&fb_helper->client);
	पूर्ण अन्यथा अणु
		ret = drm_client_modeset_commit(&fb_helper->client);
	पूर्ण

	करो_delayed = fb_helper->delayed_hotplug;
	अगर (करो_delayed)
		fb_helper->delayed_hotplug = false;
	mutex_unlock(&fb_helper->lock);

	अगर (करो_delayed)
		drm_fb_helper_hotplug_event(fb_helper);

	वापस ret;
पूर्ण

/**
 * drm_fb_helper_restore_fbdev_mode_unlocked - restore fbdev configuration
 * @fb_helper: driver-allocated fbdev helper, can be शून्य
 *
 * This should be called from driver's drm &drm_driver.lastबंद callback
 * when implementing an fbcon on top of kms using this helper. This ensures that
 * the user isn't greeted with a black screen when e.g. X dies.
 *
 * RETURNS:
 * Zero अगर everything went ok, negative error code otherwise.
 */
पूर्णांक drm_fb_helper_restore_fbdev_mode_unlocked(काष्ठा drm_fb_helper *fb_helper)
अणु
	वापस __drm_fb_helper_restore_fbdev_mode_unlocked(fb_helper, false);
पूर्ण
EXPORT_SYMBOL(drm_fb_helper_restore_fbdev_mode_unlocked);

#अगर_घोषित CONFIG_MAGIC_SYSRQ
/* emergency restore, करोn't bother with error reporting */
अटल व्योम drm_fb_helper_restore_work_fn(काष्ठा work_काष्ठा *ignored)
अणु
	काष्ठा drm_fb_helper *helper;

	mutex_lock(&kernel_fb_helper_lock);
	list_क्रम_each_entry(helper, &kernel_fb_helper_list, kernel_fb_list) अणु
		काष्ठा drm_device *dev = helper->dev;

		अगर (dev->चयन_घातer_state == DRM_SWITCH_POWER_OFF)
			जारी;

		mutex_lock(&helper->lock);
		drm_client_modeset_commit_locked(&helper->client);
		mutex_unlock(&helper->lock);
	पूर्ण
	mutex_unlock(&kernel_fb_helper_lock);
पूर्ण

अटल DECLARE_WORK(drm_fb_helper_restore_work, drm_fb_helper_restore_work_fn);

अटल व्योम drm_fb_helper_sysrq(पूर्णांक dummy1)
अणु
	schedule_work(&drm_fb_helper_restore_work);
पूर्ण

अटल स्थिर काष्ठा sysrq_key_op sysrq_drm_fb_helper_restore_op = अणु
	.handler = drm_fb_helper_sysrq,
	.help_msg = "force-fb(v)",
	.action_msg = "Restore framebuffer console",
पूर्ण;
#अन्यथा
अटल स्थिर काष्ठा sysrq_key_op sysrq_drm_fb_helper_restore_op = अणु पूर्ण;
#पूर्ण_अगर

अटल व्योम drm_fb_helper_dpms(काष्ठा fb_info *info, पूर्णांक dpms_mode)
अणु
	काष्ठा drm_fb_helper *fb_helper = info->par;

	mutex_lock(&fb_helper->lock);
	drm_client_modeset_dpms(&fb_helper->client, dpms_mode);
	mutex_unlock(&fb_helper->lock);
पूर्ण

/**
 * drm_fb_helper_blank - implementation क्रम &fb_ops.fb_blank
 * @blank: desired blanking state
 * @info: fbdev रेजिस्टरed by the helper
 */
पूर्णांक drm_fb_helper_blank(पूर्णांक blank, काष्ठा fb_info *info)
अणु
	अगर (oops_in_progress)
		वापस -EBUSY;

	चयन (blank) अणु
	/* Display: On; HSync: On, VSync: On */
	हाल FB_BLANK_UNBLANK:
		drm_fb_helper_dpms(info, DRM_MODE_DPMS_ON);
		अवरोध;
	/* Display: Off; HSync: On, VSync: On */
	हाल FB_BLANK_NORMAL:
		drm_fb_helper_dpms(info, DRM_MODE_DPMS_STANDBY);
		अवरोध;
	/* Display: Off; HSync: Off, VSync: On */
	हाल FB_BLANK_HSYNC_SUSPEND:
		drm_fb_helper_dpms(info, DRM_MODE_DPMS_STANDBY);
		अवरोध;
	/* Display: Off; HSync: On, VSync: Off */
	हाल FB_BLANK_VSYNC_SUSPEND:
		drm_fb_helper_dpms(info, DRM_MODE_DPMS_SUSPEND);
		अवरोध;
	/* Display: Off; HSync: Off, VSync: Off */
	हाल FB_BLANK_POWERDOWN:
		drm_fb_helper_dpms(info, DRM_MODE_DPMS_OFF);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_fb_helper_blank);

अटल व्योम drm_fb_helper_resume_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा drm_fb_helper *helper = container_of(work, काष्ठा drm_fb_helper,
						    resume_work);

	console_lock();
	fb_set_suspend(helper->fbdev, 0);
	console_unlock();
पूर्ण

अटल व्योम drm_fb_helper_damage_blit_real(काष्ठा drm_fb_helper *fb_helper,
					   काष्ठा drm_clip_rect *clip,
					   काष्ठा dma_buf_map *dst)
अणु
	काष्ठा drm_framebuffer *fb = fb_helper->fb;
	अचिन्हित पूर्णांक cpp = fb->क्रमmat->cpp[0];
	माप_प्रकार offset = clip->y1 * fb->pitches[0] + clip->x1 * cpp;
	व्योम *src = fb_helper->fbdev->screen_buffer + offset;
	माप_प्रकार len = (clip->x2 - clip->x1) * cpp;
	अचिन्हित पूर्णांक y;

	dma_buf_map_incr(dst, offset); /* go to first pixel within clip rect */

	क्रम (y = clip->y1; y < clip->y2; y++) अणु
		dma_buf_map_स_नकल_to(dst, src, len);
		dma_buf_map_incr(dst, fb->pitches[0]);
		src += fb->pitches[0];
	पूर्ण
पूर्ण

अटल पूर्णांक drm_fb_helper_damage_blit(काष्ठा drm_fb_helper *fb_helper,
				     काष्ठा drm_clip_rect *clip)
अणु
	काष्ठा drm_client_buffer *buffer = fb_helper->buffer;
	काष्ठा dma_buf_map map, dst;
	पूर्णांक ret;

	/*
	 * We have to pin the client buffer to its current location जबतक
	 * flushing the shaकरोw buffer. In the general हाल, concurrent
	 * modesetting operations could try to move the buffer and would
	 * fail. The modeset has to be serialized by acquiring the reservation
	 * object of the underlying BO here.
	 *
	 * For fbdev emulation, we only have to protect against fbdev modeset
	 * operations. Nothing अन्यथा will involve the client buffer's BO. So it
	 * is sufficient to acquire काष्ठा drm_fb_helper.lock here.
	 */
	mutex_lock(&fb_helper->lock);

	ret = drm_client_buffer_vmap(buffer, &map);
	अगर (ret)
		जाओ out;

	dst = map;
	drm_fb_helper_damage_blit_real(fb_helper, clip, &dst);

	drm_client_buffer_vunmap(buffer);

out:
	mutex_unlock(&fb_helper->lock);

	वापस ret;
पूर्ण

अटल व्योम drm_fb_helper_damage_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा drm_fb_helper *helper = container_of(work, काष्ठा drm_fb_helper,
						    damage_work);
	काष्ठा drm_device *dev = helper->dev;
	काष्ठा drm_clip_rect *clip = &helper->damage_clip;
	काष्ठा drm_clip_rect clip_copy;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&helper->damage_lock, flags);
	clip_copy = *clip;
	clip->x1 = clip->y1 = ~0;
	clip->x2 = clip->y2 = 0;
	spin_unlock_irqrestore(&helper->damage_lock, flags);

	/* Call damage handlers only अगर necessary */
	अगर (!(clip_copy.x1 < clip_copy.x2 && clip_copy.y1 < clip_copy.y2))
		वापस;

	अगर (helper->buffer) अणु
		ret = drm_fb_helper_damage_blit(helper, &clip_copy);
		अगर (drm_WARN_ONCE(dev, ret, "Damage blitter failed: ret=%d\n", ret))
			जाओ err;
	पूर्ण

	अगर (helper->fb->funcs->dirty) अणु
		ret = helper->fb->funcs->dirty(helper->fb, शून्य, 0, 0, &clip_copy, 1);
		अगर (drm_WARN_ONCE(dev, ret, "Dirty helper failed: ret=%d\n", ret))
			जाओ err;
	पूर्ण

	वापस;

err:
	/*
	 * Restore damage clip rectangle on errors. The next run
	 * of the damage worker will perक्रमm the update.
	 */
	spin_lock_irqsave(&helper->damage_lock, flags);
	clip->x1 = min_t(u32, clip->x1, clip_copy.x1);
	clip->y1 = min_t(u32, clip->y1, clip_copy.y1);
	clip->x2 = max_t(u32, clip->x2, clip_copy.x2);
	clip->y2 = max_t(u32, clip->y2, clip_copy.y2);
	spin_unlock_irqrestore(&helper->damage_lock, flags);
पूर्ण

/**
 * drm_fb_helper_prepare - setup a drm_fb_helper काष्ठाure
 * @dev: DRM device
 * @helper: driver-allocated fbdev helper काष्ठाure to set up
 * @funcs: poपूर्णांकer to काष्ठाure of functions associate with this helper
 *
 * Sets up the bare minimum to make the framebuffer helper usable. This is
 * useful to implement race-मुक्त initialization of the polling helpers.
 */
व्योम drm_fb_helper_prepare(काष्ठा drm_device *dev, काष्ठा drm_fb_helper *helper,
			   स्थिर काष्ठा drm_fb_helper_funcs *funcs)
अणु
	INIT_LIST_HEAD(&helper->kernel_fb_list);
	spin_lock_init(&helper->damage_lock);
	INIT_WORK(&helper->resume_work, drm_fb_helper_resume_worker);
	INIT_WORK(&helper->damage_work, drm_fb_helper_damage_work);
	helper->damage_clip.x1 = helper->damage_clip.y1 = ~0;
	mutex_init(&helper->lock);
	helper->funcs = funcs;
	helper->dev = dev;
पूर्ण
EXPORT_SYMBOL(drm_fb_helper_prepare);

/**
 * drm_fb_helper_init - initialize a &काष्ठा drm_fb_helper
 * @dev: drm device
 * @fb_helper: driver-allocated fbdev helper काष्ठाure to initialize
 *
 * This allocates the काष्ठाures क्रम the fbdev helper with the given limits.
 * Note that this won't yet touch the hardware (through the driver पूर्णांकerfaces)
 * nor रेजिस्टर the fbdev. This is only करोne in drm_fb_helper_initial_config()
 * to allow driver ग_लिखोs more control over the exact init sequence.
 *
 * Drivers must call drm_fb_helper_prepare() beक्रमe calling this function.
 *
 * RETURNS:
 * Zero अगर everything went ok, nonzero otherwise.
 */
पूर्णांक drm_fb_helper_init(काष्ठा drm_device *dev,
		       काष्ठा drm_fb_helper *fb_helper)
अणु
	पूर्णांक ret;

	अगर (!drm_fbdev_emulation) अणु
		dev->fb_helper = fb_helper;
		वापस 0;
	पूर्ण

	/*
	 * If this is not the generic fbdev client, initialize a drm_client
	 * without callbacks so we can use the modesets.
	 */
	अगर (!fb_helper->client.funcs) अणु
		ret = drm_client_init(dev, &fb_helper->client, "drm_fb_helper", शून्य);
		अगर (ret)
			वापस ret;
	पूर्ण

	dev->fb_helper = fb_helper;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_fb_helper_init);

/**
 * drm_fb_helper_alloc_fbi - allocate fb_info and some of its members
 * @fb_helper: driver-allocated fbdev helper
 *
 * A helper to alloc fb_info and the members cmap and apertures. Called
 * by the driver within the fb_probe fb_helper callback function. Drivers करो not
 * need to release the allocated fb_info काष्ठाure themselves, this is
 * स्वतःmatically करोne when calling drm_fb_helper_fini().
 *
 * RETURNS:
 * fb_info poपूर्णांकer अगर things went okay, poपूर्णांकer containing error code
 * otherwise
 */
काष्ठा fb_info *drm_fb_helper_alloc_fbi(काष्ठा drm_fb_helper *fb_helper)
अणु
	काष्ठा device *dev = fb_helper->dev->dev;
	काष्ठा fb_info *info;
	पूर्णांक ret;

	info = framebuffer_alloc(0, dev);
	अगर (!info)
		वापस ERR_PTR(-ENOMEM);

	ret = fb_alloc_cmap(&info->cmap, 256, 0);
	अगर (ret)
		जाओ err_release;

	/*
	 * TODO: We really should be smarter here and alloc an apperture
	 * क्रम each IORESOURCE_MEM resource helper->dev->dev has and also
	 * init the ranges of the appertures based on the resources.
	 * Note some drivers currently count on there being only 1 empty
	 * aperture and fill this themselves, these will need to be dealt
	 * with somehow when fixing this.
	 */
	info->apertures = alloc_apertures(1);
	अगर (!info->apertures) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_cmap;
	पूर्ण

	fb_helper->fbdev = info;
	info->skip_vt_चयन = true;

	वापस info;

err_मुक्त_cmap:
	fb_dealloc_cmap(&info->cmap);
err_release:
	framebuffer_release(info);
	वापस ERR_PTR(ret);
पूर्ण
EXPORT_SYMBOL(drm_fb_helper_alloc_fbi);

/**
 * drm_fb_helper_unरेजिस्टर_fbi - unरेजिस्टर fb_info framebuffer device
 * @fb_helper: driver-allocated fbdev helper, can be शून्य
 *
 * A wrapper around unरेजिस्टर_framebuffer, to release the fb_info
 * framebuffer device. This must be called beक्रमe releasing all resources क्रम
 * @fb_helper by calling drm_fb_helper_fini().
 */
व्योम drm_fb_helper_unरेजिस्टर_fbi(काष्ठा drm_fb_helper *fb_helper)
अणु
	अगर (fb_helper && fb_helper->fbdev)
		unरेजिस्टर_framebuffer(fb_helper->fbdev);
पूर्ण
EXPORT_SYMBOL(drm_fb_helper_unरेजिस्टर_fbi);

/**
 * drm_fb_helper_fini - finialize a &काष्ठा drm_fb_helper
 * @fb_helper: driver-allocated fbdev helper, can be शून्य
 *
 * This cleans up all reमुख्यing resources associated with @fb_helper.
 */
व्योम drm_fb_helper_fini(काष्ठा drm_fb_helper *fb_helper)
अणु
	काष्ठा fb_info *info;

	अगर (!fb_helper)
		वापस;

	fb_helper->dev->fb_helper = शून्य;

	अगर (!drm_fbdev_emulation)
		वापस;

	cancel_work_sync(&fb_helper->resume_work);
	cancel_work_sync(&fb_helper->damage_work);

	info = fb_helper->fbdev;
	अगर (info) अणु
		अगर (info->cmap.len)
			fb_dealloc_cmap(&info->cmap);
		framebuffer_release(info);
	पूर्ण
	fb_helper->fbdev = शून्य;

	mutex_lock(&kernel_fb_helper_lock);
	अगर (!list_empty(&fb_helper->kernel_fb_list)) अणु
		list_del(&fb_helper->kernel_fb_list);
		अगर (list_empty(&kernel_fb_helper_list))
			unरेजिस्टर_sysrq_key('v', &sysrq_drm_fb_helper_restore_op);
	पूर्ण
	mutex_unlock(&kernel_fb_helper_lock);

	mutex_destroy(&fb_helper->lock);

	अगर (!fb_helper->client.funcs)
		drm_client_release(&fb_helper->client);
पूर्ण
EXPORT_SYMBOL(drm_fb_helper_fini);

अटल bool drm_fbdev_use_shaकरोw_fb(काष्ठा drm_fb_helper *fb_helper)
अणु
	काष्ठा drm_device *dev = fb_helper->dev;
	काष्ठा drm_framebuffer *fb = fb_helper->fb;

	वापस dev->mode_config.prefer_shaकरोw_fbdev ||
	       dev->mode_config.prefer_shaकरोw ||
	       fb->funcs->dirty;
पूर्ण

अटल व्योम drm_fb_helper_damage(काष्ठा fb_info *info, u32 x, u32 y,
				 u32 width, u32 height)
अणु
	काष्ठा drm_fb_helper *helper = info->par;
	काष्ठा drm_clip_rect *clip = &helper->damage_clip;
	अचिन्हित दीर्घ flags;

	अगर (!drm_fbdev_use_shaकरोw_fb(helper))
		वापस;

	spin_lock_irqsave(&helper->damage_lock, flags);
	clip->x1 = min_t(u32, clip->x1, x);
	clip->y1 = min_t(u32, clip->y1, y);
	clip->x2 = max_t(u32, clip->x2, x + width);
	clip->y2 = max_t(u32, clip->y2, y + height);
	spin_unlock_irqrestore(&helper->damage_lock, flags);

	schedule_work(&helper->damage_work);
पूर्ण

/**
 * drm_fb_helper_deferred_io() - fbdev deferred_io callback function
 * @info: fb_info काष्ठा poपूर्णांकer
 * @pagelist: list of mmap framebuffer pages that have to be flushed
 *
 * This function is used as the &fb_deferred_io.deferred_io
 * callback function क्रम flushing the fbdev mmap ग_लिखोs.
 */
व्योम drm_fb_helper_deferred_io(काष्ठा fb_info *info,
			       काष्ठा list_head *pagelist)
अणु
	अचिन्हित दीर्घ start, end, min, max;
	काष्ठा page *page;
	u32 y1, y2;

	min = अच_दीर्घ_उच्च;
	max = 0;
	list_क्रम_each_entry(page, pagelist, lru) अणु
		start = page->index << PAGE_SHIFT;
		end = start + PAGE_SIZE - 1;
		min = min(min, start);
		max = max(max, end);
	पूर्ण

	अगर (min < max) अणु
		y1 = min / info->fix.line_length;
		y2 = min_t(u32, DIV_ROUND_UP(max, info->fix.line_length),
			   info->var.yres);
		drm_fb_helper_damage(info, 0, y1, info->var.xres, y2 - y1);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(drm_fb_helper_deferred_io);

/**
 * drm_fb_helper_sys_पढ़ो - wrapper around fb_sys_पढ़ो
 * @info: fb_info काष्ठा poपूर्णांकer
 * @buf: userspace buffer to पढ़ो from framebuffer memory
 * @count: number of bytes to पढ़ो from framebuffer memory
 * @ppos: पढ़ो offset within framebuffer memory
 *
 * A wrapper around fb_sys_पढ़ो implemented by fbdev core
 */
sमाप_प्रकार drm_fb_helper_sys_पढ़ो(काष्ठा fb_info *info, अक्षर __user *buf,
			       माप_प्रकार count, loff_t *ppos)
अणु
	वापस fb_sys_पढ़ो(info, buf, count, ppos);
पूर्ण
EXPORT_SYMBOL(drm_fb_helper_sys_पढ़ो);

/**
 * drm_fb_helper_sys_ग_लिखो - wrapper around fb_sys_ग_लिखो
 * @info: fb_info काष्ठा poपूर्णांकer
 * @buf: userspace buffer to ग_लिखो to framebuffer memory
 * @count: number of bytes to ग_लिखो to framebuffer memory
 * @ppos: ग_लिखो offset within framebuffer memory
 *
 * A wrapper around fb_sys_ग_लिखो implemented by fbdev core
 */
sमाप_प्रकार drm_fb_helper_sys_ग_लिखो(काष्ठा fb_info *info, स्थिर अक्षर __user *buf,
				माप_प्रकार count, loff_t *ppos)
अणु
	sमाप_प्रकार ret;

	ret = fb_sys_ग_लिखो(info, buf, count, ppos);
	अगर (ret > 0)
		drm_fb_helper_damage(info, 0, 0, info->var.xres, info->var.yres);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_fb_helper_sys_ग_लिखो);

/**
 * drm_fb_helper_sys_fillrect - wrapper around sys_fillrect
 * @info: fbdev रेजिस्टरed by the helper
 * @rect: info about rectangle to fill
 *
 * A wrapper around sys_fillrect implemented by fbdev core
 */
व्योम drm_fb_helper_sys_fillrect(काष्ठा fb_info *info,
				स्थिर काष्ठा fb_fillrect *rect)
अणु
	sys_fillrect(info, rect);
	drm_fb_helper_damage(info, rect->dx, rect->dy, rect->width, rect->height);
पूर्ण
EXPORT_SYMBOL(drm_fb_helper_sys_fillrect);

/**
 * drm_fb_helper_sys_copyarea - wrapper around sys_copyarea
 * @info: fbdev रेजिस्टरed by the helper
 * @area: info about area to copy
 *
 * A wrapper around sys_copyarea implemented by fbdev core
 */
व्योम drm_fb_helper_sys_copyarea(काष्ठा fb_info *info,
				स्थिर काष्ठा fb_copyarea *area)
अणु
	sys_copyarea(info, area);
	drm_fb_helper_damage(info, area->dx, area->dy, area->width, area->height);
पूर्ण
EXPORT_SYMBOL(drm_fb_helper_sys_copyarea);

/**
 * drm_fb_helper_sys_imageblit - wrapper around sys_imageblit
 * @info: fbdev रेजिस्टरed by the helper
 * @image: info about image to blit
 *
 * A wrapper around sys_imageblit implemented by fbdev core
 */
व्योम drm_fb_helper_sys_imageblit(काष्ठा fb_info *info,
				 स्थिर काष्ठा fb_image *image)
अणु
	sys_imageblit(info, image);
	drm_fb_helper_damage(info, image->dx, image->dy, image->width, image->height);
पूर्ण
EXPORT_SYMBOL(drm_fb_helper_sys_imageblit);

/**
 * drm_fb_helper_cfb_fillrect - wrapper around cfb_fillrect
 * @info: fbdev रेजिस्टरed by the helper
 * @rect: info about rectangle to fill
 *
 * A wrapper around cfb_fillrect implemented by fbdev core
 */
व्योम drm_fb_helper_cfb_fillrect(काष्ठा fb_info *info,
				स्थिर काष्ठा fb_fillrect *rect)
अणु
	cfb_fillrect(info, rect);
	drm_fb_helper_damage(info, rect->dx, rect->dy, rect->width, rect->height);
पूर्ण
EXPORT_SYMBOL(drm_fb_helper_cfb_fillrect);

/**
 * drm_fb_helper_cfb_copyarea - wrapper around cfb_copyarea
 * @info: fbdev रेजिस्टरed by the helper
 * @area: info about area to copy
 *
 * A wrapper around cfb_copyarea implemented by fbdev core
 */
व्योम drm_fb_helper_cfb_copyarea(काष्ठा fb_info *info,
				स्थिर काष्ठा fb_copyarea *area)
अणु
	cfb_copyarea(info, area);
	drm_fb_helper_damage(info, area->dx, area->dy, area->width, area->height);
पूर्ण
EXPORT_SYMBOL(drm_fb_helper_cfb_copyarea);

/**
 * drm_fb_helper_cfb_imageblit - wrapper around cfb_imageblit
 * @info: fbdev रेजिस्टरed by the helper
 * @image: info about image to blit
 *
 * A wrapper around cfb_imageblit implemented by fbdev core
 */
व्योम drm_fb_helper_cfb_imageblit(काष्ठा fb_info *info,
				 स्थिर काष्ठा fb_image *image)
अणु
	cfb_imageblit(info, image);
	drm_fb_helper_damage(info, image->dx, image->dy, image->width, image->height);
पूर्ण
EXPORT_SYMBOL(drm_fb_helper_cfb_imageblit);

/**
 * drm_fb_helper_set_suspend - wrapper around fb_set_suspend
 * @fb_helper: driver-allocated fbdev helper, can be शून्य
 * @suspend: whether to suspend or resume
 *
 * A wrapper around fb_set_suspend implemented by fbdev core.
 * Use drm_fb_helper_set_suspend_unlocked() अगर you करोn't need to take
 * the lock yourself
 */
व्योम drm_fb_helper_set_suspend(काष्ठा drm_fb_helper *fb_helper, bool suspend)
अणु
	अगर (fb_helper && fb_helper->fbdev)
		fb_set_suspend(fb_helper->fbdev, suspend);
पूर्ण
EXPORT_SYMBOL(drm_fb_helper_set_suspend);

/**
 * drm_fb_helper_set_suspend_unlocked - wrapper around fb_set_suspend that also
 *                                      takes the console lock
 * @fb_helper: driver-allocated fbdev helper, can be शून्य
 * @suspend: whether to suspend or resume
 *
 * A wrapper around fb_set_suspend() that takes the console lock. If the lock
 * isn't available on resume, a worker is tasked with रुकोing क्रम the lock
 * to become available. The console lock can be pretty contented on resume
 * due to all the prपूर्णांकk activity.
 *
 * This function can be called multiple बार with the same state since
 * &fb_info.state is checked to see अगर fbdev is running or not beक्रमe locking.
 *
 * Use drm_fb_helper_set_suspend() अगर you need to take the lock yourself.
 */
व्योम drm_fb_helper_set_suspend_unlocked(काष्ठा drm_fb_helper *fb_helper,
					bool suspend)
अणु
	अगर (!fb_helper || !fb_helper->fbdev)
		वापस;

	/* make sure there's no pending/ongoing resume */
	flush_work(&fb_helper->resume_work);

	अगर (suspend) अणु
		अगर (fb_helper->fbdev->state != FBINFO_STATE_RUNNING)
			वापस;

		console_lock();

	पूर्ण अन्यथा अणु
		अगर (fb_helper->fbdev->state == FBINFO_STATE_RUNNING)
			वापस;

		अगर (!console_trylock()) अणु
			schedule_work(&fb_helper->resume_work);
			वापस;
		पूर्ण
	पूर्ण

	fb_set_suspend(fb_helper->fbdev, suspend);
	console_unlock();
पूर्ण
EXPORT_SYMBOL(drm_fb_helper_set_suspend_unlocked);

अटल पूर्णांक setcmap_pseuकरो_palette(काष्ठा fb_cmap *cmap, काष्ठा fb_info *info)
अणु
	u32 *palette = (u32 *)info->pseuकरो_palette;
	पूर्णांक i;

	अगर (cmap->start + cmap->len > 16)
		वापस -EINVAL;

	क्रम (i = 0; i < cmap->len; ++i) अणु
		u16 red = cmap->red[i];
		u16 green = cmap->green[i];
		u16 blue = cmap->blue[i];
		u32 value;

		red >>= 16 - info->var.red.length;
		green >>= 16 - info->var.green.length;
		blue >>= 16 - info->var.blue.length;
		value = (red << info->var.red.offset) |
			(green << info->var.green.offset) |
			(blue << info->var.blue.offset);
		अगर (info->var.transp.length > 0) अणु
			u32 mask = (1 << info->var.transp.length) - 1;

			mask <<= info->var.transp.offset;
			value |= mask;
		पूर्ण
		palette[cmap->start + i] = value;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक setcmap_legacy(काष्ठा fb_cmap *cmap, काष्ठा fb_info *info)
अणु
	काष्ठा drm_fb_helper *fb_helper = info->par;
	काष्ठा drm_mode_set *modeset;
	काष्ठा drm_crtc *crtc;
	u16 *r, *g, *b;
	पूर्णांक ret = 0;

	drm_modeset_lock_all(fb_helper->dev);
	drm_client_क्रम_each_modeset(modeset, &fb_helper->client) अणु
		crtc = modeset->crtc;
		अगर (!crtc->funcs->gamma_set || !crtc->gamma_size) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		अगर (cmap->start + cmap->len > crtc->gamma_size) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		r = crtc->gamma_store;
		g = r + crtc->gamma_size;
		b = g + crtc->gamma_size;

		स_नकल(r + cmap->start, cmap->red, cmap->len * माप(*r));
		स_नकल(g + cmap->start, cmap->green, cmap->len * माप(*g));
		स_नकल(b + cmap->start, cmap->blue, cmap->len * माप(*b));

		ret = crtc->funcs->gamma_set(crtc, r, g, b,
					     crtc->gamma_size, शून्य);
		अगर (ret)
			जाओ out;
	पूर्ण
out:
	drm_modeset_unlock_all(fb_helper->dev);

	वापस ret;
पूर्ण

अटल काष्ठा drm_property_blob *setcmap_new_gamma_lut(काष्ठा drm_crtc *crtc,
						       काष्ठा fb_cmap *cmap)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा drm_property_blob *gamma_lut;
	काष्ठा drm_color_lut *lut;
	पूर्णांक size = crtc->gamma_size;
	पूर्णांक i;

	अगर (!size || cmap->start + cmap->len > size)
		वापस ERR_PTR(-EINVAL);

	gamma_lut = drm_property_create_blob(dev, माप(*lut) * size, शून्य);
	अगर (IS_ERR(gamma_lut))
		वापस gamma_lut;

	lut = gamma_lut->data;
	अगर (cmap->start || cmap->len != size) अणु
		u16 *r = crtc->gamma_store;
		u16 *g = r + crtc->gamma_size;
		u16 *b = g + crtc->gamma_size;

		क्रम (i = 0; i < cmap->start; i++) अणु
			lut[i].red = r[i];
			lut[i].green = g[i];
			lut[i].blue = b[i];
		पूर्ण
		क्रम (i = cmap->start + cmap->len; i < size; i++) अणु
			lut[i].red = r[i];
			lut[i].green = g[i];
			lut[i].blue = b[i];
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < cmap->len; i++) अणु
		lut[cmap->start + i].red = cmap->red[i];
		lut[cmap->start + i].green = cmap->green[i];
		lut[cmap->start + i].blue = cmap->blue[i];
	पूर्ण

	वापस gamma_lut;
पूर्ण

अटल पूर्णांक setcmap_atomic(काष्ठा fb_cmap *cmap, काष्ठा fb_info *info)
अणु
	काष्ठा drm_fb_helper *fb_helper = info->par;
	काष्ठा drm_device *dev = fb_helper->dev;
	काष्ठा drm_property_blob *gamma_lut = शून्य;
	काष्ठा drm_modeset_acquire_ctx ctx;
	काष्ठा drm_crtc_state *crtc_state;
	काष्ठा drm_atomic_state *state;
	काष्ठा drm_mode_set *modeset;
	काष्ठा drm_crtc *crtc;
	u16 *r, *g, *b;
	bool replaced;
	पूर्णांक ret = 0;

	drm_modeset_acquire_init(&ctx, 0);

	state = drm_atomic_state_alloc(dev);
	अगर (!state) अणु
		ret = -ENOMEM;
		जाओ out_ctx;
	पूर्ण

	state->acquire_ctx = &ctx;
retry:
	drm_client_क्रम_each_modeset(modeset, &fb_helper->client) अणु
		crtc = modeset->crtc;

		अगर (!gamma_lut)
			gamma_lut = setcmap_new_gamma_lut(crtc, cmap);
		अगर (IS_ERR(gamma_lut)) अणु
			ret = PTR_ERR(gamma_lut);
			gamma_lut = शून्य;
			जाओ out_state;
		पूर्ण

		crtc_state = drm_atomic_get_crtc_state(state, crtc);
		अगर (IS_ERR(crtc_state)) अणु
			ret = PTR_ERR(crtc_state);
			जाओ out_state;
		पूर्ण

		/*
		 * FIXME: This always uses gamma_lut. Some HW have only
		 * degamma_lut, in which हाल we should reset gamma_lut and set
		 * degamma_lut. See drm_crtc_legacy_gamma_set().
		 */
		replaced  = drm_property_replace_blob(&crtc_state->degamma_lut,
						      शून्य);
		replaced |= drm_property_replace_blob(&crtc_state->cपंचांग, शून्य);
		replaced |= drm_property_replace_blob(&crtc_state->gamma_lut,
						      gamma_lut);
		crtc_state->color_mgmt_changed |= replaced;
	पूर्ण

	ret = drm_atomic_commit(state);
	अगर (ret)
		जाओ out_state;

	drm_client_क्रम_each_modeset(modeset, &fb_helper->client) अणु
		crtc = modeset->crtc;

		r = crtc->gamma_store;
		g = r + crtc->gamma_size;
		b = g + crtc->gamma_size;

		स_नकल(r + cmap->start, cmap->red, cmap->len * माप(*r));
		स_नकल(g + cmap->start, cmap->green, cmap->len * माप(*g));
		स_नकल(b + cmap->start, cmap->blue, cmap->len * माप(*b));
	पूर्ण

out_state:
	अगर (ret == -EDEADLK)
		जाओ backoff;

	drm_property_blob_put(gamma_lut);
	drm_atomic_state_put(state);
out_ctx:
	drm_modeset_drop_locks(&ctx);
	drm_modeset_acquire_fini(&ctx);

	वापस ret;

backoff:
	drm_atomic_state_clear(state);
	drm_modeset_backoff(&ctx);
	जाओ retry;
पूर्ण

/**
 * drm_fb_helper_setcmap - implementation क्रम &fb_ops.fb_setcmap
 * @cmap: cmap to set
 * @info: fbdev रेजिस्टरed by the helper
 */
पूर्णांक drm_fb_helper_setcmap(काष्ठा fb_cmap *cmap, काष्ठा fb_info *info)
अणु
	काष्ठा drm_fb_helper *fb_helper = info->par;
	काष्ठा drm_device *dev = fb_helper->dev;
	पूर्णांक ret;

	अगर (oops_in_progress)
		वापस -EBUSY;

	mutex_lock(&fb_helper->lock);

	अगर (!drm_master_पूर्णांकernal_acquire(dev)) अणु
		ret = -EBUSY;
		जाओ unlock;
	पूर्ण

	mutex_lock(&fb_helper->client.modeset_mutex);
	अगर (info->fix.visual == FB_VISUAL_TRUECOLOR)
		ret = setcmap_pseuकरो_palette(cmap, info);
	अन्यथा अगर (drm_drv_uses_atomic_modeset(fb_helper->dev))
		ret = setcmap_atomic(cmap, info);
	अन्यथा
		ret = setcmap_legacy(cmap, info);
	mutex_unlock(&fb_helper->client.modeset_mutex);

	drm_master_पूर्णांकernal_release(dev);
unlock:
	mutex_unlock(&fb_helper->lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_fb_helper_setcmap);

/**
 * drm_fb_helper_ioctl - legacy ioctl implementation
 * @info: fbdev रेजिस्टरed by the helper
 * @cmd: ioctl command
 * @arg: ioctl argument
 *
 * A helper to implement the standard fbdev ioctl. Only
 * FBIO_WAITFORVSYNC is implemented क्रम now.
 */
पूर्णांक drm_fb_helper_ioctl(काष्ठा fb_info *info, अचिन्हित पूर्णांक cmd,
			अचिन्हित दीर्घ arg)
अणु
	काष्ठा drm_fb_helper *fb_helper = info->par;
	काष्ठा drm_device *dev = fb_helper->dev;
	काष्ठा drm_crtc *crtc;
	पूर्णांक ret = 0;

	mutex_lock(&fb_helper->lock);
	अगर (!drm_master_पूर्णांकernal_acquire(dev)) अणु
		ret = -EBUSY;
		जाओ unlock;
	पूर्ण

	चयन (cmd) अणु
	हाल FBIO_WAITFORVSYNC:
		/*
		 * Only consider the first CRTC.
		 *
		 * This ioctl is supposed to take the CRTC number as
		 * an argument, but in fbdev बार, what that number
		 * was supposed to be was quite unclear, dअगरferent
		 * drivers were passing that argument dअगरferently
		 * (some by reference, some by value), and most of the
		 * userspace applications were just hardcoding 0 as an
		 * argument.
		 *
		 * The first CRTC should be the पूर्णांकegrated panel on
		 * most drivers, so this is the best choice we can
		 * make. If we're not smart enough here, one should
		 * just consider चयन the userspace to KMS.
		 */
		crtc = fb_helper->client.modesets[0].crtc;

		/*
		 * Only रुको क्रम a vblank event अगर the CRTC is
		 * enabled, otherwise just करोn't करो anythपूर्णांकg,
		 * not even report an error.
		 */
		ret = drm_crtc_vblank_get(crtc);
		अगर (!ret) अणु
			drm_crtc_रुको_one_vblank(crtc);
			drm_crtc_vblank_put(crtc);
		पूर्ण

		ret = 0;
		अवरोध;
	शेष:
		ret = -ENOTTY;
	पूर्ण

	drm_master_पूर्णांकernal_release(dev);
unlock:
	mutex_unlock(&fb_helper->lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_fb_helper_ioctl);

अटल bool drm_fb_pixel_क्रमmat_equal(स्थिर काष्ठा fb_var_screeninfo *var_1,
				      स्थिर काष्ठा fb_var_screeninfo *var_2)
अणु
	वापस var_1->bits_per_pixel == var_2->bits_per_pixel &&
	       var_1->grayscale == var_2->grayscale &&
	       var_1->red.offset == var_2->red.offset &&
	       var_1->red.length == var_2->red.length &&
	       var_1->red.msb_right == var_2->red.msb_right &&
	       var_1->green.offset == var_2->green.offset &&
	       var_1->green.length == var_2->green.length &&
	       var_1->green.msb_right == var_2->green.msb_right &&
	       var_1->blue.offset == var_2->blue.offset &&
	       var_1->blue.length == var_2->blue.length &&
	       var_1->blue.msb_right == var_2->blue.msb_right &&
	       var_1->transp.offset == var_2->transp.offset &&
	       var_1->transp.length == var_2->transp.length &&
	       var_1->transp.msb_right == var_2->transp.msb_right;
पूर्ण

अटल व्योम drm_fb_helper_fill_pixel_fmt(काष्ठा fb_var_screeninfo *var,
					 u8 depth)
अणु
	चयन (depth) अणु
	हाल 8:
		var->red.offset = 0;
		var->green.offset = 0;
		var->blue.offset = 0;
		var->red.length = 8; /* 8bit DAC */
		var->green.length = 8;
		var->blue.length = 8;
		var->transp.offset = 0;
		var->transp.length = 0;
		अवरोध;
	हाल 15:
		var->red.offset = 10;
		var->green.offset = 5;
		var->blue.offset = 0;
		var->red.length = 5;
		var->green.length = 5;
		var->blue.length = 5;
		var->transp.offset = 15;
		var->transp.length = 1;
		अवरोध;
	हाल 16:
		var->red.offset = 11;
		var->green.offset = 5;
		var->blue.offset = 0;
		var->red.length = 5;
		var->green.length = 6;
		var->blue.length = 5;
		var->transp.offset = 0;
		अवरोध;
	हाल 24:
		var->red.offset = 16;
		var->green.offset = 8;
		var->blue.offset = 0;
		var->red.length = 8;
		var->green.length = 8;
		var->blue.length = 8;
		var->transp.offset = 0;
		var->transp.length = 0;
		अवरोध;
	हाल 32:
		var->red.offset = 16;
		var->green.offset = 8;
		var->blue.offset = 0;
		var->red.length = 8;
		var->green.length = 8;
		var->blue.length = 8;
		var->transp.offset = 24;
		var->transp.length = 8;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/**
 * drm_fb_helper_check_var - implementation क्रम &fb_ops.fb_check_var
 * @var: screeninfo to check
 * @info: fbdev रेजिस्टरed by the helper
 */
पूर्णांक drm_fb_helper_check_var(काष्ठा fb_var_screeninfo *var,
			    काष्ठा fb_info *info)
अणु
	काष्ठा drm_fb_helper *fb_helper = info->par;
	काष्ठा drm_framebuffer *fb = fb_helper->fb;
	काष्ठा drm_device *dev = fb_helper->dev;

	अगर (in_dbg_master())
		वापस -EINVAL;

	अगर (var->pixघड़ी != 0) अणु
		drm_dbg_kms(dev, "fbdev emulation doesn't support changing the pixel clock, value of pixclock is ignored\n");
		var->pixघड़ी = 0;
	पूर्ण

	अगर ((drm_क्रमmat_info_block_width(fb->क्रमmat, 0) > 1) ||
	    (drm_क्रमmat_info_block_height(fb->क्रमmat, 0) > 1))
		वापस -EINVAL;

	/*
	 * Changes काष्ठा fb_var_screeninfo are currently not pushed back
	 * to KMS, hence fail अगर dअगरferent settings are requested.
	 */
	अगर (var->bits_per_pixel > fb->क्रमmat->cpp[0] * 8 ||
	    var->xres > fb->width || var->yres > fb->height ||
	    var->xres_भव > fb->width || var->yres_भव > fb->height) अणु
		drm_dbg_kms(dev, "fb requested width/height/bpp can't fit in current fb "
			  "request %dx%d-%d (virtual %dx%d) > %dx%d-%d\n",
			  var->xres, var->yres, var->bits_per_pixel,
			  var->xres_भव, var->yres_भव,
			  fb->width, fb->height, fb->क्रमmat->cpp[0] * 8);
		वापस -EINVAL;
	पूर्ण

	/*
	 * Workaround क्रम SDL 1.2, which is known to be setting all pixel क्रमmat
	 * fields values to zero in some हालs. We treat this situation as a
	 * kind of "use some reasonable autodetected values".
	 */
	अगर (!var->red.offset     && !var->green.offset    &&
	    !var->blue.offset    && !var->transp.offset   &&
	    !var->red.length     && !var->green.length    &&
	    !var->blue.length    && !var->transp.length   &&
	    !var->red.msb_right  && !var->green.msb_right &&
	    !var->blue.msb_right && !var->transp.msb_right) अणु
		drm_fb_helper_fill_pixel_fmt(var, fb->क्रमmat->depth);
	पूर्ण

	/*
	 * Likewise, bits_per_pixel should be rounded up to a supported value.
	 */
	var->bits_per_pixel = fb->क्रमmat->cpp[0] * 8;

	/*
	 * drm fbdev emulation करोesn't support changing the pixel क्रमmat at all,
	 * so reject all pixel क्रमmat changing requests.
	 */
	अगर (!drm_fb_pixel_क्रमmat_equal(var, &info->var)) अणु
		drm_dbg_kms(dev, "fbdev emulation doesn't support changing the pixel format\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_fb_helper_check_var);

/**
 * drm_fb_helper_set_par - implementation क्रम &fb_ops.fb_set_par
 * @info: fbdev रेजिस्टरed by the helper
 *
 * This will let fbcon करो the mode init and is called at initialization समय by
 * the fbdev core when रेजिस्टरing the driver, and later on through the hotplug
 * callback.
 */
पूर्णांक drm_fb_helper_set_par(काष्ठा fb_info *info)
अणु
	काष्ठा drm_fb_helper *fb_helper = info->par;
	काष्ठा fb_var_screeninfo *var = &info->var;
	bool क्रमce;

	अगर (oops_in_progress)
		वापस -EBUSY;

	अगर (var->pixघड़ी != 0) अणु
		drm_err(fb_helper->dev, "PIXEL CLOCK SET\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * Normally we want to make sure that a kms master takes precedence over
	 * fbdev, to aव्योम fbdev flickering and occasionally stealing the
	 * display status. But Xorg first sets the vt back to text mode using
	 * the KDSET IOCTL with KD_TEXT, and only after that drops the master
	 * status when निकासing.
	 *
	 * In the past this was caught by drm_fb_helper_lastबंद(), but on
	 * modern प्रणालीs where logind always keeps a drm fd खोलो to orchestrate
	 * the vt चयनing, this करोesn't work.
	 *
	 * To not अवरोध the userspace ABI we have this special हाल here, which
	 * is only used क्रम the above हाल. Everything अन्यथा uses the normal
	 * commit function, which ensures that we never steal the display from
	 * an active drm master.
	 */
	क्रमce = var->activate & FB_ACTIVATE_KD_TEXT;

	__drm_fb_helper_restore_fbdev_mode_unlocked(fb_helper, क्रमce);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_fb_helper_set_par);

अटल व्योम pan_set(काष्ठा drm_fb_helper *fb_helper, पूर्णांक x, पूर्णांक y)
अणु
	काष्ठा drm_mode_set *mode_set;

	mutex_lock(&fb_helper->client.modeset_mutex);
	drm_client_क्रम_each_modeset(mode_set, &fb_helper->client) अणु
		mode_set->x = x;
		mode_set->y = y;
	पूर्ण
	mutex_unlock(&fb_helper->client.modeset_mutex);
पूर्ण

अटल पूर्णांक pan_display_atomic(काष्ठा fb_var_screeninfo *var,
			      काष्ठा fb_info *info)
अणु
	काष्ठा drm_fb_helper *fb_helper = info->par;
	पूर्णांक ret;

	pan_set(fb_helper, var->xoffset, var->yoffset);

	ret = drm_client_modeset_commit_locked(&fb_helper->client);
	अगर (!ret) अणु
		info->var.xoffset = var->xoffset;
		info->var.yoffset = var->yoffset;
	पूर्ण अन्यथा
		pan_set(fb_helper, info->var.xoffset, info->var.yoffset);

	वापस ret;
पूर्ण

अटल पूर्णांक pan_display_legacy(काष्ठा fb_var_screeninfo *var,
			      काष्ठा fb_info *info)
अणु
	काष्ठा drm_fb_helper *fb_helper = info->par;
	काष्ठा drm_client_dev *client = &fb_helper->client;
	काष्ठा drm_mode_set *modeset;
	पूर्णांक ret = 0;

	mutex_lock(&client->modeset_mutex);
	drm_modeset_lock_all(fb_helper->dev);
	drm_client_क्रम_each_modeset(modeset, client) अणु
		modeset->x = var->xoffset;
		modeset->y = var->yoffset;

		अगर (modeset->num_connectors) अणु
			ret = drm_mode_set_config_पूर्णांकernal(modeset);
			अगर (!ret) अणु
				info->var.xoffset = var->xoffset;
				info->var.yoffset = var->yoffset;
			पूर्ण
		पूर्ण
	पूर्ण
	drm_modeset_unlock_all(fb_helper->dev);
	mutex_unlock(&client->modeset_mutex);

	वापस ret;
पूर्ण

/**
 * drm_fb_helper_pan_display - implementation क्रम &fb_ops.fb_pan_display
 * @var: updated screen inक्रमmation
 * @info: fbdev रेजिस्टरed by the helper
 */
पूर्णांक drm_fb_helper_pan_display(काष्ठा fb_var_screeninfo *var,
			      काष्ठा fb_info *info)
अणु
	काष्ठा drm_fb_helper *fb_helper = info->par;
	काष्ठा drm_device *dev = fb_helper->dev;
	पूर्णांक ret;

	अगर (oops_in_progress)
		वापस -EBUSY;

	mutex_lock(&fb_helper->lock);
	अगर (!drm_master_पूर्णांकernal_acquire(dev)) अणु
		ret = -EBUSY;
		जाओ unlock;
	पूर्ण

	अगर (drm_drv_uses_atomic_modeset(dev))
		ret = pan_display_atomic(var, info);
	अन्यथा
		ret = pan_display_legacy(var, info);

	drm_master_पूर्णांकernal_release(dev);
unlock:
	mutex_unlock(&fb_helper->lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_fb_helper_pan_display);

/*
 * Allocates the backing storage and sets up the fbdev info काष्ठाure through
 * the ->fb_probe callback.
 */
अटल पूर्णांक drm_fb_helper_single_fb_probe(काष्ठा drm_fb_helper *fb_helper,
					 पूर्णांक preferred_bpp)
अणु
	काष्ठा drm_client_dev *client = &fb_helper->client;
	काष्ठा drm_device *dev = fb_helper->dev;
	पूर्णांक ret = 0;
	पूर्णांक crtc_count = 0;
	काष्ठा drm_connector_list_iter conn_iter;
	काष्ठा drm_fb_helper_surface_size sizes;
	काष्ठा drm_connector *connector;
	काष्ठा drm_mode_set *mode_set;
	पूर्णांक best_depth = 0;

	स_रखो(&sizes, 0, माप(काष्ठा drm_fb_helper_surface_size));
	sizes.surface_depth = 24;
	sizes.surface_bpp = 32;
	sizes.fb_width = (u32)-1;
	sizes.fb_height = (u32)-1;

	/*
	 * If driver picks 8 or 16 by शेष use that क्रम both depth/bpp
	 * to begin with
	 */
	अगर (preferred_bpp != sizes.surface_bpp)
		sizes.surface_depth = sizes.surface_bpp = preferred_bpp;

	drm_connector_list_iter_begin(fb_helper->dev, &conn_iter);
	drm_client_क्रम_each_connector_iter(connector, &conn_iter) अणु
		काष्ठा drm_cmdline_mode *cmdline_mode;

		cmdline_mode = &connector->cmdline_mode;

		अगर (cmdline_mode->bpp_specअगरied) अणु
			चयन (cmdline_mode->bpp) अणु
			हाल 8:
				sizes.surface_depth = sizes.surface_bpp = 8;
				अवरोध;
			हाल 15:
				sizes.surface_depth = 15;
				sizes.surface_bpp = 16;
				अवरोध;
			हाल 16:
				sizes.surface_depth = sizes.surface_bpp = 16;
				अवरोध;
			हाल 24:
				sizes.surface_depth = sizes.surface_bpp = 24;
				अवरोध;
			हाल 32:
				sizes.surface_depth = 24;
				sizes.surface_bpp = 32;
				अवरोध;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण
	drm_connector_list_iter_end(&conn_iter);

	/*
	 * If we run पूर्णांकo a situation where, क्रम example, the primary plane
	 * supports RGBA5551 (16 bpp, depth 15) but not RGB565 (16 bpp, depth
	 * 16) we need to scale करोwn the depth of the sizes we request.
	 */
	mutex_lock(&client->modeset_mutex);
	drm_client_क्रम_each_modeset(mode_set, client) अणु
		काष्ठा drm_crtc *crtc = mode_set->crtc;
		काष्ठा drm_plane *plane = crtc->primary;
		पूर्णांक j;

		drm_dbg_kms(dev, "test CRTC %u primary plane\n", drm_crtc_index(crtc));

		क्रम (j = 0; j < plane->क्रमmat_count; j++) अणु
			स्थिर काष्ठा drm_क्रमmat_info *fmt;

			fmt = drm_क्रमmat_info(plane->क्रमmat_types[j]);

			/*
			 * Do not consider YUV or other complicated क्रमmats
			 * क्रम framebuffers. This means only legacy क्रमmats
			 * are supported (fmt->depth is a legacy field) but
			 * the framebuffer emulation can only deal with such
			 * क्रमmats, specअगरically RGB/BGA क्रमmats.
			 */
			अगर (fmt->depth == 0)
				जारी;

			/* We found a perfect fit, great */
			अगर (fmt->depth == sizes.surface_depth) अणु
				best_depth = fmt->depth;
				अवरोध;
			पूर्ण

			/* Skip depths above what we're looking क्रम */
			अगर (fmt->depth > sizes.surface_depth)
				जारी;

			/* Best depth found so far */
			अगर (fmt->depth > best_depth)
				best_depth = fmt->depth;
		पूर्ण
	पूर्ण
	अगर (sizes.surface_depth != best_depth && best_depth) अणु
		drm_info(dev, "requested bpp %d, scaled depth down to %d",
			 sizes.surface_bpp, best_depth);
		sizes.surface_depth = best_depth;
	पूर्ण

	/* first up get a count of crtcs now in use and new min/maxes width/heights */
	crtc_count = 0;
	drm_client_क्रम_each_modeset(mode_set, client) अणु
		काष्ठा drm_display_mode *desired_mode;
		पूर्णांक x, y, j;
		/* in हाल of tile group, are we the last tile vert or horiz?
		 * If no tile group you are always the last one both vertically
		 * and horizontally
		 */
		bool lastv = true, lasth = true;

		desired_mode = mode_set->mode;

		अगर (!desired_mode)
			जारी;

		crtc_count++;

		x = mode_set->x;
		y = mode_set->y;

		sizes.surface_width  = max_t(u32, desired_mode->hdisplay + x, sizes.surface_width);
		sizes.surface_height = max_t(u32, desired_mode->vdisplay + y, sizes.surface_height);

		क्रम (j = 0; j < mode_set->num_connectors; j++) अणु
			काष्ठा drm_connector *connector = mode_set->connectors[j];

			अगर (connector->has_tile &&
			    desired_mode->hdisplay == connector->tile_h_size &&
			    desired_mode->vdisplay == connector->tile_v_size) अणु
				lasth = (connector->tile_h_loc == (connector->num_h_tile - 1));
				lastv = (connector->tile_v_loc == (connector->num_v_tile - 1));
				/* cloning to multiple tiles is just crazy-talk, so: */
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (lasth)
			sizes.fb_width  = min_t(u32, desired_mode->hdisplay + x, sizes.fb_width);
		अगर (lastv)
			sizes.fb_height = min_t(u32, desired_mode->vdisplay + y, sizes.fb_height);
	पूर्ण
	mutex_unlock(&client->modeset_mutex);

	अगर (crtc_count == 0 || sizes.fb_width == -1 || sizes.fb_height == -1) अणु
		drm_info(dev, "Cannot find any crtc or sizes\n");

		/* First समय: disable all crtc's.. */
		अगर (!fb_helper->deferred_setup)
			drm_client_modeset_commit(client);
		वापस -EAGAIN;
	पूर्ण

	/* Handle our overallocation */
	sizes.surface_height *= drm_fbdev_overalloc;
	sizes.surface_height /= 100;

	/* push करोwn पूर्णांकo drivers */
	ret = (*fb_helper->funcs->fb_probe)(fb_helper, &sizes);
	अगर (ret < 0)
		वापस ret;

	म_नकल(fb_helper->fb->comm, "[fbcon]");
	वापस 0;
पूर्ण

अटल व्योम drm_fb_helper_fill_fix(काष्ठा fb_info *info, uपूर्णांक32_t pitch,
				   uपूर्णांक32_t depth)
अणु
	info->fix.type = FB_TYPE_PACKED_PIXELS;
	info->fix.visual = depth == 8 ? FB_VISUAL_PSEUDOCOLOR :
		FB_VISUAL_TRUECOLOR;
	info->fix.mmio_start = 0;
	info->fix.mmio_len = 0;
	info->fix.type_aux = 0;
	info->fix.xpanstep = 1; /* करोing it in hw */
	info->fix.ypanstep = 1; /* करोing it in hw */
	info->fix.ywrapstep = 0;
	info->fix.accel = FB_ACCEL_NONE;

	info->fix.line_length = pitch;
पूर्ण

अटल व्योम drm_fb_helper_fill_var(काष्ठा fb_info *info,
				   काष्ठा drm_fb_helper *fb_helper,
				   uपूर्णांक32_t fb_width, uपूर्णांक32_t fb_height)
अणु
	काष्ठा drm_framebuffer *fb = fb_helper->fb;

	WARN_ON((drm_क्रमmat_info_block_width(fb->क्रमmat, 0) > 1) ||
		(drm_क्रमmat_info_block_height(fb->क्रमmat, 0) > 1));
	info->pseuकरो_palette = fb_helper->pseuकरो_palette;
	info->var.xres_भव = fb->width;
	info->var.yres_भव = fb->height;
	info->var.bits_per_pixel = fb->क्रमmat->cpp[0] * 8;
	info->var.accel_flags = FB_ACCELF_TEXT;
	info->var.xoffset = 0;
	info->var.yoffset = 0;
	info->var.activate = FB_ACTIVATE_NOW;

	drm_fb_helper_fill_pixel_fmt(&info->var, fb->क्रमmat->depth);

	info->var.xres = fb_width;
	info->var.yres = fb_height;
पूर्ण

/**
 * drm_fb_helper_fill_info - initializes fbdev inक्रमmation
 * @info: fbdev instance to set up
 * @fb_helper: fb helper instance to use as ढाँचा
 * @sizes: describes fbdev size and scanout surface size
 *
 * Sets up the variable and fixed fbdev metainक्रमmation from the given fb helper
 * instance and the drm framebuffer allocated in &drm_fb_helper.fb.
 *
 * Drivers should call this (or their equivalent setup code) from their
 * &drm_fb_helper_funcs.fb_probe callback after having allocated the fbdev
 * backing storage framebuffer.
 */
व्योम drm_fb_helper_fill_info(काष्ठा fb_info *info,
			     काष्ठा drm_fb_helper *fb_helper,
			     काष्ठा drm_fb_helper_surface_size *sizes)
अणु
	काष्ठा drm_framebuffer *fb = fb_helper->fb;

	drm_fb_helper_fill_fix(info, fb->pitches[0], fb->क्रमmat->depth);
	drm_fb_helper_fill_var(info, fb_helper,
			       sizes->fb_width, sizes->fb_height);

	info->par = fb_helper;
	snम_लिखो(info->fix.id, माप(info->fix.id), "%sdrmfb",
		 fb_helper->dev->driver->name);

पूर्ण
EXPORT_SYMBOL(drm_fb_helper_fill_info);

/*
 * This is a continuation of drm_setup_crtcs() that sets up anything related
 * to the framebuffer. During initialization, drm_setup_crtcs() is called beक्रमe
 * the framebuffer has been allocated (fb_helper->fb and fb_helper->fbdev).
 * So, any setup that touches those fields needs to be करोne here instead of in
 * drm_setup_crtcs().
 */
अटल व्योम drm_setup_crtcs_fb(काष्ठा drm_fb_helper *fb_helper)
अणु
	काष्ठा drm_client_dev *client = &fb_helper->client;
	काष्ठा drm_connector_list_iter conn_iter;
	काष्ठा fb_info *info = fb_helper->fbdev;
	अचिन्हित पूर्णांक rotation, sw_rotations = 0;
	काष्ठा drm_connector *connector;
	काष्ठा drm_mode_set *modeset;

	mutex_lock(&client->modeset_mutex);
	drm_client_क्रम_each_modeset(modeset, client) अणु
		अगर (!modeset->num_connectors)
			जारी;

		modeset->fb = fb_helper->fb;

		अगर (drm_client_rotation(modeset, &rotation))
			/* Rotating in hardware, fbcon should not rotate */
			sw_rotations |= DRM_MODE_ROTATE_0;
		अन्यथा
			sw_rotations |= rotation;
	पूर्ण
	mutex_unlock(&client->modeset_mutex);

	drm_connector_list_iter_begin(fb_helper->dev, &conn_iter);
	drm_client_क्रम_each_connector_iter(connector, &conn_iter) अणु

		/* use first connected connector क्रम the physical dimensions */
		अगर (connector->status == connector_status_connected) अणु
			info->var.width = connector->display_info.width_mm;
			info->var.height = connector->display_info.height_mm;
			अवरोध;
		पूर्ण
	पूर्ण
	drm_connector_list_iter_end(&conn_iter);

	चयन (sw_rotations) अणु
	हाल DRM_MODE_ROTATE_0:
		info->fbcon_rotate_hपूर्णांक = FB_ROTATE_UR;
		अवरोध;
	हाल DRM_MODE_ROTATE_90:
		info->fbcon_rotate_hपूर्णांक = FB_ROTATE_CCW;
		अवरोध;
	हाल DRM_MODE_ROTATE_180:
		info->fbcon_rotate_hपूर्णांक = FB_ROTATE_UD;
		अवरोध;
	हाल DRM_MODE_ROTATE_270:
		info->fbcon_rotate_hपूर्णांक = FB_ROTATE_CW;
		अवरोध;
	शेष:
		/*
		 * Multiple bits are set / multiple rotations requested
		 * fbcon cannot handle separate rotation settings per
		 * output, so fallback to unrotated.
		 */
		info->fbcon_rotate_hपूर्णांक = FB_ROTATE_UR;
	पूर्ण
पूर्ण

/* Note: Drops fb_helper->lock beक्रमe वापसing. */
अटल पूर्णांक
__drm_fb_helper_initial_config_and_unlock(काष्ठा drm_fb_helper *fb_helper,
					  पूर्णांक bpp_sel)
अणु
	काष्ठा drm_device *dev = fb_helper->dev;
	काष्ठा fb_info *info;
	अचिन्हित पूर्णांक width, height;
	पूर्णांक ret;

	width = dev->mode_config.max_width;
	height = dev->mode_config.max_height;

	drm_client_modeset_probe(&fb_helper->client, width, height);
	ret = drm_fb_helper_single_fb_probe(fb_helper, bpp_sel);
	अगर (ret < 0) अणु
		अगर (ret == -EAGAIN) अणु
			fb_helper->preferred_bpp = bpp_sel;
			fb_helper->deferred_setup = true;
			ret = 0;
		पूर्ण
		mutex_unlock(&fb_helper->lock);

		वापस ret;
	पूर्ण
	drm_setup_crtcs_fb(fb_helper);

	fb_helper->deferred_setup = false;

	info = fb_helper->fbdev;
	info->var.pixघड़ी = 0;
	/* Shamelessly allow physical address leaking to userspace */
#अगर IS_ENABLED(CONFIG_DRM_FBDEV_LEAK_PHYS_SMEM)
	अगर (!drm_leak_fbdev_smem)
#पूर्ण_अगर
		/* करोn't leak any physical addresses to userspace */
		info->flags |= FBINFO_HIDE_SMEM_START;

	/* Need to drop locks to aव्योम recursive deadlock in
	 * रेजिस्टर_framebuffer. This is ok because the only thing left to करो is
	 * रेजिस्टर the fbdev emulation instance in kernel_fb_helper_list. */
	mutex_unlock(&fb_helper->lock);

	ret = रेजिस्टर_framebuffer(info);
	अगर (ret < 0)
		वापस ret;

	drm_info(dev, "fb%d: %s frame buffer device\n",
		 info->node, info->fix.id);

	mutex_lock(&kernel_fb_helper_lock);
	अगर (list_empty(&kernel_fb_helper_list))
		रेजिस्टर_sysrq_key('v', &sysrq_drm_fb_helper_restore_op);

	list_add(&fb_helper->kernel_fb_list, &kernel_fb_helper_list);
	mutex_unlock(&kernel_fb_helper_lock);

	वापस 0;
पूर्ण

/**
 * drm_fb_helper_initial_config - setup a sane initial connector configuration
 * @fb_helper: fb_helper device काष्ठा
 * @bpp_sel: bpp value to use क्रम the framebuffer configuration
 *
 * Scans the CRTCs and connectors and tries to put together an initial setup.
 * At the moment, this is a cloned configuration across all heads with
 * a new framebuffer object as the backing store.
 *
 * Note that this also रेजिस्टरs the fbdev and so allows userspace to call पूर्णांकo
 * the driver through the fbdev पूर्णांकerfaces.
 *
 * This function will call करोwn पूर्णांकo the &drm_fb_helper_funcs.fb_probe callback
 * to let the driver allocate and initialize the fbdev info काष्ठाure and the
 * drm framebuffer used to back the fbdev. drm_fb_helper_fill_info() is provided
 * as a helper to setup simple शेष values क्रम the fbdev info काष्ठाure.
 *
 * HANG DEBUGGING:
 *
 * When you have fbcon support built-in or alपढ़ोy loaded, this function will करो
 * a full modeset to setup the fbdev console. Due to locking misdesign in the
 * VT/fbdev subप्रणाली that entire modeset sequence has to be करोne जबतक holding
 * console_lock. Until console_unlock is called no dmesg lines will be sent out
 * to consoles, not even serial console. This means when your driver crashes,
 * you will see असलolutely nothing अन्यथा but a प्रणाली stuck in this function,
 * with no further output. Any kind of prपूर्णांकk() you place within your own driver
 * or in the drm core modeset code will also never show up.
 *
 * Standard debug practice is to run the fbcon setup without taking the
 * console_lock as a hack, to be able to see backtraces and crashes on the
 * serial line. This can be करोne by setting the fb.lockless_रेजिस्टर_fb=1 kernel
 * cmdline option.
 *
 * The other option is to just disable fbdev emulation since very likely the
 * first modeset from userspace will crash in the same way, and is even easier
 * to debug. This can be करोne by setting the drm_kms_helper.fbdev_emulation=0
 * kernel cmdline option.
 *
 * RETURNS:
 * Zero अगर everything went ok, nonzero otherwise.
 */
पूर्णांक drm_fb_helper_initial_config(काष्ठा drm_fb_helper *fb_helper, पूर्णांक bpp_sel)
अणु
	पूर्णांक ret;

	अगर (!drm_fbdev_emulation)
		वापस 0;

	mutex_lock(&fb_helper->lock);
	ret = __drm_fb_helper_initial_config_and_unlock(fb_helper, bpp_sel);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_fb_helper_initial_config);

/**
 * drm_fb_helper_hotplug_event - respond to a hotplug notअगरication by
 *                               probing all the outमाला_दो attached to the fb
 * @fb_helper: driver-allocated fbdev helper, can be शून्य
 *
 * Scan the connectors attached to the fb_helper and try to put together a
 * setup after notअगरication of a change in output configuration.
 *
 * Called at runसमय, takes the mode config locks to be able to check/change the
 * modeset configuration. Must be run from process context (which usually means
 * either the output polling work or a work item launched from the driver's
 * hotplug पूर्णांकerrupt).
 *
 * Note that drivers may call this even beक्रमe calling
 * drm_fb_helper_initial_config but only after drm_fb_helper_init. This allows
 * क्रम a race-मुक्त fbcon setup and will make sure that the fbdev emulation will
 * not miss any hotplug events.
 *
 * RETURNS:
 * 0 on success and a non-zero error code otherwise.
 */
पूर्णांक drm_fb_helper_hotplug_event(काष्ठा drm_fb_helper *fb_helper)
अणु
	पूर्णांक err = 0;

	अगर (!drm_fbdev_emulation || !fb_helper)
		वापस 0;

	mutex_lock(&fb_helper->lock);
	अगर (fb_helper->deferred_setup) अणु
		err = __drm_fb_helper_initial_config_and_unlock(fb_helper,
				fb_helper->preferred_bpp);
		वापस err;
	पूर्ण

	अगर (!fb_helper->fb || !drm_master_पूर्णांकernal_acquire(fb_helper->dev)) अणु
		fb_helper->delayed_hotplug = true;
		mutex_unlock(&fb_helper->lock);
		वापस err;
	पूर्ण

	drm_master_पूर्णांकernal_release(fb_helper->dev);

	drm_dbg_kms(fb_helper->dev, "\n");

	drm_client_modeset_probe(&fb_helper->client, fb_helper->fb->width, fb_helper->fb->height);
	drm_setup_crtcs_fb(fb_helper);
	mutex_unlock(&fb_helper->lock);

	drm_fb_helper_set_par(fb_helper->fbdev);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_fb_helper_hotplug_event);

/**
 * drm_fb_helper_lastबंद - DRM driver lastबंद helper क्रम fbdev emulation
 * @dev: DRM device
 *
 * This function can be used as the &drm_driver->lastबंद callback क्रम drivers
 * that only need to call drm_fb_helper_restore_fbdev_mode_unlocked().
 */
व्योम drm_fb_helper_lastबंद(काष्ठा drm_device *dev)
अणु
	drm_fb_helper_restore_fbdev_mode_unlocked(dev->fb_helper);
पूर्ण
EXPORT_SYMBOL(drm_fb_helper_lastबंद);

/**
 * drm_fb_helper_output_poll_changed - DRM mode config \.output_poll_changed
 *                                     helper क्रम fbdev emulation
 * @dev: DRM device
 *
 * This function can be used as the
 * &drm_mode_config_funcs.output_poll_changed callback क्रम drivers that only
 * need to call drm_fb_helper_hotplug_event().
 */
व्योम drm_fb_helper_output_poll_changed(काष्ठा drm_device *dev)
अणु
	drm_fb_helper_hotplug_event(dev->fb_helper);
पूर्ण
EXPORT_SYMBOL(drm_fb_helper_output_poll_changed);

/* @user: 1=userspace, 0=fbcon */
अटल पूर्णांक drm_fbdev_fb_खोलो(काष्ठा fb_info *info, पूर्णांक user)
अणु
	काष्ठा drm_fb_helper *fb_helper = info->par;

	/* No need to take a ref क्रम fbcon because it unbinds on unरेजिस्टर */
	अगर (user && !try_module_get(fb_helper->dev->driver->fops->owner))
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल पूर्णांक drm_fbdev_fb_release(काष्ठा fb_info *info, पूर्णांक user)
अणु
	काष्ठा drm_fb_helper *fb_helper = info->par;

	अगर (user)
		module_put(fb_helper->dev->driver->fops->owner);

	वापस 0;
पूर्ण

अटल व्योम drm_fbdev_cleanup(काष्ठा drm_fb_helper *fb_helper)
अणु
	काष्ठा fb_info *fbi = fb_helper->fbdev;
	व्योम *shaकरोw = शून्य;

	अगर (!fb_helper->dev)
		वापस;

	अगर (fbi) अणु
		अगर (fbi->fbdefio)
			fb_deferred_io_cleanup(fbi);
		अगर (drm_fbdev_use_shaकरोw_fb(fb_helper))
			shaकरोw = fbi->screen_buffer;
	पूर्ण

	drm_fb_helper_fini(fb_helper);

	अगर (shaकरोw)
		vमुक्त(shaकरोw);
	अन्यथा अगर (fb_helper->buffer)
		drm_client_buffer_vunmap(fb_helper->buffer);

	drm_client_framebuffer_delete(fb_helper->buffer);
पूर्ण

अटल व्योम drm_fbdev_release(काष्ठा drm_fb_helper *fb_helper)
अणु
	drm_fbdev_cleanup(fb_helper);
	drm_client_release(&fb_helper->client);
	kमुक्त(fb_helper);
पूर्ण

/*
 * fb_ops.fb_destroy is called by the last put_fb_info() call at the end of
 * unरेजिस्टर_framebuffer() or fb_release().
 */
अटल व्योम drm_fbdev_fb_destroy(काष्ठा fb_info *info)
अणु
	drm_fbdev_release(info->par);
पूर्ण

अटल पूर्णांक drm_fbdev_fb_mmap(काष्ठा fb_info *info, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा drm_fb_helper *fb_helper = info->par;

	अगर (fb_helper->dev->driver->gem_prime_mmap)
		वापस fb_helper->dev->driver->gem_prime_mmap(fb_helper->buffer->gem, vma);
	अन्यथा
		वापस -ENODEV;
पूर्ण

अटल bool drm_fbdev_use_iomem(काष्ठा fb_info *info)
अणु
	काष्ठा drm_fb_helper *fb_helper = info->par;
	काष्ठा drm_client_buffer *buffer = fb_helper->buffer;

	वापस !drm_fbdev_use_shaकरोw_fb(fb_helper) && buffer->map.is_iomem;
पूर्ण

अटल sमाप_प्रकार fb_पढ़ो_screen_base(काष्ठा fb_info *info, अक्षर __user *buf, माप_प्रकार count,
				   loff_t pos)
अणु
	स्थिर अक्षर __iomem *src = info->screen_base + pos;
	माप_प्रकार alloc_size = min_t(माप_प्रकार, count, PAGE_SIZE);
	sमाप_प्रकार ret = 0;
	पूर्णांक err = 0;
	अक्षर *पंचांगp;

	पंचांगp = kदो_स्मृति(alloc_size, GFP_KERNEL);
	अगर (!पंचांगp)
		वापस -ENOMEM;

	जबतक (count) अणु
		माप_प्रकार c = min_t(माप_प्रकार, count, alloc_size);

		स_नकल_fromio(पंचांगp, src, c);
		अगर (copy_to_user(buf, पंचांगp, c)) अणु
			err = -EFAULT;
			अवरोध;
		पूर्ण

		src += c;
		buf += c;
		ret += c;
		count -= c;
	पूर्ण

	kमुक्त(पंचांगp);

	वापस ret ? ret : err;
पूर्ण

अटल sमाप_प्रकार fb_पढ़ो_screen_buffer(काष्ठा fb_info *info, अक्षर __user *buf, माप_प्रकार count,
				     loff_t pos)
अणु
	स्थिर अक्षर *src = info->screen_buffer + pos;

	अगर (copy_to_user(buf, src, count))
		वापस -EFAULT;

	वापस count;
पूर्ण

अटल sमाप_प्रकार drm_fbdev_fb_पढ़ो(काष्ठा fb_info *info, अक्षर __user *buf,
				 माप_प्रकार count, loff_t *ppos)
अणु
	loff_t pos = *ppos;
	माप_प्रकार total_size;
	sमाप_प्रकार ret;

	अगर (info->screen_size)
		total_size = info->screen_size;
	अन्यथा
		total_size = info->fix.smem_len;

	अगर (pos >= total_size)
		वापस 0;
	अगर (count >= total_size)
		count = total_size;
	अगर (total_size - count < pos)
		count = total_size - pos;

	अगर (drm_fbdev_use_iomem(info))
		ret = fb_पढ़ो_screen_base(info, buf, count, pos);
	अन्यथा
		ret = fb_पढ़ो_screen_buffer(info, buf, count, pos);

	अगर (ret > 0)
		*ppos += ret;

	वापस ret;
पूर्ण

अटल sमाप_प्रकार fb_ग_लिखो_screen_base(काष्ठा fb_info *info, स्थिर अक्षर __user *buf, माप_प्रकार count,
				    loff_t pos)
अणु
	अक्षर __iomem *dst = info->screen_base + pos;
	माप_प्रकार alloc_size = min_t(माप_प्रकार, count, PAGE_SIZE);
	sमाप_प्रकार ret = 0;
	पूर्णांक err = 0;
	u8 *पंचांगp;

	पंचांगp = kदो_स्मृति(alloc_size, GFP_KERNEL);
	अगर (!पंचांगp)
		वापस -ENOMEM;

	जबतक (count) अणु
		माप_प्रकार c = min_t(माप_प्रकार, count, alloc_size);

		अगर (copy_from_user(पंचांगp, buf, c)) अणु
			err = -EFAULT;
			अवरोध;
		पूर्ण
		स_नकल_toio(dst, पंचांगp, c);

		dst += c;
		buf += c;
		ret += c;
		count -= c;
	पूर्ण

	kमुक्त(पंचांगp);

	वापस ret ? ret : err;
पूर्ण

अटल sमाप_प्रकार fb_ग_लिखो_screen_buffer(काष्ठा fb_info *info, स्थिर अक्षर __user *buf, माप_प्रकार count,
				      loff_t pos)
अणु
	अक्षर *dst = info->screen_buffer + pos;

	अगर (copy_from_user(dst, buf, count))
		वापस -EFAULT;

	वापस count;
पूर्ण

अटल sमाप_प्रकार drm_fbdev_fb_ग_लिखो(काष्ठा fb_info *info, स्थिर अक्षर __user *buf,
				  माप_प्रकार count, loff_t *ppos)
अणु
	loff_t pos = *ppos;
	माप_प्रकार total_size;
	sमाप_प्रकार ret;
	पूर्णांक err = 0;

	अगर (info->screen_size)
		total_size = info->screen_size;
	अन्यथा
		total_size = info->fix.smem_len;

	अगर (pos > total_size)
		वापस -EFBIG;
	अगर (count > total_size) अणु
		err = -EFBIG;
		count = total_size;
	पूर्ण
	अगर (total_size - count < pos) अणु
		अगर (!err)
			err = -ENOSPC;
		count = total_size - pos;
	पूर्ण

	/*
	 * Copy to framebuffer even अगर we alपढ़ोy logged an error. Emulates
	 * the behavior of the original fbdev implementation.
	 */
	अगर (drm_fbdev_use_iomem(info))
		ret = fb_ग_लिखो_screen_base(info, buf, count, pos);
	अन्यथा
		ret = fb_ग_लिखो_screen_buffer(info, buf, count, pos);

	अगर (ret > 0)
		*ppos += ret;

	अगर (ret > 0)
		drm_fb_helper_damage(info, 0, 0, info->var.xres_भव, info->var.yres_भव);

	वापस ret ? ret : err;
पूर्ण

अटल व्योम drm_fbdev_fb_fillrect(काष्ठा fb_info *info,
				  स्थिर काष्ठा fb_fillrect *rect)
अणु
	अगर (drm_fbdev_use_iomem(info))
		drm_fb_helper_cfb_fillrect(info, rect);
	अन्यथा
		drm_fb_helper_sys_fillrect(info, rect);
पूर्ण

अटल व्योम drm_fbdev_fb_copyarea(काष्ठा fb_info *info,
				  स्थिर काष्ठा fb_copyarea *area)
अणु
	अगर (drm_fbdev_use_iomem(info))
		drm_fb_helper_cfb_copyarea(info, area);
	अन्यथा
		drm_fb_helper_sys_copyarea(info, area);
पूर्ण

अटल व्योम drm_fbdev_fb_imageblit(काष्ठा fb_info *info,
				   स्थिर काष्ठा fb_image *image)
अणु
	अगर (drm_fbdev_use_iomem(info))
		drm_fb_helper_cfb_imageblit(info, image);
	अन्यथा
		drm_fb_helper_sys_imageblit(info, image);
पूर्ण

अटल स्थिर काष्ठा fb_ops drm_fbdev_fb_ops = अणु
	.owner		= THIS_MODULE,
	DRM_FB_HELPER_DEFAULT_OPS,
	.fb_खोलो	= drm_fbdev_fb_खोलो,
	.fb_release	= drm_fbdev_fb_release,
	.fb_destroy	= drm_fbdev_fb_destroy,
	.fb_mmap	= drm_fbdev_fb_mmap,
	.fb_पढ़ो	= drm_fbdev_fb_पढ़ो,
	.fb_ग_लिखो	= drm_fbdev_fb_ग_लिखो,
	.fb_fillrect	= drm_fbdev_fb_fillrect,
	.fb_copyarea	= drm_fbdev_fb_copyarea,
	.fb_imageblit	= drm_fbdev_fb_imageblit,
पूर्ण;

अटल काष्ठा fb_deferred_io drm_fbdev_defio = अणु
	.delay		= HZ / 20,
	.deferred_io	= drm_fb_helper_deferred_io,
पूर्ण;

/*
 * This function uses the client API to create a framebuffer backed by a dumb buffer.
 *
 * The _sys_ versions are used क्रम &fb_ops.fb_पढ़ो, fb_ग_लिखो, fb_fillrect,
 * fb_copyarea, fb_imageblit.
 */
अटल पूर्णांक drm_fb_helper_generic_probe(काष्ठा drm_fb_helper *fb_helper,
				       काष्ठा drm_fb_helper_surface_size *sizes)
अणु
	काष्ठा drm_client_dev *client = &fb_helper->client;
	काष्ठा drm_device *dev = fb_helper->dev;
	काष्ठा drm_client_buffer *buffer;
	काष्ठा drm_framebuffer *fb;
	काष्ठा fb_info *fbi;
	u32 क्रमmat;
	काष्ठा dma_buf_map map;
	पूर्णांक ret;

	drm_dbg_kms(dev, "surface width(%d), height(%d) and bpp(%d)\n",
		    sizes->surface_width, sizes->surface_height,
		    sizes->surface_bpp);

	क्रमmat = drm_mode_legacy_fb_क्रमmat(sizes->surface_bpp, sizes->surface_depth);
	buffer = drm_client_framebuffer_create(client, sizes->surface_width,
					       sizes->surface_height, क्रमmat);
	अगर (IS_ERR(buffer))
		वापस PTR_ERR(buffer);

	fb_helper->buffer = buffer;
	fb_helper->fb = buffer->fb;
	fb = buffer->fb;

	fbi = drm_fb_helper_alloc_fbi(fb_helper);
	अगर (IS_ERR(fbi))
		वापस PTR_ERR(fbi);

	fbi->fbops = &drm_fbdev_fb_ops;
	fbi->screen_size = fb->height * fb->pitches[0];
	fbi->fix.smem_len = fbi->screen_size;

	drm_fb_helper_fill_info(fbi, fb_helper, sizes);

	अगर (drm_fbdev_use_shaकरोw_fb(fb_helper)) अणु
		fbi->screen_buffer = vzalloc(fbi->screen_size);
		अगर (!fbi->screen_buffer)
			वापस -ENOMEM;

		fbi->fbdefio = &drm_fbdev_defio;

		fb_deferred_io_init(fbi);
	पूर्ण अन्यथा अणु
		/* buffer is mapped क्रम HW framebuffer */
		ret = drm_client_buffer_vmap(fb_helper->buffer, &map);
		अगर (ret)
			वापस ret;
		अगर (map.is_iomem)
			fbi->screen_base = map.vaddr_iomem;
		अन्यथा
			fbi->screen_buffer = map.vaddr;

		/*
		 * Shamelessly leak the physical address to user-space. As
		 * page_to_phys() is undefined क्रम I/O memory, warn in this
		 * हाल.
		 */
#अगर IS_ENABLED(CONFIG_DRM_FBDEV_LEAK_PHYS_SMEM)
		अगर (drm_leak_fbdev_smem && fbi->fix.smem_start == 0 &&
		    !drm_WARN_ON_ONCE(dev, map.is_iomem))
			fbi->fix.smem_start =
				page_to_phys(virt_to_page(fbi->screen_buffer));
#पूर्ण_अगर
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_fb_helper_funcs drm_fb_helper_generic_funcs = अणु
	.fb_probe = drm_fb_helper_generic_probe,
पूर्ण;

अटल व्योम drm_fbdev_client_unरेजिस्टर(काष्ठा drm_client_dev *client)
अणु
	काष्ठा drm_fb_helper *fb_helper = drm_fb_helper_from_client(client);

	अगर (fb_helper->fbdev)
		/* drm_fbdev_fb_destroy() takes care of cleanup */
		drm_fb_helper_unरेजिस्टर_fbi(fb_helper);
	अन्यथा
		drm_fbdev_release(fb_helper);
पूर्ण

अटल पूर्णांक drm_fbdev_client_restore(काष्ठा drm_client_dev *client)
अणु
	drm_fb_helper_lastबंद(client->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक drm_fbdev_client_hotplug(काष्ठा drm_client_dev *client)
अणु
	काष्ठा drm_fb_helper *fb_helper = drm_fb_helper_from_client(client);
	काष्ठा drm_device *dev = client->dev;
	पूर्णांक ret;

	/* Setup is not retried अगर it has failed */
	अगर (!fb_helper->dev && fb_helper->funcs)
		वापस 0;

	अगर (dev->fb_helper)
		वापस drm_fb_helper_hotplug_event(dev->fb_helper);

	अगर (!dev->mode_config.num_connector) अणु
		drm_dbg_kms(dev, "No connectors found, will not create framebuffer!\n");
		वापस 0;
	पूर्ण

	drm_fb_helper_prepare(dev, fb_helper, &drm_fb_helper_generic_funcs);

	ret = drm_fb_helper_init(dev, fb_helper);
	अगर (ret)
		जाओ err;

	अगर (!drm_drv_uses_atomic_modeset(dev))
		drm_helper_disable_unused_functions(dev);

	ret = drm_fb_helper_initial_config(fb_helper, fb_helper->preferred_bpp);
	अगर (ret)
		जाओ err_cleanup;

	वापस 0;

err_cleanup:
	drm_fbdev_cleanup(fb_helper);
err:
	fb_helper->dev = शून्य;
	fb_helper->fbdev = शून्य;

	drm_err(dev, "fbdev: Failed to setup generic emulation (ret=%d)\n", ret);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा drm_client_funcs drm_fbdev_client_funcs = अणु
	.owner		= THIS_MODULE,
	.unरेजिस्टर	= drm_fbdev_client_unरेजिस्टर,
	.restore	= drm_fbdev_client_restore,
	.hotplug	= drm_fbdev_client_hotplug,
पूर्ण;

/**
 * drm_fbdev_generic_setup() - Setup generic fbdev emulation
 * @dev: DRM device
 * @preferred_bpp: Preferred bits per pixel क्रम the device.
 *                 @dev->mode_config.preferred_depth is used अगर this is zero.
 *
 * This function sets up generic fbdev emulation क्रम drivers that supports
 * dumb buffers with a भव address and that can be mmap'ed.
 * drm_fbdev_generic_setup() shall be called after the DRM driver रेजिस्टरed
 * the new DRM device with drm_dev_रेजिस्टर().
 *
 * Restore, hotplug events and tearकरोwn are all taken care of. Drivers that करो
 * suspend/resume need to call drm_fb_helper_set_suspend_unlocked() themselves.
 * Simple drivers might use drm_mode_config_helper_suspend().
 *
 * Drivers that set the dirty callback on their framebuffer will get a shaकरोw
 * fbdev buffer that is blitted onto the real buffer. This is करोne in order to
 * make deferred I/O work with all kinds of buffers. A shaकरोw buffer can be
 * requested explicitly by setting काष्ठा drm_mode_config.prefer_shaकरोw or
 * काष्ठा drm_mode_config.prefer_shaकरोw_fbdev to true beक्रमehand. This is
 * required to use generic fbdev emulation with SHMEM helpers.
 *
 * This function is safe to call even when there are no connectors present.
 * Setup will be retried on the next hotplug event.
 *
 * The fbdev is destroyed by drm_dev_unरेजिस्टर().
 */
व्योम drm_fbdev_generic_setup(काष्ठा drm_device *dev,
			     अचिन्हित पूर्णांक preferred_bpp)
अणु
	काष्ठा drm_fb_helper *fb_helper;
	पूर्णांक ret;

	drm_WARN(dev, !dev->रेजिस्टरed, "Device has not been registered.\n");
	drm_WARN(dev, dev->fb_helper, "fb_helper is already set!\n");

	अगर (!drm_fbdev_emulation)
		वापस;

	fb_helper = kzalloc(माप(*fb_helper), GFP_KERNEL);
	अगर (!fb_helper) अणु
		drm_err(dev, "Failed to allocate fb_helper\n");
		वापस;
	पूर्ण

	ret = drm_client_init(dev, &fb_helper->client, "fbdev", &drm_fbdev_client_funcs);
	अगर (ret) अणु
		kमुक्त(fb_helper);
		drm_err(dev, "Failed to register client: %d\n", ret);
		वापस;
	पूर्ण

	/*
	 * FIXME: This mixes up depth with bpp, which results in a glorious
	 * mess, resulting in some drivers picking wrong fbdev शेषs and
	 * others wrong preferred_depth शेषs.
	 */
	अगर (!preferred_bpp)
		preferred_bpp = dev->mode_config.preferred_depth;
	अगर (!preferred_bpp)
		preferred_bpp = 32;
	fb_helper->preferred_bpp = preferred_bpp;

	ret = drm_fbdev_client_hotplug(&fb_helper->client);
	अगर (ret)
		drm_dbg_kms(dev, "client hotplug ret=%d\n", ret);

	drm_client_रेजिस्टर(&fb_helper->client);
पूर्ण
EXPORT_SYMBOL(drm_fbdev_generic_setup);
