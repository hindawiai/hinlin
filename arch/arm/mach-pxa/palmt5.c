<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Hardware definitions क्रम Palm Tungsten|T5
 *
 * Author:	Marek Vasut <marek.vasut@gmail.com>
 *
 * Based on work of:
 *		Ales Snuparek <snuparek@atlas.cz>
 *		Justin Kendrick <twilightsentry@gmail.com>
 *		Riअक्षरdT5 <riअक्षरd_t5@users.sourceक्रमge.net>
 *
 * (find more info at www.hackndev.com)
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/delay.h>
#समावेश <linux/irq.h>
#समावेश <linux/gpio_keys.h>
#समावेश <linux/input.h>
#समावेश <linux/memblock.h>
#समावेश <linux/pda_घातer.h>
#समावेश <linux/pwm_backlight.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/wm97xx.h>
#समावेश <linux/घातer_supply.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>

#समावेश "pxa27x.h"
#समावेश <mach/audपन.स>
#समावेश "palmt5.h"
#समावेश <linux/platक्रमm_data/mmc-pxamci.h>
#समावेश <linux/platक्रमm_data/video-pxafb.h>
#समावेश <linux/platक्रमm_data/irda-pxaficp.h>
#समावेश <linux/platक्रमm_data/keypad-pxa27x.h>
#समावेश "udc.h"
#समावेश <linux/platक्रमm_data/asoc-palm27x.h>
#समावेश "palm27x.h"

#समावेश "generic.h"
#समावेश "devices.h"

/******************************************************************************
 * Pin configuration
 ******************************************************************************/
अटल अचिन्हित दीर्घ palmt5_pin_config[] __initdata = अणु
	/* MMC */
	GPIO32_MMC_CLK,
	GPIO92_MMC_DAT_0,
	GPIO109_MMC_DAT_1,
	GPIO110_MMC_DAT_2,
	GPIO111_MMC_DAT_3,
	GPIO112_MMC_CMD,
	GPIO14_GPIO,	/* SD detect */
	GPIO114_GPIO,	/* SD घातer */
	GPIO115_GPIO,	/* SD r/o चयन */

	/* AC97 */
	GPIO28_AC97_BITCLK,
	GPIO29_AC97_SDATA_IN_0,
	GPIO30_AC97_SDATA_OUT,
	GPIO31_AC97_SYNC,
	GPIO89_AC97_SYSCLK,
	GPIO95_AC97_nRESET,

	/* IrDA */
	GPIO40_GPIO,	/* ir disable */
	GPIO46_FICP_RXD,
	GPIO47_FICP_TXD,

	/* USB */
	GPIO15_GPIO,	/* usb detect */
	GPIO93_GPIO,	/* usb घातer */

	/* MATRIX KEYPAD */
	GPIO100_KP_MKIN_0 | WAKEUP_ON_LEVEL_HIGH,
	GPIO101_KP_MKIN_1 | WAKEUP_ON_LEVEL_HIGH,
	GPIO102_KP_MKIN_2 | WAKEUP_ON_LEVEL_HIGH,
	GPIO97_KP_MKIN_3 | WAKEUP_ON_LEVEL_HIGH,
	GPIO103_KP_MKOUT_0,
	GPIO104_KP_MKOUT_1,
	GPIO105_KP_MKOUT_2,

	/* LCD */
	GPIOxx_LCD_TFT_16BPP,

	/* PWM */
	GPIO16_PWM0_OUT,

	/* FFUART */
	GPIO34_FFUART_RXD,
	GPIO39_FFUART_TXD,

	/* MISC */
	GPIO10_GPIO,	/* hotsync button */
	GPIO90_GPIO,	/* घातer detect */
	GPIO107_GPIO,	/* earphone detect */
पूर्ण;

/******************************************************************************
 * GPIO keyboard
 ******************************************************************************/
#अगर defined(CONFIG_KEYBOARD_PXA27x) || defined(CONFIG_KEYBOARD_PXA27x_MODULE)
अटल स्थिर अचिन्हित पूर्णांक palmt5_matrix_keys[] = अणु
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

अटल काष्ठा matrix_keymap_data palmt5_matrix_keymap_data = अणु
	.keymap			= palmt5_matrix_keys,
	.keymap_size		= ARRAY_SIZE(palmt5_matrix_keys),
पूर्ण;

