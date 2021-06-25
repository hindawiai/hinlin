<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * The Virtual DTV test driver serves as a reference DVB driver and helps
 * validate the existing APIs in the media subप्रणाली. It can also aid
 * developers working on userspace applications.
 *
 * Copyright (C) 2020 Daniel W. S. Almeida
 */

#अगर_अघोषित VIDTV_TUNER_H
#घोषणा VIDTV_TUNER_H

#समावेश <linux/types.h>

#समावेश <media/dvb_frontend.h>

#घोषणा NUM_VALID_TUNER_FREQS 8

/**
 * काष्ठा vidtv_tuner_config - Configuration used to init the tuner.
 * @fe: A poपूर्णांकer to the dvb_frontend काष्ठाure allocated by vidtv_demod.
 * @mock_घातer_up_delay_msec: Simulate a घातer-up delay.
 * @mock_tune_delay_msec: Simulate a tune delay.
 * @vidtv_valid_dvb_t_freqs: The valid DVB-T frequencies to simulate.
 * @vidtv_valid_dvb_c_freqs: The valid DVB-C frequencies to simulate.
 * @vidtv_valid_dvb_s_freqs: The valid DVB-S frequencies to simulate.
 * @max_frequency_shअगरt_hz: The maximum frequency shअगरt in HZ allowed when
 * tuning in a channel
 *
 * The configuration used to init the tuner module, usually filled
 * by a bridge driver. For vidtv, this is filled by vidtv_bridge beक्रमe the
 * tuner module is probed.
 */
काष्ठा vidtv_tuner_config अणु
	काष्ठा dvb_frontend *fe;
	u32 mock_घातer_up_delay_msec;
	u32 mock_tune_delay_msec;
	u32 vidtv_valid_dvb_t_freqs[NUM_VALID_TUNER_FREQS];
	u32 vidtv_valid_dvb_c_freqs[NUM_VALID_TUNER_FREQS];
	u32 vidtv_valid_dvb_s_freqs[NUM_VALID_TUNER_FREQS];
	u8  max_frequency_shअगरt_hz;
पूर्ण;

#पूर्ण_अगर //VIDTV_TUNER_H
