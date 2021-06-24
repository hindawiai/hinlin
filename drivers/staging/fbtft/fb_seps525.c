<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * FB driver क्रम the NHD-1.69-160128UGC3 (Newhaven Display International, Inc.)
 * using the SEPS525 (Syncoam) LCD Controller
 *
 * Copyright (C) 2016 Analog Devices Inc.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/delay.h>

#समावेश "fbtft.h"

#घोषणा DRVNAME		"fb_seps525"
#घोषणा WIDTH		160
#घोषणा HEIGHT		128

#घोषणा SEPS525_INDEX 0x00
#घोषणा SEPS525_STATUS_RD 0x01
#घोषणा SEPS525_OSC_CTL 0x02
#घोषणा SEPS525_IREF 0x80
#घोषणा SEPS525_CLOCK_DIV 0x03
#घोषणा SEPS525_REDUCE_CURRENT 0x04
#घोषणा SEPS525_SOFT_RST 0x05
#घोषणा SEPS525_DISP_ONOFF 0x06
#घोषणा SEPS525_PRECHARGE_TIME_R 0x08
#घोषणा SEPS525_PRECHARGE_TIME_G 0x09
#घोषणा SEPS525_PRECHARGE_TIME_B 0x0A
#घोषणा SEPS525_PRECHARGE_CURRENT_R 0x0B
#घोषणा SEPS525_PRECHARGE_CURRENT_G 0x0C
#घोषणा SEPS525_PRECHARGE_CURRENT_B 0x0D
#घोषणा SEPS525_DRIVING_CURRENT_R 0x10
#घोषणा SEPS525_DRIVING_CURRENT_G 0x11
#घोषणा SEPS525_DRIVING_CURRENT_B 0x12
#घोषणा SEPS525_DISPLAYMODE_SET 0x13
#घोषणा SEPS525_RGBIF 0x14
#घोषणा SEPS525_RGB_POL 0x15
#घोषणा SEPS525_MEMORY_WRITEMODE 0x16
#घोषणा SEPS525_MX1_ADDR 0x17
#घोषणा SEPS525_MX2_ADDR 0x18
#घोषणा SEPS525_MY1_ADDR 0x19
#घोषणा SEPS525_MY2_ADDR 0x1A
#घोषणा SEPS525_MEMORY_ACCESS_POINTER_X 0x20
#घोषणा SEPS525_MEMORY_ACCESS_POINTER_Y 0x21
#घोषणा SEPS525_DDRAM_DATA_ACCESS_PORT 0x22
#घोषणा SEPS525_GRAY_SCALE_TABLE_INDEX 0x50
#घोषणा SEPS525_GRAY_SCALE_TABLE_DATA 0x51
#घोषणा SEPS525_DUTY 0x28
#घोषणा SEPS525_DSL 0x29
#घोषणा SEPS525_D1_DDRAM_FAC 0x2E
#घोषणा SEPS525_D1_DDRAM_FAR 0x2F
#घोषणा SEPS525_D2_DDRAM_SAC 0x31
#घोषणा SEPS525_D2_DDRAM_SAR 0x32
#घोषणा SEPS525_SCR1_FX1 0x33
#घोषणा SEPS525_SCR1_FX2 0x34
#घोषणा SEPS525_SCR1_FY1 0x35
#घोषणा SEPS525_SCR1_FY2 0x36
#घोषणा SEPS525_SCR2_SX1 0x37
#घोषणा SEPS525_SCR2_SX2 0x38
#घोषणा SEPS525_SCR2_SY1 0x39
#घोषणा SEPS525_SCR2_SY2 0x3A
#घोषणा SEPS525_SCREEN_SAVER_CONTEROL 0x3B
#घोषणा SEPS525_SS_SLEEP_TIMER 0x3C
#घोषणा SEPS525_SCREEN_SAVER_MODE 0x3D
#घोषणा SEPS525_SS_SCR1_FU 0x3E
#घोषणा SEPS525_SS_SCR1_MXY 0x3F
#घोषणा SEPS525_SS_SCR2_FU 0x40
#घोषणा SEPS525_SS_SCR2_MXY 0x41
#घोषणा SEPS525_MOVING_सूचीECTION 0x42
#घोषणा SEPS525_SS_SCR2_SX1 0x47
#घोषणा SEPS525_SS_SCR2_SX2 0x48
#घोषणा SEPS525_SS_SCR2_SY1 0x49
#घोषणा SEPS525_SS_SCR2_SY2 0x4A

/* SEPS525_DISPLAYMODE_SET */
#घोषणा MODE_SWAP_BGR	BIT(7)
#घोषणा MODE_SM		BIT(6)
#घोषणा MODE_RD		BIT(5)
#घोषणा MODE_CD		BIT(4)

#घोषणा seps525_use_winकरोw	0 /* FBTFT करोesn't really use it today */

