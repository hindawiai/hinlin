<शैली गुरु>
/* qxl_drv.c -- QXL driver -*- linux-c -*-
 *
 * Copyright 2011 Red Hat, Inc.
 * All Rights Reserved.
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
 *
 * Authors:
 *    Dave Airlie <airlie@redhat.com>
 *    Alon Levy <alevy@redhat.com>
 */

#समावेश "qxl_drv.h"
#समावेश <linux/console.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>

#समावेश <drm/drm.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_modeset_helper.h>
#समावेश <drm/drm_prime.h>
#समावेश <drm/drm_probe_helper.h>

#समावेश "qxl_object.h"

अटल स्थिर काष्ठा pci_device_id pciidlist[] = अणु
	अणु 0x1b36, 0x100, PCI_ANY_ID, PCI_ANY_ID, PCI_CLASS_DISPLAY_VGA << 8,
	  0xffff00, 0 पूर्ण,
	अणु 0x1b36, 0x100, PCI_ANY_ID, PCI_ANY_ID, PCI_CLASS_DISPLAY_OTHER << 8,
	  0xffff00, 0 पूर्ण,
	अणु 0, 0, 0 पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(pci, pciidlist);

अटल पूर्णांक qxl_modeset = -1;
पूर्णांक qxl_num_crtc = 4;

MODULE_PARM_DESC(modeset, "Disable/Enable modesetting");
module_param_named(modeset, qxl_modeset, पूर्णांक, 0400);

MODULE_PARM_DESC(num_heads, "Number of virtual crtcs to expose (default 4)");
module_param_named(num_heads, qxl_num_crtc, पूर्णांक, 0400);

अटल काष्ठा drm_driver qxl_driver;
अटल काष्ठा pci_driver qxl_pci_driver;

अटल bool is_vga(काष्ठा pci_dev *pdev)
अणु
	वापस pdev->class == PCI_CLASS_DISPLAY_VGA << 8;
पूर्ण

अटल पूर्णांक
qxl_pci_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा qxl_device *qdev;
	पूर्णांक ret;

	अगर (pdev->revision < 4) अणु
		DRM_ERROR("qxl too old, doesn't support client_monitors_config,"
			  " use xf86-video-qxl in user mode");
		वापस -EINVAL; /* TODO: ENODEV ? */
	पूर्ण

	qdev = devm_drm_dev_alloc(&pdev->dev, &qxl_driver,
				  काष्ठा qxl_device, ddev);
	अगर (IS_ERR(qdev)) अणु
		pr_err("Unable to init drm dev");
		वापस -ENOMEM;
	पूर्ण

	ret = pci_enable_device(pdev);
	अगर (ret)
		वापस ret;

	ret = drm_fb_helper_हटाओ_conflicting_pci_framebuffers(pdev, "qxl");
	अगर (ret)
		जाओ disable_pci;

	अगर (is_vga(pdev) && pdev->revision < 5) अणु
		ret = vga_get_पूर्णांकerruptible(pdev, VGA_RSRC_LEGACY_IO);
		अगर (ret) अणु
			DRM_ERROR("can't get legacy vga ioports\n");
			जाओ disable_pci;
		पूर्ण
	पूर्ण

	ret = qxl_device_init(qdev, pdev);
	अगर (ret)
		जाओ put_vga;

	ret = qxl_modeset_init(qdev);
	अगर (ret)
		जाओ unload;

	drm_kms_helper_poll_init(&qdev->ddev);

	/* Complete initialization. */
	ret = drm_dev_रेजिस्टर(&qdev->ddev, ent->driver_data);
	अगर (ret)
		जाओ modeset_cleanup;

	drm_fbdev_generic_setup(&qdev->ddev, 32);
	वापस 0;

modeset_cleanup:
	qxl_modeset_fini(qdev);
unload:
	qxl_device_fini(qdev);
put_vga:
	अगर (is_vga(pdev) && pdev->revision < 5)
		vga_put(pdev, VGA_RSRC_LEGACY_IO);
disable_pci:
	pci_disable_device(pdev);

	वापस ret;
पूर्ण

अटल व्योम qxl_drm_release(काष्ठा drm_device *dev)
अणु
	काष्ठा qxl_device *qdev = to_qxl(dev);

	/*
	 * TODO: qxl_device_fini() call should be in qxl_pci_हटाओ(),
	 * reordering qxl_modeset_fini() + qxl_device_fini() calls is
	 * non-trivial though.
	 */
	qxl_modeset_fini(qdev);
	qxl_device_fini(qdev);
पूर्ण

अटल व्योम
qxl_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा drm_device *dev = pci_get_drvdata(pdev);

	drm_dev_unरेजिस्टर(dev);
	drm_atomic_helper_shutकरोwn(dev);
	अगर (is_vga(pdev) && pdev->revision < 5)
		vga_put(pdev, VGA_RSRC_LEGACY_IO);
पूर्ण

DEFINE_DRM_GEM_FOPS(qxl_fops);

