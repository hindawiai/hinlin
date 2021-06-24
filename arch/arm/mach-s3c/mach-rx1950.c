<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (c) 2006-2009 Victor Chukhantsev, Denis Grigoriev,
// Copyright (c) 2007-2010 Vasily Khoruzhick
//
// based on smdk2440 written by Ben Dooks

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/memblock.h>
#समावेश <linux/delay.h>
#समावेश <linux/समयr.h>
#समावेश <linux/init.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/serial_s3c.h>
#समावेश <linux/input.h>
#समावेश <linux/gpio_keys.h>
#समावेश <linux/device.h>
#समावेश <linux/pda_घातer.h>
#समावेश <linux/pwm_backlight.h>
#समावेश <linux/pwm.h>
#समावेश <linux/s3c_adc_battery.h>
#समावेश <linux/leds.h>
#समावेश <linux/i2c.h>

#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>

#समावेश <linux/mmc/host.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>

#समावेश <linux/platक्रमm_data/i2c-s3c2410.h>
#समावेश <linux/platक्रमm_data/mmc-s3cmci.h>
#समावेश <linux/platक्रमm_data/mtd-nand-s3c2410.h>
#समावेश <linux/platक्रमm_data/touchscreen-s3c2410.h>
#समावेश <linux/platक्रमm_data/usb-s3c2410_udc.h>
#समावेश <linux/platक्रमm_data/fb-s3c2410.h>

#समावेश <sound/uda1380.h>

#समावेश "hardware-s3c24xx.h"
#समावेश "regs-gpio.h"
#समावेश "gpio-samsung.h"

#समावेश "cpu.h"
#समावेश "devs.h"
#समावेश "pm.h"
#समावेश "gpio-cfg.h"

#समावेश "s3c24xx.h"
#समावेश "h1940.h"

#घोषणा LCD_PWM_PERIOD 192960
#घोषणा LCD_PWM_DUTY 127353

अटल काष्ठा map_desc rx1950_iodesc[] __initdata = अणु
पूर्ण;

अटल काष्ठा s3c2410_uartcfg rx1950_uartcfgs[] __initdata = अणु
	[0] = अणु
	       .hwport = 0,
	       .flags = 0,
	       .ucon = 0x3c5,
	       .ulcon = 0x03,
	       .ufcon = 0x51,
		.clk_sel = S3C2410_UCON_CLKSEL3,
	पूर्ण,
	[1] = अणु
	       .hwport = 1,
	       .flags = 0,
	       .ucon = 0x3c5,
	       .ulcon = 0x03,
	       .ufcon = 0x51,
		.clk_sel = S3C2410_UCON_CLKSEL3,
	पूर्ण,
	/* IR port */
	[2] = अणु
	       .hwport = 2,
	       .flags = 0,
	       .ucon = 0x3c5,
	       .ulcon = 0x43,
	       .ufcon = 0xf1,
		.clk_sel = S3C2410_UCON_CLKSEL3,
	पूर्ण,
पूर्ण;

अटल काष्ठा s3c2410fb_display rx1950_display = अणु
	.type = S3C2410_LCDCON1_TFT,
	.width = 240,
	.height = 320,
	.xres = 240,
	.yres = 320,
	.bpp = 16,

	.pixघड़ी = 260000,
	.left_margin = 10,
	.right_margin = 20,
	.hsync_len = 10,
	.upper_margin = 2,
	.lower_margin = 2,
	.vsync_len = 2,

	.lcdcon5 = S3C2410_LCDCON5_FRM565 |
			   S3C2410_LCDCON5_INVVCLK |
			   S3C2410_LCDCON5_INVVLINE |
			   S3C2410_LCDCON5_INVVFRAME |
			   S3C2410_LCDCON5_HWSWP |
			   (0x02 << 13) |
			   (0x02 << 15),

पूर्ण;

अटल पूर्णांक घातer_supply_init(काष्ठा device *dev)
अणु
	वापस gpio_request(S3C2410_GPF(2), "cable plugged");
पूर्ण

अटल पूर्णांक rx1950_is_ac_online(व्योम)
अणु
	वापस !gpio_get_value(S3C2410_GPF(2));
पूर्ण

अटल व्योम घातer_supply_निकास(काष्ठा device *dev)
अणु
	gpio_मुक्त(S3C2410_GPF(2));
पूर्ण

