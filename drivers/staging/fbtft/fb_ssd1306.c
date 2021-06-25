<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * FB driver क्रम the SSD1306 OLED Controller
 *
 * Copyright (C) 2013 Noralf Tronnes
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/delay.h>

#समावेश "fbtft.h"

#घोषणा DRVNAME		"fb_ssd1306"
#घोषणा WIDTH		128
#घोषणा HEIGHT		64

/*
 * ग_लिखो_reg() caveat:
 *
 * This करोesn't work because D/C has to be LOW क्रम both values:
 * ग_लिखो_reg(par, val1, val2);
 *
 * Do it like this:
 * ग_लिखो_reg(par, val1);
 * ग_लिखो_reg(par, val2);
 */

/* Init sequence taken from the Adafruit SSD1306 Arduino library */
अटल पूर्णांक init_display(काष्ठा fbtft_par *par)
अणु
	par->fbtftops.reset(par);

	अगर (par->gamma.curves[0] == 0) अणु
		mutex_lock(&par->gamma.lock);
		अगर (par->info->var.yres == 64)
			par->gamma.curves[0] = 0xCF;
		अन्यथा
			par->gamma.curves[0] = 0x8F;
		mutex_unlock(&par->gamma.lock);
	पूर्ण

	/* Set Display OFF */
	ग_लिखो_reg(par, 0xAE);

	/* Set Display Clock Divide Ratio/ Oscillator Frequency */
	ग_लिखो_reg(par, 0xD5);
	ग_लिखो_reg(par, 0x80);

	/* Set Multiplex Ratio */
	ग_लिखो_reg(par, 0xA8);
	अगर (par->info->var.yres == 64)
		ग_लिखो_reg(par, 0x3F);
	अन्यथा अगर (par->info->var.yres == 48)
		ग_लिखो_reg(par, 0x2F);
	अन्यथा
		ग_लिखो_reg(par, 0x1F);

	/* Set Display Offset */
	ग_लिखो_reg(par, 0xD3);
	ग_लिखो_reg(par, 0x0);

	/* Set Display Start Line */
	ग_लिखो_reg(par, 0x40 | 0x0);

	/* Charge Pump Setting */
	ग_लिखो_reg(par, 0x8D);
	/* A[2] = 1b, Enable अक्षरge pump during display on */
	ग_लिखो_reg(par, 0x14);

	/* Set Memory Addressing Mode */
	ग_लिखो_reg(par, 0x20);
	/* Vertical addressing mode  */
	ग_लिखो_reg(par, 0x01);

	/* Set Segment Re-map */
	/* column address 127 is mapped to SEG0 */
	ग_लिखो_reg(par, 0xA0 | 0x1);

	/* Set COM Output Scan Direction */
	/* remapped mode. Scan from COM[N-1] to COM0 */
	ग_लिखो_reg(par, 0xC8);

	/* Set COM Pins Hardware Configuration */
	ग_लिखो_reg(par, 0xDA);
	अगर (par->info->var.yres == 64)
		/* A[4]=1b, Alternative COM pin configuration */
		ग_लिखो_reg(par, 0x12);
	अन्यथा अगर (par->info->var.yres == 48)
		/* A[4]=1b, Alternative COM pin configuration */
		ग_लिखो_reg(par, 0x12);
	अन्यथा
		/* A[4]=0b, Sequential COM pin configuration */
		ग_लिखो_reg(par, 0x02);

	/* Set Pre-अक्षरge Period */
	ग_लिखो_reg(par, 0xD9);
	ग_लिखो_reg(par, 0xF1);

	/* Set VCOMH Deselect Level */
	ग_लिखो_reg(par, 0xDB);
	/* according to the datasheet, this value is out of bounds */
	ग_लिखो_reg(par, 0x40);

	/* Entire Display ON */
	/* Resume to RAM content display. Output follows RAM content */
	ग_लिखो_reg(par, 0xA4);

	/* Set Normal Display
	 * 0 in RAM: OFF in display panel
	 * 1 in RAM: ON in display panel
	 */
	ग_लिखो_reg(par, 0xA6);

	/* Set Display ON */
	ग_लिखो_reg(par, 0xAF);

	वापस 0;
