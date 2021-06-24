<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Data Technology Inc. ESPT-GIGA board support
 *
 * Copyright (C) 2008, 2009 Renesas Solutions Corp.
 * Copyright (C) 2008, 2009 Nobuhiro Iwamatsu <iwamatsu.nobuhiro@renesas.com>
 */
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mtd/physmap.h>
#समावेश <linux/पन.स>
#समावेश <linux/sh_eth.h>
#समावेश <linux/sh_पूर्णांकc.h>
#समावेश <यंत्र/machvec.h>
#समावेश <linux/sizes.h>

/* NOR Flash */
अटल काष्ठा mtd_partition espt_nor_flash_partitions[] = अणु
	अणु
		.name = "U-Boot",
		.offset = 0,
		.size = (2 * SZ_128K),
		.mask_flags = MTD_WRITEABLE,	/* Read-only */
	पूर्ण, अणु
		.name = "Linux-Kernel",
		.offset = MTDPART_OFS_APPEND,
		.size = (20 * SZ_128K),
	पूर्ण, अणु
		.name = "Root Filesystem",
		.offset = MTDPART_OFS_APPEND,
		.size = MTDPART_SIZ_FULL,
	पूर्ण,
पूर्ण;

अटल काष्ठा physmap_flash_data espt_nor_flash_data = अणु
	.width = 2,
	.parts = espt_nor_flash_partitions,
	.nr_parts = ARRAY_SIZE(espt_nor_flash_partitions),
पूर्ण;

अटल काष्ठा resource espt_nor_flash_resources[] = अणु
	[0] = अणु
		.name = "NOR Flash",
		.start = 0,
		.end = SZ_8M - 1,
		.flags = IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device espt_nor_flash_device = अणु
	.name = "physmap-flash",
	.resource = espt_nor_flash_resources,
	.num_resources = ARRAY_SIZE(espt_nor_flash_resources),
	.dev = अणु
		.platक्रमm_data = &espt_nor_flash_data,
	पूर्ण,
पूर्ण;

/* SH-Ether */
अटल काष्ठा resource sh_eth_resources[] = अणु
	अणु
		.start  = 0xFEE00800,   /* use eth1 */
		.end    = 0xFEE00F7C - 1,
		.flags  = IORESOURCE_MEM,
	पूर्ण, अणु
		.start  = 0xFEE01800,   /* TSU */
		.end    = 0xFEE01FFF,
		.flags  = IORESOURCE_MEM,
	पूर्ण, अणु

		.start  = evt2irq(0x920),   /* irq number */
		.flags  = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा sh_eth_plat_data sh7763_eth_pdata = अणु
	.phy = 0,
	.phy_पूर्णांकerface = PHY_INTERFACE_MODE_MII,
पूर्ण;

अटल काष्ठा platक्रमm_device espt_eth_device = अणु
	.name       = "sh7763-gether",
	.resource   = sh_eth_resources,
	.num_resources  = ARRAY_SIZE(sh_eth_resources),
	.dev        = अणु
		.platक्रमm_data = &sh7763_eth_pdata,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device *espt_devices[] __initdata = अणु
	&espt_nor_flash_device,
	&espt_eth_device,
पूर्ण;

अटल पूर्णांक __init espt_devices_setup(व्योम)
अणु
	वापस platक्रमm_add_devices(espt_devices,
				    ARRAY_SIZE(espt_devices));
पूर्ण
device_initcall(espt_devices_setup);

अटल काष्ठा sh_machine_vector mv_espt __iniपंचांगv = अणु
	.mv_name = "ESPT-GIGA",
पूर्ण;
