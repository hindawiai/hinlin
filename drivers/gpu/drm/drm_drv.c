<शैली गुरु>
/*
 * Created: Fri Jan 19 10:48:35 2001 by faith@acm.org
 *
 * Copyright 2001 VA Linux Systems, Inc., Sunnyvale, Calअगरornia.
 * All Rights Reserved.
 *
 * Author Rickard E. (Rik) Faith <faith@valinux.com>
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
 * PRECISION INSIGHT AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#समावेश <linux/debugfs.h>
#समावेश <linux/fs.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/mount.h>
#समावेश <linux/pseuकरो_fs.h>
#समावेश <linux/slab.h>
#समावेश <linux/srcu.h>

#समावेश <drm/drm_client.h>
#समावेश <drm/drm_color_mgmt.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_managed.h>
#समावेश <drm/drm_mode_object.h>
#समावेश <drm/drm_prपूर्णांक.h>

#समावेश "drm_crtc_internal.h"
#समावेश "drm_internal.h"
#समावेश "drm_legacy.h"

MODULE_AUTHOR("Gareth Hughes, Leif Delgass, Josथऊ Fonseca, Jon Smirl");
MODULE_DESCRIPTION("DRM shared core routines");
MODULE_LICENSE("GPL and additional rights");

अटल DEFINE_SPINLOCK(drm_minor_lock);
अटल काष्ठा idr drm_minors_idr;

/*
 * If the drm core fails to init क्रम whatever reason,
 * we should prevent any drivers from रेजिस्टरing with it.
 * It's best to check this at drm_dev_init(), as some drivers
 * prefer to embed काष्ठा drm_device पूर्णांकo their own device
 * काष्ठाure and call drm_dev_init() themselves.
 */
अटल bool drm_core_init_complete;

अटल काष्ठा dentry *drm_debugfs_root;

DEFINE_STATIC_SRCU(drm_unplug_srcu);

/*
 * DRM Minors
 * A DRM device can provide several अक्षर-dev पूर्णांकerfaces on the DRM-Major. Each
 * of them is represented by a drm_minor object. Depending on the capabilities
 * of the device-driver, dअगरferent पूर्णांकerfaces are रेजिस्टरed.
 *
 * Minors can be accessed via dev->$minor_name. This poपूर्णांकer is either
 * शून्य or a valid drm_minor poपूर्णांकer and stays valid as दीर्घ as the device is
 * valid. This means, DRM minors have the same lअगरe-समय as the underlying
 * device. However, this करोesn't mean that the minor is active. Minors are
 * रेजिस्टरed and unरेजिस्टरed dynamically according to device-state.
 */

अटल काष्ठा drm_minor **drm_minor_get_slot(काष्ठा drm_device *dev,
					     अचिन्हित पूर्णांक type)
अणु
	चयन (type) अणु
	हाल DRM_MINOR_PRIMARY:
		वापस &dev->primary;
	हाल DRM_MINOR_RENDER:
		वापस &dev->render;
	शेष:
		BUG();
	पूर्ण
पूर्ण

अटल व्योम drm_minor_alloc_release(काष्ठा drm_device *dev, व्योम *data)
अणु
	काष्ठा drm_minor *minor = data;
	अचिन्हित दीर्घ flags;

	WARN_ON(dev != minor->dev);

	put_device(minor->kdev);

	spin_lock_irqsave(&drm_minor_lock, flags);
	idr_हटाओ(&drm_minors_idr, minor->index);
	spin_unlock_irqrestore(&drm_minor_lock, flags);
पूर्ण

अटल पूर्णांक drm_minor_alloc(काष्ठा drm_device *dev, अचिन्हित पूर्णांक type)
अणु
	काष्ठा drm_minor *minor;
	अचिन्हित दीर्घ flags;
	पूर्णांक r;

	minor = drmm_kzalloc(dev, माप(*minor), GFP_KERNEL);
	अगर (!minor)
		वापस -ENOMEM;

	minor->type = type;
	minor->dev = dev;

	idr_preload(GFP_KERNEL);
	spin_lock_irqsave(&drm_minor_lock, flags);
	r = idr_alloc(&drm_minors_idr,
		      शून्य,
		      64 * type,
		      64 * (type + 1),
		      GFP_NOWAIT);
	spin_unlock_irqrestore(&drm_minor_lock, flags);
	idr_preload_end();

	अगर (r < 0)
		वापस r;

	minor->index = r;

	r = drmm_add_action_or_reset(dev, drm_minor_alloc_release, minor);
	अगर (r)
		वापस r;

	minor->kdev = drm_sysfs_minor_alloc(minor);
	अगर (IS_ERR(minor->kdev))
		वापस PTR_ERR(minor->kdev);

	*drm_minor_get_slot(dev, type) = minor;
	वापस 0;
पूर्ण

