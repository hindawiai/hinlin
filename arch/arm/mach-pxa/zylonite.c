<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/arch/arm/mach-pxa/zylonite.c
 *
 * Support क्रम the PXA3xx Development Platक्रमm (aka Zylonite)
 *
 * Copyright (C) 2006 Marvell International Ltd.
 *
 * 2007-09-04: eric miao <eric.miao@marvell.com>
 *             reग_लिखो to align with latest kernel
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/leds.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/pwm.h>
#समावेश <linux/pwm_backlight.h>
#समावेश <linux/smc91x.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश "pxa3xx.h"
#समावेश <mach/audपन.स>
#समावेश <linux/platक्रमm_data/video-pxafb.h>
#समावेश "zylonite.h"
#समावेश <linux/platक्रमm_data/mmc-pxamci.h>
#समावेश <linux/platक्रमm_data/usb-ohci-pxa27x.h>
#समावेश <linux/platक्रमm_data/keypad-pxa27x.h>
#समावेश <linux/platक्रमm_data/mtd-nand-pxa3xx.h>

#समावेश "devices.h"
#समावेश "generic.h"

पूर्णांक gpio_eth_irq;
पूर्णांक gpio_debug_led1;
पूर्णांक gpio_debug_led2;

पूर्णांक wm9713_irq;

पूर्णांक lcd_id;
पूर्णांक lcd_orientation;

अटल काष्ठा resource smc91x_resources[] = अणु
	[0] = अणु
		.start	= ZYLONITE_ETH_PHYS + 0x300,
		.end	= ZYLONITE_ETH_PHYS + 0xfffff,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= -1,	/* क्रम run-समय assignment */
		.end	= -1,
		.flags	= IORESOURCE_IRQ | IORESOURCE_IRQ_HIGHEDGE,
	पूर्ण
पूर्ण;

अटल काष्ठा smc91x_platdata zylonite_smc91x_info = अणु
	.flags	= SMC91X_USE_8BIT | SMC91X_USE_16BIT |
		  SMC91X_NOWAIT | SMC91X_USE_DMA,
पूर्ण;

अटल काष्ठा platक्रमm_device smc91x_device = अणु
	.name		= "smc91x",
	.id		= 0,
	.num_resources	= ARRAY_SIZE(smc91x_resources),
	.resource	= smc91x_resources,
	.dev		= अणु
		.platक्रमm_data = &zylonite_smc91x_info,
	पूर्ण,
पूर्ण;

#अगर defined(CONFIG_LEDS_GPIO) || defined(CONFIG_LEDS_GPIO_MODULE)
अटल काष्ठा gpio_led zylonite_debug_leds[] = अणु
	[0] = अणु
		.name			= "zylonite:yellow:1",
		.शेष_trigger	= "heartbeat",
	पूर्ण,
	[1] = अणु
		.name			= "zylonite:yellow:2",
		.शेष_trigger	= "default-on",
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_led_platक्रमm_data zylonite_debug_leds_info = अणु
	.leds		= zylonite_debug_leds,
	.num_leds	= ARRAY_SIZE(zylonite_debug_leds),
पूर्ण;

अटल काष्ठा platक्रमm_device zylonite_device_leds = अणु
	.name		= "leds-gpio",
	.id		= -1,
	.dev		= अणु
		.platक्रमm_data = &zylonite_debug_leds_info,
	पूर्ण
पूर्ण;

अटल व्योम __init zylonite_init_leds(व्योम)
अणु
	zylonite_debug_leds[0].gpio = gpio_debug_led1;
	zylonite_debug_leds[1].gpio = gpio_debug_led2;

	platक्रमm_device_रेजिस्टर(&zylonite_device_leds);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम zylonite_init_leds(व्योम) अणुपूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_FB_PXA) || defined(CONFIG_FB_PXA_MODULE)
