<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * QNAP TS-109/TS-209 Board Setup
 *
 * Maपूर्णांकainer: Byron Bradley <byron.bbradley@gmail.com>
 */
#समावेश <linux/gpपन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pci.h>
#समावेश <linux/irq.h>
#समावेश <linux/mtd/physmap.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/mv643xx_eth.h>
#समावेश <linux/gpio_keys.h>
#समावेश <linux/input.h>
#समावेश <linux/i2c.h>
#समावेश <linux/serial_reg.h>
#समावेश <linux/ata_platक्रमm.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/pci.h>
#समावेश "common.h"
#समावेश "mpp.h"
#समावेश "orion5x.h"
#समावेश "tsx09-common.h"

#घोषणा QNAP_TS209_NOR_BOOT_BASE 0xf4000000
#घोषणा QNAP_TS209_NOR_BOOT_SIZE SZ_8M

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
अटल काष्ठा mtd_partition qnap_ts209_partitions[] = अणु
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

अटल काष्ठा physmap_flash_data qnap_ts209_nor_flash_data = अणु
	.width		= 1,
	.parts		= qnap_ts209_partitions,
	.nr_parts	= ARRAY_SIZE(qnap_ts209_partitions)
पूर्ण;

अटल काष्ठा resource qnap_ts209_nor_flash_resource = अणु
	.flags	= IORESOURCE_MEM,
	.start	= QNAP_TS209_NOR_BOOT_BASE,
	.end	= QNAP_TS209_NOR_BOOT_BASE + QNAP_TS209_NOR_BOOT_SIZE - 1,
पूर्ण;

अटल काष्ठा platक्रमm_device qnap_ts209_nor_flash = अणु
	.name		= "physmap-flash",
	.id		= 0,
	.dev		= अणु
		.platक्रमm_data	= &qnap_ts209_nor_flash_data,
	पूर्ण,
	.resource	= &qnap_ts209_nor_flash_resource,
	.num_resources	= 1,
पूर्ण;

/*****************************************************************************
 * PCI
 ****************************************************************************/

#घोषणा QNAP_TS209_PCI_SLOT0_OFFS	7
#घोषणा QNAP_TS209_PCI_SLOT0_IRQ_PIN	6
#घोषणा QNAP_TS209_PCI_SLOT1_IRQ_PIN	7

अटल व्योम __init qnap_ts209_pci_preinit(व्योम)
अणु
	पूर्णांक pin;

	/*
	 * Configure PCI GPIO IRQ pins
	 */
	pin = QNAP_TS209_PCI_SLOT0_IRQ_PIN;
	अगर (gpio_request(pin, "PCI Int1") == 0) अणु
		अगर (gpio_direction_input(pin) == 0) अणु
			irq_set_irq_type(gpio_to_irq(pin), IRQ_TYPE_LEVEL_LOW);
		पूर्ण अन्यथा अणु
			prपूर्णांकk(KERN_ERR "qnap_ts209_pci_preinit failed to "
					"set_irq_type pin %d\n", pin);
			gpio_मुक्त(pin);
		पूर्ण
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_ERR "qnap_ts209_pci_preinit failed to gpio_request "
				"%d\n", pin);
	पूर्ण

	pin = QNAP_TS209_PCI_SLOT1_IRQ_PIN;
	अगर (gpio_request(pin, "PCI Int2") == 0) अणु
		अगर (gpio_direction_input(pin) == 0) अणु
			irq_set_irq_type(gpio_to_irq(pin), IRQ_TYPE_LEVEL_LOW);
		पूर्ण अन्यथा अणु
			prपूर्णांकk(KERN_ERR "qnap_ts209_pci_preinit failed "
					"to set_irq_type pin %d\n", pin);
			gpio_मुक्त(pin);
		पूर्ण
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_ERR "qnap_ts209_pci_preinit failed to gpio_request "
				"%d\n", pin);
	पूर्ण
पूर्ण

अटल पूर्णांक __init qnap_ts209_pci_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot,
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
	 * PCI IRQs are connected via GPIOs.
	 */
	चयन (slot - QNAP_TS209_PCI_SLOT0_OFFS) अणु
	हाल 0:
		वापस gpio_to_irq(QNAP_TS209_PCI_SLOT0_IRQ_PIN);
	हाल 1:
		वापस gpio_to_irq(QNAP_TS209_PCI_SLOT1_IRQ_PIN);
	शेष:
		वापस -1;
	पूर्ण
पूर्ण

अटल काष्ठा hw_pci qnap_ts209_pci __initdata = अणु
	.nr_controllers	= 2,
	.preinit	= qnap_ts209_pci_preinit,
	.setup		= orion5x_pci_sys_setup,
	.scan		= orion5x_pci_sys_scan_bus,
	.map_irq	= qnap_ts209_pci_map_irq,
पूर्ण;

अटल पूर्णांक __init qnap_ts209_pci_init(व्योम)
अणु
	अगर (machine_is_ts209())
		pci_common_init(&qnap_ts209_pci);

	वापस 0;
पूर्ण

subsys_initcall(qnap_ts209_pci_init);

/*****************************************************************************
 * RTC S35390A on I2C bus
 ****************************************************************************/

#घोषणा TS209_RTC_GPIO	3

अटल काष्ठा i2c_board_info __initdata qnap_ts209_i2c_rtc = अणु
	I2C_BOARD_INFO("s35390a", 0x30),
	.irq	= 0,
पूर्ण;

/****************************************************************************
 * GPIO Attached Keys
 *     Power button is attached to the PIC microcontroller
 ****************************************************************************/

