<शैली गुरु>
/*
 * Copyright (C) 2007 Herbert Valerio Riedel <hvr@gnu.org>
 * Copyright (C) 2008 Martin Michlmayr <tbm@cyrius.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 */
#समावेश <linux/gpपन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/irq.h>
#समावेश <linux/mtd/physmap.h>
#समावेश <linux/mv643xx_eth.h>
#समावेश <linux/leds.h>
#समावेश <linux/gpio_keys.h>
#समावेश <linux/input.h>
#समावेश <linux/i2c.h>
#समावेश <linux/ata_platक्रमm.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश "common.h"
#समावेश "mpp.h"
#समावेश "orion5x.h"

#घोषणा MV2120_NOR_BOOT_BASE	0xf4000000
#घोषणा MV2120_NOR_BOOT_SIZE	SZ_512K

#घोषणा MV2120_GPIO_RTC_IRQ	3
#घोषणा MV2120_GPIO_KEY_RESET	17
#घोषणा MV2120_GPIO_KEY_POWER	18
#घोषणा MV2120_GPIO_POWER_OFF	19


/*****************************************************************************
 * Ethernet
 ****************************************************************************/
अटल काष्ठा mv643xx_eth_platक्रमm_data mv2120_eth_data = अणु
	.phy_addr	= MV643XX_ETH_PHY_ADDR(8),
पूर्ण;

अटल काष्ठा mv_sata_platक्रमm_data mv2120_sata_data = अणु
	.n_ports	= 2,
पूर्ण;

अटल काष्ठा mtd_partition mv2120_partitions[] = अणु
	अणु
		.name	= "firmware",
		.size	= 0x00080000,
		.offset	= 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा physmap_flash_data mv2120_nor_flash_data = अणु
	.width		= 1,
	.parts		= mv2120_partitions,
	.nr_parts	= ARRAY_SIZE(mv2120_partitions)
पूर्ण;

अटल काष्ठा resource mv2120_nor_flash_resource = अणु
	.flags		= IORESOURCE_MEM,
	.start		= MV2120_NOR_BOOT_BASE,
	.end		= MV2120_NOR_BOOT_BASE + MV2120_NOR_BOOT_SIZE - 1,
पूर्ण;

अटल काष्ठा platक्रमm_device mv2120_nor_flash = अणु
	.name		= "physmap-flash",
	.id		= 0,
	.dev		= अणु
		.platक्रमm_data	= &mv2120_nor_flash_data,
	पूर्ण,
	.resource	= &mv2120_nor_flash_resource,
	.num_resources	= 1,
पूर्ण;

अटल काष्ठा gpio_keys_button mv2120_buttons[] = अणु
	अणु
		.code		= KEY_RESTART,
		.gpio		= MV2120_GPIO_KEY_RESET,
		.desc		= "reset",
		.active_low	= 1,
	पूर्ण, अणु
		.code		= KEY_POWER,
		.gpio		= MV2120_GPIO_KEY_POWER,
		.desc		= "power",
		.active_low	= 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_keys_platक्रमm_data mv2120_button_data = अणु
	.buttons	= mv2120_buttons,
	.nbuttons	= ARRAY_SIZE(mv2120_buttons),
पूर्ण;

अटल काष्ठा platक्रमm_device mv2120_button_device = अणु
	.name		= "gpio-keys",
	.id		= -1,
	.num_resources	= 0,
	.dev		= अणु
		.platक्रमm_data	= &mv2120_button_data,
	पूर्ण,
पूर्ण;


/****************************************************************************
 * General Setup
 ****************************************************************************/
अटल अचिन्हित पूर्णांक mv2120_mpp_modes[] __initdata = अणु
	MPP0_GPIO,		/* Sys status LED */
	MPP1_GPIO,		/* Sys error LED */
	MPP2_GPIO,		/* OverTemp पूर्णांकerrupt */
	MPP3_GPIO,		/* RTC पूर्णांकerrupt */
	MPP4_GPIO,		/* V_LED 5V */
	MPP5_GPIO,		/* V_LED 3.3V */
	MPP6_UNUSED,
	MPP7_UNUSED,
	MPP8_GPIO,		/* SATA 0 fail LED */
	MPP9_GPIO,		/* SATA 1 fail LED */
	MPP10_UNUSED,
	MPP11_UNUSED,
	MPP12_SATA_LED,		/* SATA 0 presence */
	MPP13_SATA_LED,		/* SATA 1 presence */
	MPP14_SATA_LED,		/* SATA 0 active */
	MPP15_SATA_LED,		/* SATA 1 active */
	MPP16_UNUSED,
	MPP17_GPIO,		/* Reset button */
	MPP18_GPIO,		/* Power button */
	MPP19_GPIO,		/* Power off */
	0,
