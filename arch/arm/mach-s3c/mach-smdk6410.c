<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright 2008 Openmoko, Inc.
// Copyright 2008 Simtec Electronics
//	Ben Dooks <ben@simtec.co.uk>
//	http://armlinux.simtec.co.uk/

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/समयr.h>
#समावेश <linux/init.h>
#समावेश <linux/input.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/serial_s3c.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/i2c.h>
#समावेश <linux/leds.h>
#समावेश <linux/fb.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/delay.h>
#समावेश <linux/smsc911x.h>
#समावेश <linux/regulator/fixed.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/pwm.h>
#समावेश <linux/pwm_backlight.h>
#समावेश <linux/platक्रमm_data/s3c-hsotg.h>

#अगर_घोषित CONFIG_SMDK6410_WM1190_EV1
#समावेश <linux/mfd/wm8350/core.h>
#समावेश <linux/mfd/wm8350/pmic.h>
#पूर्ण_अगर

#अगर_घोषित CONFIG_SMDK6410_WM1192_EV1
#समावेश <linux/mfd/wm831x/core.h>
#समावेश <linux/mfd/wm831x/pdata.h>
#पूर्ण_अगर

#समावेश <video/platक्रमm_lcd.h>
#समावेश <video/samsung_fimd.h>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/mach/irq.h>

#समावेश <mach/irqs.h>
#समावेश "map.h"

#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/mach-types.h>

#समावेश "regs-gpio.h"
#समावेश "gpio-samsung.h"
#समावेश <linux/platक्रमm_data/ata-samsung_cf.h>
#समावेश <linux/platक्रमm_data/i2c-s3c2410.h>
#समावेश "fb.h"
#समावेश "gpio-cfg.h"

#समावेश "devs.h"
#समावेश "cpu.h"
#समावेश <linux/soc/samsung/s3c-adc.h>
#समावेश <linux/platक्रमm_data/touchscreen-s3c2410.h>
#समावेश "keypad.h"

#समावेश "backlight-s3c64xx.h"
#समावेश "s3c64xx.h"
#समावेश "regs-modem-s3c64xx.h"
#समावेश "regs-srom-s3c64xx.h"
#समावेश "regs-sys-s3c64xx.h"

#घोषणा UCON S3C2410_UCON_DEFAULT | S3C2410_UCON_UCLK
#घोषणा ULCON S3C2410_LCON_CS8 | S3C2410_LCON_PNONE | S3C2410_LCON_STOPB
#घोषणा UFCON S3C2410_UFCON_RXTRIG8 | S3C2410_UFCON_FIFOMODE

अटल काष्ठा s3c2410_uartcfg smdk6410_uartcfgs[] __initdata = अणु
	[0] = अणु
		.hwport	     = 0,
		.flags	     = 0,
		.ucon	     = UCON,
		.ulcon	     = ULCON,
		.ufcon	     = UFCON,
	पूर्ण,
	[1] = अणु
		.hwport	     = 1,
		.flags	     = 0,
		.ucon	     = UCON,
		.ulcon	     = ULCON,
		.ufcon	     = UFCON,
	पूर्ण,
	[2] = अणु
		.hwport	     = 2,
		.flags	     = 0,
		.ucon	     = UCON,
		.ulcon	     = ULCON,
		.ufcon	     = UFCON,
	पूर्ण,
	[3] = अणु
		.hwport	     = 3,
		.flags	     = 0,
		.ucon	     = UCON,
		.ulcon	     = ULCON,
		.ufcon	     = UFCON,
	पूर्ण,
पूर्ण;

/* framebuffer and LCD setup. */

/* GPF15 = LCD backlight control
 * GPF13 => Panel घातer
 * GPN5 = LCD nRESET संकेत
 * PWM_TOUT1 => backlight brightness
 */

अटल व्योम smdk6410_lcd_घातer_set(काष्ठा plat_lcd_data *pd,
				   अचिन्हित पूर्णांक घातer)
अणु
	अगर (घातer) अणु
		gpio_direction_output(S3C64XX_GPF(13), 1);

		/* fire nRESET on घातer up */
		gpio_direction_output(S3C64XX_GPN(5), 0);
		msleep(10);
		gpio_direction_output(S3C64XX_GPN(5), 1);
		msleep(1);
	पूर्ण अन्यथा अणु
		gpio_direction_output(S3C64XX_GPF(13), 0);
	पूर्ण