अटल काष्ठा pwm_lookup zylonite_pwm_lookup[] = अणु
	PWM_LOOKUP("pxa27x-pwm.1", 1, "pwm-backlight.0", शून्य, 10000,
		   PWM_POLARITY_NORMAL),
पूर्ण;

अटल काष्ठा platक्रमm_pwm_backlight_data zylonite_backlight_data = अणु
	.max_brightness	= 100,
	.dft_brightness	= 100,
पूर्ण;

अटल काष्ठा platक्रमm_device zylonite_backlight_device = अणु
	.name		= "pwm-backlight",
	.dev		= अणु
		.parent = &pxa27x_device_pwm1.dev,
		.platक्रमm_data	= &zylonite_backlight_data,
	पूर्ण,
पूर्ण;

अटल काष्ठा pxafb_mode_info toshiba_lपंचांग035a776c_mode = अणु
	.pixघड़ी		= 110000,
	.xres			= 240,
	.yres			= 320,
	.bpp			= 16,
	.hsync_len		= 4,
	.left_margin		= 6,
	.right_margin		= 4,
	.vsync_len		= 2,
	.upper_margin		= 2,
	.lower_margin		= 3,
	.sync			= FB_SYNC_VERT_HIGH_ACT,
पूर्ण;

अटल काष्ठा pxafb_mode_info toshiba_lपंचांग04c380k_mode = अणु
	.pixघड़ी		= 50000,
	.xres			= 640,
	.yres			= 480,
	.bpp			= 16,
	.hsync_len		= 1,
	.left_margin		= 0x9f,
	.right_margin		= 1,
	.vsync_len		= 44,
	.upper_margin		= 0,
	.lower_margin		= 0,
	.sync			= FB_SYNC_HOR_HIGH_ACT|FB_SYNC_VERT_HIGH_ACT,
पूर्ण;

अटल काष्ठा pxafb_mach_info zylonite_toshiba_lcd_info = अणु
	.num_modes      	= 1,
	.lcd_conn		= LCD_COLOR_TFT_16BPP | LCD_PCLK_EDGE_FALL,
पूर्ण;

अटल काष्ठा pxafb_mode_info sharp_ls037_modes[] = अणु
	[0] = अणु
		.pixघड़ी	= 158000,
		.xres		= 240,
		.yres		= 320,
		.bpp		= 16,
		.hsync_len	= 4,
		.left_margin	= 39,
		.right_margin	= 39,
		.vsync_len	= 1,
		.upper_margin	= 2,
		.lower_margin	= 3,
		.sync		= 0,
	पूर्ण,
	[1] = अणु
		.pixघड़ी	= 39700,
		.xres		= 480,
		.yres		= 640,
		.bpp		= 16,
		.hsync_len	= 8,
		.left_margin	= 81,
		.right_margin	= 81,
		.vsync_len	= 1,
		.upper_margin	= 2,
		.lower_margin	= 7,
		.sync		= 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा pxafb_mach_info zylonite_sharp_lcd_info = अणु
	.modes			= sharp_ls037_modes,
	.num_modes		= 2,
	.lcd_conn		= LCD_COLOR_TFT_16BPP | LCD_PCLK_EDGE_FALL,
पूर्ण;

अटल व्योम __init zylonite_init_lcd(व्योम)
अणु
	pwm_add_table(zylonite_pwm_lookup, ARRAY_SIZE(zylonite_pwm_lookup));
	platक्रमm_device_रेजिस्टर(&zylonite_backlight_device);

	अगर (lcd_id & 0x20) अणु
		pxa_set_fb_info(शून्य, &zylonite_sharp_lcd_info);
		वापस;
	पूर्ण

	/* legacy LCD panels, it would be handy here अगर LCD panel type can
	 * be decided at run-समय
	 */
	अगर (1)
		zylonite_toshiba_lcd_info.modes = &toshiba_lपंचांग035a776c_mode;
	अन्यथा
		zylonite_toshiba_lcd_info.modes = &toshiba_lपंचांग04c380k_mode;

	pxa_set_fb_info(शून्य, &zylonite_toshiba_lcd_info);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम zylonite_init_lcd(व्योम) अणुपूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_MMC)
