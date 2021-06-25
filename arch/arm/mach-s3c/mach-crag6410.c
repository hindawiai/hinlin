<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright 2011 Wolfson Microelectronics plc
//	Mark Brown <broonie@खोलोsource.wolfsonmicro.com>
//
// Copyright 2011 Simtec Electronics
//	Ben Dooks <ben@simtec.co.uk>

#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/serial_s3c.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/fb.h>
#समावेश <linux/पन.स>
#समावेश <linux/init.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/leds.h>
#समावेश <linux/delay.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/regulator/fixed.h>
#समावेश <linux/pwm.h>
#समावेश <linux/pwm_backlight.h>
#समावेश <linux/dm9000.h>
#समावेश <linux/gpio_keys.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/spi/spi.h>

#समावेश <linux/platक्रमm_data/pca953x.h>
#समावेश <linux/platक्रमm_data/s3c-hsotg.h>

#समावेश <video/platक्रमm_lcd.h>

#समावेश <linux/mfd/wm831x/core.h>
#समावेश <linux/mfd/wm831x/pdata.h>
#समावेश <linux/mfd/wm831x/irq.h>
#समावेश <linux/mfd/wm831x/gpपन.स>

#समावेश <sound/wm1250-ev1.h>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach-types.h>

#समावेश <video/samsung_fimd.h>
#समावेश "map.h"
#समावेश "regs-gpio.h"
#समावेश "gpio-samsung.h"
#समावेश <mach/irqs.h>

#समावेश "fb.h"
#समावेश "sdhci.h"
#समावेश "gpio-cfg.h"
#समावेश <linux/platक्रमm_data/spi-s3c64xx.h>

#समावेश "keypad.h"
#समावेश "devs.h"
#समावेश "cpu.h"
#समावेश <linux/soc/samsung/s3c-adc.h>
#समावेश <linux/platक्रमm_data/i2c-s3c2410.h>
#समावेश "pm.h"

#समावेश "s3c64xx.h"
#समावेश "crag6410.h"
#समावेश "regs-gpio-memport-s3c64xx.h"
#समावेश "regs-modem-s3c64xx.h"
#समावेश "regs-sys-s3c64xx.h"

/* serial port setup */

#घोषणा UCON (S3C2410_UCON_DEFAULT | S3C2410_UCON_UCLK)
#घोषणा ULCON (S3C2410_LCON_CS8 | S3C2410_LCON_PNONE | S3C2410_LCON_STOPB)
#घोषणा UFCON (S3C2410_UFCON_RXTRIG8 | S3C2410_UFCON_FIFOMODE)

अटल काष्ठा s3c2410_uartcfg crag6410_uartcfgs[] __initdata = अणु
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
	[3] = अणु
		.hwport		= 3,
		.flags		= 0,
		.ucon		= UCON,
		.ulcon		= ULCON,
		.ufcon		= UFCON,
	पूर्ण,
पूर्ण;

अटल काष्ठा pwm_lookup crag6410_pwm_lookup[] = अणु
	PWM_LOOKUP("samsung-pwm", 0, "pwm-backlight", शून्य, 100000,
		   PWM_POLARITY_NORMAL),
पूर्ण;

अटल काष्ठा platक्रमm_pwm_backlight_data crag6410_backlight_data = अणु
	.max_brightness	= 1000,
	.dft_brightness	= 600,
पूर्ण;

अटल काष्ठा platक्रमm_device crag6410_backlight_device = अणु
	.name		= "pwm-backlight",
	.id		= -1,
	.dev		= अणु
		.parent	= &samsung_device_pwm.dev,
		.platक्रमm_data = &crag6410_backlight_data,
	पूर्ण,
पूर्ण;

अटल व्योम crag6410_lcd_घातer_set(काष्ठा plat_lcd_data *pd, अचिन्हित पूर्णांक घातer)
अणु
	pr_debug("%s: setting power %d\n", __func__, घातer);

	अगर (घातer) अणु
		gpio_set_value(S3C64XX_GPB(0), 1);
		msleep(1);
		s3c_gpio_cfgpin(S3C64XX_GPF(14), S3C_GPIO_SFN(2));
	पूर्ण अन्यथा अणु
		gpio_direction_output(S3C64XX_GPF(14), 0);
		gpio_set_value(S3C64XX_GPB(0), 0);
	पूर्ण
पूर्ण

अटल काष्ठा platक्रमm_device crag6410_lcd_घातerdev = अणु
	.name			= "platform-lcd",
	.id			= -1,
	.dev.parent		= &s3c_device_fb.dev,
	.dev.platक्रमm_data	= &(काष्ठा plat_lcd_data) अणु
		.set_घातer	= crag6410_lcd_घातer_set,
	पूर्ण,
