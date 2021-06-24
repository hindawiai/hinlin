<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * FB driver क्रम the SSD1325 OLED Controller
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/delay.h>

#समावेश "fbtft.h"

#घोषणा DRVNAME		"fb_ssd1325"

#घोषणा WIDTH 128
#घोषणा HEIGHT 64
#घोषणा GAMMA_NUM   1
#घोषणा GAMMA_LEN   15
#घोषणा DEFAULT_GAMMA "7 1 1 1 1 2 2 3 3 4 4 5 5 6 6"

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

	gpiod_set_value(par->gpio.cs, 0);

	ग_लिखो_reg(par, 0xb3);
	ग_लिखो_reg(par, 0xf0);
	ग_लिखो_reg(par, 0xae);
	ग_लिखो_reg(par, 0xa1);
	ग_लिखो_reg(par, 0x00);
	ग_लिखो_reg(par, 0xa8);
	ग_लिखो_reg(par, 0x3f);
	ग_लिखो_reg(par, 0xa0);
	ग_लिखो_reg(par, 0x45);
	ग_लिखो_reg(par, 0xa2);
	ग_लिखो_reg(par, 0x40);
	ग_लिखो_reg(par, 0x75);
	ग_लिखो_reg(par, 0x00);
	ग_लिखो_reg(par, 0x3f);
	ग_लिखो_reg(par, 0x15);
	ग_लिखो_reg(par, 0x00);
	ग_लिखो_reg(par, 0x7f);
	ग_लिखो_reg(par, 0xa4);
	ग_लिखो_reg(par, 0xaf);

	वापस 0;
पूर्ण

अटल uपूर्णांक8_t rgb565_to_g16(u16 pixel)
अणु
	u16 b = pixel & 0x1f;
	u16 g = (pixel & (0x3f << 5)) >> 5;
	u16 r = (pixel & (0x1f << (5 + 6))) >> (5 + 6);

	pixel = (299 * r + 587 * g + 114 * b) / 195;
	अगर (pixel > 255)
		pixel = 255;
	वापस (uपूर्णांक8_t)pixel / 16;
पूर्ण

अटल व्योम set_addr_win(काष्ठा fbtft_par *par, पूर्णांक xs, पूर्णांक ys, पूर्णांक xe, पूर्णांक ye)
अणु
	fbtft_par_dbg(DEBUG_SET_ADDR_WIN, par,
		      "%s(xs=%d, ys=%d, xe=%d, ye=%d)\n", __func__, xs, ys, xe,
		      ye);

	ग_लिखो_reg(par, 0x75);
	ग_लिखो_reg(par, 0x00);
	ग_लिखो_reg(par, 0x3f);
	ग_लिखो_reg(par, 0x15);
	ग_लिखो_reg(par, 0x00);
	ग_लिखो_reg(par, 0x7f);
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

/*
 * Grayscale Lookup Table
 * GS1 - GS15
 * The "Gamma curve" contains the relative values between the entries
 * in the Lookup table.
 *
 * 0 = Setting of GS1 < Setting of GS2 < Setting of GS3.....<
 * Setting of GS14 < Setting of GS15
 */
अटल पूर्णांक set_gamma(काष्ठा fbtft_par *par, u32 *curves)
अणु
	पूर्णांक i;

	fbtft_par_dbg(DEBUG_INIT_DISPLAY, par, "%s()\n", __func__);

	क्रम (i = 0; i < GAMMA_LEN; i++) अणु
		अगर (i > 0 && curves[i] < 1) अणु
			dev_err(par->info->device,
				"Illegal value in Grayscale Lookup Table at index %d.\n"
				"Must be greater than 0\n", i);
			वापस -EINVAL;
		पूर्ण
		अगर (curves[i] > 7) अणु
			dev_err(par->info->device,
				"Illegal value(s) in Grayscale Lookup Table.\n"
				"At index=%d, the accumulated value has exceeded 7\n",
				i);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	ग_लिखो_reg(par, 0xB8);
	क्रम (i = 0; i < 8; i++)
		ग_लिखो_reg(par, (curves[i] & 0xFF));
	वापस 0;
पूर्ण

अटल पूर्णांक ग_लिखो_vmem(काष्ठा fbtft_par *par, माप_प्रकार offset, माप_प्रकार len)
अणु
	u16 *vmem16 = (u16 *)par->info->screen_buffer;
	u8 *buf = par->txbuf.buf;
	u8 n1;
	u8 n2;
	पूर्णांक y, x;
	पूर्णांक ret;

	क्रम (x = 0; x < par->info->var.xres; x++) अणु
		अगर (x % 2)
			जारी;
		क्रम (y = 0; y < par->info->var.yres; y++) अणु
			n1 = rgb565_to_g16(vmem16[y * par->info->var.xres + x]);
			n2 = rgb565_to_g16(vmem16
					   [y * par->info->var.xres + x + 1]);
			*buf = (n1 << 4) | n2;
			buf++;
		पूर्ण
	पूर्ण

	gpiod_set_value(par->gpio.dc, 1);

	/* Write data */
	ret = par->fbtftops.ग_लिखो(par, par->txbuf.buf,
				par->info->var.xres * par->info->var.yres / 2);
	अगर (ret < 0)
		dev_err(par->info->device,
			"%s: write failed and returned: %d\n", __func__, ret);

	वापस ret;
पूर्ण

अटल काष्ठा fbtft_display display = अणु
	.regwidth = 8,
	.width = WIDTH,
	.height = HEIGHT,
	.txbuflen = WIDTH * HEIGHT / 2,
	.gamma_num = GAMMA_NUM,
	.gamma_len = GAMMA_LEN,
	.gamma = DEFAULT_GAMMA,
	.fbtftops = अणु
		.ग_लिखो_vmem = ग_लिखो_vmem,
		.init_display = init_display,
		.set_addr_win = set_addr_win,
		.blank = blank,
		.set_gamma = set_gamma,
	पूर्ण,
पूर्ण;

FBTFT_REGISTER_DRIVER(DRVNAME, "solomon,ssd1325", &display);

MODULE_ALIAS("spi:" DRVNAME);
MODULE_ALIAS("platform:" DRVNAME);
MODULE_ALIAS("spi:ssd1325");
MODULE_ALIAS("platform:ssd1325");

MODULE_DESCRIPTION("SSD1325 OLED Driver");
MODULE_AUTHOR("Alexey Mednyy");
MODULE_LICENSE("GPL");
