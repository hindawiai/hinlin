<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * FB driver क्रम the HX8353D LCD Controller
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

#घोषणा DRVNAME "fb_hx8353d"
#घोषणा DEFAULT_GAMMA "50 77 40 08 BF 00 03 0F 00 01 73 00 72 03 B0 0F 08 00 0F"

अटल पूर्णांक init_display(काष्ठा fbtft_par *par)
अणु
	par->fbtftops.reset(par);
	mdelay(150);

	/* SETEXTC */
	ग_लिखो_reg(par, 0xB9, 0xFF, 0x83, 0x53);

	/* RADJ */
	ग_लिखो_reg(par, 0xB0, 0x3C, 0x01);

	/* VCOM */
	ग_लिखो_reg(par, 0xB6, 0x94, 0x6C, 0x50);

	/* PWR */
	ग_लिखो_reg(par, 0xB1, 0x00, 0x01, 0x1B, 0x03, 0x01, 0x08, 0x77, 0x89);

	/* COLMOD */
	ग_लिखो_reg(par, 0x3A, 0x05);

	/* MEM ACCESS */
	ग_लिखो_reg(par, MIPI_DCS_SET_ADDRESS_MODE, 0xC0);

	/* SLPOUT - Sleep out & booster on */
	ग_लिखो_reg(par, MIPI_DCS_EXIT_SLEEP_MODE);
	mdelay(150);

	/* DISPON - Display On */
	ग_लिखो_reg(par, MIPI_DCS_SET_DISPLAY_ON);

	/* RGBSET */
	ग_लिखो_reg(par, MIPI_DCS_WRITE_LUT,
		  0,  2,  4,  6,  8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30,
		32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52, 54, 56, 58, 60, 62,
		 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
		16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
		32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
		48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63,
		 0,  2,  4,  6,  8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30,
		32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52, 54, 56, 58, 60, 62);

	वापस 0;
पूर्ण;

अटल व्योम set_addr_win(काष्ठा fbtft_par *par, पूर्णांक xs, पूर्णांक ys, पूर्णांक xe, पूर्णांक ye)
अणु
	/* column address */
	ग_लिखो_reg(par, 0x2a, xs >> 8, xs & 0xff, xe >> 8, xe & 0xff);

	/* Row address */
	ग_लिखो_reg(par, 0x2b, ys >> 8, ys & 0xff, ye >> 8, ye & 0xff);

	/* memory ग_लिखो */
	ग_लिखो_reg(par, 0x2c);
पूर्ण

#घोषणा my BIT(7)
#घोषणा mx BIT(6)
#घोषणा mv BIT(5)
अटल पूर्णांक set_var(काष्ठा fbtft_par *par)
अणु
	/*
	 * madctl - memory data access control
	 *   rgb/bgr:
	 *   1. mode selection pin srgb
	 *	rgb h/w pin क्रम color filter setting: 0=rgb, 1=bgr
	 *   2. madctl rgb bit
	 *	rgb-bgr order color filter panel: 0=rgb, 1=bgr
	 */
	चयन (par->info->var.rotate) अणु
	हाल 0:
		ग_लिखो_reg(par, MIPI_DCS_SET_ADDRESS_MODE,
			  mx | my | (par->bgr << 3));
		अवरोध;
	हाल 270:
		ग_लिखो_reg(par, MIPI_DCS_SET_ADDRESS_MODE,
			  my | mv | (par->bgr << 3));
		अवरोध;
	हाल 180:
		ग_लिखो_reg(par, MIPI_DCS_SET_ADDRESS_MODE,
			  par->bgr << 3);
		अवरोध;
	हाल 90:
		ग_लिखो_reg(par, MIPI_DCS_SET_ADDRESS_MODE,
			  mx | mv | (par->bgr << 3));
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/* gamma string क्रमmat: */
अटल पूर्णांक set_gamma(काष्ठा fbtft_par *par, u32 *curves)
अणु
	ग_लिखो_reg(par, 0xE0,
		  curves[0], curves[1], curves[2], curves[3],
		  curves[4], curves[5], curves[6], curves[7],
		  curves[8], curves[9], curves[10], curves[11],
		  curves[12], curves[13], curves[14], curves[15],
		  curves[16], curves[17], curves[18]);

	वापस 0;
पूर्ण

अटल काष्ठा fbtft_display display = अणु
	.regwidth = 8,
	.width = 128,
	.height = 160,
	.gamma_num = 1,
	.gamma_len = 19,
	.gamma = DEFAULT_GAMMA,
	.fbtftops = अणु
		.init_display = init_display,
		.set_addr_win = set_addr_win,
		.set_var = set_var,
		.set_gamma = set_gamma,
	पूर्ण,
पूर्ण;

FBTFT_REGISTER_DRIVER(DRVNAME, "himax,hx8353d", &display);

MODULE_ALIAS("spi:" DRVNAME);
MODULE_ALIAS("platform:" DRVNAME);
MODULE_ALIAS("spi:hx8353d");
MODULE_ALIAS("platform:hx8353d");

MODULE_DESCRIPTION("FB driver for the HX8353D LCD Controller");
MODULE_AUTHOR("Petr Olivka");
MODULE_LICENSE("GPL");