अटल अक्षर *rx1950_supplicants[] = अणु
	"main-battery"
पूर्ण;

अटल काष्ठा pda_घातer_pdata घातer_supply_info = अणु
	.init			= घातer_supply_init,
	.is_ac_online		= rx1950_is_ac_online,
	.निकास			= घातer_supply_निकास,
	.supplied_to		= rx1950_supplicants,
	.num_supplicants	= ARRAY_SIZE(rx1950_supplicants),
पूर्ण;

अटल काष्ठा resource घातer_supply_resources[] = अणु
	[0] = DEFINE_RES_NAMED(IRQ_EINT2, 1, "ac", IORESOURCE_IRQ \
			| IORESOURCE_IRQ_LOWEDGE | IORESOURCE_IRQ_HIGHEDGE),
पूर्ण;

अटल काष्ठा platक्रमm_device घातer_supply = अणु
	.name			= "pda-power",
	.id			= -1,
	.dev			= अणु
					.platक्रमm_data =
						&घातer_supply_info,
	पूर्ण,
	.resource		= घातer_supply_resources,
	.num_resources		= ARRAY_SIZE(घातer_supply_resources),
पूर्ण;

अटल स्थिर काष्ठा s3c_adc_bat_thresh bat_lut_noac[] = अणु
	अणु .volt = 4100, .cur = 156, .level = 100पूर्ण,
	अणु .volt = 4050, .cur = 156, .level = 95पूर्ण,
	अणु .volt = 4025, .cur = 141, .level = 90पूर्ण,
	अणु .volt = 3995, .cur = 144, .level = 85पूर्ण,
	अणु .volt = 3957, .cur = 162, .level = 80पूर्ण,
	अणु .volt = 3931, .cur = 147, .level = 75पूर्ण,
	अणु .volt = 3902, .cur = 147, .level = 70पूर्ण,
	अणु .volt = 3863, .cur = 153, .level = 65पूर्ण,
	अणु .volt = 3838, .cur = 150, .level = 60पूर्ण,
	अणु .volt = 3800, .cur = 153, .level = 55पूर्ण,
	अणु .volt = 3765, .cur = 153, .level = 50पूर्ण,
	अणु .volt = 3748, .cur = 172, .level = 45पूर्ण,
	अणु .volt = 3740, .cur = 153, .level = 40पूर्ण,
	अणु .volt = 3714, .cur = 175, .level = 35पूर्ण,
	अणु .volt = 3710, .cur = 156, .level = 30पूर्ण,
	अणु .volt = 3963, .cur = 156, .level = 25पूर्ण,
	अणु .volt = 3672, .cur = 178, .level = 20पूर्ण,
	अणु .volt = 3651, .cur = 178, .level = 15पूर्ण,
	अणु .volt = 3629, .cur = 178, .level = 10पूर्ण,
	अणु .volt = 3612, .cur = 162, .level = 5पूर्ण,
	अणु .volt = 3605, .cur = 162, .level = 0पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा s3c_adc_bat_thresh bat_lut_acin[] = अणु
	अणु .volt = 4200, .cur = 0, .level = 100पूर्ण,
	अणु .volt = 4190, .cur = 0, .level = 99पूर्ण,
	अणु .volt = 4178, .cur = 0, .level = 95पूर्ण,
	अणु .volt = 4110, .cur = 0, .level = 70पूर्ण,
	अणु .volt = 4076, .cur = 0, .level = 65पूर्ण,
	अणु .volt = 4046, .cur = 0, .level = 60पूर्ण,
	अणु .volt = 4021, .cur = 0, .level = 55पूर्ण,
	अणु .volt = 3999, .cur = 0, .level = 50पूर्ण,
	अणु .volt = 3982, .cur = 0, .level = 45पूर्ण,
	अणु .volt = 3965, .cur = 0, .level = 40पूर्ण,
	अणु .volt = 3957, .cur = 0, .level = 35पूर्ण,
	अणु .volt = 3948, .cur = 0, .level = 30पूर्ण,
	अणु .volt = 3936, .cur = 0, .level = 25पूर्ण,
	अणु .volt = 3927, .cur = 0, .level = 20पूर्ण,
	अणु .volt = 3906, .cur = 0, .level = 15पूर्ण,
	अणु .volt = 3880, .cur = 0, .level = 10पूर्ण,
	अणु .volt = 3829, .cur = 0, .level = 5पूर्ण,
	अणु .volt = 3820, .cur = 0, .level = 0पूर्ण,