/* Init sequence taken from: Arduino Library क्रम the Adafruit 2.2" display */
अटल पूर्णांक init_display(काष्ठा fbtft_par *par)
अणु
	par->fbtftops.reset(par);

	usleep_range(1000, 5000);

	/* Disable Oscillator Power Down */
	ग_लिखो_reg(par, SEPS525_REDUCE_CURRENT, 0x03);
	usleep_range(1000, 5000);
	/* Set Normal Driving Current */
	ग_लिखो_reg(par, SEPS525_REDUCE_CURRENT, 0x00);
	usleep_range(1000, 5000);

	ग_लिखो_reg(par, SEPS525_SCREEN_SAVER_CONTEROL, 0x00);
	/* Set EXPORT1 Pin at Internal Clock */
	ग_लिखो_reg(par, SEPS525_OSC_CTL, 0x01);
	/* Set Clock as 120 Frames/Sec */
	ग_लिखो_reg(par, SEPS525_CLOCK_DIV, 0x90);
	/* Set Reference Voltage Controlled by External Resister */
	ग_लिखो_reg(par, SEPS525_IREF, 0x01);

	/* preअक्षरge समय R G B */
	ग_लिखो_reg(par, SEPS525_PRECHARGE_TIME_R, 0x04);
	ग_लिखो_reg(par, SEPS525_PRECHARGE_TIME_G, 0x05);
	ग_लिखो_reg(par, SEPS525_PRECHARGE_TIME_B, 0x05);

	/* preअक्षरge current R G B (uA) */
	ग_लिखो_reg(par, SEPS525_PRECHARGE_CURRENT_R, 0x9D);
	ग_लिखो_reg(par, SEPS525_PRECHARGE_CURRENT_G, 0x8C);
	ग_लिखो_reg(par, SEPS525_PRECHARGE_CURRENT_B, 0x57);

	/* driving current R G B (uA) */
	ग_लिखो_reg(par, SEPS525_DRIVING_CURRENT_R, 0x56);
	ग_लिखो_reg(par, SEPS525_DRIVING_CURRENT_G, 0x4D);
	ग_लिखो_reg(par, SEPS525_DRIVING_CURRENT_B, 0x46);
	/* Set Color Sequence */
	ग_लिखो_reg(par, SEPS525_DISPLAYMODE_SET, 0xA0);
	ग_लिखो_reg(par, SEPS525_RGBIF, 0x01); /* Set MCU Interface Mode */
	/* Set Memory Write Mode */
	ग_लिखो_reg(par, SEPS525_MEMORY_WRITEMODE, 0x66);
	ग_लिखो_reg(par, SEPS525_DUTY, 0x7F); /* 1/128 Duty (0x0F~0x7F) */
	/* Set Mapping RAM Display Start Line (0x00~0x7F) */
	ग_लिखो_reg(par, SEPS525_DSL, 0x00);
	ग_लिखो_reg(par, SEPS525_DISP_ONOFF, 0x01); /* Display On (0x00/0x01) */
	/* Set All Internal Register Value as Normal Mode */
	ग_लिखो_reg(par, SEPS525_SOFT_RST, 0x00);
	/* Set RGB Interface Polarity as Active Low */
	ग_लिखो_reg(par, SEPS525_RGB_POL, 0x00);

	ग_लिखो_reg(par, SEPS525_DDRAM_DATA_ACCESS_PORT);

	वापस 0;
पूर्ण

अटल व्योम set_addr_win(काष्ठा fbtft_par *par, पूर्णांक xs, पूर्णांक ys, पूर्णांक xe, पूर्णांक ye)
अणु
	अगर (seps525_use_winकरोw) अणु
		/* Set Winकरोw Xs,Ys Xe,Ye*/
		ग_लिखो_reg(par, SEPS525_MX1_ADDR, xs);
		ग_लिखो_reg(par, SEPS525_MX2_ADDR, xe);
		ग_लिखो_reg(par, SEPS525_MY1_ADDR, ys);
		ग_लिखो_reg(par, SEPS525_MY2_ADDR, ye);
	पूर्ण
	/* start position X,Y */
	ग_लिखो_reg(par, SEPS525_MEMORY_ACCESS_POINTER_X, xs);
	ग_लिखो_reg(par, SEPS525_MEMORY_ACCESS_POINTER_Y, ys);

	ग_लिखो_reg(par, SEPS525_DDRAM_DATA_ACCESS_PORT);
पूर्ण

अटल पूर्णांक set_var(काष्ठा fbtft_par *par)
अणु
	u8 val;

	चयन (par->info->var.rotate) अणु
	हाल 0:
		val = 0;
		अवरोध;
	हाल 180:
		val = MODE_RD | MODE_CD;
		अवरोध;
	हाल 90:
	हाल 270:

	शेष:
		वापस -EINVAL;
	पूर्ण
	/* Memory Access Control  */
	ग_लिखो_reg(par, SEPS525_DISPLAYMODE_SET, val |
		       (par->bgr ? MODE_SWAP_BGR : 0));

	ग_लिखो_reg(par, SEPS525_DDRAM_DATA_ACCESS_PORT);

	वापस 0;
पूर्ण

अटल काष्ठा fbtft_display display = अणु
	.regwidth = 8,
	.width = WIDTH,
	.height = HEIGHT,
	.fbtftops = अणु
		.init_display = init_display,
		.set_addr_win = set_addr_win,
		.set_var = set_var,
	पूर्ण,
पूर्ण;

FBTFT_REGISTER_DRIVER(DRVNAME, "syncoam,seps525", &display);

MODULE_ALIAS("spi:" DRVNAME);
MODULE_ALIAS("platform:" DRVNAME);
MODULE_ALIAS("spi:seps525");
MODULE_ALIAS("platform:seps525");

MODULE_DESCRIPTION("FB driver for the SEPS525 LCD Controller");
MODULE_AUTHOR("Michael Hennerich <michael.hennerich@analog.com>");
MODULE_LICENSE("GPL");