पूर्ण

अटल काष्ठा plat_lcd_data smdk6410_lcd_घातer_data = अणु
	.set_घातer	= smdk6410_lcd_घातer_set,
पूर्ण;

अटल काष्ठा platक्रमm_device smdk6410_lcd_घातerdev = अणु
	.name			= "platform-lcd",
	.dev.parent		= &s3c_device_fb.dev,
	.dev.platक्रमm_data	= &smdk6410_lcd_घातer_data,
पूर्ण;

अटल काष्ठा s3c_fb_pd_win smdk6410_fb_win0 = अणु
	.max_bpp	= 32,
	.शेष_bpp	= 16,
	.xres		= 800,
	.yres		= 480,
	.भव_y	= 480 * 2,
	.भव_x	= 800,
पूर्ण;

अटल काष्ठा fb_videomode smdk6410_lcd_timing = अणु
	.left_margin	= 8,
	.right_margin	= 13,
	.upper_margin	= 7,
	.lower_margin	= 5,
	.hsync_len	= 3,
	.vsync_len	= 1,
	.xres		= 800,
	.yres		= 480,
पूर्ण;

/* 405566 घड़ीs per frame => 60Hz refresh requires 24333960Hz घड़ी */
अटल काष्ठा s3c_fb_platdata smdk6410_lcd_pdata __initdata = अणु
	.setup_gpio	= s3c64xx_fb_gpio_setup_24bpp,
	.vtiming	= &smdk6410_lcd_timing,
	.win[0]		= &smdk6410_fb_win0,
	.vidcon0	= VIDCON0_VIDOUT_RGB | VIDCON0_PNRMODE_RGB,
	.vidcon1	= VIDCON1_INV_HSYNC | VIDCON1_INV_VSYNC,
पूर्ण;

/*
 * Configuring Ethernet on SMDK6410
 *
 * Both CS8900A and LAN9115 chips share one chip select mediated by CFG6.
 * The स्थिरant address below corresponds to nCS1
 *
 *  1) Set CFGB2 p3 ON others off, no other CFGB selects "ethernet"
 *  2) CFG6 needs to be चयनed to "LAN9115" side
 */

अटल काष्ठा resource smdk6410_smsc911x_resources[] = अणु
	[0] = DEFINE_RES_MEM(S3C64XX_PA_XM0CSN1, SZ_64K),
	[1] = DEFINE_RES_NAMED(S3C_EINT(10), 1, शून्य, IORESOURCE_IRQ \
					| IRQ_TYPE_LEVEL_LOW),
पूर्ण;

अटल काष्ठा smsc911x_platक्रमm_config smdk6410_smsc911x_pdata = अणु
	.irq_polarity  = SMSC911X_IRQ_POLARITY_ACTIVE_LOW,
	.irq_type      = SMSC911X_IRQ_TYPE_OPEN_DRAIN,
	.flags         = SMSC911X_USE_32BIT | SMSC911X_FORCE_INTERNAL_PHY,
	.phy_पूर्णांकerface = PHY_INTERFACE_MODE_MII,
पूर्ण;


अटल काष्ठा platक्रमm_device smdk6410_smsc911x = अणु
	.name          = "smsc911x",
	.id            = -1,
	.num_resources = ARRAY_SIZE(smdk6410_smsc911x_resources),
	.resource      = &smdk6410_smsc911x_resources[0],
	.dev = अणु
		.platक्रमm_data = &smdk6410_smsc911x_pdata,
	पूर्ण,
पूर्ण;

#अगर_घोषित CONFIG_REGULATOR
अटल काष्ठा regulator_consumer_supply smdk6410_b_pwr_5v_consumers[] = अणु
	REGULATOR_SUPPLY("PVDD", "0-001b"),
	REGULATOR_SUPPLY("AVDD", "0-001b"),
पूर्ण;

अटल काष्ठा regulator_init_data __maybe_unused smdk6410_b_pwr_5v_data = अणु
	.स्थिरraपूर्णांकs = अणु
		.always_on = 1,
	पूर्ण,
	.num_consumer_supplies = ARRAY_SIZE(smdk6410_b_pwr_5v_consumers),
	.consumer_supplies = smdk6410_b_pwr_5v_consumers,
पूर्ण;

