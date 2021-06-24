<शैली गुरु>
/*
 * OMAP15xx specअगरic gpio init
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

#घोषणा OMAP1_MPUIO_VBASE		OMAP1_MPUIO_BASE
#घोषणा OMAP1510_GPIO_BASE		0xFFFCE000

/* gpio1 */
अटल काष्ठा resource omap15xx_mpu_gpio_resources[] = अणु
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

अटल काष्ठा omap_gpio_reg_offs omap15xx_mpuio_regs = अणु
	.revision       = अच_लघु_उच्च,
	.direction	= OMAP_MPUIO_IO_CNTL,
	.datain		= OMAP_MPUIO_INPUT_LATCH,
	.dataout	= OMAP_MPUIO_OUTPUT,
	.irqstatus	= OMAP_MPUIO_GPIO_INT,
	.irqenable	= OMAP_MPUIO_GPIO_MASKIT,
	.irqenable_inv	= true,
	.irqctrl	= OMAP_MPUIO_GPIO_INT_EDGE,
पूर्ण;

अटल काष्ठा omap_gpio_platक्रमm_data omap15xx_mpu_gpio_config = अणु
	.is_mpuio		= true,
	.bank_width		= 16,
	.bank_stride		= 1,
	.regs			= &omap15xx_mpuio_regs,
पूर्ण;

अटल काष्ठा platक्रमm_device omap15xx_mpu_gpio = अणु
	.name           = "omap_gpio",
	.id             = 0,
	.dev            = अणु
		.platक्रमm_data = &omap15xx_mpu_gpio_config,
	पूर्ण,
	.num_resources = ARRAY_SIZE(omap15xx_mpu_gpio_resources),
	.resource = omap15xx_mpu_gpio_resources,
पूर्ण;

/* gpio2 */
अटल काष्ठा resource omap15xx_gpio_resources[] = अणु
	अणु
		.start	= OMAP1510_GPIO_BASE,
		.end	= OMAP1510_GPIO_BASE + SZ_2K - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start	= INT_GPIO_BANK1,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा omap_gpio_reg_offs omap15xx_gpio_regs = अणु
	.revision	= अच_लघु_उच्च,
	.direction	= OMAP1510_GPIO_सूची_CONTROL,
	.datain		= OMAP1510_GPIO_DATA_INPUT,
	.dataout	= OMAP1510_GPIO_DATA_OUTPUT,
	.irqstatus	= OMAP1510_GPIO_INT_STATUS,
	.irqenable	= OMAP1510_GPIO_INT_MASK,
	.irqenable_inv	= true,
	.irqctrl	= OMAP1510_GPIO_INT_CONTROL,
	.pinctrl	= OMAP1510_GPIO_PIN_CONTROL,
पूर्ण;

अटल काष्ठा omap_gpio_platक्रमm_data omap15xx_gpio_config = अणु
	.bank_width		= 16,
	.regs                   = &omap15xx_gpio_regs,
पूर्ण;

अटल काष्ठा platक्रमm_device omap15xx_gpio = अणु
	.name           = "omap_gpio",
	.id             = 1,
	.dev            = अणु
		.platक्रमm_data = &omap15xx_gpio_config,
	पूर्ण,
	.num_resources = ARRAY_SIZE(omap15xx_gpio_resources),
	.resource = omap15xx_gpio_resources,
पूर्ण;

/*
 * omap15xx_gpio_init needs to be करोne beक्रमe
 * machine_init functions access gpio APIs.
 * Hence omap15xx_gpio_init is a postcore_initcall.
 */
अटल पूर्णांक __init omap15xx_gpio_init(व्योम)
अणु
	अगर (!cpu_is_omap15xx())
		वापस -EINVAL;

	platक्रमm_device_रेजिस्टर(&omap15xx_mpu_gpio);
	platक्रमm_device_रेजिस्टर(&omap15xx_gpio);

	वापस 0;
पूर्ण
postcore_initcall(omap15xx_gpio_init);
