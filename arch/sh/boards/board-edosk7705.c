<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/sh/boards/renesas/eकरोsk7705/setup.c
 *
 * Copyright (C) 2000  Kazumoto Kojima
 *
 * Hitachi SolutionEngine Support.
 *
 * Modअगरied क्रम eकरोsk7705 development
 * board by S. Dunn, 2003.
 */
#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/smc91x.h>
#समावेश <linux/sh_पूर्णांकc.h>
#समावेश <यंत्र/machvec.h>
#समावेश <linux/sizes.h>

#घोषणा SMC_IOBASE	0xA2000000
#घोषणा SMC_IO_OFFSET	0x300
#घोषणा SMC_IOADDR	(SMC_IOBASE + SMC_IO_OFFSET)

#घोषणा ETHERNET_IRQ	evt2irq(0x320)

अटल व्योम __init sh_eकरोsk7705_init_irq(व्योम)
अणु
	make_imask_irq(ETHERNET_IRQ);
पूर्ण

/* eth initialization functions */
अटल काष्ठा smc91x_platdata smc91x_info = अणु
	.flags = SMC91X_USE_16BIT | SMC91X_IO_SHIFT_1 | IORESOURCE_IRQ_LOWLEVEL,
पूर्ण;

अटल काष्ठा resource smc91x_res[] = अणु
	[0] = अणु
		.start	= SMC_IOADDR,
		.end	= SMC_IOADDR + SZ_32 - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= ETHERNET_IRQ,
		.end	= ETHERNET_IRQ,
		.flags	= IORESOURCE_IRQ ,
	पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device smc91x_dev = अणु
	.name		= "smc91x",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(smc91x_res),
	.resource	= smc91x_res,

	.dev	= अणु
		.platक्रमm_data	= &smc91x_info,
	पूर्ण,
पूर्ण;

/* platक्रमm init code */
अटल काष्ठा platक्रमm_device *eकरोsk7705_devices[] __initdata = अणु
	&smc91x_dev,
पूर्ण;

अटल पूर्णांक __init init_eकरोsk7705_devices(व्योम)
अणु
	वापस platक्रमm_add_devices(eकरोsk7705_devices,
				    ARRAY_SIZE(eकरोsk7705_devices));
पूर्ण
device_initcall(init_eकरोsk7705_devices);

/*
 * The Machine Vector
 */
अटल काष्ठा sh_machine_vector mv_eकरोsk7705 __iniपंचांगv = अणु
	.mv_name		= "EDOSK7705",
	.mv_init_irq		= sh_eकरोsk7705_init_irq,
पूर्ण;
