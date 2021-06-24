<शैली गुरु>
/*
 * arch/arm/mach-orion5x/net2big-setup.c
 *
 * LaCie 2Big Network NAS setup
 *
 * Copyright (C) 2009 Simon Guinot <sguinot@lacie.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mtd/physmap.h>
#समावेश <linux/mv643xx_eth.h>
#समावेश <linux/leds.h>
#समावेश <linux/gpio_keys.h>
#समावेश <linux/input.h>
#समावेश <linux/i2c.h>
#समावेश <linux/ata_platक्रमm.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/delay.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <plat/orion-gpपन.स>
#समावेश "common.h"
#समावेश "mpp.h"
#समावेश "orion5x.h"

/*****************************************************************************
 * LaCie 2Big Network Info
 ****************************************************************************/

/*
 * 512KB NOR flash Device bus boot chip select
 */

#घोषणा NET2BIG_NOR_BOOT_BASE		0xfff80000
#घोषणा NET2BIG_NOR_BOOT_SIZE		SZ_512K

/*****************************************************************************
 * 512KB NOR Flash on Boot Device
 ****************************************************************************/

/*
 * TODO: Check ग_लिखो support on flash MX29LV400CBTC-70G
 */

अटल काष्ठा mtd_partition net2big_partitions[] = अणु
	अणु
		.name		= "Full512kb",
		.size		= MTDPART_SIZ_FULL,
		.offset		= 0x00000000,
		.mask_flags	= MTD_WRITEABLE,
	पूर्ण,
पूर्ण;

अटल काष्ठा physmap_flash_data net2big_nor_flash_data = अणु
	.width		= 1,
	.parts		= net2big_partitions,
	.nr_parts	= ARRAY_SIZE(net2big_partitions),
पूर्ण;

अटल काष्ठा resource net2big_nor_flash_resource = अणु
	.flags			= IORESOURCE_MEM,
	.start			= NET2BIG_NOR_BOOT_BASE,
	.end			= NET2BIG_NOR_BOOT_BASE
					+ NET2BIG_NOR_BOOT_SIZE - 1,
पूर्ण;

अटल काष्ठा platक्रमm_device net2big_nor_flash = अणु
	.name			= "physmap-flash",
	.id			= 0,
	.dev		= अणु
		.platक्रमm_data	= &net2big_nor_flash_data,
	पूर्ण,
	.num_resources		= 1,
	.resource		= &net2big_nor_flash_resource,
पूर्ण;

/*****************************************************************************
 * Ethernet
 ****************************************************************************/

अटल काष्ठा mv643xx_eth_platक्रमm_data net2big_eth_data = अणु
	.phy_addr	= MV643XX_ETH_PHY_ADDR(8),
पूर्ण;

/*****************************************************************************
 * I2C devices
 ****************************************************************************/

/*
 * i2c addr | chip         | description
 * 0x32     | Ricoh 5C372b | RTC
 * 0x50     | HT24LC08     | eeprom (1kB)
 */
अटल काष्ठा i2c_board_info __initdata net2big_i2c_devices[] = अणु
	अणु
		I2C_BOARD_INFO("rs5c372b", 0x32),
	पूर्ण, अणु
		I2C_BOARD_INFO("24c08", 0x50),
	पूर्ण,
पूर्ण;

/*****************************************************************************
 * SATA
 ****************************************************************************/

अटल काष्ठा mv_sata_platक्रमm_data net2big_sata_data = अणु
	.n_ports	= 2,
पूर्ण;

#घोषणा NET2BIG_GPIO_SATA_POWER_REQ	19
#घोषणा NET2BIG_GPIO_SATA0_POWER	23
#घोषणा NET2BIG_GPIO_SATA1_POWER	25

