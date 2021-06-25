<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright (C) 2013-2017 Oracle Corporation
 * This file is based on ast_drv.c
 * Copyright 2012 Red Hat Inc.
 * Authors: Dave Airlie <airlied@redhat.com>
 *          Michael Thayer <michael.thayer@oracle.com,
 *          Hans de Goede <hdegoede@redhat.com>
 */
#समावेश <linux/console.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/vt_kern.h>

#समावेश <drm/drm_crtc_helper.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_ioctl.h>
#समावेश <drm/drm_managed.h>

#समावेश "vbox_drv.h"

अटल पूर्णांक vbox_modeset = -1;

MODULE_PARM_DESC(modeset, "Disable/Enable modesetting");
module_param_named(modeset, vbox_modeset, पूर्णांक, 0400);

अटल स्थिर काष्ठा drm_driver driver;

अटल स्थिर काष्ठा pci_device_id pciidlist[] = अणु
	अणु PCI_DEVICE(0x80ee, 0xbeef) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, pciidlist);

अटल पूर्णांक vbox_pci_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा vbox_निजी *vbox;
	पूर्णांक ret = 0;

	अगर (!vbox_check_supported(VBE_DISPI_ID_HGSMI))
		वापस -ENODEV;

	ret = drm_fb_helper_हटाओ_conflicting_pci_framebuffers(pdev, "vboxvideodrmfb");
	अगर (ret)
		वापस ret;

	vbox = devm_drm_dev_alloc(&pdev->dev, &driver,
				  काष्ठा vbox_निजी, ddev);
	अगर (IS_ERR(vbox))
		वापस PTR_ERR(vbox);

	pci_set_drvdata(pdev, vbox);
	mutex_init(&vbox->hw_mutex);

	ret = pcim_enable_device(pdev);
	अगर (ret)
		वापस ret;

	ret = vbox_hw_init(vbox);
	अगर (ret)
		वापस ret;

	ret = vbox_mm_init(vbox);
	अगर (ret)
		जाओ err_hw_fini;

	ret = vbox_mode_init(vbox);
	अगर (ret)
		जाओ err_mm_fini;

	ret = vbox_irq_init(vbox);
	अगर (ret)
		जाओ err_mode_fini;

	ret = drm_dev_रेजिस्टर(&vbox->ddev, 0);
	अगर (ret)
		जाओ err_irq_fini;

	drm_fbdev_generic_setup(&vbox->ddev, 32);

	वापस 0;

err_irq_fini:
	vbox_irq_fini(vbox);
err_mode_fini:
	vbox_mode_fini(vbox);
err_mm_fini:
	vbox_mm_fini(vbox);
err_hw_fini:
	vbox_hw_fini(vbox);
	वापस ret;
पूर्ण

अटल व्योम vbox_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा vbox_निजी *vbox = pci_get_drvdata(pdev);

	drm_dev_unरेजिस्टर(&vbox->ddev);
	vbox_irq_fini(vbox);
	vbox_mode_fini(vbox);
	vbox_mm_fini(vbox);
	vbox_hw_fini(vbox);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक vbox_pm_suspend(काष्ठा device *dev)
अणु
	काष्ठा vbox_निजी *vbox = dev_get_drvdata(dev);
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	पूर्णांक error;

	error = drm_mode_config_helper_suspend(&vbox->ddev);
	अगर (error)
		वापस error;

	pci_save_state(pdev);
	pci_disable_device(pdev);
	pci_set_घातer_state(pdev, PCI_D3hot);

	वापस 0;
पूर्ण

अटल पूर्णांक vbox_pm_resume(काष्ठा device *dev)
अणु
	काष्ठा vbox_निजी *vbox = dev_get_drvdata(dev);
	काष्ठा pci_dev *pdev = to_pci_dev(dev);

	अगर (pci_enable_device(pdev))
		वापस -EIO;

	वापस drm_mode_config_helper_resume(&vbox->ddev);
पूर्ण

अटल पूर्णांक vbox_pm_मुक्तze(काष्ठा device *dev)
अणु
	काष्ठा vbox_निजी *vbox = dev_get_drvdata(dev);

	वापस drm_mode_config_helper_suspend(&vbox->ddev);
पूर्ण

अटल पूर्णांक vbox_pm_thaw(काष्ठा device *dev)
अणु
	काष्ठा vbox_निजी *vbox = dev_get_drvdata(dev);

	वापस drm_mode_config_helper_resume(&vbox->ddev);
पूर्ण

अटल पूर्णांक vbox_pm_घातeroff(काष्ठा device *dev)
अणु
	काष्ठा vbox_निजी *vbox = dev_get_drvdata(dev);

	वापस drm_mode_config_helper_suspend(&vbox->ddev);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops vbox_pm_ops = अणु
	.suspend = vbox_pm_suspend,
	.resume = vbox_pm_resume,
	.मुक्तze = vbox_pm_मुक्तze,
	.thaw = vbox_pm_thaw,
	.घातeroff = vbox_pm_घातeroff,
	.restore = vbox_pm_resume,
पूर्ण;
#पूर्ण_अगर

अटल काष्ठा pci_driver vbox_pci_driver = अणु
	.name = DRIVER_NAME,
	.id_table = pciidlist,
	.probe = vbox_pci_probe,
	.हटाओ = vbox_pci_हटाओ,
#अगर_घोषित CONFIG_PM_SLEEP
	.driver.pm = &vbox_pm_ops,
#पूर्ण_अगर
पूर्ण;

DEFINE_DRM_GEM_FOPS(vbox_fops);

अटल स्थिर काष्ठा drm_driver driver = अणु
	.driver_features =
	    DRIVER_MODESET | DRIVER_GEM | DRIVER_ATOMIC,

	.lastबंद = drm_fb_helper_lastबंद,

	.fops = &vbox_fops,
	.irq_handler = vbox_irq_handler,
	.name = DRIVER_NAME,
	.desc = DRIVER_DESC,
	.date = DRIVER_DATE,
	.major = DRIVER_MAJOR,
	.minor = DRIVER_MINOR,
	.patchlevel = DRIVER_PATCHLEVEL,

	DRM_GEM_VRAM_DRIVER,
पूर्ण;

अटल पूर्णांक __init vbox_init(व्योम)
अणु
#अगर_घोषित CONFIG_VGA_CONSOLE
	अगर (vgacon_text_क्रमce() && vbox_modeset == -1)
		वापस -EINVAL;
#पूर्ण_अगर

	अगर (vbox_modeset == 0)
		वापस -EINVAL;

	वापस pci_रेजिस्टर_driver(&vbox_pci_driver);
पूर्ण

अटल व्योम __निकास vbox_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&vbox_pci_driver);
पूर्ण

module_init(vbox_init);
module_निकास(vbox_निकास);

MODULE_AUTHOR("Oracle Corporation");
MODULE_AUTHOR("Hans de Goede <hdegoede@redhat.com>");
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL and additional rights");
