<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *
 * linux/arch/sh/boards/se/7206/setup.c
 *
 * Copyright (C) 2006  Yoshinori Sato
 * Copyright (C) 2007 - 2008  Paul Mundt
 *
 * Hitachi 7206 SolutionEngine Support.
 */
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/smc91x.h>
#समावेश <mach-se/mach/se7206.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/machvec.h>
#समावेश <यंत्र/heartbeat.h>

अटल काष्ठा resource smc91x_resources[] = अणु
	[0] = अणु
		.name		= "smc91x-regs",
		.start		= PA_SMSC + 0x300,
		.end		= PA_SMSC + 0x300 + 0x020 - 1,
		.flags		= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start		= 64,
		.end		= 64,
		.flags		= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा smc91x_platdata smc91x_info = अणु
	.flags	= SMC91X_USE_16BIT,
पूर्ण;

अटल काष्ठा platक्रमm_device smc91x_device = अणु
	.name		= "smc91x",
	.id		= -1,
	.dev		= अणु
		.dma_mask		= शून्य,
		.coherent_dma_mask	= 0xffffffff,
		.platक्रमm_data		= &smc91x_info,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(smc91x_resources),
	.resource	= smc91x_resources,
पूर्ण;

अटल अचिन्हित अक्षर heartbeat_bit_pos[] = अणु 8, 9, 10, 11, 12, 13, 14, 15 पूर्ण;

अटल काष्ठा heartbeat_data heartbeat_data = अणु
	.bit_pos	= heartbeat_bit_pos,
	.nr_bits	= ARRAY_SIZE(heartbeat_bit_pos),
पूर्ण;

अटल काष्ठा resource heartbeat_resource = अणु
	.start	= PA_LED,
	.end	= PA_LED,
	.flags	= IORESOURCE_MEM | IORESOURCE_MEM_32BIT,
पूर्ण;

अटल काष्ठा platक्रमm_device heartbeat_device = अणु
	.name		= "heartbeat",
	.id		= -1,
	.dev	= अणु
		.platक्रमm_data	= &heartbeat_data,
	पूर्ण,
	.num_resources	= 1,
	.resource	= &heartbeat_resource,
पूर्ण;

अटल काष्ठा platक्रमm_device *se7206_devices[] __initdata = अणु
	&smc91x_device,
	&heartbeat_device,
पूर्ण;

अटल पूर्णांक __init se7206_devices_setup(व्योम)
अणु
	वापस platक्रमm_add_devices(se7206_devices, ARRAY_SIZE(se7206_devices));
पूर्ण
device_initcall(se7206_devices_setup);

अटल पूर्णांक se7206_mode_pins(व्योम)
अणु
	वापस MODE_PIN1 | MODE_PIN2;
पूर्ण

/*
 * The Machine Vector
 */

अटल काष्ठा sh_machine_vector mv_se __iniपंचांगv = अणु
	.mv_name		= "SolutionEngine",
	.mv_init_irq		= init_se7206_IRQ,
	.mv_mode_pins		= se7206_mode_pins,
पूर्ण;
