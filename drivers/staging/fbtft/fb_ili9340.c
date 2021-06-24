<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * FB driver क्रम the ILI9340 LCD Controller
 *
 * Copyright (C) 2013 Noralf Tronnes
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/delay.h>
#समावेश <video/mipi_display.h>

#समावेश "fbtft.h"

#घोषणा DRVNAME		"fb_ili9340"
#घोषणा WIDTH		240
#घोषणा HEIGHT		320

/* Init sequence taken from: Arduino Library क्रम the Adafruit 2.2" display */
अटल पूर्णांक init_display(काष्ठा fbtft_par *par)
अणु
	par->fbtftops.reset(par);

	ग_लिखो_reg(par, 0xEF, 0x03, 0x80, 0x02);
	ग_लिखो_reg(par, 0xCF, 0x00, 0XC1, 0X30);
	ग_लिखो_reg(par, 0xED, 0x64, 0x03, 0X12, 0X81);
	ग_लिखो_reg(par, 0xE8, 0x85, 0x00, 0x78);
	ग_लिखो_reg(par, 0xCB, 0x39, 0x2C, 0x00, 0x34, 0x02);
	ग_लिखो_reg(par, 0xF7, 0x20);
	ग_लिखो_reg(par, 0xEA, 0x00, 0x00);

	/* Power Control 1 */
	ग_लिखो_reg(par, 0xC0, 0x23);

	/* Power Control 2 */
	ग_लिखो_reg(par, 0xC1, 0x10);

	/* VCOM Control 1 */
	ग_लिखो_reg(par, 0xC5, 0x3e, 0x28);

	/* VCOM Control 2 */
	ग_लिखो_reg(par, 0xC7, 0x86);

	/* COLMOD: Pixel Format Set */
	/* 16 bits/pixel */
	ग_लिखो_reg(par, MIPI_DCS_SET_PIXEL_FORMAT, 0x55);

	/* Frame Rate Control */
	/* Division ratio = fosc, Frame Rate = 79Hz */
	ग_लिखो_reg(par, 0xB1, 0x00, 0x18);

	/* Display Function Control */
	ग_लिखो_reg(par, 0xB6, 0x08, 0x82, 0x27);

	/* Gamma Function Disable */
	ग_लिखो_reg(par, 0xF2, 0x00);

	/* Gamma curve selection */
	ग_लिखो_reg(par, MIPI_DCS_SET_GAMMA_CURVE, 0x01);

	/* Positive Gamma Correction */
	ग_लिखो_reg(par, 0xE0,
		  0x0F, 0x31, 0x2B, 0x0C, 0x0E, 0x08, 0x4E, 0xF1,
		  0x37, 0x07, 0x10, 0x03, 0x0E, 0x09, 0x00);

	/* Negative Gamma Correction */
	ग_लिखो_reg(par, 0xE1,
		  0x00, 0x0E, 0x14, 0x03, 0x11, 0x07, 0x31, 0xC1,
		  0x48, 0x08, 0x0F, 0x0C, 0x31, 0x36, 0x0F);

	ग_लिखो_reg(par, MIPI_DCS_EXIT_SLEEP_MODE);

	mdelay(120);

	ग_लिखो_reg(par, MIPI_DCS_SET_DISPLAY_ON);

	वापस 0;
पूर्ण

अटल व्योम set_addr_win(काष्ठा fbtft_par *par, पूर्णांक xs, पूर्णांक ys, पूर्णांक xe, पूर्णांक ye)
अणु
	ग_लिखो_reg(par, MIPI_DCS_SET_COLUMN_ADDRESS,
		  xs >> 8, xs & 0xFF, xe >> 8, xe & 0xFF);

	ग_लिखो_reg(par, MIPI_DCS_SET_PAGE_ADDRESS,
		  ys >> 8, ys & 0xFF, ye >> 8, ye & 0xFF);

	ग_लिखो_reg(par, MIPI_DCS_WRITE_MEMORY_START);
पूर्ण

#घोषणा ILI9340_MADCTL_MV  0x20
#घोषणा ILI9340_MADCTL_MX  0x40
#घोषणा ILI9340_MADCTL_MY  0x80
अटल पूर्णांक set_var(काष्ठा fbtft_par *par)
अणु
	u8 val;

	चयन (par->info->var.rotate) अणु
	हाल 270:
		val = ILI9340_MADCTL_MV;
		अवरोध;
	हाल 180:
		val = ILI9340_MADCTL_MY;
		अवरोध;
	हाल 90:
		val = ILI9340_MADCTL_MV | ILI9340_MADCTL_MY | ILI9340_MADCTL_MX;
		अवरोध;
	शेष:
		val = ILI9340_MADCTL_MX;
		अवरोध;
	पूर्ण
	/* Memory Access Control  */
	ग_लिखो_reg(par, MIPI_DCS_SET_ADDRESS_MODE, val | (par->bgr << 3));

	वापस 0;
पूर्ण

अटल काष्ठा fbtft_display display = अणु
	.regwidth = 8,
	.width = WIDTH,
	.height = HEIGHT,
	.fbtftops = अणु
		.init_display = init_display,
		.set_addr_win = set_addr_win,
		.set_var = set_var,
	पूर्ण,
पूर्ण;

FBTFT_REGISTER_DRIVER(DRVNAME, "ilitek,ili9340", &display);

MODULE_ALIAS("spi:" DRVNAME);
MODULE_ALIAS("platform:" DRVNAME);
MODULE_ALIAS("spi:ili9340");
MODULE_ALIAS("platform:ili9340");

MODULE_DESCRIPTION("FB driver for the ILI9340 LCD Controller");
MODULE_AUTHOR("Noralf Tronnes");
MODULE_LICENSE("GPL");
