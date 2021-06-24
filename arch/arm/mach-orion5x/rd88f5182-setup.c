<शैली गुरु>
/*
 * arch/arm/mach-orion5x/rd88f5182-setup.c
 *
 * Marvell Orion-NAS Reference Design Setup
 *
 * Maपूर्णांकainer: Ronen Shitrit <rshitrit@marvell.com>
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
#समावेश <linux/ata_platक्रमm.h>
#समावेश <linux/i2c.h>
#समावेश <linux/leds.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/pci.h>
#समावेश "common.h"
#समावेश "mpp.h"
#समावेश "orion5x.h"

/*****************************************************************************
 * RD-88F5182 Info
 ****************************************************************************/

/*
 * 512K NOR flash Device bus boot chip select
 */

#घोषणा RD88F5182_NOR_BOOT_BASE		0xf4000000
#घोषणा RD88F5182_NOR_BOOT_SIZE		SZ_512K

/*
 * 16M NOR flash on Device bus chip select 1
 */

#घोषणा RD88F5182_NOR_BASE		0xfc000000
#घोषणा RD88F5182_NOR_SIZE		SZ_16M

/*
 * PCI
 */

#घोषणा RD88F5182_PCI_SLOT0_OFFS	7
#घोषणा RD88F5182_PCI_SLOT0_IRQ_A_PIN	7
#घोषणा RD88F5182_PCI_SLOT0_IRQ_B_PIN	6

/*****************************************************************************
 * 16M NOR Flash on Device bus CS1
 ****************************************************************************/

अटल काष्ठा physmap_flash_data rd88f5182_nor_flash_data = अणु
	.width		= 1,
पूर्ण;

अटल काष्ठा resource rd88f5182_nor_flash_resource = अणु
	.flags			= IORESOURCE_MEM,
	.start			= RD88F5182_NOR_BASE,
	.end			= RD88F5182_NOR_BASE + RD88F5182_NOR_SIZE - 1,
पूर्ण;

अटल काष्ठा platक्रमm_device rd88f5182_nor_flash = अणु
	.name			= "physmap-flash",
	.id			= 0,
	.dev		= अणु
		.platक्रमm_data	= &rd88f5182_nor_flash_data,
	पूर्ण,
	.num_resources		= 1,
	.resource		= &rd88f5182_nor_flash_resource,
पूर्ण;

/*****************************************************************************
 * Use GPIO LED as CPU active indication
 ****************************************************************************/

#घोषणा RD88F5182_GPIO_LED		0

अटल काष्ठा gpio_led rd88f5182_gpio_led_pins[] = अणु
	अणु
		.name		= "rd88f5182:cpu",
		.शेष_trigger = "cpu0",
		.gpio		= RD88F5182_GPIO_LED,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_led_platक्रमm_data rd88f5182_gpio_led_data = अणु
	.leds		= rd88f5182_gpio_led_pins,
	.num_leds	= ARRAY_SIZE(rd88f5182_gpio_led_pins),
पूर्ण;

अटल काष्ठा platक्रमm_device rd88f5182_gpio_leds = अणु
	.name	= "leds-gpio",
	.id	= -1,
	.dev	= अणु
		.platक्रमm_data = &rd88f5182_gpio_led_data,
	पूर्ण,
पूर्ण;

/*****************************************************************************
 * PCI
 ****************************************************************************/

अटल व्योम __init rd88f5182_pci_preinit(व्योम)
अणु
	पूर्णांक pin;

	/*
	 * Configure PCI GPIO IRQ pins
	 */
	pin = RD88F5182_PCI_SLOT0_IRQ_A_PIN;
	अगर (gpio_request(pin, "PCI IntA") == 0) अणु
		अगर (gpio_direction_input(pin) == 0) अणु
			irq_set_irq_type(gpio_to_irq(pin), IRQ_TYPE_LEVEL_LOW);
		पूर्ण अन्यथा अणु
			prपूर्णांकk(KERN_ERR "rd88f5182_pci_preinit failed to "
					"set_irq_type pin %d\n", pin);
			gpio_मुक्त(pin);
		पूर्ण
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_ERR "rd88f5182_pci_preinit failed to request gpio %d\n", pin);
	पूर्ण

	pin = RD88F5182_PCI_SLOT0_IRQ_B_PIN;
	अगर (gpio_request(pin, "PCI IntB") == 0) अणु
		अगर (gpio_direction_input(pin) == 0) अणु
			irq_set_irq_type(gpio_to_irq(pin), IRQ_TYPE_LEVEL_LOW);
		पूर्ण अन्यथा अणु
			prपूर्णांकk(KERN_ERR "rd88f5182_pci_preinit failed to "
					"set_irq_type pin %d\n", pin);
			gpio_मुक्त(pin);
		पूर्ण
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_ERR "rd88f5182_pci_preinit failed to gpio_request %d\n", pin);
	पूर्ण
पूर्ण

