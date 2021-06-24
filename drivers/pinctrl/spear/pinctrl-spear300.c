<शैली गुरु>
/*
 * Driver क्रम the ST Microelectronics SPEAr300 pinmux
 *
 * Copyright (C) 2012 ST Microelectronics
 * Viresh Kumar <vireshk@kernel.org>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश "pinctrl-spear3xx.h"

#घोषणा DRIVER_NAME "spear300-pinmux"

/* addresses */
#घोषणा PMX_CONFIG_REG			0x00
#घोषणा MODE_CONFIG_REG			0x04

/* modes */
#घोषणा न_अंकD_MODE			(1 << 0)
#घोषणा NOR_MODE			(1 << 1)
#घोषणा PHOTO_FRAME_MODE		(1 << 2)
#घोषणा LEND_IP_PHONE_MODE		(1 << 3)
#घोषणा HEND_IP_PHONE_MODE		(1 << 4)
#घोषणा LEND_WIFI_PHONE_MODE		(1 << 5)
#घोषणा HEND_WIFI_PHONE_MODE		(1 << 6)
#घोषणा ATA_PABX_WI2S_MODE		(1 << 7)
#घोषणा ATA_PABX_I2S_MODE		(1 << 8)
#घोषणा CAML_LCDW_MODE			(1 << 9)
#घोषणा CAMU_LCD_MODE			(1 << 10)
#घोषणा CAMU_WLCD_MODE			(1 << 11)
#घोषणा CAML_LCD_MODE			(1 << 12)

अटल काष्ठा spear_pmx_mode pmx_mode_nand = अणु
	.name = "nand",
	.mode = न_अंकD_MODE,
	.reg = MODE_CONFIG_REG,
	.mask = 0x0000000F,
	.val = 0x00,
पूर्ण;

अटल काष्ठा spear_pmx_mode pmx_mode_nor = अणु
	.name = "nor",
	.mode = NOR_MODE,
	.reg = MODE_CONFIG_REG,
	.mask = 0x0000000F,
	.val = 0x01,
पूर्ण;

अटल काष्ठा spear_pmx_mode pmx_mode_photo_frame = अणु
	.name = "photo frame mode",
	.mode = PHOTO_FRAME_MODE,
	.reg = MODE_CONFIG_REG,
	.mask = 0x0000000F,
	.val = 0x02,
पूर्ण;

अटल काष्ठा spear_pmx_mode pmx_mode_lend_ip_phone = अणु
	.name = "lend ip phone mode",
	.mode = LEND_IP_PHONE_MODE,
	.reg = MODE_CONFIG_REG,
	.mask = 0x0000000F,
	.val = 0x03,
पूर्ण;

अटल काष्ठा spear_pmx_mode pmx_mode_hend_ip_phone = अणु
	.name = "hend ip phone mode",
	.mode = HEND_IP_PHONE_MODE,
	.reg = MODE_CONFIG_REG,
	.mask = 0x0000000F,
	.val = 0x04,
पूर्ण;

अटल काष्ठा spear_pmx_mode pmx_mode_lend_wअगरi_phone = अणु
	.name = "lend wifi phone mode",
	.mode = LEND_WIFI_PHONE_MODE,
	.reg = MODE_CONFIG_REG,
	.mask = 0x0000000F,
	.val = 0x05,
पूर्ण;

अटल काष्ठा spear_pmx_mode pmx_mode_hend_wअगरi_phone = अणु
	.name = "hend wifi phone mode",
	.mode = HEND_WIFI_PHONE_MODE,
	.reg = MODE_CONFIG_REG,
	.mask = 0x0000000F,
	.val = 0x06,
पूर्ण;

अटल काष्ठा spear_pmx_mode pmx_mode_ata_pabx_wi2s = अणु
	.name = "ata pabx wi2s mode",
	.mode = ATA_PABX_WI2S_MODE,
	.reg = MODE_CONFIG_REG,
	.mask = 0x0000000F,
	.val = 0x07,
पूर्ण;