अटल काष्ठा fixed_voltage_config smdk6410_b_pwr_5v_pdata = अणु
	.supply_name = "B_PWR_5V",
	.microvolts = 5000000,
	.init_data = &smdk6410_b_pwr_5v_data,
पूर्ण;

अटल काष्ठा platक्रमm_device smdk6410_b_pwr_5v = अणु
	.name          = "reg-fixed-voltage",
	.id            = -1,
	.dev = अणु
		.platक्रमm_data = &smdk6410_b_pwr_5v_pdata,
	पूर्ण,
पूर्ण;
#पूर्ण_अगर

अटल काष्ठा s3c_ide_platdata smdk6410_ide_pdata __initdata = अणु
	.setup_gpio	= s3c64xx_ide_setup_gpio,
पूर्ण;

अटल uपूर्णांक32_t smdk6410_keymap[] __initdata = अणु
	/* KEY(row, col, keycode) */
	KEY(0, 3, KEY_1), KEY(0, 4, KEY_2), KEY(0, 5, KEY_3),
	KEY(0, 6, KEY_4), KEY(0, 7, KEY_5),
	KEY(1, 3, KEY_A), KEY(1, 4, KEY_B), KEY(1, 5, KEY_C),
	KEY(1, 6, KEY_D), KEY(1, 7, KEY_E)
पूर्ण;

अटल काष्ठा matrix_keymap_data smdk6410_keymap_data __initdata = अणु
	.keymap		= smdk6410_keymap,
	.keymap_size	= ARRAY_SIZE(smdk6410_keymap),
पूर्ण;

अटल काष्ठा samsung_keypad_platdata smdk6410_keypad_data __initdata = अणु
	.keymap_data	= &smdk6410_keymap_data,
	.rows		= 2,
	.cols		= 8,
पूर्ण;

अटल काष्ठा map_desc smdk6410_iodesc[] = अणुपूर्ण;

अटल काष्ठा platक्रमm_device *smdk6410_devices[] __initdata = अणु
#अगर_घोषित CONFIG_SMDK6410_SD_CH0
	&s3c_device_hsmmc0,
#पूर्ण_अगर
#अगर_घोषित CONFIG_SMDK6410_SD_CH1
	&s3c_device_hsmmc1,
#पूर्ण_अगर
	&s3c_device_i2c0,
	&s3c_device_i2c1,
	&s3c_device_fb,
	&s3c_device_ohci,
	&samsung_device_pwm,
	&s3c_device_usb_hsotg,
	&s3c64xx_device_iisv4,
	&samsung_device_keypad,

#अगर_घोषित CONFIG_REGULATOR
	&smdk6410_b_pwr_5v,
#पूर्ण_अगर
	&smdk6410_lcd_घातerdev,

	&smdk6410_smsc911x,
	&s3c_device_adc,
	&s3c_device_cfcon,
	&s3c_device_rtc,
	&s3c_device_wdt,
पूर्ण;

#अगर_घोषित CONFIG_REGULATOR
/* ARM core */
अटल काष्ठा regulator_consumer_supply smdk6410_vddarm_consumers[] = अणु
	REGULATOR_SUPPLY("vddarm", शून्य),
पूर्ण;

/* VDDARM, BUCK1 on J5 */
अटल काष्ठा regulator_init_data __maybe_unused smdk6410_vddarm = अणु
	.स्थिरraपूर्णांकs = अणु
		.name = "PVDD_ARM",
		.min_uV = 1000000,
		.max_uV = 1300000,
		.always_on = 1,
		.valid_ops_mask = REGULATOR_CHANGE_VOLTAGE,
	पूर्ण,
	.num_consumer_supplies = ARRAY_SIZE(smdk6410_vddarm_consumers),
	.consumer_supplies = smdk6410_vddarm_consumers,
पूर्ण;

/* VDD_INT, BUCK2 on J5 */
अटल काष्ठा regulator_init_data __maybe_unused smdk6410_vddपूर्णांक = अणु
	.स्थिरraपूर्णांकs = अणु
		.name = "PVDD_INT",
		.min_uV = 1000000,
		.max_uV = 1200000,
		.always_on = 1,
		.valid_ops_mask = REGULATOR_CHANGE_VOLTAGE,
	पूर्ण,
पूर्ण;