पूर्ण

अटल व्योम set_addr_win_64x48(काष्ठा fbtft_par *par)
अणु
	/* Set Column Address */
	ग_लिखो_reg(par, 0x21);
	ग_लिखो_reg(par, 0x20);
	ग_लिखो_reg(par, 0x5F);

	/* Set Page Address */
	ग_लिखो_reg(par, 0x22);
	ग_लिखो_reg(par, 0x0);
	ग_लिखो_reg(par, 0x5);
पूर्ण

अटल व्योम set_addr_win(काष्ठा fbtft_par *par, पूर्णांक xs, पूर्णांक ys, पूर्णांक xe, पूर्णांक ye)
अणु
	/* Set Lower Column Start Address क्रम Page Addressing Mode */
	ग_लिखो_reg(par, 0x00 | 0x0);
	/* Set Higher Column Start Address क्रम Page Addressing Mode */
	ग_लिखो_reg(par, 0x10 | 0x0);
	/* Set Display Start Line */
	ग_लिखो_reg(par, 0x40 | 0x0);

	अगर (par->info->var.xres == 64 && par->info->var.yres == 48)
		set_addr_win_64x48(par);
पूर्ण

अटल पूर्णांक blank(काष्ठा fbtft_par *par, bool on)
अणु
	fbtft_par_dbg(DEBUG_BLANK, par, "(%s=%s)\n",
		      __func__, on ? "true" : "false");

	अगर (on)
		ग_लिखो_reg(par, 0xAE);
	अन्यथा
		ग_लिखो_reg(par, 0xAF);
	वापस 0;
पूर्ण

/* Gamma is used to control Contrast */
अटल पूर्णांक set_gamma(काष्ठा fbtft_par *par, u32 *curves)
अणु
	/* apply mask */
	curves[0] &= 0xFF;

	/* Set Contrast Control क्रम BANK0 */
	ग_लिखो_reg(par, 0x81);
	ग_लिखो_reg(par, curves[0]);

	वापस 0;
पूर्ण

अटल पूर्णांक ग_लिखो_vmem(काष्ठा fbtft_par *par, माप_प्रकार offset, माप_प्रकार len)
अणु
	u16 *vmem16 = (u16 *)par->info->screen_buffer;
	u32 xres = par->info->var.xres;
	u32 yres = par->info->var.yres;
	u8 *buf = par->txbuf.buf;
	पूर्णांक x, y, i;
	पूर्णांक ret = 0;

	क्रम (x = 0; x < xres; x++) अणु
		क्रम (y = 0; y < yres / 8; y++) अणु
			*buf = 0x00;
			क्रम (i = 0; i < 8; i++)
				अगर (vmem16[(y * 8 + i) * xres + x])
					*buf |= BIT(i);
			buf++;
		पूर्ण
	पूर्ण

	/* Write data */
	gpiod_set_value(par->gpio.dc, 1);
	ret = par->fbtftops.ग_लिखो(par, par->txbuf.buf, xres * yres / 8);
	अगर (ret < 0)
		dev_err(par->info->device, "write failed and returned: %d\n",
			ret);

	वापस ret;
पूर्ण

अटल काष्ठा fbtft_display display = अणु
	.regwidth = 8,
	.width = WIDTH,
	.height = HEIGHT,
	.gamma_num = 1,
	.gamma_len = 1,
	.gamma = "00",
	.fbtftops = अणु
		.ग_लिखो_vmem = ग_लिखो_vmem,
		.init_display = init_display,
		.set_addr_win = set_addr_win,
		.blank = blank,
		.set_gamma = set_gamma,
	पूर्ण,
पूर्ण;

FBTFT_REGISTER_DRIVER(DRVNAME, "solomon,ssd1306", &display);

MODULE_ALIAS("spi:" DRVNAME);
MODULE_ALIAS("platform:" DRVNAME);
MODULE_ALIAS("spi:ssd1306");
MODULE_ALIAS("platform:ssd1306");

MODULE_DESCRIPTION("SSD1306 OLED Driver");
MODULE_AUTHOR("Noralf Tronnes");
MODULE_LICENSE("GPL");
