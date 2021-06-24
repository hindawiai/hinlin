<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Hardware definitions क्रम PalmTX
 *
 * Author:     Marek Vasut <marek.vasut@gmail.com>
 *
 * Based on work of:
 *		Alex Osborne <ato@meshy.org>
 *		Cristiano P. <cristianop@users.sourceक्रमge.net>
 *		Jan Herman <2hp@seznam.cz>
 *		Michal Hrusecky
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
#समावेश <linux/mtd/platnand.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/physmap.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>

#समावेश "pxa27x.h"
#समावेश <mach/audपन.स>
#समावेश <mach/palmtx.h>
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
अटल अचिन्हित दीर्घ palmtx_pin_config[] __initdata = अणु
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

	/* PWM */
	GPIO16_PWM0_OUT,

	/* USB */
	GPIO13_GPIO,	/* usb detect */
	GPIO93_GPIO,	/* usb घातer */

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
	GPIO94_GPIO,	/* wअगरi घातer 1 */
	GPIO108_GPIO,	/* wअगरi घातer 2 */
	GPIO116_GPIO,	/* wअगरi पढ़ोy */

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

	/* FFUART */
	GPIO34_FFUART_RXD,
	GPIO39_FFUART_TXD,

	/* न_अंकD */
	GPIO15_nCS_1,
	GPIO18_RDY,

	/* MISC. */
	GPIO10_GPIO,	/* hotsync button */
	GPIO12_GPIO,	/* घातer detect */
	GPIO107_GPIO,	/* earphone detect */
पूर्ण;

/******************************************************************************
 * NOR Flash
 ******************************************************************************/
#अगर defined(CONFIG_MTD_PHYSMAP) || defined(CONFIG_MTD_PHYSMAP_MODULE)
अटल काष्ठा mtd_partition palmtx_partitions[] = अणु
	अणु
		.name		= "Flash",
		.offset		= 0x00000000,
		.size		= MTDPART_SIZ_FULL,
		.mask_flags	= 0
	पूर्ण
पूर्ण;

अटल काष्ठा physmap_flash_data palmtx_flash_data[] = अणु
	अणु
		.width		= 2,			/* bankwidth in bytes */
		.parts		= palmtx_partitions,
		.nr_parts	= ARRAY_SIZE(palmtx_partitions)
	पूर्ण
पूर्ण;

अटल काष्ठा resource palmtx_flash_resource = अणु
	.start	= PXA_CS0_PHYS,
	.end	= PXA_CS0_PHYS + SZ_8M - 1,
	.flags	= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा platक्रमm_device palmtx_flash = अणु
	.name		= "physmap-flash",
	.id		= 0,
	.resource	= &palmtx_flash_resource,
	.num_resources	= 1,
	.dev 		= अणु
		.platक्रमm_data = palmtx_flash_data,
	पूर्ण,
पूर्ण;

अटल व्योम __init palmtx_nor_init(व्योम)
अणु
	platक्रमm_device_रेजिस्टर(&palmtx_flash);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम palmtx_nor_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * GPIO keyboard
 ******************************************************************************/
#अगर defined(CONFIG_KEYBOARD_PXA27x) || defined(CONFIG_KEYBOARD_PXA27x_MODULE)
अटल स्थिर अचिन्हित पूर्णांक palmtx_matrix_keys[] = अणु
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

अटल काष्ठा matrix_keymap_data palmtx_matrix_keymap_data = अणु
	.keymap			= palmtx_matrix_keys,
	.keymap_size		= ARRAY_SIZE(palmtx_matrix_keys),
पूर्ण;

अटल काष्ठा pxa27x_keypad_platक्रमm_data palmtx_keypad_platक्रमm_data = अणु
	.matrix_key_rows	= 4,
	.matrix_key_cols	= 3,
	.matrix_keymap_data	= &palmtx_matrix_keymap_data,

	.debounce_पूर्णांकerval	= 30,
पूर्ण;

अटल व्योम __init palmtx_kpc_init(व्योम)
अणु
	pxa_set_keypad_info(&palmtx_keypad_platक्रमm_data);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम palmtx_kpc_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * GPIO keys
 ******************************************************************************/
#अगर defined(CONFIG_KEYBOARD_GPIO) || defined(CONFIG_KEYBOARD_GPIO_MODULE)
अटल काष्ठा gpio_keys_button palmtx_pxa_buttons[] = अणु
	अणुKEY_F8, GPIO_NR_PALMTX_HOTSYNC_BUTTON_N, 1, "HotSync Button" पूर्ण,
पूर्ण;

अटल काष्ठा gpio_keys_platक्रमm_data palmtx_pxa_keys_data = अणु
	.buttons	= palmtx_pxa_buttons,
	.nbuttons	= ARRAY_SIZE(palmtx_pxa_buttons),
पूर्ण;

अटल काष्ठा platक्रमm_device palmtx_pxa_keys = अणु
	.name	= "gpio-keys",
	.id	= -1,
	.dev	= अणु
		.platक्रमm_data = &palmtx_pxa_keys_data,
	पूर्ण,
पूर्ण;

अटल व्योम __init palmtx_keys_init(व्योम)
अणु
	platक्रमm_device_रेजिस्टर(&palmtx_pxa_keys);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम palmtx_keys_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * न_अंकD Flash
 ******************************************************************************/
#अगर defined(CONFIG_MTD_न_अंकD_PLATFORM) || \
	defined(CONFIG_MTD_न_अंकD_PLATFORM_MODULE)
अटल व्योम palmtx_nand_cmd_ctl(काष्ठा nand_chip *this, पूर्णांक cmd,
				अचिन्हित पूर्णांक ctrl)
