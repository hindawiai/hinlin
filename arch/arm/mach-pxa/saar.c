<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/mach-pxa/saar.c
 *
 *  Support क्रम the Marvell PXA930 Handheld Platक्रमm (aka SAAR)
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
#समावेश <linux/delay.h>
#समावेश <linux/fb.h>
#समावेश <linux/i2c.h>
#समावेश <linux/platक्रमm_data/i2c-pxa.h>
#समावेश <linux/smc91x.h>
#समावेश <linux/mfd/da903x.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/mtd/onenand.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/flash.h>

#समावेश "pxa930.h"
#समावेश <linux/platक्रमm_data/video-pxafb.h>

#समावेश "devices.h"
#समावेश "generic.h"

#घोषणा GPIO_LCD_RESET		(16)

/* SAAR MFP configurations */
अटल mfp_cfg_t saar_mfp_cfg[] __initdata = अणु
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
	GPIO22_LCD_VSYNC,
	GPIO17_LCD_FCLK_RD,
	GPIO18_LCD_LCLK_A0,
	GPIO19_LCD_PCLK_WR,
	GPIO16_GPIO, /* LCD reset */

	/* Ethernet */
	DF_nCS1_nCS3,
	GPIO97_GPIO,

	/* DFI */
	DF_INT_RnB_ND_INT_RnB,
	DF_nRE_nOE_ND_nRE,
	DF_nWE_ND_nWE,
	DF_CLE_nOE_ND_CLE,
	DF_nADV1_ALE_ND_ALE,
	DF_nADV2_ALE_nCS3,
	DF_nCS0_ND_nCS0,
	DF_IO0_ND_IO0,
	DF_IO1_ND_IO1,
	DF_IO2_ND_IO2,
	DF_IO3_ND_IO3,
	DF_IO4_ND_IO4,
	DF_IO5_ND_IO5,
	DF_IO6_ND_IO6,
	DF_IO7_ND_IO7,
	DF_IO8_ND_IO8,
	DF_IO9_ND_IO9,
	DF_IO10_ND_IO10,
	DF_IO11_ND_IO11,
	DF_IO12_ND_IO12,
	DF_IO13_ND_IO13,
	DF_IO14_ND_IO14,
	DF_IO15_ND_IO15,
पूर्ण;

#घोषणा SAAR_ETH_PHYS	(0x14000000)

अटल काष्ठा resource smc91x_resources[] = अणु
	[0] = अणु
		.start	= (SAAR_ETH_PHYS + 0x300),
		.end	= (SAAR_ETH_PHYS + 0xfffff),
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= PXA_GPIO_TO_IRQ(mfp_to_gpio(MFP_PIN_GPIO97)),
		.end	= PXA_GPIO_TO_IRQ(mfp_to_gpio(MFP_PIN_GPIO97)),
		.flags	= IORESOURCE_IRQ | IORESOURCE_IRQ_HIGHEDGE,
	पूर्ण
पूर्ण;

अटल काष्ठा smc91x_platdata saar_smc91x_info = अणु
	.flags	= SMC91X_USE_16BIT | SMC91X_NOWAIT | SMC91X_USE_DMA,
पूर्ण;

अटल काष्ठा platक्रमm_device smc91x_device = अणु
	.name		= "smc91x",
	.id		= 0,
	.num_resources	= ARRAY_SIZE(smc91x_resources),
	.resource	= smc91x_resources,
	.dev		= अणु
		.platक्रमm_data = &saar_smc91x_info,
	पूर्ण,
पूर्ण;

