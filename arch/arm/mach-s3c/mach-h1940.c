<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (c) 2003-2005 Simtec Electronics
//   Ben Dooks <ben@simtec.co.uk>
//
// https://www.handhelds.org/projects/h1940.hपंचांगl

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/memblock.h>
#समावेश <linux/समयr.h>
#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/serial_s3c.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/input.h>
#समावेश <linux/gpio_keys.h>
#समावेश <linux/pwm.h>
#समावेश <linux/pwm_backlight.h>
#समावेश <linux/i2c.h>
#समावेश <linux/leds.h>
#समावेश <linux/pda_घातer.h>
#समावेश <linux/s3c_adc_battery.h>
#समावेश <linux/delay.h>

#समावेश <video/platक्रमm_lcd.h>

#समावेश <linux/mmc/host.h>
#समावेश <linux/export.h>

#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/mach/irq.h>

#समावेश <linux/platक्रमm_data/i2c-s3c2410.h>
#समावेश <linux/platक्रमm_data/mmc-s3cmci.h>
#समावेश <linux/platक्रमm_data/touchscreen-s3c2410.h>
#समावेश <linux/platक्रमm_data/usb-s3c2410_udc.h>

#समावेश <sound/uda1380.h>

#समावेश <linux/platक्रमm_data/fb-s3c2410.h>
#समावेश "map.h"
#समावेश "hardware-s3c24xx.h"
#समावेश "regs-clock.h"
#समावेश "regs-gpio.h"
#समावेश "gpio-samsung.h"

#समावेश "cpu.h"
#समावेश "devs.h"
#समावेश "gpio-cfg.h"
#समावेश "pm.h"

#समावेश "s3c24xx.h"
#समावेश "h1940.h"

#घोषणा H1940_LATCH		((व्योम __क्रमce __iomem *)0xF8000000)

#घोषणा H1940_PA_LATCH		S3C2410_CS2

#घोषणा H1940_LATCH_BIT(x)	(1 << ((x) + 16 - S3C_GPIO_END))

#घोषणा S3C24XX_PLL_MDIV_SHIFT         (12)
#घोषणा S3C24XX_PLL_PDIV_SHIFT         (4)
#घोषणा S3C24XX_PLL_SDIV_SHIFT         (0)

अटल काष्ठा map_desc h1940_iodesc[] __initdata = अणु
	[0] = अणु
		.भव	= (अचिन्हित दीर्घ)H1940_LATCH,
		.pfn		= __phys_to_pfn(H1940_PA_LATCH),
		.length		= SZ_16K,
		.type		= MT_DEVICE
	पूर्ण,
पूर्ण;

#घोषणा UCON S3C2410_UCON_DEFAULT | S3C2410_UCON_UCLK
#घोषणा ULCON S3C2410_LCON_CS8 | S3C2410_LCON_PNONE | S3C2410_LCON_STOPB
#घोषणा UFCON S3C2410_UFCON_RXTRIG8 | S3C2410_UFCON_FIFOMODE

अटल काष्ठा s3c2410_uartcfg h1940_uartcfgs[] __initdata = अणु
	[0] = अणु
		.hwport	     = 0,
		.flags	     = 0,
		.ucon	     = 0x3c5,
		.ulcon	     = 0x03,
		.ufcon	     = 0x51,
	पूर्ण,
	[1] = अणु
		.hwport	     = 1,
		.flags	     = 0,
		.ucon	     = 0x245,
		.ulcon	     = 0x03,
		.ufcon	     = 0x00,
	पूर्ण,
	/* IR port */
	[2] = अणु
		.hwport	     = 2,
		.flags	     = 0,
		.uart_flags  = UPF_CONS_FLOW,
		.ucon	     = 0x3c5,
		.ulcon	     = 0x43,
		.ufcon	     = 0x51,
	पूर्ण
पूर्ण;

/* Board control latch control */

अटल अचिन्हित पूर्णांक latch_state;

अटल व्योम h1940_latch_control(अचिन्हित पूर्णांक clear, अचिन्हित पूर्णांक set)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);

	latch_state &= ~clear;
	latch_state |= set;

	__raw_ग_लिखोl(latch_state, H1940_LATCH);

	local_irq_restore(flags);