अटल व्योम __init net2big_sata_घातer_init(व्योम)
अणु
	पूर्णांक err;

	/* Configure GPIOs over MPP max number. */
	orion_gpio_set_valid(NET2BIG_GPIO_SATA0_POWER, 1);
	orion_gpio_set_valid(NET2BIG_GPIO_SATA1_POWER, 1);

	err = gpio_request(NET2BIG_GPIO_SATA0_POWER, "SATA0 power status");
	अगर (err == 0) अणु
		err = gpio_direction_input(NET2BIG_GPIO_SATA0_POWER);
		अगर (err)
			gpio_मुक्त(NET2BIG_GPIO_SATA0_POWER);
	पूर्ण
	अगर (err) अणु
		pr_err("net2big: failed to setup SATA0 power GPIO\n");
		वापस;
	पूर्ण

	err = gpio_request(NET2BIG_GPIO_SATA1_POWER, "SATA1 power status");
	अगर (err == 0) अणु
		err = gpio_direction_input(NET2BIG_GPIO_SATA1_POWER);
		अगर (err)
			gpio_मुक्त(NET2BIG_GPIO_SATA1_POWER);
	पूर्ण
	अगर (err) अणु
		pr_err("net2big: failed to setup SATA1 power GPIO\n");
		जाओ err_मुक्त_1;
	पूर्ण

	err = gpio_request(NET2BIG_GPIO_SATA_POWER_REQ, "SATA power request");
	अगर (err == 0) अणु
		err = gpio_direction_output(NET2BIG_GPIO_SATA_POWER_REQ, 0);
		अगर (err)
			gpio_मुक्त(NET2BIG_GPIO_SATA_POWER_REQ);
	पूर्ण
	अगर (err) अणु
		pr_err("net2big: failed to setup SATA power request GPIO\n");
		जाओ err_मुक्त_2;
	पूर्ण

	अगर (gpio_get_value(NET2BIG_GPIO_SATA0_POWER) &&
		gpio_get_value(NET2BIG_GPIO_SATA1_POWER)) अणु
		वापस;
	पूर्ण

	/*
	 * SATA घातer up on both disk is करोne by pulling high the CPLD घातer
	 * request line. The 300ms delay is related to the CPLD घड़ी and is
	 * needed to be sure that the CPLD has take पूर्णांकo account the low line
	 * status.
	 */
	msleep(300);
	gpio_set_value(NET2BIG_GPIO_SATA_POWER_REQ, 1);
	pr_info("net2big: power up SATA hard disks\n");

	वापस;

err_मुक्त_2:
	gpio_मुक्त(NET2BIG_GPIO_SATA1_POWER);
err_मुक्त_1:
	gpio_मुक्त(NET2BIG_GPIO_SATA0_POWER);

	वापस;
पूर्ण

/*****************************************************************************
 * GPIO LEDs
 ****************************************************************************/

/*
 * The घातer front LEDs (blue and red) and SATA red LEDs are controlled via a
 * single GPIO line and are compatible with the leds-gpio driver.
 *
 * The SATA blue LEDs have some hardware blink capabilities which are detailed
 * in the following array:
 *
 * SATAx blue LED | SATAx activity | LED state
 *                |                |
 *       0        |       0        |  blink (rate 300ms)
 *       1        |       0        |  off
 *       ?        |       1        |  on
 *
 * Notes: The blue and the red front LED's can't be on at the same समय.
 *        Blue LED have priority.
 */

#घोषणा NET2BIG_GPIO_PWR_RED_LED	6
#घोषणा NET2BIG_GPIO_PWR_BLUE_LED	16
#घोषणा NET2BIG_GPIO_PWR_LED_BLINK_STOP	7

#घोषणा NET2BIG_GPIO_SATA0_RED_LED	11
#घोषणा NET2BIG_GPIO_SATA1_RED_LED	10

#घोषणा NET2BIG_GPIO_SATA0_BLUE_LED	17
#घोषणा NET2BIG_GPIO_SATA1_BLUE_LED	13

अटल काष्ठा gpio_led net2big_leds[] = अणु
	अणु
		.name = "net2big:red:power",
		.gpio = NET2BIG_GPIO_PWR_RED_LED,
	पूर्ण,
	अणु
		.name = "net2big:blue:power",
		.gpio = NET2BIG_GPIO_PWR_BLUE_LED,
	पूर्ण,
	अणु
		.name = "net2big:red:sata0",
		.gpio = NET2BIG_GPIO_SATA0_RED_LED,
	पूर्ण,
	अणु
		.name = "net2big:red:sata1",
		.gpio = NET2BIG_GPIO_SATA1_RED_LED,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_led_platक्रमm_data net2big_led_data = अणु
	.num_leds = ARRAY_SIZE(net2big_leds),
	.leds = net2big_leds,
