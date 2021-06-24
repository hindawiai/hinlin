<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * FB driver क्रम the ILI9481 LCD Controller
 *
 * Copyright (c) 2014 Petr Olivka
 * Copyright (c) 2013 Noralf Tronnes
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <video/mipi_display.h>

#समावेश "fbtft.h"

#घोषणा DRVNAME	"fb_ili9481"
#घोषणा WIDTH		320
#घोषणा HEIGHT		480

अटल स्थिर s16 शेष_init_sequence[] = अणु
	/* SLP_OUT - Sleep out */
	-1, MIPI_DCS_EXIT_SLEEP_MODE,
	-2, 50,
	/* Power setting */
	-1, 0xD0, 0x07, 0x42, 0x18,
	/* VCOM */
	-1, 0xD1, 0x00, 0x07, 0x10,
	/* Power setting क्रम norm. mode */
	-1, 0xD2, 0x01, 0x02,
	/* Panel driving setting */
	-1, 0xC0, 0x10, 0x3B, 0x00, 0x02, 0x11,
	/* Frame rate & inv. */
	-1, 0xC5, 0x03,
	/* Pixel क्रमmat */
	-1, MIPI_DCS_SET_PIXEL_FORMAT, 0x55,
	/* Gamma */
	-1, 0xC8, 0x00, 0x32, 0x36, 0x45, 0x06, 0x16,
		  0x37, 0x75, 0x77, 0x54, 0x0C, 0x00,
	/* DISP_ON */
	-1, MIPI_DCS_SET_DISPLAY_ON,
	-3
पूर्ण;

अटल व्योम set_addr_win(काष्ठा fbtft_par *par, पूर्णांक xs, पूर्णांक ys, पूर्णांक xe, पूर्णांक ye)
अणु
	ग_लिखो_reg(par, MIPI_DCS_SET_COLUMN_ADDRESS,
		  xs >> 8, xs & 0xff, xe >> 8, xe & 0xff);

	ग_लिखो_reg(par, MIPI_DCS_SET_PAGE_ADDRESS,
		  ys >> 8, ys & 0xff, ye >> 8, ye & 0xff);

	ग_लिखो_reg(par, MIPI_DCS_WRITE_MEMORY_START);
पूर्ण

#घोषणा HFLIP 0x01
#घोषणा VFLIP 0x02
#घोषणा ROW_X_COL 0x20
अटल पूर्णांक set_var(काष्ठा fbtft_par *par)
अणु
	चयन (par->info->var.rotate) अणु
	हाल 270:
		ग_लिखो_reg(par, MIPI_DCS_SET_ADDRESS_MODE,
			  ROW_X_COL | HFLIP | VFLIP | (par->bgr << 3));
		अवरोध;
	हाल 180:
		ग_लिखो_reg(par, MIPI_DCS_SET_ADDRESS_MODE,
			  VFLIP | (par->bgr << 3));
		अवरोध;
	हाल 90:
		ग_लिखो_reg(par, MIPI_DCS_SET_ADDRESS_MODE,
			  ROW_X_COL | (par->bgr << 3));
		अवरोध;
	शेष:
		ग_लिखो_reg(par, MIPI_DCS_SET_ADDRESS_MODE,
			  HFLIP | (par->bgr << 3));
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा fbtft_display display = अणु
	.regwidth = 8,
	.width = WIDTH,
	.height = HEIGHT,
	.init_sequence = शेष_init_sequence,
	.fbtftops = अणु
		.set_addr_win = set_addr_win,
		.set_var = set_var,
	पूर्ण,
पूर्ण;

FBTFT_REGISTER_DRIVER(DRVNAME, "ilitek,ili9481", &display);

MODULE_ALIAS("spi:" DRVNAME);
MODULE_ALIAS("platform:" DRVNAME);
MODULE_ALIAS("spi:ili9481");
MODULE_ALIAS("platform:ili9481");

MODULE_DESCRIPTION("FB driver for the ILI9481 LCD Controller");
MODULE_AUTHOR("Petr Olivka");
MODULE_LICENSE("GPL");
