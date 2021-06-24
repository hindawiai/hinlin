<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  cx18 functions to query card hardware
 *
 *  Derived from ivtv-cards.c
 *
 *  Copyright (C) 2007  Hans Verkuil <hverkuil@xs4all.nl>
 *  Copyright (C) 2008  Andy Walls <awalls@md.metrocast.net>
 */

#समावेश "cx18-driver.h"
#समावेश "cx18-cards.h"
#समावेश "cx18-av-core.h"
#समावेश "cx18-i2c.h"
#समावेश <media/i2c/cs5345.h>

#घोषणा V4L2_STD_PAL_SECAM (V4L2_STD_PAL|V4L2_STD_SECAM)

/********************** card configuration *******************************/

/* usual i2c tuner addresses to probe */
अटल काष्ठा cx18_card_tuner_i2c cx18_i2c_std = अणु
	.radio = अणु I2C_CLIENT_END पूर्ण,
	.demod = अणु 0x43, I2C_CLIENT_END पूर्ण,
	.tv    = अणु 0x61, 0x60, I2C_CLIENT_END पूर्ण,
पूर्ण;

/*
 * usual i2c tuner addresses to probe with additional demod address क्रम
 * an NXP TDA8295 at 0x42 (N.B. it can possibly be at 0x4b or 0x4c too).
 */
अटल काष्ठा cx18_card_tuner_i2c cx18_i2c_nxp = अणु
	.radio = अणु I2C_CLIENT_END पूर्ण,
	.demod = अणु 0x42, 0x43, I2C_CLIENT_END पूर्ण,
	.tv    = अणु 0x61, 0x60, I2C_CLIENT_END पूर्ण,
पूर्ण;

/* Please add new PCI IDs to: https://pci-ids.ucw.cz/
   This keeps the PCI ID database up to date. Note that the entries
   must be added under venकरोr 0x4444 (Conexant) as subप्रणाली IDs.
   New venकरोr IDs should still be added to the venकरोr ID list. */

/* Hauppauge HVR-1600 cards */

/* Note: क्रम Hauppauge cards the tveeprom inक्रमmation is used instead
   of PCI IDs */
अटल स्थिर काष्ठा cx18_card cx18_card_hvr1600_esmt = अणु
	.type = CX18_CARD_HVR_1600_ESMT,
	.name = "Hauppauge HVR-1600",
	.comment = "Simultaneous Digital and Analog TV capture supported\n",
	.v4l2_capabilities = CX18_CAP_ENCODER,
	.hw_audio_ctrl = CX18_HW_418_AV,
	.hw_muxer = CX18_HW_CS5345,
	.hw_all = CX18_HW_TVEEPROM | CX18_HW_418_AV | CX18_HW_TUNER |
		  CX18_HW_CS5345 | CX18_HW_DVB | CX18_HW_GPIO_RESET_CTRL |
		  CX18_HW_Z8F0811_IR_HAUP,
	.video_inमाला_दो = अणु
		अणु CX18_CARD_INPUT_VID_TUNER,  0, CX18_AV_COMPOSITE7 पूर्ण,
		अणु CX18_CARD_INPUT_SVIDEO1,    1, CX18_AV_SVIDEO1    पूर्ण,
		अणु CX18_CARD_INPUT_COMPOSITE1, 1, CX18_AV_COMPOSITE3 पूर्ण,
		अणु CX18_CARD_INPUT_SVIDEO2,    2, CX18_AV_SVIDEO2    पूर्ण,
		अणु CX18_CARD_INPUT_COMPOSITE2, 2, CX18_AV_COMPOSITE4 पूर्ण,
	पूर्ण,
	.audio_inमाला_दो = अणु
		अणु CX18_CARD_INPUT_AUD_TUNER,
		  CX18_AV_AUDIO8, CS5345_IN_1 | CS5345_MCLK_1_5 पूर्ण,
		अणु CX18_CARD_INPUT_LINE_IN1,
		  CX18_AV_AUDIO_SERIAL1, CS5345_IN_2 पूर्ण,
		अणु CX18_CARD_INPUT_LINE_IN2,
		  CX18_AV_AUDIO_SERIAL1, CS5345_IN_3 पूर्ण,
	पूर्ण,
	.radio_input = अणु CX18_CARD_INPUT_AUD_TUNER,
			 CX18_AV_AUDIO_SERIAL1, CS5345_IN_4 पूर्ण,
	.ddr = अणु
		/* ESMT M13S128324A-5B memory */
		.chip_config = 0x003,
		.refresh = 0x30c,
		.timing1 = 0x44220e82,
		.timing2 = 0x08,
		.tune_lane = 0,
		.initial_emrs = 0,
	पूर्ण,
	.gpio_init.initial_value = 0x3001,
	.gpio_init.direction = 0x3001,
	.gpio_i2c_slave_reset = अणु
		.active_lo_mask = 0x3001,
		.msecs_निश्चितed = 10,
		.msecs_recovery = 40,
		.ir_reset_mask  = 0x0001,
	पूर्ण,
	.i2c = &cx18_i2c_std,