पूर्ण;

/* 640x480 URT */
अटल काष्ठा s3c_fb_pd_win crag6410_fb_win0 = अणु
	.max_bpp	= 32,
	.शेष_bpp	= 16,
	.xres		= 640,
	.yres		= 480,
	.भव_y	= 480 * 2,
	.भव_x	= 640,
पूर्ण;

अटल काष्ठा fb_videomode crag6410_lcd_timing = अणु
	.left_margin	= 150,
	.right_margin	= 80,
	.upper_margin	= 40,
	.lower_margin	= 5,
	.hsync_len	= 40,
	.vsync_len	= 5,
	.xres		= 640,
	.yres		= 480,
पूर्ण;

/* 405566 घड़ीs per frame => 60Hz refresh requires 24333960Hz घड़ी */
अटल काष्ठा s3c_fb_platdata crag6410_lcd_pdata = अणु
	.setup_gpio	= s3c64xx_fb_gpio_setup_24bpp,
	.vtiming	= &crag6410_lcd_timing,
	.win[0]		= &crag6410_fb_win0,
	.vidcon0	= VIDCON0_VIDOUT_RGB | VIDCON0_PNRMODE_RGB,
	.vidcon1	= VIDCON1_INV_HSYNC | VIDCON1_INV_VSYNC,
पूर्ण;

/* 2x6 keypad */

अटल uपूर्णांक32_t crag6410_keymap[] = अणु
	/* KEY(row, col, keycode) */
	KEY(0, 0, KEY_VOLUMEUP),
	KEY(0, 1, KEY_HOME),
	KEY(0, 2, KEY_VOLUMEDOWN),
	KEY(0, 3, KEY_HELP),
	KEY(0, 4, KEY_MENU),
	KEY(0, 5, KEY_MEDIA),
	KEY(1, 0, 232),
	KEY(1, 1, KEY_DOWN),
	KEY(1, 2, KEY_LEFT),
	KEY(1, 3, KEY_UP),
	KEY(1, 4, KEY_RIGHT),
	KEY(1, 5, KEY_CAMERA),
पूर्ण;

अटल काष्ठा matrix_keymap_data crag6410_keymap_data = अणु
	.keymap		= crag6410_keymap,
	.keymap_size	= ARRAY_SIZE(crag6410_keymap),
पूर्ण;

अटल काष्ठा samsung_keypad_platdata crag6410_keypad_data = अणु
	.keymap_data	= &crag6410_keymap_data,
	.rows		= 2,
	.cols		= 6,
पूर्ण;

अटल काष्ठा gpio_keys_button crag6410_gpio_keys[] = अणु
	[0] = अणु
		.code	= KEY_SUSPEND,
		.gpio	= S3C64XX_GPL(10),	/* EINT 18 */
		.type	= EV_KEY,
		.wakeup	= 1,
		.active_low = 1,
	पूर्ण,
	[1] = अणु
		.code	= SW_FRONT_PROXIMITY,
		.gpio	= S3C64XX_GPN(11),	/* EINT 11 */
		.type	= EV_SW,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_keys_platक्रमm_data crag6410_gpio_keydata = अणु
	.buttons	= crag6410_gpio_keys,
	.nbuttons	= ARRAY_SIZE(crag6410_gpio_keys),
पूर्ण;

अटल काष्ठा platक्रमm_device crag6410_gpio_keydev = अणु
	.name		= "gpio-keys",
	.id		= 0,
	.dev.platक्रमm_data = &crag6410_gpio_keydata,
पूर्ण;

अटल काष्ठा resource crag6410_dm9k_resource[] = अणु
	[0] = DEFINE_RES_MEM(S3C64XX_PA_XM0CSN5, 2),
	[1] = DEFINE_RES_MEM(S3C64XX_PA_XM0CSN5 + (1 << 8), 2),
	[2] = DEFINE_RES_NAMED(S3C_EINT(17), 1, शून्य, IORESOURCE_IRQ \
				| IORESOURCE_IRQ_HIGHLEVEL),
पूर्ण;

अटल काष्ठा dm9000_plat_data mini6410_dm9k_pdata = अणु
	.flags	= DM9000_PLATF_16BITONLY,
पूर्ण;

अटल काष्ठा platक्रमm_device crag6410_dm9k_device = अणु
	.name		= "dm9000",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(crag6410_dm9k_resource),
	.resource	= crag6410_dm9k_resource,
	.dev.platक्रमm_data = &mini6410_dm9k_pdata,
पूर्ण;