#अगर defined(CONFIG_FB_PXA) || defined(CONFIG_FB_PXA_MODULE)
अटल uपूर्णांक16_t lcd_घातer_on[] = अणु
	/* single frame */
	SMART_CMD_NOOP,
	SMART_CMD(0x00),
	SMART_DELAY(0),

	SMART_CMD_NOOP,
	SMART_CMD(0x00),
	SMART_DELAY(0),

	SMART_CMD_NOOP,
	SMART_CMD(0x00),
	SMART_DELAY(0),

	SMART_CMD_NOOP,
	SMART_CMD(0x00),
	SMART_DELAY(10),

	/* calibration control */
	SMART_CMD(0x00),
	SMART_CMD(0xA4),
	SMART_DAT(0x80),
	SMART_DAT(0x01),
	SMART_DELAY(150),

	/*Power-On Init sequence*/
	SMART_CMD(0x00),	/* output ctrl */
	SMART_CMD(0x01),
	SMART_DAT(0x01),
	SMART_DAT(0x00),
	SMART_CMD(0x00),	/* wave ctrl */
	SMART_CMD(0x02),
	SMART_DAT(0x07),
	SMART_DAT(0x00),
	SMART_CMD(0x00),
	SMART_CMD(0x03),	/* entry mode */
	SMART_DAT(0xD0),
	SMART_DAT(0x30),
	SMART_CMD(0x00),
	SMART_CMD(0x08),	/* display ctrl 2 */
	SMART_DAT(0x08),
	SMART_DAT(0x08),
	SMART_CMD(0x00),
	SMART_CMD(0x09),	/* display ctrl 3 */
	SMART_DAT(0x04),
	SMART_DAT(0x2F),
	SMART_CMD(0x00),
	SMART_CMD(0x0A),	/* display ctrl 4 */
	SMART_DAT(0x00),
	SMART_DAT(0x08),
	SMART_CMD(0x00),
	SMART_CMD(0x0D),	/* Frame Marker position */
	SMART_DAT(0x00),
	SMART_DAT(0x08),
	SMART_CMD(0x00),
	SMART_CMD(0x60),	/* Driver output control */
	SMART_DAT(0x27),
	SMART_DAT(0x00),
	SMART_CMD(0x00),
	SMART_CMD(0x61),	/* Base image display control */
	SMART_DAT(0x00),
	SMART_DAT(0x01),
	SMART_CMD(0x00),
	SMART_CMD(0x30),	/* Y settings 30h-3Dh */
	SMART_DAT(0x07),
	SMART_DAT(0x07),
	SMART_CMD(0x00),
	SMART_CMD(0x31),
	SMART_DAT(0x00),
	SMART_DAT(0x07),
	SMART_CMD(0x00),
	SMART_CMD(0x32),	/* Timing(3), ASW HOLD=0.5CLK */
	SMART_DAT(0x04),
	SMART_DAT(0x00),
	SMART_CMD(0x00),
	SMART_CMD(0x33),	/* Timing(4), CKV ST=0CLK, CKV ED=1CLK */
	SMART_DAT(0x03),
	SMART_DAT(0x03),
	SMART_CMD(0x00),
	SMART_CMD(0x34),
	SMART_DAT(0x00),
	SMART_DAT(0x00),
	SMART_CMD(0x00),
	SMART_CMD(0x35),
	SMART_DAT(0x02),
	SMART_DAT(0x05),
	SMART_CMD(0x00),
	SMART_CMD(0x36),
	SMART_DAT(0x1F),
	SMART_DAT(0x1F),
	SMART_CMD(0x00),
	SMART_CMD(0x37),
	SMART_DAT(0x07),
	SMART_DAT(0x07),
	SMART_CMD(0x00),
	SMART_CMD(0x38),
	SMART_DAT(0x00),
	SMART_DAT(0x07),
	SMART_CMD(0x00),
	SMART_CMD(0x39),
	SMART_DAT(0x04),
	SMART_DAT(0x00),
	SMART_CMD(0x00),
	SMART_CMD(0x3A),
	SMART_DAT(0x03),
	SMART_DAT(0x03),
	SMART_CMD(0x00),
	SMART_CMD(0x3B),
	SMART_DAT(0x00),
	SMART_DAT(0x00),
	SMART_CMD(0x00),
	SMART_CMD(0x3C),
	SMART_DAT(0x02),
	SMART_DAT(0x05),
	SMART_CMD(0x00),
	SMART_CMD(0x3D),
	SMART_DAT(0x1F),
	SMART_DAT(0x1F),
	SMART_CMD(0x00),	/* Display control 1 */
	SMART_CMD(0x07),
	SMART_DAT(0x00),
	SMART_DAT(0x01),
	SMART_CMD(0x00),	/* Power control 5 */
	SMART_CMD(0x17),
	SMART_DAT(0x00),
	SMART_DAT(0x01),
	SMART_CMD(0x00),	/* Power control 1 */
	SMART_CMD(0x10),
	SMART_DAT(0x10),
	SMART_DAT(0xB0),
	SMART_CMD(0x00),	/* Power control 2 */
	SMART_CMD(0x11),
	SMART_DAT(0x01),
	SMART_DAT(0x30),
	SMART_CMD(0x00),	/* Power control 3 */
	SMART_CMD(0x12),
	SMART_DAT(0x01),
	SMART_DAT(0x9E),
	SMART_CMD(0x00),	/* Power control 4 */
	SMART_CMD(0x13),
	SMART_DAT(0x17),
	SMART_DAT(0x00),
	SMART_CMD(0x00),	/* Power control 3 */
	SMART_CMD(0x12),
	SMART_DAT(0x01),
	SMART_DAT(0xBE),
	SMART_DELAY(100),

	/* display mode : 240*320 */
	SMART_CMD(0x00),	/* RAM address set(H) 0*/
	SMART_CMD(0x20),
	SMART_DAT(0x00),
	SMART_DAT(0x00),
	SMART_CMD(0x00),	/* RAM address set(V)   4*/
	SMART_CMD(0x21),
	SMART_DAT(0x00),
	SMART_DAT(0x00),
	SMART_CMD(0x00),	/* Start of Winकरोw RAM address set(H) 8*/
	SMART_CMD(0x50),
	SMART_DAT(0x00),
	SMART_DAT(0x00),
	SMART_CMD(0x00), 	/* End of Winकरोw RAM address set(H) 12*/
	SMART_CMD(0x51),
	SMART_DAT(0x00),
	SMART_DAT(0xEF),
	SMART_CMD(0x00),	/* Start of Winकरोw RAM address set(V) 16*/
	SMART_CMD(0x52),
	SMART_DAT(0x00),
	SMART_DAT(0x00),
	SMART_CMD(0x00),	/* End of Winकरोw RAM address set(V) 20*/
	SMART_CMD(0x53),
	SMART_DAT(0x01),
	SMART_DAT(0x3F),
	SMART_CMD(0x00), 	/* Panel पूर्णांकerface control 1 */
	SMART_CMD(0x90),
	SMART_DAT(0x00),
	SMART_DAT(0x1A),
	SMART_CMD(0x00), 	/* Panel पूर्णांकerface control 2 */
	SMART_CMD(0x92),
	SMART_DAT(0x04),
	SMART_DAT(0x00),
	SMART_CMD(0x00), 	/* Panel पूर्णांकerface control 3 */
	SMART_CMD(0x93),
	SMART_DAT(0x00),
	SMART_DAT(0x05),
	SMART_DELAY(20),
