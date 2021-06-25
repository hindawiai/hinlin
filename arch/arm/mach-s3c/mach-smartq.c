<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (C) 2010 Maurus Cuelenaere

#समावेश <linux/delay.h>
#समावेश <linux/fb.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pwm.h>
#समावेश <linux/pwm_backlight.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/serial_s3c.h>
#समावेश <linux/spi/spi_gpपन.स>
#समावेश <linux/platक्रमm_data/s3c-hsotg.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/map.h>

#समावेश "map.h"
#समावेश "regs-gpio.h"
#समावेश "gpio-samsung.h"

#समावेश "cpu.h"
#समावेश "devs.h"
#समावेश <linux/platक्रमm_data/i2c-s3c2410.h>
#समावेश "gpio-cfg.h"
#समावेश <linux/platक्रमm_data/hwmon-s3c.h>
#समावेश <linux/platक्रमm_data/usb-ohci-s3c2410.h>
#समावेश "sdhci.h"
#समावेश <linux/platक्रमm_data/touchscreen-s3c2410.h>

#समावेश <video/platक्रमm_lcd.h>

#समावेश "s3c64xx.h"
#समावेश "mach-smartq.h"
#समावेश "regs-modem-s3c64xx.h"

#घोषणा UCON S3C2410_UCON_DEFAULT
#घोषणा ULCON (S3C2410_LCON_CS8 | S3C2410_LCON_PNONE)
#घोषणा UFCON (S3C2410_UFCON_RXTRIG8 | S3C2410_UFCON_FIFOMODE)

अटल काष्ठा s3c2410_uartcfg smartq_uartcfgs[] __initdata = अणु
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
पूर्ण;

अटल व्योम smartq_usb_host_घातercontrol(पूर्णांक port, पूर्णांक to)
अणु
	pr_debug("%s(%d, %d)\n", __func__, port, to);

	अगर (port == 0) अणु
		gpio_set_value(S3C64XX_GPL(0), to);
		gpio_set_value(S3C64XX_GPL(1), to);
	पूर्ण
पूर्ण

अटल irqवापस_t smartq_usb_host_ocirq(पूर्णांक irq, व्योम *pw)
अणु
	काष्ठा s3c2410_hcd_info *info = pw;

	अगर (gpio_get_value(S3C64XX_GPL(10)) == 0) अणु
		pr_debug("%s: over-current irq (oc detected)\n", __func__);
		s3c2410_usb_report_oc(info, 3);
	पूर्ण अन्यथा अणु
		pr_debug("%s: over-current irq (oc cleared)\n", __func__);
		s3c2410_usb_report_oc(info, 0);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम smartq_usb_host_enableoc(काष्ठा s3c2410_hcd_info *info, पूर्णांक on)
अणु
	पूर्णांक ret;

	/* This isn't present on a SmartQ 5 board */
	अगर (machine_is_smartq5())
		वापस;

	अगर (on) अणु
		ret = request_irq(gpio_to_irq(S3C64XX_GPL(10)),
				  smartq_usb_host_ocirq,
				  IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING,
				  "USB host overcurrent", info);
		अगर (ret != 0)
			pr_err("failed to request usb oc irq: %d\n", ret);
	पूर्ण अन्यथा अणु
		मुक्त_irq(gpio_to_irq(S3C64XX_GPL(10)), info);
	पूर्ण
पूर्ण

अटल काष्ठा s3c2410_hcd_info smartq_usb_host_info = अणु
	.port[0]	= अणु
		.flags	= S3C_HCDFLG_USED
	पूर्ण,
	.port[1]	= अणु
		.flags	= 0
	पूर्ण,

	.घातer_control	= smartq_usb_host_घातercontrol,
	.enable_oc	= smartq_usb_host_enableoc,
पूर्ण;

