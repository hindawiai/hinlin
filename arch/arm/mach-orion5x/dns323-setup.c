<शैली गुरु>
/*
 * arch/arm/mach-orion5x/dns323-setup.c
 *
 * Copyright (C) 2007 Herbert Valerio Riedel <hvr@gnu.org>
 *
 * Support क्रम HW Rev C1:
 *
 * Copyright (C) 2010 Benjamin Herrenschmidt <benh@kernel.crashing.org>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 */
#समावेश <linux/gpपन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pci.h>
#समावेश <linux/irq.h>
#समावेश <linux/mtd/physmap.h>
#समावेश <linux/mv643xx_eth.h>
#समावेश <linux/leds.h>
#समावेश <linux/gpio_keys.h>
#समावेश <linux/input.h>
#समावेश <linux/i2c.h>
#समावेश <linux/ata_platक्रमm.h>
#समावेश <linux/phy.h>
#समावेश <linux/marvell_phy.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/pci.h>
#समावेश <यंत्र/प्रणाली_info.h>
#समावेश <plat/orion-gpपन.स>
#समावेश "orion5x.h"
#समावेश "common.h"
#समावेश "mpp.h"

/* Rev A1 and B1 */
#घोषणा DNS323_GPIO_LED_RIGHT_AMBER	1
#घोषणा DNS323_GPIO_LED_LEFT_AMBER	2
#घोषणा DNS323_GPIO_SYSTEM_UP		3
#घोषणा DNS323_GPIO_LED_POWER1		4
#घोषणा DNS323_GPIO_LED_POWER2		5
#घोषणा DNS323_GPIO_OVERTEMP		6
#घोषणा DNS323_GPIO_RTC			7
#घोषणा DNS323_GPIO_POWER_OFF		8
#घोषणा DNS323_GPIO_KEY_POWER		9
#घोषणा DNS323_GPIO_KEY_RESET		10

/* Rev C1 */
#घोषणा DNS323C_GPIO_KEY_POWER		1
#घोषणा DNS323C_GPIO_POWER_OFF		2
#घोषणा DNS323C_GPIO_LED_RIGHT_AMBER	8
#घोषणा DNS323C_GPIO_LED_LEFT_AMBER	9
#घोषणा DNS323C_GPIO_LED_POWER		17
#घोषणा DNS323C_GPIO_FAN_BIT1		18
#घोषणा DNS323C_GPIO_FAN_BIT0		19

/* Exposed to userspace, करो not change */
क्रमागत अणु
	DNS323_REV_A1,	/* 0 */
	DNS323_REV_B1,	/* 1 */
	DNS323_REV_C1,	/* 2 */
पूर्ण;


/****************************************************************************
 * PCI setup
 */

अटल पूर्णांक __init dns323_pci_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	पूर्णांक irq;

	/*
	 * Check क्रम devices with hard-wired IRQs.
	 */
	irq = orion5x_pci_map_irq(dev, slot, pin);
	अगर (irq != -1)
		वापस irq;

	वापस -1;
पूर्ण

अटल काष्ठा hw_pci dns323_pci __initdata = अणु
	.nr_controllers = 2,
	.setup		= orion5x_pci_sys_setup,
	.scan		= orion5x_pci_sys_scan_bus,
	.map_irq	= dns323_pci_map_irq,
पूर्ण;

अटल पूर्णांक __init dns323_pci_init(व्योम)
अणु
	/* Rev B1 and C1 करोesn't really use its PCI bus, and initialising PCI
	 * माला_लो in the way of initialising the SATA controller.
	 */
	अगर (machine_is_dns323() && प्रणाली_rev == DNS323_REV_A1)
		pci_common_init(&dns323_pci);

	वापस 0;
पूर्ण

subsys_initcall(dns323_pci_init);

/****************************************************************************
 * 8MiB NOR flash (Spansion S29GL064M90TFIR4)
 *
 * Layout as used by D-Link:
 *  0x00000000-0x00010000 : "MTD1"
 *  0x00010000-0x00020000 : "MTD2"
 *  0x00020000-0x001a0000 : "Linux Kernel"
 *  0x001a0000-0x007d0000 : "File System"
 *  0x007d0000-0x00800000 : "u-boot"
 */

