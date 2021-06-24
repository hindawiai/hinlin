<शैली गुरु>
/*
 * arch/arm/mach-orion5x/rd88f6183-ap-ge-setup.c
 *
 * Marvell Orion-1-90 AP GE Reference Design Setup
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */
#समावेश <linux/gpपन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pci.h>
#समावेश <linux/irq.h>
#समावेश <linux/mtd/physmap.h>
#समावेश <linux/mv643xx_eth.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/flash.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/platक्रमm_data/dsa.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/pci.h>
#समावेश "common.h"
#समावेश "orion5x.h"

अटल काष्ठा mv643xx_eth_platक्रमm_data rd88f6183ap_ge_eth_data = अणु
	.phy_addr	= -1,
	.speed		= SPEED_1000,
	.duplex		= DUPLEX_FULL,
पूर्ण;

अटल काष्ठा dsa_chip_data rd88f6183ap_ge_चयन_chip_data = अणु
	.port_names[0]	= "lan1",
	.port_names[1]	= "lan2",
	.port_names[2]	= "lan3",
	.port_names[3]	= "lan4",
	.port_names[4]	= "wan",
	.port_names[5]	= "cpu",
पूर्ण;

अटल काष्ठा mtd_partition rd88f6183ap_ge_partitions[] = अणु
	अणु
		.name	= "kernel",
		.offset	= 0x00000000,
		.size	= 0x00200000,
	पूर्ण, अणु
		.name	= "rootfs",
		.offset	= 0x00200000,
		.size	= 0x00500000,
	पूर्ण, अणु
		.name	= "nvram",
		.offset	= 0x00700000,
		.size	= 0x00080000,
	पूर्ण,
पूर्ण;

अटल काष्ठा flash_platक्रमm_data rd88f6183ap_ge_spi_slave_data = अणु
	.type		= "m25p64",
	.nr_parts	= ARRAY_SIZE(rd88f6183ap_ge_partitions),
	.parts		= rd88f6183ap_ge_partitions,
पूर्ण;

अटल काष्ठा spi_board_info __initdata rd88f6183ap_ge_spi_slave_info[] = अणु
	अणु
		.modalias	= "m25p80",
		.platक्रमm_data	= &rd88f6183ap_ge_spi_slave_data,
		.max_speed_hz	= 20000000,
		.bus_num	= 0,
		.chip_select	= 0,
	पूर्ण,
पूर्ण;

अटल व्योम __init rd88f6183ap_ge_init(व्योम)
अणु
	/*
	 * Setup basic Orion functions. Need to be called early.
	 */
	orion5x_init();

	/*
	 * Configure peripherals.
	 */
	orion5x_ehci0_init();
	orion5x_eth_init(&rd88f6183ap_ge_eth_data);
	orion5x_eth_चयन_init(&rd88f6183ap_ge_चयन_chip_data);
	spi_रेजिस्टर_board_info(rd88f6183ap_ge_spi_slave_info,
				ARRAY_SIZE(rd88f6183ap_ge_spi_slave_info));
	orion5x_spi_init();
	orion5x_uart0_init();
पूर्ण

अटल काष्ठा hw_pci rd88f6183ap_ge_pci __initdata = अणु
	.nr_controllers	= 2,
	.setup		= orion5x_pci_sys_setup,
	.scan		= orion5x_pci_sys_scan_bus,
	.map_irq	= orion5x_pci_map_irq,
पूर्ण;

अटल पूर्णांक __init rd88f6183ap_ge_pci_init(व्योम)
अणु
	अगर (machine_is_rd88f6183ap_ge()) अणु
		orion5x_pci_disable();
		pci_common_init(&rd88f6183ap_ge_pci);
	पूर्ण

	वापस 0;
पूर्ण
subsys_initcall(rd88f6183ap_ge_pci_init);

MACHINE_START(RD88F6183AP_GE, "Marvell Orion-1-90 AP GE Reference Design")
	/* Maपूर्णांकainer: Lennert Buytenhek <buytenh@marvell.com> */
	.atag_offset	= 0x100,
	.nr_irqs	= ORION5X_NR_IRQS,
	.init_machine	= rd88f6183ap_ge_init,
	.map_io		= orion5x_map_io,
	.init_early	= orion5x_init_early,
	.init_irq	= orion5x_init_irq,
	.init_समय	= orion5x_समयr_init,
	.fixup		= tag_fixup_mem32,
	.restart	= orion5x_restart,
MACHINE_END
