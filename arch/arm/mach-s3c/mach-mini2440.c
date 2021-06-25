<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (c) 2008 Ramax Lo <ramaxlo@gmail.com>
//      Based on mach-anubis.c by Ben Dooks <ben@simtec.co.uk>
//      and modअगरications by SBZ <sbz@spgui.org> and
//      Weibing <http://weibing.blogbus.com> and
//      Michel Pollet <buserror@gmail.com>
//
// For product inक्रमmation, visit https://code.google.com/p/mini2440/

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/समयr.h>
#समावेश <linux/init.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/input.h>
#समावेश <linux/पन.स>
#समावेश <linux/serial_core.h>
#समावेश <linux/serial_s3c.h>
#समावेश <linux/dm9000.h>
#समावेश <linux/property.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/gpio_keys.h>
#समावेश <linux/i2c.h>
#समावेश <linux/mmc/host.h>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>

#समावेश <linux/platक्रमm_data/fb-s3c2410.h>
#समावेश <यंत्र/mach-types.h>

#समावेश "regs-gpio.h"
#समावेश <linux/platक्रमm_data/leds-s3c24xx.h>
#समावेश <mach/irqs.h>
#समावेश "gpio-samsung.h"
#समावेश <linux/platक्रमm_data/mtd-nand-s3c2410.h>
#समावेश <linux/platक्रमm_data/i2c-s3c2410.h>
#समावेश <linux/platक्रमm_data/mmc-s3cmci.h>
#समावेश <linux/platक्रमm_data/usb-s3c2410_udc.h>

#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/mtd/nand-ecc-sw-hamming.h>
#समावेश <linux/mtd/partitions.h>

#समावेश "gpio-cfg.h"
#समावेश "devs.h"
#समावेश "cpu.h"

#समावेश <sound/s3c24xx_uda134x.h>

#समावेश "s3c24xx.h"

#घोषणा MACH_MINI2440_DM9K_BASE (S3C2410_CS4 + 0x300)

अटल काष्ठा map_desc mini2440_iodesc[] __initdata = अणु
	/* nothing to declare, move aदीर्घ */
पूर्ण;

#घोषणा UCON S3C2410_UCON_DEFAULT
#घोषणा ULCON (S3C2410_LCON_CS8 | S3C2410_LCON_PNONE | S3C2410_LCON_STOPB)
#घोषणा UFCON (S3C2410_UFCON_RXTRIG8 | S3C2410_UFCON_FIFOMODE)


अटल काष्ठा s3c2410_uartcfg mini2440_uartcfgs[] __initdata = अणु
	[0] = अणु
		.hwport		= 0,
		.flags		= 0,
		.ucon		= UCON,
		.ulcon		= ULCON,
		.ufcon		= UFCON,
	पूर्ण,
	[1] = अणु
		.hwport		= 1,
		.flags		= 0,
		.ucon		= UCON,
		.ulcon		= ULCON,
		.ufcon		= UFCON,
	पूर्ण,
	[2] = अणु
		.hwport		= 2,
		.flags		= 0,
		.ucon		= UCON,
		.ulcon		= ULCON,
		.ufcon		= UFCON,
	पूर्ण,
पूर्ण;

/* USB device UDC support */

अटल काष्ठा s3c2410_udc_mach_info mini2440_udc_cfg __initdata = अणु
	.pullup_pin = S3C2410_GPC(5),
पूर्ण;


/* LCD timing and setup */

/*
 * This macro simplअगरies the table bellow
 */