अटल काष्ठा resource crag6410_mmgpio_resource[] = अणु
	[0] = DEFINE_RES_MEM_NAMED(S3C64XX_PA_XM0CSN4, 1, "dat"),
पूर्ण;

अटल काष्ठा platक्रमm_device crag6410_mmgpio = अणु
	.name		= "basic-mmio-gpio",
	.id		= -1,
	.resource	= crag6410_mmgpio_resource,
	.num_resources	= ARRAY_SIZE(crag6410_mmgpio_resource),
	.dev.platक्रमm_data = &(काष्ठा bgpio_pdata) अणु
		.base	= MMGPIO_GPIO_BASE,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device speyside_device = अणु
	.name		= "speyside",
	.id		= -1,
पूर्ण;

अटल काष्ठा platक्रमm_device lowland_device = अणु
	.name		= "lowland",
	.id		= -1,
पूर्ण;

अटल काष्ठा platक्रमm_device tobermory_device = अणु
	.name		= "tobermory",
	.id		= -1,
पूर्ण;

अटल काष्ठा platक्रमm_device littlemill_device = अणु
	.name		= "littlemill",
	.id		= -1,
पूर्ण;

अटल काष्ठा platक्रमm_device bells_wm2200_device = अणु
	.name		= "bells",
	.id		= 0,
पूर्ण;

अटल काष्ठा platक्रमm_device bells_wm5102_device = अणु
	.name		= "bells",
	.id		= 1,
पूर्ण;

अटल काष्ठा platक्रमm_device bells_wm5110_device = अणु
	.name		= "bells",
	.id		= 2,
पूर्ण;

अटल काष्ठा regulator_consumer_supply wallvdd_consumers[] = अणु
	REGULATOR_SUPPLY("SPKVDD", "1-001a"),
	REGULATOR_SUPPLY("SPKVDD1", "1-001a"),
	REGULATOR_SUPPLY("SPKVDD2", "1-001a"),
	REGULATOR_SUPPLY("SPKVDDL", "1-001a"),
	REGULATOR_SUPPLY("SPKVDDR", "1-001a"),

	REGULATOR_SUPPLY("SPKVDDL", "spi0.1"),
	REGULATOR_SUPPLY("SPKVDDR", "spi0.1"),

	REGULATOR_SUPPLY("DC1VDD", "0-0034"),
	REGULATOR_SUPPLY("DC2VDD", "0-0034"),
	REGULATOR_SUPPLY("DC3VDD", "0-0034"),
	REGULATOR_SUPPLY("LDO1VDD", "0-0034"),
	REGULATOR_SUPPLY("LDO2VDD", "0-0034"),
	REGULATOR_SUPPLY("LDO4VDD", "0-0034"),
	REGULATOR_SUPPLY("LDO5VDD", "0-0034"),
	REGULATOR_SUPPLY("LDO6VDD", "0-0034"),
	REGULATOR_SUPPLY("LDO7VDD", "0-0034"),
	REGULATOR_SUPPLY("LDO8VDD", "0-0034"),
	REGULATOR_SUPPLY("LDO9VDD", "0-0034"),
	REGULATOR_SUPPLY("LDO10VDD", "0-0034"),
	REGULATOR_SUPPLY("LDO11VDD", "0-0034"),

	REGULATOR_SUPPLY("DC1VDD", "1-0034"),
	REGULATOR_SUPPLY("DC2VDD", "1-0034"),
	REGULATOR_SUPPLY("DC3VDD", "1-0034"),
	REGULATOR_SUPPLY("LDO1VDD", "1-0034"),
	REGULATOR_SUPPLY("LDO2VDD", "1-0034"),
	REGULATOR_SUPPLY("LDO4VDD", "1-0034"),
	REGULATOR_SUPPLY("LDO5VDD", "1-0034"),
	REGULATOR_SUPPLY("LDO6VDD", "1-0034"),
	REGULATOR_SUPPLY("LDO7VDD", "1-0034"),
	REGULATOR_SUPPLY("LDO8VDD", "1-0034"),
	REGULATOR_SUPPLY("LDO9VDD", "1-0034"),
	REGULATOR_SUPPLY("LDO10VDD", "1-0034"),
	REGULATOR_SUPPLY("LDO11VDD", "1-0034"),
पूर्ण;

अटल काष्ठा regulator_init_data wallvdd_data = अणु
	.स्थिरraपूर्णांकs = अणु
		.always_on = 1,
	पूर्ण,
	.num_consumer_supplies = ARRAY_SIZE(wallvdd_consumers),
	.consumer_supplies = wallvdd_consumers,
पूर्ण;

अटल काष्ठा fixed_voltage_config wallvdd_pdata = अणु
	.supply_name = "WALLVDD",
	.microvolts = 5000000,
	.init_data = &wallvdd_data,