/* VDD_HI, LDO3 on J5 */
अटल काष्ठा regulator_init_data __maybe_unused smdk6410_vddhi = अणु
	.स्थिरraपूर्णांकs = अणु
		.name = "PVDD_HI",
		.always_on = 1,
	पूर्ण,
पूर्ण;

/* VDD_PLL, LDO2 on J5 */
अटल काष्ठा regulator_init_data __maybe_unused smdk6410_vddpll = अणु
	.स्थिरraपूर्णांकs = अणु
		.name = "PVDD_PLL",
		.always_on = 1,
	पूर्ण,
पूर्ण;

/* VDD_UH_MMC, LDO5 on J5 */
अटल काष्ठा regulator_init_data __maybe_unused smdk6410_vdduh_mmc = अणु
	.स्थिरraपूर्णांकs = अणु
		.name = "PVDD_UH+PVDD_MMC",
		.always_on = 1,
	पूर्ण,
पूर्ण;

/* VCCM3BT, LDO8 on J5 */
अटल काष्ठा regulator_init_data __maybe_unused smdk6410_vccmc3bt = अणु
	.स्थिरraपूर्णांकs = अणु
		.name = "PVCCM3BT",
		.always_on = 1,
	पूर्ण,
पूर्ण;

/* VCCM2MTV, LDO11 on J5 */
अटल काष्ठा regulator_init_data __maybe_unused smdk6410_vccm2mtv = अणु
	.स्थिरraपूर्णांकs = अणु
		.name = "PVCCM2MTV",
		.always_on = 1,
	पूर्ण,
पूर्ण;

/* VDD_LCD, LDO12 on J5 */
अटल काष्ठा regulator_init_data __maybe_unused smdk6410_vddlcd = अणु
	.स्थिरraपूर्णांकs = अणु
		.name = "PVDD_LCD",
		.always_on = 1,
	पूर्ण,
पूर्ण;

/* VDD_OTGI, LDO9 on J5 */
अटल काष्ठा regulator_init_data __maybe_unused smdk6410_vdकरोtgi = अणु
	.स्थिरraपूर्णांकs = अणु
		.name = "PVDD_OTGI",
		.always_on = 1,
	पूर्ण,
पूर्ण;

/* VDD_OTG, LDO14 on J5 */
अटल काष्ठा regulator_init_data __maybe_unused smdk6410_vdकरोtg = अणु
	.स्थिरraपूर्णांकs = अणु
		.name = "PVDD_OTG",
		.always_on = 1,
	पूर्ण,
पूर्ण;

/* VDD_ALIVE, LDO15 on J5 */
अटल काष्ठा regulator_init_data __maybe_unused smdk6410_vddalive = अणु
	.स्थिरraपूर्णांकs = अणु
		.name = "PVDD_ALIVE",
		.always_on = 1,
	पूर्ण,
पूर्ण;

/* VDD_AUDIO, VLDO_AUDIO on J5 */
अटल काष्ठा regulator_init_data __maybe_unused smdk6410_vddaudio = अणु
	.स्थिरraपूर्णांकs = अणु
		.name = "PVDD_AUDIO",
		.always_on = 1,
	पूर्ण,
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_SMDK6410_WM1190_EV1
/* S3C64xx पूर्णांकernal logic & PLL */
अटल काष्ठा regulator_init_data __maybe_unused wm8350_dcdc1_data = अणु
	.स्थिरraपूर्णांकs = अणु
		.name = "PVDD_INT+PVDD_PLL",
		.min_uV = 1200000,
		.max_uV = 1200000,
		.always_on = 1,
		.apply_uV = 1,
	पूर्ण,
पूर्ण;

/* Memory */
अटल काष्ठा regulator_init_data __maybe_unused wm8350_dcdc3_data = अणु
	.स्थिरraपूर्णांकs = अणु
		.name = "PVDD_MEM",
		.min_uV = 1800000,
		.max_uV = 1800000,
		.always_on = 1,
		.state_mem = अणु
			 .uV = 1800000,
			 .mode = REGULATOR_MODE_NORMAL,
			 .enabled = 1,
		पूर्ण,
		.initial_state = PM_SUSPEND_MEM,
	पूर्ण,
पूर्ण;

/* USB, EXT, PCM, ADC/DAC, USB, MMC */
अटल काष्ठा regulator_consumer_supply wm8350_dcdc4_consumers[] = अणु
	REGULATOR_SUPPLY("DVDD", "0-001b"),
