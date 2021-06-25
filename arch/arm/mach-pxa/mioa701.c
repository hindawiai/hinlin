<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Handles the Mitac Mio A701 Board
 *
 * Copyright (C) 2008 Robert Jarzmik
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/syscore_ops.h>
#समावेश <linux/input.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio_keys.h>
#समावेश <linux/pwm.h>
#समावेश <linux/pwm_backlight.h>
#समावेश <linux/rtc.h>
#समावेश <linux/leds.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/pda_घातer.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/wm97xx.h>
#समावेश <linux/mtd/physmap.h>
#समावेश <linux/reboot.h>
#समावेश <linux/regulator/fixed.h>
#समावेश <linux/regulator/max1586.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_data/i2c-pxa.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>

#समावेश "pxa27x.h"
#समावेश "regs-rtc.h"
#समावेश <linux/platक्रमm_data/keypad-pxa27x.h>
#समावेश <linux/platक्रमm_data/video-pxafb.h>
#समावेश <linux/platक्रमm_data/mmc-pxamci.h>
#समावेश "udc.h"
#समावेश "pxa27x-udc.h"
#समावेश <linux/platक्रमm_data/media/camera-pxa.h>
#समावेश <mach/audपन.स>
#समावेश <mach/smemc.h>

#समावेश "mioa701.h"

#समावेश "generic.h"
#समावेश "devices.h"

