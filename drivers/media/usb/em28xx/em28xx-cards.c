<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// em28xx-cards.c - driver क्रम Empia EM2800/EM2820/2840 USB
//		    video capture devices
//
// Copyright (C) 2005 Luकरोvico Caveकरोn <caveकरोn@sssup.it>
//		      Markus Rechberger <mrechberger@gmail.com>
//		      Mauro Carvalho Chehab <mchehab@kernel.org>
//		      Sascha Sommer <saschasommer@मुक्तnet.de>
// Copyright (C) 2012 Frank Schथअfer <fschaefer.oss@googlemail.com>
//
// This program is मुक्त software; you can redistribute it and/or modअगरy
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License क्रम more details.

#समावेश "em28xx.h"

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/usb.h>
#समावेश <media/tuner.h>
#समावेश <media/drv-पूर्णांकf/msp3400.h>
#समावेश <media/i2c/saa7115.h>
#समावेश <dt-bindings/media/tvp5150.h>
#समावेश <media/i2c/tvaudपन.स>
#समावेश <media/tveeprom.h>
#समावेश <media/v4l2-common.h>
#समावेश <sound/ac97_codec.h>

#घोषणा DRIVER_NAME         "em28xx"

अटल पूर्णांक tuner = -1;
module_param(tuner, पूर्णांक, 0444);
MODULE_PARM_DESC(tuner, "tuner type");

अटल अचिन्हित पूर्णांक disable_ir;
module_param(disable_ir, पूर्णांक, 0444);
MODULE_PARM_DESC(disable_ir, "disable infrared remote support");

अटल अचिन्हित पूर्णांक disable_usb_speed_check;
module_param(disable_usb_speed_check, पूर्णांक, 0444);
MODULE_PARM_DESC(disable_usb_speed_check,
		 "override min bandwidth requirement of 480M bps");

