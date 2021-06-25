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
#अगर_अघोषित DRM_FB_HELPER_H
#घोषणा DRM_FB_HELPER_H

काष्ठा drm_fb_helper;

#समावेश <drm/drm_client.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_device.h>
#समावेश <linux/kgdb.h>
#समावेश <linux/vgaarb.h>

क्रमागत mode_set_atomic अणु
	LEAVE_ATOMIC_MODE_SET,
	ENTER_ATOMIC_MODE_SET,
पूर्ण;

/**
 * काष्ठा drm_fb_helper_surface_size - describes fbdev size and scanout surface size
 * @fb_width: fbdev width
 * @fb_height: fbdev height
 * @surface_width: scanout buffer width
 * @surface_height: scanout buffer height
 * @surface_bpp: scanout buffer bpp
 * @surface_depth: scanout buffer depth
 *
 * Note that the scanout surface width/height may be larger than the fbdev
 * width/height.  In हाल of multiple displays, the scanout surface is sized
 * according to the largest width/height (so it is large enough क्रम all CRTCs
 * to scanout).  But the fbdev width/height is sized to the minimum width/
 * height of all the displays.  This ensures that fbcon fits on the smallest
 * of the attached displays. fb_width/fb_height is used by
 * drm_fb_helper_fill_info() to fill out the &fb_info.var काष्ठाure.
 */
काष्ठा drm_fb_helper_surface_size अणु
	u32 fb_width;
	u32 fb_height;
	u32 surface_width;
	u32 surface_height;
	u32 surface_bpp;
	u32 surface_depth;
पूर्ण;

/**
 * काष्ठा drm_fb_helper_funcs - driver callbacks क्रम the fbdev emulation library
 *
 * Driver callbacks used by the fbdev emulation helper library.
 */
काष्ठा drm_fb_helper_funcs अणु
	/**
	 * @fb_probe:
	 *
	 * Driver callback to allocate and initialize the fbdev info काष्ठाure.
	 * Furthermore it also needs to allocate the DRM framebuffer used to
	 * back the fbdev.
	 *
	 * This callback is mandatory.
	 *
	 * RETURNS:
	 *
	 * The driver should वापस 0 on success and a negative error code on
	 * failure.
	 */
	पूर्णांक (*fb_probe)(काष्ठा drm_fb_helper *helper,
			काष्ठा drm_fb_helper_surface_size *sizes);
पूर्ण;

/**
 * काष्ठा drm_fb_helper - मुख्य काष्ठाure to emulate fbdev on top of KMS
 * @fb: Scanout framebuffer object
 * @dev: DRM device
 * @funcs: driver callbacks क्रम fb helper
 * @fbdev: emulated fbdev device info काष्ठा
 * @pseuकरो_palette: fake palette of 16 colors
 * @damage_clip: clip rectangle used with deferred_io to accumulate damage to
 *                the screen buffer
 * @damage_lock: spinlock protecting @damage_clip
 * @damage_work: worker used to flush the framebuffer
 * @resume_work: worker used during resume अगर the console lock is alपढ़ोy taken
 *
 * This is the मुख्य काष्ठाure used by the fbdev helpers. Drivers supporting
 * fbdev emulation should embedded this पूर्णांकo their overall driver काष्ठाure.
 * Drivers must also fill out a &काष्ठा drm_fb_helper_funcs with a few
 * operations.
 */
