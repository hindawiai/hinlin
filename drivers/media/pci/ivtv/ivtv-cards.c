<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    Functions to query card hardware
    Copyright (C) 2003-2004  Kevin Thayer <nufan_wfk at yahoo.com>
    Copyright (C) 2005-2007  Hans Verkuil <hverkuil@xs4all.nl>

 */

#समावेश "ivtv-driver.h"
#समावेश "ivtv-cards.h"
#समावेश "ivtv-i2c.h"

#समावेश <media/drv-पूर्णांकf/msp3400.h>
#समावेश <media/i2c/m52790.h>
#समावेश <media/i2c/wm8775.h>
#समावेश <media/i2c/cs53l32a.h>
#समावेश <media/drv-पूर्णांकf/cx25840.h>
#समावेश <media/i2c/upd64031a.h>

#घोषणा MSP_TUNER  MSP_INPUT(MSP_IN_SCART1, MSP_IN_TUNER1, \
				MSP_DSP_IN_TUNER, MSP_DSP_IN_TUNER)
#घोषणा MSP_SCART1 MSP_INPUT(MSP_IN_SCART1, MSP_IN_TUNER1, \
				MSP_DSP_IN_SCART, MSP_DSP_IN_SCART)
#घोषणा MSP_SCART2 MSP_INPUT(MSP_IN_SCART2, MSP_IN_TUNER1, \
				MSP_DSP_IN_SCART, MSP_DSP_IN_SCART)
#घोषणा MSP_SCART3 MSP_INPUT(MSP_IN_SCART3, MSP_IN_TUNER1, \
				MSP_DSP_IN_SCART, MSP_DSP_IN_SCART)
#घोषणा MSP_MONO   MSP_INPUT(MSP_IN_MONO, MSP_IN_TUNER1, \
				MSP_DSP_IN_SCART, MSP_DSP_IN_SCART)

#घोषणा V4L2_STD_PAL_SECAM (V4L2_STD_PAL|V4L2_STD_SECAM)

/* usual i2c tuner addresses to probe */
अटल काष्ठा ivtv_card_tuner_i2c ivtv_i2c_std = अणु
	.radio = अणु I2C_CLIENT_END पूर्ण,
	.demod = अणु 0x43, I2C_CLIENT_END पूर्ण,
	.tv    = अणु 0x61, 0x60, I2C_CLIENT_END पूर्ण,
पूर्ण;

/* as above, but with possible radio tuner */
अटल काष्ठा ivtv_card_tuner_i2c ivtv_i2c_radio = अणु
	.radio = अणु 0x60, I2C_CLIENT_END पूर्ण,
	.demod = अणु 0x43, I2C_CLIENT_END पूर्ण,
	.tv    = अणु 0x61, I2C_CLIENT_END पूर्ण,
पूर्ण;

/* using the tda8290+75a combo */
अटल काष्ठा ivtv_card_tuner_i2c ivtv_i2c_tda8290 = अणु
	.radio = अणु I2C_CLIENT_END पूर्ण,
	.demod = अणु I2C_CLIENT_END पूर्ण,
	.tv    = अणु 0x4b, I2C_CLIENT_END पूर्ण,
पूर्ण;

/********************** card configuration *******************************/

/* Please add new PCI IDs to: https://pci-ids.ucw.cz/
   This keeps the PCI ID database up to date. Note that the entries
   must be added under venकरोr 0x4444 (Conexant) as subप्रणाली IDs.
   New venकरोr IDs should still be added to the venकरोr ID list. */

/* Hauppauge PVR-250 cards */

/* Note: क्रम Hauppauge cards the tveeprom inक्रमmation is used instead of PCI IDs */
अटल स्थिर काष्ठा ivtv_card ivtv_card_pvr250 = अणु
	.type = IVTV_CARD_PVR_250,
	.name = "Hauppauge WinTV PVR-250",
	.v4l2_capabilities = IVTV_CAP_ENCODER,
	.hw_video = IVTV_HW_SAA7115,
	.hw_audio = IVTV_HW_MSP34XX,
	.hw_audio_ctrl = IVTV_HW_MSP34XX,
	.hw_all = IVTV_HW_MSP34XX | IVTV_HW_SAA7115 |
		  IVTV_HW_TVEEPROM | IVTV_HW_TUNER,
	.video_inमाला_दो = अणु
		अणु IVTV_CARD_INPUT_VID_TUNER,  0, IVTV_SAA71XX_COMPOSITE4 पूर्ण,
		अणु IVTV_CARD_INPUT_SVIDEO1,    1, IVTV_SAA71XX_SVIDEO0    पूर्ण,
		अणु IVTV_CARD_INPUT_COMPOSITE1, 1, IVTV_SAA71XX_COMPOSITE0 पूर्ण,
		अणु IVTV_CARD_INPUT_SVIDEO2,    2, IVTV_SAA71XX_SVIDEO1    पूर्ण,
		अणु IVTV_CARD_INPUT_COMPOSITE2, 2, IVTV_SAA71XX_COMPOSITE1 पूर्ण,
		अणु IVTV_CARD_INPUT_COMPOSITE3, 1, IVTV_SAA71XX_COMPOSITE5 पूर्ण,
	पूर्ण,
	.audio_inमाला_दो = अणु
		अणु IVTV_CARD_INPUT_AUD_TUNER,  MSP_TUNER  पूर्ण,
		अणु IVTV_CARD_INPUT_LINE_IN1,   MSP_SCART1 पूर्ण,
		अणु IVTV_CARD_INPUT_LINE_IN2,   MSP_SCART3 पूर्ण,
	पूर्ण,
	.radio_input = अणु IVTV_CARD_INPUT_AUD_TUNER, MSP_SCART2 पूर्ण,
	.i2c = &ivtv_i2c_std,
पूर्ण;

/* ------------------------------------------------------------------------- */

/* Hauppauge PVR-350 cards */

/* Outमाला_दो क्रम Hauppauge PVR350 cards */
अटल काष्ठा ivtv_card_output ivtv_pvr350_outमाला_दो[] = अणु
	अणु
		.name = "S-Video + Composite",
		.video_output = 0,
	पूर्ण, अणु
		.name = "Composite",
		.video_output = 1,
	पूर्ण, अणु
		.name = "S-Video",
		.video_output = 2,
	पूर्ण, अणु
		.name = "RGB",
		.video_output = 3,
	पूर्ण, अणु
		.name = "YUV C",
		.video_output = 4,
	पूर्ण, अणु
		.name = "YUV V",
		.video_output = 5,
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ivtv_card ivtv_card_pvr350 = अणु
	.type = IVTV_CARD_PVR_350,
	.name = "Hauppauge WinTV PVR-350",
	.v4l2_capabilities = IVTV_CAP_ENCODER | IVTV_CAP_DECODER,
	.video_outमाला_दो = ivtv_pvr350_outमाला_दो,
	.nof_outमाला_दो = ARRAY_SIZE(ivtv_pvr350_outमाला_दो),
	.hw_video = IVTV_HW_SAA7115,
	.hw_audio = IVTV_HW_MSP34XX,
	.hw_audio_ctrl = IVTV_HW_MSP34XX,
	.hw_all = IVTV_HW_MSP34XX | IVTV_HW_SAA7115 |
		  IVTV_HW_SAA7127 | IVTV_HW_TVEEPROM | IVTV_HW_TUNER |
		  IVTV_HW_I2C_IR_RX_HAUP_EXT | IVTV_HW_I2C_IR_RX_HAUP_INT,
	.video_inमाला_दो = अणु
		अणु IVTV_CARD_INPUT_VID_TUNER,  0, IVTV_SAA71XX_COMPOSITE4 पूर्ण,
		अणु IVTV_CARD_INPUT_SVIDEO1,    1, IVTV_SAA71XX_SVIDEO0    पूर्ण,
		अणु IVTV_CARD_INPUT_COMPOSITE1, 1, IVTV_SAA71XX_COMPOSITE0 पूर्ण,
		अणु IVTV_CARD_INPUT_SVIDEO2,    2, IVTV_SAA71XX_SVIDEO1    पूर्ण,
		अणु IVTV_CARD_INPUT_COMPOSITE2, 2, IVTV_SAA71XX_COMPOSITE1 पूर्ण,
		अणु IVTV_CARD_INPUT_COMPOSITE3, 1, IVTV_SAA71XX_COMPOSITE5 पूर्ण,
	पूर्ण,
	.audio_inमाला_दो = अणु
		अणु IVTV_CARD_INPUT_AUD_TUNER,  MSP_TUNER  पूर्ण,
		अणु IVTV_CARD_INPUT_LINE_IN1,   MSP_SCART1 पूर्ण,
		अणु IVTV_CARD_INPUT_LINE_IN2,   MSP_SCART3 पूर्ण,
	पूर्ण,
	.radio_input = अणु IVTV_CARD_INPUT_AUD_TUNER, MSP_SCART2 पूर्ण,
	.i2c = &ivtv_i2c_std,
पूर्ण;

/* PVR-350 V1 boards have a dअगरferent audio tuner input and use a
   saa7114 instead of a saa7115.
   Note that the info below comes from a pre-production model so it may
   not be correct. Especially the audio behaves strangely (mono only it seems) */
अटल स्थिर काष्ठा ivtv_card ivtv_card_pvr350_v1 = अणु
	.type = IVTV_CARD_PVR_350_V1,
	.name = "Hauppauge WinTV PVR-350 (V1)",
	.v4l2_capabilities = IVTV_CAP_ENCODER | IVTV_CAP_DECODER,
	.video_outमाला_दो = ivtv_pvr350_outमाला_दो,
	.nof_outमाला_दो = ARRAY_SIZE(ivtv_pvr350_outमाला_दो),
	.hw_video = IVTV_HW_SAA7114,
	.hw_audio = IVTV_HW_MSP34XX,
	.hw_audio_ctrl = IVTV_HW_MSP34XX,
	.hw_all = IVTV_HW_MSP34XX | IVTV_HW_SAA7114 |
		  IVTV_HW_SAA7127 | IVTV_HW_TVEEPROM | IVTV_HW_TUNER,
	.video_inमाला_दो = अणु
		अणु IVTV_CARD_INPUT_VID_TUNER,  0, IVTV_SAA71XX_COMPOSITE4 पूर्ण,
		अणु IVTV_CARD_INPUT_SVIDEO1,    1, IVTV_SAA71XX_SVIDEO0    पूर्ण,
		अणु IVTV_CARD_INPUT_COMPOSITE1, 1, IVTV_SAA71XX_COMPOSITE0 पूर्ण,
		अणु IVTV_CARD_INPUT_SVIDEO2,    2, IVTV_SAA71XX_SVIDEO1    पूर्ण,
		अणु IVTV_CARD_INPUT_COMPOSITE2, 2, IVTV_SAA71XX_COMPOSITE1 पूर्ण,
		अणु IVTV_CARD_INPUT_COMPOSITE3, 1, IVTV_SAA71XX_COMPOSITE5 पूर्ण,
	पूर्ण,
	.audio_inमाला_दो = अणु
		अणु IVTV_CARD_INPUT_AUD_TUNER,  MSP_MONO   पूर्ण,
		अणु IVTV_CARD_INPUT_LINE_IN1,   MSP_SCART1 पूर्ण,
		अणु IVTV_CARD_INPUT_LINE_IN2,   MSP_SCART3 पूर्ण,
	पूर्ण,
	.radio_input = अणु IVTV_CARD_INPUT_AUD_TUNER, MSP_SCART2 पूर्ण,
	.i2c = &ivtv_i2c_std,
