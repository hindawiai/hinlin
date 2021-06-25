<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// S3C2442 Machine Support क्रम Openmoko GTA02 / FreeRunner.
//
// Copyright (C) 2006-2009 by Openmoko, Inc.
// Authors: Harald Welte <laक्रमge@खोलोmoko.org>
//          Andy Green <andy@खोलोmoko.org>
//          Werner Almesberger <werner@खोलोmoko.org>
// All rights reserved.

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/delay.h>
#समावेश <linux/समयr.h>
#समावेश <linux/init.h>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio_keys.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/serial_s3c.h>
#समावेश <linux/input.h>
#समावेश <linux/पन.स>
#समावेश <linux/i2c.h>

#समावेश <linux/mmc/host.h>

#समावेश <linux/mfd/pcf50633/adc.h>
#समावेश <linux/mfd/pcf50633/backlight.h>
#समावेश <linux/mfd/pcf50633/core.h>
#समावेश <linux/mfd/pcf50633/gpपन.स>
#समावेश <linux/mfd/pcf50633/mbc.h>
#समावेश <linux/mfd/pcf50633/pmic.h>

#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/mtd/nand-ecc-sw-hamming.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/mtd/physmap.h>

#समावेश <linux/regulator/machine.h>

#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/s3c24xx.h>

#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/mach/irq.h>

#समावेश <linux/platक्रमm_data/i2c-s3c2410.h>
#समावेश <linux/platक्रमm_data/mtd-nand-s3c2410.h>
#समावेश <linux/platक्रमm_data/touchscreen-s3c2410.h>
#समावेश <linux/platक्रमm_data/usb-ohci-s3c2410.h>
#समावेश <linux/platक्रमm_data/usb-s3c2410_udc.h>
#समावेश <linux/platक्रमm_data/fb-s3c2410.h>

#समावेश "regs-gpio.h"
#समावेश "regs-irq.h"
#समावेश "gpio-samsung.h"

#समावेश "cpu.h"
#समावेश "devs.h"
#समावेश "gpio-cfg.h"
#समावेश "pm.h"

#समावेश "s3c24xx.h"
#समावेश "gta02.h"

अटल काष्ठा pcf50633 *gta02_pcf;

/*
 * This माला_लो called frequently when we paniced.
 */

अटल दीर्घ gta02_panic_blink(पूर्णांक state)
अणु
	दीर्घ delay = 0;
	अक्षर led;

	led = (state) ? 1 : 0;
	gpio_direction_output(GTA02_GPIO_AUX_LED, led);

	वापस delay;
पूर्ण


अटल काष्ठा map_desc gta02_iodesc[] __initdata = अणु
	अणु
		.भव	= 0xe0000000,
		.pfn		= __phys_to_pfn(S3C2410_CS3 + 0x01000000),
		.length		= SZ_1M,
		.type		= MT_DEVICE
	पूर्ण,
पूर्ण;

#घोषणा UCON (S3C2410_UCON_DEFAULT | S3C2443_UCON_RXERR_IRQEN)
#घोषणा ULCON (S3C2410_LCON_CS8 | S3C2410_LCON_PNONE | S3C2410_LCON_STOPB)
#घोषणा UFCON (S3C2410_UFCON_RXTRIG8 | S3C2410_UFCON_FIFOMODE)

अटल काष्ठा s3c2410_uartcfg gta02_uartcfgs[] = अणु
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

#अगर_घोषित CONFIG_CHARGER_PCF50633
/*
 * On GTA02 the 1A अक्षरger features a 48K resistor to 0V on the ID pin.
 * We use this to recognize that we can pull 1A from the USB socket.
 *
 * These स्थिरants are the measured pcf50633 ADC levels with the 1A
 * अक्षरger / 48K resistor, and with no pullकरोwn resistor.
 */

#घोषणा ADC_NOM_CHG_DETECT_1A 6
#घोषणा ADC_NOM_CHG_DETECT_USB 43

