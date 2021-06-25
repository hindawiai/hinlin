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

#घोषणा DRVNAME		"fb_upd161704"
#घोषणा WIDTH		240
#घोषणा HEIGHT		320
#घोषणा BPP		16

अटल पूर्णांक init_display(काष्ठा fbtft_par *par)
अणु
	par->fbtftops.reset(par);

	अगर (par->gpio.cs)
		gpiod_set_value(par->gpio.cs, 0);  /* Activate chip */

	/* Initialization sequence from Lib_UTFT */

	/* रेजिस्टर reset */
	ग_लिखो_reg(par, 0x0003, 0x0001);	/* Soft reset */

	/* oscillator start */
	ग_लिखो_reg(par, 0x003A, 0x0001);	/*Oscillator 0: stop, 1: operation */
	udelay(100);

	/* y-setting */
	ग_लिखो_reg(par, 0x0024, 0x007B);	/* amplitude setting */
	udelay(10);
	ग_लिखो_reg(par, 0x0025, 0x003B);	/* amplitude setting */
	ग_लिखो_reg(par, 0x0026, 0x0034);	/* amplitude setting */
	udelay(10);
	ग_लिखो_reg(par, 0x0027, 0x0004);	/* amplitude setting */
	ग_लिखो_reg(par, 0x0052, 0x0025);	/* circuit setting 1 */
	udelay(10);
	ग_लिखो_reg(par, 0x0053, 0x0033);	/* circuit setting 2 */
	ग_लिखो_reg(par, 0x0061, 0x001C);	/* adjusपंचांगent V10 positive polarity */
	udelay(10);
	ग_लिखो_reg(par, 0x0062, 0x002C);	/* adjusपंचांगent V9 negative polarity */
	ग_लिखो_reg(par, 0x0063, 0x0022);	/* adjusपंचांगent V34 positive polarity */
	udelay(10);
	ग_लिखो_reg(par, 0x0064, 0x0027);	/* adjusपंचांगent V31 negative polarity */
	udelay(10);
	ग_लिखो_reg(par, 0x0065, 0x0014);	/* adjusपंचांगent V61 negative polarity */
	udelay(10);
	ग_लिखो_reg(par, 0x0066, 0x0010);	/* adjusपंचांगent V61 negative polarity */

	/* Basical घड़ी क्रम 1 line (BASECOUNT[7:0]) number specअगरied */
	ग_लिखो_reg(par, 0x002E, 0x002D);

	/* Power supply setting */
	ग_लिखो_reg(par, 0x0019, 0x0000);	/* DC/DC output setting */
	udelay(200);
	ग_लिखो_reg(par, 0x001A, 0x1000);	/* DC/DC frequency setting */
	ग_लिखो_reg(par, 0x001B, 0x0023);	/* DC/DC rising setting */
	ग_लिखो_reg(par, 0x001C, 0x0C01);	/* Regulator voltage setting */
	ग_लिखो_reg(par, 0x001D, 0x0000);	/* Regulator current setting */
	ग_लिखो_reg(par, 0x001E, 0x0009);	/* VCOM output setting */
	ग_लिखो_reg(par, 0x001F, 0x0035);	/* VCOM amplitude setting */
	ग_लिखो_reg(par, 0x0020, 0x0015);	/* VCOMM cencter setting */
	ग_लिखो_reg(par, 0x0018, 0x1E7B);	/* DC/DC operation setting */

	/* winकरोws setting */
	ग_लिखो_reg(par, 0x0008, 0x0000);	/* Minimum X address */
	ग_लिखो_reg(par, 0x0009, 0x00EF);	/* Maximum X address */
	ग_लिखो_reg(par, 0x000a, 0x0000);	/* Minimum Y address */
	ग_लिखो_reg(par, 0x000b, 0x013F);	/* Maximum Y address */

	/* LCD display area setting */
	ग_लिखो_reg(par, 0x0029, 0x0000);	/* [LCDSIZE]  X MIN. size set */
	ग_लिखो_reg(par, 0x002A, 0x0000);	/* [LCDSIZE]  Y MIN. size set */
	ग_लिखो_reg(par, 0x002B, 0x00EF);	/* [LCDSIZE]  X MAX. size set */
	ग_लिखो_reg(par, 0x002C, 0x013F);	/* [LCDSIZE]  Y MAX. size set */

	/* Gate scan setting */
	ग_लिखो_reg(par, 0x0032, 0x0002);

	/* n line inversion line number */
	ग_लिखो_reg(par, 0x0033, 0x0000);

	/* Line inversion/frame inversion/पूर्णांकerlace setting */
	ग_लिखो_reg(par, 0x0037, 0x0000);

	/* Gate scan operation setting रेजिस्टर */
	ग_लिखो_reg(par, 0x003B, 0x0001);

	/* Color mode */
	/*GS = 0: 260-k color (64 gray scale), GS = 1: 8 color (2 gray scale) */
	ग_लिखो_reg(par, 0x0004, 0x0000);

	/* RAM control रेजिस्टर */
	ग_लिखो_reg(par, 0x0005, 0x0000);	/*Winकरोw access 00:Normal, 10:Winकरोw */

	/* Display setting रेजिस्टर 2 */
	ग_लिखो_reg(par, 0x0001, 0x0000);

	/* display setting */
	ग_लिखो_reg(par, 0x0000, 0x0000);	/* display on */

	वापस 0;
