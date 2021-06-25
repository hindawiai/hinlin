<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Hardware definitions क्रम Palm Zire72
 *
 * Authors:
 *	Vladimir "Farcaller" Pouzanov <farcaller@gmail.com>
 *	Sergey Lapin <slapin@ossfans.org>
 *	Alex Osborne <bobofकरोom@gmail.com>
 *	Jan Herman <2hp@seznam.cz>
 *
 * Reग_लिखो क्रम मुख्यline:
 *	Marek Vasut <marek.vasut@gmail.com>
 *
 * (find more info at www.hackndev.com)
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/syscore_ops.h>
#समावेश <linux/delay.h>
#समावेश <linux/irq.h>
#समावेश <linux/gpio_keys.h>
#समावेश <linux/input.h>
#समावेश <linux/pda_घातer.h>
#समावेश <linux/pwm_backlight.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/wm97xx.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/platक्रमm_data/i2c-gpपन.स>
#समावेश <linux/gpio/machine.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/suspend.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>

#समावेश "pxa27x.h"
#समावेश <mach/audपन.स>
#समावेश "palmz72.h"
#समावेश <linux/platक्रमm_data/mmc-pxamci.h>
#समावेश <linux/platक्रमm_data/video-pxafb.h>
#समावेश <linux/platक्रमm_data/irda-pxaficp.h>
#समावेश <linux/platक्रमm_data/keypad-pxa27x.h>
#समावेश "udc.h"
#समावेश <linux/platक्रमm_data/asoc-palm27x.h>
#समावेश "palm27x.h"

#समावेश "pm.h"
#समावेश <linux/platक्रमm_data/media/camera-pxa.h>

#समावेश "generic.h"
#समावेश "devices.h"

/******************************************************************************
 * Pin configuration
 ******************************************************************************/
अटल अचिन्हित दीर्घ palmz72_pin_config[] __initdata = अणु
	/* MMC */
	GPIO32_MMC_CLK,
	GPIO92_MMC_DAT_0,
	GPIO109_MMC_DAT_1,
	GPIO110_MMC_DAT_2,
	GPIO111_MMC_DAT_3,
	GPIO112_MMC_CMD,
	GPIO14_GPIO,	/* SD detect */
	GPIO115_GPIO,	/* SD RO */
	GPIO98_GPIO,	/* SD घातer */

	/* AC97 */
	GPIO28_AC97_BITCLK,
	GPIO29_AC97_SDATA_IN_0,
	GPIO30_AC97_SDATA_OUT,
	GPIO31_AC97_SYNC,
	GPIO89_AC97_SYSCLK,
	GPIO113_AC97_nRESET,

	/* IrDA */
	GPIO49_GPIO,	/* ir disable */
	GPIO46_FICP_RXD,
	GPIO47_FICP_TXD,

	/* PWM */
	GPIO16_PWM0_OUT,

	/* USB */
	GPIO15_GPIO,	/* usb detect */
	GPIO95_GPIO,	/* usb pullup */

	/* Matrix keypad */
	GPIO100_KP_MKIN_0	| WAKEUP_ON_LEVEL_HIGH,
	GPIO101_KP_MKIN_1	| WAKEUP_ON_LEVEL_HIGH,
	GPIO102_KP_MKIN_2	| WAKEUP_ON_LEVEL_HIGH,
	GPIO97_KP_MKIN_3	| WAKEUP_ON_LEVEL_HIGH,
	GPIO103_KP_MKOUT_0,
	GPIO104_KP_MKOUT_1,
	GPIO105_KP_MKOUT_2,

	/* LCD */
	GPIOxx_LCD_TFT_16BPP,

	GPIO20_GPIO,	/* bl घातer */
	GPIO21_GPIO,	/* LCD border चयन */
	GPIO22_GPIO,	/* LCD border color */
	GPIO96_GPIO,	/* lcd घातer */

	/* PXA Camera */
	GPIO81_CIF_DD_0,
	GPIO48_CIF_DD_5,
	GPIO50_CIF_DD_3,
	GPIO51_CIF_DD_2,
	GPIO52_CIF_DD_4,
	GPIO53_CIF_MCLK,
	GPIO54_CIF_PCLK,
	GPIO55_CIF_DD_1,
	GPIO84_CIF_FV,
	GPIO85_CIF_LV,
	GPIO93_CIF_DD_6,
	GPIO108_CIF_DD_7,

	GPIO56_GPIO,	/* OV9640 Powerकरोwn */
	GPIO57_GPIO,	/* OV9640 Reset */
	GPIO91_GPIO,	/* OV9640 Power */

	/* I2C */
	GPIO117_GPIO,	/* I2C_SCL */
	GPIO118_GPIO,	/* I2C_SDA */

	/* Misc. */
	GPIO0_GPIO	| WAKEUP_ON_LEVEL_HIGH,	/* घातer detect */
	GPIO88_GPIO,				/* green led */
	GPIO27_GPIO,				/* WM9712 IRQ */