अटल अचिन्हित दीर्घ mioa701_pin_config[] = अणु
	/* Mio global */
	MIO_CFG_OUT(GPIO9_CHARGE_EN, AF0, DRIVE_LOW),
	MIO_CFG_OUT(GPIO18_POWEROFF, AF0, DRIVE_LOW),
	MFP_CFG_OUT(GPIO3, AF0, DRIVE_HIGH),
	MFP_CFG_OUT(GPIO4, AF0, DRIVE_HIGH),
	MIO_CFG_IN(GPIO80_MAYBE_CHARGE_VDROP, AF0),

	/* Backlight PWM 0 */
	GPIO16_PWM0_OUT,

	/* MMC */
	GPIO32_MMC_CLK,
	GPIO92_MMC_DAT_0,
	GPIO109_MMC_DAT_1,
	GPIO110_MMC_DAT_2,
	GPIO111_MMC_DAT_3,
	GPIO112_MMC_CMD,
	MIO_CFG_IN(GPIO78_SDIO_RO, AF0),
	MIO_CFG_IN(GPIO15_SDIO_INSERT, AF0),
	MIO_CFG_OUT(GPIO91_SDIO_EN, AF0, DRIVE_LOW),

	/* USB */
	MIO_CFG_IN(GPIO13_nUSB_DETECT, AF0),
	MIO_CFG_OUT(GPIO22_USB_ENABLE, AF0, DRIVE_LOW),

	/* LCD */
	GPIOxx_LCD_TFT_16BPP,

	/* QCI */
	GPIO12_CIF_DD_7,
	GPIO17_CIF_DD_6,
	GPIO50_CIF_DD_3,
	GPIO51_CIF_DD_2,
	GPIO52_CIF_DD_4,
	GPIO53_CIF_MCLK,
	GPIO54_CIF_PCLK,
	GPIO55_CIF_DD_1,
	GPIO81_CIF_DD_0,
	GPIO82_CIF_DD_5,
	GPIO84_CIF_FV,
	GPIO85_CIF_LV,
	MIO_CFG_OUT(GPIO56_MT9M111_nOE, AF0, DRIVE_LOW),

	/* Bluetooth */
	MIO_CFG_IN(GPIO14_BT_nACTIVITY, AF0),
	GPIO44_BTUART_CTS,
	GPIO42_BTUART_RXD,
	GPIO45_BTUART_RTS,
	GPIO43_BTUART_TXD,
	MIO_CFG_OUT(GPIO83_BT_ON, AF0, DRIVE_LOW),
	MIO_CFG_OUT(GPIO77_BT_UNKNOWN1, AF0, DRIVE_HIGH),
	MIO_CFG_OUT(GPIO86_BT_MAYBE_nRESET, AF0, DRIVE_HIGH),

	/* GPS */
	MIO_CFG_OUT(GPIO23_GPS_UNKNOWN1, AF0, DRIVE_LOW),
	MIO_CFG_OUT(GPIO26_GPS_ON, AF0, DRIVE_LOW),
	MIO_CFG_OUT(GPIO27_GPS_RESET, AF0, DRIVE_LOW),
	MIO_CFG_OUT(GPIO106_GPS_UNKNOWN2, AF0, DRIVE_LOW),
	MIO_CFG_OUT(GPIO107_GPS_UNKNOWN3, AF0, DRIVE_LOW),
	GPIO46_STUART_RXD,
	GPIO47_STUART_TXD,

	/* GSM */
	MIO_CFG_OUT(GPIO24_GSM_MOD_RESET_CMD, AF0, DRIVE_LOW),
	MIO_CFG_OUT(GPIO88_GSM_nMOD_ON_CMD, AF0, DRIVE_HIGH),
	MIO_CFG_OUT(GPIO90_GSM_nMOD_OFF_CMD, AF0, DRIVE_HIGH),
	MIO_CFG_OUT(GPIO114_GSM_nMOD_DTE_UART_STATE, AF0, DRIVE_HIGH),
	MIO_CFG_IN(GPIO25_GSM_MOD_ON_STATE, AF0),
	MIO_CFG_IN(GPIO113_GSM_EVENT, AF0) | WAKEUP_ON_EDGE_BOTH,
	GPIO34_FFUART_RXD,
	GPIO35_FFUART_CTS,
	GPIO36_FFUART_DCD,
	GPIO37_FFUART_DSR,
	GPIO39_FFUART_TXD,
	GPIO40_FFUART_DTR,
	GPIO41_FFUART_RTS,

	/* Sound */
	GPIO28_AC97_BITCLK,
	GPIO29_AC97_SDATA_IN_0,
	GPIO30_AC97_SDATA_OUT,
	GPIO31_AC97_SYNC,
	GPIO89_AC97_SYSCLK,
	MIO_CFG_IN(GPIO12_HPJACK_INSERT, AF0),

	/* Leds */
	MIO_CFG_OUT(GPIO10_LED_nCharging, AF0, DRIVE_HIGH),
	MIO_CFG_OUT(GPIO97_LED_nBlue, AF0, DRIVE_HIGH),
	MIO_CFG_OUT(GPIO98_LED_nOrange, AF0, DRIVE_HIGH),
	MIO_CFG_OUT(GPIO82_LED_nVibra, AF0, DRIVE_HIGH),
	MIO_CFG_OUT(GPIO115_LED_nKeyboard, AF0, DRIVE_HIGH),

	/* Keyboard */
	MIO_CFG_IN(GPIO0_KEY_POWER, AF0) | WAKEUP_ON_EDGE_BOTH,
	MIO_CFG_IN(GPIO93_KEY_VOLUME_UP, AF0),
	MIO_CFG_IN(GPIO94_KEY_VOLUME_DOWN, AF0),
	GPIO100_KP_MKIN_0,
	GPIO101_KP_MKIN_1,
	GPIO102_KP_MKIN_2,
	GPIO103_KP_MKOUT_0,
	GPIO104_KP_MKOUT_1,
	GPIO105_KP_MKOUT_2,

	/* I2C */
	GPIO117_I2C_SCL,
	GPIO118_I2C_SDA,

	/* Unknown */
	MFP_CFG_IN(GPIO20, AF0),
	MFP_CFG_IN(GPIO21, AF0),
	MFP_CFG_IN(GPIO33, AF0),
	MFP_CFG_OUT(GPIO49, AF0, DRIVE_HIGH),
	MFP_CFG_OUT(GPIO57, AF0, DRIVE_HIGH),
	MFP_CFG_IN(GPIO96, AF0),
	MFP_CFG_OUT(GPIO116, AF0, DRIVE_HIGH),
पूर्ण;

अटल काष्ठा pwm_lookup mioa701_pwm_lookup[] = अणु
	PWM_LOOKUP("pxa27x-pwm.0", 0, "pwm-backlight", शून्य, 4000 * 1024,
		   PWM_POLARITY_NORMAL),
पूर्ण;

/* LCD Screen and Backlight */
अटल काष्ठा platक्रमm_pwm_backlight_data mioa701_backlight_data = अणु
	.max_brightness	= 100,
	.dft_brightness	= 50,
पूर्ण;

/*
 * LTM0305A776C LCD panel timings
 *
 * see:
 *  - the LTM0305A776C datasheet,
 *  - and the PXA27x Programmers' manual
 */
अटल काष्ठा pxafb_mode_info mioa701_lपंचांग0305a776c = अणु
	.pixघड़ी		= 220000,	/* CLK=4.545 MHz */
	.xres			= 240,
	.yres			= 320,
	.bpp			= 16,
	.hsync_len		= 4,
	.vsync_len		= 2,
	.left_margin		= 6,
	.right_margin		= 4,
	.upper_margin		= 5,
	.lower_margin		= 3,