पूर्ण;

अटल uपूर्णांक16_t lcd_panel_on[] = अणु
	SMART_CMD(0x00),
	SMART_CMD(0x07),
	SMART_DAT(0x00),
	SMART_DAT(0x21),
	SMART_DELAY(1),

	SMART_CMD(0x00),
	SMART_CMD(0x07),
	SMART_DAT(0x00),
	SMART_DAT(0x61),
	SMART_DELAY(100),

	SMART_CMD(0x00),
	SMART_CMD(0x07),
	SMART_DAT(0x01),
	SMART_DAT(0x73),
	SMART_DELAY(1),
पूर्ण;

अटल uपूर्णांक16_t lcd_panel_off[] = अणु
	SMART_CMD(0x00),
	SMART_CMD(0x07),
	SMART_DAT(0x00),
	SMART_DAT(0x72),
	SMART_DELAY(40),

	SMART_CMD(0x00),
	SMART_CMD(0x07),
	SMART_DAT(0x00),
	SMART_DAT(0x01),
	SMART_DELAY(1),

	SMART_CMD(0x00),
	SMART_CMD(0x07),
	SMART_DAT(0x00),
	SMART_DAT(0x00),
	SMART_DELAY(1),
पूर्ण;

अटल uपूर्णांक16_t lcd_घातer_off[] = अणु
	SMART_CMD(0x00),
	SMART_CMD(0x10),
	SMART_DAT(0x00),
	SMART_DAT(0x80),

	SMART_CMD(0x00),
	SMART_CMD(0x11),
	SMART_DAT(0x01),
	SMART_DAT(0x60),

	SMART_CMD(0x00),
	SMART_CMD(0x12),
	SMART_DAT(0x01),
	SMART_DAT(0xAE),
	SMART_DELAY(40),

	SMART_CMD(0x00),
	SMART_CMD(0x10),
	SMART_DAT(0x00),
	SMART_DAT(0x00),
पूर्ण;