#घोषणा DNS323_NOR_BOOT_BASE 0xf4000000
#घोषणा DNS323_NOR_BOOT_SIZE SZ_8M

अटल काष्ठा mtd_partition dns323_partitions[] = अणु
	अणु
		.name	= "MTD1",
		.size	= 0x00010000,
		.offset	= 0,
	पूर्ण, अणु
		.name	= "MTD2",
		.size	= 0x00010000,
		.offset = 0x00010000,
	पूर्ण, अणु
		.name	= "Linux Kernel",
		.size	= 0x00180000,
		.offset	= 0x00020000,
	पूर्ण, अणु
		.name	= "File System",
		.size	= 0x00630000,
		.offset	= 0x001A0000,
	पूर्ण, अणु
		.name	= "u-boot",
		.size	= 0x00030000,
		.offset	= 0x007d0000,
	पूर्ण,
पूर्ण;

अटल काष्ठा physmap_flash_data dns323_nor_flash_data = अणु
	.width		= 1,
	.parts		= dns323_partitions,
	.nr_parts	= ARRAY_SIZE(dns323_partitions)
पूर्ण;

अटल काष्ठा resource dns323_nor_flash_resource = अणु
	.flags		= IORESOURCE_MEM,
	.start		= DNS323_NOR_BOOT_BASE,
	.end		= DNS323_NOR_BOOT_BASE + DNS323_NOR_BOOT_SIZE - 1,
पूर्ण;

अटल काष्ठा platक्रमm_device dns323_nor_flash = अणु
	.name		= "physmap-flash",
	.id		= 0,
	.dev		= अणु
		.platक्रमm_data	= &dns323_nor_flash_data,
	पूर्ण,
	.resource	= &dns323_nor_flash_resource,
	.num_resources	= 1,
पूर्ण;

/****************************************************************************
 * Ethernet
 */

अटल काष्ठा mv643xx_eth_platक्रमm_data dns323_eth_data = अणु
	.phy_addr = MV643XX_ETH_PHY_ADDR(8),
पूर्ण;

/* dns323_parse_hex_*() taken from tsx09-common.c; should a common copy of these
 * functions be kept somewhere?
 */
अटल पूर्णांक __init dns323_parse_hex_nibble(अक्षर n)
अणु
	अगर (n >= '0' && n <= '9')
		वापस n - '0';

	अगर (n >= 'A' && n <= 'F')
		वापस n - 'A' + 10;

	अगर (n >= 'a' && n <= 'f')
		वापस n - 'a' + 10;

	वापस -1;
पूर्ण

अटल पूर्णांक __init dns323_parse_hex_byte(स्थिर अक्षर *b)
अणु
	पूर्णांक hi;
	पूर्णांक lo;

	hi = dns323_parse_hex_nibble(b[0]);
	lo = dns323_parse_hex_nibble(b[1]);

	अगर (hi < 0 || lo < 0)
		वापस -1;

	वापस (hi << 4) | lo;
पूर्ण

अटल पूर्णांक __init dns323_पढ़ो_mac_addr(व्योम)
अणु
	u_पूर्णांक8_t addr[6];
	पूर्णांक i;
	अक्षर *mac_page;

	/* MAC address is stored as a regular ol' string in /dev/mtdblock4
	 * (0x007d0000-0x00800000) starting at offset 196480 (0x2ff80).
	 */
	mac_page = ioremap(DNS323_NOR_BOOT_BASE + 0x7d0000 + 196480, 1024);
	अगर (!mac_page)
		वापस -ENOMEM;

	/* Sanity check the string we're looking at */
	क्रम (i = 0; i < 5; i++) अणु
		अगर (*(mac_page + (i * 3) + 2) != ':') अणु
			जाओ error_fail;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < 6; i++)	अणु
		पूर्णांक byte;

		byte = dns323_parse_hex_byte(mac_page + (i * 3));
		अगर (byte < 0) अणु
			जाओ error_fail;
		पूर्ण

		addr[i] = byte;
	पूर्ण

	iounmap(mac_page);
	prपूर्णांकk("DNS-323: Found ethernet MAC address: %pM\n", addr);

	स_नकल(dns323_eth_data.mac_addr, addr, 6);

	वापस 0;