पूर्ण;

/* ------------------------------------------------------------------------- */

/* Hauppauge PVR-150/PVR-500 cards */

अटल स्थिर काष्ठा ivtv_card ivtv_card_pvr150 = अणु
	.type = IVTV_CARD_PVR_150,
	.name = "Hauppauge WinTV PVR-150",
	.v4l2_capabilities = IVTV_CAP_ENCODER,
	.hw_video = IVTV_HW_CX25840,
	.hw_audio = IVTV_HW_CX25840,
	.hw_audio_ctrl = IVTV_HW_CX25840,
	.hw_muxer = IVTV_HW_WM8775,
	.hw_all = IVTV_HW_WM8775 | IVTV_HW_CX25840 |
		  IVTV_HW_TVEEPROM | IVTV_HW_TUNER |
		  IVTV_HW_I2C_IR_RX_HAUP_EXT | IVTV_HW_I2C_IR_RX_HAUP_INT |
		  IVTV_HW_Z8F0811_IR_HAUP,
	.video_inमाला_दो = अणु
		अणु IVTV_CARD_INPUT_VID_TUNER,  0, CX25840_COMPOSITE7 पूर्ण,
		अणु IVTV_CARD_INPUT_SVIDEO1,    1, CX25840_SVIDEO1    पूर्ण,
		अणु IVTV_CARD_INPUT_COMPOSITE1, 1, CX25840_COMPOSITE3 पूर्ण,
		अणु IVTV_CARD_INPUT_SVIDEO2,    2, CX25840_SVIDEO2    पूर्ण,
		अणु IVTV_CARD_INPUT_COMPOSITE2, 2, CX25840_COMPOSITE4 पूर्ण,
	पूर्ण,
	.audio_inमाला_दो = अणु
		अणु IVTV_CARD_INPUT_AUD_TUNER,
		  CX25840_AUDIO8, WM8775_AIN2 पूर्ण,
		अणु IVTV_CARD_INPUT_LINE_IN1,
		  CX25840_AUDIO_SERIAL, WM8775_AIN2 पूर्ण,
		अणु IVTV_CARD_INPUT_LINE_IN2,
		  CX25840_AUDIO_SERIAL, WM8775_AIN3 पूर्ण,
	पूर्ण,
	.radio_input = अणु IVTV_CARD_INPUT_AUD_TUNER,
			 CX25840_AUDIO_SERIAL, WM8775_AIN4 पूर्ण,
	/* apparently needed क्रम the IR blaster */
	.gpio_init = अणु .direction = 0x1f01, .initial_value = 0x26f3 पूर्ण,
	.i2c = &ivtv_i2c_std,
पूर्ण;

/* ------------------------------------------------------------------------- */

/* AVerMedia M179 cards */

अटल स्थिर काष्ठा ivtv_card_pci_info ivtv_pci_m179[] = अणु
	अणु PCI_DEVICE_ID_IVTV15, IVTV_PCI_ID_AVERMEDIA, 0xa3cf पूर्ण,
	अणु PCI_DEVICE_ID_IVTV15, IVTV_PCI_ID_AVERMEDIA, 0xa3ce पूर्ण,
	अणु 0, 0, 0 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ivtv_card ivtv_card_m179 = अणु
	.type = IVTV_CARD_M179,
	.name = "AVerMedia M179",
	.v4l2_capabilities = IVTV_CAP_ENCODER,
	.hw_video = IVTV_HW_SAA7114,
	.hw_audio = IVTV_HW_GPIO,
	.hw_audio_ctrl = IVTV_HW_GPIO,
	.hw_all = IVTV_HW_GPIO | IVTV_HW_SAA7114 | IVTV_HW_TUNER,
	.video_inमाला_दो = अणु
		अणु IVTV_CARD_INPUT_VID_TUNER,  0, IVTV_SAA71XX_COMPOSITE4 पूर्ण,
		अणु IVTV_CARD_INPUT_SVIDEO1,    1, IVTV_SAA71XX_SVIDEO0    पूर्ण,
		अणु IVTV_CARD_INPUT_COMPOSITE1, 1, IVTV_SAA71XX_COMPOSITE3 पूर्ण,
	पूर्ण,
	.audio_inमाला_दो = अणु
		अणु IVTV_CARD_INPUT_AUD_TUNER,  IVTV_GPIO_TUNER   पूर्ण,
		अणु IVTV_CARD_INPUT_LINE_IN1,   IVTV_GPIO_LINE_IN पूर्ण,
	पूर्ण,
	.gpio_init = अणु .direction = 0xe380, .initial_value = 0x8290 पूर्ण,
	.gpio_audio_input  = अणु .mask = 0x8040, .tuner  = 0x8000, .linein = 0x0000 पूर्ण,
	.gpio_audio_mute   = अणु .mask = 0x2000, .mute   = 0x2000 पूर्ण,
	.gpio_audio_mode   = अणु .mask = 0x4300, .mono   = 0x4000, .stereo = 0x0200,
			      .lang1 = 0x0200, .lang2  = 0x0100, .both   = 0x0000 पूर्ण,
	.gpio_audio_freq   = अणु .mask = 0x0018, .f32000 = 0x0000,
			     .f44100 = 0x0008, .f48000 = 0x0010 पूर्ण,
	.gpio_audio_detect = अणु .mask = 0x4000, .stereo = 0x0000 पूर्ण,
	.tuners = अणु
		/* As far as we know all M179 cards use this tuner */
		अणु .std = V4L2_STD_ALL, .tuner = TUNER_PHILIPS_NTSC पूर्ण,
	पूर्ण,
	.pci_list = ivtv_pci_m179,
	.i2c = &ivtv_i2c_std,
पूर्ण;

/* ------------------------------------------------------------------------- */

/* Yuan MPG600/Kuroutoshikou ITVC16-STVLP cards */

अटल स्थिर काष्ठा ivtv_card_pci_info ivtv_pci_mpg600[] = अणु
	अणु PCI_DEVICE_ID_IVTV16, IVTV_PCI_ID_YUAN1, 0xfff3 पूर्ण,
	अणु PCI_DEVICE_ID_IVTV16, IVTV_PCI_ID_YUAN1, 0xffff पूर्ण,
	अणु 0, 0, 0 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ivtv_card ivtv_card_mpg600 = अणु
	.type = IVTV_CARD_MPG600,
	.name = "Yuan MPG600, Kuroutoshikou ITVC16-STVLP",
	.v4l2_capabilities = IVTV_CAP_ENCODER,
	.hw_video = IVTV_HW_SAA7115,
	.hw_audio = IVTV_HW_GPIO,
	.hw_audio_ctrl = IVTV_HW_GPIO,
	.hw_all = IVTV_HW_GPIO | IVTV_HW_SAA7115 | IVTV_HW_TUNER,
	.video_inमाला_दो = अणु
		अणु IVTV_CARD_INPUT_VID_TUNER,  0, IVTV_SAA71XX_COMPOSITE4 पूर्ण,
		अणु IVTV_CARD_INPUT_SVIDEO1,    1, IVTV_SAA71XX_SVIDEO0    पूर्ण,
		अणु IVTV_CARD_INPUT_COMPOSITE1, 1, IVTV_SAA71XX_COMPOSITE3 पूर्ण,
	पूर्ण,
	.audio_inमाला_दो = अणु
		अणु IVTV_CARD_INPUT_AUD_TUNER,  IVTV_GPIO_TUNER   पूर्ण,
		अणु IVTV_CARD_INPUT_LINE_IN1,   IVTV_GPIO_LINE_IN पूर्ण,
	पूर्ण,
	.gpio_init = अणु .direction = 0x3080, .initial_value = 0x0004 पूर्ण,
	.gpio_audio_input  = अणु .mask = 0x3000, .tuner  = 0x0000, .linein = 0x2000 पूर्ण,
	.gpio_audio_mute   = अणु .mask = 0x0001, .mute   = 0x0001 पूर्ण,
	.gpio_audio_mode   = अणु .mask = 0x000e, .mono   = 0x0006, .stereo = 0x0004,
			      .lang1 = 0x0004, .lang2  = 0x0000, .both   = 0x0008 पूर्ण,
	.gpio_audio_detect = अणु .mask = 0x0900, .stereo = 0x0100 पूर्ण,
	.tuners = अणु
		/* The PAL tuner is confirmed */
		अणु .std = V4L2_STD_PAL_SECAM, .tuner = TUNER_PHILIPS_FQ1216ME पूर्ण,
		अणु .std = V4L2_STD_ALL, .tuner = TUNER_PHILIPS_FQ1286 पूर्ण,
	पूर्ण,
	.pci_list = ivtv_pci_mpg600,
	.i2c = &ivtv_i2c_std,
पूर्ण;

/* ------------------------------------------------------------------------- */

/* Yuan MPG160/Kuroutoshikou ITVC15-STVLP cards */

अटल स्थिर काष्ठा ivtv_card_pci_info ivtv_pci_mpg160[] = अणु
	अणु PCI_DEVICE_ID_IVTV15, IVTV_PCI_ID_YUAN1, 0 पूर्ण,
	अणु PCI_DEVICE_ID_IVTV15, IVTV_PCI_ID_IODATA, 0x40a0 पूर्ण,
	अणु 0, 0, 0 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ivtv_card ivtv_card_mpg160 = अणु
	.type = IVTV_CARD_MPG160,
	.name = "YUAN MPG160, Kuroutoshikou ITVC15-STVLP, I/O Data GV-M2TV/PCI",
	.v4l2_capabilities = IVTV_CAP_ENCODER,
	.hw_video = IVTV_HW_SAA7114,
	.hw_audio = IVTV_HW_GPIO,
	.hw_audio_ctrl = IVTV_HW_GPIO,
	.hw_all = IVTV_HW_GPIO | IVTV_HW_SAA7114 | IVTV_HW_TUNER,
	.video_inमाला_दो = अणु
		अणु IVTV_CARD_INPUT_VID_TUNER,  0, IVTV_SAA71XX_COMPOSITE4 पूर्ण,
		अणु IVTV_CARD_INPUT_SVIDEO1,    1, IVTV_SAA71XX_SVIDEO0    पूर्ण,
		अणु IVTV_CARD_INPUT_COMPOSITE1, 1, IVTV_SAA71XX_COMPOSITE3 पूर्ण,
	पूर्ण,
	.audio_inमाला_दो = अणु
		अणु IVTV_CARD_INPUT_AUD_TUNER,  IVTV_GPIO_TUNER   पूर्ण,
		अणु IVTV_CARD_INPUT_LINE_IN1,   IVTV_GPIO_LINE_IN पूर्ण,
	पूर्ण,
	.gpio_init = अणु .direction = 0x7080, .initial_value = 0x400c पूर्ण,
	.gpio_audio_input  = अणु .mask = 0x3000, .tuner  = 0x0000, .linein = 0x2000 पूर्ण,
	.gpio_audio_mute   = अणु .mask = 0x0001, .mute   = 0x0001 पूर्ण,
	.gpio_audio_mode   = अणु .mask = 0x000e, .mono   = 0x0006, .stereo = 0x0004,
			      .lang1 = 0x0004, .lang2  = 0x0000, .both   = 0x0008 पूर्ण,
	.gpio_audio_detect = अणु .mask = 0x0900, .stereo = 0x0100 पूर्ण,
	.tuners = अणु
		अणु .std = V4L2_STD_PAL_SECAM, .tuner = TUNER_PHILIPS_FQ1216ME पूर्ण,
		अणु .std = V4L2_STD_ALL, .tuner = TUNER_PHILIPS_FQ1286 पूर्ण,
	पूर्ण,
	.pci_list = ivtv_pci_mpg160,
	.i2c = &ivtv_i2c_std,
