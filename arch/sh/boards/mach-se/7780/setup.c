<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/arch/sh/boards/se/7780/setup.c
 *
 * Copyright (C) 2006,2007  Nobuhiro Iwamatsu
 *
 * Hitachi UL SolutionEngine 7780 Support.
 */
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <यंत्र/machvec.h>
#समावेश <mach-se/mach/se7780.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/heartbeat.h>

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
		.start  = SMC_IRQ,
		.end    = SMC_IRQ,
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

अटल काष्ठा platक्रमm_device *se7780_devices[] __initdata = अणु
	&heartbeat_device,
	&smc91x_eth_device,
पूर्ण;

अटल पूर्णांक __init se7780_devices_setup(व्योम)
अणु
	वापस platक्रमm_add_devices(se7780_devices,
		ARRAY_SIZE(se7780_devices));
पूर्ण
device_initcall(se7780_devices_setup);

#घोषणा GPIO_PHCR        0xFFEA000E
#घोषणा GPIO_PMSELR      0xFFEA0080
#घोषणा GPIO_PECR        0xFFEA0008

अटल व्योम __init se7780_setup(अक्षर **cmdline_p)
अणु
	/* "SH-Linux" on LED Display */
	__raw_ग_लिखोw( 'S' , PA_LED_DISP + (DISP_SEL0_ADDR << 1) );
	__raw_ग_लिखोw( 'H' , PA_LED_DISP + (DISP_SEL1_ADDR << 1) );
	__raw_ग_लिखोw( '-' , PA_LED_DISP + (DISP_SEL2_ADDR << 1) );
	__raw_ग_लिखोw( 'L' , PA_LED_DISP + (DISP_SEL3_ADDR << 1) );
	__raw_ग_लिखोw( 'i' , PA_LED_DISP + (DISP_SEL4_ADDR << 1) );
	__raw_ग_लिखोw( 'n' , PA_LED_DISP + (DISP_SEL5_ADDR << 1) );
	__raw_ग_लिखोw( 'u' , PA_LED_DISP + (DISP_SEL6_ADDR << 1) );
	__raw_ग_लिखोw( 'x' , PA_LED_DISP + (DISP_SEL7_ADDR << 1) );

	prपूर्णांकk(KERN_INFO "Hitachi UL Solutions Engine 7780SE03 support.\n");

	/*
	 * PCI REQ/GNT setting
	 *   REQ0/GNT0 -> USB
	 *   REQ1/GNT1 -> PC Card
	 *   REQ2/GNT2 -> Serial ATA
	 *   REQ3/GNT3 -> PCI slot
	 */
	__raw_ग_लिखोw(0x0213, FPGA_REQSEL);

	/* GPIO setting */
	__raw_ग_लिखोw(0x0000, GPIO_PECR);
	__raw_ग_लिखोw(__raw_पढ़ोw(GPIO_PHCR)&0xfff3, GPIO_PHCR);
	__raw_ग_लिखोw(0x0c00, GPIO_PMSELR);

	/* iVDR Power ON */
	__raw_ग_लिखोw(0x0001, FPGA_IVDRPW);
पूर्ण

/*
 * The Machine Vector
 */
अटल काष्ठा sh_machine_vector mv_se7780 __iniपंचांगv = अणु
	.mv_name                = "Solution Engine 7780" ,
	.mv_setup               = se7780_setup ,
	.mv_init_irq		= init_se7780_IRQ,
पूर्ण;
