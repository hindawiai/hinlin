<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/mach-pxa/tavorevb.c
 *
 *  Support क्रम the Marvell PXA930 Evaluation Board
 *
 *  Copyright (C) 2007-2008 Marvell International Ltd.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/clk.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/smc91x.h>
#समावेश <linux/pwm.h>
#समावेश <linux/pwm_backlight.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>

#समावेश "pxa930.h"
#समावेश <linux/platक्रमm_data/video-pxafb.h>
#समावेश <linux/platक्रमm_data/keypad-pxa27x.h>

#समावेश "devices.h"
#समावेश "generic.h"

/* Tavor EVB MFP configurations */
अटल mfp_cfg_t tavorevb_mfp_cfg[] __initdata = अणु
	/* Ethernet */
	DF_nCS1_nCS3,
	GPIO47_GPIO,

	/* LCD */
	GPIO23_LCD_DD0,
	GPIO24_LCD_DD1,
	GPIO25_LCD_DD2,
	GPIO26_LCD_DD3,
	GPIO27_LCD_DD4,
	GPIO28_LCD_DD5,
	GPIO29_LCD_DD6,
	GPIO44_LCD_DD7,
	GPIO21_LCD_CS,
	GPIO22_LCD_CS2,

	GPIO17_LCD_FCLK_RD,
	GPIO18_LCD_LCLK_A0,
	GPIO19_LCD_PCLK_WR,

	/* LCD Backlight */
	GPIO43_PWM3,	/* primary backlight */
	GPIO32_PWM0,	/* secondary backlight */

	/* Keypad */
	GPIO0_KP_MKIN_0,
	GPIO2_KP_MKIN_1,
	GPIO4_KP_MKIN_2,
	GPIO6_KP_MKIN_3,
	GPIO8_KP_MKIN_4,
	GPIO10_KP_MKIN_5,
	GPIO12_KP_MKIN_6,
	GPIO1_KP_MKOUT_0,
	GPIO3_KP_MKOUT_1,
	GPIO5_KP_MKOUT_2,
	GPIO7_KP_MKOUT_3,
	GPIO9_KP_MKOUT_4,
	GPIO11_KP_MKOUT_5,
	GPIO13_KP_MKOUT_6,

	GPIO14_KP_DKIN_2,
	GPIO15_KP_DKIN_3,
पूर्ण;

#घोषणा TAVOREVB_ETH_PHYS	(0x14000000)

अटल काष्ठा resource smc91x_resources[] = अणु
	[0] = अणु
		.start	= (TAVOREVB_ETH_PHYS + 0x300),
		.end	= (TAVOREVB_ETH_PHYS + 0xfffff),
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= PXA_GPIO_TO_IRQ(mfp_to_gpio(MFP_PIN_GPIO47)),
		.end	= PXA_GPIO_TO_IRQ(mfp_to_gpio(MFP_PIN_GPIO47)),
		.flags	= IORESOURCE_IRQ | IORESOURCE_IRQ_HIGHEDGE,
	पूर्ण
पूर्ण;

अटल काष्ठा smc91x_platdata tavorevb_smc91x_info = अणु
	.flags	= SMC91X_USE_16BIT | SMC91X_NOWAIT | SMC91X_USE_DMA,
पूर्ण;

अटल काष्ठा platक्रमm_device smc91x_device = अणु
	.name		= "smc91x",
	.id		= 0,
	.num_resources	= ARRAY_SIZE(smc91x_resources),
	.resource	= smc91x_resources,
	.dev		= अणु
		.platक्रमm_data = &tavorevb_smc91x_info,
	पूर्ण,
पूर्ण;