error_fail:
	iounmap(mac_page);
	वापस -EINVAL;
पूर्ण

/****************************************************************************
 * GPIO LEDs (simple - करोesn't use hardware blinking support)
 */

अटल काष्ठा gpio_led dns323ab_leds[] = अणु
	अणु
		.name = "power:blue",
		.gpio = DNS323_GPIO_LED_POWER2,
		.शेष_trigger = "default-on",
	पूर्ण, अणु
		.name = "right:amber",
		.gpio = DNS323_GPIO_LED_RIGHT_AMBER,
		.active_low = 1,
	पूर्ण, अणु
		.name = "left:amber",
		.gpio = DNS323_GPIO_LED_LEFT_AMBER,
		.active_low = 1,
	पूर्ण,
पूर्ण;


अटल काष्ठा gpio_led dns323c_leds[] = अणु
	अणु
		.name = "power:blue",
		.gpio = DNS323C_GPIO_LED_POWER,
		.शेष_trigger = "timer",
		.active_low = 1,
	पूर्ण, अणु
		.name = "right:amber",
		.gpio = DNS323C_GPIO_LED_RIGHT_AMBER,
		.active_low = 1,
	पूर्ण, अणु
		.name = "left:amber",
		.gpio = DNS323C_GPIO_LED_LEFT_AMBER,
		.active_low = 1,
	पूर्ण,
पूर्ण;


अटल काष्ठा gpio_led_platक्रमm_data dns323ab_led_data = अणु
	.num_leds	= ARRAY_SIZE(dns323ab_leds),
	.leds		= dns323ab_leds,
	.gpio_blink_set = orion_gpio_led_blink_set,
पूर्ण;

अटल काष्ठा gpio_led_platक्रमm_data dns323c_led_data = अणु
	.num_leds	= ARRAY_SIZE(dns323c_leds),
	.leds		= dns323c_leds,
	.gpio_blink_set = orion_gpio_led_blink_set,
पूर्ण;

अटल काष्ठा platक्रमm_device dns323_gpio_leds = अणु
	.name		= "leds-gpio",
	.id		= -1,
	.dev		= अणु
		.platक्रमm_data	= &dns323ab_led_data,
	पूर्ण,
पूर्ण;

/****************************************************************************
 * GPIO Attached Keys
 */

अटल काष्ठा gpio_keys_button dns323ab_buttons[] = अणु
	अणु
		.code		= KEY_RESTART,
		.gpio		= DNS323_GPIO_KEY_RESET,
		.desc		= "Reset Button",
		.active_low	= 1,
	पूर्ण, अणु
		.code		= KEY_POWER,
		.gpio		= DNS323_GPIO_KEY_POWER,
		.desc		= "Power Button",
		.active_low	= 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_keys_platक्रमm_data dns323ab_button_data = अणु
	.buttons	= dns323ab_buttons,
	.nbuttons	= ARRAY_SIZE(dns323ab_buttons),
पूर्ण;

अटल काष्ठा gpio_keys_button dns323c_buttons[] = अणु
	अणु
		.code		= KEY_POWER,
		.gpio		= DNS323C_GPIO_KEY_POWER,
		.desc		= "Power Button",
		.active_low	= 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_keys_platक्रमm_data dns323c_button_data = अणु
	.buttons	= dns323c_buttons,
	.nbuttons	= ARRAY_SIZE(dns323c_buttons),
पूर्ण;

अटल काष्ठा platक्रमm_device dns323_button_device = अणु
	.name		= "gpio-keys",
	.id		= -1,
	.num_resources	= 0,
	.dev		= अणु
		.platक्रमm_data	= &dns323ab_button_data,
	पूर्ण,
पूर्ण;

/*****************************************************************************
 * SATA
 */
अटल काष्ठा mv_sata_platक्रमm_data dns323_sata_data = अणु
       .n_ports        = 2,
पूर्ण;