पूर्ण;

अटल स्थिर काष्ठा cx18_card cx18_card_hvr1600_s5h1411 = अणु
	.type = CX18_CARD_HVR_1600_S5H1411,
	.name = "Hauppauge HVR-1600",
	.comment = "Simultaneous Digital and Analog TV capture supported\n",
	.v4l2_capabilities = CX18_CAP_ENCODER,
	.hw_audio_ctrl = CX18_HW_418_AV,
	.hw_muxer = CX18_HW_CS5345,
	.hw_all = CX18_HW_TVEEPROM | CX18_HW_418_AV | CX18_HW_TUNER |
		  CX18_HW_CS5345 | CX18_HW_DVB | CX18_HW_GPIO_RESET_CTRL |
		  CX18_HW_Z8F0811_IR_HAUP,
	.video_inमाला_दो = अणु
		अणु CX18_CARD_INPUT_VID_TUNER,  0, CX18_AV_COMPOSITE7 पूर्ण,
		अणु CX18_CARD_INPUT_SVIDEO1,    1, CX18_AV_SVIDEO1    पूर्ण,
		अणु CX18_CARD_INPUT_COMPOSITE1, 1, CX18_AV_COMPOSITE3 पूर्ण,
		अणु CX18_CARD_INPUT_SVIDEO2,    2, CX18_AV_SVIDEO2    पूर्ण,
		अणु CX18_CARD_INPUT_COMPOSITE2, 2, CX18_AV_COMPOSITE4 पूर्ण,
	पूर्ण,
	.audio_inमाला_दो = अणु
		अणु CX18_CARD_INPUT_AUD_TUNER,
		  CX18_AV_AUDIO8, CS5345_IN_1 | CS5345_MCLK_1_5 पूर्ण,
		अणु CX18_CARD_INPUT_LINE_IN1,
		  CX18_AV_AUDIO_SERIAL1, CS5345_IN_2 पूर्ण,
		अणु CX18_CARD_INPUT_LINE_IN2,
		  CX18_AV_AUDIO_SERIAL1, CS5345_IN_3 पूर्ण,
	पूर्ण,
	.radio_input = अणु CX18_CARD_INPUT_AUD_TUNER,
			 CX18_AV_AUDIO_SERIAL1, CS5345_IN_4 पूर्ण,
	.ddr = अणु
		/* ESMT M13S128324A-5B memory */
		.chip_config = 0x003,
		.refresh = 0x30c,
		.timing1 = 0x44220e82,
		.timing2 = 0x08,
		.tune_lane = 0,
		.initial_emrs = 0,
	पूर्ण,
	.gpio_init.initial_value = 0x3801,
	.gpio_init.direction = 0x3801,
	.gpio_i2c_slave_reset = अणु
		.active_lo_mask = 0x3801,
		.msecs_निश्चितed = 10,
		.msecs_recovery = 40,
		.ir_reset_mask  = 0x0001,
	पूर्ण,
	.i2c = &cx18_i2c_nxp,
पूर्ण;