पूर्ण

अटल व्योम set_addr_win(काष्ठा fbtft_par *par, पूर्णांक xs, पूर्णांक ys, पूर्णांक xe, पूर्णांक ye)
अणु
	चयन (par->info->var.rotate) अणु
	/* R20h = Horizontal GRAM Start Address */
	/* R21h = Vertical GRAM Start Address */
	हाल 0:
		ग_लिखो_reg(par, 0x0006, xs);
		ग_लिखो_reg(par, 0x0007, ys);
		अवरोध;
	हाल 180:
		ग_लिखो_reg(par, 0x0006, WIDTH - 1 - xs);
		ग_लिखो_reg(par, 0x0007, HEIGHT - 1 - ys);
		अवरोध;
	हाल 270:
		ग_लिखो_reg(par, 0x0006, WIDTH - 1 - ys);
		ग_लिखो_reg(par, 0x0007, xs);
		अवरोध;
	हाल 90:
		ग_लिखो_reg(par, 0x0006, ys);
		ग_लिखो_reg(par, 0x0007, HEIGHT - 1 - xs);
		अवरोध;
	पूर्ण

	ग_लिखो_reg(par, 0x0e); /* Write Data to GRAM */
पूर्ण

अटल पूर्णांक set_var(काष्ठा fbtft_par *par)
अणु
	चयन (par->info->var.rotate) अणु
	/* AM: GRAM update direction */
	हाल 0:
		ग_लिखो_reg(par, 0x01, 0x0000);
		ग_लिखो_reg(par, 0x05, 0x0000);
		अवरोध;
	हाल 180:
		ग_लिखो_reg(par, 0x01, 0x00C0);
		ग_लिखो_reg(par, 0x05, 0x0000);
		अवरोध;
	हाल 270:
		ग_लिखो_reg(par, 0x01, 0x0080);
		ग_लिखो_reg(par, 0x05, 0x0001);
		अवरोध;
	हाल 90:
		ग_लिखो_reg(par, 0x01, 0x0040);
		ग_लिखो_reg(par, 0x05, 0x0001);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा fbtft_display display = अणु
	.regwidth = 16,
	.width = WIDTH,
	.height = HEIGHT,
	.fbtftops = अणु
		.init_display = init_display,
		.set_addr_win = set_addr_win,
		.set_var = set_var,
	पूर्ण,
पूर्ण;

FBTFT_REGISTER_DRIVER(DRVNAME, "nec,upd161704", &display);

MODULE_ALIAS("spi:" DRVNAME);
MODULE_ALIAS("platform:" DRVNAME);
MODULE_ALIAS("spi:upd161704");
MODULE_ALIAS("platform:upd161704");

MODULE_DESCRIPTION("FB driver for the uPD161704 LCD Controller");
MODULE_AUTHOR("Seong-Woo Kim");
MODULE_LICENSE("GPL");