#अगर_घोषित CONFIG_PCF50633_ADC
अटल व्योम
gta02_configure_pmu_क्रम_अक्षरger(काष्ठा pcf50633 *pcf, व्योम *unused, पूर्णांक res)
अणु
	पूर्णांक  ma;

	/* Interpret अक्षरger type */
	अगर (res < ((ADC_NOM_CHG_DETECT_USB + ADC_NOM_CHG_DETECT_1A) / 2)) अणु

		/*
		 * Sanity - stop GPO driving out now that we have a 1A अक्षरger
		 * GPO controls USB Host घातer generation on GTA02
		 */
		pcf50633_gpio_set(pcf, PCF50633_GPO, 0);

		ma = 1000;
	पूर्ण अन्यथा
		ma = 100;

	pcf50633_mbc_usb_curlim_set(pcf, ma);
पूर्ण
#पूर्ण_अगर

अटल काष्ठा delayed_work gta02_अक्षरger_work;
अटल पूर्णांक gta02_usb_vbus_draw;

अटल व्योम gta02_अक्षरger_worker(काष्ठा work_काष्ठा *work)
अणु
	अगर (gta02_usb_vbus_draw) अणु
		pcf50633_mbc_usb_curlim_set(gta02_pcf, gta02_usb_vbus_draw);
		वापस;
	पूर्ण

#अगर_घोषित CONFIG_PCF50633_ADC
	pcf50633_adc_async_पढ़ो(gta02_pcf,
				PCF50633_ADCC1_MUX_ADCIN1,
				PCF50633_ADCC1_AVERAGE_16,
				gta02_configure_pmu_क्रम_अक्षरger,
				शून्य);
#अन्यथा
	/*
	 * If the PCF50633 ADC is disabled we fallback to a
	 * 100mA limit क्रम safety.
	 */
	pcf50633_mbc_usb_curlim_set(gta02_pcf, 100);
#पूर्ण_अगर
पूर्ण

#घोषणा GTA02_CHARGER_CONFIGURE_TIMEOUT ((3000 * HZ) / 1000)

अटल व्योम gta02_pmu_event_callback(काष्ठा pcf50633 *pcf, पूर्णांक irq)
अणु
	अगर (irq == PCF50633_IRQ_USBINS) अणु
		schedule_delayed_work(&gta02_अक्षरger_work,
				      GTA02_CHARGER_CONFIGURE_TIMEOUT);

		वापस;
	पूर्ण

	अगर (irq == PCF50633_IRQ_USBREM) अणु
		cancel_delayed_work_sync(&gta02_अक्षरger_work);
		gta02_usb_vbus_draw = 0;
	पूर्ण
पूर्ण

अटल व्योम gta02_udc_vbus_draw(अचिन्हित पूर्णांक ma)
अणु
	अगर (!gta02_pcf)
		वापस;

	gta02_usb_vbus_draw = ma;

	schedule_delayed_work(&gta02_अक्षरger_work,
			      GTA02_CHARGER_CONFIGURE_TIMEOUT);
पूर्ण
#अन्यथा /* !CONFIG_CHARGER_PCF50633 */
#घोषणा gta02_pmu_event_callback	शून्य
#घोषणा gta02_udc_vbus_draw		शून्य
#पूर्ण_अगर

अटल अक्षर *gta02_batteries[] = अणु
	"battery",
पूर्ण;

अटल काष्ठा pcf50633_bl_platक्रमm_data gta02_backlight_data = अणु
	.शेष_brightness = 0x3f,
	.शेष_brightness_limit = 0,
	.ramp_समय = 5,
पूर्ण;

