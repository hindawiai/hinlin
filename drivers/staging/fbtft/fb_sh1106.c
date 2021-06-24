<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * FB driver क्रम the SH1106 OLED Controller
 * Based on the SSD1306 driver by Noralf Tronnes
 *
 * Copyright (C) 2017 Heiner Kallweit
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/delay.h>

#समावेश "fbtft.h"

#घोषणा DRVNAME		"fb_sh1106"
#घोषणा WIDTH		128
#घोषणा HEIGHT		64

/* Init sequence based on the Adafruit SSD1306 Arduino library */
अटल पूर्णांक init_display(काष्ठा fbtft_par *par)
अणु
	अगर (!par->info->var.xres || par->info->var.xres > WIDTH ||
	    !par->info->var.yres || par->info->var.yres > HEIGHT ||
	    par->info->var.yres % 8) अणु
		dev_err(par->info->device, "Invalid screen size\n");
		वापस -EINVAL;
	पूर्ण

	अगर (par->info->var.rotate) अणु
		dev_err(par->info->device, "Display rotation not supported\n");
		वापस -EINVAL;
	पूर्ण

	par->fbtftops.reset(par);

	/* Set Display OFF */
	ग_लिखो_reg(par, 0xAE);

	/* Set Display Clock Divide Ratio/ Oscillator Frequency */
	ग_लिखो_reg(par, 0xD5, 0x80);

	/* Set Multiplex Ratio */
	ग_लिखो_reg(par, 0xA8, par->info->var.yres - 1);

	/* Set Display Offset */
	ग_लिखो_reg(par, 0xD3, 0x00);

	/* Set Display Start Line */
	ग_लिखो_reg(par, 0x40 | 0x0);

	/* Set Segment Re-map */
	/* column address 127 is mapped to SEG0 */
	ग_लिखो_reg(par, 0xA0 | 0x1);

	/* Set COM Output Scan Direction */
	/* remapped mode. Scan from COM[N-1] to COM0 */
	ग_लिखो_reg(par, 0xC8);

	/* Set COM Pins Hardware Configuration */
	अगर (par->info->var.yres == 64)
		/* A[4]=1b, Alternative COM pin configuration */
		ग_लिखो_reg(par, 0xDA, 0x12);
	अन्यथा अगर (par->info->var.yres == 48)
		/* A[4]=1b, Alternative COM pin configuration */
		ग_लिखो_reg(par, 0xDA, 0x12);
	अन्यथा
		/* A[4]=0b, Sequential COM pin configuration */
		ग_लिखो_reg(par, 0xDA, 0x02);

	/* Set Pre-अक्षरge Period */
	ग_लिखो_reg(par, 0xD9, 0xF1);

	/* Set VCOMH Deselect Level */
	ग_लिखो_reg(par, 0xDB, 0x40);

	/* Set Display ON */
	ग_लिखो_reg(par, 0xAF);

	msleep(150);

	वापस 0;
पूर्ण

अटल व्योम set_addr_win(काष्ठा fbtft_par *par, पूर्णांक xs, पूर्णांक ys, पूर्णांक xe, पूर्णांक ye)
अणु
पूर्ण

अटल पूर्णांक blank(काष्ठा fbtft_par *par, bool on)
अणु
	fbtft_par_dbg(DEBUG_BLANK, par, "(%s=%s)\n",
		      __func__, on ? "true" : "false");

	ग_लिखो_reg(par, on ? 0xAE : 0xAF);

	वापस 0;
पूर्ण

/* Gamma is used to control Contrast */
अटल पूर्णांक set_gamma(काष्ठा fbtft_par *par, u32 *curves)
अणु
	/* apply mask */
	curves[0] &= 0xFF;

	/* Set Contrast Control क्रम BANK0 */
	ग_लिखो_reg(par, 0x81, curves[0]);

	वापस 0;
पूर्ण

अटल पूर्णांक ग_लिखो_vmem(काष्ठा fbtft_par *par, माप_प्रकार offset, माप_प्रकार len)
अणु
	u16 *vmem16 = (u16 *)par->info->screen_buffer;
	u32 xres = par->info->var.xres;
	पूर्णांक page, page_start, page_end, x, i, ret;
	u8 *buf = par->txbuf.buf;

	/* offset refers to vmem with 2 bytes element size */
	page_start = offset / (8 * 2 * xres);
	page_end = DIV_ROUND_UP(offset + len, 8 * 2 * xres);

	क्रम (page = page_start; page < page_end; page++) अणु
		/* set page and set column to 2 because of vidmem width 132 */
		ग_लिखो_reg(par, 0xb0 | page, 0x00 | 2, 0x10 | 0);

		स_रखो(buf, 0, xres);
		क्रम (x = 0; x < xres; x++)
			क्रम (i = 0; i < 8; i++)
				अगर (vmem16[(page * 8 + i) * xres + x])
					buf[x] |= BIT(i);

		/* Write data */
		ret = fbtft_ग_लिखो_buf_dc(par, buf, xres, 1);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ग_लिखो_रेजिस्टर(काष्ठा fbtft_par *par, पूर्णांक len, ...)
अणु
	बहु_सूची args;
	पूर्णांक i;

	बहु_शुरू(args, len);

	क्रम (i = 0; i < len; i++)
		par->buf[i] = बहु_तर्क(args, अचिन्हित पूर्णांक);

	/* keep DC low क्रम all command bytes to transfer */
	fbtft_ग_लिखो_buf_dc(par, par->buf, len, 0);

	बहु_पूर्ण(args);
पूर्ण

अटल काष्ठा fbtft_display display = अणु
	.regwidth = 8,
	.width = WIDTH,
	.height = HEIGHT,
	.txbuflen = WIDTH,
	.gamma_num = 1,
	.gamma_len = 1,
	/* set शेष contrast to 0xcd = 80% */
	.gamma = "cd",
	.fbtftops = अणु
		.ग_लिखो_vmem = ग_लिखो_vmem,
		.ग_लिखो_रेजिस्टर = ग_लिखो_रेजिस्टर,
		.init_display = init_display,
		.set_addr_win = set_addr_win,
		.blank = blank,
		.set_gamma = set_gamma,
	पूर्ण,
पूर्ण;

FBTFT_REGISTER_DRIVER(DRVNAME, "sinowealth,sh1106", &display);

MODULE_ALIAS("spi:" DRVNAME);
MODULE_ALIAS("platform:" DRVNAME);
MODULE_ALIAS("spi:sh1106");
MODULE_ALIAS("platform:sh1106");

MODULE_DESCRIPTION("SH1106 OLED Driver");
MODULE_AUTHOR("Heiner Kallweit");
MODULE_LICENSE("GPL");
