<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Lyrtech SFFSDR board support.
 *
 * Copyright (C) 2008 Philip Balister, OpenSDR <philip@खोलोsdr.com>
 * Copyright (C) 2008 Lyrtech <www.lyrtech.com>
 *
 * Based on DV-EVM platक्रमm, original copyright follows:
 *
 * Copyright (C) 2007 MontaVista Software, Inc.
 */

#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/i2c.h>
#समावेश <linux/property.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/mtd/partitions.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/flash.h>

#समावेश <mach/common.h>
#समावेश <linux/platक्रमm_data/i2c-davinci.h>
#समावेश <mach/serial.h>
#समावेश <mach/mux.h>
#समावेश <linux/platक्रमm_data/usb-davinci.h>

#समावेश "davinci.h"

#घोषणा SFFSDR_PHY_ID		"davinci_mdio-0:01"
अटल काष्ठा mtd_partition davinci_sffsdr_nandflash_partition[] = अणु
	/* U-Boot Environment: Block 0
	 * UBL:                Block 1
	 * U-Boot:             Blocks 6-7 (256 kb)
	 * Integrity Kernel:   Blocks 8-31 (3 Mb)
	 * Integrity Data:     Blocks 100-END
	 */
	अणु
		.name		= "Linux Kernel",
		.offset		= 32 * SZ_128K,
		.size		= 16 * SZ_128K, /* 2 Mb */
		.mask_flags	= MTD_WRITEABLE, /* Force पढ़ो-only */
	पूर्ण,
	अणु
		.name		= "Linux ROOT",
		.offset		= MTDPART_OFS_APPEND,
		.size		= 256 * SZ_128K, /* 32 Mb */
		.mask_flags	= 0, /* R/W */
	पूर्ण,
पूर्ण;

अटल काष्ठा flash_platक्रमm_data davinci_sffsdr_nandflash_data = अणु
	.parts		= davinci_sffsdr_nandflash_partition,
	.nr_parts	= ARRAY_SIZE(davinci_sffsdr_nandflash_partition),
पूर्ण;

अटल काष्ठा resource davinci_sffsdr_nandflash_resource[] = अणु
	अणु
		.start		= DM644X_ASYNC_EMIF_DATA_CE0_BASE,
		.end		= DM644X_ASYNC_EMIF_DATA_CE0_BASE + SZ_16M - 1,
		.flags		= IORESOURCE_MEM,
	पूर्ण, अणु
		.start		= DM644X_ASYNC_EMIF_CONTROL_BASE,
		.end		= DM644X_ASYNC_EMIF_CONTROL_BASE + SZ_4K - 1,
		.flags		= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device davinci_sffsdr_nandflash_device = अणु
	.name		= "davinci_nand", /* Name of driver */
	.id		= 0,
	.dev		= अणु
		.platक्रमm_data	= &davinci_sffsdr_nandflash_data,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(davinci_sffsdr_nandflash_resource),
	.resource	= davinci_sffsdr_nandflash_resource,
पूर्ण;

अटल स्थिर काष्ठा property_entry eeprom_properties[] = अणु
	PROPERTY_ENTRY_U32("pagesize", 32),
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा software_node eeprom_node = अणु
	.properties = eeprom_properties,
पूर्ण;

अटल काष्ठा i2c_board_info __initdata i2c_info[] =  अणु
	अणु
		I2C_BOARD_INFO("24c64", 0x50),
		.swnode = &eeprom_node,
	पूर्ण,
	/* Other I2C devices:
	 * MSP430,  addr 0x23 (not used)
	 * PCA9543, addr 0x70 (setup करोne by U-Boot)
	 * ADS7828, addr 0x48 (ADC क्रम voltage monitoring.)
	 */
पूर्ण;

अटल काष्ठा davinci_i2c_platक्रमm_data i2c_pdata = अणु
	.bus_freq	= 20 /* kHz */,
	.bus_delay	= 100 /* usec */,
पूर्ण;

अटल व्योम __init sffsdr_init_i2c(व्योम)
अणु
	davinci_init_i2c(&i2c_pdata);
	i2c_रेजिस्टर_board_info(1, i2c_info, ARRAY_SIZE(i2c_info));
पूर्ण

अटल काष्ठा platक्रमm_device *davinci_sffsdr_devices[] __initdata = अणु
	&davinci_sffsdr_nandflash_device,
पूर्ण;

अटल व्योम __init davinci_sffsdr_map_io(व्योम)
अणु
	dm644x_init();
पूर्ण

अटल __init व्योम davinci_sffsdr_init(व्योम)
अणु
	काष्ठा davinci_soc_info *soc_info = &davinci_soc_info;

	dm644x_रेजिस्टर_घड़ीs();

	dm644x_init_devices();

	platक्रमm_add_devices(davinci_sffsdr_devices,
			     ARRAY_SIZE(davinci_sffsdr_devices));
	sffsdr_init_i2c();
	davinci_serial_init(dm644x_serial_device);
	soc_info->emac_pdata->phy_id = SFFSDR_PHY_ID;
	davinci_setup_usb(0, 0); /* We support only peripheral mode. */

	/* mux VLYNQ pins */
	davinci_cfg_reg(DM644X_VLYNQEN);
	davinci_cfg_reg(DM644X_VLYNQWD);
पूर्ण

MACHINE_START(SFFSDR, "Lyrtech SFFSDR")
	.atag_offset  = 0x100,
	.map_io	      = davinci_sffsdr_map_io,
	.init_irq     = dm644x_init_irq,
	.init_समय	= dm644x_init_समय,
	.init_machine = davinci_sffsdr_init,
	.init_late	= davinci_init_late,
	.dma_zone_size	= SZ_128M,
MACHINE_END