अटल काष्ठा pxa27x_keypad_platक्रमm_data palmt5_keypad_platक्रमm_data = अणु
	.matrix_key_rows	= 4,
	.matrix_key_cols	= 3,
	.matrix_keymap_data	= &palmt5_matrix_keymap_data,

	.debounce_पूर्णांकerval	= 30,
पूर्ण;

अटल व्योम __init palmt5_kpc_init(व्योम)
अणु
	pxa_set_keypad_info(&palmt5_keypad_platक्रमm_data);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम palmt5_kpc_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * GPIO keys
 ******************************************************************************/
#अगर defined(CONFIG_KEYBOARD_GPIO) || defined(CONFIG_KEYBOARD_GPIO_MODULE)
अटल काष्ठा gpio_keys_button palmt5_pxa_buttons[] = अणु
	अणुKEY_F8, GPIO_NR_PALMT5_HOTSYNC_BUTTON_N, 1, "HotSync Button" पूर्ण,
पूर्ण;

अटल काष्ठा gpio_keys_platक्रमm_data palmt5_pxa_keys_data = अणु
	.buttons	= palmt5_pxa_buttons,
	.nbuttons	= ARRAY_SIZE(palmt5_pxa_buttons),
पूर्ण;

अटल काष्ठा platक्रमm_device palmt5_pxa_keys = अणु
	.name	= "gpio-keys",
	.id	= -1,
	.dev	= अणु
		.platक्रमm_data = &palmt5_pxa_keys_data,
	पूर्ण,
पूर्ण;

अटल व्योम __init palmt5_keys_init(व्योम)
अणु
	platक्रमm_device_रेजिस्टर(&palmt5_pxa_keys);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम palmt5_keys_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * Machine init
 ******************************************************************************/
अटल व्योम __init palmt5_reserve(व्योम)
अणु
	memblock_reserve(0xa0200000, 0x1000);
पूर्ण

अटल काष्ठा gpiod_lookup_table palmt5_mci_gpio_table = अणु
	.dev_id = "pxa2xx-mci.0",
	.table = अणु
		GPIO_LOOKUP("gpio-pxa", GPIO_NR_PALMT5_SD_DETECT_N,
			    "cd", GPIO_ACTIVE_LOW),
		GPIO_LOOKUP("gpio-pxa", GPIO_NR_PALMT5_SD_READONLY,
			    "wp", GPIO_ACTIVE_LOW),
		GPIO_LOOKUP("gpio-pxa", GPIO_NR_PALMT5_SD_POWER,
			    "power", GPIO_ACTIVE_HIGH),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल व्योम __init palmt5_init(व्योम)
अणु
	pxa2xx_mfp_config(ARRAY_AND_SIZE(palmt5_pin_config));
	pxa_set_ffuart_info(शून्य);
	pxa_set_btuart_info(शून्य);
	pxa_set_stuart_info(शून्य);

	palm27x_mmc_init(&palmt5_mci_gpio_table);
	palm27x_pm_init(PALMT5_STR_BASE);
	palm27x_lcd_init(-1, &palm_320x480_lcd_mode);
	palm27x_udc_init(GPIO_NR_PALMT5_USB_DETECT_N,
			GPIO_NR_PALMT5_USB_PULLUP, 1);
	palm27x_irda_init(GPIO_NR_PALMT5_IR_DISABLE);
	palm27x_ac97_init(PALMT5_BAT_MIN_VOLTAGE, PALMT5_BAT_MAX_VOLTAGE,
			GPIO_NR_PALMT5_EARPHONE_DETECT, 95);
	palm27x_pwm_init(GPIO_NR_PALMT5_BL_POWER, GPIO_NR_PALMT5_LCD_POWER);
	palm27x_घातer_init(GPIO_NR_PALMT5_POWER_DETECT, -1);
	palm27x_pmic_init();
	palmt5_kpc_init();
	palmt5_keys_init();
पूर्ण

MACHINE_START(PALMT5, "Palm Tungsten|T5")
	.atag_offset	= 0x100,
	.map_io		= pxa27x_map_io,
	.reserve	= palmt5_reserve,
	.nr_irqs	= PXA_NR_IRQS,
	.init_irq	= pxa27x_init_irq,
	.handle_irq	= pxa27x_handle_irq,
	.init_समय	= pxa_समयr_init,
	.init_machine	= palmt5_init,
	.restart	= pxa_restart,
MACHINE_END
