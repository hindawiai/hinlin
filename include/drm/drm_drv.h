<शैली गुरु>
/*
 * Copyright 1999 Precision Insight, Inc., Cedar Park, Texas.
 * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, Calअगरornia.
 * Copyright (c) 2009-2010, Code Aurora Forum.
 * Copyright 2016 Intel Corp.
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
 * VA LINUX SYSTEMS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#अगर_अघोषित _DRM_DRV_H_
#घोषणा _DRM_DRV_H_

#समावेश <linux/list.h>
#समावेश <linux/irqवापस.h>

#समावेश <drm/drm_device.h>

काष्ठा drm_file;
काष्ठा drm_gem_object;
काष्ठा drm_master;
काष्ठा drm_minor;
काष्ठा dma_buf;
काष्ठा dma_buf_attachment;
काष्ठा drm_display_mode;
काष्ठा drm_mode_create_dumb;
काष्ठा drm_prपूर्णांकer;
काष्ठा sg_table;

/**
 * क्रमागत drm_driver_feature - feature flags
 *
 * See &drm_driver.driver_features, drm_device.driver_features and
 * drm_core_check_feature().
 */
क्रमागत drm_driver_feature अणु
	/**
	 * @DRIVER_GEM:
	 *
	 * Driver use the GEM memory manager. This should be set क्रम all modern
	 * drivers.
	 */
	DRIVER_GEM			= BIT(0),
	/**
	 * @DRIVER_MODESET:
	 *
	 * Driver supports mode setting पूर्णांकerfaces (KMS).
	 */
	DRIVER_MODESET			= BIT(1),
	/**
	 * @DRIVER_RENDER:
	 *
	 * Driver supports dedicated render nodes. See also the :ref:`section on
	 * render nodes <drm_render_node>` क्रम details.
	 */
	DRIVER_RENDER			= BIT(3),
	/**
	 * @DRIVER_ATOMIC:
	 *
	 * Driver supports the full atomic modesetting userspace API. Drivers
	 * which only use atomic पूर्णांकernally, but करो not support the full
	 * userspace API (e.g. not all properties converted to atomic, or
	 * multi-plane updates are not guaranteed to be tear-मुक्त) should not
	 * set this flag.
	 */
	DRIVER_ATOMIC			= BIT(4),
	/**
	 * @DRIVER_SYNCOBJ:
	 *
	 * Driver supports &drm_syncobj क्रम explicit synchronization of command
	 * submission.
	 */
	DRIVER_SYNCOBJ                  = BIT(5),
	/**
	 * @DRIVER_SYNCOBJ_TIMELINE:
	 *
	 * Driver supports the समयline flavor of &drm_syncobj क्रम explicit
	 * synchronization of command submission.
	 */
	DRIVER_SYNCOBJ_TIMELINE         = BIT(6),

	/* IMPORTANT: Below are all the legacy flags, add new ones above. */

	/**
	 * @DRIVER_USE_AGP:
	 *
	 * Set up DRM AGP support, see drm_agp_init(), the DRM core will manage
	 * AGP resources. New drivers करोn't need this.
	 */
	DRIVER_USE_AGP			= BIT(25),
	/**
	 * @DRIVER_LEGACY:
	 *
	 * Denote a legacy driver using shaकरोw attach. Do not use.
	 */
	DRIVER_LEGACY			= BIT(26),
	/**
	 * @DRIVER_PCI_DMA:
	 *
	 * Driver is capable of PCI DMA, mapping of PCI DMA buffers to userspace
	 * will be enabled. Only क्रम legacy drivers. Do not use.
	 */
	DRIVER_PCI_DMA			= BIT(27),
	/**
	 * @DRIVER_SG:
	 *
	 * Driver can perक्रमm scatter/gather DMA, allocation and mapping of
	 * scatter/gather buffers will be enabled. Only क्रम legacy drivers. Do
	 * not use.
	 */
	DRIVER_SG			= BIT(28),

	/**
	 * @DRIVER_HAVE_DMA:
	 *
	 * Driver supports DMA, the userspace DMA API will be supported. Only
	 * क्रम legacy drivers. Do not use.
	 */
	DRIVER_HAVE_DMA			= BIT(29),
	/**
	 * @DRIVER_HAVE_IRQ:
	 *
	 * Legacy irq support. Only क्रम legacy drivers. Do not use.
	 *
	 * New drivers can either use the drm_irq_install() and
	 * drm_irq_uninstall() helper functions, or roll their own irq support
	 * code by calling request_irq() directly.
	 */
	DRIVER_HAVE_IRQ			= BIT(30),
	/**
	 * @DRIVER_KMS_LEGACY_CONTEXT:
	 *
	 * Used only by nouveau क्रम backwards compatibility with existing
	 * userspace.  Do not use.
	 */
	DRIVER_KMS_LEGACY_CONTEXT	= BIT(31),