अटल पूर्णांक drm_minor_रेजिस्टर(काष्ठा drm_device *dev, अचिन्हित पूर्णांक type)
अणु
	काष्ठा drm_minor *minor;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	DRM_DEBUG("\n");

	minor = *drm_minor_get_slot(dev, type);
	अगर (!minor)
		वापस 0;

	ret = drm_debugfs_init(minor, minor->index, drm_debugfs_root);
	अगर (ret) अणु
		DRM_ERROR("DRM: Failed to initialize /sys/kernel/debug/dri.\n");
		जाओ err_debugfs;
	पूर्ण

	ret = device_add(minor->kdev);
	अगर (ret)
		जाओ err_debugfs;

	/* replace शून्य with @minor so lookups will succeed from now on */
	spin_lock_irqsave(&drm_minor_lock, flags);
	idr_replace(&drm_minors_idr, minor, minor->index);
	spin_unlock_irqrestore(&drm_minor_lock, flags);

	DRM_DEBUG("new minor registered %d\n", minor->index);
	वापस 0;

err_debugfs:
	drm_debugfs_cleanup(minor);
	वापस ret;
पूर्ण

अटल व्योम drm_minor_unरेजिस्टर(काष्ठा drm_device *dev, अचिन्हित पूर्णांक type)
अणु
	काष्ठा drm_minor *minor;
	अचिन्हित दीर्घ flags;

	minor = *drm_minor_get_slot(dev, type);
	अगर (!minor || !device_is_रेजिस्टरed(minor->kdev))
		वापस;

	/* replace @minor with शून्य so lookups will fail from now on */
	spin_lock_irqsave(&drm_minor_lock, flags);
	idr_replace(&drm_minors_idr, शून्य, minor->index);
	spin_unlock_irqrestore(&drm_minor_lock, flags);

	device_del(minor->kdev);
	dev_set_drvdata(minor->kdev, शून्य); /* safety belt */
	drm_debugfs_cleanup(minor);
पूर्ण

/*
 * Looks up the given minor-ID and वापसs the respective DRM-minor object. The
 * refence-count of the underlying device is increased so you must release this
 * object with drm_minor_release().
 *
 * As दीर्घ as you hold this minor, it is guaranteed that the object and the
 * minor->dev poपूर्णांकer will stay valid! However, the device may get unplugged and
 * unरेजिस्टरed जबतक you hold the minor.
 */
काष्ठा drm_minor *drm_minor_acquire(अचिन्हित पूर्णांक minor_id)
अणु
	काष्ठा drm_minor *minor;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&drm_minor_lock, flags);
	minor = idr_find(&drm_minors_idr, minor_id);
	अगर (minor)
		drm_dev_get(minor->dev);
	spin_unlock_irqrestore(&drm_minor_lock, flags);

	अगर (!minor) अणु
		वापस ERR_PTR(-ENODEV);
	पूर्ण अन्यथा अगर (drm_dev_is_unplugged(minor->dev)) अणु
		drm_dev_put(minor->dev);
		वापस ERR_PTR(-ENODEV);
	पूर्ण

	वापस minor;
पूर्ण

व्योम drm_minor_release(काष्ठा drm_minor *minor)
अणु
	drm_dev_put(minor->dev);
पूर्ण

