<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Synopsys DesignWare I2C adapter driver (master only).
 *
 * Based on the TI DAVINCI I2C adapter driver.
 *
 * Copyright (C) 2006 Texas Instruments.
 * Copyright (C) 2007 MontaVista Software Inc.
 * Copyright (C) 2009 Provigent Ltd.
 * Copyright (C) 2011, 2015, 2016 Intel Corporation.
 */
#समावेश <linux/acpi.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>

#समावेश "i2c-designware-core.h"

#घोषणा DRIVER_NAME "i2c-designware-pci"
#घोषणा AMD_CLK_RATE_HZ	100000

क्रमागत dw_pci_ctl_id_t अणु
	medfield,
	merrअगरield,
	baytrail,
	cherrytrail,
	haswell,
	elkhartlake,
	navi_amd,
पूर्ण;

काष्ठा dw_scl_sda_cfg अणु
	u32 ss_hcnt;
	u32 fs_hcnt;
	u32 ss_lcnt;
	u32 fs_lcnt;
	u32 sda_hold;
पूर्ण;

काष्ठा dw_pci_controller अणु
	u32 bus_num;
	u32 flags;
	काष्ठा dw_scl_sda_cfg *scl_sda_cfg;
	पूर्णांक (*setup)(काष्ठा pci_dev *pdev, काष्ठा dw_pci_controller *c);
	u32 (*get_clk_rate_khz)(काष्ठा dw_i2c_dev *dev);
पूर्ण;

/* Merrअगरield HCNT/LCNT/SDA hold समय */
अटल काष्ठा dw_scl_sda_cfg mrfld_config = अणु
	.ss_hcnt = 0x2f8,
	.fs_hcnt = 0x87,
	.ss_lcnt = 0x37b,
	.fs_lcnt = 0x10a,
पूर्ण;

/* BayTrail HCNT/LCNT/SDA hold समय */
अटल काष्ठा dw_scl_sda_cfg byt_config = अणु
	.ss_hcnt = 0x200,
	.fs_hcnt = 0x55,
	.ss_lcnt = 0x200,
	.fs_lcnt = 0x99,
	.sda_hold = 0x6,
पूर्ण;

/* Haswell HCNT/LCNT/SDA hold समय */
अटल काष्ठा dw_scl_sda_cfg hsw_config = अणु
	.ss_hcnt = 0x01b0,
	.fs_hcnt = 0x48,
	.ss_lcnt = 0x01fb,
	.fs_lcnt = 0xa0,
	.sda_hold = 0x9,
पूर्ण;

/* NAVI-AMD HCNT/LCNT/SDA hold समय */
अटल काष्ठा dw_scl_sda_cfg navi_amd_config = अणु
	.ss_hcnt = 0x1ae,
	.ss_lcnt = 0x23a,
	.sda_hold = 0x9,
पूर्ण;

अटल u32 mfld_get_clk_rate_khz(काष्ठा dw_i2c_dev *dev)
अणु
	वापस 25000;
पूर्ण

अटल u32 navi_amd_get_clk_rate_khz(काष्ठा dw_i2c_dev *dev)
अणु
	वापस AMD_CLK_RATE_HZ;
पूर्ण

अटल पूर्णांक mfld_setup(काष्ठा pci_dev *pdev, काष्ठा dw_pci_controller *c)
अणु
	काष्ठा dw_i2c_dev *dev = dev_get_drvdata(&pdev->dev);

	चयन (pdev->device) अणु
	हाल 0x0817:
		dev->timings.bus_freq_hz = I2C_MAX_STANDARD_MODE_FREQ;
		fallthrough;
	हाल 0x0818:
	हाल 0x0819:
		c->bus_num = pdev->device - 0x817 + 3;
		वापस 0;
	हाल 0x082C:
	हाल 0x082D:
	हाल 0x082E:
		c->bus_num = pdev->device - 0x82C + 0;
		वापस 0;
	पूर्ण
	वापस -ENODEV;