पूर्ण;

/**
 * काष्ठा drm_driver - DRM driver काष्ठाure
 *
 * This काष्ठाure represent the common code क्रम a family of cards. There will be
 * one &काष्ठा drm_device क्रम each card present in this family. It contains lots
 * of vfunc entries, and a pile of those probably should be moved to more
 * appropriate places like &drm_mode_config_funcs or पूर्णांकo a new operations
 * काष्ठाure क्रम GEM drivers.
 */
काष्ठा drm_driver अणु
	/**
	 * @load:
	 *
	 * Backward-compatible driver callback to complete initialization steps
	 * after the driver is रेजिस्टरed.  For this reason, may suffer from
	 * race conditions and its use is deprecated क्रम new drivers.  It is
	 * thereक्रमe only supported क्रम existing drivers not yet converted to
	 * the new scheme.  See devm_drm_dev_alloc() and drm_dev_रेजिस्टर() क्रम
	 * proper and race-मुक्त way to set up a &काष्ठा drm_device.
	 *
	 * This is deprecated, करो not use!
	 *
	 * Returns:
	 *
	 * Zero on success, non-zero value on failure.
	 */
	पूर्णांक (*load) (काष्ठा drm_device *, अचिन्हित दीर्घ flags);

	/**
	 * @खोलो:
	 *
	 * Driver callback when a new &काष्ठा drm_file is खोलोed. Useful क्रम
	 * setting up driver-निजी data काष्ठाures like buffer allocators,
	 * execution contexts or similar things. Such driver-निजी resources
	 * must be released again in @postबंद.
	 *
	 * Since the display/modeset side of DRM can only be owned by exactly
	 * one &काष्ठा drm_file (see &drm_file.is_master and &drm_device.master)
	 * there should never be a need to set up any modeset related resources
	 * in this callback. Doing so would be a driver design bug.
	 *
	 * Returns:
	 *
	 * 0 on success, a negative error code on failure, which will be
	 * promoted to userspace as the result of the खोलो() प्रणाली call.
	 */
	पूर्णांक (*खोलो) (काष्ठा drm_device *, काष्ठा drm_file *);

	/**
	 * @postबंद:
	 *
	 * One of the driver callbacks when a new &काष्ठा drm_file is बंदd.
	 * Useful क्रम tearing करोwn driver-निजी data काष्ठाures allocated in
	 * @खोलो like buffer allocators, execution contexts or similar things.
	 *
	 * Since the display/modeset side of DRM can only be owned by exactly
	 * one &काष्ठा drm_file (see &drm_file.is_master and &drm_device.master)
	 * there should never be a need to tear करोwn any modeset related
	 * resources in this callback. Doing so would be a driver design bug.
	 */
	व्योम (*postबंद) (काष्ठा drm_device *, काष्ठा drm_file *);

	/**
	 * @lastबंद:
	 *
	 * Called when the last &काष्ठा drm_file has been बंदd and there's
	 * currently no userspace client क्रम the &काष्ठा drm_device.
	 *
	 * Modern drivers should only use this to क्रमce-restore the fbdev
	 * framebuffer using drm_fb_helper_restore_fbdev_mode_unlocked().
	 * Anything अन्यथा would indicate there's something seriously wrong.
	 * Modern drivers can also use this to execute delayed घातer चयनing
	 * state changes, e.g. in conjunction with the :ref:`vga_चयनeroo`
	 * infraकाष्ठाure.
	 *
	 * This is called after @postबंद hook has been called.
	 *
	 * NOTE:
	 *
	 * All legacy drivers use this callback to de-initialize the hardware.
	 * This is purely because of the shaकरोw-attach model, where the DRM
	 * kernel driver करोes not really own the hardware. Instead ownershipe is
	 * handled with the help of userspace through an inheritedly racy dance
	 * to set/unset the VT पूर्णांकo raw mode.
	 *
	 * Legacy drivers initialize the hardware in the @firstखोलो callback,
	 * which isn't even called क्रम modern drivers.
	 */
	व्योम (*lastबंद) (काष्ठा drm_device *);

	/**
	 * @unload:
	 *
	 * Reverse the effects of the driver load callback.  Ideally,
	 * the clean up perक्रमmed by the driver should happen in the
	 * reverse order of the initialization.  Similarly to the load
	 * hook, this handler is deprecated and its usage should be
	 * dropped in favor of an खोलो-coded tearकरोwn function at the
	 * driver layer.  See drm_dev_unरेजिस्टर() and drm_dev_put()
	 * क्रम the proper way to हटाओ a &काष्ठा drm_device.
	 *
	 * The unload() hook is called right after unरेजिस्टरing
	 * the device.
	 *
	 */
	व्योम (*unload) (काष्ठा drm_device *);

	/**
	 * @release:
	 *
	 * Optional callback क्रम destroying device data after the final
	 * reference is released, i.e. the device is being destroyed.
	 *
	 * This is deprecated, clean up all memory allocations associated with a
	 * &drm_device using drmm_add_action(), drmm_kदो_स्मृति() and related
	 * managed resources functions.
	 */
	व्योम (*release) (काष्ठा drm_device *);

	/**
	 * @irq_handler:
	 *
	 * Interrupt handler called when using drm_irq_install(). Not used by
	 * drivers which implement their own पूर्णांकerrupt handling.
	 */
	irqवापस_t(*irq_handler) (पूर्णांक irq, व्योम *arg);

	/**
	 * @irq_preinstall:
	 *
	 * Optional callback used by drm_irq_install() which is called beक्रमe
	 * the पूर्णांकerrupt handler is रेजिस्टरed. This should be used to clear out
	 * any pending पूर्णांकerrupts (from e.g. firmware based drives) and reset
	 * the पूर्णांकerrupt handling रेजिस्टरs.
	 */
	व्योम (*irq_preinstall) (काष्ठा drm_device *dev);

	/**
	 * @irq_postinstall:
	 *
	 * Optional callback used by drm_irq_install() which is called after
	 * the पूर्णांकerrupt handler is रेजिस्टरed. This should be used to enable
	 * पूर्णांकerrupt generation in the hardware.
	 */
	पूर्णांक (*irq_postinstall) (काष्ठा drm_device *dev);

	/**
	 * @irq_uninstall:
	 *
	 * Optional callback used by drm_irq_uninstall() which is called beक्रमe
	 * the पूर्णांकerrupt handler is unरेजिस्टरed. This should be used to disable
	 * पूर्णांकerrupt generation in the hardware.
	 */
	व्योम (*irq_uninstall) (काष्ठा drm_device *dev);

	/**
	 * @master_set:
	 *
	 * Called whenever the minor master is set. Only used by vmwgfx.
	 */
	व्योम (*master_set)(काष्ठा drm_device *dev, काष्ठा drm_file *file_priv,
			   bool from_खोलो);
	/**
	 * @master_drop:
	 *
	 * Called whenever the minor master is dropped. Only used by vmwgfx.
	 */
	व्योम (*master_drop)(काष्ठा drm_device *dev, काष्ठा drm_file *file_priv);

	/**
	 * @debugfs_init:
	 *
	 * Allows drivers to create driver-specअगरic debugfs files.
	 */
	व्योम (*debugfs_init)(काष्ठा drm_minor *minor);

	/**
	 * @gem_create_object: स्थिरructor क्रम gem objects
	 *
	 * Hook क्रम allocating the GEM object काष्ठा, क्रम use by the CMA and
	 * SHMEM GEM helpers.
	 */
	काष्ठा drm_gem_object *(*gem_create_object)(काष्ठा drm_device *dev,
						    माप_प्रकार size);

	/**
	 * @prime_handle_to_fd:
	 *
	 * Main PRIME export function. Should be implemented with
	 * drm_gem_prime_handle_to_fd() क्रम GEM based drivers.
	 *
	 * For an in-depth discussion see :ref:`PRIME buffer sharing
	 * करोcumentation <prime_buffer_sharing>`.
	 */
	पूर्णांक (*prime_handle_to_fd)(काष्ठा drm_device *dev, काष्ठा drm_file *file_priv,
				uपूर्णांक32_t handle, uपूर्णांक32_t flags, पूर्णांक *prime_fd);
	/**
	 * @prime_fd_to_handle:
	 *
	 * Main PRIME import function. Should be implemented with
	 * drm_gem_prime_fd_to_handle() क्रम GEM based drivers.
	 *
	 * For an in-depth discussion see :ref:`PRIME buffer sharing
	 * करोcumentation <prime_buffer_sharing>`.
	 */
	पूर्णांक (*prime_fd_to_handle)(काष्ठा drm_device *dev, काष्ठा drm_file *file_priv,
				पूर्णांक prime_fd, uपूर्णांक32_t *handle);

	/**
	 * @gem_prime_import:
	 *
	 * Import hook क्रम GEM drivers.
	 *
	 * This शेषs to drm_gem_prime_import() अगर not set.
	 */
	काष्ठा drm_gem_object * (*gem_prime_import)(काष्ठा drm_device *dev,
				काष्ठा dma_buf *dma_buf);
	/**
	 * @gem_prime_import_sg_table:
	 *
	 * Optional hook used by the PRIME helper functions
	 * drm_gem_prime_import() respectively drm_gem_prime_import_dev().
	 */
	काष्ठा drm_gem_object *(*gem_prime_import_sg_table)(
				काष्ठा drm_device *dev,
				काष्ठा dma_buf_attachment *attach,
				काष्ठा sg_table *sgt);
	/**
	 * @gem_prime_mmap:
	 *
	 * mmap hook क्रम GEM drivers, used to implement dma-buf mmap in the
	 * PRIME helpers.
	 *
	 * FIXME: There's way too much duplication going on here, and also moved
	 * to &drm_gem_object_funcs.
	 */
	पूर्णांक (*gem_prime_mmap)(काष्ठा drm_gem_object *obj,
				काष्ठा vm_area_काष्ठा *vma);

	/**
	 * @dumb_create:
	 *
	 * This creates a new dumb buffer in the driver's backing storage manager (GEM,
	 * TTM or something अन्यथा entirely) and वापसs the resulting buffer handle. This
	 * handle can then be wrapped up पूर्णांकo a framebuffer modeset object.
	 *
	 * Note that userspace is not allowed to use such objects क्रम render
	 * acceleration - drivers must create their own निजी ioctls क्रम such a use
	 * हाल.
	 *
	 * Width, height and depth are specअगरied in the &drm_mode_create_dumb
	 * argument. The callback needs to fill the handle, pitch and size क्रम
	 * the created buffer.
	 *
	 * Called by the user via ioctl.
	 *
	 * Returns:
	 *
	 * Zero on success, negative त्रुटि_सं on failure.
	 */
	पूर्णांक (*dumb_create)(काष्ठा drm_file *file_priv,
			   काष्ठा drm_device *dev,
			   काष्ठा drm_mode_create_dumb *args);
	/**
	 * @dumb_map_offset:
	 *
	 * Allocate an offset in the drm device node's address space to be able to
	 * memory map a dumb buffer.
	 *
	 * The शेष implementation is drm_gem_create_mmap_offset(). GEM based
	 * drivers must not overग_लिखो this.
	 *
	 * Called by the user via ioctl.
	 *
	 * Returns:
	 *
	 * Zero on success, negative त्रुटि_सं on failure.
	 */
	पूर्णांक (*dumb_map_offset)(काष्ठा drm_file *file_priv,
			       काष्ठा drm_device *dev, uपूर्णांक32_t handle,
			       uपूर्णांक64_t *offset);
	/**
	 * @dumb_destroy:
	 *
	 * This destroys the userspace handle क्रम the given dumb backing storage buffer.
	 * Since buffer objects must be reference counted in the kernel a buffer object
	 * won't be immediately मुक्तd अगर a framebuffer modeset object still uses it.
	 *
	 * Called by the user via ioctl.
	 *
	 * The शेष implementation is drm_gem_dumb_destroy(). GEM based drivers
	 * must not overग_लिखो this.
	 *
	 * Returns:
	 *
	 * Zero on success, negative त्रुटि_सं on failure.
	 */
	पूर्णांक (*dumb_destroy)(काष्ठा drm_file *file_priv,
			    काष्ठा drm_device *dev,
			    uपूर्णांक32_t handle);

	/** @major: driver major number */
	पूर्णांक major;
	/** @minor: driver minor number */
	पूर्णांक minor;
	/** @patchlevel: driver patch level */
	पूर्णांक patchlevel;
	/** @name: driver name */
	अक्षर *name;
	/** @desc: driver description */
	अक्षर *desc;
	/** @date: driver date */
	अक्षर *date;

	/**
	 * @driver_features:
	 * Driver features, see &क्रमागत drm_driver_feature. Drivers can disable
	 * some features on a per-instance basis using
	 * &drm_device.driver_features.
	 */
	u32 driver_features;

	/**
	 * @ioctls:
	 *
	 * Array of driver-निजी IOCTL description entries. See the chapter on
	 * :ref:`IOCTL support in the userland पूर्णांकerfaces
	 * chapter<drm_driver_ioctl>` क्रम the full details.
	 */

	स्थिर काष्ठा drm_ioctl_desc *ioctls;
	/** @num_ioctls: Number of entries in @ioctls. */
	पूर्णांक num_ioctls;

	/**
	 * @fops:
	 *
	 * File operations क्रम the DRM device node. See the discussion in
	 * :ref:`file operations<drm_driver_fops>` क्रम in-depth coverage and
	 * some examples.
	 */
	स्थिर काष्ठा file_operations *fops;