पूर्ण;

अटल काष्ठा regulator_init_data __maybe_unused wm8350_dcdc4_data = अणु
	.स्थिरraपूर्णांकs = अणु
		.name = "PVDD_HI+PVDD_EXT+PVDD_SYS+PVCCM2MTV",
		.min_uV = 3000000,
		.max_uV = 3000000,
		.always_on = 1,
	पूर्ण,
	.num_consumer_supplies = ARRAY_SIZE(wm8350_dcdc4_consumers),
	.consumer_supplies = wm8350_dcdc4_consumers,
पूर्ण;

/* OTGi/1190-EV1 HPVDD & AVDD */
अटल काष्ठा regulator_init_data __maybe_unused wm8350_lकरो4_data = अणु
	.स्थिरraपूर्णांकs = अणु
		.name = "PVDD_OTGI+HPVDD+AVDD",
		.min_uV = 1200000,
		.max_uV = 1200000,
		.apply_uV = 1,
		.always_on = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा अणु
	पूर्णांक regulator;
	काष्ठा regulator_init_data *initdata;
पूर्ण wm1190_regulators[] = अणु
	अणु WM8350_DCDC_1, &wm8350_dcdc1_data पूर्ण,
	अणु WM8350_DCDC_3, &wm8350_dcdc3_data पूर्ण,
	अणु WM8350_DCDC_4, &wm8350_dcdc4_data पूर्ण,
	अणु WM8350_DCDC_6, &smdk6410_vddarm पूर्ण,
	अणु WM8350_LDO_1, &smdk6410_vddalive पूर्ण,
	अणु WM8350_LDO_2, &smdk6410_vdकरोtg पूर्ण,
	अणु WM8350_LDO_3, &smdk6410_vddlcd पूर्ण,
	अणु WM8350_LDO_4, &wm8350_lकरो4_data पूर्ण,
पूर्ण;

अटल पूर्णांक __init smdk6410_wm8350_init(काष्ठा wm8350 *wm8350)
अणु
	पूर्णांक i;

	/* Configure the IRQ line */
	s3c_gpio_setpull(S3C64XX_GPN(12), S3C_GPIO_PULL_UP);

	/* Instantiate the regulators */
	क्रम (i = 0; i < ARRAY_SIZE(wm1190_regulators); i++)
		wm8350_रेजिस्टर_regulator(wm8350,
					  wm1190_regulators[i].regulator,
					  wm1190_regulators[i].initdata);

	वापस 0;
पूर्ण

अटल काष्ठा wm8350_platक्रमm_data __initdata smdk6410_wm8350_pdata = अणु
	.init = smdk6410_wm8350_init,
	.irq_high = 1,
	.irq_base = IRQ_BOARD_START,
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_SMDK6410_WM1192_EV1
अटल काष्ठा gpio_led wm1192_pmic_leds[] = अणु
	अणु
		.name = "PMIC:red:power",
		.gpio = GPIO_BOARD_START + 3,
		.शेष_state = LEDS_GPIO_DEFSTATE_ON,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_led_platक्रमm_data wm1192_pmic_led = अणु
	.num_leds = ARRAY_SIZE(wm1192_pmic_leds),
	.leds = wm1192_pmic_leds,
पूर्ण;

अटल काष्ठा platक्रमm_device wm1192_pmic_led_dev = अणु
	.name          = "leds-gpio",
	.id            = -1,
	.dev = अणु
		.platक्रमm_data = &wm1192_pmic_led,
	पूर्ण,
पूर्ण;

अटल पूर्णांक wm1192_pre_init(काष्ठा wm831x *wm831x)
अणु
	पूर्णांक ret;

	/* Configure the IRQ line */
	s3c_gpio_setpull(S3C64XX_GPN(12), S3C_GPIO_PULL_UP);

	ret = platक्रमm_device_रेजिस्टर(&wm1192_pmic_led_dev);
	अगर (ret != 0)
		dev_err(wm831x->dev, "Failed to add PMIC LED: %d\n", ret);

	वापस 0;
पूर्ण

अटल काष्ठा wm831x_backlight_pdata wm1192_backlight_pdata = अणु
	.isink = 1,
	.max_uA = 27554,
पूर्ण;