पूर्ण

 /*
  * TODO find a better way how to deduplicate instantiation
  * of USB PD slave device from nVidia GPU driver.
  */
अटल पूर्णांक navi_amd_रेजिस्टर_client(काष्ठा dw_i2c_dev *dev)
अणु
	काष्ठा i2c_board_info	info;

	स_रखो(&info, 0, माप(काष्ठा i2c_board_info));
	strscpy(info.type, "ccgx-ucsi", I2C_NAME_SIZE);
	info.addr = 0x08;
	info.irq = dev->irq;

	dev->slave = i2c_new_client_device(&dev->adapter, &info);
	अगर (IS_ERR(dev->slave))
		वापस PTR_ERR(dev->slave);

	वापस 0;
पूर्ण

अटल पूर्णांक navi_amd_setup(काष्ठा pci_dev *pdev, काष्ठा dw_pci_controller *c)
अणु
	काष्ठा dw_i2c_dev *dev = dev_get_drvdata(&pdev->dev);

	dev->flags |= MODEL_AMD_NAVI_GPU;
	dev->timings.bus_freq_hz = I2C_MAX_STANDARD_MODE_FREQ;
	वापस 0;
पूर्ण

अटल पूर्णांक mrfld_setup(काष्ठा pci_dev *pdev, काष्ठा dw_pci_controller *c)
अणु
	/*
	 * On Intel Merrअगरield the user visible i2c buses are क्रमागतerated
	 * [1..7]. So, we add 1 to shअगरt the शेष range. Besides that the
	 * first PCI slot provides 4 functions, that's why we have to add 0 to
	 * the first slot and 4 to the next one.
	 */
	चयन (PCI_SLOT(pdev->devfn)) अणु
	हाल 8:
		c->bus_num = PCI_FUNC(pdev->devfn) + 0 + 1;
		वापस 0;
	हाल 9:
		c->bus_num = PCI_FUNC(pdev->devfn) + 4 + 1;
		वापस 0;
	पूर्ण
	वापस -ENODEV;
पूर्ण

अटल u32 ehl_get_clk_rate_khz(काष्ठा dw_i2c_dev *dev)
अणु
	वापस 100000;
पूर्ण

अटल काष्ठा dw_pci_controller dw_pci_controllers[] = अणु
	[medfield] = अणु
		.bus_num = -1,
		.setup = mfld_setup,
		.get_clk_rate_khz = mfld_get_clk_rate_khz,
	पूर्ण,
	[merrअगरield] = अणु
		.bus_num = -1,
		.scl_sda_cfg = &mrfld_config,
		.setup = mrfld_setup,
	पूर्ण,
	[baytrail] = अणु
		.bus_num = -1,
		.scl_sda_cfg = &byt_config,
	पूर्ण,
	[haswell] = अणु
		.bus_num = -1,
		.scl_sda_cfg = &hsw_config,
	पूर्ण,
	[cherrytrail] = अणु
		.bus_num = -1,
		.scl_sda_cfg = &byt_config,
	पूर्ण,
	[elkhartlake] = अणु
		.bus_num = -1,
		.get_clk_rate_khz = ehl_get_clk_rate_khz,
	पूर्ण,
	[navi_amd] = अणु
		.bus_num = -1,
		.scl_sda_cfg = &navi_amd_config,
		.setup =  navi_amd_setup,
		.get_clk_rate_khz = navi_amd_get_clk_rate_khz,
	पूर्ण,
पूर्ण;

#अगर_घोषित CONFIG_PM
अटल पूर्णांक i2c_dw_pci_suspend(काष्ठा device *dev)
अणु
	काष्ठा dw_i2c_dev *i_dev = dev_get_drvdata(dev);

	i_dev->suspended = true;
	i_dev->disable(i_dev);

	वापस 0;
पूर्ण

