<शैली गुरु>
/*
 * OMAP16xx specअगरic gpio init
 *
 * Copyright (C) 2010 Texas Instruments Incorporated - https://www.ti.com/
 *
 * Author:
 *	Charulatha V <अक्षरu@ti.com>
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/gpपन.स>
#समावेश <linux/platक्रमm_data/gpio-omap.h>

#समावेश <mach/irqs.h>

#समावेश "soc.h"

#घोषणा OMAP1610_GPIO1_BASE		0xfffbe400
#घोषणा OMAP1610_GPIO2_BASE		0xfffbec00
#घोषणा OMAP1610_GPIO3_BASE		0xfffbb400
#घोषणा OMAP1610_GPIO4_BASE		0xfffbbc00
#घोषणा OMAP1_MPUIO_VBASE		OMAP1_MPUIO_BASE

/* smart idle, enable wakeup */
#घोषणा SYSCONFIG_WORD			0x14

/* mpu gpio */
अटल काष्ठा resource omap16xx_mpu_gpio_resources[] = अणु
	अणु
		.start	= OMAP1_MPUIO_VBASE,
		.end	= OMAP1_MPUIO_VBASE + SZ_2K - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start	= INT_MPUIO,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा omap_gpio_reg_offs omap16xx_mpuio_regs = अणु
	.revision       = अच_लघु_उच्च,
	.direction	= OMAP_MPUIO_IO_CNTL,
	.datain		= OMAP_MPUIO_INPUT_LATCH,
	.dataout	= OMAP_MPUIO_OUTPUT,
	.irqstatus	= OMAP_MPUIO_GPIO_INT,
	.irqenable	= OMAP_MPUIO_GPIO_MASKIT,
	.irqenable_inv	= true,
	.irqctrl	= OMAP_MPUIO_GPIO_INT_EDGE,
पूर्ण;

अटल काष्ठा omap_gpio_platक्रमm_data omap16xx_mpu_gpio_config = अणु
	.is_mpuio		= true,
	.bank_width		= 16,
	.bank_stride		= 1,
	.regs                   = &omap16xx_mpuio_regs,
पूर्ण;

अटल काष्ठा platक्रमm_device omap16xx_mpu_gpio = अणु
	.name           = "omap_gpio",
	.id             = 0,
	.dev            = अणु
		.platक्रमm_data = &omap16xx_mpu_gpio_config,
	पूर्ण,
	.num_resources = ARRAY_SIZE(omap16xx_mpu_gpio_resources),
	.resource = omap16xx_mpu_gpio_resources,
पूर्ण;

/* gpio1 */
अटल काष्ठा resource omap16xx_gpio1_resources[] = अणु
	अणु
		.start	= OMAP1610_GPIO1_BASE,
		.end	= OMAP1610_GPIO1_BASE + SZ_2K - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start	= INT_GPIO_BANK1,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा omap_gpio_reg_offs omap16xx_gpio_regs = अणु
	.revision       = OMAP1610_GPIO_REVISION,
	.direction	= OMAP1610_GPIO_सूचीECTION,
	.set_dataout	= OMAP1610_GPIO_SET_DATAOUT,
	.clr_dataout	= OMAP1610_GPIO_CLEAR_DATAOUT,
	.datain		= OMAP1610_GPIO_DATAIN,
	.dataout	= OMAP1610_GPIO_DATAOUT,
	.irqstatus	= OMAP1610_GPIO_IRQSTATUS1,
	.irqenable	= OMAP1610_GPIO_IRQENABLE1,
	.set_irqenable	= OMAP1610_GPIO_SET_IRQENABLE1,
	.clr_irqenable	= OMAP1610_GPIO_CLEAR_IRQENABLE1,
	.wkup_en	= OMAP1610_GPIO_WAKEUPENABLE,
	.edgectrl1	= OMAP1610_GPIO_EDGE_CTRL1,
	.edgectrl2	= OMAP1610_GPIO_EDGE_CTRL2,
पूर्ण;

अटल काष्ठा omap_gpio_platक्रमm_data omap16xx_gpio1_config = अणु
	.bank_width		= 16,
	.regs                   = &omap16xx_gpio_regs,
पूर्ण;

अटल काष्ठा platक्रमm_device omap16xx_gpio1 = अणु
	.name           = "omap_gpio",
	.id             = 1,
	.dev            = अणु
		.platक्रमm_data = &omap16xx_gpio1_config,
	पूर्ण,
	.num_resources = ARRAY_SIZE(omap16xx_gpio1_resources),
	.resource = omap16xx_gpio1_resources,
पूर्ण;

