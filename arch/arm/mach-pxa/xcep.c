<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*  linux/arch/arm/mach-pxa/xcep.c
 *
 *  Support क्रम the Iskratel Electronics XCEP platक्रमm as used in
 *  the Libera instruments from Instrumentation Technologies.
 *
 *  Author:     Ales Barकरोrfer <ales@i-tech.si>
 *  Contributions by: Abbott, MG (Michael) <michael.abbott@diamond.ac.uk>
 *  Contributions by: Matej Kenda <matej.kenda@i-tech.si>
 *  Created:    June 2006
 *  Copyright:  (C) 2006-2009 Instrumentation Technologies
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/i2c.h>
#समावेश <linux/platक्रमm_data/i2c-pxa.h>
#समावेश <linux/smc91x.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/mtd/physmap.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/irq.h>
#समावेश <यंत्र/mach/map.h>

#समावेश <mach/hardware.h>
#समावेश "pxa25x.h"
#समावेश <mach/smemc.h>

#समावेश "generic.h"
#समावेश "devices.h"

#घोषणा XCEP_ETH_PHYS		(PXA_CS3_PHYS + 0x00000300)
#घोषणा XCEP_ETH_PHYS_END	(PXA_CS3_PHYS + 0x000fffff)
#घोषणा XCEP_ETH_ATTR		(PXA_CS3_PHYS + 0x02000000)
#घोषणा XCEP_ETH_ATTR_END	(PXA_CS3_PHYS + 0x020fffff)
#घोषणा XCEP_ETH_IRQ		IRQ_GPIO0

/*  XCEP CPLD base */
#घोषणा XCEP_CPLD_BASE		0xf0000000


/* Flash partitions. */

अटल काष्ठा mtd_partition xcep_partitions[] = अणु
	अणु
		.name =		"Bootloader",
		.size =		0x00040000,
		.offset =	0,
		.mask_flags =	MTD_WRITEABLE
	पूर्ण, अणु
		.name =		"Bootloader ENV",
		.size =		0x00040000,
		.offset =	0x00040000,
		.mask_flags =	MTD_WRITEABLE
	पूर्ण, अणु
		.name =		"Kernel",
		.size =		0x00100000,
		.offset =	0x00080000,
	पूर्ण, अणु
		.name =		"Rescue fs",
		.size =		0x00280000,
		.offset =	0x00180000,
	पूर्ण, अणु
		.name =		"Filesystem",
		.size =		MTDPART_SIZ_FULL,
		.offset =	0x00400000
	पूर्ण
पूर्ण;

अटल काष्ठा physmap_flash_data xcep_flash_data[] = अणु
	अणु
		.width		= 4,		/* bankwidth in bytes */
		.parts		= xcep_partitions,
		.nr_parts	= ARRAY_SIZE(xcep_partitions)
	पूर्ण
पूर्ण;

अटल काष्ठा resource flash_resource = अणु
	.start	= PXA_CS0_PHYS,
	.end	= PXA_CS0_PHYS + SZ_32M - 1,
	.flags	= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा platक्रमm_device flash_device = अणु
	.name	= "physmap-flash",
	.id	= 0,
	.dev 	= अणु
		.platक्रमm_data = xcep_flash_data,
	पूर्ण,
	.resource = &flash_resource,
	.num_resources = 1,
पूर्ण;



/* SMC LAN91C111 network controller. */

अटल काष्ठा resource smc91x_resources[] = अणु
	[0] = अणु
		.name	= "smc91x-regs",
		.start	= XCEP_ETH_PHYS,
		.end	= XCEP_ETH_PHYS_END,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= XCEP_ETH_IRQ,
		.end	= XCEP_ETH_IRQ,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	[2] = अणु
		.name	= "smc91x-attrib",
		.start	= XCEP_ETH_ATTR,
		.end	= XCEP_ETH_ATTR_END,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा smc91x_platdata xcep_smc91x_info = अणु
	.flags	= SMC91X_USE_8BIT | SMC91X_USE_16BIT | SMC91X_USE_32BIT |
		  SMC91X_NOWAIT | SMC91X_USE_DMA,
पूर्ण;

अटल काष्ठा platक्रमm_device smc91x_device = अणु
	.name		= "smc91x",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(smc91x_resources),
	.resource	= smc91x_resources,
	.dev		= अणु
		.platक्रमm_data = &xcep_smc91x_info,
	पूर्ण,
पूर्ण;


अटल काष्ठा platक्रमm_device *devices[] __initdata = अणु
	&flash_device,
	&smc91x_device,
पूर्ण;


/* We have to state that there are HWMON devices on the I2C bus on XCEP.
 * Drivers क्रम HWMON verअगरy capabilities of the adapter when loading and
 * refuse to attach अगर the adapter करोesn't support HWMON class of devices. */
अटल काष्ठा i2c_pxa_platक्रमm_data xcep_i2c_platक्रमm_data  = अणु
	.class = I2C_CLASS_HWMON
पूर्ण;


अटल mfp_cfg_t xcep_pin_config[] __initdata = अणु
	GPIO79_nCS_3,	/* SMC 91C111 chip select. */
	GPIO80_nCS_4,	/* CPLD chip select. */
	/* SSP communication to MSP430 */
	GPIO23_SSP1_SCLK,
	GPIO24_SSP1_SFRM,
	GPIO25_SSP1_TXD,
	GPIO26_SSP1_RXD,
	GPIO27_SSP1_EXTCLK
पूर्ण;

अटल व्योम __init xcep_init(व्योम)
अणु
	pxa2xx_mfp_config(ARRAY_AND_SIZE(xcep_pin_config));

	pxa_set_ffuart_info(शून्य);
	pxa_set_btuart_info(शून्य);
	pxa_set_stuart_info(शून्य);
	pxa_set_hwuart_info(शून्य);

	/* See Intel XScale Developer's Guide क्रम details */
	/* Set RDF and RDN to appropriate values (chip select 3 (smc91x)) */
	__raw_ग_लिखोl((__raw_पढ़ोl(MSC1) & 0xffff) | 0xD5540000, MSC1);
	/* Set RDF and RDN to appropriate values (chip select 5 (fpga)) */
	__raw_ग_लिखोl((__raw_पढ़ोl(MSC2) & 0xffff) | 0x72A00000, MSC2);

	platक्रमm_add_devices(ARRAY_AND_SIZE(devices));
	pxa_set_i2c_info(&xcep_i2c_platक्रमm_data);
पूर्ण

MACHINE_START(XCEP, "Iskratel XCEP")
	.atag_offset	= 0x100,
	.init_machine	= xcep_init,
	.map_io		= pxa25x_map_io,
	.nr_irqs	= PXA_NR_IRQS,
	.init_irq	= pxa25x_init_irq,
	.handle_irq	= pxa25x_handle_irq,
	.init_समय	= pxa_समयr_init,
	.restart	= pxa_restart,
MACHINE_END