/****************************************************************************
 * General Setup
 */
अटल अचिन्हित पूर्णांक dns323a_mpp_modes[] __initdata = अणु
	MPP0_PCIE_RST_OUTn,
	MPP1_GPIO,		/* right amber LED (sata ch0) */
	MPP2_GPIO,		/* left amber LED (sata ch1) */
	MPP3_UNUSED,
	MPP4_GPIO,		/* घातer button LED */
	MPP5_GPIO,		/* घातer button LED */
	MPP6_GPIO,		/* GMT G751-2f overtemp */
	MPP7_GPIO,		/* M41T80 nIRQ/OUT/SQW */
	MPP8_GPIO,		/* triggers घातer off */
	MPP9_GPIO,		/* घातer button चयन */
	MPP10_GPIO,		/* reset button चयन */
	MPP11_UNUSED,
	MPP12_UNUSED,
	MPP13_UNUSED,
	MPP14_UNUSED,
	MPP15_UNUSED,
	MPP16_UNUSED,
	MPP17_UNUSED,
	MPP18_UNUSED,
	MPP19_UNUSED,
	0,
पूर्ण;

अटल अचिन्हित पूर्णांक dns323b_mpp_modes[] __initdata = अणु
	MPP0_UNUSED,
	MPP1_GPIO,		/* right amber LED (sata ch0) */
	MPP2_GPIO,		/* left amber LED (sata ch1) */
	MPP3_GPIO,		/* प्रणाली up flag */
	MPP4_GPIO,		/* घातer button LED */
	MPP5_GPIO,		/* घातer button LED */
	MPP6_GPIO,		/* GMT G751-2f overtemp */
	MPP7_GPIO,		/* M41T80 nIRQ/OUT/SQW */
	MPP8_GPIO,		/* triggers घातer off */
	MPP9_GPIO,		/* घातer button चयन */
	MPP10_GPIO,		/* reset button चयन */
	MPP11_UNUSED,
	MPP12_SATA_LED,
	MPP13_SATA_LED,
	MPP14_SATA_LED,
	MPP15_SATA_LED,
	MPP16_UNUSED,
	MPP17_UNUSED,
	MPP18_UNUSED,
	MPP19_UNUSED,
	0,
पूर्ण;

अटल अचिन्हित पूर्णांक dns323c_mpp_modes[] __initdata = अणु
	MPP0_GPIO,		/* ? input */
	MPP1_GPIO,		/* input घातer चयन (0 = pressed) */
	MPP2_GPIO,		/* output घातer off */
	MPP3_UNUSED,		/* ? output */
	MPP4_UNUSED,		/* ? output */
	MPP5_UNUSED,		/* ? output */
	MPP6_UNUSED,		/* ? output */
	MPP7_UNUSED,		/* ? output */
	MPP8_GPIO,		/* i/o right amber LED */
	MPP9_GPIO,		/* i/o left amber LED */
	MPP10_GPIO,		/* input */
	MPP11_UNUSED,
	MPP12_SATA_LED,
	MPP13_SATA_LED,
	MPP14_SATA_LED,
	MPP15_SATA_LED,
	MPP16_UNUSED,
	MPP17_GPIO,		/* घातer button LED */
	MPP18_GPIO,		/* fan speed bit 0 */
	MPP19_GPIO,		/* fan speed bit 1 */
	0,
पूर्ण;

/* Rev C1 Fan speed notes:
 *
 * The fan is controlled by 2 GPIOs on this board. The settings
 * of the bits is as follow:
 *
 *  GPIO 18    GPIO 19    Fan
 *
 *    0          0        stopped
 *    0          1        low speed
 *    1          0        high speed
 *    1          1        करोn't करो that (*)
 *
 * (*) I think the two bits control two feed-in resistors पूर्णांकo a fixed
 *     PWN circuit, setting both bits will basically go a 'bit' faster
 *     than high speed, but d-link करोesn't करो it and you may get out of
 *     HW spec so करोn't करो it.
 */