पूर्ण;

अटल काष्ठा i2c_board_info __initdata mv2120_i2c_rtc = अणु
	I2C_BOARD_INFO("pcf8563", 0x51),
	.irq	= 0,
पूर्ण;

अटल काष्ठा gpio_led mv2120_led_pins[] = अणु
	अणु
		.name			= "mv2120:blue:health",
		.gpio			= 0,
	पूर्ण,
	अणु
		.name			= "mv2120:red:health",
		.gpio			= 1,
	पूर्ण,
	अणु
		.name			= "mv2120:led:bright",
		.gpio			= 4,
		.शेष_trigger	= "default-on",
	पूर्ण,
	अणु
		.name			= "mv2120:led:dimmed",
		.gpio			= 5,
	पूर्ण,
	अणु
		.name			= "mv2120:red:sata0",
		.gpio			= 8,
		.active_low		= 1,
	पूर्ण,
	अणु
		.name			= "mv2120:red:sata1",
		.gpio			= 9,
		.active_low		= 1,
	पूर्ण,

पूर्ण;

अटल काष्ठा gpio_led_platक्रमm_data mv2120_led_data = अणु
	.leds		= mv2120_led_pins,
	.num_leds	= ARRAY_SIZE(mv2120_led_pins),
पूर्ण;

अटल काष्ठा platक्रमm_device mv2120_leds = अणु
	.name	= "leds-gpio",
	.id	= -1,
	.dev	= अणु
		.platक्रमm_data	= &mv2120_led_data,
	पूर्ण
पूर्ण;

अटल व्योम mv2120_घातer_off(व्योम)
अणु
	pr_info("%s: triggering power-off...\n", __func__);
	gpio_set_value(MV2120_GPIO_POWER_OFF, 0);
पूर्ण

अटल व्योम __init mv2120_init(व्योम)
अणु
	/* Setup basic Orion functions. Need to be called early. */
	orion5x_init();

	orion5x_mpp_conf(mv2120_mpp_modes);

	/*
	 * Configure peripherals.
	 */
	orion5x_ehci0_init();
	orion5x_ehci1_init();
	orion5x_eth_init(&mv2120_eth_data);
	orion5x_i2c_init();
	orion5x_sata_init(&mv2120_sata_data);
	orion5x_uart0_init();
	orion5x_xor_init();

	mvebu_mbus_add_winकरोw_by_id(ORION_MBUS_DEVBUS_BOOT_TARGET,
				    ORION_MBUS_DEVBUS_BOOT_ATTR,
				    MV2120_NOR_BOOT_BASE,
				    MV2120_NOR_BOOT_SIZE);
	platक्रमm_device_रेजिस्टर(&mv2120_nor_flash);

	platक्रमm_device_रेजिस्टर(&mv2120_button_device);

	अगर (gpio_request(MV2120_GPIO_RTC_IRQ, "rtc") == 0) अणु
		अगर (gpio_direction_input(MV2120_GPIO_RTC_IRQ) == 0)
			mv2120_i2c_rtc.irq = gpio_to_irq(MV2120_GPIO_RTC_IRQ);
		अन्यथा
			gpio_मुक्त(MV2120_GPIO_RTC_IRQ);
	पूर्ण
	i2c_रेजिस्टर_board_info(0, &mv2120_i2c_rtc, 1);
	platक्रमm_device_रेजिस्टर(&mv2120_leds);

	/* रेजिस्टर mv2120 specअगरic घातer-off method */
	अगर (gpio_request(MV2120_GPIO_POWER_OFF, "POWEROFF") != 0 ||
	    gpio_direction_output(MV2120_GPIO_POWER_OFF, 1) != 0)
		pr_err("mv2120: failed to setup power-off GPIO\n");
	pm_घातer_off = mv2120_घातer_off;
पूर्ण

/* Warning: HP uses a wrong mach-type (=526) in their bootloader */
MACHINE_START(MV2120, "HP Media Vault mv2120")
	/* Maपूर्णांकainer: Martin Michlmayr <tbm@cyrius.com> */
	.atag_offset	= 0x100,
	.nr_irqs	= ORION5X_NR_IRQS,
	.init_machine	= mv2120_init,
	.map_io		= orion5x_map_io,
	.init_early	= orion5x_init_early,
	.init_irq	= orion5x_init_irq,
	.init_समय	= orion5x_समयr_init,
	.fixup		= tag_fixup_mem32,
	.restart	= orion5x_restart,
MACHINE_END