पूर्ण

अटल अंतरभूत पूर्णांक h1940_gpiolib_to_latch(पूर्णांक offset)
अणु
	वापस 1 << (offset + 16);
पूर्ण

अटल व्योम h1940_gpiolib_latch_set(काष्ठा gpio_chip *chip,
					अचिन्हित offset, पूर्णांक value)
अणु
	पूर्णांक latch_bit = h1940_gpiolib_to_latch(offset);

	h1940_latch_control(value ? 0 : latch_bit,
		value ? latch_bit : 0);
पूर्ण

अटल पूर्णांक h1940_gpiolib_latch_output(काष्ठा gpio_chip *chip,
					अचिन्हित offset, पूर्णांक value)
अणु
	h1940_gpiolib_latch_set(chip, offset, value);
	वापस 0;
पूर्ण

अटल पूर्णांक h1940_gpiolib_latch_get(काष्ठा gpio_chip *chip,
					अचिन्हित offset)
अणु
	वापस (latch_state >> (offset + 16)) & 1;
पूर्ण

अटल काष्ठा gpio_chip h1940_latch_gpiochip = अणु
	.base			= H1940_LATCH_GPIO(0),
	.owner			= THIS_MODULE,
	.label			= "H1940_LATCH",
	.ngpio			= 16,
	.direction_output	= h1940_gpiolib_latch_output,
	.set			= h1940_gpiolib_latch_set,
	.get			= h1940_gpiolib_latch_get,
पूर्ण;

अटल काष्ठा s3c2410_udc_mach_info h1940_udc_cfg __initdata = अणु
	.vbus_pin		= S3C2410_GPG(5),
	.vbus_pin_inverted	= 1,
	.pullup_pin		= H1940_LATCH_USB_DP,
पूर्ण;

अटल काष्ठा s3c2410_ts_mach_info h1940_ts_cfg __initdata = अणु
		.delay = 10000,
		.presc = 49,
		.oversampling_shअगरt = 2,
		.cfg_gpio = s3c24xx_ts_cfg_gpio,
पूर्ण;

/*
 * Set lcd on or off
 */
अटल काष्ठा s3c2410fb_display h1940_lcd __initdata = अणु
	.lcdcon5=	S3C2410_LCDCON5_FRM565 | \
			S3C2410_LCDCON5_INVVLINE | \
			S3C2410_LCDCON5_HWSWP,

	.type =		S3C2410_LCDCON1_TFT,
	.width =	240,
	.height =	320,
	.pixघड़ी =	260000,
	.xres =		240,
	.yres =		320,
	.bpp =		16,
	.left_margin =	8,
	.right_margin =	20,
	.hsync_len =	4,
	.upper_margin =	8,
	.lower_margin = 7,
	.vsync_len =	1,
पूर्ण;

अटल काष्ठा s3c2410fb_mach_info h1940_fb_info __initdata = अणु
	.displays = &h1940_lcd,
	.num_displays = 1,
	.शेष_display = 0,

	.lpcsel =	0x02,
	.gpccon =	0xaa940659,
	.gpccon_mask =	0xffffc0f0,
	.gpccon_reg =	S3C2410_GPCCON,
	.gpcup =	0x0000ffff,
	.gpcup_mask =	0xffffffff,
	.gpcup_reg =	S3C2410_GPCUP,
	.gpdcon =	0xaa84aaa0,
	.gpdcon_mask =	0xffffffff,
	.gpdcon_reg =	S3C2410_GPDCON,
	.gpdup =	0x0000faff,
	.gpdup_mask =	0xffffffff,
	.gpdup_reg =	S3C2410_GPDUP,
पूर्ण;

अटल पूर्णांक घातer_supply_init(काष्ठा device *dev)
अणु
	वापस gpio_request(S3C2410_GPF(2), "cable plugged");
पूर्ण

अटल पूर्णांक h1940_is_ac_online(व्योम)
अणु
	वापस !gpio_get_value(S3C2410_GPF(2));
पूर्ण

अटल व्योम घातer_supply_निकास(काष्ठा device *dev)
अणु
	gpio_मुक्त(S3C2410_GPF(2));
