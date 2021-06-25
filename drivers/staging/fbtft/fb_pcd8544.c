<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * FB driver क्रम the PCD8544 LCD Controller
 *
 * The display is monochrome and the video memory is RGB565.
 * Any pixel value except 0 turns the pixel on.
 *
 * Copyright (C) 2013 Noralf Tronnes
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/delay.h>

#समावेश "fbtft.h"

#घोषणा DRVNAME	       "fb_pcd8544"
#घोषणा WIDTH          84
#घोषणा HEIGHT         48
#घोषणा TXBUFLEN       (84 * 6)
#घोषणा DEFAULT_GAMMA  "40" /* gamma controls the contrast in this driver */

अटल अचिन्हित पूर्णांक tc;
module_param(tc, uपूर्णांक, 0000);
MODULE_PARM_DESC(tc, "TC[1:0] Temperature coefficient: 0-3 (default: 0)");

अटल अचिन्हित पूर्णांक bs = 4;
module_param(bs, uपूर्णांक, 0000);
MODULE_PARM_DESC(bs, "BS[2:0] Bias voltage level: 0-7 (default: 4)");

अटल पूर्णांक init_display(काष्ठा fbtft_par *par)
अणु
	par->fbtftops.reset(par);

	/* Function set
	 *
	 * 5:1  1
	 * 2:0  PD - Powerकरोwn control: chip is active
	 * 1:0  V  - Entry mode: horizontal addressing
	 * 0:1  H  - Extended inकाष्ठाion set control: extended
	 */
	ग_लिखो_reg(par, 0x21);

	/* H=1 Temperature control
	 *
	 * 2:1  1
	 * 1:x  TC1 - Temperature Coefficient: 0x10
	 * 0:x  TC0
	 */
	ग_लिखो_reg(par, 0x04 | (tc & 0x3));

	/* H=1 Bias प्रणाली
	 *
	 * 4:1  1
	 * 3:0  0
	 * 2:x  BS2 - Bias System
	 * 1:x  BS1
	 * 0:x  BS0
	 */
	ग_लिखो_reg(par, 0x10 | (bs & 0x7));

	/* Function set
	 *
	 * 5:1  1
	 * 2:0  PD - Powerकरोwn control: chip is active
	 * 1:1  V  - Entry mode: vertical addressing
	 * 0:0  H  - Extended inकाष्ठाion set control: basic
	 */
	ग_लिखो_reg(par, 0x22);

	/* H=0 Display control
	 *
	 * 3:1  1
	 * 2:1  D  - DE: 10=normal mode
	 * 1:0  0
	 * 0:0  E
	 */
	ग_लिखो_reg(par, 0x08 | 4);

	वापस 0;
पूर्ण

अटल व्योम set_addr_win(काष्ठा fbtft_par *par, पूर्णांक xs, पूर्णांक ys, पूर्णांक xe, पूर्णांक ye)
अणु
	/* H=0 Set X address of RAM
	 *
	 * 7:1  1
	 * 6-0: X[6:0] - 0x00
	 */
	ग_लिखो_reg(par, 0x80);

	/* H=0 Set Y address of RAM
	 *
	 * 7:0  0
	 * 6:1  1
	 * 2-0: Y[2:0] - 0x0
	 */
	ग_लिखो_reg(par, 0x40);
पूर्ण

अटल पूर्णांक ग_लिखो_vmem(काष्ठा fbtft_par *par, माप_प्रकार offset, माप_प्रकार len)
अणु
	u16 *vmem16 = (u16 *)par->info->screen_buffer;
	u8 *buf = par->txbuf.buf;
	पूर्णांक x, y, i;
	पूर्णांक ret = 0;

	क्रम (x = 0; x < 84; x++) अणु
		क्रम (y = 0; y < 6; y++) अणु
			*buf = 0x00;
			क्रम (i = 0; i < 8; i++)
				*buf |= (vmem16[(y * 8 + i) * 84 + x] ?
					 1 : 0) << i;
			buf++;
		पूर्ण
	पूर्ण

	/* Write data */
	gpiod_set_value(par->gpio.dc, 1);
	ret = par->fbtftops.ग_लिखो(par, par->txbuf.buf, 6 * 84);
	अगर (ret < 0)
		dev_err(par->info->device, "write failed and returned: %d\n",
			ret);

	वापस ret;
पूर्ण

अटल पूर्णांक set_gamma(काष्ठा fbtft_par *par, u32 *curves)
अणु
	/* apply mask */
	curves[0] &= 0x7F;

	ग_लिखो_reg(par, 0x23); /* turn on extended inकाष्ठाion set */
	ग_लिखो_reg(par, 0x80 | curves[0]);
	ग_लिखो_reg(par, 0x22); /* turn off extended inकाष्ठाion set */

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

FBTFT_REGISTER_DRIVER(DRVNAME, "philips,pcd8544", &display);

MODULE_ALIAS("spi:" DRVNAME);
MODULE_ALIAS("spi:pcd8544");

MODULE_DESCRIPTION("FB driver for the PCD8544 LCD Controller");
MODULE_AUTHOR("Noralf Tronnes");
MODULE_LICENSE("GPL");
