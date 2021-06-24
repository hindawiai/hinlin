<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * FB driver क्रम the TLS8204 LCD Controller
 *
 * The display is monochrome and the video memory is RGB565.
 * Any pixel value except 0 turns the pixel on.
 *
 * Copyright (C) 2013 Noralf Tronnes
 * Copyright (C) 2014 Michael Hope (adapted क्रम the TLS8204)
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/delay.h>

#समावेश "fbtft.h"

#घोषणा DRVNAME		"fb_tls8204"
#घोषणा WIDTH		84
#घोषणा HEIGHT		48
#घोषणा TXBUFLEN	WIDTH

/* gamma is used to control contrast in this driver */
#घोषणा DEFAULT_GAMMA	"40"

अटल अचिन्हित पूर्णांक bs = 4;
module_param(bs, uपूर्णांक, 0000);
MODULE_PARM_DESC(bs, "BS[2:0] Bias voltage level: 0-7 (default: 4)");

अटल पूर्णांक init_display(काष्ठा fbtft_par *par)
अणु
	par->fbtftops.reset(par);

	/* Enter extended command mode */
	ग_लिखो_reg(par, 0x21);	/* 5:1  1
				 * 2:0  PD - Powerकरोwn control: chip is active
				 * 1:0  V  - Entry mode: horizontal addressing
				 * 0:1  H  - Extended inकाष्ठाion set control:
				 *	     extended
				 */

	/* H=1 Bias प्रणाली */
	ग_लिखो_reg(par, 0x10 | (bs & 0x7));
				/* 4:1  1
				 * 3:0  0
				 * 2:x  BS2 - Bias System
				 * 1:x  BS1
				 * 0:x  BS0
				 */

	/* Set the address of the first display line. */
	ग_लिखो_reg(par, 0x04 | (64 >> 6));
	ग_लिखो_reg(par, 0x40 | (64 & 0x3F));

	/* Enter H=0 standard command mode */
	ग_लिखो_reg(par, 0x20);

	/* H=0 Display control */
	ग_लिखो_reg(par, 0x08 | 4);
				/* 3:1  1
				 * 2:1  D - DE: 10=normal mode
				 * 1:0  0
				 * 0:0  E
				 */

	वापस 0;
पूर्ण

अटल व्योम set_addr_win(काष्ठा fbtft_par *par, पूर्णांक xs, पूर्णांक ys, पूर्णांक xe, पूर्णांक ye)
अणु
	/* H=0 Set X address of RAM */
	ग_लिखो_reg(par, 0x80);	/* 7:1  1
				 * 6-0: X[6:0] - 0x00
				 */

	/* H=0 Set Y address of RAM */
	ग_लिखो_reg(par, 0x40);	/* 7:0  0
				 * 6:1  1
				 * 2-0: Y[2:0] - 0x0
				 */
पूर्ण

अटल पूर्णांक ग_लिखो_vmem(काष्ठा fbtft_par *par, माप_प्रकार offset, माप_प्रकार len)
अणु
	u16 *vmem16 = (u16 *)par->info->screen_buffer;
	पूर्णांक x, y, i;
	पूर्णांक ret = 0;

	क्रम (y = 0; y < HEIGHT / 8; y++) अणु
		u8 *buf = par->txbuf.buf;
		/* The display is 102x68 but the LCD is 84x48.
		 * Set the ग_लिखो poपूर्णांकer at the start of each row.
		 */
		gpiod_set_value(par->gpio.dc, 0);
		ग_लिखो_reg(par, 0x80 | 0);
		ग_लिखो_reg(par, 0x40 | y);

		क्रम (x = 0; x < WIDTH; x++) अणु
			u8 ch = 0;

			क्रम (i = 0; i < 8 * WIDTH; i += WIDTH) अणु
				ch >>= 1;
				अगर (vmem16[(y * 8 * WIDTH) + i + x])
					ch |= 0x80;
			पूर्ण
			*buf++ = ch;
		पूर्ण
		/* Write the row */
		gpiod_set_value(par->gpio.dc, 1);
		ret = par->fbtftops.ग_लिखो(par, par->txbuf.buf, WIDTH);
		अगर (ret < 0) अणु
			dev_err(par->info->device,
				"write failed and returned: %d\n", ret);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक set_gamma(काष्ठा fbtft_par *par, u32 *curves)
अणु
	/* apply mask */
	curves[0] &= 0x7F;

	ग_लिखो_reg(par, 0x21); /* turn on extended inकाष्ठाion set */
	ग_लिखो_reg(par, 0x80 | curves[0]);
	ग_लिखो_reg(par, 0x20); /* turn off extended inकाष्ठाion set */

	वापस 0;
पूर्ण

अटल काष्ठा fbtft_display display = अणु
	.regwidth = 8,
	.width = WIDTH,
	.height = HEIGHT,
	.txbuflen = TXBUFLEN,
	.gamma_num = 1,
	.gamma_len = 1,
	.gamma = DEFAULT_GAMMA,
	.fbtftops = अणु
		.init_display = init_display,
		.set_addr_win = set_addr_win,
		.ग_लिखो_vmem = ग_लिखो_vmem,
		.set_gamma = set_gamma,
	पूर्ण,
	.backlight = 1,
पूर्ण;

FBTFT_REGISTER_DRIVER(DRVNAME, "teralane,tls8204", &display);

MODULE_ALIAS("spi:" DRVNAME);
MODULE_ALIAS("spi:tls8204");

MODULE_DESCRIPTION("FB driver for the TLS8204 LCD Controller");
MODULE_AUTHOR("Michael Hope");
MODULE_LICENSE("GPL");
