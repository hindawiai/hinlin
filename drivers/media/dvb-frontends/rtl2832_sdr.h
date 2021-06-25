<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Realtek RTL2832U SDR driver
 *
 * Copyright (C) 2013 Antti Palosaari <crope@iki.fi>
 *
 * GNU Radio plugin "gr-kernel" क्रम device usage will be on:
 * http://git.linuxtv.org/anttip/gr-kernel.git
 */

#अगर_अघोषित RTL2832_SDR_H
#घोषणा RTL2832_SDR_H

#समावेश <linux/i2c.h>
#समावेश <media/v4l2-subdev.h>
#समावेश <media/dvb_frontend.h>

/**
 * काष्ठा rtl2832_sdr_platक्रमm_data - Platक्रमm data क्रम the rtl2832_sdr driver
 * @clk: Clock frequency (4000000, 16000000, 25000000, 28800000).
 * @tuner: Used tuner model.
 * @regmap: poपूर्णांकer to &काष्ठा regmap.
 * @dvb_frontend: rtl2832 DVB frontend.
 * @v4l2_subdev: Tuner v4l2 controls.
 * @dvb_usb_device: DVB USB पूर्णांकerface क्रम USB streaming.
 */
काष्ठा rtl2832_sdr_platक्रमm_data अणु
	u32 clk;
	/*
	 * XXX: This list must be kept sync with dvb_usb_rtl28xxu USB IF driver.
	 */
#घोषणा RTL2832_SDR_TUNER_FC2580    0x21
#घोषणा RTL2832_SDR_TUNER_TUA9001   0x24
#घोषणा RTL2832_SDR_TUNER_FC0012    0x26
#घोषणा RTL2832_SDR_TUNER_E4000     0x27
#घोषणा RTL2832_SDR_TUNER_FC0013    0x29
#घोषणा RTL2832_SDR_TUNER_R820T     0x2a
#घोषणा RTL2832_SDR_TUNER_R828D     0x2b
	u8 tuner;

	काष्ठा regmap *regmap;
	काष्ठा dvb_frontend *dvb_frontend;
	काष्ठा v4l2_subdev *v4l2_subdev;
	काष्ठा dvb_usb_device *dvb_usb_device;
पूर्ण;

#पूर्ण_अगर /* RTL2832_SDR_H */