#घोषणा _LCD_DECLARE(_घड़ी, _xres, margin_left, margin_right, hsync, \
			_yres, margin_top, margin_bottom, vsync, refresh) \
	.width = _xres, \
	.xres = _xres, \
	.height = _yres, \
	.yres = _yres, \
	.left_margin	= margin_left,	\
	.right_margin	= margin_right,	\
	.upper_margin	= margin_top,	\
	.lower_margin	= margin_bottom,	\
	.hsync_len	= hsync,	\
	.vsync_len	= vsync,	\
	.pixघड़ी	= ((_घड़ी*100000000000LL) /	\
			   ((refresh) * \
			   (hsync + margin_left + _xres + margin_right) * \
			   (vsync + margin_top + _yres + margin_bottom))), \
	.bpp		= 16,\
	.type		= (S3C2410_LCDCON1_TFT16BPP |\
			   S3C2410_LCDCON1_TFT)

अटल काष्ठा s3c2410fb_display mini2440_lcd_cfg[] __initdata = अणु
	[0] = अणु	/* mini2440 + 3.5" TFT + touchscreen */
		_LCD_DECLARE(
			7,			/* The 3.5 is quite fast */
			240, 21, 38, 6,		/* x timing */
			320, 4, 4, 2,		/* y timing */
			60),			/* refresh rate */
		.lcdcon5	= (S3C2410_LCDCON5_FRM565 |
				   S3C2410_LCDCON5_INVVLINE |
				   S3C2410_LCDCON5_INVVFRAME |
				   S3C2410_LCDCON5_INVVDEN |
				   S3C2410_LCDCON5_PWREN),
	पूर्ण,
	[1] = अणु /* mini2440 + 7" TFT + touchscreen */
		_LCD_DECLARE(
			10,			/* the 7" runs slower */
			800, 40, 40, 48,	/* x timing */
			480, 29, 3, 3,		/* y timing */
			50),			/* refresh rate */
		.lcdcon5	= (S3C2410_LCDCON5_FRM565 |
				   S3C2410_LCDCON5_INVVLINE |
				   S3C2410_LCDCON5_INVVFRAME |
				   S3C2410_LCDCON5_PWREN),
	पूर्ण,
	/* The VGA shield can outout at several resolutions. All share
	 * the same timings, however, anything smaller than 1024x768
	 * will only be displayed in the top left corner of a 1024x768
	 * XGA output unless you add optional dip चयनes to the shield.
	 * Thereक्रमe timings क्रम other resolutions have been omitted here.
	 */
	[2] = अणु
		_LCD_DECLARE(
			10,
			1024, 1, 2, 2,		/* y timing */
			768, 200, 16, 16,	/* x timing */
			24),	/* refresh rate, maximum stable,
				 * tested with the FPGA shield
				 */
		.lcdcon5	= (S3C2410_LCDCON5_FRM565 |
				   S3C2410_LCDCON5_HWSWP),
	पूर्ण,
	/* mini2440 + 3.5" TFT (LCD-W35i, LQ035Q1DG06 type) + touchscreen*/
	[3] = अणु
		_LCD_DECLARE(
			/* घड़ी */
			7,
			/* xres, margin_right, margin_left, hsync */
			320, 68, 66, 4,
			/* yres, margin_top, margin_bottom, vsync */
			240, 4, 4, 9,
			/* refresh rate */
			60),
		.lcdcon5	= (S3C2410_LCDCON5_FRM565 |
				   S3C2410_LCDCON5_INVVDEN |
				   S3C2410_LCDCON5_INVVFRAME |
				   S3C2410_LCDCON5_INVVLINE |
				   S3C2410_LCDCON5_INVVCLK |
				   S3C2410_LCDCON5_HWSWP),
	पूर्ण,
पूर्ण;

/* toकरो - put पूर्णांकo gpio header */

#घोषणा S3C2410_GPCCON_MASK(x)	(3 << ((x) * 2))
#घोषणा S3C2410_GPDCON_MASK(x)	(3 << ((x) * 2))