अटल स्थिर काष्ठा cx18_card cx18_card_hvr1600_samsung = अणु
	.type = CX18_CARD_HVR_1600_SAMSUNG,
	.name = "Hauppauge HVR-1600 (Preproduction)",
	.comment = "Simultaneous Digital and Analog TV capture supported\n",
	.v4l2_capabilities = CX18_CAP_ENCODER,
	.hw_audio_ctrl = CX18_HW_418_AV,
	.hw_muxer = CX18_HW_CS5345,
	.hw_all = CX18_HW_TVEEPROM | CX18_HW_418_AV | CX18_HW_TUNER |
		  CX18_HW_CS5345 | CX18_HW_DVB | CX18_HW_GPIO_RESET_CTRL |
		  CX18_HW_Z8F0811_IR_HAUP,
	.video_inमाला_दो = अणु
		अणु CX18_CARD_INPUT_VID_TUNER,  0, CX18_AV_COMPOSITE7 पूर्ण,
		अणु CX18_CARD_INPUT_SVIDEO1,    1, CX18_AV_SVIDEO1    पूर्ण,
		अणु CX18_CARD_INPUT_COMPOSITE1, 1, CX18_AV_COMPOSITE3 पूर्ण,
		अणु CX18_CARD_INPUT_SVIDEO2,    2, CX18_AV_SVIDEO2    पूर्ण,
		अणु CX18_CARD_INPUT_COMPOSITE2, 2, CX18_AV_COMPOSITE4 पूर्ण,
	पूर्ण,
	.audio_inमाला_दो = अणु
		अणु CX18_CARD_INPUT_AUD_TUNER,
		  CX18_AV_AUDIO8, CS5345_IN_1 | CS5345_MCLK_1_5 पूर्ण,
		अणु CX18_CARD_INPUT_LINE_IN1,
		  CX18_AV_AUDIO_SERIAL1, CS5345_IN_2 पूर्ण,
		अणु CX18_CARD_INPUT_LINE_IN2,
		  CX18_AV_AUDIO_SERIAL1, CS5345_IN_3 पूर्ण,
	पूर्ण,
	.radio_input = अणु CX18_CARD_INPUT_AUD_TUNER,
			 CX18_AV_AUDIO_SERIAL1, CS5345_IN_4 पूर्ण,
	.ddr = अणु
		/* Samsung K4D263238G-VC33 memory */
		.chip_config = 0x003,
		.refresh = 0x30c,
		.timing1 = 0x23230b73,
		.timing2 = 0x08,
		.tune_lane = 0,
		.initial_emrs = 2,
	पूर्ण,
	.gpio_init.initial_value = 0x3001,
	.gpio_init.direction = 0x3001,
	.gpio_i2c_slave_reset = अणु
		.active_lo_mask = 0x3001,
		.msecs_निश्चितed = 10,
		.msecs_recovery = 40,
		.ir_reset_mask  = 0x0001,
	पूर्ण,
	.i2c = &cx18_i2c_std,
पूर्ण;

/* ------------------------------------------------------------------------- */

/* Compro VideoMate H900: note that this card is analog only! */

अटल स्थिर काष्ठा cx18_card_pci_info cx18_pci_h900[] = अणु
	अणु PCI_DEVICE_ID_CX23418, CX18_PCI_ID_COMPRO, 0xe100 पूर्ण,
	अणु 0, 0, 0 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा cx18_card cx18_card_h900 = अणु
	.type = CX18_CARD_COMPRO_H900,
	.name = "Compro VideoMate H900",
	.comment = "Analog TV capture supported\n",
	.v4l2_capabilities = CX18_CAP_ENCODER,
	.hw_audio_ctrl = CX18_HW_418_AV,
	.hw_all = CX18_HW_418_AV | CX18_HW_TUNER | CX18_HW_GPIO_RESET_CTRL,
	.video_inमाला_दो = अणु
		अणु CX18_CARD_INPUT_VID_TUNER,  0, CX18_AV_COMPOSITE2 पूर्ण,
		अणु CX18_CARD_INPUT_SVIDEO1,    1,
			CX18_AV_SVIDEO_LUMA3 | CX18_AV_SVIDEO_CHROMA4 पूर्ण,
		अणु CX18_CARD_INPUT_COMPOSITE1, 1, CX18_AV_COMPOSITE1 पूर्ण,
	पूर्ण,
	.audio_inमाला_दो = अणु
		अणु CX18_CARD_INPUT_AUD_TUNER,
		  CX18_AV_AUDIO5, 0 पूर्ण,
		अणु CX18_CARD_INPUT_LINE_IN1,
		  CX18_AV_AUDIO_SERIAL1, 0 पूर्ण,
	पूर्ण,
	.radio_input = अणु CX18_CARD_INPUT_AUD_TUNER,
			 CX18_AV_AUDIO_SERIAL1, 0 पूर्ण,
	.tuners = अणु
		अणु .std = V4L2_STD_ALL, .tuner = TUNER_XC2028 पूर्ण,
	पूर्ण,
	.ddr = अणु
		/* EtronTech EM6A9160TS-5G memory */
		.chip_config = 0x50003,
		.refresh = 0x753,
		.timing1 = 0x24330e84,
		.timing2 = 0x1f,
		.tune_lane = 0,
		.initial_emrs = 0,
	पूर्ण,
	.xceive_pin = 15,
	.pci_list = cx18_pci_h900,
	.i2c = &cx18_i2c_std,
पूर्ण;