पूर्ण

अटल अक्षर *h1940_supplicants[] = अणु
	"main-battery",
	"backup-battery",
पूर्ण;

अटल काष्ठा pda_घातer_pdata घातer_supply_info = अणु
	.init			= घातer_supply_init,
	.is_ac_online		= h1940_is_ac_online,
	.निकास			= घातer_supply_निकास,
	.supplied_to		= h1940_supplicants,
	.num_supplicants	= ARRAY_SIZE(h1940_supplicants),
पूर्ण;

अटल काष्ठा resource घातer_supply_resources[] = अणु
	[0] = DEFINE_RES_NAMED(IRQ_EINT2, 1, "ac", IORESOURCE_IRQ \
			| IORESOURCE_IRQ_LOWEDGE | IORESOURCE_IRQ_HIGHEDGE),
पूर्ण;

अटल काष्ठा platक्रमm_device घातer_supply = अणु
	.name		= "pda-power",
	.id		= -1,
	.dev		= अणु
				.platक्रमm_data =
					&घातer_supply_info,
	पूर्ण,
	.resource	= घातer_supply_resources,
	.num_resources	= ARRAY_SIZE(घातer_supply_resources),
पूर्ण;

अटल स्थिर काष्ठा s3c_adc_bat_thresh bat_lut_noac[] = अणु
	अणु .volt = 4070, .cur = 162, .level = 100पूर्ण,
	अणु .volt = 4040, .cur = 165, .level = 95पूर्ण,
	अणु .volt = 4016, .cur = 164, .level = 90पूर्ण,
	अणु .volt = 3996, .cur = 166, .level = 85पूर्ण,
	अणु .volt = 3971, .cur = 168, .level = 80पूर्ण,
	अणु .volt = 3951, .cur = 168, .level = 75पूर्ण,
	अणु .volt = 3931, .cur = 170, .level = 70पूर्ण,
	अणु .volt = 3903, .cur = 172, .level = 65पूर्ण,
	अणु .volt = 3886, .cur = 172, .level = 60पूर्ण,
	अणु .volt = 3858, .cur = 176, .level = 55पूर्ण,
	अणु .volt = 3842, .cur = 176, .level = 50पूर्ण,
	अणु .volt = 3818, .cur = 176, .level = 45पूर्ण,
	अणु .volt = 3789, .cur = 180, .level = 40पूर्ण,
	अणु .volt = 3769, .cur = 180, .level = 35पूर्ण,
	अणु .volt = 3749, .cur = 184, .level = 30पूर्ण,
	अणु .volt = 3732, .cur = 184, .level = 25पूर्ण,
	अणु .volt = 3716, .cur = 184, .level = 20पूर्ण,
	अणु .volt = 3708, .cur = 184, .level = 15पूर्ण,
	अणु .volt = 3716, .cur = 96, .level = 10पूर्ण,
	अणु .volt = 3700, .cur = 96, .level = 5पूर्ण,
	अणु .volt = 3684, .cur = 96, .level = 0पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा s3c_adc_bat_thresh bat_lut_acin[] = अणु
	अणु .volt = 4130, .cur = 0, .level = 100पूर्ण,
	अणु .volt = 3982, .cur = 0, .level = 50पूर्ण,
	अणु .volt = 3854, .cur = 0, .level = 10पूर्ण,
	अणु .volt = 3841, .cur = 0, .level = 0पूर्ण,
पूर्ण;

अटल काष्ठा gpiod_lookup_table h1940_bat_gpio_table = अणु
	.dev_id = "s3c-adc-battery",
	.table = अणु
		/* Charge status S3C2410_GPF(3) */
		GPIO_LOOKUP("GPIOF", 3, "charge-status", GPIO_ACTIVE_LOW),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक h1940_bat_init(व्योम)
अणु
	पूर्णांक ret;

	ret = gpio_request(H1940_LATCH_SM803_ENABLE, "h1940-charger-enable");
	अगर (ret)
		वापस ret;
	gpio_direction_output(H1940_LATCH_SM803_ENABLE, 0);

	वापस 0;

पूर्ण

