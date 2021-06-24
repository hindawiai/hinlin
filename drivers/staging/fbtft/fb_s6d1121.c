<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * FB driver क्रम the S6D1121 LCD Controller
 *
 * Copyright (C) 2013 Roman Rolinsky
 *
 * Based on fb_ili9325.c by Noralf Tronnes
 * Based on ili9325.c by Jeroen Domburg
 * Init code from UTFT library by Henning Karlsen
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/delay.h>

#समावेश "fbtft.h"

#घोषणा DRVNAME		"fb_s6d1121"
#घोषणा WIDTH		240
#घोषणा HEIGHT		320
#घोषणा BPP		16
#घोषणा FPS		20
#घोषणा DEFAULT_GAMMA	"26 09 24 2C 1F 23 24 25 22 26 25 23 0D 00\n" \
			"1C 1A 13 1D 0B 11 12 10 13 15 36 19 00 0D"

अटल पूर्णांक init_display(काष्ठा fbtft_par *par)
अणु
	par->fbtftops.reset(par);

	अगर (par->gpio.cs)
		gpiod_set_value(par->gpio.cs, 0);  /* Activate chip */

	/* Initialization sequence from Lib_UTFT */

	ग_लिखो_reg(par, 0x0011, 0x2004);
	ग_लिखो_reg(par, 0x0013, 0xCC00);
	ग_लिखो_reg(par, 0x0015, 0x2600);
	ग_लिखो_reg(par, 0x0014, 0x252A);
	ग_लिखो_reg(par, 0x0012, 0x0033);
	ग_लिखो_reg(par, 0x0013, 0xCC04);
	ग_लिखो_reg(par, 0x0013, 0xCC06);
	ग_लिखो_reg(par, 0x0013, 0xCC4F);
	ग_लिखो_reg(par, 0x0013, 0x674F);
	ग_लिखो_reg(par, 0x0011, 0x2003);
	ग_लिखो_reg(par, 0x0016, 0x0007);
	ग_लिखो_reg(par, 0x0002, 0x0013);
	ग_लिखो_reg(par, 0x0003, 0x0003);
	ग_लिखो_reg(par, 0x0001, 0x0127);
	ग_लिखो_reg(par, 0x0008, 0x0303);
	ग_लिखो_reg(par, 0x000A, 0x000B);
	ग_लिखो_reg(par, 0x000B, 0x0003);
	ग_लिखो_reg(par, 0x000C, 0x0000);
	ग_लिखो_reg(par, 0x0041, 0x0000);
	ग_लिखो_reg(par, 0x0050, 0x0000);
	ग_लिखो_reg(par, 0x0060, 0x0005);
	ग_लिखो_reg(par, 0x0070, 0x000B);
	ग_लिखो_reg(par, 0x0071, 0x0000);
	ग_लिखो_reg(par, 0x0078, 0x0000);
	ग_लिखो_reg(par, 0x007A, 0x0000);
	ग_लिखो_reg(par, 0x0079, 0x0007);
	ग_लिखो_reg(par, 0x0007, 0x0051);
	ग_लिखो_reg(par, 0x0007, 0x0053);
	ग_लिखो_reg(par, 0x0079, 0x0000);

	ग_लिखो_reg(par, 0x0022); /* Write Data to GRAM */

	वापस 0;
पूर्ण

अटल व्योम set_addr_win(काष्ठा fbtft_par *par, पूर्णांक xs, पूर्णांक ys, पूर्णांक xe, पूर्णांक ye)
अणु
	चयन (par->info->var.rotate) अणु
	/* R20h = Horizontal GRAM Start Address */
	/* R21h = Vertical GRAM Start Address */
	हाल 0:
		ग_लिखो_reg(par, 0x0020, xs);
		ग_लिखो_reg(par, 0x0021, ys);
		अवरोध;
	हाल 180:
		ग_लिखो_reg(par, 0x0020, WIDTH - 1 - xs);
		ग_लिखो_reg(par, 0x0021, HEIGHT - 1 - ys);
		अवरोध;
	हाल 270:
		ग_लिखो_reg(par, 0x0020, WIDTH - 1 - ys);
		ग_लिखो_reg(par, 0x0021, xs);
		अवरोध;
	हाल 90:
		ग_लिखो_reg(par, 0x0020, ys);
		ग_लिखो_reg(par, 0x0021, HEIGHT - 1 - xs);
		अवरोध;
	पूर्ण
	ग_लिखो_reg(par, 0x0022); /* Write Data to GRAM */
