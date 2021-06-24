<शैली गुरु>
/*
 * OMAP7xx specअगरic gpio init
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

#घोषणा OMAP7XX_GPIO1_BASE		0xfffbc000
#घोषणा OMAP7XX_GPIO2_BASE		0xfffbc800
#घोषणा OMAP7XX_GPIO3_BASE		0xfffbd000
#घोषणा OMAP7XX_GPIO4_BASE		0xfffbd800
#घोषणा OMAP7XX_GPIO5_BASE		0xfffbe000
#घोषणा OMAP7XX_GPIO6_BASE		0xfffbe800
#घोषणा OMAP1_MPUIO_VBASE		OMAP1_MPUIO_BASE

/* mpu gpio */
अटल काष्ठा resource omap7xx_mpu_gpio_resources[] = अणु
	अणु
		.start	= OMAP1_MPUIO_VBASE,
		.end	= OMAP1_MPUIO_VBASE + SZ_2K - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start	= INT_7XX_MPUIO,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा omap_gpio_reg_offs omap7xx_mpuio_regs = अणु
	.revision	= अच_लघु_उच्च,
	.direction	= OMAP_MPUIO_IO_CNTL / 2,
	.datain		= OMAP_MPUIO_INPUT_LATCH / 2,
	.dataout	= OMAP_MPUIO_OUTPUT / 2,
	.irqstatus	= OMAP_MPUIO_GPIO_INT / 2,
	.irqenable	= OMAP_MPUIO_GPIO_MASKIT / 2,
	.irqenable_inv	= true,
	.irqctrl	= OMAP_MPUIO_GPIO_INT_EDGE >> 1,
पूर्ण;

अटल काष्ठा omap_gpio_platक्रमm_data omap7xx_mpu_gpio_config = अणु
	.is_mpuio		= true,
	.bank_width		= 16,
	.bank_stride		= 2,
	.regs                   = &omap7xx_mpuio_regs,
पूर्ण;

अटल काष्ठा platक्रमm_device omap7xx_mpu_gpio = अणु
	.name           = "omap_gpio",
	.id             = 0,
	.dev            = अणु
		.platक्रमm_data = &omap7xx_mpu_gpio_config,
	पूर्ण,
	.num_resources = ARRAY_SIZE(omap7xx_mpu_gpio_resources),
	.resource = omap7xx_mpu_gpio_resources,
पूर्ण;

/* gpio1 */
अटल काष्ठा resource omap7xx_gpio1_resources[] = अणु
	अणु
		.start	= OMAP7XX_GPIO1_BASE,
		.end	= OMAP7XX_GPIO1_BASE + SZ_2K - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start	= INT_7XX_GPIO_BANK1,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा omap_gpio_reg_offs omap7xx_gpio_regs = अणु
	.revision	= अच_लघु_उच्च,
	.direction	= OMAP7XX_GPIO_सूची_CONTROL,
	.datain		= OMAP7XX_GPIO_DATA_INPUT,
	.dataout	= OMAP7XX_GPIO_DATA_OUTPUT,
	.irqstatus	= OMAP7XX_GPIO_INT_STATUS,
	.irqenable	= OMAP7XX_GPIO_INT_MASK,
	.irqenable_inv	= true,
	.irqctrl	= OMAP7XX_GPIO_INT_CONTROL,
पूर्ण;

अटल काष्ठा omap_gpio_platक्रमm_data omap7xx_gpio1_config = अणु
	.bank_width		= 32,
	.regs			= &omap7xx_gpio_regs,
पूर्ण;

अटल काष्ठा platक्रमm_device omap7xx_gpio1 = अणु
	.name           = "omap_gpio",
	.id             = 1,
	.dev            = अणु
		.platक्रमm_data = &omap7xx_gpio1_config,
	पूर्ण,
	.num_resources = ARRAY_SIZE(omap7xx_gpio1_resources),
	.resource = omap7xx_gpio1_resources,
पूर्ण;

/* gpio2 */
अटल काष्ठा resource omap7xx_gpio2_resources[] = अणु
	अणु
		.start	= OMAP7XX_GPIO2_BASE,
		.end	= OMAP7XX_GPIO2_BASE + SZ_2K - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start	= INT_7XX_GPIO_BANK2,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा omap_gpio_platक्रमm_data omap7xx_gpio2_config = अणु
	.bank_width		= 32,
	.regs			= &omap7xx_gpio_regs,
पूर्ण;

अटल काष्ठा platक्रमm_device omap7xx_gpio2 = अणु
	.name           = "omap_gpio",
	.id             = 2,
	.dev            = अणु
		.platक्रमm_data = &omap7xx_gpio2_config,
	पूर्ण,
	.num_resources = ARRAY_SIZE(omap7xx_gpio2_resources),
	.resource = omap7xx_gpio2_resources,