#अगर_घोषित CONFIG_DRM_LEGACY
	/* Everything below here is क्रम legacy driver, never use! */
	/* निजी: */

	पूर्णांक (*firstखोलो) (काष्ठा drm_device *);
	व्योम (*preबंद) (काष्ठा drm_device *, काष्ठा drm_file *file_priv);
	पूर्णांक (*dma_ioctl) (काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file_priv);
	पूर्णांक (*dma_quiescent) (काष्ठा drm_device *);
	पूर्णांक (*context_dtor) (काष्ठा drm_device *dev, पूर्णांक context);
	u32 (*get_vblank_counter)(काष्ठा drm_device *dev, अचिन्हित पूर्णांक pipe);
	पूर्णांक (*enable_vblank)(काष्ठा drm_device *dev, अचिन्हित पूर्णांक pipe);
	व्योम (*disable_vblank)(काष्ठा drm_device *dev, अचिन्हित पूर्णांक pipe);
	पूर्णांक dev_priv_size;
#पूर्ण_अगर
पूर्ण;

व्योम *__devm_drm_dev_alloc(काष्ठा device *parent,
			   स्थिर काष्ठा drm_driver *driver,
			   माप_प्रकार size, माप_प्रकार offset);

/**
 * devm_drm_dev_alloc - Resource managed allocation of a &drm_device instance
 * @parent: Parent device object
 * @driver: DRM driver
 * @type: the type of the काष्ठा which contains काष्ठा &drm_device
 * @member: the name of the &drm_device within @type.
 *
 * This allocates and initialize a new DRM device. No device registration is करोne.
 * Call drm_dev_रेजिस्टर() to advertice the device to user space and रेजिस्टर it
 * with other core subप्रणालीs. This should be करोne last in the device
 * initialization sequence to make sure userspace can't access an inconsistent
 * state.
 *
 * The initial ref-count of the object is 1. Use drm_dev_get() and
 * drm_dev_put() to take and drop further ref-counts.
 *
 * It is recommended that drivers embed &काष्ठा drm_device पूर्णांकo their own device
 * काष्ठाure.
 *
 * Note that this manages the lअगरeसमय of the resulting &drm_device
 * स्वतःmatically using devres. The DRM device initialized with this function is
 * स्वतःmatically put on driver detach using drm_dev_put().
 *
 * RETURNS:
 * Poपूर्णांकer to new DRM device, or ERR_PTR on failure.
 */
