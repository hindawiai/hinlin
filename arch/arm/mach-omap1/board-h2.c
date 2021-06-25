<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/arch/arm/mach-omap1/board-h2.c
 *
 * Board specअगरic inits क्रम OMAP-1610 H2
 *
 * Copyright (C) 2001 RidgeRun, Inc.
 * Author: Greg Lonnon <glonnon@ridgerun.com>
 *
 * Copyright (C) 2002 MontaVista Software, Inc.
 *
 * Separated FPGA पूर्णांकerrupts from innovator1510.c and cleaned up क्रम 2.6
 * Copyright (C) 2004 Nokia Corporation by Tony Lindrgen <tony@atomide.com>
 *
 * H2 specअगरic changes and cleanup
 * Copyright (C) 2004 Nokia Corporation by Imre Deak <imre.deak@nokia.com>
 */
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/platnand.h>
#समावेश <linux/mtd/physmap.h>
#समावेश <linux/input.h>
#समावेश <linux/mfd/tps65010.h>
#समावेश <linux/smc91x.h>
#समावेश <linux/omapfb.h>
#समावेश <linux/platक्रमm_data/gpio-omap.h>
#समावेश <linux/leds.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>

#समावेश <mach/mux.h>
#समावेश <linux/omap-dma.h>
#समावेश <mach/tc.h>
#समावेश <linux/platक्रमm_data/keypad-omap.h>
#समावेश "flash.h"

#समावेश <mach/hardware.h>
#समावेश <mach/usb.h>

#समावेश "common.h"
#समावेश "board-h2.h"

/* The first 16 SoC GPIO lines are on this GPIO chip */
#घोषणा OMAP_GPIO_LABEL			"gpio-0-15"

/* At OMAP1610 Innovator the Ethernet is directly connected to CS1 */
#घोषणा OMAP1610_ETHR_START		0x04000300

अटल स्थिर अचिन्हित पूर्णांक h2_keymap[] = अणु
	KEY(0, 0, KEY_LEFT),
	KEY(1, 0, KEY_RIGHT),
	KEY(2, 0, KEY_3),
	KEY(3, 0, KEY_F10),
	KEY(4, 0, KEY_F5),
	KEY(5, 0, KEY_9),
	KEY(0, 1, KEY_DOWN),
	KEY(1, 1, KEY_UP),
	KEY(2, 1, KEY_2),
	KEY(3, 1, KEY_F9),
	KEY(4, 1, KEY_F7),
	KEY(5, 1, KEY_0),
	KEY(0, 2, KEY_ENTER),
	KEY(1, 2, KEY_6),
	KEY(2, 2, KEY_1),
	KEY(3, 2, KEY_F2),
	KEY(4, 2, KEY_F6),
	KEY(5, 2, KEY_HOME),
	KEY(0, 3, KEY_8),
	KEY(1, 3, KEY_5),
	KEY(2, 3, KEY_F12),
	KEY(3, 3, KEY_F3),
	KEY(4, 3, KEY_F8),
	KEY(5, 3, KEY_END),
	KEY(0, 4, KEY_7),
	KEY(1, 4, KEY_4),
	KEY(2, 4, KEY_F11),
	KEY(3, 4, KEY_F1),
	KEY(4, 4, KEY_F4),
	KEY(5, 4, KEY_ESC),
	KEY(0, 5, KEY_F13),
	KEY(1, 5, KEY_F14),
	KEY(2, 5, KEY_F15),
	KEY(3, 5, KEY_F16),
	KEY(4, 5, KEY_SLEEP),
पूर्ण;

अटल काष्ठा mtd_partition h2_nor_partitions[] = अणु
	/* bootloader (U-Boot, etc) in first sector */
	अणु
	      .name		= "bootloader",
	      .offset		= 0,
	      .size		= SZ_128K,
	      .mask_flags	= MTD_WRITEABLE, /* क्रमce पढ़ो-only */
	पूर्ण,
	/* bootloader params in the next sector */
	अणु
	      .name		= "params",
	      .offset		= MTDPART_OFS_APPEND,
	      .size		= SZ_128K,
	      .mask_flags	= 0,
	पूर्ण,
	/* kernel */
	अणु
	      .name		= "kernel",
	      .offset		= MTDPART_OFS_APPEND,
	      .size		= SZ_2M,
	      .mask_flags	= 0
	पूर्ण,
	/* file प्रणाली */
	अणु
	      .name		= "filesystem",
	      .offset		= MTDPART_OFS_APPEND,
	      .size		= MTDPART_SIZ_FULL,
	      .mask_flags	= 0
	पूर्ण