/*
 * On the DNS-323 A1 and B1 the following devices are attached via I2C:
 *
 *  i2c addr | chip        | description
 *  0x3e     | GMT G760Af  | fan speed PWM controller
 *  0x48     | GMT G751-2f | temp. sensor and therm. watchकरोg (LM75 compatible)
 *  0x68     | ST M41T80   | RTC w/ alarm
 */
अटल काष्ठा i2c_board_info __initdata dns323ab_i2c_devices[] = अणु
	अणु
		I2C_BOARD_INFO("g760a", 0x3e),
	पूर्ण, अणु
		I2C_BOARD_INFO("lm75", 0x48),
	पूर्ण, अणु
		I2C_BOARD_INFO("m41t80", 0x68),
	पूर्ण,
पूर्ण;

/*
 * On the DNS-323 C1 the following devices are attached via I2C:
 *
 *  i2c addr | chip        | description
 *  0x48     | GMT G751-2f | temp. sensor and therm. watchकरोg (LM75 compatible)
 *  0x68     | ST M41T80   | RTC w/ alarm
 */
अटल काष्ठा i2c_board_info __initdata dns323c_i2c_devices[] = अणु
	अणु
		I2C_BOARD_INFO("lm75", 0x48),
	पूर्ण, अणु
		I2C_BOARD_INFO("m41t80", 0x68),
	पूर्ण,
पूर्ण;

/* DNS-323 rev. A specअगरic घातer off method */
अटल व्योम dns323a_घातer_off(व्योम)
अणु
	pr_info("DNS-323: Triggering power-off...\n");
	gpio_set_value(DNS323_GPIO_POWER_OFF, 1);
पूर्ण

/* DNS-323 rev B specअगरic घातer off method */
अटल व्योम dns323b_घातer_off(व्योम)
अणु
	pr_info("DNS-323: Triggering power-off...\n");
	/* Pin has to be changed to 1 and back to 0 to करो actual घातer off. */
	gpio_set_value(DNS323_GPIO_POWER_OFF, 1);
	mdelay(100);
	gpio_set_value(DNS323_GPIO_POWER_OFF, 0);
पूर्ण

/* DNS-323 rev. C specअगरic घातer off method */
अटल व्योम dns323c_घातer_off(व्योम)
अणु
	pr_info("DNS-323: Triggering power-off...\n");
	gpio_set_value(DNS323C_GPIO_POWER_OFF, 1);
पूर्ण

अटल पूर्णांक dns323c_phy_fixup(काष्ठा phy_device *phy)
अणु
	phy->dev_flags |= MARVELL_PHY_M1118_DNS323_LEDS;

	वापस 0;
पूर्ण

अटल पूर्णांक __init dns323_identअगरy_rev(व्योम)
अणु
	u32 dev, rev, i, reg;

	pr_debug("DNS-323: Identifying board ... \n");

	/* Rev A1 has a 5181 */
	orion5x_pcie_id(&dev, &rev);
	अगर (dev == MV88F5181_DEV_ID) अणु
		pr_debug("DNS-323: 5181 found, board is A1\n");
		वापस DNS323_REV_A1;
	पूर्ण
	pr_debug("DNS-323: 5182 found, board is B1 or C1, checking PHY...\n");

	/* Rev B1 and C1 both have 5182, let's poke at the eth PHY. This is
	 * a bit gross but we want to करो that without links पूर्णांकo the eth
	 * driver so let's poke at it directly. We शेष to rev B1 in
	 * हाल the accesses fail
	 */