अटल काष्ठा gpiod_lookup_table smartq_usb_otg_vbus_gpiod_table = अणु
	.dev_id = "gpio-vbus",
	.table = अणु
		GPIO_LOOKUP("GPL", 9, "vbus", GPIO_ACTIVE_LOW),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device smartq_usb_otg_vbus_dev = अणु
	.name			= "gpio-vbus",
पूर्ण;

अटल काष्ठा pwm_lookup smartq_pwm_lookup[] = अणु
	PWM_LOOKUP("samsung-pwm", 1, "pwm-backlight.0", शून्य,
		   1000000000 / (1000 * 20), PWM_POLARITY_NORMAL),
पूर्ण;

अटल पूर्णांक smartq_bl_init(काष्ठा device *dev)
अणु
    s3c_gpio_cfgpin(S3C64XX_GPF(15), S3C_GPIO_SFN(2));

    वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_pwm_backlight_data smartq_backlight_data = अणु
	.max_brightness	= 1000,
	.dft_brightness	= 600,
	.init		= smartq_bl_init,
पूर्ण;

अटल काष्ठा platक्रमm_device smartq_backlight_device = अणु
	.name		= "pwm-backlight",
	.dev		= अणु
		.parent	= &samsung_device_pwm.dev,
		.platक्रमm_data = &smartq_backlight_data,
	पूर्ण,
पूर्ण;

अटल काष्ठा s3c2410_ts_mach_info smartq_touchscreen_pdata __initdata = अणु
	.delay			= 65535,
	.presc			= 99,
	.oversampling_shअगरt	= 4,
पूर्ण;

अटल काष्ठा s3c_sdhci_platdata smartq_पूर्णांकernal_hsmmc_pdata = अणु
	.max_width		= 4,
	.cd_type		= S3C_SDHCI_CD_PERMANENT,
पूर्ण;

अटल काष्ठा s3c_hwmon_pdata smartq_hwmon_pdata __initdata = अणु
	/* Battery voltage (?-4.2V) */
	.in[0] = &(काष्ठा s3c_hwmon_chcfg) अणु
		.name		= "smartq:battery-voltage",
		.mult		= 3300,
		.भाग		= 2048,
	पूर्ण,
	/* Reference voltage (1.2V) */
	.in[1] = &(काष्ठा s3c_hwmon_chcfg) अणु
		.name		= "smartq:reference-voltage",
		.mult		= 3300,
		.भाग		= 4096,
	पूर्ण,
पूर्ण;

अटल काष्ठा dwc2_hsotg_plat smartq_hsotg_pdata;

अटल पूर्णांक __init smartq_lcd_setup_gpio(व्योम)
अणु
	पूर्णांक ret;

	ret = gpio_request(S3C64XX_GPM(3), "LCD power");
	अगर (ret < 0)
		वापस ret;

	/* turn घातer off */
	gpio_direction_output(S3C64XX_GPM(3), 0);

	वापस 0;
पूर्ण

/* GPM0 -> CS */
अटल काष्ठा spi_gpio_platक्रमm_data smartq_lcd_control = अणु
	.num_chipselect	= 1,
पूर्ण;

अटल काष्ठा platक्रमm_device smartq_lcd_control_device = अणु
	.name			= "spi_gpio",
	.id			= 1,
	.dev.platक्रमm_data	= &smartq_lcd_control,
पूर्ण;