पूर्ण;

अटल काष्ठा platक्रमm_device wallvdd_device = अणु
	.name		= "reg-fixed-voltage",
	.id		= -1,
	.dev = अणु
		.platक्रमm_data = &wallvdd_pdata,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device *crag6410_devices[] __initdata = अणु
	&s3c_device_hsmmc0,
	&s3c_device_hsmmc2,
	&s3c_device_i2c0,
	&s3c_device_i2c1,
	&s3c_device_fb,
	&s3c_device_ohci,
	&s3c_device_usb_hsotg,
	&samsung_device_pwm,
	&s3c64xx_device_iis0,
	&s3c64xx_device_iis1,
	&samsung_device_keypad,
	&crag6410_gpio_keydev,
	&crag6410_dm9k_device,
	&s3c64xx_device_spi0,
	&crag6410_mmgpio,
	&crag6410_lcd_घातerdev,
	&crag6410_backlight_device,
	&speyside_device,
	&tobermory_device,
	&littlemill_device,
	&lowland_device,
	&bells_wm2200_device,
	&bells_wm5102_device,
	&bells_wm5110_device,
	&wallvdd_device,
पूर्ण;

अटल काष्ठा pca953x_platक्रमm_data crag6410_pca_data = अणु
	.gpio_base	= PCA935X_GPIO_BASE,
	.irq_base	= -1,
पूर्ण;

/* VDDARM is controlled by DVS1 connected to GPK(0) */
अटल काष्ठा wm831x_buckv_pdata vddarm_pdata = अणु
	.dvs_control_src = 1,
पूर्ण;

अटल काष्ठा regulator_consumer_supply vddarm_consumers[] = अणु
	REGULATOR_SUPPLY("vddarm", शून्य),
पूर्ण;

अटल काष्ठा regulator_init_data vddarm = अणु
	.स्थिरraपूर्णांकs = अणु
		.name = "VDDARM",
		.min_uV = 1000000,
		.max_uV = 1300000,
		.always_on = 1,
		.valid_ops_mask = REGULATOR_CHANGE_VOLTAGE,
	पूर्ण,
	.num_consumer_supplies = ARRAY_SIZE(vddarm_consumers),
	.consumer_supplies = vddarm_consumers,
	.supply_regulator = "WALLVDD",
	.driver_data = &vddarm_pdata,
पूर्ण;

अटल काष्ठा regulator_consumer_supply vddपूर्णांक_consumers[] = अणु
	REGULATOR_SUPPLY("vddint", शून्य),
पूर्ण;

अटल काष्ठा regulator_init_data vddपूर्णांक = अणु
	.स्थिरraपूर्णांकs = अणु
		.name = "VDDINT",
		.min_uV = 1000000,
		.max_uV = 1200000,
		.always_on = 1,
		.valid_ops_mask = REGULATOR_CHANGE_VOLTAGE,
	पूर्ण,
	.num_consumer_supplies = ARRAY_SIZE(vddपूर्णांक_consumers),
	.consumer_supplies = vddपूर्णांक_consumers,
	.supply_regulator = "WALLVDD",
पूर्ण;

अटल काष्ठा regulator_init_data vddmem = अणु
	.स्थिरraपूर्णांकs = अणु
		.name = "VDDMEM",
		.always_on = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा regulator_init_data vddsys = अणु
	.स्थिरraपूर्णांकs = अणु
		.name = "VDDSYS,VDDEXT,VDDPCM,VDDSS",
		.always_on = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा regulator_consumer_supply vddmmc_consumers[] = अणु
	REGULATOR_SUPPLY("vmmc", "s3c-sdhci.0"),
	REGULATOR_SUPPLY("vmmc", "s3c-sdhci.1"),
	REGULATOR_SUPPLY("vmmc", "s3c-sdhci.2"),
पूर्ण;

अटल काष्ठा regulator_init_data vddmmc = अणु
	.स्थिरraपूर्णांकs = अणु
		.name = "VDDMMC,UH",
		.always_on = 1,
	पूर्ण,
	.num_consumer_supplies = ARRAY_SIZE(vddmmc_consumers),
	.consumer_supplies = vddmmc_consumers,
	.supply_regulator = "WALLVDD",
पूर्ण;

अटल काष्ठा regulator_init_data vdकरोtgi = अणु
	.स्थिरraपूर्णांकs = अणु
		.name = "VDDOTGi",
		.always_on = 1,
	पूर्ण,
	.supply_regulator = "WALLVDD",
पूर्ण;