पूर्ण;

/* ------------------------------------------------------------------------- */

/* Yuan PG600/Diamond PVR-550 cards */

अटल स्थिर काष्ठा ivtv_card_pci_info ivtv_pci_pg600[] = अणु
	अणु PCI_DEVICE_ID_IVTV16, IVTV_PCI_ID_DIAMONDMM, 0x0070 पूर्ण,
	अणु PCI_DEVICE_ID_IVTV16, IVTV_PCI_ID_YUAN3,     0x0600 पूर्ण,
	अणु 0, 0, 0 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ivtv_card ivtv_card_pg600 = अणु
	.type = IVTV_CARD_PG600,
	.name = "Yuan PG600, Diamond PVR-550",
	.v4l2_capabilities = IVTV_CAP_ENCODER,
	.hw_video = IVTV_HW_CX25840,
	.hw_audio = IVTV_HW_CX25840,
	.hw_audio_ctrl = IVTV_HW_CX25840,
	.hw_all = IVTV_HW_CX25840 | IVTV_HW_TUNER,
	.video_inमाला_दो = अणु
		अणु IVTV_CARD_INPUT_VID_TUNER,  0, CX25840_COMPOSITE2 पूर्ण,
		अणु IVTV_CARD_INPUT_SVIDEO1,    1,
		  CX25840_SVIDEO_LUMA3 | CX25840_SVIDEO_CHROMA4 पूर्ण,
		अणु IVTV_CARD_INPUT_COMPOSITE1, 1, CX25840_COMPOSITE1 पूर्ण,
	पूर्ण,
	.audio_inमाला_दो = अणु
		अणु IVTV_CARD_INPUT_AUD_TUNER,  CX25840_AUDIO5       पूर्ण,
		अणु IVTV_CARD_INPUT_LINE_IN1,   CX25840_AUDIO_SERIAL पूर्ण,
	पूर्ण,
	.tuners = अणु
		अणु .std = V4L2_STD_PAL_SECAM, .tuner = TUNER_PHILIPS_FQ1216ME पूर्ण,
		अणु .std = V4L2_STD_ALL, .tuner = TUNER_PHILIPS_FQ1286 पूर्ण,
	पूर्ण,
	.pci_list = ivtv_pci_pg600,
	.i2c = &ivtv_i2c_std,
पूर्ण;

/* ------------------------------------------------------------------------- */

/* Adaptec VideOh! AVC-2410 card */

अटल स्थिर काष्ठा ivtv_card_pci_info ivtv_pci_avc2410[] = अणु
	अणु PCI_DEVICE_ID_IVTV16, IVTV_PCI_ID_ADAPTEC, 0x0093 पूर्ण,
	अणु 0, 0, 0 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ivtv_card ivtv_card_avc2410 = अणु
	.type = IVTV_CARD_AVC2410,
	.name = "Adaptec VideOh! AVC-2410",
	.v4l2_capabilities = IVTV_CAP_ENCODER,
	.hw_video = IVTV_HW_SAA7115,
	.hw_audio = IVTV_HW_MSP34XX,
	.hw_audio_ctrl = IVTV_HW_MSP34XX,
	.hw_muxer = IVTV_HW_CS53L32A,
	.hw_all = IVTV_HW_MSP34XX | IVTV_HW_CS53L32A |
		  IVTV_HW_SAA7115 | IVTV_HW_TUNER |
		  IVTV_HW_I2C_IR_RX_ADAPTEC,
	.video_inमाला_दो = अणु
		अणु IVTV_CARD_INPUT_VID_TUNER,  0, IVTV_SAA71XX_COMPOSITE4 पूर्ण,
		अणु IVTV_CARD_INPUT_SVIDEO1,    1, IVTV_SAA71XX_SVIDEO0    पूर्ण,
		अणु IVTV_CARD_INPUT_COMPOSITE1, 1, IVTV_SAA71XX_COMPOSITE3 पूर्ण,
	पूर्ण,
	.audio_inमाला_दो = अणु
		अणु IVTV_CARD_INPUT_AUD_TUNER,
		  MSP_TUNER, CS53L32A_IN0 पूर्ण,
		अणु IVTV_CARD_INPUT_LINE_IN1,
		  MSP_SCART1, CS53L32A_IN2 पूर्ण,
	पूर्ण,
	/* This card has no eeprom and in fact the Winकरोws driver relies
	   on the country/region setting of the user to decide which tuner
	   is available. */
	.tuners = अणु
		अणु .std = V4L2_STD_PAL_SECAM, .tuner = TUNER_PHILIPS_FM1216ME_MK3 पूर्ण,
		अणु .std = V4L2_STD_ALL - V4L2_STD_NTSC_M_JP,
			.tuner = TUNER_PHILIPS_FM1236_MK3 पूर्ण,
		अणु .std = V4L2_STD_NTSC_M_JP, .tuner = TUNER_PHILIPS_FQ1286 पूर्ण,
	पूर्ण,
	.pci_list = ivtv_pci_avc2410,
	.i2c = &ivtv_i2c_std,
पूर्ण;

/* ------------------------------------------------------------------------- */

/* Adaptec VideOh! AVC-2010 card */

अटल स्थिर काष्ठा ivtv_card_pci_info ivtv_pci_avc2010[] = अणु
	अणु PCI_DEVICE_ID_IVTV16, IVTV_PCI_ID_ADAPTEC, 0x0092 पूर्ण,
	अणु 0, 0, 0 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ivtv_card ivtv_card_avc2010 = अणु
	.type = IVTV_CARD_AVC2010,
	.name = "Adaptec VideOh! AVC-2010",
	.v4l2_capabilities = IVTV_CAP_ENCODER,
	.hw_video = IVTV_HW_SAA7115,
	.hw_audio = IVTV_HW_CS53L32A,
	.hw_audio_ctrl = IVTV_HW_CS53L32A,
	.hw_all = IVTV_HW_CS53L32A | IVTV_HW_SAA7115,
	.video_inमाला_दो = अणु
		अणु IVTV_CARD_INPUT_SVIDEO1,    0, IVTV_SAA71XX_SVIDEO0    पूर्ण,
		अणु IVTV_CARD_INPUT_COMPOSITE1, 0, IVTV_SAA71XX_COMPOSITE3 पूर्ण,
	पूर्ण,
	.audio_inमाला_दो = अणु
		अणु IVTV_CARD_INPUT_LINE_IN1,   CS53L32A_IN2 पूर्ण,
	पूर्ण,
	/* Does not have a tuner */
	.pci_list = ivtv_pci_avc2010,
पूर्ण;

/* ------------------------------------------------------------------------- */

/* Nagase Transgear 5000TV card */

अटल स्थिर काष्ठा ivtv_card_pci_info ivtv_pci_tg5000tv[] = अणु
	अणु PCI_DEVICE_ID_IVTV16, IVTV_PCI_ID_AVERMEDIA, 0xbfff पूर्ण,
	अणु 0, 0, 0 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ivtv_card ivtv_card_tg5000tv = अणु
	.type = IVTV_CARD_TG5000TV,
	.name = "Nagase Transgear 5000TV",
	.v4l2_capabilities = IVTV_CAP_ENCODER,
	.hw_video = IVTV_HW_SAA7114 | IVTV_HW_UPD64031A | IVTV_HW_UPD6408X |
	IVTV_HW_GPIO,
	.hw_audio = IVTV_HW_GPIO,
	.hw_audio_ctrl = IVTV_HW_GPIO,
	.hw_all = IVTV_HW_GPIO | IVTV_HW_SAA7114 | IVTV_HW_TUNER |
		  IVTV_HW_UPD64031A | IVTV_HW_UPD6408X,
	.video_inमाला_दो = अणु
		अणु IVTV_CARD_INPUT_VID_TUNER,  0, IVTV_SAA71XX_SVIDEO0 पूर्ण,
		अणु IVTV_CARD_INPUT_SVIDEO1,    1, IVTV_SAA71XX_SVIDEO2 पूर्ण,
		अणु IVTV_CARD_INPUT_COMPOSITE1, 1, IVTV_SAA71XX_SVIDEO2 पूर्ण,
	पूर्ण,
	.audio_inमाला_दो = अणु
		अणु IVTV_CARD_INPUT_AUD_TUNER,  IVTV_GPIO_TUNER   पूर्ण,
		अणु IVTV_CARD_INPUT_LINE_IN1,   IVTV_GPIO_LINE_IN पूर्ण,
	पूर्ण,
	.gr_config = UPD64031A_VERTICAL_EXTERNAL,
	.gpio_init = अणु .direction = 0xe080, .initial_value = 0x8000 पूर्ण,
	.gpio_audio_input  = अणु .mask = 0x8080, .tuner  = 0x8000, .linein = 0x0080 पूर्ण,
	.gpio_audio_mute   = अणु .mask = 0x6000, .mute   = 0x6000 पूर्ण,
	.gpio_audio_mode   = अणु .mask = 0x4300, .mono   = 0x4000, .stereo = 0x0200,
			      .lang1 = 0x0300, .lang2  = 0x0000, .both   = 0x0200 पूर्ण,
	.gpio_video_input  = अणु .mask = 0x0030, .tuner  = 0x0000,
			  .composite = 0x0010, .svideo = 0x0020 पूर्ण,
	.tuners = अणु
		अणु .std = V4L2_STD_MN, .tuner = TUNER_PHILIPS_FQ1286 पूर्ण,
	पूर्ण,
	.pci_list = ivtv_pci_tg5000tv,
	.i2c = &ivtv_i2c_std,