अटल काष्ठा pxamci_platक्रमm_data zylonite_mci_platक्रमm_data = अणु
	.detect_delay_ms= 200,
	.ocr_mask	= MMC_VDD_32_33|MMC_VDD_33_34,
पूर्ण;

#घोषणा PCA9539A_MCI_CD 0
#घोषणा PCA9539A_MCI1_CD 1
#घोषणा PCA9539A_MCI_WP 2
#घोषणा PCA9539A_MCI1_WP 3
#घोषणा PCA9539A_MCI3_CD 30
#घोषणा PCA9539A_MCI3_WP 31

अटल काष्ठा gpiod_lookup_table zylonite_mci_gpio_table = अणु
	.dev_id = "pxa2xx-mci.0",
	.table = अणु
		GPIO_LOOKUP("i2c-pca9539-a", PCA9539A_MCI_CD,
			    "cd", GPIO_ACTIVE_LOW),
		GPIO_LOOKUP("i2c-pca9539-a", PCA9539A_MCI_WP,
			    "wp", GPIO_ACTIVE_LOW),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा pxamci_platक्रमm_data zylonite_mci2_platक्रमm_data = अणु
	.detect_delay_ms= 200,
	.ocr_mask	= MMC_VDD_32_33|MMC_VDD_33_34,
पूर्ण;

अटल काष्ठा gpiod_lookup_table zylonite_mci2_gpio_table = अणु
	.dev_id = "pxa2xx-mci.1",
	.table = अणु
		GPIO_LOOKUP("i2c-pca9539-a", PCA9539A_MCI1_CD,
			    "cd", GPIO_ACTIVE_LOW),
		GPIO_LOOKUP("i2c-pca9539-a", PCA9539A_MCI1_WP,
			    "wp", GPIO_ACTIVE_LOW),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा pxamci_platक्रमm_data zylonite_mci3_platक्रमm_data = अणु
	.detect_delay_ms= 200,
	.ocr_mask	= MMC_VDD_32_33|MMC_VDD_33_34,
पूर्ण;

अटल काष्ठा gpiod_lookup_table zylonite_mci3_gpio_table = अणु
	.dev_id = "pxa2xx-mci.2",
	.table = अणु
		GPIO_LOOKUP("i2c-pca9539-a", PCA9539A_MCI3_CD,
			    "cd", GPIO_ACTIVE_LOW),
		GPIO_LOOKUP("i2c-pca9539-a", PCA9539A_MCI3_WP,
			    "wp", GPIO_ACTIVE_LOW),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल व्योम __init zylonite_init_mmc(व्योम)