अटल काष्ठा gpiod_lookup_table smartq_lcd_control_gpiod_table = अणु
	.dev_id         = "spi_gpio",
	.table          = अणु
		GPIO_LOOKUP("GPIOM", 1,
			    "sck", GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP("GPIOM", 2,
			    "mosi", GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP("GPIOM", 3,
			    "miso", GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP("GPIOM", 0,
			    "cs", GPIO_ACTIVE_HIGH),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल व्योम smartq_lcd_घातer_set(काष्ठा plat_lcd_data *pd, अचिन्हित पूर्णांक घातer)
अणु
	gpio_direction_output(S3C64XX_GPM(3), घातer);
पूर्ण

अटल काष्ठा plat_lcd_data smartq_lcd_घातer_data = अणु
	.set_घातer	= smartq_lcd_घातer_set,
पूर्ण;

अटल काष्ठा platक्रमm_device smartq_lcd_घातer_device = अणु
	.name			= "platform-lcd",
	.dev.parent		= &s3c_device_fb.dev,
	.dev.platक्रमm_data	= &smartq_lcd_घातer_data,
पूर्ण;

अटल काष्ठा i2c_board_info smartq_i2c_devs[] __initdata = अणु
	अणु I2C_BOARD_INFO("wm8987", 0x1a), पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device *smartq_devices[] __initdata = अणु
	&s3c_device_hsmmc1,	/* Init iन_अंकD first, ... */
	&s3c_device_hsmmc0,	/* ... then the बाह्यal SD card */
	&s3c_device_hsmmc2,
	&s3c_device_adc,
	&s3c_device_fb,
	&s3c_device_hwmon,
	&s3c_device_i2c0,
	&s3c_device_ohci,
	&s3c_device_rtc,
	&samsung_device_pwm,
	&s3c_device_usb_hsotg,
	&s3c64xx_device_iis0,
	&smartq_backlight_device,
	&smartq_lcd_control_device,
	&smartq_lcd_घातer_device,
	&smartq_usb_otg_vbus_dev,
पूर्ण;

अटल व्योम __init smartq_lcd_mode_set(व्योम)
अणु
	u32 पंचांगp;

	/* set the LCD type */
	पंचांगp = __raw_पढ़ोl(S3C64XX_SPCON);
	पंचांगp &= ~S3C64XX_SPCON_LCD_SEL_MASK;
	पंचांगp |= S3C64XX_SPCON_LCD_SEL_RGB;
	__raw_ग_लिखोl(पंचांगp, S3C64XX_SPCON);

	/* हटाओ the LCD bypass */
	पंचांगp = __raw_पढ़ोl(S3C64XX_MODEM_MIFPCON);
	पंचांगp &= ~MIFPCON_LCD_BYPASS;
	__raw_ग_लिखोl(पंचांगp, S3C64XX_MODEM_MIFPCON);
पूर्ण

अटल व्योम smartq_घातer_off(व्योम)
अणु
	gpio_direction_output(S3C64XX_GPK(15), 1);
पूर्ण

अटल पूर्णांक __init smartq_घातer_off_init(व्योम)
अणु
	पूर्णांक ret;

	ret = gpio_request(S3C64XX_GPK(15), "Power control");
	अगर (ret < 0) अणु
		pr_err("%s: failed to get GPK15\n", __func__);
		वापस ret;
	पूर्ण

	/* leave घातer on */
	gpio_direction_output(S3C64XX_GPK(15), 0);

	pm_घातer_off = smartq_घातer_off;

	वापस ret;
पूर्ण

अटल पूर्णांक __init smartq_usb_host_init(व्योम)
अणु
	पूर्णांक ret;

	ret = gpio_request(S3C64XX_GPL(0), "USB power control");
	अगर (ret < 0) अणु
		pr_err("%s: failed to get GPL0\n", __func__);
		वापस ret;
	पूर्ण

	ret = gpio_request(S3C64XX_GPL(1), "USB host power control");
	अगर (ret < 0) अणु
		pr_err("%s: failed to get GPL1\n", __func__);
		जाओ err;
	पूर्ण

	अगर (!machine_is_smartq5()) अणु
		/* This isn't present on a SmartQ 5 board */
		ret = gpio_request(S3C64XX_GPL(10), "USB host overcurrent");
		अगर (ret < 0) अणु
			pr_err("%s: failed to get GPL10\n", __func__);
			जाओ err2;
		पूर्ण
	पूर्ण

	/* turn घातer off */
	gpio_direction_output(S3C64XX_GPL(0), 0);
	gpio_direction_output(S3C64XX_GPL(1), 0);
	अगर (!machine_is_smartq5())
		gpio_direction_input(S3C64XX_GPL(10));

	s3c_device_ohci.dev.platक्रमm_data = &smartq_usb_host_info;

	वापस 0;

err2:
	gpio_मुक्त(S3C64XX_GPL(1));
err:
	gpio_मुक्त(S3C64XX_GPL(0));
	वापस ret;
पूर्ण

अटल पूर्णांक __init smartq_wअगरi_init(व्योम)
अणु
	पूर्णांक ret;

	ret = gpio_request(S3C64XX_GPK(1), "wifi control");
	अगर (ret < 0) अणु
		pr_err("%s: failed to get GPK1\n", __func__);
		वापस ret;
	पूर्ण

	ret = gpio_request(S3C64XX_GPK(2), "wifi reset");
	अगर (ret < 0) अणु
		pr_err("%s: failed to get GPK2\n", __func__);
		gpio_मुक्त(S3C64XX_GPK(1));
		वापस ret;
	पूर्ण

	/* turn घातer on */
	gpio_direction_output(S3C64XX_GPK(1), 1);

	/* reset device */
	gpio_direction_output(S3C64XX_GPK(2), 0);
	mdelay(100);
	gpio_set_value(S3C64XX_GPK(2), 1);
	gpio_direction_input(S3C64XX_GPK(2));

	वापस 0;
पूर्ण

अटल काष्ठा map_desc smartq_iodesc[] __initdata = अणुपूर्ण;
व्योम __init smartq_map_io(व्योम)
अणु
	s3c64xx_init_io(smartq_iodesc, ARRAY_SIZE(smartq_iodesc));
	s3c64xx_set_xtal_freq(12000000);
	s3c64xx_set_xusbxti_freq(12000000);
	s3c24xx_init_uarts(smartq_uartcfgs, ARRAY_SIZE(smartq_uartcfgs));
	s3c64xx_set_समयr_source(S3C64XX_PWM3, S3C64XX_PWM4);

	smartq_lcd_mode_set();
पूर्ण

अटल काष्ठा gpiod_lookup_table smartq_audio_gpios = अणु
	.dev_id = "smartq-audio",
	.table = अणु
		GPIO_LOOKUP("GPL", 12, "headphone detect", 0),
		GPIO_LOOKUP("GPK", 12, "amplifiers shutdown", 0),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

व्योम __init smartq_machine_init(व्योम)
अणु
	s3c_i2c0_set_platdata(शून्य);
	dwc2_hsotg_set_platdata(&smartq_hsotg_pdata);
	s3c_hwmon_set_platdata(&smartq_hwmon_pdata);
	s3c_sdhci1_set_platdata(&smartq_पूर्णांकernal_hsmmc_pdata);
	s3c_sdhci2_set_platdata(&smartq_पूर्णांकernal_hsmmc_pdata);
	s3c64xx_ts_set_platdata(&smartq_touchscreen_pdata);

	i2c_रेजिस्टर_board_info(0, smartq_i2c_devs,
				ARRAY_SIZE(smartq_i2c_devs));

	WARN_ON(smartq_lcd_setup_gpio());
	WARN_ON(smartq_घातer_off_init());
	WARN_ON(smartq_usb_host_init());
	WARN_ON(smartq_wअगरi_init());

	pwm_add_table(smartq_pwm_lookup, ARRAY_SIZE(smartq_pwm_lookup));
	gpiod_add_lookup_table(&smartq_lcd_control_gpiod_table);
	gpiod_add_lookup_table(&smartq_usb_otg_vbus_gpiod_table);
	platक्रमm_add_devices(smartq_devices, ARRAY_SIZE(smartq_devices));

	gpiod_add_lookup_table(&smartq_audio_gpios);
	platक्रमm_device_रेजिस्टर_simple("smartq-audio", -1, शून्य, 0);
पूर्ण