पूर्ण;

अटल व्योम mioa701_lcd_घातer(पूर्णांक on, काष्ठा fb_var_screeninfo *si)
अणु
	gpio_set_value(GPIO87_LCD_POWER, on);
पूर्ण

अटल काष्ठा pxafb_mach_info mioa701_pxafb_info = अणु
	.modes			= &mioa701_lपंचांग0305a776c,
	.num_modes		= 1,
	.lcd_conn		= LCD_COLOR_TFT_16BPP | LCD_PCLK_EDGE_FALL,
	.pxafb_lcd_घातer	= mioa701_lcd_घातer,
पूर्ण;

/*
 * Keyboard configuration
 */
अटल स्थिर अचिन्हित पूर्णांक mioa701_matrix_keys[] = अणु
	KEY(0, 0, KEY_UP),
	KEY(0, 1, KEY_RIGHT),
	KEY(0, 2, KEY_MEDIA),
	KEY(1, 0, KEY_DOWN),
	KEY(1, 1, KEY_ENTER),
	KEY(1, 2, KEY_CONNECT),	/* GPS key */
	KEY(2, 0, KEY_LEFT),
	KEY(2, 1, KEY_PHONE),	/* Phone Green key */
	KEY(2, 2, KEY_CAMERA)	/* Camera key */
पूर्ण;

अटल काष्ठा matrix_keymap_data mioa701_matrix_keymap_data = अणु
	.keymap			= mioa701_matrix_keys,
	.keymap_size		= ARRAY_SIZE(mioa701_matrix_keys),
पूर्ण;

अटल काष्ठा pxa27x_keypad_platक्रमm_data mioa701_keypad_info = अणु
	.matrix_key_rows = 3,
	.matrix_key_cols = 3,
	.matrix_keymap_data = &mioa701_matrix_keymap_data,
पूर्ण;

/*
 * GPIO Key Configuration
 */
#घोषणा MIO_KEY(key, _gpio, _desc, _wakeup) \
	अणु .code = (key), .gpio = (_gpio), .active_low = 0, \
	.desc = (_desc), .type = EV_KEY, .wakeup = (_wakeup) पूर्ण
अटल काष्ठा gpio_keys_button mioa701_button_table[] = अणु
	MIO_KEY(KEY_EXIT, GPIO0_KEY_POWER, "Power button", 1),
	MIO_KEY(KEY_VOLUMEUP, GPIO93_KEY_VOLUME_UP, "Volume up", 0),
	MIO_KEY(KEY_VOLUMEDOWN, GPIO94_KEY_VOLUME_DOWN, "Volume down", 0),
	MIO_KEY(KEY_HP, GPIO12_HPJACK_INSERT, "HP jack detect", 0)
पूर्ण;

अटल काष्ठा gpio_keys_platक्रमm_data mioa701_gpio_keys_data = अणु
	.buttons  = mioa701_button_table,
	.nbuttons = ARRAY_SIZE(mioa701_button_table),
पूर्ण;

/*
 * Leds and vibrator
 */
#घोषणा ONE_LED(_gpio, _name) \
अणु .gpio = (_gpio), .name = (_name), .active_low = true पूर्ण
अटल काष्ठा gpio_led gpio_leds[] = अणु
	ONE_LED(GPIO10_LED_nCharging, "mioa701:charging"),
	ONE_LED(GPIO97_LED_nBlue, "mioa701:blue"),
	ONE_LED(GPIO98_LED_nOrange, "mioa701:orange"),
	ONE_LED(GPIO82_LED_nVibra, "mioa701:vibra"),
	ONE_LED(GPIO115_LED_nKeyboard, "mioa701:keyboard")
पूर्ण;

अटल काष्ठा gpio_led_platक्रमm_data gpio_led_info = अणु
	.leds = gpio_leds,
	.num_leds = ARRAY_SIZE(gpio_leds),
पूर्ण;