#घोषणा devm_drm_dev_alloc(parent, driver, type, member) \
	((type *) __devm_drm_dev_alloc(parent, driver, माप(type), \
				       दुरत्व(type, member)))

काष्ठा drm_device *drm_dev_alloc(स्थिर काष्ठा drm_driver *driver,
				 काष्ठा device *parent);
पूर्णांक drm_dev_रेजिस्टर(काष्ठा drm_device *dev, अचिन्हित दीर्घ flags);
व्योम drm_dev_unरेजिस्टर(काष्ठा drm_device *dev);

व्योम drm_dev_get(काष्ठा drm_device *dev);
व्योम drm_dev_put(काष्ठा drm_device *dev);
व्योम drm_put_dev(काष्ठा drm_device *dev);
bool drm_dev_enter(काष्ठा drm_device *dev, पूर्णांक *idx);
व्योम drm_dev_निकास(पूर्णांक idx);
व्योम drm_dev_unplug(काष्ठा drm_device *dev);

/**
 * drm_dev_is_unplugged - is a DRM device unplugged
 * @dev: DRM device
 *
 * This function can be called to check whether a hotpluggable is unplugged.
 * Unplugging itself is singalled through drm_dev_unplug(). If a device is
 * unplugged, these two functions guarantee that any store beक्रमe calling
 * drm_dev_unplug() is visible to callers of this function after it completes
 *
 * WARNING: This function fundamentally races against drm_dev_unplug(). It is
 * recommended that drivers instead use the underlying drm_dev_enter() and
 * drm_dev_निकास() function pairs.
 */