अटल काष्ठा spear_pmx_mode pmx_mode_ata_pabx_i2s = अणु
	.name = "ata pabx i2s mode",
	.mode = ATA_PABX_I2S_MODE,
	.reg = MODE_CONFIG_REG,
	.mask = 0x0000000F,
	.val = 0x08,
पूर्ण;

अटल काष्ठा spear_pmx_mode pmx_mode_caml_lcdw = अणु
	.name = "caml lcdw mode",
	.mode = CAML_LCDW_MODE,
	.reg = MODE_CONFIG_REG,
	.mask = 0x0000000F,
	.val = 0x0C,
पूर्ण;

अटल काष्ठा spear_pmx_mode pmx_mode_camu_lcd = अणु
	.name = "camu lcd mode",
	.mode = CAMU_LCD_MODE,
	.reg = MODE_CONFIG_REG,
	.mask = 0x0000000F,
	.val = 0x0D,
पूर्ण;

अटल काष्ठा spear_pmx_mode pmx_mode_camu_wlcd = अणु
	.name = "camu wlcd mode",
	.mode = CAMU_WLCD_MODE,
	.reg = MODE_CONFIG_REG,
	.mask = 0x0000000F,
	.val = 0xE,
पूर्ण;

अटल काष्ठा spear_pmx_mode pmx_mode_caml_lcd = अणु
	.name = "caml lcd mode",
	.mode = CAML_LCD_MODE,
	.reg = MODE_CONFIG_REG,
	.mask = 0x0000000F,
	.val = 0x0F,
पूर्ण;

अटल काष्ठा spear_pmx_mode *spear300_pmx_modes[] = अणु
	&pmx_mode_nand,
	&pmx_mode_nor,
	&pmx_mode_photo_frame,
	&pmx_mode_lend_ip_phone,
	&pmx_mode_hend_ip_phone,
	&pmx_mode_lend_wअगरi_phone,
	&pmx_mode_hend_wअगरi_phone,
	&pmx_mode_ata_pabx_wi2s,
	&pmx_mode_ata_pabx_i2s,
	&pmx_mode_caml_lcdw,
	&pmx_mode_camu_lcd,
	&pmx_mode_camu_wlcd,
	&pmx_mode_caml_lcd,
पूर्ण;