/* ------------------------------------------------------------------------- */

/* Yuan MPC718: not working at the moment! */

अटल स्थिर काष्ठा cx18_card_pci_info cx18_pci_mpc718[] = अणु
	अणु PCI_DEVICE_ID_CX23418, CX18_PCI_ID_YUAN, 0x0718 पूर्ण,
	अणु 0, 0, 0 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा cx18_card cx18_card_mpc718 = अणु
	.type = CX18_CARD_YUAN_MPC718,
	.name = "Yuan MPC718 MiniPCI DVB-T/Analog",
	.comment = "Experimenters needed for device to work well.\n"
		  "\tTo help, mail the linux-media list (www.linuxtv.org).\n",
	.v4l2_capabilities = CX18_CAP_ENCODER,
	.hw_audio_ctrl = CX18_HW_418_AV,
	.hw_muxer = CX18_HW_GPIO_MUX,
	.hw_all = CX18_HW_TVEEPROM | CX18_HW_418_AV | CX18_HW_TUNER |
		  CX18_HW_GPIO_MUX | CX18_HW_DVB | CX18_HW_GPIO_RESET_CTRL,
	.video_inमाला_दो = अणु
		अणु CX18_CARD_INPUT_VID_TUNER,  0, CX18_AV_COMPOSITE2 पूर्ण,
		अणु CX18_CARD_INPUT_SVIDEO1,    1,
				CX18_AV_SVIDEO_LUMA3 | CX18_AV_SVIDEO_CHROMA4 पूर्ण,
		अणु CX18_CARD_INPUT_COMPOSITE1, 1, CX18_AV_COMPOSITE1 पूर्ण,
		अणु CX18_CARD_INPUT_SVIDEO2,    2,
				CX18_AV_SVIDEO_LUMA7 | CX18_AV_SVIDEO_CHROMA8 पूर्ण,
		अणु CX18_CARD_INPUT_COMPOSITE2, 2, CX18_AV_COMPOSITE6 पूर्ण,
	पूर्ण,
	.audio_inमाला_दो = अणु
		अणु CX18_CARD_INPUT_AUD_TUNER, CX18_AV_AUDIO5,        0 पूर्ण,
		अणु CX18_CARD_INPUT_LINE_IN1,  CX18_AV_AUDIO_SERIAL1, 1 पूर्ण,
		अणु CX18_CARD_INPUT_LINE_IN2,  CX18_AV_AUDIO_SERIAL2, 1 पूर्ण,
	पूर्ण,
	.tuners = अणु
		/* XC3028 tuner */
		अणु .std = V4L2_STD_ALL, .tuner = TUNER_XC2028 पूर्ण,
	पूर्ण,
	/* FIXME - the FM radio is just a guess and driver करोesn't use SIF */
	.radio_input = अणु CX18_CARD_INPUT_AUD_TUNER, CX18_AV_AUDIO5, 2 पूर्ण,
	.ddr = अणु
		/* Hynix HY5DU283222B DDR RAM */
		.chip_config = 0x303,
		.refresh = 0x3bd,
		.timing1 = 0x36320966,
		.timing2 = 0x1f,
		.tune_lane = 0,
		.initial_emrs = 2,
	पूर्ण,
	.gpio_init.initial_value = 0x1,
	.gpio_init.direction = 0x3,
	/* FIXME - these GPIO's are just guesses */
	.gpio_audio_input = अणु .mask   = 0x3,
			      .tuner  = 0x1,
			      .linein = 0x3,
			      .radio  = 0x1 पूर्ण,
	.xceive_pin = 0,
	.pci_list = cx18_pci_mpc718,
	.i2c = &cx18_i2c_std,
पूर्ण;

/* ------------------------------------------------------------------------- */

/* GoTView PCI */