#अगर defined(CONFIG_KEYBOARD_PXA27x) || defined(CONFIG_KEYBOARD_PXA27x_MODULE)
अटल स्थिर अचिन्हित पूर्णांक tavorevb_matrix_key_map[] = अणु
	/* KEY(row, col, key_code) */
	KEY(0, 4, KEY_A), KEY(0, 5, KEY_B), KEY(0, 6, KEY_C),
	KEY(1, 4, KEY_E), KEY(1, 5, KEY_F), KEY(1, 6, KEY_G),
	KEY(2, 4, KEY_I), KEY(2, 5, KEY_J), KEY(2, 6, KEY_K),
	KEY(3, 4, KEY_M), KEY(3, 5, KEY_N), KEY(3, 6, KEY_O),
	KEY(4, 5, KEY_R), KEY(4, 6, KEY_S),
	KEY(5, 4, KEY_U), KEY(5, 4, KEY_V), KEY(5, 6, KEY_W),

	KEY(6, 4, KEY_Y), KEY(6, 5, KEY_Z),

	KEY(0, 3, KEY_0), KEY(2, 0, KEY_1), KEY(2, 1, KEY_2), KEY(2, 2, KEY_3),
	KEY(2, 3, KEY_4), KEY(1, 0, KEY_5), KEY(1, 1, KEY_6), KEY(1, 2, KEY_7),
	KEY(1, 3, KEY_8), KEY(0, 2, KEY_9),

	KEY(6, 6, KEY_SPACE),
	KEY(0, 0, KEY_KPASTERISK), 	/* * */
	KEY(0, 1, KEY_KPDOT), 		/* # */

	KEY(4, 1, KEY_UP),
	KEY(4, 3, KEY_DOWN),
	KEY(4, 0, KEY_LEFT),
	KEY(4, 2, KEY_RIGHT),
	KEY(6, 0, KEY_HOME),
	KEY(3, 2, KEY_END),
	KEY(6, 1, KEY_DELETE),
	KEY(5, 2, KEY_BACK),
	KEY(6, 3, KEY_CAPSLOCK),	/* KEY_LEFTSHIFT), */

	KEY(4, 4, KEY_ENTER),		/* scroll push */
	KEY(6, 2, KEY_ENTER),		/* keypad action */

	KEY(3, 1, KEY_SEND),
	KEY(5, 3, KEY_RECORD),
	KEY(5, 0, KEY_VOLUMEUP),
	KEY(5, 1, KEY_VOLUMEDOWN),

	KEY(3, 0, KEY_F22),	/* soft1 */
	KEY(3, 3, KEY_F23),	/* soft2 */
पूर्ण;

अटल काष्ठा matrix_keymap_data tavorevb_matrix_keymap_data = अणु
	.keymap		= tavorevb_matrix_key_map,
	.keymap_size	= ARRAY_SIZE(tavorevb_matrix_key_map),
पूर्ण;

अटल काष्ठा pxa27x_keypad_platक्रमm_data tavorevb_keypad_info = अणु
	.matrix_key_rows	= 7,
	.matrix_key_cols	= 7,
	.matrix_keymap_data	= &tavorevb_matrix_keymap_data,
	.debounce_पूर्णांकerval	= 30,
पूर्ण;

अटल व्योम __init tavorevb_init_keypad(व्योम)
अणु
	pxa_set_keypad_info(&tavorevb_keypad_info);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम tavorevb_init_keypad(व्योम) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_KEYBOARD_PXA27x || CONFIG_KEYBOARD_PXA27x_MODULE */

#अगर defined(CONFIG_FB_PXA) || defined(CONFIG_FB_PXA_MODULE)
अटल काष्ठा pwm_lookup tavorevb_pwm_lookup[] = अणु
	PWM_LOOKUP("pxa27x-pwm.0", 1, "pwm-backlight.0", शून्य, 100000,
		   PWM_POLARITY_NORMAL),
	PWM_LOOKUP("pxa27x-pwm.0", 0, "pwm-backlight.1", शून्य, 100000,
		   PWM_POLARITY_NORMAL),
पूर्ण;