अटल काष्ठा regulator_init_data __maybe_unused wm1192_dcdc3 = अणु
	.स्थिरraपूर्णांकs = अणु
		.name = "PVDD_MEM+PVDD_GPS",
		.always_on = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा regulator_consumer_supply wm1192_lकरो1_consumers[] = अणु
	REGULATOR_SUPPLY("DVDD", "0-001b"),   /* WM8580 */
पूर्ण;

अटल काष्ठा regulator_init_data __maybe_unused wm1192_lकरो1 = अणु
	.स्थिरraपूर्णांकs = अणु
		.name = "PVDD_LCD+PVDD_EXT",
		.always_on = 1,
	पूर्ण,
	.consumer_supplies = wm1192_lकरो1_consumers,
	.num_consumer_supplies = ARRAY_SIZE(wm1192_lकरो1_consumers),
पूर्ण;

अटल काष्ठा wm831x_status_pdata wm1192_led7_pdata = अणु
	.name = "LED7:green:",
पूर्ण;

अटल काष्ठा wm831x_status_pdata wm1192_led8_pdata = अणु
	.name = "LED8:green:",
पूर्ण;

अटल काष्ठा wm831x_pdata smdk6410_wm1192_pdata = अणु
	.pre_init = wm1192_pre_init,

	.backlight = &wm1192_backlight_pdata,
	.dcdc = अणु
		&smdk6410_vddarm,  /* DCDC1 */
		&smdk6410_vddपूर्णांक,  /* DCDC2 */
		&wm1192_dcdc3,
	पूर्ण,
	.gpio_base = GPIO_BOARD_START,
	.lकरो = अणु
		 &wm1192_lकरो1,        /* LDO1 */
		 &smdk6410_vdduh_mmc, /* LDO2 */
		 शून्य,                /* LDO3 NC */
		 &smdk6410_vdकरोtgi,   /* LDO4 */
		 &smdk6410_vdकरोtg,    /* LDO5 */
		 &smdk6410_vddhi,     /* LDO6 */
		 &smdk6410_vddaudio,  /* LDO7 */
		 &smdk6410_vccm2mtv,  /* LDO8 */
		 &smdk6410_vddpll,    /* LDO9 */
		 &smdk6410_vccmc3bt,  /* LDO10 */
		 &smdk6410_vddalive,  /* LDO11 */
	पूर्ण,
	.status = अणु
		&wm1192_led7_pdata,
		&wm1192_led8_pdata,
	पूर्ण,
पूर्ण;
#पूर्ण_अगर

अटल काष्ठा i2c_board_info i2c_devs0[] __initdata = अणु
	अणु I2C_BOARD_INFO("24c08", 0x50), पूर्ण,
	अणु I2C_BOARD_INFO("wm8580", 0x1b), पूर्ण,

#अगर_घोषित CONFIG_SMDK6410_WM1192_EV1
	अणु I2C_BOARD_INFO("wm8312", 0x34),
	  .platक्रमm_data = &smdk6410_wm1192_pdata,
	  .irq = S3C_EINT(12),
	पूर्ण,
#पूर्ण_अगर

#अगर_घोषित CONFIG_SMDK6410_WM1190_EV1
	अणु I2C_BOARD_INFO("wm8350", 0x1a),
	  .platक्रमm_data = &smdk6410_wm8350_pdata,
	  .irq = S3C_EINT(12),
	पूर्ण,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा i2c_board_info i2c_devs1[] __initdata = अणु
	अणु I2C_BOARD_INFO("24c128", 0x57), पूर्ण,	/* Samsung S524AD0XD1 */
पूर्ण;

/* LCD Backlight data */
अटल काष्ठा samsung_bl_gpio_info smdk6410_bl_gpio_info = अणु
	.no = S3C64XX_GPF(15),
	.func = S3C_GPIO_SFN(2),
पूर्ण;

अटल काष्ठा pwm_lookup smdk6410_pwm_lookup[] = अणु
	PWM_LOOKUP("samsung-pwm", 1, "pwm-backlight.0", शून्य, 78770,
		   PWM_POLARITY_NORMAL),
पूर्ण;

अटल काष्ठा platक्रमm_pwm_backlight_data smdk6410_bl_data = अणु
	/* Intentionally blank */
पूर्ण;

अटल काष्ठा dwc2_hsotg_plat smdk6410_hsotg_pdata;