अटल स्थिर काष्ठा cx18_card_pci_info cx18_pci_gotview_dvd3[] = अणु
	अणु PCI_DEVICE_ID_CX23418, CX18_PCI_ID_GOTVIEW, 0x3343 पूर्ण,
	अणु 0, 0, 0 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा cx18_card cx18_card_gotview_dvd3 = अणु
	.type = CX18_CARD_GOTVIEW_PCI_DVD3,
	.name = "GoTView PCI DVD3 Hybrid",
	.comment = "Experimenters needed for device to work well.\n"
		  "\tTo help, mail the linux-media list (www.linuxtv.org).\n",
	.v4l2_capabilities = CX18_CAP_ENCODER,
	.hw_audio_ctrl = CX18_HW_418_AV,
	.hw_muxer = CX18_HW_GPIO_MUX,
	.hw_all = CX18_HW_TVEEPROM | CX18_HW_418_AV | CX18_HW_TUNER |
		  CX18_HW_GPIO_MUX | CX18_HW_DVB | CX18_HW_GPIO_RESET_CTRL,
	.video_inमाला_दो = अणु
		अणु CX18_CARD_INPUT_VID_TUNER,  0, CX18_AV_COMPOSITE2 पूर्ण,
		अणु CX18_CARD_INPUT_SVIDEO1,    1,
				CX18_AV_SVIDEO_LUMA3 | CX18_AV_SVIDEO_CHROMA4 पूर्ण,
		अणु CX18_CARD_INPUT_COMPOSITE1, 1, CX18_AV_COMPOSITE1 पूर्ण,
		अणु CX18_CARD_INPUT_SVIDEO2,    2,
				CX18_AV_SVIDEO_LUMA7 | CX18_AV_SVIDEO_CHROMA8 पूर्ण,
		अणु CX18_CARD_INPUT_COMPOSITE2, 2, CX18_AV_COMPOSITE6 पूर्ण,
	पूर्ण,
	.audio_inमाला_दो = अणु
		अणु CX18_CARD_INPUT_AUD_TUNER, CX18_AV_AUDIO5,        0 पूर्ण,
		अणु CX18_CARD_INPUT_LINE_IN1,  CX18_AV_AUDIO_SERIAL1, 1 पूर्ण,
		अणु CX18_CARD_INPUT_LINE_IN2,  CX18_AV_AUDIO_SERIAL2, 1 पूर्ण,
	पूर्ण,
	.tuners = अणु
		/* XC3028 tuner */
		अणु .std = V4L2_STD_ALL, .tuner = TUNER_XC2028 पूर्ण,
	पूर्ण,
	/* FIXME - the FM radio is just a guess and driver करोesn't use SIF */
	.radio_input = अणु CX18_CARD_INPUT_AUD_TUNER, CX18_AV_AUDIO5, 2 पूर्ण,
	.ddr = अणु
		/* Hynix HY5DU283222B DDR RAM */
		.chip_config = 0x303,
		.refresh = 0x3bd,
		.timing1 = 0x36320966,
		.timing2 = 0x1f,
		.tune_lane = 0,
		.initial_emrs = 2,
	पूर्ण,
	.gpio_init.initial_value = 0x1,
	.gpio_init.direction = 0x3,

	.gpio_audio_input = अणु .mask   = 0x3,
			      .tuner  = 0x1,
			      .linein = 0x2,
			      .radio  = 0x1 पूर्ण,
	.xceive_pin = 0,
	.pci_list = cx18_pci_gotview_dvd3,
	.i2c = &cx18_i2c_std,
पूर्ण;

/* ------------------------------------------------------------------------- */

/* Conexant Raptor PAL/SECAM: note that this card is analog only! */