अटल काष्ठा s3c2410fb_mach_info mini2440_fb_info __initdata = अणु
	.displays	 = &mini2440_lcd_cfg[0], /* not स्थिरant! see init */
	.num_displays	 = 1,
	.शेष_display = 0,

	/* Enable VD[2..7], VD[10..15], VD[18..23] and VCLK, syncs, VDEN
	 * and disable the pull करोwn resistors on pins we are using क्रम LCD
	 * data.
	 */

	.gpcup		= (0xf << 1) | (0x3f << 10),

	.gpccon		= (S3C2410_GPC1_VCLK   | S3C2410_GPC2_VLINE |
			   S3C2410_GPC3_VFRAME | S3C2410_GPC4_VM |
			   S3C2410_GPC10_VD2   | S3C2410_GPC11_VD3 |
			   S3C2410_GPC12_VD4   | S3C2410_GPC13_VD5 |
			   S3C2410_GPC14_VD6   | S3C2410_GPC15_VD7),

	.gpccon_mask	= (S3C2410_GPCCON_MASK(1)  | S3C2410_GPCCON_MASK(2)  |
			   S3C2410_GPCCON_MASK(3)  | S3C2410_GPCCON_MASK(4)  |
			   S3C2410_GPCCON_MASK(10) | S3C2410_GPCCON_MASK(11) |
			   S3C2410_GPCCON_MASK(12) | S3C2410_GPCCON_MASK(13) |
			   S3C2410_GPCCON_MASK(14) | S3C2410_GPCCON_MASK(15)),

	.gpccon_reg	= S3C2410_GPCCON,
	.gpcup_reg	= S3C2410_GPCUP,

	.gpdup		= (0x3f << 2) | (0x3f << 10),

	.gpdcon		= (S3C2410_GPD2_VD10  | S3C2410_GPD3_VD11 |
			   S3C2410_GPD4_VD12  | S3C2410_GPD5_VD13 |
			   S3C2410_GPD6_VD14  | S3C2410_GPD7_VD15 |
			   S3C2410_GPD10_VD18 | S3C2410_GPD11_VD19 |
			   S3C2410_GPD12_VD20 | S3C2410_GPD13_VD21 |
			   S3C2410_GPD14_VD22 | S3C2410_GPD15_VD23),

	.gpdcon_mask	= (S3C2410_GPDCON_MASK(2)  | S3C2410_GPDCON_MASK(3) |
			   S3C2410_GPDCON_MASK(4)  | S3C2410_GPDCON_MASK(5) |
			   S3C2410_GPDCON_MASK(6)  | S3C2410_GPDCON_MASK(7) |
			   S3C2410_GPDCON_MASK(10) | S3C2410_GPDCON_MASK(11)|
			   S3C2410_GPDCON_MASK(12) | S3C2410_GPDCON_MASK(13)|
			   S3C2410_GPDCON_MASK(14) | S3C2410_GPDCON_MASK(15)),

	.gpdcon_reg	= S3C2410_GPDCON,
	.gpdup_reg	= S3C2410_GPDUP,
पूर्ण;

/* MMC/SD  */

अटल काष्ठा s3c24xx_mci_pdata mini2440_mmc_cfg __initdata = अणु
	.wprotect_invert	= 1,
	.set_घातer		= s3c24xx_mci_def_set_घातer,
	.ocr_avail		= MMC_VDD_32_33|MMC_VDD_33_34,
पूर्ण;