काष्ठा drm_fb_helper अणु
	/**
	 * @client:
	 *
	 * DRM client used by the generic fbdev emulation.
	 */
	काष्ठा drm_client_dev client;

	/**
	 * @buffer:
	 *
	 * Framebuffer used by the generic fbdev emulation.
	 */
	काष्ठा drm_client_buffer *buffer;

	काष्ठा drm_framebuffer *fb;
	काष्ठा drm_device *dev;
	स्थिर काष्ठा drm_fb_helper_funcs *funcs;
	काष्ठा fb_info *fbdev;
	u32 pseuकरो_palette[17];
	काष्ठा drm_clip_rect damage_clip;
	spinlock_t damage_lock;
	काष्ठा work_काष्ठा damage_work;
	काष्ठा work_काष्ठा resume_work;

	/**
	 * @lock:
	 *
	 * Top-level FBDEV helper lock. This protects all पूर्णांकernal data
	 * काष्ठाures and lists, such as @connector_info and @crtc_info.
	 *
	 * FIXME: fbdev emulation locking is a mess and दीर्घ term we want to
	 * protect all helper पूर्णांकernal state with this lock as well as reduce
	 * core KMS locking as much as possible.
	 */
	काष्ठा mutex lock;

	/**
	 * @kernel_fb_list:
	 *
	 * Entry on the global kernel_fb_helper_list, used क्रम kgdb entry/निकास.
	 */
	काष्ठा list_head kernel_fb_list;

	/**
	 * @delayed_hotplug:
	 *
	 * A hotplug was received जबतक fbdev wasn't in control of the DRM
	 * device, i.e. another KMS master was active. The output configuration
	 * needs to be reprobe when fbdev is in control again.
	 */
	bool delayed_hotplug;

	/**
	 * @deferred_setup:
	 *
	 * If no outमाला_दो are connected (disconnected or unknown) the FB helper
	 * code will defer setup until at least one of the outमाला_दो shows up.
	 * This field keeps track of the status so that setup can be retried
	 * at every hotplug event until it succeeds eventually.
	 *
	 * Protected by @lock.
	 */
	bool deferred_setup;

	/**
	 * @preferred_bpp:
	 *
	 * Temporary storage क्रम the driver's preferred BPP setting passed to
	 * FB helper initialization. This needs to be tracked so that deferred
	 * FB helper setup can pass this on.
	 *
	 * See also: @deferred_setup
	 */
	पूर्णांक preferred_bpp;
पूर्ण;

अटल अंतरभूत काष्ठा drm_fb_helper *
drm_fb_helper_from_client(काष्ठा drm_client_dev *client)
अणु
	वापस container_of(client, काष्ठा drm_fb_helper, client);
पूर्ण

/**
 * define DRM_FB_HELPER_DEFAULT_OPS - helper define क्रम drm drivers
 *
 * Helper define to रेजिस्टर शेष implementations of drm_fb_helper
 * functions. To be used in काष्ठा fb_ops of drm drivers.
 */
#घोषणा DRM_FB_HELPER_DEFAULT_OPS \
	.fb_check_var	= drm_fb_helper_check_var, \
	.fb_set_par	= drm_fb_helper_set_par, \
	.fb_setcmap	= drm_fb_helper_setcmap, \
	.fb_blank	= drm_fb_helper_blank, \
	.fb_pan_display	= drm_fb_helper_pan_display, \
	.fb_debug_enter = drm_fb_helper_debug_enter, \
	.fb_debug_leave = drm_fb_helper_debug_leave, \
	.fb_ioctl	= drm_fb_helper_ioctl

#अगर_घोषित CONFIG_DRM_FBDEV_EMULATION
व्योम drm_fb_helper_prepare(काष्ठा drm_device *dev, काष्ठा drm_fb_helper *helper,
			   स्थिर काष्ठा drm_fb_helper_funcs *funcs);
पूर्णांक drm_fb_helper_init(काष्ठा drm_device *dev, काष्ठा drm_fb_helper *helper);
व्योम drm_fb_helper_fini(काष्ठा drm_fb_helper *helper);
पूर्णांक drm_fb_helper_blank(पूर्णांक blank, काष्ठा fb_info *info);
पूर्णांक drm_fb_helper_pan_display(काष्ठा fb_var_screeninfo *var,
			      काष्ठा fb_info *info);
पूर्णांक drm_fb_helper_set_par(काष्ठा fb_info *info);
पूर्णांक drm_fb_helper_check_var(काष्ठा fb_var_screeninfo *var,
			    काष्ठा fb_info *info);

पूर्णांक drm_fb_helper_restore_fbdev_mode_unlocked(काष्ठा drm_fb_helper *fb_helper);

काष्ठा fb_info *drm_fb_helper_alloc_fbi(काष्ठा drm_fb_helper *fb_helper);
व्योम drm_fb_helper_unरेजिस्टर_fbi(काष्ठा drm_fb_helper *fb_helper);
व्योम drm_fb_helper_fill_info(काष्ठा fb_info *info,
			     काष्ठा drm_fb_helper *fb_helper,
			     काष्ठा drm_fb_helper_surface_size *sizes);

व्योम drm_fb_helper_deferred_io(काष्ठा fb_info *info,
			       काष्ठा list_head *pagelist);

sमाप_प्रकार drm_fb_helper_sys_पढ़ो(काष्ठा fb_info *info, अक्षर __user *buf,
			       माप_प्रकार count, loff_t *ppos);
sमाप_प्रकार drm_fb_helper_sys_ग_लिखो(काष्ठा fb_info *info, स्थिर अक्षर __user *buf,
				माप_प्रकार count, loff_t *ppos);

व्योम drm_fb_helper_sys_fillrect(काष्ठा fb_info *info,
				स्थिर काष्ठा fb_fillrect *rect);