अटल uपूर्णांक16_t update_framedata[] = अणु
	/* set display ram: 240*320 */
	SMART_CMD(0x00), /* RAM address set(H) 0*/
	SMART_CMD(0x20),
	SMART_DAT(0x00),
	SMART_DAT(0x00),
	SMART_CMD(0x00), /* RAM address set(V) 4*/
	SMART_CMD(0x21),
	SMART_DAT(0x00),
	SMART_DAT(0x00),
	SMART_CMD(0x00), /* Start of Winकरोw RAM address set(H) 8 */
	SMART_CMD(0x50),
	SMART_DAT(0x00),
	SMART_DAT(0x00),
	SMART_CMD(0x00), /* End of Winकरोw RAM address set(H) 12 */
	SMART_CMD(0x51),
	SMART_DAT(0x00),
	SMART_DAT(0xEF),
	SMART_CMD(0x00), /* Start of Winकरोw RAM address set(V) 16 */
	SMART_CMD(0x52),
	SMART_DAT(0x00),
	SMART_DAT(0x00),
	SMART_CMD(0x00), /* End of Winकरोw RAM address set(V) 20 */
	SMART_CMD(0x53),
	SMART_DAT(0x01),
	SMART_DAT(0x3F),

	/* रुको क्रम vsync cmd beक्रमe transferring frame data */
	SMART_CMD_WAIT_FOR_VSYNC,

	/* ग_लिखो ram */
	SMART_CMD(0x00),
	SMART_CMD(0x22),

	/* ग_लिखो frame data */
	SMART_CMD_WRITE_FRAME,
पूर्ण;

अटल व्योम lपंचांग022a97a_lcd_घातer(पूर्णांक on, काष्ठा fb_var_screeninfo *var)
अणु
	अटल पूर्णांक pin_requested = 0;
	काष्ठा fb_info *info = container_of(var, काष्ठा fb_info, var);
	पूर्णांक err;

	अगर (!pin_requested) अणु
		err = gpio_request(GPIO_LCD_RESET, "lcd reset");
		अगर (err) अणु
			pr_err("failed to request gpio for LCD reset\n");
			वापस;
		पूर्ण

		gpio_direction_output(GPIO_LCD_RESET, 0);
		pin_requested = 1;
	पूर्ण

	अगर (on) अणु
		gpio_set_value(GPIO_LCD_RESET, 0); msleep(100);
		gpio_set_value(GPIO_LCD_RESET, 1); msleep(10);

		pxafb_smart_queue(info, ARRAY_AND_SIZE(lcd_घातer_on));
		pxafb_smart_queue(info, ARRAY_AND_SIZE(lcd_panel_on));
	पूर्ण अन्यथा अणु
		pxafb_smart_queue(info, ARRAY_AND_SIZE(lcd_panel_off));
		pxafb_smart_queue(info, ARRAY_AND_SIZE(lcd_घातer_off));
	पूर्ण

	err = pxafb_smart_flush(info);
	अगर (err)
		pr_err("%s: timed out\n", __func__);
पूर्ण

अटल व्योम lपंचांग022a97a_update(काष्ठा fb_info *info)
अणु
	pxafb_smart_queue(info, ARRAY_AND_SIZE(update_framedata));
	pxafb_smart_flush(info);
पूर्ण

अटल काष्ठा pxafb_mode_info toshiba_lपंचांग022a97a_modes[] = अणु
	[0] = अणु
		.xres			= 240,
		.yres			= 320,
		.bpp			= 16,
		.a0csrd_set_hld		= 30,
		.a0cswr_set_hld		= 30,
		.wr_pulse_width		= 30,
		.rd_pulse_width 	= 30,
		.op_hold_समय 		= 30,
		.cmd_inh_समय		= 60,

		/* L_LCLK_A0 and L_LCLK_RD active low */
		.sync			= FB_SYNC_HOR_HIGH_ACT |
					  FB_SYNC_VERT_HIGH_ACT,
	पूर्ण,
पूर्ण;

अटल काष्ठा pxafb_mach_info saar_lcd_info = अणु
	.modes			= toshiba_lपंचांग022a97a_modes,
	.num_modes		= 1,
	.lcd_conn		= LCD_SMART_PANEL_8BPP | LCD_PCLK_EDGE_FALL,
	.pxafb_lcd_घातer	= lपंचांग022a97a_lcd_घातer,
	.smart_update		= lपंचांग022a97a_update,
पूर्ण;

अटल व्योम __init saar_init_lcd(व्योम)
अणु
	pxa_set_fb_info(शून्य, &saar_lcd_info);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम saar_init_lcd(व्योम) अणुपूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_I2C_PXA) || defined(CONFIG_I2C_PXA_MODULE)
अटल काष्ठा da9034_backlight_pdata saar_da9034_backlight = अणु
	.output_current	= 4,	/* 4mA */
पूर्ण;

अटल काष्ठा da903x_subdev_info saar_da9034_subdevs[] = अणु
	[0] = अणु
		.name		= "da903x-backlight",
		.id		= DA9034_ID_WLED,
		.platक्रमm_data	= &saar_da9034_backlight,
	पूर्ण,