अटल काष्ठा pcf50633_platक्रमm_data gta02_pcf_pdata = अणु
	.resumers = अणु
		[0] =	PCF50633_INT1_USBINS |
			PCF50633_INT1_USBREM |
			PCF50633_INT1_ALARM,
		[1] =	PCF50633_INT2_ONKEYF,
		[2] =	PCF50633_INT3_ONKEY1S,
		[3] =	PCF50633_INT4_LOWSYS |
			PCF50633_INT4_LOWBAT |
			PCF50633_INT4_HIGHTMP,
	पूर्ण,

	.batteries = gta02_batteries,
	.num_batteries = ARRAY_SIZE(gta02_batteries),

	.अक्षरger_reference_current_ma = 1000,

	.backlight_data = &gta02_backlight_data,

	.reg_init_data = अणु
		[PCF50633_REGULATOR_AUTO] = अणु
			.स्थिरraपूर्णांकs = अणु
				.min_uV = 3300000,
				.max_uV = 3300000,
				.valid_modes_mask = REGULATOR_MODE_NORMAL,
				.always_on = 1,
				.apply_uV = 1,
			पूर्ण,
		पूर्ण,
		[PCF50633_REGULATOR_DOWN1] = अणु
			.स्थिरraपूर्णांकs = अणु
				.min_uV = 1300000,
				.max_uV = 1600000,
				.valid_modes_mask = REGULATOR_MODE_NORMAL,
				.always_on = 1,
				.apply_uV = 1,
			पूर्ण,
		पूर्ण,
		[PCF50633_REGULATOR_DOWN2] = अणु
			.स्थिरraपूर्णांकs = अणु
				.min_uV = 1800000,
				.max_uV = 1800000,
				.valid_modes_mask = REGULATOR_MODE_NORMAL,
				.apply_uV = 1,
				.always_on = 1,
			पूर्ण,
		पूर्ण,
		[PCF50633_REGULATOR_HCLDO] = अणु
			.स्थिरraपूर्णांकs = अणु
				.min_uV = 2000000,
				.max_uV = 3300000,
				.valid_modes_mask = REGULATOR_MODE_NORMAL,
				.valid_ops_mask = REGULATOR_CHANGE_VOLTAGE |
						REGULATOR_CHANGE_STATUS,
			पूर्ण,
		पूर्ण,
		[PCF50633_REGULATOR_LDO1] = अणु
			.स्थिरraपूर्णांकs = अणु
				.min_uV = 3300000,
				.max_uV = 3300000,
				.valid_modes_mask = REGULATOR_MODE_NORMAL,
				.valid_ops_mask = REGULATOR_CHANGE_STATUS,
				.apply_uV = 1,
			पूर्ण,
		पूर्ण,
		[PCF50633_REGULATOR_LDO2] = अणु
			.स्थिरraपूर्णांकs = अणु
				.min_uV = 3300000,
				.max_uV = 3300000,
				.valid_modes_mask = REGULATOR_MODE_NORMAL,
				.apply_uV = 1,
			पूर्ण,
		पूर्ण,
		[PCF50633_REGULATOR_LDO3] = अणु
			.स्थिरraपूर्णांकs = अणु
				.min_uV = 3000000,
				.max_uV = 3000000,
				.valid_modes_mask = REGULATOR_MODE_NORMAL,
				.apply_uV = 1,
			पूर्ण,
		पूर्ण,
		[PCF50633_REGULATOR_LDO4] = अणु
			.स्थिरraपूर्णांकs = अणु
				.min_uV = 3200000,
				.max_uV = 3200000,
				.valid_modes_mask = REGULATOR_MODE_NORMAL,
				.valid_ops_mask = REGULATOR_CHANGE_STATUS,
				.apply_uV = 1,
			पूर्ण,
		पूर्ण,
		[PCF50633_REGULATOR_LDO5] = अणु
			.स्थिरraपूर्णांकs = अणु
				.min_uV = 3000000,
				.max_uV = 3000000,
				.valid_modes_mask = REGULATOR_MODE_NORMAL,
				.valid_ops_mask = REGULATOR_CHANGE_STATUS,
				.apply_uV = 1,
			पूर्ण,
		पूर्ण,
		[PCF50633_REGULATOR_LDO6] = अणु
			.स्थिरraपूर्णांकs = अणु
				.min_uV = 3000000,
				.max_uV = 3000000,
				.valid_modes_mask = REGULATOR_MODE_NORMAL,
			पूर्ण,
		पूर्ण,
		[PCF50633_REGULATOR_MEMLDO] = अणु
			.स्थिरraपूर्णांकs = अणु
				.min_uV = 1800000,
				.max_uV = 1800000,
				.valid_modes_mask = REGULATOR_MODE_NORMAL,
			पूर्ण,
		पूर्ण,

	पूर्ण,
	.mbc_event_callback = gta02_pmu_event_callback,
पूर्ण;


/* NOR Flash. */

