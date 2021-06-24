<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/arch/sh/boards/se/770x/setup.c
 *
 * Copyright (C) 2000  Kazumoto Kojima
 *
 * Hitachi SolutionEngine Support.
 *
 */
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/sh_eth.h>
#समावेश <mach-se/mach/se.h>
#समावेश <mach-se/mach/mrshpc.h>
#समावेश <यंत्र/machvec.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/smc37c93x.h>
#समावेश <यंत्र/heartbeat.h>

/*
 * Configure the Super I/O chip
 */
अटल व्योम __init smsc_config(पूर्णांक index, पूर्णांक data)
अणु
	outb_p(index, INDEX_PORT);
	outb_p(data, DATA_PORT);
पूर्ण

/* XXX: Another candidate क्रम a more generic cchip machine vector */
अटल व्योम __init smsc_setup(अक्षर **cmdline_p)
अणु
	outb_p(CONFIG_ENTER, CONFIG_PORT);
	outb_p(CONFIG_ENTER, CONFIG_PORT);

	/* FDC */
	smsc_config(CURRENT_LDN_INDEX, LDN_FDC);
	smsc_config(ACTIVATE_INDEX, 0x01);
	smsc_config(IRQ_SELECT_INDEX, 6); /* IRQ6 */

	/* AUXIO (GPIO): to use IDE1 */
	smsc_config(CURRENT_LDN_INDEX, LDN_AUXIO);
	smsc_config(GPIO46_INDEX, 0x00); /* nIOROP */
	smsc_config(GPIO47_INDEX, 0x00); /* nIOWOP */

	/* COM1 */
	smsc_config(CURRENT_LDN_INDEX, LDN_COM1);
	smsc_config(ACTIVATE_INDEX, 0x01);
	smsc_config(IO_BASE_HI_INDEX, 0x03);
	smsc_config(IO_BASE_LO_INDEX, 0xf8);
	smsc_config(IRQ_SELECT_INDEX, 4); /* IRQ4 */

	/* COM2 */
	smsc_config(CURRENT_LDN_INDEX, LDN_COM2);
	smsc_config(ACTIVATE_INDEX, 0x01);
	smsc_config(IO_BASE_HI_INDEX, 0x02);
	smsc_config(IO_BASE_LO_INDEX, 0xf8);
	smsc_config(IRQ_SELECT_INDEX, 3); /* IRQ3 */

	/* RTC */
	smsc_config(CURRENT_LDN_INDEX, LDN_RTC);
	smsc_config(ACTIVATE_INDEX, 0x01);
	smsc_config(IRQ_SELECT_INDEX, 8); /* IRQ8 */

	/* XXX: PARPORT, KBD, and MOUSE will come here... */
	outb_p(CONFIG_EXIT, CONFIG_PORT);
पूर्ण


अटल काष्ठा resource cf_ide_resources[] = अणु
	[0] = अणु
		.start  = PA_MRSHPC_IO + 0x1f0,
		.end    = PA_MRSHPC_IO + 0x1f0 + 8,
		.flags  = IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start  = PA_MRSHPC_IO + 0x1f0 + 0x206,
		.end    = PA_MRSHPC_IO + 0x1f0 + 8 + 0x206 + 8,
		.flags  = IORESOURCE_MEM,
	पूर्ण,
	[2] = अणु
		.start  = IRQ_CFCARD,
		.flags  = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device cf_ide_device  = अणु
	.name           = "pata_platform",
	.id             = -1,
	.num_resources  = ARRAY_SIZE(cf_ide_resources),
	.resource       = cf_ide_resources,
पूर्ण;

अटल अचिन्हित अक्षर heartbeat_bit_pos[] = अणु 8, 9, 10, 11, 12, 13, 14, 15 पूर्ण;

अटल काष्ठा heartbeat_data heartbeat_data = अणु
	.bit_pos	= heartbeat_bit_pos,
	.nr_bits	= ARRAY_SIZE(heartbeat_bit_pos),
पूर्ण;

अटल काष्ठा resource heartbeat_resource = अणु
	.start	= PA_LED,
	.end	= PA_LED,
	.flags	= IORESOURCE_MEM | IORESOURCE_MEM_16BIT,
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

#अगर defined(CONFIG_CPU_SUBTYPE_SH7710) ||\
	defined(CONFIG_CPU_SUBTYPE_SH7712)
/* SH771X Ethernet driver */
अटल काष्ठा sh_eth_plat_data sh_eth_plat = अणु
	.phy = PHY_ID,
	.phy_पूर्णांकerface = PHY_INTERFACE_MODE_MII,
पूर्ण;

अटल काष्ठा resource sh_eth0_resources[] = अणु
	[0] = अणु
		.start = SH_ETH0_BASE,
		.end = SH_ETH0_BASE + 0x1B8 - 1,
		.flags = IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start = SH_TSU_BASE,
		.end = SH_TSU_BASE + 0x200 - 1,
		.flags = IORESOURCE_MEM,
	पूर्ण,
	[2] = अणु
		.start = SH_ETH0_IRQ,
		.end = SH_ETH0_IRQ,
		.flags = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device sh_eth0_device = अणु
	.name = "sh771x-ether",
	.id = 0,
	.dev = अणु
		.platक्रमm_data = &sh_eth_plat,
	पूर्ण,
	.num_resources = ARRAY_SIZE(sh_eth0_resources),
	.resource = sh_eth0_resources,
पूर्ण;

अटल काष्ठा resource sh_eth1_resources[] = अणु
	[0] = अणु
		.start = SH_ETH1_BASE,
		.end = SH_ETH1_BASE + 0x1B8 - 1,
		.flags = IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start = SH_TSU_BASE,
		.end = SH_TSU_BASE + 0x200 - 1,
		.flags = IORESOURCE_MEM,
	पूर्ण,
	[2] = अणु
		.start = SH_ETH1_IRQ,
		.end = SH_ETH1_IRQ,
		.flags = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device sh_eth1_device = अणु
	.name = "sh771x-ether",
	.id = 1,
	.dev = अणु
		.platक्रमm_data = &sh_eth_plat,
	पूर्ण,
	.num_resources = ARRAY_SIZE(sh_eth1_resources),
	.resource = sh_eth1_resources,
पूर्ण;
#पूर्ण_अगर

अटल काष्ठा platक्रमm_device *se_devices[] __initdata = अणु
	&heartbeat_device,
	&cf_ide_device,
#अगर defined(CONFIG_CPU_SUBTYPE_SH7710) ||\
	defined(CONFIG_CPU_SUBTYPE_SH7712)
	&sh_eth0_device,
	&sh_eth1_device,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक __init se_devices_setup(व्योम)
अणु
	mrshpc_setup_winकरोws();
	वापस platक्रमm_add_devices(se_devices, ARRAY_SIZE(se_devices));
पूर्ण
device_initcall(se_devices_setup);

/*
 * The Machine Vector
 */
अटल काष्ठा sh_machine_vector mv_se __iniपंचांगv = अणु
	.mv_name		= "SolutionEngine",
	.mv_setup		= smsc_setup,
	.mv_init_irq		= init_se_IRQ,
पूर्ण;