/*
 * GSM Sagem XS200 chip
 *
 * GSM handling was purged from kernel. For history, this is the way to go :
 *   - init : GPIO24_GSM_MOD_RESET_CMD = 0, GPIO114_GSM_nMOD_DTE_UART_STATE = 1
 *            GPIO88_GSM_nMOD_ON_CMD = 1, GPIO90_GSM_nMOD_OFF_CMD = 1
 *   - reset : GPIO24_GSM_MOD_RESET_CMD = 1, msleep(100),
 *             GPIO24_GSM_MOD_RESET_CMD = 0
 *   - turn on  : GPIO88_GSM_nMOD_ON_CMD = 0, msleep(1000),
 *                GPIO88_GSM_nMOD_ON_CMD = 1
 *   - turn off : GPIO90_GSM_nMOD_OFF_CMD = 0, msleep(1000),
 *                GPIO90_GSM_nMOD_OFF_CMD = 1
 */
अटल पूर्णांक is_gsm_on(व्योम)
अणु
	पूर्णांक is_on;

	is_on = !!gpio_get_value(GPIO25_GSM_MOD_ON_STATE);
	वापस is_on;
पूर्ण

irqवापस_t gsm_on_irq(पूर्णांक irq, व्योम *p)
अणु
	prपूर्णांकk(KERN_DEBUG "Mioa701: GSM status changed to %s\n",
	       is_gsm_on() ? "on" : "off");
	वापस IRQ_HANDLED;
पूर्ण

अटल काष्ठा gpio gsm_gpios[] = अणु
	अणु GPIO25_GSM_MOD_ON_STATE, GPIOF_IN, "GSM state" पूर्ण,
	अणु GPIO113_GSM_EVENT, GPIOF_IN, "GSM event" पूर्ण,
पूर्ण;

अटल पूर्णांक __init gsm_init(व्योम)
अणु
	पूर्णांक rc;

	rc = gpio_request_array(ARRAY_AND_SIZE(gsm_gpios));
	अगर (rc)
		जाओ err_gpio;
	rc = request_irq(gpio_to_irq(GPIO25_GSM_MOD_ON_STATE), gsm_on_irq,
			 IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING,
			 "GSM XS200 Power Irq", शून्य);
	अगर (rc)
		जाओ err_irq;

	gpio_set_wake(GPIO113_GSM_EVENT, 1);
	वापस 0;

err_irq:
	prपूर्णांकk(KERN_ERR "Mioa701: Can't request GSM_ON irq\n");
	gpio_मुक्त_array(ARRAY_AND_SIZE(gsm_gpios));
err_gpio:
	prपूर्णांकk(KERN_ERR "Mioa701: gsm not available\n");
	वापस rc;
पूर्ण

अटल व्योम gsm_निकास(व्योम)
अणु
	मुक्त_irq(gpio_to_irq(GPIO25_GSM_MOD_ON_STATE), शून्य);
	gpio_मुक्त_array(ARRAY_AND_SIZE(gsm_gpios));
पूर्ण

/*
 * Bluetooth BRF6150 chip
 *
 * BT handling was purged from kernel. For history, this is the way to go :
 * - turn on  : GPIO83_BT_ON = 1
 * - turn off : GPIO83_BT_ON = 0
 */

/*
 * GPS Sirf Star III chip
 *
 * GPS handling was purged from kernel. For history, this is the way to go :
 * - init : GPIO23_GPS_UNKNOWN1 = 1, GPIO26_GPS_ON = 0, GPIO27_GPS_RESET = 0
 *          GPIO106_GPS_UNKNOWN2 = 0, GPIO107_GPS_UNKNOWN3 = 0
 * - turn on  : GPIO27_GPS_RESET = 1, GPIO26_GPS_ON = 1
 * - turn off : GPIO26_GPS_ON = 0, GPIO27_GPS_RESET = 0
 */

/*
 * USB UDC
 */
अटल पूर्णांक is_usb_connected(व्योम)
अणु
	वापस !gpio_get_value(GPIO13_nUSB_DETECT);
पूर्ण

अटल काष्ठा pxa2xx_udc_mach_info mioa701_udc_info = अणु
	.udc_is_connected = is_usb_connected,
	.gpio_pullup	  = GPIO22_USB_ENABLE,
पूर्ण;

अटल काष्ठा gpiod_lookup_table gpio_vbus_gpiod_table = अणु
	.dev_id = "gpio-vbus",
	.table = अणु
		GPIO_LOOKUP("gpio-pxa", GPIO13_nUSB_DETECT,
			    "vbus", GPIO_ACTIVE_LOW),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

/*
 * SDIO/MMC Card controller
 */
/**
 * The card detect पूर्णांकerrupt isn't debounced so we delay it by 250ms
 * to give the card a chance to fully insert/eject.
 */
अटल काष्ठा pxamci_platक्रमm_data mioa701_mci_info = अणु
	.detect_delay_ms	= 250,
	.ocr_mask 		= MMC_VDD_32_33 | MMC_VDD_33_34,