/**
 * DOC: driver instance overview
 *
 * A device instance क्रम a drm driver is represented by &काष्ठा drm_device. This
 * is allocated and initialized with devm_drm_dev_alloc(), usually from
 * bus-specअगरic ->probe() callbacks implemented by the driver. The driver then
 * needs to initialize all the various subप्रणालीs क्रम the drm device like memory
 * management, vblank handling, modesetting support and initial output
 * configuration plus obviously initialize all the corresponding hardware bits.
 * Finally when everything is up and running and पढ़ोy क्रम userspace the device
 * instance can be published using drm_dev_रेजिस्टर().
 *
 * There is also deprecated support क्रम initalizing device instances using
 * bus-specअगरic helpers and the &drm_driver.load callback. But due to
 * backwards-compatibility needs the device instance have to be published too
 * early, which requires unpretty global locking to make safe and is thereक्रमe
 * only support क्रम existing drivers not yet converted to the new scheme.
 *
 * When cleaning up a device instance everything needs to be करोne in reverse:
 * First unpublish the device instance with drm_dev_unरेजिस्टर(). Then clean up
 * any other resources allocated at device initialization and drop the driver's
 * reference to &drm_device using drm_dev_put().
 *
 * Note that any allocation or resource which is visible to userspace must be
 * released only when the final drm_dev_put() is called, and not when the
 * driver is unbound from the underlying physical काष्ठा &device. Best to use
 * &drm_device managed resources with drmm_add_action(), drmm_kदो_स्मृति() and
 * related functions.
 *
 * devres managed resources like devm_kदो_स्मृति() can only be used क्रम resources
 * directly related to the underlying hardware device, and only used in code
 * paths fully रक्षित by drm_dev_enter() and drm_dev_निकास().
 *
 * Display driver example
 * ~~~~~~~~~~~~~~~~~~~~~~
 *
 * The following example shows a typical काष्ठाure of a DRM display driver.
 * The example focus on the probe() function and the other functions that is
 * almost always present and serves as a demonstration of devm_drm_dev_alloc().
 *
 * .. code-block:: c
 *
 *	काष्ठा driver_device अणु
 *		काष्ठा drm_device drm;
 *		व्योम *userspace_facing;
 *		काष्ठा clk *pclk;
 *	पूर्ण;
 *
 *	अटल स्थिर काष्ठा drm_driver driver_drm_driver = अणु
 *		[...]
 *	पूर्ण;
 *
 *	अटल पूर्णांक driver_probe(काष्ठा platक्रमm_device *pdev)
 *	अणु
 *		काष्ठा driver_device *priv;
 *		काष्ठा drm_device *drm;
 *		पूर्णांक ret;
 *
 *		priv = devm_drm_dev_alloc(&pdev->dev, &driver_drm_driver,
 *					  काष्ठा driver_device, drm);
 *		अगर (IS_ERR(priv))
 *			वापस PTR_ERR(priv);
 *		drm = &priv->drm;
 *
 *		ret = drmm_mode_config_init(drm);
 *		अगर (ret)
 *			वापस ret;
 *
 *		priv->userspace_facing = drmm_kzalloc(..., GFP_KERNEL);
 *		अगर (!priv->userspace_facing)
 *			वापस -ENOMEM;
 *
 *		priv->pclk = devm_clk_get(dev, "PCLK");
 *		अगर (IS_ERR(priv->pclk))
 *			वापस PTR_ERR(priv->pclk);
 *
 *		// Further setup, display pipeline etc
 *
 *		platक्रमm_set_drvdata(pdev, drm);
 *
 *		drm_mode_config_reset(drm);
 *
 *		ret = drm_dev_रेजिस्टर(drm);
 *		अगर (ret)
 *			वापस ret;
 *
 *		drm_fbdev_generic_setup(drm, 32);
 *
 *		वापस 0;
 *	पूर्ण
 *
 *	// This function is called beक्रमe the devm_ resources are released
 *	अटल पूर्णांक driver_हटाओ(काष्ठा platक्रमm_device *pdev)
 *	अणु
 *		काष्ठा drm_device *drm = platक्रमm_get_drvdata(pdev);
 *
 *		drm_dev_unरेजिस्टर(drm);
 *		drm_atomic_helper_shutकरोwn(drm)
 *
 *		वापस 0;
 *	पूर्ण
 *
 *	// This function is called on kernel restart and shutकरोwn
 *	अटल व्योम driver_shutकरोwn(काष्ठा platक्रमm_device *pdev)
 *	अणु
 *		drm_atomic_helper_shutकरोwn(platक्रमm_get_drvdata(pdev));
 *	पूर्ण
 *
 *	अटल पूर्णांक __maybe_unused driver_pm_suspend(काष्ठा device *dev)
 *	अणु
 *		वापस drm_mode_config_helper_suspend(dev_get_drvdata(dev));
 *	पूर्ण
 *
 *	अटल पूर्णांक __maybe_unused driver_pm_resume(काष्ठा device *dev)
 *	अणु
 *		drm_mode_config_helper_resume(dev_get_drvdata(dev));
 *
 *		वापस 0;
 *	पूर्ण
 *
 *	अटल स्थिर काष्ठा dev_pm_ops driver_pm_ops = अणु
 *		SET_SYSTEM_SLEEP_PM_OPS(driver_pm_suspend, driver_pm_resume)
 *	पूर्ण;
 *
 *	अटल काष्ठा platक्रमm_driver driver_driver = अणु
 *		.driver = अणु
 *			[...]
 *			.pm = &driver_pm_ops,
 *		पूर्ण,
 *		.probe = driver_probe,
 *		.हटाओ = driver_हटाओ,
 *		.shutकरोwn = driver_shutकरोwn,
 *	पूर्ण;
 *	module_platक्रमm_driver(driver_driver);
 *
 * Drivers that want to support device unplugging (USB, DT overlay unload) should
 * use drm_dev_unplug() instead of drm_dev_unरेजिस्टर(). The driver must protect
 * regions that is accessing device resources to prevent use after they're
 * released. This is करोne using drm_dev_enter() and drm_dev_निकास(). There is one
 * लघुcoming however, drm_dev_unplug() marks the drm_device as unplugged beक्रमe
 * drm_atomic_helper_shutकरोwn() is called. This means that अगर the disable code
 * paths are रक्षित, they will not run on regular driver module unload,
 * possibily leaving the hardware enabled.
 */