/* fsmc_2chips_pins */
अटल स्थिर अचिन्हित fsmc_2chips_pins[] = अणु 1, 97 पूर्ण;
अटल काष्ठा spear_muxreg fsmc_2chips_muxreg[] = अणु
	अणु
		.reg = PMX_CONFIG_REG,
		.mask = PMX_FIRDA_MASK,
		.val = 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux fsmc_2chips_modemux[] = अणु
	अणु
		.modes = न_अंकD_MODE | NOR_MODE | PHOTO_FRAME_MODE |
			ATA_PABX_WI2S_MODE | ATA_PABX_I2S_MODE,
		.muxregs = fsmc_2chips_muxreg,
		.nmuxregs = ARRAY_SIZE(fsmc_2chips_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup fsmc_2chips_pingroup = अणु
	.name = "fsmc_2chips_grp",
	.pins = fsmc_2chips_pins,
	.npins = ARRAY_SIZE(fsmc_2chips_pins),
	.modemuxs = fsmc_2chips_modemux,
	.nmodemuxs = ARRAY_SIZE(fsmc_2chips_modemux),
पूर्ण;

/* fsmc_4chips_pins */
अटल स्थिर अचिन्हित fsmc_4chips_pins[] = अणु 1, 2, 3, 97 पूर्ण;
अटल काष्ठा spear_muxreg fsmc_4chips_muxreg[] = अणु
	अणु
		.reg = PMX_CONFIG_REG,
		.mask = PMX_FIRDA_MASK | PMX_UART0_MASK,
		.val = 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux fsmc_4chips_modemux[] = अणु
	अणु
		.modes = न_अंकD_MODE | NOR_MODE | PHOTO_FRAME_MODE |
			ATA_PABX_WI2S_MODE | ATA_PABX_I2S_MODE,
		.muxregs = fsmc_4chips_muxreg,
		.nmuxregs = ARRAY_SIZE(fsmc_4chips_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup fsmc_4chips_pingroup = अणु
	.name = "fsmc_4chips_grp",
	.pins = fsmc_4chips_pins,
	.npins = ARRAY_SIZE(fsmc_4chips_pins),
	.modemuxs = fsmc_4chips_modemux,
	.nmodemuxs = ARRAY_SIZE(fsmc_4chips_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर fsmc_grps[] = अणु "fsmc_2chips_grp", "fsmc_4chips_grp"
पूर्ण;
अटल काष्ठा spear_function fsmc_function = अणु
	.name = "fsmc",
	.groups = fsmc_grps,
	.ngroups = ARRAY_SIZE(fsmc_grps),
पूर्ण;

/* clcd_lcdmode_pins */
अटल स्थिर अचिन्हित clcd_lcdmode_pins[] = अणु 49, 50 पूर्ण;
अटल काष्ठा spear_muxreg clcd_lcdmode_muxreg[] = अणु
	अणु
		.reg = PMX_CONFIG_REG,
		.mask = PMX_TIMER_0_1_MASK | PMX_TIMER_2_3_MASK,
		.val = 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux clcd_lcdmode_modemux[] = अणु
	अणु
		.modes = HEND_IP_PHONE_MODE | HEND_WIFI_PHONE_MODE |
			CAMU_LCD_MODE | CAML_LCD_MODE,
		.muxregs = clcd_lcdmode_muxreg,
		.nmuxregs = ARRAY_SIZE(clcd_lcdmode_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup clcd_lcdmode_pingroup = अणु
	.name = "clcd_lcdmode_grp",
	.pins = clcd_lcdmode_pins,
	.npins = ARRAY_SIZE(clcd_lcdmode_pins),
	.modemuxs = clcd_lcdmode_modemux,
	.nmodemuxs = ARRAY_SIZE(clcd_lcdmode_modemux),
पूर्ण;

/* clcd_pभ_शेषe_pins */
अटल स्थिर अचिन्हित clcd_pभ_शेषe_pins[] = अणु 47, 48, 49, 50 पूर्ण;
अटल काष्ठा spear_muxreg clcd_pभ_शेषe_muxreg[] = अणु
	अणु
		.reg = PMX_CONFIG_REG,
		.mask = PMX_TIMER_2_3_MASK,
		.val = 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux clcd_pभ_शेषe_modemux[] = अणु
	अणु
		.modes = PHOTO_FRAME_MODE,
		.muxregs = clcd_pभ_शेषe_muxreg,
		.nmuxregs = ARRAY_SIZE(clcd_pभ_शेषe_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup clcd_pभ_शेषe_pingroup = अणु
	.name = "clcd_pfmode_grp",
	.pins = clcd_pभ_शेषe_pins,
	.npins = ARRAY_SIZE(clcd_pभ_शेषe_pins),
	.modemuxs = clcd_pभ_शेषe_modemux,
	.nmodemuxs = ARRAY_SIZE(clcd_pभ_शेषe_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर clcd_grps[] = अणु "clcd_lcdmode_grp", "clcd_pfmode_grp"
पूर्ण;
अटल काष्ठा spear_function clcd_function = अणु
	.name = "clcd",
	.groups = clcd_grps,
	.ngroups = ARRAY_SIZE(clcd_grps),
पूर्ण;

/* tdm_pins */
अटल स्थिर अचिन्हित tdm_pins[] = अणु 34, 35, 36, 37, 38 पूर्ण;
अटल काष्ठा spear_muxreg tdm_muxreg[] = अणु
	अणु
		.reg = PMX_CONFIG_REG,
		.mask = PMX_UART0_MODEM_MASK | PMX_SSP_CS_MASK,
		.val = 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux tdm_modemux[] = अणु
	अणु
		.modes = PHOTO_FRAME_MODE | LEND_IP_PHONE_MODE |
			HEND_IP_PHONE_MODE | LEND_WIFI_PHONE_MODE
			| HEND_WIFI_PHONE_MODE | ATA_PABX_WI2S_MODE
			| ATA_PABX_I2S_MODE | CAML_LCDW_MODE | CAMU_LCD_MODE
			| CAMU_WLCD_MODE | CAML_LCD_MODE,
		.muxregs = tdm_muxreg,
		.nmuxregs = ARRAY_SIZE(tdm_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup tdm_pingroup = अणु
	.name = "tdm_grp",
	.pins = tdm_pins,
	.npins = ARRAY_SIZE(tdm_pins),
	.modemuxs = tdm_modemux,
	.nmodemuxs = ARRAY_SIZE(tdm_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर tdm_grps[] = अणु "tdm_grp" पूर्ण;
अटल काष्ठा spear_function tdm_function = अणु
	.name = "tdm",
	.groups = tdm_grps,
	.ngroups = ARRAY_SIZE(tdm_grps),
पूर्ण;

/* i2c_clk_pins */
अटल स्थिर अचिन्हित i2c_clk_pins[] = अणु 45, 46, 47, 48 पूर्ण;
अटल काष्ठा spear_muxreg i2c_clk_muxreg[] = अणु
	अणु
		.reg = PMX_CONFIG_REG,
		.mask = PMX_TIMER_0_1_MASK | PMX_TIMER_2_3_MASK,
		.val = 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux i2c_clk_modemux[] = अणु
	अणु
		.modes = LEND_IP_PHONE_MODE | HEND_IP_PHONE_MODE |
			LEND_WIFI_PHONE_MODE | HEND_WIFI_PHONE_MODE |
			ATA_PABX_WI2S_MODE | ATA_PABX_I2S_MODE | CAML_LCDW_MODE
			| CAML_LCD_MODE,
		.muxregs = i2c_clk_muxreg,
		.nmuxregs = ARRAY_SIZE(i2c_clk_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup i2c_clk_pingroup = अणु
	.name = "i2c_clk_grp_grp",
	.pins = i2c_clk_pins,
	.npins = ARRAY_SIZE(i2c_clk_pins),
	.modemuxs = i2c_clk_modemux,
	.nmodemuxs = ARRAY_SIZE(i2c_clk_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर i2c_grps[] = अणु "i2c_clk_grp" पूर्ण;
अटल काष्ठा spear_function i2c_function = अणु
	.name = "i2c1",
	.groups = i2c_grps,
	.ngroups = ARRAY_SIZE(i2c_grps),
पूर्ण;

/* caml_pins */
अटल स्थिर अचिन्हित caml_pins[] = अणु 12, 13, 14, 15, 16, 17, 18, 19, 20, 21 पूर्ण;
अटल काष्ठा spear_muxreg caml_muxreg[] = अणु
	अणु
		.reg = PMX_CONFIG_REG,
		.mask = PMX_MII_MASK,
		.val = 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux caml_modemux[] = अणु
	अणु
		.modes = CAML_LCDW_MODE | CAML_LCD_MODE,
		.muxregs = caml_muxreg,
		.nmuxregs = ARRAY_SIZE(caml_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup caml_pingroup = अणु
	.name = "caml_grp",
	.pins = caml_pins,
	.npins = ARRAY_SIZE(caml_pins),
	.modemuxs = caml_modemux,
	.nmodemuxs = ARRAY_SIZE(caml_modemux),
पूर्ण;

/* camu_pins */
अटल स्थिर अचिन्हित camu_pins[] = अणु 16, 17, 18, 19, 20, 21, 45, 46, 47, 48 पूर्ण;
अटल काष्ठा spear_muxreg camu_muxreg[] = अणु
	अणु
		.reg = PMX_CONFIG_REG,
		.mask = PMX_TIMER_0_1_MASK | PMX_TIMER_2_3_MASK | PMX_MII_MASK,
		.val = 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux camu_modemux[] = अणु
	अणु
		.modes = CAMU_LCD_MODE | CAMU_WLCD_MODE,
		.muxregs = camu_muxreg,
		.nmuxregs = ARRAY_SIZE(camu_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup camu_pingroup = अणु
	.name = "camu_grp",
	.pins = camu_pins,
	.npins = ARRAY_SIZE(camu_pins),
	.modemuxs = camu_modemux,
	.nmodemuxs = ARRAY_SIZE(camu_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर cam_grps[] = अणु "caml_grp", "camu_grp" पूर्ण;
अटल काष्ठा spear_function cam_function = अणु
	.name = "cam",
	.groups = cam_grps,
	.ngroups = ARRAY_SIZE(cam_grps),
पूर्ण;

/* dac_pins */
अटल स्थिर अचिन्हित dac_pins[] = अणु 43, 44 पूर्ण;
अटल काष्ठा spear_muxreg dac_muxreg[] = अणु
	अणु
		.reg = PMX_CONFIG_REG,
		.mask = PMX_TIMER_0_1_MASK,
		.val = 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux dac_modemux[] = अणु
	अणु
		.modes = ATA_PABX_I2S_MODE | CAML_LCDW_MODE | CAMU_LCD_MODE
			| CAMU_WLCD_MODE | CAML_LCD_MODE,
		.muxregs = dac_muxreg,
		.nmuxregs = ARRAY_SIZE(dac_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup dac_pingroup = अणु
	.name = "dac_grp",
	.pins = dac_pins,
	.npins = ARRAY_SIZE(dac_pins),
	.modemuxs = dac_modemux,
	.nmodemuxs = ARRAY_SIZE(dac_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर dac_grps[] = अणु "dac_grp" पूर्ण;
अटल काष्ठा spear_function dac_function = अणु
	.name = "dac",
	.groups = dac_grps,
	.ngroups = ARRAY_SIZE(dac_grps),
पूर्ण;

/* i2s_pins */
अटल स्थिर अचिन्हित i2s_pins[] = अणु 39, 40, 41, 42 पूर्ण;
अटल काष्ठा spear_muxreg i2s_muxreg[] = अणु
	अणु
		.reg = PMX_CONFIG_REG,
		.mask = PMX_UART0_MODEM_MASK,
		.val = 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux i2s_modemux[] = अणु
	अणु
		.modes = LEND_IP_PHONE_MODE | HEND_IP_PHONE_MODE
			| LEND_WIFI_PHONE_MODE | HEND_WIFI_PHONE_MODE |
			ATA_PABX_I2S_MODE | CAML_LCDW_MODE | CAMU_LCD_MODE
			| CAMU_WLCD_MODE | CAML_LCD_MODE,
		.muxregs = i2s_muxreg,
		.nmuxregs = ARRAY_SIZE(i2s_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup i2s_pingroup = अणु
	.name = "i2s_grp",
	.pins = i2s_pins,
	.npins = ARRAY_SIZE(i2s_pins),
	.modemuxs = i2s_modemux,
	.nmodemuxs = ARRAY_SIZE(i2s_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर i2s_grps[] = अणु "i2s_grp" पूर्ण;
अटल काष्ठा spear_function i2s_function = अणु
	.name = "i2s",
	.groups = i2s_grps,
	.ngroups = ARRAY_SIZE(i2s_grps),
पूर्ण;

/* sdhci_4bit_pins */
अटल स्थिर अचिन्हित sdhci_4bit_pins[] = अणु 28, 29, 30, 31, 32, 33 पूर्ण;
अटल काष्ठा spear_muxreg sdhci_4bit_muxreg[] = अणु
	अणु
		.reg = PMX_CONFIG_REG,
		.mask = PMX_GPIO_PIN0_MASK | PMX_GPIO_PIN1_MASK |
			PMX_GPIO_PIN2_MASK | PMX_GPIO_PIN3_MASK |
			PMX_GPIO_PIN4_MASK | PMX_GPIO_PIN5_MASK,
		.val = 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux sdhci_4bit_modemux[] = अणु
	अणु
		.modes = PHOTO_FRAME_MODE | LEND_IP_PHONE_MODE |
			HEND_IP_PHONE_MODE | LEND_WIFI_PHONE_MODE |
			HEND_WIFI_PHONE_MODE | CAML_LCDW_MODE | CAMU_LCD_MODE |
			CAMU_WLCD_MODE | CAML_LCD_MODE | ATA_PABX_WI2S_MODE,
		.muxregs = sdhci_4bit_muxreg,
		.nmuxregs = ARRAY_SIZE(sdhci_4bit_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup sdhci_4bit_pingroup = अणु
	.name = "sdhci_4bit_grp",
	.pins = sdhci_4bit_pins,
	.npins = ARRAY_SIZE(sdhci_4bit_pins),
	.modemuxs = sdhci_4bit_modemux,
	.nmodemuxs = ARRAY_SIZE(sdhci_4bit_modemux),
पूर्ण;

/* sdhci_8bit_pins */
अटल स्थिर अचिन्हित sdhci_8bit_pins[] = अणु 24, 25, 26, 27, 28, 29, 30, 31, 32,
	33 पूर्ण;
अटल काष्ठा spear_muxreg sdhci_8bit_muxreg[] = अणु
	अणु
		.reg = PMX_CONFIG_REG,
		.mask = PMX_GPIO_PIN0_MASK | PMX_GPIO_PIN1_MASK |
			PMX_GPIO_PIN2_MASK | PMX_GPIO_PIN3_MASK |
			PMX_GPIO_PIN4_MASK | PMX_GPIO_PIN5_MASK | PMX_MII_MASK,
		.val = 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux sdhci_8bit_modemux[] = अणु
	अणु
		.modes = PHOTO_FRAME_MODE | LEND_IP_PHONE_MODE |
			HEND_IP_PHONE_MODE | LEND_WIFI_PHONE_MODE |
			HEND_WIFI_PHONE_MODE | CAML_LCDW_MODE | CAMU_LCD_MODE |
			CAMU_WLCD_MODE | CAML_LCD_MODE,
		.muxregs = sdhci_8bit_muxreg,
		.nmuxregs = ARRAY_SIZE(sdhci_8bit_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup sdhci_8bit_pingroup = अणु
	.name = "sdhci_8bit_grp",
	.pins = sdhci_8bit_pins,
	.npins = ARRAY_SIZE(sdhci_8bit_pins),
	.modemuxs = sdhci_8bit_modemux,
	.nmodemuxs = ARRAY_SIZE(sdhci_8bit_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर sdhci_grps[] = अणु "sdhci_4bit_grp", "sdhci_8bit_grp" पूर्ण;
अटल काष्ठा spear_function sdhci_function = अणु
	.name = "sdhci",
	.groups = sdhci_grps,
	.ngroups = ARRAY_SIZE(sdhci_grps),
पूर्ण;

/* gpio1_0_to_3_pins */
अटल स्थिर अचिन्हित gpio1_0_to_3_pins[] = अणु 39, 40, 41, 42 पूर्ण;
अटल काष्ठा spear_muxreg gpio1_0_to_3_muxreg[] = अणु
	अणु
		.reg = PMX_CONFIG_REG,
		.mask = PMX_UART0_MODEM_MASK,
		.val = 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux gpio1_0_to_3_modemux[] = अणु
	अणु
		.modes = PHOTO_FRAME_MODE,
		.muxregs = gpio1_0_to_3_muxreg,
		.nmuxregs = ARRAY_SIZE(gpio1_0_to_3_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup gpio1_0_to_3_pingroup = अणु
	.name = "gpio1_0_to_3_grp",
	.pins = gpio1_0_to_3_pins,
	.npins = ARRAY_SIZE(gpio1_0_to_3_pins),
	.modemuxs = gpio1_0_to_3_modemux,
	.nmodemuxs = ARRAY_SIZE(gpio1_0_to_3_modemux),
पूर्ण;

/* gpio1_4_to_7_pins */
अटल स्थिर अचिन्हित gpio1_4_to_7_pins[] = अणु 43, 44, 45, 46 पूर्ण;

अटल काष्ठा spear_muxreg gpio1_4_to_7_muxreg[] = अणु
	अणु
		.reg = PMX_CONFIG_REG,
		.mask = PMX_TIMER_0_1_MASK | PMX_TIMER_2_3_MASK,
		.val = 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux gpio1_4_to_7_modemux[] = अणु
	अणु
		.modes = PHOTO_FRAME_MODE,
		.muxregs = gpio1_4_to_7_muxreg,
		.nmuxregs = ARRAY_SIZE(gpio1_4_to_7_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup gpio1_4_to_7_pingroup = अणु
	.name = "gpio1_4_to_7_grp",
	.pins = gpio1_4_to_7_pins,
	.npins = ARRAY_SIZE(gpio1_4_to_7_pins),
	.modemuxs = gpio1_4_to_7_modemux,
	.nmodemuxs = ARRAY_SIZE(gpio1_4_to_7_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर gpio1_grps[] = अणु "gpio1_0_to_3_grp", "gpio1_4_to_7_grp"
पूर्ण;
अटल काष्ठा spear_function gpio1_function = अणु
	.name = "gpio1",
	.groups = gpio1_grps,
	.ngroups = ARRAY_SIZE(gpio1_grps),
पूर्ण;

/* pingroups */
अटल काष्ठा spear_pingroup *spear300_pingroups[] = अणु
	SPEAR3XX_COMMON_PINGROUPS,
	&fsmc_2chips_pingroup,
	&fsmc_4chips_pingroup,
	&clcd_lcdmode_pingroup,
	&clcd_pभ_शेषe_pingroup,
	&tdm_pingroup,
	&i2c_clk_pingroup,
	&caml_pingroup,
	&camu_pingroup,
	&dac_pingroup,
	&i2s_pingroup,
	&sdhci_4bit_pingroup,
	&sdhci_8bit_pingroup,
	&gpio1_0_to_3_pingroup,
	&gpio1_4_to_7_pingroup,
पूर्ण;

/* functions */
अटल काष्ठा spear_function *spear300_functions[] = अणु
	SPEAR3XX_COMMON_FUNCTIONS,
	&fsmc_function,
	&clcd_function,
	&tdm_function,
	&i2c_function,
	&cam_function,
	&dac_function,
	&i2s_function,
	&sdhci_function,
	&gpio1_function,
पूर्ण;

अटल स्थिर काष्ठा of_device_id spear300_pinctrl_of_match[] = अणु
	अणु
		.compatible = "st,spear300-pinmux",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक spear300_pinctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	spear3xx_machdata.groups = spear300_pingroups;
	spear3xx_machdata.ngroups = ARRAY_SIZE(spear300_pingroups);
	spear3xx_machdata.functions = spear300_functions;
	spear3xx_machdata.nfunctions = ARRAY_SIZE(spear300_functions);
	spear3xx_machdata.gpio_pingroups = शून्य;
	spear3xx_machdata.ngpio_pingroups = 0;

	spear3xx_machdata.modes_supported = true;
	spear3xx_machdata.pmx_modes = spear300_pmx_modes;
	spear3xx_machdata.npmx_modes = ARRAY_SIZE(spear300_pmx_modes);

	pmx_init_addr(&spear3xx_machdata, PMX_CONFIG_REG);

	वापस spear_pinctrl_probe(pdev, &spear3xx_machdata);
पूर्ण

अटल काष्ठा platक्रमm_driver spear300_pinctrl_driver = अणु
	.driver = अणु
		.name = DRIVER_NAME,
		.of_match_table = spear300_pinctrl_of_match,
	पूर्ण,
	.probe = spear300_pinctrl_probe,
पूर्ण;

अटल पूर्णांक __init spear300_pinctrl_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&spear300_pinctrl_driver);
पूर्ण
arch_initcall(spear300_pinctrl_init);