पूर्ण

अटल पूर्णांक set_var(काष्ठा fbtft_par *par)
अणु
	चयन (par->info->var.rotate) अणु
	/* AM: GRAM update direction */
	हाल 0:
		ग_लिखो_reg(par, 0x03, 0x0003 | (par->bgr << 12));
		अवरोध;
	हाल 180:
		ग_लिखो_reg(par, 0x03, 0x0000 | (par->bgr << 12));
		अवरोध;
	हाल 270:
		ग_लिखो_reg(par, 0x03, 0x000A | (par->bgr << 12));
		अवरोध;
	हाल 90:
		ग_लिखो_reg(par, 0x03, 0x0009 | (par->bgr << 12));
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Gamma string क्रमmat:
 * PKP0 PKP1 PKP2 PKP3 PKP4 PKP5 PKP6 PKP7 PKP8 PKP9 PKP10 PKP11 VRP0 VRP1
 * PKN0 PKN1 PKN2 PKN3 PKN4 PKN5 PKN6 PKN7 PRN8 PRN9 PRN10 PRN11 VRN0 VRN1
 */
#घोषणा CURVE(num, idx)  curves[(num) * par->gamma.num_values + (idx)]
अटल पूर्णांक set_gamma(काष्ठा fbtft_par *par, u32 *curves)
अणु
	अटल स्थिर अचिन्हित दीर्घ mask[] = अणु
		0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f,
		0x3f, 0x3f, 0x1f, 0x1f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f,
		0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x1f, 0x1f,
	पूर्ण;
	पूर्णांक i, j;

	/* apply mask */
	क्रम (i = 0; i < 2; i++)
		क्रम (j = 0; j < 14; j++)
			CURVE(i, j) &= mask[i * par->gamma.num_values + j];

	ग_लिखो_reg(par, 0x0030, CURVE(0, 1) << 8 | CURVE(0, 0));
	ग_लिखो_reg(par, 0x0031, CURVE(0, 3) << 8 | CURVE(0, 2));
	ग_लिखो_reg(par, 0x0032, CURVE(0, 5) << 8 | CURVE(0, 3));
	ग_लिखो_reg(par, 0x0033, CURVE(0, 7) << 8 | CURVE(0, 6));
	ग_लिखो_reg(par, 0x0034, CURVE(0, 9) << 8 | CURVE(0, 8));
	ग_लिखो_reg(par, 0x0035, CURVE(0, 11) << 8 | CURVE(0, 10));

	ग_लिखो_reg(par, 0x0036, CURVE(1, 1) << 8 | CURVE(1, 0));
	ग_लिखो_reg(par, 0x0037, CURVE(1, 3) << 8 | CURVE(1, 2));
	ग_लिखो_reg(par, 0x0038, CURVE(1, 5) << 8 | CURVE(1, 4));
	ग_लिखो_reg(par, 0x0039, CURVE(1, 7) << 8 | CURVE(1, 6));
	ग_लिखो_reg(par, 0x003A, CURVE(1, 9) << 8 | CURVE(1, 8));
	ग_लिखो_reg(par, 0x003B, CURVE(1, 11) << 8 | CURVE(1, 10));

	ग_लिखो_reg(par, 0x003C, CURVE(0, 13) << 8 | CURVE(0, 12));
	ग_लिखो_reg(par, 0x003D, CURVE(1, 13) << 8 | CURVE(1, 12));

	वापस 0;
पूर्ण

#अघोषित CURVE

अटल काष्ठा fbtft_display display = अणु
	.regwidth = 16,
	.width = WIDTH,
	.height = HEIGHT,
	.bpp = BPP,
	.fps = FPS,
	.gamma_num = 2,
	.gamma_len = 14,
	.gamma = DEFAULT_GAMMA,
	.fbtftops = अणु
		.init_display = init_display,
		.set_addr_win = set_addr_win,
		.set_var = set_var,
		.set_gamma = set_gamma,
	पूर्ण,
पूर्ण;

FBTFT_REGISTER_DRIVER(DRVNAME, "samsung,s6d1121", &display);

MODULE_ALIAS("spi:" DRVNAME);
MODULE_ALIAS("platform:" DRVNAME);
MODULE_ALIAS("spi:s6d1121");
MODULE_ALIAS("platform:s6d1121");

MODULE_DESCRIPTION("FB driver for the S6D1121 LCD Controller");
MODULE_AUTHOR("Roman Rolinsky");
MODULE_LICENSE("GPL");