पूर्ण;

अटल काष्ठा gpiod_lookup_table mioa701_mci_gpio_table = अणु
	.dev_id = "pxa2xx-mci.0",
	.table = अणु
		/* Card detect on GPIO 15 */
		GPIO_LOOKUP("gpio-pxa", GPIO15_SDIO_INSERT,
			    "cd", GPIO_ACTIVE_LOW),
		/* Write protect on GPIO 78 */
		GPIO_LOOKUP("gpio-pxa", GPIO78_SDIO_RO,
			    "wp", GPIO_ACTIVE_LOW),
		/* Power on GPIO 91 */
		GPIO_LOOKUP("gpio-pxa", GPIO91_SDIO_EN,
			    "power", GPIO_ACTIVE_HIGH),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

/* FlashRAM */
अटल काष्ठा resource करोcg3_resource = अणु
	.start = PXA_CS0_PHYS,
	.end   = PXA_CS0_PHYS + SZ_8K - 1,
	.flags = IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा platक्रमm_device करोcg3 = अणु
	.name	       = "docg3",
	.id	       = -1,
	.resource      = &करोcg3_resource,
	.num_resources = 1,
	.dev = अणु
		.platक्रमm_data = शून्य,
	पूर्ण,
पूर्ण;

/*
 * Suspend/Resume bootstrap management
 *
 * MIO A701 reboot sequence is highly ROM dependent. From the one dissassembled,
 * this sequence is as follows :
 *   - disables पूर्णांकerrupts
 *   - initialize SDRAM (self refresh RAM पूर्णांकo active RAM)
 *   - initialize GPIOs (depends on value at 0xa020b020)
 *   - initialize coprossessors
 *   - अगर edge detect on PWR_SCL(GPIO3), then proceed to cold start
 *   - or अगर value at 0xa020b000 not equal to 0x0f0f0f0f, proceed to cold start
 *   - अन्यथा करो a resume, ie. jump to addr 0xa0100000
 */
#घोषणा RESUME_ENABLE_ADDR	0xa020b000
#घोषणा RESUME_ENABLE_VAL	0x0f0f0f0f
#घोषणा RESUME_BT_ADDR		0xa020b020
#घोषणा RESUME_UNKNOWN_ADDR	0xa020b024
#घोषणा RESUME_VECTOR_ADDR	0xa0100000
#घोषणा BOOTSTRAP_WORDS		mioa701_bootstrap_lg/4

अटल u32 *save_buffer;

अटल व्योम install_bootstrap(व्योम)
अणु
	पूर्णांक i;
	u32 *rom_bootstrap  = phys_to_virt(RESUME_VECTOR_ADDR);
	u32 *src = &mioa701_bootstrap;

	क्रम (i = 0; i < BOOTSTRAP_WORDS; i++)
		rom_bootstrap[i] = src[i];
पूर्ण


अटल पूर्णांक mioa701_sys_suspend(व्योम)
अणु
	पूर्णांक i = 0, is_bt_on;
	u32 *mem_resume_vector	= phys_to_virt(RESUME_VECTOR_ADDR);
	u32 *mem_resume_enabler = phys_to_virt(RESUME_ENABLE_ADDR);
	u32 *mem_resume_bt	= phys_to_virt(RESUME_BT_ADDR);
	u32 *mem_resume_unknown	= phys_to_virt(RESUME_UNKNOWN_ADDR);

	/* Devices prepare suspend */
	is_bt_on = !!gpio_get_value(GPIO83_BT_ON);
	pxa2xx_mfp_set_lpm(GPIO83_BT_ON,
			   is_bt_on ? MFP_LPM_DRIVE_HIGH : MFP_LPM_DRIVE_LOW);

	क्रम (i = 0; i < BOOTSTRAP_WORDS; i++)
		save_buffer[i] = mem_resume_vector[i];
	save_buffer[i++] = *mem_resume_enabler;
	save_buffer[i++] = *mem_resume_bt;
	save_buffer[i++] = *mem_resume_unknown;

	*mem_resume_enabler = RESUME_ENABLE_VAL;
	*mem_resume_bt	    = is_bt_on;

	install_bootstrap();
	वापस 0;
पूर्ण

