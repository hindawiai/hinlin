<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Machine specअगरic code क्रम the Acer n30, Acer N35, Navman PiN 570,
// Yakumo AlphaX and Airis NC05 PDAs.
//
// Copyright (c) 2003-2005 Simtec Electronics
//	Ben Dooks <ben@simtec.co.uk>
//
// Copyright (c) 2005-2008 Christer Weinigel <christer@weinigel.se>
//
// There is a wiki with more inक्रमmation about the n30 port at
// https://handhelds.org/moin/moin.cgi/AcerN30Documentation .

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>

#समावेश <linux/gpio_keys.h>
#समावेश <linux/init.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/serial_s3c.h>
#समावेश <linux/समयr.h>
#समावेश <linux/पन.स>
#समावेश <linux/mmc/host.h>

#समावेश "hardware-s3c24xx.h"
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/mach-types.h>

#समावेश <linux/platक्रमm_data/fb-s3c2410.h>
#समावेश <linux/platक्रमm_data/leds-s3c24xx.h>
#समावेश "regs-gpio.h"
#समावेश "gpio-samsung.h"
#समावेश "gpio-cfg.h"

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/irq.h>
#समावेश <यंत्र/mach/map.h>

#समावेश <linux/platक्रमm_data/i2c-s3c2410.h>

#समावेश "cpu.h"
#समावेश "devs.h"
#समावेश <linux/platक्रमm_data/mmc-s3cmci.h>
#समावेश <linux/platक्रमm_data/usb-s3c2410_udc.h>

#समावेश "s3c24xx.h"

अटल काष्ठा map_desc n30_iodesc[] __initdata = अणु
	/* nothing here yet */
पूर्ण;

अटल काष्ठा s3c2410_uartcfg n30_uartcfgs[] = अणु
	/* Normal serial port */
	[0] = अणु
		.hwport	     = 0,
		.flags	     = 0,
		.ucon	     = 0x2c5,
		.ulcon	     = 0x03,
		.ufcon	     = 0x51,
	पूर्ण,
	/* IR port */
	[1] = अणु
		.hwport	     = 1,
		.flags	     = 0,
		.uart_flags  = UPF_CONS_FLOW,
		.ucon	     = 0x2c5,
		.ulcon	     = 0x43,
		.ufcon	     = 0x51,
	पूर्ण,
	/* On the N30 the bluetooth controller is connected here.
	 * On the N35 and variants the GPS receiver is connected here. */
	[2] = अणु
		.hwport	     = 2,
		.flags	     = 0,
		.ucon	     = 0x2c5,
		.ulcon	     = 0x03,
		.ufcon	     = 0x51,
	पूर्ण,
पूर्ण;

अटल काष्ठा s3c2410_udc_mach_info n30_udc_cfg __initdata = अणु
	.vbus_pin		= S3C2410_GPG(1),
	.vbus_pin_inverted	= 0,
	.pullup_pin		= S3C2410_GPB(3),
पूर्ण;

अटल काष्ठा gpio_keys_button n30_buttons[] = अणु
	अणु
		.gpio		= S3C2410_GPF(0),
		.code		= KEY_POWER,
		.desc		= "Power",
		.active_low	= 0,
	पूर्ण,
	अणु
		.gpio		= S3C2410_GPG(9),
		.code		= KEY_UP,
		.desc		= "Thumbwheel Up",
		.active_low	= 0,
	पूर्ण,
	अणु
		.gpio		= S3C2410_GPG(8),
		.code		= KEY_DOWN,
		.desc		= "Thumbwheel Down",
		.active_low	= 0,
	पूर्ण,
	अणु
		.gpio		= S3C2410_GPG(7),
		.code		= KEY_ENTER,
		.desc		= "Thumbwheel Press",
		.active_low	= 0,
	पूर्ण,
	अणु
		.gpio		= S3C2410_GPF(7),
		.code		= KEY_HOMEPAGE,
		.desc		= "Home",
		.active_low	= 0,
	पूर्ण,
	अणु
		.gpio		= S3C2410_GPF(6),
		.code		= KEY_CALENDAR,
		.desc		= "Calendar",
		.active_low	= 0,
	पूर्ण,
	अणु
		.gpio		= S3C2410_GPF(5),
		.code		= KEY_ADDRESSBOOK,
		.desc		= "Contacts",
		.active_low	= 0,
	पूर्ण,
	अणु
		.gpio		= S3C2410_GPF(4),
		.code		= KEY_MAIL,
		.desc		= "Mail",
		.active_low	= 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_keys_platक्रमm_data n30_button_data = अणु
	.buttons	= n30_buttons,
	.nbuttons	= ARRAY_SIZE(n30_buttons),
