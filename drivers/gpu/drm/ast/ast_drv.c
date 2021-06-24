<शैली गुरु>
/*
 * Copyright 2012 Red Hat Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDERS, AUTHORS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 */
/*
 * Authors: Dave Airlie <airlied@redhat.com>
 */

#समावेश <linux/console.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_crtc_helper.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_gem_vram_helper.h>
#समावेश <drm/drm_probe_helper.h>

#समावेश "ast_drv.h"

पूर्णांक ast_modeset = -1;

MODULE_PARM_DESC(modeset, "Disable/Enable modesetting");
module_param_named(modeset, ast_modeset, पूर्णांक, 0400);

/*
 * DRM driver
 */

DEFINE_DRM_GEM_FOPS(ast_fops);

अटल स्थिर काष्ठा drm_driver ast_driver = अणु
	.driver_features = DRIVER_ATOMIC |
			   DRIVER_GEM |
			   DRIVER_MODESET,

	.fops = &ast_fops,
	.name = DRIVER_NAME,
	.desc = DRIVER_DESC,
	.date = DRIVER_DATE,
	.major = DRIVER_MAJOR,
	.minor = DRIVER_MINOR,
	.patchlevel = DRIVER_PATCHLEVEL,

	DRM_GEM_VRAM_DRIVER
पूर्ण;

/*
 * PCI driver
 */

#घोषणा PCI_VENDOR_ASPEED 0x1a03

#घोषणा AST_VGA_DEVICE(id, info) अणु		\
	.class = PCI_BASE_CLASS_DISPLAY << 16,	\
	.class_mask = 0xff0000,			\
	.venकरोr = PCI_VENDOR_ASPEED,			\
	.device = id,				\
	.subvenकरोr = PCI_ANY_ID,		\
	.subdevice = PCI_ANY_ID,		\
	.driver_data = (अचिन्हित दीर्घ) info पूर्ण

अटल स्थिर काष्ठा pci_device_id ast_pciidlist[] = अणु
	AST_VGA_DEVICE(PCI_CHIP_AST2000, शून्य),
	AST_VGA_DEVICE(PCI_CHIP_AST2100, शून्य),
	अणु0, 0, 0पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(pci, ast_pciidlist);

अटल व्योम ast_kick_out_firmware_fb(काष्ठा pci_dev *pdev)
अणु
	काष्ठा apertures_काष्ठा *ap;
	bool primary = false;

	ap = alloc_apertures(1);
	अगर (!ap)
		वापस;

	ap->ranges[0].base = pci_resource_start(pdev, 0);
	ap->ranges[0].size = pci_resource_len(pdev, 0);

#अगर_घोषित CONFIG_X86
	primary = pdev->resource[PCI_ROM_RESOURCE].flags & IORESOURCE_ROM_SHADOW;
#पूर्ण_अगर
	drm_fb_helper_हटाओ_conflicting_framebuffers(ap, "astdrmfb", primary);
	kमुक्त(ap);
पूर्ण

अटल पूर्णांक ast_pci_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा ast_निजी *ast;
	काष्ठा drm_device *dev;
	पूर्णांक ret;

	ast_kick_out_firmware_fb(pdev);

	ret = pcim_enable_device(pdev);
	अगर (ret)
		वापस ret;

	ast = ast_device_create(&ast_driver, pdev, ent->driver_data);
	अगर (IS_ERR(ast))
		वापस PTR_ERR(ast);
	dev = &ast->base;

	ret = drm_dev_रेजिस्टर(dev, ent->driver_data);
	अगर (ret)
		वापस ret;

	drm_fbdev_generic_setup(dev, 32);

	वापस 0;
पूर्ण

अटल व्योम ast_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा drm_device *dev = pci_get_drvdata(pdev);

	drm_dev_unरेजिस्टर(dev);
	drm_atomic_helper_shutकरोwn(dev);
पूर्ण

अटल पूर्णांक ast_drm_मुक्तze(काष्ठा drm_device *dev)
अणु
	पूर्णांक error;

	error = drm_mode_config_helper_suspend(dev);
	अगर (error)
		वापस error;
	pci_save_state(to_pci_dev(dev->dev));
	वापस 0;
पूर्ण

अटल पूर्णांक ast_drm_thaw(काष्ठा drm_device *dev)
अणु
	ast_post_gpu(dev);

	वापस drm_mode_config_helper_resume(dev);
पूर्ण

अटल पूर्णांक ast_drm_resume(काष्ठा drm_device *dev)
अणु
	पूर्णांक ret;

	अगर (pci_enable_device(to_pci_dev(dev->dev)))
		वापस -EIO;

	ret = ast_drm_thaw(dev);
	अगर (ret)
		वापस ret;
	वापस 0;
पूर्ण

अटल पूर्णांक ast_pm_suspend(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा drm_device *ddev = pci_get_drvdata(pdev);
	पूर्णांक error;

	error = ast_drm_मुक्तze(ddev);
	अगर (error)
		वापस error;

	pci_disable_device(pdev);
	pci_set_घातer_state(pdev, PCI_D3hot);
	वापस 0;
पूर्ण

अटल पूर्णांक ast_pm_resume(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा drm_device *ddev = pci_get_drvdata(pdev);
	वापस ast_drm_resume(ddev);
पूर्ण

अटल पूर्णांक ast_pm_मुक्तze(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा drm_device *ddev = pci_get_drvdata(pdev);
	वापस ast_drm_मुक्तze(ddev);
पूर्ण

अटल पूर्णांक ast_pm_thaw(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा drm_device *ddev = pci_get_drvdata(pdev);
	वापस ast_drm_thaw(ddev);
पूर्ण

अटल पूर्णांक ast_pm_घातeroff(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा drm_device *ddev = pci_get_drvdata(pdev);

	वापस ast_drm_मुक्तze(ddev);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops ast_pm_ops = अणु
	.suspend = ast_pm_suspend,
	.resume = ast_pm_resume,
	.मुक्तze = ast_pm_मुक्तze,
	.thaw = ast_pm_thaw,
	.घातeroff = ast_pm_घातeroff,
	.restore = ast_pm_resume,
पूर्ण;

अटल काष्ठा pci_driver ast_pci_driver = अणु
	.name = DRIVER_NAME,
	.id_table = ast_pciidlist,
	.probe = ast_pci_probe,
	.हटाओ = ast_pci_हटाओ,
	.driver.pm = &ast_pm_ops,
पूर्ण;

अटल पूर्णांक __init ast_init(व्योम)
अणु
	अगर (vgacon_text_क्रमce() && ast_modeset == -1)
		वापस -EINVAL;

	अगर (ast_modeset == 0)
		वापस -EINVAL;
	वापस pci_रेजिस्टर_driver(&ast_pci_driver);
पूर्ण
अटल व्योम __निकास ast_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&ast_pci_driver);
पूर्ण

module_init(ast_init);
module_निकास(ast_निकास);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL and additional rights");
