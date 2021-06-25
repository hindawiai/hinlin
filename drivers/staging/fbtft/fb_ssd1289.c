<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * FB driver क्रम the SSD1289 LCD Controller
 *
 * Copyright (C) 2013 Noralf Tronnes
 *
 * Init sequence taken from ITDB02_Graph16.cpp - (C)2010-2011 Henning Karlsen
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/gpio/consumer.h>

#समावेश "fbtft.h"

#घोषणा DRVNAME		"fb_ssd1289"
#घोषणा WIDTH		240
#घोषणा HEIGHT		320
#घोषणा DEFAULT_GAMMA	"02 03 2 5 7 7 4 2 4 2\n" \
			"02 03 2 5 7 5 4 2 4 2"

अटल अचिन्हित पूर्णांक reg11 = 0x6040;
module_param(reg11, uपूर्णांक, 0000);
MODULE_PARM_DESC(reg11, "Register 11h value");

अटल पूर्णांक init_display(काष्ठा fbtft_par *par)
अणु
	par->fbtftops.reset(par);

	अगर (par->gpio.cs)
		gpiod_set_value(par->gpio.cs, 0);  /* Activate chip */

	ग_लिखो_reg(par, 0x00, 0x0001);
	ग_लिखो_reg(par, 0x03, 0xA8A4);
	ग_लिखो_reg(par, 0x0C, 0x0000);
	ग_लिखो_reg(par, 0x0D, 0x080C);
	ग_लिखो_reg(par, 0x0E, 0x2B00);
	ग_लिखो_reg(par, 0x1E, 0x00B7);
	ग_लिखो_reg(par, 0x01,
		  BIT(13) | (par->bgr << 11) | BIT(9) | (HEIGHT - 1));
	ग_लिखो_reg(par, 0x02, 0x0600);
	ग_लिखो_reg(par, 0x10, 0x0000);
	ग_लिखो_reg(par, 0x05, 0x0000);
	ग_लिखो_reg(par, 0x06, 0x0000);
	ग_लिखो_reg(par, 0x16, 0xEF1C);
	ग_लिखो_reg(par, 0x17, 0x0003);
	ग_लिखो_reg(par, 0x07, 0x0233);
	ग_लिखो_reg(par, 0x0B, 0x0000);
	ग_लिखो_reg(par, 0x0F, 0x0000);
	ग_लिखो_reg(par, 0x41, 0x0000);
	ग_लिखो_reg(par, 0x42, 0x0000);
	ग_लिखो_reg(par, 0x48, 0x0000);
	ग_लिखो_reg(par, 0x49, 0x013F);
	ग_लिखो_reg(par, 0x4A, 0x0000);
	ग_लिखो_reg(par, 0x4B, 0x0000);
	ग_लिखो_reg(par, 0x44, 0xEF00);
	ग_लिखो_reg(par, 0x45, 0x0000);
	ग_लिखो_reg(par, 0x46, 0x013F);
	ग_लिखो_reg(par, 0x23, 0x0000);
	ग_लिखो_reg(par, 0x24, 0x0000);
	ग_लिखो_reg(par, 0x25, 0x8000);
	ग_लिखो_reg(par, 0x4f, 0x0000);
	ग_लिखो_reg(par, 0x4e, 0x0000);
	ग_लिखो_reg(par, 0x22);
	वापस 0;
पूर्ण

अटल व्योम set_addr_win(काष्ठा fbtft_par *par, पूर्णांक xs, पूर्णांक ys, पूर्णांक xe, पूर्णांक ye)
अणु
	चयन (par->info->var.rotate) अणु
	/* R4Eh - Set GDDRAM X address counter */
	/* R4Fh - Set GDDRAM Y address counter */
	हाल 0:
		ग_लिखो_reg(par, 0x4e, xs);
		ग_लिखो_reg(par, 0x4f, ys);
		अवरोध;
	हाल 180:
		ग_लिखो_reg(par, 0x4e, par->info->var.xres - 1 - xs);
		ग_लिखो_reg(par, 0x4f, par->info->var.yres - 1 - ys);
		अवरोध;
	हाल 270:
		ग_लिखो_reg(par, 0x4e, par->info->var.yres - 1 - ys);
		ग_लिखो_reg(par, 0x4f, xs);
		अवरोध;
	हाल 90:
		ग_लिखो_reg(par, 0x4e, ys);
		ग_लिखो_reg(par, 0x4f, par->info->var.xres - 1 - xs);
		अवरोध;
	पूर्ण

	/* R22h - RAM data ग_लिखो */
	ग_लिखो_reg(par, 0x22);