अटल पूर्णांक __init rd88f5182_pci_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot,
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
	 * PCI IRQs are connected via GPIOs
	 */
	चयन (slot - RD88F5182_PCI_SLOT0_OFFS) अणु
	हाल 0:
		अगर (pin == 1)
			वापस gpio_to_irq(RD88F5182_PCI_SLOT0_IRQ_A_PIN);
		अन्यथा
			वापस gpio_to_irq(RD88F5182_PCI_SLOT0_IRQ_B_PIN);
	शेष:
		वापस -1;
	पूर्ण
पूर्ण

अटल काष्ठा hw_pci rd88f5182_pci __initdata = अणु
	.nr_controllers	= 2,
	.preinit	= rd88f5182_pci_preinit,
	.setup		= orion5x_pci_sys_setup,
	.scan		= orion5x_pci_sys_scan_bus,
	.map_irq	= rd88f5182_pci_map_irq,
पूर्ण;

अटल पूर्णांक __init rd88f5182_pci_init(व्योम)
अणु
	अगर (machine_is_rd88f5182())
		pci_common_init(&rd88f5182_pci);

	वापस 0;
पूर्ण

subsys_initcall(rd88f5182_pci_init);

/*****************************************************************************
 * Ethernet
 ****************************************************************************/

अटल काष्ठा mv643xx_eth_platक्रमm_data rd88f5182_eth_data = अणु
	.phy_addr	= MV643XX_ETH_PHY_ADDR(8),
पूर्ण;

/*****************************************************************************
 * RTC DS1338 on I2C bus
 ****************************************************************************/
अटल काष्ठा i2c_board_info __initdata rd88f5182_i2c_rtc = अणु
	I2C_BOARD_INFO("ds1338", 0x68),
पूर्ण;

/*****************************************************************************
 * Sata
 ****************************************************************************/
अटल काष्ठा mv_sata_platक्रमm_data rd88f5182_sata_data = अणु
	.n_ports	= 2,
पूर्ण;

/*****************************************************************************
 * General Setup
 ****************************************************************************/
अटल अचिन्हित पूर्णांक rd88f5182_mpp_modes[] __initdata = अणु
	MPP0_GPIO,		/* Debug Led */
	MPP1_GPIO,		/* Reset Switch */
	MPP2_UNUSED,
	MPP3_GPIO,		/* RTC Int */
	MPP4_GPIO,
	MPP5_GPIO,
	MPP6_GPIO,		/* PCI_पूर्णांकA */
	MPP7_GPIO,		/* PCI_पूर्णांकB */
	MPP8_UNUSED,
	MPP9_UNUSED,
	MPP10_UNUSED,
	MPP11_UNUSED,
	MPP12_SATA_LED,		/* SATA 0 presence */
	MPP13_SATA_LED,		/* SATA 1 presence */
	MPP14_SATA_LED,		/* SATA 0 active */
	MPP15_SATA_LED,		/* SATA 1 active */
	MPP16_UNUSED,
	MPP17_UNUSED,
	MPP18_UNUSED,
	MPP19_UNUSED,
	0,
पूर्ण;

अटल व्योम __init rd88f5182_init(व्योम)
अणु
	/*
	 * Setup basic Orion functions. Need to be called early.
	 */
	orion5x_init();

	orion5x_mpp_conf(rd88f5182_mpp_modes);

	/*
	 * MPP[20] PCI Clock to MV88F5182
	 * MPP[21] PCI Clock to mini PCI CON11
	 * MPP[22] USB 0 over current indication
	 * MPP[23] USB 1 over current indication
	 * MPP[24] USB 1 over current enable
	 * MPP[25] USB 0 over current enable
	 */

	/*
	 * Configure peripherals.
	 */
	orion5x_ehci0_init();
	orion5x_ehci1_init();
	orion5x_eth_init(&rd88f5182_eth_data);
	orion5x_i2c_init();
	orion5x_sata_init(&rd88f5182_sata_data);
	orion5x_uart0_init();
	orion5x_xor_init();

	mvebu_mbus_add_winकरोw_by_id(ORION_MBUS_DEVBUS_BOOT_TARGET,
				    ORION_MBUS_DEVBUS_BOOT_ATTR,
				    RD88F5182_NOR_BOOT_BASE,
				    RD88F5182_NOR_BOOT_SIZE);
	mvebu_mbus_add_winकरोw_by_id(ORION_MBUS_DEVBUS_TARGET(1),
				    ORION_MBUS_DEVBUS_ATTR(1),
				    RD88F5182_NOR_BASE,
				    RD88F5182_NOR_SIZE);
	platक्रमm_device_रेजिस्टर(&rd88f5182_nor_flash);
	platक्रमm_device_रेजिस्टर(&rd88f5182_gpio_leds);

	i2c_रेजिस्टर_board_info(0, &rd88f5182_i2c_rtc, 1);
पूर्ण

MACHINE_START(RD88F5182, "Marvell Orion-NAS Reference Design")
	/* Maपूर्णांकainer: Ronen Shitrit <rshitrit@marvell.com> */
	.atag_offset	= 0x100,
	.nr_irqs	= ORION5X_NR_IRQS,
	.init_machine	= rd88f5182_init,
	.map_io		= orion5x_map_io,
	.init_early	= orion5x_init_early,
	.init_irq	= orion5x_init_irq,
	.init_समय	= orion5x_समयr_init,
	.restart	= orion5x_restart,
MACHINE_END