अटल स्थिर काष्ठा cx18_card_pci_info cx18_pci_cnxt_raptor_pal[] = अणु
	अणु PCI_DEVICE_ID_CX23418, CX18_PCI_ID_CONEXANT, 0x0009 पूर्ण,
	अणु 0, 0, 0 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा cx18_card cx18_card_cnxt_raptor_pal = अणु
	.type = CX18_CARD_CNXT_RAPTOR_PAL,
	.name = "Conexant Raptor PAL/SECAM",
	.comment = "Analog TV capture supported\n",
	.v4l2_capabilities = CX18_CAP_ENCODER,
	.hw_audio_ctrl = CX18_HW_418_AV,
	.hw_muxer = CX18_HW_GPIO_MUX,
	.hw_all = CX18_HW_418_AV | CX18_HW_TUNER | CX18_HW_GPIO_MUX,
	.video_inमाला_दो = अणु
		अणु CX18_CARD_INPUT_VID_TUNER,  0, CX18_AV_COMPOSITE2 पूर्ण,
		अणु CX18_CARD_INPUT_SVIDEO1,    1,
			CX18_AV_SVIDEO_LUMA3 | CX18_AV_SVIDEO_CHROMA4 पूर्ण,
		अणु CX18_CARD_INPUT_COMPOSITE1, 1, CX18_AV_COMPOSITE1 पूर्ण,
		अणु CX18_CARD_INPUT_SVIDEO2,    2,
			CX18_AV_SVIDEO_LUMA7 | CX18_AV_SVIDEO_CHROMA8 पूर्ण,
		अणु CX18_CARD_INPUT_COMPOSITE2, 2, CX18_AV_COMPOSITE6 पूर्ण,
	पूर्ण,
	.audio_inमाला_दो = अणु
		अणु CX18_CARD_INPUT_AUD_TUNER, CX18_AV_AUDIO5,	    0 पूर्ण,
		अणु CX18_CARD_INPUT_LINE_IN1,  CX18_AV_AUDIO_SERIAL1, 1 पूर्ण,
		अणु CX18_CARD_INPUT_LINE_IN2,  CX18_AV_AUDIO_SERIAL2, 1 पूर्ण,
	पूर्ण,
	.tuners = अणु
		अणु .std = V4L2_STD_PAL_SECAM, .tuner = TUNER_PHILIPS_FM1216ME_MK3 पूर्ण,
	पूर्ण,
	.radio_input = अणु CX18_CARD_INPUT_AUD_TUNER, CX18_AV_AUDIO_SERIAL1, 2 पूर्ण,
	.ddr = अणु
		/* MT 46V16M16 memory */
		.chip_config = 0x50306,
		.refresh = 0x753,
		.timing1 = 0x33220953,
		.timing2 = 0x09,
		.tune_lane = 0,
		.initial_emrs = 0,
	पूर्ण,
	.gpio_init.initial_value = 0x1002,
	.gpio_init.direction = 0xf002,
	.gpio_audio_input = अणु .mask   = 0xf002,
			      .tuner  = 0x1002,   /* LED D1  Tuner AF  */
			      .linein = 0x2000,   /* LED D2  Line In 1 */
			      .radio  = 0x4002 पूर्ण, /* LED D3  Tuner AF  */
	.pci_list = cx18_pci_cnxt_raptor_pal,
	.i2c = &cx18_i2c_std,
पूर्ण;

/* ------------------------------------------------------------------------- */

/* Toshiba Qosmio laptop पूर्णांकernal DVB-T/Analog Hybrid Tuner */

अटल स्थिर काष्ठा cx18_card_pci_info cx18_pci_toshiba_qosmio_dvbt[] = अणु
	अणु PCI_DEVICE_ID_CX23418, CX18_PCI_ID_TOSHIBA, 0x0110 पूर्ण,
	अणु 0, 0, 0 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा cx18_card cx18_card_toshiba_qosmio_dvbt = अणु
	.type = CX18_CARD_TOSHIBA_QOSMIO_DVBT,
	.name = "Toshiba Qosmio DVB-T/Analog",
	.comment = "Experimenters and photos needed for device to work well.\n"
		  "\tTo help, mail the linux-media list (www.linuxtv.org).\n",
	.v4l2_capabilities = CX18_CAP_ENCODER,
	.hw_audio_ctrl = CX18_HW_418_AV,
	.hw_all = CX18_HW_418_AV | CX18_HW_TUNER | CX18_HW_GPIO_RESET_CTRL,
	.video_inमाला_दो = अणु
		अणु CX18_CARD_INPUT_VID_TUNER,  0, CX18_AV_COMPOSITE6 पूर्ण,
		अणु CX18_CARD_INPUT_SVIDEO1,    1,
			CX18_AV_SVIDEO_LUMA3 | CX18_AV_SVIDEO_CHROMA4 पूर्ण,
		अणु CX18_CARD_INPUT_COMPOSITE1, 1, CX18_AV_COMPOSITE1 पूर्ण,
	पूर्ण,
	.audio_inमाला_दो = अणु
		अणु CX18_CARD_INPUT_AUD_TUNER, CX18_AV_AUDIO5,	    0 पूर्ण,
		अणु CX18_CARD_INPUT_LINE_IN1,  CX18_AV_AUDIO_SERIAL1, 1 पूर्ण,
	पूर्ण,
	.tuners = अणु
		अणु .std = V4L2_STD_ALL, .tuner = TUNER_XC2028 पूर्ण,
	पूर्ण,
	.ddr = अणु
		.chip_config = 0x202,
		.refresh = 0x3bb,
		.timing1 = 0x33320a63,
		.timing2 = 0x0a,
		.tune_lane = 0,
		.initial_emrs = 0x42,
	पूर्ण,
	.xceive_pin = 15,
	.pci_list = cx18_pci_toshiba_qosmio_dvbt,
	.i2c = &cx18_i2c_std,
पूर्ण;

/* ------------------------------------------------------------------------- */

/* Leadtek WinFast PVR2100 */