अटल व्योम h1940_bat_निकास(व्योम)
अणु
	gpio_मुक्त(H1940_LATCH_SM803_ENABLE);
पूर्ण

अटल व्योम h1940_enable_अक्षरger(व्योम)
अणु
	gpio_set_value(H1940_LATCH_SM803_ENABLE, 1);
पूर्ण

अटल व्योम h1940_disable_अक्षरger(व्योम)
अणु
	gpio_set_value(H1940_LATCH_SM803_ENABLE, 0);
पूर्ण

अटल काष्ठा s3c_adc_bat_pdata h1940_bat_cfg = अणु
	.init = h1940_bat_init,
	.निकास = h1940_bat_निकास,
	.enable_अक्षरger = h1940_enable_अक्षरger,
	.disable_अक्षरger = h1940_disable_अक्षरger,
	.lut_noac = bat_lut_noac,
	.lut_noac_cnt = ARRAY_SIZE(bat_lut_noac),
	.lut_acin = bat_lut_acin,
	.lut_acin_cnt = ARRAY_SIZE(bat_lut_acin),
	.volt_channel = 0,
	.current_channel = 1,
	.volt_mult = 4056,
	.current_mult = 1893,
	.पूर्णांकernal_impedance = 200,
	.backup_volt_channel = 3,
	/* TODO Check backup volt multiplier */
	.backup_volt_mult = 4056,
	.backup_volt_min = 0,
	.backup_volt_max = 4149288
पूर्ण;

अटल काष्ठा platक्रमm_device h1940_battery = अणु
	.name             = "s3c-adc-battery",
	.id               = -1,
	.dev = अणु
		.parent = &s3c_device_adc.dev,
		.platक्रमm_data = &h1940_bat_cfg,
	पूर्ण,
पूर्ण;

अटल DEFINE_SPINLOCK(h1940_blink_spin);

पूर्णांक h1940_led_blink_set(काष्ठा gpio_desc *desc, पूर्णांक state,
	अचिन्हित दीर्घ *delay_on, अचिन्हित दीर्घ *delay_off)
अणु
	पूर्णांक blink_gpio, check_gpio1, check_gpio2;
	पूर्णांक gpio = desc ? desc_to_gpio(desc) : -EINVAL;

	चयन (gpio) अणु
	हाल H1940_LATCH_LED_GREEN:
		blink_gpio = S3C2410_GPA(7);
		check_gpio1 = S3C2410_GPA(1);
		check_gpio2 = S3C2410_GPA(3);
		अवरोध;
	हाल H1940_LATCH_LED_RED:
		blink_gpio = S3C2410_GPA(1);
		check_gpio1 = S3C2410_GPA(7);
		check_gpio2 = S3C2410_GPA(3);
		अवरोध;
	शेष:
		blink_gpio = S3C2410_GPA(3);
		check_gpio1 = S3C2410_GPA(1);
		check_gpio2 = S3C2410_GPA(7);
		अवरोध;
	पूर्ण

	अगर (delay_on && delay_off && !*delay_on && !*delay_off)
		*delay_on = *delay_off = 500;

	spin_lock(&h1940_blink_spin);

	चयन (state) अणु
	हाल GPIO_LED_NO_BLINK_LOW:
	हाल GPIO_LED_NO_BLINK_HIGH:
		अगर (!gpio_get_value(check_gpio1) &&
		    !gpio_get_value(check_gpio2))
			gpio_set_value(H1940_LATCH_LED_FLASH, 0);
		gpio_set_value(blink_gpio, 0);
		अगर (gpio_is_valid(gpio))
			gpio_set_value(gpio, state);
		अवरोध;
	हाल GPIO_LED_BLINK:
		अगर (gpio_is_valid(gpio))
			gpio_set_value(gpio, 0);
		gpio_set_value(H1940_LATCH_LED_FLASH, 1);
		gpio_set_value(blink_gpio, 1);
		अवरोध;
	पूर्ण

	spin_unlock(&h1940_blink_spin);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(h1940_led_blink_set);

