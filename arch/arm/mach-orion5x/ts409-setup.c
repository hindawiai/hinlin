<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * QNAP TS-409 Board Setup
 *
 * Maपूर्णांकainer: Sylver Bruneau <sylver.bruneau@gmail.com>
 *
 * Copyright (C) 2008  Sylver Bruneau <sylver.bruneau@gmail.com>
 * Copyright (C) 2008  Martin Michlmayr <tbm@cyrius.com>
 */
#समावेश <linux/gpपन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pci.h>
#समावेश <linux/irq.h>
#समावेश <linux/mtd/physmap.h>
#समावेश <linux/mv643xx_eth.h>
#समावेश <linux/leds.h>
#समावेश <linux/gpio_keys.h>
#समावेश <linux/input.h>
#समावेश <linux/i2c.h>
#समावेश <linux/serial_reg.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/pci.h>
#समावेश "common.h"
#समावेश "mpp.h"
#समावेश "orion5x.h"
#समावेश "tsx09-common.h"

/*****************************************************************************
 * QNAP TS-409 Info
 ****************************************************************************/

/*
 * QNAP TS-409 hardware :
 * - Marvell 88F5281-D0
 * - Marvell 88SX7042 SATA controller (PCIe)
 * - Marvell 88E1118 Gigabit Ethernet PHY
 * - RTC S35390A (@0x30) on I2C bus
 * - 8MB NOR flash
 * - 256MB of DDR-2 RAM
 */

/*
 * 8MB NOR flash Device bus boot chip select
 */

#घोषणा QNAP_TS409_NOR_BOOT_BASE 0xff800000
#घोषणा QNAP_TS409_NOR_BOOT_SIZE SZ_8M

/****************************************************************************
 * 8MiB NOR flash. The काष्ठा mtd_partition is not in the same order as the
 *     partitions on the device because we want to keep compatibility with
 *     existing QNAP firmware.
 *
 * Layout as used by QNAP:
 *  [2] 0x00000000-0x00200000 : "Kernel"
 *  [3] 0x00200000-0x00600000 : "RootFS1"
 *  [4] 0x00600000-0x00700000 : "RootFS2"
 *  [6] 0x00700000-0x00760000 : "NAS Config" (पढ़ो-only)
 *  [5] 0x00760000-0x00780000 : "U-Boot Config"
 *  [1] 0x00780000-0x00800000 : "U-Boot" (पढ़ो-only)
 ***************************************************************************/
अटल काष्ठा mtd_partition qnap_ts409_partitions[] = अणु
	अणु
		.name		= "U-Boot",
		.size		= 0x00080000,
		.offset		= 0x00780000,
		.mask_flags	= MTD_WRITEABLE,
	पूर्ण, अणु
		.name		= "Kernel",
		.size		= 0x00200000,
		.offset		= 0,
	पूर्ण, अणु
		.name		= "RootFS1",
		.size		= 0x00400000,
		.offset		= 0x00200000,
	पूर्ण, अणु
		.name		= "RootFS2",
		.size		= 0x00100000,
		.offset		= 0x00600000,
	पूर्ण, अणु
		.name		= "U-Boot Config",
		.size		= 0x00020000,
		.offset		= 0x00760000,
	पूर्ण, अणु
		.name		= "NAS Config",
		.size		= 0x00060000,
		.offset		= 0x00700000,
		.mask_flags	= MTD_WRITEABLE,
	पूर्ण,
पूर्ण;

अटल काष्ठा physmap_flash_data qnap_ts409_nor_flash_data = अणु
	.width		= 1,
	.parts		= qnap_ts409_partitions,
	.nr_parts	= ARRAY_SIZE(qnap_ts409_partitions)
पूर्ण;

अटल काष्ठा resource qnap_ts409_nor_flash_resource = अणु
	.flags	= IORESOURCE_MEM,
	.start	= QNAP_TS409_NOR_BOOT_BASE,
	.end	= QNAP_TS409_NOR_BOOT_BASE + QNAP_TS409_NOR_BOOT_SIZE - 1,
