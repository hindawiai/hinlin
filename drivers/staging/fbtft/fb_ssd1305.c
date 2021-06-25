<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * FB driver क्रम the SSD1305 OLED Controller
 *
 * based on SSD1306 driver by Noralf Tronnes
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/delay.h>

#समावेश "fbtft.h"

#घोषणा DRVNAME		"fb_ssd1305"

#घोषणा WIDTH 128
#घोषणा HEIGHT 64

/*
 * ग_लिखो_reg() caveat:
 *
 *    This करोesn't work because D/C has to be LOW क्रम both values:
 *      ग_लिखो_reg(par, val1, val2);
 *
 *    Do it like this:
 *      ग_लिखो_reg(par, val1);
 *      ग_लिखो_reg(par, val2);
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

	/*
	 * Set Segment Re-map
	 * column address 127 is mapped to SEG0
	 */
	ग_लिखो_reg(par, 0xA0 | ((par->info->var.rotate == 180) ? 0x0 : 0x1));

	/*
	 * Set COM Output Scan Direction
	 * remapped mode. Scan from COM[N-1] to COM0
	 */
	ग_लिखो_reg(par, ((par->info->var.rotate == 180) ? 0xC8 : 0xC0));

	/* Set COM Pins Hardware Configuration */
	ग_लिखो_reg(par, 0xDA);
	अगर (par->info->var.yres == 64) अणु
		/* A[4]=1b, Alternative COM pin configuration */
		ग_लिखो_reg(par, 0x12);
	पूर्ण अन्यथा अणु
		/* A[4]=0b, Sequential COM pin configuration */
		ग_लिखो_reg(par, 0x02);
	पूर्ण

	/* Set Pre-अक्षरge Period */
	ग_लिखो_reg(par, 0xD9);
	ग_लिखो_reg(par, 0xF1);

	/*
	 * Entire Display ON
	 * Resume to RAM content display. Output follows RAM content
	 */
	ग_लिखो_reg(par, 0xA4);

	/*
	 * Set Normal Display
	 *  0 in RAM: OFF in display panel
	 *  1 in RAM: ON in display panel
	 */
	ग_लिखो_reg(par, 0xA6);

	/* Set Display ON */
	ग_लिखो_reg(par, 0xAF);

	वापस 0;
पूर्ण

अटल व्योम set_addr_win(काष्ठा fbtft_par *par, पूर्णांक xs, पूर्णांक ys, पूर्णांक xe, पूर्णांक ye)
अणु
	/* Set Lower Column Start Address क्रम Page Addressing Mode */
	ग_लिखो_reg(par, 0x00 | ((par->info->var.rotate == 180) ? 0x0 : 0x4));
	/* Set Higher Column Start Address क्रम Page Addressing Mode */
	ग_लिखो_reg(par, 0x10 | 0x0);
	/* Set Display Start Line */
	ग_लिखो_reg(par, 0x40 | 0x0);
पूर्ण

अटल पूर्णांक blank(काष्ठा fbtft_par *par, bool on)
अणु
	अगर (on)
		ग_लिखो_reg(par, 0xAE);
	अन्यथा
		ग_लिखो_reg(par, 0xAF);
	वापस 0;
पूर्ण

/* Gamma is used to control Contrast */
अटल पूर्णांक set_gamma(काष्ठा fbtft_par *par, u32 *curves)
अणु
	curves[0] &= 0xFF;
	/* Set Contrast Control क्रम BANK0 */
	ग_लिखो_reg(par, 0x81);
	ग_लिखो_reg(par, curves[0]);

	वापस 0;
पूर्ण

अटल पूर्णांक ग_लिखो_vmem(काष्ठा fbtft_par *par, माप_प्रकार offset, माप_प्रकार len)
अणु
	u16 *vmem16 = (u16 *)par->info->screen_buffer;
	u8 *buf = par->txbuf.buf;
	पूर्णांक x, y, i;
	पूर्णांक ret;

	क्रम (x = 0; x < par->info->var.xres; x++) अणु
		क्रम (y = 0; y < par->info->var.yres / 8; y++) अणु
			*buf = 0x00;
			क्रम (i = 0; i < 8; i++)
				*buf |= (vmem16[(y * 8 + i) *
						par->info->var.xres + x] ?
					 1 : 0) << i;
			buf++;
		पूर्ण
	पूर्ण

	/* Write data */
	gpiod_set_value(par->gpio.dc, 1);
	ret = par->fbtftops.ग_लिखो(par, par->txbuf.buf,
				  par->info->var.xres * par->info->var.yres /
				  8);
	अगर (ret < 0)
		dev_err(par->info->device, "write failed and returned: %d\n",
			ret);
	वापस ret;
पूर्ण

अटल काष्ठा fbtft_display display = अणु
	.regwidth = 8,
	.width = WIDTH,
	.height = HEIGHT,
	.txbuflen = WIDTH * HEIGHT / 8,
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

FBTFT_REGISTER_DRIVER(DRVNAME, "solomon,ssd1305", &display);

MODULE_ALIAS("spi:" DRVNAME);
MODULE_ALIAS("platform:" DRVNAME);
MODULE_ALIAS("spi:ssd1305");
MODULE_ALIAS("platform:ssd1305");

MODULE_DESCRIPTION("SSD1305 OLED Driver");
MODULE_AUTHOR("Alexey Mednyy");
MODULE_LICENSE("GPL");