अटल काष्ठा gpio_led h1940_leds_desc[] = अणु
	अणु
		.name			= "Green",
		.शेष_trigger	= "main-battery-full",
		.gpio			= H1940_LATCH_LED_GREEN,
		.retain_state_suspended	= 1,
	पूर्ण,
	अणु
		.name			= "Red",
		.शेष_trigger
			= "main-battery-charging-blink-full-solid",
		.gpio			= H1940_LATCH_LED_RED,
		.retain_state_suspended	= 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_led_platक्रमm_data h1940_leds_pdata = अणु
	.num_leds	= ARRAY_SIZE(h1940_leds_desc),
	.leds		= h1940_leds_desc,
	.gpio_blink_set	= h1940_led_blink_set,
पूर्ण;

अटल काष्ठा platक्रमm_device h1940_device_leds = अणु
	.name	= "leds-gpio",
	.id	= -1,
	.dev	= अणु
			.platक्रमm_data = &h1940_leds_pdata,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device h1940_device_bluetooth = अणु
	.name             = "h1940-bt",
	.id               = -1,
पूर्ण;

अटल व्योम h1940_set_mmc_घातer(अचिन्हित अक्षर घातer_mode, अचिन्हित लघु vdd)
अणु
	s3c24xx_mci_def_set_घातer(घातer_mode, vdd);

	चयन (घातer_mode) अणु
	हाल MMC_POWER_OFF:
		gpio_set_value(H1940_LATCH_SD_POWER, 0);
		अवरोध;
	हाल MMC_POWER_UP:
	हाल MMC_POWER_ON:
		gpio_set_value(H1940_LATCH_SD_POWER, 1);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल काष्ठा s3c24xx_mci_pdata h1940_mmc_cfg __initdata = अणु
	.set_घातer     = h1940_set_mmc_घातer,
	.ocr_avail     = MMC_VDD_32_33,
पूर्ण;

अटल काष्ठा gpiod_lookup_table h1940_mmc_gpio_table = अणु
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