अटल काष्ठा platक्रमm_pwm_backlight_data tavorevb_backlight_data[] = अणु
	[0] = अणु
		/* primary backlight */
		.max_brightness	= 100,
		.dft_brightness	= 100,
	पूर्ण,
	[1] = अणु
		/* secondary backlight */
		.max_brightness	= 100,
		.dft_brightness	= 100,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device tavorevb_backlight_devices[] = अणु
	[0] = अणु
		.name		= "pwm-backlight",
		.id		= 0,
		.dev		= अणु
			.platक्रमm_data = &tavorevb_backlight_data[0],
		पूर्ण,
	पूर्ण,
	[1] = अणु
		.name		= "pwm-backlight",
		.id		= 1,
		.dev		= अणु
			.platक्रमm_data = &tavorevb_backlight_data[1],
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल uपूर्णांक16_t panel_init[] = अणु
	/* DSTB OUT */
	SMART_CMD(0x00),
	SMART_CMD_NOOP,
	SMART_DELAY(1),

	SMART_CMD(0x00),
	SMART_CMD_NOOP,
	SMART_DELAY(1),

	SMART_CMD(0x00),
	SMART_CMD_NOOP,
	SMART_DELAY(1),

	/* STB OUT */
	SMART_CMD(0x00),
	SMART_CMD(0x1D),
	SMART_DAT(0x00),
	SMART_DAT(0x05),
	SMART_DELAY(1),

	/* P-ON Init sequence */
	SMART_CMD(0x00), /* OSC ON */
	SMART_CMD(0x00),
	SMART_DAT(0x00),
	SMART_DAT(0x01),
	SMART_CMD(0x00),
	SMART_CMD(0x01), /* SOURCE DRIVER SHIFT सूचीECTION and display RAM setting */
	SMART_DAT(0x01),
	SMART_DAT(0x27),
	SMART_CMD(0x00),
	SMART_CMD(0x02), /* LINE INV */
	SMART_DAT(0x02),
	SMART_DAT(0x00),
	SMART_CMD(0x00),
	SMART_CMD(0x03), /* IF mode(1) */
	SMART_DAT(0x01), /* 8bit smart mode(8-8),high speed ग_लिखो mode */
	SMART_DAT(0x30),
	SMART_CMD(0x07),
	SMART_CMD(0x00), /* RAM Write Mode */
	SMART_DAT(0x00),
	SMART_DAT(0x03),
	SMART_CMD(0x00),

	/* DISPLAY Setting,  262K, fixed(NO scroll), no split screen */
	SMART_CMD(0x07),
	SMART_DAT(0x40), /* 16/18/19 BPP */
	SMART_DAT(0x00),
	SMART_CMD(0x00),
	SMART_CMD(0x08), /* BP, FP Seting, BP=2H, FP=3H */
	SMART_DAT(0x03),
	SMART_DAT(0x02),
	SMART_CMD(0x00),
	SMART_CMD(0x0C), /* IF mode(2), using पूर्णांकernal घड़ी & MPU */
	SMART_DAT(0x00),
	SMART_DAT(0x00),
	SMART_CMD(0x00),
	SMART_CMD(0x0D), /* Frame setting, 1Min. Frequence, 16CLK */
	SMART_DAT(0x00),
	SMART_DAT(0x10),
	SMART_CMD(0x00),
	SMART_CMD(0x12), /* Timing(1),ASW W=4CLK, ASW ST=1CLK */
	SMART_DAT(0x03),
	SMART_DAT(0x02),
	SMART_CMD(0x00),
	SMART_CMD(0x13), /* Timing(2),OEV ST=0.5CLK, OEV ED=1CLK */
	SMART_DAT(0x01),
	SMART_DAT(0x02),
	SMART_CMD(0x00),
	SMART_CMD(0x14), /* Timing(3), ASW HOLD=0.5CLK */
	SMART_DAT(0x00),
	SMART_DAT(0x00),
	SMART_CMD(0x00),
	SMART_CMD(0x15), /* Timing(4), CKV ST=0CLK, CKV ED=1CLK */
	SMART_DAT(0x20),
	SMART_DAT(0x00),
	SMART_CMD(0x00),
	SMART_CMD(0x1C),
	SMART_DAT(0x00),
	SMART_DAT(0x00),
	SMART_CMD(0x03),
	SMART_CMD(0x00),
	SMART_DAT(0x04),
	SMART_DAT(0x03),
	SMART_CMD(0x03),
	SMART_CMD(0x01),
	SMART_DAT(0x03),
	SMART_DAT(0x04),
	SMART_CMD(0x03),
	SMART_CMD(0x02),
	SMART_DAT(0x04),
	SMART_DAT(0x03),
	SMART_CMD(0x03),
	SMART_CMD(0x03),
	SMART_DAT(0x03),
	SMART_DAT(0x03),
	SMART_CMD(0x03),
	SMART_CMD(0x04),
	SMART_DAT(0x01),
	SMART_DAT(0x01),
	SMART_CMD(0x03),
	SMART_CMD(0x05),
	SMART_DAT(0x00),
	SMART_DAT(0x00),
	SMART_CMD(0x04),
	SMART_CMD(0x02),
	SMART_DAT(0x00),
	SMART_DAT(0x00),
	SMART_CMD(0x04),
	SMART_CMD(0x03),
	SMART_DAT(0x01),
	SMART_DAT(0x3F),
	SMART_DELAY(0),

	/* DISP RAM setting: 240*320 */
	SMART_CMD(0x04), /* HADDR, START 0 */
	SMART_CMD(0x06),
	SMART_DAT(0x00),
	SMART_DAT(0x00), /* x1,3 */
	SMART_CMD(0x04), /* HADDR,  END   4 */
	SMART_CMD(0x07),
	SMART_DAT(0x00),
	SMART_DAT(0xEF), /* x2, 7 */
	SMART_CMD(0x04), /* VADDR, START 8 */
	SMART_CMD(0x08),
	SMART_DAT(0x00), /* y1, 10 */
	SMART_DAT(0x00), /* y1, 11 */
	SMART_CMD(0x04), /* VADDR, END 12 */
	SMART_CMD(0x09),
	SMART_DAT(0x01), /* y2, 14 */
	SMART_DAT(0x3F), /* y2, 15 */
	SMART_CMD(0x02), /* RAM ADDR SETTING 16 */
	SMART_CMD(0x00),
	SMART_DAT(0x00),
	SMART_DAT(0x00), /* x1, 19 */
	SMART_CMD(0x02), /* RAM ADDR SETTING 20 */
	SMART_CMD(0x01),
	SMART_DAT(0x00), /* y1, 22 */
	SMART_DAT(0x00), /* y1, 23 */