पूर्ण;

अटल काष्ठा platक्रमm_device n30_button_device = अणु
	.name		= "gpio-keys",
	.id		= -1,
	.dev		= अणु
		.platक्रमm_data	= &n30_button_data,
	पूर्ण
पूर्ण;

अटल काष्ठा gpio_keys_button n35_buttons[] = अणु
	अणु
		.gpio		= S3C2410_GPF(0),
		.code		= KEY_POWER,
		.type		= EV_PWR,
		.desc		= "Power",
		.active_low	= 0,
		.wakeup		= 1,
	पूर्ण,
	अणु
		.gpio		= S3C2410_GPG(9),
		.code		= KEY_UP,
		.desc		= "Joystick Up",
		.active_low	= 0,
	पूर्ण,
	अणु
		.gpio		= S3C2410_GPG(8),
		.code		= KEY_DOWN,
		.desc		= "Joystick Down",
		.active_low	= 0,
	पूर्ण,
	अणु
		.gpio		= S3C2410_GPG(6),
		.code		= KEY_DOWN,
		.desc		= "Joystick Left",
		.active_low	= 0,
	पूर्ण,
	अणु
		.gpio		= S3C2410_GPG(5),
		.code		= KEY_DOWN,
		.desc		= "Joystick Right",
		.active_low	= 0,
	पूर्ण,
	अणु
		.gpio		= S3C2410_GPG(7),
		.code		= KEY_ENTER,
		.desc		= "Joystick Press",
		.active_low	= 0,
	पूर्ण,
	अणु
		.gpio		= S3C2410_GPF(7),
		.code		= KEY_HOMEPAGE,
		.desc		= "Home",
		.active_low	= 0,
	पूर्ण,
	अणु
		.gpio		= S3C2410_GPF(6),
		.code		= KEY_CALENDAR,
		.desc		= "Calendar",
		.active_low	= 0,
	पूर्ण,
	अणु
		.gpio		= S3C2410_GPF(5),
		.code		= KEY_ADDRESSBOOK,
		.desc		= "Contacts",
		.active_low	= 0,
	पूर्ण,
	अणु
		.gpio		= S3C2410_GPF(4),
		.code		= KEY_MAIL,
		.desc		= "Mail",
		.active_low	= 0,
	पूर्ण,
	अणु
		.gpio		= S3C2410_GPF(3),
		.code		= SW_RADIO,
		.desc		= "GPS Antenna",
		.active_low	= 0,
	पूर्ण,
	अणु
		.gpio		= S3C2410_GPG(2),
		.code		= SW_HEADPHONE_INSERT,
		.desc		= "Headphone",
		.active_low	= 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_keys_platक्रमm_data n35_button_data = अणु
	.buttons	= n35_buttons,
	.nbuttons	= ARRAY_SIZE(n35_buttons),
पूर्ण;

अटल काष्ठा platक्रमm_device n35_button_device = अणु
	.name		= "gpio-keys",
	.id		= -1,
	.num_resources	= 0,
	.dev		= अणु
		.platक्रमm_data	= &n35_button_data,
	पूर्ण
पूर्ण;

/* This is the bluetooth LED on the device. */

अटल काष्ठा gpiod_lookup_table n30_blue_led_gpio_table = अणु
	.dev_id = "s3c24xx_led.1",
	.table = अणु
		GPIO_LOOKUP("GPG", 6, शून्य, GPIO_ACTIVE_HIGH),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा s3c24xx_led_platdata n30_blue_led_pdata = अणु
	.name		= "blue_led",
	.def_trigger	= "",
पूर्ण;

/* This is the blue LED on the device. Originally used to indicate GPS activity
 * by flashing. */

अटल काष्ठा gpiod_lookup_table n35_blue_led_gpio_table = अणु
	.dev_id = "s3c24xx_led.1",
	.table = अणु
		GPIO_LOOKUP("GPD", 8, शून्य, GPIO_ACTIVE_HIGH),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा s3c24xx_led_platdata n35_blue_led_pdata = अणु
	.name		= "blue_led",
	.def_trigger	= "",
पूर्ण;

