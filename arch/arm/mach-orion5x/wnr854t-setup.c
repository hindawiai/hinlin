<शैली गुरु>
/*
 * arch/arm/mach-orion5x/wnr854t-setup.c
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
#समावेश <linux/delay.h>
#समावेश <linux/mtd/physmap.h>
#समावेश <linux/mv643xx_eth.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/platक्रमm_data/dsa.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/pci.h>
#समावेश "orion5x.h"
#समावेश "common.h"
#समावेश "mpp.h"

अटल अचिन्हित पूर्णांक wnr854t_mpp_modes[] __initdata = अणु
	MPP0_GPIO,		/* Power LED green (0=on) */
	MPP1_GPIO,		/* Reset Button (0=off) */
	MPP2_GPIO,		/* Power LED blink (0=off) */
	MPP3_GPIO,		/* WAN Status LED amber (0=off) */
	MPP4_GPIO,		/* PCI पूर्णांक */
	MPP5_GPIO,		/* ??? */
	MPP6_GPIO,		/* ??? */
	MPP7_GPIO,		/* ??? */
	MPP8_UNUSED,		/* ??? */
	MPP9_GIGE,		/* GE_RXERR */
	MPP10_UNUSED,		/* ??? */
	MPP11_UNUSED,		/* ??? */
	MPP12_GIGE,		/* GE_TXD[4] */
	MPP13_GIGE,		/* GE_TXD[5] */
	MPP14_GIGE,		/* GE_TXD[6] */
	MPP15_GIGE,		/* GE_TXD[7] */
	MPP16_GIGE,		/* GE_RXD[4] */
	MPP17_GIGE,		/* GE_RXD[5] */
	MPP18_GIGE,		/* GE_RXD[6] */
	MPP19_GIGE,		/* GE_RXD[7] */
	0,
पूर्ण;

/*
 * 8M NOR flash Device bus boot chip select
 */
#घोषणा WNR854T_NOR_BOOT_BASE	0xf4000000
#घोषणा WNR854T_NOR_BOOT_SIZE	SZ_8M

अटल काष्ठा mtd_partition wnr854t_nor_flash_partitions[] = अणु
	अणु
		.name		= "kernel",
		.offset		= 0x00000000,
		.size		= 0x00100000,
	पूर्ण, अणु
		.name		= "rootfs",
		.offset		= 0x00100000,
		.size		= 0x00660000,
	पूर्ण, अणु
		.name		= "uboot",
		.offset		= 0x00760000,
		.size		= 0x00040000,
	पूर्ण,
पूर्ण;

अटल काष्ठा physmap_flash_data wnr854t_nor_flash_data = अणु
	.width		= 2,
	.parts		= wnr854t_nor_flash_partitions,
	.nr_parts	= ARRAY_SIZE(wnr854t_nor_flash_partitions),
पूर्ण;

अटल काष्ठा resource wnr854t_nor_flash_resource = अणु
	.flags		= IORESOURCE_MEM,
	.start		= WNR854T_NOR_BOOT_BASE,
	.end		= WNR854T_NOR_BOOT_BASE + WNR854T_NOR_BOOT_SIZE - 1,
पूर्ण;

अटल काष्ठा platक्रमm_device wnr854t_nor_flash = अणु
	.name			= "physmap-flash",
	.id			= 0,
	.dev		= अणु
		.platक्रमm_data	= &wnr854t_nor_flash_data,
	पूर्ण,
	.num_resources		= 1,
	.resource		= &wnr854t_nor_flash_resource,
पूर्ण;

अटल काष्ठा mv643xx_eth_platक्रमm_data wnr854t_eth_data = अणु
	.phy_addr	= MV643XX_ETH_PHY_NONE,
	.speed		= SPEED_1000,
	.duplex		= DUPLEX_FULL,
पूर्ण;

अटल काष्ठा dsa_chip_data wnr854t_चयन_chip_data = अणु
	.port_names[0] = "lan3",
	.port_names[1] = "lan4",
	.port_names[2] = "wan",
	.port_names[3] = "cpu",
	.port_names[5] = "lan1",
	.port_names[7] = "lan2",
पूर्ण;

अटल व्योम __init wnr854t_init(व्योम)
अणु
	/*
	 * Setup basic Orion functions. Need to be called early.
	 */
	orion5x_init();

	orion5x_mpp_conf(wnr854t_mpp_modes);

	/*
	 * Configure peripherals.
	 */
	orion5x_eth_init(&wnr854t_eth_data);
	orion5x_eth_चयन_init(&wnr854t_चयन_chip_data);
	orion5x_uart0_init();

	mvebu_mbus_add_winकरोw_by_id(ORION_MBUS_DEVBUS_BOOT_TARGET,
				    ORION_MBUS_DEVBUS_BOOT_ATTR,
				    WNR854T_NOR_BOOT_BASE,
				    WNR854T_NOR_BOOT_SIZE);
	platक्रमm_device_रेजिस्टर(&wnr854t_nor_flash);
पूर्ण

अटल पूर्णांक __init wnr854t_pci_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot,
	u8 pin)
अणु
	पूर्णांक irq;

	/*
	 * Check क्रम devices with hard-wired IRQs.
	 */
	irq = orion5x_pci_map_irq(dev, slot, pin);
	अगर (irq != -1)
		वापस irq;

	/*
	 * Mini-PCI slot.
	 */
	अगर (slot == 7)
		वापस gpio_to_irq(4);

	वापस -1;
पूर्ण

अटल काष्ठा hw_pci wnr854t_pci __initdata = अणु
	.nr_controllers	= 2,
	.setup		= orion5x_pci_sys_setup,
	.scan		= orion5x_pci_sys_scan_bus,
	.map_irq	= wnr854t_pci_map_irq,
पूर्ण;

अटल पूर्णांक __init wnr854t_pci_init(व्योम)
अणु
	अगर (machine_is_wnr854t())
		pci_common_init(&wnr854t_pci);

	वापस 0;
पूर्ण
subsys_initcall(wnr854t_pci_init);

MACHINE_START(WNR854T, "Netgear WNR854T")
	/* Maपूर्णांकainer: Imre Kaloz <kaloz@खोलोwrt.org> */
	.atag_offset	= 0x100,
	.nr_irqs	= ORION5X_NR_IRQS,
	.init_machine	= wnr854t_init,
	.map_io		= orion5x_map_io,
	.init_early	= orion5x_init_early,
	.init_irq	= orion5x_init_irq,
	.init_समय	= orion5x_समयr_init,
	.fixup		= tag_fixup_mem32,
	.restart	= orion5x_restart,
MACHINE_END