पूर्ण;

अटल काष्ठा gpiod_lookup_table rx1950_bat_gpio_table = अणु
	.dev_id = "s3c-adc-battery",
	.table = अणु
		/* Charge status S3C2410_GPF(3) */
		GPIO_LOOKUP("GPIOF", 3, "charge-status", GPIO_ACTIVE_HIGH),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक rx1950_bat_init(व्योम)
अणु
	पूर्णांक ret;

	ret = gpio_request(S3C2410_GPJ(2), "rx1950-charger-enable-1");
	अगर (ret)
		जाओ err_gpio1;
	ret = gpio_request(S3C2410_GPJ(3), "rx1950-charger-enable-2");
	अगर (ret)
		जाओ err_gpio2;

	वापस 0;

err_gpio2:
	gpio_मुक्त(S3C2410_GPJ(2));
err_gpio1:
	वापस ret;
पूर्ण

अटल व्योम rx1950_bat_निकास(व्योम)
अणु
	gpio_मुक्त(S3C2410_GPJ(2));
	gpio_मुक्त(S3C2410_GPJ(3));
पूर्ण

अटल व्योम rx1950_enable_अक्षरger(व्योम)
अणु
	gpio_direction_output(S3C2410_GPJ(2), 1);
	gpio_direction_output(S3C2410_GPJ(3), 1);
पूर्ण

अटल व्योम rx1950_disable_अक्षरger(व्योम)
अणु
	gpio_direction_output(S3C2410_GPJ(2), 0);
	gpio_direction_output(S3C2410_GPJ(3), 0);
पूर्ण

अटल DEFINE_SPINLOCK(rx1950_blink_spin);

अटल पूर्णांक rx1950_led_blink_set(काष्ठा gpio_desc *desc, पूर्णांक state,
	अचिन्हित दीर्घ *delay_on, अचिन्हित दीर्घ *delay_off)
अणु
	पूर्णांक gpio = desc_to_gpio(desc);
	पूर्णांक blink_gpio, check_gpio;

	चयन (gpio) अणु
	हाल S3C2410_GPA(6):
		blink_gpio = S3C2410_GPA(4);
		check_gpio = S3C2410_GPA(3);
		अवरोध;
	हाल S3C2410_GPA(7):
		blink_gpio = S3C2410_GPA(3);
		check_gpio = S3C2410_GPA(4);
		अवरोध;
	शेष:
		वापस -EINVAL;
		अवरोध;
	पूर्ण

	अगर (delay_on && delay_off && !*delay_on && !*delay_off)
		*delay_on = *delay_off = 500;

	spin_lock(&rx1950_blink_spin);

	चयन (state) अणु
	हाल GPIO_LED_NO_BLINK_LOW:
	हाल GPIO_LED_NO_BLINK_HIGH:
		अगर (!gpio_get_value(check_gpio))
			gpio_set_value(S3C2410_GPJ(6), 0);
		gpio_set_value(blink_gpio, 0);
		gpio_set_value(gpio, state);
		अवरोध;
	हाल GPIO_LED_BLINK:
		gpio_set_value(gpio, 0);
		gpio_set_value(S3C2410_GPJ(6), 1);
		gpio_set_value(blink_gpio, 1);
		अवरोध;
	पूर्ण

	spin_unlock(&rx1950_blink_spin);

	वापस 0;
पूर्ण

अटल काष्ठा gpio_led rx1950_leds_desc[] = अणु
	अणु
		.name			= "Green",
		.शेष_trigger	= "main-battery-full",
		.gpio			= S3C2410_GPA(6),
		.retain_state_suspended	= 1,
	पूर्ण,
	अणु
		.name			= "Red",
		.शेष_trigger
			= "main-battery-charging-blink-full-solid",
		.gpio			= S3C2410_GPA(7),
		.retain_state_suspended	= 1,
	पूर्ण,
	अणु
		.name			= "Blue",
		.शेष_trigger	= "rx1950-acx-mem",
		.gpio			= S3C2410_GPA(11),
		.retain_state_suspended	= 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_led_platक्रमm_data rx1950_leds_pdata = अणु
	.num_leds	= ARRAY_SIZE(rx1950_leds_desc),
	.leds		= rx1950_leds_desc,
	.gpio_blink_set	= rx1950_led_blink_set,