पूर्ण;

अटल काष्ठा physmap_flash_data h2_nor_data = अणु
	.width		= 2,
	.set_vpp	= omap1_set_vpp,
	.parts		= h2_nor_partitions,
	.nr_parts	= ARRAY_SIZE(h2_nor_partitions),
पूर्ण;

अटल काष्ठा resource h2_nor_resource = अणु
	/* This is on CS3, wherever it's mapped */
	.flags		= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा platक्रमm_device h2_nor_device = अणु
	.name		= "physmap-flash",
	.id		= 0,
	.dev		= अणु
		.platक्रमm_data	= &h2_nor_data,
	पूर्ण,
	.num_resources	= 1,
	.resource	= &h2_nor_resource,
पूर्ण;

अटल काष्ठा mtd_partition h2_nand_partitions[] = अणु
#अगर 0
	/* REVISIT:  enable these partitions अगर you make न_अंकD BOOT
	 * work on your H2 (rev C or newer); published versions of
	 * x-load only support P2 and H3.
	 */
	अणु
		.name		= "xloader",
		.offset		= 0,
		.size		= 64 * 1024,
		.mask_flags	= MTD_WRITEABLE,	/* क्रमce पढ़ो-only */
	पूर्ण,
	अणु
		.name		= "bootloader",
		.offset		= MTDPART_OFS_APPEND,
		.size		= 256 * 1024,
		.mask_flags	= MTD_WRITEABLE,	/* क्रमce पढ़ो-only */
	पूर्ण,
	अणु
		.name		= "params",
		.offset		= MTDPART_OFS_APPEND,
		.size		= 192 * 1024,
	पूर्ण,
	अणु
		.name		= "kernel",
		.offset		= MTDPART_OFS_APPEND,
		.size		= 2 * SZ_1M,
	पूर्ण,
#पूर्ण_अगर
	अणु
		.name		= "filesystem",
		.size		= MTDPART_SIZ_FULL,
		.offset		= MTDPART_OFS_APPEND,
	पूर्ण,
पूर्ण;

#घोषणा H2_न_अंकD_RB_GPIO_PIN	62

अटल पूर्णांक h2_nand_dev_पढ़ोy(काष्ठा nand_chip *chip)
अणु
	वापस gpio_get_value(H2_न_अंकD_RB_GPIO_PIN);
पूर्ण

अटल काष्ठा platक्रमm_nand_data h2_nand_platdata = अणु
	.chip	= अणु
		.nr_chips		= 1,
		.chip_offset		= 0,
		.nr_partitions		= ARRAY_SIZE(h2_nand_partitions),
		.partitions		= h2_nand_partitions,
		.options		= न_अंकD_SAMSUNG_LP_OPTIONS,
	पूर्ण,
	.ctrl	= अणु
		.cmd_ctrl	= omap1_nand_cmd_ctl,
		.dev_पढ़ोy	= h2_nand_dev_पढ़ोy,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource h2_nand_resource = अणु
	.flags		= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा platक्रमm_device h2_nand_device = अणु
	.name		= "gen_nand",
	.id		= 0,
	.dev		= अणु
		.platक्रमm_data	= &h2_nand_platdata,
	पूर्ण,
	.num_resources	= 1,
	.resource	= &h2_nand_resource,
पूर्ण;

अटल काष्ठा smc91x_platdata h2_smc91x_info = अणु
	.flags	= SMC91X_USE_16BIT | SMC91X_NOWAIT,
	.leda	= RPC_LED_100_10,
	.ledb	= RPC_LED_TX_RX,
पूर्ण;

अटल काष्ठा resource h2_smc91x_resources[] = अणु
	[0] = अणु
		.start	= OMAP1610_ETHR_START,		/* Physical */
		.end	= OMAP1610_ETHR_START + 0xf,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.flags	= IORESOURCE_IRQ | IORESOURCE_IRQ_LOWEDGE,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device h2_smc91x_device = अणु
	.name		= "smc91x",
	.id		= 0,
	.dev	= अणु
		.platक्रमm_data	= &h2_smc91x_info,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(h2_smc91x_resources),
	.resource	= h2_smc91x_resources,
