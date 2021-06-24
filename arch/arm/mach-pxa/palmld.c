<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Hardware definitions क्रम Palm LअगरeDrive
 *
 * Author:     Marek Vasut <marek.vasut@gmail.com>
 *
 * Based on work of:
 *		Alex Osborne <ato@meshy.org>
 *
 * (find more info at www.hackndev.com)
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/delay.h>
#समावेश <linux/irq.h>
#समावेश <linux/gpio_keys.h>
#समावेश <linux/input.h>
#समावेश <linux/pda_घातer.h>
#समावेश <linux/pwm_backlight.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/wm97xx.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/mtd/physmap.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>

#समावेश "pxa27x.h"
#समावेश <mach/audपन.स>
#समावेश <mach/palmld.h>
#समावेश <linux/platक्रमm_data/mmc-pxamci.h>
#समावेश <linux/platक्रमm_data/video-pxafb.h>
#समावेश <linux/platक्रमm_data/irda-pxaficp.h>
#समावेश <linux/platक्रमm_data/keypad-pxa27x.h>
#समावेश <linux/platक्रमm_data/asoc-palm27x.h>
#समावेश "palm27x.h"

#समावेश "generic.h"
#समावेश "devices.h"

/******************************************************************************
 * Pin configuration
 ******************************************************************************/
अटल अचिन्हित दीर्घ palmld_pin_config[] __initdata = अणु
	/* MMC */
	GPIO32_MMC_CLK,
	GPIO92_MMC_DAT_0,
	GPIO109_MMC_DAT_1,
	GPIO110_MMC_DAT_2,
	GPIO111_MMC_DAT_3,
	GPIO112_MMC_CMD,
	GPIO14_GPIO,	/* SD detect */
	GPIO114_GPIO,	/* SD घातer */
	GPIO116_GPIO,	/* SD r/o चयन */

	/* AC97 */
	GPIO28_AC97_BITCLK,
	GPIO29_AC97_SDATA_IN_0,
	GPIO30_AC97_SDATA_OUT,
	GPIO31_AC97_SYNC,
	GPIO89_AC97_SYSCLK,
	GPIO95_AC97_nRESET,

	/* IrDA */
	GPIO108_GPIO,	/* ir disable */
	GPIO46_FICP_RXD,
	GPIO47_FICP_TXD,

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

	/* GPIO KEYS */
	GPIO10_GPIO,	/* hotsync button */
	GPIO12_GPIO,	/* घातer चयन */
	GPIO15_GPIO,	/* lock चयन */

	/* LEDs */
	GPIO52_GPIO,	/* green led */
	GPIO94_GPIO,	/* orange led */

	/* PCMCIA */
	GPIO48_nPOE,
	GPIO49_nPWE,
	GPIO50_nPIOR,
	GPIO51_nPIOW,
	GPIO85_nPCE_1,
	GPIO54_nPCE_2,
	GPIO79_PSKTSEL,
	GPIO55_nPREG,
	GPIO56_nPWAIT,
	GPIO57_nIOIS16,
	GPIO36_GPIO,	/* wअगरi घातer */
	GPIO38_GPIO,	/* wअगरi पढ़ोy */
	GPIO81_GPIO,	/* wअगरi reset */

	/* FFUART */
	GPIO34_FFUART_RXD,
	GPIO39_FFUART_TXD,

	/* HDD */
	GPIO98_GPIO,	/* HDD reset */
	GPIO115_GPIO,	/* HDD घातer */

	/* MISC */
	GPIO13_GPIO,	/* earphone detect */
पूर्ण;

/******************************************************************************
 * NOR Flash
 ******************************************************************************/
#अगर defined(CONFIG_MTD_PHYSMAP) || defined(CONFIG_MTD_PHYSMAP_MODULE)
अटल काष्ठा mtd_partition palmld_partitions[] = अणु
	अणु
		.name		= "Flash",
		.offset		= 0x00000000,
		.size		= MTDPART_SIZ_FULL,
		.mask_flags	= 0
	पूर्ण
पूर्ण;

अटल काष्ठा physmap_flash_data palmld_flash_data[] = अणु
	अणु
		.width		= 2,			/* bankwidth in bytes */
		.parts		= palmld_partitions,
		.nr_parts	= ARRAY_SIZE(palmld_partitions)
	पूर्ण
पूर्ण;