/* This LED is driven by the battery microcontroller, and is blinking
 * red, blinking green or solid green when the battery is low,
 * अक्षरging or full respectively.  By driving GPD9 low, it's possible
 * to क्रमce the LED to blink red, so call that warning LED.  */

अटल काष्ठा gpiod_lookup_table n30_warning_led_gpio_table = अणु
	.dev_id = "s3c24xx_led.2",
	.table = अणु
		GPIO_LOOKUP("GPD", 9, शून्य, GPIO_ACTIVE_LOW),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा s3c24xx_led_platdata n30_warning_led_pdata = अणु
	.name		= "warning_led",
	.def_trigger	= "",
पूर्ण;

अटल काष्ठा gpiod_lookup_table n35_warning_led_gpio_table = अणु
	.dev_id = "s3c24xx_led.2",
	.table = अणु
		GPIO_LOOKUP("GPD", 9, शून्य, GPIO_ACTIVE_LOW | GPIO_OPEN_DRAIN),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा s3c24xx_led_platdata n35_warning_led_pdata = अणु
	.name		= "warning_led",
	.def_trigger	= "",
पूर्ण;

अटल काष्ठा platक्रमm_device n30_blue_led = अणु
	.name		= "s3c24xx_led",
	.id		= 1,
	.dev		= अणु
		.platक्रमm_data	= &n30_blue_led_pdata,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device n35_blue_led = अणु
	.name		= "s3c24xx_led",
	.id		= 1,
	.dev		= अणु
		.platक्रमm_data	= &n35_blue_led_pdata,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device n30_warning_led = अणु
	.name		= "s3c24xx_led",
	.id		= 2,
	.dev		= अणु
		.platक्रमm_data	= &n30_warning_led_pdata,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device n35_warning_led = अणु
	.name		= "s3c24xx_led",
	.id		= 2,
	.dev		= अणु
		.platक्रमm_data	= &n35_warning_led_pdata,
	पूर्ण,
पूर्ण;

अटल काष्ठा s3c2410fb_display n30_display __initdata = अणु
	.type		= S3C2410_LCDCON1_TFT,
	.width		= 240,
	.height		= 320,
	.pixघड़ी	= 170000,

	.xres		= 240,
	.yres		= 320,
	.bpp		= 16,
	.left_margin	= 3,
	.right_margin	= 40,
	.hsync_len	= 40,
	.upper_margin	= 2,
	.lower_margin	= 3,
	.vsync_len	= 2,

	.lcdcon5 = S3C2410_LCDCON5_INVVLINE | S3C2410_LCDCON5_INVVFRAME,
पूर्ण;

अटल काष्ठा s3c2410fb_mach_info n30_fb_info __initdata = अणु
	.displays	= &n30_display,
	.num_displays	= 1,
	.शेष_display = 0,
	.lpcsel		= 0x06,
पूर्ण;

अटल व्योम n30_sdi_set_घातer(अचिन्हित अक्षर घातer_mode, अचिन्हित लघु vdd)
अणु
	s3c24xx_mci_def_set_घातer(घातer_mode, vdd);

	चयन (घातer_mode) अणु
	हाल MMC_POWER_ON:
	हाल MMC_POWER_UP:
		gpio_set_value(S3C2410_GPG(4), 1);
		अवरोध;
	हाल MMC_POWER_OFF:
	शेष:
		gpio_set_value(S3C2410_GPG(4), 0);
		अवरोध;
	पूर्ण
पूर्ण

अटल काष्ठा s3c24xx_mci_pdata n30_mci_cfg __initdata = अणु
	.ocr_avail	= MMC_VDD_32_33,
	.set_घातer	= n30_sdi_set_घातer,
पूर्ण;

