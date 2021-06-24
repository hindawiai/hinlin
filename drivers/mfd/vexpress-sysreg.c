<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Copyright (C) 2012 ARM Limited
 */

#समावेश <linux/gpio/driver.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/mfd/core.h>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_data/syscon.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/स्थिति.स>

#घोषणा SYS_ID			0x000
#घोषणा SYS_SW			0x004
#घोषणा SYS_LED			0x008
#घोषणा SYS_100HZ		0x024
#घोषणा SYS_FLAGSSET		0x030
#घोषणा SYS_FLAGSCLR		0x034
#घोषणा SYS_NVFLAGS		0x038
#घोषणा SYS_NVFLAGSSET		0x038
#घोषणा SYS_NVFLAGSCLR		0x03c
#घोषणा SYS_MCI			0x048
#घोषणा SYS_FLASH		0x04c
#घोषणा SYS_CFGSW		0x058
#घोषणा SYS_24MHZ		0x05c
#घोषणा SYS_MISC		0x060
#घोषणा SYS_DMA			0x064
#घोषणा SYS_PROCID0		0x084
#घोषणा SYS_PROCID1		0x088
#घोषणा SYS_CFGDATA		0x0a0
#घोषणा SYS_CFGCTRL		0x0a4
#घोषणा SYS_CFGSTAT		0x0a8

/* The sysreg block is just a अक्रमom collection of various functions... */

अटल काष्ठा bgpio_pdata vexpress_sysreg_sys_led_pdata = अणु
	.label = "sys_led",
	.base = -1,
	.ngpio = 8,
पूर्ण;

अटल काष्ठा bgpio_pdata vexpress_sysreg_sys_mci_pdata = अणु
	.label = "sys_mci",
	.base = -1,
	.ngpio = 2,
पूर्ण;

अटल काष्ठा bgpio_pdata vexpress_sysreg_sys_flash_pdata = अणु
	.label = "sys_flash",
	.base = -1,
	.ngpio = 1,
पूर्ण;

अटल काष्ठा mfd_cell vexpress_sysreg_cells[] = अणु
	अणु
		.name = "basic-mmio-gpio",
		.of_compatible = "arm,vexpress-sysreg,sys_led",
		.num_resources = 1,
		.resources = (काष्ठा resource []) अणु
			DEFINE_RES_MEM_NAMED(SYS_LED, 0x4, "dat"),
		पूर्ण,
		.platक्रमm_data = &vexpress_sysreg_sys_led_pdata,
		.pdata_size = माप(vexpress_sysreg_sys_led_pdata),
	पूर्ण, अणु
		.name = "basic-mmio-gpio",
		.of_compatible = "arm,vexpress-sysreg,sys_mci",
		.num_resources = 1,
		.resources = (काष्ठा resource []) अणु
			DEFINE_RES_MEM_NAMED(SYS_MCI, 0x4, "dat"),
		पूर्ण,
		.platक्रमm_data = &vexpress_sysreg_sys_mci_pdata,
		.pdata_size = माप(vexpress_sysreg_sys_mci_pdata),
	पूर्ण, अणु
		.name = "basic-mmio-gpio",
		.of_compatible = "arm,vexpress-sysreg,sys_flash",
		.num_resources = 1,
		.resources = (काष्ठा resource []) अणु
			DEFINE_RES_MEM_NAMED(SYS_FLASH, 0x4, "dat"),
		पूर्ण,
		.platक्रमm_data = &vexpress_sysreg_sys_flash_pdata,
		.pdata_size = माप(vexpress_sysreg_sys_flash_pdata),
	पूर्ण, अणु
		.name = "vexpress-syscfg",
		.num_resources = 1,
		.resources = (काष्ठा resource []) अणु
			DEFINE_RES_MEM(SYS_MISC, 0x4c),
		पूर्ण,
	पूर्ण
पूर्ण;

अटल पूर्णांक vexpress_sysreg_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *mem;
	व्योम __iomem *base;
	काष्ठा gpio_chip *mmc_gpio_chip;

	mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!mem)
		वापस -EINVAL;

	base = devm_ioremap(&pdev->dev, mem->start, resource_size(mem));
	अगर (!base)
		वापस -ENOMEM;

	/*
	 * Duplicated SYS_MCI pseuकरो-GPIO controller क्रम compatibility with
	 * older trees using sysreg node क्रम MMC control lines.
	 */
	mmc_gpio_chip = devm_kzalloc(&pdev->dev, माप(*mmc_gpio_chip),
			GFP_KERNEL);
	अगर (!mmc_gpio_chip)
		वापस -ENOMEM;
	bgpio_init(mmc_gpio_chip, &pdev->dev, 0x4, base + SYS_MCI,
			शून्य, शून्य, शून्य, शून्य, 0);
	mmc_gpio_chip->ngpio = 2;
	devm_gpiochip_add_data(&pdev->dev, mmc_gpio_chip, शून्य);

	वापस devm_mfd_add_devices(&pdev->dev, PLATFORM_DEVID_AUTO,
			vexpress_sysreg_cells,
			ARRAY_SIZE(vexpress_sysreg_cells), mem, 0, शून्य);
पूर्ण

अटल स्थिर काष्ठा of_device_id vexpress_sysreg_match[] = अणु
	अणु .compatible = "arm,vexpress-sysreg", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, vexpress_sysreg_match);

अटल काष्ठा platक्रमm_driver vexpress_sysreg_driver = अणु
	.driver = अणु
		.name = "vexpress-sysreg",
		.of_match_table = vexpress_sysreg_match,
	पूर्ण,
	.probe = vexpress_sysreg_probe,
पूर्ण;

module_platक्रमm_driver(vexpress_sysreg_driver);
MODULE_LICENSE("GPL v2");