अटल व्योम __init smdk6410_map_io(व्योम)
अणु
	u32 पंचांगp;

	s3c64xx_init_io(smdk6410_iodesc, ARRAY_SIZE(smdk6410_iodesc));
	s3c64xx_set_xtal_freq(12000000);
	s3c24xx_init_uarts(smdk6410_uartcfgs, ARRAY_SIZE(smdk6410_uartcfgs));
	s3c64xx_set_समयr_source(S3C64XX_PWM3, S3C64XX_PWM4);

	/* set the LCD type */

	पंचांगp = __raw_पढ़ोl(S3C64XX_SPCON);
	पंचांगp &= ~S3C64XX_SPCON_LCD_SEL_MASK;
	पंचांगp |= S3C64XX_SPCON_LCD_SEL_RGB;
	__raw_ग_लिखोl(पंचांगp, S3C64XX_SPCON);

	/* हटाओ the lcd bypass */
	पंचांगp = __raw_पढ़ोl(S3C64XX_MODEM_MIFPCON);
	पंचांगp &= ~MIFPCON_LCD_BYPASS;
	__raw_ग_लिखोl(पंचांगp, S3C64XX_MODEM_MIFPCON);
पूर्ण

अटल व्योम __init smdk6410_machine_init(व्योम)
अणु
	u32 cs1;

	s3c_i2c0_set_platdata(शून्य);
	s3c_i2c1_set_platdata(शून्य);
	s3c_fb_set_platdata(&smdk6410_lcd_pdata);
	dwc2_hsotg_set_platdata(&smdk6410_hsotg_pdata);

	samsung_keypad_set_platdata(&smdk6410_keypad_data);

	s3c64xx_ts_set_platdata(शून्य);

	/* configure nCS1 width to 16 bits */

	cs1 = __raw_पढ़ोl(S3C64XX_SROM_BW) &
		    ~(S3C64XX_SROM_BW__CS_MASK << S3C64XX_SROM_BW__NCS1__SHIFT);
	cs1 |= ((1 << S3C64XX_SROM_BW__DATAWIDTH__SHIFT) |
		(1 << S3C64XX_SROM_BW__WAITENABLE__SHIFT) |
		(1 << S3C64XX_SROM_BW__BYTEENABLE__SHIFT)) <<
						   S3C64XX_SROM_BW__NCS1__SHIFT;
	__raw_ग_लिखोl(cs1, S3C64XX_SROM_BW);

	/* set timing क्रम nCS1 suitable क्रम ethernet chip */

	__raw_ग_लिखोl((0 << S3C64XX_SROM_BCX__PMC__SHIFT) |
		     (6 << S3C64XX_SROM_BCX__TACP__SHIFT) |
		     (4 << S3C64XX_SROM_BCX__TCAH__SHIFT) |
		     (1 << S3C64XX_SROM_BCX__TCOH__SHIFT) |
		     (0xe << S3C64XX_SROM_BCX__TACC__SHIFT) |
		     (4 << S3C64XX_SROM_BCX__TCOS__SHIFT) |
		     (0 << S3C64XX_SROM_BCX__TACS__SHIFT), S3C64XX_SROM_BC1);

	gpio_request(S3C64XX_GPN(5), "LCD power");
	gpio_request(S3C64XX_GPF(13), "LCD power");

	i2c_रेजिस्टर_board_info(0, i2c_devs0, ARRAY_SIZE(i2c_devs0));
	i2c_रेजिस्टर_board_info(1, i2c_devs1, ARRAY_SIZE(i2c_devs1));

	s3c_ide_set_platdata(&smdk6410_ide_pdata);

	platक्रमm_add_devices(smdk6410_devices, ARRAY_SIZE(smdk6410_devices));

	pwm_add_table(smdk6410_pwm_lookup, ARRAY_SIZE(smdk6410_pwm_lookup));
	samsung_bl_set(&smdk6410_bl_gpio_info, &smdk6410_bl_data);
पूर्ण

MACHINE_START(SMDK6410, "SMDK6410")
	/* Maपूर्णांकainer: Ben Dooks <ben-linux@fluff.org> */
	.atag_offset	= 0x100,
	.nr_irqs	= S3C64XX_NR_IRQS,
	.init_irq	= s3c6410_init_irq,
	.map_io		= smdk6410_map_io,
	.init_machine	= smdk6410_machine_init,
	.init_समय	= s3c64xx_समयr_init,
MACHINE_END