पूर्ण;

अटल काष्ठा resource h2_kp_resources[] = अणु
	[0] = अणु
		.start	= INT_KEYBOARD,
		.end	= INT_KEYBOARD,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा matrix_keymap_data h2_keymap_data = अणु
	.keymap		= h2_keymap,
	.keymap_size	= ARRAY_SIZE(h2_keymap),
पूर्ण;

अटल काष्ठा omap_kp_platक्रमm_data h2_kp_data = अणु
	.rows		= 8,
	.cols		= 8,
	.keymap_data	= &h2_keymap_data,
	.rep		= true,
	.delay		= 9,
	.dbounce	= true,
पूर्ण;

अटल काष्ठा platक्रमm_device h2_kp_device = अणु
	.name		= "omap-keypad",
	.id		= -1,
	.dev		= अणु
		.platक्रमm_data = &h2_kp_data,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(h2_kp_resources),
	.resource	= h2_kp_resources,
पूर्ण;

अटल स्थिर काष्ठा gpio_led h2_gpio_led_pins[] = अणु
	अणु
		.name		= "h2:red",
		.शेष_trigger = "heartbeat",
		.gpio		= 3,
	पूर्ण,
	अणु
		.name		= "h2:green",
		.शेष_trigger = "cpu0",
		.gpio		= OMAP_MPUIO(4),
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_led_platक्रमm_data h2_gpio_led_data = अणु
	.leds		= h2_gpio_led_pins,
	.num_leds	= ARRAY_SIZE(h2_gpio_led_pins),
पूर्ण;

अटल काष्ठा platक्रमm_device h2_gpio_leds = अणु
	.name	= "leds-gpio",
	.id	= -1,
	.dev	= अणु
		.platक्रमm_data = &h2_gpio_led_data,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device *h2_devices[] __initdata = अणु
	&h2_nor_device,
	&h2_nand_device,
	&h2_smc91x_device,
	&h2_kp_device,
	&h2_gpio_leds,
पूर्ण;

अटल व्योम __init h2_init_smc91x(व्योम)
अणु
	अगर (gpio_request(0, "SMC91x irq") < 0) अणु
		prपूर्णांकk("Error requesting gpio 0 for smc91x irq\n");
		वापस;
	पूर्ण
पूर्ण

अटल पूर्णांक tps_setup(काष्ठा i2c_client *client, व्योम *context)
अणु
	अगर (!IS_BUILTIN(CONFIG_TPS65010))
		वापस -ENOSYS;

	tps65010_config_vregs1(TPS_LDO2_ENABLE | TPS_VLDO2_3_0V |
				TPS_LDO1_ENABLE | TPS_VLDO1_3_0V);

	वापस 0;
पूर्ण

अटल काष्ठा tps65010_board tps_board = अणु
	.base		= H2_TPS_GPIO_BASE,
	.ouपंचांगask	= 0x0f,
	.setup		= tps_setup,
पूर्ण;

अटल काष्ठा i2c_board_info __initdata h2_i2c_board_info[] = अणु
	अणु
		I2C_BOARD_INFO("tps65010", 0x48),
		.platक्रमm_data	= &tps_board,
	पूर्ण, अणु
		.type = "isp1301_omap",
		.addr = 0x2d,
		.dev_name = "isp1301",
	पूर्ण,
पूर्ण;

अटल काष्ठा gpiod_lookup_table isp1301_gpiod_table = अणु
	.dev_id = "isp1301",
	.table = अणु
		/* Active low since the irq triggers on falling edge */
		GPIO_LOOKUP(OMAP_GPIO_LABEL, 2,
			    शून्य, GPIO_ACTIVE_LOW),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा omap_usb_config h2_usb_config __initdata = अणु
	/* usb1 has a Mini-AB port and बाह्यal isp1301 transceiver */
	.otg		= 2,

#अगर IS_ENABLED(CONFIG_USB_OMAP)
	.hmc_mode	= 19,	/* 0:host(off) 1:dev|otg 2:disabled */
	/* .hmc_mode	= 21,*/	/* 0:host(off) 1:dev(loopback) 2:host(loopback) */
