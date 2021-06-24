<शैली गुरु>
/*
 * arch/arm/mach-orion5x/wrt350n-v2-setup.c
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
#समावेश <linux/leds.h>
#समावेश <linux/gpio_keys.h>
#समावेश <linux/input.h>
#समावेश <linux/platक्रमm_data/dsa.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/pci.h>
#समावेश "orion5x.h"
#समावेश "common.h"
#समावेश "mpp.h"

/*
 * LEDs attached to GPIO
 */
अटल काष्ठा gpio_led wrt350n_v2_led_pins[] = अणु
	अणु
		.name		= "wrt350nv2:green:power",
		.gpio		= 0,
		.active_low	= 1,
	पूर्ण, अणु
		.name		= "wrt350nv2:green:security",
		.gpio		= 1,
		.active_low	= 1,
	पूर्ण, अणु
		.name		= "wrt350nv2:orange:power",
		.gpio		= 5,
		.active_low	= 1,
	पूर्ण, अणु
		.name		= "wrt350nv2:green:usb",
		.gpio		= 6,
		.active_low	= 1,
	पूर्ण, अणु
		.name		= "wrt350nv2:green:wireless",
		.gpio		= 7,
		.active_low	= 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_led_platक्रमm_data wrt350n_v2_led_data = अणु
	.leds		= wrt350n_v2_led_pins,
	.num_leds	= ARRAY_SIZE(wrt350n_v2_led_pins),
पूर्ण;

अटल काष्ठा platक्रमm_device wrt350n_v2_leds = अणु
	.name	= "leds-gpio",
	.id	= -1,
	.dev	= अणु
		.platक्रमm_data	= &wrt350n_v2_led_data,
	पूर्ण,
पूर्ण;

/*
 * Buttons attached to GPIO
 */
अटल काष्ठा gpio_keys_button wrt350n_v2_buttons[] = अणु
	अणु
		.code		= KEY_RESTART,
		.gpio		= 3,
		.desc		= "Reset Button",
		.active_low	= 1,
	पूर्ण, अणु
		.code		= KEY_WPS_BUTTON,
		.gpio		= 2,
		.desc		= "WPS Button",
		.active_low	= 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_keys_platक्रमm_data wrt350n_v2_button_data = अणु
	.buttons	= wrt350n_v2_buttons,
	.nbuttons	= ARRAY_SIZE(wrt350n_v2_buttons),
पूर्ण;

अटल काष्ठा platक्रमm_device wrt350n_v2_button_device = अणु
	.name		= "gpio-keys",
	.id		= -1,
	.num_resources	= 0,
	.dev		= अणु
		.platक्रमm_data	= &wrt350n_v2_button_data,
	पूर्ण,
पूर्ण;

/*
 * General setup
 */
अटल अचिन्हित पूर्णांक wrt350n_v2_mpp_modes[] __initdata = अणु
	MPP0_GPIO,		/* Power LED green (0=on) */
	MPP1_GPIO,		/* Security LED (0=on) */
	MPP2_GPIO,		/* Internal Button (0=on) */
	MPP3_GPIO,		/* Reset Button (0=on) */
	MPP4_GPIO,		/* PCI पूर्णांक */
	MPP5_GPIO,		/* Power LED orange (0=on) */
	MPP6_GPIO,		/* USB LED (0=on) */
	MPP7_GPIO,		/* Wireless LED (0=on) */
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
#घोषणा WRT350N_V2_NOR_BOOT_BASE	0xf4000000
#घोषणा WRT350N_V2_NOR_BOOT_SIZE	SZ_8M

अटल काष्ठा mtd_partition wrt350n_v2_nor_flash_partitions[] = अणु
	अणु
		.name		= "kernel",
		.offset		= 0x00000000,
		.size		= 0x00760000,
	पूर्ण, अणु
		.name		= "rootfs",
		.offset		= 0x001a0000,
		.size		= 0x005c0000,
	पूर्ण, अणु
		.name		= "lang",
		.offset		= 0x00760000,
		.size		= 0x00040000,
	पूर्ण, अणु
		.name		= "nvram",
		.offset		= 0x007a0000,
		.size		= 0x00020000,
	पूर्ण, अणु
		.name		= "u-boot",
		.offset		= 0x007c0000,
		.size		= 0x00040000,
	पूर्ण,