पूर्ण;

अटल uपूर्णांक16_t panel_on[] = अणु
	/* Power-IC ON */
	SMART_CMD(0x01),
	SMART_CMD(0x02),
	SMART_DAT(0x07),
	SMART_DAT(0x7D),
	SMART_CMD(0x01),
	SMART_CMD(0x03),
	SMART_DAT(0x00),
	SMART_DAT(0x05),
	SMART_CMD(0x01),
	SMART_CMD(0x04),
	SMART_DAT(0x00),
	SMART_DAT(0x00),
	SMART_CMD(0x01),
	SMART_CMD(0x05),
	SMART_DAT(0x00),
	SMART_DAT(0x15),
	SMART_CMD(0x01),
	SMART_CMD(0x00),
	SMART_DAT(0xC0),
	SMART_DAT(0x10),
	SMART_DELAY(30),

	/* DISP ON */
	SMART_CMD(0x01),
	SMART_CMD(0x01),
	SMART_DAT(0x00),
	SMART_DAT(0x01),
	SMART_CMD(0x01),
	SMART_CMD(0x00),
	SMART_DAT(0xFF),
	SMART_DAT(0xFE),
	SMART_DELAY(150),
पूर्ण;

अटल uपूर्णांक16_t panel_off[] = अणु
	SMART_CMD(0x00),
	SMART_CMD(0x1E),
	SMART_DAT(0x00),
	SMART_DAT(0x0A),
	SMART_CMD(0x01),
	SMART_CMD(0x00),
	SMART_DAT(0xFF),
	SMART_DAT(0xEE),
	SMART_CMD(0x01),
	SMART_CMD(0x00),
	SMART_DAT(0xF8),
	SMART_DAT(0x12),
	SMART_CMD(0x01),
	SMART_CMD(0x00),
	SMART_DAT(0xE8),
	SMART_DAT(0x11),
	SMART_CMD(0x01),
	SMART_CMD(0x00),
	SMART_DAT(0xC0),
	SMART_DAT(0x11),
	SMART_CMD(0x01),
	SMART_CMD(0x00),
	SMART_DAT(0x40),
	SMART_DAT(0x11),
	SMART_CMD(0x01),
	SMART_CMD(0x00),
	SMART_DAT(0x00),
	SMART_DAT(0x10),