व्योम drm_fb_helper_sys_copyarea(काष्ठा fb_info *info,
				स्थिर काष्ठा fb_copyarea *area);
व्योम drm_fb_helper_sys_imageblit(काष्ठा fb_info *info,
				 स्थिर काष्ठा fb_image *image);

व्योम drm_fb_helper_cfb_fillrect(काष्ठा fb_info *info,
				स्थिर काष्ठा fb_fillrect *rect);
व्योम drm_fb_helper_cfb_copyarea(काष्ठा fb_info *info,
				स्थिर काष्ठा fb_copyarea *area);
व्योम drm_fb_helper_cfb_imageblit(काष्ठा fb_info *info,
				 स्थिर काष्ठा fb_image *image);

व्योम drm_fb_helper_set_suspend(काष्ठा drm_fb_helper *fb_helper, bool suspend);
व्योम drm_fb_helper_set_suspend_unlocked(काष्ठा drm_fb_helper *fb_helper,
					bool suspend);

पूर्णांक drm_fb_helper_setcmap(काष्ठा fb_cmap *cmap, काष्ठा fb_info *info);

पूर्णांक drm_fb_helper_ioctl(काष्ठा fb_info *info, अचिन्हित पूर्णांक cmd,
			अचिन्हित दीर्घ arg);

पूर्णांक drm_fb_helper_hotplug_event(काष्ठा drm_fb_helper *fb_helper);
पूर्णांक drm_fb_helper_initial_config(काष्ठा drm_fb_helper *fb_helper, पूर्णांक bpp_sel);
पूर्णांक drm_fb_helper_debug_enter(काष्ठा fb_info *info);
पूर्णांक drm_fb_helper_debug_leave(काष्ठा fb_info *info);

व्योम drm_fb_helper_lastबंद(काष्ठा drm_device *dev);
व्योम drm_fb_helper_output_poll_changed(काष्ठा drm_device *dev);

व्योम drm_fbdev_generic_setup(काष्ठा drm_device *dev,
			     अचिन्हित पूर्णांक preferred_bpp);
#अन्यथा
अटल अंतरभूत व्योम drm_fb_helper_prepare(काष्ठा drm_device *dev,
					काष्ठा drm_fb_helper *helper,
					स्थिर काष्ठा drm_fb_helper_funcs *funcs)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक drm_fb_helper_init(काष्ठा drm_device *dev,
		       काष्ठा drm_fb_helper *helper)
अणु
	/* So drivers can use it to मुक्त the काष्ठा */
	helper->dev = dev;
	dev->fb_helper = helper;

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम drm_fb_helper_fini(काष्ठा drm_fb_helper *helper)
अणु
	अगर (helper && helper->dev)
		helper->dev->fb_helper = शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक drm_fb_helper_blank(पूर्णांक blank, काष्ठा fb_info *info)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक drm_fb_helper_pan_display(काष्ठा fb_var_screeninfo *var,
					    काष्ठा fb_info *info)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक drm_fb_helper_set_par(काष्ठा fb_info *info)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक drm_fb_helper_check_var(काष्ठा fb_var_screeninfo *var,
					  काष्ठा fb_info *info)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
drm_fb_helper_restore_fbdev_mode_unlocked(काष्ठा drm_fb_helper *fb_helper)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा fb_info *
drm_fb_helper_alloc_fbi(काष्ठा drm_fb_helper *fb_helper)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम drm_fb_helper_unरेजिस्टर_fbi(काष्ठा drm_fb_helper *fb_helper)
अणु
पूर्ण

अटल अंतरभूत व्योम
drm_fb_helper_fill_info(काष्ठा fb_info *info,
			काष्ठा drm_fb_helper *fb_helper,
			काष्ठा drm_fb_helper_surface_size *sizes)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक drm_fb_helper_setcmap(काष्ठा fb_cmap *cmap,
					काष्ठा fb_info *info)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक drm_fb_helper_ioctl(काष्ठा fb_info *info, अचिन्हित पूर्णांक cmd,
				      अचिन्हित दीर्घ arg)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम drm_fb_helper_deferred_io(काष्ठा fb_info *info,
					     काष्ठा list_head *pagelist)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक drm_fb_helper_defio_init(काष्ठा drm_fb_helper *fb_helper)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत sमाप_प्रकार drm_fb_helper_sys_पढ़ो(काष्ठा fb_info *info,
					     अक्षर __user *buf, माप_प्रकार count,
					     loff_t *ppos)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत sमाप_प्रकार drm_fb_helper_sys_ग_लिखो(काष्ठा fb_info *info,
					      स्थिर अक्षर __user *buf,
					      माप_प्रकार count, loff_t *ppos)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत व्योम drm_fb_helper_sys_fillrect(काष्ठा fb_info *info,
					      स्थिर काष्ठा fb_fillrect *rect)
