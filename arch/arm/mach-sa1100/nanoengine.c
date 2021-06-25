<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/arch/arm/mach-sa1100/nanoengine.c
 *
 * Bright Star Engineering's nanoEngine board init code.
 *
 * Copyright (C) 2010 Marcelo Roberto Jimenez <mroberto@cpti.cetuc.puc-rio.br>
 */

#समावेश <linux/init.h>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_data/sa11x0-serial.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/root_dev.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/page.h>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/flash.h>
#समावेश <यंत्र/mach/map.h>

#समावेश <mach/hardware.h>
#समावेश <mach/nanoengine.h>
#समावेश <mach/irqs.h>

#समावेश "generic.h"

/* Flash bank 0 */
अटल काष्ठा mtd_partition nanoengine_partitions[] = अणु
	अणु
		.name	= "nanoEngine boot firmware and parameter table",
		.size		= 0x00010000,  /* 32K */
		.offset		= 0,
		.mask_flags	= MTD_WRITEABLE,
	पूर्ण, अणु
		.name		= "kernel/initrd reserved",
		.size		= 0x002f0000,
		.offset		= 0x00010000,
		.mask_flags	= MTD_WRITEABLE,
	पूर्ण, अणु
		.name		= "experimental filesystem allocation",
		.size		= 0x00100000,
		.offset		= 0x00300000,
		.mask_flags	= MTD_WRITEABLE,
	पूर्ण
पूर्ण;

अटल काष्ठा flash_platक्रमm_data nanoengine_flash_data = अणु
	.map_name	= "jedec_probe",
	.parts		= nanoengine_partitions,
	.nr_parts	= ARRAY_SIZE(nanoengine_partitions),
पूर्ण;

अटल काष्ठा resource nanoengine_flash_resources[] = अणु
	DEFINE_RES_MEM(SA1100_CS0_PHYS, SZ_32M),
	DEFINE_RES_MEM(SA1100_CS1_PHYS, SZ_32M),
पूर्ण;

अटल काष्ठा map_desc nanoengine_io_desc[] __initdata = अणु
	अणु
		/* System Registers */
		.भव	= 0xf0000000,
		.pfn		= __phys_to_pfn(0x10000000),
		.length		= 0x00100000,
		.type		= MT_DEVICE
	पूर्ण, अणु
		/* Internal PCI Memory Read/Write */
		.भव	= न_अंकO_PCI_MEM_RW_VIRT,
		.pfn		= __phys_to_pfn(न_अंकO_PCI_MEM_RW_PHYS),
		.length		= न_अंकO_PCI_MEM_RW_SIZE,
		.type		= MT_DEVICE
	पूर्ण, अणु
		/* Internal PCI Config Space */
		.भव	= न_अंकO_PCI_CONFIG_SPACE_VIRT,
		.pfn		= __phys_to_pfn(न_अंकO_PCI_CONFIG_SPACE_PHYS),
		.length		= न_अंकO_PCI_CONFIG_SPACE_SIZE,
		.type		= MT_DEVICE
	पूर्ण
पूर्ण;

अटल व्योम __init nanoengine_map_io(व्योम)
अणु
	sa1100_map_io();
	iotable_init(nanoengine_io_desc, ARRAY_SIZE(nanoengine_io_desc));

	sa1100_रेजिस्टर_uart(0, 1);
	sa1100_रेजिस्टर_uart(1, 2);
	sa1100_रेजिस्टर_uart(2, 3);
	Ser1SDCR0 |= SDCR0_UART;
	/* disable IRDA -- UART2 is used as a normal serial port */
	Ser2UTCR4 = 0;
	Ser2HSCR0 = 0;
पूर्ण

अटल काष्ठा gpiod_lookup_table nanoengine_pcmcia0_gpio_table = अणु
	.dev_id = "sa11x0-pcmcia.0",
	.table = अणु
		GPIO_LOOKUP("gpio", 11, "ready", GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP("gpio", 13, "detect", GPIO_ACTIVE_LOW),
		GPIO_LOOKUP("gpio", 15, "reset", GPIO_ACTIVE_HIGH),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpiod_lookup_table nanoengine_pcmcia1_gpio_table = अणु
	.dev_id = "sa11x0-pcmcia.1",
	.table = अणु
		GPIO_LOOKUP("gpio", 12, "ready", GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP("gpio", 14, "detect", GPIO_ACTIVE_LOW),
		GPIO_LOOKUP("gpio", 16, "reset", GPIO_ACTIVE_HIGH),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल व्योम __init nanoengine_init(व्योम)
अणु
	sa11x0_रेजिस्टर_pcmcia(0, &nanoengine_pcmcia0_gpio_table);
	sa11x0_रेजिस्टर_pcmcia(1, &nanoengine_pcmcia1_gpio_table);
	sa11x0_रेजिस्टर_mtd(&nanoengine_flash_data, nanoengine_flash_resources,
		ARRAY_SIZE(nanoengine_flash_resources));
पूर्ण

MACHINE_START(न_अंकOENGINE, "BSE nanoEngine")
	.atag_offset	= 0x100,
	.map_io		= nanoengine_map_io,
	.nr_irqs	= SA1100_NR_IRQS,
	.init_irq	= sa1100_init_irq,
	.init_समय	= sa1100_समयr_init,
	.init_machine	= nanoengine_init,
	.init_late	= sa11x0_init_late,
	.restart	= sa11x0_restart,
MACHINE_END