/**
 * drm_put_dev - Unरेजिस्टर and release a DRM device
 * @dev: DRM device
 *
 * Called at module unload समय or when a PCI device is unplugged.
 *
 * Cleans up all DRM device, calling drm_lastबंद().
 *
 * Note: Use of this function is deprecated. It will eventually go away
 * completely.  Please use drm_dev_unरेजिस्टर() and drm_dev_put() explicitly
 * instead to make sure that the device isn't userspace accessible any more
 * जबतक tearकरोwn is in progress, ensuring that userspace can't access an
 * inconsistent state.
 */
व्योम drm_put_dev(काष्ठा drm_device *dev)
अणु
	DRM_DEBUG("\n");

	अगर (!dev) अणु
		DRM_ERROR("cleanup called no dev\n");
		वापस;
	पूर्ण

	drm_dev_unरेजिस्टर(dev);
	drm_dev_put(dev);
पूर्ण
EXPORT_SYMBOL(drm_put_dev);

/**
 * drm_dev_enter - Enter device critical section
 * @dev: DRM device
 * @idx: Poपूर्णांकer to index that will be passed to the matching drm_dev_निकास()
 *
 * This function marks and protects the beginning of a section that should not
 * be entered after the device has been unplugged. The section end is marked
 * with drm_dev_निकास(). Calls to this function can be nested.
 *
 * Returns:
 * True अगर it is OK to enter the section, false otherwise.
 */
bool drm_dev_enter(काष्ठा drm_device *dev, पूर्णांक *idx)
अणु
	*idx = srcu_पढ़ो_lock(&drm_unplug_srcu);

	अगर (dev->unplugged) अणु
		srcu_पढ़ो_unlock(&drm_unplug_srcu, *idx);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण
EXPORT_SYMBOL(drm_dev_enter);

/**
 * drm_dev_निकास - Exit device critical section
 * @idx: index वापसed from drm_dev_enter()
 *
 * This function marks the end of a section that should not be entered after
 * the device has been unplugged.
 */
व्योम drm_dev_निकास(पूर्णांक idx)
अणु
	srcu_पढ़ो_unlock(&drm_unplug_srcu, idx);
पूर्ण
EXPORT_SYMBOL(drm_dev_निकास);

/**
 * drm_dev_unplug - unplug a DRM device
 * @dev: DRM device
 *
 * This unplugs a hotpluggable DRM device, which makes it inaccessible to
 * userspace operations. Entry-poपूर्णांकs can use drm_dev_enter() and
 * drm_dev_निकास() to protect device resources in a race मुक्त manner. This
 * essentially unरेजिस्टरs the device like drm_dev_unरेजिस्टर(), but can be
 * called जबतक there are still खोलो users of @dev.
 */
व्योम drm_dev_unplug(काष्ठा drm_device *dev)
अणु
	/*
	 * After synchronizing any critical पढ़ो section is guaranteed to see
	 * the new value of ->unplugged, and any critical section which might
	 * still have seen the old value of ->unplugged is guaranteed to have
	 * finished.
	 */
	dev->unplugged = true;
	synchronize_srcu(&drm_unplug_srcu);

	drm_dev_unरेजिस्टर(dev);

	/* Clear all CPU mappings poपूर्णांकing to this device */
	unmap_mapping_range(dev->anon_inode->i_mapping, 0, 0, 1);
पूर्ण
EXPORT_SYMBOL(drm_dev_unplug);

/*
 * DRM पूर्णांकernal mount
 * We want to be able to allocate our own "struct address_space" to control
 * memory-mappings in VRAM (or stolen RAM, ...). However, core MM करोes not allow
 * stand-alone address_space objects, so we need an underlying inode. As there
 * is no way to allocate an independent inode easily, we need a fake पूर्णांकernal
 * VFS mount-poपूर्णांक.
 *
 * The drm_fs_inode_new() function allocates a new inode, drm_fs_inode_मुक्त()
 * मुक्तs it again. You are allowed to use iget() and iput() to get references to
 * the inode. But each drm_fs_inode_new() call must be paired with exactly one
 * drm_fs_inode_मुक्त() call (which करोes not have to be the last iput()).
 * We use drm_fs_inode_*() to manage our पूर्णांकernal VFS mount-poपूर्णांक and share it
 * between multiple inode-users. You could, technically, call
 * iget() + drm_fs_inode_मुक्त() directly after alloc and someसमय later करो an
 * iput(), but this way you'd end up with a new vfsmount क्रम each inode.
 */

अटल पूर्णांक drm_fs_cnt;
अटल काष्ठा vfsmount *drm_fs_mnt;

अटल पूर्णांक drm_fs_init_fs_context(काष्ठा fs_context *fc)
अणु
	वापस init_pseuकरो(fc, 0x010203ff) ? 0 : -ENOMEM;
पूर्ण