पूर्ण;

अटल काष्ठा platक्रमm_device rx1950_leds = अणु
	.name	= "leds-gpio",
	.id		= -1,
	.dev	= अणु
				.platक्रमm_data = &rx1950_leds_pdata,
	पूर्ण,
पूर्ण;

अटल काष्ठा s3c_adc_bat_pdata rx1950_bat_cfg = अणु
	.init = rx1950_bat_init,
	.निकास = rx1950_bat_निकास,
	.enable_अक्षरger = rx1950_enable_अक्षरger,
	.disable_अक्षरger = rx1950_disable_अक्षरger,
	.lut_noac = bat_lut_noac,
	.lut_noac_cnt = ARRAY_SIZE(bat_lut_noac),
	.lut_acin = bat_lut_acin,
	.lut_acin_cnt = ARRAY_SIZE(bat_lut_acin),
	.volt_channel = 0,
	.current_channel = 1,
	.volt_mult = 4235,
	.current_mult = 2900,
	.पूर्णांकernal_impedance = 200,
पूर्ण;

अटल काष्ठा platक्रमm_device rx1950_battery = अणु
	.name             = "s3c-adc-battery",
	.id               = -1,
	.dev = अणु
		.parent = &s3c_device_adc.dev,
		.platक्रमm_data = &rx1950_bat_cfg,
	पूर्ण,
पूर्ण;

अटल काष्ठा s3c2410fb_mach_info rx1950_lcd_cfg = अणु
	.displays = &rx1950_display,
	.num_displays = 1,
	.शेष_display = 0,

	.lpcsel = 0x02,
	.gpccon = 0xaa9556a9,
	.gpccon_mask = 0xffc003fc,
	.gpccon_reg = S3C2410_GPCCON,
	.gpcup = 0x0000ffff,
	.gpcup_mask = 0xffffffff,
	.gpcup_reg = S3C2410_GPCUP,

	.gpdcon = 0xaa90aaa1,
	.gpdcon_mask = 0xffc0fff0,
	.gpdcon_reg = S3C2410_GPDCON,
	.gpdup = 0x0000fcfd,
	.gpdup_mask = 0xffffffff,
	.gpdup_reg = S3C2410_GPDUP,
पूर्ण;

अटल काष्ठा pwm_lookup rx1950_pwm_lookup[] = अणु
	PWM_LOOKUP("samsung-pwm", 0, "pwm-backlight.0", शून्य, 48000,
		   PWM_POLARITY_NORMAL),
	PWM_LOOKUP("samsung-pwm", 1, "pwm-backlight.0", "RX1950 LCD", LCD_PWM_PERIOD,
		   PWM_POLARITY_NORMAL),
पूर्ण;

अटल काष्ठा pwm_device *lcd_pwm;
अटल काष्ठा pwm_state lcd_pwm_state;