पूर्ण;

/* ------------------------------------------------------------------------- */

/* AOpen VA2000MAX-SNT6 card */

अटल स्थिर काष्ठा ivtv_card_pci_info ivtv_pci_va2000[] = अणु
	अणु PCI_DEVICE_ID_IVTV16, 0, 0xff5f पूर्ण,
	अणु 0, 0, 0 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ivtv_card ivtv_card_va2000 = अणु
	.type = IVTV_CARD_VA2000MAX_SNT6,
	.name = "AOpen VA2000MAX-SNT6",
	.v4l2_capabilities = IVTV_CAP_ENCODER,
	.hw_video = IVTV_HW_SAA7115 | IVTV_HW_UPD6408X,
	.hw_audio = IVTV_HW_MSP34XX,
	.hw_audio_ctrl = IVTV_HW_MSP34XX,
	.hw_all = IVTV_HW_MSP34XX | IVTV_HW_SAA7115 |
		  IVTV_HW_UPD6408X | IVTV_HW_TUNER,
	.video_inमाला_दो = अणु
		अणु IVTV_CARD_INPUT_VID_TUNER, 0, IVTV_SAA71XX_SVIDEO0 पूर्ण,
	पूर्ण,
	.audio_inमाला_दो = अणु
		अणु IVTV_CARD_INPUT_AUD_TUNER, MSP_TUNER पूर्ण,
	पूर्ण,
	.tuners = अणु
		अणु .std = V4L2_STD_MN, .tuner = TUNER_PHILIPS_FQ1286 पूर्ण,
	पूर्ण,
	.pci_list = ivtv_pci_va2000,
	.i2c = &ivtv_i2c_std,
पूर्ण;

/* ------------------------------------------------------------------------- */

/* Yuan MPG600GR/Kuroutoshikou CX23416GYC-STVLP cards */

अटल स्थिर काष्ठा ivtv_card_pci_info ivtv_pci_cx23416gyc[] = अणु
	अणु PCI_DEVICE_ID_IVTV16, IVTV_PCI_ID_YUAN1, 0x0600 पूर्ण,
	अणु PCI_DEVICE_ID_IVTV16, IVTV_PCI_ID_YUAN4, 0x0600 पूर्ण,
	अणु PCI_DEVICE_ID_IVTV16, IVTV_PCI_ID_MELCO, 0x0523 पूर्ण,
	अणु 0, 0, 0 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ivtv_card ivtv_card_cx23416gyc = अणु
	.type = IVTV_CARD_CX23416GYC,
	.name = "Yuan MPG600GR, Kuroutoshikou CX23416GYC-STVLP",
	.v4l2_capabilities = IVTV_CAP_ENCODER,
	.hw_video = IVTV_HW_SAA717X | IVTV_HW_GPIO |
		IVTV_HW_UPD64031A | IVTV_HW_UPD6408X,
	.hw_audio = IVTV_HW_SAA717X,
	.hw_audio_ctrl = IVTV_HW_SAA717X,
	.hw_all = IVTV_HW_GPIO | IVTV_HW_SAA717X | IVTV_HW_TUNER |
		  IVTV_HW_UPD64031A | IVTV_HW_UPD6408X,
	.video_inमाला_दो = अणु
		अणु IVTV_CARD_INPUT_VID_TUNER,  0, IVTV_SAA71XX_SVIDEO3 |
						 IVTV_SAA717X_TUNER_FLAG पूर्ण,
		अणु IVTV_CARD_INPUT_SVIDEO1,    1, IVTV_SAA71XX_SVIDEO0 पूर्ण,
		अणु IVTV_CARD_INPUT_COMPOSITE1, 1, IVTV_SAA71XX_SVIDEO3 पूर्ण,
	पूर्ण,
	.audio_inमाला_दो = अणु
		अणु IVTV_CARD_INPUT_AUD_TUNER,  IVTV_SAA717X_IN2 पूर्ण,
		अणु IVTV_CARD_INPUT_LINE_IN1,   IVTV_SAA717X_IN0 पूर्ण,
	पूर्ण,
	.gr_config = UPD64031A_VERTICAL_EXTERNAL,
	.gpio_init = अणु .direction = 0xf880, .initial_value = 0x8800 पूर्ण,
	.gpio_video_input  = अणु .mask = 0x0020, .tuner  = 0x0000,
			       .composite = 0x0020, .svideo = 0x0020 पूर्ण,
	.gpio_audio_freq   = अणु .mask = 0xc000, .f32000 = 0x0000,
			     .f44100 = 0x4000, .f48000 = 0x8000 पूर्ण,
	.tuners = अणु
		अणु .std = V4L2_STD_PAL_SECAM, .tuner = TUNER_PHILIPS_FM1216ME_MK3 पूर्ण,
		अणु .std = V4L2_STD_ALL, .tuner = TUNER_PHILIPS_FM1236_MK3 पूर्ण,
	पूर्ण,
	.pci_list = ivtv_pci_cx23416gyc,
	.i2c = &ivtv_i2c_std,
पूर्ण;

अटल स्थिर काष्ठा ivtv_card ivtv_card_cx23416gyc_nogr = अणु
	.type = IVTV_CARD_CX23416GYC_NOGR,
	.name = "Yuan MPG600GR, Kuroutoshikou CX23416GYC-STVLP (no GR)",
	.v4l2_capabilities = IVTV_CAP_ENCODER,
	.hw_video = IVTV_HW_SAA717X | IVTV_HW_GPIO | IVTV_HW_UPD6408X,
	.hw_audio = IVTV_HW_SAA717X,
	.hw_audio_ctrl = IVTV_HW_SAA717X,
	.hw_all = IVTV_HW_GPIO | IVTV_HW_SAA717X | IVTV_HW_TUNER |
		  IVTV_HW_UPD6408X,
	.video_inमाला_दो = अणु
		अणु IVTV_CARD_INPUT_VID_TUNER,  0, IVTV_SAA71XX_COMPOSITE4 |
						 IVTV_SAA717X_TUNER_FLAG पूर्ण,
		अणु IVTV_CARD_INPUT_SVIDEO1,    1, IVTV_SAA71XX_SVIDEO0    पूर्ण,
		अणु IVTV_CARD_INPUT_COMPOSITE1, 1, IVTV_SAA71XX_COMPOSITE0 पूर्ण,
	पूर्ण,
	.audio_inमाला_दो = अणु
		अणु IVTV_CARD_INPUT_AUD_TUNER,  IVTV_SAA717X_IN2 पूर्ण,
		अणु IVTV_CARD_INPUT_LINE_IN1,   IVTV_SAA717X_IN0 पूर्ण,
	पूर्ण,
	.gpio_init = अणु .direction = 0xf880, .initial_value = 0x8800 पूर्ण,
	.gpio_video_input  = अणु .mask = 0x0020, .tuner  = 0x0000,
			       .composite = 0x0020, .svideo = 0x0020 पूर्ण,
	.gpio_audio_freq   = अणु .mask = 0xc000, .f32000 = 0x0000,
			     .f44100 = 0x4000, .f48000 = 0x8000 पूर्ण,
	.tuners = अणु
		अणु .std = V4L2_STD_PAL_SECAM, .tuner = TUNER_PHILIPS_FM1216ME_MK3 पूर्ण,
		अणु .std = V4L2_STD_ALL, .tuner = TUNER_PHILIPS_FM1236_MK3 पूर्ण,
	पूर्ण,
	.i2c = &ivtv_i2c_std,
पूर्ण;

अटल स्थिर काष्ठा ivtv_card ivtv_card_cx23416gyc_nogrycs = अणु
	.type = IVTV_CARD_CX23416GYC_NOGRYCS,
	.name = "Yuan MPG600GR, Kuroutoshikou CX23416GYC-STVLP (no GR/YCS)",
	.v4l2_capabilities = IVTV_CAP_ENCODER,
	.hw_video = IVTV_HW_SAA717X | IVTV_HW_GPIO,
	.hw_audio = IVTV_HW_SAA717X,
	.hw_audio_ctrl = IVTV_HW_SAA717X,
	.hw_all = IVTV_HW_GPIO | IVTV_HW_SAA717X | IVTV_HW_TUNER,
	.video_inमाला_दो = अणु
		अणु IVTV_CARD_INPUT_VID_TUNER,  0, IVTV_SAA71XX_COMPOSITE4 |
						 IVTV_SAA717X_TUNER_FLAG पूर्ण,
		अणु IVTV_CARD_INPUT_SVIDEO1,    1, IVTV_SAA71XX_SVIDEO0    पूर्ण,
		अणु IVTV_CARD_INPUT_COMPOSITE1, 1, IVTV_SAA71XX_COMPOSITE0 पूर्ण,
	पूर्ण,
	.audio_inमाला_दो = अणु
		अणु IVTV_CARD_INPUT_AUD_TUNER,  IVTV_SAA717X_IN2 पूर्ण,
		अणु IVTV_CARD_INPUT_LINE_IN1,   IVTV_SAA717X_IN0 पूर्ण,
	पूर्ण,
	.gpio_init = अणु .direction = 0xf880, .initial_value = 0x8800 पूर्ण,
	.gpio_video_input  = अणु .mask = 0x0020, .tuner  = 0x0000,
			       .composite = 0x0020, .svideo = 0x0020 पूर्ण,
	.gpio_audio_freq   = अणु .mask = 0xc000, .f32000 = 0x0000,
			     .f44100 = 0x4000, .f48000 = 0x8000 पूर्ण,
	.tuners = अणु
		अणु .std = V4L2_STD_PAL_SECAM, .tuner = TUNER_PHILIPS_FM1216ME_MK3 पूर्ण,
		अणु .std = V4L2_STD_ALL, .tuner = TUNER_PHILIPS_FM1236_MK3 पूर्ण,
	पूर्ण,
	.i2c = &ivtv_i2c_std,
पूर्ण;

/* ------------------------------------------------------------------------- */

/* I/O Data GV-MVP/RX & GV-MVP/RX2W (dual tuner) cards */