पूर्ण;

/* gpio3 */
अटल काष्ठा resource omap7xx_gpio3_resources[] = अणु
	अणु
		.start	= OMAP7XX_GPIO3_BASE,
		.end	= OMAP7XX_GPIO3_BASE + SZ_2K - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start	= INT_7XX_GPIO_BANK3,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा omap_gpio_platक्रमm_data omap7xx_gpio3_config = अणु
	.bank_width		= 32,
	.regs			= &omap7xx_gpio_regs,
पूर्ण;

अटल काष्ठा platक्रमm_device omap7xx_gpio3 = अणु
	.name           = "omap_gpio",
	.id             = 3,
	.dev            = अणु
		.platक्रमm_data = &omap7xx_gpio3_config,
	पूर्ण,
	.num_resources = ARRAY_SIZE(omap7xx_gpio3_resources),
	.resource = omap7xx_gpio3_resources,
पूर्ण;

/* gpio4 */
अटल काष्ठा resource omap7xx_gpio4_resources[] = अणु
	अणु
		.start	= OMAP7XX_GPIO4_BASE,
		.end	= OMAP7XX_GPIO4_BASE + SZ_2K - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start	= INT_7XX_GPIO_BANK4,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा omap_gpio_platक्रमm_data omap7xx_gpio4_config = अणु
	.bank_width		= 32,
	.regs			= &omap7xx_gpio_regs,
पूर्ण;

अटल काष्ठा platक्रमm_device omap7xx_gpio4 = अणु
	.name           = "omap_gpio",
	.id             = 4,
	.dev            = अणु
		.platक्रमm_data = &omap7xx_gpio4_config,
	पूर्ण,
	.num_resources = ARRAY_SIZE(omap7xx_gpio4_resources),
	.resource = omap7xx_gpio4_resources,
पूर्ण;

/* gpio5 */
अटल काष्ठा resource omap7xx_gpio5_resources[] = अणु
	अणु
		.start	= OMAP7XX_GPIO5_BASE,
		.end	= OMAP7XX_GPIO5_BASE + SZ_2K - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start	= INT_7XX_GPIO_BANK5,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा omap_gpio_platक्रमm_data omap7xx_gpio5_config = अणु
	.bank_width		= 32,
	.regs			= &omap7xx_gpio_regs,
पूर्ण;

अटल काष्ठा platक्रमm_device omap7xx_gpio5 = अणु
	.name           = "omap_gpio",
	.id             = 5,
	.dev            = अणु
		.platक्रमm_data = &omap7xx_gpio5_config,
	पूर्ण,
	.num_resources = ARRAY_SIZE(omap7xx_gpio5_resources),
	.resource = omap7xx_gpio5_resources,
पूर्ण;

/* gpio6 */
अटल काष्ठा resource omap7xx_gpio6_resources[] = अणु
	अणु
		.start	= OMAP7XX_GPIO6_BASE,
		.end	= OMAP7XX_GPIO6_BASE + SZ_2K - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start	= INT_7XX_GPIO_BANK6,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा omap_gpio_platक्रमm_data omap7xx_gpio6_config = अणु
	.bank_width		= 32,
	.regs			= &omap7xx_gpio_regs,
पूर्ण;

अटल काष्ठा platक्रमm_device omap7xx_gpio6 = अणु
	.name           = "omap_gpio",
	.id             = 6,
	.dev            = अणु
		.platक्रमm_data = &omap7xx_gpio6_config,
	पूर्ण,
	.num_resources = ARRAY_SIZE(omap7xx_gpio6_resources),
	.resource = omap7xx_gpio6_resources,
पूर्ण;

अटल काष्ठा platक्रमm_device *omap7xx_gpio_dev[] __initdata = अणु
	&omap7xx_mpu_gpio,
	&omap7xx_gpio1,
	&omap7xx_gpio2,
	&omap7xx_gpio3,
	&omap7xx_gpio4,
	&omap7xx_gpio5,
	&omap7xx_gpio6,
पूर्ण;

/*
 * omap7xx_gpio_init needs to be करोne beक्रमe
 * machine_init functions access gpio APIs.
 * Hence omap7xx_gpio_init is a postcore_initcall.
 */
अटल पूर्णांक __init omap7xx_gpio_init(व्योम)
अणु
	पूर्णांक i;

	अगर (!cpu_is_omap7xx())
		वापस -EINVAL;

	क्रम (i = 0; i < ARRAY_SIZE(omap7xx_gpio_dev); i++)
		platक्रमm_device_रेजिस्टर(omap7xx_gpio_dev[i]);

	वापस 0;
पूर्ण
postcore_initcall(omap7xx_gpio_init);