अटल व्योम rx1950_lcd_घातer(पूर्णांक enable)
अणु
	पूर्णांक i;
	अटल पूर्णांक enabled;
	अगर (enabled == enable)
		वापस;
	अगर (!enable) अणु

		/* GPC11-GPC15->OUTPUT */
		क्रम (i = 11; i < 16; i++)
			gpio_direction_output(S3C2410_GPC(i), 1);

		/* Wait a bit here... */
		mdelay(100);

		/* GPD2-GPD7->OUTPUT */
		/* GPD11-GPD15->OUTPUT */
		/* GPD2-GPD7->1, GPD11-GPD15->1 */
		क्रम (i = 2; i < 8; i++)
			gpio_direction_output(S3C2410_GPD(i), 1);
		क्रम (i = 11; i < 16; i++)
			gpio_direction_output(S3C2410_GPD(i), 1);

		/* Wait a bit here...*/
		mdelay(100);

		/* GPB0->OUTPUT, GPB0->0 */
		gpio_direction_output(S3C2410_GPB(0), 0);

		/* GPC1-GPC4->OUTPUT, GPC1-4->0 */
		क्रम (i = 1; i < 5; i++)
			gpio_direction_output(S3C2410_GPC(i), 0);

		/* GPC15-GPC11->0 */
		क्रम (i = 11; i < 16; i++)
			gpio_direction_output(S3C2410_GPC(i), 0);

		/* GPD15-GPD11->0, GPD2->GPD7->0 */
		क्रम (i = 11; i < 16; i++)
			gpio_direction_output(S3C2410_GPD(i), 0);

		क्रम (i = 2; i < 8; i++)
			gpio_direction_output(S3C2410_GPD(i), 0);

		/* GPC6->0, GPC7->0, GPC5->0 */
		gpio_direction_output(S3C2410_GPC(6), 0);
		gpio_direction_output(S3C2410_GPC(7), 0);
		gpio_direction_output(S3C2410_GPC(5), 0);

		/* GPB1->OUTPUT, GPB1->0 */
		gpio_direction_output(S3C2410_GPB(1), 0);

		lcd_pwm_state.enabled = false;
		pwm_apply_state(lcd_pwm, &lcd_pwm_state);

		/* GPC0->0, GPC10->0 */
		gpio_direction_output(S3C2410_GPC(0), 0);
		gpio_direction_output(S3C2410_GPC(10), 0);
	पूर्ण अन्यथा अणु
		lcd_pwm_state.enabled = true;
		pwm_apply_state(lcd_pwm, &lcd_pwm_state);

		gpio_direction_output(S3C2410_GPC(0), 1);
		gpio_direction_output(S3C2410_GPC(5), 1);

		s3c_gpio_cfgpin(S3C2410_GPB(1), S3C2410_GPB1_TOUT1);
		gpio_direction_output(S3C2410_GPC(7), 1);

		क्रम (i = 1; i < 5; i++)
			s3c_gpio_cfgpin(S3C2410_GPC(i), S3C_GPIO_SFN(2));

		क्रम (i = 11; i < 16; i++)
			s3c_gpio_cfgpin(S3C2410_GPC(i), S3C_GPIO_SFN(2));

		क्रम (i = 2; i < 8; i++)
			s3c_gpio_cfgpin(S3C2410_GPD(i), S3C_GPIO_SFN(2));

		क्रम (i = 11; i < 16; i++)
			s3c_gpio_cfgpin(S3C2410_GPD(i), S3C_GPIO_SFN(2));

		gpio_direction_output(S3C2410_GPC(10), 1);
		gpio_direction_output(S3C2410_GPC(6), 1);
	पूर्ण
	enabled = enable;
पूर्ण

अटल व्योम rx1950_bl_घातer(पूर्णांक enable)
अणु
	अटल पूर्णांक enabled;
	अगर (enabled == enable)
		वापस;
	अगर (!enable) अणु
			gpio_direction_output(S3C2410_GPB(0), 0);
	पूर्ण अन्यथा अणु
			/* LED driver need a "push" to घातer on */
			gpio_direction_output(S3C2410_GPB(0), 1);
			/* Warm up backlight क्रम one period of PWM.
			 * Without this trick its almost impossible to
			 * enable backlight with low brightness value
			 */
			ndelay(48000);
			s3c_gpio_cfgpin(S3C2410_GPB(0), S3C2410_GPB0_TOUT0);
	पूर्ण
	enabled = enable;
पूर्ण

अटल पूर्णांक rx1950_backlight_init(काष्ठा device *dev)
अणु
	WARN_ON(gpio_request(S3C2410_GPB(0), "Backlight"));
	lcd_pwm = pwm_get(dev, "RX1950 LCD");
	अगर (IS_ERR(lcd_pwm)) अणु
		dev_err(dev, "Unable to request PWM for LCD power!\n");
		वापस PTR_ERR(lcd_pwm);
	पूर्ण

	/*
	 * Call pwm_init_state to initialize .polarity and .period. The other
	 * values are fixed in this driver.
	 */
	pwm_init_state(lcd_pwm, &lcd_pwm_state);

	lcd_pwm_state.duty_cycle = LCD_PWM_DUTY;

	rx1950_lcd_घातer(1);
	rx1950_bl_घातer(1);

	वापस 0;
पूर्ण

अटल व्योम rx1950_backlight_निकास(काष्ठा device *dev)
अणु
	rx1950_bl_घातer(0);
	rx1950_lcd_घातer(0);

	pwm_put(lcd_pwm);
	gpio_मुक्त(S3C2410_GPB(0));
पूर्ण