अणु
	gpiod_add_lookup_table(&zylonite_mci_gpio_table);
	pxa_set_mci_info(&zylonite_mci_platक्रमm_data);
	gpiod_add_lookup_table(&zylonite_mci2_gpio_table);
	pxa3xx_set_mci2_info(&zylonite_mci2_platक्रमm_data);
	अगर (cpu_is_pxa310()) अणु
		gpiod_add_lookup_table(&zylonite_mci3_gpio_table);
		pxa3xx_set_mci3_info(&zylonite_mci3_platक्रमm_data);
	पूर्ण
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम zylonite_init_mmc(व्योम) अणुपूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_KEYBOARD_PXA27x) || defined(CONFIG_KEYBOARD_PXA27x_MODULE)
अटल स्थिर अचिन्हित पूर्णांक zylonite_matrix_key_map[] = अणु
	/* KEY(row, col, key_code) */
	KEY(0, 0, KEY_A), KEY(0, 1, KEY_B), KEY(0, 2, KEY_C), KEY(0, 5, KEY_D),
	KEY(1, 0, KEY_E), KEY(1, 1, KEY_F), KEY(1, 2, KEY_G), KEY(1, 5, KEY_H),
	KEY(2, 0, KEY_I), KEY(2, 1, KEY_J), KEY(2, 2, KEY_K), KEY(2, 5, KEY_L),
	KEY(3, 0, KEY_M), KEY(3, 1, KEY_N), KEY(3, 2, KEY_O), KEY(3, 5, KEY_P),
	KEY(5, 0, KEY_Q), KEY(5, 1, KEY_R), KEY(5, 2, KEY_S), KEY(5, 5, KEY_T),
	KEY(6, 0, KEY_U), KEY(6, 1, KEY_V), KEY(6, 2, KEY_W), KEY(6, 5, KEY_X),
	KEY(7, 1, KEY_Y), KEY(7, 2, KEY_Z),

	KEY(4, 4, KEY_0), KEY(1, 3, KEY_1), KEY(4, 1, KEY_2), KEY(1, 4, KEY_3),
	KEY(2, 3, KEY_4), KEY(4, 2, KEY_5), KEY(2, 4, KEY_6), KEY(3, 3, KEY_7),
	KEY(4, 3, KEY_8), KEY(3, 4, KEY_9),

	KEY(4, 5, KEY_SPACE),
	KEY(5, 3, KEY_KPASTERISK), 	/* * */
	KEY(5, 4, KEY_KPDOT), 		/* #" */

	KEY(0, 7, KEY_UP),
	KEY(1, 7, KEY_DOWN),
	KEY(2, 7, KEY_LEFT),
	KEY(3, 7, KEY_RIGHT),
	KEY(2, 6, KEY_HOME),
	KEY(3, 6, KEY_END),
	KEY(6, 4, KEY_DELETE),
	KEY(6, 6, KEY_BACK),
	KEY(6, 3, KEY_CAPSLOCK),	/* KEY_LEFTSHIFT), */

	KEY(4, 6, KEY_ENTER),		/* scroll push */
	KEY(5, 7, KEY_ENTER),		/* keypad action */

	KEY(0, 4, KEY_EMAIL),
	KEY(5, 6, KEY_SEND),
	KEY(4, 0, KEY_CALENDAR),
	KEY(7, 6, KEY_RECORD),
	KEY(6, 7, KEY_VOLUMEUP),
	KEY(7, 7, KEY_VOLUMEDOWN),

	KEY(0, 6, KEY_F22),	/* soft1 */
	KEY(1, 6, KEY_F23),	/* soft2 */
	KEY(0, 3, KEY_AUX),	/* contact */
पूर्ण;

अटल काष्ठा matrix_keymap_data zylonite_matrix_keymap_data = अणु
	.keymap			= zylonite_matrix_key_map,
	.keymap_size		= ARRAY_SIZE(zylonite_matrix_key_map),
पूर्ण;

अटल काष्ठा pxa27x_keypad_platक्रमm_data zylonite_keypad_info = अणु
	.matrix_key_rows	= 8,
	.matrix_key_cols	= 8,
	.matrix_keymap_data	= &zylonite_matrix_keymap_data,

	.enable_rotary0		= 1,
	.rotary0_up_key		= KEY_UP,
	.rotary0_करोwn_key	= KEY_DOWN,

	.debounce_पूर्णांकerval	= 30,
पूर्ण;