#घोषणा GTA02_FLASH_BASE	0x18000000 /* GCS3 */
#घोषणा GTA02_FLASH_SIZE	0x200000 /* 2MBytes */

अटल काष्ठा physmap_flash_data gta02_nor_flash_data = अणु
	.width		= 2,
पूर्ण;

अटल काष्ठा resource gta02_nor_flash_resource =
	DEFINE_RES_MEM(GTA02_FLASH_BASE, GTA02_FLASH_SIZE);

अटल काष्ठा platक्रमm_device gta02_nor_flash = अणु
	.name		= "physmap-flash",
	.id		= 0,
	.dev		= अणु
		.platक्रमm_data	= &gta02_nor_flash_data,
	पूर्ण,
	.resource	= &gta02_nor_flash_resource,
	.num_resources	= 1,
पूर्ण;


अटल काष्ठा platक्रमm_device s3c24xx_pwm_device = अणु
	.name		= "s3c24xx_pwm",
	.num_resources	= 0,
पूर्ण;

अटल काष्ठा platक्रमm_device gta02_dfbmcs320_device = अणु
	.name = "dfbmcs320",
पूर्ण;

अटल काष्ठा i2c_board_info gta02_i2c_devs[] __initdata = अणु
	अणु
		I2C_BOARD_INFO("pcf50633", 0x73),
		.irq = GTA02_IRQ_PCF50633,
		.platक्रमm_data = &gta02_pcf_pdata,
	पूर्ण,
	अणु
		I2C_BOARD_INFO("wm8753", 0x1a),
	पूर्ण,
पूर्ण;

अटल काष्ठा s3c2410_nand_set __initdata gta02_nand_sets[] = अणु
	[0] = अणु
		/*
		 * This name is also hard-coded in the boot loaders, so
		 * changing it would would require all users to upgrade
		 * their boot loaders, some of which are stored in a NOR
		 * that is considered to be immutable.
		 */
		.name		= "neo1973-nand",
		.nr_chips	= 1,
		.flash_bbt	= 1,
	पूर्ण,
पूर्ण;

/*
 * Choose a set of timings derived from S3C@2442B MCP54
 * data sheet (K5D2G13ACM-D075 MCP Memory).
 */

अटल काष्ठा s3c2410_platक्रमm_nand __initdata gta02_nand_info = अणु
	.tacls		= 0,
	.twrph0		= 25,
	.twrph1		= 15,
	.nr_sets	= ARRAY_SIZE(gta02_nand_sets),
	.sets		= gta02_nand_sets,
	.engine_type	= न_अंकD_ECC_ENGINE_TYPE_SOFT,
पूर्ण;


/* Get PMU to set USB current limit accordingly. */
अटल काष्ठा s3c2410_udc_mach_info gta02_udc_cfg __initdata = अणु
	.vbus_draw	= gta02_udc_vbus_draw,
	.pullup_pin = GTA02_GPIO_USB_PULLUP,
पूर्ण;

/* USB */
अटल काष्ठा s3c2410_hcd_info gta02_usb_info __initdata = अणु
	.port[0]	= अणु
		.flags	= S3C_HCDFLG_USED,
	पूर्ण,
	.port[1]	= अणु
		.flags	= 0,
	पूर्ण,
पूर्ण;

/* Touchscreen */
अटल काष्ठा s3c2410_ts_mach_info gta02_ts_info = अणु
	.delay			= 10000,
	.presc			= 0xff, /* slow as we can go */
	.oversampling_shअगरt	= 2,
पूर्ण;

/* Buttons */
अटल काष्ठा gpio_keys_button gta02_buttons[] = अणु
	अणु
		.gpio = GTA02_GPIO_AUX_KEY,
		.code = KEY_PHONE,
		.desc = "Aux",
		.type = EV_KEY,
		.debounce_पूर्णांकerval = 100,
	पूर्ण,
	अणु
		.gpio = GTA02_GPIO_HOLD_KEY,
		.code = KEY_PAUSE,
		.desc = "Hold",
		.type = EV_KEY,
		.debounce_पूर्णांकerval = 100,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_keys_platक्रमm_data gta02_buttons_pdata = अणु
	.buttons = gta02_buttons,
	.nbuttons = ARRAY_SIZE(gta02_buttons),