#या_अगर	IS_ENABLED(CONFIG_USB_OHCI_HCD)
	/* needs OTG cable, or NONSTANDARD (B-to-MiniB) */
	.hmc_mode	= 20,	/* 1:dev|otg(off) 1:host 2:disabled */
#पूर्ण_अगर

	.pins[1]	= 3,
पूर्ण;

अटल स्थिर काष्ठा omap_lcd_config h2_lcd_config __initस्थिर = अणु
	.ctrl_name	= "internal",
पूर्ण;

अटल व्योम __init h2_init(व्योम)
अणु
	h2_init_smc91x();

	/* Here we assume the NOR boot config:  NOR on CS3 (possibly swapped
	 * to address 0 by a dip चयन), न_अंकD on CS2B.  The न_अंकD driver will
	 * notice whether a न_अंकD chip is enabled at probe समय.
	 *
	 * FIXME revC boards (and H3) support न_अंकD-boot, with a dip चयन to
	 * put NOR on CS2B and न_अंकD (which on H2 may be 16bit) on CS3.  Try
	 * detecting that in code here, to aव्योम probing every possible flash
	 * configuration...
	 */
	h2_nor_resource.end = h2_nor_resource.start = omap_cs3_phys();
	h2_nor_resource.end += SZ_32M - 1;

	h2_nand_resource.end = h2_nand_resource.start = OMAP_CS2B_PHYS;
	h2_nand_resource.end += SZ_4K - 1;
	BUG_ON(gpio_request(H2_न_अंकD_RB_GPIO_PIN, "NAND ready") < 0);
	gpio_direction_input(H2_न_अंकD_RB_GPIO_PIN);

	gpiod_add_lookup_table(&isp1301_gpiod_table);

	omap_cfg_reg(L3_1610_FLASH_CS2B_OE);
	omap_cfg_reg(M8_1610_FLASH_CS2B_WE);

	/* MMC:  card detect and WP */
	/* omap_cfg_reg(U19_ARMIO1); */		/* CD */
	omap_cfg_reg(BALLOUT_V8_ARMIO3);	/* WP */

	/* Mux pins क्रम keypad */
	omap_cfg_reg(F18_1610_KBC0);
	omap_cfg_reg(D20_1610_KBC1);
	omap_cfg_reg(D19_1610_KBC2);
	omap_cfg_reg(E18_1610_KBC3);
	omap_cfg_reg(C21_1610_KBC4);
	omap_cfg_reg(G18_1610_KBR0);
	omap_cfg_reg(F19_1610_KBR1);
	omap_cfg_reg(H14_1610_KBR2);
	omap_cfg_reg(E20_1610_KBR3);
	omap_cfg_reg(E19_1610_KBR4);
	omap_cfg_reg(N19_1610_KBR5);

	/* GPIO based LEDs */
	omap_cfg_reg(P18_1610_GPIO3);
	omap_cfg_reg(MPUIO4);

	h2_smc91x_resources[1].start = gpio_to_irq(0);
	h2_smc91x_resources[1].end = gpio_to_irq(0);
	platक्रमm_add_devices(h2_devices, ARRAY_SIZE(h2_devices));
	omap_serial_init();

	/* ISP1301 IRQ wired at M14 */
	omap_cfg_reg(M14_1510_GPIO2);
	h2_i2c_board_info[0].irq = gpio_to_irq(58);
	omap_रेजिस्टर_i2c_bus(1, 100, h2_i2c_board_info,
			      ARRAY_SIZE(h2_i2c_board_info));
	omap1_usb_init(&h2_usb_config);
	h2_mmc_init();

	omapfb_set_lcd_config(&h2_lcd_config);
पूर्ण

MACHINE_START(OMAP_H2, "TI-H2")
	/* Maपूर्णांकainer: Imre Deak <imre.deak@nokia.com> */
	.atag_offset	= 0x100,
	.map_io		= omap16xx_map_io,
	.init_early     = omap1_init_early,
	.init_irq	= omap1_init_irq,
	.handle_irq	= omap1_handle_irq,
	.init_machine	= h2_init,
	.init_late	= omap1_init_late,
	.init_समय	= omap1_समयr_init,
	.restart	= omap1_restart,
MACHINE_END