अटल स्थिर काष्ठा ivtv_card_pci_info ivtv_pci_gv_mvprx[] = अणु
	अणु PCI_DEVICE_ID_IVTV16, IVTV_PCI_ID_IODATA, 0xd01e पूर्ण,
	अणु PCI_DEVICE_ID_IVTV16, IVTV_PCI_ID_IODATA, 0xd038 पूर्ण, /* 2W unit #1 */
	अणु PCI_DEVICE_ID_IVTV16, IVTV_PCI_ID_IODATA, 0xd039 पूर्ण, /* 2W unit #2 */
	अणु 0, 0, 0 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ivtv_card ivtv_card_gv_mvprx = अणु
	.type = IVTV_CARD_GV_MVPRX,
	.name = "I/O Data GV-MVP/RX, GV-MVP/RX2W (dual tuner)",
	.v4l2_capabilities = IVTV_CAP_ENCODER,
	.hw_video = IVTV_HW_SAA7115 | IVTV_HW_UPD64031A | IVTV_HW_UPD6408X,
	.hw_audio = IVTV_HW_GPIO,
	.hw_audio_ctrl = IVTV_HW_WM8739,
	.hw_all = IVTV_HW_GPIO | IVTV_HW_SAA7115 | IVTV_HW_VP27SMPX |
		  IVTV_HW_TUNER | IVTV_HW_WM8739 |
		  IVTV_HW_UPD64031A | IVTV_HW_UPD6408X,
	.video_inमाला_दो = अणु
		अणु IVTV_CARD_INPUT_VID_TUNER,  0, IVTV_SAA71XX_SVIDEO0    पूर्ण,
		अणु IVTV_CARD_INPUT_SVIDEO1,    1, IVTV_SAA71XX_SVIDEO1    पूर्ण,
		अणु IVTV_CARD_INPUT_COMPOSITE1, 1, IVTV_SAA71XX_SVIDEO2    पूर्ण,
	पूर्ण,
	.audio_inमाला_दो = अणु
		अणु IVTV_CARD_INPUT_AUD_TUNER,  IVTV_GPIO_TUNER   पूर्ण,
		अणु IVTV_CARD_INPUT_LINE_IN1,   IVTV_GPIO_LINE_IN पूर्ण,
	पूर्ण,
	.gpio_init = अणु .direction = 0xc301, .initial_value = 0x0200 पूर्ण,
	.gpio_audio_input  = अणु .mask = 0xffff, .tuner  = 0x0200, .linein = 0x0300 पूर्ण,
	.tuners = अणु
		/* This card has the Panasonic VP27 tuner */
		अणु .std = V4L2_STD_MN, .tuner = TUNER_PANASONIC_VP27 पूर्ण,
	पूर्ण,
	.pci_list = ivtv_pci_gv_mvprx,
	.i2c = &ivtv_i2c_std,
पूर्ण;

/* ------------------------------------------------------------------------- */

/* I/O Data GV-MVP/RX2E card */

अटल स्थिर काष्ठा ivtv_card_pci_info ivtv_pci_gv_mvprx2e[] = अणु
	अणु PCI_DEVICE_ID_IVTV16, IVTV_PCI_ID_IODATA, 0xd025 पूर्ण,
	अणु0, 0, 0पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ivtv_card ivtv_card_gv_mvprx2e = अणु
	.type = IVTV_CARD_GV_MVPRX2E,
	.name = "I/O Data GV-MVP/RX2E",
	.v4l2_capabilities = IVTV_CAP_ENCODER,
	.hw_video = IVTV_HW_SAA7115,
	.hw_audio = IVTV_HW_GPIO,
	.hw_audio_ctrl = IVTV_HW_WM8739,
	.hw_all = IVTV_HW_GPIO | IVTV_HW_SAA7115 | IVTV_HW_TUNER |
		  IVTV_HW_VP27SMPX | IVTV_HW_WM8739,
	.video_inमाला_दो = अणु
		अणु IVTV_CARD_INPUT_VID_TUNER,  0, IVTV_SAA71XX_COMPOSITE4 पूर्ण,
		अणु IVTV_CARD_INPUT_SVIDEO1,    1, IVTV_SAA71XX_SVIDEO0    पूर्ण,
		अणु IVTV_CARD_INPUT_COMPOSITE1, 1, IVTV_SAA71XX_COMPOSITE3 पूर्ण,
	पूर्ण,
	.audio_inमाला_दो = अणु
		अणु IVTV_CARD_INPUT_AUD_TUNER,  IVTV_GPIO_TUNER   पूर्ण,
		अणु IVTV_CARD_INPUT_LINE_IN1,   IVTV_GPIO_LINE_IN पूर्ण,
	पूर्ण,
	.gpio_init = अणु .direction = 0xc301, .initial_value = 0x0200 पूर्ण,
	.gpio_audio_input  = अणु .mask = 0xffff, .tuner  = 0x0200, .linein = 0x0300 पूर्ण,
	.tuners = अणु
		/* This card has the Panasonic VP27 tuner */
		अणु .std = V4L2_STD_MN, .tuner = TUNER_PANASONIC_VP27 पूर्ण,
	पूर्ण,
	.pci_list = ivtv_pci_gv_mvprx2e,
	.i2c = &ivtv_i2c_std,
पूर्ण;

/* ------------------------------------------------------------------------- */

/* GotVIEW PCI DVD card */

अटल स्थिर काष्ठा ivtv_card_pci_info ivtv_pci_gotview_pci_dvd[] = अणु
	अणु PCI_DEVICE_ID_IVTV16, IVTV_PCI_ID_YUAN1, 0x0600 पूर्ण,
	अणु 0, 0, 0 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ivtv_card ivtv_card_gotview_pci_dvd = अणु
	.type = IVTV_CARD_GOTVIEW_PCI_DVD,
	.name = "GotView PCI DVD",
	.v4l2_capabilities = IVTV_CAP_ENCODER,
	.hw_video = IVTV_HW_SAA717X,
	.hw_audio = IVTV_HW_SAA717X,
	.hw_audio_ctrl = IVTV_HW_SAA717X,
	.hw_all = IVTV_HW_SAA717X | IVTV_HW_TUNER,
	.video_inमाला_दो = अणु
		अणु IVTV_CARD_INPUT_VID_TUNER,  0, IVTV_SAA71XX_COMPOSITE1 पूर्ण,  /* pin 116 */
		अणु IVTV_CARD_INPUT_SVIDEO1,    1, IVTV_SAA71XX_SVIDEO0 पूर्ण,     /* pin 114/109 */
		अणु IVTV_CARD_INPUT_COMPOSITE1, 1, IVTV_SAA71XX_COMPOSITE3 पूर्ण,  /* pin 118 */
	पूर्ण,
	.audio_inमाला_दो = अणु
		अणु IVTV_CARD_INPUT_AUD_TUNER,  IVTV_SAA717X_IN0 पूर्ण,
		अणु IVTV_CARD_INPUT_LINE_IN1,   IVTV_SAA717X_IN2 पूर्ण,
	पूर्ण,
	.gpio_init = अणु .direction = 0xf000, .initial_value = 0xA000 पूर्ण,
	.tuners = अणु
		/* This card has a Philips FQ1216ME MK3 tuner */
		अणु .std = V4L2_STD_PAL_SECAM, .tuner = TUNER_PHILIPS_FM1216ME_MK3 पूर्ण,
	पूर्ण,
	.pci_list = ivtv_pci_gotview_pci_dvd,
	.i2c = &ivtv_i2c_std,
पूर्ण;

/* ------------------------------------------------------------------------- */

/* GotVIEW PCI DVD2 Deluxe card */

अटल स्थिर काष्ठा ivtv_card_pci_info ivtv_pci_gotview_pci_dvd2[] = अणु
	अणु PCI_DEVICE_ID_IVTV16, IVTV_PCI_ID_GOTVIEW1, 0x0600 पूर्ण,
	अणु 0, 0, 0 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ivtv_card ivtv_card_gotview_pci_dvd2 = अणु
	.type = IVTV_CARD_GOTVIEW_PCI_DVD2,
	.name = "GotView PCI DVD2 Deluxe",
	.v4l2_capabilities = IVTV_CAP_ENCODER,
	.hw_video = IVTV_HW_CX25840,
	.hw_audio = IVTV_HW_CX25840,
	.hw_audio_ctrl = IVTV_HW_CX25840,
	.hw_muxer = IVTV_HW_GPIO,
	.hw_all = IVTV_HW_CX25840 | IVTV_HW_TUNER,
	.video_inमाला_दो = अणु
		अणु IVTV_CARD_INPUT_VID_TUNER,  0, CX25840_COMPOSITE2 पूर्ण,
		अणु IVTV_CARD_INPUT_SVIDEO1,    1,
		  CX25840_SVIDEO_LUMA3 | CX25840_SVIDEO_CHROMA4 पूर्ण,
		अणु IVTV_CARD_INPUT_COMPOSITE1, 1, CX25840_COMPOSITE1 पूर्ण,
	पूर्ण,
	.audio_inमाला_दो = अणु
		अणु IVTV_CARD_INPUT_AUD_TUNER,  CX25840_AUDIO5,       0 पूर्ण,
		अणु IVTV_CARD_INPUT_LINE_IN1,   CX25840_AUDIO_SERIAL, 1 पूर्ण,
	पूर्ण,
	.radio_input = अणु IVTV_CARD_INPUT_AUD_TUNER, CX25840_AUDIO_SERIAL, 2 पूर्ण,
	.gpio_init = अणु .direction = 0x0800, .initial_value = 0 पूर्ण,
	.gpio_audio_input  = अणु .mask = 0x0800, .tuner = 0, .linein = 0, .radio = 0x0800 पूर्ण,
	.tuners = अणु
		/* This card has a Philips FQ1216ME MK5 tuner */
		अणु .std = V4L2_STD_PAL_SECAM, .tuner = TUNER_PHILIPS_FM1216ME_MK3 पूर्ण,
	पूर्ण,
	.pci_list = ivtv_pci_gotview_pci_dvd2,
	.i2c = &ivtv_i2c_std,
पूर्ण;

/* ------------------------------------------------------------------------- */

/* Yuan MPC622 miniPCI card */

अटल स्थिर काष्ठा ivtv_card_pci_info ivtv_pci_yuan_mpc622[] = अणु
	अणु PCI_DEVICE_ID_IVTV16, IVTV_PCI_ID_YUAN2, 0xd998 पूर्ण,
	अणु 0, 0, 0 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ivtv_card ivtv_card_yuan_mpc622 = अणु
	.type = IVTV_CARD_YUAN_MPC622,
	.name = "Yuan MPC622",
	.v4l2_capabilities = IVTV_CAP_ENCODER,
	.hw_video = IVTV_HW_CX25840,
	.hw_audio = IVTV_HW_CX25840,
	.hw_audio_ctrl = IVTV_HW_CX25840,
	.hw_all = IVTV_HW_CX25840 | IVTV_HW_TUNER,
	.video_inमाला_दो = अणु
		अणु IVTV_CARD_INPUT_VID_TUNER,  0, CX25840_COMPOSITE2 पूर्ण,
		अणु IVTV_CARD_INPUT_SVIDEO1,    1,
		  CX25840_SVIDEO_LUMA3 | CX25840_SVIDEO_CHROMA4 पूर्ण,
		अणु IVTV_CARD_INPUT_COMPOSITE1, 1, CX25840_COMPOSITE1 पूर्ण,
	पूर्ण,
	.audio_inमाला_दो = अणु
		अणु IVTV_CARD_INPUT_AUD_TUNER,  CX25840_AUDIO5       पूर्ण,
		अणु IVTV_CARD_INPUT_LINE_IN1,   CX25840_AUDIO_SERIAL पूर्ण,
	पूर्ण,
	.gpio_init = अणु .direction = 0x00ff, .initial_value = 0x0002 पूर्ण,
	.tuners = अणु
		/* This card has the TDA8290/TDA8275 tuner chips */
		अणु .std = V4L2_STD_ALL, .tuner = TUNER_PHILIPS_TDA8290 पूर्ण,
	पूर्ण,
	.pci_list = ivtv_pci_yuan_mpc622,
	.i2c = &ivtv_i2c_tda8290,