पूर्ण;

अटल काष्ठा platक्रमm_device qnap_ts409_nor_flash = अणु
	.name		= "physmap-flash",
	.id		= 0,
	.dev		= अणु .platक्रमm_data = &qnap_ts409_nor_flash_data, पूर्ण,
	.num_resources	= 1,
	.resource	= &qnap_ts409_nor_flash_resource,
पूर्ण;

/*****************************************************************************
 * PCI
 ****************************************************************************/

अटल पूर्णांक __init qnap_ts409_pci_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot,
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
	 * PCI isn't used on the TS-409
	 */
	वापस -1;
पूर्ण

अटल काष्ठा hw_pci qnap_ts409_pci __initdata = अणु
	.nr_controllers	= 2,
	.setup		= orion5x_pci_sys_setup,
	.scan		= orion5x_pci_sys_scan_bus,
	.map_irq	= qnap_ts409_pci_map_irq,
पूर्ण;

अटल पूर्णांक __init qnap_ts409_pci_init(व्योम)
अणु
	अगर (machine_is_ts409())
		pci_common_init(&qnap_ts409_pci);

	वापस 0;
पूर्ण

subsys_initcall(qnap_ts409_pci_init);

/*****************************************************************************
 * RTC S35390A on I2C bus
 ****************************************************************************/

#घोषणा TS409_RTC_GPIO	10

अटल काष्ठा i2c_board_info __initdata qnap_ts409_i2c_rtc = अणु
	I2C_BOARD_INFO("s35390a", 0x30),
पूर्ण;

/*****************************************************************************
 * LEDs attached to GPIO
 ****************************************************************************/

अटल काष्ठा gpio_led ts409_led_pins[] = अणु
	अणु
		.name		= "ts409:red:sata1",
		.gpio		= 4,
		.active_low	= 1,
	पूर्ण, अणु
		.name		= "ts409:red:sata2",
		.gpio		= 5,
		.active_low	= 1,
	पूर्ण, अणु
		.name		= "ts409:red:sata3",
		.gpio		= 6,
		.active_low	= 1,
	पूर्ण, अणु
		.name		= "ts409:red:sata4",
		.gpio		= 7,
		.active_low	= 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_led_platक्रमm_data ts409_led_data = अणु
	.leds		= ts409_led_pins,
	.num_leds	= ARRAY_SIZE(ts409_led_pins),
पूर्ण;

अटल काष्ठा platक्रमm_device ts409_leds = अणु
	.name	= "leds-gpio",
	.id	= -1,
	.dev	= अणु
		.platक्रमm_data	= &ts409_led_data,
	पूर्ण,
पूर्ण;

/****************************************************************************
 * GPIO Attached Keys
 *     Power button is attached to the PIC microcontroller
 ****************************************************************************/

#घोषणा QNAP_TS409_GPIO_KEY_RESET	14
#घोषणा QNAP_TS409_GPIO_KEY_MEDIA	15

अटल काष्ठा gpio_keys_button qnap_ts409_buttons[] = अणु
	अणु
		.code		= KEY_RESTART,
		.gpio		= QNAP_TS409_GPIO_KEY_RESET,
		.desc		= "Reset Button",
		.active_low	= 1,
	पूर्ण, अणु
		.code		= KEY_COPY,
		.gpio		= QNAP_TS409_GPIO_KEY_MEDIA,
		.desc		= "USB Copy Button",
		.active_low	= 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_keys_platक्रमm_data qnap_ts409_button_data = अणु
	.buttons	= qnap_ts409_buttons,
	.nbuttons	= ARRAY_SIZE(qnap_ts409_buttons),
पूर्ण;

अटल काष्ठा platक्रमm_device qnap_ts409_button_device = अणु
	.name		= "gpio-keys",
	.id		= -1,
	.num_resources	= 0,
	.dev		= अणु
		.platक्रमm_data	= &qnap_ts409_button_data,
	पूर्ण,
