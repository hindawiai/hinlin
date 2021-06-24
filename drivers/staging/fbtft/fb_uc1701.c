<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * FB driver क्रम the UC1701 LCD Controller
 *
 * The display is monochrome and the video memory is RGB565.
 * Any pixel value except 0 turns the pixel on.
 *
 * Copyright (C) 2014 Juergen Holzmann
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/delay.h>

#समावेश "fbtft.h"

#घोषणा DRVNAME	"fb_uc1701"
#घोषणा WIDTH	  102
#घोषणा HEIGHT	 64
#घोषणा PAGES	  (HEIGHT / 8)

/* 1: Display on/off */
#घोषणा LCD_DISPLAY_ENABLE    0xAE
/* 2: display start line set */
#घोषणा LCD_START_LINE	0x40
/* 3: Page address set (lower 4 bits select one of the pages) */
#घोषणा LCD_PAGE_ADDRESS      0xB0
/* 4: column address */
#घोषणा LCD_COL_ADDRESS       0x10
/* 8: select orientation */
#घोषणा LCD_BOTTOMVIEW	0xA0
/* 9: inverted display */
#घोषणा LCD_DISPLAY_INVERT    0xA6
/* 10: show memory content or चयन all pixels on */
#घोषणा LCD_ALL_PIXEL	 0xA4
/* 11: lcd bias set */
#घोषणा LCD_BIAS	      0xA2
/* 14: Reset Controller */
#घोषणा LCD_RESET_CMD	 0xE2
/* 15: output mode select (turns display upside-करोwn) */
#घोषणा LCD_SCAN_सूची	  0xC0
/* 16: घातer control set */
#घोषणा LCD_POWER_CONTROL     0x28
/* 17: voltage regulator resistor ratio set */
#घोषणा LCD_VOLTAGE	   0x20
/* 18: Volume mode set */
#घोषणा LCD_VOLUME_MODE       0x81
/* 22: NOP command */
#घोषणा LCD_NO_OP	     0xE3
/* 25: advanced program control */
#घोषणा LCD_ADV_PROG_CTRL     0xFA
/* 25: advanced program control2 */
#घोषणा LCD_ADV_PROG_CTRL2    0x10
#घोषणा LCD_TEMPCOMP_HIGH     0x80
/* column offset क्रम normal orientation */
#घोषणा SHIFT_ADDR_NORMAL     0
/* column offset क्रम bottom view orientation */
#घोषणा SHIFT_ADDR_TOPVIEW    30

अटल पूर्णांक init_display(काष्ठा fbtft_par *par)
अणु
	par->fbtftops.reset(par);

	/* softreset of LCD */
	ग_लिखो_reg(par, LCD_RESET_CMD);
	mdelay(10);

	/* set startpoपूर्णांक */
	ग_लिखो_reg(par, LCD_START_LINE);

	/* select orientation BOTTOMVIEW */
	ग_लिखो_reg(par, LCD_BOTTOMVIEW | 1);

	/* output mode select (turns display upside-करोwn) */
	ग_लिखो_reg(par, LCD_SCAN_सूची | 0x00);

	/* Normal Pixel mode */
	ग_लिखो_reg(par, LCD_ALL_PIXEL | 0);

	/* positive display */
	ग_लिखो_reg(par, LCD_DISPLAY_INVERT | 0);

	/* bias 1/9 */
	ग_लिखो_reg(par, LCD_BIAS | 0);

	/* घातer control mode: all features on */
	ग_लिखो_reg(par, LCD_POWER_CONTROL | 0x07);

	/* set voltage regulator R/R */
	ग_लिखो_reg(par, LCD_VOLTAGE | 0x07);

	/* volume mode set */
	ग_लिखो_reg(par, LCD_VOLUME_MODE);
	ग_लिखो_reg(par, 0x09);
	ग_लिखो_reg(par, LCD_NO_OP);

	/* advanced program control */
	ग_लिखो_reg(par, LCD_ADV_PROG_CTRL);
	ग_लिखो_reg(par, LCD_ADV_PROG_CTRL2 | LCD_TEMPCOMP_HIGH);

	/* enable display */
	ग_लिखो_reg(par, LCD_DISPLAY_ENABLE | 1);

	वापस 0;
पूर्ण

अटल व्योम set_addr_win(काष्ठा fbtft_par *par, पूर्णांक xs, पूर्णांक ys, पूर्णांक xe, पूर्णांक ye)
अणु
	/* जाओ address */
	ग_लिखो_reg(par, LCD_PAGE_ADDRESS);
	ग_लिखो_reg(par, 0x00);
	ग_लिखो_reg(par, LCD_COL_ADDRESS);
पूर्ण

अटल पूर्णांक ग_लिखो_vmem(काष्ठा fbtft_par *par, माप_प्रकार offset, माप_प्रकार len)
अणु
	u16 *vmem16 = (u16 *)par->info->screen_buffer;
	u8 *buf;
	पूर्णांक x, y, i;
	पूर्णांक ret = 0;

	क्रम (y = 0; y < PAGES; y++) अणु
		buf = par->txbuf.buf;
		क्रम (x = 0; x < WIDTH; x++) अणु
			*buf = 0x00;
			क्रम (i = 0; i < 8; i++)
				*buf |= (vmem16[((y * 8 * WIDTH) +
						 (i * WIDTH)) + x] ?
					 1 : 0) << i;
			buf++;
		पूर्ण

		ग_लिखो_reg(par, LCD_PAGE_ADDRESS | (u8)y);
		ग_लिखो_reg(par, 0x00);
		ग_लिखो_reg(par, LCD_COL_ADDRESS);
		gpiod_set_value(par->gpio.dc, 1);
		ret = par->fbtftops.ग_लिखो(par, par->txbuf.buf, WIDTH);
		gpiod_set_value(par->gpio.dc, 0);
	पूर्ण

	अगर (ret < 0)
		dev_err(par->info->device, "write failed and returned: %d\n",
			ret);

	वापस ret;
पूर्ण

अटल काष्ठा fbtft_display display = अणु
	.regwidth = 8,
	.width = WIDTH,
	.height = HEIGHT,
	.fbtftops = अणु
		.init_display = init_display,
		.set_addr_win = set_addr_win,
		.ग_लिखो_vmem = ग_लिखो_vmem,
	पूर्ण,
	.backlight = 1,
पूर्ण;

FBTFT_REGISTER_DRIVER(DRVNAME, "UltraChip,uc1701", &display);

MODULE_ALIAS("spi:" DRVNAME);
MODULE_ALIAS("spi:uc1701");

MODULE_DESCRIPTION("FB driver for the UC1701 LCD Controller");
MODULE_AUTHOR("Juergen Holzmann");
MODULE_LICENSE("GPL");
