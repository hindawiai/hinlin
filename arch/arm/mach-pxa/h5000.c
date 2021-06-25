<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Hardware definitions क्रम HP iPAQ h5xxx Handheld Computers
 *
 * Copyright 2000-2003  Hewlett-Packard Company.
 * Copyright 2002       Jamey Hicks <jamey.hicks@hp.com>
 * Copyright 2004-2005  Phil Blundell <pb@handhelds.org>
 * Copyright 2007-2008  Anton Vorontsov <cbouaपंचांगailru@gmail.com>
 *
 * COMPAQ COMPUTER CORPORATION MAKES NO WARRANTIES, EXPRESSED OR IMPLIED,
 * AS TO THE USEFULNESS OR CORRECTNESS OF THIS CODE OR ITS
 * FITNESS FOR ANY PARTICULAR PURPOSE.
 *
 * Author: Jamey Hicks.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/mtd/physmap.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/irq.h>

#समावेश "pxa25x.h"
#समावेश "h5000.h"
#समावेश "udc.h"
#समावेश <mach/smemc.h>

#समावेश "generic.h"

/*
 * Flash
 */

अटल काष्ठा mtd_partition h5000_flash0_partitions[] = अणु
	अणु
		.name = "bootldr",
		.size = 0x00040000,
		.offset = 0,
		.mask_flags = MTD_WRITEABLE,
	पूर्ण,
	अणु
		.name = "root",
		.size = MTDPART_SIZ_FULL,
		.offset = MTDPART_OFS_APPEND,
	पूर्ण,
पूर्ण;

अटल काष्ठा mtd_partition h5000_flash1_partitions[] = अणु
	अणु
		.name = "second root",
		.size = SZ_16M - 0x00040000,
		.offset = 0,
	पूर्ण,
	अणु
		.name = "asset",
		.size = MTDPART_SIZ_FULL,
		.offset = MTDPART_OFS_APPEND,
		.mask_flags = MTD_WRITEABLE,
	पूर्ण,
पूर्ण;

अटल काष्ठा physmap_flash_data h5000_flash0_data = अणु
	.width = 4,
	.parts = h5000_flash0_partitions,
	.nr_parts = ARRAY_SIZE(h5000_flash0_partitions),
पूर्ण;

अटल काष्ठा physmap_flash_data h5000_flash1_data = अणु
	.width = 4,
	.parts = h5000_flash1_partitions,
	.nr_parts = ARRAY_SIZE(h5000_flash1_partitions),
पूर्ण;

अटल काष्ठा resource h5000_flash0_resources = अणु
	.start = PXA_CS0_PHYS,
	.end = PXA_CS0_PHYS + SZ_32M - 1,
	.flags = IORESOURCE_MEM | IORESOURCE_MEM_32BIT,
पूर्ण;

अटल काष्ठा resource h5000_flash1_resources = अणु
	.start = PXA_CS0_PHYS + SZ_32M,
	.end = PXA_CS0_PHYS + SZ_32M + SZ_16M - 1,
	.flags = IORESOURCE_MEM | IORESOURCE_MEM_32BIT,
पूर्ण;

अटल काष्ठा platक्रमm_device h5000_flash[] = अणु
	अणु
		.name = "physmap-flash",
		.id = 0,
		.resource = &h5000_flash0_resources,
		.num_resources = 1,
		.dev = अणु
			.platक्रमm_data = &h5000_flash0_data,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "physmap-flash",
		.id = 1,
		.resource = &h5000_flash1_resources,
		.num_resources = 1,
		.dev = अणु
			.platक्रमm_data = &h5000_flash1_data,
		पूर्ण,
	पूर्ण,
पूर्ण;

/*
 * USB Device Controller
 */

अटल काष्ठा pxa2xx_udc_mach_info h5000_udc_mach_info __initdata = अणु
	.gpio_pullup = H5000_GPIO_USB_PULLUP,
पूर्ण;

/*
 * GPIO setup
 */

अटल अचिन्हित दीर्घ h5000_pin_config[] __initdata = अणु
	/* Crystal and Clock Signals */
	GPIO12_32KHz,

	/* SDRAM and Static Memory I/O Signals */
	GPIO15_nCS_1,
	GPIO78_nCS_2,
	GPIO79_nCS_3,
	GPIO80_nCS_4,

	/* FFUART */
	GPIO34_FFUART_RXD,
	GPIO35_FFUART_CTS,
	GPIO36_FFUART_DCD,
	GPIO37_FFUART_DSR,
	GPIO38_FFUART_RI,
	GPIO39_FFUART_TXD,
	GPIO40_FFUART_DTR,
	GPIO41_FFUART_RTS,

	/* BTUART */
	GPIO42_BTUART_RXD,
	GPIO43_BTUART_TXD,
	GPIO44_BTUART_CTS,
	GPIO45_BTUART_RTS,

	/* SSP1 */
	GPIO23_SSP1_SCLK,
	GPIO25_SSP1_TXD,
	GPIO26_SSP1_RXD,

	/* I2S */
	GPIO28_I2S_BITCLK_OUT,
	GPIO29_I2S_SDATA_IN,
	GPIO30_I2S_SDATA_OUT,
	GPIO31_I2S_SYNC,
	GPIO32_I2S_SYSCLK,
पूर्ण;

/*
 * Localbus setup:
 * CS0: Flash;
 * CS1: MediaQ chip, select 16-bit bus and vlio;
 * CS5: SAMCOP.
 */

अटल व्योम fix_msc(व्योम)
अणु
	__raw_ग_लिखोl(0x129c24f2, MSC0);
	__raw_ग_लिखोl(0x7ff424fa, MSC1);
	__raw_ग_लिखोl(0x7ff47ff4, MSC2);

	__raw_ग_लिखोl(__raw_पढ़ोl(MDREFR) | 0x02080000, MDREFR);
पूर्ण

/*
 * Platक्रमm devices
 */

अटल काष्ठा platक्रमm_device *devices[] __initdata = अणु
	&h5000_flash[0],
	&h5000_flash[1],
पूर्ण;

अटल व्योम __init h5000_init(व्योम)
अणु
	fix_msc();

	pxa2xx_mfp_config(ARRAY_AND_SIZE(h5000_pin_config));
	pxa_set_ffuart_info(शून्य);
	pxa_set_btuart_info(शून्य);
	pxa_set_stuart_info(शून्य);
	pxa_set_udc_info(&h5000_udc_mach_info);
	platक्रमm_add_devices(ARRAY_AND_SIZE(devices));
पूर्ण

MACHINE_START(H5400, "HP iPAQ H5000")
	.atag_offset = 0x100,
	.map_io = pxa25x_map_io,
	.nr_irqs = PXA_NR_IRQS,
	.init_irq = pxa25x_init_irq,
	.handle_irq = pxa25x_handle_irq,
	.init_समय	= pxa_समयr_init,
	.init_machine = h5000_init,
	.restart	= pxa_restart,
MACHINE_END