अटल व्योम mioa701_sys_resume(व्योम)
अणु
	पूर्णांक i = 0;
	u32 *mem_resume_vector	= phys_to_virt(RESUME_VECTOR_ADDR);
	u32 *mem_resume_enabler = phys_to_virt(RESUME_ENABLE_ADDR);
	u32 *mem_resume_bt	= phys_to_virt(RESUME_BT_ADDR);
	u32 *mem_resume_unknown	= phys_to_virt(RESUME_UNKNOWN_ADDR);

	क्रम (i = 0; i < BOOTSTRAP_WORDS; i++)
		mem_resume_vector[i] = save_buffer[i];
	*mem_resume_enabler = save_buffer[i++];
	*mem_resume_bt	    = save_buffer[i++];
	*mem_resume_unknown = save_buffer[i++];
पूर्ण

अटल काष्ठा syscore_ops mioa701_syscore_ops = अणु
	.suspend	= mioa701_sys_suspend,
	.resume		= mioa701_sys_resume,
पूर्ण;

अटल पूर्णांक __init bootstrap_init(व्योम)
अणु
	पूर्णांक save_size = mioa701_bootstrap_lg + (माप(u32) * 3);

	रेजिस्टर_syscore_ops(&mioa701_syscore_ops);

	save_buffer = kदो_स्मृति(save_size, GFP_KERNEL);
	अगर (!save_buffer)
		वापस -ENOMEM;
	prपूर्णांकk(KERN_INFO "MioA701: allocated %d bytes for bootstrap\n",
	       save_size);
	वापस 0;
पूर्ण

अटल व्योम bootstrap_निकास(व्योम)
अणु
	kमुक्त(save_buffer);
	unरेजिस्टर_syscore_ops(&mioa701_syscore_ops);

	prपूर्णांकk(KERN_CRIT "Unregistering mioa701 suspend will hang next"
	       "resume !!!\n");
पूर्ण

/*
 * Power Supply
 */
अटल अक्षर *supplicants[] = अणु
	"mioa701_battery"
पूर्ण;

अटल पूर्णांक is_ac_connected(व्योम)
अणु
	वापस gpio_get_value(GPIO96_AC_DETECT);
पूर्ण

अटल व्योम mioa701_set_अक्षरge(पूर्णांक flags)
अणु
	gpio_set_value(GPIO9_CHARGE_EN, (flags == PDA_POWER_CHARGE_USB));
पूर्ण

अटल काष्ठा pda_घातer_pdata घातer_pdata = अणु
	.is_ac_online	= is_ac_connected,
	.is_usb_online	= is_usb_connected,
	.set_अक्षरge = mioa701_set_अक्षरge,
	.supplied_to = supplicants,
	.num_supplicants = ARRAY_SIZE(supplicants),
पूर्ण;

अटल काष्ठा resource घातer_resources[] = अणु
	[0] = अणु
		.name	= "ac",
		.start	= PXA_GPIO_TO_IRQ(GPIO96_AC_DETECT),
		.end	= PXA_GPIO_TO_IRQ(GPIO96_AC_DETECT),
		.flags	= IORESOURCE_IRQ | IORESOURCE_IRQ_HIGHEDGE |
		IORESOURCE_IRQ_LOWEDGE,
	पूर्ण,
	[1] = अणु
		.name	= "usb",
		.start	= PXA_GPIO_TO_IRQ(GPIO13_nUSB_DETECT),
		.end	= PXA_GPIO_TO_IRQ(GPIO13_nUSB_DETECT),
		.flags	= IORESOURCE_IRQ | IORESOURCE_IRQ_HIGHEDGE |
		IORESOURCE_IRQ_LOWEDGE,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device घातer_dev = अणु
	.name		= "pda-power",
	.id		= -1,
	.resource	= घातer_resources,
	.num_resources	= ARRAY_SIZE(घातer_resources),
	.dev = अणु
		.platक्रमm_data	= &घातer_pdata,
	पूर्ण,
पूर्ण;

अटल काष्ठा wm97xx_batt_pdata mioa701_battery_data = अणु
	.batt_aux	= WM97XX_AUX_ID1,
	.temp_aux	= -1,
	.min_voltage	= 0xc00,
	.max_voltage	= 0xfc0,
	.batt_tech	= POWER_SUPPLY_TECHNOLOGY_LION,
	.batt_भाग	= 1,
	.batt_mult	= 1,
	.batt_name	= "mioa701_battery",
पूर्ण;

अटल काष्ठा wm97xx_pdata mioa701_wm97xx_pdata = अणु
	.batt_pdata	= &mioa701_battery_data,
पूर्ण;

/*
 * Voltage regulation
 */
