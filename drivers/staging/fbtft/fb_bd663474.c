<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * FB driver क्रम the uPD161704 LCD Controller
 *
 * Copyright (C) 2014 Seong-Woo Kim
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

#घोषणा DRVNAME		"fb_bd663474"
#घोषणा WIDTH		240
#घोषणा HEIGHT		320
#घोषणा BPP		16

अटल पूर्णांक init_display(काष्ठा fbtft_par *par)
अणु
	अगर (par->gpio.cs)
		gpiod_set_value(par->gpio.cs, 0);  /* Activate chip */

	par->fbtftops.reset(par);

	/* Initialization sequence from Lib_UTFT */

	/* oscillator start */
	ग_लिखो_reg(par, 0x000, 0x0001);	/*oscillator 0: stop, 1: operation */
	mdelay(10);

	/* Power settings */
	ग_लिखो_reg(par, 0x100, 0x0000); /* घातer supply setup */
	ग_लिखो_reg(par, 0x101, 0x0000);
	ग_लिखो_reg(par, 0x102, 0x3110);
	ग_लिखो_reg(par, 0x103, 0xe200);
	ग_लिखो_reg(par, 0x110, 0x009d);
	ग_लिखो_reg(par, 0x111, 0x0022);
	ग_लिखो_reg(par, 0x100, 0x0120);
	mdelay(20);

	ग_लिखो_reg(par, 0x100, 0x3120);
	mdelay(80);
	/* Display control */
	ग_लिखो_reg(par, 0x001, 0x0100);
	ग_लिखो_reg(par, 0x002, 0x0000);
	ग_लिखो_reg(par, 0x003, 0x1230);
	ग_लिखो_reg(par, 0x006, 0x0000);
	ग_लिखो_reg(par, 0x007, 0x0101);
	ग_लिखो_reg(par, 0x008, 0x0808);
	ग_लिखो_reg(par, 0x009, 0x0000);
	ग_लिखो_reg(par, 0x00b, 0x0000);
	ग_लिखो_reg(par, 0x00c, 0x0000);
	ग_लिखो_reg(par, 0x00d, 0x0018);
	/* LTPS control settings */
	ग_लिखो_reg(par, 0x012, 0x0000);
	ग_लिखो_reg(par, 0x013, 0x0000);
	ग_लिखो_reg(par, 0x018, 0x0000);
	ग_लिखो_reg(par, 0x019, 0x0000);

	ग_लिखो_reg(par, 0x203, 0x0000);
	ग_लिखो_reg(par, 0x204, 0x0000);

	ग_लिखो_reg(par, 0x210, 0x0000);
	ग_लिखो_reg(par, 0x211, 0x00ef);
	ग_लिखो_reg(par, 0x212, 0x0000);
	ग_लिखो_reg(par, 0x213, 0x013f);
	ग_लिखो_reg(par, 0x214, 0x0000);
	ग_लिखो_reg(par, 0x215, 0x0000);
	ग_लिखो_reg(par, 0x216, 0x0000);
	ग_लिखो_reg(par, 0x217, 0x0000);

	/* Gray scale settings */
	ग_लिखो_reg(par, 0x300, 0x5343);
	ग_लिखो_reg(par, 0x301, 0x1021);
	ग_लिखो_reg(par, 0x302, 0x0003);
	ग_लिखो_reg(par, 0x303, 0x0011);
	ग_लिखो_reg(par, 0x304, 0x050a);
	ग_लिखो_reg(par, 0x305, 0x4342);
	ग_लिखो_reg(par, 0x306, 0x1100);
	ग_लिखो_reg(par, 0x307, 0x0003);
	ग_लिखो_reg(par, 0x308, 0x1201);
	ग_लिखो_reg(par, 0x309, 0x050a);

	/* RAM access settings */
	ग_लिखो_reg(par, 0x400, 0x4027);
	ग_लिखो_reg(par, 0x401, 0x0000);
	ग_लिखो_reg(par, 0x402, 0x0000);  /* First screen drive position (1) */
	ग_लिखो_reg(par, 0x403, 0x013f);  /* First screen drive position (2) */
	ग_लिखो_reg(par, 0x404, 0x0000);

	ग_लिखो_reg(par, 0x200, 0x0000);
	ग_लिखो_reg(par, 0x201, 0x0000);
	ग_लिखो_reg(par, 0x100, 0x7120);
	ग_लिखो_reg(par, 0x007, 0x0103);
	mdelay(10);
	ग_लिखो_reg(par, 0x007, 0x0113);

	वापस 0;
पूर्ण

अटल व्योम set_addr_win(काष्ठा fbtft_par *par, पूर्णांक xs, पूर्णांक ys, पूर्णांक xe, पूर्णांक ye)
अणु
	चयन (par->info->var.rotate) अणु
	/* R200h = Horizontal GRAM Start Address */
	/* R201h = Vertical GRAM Start Address */
	हाल 0:
		ग_लिखो_reg(par, 0x0200, xs);
		ग_लिखो_reg(par, 0x0201, ys);
		अवरोध;
	हाल 180:
		ग_लिखो_reg(par, 0x0200, WIDTH - 1 - xs);
		ग_लिखो_reg(par, 0x0201, HEIGHT - 1 - ys);
		अवरोध;
	हाल 270:
		ग_लिखो_reg(par, 0x0200, WIDTH - 1 - ys);
		ग_लिखो_reg(par, 0x0201, xs);
		अवरोध;
	हाल 90:
		ग_लिखो_reg(par, 0x0200, ys);
		ग_लिखो_reg(par, 0x0201, HEIGHT - 1 - xs);
		अवरोध;
	पूर्ण
	ग_लिखो_reg(par, 0x202); /* Write Data to GRAM */
पूर्ण

अटल पूर्णांक set_var(काष्ठा fbtft_par *par)
अणु
	चयन (par->info->var.rotate) अणु
	/* AM: GRAM update direction */
	हाल 0:
		ग_लिखो_reg(par, 0x003, 0x1230);
		अवरोध;
	हाल 180:
		ग_लिखो_reg(par, 0x003, 0x1200);
		अवरोध;
	हाल 270:
		ग_लिखो_reg(par, 0x003, 0x1228);
		अवरोध;
	हाल 90:
		ग_लिखो_reg(par, 0x003, 0x1218);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा fbtft_display display = अणु
	.regwidth = 16,
	.width = WIDTH,
	.height = HEIGHT,
	.bpp = BPP,
	.fbtftops = अणु
		.init_display = init_display,
		.set_addr_win = set_addr_win,
		.set_var = set_var,
	पूर्ण,
पूर्ण;

FBTFT_REGISTER_DRIVER(DRVNAME, "hitachi,bd663474", &display);

MODULE_ALIAS("spi:" DRVNAME);
MODULE_ALIAS("platform:" DRVNAME);
MODULE_ALIAS("spi:bd663474");
MODULE_ALIAS("platform:bd663474");

MODULE_DESCRIPTION("FB driver for the uPD161704 LCD Controller");
MODULE_AUTHOR("Seong-Woo Kim");
MODULE_LICENSE("GPL");
