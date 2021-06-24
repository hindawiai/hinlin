<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * FB driver क्रम the HX8357D LCD Controller
 * Copyright (C) 2015 Adafruit Industries
 *
 * Based on the HX8347D FB driver
 * Copyright (C) 2013 Christian Vogelgsang
 *
 * Based on driver code found here: https://github.com/watterott/r61505u-Adapter
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <video/mipi_display.h>

#समावेश "fbtft.h"
#समावेश "fb_hx8357d.h"

#घोषणा DRVNAME		"fb_hx8357d"
#घोषणा WIDTH		320
#घोषणा HEIGHT		480

अटल पूर्णांक init_display(काष्ठा fbtft_par *par)
अणु
	par->fbtftops.reset(par);

	/* Reset things like Gamma */
	ग_लिखो_reg(par, MIPI_DCS_SOFT_RESET);
	usleep_range(5000, 7000);

	/* setextc */
	ग_लिखो_reg(par, HX8357D_SETC, 0xFF, 0x83, 0x57);
	msleep(150);

	/* setRGB which also enables SDO */
	ग_लिखो_reg(par, HX8357_SETRGB, 0x00, 0x00, 0x06, 0x06);

	/* -1.52V */
	ग_लिखो_reg(par, HX8357D_SETCOM, 0x25);

	/* Normal mode 70Hz, Idle mode 55 Hz */
	ग_लिखो_reg(par, HX8357_SETOSC, 0x68);

	/* Set Panel - BGR, Gate direction swapped */
	ग_लिखो_reg(par, HX8357_SETPANEL, 0x05);

	ग_लिखो_reg(par, HX8357_SETPWR1,
		  0x00,  /* Not deep standby */
		  0x15,  /* BT */
		  0x1C,  /* VSPR */
		  0x1C,  /* VSNR */
		  0x83,  /* AP */
		  0xAA);  /* FS */

	ग_लिखो_reg(par, HX8357D_SETSTBA,
		  0x50,  /* OPON normal */
		  0x50,  /* OPON idle */
		  0x01,  /* STBA */
		  0x3C,  /* STBA */
		  0x1E,  /* STBA */
		  0x08);  /* GEN */

	ग_लिखो_reg(par, HX8357D_SETCYC,
		  0x02,  /* NW 0x02 */
		  0x40,  /* RTN */
		  0x00,  /* DIV */
		  0x2A,  /* DUM */
		  0x2A,  /* DUM */
		  0x0D,  /* GDON */
		  0x78);  /* GDOFF */

	ग_लिखो_reg(par, HX8357D_SETGAMMA,
		  0x02,
		  0x0A,
		  0x11,
		  0x1d,
		  0x23,
		  0x35,
		  0x41,
		  0x4b,
		  0x4b,
		  0x42,
		  0x3A,
		  0x27,
		  0x1B,
		  0x08,
		  0x09,
		  0x03,
		  0x02,
		  0x0A,
		  0x11,
		  0x1d,
		  0x23,
		  0x35,
		  0x41,
		  0x4b,
		  0x4b,
		  0x42,
		  0x3A,
		  0x27,
		  0x1B,
		  0x08,
		  0x09,
		  0x03,
		  0x00,
		  0x01);

	/* 16 bit */
	ग_लिखो_reg(par, MIPI_DCS_SET_PIXEL_FORMAT, 0x55);

	ग_लिखो_reg(par, MIPI_DCS_SET_ADDRESS_MODE, 0xC0);

	/* TE off */
	ग_लिखो_reg(par, MIPI_DCS_SET_TEAR_ON, 0x00);

	/* tear line */
	ग_लिखो_reg(par, MIPI_DCS_SET_TEAR_SCANLINE, 0x00, 0x02);

	/* Exit Sleep */
	ग_लिखो_reg(par, MIPI_DCS_EXIT_SLEEP_MODE);
	msleep(150);

	/* display on */
	ग_लिखो_reg(par, MIPI_DCS_SET_DISPLAY_ON);
	usleep_range(5000, 7000);

	वापस 0;
पूर्ण

अटल व्योम set_addr_win(काष्ठा fbtft_par *par, पूर्णांक xs, पूर्णांक ys, पूर्णांक xe, पूर्णांक ye)
अणु
	ग_लिखो_reg(par, MIPI_DCS_SET_COLUMN_ADDRESS,
		  xs >> 8, xs & 0xff,  /* XSTART */
		  xe >> 8, xe & 0xff); /* XEND */

	ग_लिखो_reg(par, MIPI_DCS_SET_PAGE_ADDRESS,
		  ys >> 8, ys & 0xff,  /* YSTART */
		  ye >> 8, ye & 0xff); /* YEND */

	ग_लिखो_reg(par, MIPI_DCS_WRITE_MEMORY_START);
पूर्ण

#घोषणा HX8357D_MADCTL_MY  0x80
#घोषणा HX8357D_MADCTL_MX  0x40
#घोषणा HX8357D_MADCTL_MV  0x20
#घोषणा HX8357D_MADCTL_ML  0x10
#घोषणा HX8357D_MADCTL_RGB 0x00
#घोषणा HX8357D_MADCTL_BGR 0x08
#घोषणा HX8357D_MADCTL_MH  0x04
अटल पूर्णांक set_var(काष्ठा fbtft_par *par)
अणु
	u8 val;

	चयन (par->info->var.rotate) अणु
	हाल 270:
		val = HX8357D_MADCTL_MV | HX8357D_MADCTL_MX;
		अवरोध;
	हाल 180:
		val = 0;
		अवरोध;
	हाल 90:
		val = HX8357D_MADCTL_MV | HX8357D_MADCTL_MY;
		अवरोध;
	शेष:
		val = HX8357D_MADCTL_MX | HX8357D_MADCTL_MY;
		अवरोध;
	पूर्ण

	val |= (par->bgr ? HX8357D_MADCTL_RGB : HX8357D_MADCTL_BGR);

	/* Memory Access Control */
	ग_लिखो_reg(par, MIPI_DCS_SET_ADDRESS_MODE, val);

	वापस 0;
पूर्ण

अटल काष्ठा fbtft_display display = अणु
	.regwidth = 8,
	.width = WIDTH,
	.height = HEIGHT,
	.gamma_num = 2,
	.gamma_len = 14,
	.fbtftops = अणु
		.init_display = init_display,
		.set_addr_win = set_addr_win,
		.set_var = set_var,
	पूर्ण,
पूर्ण;

FBTFT_REGISTER_DRIVER(DRVNAME, "himax,hx8357d", &display);

MODULE_ALIAS("spi:" DRVNAME);
MODULE_ALIAS("platform:" DRVNAME);
MODULE_ALIAS("spi:hx8357d");
MODULE_ALIAS("platform:hx8357d");

MODULE_DESCRIPTION("FB driver for the HX8357D LCD Controller");
MODULE_AUTHOR("Sean Cross <xobs@kosagi.com>");
MODULE_LICENSE("GPL");