/* gpio2 */
अटल काष्ठा resource omap16xx_gpio2_resources[] = अणु
	अणु
		.start	= OMAP1610_GPIO2_BASE,
		.end	= OMAP1610_GPIO2_BASE + SZ_2K - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start	= INT_1610_GPIO_BANK2,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा omap_gpio_platक्रमm_data omap16xx_gpio2_config = अणु
	.bank_width		= 16,
	.regs                   = &omap16xx_gpio_regs,
पूर्ण;

अटल काष्ठा platक्रमm_device omap16xx_gpio2 = अणु
	.name           = "omap_gpio",
	.id             = 2,
	.dev            = अणु
		.platक्रमm_data = &omap16xx_gpio2_config,
	पूर्ण,
	.num_resources = ARRAY_SIZE(omap16xx_gpio2_resources),
	.resource = omap16xx_gpio2_resources,
पूर्ण;

/* gpio3 */
अटल काष्ठा resource omap16xx_gpio3_resources[] = अणु
	अणु
		.start	= OMAP1610_GPIO3_BASE,
		.end	= OMAP1610_GPIO3_BASE + SZ_2K - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start	= INT_1610_GPIO_BANK3,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा omap_gpio_platक्रमm_data omap16xx_gpio3_config = अणु
	.bank_width		= 16,
	.regs                   = &omap16xx_gpio_regs,
पूर्ण;

अटल काष्ठा platक्रमm_device omap16xx_gpio3 = अणु
	.name           = "omap_gpio",
	.id             = 3,
	.dev            = अणु
		.platक्रमm_data = &omap16xx_gpio3_config,
	पूर्ण,
	.num_resources = ARRAY_SIZE(omap16xx_gpio3_resources),
	.resource = omap16xx_gpio3_resources,
पूर्ण;

/* gpio4 */
अटल काष्ठा resource omap16xx_gpio4_resources[] = अणु
	अणु
		.start	= OMAP1610_GPIO4_BASE,
		.end	= OMAP1610_GPIO4_BASE + SZ_2K - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start	= INT_1610_GPIO_BANK4,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा omap_gpio_platक्रमm_data omap16xx_gpio4_config = अणु
	.bank_width		= 16,
	.regs                   = &omap16xx_gpio_regs,
पूर्ण;

अटल काष्ठा platक्रमm_device omap16xx_gpio4 = अणु
	.name           = "omap_gpio",
	.id             = 4,
	.dev            = अणु
		.platक्रमm_data = &omap16xx_gpio4_config,
	पूर्ण,
	.num_resources = ARRAY_SIZE(omap16xx_gpio4_resources),
	.resource = omap16xx_gpio4_resources,
पूर्ण;

अटल काष्ठा platक्रमm_device *omap16xx_gpio_dev[] __initdata = अणु
	&omap16xx_mpu_gpio,
	&omap16xx_gpio1,
	&omap16xx_gpio2,
	&omap16xx_gpio3,
	&omap16xx_gpio4,
पूर्ण;

/*
 * omap16xx_gpio_init needs to be करोne beक्रमe
 * machine_init functions access gpio APIs.
 * Hence omap16xx_gpio_init is a postcore_initcall.
 */
अटल पूर्णांक __init omap16xx_gpio_init(व्योम)
अणु
	पूर्णांक i;
	व्योम __iomem *base;
	काष्ठा resource *res;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा omap_gpio_platक्रमm_data *pdata;

	अगर (!cpu_is_omap16xx())
		वापस -EINVAL;

	/*
	 * Enable प्रणाली घड़ी क्रम GPIO module.
	 * The CAM_CLK_CTRL *is* really the right place.
	 */
	omap_ग_लिखोl(omap_पढ़ोl(ULPD_CAM_CLK_CTRL) | 0x04,
					ULPD_CAM_CLK_CTRL);

	क्रम (i = 0; i < ARRAY_SIZE(omap16xx_gpio_dev); i++) अणु
		pdev = omap16xx_gpio_dev[i];
		pdata = pdev->dev.platक्रमm_data;

		res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
		अगर (unlikely(!res)) अणु
			dev_err(&pdev->dev, "Invalid mem resource.\n");
			वापस -ENODEV;
		पूर्ण

		base = ioremap(res->start, resource_size(res));
		अगर (unlikely(!base)) अणु
			dev_err(&pdev->dev, "ioremap failed.\n");
			वापस -ENOMEM;
		पूर्ण

		__raw_ग_लिखोl(SYSCONFIG_WORD, base + OMAP1610_GPIO_SYSCONFIG);
		iounmap(base);

		platक्रमm_device_रेजिस्टर(omap16xx_gpio_dev[i]);
	पूर्ण

	वापस 0;
पूर्ण
postcore_initcall(omap16xx_gpio_init);