पूर्ण;

अटल काष्ठा da903x_platक्रमm_data saar_da9034_info = अणु
	.num_subdevs	= ARRAY_SIZE(saar_da9034_subdevs),
	.subdevs	= saar_da9034_subdevs,
पूर्ण;

अटल काष्ठा i2c_board_info saar_i2c_info[] = अणु
	[0] = अणु
		.type		= "da9034",
		.addr		= 0x34,
		.platक्रमm_data	= &saar_da9034_info,
		.irq		= PXA_GPIO_TO_IRQ(mfp_to_gpio(MFP_PIN_GPIO83)),
	पूर्ण,
पूर्ण;

अटल व्योम __init saar_init_i2c(व्योम)
अणु
	pxa_set_i2c_info(शून्य);
	i2c_रेजिस्टर_board_info(0, ARRAY_AND_SIZE(saar_i2c_info));
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम saar_init_i2c(व्योम) अणुपूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_MTD_ONEन_अंकD) || defined(CONFIG_MTD_ONEन_अंकD_MODULE)
अटल काष्ठा mtd_partition saar_onenand_partitions[] = अणु
	अणु
		.name		= "bootloader",
		.offset		= 0,
		.size		= SZ_1M,
		.mask_flags	= MTD_WRITEABLE,
	पूर्ण, अणु
		.name		= "reserved",
		.offset		= MTDPART_OFS_APPEND,
		.size		= SZ_128K,
		.mask_flags	= MTD_WRITEABLE,
	पूर्ण, अणु
		.name		= "reserved",
		.offset		= MTDPART_OFS_APPEND,
		.size		= SZ_8M,
		.mask_flags	= MTD_WRITEABLE,
	पूर्ण, अणु
		.name		= "kernel",
		.offset		= MTDPART_OFS_APPEND,
		.size		= (SZ_2M + SZ_1M),
		.mask_flags	= 0,
	पूर्ण, अणु
		.name		= "filesystem",
		.offset		= MTDPART_OFS_APPEND,
		.size		= SZ_32M + SZ_16M,
		.mask_flags	= 0,
	पूर्ण
पूर्ण;

अटल काष्ठा onenand_platक्रमm_data saar_onenand_info = अणु
	.parts		= saar_onenand_partitions,
	.nr_parts	= ARRAY_SIZE(saar_onenand_partitions),
पूर्ण;

#घोषणा SMC_CS0_PHYS_BASE	(0x10000000)

अटल काष्ठा resource saar_resource_onenand[] = अणु
	[0] = अणु
		.start	= SMC_CS0_PHYS_BASE,
		.end	= SMC_CS0_PHYS_BASE + SZ_1M,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device saar_device_onenand = अणु
	.name		= "onenand-flash",
	.id		= -1,
	.dev		= अणु
		.platक्रमm_data	= &saar_onenand_info,
	पूर्ण,
	.resource	= saar_resource_onenand,
	.num_resources	= ARRAY_SIZE(saar_resource_onenand),
पूर्ण;

अटल व्योम __init saar_init_onenand(व्योम)
अणु
	platक्रमm_device_रेजिस्टर(&saar_device_onenand);
पूर्ण
#अन्यथा
अटल व्योम __init saar_init_onenand(व्योम) अणुपूर्ण
#पूर्ण_अगर

अटल व्योम __init saar_init(व्योम)
अणु
	/* initialize MFP configurations */
	pxa3xx_mfp_config(ARRAY_AND_SIZE(saar_mfp_cfg));

	pxa_set_ffuart_info(शून्य);
	pxa_set_btuart_info(शून्य);
	pxa_set_stuart_info(शून्य);

	platक्रमm_device_रेजिस्टर(&smc91x_device);
	saar_init_onenand();

	saar_init_i2c();
	saar_init_lcd();
पूर्ण

MACHINE_START(SAAR, "PXA930 Handheld Platform (aka SAAR)")
	/* Maपूर्णांकainer: Eric Miao <eric.miao@marvell.com> */
	.atag_offset    = 0x100,
	.map_io         = pxa3xx_map_io,
	.nr_irqs	= PXA_NR_IRQS,
	.init_irq       = pxa3xx_init_irq,
	.handle_irq       = pxa3xx_handle_irq,
	.init_समय	= pxa_समयr_init,
	.init_machine   = saar_init,
	.restart	= pxa_restart,
MACHINE_END