अणु
	अक्षर __iomem *nandaddr = this->legacy.IO_ADDR_W;

	अगर (cmd == न_अंकD_CMD_NONE)
		वापस;

	अगर (ctrl & न_अंकD_CLE)
		ग_लिखोb(cmd, PALMTX_न_अंकD_CLE_VIRT);
	अन्यथा अगर (ctrl & न_अंकD_ALE)
		ग_लिखोb(cmd, PALMTX_न_अंकD_ALE_VIRT);
	अन्यथा
		ग_लिखोb(cmd, nandaddr);
पूर्ण

अटल काष्ठा mtd_partition palmtx_partition_info[] = अणु
	[0] = अणु
		.name	= "palmtx-0",
		.offset	= 0,
		.size	= MTDPART_SIZ_FULL
	पूर्ण,
पूर्ण;

काष्ठा platक्रमm_nand_data palmtx_nand_platdata = अणु
	.chip	= अणु
		.nr_chips		= 1,
		.chip_offset		= 0,
		.nr_partitions		= ARRAY_SIZE(palmtx_partition_info),
		.partitions		= palmtx_partition_info,
		.chip_delay		= 20,
	पूर्ण,
	.ctrl	= अणु
		.cmd_ctrl	= palmtx_nand_cmd_ctl,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource palmtx_nand_resource[] = अणु
	[0]	= अणु
		.start	= PXA_CS1_PHYS,
		.end	= PXA_CS1_PHYS + SZ_1M - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device palmtx_nand = अणु
	.name		= "gen_nand",
	.num_resources	= ARRAY_SIZE(palmtx_nand_resource),
	.resource	= palmtx_nand_resource,
	.id		= -1,
	.dev		= अणु
		.platक्रमm_data	= &palmtx_nand_platdata,
	पूर्ण
पूर्ण;

अटल व्योम __init palmtx_nand_init(व्योम)
अणु
	platक्रमm_device_रेजिस्टर(&palmtx_nand);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम palmtx_nand_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * Machine init
 ******************************************************************************/
अटल काष्ठा map_desc palmtx_io_desc[] __initdata = अणु
अणु
	.भव	= (अचिन्हित दीर्घ)PALMTX_PCMCIA_VIRT,
	.pfn		= __phys_to_pfn(PALMTX_PCMCIA_PHYS),
	.length		= PALMTX_PCMCIA_SIZE,
	.type		= MT_DEVICE,
पूर्ण, अणु
	.भव	= (अचिन्हित दीर्घ)PALMTX_न_अंकD_ALE_VIRT,
	.pfn		= __phys_to_pfn(PALMTX_न_अंकD_ALE_PHYS),
	.length		= SZ_1M,
	.type		= MT_DEVICE,
पूर्ण, अणु
	.भव	= (अचिन्हित दीर्घ)PALMTX_न_अंकD_CLE_VIRT,
	.pfn		= __phys_to_pfn(PALMTX_न_अंकD_CLE_PHYS),
	.length		= SZ_1M,
	.type		= MT_DEVICE,
पूर्ण
पूर्ण;

अटल व्योम __init palmtx_map_io(व्योम)
अणु
	pxa27x_map_io();
	iotable_init(palmtx_io_desc, ARRAY_SIZE(palmtx_io_desc));
पूर्ण

अटल काष्ठा gpiod_lookup_table palmtx_mci_gpio_table = अणु
	.dev_id = "pxa2xx-mci.0",
	.table = अणु
		GPIO_LOOKUP("gpio-pxa", GPIO_NR_PALMTX_SD_DETECT_N,
			    "cd", GPIO_ACTIVE_LOW),
		GPIO_LOOKUP("gpio-pxa", GPIO_NR_PALMTX_SD_READONLY,
			    "wp", GPIO_ACTIVE_LOW),
		GPIO_LOOKUP("gpio-pxa", GPIO_NR_PALMTX_SD_POWER,
			    "power", GPIO_ACTIVE_HIGH),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल व्योम __init palmtx_init(व्योम)
अणु
	pxa2xx_mfp_config(ARRAY_AND_SIZE(palmtx_pin_config));
	pxa_set_ffuart_info(शून्य);
	pxa_set_btuart_info(शून्य);
	pxa_set_stuart_info(शून्य);

	palm27x_mmc_init(&palmtx_mci_gpio_table);
	palm27x_pm_init(PALMTX_STR_BASE);
	palm27x_lcd_init(-1, &palm_320x480_lcd_mode);
	palm27x_udc_init(GPIO_NR_PALMTX_USB_DETECT_N,
			GPIO_NR_PALMTX_USB_PULLUP, 1);
	palm27x_irda_init(GPIO_NR_PALMTX_IR_DISABLE);
	palm27x_ac97_init(PALMTX_BAT_MIN_VOLTAGE, PALMTX_BAT_MAX_VOLTAGE,
			GPIO_NR_PALMTX_EARPHONE_DETECT, 95);
	palm27x_pwm_init(GPIO_NR_PALMTX_BL_POWER, GPIO_NR_PALMTX_LCD_POWER);
	palm27x_घातer_init(GPIO_NR_PALMTX_POWER_DETECT, -1);
	palm27x_pmic_init();
	palmtx_kpc_init();
	palmtx_keys_init();
	palmtx_nor_init();
	palmtx_nand_init();
पूर्ण

MACHINE_START(PALMTX, "Palm T|X")
	.atag_offset	= 0x100,
	.map_io		= palmtx_map_io,
	.nr_irqs	= PXA_NR_IRQS,
	.init_irq	= pxa27x_init_irq,
	.handle_irq	= pxa27x_handle_irq,
	.init_समय	= pxa_समयr_init,
	.init_machine	= palmtx_init,
	.restart	= pxa_restart,
MACHINE_END