अटल काष्ठा resource palmld_flash_resource = अणु
	.start	= PXA_CS0_PHYS,
	.end	= PXA_CS0_PHYS + SZ_4M - 1,
	.flags	= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा platक्रमm_device palmld_flash = अणु
	.name		= "physmap-flash",
	.id		= 0,
	.resource	= &palmld_flash_resource,
	.num_resources	= 1,
	.dev 		= अणु
		.platक्रमm_data = palmld_flash_data,
	पूर्ण,
पूर्ण;

अटल व्योम __init palmld_nor_init(व्योम)
अणु
	platक्रमm_device_रेजिस्टर(&palmld_flash);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम palmld_nor_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * GPIO keyboard
 ******************************************************************************/
#अगर defined(CONFIG_KEYBOARD_PXA27x) || defined(CONFIG_KEYBOARD_PXA27x_MODULE)
अटल स्थिर अचिन्हित पूर्णांक palmld_matrix_keys[] = अणु
	KEY(0, 1, KEY_F2),
	KEY(0, 2, KEY_UP),

	KEY(1, 0, KEY_F3),
	KEY(1, 1, KEY_F4),
	KEY(1, 2, KEY_RIGHT),

	KEY(2, 0, KEY_F1),
	KEY(2, 1, KEY_F5),
	KEY(2, 2, KEY_DOWN),

	KEY(3, 0, KEY_F6),
	KEY(3, 1, KEY_ENTER),
	KEY(3, 2, KEY_LEFT),
पूर्ण;

अटल काष्ठा matrix_keymap_data palmld_matrix_keymap_data = अणु
	.keymap			= palmld_matrix_keys,
	.keymap_size		= ARRAY_SIZE(palmld_matrix_keys),
पूर्ण;

अटल काष्ठा pxa27x_keypad_platक्रमm_data palmld_keypad_platक्रमm_data = अणु
	.matrix_key_rows	= 4,
	.matrix_key_cols	= 3,
	.matrix_keymap_data	= &palmld_matrix_keymap_data,

	.debounce_पूर्णांकerval	= 30,
पूर्ण;

अटल व्योम __init palmld_kpc_init(व्योम)
अणु
	pxa_set_keypad_info(&palmld_keypad_platक्रमm_data);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम palmld_kpc_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * GPIO keys
 ******************************************************************************/
#अगर defined(CONFIG_KEYBOARD_GPIO) || defined(CONFIG_KEYBOARD_GPIO_MODULE)
अटल काष्ठा gpio_keys_button palmld_pxa_buttons[] = अणु
	अणुKEY_F8, GPIO_NR_PALMLD_HOTSYNC_BUTTON_N, 1, "HotSync Button" पूर्ण,
	अणुKEY_F9, GPIO_NR_PALMLD_LOCK_SWITCH, 0, "Lock Switch" पूर्ण,
	अणुKEY_POWER, GPIO_NR_PALMLD_POWER_SWITCH, 0, "Power Switch" पूर्ण,
पूर्ण;

अटल काष्ठा gpio_keys_platक्रमm_data palmld_pxa_keys_data = अणु
	.buttons	= palmld_pxa_buttons,
	.nbuttons	= ARRAY_SIZE(palmld_pxa_buttons),
पूर्ण;

अटल काष्ठा platक्रमm_device palmld_pxa_keys = अणु
	.name	= "gpio-keys",
	.id	= -1,
	.dev	= अणु
		.platक्रमm_data = &palmld_pxa_keys_data,
	पूर्ण,
पूर्ण;

अटल व्योम __init palmld_keys_init(व्योम)
अणु
	platक्रमm_device_रेजिस्टर(&palmld_pxa_keys);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम palmld_keys_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * LEDs
 ******************************************************************************/
#अगर defined(CONFIG_LEDS_GPIO) || defined(CONFIG_LEDS_GPIO_MODULE)
काष्ठा gpio_led gpio_leds[] = अणु
अणु
	.name			= "palmld:green:led",
	.शेष_trigger	= "none",
	.gpio			= GPIO_NR_PALMLD_LED_GREEN,
पूर्ण, अणु
	.name			= "palmld:amber:led",
	.शेष_trigger	= "none",
	.gpio			= GPIO_NR_PALMLD_LED_AMBER,
पूर्ण,
पूर्ण;

अटल काष्ठा gpio_led_platक्रमm_data gpio_led_info = अणु
	.leds		= gpio_leds,
	.num_leds	= ARRAY_SIZE(gpio_leds),
पूर्ण;

अटल काष्ठा platक्रमm_device palmld_leds = अणु
	.name	= "leds-gpio",
	.id	= -1,
	.dev	= अणु
		.platक्रमm_data	= &gpio_led_info,
	पूर्ण