अटल काष्ठा regulator_consumer_supply max1586_consumers[] = अणु
	REGULATOR_SUPPLY("vcc_core", शून्य),
पूर्ण;

अटल काष्ठा regulator_init_data max1586_v3_info = अणु
	.स्थिरraपूर्णांकs = अणु
		.name = "vcc_core range",
		.min_uV = 1000000,
		.max_uV = 1705000,
		.always_on = 1,
		.valid_ops_mask = REGULATOR_CHANGE_VOLTAGE,
	पूर्ण,
	.num_consumer_supplies = ARRAY_SIZE(max1586_consumers),
	.consumer_supplies = max1586_consumers,
पूर्ण;

अटल काष्ठा max1586_subdev_data max1586_subdevs[] = अणु
	अणु .name = "vcc_core", .id = MAX1586_V3,
	  .platक्रमm_data = &max1586_v3_info पूर्ण,
पूर्ण;

अटल काष्ठा max1586_platक्रमm_data max1586_info = अणु
	.subdevs = max1586_subdevs,
	.num_subdevs = ARRAY_SIZE(max1586_subdevs),
	.v3_gain = MAX1586_GAIN_NO_R24, /* 700..1475 mV */
पूर्ण;

/*
 * Camera पूर्णांकerface
 */
काष्ठा pxacamera_platक्रमm_data mioa701_pxacamera_platक्रमm_data = अणु
	.flags  = PXA_CAMERA_MASTER | PXA_CAMERA_DATAWIDTH_8 |
		PXA_CAMERA_PCLK_EN | PXA_CAMERA_MCLK_EN,
	.mclk_10khz = 5000,
	.sensor_i2c_adapter_id = 0,
	.sensor_i2c_address = 0x5d,
पूर्ण;

अटल काष्ठा i2c_board_info __initdata mioa701_pi2c_devices[] = अणु
	अणु
		I2C_BOARD_INFO("max1586", 0x14),
		.platक्रमm_data = &max1586_info,
	पूर्ण,
पूर्ण;

/* Board I2C devices. */
अटल काष्ठा i2c_board_info mioa701_i2c_devices[] = अणु
	अणु
		I2C_BOARD_INFO("mt9m111", 0x5d),
	पूर्ण,
पूर्ण;

काष्ठा i2c_pxa_platक्रमm_data i2c_pdata = अणु
	.fast_mode = 1,
पूर्ण;

अटल pxa2xx_audio_ops_t mioa701_ac97_info = अणु
	.reset_gpio = 95,
	.codec_pdata = अणु &mioa701_wm97xx_pdata, पूर्ण,
पूर्ण;

/*
 * Mio global
 */

/* Devices */
#घोषणा MIO_PARENT_DEV(var, strname, tparent, pdata)	\
अटल काष्ठा platक्रमm_device var = अणु			\
	.name		= strname,			\
	.id		= -1,				\
	.dev		= अणु				\
		.platक्रमm_data = pdata,			\
		.parent	= tparent,			\
	पूर्ण,						\
पूर्ण;
#घोषणा MIO_SIMPLE_DEV(var, strname, pdata)	\
	MIO_PARENT_DEV(var, strname, शून्य, pdata)

MIO_SIMPLE_DEV(mioa701_gpio_keys, "gpio-keys",	    &mioa701_gpio_keys_data)
MIO_PARENT_DEV(mioa701_backlight, "pwm-backlight",  &pxa27x_device_pwm0.dev,
		&mioa701_backlight_data);
MIO_SIMPLE_DEV(mioa701_led,	  "leds-gpio",	    &gpio_led_info)
MIO_SIMPLE_DEV(pxa2xx_pcm,	  "pxa2xx-pcm",	    शून्य)
MIO_SIMPLE_DEV(mioa701_sound,	  "mioa701-wm9713", शून्य)
MIO_SIMPLE_DEV(mioa701_board,	  "mioa701-board",  शून्य)
MIO_SIMPLE_DEV(gpio_vbus,	  "gpio-vbus",      शून्य);

अटल काष्ठा platक्रमm_device *devices[] __initdata = अणु
	&mioa701_gpio_keys,
	&mioa701_backlight,
	&mioa701_led,
	&pxa2xx_pcm,
	&mioa701_sound,
	&घातer_dev,
	&करोcg3,
	&gpio_vbus,
	&mioa701_board,
पूर्ण;

अटल व्योम mioa701_machine_निकास(व्योम);

अटल व्योम mioa701_घातeroff(व्योम)
अणु
	mioa701_machine_निकास();
	pxa_restart(REBOOT_SOFT, शून्य);