अटल व्योम __init zylonite_init_keypad(व्योम)
अणु
	pxa_set_keypad_info(&zylonite_keypad_info);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम zylonite_init_keypad(व्योम) अणुपूर्ण
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_MTD_न_अंकD_MARVELL)
अटल काष्ठा mtd_partition zylonite_nand_partitions[] = अणु
	[0] = अणु
		.name        = "Bootloader",
		.offset      = 0,
		.size        = 0x060000,
		.mask_flags  = MTD_WRITEABLE, /* क्रमce पढ़ो-only */
	पूर्ण,
	[1] = अणु
		.name        = "Kernel",
		.offset      = 0x060000,
		.size        = 0x200000,
		.mask_flags  = MTD_WRITEABLE, /* क्रमce पढ़ो-only */
	पूर्ण,
	[2] = अणु
		.name        = "Filesystem",
		.offset      = 0x0260000,
		.size        = 0x3000000,     /* 48M - rootfs */
	पूर्ण,
	[3] = अणु
		.name        = "MassStorage",
		.offset      = 0x3260000,
		.size        = 0x3d40000,
	पूर्ण,
	[4] = अणु
		.name        = "BBT",
		.offset      = 0x6FA0000,
		.size        = 0x80000,
		.mask_flags  = MTD_WRITEABLE,  /* क्रमce पढ़ो-only */
	पूर्ण,
	/* NOTE: we reserve some blocks at the end of the न_अंकD flash क्रम
	 * bad block management, and the max number of relocation blocks
	 * dअगरfers on dअगरferent platक्रमms. Please take care with it when
	 * defining the partition table.
	 */
पूर्ण;

अटल काष्ठा pxa3xx_nand_platक्रमm_data zylonite_nand_info = अणु
	.parts		= zylonite_nand_partitions,
	.nr_parts	= ARRAY_SIZE(zylonite_nand_partitions),
पूर्ण;

अटल व्योम __init zylonite_init_nand(व्योम)
अणु
	pxa3xx_set_nand_info(&zylonite_nand_info);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम zylonite_init_nand(व्योम) अणुपूर्ण
#पूर्ण_अगर /* IS_ENABLED(CONFIG_MTD_न_अंकD_MARVELL) */

#अगर defined(CONFIG_USB_OHCI_HCD) || defined(CONFIG_USB_OHCI_HCD_MODULE)
अटल काष्ठा pxaohci_platक्रमm_data zylonite_ohci_info = अणु
	.port_mode	= PMM_PERPORT_MODE,
	.flags		= ENABLE_PORT1 | ENABLE_PORT2 |
			  POWER_CONTROL_LOW | POWER_SENSE_LOW,
पूर्ण;

अटल व्योम __init zylonite_init_ohci(व्योम)
अणु
	pxa_set_ohci_info(&zylonite_ohci_info);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम zylonite_init_ohci(व्योम) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_USB_OHCI_HCD || CONFIG_USB_OHCI_HCD_MODULE */

अटल व्योम __init zylonite_init(व्योम)
अणु
	pxa_set_ffuart_info(शून्य);
	pxa_set_btuart_info(शून्य);
	pxa_set_stuart_info(शून्य);

	/* board-processor specअगरic initialization */
	zylonite_pxa300_init();
	zylonite_pxa320_init();

	/*
	 * Note: We depend that the bootloader set
	 * the correct value to MSC रेजिस्टर क्रम SMC91x.
	 */
	smc91x_resources[1].start = PXA_GPIO_TO_IRQ(gpio_eth_irq);
	smc91x_resources[1].end   = PXA_GPIO_TO_IRQ(gpio_eth_irq);
	platक्रमm_device_रेजिस्टर(&smc91x_device);

	pxa_set_ac97_info(शून्य);
	zylonite_init_lcd();
	zylonite_init_mmc();
	zylonite_init_keypad();
	zylonite_init_nand();
	zylonite_init_leds();
	zylonite_init_ohci();
पूर्ण

MACHINE_START(ZYLONITE, "PXA3xx Platform Development Kit (aka Zylonite)")
	.atag_offset	= 0x100,
	.map_io		= pxa3xx_map_io,
	.nr_irqs	= ZYLONITE_NR_IRQS,
	.init_irq	= pxa3xx_init_irq,
	.handle_irq	= pxa3xx_handle_irq,
	.init_समय	= pxa_समयr_init,
	.init_machine	= zylonite_init,
	.restart	= pxa_restart,
MACHINE_END