अटल काष्ठा gpiod_lookup_table n30_mci_gpio_table = अणु
	.dev_id = "s3c2410-sdi",
	.table = अणु
		/* Card detect S3C2410_GPF(1) */
		GPIO_LOOKUP("GPIOF", 1, "cd", GPIO_ACTIVE_LOW),
		/* Write protect S3C2410_GPG(10) */
		GPIO_LOOKUP("GPIOG", 10, "wp", GPIO_ACTIVE_LOW),
		अणु पूर्ण,
		/* bus pins */
		GPIO_LOOKUP_IDX("GPIOE",  5, "bus", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("GPIOE",  6, "bus", 1, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("GPIOE",  7, "bus", 2, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("GPIOE",  8, "bus", 3, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("GPIOE",  9, "bus", 4, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("GPIOE", 10, "bus", 5, GPIO_ACTIVE_HIGH),
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device *n30_devices[] __initdata = अणु
	&s3c_device_lcd,
	&s3c_device_wdt,
	&s3c_device_i2c0,
	&s3c_device_iis,
	&s3c_device_ohci,
	&s3c_device_rtc,
	&s3c_device_usbgadget,
	&s3c_device_sdi,
	&n30_button_device,
	&n30_blue_led,
	&n30_warning_led,
पूर्ण;

अटल काष्ठा platक्रमm_device *n35_devices[] __initdata = अणु
	&s3c_device_lcd,
	&s3c_device_wdt,
	&s3c_device_i2c0,
	&s3c_device_iis,
	&s3c_device_rtc,
	&s3c_device_usbgadget,
	&s3c_device_sdi,
	&n35_button_device,
	&n35_blue_led,
	&n35_warning_led,
पूर्ण;

अटल काष्ठा s3c2410_platक्रमm_i2c __initdata n30_i2ccfg = अणु
	.flags		= 0,
	.slave_addr	= 0x10,
	.frequency	= 10*1000,
पूर्ण;

/* Lots of hardcoded stuff, but it sets up the hardware in a useful
 * state so that we can boot Linux directly from flash. */
अटल व्योम __init n30_hwinit(व्योम)
अणु
	/* GPA0-11 special functions -- unknown what they करो
	 * GPA12 N30 special function -- unknown what it करोes
	 *       N35/PiN output -- unknown what it करोes
	 *
	 * A12 is nGCS1 on the N30 and an output on the N35/PiN.  I
	 * करोn't think it करोes anything useful on the N30, so I ought
	 * to make it an output there too since it always driven to 0
	 * as far as I can tell. */
	अगर (machine_is_n30())
		__raw_ग_लिखोl(0x007fffff, S3C2410_GPACON);
	अगर (machine_is_n35())
		__raw_ग_लिखोl(0x007fefff, S3C2410_GPACON);
	__raw_ग_लिखोl(0x00000000, S3C2410_GPADAT);

	/* GPB0 TOUT0 backlight level
	 * GPB1 output 1=backlight on
	 * GPB2 output IrDA enable 0=transceiver enabled, 1=disabled
	 * GPB3 output USB D+ pull up 0=disabled, 1=enabled
	 * GPB4 N30 output -- unknown function
	 *      N30/PiN GPS control 0=GPS enabled, 1=GPS disabled
	 * GPB5 output -- unknown function
	 * GPB6 input -- unknown function
	 * GPB7 output -- unknown function
	 * GPB8 output -- probably LCD driver enable
	 * GPB9 output -- probably LCD VSYNC driver enable
	 * GPB10 output -- probably LCD HSYNC driver enable
	 */
	__raw_ग_लिखोl(0x00154556, S3C2410_GPBCON);
	__raw_ग_लिखोl(0x00000750, S3C2410_GPBDAT);
	__raw_ग_लिखोl(0x00000073, S3C2410_GPBUP);

	/* GPC0 input RS232 DCD/DSR/RI
	 * GPC1 LCD
	 * GPC2 output RS232 DTR?
	 * GPC3 input RS232 DCD/DSR/RI
	 * GPC4 LCD
	 * GPC5 output 0=न_अंकD ग_लिखो enabled, 1=न_अंकD ग_लिखो protect
	 * GPC6 input -- unknown function
	 * GPC7 input अक्षरger status 0=अक्षरger connected
	 *      this input can be triggered by घातer on the USB device
	 *      port too, but will go back to disconnected soon after.
	 * GPC8 N30/N35 output -- unknown function, always driven to 1
	 *      PiN input -- unknown function, always पढ़ो as 1
	 *      Make it an input with a pull up क्रम all models.
	 * GPC9-15 LCD
	 */
	__raw_ग_लिखोl(0xaaa80618, S3C2410_GPCCON);
	__raw_ग_लिखोl(0x0000014c, S3C2410_GPCDAT);
	__raw_ग_लिखोl(0x0000fef2, S3C2410_GPCUP);

	/* GPD0 input -- unknown function
	 * GPD1-D7 LCD
	 * GPD8 N30 output -- unknown function
	 *      N35/PiN output 1=GPS LED on
	 * GPD9 output 0=घातer led blinks red, 1=normal घातer led function
	 * GPD10 output -- unknown function
	 * GPD11-15 LCD drivers
	 */
	__raw_ग_लिखोl(0xaa95aaa4, S3C2410_GPDCON);
	__raw_ग_लिखोl(0x00000601, S3C2410_GPDDAT);
	__raw_ग_लिखोl(0x0000fbfe, S3C2410_GPDUP);

	/* GPE0-4 I2S audio bus
	 * GPE5-10 SD/MMC bus
	 * E11-13 outमाला_दो -- unknown function, probably घातer management
	 * E14-15 I2C bus connected to the battery controller
	 */
	__raw_ग_लिखोl(0xa56aaaaa, S3C2410_GPECON);
	__raw_ग_लिखोl(0x0000efc5, S3C2410_GPEDAT);
	__raw_ग_लिखोl(0x0000f81f, S3C2410_GPEUP);

	/* GPF0  input 0=घातer button pressed
	 * GPF1  input SD/MMC चयन 0=card present
	 * GPF2  N30 1=reset button pressed (inverted compared to the rest)
	 *	 N35/PiN 0=reset button pressed
	 * GPF3  N30/PiN input -- unknown function
	 *       N35 input GPS antenna position, 0=antenna बंदd, 1=खोलो
	 * GPF4  input 0=button 4 pressed
	 * GPF5  input 0=button 3 pressed
	 * GPF6  input 0=button 2 pressed
	 * GPF7  input 0=button 1 pressed
	 */
	__raw_ग_लिखोl(0x0000aaaa, S3C2410_GPFCON);
	__raw_ग_लिखोl(0x00000000, S3C2410_GPFDAT);
	__raw_ग_लिखोl(0x000000ff, S3C2410_GPFUP);

	/* GPG0  input RS232 DCD/DSR/RI
	 * GPG1  input 1=USB gadget port has घातer from a host
	 * GPG2  N30 input -- unknown function
	 *       N35/PiN input 0=headphones plugged in, 1=not plugged in
	 * GPG3  N30 output -- unknown function
	 *       N35/PiN input with unknown function
	 * GPG4  N30 output 0=MMC enabled, 1=MMC disabled
	 * GPG5  N30 output 0=BlueTooth chip disabled, 1=enabled
	 *       N35/PiN input joystick right
	 * GPG6  N30 output 0=blue led on, 1=off
	 *       N35/PiN input joystick left
	 * GPG7  input 0=thumbwheel pressed
	 * GPG8  input 0=thumbwheel करोwn
	 * GPG9  input 0=thumbwheel up
	 * GPG10 input SD/MMC ग_लिखो protect चयन
	 * GPG11 N30 input -- unknown function
	 *       N35 output 0=GPS antenna घातered, 1=not घातered
	 *       PiN output -- unknown function
	 * GPG12-15 touch screen functions
	 *
	 * The pullups dअगरfer between the models, so enable all
	 * pullups that are enabled on any of the models.
	 */
	अगर (machine_is_n30())
		__raw_ग_लिखोl(0xff0a956a, S3C2410_GPGCON);
	अगर (machine_is_n35())
		__raw_ग_लिखोl(0xff4aa92a, S3C2410_GPGCON);
	__raw_ग_लिखोl(0x0000e800, S3C2410_GPGDAT);
	__raw_ग_लिखोl(0x0000f86f, S3C2410_GPGUP);

	/* GPH0/1/2/3 RS232 serial port
	 * GPH4/5 IrDA serial port
	 * GPH6/7  N30 BlueTooth serial port
	 *         N35/PiN GPS receiver
	 * GPH8 input -- unknown function
	 * GPH9 CLKOUT0 HCLK -- unknown use
	 * GPH10 CLKOUT1 FCLK -- unknown use
	 *
	 * The pull ups क्रम H6/H7 are enabled on N30 but not on the
	 * N35/PiN.  I suppose is useful क्रम a budget model of the N30
	 * with no bluetooth.  It करोesn't hurt to have the pull ups
	 * enabled on the N35, so leave them enabled क्रम all models.
	 */
	__raw_ग_लिखोl(0x0028aaaa, S3C2410_GPHCON);
	__raw_ग_लिखोl(0x000005ef, S3C2410_GPHDAT);
	__raw_ग_लिखोl(0x0000063f, S3C2410_GPHUP);
पूर्ण

अटल व्योम __init n30_map_io(व्योम)
अणु
	s3c24xx_init_io(n30_iodesc, ARRAY_SIZE(n30_iodesc));
	n30_hwinit();
	s3c24xx_init_uarts(n30_uartcfgs, ARRAY_SIZE(n30_uartcfgs));
	s3c24xx_set_समयr_source(S3C24XX_PWM3, S3C24XX_PWM4);
पूर्ण

अटल व्योम __init n30_init_समय(व्योम)
अणु
	s3c2410_init_घड़ीs(12000000);
	s3c24xx_समयr_init();
पूर्ण

/* GPB3 is the line that controls the pull-up क्रम the USB D+ line */

अटल व्योम __init n30_init(व्योम)
अणु
	WARN_ON(gpio_request(S3C2410_GPG(4), "mmc power"));

	s3c24xx_fb_set_platdata(&n30_fb_info);
	s3c24xx_udc_set_platdata(&n30_udc_cfg);
	gpiod_add_lookup_table(&n30_mci_gpio_table);
	s3c24xx_mci_set_platdata(&n30_mci_cfg);
	s3c_i2c0_set_platdata(&n30_i2ccfg);

	/* Turn off suspend on both USB ports, and चयन the
	 * selectable USB port to USB device mode. */

	s3c2410_modअगरy_misccr(S3C2410_MISCCR_USBHOST |
			      S3C2410_MISCCR_USBSUSPND0 |
			      S3C2410_MISCCR_USBSUSPND1, 0x0);

	/* Configure the I2S pins (GPE0...GPE4) in correct mode */
	s3c_gpio_cfgall_range(S3C2410_GPE(0), 5, S3C_GPIO_SFN(2),
			      S3C_GPIO_PULL_NONE);

	अगर (machine_is_n30()) अणु
		/* Turn off suspend on both USB ports, and चयन the
		 * selectable USB port to USB device mode. */
		s3c2410_modअगरy_misccr(S3C2410_MISCCR_USBHOST |
				      S3C2410_MISCCR_USBSUSPND0 |
				      S3C2410_MISCCR_USBSUSPND1, 0x0);

		/* Disable pull-up and add GPIO tables */
		s3c_gpio_setpull(S3C2410_GPG(6), S3C_GPIO_PULL_NONE);
		s3c_gpio_setpull(S3C2410_GPD(9), S3C_GPIO_PULL_NONE);
		gpiod_add_lookup_table(&n30_blue_led_gpio_table);
		gpiod_add_lookup_table(&n30_warning_led_gpio_table);

		platक्रमm_add_devices(n30_devices, ARRAY_SIZE(n30_devices));
	पूर्ण

	अगर (machine_is_n35()) अणु
		/* Turn off suspend and चयन the selectable USB port
		 * to USB device mode.  Turn on suspend क्रम the host
		 * port since it is not connected on the N35.
		 *
		 * Actually, the host port is available at some pads
		 * on the back of the device, so it would actually be
		 * possible to add a USB device inside the N35 अगर you
		 * are willing to करो some hardware modअगरications. */
		s3c2410_modअगरy_misccr(S3C2410_MISCCR_USBHOST |
				      S3C2410_MISCCR_USBSUSPND0 |
				      S3C2410_MISCCR_USBSUSPND1,
				      S3C2410_MISCCR_USBSUSPND0);

		/* Disable pull-up and add GPIO tables */
		s3c_gpio_setpull(S3C2410_GPD(8), S3C_GPIO_PULL_NONE);
		s3c_gpio_setpull(S3C2410_GPD(9), S3C_GPIO_PULL_NONE);
		gpiod_add_lookup_table(&n35_blue_led_gpio_table);
		gpiod_add_lookup_table(&n35_warning_led_gpio_table);

		platक्रमm_add_devices(n35_devices, ARRAY_SIZE(n35_devices));
	पूर्ण
पूर्ण

MACHINE_START(N30, "Acer-N30")
	/* Maपूर्णांकainer: Christer Weinigel <christer@weinigel.se>,
				Ben Dooks <ben-linux@fluff.org>
	*/
	.atag_offset	= 0x100,
	.init_समय	= n30_init_समय,
	.init_machine	= n30_init,
	.init_irq	= s3c2410_init_irq,
	.map_io		= n30_map_io,
MACHINE_END

MACHINE_START(N35, "Acer-N35")
	/* Maपूर्णांकainer: Christer Weinigel <christer@weinigel.se>
	*/
	.atag_offset	= 0x100,
	.init_समय	= n30_init_समय,
	.init_machine	= n30_init,
	.init_irq	= s3c2410_init_irq,
	.map_io		= n30_map_io,
MACHINE_END