पूर्ण;

/* ------------------------------------------------------------------------- */

/* DIGITAL COWBOY DCT-MTVP1 card */

अटल स्थिर काष्ठा ivtv_card_pci_info ivtv_pci_dcपंचांगvtvp1[] = अणु
	अणु PCI_DEVICE_ID_IVTV16, IVTV_PCI_ID_AVERMEDIA, 0xbfff पूर्ण,
	अणु 0, 0, 0 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ivtv_card ivtv_card_dcपंचांगvtvp1 = अणु
	.type = IVTV_CARD_DCTMTVP1,
	.name = "Digital Cowboy DCT-MTVP1",
	.v4l2_capabilities = IVTV_CAP_ENCODER,
	.hw_video = IVTV_HW_SAA7115 | IVTV_HW_UPD64031A | IVTV_HW_UPD6408X |
		IVTV_HW_GPIO,
	.hw_audio = IVTV_HW_GPIO,
	.hw_audio_ctrl = IVTV_HW_GPIO,
	.hw_all = IVTV_HW_GPIO | IVTV_HW_SAA7115 | IVTV_HW_TUNER |
		IVTV_HW_UPD64031A | IVTV_HW_UPD6408X,
	.video_inमाला_दो = अणु
		अणु IVTV_CARD_INPUT_VID_TUNER,  0, IVTV_SAA71XX_SVIDEO0    पूर्ण,
		अणु IVTV_CARD_INPUT_SVIDEO1,    1, IVTV_SAA71XX_SVIDEO2    पूर्ण,
		अणु IVTV_CARD_INPUT_COMPOSITE1, 1, IVTV_SAA71XX_SVIDEO2 पूर्ण,
	पूर्ण,
	.audio_inमाला_दो = अणु
		अणु IVTV_CARD_INPUT_AUD_TUNER,  IVTV_GPIO_TUNER   पूर्ण,
		अणु IVTV_CARD_INPUT_LINE_IN1,   IVTV_GPIO_LINE_IN पूर्ण,
	पूर्ण,
	.gpio_init = अणु .direction = 0xe080, .initial_value = 0x8000 पूर्ण,
	.gpio_audio_input  = अणु .mask = 0x8080, .tuner  = 0x8000, .linein = 0x0080 पूर्ण,
	.gpio_audio_mute   = अणु .mask = 0x6000, .mute   = 0x6000 पूर्ण,
	.gpio_audio_mode   = अणु .mask = 0x4300, .mono   = 0x4000, .stereo = 0x0200,
			      .lang1 = 0x0300, .lang2  = 0x0000, .both   = 0x0200 पूर्ण,
	.gpio_video_input  = अणु .mask = 0x0030, .tuner  = 0x0000,
			       .composite = 0x0010, .svideo = 0x0020पूर्ण,
	.tuners = अणु
		अणु .std = V4L2_STD_MN, .tuner = TUNER_PHILIPS_FQ1286 पूर्ण,
	पूर्ण,
	.pci_list = ivtv_pci_dcपंचांगvtvp1,
	.i2c = &ivtv_i2c_std,
पूर्ण;

/* ------------------------------------------------------------------------- */

/* Yuan PG600-2/GotView PCI DVD Lite cards */

अटल स्थिर काष्ठा ivtv_card_pci_info ivtv_pci_pg600v2[] = अणु
	अणु PCI_DEVICE_ID_IVTV16, IVTV_PCI_ID_YUAN3,     0x0600 पूर्ण,
	अणु PCI_DEVICE_ID_IVTV16, IVTV_PCI_ID_GOTVIEW2,  0x0600 पूर्ण,
	अणु 0, 0, 0 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ivtv_card ivtv_card_pg600v2 = अणु
	.type = IVTV_CARD_PG600V2,
	.name = "Yuan PG600-2, GotView PCI DVD Lite",
	.v4l2_capabilities = IVTV_CAP_ENCODER,
	.hw_video = IVTV_HW_CX25840,
	.hw_audio = IVTV_HW_CX25840,
	.hw_audio_ctrl = IVTV_HW_CX25840,
	.hw_all = IVTV_HW_CX25840 | IVTV_HW_TUNER,
	/* XC2028 support apparently works क्रम the Yuan, it's still
	   uncertain whether it also works with the GotView. */
	.video_inमाला_दो = अणु
		अणु IVTV_CARD_INPUT_VID_TUNER,  0, CX25840_COMPOSITE2 पूर्ण,
		अणु IVTV_CARD_INPUT_SVIDEO1,    1,
		  CX25840_SVIDEO_LUMA3 | CX25840_SVIDEO_CHROMA4 पूर्ण,
		अणु IVTV_CARD_INPUT_COMPOSITE1, 1, CX25840_COMPOSITE1 पूर्ण,
	पूर्ण,
	.audio_inमाला_दो = अणु
		अणु IVTV_CARD_INPUT_AUD_TUNER,  CX25840_AUDIO5       पूर्ण,
		अणु IVTV_CARD_INPUT_LINE_IN1,   CX25840_AUDIO_SERIAL पूर्ण,
	पूर्ण,
	.radio_input = अणु IVTV_CARD_INPUT_AUD_TUNER, CX25840_AUDIO5 पूर्ण,
	.xceive_pin = 12,
	.tuners = अणु
		अणु .std = V4L2_STD_ALL, .tuner = TUNER_XC2028 पूर्ण,
	पूर्ण,
	.pci_list = ivtv_pci_pg600v2,
	.i2c = &ivtv_i2c_std,
पूर्ण;

/* ------------------------------------------------------------------------- */

/* Club3D ZAP-TV1x01 cards */

अटल स्थिर काष्ठा ivtv_card_pci_info ivtv_pci_club3d[] = अणु
	अणु PCI_DEVICE_ID_IVTV16, IVTV_PCI_ID_YUAN3,     0x0600 पूर्ण,
	अणु 0, 0, 0 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ivtv_card ivtv_card_club3d = अणु
	.type = IVTV_CARD_CLUB3D,
	.name = "Club3D ZAP-TV1x01",
	.v4l2_capabilities = IVTV_CAP_ENCODER,
	.hw_video = IVTV_HW_CX25840,
	.hw_audio = IVTV_HW_CX25840,
	.hw_audio_ctrl = IVTV_HW_CX25840,
	.hw_all = IVTV_HW_CX25840 | IVTV_HW_TUNER,
	.video_inमाला_दो = अणु
		अणु IVTV_CARD_INPUT_VID_TUNER,  0, CX25840_COMPOSITE2 पूर्ण,
		अणु IVTV_CARD_INPUT_SVIDEO1,    1,
		  CX25840_SVIDEO_LUMA3 | CX25840_SVIDEO_CHROMA4 पूर्ण,
		अणु IVTV_CARD_INPUT_COMPOSITE1, 1, CX25840_COMPOSITE3 पूर्ण,
	पूर्ण,
	.audio_inमाला_दो = अणु
		अणु IVTV_CARD_INPUT_AUD_TUNER,  CX25840_AUDIO5       पूर्ण,
		अणु IVTV_CARD_INPUT_LINE_IN1,   CX25840_AUDIO_SERIAL पूर्ण,
	पूर्ण,
	.radio_input = अणु IVTV_CARD_INPUT_AUD_TUNER, CX25840_AUDIO5 पूर्ण,
	.xceive_pin = 12,
	.tuners = अणु
		अणु .std = V4L2_STD_ALL, .tuner = TUNER_XC2028 पूर्ण,
	पूर्ण,
	.pci_list = ivtv_pci_club3d,
	.i2c = &ivtv_i2c_std,
पूर्ण;

/* ------------------------------------------------------------------------- */

/* AVerTV MCE 116 Plus (M116) card */

अटल स्थिर काष्ठा ivtv_card_pci_info ivtv_pci_avertv_mce116[] = अणु
	अणु PCI_DEVICE_ID_IVTV16, IVTV_PCI_ID_AVERMEDIA, 0xc439 पूर्ण,
	अणु 0, 0, 0 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ivtv_card ivtv_card_avertv_mce116 = अणु
	.type = IVTV_CARD_AVERTV_MCE116,
	.name = "AVerTV MCE 116 Plus",
	.v4l2_capabilities = IVTV_CAP_ENCODER,
	.hw_video = IVTV_HW_CX25840,
	.hw_audio = IVTV_HW_CX25840,
	.hw_audio_ctrl = IVTV_HW_CX25840,
	.hw_all = IVTV_HW_CX25840 | IVTV_HW_TUNER | IVTV_HW_WM8739 |
		  IVTV_HW_I2C_IR_RX_AVER,
	.video_inमाला_दो = अणु
		अणु IVTV_CARD_INPUT_VID_TUNER,  0, CX25840_COMPOSITE2 पूर्ण,
		अणु IVTV_CARD_INPUT_SVIDEO1,    1, CX25840_SVIDEO3    पूर्ण,
		अणु IVTV_CARD_INPUT_COMPOSITE1, 1, CX25840_COMPOSITE1 पूर्ण,
	पूर्ण,
	.audio_inमाला_दो = अणु
		अणु IVTV_CARD_INPUT_AUD_TUNER,  CX25840_AUDIO5       पूर्ण,
		अणु IVTV_CARD_INPUT_LINE_IN1,   CX25840_AUDIO_SERIAL, 1 पूर्ण,
	पूर्ण,
	.radio_input = अणु IVTV_CARD_INPUT_AUD_TUNER,  CX25840_AUDIO5 पूर्ण,
	/* enable line-in */
	.gpio_init = अणु .direction = 0xe000, .initial_value = 0x4000 पूर्ण,
	.xceive_pin = 10,
	.tuners = अणु
		अणु .std = V4L2_STD_ALL, .tuner = TUNER_XC2028 पूर्ण,
	पूर्ण,
	.pci_list = ivtv_pci_avertv_mce116,
	.i2c = &ivtv_i2c_std,
पूर्ण;

/* ------------------------------------------------------------------------- */

/* AVerMedia PVR-150 Plus / AVerTV M113 cards with a Daewoo/Partsnic Tuner */

