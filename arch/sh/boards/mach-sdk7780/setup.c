<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/sh/boards/renesas/sdk7780/setup.c
 *
 * Renesas Solutions SH7780 SDK Support
 * Copyright (C) 2008 Nicholas Beck <nbeck@mpc-data.co.uk>
 */
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/ata_platक्रमm.h>
#समावेश <यंत्र/machvec.h>
#समावेश <mach/sdk7780.h>
#समावेश <यंत्र/heartbeat.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/addrspace.h>

#घोषणा GPIO_PECR        0xFFEA0008

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
अटल काष्ठा resource smc91x_eth_resources[] = अणु
	[0] = अणु
		.name   = "smc91x-regs" ,
		.start  = PA_LAN + 0x300,
		.end    = PA_LAN + 0x300 + 0x10 ,
		.flags  = IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start  = IRQ_ETHERNET,
		.end    = IRQ_ETHERNET,
		.flags  = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device smc91x_eth_device = अणु
	.name           = "smc91x",
	.id             = 0,
	.dev = अणु
		.dma_mask               = शून्य,         /* करोn't use dma */
		.coherent_dma_mask      = 0xffffffff,
	पूर्ण,
	.num_resources  = ARRAY_SIZE(smc91x_eth_resources),
	.resource       = smc91x_eth_resources,
पूर्ण;

अटल काष्ठा platक्रमm_device *sdk7780_devices[] __initdata = अणु
	&heartbeat_device,
	&smc91x_eth_device,
पूर्ण;

अटल पूर्णांक __init sdk7780_devices_setup(व्योम)
अणु
	वापस platक्रमm_add_devices(sdk7780_devices,
		ARRAY_SIZE(sdk7780_devices));
पूर्ण
device_initcall(sdk7780_devices_setup);

अटल व्योम __init sdk7780_setup(अक्षर **cmdline_p)
अणु
	u16 ver = __raw_पढ़ोw(FPGA_FPVERR);
	u16 dateStamp = __raw_पढ़ोw(FPGA_FPDATER);

	prपूर्णांकk(KERN_INFO "Renesas Technology Europe SDK7780 support.\n");
	prपूर्णांकk(KERN_INFO "Board version: %d (revision %d), "
			 "FPGA version: %d (revision %d), datestamp : %d\n",
			 (ver >> 12) & 0xf, (ver >> 8) & 0xf,
			 (ver >>  4) & 0xf, ver & 0xf,
			 dateStamp);

	/* Setup pin mux'ing क्रम PCIC */
	__raw_ग_लिखोw(0x0000, GPIO_PECR);
पूर्ण

/*
 * The Machine Vector
 */
अटल काष्ठा sh_machine_vector mv_se7780 __iniपंचांगv = अणु
	.mv_name        = "Renesas SDK7780-R3" ,
	.mv_setup		= sdk7780_setup,
	.mv_init_irq	= init_sdk7780_IRQ,
पूर्ण;