#घोषणा QNAP_TS209_GPIO_KEY_MEDIA	1
#घोषणा QNAP_TS209_GPIO_KEY_RESET	2

अटल काष्ठा gpio_keys_button qnap_ts209_buttons[] = अणु
	अणु
		.code		= KEY_COPY,
		.gpio		= QNAP_TS209_GPIO_KEY_MEDIA,
		.desc		= "USB Copy Button",
		.active_low	= 1,
	पूर्ण, अणु
		.code		= KEY_RESTART,
		.gpio		= QNAP_TS209_GPIO_KEY_RESET,
		.desc		= "Reset Button",
		.active_low	= 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_keys_platक्रमm_data qnap_ts209_button_data = अणु
	.buttons	= qnap_ts209_buttons,
	.nbuttons	= ARRAY_SIZE(qnap_ts209_buttons),
पूर्ण;

अटल काष्ठा platक्रमm_device qnap_ts209_button_device = अणु
	.name		= "gpio-keys",
	.id		= -1,
	.num_resources	= 0,
	.dev		= अणु
		.platक्रमm_data	= &qnap_ts209_button_data,
	पूर्ण,
पूर्ण;

/*****************************************************************************
 * SATA
 ****************************************************************************/
अटल काष्ठा mv_sata_platक्रमm_data qnap_ts209_sata_data = अणु
	.n_ports	= 2,
पूर्ण;

/*****************************************************************************

 * General Setup
 ****************************************************************************/
अटल अचिन्हित पूर्णांक ts209_mpp_modes[] __initdata = अणु
	MPP0_UNUSED,
	MPP1_GPIO,		/* USB copy button */
	MPP2_GPIO,		/* Load शेषs button */
	MPP3_GPIO,		/* GPIO RTC */
	MPP4_UNUSED,
	MPP5_UNUSED,
	MPP6_GPIO,		/* PCI Int A */
	MPP7_GPIO,		/* PCI Int B */
	MPP8_UNUSED,
	MPP9_UNUSED,
	MPP10_UNUSED,
	MPP11_UNUSED,
	MPP12_SATA_LED,		/* SATA 0 presence */
	MPP13_SATA_LED,		/* SATA 1 presence */
	MPP14_SATA_LED,		/* SATA 0 active */
	MPP15_SATA_LED,		/* SATA 1 active */
	MPP16_UART,		/* UART1 RXD */
	MPP17_UART,		/* UART1 TXD */
	MPP18_GPIO,		/* SW_RST */
	MPP19_UNUSED,
	0,
पूर्ण;

अटल व्योम __init qnap_ts209_init(व्योम)
अणु
	/*
	 * Setup basic Orion functions. Need to be called early.
	 */
	orion5x_init();

	orion5x_mpp_conf(ts209_mpp_modes);

	/*
	 * MPP[20] PCI घड़ी 0
	 * MPP[21] PCI घड़ी 1
	 * MPP[22] USB 0 over current
	 * MPP[23-25] Reserved
	 */

	/*
	 * Configure peripherals.
	 */
	mvebu_mbus_add_winकरोw_by_id(ORION_MBUS_DEVBUS_BOOT_TARGET,
				    ORION_MBUS_DEVBUS_BOOT_ATTR,
				    QNAP_TS209_NOR_BOOT_BASE,
				    QNAP_TS209_NOR_BOOT_SIZE);
	platक्रमm_device_रेजिस्टर(&qnap_ts209_nor_flash);

	orion5x_ehci0_init();
	orion5x_ehci1_init();
	qnap_tsx09_find_mac_addr(QNAP_TS209_NOR_BOOT_BASE +
				 qnap_ts209_partitions[5].offset,
				 qnap_ts209_partitions[5].size);
	orion5x_eth_init(&qnap_tsx09_eth_data);
	orion5x_i2c_init();
	orion5x_sata_init(&qnap_ts209_sata_data);
	orion5x_uart0_init();
	orion5x_uart1_init();
	orion5x_xor_init();

	platक्रमm_device_रेजिस्टर(&qnap_ts209_button_device);

	/* Get RTC IRQ and रेजिस्टर the chip */
	अगर (gpio_request(TS209_RTC_GPIO, "rtc") == 0) अणु
		अगर (gpio_direction_input(TS209_RTC_GPIO) == 0)
			qnap_ts209_i2c_rtc.irq = gpio_to_irq(TS209_RTC_GPIO);
		अन्यथा
			gpio_मुक्त(TS209_RTC_GPIO);
	पूर्ण
	अगर (qnap_ts209_i2c_rtc.irq == 0)
		pr_warn("qnap_ts209_init: failed to get RTC IRQ\n");
	i2c_रेजिस्टर_board_info(0, &qnap_ts209_i2c_rtc, 1);

	/* रेजिस्टर tsx09 specअगरic घातer-off method */
	pm_घातer_off = qnap_tsx09_घातer_off;
पूर्ण

MACHINE_START(TS209, "QNAP TS-109/TS-209")
	/* Maपूर्णांकainer: Byron Bradley <byron.bbradley@gmail.com> */
	.atag_offset	= 0x100,
	.nr_irqs	= ORION5X_NR_IRQS,
	.init_machine	= qnap_ts209_init,
	.map_io		= orion5x_map_io,
	.init_early	= orion5x_init_early,
	.init_irq	= orion5x_init_irq,
	.init_समय	= orion5x_समयr_init,
	.fixup		= tag_fixup_mem32,
	.restart	= orion5x_restart,
MACHINE_END
