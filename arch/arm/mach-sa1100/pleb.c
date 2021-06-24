<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/arch/arm/mach-sa1100/pleb.c
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/tty.h>
#समावेश <linux/ioport.h>
#समावेश <linux/platक्रमm_data/sa11x0-serial.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/irq.h>
#समावेश <linux/पन.स>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/smc91x.h>

#समावेश <mach/hardware.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/mach-types.h>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/mach/flash.h>
#समावेश <mach/irqs.h>

#समावेश "generic.h"


/*
 * Ethernet IRQ mappings
 */

#घोषणा PLEB_ETH0_P		(0x20000300)	/* Ethernet 0 in PCMCIA0 IO */
#घोषणा PLEB_ETH0_V		(0xf6000300)

#घोषणा GPIO_ETH0_IRQ		GPIO_GPIO(21)
#घोषणा GPIO_ETH0_EN		GPIO_GPIO(26)

#घोषणा IRQ_GPIO_ETH0_IRQ	IRQ_GPIO21

अटल काष्ठा resource smc91x_resources[] = अणु
	[0] = DEFINE_RES_MEM(PLEB_ETH0_P, 0x04000000),
#अगर 0 /* Autoprobe instead, to get rising/falling edge अक्षरacteristic right */
	[1] = DEFINE_RES_IRQ(IRQ_GPIO_ETH0_IRQ),
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा smc91x_platdata smc91x_platdata = अणु
	.flags = SMC91X_USE_16BIT | SMC91X_USE_8BIT | SMC91X_NOWAIT,
पूर्ण;

अटल काष्ठा platक्रमm_device smc91x_device = अणु
	.name		= "smc91x",
	.id		= 0,
	.num_resources	= ARRAY_SIZE(smc91x_resources),
	.resource	= smc91x_resources,
	.dev = अणु
		.platक्रमm_data  = &smc91x_platdata,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device *devices[] __initdata = अणु
	&smc91x_device,
पूर्ण;


/*
 * Pleb's memory map
 * has flash memory (typically 4 or 8 meg) selected by
 * the two SA1100 lowest chip select outमाला_दो.
 */
अटल काष्ठा resource pleb_flash_resources[] = अणु
	[0] = DEFINE_RES_MEM(SA1100_CS0_PHYS, SZ_8M),
	[1] = DEFINE_RES_MEM(SA1100_CS1_PHYS, SZ_8M),
पूर्ण;


अटल काष्ठा mtd_partition pleb_partitions[] = अणु
	अणु
		.name		= "blob",
		.offset		= 0,
		.size		= 0x00020000,
	पूर्ण, अणु
		.name		= "kernel",
		.offset		= MTDPART_OFS_APPEND,
		.size		= 0x000e0000,
	पूर्ण, अणु
		.name		= "rootfs",
		.offset		= MTDPART_OFS_APPEND,
		.size		= 0x00300000,
	पूर्ण
पूर्ण;


अटल काष्ठा flash_platक्रमm_data pleb_flash_data = अणु
	.map_name = "cfi_probe",
	.parts = pleb_partitions,
	.nr_parts = ARRAY_SIZE(pleb_partitions),
पूर्ण;


अटल व्योम __init pleb_init(व्योम)
अणु
	sa11x0_रेजिस्टर_mtd(&pleb_flash_data, pleb_flash_resources,
			      ARRAY_SIZE(pleb_flash_resources));


	platक्रमm_add_devices(devices, ARRAY_SIZE(devices));
पूर्ण


अटल व्योम __init pleb_map_io(व्योम)
अणु
	sa1100_map_io();

	sa1100_रेजिस्टर_uart(0, 3);
	sa1100_रेजिस्टर_uart(1, 1);

	GAFR |= (GPIO_UART_TXD | GPIO_UART_RXD);
	GPDR |= GPIO_UART_TXD;
	GPDR &= ~GPIO_UART_RXD;
	PPAR |= PPAR_UPR;

	/*
	 * Fix expansion memory timing क्रम network card
	 */
	MECR = ((2<<10) | (2<<5) | (2<<0));

	/*
	 * Enable the SMC ethernet controller
	 */
	GPDR |= GPIO_ETH0_EN;	/* set to output */
	GPCR  = GPIO_ETH0_EN;	/* clear MCLK (enable smc) */

	GPDR &= ~GPIO_ETH0_IRQ;

	irq_set_irq_type(GPIO_ETH0_IRQ, IRQ_TYPE_EDGE_FALLING);
पूर्ण

MACHINE_START(PLEB, "PLEB")
	.map_io		= pleb_map_io,
	.nr_irqs	= SA1100_NR_IRQS,
	.init_irq	= sa1100_init_irq,
	.init_समय	= sa1100_समयr_init,
	.init_machine   = pleb_init,
	.init_late	= sa11x0_init_late,
	.restart	= sa11x0_restart,
MACHINE_END