अटल काष्ठा file_प्रणाली_type drm_fs_type = अणु
	.name		= "drm",
	.owner		= THIS_MODULE,
	.init_fs_context = drm_fs_init_fs_context,
	.समाप्त_sb	= समाप्त_anon_super,
पूर्ण;

अटल काष्ठा inode *drm_fs_inode_new(व्योम)
अणु
	काष्ठा inode *inode;
	पूर्णांक r;

	r = simple_pin_fs(&drm_fs_type, &drm_fs_mnt, &drm_fs_cnt);
	अगर (r < 0) अणु
		DRM_ERROR("Cannot mount pseudo fs: %d\n", r);
		वापस ERR_PTR(r);
	पूर्ण

	inode = alloc_anon_inode(drm_fs_mnt->mnt_sb);
	अगर (IS_ERR(inode))
		simple_release_fs(&drm_fs_mnt, &drm_fs_cnt);

	वापस inode;
पूर्ण

अटल व्योम drm_fs_inode_मुक्त(काष्ठा inode *inode)
अणु
	अगर (inode) अणु
		iput(inode);
		simple_release_fs(&drm_fs_mnt, &drm_fs_cnt);
	पूर्ण
पूर्ण

/**
 * DOC: component helper usage recommendations
 *
 * DRM drivers that drive hardware where a logical device consists of a pile of
 * independent hardware blocks are recommended to use the :ref:`component helper
 * library<component>`. For consistency and better options क्रम code reuse the
 * following guidelines apply:
 *
 *  - The entire device initialization procedure should be run from the
 *    &component_master_ops.master_bind callback, starting with
 *    devm_drm_dev_alloc(), then binding all components with
 *    component_bind_all() and finishing with drm_dev_रेजिस्टर().
 *
 *  - The opaque poपूर्णांकer passed to all components through component_bind_all()
 *    should poपूर्णांक at &काष्ठा drm_device of the device instance, not some driver
 *    specअगरic निजी काष्ठाure.
 *
 *  - The component helper fills the niche where further standardization of
 *    पूर्णांकerfaces is not practical. When there alपढ़ोy is, or will be, a
 *    standardized पूर्णांकerface like &drm_bridge or &drm_panel, providing its own
 *    functions to find such components at driver load समय, like
 *    drm_of_find_panel_or_bridge(), then the component helper should not be
 *    used.
 */

अटल व्योम drm_dev_init_release(काष्ठा drm_device *dev, व्योम *res)
अणु
	drm_legacy_ctxbiपंचांगap_cleanup(dev);
	drm_legacy_हटाओ_map_hash(dev);
	drm_fs_inode_मुक्त(dev->anon_inode);

	put_device(dev->dev);
	/* Prevent use-after-मुक्त in drm_managed_release when debugging is
	 * enabled. Slightly awkward, but can't really be helped. */
	dev->dev = शून्य;
	mutex_destroy(&dev->master_mutex);
	mutex_destroy(&dev->clientlist_mutex);
	mutex_destroy(&dev->filelist_mutex);
	mutex_destroy(&dev->काष्ठा_mutex);
	drm_legacy_destroy_members(dev);
पूर्ण

अटल पूर्णांक drm_dev_init(काष्ठा drm_device *dev,
			स्थिर काष्ठा drm_driver *driver,
			काष्ठा device *parent)
अणु
	पूर्णांक ret;

	अगर (!drm_core_init_complete) अणु
		DRM_ERROR("DRM core is not initialized\n");
		वापस -ENODEV;
	पूर्ण

	अगर (WARN_ON(!parent))
		वापस -EINVAL;

	kref_init(&dev->ref);
	dev->dev = get_device(parent);
	dev->driver = driver;

	INIT_LIST_HEAD(&dev->managed.resources);
	spin_lock_init(&dev->managed.lock);

	/* no per-device feature limits by शेष */
	dev->driver_features = ~0u;

	drm_legacy_init_members(dev);
	INIT_LIST_HEAD(&dev->filelist);
	INIT_LIST_HEAD(&dev->filelist_पूर्णांकernal);
	INIT_LIST_HEAD(&dev->clientlist);
	INIT_LIST_HEAD(&dev->vblank_event_list);

	spin_lock_init(&dev->event_lock);
	mutex_init(&dev->काष्ठा_mutex);
	mutex_init(&dev->filelist_mutex);
	mutex_init(&dev->clientlist_mutex);
	mutex_init(&dev->master_mutex);

	ret = drmm_add_action(dev, drm_dev_init_release, शून्य);
	अगर (ret)
		वापस ret;

	dev->anon_inode = drm_fs_inode_new();
	अगर (IS_ERR(dev->anon_inode)) अणु
		ret = PTR_ERR(dev->anon_inode);
		DRM_ERROR("Cannot allocate anonymous inode: %d\n", ret);
		जाओ err;
	पूर्ण

	अगर (drm_core_check_feature(dev, DRIVER_RENDER)) अणु
		ret = drm_minor_alloc(dev, DRM_MINOR_RENDER);
		अगर (ret)
			जाओ err;
	पूर्ण

	ret = drm_minor_alloc(dev, DRM_MINOR_PRIMARY);
	अगर (ret)
		जाओ err;

	ret = drm_legacy_create_map_hash(dev);
	अगर (ret)
		जाओ err;

	drm_legacy_ctxbiपंचांगap_init(dev);

	अगर (drm_core_check_feature(dev, DRIVER_GEM)) अणु
		ret = drm_gem_init(dev);
		अगर (ret) अणु
			DRM_ERROR("Cannot initialize graphics execution manager (GEM)\n");
			जाओ err;
		पूर्ण
	पूर्ण

	ret = drm_dev_set_unique(dev, dev_name(parent));
	अगर (ret)
		जाओ err;

	वापस 0;