अटल पूर्णांक rx1950_backlight_notअगरy(काष्ठा device *dev, पूर्णांक brightness)
अणु
	अगर (!brightness) अणु
		rx1950_bl_घातer(0);
		rx1950_lcd_घातer(0);
	पूर्ण अन्यथा अणु
		rx1950_lcd_घातer(1);
		rx1950_bl_घातer(1);
	पूर्ण
	वापस brightness;
पूर्ण

अटल काष्ठा platक्रमm_pwm_backlight_data rx1950_backlight_data = अणु
	.max_brightness = 24,
	.dft_brightness = 4,
	.init = rx1950_backlight_init,
	.notअगरy = rx1950_backlight_notअगरy,
	.निकास = rx1950_backlight_निकास,
पूर्ण;

अटल काष्ठा platक्रमm_device rx1950_backlight = अणु
	.name = "pwm-backlight",
	.dev = अणु
		.parent = &samsung_device_pwm.dev,
		.platक्रमm_data = &rx1950_backlight_data,
	पूर्ण,
पूर्ण;

अटल व्योम rx1950_set_mmc_घातer(अचिन्हित अक्षर घातer_mode, अचिन्हित लघु vdd)
अणु
	s3c24xx_mci_def_set_घातer(घातer_mode, vdd);

	चयन (घातer_mode) अणु
	हाल MMC_POWER_OFF:
		gpio_direction_output(S3C2410_GPJ(1), 0);
		अवरोध;
	हाल MMC_POWER_UP:
	हाल MMC_POWER_ON:
		gpio_direction_output(S3C2410_GPJ(1), 1);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल काष्ठा s3c24xx_mci_pdata rx1950_mmc_cfg __initdata = अणु
	.set_घातer = rx1950_set_mmc_घातer,
	.ocr_avail = MMC_VDD_32_33,
पूर्ण;

अटल काष्ठा gpiod_lookup_table rx1950_mmc_gpio_table = अणु
	.dev_id = "s3c2410-sdi",
	.table = अणु
		/* Card detect S3C2410_GPF(5) */
		GPIO_LOOKUP("GPIOF", 5, "cd", GPIO_ACTIVE_LOW),
		/* Write protect S3C2410_GPH(8) */
		GPIO_LOOKUP("GPIOH", 8, "wp", GPIO_ACTIVE_LOW),
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

अटल काष्ठा mtd_partition rx1950_nand_part[] = अणु
	[0] = अणु
			.name = "Boot0",
			.offset = 0,
			.size = 0x4000,
			.mask_flags = MTD_WRITEABLE,
	पूर्ण,
	[1] = अणु
			.name = "Boot1",
			.offset = MTDPART_OFS_APPEND,
			.size = 0x40000,
			.mask_flags = MTD_WRITEABLE,
	पूर्ण,
	[2] = अणु
			.name = "Kernel",
			.offset = MTDPART_OFS_APPEND,
			.size = 0x300000,
			.mask_flags = 0,
	पूर्ण,
	[3] = अणु
			.name = "Filesystem",
			.offset = MTDPART_OFS_APPEND,
			.size = MTDPART_SIZ_FULL,
			.mask_flags = 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा s3c2410_nand_set rx1950_nand_sets[] = अणु
	[0] = अणु
			.name = "Internal",
			.nr_chips = 1,
			.nr_partitions = ARRAY_SIZE(rx1950_nand_part),
			.partitions = rx1950_nand_part,
	पूर्ण,
पूर्ण;

अटल काष्ठा s3c2410_platक्रमm_nand rx1950_nand_info = अणु
	.tacls = 25,
	.twrph0 = 50,
	.twrph1 = 15,
	.nr_sets = ARRAY_SIZE(rx1950_nand_sets),
	.sets = rx1950_nand_sets,
	.engine_type = न_अंकD_ECC_ENGINE_TYPE_SOFT,
पूर्ण;

अटल काष्ठा s3c2410_udc_mach_info rx1950_udc_cfg __initdata = अणु
	.vbus_pin = S3C2410_GPG(5),
	.vbus_pin_inverted = 1,
	.pullup_pin = S3C2410_GPJ(5),
पूर्ण;

अटल काष्ठा s3c2410_ts_mach_info rx1950_ts_cfg __initdata = अणु
	.delay = 10000,
	.presc = 49,
	.oversampling_shअगरt = 3,
पूर्ण;