अटल पूर्णांक qxl_drm_मुक्तze(काष्ठा drm_device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev->dev);
	काष्ठा qxl_device *qdev = to_qxl(dev);
	पूर्णांक ret;

	ret = drm_mode_config_helper_suspend(dev);
	अगर (ret)
		वापस ret;

	qxl_destroy_monitors_object(qdev);
	qxl_surf_evict(qdev);
	qxl_vram_evict(qdev);

	जबतक (!qxl_check_idle(qdev->command_ring));
	जबतक (!qxl_check_idle(qdev->release_ring))
		qxl_queue_garbage_collect(qdev, 1);

	pci_save_state(pdev);

	वापस 0;
पूर्ण

अटल पूर्णांक qxl_drm_resume(काष्ठा drm_device *dev, bool thaw)
अणु
	काष्ठा qxl_device *qdev = to_qxl(dev);

	qdev->ram_header->पूर्णांक_mask = QXL_INTERRUPT_MASK;
	अगर (!thaw) अणु
		qxl_reinit_memslots(qdev);
		qxl_ring_init_hdr(qdev->release_ring);
	पूर्ण

	qxl_create_monitors_object(qdev);
	वापस drm_mode_config_helper_resume(dev);
पूर्ण

अटल पूर्णांक qxl_pm_suspend(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा drm_device *drm_dev = pci_get_drvdata(pdev);
	पूर्णांक error;

	error = qxl_drm_मुक्तze(drm_dev);
	अगर (error)
		वापस error;

	pci_disable_device(pdev);
	pci_set_घातer_state(pdev, PCI_D3hot);
	वापस 0;
पूर्ण

अटल पूर्णांक qxl_pm_resume(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा drm_device *drm_dev = pci_get_drvdata(pdev);

	pci_set_घातer_state(pdev, PCI_D0);
	pci_restore_state(pdev);
	अगर (pci_enable_device(pdev)) अणु
		वापस -EIO;
	पूर्ण

	वापस qxl_drm_resume(drm_dev, false);
पूर्ण

अटल पूर्णांक qxl_pm_thaw(काष्ठा device *dev)
अणु
	काष्ठा drm_device *drm_dev = dev_get_drvdata(dev);

	वापस qxl_drm_resume(drm_dev, true);
पूर्ण

अटल पूर्णांक qxl_pm_मुक्तze(काष्ठा device *dev)
अणु
	काष्ठा drm_device *drm_dev = dev_get_drvdata(dev);

	वापस qxl_drm_मुक्तze(drm_dev);
पूर्ण

अटल पूर्णांक qxl_pm_restore(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा drm_device *drm_dev = pci_get_drvdata(pdev);
	काष्ठा qxl_device *qdev = to_qxl(drm_dev);

	qxl_io_reset(qdev);
	वापस qxl_drm_resume(drm_dev, false);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops qxl_pm_ops = अणु
	.suspend = qxl_pm_suspend,
	.resume = qxl_pm_resume,
	.मुक्तze = qxl_pm_मुक्तze,
	.thaw = qxl_pm_thaw,
	.घातeroff = qxl_pm_मुक्तze,
	.restore = qxl_pm_restore,
पूर्ण;
अटल काष्ठा pci_driver qxl_pci_driver = अणु
	 .name = DRIVER_NAME,
	 .id_table = pciidlist,
	 .probe = qxl_pci_probe,
	 .हटाओ = qxl_pci_हटाओ,
	 .driver.pm = &qxl_pm_ops,
पूर्ण;

अटल काष्ठा drm_driver qxl_driver = अणु
	.driver_features = DRIVER_GEM | DRIVER_MODESET | DRIVER_ATOMIC,

	.dumb_create = qxl_mode_dumb_create,
	.dumb_map_offset = qxl_mode_dumb_mmap,
#अगर defined(CONFIG_DEBUG_FS)
	.debugfs_init = qxl_debugfs_init,
#पूर्ण_अगर
	.prime_handle_to_fd = drm_gem_prime_handle_to_fd,
	.prime_fd_to_handle = drm_gem_prime_fd_to_handle,
	.gem_prime_import_sg_table = qxl_gem_prime_import_sg_table,
	.gem_prime_mmap = qxl_gem_prime_mmap,
	.fops = &qxl_fops,
	.ioctls = qxl_ioctls,
	.irq_handler = qxl_irq_handler,
	.name = DRIVER_NAME,
	.desc = DRIVER_DESC,
	.date = DRIVER_DATE,
	.major = 0,
	.minor = 1,
	.patchlevel = 0,

	.release = qxl_drm_release,
पूर्ण;

अटल पूर्णांक __init qxl_init(व्योम)
अणु
	अगर (vgacon_text_क्रमce() && qxl_modeset == -1)
		वापस -EINVAL;

	अगर (qxl_modeset == 0)
		वापस -EINVAL;
	qxl_driver.num_ioctls = qxl_max_ioctls;
	वापस pci_रेजिस्टर_driver(&qxl_pci_driver);
पूर्ण

अटल व्योम __निकास qxl_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&qxl_pci_driver);
पूर्ण

module_init(qxl_init);
module_निकास(qxl_निकास);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL and additional rights");