पूर्ण;

अटल काष्ठा platक्रमm_device gta02_buttons_device = अणु
	.name = "gpio-keys",
	.id = -1,
	.dev = अणु
		.platक्रमm_data = &gta02_buttons_pdata,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpiod_lookup_table gta02_audio_gpio_table = अणु
	.dev_id = "neo1973-audio",
	.table = अणु
		GPIO_LOOKUP("GPIOJ", 2, "amp-shut", GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP("GPIOJ", 1, "hp", GPIO_ACTIVE_HIGH),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device gta02_audio = अणु
	.name = "neo1973-audio",
	.id = -1,
पूर्ण;

अटल काष्ठा gpiod_lookup_table gta02_mmc_gpio_table = अणु
	.dev_id = "s3c2410-sdi",
	.table = अणु
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

अटल व्योम __init gta02_map_io(व्योम)
अणु
	s3c24xx_init_io(gta02_iodesc, ARRAY_SIZE(gta02_iodesc));
	s3c24xx_init_uarts(gta02_uartcfgs, ARRAY_SIZE(gta02_uartcfgs));
	s3c24xx_set_समयr_source(S3C24XX_PWM3, S3C24XX_PWM4);
पूर्ण


/* These are the guys that करोn't need to be children of PMU. */

अटल काष्ठा platक्रमm_device *gta02_devices[] __initdata = अणु
	&s3c_device_ohci,
	&s3c_device_wdt,
	&s3c_device_sdi,
	&s3c_device_usbgadget,
	&s3c_device_nand,
	&gta02_nor_flash,
	&s3c24xx_pwm_device,
	&s3c_device_iis,
	&s3c_device_i2c0,
	&gta02_dfbmcs320_device,
	&gta02_buttons_device,
	&s3c_device_adc,
	&s3c_device_ts,
	&gta02_audio,
पूर्ण;

अटल व्योम gta02_घातeroff(व्योम)
अणु
	pcf50633_reg_set_bit_mask(gta02_pcf, PCF50633_REG_OOCSHDWN, 1, 1);
पूर्ण

अटल व्योम __init gta02_machine_init(व्योम)
अणु
	/* Set the panic callback to turn AUX LED on or off. */
	panic_blink = gta02_panic_blink;

	s3c_pm_init();

#अगर_घोषित CONFIG_CHARGER_PCF50633
	INIT_DELAYED_WORK(&gta02_अक्षरger_work, gta02_अक्षरger_worker);
#पूर्ण_अगर

	s3c24xx_udc_set_platdata(&gta02_udc_cfg);
	s3c24xx_ts_set_platdata(&gta02_ts_info);
	s3c_ohci_set_platdata(&gta02_usb_info);
	s3c_nand_set_platdata(&gta02_nand_info);
	s3c_i2c0_set_platdata(शून्य);

	i2c_रेजिस्टर_board_info(0, gta02_i2c_devs, ARRAY_SIZE(gta02_i2c_devs));

	/* Configure the I2S pins (GPE0...GPE4) in correct mode */
	s3c_gpio_cfgall_range(S3C2410_GPE(0), 5, S3C_GPIO_SFN(2),
			      S3C_GPIO_PULL_NONE);

	gpiod_add_lookup_table(&gta02_audio_gpio_table);
	gpiod_add_lookup_table(&gta02_mmc_gpio_table);
	platक्रमm_add_devices(gta02_devices, ARRAY_SIZE(gta02_devices));
	pm_घातer_off = gta02_घातeroff;

	regulator_has_full_स्थिरraपूर्णांकs();
पूर्ण

अटल व्योम __init gta02_init_समय(व्योम)
अणु
	s3c2442_init_घड़ीs(12000000);
	s3c24xx_समयr_init();
पूर्ण

MACHINE_START(NEO1973_GTA02, "GTA02")
	/* Maपूर्णांकainer: Nelson Castillo <arhuaco@freaks-uniकरोs.net> */
	.atag_offset	= 0x100,
	.map_io		= gta02_map_io,
	.init_irq	= s3c2442_init_irq,
	.init_machine	= gta02_machine_init,
	.init_समय	= gta02_init_समय,
MACHINE_END