अटल काष्ठा gpio_keys_button rx1950_gpio_keys_table[] = अणु
	अणु
		.code		= KEY_POWER,
		.gpio		= S3C2410_GPF(0),
		.active_low	= 1,
		.desc		= "Power button",
		.wakeup		= 1,
	पूर्ण,
	अणु
		.code		= KEY_F5,
		.gpio		= S3C2410_GPF(7),
		.active_low	= 1,
		.desc		= "Record button",
	पूर्ण,
	अणु
		.code		= KEY_F1,
		.gpio		= S3C2410_GPG(0),
		.active_low	= 1,
		.desc		= "Calendar button",
	पूर्ण,
	अणु
		.code		= KEY_F2,
		.gpio		= S3C2410_GPG(2),
		.active_low	= 1,
		.desc		= "Contacts button",
	पूर्ण,
	अणु
		.code		= KEY_F3,
		.gpio		= S3C2410_GPG(3),
		.active_low	= 1,
		.desc		= "Mail button",
	पूर्ण,
	अणु
		.code		= KEY_F4,
		.gpio		= S3C2410_GPG(7),
		.active_low	= 1,
		.desc		= "WLAN button",
	पूर्ण,
	अणु
		.code		= KEY_LEFT,
		.gpio		= S3C2410_GPG(10),
		.active_low	= 1,
		.desc		= "Left button",
	पूर्ण,
	अणु
		.code		= KEY_RIGHT,
		.gpio		= S3C2410_GPG(11),
		.active_low	= 1,
		.desc		= "Right button",
	पूर्ण,
	अणु
		.code		= KEY_UP,
		.gpio		= S3C2410_GPG(4),
		.active_low	= 1,
		.desc		= "Up button",
	पूर्ण,
	अणु
		.code		= KEY_DOWN,
		.gpio		= S3C2410_GPG(6),
		.active_low	= 1,
		.desc		= "Down button",
	पूर्ण,
	अणु
		.code		= KEY_ENTER,
		.gpio		= S3C2410_GPG(9),
		.active_low	= 1,
		.desc		= "Ok button"
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_keys_platक्रमm_data rx1950_gpio_keys_data = अणु
	.buttons = rx1950_gpio_keys_table,
	.nbuttons = ARRAY_SIZE(rx1950_gpio_keys_table),
पूर्ण;

अटल काष्ठा platक्रमm_device rx1950_device_gpiokeys = अणु
	.name = "gpio-keys",
	.dev.platक्रमm_data = &rx1950_gpio_keys_data,
पूर्ण;

अटल काष्ठा uda1380_platक्रमm_data uda1380_info = अणु
	.gpio_घातer	= S3C2410_GPJ(0),
	.gpio_reset	= S3C2410_GPD(0),
	.dac_clk	= UDA1380_DAC_CLK_SYSCLK,
पूर्ण;

