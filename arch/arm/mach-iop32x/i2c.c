<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * arch/arm/plat-iop/i2c.c
 *
 * Author: Nicolas Pitre <nico@cam.org>
 * Copyright (C) 2001 MontaVista Software, Inc.
 * Copyright (C) 2004 Intel Corporation.
 */

#समावेश <linux/mm.h>
#समावेश <linux/init.h>
#समावेश <linux/major.h>
#समावेश <linux/fs.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/serial.h>
#समावेश <linux/tty.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/पन.स>
#समावेश <linux/gpio/machine.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/memory.h>
#समावेश <यंत्र/mach/arch.h>

#समावेश "hardware.h"
#समावेश "iop3xx.h"
#समावेश "irqs.h"

/*
 * Each of the I2C busses have corresponding GPIO lines, and the driver
 * need to access these directly to drive the bus low at बार.
 */

काष्ठा gpiod_lookup_table iop3xx_i2c0_gpio_lookup = अणु
	.dev_id = "IOP3xx-I2C.0",
	.table = अणु
		GPIO_LOOKUP("gpio-iop", 7, "scl", GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP("gpio-iop", 6, "sda", GPIO_ACTIVE_HIGH),
		अणु पूर्ण
	पूर्ण,
पूर्ण;

काष्ठा gpiod_lookup_table iop3xx_i2c1_gpio_lookup = अणु
	.dev_id = "IOP3xx-I2C.1",
	.table = अणु
		GPIO_LOOKUP("gpio-iop", 5, "scl", GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP("gpio-iop", 4, "sda", GPIO_ACTIVE_HIGH),
		अणु पूर्ण
	पूर्ण,
पूर्ण;

अटल काष्ठा resource iop3xx_i2c0_resources[] = अणु
	[0] = अणु
		.start	= 0xfffff680,
		.end	= 0xfffff697,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= IRQ_IOP32X_I2C_0,
		.end	= IRQ_IOP32X_I2C_0,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

काष्ठा platक्रमm_device iop3xx_i2c0_device = अणु
	.name		= "IOP3xx-I2C",
	.id		= 0,
	.num_resources	= 2,
	.resource	= iop3xx_i2c0_resources,
पूर्ण;


अटल काष्ठा resource iop3xx_i2c1_resources[] = अणु
	[0] = अणु
		.start	= 0xfffff6a0,
		.end	= 0xfffff6b7,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= IRQ_IOP32X_I2C_1,
		.end	= IRQ_IOP32X_I2C_1,
		.flags	= IORESOURCE_IRQ,
	पूर्ण
पूर्ण;

काष्ठा platक्रमm_device iop3xx_i2c1_device = अणु
	.name		= "IOP3xx-I2C",
	.id		= 1,
	.num_resources	= 2,
	.resource	= iop3xx_i2c1_resources,
पूर्ण;