पूर्ण;

अटल व्योम __init palmld_leds_init(व्योम)
अणु
	platक्रमm_device_रेजिस्टर(&palmld_leds);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम palmld_leds_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * HDD
 ******************************************************************************/
#अगर defined(CONFIG_PATA_PALMLD) || defined(CONFIG_PATA_PALMLD_MODULE)
अटल काष्ठा platक्रमm_device palmld_ide_device = अणु
	.name	= "pata_palmld",
	.id	= -1,
पूर्ण;

अटल काष्ठा gpiod_lookup_table palmld_ide_gpio_table = अणु
	.dev_id = "pata_palmld",
	.table = अणु
		GPIO_LOOKUP("gpio-pxa", GPIO_NR_PALMLD_IDE_PWEN,
			    "power", GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP("gpio-pxa", GPIO_NR_PALMLD_IDE_RESET,
			    "reset", GPIO_ACTIVE_LOW),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल व्योम __init palmld_ide_init(व्योम)
अणु
	gpiod_add_lookup_table(&palmld_ide_gpio_table);
	platक्रमm_device_रेजिस्टर(&palmld_ide_device);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम palmld_ide_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * Machine init
 ******************************************************************************/
अटल काष्ठा map_desc palmld_io_desc[] __initdata = अणु
अणु
	.भव	= PALMLD_IDE_VIRT,
	.pfn		= __phys_to_pfn(PALMLD_IDE_PHYS),
	.length		= PALMLD_IDE_SIZE,
	.type		= MT_DEVICE
पूर्ण,
अणु
	.भव	= PALMLD_USB_VIRT,
	.pfn		= __phys_to_pfn(PALMLD_USB_PHYS),
	.length		= PALMLD_USB_SIZE,
	.type		= MT_DEVICE
पूर्ण,
पूर्ण;

अटल व्योम __init palmld_map_io(व्योम)
अणु
	pxa27x_map_io();
	iotable_init(palmld_io_desc, ARRAY_SIZE(palmld_io_desc));
पूर्ण

अटल काष्ठा gpiod_lookup_table palmld_mci_gpio_table = अणु
	.dev_id = "pxa2xx-mci.0",
	.table = अणु
		GPIO_LOOKUP("gpio-pxa", GPIO_NR_PALMLD_SD_DETECT_N,
			    "cd", GPIO_ACTIVE_LOW),
		GPIO_LOOKUP("gpio-pxa", GPIO_NR_PALMLD_SD_READONLY,
			    "wp", GPIO_ACTIVE_LOW),
		GPIO_LOOKUP("gpio-pxa", GPIO_NR_PALMLD_SD_POWER,
			    "power", GPIO_ACTIVE_HIGH),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल व्योम __init palmld_init(व्योम)
अणु
	pxa2xx_mfp_config(ARRAY_AND_SIZE(palmld_pin_config));
	pxa_set_ffuart_info(शून्य);
	pxa_set_btuart_info(शून्य);
	pxa_set_stuart_info(शून्य);

	palm27x_mmc_init(&palmld_mci_gpio_table);
	palm27x_pm_init(PALMLD_STR_BASE);
	palm27x_lcd_init(-1, &palm_320x480_lcd_mode);
	palm27x_irda_init(GPIO_NR_PALMLD_IR_DISABLE);
	palm27x_ac97_init(PALMLD_BAT_MIN_VOLTAGE, PALMLD_BAT_MAX_VOLTAGE,
			GPIO_NR_PALMLD_EARPHONE_DETECT, 95);
	palm27x_pwm_init(GPIO_NR_PALMLD_BL_POWER, GPIO_NR_PALMLD_LCD_POWER);
	palm27x_घातer_init(GPIO_NR_PALMLD_POWER_DETECT,
			GPIO_NR_PALMLD_USB_DETECT_N);
	palm27x_pmic_init();
	palmld_kpc_init();
	palmld_keys_init();
	palmld_nor_init();
	palmld_leds_init();
	palmld_ide_init();
पूर्ण

MACHINE_START(PALMLD, "Palm LifeDrive")
	.atag_offset	= 0x100,
	.map_io		= palmld_map_io,
	.nr_irqs	= PXA_NR_IRQS,
	.init_irq	= pxa27x_init_irq,
	.handle_irq	= pxa27x_handle_irq,
	.init_समय	= pxa_समयr_init,
	.init_machine	= palmld_init,
	.restart	= pxa_restart,
MACHINE_END