पूर्ण;

अटल काष्ठा physmap_flash_data wrt350n_v2_nor_flash_data = अणु
	.width		= 1,
	.parts		= wrt350n_v2_nor_flash_partitions,
	.nr_parts	= ARRAY_SIZE(wrt350n_v2_nor_flash_partitions),
पूर्ण;

अटल काष्ठा resource wrt350n_v2_nor_flash_resource = अणु
	.flags		= IORESOURCE_MEM,
	.start		= WRT350N_V2_NOR_BOOT_BASE,
	.end		= WRT350N_V2_NOR_BOOT_BASE + WRT350N_V2_NOR_BOOT_SIZE - 1,
पूर्ण;

अटल काष्ठा platक्रमm_device wrt350n_v2_nor_flash = अणु
	.name			= "physmap-flash",
	.id			= 0,
	.dev		= अणु
		.platक्रमm_data	= &wrt350n_v2_nor_flash_data,
	पूर्ण,
	.num_resources		= 1,
	.resource		= &wrt350n_v2_nor_flash_resource,
पूर्ण;

अटल काष्ठा mv643xx_eth_platक्रमm_data wrt350n_v2_eth_data = अणु
	.phy_addr	= MV643XX_ETH_PHY_NONE,
	.speed		= SPEED_1000,
	.duplex		= DUPLEX_FULL,
पूर्ण;

अटल काष्ठा dsa_chip_data wrt350n_v2_चयन_chip_data = अणु
	.port_names[0]	= "lan2",
	.port_names[1]	= "lan1",
	.port_names[2]	= "wan",
	.port_names[3]	= "cpu",
	.port_names[5]	= "lan3",
	.port_names[7]	= "lan4",
पूर्ण;

अटल व्योम __init wrt350n_v2_init(व्योम)
अणु
	/*
	 * Setup basic Orion functions. Need to be called early.
	 */
	orion5x_init();

	orion5x_mpp_conf(wrt350n_v2_mpp_modes);

	/*
	 * Configure peripherals.
	 */
	orion5x_ehci0_init();
	orion5x_eth_init(&wrt350n_v2_eth_data);
	orion5x_eth_चयन_init(&wrt350n_v2_चयन_chip_data);
	orion5x_uart0_init();

	mvebu_mbus_add_winकरोw_by_id(ORION_MBUS_DEVBUS_BOOT_TARGET,
				    ORION_MBUS_DEVBUS_BOOT_ATTR,
				    WRT350N_V2_NOR_BOOT_BASE,
				    WRT350N_V2_NOR_BOOT_SIZE);
	platक्रमm_device_रेजिस्टर(&wrt350n_v2_nor_flash);
	platक्रमm_device_रेजिस्टर(&wrt350n_v2_leds);
	platक्रमm_device_रेजिस्टर(&wrt350n_v2_button_device);
पूर्ण

अटल पूर्णांक __init wrt350n_v2_pci_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot,
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

अटल काष्ठा hw_pci wrt350n_v2_pci __initdata = अणु
	.nr_controllers	= 2,
	.setup		= orion5x_pci_sys_setup,
	.scan		= orion5x_pci_sys_scan_bus,
	.map_irq	= wrt350n_v2_pci_map_irq,
पूर्ण;

अटल पूर्णांक __init wrt350n_v2_pci_init(व्योम)
अणु
	अगर (machine_is_wrt350n_v2())
		pci_common_init(&wrt350n_v2_pci);

	वापस 0;
पूर्ण
subsys_initcall(wrt350n_v2_pci_init);

MACHINE_START(WRT350N_V2, "Linksys WRT350N v2")
	/* Maपूर्णांकainer: Lennert Buytenhek <buytenh@marvell.com> */
	.atag_offset	= 0x100,
	.nr_irqs	= ORION5X_NR_IRQS,
	.init_machine	= wrt350n_v2_init,
	.map_io		= orion5x_map_io,
	.init_early	= orion5x_init_early,
	.init_irq	= orion5x_init_irq,
	.init_समय	= orion5x_समयr_init,
	.fixup		= tag_fixup_mem32,
	.restart	= orion5x_restart,
MACHINE_END