पूर्ण;

अटल uपूर्णांक16_t update_framedata[] = अणु
	/* ग_लिखो ram */
	SMART_CMD(0x02),
	SMART_CMD(0x02),

	/* ग_लिखो frame data */
	SMART_CMD_WRITE_FRAME,
पूर्ण;

अटल व्योम lपंचांग020d550_lcd_घातer(पूर्णांक on, काष्ठा fb_var_screeninfo *var)
अणु
	काष्ठा fb_info *info = container_of(var, काष्ठा fb_info, var);

	अगर (on) अणु
		pxafb_smart_queue(info, ARRAY_AND_SIZE(panel_init));
		pxafb_smart_queue(info, ARRAY_AND_SIZE(panel_on));
	पूर्ण अन्यथा अणु
		pxafb_smart_queue(info, ARRAY_AND_SIZE(panel_off));
	पूर्ण

	अगर (pxafb_smart_flush(info))
		pr_err("%s: timed out\n", __func__);
पूर्ण

अटल व्योम lपंचांग020d550_update(काष्ठा fb_info *info)
अणु
	pxafb_smart_queue(info, ARRAY_AND_SIZE(update_framedata));
	pxafb_smart_flush(info);
पूर्ण

अटल काष्ठा pxafb_mode_info toshiba_lपंचांग020d550_modes[] = अणु
	[0] = अणु
		.xres			= 240,
		.yres			= 320,
		.bpp			= 16,
		.a0csrd_set_hld		= 30,
		.a0cswr_set_hld		= 30,
		.wr_pulse_width		= 30,
		.rd_pulse_width 	= 170,
		.op_hold_समय 		= 30,
		.cmd_inh_समय		= 60,

		/* L_LCLK_A0 and L_LCLK_RD active low */
		.sync			= FB_SYNC_HOR_HIGH_ACT |
					  FB_SYNC_VERT_HIGH_ACT,
	पूर्ण,
पूर्ण;

अटल काष्ठा pxafb_mach_info tavorevb_lcd_info = अणु
	.modes			= toshiba_lपंचांग020d550_modes,
	.num_modes		= 1,
	.lcd_conn		= LCD_SMART_PANEL_8BPP | LCD_PCLK_EDGE_FALL,
	.pxafb_lcd_घातer	= lपंचांग020d550_lcd_घातer,
	.smart_update		= lपंचांग020d550_update,
पूर्ण;

अटल व्योम __init tavorevb_init_lcd(व्योम)
अणु
	pwm_add_table(tavorevb_pwm_lookup, ARRAY_SIZE(tavorevb_pwm_lookup));
	platक्रमm_device_रेजिस्टर(&tavorevb_backlight_devices[0]);
	platक्रमm_device_रेजिस्टर(&tavorevb_backlight_devices[1]);
	pxa_set_fb_info(शून्य, &tavorevb_lcd_info);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम tavorevb_init_lcd(व्योम) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_FB_PXA || CONFIG_FB_PXA_MODULE */

अटल व्योम __init tavorevb_init(व्योम)
अणु
	/* initialize MFP configurations */
	pxa3xx_mfp_config(ARRAY_AND_SIZE(tavorevb_mfp_cfg));

	pxa_set_ffuart_info(शून्य);
	pxa_set_btuart_info(शून्य);
	pxa_set_stuart_info(शून्य);

	platक्रमm_device_रेजिस्टर(&smc91x_device);

	tavorevb_init_lcd();
	tavorevb_init_keypad();
पूर्ण

MACHINE_START(TAVOREVB, "PXA930 Evaluation Board (aka TavorEVB)")
	/* Maपूर्णांकainer: Eric Miao <eric.miao@marvell.com> */
	.atag_offset    = 0x100,
	.map_io         = pxa3xx_map_io,
	.nr_irqs	= PXA_NR_IRQS,
	.init_irq       = pxa3xx_init_irq,
	.handle_irq       = pxa3xx_handle_irq,
	.init_समय	= pxa_समयr_init,
	.init_machine   = tavorevb_init,
	.restart	= pxa_restart,
MACHINE_END