अटल काष्ठा gpiod_lookup_table h1940_audio_gpio_table = अणु
	.dev_id = "h1940-audio",
	.table = अणु
		GPIO_LOOKUP("H1940_LATCH",
			    H1940_LATCH_AUDIO_POWER - H1940_LATCH_GPIO(0),
			    "speaker-power", GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP("GPIOG", 4, "hp", GPIO_ACTIVE_HIGH),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device h1940_audio = अणु
	.name = "h1940-audio",
	.id   = -1,
पूर्ण;

अटल काष्ठा pwm_lookup h1940_pwm_lookup[] = अणु
	PWM_LOOKUP("samsung-pwm", 0, "pwm-backlight", शून्य, 36296,
		   PWM_POLARITY_NORMAL),
पूर्ण;

अटल पूर्णांक h1940_backlight_init(काष्ठा device *dev)
अणु
	gpio_request(S3C2410_GPB(0), "Backlight");

	gpio_direction_output(S3C2410_GPB(0), 0);
	s3c_gpio_setpull(S3C2410_GPB(0), S3C_GPIO_PULL_NONE);
	s3c_gpio_cfgpin(S3C2410_GPB(0), S3C2410_GPB0_TOUT0);
	gpio_set_value(H1940_LATCH_MAX1698_nSHUTDOWN, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक h1940_backlight_notअगरy(काष्ठा device *dev, पूर्णांक brightness)
अणु
	अगर (!brightness) अणु
		gpio_direction_output(S3C2410_GPB(0), 1);
		gpio_set_value(H1940_LATCH_MAX1698_nSHUTDOWN, 0);
	पूर्ण अन्यथा अणु
		gpio_direction_output(S3C2410_GPB(0), 0);
		s3c_gpio_setpull(S3C2410_GPB(0), S3C_GPIO_PULL_NONE);
		s3c_gpio_cfgpin(S3C2410_GPB(0), S3C2410_GPB0_TOUT0);
		gpio_set_value(H1940_LATCH_MAX1698_nSHUTDOWN, 1);
	पूर्ण
	वापस brightness;
पूर्ण

अटल व्योम h1940_backlight_निकास(काष्ठा device *dev)
अणु
	gpio_direction_output(S3C2410_GPB(0), 1);
	gpio_set_value(H1940_LATCH_MAX1698_nSHUTDOWN, 0);
पूर्ण


अटल काष्ठा platक्रमm_pwm_backlight_data backlight_data = अणु
	.max_brightness = 100,
	.dft_brightness = 50,
	.init           = h1940_backlight_init,
	.notअगरy		= h1940_backlight_notअगरy,
	.निकास           = h1940_backlight_निकास,
पूर्ण;

अटल काष्ठा platक्रमm_device h1940_backlight = अणु
	.name = "pwm-backlight",
	.dev  = अणु
		.parent = &samsung_device_pwm.dev,
		.platक्रमm_data = &backlight_data,
	पूर्ण,
	.id   = -1,
पूर्ण;

अटल व्योम h1940_lcd_घातer_set(काष्ठा plat_lcd_data *pd,
					अचिन्हित पूर्णांक घातer)
अणु
	पूर्णांक value, retries = 100;

	अगर (!घातer) अणु
		gpio_set_value(S3C2410_GPC(0), 0);
		/* रुको क्रम 3ac */
		करो अणु
			value = gpio_get_value(S3C2410_GPC(6));
		पूर्ण जबतक (value && retries--);

		gpio_set_value(H1940_LATCH_LCD_P2, 0);
		gpio_set_value(H1940_LATCH_LCD_P3, 0);
		gpio_set_value(H1940_LATCH_LCD_P4, 0);

		gpio_direction_output(S3C2410_GPC(1), 0);
		gpio_direction_output(S3C2410_GPC(4), 0);

		gpio_set_value(H1940_LATCH_LCD_P1, 0);
		gpio_set_value(H1940_LATCH_LCD_P0, 0);

		gpio_set_value(S3C2410_GPC(5), 0);

	पूर्ण अन्यथा अणु
		gpio_set_value(H1940_LATCH_LCD_P0, 1);
		gpio_set_value(H1940_LATCH_LCD_P1, 1);

		gpio_direction_input(S3C2410_GPC(1));
		gpio_direction_input(S3C2410_GPC(4));
		mdelay(10);
		s3c_gpio_cfgpin(S3C2410_GPC(1), S3C_GPIO_SFN(2));
		s3c_gpio_cfgpin(S3C2410_GPC(4), S3C_GPIO_SFN(2));

		gpio_set_value(S3C2410_GPC(5), 1);
		gpio_set_value(S3C2410_GPC(0), 1);

		gpio_set_value(H1940_LATCH_LCD_P3, 1);
		gpio_set_value(H1940_LATCH_LCD_P2, 1);
		gpio_set_value(H1940_LATCH_LCD_P4, 1);
	पूर्ण
पूर्ण

अटल काष्ठा plat_lcd_data h1940_lcd_घातer_data = अणु
	.set_घातer      = h1940_lcd_घातer_set,
पूर्ण;

अटल काष्ठा platक्रमm_device h1940_lcd_घातerdev = अणु
	.name                   = "platform-lcd",
	.dev.parent             = &s3c_device_lcd.dev,
	.dev.platक्रमm_data      = &h1940_lcd_घातer_data,
पूर्ण;

अटल काष्ठा uda1380_platक्रमm_data uda1380_info = अणु
	.gpio_घातer	= H1940_LATCH_UDA_POWER,
	.gpio_reset	= S3C2410_GPA(12),
	.dac_clk	= UDA1380_DAC_CLK_SYSCLK,
पूर्ण;

अटल काष्ठा i2c_board_info h1940_i2c_devices[] = अणु
	अणु
		I2C_BOARD_INFO("uda1380", 0x1a),
		.platक्रमm_data = &uda1380_info,
	पूर्ण,
पूर्ण;

#घोषणा DECLARE_BUTTON(p, k, n, w)	\
	अणु				\
		.gpio		= p,	\
		.code		= k,	\
		.desc		= n,	\
		.wakeup		= w,	\
		.active_low	= 1,	\
	पूर्ण

अटल काष्ठा gpio_keys_button h1940_buttons[] = अणु
	DECLARE_BUTTON(S3C2410_GPF(0),       KEY_POWER,          "Power", 1),
	DECLARE_BUTTON(S3C2410_GPF(6),       KEY_ENTER,         "Select", 1),
	DECLARE_BUTTON(S3C2410_GPF(7),      KEY_RECORD,         "Record", 0),
	DECLARE_BUTTON(S3C2410_GPG(0),         KEY_F11,       "Calendar", 0),
	DECLARE_BUTTON(S3C2410_GPG(2),         KEY_F12,       "Contacts", 0),
	DECLARE_BUTTON(S3C2410_GPG(3),        KEY_MAIL,           "Mail", 0),
	DECLARE_BUTTON(S3C2410_GPG(6),        KEY_LEFT,     "Left_arrow", 0),
	DECLARE_BUTTON(S3C2410_GPG(7),    KEY_HOMEPAGE,           "Home", 0),
	DECLARE_BUTTON(S3C2410_GPG(8),       KEY_RIGHT,    "Right_arrow", 0),
	DECLARE_BUTTON(S3C2410_GPG(9),          KEY_UP,       "Up_arrow", 0),
	DECLARE_BUTTON(S3C2410_GPG(10),       KEY_DOWN,     "Down_arrow", 0),
पूर्ण;

अटल काष्ठा gpio_keys_platक्रमm_data h1940_buttons_data = अणु
	.buttons	= h1940_buttons,
	.nbuttons	= ARRAY_SIZE(h1940_buttons),
पूर्ण;

अटल काष्ठा platक्रमm_device h1940_dev_buttons = अणु
	.name		= "gpio-keys",
	.id		= -1,
	.dev		= अणु
		.platक्रमm_data  = &h1940_buttons_data,
	पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device *h1940_devices[] __initdata = अणु
	&h1940_dev_buttons,
	&s3c_device_ohci,
	&s3c_device_lcd,
	&s3c_device_wdt,
	&s3c_device_i2c0,
	&s3c_device_iis,
	&s3c_device_usbgadget,
	&h1940_device_leds,
	&h1940_device_bluetooth,
	&s3c_device_sdi,
	&s3c_device_rtc,
	&samsung_device_pwm,
	&h1940_backlight,
	&h1940_lcd_घातerdev,
	&s3c_device_adc,
	&s3c_device_ts,
	&घातer_supply,
	&h1940_battery,
	&h1940_audio,
पूर्ण;

अटल व्योम __init h1940_map_io(व्योम)
अणु
	s3c24xx_init_io(h1940_iodesc, ARRAY_SIZE(h1940_iodesc));
	s3c24xx_init_uarts(h1940_uartcfgs, ARRAY_SIZE(h1940_uartcfgs));
	s3c24xx_set_समयr_source(S3C24XX_PWM3, S3C24XX_PWM4);

	/* setup PM */

#अगर_घोषित CONFIG_PM_H1940
	स_नकल(phys_to_virt(H1940_SUSPEND_RESUMEAT), h1940_pm_वापस, 1024);
#पूर्ण_अगर
	s3c_pm_init();

	/* Add latch gpio chip, set latch initial value */
	h1940_latch_control(0, 0);
	WARN_ON(gpiochip_add_data(&h1940_latch_gpiochip, शून्य));
पूर्ण

अटल व्योम __init h1940_init_समय(व्योम)
अणु
	s3c2410_init_घड़ीs(12000000);
	s3c24xx_समयr_init();
पूर्ण

/* H1940 and RX3715 need to reserve this क्रम suspend */
अटल व्योम __init h1940_reserve(व्योम)
अणु
	memblock_reserve(0x30003000, 0x1000);
	memblock_reserve(0x30081000, 0x1000);
पूर्ण

अटल व्योम __init h1940_init(व्योम)
अणु
	u32 पंचांगp;

	s3c24xx_fb_set_platdata(&h1940_fb_info);
	gpiod_add_lookup_table(&h1940_mmc_gpio_table);
	gpiod_add_lookup_table(&h1940_audio_gpio_table);
	gpiod_add_lookup_table(&h1940_bat_gpio_table);
	/* Configure the I2S pins (GPE0...GPE4) in correct mode */
	s3c_gpio_cfgall_range(S3C2410_GPE(0), 5, S3C_GPIO_SFN(2),
			      S3C_GPIO_PULL_NONE);
	s3c24xx_mci_set_platdata(&h1940_mmc_cfg);
 	s3c24xx_udc_set_platdata(&h1940_udc_cfg);
	s3c24xx_ts_set_platdata(&h1940_ts_cfg);
	s3c_i2c0_set_platdata(शून्य);

	/* Turn off suspend on both USB ports, and चयन the
	 * selectable USB port to USB device mode. */

	s3c2410_modअगरy_misccr(S3C2410_MISCCR_USBHOST |
			      S3C2410_MISCCR_USBSUSPND0 |
			      S3C2410_MISCCR_USBSUSPND1, 0x0);

	पंचांगp =   (0x78 << S3C24XX_PLL_MDIV_SHIFT)
	      | (0x02 << S3C24XX_PLL_PDIV_SHIFT)
	      | (0x03 << S3C24XX_PLL_SDIV_SHIFT);
	ग_लिखोl(पंचांगp, S3C2410_UPLLCON);

	gpio_request(S3C2410_GPC(0), "LCD power");
	gpio_request(S3C2410_GPC(1), "LCD power");
	gpio_request(S3C2410_GPC(4), "LCD power");
	gpio_request(S3C2410_GPC(5), "LCD power");
	gpio_request(S3C2410_GPC(6), "LCD power");
	gpio_request(H1940_LATCH_LCD_P0, "LCD power");
	gpio_request(H1940_LATCH_LCD_P1, "LCD power");
	gpio_request(H1940_LATCH_LCD_P2, "LCD power");
	gpio_request(H1940_LATCH_LCD_P3, "LCD power");
	gpio_request(H1940_LATCH_LCD_P4, "LCD power");
	gpio_request(H1940_LATCH_MAX1698_nSHUTDOWN, "LCD power");
	gpio_direction_output(S3C2410_GPC(0), 0);
	gpio_direction_output(S3C2410_GPC(1), 0);
	gpio_direction_output(S3C2410_GPC(4), 0);
	gpio_direction_output(S3C2410_GPC(5), 0);
	gpio_direction_input(S3C2410_GPC(6));
	gpio_direction_output(H1940_LATCH_LCD_P0, 0);
	gpio_direction_output(H1940_LATCH_LCD_P1, 0);
	gpio_direction_output(H1940_LATCH_LCD_P2, 0);
	gpio_direction_output(H1940_LATCH_LCD_P3, 0);
	gpio_direction_output(H1940_LATCH_LCD_P4, 0);
	gpio_direction_output(H1940_LATCH_MAX1698_nSHUTDOWN, 0);

	gpio_request(H1940_LATCH_SD_POWER, "SD power");
	gpio_direction_output(H1940_LATCH_SD_POWER, 0);

	pwm_add_table(h1940_pwm_lookup, ARRAY_SIZE(h1940_pwm_lookup));
	platक्रमm_add_devices(h1940_devices, ARRAY_SIZE(h1940_devices));

	gpio_request(S3C2410_GPA(1), "Red LED blink");
	gpio_request(S3C2410_GPA(3), "Blue LED blink");
	gpio_request(S3C2410_GPA(7), "Green LED blink");
	gpio_request(H1940_LATCH_LED_FLASH, "LED blink");
	gpio_direction_output(S3C2410_GPA(1), 0);
	gpio_direction_output(S3C2410_GPA(3), 0);
	gpio_direction_output(S3C2410_GPA(7), 0);
	gpio_direction_output(H1940_LATCH_LED_FLASH, 0);

	i2c_रेजिस्टर_board_info(0, h1940_i2c_devices,
		ARRAY_SIZE(h1940_i2c_devices));
पूर्ण

MACHINE_START(H1940, "IPAQ-H1940")
	/* Maपूर्णांकainer: Ben Dooks <ben-linux@fluff.org> */
	.atag_offset	= 0x100,
	.map_io		= h1940_map_io,
	.reserve	= h1940_reserve,
	.init_irq	= s3c2410_init_irq,
	.init_machine	= h1940_init,
	.init_समय	= h1940_init_समय,
MACHINE_END