पूर्ण

अटल व्योम mioa701_restart(क्रमागत reboot_mode c, स्थिर अक्षर *cmd)
अणु
	mioa701_machine_निकास();
	pxa_restart(REBOOT_SOFT, cmd);
पूर्ण

अटल काष्ठा gpio global_gpios[] = अणु
	अणु GPIO9_CHARGE_EN, GPIOF_OUT_INIT_HIGH, "Charger enable" पूर्ण,
	अणु GPIO18_POWEROFF, GPIOF_OUT_INIT_LOW, "Power Off" पूर्ण,
	अणु GPIO87_LCD_POWER, GPIOF_OUT_INIT_LOW, "LCD Power" पूर्ण,
	अणु GPIO56_MT9M111_nOE, GPIOF_OUT_INIT_LOW, "Camera nOE" पूर्ण,
पूर्ण;

अटल काष्ठा regulator_consumer_supply fixed_5v0_consumers[] = अणु
	REGULATOR_SUPPLY("power", "pwm-backlight"),
पूर्ण;

अटल व्योम __init mioa701_machine_init(व्योम)
अणु
	पूर्णांक rc;

	PSLR  = 0xff100000; /* SYSDEL=125ms, PWRDEL=125ms, PSLR_SL_ROD=1 */
	PCFR = PCFR_DC_EN | PCFR_GPR_EN | PCFR_OPDE;
	RTTR = 32768 - 1; /* Reset crazy WinCE value */
	UP2OCR = UP2OCR_HXOE;

	/*
	 * Set up the flash memory : DiskOnChip G3 on first अटल memory bank
	 */
	__raw_ग_लिखोl(0x7ff02dd8, MSC0);
	__raw_ग_लिखोl(0x0001c391, MCMEM0);
	__raw_ग_लिखोl(0x0001c391, MCATT0);
	__raw_ग_लिखोl(0x0001c391, MCIO0);


	pxa2xx_mfp_config(ARRAY_AND_SIZE(mioa701_pin_config));
	pxa_set_ffuart_info(शून्य);
	pxa_set_btuart_info(शून्य);
	pxa_set_stuart_info(शून्य);
	rc = gpio_request_array(ARRAY_AND_SIZE(global_gpios));
	अगर (rc)
		pr_err("MioA701: Failed to request GPIOs: %d", rc);
	bootstrap_init();
	pxa_set_fb_info(शून्य, &mioa701_pxafb_info);
	gpiod_add_lookup_table(&mioa701_mci_gpio_table);
	pxa_set_mci_info(&mioa701_mci_info);
	pxa_set_keypad_info(&mioa701_keypad_info);
	pxa_set_udc_info(&mioa701_udc_info);
	pxa_set_ac97_info(&mioa701_ac97_info);
	pm_घातer_off = mioa701_घातeroff;
	pwm_add_table(mioa701_pwm_lookup, ARRAY_SIZE(mioa701_pwm_lookup));
	gpiod_add_lookup_table(&gpio_vbus_gpiod_table);
	platक्रमm_add_devices(devices, ARRAY_SIZE(devices));
	gsm_init();

	i2c_रेजिस्टर_board_info(0, ARRAY_AND_SIZE(mioa701_i2c_devices));
	i2c_रेजिस्टर_board_info(1, ARRAY_AND_SIZE(mioa701_pi2c_devices));
	pxa_set_i2c_info(&i2c_pdata);
	pxa27x_set_i2c_घातer_info(शून्य);
	pxa_set_camera_info(&mioa701_pxacamera_platक्रमm_data);

	regulator_रेजिस्टर_always_on(0, "fixed-5.0V", fixed_5v0_consumers,
				     ARRAY_SIZE(fixed_5v0_consumers),
				     5000000);
	regulator_has_full_स्थिरraपूर्णांकs();
पूर्ण

अटल व्योम mioa701_machine_निकास(व्योम)
अणु
	bootstrap_निकास();
	gsm_निकास();
पूर्ण

MACHINE_START(MIOA701, "MIO A701")
	.atag_offset	= 0x100,
	.map_io		= &pxa27x_map_io,
	.nr_irqs	= PXA_NR_IRQS,
	.init_irq	= &pxa27x_init_irq,
	.handle_irq	= &pxa27x_handle_irq,
	.init_machine	= mioa701_machine_init,
	.init_समय	= pxa_समयr_init,
	.restart	= mioa701_restart,
MACHINE_END