पूर्ण;

/*****************************************************************************
 * General Setup
 ****************************************************************************/
अटल अचिन्हित पूर्णांक ts409_mpp_modes[] __initdata = अणु
	MPP0_UNUSED,
	MPP1_UNUSED,
	MPP2_UNUSED,
	MPP3_UNUSED,
	MPP4_GPIO,		/* HDD 1 status */
	MPP5_GPIO,		/* HDD 2 status */
	MPP6_GPIO,		/* HDD 3 status */
	MPP7_GPIO,		/* HDD 4 status */
	MPP8_UNUSED,
	MPP9_UNUSED,
	MPP10_GPIO,		/* RTC पूर्णांक */
	MPP11_UNUSED,
	MPP12_UNUSED,
	MPP13_UNUSED,
	MPP14_GPIO,		/* SW_RST */
	MPP15_GPIO,		/* USB copy button */
	MPP16_UART,		/* UART1 RXD */
	MPP17_UART,		/* UART1 TXD */
	MPP18_UNUSED,
	MPP19_UNUSED,
	0,
पूर्ण;

अटल व्योम __init qnap_ts409_init(व्योम)
अणु
	/*
	 * Setup basic Orion functions. Need to be called early.
	 */
	orion5x_init();

	orion5x_mpp_conf(ts409_mpp_modes);

	/*
	 * Configure peripherals.
	 */
	mvebu_mbus_add_winकरोw_by_id(ORION_MBUS_DEVBUS_BOOT_TARGET,
				    ORION_MBUS_DEVBUS_BOOT_ATTR,
				    QNAP_TS409_NOR_BOOT_BASE,
				    QNAP_TS409_NOR_BOOT_SIZE);
	platक्रमm_device_रेजिस्टर(&qnap_ts409_nor_flash);

	orion5x_ehci0_init();
	qnap_tsx09_find_mac_addr(QNAP_TS409_NOR_BOOT_BASE +
				 qnap_ts409_partitions[5].offset,
				 qnap_ts409_partitions[5].size);
	orion5x_eth_init(&qnap_tsx09_eth_data);
	orion5x_i2c_init();
	orion5x_uart0_init();
	orion5x_uart1_init();

	platक्रमm_device_रेजिस्टर(&qnap_ts409_button_device);

	/* Get RTC IRQ and रेजिस्टर the chip */
	अगर (gpio_request(TS409_RTC_GPIO, "rtc") == 0) अणु
		अगर (gpio_direction_input(TS409_RTC_GPIO) == 0)
			qnap_ts409_i2c_rtc.irq = gpio_to_irq(TS409_RTC_GPIO);
		अन्यथा
			gpio_मुक्त(TS409_RTC_GPIO);
	पूर्ण
	अगर (qnap_ts409_i2c_rtc.irq == 0)
		pr_warn("qnap_ts409_init: failed to get RTC IRQ\n");
	i2c_रेजिस्टर_board_info(0, &qnap_ts409_i2c_rtc, 1);
	platक्रमm_device_रेजिस्टर(&ts409_leds);

	/* रेजिस्टर tsx09 specअगरic घातer-off method */
	pm_घातer_off = qnap_tsx09_घातer_off;
पूर्ण

MACHINE_START(TS409, "QNAP TS-409")
	/* Maपूर्णांकainer:  Sylver Bruneau <sylver.bruneau@gmail.com> */
	.atag_offset	= 0x100,
	.nr_irqs	= ORION5X_NR_IRQS,
	.init_machine	= qnap_ts409_init,
	.map_io		= orion5x_map_io,
	.init_early	= orion5x_init_early,
	.init_irq	= orion5x_init_irq,
	.init_समय	= orion5x_समयr_init,
	.fixup		= tag_fixup_mem32,
	.restart	= orion5x_restart,
MACHINE_END