अटल काष्ठा gpiod_lookup_table mini2440_mmc_gpio_table = अणु
	.dev_id = "s3c2410-sdi",
	.table = अणु
		/* Card detect S3C2410_GPG(8) */
		GPIO_LOOKUP("GPIOG", 8, "cd", GPIO_ACTIVE_LOW),
		/* Write protect S3C2410_GPH(8) */
		GPIO_LOOKUP("GPIOH", 8, "wp", GPIO_ACTIVE_HIGH),
		/* bus pins */
		GPIO_LOOKUP_IDX("GPIOE",  5, "bus", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("GPIOE",  6, "bus", 1, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("GPIOE",  7, "bus", 2, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("GPIOE",  8, "bus", 3, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("GPIOE",  9, "bus", 4, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("GPIOE", 10, "bus", 5, GPIO_ACTIVE_HIGH),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

/* न_अंकD Flash on MINI2440 board */

अटल काष्ठा mtd_partition mini2440_शेष_nand_part[] __initdata = अणु
	[0] = अणु
		.name	= "u-boot",
		.size	= SZ_256K,
		.offset	= 0,
	पूर्ण,
	[1] = अणु
		.name	= "u-boot-env",
		.size	= SZ_128K,
		.offset	= SZ_256K,
	पूर्ण,
	[2] = अणु
		.name	= "kernel",
		/* 5 megabytes, क्रम a kernel with no modules
		 * or a uImage with a ramdisk attached
		 */
		.size	= 0x00500000,
		.offset	= SZ_256K + SZ_128K,
	पूर्ण,
	[3] = अणु
		.name	= "root",
		.offset	= SZ_256K + SZ_128K + 0x00500000,
		.size	= MTDPART_SIZ_FULL,
	पूर्ण,
पूर्ण;

अटल काष्ठा s3c2410_nand_set mini2440_nand_sets[] __initdata = अणु
	[0] = अणु
		.name		= "nand",
		.nr_chips	= 1,
		.nr_partitions	= ARRAY_SIZE(mini2440_शेष_nand_part),
		.partitions	= mini2440_शेष_nand_part,
		.flash_bbt	= 1, /* we use u-boot to create a BBT */
	पूर्ण,
पूर्ण;

अटल काष्ठा s3c2410_platक्रमm_nand mini2440_nand_info __initdata = अणु
	.tacls		= 0,
	.twrph0		= 25,
	.twrph1		= 15,
	.nr_sets	= ARRAY_SIZE(mini2440_nand_sets),
	.sets		= mini2440_nand_sets,
	.ignore_unset_ecc = 1,
	.engine_type	= न_अंकD_ECC_ENGINE_TYPE_ON_HOST,
पूर्ण;

/* DM9000AEP 10/100 ethernet controller */

अटल काष्ठा resource mini2440_dm9k_resource[] = अणु
	[0] = DEFINE_RES_MEM(MACH_MINI2440_DM9K_BASE, 4),
	[1] = DEFINE_RES_MEM(MACH_MINI2440_DM9K_BASE + 4, 4),
	[2] = DEFINE_RES_NAMED(IRQ_EINT7, 1, शून्य, IORESOURCE_IRQ
						| IORESOURCE_IRQ_HIGHEDGE),
पूर्ण;

/*
 * The DM9000 has no eeprom, and it's MAC address is set by
 * the bootloader beक्रमe starting the kernel.
 */
अटल काष्ठा dm9000_plat_data mini2440_dm9k_pdata = अणु
	.flags		= (DM9000_PLATF_16BITONLY | DM9000_PLATF_NO_EEPROM),
पूर्ण;

अटल काष्ठा platक्रमm_device mini2440_device_eth = अणु
	.name		= "dm9000",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(mini2440_dm9k_resource),
	.resource	= mini2440_dm9k_resource,
	.dev		= अणु
		.platक्रमm_data	= &mini2440_dm9k_pdata,
	पूर्ण,
पूर्ण;

/*  CON5
 *	+--+	 /-----\
 *	|  |    |	|
 *	|  |	|  BAT	|
 *	|  |	 \_____/
 *	|  |
 *	|  |  +----+  +----+
 *	|  |  | K5 |  | K1 |
 *	|  |  +----+  +----+
 *	|  |  +----+  +----+
 *	|  |  | K4 |  | K2 |
 *	|  |  +----+  +----+
 *	|  |  +----+  +----+
 *	|  |  | K6 |  | K3 |
 *	|  |  +----+  +----+
 *	  .....
 */
अटल काष्ठा gpio_keys_button mini2440_buttons[] = अणु
	अणु
		.gpio		= S3C2410_GPG(0),		/* K1 */
		.code		= KEY_F1,
		.desc		= "Button 1",
		.active_low	= 1,
	पूर्ण,
	अणु
		.gpio		= S3C2410_GPG(3),		/* K2 */
		.code		= KEY_F2,
		.desc		= "Button 2",
		.active_low	= 1,
	पूर्ण,
	अणु
		.gpio		= S3C2410_GPG(5),		/* K3 */
		.code		= KEY_F3,
		.desc		= "Button 3",
		.active_low	= 1,
	पूर्ण,
	अणु
		.gpio		= S3C2410_GPG(6),		/* K4 */
		.code		= KEY_POWER,
		.desc		= "Power",
		.active_low	= 1,
	पूर्ण,
	अणु
		.gpio		= S3C2410_GPG(7),		/* K5 */
		.code		= KEY_F5,
		.desc		= "Button 5",
		.active_low	= 1,
	पूर्ण,
#अगर 0
	/* this pin is also known as TCLK1 and seems to alपढ़ोy
	 * marked as "in use" somehow in the kernel -- possibly wrongly
	 */
	अणु
		.gpio		= S3C2410_GPG(11),	/* K6 */
		.code		= KEY_F6,
		.desc		= "Button 6",
		.active_low	= 1,
	पूर्ण,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा gpio_keys_platक्रमm_data mini2440_button_data = अणु
	.buttons	= mini2440_buttons,
	.nbuttons	= ARRAY_SIZE(mini2440_buttons),
पूर्ण;

अटल काष्ठा platक्रमm_device mini2440_button_device = अणु
	.name		= "gpio-keys",
	.id		= -1,
	.dev		= अणु
		.platक्रमm_data	= &mini2440_button_data,
	पूर्ण
पूर्ण;

/* LEDS */

अटल काष्ठा gpiod_lookup_table mini2440_led1_gpio_table = अणु
	.dev_id = "s3c24xx_led.1",
	.table = अणु
		GPIO_LOOKUP("GPB", 5, शून्य, GPIO_ACTIVE_LOW | GPIO_OPEN_DRAIN),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpiod_lookup_table mini2440_led2_gpio_table = अणु
	.dev_id = "s3c24xx_led.2",
	.table = अणु
		GPIO_LOOKUP("GPB", 6, शून्य, GPIO_ACTIVE_LOW | GPIO_OPEN_DRAIN),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpiod_lookup_table mini2440_led3_gpio_table = अणु
	.dev_id = "s3c24xx_led.3",
	.table = अणु
		GPIO_LOOKUP("GPB", 7, शून्य, GPIO_ACTIVE_LOW | GPIO_OPEN_DRAIN),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpiod_lookup_table mini2440_led4_gpio_table = अणु
	.dev_id = "s3c24xx_led.4",
	.table = अणु
		GPIO_LOOKUP("GPB", 8, शून्य, GPIO_ACTIVE_LOW | GPIO_OPEN_DRAIN),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpiod_lookup_table mini2440_backlight_gpio_table = अणु
	.dev_id = "s3c24xx_led.5",
	.table = अणु
		GPIO_LOOKUP("GPG", 4, शून्य, GPIO_ACTIVE_HIGH),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा s3c24xx_led_platdata mini2440_led1_pdata = अणु
	.name		= "led1",
	.def_trigger	= "heartbeat",
पूर्ण;

अटल काष्ठा s3c24xx_led_platdata mini2440_led2_pdata = अणु
	.name		= "led2",
	.def_trigger	= "nand-disk",
पूर्ण;

अटल काष्ठा s3c24xx_led_platdata mini2440_led3_pdata = अणु
	.name		= "led3",
	.def_trigger	= "mmc0",
पूर्ण;

अटल काष्ठा s3c24xx_led_platdata mini2440_led4_pdata = अणु
	.name		= "led4",
	.def_trigger	= "",
पूर्ण;

अटल काष्ठा s3c24xx_led_platdata mini2440_led_backlight_pdata = अणु
	.name		= "backlight",
	.def_trigger	= "backlight",
पूर्ण;

अटल काष्ठा platक्रमm_device mini2440_led1 = अणु
	.name		= "s3c24xx_led",
	.id		= 1,
	.dev		= अणु
		.platक्रमm_data	= &mini2440_led1_pdata,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device mini2440_led2 = अणु
	.name		= "s3c24xx_led",
	.id		= 2,
	.dev		= अणु
		.platक्रमm_data	= &mini2440_led2_pdata,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device mini2440_led3 = अणु
	.name		= "s3c24xx_led",
	.id		= 3,
	.dev		= अणु
		.platक्रमm_data	= &mini2440_led3_pdata,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device mini2440_led4 = अणु
	.name		= "s3c24xx_led",
	.id		= 4,
	.dev		= अणु
		.platक्रमm_data	= &mini2440_led4_pdata,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device mini2440_led_backlight = अणु
	.name		= "s3c24xx_led",
	.id		= 5,
	.dev		= अणु
		.platक्रमm_data	= &mini2440_led_backlight_pdata,
	पूर्ण,
पूर्ण;

/* AUDIO */

अटल काष्ठा s3c24xx_uda134x_platक्रमm_data mini2440_audio_pins = अणु
	.l3_clk = S3C2410_GPB(4),
	.l3_mode = S3C2410_GPB(2),
	.l3_data = S3C2410_GPB(3),
	.model = UDA134X_UDA1341
पूर्ण;

अटल काष्ठा platक्रमm_device mini2440_audio = अणु
	.name		= "s3c24xx_uda134x",
	.id		= 0,
	.dev		= अणु
		.platक्रमm_data	= &mini2440_audio_pins,
	पूर्ण,
पूर्ण;

/*
 * I2C devices
 */
अटल स्थिर काष्ठा property_entry mini2440_at24_properties[] = अणु
	PROPERTY_ENTRY_U32("pagesize", 16),
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा software_node mini2440_at24_node = अणु
	.properties = mini2440_at24_properties,
पूर्ण;

अटल काष्ठा i2c_board_info mini2440_i2c_devs[] __initdata = अणु
	अणु
		I2C_BOARD_INFO("24c08", 0x50),
		.swnode = &mini2440_at24_node,
	पूर्ण,
पूर्ण;

अटल काष्ठा uda134x_platक्रमm_data s3c24xx_uda134x = अणु
	.l3 = अणु
		.gpio_clk = S3C2410_GPB(4),
		.gpio_data = S3C2410_GPB(3),
		.gpio_mode = S3C2410_GPB(2),
		.use_gpios = 1,
		.data_hold = 1,
		.data_setup = 1,
		.घड़ी_high = 1,
		.mode_hold = 1,
		.mode = 1,
		.mode_setup = 1,
	पूर्ण,
	.model = UDA134X_UDA1341,
पूर्ण;

अटल काष्ठा platक्रमm_device uda1340_codec = अणु
		.name = "uda134x-codec",
		.id = -1,
		.dev = अणु
			.platक्रमm_data	= &s3c24xx_uda134x,
		पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device *mini2440_devices[] __initdata = अणु
	&s3c_device_ohci,
	&s3c_device_wdt,
	&s3c_device_i2c0,
	&s3c_device_rtc,
	&s3c_device_usbgadget,
	&mini2440_device_eth,
	&mini2440_led1,
	&mini2440_led2,
	&mini2440_led3,
	&mini2440_led4,
	&mini2440_button_device,
	&s3c_device_nand,
	&s3c_device_sdi,
	&s3c2440_device_dma,
	&s3c_device_iis,
	&uda1340_codec,
	&mini2440_audio,
पूर्ण;

अटल व्योम __init mini2440_map_io(व्योम)
अणु
	s3c24xx_init_io(mini2440_iodesc, ARRAY_SIZE(mini2440_iodesc));
	s3c24xx_init_uarts(mini2440_uartcfgs, ARRAY_SIZE(mini2440_uartcfgs));
	s3c24xx_set_समयr_source(S3C24XX_PWM3, S3C24XX_PWM4);
पूर्ण

अटल व्योम __init mini2440_init_समय(व्योम)
अणु
	s3c2440_init_घड़ीs(12000000);
	s3c24xx_समयr_init();
पूर्ण

/*
 * mini2440_features string
 *
 * t = Touchscreen present
 * b = backlight control
 * c = camera [TODO]
 * 0-9 LCD configuration
 *
 */
अटल अक्षर mini2440_features_str[12] __initdata = "0tb";

अटल पूर्णांक __init mini2440_features_setup(अक्षर *str)
अणु
	अगर (str)
		strlcpy(mini2440_features_str, str,
			माप(mini2440_features_str));
	वापस 1;
पूर्ण

__setup("mini2440=", mini2440_features_setup);

#घोषणा FEATURE_SCREEN (1 << 0)
#घोषणा FEATURE_BACKLIGHT (1 << 1)
#घोषणा FEATURE_TOUCH (1 << 2)
#घोषणा FEATURE_CAMERA (1 << 3)

काष्ठा mini2440_features_t अणु
	पूर्णांक count;
	पूर्णांक करोne;
	पूर्णांक lcd_index;
	काष्ठा platक्रमm_device *optional[8];
पूर्ण;

अटल व्योम __init mini2440_parse_features(
		काष्ठा mini2440_features_t *features,
		स्थिर अक्षर *features_str)
अणु
	स्थिर अक्षर *fp = features_str;

	features->count = 0;
	features->करोne = 0;
	features->lcd_index = -1;

	जबतक (*fp) अणु
		अक्षर f = *fp++;

		चयन (f) अणु
		हाल '0'...'9':	/* tft screen */
			अगर (features->करोne & FEATURE_SCREEN) अणु
				pr_info("MINI2440: '%c' ignored, screen type already set\n",
					f);
			पूर्ण अन्यथा अणु
				पूर्णांक li = f - '0';

				अगर (li >= ARRAY_SIZE(mini2440_lcd_cfg))
					pr_info("MINI2440: '%c' out of range LCD mode\n",
						f);
				अन्यथा अणु
					features->optional[features->count++] =
							&s3c_device_lcd;
					features->lcd_index = li;
				पूर्ण
			पूर्ण
			features->करोne |= FEATURE_SCREEN;
			अवरोध;
		हाल 'b':
			अगर (features->करोne & FEATURE_BACKLIGHT)
				pr_info("MINI2440: '%c' ignored, backlight already set\n",
					f);
			अन्यथा अणु
				features->optional[features->count++] =
						&mini2440_led_backlight;
			पूर्ण
			features->करोne |= FEATURE_BACKLIGHT;
			अवरोध;
		हाल 't':
			pr_info("MINI2440: '%c' ignored, touchscreen not compiled in\n",
				f);
			अवरोध;
		हाल 'c':
			अगर (features->करोne & FEATURE_CAMERA)
				pr_info("MINI2440: '%c' ignored, camera already registered\n",
					f);
			अन्यथा
				features->optional[features->count++] =
					&s3c_device_camअगर;
			features->करोne |= FEATURE_CAMERA;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम __init mini2440_init(व्योम)
अणु
	काष्ठा mini2440_features_t features = अणु 0 पूर्ण;
	पूर्णांक i;

	pr_info("MINI2440: Option string mini2440=%s\n",
			mini2440_features_str);

	/* Parse the feature string */
	mini2440_parse_features(&features, mini2440_features_str);

	/* turn LCD on */
	s3c_gpio_cfgpin(S3C2410_GPC(0), S3C2410_GPC0_LEND);

	/* Turn the backlight early on */
	WARN_ON(gpio_request_one(S3C2410_GPG(4), GPIOF_OUT_INIT_HIGH, शून्य));
	gpio_मुक्त(S3C2410_GPG(4));

	/* हटाओ pullup on optional PWM backlight -- unused on 3.5 and 7"s */
	gpio_request_one(S3C2410_GPB(1), GPIOF_IN, शून्य);
	s3c_gpio_setpull(S3C2410_GPB(1), S3C_GPIO_PULL_UP);
	gpio_मुक्त(S3C2410_GPB(1));

	/* mark the key as input, without pullups (there is one on the board) */
	क्रम (i = 0; i < ARRAY_SIZE(mini2440_buttons); i++) अणु
		s3c_gpio_setpull(mini2440_buttons[i].gpio, S3C_GPIO_PULL_UP);
		s3c_gpio_cfgpin(mini2440_buttons[i].gpio, S3C2410_GPIO_INPUT);
	पूर्ण

	/* Configure the I2S pins (GPE0...GPE4) in correct mode */
	s3c_gpio_cfgall_range(S3C2410_GPE(0), 5, S3C_GPIO_SFN(2),
			      S3C_GPIO_PULL_NONE);

	अगर (features.lcd_index != -1) अणु
		पूर्णांक li;

		mini2440_fb_info.displays =
			&mini2440_lcd_cfg[features.lcd_index];

		pr_info("MINI2440: LCD");
		क्रम (li = 0; li < ARRAY_SIZE(mini2440_lcd_cfg); li++)
			अगर (li == features.lcd_index)
				pr_cont(" [%d:%dx%d]", li,
					mini2440_lcd_cfg[li].width,
					mini2440_lcd_cfg[li].height);
			अन्यथा
				pr_cont(" %d:%dx%d", li,
					mini2440_lcd_cfg[li].width,
					mini2440_lcd_cfg[li].height);
		pr_cont("\n");
		s3c24xx_fb_set_platdata(&mini2440_fb_info);
	पूर्ण

	s3c24xx_udc_set_platdata(&mini2440_udc_cfg);
	gpiod_add_lookup_table(&mini2440_mmc_gpio_table);
	s3c24xx_mci_set_platdata(&mini2440_mmc_cfg);
	s3c_nand_set_platdata(&mini2440_nand_info);
	s3c_i2c0_set_platdata(शून्य);

	i2c_रेजिस्टर_board_info(0, mini2440_i2c_devs,
				ARRAY_SIZE(mini2440_i2c_devs));

	/* Disable pull-up on the LED lines */
	s3c_gpio_setpull(S3C2410_GPB(5), S3C_GPIO_PULL_NONE);
	s3c_gpio_setpull(S3C2410_GPB(6), S3C_GPIO_PULL_NONE);
	s3c_gpio_setpull(S3C2410_GPB(7), S3C_GPIO_PULL_NONE);
	s3c_gpio_setpull(S3C2410_GPB(8), S3C_GPIO_PULL_NONE);
	s3c_gpio_setpull(S3C2410_GPG(4), S3C_GPIO_PULL_NONE);

	/* Add lookups क्रम the lines */
	gpiod_add_lookup_table(&mini2440_led1_gpio_table);
	gpiod_add_lookup_table(&mini2440_led2_gpio_table);
	gpiod_add_lookup_table(&mini2440_led3_gpio_table);
	gpiod_add_lookup_table(&mini2440_led4_gpio_table);
	gpiod_add_lookup_table(&mini2440_backlight_gpio_table);

	platक्रमm_add_devices(mini2440_devices, ARRAY_SIZE(mini2440_devices));

	अगर (features.count)	/* the optional features */
		platक्रमm_add_devices(features.optional, features.count);

पूर्ण


MACHINE_START(MINI2440, "MINI2440")
	/* Maपूर्णांकainer: Michel Pollet <buserror@gmail.com> */
	.atag_offset	= 0x100,
	.map_io		= mini2440_map_io,
	.init_machine	= mini2440_init,
	.init_irq	= s3c2440_init_irq,
	.init_समय	= mini2440_init_समय,
MACHINE_END
