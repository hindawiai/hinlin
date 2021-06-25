<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * FB driver क्रम the HX8347D LCD Controller
 *
 * Copyright (C) 2013 Christian Vogelgsang
 *
 * Based on driver code found here: https://github.com/watterott/r61505u-Adapter
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>

#समावेश "fbtft.h"

#घोषणा DRVNAME		"fb_hx8347d"
#घोषणा WIDTH		320
#घोषणा HEIGHT		240
#घोषणा DEFAULT_GAMMA	"0 0 0 0 0 0 0 0 0 0 0 0 0 0\n" \
			"0 0 0 0 0 0 0 0 0 0 0 0 0 0"

अटल पूर्णांक init_display(काष्ठा fbtft_par *par)
अणु
	par->fbtftops.reset(par);

	/* driving ability */
	ग_लिखो_reg(par, 0xEA, 0x00);
	ग_लिखो_reg(par, 0xEB, 0x20);
	ग_लिखो_reg(par, 0xEC, 0x0C);
	ग_लिखो_reg(par, 0xED, 0xC4);
	ग_लिखो_reg(par, 0xE8, 0x40);
	ग_लिखो_reg(par, 0xE9, 0x38);
	ग_लिखो_reg(par, 0xF1, 0x01);
	ग_लिखो_reg(par, 0xF2, 0x10);
	ग_लिखो_reg(par, 0x27, 0xA3);

	/* घातer voltage */
	ग_लिखो_reg(par, 0x1B, 0x1B);
	ग_लिखो_reg(par, 0x1A, 0x01);
	ग_लिखो_reg(par, 0x24, 0x2F);
	ग_लिखो_reg(par, 0x25, 0x57);

	/* VCOM offset */
	ग_लिखो_reg(par, 0x23, 0x8D); /* क्रम flicker adjust */

	/* घातer on */
	ग_लिखो_reg(par, 0x18, 0x36);
	ग_लिखो_reg(par, 0x19, 0x01); /* start osc */
	ग_लिखो_reg(par, 0x01, 0x00); /* wakeup */
	ग_लिखो_reg(par, 0x1F, 0x88);
	mdelay(5);
	ग_लिखो_reg(par, 0x1F, 0x80);
	mdelay(5);
	ग_लिखो_reg(par, 0x1F, 0x90);
	mdelay(5);
	ग_लिखो_reg(par, 0x1F, 0xD0);
	mdelay(5);

	/* color selection */
	ग_लिखो_reg(par, 0x17, 0x05); /* 65k */

	/*panel अक्षरacteristic */
	ग_लिखो_reg(par, 0x36, 0x00);

	/*display on */
	ग_लिखो_reg(par, 0x28, 0x38);
	mdelay(40);
	ग_लिखो_reg(par, 0x28, 0x3C);

	/* orientation */
	ग_लिखो_reg(par, 0x16, 0x60 | (par->bgr << 3));

	वापस 0;
पूर्ण

अटल व्योम set_addr_win(काष्ठा fbtft_par *par, पूर्णांक xs, पूर्णांक ys, पूर्णांक xe, पूर्णांक ye)
अणु
	ग_लिखो_reg(par, 0x02, (xs >> 8) & 0xFF);
	ग_लिखो_reg(par, 0x03, xs & 0xFF);
	ग_लिखो_reg(par, 0x04, (xe >> 8) & 0xFF);
	ग_लिखो_reg(par, 0x05, xe & 0xFF);
	ग_लिखो_reg(par, 0x06, (ys >> 8) & 0xFF);
	ग_लिखो_reg(par, 0x07, ys & 0xFF);
	ग_लिखो_reg(par, 0x08, (ye >> 8) & 0xFF);
	ग_लिखो_reg(par, 0x09, ye & 0xFF);
	ग_लिखो_reg(par, 0x22);
पूर्ण

/*
 * Gamma string क्रमmat:
 *   VRP0 VRP1 VRP2 VRP3 VRP4 VRP5 PRP0 PRP1 PKP0 PKP1 PKP2 PKP3 PKP4 CGM
 *   VRN0 VRN1 VRN2 VRN3 VRN4 VRN5 PRN0 PRN1 PKN0 PKN1 PKN2 PKN3 PKN4 CGM
 */
#घोषणा CURVE(num, idx)  curves[(num) * par->gamma.num_values + (idx)]
अटल पूर्णांक set_gamma(काष्ठा fbtft_par *par, u32 *curves)
अणु
	अटल स्थिर अचिन्हित दीर्घ mask[] = अणु
		0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x7f, 0x7f, 0x1f, 0x1f,
		0x1f, 0x1f, 0x1f, 0x0f,
	पूर्ण;
	पूर्णांक i, j;
	पूर्णांक acc = 0;

	/* apply mask */
	क्रम (i = 0; i < par->gamma.num_curves; i++)
		क्रम (j = 0; j < par->gamma.num_values; j++) अणु
			acc += CURVE(i, j);
			CURVE(i, j) &= mask[j];
		पूर्ण

	अगर (acc == 0) /* skip अगर all values are zero */
		वापस 0;

	क्रम (i = 0; i < par->gamma.num_curves; i++) अणु
		ग_लिखो_reg(par, 0x40 + (i * 0x10), CURVE(i, 0));
		ग_लिखो_reg(par, 0x41 + (i * 0x10), CURVE(i, 1));
		ग_लिखो_reg(par, 0x42 + (i * 0x10), CURVE(i, 2));
		ग_लिखो_reg(par, 0x43 + (i * 0x10), CURVE(i, 3));
		ग_लिखो_reg(par, 0x44 + (i * 0x10), CURVE(i, 4));
		ग_लिखो_reg(par, 0x45 + (i * 0x10), CURVE(i, 5));
		ग_लिखो_reg(par, 0x46 + (i * 0x10), CURVE(i, 6));
		ग_लिखो_reg(par, 0x47 + (i * 0x10), CURVE(i, 7));
		ग_लिखो_reg(par, 0x48 + (i * 0x10), CURVE(i, 8));
		ग_लिखो_reg(par, 0x49 + (i * 0x10), CURVE(i, 9));
		ग_लिखो_reg(par, 0x4A + (i * 0x10), CURVE(i, 10));
		ग_लिखो_reg(par, 0x4B + (i * 0x10), CURVE(i, 11));
		ग_लिखो_reg(par, 0x4C + (i * 0x10), CURVE(i, 12));
	पूर्ण
	ग_लिखो_reg(par, 0x5D, (CURVE(1, 0) << 4) | CURVE(0, 0));

	वापस 0;
पूर्ण

#अघोषित CURVE

अटल काष्ठा fbtft_display display = अणु
	.regwidth = 8,
	.width = WIDTH,
	.height = HEIGHT,
	.gamma_num = 2,
	.gamma_len = 14,
	.gamma = DEFAULT_GAMMA,
	.fbtftops = अणु
		.init_display = init_display,
		.set_addr_win = set_addr_win,
		.set_gamma = set_gamma,
	पूर्ण,
पूर्ण;

FBTFT_REGISTER_DRIVER(DRVNAME, "himax,hx8347d", &display);

MODULE_ALIAS("spi:" DRVNAME);
MODULE_ALIAS("platform:" DRVNAME);
MODULE_ALIAS("spi:hx8347d");
MODULE_ALIAS("platform:hx8347d");

MODULE_DESCRIPTION("FB driver for the HX8347D LCD Controller");
MODULE_AUTHOR("Christian Vogelgsang");
MODULE_LICENSE("GPL");