अटल काष्ठा i2c_board_info rx1950_i2c_devices[] = अणु
	अणु
		I2C_BOARD_INFO("uda1380", 0x1a),
		.platक्रमm_data = &uda1380_info,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpiod_lookup_table rx1950_audio_gpio_table = अणु
	.dev_id = "rx1950-audio",
	.table = अणु
		GPIO_LOOKUP("GPIOG", 12, "hp-gpio", GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP("GPIOA", 1, "speaker-power", GPIO_ACTIVE_HIGH),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device rx1950_audio = अणु
	.name = "rx1950-audio",
	.id = -1,
पूर्ण;

अटल काष्ठा platक्रमm_device *rx1950_devices[] __initdata = अणु
	&s3c2410_device_dclk,
	&s3c_device_lcd,
	&s3c_device_wdt,
	&s3c_device_i2c0,
	&s3c_device_iis,
	&s3c_device_usbgadget,
	&s3c_device_rtc,
	&s3c_device_nand,
	&s3c_device_sdi,
	&s3c_device_adc,
	&s3c_device_ts,
	&samsung_device_pwm,
	&rx1950_backlight,
	&rx1950_device_gpiokeys,
	&घातer_supply,
	&rx1950_battery,
	&rx1950_leds,
	&rx1950_audio,
पूर्ण;

अटल व्योम __init rx1950_map_io(व्योम)
अणु
	s3c24xx_init_io(rx1950_iodesc, ARRAY_SIZE(rx1950_iodesc));
	s3c24xx_init_uarts(rx1950_uartcfgs, ARRAY_SIZE(rx1950_uartcfgs));
	s3c24xx_set_समयr_source(S3C24XX_PWM3, S3C24XX_PWM4);

	/* setup PM */

#अगर_घोषित CONFIG_PM_H1940
	स_नकल(phys_to_virt(H1940_SUSPEND_RESUMEAT), h1940_pm_वापस, 8);
#पूर्ण_अगर

	s3c_pm_init();
पूर्ण

अटल व्योम __init rx1950_init_समय(व्योम)
अणु
	s3c2442_init_घड़ीs(16934000);
	s3c24xx_समयr_init();
पूर्ण

अटल व्योम __init rx1950_init_machine(व्योम)
अणु
	पूर्णांक i;

	s3c24xx_fb_set_platdata(&rx1950_lcd_cfg);
	s3c24xx_udc_set_platdata(&rx1950_udc_cfg);
	s3c24xx_ts_set_platdata(&rx1950_ts_cfg);
	gpiod_add_lookup_table(&rx1950_mmc_gpio_table);
	s3c24xx_mci_set_platdata(&rx1950_mmc_cfg);
	s3c_i2c0_set_platdata(शून्य);
	s3c_nand_set_platdata(&rx1950_nand_info);

	/* Turn off suspend on both USB ports, and चयन the
	 * selectable USB port to USB device mode. */
	s3c2410_modअगरy_misccr(S3C2410_MISCCR_USBHOST |
						S3C2410_MISCCR_USBSUSPND0 |
						S3C2410_MISCCR_USBSUSPND1, 0x0);

	/* mmc घातer is disabled by शेष */
	WARN_ON(gpio_request(S3C2410_GPJ(1), "MMC power"));
	gpio_direction_output(S3C2410_GPJ(1), 0);

	क्रम (i = 0; i < 8; i++)
		WARN_ON(gpio_request(S3C2410_GPC(i), "LCD power"));

	क्रम (i = 10; i < 16; i++)
		WARN_ON(gpio_request(S3C2410_GPC(i), "LCD power"));

	क्रम (i = 2; i < 8; i++)
		WARN_ON(gpio_request(S3C2410_GPD(i), "LCD power"));

	क्रम (i = 11; i < 16; i++)
		WARN_ON(gpio_request(S3C2410_GPD(i), "LCD power"));

	WARN_ON(gpio_request(S3C2410_GPB(1), "LCD power"));

	WARN_ON(gpio_request(S3C2410_GPA(3), "Red blink"));
	WARN_ON(gpio_request(S3C2410_GPA(4), "Green blink"));
	WARN_ON(gpio_request(S3C2410_GPJ(6), "LED blink"));
	gpio_direction_output(S3C2410_GPA(3), 0);
	gpio_direction_output(S3C2410_GPA(4), 0);
	gpio_direction_output(S3C2410_GPJ(6), 0);

	pwm_add_table(rx1950_pwm_lookup, ARRAY_SIZE(rx1950_pwm_lookup));
	gpiod_add_lookup_table(&rx1950_audio_gpio_table);
	gpiod_add_lookup_table(&rx1950_bat_gpio_table);
	/* Configure the I2S pins (GPE0...GPE4) in correct mode */
	s3c_gpio_cfgall_range(S3C2410_GPE(0), 5, S3C_GPIO_SFN(2),
			      S3C_GPIO_PULL_NONE);
	platक्रमm_add_devices(rx1950_devices, ARRAY_SIZE(rx1950_devices));

	i2c_रेजिस्टर_board_info(0, rx1950_i2c_devices,
		ARRAY_SIZE(rx1950_i2c_devices));
पूर्ण

/* H1940 and RX3715 need to reserve this क्रम suspend */
अटल व्योम __init rx1950_reserve(व्योम)
अणु
	memblock_reserve(0x30003000, 0x1000);
	memblock_reserve(0x30081000, 0x1000);
पूर्ण

MACHINE_START(RX1950, "HP iPAQ RX1950")
    /* Maपूर्णांकainers: Vasily Khoruzhick */
	.atag_offset = 0x100,
	.map_io = rx1950_map_io,
	.reserve	= rx1950_reserve,
	.init_irq	= s3c2442_init_irq,
	.init_machine = rx1950_init_machine,
	.init_समय	= rx1950_init_समय,
MACHINE_END