err:
	drm_managed_release(dev);

	वापस ret;
पूर्ण

अटल व्योम devm_drm_dev_init_release(व्योम *data)
अणु
	drm_dev_put(data);
पूर्ण

अटल पूर्णांक devm_drm_dev_init(काष्ठा device *parent,
			     काष्ठा drm_device *dev,
			     स्थिर काष्ठा drm_driver *driver)
अणु
	पूर्णांक ret;

	ret = drm_dev_init(dev, driver, parent);
	अगर (ret)
		वापस ret;

	वापस devm_add_action_or_reset(parent,
					devm_drm_dev_init_release, dev);
पूर्ण

व्योम *__devm_drm_dev_alloc(काष्ठा device *parent,
			   स्थिर काष्ठा drm_driver *driver,
			   माप_प्रकार size, माप_प्रकार offset)
अणु
	व्योम *container;
	काष्ठा drm_device *drm;
	पूर्णांक ret;

	container = kzalloc(size, GFP_KERNEL);
	अगर (!container)
		वापस ERR_PTR(-ENOMEM);

	drm = container + offset;
	ret = devm_drm_dev_init(parent, drm, driver);
	अगर (ret) अणु
		kमुक्त(container);
		वापस ERR_PTR(ret);
	पूर्ण
	drmm_add_final_kमुक्त(drm, container);

	वापस container;
पूर्ण
EXPORT_SYMBOL(__devm_drm_dev_alloc);

/**
 * drm_dev_alloc - Allocate new DRM device
 * @driver: DRM driver to allocate device क्रम
 * @parent: Parent device object
 *
 * This is the deprecated version of devm_drm_dev_alloc(), which करोes not support
 * subclassing through embedding the काष्ठा &drm_device in a driver निजी
 * काष्ठाure, and which करोes not support स्वतःmatic cleanup through devres.
 *
 * RETURNS:
 * Poपूर्णांकer to new DRM device, or ERR_PTR on failure.
 */
काष्ठा drm_device *drm_dev_alloc(स्थिर काष्ठा drm_driver *driver,
				 काष्ठा device *parent)
अणु
	काष्ठा drm_device *dev;
	पूर्णांक ret;

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस ERR_PTR(-ENOMEM);

	ret = drm_dev_init(dev, driver, parent);
	अगर (ret) अणु
		kमुक्त(dev);
		वापस ERR_PTR(ret);
	पूर्ण

	drmm_add_final_kमुक्त(dev, dev);

	वापस dev;
पूर्ण
EXPORT_SYMBOL(drm_dev_alloc);

अटल व्योम drm_dev_release(काष्ठा kref *ref)
अणु
	काष्ठा drm_device *dev = container_of(ref, काष्ठा drm_device, ref);

	अगर (dev->driver->release)
		dev->driver->release(dev);

	drm_managed_release(dev);

	kमुक्त(dev->managed.final_kमुक्त);
पूर्ण

/**
 * drm_dev_get - Take reference of a DRM device
 * @dev: device to take reference of or शून्य
 *
 * This increases the ref-count of @dev by one. You *must* alपढ़ोy own a
 * reference when calling this. Use drm_dev_put() to drop this reference
 * again.
 *
 * This function never fails. However, this function करोes not provide *any*
 * guarantee whether the device is alive or running. It only provides a
 * reference to the object and the memory associated with it.
 */
व्योम drm_dev_get(काष्ठा drm_device *dev)
अणु
	अगर (dev)
		kref_get(&dev->ref);
पूर्ण
EXPORT_SYMBOL(drm_dev_get);

/**
 * drm_dev_put - Drop reference of a DRM device
 * @dev: device to drop reference of or शून्य
 *
 * This decreases the ref-count of @dev by one. The device is destroyed अगर the
 * ref-count drops to zero.
 */
व्योम drm_dev_put(काष्ठा drm_device *dev)
अणु
	अगर (dev)
		kref_put(&dev->ref, drm_dev_release);
पूर्ण
EXPORT_SYMBOL(drm_dev_put);