अटल काष्ठा regulator_init_data vdकरोtg = अणु
	.स्थिरraपूर्णांकs = अणु
		.name = "VDDOTG",
		.always_on = 1,
	पूर्ण,
	.supply_regulator = "WALLVDD",
पूर्ण;

अटल काष्ठा regulator_init_data vddhi = अणु
	.स्थिरraपूर्णांकs = अणु
		.name = "VDDHI",
		.always_on = 1,
	पूर्ण,
	.supply_regulator = "WALLVDD",
पूर्ण;

अटल काष्ठा regulator_init_data vddadc = अणु
	.स्थिरraपूर्णांकs = अणु
		.name = "VDDADC,VDDDAC",
		.always_on = 1,
	पूर्ण,
	.supply_regulator = "WALLVDD",
पूर्ण;

अटल काष्ठा regulator_init_data vddmem0 = अणु
	.स्थिरraपूर्णांकs = अणु
		.name = "VDDMEM0",
		.always_on = 1,
	पूर्ण,
	.supply_regulator = "WALLVDD",
पूर्ण;

अटल काष्ठा regulator_init_data vddpll = अणु
	.स्थिरraपूर्णांकs = अणु
		.name = "VDDPLL",
		.always_on = 1,
	पूर्ण,
	.supply_regulator = "WALLVDD",
पूर्ण;

अटल काष्ठा regulator_init_data vddlcd = अणु
	.स्थिरraपूर्णांकs = अणु
		.name = "VDDLCD",
		.always_on = 1,
	पूर्ण,
	.supply_regulator = "WALLVDD",
पूर्ण;

अटल काष्ठा regulator_init_data vddalive = अणु
	.स्थिरraपूर्णांकs = अणु
		.name = "VDDALIVE",
		.always_on = 1,
	पूर्ण,
	.supply_regulator = "WALLVDD",
पूर्ण;

अटल काष्ठा wm831x_backup_pdata banff_backup_pdata = अणु
	.अक्षरger_enable = 1,
	.vlim = 2500,  /* mV */
	.ilim = 200,   /* uA */
पूर्ण;

अटल काष्ठा wm831x_status_pdata banff_red_led = अणु
	.name = "banff:red:",
	.शेष_src = WM831X_STATUS_MANUAL,
पूर्ण;

अटल काष्ठा wm831x_status_pdata banff_green_led = अणु
	.name = "banff:green:",
	.शेष_src = WM831X_STATUS_MANUAL,
पूर्ण;

अटल काष्ठा wm831x_touch_pdata touch_pdata = अणु
	.data_irq = S3C_EINT(26),
	.pd_irq = S3C_EINT(27),
पूर्ण;

अटल काष्ठा wm831x_pdata crag_pmic_pdata = अणु
	.wm831x_num = 1,
	.irq_base = BANFF_PMIC_IRQ_BASE,
	.gpio_base = BANFF_PMIC_GPIO_BASE,
	.soft_shutकरोwn = true,

	.backup = &banff_backup_pdata,

	.gpio_शेषs = अणु
		/* GPIO5: DVS1_REQ - CMOS, DBVDD, active high */
		[4] = WM831X_GPN_सूची | WM831X_GPN_POL | WM831X_GPN_ENA | 0x8,
		/* GPIO11: Touchscreen data - CMOS, DBVDD, active high*/
		[10] = WM831X_GPN_POL | WM831X_GPN_ENA | 0x6,
		/* GPIO12: Touchscreen pen करोwn - CMOS, DBVDD, active high*/
		[11] = WM831X_GPN_POL | WM831X_GPN_ENA | 0x7,
	पूर्ण,

	.dcdc = अणु
		&vddarm,  /* DCDC1 */
		&vddपूर्णांक,  /* DCDC2 */
		&vddmem,  /* DCDC3 */
	पूर्ण,

	.lकरो = अणु
		&vddsys,   /* LDO1 */
		&vddmmc,   /* LDO2 */
		शून्य,      /* LDO3 */
		&vdकरोtgi,  /* LDO4 */
		&vdकरोtg,   /* LDO5 */
		&vddhi,    /* LDO6 */
		&vddadc,   /* LDO7 */
		&vddmem0,  /* LDO8 */
		&vddpll,   /* LDO9 */
		&vddlcd,   /* LDO10 */
		&vddalive, /* LDO11 */
	पूर्ण,

	.status = अणु
		&banff_green_led,
		&banff_red_led,
	पूर्ण,

	.touch = &touch_pdata,
पूर्ण;