अटल स्थिर काष्ठा cx18_card_pci_info cx18_pci_leadtek_pvr2100[] = अणु
	अणु PCI_DEVICE_ID_CX23418, CX18_PCI_ID_LEADTEK, 0x6f27 पूर्ण, /* PVR2100   */
	अणु 0, 0, 0 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा cx18_card cx18_card_leadtek_pvr2100 = अणु
	.type = CX18_CARD_LEADTEK_PVR2100,
	.name = "Leadtek WinFast PVR2100",
	.comment = "Experimenters and photos needed for device to work well.\n"
		  "\tTo help, mail the linux-media list (www.linuxtv.org).\n",
	.v4l2_capabilities = CX18_CAP_ENCODER,
	.hw_audio_ctrl = CX18_HW_418_AV,
	.hw_muxer = CX18_HW_GPIO_MUX,
	.hw_all = CX18_HW_418_AV | CX18_HW_TUNER | CX18_HW_GPIO_MUX |
		  CX18_HW_GPIO_RESET_CTRL,
	.video_inमाला_दो = अणु
		अणु CX18_CARD_INPUT_VID_TUNER,  0, CX18_AV_COMPOSITE2 पूर्ण,
		अणु CX18_CARD_INPUT_SVIDEO1,    1,
			CX18_AV_SVIDEO_LUMA3 | CX18_AV_SVIDEO_CHROMA4 पूर्ण,
		अणु CX18_CARD_INPUT_COMPOSITE1, 1, CX18_AV_COMPOSITE7 पूर्ण,
		अणु CX18_CARD_INPUT_COMPONENT1, 1, CX18_AV_COMPONENT1 पूर्ण,
	पूर्ण,
	.audio_inमाला_दो = अणु
		अणु CX18_CARD_INPUT_AUD_TUNER, CX18_AV_AUDIO5,	    0 पूर्ण,
		अणु CX18_CARD_INPUT_LINE_IN1,  CX18_AV_AUDIO_SERIAL1, 1 पूर्ण,
	पूर्ण,
	.tuners = अणु
		/* XC2028 tuner */
		अणु .std = V4L2_STD_ALL, .tuner = TUNER_XC2028 पूर्ण,
	पूर्ण,
	.radio_input = अणु CX18_CARD_INPUT_AUD_TUNER, CX18_AV_AUDIO5, 2 पूर्ण,
	.ddr = अणु
		/* Poपूर्णांकer to proper DDR config values provided by Terry Wu */
		.chip_config = 0x303,
		.refresh = 0x3bb,
		.timing1 = 0x24220e83,
		.timing2 = 0x1f,
		.tune_lane = 0,
		.initial_emrs = 0x2,
	पूर्ण,
	.gpio_init.initial_value = 0x6,
	.gpio_init.direction = 0x7,
	.gpio_audio_input = अणु .mask   = 0x7,
			      .tuner  = 0x6, .linein = 0x2, .radio  = 0x2 पूर्ण,
	.xceive_pin = 1,
	.pci_list = cx18_pci_leadtek_pvr2100,
	.i2c = &cx18_i2c_std,
पूर्ण;

/* ------------------------------------------------------------------------- */

/* Leadtek WinFast DVR3100 H */