अटल स्थिर काष्ठा ivtv_card_pci_info ivtv_pci_aver_pvr150[] = अणु
	अणु PCI_DEVICE_ID_IVTV16, IVTV_PCI_ID_AVERMEDIA, 0xc034 पूर्ण, /* NTSC */
	अणु PCI_DEVICE_ID_IVTV16, IVTV_PCI_ID_AVERMEDIA, 0xc035 पूर्ण, /* NTSC FM */
	अणु 0, 0, 0 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ivtv_card ivtv_card_aver_pvr150 = अणु
	.type = IVTV_CARD_AVER_PVR150PLUS,
	.name = "AVerMedia PVR-150 Plus / AVerTV M113 Partsnic (Daewoo) Tuner",
	.v4l2_capabilities = IVTV_CAP_ENCODER,
	.hw_video = IVTV_HW_CX25840,
	.hw_audio = IVTV_HW_CX25840,
	.hw_audio_ctrl = IVTV_HW_CX25840,
	.hw_muxer = IVTV_HW_GPIO,
	.hw_all = IVTV_HW_CX25840 | IVTV_HW_TUNER |
		  IVTV_HW_WM8739 | IVTV_HW_GPIO,
	.video_inमाला_दो = अणु
		अणु IVTV_CARD_INPUT_VID_TUNER,  0, CX25840_COMPOSITE2 पूर्ण,
		अणु IVTV_CARD_INPUT_SVIDEO1,    1, CX25840_SVIDEO3    पूर्ण,
		अणु IVTV_CARD_INPUT_COMPOSITE1, 1, CX25840_COMPOSITE1 पूर्ण,
	पूर्ण,
	.audio_inमाला_दो = अणु
		अणु IVTV_CARD_INPUT_AUD_TUNER,  CX25840_AUDIO5,       0 पूर्ण,
		अणु IVTV_CARD_INPUT_LINE_IN1,   CX25840_AUDIO_SERIAL, 1 पूर्ण,
	पूर्ण,
	.radio_input = अणु IVTV_CARD_INPUT_AUD_TUNER, CX25840_AUDIO_SERIAL, 2 पूर्ण,
	/* The 74HC4052 Dual 4:1 multiplexer is controlled by 2 GPIO lines */
	.gpio_init = अणु .direction = 0xc000, .initial_value = 0 पूर्ण,
	.gpio_audio_input  = अणु .mask   = 0xc000,
			       .tuner  = 0x0000,
			       .linein = 0x4000,
			       .radio  = 0x8000 पूर्ण,
	.tuners = अणु
		/* Subप्रणाली ID's 0xc03[45] have a Partsnic PTI-5NF05 tuner */
		अणु .std = V4L2_STD_MN, .tuner = TUNER_PARTSNIC_PTI_5NF05 पूर्ण,
	पूर्ण,
	.pci_list = ivtv_pci_aver_pvr150,
	/* Subप्रणाली ID 0xc035 has a TEA5767(?) FM tuner, 0xc034 करोes not */
	.i2c = &ivtv_i2c_radio,
पूर्ण;

/* ------------------------------------------------------------------------- */

/* AVerMedia UltraTV 1500 MCE (newer non-cx88 version, M113 variant) card */

अटल स्थिर काष्ठा ivtv_card_pci_info ivtv_pci_aver_ultra1500mce[] = अणु
	अणु PCI_DEVICE_ID_IVTV16, IVTV_PCI_ID_AVERMEDIA, 0xc019 पूर्ण, /* NTSC */
	अणु PCI_DEVICE_ID_IVTV16, IVTV_PCI_ID_AVERMEDIA, 0xc01b पूर्ण, /* PAL/SECAM */
	अणु 0, 0, 0 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ivtv_card ivtv_card_aver_ultra1500mce = अणु
	.type = IVTV_CARD_AVER_ULTRA1500MCE,
	.name = "AVerMedia UltraTV 1500 MCE / AVerTV M113 Philips Tuner",
	.comment = "For non-NTSC tuners, use the pal= or secam= module options",
	.v4l2_capabilities = IVTV_CAP_ENCODER,
	.hw_video = IVTV_HW_CX25840,
	.hw_audio = IVTV_HW_CX25840,
	.hw_audio_ctrl = IVTV_HW_CX25840,
	.hw_muxer = IVTV_HW_GPIO,
	.hw_all = IVTV_HW_CX25840 | IVTV_HW_TUNER |
		  IVTV_HW_WM8739 | IVTV_HW_GPIO,
	.video_inमाला_दो = अणु
		अणु IVTV_CARD_INPUT_VID_TUNER,  0, CX25840_COMPOSITE2 पूर्ण,
		अणु IVTV_CARD_INPUT_SVIDEO1,    1, CX25840_SVIDEO3    पूर्ण,
		अणु IVTV_CARD_INPUT_COMPOSITE1, 1, CX25840_COMPOSITE1 पूर्ण,
	पूर्ण,
	.audio_inमाला_दो = अणु
		अणु IVTV_CARD_INPUT_AUD_TUNER,  CX25840_AUDIO5,       0 पूर्ण,
		अणु IVTV_CARD_INPUT_LINE_IN1,   CX25840_AUDIO_SERIAL, 1 पूर्ण,
	पूर्ण,
	.radio_input = अणु IVTV_CARD_INPUT_AUD_TUNER, CX25840_AUDIO_SERIAL, 2 पूर्ण,
	/* The 74HC4052 Dual 4:1 multiplexer is controlled by 2 GPIO lines */
	.gpio_init = अणु .direction = 0xc000, .initial_value = 0 पूर्ण,
	.gpio_audio_input  = अणु .mask   = 0xc000,
			       .tuner  = 0x0000,
			       .linein = 0x4000,
			       .radio  = 0x8000 पूर्ण,
	.tuners = अणु
		/* The UltraTV 1500 MCE has a Philips FM1236 MK5 TV/FM tuner */
		अणु .std = V4L2_STD_MN, .tuner = TUNER_PHILIPS_FM1236_MK3 पूर्ण,
		अणु .std = V4L2_STD_PAL_SECAM, .tuner = TUNER_PHILIPS_FM1216MK5 पूर्ण,
	पूर्ण,
	.pci_list = ivtv_pci_aver_ultra1500mce,
	.i2c = &ivtv_i2c_std,
पूर्ण;

/* ------------------------------------------------------------------------- */

/* AVerMedia EZMaker PCI Deluxe card */

अटल स्थिर काष्ठा ivtv_card_pci_info ivtv_pci_aver_ezmaker[] = अणु
	अणु PCI_DEVICE_ID_IVTV16, IVTV_PCI_ID_AVERMEDIA, 0xc03f पूर्ण,
	अणु 0, 0, 0 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ivtv_card ivtv_card_aver_ezmaker = अणु
	.type = IVTV_CARD_AVER_EZMAKER,
	.name = "AVerMedia EZMaker PCI Deluxe",
	.v4l2_capabilities = IVTV_CAP_ENCODER,
	.hw_video = IVTV_HW_CX25840,
	.hw_audio = IVTV_HW_CX25840,
	.hw_audio_ctrl = IVTV_HW_CX25840,
	.hw_all = IVTV_HW_CX25840 | IVTV_HW_WM8739,
	.video_inमाला_दो = अणु
		अणु IVTV_CARD_INPUT_SVIDEO1,    0, CX25840_SVIDEO3 पूर्ण,
		अणु IVTV_CARD_INPUT_COMPOSITE1, 0, CX25840_COMPOSITE1 पूर्ण,
	पूर्ण,
	.audio_inमाला_दो = अणु
		अणु IVTV_CARD_INPUT_LINE_IN1,   CX25840_AUDIO_SERIAL, 0 पूर्ण,
	पूर्ण,
	.gpio_init = अणु .direction = 0x4000, .initial_value = 0x4000 पूर्ण,
	/* Does not have a tuner */
	.pci_list = ivtv_pci_aver_ezmaker,
पूर्ण;

/* ------------------------------------------------------------------------- */

/* ASUS Falcon2 */

अटल स्थिर काष्ठा ivtv_card_pci_info ivtv_pci_asus_falcon2[] = अणु
	अणु PCI_DEVICE_ID_IVTV16, IVTV_PCI_ID_ASUSTEK, 0x4b66 पूर्ण,
	अणु PCI_DEVICE_ID_IVTV16, IVTV_PCI_ID_ASUSTEK, 0x462e पूर्ण,
	अणु PCI_DEVICE_ID_IVTV16, IVTV_PCI_ID_ASUSTEK, 0x4b2e पूर्ण,
	अणु 0, 0, 0 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ivtv_card ivtv_card_asus_falcon2 = अणु
	.type = IVTV_CARD_ASUS_FALCON2,
	.name = "ASUS Falcon2",
	.v4l2_capabilities = IVTV_CAP_ENCODER,
	.hw_video = IVTV_HW_CX25840,
	.hw_audio = IVTV_HW_CX25840,
	.hw_audio_ctrl = IVTV_HW_CX25840,
	.hw_muxer = IVTV_HW_M52790,
	.hw_all = IVTV_HW_CX25840 | IVTV_HW_M52790 | IVTV_HW_TUNER,
	.video_inमाला_दो = अणु
		अणु IVTV_CARD_INPUT_VID_TUNER,  0, CX25840_COMPOSITE2 पूर्ण,
		अणु IVTV_CARD_INPUT_SVIDEO1,    1, CX25840_SVIDEO3    पूर्ण,
		अणु IVTV_CARD_INPUT_COMPOSITE1, 2, CX25840_COMPOSITE2 पूर्ण,
	पूर्ण,
	.audio_inमाला_दो = अणु
		अणु IVTV_CARD_INPUT_AUD_TUNER, CX25840_AUDIO5, M52790_IN_TUNER पूर्ण,
		अणु IVTV_CARD_INPUT_LINE_IN1, CX25840_AUDIO_SERIAL,
			M52790_IN_V2 | M52790_SW1_YCMIX | M52790_SW2_YCMIX पूर्ण,
		अणु IVTV_CARD_INPUT_LINE_IN1, CX25840_AUDIO_SERIAL, M52790_IN_V2 पूर्ण,
	पूर्ण,
	.radio_input = अणु IVTV_CARD_INPUT_AUD_TUNER, CX25840_AUDIO_SERIAL, M52790_IN_TUNER पूर्ण,
	.tuners = अणु
		अणु .std = V4L2_STD_MN, .tuner = TUNER_PHILIPS_FM1236_MK3 पूर्ण,
	पूर्ण,
	.pci_list = ivtv_pci_asus_falcon2,
	.i2c = &ivtv_i2c_std,
पूर्ण;

/* ------------------------------------------------------------------------- */

/* AVerMedia M104 miniPCI card */