पूर्ण

अटल पूर्णांक set_var(काष्ठा fbtft_par *par)
अणु
	अगर (par->fbtftops.init_display != init_display) अणु
		/* करोn't risk messing up रेजिस्टर 11h */
		fbtft_par_dbg(DEBUG_INIT_DISPLAY, par,
			      "%s: skipping since custom init_display() is used\n",
			      __func__);
		वापस 0;
	पूर्ण

	चयन (par->info->var.rotate) अणु
	हाल 0:
		ग_लिखो_reg(par, 0x11, reg11 | 0x30);
		अवरोध;
	हाल 270:
		ग_लिखो_reg(par, 0x11, reg11 | 0x28);
		अवरोध;
	हाल 180:
		ग_लिखो_reg(par, 0x11, reg11 | 0x00);
		अवरोध;
	हाल 90:
		ग_लिखो_reg(par, 0x11, reg11 | 0x18);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Gamma string क्रमmat:
 * VRP0 VRP1 PRP0 PRP1 PKP0 PKP1 PKP2 PKP3 PKP4 PKP5
 * VRN0 VRN1 PRN0 PRN1 PKN0 PKN1 PKN2 PKN3 PKN4 PKN5
 */
#घोषणा CURVE(num, idx)  curves[(num) * par->gamma.num_values + (idx)]
अटल पूर्णांक set_gamma(काष्ठा fbtft_par *par, u32 *curves)
अणु
	अटल स्थिर अचिन्हित दीर्घ mask[] = अणु
		0x1f, 0x1f, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07,
		0x1f, 0x1f, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07,
	पूर्ण;
	पूर्णांक i, j;

	/* apply mask */
	क्रम (i = 0; i < 2; i++)
		क्रम (j = 0; j < 10; j++)
			CURVE(i, j) &= mask[i * par->gamma.num_values + j];

	ग_लिखो_reg(par, 0x0030, CURVE(0, 5) << 8 | CURVE(0, 4));
	ग_लिखो_reg(par, 0x0031, CURVE(0, 7) << 8 | CURVE(0, 6));
	ग_लिखो_reg(par, 0x0032, CURVE(0, 9) << 8 | CURVE(0, 8));
	ग_लिखो_reg(par, 0x0033, CURVE(0, 3) << 8 | CURVE(0, 2));
	ग_लिखो_reg(par, 0x0034, CURVE(1, 5) << 8 | CURVE(1, 4));
	ग_लिखो_reg(par, 0x0035, CURVE(1, 7) << 8 | CURVE(1, 6));
	ग_लिखो_reg(par, 0x0036, CURVE(1, 9) << 8 | CURVE(1, 8));
	ग_लिखो_reg(par, 0x0037, CURVE(1, 3) << 8 | CURVE(1, 2));
	ग_लिखो_reg(par, 0x003A, CURVE(0, 1) << 8 | CURVE(0, 0));
	ग_लिखो_reg(par, 0x003B, CURVE(1, 1) << 8 | CURVE(1, 0));

	वापस 0;
पूर्ण

#अघोषित CURVE

अटल काष्ठा fbtft_display display = अणु
	.regwidth = 16,
	.width = WIDTH,
	.height = HEIGHT,
	.gamma_num = 2,
	.gamma_len = 10,
	.gamma = DEFAULT_GAMMA,
	.fbtftops = अणु
		.init_display = init_display,
		.set_addr_win = set_addr_win,
		.set_var = set_var,
		.set_gamma = set_gamma,
	पूर्ण,
पूर्ण;

FBTFT_REGISTER_DRIVER(DRVNAME, "solomon,ssd1289", &display);

MODULE_ALIAS("spi:" DRVNAME);
MODULE_ALIAS("platform:" DRVNAME);
MODULE_ALIAS("spi:ssd1289");
MODULE_ALIAS("platform:ssd1289");

MODULE_DESCRIPTION("FB driver for the SSD1289 LCD Controller");
MODULE_AUTHOR("Noralf Tronnes");
MODULE_LICENSE("GPL");