पूर्ण;

अटल काष्ठा platक्रमm_device net2big_gpio_leds = अणु
	.name           = "leds-gpio",
	.id             = -1,
	.dev            = अणु
		.platक्रमm_data  = &net2big_led_data,
	पूर्ण,
पूर्ण;

अटल व्योम __init net2big_gpio_leds_init(व्योम)
अणु
	पूर्णांक err;

	/* Stop initial CPLD slow red/blue blinking on घातer LED. */
	err = gpio_request(NET2BIG_GPIO_PWR_LED_BLINK_STOP,
			   "Power LED blink stop");
	अगर (err == 0) अणु
		err = gpio_direction_output(NET2BIG_GPIO_PWR_LED_BLINK_STOP, 1);
		अगर (err)
			gpio_मुक्त(NET2BIG_GPIO_PWR_LED_BLINK_STOP);
	पूर्ण
	अगर (err)
		pr_err("net2big: failed to setup power LED blink GPIO\n");

	/*
	 * Configure SATA0 and SATA1 blue LEDs to blink in relation with the
	 * hard disk activity.
	 */
	err = gpio_request(NET2BIG_GPIO_SATA0_BLUE_LED,
			   "SATA0 blue LED control");
	अगर (err == 0) अणु
		err = gpio_direction_output(NET2BIG_GPIO_SATA0_BLUE_LED, 1);
		अगर (err)
			gpio_मुक्त(NET2BIG_GPIO_SATA0_BLUE_LED);
	पूर्ण
	अगर (err)
		pr_err("net2big: failed to setup SATA0 blue LED GPIO\n");

	err = gpio_request(NET2BIG_GPIO_SATA1_BLUE_LED,
			   "SATA1 blue LED control");
	अगर (err == 0) अणु
		err = gpio_direction_output(NET2BIG_GPIO_SATA1_BLUE_LED, 1);
		अगर (err)
			gpio_मुक्त(NET2BIG_GPIO_SATA1_BLUE_LED);
	पूर्ण
	अगर (err)
		pr_err("net2big: failed to setup SATA1 blue LED GPIO\n");

	platक्रमm_device_रेजिस्टर(&net2big_gpio_leds);
पूर्ण

/****************************************************************************
 * GPIO keys
 ****************************************************************************/

#घोषणा NET2BIG_GPIO_PUSH_BUTTON	18
#घोषणा NET2BIG_GPIO_POWER_SWITCH_ON	8
#घोषणा NET2BIG_GPIO_POWER_SWITCH_OFF	9

#घोषणा NET2BIG_SWITCH_POWER_ON		0x1
#घोषणा NET2BIG_SWITCH_POWER_OFF	0x2

अटल काष्ठा gpio_keys_button net2big_buttons[] = अणु
	अणु
		.type		= EV_SW,
		.code		= NET2BIG_SWITCH_POWER_OFF,
		.gpio		= NET2BIG_GPIO_POWER_SWITCH_OFF,
		.desc		= "Power rocker switch (auto|off)",
		.active_low	= 0,
	पूर्ण,
	अणु
		.type		= EV_SW,
		.code		= NET2BIG_SWITCH_POWER_ON,
		.gpio		= NET2BIG_GPIO_POWER_SWITCH_ON,
		.desc		= "Power rocker switch (on|auto)",
		.active_low	= 0,
	पूर्ण,
	अणु
		.type		= EV_KEY,
		.code		= KEY_POWER,
		.gpio		= NET2BIG_GPIO_PUSH_BUTTON,
		.desc		= "Front Push Button",
		.active_low	= 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_keys_platक्रमm_data net2big_button_data = अणु
	.buttons	= net2big_buttons,
	.nbuttons	= ARRAY_SIZE(net2big_buttons),
पूर्ण;

अटल काष्ठा platक्रमm_device net2big_gpio_buttons = अणु
	.name		= "gpio-keys",
	.id		= -1,
	.dev		= अणु
		.platक्रमm_data	= &net2big_button_data,
	पूर्ण,
पूर्ण;

/*****************************************************************************
 * General Setup
 ****************************************************************************/

