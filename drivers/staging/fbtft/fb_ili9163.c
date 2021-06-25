<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * FB driver क्रम the ILI9163 LCD Controller
 *
 * Copyright (C) 2015 Kozhevnikov Anम_से_दy
 *
 * Based on ili9325.c by Noralf Tronnes and
 * .S.U.M.O.T.O.Y. by Max MC Costa (https://github.com/sumotoy/TFT_ILI9163C).
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/delay.h>
#समावेश <video/mipi_display.h>

#समावेश "fbtft.h"

#घोषणा DRVNAME		"fb_ili9163"
#घोषणा WIDTH		128
#घोषणा HEIGHT		128
#घोषणा BPP		16
#घोषणा FPS		30

#अगर_घोषित GAMMA_ADJ
#घोषणा GAMMA_LEN	15
#घोषणा GAMMA_NUM	1
#घोषणा DEFAULT_GAMMA	"36 29 12 22 1C 15 42 B7 2F 13 12 0A 11 0B 06\n"
#पूर्ण_अगर

/* ILI9163C commands */
#घोषणा CMD_FRMCTR1	0xB1 /* Frame Rate Control */
			     /*	(In normal mode/Full colors) */
#घोषणा CMD_FRMCTR2	0xB2 /* Frame Rate Control (In Idle mode/8-colors) */
#घोषणा CMD_FRMCTR3	0xB3 /* Frame Rate Control */
			     /*	(In Partial mode/full colors) */
#घोषणा CMD_DINVCTR	0xB4 /* Display Inversion Control */
#घोषणा CMD_RGBBLK	0xB5 /* RGB Interface Blanking Porch setting */
#घोषणा CMD_DFUNCTR	0xB6 /* Display Function set 5 */
#घोषणा CMD_SDRVसूची	0xB7 /* Source Driver Direction Control */
#घोषणा CMD_GDRVसूची	0xB8 /* Gate Driver Direction Control  */

#घोषणा CMD_PWCTR1	0xC0 /* Power_Control1 */
#घोषणा CMD_PWCTR2	0xC1 /* Power_Control2 */
#घोषणा CMD_PWCTR3	0xC2 /* Power_Control3 */
#घोषणा CMD_PWCTR4	0xC3 /* Power_Control4 */
#घोषणा CMD_PWCTR5	0xC4 /* Power_Control5 */
#घोषणा CMD_VCOMCTR1	0xC5 /* VCOM_Control 1 */
#घोषणा CMD_VCOMCTR2	0xC6 /* VCOM_Control 2 */
#घोषणा CMD_VCOMOFFS	0xC7 /* VCOM Offset Control */
#घोषणा CMD_PGAMMAC	0xE0 /* Positive Gamma Correction Setting */
#घोषणा CMD_NGAMMAC	0xE1 /* Negative Gamma Correction Setting */
#घोषणा CMD_GAMRSEL	0xF2 /* GAM_R_SEL */

/*
 * This display:
 * http://www.ebay.com/iपंचांग/Replace-Nokia-5110-LCD-1-44-Red-Serial-128X128-SPI-
 * Color-TFT-LCD-Display-Module-/271422122271
 * This particular display has a design error! The controller has 3 pins to
 * configure to स्थिरrain the memory and resolution to a fixed dimension (in
 * that हाल 128x128) but they leaved those pins configured क्रम 128x160 so
 * there was several pixel memory addressing problems.
 * I solved by setup several parameters that dinamically fix the resolution as
 * needit so below the parameters क्रम this display. If you have a strain or a
 * correct display (can happen with chinese) you can copy those parameters and
 * create setup क्रम dअगरferent displays.
 */

#अगर_घोषित RED
#घोषणा __OFFSET		32 /*see note 2 - this is the red version */
#अन्यथा
#घोषणा __OFFSET		0  /*see note 2 - this is the black version */
#पूर्ण_अगर

अटल पूर्णांक init_display(काष्ठा fbtft_par *par)
अणु
	par->fbtftops.reset(par);

	अगर (par->gpio.cs)
		gpiod_set_value(par->gpio.cs, 0);  /* Activate chip */

	ग_लिखो_reg(par, MIPI_DCS_SOFT_RESET); /* software reset */
	mdelay(500);
	ग_लिखो_reg(par, MIPI_DCS_EXIT_SLEEP_MODE); /* निकास sleep */
	mdelay(5);
	ग_लिखो_reg(par, MIPI_DCS_SET_PIXEL_FORMAT, MIPI_DCS_PIXEL_FMT_16BIT);
	/* शेष gamma curve 3 */
	ग_लिखो_reg(par, MIPI_DCS_SET_GAMMA_CURVE, 0x02);
#अगर_घोषित GAMMA_ADJ
	ग_लिखो_reg(par, CMD_GAMRSEL, 0x01); /* Enable Gamma adj */
#पूर्ण_अगर
	ग_लिखो_reg(par, MIPI_DCS_ENTER_NORMAL_MODE);
	ग_लिखो_reg(par, CMD_DFUNCTR, 0xff, 0x06);
	/* Frame Rate Control (In normal mode/Full colors) */
	ग_लिखो_reg(par, CMD_FRMCTR1, 0x08, 0x02);
	ग_लिखो_reg(par, CMD_DINVCTR, 0x07); /* display inversion  */
	/* Set VRH1[4:0] & VC[2:0] क्रम VCI1 & GVDD */
	ग_लिखो_reg(par, CMD_PWCTR1, 0x0A, 0x02);
	/* Set BT[2:0] क्रम AVDD & VCL & VGH & VGL  */
	ग_लिखो_reg(par, CMD_PWCTR2, 0x02);
	/* Set VMH[6:0] & VML[6:0] क्रम VOMH & VCOML */
	ग_लिखो_reg(par, CMD_VCOMCTR1, 0x50, 0x63);
	ग_लिखो_reg(par, CMD_VCOMOFFS, 0);

	ग_लिखो_reg(par, MIPI_DCS_SET_COLUMN_ADDRESS, 0, 0, 0, WIDTH);
	ग_लिखो_reg(par, MIPI_DCS_SET_PAGE_ADDRESS, 0, 0, 0, HEIGHT);

	ग_लिखो_reg(par, MIPI_DCS_SET_DISPLAY_ON); /* display ON */
	ग_लिखो_reg(par, MIPI_DCS_WRITE_MEMORY_START); /* Memory Write */

	वापस 0;
पूर्ण

अटल व्योम set_addr_win(काष्ठा fbtft_par *par, पूर्णांक xs, पूर्णांक ys,
			 पूर्णांक xe, पूर्णांक ye)
अणु
	चयन (par->info->var.rotate) अणु
	हाल 0:
		ग_लिखो_reg(par, MIPI_DCS_SET_COLUMN_ADDRESS,
			  xs >> 8, xs & 0xff, xe >> 8, xe & 0xff);
		ग_लिखो_reg(par, MIPI_DCS_SET_PAGE_ADDRESS,
			  (ys + __OFFSET) >> 8, (ys + __OFFSET) & 0xff,
			  (ye + __OFFSET) >> 8, (ye + __OFFSET) & 0xff);
		अवरोध;
	हाल 90:
		ग_लिखो_reg(par, MIPI_DCS_SET_COLUMN_ADDRESS,
			  (xs + __OFFSET) >> 8, (xs + __OFFSET) & 0xff,
			  (xe + __OFFSET) >> 8, (xe + __OFFSET) & 0xff);
		ग_लिखो_reg(par, MIPI_DCS_SET_PAGE_ADDRESS,
			  ys >> 8, ys & 0xff, ye >> 8, ye & 0xff);
		अवरोध;
	हाल 180:
	हाल 270:
		ग_लिखो_reg(par, MIPI_DCS_SET_COLUMN_ADDRESS,
			  xs >> 8, xs & 0xff, xe >> 8, xe & 0xff);
		ग_लिखो_reg(par, MIPI_DCS_SET_PAGE_ADDRESS,
			  ys >> 8, ys & 0xff, ye >> 8, ye & 0xff);
		अवरोध;
	शेष:
		/* Fix incorrect setting */
		par->info->var.rotate = 0;
	पूर्ण
	ग_लिखो_reg(par, MIPI_DCS_WRITE_MEMORY_START);
पूर्ण

/*
 * 7) MY:  1(bottom to top),	0(top to bottom)    Row Address Order
 * 6) MX:  1(R to L),		0(L to R)	    Column Address Order
 * 5) MV:  1(Exchanged),	0(normal)	    Row/Column exchange
 * 4) ML:  1(bottom to top),	0(top to bottom)    Vertical Refresh Order
 * 3) RGB: 1(BGR),		0(RGB)		    Color Space
 * 2) MH:  1(R to L),		0(L to R)	    Horizontal Refresh Order
 * 1)
 * 0)
 *
 *	MY, MX, MV, ML,RGB, MH, D1, D0
 *	0 | 0 | 0 | 0 | 1 | 0 | 0 | 0	//normal
 *	1 | 0 | 0 | 0 | 1 | 0 | 0 | 0	//Y-Mirror
 *	0 | 1 | 0 | 0 | 1 | 0 | 0 | 0	//X-Mirror
 *	1 | 1 | 0 | 0 | 1 | 0 | 0 | 0	//X-Y-Mirror
 *	0 | 0 | 1 | 0 | 1 | 0 | 0 | 0	//X-Y Exchange
 *	1 | 0 | 1 | 0 | 1 | 0 | 0 | 0	//X-Y Exchange, Y-Mirror
 *	0 | 1 | 1 | 0 | 1 | 0 | 0 | 0	//XY exchange
 *	1 | 1 | 1 | 0 | 1 | 0 | 0 | 0
 */
अटल पूर्णांक set_var(काष्ठा fbtft_par *par)
अणु
	u8 mactrl_data = 0; /* Aव्योम compiler warning */

	चयन (par->info->var.rotate) अणु
	हाल 0:
		mactrl_data = 0x08;
		अवरोध;
	हाल 180:
		mactrl_data = 0xC8;
		अवरोध;
	हाल 270:
		mactrl_data = 0xA8;
		अवरोध;
	हाल 90:
		mactrl_data = 0x68;
		अवरोध;
	पूर्ण

	/* Colorspcae */
	अगर (par->bgr)
		mactrl_data |= BIT(2);
	ग_लिखो_reg(par, MIPI_DCS_SET_ADDRESS_MODE, mactrl_data);
	ग_लिखो_reg(par, MIPI_DCS_WRITE_MEMORY_START);
	वापस 0;
पूर्ण

#अगर_घोषित GAMMA_ADJ
#घोषणा CURVE(num, idx)  curves[(num) * par->gamma.num_values + (idx)]
अटल पूर्णांक gamma_adj(काष्ठा fbtft_par *par, u32 *curves)
अणु
	अटल स्थिर अचिन्हित दीर्घ mask[] = अणु
		0x3F, 0x3F, 0x3F, 0x3F, 0x3F,
		0x1f, 0x3f, 0x0f, 0x0f, 0x7f, 0x1f,
		0x3F, 0x3F, 0x3F, 0x3F, 0x3Fपूर्ण;
	पूर्णांक i, j;

	क्रम (i = 0; i < GAMMA_NUM; i++)
		क्रम (j = 0; j < GAMMA_LEN; j++)
			CURVE(i, j) &= mask[i * par->gamma.num_values + j];

	ग_लिखो_reg(par, CMD_PGAMMAC,
		  CURVE(0, 0),
		  CURVE(0, 1),
		  CURVE(0, 2),
		  CURVE(0, 3),
		  CURVE(0, 4),
		  CURVE(0, 5),
		  CURVE(0, 6),
		  (CURVE(0, 7) << 4) | CURVE(0, 8),
		  CURVE(0, 9),
		  CURVE(0, 10),
		  CURVE(0, 11),
		  CURVE(0, 12),
		  CURVE(0, 13),
		  CURVE(0, 14),
		  CURVE(0, 15));

	/* Write Data to GRAM mode */
	ग_लिखो_reg(par, MIPI_DCS_WRITE_MEMORY_START);

	वापस 0;
पूर्ण

#अघोषित CURVE
#पूर्ण_अगर

अटल काष्ठा fbtft_display display = अणु
	.regwidth = 8,
	.width = WIDTH,
	.height = HEIGHT,
	.bpp = BPP,
	.fps = FPS,
#अगर_घोषित GAMMA_ADJ
	.gamma_num = GAMMA_NUM,
	.gamma_len = GAMMA_LEN,
	.gamma = DEFAULT_GAMMA,
#पूर्ण_अगर
	.fbtftops = अणु
		.init_display = init_display,
		.set_addr_win = set_addr_win,
		.set_var = set_var,
#अगर_घोषित GAMMA_ADJ
		.set_gamma = gamma_adj,
#पूर्ण_अगर
	पूर्ण,
पूर्ण;

FBTFT_REGISTER_DRIVER(DRVNAME, "ilitek,ili9163", &display);

MODULE_ALIAS("spi:" DRVNAME);
MODULE_ALIAS("platform:" DRVNAME);
MODULE_ALIAS("spi:ili9163");
MODULE_ALIAS("platform:ili9163");

MODULE_DESCRIPTION("FB driver for the ILI9163 LCD Controller");
MODULE_AUTHOR("Kozhevnikov Anatoly");
MODULE_LICENSE("GPL");
