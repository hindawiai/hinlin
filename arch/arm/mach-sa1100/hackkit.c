<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/arch/arm/mach-sa1100/hackkit.c
 *
 * Copyright (C) 2002 Stefan Eletzhofer <stefan.eletzhofer@eletztrick.de>
 *
 * This file contains all HackKit tweaks. Based on original work from
 * Nicolas Pitre's assabet fixes
 */
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/tty.h>
#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/cpufreq.h>
#समावेश <linux/platक्रमm_data/sa11x0-serial.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/tty.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/leds.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/page.h>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/flash.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/mach/irq.h>

#समावेश <mach/hardware.h>
#समावेश <mach/irqs.h>

#समावेश "generic.h"

/**********************************************************************
 *  prototypes
 */

/* init funcs */
अटल व्योम __init hackkit_map_io(व्योम);

अटल व्योम hackkit_uart_pm(काष्ठा uart_port *port, u_पूर्णांक state, u_पूर्णांक oldstate);

/**********************************************************************
 *  global data
 */

/**********************************************************************
 *  अटल data
 */

अटल काष्ठा map_desc hackkit_io_desc[] __initdata = अणु
	अणु	/* Flash bank 0 */
		.भव	=  0xe8000000,
		.pfn		= __phys_to_pfn(0x00000000),
		.length		= 0x01000000,
		.type		= MT_DEVICE
	पूर्ण,
पूर्ण;

अटल काष्ठा sa1100_port_fns hackkit_port_fns __initdata = अणु
	.pm		= hackkit_uart_pm,
पूर्ण;

/**********************************************************************
 *  Static functions
 */

अटल व्योम __init hackkit_map_io(व्योम)
अणु
	sa1100_map_io();
	iotable_init(hackkit_io_desc, ARRAY_SIZE(hackkit_io_desc));

	sa1100_रेजिस्टर_uart_fns(&hackkit_port_fns);
	sa1100_रेजिस्टर_uart(0, 1);	/* com port */
	sa1100_रेजिस्टर_uart(1, 2);
	sa1100_रेजिस्टर_uart(2, 3);	/* radio module */

	Ser1SDCR0 |= SDCR0_SUS;
पूर्ण

/**
 *	hackkit_uart_pm - घातermgmt callback function क्रम प्रणाली 3 UART
 *	@port: uart port काष्ठाure
 *	@state: pm state
 *	@oldstate: old pm state
 *
 */
अटल व्योम hackkit_uart_pm(काष्ठा uart_port *port, u_पूर्णांक state, u_पूर्णांक oldstate)
अणु
	/* TODO: चयन on/off uart in घातersave mode */
पूर्ण

अटल काष्ठा mtd_partition hackkit_partitions[] = अणु
	अणु
		.name		= "BLOB",
		.size		= 0x00040000,
		.offset		= 0x00000000,
		.mask_flags	= MTD_WRITEABLE,  /* क्रमce पढ़ो-only */
	पूर्ण, अणु
		.name		= "config",
		.size		= 0x00040000,
		.offset		= MTDPART_OFS_APPEND,
	पूर्ण, अणु
		.name		= "kernel",
		.size		= 0x00100000,
		.offset		= MTDPART_OFS_APPEND,
	पूर्ण, अणु
		.name		= "initrd",
		.size		= 0x00180000,
		.offset		= MTDPART_OFS_APPEND,
	पूर्ण, अणु
		.name		= "rootfs",
		.size		= 0x700000,
		.offset		= MTDPART_OFS_APPEND,
	पूर्ण, अणु
		.name		= "data",
		.size		= MTDPART_SIZ_FULL,
		.offset		= MTDPART_OFS_APPEND,
	पूर्ण
पूर्ण;

अटल काष्ठा flash_platक्रमm_data hackkit_flash_data = अणु
	.map_name	= "cfi_probe",
	.parts		= hackkit_partitions,
	.nr_parts	= ARRAY_SIZE(hackkit_partitions),
पूर्ण;

अटल काष्ठा resource hackkit_flash_resource =
	DEFINE_RES_MEM(SA1100_CS0_PHYS, SZ_32M);

/* LEDs */
काष्ठा gpio_led hackkit_gpio_leds[] = अणु
	अणु
		.name			= "hackkit:red",
		.शेष_trigger	= "cpu0",
		.gpio			= 22,
	पूर्ण,
	अणु
		.name			= "hackkit:green",
		.शेष_trigger	= "heartbeat",
		.gpio			= 23,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_led_platक्रमm_data hackkit_gpio_led_info = अणु
	.leds		= hackkit_gpio_leds,
	.num_leds	= ARRAY_SIZE(hackkit_gpio_leds),
पूर्ण;

अटल काष्ठा platक्रमm_device hackkit_leds = अणु
	.name	= "leds-gpio",
	.id	= -1,
	.dev	= अणु
		.platक्रमm_data	= &hackkit_gpio_led_info,
	पूर्ण
पूर्ण;

अटल व्योम __init hackkit_init(व्योम)
अणु
	sa11x0_रेजिस्टर_mtd(&hackkit_flash_data, &hackkit_flash_resource, 1);
	platक्रमm_device_रेजिस्टर(&hackkit_leds);
पूर्ण

/**********************************************************************
 *  Exported Functions
 */

MACHINE_START(HACKKIT, "HackKit Cpu Board")
	.atag_offset	= 0x100,
	.map_io		= hackkit_map_io,
	.nr_irqs	= SA1100_NR_IRQS,
	.init_irq	= sa1100_init_irq,
	.init_समय	= sa1100_समयr_init,
	.init_machine	= hackkit_init,
	.init_late	= sa11x0_init_late,
	.restart	= sa11x0_restart,
MACHINE_END
