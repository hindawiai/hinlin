<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/arch/sh/boards/se/7722/setup.c
 *
 * Copyright (C) 2007 Nobuhiro Iwamatsu
 * Copyright (C) 2012 Paul Mundt
 *
 * Hitachi UL SolutionEngine 7722 Support.
 */
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/ata_platक्रमm.h>
#समावेश <linux/input.h>
#समावेश <linux/input/sh_keysc.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/smc91x.h>
#समावेश <linux/sh_पूर्णांकc.h>
#समावेश <mach-se/mach/se7722.h>
#समावेश <mach-se/mach/mrshpc.h>
#समावेश <यंत्र/machvec.h>
#समावेश <यंत्र/घड़ी.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/heartbeat.h>
#समावेश <cpu/sh7722.h>

/* Heartbeat */
अटल काष्ठा resource heartbeat_resource = अणु
	.start  = PA_LED,
	.end    = PA_LED,
	.flags  = IORESOURCE_MEM | IORESOURCE_MEM_16BIT,
पूर्ण;

अटल काष्ठा platक्रमm_device heartbeat_device = अणु
	.name           = "heartbeat",
	.id             = -1,
	.num_resources  = 1,
	.resource       = &heartbeat_resource,
पूर्ण;

/* SMC91x */
अटल काष्ठा smc91x_platdata smc91x_info = अणु
	.flags = SMC91X_USE_16BIT,
पूर्ण;

अटल काष्ठा resource smc91x_eth_resources[] = अणु
	[0] = अणु
		.name   = "smc91x-regs" ,
		.start  = PA_LAN + 0x300,
		.end    = PA_LAN + 0x300 + 0x10 ,
		.flags  = IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		/* Filled in later */
		.flags  = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device smc91x_eth_device = अणु
	.name           = "smc91x",
	.id             = 0,
	.dev = अणु
		.dma_mask               = शून्य,         /* करोn't use dma */
		.coherent_dma_mask      = 0xffffffff,
		.platक्रमm_data	= &smc91x_info,
	पूर्ण,
	.num_resources  = ARRAY_SIZE(smc91x_eth_resources),
	.resource       = smc91x_eth_resources,
पूर्ण;

अटल काष्ठा resource cf_ide_resources[] = अणु
	[0] = अणु
		.start  = PA_MRSHPC_IO + 0x1f0,
		.end    = PA_MRSHPC_IO + 0x1f0 + 8 ,
		.flags  = IORESOURCE_IO,
	पूर्ण,
	[1] = अणु
		.start  = PA_MRSHPC_IO + 0x1f0 + 0x206,
		.end    = PA_MRSHPC_IO + 0x1f0 +8 + 0x206 + 8,
		.flags  = IORESOURCE_IO,
	पूर्ण,
	[2] = अणु
		/* Filled in later */
		.flags  = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device cf_ide_device  = अणु
	.name           = "pata_platform",
	.id             = -1,
	.num_resources  = ARRAY_SIZE(cf_ide_resources),
	.resource       = cf_ide_resources,
पूर्ण;

अटल काष्ठा sh_keysc_info sh_keysc_info = अणु
	.mode = SH_KEYSC_MODE_1, /* KEYOUT0->5, KEYIN0->4 */
	.scan_timing = 3,
	.delay = 5,
	.keycodes = अणु /* SW1 -> SW30 */
		KEY_A, KEY_B, KEY_C, KEY_D, KEY_E,
		KEY_F, KEY_G, KEY_H, KEY_I, KEY_J,
		KEY_K, KEY_L, KEY_M, KEY_N, KEY_O,
		KEY_P, KEY_Q, KEY_R, KEY_S, KEY_T,
		KEY_U, KEY_V, KEY_W, KEY_X, KEY_Y,
		KEY_Z,
		KEY_HOME, KEY_SLEEP, KEY_WAKEUP, KEY_COFFEE, /* lअगरe */
	पूर्ण,
पूर्ण;

अटल काष्ठा resource sh_keysc_resources[] = अणु
	[0] = अणु
		.start  = 0x044b0000,
		.end    = 0x044b000f,
		.flags  = IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start  = evt2irq(0xbe0),
		.flags  = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device sh_keysc_device = अणु
	.name           = "sh_keysc",
	.id             = 0, /* "keysc0" घड़ी */
	.num_resources  = ARRAY_SIZE(sh_keysc_resources),
	.resource       = sh_keysc_resources,
	.dev	= अणु
		.platक्रमm_data	= &sh_keysc_info,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device *se7722_devices[] __initdata = अणु
	&heartbeat_device,
	&smc91x_eth_device,
	&cf_ide_device,
	&sh_keysc_device,
पूर्ण;

अटल पूर्णांक __init se7722_devices_setup(व्योम)
अणु
	mrshpc_setup_winकरोws();

	/* Wire-up dynamic vectors */
	cf_ide_resources[2].start = cf_ide_resources[2].end =
		irq_find_mapping(se7722_irq_करोमुख्य, SE7722_FPGA_IRQ_MRSHPC0);

	smc91x_eth_resources[1].start = smc91x_eth_resources[1].end =
		irq_find_mapping(se7722_irq_करोमुख्य, SE7722_FPGA_IRQ_SMC);

	वापस platक्रमm_add_devices(se7722_devices, ARRAY_SIZE(se7722_devices));
पूर्ण
device_initcall(se7722_devices_setup);

अटल व्योम __init se7722_setup(अक्षर **cmdline_p)
अणु
	__raw_ग_लिखोw(0x010D, FPGA_OUT);    /* FPGA */

	__raw_ग_लिखोw(0x0000, PORT_PECR);   /* PORT E 1 = IRQ5 ,E 0 = BS */
	__raw_ग_लिखोw(0x1000, PORT_PJCR);   /* PORT J 1 = IRQ1,J 0 =IRQ0 */

	/* LCDC I/O */
	__raw_ग_लिखोw(0x0020, PORT_PSELD);

	/* SIOF1*/
	__raw_ग_लिखोw(0x0003, PORT_PSELB);
	__raw_ग_लिखोw(0xe000, PORT_PSELC);
	__raw_ग_लिखोw(0x0000, PORT_PKCR);

	/* LCDC */
	__raw_ग_लिखोw(0x4020, PORT_PHCR);
	__raw_ग_लिखोw(0x0000, PORT_PLCR);
	__raw_ग_लिखोw(0x0000, PORT_PMCR);
	__raw_ग_लिखोw(0x0002, PORT_PRCR);
	__raw_ग_लिखोw(0x0000, PORT_PXCR);   /* LCDC,CS6A */

	/* KEYSC */
	__raw_ग_लिखोw(0x0A10, PORT_PSELA); /* BS,SHHID2 */
	__raw_ग_लिखोw(0x0000, PORT_PYCR);
	__raw_ग_लिखोw(0x0000, PORT_PZCR);
	__raw_ग_लिखोw(__raw_पढ़ोw(PORT_HIZCRA) & ~0x4000, PORT_HIZCRA);
	__raw_ग_लिखोw(__raw_पढ़ोw(PORT_HIZCRC) & ~0xc000, PORT_HIZCRC);
पूर्ण

/*
 * The Machine Vector
 */
अटल काष्ठा sh_machine_vector mv_se7722 __iniपंचांगv = अणु
	.mv_name                = "Solution Engine 7722" ,
	.mv_setup               = se7722_setup ,
	.mv_init_irq		= init_se7722_IRQ,
पूर्ण;
