<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/arch/sh/boards/se/7751/setup.c
 *
 * Copyright (C) 2000  Kazumoto Kojima
 *
 * Hitachi SolutionEngine Support.
 *
 * Modअगरied क्रम 7751 Solution Engine by
 * Ian da Silva and Jeremy Siegel, 2001.
 */
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <यंत्र/machvec.h>
#समावेश <mach-se/mach/se7751.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/heartbeat.h>

अटल अचिन्हित अक्षर heartbeat_bit_pos[] = अणु 8, 9, 10, 11, 12, 13, 14, 15 पूर्ण;

अटल काष्ठा heartbeat_data heartbeat_data = अणु
	.bit_pos	= heartbeat_bit_pos,
	.nr_bits	= ARRAY_SIZE(heartbeat_bit_pos),
पूर्ण;

अटल काष्ठा resource heartbeat_resources[] = अणु
	[0] = अणु
		.start	= PA_LED,
		.end	= PA_LED,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device heartbeat_device = अणु
	.name		= "heartbeat",
	.id		= -1,
	.dev	= अणु
		.platक्रमm_data	= &heartbeat_data,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(heartbeat_resources),
	.resource	= heartbeat_resources,
पूर्ण;

अटल काष्ठा platक्रमm_device *se7751_devices[] __initdata = अणु
	&heartbeat_device,
पूर्ण;

अटल पूर्णांक __init se7751_devices_setup(व्योम)
अणु
	वापस platक्रमm_add_devices(se7751_devices, ARRAY_SIZE(se7751_devices));
पूर्ण
device_initcall(se7751_devices_setup);

/*
 * The Machine Vector
 */
अटल काष्ठा sh_machine_vector mv_7751se __iniपंचांगv = अणु
	.mv_name		= "7751 SolutionEngine",
	.mv_init_irq		= init_7751se_IRQ,
पूर्ण;
