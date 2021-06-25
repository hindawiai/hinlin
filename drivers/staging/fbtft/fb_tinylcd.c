<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Custom FB driver क्रम tinylcd.com display
 *
 * Copyright (C) 2013 Noralf Tronnes
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <video/mipi_display.h>

#समावेश "fbtft.h"

#घोषणा DRVNAME		"fb_tinylcd"
#घोषणा WIDTH		320
#घोषणा HEIGHT		480

अटल पूर्णांक init_display(काष्ठा fbtft_par *par)
अणु
	par->fbtftops.reset(par);

	ग_लिखो_reg(par, 0xB0, 0x80);
	ग_लिखो_reg(par, 0xC0, 0x0A, 0x0A);
	ग_लिखो_reg(par, 0xC1, 0x45, 0x07);
	ग_लिखो_reg(par, 0xC2, 0x33);
	ग_लिखो_reg(par, 0xC5, 0x00, 0x42, 0x80);
	ग_लिखो_reg(par, 0xB1, 0xD0, 0x11);
	ग_लिखो_reg(par, 0xB4, 0x02);
	ग_लिखो_reg(par, 0xB6, 0x00, 0x22, 0x3B);
	ग_लिखो_reg(par, 0xB7, 0x07);
	ग_लिखो_reg(par, MIPI_DCS_SET_ADDRESS_MODE, 0x58);
	ग_लिखो_reg(par, 0xF0, 0x36, 0xA5, 0xD3);
	ग_लिखो_reg(par, 0xE5, 0x80);
	ग_लिखो_reg(par, 0xE5, 0x01);
	ग_लिखो_reg(par, 0xB3, 0x00);
	ग_लिखो_reg(par, 0xE5, 0x00);
	ग_लिखो_reg(par, 0xF0, 0x36, 0xA5, 0x53);
	ग_लिखो_reg(par, 0xE0, 0x00, 0x35, 0x33, 0x00, 0x00, 0x00,
		       0x00, 0x35, 0x33, 0x00, 0x00, 0x00);
	ग_लिखो_reg(par, MIPI_DCS_SET_PIXEL_FORMAT, 0x55);
	ग_लिखो_reg(par, MIPI_DCS_EXIT_SLEEP_MODE);
	udelay(250);
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

अटल पूर्णांक set_var(काष्ठा fbtft_par *par)
अणु
	चयन (par->info->var.rotate) अणु
	हाल 270:
		ग_लिखो_reg(par, 0xB6, 0x00, 0x02, 0x3B);
		ग_लिखो_reg(par, MIPI_DCS_SET_ADDRESS_MODE, 0x28);
		अवरोध;
	हाल 180:
		ग_लिखो_reg(par, 0xB6, 0x00, 0x22, 0x3B);
		ग_लिखो_reg(par, MIPI_DCS_SET_ADDRESS_MODE, 0x58);
		अवरोध;
	हाल 90:
		ग_लिखो_reg(par, 0xB6, 0x00, 0x22, 0x3B);
		ग_लिखो_reg(par, MIPI_DCS_SET_ADDRESS_MODE, 0x38);
		अवरोध;
	शेष:
		ग_लिखो_reg(par, 0xB6, 0x00, 0x22, 0x3B);
		ग_लिखो_reg(par, MIPI_DCS_SET_ADDRESS_MODE, 0x08);
		अवरोध;
	पूर्ण

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

FBTFT_REGISTER_DRIVER(DRVNAME, "neosec,tinylcd", &display);

MODULE_ALIAS("spi:" DRVNAME);
MODULE_ALIAS("spi:tinylcd");

MODULE_DESCRIPTION("Custom FB driver for tinylcd.com display");
MODULE_AUTHOR("Noralf Tronnes");
MODULE_LICENSE("GPL");