/*
 * VDDARM is eventually ending up as a regulator hanging on the MFD cell device
 * "wm831x-buckv.1" spawn from drivers/mfd/wm831x-core.c.
 *
 * From the note on the platक्रमm data we can see that this is clearly DVS1
 * and asचिन्हित as dcdc1 resource to the MFD core which sets .id of the cell
 * spawning the DVS1 platक्रमm device to 1, then the cell platक्रमm device
 * name is calculated from 10*instance + id resulting in the device name
 * "wm831x-buckv.11"
 */
अटल काष्ठा gpiod_lookup_table crag_pmic_gpiod_table = अणु
	.dev_id = "wm831x-buckv.11",
	.table = अणु
		GPIO_LOOKUP("GPIOK", 0, "dvs", GPIO_ACTIVE_HIGH),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा i2c_board_info i2c_devs0[] = अणु
	अणु I2C_BOARD_INFO("24c08", 0x50), पूर्ण,
	अणु I2C_BOARD_INFO("tca6408", 0x20),
	  .platक्रमm_data = &crag6410_pca_data,
	पूर्ण,
	अणु I2C_BOARD_INFO("wm8312", 0x34),
	  .platक्रमm_data = &crag_pmic_pdata,
	  .irq = S3C_EINT(23),
	पूर्ण,
पूर्ण;

अटल काष्ठा s3c2410_platक्रमm_i2c i2c0_pdata = अणु
	.frequency = 400000,
पूर्ण;

अटल काष्ठा regulator_consumer_supply pvdd_1v2_consumers[] = अणु
	REGULATOR_SUPPLY("DCVDD", "spi0.0"),
	REGULATOR_SUPPLY("AVDD", "spi0.0"),
	REGULATOR_SUPPLY("AVDD", "spi0.1"),
पूर्ण;

अटल काष्ठा regulator_init_data pvdd_1v2 = अणु
	.स्थिरraपूर्णांकs = अणु
		.name = "PVDD_1V2",
		.valid_ops_mask = REGULATOR_CHANGE_STATUS,
	पूर्ण,

	.consumer_supplies = pvdd_1v2_consumers,
	.num_consumer_supplies = ARRAY_SIZE(pvdd_1v2_consumers),
पूर्ण;

अटल काष्ठा regulator_consumer_supply pvdd_1v8_consumers[] = अणु
	REGULATOR_SUPPLY("LDOVDD", "1-001a"),
	REGULATOR_SUPPLY("PLLVDD", "1-001a"),
	REGULATOR_SUPPLY("DBVDD", "1-001a"),
	REGULATOR_SUPPLY("DBVDD1", "1-001a"),
	REGULATOR_SUPPLY("DBVDD2", "1-001a"),
	REGULATOR_SUPPLY("DBVDD3", "1-001a"),
	REGULATOR_SUPPLY("CPVDD", "1-001a"),
	REGULATOR_SUPPLY("AVDD2", "1-001a"),
	REGULATOR_SUPPLY("DCVDD", "1-001a"),
	REGULATOR_SUPPLY("AVDD", "1-001a"),
	REGULATOR_SUPPLY("DBVDD", "spi0.0"),

	REGULATOR_SUPPLY("DBVDD", "1-003a"),
	REGULATOR_SUPPLY("LDOVDD", "1-003a"),
	REGULATOR_SUPPLY("CPVDD", "1-003a"),
	REGULATOR_SUPPLY("AVDD", "1-003a"),
	REGULATOR_SUPPLY("DBVDD1", "spi0.1"),
	REGULATOR_SUPPLY("DBVDD2", "spi0.1"),
	REGULATOR_SUPPLY("DBVDD3", "spi0.1"),
	REGULATOR_SUPPLY("LDOVDD", "spi0.1"),
	REGULATOR_SUPPLY("CPVDD", "spi0.1"),
पूर्ण;

अटल काष्ठा regulator_init_data pvdd_1v8 = अणु
	.स्थिरraपूर्णांकs = अणु
		.name = "PVDD_1V8",
		.always_on = 1,
	पूर्ण,

	.consumer_supplies = pvdd_1v8_consumers,
	.num_consumer_supplies = ARRAY_SIZE(pvdd_1v8_consumers),
पूर्ण;

अटल काष्ठा regulator_consumer_supply pvdd_3v3_consumers[] = अणु
	REGULATOR_SUPPLY("MICVDD", "1-001a"),
	REGULATOR_SUPPLY("AVDD1", "1-001a"),
पूर्ण;

अटल काष्ठा regulator_init_data pvdd_3v3 = अणु
	.स्थिरraपूर्णांकs = अणु
		.name = "PVDD_3V3",
		.always_on = 1,
	पूर्ण,

	.consumer_supplies = pvdd_3v3_consumers,
	.num_consumer_supplies = ARRAY_SIZE(pvdd_3v3_consumers),
