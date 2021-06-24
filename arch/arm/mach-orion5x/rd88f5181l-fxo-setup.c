<शैली गुरु>
/*
 * arch/arm/mach-orion5x/rd88f5181l-fxo-setup.c
 *
 * Marvell Orion-VoIP FXO Reference Design Setup
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
#समावेश <linux/ethtool.h>
#समावेश <linux/platक्रमm_data/dsa.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/pci.h>
#समावेश "common.h"
#समावेश "mpp.h"
#समावेश "orion5x.h"

/*****************************************************************************
 * RD-88F5181L FXO Info
 ****************************************************************************/
/*
 * 8M NOR flash Device bus boot chip select
 */
#घोषणा RD88F5181L_FXO_NOR_BOOT_BASE		0xff800000
#घोषणा RD88F5181L_FXO_NOR_BOOT_SIZE		SZ_8M


/*****************************************************************************
 * 8M NOR Flash on Device bus Boot chip select
 ****************************************************************************/
अटल काष्ठा physmap_flash_data rd88f5181l_fxo_nor_boot_flash_data = अणु
	.width		= 1,
पूर्ण;

अटल काष्ठा resource rd88f5181l_fxo_nor_boot_flash_resource = अणु
	.flags		= IORESOURCE_MEM,
	.start		= RD88F5181L_FXO_NOR_BOOT_BASE,
	.end		= RD88F5181L_FXO_NOR_BOOT_BASE +
			  RD88F5181L_FXO_NOR_BOOT_SIZE - 1,
पूर्ण;

अटल काष्ठा platक्रमm_device rd88f5181l_fxo_nor_boot_flash = अणु
	.name			= "physmap-flash",
	.id			= 0,
	.dev		= अणु
		.platक्रमm_data	= &rd88f5181l_fxo_nor_boot_flash_data,
	पूर्ण,
	.num_resources		= 1,
	.resource		= &rd88f5181l_fxo_nor_boot_flash_resource,
पूर्ण;


/*****************************************************************************
 * General Setup
 ****************************************************************************/
अटल अचिन्हित पूर्णांक rd88f5181l_fxo_mpp_modes[] __initdata = अणु
	MPP0_GPIO,		/* LED1 CardBus LED (front panel) */
	MPP1_GPIO,		/* PCI_पूर्णांकA */
	MPP2_GPIO,		/* Hard Reset / Factory Init*/
	MPP3_GPIO,		/* FXS or DAA select */
	MPP4_GPIO,		/* LED6 - phone LED (front panel) */
	MPP5_GPIO,		/* LED5 - phone LED (front panel) */
	MPP6_PCI_CLK,		/* CPU PCI refclk */
	MPP7_PCI_CLK,		/* PCI/PCIe refclk */
	MPP8_GPIO,		/* CardBus reset */
	MPP9_GPIO,		/* GE_RXERR */
	MPP10_GPIO,		/* LED2 MiniPCI LED (front panel) */
	MPP11_GPIO,		/* Lअगरeline control */
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

अटल काष्ठा mv643xx_eth_platक्रमm_data rd88f5181l_fxo_eth_data = अणु
	.phy_addr	= MV643XX_ETH_PHY_NONE,
	.speed		= SPEED_1000,
	.duplex		= DUPLEX_FULL,
पूर्ण;

अटल काष्ठा dsa_chip_data rd88f5181l_fxo_चयन_chip_data = अणु
	.port_names[0]	= "lan2",
	.port_names[1]	= "lan1",
	.port_names[2]	= "wan",
	.port_names[3]	= "cpu",
	.port_names[5]	= "lan4",
	.port_names[7]	= "lan3",
पूर्ण;

अटल व्योम __init rd88f5181l_fxo_init(व्योम)
अणु
	/*
	 * Setup basic Orion functions. Need to be called early.
	 */
	orion5x_init();

	orion5x_mpp_conf(rd88f5181l_fxo_mpp_modes);

	/*
	 * Configure peripherals.
	 */
	orion5x_ehci0_init();
	orion5x_eth_init(&rd88f5181l_fxo_eth_data);
	orion5x_eth_चयन_init(&rd88f5181l_fxo_चयन_chip_data);
	orion5x_uart0_init();

	mvebu_mbus_add_winकरोw_by_id(ORION_MBUS_DEVBUS_BOOT_TARGET,
				    ORION_MBUS_DEVBUS_BOOT_ATTR,
				    RD88F5181L_FXO_NOR_BOOT_BASE,
				    RD88F5181L_FXO_NOR_BOOT_SIZE);
	platक्रमm_device_रेजिस्टर(&rd88f5181l_fxo_nor_boot_flash);
पूर्ण

अटल पूर्णांक __init
rd88f5181l_fxo_pci_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	पूर्णांक irq;

	/*
	 * Check क्रम devices with hard-wired IRQs.
	 */
	irq = orion5x_pci_map_irq(dev, slot, pin);
	अगर (irq != -1)
		वापस irq;

	/*
	 * Mini-PCI / Cardbus slot.
	 */
	वापस gpio_to_irq(1);
पूर्ण

अटल काष्ठा hw_pci rd88f5181l_fxo_pci __initdata = अणु
	.nr_controllers	= 2,
	.setup		= orion5x_pci_sys_setup,
	.scan		= orion5x_pci_sys_scan_bus,
	.map_irq	= rd88f5181l_fxo_pci_map_irq,
पूर्ण;

अटल पूर्णांक __init rd88f5181l_fxo_pci_init(व्योम)
अणु
	अगर (machine_is_rd88f5181l_fxo()) अणु
		orion5x_pci_set_cardbus_mode();
		pci_common_init(&rd88f5181l_fxo_pci);
	पूर्ण

	वापस 0;
पूर्ण
subsys_initcall(rd88f5181l_fxo_pci_init);

MACHINE_START(RD88F5181L_FXO, "Marvell Orion-VoIP FXO Reference Design")
	/* Maपूर्णांकainer: Nicolas Pitre <nico@marvell.com> */
	.atag_offset	= 0x100,
	.nr_irqs	= ORION5X_NR_IRQS,
	.init_machine	= rd88f5181l_fxo_init,
	.map_io		= orion5x_map_io,
	.init_early	= orion5x_init_early,
	.init_irq	= orion5x_init_irq,
	.init_समय	= orion5x_समयr_init,
	.fixup		= tag_fixup_mem32,
	.restart	= orion5x_restart,
MACHINE_END