#घोषणा ETH_SMI_REG		(ORION5X_ETH_VIRT_BASE + 0x2000 + 0x004)
#घोषणा  SMI_BUSY		0x10000000
#घोषणा  SMI_READ_VALID		0x08000000
#घोषणा  SMI_OPCODE_READ	0x04000000
#घोषणा  SMI_OPCODE_WRITE	0x00000000

	क्रम (i = 0; i < 1000; i++) अणु
		reg = पढ़ोl(ETH_SMI_REG);
		अगर (!(reg & SMI_BUSY))
			अवरोध;
	पूर्ण
	अगर (i >= 1000) अणु
		pr_warn("DNS-323: Timeout accessing PHY, assuming rev B1\n");
		वापस DNS323_REV_B1;
	पूर्ण
	ग_लिखोl((3 << 21)	/* phy ID reg */ |
	       (8 << 16)	/* phy addr */ |
	       SMI_OPCODE_READ, ETH_SMI_REG);
	क्रम (i = 0; i < 1000; i++) अणु
		reg = पढ़ोl(ETH_SMI_REG);
		अगर (reg & SMI_READ_VALID)
			अवरोध;
	पूर्ण
	अगर (i >= 1000) अणु
		pr_warn("DNS-323: Timeout reading PHY, assuming rev B1\n");
		वापस DNS323_REV_B1;
	पूर्ण
	pr_debug("DNS-323: Ethernet PHY ID 0x%x\n", reg & 0xffff);

	/* Note: the Marvell tools mask the ID with 0x3f0 beक्रमe comparison
	 * but I करोn't see that making a dअगरference here, at least with
	 * any known Marvell PHY ID
	 */
	चयन(reg & 0xfff0) अणु
	हाल 0x0cc0: /* MV88E1111 */
		वापस DNS323_REV_B1;
	हाल 0x0e10: /* MV88E1118 */
		वापस DNS323_REV_C1;
	शेष:
		pr_warn("DNS-323: Unknown PHY ID 0x%04x, assuming rev B1\n",
			reg & 0xffff);
	पूर्ण
	वापस DNS323_REV_B1;
पूर्ण