अटल पूर्णांक create_compat_control_link(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_minor *minor;
	अक्षर *name;
	पूर्णांक ret;

	अगर (!drm_core_check_feature(dev, DRIVER_MODESET))
		वापस 0;

	minor = *drm_minor_get_slot(dev, DRM_MINOR_PRIMARY);
	अगर (!minor)
		वापस 0;

	/*
	 * Some existing userspace out there uses the existing of the controlD*
	 * sysfs files to figure out whether it's a modeset driver. It only करोes
	 * सूची_पढ़ो, hence a symlink is sufficient (and the least confusing
	 * option). Otherwise controlD* is entirely unused.
	 *
	 * Old controlD अक्षरdev have been allocated in the range
	 * 64-127.
	 */
	name = kaप्र_लिखो(GFP_KERNEL, "controlD%d", minor->index + 64);
	अगर (!name)
		वापस -ENOMEM;

	ret = sysfs_create_link(minor->kdev->kobj.parent,
				&minor->kdev->kobj,
				name);

	kमुक्त(name);

	वापस ret;
पूर्ण

अटल व्योम हटाओ_compat_control_link(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_minor *minor;
	अक्षर *name;

	अगर (!drm_core_check_feature(dev, DRIVER_MODESET))
		वापस;

	minor = *drm_minor_get_slot(dev, DRM_MINOR_PRIMARY);
	अगर (!minor)
		वापस;

	name = kaप्र_लिखो(GFP_KERNEL, "controlD%d", minor->index + 64);
	अगर (!name)
		वापस;

	sysfs_हटाओ_link(minor->kdev->kobj.parent, name);

	kमुक्त(name);
पूर्ण

/**
 * drm_dev_रेजिस्टर - Register DRM device
 * @dev: Device to रेजिस्टर
 * @flags: Flags passed to the driver's .load() function
 *
 * Register the DRM device @dev with the प्रणाली, advertise device to user-space
 * and start normal device operation. @dev must be initialized via drm_dev_init()
 * previously.
 *
 * Never call this twice on any device!
 *
 * NOTE: To ensure backward compatibility with existing drivers method this
 * function calls the &drm_driver.load method after रेजिस्टरing the device
 * nodes, creating race conditions. Usage of the &drm_driver.load methods is
 * thereक्रमe deprecated, drivers must perक्रमm all initialization beक्रमe calling
 * drm_dev_रेजिस्टर().
 *
 * RETURNS:
 * 0 on success, negative error code on failure.
 */
पूर्णांक drm_dev_रेजिस्टर(काष्ठा drm_device *dev, अचिन्हित दीर्घ flags)
अणु
	स्थिर काष्ठा drm_driver *driver = dev->driver;
	पूर्णांक ret;

	अगर (!driver->load)
		drm_mode_config_validate(dev);

	WARN_ON(!dev->managed.final_kमुक्त);

	अगर (drm_dev_needs_global_mutex(dev))
		mutex_lock(&drm_global_mutex);

	ret = drm_minor_रेजिस्टर(dev, DRM_MINOR_RENDER);
	अगर (ret)
		जाओ err_minors;

	ret = drm_minor_रेजिस्टर(dev, DRM_MINOR_PRIMARY);
	अगर (ret)
		जाओ err_minors;

	ret = create_compat_control_link(dev);
	अगर (ret)
		जाओ err_minors;

	dev->रेजिस्टरed = true;

	अगर (dev->driver->load) अणु
		ret = dev->driver->load(dev, flags);
		अगर (ret)
			जाओ err_minors;
	पूर्ण

	अगर (drm_core_check_feature(dev, DRIVER_MODESET))
		drm_modeset_रेजिस्टर_all(dev);

	DRM_INFO("Initialized %s %d.%d.%d %s for %s on minor %d\n",
		 driver->name, driver->major, driver->minor,
		 driver->patchlevel, driver->date,
		 dev->dev ? dev_name(dev->dev) : "virtual device",
		 dev->primary->index);

	जाओ out_unlock;

err_minors:
	हटाओ_compat_control_link(dev);
	drm_minor_unरेजिस्टर(dev, DRM_MINOR_PRIMARY);
	drm_minor_unरेजिस्टर(dev, DRM_MINOR_RENDER);
out_unlock:
	अगर (drm_dev_needs_global_mutex(dev))
		mutex_unlock(&drm_global_mutex);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_dev_रेजिस्टर);

/**
 * drm_dev_unरेजिस्टर - Unरेजिस्टर DRM device
 * @dev: Device to unरेजिस्टर
 *
 * Unरेजिस्टर the DRM device from the प्रणाली. This करोes the reverse of
 * drm_dev_रेजिस्टर() but करोes not deallocate the device. The caller must call
 * drm_dev_put() to drop their final reference.
 *
 * A special क्रमm of unरेजिस्टरing क्रम hotpluggable devices is drm_dev_unplug(),
 * which can be called जबतक there are still खोलो users of @dev.
 *
 * This should be called first in the device tearकरोwn code to make sure
 * userspace can't access the device instance any more.
 */
व्योम drm_dev_unरेजिस्टर(काष्ठा drm_device *dev)
अणु
	अगर (drm_core_check_feature(dev, DRIVER_LEGACY))
		drm_lastबंद(dev);

	dev->रेजिस्टरed = false;

	drm_client_dev_unरेजिस्टर(dev);

	अगर (drm_core_check_feature(dev, DRIVER_MODESET))
		drm_modeset_unरेजिस्टर_all(dev);

	अगर (dev->driver->unload)
		dev->driver->unload(dev);

	अगर (dev->agp)
		drm_pci_agp_destroy(dev);

	drm_legacy_rmmaps(dev);

	हटाओ_compat_control_link(dev);
	drm_minor_unरेजिस्टर(dev, DRM_MINOR_PRIMARY);
	drm_minor_unरेजिस्टर(dev, DRM_MINOR_RENDER);
पूर्ण
EXPORT_SYMBOL(drm_dev_unरेजिस्टर);

/**
 * drm_dev_set_unique - Set the unique name of a DRM device
 * @dev: device of which to set the unique name
 * @name: unique name
 *
 * Sets the unique name of a DRM device using the specअगरied string. This is
 * alपढ़ोy करोne by drm_dev_init(), drivers should only override the शेष
 * unique name क्रम backwards compatibility reasons.
 *
 * Return: 0 on success or a negative error code on failure.
 */
पूर्णांक drm_dev_set_unique(काष्ठा drm_device *dev, स्थिर अक्षर *name)
अणु
	drmm_kमुक्त(dev, dev->unique);
	dev->unique = drmm_kstrdup(dev, name, GFP_KERNEL);

	वापस dev->unique ? 0 : -ENOMEM;
पूर्ण
EXPORT_SYMBOL(drm_dev_set_unique);

/*
 * DRM Core
 * The DRM core module initializes all global DRM objects and makes them
 * available to drivers. Once setup, drivers can probe their respective
 * devices.
 * Currently, core management includes:
 *  - The "DRM-Global" key/value database
 *  - Global ID management क्रम connectors
 *  - DRM major number allocation
 *  - DRM minor management
 *  - DRM sysfs class
 *  - DRM debugfs root
 *
 * Furthermore, the DRM core provides dynamic अक्षर-dev lookups. For each
 * पूर्णांकerface रेजिस्टरed on a DRM device, you can request minor numbers from DRM
 * core. DRM core takes care of major-number management and अक्षर-dev
 * registration. A stub ->खोलो() callback क्रमwards any खोलो() requests to the
 * रेजिस्टरed minor.
 */

अटल पूर्णांक drm_stub_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	स्थिर काष्ठा file_operations *new_fops;
	काष्ठा drm_minor *minor;
	पूर्णांक err;

	DRM_DEBUG("\n");

	minor = drm_minor_acquire(iminor(inode));
	अगर (IS_ERR(minor))
		वापस PTR_ERR(minor);

	new_fops = fops_get(minor->dev->driver->fops);
	अगर (!new_fops) अणु
		err = -ENODEV;
		जाओ out;
	पूर्ण

	replace_fops(filp, new_fops);
	अगर (filp->f_op->खोलो)
		err = filp->f_op->खोलो(inode, filp);
	अन्यथा
		err = 0;

out:
	drm_minor_release(minor);

	वापस err;
पूर्ण

अटल स्थिर काष्ठा file_operations drm_stub_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = drm_stub_खोलो,
	.llseek = noop_llseek,
पूर्ण;

अटल व्योम drm_core_निकास(व्योम)
अणु
	unरेजिस्टर_chrdev(DRM_MAJOR, "drm");
	debugfs_हटाओ(drm_debugfs_root);
	drm_sysfs_destroy();
	idr_destroy(&drm_minors_idr);
	drm_connector_ida_destroy();
पूर्ण

अटल पूर्णांक __init drm_core_init(व्योम)
अणु
	पूर्णांक ret;

	drm_connector_ida_init();
	idr_init(&drm_minors_idr);

	ret = drm_sysfs_init();
	अगर (ret < 0) अणु
		DRM_ERROR("Cannot create DRM class: %d\n", ret);
		जाओ error;
	पूर्ण

	drm_debugfs_root = debugfs_create_dir("dri", शून्य);

	ret = रेजिस्टर_chrdev(DRM_MAJOR, "drm", &drm_stub_fops);
	अगर (ret < 0)
		जाओ error;

	drm_core_init_complete = true;

	DRM_DEBUG("Initialized\n");
	वापस 0;

error:
	drm_core_निकास();
	वापस ret;
पूर्ण

module_init(drm_core_init);
module_निकास(drm_core_निकास);