पूर्ण;

/******************************************************************************
 * GPIO keyboard
 ******************************************************************************/
#अगर defined(CONFIG_KEYBOARD_PXA27x) || defined(CONFIG_KEYBOARD_PXA27x_MODULE)
अटल स्थिर अचिन्हित पूर्णांक palmz72_matrix_keys[] = अणु
	KEY(0, 0, KEY_POWER),
	KEY(0, 1, KEY_F1),
	KEY(0, 2, KEY_ENTER),

	KEY(1, 0, KEY_F2),
	KEY(1, 1, KEY_F3),
	KEY(1, 2, KEY_F4),

	KEY(2, 0, KEY_UP),
	KEY(2, 2, KEY_DOWN),

	KEY(3, 0, KEY_RIGHT),
	KEY(3, 2, KEY_LEFT),
पूर्ण;

अटल काष्ठा matrix_keymap_data almz72_matrix_keymap_data = अणु
	.keymap			= palmz72_matrix_keys,
	.keymap_size		= ARRAY_SIZE(palmz72_matrix_keys),
पूर्ण;

अटल काष्ठा pxa27x_keypad_platक्रमm_data palmz72_keypad_platक्रमm_data = अणु
	.matrix_key_rows	= 4,
	.matrix_key_cols	= 3,
	.matrix_keymap_data	= &almz72_matrix_keymap_data,

	.debounce_पूर्णांकerval	= 30,
पूर्ण;

अटल व्योम __init palmz72_kpc_init(व्योम)
अणु
	pxa_set_keypad_info(&palmz72_keypad_platक्रमm_data);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम palmz72_kpc_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * LEDs
 ******************************************************************************/
#अगर defined(CONFIG_LEDS_GPIO) || defined(CONFIG_LEDS_GPIO_MODULE)
अटल काष्ठा gpio_led gpio_leds[] = अणु
	अणु
		.name			= "palmz72:green:led",
		.शेष_trigger	= "none",
		.gpio			= GPIO_NR_PALMZ72_LED_GREEN,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_led_platक्रमm_data gpio_led_info = अणु
	.leds		= gpio_leds,
	.num_leds	= ARRAY_SIZE(gpio_leds),
पूर्ण;

अटल काष्ठा platक्रमm_device palmz72_leds = अणु
	.name	= "leds-gpio",
	.id	= -1,
	.dev	= अणु
		.platक्रमm_data	= &gpio_led_info,
	पूर्ण
पूर्ण;

अटल व्योम __init palmz72_leds_init(व्योम)
अणु
	platक्रमm_device_रेजिस्टर(&palmz72_leds);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम palmz72_leds_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM

/* We have some black magic here
 * PalmOS ROM on recover expects special काष्ठा physical address
 * to be transferred via PSPR. Using this काष्ठा PalmOS restores
 * its state after sleep. As क्रम Linux, we need to setup it the
 * same way. More than that, PalmOS ROM changes some values in memory.
 * For now only one location is found, which needs special treaपंचांगent.
 * Thanks to Alex Osborne, Andrzej Zaborowski, and lots of other people
 * क्रम पढ़ोing backtraces क्रम me :)
 */

