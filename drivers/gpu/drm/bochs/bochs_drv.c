<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 */

#समावेश <linux/module.h>
#समावेश <linux/pci.h>

#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_managed.h>

#समावेश "bochs.h"

अटल पूर्णांक bochs_modeset = -1;
module_param_named(modeset, bochs_modeset, पूर्णांक, 0444);
MODULE_PARM_DESC(modeset, "enable/disable kernel modesetting");

/* ---------------------------------------------------------------------- */
/* drm पूर्णांकerface                                                          */

अटल व्योम bochs_unload(काष्ठा drm_device *dev)
अणु
	काष्ठा bochs_device *bochs = dev->dev_निजी;

	bochs_mm_fini(bochs);
पूर्ण

अटल पूर्णांक bochs_load(काष्ठा drm_device *dev)
अणु
	काष्ठा bochs_device *bochs;
	पूर्णांक ret;

	bochs = drmm_kzalloc(dev, माप(*bochs), GFP_KERNEL);
	अगर (bochs == शून्य)
		वापस -ENOMEM;
	dev->dev_निजी = bochs;
	bochs->dev = dev;

	ret = bochs_hw_init(dev);
	अगर (ret)
		जाओ err;

	ret = bochs_mm_init(bochs);
	अगर (ret)
		जाओ err;

	ret = bochs_kms_init(bochs);
	अगर (ret)
		जाओ err;

	वापस 0;

err:
	bochs_unload(dev);
	वापस ret;
पूर्ण

DEFINE_DRM_GEM_FOPS(bochs_fops);

अटल स्थिर काष्ठा drm_driver bochs_driver = अणु
	.driver_features	= DRIVER_GEM | DRIVER_MODESET | DRIVER_ATOMIC,
	.fops			= &bochs_fops,
	.name			= "bochs-drm",
	.desc			= "bochs dispi vga interface (qemu stdvga)",
	.date			= "20130925",
	.major			= 1,
	.minor			= 0,
	DRM_GEM_VRAM_DRIVER,
	.release                = bochs_unload,
पूर्ण;

/* ---------------------------------------------------------------------- */
/* pm पूर्णांकerface                                                           */

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक bochs_pm_suspend(काष्ठा device *dev)
अणु
	काष्ठा drm_device *drm_dev = dev_get_drvdata(dev);

	वापस drm_mode_config_helper_suspend(drm_dev);
पूर्ण

अटल पूर्णांक bochs_pm_resume(काष्ठा device *dev)
अणु
	काष्ठा drm_device *drm_dev = dev_get_drvdata(dev);

	वापस drm_mode_config_helper_resume(drm_dev);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops bochs_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(bochs_pm_suspend,
				bochs_pm_resume)
पूर्ण;

/* ---------------------------------------------------------------------- */
/* pci पूर्णांकerface                                                          */

अटल पूर्णांक bochs_pci_probe(काष्ठा pci_dev *pdev,
			   स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा drm_device *dev;
	अचिन्हित दीर्घ fbsize;
	पूर्णांक ret;

	fbsize = pci_resource_len(pdev, 0);
	अगर (fbsize < 4 * 1024 * 1024) अणु
		DRM_ERROR("less than 4 MB video memory, ignoring device\n");
		वापस -ENOMEM;
	पूर्ण

	ret = drm_fb_helper_हटाओ_conflicting_pci_framebuffers(pdev, "bochsdrmfb");
	अगर (ret)
		वापस ret;

	dev = drm_dev_alloc(&bochs_driver, &pdev->dev);
	अगर (IS_ERR(dev))
		वापस PTR_ERR(dev);

	ret = pci_enable_device(pdev);
	अगर (ret)
		जाओ err_मुक्त_dev;

	pci_set_drvdata(pdev, dev);

	ret = bochs_load(dev);
	अगर (ret)
		जाओ err_मुक्त_dev;

	ret = drm_dev_रेजिस्टर(dev, 0);
	अगर (ret)
		जाओ err_unload;

	drm_fbdev_generic_setup(dev, 32);
	वापस ret;

err_unload:
	bochs_unload(dev);
err_मुक्त_dev:
	drm_dev_put(dev);
	वापस ret;
पूर्ण

अटल व्योम bochs_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा drm_device *dev = pci_get_drvdata(pdev);

	drm_dev_unplug(dev);
	drm_atomic_helper_shutकरोwn(dev);
	bochs_hw_fini(dev);
	drm_dev_put(dev);
पूर्ण

अटल स्थिर काष्ठा pci_device_id bochs_pci_tbl[] = अणु
	अणु
		.venकरोr      = 0x1234,
		.device      = 0x1111,
		.subvenकरोr   = PCI_SUBVENDOR_ID_REDHAT_QUMRANET,
		.subdevice   = PCI_SUBDEVICE_ID_QEMU,
		.driver_data = BOCHS_QEMU_STDVGA,
	पूर्ण,
	अणु
		.venकरोr      = 0x1234,
		.device      = 0x1111,
		.subvenकरोr   = PCI_ANY_ID,
		.subdevice   = PCI_ANY_ID,
		.driver_data = BOCHS_UNKNOWN,
	पूर्ण,
	अणु /* end of list */ पूर्ण
पूर्ण;

अटल काष्ठा pci_driver bochs_pci_driver = अणु
	.name =		"bochs-drm",
	.id_table =	bochs_pci_tbl,
	.probe =	bochs_pci_probe,
	.हटाओ =	bochs_pci_हटाओ,
	.driver.pm =    &bochs_pm_ops,
पूर्ण;

/* ---------------------------------------------------------------------- */
/* module init/निकास                                                       */

अटल पूर्णांक __init bochs_init(व्योम)
अणु
	अगर (vgacon_text_क्रमce() && bochs_modeset == -1)
		वापस -EINVAL;

	अगर (bochs_modeset == 0)
		वापस -EINVAL;

	वापस pci_रेजिस्टर_driver(&bochs_pci_driver);
पूर्ण

अटल व्योम __निकास bochs_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&bochs_pci_driver);
पूर्ण

module_init(bochs_init);
module_निकास(bochs_निकास);

MODULE_DEVICE_TABLE(pci, bochs_pci_tbl);
MODULE_AUTHOR("Gerd Hoffmann <kraxel@redhat.com>");
MODULE_LICENSE("GPL");