अटल अंतरभूत bool drm_dev_is_unplugged(काष्ठा drm_device *dev)
अणु
	पूर्णांक idx;

	अगर (drm_dev_enter(dev, &idx)) अणु
		drm_dev_निकास(idx);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

/**
 * drm_core_check_all_features - check driver feature flags mask
 * @dev: DRM device to check
 * @features: feature flag(s) mask
 *
 * This checks @dev क्रम driver features, see &drm_driver.driver_features,
 * &drm_device.driver_features, and the various &क्रमागत drm_driver_feature flags.
 *
 * Returns true अगर all features in the @features mask are supported, false
 * otherwise.
 */
अटल अंतरभूत bool drm_core_check_all_features(स्थिर काष्ठा drm_device *dev,
					       u32 features)
अणु
	u32 supported = dev->driver->driver_features & dev->driver_features;

	वापस features && (supported & features) == features;
पूर्ण

/**
 * drm_core_check_feature - check driver feature flags
 * @dev: DRM device to check
 * @feature: feature flag
 *
 * This checks @dev क्रम driver features, see &drm_driver.driver_features,
 * &drm_device.driver_features, and the various &क्रमागत drm_driver_feature flags.
 *
 * Returns true अगर the @feature is supported, false otherwise.
 */
अटल अंतरभूत bool drm_core_check_feature(स्थिर काष्ठा drm_device *dev,
					  क्रमागत drm_driver_feature feature)
अणु
	वापस drm_core_check_all_features(dev, feature);
पूर्ण

/**
 * drm_drv_uses_atomic_modeset - check अगर the driver implements
 * atomic_commit()
 * @dev: DRM device
 *
 * This check is useful अगर drivers करो not have DRIVER_ATOMIC set but
 * have atomic modesetting पूर्णांकernally implemented.
 */
अटल अंतरभूत bool drm_drv_uses_atomic_modeset(काष्ठा drm_device *dev)
अणु
	वापस drm_core_check_feature(dev, DRIVER_ATOMIC) ||
		(dev->mode_config.funcs && dev->mode_config.funcs->atomic_commit != शून्य);
पूर्ण


पूर्णांक drm_dev_set_unique(काष्ठा drm_device *dev, स्थिर अक्षर *name);


#पूर्ण_अगर