#घोषणा PALMZ72_SAVE_DWORD ((अचिन्हित दीर्घ *)0xc0000050)

अटल काष्ठा palmz72_resume_info palmz72_resume_info = अणु
	.magic0 = 0xb4e6,
	.magic1 = 1,

	/* reset state, MMU off etc */
	.arm_control = 0,
	.aux_control = 0,
	.ttb = 0,
	.करोमुख्य_access = 0,
	.process_id = 0,
पूर्ण;

अटल अचिन्हित दीर्घ store_ptr;

/* syscore_ops क्रम Palm Zire 72 PM */

अटल पूर्णांक palmz72_pm_suspend(व्योम)
अणु
	/* setup the resume_info काष्ठा क्रम the original bootloader */
	palmz72_resume_info.resume_addr = (u32) cpu_resume;

	/* Storing memory touched by ROM */
	store_ptr = *PALMZ72_SAVE_DWORD;

	/* Setting PSPR to a proper value */
	PSPR = __pa_symbol(&palmz72_resume_info);

	वापस 0;
पूर्ण

अटल व्योम palmz72_pm_resume(व्योम)
अणु
	*PALMZ72_SAVE_DWORD = store_ptr;
पूर्ण

अटल काष्ठा syscore_ops palmz72_pm_syscore_ops = अणु
	.suspend = palmz72_pm_suspend,
	.resume = palmz72_pm_resume,
पूर्ण;

अटल पूर्णांक __init palmz72_pm_init(व्योम)
अणु
	अगर (machine_is_palmz72()) अणु
		रेजिस्टर_syscore_ops(&palmz72_pm_syscore_ops);
		वापस 0;
	पूर्ण
	वापस -ENODEV;
पूर्ण

device_initcall(palmz72_pm_init);
#पूर्ण_अगर

अटल काष्ठा gpiod_lookup_table palmz72_mci_gpio_table = अणु
	.dev_id = "pxa2xx-mci.0",
	.table = अणु
		GPIO_LOOKUP("gpio-pxa", GPIO_NR_PALMZ72_SD_DETECT_N,
			    "cd", GPIO_ACTIVE_LOW),
		GPIO_LOOKUP("gpio-pxa", GPIO_NR_PALMZ72_SD_RO,
			    "wp", GPIO_ACTIVE_LOW),
		GPIO_LOOKUP("gpio-pxa", GPIO_NR_PALMZ72_SD_POWER_N,
			    "power", GPIO_ACTIVE_LOW),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

/******************************************************************************
 * Machine init
 ******************************************************************************/
अटल व्योम __init palmz72_init(व्योम)
अणु
	pxa2xx_mfp_config(ARRAY_AND_SIZE(palmz72_pin_config));
	pxa_set_ffuart_info(शून्य);
	pxa_set_btuart_info(शून्य);
	pxa_set_stuart_info(शून्य);

	palm27x_mmc_init(&palmz72_mci_gpio_table);
	palm27x_lcd_init(-1, &palm_320x320_lcd_mode);
	palm27x_udc_init(GPIO_NR_PALMZ72_USB_DETECT_N,
			GPIO_NR_PALMZ72_USB_PULLUP, 0);
	palm27x_irda_init(GPIO_NR_PALMZ72_IR_DISABLE);
	palm27x_ac97_init(PALMZ72_BAT_MIN_VOLTAGE, PALMZ72_BAT_MAX_VOLTAGE,
			-1, 113);
	palm27x_pwm_init(-1, -1);
	palm27x_घातer_init(-1, -1);
	palm27x_pmic_init();
	palmz72_kpc_init();
	palmz72_leds_init();
पूर्ण

MACHINE_START(PALMZ72, "Palm Zire72")
	.atag_offset	= 0x100,
	.map_io		= pxa27x_map_io,
	.nr_irqs	= PXA_NR_IRQS,
	.init_irq	= pxa27x_init_irq,
	.handle_irq	= pxa27x_handle_irq,
	.init_समय	= pxa_समयr_init,
	.init_machine	= palmz72_init,
	.restart	= pxa_restart,
MACHINE_END