अटल अचिन्हित पूर्णांक card[]     = अणु[0 ... (EM28XX_MAXBOARDS - 1)] = -1U पूर्ण;
module_param_array(card,  पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(card,     "card type");

अटल पूर्णांक usb_xfer_mode = -1;
module_param(usb_xfer_mode, पूर्णांक, 0444);
MODULE_PARM_DESC(usb_xfer_mode,
		 "USB transfer mode for frame data (-1 = auto, 0 = prefer isoc, 1 = prefer bulk)");

/* Biपंचांगask marking allocated devices from 0 to EM28XX_MAXBOARDS - 1 */
अटल DECLARE_BITMAP(em28xx_devused, EM28XX_MAXBOARDS);

काष्ठा em28xx_hash_table अणु
	अचिन्हित दीर्घ hash;
	अचिन्हित पूर्णांक  model;
	अचिन्हित पूर्णांक  tuner;
पूर्ण;

अटल व्योम em28xx_pre_card_setup(काष्ठा em28xx *dev);

/*
 *  Reset sequences क्रम analog/digital modes
 */

/* Reset क्रम the most [analog] boards */
अटल स्थिर काष्ठा em28xx_reg_seq शेष_analog[] = अणु
	अणुEM2820_R08_GPIO_CTRL,	0x6d,   ~EM_GPIO_4,	10पूर्ण,
	अणु	-1,		-1,	-1,		-1पूर्ण,
पूर्ण;

/* Reset क्रम the most [digital] boards */
अटल स्थिर काष्ठा em28xx_reg_seq शेष_digital[] = अणु
	अणुEM2820_R08_GPIO_CTRL,	0x6e,	~EM_GPIO_4,	10पूर्ण,
	अणु	-1,		-1,	-1,		-1पूर्ण,
पूर्ण;

/* Board :Zolid Hybrid Tv Stick */
अटल काष्ठा em28xx_reg_seq zolid_tuner[] = अणु
	अणुEM2820_R08_GPIO_CTRL,		0xfd,		0xff,	100पूर्ण,
	अणुEM2820_R08_GPIO_CTRL,		0xfe,		0xff,	100पूर्ण,
	अणु		-1,					-1,			-1,		 -1पूर्ण,
पूर्ण;

अटल काष्ठा em28xx_reg_seq zolid_digital[] = अणु
	अणुEM2820_R08_GPIO_CTRL,		0x6a,		0xff,	100पूर्ण,
	अणुEM2820_R08_GPIO_CTRL,		0x7a,		0xff,	100पूर्ण,
	अणुEM2880_R04_GPO,			0x04,		0xff,	100पूर्ण,
	अणुEM2880_R04_GPO,			0x0c,		0xff,	100पूर्ण,
	अणु	-1,						-1,			-1,		 -1पूर्ण,
पूर्ण;

/* Board Hauppauge WinTV HVR 900 analog */
अटल स्थिर काष्ठा em28xx_reg_seq hauppauge_wपूर्णांकv_hvr_900_analog[] = अणु
	अणुEM2820_R08_GPIO_CTRL,	0x2d,	~EM_GPIO_4,	10पूर्ण,
	अणु	0x05,		0xff,	0x10,		10पूर्ण,
	अणु	-1,		-1,	-1,		-1पूर्ण,
पूर्ण;

/* Board Hauppauge WinTV HVR 900 digital */
अटल स्थिर काष्ठा em28xx_reg_seq hauppauge_wपूर्णांकv_hvr_900_digital[] = अणु
	अणुEM2820_R08_GPIO_CTRL,	0x2e,	~EM_GPIO_4,	10पूर्ण,
	अणुEM2880_R04_GPO,	0x04,	0x0f,		10पूर्ण,
	अणुEM2880_R04_GPO,	0x0c,	0x0f,		10पूर्ण,
	अणु	-1,		-1,	-1,		-1पूर्ण,
पूर्ण;

/* Board Hauppauge WinTV HVR 900 (R2) digital */
अटल स्थिर काष्ठा em28xx_reg_seq hauppauge_wपूर्णांकv_hvr_900R2_digital[] = अणु
	अणुEM2820_R08_GPIO_CTRL,	0x2e,	~EM_GPIO_4,	10पूर्ण,
	अणुEM2880_R04_GPO,	0x0c,	0x0f,		10पूर्ण,
	अणु	-1,		-1,	-1,		-1पूर्ण,
पूर्ण;

/* Boards - EM2880 MSI DIGIVOX AD and EM2880_BOARD_MSI_DIGIVOX_AD_II */
अटल स्थिर काष्ठा em28xx_reg_seq em2880_msi_digivox_ad_analog[] = अणु
	अणुEM2820_R08_GPIO_CTRL,	0x69,   ~EM_GPIO_4,	10पूर्ण,
	अणु	-1,		-1,	-1,		-1पूर्ण,
पूर्ण;

/* Board - EM2882 Kworld 315U digital */
अटल स्थिर काष्ठा em28xx_reg_seq em2882_kworld_315u_digital[] = अणु
	अणुEM2820_R08_GPIO_CTRL,	0xff,	0xff,		10पूर्ण,
	अणुEM2820_R08_GPIO_CTRL,	0xfe,	0xff,		10पूर्ण,
	अणुEM2880_R04_GPO,	0x04,	0xff,		10पूर्ण,
	अणुEM2880_R04_GPO,	0x0c,	0xff,		10पूर्ण,
	अणुEM2820_R08_GPIO_CTRL,	0x7e,	0xff,		10पूर्ण,
	अणु	-1,		-1,	-1,		-1पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा em28xx_reg_seq em2882_kworld_315u_tuner_gpio[] = अणु
	अणुEM2880_R04_GPO,	0x08,	0xff,		10पूर्ण,
	अणुEM2880_R04_GPO,	0x0c,	0xff,		10पूर्ण,
	अणुEM2880_R04_GPO,	0x08,	0xff,		10पूर्ण,
	अणुEM2880_R04_GPO,	0x0c,	0xff,		10पूर्ण,
	अणु	-1,		-1,	-1,		-1पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा em28xx_reg_seq kworld_330u_analog[] = अणु
	अणुEM2820_R08_GPIO_CTRL,	0x6d,	~EM_GPIO_4,	10पूर्ण,
	अणुEM2880_R04_GPO,	0x00,	0xff,		10पूर्ण,
	अणु	-1,		-1,	-1,		-1पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा em28xx_reg_seq kworld_330u_digital[] = अणु
	अणुEM2820_R08_GPIO_CTRL,	0x6e,	~EM_GPIO_4,	10पूर्ण,
	अणुEM2880_R04_GPO,	0x08,	0xff,		10पूर्ण,
	अणु	-1,		-1,	-1,		-1पूर्ण,
पूर्ण;

/*
 * Evga inDtube
 * GPIO0 - Enable digital घातer (s5h1409) - low to enable
 * GPIO1 - Enable analog घातer (tvp5150/emp202) - low to enable
 * GPIO4 - xc3028 reset
 * GOP3  - s5h1409 reset
 */
अटल स्थिर काष्ठा em28xx_reg_seq evga_indtube_analog[] = अणु
	अणुEM2820_R08_GPIO_CTRL,	0x79,   0xff,		60पूर्ण,
	अणु	-1,		-1,	-1,		-1पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा em28xx_reg_seq evga_indtube_digital[] = अणु
	अणुEM2820_R08_GPIO_CTRL,	0x7a,	0xff,		 1पूर्ण,
	अणुEM2880_R04_GPO,	0x04,	0xff,		10पूर्ण,
	अणुEM2880_R04_GPO,	0x0c,	0xff,		 1पूर्ण,
	अणु	-1,		-1,	-1,		-1पूर्ण,
पूर्ण;

/*
 * KWorld PlusTV 340U, UB435-Q and UB435-Q V2 (ATSC) GPIOs map:
 * EM_GPIO_0 - currently unknown
 * EM_GPIO_1 - LED disable/enable (1 = off, 0 = on)
 * EM_GPIO_2 - currently unknown
 * EM_GPIO_3 - currently unknown
 * EM_GPIO_4 - TDA18271HD/C1 tuner (1 = active, 0 = in reset)
 * EM_GPIO_5 - LGDT3304 ATSC/QAM demod (1 = active, 0 = in reset)
 * EM_GPIO_6 - currently unknown
 * EM_GPIO_7 - currently unknown
 */
अटल स्थिर काष्ठा em28xx_reg_seq kworld_a340_digital[] = अणु
	अणुEM2820_R08_GPIO_CTRL,	0x6d,	~EM_GPIO_4,	10पूर्ण,
	अणु	-1,		-1,	-1,		-1पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा em28xx_reg_seq kworld_ub435q_v3_digital[] = अणु
	अणुEM2874_R80_GPIO_P0_CTRL,	0xff,	0xff,	100पूर्ण,
	अणुEM2874_R80_GPIO_P0_CTRL,	0xfe,	0xff,	100पूर्ण,
	अणुEM2874_R80_GPIO_P0_CTRL,	0xbe,	0xff,	100पूर्ण,
	अणुEM2874_R80_GPIO_P0_CTRL,	0xfe,	0xff,	100पूर्ण,
	अणु	-1,			-1,	-1,	-1पूर्ण,
पूर्ण;

/* Pinnacle Hybrid Pro eb1a:2881 */
अटल स्थिर काष्ठा em28xx_reg_seq pinnacle_hybrid_pro_analog[] = अणु
	अणुEM2820_R08_GPIO_CTRL,	0xfd,   ~EM_GPIO_4,	10पूर्ण,
	अणु	-1,		-1,	-1,		-1पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा em28xx_reg_seq pinnacle_hybrid_pro_digital[] = अणु
	अणुEM2820_R08_GPIO_CTRL,	0x6e,	~EM_GPIO_4,	10पूर्ण,
	अणुEM2880_R04_GPO,	0x04,	0xff,	       100पूर्ण,/* zl10353 reset */
	अणुEM2880_R04_GPO,	0x0c,	0xff,		 1पूर्ण,
	अणु	-1,		-1,	-1,		-1पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा em28xx_reg_seq terratec_cinergy_USB_XS_FR_analog[] = अणु
	अणुEM2820_R08_GPIO_CTRL,	0x6d,	~EM_GPIO_4,	10पूर्ण,
	अणुEM2880_R04_GPO,	0x00,	0xff,		10पूर्ण,
	अणु	-1,		-1,	-1,		-1पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा em28xx_reg_seq terratec_cinergy_USB_XS_FR_digital[] = अणु
	अणुEM2820_R08_GPIO_CTRL,	0x6e,	~EM_GPIO_4,	10पूर्ण,
	अणुEM2880_R04_GPO,	0x08,	0xff,		10पूर्ण,
	अणु	-1,		-1,	-1,		-1पूर्ण,
पूर्ण;

/*
 * PCTV HD Mini (80e) GPIOs
 * 0-5: not used
 * 6:   demod reset, active low
 * 7:   LED on, active high
 */
अटल स्थिर काष्ठा em28xx_reg_seq em2874_pctv_80e_digital[] = अणु
	अणुEM28XX_R06_I2C_CLK,    0x45,   0xff,		  10पूर्ण, /*400 KHz*/
	अणुEM2874_R80_GPIO_P0_CTRL, 0x00,   0xff,		  100पूर्ण,/*Demod reset*/
	अणुEM2874_R80_GPIO_P0_CTRL, 0x40,   0xff,		  10पूर्ण,
	अणु  -1,			-1,	-1,		  -1पूर्ण,
पूर्ण;

/*
 * eb1a:2868 Redकरो DVB-C USB TV Box
 * GPIO4 - CU1216L NIM
 * Other GPIOs seems to be करोn't care.
 */
अटल स्थिर काष्ठा em28xx_reg_seq redकरो_dvb_c_usb_box[] = अणु
	अणुEM2820_R08_GPIO_CTRL,	0xfe,	0xff,		10पूर्ण,
	अणुEM2820_R08_GPIO_CTRL,	0xde,	0xff,		10पूर्ण,
	अणुEM2820_R08_GPIO_CTRL,	0xfe,	0xff,		10पूर्ण,
	अणुEM2820_R08_GPIO_CTRL,	0xff,	0xff,		10पूर्ण,
	अणुEM2820_R08_GPIO_CTRL,	0x7f,	0xff,		10पूर्ण,
	अणुEM2820_R08_GPIO_CTRL,	0x6f,	0xff,		10पूर्ण,
	अणुEM2820_R08_GPIO_CTRL,	0xff,	0xff,		10पूर्ण,
	अणु	-1,		-1,	-1,		-1पूर्ण,
पूर्ण;

/* Callback क्रम the most boards */
अटल स्थिर काष्ठा em28xx_reg_seq शेष_tuner_gpio[] = अणु
	अणुEM2820_R08_GPIO_CTRL,	EM_GPIO_4,	EM_GPIO_4,	10पूर्ण,
	अणुEM2820_R08_GPIO_CTRL,	0,		EM_GPIO_4,	10पूर्ण,
	अणुEM2820_R08_GPIO_CTRL,	EM_GPIO_4,	EM_GPIO_4,	10पूर्ण,
	अणु	-1,		-1,		-1,		-1पूर्ण,
पूर्ण;

/* Mute/unmute */
अटल स्थिर काष्ठा em28xx_reg_seq compro_unmute_tv_gpio[] = अणु
	अणुEM2820_R08_GPIO_CTRL,	5,	7,	10पूर्ण,
	अणु	-1,		-1,	-1,	-1पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा em28xx_reg_seq compro_unmute_svid_gpio[] = अणु
	अणुEM2820_R08_GPIO_CTRL,	4,	7,	10पूर्ण,
	अणु	-1,		-1,	-1,	-1पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा em28xx_reg_seq compro_mute_gpio[] = अणु
	अणुEM2820_R08_GPIO_CTRL,	6,	7,	10पूर्ण,
	अणु	-1,		-1,	-1,	-1पूर्ण,
पूर्ण;

/* Terratec AV350 */
अटल स्थिर काष्ठा em28xx_reg_seq terratec_av350_mute_gpio[] = अणु
	अणुEM2820_R08_GPIO_CTRL,	0xff,	0x7f,		10पूर्ण,
	अणु	-1,		-1,	-1,		-1पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा em28xx_reg_seq terratec_av350_unmute_gpio[] = अणु
	अणुEM2820_R08_GPIO_CTRL,	0xff,	0xff,		10पूर्ण,
	अणु	-1,		-1,	-1,		-1पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा em28xx_reg_seq silvercrest_reg_seq[] = अणु
	अणुEM2820_R08_GPIO_CTRL,	0xff,	0xff,		10पूर्ण,
	अणुEM2820_R08_GPIO_CTRL,	0x01,	0xf7,		10पूर्ण,
	अणु	-1,		-1,	-1,		-1पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा em28xx_reg_seq vc211a_enable[] = अणु
	अणुEM2820_R08_GPIO_CTRL,	0xff,	0x07,		10पूर्ण,
	अणुEM2820_R08_GPIO_CTRL,	0xff,	0x0f,		10पूर्ण,
	अणुEM2820_R08_GPIO_CTRL,	0xff,	0x0b,		10पूर्ण,
	अणु	-1,		-1,	-1,		-1पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा em28xx_reg_seq dikom_dk300_digital[] = अणु
	अणुEM2820_R08_GPIO_CTRL,	0x6e,	~EM_GPIO_4,	10पूर्ण,
	अणुEM2880_R04_GPO,	0x08,	0xff,		10पूर्ण,
	अणु	-1,		-1,	-1,		-1पूर्ण,
पूर्ण;

/* Reset क्रम the most [digital] boards */
अटल स्थिर काष्ठा em28xx_reg_seq leadership_digital[] = अणु
	अणुEM2874_R80_GPIO_P0_CTRL,	0x70,	0xff,	10पूर्ण,
	अणु	-1,			-1,	-1,	-1पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा em28xx_reg_seq leadership_reset[] = अणु
	अणुEM2874_R80_GPIO_P0_CTRL,	0xf0,	0xff,	10पूर्ण,
	अणुEM2874_R80_GPIO_P0_CTRL,	0xb0,	0xff,	10पूर्ण,
	अणुEM2874_R80_GPIO_P0_CTRL,	0xf0,	0xff,	10पूर्ण,
	अणु	-1,			-1,	-1,	-1पूर्ण,
पूर्ण;

/*
 * 2013:024f PCTV nanoStick T2 290e
 * GPIO_6 - demod reset
 * GPIO_7 - LED
 */
अटल स्थिर काष्ठा em28xx_reg_seq pctv_290e[] = अणु
	अणुEM2874_R80_GPIO_P0_CTRL,	0x00,	0xff,	80पूर्ण,
	अणुEM2874_R80_GPIO_P0_CTRL,	0x40,	0xff,	80पूर्ण, /* GPIO_6 = 1 */
	अणुEM2874_R80_GPIO_P0_CTRL,	0xc0,	0xff,	80पूर्ण, /* GPIO_7 = 1 */
	अणु	-1,			-1,	-1,	-1पूर्ण,
पूर्ण;

#अगर 0
अटल स्थिर काष्ठा em28xx_reg_seq terratec_h5_gpio[] = अणु
	अणुEM2820_R08_GPIO_CTRL,		0xff,	0xff,	10पूर्ण,
	अणुEM2874_R80_GPIO_P0_CTRL,	0xf6,	0xff,	100पूर्ण,
	अणुEM2874_R80_GPIO_P0_CTRL,	0xf2,	0xff,	50पूर्ण,
	अणुEM2874_R80_GPIO_P0_CTRL,	0xf6,	0xff,	50पूर्ण,
	अणु	-1,			-1,	-1,	-1पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा em28xx_reg_seq terratec_h5_digital[] = अणु
	अणुEM2874_R80_GPIO_P0_CTRL,	0xf6,	0xff,	10पूर्ण,
	अणुEM2874_R80_GPIO_P0_CTRL,	0xe6,	0xff,	100पूर्ण,
	अणुEM2874_R80_GPIO_P0_CTRL,	0xa6,	0xff,	10पूर्ण,
	अणु	-1,			-1,	-1,	-1पूर्ण,
पूर्ण;
#पूर्ण_अगर

/*
 * 2013:024f PCTV DVB-S2 Stick 460e
 * GPIO_0 - POWER_ON
 * GPIO_1 - BOOST
 * GPIO_2 - VUV_LNB (red LED)
 * GPIO_3 - EXT_12V
 * GPIO_4 - INT_DEM (DEMOD GPIO_0)
 * GPIO_5 - INT_LNB
 * GPIO_6 - RESET_DEM
 * GPIO_7 - LED (green LED)
 */
अटल स्थिर काष्ठा em28xx_reg_seq pctv_460e[] = अणु
	अणुEM2874_R80_GPIO_P0_CTRL,	0x01,	0xff,	50पूर्ण,
	अणु	0x0d,			0xff,	0xff,	50पूर्ण,
	अणुEM2874_R80_GPIO_P0_CTRL,	0x41,	0xff,	50पूर्ण, /* GPIO_6=1 */
	अणु	0x0d,			0x42,	0xff,	50पूर्ण,
	अणुEM2874_R80_GPIO_P0_CTRL,	0x61,	0xff,	50पूर्ण, /* GPIO_5=1 */
	अणु	-1,			-1,	-1,	-1पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा em28xx_reg_seq c3tech_digital_duo_digital[] = अणु
	अणुEM2874_R80_GPIO_P0_CTRL,	0xff,	0xff,	10पूर्ण,
	अणुEM2874_R80_GPIO_P0_CTRL,	0xfd,	0xff,	10पूर्ण, /* xc5000 reset */
	अणुEM2874_R80_GPIO_P0_CTRL,	0xf9,	0xff,	35पूर्ण,
	अणुEM2874_R80_GPIO_P0_CTRL,	0xfd,	0xff,	10पूर्ण,
	अणुEM2874_R80_GPIO_P0_CTRL,	0xff,	0xff,	10पूर्ण,
	अणुEM2874_R80_GPIO_P0_CTRL,	0xfe,	0xff,	10पूर्ण,
	अणुEM2874_R80_GPIO_P0_CTRL,	0xbe,	0xff,	10पूर्ण,
	अणुEM2874_R80_GPIO_P0_CTRL,	0xfe,	0xff,	20पूर्ण,
	अणु	-1,			-1,	-1,	-1पूर्ण,
पूर्ण;

/*
 * 2013:0258 PCTV DVB-S2 Stick (461e)
 * GPIO 0 = POWER_ON
 * GPIO 1 = BOOST
 * GPIO 2 = VUV_LNB (red LED)
 * GPIO 3 = #EXT_12V
 * GPIO 4 = INT_DEM
 * GPIO 5 = INT_LNB
 * GPIO 6 = #RESET_DEM
 * GPIO 7 = P07_LED (green LED)
 */
अटल स्थिर काष्ठा em28xx_reg_seq pctv_461e[] = अणु
	अणुEM2874_R80_GPIO_P0_CTRL,      0x7f, 0xff,    0पूर्ण,
	अणु0x0d,                 0xff, 0xff,    0पूर्ण,
	अणुEM2874_R80_GPIO_P0_CTRL,      0x3f, 0xff,  100पूर्ण, /* reset demod */
	अणुEM2874_R80_GPIO_P0_CTRL,      0x7f, 0xff,  200पूर्ण, /* reset demod */
	अणु0x0d,                 0x42, 0xff,    0पूर्ण,
	अणुEM2874_R80_GPIO_P0_CTRL,      0xeb, 0xff,    0पूर्ण,
	अणुEM2874_R5F_TS_ENABLE, 0x84, 0x84,    0पूर्ण, /* parallel? | null discard */
	अणु                  -1,   -1,   -1,   -1पूर्ण,
पूर्ण;

#अगर 0
अटल स्थिर काष्ठा em28xx_reg_seq hauppauge_930c_gpio[] = अणु
	अणुEM2874_R80_GPIO_P0_CTRL,	0x6f,	0xff,	10पूर्ण,
	अणुEM2874_R80_GPIO_P0_CTRL,	0x4f,	0xff,	10पूर्ण, /* xc5000 reset */
	अणुEM2874_R80_GPIO_P0_CTRL,	0x6f,	0xff,	10पूर्ण,
	अणुEM2874_R80_GPIO_P0_CTRL,	0x4f,	0xff,	10पूर्ण,
	अणु	-1,			-1,	-1,	-1पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा em28xx_reg_seq hauppauge_930c_digital[] = अणु
	अणुEM2874_R80_GPIO_P0_CTRL,	0xf6,	0xff,	10पूर्ण,
	अणुEM2874_R80_GPIO_P0_CTRL,	0xe6,	0xff,	100पूर्ण,
	अणुEM2874_R80_GPIO_P0_CTRL,	0xa6,	0xff,	10पूर्ण,
	अणु	-1,			-1,	-1,	-1पूर्ण,
पूर्ण;
#पूर्ण_अगर

/*
 * 1b80:e425 MaxMedia UB425-TC
 * 1b80:e1cc Delock 61959
 * GPIO_6 - demod reset, 0=active
 * GPIO_7 - LED, 0=active
 */
अटल स्थिर काष्ठा em28xx_reg_seq maxmedia_ub425_tc[] = अणु
	अणुEM2874_R80_GPIO_P0_CTRL,	0x83,	0xff,	100पूर्ण,
	अणुEM2874_R80_GPIO_P0_CTRL,	0xc3,	0xff,	100पूर्ण, /* GPIO_6 = 1 */
	अणुEM2874_R80_GPIO_P0_CTRL,	0x43,	0xff,	000पूर्ण, /* GPIO_7 = 0 */
	अणु	-1,			-1,	-1,	-1पूर्ण,
पूर्ण;

/*
 * 2304:0242 PCTV QuatroStick (510e)
 * GPIO_2: decoder reset, 0=active
 * GPIO_4: decoder suspend, 0=active
 * GPIO_6: demod reset, 0=active
 * GPIO_7: LED, 1=active
 */
अटल स्थिर काष्ठा em28xx_reg_seq pctv_510e[] = अणु
	अणुEM2874_R80_GPIO_P0_CTRL,	0x10,	0xff,	100पूर्ण,
	अणुEM2874_R80_GPIO_P0_CTRL,	0x14,	0xff,	100पूर्ण, /* GPIO_2 = 1 */
	अणुEM2874_R80_GPIO_P0_CTRL,	0x54,	0xff,	050पूर्ण, /* GPIO_6 = 1 */
	अणु	-1,			-1,	-1,	-1पूर्ण,
पूर्ण;

/*
 * 2013:0251 PCTV QuatroStick nano (520e)
 * GPIO_2: decoder reset, 0=active
 * GPIO_4: decoder suspend, 0=active
 * GPIO_6: demod reset, 0=active
 * GPIO_7: LED, 1=active
 */
अटल स्थिर काष्ठा em28xx_reg_seq pctv_520e[] = अणु
	अणुEM2874_R80_GPIO_P0_CTRL,	0x10,	0xff,	100पूर्ण,
	अणुEM2874_R80_GPIO_P0_CTRL,	0x14,	0xff,	100पूर्ण, /* GPIO_2 = 1 */
	अणुEM2874_R80_GPIO_P0_CTRL,	0x54,	0xff,	050पूर्ण, /* GPIO_6 = 1 */
	अणुEM2874_R80_GPIO_P0_CTRL,	0xd4,	0xff,	000पूर्ण, /* GPIO_7 = 1 */
	अणु	-1,			-1,	-1,	-1पूर्ण,
पूर्ण;

/*
 * 1ae7:9003/9004 SpeedLink Vicious And Devine Laplace webcam
 * reg 0x80/0x84:
 * GPIO_0: capturing LED, 0=on, 1=off
 * GPIO_2: AV mute button, 0=pressed, 1=unpressed
 * GPIO 3: illumination button, 0=pressed, 1=unpressed
 * GPIO_6: illumination/flash LED, 0=on, 1=off
 * reg 0x81/0x85:
 * GPIO_7: snapshot button, 0=pressed, 1=unpressed
 */
अटल स्थिर काष्ठा em28xx_reg_seq speedlink_vad_laplace_reg_seq[] = अणु
	अणुEM2820_R08_GPIO_CTRL,		0xf7,	0xff,	10पूर्ण,
	अणुEM2874_R80_GPIO_P0_CTRL,	0xff,	0xb2,	10पूर्ण,
	अणु	-1,			-1,	-1,	-1पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा em28xx_reg_seq pctv_292e[] = अणु
	अणुEM2874_R80_GPIO_P0_CTRL,      0xff, 0xff,      0पूर्ण,
	अणु0x0d,                         0xff, 0xff,    950पूर्ण,
	अणुEM2874_R80_GPIO_P0_CTRL,      0xbd, 0xff,    100पूर्ण,
	अणुEM2874_R80_GPIO_P0_CTRL,      0xfd, 0xff,    410पूर्ण,
	अणुEM2874_R80_GPIO_P0_CTRL,      0x7d, 0xff,    300पूर्ण,
	अणुEM2874_R80_GPIO_P0_CTRL,      0x7c, 0xff,     60पूर्ण,
	अणु0x0d,                         0x42, 0xff,     50पूर्ण,
	अणुEM2874_R5F_TS_ENABLE,         0x85, 0xff,      0पूर्ण,
	अणु-1,                             -1,   -1,     -1पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा em28xx_reg_seq terratec_t2_stick_hd[] = अणु
	अणुEM2874_R80_GPIO_P0_CTRL,	0xff,	0xff,	0पूर्ण,
	अणु0x0d,				0xff,	0xff,	600पूर्ण,
	अणुEM2874_R80_GPIO_P0_CTRL,	0xfc,	0xff,	10पूर्ण,
	अणुEM2874_R80_GPIO_P0_CTRL,	0xbc,	0xff,	100पूर्ण,
	अणुEM2874_R80_GPIO_P0_CTRL,	0xfc,	0xff,	100पूर्ण,
	अणुEM2874_R80_GPIO_P0_CTRL,	0x00,	0xff,	300पूर्ण,
	अणुEM2874_R80_GPIO_P0_CTRL,	0xf8,	0xff,	100पूर्ण,
	अणुEM2874_R80_GPIO_P0_CTRL,	0xfc,	0xff,	300पूर्ण,
	अणु0x0d,				0x42,	0xff,	1000पूर्ण,
	अणुEM2874_R5F_TS_ENABLE,		0x85,	0xff,	0पूर्ण,
	अणु-1,                             -1,   -1,     -1पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा em28xx_reg_seq plex_px_bcud[] = अणु
	अणुEM2874_R80_GPIO_P0_CTRL,	0xff,	0xff,	0पूर्ण,
	अणु0x0d,				0xff,	0xff,	0पूर्ण,
	अणुEM2874_R50_IR_CONFIG,		0x01,	0xff,	0पूर्ण,
	अणुEM28XX_R06_I2C_CLK,		0x40,	0xff,	0पूर्ण,
	अणुEM2874_R80_GPIO_P0_CTRL,	0xfd,	0xff,	100पूर्ण,
	अणुEM28XX_R12_VINENABLE,		0x20,	0x20,	0पूर्ण,
	अणु0x0d,				0x42,	0xff,	1000पूर्ण,
	अणुEM2874_R80_GPIO_P0_CTRL,	0xfc,	0xff,	10पूर्ण,
	अणुEM2874_R80_GPIO_P0_CTRL,	0xfd,	0xff,	10पूर्ण,
	अणु0x73,				0xfd,	0xff,	100पूर्ण,
	अणु-1,				-1,	-1,	-1पूर्ण,
पूर्ण;

/*
 * 2040:0265 Hauppauge WinTV-dualHD DVB Isoc
 * 2040:8265 Hauppauge WinTV-dualHD DVB Bulk
 * 2040:026d Hauppauge WinTV-dualHD ATSC/QAM Isoc
 * 2040:826d Hauppauge WinTV-dualHD ATSC/QAM Bulk
 * reg 0x80/0x84:
 * GPIO_0: Yellow LED tuner 1, 0=on, 1=off
 * GPIO_1: Green LED tuner 1, 0=on, 1=off
 * GPIO_2: Yellow LED tuner 2, 0=on, 1=off
 * GPIO_3: Green LED tuner 2, 0=on, 1=off
 * GPIO_5: Reset #2, 0=active
 * GPIO_6: Reset #1, 0=active
 */
अटल स्थिर काष्ठा em28xx_reg_seq hauppauge_dualhd_dvb[] = अणु
	अणुEM2874_R80_GPIO_P0_CTRL,      0xff, 0xff,      0पूर्ण,
	अणु0x0d,                         0xff, 0xff,    200पूर्ण,
	अणु0x50,                         0x04, 0xff,    300पूर्ण,
	अणुEM2874_R80_GPIO_P0_CTRL,      0xbf, 0xff,    100पूर्ण, /* demod 1 reset */
	अणुEM2874_R80_GPIO_P0_CTRL,      0xff, 0xff,    100पूर्ण,
	अणुEM2874_R80_GPIO_P0_CTRL,      0xdf, 0xff,    100पूर्ण, /* demod 2 reset */
	अणुEM2874_R80_GPIO_P0_CTRL,      0xff, 0xff,    100पूर्ण,
	अणुEM2874_R5F_TS_ENABLE,         0x00, 0xff,     50पूर्ण, /* disable TS filters */
	अणुEM2874_R5D_TS1_PKT_SIZE,      0x05, 0xff,     50पूर्ण,
	अणुEM2874_R5E_TS2_PKT_SIZE,      0x05, 0xff,     50पूर्ण,
	अणु-1,                             -1,   -1,     -1पूर्ण,
पूर्ण;

/* Hauppauge USB QuadHD */
अटल काष्ठा em28xx_reg_seq hauppauge_usb_quadhd_atsc_reg_seq[] = अणु
	अणुEM2874_R80_GPIO_P0_CTRL,      0xff, 0xff,      0पूर्ण,
	अणु0x0d,                         0xff, 0xff,    200पूर्ण,
	अणु0x50,                         0x04, 0xff,    300पूर्ण,
	अणुEM2874_R80_GPIO_P0_CTRL,      0xb0, 0xf0,    100पूर्ण, /* demod 1 reset */
	अणुEM2874_R80_GPIO_P0_CTRL,      0xf0, 0xf0,    100पूर्ण,
	अणुEM2874_R80_GPIO_P0_CTRL,      0xd0, 0xf0,    100पूर्ण, /* demod 2 reset */
	अणुEM2874_R80_GPIO_P0_CTRL,      0xf0, 0xf0,    100पूर्ण,
	अणुEM2874_R5F_TS_ENABLE,         0x44, 0xff,     50पूर्ण,
	अणुEM2874_R5D_TS1_PKT_SIZE,      0x05, 0xff,     50पूर्ण,
	अणुEM2874_R5E_TS2_PKT_SIZE,      0x05, 0xff,     50पूर्ण,
	अणु-1,                           -1,   -1,       -1पूर्ण,
पूर्ण;

/*
 *  Button definitions
 */
अटल स्थिर काष्ठा em28xx_button std_snapshot_button[] = अणु
	अणु
		.role         = EM28XX_BUTTON_SNAPSHOT,
		.reg_r        = EM28XX_R0C_USBSUSP,
		.reg_clearing = EM28XX_R0C_USBSUSP,
		.mask         = EM28XX_R0C_USBSUSP_SNAPSHOT,
		.inverted     = 0,
	पूर्ण,
	अणु-1, 0, 0, 0, 0पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा em28xx_button speedlink_vad_laplace_buttons[] = अणु
	अणु
		.role     = EM28XX_BUTTON_SNAPSHOT,
		.reg_r    = EM2874_R85_GPIO_P1_STATE,
		.mask     = 0x80,
		.inverted = 1,
	पूर्ण,
	अणु
		.role     = EM28XX_BUTTON_ILLUMINATION,
		.reg_r    = EM2874_R84_GPIO_P0_STATE,
		.mask     = 0x08,
		.inverted = 1,
	पूर्ण,
	अणु-1, 0, 0, 0, 0पूर्ण,
पूर्ण;

/*
 *  LED definitions
 */
अटल काष्ठा em28xx_led speedlink_vad_laplace_leds[] = अणु
	अणु
		.role      = EM28XX_LED_ANALOG_CAPTURING,
		.gpio_reg  = EM2874_R80_GPIO_P0_CTRL,
		.gpio_mask = 0x01,
		.inverted  = 1,
	पूर्ण,
	अणु
		.role      = EM28XX_LED_ILLUMINATION,
		.gpio_reg  = EM2874_R80_GPIO_P0_CTRL,
		.gpio_mask = 0x40,
		.inverted  = 1,
	पूर्ण,
	अणु-1, 0, 0, 0पूर्ण,
पूर्ण;

अटल काष्ठा em28xx_led kworld_ub435q_v3_leds[] = अणु
	अणु
		.role      = EM28XX_LED_DIGITAL_CAPTURING,
		.gpio_reg  = EM2874_R80_GPIO_P0_CTRL,
		.gpio_mask = 0x80,
		.inverted  = 1,
	पूर्ण,
	अणु-1, 0, 0, 0पूर्ण,
पूर्ण;

अटल काष्ठा em28xx_led pctv_80e_leds[] = अणु
	अणु
		.role      = EM28XX_LED_DIGITAL_CAPTURING,
		.gpio_reg  = EM2874_R80_GPIO_P0_CTRL,
		.gpio_mask = 0x80,
		.inverted  = 0,
	पूर्ण,
	अणु-1, 0, 0, 0पूर्ण,
पूर्ण;

अटल काष्ठा em28xx_led terratec_grabby_leds[] = अणु
	अणु
		.role      = EM28XX_LED_ANALOG_CAPTURING,
		.gpio_reg  = EM2820_R08_GPIO_CTRL,
		.gpio_mask = EM_GPIO_3,
		.inverted  = 1,
	पूर्ण,
	अणु-1, 0, 0, 0पूर्ण,
पूर्ण;

अटल काष्ठा em28xx_led hauppauge_dualhd_leds[] = अणु
	अणु
		.role      = EM28XX_LED_DIGITAL_CAPTURING,
		.gpio_reg  = EM2874_R80_GPIO_P0_CTRL,
		.gpio_mask = EM_GPIO_1,
		.inverted  = 1,
	पूर्ण,
	अणु
		.role      = EM28XX_LED_DIGITAL_CAPTURING_TS2,
		.gpio_reg  = EM2874_R80_GPIO_P0_CTRL,
		.gpio_mask = EM_GPIO_3,
		.inverted  = 1,
	पूर्ण,
	अणु-1, 0, 0, 0पूर्ण,
पूर्ण;

अटल काष्ठा em28xx_led hauppauge_usb_quadhd_leds[] = अणु
	अणु
		.role      = EM28XX_LED_DIGITAL_CAPTURING,
		.gpio_reg  = EM2874_R80_GPIO_P0_CTRL,
		.gpio_mask = EM_GPIO_2,
		.inverted  = 1,
	पूर्ण,
	अणु
		.role      = EM28XX_LED_DIGITAL_CAPTURING_TS2,
		.gpio_reg  = EM2874_R80_GPIO_P0_CTRL,
		.gpio_mask = EM_GPIO_0,
		.inverted  = 1,
	पूर्ण,
	अणु-1, 0, 0, 0पूर्ण,
पूर्ण;

/*
 *  Board definitions
 */
स्थिर काष्ठा em28xx_board em28xx_boards[] = अणु
	[EM2750_BOARD_UNKNOWN] = अणु
		.name          = "EM2710/EM2750/EM2751 webcam grabber",
		.xclk          = EM28XX_XCLK_FREQUENCY_20MHZ,
		.tuner_type    = TUNER_ABSENT,
		.is_webcam     = 1,
		.input         = अणु अणु
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = 0,
			.amux     = EM28XX_AMUX_VIDEO,
			.gpio     = silvercrest_reg_seq,
		पूर्ण पूर्ण,
	पूर्ण,
	[EM2800_BOARD_UNKNOWN] = अणु
		.name         = "Unknown EM2800 video grabber",
		.is_em2800    = 1,
		.tda9887_conf = TDA9887_PRESENT,
		.decoder      = EM28XX_SAA711X,
		.tuner_type   = TUNER_ABSENT,
		.input        = अणु अणु
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = SAA7115_COMPOSITE0,
			.amux     = EM28XX_AMUX_LINE_IN,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = SAA7115_SVIDEO3,
			.amux     = EM28XX_AMUX_LINE_IN,
		पूर्ण पूर्ण,
	पूर्ण,
	[EM2820_BOARD_UNKNOWN] = अणु
		.name          = "Unknown EM2750/28xx video grabber",
		.tuner_type    = TUNER_ABSENT,
		.is_webcam     = 1,	/* To enable sensor probe */
	पूर्ण,
	[EM2882_BOARD_ZOLID_HYBRID_TV_STICK] = अणु
		.name			= ":ZOLID HYBRID TV STICK",
		.tuner_type		= TUNER_XC2028,
		.tuner_gpio		= zolid_tuner,
		.decoder		= EM28XX_TVP5150,
		.xclk			= EM28XX_XCLK_FREQUENCY_12MHZ,
		.mts_firmware	= 1,
		.has_dvb		= 1,
		.dvb_gpio		= zolid_digital,
	पूर्ण,
	[EM2750_BOARD_DLCW_130] = अणु
		/* Beijing Huaqi Inक्रमmation Digital Technology Co., Ltd */
		.name          = "Huaqi DLCW-130",
		.valid         = EM28XX_BOARD_NOT_VALIDATED,
		.xclk          = EM28XX_XCLK_FREQUENCY_48MHZ,
		.tuner_type    = TUNER_ABSENT,
		.is_webcam     = 1,
		.input         = अणु अणु
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = 0,
			.amux     = EM28XX_AMUX_VIDEO,
		पूर्ण पूर्ण,
	पूर्ण,
	[EM2820_BOARD_KWORLD_PVRTV2800RF] = अणु
		.name         = "Kworld PVR TV 2800 RF",
		.tuner_type   = TUNER_TEMIC_PAL,
		.tda9887_conf = TDA9887_PRESENT,
		.decoder      = EM28XX_SAA711X,
		.input        = अणु अणु
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = SAA7115_COMPOSITE0,
			.amux     = EM28XX_AMUX_LINE_IN,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = SAA7115_SVIDEO3,
			.amux     = EM28XX_AMUX_LINE_IN,
		पूर्ण पूर्ण,
	पूर्ण,
	[EM2820_BOARD_GADMEI_TVR200] = अणु
		.name         = "Gadmei TVR200",
		.tuner_type   = TUNER_LG_PAL_NEW_TAPC,
		.tda9887_conf = TDA9887_PRESENT,
		.decoder      = EM28XX_SAA711X,
		.input        = अणु अणु
			.type     = EM28XX_VMUX_TELEVISION,
			.vmux     = SAA7115_COMPOSITE2,
			.amux     = EM28XX_AMUX_LINE_IN,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = SAA7115_COMPOSITE0,
			.amux     = EM28XX_AMUX_LINE_IN,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = SAA7115_SVIDEO3,
			.amux     = EM28XX_AMUX_LINE_IN,
		पूर्ण पूर्ण,
	पूर्ण,
	[EM2820_BOARD_TERRATEC_CINERGY_250] = अणु
		.name         = "Terratec Cinergy 250 USB",
		.tuner_type   = TUNER_LG_PAL_NEW_TAPC,
		.has_ir_i2c   = 1,
		.tda9887_conf = TDA9887_PRESENT,
		.decoder      = EM28XX_SAA711X,
		.input        = अणु अणु
			.type     = EM28XX_VMUX_TELEVISION,
			.vmux     = SAA7115_COMPOSITE2,
			.amux     = EM28XX_AMUX_VIDEO,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = SAA7115_COMPOSITE0,
			.amux     = EM28XX_AMUX_LINE_IN,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = SAA7115_SVIDEO3,
			.amux     = EM28XX_AMUX_LINE_IN,
		पूर्ण पूर्ण,
	पूर्ण,
	[EM2820_BOARD_PINNACLE_USB_2] = अणु
		.name         = "Pinnacle PCTV USB 2",
		.tuner_type   = TUNER_LG_PAL_NEW_TAPC,
		.has_ir_i2c   = 1,
		.tda9887_conf = TDA9887_PRESENT,
		.decoder      = EM28XX_SAA711X,
		.input        = अणु अणु
			.type     = EM28XX_VMUX_TELEVISION,
			.vmux     = SAA7115_COMPOSITE2,
			.amux     = EM28XX_AMUX_VIDEO,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = SAA7115_COMPOSITE0,
			.amux     = EM28XX_AMUX_LINE_IN,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = SAA7115_SVIDEO3,
			.amux     = EM28XX_AMUX_LINE_IN,
		पूर्ण पूर्ण,
	पूर्ण,
	[EM2820_BOARD_HAUPPAUGE_WINTV_USB_2] = अणु
		.name         = "Hauppauge WinTV USB 2",
		.tuner_type   = TUNER_PHILIPS_FM1236_MK3,
		.tda9887_conf = TDA9887_PRESENT |
				TDA9887_PORT1_ACTIVE |
				TDA9887_PORT2_ACTIVE,
		.decoder      = EM28XX_TVP5150,
		.has_msp34xx  = 1,
		.has_ir_i2c   = 1,
		.input        = अणु अणु
			.type     = EM28XX_VMUX_TELEVISION,
			.vmux     = TVP5150_COMPOSITE0,
			.amux     = MSP_INPUT_DEFAULT,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = TVP5150_SVIDEO,
			.amux     = MSP_INPUT(MSP_IN_SCART1, MSP_IN_TUNER1,
					MSP_DSP_IN_SCART, MSP_DSP_IN_SCART),
		पूर्ण पूर्ण,
	पूर्ण,
	[EM2820_BOARD_DLINK_USB_TV] = अणु
		.name         = "D-Link DUB-T210 TV Tuner",
		.valid        = EM28XX_BOARD_NOT_VALIDATED,
		.tuner_type   = TUNER_LG_PAL_NEW_TAPC,
		.tda9887_conf = TDA9887_PRESENT,
		.decoder      = EM28XX_SAA711X,
		.input        = अणु अणु
			.type     = EM28XX_VMUX_TELEVISION,
			.vmux     = SAA7115_COMPOSITE2,
			.amux     = EM28XX_AMUX_LINE_IN,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = SAA7115_COMPOSITE0,
			.amux     = EM28XX_AMUX_LINE_IN,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = SAA7115_SVIDEO3,
			.amux     = EM28XX_AMUX_LINE_IN,
		पूर्ण पूर्ण,
	पूर्ण,
	[EM2820_BOARD_HERCULES_SMART_TV_USB2] = अणु
		.name         = "Hercules Smart TV USB 2.0",
		.valid        = EM28XX_BOARD_NOT_VALIDATED,
		.tuner_type   = TUNER_LG_PAL_NEW_TAPC,
		.tda9887_conf = TDA9887_PRESENT,
		.decoder      = EM28XX_SAA711X,
		.input        = अणु अणु
			.type     = EM28XX_VMUX_TELEVISION,
			.vmux     = SAA7115_COMPOSITE2,
			.amux     = EM28XX_AMUX_LINE_IN,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = SAA7115_COMPOSITE0,
			.amux     = EM28XX_AMUX_LINE_IN,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = SAA7115_SVIDEO3,
			.amux     = EM28XX_AMUX_LINE_IN,
		पूर्ण पूर्ण,
	पूर्ण,
	[EM2820_BOARD_PINNACLE_USB_2_FM1216ME] = अणु
		.name         = "Pinnacle PCTV USB 2 (Philips FM1216ME)",
		.valid        = EM28XX_BOARD_NOT_VALIDATED,
		.tuner_type   = TUNER_PHILIPS_FM1216ME_MK3,
		.tda9887_conf = TDA9887_PRESENT,
		.decoder      = EM28XX_SAA711X,
		.input        = अणु अणु
			.type     = EM28XX_VMUX_TELEVISION,
			.vmux     = SAA7115_COMPOSITE2,
			.amux     = EM28XX_AMUX_VIDEO,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = SAA7115_COMPOSITE0,
			.amux     = EM28XX_AMUX_LINE_IN,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = SAA7115_SVIDEO3,
			.amux     = EM28XX_AMUX_LINE_IN,
		पूर्ण पूर्ण,
	पूर्ण,
	[EM2820_BOARD_GADMEI_UTV310] = अणु
		.name         = "Gadmei UTV310",
		.valid        = EM28XX_BOARD_NOT_VALIDATED,
		.tuner_type   = TUNER_TNF_5335MF,
		.tda9887_conf = TDA9887_PRESENT,
		.decoder      = EM28XX_SAA711X,
		.input        = अणु अणु
			.type     = EM28XX_VMUX_TELEVISION,
			.vmux     = SAA7115_COMPOSITE1,
			.amux     = EM28XX_AMUX_LINE_IN,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = SAA7115_COMPOSITE0,
			.amux     = EM28XX_AMUX_LINE_IN,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = SAA7115_SVIDEO3,
			.amux     = EM28XX_AMUX_LINE_IN,
		पूर्ण पूर्ण,
	पूर्ण,
	[EM2820_BOARD_LEADTEK_WINFAST_USBII_DELUXE] = अणु
		.name         = "Leadtek Winfast USB II Deluxe",
		.valid        = EM28XX_BOARD_NOT_VALIDATED,
		.tuner_type   = TUNER_PHILIPS_FM1216ME_MK3,
		.has_ir_i2c   = 1,
		.tvaudio_addr = 0x58,
		.tda9887_conf = TDA9887_PRESENT |
				TDA9887_PORT2_ACTIVE |
				TDA9887_QSS,
		.decoder      = EM28XX_SAA711X,
		.adecoder     = EM28XX_TVAUDIO,
		.input        = अणु अणु
			.type     = EM28XX_VMUX_TELEVISION,
			.vmux     = SAA7115_COMPOSITE4,
			.amux     = EM28XX_AMUX_AUX,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = SAA7115_COMPOSITE5,
			.amux     = EM28XX_AMUX_LINE_IN,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = SAA7115_SVIDEO3,
			.amux     = EM28XX_AMUX_LINE_IN,
		पूर्ण पूर्ण,
			.radio	  = अणु
			.type     = EM28XX_RADIO,
			.amux     = EM28XX_AMUX_AUX,
			पूर्ण
	पूर्ण,
	[EM2820_BOARD_VIDEOLOGY_20K14XUSB] = अणु
		.name         = "Videology 20K14XUSB USB2.0",
		.valid        = EM28XX_BOARD_NOT_VALIDATED,
		.tuner_type   = TUNER_ABSENT,
		.is_webcam    = 1,
		.input        = अणु अणु
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = 0,
			.amux     = EM28XX_AMUX_VIDEO,
		पूर्ण पूर्ण,
	पूर्ण,
	[EM2820_BOARD_SILVERCREST_WEBCAM] = अणु
		.name         = "Silvercrest Webcam 1.3mpix",
		.tuner_type   = TUNER_ABSENT,
		.is_webcam    = 1,
		.input        = अणु अणु
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = 0,
			.amux     = EM28XX_AMUX_VIDEO,
			.gpio     = silvercrest_reg_seq,
		पूर्ण पूर्ण,
	पूर्ण,
	[EM2821_BOARD_SUPERCOMP_USB_2] = अणु
		.name         = "Supercomp USB 2.0 TV",
		.valid        = EM28XX_BOARD_NOT_VALIDATED,
		.tuner_type   = TUNER_PHILIPS_FM1236_MK3,
		.tda9887_conf = TDA9887_PRESENT |
				TDA9887_PORT1_ACTIVE |
				TDA9887_PORT2_ACTIVE,
		.decoder      = EM28XX_SAA711X,
		.input        = अणु अणु
			.type     = EM28XX_VMUX_TELEVISION,
			.vmux     = SAA7115_COMPOSITE2,
			.amux     = EM28XX_AMUX_LINE_IN,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = SAA7115_COMPOSITE0,
			.amux     = EM28XX_AMUX_VIDEO,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = SAA7115_SVIDEO3,
			.amux     = EM28XX_AMUX_LINE_IN,
		पूर्ण पूर्ण,
	पूर्ण,
	[EM2821_BOARD_USBGEAR_VD204] = अणु
		.name         = "Usbgear VD204v9",
		.valid        = EM28XX_BOARD_NOT_VALIDATED,
		.tuner_type   = TUNER_ABSENT,	/* Capture only device */
		.decoder      = EM28XX_SAA711X,
		.input        = अणु अणु
			.type  = EM28XX_VMUX_COMPOSITE,
			.vmux  = SAA7115_COMPOSITE0,
			.amux  = EM28XX_AMUX_LINE_IN,
		पूर्ण, अणु
			.type  = EM28XX_VMUX_SVIDEO,
			.vmux  = SAA7115_SVIDEO3,
			.amux  = EM28XX_AMUX_LINE_IN,
		पूर्ण पूर्ण,
	पूर्ण,
	[EM2860_BOARD_NETGMBH_CAM] = अणु
		/* Beijing Huaqi Inक्रमmation Digital Technology Co., Ltd */
		.name         = "NetGMBH Cam",
		.valid        = EM28XX_BOARD_NOT_VALIDATED,
		.tuner_type   = TUNER_ABSENT,
		.is_webcam    = 1,
		.input        = अणु अणु
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = 0,
			.amux     = EM28XX_AMUX_VIDEO,
		पूर्ण पूर्ण,
	पूर्ण,
	[EM2860_BOARD_TYPHOON_DVD_MAKER] = अणु
		.name         = "Typhoon DVD Maker",
		.decoder      = EM28XX_SAA711X,
		.tuner_type   = TUNER_ABSENT,	/* Capture only device */
		.input        = अणु अणु
			.type  = EM28XX_VMUX_COMPOSITE,
			.vmux  = SAA7115_COMPOSITE0,
			.amux  = EM28XX_AMUX_LINE_IN,
		पूर्ण, अणु
			.type  = EM28XX_VMUX_SVIDEO,
			.vmux  = SAA7115_SVIDEO3,
			.amux  = EM28XX_AMUX_LINE_IN,
		पूर्ण पूर्ण,
	पूर्ण,
	[EM2860_BOARD_GADMEI_UTV330] = अणु
		.name         = "Gadmei UTV330",
		.valid        = EM28XX_BOARD_NOT_VALIDATED,
		.tuner_type   = TUNER_TNF_5335MF,
		.tda9887_conf = TDA9887_PRESENT,
		.decoder      = EM28XX_SAA711X,
		.input        = अणु अणु
			.type     = EM28XX_VMUX_TELEVISION,
			.vmux     = SAA7115_COMPOSITE2,
			.amux     = EM28XX_AMUX_VIDEO,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = SAA7115_COMPOSITE0,
			.amux     = EM28XX_AMUX_LINE_IN,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = SAA7115_SVIDEO3,
			.amux     = EM28XX_AMUX_LINE_IN,
		पूर्ण पूर्ण,
	पूर्ण,
	[EM2861_BOARD_GADMEI_UTV330PLUS] = अणु
		.name         = "Gadmei UTV330+",
		.tuner_type   = TUNER_TNF_5335MF,
		.tda9887_conf = TDA9887_PRESENT,
		.ir_codes     = RC_MAP_GADMEI_RM008Z,
		.decoder      = EM28XX_SAA711X,
		.xclk         = EM28XX_XCLK_FREQUENCY_12MHZ,
		.input        = अणु अणु
			.type     = EM28XX_VMUX_TELEVISION,
			.vmux     = SAA7115_COMPOSITE2,
			.amux     = EM28XX_AMUX_VIDEO,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = SAA7115_COMPOSITE0,
			.amux     = EM28XX_AMUX_LINE_IN,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = SAA7115_SVIDEO3,
			.amux     = EM28XX_AMUX_LINE_IN,
		पूर्ण पूर्ण,
	पूर्ण,
	[EM2860_BOARD_TERRATEC_HYBRID_XS] = अणु
		.name         = "Terratec Cinergy A Hybrid XS",
		.valid        = EM28XX_BOARD_NOT_VALIDATED,
		.tuner_type   = TUNER_XC2028,
		.tuner_gpio   = शेष_tuner_gpio,
		.decoder      = EM28XX_TVP5150,

		.input        = अणु अणु
			.type     = EM28XX_VMUX_TELEVISION,
			.vmux     = TVP5150_COMPOSITE0,
			.amux     = EM28XX_AMUX_VIDEO,
			.gpio     = hauppauge_wपूर्णांकv_hvr_900_analog,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = TVP5150_COMPOSITE1,
			.amux     = EM28XX_AMUX_LINE_IN,
			.gpio     = hauppauge_wपूर्णांकv_hvr_900_analog,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = TVP5150_SVIDEO,
			.amux     = EM28XX_AMUX_LINE_IN,
			.gpio     = hauppauge_wपूर्णांकv_hvr_900_analog,
		पूर्ण पूर्ण,
	पूर्ण,
	[EM2861_BOARD_KWORLD_PVRTV_300U] = अणु
		.name	      = "KWorld PVRTV 300U",
		.valid        = EM28XX_BOARD_NOT_VALIDATED,
		.tuner_type   = TUNER_XC2028,
		.tuner_gpio   = शेष_tuner_gpio,
		.decoder      = EM28XX_TVP5150,
		.input        = अणु अणु
			.type     = EM28XX_VMUX_TELEVISION,
			.vmux     = TVP5150_COMPOSITE0,
			.amux     = EM28XX_AMUX_VIDEO,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = TVP5150_COMPOSITE1,
			.amux     = EM28XX_AMUX_LINE_IN,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = TVP5150_SVIDEO,
			.amux     = EM28XX_AMUX_LINE_IN,
		पूर्ण पूर्ण,
	पूर्ण,
	[EM2861_BOARD_YAKUMO_MOVIE_MIXER] = अणु
		.name          = "Yakumo MovieMixer",
		.tuner_type    = TUNER_ABSENT,	/* Capture only device */
		.decoder       = EM28XX_TVP5150,
		.input         = अणु अणु
			.type     = EM28XX_VMUX_TELEVISION,
			.vmux     = TVP5150_COMPOSITE0,
			.amux     = EM28XX_AMUX_VIDEO,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = TVP5150_COMPOSITE1,
			.amux     = EM28XX_AMUX_LINE_IN,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = TVP5150_SVIDEO,
			.amux     = EM28XX_AMUX_LINE_IN,
		पूर्ण पूर्ण,
	पूर्ण,
	[EM2860_BOARD_TVP5150_REFERENCE_DESIGN] = अणु
		.name          = "EM2860/TVP5150 Reference Design",
		.tuner_type    = TUNER_ABSENT,	/* Capture only device */
		.decoder       = EM28XX_TVP5150,
		.input         = अणु अणु
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = TVP5150_COMPOSITE1,
			.amux     = EM28XX_AMUX_LINE_IN,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = TVP5150_SVIDEO,
			.amux     = EM28XX_AMUX_LINE_IN,
		पूर्ण पूर्ण,
	पूर्ण,
	[EM2861_BOARD_PLEXTOR_PX_TV100U] = अणु
		.name         = "Plextor ConvertX PX-TV100U",
		.tuner_type   = TUNER_TNF_5335MF,
		.xclk         = EM28XX_XCLK_I2S_MSB_TIMING |
				EM28XX_XCLK_FREQUENCY_12MHZ,
		.tda9887_conf = TDA9887_PRESENT,
		.decoder      = EM28XX_TVP5150,
		.has_msp34xx  = 1,
		.input        = अणु अणु
			.type     = EM28XX_VMUX_TELEVISION,
			.vmux     = TVP5150_COMPOSITE0,
			.amux     = EM28XX_AMUX_LINE_IN,
			.gpio     = pinnacle_hybrid_pro_analog,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = TVP5150_COMPOSITE1,
			.amux     = EM28XX_AMUX_LINE_IN,
			.gpio     = pinnacle_hybrid_pro_analog,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = TVP5150_SVIDEO,
			.amux     = EM28XX_AMUX_LINE_IN,
			.gpio     = pinnacle_hybrid_pro_analog,
		पूर्ण पूर्ण,
	पूर्ण,

	/* Those boards with em2870 are DVB Only*/

	[EM2870_BOARD_TERRATEC_XS] = अणु
		.name         = "Terratec Cinergy T XS",
		.valid        = EM28XX_BOARD_NOT_VALIDATED,
		.tuner_type   = TUNER_XC2028,
		.tuner_gpio   = शेष_tuner_gpio,
	पूर्ण,
	[EM2870_BOARD_TERRATEC_XS_MT2060] = अणु
		.name         = "Terratec Cinergy T XS (MT2060)",
		.xclk         = EM28XX_XCLK_IR_RC5_MODE |
				EM28XX_XCLK_FREQUENCY_12MHZ,
		.i2c_speed    = EM28XX_I2C_CLK_WAIT_ENABLE,
		.tuner_type   = TUNER_ABSENT, /* MT2060 */
		.has_dvb      = 1,
		.tuner_gpio   = शेष_tuner_gpio,
	पूर्ण,
	[EM2870_BOARD_KWORLD_350U] = अणु
		.name         = "Kworld 350 U DVB-T",
		.valid        = EM28XX_BOARD_NOT_VALIDATED,
		.tuner_type   = TUNER_XC2028,
		.tuner_gpio   = शेष_tuner_gpio,
	पूर्ण,
	[EM2870_BOARD_KWORLD_355U] = अणु
		.name         = "Kworld 355 U DVB-T",
		.valid        = EM28XX_BOARD_NOT_VALIDATED,
		.tuner_type   = TUNER_ABSENT,
		.tuner_gpio   = शेष_tuner_gpio,
		.has_dvb      = 1,
		.dvb_gpio     = शेष_digital,
	पूर्ण,
	[EM2870_BOARD_PINNACLE_PCTV_DVB] = अणु
		.name         = "Pinnacle PCTV DVB-T",
		.valid        = EM28XX_BOARD_NOT_VALIDATED,
		.tuner_type   = TUNER_ABSENT, /* MT2060 */
		/* djh - I have serious करोubts this is right... */
		.xclk         = EM28XX_XCLK_IR_RC5_MODE |
				EM28XX_XCLK_FREQUENCY_10MHZ,
	पूर्ण,
	[EM2870_BOARD_COMPRO_VIDEOMATE] = अणु
		.name         = "Compro, VideoMate U3",
		.valid        = EM28XX_BOARD_NOT_VALIDATED,
		.tuner_type   = TUNER_ABSENT, /* MT2060 */
	पूर्ण,

	[EM2880_BOARD_TERRATEC_HYBRID_XS_FR] = अणु
		.name         = "Terratec Hybrid XS Secam",
		.has_msp34xx  = 1,
		.tuner_type   = TUNER_XC2028,
		.tuner_gpio   = शेष_tuner_gpio,
		.decoder      = EM28XX_TVP5150,
		.has_dvb      = 1,
		.dvb_gpio     = terratec_cinergy_USB_XS_FR_digital,
		.input        = अणु अणु
			.type     = EM28XX_VMUX_TELEVISION,
			.vmux     = TVP5150_COMPOSITE0,
			.amux     = EM28XX_AMUX_VIDEO,
			.gpio     = terratec_cinergy_USB_XS_FR_analog,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = TVP5150_COMPOSITE1,
			.amux     = EM28XX_AMUX_LINE_IN,
			.gpio     = terratec_cinergy_USB_XS_FR_analog,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = TVP5150_SVIDEO,
			.amux     = EM28XX_AMUX_LINE_IN,
			.gpio     = terratec_cinergy_USB_XS_FR_analog,
		पूर्ण पूर्ण,
	पूर्ण,
	[EM2884_BOARD_TERRATEC_H5] = अणु
		.name         = "Terratec Cinergy H5",
		.has_dvb      = 1,
#अगर 0
		.tuner_type   = TUNER_PHILIPS_TDA8290,
		.tuner_addr   = 0x41,
		.dvb_gpio     = terratec_h5_digital, /* FIXME: probably wrong */
		.tuner_gpio   = terratec_h5_gpio,
#अन्यथा
		.tuner_type   = TUNER_ABSENT,
#पूर्ण_अगर
		.def_i2c_bus  = 1,
		.i2c_speed    = EM28XX_I2C_CLK_WAIT_ENABLE |
				EM28XX_I2C_FREQ_400_KHZ,
	पूर्ण,
	[EM2884_BOARD_TERRATEC_H6] = अणु
		.name         = "Terratec Cinergy H6 rev. 2",
		.has_dvb      = 1,
		.ir_codes     = RC_MAP_NEC_TERRATEC_CINERGY_XS,
#अगर 0
		.tuner_type   = TUNER_PHILIPS_TDA8290,
		.tuner_addr   = 0x41,
		.dvb_gpio     = terratec_h5_digital, /* FIXME: probably wrong */
		.tuner_gpio   = terratec_h5_gpio,
#अन्यथा
		.tuner_type   = TUNER_ABSENT,
#पूर्ण_अगर
		.def_i2c_bus  = 1,
		.i2c_speed    = EM28XX_I2C_CLK_WAIT_ENABLE |
				EM28XX_I2C_FREQ_400_KHZ,
	पूर्ण,
	[EM2884_BOARD_HAUPPAUGE_WINTV_HVR_930C] = अणु
		.name         = "Hauppauge WinTV HVR 930C",
		.has_dvb      = 1,
#अगर 0 /* FIXME: Add analog support */
		.tuner_type   = TUNER_XC5000,
		.tuner_addr   = 0x41,
		.dvb_gpio     = hauppauge_930c_digital,
		.tuner_gpio   = hauppauge_930c_gpio,
#अन्यथा
		.tuner_type   = TUNER_ABSENT,
#पूर्ण_अगर
		.ir_codes     = RC_MAP_HAUPPAUGE,
		.def_i2c_bus  = 1,
		.i2c_speed    = EM28XX_I2C_CLK_WAIT_ENABLE |
				EM28XX_I2C_FREQ_400_KHZ,
	पूर्ण,
	[EM2884_BOARD_C3TECH_DIGITAL_DUO] = अणु
		.name         = "C3 Tech Digital Duo HDTV/SDTV USB",
		.has_dvb      = 1,
		/* FIXME: Add analog support - need a saa7136 driver */
		.tuner_type = TUNER_ABSENT,	/* Digital-only TDA18271HD */
		.ir_codes     = RC_MAP_EMPTY,
		.def_i2c_bus  = 1,
		.i2c_speed    = EM28XX_I2C_CLK_WAIT_ENABLE,
		.dvb_gpio     = c3tech_digital_duo_digital,
	पूर्ण,
	[EM2884_BOARD_CINERGY_HTC_STICK] = अणु
		.name         = "Terratec Cinergy HTC Stick",
		.has_dvb      = 1,
		.ir_codes     = RC_MAP_NEC_TERRATEC_CINERGY_XS,
		.tuner_type   = TUNER_ABSENT,
		.def_i2c_bus  = 1,
		.i2c_speed    = EM28XX_I2C_CLK_WAIT_ENABLE |
				EM28XX_I2C_FREQ_400_KHZ,
	पूर्ण,
	[EM2884_BOARD_ELGATO_EYETV_HYBRID_2008] = अणु
		.name         = "Elgato EyeTV Hybrid 2008 INT",
		.has_dvb      = 1,
		.ir_codes     = RC_MAP_NEC_TERRATEC_CINERGY_XS,
		.tuner_type   = TUNER_ABSENT,
		.def_i2c_bus  = 1,
		.i2c_speed    = EM28XX_I2C_CLK_WAIT_ENABLE |
				EM28XX_I2C_FREQ_400_KHZ,
	पूर्ण,
	[EM2880_BOARD_HAUPPAUGE_WINTV_HVR_900] = अणु
		.name         = "Hauppauge WinTV HVR 900",
		.tda9887_conf = TDA9887_PRESENT,
		.tuner_type   = TUNER_XC2028,
		.tuner_gpio   = शेष_tuner_gpio,
		.mts_firmware = 1,
		.has_dvb      = 1,
		.dvb_gpio     = hauppauge_wपूर्णांकv_hvr_900_digital,
		.ir_codes     = RC_MAP_HAUPPAUGE,
		.decoder      = EM28XX_TVP5150,
		.input        = अणु अणु
			.type     = EM28XX_VMUX_TELEVISION,
			.vmux     = TVP5150_COMPOSITE0,
			.amux     = EM28XX_AMUX_VIDEO,
			.gpio     = hauppauge_wपूर्णांकv_hvr_900_analog,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = TVP5150_COMPOSITE1,
			.amux     = EM28XX_AMUX_LINE_IN,
			.gpio     = hauppauge_wपूर्णांकv_hvr_900_analog,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = TVP5150_SVIDEO,
			.amux     = EM28XX_AMUX_LINE_IN,
			.gpio     = hauppauge_wपूर्णांकv_hvr_900_analog,
		पूर्ण पूर्ण,
	पूर्ण,
	[EM2880_BOARD_HAUPPAUGE_WINTV_HVR_900_R2] = अणु
		.name         = "Hauppauge WinTV HVR 900 (R2)",
		.tda9887_conf = TDA9887_PRESENT,
		.tuner_type   = TUNER_XC2028,
		.tuner_gpio   = शेष_tuner_gpio,
		.mts_firmware = 1,
		.has_dvb      = 1,
		.dvb_gpio     = hauppauge_wपूर्णांकv_hvr_900R2_digital,
		.ir_codes     = RC_MAP_HAUPPAUGE,
		.decoder      = EM28XX_TVP5150,
		.input        = अणु अणु
			.type     = EM28XX_VMUX_TELEVISION,
			.vmux     = TVP5150_COMPOSITE0,
			.amux     = EM28XX_AMUX_VIDEO,
			.gpio     = hauppauge_wपूर्णांकv_hvr_900_analog,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = TVP5150_COMPOSITE1,
			.amux     = EM28XX_AMUX_LINE_IN,
			.gpio     = hauppauge_wपूर्णांकv_hvr_900_analog,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = TVP5150_SVIDEO,
			.amux     = EM28XX_AMUX_LINE_IN,
			.gpio     = hauppauge_wपूर्णांकv_hvr_900_analog,
		पूर्ण पूर्ण,
	पूर्ण,
	[EM2883_BOARD_HAUPPAUGE_WINTV_HVR_850] = अणु
		.name           = "Hauppauge WinTV HVR 850",
		.tuner_type     = TUNER_XC2028,
		.tuner_gpio     = शेष_tuner_gpio,
		.mts_firmware   = 1,
		.has_dvb        = 1,
		.dvb_gpio       = hauppauge_wपूर्णांकv_hvr_900_digital,
		.ir_codes       = RC_MAP_HAUPPAUGE,
		.decoder        = EM28XX_TVP5150,
		.input          = अणु अणु
			.type     = EM28XX_VMUX_TELEVISION,
			.vmux     = TVP5150_COMPOSITE0,
			.amux     = EM28XX_AMUX_VIDEO,
			.gpio     = hauppauge_wपूर्णांकv_hvr_900_analog,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = TVP5150_COMPOSITE1,
			.amux     = EM28XX_AMUX_LINE_IN,
			.gpio     = hauppauge_wपूर्णांकv_hvr_900_analog,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = TVP5150_SVIDEO,
			.amux     = EM28XX_AMUX_LINE_IN,
			.gpio     = hauppauge_wपूर्णांकv_hvr_900_analog,
		पूर्ण पूर्ण,
	पूर्ण,
	[EM2883_BOARD_HAUPPAUGE_WINTV_HVR_950] = अणु
		.name           = "Hauppauge WinTV HVR 950",
		.tuner_type     = TUNER_XC2028,
		.tuner_gpio     = शेष_tuner_gpio,
		.mts_firmware   = 1,
		.has_dvb        = 1,
		.dvb_gpio       = hauppauge_wपूर्णांकv_hvr_900_digital,
		.ir_codes       = RC_MAP_HAUPPAUGE,
		.decoder        = EM28XX_TVP5150,
		.input          = अणु अणु
			.type     = EM28XX_VMUX_TELEVISION,
			.vmux     = TVP5150_COMPOSITE0,
			.amux     = EM28XX_AMUX_VIDEO,
			.gpio     = hauppauge_wपूर्णांकv_hvr_900_analog,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = TVP5150_COMPOSITE1,
			.amux     = EM28XX_AMUX_LINE_IN,
			.gpio     = hauppauge_wपूर्णांकv_hvr_900_analog,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = TVP5150_SVIDEO,
			.amux     = EM28XX_AMUX_LINE_IN,
			.gpio     = hauppauge_wपूर्णांकv_hvr_900_analog,
		पूर्ण पूर्ण,
	पूर्ण,
	[EM2880_BOARD_PINNACLE_PCTV_HD_PRO] = अणु
		.name           = "Pinnacle PCTV HD Pro Stick",
		.tuner_type     = TUNER_XC2028,
		.tuner_gpio   = शेष_tuner_gpio,
		.mts_firmware   = 1,
		.has_dvb        = 1,
		.dvb_gpio       = hauppauge_wपूर्णांकv_hvr_900_digital,
		.ir_codes       = RC_MAP_PINNACLE_PCTV_HD,
		.decoder        = EM28XX_TVP5150,
		.input          = अणु अणु
			.type     = EM28XX_VMUX_TELEVISION,
			.vmux     = TVP5150_COMPOSITE0,
			.amux     = EM28XX_AMUX_VIDEO,
			.gpio     = hauppauge_wपूर्णांकv_hvr_900_analog,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = TVP5150_COMPOSITE1,
			.amux     = EM28XX_AMUX_LINE_IN,
			.gpio     = hauppauge_wपूर्णांकv_hvr_900_analog,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = TVP5150_SVIDEO,
			.amux     = EM28XX_AMUX_LINE_IN,
			.gpio     = hauppauge_wपूर्णांकv_hvr_900_analog,
		पूर्ण पूर्ण,
	पूर्ण,
	[EM2880_BOARD_AMD_ATI_TV_WONDER_HD_600] = अणु
		.name           = "AMD ATI TV Wonder HD 600",
		.tuner_type     = TUNER_XC2028,
		.tuner_gpio     = शेष_tuner_gpio,
		.mts_firmware   = 1,
		.has_dvb        = 1,
		.dvb_gpio       = hauppauge_wपूर्णांकv_hvr_900_digital,
		.ir_codes       = RC_MAP_ATI_TV_WONDER_HD_600,
		.decoder        = EM28XX_TVP5150,
		.input          = अणु अणु
			.type     = EM28XX_VMUX_TELEVISION,
			.vmux     = TVP5150_COMPOSITE0,
			.amux     = EM28XX_AMUX_VIDEO,
			.gpio     = hauppauge_wपूर्णांकv_hvr_900_analog,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = TVP5150_COMPOSITE1,
			.amux     = EM28XX_AMUX_LINE_IN,
			.gpio     = hauppauge_wपूर्णांकv_hvr_900_analog,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = TVP5150_SVIDEO,
			.amux     = EM28XX_AMUX_LINE_IN,
			.gpio     = hauppauge_wपूर्णांकv_hvr_900_analog,
		पूर्ण पूर्ण,
	पूर्ण,
	[EM2880_BOARD_TERRATEC_HYBRID_XS] = अणु
		.name           = "Terratec Hybrid XS",
		.tuner_type     = TUNER_XC2028,
		.tuner_gpio     = शेष_tuner_gpio,
		.decoder        = EM28XX_TVP5150,
		.has_dvb        = 1,
		.dvb_gpio       = शेष_digital,
		.ir_codes       = RC_MAP_TERRATEC_CINERGY_XS,
		.xclk           = EM28XX_XCLK_FREQUENCY_12MHZ, /* NEC IR */
		.input          = अणु अणु
			.type     = EM28XX_VMUX_TELEVISION,
			.vmux     = TVP5150_COMPOSITE0,
			.amux     = EM28XX_AMUX_VIDEO,
			.gpio     = शेष_analog,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = TVP5150_COMPOSITE1,
			.amux     = EM28XX_AMUX_LINE_IN,
			.gpio     = शेष_analog,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = TVP5150_SVIDEO,
			.amux     = EM28XX_AMUX_LINE_IN,
			.gpio     = शेष_analog,
		पूर्ण पूर्ण,
	पूर्ण,
	/*
	 * maybe there's a reason behind it why Terratec sells the Hybrid XS
	 * as Prodigy XS with a dअगरferent PID, let's keep it separated क्रम now
	 * maybe we'll need it later on
	 */
	[EM2880_BOARD_TERRATEC_PRODIGY_XS] = अणु
		.name         = "Terratec Prodigy XS",
		.tuner_type   = TUNER_XC2028,
		.tuner_gpio   = शेष_tuner_gpio,
		.decoder      = EM28XX_TVP5150,
		.input        = अणु अणु
			.type     = EM28XX_VMUX_TELEVISION,
			.vmux     = TVP5150_COMPOSITE0,
			.amux     = EM28XX_AMUX_VIDEO,
			.gpio     = hauppauge_wपूर्णांकv_hvr_900_analog,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = TVP5150_COMPOSITE1,
			.amux     = EM28XX_AMUX_LINE_IN,
			.gpio     = hauppauge_wपूर्णांकv_hvr_900_analog,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = TVP5150_SVIDEO,
			.amux     = EM28XX_AMUX_LINE_IN,
			.gpio     = hauppauge_wपूर्णांकv_hvr_900_analog,
		पूर्ण पूर्ण,
	पूर्ण,
	[EM2820_BOARD_MSI_VOX_USB_2] = अणु
		.name		   = "MSI VOX USB 2.0",
		.tuner_type	   = TUNER_LG_PAL_NEW_TAPC,
		.tda9887_conf	   = TDA9887_PRESENT      |
				     TDA9887_PORT1_ACTIVE |
				     TDA9887_PORT2_ACTIVE,
		.max_range_640_480 = 1,
		.decoder           = EM28XX_SAA711X,
		.input             = अणु अणु
			.type      = EM28XX_VMUX_TELEVISION,
			.vmux      = SAA7115_COMPOSITE4,
			.amux      = EM28XX_AMUX_VIDEO,
		पूर्ण, अणु
			.type      = EM28XX_VMUX_COMPOSITE,
			.vmux      = SAA7115_COMPOSITE0,
			.amux      = EM28XX_AMUX_LINE_IN,
		पूर्ण, अणु
			.type      = EM28XX_VMUX_SVIDEO,
			.vmux      = SAA7115_SVIDEO3,
			.amux      = EM28XX_AMUX_LINE_IN,
		पूर्ण पूर्ण,
	पूर्ण,
	[EM2800_BOARD_TERRATEC_CINERGY_200] = अणु
		.name         = "Terratec Cinergy 200 USB",
		.is_em2800    = 1,
		.has_ir_i2c   = 1,
		.tuner_type   = TUNER_LG_TALN,
		.tda9887_conf = TDA9887_PRESENT,
		.decoder      = EM28XX_SAA711X,
		.input        = अणु अणु
			.type     = EM28XX_VMUX_TELEVISION,
			.vmux     = SAA7115_COMPOSITE2,
			.amux     = EM28XX_AMUX_VIDEO,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = SAA7115_COMPOSITE0,
			.amux     = EM28XX_AMUX_LINE_IN,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = SAA7115_SVIDEO3,
			.amux     = EM28XX_AMUX_LINE_IN,
		पूर्ण पूर्ण,
	पूर्ण,
	[EM2800_BOARD_GRABBEEX_USB2800] = अणु
		.name       = "eMPIA Technology, Inc. GrabBeeX+ Video Encoder",
		.is_em2800  = 1,
		.decoder    = EM28XX_SAA711X,
		.tuner_type = TUNER_ABSENT, /* capture only board */
		.input      = अणु अणु
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = SAA7115_COMPOSITE0,
			.amux     = EM28XX_AMUX_LINE_IN,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = SAA7115_SVIDEO3,
			.amux     = EM28XX_AMUX_LINE_IN,
		पूर्ण पूर्ण,
	पूर्ण,
	[EM2800_BOARD_VC211A] = अणु
		.name         = "Actionmaster/LinXcel/Digitus VC211A",
		.is_em2800    = 1,
		.tuner_type   = TUNER_ABSENT,	/* Capture-only board */
		.decoder      = EM28XX_SAA711X,
		.input        = अणु अणु
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = SAA7115_COMPOSITE0,
			.amux     = EM28XX_AMUX_LINE_IN,
			.gpio     = vc211a_enable,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = SAA7115_SVIDEO3,
			.amux     = EM28XX_AMUX_LINE_IN,
			.gpio     = vc211a_enable,
		पूर्ण पूर्ण,
	पूर्ण,
	[EM2800_BOARD_LEADTEK_WINFAST_USBII] = अणु
		.name         = "Leadtek Winfast USB II",
		.is_em2800    = 1,
		.tuner_type   = TUNER_LG_PAL_NEW_TAPC,
		.tda9887_conf = TDA9887_PRESENT,
		.decoder      = EM28XX_SAA711X,
		.input        = अणु अणु
			.type     = EM28XX_VMUX_TELEVISION,
			.vmux     = SAA7115_COMPOSITE2,
			.amux     = EM28XX_AMUX_VIDEO,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = SAA7115_COMPOSITE0,
			.amux     = EM28XX_AMUX_LINE_IN,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = SAA7115_SVIDEO3,
			.amux     = EM28XX_AMUX_LINE_IN,
		पूर्ण पूर्ण,
	पूर्ण,
	[EM2800_BOARD_KWORLD_USB2800] = अणु
		.name         = "Kworld USB2800",
		.is_em2800    = 1,
		.tuner_type   = TUNER_PHILIPS_FCV1236D,
		.tda9887_conf = TDA9887_PRESENT,
		.decoder      = EM28XX_SAA711X,
		.input        = अणु अणु
			.type     = EM28XX_VMUX_TELEVISION,
			.vmux     = SAA7115_COMPOSITE2,
			.amux     = EM28XX_AMUX_VIDEO,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = SAA7115_COMPOSITE0,
			.amux     = EM28XX_AMUX_LINE_IN,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = SAA7115_SVIDEO3,
			.amux     = EM28XX_AMUX_LINE_IN,
		पूर्ण पूर्ण,
	पूर्ण,
	[EM2820_BOARD_PINNACLE_DVC_90] = अणु
		.name	      = "Pinnacle Dazzle DVC 90/100/101/107 / Kaiser Baas Video to DVD maker / Kworld DVD Maker 2 / Plextor ConvertX PX-AV100U",
		.tuner_type   = TUNER_ABSENT, /* capture only board */
		.decoder      = EM28XX_SAA711X,
		.input        = अणु अणु
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = SAA7115_COMPOSITE0,
			.amux     = EM28XX_AMUX_LINE_IN,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = SAA7115_SVIDEO3,
			.amux     = EM28XX_AMUX_LINE_IN,
		पूर्ण पूर्ण,
	पूर्ण,
	[EM2800_BOARD_VGEAR_POCKETTV] = अणु
		.name         = "V-Gear PocketTV",
		.is_em2800    = 1,
		.tuner_type   = TUNER_LG_PAL_NEW_TAPC,
		.tda9887_conf = TDA9887_PRESENT,
		.decoder      = EM28XX_SAA711X,
		.input        = अणु अणु
			.type     = EM28XX_VMUX_TELEVISION,
			.vmux     = SAA7115_COMPOSITE2,
			.amux     = EM28XX_AMUX_VIDEO,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = SAA7115_COMPOSITE0,
			.amux     = EM28XX_AMUX_LINE_IN,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = SAA7115_SVIDEO3,
			.amux     = EM28XX_AMUX_LINE_IN,
		पूर्ण पूर्ण,
	पूर्ण,
	[EM2820_BOARD_PROLINK_PLAYTV_BOX4_USB2] = अणु
		.name         = "Pixelview PlayTV Box 4 USB 2.0",
		.tda9887_conf = TDA9887_PRESENT,
		.tuner_type   = TUNER_YMEC_TVF_5533MF,
		.decoder      = EM28XX_SAA711X,
		.input        = अणु अणु
			.type     = EM28XX_VMUX_TELEVISION,
			.vmux     = SAA7115_COMPOSITE2,
			.amux     = EM28XX_AMUX_VIDEO,
			.aout     = EM28XX_AOUT_MONO |	/* I2S */
				    EM28XX_AOUT_MASTER,	/* Line out pin */
		पूर्ण, अणु
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = SAA7115_COMPOSITE0,
			.amux     = EM28XX_AMUX_LINE_IN,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = SAA7115_SVIDEO3,
			.amux     = EM28XX_AMUX_LINE_IN,
		पूर्ण पूर्ण,
	पूर्ण,
	[EM2820_BOARD_PROLINK_PLAYTV_USB2] = अणु
		.name         = "SIIG AVTuner-PVR / Pixelview Prolink PlayTV USB 2.0",
		.buttons = std_snapshot_button,
		.tda9887_conf = TDA9887_PRESENT,
		.tuner_type   = TUNER_YMEC_TVF_5533MF,
		.tuner_addr   = 0x60,
		.decoder      = EM28XX_SAA711X,
		.input        = अणु अणु
			.type     = EM28XX_VMUX_TELEVISION,
			.vmux     = SAA7115_COMPOSITE2,
			.amux     = EM28XX_AMUX_VIDEO,
			.aout     = EM28XX_AOUT_MONO |	/* I2S */
				    EM28XX_AOUT_MASTER,	/* Line out pin */
		पूर्ण, अणु
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = SAA7115_COMPOSITE0,
			.amux     = EM28XX_AMUX_LINE_IN,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = SAA7115_SVIDEO3,
			.amux     = EM28XX_AMUX_LINE_IN,
		पूर्ण पूर्ण,
	पूर्ण,
	[EM2860_BOARD_SAA711X_REFERENCE_DESIGN] = अणु
		.name                = "EM2860/SAA711X Reference Design",
		.buttons = std_snapshot_button,
		.tuner_type          = TUNER_ABSENT,
		.decoder             = EM28XX_SAA711X,
		.input               = अणु अणु
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = SAA7115_SVIDEO3,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = SAA7115_COMPOSITE0,
		पूर्ण पूर्ण,
	पूर्ण,

	[EM2874_BOARD_LEADERSHIP_ISDBT] = अणु
		.def_i2c_bus	= 1,
		.i2c_speed      = EM28XX_I2C_CLK_WAIT_ENABLE |
				  EM28XX_I2C_FREQ_100_KHZ,
		.xclk		= EM28XX_XCLK_FREQUENCY_10MHZ,
		.name		= "EM2874 Leadership ISDBT",
		.tuner_type	= TUNER_ABSENT,
		.tuner_gpio     = leadership_reset,
		.dvb_gpio       = leadership_digital,
		.has_dvb	= 1,
	पूर्ण,

	[EM2880_BOARD_MSI_DIGIVOX_AD] = अणु
		.name         = "MSI DigiVox A/D",
		.valid        = EM28XX_BOARD_NOT_VALIDATED,
		.tuner_type   = TUNER_XC2028,
		.tuner_gpio   = शेष_tuner_gpio,
		.decoder      = EM28XX_TVP5150,
		.input        = अणु अणु
			.type     = EM28XX_VMUX_TELEVISION,
			.vmux     = TVP5150_COMPOSITE0,
			.amux     = EM28XX_AMUX_VIDEO,
			.gpio     = em2880_msi_digivox_ad_analog,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = TVP5150_COMPOSITE1,
			.amux     = EM28XX_AMUX_LINE_IN,
			.gpio     = em2880_msi_digivox_ad_analog,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = TVP5150_SVIDEO,
			.amux     = EM28XX_AMUX_LINE_IN,
			.gpio     = em2880_msi_digivox_ad_analog,
		पूर्ण पूर्ण,
	पूर्ण,
	[EM2880_BOARD_MSI_DIGIVOX_AD_II] = अणु
		.name         = "MSI DigiVox A/D II",
		.valid        = EM28XX_BOARD_NOT_VALIDATED,
		.tuner_type   = TUNER_XC2028,
		.tuner_gpio   = शेष_tuner_gpio,
		.decoder      = EM28XX_TVP5150,
		.input        = अणु अणु
			.type     = EM28XX_VMUX_TELEVISION,
			.vmux     = TVP5150_COMPOSITE0,
			.amux     = EM28XX_AMUX_VIDEO,
			.gpio     = em2880_msi_digivox_ad_analog,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = TVP5150_COMPOSITE1,
			.amux     = EM28XX_AMUX_LINE_IN,
			.gpio     = em2880_msi_digivox_ad_analog,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = TVP5150_SVIDEO,
			.amux     = EM28XX_AMUX_LINE_IN,
			.gpio     = em2880_msi_digivox_ad_analog,
		पूर्ण पूर्ण,
	पूर्ण,
	[EM2880_BOARD_KWORLD_DVB_305U] = अणु
		.name	      = "KWorld DVB-T 305U",
		.tuner_type   = TUNER_XC2028,
		.tuner_gpio   = शेष_tuner_gpio,
		.decoder      = EM28XX_TVP5150,
		.input        = अणु अणु
			.type     = EM28XX_VMUX_TELEVISION,
			.vmux     = TVP5150_COMPOSITE0,
			.amux     = EM28XX_AMUX_VIDEO,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = TVP5150_COMPOSITE1,
			.amux     = EM28XX_AMUX_LINE_IN,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = TVP5150_SVIDEO,
			.amux     = EM28XX_AMUX_LINE_IN,
		पूर्ण पूर्ण,
	पूर्ण,
	[EM2880_BOARD_KWORLD_DVB_310U] = अणु
		.name	      = "KWorld DVB-T 310U",
		.tuner_type   = TUNER_XC2028,
		.tuner_gpio   = शेष_tuner_gpio,
		.has_dvb      = 1,
		.dvb_gpio     = शेष_digital,
		.mts_firmware = 1,
		.decoder      = EM28XX_TVP5150,
		.input        = अणु अणु
			.type     = EM28XX_VMUX_TELEVISION,
			.vmux     = TVP5150_COMPOSITE0,
			.amux     = EM28XX_AMUX_VIDEO,
			.gpio     = शेष_analog,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = TVP5150_COMPOSITE1,
			.amux     = EM28XX_AMUX_LINE_IN,
			.gpio     = शेष_analog,
		पूर्ण, अणु	/* S-video has not been tested yet */
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = TVP5150_SVIDEO,
			.amux     = EM28XX_AMUX_LINE_IN,
			.gpio     = शेष_analog,
		पूर्ण पूर्ण,
	पूर्ण,
	[EM2882_BOARD_KWORLD_ATSC_315U] = अणु
		.name		= "KWorld ATSC 315U HDTV TV Box",
		.valid		= EM28XX_BOARD_NOT_VALIDATED,
		.tuner_type	= TUNER_THOMSON_DTT761X,
		.tuner_gpio	= em2882_kworld_315u_tuner_gpio,
		.tda9887_conf	= TDA9887_PRESENT,
		.decoder	= EM28XX_SAA711X,
		.has_dvb	= 1,
		.dvb_gpio	= em2882_kworld_315u_digital,
		.ir_codes	= RC_MAP_KWORLD_315U,
		.xclk		= EM28XX_XCLK_FREQUENCY_12MHZ,
		.i2c_speed	= EM28XX_I2C_CLK_WAIT_ENABLE,
#अगर 0
		/* FIXME: Analog mode - still not पढ़ोy */
		.input        = अणु अणु
			.type = EM28XX_VMUX_TELEVISION,
			.vmux = SAA7115_COMPOSITE2,
			.amux = EM28XX_AMUX_VIDEO,
			.gpio = em2882_kworld_315u_analog,
			.aout = EM28XX_AOUT_PCM_IN | EM28XX_AOUT_PCM_STEREO,
		पूर्ण, अणु
			.type = EM28XX_VMUX_COMPOSITE,
			.vmux = SAA7115_COMPOSITE0,
			.amux = EM28XX_AMUX_LINE_IN,
			.gpio = em2882_kworld_315u_analog1,
			.aout = EM28XX_AOUT_PCM_IN | EM28XX_AOUT_PCM_STEREO,
		पूर्ण, अणु
			.type = EM28XX_VMUX_SVIDEO,
			.vmux = SAA7115_SVIDEO3,
			.amux = EM28XX_AMUX_LINE_IN,
			.gpio = em2882_kworld_315u_analog1,
			.aout = EM28XX_AOUT_PCM_IN | EM28XX_AOUT_PCM_STEREO,
		पूर्ण पूर्ण,
#पूर्ण_अगर
	पूर्ण,
	[EM2880_BOARD_EMPIRE_DUAL_TV] = अणु
		.name = "Empire dual TV",
		.tuner_type = TUNER_XC2028,
		.tuner_gpio = शेष_tuner_gpio,
		.has_dvb = 1,
		.dvb_gpio = शेष_digital,
		.mts_firmware = 1,
		.decoder = EM28XX_TVP5150,
		.input = अणु अणु
			.type = EM28XX_VMUX_TELEVISION,
			.vmux = TVP5150_COMPOSITE0,
			.amux = EM28XX_AMUX_VIDEO,
			.gpio = शेष_analog,
		पूर्ण, अणु
			.type = EM28XX_VMUX_COMPOSITE,
			.vmux = TVP5150_COMPOSITE1,
			.amux = EM28XX_AMUX_LINE_IN,
			.gpio = शेष_analog,
		पूर्ण, अणु
			.type = EM28XX_VMUX_SVIDEO,
			.vmux = TVP5150_SVIDEO,
			.amux = EM28XX_AMUX_LINE_IN,
			.gpio = शेष_analog,
		पूर्ण पूर्ण,
	पूर्ण,
	[EM2881_BOARD_DNT_DA2_HYBRID] = अणु
		.name         = "DNT DA2 Hybrid",
		.valid        = EM28XX_BOARD_NOT_VALIDATED,
		.tuner_type   = TUNER_XC2028,
		.tuner_gpio   = शेष_tuner_gpio,
		.decoder      = EM28XX_TVP5150,
		.input        = अणु अणु
			.type     = EM28XX_VMUX_TELEVISION,
			.vmux     = TVP5150_COMPOSITE0,
			.amux     = EM28XX_AMUX_VIDEO,
			.gpio     = शेष_analog,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = TVP5150_COMPOSITE1,
			.amux     = EM28XX_AMUX_LINE_IN,
			.gpio     = शेष_analog,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = TVP5150_SVIDEO,
			.amux     = EM28XX_AMUX_LINE_IN,
			.gpio     = शेष_analog,
		पूर्ण पूर्ण,
	पूर्ण,
	[EM2881_BOARD_PINNACLE_HYBRID_PRO] = अणु
		.name         = "Pinnacle Hybrid Pro",
		.tuner_type   = TUNER_XC2028,
		.tuner_gpio   = शेष_tuner_gpio,
		.decoder      = EM28XX_TVP5150,
		.has_dvb      = 1,
		.dvb_gpio     = pinnacle_hybrid_pro_digital,
		.input        = अणु अणु
			.type     = EM28XX_VMUX_TELEVISION,
			.vmux     = TVP5150_COMPOSITE0,
			.amux     = EM28XX_AMUX_VIDEO,
			.gpio     = pinnacle_hybrid_pro_analog,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = TVP5150_COMPOSITE1,
			.amux     = EM28XX_AMUX_LINE_IN,
			.gpio     = pinnacle_hybrid_pro_analog,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = TVP5150_SVIDEO,
			.amux     = EM28XX_AMUX_LINE_IN,
			.gpio     = pinnacle_hybrid_pro_analog,
		पूर्ण पूर्ण,
	पूर्ण,
	[EM2882_BOARD_PINNACLE_HYBRID_PRO_330E] = अणु
		.name         = "Pinnacle Hybrid Pro (330e)",
		.tuner_type   = TUNER_XC2028,
		.tuner_gpio   = शेष_tuner_gpio,
		.mts_firmware = 1,
		.has_dvb      = 1,
		.dvb_gpio     = hauppauge_wपूर्णांकv_hvr_900R2_digital,
		.ir_codes     = RC_MAP_PINNACLE_PCTV_HD,
		.decoder      = EM28XX_TVP5150,
		.input        = अणु अणु
			.type     = EM28XX_VMUX_TELEVISION,
			.vmux     = TVP5150_COMPOSITE0,
			.amux     = EM28XX_AMUX_VIDEO,
			.gpio     = hauppauge_wपूर्णांकv_hvr_900_analog,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = TVP5150_COMPOSITE1,
			.amux     = EM28XX_AMUX_LINE_IN,
			.gpio     = hauppauge_wपूर्णांकv_hvr_900_analog,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = TVP5150_SVIDEO,
			.amux     = EM28XX_AMUX_LINE_IN,
			.gpio     = hauppauge_wपूर्णांकv_hvr_900_analog,
		पूर्ण पूर्ण,
	पूर्ण,
	[EM2882_BOARD_KWORLD_VS_DVBT] = अणु
		.name         = "Kworld VS-DVB-T 323UR",
		.tuner_type   = TUNER_XC2028,
		.tuner_gpio   = शेष_tuner_gpio,
		.decoder      = EM28XX_TVP5150,
		.mts_firmware = 1,
		.has_dvb      = 1,
		.dvb_gpio     = kworld_330u_digital,
		.xclk         = EM28XX_XCLK_FREQUENCY_12MHZ, /* NEC IR */
		.ir_codes     = RC_MAP_KWORLD_315U,
		.input        = अणु अणु
			.type     = EM28XX_VMUX_TELEVISION,
			.vmux     = TVP5150_COMPOSITE0,
			.amux     = EM28XX_AMUX_VIDEO,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = TVP5150_COMPOSITE1,
			.amux     = EM28XX_AMUX_LINE_IN,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = TVP5150_SVIDEO,
			.amux     = EM28XX_AMUX_LINE_IN,
		पूर्ण पूर्ण,
	पूर्ण,
	[EM2882_BOARD_TERRATEC_HYBRID_XS] = अणु
		.name         = "Terratec Cinergy Hybrid T USB XS (em2882)",
		.tuner_type   = TUNER_XC2028,
		.tuner_gpio   = शेष_tuner_gpio,
		.mts_firmware = 1,
		.decoder      = EM28XX_TVP5150,
		.has_dvb      = 1,
		.dvb_gpio     = hauppauge_wपूर्णांकv_hvr_900_digital,
		.ir_codes     = RC_MAP_TERRATEC_CINERGY_XS,
		.xclk         = EM28XX_XCLK_FREQUENCY_12MHZ,
		.input        = अणु अणु
			.type     = EM28XX_VMUX_TELEVISION,
			.vmux     = TVP5150_COMPOSITE0,
			.amux     = EM28XX_AMUX_VIDEO,
			.gpio     = hauppauge_wपूर्णांकv_hvr_900_analog,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = TVP5150_COMPOSITE1,
			.amux     = EM28XX_AMUX_LINE_IN,
			.gpio     = hauppauge_wपूर्णांकv_hvr_900_analog,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = TVP5150_SVIDEO,
			.amux     = EM28XX_AMUX_LINE_IN,
			.gpio     = hauppauge_wपूर्णांकv_hvr_900_analog,
		पूर्ण पूर्ण,
	पूर्ण,
	[EM2882_BOARD_DIKOM_DK300] = अणु
		.name         = "Dikom DK300",
		.tuner_type   = TUNER_XC2028,
		.tuner_gpio   = शेष_tuner_gpio,
		.decoder      = EM28XX_TVP5150,
		.mts_firmware = 1,
		.has_dvb      = 1,
		.dvb_gpio     = dikom_dk300_digital,
		.input        = अणु अणु
			.type     = EM28XX_VMUX_TELEVISION,
			.vmux     = TVP5150_COMPOSITE0,
			.amux     = EM28XX_AMUX_VIDEO,
			.gpio     = शेष_analog,
		पूर्ण पूर्ण,
	पूर्ण,
	[EM2883_BOARD_KWORLD_HYBRID_330U] = अणु
		.name         = "Kworld PlusTV HD Hybrid 330",
		.tuner_type   = TUNER_XC2028,
		.tuner_gpio   = शेष_tuner_gpio,
		.decoder      = EM28XX_TVP5150,
		.mts_firmware = 1,
		.has_dvb      = 1,
		.dvb_gpio     = kworld_330u_digital,
		.xclk             = EM28XX_XCLK_FREQUENCY_12MHZ,
		.i2c_speed        = EM28XX_I2C_CLK_WAIT_ENABLE |
				    EM28XX_I2C_EEPROM_ON_BOARD |
				    EM28XX_I2C_EEPROM_KEY_VALID,
		.input        = अणु अणु
			.type     = EM28XX_VMUX_TELEVISION,
			.vmux     = TVP5150_COMPOSITE0,
			.amux     = EM28XX_AMUX_VIDEO,
			.gpio     = kworld_330u_analog,
			.aout     = EM28XX_AOUT_PCM_IN | EM28XX_AOUT_PCM_STEREO,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = TVP5150_COMPOSITE1,
			.amux     = EM28XX_AMUX_LINE_IN,
			.gpio     = kworld_330u_analog,
			.aout     = EM28XX_AOUT_PCM_IN | EM28XX_AOUT_PCM_STEREO,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = TVP5150_SVIDEO,
			.amux     = EM28XX_AMUX_LINE_IN,
			.gpio     = kworld_330u_analog,
		पूर्ण पूर्ण,
	पूर्ण,
	[EM2820_BOARD_COMPRO_VIDEOMATE_FORYOU] = अणु
		.name         = "Compro VideoMate ForYou/Stereo",
		.tuner_type   = TUNER_LG_PAL_NEW_TAPC,
		.tvaudio_addr = 0xb0,
		.tda9887_conf = TDA9887_PRESENT,
		.decoder      = EM28XX_TVP5150,
		.adecoder     = EM28XX_TVAUDIO,
		.mute_gpio    = compro_mute_gpio,
		.input        = अणु अणु
			.type     = EM28XX_VMUX_TELEVISION,
			.vmux     = TVP5150_COMPOSITE0,
			.amux     = EM28XX_AMUX_VIDEO,
			.gpio     = compro_unmute_tv_gpio,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = TVP5150_SVIDEO,
			.amux     = EM28XX_AMUX_LINE_IN,
			.gpio     = compro_unmute_svid_gpio,
		पूर्ण पूर्ण,
	पूर्ण,
	[EM2860_BOARD_KAIOMY_TVNPC_U2] = अणु
		.name	      = "Kaiomy TVnPC U2",
		.vchannels    = 3,
		.tuner_type   = TUNER_XC2028,
		.tuner_addr   = 0x61,
		.mts_firmware = 1,
		.decoder      = EM28XX_TVP5150,
		.tuner_gpio   = शेष_tuner_gpio,
		.ir_codes     = RC_MAP_KAIOMY,
		.input          = अणु अणु
			.type     = EM28XX_VMUX_TELEVISION,
			.vmux     = TVP5150_COMPOSITE0,
			.amux     = EM28XX_AMUX_VIDEO,

		पूर्ण, अणु
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = TVP5150_COMPOSITE1,
			.amux     = EM28XX_AMUX_LINE_IN,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = TVP5150_SVIDEO,
			.amux     = EM28XX_AMUX_LINE_IN,
		पूर्ण पूर्ण,
		.radio		= अणु
			.type     = EM28XX_RADIO,
			.amux     = EM28XX_AMUX_LINE_IN,
		पूर्ण
	पूर्ण,
	[EM2860_BOARD_EASYCAP] = अणु
		.name         = "Easy Cap Capture DC-60",
		.vchannels    = 2,
		.tuner_type   = TUNER_ABSENT,
		.decoder      = EM28XX_SAA711X,
		.input           = अणु अणु
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = SAA7115_COMPOSITE0,
			.amux     = EM28XX_AMUX_LINE_IN,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = SAA7115_SVIDEO3,
			.amux     = EM28XX_AMUX_LINE_IN,
		पूर्ण पूर्ण,
	पूर्ण,
	[EM2820_BOARD_IODATA_GVMVP_SZ] = अणु
		.name       = "IO-DATA GV-MVP/SZ",
		.tuner_type   = TUNER_PHILIPS_FM1236_MK3,
		.tuner_gpio   = शेष_tuner_gpio,
		.tda9887_conf = TDA9887_PRESENT,
		.decoder      = EM28XX_TVP5150,
		.input        = अणु अणु
			.type     = EM28XX_VMUX_TELEVISION,
			.vmux     = TVP5150_COMPOSITE0,
			.amux     = EM28XX_AMUX_VIDEO,
		पूर्ण, अणु /* Composite has not been tested yet */
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = TVP5150_COMPOSITE1,
			.amux     = EM28XX_AMUX_VIDEO,
		पूर्ण, अणु /* S-video has not been tested yet */
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = TVP5150_SVIDEO,
			.amux     = EM28XX_AMUX_VIDEO,
		पूर्ण पूर्ण,
	पूर्ण,
	[EM2860_BOARD_TERRATEC_GRABBY] = अणु
		.name            = "Terratec Grabby",
		.vchannels       = 2,
		.tuner_type      = TUNER_ABSENT,
		.decoder         = EM28XX_SAA711X,
		.xclk            = EM28XX_XCLK_FREQUENCY_12MHZ,
		.input           = अणु अणु
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = SAA7115_COMPOSITE0,
			.amux     = EM28XX_AMUX_LINE_IN,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = SAA7115_SVIDEO3,
			.amux     = EM28XX_AMUX_LINE_IN,
		पूर्ण पूर्ण,
		.buttons         = std_snapshot_button,
		.leds            = terratec_grabby_leds,
	पूर्ण,
	[EM2860_BOARD_TERRATEC_AV350] = अणु
		.name            = "Terratec AV350",
		.vchannels       = 2,
		.tuner_type      = TUNER_ABSENT,
		.decoder         = EM28XX_TVP5150,
		.xclk            = EM28XX_XCLK_FREQUENCY_12MHZ,
		.mute_gpio       = terratec_av350_mute_gpio,
		.input           = अणु अणु
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = TVP5150_COMPOSITE1,
			.amux     = EM28XX_AMUX_LINE_IN,
			.gpio     = terratec_av350_unmute_gpio,

		पूर्ण, अणु
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = TVP5150_SVIDEO,
			.amux     = EM28XX_AMUX_LINE_IN,
			.gpio     = terratec_av350_unmute_gpio,
		पूर्ण पूर्ण,
	पूर्ण,

	[EM2860_BOARD_ELGATO_VIDEO_CAPTURE] = अणु
		.name         = "Elgato Video Capture",
		.decoder      = EM28XX_SAA711X,
		.tuner_type   = TUNER_ABSENT,   /* Capture only device */
		.input        = अणु अणु
			.type  = EM28XX_VMUX_COMPOSITE,
			.vmux  = SAA7115_COMPOSITE0,
			.amux  = EM28XX_AMUX_LINE_IN,
		पूर्ण, अणु
			.type  = EM28XX_VMUX_SVIDEO,
			.vmux  = SAA7115_SVIDEO3,
			.amux  = EM28XX_AMUX_LINE_IN,
		पूर्ण पूर्ण,
	पूर्ण,

	[EM2882_BOARD_EVGA_INDTUBE] = अणु
		.name         = "Evga inDtube",
		.tuner_type   = TUNER_XC2028,
		.tuner_gpio   = शेष_tuner_gpio,
		.decoder      = EM28XX_TVP5150,
		.xclk         = EM28XX_XCLK_FREQUENCY_12MHZ, /* NEC IR */
		.mts_firmware = 1,
		.has_dvb      = 1,
		.dvb_gpio     = evga_indtube_digital,
		.ir_codes     = RC_MAP_EVGA_INDTUBE,
		.input        = अणु अणु
			.type     = EM28XX_VMUX_TELEVISION,
			.vmux     = TVP5150_COMPOSITE0,
			.amux     = EM28XX_AMUX_VIDEO,
			.gpio     = evga_indtube_analog,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = TVP5150_COMPOSITE1,
			.amux     = EM28XX_AMUX_LINE_IN,
			.gpio     = evga_indtube_analog,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = TVP5150_SVIDEO,
			.amux     = EM28XX_AMUX_LINE_IN,
			.gpio     = evga_indtube_analog,
		पूर्ण पूर्ण,
	पूर्ण,
	/*
	 * eb1a:2868 Empia EM2870 + Philips CU1216L NIM
	 * (Philips TDA10023 + Infineon TUA6034)
	 */
	[EM2870_BOARD_REDDO_DVB_C_USB_BOX] = अणु
		.name          = "Reddo DVB-C USB TV Box",
		.tuner_type    = TUNER_ABSENT,
		.tuner_gpio    = redकरो_dvb_c_usb_box,
		.has_dvb       = 1,
	पूर्ण,
	/*
	 * 1b80:a340 - Empia EM2870, NXP TDA18271HD and LG DT3304, sold
	 * initially as the KWorld PlusTV 340U, then as the UB435-Q.
	 * Early variants have a TDA18271HD/C1, later ones a TDA18271HD/C2
	 */
	[EM2870_BOARD_KWORLD_A340] = अणु
		.name       = "KWorld PlusTV 340U or UB435-Q (ATSC)",
		.tuner_type = TUNER_ABSENT,	/* Digital-only TDA18271HD */
		.has_dvb    = 1,
		.dvb_gpio   = kworld_a340_digital,
		.tuner_gpio = शेष_tuner_gpio,
	पूर्ण,
	/*
	 * 2013:024f PCTV nanoStick T2 290e.
	 * Empia EM28174, Sony CXD2820R and NXP TDA18271HD/C2
	 */
	[EM28174_BOARD_PCTV_290E] = अणु
		.name          = "PCTV nanoStick T2 290e",
		.def_i2c_bus   = 1,
		.i2c_speed     = EM28XX_I2C_CLK_WAIT_ENABLE |
				 EM28XX_I2C_FREQ_100_KHZ,
		.tuner_type    = TUNER_ABSENT,
		.tuner_gpio    = pctv_290e,
		.has_dvb       = 1,
		.ir_codes      = RC_MAP_PINNACLE_PCTV_HD,
	पूर्ण,
	/*
	 * 2013:024f PCTV DVB-S2 Stick 460e
	 * Empia EM28174, NXP TDA10071, Conexant CX24118A and Allegro A8293
	 */
	[EM28174_BOARD_PCTV_460E] = अणु
		.def_i2c_bus   = 1,
		.i2c_speed     = EM28XX_I2C_CLK_WAIT_ENABLE |
				 EM28XX_I2C_FREQ_400_KHZ,
		.name          = "PCTV DVB-S2 Stick (460e)",
		.tuner_type    = TUNER_ABSENT,
		.tuner_gpio    = pctv_460e,
		.has_dvb       = 1,
		.ir_codes      = RC_MAP_PINNACLE_PCTV_HD,
	पूर्ण,
	/*
	 * eb1a:5006 Honestech VIDBOX NW03
	 * Empia EM2860, Philips SAA7113, Empia EMP202, No Tuner
	 */
	[EM2860_BOARD_HT_VIDBOX_NW03] = अणु
		.name                = "Honestech Vidbox NW03",
		.tuner_type          = TUNER_ABSENT,
		.decoder             = EM28XX_SAA711X,
		.input               = अणु अणु
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = SAA7115_COMPOSITE0,
			.amux     = EM28XX_AMUX_LINE_IN,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = SAA7115_SVIDEO3,  /* S-VIDEO needs check */
			.amux     = EM28XX_AMUX_LINE_IN,
		पूर्ण पूर्ण,
	पूर्ण,
	/*
	 * 1b80:e425 MaxMedia UB425-TC
	 * Empia EM2874B + Micronas DRX 3913KA2 + NXP TDA18271HDC2
	 */
	[EM2874_BOARD_MAXMEDIA_UB425_TC] = अणु
		.name          = "MaxMedia UB425-TC",
		.tuner_type    = TUNER_ABSENT,
		.tuner_gpio    = maxmedia_ub425_tc,
		.has_dvb       = 1,
		.ir_codes      = RC_MAP_REDDO,
		.def_i2c_bus   = 1,
		.i2c_speed     = EM28XX_I2C_CLK_WAIT_ENABLE |
				EM28XX_I2C_FREQ_400_KHZ,
	पूर्ण,
	/*
	 * 2304:0242 PCTV QuatroStick (510e)
	 * Empia EM2884 + Micronas DRX 3926K + NXP TDA18271HDC2
	 */
	[EM2884_BOARD_PCTV_510E] = अणु
		.name          = "PCTV QuatroStick (510e)",
		.tuner_type    = TUNER_ABSENT,
		.tuner_gpio    = pctv_510e,
		.has_dvb       = 1,
		.ir_codes      = RC_MAP_PINNACLE_PCTV_HD,
		.def_i2c_bus   = 1,
		.i2c_speed     = EM28XX_I2C_CLK_WAIT_ENABLE |
				EM28XX_I2C_FREQ_400_KHZ,
	पूर्ण,
	/*
	 * 2013:0251 PCTV QuatroStick nano (520e)
	 * Empia EM2884 + Micronas DRX 3926K + NXP TDA18271HDC2
	 */
	[EM2884_BOARD_PCTV_520E] = अणु
		.name          = "PCTV QuatroStick nano (520e)",
		.tuner_type    = TUNER_ABSENT,
		.tuner_gpio    = pctv_520e,
		.has_dvb       = 1,
		.ir_codes      = RC_MAP_PINNACLE_PCTV_HD,
		.def_i2c_bus   = 1,
		.i2c_speed     = EM28XX_I2C_CLK_WAIT_ENABLE |
				EM28XX_I2C_FREQ_400_KHZ,
	पूर्ण,
	[EM2884_BOARD_TERRATEC_HTC_USB_XS] = अणु
		.name         = "Terratec Cinergy HTC USB XS",
		.has_dvb      = 1,
		.ir_codes     = RC_MAP_NEC_TERRATEC_CINERGY_XS,
		.tuner_type   = TUNER_ABSENT,
		.def_i2c_bus  = 1,
		.i2c_speed    = EM28XX_I2C_CLK_WAIT_ENABLE |
				EM28XX_I2C_FREQ_400_KHZ,
	पूर्ण,
	/*
	 * 1b80:e1cc Delock 61959
	 * Empia EM2874B + Micronas DRX 3913KA2 + NXP TDA18271HDC2
	 * mostly the same as MaxMedia UB-425-TC but dअगरferent remote
	 */
	[EM2874_BOARD_DELOCK_61959] = अणु
		.name          = "Delock 61959",
		.tuner_type    = TUNER_ABSENT,
		.tuner_gpio    = maxmedia_ub425_tc,
		.has_dvb       = 1,
		.ir_codes      = RC_MAP_DELOCK_61959,
		.def_i2c_bus   = 1,
		.i2c_speed     = EM28XX_I2C_CLK_WAIT_ENABLE |
				EM28XX_I2C_FREQ_400_KHZ,
	पूर्ण,
	/*
	 * 1b80:e346 KWorld USB ATSC TV Stick UB435-Q V2
	 * Empia EM2874B + LG DT3305 + NXP TDA18271HDC2
	 */
	[EM2874_BOARD_KWORLD_UB435Q_V2] = अणु
		.name		= "KWorld USB ATSC TV Stick UB435-Q V2",
		.tuner_type	= TUNER_ABSENT,
		.has_dvb	= 1,
		.dvb_gpio	= kworld_a340_digital,
		.tuner_gpio	= शेष_tuner_gpio,
		.def_i2c_bus	= 1,
	पूर्ण,
	/*
	 * 1b80:e34c KWorld USB ATSC TV Stick UB435-Q V3
	 * Empia EM2874B + LG DT3305 + NXP TDA18271HDC2
	 */
	[EM2874_BOARD_KWORLD_UB435Q_V3] = अणु
		.name		= "KWorld USB ATSC TV Stick UB435-Q V3",
		.tuner_type	= TUNER_ABSENT,
		.has_dvb	= 1,
		.tuner_gpio	= kworld_ub435q_v3_digital,
		.def_i2c_bus	= 1,
		.i2c_speed      = EM28XX_I2C_CLK_WAIT_ENABLE |
				  EM28XX_I2C_FREQ_100_KHZ,
		.leds = kworld_ub435q_v3_leds,
	पूर्ण,
	[EM2874_BOARD_PCTV_HD_MINI_80E] = अणु
		.name         = "Pinnacle PCTV HD Mini",
		.tuner_type   = TUNER_ABSENT,
		.has_dvb      = 1,
		.dvb_gpio     = em2874_pctv_80e_digital,
		.decoder      = EM28XX_NODECODER,
		.ir_codes     = RC_MAP_PINNACLE_PCTV_HD,
		.leds         = pctv_80e_leds,
	पूर्ण,
	/*
	 * 1ae7:9003/9004 SpeedLink Vicious And Devine Laplace webcam
	 * Empia EM2765 + OmniVision OV2640
	 */
	[EM2765_BOARD_SPEEDLINK_VAD_LAPLACE] = अणु
		.name         = "SpeedLink Vicious And Devine Laplace webcam",
		.xclk         = EM28XX_XCLK_FREQUENCY_24MHZ,
		.i2c_speed    = EM28XX_I2C_CLK_WAIT_ENABLE |
				EM28XX_I2C_FREQ_100_KHZ,
		.def_i2c_bus  = 1,
		.tuner_type   = TUNER_ABSENT,
		.is_webcam    = 1,
		.input        = अणु अणु
			.type     = EM28XX_VMUX_COMPOSITE,
			.amux     = EM28XX_AMUX_VIDEO,
			.gpio     = speedlink_vad_laplace_reg_seq,
		पूर्ण पूर्ण,
		.buttons = speedlink_vad_laplace_buttons,
		.leds = speedlink_vad_laplace_leds,
	पूर्ण,
	/*
	 * 2013:0258 PCTV DVB-S2 Stick (461e)
	 * Empia EM28178, Montage M88DS3103, Montage M88TS2022, Allegro A8293
	 */
	[EM28178_BOARD_PCTV_461E] = अणु
		.def_i2c_bus   = 1,
		.i2c_speed     = EM28XX_I2C_CLK_WAIT_ENABLE |
				 EM28XX_I2C_FREQ_400_KHZ,
		.name          = "PCTV DVB-S2 Stick (461e)",
		.tuner_type    = TUNER_ABSENT,
		.tuner_gpio    = pctv_461e,
		.has_dvb       = 1,
		.ir_codes      = RC_MAP_PINNACLE_PCTV_HD,
	पूर्ण,
	/*
	 * 2013:0259 PCTV DVB-S2 Stick (461e_v2)
	 * Empia EM28178, Montage M88DS3103b, Montage M88TS2022, Allegro A8293
	 */
	[EM28178_BOARD_PCTV_461E_V2] = अणु
		.def_i2c_bus   = 1,
		.i2c_speed     = EM28XX_I2C_CLK_WAIT_ENABLE |
				 EM28XX_I2C_FREQ_400_KHZ,
		.name          = "PCTV DVB-S2 Stick (461e v2)",
		.tuner_type    = TUNER_ABSENT,
		.tuner_gpio    = pctv_461e,
		.has_dvb       = 1,
		.ir_codes      = RC_MAP_PINNACLE_PCTV_HD,
	पूर्ण,
	/*
	 * 2013:025f PCTV tripleStick (292e).
	 * Empia EM28178, Silicon Lअसल Si2168, Silicon Lअसल Si2157
	 */
	[EM28178_BOARD_PCTV_292E] = अणु
		.name          = "PCTV tripleStick (292e)",
		.def_i2c_bus   = 1,
		.i2c_speed     = EM28XX_I2C_CLK_WAIT_ENABLE |
				 EM28XX_I2C_FREQ_400_KHZ,
		.tuner_type    = TUNER_ABSENT,
		.tuner_gpio    = pctv_292e,
		.has_dvb       = 1,
		.ir_codes      = RC_MAP_PINNACLE_PCTV_HD,
	पूर्ण,
	[EM2861_BOARD_LEADTEK_VC100] = अणु
		.name          = "Leadtek VC100",
		.tuner_type    = TUNER_ABSENT,	/* Capture only device */
		.decoder       = EM28XX_TVP5150,
		.input         = अणु अणु
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = TVP5150_COMPOSITE1,
			.amux     = EM28XX_AMUX_LINE_IN,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = TVP5150_SVIDEO,
			.amux     = EM28XX_AMUX_LINE_IN,
		पूर्ण पूर्ण,
	पूर्ण,
	/*
	 * eb1a:8179 Terratec Cinergy T2 Stick HD.
	 * Empia EM28178, Silicon Lअसल Si2168, Silicon Lअसल Si2146
	 */
	[EM28178_BOARD_TERRATEC_T2_STICK_HD] = अणु
		.name          = "Terratec Cinergy T2 Stick HD",
		.def_i2c_bus   = 1,
		.i2c_speed     = EM28XX_I2C_CLK_WAIT_ENABLE |
				 EM28XX_I2C_FREQ_400_KHZ,
		.tuner_type    = TUNER_ABSENT,
		.tuner_gpio    = terratec_t2_stick_hd,
		.has_dvb       = 1,
		.ir_codes      = RC_MAP_TERRATEC_SLIM_2,
	पूर्ण,

	/*
	 * 3275:0085 PLEX PX-BCUD.
	 * Empia EM28178, TOSHIBA TC90532XBG, Sharp QM1D1C0042
	 */
	[EM28178_BOARD_PLEX_PX_BCUD] = अणु
		.name          = "PLEX PX-BCUD",
		.xclk          = EM28XX_XCLK_FREQUENCY_4_3MHZ,
		.def_i2c_bus   = 1,
		.i2c_speed     = EM28XX_I2C_CLK_WAIT_ENABLE,
		.tuner_type    = TUNER_ABSENT,
		.tuner_gpio    = plex_px_bcud,
		.has_dvb       = 1,
	पूर्ण,
	/*
	 * 2040:0265 Hauppauge WinTV-dualHD (DVB version) Isoc.
	 * 2040:8265 Hauppauge WinTV-dualHD (DVB version) Bulk.
	 * Empia EM28274, 2x Silicon Lअसल Si2168, 2x Silicon Lअसल Si2157
	 */
	[EM28174_BOARD_HAUPPAUGE_WINTV_DUALHD_DVB] = अणु
		.name          = "Hauppauge WinTV-dualHD DVB",
		.def_i2c_bus   = 1,
		.i2c_speed     = EM28XX_I2C_CLK_WAIT_ENABLE |
				 EM28XX_I2C_FREQ_400_KHZ,
		.tuner_type    = TUNER_ABSENT,
		.tuner_gpio    = hauppauge_dualhd_dvb,
		.has_dvb       = 1,
		.has_dual_ts   = 1,
		.ir_codes      = RC_MAP_HAUPPAUGE,
		.leds          = hauppauge_dualhd_leds,
	पूर्ण,
	/*
	 * 2040:026d Hauppauge WinTV-dualHD (model 01595 - ATSC/QAM) Isoc.
	 * 2040:826d Hauppauge WinTV-dualHD (model 01595 - ATSC/QAM) Bulk.
	 * Empia EM28274, 2x LG LGDT3306A, 2x Silicon Lअसल Si2157
	 */
	[EM28174_BOARD_HAUPPAUGE_WINTV_DUALHD_01595] = अणु
		.name          = "Hauppauge WinTV-dualHD 01595 ATSC/QAM",
		.def_i2c_bus   = 1,
		.i2c_speed     = EM28XX_I2C_CLK_WAIT_ENABLE |
				 EM28XX_I2C_FREQ_400_KHZ,
		.tuner_type    = TUNER_ABSENT,
		.tuner_gpio    = hauppauge_dualhd_dvb,
		.has_dvb       = 1,
		.has_dual_ts   = 1,
		.ir_codes      = RC_MAP_HAUPPAUGE,
		.leds          = hauppauge_dualhd_leds,
	पूर्ण,
	/*
	 * 1b80:e349 Magix USB Videowandler-2
	 * (same chips as Honestech VIDBOX NW03)
	 * Empia EM2860, Philips SAA7113, Empia EMP202, No Tuner
	 */
	[EM2861_BOARD_MAGIX_VIDEOWANDLER2] = अणु
		.name                = "Magix USB Videowandler-2",
		.tuner_type          = TUNER_ABSENT,
		.decoder             = EM28XX_SAA711X,
		.input               = अणु अणु
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = SAA7115_COMPOSITE0,
			.amux     = EM28XX_AMUX_LINE_IN,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_SVIDEO,
			.amux     = EM28XX_AMUX_LINE_IN,
		पूर्ण पूर्ण,
	पूर्ण,
	/*
	 * 1f4d:1abe MyGica iGrabber
	 * (same as several other EM2860 devices)
	 * Empia EM2860, Philips SAA7113, Empia EMP202, No Tuner
	 */
	[EM2860_BOARD_MYGICA_IGRABBER] = अणु
		.name         = "MyGica iGrabber",
		.vchannels    = 2,
		.tuner_type   = TUNER_ABSENT,
		.decoder      = EM28XX_SAA711X,
		.input           = अणु अणु
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = SAA7115_COMPOSITE0,
			.amux     = EM28XX_AMUX_LINE_IN,
		पूर्ण, अणु
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = SAA7115_SVIDEO3,
			.amux     = EM28XX_AMUX_LINE_IN,
		पूर्ण पूर्ण,
	पूर्ण,
	/* 2040:826d Hauppauge USB QuadHD
	 * Empia 28274, Max Linear 692 ATSC combo demod/tuner
	 */
	[EM2874_BOARD_HAUPPAUGE_USB_QUADHD] = अणु
		.name          = "Hauppauge USB QuadHD ATSC",
		.def_i2c_bus   = 1,
		.has_dual_ts   = 1,
		.has_dvb       = 1,
		.i2c_speed     = EM28XX_I2C_CLK_WAIT_ENABLE | EM28XX_I2C_FREQ_100_KHZ,
		.tuner_type    = TUNER_ABSENT,
		.tuner_gpio    = hauppauge_usb_quadhd_atsc_reg_seq,
		.leds          = hauppauge_usb_quadhd_leds,
	पूर्ण,
पूर्ण;
EXPORT_SYMBOL_GPL(em28xx_boards);

अटल स्थिर अचिन्हित पूर्णांक em28xx_bcount = ARRAY_SIZE(em28xx_boards);

/* table of devices that work with this driver */
काष्ठा usb_device_id em28xx_id_table[] = अणु
	अणु USB_DEVICE(0xeb1a, 0x2750),
			.driver_info = EM2750_BOARD_UNKNOWN पूर्ण,
	अणु USB_DEVICE(0xeb1a, 0x2751),
			.driver_info = EM2750_BOARD_UNKNOWN पूर्ण,
	अणु USB_DEVICE(0xeb1a, 0x2800),
			.driver_info = EM2800_BOARD_UNKNOWN पूर्ण,
	अणु USB_DEVICE(0xeb1a, 0x2710),
			.driver_info = EM2820_BOARD_UNKNOWN पूर्ण,
	अणु USB_DEVICE(0xeb1a, 0x2820),
			.driver_info = EM2820_BOARD_UNKNOWN पूर्ण,
	अणु USB_DEVICE(0xeb1a, 0x2821),
			.driver_info = EM2820_BOARD_UNKNOWN पूर्ण,
	अणु USB_DEVICE(0xeb1a, 0x2860),
			.driver_info = EM2820_BOARD_UNKNOWN पूर्ण,
	अणु USB_DEVICE(0xeb1a, 0x2861),
			.driver_info = EM2820_BOARD_UNKNOWN पूर्ण,
	अणु USB_DEVICE(0xeb1a, 0x2862),
			.driver_info = EM2820_BOARD_UNKNOWN पूर्ण,
	अणु USB_DEVICE(0xeb1a, 0x2863),
			.driver_info = EM2820_BOARD_UNKNOWN पूर्ण,
	अणु USB_DEVICE(0xeb1a, 0x2870),
			.driver_info = EM2820_BOARD_UNKNOWN पूर्ण,
	अणु USB_DEVICE(0xeb1a, 0x2881),
			.driver_info = EM2820_BOARD_UNKNOWN पूर्ण,
	अणु USB_DEVICE(0xeb1a, 0x2883), /* used by :Zolid Hybrid Tv Stick */
			.driver_info = EM2820_BOARD_UNKNOWN पूर्ण,
	अणु USB_DEVICE(0xeb1a, 0x2868),
			.driver_info = EM2820_BOARD_UNKNOWN पूर्ण,
	अणु USB_DEVICE(0xeb1a, 0x2875),
			.driver_info = EM2820_BOARD_UNKNOWN पूर्ण,
	अणु USB_DEVICE(0xeb1a, 0x2885), /* MSI Digivox Trio */
			.driver_info = EM2884_BOARD_TERRATEC_H5 पूर्ण,
	अणु USB_DEVICE(0xeb1a, 0xe300),
			.driver_info = EM2861_BOARD_KWORLD_PVRTV_300U पूर्ण,
	अणु USB_DEVICE(0xeb1a, 0xe303),
			.driver_info = EM2860_BOARD_KAIOMY_TVNPC_U2 पूर्ण,
	अणु USB_DEVICE(0xeb1a, 0xe305),
			.driver_info = EM2880_BOARD_KWORLD_DVB_305U पूर्ण,
	अणु USB_DEVICE(0xeb1a, 0xe310),
			.driver_info = EM2880_BOARD_MSI_DIGIVOX_AD पूर्ण,
	अणु USB_DEVICE(0xeb1a, 0xa313),
		.driver_info = EM2882_BOARD_KWORLD_ATSC_315U पूर्ण,
	अणु USB_DEVICE(0xeb1a, 0xa316),
			.driver_info = EM2883_BOARD_KWORLD_HYBRID_330U पूर्ण,
	अणु USB_DEVICE(0xeb1a, 0xe320),
			.driver_info = EM2880_BOARD_MSI_DIGIVOX_AD_II पूर्ण,
	अणु USB_DEVICE(0xeb1a, 0xe323),
			.driver_info = EM2882_BOARD_KWORLD_VS_DVBT पूर्ण,
	अणु USB_DEVICE(0xeb1a, 0xe350),
			.driver_info = EM2870_BOARD_KWORLD_350U पूर्ण,
	अणु USB_DEVICE(0xeb1a, 0xe355),
			.driver_info = EM2870_BOARD_KWORLD_355U पूर्ण,
	अणु USB_DEVICE(0xeb1a, 0x2801),
			.driver_info = EM2800_BOARD_GRABBEEX_USB2800 पूर्ण,
	अणु USB_DEVICE(0xeb1a, 0xe357),
			.driver_info = EM2870_BOARD_KWORLD_355U पूर्ण,
	अणु USB_DEVICE(0xeb1a, 0xe359),
			.driver_info = EM2870_BOARD_KWORLD_355U पूर्ण,
	अणु USB_DEVICE(0x1b80, 0xe302), /* Kaiser Baas Video to DVD maker */
			.driver_info = EM2820_BOARD_PINNACLE_DVC_90 पूर्ण,
	अणु USB_DEVICE(0x1b80, 0xe304), /* Kworld DVD Maker 2 */
			.driver_info = EM2820_BOARD_PINNACLE_DVC_90 पूर्ण,
	अणु USB_DEVICE(0x0ccd, 0x0036),
			.driver_info = EM2820_BOARD_TERRATEC_CINERGY_250 पूर्ण,
	अणु USB_DEVICE(0x0ccd, 0x004c),
			.driver_info = EM2880_BOARD_TERRATEC_HYBRID_XS_FR पूर्ण,
	अणु USB_DEVICE(0x0ccd, 0x004f),
			.driver_info = EM2860_BOARD_TERRATEC_HYBRID_XS पूर्ण,
	अणु USB_DEVICE(0x0ccd, 0x005e),
			.driver_info = EM2882_BOARD_TERRATEC_HYBRID_XS पूर्ण,
	अणु USB_DEVICE(0x0ccd, 0x0042),
			.driver_info = EM2882_BOARD_TERRATEC_HYBRID_XS पूर्ण,
	अणु USB_DEVICE(0x0ccd, 0x0043),
			.driver_info = EM2870_BOARD_TERRATEC_XS_MT2060 पूर्ण,
	अणु USB_DEVICE(0x0ccd, 0x008e),	/* Cinergy HTC USB XS Rev. 1 */
			.driver_info = EM2884_BOARD_TERRATEC_HTC_USB_XS पूर्ण,
	अणु USB_DEVICE(0x0ccd, 0x00ac),	/* Cinergy HTC USB XS Rev. 2 */
			.driver_info = EM2884_BOARD_TERRATEC_HTC_USB_XS पूर्ण,
	अणु USB_DEVICE(0x0ccd, 0x10a2),	/* H5 Rev. 1 */
			.driver_info = EM2884_BOARD_TERRATEC_H5 पूर्ण,
	अणु USB_DEVICE(0x0ccd, 0x10ad),	/* H5 Rev. 2 */
			.driver_info = EM2884_BOARD_TERRATEC_H5 पूर्ण,
	अणु USB_DEVICE(0x0ccd, 0x10b6),	/* H5 Rev. 3 */
			.driver_info = EM2884_BOARD_TERRATEC_H5 पूर्ण,
	अणु USB_DEVICE(0x0ccd, 0x10b2),	/* H6 */
			.driver_info = EM2884_BOARD_TERRATEC_H6 पूर्ण,
	अणु USB_DEVICE(0x0ccd, 0x0084),
			.driver_info = EM2860_BOARD_TERRATEC_AV350 पूर्ण,
	अणु USB_DEVICE(0x0ccd, 0x0096),
			.driver_info = EM2860_BOARD_TERRATEC_GRABBY पूर्ण,
	अणु USB_DEVICE(0x0ccd, 0x10AF),
			.driver_info = EM2860_BOARD_TERRATEC_GRABBY पूर्ण,
	अणु USB_DEVICE(0x0ccd, 0x00b2),
			.driver_info = EM2884_BOARD_CINERGY_HTC_STICK पूर्ण,
	अणु USB_DEVICE(0x0fd9, 0x0018),
			.driver_info = EM2884_BOARD_ELGATO_EYETV_HYBRID_2008 पूर्ण,
	अणु USB_DEVICE(0x0fd9, 0x0033),
			.driver_info = EM2860_BOARD_ELGATO_VIDEO_CAPTURE पूर्ण,
	अणु USB_DEVICE(0x185b, 0x2870),
			.driver_info = EM2870_BOARD_COMPRO_VIDEOMATE पूर्ण,
	अणु USB_DEVICE(0x185b, 0x2041),
			.driver_info = EM2820_BOARD_COMPRO_VIDEOMATE_FORYOU पूर्ण,
	अणु USB_DEVICE(0x2040, 0x4200),
			.driver_info = EM2820_BOARD_HAUPPAUGE_WINTV_USB_2 पूर्ण,
	अणु USB_DEVICE(0x2040, 0x4201),
			.driver_info = EM2820_BOARD_HAUPPAUGE_WINTV_USB_2 पूर्ण,
	अणु USB_DEVICE(0x2040, 0x6500),
			.driver_info = EM2880_BOARD_HAUPPAUGE_WINTV_HVR_900 पूर्ण,
	अणु USB_DEVICE(0x2040, 0x6502),
			.driver_info = EM2880_BOARD_HAUPPAUGE_WINTV_HVR_900_R2 पूर्ण,
	अणु USB_DEVICE(0x2040, 0x6513), /* HCW HVR-980 */
			.driver_info = EM2883_BOARD_HAUPPAUGE_WINTV_HVR_950 पूर्ण,
	अणु USB_DEVICE(0x2040, 0x6517), /* HP  HVR-950 */
			.driver_info = EM2883_BOARD_HAUPPAUGE_WINTV_HVR_950 पूर्ण,
	अणु USB_DEVICE(0x2040, 0x651b), /* RP  HVR-950 */
			.driver_info = EM2883_BOARD_HAUPPAUGE_WINTV_HVR_950 पूर्ण,
	अणु USB_DEVICE(0x2040, 0x651f),
			.driver_info = EM2883_BOARD_HAUPPAUGE_WINTV_HVR_850 पूर्ण,
	अणु USB_DEVICE(0x2040, 0x0265),
			.driver_info = EM28174_BOARD_HAUPPAUGE_WINTV_DUALHD_DVB पूर्ण,
	अणु USB_DEVICE(0x2040, 0x8265),
			.driver_info = EM28174_BOARD_HAUPPAUGE_WINTV_DUALHD_DVB पूर्ण,
	अणु USB_DEVICE(0x2040, 0x026d),
			.driver_info = EM28174_BOARD_HAUPPAUGE_WINTV_DUALHD_01595 पूर्ण,
	अणु USB_DEVICE(0x2040, 0x826d),
			.driver_info = EM28174_BOARD_HAUPPAUGE_WINTV_DUALHD_01595 पूर्ण,
	अणु USB_DEVICE(0x2040, 0x846d),
			.driver_info = EM2874_BOARD_HAUPPAUGE_USB_QUADHD पूर्ण,
	अणु USB_DEVICE(0x0438, 0xb002),
			.driver_info = EM2880_BOARD_AMD_ATI_TV_WONDER_HD_600 पूर्ण,
	अणु USB_DEVICE(0x2001, 0xf112),
			.driver_info = EM2820_BOARD_DLINK_USB_TV पूर्ण,
	अणु USB_DEVICE(0x2304, 0x0207),
			.driver_info = EM2820_BOARD_PINNACLE_DVC_90 पूर्ण,
	अणु USB_DEVICE(0x2304, 0x0208),
			.driver_info = EM2820_BOARD_PINNACLE_USB_2 पूर्ण,
	अणु USB_DEVICE(0x2304, 0x021a),
			.driver_info = EM2820_BOARD_PINNACLE_DVC_90 पूर्ण,
	अणु USB_DEVICE(0x2304, 0x0226),
			.driver_info = EM2882_BOARD_PINNACLE_HYBRID_PRO_330E पूर्ण,
	अणु USB_DEVICE(0x2304, 0x0227),
			.driver_info = EM2880_BOARD_PINNACLE_PCTV_HD_PRO पूर्ण,
	अणु USB_DEVICE(0x2304, 0x023f),
			.driver_info = EM2874_BOARD_PCTV_HD_MINI_80E पूर्ण,
	अणु USB_DEVICE(0x0413, 0x6023),
			.driver_info = EM2800_BOARD_LEADTEK_WINFAST_USBII पूर्ण,
	अणु USB_DEVICE(0x093b, 0xa003),
		       .driver_info = EM2820_BOARD_PINNACLE_DVC_90 पूर्ण,
	अणु USB_DEVICE(0x093b, 0xa005),
			.driver_info = EM2861_BOARD_PLEXTOR_PX_TV100U पूर्ण,
	अणु USB_DEVICE(0x04bb, 0x0515),
			.driver_info = EM2820_BOARD_IODATA_GVMVP_SZ पूर्ण,
	अणु USB_DEVICE(0xeb1a, 0x50a6),
			.driver_info = EM2860_BOARD_GADMEI_UTV330 पूर्ण,
	अणु USB_DEVICE(0x1b80, 0xa340),
			.driver_info = EM2870_BOARD_KWORLD_A340 पूर्ण,
	अणु USB_DEVICE(0x1b80, 0xe346),
			.driver_info = EM2874_BOARD_KWORLD_UB435Q_V2 पूर्ण,
	अणु USB_DEVICE(0x1b80, 0xe34c),
			.driver_info = EM2874_BOARD_KWORLD_UB435Q_V3 पूर्ण,
	अणु USB_DEVICE(0x2013, 0x024f),
			.driver_info = EM28174_BOARD_PCTV_290E पूर्ण,
	अणु USB_DEVICE(0x2013, 0x024c),
			.driver_info = EM28174_BOARD_PCTV_460E पूर्ण,
	अणु USB_DEVICE(0x2040, 0x1605),
			.driver_info = EM2884_BOARD_HAUPPAUGE_WINTV_HVR_930C पूर्ण,
	अणु USB_DEVICE(0x1b80, 0xe755),
			.driver_info = EM2884_BOARD_C3TECH_DIGITAL_DUO पूर्ण,
	अणु USB_DEVICE(0xeb1a, 0x5006),
			.driver_info = EM2860_BOARD_HT_VIDBOX_NW03 पूर्ण,
	अणु USB_DEVICE(0x1b80, 0xe309), /* Sveon STV40 */
			.driver_info = EM2860_BOARD_EASYCAP पूर्ण,
	अणु USB_DEVICE(0x1b80, 0xe425),
			.driver_info = EM2874_BOARD_MAXMEDIA_UB425_TC पूर्ण,
	अणु USB_DEVICE(0x1f4d, 0x1abe),
			.driver_info = EM2860_BOARD_MYGICA_IGRABBER पूर्ण,
	अणु USB_DEVICE(0x2304, 0x0242),
			.driver_info = EM2884_BOARD_PCTV_510E पूर्ण,
	अणु USB_DEVICE(0x2013, 0x0251),
			.driver_info = EM2884_BOARD_PCTV_520E पूर्ण,
	अणु USB_DEVICE(0x1b80, 0xe1cc),
			.driver_info = EM2874_BOARD_DELOCK_61959 पूर्ण,
	अणु USB_DEVICE(0x1ae7, 0x9003),
			.driver_info = EM2765_BOARD_SPEEDLINK_VAD_LAPLACE पूर्ण,
	अणु USB_DEVICE(0x1ae7, 0x9004),
			.driver_info = EM2765_BOARD_SPEEDLINK_VAD_LAPLACE पूर्ण,
	अणु USB_DEVICE(0x2013, 0x0258),
			.driver_info = EM28178_BOARD_PCTV_461E पूर्ण,
	अणु USB_DEVICE(0x2013, 0x8258), /* Bulk transport 461e */
			.driver_info = EM28178_BOARD_PCTV_461E पूर्ण,
	अणु USB_DEVICE(0x2013, 0x0461),
			.driver_info = EM28178_BOARD_PCTV_461E_V2 पूर्ण,
	अणु USB_DEVICE(0x2013, 0x8461), /* Bulk transport 461e v2 */
			.driver_info = EM28178_BOARD_PCTV_461E_V2 पूर्ण,
	अणु USB_DEVICE(0x2013, 0x0259),
			.driver_info = EM28178_BOARD_PCTV_461E_V2 पूर्ण,
	अणु USB_DEVICE(0x2013, 0x025f),
			.driver_info = EM28178_BOARD_PCTV_292E पूर्ण,
	अणु USB_DEVICE(0x2013, 0x0264), /* Hauppauge WinTV-soloHD 292e SE */
			.driver_info = EM28178_BOARD_PCTV_292E पूर्ण,
	अणु USB_DEVICE(0x2040, 0x0264), /* Hauppauge WinTV-soloHD Isoc */
			.driver_info = EM28178_BOARD_PCTV_292E पूर्ण,
	अणु USB_DEVICE(0x2040, 0x8264), /* Hauppauge OEM Generic WinTV-soloHD Bulk */
			.driver_info = EM28178_BOARD_PCTV_292E पूर्ण,
	अणु USB_DEVICE(0x2040, 0x8268), /* Hauppauge Retail WinTV-soloHD Bulk */
			.driver_info = EM28178_BOARD_PCTV_292E पूर्ण,
	अणु USB_DEVICE(0x0413, 0x6f07),
			.driver_info = EM2861_BOARD_LEADTEK_VC100 पूर्ण,
	अणु USB_DEVICE(0xeb1a, 0x8179),
			.driver_info = EM28178_BOARD_TERRATEC_T2_STICK_HD पूर्ण,
	अणु USB_DEVICE(0x3275, 0x0085),
			.driver_info = EM28178_BOARD_PLEX_PX_BCUD पूर्ण,
	अणु USB_DEVICE(0xeb1a, 0x5051), /* Ion Video 2 PC MKII / Startech svid2usb23 / Raygo R12-41373 */
			.driver_info = EM2860_BOARD_TVP5150_REFERENCE_DESIGN पूर्ण,
	अणु USB_DEVICE(0x1b80, 0xe349), /* Magix USB Videowandler-2 */
		.driver_info = EM2861_BOARD_MAGIX_VIDEOWANDLER2 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(usb, em28xx_id_table);

/*
 * EEPROM hash table क्रम devices with generic USB IDs
 */
अटल स्थिर काष्ठा em28xx_hash_table em28xx_eeprom_hash[] = अणु
	/* P/N: SA 60002070465 Tuner: TVF7533-MF */
	अणु0x6ce05a8f, EM2820_BOARD_PROLINK_PLAYTV_USB2, TUNER_YMEC_TVF_5533MFपूर्ण,
	अणु0x72cc5a8b, EM2820_BOARD_PROLINK_PLAYTV_BOX4_USB2, TUNER_YMEC_TVF_5533MFपूर्ण,
	अणु0x966a0441, EM2880_BOARD_KWORLD_DVB_310U, TUNER_XC2028पूर्ण,
	अणु0x166a0441, EM2880_BOARD_EMPIRE_DUAL_TV, TUNER_XC2028पूर्ण,
	अणु0xcee44a99, EM2882_BOARD_EVGA_INDTUBE, TUNER_XC2028पूर्ण,
	अणु0xb8846b20, EM2881_BOARD_PINNACLE_HYBRID_PRO, TUNER_XC2028पूर्ण,
	अणु0x63f653bd, EM2870_BOARD_REDDO_DVB_C_USB_BOX, TUNER_ABSENTपूर्ण,
	अणु0x4e913442, EM2882_BOARD_DIKOM_DK300, TUNER_XC2028पूर्ण,
	अणु0x85dd871e, EM2882_BOARD_ZOLID_HYBRID_TV_STICK, TUNER_XC2028पूर्ण,
पूर्ण;

/* I2C devicelist hash table क्रम devices with generic USB IDs */
अटल स्थिर काष्ठा em28xx_hash_table em28xx_i2c_hash[] = अणु
	अणु0xb06a32c3, EM2800_BOARD_TERRATEC_CINERGY_200, TUNER_LG_PAL_NEW_TAPCपूर्ण,
	अणु0xf51200e3, EM2800_BOARD_VGEAR_POCKETTV, TUNER_LG_PAL_NEW_TAPCपूर्ण,
	अणु0x1ba50080, EM2860_BOARD_SAA711X_REFERENCE_DESIGN, TUNER_ABSENTपूर्ण,
	अणु0x77800080, EM2860_BOARD_TVP5150_REFERENCE_DESIGN, TUNER_ABSENTपूर्ण,
	अणु0xc51200e3, EM2820_BOARD_GADMEI_TVR200, TUNER_LG_PAL_NEW_TAPCपूर्ण,
	अणु0x4ba50080, EM2861_BOARD_GADMEI_UTV330PLUS, TUNER_TNF_5335MFपूर्ण,
	अणु0x6b800080, EM2874_BOARD_LEADERSHIP_ISDBT, TUNER_ABSENTपूर्ण,
	अणु0x27e10080, EM2882_BOARD_ZOLID_HYBRID_TV_STICK, TUNER_XC2028पूर्ण,
पूर्ण;

/* NOTE: पूर्णांकroduce a separate hash table क्रम devices with 16 bit eeproms */

पूर्णांक em28xx_tuner_callback(व्योम *ptr, पूर्णांक component, पूर्णांक command, पूर्णांक arg)
अणु
	काष्ठा em28xx_i2c_bus *i2c_bus = ptr;
	काष्ठा em28xx *dev = i2c_bus->dev;
	पूर्णांक rc = 0;

	अगर (dev->tuner_type != TUNER_XC2028 && dev->tuner_type != TUNER_XC5000)
		वापस 0;

	अगर (command != XC2028_TUNER_RESET && command != XC5000_TUNER_RESET)
		वापस 0;

	rc = em28xx_gpio_set(dev, dev->board.tuner_gpio);

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(em28xx_tuner_callback);

अटल अंतरभूत व्योम em28xx_set_xclk_i2c_speed(काष्ठा em28xx *dev)
अणु
	स्थिर काष्ठा em28xx_board *board = &em28xx_boards[dev->model];
	u8 xclk = board->xclk, i2c_speed = board->i2c_speed;

	/*
	 * Those are the शेष values क्रम the majority of boards
	 * Use those values अगर not specअगरied otherwise at boards entry
	 */
	अगर (!xclk)
		xclk = EM28XX_XCLK_IR_RC5_MODE |
		       EM28XX_XCLK_FREQUENCY_12MHZ;

	em28xx_ग_लिखो_reg(dev, EM28XX_R0F_XCLK, xclk);

	अगर (!i2c_speed)
		i2c_speed = EM28XX_I2C_CLK_WAIT_ENABLE |
			    EM28XX_I2C_FREQ_100_KHZ;

	dev->i2c_speed = i2c_speed & 0x03;

	अगर (!dev->board.is_em2800)
		em28xx_ग_लिखो_reg(dev, EM28XX_R06_I2C_CLK, i2c_speed);
	msleep(50);
पूर्ण

अटल अंतरभूत व्योम em28xx_set_model(काष्ठा em28xx *dev)
अणु
	dev->board = em28xx_boards[dev->model];
	dev->has_msp34xx = dev->board.has_msp34xx;
	dev->is_webcam = dev->board.is_webcam;

	em28xx_set_xclk_i2c_speed(dev);

	/* Should be initialized early, क्रम I2C to work */
	dev->def_i2c_bus = dev->board.def_i2c_bus;
पूर्ण

/*
 * Wait until AC97_RESET reports the expected value reliably beक्रमe proceeding.
 * We also check that two unrelated रेजिस्टरs accesses करोn't वापस the same
 * value to aव्योम premature वापस.
 * This procedure helps ensuring AC97 रेजिस्टर accesses are reliable.
 */
अटल पूर्णांक em28xx_रुको_until_ac97_features_equals(काष्ठा em28xx *dev,
						  पूर्णांक expected_feat)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(2000);
	पूर्णांक feat, घातerकरोwn;

	जबतक (समय_is_after_jअगरfies(समयout)) अणु
		feat = em28xx_पढ़ो_ac97(dev, AC97_RESET);
		अगर (feat < 0)
			वापस feat;

		घातerकरोwn = em28xx_पढ़ो_ac97(dev, AC97_POWERDOWN);
		अगर (घातerकरोwn < 0)
			वापस घातerकरोwn;

		अगर (feat == expected_feat && feat != घातerकरोwn)
			वापस 0;

		msleep(50);
	पूर्ण

	dev_warn(&dev->पूर्णांकf->dev, "AC97 registers access is not reliable !\n");
	वापस -ETIMEDOUT;
पूर्ण

/*
 * Since em28xx_pre_card_setup() requires a proper dev->model,
 * this won't work क्रम boards with generic PCI IDs
 */
अटल व्योम em28xx_pre_card_setup(काष्ठा em28xx *dev)
अणु
	/*
	 * Set the initial XCLK and I2C घड़ी values based on the board
	 * definition
	 */
	em28xx_set_xclk_i2c_speed(dev);

	/* request some modules */
	चयन (dev->model) अणु
	हाल EM2861_BOARD_PLEXTOR_PX_TV100U:
		/* Sets the msp34xx I2S speed */
		dev->i2s_speed = 2048000;
		अवरोध;
	हाल EM2861_BOARD_KWORLD_PVRTV_300U:
	हाल EM2880_BOARD_KWORLD_DVB_305U:
		em28xx_ग_लिखो_reg(dev, EM2820_R08_GPIO_CTRL, 0x6d);
		usleep_range(10000, 11000);
		em28xx_ग_लिखो_reg(dev, EM2820_R08_GPIO_CTRL, 0x7d);
		usleep_range(10000, 11000);
		अवरोध;
	हाल EM2870_BOARD_COMPRO_VIDEOMATE:
		/*
		 * TODO: someone can करो some cleanup here...
		 *	 not everything's needed
		 */
		em28xx_ग_लिखो_reg(dev, EM2880_R04_GPO, 0x00);
		usleep_range(10000, 11000);
		em28xx_ग_लिखो_reg(dev, EM2880_R04_GPO, 0x01);
		usleep_range(10000, 11000);
		em28xx_ग_लिखो_reg(dev, EM2820_R08_GPIO_CTRL, 0xfd);
		msleep(70);
		em28xx_ग_लिखो_reg(dev, EM2820_R08_GPIO_CTRL, 0xfc);
		msleep(70);
		em28xx_ग_लिखो_reg(dev, EM2820_R08_GPIO_CTRL, 0xdc);
		msleep(70);
		em28xx_ग_लिखो_reg(dev, EM2820_R08_GPIO_CTRL, 0xfc);
		msleep(70);
		अवरोध;
	हाल EM2870_BOARD_TERRATEC_XS_MT2060:
		/*
		 * this device needs some gpio ग_लिखोs to get the DVB-T
		 * demod work
		 */
		em28xx_ग_लिखो_reg(dev, EM2820_R08_GPIO_CTRL, 0xfe);
		msleep(70);
		em28xx_ग_लिखो_reg(dev, EM2820_R08_GPIO_CTRL, 0xde);
		msleep(70);
		em28xx_ग_लिखो_reg(dev, EM2820_R08_GPIO_CTRL, 0xfe);
		msleep(70);
		अवरोध;
	हाल EM2870_BOARD_PINNACLE_PCTV_DVB:
		/*
		 * this device needs some gpio ग_लिखोs to get the
		 * DVB-T demod work
		 */
		em28xx_ग_लिखो_reg(dev, EM2820_R08_GPIO_CTRL, 0xfe);
		msleep(70);
		em28xx_ग_लिखो_reg(dev, EM2820_R08_GPIO_CTRL, 0xde);
		msleep(70);
		em28xx_ग_लिखो_reg(dev, EM2820_R08_GPIO_CTRL, 0xfe);
		msleep(70);
		अवरोध;
	हाल EM2820_BOARD_GADMEI_UTV310:
	हाल EM2820_BOARD_MSI_VOX_USB_2:
		/* enables audio क्रम that devices */
		em28xx_ग_लिखो_reg(dev, EM2820_R08_GPIO_CTRL, 0xfd);
		अवरोध;

	हाल EM2882_BOARD_KWORLD_ATSC_315U:
		em28xx_ग_लिखो_reg(dev, EM2820_R08_GPIO_CTRL, 0xff);
		usleep_range(10000, 11000);
		em28xx_ग_लिखो_reg(dev, EM2820_R08_GPIO_CTRL, 0xfe);
		usleep_range(10000, 11000);
		em28xx_ग_लिखो_reg(dev, EM2880_R04_GPO, 0x00);
		usleep_range(10000, 11000);
		em28xx_ग_लिखो_reg(dev, EM2880_R04_GPO, 0x08);
		usleep_range(10000, 11000);
		अवरोध;

	हाल EM2860_BOARD_KAIOMY_TVNPC_U2:
		em28xx_ग_लिखो_regs(dev, EM28XX_R0F_XCLK, "\x07", 1);
		em28xx_ग_लिखो_regs(dev, EM28XX_R06_I2C_CLK, "\x40", 1);
		em28xx_ग_लिखो_regs(dev, 0x0d, "\x42", 1);
		em28xx_ग_लिखो_regs(dev, 0x08, "\xfd", 1);
		usleep_range(10000, 11000);
		em28xx_ग_लिखो_regs(dev, 0x08, "\xff", 1);
		usleep_range(10000, 11000);
		em28xx_ग_लिखो_regs(dev, 0x08, "\x7f", 1);
		usleep_range(10000, 11000);
		em28xx_ग_लिखो_regs(dev, 0x08, "\x6b", 1);

		अवरोध;
	हाल EM2860_BOARD_EASYCAP:
		em28xx_ग_लिखो_regs(dev, 0x08, "\xf8", 1);
		अवरोध;

	हाल EM2820_BOARD_IODATA_GVMVP_SZ:
		em28xx_ग_लिखो_reg(dev, EM2820_R08_GPIO_CTRL, 0xff);
		msleep(70);
		em28xx_ग_लिखो_reg(dev, EM2820_R08_GPIO_CTRL, 0xf7);
		usleep_range(10000, 11000);
		em28xx_ग_लिखो_reg(dev, EM2820_R08_GPIO_CTRL, 0xfe);
		msleep(70);
		em28xx_ग_लिखो_reg(dev, EM2820_R08_GPIO_CTRL, 0xfd);
		msleep(70);
		अवरोध;

	हाल EM2860_BOARD_TERRATEC_GRABBY:
		/*
		 * HACK?: Ensure AC97 रेजिस्टर पढ़ोing is reliable beक्रमe
		 * proceeding. In practice, this will रुको about 1.6 seconds.
		 */
		em28xx_रुको_until_ac97_features_equals(dev, 0x6a90);
		अवरोध;
	पूर्ण

	em28xx_gpio_set(dev, dev->board.tuner_gpio);
	em28xx_set_mode(dev, EM28XX_ANALOG_MODE);

	/* Unlock device */
	em28xx_set_mode(dev, EM28XX_SUSPEND);
पूर्ण

अटल पूर्णांक em28xx_hपूर्णांक_board(काष्ठा em28xx *dev)
अणु
	पूर्णांक i;

	अगर (dev->is_webcam) अणु
		अगर (dev->em28xx_sensor == EM28XX_MT9V011) अणु
			dev->model = EM2820_BOARD_SILVERCREST_WEBCAM;
		पूर्ण अन्यथा अगर (dev->em28xx_sensor == EM28XX_MT9M001 ||
			   dev->em28xx_sensor == EM28XX_MT9M111) अणु
			dev->model = EM2750_BOARD_UNKNOWN;
		पूर्ण
		/* FIXME: IMPROVE ! */

		वापस 0;
	पूर्ण

	/*
	 * HINT method: EEPROM
	 *
	 * This method works only क्रम boards with eeprom.
	 * Uses a hash of all eeprom bytes. The hash should be
	 * unique क्रम a venकरोr/tuner pair.
	 * There are a high chance that tuners क्रम dअगरferent
	 * video standards produce dअगरferent hashes.
	 */
	क्रम (i = 0; i < ARRAY_SIZE(em28xx_eeprom_hash); i++) अणु
		अगर (dev->hash == em28xx_eeprom_hash[i].hash) अणु
			dev->model = em28xx_eeprom_hash[i].model;
			dev->tuner_type = em28xx_eeprom_hash[i].tuner;

			dev_err(&dev->पूर्णांकf->dev,
				"Your board has no unique USB ID.\n"
				"A hint were successfully done, based on eeprom hash.\n"
				"This method is not 100%% failproof.\n"
				"If the board were misdetected, please email this log to:\n"
				"\tV4L Mailing List  <linux-media@vger.kernel.org>\n"
				"Board detected as %s\n",
			       em28xx_boards[dev->model].name);

			वापस 0;
		पूर्ण
	पूर्ण

	/*
	 * HINT method: I2C attached devices
	 *
	 * This method works क्रम all boards.
	 * Uses a hash of i2c scanned devices.
	 * Devices with the same i2c attached chips will
	 * be considered equal.
	 * This method is less precise than the eeprom one.
	 */

	/* user did not request i2c scanning => करो it now */
	अगर (!dev->i2c_hash)
		em28xx_करो_i2c_scan(dev, dev->def_i2c_bus);

	क्रम (i = 0; i < ARRAY_SIZE(em28xx_i2c_hash); i++) अणु
		अगर (dev->i2c_hash == em28xx_i2c_hash[i].hash) अणु
			dev->model = em28xx_i2c_hash[i].model;
			dev->tuner_type = em28xx_i2c_hash[i].tuner;
			dev_err(&dev->पूर्णांकf->dev,
				"Your board has no unique USB ID.\n"
				"A hint were successfully done, based on i2c devicelist hash.\n"
				"This method is not 100%% failproof.\n"
				"If the board were misdetected, please email this log to:\n"
				"\tV4L Mailing List  <linux-media@vger.kernel.org>\n"
				"Board detected as %s\n",
				em28xx_boards[dev->model].name);

			वापस 0;
		पूर्ण
	पूर्ण

	dev_err(&dev->पूर्णांकf->dev,
		"Your board has no unique USB ID and thus need a hint to be detected.\n"
		"You may try to use card=<n> insmod option to workaround that.\n"
		"Please send an email with this log to:\n"
		"\tV4L Mailing List <linux-media@vger.kernel.org>\n"
		"Board eeprom hash is 0x%08lx\n"
		"Board i2c devicelist hash is 0x%08lx\n",
		dev->hash, dev->i2c_hash);

	dev_err(&dev->पूर्णांकf->dev,
		"Here is a list of valid choices for the card=<n> insmod option:\n");
	क्रम (i = 0; i < em28xx_bcount; i++) अणु
		dev_err(&dev->पूर्णांकf->dev,
			"    card=%d -> %s\n", i, em28xx_boards[i].name);
	पूर्ण
	वापस -1;
पूर्ण

अटल व्योम em28xx_card_setup(काष्ठा em28xx *dev)
अणु
	पूर्णांक i, j, idx;
	bool duplicate_entry;

	/*
	 * If the device can be a webcam, seek क्रम a sensor.
	 * If sensor is not found, then it isn't a webcam.
	 */
	अगर (dev->is_webcam) अणु
		em28xx_detect_sensor(dev);
		अगर (dev->em28xx_sensor == EM28XX_NOSENSOR)
			/* NOTE: error/unknown sensor/no sensor */
			dev->is_webcam = 0;
	पूर्ण

	चयन (dev->model) अणु
	हाल EM2750_BOARD_UNKNOWN:
	हाल EM2820_BOARD_UNKNOWN:
	हाल EM2800_BOARD_UNKNOWN:
		/*
		 * The K-WORLD DVB-T 310U is detected as an MSI Digivox AD.
		 *
		 * This occurs because they share identical USB venकरोr and
		 * product IDs.
		 *
		 * What we करो here is look up the EEPROM hash of the K-WORLD
		 * and अगर it is found then we decide that we करो not have
		 * a DIGIVOX and reset the device to the K-WORLD instead.
		 *
		 * This solution is only valid अगर they करो not share eeprom
		 * hash identities which has not been determined as yet.
		 */
		अगर (em28xx_hपूर्णांक_board(dev) < 0) अणु
			dev_err(&dev->पूर्णांकf->dev, "Board not discovered\n");
		पूर्ण अन्यथा अणु
			em28xx_set_model(dev);
			em28xx_pre_card_setup(dev);
		पूर्ण
		अवरोध;
	शेष:
		em28xx_set_model(dev);
	पूर्ण

	dev_info(&dev->पूर्णांकf->dev, "Identified as %s (card=%d)\n",
		 dev->board.name, dev->model);

	dev->tuner_type = em28xx_boards[dev->model].tuner_type;

	/* request some modules */
	चयन (dev->model) अणु
	हाल EM2820_BOARD_HAUPPAUGE_WINTV_USB_2:
	हाल EM2880_BOARD_HAUPPAUGE_WINTV_HVR_900:
	हाल EM2880_BOARD_HAUPPAUGE_WINTV_HVR_900_R2:
	हाल EM2883_BOARD_HAUPPAUGE_WINTV_HVR_850:
	हाल EM2883_BOARD_HAUPPAUGE_WINTV_HVR_950:
	हाल EM2884_BOARD_HAUPPAUGE_WINTV_HVR_930C:
	हाल EM28174_BOARD_HAUPPAUGE_WINTV_DUALHD_DVB:
	हाल EM28174_BOARD_HAUPPAUGE_WINTV_DUALHD_01595:
	अणु
		काष्ठा tveeprom tv;

		अगर (!dev->eedata)
			अवरोध;
#अगर defined(CONFIG_MODULES) && defined(MODULE)
		request_module("tveeprom");
#पूर्ण_अगर
		/* Call first TVeeprom */

		tveeprom_hauppauge_analog(&tv, dev->eedata);

		dev->tuner_type = tv.tuner_type;

		अगर (tv.audio_processor == TVEEPROM_AUDPROC_MSP) अणु
			dev->i2s_speed = 2048000;
			dev->has_msp34xx = 1;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल EM2882_BOARD_KWORLD_ATSC_315U:
		em28xx_ग_लिखो_reg(dev, 0x0d, 0x42);
		usleep_range(10000, 11000);
		em28xx_ग_लिखो_reg(dev, EM2820_R08_GPIO_CTRL, 0xfd);
		usleep_range(10000, 11000);
		अवरोध;
	हाल EM2820_BOARD_KWORLD_PVRTV2800RF:
		/* GPIO enables sound on KWORLD PVR TV 2800RF */
		em28xx_ग_लिखो_reg(dev, EM2820_R08_GPIO_CTRL, 0xf9);
		अवरोध;
	हाल EM2820_BOARD_UNKNOWN:
	हाल EM2800_BOARD_UNKNOWN:
		/*
		 * The K-WORLD DVB-T 310U is detected as an MSI Digivox AD.
		 *
		 * This occurs because they share identical USB venकरोr and
		 * product IDs.
		 *
		 * What we करो here is look up the EEPROM hash of the K-WORLD
		 * and अगर it is found then we decide that we करो not have
		 * a DIGIVOX and reset the device to the K-WORLD instead.
		 *
		 * This solution is only valid अगर they करो not share eeprom
		 * hash identities which has not been determined as yet.
		 */
	हाल EM2880_BOARD_MSI_DIGIVOX_AD:
		अगर (!em28xx_hपूर्णांक_board(dev))
			em28xx_set_model(dev);

		/*
		 * In हालs where we had to use a board hपूर्णांक, the call to
		 * em28xx_set_mode() in em28xx_pre_card_setup() was a no-op,
		 * so make the call now so the analog GPIOs are set properly
		 * beक्रमe probing the i2c bus.
		 */
		em28xx_gpio_set(dev, dev->board.tuner_gpio);
		em28xx_set_mode(dev, EM28XX_ANALOG_MODE);
		अवरोध;

		/*
		 * The Dikom DK300 is detected as an Kworld VS-DVB-T 323UR.
		 *
		 * This occurs because they share identical USB venकरोr and
		 * product IDs.
		 *
		 * What we करो here is look up the EEPROM hash of the Dikom
		 * and अगर it is found then we decide that we करो not have
		 * a Kworld and reset the device to the Dikom instead.
		 *
		 * This solution is only valid अगर they करो not share eeprom
		 * hash identities which has not been determined as yet.
		 */
	हाल EM2882_BOARD_KWORLD_VS_DVBT:
		अगर (!em28xx_hपूर्णांक_board(dev))
			em28xx_set_model(dev);

		/*
		 * In हालs where we had to use a board hपूर्णांक, the call to
		 * em28xx_set_mode() in em28xx_pre_card_setup() was a no-op,
		 * so make the call now so the analog GPIOs are set properly
		 * beक्रमe probing the i2c bus.
		 */
		em28xx_gpio_set(dev, dev->board.tuner_gpio);
		em28xx_set_mode(dev, EM28XX_ANALOG_MODE);
		अवरोध;
	पूर्ण

	अगर (dev->board.valid == EM28XX_BOARD_NOT_VALIDATED) अणु
		dev_err(&dev->पूर्णांकf->dev,
			"\n\n"
			"The support for this board weren't valid yet.\n"
			"Please send a report of having this working\n"
			"not to V4L mailing list (and/or to other addresses)\n\n");
	पूर्ण

	/* Free eeprom data memory */
	kमुक्त(dev->eedata);
	dev->eedata = शून्य;

	/* Allow override tuner type by a module parameter */
	अगर (tuner >= 0)
		dev->tuner_type = tuner;

	/*
	 * Dynamically generate a list of valid audio inमाला_दो क्रम this
	 * specअगरic board, mapping them via क्रमागत em28xx_amux.
	 */

	idx = 0;
	क्रम (i = 0; i < MAX_EM28XX_INPUT; i++) अणु
		अगर (!INPUT(i)->type)
			जारी;

		/* Skip alपढ़ोy mapped audio inमाला_दो */
		duplicate_entry = false;
		क्रम (j = 0; j < idx; j++) अणु
			अगर (INPUT(i)->amux == dev->amux_map[j]) अणु
				duplicate_entry = true;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (duplicate_entry)
			जारी;

		dev->amux_map[idx++] = INPUT(i)->amux;
	पूर्ण
	क्रम (; idx < MAX_EM28XX_INPUT; idx++)
		dev->amux_map[idx] = EM28XX_AMUX_UNUSED;
पूर्ण

व्योम em28xx_setup_xc3028(काष्ठा em28xx *dev, काष्ठा xc2028_ctrl *ctl)
अणु
	स_रखो(ctl, 0, माप(*ctl));

	ctl->fname   = XC2028_DEFAULT_FIRMWARE;
	ctl->max_len = 64;
	ctl->mts = em28xx_boards[dev->model].mts_firmware;

	चयन (dev->model) अणु
	हाल EM2880_BOARD_EMPIRE_DUAL_TV:
	हाल EM2880_BOARD_HAUPPAUGE_WINTV_HVR_900:
	हाल EM2882_BOARD_TERRATEC_HYBRID_XS:
	हाल EM2880_BOARD_TERRATEC_HYBRID_XS:
	हाल EM2880_BOARD_TERRATEC_HYBRID_XS_FR:
	हाल EM2881_BOARD_PINNACLE_HYBRID_PRO:
	हाल EM2882_BOARD_ZOLID_HYBRID_TV_STICK:
		ctl->demod = XC3028_FE_ZARLINK456;
		अवरोध;
	हाल EM2880_BOARD_HAUPPAUGE_WINTV_HVR_900_R2:
	हाल EM2882_BOARD_PINNACLE_HYBRID_PRO_330E:
		ctl->demod = XC3028_FE_DEFAULT;
		अवरोध;
	हाल EM2880_BOARD_AMD_ATI_TV_WONDER_HD_600:
		ctl->demod = XC3028_FE_DEFAULT;
		ctl->fname = XC3028L_DEFAULT_FIRMWARE;
		अवरोध;
	हाल EM2883_BOARD_HAUPPAUGE_WINTV_HVR_850:
	हाल EM2883_BOARD_HAUPPAUGE_WINTV_HVR_950:
	हाल EM2880_BOARD_PINNACLE_PCTV_HD_PRO:
		/* FIXME: Better to specअगरy the needed IF */
		ctl->demod = XC3028_FE_DEFAULT;
		अवरोध;
	हाल EM2883_BOARD_KWORLD_HYBRID_330U:
	हाल EM2882_BOARD_DIKOM_DK300:
	हाल EM2882_BOARD_KWORLD_VS_DVBT:
		ctl->demod = XC3028_FE_CHINA;
		ctl->fname = XC2028_DEFAULT_FIRMWARE;
		अवरोध;
	हाल EM2882_BOARD_EVGA_INDTUBE:
		ctl->demod = XC3028_FE_CHINA;
		ctl->fname = XC3028L_DEFAULT_FIRMWARE;
		अवरोध;
	शेष:
		ctl->demod = XC3028_FE_OREN538;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(em28xx_setup_xc3028);

अटल व्योम request_module_async(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा em28xx *dev = container_of(work,
			     काष्ठा em28xx, request_module_wk);

	/*
	 * The em28xx extensions can be modules or builtin. If the
	 * modules are alपढ़ोy loaded or are built in, those extensions
	 * can be initialised right now. Otherwise, the module init
	 * code will करो it.
	 */

	/*
	 * Devices with an audio-only पूर्णांकf also have a V4L/DVB/RC
	 * पूर्णांकf. Don't रेजिस्टर extensions twice on those devices.
	 */
	अगर (dev->is_audio_only) अणु
#अगर defined(CONFIG_MODULES) && defined(MODULE)
		request_module("em28xx-alsa");
#पूर्ण_अगर
		वापस;
	पूर्ण

	em28xx_init_extension(dev);

#अगर defined(CONFIG_MODULES) && defined(MODULE)
	अगर (dev->has_video)
		request_module("em28xx-v4l");
	अगर (dev->usb_audio_type == EM28XX_USB_AUDIO_CLASS)
		request_module("snd-usb-audio");
	अन्यथा अगर (dev->usb_audio_type == EM28XX_USB_AUDIO_VENDOR)
		request_module("em28xx-alsa");
	अगर (dev->board.has_dvb)
		request_module("em28xx-dvb");
	अगर (dev->board.buttons ||
	    ((dev->board.ir_codes || dev->board.has_ir_i2c) && !disable_ir))
		request_module("em28xx-rc");
#पूर्ण_अगर /* CONFIG_MODULES */
पूर्ण

अटल व्योम request_modules(काष्ठा em28xx *dev)
अणु
	INIT_WORK(&dev->request_module_wk, request_module_async);
	schedule_work(&dev->request_module_wk);
पूर्ण

अटल व्योम flush_request_modules(काष्ठा em28xx *dev)
अणु
	flush_work(&dev->request_module_wk);
पूर्ण

अटल पूर्णांक em28xx_media_device_init(काष्ठा em28xx *dev,
				    काष्ठा usb_device *udev)
अणु
#अगर_घोषित CONFIG_MEDIA_CONTROLLER
	काष्ठा media_device *mdev;

	mdev = kzalloc(माप(*mdev), GFP_KERNEL);
	अगर (!mdev)
		वापस -ENOMEM;

	अगर (udev->product)
		media_device_usb_init(mdev, udev, udev->product);
	अन्यथा अगर (udev->manufacturer)
		media_device_usb_init(mdev, udev, udev->manufacturer);
	अन्यथा
		media_device_usb_init(mdev, udev, dev_name(&dev->पूर्णांकf->dev));

	dev->media_dev = mdev;
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल व्योम em28xx_unरेजिस्टर_media_device(काष्ठा em28xx *dev)
अणु
#अगर_घोषित CONFIG_MEDIA_CONTROLLER
	अगर (dev->media_dev) अणु
		media_device_unरेजिस्टर(dev->media_dev);
		media_device_cleanup(dev->media_dev);
		kमुक्त(dev->media_dev);
		dev->media_dev = शून्य;
	पूर्ण
#पूर्ण_अगर
पूर्ण

/*
 * em28xx_release_resources()
 * unरेजिस्टरs the v4l2,i2c and usb devices
 * called when the device माला_लो disconnected or at module unload
 */
अटल व्योम em28xx_release_resources(काष्ठा em28xx *dev)
अणु
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(dev->पूर्णांकf);

	/*FIXME: I2C IR should be disconnected */

	mutex_lock(&dev->lock);

	em28xx_unरेजिस्टर_media_device(dev);

	अगर (dev->def_i2c_bus)
		em28xx_i2c_unरेजिस्टर(dev, 1);
	em28xx_i2c_unरेजिस्टर(dev, 0);

	अगर (dev->ts == PRIMARY_TS)
		usb_put_dev(udev);

	/* Mark device as unused */
	clear_bit(dev->devno, em28xx_devused);

	mutex_unlock(&dev->lock);
पूर्ण;

/**
 * em28xx_मुक्त_device() - Free em28xx device
 *
 * @ref: काष्ठा kref क्रम em28xx device
 *
 * This is called when all extensions and em28xx core unरेजिस्टरs a device
 */
व्योम em28xx_मुक्त_device(काष्ठा kref *ref)
अणु
	काष्ठा em28xx *dev = kref_to_dev(ref);

	dev_info(&dev->पूर्णांकf->dev, "Freeing device\n");

	अगर (!dev->disconnected)
		em28xx_release_resources(dev);

	अगर (dev->ts == PRIMARY_TS)
		kमुक्त(dev->alt_max_pkt_size_isoc);

	kमुक्त(dev);
पूर्ण
EXPORT_SYMBOL_GPL(em28xx_मुक्त_device);

/*
 * em28xx_init_dev()
 * allocates and inits the device काष्ठाs, रेजिस्टरs i2c bus and v4l device
 */
अटल पूर्णांक em28xx_init_dev(काष्ठा em28xx *dev, काष्ठा usb_device *udev,
			   काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			   पूर्णांक minor)
अणु
	पूर्णांक retval;
	स्थिर अक्षर *chip_name = शून्य;

	dev->पूर्णांकf = पूर्णांकf;
	mutex_init(&dev->ctrl_urb_lock);
	spin_lock_init(&dev->slock);

	dev->em28xx_ग_लिखो_regs = em28xx_ग_लिखो_regs;
	dev->em28xx_पढ़ो_reg = em28xx_पढ़ो_reg;
	dev->em28xx_पढ़ो_reg_req_len = em28xx_पढ़ो_reg_req_len;
	dev->em28xx_ग_लिखो_regs_req = em28xx_ग_लिखो_regs_req;
	dev->em28xx_पढ़ो_reg_req = em28xx_पढ़ो_reg_req;
	dev->board.is_em2800 = em28xx_boards[dev->model].is_em2800;

	em28xx_set_model(dev);

	dev->रुको_after_ग_लिखो = 5;

	/* Based on the Chip ID, set the device configuration */
	retval = em28xx_पढ़ो_reg(dev, EM28XX_R0A_CHIPID);
	अगर (retval > 0) अणु
		dev->chip_id = retval;

		चयन (dev->chip_id) अणु
		हाल CHIP_ID_EM2800:
			chip_name = "em2800";
			अवरोध;
		हाल CHIP_ID_EM2710:
			chip_name = "em2710";
			अवरोध;
		हाल CHIP_ID_EM2750:
			chip_name = "em2750";
			अवरोध;
		हाल CHIP_ID_EM2765:
			chip_name = "em2765";
			dev->रुको_after_ग_लिखो = 0;
			dev->is_em25xx = 1;
			dev->eeprom_addrwidth_16bit = 1;
			अवरोध;
		हाल CHIP_ID_EM2820:
			chip_name = "em2710/2820";
			अगर (le16_to_cpu(udev->descriptor.idVenकरोr) == 0xeb1a) अणु
				__le16 idProd = udev->descriptor.idProduct;

				अगर (le16_to_cpu(idProd) == 0x2710)
					chip_name = "em2710";
				अन्यथा अगर (le16_to_cpu(idProd) == 0x2820)
					chip_name = "em2820";
			पूर्ण
			/* NOTE: the em2820 is used in webcams, too ! */
			अवरोध;
		हाल CHIP_ID_EM2840:
			chip_name = "em2840";
			अवरोध;
		हाल CHIP_ID_EM2860:
			chip_name = "em2860";
			अवरोध;
		हाल CHIP_ID_EM2870:
			chip_name = "em2870";
			dev->रुको_after_ग_लिखो = 0;
			अवरोध;
		हाल CHIP_ID_EM2874:
			chip_name = "em2874";
			dev->रुको_after_ग_लिखो = 0;
			dev->eeprom_addrwidth_16bit = 1;
			अवरोध;
		हाल CHIP_ID_EM28174:
			chip_name = "em28174";
			dev->रुको_after_ग_लिखो = 0;
			dev->eeprom_addrwidth_16bit = 1;
			अवरोध;
		हाल CHIP_ID_EM28178:
			chip_name = "em28178";
			dev->रुको_after_ग_लिखो = 0;
			dev->eeprom_addrwidth_16bit = 1;
			अवरोध;
		हाल CHIP_ID_EM2883:
			chip_name = "em2882/3";
			dev->रुको_after_ग_लिखो = 0;
			अवरोध;
		हाल CHIP_ID_EM2884:
			chip_name = "em2884";
			dev->रुको_after_ग_लिखो = 0;
			dev->eeprom_addrwidth_16bit = 1;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!chip_name)
		dev_info(&dev->पूर्णांकf->dev,
			 "unknown em28xx chip ID (%d)\n", dev->chip_id);
	अन्यथा
		dev_info(&dev->पूर्णांकf->dev, "chip ID is %s\n", chip_name);

	em28xx_media_device_init(dev, udev);

	अगर (dev->is_audio_only) अणु
		retval = em28xx_audio_setup(dev);
		अगर (retval)
			वापस -ENODEV;
		em28xx_init_extension(dev);

		वापस 0;
	पूर्ण

	em28xx_pre_card_setup(dev);

	rt_mutex_init(&dev->i2c_bus_lock);

	/* रेजिस्टर i2c bus 0 */
	अगर (dev->board.is_em2800)
		retval = em28xx_i2c_रेजिस्टर(dev, 0, EM28XX_I2C_ALGO_EM2800);
	अन्यथा
		retval = em28xx_i2c_रेजिस्टर(dev, 0, EM28XX_I2C_ALGO_EM28XX);
	अगर (retval < 0) अणु
		dev_err(&dev->पूर्णांकf->dev,
			"%s: em28xx_i2c_register bus 0 - error [%d]!\n",
		       __func__, retval);
		वापस retval;
	पूर्ण

	/* रेजिस्टर i2c bus 1 */
	अगर (dev->def_i2c_bus) अणु
		अगर (dev->is_em25xx)
			retval = em28xx_i2c_रेजिस्टर(dev, 1,
						     EM28XX_I2C_ALGO_EM25XX_BUS_B);
		अन्यथा
			retval = em28xx_i2c_रेजिस्टर(dev, 1,
						     EM28XX_I2C_ALGO_EM28XX);
		अगर (retval < 0) अणु
			dev_err(&dev->पूर्णांकf->dev,
				"%s: em28xx_i2c_register bus 1 - error [%d]!\n",
				__func__, retval);

			em28xx_i2c_unरेजिस्टर(dev, 0);

			वापस retval;
		पूर्ण
	पूर्ण

	/* Do board specअगरic init and eeprom पढ़ोing */
	em28xx_card_setup(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक em28xx_duplicate_dev(काष्ठा em28xx *dev)
अणु
	पूर्णांक nr;
	काष्ठा em28xx *sec_dev = kmemdup(dev, माप(*sec_dev), GFP_KERNEL);

	अगर (!sec_dev) अणु
		dev->dev_next = शून्य;
		वापस -ENOMEM;
	पूर्ण
	/* Check to see next मुक्त device and mark as used */
	करो अणु
		nr = find_first_zero_bit(em28xx_devused, EM28XX_MAXBOARDS);
		अगर (nr >= EM28XX_MAXBOARDS) अणु
			/* No मुक्त device slots */
			dev_warn(&dev->पूर्णांकf->dev, ": Supports only %i em28xx boards.\n",
				 EM28XX_MAXBOARDS);
			kमुक्त(sec_dev);
			dev->dev_next = शून्य;
			वापस -ENOMEM;
		पूर्ण
	पूर्ण जबतक (test_and_set_bit(nr, em28xx_devused));
	sec_dev->devno = nr;
	snम_लिखो(sec_dev->name, 28, "em28xx #%d", nr);
	sec_dev->dev_next = शून्य;
	dev->dev_next = sec_dev;
	वापस 0;
पूर्ण

/* high bandwidth multiplier, as encoded in highspeed endpoपूर्णांक descriptors */
#घोषणा hb_mult(wMaxPacketSize) (1 + (((wMaxPacketSize) >> 11) & 0x03))

अटल व्योम em28xx_check_usb_descriptor(काष्ठा em28xx *dev,
					काष्ठा usb_device *udev,
					काष्ठा usb_पूर्णांकerface *पूर्णांकf,
					पूर्णांक alt, पूर्णांक ep,
					bool *has_venकरोr_audio,
					bool *has_video,
					bool *has_dvb)
अणु
	स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *e;
	पूर्णांक sizedescr, size;

	/*
	 * NOTE:
	 *
	 * Old logic with support क्रम isoc transfers only was:
	 *  0x82	isoc		=> analog
	 *  0x83	isoc		=> audio
	 *  0x84	isoc		=> digital
	 *
	 * New logic with support क्रम bulk transfers
	 *  0x82	isoc		=> analog
	 *  0x82	bulk		=> analog
	 *  0x83	isoc*		=> audio
	 *  0x84	isoc		=> digital
	 *  0x84	bulk		=> analog or digital**
	 *  0x85	isoc		=> digital TS2
	 *  0x85	bulk		=> digital TS2
	 * (*: audio should always be isoc)
	 * (**: analog, अगर ep 0x82 is isoc, otherwise digital)
	 *
	 * The new logic preserves backwards compatibility and
	 * reflects the endpoपूर्णांक configurations we have seen
	 * so far. But there might be devices क्रम which this
	 * logic is not sufficient...
	 */

	e = &पूर्णांकf->altsetting[alt].endpoपूर्णांक[ep].desc;

	अगर (!usb_endpoपूर्णांक_dir_in(e))
		वापस;

	sizedescr = le16_to_cpu(e->wMaxPacketSize);
	size = sizedescr & 0x7ff;

	अगर (udev->speed == USB_SPEED_HIGH)
		size = size * hb_mult(sizedescr);

	/* Only inspect input endpoपूर्णांकs */

	चयन (e->bEndpoपूर्णांकAddress) अणु
	हाल 0x82:
		*has_video = true;
		अगर (usb_endpoपूर्णांक_xfer_isoc(e)) अणु
			dev->analog_ep_isoc = e->bEndpoपूर्णांकAddress;
			dev->alt_max_pkt_size_isoc[alt] = size;
		पूर्ण अन्यथा अगर (usb_endpoपूर्णांक_xfer_bulk(e)) अणु
			dev->analog_ep_bulk = e->bEndpoपूर्णांकAddress;
		पूर्ण
		वापस;
	हाल 0x83:
		अगर (usb_endpoपूर्णांक_xfer_isoc(e))
			*has_venकरोr_audio = true;
		अन्यथा
			dev_err(&पूर्णांकf->dev,
				"error: skipping audio endpoint 0x83, because it uses bulk transfers !\n");
		वापस;
	हाल 0x84:
		अगर (*has_video && (usb_endpoपूर्णांक_xfer_bulk(e))) अणु
			dev->analog_ep_bulk = e->bEndpoपूर्णांकAddress;
		पूर्ण अन्यथा अणु
			अगर (usb_endpoपूर्णांक_xfer_isoc(e)) अणु
				अगर (size > dev->dvb_max_pkt_size_isoc) अणु
					/*
					 * 2) some manufacturers (e.g. Terratec)
					 * disable endpoपूर्णांकs by setting
					 * wMaxPacketSize to 0 bytes क्रम all
					 * alt settings. So far, we've seen
					 * this क्रम DVB isoc endpoपूर्णांकs only.
					 */
					*has_dvb = true;
					dev->dvb_ep_isoc = e->bEndpoपूर्णांकAddress;
					dev->dvb_max_pkt_size_isoc = size;
					dev->dvb_alt_isoc = alt;
				पूर्ण
			पूर्ण अन्यथा अणु
				*has_dvb = true;
				dev->dvb_ep_bulk = e->bEndpoपूर्णांकAddress;
			पूर्ण
		पूर्ण
		वापस;
	हाल 0x85:
		अगर (usb_endpoपूर्णांक_xfer_isoc(e)) अणु
			अगर (size > dev->dvb_max_pkt_size_isoc_ts2) अणु
				dev->dvb_ep_isoc_ts2 = e->bEndpoपूर्णांकAddress;
				dev->dvb_max_pkt_size_isoc_ts2 = size;
				dev->dvb_alt_isoc = alt;
			पूर्ण
		पूर्ण अन्यथा अणु
			dev->dvb_ep_bulk_ts2 = e->bEndpoपूर्णांकAddress;
		पूर्ण
		वापस;
	पूर्ण
पूर्ण

/*
 * em28xx_usb_probe()
 * checks क्रम supported devices
 */
अटल पूर्णांक em28xx_usb_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			    स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *udev;
	काष्ठा em28xx *dev = शून्य;
	पूर्णांक retval;
	bool has_venकरोr_audio = false, has_video = false, has_dvb = false;
	पूर्णांक i, nr, try_bulk;
	स्थिर पूर्णांक अगरnum = पूर्णांकf->altsetting[0].desc.bInterfaceNumber;
	अक्षर *speed;

	udev = usb_get_dev(पूर्णांकerface_to_usbdev(पूर्णांकf));

	/* Check to see next मुक्त device and mark as used */
	करो अणु
		nr = find_first_zero_bit(em28xx_devused, EM28XX_MAXBOARDS);
		अगर (nr >= EM28XX_MAXBOARDS) अणु
			/* No मुक्त device slots */
			dev_err(&पूर्णांकf->dev,
				"Driver supports up to %i em28xx boards.\n",
			       EM28XX_MAXBOARDS);
			retval = -ENOMEM;
			जाओ err_no_slot;
		पूर्ण
	पूर्ण जबतक (test_and_set_bit(nr, em28xx_devused));

	/* Don't रेजिस्टर audio पूर्णांकerfaces */
	अगर (पूर्णांकf->altsetting[0].desc.bInterfaceClass == USB_CLASS_AUDIO) अणु
		dev_info(&पूर्णांकf->dev,
			"audio device (%04x:%04x): interface %i, class %i\n",
			le16_to_cpu(udev->descriptor.idVenकरोr),
			le16_to_cpu(udev->descriptor.idProduct),
			अगरnum,
			पूर्णांकf->altsetting[0].desc.bInterfaceClass);

		retval = -ENODEV;
		जाओ err;
	पूर्ण

	/* allocate memory क्रम our device state and initialize it */
	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev) अणु
		retval = -ENOMEM;
		जाओ err;
	पूर्ण

	/* compute alternate max packet sizes */
	dev->alt_max_pkt_size_isoc = kसुस्मृति(पूर्णांकf->num_altsetting,
					     माप(dev->alt_max_pkt_size_isoc[0]),
					     GFP_KERNEL);
	अगर (!dev->alt_max_pkt_size_isoc) अणु
		kमुक्त(dev);
		retval = -ENOMEM;
		जाओ err;
	पूर्ण

	/* Get endpoपूर्णांकs */
	क्रम (i = 0; i < पूर्णांकf->num_altsetting; i++) अणु
		पूर्णांक ep;

		क्रम (ep = 0;
		     ep < पूर्णांकf->altsetting[i].desc.bNumEndpoपूर्णांकs;
		     ep++)
			em28xx_check_usb_descriptor(dev, udev, पूर्णांकf,
						    i, ep,
						    &has_venकरोr_audio,
						    &has_video,
						    &has_dvb);
	पूर्ण

	अगर (!(has_venकरोr_audio || has_video || has_dvb)) अणु
		retval = -ENODEV;
		जाओ err_मुक्त;
	पूर्ण

	चयन (udev->speed) अणु
	हाल USB_SPEED_LOW:
		speed = "1.5";
		अवरोध;
	हाल USB_SPEED_UNKNOWN:
	हाल USB_SPEED_FULL:
		speed = "12";
		अवरोध;
	हाल USB_SPEED_HIGH:
		speed = "480";
		अवरोध;
	शेष:
		speed = "unknown";
	पूर्ण

	dev_info(&पूर्णांकf->dev,
		"New device %s %s @ %s Mbps (%04x:%04x, interface %d, class %d)\n",
		udev->manufacturer ? udev->manufacturer : "",
		udev->product ? udev->product : "",
		speed,
		le16_to_cpu(udev->descriptor.idVenकरोr),
		le16_to_cpu(udev->descriptor.idProduct),
		अगरnum,
		पूर्णांकf->altsetting->desc.bInterfaceNumber);

	/*
	 * Make sure we have 480 Mbps of bandwidth, otherwise things like
	 * video stream wouldn't likely work, since 12 Mbps is generally
	 * not enough even क्रम most Digital TV streams.
	 */
	अगर (udev->speed != USB_SPEED_HIGH && disable_usb_speed_check == 0) अणु
		dev_err(&पूर्णांकf->dev, "Device initialization failed.\n");
		dev_err(&पूर्णांकf->dev,
			"Device must be connected to a high-speed USB 2.0 port.\n");
		retval = -ENODEV;
		जाओ err_मुक्त;
	पूर्ण

	dev->devno = nr;
	dev->model = id->driver_info;
	dev->alt   = -1;
	dev->is_audio_only = has_venकरोr_audio && !(has_video || has_dvb);
	dev->has_video = has_video;
	dev->अगरnum = अगरnum;

	dev->ts = PRIMARY_TS;
	snम_लिखो(dev->name, 28, "em28xx");
	dev->dev_next = शून्य;

	अगर (has_venकरोr_audio) अणु
		dev_info(&पूर्णांकf->dev,
			"Audio interface %i found (Vendor Class)\n", अगरnum);
		dev->usb_audio_type = EM28XX_USB_AUDIO_VENDOR;
	पूर्ण
	/* Checks अगर audio is provided by a USB Audio Class पूर्णांकf */
	क्रम (i = 0; i < udev->config->desc.bNumInterfaces; i++) अणु
		काष्ठा usb_पूर्णांकerface *uअगर = udev->config->पूर्णांकerface[i];

		अगर (uअगर->altsetting[0].desc.bInterfaceClass == USB_CLASS_AUDIO) अणु
			अगर (has_venकरोr_audio)
				dev_err(&पूर्णांकf->dev,
					"em28xx: device seems to have vendor AND usb audio class interfaces !\n"
					"\t\tThe vendor interface will be ignored. Please contact the developers <linux-media@vger.kernel.org>\n");
			dev->usb_audio_type = EM28XX_USB_AUDIO_CLASS;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (has_video)
		dev_info(&पूर्णांकf->dev, "Video interface %i found:%s%s\n",
			अगरnum,
			dev->analog_ep_bulk ? " bulk" : "",
			dev->analog_ep_isoc ? " isoc" : "");
	अगर (has_dvb)
		dev_info(&पूर्णांकf->dev, "DVB interface %i found:%s%s\n",
			अगरnum,
			dev->dvb_ep_bulk ? " bulk" : "",
			dev->dvb_ep_isoc ? " isoc" : "");

	dev->num_alt = पूर्णांकf->num_altsetting;

	अगर ((अचिन्हित पूर्णांक)card[nr] < em28xx_bcount)
		dev->model = card[nr];

	/* save our data poपूर्णांकer in this पूर्णांकf device */
	usb_set_पूर्णांकfdata(पूर्णांकf, dev);

	/* allocate device काष्ठा and check अगर the device is a webcam */
	mutex_init(&dev->lock);
	retval = em28xx_init_dev(dev, udev, पूर्णांकf, nr);
	अगर (retval)
		जाओ err_मुक्त;

	अगर (usb_xfer_mode < 0) अणु
		अगर (dev->is_webcam)
			try_bulk = 1;
		अन्यथा
			try_bulk = 0;
	पूर्ण अन्यथा अणु
		try_bulk = usb_xfer_mode > 0;
	पूर्ण

	/* Disable V4L2 अगर the device करोesn't have a decoder or image sensor */
	अगर (has_video &&
	    dev->board.decoder == EM28XX_NODECODER &&
	    dev->em28xx_sensor == EM28XX_NOSENSOR) अणु
		dev_err(&पूर्णांकf->dev,
			"Currently, V4L2 is not supported on this model\n");
		has_video = false;
		dev->has_video = false;
	पूर्ण

	अगर (dev->board.has_dual_ts &&
	    (dev->tuner_type != TUNER_ABSENT || INPUT(0)->type)) अणु
		/*
		 * The logic with sets alternate is not पढ़ोy क्रम dual-tuners
		 * which analog modes.
		 */
		dev_err(&पूर्णांकf->dev,
			"We currently don't support analog TV or stream capture on dual tuners.\n");
		has_video = false;
	पूर्ण

	/* Select USB transfer types to use */
	अगर (has_video) अणु
		अगर (!dev->analog_ep_isoc || (try_bulk && dev->analog_ep_bulk))
			dev->analog_xfer_bulk = 1;
		dev_info(&पूर्णांकf->dev, "analog set to %s mode.\n",
			dev->analog_xfer_bulk ? "bulk" : "isoc");
	पूर्ण
	अगर (has_dvb) अणु
		अगर (!dev->dvb_ep_isoc || (try_bulk && dev->dvb_ep_bulk))
			dev->dvb_xfer_bulk = 1;
		dev_info(&पूर्णांकf->dev, "dvb set to %s mode.\n",
			dev->dvb_xfer_bulk ? "bulk" : "isoc");
	पूर्ण

	अगर (dev->board.has_dual_ts && em28xx_duplicate_dev(dev) == 0) अणु
		dev->dev_next->ts = SECONDARY_TS;
		dev->dev_next->alt   = -1;
		dev->dev_next->is_audio_only = has_venकरोr_audio &&
						!(has_video || has_dvb);
		dev->dev_next->has_video = false;
		dev->dev_next->अगरnum = अगरnum;
		dev->dev_next->model = id->driver_info;

		mutex_init(&dev->dev_next->lock);
		retval = em28xx_init_dev(dev->dev_next, udev, पूर्णांकf,
					 dev->dev_next->devno);
		अगर (retval)
			जाओ err_मुक्त;

		dev->dev_next->board.ir_codes = शून्य; /* No IR क्रम 2nd tuner */
		dev->dev_next->board.has_ir_i2c = 0; /* No IR क्रम 2nd tuner */

		अगर (usb_xfer_mode < 0) अणु
			अगर (dev->dev_next->is_webcam)
				try_bulk = 1;
			अन्यथा
				try_bulk = 0;
		पूर्ण अन्यथा अणु
			try_bulk = usb_xfer_mode > 0;
		पूर्ण

		/* Select USB transfer types to use */
		अगर (has_dvb) अणु
			अगर (!dev->dvb_ep_isoc_ts2 ||
			    (try_bulk && dev->dvb_ep_bulk_ts2))
				dev->dev_next->dvb_xfer_bulk = 1;
			dev_info(&dev->पूर्णांकf->dev, "dvb ts2 set to %s mode.\n",
				 dev->dev_next->dvb_xfer_bulk ? "bulk" : "isoc");
		पूर्ण

		dev->dev_next->dvb_ep_isoc = dev->dvb_ep_isoc_ts2;
		dev->dev_next->dvb_ep_bulk = dev->dvb_ep_bulk_ts2;
		dev->dev_next->dvb_max_pkt_size_isoc = dev->dvb_max_pkt_size_isoc_ts2;
		dev->dev_next->dvb_alt_isoc = dev->dvb_alt_isoc;

		/* Configuare hardware to support TS2*/
		अगर (dev->dvb_xfer_bulk) अणु
			/* The ep4 and ep5 are configuared क्रम BULK */
			em28xx_ग_लिखो_reg(dev, 0x0b, 0x96);
			mdelay(100);
			em28xx_ग_लिखो_reg(dev, 0x0b, 0x80);
			mdelay(100);
		पूर्ण अन्यथा अणु
			/* The ep4 and ep5 are configuared क्रम ISO */
			em28xx_ग_लिखो_reg(dev, 0x0b, 0x96);
			mdelay(100);
			em28xx_ग_लिखो_reg(dev, 0x0b, 0x82);
			mdelay(100);
		पूर्ण

		kref_init(&dev->dev_next->ref);
	पूर्ण

	kref_init(&dev->ref);

	request_modules(dev);

	/*
	 * Do it at the end, to reduce dynamic configuration changes during
	 * the device init. Yet, as request_modules() can be async, the
	 * topology will likely change after the load of the em28xx subdrivers.
	 */
#अगर_घोषित CONFIG_MEDIA_CONTROLLER
	retval = media_device_रेजिस्टर(dev->media_dev);
#पूर्ण_अगर

	वापस 0;

err_मुक्त:
	kमुक्त(dev->alt_max_pkt_size_isoc);
	kमुक्त(dev);

err:
	clear_bit(nr, em28xx_devused);

err_no_slot:
	usb_put_dev(udev);
	वापस retval;
पूर्ण

/*
 * em28xx_usb_disconnect()
 * called when the device माला_लो disconnected
 * video device will be unरेजिस्टरed on v4l2_बंद in हाल it is still खोलो
 */
अटल व्योम em28xx_usb_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा em28xx *dev;

	dev = usb_get_पूर्णांकfdata(पूर्णांकf);
	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);

	अगर (!dev)
		वापस;

	अगर (dev->dev_next) अणु
		dev->dev_next->disconnected = 1;
		dev_info(&dev->पूर्णांकf->dev, "Disconnecting %s\n",
			 dev->dev_next->name);
	पूर्ण

	dev->disconnected = 1;

	dev_info(&dev->पूर्णांकf->dev, "Disconnecting %s\n", dev->name);

	flush_request_modules(dev);

	em28xx_बंद_extension(dev);

	अगर (dev->dev_next)
		em28xx_release_resources(dev->dev_next);
	em28xx_release_resources(dev);

	अगर (dev->dev_next) अणु
		kref_put(&dev->dev_next->ref, em28xx_मुक्त_device);
		dev->dev_next = शून्य;
	पूर्ण
	kref_put(&dev->ref, em28xx_मुक्त_device);
पूर्ण

अटल पूर्णांक em28xx_usb_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			      pm_message_t message)
अणु
	काष्ठा em28xx *dev;

	dev = usb_get_पूर्णांकfdata(पूर्णांकf);
	अगर (!dev)
		वापस 0;
	em28xx_suspend_extension(dev);
	वापस 0;
पूर्ण

अटल पूर्णांक em28xx_usb_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा em28xx *dev;

	dev = usb_get_पूर्णांकfdata(पूर्णांकf);
	अगर (!dev)
		वापस 0;
	em28xx_resume_extension(dev);
	वापस 0;
पूर्ण

अटल काष्ठा usb_driver em28xx_usb_driver = अणु
	.name = "em28xx",
	.probe = em28xx_usb_probe,
	.disconnect = em28xx_usb_disconnect,
	.suspend = em28xx_usb_suspend,
	.resume = em28xx_usb_resume,
	.reset_resume = em28xx_usb_resume,
	.id_table = em28xx_id_table,
पूर्ण;

module_usb_driver(em28xx_usb_driver);