पूर्ण;

अटल काष्ठा wm831x_pdata glenfarclas_pmic_pdata = अणु
	.wm831x_num = 2,
	.irq_base = GLENFARCLAS_PMIC_IRQ_BASE,
	.gpio_base = GLENFARCLAS_PMIC_GPIO_BASE,
	.soft_shutकरोwn = true,

	.gpio_शेषs = अणु
		/* GPIO1-3: IRQ inमाला_दो, rising edge triggered, CMOS */
		[0] = WM831X_GPN_सूची | WM831X_GPN_POL | WM831X_GPN_ENA,
		[1] = WM831X_GPN_सूची | WM831X_GPN_POL | WM831X_GPN_ENA,
		[2] = WM831X_GPN_सूची | WM831X_GPN_POL | WM831X_GPN_ENA,
	पूर्ण,

	.dcdc = अणु
		&pvdd_1v2,  /* DCDC1 */
		&pvdd_1v8,  /* DCDC2 */
		&pvdd_3v3,  /* DCDC3 */
	पूर्ण,

	.disable_touch = true,
पूर्ण;

अटल काष्ठा wm1250_ev1_pdata wm1250_ev1_pdata = अणु
	.gpios = अणु
		[WM1250_EV1_GPIO_CLK_ENA] = S3C64XX_GPN(12),
		[WM1250_EV1_GPIO_CLK_SEL0] = S3C64XX_GPL(12),
		[WM1250_EV1_GPIO_CLK_SEL1] = S3C64XX_GPL(13),
		[WM1250_EV1_GPIO_OSR] = S3C64XX_GPL(14),
		[WM1250_EV1_GPIO_MASTER] = S3C64XX_GPL(8),
	पूर्ण,
पूर्ण;

अटल काष्ठा i2c_board_info i2c_devs1[] = अणु
	अणु I2C_BOARD_INFO("wm8311", 0x34),
	  .irq = S3C_EINT(0),
	  .platक्रमm_data = &glenfarclas_pmic_pdata पूर्ण,

	अणु I2C_BOARD_INFO("wlf-gf-module", 0x20) पूर्ण,
	अणु I2C_BOARD_INFO("wlf-gf-module", 0x22) पूर्ण,
	अणु I2C_BOARD_INFO("wlf-gf-module", 0x24) पूर्ण,
	अणु I2C_BOARD_INFO("wlf-gf-module", 0x25) पूर्ण,
	अणु I2C_BOARD_INFO("wlf-gf-module", 0x26) पूर्ण,

	अणु I2C_BOARD_INFO("wm1250-ev1", 0x27),
	  .platक्रमm_data = &wm1250_ev1_pdata पूर्ण,
पूर्ण;

अटल काष्ठा s3c2410_platक्रमm_i2c i2c1_pdata = अणु
	.frequency = 400000,
	.bus_num = 1,
पूर्ण;

अटल व्योम __init crag6410_map_io(व्योम)
अणु
	s3c64xx_init_io(शून्य, 0);
	s3c64xx_set_xtal_freq(12000000);
	s3c24xx_init_uarts(crag6410_uartcfgs, ARRAY_SIZE(crag6410_uartcfgs));
	s3c64xx_set_समयr_source(S3C64XX_PWM3, S3C64XX_PWM4);

	/* LCD type and Bypass set by bootloader */
पूर्ण

अटल काष्ठा s3c_sdhci_platdata crag6410_hsmmc2_pdata = अणु
	.max_width		= 4,
	.cd_type		= S3C_SDHCI_CD_PERMANENT,
	.host_caps		= MMC_CAP_POWER_OFF_CARD,
पूर्ण;

अटल व्योम crag6410_cfg_sdhci0(काष्ठा platक्रमm_device *dev, पूर्णांक width)
अणु
	/* Set all the necessary GPG pins to special-function 2 */
	s3c_gpio_cfgrange_nopull(S3C64XX_GPG(0), 2 + width, S3C_GPIO_SFN(2));

	/* क्रमce card-detected क्रम prototype 0 */
	s3c_gpio_setpull(S3C64XX_GPG(6), S3C_GPIO_PULL_DOWN);
पूर्ण

अटल काष्ठा s3c_sdhci_platdata crag6410_hsmmc0_pdata = अणु
	.max_width		= 4,
	.cd_type		= S3C_SDHCI_CD_INTERNAL,
	.cfg_gpio		= crag6410_cfg_sdhci0,
	.host_caps		= MMC_CAP_POWER_OFF_CARD,
पूर्ण;

