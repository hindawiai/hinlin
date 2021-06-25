<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Hisilicon Hibmc SoC drm driver
 *
 * Based on the bochs drm driver.
 *
 * Copyright (c) 2016 Huawei Limited.
 *
 * Author:
 *	Rongrong Zou <zourongrong@huawei.com>
 *	Rongrong Zou <zourongrong@gmail.com>
 *	Jianhua Li <lijianhua@huawei.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/pci.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_gem_framebuffer_helper.h>
#समावेश <drm/drm_gem_vram_helper.h>
#समावेश <drm/drm_irq.h>
#समावेश <drm/drm_managed.h>
#समावेश <drm/drm_vblank.h>

#समावेश "hibmc_drm_drv.h"
#समावेश "hibmc_drm_regs.h"

DEFINE_DRM_GEM_FOPS(hibmc_fops);

अटल irqवापस_t hibmc_drm_पूर्णांकerrupt(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा drm_device *dev = (काष्ठा drm_device *)arg;
	काष्ठा hibmc_drm_निजी *priv = to_hibmc_drm_निजी(dev);
	u32 status;

	status = पढ़ोl(priv->mmio + HIBMC_RAW_INTERRUPT);

	अगर (status & HIBMC_RAW_INTERRUPT_VBLANK(1)) अणु
		ग_लिखोl(HIBMC_RAW_INTERRUPT_VBLANK(1),
		       priv->mmio + HIBMC_RAW_INTERRUPT);
		drm_handle_vblank(dev, 0);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक hibmc_dumb_create(काष्ठा drm_file *file, काष्ठा drm_device *dev,
			     काष्ठा drm_mode_create_dumb *args)
अणु
	वापस drm_gem_vram_fill_create_dumb(file, dev, 0, 128, args);
पूर्ण

अटल स्थिर काष्ठा drm_driver hibmc_driver = अणु
	.driver_features	= DRIVER_GEM | DRIVER_MODESET | DRIVER_ATOMIC,
	.fops			= &hibmc_fops,
	.name			= "hibmc",
	.date			= "20160828",
	.desc			= "hibmc drm driver",
	.major			= 1,
	.minor			= 0,
	.debugfs_init		= drm_vram_mm_debugfs_init,
	.dumb_create            = hibmc_dumb_create,
	.dumb_map_offset        = drm_gem_vram_driver_dumb_mmap_offset,
	.gem_prime_mmap		= drm_gem_prime_mmap,
	.irq_handler		= hibmc_drm_पूर्णांकerrupt,
पूर्ण;

अटल पूर्णांक __maybe_unused hibmc_pm_suspend(काष्ठा device *dev)
अणु
	काष्ठा drm_device *drm_dev = dev_get_drvdata(dev);

	वापस drm_mode_config_helper_suspend(drm_dev);
पूर्ण

अटल पूर्णांक  __maybe_unused hibmc_pm_resume(काष्ठा device *dev)
अणु
	काष्ठा drm_device *drm_dev = dev_get_drvdata(dev);

	वापस drm_mode_config_helper_resume(drm_dev);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops hibmc_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(hibmc_pm_suspend,
				hibmc_pm_resume)
पूर्ण;

अटल स्थिर काष्ठा drm_mode_config_funcs hibmc_mode_funcs = अणु
	.mode_valid = drm_vram_helper_mode_valid,
	.atomic_check = drm_atomic_helper_check,
	.atomic_commit = drm_atomic_helper_commit,
	.fb_create = drm_gem_fb_create,
पूर्ण;

अटल पूर्णांक hibmc_kms_init(काष्ठा hibmc_drm_निजी *priv)
अणु
	काष्ठा drm_device *dev = &priv->dev;
	पूर्णांक ret;

	ret = drmm_mode_config_init(dev);
	अगर (ret)
		वापस ret;

	dev->mode_config.min_width = 0;
	dev->mode_config.min_height = 0;
	dev->mode_config.max_width = 1920;
	dev->mode_config.max_height = 1200;

	dev->mode_config.fb_base = priv->fb_base;
	dev->mode_config.preferred_depth = 32;
	dev->mode_config.prefer_shaकरोw = 1;

	dev->mode_config.funcs = (व्योम *)&hibmc_mode_funcs;

	ret = hibmc_de_init(priv);
	अगर (ret) अणु
		drm_err(dev, "failed to init de: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = hibmc_vdac_init(priv);
	अगर (ret) अणु
		drm_err(dev, "failed to init vdac: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * It can operate in one of three modes: 0, 1 or Sleep.
 */
व्योम hibmc_set_घातer_mode(काष्ठा hibmc_drm_निजी *priv, u32 घातer_mode)
अणु
	u32 control_value = 0;
	व्योम __iomem   *mmio = priv->mmio;
	u32 input = 1;

	अगर (घातer_mode > HIBMC_PW_MODE_CTL_MODE_SLEEP)
		वापस;

	अगर (घातer_mode == HIBMC_PW_MODE_CTL_MODE_SLEEP)
		input = 0;

	control_value = पढ़ोl(mmio + HIBMC_POWER_MODE_CTRL);
	control_value &= ~(HIBMC_PW_MODE_CTL_MODE_MASK |
			   HIBMC_PW_MODE_CTL_OSC_INPUT_MASK);
	control_value |= HIBMC_FIELD(HIBMC_PW_MODE_CTL_MODE, घातer_mode);
	control_value |= HIBMC_FIELD(HIBMC_PW_MODE_CTL_OSC_INPUT, input);
	ग_लिखोl(control_value, mmio + HIBMC_POWER_MODE_CTRL);
पूर्ण

व्योम hibmc_set_current_gate(काष्ठा hibmc_drm_निजी *priv, अचिन्हित पूर्णांक gate)
अणु
	u32 gate_reg;
	u32 mode;
	व्योम __iomem   *mmio = priv->mmio;

	/* Get current घातer mode. */
	mode = (पढ़ोl(mmio + HIBMC_POWER_MODE_CTRL) &
		HIBMC_PW_MODE_CTL_MODE_MASK) >> HIBMC_PW_MODE_CTL_MODE_SHIFT;

	चयन (mode) अणु
	हाल HIBMC_PW_MODE_CTL_MODE_MODE0:
		gate_reg = HIBMC_MODE0_GATE;
		अवरोध;

	हाल HIBMC_PW_MODE_CTL_MODE_MODE1:
		gate_reg = HIBMC_MODE1_GATE;
		अवरोध;

	शेष:
		gate_reg = HIBMC_MODE0_GATE;
		अवरोध;
	पूर्ण
	ग_लिखोl(gate, mmio + gate_reg);
पूर्ण

अटल व्योम hibmc_hw_config(काष्ठा hibmc_drm_निजी *priv)
अणु
	u32 reg;

	/* On hardware reset, घातer mode 0 is शेष. */
	hibmc_set_घातer_mode(priv, HIBMC_PW_MODE_CTL_MODE_MODE0);

	/* Enable display घातer gate & LOCALMEM घातer gate*/
	reg = पढ़ोl(priv->mmio + HIBMC_CURRENT_GATE);
	reg &= ~HIBMC_CURR_GATE_DISPLAY_MASK;
	reg &= ~HIBMC_CURR_GATE_LOCALMEM_MASK;
	reg |= HIBMC_CURR_GATE_DISPLAY(1);
	reg |= HIBMC_CURR_GATE_LOCALMEM(1);

	hibmc_set_current_gate(priv, reg);

	/*
	 * Reset the memory controller. If the memory controller
	 * is not reset in chip,the प्रणाली might hang when sw accesses
	 * the memory.The memory should be resetted after
	 * changing the MXCLK.
	 */
	reg = पढ़ोl(priv->mmio + HIBMC_MISC_CTRL);
	reg &= ~HIBMC_MSCCTL_LOCALMEM_RESET_MASK;
	reg |= HIBMC_MSCCTL_LOCALMEM_RESET(0);
	ग_लिखोl(reg, priv->mmio + HIBMC_MISC_CTRL);

	reg &= ~HIBMC_MSCCTL_LOCALMEM_RESET_MASK;
	reg |= HIBMC_MSCCTL_LOCALMEM_RESET(1);

	ग_लिखोl(reg, priv->mmio + HIBMC_MISC_CTRL);
पूर्ण

अटल पूर्णांक hibmc_hw_map(काष्ठा hibmc_drm_निजी *priv)
अणु
	काष्ठा drm_device *dev = &priv->dev;
	काष्ठा pci_dev *pdev = to_pci_dev(dev->dev);
	resource_माप_प्रकार addr, size, ioaddr, iosize;

	ioaddr = pci_resource_start(pdev, 1);
	iosize = pci_resource_len(pdev, 1);
	priv->mmio = devm_ioremap(dev->dev, ioaddr, iosize);
	अगर (!priv->mmio) अणु
		drm_err(dev, "Cannot map mmio region\n");
		वापस -ENOMEM;
	पूर्ण

	addr = pci_resource_start(pdev, 0);
	size = pci_resource_len(pdev, 0);
	priv->fb_map = devm_ioremap(dev->dev, addr, size);
	अगर (!priv->fb_map) अणु
		drm_err(dev, "Cannot map framebuffer\n");
		वापस -ENOMEM;
	पूर्ण
	priv->fb_base = addr;
	priv->fb_size = size;

	वापस 0;
पूर्ण

अटल पूर्णांक hibmc_hw_init(काष्ठा hibmc_drm_निजी *priv)
अणु
	पूर्णांक ret;

	ret = hibmc_hw_map(priv);
	अगर (ret)
		वापस ret;

	hibmc_hw_config(priv);

	वापस 0;
पूर्ण

अटल पूर्णांक hibmc_unload(काष्ठा drm_device *dev)
अणु
	drm_atomic_helper_shutकरोwn(dev);

	अगर (dev->irq_enabled)
		drm_irq_uninstall(dev);

	pci_disable_msi(to_pci_dev(dev->dev));

	वापस 0;
पूर्ण

अटल पूर्णांक hibmc_load(काष्ठा drm_device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev->dev);
	काष्ठा hibmc_drm_निजी *priv = to_hibmc_drm_निजी(dev);
	पूर्णांक ret;

	ret = hibmc_hw_init(priv);
	अगर (ret)
		जाओ err;

	ret = drmm_vram_helper_init(dev, pci_resource_start(pdev, 0), priv->fb_size);
	अगर (ret) अणु
		drm_err(dev, "Error initializing VRAM MM; %d\n", ret);
		जाओ err;
	पूर्ण

	ret = hibmc_kms_init(priv);
	अगर (ret)
		जाओ err;

	ret = drm_vblank_init(dev, dev->mode_config.num_crtc);
	अगर (ret) अणु
		drm_err(dev, "failed to initialize vblank: %d\n", ret);
		जाओ err;
	पूर्ण

	ret = pci_enable_msi(pdev);
	अगर (ret) अणु
		drm_warn(dev, "enabling MSI failed: %d\n", ret);
	पूर्ण अन्यथा अणु
		ret = drm_irq_install(dev, pdev->irq);
		अगर (ret)
			drm_warn(dev, "install irq failed: %d\n", ret);
	पूर्ण

	/* reset all the states of crtc/plane/encoder/connector */
	drm_mode_config_reset(dev);

	वापस 0;

err:
	hibmc_unload(dev);
	drm_err(dev, "failed to initialize drm driver: %d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक hibmc_pci_probe(काष्ठा pci_dev *pdev,
			   स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा hibmc_drm_निजी *priv;
	काष्ठा drm_device *dev;
	पूर्णांक ret;

	ret = drm_fb_helper_हटाओ_conflicting_pci_framebuffers(pdev,
								"hibmcdrmfb");
	अगर (ret)
		वापस ret;

	priv = devm_drm_dev_alloc(&pdev->dev, &hibmc_driver,
				  काष्ठा hibmc_drm_निजी, dev);
	अगर (IS_ERR(priv)) अणु
		DRM_ERROR("failed to allocate drm_device\n");
		वापस PTR_ERR(priv);
	पूर्ण

	dev = &priv->dev;
	pci_set_drvdata(pdev, dev);

	ret = pcim_enable_device(pdev);
	अगर (ret) अणु
		drm_err(dev, "failed to enable pci device: %d\n", ret);
		जाओ err_वापस;
	पूर्ण

	ret = hibmc_load(dev);
	अगर (ret) अणु
		drm_err(dev, "failed to load hibmc: %d\n", ret);
		जाओ err_वापस;
	पूर्ण

	ret = drm_dev_रेजिस्टर(dev, 0);
	अगर (ret) अणु
		drm_err(dev, "failed to register drv for userspace access: %d\n",
			  ret);
		जाओ err_unload;
	पूर्ण

	drm_fbdev_generic_setup(dev, dev->mode_config.preferred_depth);

	वापस 0;

err_unload:
	hibmc_unload(dev);
err_वापस:
	वापस ret;
पूर्ण

अटल व्योम hibmc_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा drm_device *dev = pci_get_drvdata(pdev);

	drm_dev_unरेजिस्टर(dev);
	hibmc_unload(dev);
पूर्ण

अटल स्थिर काष्ठा pci_device_id hibmc_pci_table[] = अणु
	अणु PCI_VDEVICE(HUAWEI, 0x1711) पूर्ण,
	अणु0,पूर्ण
पूर्ण;

अटल काष्ठा pci_driver hibmc_pci_driver = अणु
	.name =		"hibmc-drm",
	.id_table =	hibmc_pci_table,
	.probe =	hibmc_pci_probe,
	.हटाओ =	hibmc_pci_हटाओ,
	.driver.pm =    &hibmc_pm_ops,
पूर्ण;

module_pci_driver(hibmc_pci_driver);

MODULE_DEVICE_TABLE(pci, hibmc_pci_table);
MODULE_AUTHOR("RongrongZou <zourongrong@huawei.com>");
MODULE_DESCRIPTION("DRM Driver for Hisilicon Hibmc");
MODULE_LICENSE("GPL v2");