अटल स्थिर काष्ठा ivtv_card_pci_info ivtv_pci_aver_m104[] = अणु
	अणु PCI_DEVICE_ID_IVTV16, IVTV_PCI_ID_AVERMEDIA, 0xc136 पूर्ण,
	अणु 0, 0, 0 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ivtv_card ivtv_card_aver_m104 = अणु
	.type = IVTV_CARD_AVER_M104,
	.name = "AVerMedia M104",
	.comment = "Not yet supported!\n",
	.v4l2_capabilities = 0, /*IVTV_CAP_ENCODER,*/
	.hw_video = IVTV_HW_CX25840,
	.hw_audio = IVTV_HW_CX25840,
	.hw_audio_ctrl = IVTV_HW_CX25840,
	.hw_all = IVTV_HW_CX25840 | IVTV_HW_TUNER | IVTV_HW_WM8739,
	.video_inमाला_दो = अणु
		अणु IVTV_CARD_INPUT_SVIDEO1,    0, CX25840_SVIDEO3    पूर्ण,
		अणु IVTV_CARD_INPUT_COMPOSITE1, 0, CX25840_COMPOSITE1 पूर्ण,
	पूर्ण,
	.audio_inमाला_दो = अणु
		अणु IVTV_CARD_INPUT_LINE_IN1,   CX25840_AUDIO_SERIAL, 1 पूर्ण,
	पूर्ण,
	.radio_input = अणु IVTV_CARD_INPUT_AUD_TUNER, CX25840_AUDIO_SERIAL, 2 पूर्ण,
	/* enable line-in + reset tuner */
	.gpio_init = अणु .direction = 0xe000, .initial_value = 0x4000 पूर्ण,
	.xceive_pin = 10,
	.tuners = अणु
		अणु .std = V4L2_STD_ALL, .tuner = TUNER_XC2028 पूर्ण,
	पूर्ण,
	.pci_list = ivtv_pci_aver_m104,
	.i2c = &ivtv_i2c_std,
पूर्ण;

/* ------------------------------------------------------------------------- */

/* Buffalo PC-MV5L/PCI cards */

अटल स्थिर काष्ठा ivtv_card_pci_info ivtv_pci_buffalo[] = अणु
	अणु PCI_DEVICE_ID_IVTV16, IVTV_PCI_ID_MELCO, 0x052b पूर्ण,
	अणु 0, 0, 0 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ivtv_card ivtv_card_buffalo = अणु
	.type = IVTV_CARD_BUFFALO_MV5L,
	.name = "Buffalo PC-MV5L/PCI",
	.v4l2_capabilities = IVTV_CAP_ENCODER,
	.hw_video = IVTV_HW_CX25840,
	.hw_audio = IVTV_HW_CX25840,
	.hw_audio_ctrl = IVTV_HW_CX25840,
	.hw_all = IVTV_HW_CX25840 | IVTV_HW_TUNER,
	.video_inमाला_दो = अणु
		अणु IVTV_CARD_INPUT_VID_TUNER,  0, CX25840_COMPOSITE2 पूर्ण,
		अणु IVTV_CARD_INPUT_SVIDEO1,    1,
			CX25840_SVIDEO_LUMA3 | CX25840_SVIDEO_CHROMA4 पूर्ण,
		अणु IVTV_CARD_INPUT_COMPOSITE1, 1, CX25840_COMPOSITE1 पूर्ण,
	पूर्ण,
	.audio_inमाला_दो = अणु
		अणु IVTV_CARD_INPUT_AUD_TUNER,  CX25840_AUDIO5       पूर्ण,
		अणु IVTV_CARD_INPUT_LINE_IN1,   CX25840_AUDIO_SERIAL पूर्ण,
	पूर्ण,
	.xceive_pin = 12,
	.tuners = अणु
		अणु .std = V4L2_STD_ALL, .tuner = TUNER_XC2028 पूर्ण,
	पूर्ण,
	.pci_list = ivtv_pci_buffalo,
	.i2c = &ivtv_i2c_std,
पूर्ण;

/* ------------------------------------------------------------------------- */
/* Sony Kikyou */

अटल स्थिर काष्ठा ivtv_card_pci_info ivtv_pci_kikyou[] = अणु
	अणु PCI_DEVICE_ID_IVTV16, IVTV_PCI_ID_SONY, 0x813d पूर्ण,
	अणु 0, 0, 0 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ivtv_card ivtv_card_kikyou = अणु
	.type = IVTV_CARD_KIKYOU,
	.name = "Sony VAIO Giga Pocket (ENX Kikyou)",
	.v4l2_capabilities = IVTV_CAP_ENCODER,
	.hw_video = IVTV_HW_SAA7115,
	.hw_audio = IVTV_HW_GPIO,
	.hw_audio_ctrl = IVTV_HW_GPIO,
	.hw_all = IVTV_HW_GPIO | IVTV_HW_SAA7115 | IVTV_HW_TUNER,
	.video_inमाला_दो = अणु
	अणु IVTV_CARD_INPUT_VID_TUNER,  0, IVTV_SAA71XX_COMPOSITE1 पूर्ण,
	अणु IVTV_CARD_INPUT_COMPOSITE1, 1, IVTV_SAA71XX_COMPOSITE1 पूर्ण,
	अणु IVTV_CARD_INPUT_SVIDEO1,    1, IVTV_SAA71XX_SVIDEO1 पूर्ण,
	पूर्ण,
	.audio_inमाला_दो = अणु
	     अणु IVTV_CARD_INPUT_AUD_TUNER,  IVTV_GPIO_TUNER पूर्ण,
	     अणु IVTV_CARD_INPUT_LINE_IN1,   IVTV_GPIO_LINE_IN पूर्ण,
	     अणु IVTV_CARD_INPUT_LINE_IN2,   IVTV_GPIO_LINE_IN पूर्ण,
	पूर्ण,
	.gpio_init = अणु .direction = 0x03e1, .initial_value = 0x0320 पूर्ण,
	.gpio_audio_input = अणु .mask   = 0x0060,
			      .tuner  = 0x0020,
			      .linein = 0x0000,
			      .radio  = 0x0060 पूर्ण,
	.gpio_audio_mute  = अणु .mask = 0x0000,
			      .mute = 0x0000 पूर्ण, /* 0x200? Disable क्रम now. */
	.gpio_audio_mode  = अणु .mask   = 0x0080,
			      .mono   = 0x0000,
			      .stereo = 0x0000, /* SAP */
			      .lang1  = 0x0080,
			      .lang2  = 0x0000,
			      .both   = 0x0080 पूर्ण,
	.tuners = अणु
	     अणु .std = V4L2_STD_ALL, .tuner = TUNER_SONY_BTF_PXN01Z पूर्ण,
	पूर्ण,
	.pci_list = ivtv_pci_kikyou,
	.i2c = &ivtv_i2c_std,
पूर्ण;


अटल स्थिर काष्ठा ivtv_card *ivtv_card_list[] = अणु
	&ivtv_card_pvr250,
	&ivtv_card_pvr350,
	&ivtv_card_pvr150,
	&ivtv_card_m179,
	&ivtv_card_mpg600,
	&ivtv_card_mpg160,
	&ivtv_card_pg600,
	&ivtv_card_avc2410,
	&ivtv_card_avc2010,
	&ivtv_card_tg5000tv,
	&ivtv_card_va2000,
	&ivtv_card_cx23416gyc,
	&ivtv_card_gv_mvprx,
	&ivtv_card_gv_mvprx2e,
	&ivtv_card_gotview_pci_dvd,
	&ivtv_card_gotview_pci_dvd2,
	&ivtv_card_yuan_mpc622,
	&ivtv_card_dcपंचांगvtvp1,
	&ivtv_card_pg600v2,
	&ivtv_card_club3d,
	&ivtv_card_avertv_mce116,
	&ivtv_card_asus_falcon2,
	&ivtv_card_aver_pvr150,
	&ivtv_card_aver_ezmaker,
	&ivtv_card_aver_m104,
	&ivtv_card_buffalo,
	&ivtv_card_aver_ultra1500mce,
	&ivtv_card_kikyou,

	/* Variations of standard cards but with the same PCI IDs.
	   These cards must come last in this list. */
	&ivtv_card_pvr350_v1,
	&ivtv_card_cx23416gyc_nogr,
	&ivtv_card_cx23416gyc_nogrycs,
पूर्ण;

स्थिर काष्ठा ivtv_card *ivtv_get_card(u16 index)
अणु
	अगर (index >= ARRAY_SIZE(ivtv_card_list))
		वापस शून्य;
	वापस ivtv_card_list[index];
पूर्ण

पूर्णांक ivtv_get_input(काष्ठा ivtv *itv, u16 index, काष्ठा v4l2_input *input)
अणु
	स्थिर काष्ठा ivtv_card_video_input *card_input = itv->card->video_inमाला_दो + index;
	अटल स्थिर अक्षर * स्थिर input_strs[] = अणु
		"Tuner 1",
		"S-Video 1",
		"S-Video 2",
		"Composite 1",
		"Composite 2",
		"Composite 3"
	पूर्ण;

	अगर (index >= itv->nof_inमाला_दो)
		वापस -EINVAL;
	input->index = index;
	strscpy(input->name, input_strs[card_input->video_type - 1],
		माप(input->name));
	input->type = (card_input->video_type == IVTV_CARD_INPUT_VID_TUNER ?
			V4L2_INPUT_TYPE_TUNER : V4L2_INPUT_TYPE_CAMERA);
	input->audioset = (1 << itv->nof_audio_inमाला_दो) - 1;
	input->std = (input->type == V4L2_INPUT_TYPE_TUNER) ?
				itv->tuner_std : V4L2_STD_ALL;
	वापस 0;
पूर्ण

पूर्णांक ivtv_get_output(काष्ठा ivtv *itv, u16 index, काष्ठा v4l2_output *output)
अणु
	स्थिर काष्ठा ivtv_card_output *card_output = itv->card->video_outमाला_दो + index;

	अगर (index >= itv->card->nof_outमाला_दो)
		वापस -EINVAL;
	output->index = index;
	strscpy(output->name, card_output->name, माप(output->name));
	output->type = V4L2_OUTPUT_TYPE_ANALOG;
	output->audioset = 1;
	output->std = V4L2_STD_ALL;
	वापस 0;
पूर्ण

पूर्णांक ivtv_get_audio_input(काष्ठा ivtv *itv, u16 index, काष्ठा v4l2_audio *audio)
अणु
	स्थिर काष्ठा ivtv_card_audio_input *aud_input = itv->card->audio_inमाला_दो + index;
	अटल स्थिर अक्षर * स्थिर input_strs[] = अणु
		"Tuner 1",
		"Line In 1",
		"Line In 2"
	पूर्ण;

	स_रखो(audio, 0, माप(*audio));
	अगर (index >= itv->nof_audio_inमाला_दो)
		वापस -EINVAL;
	strscpy(audio->name, input_strs[aud_input->audio_type - 1],
		माप(audio->name));
	audio->index = index;
	audio->capability = V4L2_AUDCAP_STEREO;
	वापस 0;
पूर्ण

पूर्णांक ivtv_get_audio_output(काष्ठा ivtv *itv, u16 index, काष्ठा v4l2_audioout *aud_output)
अणु
	स_रखो(aud_output, 0, माप(*aud_output));
	अगर (itv->card->video_outमाला_दो == शून्य || index != 0)
		वापस -EINVAL;
	strscpy(aud_output->name, "A/V Audio Out", माप(aud_output->name));
	वापस 0;
पूर्ण