अणु
पूर्ण

अटल अंतरभूत व्योम drm_fb_helper_sys_copyarea(काष्ठा fb_info *info,
					      स्थिर काष्ठा fb_copyarea *area)
अणु
पूर्ण

अटल अंतरभूत व्योम drm_fb_helper_sys_imageblit(काष्ठा fb_info *info,
					       स्थिर काष्ठा fb_image *image)
अणु
पूर्ण

अटल अंतरभूत व्योम drm_fb_helper_cfb_fillrect(काष्ठा fb_info *info,
					      स्थिर काष्ठा fb_fillrect *rect)
अणु
पूर्ण

अटल अंतरभूत व्योम drm_fb_helper_cfb_copyarea(काष्ठा fb_info *info,
					      स्थिर काष्ठा fb_copyarea *area)
अणु
पूर्ण

अटल अंतरभूत व्योम drm_fb_helper_cfb_imageblit(काष्ठा fb_info *info,
					       स्थिर काष्ठा fb_image *image)
अणु
पूर्ण

अटल अंतरभूत व्योम drm_fb_helper_set_suspend(काष्ठा drm_fb_helper *fb_helper,
					     bool suspend)
अणु
पूर्ण

अटल अंतरभूत व्योम
drm_fb_helper_set_suspend_unlocked(काष्ठा drm_fb_helper *fb_helper, bool suspend)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक drm_fb_helper_hotplug_event(काष्ठा drm_fb_helper *fb_helper)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक drm_fb_helper_initial_config(काष्ठा drm_fb_helper *fb_helper,
					       पूर्णांक bpp_sel)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक drm_fb_helper_debug_enter(काष्ठा fb_info *info)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक drm_fb_helper_debug_leave(काष्ठा fb_info *info)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम drm_fb_helper_lastबंद(काष्ठा drm_device *dev)
अणु
पूर्ण

अटल अंतरभूत व्योम drm_fb_helper_output_poll_changed(काष्ठा drm_device *dev)
अणु
पूर्ण

अटल अंतरभूत व्योम
drm_fbdev_generic_setup(काष्ठा drm_device *dev, अचिन्हित पूर्णांक preferred_bpp)
अणु
पूर्ण

#पूर्ण_अगर

/**
 * drm_fb_helper_हटाओ_conflicting_framebuffers - हटाओ firmware-configured framebuffers
 * @a: memory range, users of which are to be हटाओd
 * @name: requesting driver name
 * @primary: also kick vga16fb अगर present
 *
 * This function हटाओs framebuffer devices (initialized by firmware/bootloader)
 * which use memory range described by @a. If @a is शून्य all such devices are
 * हटाओd.
 */
अटल अंतरभूत पूर्णांक
drm_fb_helper_हटाओ_conflicting_framebuffers(काष्ठा apertures_काष्ठा *a,
					      स्थिर अक्षर *name, bool primary)
अणु
#अगर IS_REACHABLE(CONFIG_FB)
	वापस हटाओ_conflicting_framebuffers(a, name, primary);
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

/**
 * drm_fb_helper_हटाओ_conflicting_pci_framebuffers - हटाओ firmware-configured framebuffers क्रम PCI devices
 * @pdev: PCI device
 * @name: requesting driver name
 *
 * This function हटाओs framebuffer devices (eg. initialized by firmware)
 * using memory range configured क्रम any of @pdev's memory bars.
 *
 * The function assumes that PCI device with shaकरोwed ROM drives a primary
 * display and so kicks out vga16fb.
 */
अटल अंतरभूत पूर्णांक
drm_fb_helper_हटाओ_conflicting_pci_framebuffers(काष्ठा pci_dev *pdev,
						  स्थिर अक्षर *name)
अणु
	पूर्णांक ret = 0;

	/*
	 * WARNING: Apparently we must kick fbdev drivers beक्रमe vgacon,
	 * otherwise the vga fbdev driver falls over.
	 */
#अगर IS_REACHABLE(CONFIG_FB)
	ret = हटाओ_conflicting_pci_framebuffers(pdev, name);
#पूर्ण_अगर
	अगर (ret == 0)
		ret = vga_हटाओ_vgacon(pdev);
	वापस ret;
पूर्ण

#पूर्ण_अगर