अटल अचिन्हित पूर्णांक net2big_mpp_modes[] __initdata = अणु
	MPP0_GPIO,	/* Raid mode (bit 0) */
	MPP1_GPIO,	/* USB port 2 fuse (0 = Fail, 1 = Ok) */
	MPP2_GPIO,	/* Raid mode (bit 1) */
	MPP3_GPIO,	/* Board ID (bit 0) */
	MPP4_GPIO,	/* Fan activity (0 = Off, 1 = On) */
	MPP5_GPIO,	/* Fan fail detection */
	MPP6_GPIO,	/* Red front LED (0 = Off, 1 = On) */
	MPP7_GPIO,	/* Disable initial blinking on front LED */
	MPP8_GPIO,	/* Rear घातer चयन (on|स्वतः) */
	MPP9_GPIO,	/* Rear घातer चयन (स्वतः|off) */
	MPP10_GPIO,	/* SATA 1 red LED (0 = Off, 1 = On) */
	MPP11_GPIO,	/* SATA 0 red LED (0 = Off, 1 = On) */
	MPP12_GPIO,	/* Board ID (bit 1) */
	MPP13_GPIO,	/* SATA 1 blue LED blink control */
	MPP14_SATA_LED,
	MPP15_SATA_LED,
	MPP16_GPIO,	/* Blue front LED control */
	MPP17_GPIO,	/* SATA 0 blue LED blink control */
	MPP18_GPIO,	/* Front button (0 = Released, 1 = Pushed ) */
	MPP19_GPIO,	/* SATAअणु0,1पूर्ण घातer On/Off request */
	0,
	/* 22: USB port 1 fuse (0 = Fail, 1 = Ok) */
	/* 23: SATA 0 घातer status */
	/* 24: Board घातer off */
	/* 25: SATA 1 घातer status */
पूर्ण;

#घोषणा NET2BIG_GPIO_POWER_OFF		24

अटल व्योम net2big_घातer_off(व्योम)
अणु
	gpio_set_value(NET2BIG_GPIO_POWER_OFF, 1);
पूर्ण

अटल व्योम __init net2big_init(व्योम)
अणु
	/*
	 * Setup basic Orion functions. Need to be called early.
	 */
	orion5x_init();

	orion5x_mpp_conf(net2big_mpp_modes);

	/*
	 * Configure peripherals.
	 */
	orion5x_ehci0_init();
	orion5x_ehci1_init();
	orion5x_eth_init(&net2big_eth_data);
	orion5x_i2c_init();
	orion5x_uart0_init();
	orion5x_xor_init();

	net2big_sata_घातer_init();
	orion5x_sata_init(&net2big_sata_data);

	mvebu_mbus_add_winकरोw_by_id(ORION_MBUS_DEVBUS_BOOT_TARGET,
				    ORION_MBUS_DEVBUS_BOOT_ATTR,
				    NET2BIG_NOR_BOOT_BASE,
				    NET2BIG_NOR_BOOT_SIZE);
	platक्रमm_device_रेजिस्टर(&net2big_nor_flash);

	platक्रमm_device_रेजिस्टर(&net2big_gpio_buttons);
	net2big_gpio_leds_init();

	i2c_रेजिस्टर_board_info(0, net2big_i2c_devices,
				ARRAY_SIZE(net2big_i2c_devices));

	orion_gpio_set_valid(NET2BIG_GPIO_POWER_OFF, 1);

	अगर (gpio_request(NET2BIG_GPIO_POWER_OFF, "power-off") == 0 &&
	    gpio_direction_output(NET2BIG_GPIO_POWER_OFF, 0) == 0)
		pm_घातer_off = net2big_घातer_off;
	अन्यथा
		pr_err("net2big: failed to configure power-off GPIO\n");

	pr_notice("net2big: Flash writing is not yet supported.\n");
पूर्ण

/* Warning: LaCie use a wrong mach-type (0x20e=526) in their bootloader. */
MACHINE_START(NET2BIG, "LaCie 2Big Network")
	.atag_offset	= 0x100,
	.nr_irqs	= ORION5X_NR_IRQS,
	.init_machine	= net2big_init,
	.map_io		= orion5x_map_io,
	.init_early	= orion5x_init_early,
	.init_irq	= orion5x_init_irq,
	.init_समय	= orion5x_समयr_init,
	.fixup		= tag_fixup_mem32,
	.restart	= orion5x_restart,
MACHINE_END