अटल व्योम __init dns323_init(व्योम)
अणु
	/* Setup basic Orion functions. Need to be called early. */
	orion5x_init();

	/* Identअगरy revision */
	प्रणाली_rev = dns323_identअगरy_rev();
	pr_info("DNS-323: Identified HW revision %c1\n", 'A' + प्रणाली_rev);

	/* Just to be tricky, the 5182 has a completely dअगरferent
	 * set of MPP modes to the 5181.
	 */
	चयन(प्रणाली_rev) अणु
	हाल DNS323_REV_A1:
		orion5x_mpp_conf(dns323a_mpp_modes);
		ग_लिखोl(0, MPP_DEV_CTRL);		/* DEV_D[31:16] */
		अवरोध;
	हाल DNS323_REV_B1:
		orion5x_mpp_conf(dns323b_mpp_modes);
		अवरोध;
	हाल DNS323_REV_C1:
		orion5x_mpp_conf(dns323c_mpp_modes);
		अवरोध;
	पूर्ण

	/* setup flash mapping
	 * CS3 holds a 8 MB Spansion S29GL064M90TFIR4
	 */
	mvebu_mbus_add_winकरोw_by_id(ORION_MBUS_DEVBUS_BOOT_TARGET,
				    ORION_MBUS_DEVBUS_BOOT_ATTR,
				    DNS323_NOR_BOOT_BASE,
				    DNS323_NOR_BOOT_SIZE);
	platक्रमm_device_रेजिस्टर(&dns323_nor_flash);

	/* Sort out LEDs, Buttons and i2c devices */
	चयन(प्रणाली_rev) अणु
	हाल DNS323_REV_A1:
		/* The 5181 घातer LED is active low and requires
		 * DNS323_GPIO_LED_POWER1 to also be low.
		 */
		 dns323ab_leds[0].active_low = 1;
		 gpio_request(DNS323_GPIO_LED_POWER1, "Power Led Enable");
		 gpio_direction_output(DNS323_GPIO_LED_POWER1, 0);
		fallthrough;
	हाल DNS323_REV_B1:
		i2c_रेजिस्टर_board_info(0, dns323ab_i2c_devices,
				ARRAY_SIZE(dns323ab_i2c_devices));
		अवरोध;
	हाल DNS323_REV_C1:
		/* Hookup LEDs & Buttons */
		dns323_gpio_leds.dev.platक्रमm_data = &dns323c_led_data;
		dns323_button_device.dev.platक्रमm_data = &dns323c_button_data;

		/* Hookup i2c devices and fan driver */
		i2c_रेजिस्टर_board_info(0, dns323c_i2c_devices,
				ARRAY_SIZE(dns323c_i2c_devices));
		platक्रमm_device_रेजिस्टर_simple("dns323c-fan", 0, शून्य, 0);

		/* Register fixup क्रम the PHY LEDs */
		अगर (!IS_BUILTIN(CONFIG_PHYLIB))
			अवरोध;
		phy_रेजिस्टर_fixup_क्रम_uid(MARVELL_PHY_ID_88E1118,
					   MARVELL_PHY_ID_MASK,
					   dns323c_phy_fixup);
	पूर्ण

	platक्रमm_device_रेजिस्टर(&dns323_gpio_leds);
	platक्रमm_device_रेजिस्टर(&dns323_button_device);

	/*
	 * Configure peripherals.
	 */
	अगर (dns323_पढ़ो_mac_addr() < 0)
		prपूर्णांकk("DNS-323: Failed to read MAC address\n");
	orion5x_ehci0_init();
	orion5x_eth_init(&dns323_eth_data);
	orion5x_i2c_init();
	orion5x_uart0_init();

	/* Reमुख्यing GPIOs */
	चयन(प्रणाली_rev) अणु
	हाल DNS323_REV_A1:
		/* Poweroff GPIO */
		अगर (gpio_request(DNS323_GPIO_POWER_OFF, "POWEROFF") != 0 ||
		    gpio_direction_output(DNS323_GPIO_POWER_OFF, 0) != 0)
			pr_err("DNS-323: failed to setup power-off GPIO\n");
		pm_घातer_off = dns323a_घातer_off;
		अवरोध;
	हाल DNS323_REV_B1:
		/* 5182 built-in SATA init */
		orion5x_sata_init(&dns323_sata_data);

		/* The DNS323 rev B1 has flag to indicate the प्रणाली is up.
		 * Without this flag set, घातer LED will flash and cannot be
		 * controlled via leds-gpio.
		 */
		अगर (gpio_request(DNS323_GPIO_SYSTEM_UP, "SYS_READY") == 0)
			gpio_direction_output(DNS323_GPIO_SYSTEM_UP, 1);

		/* Poweroff GPIO */
		अगर (gpio_request(DNS323_GPIO_POWER_OFF, "POWEROFF") != 0 ||
		    gpio_direction_output(DNS323_GPIO_POWER_OFF, 0) != 0)
			pr_err("DNS-323: failed to setup power-off GPIO\n");
		pm_घातer_off = dns323b_घातer_off;
		अवरोध;
	हाल DNS323_REV_C1:
		/* 5182 built-in SATA init */
		orion5x_sata_init(&dns323_sata_data);

		/* Poweroff GPIO */
		अगर (gpio_request(DNS323C_GPIO_POWER_OFF, "POWEROFF") != 0 ||
		    gpio_direction_output(DNS323C_GPIO_POWER_OFF, 0) != 0)
			pr_err("DNS-323: failed to setup power-off GPIO\n");
		pm_घातer_off = dns323c_घातer_off;

		/* Now, -this- should theorically be करोne by the sata_mv driver
		 * once I figure out what's going on there. Maybe the behaviour
		 * of the LEDs should be somewhat passed via the platक्रमm_data.
		 * क्रम now, just whack the रेजिस्टर and make the LEDs happy
		 *
		 * Note: AFAIK, rev B1 needs the same treatement but I'll let
		 * somebody अन्यथा test it.
		 */
		ग_लिखोl(0x5, ORION5X_SATA_VIRT_BASE + 0x2c);
		अवरोध;
	पूर्ण
पूर्ण

/* Warning: D-Link uses a wrong mach-type (=526) in their bootloader */
MACHINE_START(DNS323, "D-Link DNS-323")
	/* Maपूर्णांकainer: Herbert Valerio Riedel <hvr@gnu.org> */
	.atag_offset	= 0x100,
	.nr_irqs	= ORION5X_NR_IRQS,
	.init_machine	= dns323_init,
	.map_io		= orion5x_map_io,
	.init_early	= orion5x_init_early,
	.init_irq	= orion5x_init_irq,
	.init_समय	= orion5x_समयr_init,
	.fixup		= tag_fixup_mem32,
	.restart	= orion5x_restart,
MACHINE_END