अटल स्थिर काष्ठा gpio_led gpio_leds[] = अणु
	अणु
		.name = "d13:green:",
		.gpio = MMGPIO_GPIO_BASE + 0,
		.शेष_state = LEDS_GPIO_DEFSTATE_ON,
	पूर्ण,
	अणु
		.name = "d14:green:",
		.gpio = MMGPIO_GPIO_BASE + 1,
		.शेष_state = LEDS_GPIO_DEFSTATE_ON,
	पूर्ण,
	अणु
		.name = "d15:green:",
		.gpio = MMGPIO_GPIO_BASE + 2,
		.शेष_state = LEDS_GPIO_DEFSTATE_ON,
	पूर्ण,
	अणु
		.name = "d16:green:",
		.gpio = MMGPIO_GPIO_BASE + 3,
		.शेष_state = LEDS_GPIO_DEFSTATE_ON,
	पूर्ण,
	अणु
		.name = "d17:green:",
		.gpio = MMGPIO_GPIO_BASE + 4,
		.शेष_state = LEDS_GPIO_DEFSTATE_ON,
	पूर्ण,
	अणु
		.name = "d18:green:",
		.gpio = MMGPIO_GPIO_BASE + 5,
		.शेष_state = LEDS_GPIO_DEFSTATE_ON,
	पूर्ण,
	अणु
		.name = "d19:green:",
		.gpio = MMGPIO_GPIO_BASE + 6,
		.शेष_state = LEDS_GPIO_DEFSTATE_ON,
	पूर्ण,
	अणु
		.name = "d20:green:",
		.gpio = MMGPIO_GPIO_BASE + 7,
		.शेष_state = LEDS_GPIO_DEFSTATE_ON,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा gpio_led_platक्रमm_data gpio_leds_pdata = अणु
	.leds = gpio_leds,
	.num_leds = ARRAY_SIZE(gpio_leds),
पूर्ण;

अटल काष्ठा dwc2_hsotg_plat crag6410_hsotg_pdata;

अटल व्योम __init crag6410_machine_init(व्योम)
अणु
	/* Open drain IRQs need pullups */
	s3c_gpio_setpull(S3C64XX_GPM(0), S3C_GPIO_PULL_UP);
	s3c_gpio_setpull(S3C64XX_GPN(0), S3C_GPIO_PULL_UP);

	gpio_request(S3C64XX_GPB(0), "LCD power");
	gpio_direction_output(S3C64XX_GPB(0), 0);

	gpio_request(S3C64XX_GPF(14), "LCD PWM");
	gpio_direction_output(S3C64XX_GPF(14), 0);  /* turn off */

	gpio_request(S3C64XX_GPB(1), "SD power");
	gpio_direction_output(S3C64XX_GPB(1), 0);

	gpio_request(S3C64XX_GPF(10), "nRESETSEL");
	gpio_direction_output(S3C64XX_GPF(10), 1);

	s3c_sdhci0_set_platdata(&crag6410_hsmmc0_pdata);
	s3c_sdhci2_set_platdata(&crag6410_hsmmc2_pdata);

	s3c_i2c0_set_platdata(&i2c0_pdata);
	s3c_i2c1_set_platdata(&i2c1_pdata);
	s3c_fb_set_platdata(&crag6410_lcd_pdata);
	dwc2_hsotg_set_platdata(&crag6410_hsotg_pdata);

	gpiod_add_lookup_table(&crag_pmic_gpiod_table);
	i2c_रेजिस्टर_board_info(0, i2c_devs0, ARRAY_SIZE(i2c_devs0));
	i2c_रेजिस्टर_board_info(1, i2c_devs1, ARRAY_SIZE(i2c_devs1));

	samsung_keypad_set_platdata(&crag6410_keypad_data);
	s3c64xx_spi0_set_platdata(शून्य, 0, 2);

	pwm_add_table(crag6410_pwm_lookup, ARRAY_SIZE(crag6410_pwm_lookup));
	platक्रमm_add_devices(crag6410_devices, ARRAY_SIZE(crag6410_devices));

	gpio_led_रेजिस्टर_device(-1, &gpio_leds_pdata);

	regulator_has_full_स्थिरraपूर्णांकs();

	s3c64xx_pm_init();
पूर्ण

MACHINE_START(WLF_CRAGG_6410, "Wolfson Cragganmore 6410")
	/* Maपूर्णांकainer: Mark Brown <broonie@खोलोsource.wolfsonmicro.com> */
	.atag_offset	= 0x100,
	.nr_irqs	= S3C64XX_NR_IRQS,
	.init_irq	= s3c6410_init_irq,
	.map_io		= crag6410_map_io,
	.init_machine	= crag6410_machine_init,
	.init_समय	= s3c64xx_समयr_init,
MACHINE_END
