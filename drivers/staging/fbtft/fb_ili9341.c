<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * FB driver क्रम the ILI9341 LCD display controller
 *
 * This display uses 9-bit SPI: Data/Command bit + 8 data bits
 * For platक्रमms that करोesn't support 9-bit, the driver is capable
 * of emulating this using 8-bit transfer.
 * This is करोne by transferring eight 9-bit words in 9 bytes.
 *
 * Copyright (C) 2013 Christian Vogelgsang
 * Based on adafruit22fb.c by Noralf Tronnes
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <video/mipi_display.h>

#समावेश "fbtft.h"

#घोषणा DRVNAME		"fb_ili9341"
#घोषणा WIDTH		240
#घोषणा HEIGHT		320
#घोषणा TXBUFLEN	(4 * PAGE_SIZE)
#घोषणा DEFAULT_GAMMA	"1F 1A 18 0A 0F 06 45 87 32 0A 07 02 07 05 00\n" \
			"00 25 27 05 10 09 3A 78 4D 05 18 0D 38 3A 1F"

अटल पूर्णांक init_display(काष्ठा fbtft_par *par)
अणु
	par->fbtftops.reset(par);

	/* startup sequence क्रम MI0283QT-9A */
	ग_लिखो_reg(par, MIPI_DCS_SOFT_RESET);
	mdelay(5);
	ग_लिखो_reg(par, MIPI_DCS_SET_DISPLAY_OFF);
	/* --------------------------------------------------------- */
	ग_लिखो_reg(par, 0xCF, 0x00, 0x83, 0x30);
	ग_लिखो_reg(par, 0xED, 0x64, 0x03, 0x12, 0x81);
	ग_लिखो_reg(par, 0xE8, 0x85, 0x01, 0x79);
	ग_लिखो_reg(par, 0xCB, 0x39, 0X2C, 0x00, 0x34, 0x02);
	ग_लिखो_reg(par, 0xF7, 0x20);
	ग_लिखो_reg(par, 0xEA, 0x00, 0x00);
	/* ------------घातer control-------------------------------- */
	ग_लिखो_reg(par, 0xC0, 0x26);
	ग_लिखो_reg(par, 0xC1, 0x11);
	/* ------------VCOM --------- */
	ग_लिखो_reg(par, 0xC5, 0x35, 0x3E);
	ग_लिखो_reg(par, 0xC7, 0xBE);
	/* ------------memory access control------------------------ */
	ग_लिखो_reg(par, MIPI_DCS_SET_PIXEL_FORMAT, 0x55); /* 16bit pixel */
	/* ------------frame rate----------------------------------- */
	ग_लिखो_reg(par, 0xB1, 0x00, 0x1B);
	/* ------------Gamma---------------------------------------- */
	/* ग_लिखो_reg(par, 0xF2, 0x08); */ /* Gamma Function Disable */
	ग_लिखो_reg(par, MIPI_DCS_SET_GAMMA_CURVE, 0x01);
	/* ------------display-------------------------------------- */
	ग_लिखो_reg(par, 0xB7, 0x07); /* entry mode set */
	ग_लिखो_reg(par, 0xB6, 0x0A, 0x82, 0x27, 0x00);
	ग_लिखो_reg(par, MIPI_DCS_EXIT_SLEEP_MODE);
	mdelay(100);
	ग_लिखो_reg(par, MIPI_DCS_SET_DISPLAY_ON);
	mdelay(20);

	वापस 0;
पूर्ण

अटल व्योम set_addr_win(काष्ठा fbtft_par *par, पूर्णांक xs, पूर्णांक ys, पूर्णांक xe, पूर्णांक ye)
अणु
	ग_लिखो_reg(par, MIPI_DCS_SET_COLUMN_ADDRESS,
		  (xs >> 8) & 0xFF, xs & 0xFF, (xe >> 8) & 0xFF, xe & 0xFF);

	ग_लिखो_reg(par, MIPI_DCS_SET_PAGE_ADDRESS,
		  (ys >> 8) & 0xFF, ys & 0xFF, (ye >> 8) & 0xFF, ye & 0xFF);

	ग_लिखो_reg(par, MIPI_DCS_WRITE_MEMORY_START);
पूर्ण

#घोषणा MEM_Y   BIT(7) /* MY row address order */
#घोषणा MEM_X   BIT(6) /* MX column address order */
#घोषणा MEM_V   BIT(5) /* MV row / column exchange */
#घोषणा MEM_L   BIT(4) /* ML vertical refresh order */
#घोषणा MEM_H   BIT(2) /* MH horizontal refresh order */
#घोषणा MEM_BGR (3) /* RGB-BGR Order */
अटल पूर्णांक set_var(काष्ठा fbtft_par *par)
अणु
	चयन (par->info->var.rotate) अणु
	हाल 0:
		ग_लिखो_reg(par, MIPI_DCS_SET_ADDRESS_MODE,
			  MEM_X | (par->bgr << MEM_BGR));
		अवरोध;
	हाल 270:
		ग_लिखो_reg(par, MIPI_DCS_SET_ADDRESS_MODE,
			  MEM_V | MEM_L | (par->bgr << MEM_BGR));
		अवरोध;
	हाल 180:
		ग_लिखो_reg(par, MIPI_DCS_SET_ADDRESS_MODE,
			  MEM_Y | (par->bgr << MEM_BGR));
		अवरोध;
	हाल 90:
		ग_लिखो_reg(par, MIPI_DCS_SET_ADDRESS_MODE,
			  MEM_Y | MEM_X | MEM_V | (par->bgr << MEM_BGR));
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Gamma string क्रमmat:
 *  Positive: Par1 Par2 [...] Par15
 *  Negative: Par1 Par2 [...] Par15
 */
#घोषणा CURVE(num, idx)  curves[(num) * par->gamma.num_values + (idx)]
अटल पूर्णांक set_gamma(काष्ठा fbtft_par *par, u32 *curves)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < par->gamma.num_curves; i++)
		ग_लिखो_reg(par, 0xE0 + i,
			  CURVE(i, 0), CURVE(i, 1), CURVE(i, 2),
			  CURVE(i, 3), CURVE(i, 4), CURVE(i, 5),
			  CURVE(i, 6), CURVE(i, 7), CURVE(i, 8),
			  CURVE(i, 9), CURVE(i, 10), CURVE(i, 11),
			  CURVE(i, 12), CURVE(i, 13), CURVE(i, 14));

	वापस 0;
पूर्ण

#अघोषित CURVE

अटल काष्ठा fbtft_display display = अणु
	.regwidth = 8,
	.width = WIDTH,
	.height = HEIGHT,
	.txbuflen = TXBUFLEN,
	.gamma_num = 2,
	.gamma_len = 15,
	.gamma = DEFAULT_GAMMA,
	.fbtftops = अणु
		.init_display = init_display,
		.set_addr_win = set_addr_win,
		.set_var = set_var,
		.set_gamma = set_gamma,
	पूर्ण,
पूर्ण;

FBTFT_REGISTER_DRIVER(DRVNAME, "ilitek,ili9341", &display);

MODULE_ALIAS("spi:" DRVNAME);
MODULE_ALIAS("platform:" DRVNAME);
MODULE_ALIAS("spi:ili9341");
MODULE_ALIAS("platform:ili9341");

MODULE_DESCRIPTION("FB driver for the ILI9341 LCD display controller");
MODULE_AUTHOR("Christian Vogelgsang");
MODULE_LICENSE("GPL");