अटल पूर्णांक i2c_dw_pci_resume(काष्ठा device *dev)
अणु
	काष्ठा dw_i2c_dev *i_dev = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = i_dev->init(i_dev);
	i_dev->suspended = false;

	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल UNIVERSAL_DEV_PM_OPS(i2c_dw_pm_ops, i2c_dw_pci_suspend,
			    i2c_dw_pci_resume, शून्य);

अटल पूर्णांक i2c_dw_pci_probe(काष्ठा pci_dev *pdev,
			    स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा dw_i2c_dev *dev;
	काष्ठा i2c_adapter *adap;
	पूर्णांक r;
	काष्ठा dw_pci_controller *controller;
	काष्ठा dw_scl_sda_cfg *cfg;

	अगर (id->driver_data >= ARRAY_SIZE(dw_pci_controllers)) अणु
		dev_err(&pdev->dev, "%s: invalid driver data %ld\n", __func__,
			id->driver_data);
		वापस -EINVAL;
	पूर्ण

	controller = &dw_pci_controllers[id->driver_data];

	r = pcim_enable_device(pdev);
	अगर (r) अणु
		dev_err(&pdev->dev, "Failed to enable I2C PCI device (%d)\n",
			r);
		वापस r;
	पूर्ण

	pci_set_master(pdev);

	r = pcim_iomap_regions(pdev, 1 << 0, pci_name(pdev));
	अगर (r) अणु
		dev_err(&pdev->dev, "I/O memory remapping failed\n");
		वापस r;
	पूर्ण

	dev = devm_kzalloc(&pdev->dev, माप(काष्ठा dw_i2c_dev), GFP_KERNEL);
	अगर (!dev)
		वापस -ENOMEM;

	r = pci_alloc_irq_vectors(pdev, 1, 1, PCI_IRQ_ALL_TYPES);
	अगर (r < 0)
		वापस r;

	dev->get_clk_rate_khz = controller->get_clk_rate_khz;
	dev->timings.bus_freq_hz = I2C_MAX_FAST_MODE_FREQ;
	dev->base = pcim_iomap_table(pdev)[0];
	dev->dev = &pdev->dev;
	dev->irq = pci_irq_vector(pdev, 0);
	dev->flags |= controller->flags;

	pci_set_drvdata(pdev, dev);

	अगर (controller->setup) अणु
		r = controller->setup(pdev, controller);
		अगर (r) अणु
			pci_मुक्त_irq_vectors(pdev);
			वापस r;
		पूर्ण
	पूर्ण

	i2c_dw_adjust_bus_speed(dev);

	अगर (has_acpi_companion(&pdev->dev))
		i2c_dw_acpi_configure(&pdev->dev);

	r = i2c_dw_validate_speed(dev);
	अगर (r) अणु
		pci_मुक्त_irq_vectors(pdev);
		वापस r;
	पूर्ण

	i2c_dw_configure(dev);

	अगर (controller->scl_sda_cfg) अणु
		cfg = controller->scl_sda_cfg;
		dev->ss_hcnt = cfg->ss_hcnt;
		dev->fs_hcnt = cfg->fs_hcnt;
		dev->ss_lcnt = cfg->ss_lcnt;
		dev->fs_lcnt = cfg->fs_lcnt;
		dev->sda_hold_समय = cfg->sda_hold;
	पूर्ण

	adap = &dev->adapter;
	adap->owner = THIS_MODULE;
	adap->class = 0;
	ACPI_COMPANION_SET(&adap->dev, ACPI_COMPANION(&pdev->dev));
	adap->nr = controller->bus_num;

	r = i2c_dw_probe(dev);
	अगर (r) अणु
		pci_मुक्त_irq_vectors(pdev);
		वापस r;
	पूर्ण

	अगर ((dev->flags & MODEL_MASK) == MODEL_AMD_NAVI_GPU) अणु
		r = navi_amd_रेजिस्टर_client(dev);
		अगर (r) अणु
			dev_err(dev->dev, "register client failed with %d\n", r);
			वापस r;
		पूर्ण
	पूर्ण

	pm_runसमय_set_स्वतःsuspend_delay(&pdev->dev, 1000);
	pm_runसमय_use_स्वतःsuspend(&pdev->dev);
	pm_runसमय_put_स्वतःsuspend(&pdev->dev);
	pm_runसमय_allow(&pdev->dev);

	वापस 0;
पूर्ण

अटल व्योम i2c_dw_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा dw_i2c_dev *dev = pci_get_drvdata(pdev);

	dev->disable(dev);
	pm_runसमय_क्रमbid(&pdev->dev);
	pm_runसमय_get_noresume(&pdev->dev);

	i2c_del_adapter(&dev->adapter);
	devm_मुक्त_irq(&pdev->dev, dev->irq, dev);
	pci_मुक्त_irq_vectors(pdev);
पूर्ण

/* work with hotplug and coldplug */
MODULE_ALIAS("i2c_designware-pci");

अटल स्थिर काष्ठा pci_device_id i2_designware_pci_ids[] = अणु
	/* Medfield */
	अणु PCI_VDEVICE(INTEL, 0x0817), medfield पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x0818), medfield पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x0819), medfield पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x082C), medfield पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x082D), medfield पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x082E), medfield पूर्ण,
	/* Merrअगरield */
	अणु PCI_VDEVICE(INTEL, 0x1195), merrअगरield पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1196), merrअगरield पूर्ण,
	/* Baytrail */
	अणु PCI_VDEVICE(INTEL, 0x0F41), baytrail पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x0F42), baytrail पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x0F43), baytrail पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x0F44), baytrail पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x0F45), baytrail पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x0F46), baytrail पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x0F47), baytrail पूर्ण,
	/* Haswell */
	अणु PCI_VDEVICE(INTEL, 0x9c61), haswell पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x9c62), haswell पूर्ण,
	/* Braswell / Cherrytrail */
	अणु PCI_VDEVICE(INTEL, 0x22C1), cherrytrail पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x22C2), cherrytrail पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x22C3), cherrytrail पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x22C4), cherrytrail पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x22C5), cherrytrail पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x22C6), cherrytrail पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x22C7), cherrytrail पूर्ण,
	/* Elkhart Lake (PSE I2C) */
	अणु PCI_VDEVICE(INTEL, 0x4bb9), elkhartlake पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x4bba), elkhartlake पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x4bbb), elkhartlake पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x4bbc), elkhartlake पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x4bbd), elkhartlake पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x4bbe), elkhartlake पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x4bbf), elkhartlake पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x4bc0), elkhartlake पूर्ण,
	अणु PCI_VDEVICE(ATI,  0x7314), navi_amd पूर्ण,
	अणु PCI_VDEVICE(ATI,  0x73a4), navi_amd पूर्ण,
	अणु PCI_VDEVICE(ATI,  0x73e4), navi_amd पूर्ण,
	अणु PCI_VDEVICE(ATI,  0x73c4), navi_amd पूर्ण,
	अणु 0,पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, i2_designware_pci_ids);

अटल काष्ठा pci_driver dw_i2c_driver = अणु
	.name		= DRIVER_NAME,
	.id_table	= i2_designware_pci_ids,
	.probe		= i2c_dw_pci_probe,
	.हटाओ		= i2c_dw_pci_हटाओ,
	.driver         = अणु
		.pm     = &i2c_dw_pm_ops,
	पूर्ण,
पूर्ण;

module_pci_driver(dw_i2c_driver);

MODULE_AUTHOR("Baruch Siach <baruch@tkos.co.il>");
MODULE_DESCRIPTION("Synopsys DesignWare PCI I2C bus adapter");
MODULE_LICENSE("GPL");