अटल स्थिर काष्ठा cx18_card_pci_info cx18_pci_leadtek_dvr3100h[] = अणु
	अणु PCI_DEVICE_ID_CX23418, CX18_PCI_ID_LEADTEK, 0x6690 पूर्ण, /* DVR3100 H */
	अणु 0, 0, 0 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा cx18_card cx18_card_leadtek_dvr3100h = अणु
	.type = CX18_CARD_LEADTEK_DVR3100H,
	.name = "Leadtek WinFast DVR3100 H",
	.comment = "Simultaneous DVB-T and Analog capture supported,\n"
		  "\texcept when capturing Analog from the antenna input.\n",
	.v4l2_capabilities = CX18_CAP_ENCODER,
	.hw_audio_ctrl = CX18_HW_418_AV,
	.hw_muxer = CX18_HW_GPIO_MUX,
	.hw_all = CX18_HW_418_AV | CX18_HW_TUNER | CX18_HW_GPIO_MUX |
		  CX18_HW_DVB | CX18_HW_GPIO_RESET_CTRL,
	.video_inमाला_दो = अणु
		अणु CX18_CARD_INPUT_VID_TUNER,  0, CX18_AV_COMPOSITE2 पूर्ण,
		अणु CX18_CARD_INPUT_SVIDEO1,    1,
			CX18_AV_SVIDEO_LUMA3 | CX18_AV_SVIDEO_CHROMA4 पूर्ण,
		अणु CX18_CARD_INPUT_COMPOSITE1, 1, CX18_AV_COMPOSITE7 पूर्ण,
		अणु CX18_CARD_INPUT_COMPONENT1, 1, CX18_AV_COMPONENT1 पूर्ण,
	पूर्ण,
	.audio_inमाला_दो = अणु
		अणु CX18_CARD_INPUT_AUD_TUNER, CX18_AV_AUDIO5,	    0 पूर्ण,
		अणु CX18_CARD_INPUT_LINE_IN1,  CX18_AV_AUDIO_SERIAL1, 1 पूर्ण,
	पूर्ण,
	.tuners = अणु
		/* XC3028 tuner */
		अणु .std = V4L2_STD_ALL, .tuner = TUNER_XC2028 पूर्ण,
	पूर्ण,
	.radio_input = अणु CX18_CARD_INPUT_AUD_TUNER, CX18_AV_AUDIO5, 2 पूर्ण,
	.ddr = अणु
		/* Poपूर्णांकer to proper DDR config values provided by Terry Wu */
		.chip_config = 0x303,
		.refresh = 0x3bb,
		.timing1 = 0x24220e83,
		.timing2 = 0x1f,
		.tune_lane = 0,
		.initial_emrs = 0x2,
	पूर्ण,
	.gpio_init.initial_value = 0x6,
	.gpio_init.direction = 0x7,
	.gpio_audio_input = अणु .mask   = 0x7,
			      .tuner  = 0x6, .linein = 0x2, .radio  = 0x2 पूर्ण,
	.xceive_pin = 1,
	.pci_list = cx18_pci_leadtek_dvr3100h,
	.i2c = &cx18_i2c_std,
पूर्ण;

/* ------------------------------------------------------------------------- */

अटल स्थिर काष्ठा cx18_card *cx18_card_list[] = अणु
	&cx18_card_hvr1600_esmt,
	&cx18_card_hvr1600_samsung,
	&cx18_card_h900,
	&cx18_card_mpc718,
	&cx18_card_cnxt_raptor_pal,
	&cx18_card_toshiba_qosmio_dvbt,
	&cx18_card_leadtek_pvr2100,
	&cx18_card_leadtek_dvr3100h,
	&cx18_card_gotview_dvd3,
	&cx18_card_hvr1600_s5h1411
पूर्ण;

स्थिर काष्ठा cx18_card *cx18_get_card(u16 index)
अणु
	अगर (index >= ARRAY_SIZE(cx18_card_list))
		वापस शून्य;
	वापस cx18_card_list[index];
पूर्ण

पूर्णांक cx18_get_input(काष्ठा cx18 *cx, u16 index, काष्ठा v4l2_input *input)
अणु
	स्थिर काष्ठा cx18_card_video_input *card_input =
		cx->card->video_inमाला_दो + index;
	अटल स्थिर अक्षर * स्थिर input_strs[] = अणु
		"Tuner 1",
		"S-Video 1",
		"S-Video 2",
		"Composite 1",
		"Composite 2",
		"Component 1"
	पूर्ण;

	अगर (index >= cx->nof_inमाला_दो)
		वापस -EINVAL;
	input->index = index;
	strscpy(input->name, input_strs[card_input->video_type - 1],
		माप(input->name));
	input->type = (card_input->video_type == CX18_CARD_INPUT_VID_TUNER ?
			V4L2_INPUT_TYPE_TUNER : V4L2_INPUT_TYPE_CAMERA);
	input->audioset = (1 << cx->nof_audio_inमाला_दो) - 1;
	input->std = (input->type == V4L2_INPUT_TYPE_TUNER) ?
				cx->tuner_std : V4L2_STD_ALL;
	वापस 0;
पूर्ण

पूर्णांक cx18_get_audio_input(काष्ठा cx18 *cx, u16 index, काष्ठा v4l2_audio *audio)
अणु
	स्थिर काष्ठा cx18_card_audio_input *aud_input =
		cx->card->audio_inमाला_दो + index;
	अटल स्थिर अक्षर * स्थिर input_strs[] = अणु
		"Tuner 1",
		"Line In 1",
		"Line In 2"
	पूर्ण;

	स_रखो(audio, 0, माप(*audio));
	अगर (index >= cx->nof_audio_inमाला_दो)
		वापस -EINVAL;
	strscpy(audio->name, input_strs[aud_input->audio_type - 1],
		माप(audio->name));
	audio->index = index;
	audio->capability = V4L2_AUDCAP_STEREO;
	वापस 0;
पूर्ण
